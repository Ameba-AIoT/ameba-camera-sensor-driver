/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */


#include "rts_isp.h"
#include "rts_isp_patch.h"
#include <isp_utils.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod_sensor.h>
#include <isp_mod_blc.h>
#include <isp_hw_blc.h>
#include <string.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_BLC

struct isp_mod_blc {
	struct isp_mod mod;
	const struct isp_hw_blc_ops *hw_ops;
	const isp_iq_blc_t *iq;

	isp_iq_blc_offset_t current;
	isp_iq_blc_offset_t target;

	isp_algo_param_blc_t *param;

	int bits;
	uint8_t force_update;

	enum rts_isp_dynamic_iq_mode dyn_iq_mode;
};

static int __mod_blc_set(struct isp_mod *mod)
{
	struct isp_mod_blc *blc = get_mod(mod, blc);

	return blc->hw_ops->set(mod->owner_id, &blc->current, blc->bits);
}

static int mod_blc_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	const struct rts_isp_interface_info *info = NULL;
	struct isp_mod_blc *blc = get_mod(mod, blc);

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_INTERFACE,
				       &info, sizeof(struct rts_isp_interface_info *));
	if (ret)
		return ret;

	if (info != NULL)
		blc->bits = info->bit_depth;

	return __mod_blc_set(mod);
}

