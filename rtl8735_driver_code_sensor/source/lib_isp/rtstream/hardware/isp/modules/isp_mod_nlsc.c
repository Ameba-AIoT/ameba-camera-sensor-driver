/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_iq.h>
#include <isp_statis.h>
#include <isp_notify.h>
#include <isp_mod_crop.h>
#include <isp_mod_sensor.h>
#include <isp_mod_nlsc.h>
#include <isp_hw_nlsc.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_LSC

struct isp_mod_nlsc {
	struct isp_mod mod;
	const struct isp_hw_nlsc_ops *hw_ops;
	const isp_iq_nlsc_t *iq;

	rts_isp_point_t offset;

	isp_algo_param_nlsc_t *param;

	int in_std_illum;
};

static int isp_mod_nlsc_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_nlsc *nlsc;

	nlsc = get_mod(mod, nlsc);
	nlsc->hw_ops = isp_hw_nlsc_get_ops();
	if (nlsc->hw_ops == NULL) {
		isp_error("get nlsc hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	nlsc->param = &isp_iq_get_algo_param(mod->owner_id)->nlsc;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_nlsc_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int nlsc_judge_in_std_illum(struct isp_mod_nlsc *nlsc,
				   const struct rts_isp_awb_statis *statis)
{
	int i;
	uint32_t max_wp_num = 0;
	uint32_t white_pixel_rate;

	for (i = 0; i < (int)ARRAY_SIZE(statis->illum_white_pixels); i++)
		if (max_wp_num < statis->illum_white_pixels[i])
			max_wp_num = statis->illum_white_pixels[i];
	white_pixel_rate = max_wp_num * 1000 / 57600/* TODO: pixels from AWB */;
	if (white_pixel_rate > nlsc->iq->dyn_ct.pixels_for_enable)
		return RTS_ISP_TRUE;
	else if (white_pixel_rate < nlsc->iq->dyn_ct.pixels_for_disable)
		return RTS_ISP_FALSE;
	else
		return nlsc->in_std_illum;
}

static int check_nlsc_iq(const isp_iq_nlsc_t *iq)
{
	int i;

	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (iq->common.step == 0 || iq->common.r_curve_count == 0 ||
	    iq->common.r_curve_count != iq->common.g_curve_count ||
	    iq->common.r_curve_count != iq->common.b_curve_count)
		return -RTS_ISP_EINVAL;
	if (isp_iq_check_hysteresis_bounds(&iq->dyn_ct.bounds,
					   iq->dyn_ct.ct_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ct.ct_items_count; i++)
		if (isp_iq_check_bounds(&iq->dyn_ct.ct_items[i].bounds,
				iq->dyn_ct.ct_items[i].adjs_count))
			return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_nlsc_change_dyn_iq_notify(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);
	const isp_iq_nlsc_t *iq = nlsc->iq;

	if (iq->dyn_ct.enable)
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_STATIS_DONE);
	else
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_STATIS_DONE);
	if (ret)
		return ret;
	if (iq->dyn_ct.enable || iq->dyn_gain.enable)
		return isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	else
		return isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
}

static void intp_nlsc_adj(isp_iq_nlsc_adj_t *adj, uint32_t dyn_value,
			  uint32_t bound0, const isp_iq_nlsc_adj_t *adj0,
			  uint32_t bound1, const isp_iq_nlsc_adj_t *adj1)
{
	if (!adj || !adj0 || !adj1)
		return;

	adj->r = linear_intp(dyn_value, bound0, adj0->r, bound1, adj1->r);
	adj->g = linear_intp(dyn_value, bound0, adj0->g, bound1, adj1->g);
	adj->b = linear_intp(dyn_value, bound0, adj0->b, bound1, adj1->b);
}

static int mod_nlsc_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);
	const struct rts_isp_awb_statis *statis;

	statis = &((const struct rts_isp_statis *)data)->awb;
	nlsc->in_std_illum = nlsc_judge_in_std_illum(nlsc, statis);
	if (!nlsc->in_std_illum)
		nlsc->param->ct_index = nlsc->iq->dyn_ct.bounds.def_index;
	//isp_info("%s \r\n",__func__);
	return RTS_ISP_OK;
}

static int nlsc_set_center(struct isp_mod_nlsc *nlsc)
{
	int ret;
	struct isp_hw_nlsc_center center;
	struct isp_sensor_mode mode;

	ret = isp_mod_sibling_get_info(&nlsc->mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		return ret;
	center.r.x = nlsc->iq->common.r_center.x - nlsc->offset.x;
	center.g.x = nlsc->iq->common.g_center.x - nlsc->offset.x;
	center.b.x = nlsc->iq->common.b_center.x - nlsc->offset.x;
	center.r.y = nlsc->iq->common.r_center.y - nlsc->offset.y;
	center.g.y = nlsc->iq->common.g_center.y - nlsc->offset.y;
	center.b.y = nlsc->iq->common.b_center.y - nlsc->offset.y;

	center.r.x = clamp(center.r.x, 0, (int)mode.size.isp.w);
	center.g.x = clamp(center.g.x, 0, (int)mode.size.isp.w);
	center.b.x = clamp(center.b.x, 0, (int)mode.size.isp.w);
	center.r.y = clamp(center.r.y, 0, (int)mode.size.isp.h);
	center.g.y = clamp(center.g.y, 0, (int)mode.size.isp.h);
	center.b.y = clamp(center.b.y, 0, (int)mode.size.isp.h);

	return nlsc->hw_ops->set_center(nlsc->mod.owner_id, &center);
}

static int mod_nlsc_exec_set_offset(struct isp_mod *mod, void *data)
{
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);

	nlsc->offset = *(rts_isp_point_t *)data;

	return nlsc_set_center(nlsc);
}

