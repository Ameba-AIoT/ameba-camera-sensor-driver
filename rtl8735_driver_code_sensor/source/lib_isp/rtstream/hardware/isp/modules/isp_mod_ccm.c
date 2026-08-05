/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "rts_isp.h"
#include <isp_utils.h>
#include <isp_v4l2_ctrl.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_mod_ccm.h>
#include <isp_hw_ccm.h>
#include <string.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_CCM

struct isp_mod_ccm {
	struct isp_mod mod;
	const struct isp_hw_ccm_ops *hw_ops;
	const isp_iq_ccm_t *iq;

	isp_algo_param_ccm_t *param;

	isp_iq_ccm_item_t current;
	isp_iq_ccm_item_t target;

	uint8_t force_update;
	enum rts_isp_dynamic_iq_mode dyn_iq_mode;

	struct {
		struct v4l2_ctrl *auto_ccm_ctrl;
		struct v4l2_ctrl *ccm_matrix_ctrl;
	};
};

static int isp_mod_ccm_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_ccm *ccm;

	ccm = get_mod(mod, ccm);
	ccm->hw_ops = isp_hw_ccm_get_ops();
	if (ccm->hw_ops == NULL) {
		isp_error("get ccm hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	ccm->param = &isp_iq_get_algo_param(mod->owner_id)->ccm;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_ccm_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int __mod_ccm_set(struct isp_mod *mod)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	if (ccm->auto_ccm_ctrl && !ccm->auto_ccm_ctrl->val)
		return RTS_ISP_OK;

	return ccm->hw_ops->set_ccm(mod->owner_id, &ccm->current);
}

static int check_ccm_iq(const isp_iq_ccm_t *iq)
{

	int i;

	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (isp_iq_check_hysteresis_bounds(&iq->dyn_ct.bounds,
					   iq->dyn_ct.ct_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ct.ct_items_count; i++)
		if (isp_iq_check_bounds(&iq->dyn_ct.ct_items[i].bounds,
				iq->dyn_ct.ct_items[i].gain_items_count))
			return -RTS_ISP_EINVAL;
	if (iq->dyn_ht.enable &&
	    isp_iq_check_bounds(&iq->dyn_ht.bounds, iq->dyn_ht.items_count))
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int ccm_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_ccm_item_t *items)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	if (index == 0)
		ccm->target = items[index];
	else if (index == bounds->bounds_count)
		ccm->target = items[index - 1];
	else
		linear_intp_array(ccm->target.ccm, dyn_value,
				  bounds->bounds[index - 1],
				  items[index - 1].ccm,
				  bounds->bounds[index], items[index].ccm,
				  ARRAY_SIZE(ccm->target.ccm));
	//printf("index %d bounds_count %d dyn_value %d \r\n", (uint32_t)index, (uint32_t)bounds->bounds_count, (uint32_t)dyn_value);
	return RTS_ISP_OK;
}

static int mod_ccm_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	if ( !ccm->force_update &&
			memcmp(&ccm->current, &ccm->target, sizeof(ccm->current)) == 0)
		return RTS_ISP_OK;

	ccm->force_update = RTS_ISP_FALSE;

	if (ccm->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		calc_smooth_array(ccm->current.ccm, ccm->target.ccm, 8, 16,
				  ARRAY_SIZE(ccm->current.ccm));
	else
		memcpy(&ccm->current, &ccm->target, sizeof(ccm->current));
	//isp_info("%s \r\n",__func__);
	return __mod_ccm_set(mod);
}

static int mod_ccm_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);
	const isp_iq_ccm_t *iq;
	const isp_iq_ccm_ct_item_t *ct_item;
	int dyn_enable;

	ccm->iq = isp_iq_get_ccm(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_ccm_iq(ccm->iq))
		return -RTS_ISP_EINVAL;
	iq = ccm->iq;

	ccm->param->ct_index = iq->dyn_ct.bounds.def_index;
	ct_item = &iq->dyn_ct.ct_items[ccm->param->ct_index];
	ccm->param->gain_index = ct_item->bounds.def_index;
	ccm->current = ct_item->gain_items[ccm->param->gain_index];
	ccm->target = ccm->current;
	ret = __mod_ccm_set(mod);
	if (ret)
		return ret;
	dyn_enable = (iq->dyn_ct.enable || iq->dyn_gain.enable ||
		      iq->dyn_ht.enable);
	//isp_info("%s done \r\n", __func__);
	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static int mod_ccm_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);
	const isp_iq_ccm_t *iq = ccm->iq;
	const isp_iq_ccm_ct_item_t *ct_item;
	const struct isp_notify_dynamic *dyn = data;

	ccm->force_update = RTS_ISP_TRUE;
	ccm->dyn_iq_mode = dyn->dyn_mode;

	if (iq->dyn_ht.enable && dyn->sensor.high_temp_en) {
		uint32_t dyn_value;

		if (iq->dyn_ht.based_on_gain)
			dyn_value = dyn->ae.gain;
		else
			dyn_value = dyn->sensor.temperature;
		ccm->param->ht_index =
			isp_iq_get_bound(&iq->dyn_ht.bounds, dyn_value);
		ccm_intp_target(mod, dyn_value, ccm->param->ht_index,
			&iq->dyn_ht.bounds, iq->dyn_ht.items);

		goto SET_CCM;
	}

	if (iq->dyn_ct.enable)
		ccm->param->ct_index =
			isp_iq_get_hysteresis_bound(&iq->dyn_ct.bounds,
							    dyn->awb.color_temp,
						    ccm->param->ct_index);
	ct_item = &iq->dyn_ct.ct_items[ccm->param->ct_index];
	if (iq->dyn_gain.enable) {
		uint32_t dyn_value;

		if (ct_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;
		//printf("dyn_gain.enable %d dyn_ct.enable %d color_temp %d dyn_value %d\r\n", (uint32_t)iq->dyn_gain.enable, (uint32_t)iq->dyn_ct.enable, (uint32_t)dyn->awb.color_temp, (uint32_t)dyn_value);
		ccm->param->gain_index = isp_iq_get_bound(&ct_item->bounds, dyn_value);
		ccm_intp_target(mod, dyn_value, ccm->param->gain_index,
			&ct_item->bounds, ct_item->gain_items);
	} else {
		ccm->param->gain_index = ct_item->bounds.def_index;
		ccm->target = ct_item->gain_items[ccm->param->gain_index];
	}

SET_CCM:
	if (ccm->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		memcmp(&ccm->current, &ccm->target, sizeof(ccm->current)) == 0)
		return RTS_ISP_OK;

	ccm->force_update = RTS_ISP_FALSE;
	memcpy(&ccm->current, &ccm->target, sizeof(ccm->current));
	return __mod_ccm_set(mod);
}

