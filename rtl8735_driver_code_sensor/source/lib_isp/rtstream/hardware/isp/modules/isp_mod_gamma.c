/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */
#include "rts_isp.h"
#include <isp_v4l2_ctrl.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod_gamma.h>
#include <isp_mod_sensor.h>
#include <isp_hw_gamma.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_GAMMA

struct isp_mod_gamma {
	struct isp_mod mod;
	const struct isp_hw_gamma_ops *hw_ops;
	const isp_iq_gamma_t *iq;

	isp_algo_param_gamma_t *param;

	isp_iq_gamma_item_t current;
	isp_iq_gamma_item_t target;

	uint8_t force_update;
	enum rts_isp_sensor_hdr_mode hdr_mode;
	enum rts_isp_dynamic_iq_mode dyn_iq_mode;

	struct {
		struct v4l2_ctrl *auto_gamma_ctrl;
		struct v4l2_ctrl *gamma_curve_ctrl;
	};
};

static int __mod_gamma_set(struct isp_mod *mod)
{
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	if (gamma->auto_gamma_ctrl && !gamma->auto_gamma_ctrl->val)
		return RTS_ISP_OK;

	return gamma->hw_ops->set_gamma(mod->owner_id, &gamma->current);
}

static int gamma_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	int i;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	switch (ctrl->id) {
	case RTS_V4L2_CID_AUTO_GAMMA:
		for (i = 0; i < (int)gamma->gamma_curve_ctrl->elems; i++)
			gamma->gamma_curve_ctrl->p_new.p_u16[i] =
				gamma->current.curve[i];
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int gamma_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int i;
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	switch (ctrl->id) {
	case RTS_V4L2_CID_AUTO_GAMMA:
		if (ctrl->val) {
			if (ctrl->is_new)
				ret = __mod_gamma_set(mod);
		} else if (gamma->gamma_curve_ctrl->is_new) {
			isp_iq_gamma_item_t manual_iq;

			manual_iq.curve_count = gamma->gamma_curve_ctrl->elems;
			if (!isp_calloc_array(manual_iq.curve,
					      manual_iq.curve_count)) {
				ret = -RTS_ISP_ENOMEM;
				break;
			}
			for (i = 0; i < manual_iq.curve_count; i++)
				manual_iq.curve[i] =
					gamma->gamma_curve_ctrl->p_new.p_u16[i];
			ret = gamma->hw_ops->set_gamma(mod->owner_id,
						       &manual_iq);
			isp_free(manual_iq.curve);
		}
		break;
	default:
		break;
	}
	return ret;
}

static const struct v4l2_ctrl_ops gamma_ctrl_ops = {
	.g_volatile_ctrl = gamma_g_volatile_ctrl,
	.s_ctrl = gamma_s_ctrl,
};

