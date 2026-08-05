/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include "isp_mem.h"
#include "rts_isp.h"
#include <isp_mod.h>
#include <isp_iq.h>
#include <isp_notify.h>
#include <isp_mod_ygc.h>
#include <isp_mod_sensor.h>
#include <isp_hw_ygc.h>
#include <string.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_YGC

struct isp_mod_ygc {
	struct isp_mod mod;
	const struct isp_hw_ygc_ops *hw_ops;
	const isp_iq_ygc_t *iq;

	uint8_t force_update;
	enum rts_isp_sensor_hdr_mode hdr_mode;
	enum rts_isp_dynamic_iq_mode dyn_iq_mode;

	isp_algo_param_ygc_t *param;

	isp_iq_ygc_item_t current;
	isp_iq_ygc_item_t target;
};

static int check_ygc_iq(const isp_iq_ygc_t *iq)
{
	int i, j;

	if (!iq)
		return -RTS_ISP_ENOITEM;
	//isp_info("%s dyn_gain enable %d gain_items_count %d based_on_et_gain %d\r\n", __func__,  iq->dyn_gain.enable, iq->dyn_gain.gain_items_count, iq->dyn_gain.based_on_et_gain);
	if (isp_iq_check_bounds(&iq->dyn_ratio.bounds,
				iq->dyn_ratio.ratio_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ratio.ratio_items_count; i++) {
		if (isp_iq_check_bounds(&iq->dyn_ratio.ratio_items[i].bounds,
				iq->dyn_ratio.ratio_items[i].gain_items_count))
			return -RTS_ISP_EINVAL;

		// each ygc curve should have 63 items.
		for (j = 0; j < iq->dyn_ratio.ratio_items[i].gain_items_count; j++)
			if (iq->dyn_ratio.ratio_items[i].gain_items[j].curve_count != 63)
				return -RTS_ISP_EINVAL;
	}

	//isp_info("%s dyn_ht enable %d items_count %d based_on_et_gain %d\r\n", __func__,  iq->dyn_ht.enable, iq->dyn_ht.items_count, iq->dyn_ht.based_on_gain);

	if (iq->dyn_ht.enable &&
	    isp_iq_check_bounds(&iq->dyn_ht.bounds, iq->dyn_ht.items_count))
		return -RTS_ISP_EINVAL;
	for (i = 1; i < iq->dyn_ht.items_count; i++)
		if (iq->dyn_ht.items[i].curve_count !=
		    iq->dyn_ht.items[0].curve_count) {
			isp_error("%s dyn_ht.items0 %d dyn_ht.items%d %d  \r\n", __func__,  (int)iq->dyn_ht.items[0].curve_count, i, (int)iq->dyn_ht.items[i].curve_count);
			return -RTS_ISP_EINVAL;
	}


	return RTS_ISP_OK;
}

static int ygc_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_ygc_item_t *items)
{
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);

	if (index == 0)
		isp_memcpy_array(ygc->target.curve, items[index].curve,
				 ygc->target.curve_count);
	else if (index == bounds->bounds_count)
		isp_memcpy_array(ygc->target.curve, items[index - 1].curve,
				 ygc->target.curve_count);
	else
		linear_intp_array(ygc->target.curve, dyn_value,
				  bounds->bounds[index - 1],
				  items[index - 1].curve,
				  bounds->bounds[index], items[index].curve,
				  ygc->target.curve_count);
	return RTS_ISP_OK;
}

static int mod_ygc_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);

	if (!ygc->force_update &&
		isp_memcmp_array(ygc->current.curve, ygc->target.curve,
			     ygc->current.curve_count) == 0)
		return RTS_ISP_OK;

	ygc->force_update = RTS_ISP_FALSE;
	if (ygc->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		calc_smooth_array(ygc->current.curve, ygc->target.curve, 8, 128,
				  ygc->current.curve_count);
	else
		isp_memcpy_array(ygc->current.curve, ygc->target.curve,
			     ygc->current.curve_count);
	//isp_info("%s \r\n",__func__);
	return ygc->hw_ops->set_ygc(mod->owner_id, &ygc->current);
}

