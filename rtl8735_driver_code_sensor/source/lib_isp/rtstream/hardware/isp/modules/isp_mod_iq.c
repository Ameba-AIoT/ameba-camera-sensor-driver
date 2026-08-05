/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <strings.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <rts_isp.h>
#include <rts_isp_patch.h>
#include <isp_top.h>
#include <isp_poll.h>
#include <isp_core.h>
#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_shm.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_vctrl.h>
#include <isp_mod_ae.h>
#include <isp_mod_awb.h>
#include <isp_mod_af.h>
#include <isp_mod_sensor.h>
#include <isp_mod_iq.h>
#include <isp_hw_iq.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_IQ

#define DYNAMIC_IQ_TIMER_INTERVAL 100
static struct isp_mod_iq iq;

char TUNING_PARAM_SHM_NAME[] = "/isp_tuning_param.shm";
char TUNING_IQ_TABLE_SHM_NAME[] = "/isp_iq_tuning.shm";

struct isp_mod_iq {
	struct isp_mod mod;
	struct isp_iq *man;
	struct {
		struct v4l2_ctrl *day_night_ctrl;
		struct v4l2_ctrl *iq_ctrl;
		const char *iq_menu[_MAX_ISP_IQ_NUM];
	};
	struct v4l2_ctrl *dyn_iq_ctrl;
	struct v4l2_ctrl *nr_level_ctrl;
	struct v4l2_ctrl *de_level_ctrl;
	struct v4l2_ctrl *dyn_iq_mode_ctrl;

	const isp_iq_texture_t *iq;

	isp_timer_handle_t timer;
	struct isp_notify_dynamic dynamic;
	struct isp_notify_dynamic notified_dynamic;

	struct isp_shm tuning_shm;
	void *iq_backup;

	const struct isp_hw_iq_ops *hw_ops;

	struct isp_shm algo_param_shm;
	isp_algo_param_t *algo_param;

	const struct rts_isp_sensor_patch_ops *patch_ops;
};

static int apply_iq_table(struct isp_mod *mod,
			  uint32_t day_night, uint32_t target_id);

static int mod_iq_info_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	*(struct isp_notify_dynamic **)data = &iq->dynamic;
	return RTS_ISP_OK;
}

static int mod_iq_info_iq_sel(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (iq->iq_ctrl)
		*(int *)data = iq->iq_ctrl->val;
	else
		*(int *)data = 0;

	return RTS_ISP_OK;
}

static int mod_iq_info_packed_iq(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct isp_packed_iq_info *info = data;

	info->bfr = iq->man->bfr;
	return RTS_ISP_OK;
}

