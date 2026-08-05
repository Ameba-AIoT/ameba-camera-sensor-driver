/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2021 Mike Wong <mike.wong@realtek.com>
 */

#include "rts_isp.h"
#include <isp_utils.h>
#include <isp_notify.h>
#include <isp_mod.h>
#include <isp_iq.h>
#include <isp_mod_snr.h>
#include <isp_mod_sensor.h>
#include <isp_hw_snr.h>
#include <string.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_SNR

struct isp_mod_snr {
	struct isp_mod mod;
	const struct isp_hw_snr_ops *hw_ops;
	const isp_iq_snr_t *iq;

	isp_algo_param_snr_t *param;

	isp_iq_snr_item_t current;
	isp_iq_snr_item_t target;
	uint8_t force_update;
	enum rts_isp_dynamic_iq_mode dyn_iq_mode;
};

static int isp_mod_snr_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_snr *snr;

	snr = get_mod(mod, snr);
	snr->hw_ops = isp_hw_snr_get_ops();
	if (snr->hw_ops == NULL) {
		isp_error("get snr hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	snr->param = &isp_iq_get_algo_param(mod->owner_id)->snr;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_snr_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static void calc_smooth_snr_adj(isp_iq_snr_item_t *cur,
				   const isp_iq_snr_item_t *target)
{
	const int max = 16;
	const int div = 8;

	cur->offset = calc_smooth(cur->offset, target->offset, div, max);
	cur->ratio = calc_smooth(cur->ratio, target->ratio, div, max);
}

static int __mod_snr_set(struct isp_mod *mod)
{
	struct isp_mod_snr *snr = get_mod(mod, snr);

	return snr->hw_ops->set(mod->owner_id, &snr->current);
}

static int check_snr_iq(const isp_iq_snr_t *iq)
{
	if (!iq)
		return -RTS_ISP_ENOITEM;

	if (isp_iq_check_bounds(&iq->dyn_gain.bounds,
				iq->dyn_gain.gain_items_count))
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_snr_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_snr *snr = get_mod(mod, snr);

	ret = snr->hw_ops->estimation(mod->owner_id);
	if (ret)
		return ret;

	if (!snr->force_update && memcmp(&snr->current, &snr->target, sizeof(snr->current)) == 0)
		return RTS_ISP_OK;

	snr->force_update = RTS_ISP_FALSE;
	if (snr->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		calc_smooth_snr_adj(&snr->current, &snr->target);
	else
		memcpy(&snr->current, &snr->target, sizeof(snr->current));

	return __mod_snr_set(mod);
}

static int mod_snr_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_snr *snr = get_mod(mod, snr);
	const isp_iq_snr_t *iq;
	int dyn_enable;

	snr->iq = isp_iq_get_snr(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_snr_iq(snr->iq))
		return -RTS_ISP_EINVAL;

	iq = snr->iq;
	snr->param->gain_index = iq->dyn_gain.bounds.def_index;
	snr->current = iq->dyn_gain.gain_items[snr->param->gain_index];
	snr->target = iq->dyn_gain.gain_items[snr->param->gain_index];

	ret = __mod_snr_set(mod);
	if (ret)
		return ret;
	dyn_enable = (iq->dyn_gain.enable);

	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static void intp_snr_target(isp_iq_snr_item_t *items, uint32_t dyn_value,
				uint32_t bound0, const isp_iq_snr_item_t *items0,
				uint32_t bound1, const isp_iq_snr_item_t *items1)
{
	if (!items || !items0 || !items1)
		return;

	items->offset = linear_intp(dyn_value,
					bound0, items0->offset,
					bound1, items1->offset);

	items->ratio = linear_intp(dyn_value,
					bound0, items0->ratio,
					bound1, items1->ratio);
}

static int snr_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_snr_item_t *items)
{
	struct isp_mod_snr *snr = get_mod(mod, snr);

	if (index == 0) {
		snr->target = items[index];
	} else if (index == bounds->bounds_count) {
		snr->target = items[index - 1];
	} else {
		intp_snr_target(&snr->target, dyn_value,
				bounds->bounds[index - 1], &items[index - 1],
				bounds->bounds[index], &items[index]);
	}

	return RTS_ISP_OK;
}

static int mod_snr_dynamic(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_snr *snr = get_mod(mod, snr);
	struct isp_notify_dynamic *dyn = data;
	const isp_iq_snr_t *iq = snr->iq;
	uint32_t dyn_value;

	snr->force_update = RTS_ISP_TRUE;
	snr->dyn_iq_mode = dyn->dyn_mode;

	//AE info from short exposure path
	if (iq->dyn_gain.based_on_et_gain)
		dyn_value = ((uint32_t)(dyn->ae.exposure[1] * dyn->ae.total_gain[1] / 100));
	else
		dyn_value = ((uint32_t)(dyn->ae.total_gain[1] * 16));

	snr->param->gain_index =
		isp_iq_get_bound(&iq->dyn_gain.bounds, dyn_value);

	snr_intp_target(mod, dyn_value, snr->param->gain_index,
		&iq->dyn_gain.bounds, iq->dyn_gain.gain_items);

	if (snr->dyn_iq_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING ||
		memcmp(&snr->current, &snr->target, sizeof(snr->current)) == 0)
		return RTS_ISP_OK;

	snr->force_update = RTS_ISP_FALSE;

	ret = snr->hw_ops->estimation(mod->owner_id);
	if (ret)
		return ret;

	memcpy(&snr->current, &snr->target, sizeof(snr->current));
	return __mod_snr_set(mod);
}

static struct isp_mod_action_info snr_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_snr_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_snr_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_snr_dynamic),
};

static struct isp_mod_snr snr;

int isp_register_mod_snr(void)
{
	memset(&snr, 0, sizeof(snr));
	snr.mod.id = MOD_SNR;
	snr.mod.name = "snr";
	snr.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_STATIS_DONE_BIT;
	snr.mod.init = isp_mod_snr_init;
	snr.mod.cleanup = isp_mod_snr_cleanup;
	snr.mod.notify_actions = snr_notify_actions;
	snr.mod.notify_actions_num = ARRAY_SIZE(snr_notify_actions);
	return isp_mod_register(&snr.mod);
}

void isp_unregister_mod_snr(void)
{
	isp_mod_unregister(&snr.mod);
}