static struct isp_mod_action_info nlsc_exec_actions[] = {
	ISP_MOD_ACTION(NLSC_EXEC_SET_OFFSET, mod_nlsc_exec_set_offset),
};

static int mod_nlsc_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);
	const isp_iq_nlsc_t *iq;
	const isp_iq_nlsc_ct_item_t *ct_item;

	nlsc->iq = isp_iq_get_nlsc(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_nlsc_iq(nlsc->iq))
		return -RTS_ISP_EINVAL;
	iq = nlsc->iq;

	ret = nlsc->hw_ops->set_nlsc(mod->owner_id, &nlsc->iq->common);
	if (ret)
		return ret;
	ret = nlsc_set_center(nlsc);
	if (ret)
		return ret;

	nlsc->param->ct_index = iq->dyn_ct.bounds.def_index;
	ct_item = &iq->dyn_ct.ct_items[nlsc->param->ct_index];
	nlsc->param->gain_index = ct_item->bounds.def_index;
	ret = nlsc->hw_ops->set_adj(mod->owner_id,
				    &ct_item->adjs[nlsc->param->gain_index]);
	if (ret)
		return ret;
	//isp_info("%s done \r\n", __func__);
	return mod_nlsc_change_dyn_iq_notify(mod);
}

static int mod_nlsc_dynamic(struct isp_mod *mod, void *data)
{
	isp_iq_nlsc_adj_t adj;
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);
	const isp_iq_nlsc_t *iq = nlsc->iq;
	const isp_iq_nlsc_ct_item_t *ct_item;
	const struct isp_notify_dynamic *dyn = data;

	if (iq->dyn_ct.enable && nlsc->in_std_illum)
		nlsc->param->ct_index =
			isp_iq_get_hysteresis_bound(&iq->dyn_ct.bounds,
						    dyn->awb.color_temp,
						    nlsc->param->ct_index);

	ct_item = &iq->dyn_ct.ct_items[nlsc->param->ct_index];

	if (iq->dyn_gain.enable) {
		int index;
		uint32_t dyn_value;

		if (ct_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;

		index = isp_iq_get_bound(&ct_item->bounds, dyn_value);
		nlsc->param->gain_index = index;
		if (index == 0)
			adj = ct_item->adjs[index];
		else if (index == ct_item->bounds.bounds_count)
			adj = ct_item->adjs[index - 1];
		else
			intp_nlsc_adj(&adj, dyn_value,
				      ct_item->bounds.bounds[index - 1],
				      &ct_item->adjs[index - 1],
				      ct_item->bounds.bounds[index],
				      &ct_item->adjs[index]);
	} else {
		nlsc->param->gain_index = ct_item->bounds.def_index;
		adj = ct_item->adjs[nlsc->param->gain_index];
	}

	return nlsc->hw_ops->set_adj(mod->owner_id, &adj);
}

static int mod_nlsc_crop_change(struct isp_mod *mod, void *data)
{
	struct isp_mod_nlsc *nlsc = get_mod(mod, nlsc);

	nlsc->offset = *(const rts_isp_point_t *)data;

	return nlsc_set_center(nlsc);
}

static struct isp_mod_action_info nlsc_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_nlsc_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_nlsc_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_nlsc_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_CROP_CHANGE, mod_nlsc_crop_change),
};

static struct isp_mod_nlsc nlsc;

int isp_register_mod_nlsc(void)
{
	memset(&nlsc, 0, sizeof(nlsc));
	nlsc.mod.id = MOD_NLSC;
	nlsc.mod.name = "nlsc";
	nlsc.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_STATIS_DONE_BIT |
						   ISP_CROP_CHANGE_BIT;
	nlsc.mod.init = isp_mod_nlsc_init;
	nlsc.mod.cleanup = isp_mod_nlsc_cleanup;
	nlsc.mod.exec_actions = nlsc_exec_actions;
	nlsc.mod.exec_actions_num = ARRAY_SIZE(nlsc_exec_actions);
	nlsc.mod.notify_actions = nlsc_notify_actions;
	nlsc.mod.notify_actions_num = ARRAY_SIZE(nlsc_notify_actions);
	return isp_mod_register(&nlsc.mod);
}

void isp_unregister_mod_nlsc(void)
{
	isp_mod_unregister(&nlsc.mod);
}