static int mod_iq_info_plugins_version(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct rts_isp_plugins_version *version = data;

	memset(version, 0, sizeof(*version));
	ret = isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_VERSION,
				       &version->ae_api_version,
				       sizeof(version->ae_api_version));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_AWB, AWB_INFO_VERSION,
				       &version->awb_api_version,
				       sizeof(version->awb_api_version));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_AF, AF_INFO_VERSION,
				       &version->af_api_version,
				       sizeof(version->af_api_version));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_VERSION,
				       &version->sensor_api_version,
				       sizeof(version->sensor_api_version));
	if (ret)
		return ret;
	if (iq->man && iq->man->iq_table) {
		version->iq_pack_version = (iq->man->packed_version.major << 16) | (iq->man->packed_version.minor);
		version->iq_proto_version = iq->man->iq_table->header->version;
		version->iq_customer_version = iq->man->cus_version;
	} else {
		version->iq_pack_version = 0;
		version->iq_proto_version = 0;
		version->iq_customer_version = 0;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_action_info iq_info_actions[] = {
	ISP_MOD_ACTION(IQ_INFO_DYNAMIC, mod_iq_info_dynamic),
	ISP_MOD_ACTION(IQ_INFO_IQ_SEL, mod_iq_info_iq_sel),
	ISP_MOD_ACTION(IQ_INFO_PACKED_IQ, mod_iq_info_packed_iq),
	ISP_MOD_ACTION(IQ_INFO_PLUGINS_VERSION, mod_iq_info_plugins_version),
};

static void iq_reset_notified_value(struct isp_mod_iq *iq)
{
	memset(&iq->notified_dynamic, 0, sizeof(iq->notified_dynamic));
}

static int check_static_iq(const isp_iq_texture_static_t *static_regs)
{

	if (static_regs->offsets_count != static_regs->values_count)
	{
		isp_error("%s %d %d \r\n", __func__, (int)static_regs->offsets_count, (int)static_regs->values_count);
		return -RTS_ISP_EINVAL;
	}


	//for (int i = 0; i < static_regs->offsets_count; i++) {
	//	isp_info("%d 0x%08x 0x%08x \r\n", i, static_regs->offsets[i], static_regs->values[i]);
	//}
	//isp_info("%s %d \r\n", __func__, static_regs->offsets_count);
	return RTS_ISP_OK;
}

static int check_reg_offset_val(const isp_iq_texture_dynamic_value_t *value,
								const isp_iq_texture_dynamic_offset_t *offset)
{
		if (offset->discrete_offsets_count !=
		    value->discrete_values_count ||
		    offset->continuous_offsets_count !=
		    value->continuous_values_count ||
		    offset->nr_discrete_offsets_count !=
		    value->nr_discrete_values_count ||
		    offset->nr_continuous_offsets_count !=
		    value->nr_continuous_values_count ||
		    offset->de_discrete_offsets_count !=
		    value->de_discrete_values_count ||
		    offset->de_continuous_offsets_count !=
		    value->de_continuous_values_count ||
			offset->md_discrete_offsets_count !=
		    value->md_discrete_values_count ||
		    offset->md_continuous_offsets_count !=
			value->md_continuous_values_count ||
			value->md_ind_continuous_enable_count !=
			value->md_continuous_values_count ||
			value->md_ind_discrete_enable_count !=
			value->md_discrete_values_count)
				return -RTS_ISP_EINVAL;
		else
			return RTS_ISP_OK;
}

static int check_dynamic_ratio_iq(const isp_iq_texture_dyn_ratio_t *dyn_ratio)
{
	int i, j, ret;
	const isp_iq_texture_dynamic_offset_t *offset;
	const isp_iq_texture_dyn_ratio_item_t *ratio_item;
	offset = &dyn_ratio->offset;
	//isp_info("%s enable %d based_on_et_gain %d values_count %d continuous %d discrete %d\r\n", __func__, dynamic->enable, dynamic->based_on_et_gain, dynamic->values_count, offset->continuous_offsets_count,  offset->discrete_offsets_count);



	if (isp_iq_check_bounds(&dyn_ratio->bounds, dyn_ratio->ratio_items_count)) {
		return -RTS_ISP_EINVAL;
	}


	//isp_info("%s nr_discrete %d %d nr_continuous %d %d \r\n", __func__, offset->nr_discrete_offsets_count, offset->nr_discrete_levels_count,
	//offset->nr_continuous_offsets_count, offset->nr_continuous_levels_count);
	//isp_info("%s de_discrete %d %d de_continuous %d %d \r\n", __func__, offset->de_discrete_offsets_count, offset->de_discrete_levels_count,
	//offset->de_continuous_offsets_count, offset->de_continuous_levels_count);

	offset = &dyn_ratio->offset;
	if (offset->nr_discrete_offsets_count !=
	    offset->nr_discrete_levels_count ||
	    offset->nr_continuous_offsets_count !=
	    offset->nr_continuous_levels_count ||
	    offset->de_discrete_offsets_count !=
	    offset->de_discrete_levels_count ||
	    offset->de_continuous_offsets_count !=
	    offset->de_continuous_levels_count ||
		offset->md_discrete_offsets_count !=
		offset->md_discrete_levels_count ||
		offset->md_continuous_offsets_count !=
		offset->md_continuous_levels_count) {
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->nr_discrete_offsets_count, (int)offset->nr_discrete_levels_count,
				(int)offset->nr_continuous_offsets_count, (int)offset->nr_continuous_levels_count);
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->de_discrete_offsets_count, (int)offset->de_discrete_levels_count,
				(int)offset->de_continuous_offsets_count, (int)offset->de_continuous_levels_count);
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->md_discrete_offsets_count, (int)offset->md_discrete_levels_count,
				(int)offset->md_continuous_offsets_count, (int)offset->md_continuous_levels_count);
		return -RTS_ISP_EINVAL;
	}

	for (i = 0; i < dyn_ratio->ratio_items_count; i ++) {
		ratio_item = &dyn_ratio->ratio_items[i];
		if (isp_iq_check_bounds(&dyn_ratio->dyn_gain_bounds, ratio_item->gain_items_count)) {
			isp_error("ratio_items %d bounds check failed!\n", i);
			return -RTS_ISP_EINVAL;
		}
		for (j = 0; j < ratio_item->gain_items_count; j++) {
			const isp_iq_texture_dynamic_value_t *value =
				&ratio_item->gain_items[j];
			ret = check_reg_offset_val(value, offset);
			if (RTS_ISP_OK != ret) {
				isp_error(
					"%s [%d] discrete %d %d continuous %d %d nr_discrete %d %d\r\n",
					__func__, j, (int)offset->discrete_offsets_count,
					(int)value->discrete_values_count,
					(int)offset->continuous_offsets_count,
					(int)value->continuous_values_count,
					(int)offset->nr_discrete_offsets_count,
					(int)value->nr_discrete_values_count);
				isp_error("%s nr_continuous%d %d de_discrete%d %d de_continuous %d %d\r\n",
						__func__, (int)offset->nr_continuous_offsets_count, (int)value->nr_continuous_values_count,
						(int)offset->de_discrete_offsets_count, (int)value->de_discrete_values_count,
						(int)offset->de_continuous_offsets_count, (int)value->de_continuous_values_count);
				isp_error("%s md_ind_continuous_enable_count%d %d md_ind_discrete_enable_count%d %d\r\n",
						__func__, (int)value->md_ind_continuous_enable_count,  (int)value->md_continuous_values_count,
						(int)value->md_ind_discrete_enable_count, (int)value->md_discrete_values_count);
				return ret;
			}
		}
	}
	return RTS_ISP_OK;
}

static int check_dynamic_iq(const isp_iq_texture_dynamic_t *dynamic)
{
	int i, ret;
	const isp_iq_texture_dynamic_offset_t *offset;
	offset = &dynamic->offset;
	//isp_info("%s enable %d based_on_et_gain %d values_count %d continuous %d discrete %d\r\n", __func__, dynamic->enable, dynamic->based_on_et_gain, dynamic->values_count, offset->continuous_offsets_count,  offset->discrete_offsets_count);



	if (isp_iq_check_bounds(&dynamic->bounds, dynamic->values_count)) {
		return -RTS_ISP_EINVAL;
	}


	//isp_info("%s nr_discrete %d %d nr_continuous %d %d \r\n", __func__, offset->nr_discrete_offsets_count, offset->nr_discrete_levels_count,
	//offset->nr_continuous_offsets_count, offset->nr_continuous_levels_count);
	//isp_info("%s de_discrete %d %d de_continuous %d %d \r\n", __func__, offset->de_discrete_offsets_count, offset->de_discrete_levels_count,
	//offset->de_continuous_offsets_count, offset->de_continuous_levels_count);

	offset = &dynamic->offset;
	if (offset->nr_discrete_offsets_count !=
	    offset->nr_discrete_levels_count ||
	    offset->nr_continuous_offsets_count !=
	    offset->nr_continuous_levels_count ||
	    offset->de_discrete_offsets_count !=
	    offset->de_discrete_levels_count ||
	    offset->de_continuous_offsets_count !=
	    offset->de_continuous_levels_count ||
		offset->md_discrete_offsets_count !=
		offset->md_discrete_levels_count ||
		offset->md_continuous_offsets_count !=
		offset->md_continuous_levels_count) {
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->nr_discrete_offsets_count, (int)offset->nr_discrete_levels_count,
				(int)offset->nr_continuous_offsets_count, (int)offset->nr_continuous_levels_count);
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->de_discrete_offsets_count, (int)offset->de_discrete_levels_count,
				(int)offset->de_continuous_offsets_count, (int)offset->de_continuous_levels_count);
		isp_error("%s %d %d %d %d \r\n",
				__func__, (int)offset->md_discrete_offsets_count, (int)offset->md_discrete_levels_count,
				(int)offset->md_continuous_offsets_count, (int)offset->md_continuous_levels_count);
		return -RTS_ISP_EINVAL;
	}


	for (i = 0; i < dynamic->values_count; i++) {
		const isp_iq_texture_dynamic_value_t *value =
			&dynamic->values[i];
		ret = check_reg_offset_val(value, offset);
		if (RTS_ISP_OK != ret) {
			isp_error(
				"%s [%d] discrete %d %d continuous %d %d nr_discrete %d %d\r\n",
				__func__, i, (int)offset->discrete_offsets_count,
				(int)value->discrete_values_count,
				(int)offset->continuous_offsets_count,
				(int)value->continuous_values_count,
				(int)offset->nr_discrete_offsets_count,
				(int)value->nr_discrete_values_count);
			isp_error("%s nr_continuous%d %d de_discrete%d %d de_continuous %d %d\r\n",
					__func__, (int)offset->nr_continuous_offsets_count, (int)value->nr_continuous_values_count,
					(int)offset->de_discrete_offsets_count, (int)value->de_discrete_values_count,
					(int)offset->de_continuous_offsets_count, (int)value->de_continuous_values_count);
			isp_error("%s md_ind_continuous_enable_count%d %d md_ind_discrete_enable_count%d %d\r\n",
					__func__, (int)value->md_ind_continuous_enable_count,  (int)value->md_continuous_values_count,
					(int)value->md_ind_discrete_enable_count, (int)value->md_discrete_values_count);
			return ret;
		}
	}
	return RTS_ISP_OK;
}