static int mod_ccm_dynamic_post(struct isp_mod *mod, void *data)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	return ccm->hw_ops->update_cac(mod->owner_id);
}

static struct isp_mod_action_info ccm_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_ccm_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_ccm_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_ccm_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC_POST, mod_ccm_dynamic_post),
};

static int ccm_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	int i;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	switch (ctrl->id) {
	case RTS_V4L2_CID_AUTO_CCM:
		for (i = 0; i < (int)ARRAY_SIZE(ccm->current.ccm); i++)
			ccm->ccm_matrix_ctrl->p_new.p_s32[i] =
				ccm->current.ccm[i];
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int ccm_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int i;
	int ret = RTS_ISP_OK;
	isp_iq_ccm_item_t item;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);

	switch (ctrl->id) {
	case RTS_V4L2_CID_AUTO_CCM:
		if (ctrl->val) {
			if (ctrl->is_new)
				ret = __mod_ccm_set(mod);
		} else if (ccm->ccm_matrix_ctrl->is_new) {
			for (i = 0; i < (int)ARRAY_SIZE(item.ccm); i++)
				item.ccm[i] =
					ccm->ccm_matrix_ctrl->p_new.p_s32[i];
			ret = ccm->hw_ops->set_ccm(mod->owner_id, &item);
		}
		break;
	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set ccm ctrl fail");
	return ret;
}

static const struct v4l2_ctrl_ops ccm_ctrl_ops = {
	.g_volatile_ctrl = ccm_g_volatile_ctrl,
	.s_ctrl = ccm_s_ctrl,
};

static int isp_mod_ccm_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_ccm *ccm = get_mod(mod, ccm);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config auto_ccm_config = {
		.ops = &ccm_ctrl_ops,
		.id = RTS_V4L2_CID_AUTO_CCM,
		.name = "Auto CCM",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 1,
	};
	const struct v4l2_ctrl_config ccm_matrix_config = {
		.ops = &ccm_ctrl_ops,
		.id = RTS_V4L2_CID_CCM_MATRIX,
		.name = "CCM matrix",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = -2048,
		.max = 2047,
		.step = 1,
		.def = 0,
		.dims = {ARRAY_SIZE(ccm->current.ccm)},
	};

	ccm->auto_ccm_ctrl = rtsv_ctrl_new_custom(handler,
						  &auto_ccm_config, mod);
	ccm->ccm_matrix_ctrl = rtsv_ctrl_new_custom(handler,
						    &ccm_matrix_config, mod);
	rtsv_ctrl_auto_cluster(2, &ccm->auto_ccm_ctrl, 0, RTS_ISP_TRUE);
	if (handler->error) {
		isp_perror(handler->error, "add ccm ctrl fail");
		return handler->error;

	}
	return RTS_ISP_OK;

}

static struct isp_mod_ccm ccm;

int isp_register_mod_ccm(void)
{
	memset(&ccm, 0, sizeof(ccm));
	ccm.mod.id = MOD_CCM;
	ccm.mod.name = "ccm";
	ccm.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_DYNAMIC_POST_BIT;
	ccm.mod.init = isp_mod_ccm_init;
	ccm.mod.cleanup = isp_mod_ccm_cleanup;
	ccm.mod.add_ctrl = isp_mod_ccm_add_ctrl;
	ccm.mod.notify_actions = ccm_notify_actions;
	ccm.mod.notify_actions_num = ARRAY_SIZE(ccm_notify_actions);
	return isp_mod_register(&ccm.mod);
}

void isp_unregister_mod_ccm(void)
{
	isp_mod_unregister(&ccm.mod);
}