static int isp_mod_blc_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_blc *blc;

	blc = get_mod(mod, blc);
	blc->hw_ops = isp_hw_blc_get_ops();
	if (blc->hw_ops == NULL) {
		isp_error("get blc hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	blc->param = &isp_iq_get_algo_param(mod->owner_id)->blc;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_blc_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static void calc_smooth_blc_offset(isp_iq_blc_offset_t *cur,
				   const isp_iq_blc_offset_t *target, int num)
{
	int i;
	const int max = 16;
	const int div = 8;

	for (i = 0; i < num; i++) {
		cur->r[i] = calc_smooth(cur->r[i], target->r[i], div, max);
		cur->gr[i] = calc_smooth(cur->gr[i], target->gr[i], div, max);
		cur->gb[i] = calc_smooth(cur->gb[i], target->gb[i], div, max);
		cur->b[i] = calc_smooth(cur->b[i], target->b[i], div, max);
	}
}

static int check_blc_iq(const isp_iq_blc_t *iq)
{
	int i;

	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (isp_iq_check_hysteresis_bounds(&iq->dyn_ct.bounds,
					   iq->dyn_ct.ct_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ct.ct_items_count; i++)
		if (isp_iq_check_bounds(&iq->dyn_ct.ct_items[i].bounds,
					iq->dyn_ct.ct_items[i].offsets_count))
			return -RTS_ISP_EINVAL;
	if (iq->dyn_ht.enable &&
	    isp_iq_check_bounds(&iq->dyn_ht.bounds, iq->dyn_ht.offsets_count))
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_blc_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_blc *blc = get_mod(mod, blc);

	if (!blc->force_update &&
		memcmp(&blc->current, &blc->target, sizeof(blc->current)) == 0)
		return RTS_ISP_OK;

	blc->force_update = RTS_ISP_FALSE;
	if (blc->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		calc_smooth_blc_offset(&blc->current, &blc->target,
				       blc->hw_ops->get_num(mod->owner_id));
	else
		memcpy(&blc->current, &blc->target, sizeof(blc->target));
	//isp_info("%s \r\n",__func__);
	return __mod_blc_set(mod);
}

static int mod_blc_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_blc *blc = get_mod(mod, blc);
	const isp_iq_blc_t *iq;
	const isp_iq_blc_ct_item_t *ct_item;
	int dyn_enable;

	blc->iq = isp_iq_get_blc(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_blc_iq(blc->iq))
		return -RTS_ISP_EINVAL;
	iq = blc->iq;

	blc->param->ct_index = iq->dyn_ct.bounds.def_index;
	ct_item = &iq->dyn_ct.ct_items[blc->param->ct_index];
	blc->param->gain_index = ct_item->bounds.def_index;
	blc->current = ct_item->offsets[blc->param->gain_index];
	blc->target = ct_item->offsets[blc->param->gain_index];
	ret = __mod_blc_set(mod);
	if (ret)
		return ret;
	dyn_enable = (iq->dyn_gain.enable || iq->dyn_ct.enable ||
		      iq->dyn_ht.enable);

	//isp_info("%s done \r\n", __func__);
	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static void intp_blc_offset(isp_iq_blc_offset_t *offset, uint32_t dyn_value,
			    uint32_t bound0, const isp_iq_blc_offset_t *offset0,
			    uint32_t bound1, const isp_iq_blc_offset_t *offset1,
			    int num)
{
	int i;

	if (!offset || !offset0 || !offset1)
		return;

	for (i = 0; i < num; i++) {
		offset->r[i] = linear_intp(dyn_value,
					   bound0, offset0->r[i],
					   bound1, offset1->r[i]);
		offset->gr[i] = linear_intp(dyn_value,
					    bound0, offset0->gr[i],
					    bound1, offset1->gr[i]);
		offset->gb[i] = linear_intp(dyn_value,
					    bound0, offset0->gb[i],
					    bound1, offset1->gb[i]);
		offset->b[i] = linear_intp(dyn_value,
					   bound0, offset0->b[i],
					   bound1, offset1->b[i]);
	}
}

static int blc_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_blc_offset_t *offsets)
{
	struct isp_mod_blc *blc = get_mod(mod, blc);

	if (index == 0) {
		blc->target = offsets[index];
	} else if (index == bounds->bounds_count) {
		blc->target = offsets[index - 1];
	} else {
		intp_blc_offset(&blc->target, dyn_value,
				bounds->bounds[index - 1], &offsets[index - 1],
				bounds->bounds[index], &offsets[index],
				blc->hw_ops->get_num(mod->owner_id));
	}

	return RTS_ISP_OK;
}

static int mod_blc_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_blc *blc = get_mod(mod, blc);
	const isp_iq_blc_t *iq = blc->iq;
	isp_iq_blc_ct_item_t *ct_item;
	struct isp_notify_dynamic *dyn = data;

	blc->force_update = RTS_ISP_TRUE;
	blc->dyn_iq_mode = dyn->dyn_mode;

	if (dyn->sensor.high_temp_en && iq->dyn_ht.enable) {
		uint32_t dyn_value;

		if (iq->dyn_ht.based_on_gain)
			dyn_value = dyn->ae.gain;
		else
			dyn_value = dyn->sensor.temperature;
		blc->param->ht_index =
			isp_iq_get_bound(&iq->dyn_ht.bounds, dyn_value);
		blc_intp_target(mod, dyn_value, blc->param->ht_index,
			&iq->dyn_ht.bounds, iq->dyn_ht.offsets);

		goto SET_BLC;
	}

	if (iq->dyn_ct.enable)
		blc->param->ct_index =
			isp_iq_get_hysteresis_bound(&iq->dyn_ct.bounds,
						    dyn->awb.color_temp,
						    blc->param->ct_index);

	ct_item = &iq->dyn_ct.ct_items[blc->param->ct_index];

	if (iq->dyn_gain.enable) {
		uint32_t dyn_value;

		if (ct_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;
		blc->param->gain_index =
			isp_iq_get_bound(&ct_item->bounds, dyn_value);
		blc_intp_target(mod, dyn_value, blc->param->gain_index,
			&ct_item->bounds, ct_item->offsets);

	} else {
		blc->param->gain_index = ct_item->bounds.def_index;
		blc->target = ct_item->offsets[blc->param->gain_index];
	}

SET_BLC:
	if (blc->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		memcmp(&blc->current, &blc->target, sizeof(blc->current)) == 0)
		return RTS_ISP_OK;

	blc->force_update = RTS_ISP_FALSE;
	memcpy(&blc->current, &blc->target, sizeof(blc->target));
	return __mod_blc_set(mod);
}

static struct isp_mod_action_info blc_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_blc_mode_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_blc_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_blc_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_blc_dynamic),
};

static struct isp_mod_blc blc;

int isp_register_mod_blc(void)
{
	memset(&blc, 0, sizeof(blc));
	blc.mod.id = MOD_BLC;
	blc.mod.name = "blc";
	blc.mod.notify_bits = (ISP_IQ_CHANGE_BIT | ISP_HDR_MODE_CHANGE_BIT);
	blc.mod.init = isp_mod_blc_init;
	blc.mod.cleanup = isp_mod_blc_cleanup;
	blc.mod.notify_actions = blc_notify_actions;
	blc.mod.notify_actions_num = ARRAY_SIZE(blc_notify_actions);
	return isp_mod_register(&blc.mod);
}

void isp_unregister_mod_blc(void)
{
	isp_mod_unregister(&blc.mod);
}