static int is_bounds_equal(const isp_iq_bounds_t *bounds, const isp_iq_bounds_t *bounds2)
{
	int i;
	if (bounds->bounds_count != bounds2->bounds_count ||
	    bounds->def_index != bounds2->def_index)
		return false;
	for (i = 0; i < bounds->bounds_count; i ++)
		if (bounds->bounds[i] != bounds2->bounds[i])
			return false;
	return true;
}

static int iq_dynamic_notify(struct isp_mod *mod, struct isp_mod *target)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (!iq->dyn_iq_ctrl->cur.val)
		return RTS_ISP_OK;

	if (!memcmp(&iq->dynamic, &iq->notified_dynamic, sizeof(iq->dynamic)))
		return RTS_ISP_OK;

	if (target) {
			ret = isp_mod_notify(target, ISP_NOTIFY_DYNAMIC,
					     &iq->dynamic, sizeof(iq->dynamic));
	} else {
		ret = isp_core_notify(isp_top_get_core(mod->owner_id),
				      ISP_NOTIFY_DYNAMIC,
				      &iq->dynamic, sizeof(iq->dynamic));
		if (!ret && iq->patch_ops)
			ret = iq->patch_ops->dynamic(mod->owner_id,
						     &iq->dynamic);
	}
	if (ret)
		goto out;
	ret = isp_core_notify(isp_top_get_core(mod->owner_id),
			      ISP_NOTIFY_DYNAMIC_POST, NULL, 0);
	if (ret)
		goto out;
	iq->notified_dynamic = iq->dynamic;
out:
	if (ret)
		isp_perror(ret, "iq notify dynamic fail");
	return ret;
}

static int iq_timer_callback(isp_timer_handle_t *timer, void *data)
{
	struct isp_mod *mod = data;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (iq->dyn_iq_ctrl->cur.val)
		return iq_dynamic_notify(mod, NULL);
	return RTS_ISP_OK;
}

int iq_dynamic_run(void)
{
	struct isp_mod *mod = &iq.mod;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (iq->dyn_iq_ctrl->cur.val)
		return iq_dynamic_notify(mod, NULL);
	return RTS_ISP_OK;
}

static int mod_iq_start_pre(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	ret = iq_dynamic_notify(mod, NULL);
	if (ret)
		return ret;
	return isp_timer_start(&iq->timer, DYNAMIC_IQ_TIMER_INTERVAL,
			       DYNAMIC_IQ_TIMER_INTERVAL);
}

static int mod_iq_stop_post(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq_reset_notified_value(iq);
	return isp_timer_stop(&iq->timer);
}

static int mod_iq_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	uint32_t gain;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	const isp_iq_texture_static_t *static_regs;
	const isp_iq_texture_dynamic_t *dynamic_regs;
	const isp_iq_texture_dyn_ratio_t *dynamic_ratio_regs;
	isp_algo_param_texture_t *param = &iq->algo_param->texture;


	iq->iq = isp_iq_get_texture(mod->owner_id);

	if (!iq->iq) {
		isp_error("%s iq NULL \r\n", __func__);
		return -RTS_ISP_ENOITEM;
	}

	static_regs = &iq->iq->static_regs;
	dynamic_regs = &iq->iq->dynamic_regs;
	dynamic_ratio_regs = &iq->iq->dyn_ratio_regs;
	isp_info("%s texture 0x%08x static_regs 0x%08x \r\n", __func__, iq->iq,
		 static_regs);

	if (!is_bounds_equal(&dynamic_regs->bounds, &dynamic_ratio_regs->dyn_gain_bounds)) {
		isp_error(
			"gain bounds of dynamic_regs is not equal to dynamic_ratio_regs'\r\n");
		return -RTS_ISP_EINVAL;
	}

	if (check_static_iq(static_regs) || check_dynamic_iq(dynamic_regs)
		|| check_dynamic_ratio_iq(dynamic_ratio_regs)) {
		isp_error("%s check_static_iq/check_dynamic_iq \r\n", __func__);
		return -RTS_ISP_EINVAL;
	}



	ret = iq->hw_ops->set_static_regs(mod->owner_id, static_regs);
	if (ret) {
		isp_error("%s set_static_regs %d \r\n", __func__, ret);
		return ret;
	}


	param->gain_index = dynamic_regs->bounds.def_index;
	gain = dynamic_regs->bounds.bounds[param->gain_index];
	ret = iq->hw_ops->set_dynamic_regs(mod->owner_id, gain, 0, 0,
					   0, dynamic_regs, param->gain_index);
	if (ret) {
		isp_error("%s set_dynamic_regs %d \r\n", __func__, ret);
		return ret;
	}

	param->ratio_index = dynamic_ratio_regs->bounds.def_index;

	ret = iq->hw_ops->set_dynamic_ratio_regs(mod->owner_id, gain, 0, 0,
					   0, dynamic_ratio_regs, param->ratio_index, param->gain_index);
	if (ret) {
		isp_error("%s set_dynamic_ratio_regs %d \r\n", __func__, ret);
		return ret;
	}

	if (dynamic_regs->enable || dynamic_ratio_regs->enable)
		return isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	else
		return isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);

}