static int mod_ygc_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);
	const isp_iq_ygc_t *iq;
	const isp_iq_ygc_item_t *ygc_item;
	const isp_iq_ygc_ratio_item_t *ratio_item;
	int dyn_enable;

	ygc->iq = isp_iq_get_ygc(mod->owner_id);

	//return 0; //[Workaround] for IQ load

	if (check_ygc_iq(ygc->iq)) {
		isp_error("%s check_ygc_iq failed\r\n", __func__);
		return -RTS_ISP_EINVAL;
	}

	iq = ygc->iq;

	if (ygc->hdr_mode == LINEAR_MODE)
		ygc->param->ratio_index = 0;
	else
		ygc->param->ratio_index = iq->dyn_ratio.bounds.def_index;

	ratio_item = &iq->dyn_ratio.ratio_items[ygc->param->ratio_index];
	ygc->param->gain_index = ratio_item->bounds.def_index;
	ygc_item = &ratio_item->gain_items[ygc->param->gain_index];

	isp_free(ygc->current.curve);
	isp_free(ygc->target.curve);
	ygc->current.curve_count = ygc_item->curve_count;
	ygc->target.curve_count = ygc_item->curve_count;
	if (!isp_calloc_array(ygc->current.curve, ygc->current.curve_count)) {
		isp_error("%s isp_calloc_array current failed\r\n", __func__);
		return -RTS_ISP_ENOMEM;
	}

	if (!isp_calloc_array(ygc->target.curve, ygc->target.curve_count)) {
		isp_error("%s isp_calloc_array target failed\r\n", __func__);
		isp_free(ygc->current.curve);
		return -RTS_ISP_ENOMEM;
	}
	isp_memcpy_array(ygc->current.curve,
			 ygc_item->curve, ygc_item->curve_count);
	isp_memcpy_array(ygc->target.curve,
			 ygc_item->curve, ygc_item->curve_count);

	ret = ygc->hw_ops->set_ygc(mod->owner_id, &ygc->current);
	if (ret) {
		isp_error("%s set_ygc failed %d \r\n", __func__, ret);
		return ret;
	}

	dyn_enable = iq->dyn_gain.enable ||
				 iq->dyn_ratio.enable || iq->dyn_ht.enable;
	//isp_info("%s done \r\n", __func__);
	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static int mod_ygc_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);
	const struct isp_notify_dynamic *dyn = data;
	const isp_iq_ygc_t *iq = ygc->iq;
	const isp_iq_ygc_ratio_item_t *ratio_item;

	ygc->force_update = RTS_ISP_TRUE;
	ygc->dyn_iq_mode = dyn->dyn_mode;

	if (iq->dyn_ht.enable && dyn->sensor.high_temp_en) {
		uint32_t dyn_value;

		if (iq->dyn_ht.based_on_gain)
			dyn_value = dyn->ae.gain;
		else
			dyn_value = dyn->sensor.temperature;
		ygc->param->ht_index =
			isp_iq_get_bound(&iq->dyn_ht.bounds, dyn_value);
		ygc_intp_target(mod, dyn_value, ygc->param->ht_index,
			&iq->dyn_ht.bounds, iq->dyn_ht.items);

		goto SET_YGC;
	}

	if (iq->dyn_ratio.enable) {
		ygc->param->ratio_index = isp_iq_get_bound(
			&iq->dyn_ratio.bounds, dyn->ae.iq_ratio[1]
		);
		ygc->param->ratio_index =
			(ygc->param->ratio_index ==
			 iq->dyn_ratio.bounds.bounds_count) ?
				ygc->param->ratio_index - 1 :
				ygc->param->ratio_index;
	}

	ratio_item = &iq->dyn_ratio.ratio_items[ygc->param->ratio_index];

	if (iq->dyn_gain.enable) {
		uint32_t dyn_value;
		if (ratio_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;
		ygc->param->gain_index =
		isp_iq_get_bound(&ratio_item->bounds, dyn_value);

		ygc_intp_target(mod, dyn_value, ygc->param->gain_index,
			&ratio_item->bounds, ratio_item->gain_items);
	} else {
		ygc->param->gain_index = ratio_item->bounds.def_index;
		ygc->target = ratio_item->gain_items[ygc->param->gain_index];
	}

SET_YGC:
	if (ygc->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		isp_memcmp_array(ygc->current.curve, ygc->target.curve,
			ygc->current.curve_count) == 0)
		return RTS_ISP_OK;

	ygc->force_update = RTS_ISP_FALSE;
	isp_memcpy_array(ygc->current.curve, ygc->target.curve,
		ygc->current.curve_count);
	return ygc->hw_ops->set_ygc(mod->owner_id, &ygc->current);
}

static int mod_ygc_hdr_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_sensor_mode mode = {
		.hdr = LINEAR_MODE,
	};
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
								   &mode, sizeof(mode));
	if (ret)
		return ret;

	ygc->hdr_mode = mode.hdr;
	return RTS_ISP_OK;
}

static struct isp_mod_action_info ygc_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_ygc_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_ygc_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_ygc_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_ygc_hdr_mode_change),
};

static int isp_mod_ygc_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_ygc *ygc;

	ygc = get_mod(mod, ygc);
	ygc->hw_ops = isp_hw_ygc_get_ops();
	if (ygc->hw_ops == NULL) {
		isp_error("get ygc hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	ygc->param = &isp_iq_get_algo_param(mod->owner_id)->ygc;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_ygc_cleanup(struct isp_mod *mod)
{
	struct isp_mod_ygc *ygc = get_mod(mod, ygc);

	isp_free(ygc->current.curve);
	isp_free(ygc->target.curve);
	return RTS_ISP_OK;
}

static int isp_mod_ygc_add_ctrl(struct isp_mod *mod, void *phandler)
{
	return RTS_ISP_OK;
}

static struct isp_mod_ygc ygc;

int isp_register_mod_ygc(void)
{
	memset(&ygc, 0, sizeof(ygc));
	ygc.mod.id = MOD_YGC;
	ygc.mod.name = "ygc";
	ygc.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_HDR_MODE_CHANGE_BIT;
	ygc.mod.init = isp_mod_ygc_init;
	ygc.mod.cleanup = isp_mod_ygc_cleanup;
	ygc.mod.add_ctrl = isp_mod_ygc_add_ctrl;
	ygc.mod.notify_actions = ygc_notify_actions;
	ygc.mod.notify_actions_num = ARRAY_SIZE(ygc_notify_actions);
	return isp_mod_register(&ygc.mod);
}

void isp_unregister_mod_ygc(void)
{
	isp_mod_unregister(&ygc.mod);
}