static int check_gamma_iq(const isp_iq_gamma_t *iq)
{
	int i, j;

	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (isp_iq_check_bounds(&iq->dyn_ratio.bounds,
				iq->dyn_ratio.ratio_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ratio.ratio_items_count; i++) {
		if (isp_iq_check_bounds(&iq->dyn_ratio.ratio_items[i].bounds,
				iq->dyn_ratio.ratio_items[i].gain_items_count))
			return -RTS_ISP_EINVAL;

		// each gamma curve should have 35 items.
		for (j = 0; j < iq->dyn_ratio.ratio_items[i].gain_items_count; j++)
			if (iq->dyn_ratio.ratio_items[i].gain_items[j].curve_count != 35)
				return -RTS_ISP_EINVAL;
	}

	if (iq->dyn_ht.enable &&
	    isp_iq_check_bounds(&iq->dyn_ht.bounds, iq->dyn_ht.items_count))
		return -RTS_ISP_EINVAL;
	for (i = 1; i < iq->dyn_ht.items_count; i++)
		if (iq->dyn_ht.items[i].curve_count !=
		    iq->dyn_ht.items[0].curve_count)
			return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int gamma_intp_target(struct isp_mod *mod, int dyn_value, int index,
			     const isp_iq_bounds_t *bounds,
			     const isp_iq_gamma_item_t *items)
{
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	if (index == 0)
		isp_memcpy_array(gamma->target.curve, items[index].curve,
				 gamma->target.curve_count);
	else if (index == bounds->bounds_count)
		isp_memcpy_array(gamma->target.curve, items[index - 1].curve,
				 gamma->target.curve_count);
	else
		linear_intp_array(gamma->target.curve, dyn_value,
				  bounds->bounds[index - 1],
				  items[index - 1].curve,
				  bounds->bounds[index], items[index].curve,
				  gamma->target.curve_count);
	return RTS_ISP_OK;
}

static int mod_gamma_statis_done(struct isp_mod *mod, void *data)
{

	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	if (!gamma->force_update &&
		isp_memcmp_array(gamma->current.curve, gamma->target.curve,
			     gamma->current.curve_count) == 0)
		return RTS_ISP_OK;

	gamma->force_update = RTS_ISP_FALSE;
	if (gamma->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		calc_smooth_array(gamma->current.curve, gamma->target.curve, 8,
				  128, gamma->current.curve_count);
	else
		isp_memcpy_array(gamma->current.curve, gamma->target.curve,
			     gamma->current.curve_count);
	//isp_info("%s \r\n",__func__);
	return __mod_gamma_set(mod);
}

static int mod_gamma_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);
	const isp_iq_gamma_t *iq;
	const isp_iq_gamma_item_t *gamma_item;
	const isp_iq_gamma_ratio_item_t *ratio_item;
	int dyn_enable;

	gamma->iq = isp_iq_get_gamma(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_gamma_iq(gamma->iq))
		return -RTS_ISP_ENOITEM;
	iq = gamma->iq;

	if (gamma->hdr_mode == LINEAR_MODE)
		gamma->param->ratio_index = 0;
	else
		gamma->param->ratio_index = iq->dyn_ratio.bounds.def_index;
	ratio_item = &iq->dyn_ratio.ratio_items[gamma->param->ratio_index];
	gamma->param->gain_index = ratio_item->bounds.def_index;
	gamma_item = &ratio_item->gain_items[gamma->param->gain_index];

	isp_free(gamma->current.curve);
	isp_free(gamma->target.curve);
	gamma->current.curve_count = gamma_item->curve_count;
	gamma->target.curve_count = gamma_item->curve_count;
	if (!isp_calloc_array(gamma->current.curve, gamma->current.curve_count))
		return -RTS_ISP_ENOMEM;
	if (!isp_calloc_array(gamma->target.curve, gamma->target.curve_count)) {
		isp_free(gamma->current.curve);
		return -RTS_ISP_ENOMEM;
	}
	isp_memcpy_array(gamma->current.curve,
			 gamma_item->curve, gamma_item->curve_count);
	isp_memcpy_array(gamma->target.curve,
			 gamma_item->curve, gamma_item->curve_count);

	ret = __mod_gamma_set(mod);
	if (ret)
		return ret;
	dyn_enable = iq->dyn_ratio.enable || iq->dyn_ht.enable ||
				iq->dyn_gain.enable;
	//isp_info("%s done \r\n", __func__);
	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static int mod_gamma_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);
	const struct isp_notify_dynamic *dyn = data;
	const isp_iq_gamma_t *iq = gamma->iq;
	const isp_iq_gamma_ratio_item_t *ratio_item;

	gamma->force_update = RTS_ISP_TRUE;
	gamma->dyn_iq_mode = dyn->dyn_mode;

	if (iq->dyn_ht.enable && dyn->sensor.high_temp_en) {
		uint32_t dyn_value;

		if (iq->dyn_ht.based_on_gain)
			dyn_value = dyn->ae.gain;
		else
			dyn_value = dyn->sensor.temperature;
		gamma->param->ht_index =
			isp_iq_get_bound(&iq->dyn_ht.bounds, dyn_value);
		gamma_intp_target(mod, dyn_value, gamma->param->ht_index,
			&iq->dyn_ht.bounds, iq->dyn_ht.items);

		goto SET_GAMMA;
	}

	if (iq->dyn_ratio.enable) {
		gamma->param->ratio_index = isp_iq_get_bound(
			&iq->dyn_ratio.bounds, dyn->ae.iq_ratio[1]
		);
		gamma->param->ratio_index =
			(gamma->param->ratio_index ==
			 iq->dyn_ratio.bounds.bounds_count) ?
				gamma->param->ratio_index - 1 :
				gamma->param->ratio_index;
	}

	ratio_item = &iq->dyn_ratio.ratio_items[gamma->param->ratio_index];

	if (iq->dyn_gain.enable) {
		uint32_t dyn_value;
		if (ratio_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;
		gamma->param->gain_index =
		isp_iq_get_bound(&ratio_item->bounds, dyn_value);

		gamma_intp_target(mod, dyn_value, gamma->param->gain_index,
			&ratio_item->bounds, ratio_item->gain_items);
	} else {
		gamma->param->gain_index = ratio_item->bounds.def_index;
		gamma->target = ratio_item->gain_items[gamma->param->gain_index];
	}

SET_GAMMA:
	if (gamma->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		isp_memcmp_array(gamma->current.curve, gamma->target.curve,
			gamma->current.curve_count) == 0)
		return RTS_ISP_OK;

	gamma->force_update = RTS_ISP_FALSE;
	isp_memcpy_array(gamma->current.curve, gamma->target.curve,
		gamma->current.curve_count);
	return __mod_gamma_set(mod);
}

static int mod_gamma_hdr_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_sensor_mode mode = {
		.hdr = LINEAR_MODE,
	};
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
								   &mode, sizeof(mode));
	if (ret)
		return ret;

	gamma->hdr_mode = mode.hdr;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info gamma_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_gamma_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_gamma_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_gamma_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_gamma_hdr_mode_change),
};