static int mod_iq_hdr_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_sensor_mode mode = {
		.hdr = LINEAR_MODE,
	};

	struct isp_mod_iq *iq = get_mod(mod, iq);

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
								   &mode, sizeof(mode));
	if (ret)
		return ret;

	if (mode.hdr == iq->man->id)
		return RTS_ISP_OK;

	ret = isp_iq_change_table(iq->man, mode.hdr);
	if (ret)
		return ret;

	if (isp_top_get_status() <= RTS_ISP_STOPPED)
		return RTS_ISP_OK;

	return apply_iq_table(mod, iq->day_night_ctrl->val, 0);
}

static int mod_iq_dynamic(struct isp_mod *mod, void *data)
{
	int ret;
	uint32_t gain;
	uint16_t md_val;
	int nr_level;
	int de_level;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	const isp_iq_texture_dynamic_t *dynamic_regs = &iq->iq->dynamic_regs;
	const isp_iq_texture_dyn_ratio_t *dynamic_ratio_regs = &iq->iq->dyn_ratio_regs;
	struct isp_notify_dynamic *dyn = data;
	isp_algo_param_texture_t *param = &iq->algo_param->texture;

	if (dynamic_regs->based_on_et_gain)
		gain = dyn->ae.exp_gain;
	else
		gain = dyn->ae.gain;

	md_val = dyn->md.md_val;

	param->gain_index = isp_iq_get_bound(&dynamic_regs->bounds, gain);

	if (dyn->ae.hdr_mode == LINEAR_MODE) {
		param->ratio_index = 0;
	} else if (iq->iq->dyn_ratio_regs.enable) {
		param->ratio_index = isp_iq_get_bound(
			&iq->iq->dyn_ratio_regs.bounds, dyn->ae.iq_ratio[1]
		);
	}

	nr_level = iq->nr_level_ctrl ? iq->nr_level_ctrl->val - 4 : 0;
	de_level = iq->de_level_ctrl ? iq->de_level_ctrl->val - 4 : 0;
	ret = iq->hw_ops->set_dynamic_regs(mod->owner_id,
					   gain, nr_level, de_level, md_val,
					   dynamic_regs, param->gain_index);
	if (ret)
		return ret;

	ret = iq->hw_ops->set_dynamic_ratio_regs(
				mod->owner_id, gain,
				nr_level, de_level, md_val,
				dynamic_ratio_regs,
				param->ratio_index, param->gain_index);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info iq_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_START_PRE, mod_iq_start_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_POST, mod_iq_stop_post),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_iq_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_iq_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_iq_hdr_mode_change),
};

static inline void set_ptr_value(uint32_t *ptr, uint32_t value)
{
	if (ptr)
		*ptr = value;
}

static int iq_get_type_info(struct isp_mod *mod,
			    enum rts_isp_tuning_iq_type type,
			    const pb_msgdesc_t **fields, void ***iq_ptr,
			    uint32_t *target_id, uint32_t *size)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct isp_iq *man = iq->man;

	switch (type) {
	case RTS_ISP_TUNING_IQ_TABLE_ALL:
		*fields = isp_iq_table_t_fields;
		*iq_ptr = (void **)&man->iq_table;
		set_ptr_value(target_id, 0);
		set_ptr_value(size, sizeof(*man->iq_table));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_BLC:
		*fields = isp_iq_blc_t_fields;
		*iq_ptr = (void **)&man->iq_table->blc;
		set_ptr_value(target_id, MOD_BLC);
		set_ptr_value(size, sizeof(*man->iq_table->blc));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_NLSC:
		*fields = isp_iq_nlsc_t_fields;
		*iq_ptr = (void **)&man->iq_table->nlsc;
		set_ptr_value(target_id, MOD_NLSC);
		set_ptr_value(size, sizeof(*man->iq_table->nlsc));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_MLSC:
		*fields = isp_iq_mlsc_t_fields;
		*iq_ptr = (void **)&man->iq_table->mlsc;
		set_ptr_value(target_id, MOD_MLSC);
		set_ptr_value(size, sizeof(*man->iq_table->mlsc));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_AE:
		*fields = isp_iq_ae_t_fields;
		*iq_ptr = (void **)&man->iq_table->ae;
		set_ptr_value(target_id, MOD_AE);
		set_ptr_value(size, sizeof(*man->iq_table->ae));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_AWB:
		*fields = isp_iq_awb_t_fields;
		*iq_ptr = (void **)&man->iq_table->awb;
		set_ptr_value(target_id, MOD_AWB);
		set_ptr_value(size, sizeof(*man->iq_table->awb));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_AF:
		*fields = isp_iq_af_t_fields;
		*iq_ptr = (void **)&man->iq_table->af;
		set_ptr_value(target_id, MOD_AF);
		set_ptr_value(size, sizeof(*man->iq_table->af));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_CCM:
		*fields = isp_iq_ccm_t_fields;
		*iq_ptr = (void **)&man->iq_table->ccm;
		set_ptr_value(target_id, MOD_CCM);
		set_ptr_value(size, sizeof(*man->iq_table->ccm));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_GAMMA:
		*fields = isp_iq_gamma_t_fields;
		*iq_ptr = (void **)&man->iq_table->gamma;
		set_ptr_value(target_id, MOD_GAMMA);
		set_ptr_value(size, sizeof(*man->iq_table->gamma));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_WDR:
		*fields = isp_iq_wdr_t_fields;
		*iq_ptr = (void **)&man->iq_table->wdr;
		set_ptr_value(target_id, MOD_WDR);
		set_ptr_value(size, sizeof(*man->iq_table->wdr));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_YGC:
		*fields = isp_iq_ygc_t_fields;
		*iq_ptr = (void **)&man->iq_table->ygc;
		set_ptr_value(target_id, MOD_YGC);
		set_ptr_value(size, sizeof(*man->iq_table->ygc));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_UVTUNE:
		*fields = isp_iq_uvtune_t_fields;
		*iq_ptr = (void **)&man->iq_table->uvtune;
		set_ptr_value(target_id, MOD_UVTUNE);
		set_ptr_value(size, sizeof(*man->iq_table->uvtune));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_SPE:
		*fields = isp_iq_spe_t_fields;
		*iq_ptr = (void **)&man->iq_table->spe;
		set_ptr_value(target_id, MOD_SPE);
		set_ptr_value(size, sizeof(*man->iq_table->spe));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_TEXTURE:
		*fields = isp_iq_texture_t_fields;
		*iq_ptr = (void **)&man->iq_table->texture;
		set_ptr_value(target_id, MOD_IQ);
		set_ptr_value(size, sizeof(*man->iq_table->texture));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_DAYNIGHT:
		*fields = isp_iq_daynight_t_fields;
		*iq_ptr = (void **)&man->iq_table->daynight;
		set_ptr_value(target_id, MOD_RAWSTAT);
		set_ptr_value(size, sizeof(*man->iq_table->daynight));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_HIGH_TEMP:
		*fields = isp_iq_high_temp_t_fields;
		*iq_ptr = (void **)&man->iq_table->high_temp;
		set_ptr_value(target_id, MOD_SENSOR);
		set_ptr_value(size, sizeof(*man->iq_table->high_temp));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_TM:
		*fields = isp_iq_tm_t_fields;
		*iq_ptr = (void **)&man->iq_table->tm;
		set_ptr_value(target_id, MOD_TM);
		set_ptr_value(size, sizeof(*man->iq_table->tm));
		break;
	case RTS_ISP_TUNING_IQ_TABLE_MD:
		*fields = isp_iq_md_t_fields;
		*iq_ptr = (void **)&man->iq_table->md;
		set_ptr_value(target_id, MOD_MD);
		set_ptr_value(size, sizeof(*man->iq_table->md));
		break;
	default:
		return -RTS_ISP_ENOITEM;
	}
	return RTS_ISP_OK;
}

