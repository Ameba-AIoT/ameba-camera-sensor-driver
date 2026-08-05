/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2022 Ian Tsai <ian.ys_tsai@realtek.com>
 */

#include <isp_top.h>
#include <isp_core.h>
#include <isp_statis.h>
#include <isp_notify.h>
#include <isp_mod.h>
#include <isp_core.h>
#include <isp_mod_md.h>
#include <isp_mod_iq.h>
#include <isp_hw_md.h>
#include <rts_isp_md_algo.h>
#include <isp_iq.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_MD

struct isp_mod_md {
	struct isp_mod mod;
	const struct isp_hw_md_ops *hw_ops;
	const struct rts_isp_md_algo *algo;
	uint16_t md_val;
	const isp_iq_md_t *iq;
	isp_algo_param_md_t *algo_param;

	isp_iq_md_item_t current;
	isp_iq_md_item_t target;
};

static int md_algo_set_ctrls(struct isp_mod_md *md);

static int check_algo_version(uint32_t version)
{
	if (algo_magic(version) != MD_API_VERSION_MAGIC ||
	    algo_major_version(version) != MD_API_MAJOR_VERSION ||
	    algo_minor_version(version) > 0)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_algo(const struct rts_isp_md_algo *md_algo)
{
	if (!md_algo || check_algo_version(md_algo->api_version))
		return -RTS_ISP_EINVAL;
	printf("md ver 0x%08x \n",md_algo->api_version);
	if (!md_algo->init || !md_algo->cleanup)
		return -RTS_ISP_EINVAL;
	if (!md_algo->run || !md_algo->ctrl)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int md_algo_prepare_info(struct isp_mod_md *md,
				struct rts_isp_algo_md_init_info *info)
{
	uint16_t ae_win_num, awb_win_num;

	info->iq = md->iq;
	info->algo_param = md->algo_param;


	md->hw_ops->get_win_num(md->mod.owner_id, &ae_win_num, &awb_win_num);
	info->win_num_info.ae_win_num = ae_win_num;
	info->win_num_info.awb_win_num = awb_win_num;

	return RTS_ISP_OK;
}

static int md_algo_init(struct isp_mod_md *md)
{
	int ret;
	struct rts_isp_algo_md_init_info info;

	ret = isp_algo_get_md(isp_top_get_algom(), md->mod.owner_id, &md->algo);
	if (ret)
		return ret;

	ret = check_algo(md->algo);
	if (ret)
		return ret;
	ret = md_algo_prepare_info(md, &info);

	if (ret)
		return ret;

	return md->algo->init(md->mod.owner_id, &info);
}

static int md_algo_cleanup(struct isp_mod_md *md)
{
	if (md->algo) {
		md->algo->cleanup(md->mod.owner_id);
		md->algo = NULL;
	}
	return RTS_ISP_OK;
}

static int md_algo_update(struct isp_mod_md *md)
{
	int ret;

	ret = md_algo_cleanup(md);
	if (ret)
		return ret;
	ret = md_algo_init(md);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

static int isp_mod_md_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_md *md;
	isp_algo_param_t *isp_algo;

	md = get_mod(mod, md);
	md->hw_ops = isp_hw_md_get_ops();
	if (md->hw_ops == NULL) {
		isp_error("get md hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	isp_algo = isp_iq_get_algo_param(mod->owner_id);
	if (!isp_algo) {
		isp_error("get ae algo param fail\n");
		return -RTS_ISP_EINVAL;
	}

	md->algo_param = &isp_algo->md;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_md_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_md_add_ctrl(struct isp_mod *mod, void *phandler)
{

	return RTS_ISP_OK;
}

static void calc_smooth_md_adj(isp_iq_md_item_t *cur,
				   const isp_iq_md_item_t *target)
{
	const int max = 16;
	const int div = 8;
	int i;

	for (i = 0; i < MD_MAX_TYPE; i++){
		cur->ratio[i] = calc_smooth(cur->ratio[i], target->ratio[i], div, max);
	}
}

static int mod_md_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_md *md = get_mod(mod, md);
	struct isp_notify_dynamic_md dyn_md;
	struct rts_isp_algo_md_result result;
	struct rts_isp_md_algo_statis statis;

	statis.ae_statis =&((const struct rts_isp_statis *)data)->ae;
	statis.awb_statis =&((const struct rts_isp_statis *)data)->awb;

	if (memcmp(&md->current, &md->target, sizeof(md->current)) != 0){
		calc_smooth_md_adj(&md->current, &md->target);

		ret = md_algo_set_ctrls(md);
		if (ret)
			return ret;
	}

	ret = md->algo->run(md->mod.owner_id, &statis, &result);
	if (ret)
		return ret;

	md->md_val = result.md_val;
	dyn_md.md_val = result.md_val;

	ret = isp_mod_sibling_execute(&md->mod, MOD_IQ, IQ_EXEC_SET_DYNAMIC_MD,
				       &dyn_md, sizeof(dyn_md));
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

static int mod_md_start_pre(struct isp_mod *mod, void *data)
{
	struct isp_mod_md *md = get_mod(mod, md);
	uint16_t ae_win_num, awb_win_num;

	return md->hw_ops->get_win_num(md->mod.owner_id, &ae_win_num,
				       &awb_win_num);
	// return RTS_ISP_OK;
}

static int mod_md_stop_pre(struct isp_mod *mod, void *data)
{
	return RTS_ISP_OK;
}

static int mod_md_algo_update(struct isp_mod *mod, void *data)
{
	struct isp_mod_md *md = get_mod(mod, md);
	uint32_t notify_data;

	notify_data = *(uint32_t *)data;
	if (!(notify_data & ISP_ALGO_MD_CHANGE_BIT))
		return RTS_ISP_OK;

	return md_algo_update(md);
}

static int check_md_iq(const isp_iq_md_t *iq)
{
	if (!iq)
		return -RTS_ISP_ENOITEM;

	if (isp_iq_check_bounds(&iq->dyn_gain.bounds,
				iq->dyn_gain.gain_items_count))
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_md_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_md *md = get_mod(mod, md);
	const isp_iq_md_t *iq;
	const isp_iq_md_item_t *items;
	int dyn_enable;

	md->iq = isp_iq_get_md(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_md_iq(md->iq))
		return -RTS_ISP_EINVAL;

	iq = md->iq;
	md->algo_param->gain_index = iq->dyn_gain.bounds.def_index;
	md->target = iq->dyn_gain.gain_items[md->algo_param->gain_index];
	md->current = iq->dyn_gain.gain_items[md->algo_param->gain_index];

	ret = md_algo_update(md);
	if (ret)
		return ret;

	ret = md_algo_set_ctrls(md);
	if (ret)
		return ret;

	dyn_enable = iq->dyn_gain.enable;

	return isp_mod_set_smooth_notify(mod, dyn_enable);
}

static void intp_md_target(isp_iq_md_item_t *items, uint32_t dyn_value,
				uint32_t bound0, const isp_iq_md_item_t *items0,
				uint32_t bound1, const isp_iq_md_item_t *items1)
{
	int i;

	if (!items || !items0 || !items1)
		return;

	for(i = 0; i < MD_MAX_TYPE; i++){
		items->ratio[i] = linear_intp(dyn_value,
						bound0, items0->ratio[i],
						bound1, items1->ratio[i]);
	}
}

static int md_intp_target(struct isp_mod *mod, int dyn_value, int index,
			   const isp_iq_bounds_t *bounds,
			   const isp_iq_md_item_t *items)
{
	struct isp_mod_md *md = get_mod(mod, md);

	if (index == 0) {
		md->target = items[index];
	} else if (index == bounds->bounds_count) {
		md->target = items[index - 1];
	} else {
		intp_md_target(&md->target, dyn_value,
				bounds->bounds[index - 1], &items[index - 1],
				bounds->bounds[index], &items[index]);
	}

	return RTS_ISP_OK;
}

static int mod_md_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_md *md = get_mod(mod, md);
	struct isp_notify_dynamic *dyn = data;
	const isp_iq_md_t *iq = md->iq;
	uint32_t dyn_value;

	if (iq->dyn_gain.based_on_et_gain)
		dyn_value = dyn->ae.exp_gain;
	else
		dyn_value = dyn->ae.gain;

	md->algo_param->gain_index =
		isp_iq_get_bound(&iq->dyn_gain.bounds, dyn_value);

	return md_intp_target(mod, dyn_value, md->algo_param->gain_index,
				 &iq->dyn_gain.bounds, iq->dyn_gain.gain_items);
}

static int md_algo_set_ctrls(struct isp_mod_md *md)
{
	int ret;

	if (!md->algo)
		return -RTS_ISP_ENOTREADY;

	ret = md->algo->ctrl(md->mod.owner_id, SET_RATIO, &md->target);

	return ret;
}

static struct isp_mod_action_info md_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_md_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_ALGO_UPDATE, mod_md_algo_update),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_md_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_START_PRE, mod_md_start_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_PRE, mod_md_stop_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_md_dynamic),
};

static struct isp_mod_md md;

int isp_register_mod_md(void)
{
	memset(&md, 0, sizeof(md));
	md.mod.id = MOD_MD;
	md.mod.name = "md";
	md.mod.notify_bits = ISP_ALGO_UPDATE_BIT | ISP_IQ_CHANGE_BIT |
			     ISP_STATIS_DONE_BIT | ISP_START_PRE_BIT |
			     ISP_STOP_PRE_BIT;
	md.mod.init = isp_mod_md_init;
	md.mod.cleanup = isp_mod_md_cleanup;
	md.mod.add_ctrl = isp_mod_md_add_ctrl;
	// md.mod.info_actions = md_info_actions;
	// md.mod.info_actions_num = ARRAY_SIZE(md_info_actions);
	md.mod.notify_actions = md_notify_actions;
	md.mod.notify_actions_num = ARRAY_SIZE(md_notify_actions);
	return isp_mod_register(&md.mod);
}

void isp_unregister_mod_md(void)
{
	isp_mod_unregister(&md.mod);
}