static int isp_mod_gamma_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_gamma *gamma;

	gamma = get_mod(mod, gamma);
	gamma->hw_ops = isp_hw_gamma_get_ops();
	if (gamma->hw_ops == NULL) {
		isp_error("get gamma hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	gamma->param = &isp_iq_get_algo_param(mod->owner_id)->gamma;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_gamma_cleanup(struct isp_mod *mod)
{
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);

	isp_free(gamma->current.curve);
	isp_free(gamma->target.curve);
	return RTS_ISP_OK;
}

static int isp_mod_gamma_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_gamma *gamma = get_mod(mod, gamma);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config auto_gamma_config = {
		.ops = &gamma_ctrl_ops,
		.id = RTS_V4L2_CID_AUTO_GAMMA,
		.name = "Auto RGB gamma",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 1,
	};
	const struct v4l2_ctrl_config gamma_curve_config = {
		.ops = &gamma_ctrl_ops,
		.id = RTS_V4L2_CID_GAMMA_CURVE,
		.name = "RGB gamma curve",
		.type = V4L2_CTRL_TYPE_U16,
		.min = 0,
		.max = 4095,
		.step = 1,
		.def = 0,
		.dims = {gamma->iq->dyn_ratio.ratio_items[0].gain_items[0].curve_count}
	};
	gamma->auto_gamma_ctrl = rtsv_ctrl_new_custom(handler,
						      &auto_gamma_config, mod);
	gamma->gamma_curve_ctrl = rtsv_ctrl_new_custom(handler,
						       &gamma_curve_config,
						       mod);
	rtsv_ctrl_auto_cluster(2, &gamma->auto_gamma_ctrl, 0, RTS_ISP_TRUE);
	if (handler->error) {
		isp_perror(handler->error, "add gamma ctrls fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_gamma __gamma;

int isp_register_mod_gamma(void)
{
	memset(&__gamma, 0, sizeof(__gamma));
	__gamma.mod.id = MOD_GAMMA;
	__gamma.mod.name = "gamma";
	__gamma.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_HDR_MODE_CHANGE_BIT;
	__gamma.mod.init = isp_mod_gamma_init;
	__gamma.mod.cleanup = isp_mod_gamma_cleanup;
	__gamma.mod.add_ctrl = isp_mod_gamma_add_ctrl;
	__gamma.mod.notify_actions = gamma_notify_actions;
	__gamma.mod.notify_actions_num = ARRAY_SIZE(gamma_notify_actions);
	return isp_mod_register(&__gamma.mod);
}

void isp_unregister_mod_gamma(void)
{
	isp_mod_unregister(&__gamma.mod);
}