static int apply_iq_table(struct isp_mod *mod,
			  uint32_t day_night, uint32_t target_id)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (target_id) {
		struct isp_mod *target;

		target = isp_top_get_mod(mod->owner_id, target_id);
		ret = isp_mod_notify(target, ISP_NOTIFY_IQ_CHANGE,
				     &day_night, sizeof(day_night));
		if (ret)
			goto out;
		iq_reset_notified_value(iq);
		ret = iq_dynamic_notify(mod, target);
	} else {
		ret = isp_core_notify(isp_top_get_core(mod->owner_id),
				      ISP_NOTIFY_IQ_CHANGE,
				      &day_night, sizeof(day_night));
		if (ret)
			goto out;
		iq_reset_notified_value(iq);
		ret = iq_dynamic_notify(mod, NULL);
	}
out:
	if (ret)
		isp_perror(ret, "iq change notify fail");
	return ret;
}

static int iq_get_prepare(struct isp_mod *mod,
			  enum rts_isp_tuning_iq_type type,
			  const pb_msgdesc_t **fields, void **iq_ptr)
{
	int ret;
	void **ptr;

	ret = iq_get_type_info(mod, type, fields, &ptr, NULL, NULL);
	if (ret)
		return ret;
	*iq_ptr = *ptr;

	return RTS_ISP_OK;
}

static int iq_set_prepare(struct isp_mod *mod,
			  enum rts_isp_tuning_iq_type type,
			  const pb_msgdesc_t **fields,
			  void **iq_ptr, uint32_t *target_id)
{
	int ret;
	void **ptr;
	uint32_t size;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	ret = iq_get_type_info(mod, type, fields, &ptr, target_id, &size);
	if (ret)
		return ret;
	iq->iq_backup = *ptr;
	*ptr = isp_calloc(1, size);
	if (!*ptr) {
		*ptr = iq->iq_backup;
		iq->iq_backup = NULL;
		return -RTS_ISP_ENOMEM;
	}
	*iq_ptr = *ptr;

	return RTS_ISP_OK;
}

static void iq_set_unprepare(struct isp_mod *mod,
			     enum rts_isp_tuning_iq_type type, int retval)
{
	int ret;
	void **ptr;
	uint32_t mod_id;
	const pb_msgdesc_t *fields;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (!iq->iq_backup)
		return;

	ret = iq_get_type_info(mod, type, &fields, &ptr, &mod_id, NULL);
	if (ret)
		return;
	if (retval) {
		isp_error("set iq fail, roll back to old iq table\n");
		pb_release(fields, *ptr);
		isp_free(*ptr);
		*ptr = iq->iq_backup;
		iq->iq_backup = NULL;
		apply_iq_table(mod, iq->day_night_ctrl->cur.val, mod_id);
	} else {
		pb_release(fields, iq->iq_backup);
		isp_free(iq->iq_backup);
	}
}

static int mod_iq_exec_set_dynamic_ae(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq->dynamic.ae = *(struct isp_notify_dynamic_ae *)data;

	return RTS_ISP_OK;
}

static int mod_iq_exec_set_dynamic_awb(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq->dynamic.awb = *(struct isp_notify_dynamic_awb *)data;

	return RTS_ISP_OK;
}

static int mod_iq_exec_set_dynamic_snr(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq->dynamic.sensor = *(struct isp_notify_dynamic_sensor *)data;

	return RTS_ISP_OK;
}

static int mod_iq_exec_set_dynamic_md(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq->dynamic.md = *(struct isp_notify_dynamic_md *)data;

	return RTS_ISP_OK;
}

static int mod_iq_exec_bind_algo(struct isp_mod *mod, void *data)
{
	int id = *(int *)data;

	return isp_top_bind_algo_unlock(mod->owner_id, id);
}

static int mod_iq_exec_unbind_algo(struct isp_mod *mod, void *data)
{
	int id = *(int *)data;

	return isp_top_unbind_algo_unlock(mod->owner_id, id);
}

