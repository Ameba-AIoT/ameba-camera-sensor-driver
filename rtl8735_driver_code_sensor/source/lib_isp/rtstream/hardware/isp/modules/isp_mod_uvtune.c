/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_mod_uvtune.h>
#include <isp_hw_uvtune.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_UVTUNE

struct isp_mod_uvtune {
	struct isp_mod mod;
	const struct isp_hw_uvtune_ops *hw_ops;
	const isp_iq_uvtune_t *iq;

	isp_algo_param_uvtune_t *param;
	isp_iq_uvtune_item_t gain_item;
};

static int check_uvtune_iq(const isp_iq_uvtune_t *iq)
{
	int i;

	if (!iq)
		return -RTS_ISP_EINVAL;
	if (isp_iq_check_hysteresis_bounds(&iq->dyn_ct.bounds,
					   iq->dyn_ct.ct_items_count))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < iq->dyn_ct.ct_items_count; i++)
		if (isp_iq_check_bounds(&iq->dyn_ct.ct_items[i].bounds,
				iq->dyn_ct.ct_items[i].gain_items_count))
			return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mod_uvtune_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_uvtune *uvtune = get_mod(mod, uvtune);
	//isp_info("%s \r\n",__func__);
	return uvtune->hw_ops->estimation(mod->owner_id);
}

static int mod_uvtune_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_uvtune *uvtune = get_mod(mod, uvtune);
	const isp_iq_uvtune_t *iq;
	const isp_iq_uvtune_ct_item_t *ct_item;
	const isp_iq_uvtune_item_t *gain_item;

	uvtune->iq = isp_iq_get_uvtune(mod->owner_id);
	//return 0; //[Workaround] for IQ load
	if (check_uvtune_iq(uvtune->iq))
		return -RTS_ISP_EINVAL;
	iq = uvtune->iq;

	uvtune->param->ct_index = iq->dyn_ct.bounds.def_index;
	ct_item = &iq->dyn_ct.ct_items[uvtune->param->ct_index];
	uvtune->param->gain_index = ct_item->bounds.def_index;
	gain_item = &ct_item->gain_items[uvtune->param->gain_index];

	isp_free(uvtune->gain_item.mats);
	uvtune->gain_item.mats_count = gain_item->mats_count;
	if (!isp_calloc_array(uvtune->gain_item.mats,
			      uvtune->gain_item.mats_count))
		return -RTS_ISP_ENOMEM;
	isp_memcpy_array(uvtune->gain_item.mats, gain_item->mats,
			 gain_item->mats_count);

	uvtune->hw_ops->set_regs(mod->owner_id, &uvtune->gain_item);
	if (iq->dyn_ct.enable || iq->dyn_gain.enable)
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	else
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
	//isp_info("%s done \r\n", __func__);
	return ret;
}

static int mod_uvtune_dynamic(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_uvtune *uvtune = get_mod(mod, uvtune);
	const isp_iq_uvtune_t *iq = uvtune->iq;
	const isp_iq_uvtune_ct_item_t *ct_item;
	const struct isp_notify_dynamic *dyn = data;

	if (iq->dyn_ct.enable)
		uvtune->param->ct_index =
			isp_iq_get_hysteresis_bound(&iq->dyn_ct.bounds,
						    dyn->awb.color_temp,
						    uvtune->param->ct_index);
	ct_item = &iq->dyn_ct.ct_items[uvtune->param->ct_index];

	if (iq->dyn_gain.enable) {
		int index;
		uint32_t dyn_value;

		if (ct_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;

		index = isp_iq_get_bound(&ct_item->bounds, dyn_value);
		uvtune->param->gain_index = index;
		if (index == 0) {
			isp_memcpy_array(uvtune->gain_item.mats,
					 ct_item->gain_items[index].mats,
					 uvtune->gain_item.mats_count);
		} else if (index == ct_item->bounds.bounds_count) {
			isp_memcpy_array(uvtune->gain_item.mats,
					 ct_item->gain_items[index - 1].mats,
					 uvtune->gain_item.mats_count);
		} else {
			linear_intp_array(uvtune->gain_item.mats, dyn_value,
					  ct_item->bounds.bounds[index - 1],
					  ct_item->gain_items[index - 1].mats,
					  ct_item->bounds.bounds[index],
					  ct_item->gain_items[index].mats,
					  uvtune->gain_item.mats_count);
		}
	} else {
		uvtune->param->gain_index = ct_item->bounds.def_index;
		isp_memcpy_array(uvtune->gain_item.mats,
			ct_item->gain_items[uvtune->param->gain_index].mats,
			uvtune->gain_item.mats_count);
	}

	ret = uvtune->hw_ops->set_regs(mod->owner_id, &uvtune->gain_item);
	if (ret)
		return ret;

	if (dyn->dyn_mode == RTS_ISP_DYNAMIC_IQ_MODE_STEPPING)
		return RTS_ISP_OK;

	ret = uvtune->hw_ops->estimation(mod->owner_id);
	if (ret)
		return ret;

	return ret;

}

static struct isp_mod_action_info uvtune_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_uvtune_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_uvtune_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_uvtune_dynamic),
};

static int isp_mod_uvtune_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_uvtune *uvtune;

	uvtune = get_mod(mod, uvtune);
	uvtune->hw_ops = isp_hw_uvtune_get_ops();
	if (uvtune->hw_ops == NULL) {
		isp_error("get uvtune hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	uvtune->param = &isp_iq_get_algo_param(mod->owner_id)->uvtune;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_uvtune_cleanup(struct isp_mod *mod)
{
	struct isp_mod_uvtune *uvtune = get_mod(mod, uvtune);

	isp_free(uvtune->gain_item.mats);
	return RTS_ISP_OK;
}

static struct isp_mod_uvtune uvtune;

int isp_register_mod_uvtune(void)
{
	memset(&uvtune, 0, sizeof(uvtune));
	uvtune.mod.id = MOD_UVTUNE;
	uvtune.mod.name = "uvtune";
	uvtune.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_STATIS_DONE_BIT;
	uvtune.mod.init = isp_mod_uvtune_init;
	uvtune.mod.cleanup = isp_mod_uvtune_cleanup;
	uvtune.mod.notify_actions = uvtune_notify_actions;
	uvtune.mod.notify_actions_num = ARRAY_SIZE(uvtune_notify_actions);
	return isp_mod_register(&uvtune.mod);
}

void isp_unregister_mod_uvtune(void)
{
	isp_mod_unregister(&uvtune.mod);
}

