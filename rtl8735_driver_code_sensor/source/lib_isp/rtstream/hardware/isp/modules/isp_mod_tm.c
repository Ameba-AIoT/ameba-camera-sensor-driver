/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2021 Mike Wong <mike.wong@realtek.com>
 */

#include "rts_isp.h"
#include <isp_utils.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod_sensor.h>
#include <isp_mod_tm.h>
#include <isp_hw_tm.h>
#include <string.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_TM

struct isp_mod_tm {
	struct isp_mod mod;
	const struct isp_hw_tm_ops *hw_ops;
	const isp_iq_tm_t *iq;

	isp_algo_param_tm_t *param;

	isp_iq_tm_item_t current;
	isp_iq_tm_item_t target;

	uint8_t force_update;
	enum rts_isp_dynamic_iq_mode dyn_iq_mode;

	enum rts_isp_sensor_hdr_mode hdr_mode;
};

static int isp_mod_tm_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_tm *tm;

	tm = get_mod(mod, tm);
	tm->hw_ops = isp_hw_tm_get_ops();
	if (tm->hw_ops == NULL) {
		isp_error("get tm hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	tm->param = &isp_iq_get_algo_param(mod->owner_id)->tm;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_tm_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int check_tm_iq(const isp_iq_tm_t *iq)
{
	if (!iq)
		return -RTS_ISP_ENOITEM;

	if (isp_iq_check_bounds(&iq->dyn_gain.bounds,
				iq->dyn_gain.gain_items_count))
		return -RTS_ISP_EINVAL;

	if (iq->dyn_ht.enable &&
		isp_iq_check_bounds(&iq->dyn_ht.bounds, iq->dyn_ht.items_count))
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_tm_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_tm *tm = get_mod(mod, tm);

	if (tm->hdr_mode != HDR_MODE)
		return 0;
	if (!tm->force_update &&
	    memcmp(&tm->current, &tm->target, sizeof(tm->current)) == 0)
		return RTS_ISP_OK;

	tm->force_update = RTS_ISP_FALSE;

	if (tm->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING) {
		tm->current.value = calc_smooth_float(tm->current.value,
							tm->target.value, 8.0f, 0.5f);

		calc_smooth_array(tm->current.long_luma_thd, tm->target.long_luma_thd,
				16, 32, ARRAY_SIZE(tm->current.long_luma_thd));

		calc_smooth_array(tm->current.short_luma_thd, tm->target.short_luma_thd,
				16, 32, ARRAY_SIZE(tm->current.short_luma_thd));
	} else {
		memcpy(&tm->current, &tm->target, sizeof(tm->current));
	}


	ret = tm->hw_ops->set_target(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_long(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_short(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_param(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	return RTS_ISP_OK;
}

static int mod_tm_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_tm *tm = get_mod(mod, tm);
	const isp_iq_tm_t *iq;
	int dyn_enable;

	tm->iq = isp_iq_get_tm(mod->owner_id);
	if (tm->hdr_mode != HDR_MODE)
		return 0;
	ret = check_tm_iq(tm->iq);
	if(ret)
		return ret;

	iq = tm->iq;
	tm->param->gain_index = iq->dyn_gain.bounds.def_index;
	tm->current = iq->dyn_gain.gain_items[tm->param->gain_index];
	tm->target = iq->dyn_gain.gain_items[tm->param->gain_index];

	ret = tm->hw_ops->set_target(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_long(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_short(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_param(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	dyn_enable = iq->dyn_gain.enable || iq->dyn_ht.enable;

	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static void intp_tm_target(isp_iq_tm_item_t *item, uint32_t dyn_value,
			   uint32_t bound0, const isp_iq_tm_item_t *item0,
			   uint32_t bound1, const isp_iq_tm_item_t *item1)
{
	if (!item || !item0 || !item1)
		return;

	item->value = linear_intp_float(dyn_value, bound0, item0->value, bound1,
				     item1->value);

	item->long_luma_offset =
		linear_intp(dyn_value, bound0, item0->long_luma_offset, bound1,
			    item1->long_luma_offset);

	item->short_luma_offset =
		linear_intp(dyn_value, bound0, item0->short_luma_offset, bound1,
			    item1->short_luma_offset);

	item->direct_factor_k0 =
		linear_intp(dyn_value, bound0, item0->direct_factor_k0, bound1,
			    item1->direct_factor_k0);
	item->direct_factor_k1 =
		linear_intp(dyn_value, bound0, item0->direct_factor_k1, bound1,
			    item1->direct_factor_k1);
	item->direct_factor_k2 =
		linear_intp(dyn_value, bound0, item0->direct_factor_k2, bound1,
			    item1->direct_factor_k2);
	item->direct_weight_w0 =
		linear_intp(dyn_value, bound0, item0->direct_weight_w0, bound1,
			    item1->direct_weight_w0);
	item->direct_weight_w1 =
		linear_intp(dyn_value, bound0, item0->direct_weight_w1, bound1,
			    item1->direct_weight_w1);
	item->rate_max = linear_intp(dyn_value, bound0, item0->rate_max, bound1,
				     item1->rate_max);
	item->rate_min = linear_intp(dyn_value, bound0, item0->rate_min, bound1,
				     item1->rate_min);

	linear_intp_array(item->short_luma_thd, dyn_value, bound0,
			  item0->short_luma_thd, bound1, item1->short_luma_thd,
			  ARRAY_SIZE(item->short_luma_thd));

	linear_intp_array(item->long_luma_thd, dyn_value, bound0,
			  item0->long_luma_thd, bound1, item1->long_luma_thd,
			  ARRAY_SIZE(item->long_luma_thd));
}

static int tm_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_tm_item_t *value)
{
	struct isp_mod_tm *tm = get_mod(mod, tm);

	if (index == 0) {
		tm->target = value[index];
	} else if (index == bounds->bounds_count) {
		tm->target = value[index - 1];
	} else {
		intp_tm_target(&tm->target, dyn_value,
				bounds->bounds[index - 1], &value[index - 1],
				bounds->bounds[index], &value[index]);
	}

	return RTS_ISP_OK;
}

static int mod_tm_dynamic(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_tm *tm = get_mod(mod, tm);
	struct isp_notify_dynamic *dyn = data;
	const isp_iq_tm_t *iq = tm->iq;
	uint32_t dyn_value;

	tm->force_update = RTS_ISP_TRUE;
	tm->dyn_iq_mode = dyn->dyn_mode;
	if (tm->hdr_mode != HDR_MODE)
		return 0;

	if (iq->dyn_ht.enable && dyn->sensor.high_temp_en) {
		if (iq->dyn_ht.based_on_gain)
			dyn_value = dyn->ae.gain;
		else
			dyn_value = dyn->sensor.temperature;
		tm->param->ht_index =
			isp_iq_get_bound(&iq->dyn_ht.bounds, dyn_value);
		tm_intp_target(mod, dyn_value, tm->param->ht_index,
			&iq->dyn_ht.bounds, iq->dyn_ht.items);

		goto SET_TM;
	}

	if (iq->dyn_gain.based_on_et_gain)
		dyn_value = dyn->ae.exp_gain;
	else
		dyn_value = dyn->ae.gain;
	tm->param->gain_index =
		isp_iq_get_bound(&iq->dyn_gain.bounds, dyn_value);

	tm_intp_target(mod, dyn_value, tm->param->gain_index,
		&iq->dyn_gain.bounds, iq->dyn_gain.gain_items);

SET_TM:
	if (tm->hdr_mode != HDR_MODE ||
		tm->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		memcmp(&tm->current, &tm->target, sizeof(tm->current)) == 0)
		return RTS_ISP_OK;

	tm->force_update = RTS_ISP_FALSE;
	memcpy(&tm->current, &tm->target, sizeof(tm->current));

	ret = tm->hw_ops->set_target(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_long(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_thd_short(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	ret = tm->hw_ops->set_edge_param(mod->owner_id, &tm->current);
	if (ret) {
		return ret;
	}

	return ret;
}

static int mod_tm_hdr_mode_change(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_tm *tm = get_mod(mod, tm);
	struct isp_sensor_mode mode = {
		.hdr = LINEAR_MODE,
	};

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
					   &mode, sizeof(mode));
	if (ret)
		goto err;

	tm->hdr_mode = mode.hdr;

	if(tm->hw_ops->set_enable) {
		tm->hw_ops->set_enable(mod->owner_id, (tm->hdr_mode==HDR_MODE));
	}
	return ret;

	err:
	isp_error("Tone Mapping mode change err %d \n",	ret);
	return ret;
}

static struct isp_mod_action_info tm_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_tm_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_tm_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_tm_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_tm_hdr_mode_change),
};

static struct isp_mod_tm tm;

int isp_register_mod_tm(void)
{
	memset(&tm, 0, sizeof(tm));
	tm.mod.id = MOD_TM;
	tm.mod.name = "tm";
	tm.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_HDR_MODE_CHANGE_BIT;
	tm.mod.init = isp_mod_tm_init;
	tm.mod.cleanup = isp_mod_tm_cleanup;
	tm.mod.notify_actions = tm_notify_actions;
	tm.mod.notify_actions_num = ARRAY_SIZE(tm_notify_actions);
	return isp_mod_register(&tm.mod);
}

void isp_unregister_mod_tm(void)
{
	isp_mod_unregister(&tm.mod);
}