static int mod_iq_exec_get_algo_param(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	isp_algo_param_t *algo_param = iq->algo_param;
	struct rts_isp_tuning_param *param = data;
	pb_ostream_t stream;
	const pb_msgdesc_t *fields;
	const void *src_struct;

	if (!param)
		return -RTS_ISP_EINVAL;

	stream = pb_ostream_from_buffer(iq->algo_param_shm.buf, param->max_len);
	switch (param->type) {
	case RTS_ISP_TUNING_PARAM_ALL:
		fields = isp_algo_param_t_fields;
		src_struct = algo_param;
		break;
	case RTS_ISP_TUNING_PARAM_AE:
		fields = isp_algo_param_ae_t_fields;
		src_struct = &algo_param->ae;
		break;
	case RTS_ISP_TUNING_PARAM_AWB:
		fields = isp_algo_param_awb_t_fields;
		src_struct = &algo_param->awb;
		break;
	case RTS_ISP_TUNING_PARAM_FLICK:
		fields = isp_algo_param_flick_t_fields;
		src_struct = &algo_param->flick;
		break;
	case RTS_ISP_TUNING_PARAM_WDR:
		fields = isp_algo_param_wdr_t_fields;
		src_struct = &algo_param->wdr;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	if (!pb_encode(&stream, fields, src_struct)) {
		isp_error("encode param error: %s\n", PB_GET_ERROR(&stream));
		return -RTS_ISP_EPROTOBUF;
	}

	param->len = stream.bytes_written;

	return RTS_ISP_OK;
}

static int mod_iq_exec_get_meta_param(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	isp_algo_param_t *algo_param = iq->algo_param;
	struct rts_isp_meta_param *m_param = (struct rts_isp_meta_param *)data;

    isp_algo_param_ae_t *ae_para;
    isp_algo_param_awb_t *awb_para;
    isp_algo_param_wdr_t *wdr_para;


    ae_para = &(algo_param->ae);
    awb_para = &(algo_param->awb);
    wdr_para = &(algo_param->wdr);


	m_param->exposure_h = ae_para->exposure[0];
	m_param->gain_h = ae_para->gain[0];
	m_param->y_average = ae_para->y_mean;

	m_param->colot_temperature = awb_para->color_temperature;
	m_param->white_num = awb_para->white_num;
	m_param->rg_sum = awb_para->rg_sum;
	m_param->bg_sum = awb_para->bg_sum;

	m_param->exposure_l = ae_para->exposure[1];
	m_param->gain_l = ae_para->gain[1];
	m_param->cur_dyn_fps = ae_para->cur_dyn_fps;
	m_param->cur_y_target = ae_para->cur_y_target;

	m_param->hist_contrast = wdr_para->hist_contrast;
	m_param->hist_contrast_origin =wdr_para->hist_contrast_origin;

	memset(m_param->ae_algo_dbg_buf, 0, sizeof(m_param->ae_algo_dbg_buf));
	return isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_DEBUG_BUF,
				       &m_param->ae_algo_dbg_buf[0],
				       sizeof(m_param->ae_algo_dbg_buf));

}

static int mod_iq_exec_set_algo_param(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	isp_algo_param_t *algo_param = iq->algo_param;
	struct rts_isp_tuning_param *param = data;
	pb_istream_t stream;
	const pb_msgdesc_t *fields;
	void *dst_struct;

	if (!param)
		return -RTS_ISP_EINVAL;

	stream = pb_istream_from_buffer(iq->algo_param_shm.buf, param->len);
	switch (param->type) {
	case RTS_ISP_TUNING_PARAM_ALL:
		fields = isp_algo_param_t_fields;
		dst_struct = algo_param;
		break;
	case RTS_ISP_TUNING_PARAM_AE:
		fields = isp_algo_param_ae_t_fields;
		dst_struct = &algo_param->ae;
		break;
	case RTS_ISP_TUNING_PARAM_AWB:
		fields = isp_algo_param_awb_t_fields;
		dst_struct = &algo_param->awb;
		break;
	case RTS_ISP_TUNING_PARAM_FLICK:
		fields = isp_algo_param_flick_t_fields;
		dst_struct = &algo_param->flick;
		break;
	case RTS_ISP_TUNING_PARAM_WDR:
		fields = isp_algo_param_wdr_t_fields;
		dst_struct = &algo_param->wdr;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	if (!pb_decode_noinit(&stream, fields, dst_struct)) {
		isp_error("encode param error: %s\n", PB_GET_ERROR(&stream));
		return -RTS_ISP_EPROTOBUF;
	}

	return RTS_ISP_OK;
}

static int mod_iq_exec_get_iq_table(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct rts_isp_tuning_iq *tuning_iq = data;
	pb_ostream_t stream;
	const pb_msgdesc_t *fields = NULL;
	void *src_struct = NULL;

	if (tuning_iq->type >= __RTS_ISP_TUNING_IQ_TABLE_NUM ||
	    tuning_iq->max_len != TUNING_IQ_TABLE_SHM_SIZE)
		return -RTS_ISP_EINVAL;

	ret = iq_get_prepare(mod, tuning_iq->type, &fields, &src_struct);
	if (ret)
		return ret;

	stream = pb_ostream_from_buffer(iq->tuning_shm.buf, tuning_iq->max_len);
	if (!pb_encode(&stream, fields, src_struct)) {
		isp_error("encode iq error: %s\n", PB_GET_ERROR(&stream));
		return -RTS_ISP_EPROTOBUF;
	}
	tuning_iq->len = stream.bytes_written;

	return RTS_ISP_OK;
}

static int mod_iq_exec_set_iq_table(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct rts_isp_tuning_iq *tuning_iq = data;
	pb_istream_t stream;
	const pb_msgdesc_t *fields = NULL;
	void *dst_struct = NULL;
	uint32_t mod_id = 0;

	if (tuning_iq->type >= __RTS_ISP_TUNING_IQ_TABLE_NUM ||
	    tuning_iq->max_len != TUNING_IQ_TABLE_SHM_SIZE)
		return -RTS_ISP_EINVAL;

	ret = iq_set_prepare(mod, tuning_iq->type,
			     &fields, &dst_struct, &mod_id);
	if (ret)
		return ret;

	stream = pb_istream_from_buffer(iq->tuning_shm.buf, tuning_iq->len);
	if (!pb_decode(&stream, fields, dst_struct)) {
		isp_error("decode iq error: %s\n", PB_GET_ERROR(&stream));
		ret = -RTS_ISP_EPROTOBUF;
		goto out;
	}
	ret = apply_iq_table(mod, iq->day_night_ctrl->cur.val, mod_id);
out:
	iq_set_unprepare(mod, tuning_iq->type, ret);
	return ret;
}

static int mod_iq_exec_read_regs(struct isp_mod *mod, void *data)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct isp_iq_tuning_regs *regs = data;

	return iq->hw_ops->read_regs(mod->owner_id, regs->regs, regs->num);
}

static int mod_iq_exec_write_regs(struct isp_mod *mod, void *data)
{
	int ret;
	int has_vreg;
	struct isp_mod_iq *iq = get_mod(mod, iq);
	struct isp_iq_tuning_regs *regs = data;

	ret = iq->hw_ops->write_regs(mod->owner_id,
				     regs->regs, regs->num, &has_vreg);
	if (ret)
		return ret;
	if (has_vreg)
		return isp_core_notify(isp_top_get_core(mod->owner_id),
				       ISP_NOTIFY_DYNAMIC_POST, NULL, 0);
	return RTS_ISP_OK;
}

static int mod_iq_exec_reload_packed_iq(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	iq->iq_backup = iq->man->iq_table;
	iq->man->iq_table = NULL;
	ret = isp_iq_reload_packed_iq(iq->man);
	if (ret)
		goto out;
	ret = apply_iq_table(mod, iq->day_night_ctrl->cur.val, 0);
	if (ret)
		goto out;
	if (iq->iq_ctrl) {
		int i;

		iq->iq_ctrl->default_value = iq->man->id;
		iq->iq_ctrl->menu_skip_mask = (~iq->man->entry_bits &
					       ((1 << _MAX_ISP_IQ_NUM) - 1));
		iq->iq_ctrl->cur.val = iq->man->id;
		iq->iq_ctrl->val = iq->man->id;
		for (i = 0; i < _MAX_ISP_IQ_NUM; i++)
			iq->iq_menu[i] = iq->man->entries[i].name;
	}
out:
	if (ret) {
		iq->man->iq_table = iq->iq_backup;
		apply_iq_table(mod, iq->day_night_ctrl->cur.val, 0);
	} else {
		pb_release(isp_iq_table_t_fields, iq->iq_backup);
		isp_free(iq->iq_backup);
	}
	iq->iq_backup = NULL;
	return ret;
}

static struct isp_mod_action_info iq_exec_actions[] = {
	ISP_MOD_ACTION(IQ_EXEC_SET_DYNAMIC_AE, mod_iq_exec_set_dynamic_ae),
	ISP_MOD_ACTION(IQ_EXEC_SET_DYNAMIC_AWB, mod_iq_exec_set_dynamic_awb),
	ISP_MOD_ACTION(IQ_EXEC_SET_DYNAMIC_MD, mod_iq_exec_set_dynamic_md),
	ISP_MOD_ACTION(IQ_EXEC_BIND_ALGO, mod_iq_exec_bind_algo),
	ISP_MOD_ACTION(IQ_EXEC_UNBIND_ALGO, mod_iq_exec_unbind_algo),
	ISP_MOD_ACTION(IQ_EXEC_GET_ALGO_PARAM, mod_iq_exec_get_algo_param),
	ISP_MOD_ACTION(IQ_EXEC_SET_ALGO_PARAM, mod_iq_exec_set_algo_param),
	ISP_MOD_ACTION(IQ_EXEC_GET_IQ_TABLE, mod_iq_exec_get_iq_table),
	ISP_MOD_ACTION(IQ_EXEC_SET_IQ_TABLE, mod_iq_exec_set_iq_table),
	ISP_MOD_ACTION(IQ_EXEC_SET_DYNAMIC_SENSOR, mod_iq_exec_set_dynamic_snr),
	ISP_MOD_ACTION(IQ_EXEC_READ_REGS, mod_iq_exec_read_regs),
	ISP_MOD_ACTION(IQ_EXEC_WRITE_REGS, mod_iq_exec_write_regs),
	ISP_MOD_ACTION(IQ_EXEC_RELOAD_PACKED_IQ, mod_iq_exec_reload_packed_iq),
	ISP_MOD_ACTION(IQ_EXEC_GET_META_PARAM, mod_iq_exec_get_meta_param),
};

static int iq_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_iq *iq = get_mod(mod, iq);

	if (ctrl->val == ctrl->cur.val) /* called by ctrl setup */
		return RTS_ISP_OK;
	switch (ctrl->id) {
	case RTS_V4L2_CID_DAY_NIGHT:
		ret = isp_iq_change_day_night(iq->man, ctrl->val);
		if (ret)
			return ret;
		ret = apply_iq_table(mod, iq->day_night_ctrl->val, 0);
		if (ret) {
			isp_error("change day night fail, roll back to old\n");
			isp_iq_change_day_night(iq->man, ctrl->cur.val);
			apply_iq_table(mod, iq->day_night_ctrl->val, 0);
		}
		break;
	case RTS_V4L2_CID_IQ_TABLE:
#if 0
		ret = isp_iq_change_table(iq->man, ctrl->val);
		ret = apply_iq_table(mod, iq->day_night_ctrl->val, 0);
		if (ret) {
			isp_error("change iq table fail, roll back to old\n");
			isp_iq_change_table(iq->man, ctrl->cur.val);
			apply_iq_table(mod, iq->day_night_ctrl->val, 0);
		}
#else
		printf("iq_id used for linear/hdr sensor setting. this ctrl can't set iq table index \n");

#endif
		break;
	case RTS_V4L2_CID_DYNAMIC_IQ:
	case RTS_V4L2_CID_NR_LEVEL:
	case RTS_V4L2_CID_DE_LEVEL:
		if (!iq->dyn_iq_ctrl->val)
			break;
		iq_reset_notified_value(iq);
		ret = iq_dynamic_notify(mod, NULL);
		break;
	case RTS_V4L2_CID_DYNAMIC_IQ_MODE:

		printf("Change dyn_iq_mode to %d\n", (int)iq->dyn_iq_mode_ctrl->val);
		iq->dynamic.dyn_mode = (enum rts_isp_dynamic_iq_mode)iq->dyn_iq_mode_ctrl->val;

		break;
	default:
		ret = -RTS_ISP_ECTRL;
	}

	return ret;
}

static const struct v4l2_ctrl_ops iq_ctrl_ops = {
	.s_ctrl = iq_s_ctrl,
};

static int isp_mod_iq_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_iq *iq;

	iq = get_mod(mod, iq);
	iq->man = isp_core_get_iq(isp_top_get_core(mod->owner_id));
	if (!iq->man) {
		ret = -RTS_ISP_ENOTREADY;
		goto err;
	}
	iq->hw_ops = isp_hw_iq_get_ops();
	if (!iq->hw_ops) {
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR,
				       SENSOR_INFO_PATCH_OPS,
				       &iq->patch_ops, sizeof(struct rts_isp_sensor_patch_ops *));
	if (ret)
		goto err;
	iq->algo_param = isp_iq_get_algo_param(mod->owner_id);
	ret = isp_shm_init(&iq->algo_param_shm, TUNING_PARAM_SHM_SIZE,
			   TUNING_PARAM_SHM_NAME);
	if (ret)
		goto err;

	ret = isp_shm_init(&iq->tuning_shm, TUNING_IQ_TABLE_SHM_SIZE,
			   TUNING_IQ_TABLE_SHM_NAME);
	if (ret)
		goto err;
	iq->dynamic.pre = &iq->notified_dynamic;
	iq->notified_dynamic.pre = &iq->notified_dynamic;
	ret = isp_timer_init(&iq->timer, isp_top_get_poll(),
			     iq_timer_callback, mod);
	if (ret)
		goto err;

	return RTS_ISP_OK;
err:
	isp_perror(ret, "mod iq init fail");
	isp_shm_cleanup(&iq->algo_param_shm, TUNING_PARAM_SHM_SIZE,
			TUNING_PARAM_SHM_NAME);
	isp_shm_cleanup(&iq->tuning_shm, TUNING_IQ_TABLE_SHM_SIZE,
			TUNING_IQ_TABLE_SHM_NAME);
	return ret;
}

static int isp_mod_iq_cleanup(struct isp_mod *mod)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	isp_timer_cleanup(&iq->timer);
	isp_shm_cleanup(&iq->algo_param_shm, TUNING_PARAM_SHM_SIZE,
			TUNING_PARAM_SHM_NAME);
	isp_shm_cleanup(&iq->tuning_shm, TUNING_IQ_TABLE_SHM_SIZE,
			TUNING_IQ_TABLE_SHM_NAME);
	return RTS_ISP_OK;
}

static int isp_mod_iq_hardware_init(struct isp_mod *mod)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);

	return iq->hw_ops->init_vreg(mod->owner_id);
}


extern int iq_init_dn_mode;

static int isp_mod_iq_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_iq *iq = get_mod(mod, iq);
	uint32_t iq_entry_bits;
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config dn_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_DAY_NIGHT,
		.name = "Night mode",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 2,
		.step = 1,
		.def = iq_init_dn_mode,
	};
	int i;

	for (i = 0; i < _MAX_ISP_IQ_NUM; i++)
		iq->iq_menu[i] = iq->man->entries[i].name;

	struct v4l2_ctrl_config iq_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_IQ_TABLE,
		.name = "IQ table menu",
		.type = V4L2_CTRL_TYPE_MENU,
		.max = ARRAY_SIZE(iq->iq_menu) - 1,
		.qmenu = iq->iq_menu,
	};
	struct v4l2_ctrl_config dyn_iq_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_DYNAMIC_IQ,
		.name = "IQ dynamic global enable",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 1,
	};
	const struct v4l2_ctrl_config nr_level_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_NR_LEVEL,
		.name = "Noise reduction level",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 8,
		.step = 1,
		.def = 4,
	};
	const struct v4l2_ctrl_config de_level_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_DE_LEVEL,
		.name = "Detail enhancement level",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 8,
		.step = 1,
		.def = 4,
	};
	const struct v4l2_ctrl_config dynamic_iq_mode_config = {
		.ops = &iq_ctrl_ops,
		.id = RTS_V4L2_CID_DYNAMIC_IQ_MODE,
		.name = "Dynamic IQ mode",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = RTS_ISP_DYNAMIC_IQ_MODE_STEPPING,
		.max = RTS_ISP_DYNAMIC_IQ_MODE_ONE_SHOT,
		.step = 1,
		.def = RTS_ISP_DYNAMIC_IQ_MODE_STEPPING,
	};

	iq->day_night_ctrl = rtsv_ctrl_new_custom(handler, &dn_config, mod);
	iq_entry_bits = iq->man->entry_bits;
	if (!iq_entry_bits)
		return -RTS_ISP_ENOTREADY;
	iq_config.def = iq->man->id;
	iq_entry_bits = ~iq_entry_bits & ((1 << _MAX_ISP_IQ_NUM) - 1);
	iq_config.menu_skip_mask = iq_entry_bits;

	iq->iq_ctrl = rtsv_ctrl_new_custom(handler, &iq_config, mod);

	iq->dyn_iq_ctrl = rtsv_ctrl_new_custom(handler, &dyn_iq_config, mod);
	iq->nr_level_ctrl = rtsv_ctrl_new_custom(handler,
						 &nr_level_config, mod);
	iq->de_level_ctrl = rtsv_ctrl_new_custom(handler,
						 &de_level_config, mod);
	iq->dyn_iq_mode_ctrl = rtsv_ctrl_new_custom(handler,
						 &dynamic_iq_mode_config, mod);
	if (iq->dyn_iq_mode_ctrl != NULL)
		iq->dynamic.dyn_mode = (enum rts_isp_dynamic_iq_mode)iq->dyn_iq_mode_ctrl->default_value;

	if (handler->error) {
		isp_perror(handler->error, "add iq ctrls fail");
		return handler->error;
	}

	return RTS_ISP_OK;
}



int isp_register_mod_iq(void)
{
	memset(&iq, 0, sizeof(iq));
	iq.mod.id = MOD_IQ;
	iq.mod.name = "iq";
	iq.mod.notify_bits = (ISP_IQ_CHANGE_BIT | ISP_HDR_MODE_CHANGE_BIT |
						 ISP_START_PRE_BIT | ISP_STOP_POST_BIT);
	iq.mod.init = isp_mod_iq_init;
	iq.mod.cleanup = isp_mod_iq_cleanup;
	iq.mod.hardware_init = isp_mod_iq_hardware_init;
	iq.mod.add_ctrl = isp_mod_iq_add_ctrl;
	iq.mod.info_actions = iq_info_actions;
	iq.mod.info_actions_num = ARRAY_SIZE(iq_info_actions);
	iq.mod.notify_actions = iq_notify_actions;
	iq.mod.notify_actions_num = ARRAY_SIZE(iq_notify_actions);
	iq.mod.exec_actions = iq_exec_actions;
	iq.mod.exec_actions_num = ARRAY_SIZE(iq_exec_actions);
	return isp_mod_register(&iq.mod);
}

void isp_unregister_mod_iq(void)
{
	isp_mod_unregister(&iq.mod);
}

