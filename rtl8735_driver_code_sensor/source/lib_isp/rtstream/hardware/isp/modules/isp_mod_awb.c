/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdlib.h>
#include <rts_isp_awb.h>
#include <isp_top.h>
#include <isp_v4l2_ctrl.h>
#include <isp_statis.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod_crop.h>
#include <isp_mod_awb.h>
#include <isp_mod_iq.h>
#include <isp_hw_awb.h>
#include <isp_algo.h>
#include <isp_debug.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_AWB

struct isp_mod_awb {
	struct isp_mod mod;
	const struct rts_isp_awb_algo *awb_algo;
	const struct isp_hw_awb_ops *hw_ops;

	struct isp_awb_hw_info hw_info;
	uint16_t pixels_per_cell;
	uint16_t fine_pixels;
	int algo_delay;

	struct rts_isp_awb_gain gain;
	uint32_t color_temp;

	enum rts_isp_awb_mode mode;
	struct {
		uint16_t r_gain_adj;
		uint16_t b_gain_adj;
	} _auto_setting;
	uint32_t auto_setting_has_set;

	struct {
		struct v4l2_ctrl *awb_ctrl;
		struct v4l2_ctrl *red_ctrl;
		struct v4l2_ctrl *green_ctrl;
		struct v4l2_ctrl *blue_ctrl;
		struct v4l2_ctrl *color_temp_ctrl;
	};

	isp_algo_param_t *param;

	struct isp_mod *mod_iq;
	const isp_iq_awb_t *iq;
	uint awb_clip:1;
};

static int check_awb_algo_version(uint32_t version)
{
	if (algo_magic(version) != AWB_API_VERSION_MAGIC ||
	    algo_major_version(version) != AWB_API_MAJOR_VERSION ||
	    algo_minor_version(version) > 0)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_awb(const struct rts_isp_awb_algo *awb_algo)
{
	if (!awb_algo || check_awb_algo_version(awb_algo->api_version))
		return -RTS_ISP_EINVAL;
	printf("awb ver 0x%08x \n",awb_algo->api_version);
	if (!awb_algo->init || !awb_algo->cleanup)
		return -RTS_ISP_EINVAL;
	if (!awb_algo->run || !awb_algo->ctrl)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_awb_iq(const isp_iq_awb_t *iq)
{
	int i;
	isp_iq_awb_ct_item_t *ct_item;

	if (!iq)
		return -RTS_ISP_EINVAL;
	//return 0; //[Workaround] for IQ load
	if (isp_iq_check_hysteresis_bounds(&iq->dyn_ct.bounds,
					   iq->dyn_ct.ct_items_count))
		return -RTS_ISP_EINVAL;
	isp_info("%s ct_items_count %d dyn_ct.enable %d \r\n", __func__,  iq->dyn_ct.ct_items_count, iq->dyn_ct.enable);
	for (i = 0; i < iq->dyn_ct.ct_items_count; i++) {
		ct_item = &iq->dyn_ct.ct_items[i];
		isp_info("%s based_on_et_gain %d adjs_count %d \r\n", __func__, ct_item->based_on_et_gain, ct_item->adjs_count);
		if (isp_iq_check_bounds(&ct_item->bounds, ct_item->adjs_count))
			return -RTS_ISP_EINVAL;
	}
	isp_info("%s enable %d r_gain %d g_gain %d b_gain %d \r\n", __func__,  iq->enable, iq->def_r_gain, iq->def_g_gain, iq->def_b_gain);
	if (iq->def_r_gain < 256 || iq->def_r_gain > 2047 ||
	    iq->def_g_gain < 256 || iq->def_g_gain > 2047 ||
	    iq->def_b_gain < 256 || iq->def_b_gain > 2047) {

		return -RTS_ISP_ERANGE;
	}


	return RTS_ISP_OK;
}

static int awb_calc_pixels(struct isp_mod_awb *awb, const rts_isp_grid_t *grid)
{
	awb->pixels_per_cell = (grid->cell.w * grid->cell.h /
				awb->hw_info.cell_sample.w /
				awb->hw_info.cell_sample.h);
	awb->fine_pixels = (awb->pixels_per_cell *
			    grid->size.cols * grid->size.rows);
	return RTS_ISP_OK;
}

static int awb_algo_need_delay(struct isp_mod_awb *awb)
{
	if (awb->algo_delay) {
		awb->algo_delay--;
		return RTS_ISP_TRUE;
	}
	return RTS_ISP_FALSE;
}

static int mod_awb_info_statis(struct isp_mod *mod, void *data)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct isp_mod_awb_stat_info *info = data;

	info->info.win = awb->hw_info.grid_info.size;
	info->info.pixels_per_cell = awb->pixels_per_cell;
	info->info.fine_pixels = awb->fine_pixels;
	info->rgby_size = awb->hw_info.rgby_size;
	info->rgbg_size = awb->hw_info.rgbg_size;
	info->pixels_size = awb->hw_info.pixels_size;

	return RTS_ISP_OK;
}

static int mod_awb_info_version(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	const struct rts_isp_awb_algo *algo;
	uint16_t *version = data;

	if (awb->awb_algo) {
		*version = awb->awb_algo->api_version & AWB_VERSION_MASK;
		return RTS_ISP_OK;
	}
	ret = isp_algo_get_awb(isp_top_get_algom(), mod->owner_id, &algo);
	if (ret)
		return ret;
	*version = algo->api_version & AWB_VERSION_MASK;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info awb_info_actions[] = {
	ISP_MOD_ACTION(AWB_INFO_STATIS, mod_awb_info_statis),
	ISP_MOD_ACTION(AWB_INFO_VERSION, mod_awb_info_version),
};

static int mod_awb_exec_get_setting(struct isp_mod *mod, void *data)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct rts_isp_awb_setting *setting = data;

	setting->mode = awb->mode;
	setting->_temperature.temperature =
		rtsv_ctrl_g_ctrl(awb->color_temp_ctrl);
	setting->_auto.r_gain_adj = awb->_auto_setting.r_gain_adj;
	setting->_auto.b_gain_adj = awb->_auto_setting.b_gain_adj;
	setting->_component.r_gain = rtsv_ctrl_g_ctrl(awb->red_ctrl);
	setting->_component.g_gain = rtsv_ctrl_g_ctrl(awb->green_ctrl);
	setting->_component.b_gain = rtsv_ctrl_g_ctrl(awb->blue_ctrl);

	return RTS_ISP_OK;
}

static int mod_awb_exec_set_setting(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct rts_isp_awb_setting *setting = data;

	if (setting->mode < RTS_ISP_AWB_TEMPERATURE_MODE ||
	    setting->mode > RTS_ISP_AWB_COMPONENT_MODE) {
		ret = -RTS_ISP_EINVAL;
		goto out;
	}

	ret = rtsv_ctrl_s_ctrl(awb->awb_ctrl,
			       setting->mode == RTS_ISP_AWB_AUTO_MODE);
	if (ret)
		goto out;
	awb->mode = setting->mode;

	switch (setting->mode) {
	case RTS_ISP_AWB_TEMPERATURE_MODE:
		ret = rtsv_ctrl_s_ctrl(awb->color_temp_ctrl,
				       setting->_temperature.temperature);
		if (ret)
			goto out;
		break;
	case RTS_ISP_AWB_AUTO_MODE:
		if (awb->awb_algo) {
			ret = awb->awb_algo->ctrl(mod->owner_id, SET_GAIN_ADJ,
						  &setting->_auto);
			if (ret)
				goto out;
		}
		awb->_auto_setting.r_gain_adj = setting->_auto.r_gain_adj;
		awb->_auto_setting.b_gain_adj = setting->_auto.b_gain_adj;
		awb->auto_setting_has_set = RTS_ISP_TRUE;
		break;
	case RTS_ISP_AWB_COMPONENT_MODE:
		ret = rtsv_ctrl_s_ctrl(awb->red_ctrl,
				       setting->_component.r_gain);
		if (ret)
			goto out;
		ret = rtsv_ctrl_s_ctrl(awb->green_ctrl,
				       setting->_component.g_gain);
		if (ret)
			goto out;
		ret = rtsv_ctrl_s_ctrl(awb->blue_ctrl,
				       setting->_component.b_gain);
		if (ret)
			goto out;
		break;
	}

	ret = mod_awb_exec_get_setting(mod, setting);
out:
	if (ret)
		isp_perror(ret, "set awb ctrl fail");
	return ret;
}

static int mod_awb_exec_set_awb_clip(struct isp_mod *mod, void *data)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);

	awb->awb_clip = *(uint32_t *)data;

	return awb->hw_ops->set_clip(mod->owner_id, awb->awb_clip);
}

static struct isp_mod_action_info awb_exec_actions[] = {
	ISP_MOD_ACTION(AWB_EXEC_GET_SETTING, mod_awb_exec_get_setting),
	ISP_MOD_ACTION(AWB_EXEC_SET_SETTING, mod_awb_exec_set_setting),
	ISP_MOD_ACTION(AWB_EXEC_SET_AWB_CLIP, mod_awb_exec_set_awb_clip),
};

static int mod_awb_set_gain_result(struct isp_mod *mod,
				   const struct rts_isp_awb_gain_result *result)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct isp_notify_dynamic_awb dyn_awb;

	ret = awb->hw_ops->set_final_gain(mod->owner_id, &result->gain);
	if (ret)
		return ret;

	awb->color_temp = result->color_temperature;
	awb->gain = result->gain;

	dyn_awb.color_temp = awb->color_temp;
	dyn_awb.r_gain = result->gain.r_gain / 256.0f;
	dyn_awb.g_gain = (result->gain.gr_gain + result->gain.gb_gain) / 512.0f;
	dyn_awb.b_gain = result->gain.b_gain / 256.0f;

	return isp_mod_execute(awb->mod_iq, IQ_EXEC_SET_DYNAMIC_AWB,
			       &dyn_awb, sizeof(dyn_awb));
}

static int mod_awb_set_result(struct isp_mod *mod,
			      const struct rts_isp_awb_result *result)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	//printf("%s update %d r %d gr %d gb %d b %d\n", __func__, result->result.need_update, result->result.gain.r_gain, result->result.gain.gr_gain, result->result.gain.gb_gain, result->result.gain.b_gain);
	if (result->result.need_update) {
		ret = mod_awb_set_gain_result(mod, &result->result);
		if (ret)
	return ret;
	}
	return awb->hw_ops->set_statis_config(mod->owner_id, &result->config);
}

static void clear_awb_result_need_update_flag(struct rts_isp_awb_result *result)
{
	result->result.need_update = RTS_ISP_FALSE;
	result->config.rough_gain.need_update = RTS_ISP_FALSE;
	result->config.rough_limit.need_update = RTS_ISP_FALSE;
	result->config.fine_limit.need_update = RTS_ISP_FALSE;
	result->config.illums.need_update = RTS_ISP_FALSE;
}
#ifdef _AWB_DEBUG_
static int log_cnt = 0;
static int interval = 60;
#endif
static int mod_awb_statis_done(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_awb *awb = get_mod(mod, awb);

	if (awb_algo_need_delay(awb)) {
		return RTS_ISP_OK;
	}

	if (awb->awb_algo) {
		const struct rts_isp_awb_statis *statis;
		struct rts_isp_awb_result result;

		clear_awb_result_need_update_flag(&result);
		statis = &((const struct rts_isp_statis *)data)->awb;
		ret = awb->awb_algo->run(mod->owner_id, statis, &result);

#ifdef _AWB_DEBUG_

		if (result.result.need_update || (log_cnt%interval) == 0 ) {
			uint32_t win_num = awb->hw_info.grid_info.size.cols * awb->hw_info.grid_info.size.rows;
			printf("win %d r %08x g %08x b %08x r %08x g %08x b %08x wp %08x\r\n", win_num, (unsigned int)statis->r_mean,  (unsigned int)statis->g_mean, (unsigned int)statis->b_mean, (unsigned int)statis->fine_r_sum, (unsigned int)statis->fine_g_sum, (unsigned int)statis->fine_b_sum, (unsigned int)statis->fine_white_pixels);
			//printf("r %08x g %08x b %08x wp %08x\r\n", (unsigned int)statis->fine_r_sum, (unsigned int)statis->fine_g_sum, (unsigned int)statis->fine_b_sum, (unsigned int)statis->fine_white_pixels);
			if (result.result.need_update ) {
				printf("updated %d temp %d r %08x gb %08x gr %08x b %08x \r\n", (unsigned int)result.result.need_update, (unsigned int)result.result.color_temperature, (unsigned int)result.result.gain.r_gain, (unsigned int)result.result.gain.gb_gain, (unsigned int)result.result.gain.gr_gain, (unsigned int)result.result.gain.b_gain);
				printf("config fine_limit %d illums %d rough_gain %d rough_limit %d \r\n", (unsigned int)result.config.fine_limit.need_update, (unsigned int)result.config.illums.need_update, (unsigned int)result.config.rough_gain.need_update, (unsigned int)result.config.rough_limit.need_update);
			}
			if (interval == 60) {
				interval = 59;
			} else {
				interval = 60;
			}

		}
		log_cnt++;
#endif
		if (ret)
			goto out;
		ret = mod_awb_set_result(mod, &result);
		if (ret)
			goto out;
	}
out:
	if (ret)
		isp_perror(ret, "awb statis done handle fail");
	//isp_info("%s \r\n",__func__);
	return ret;
}

static int mod_awb_cleanup_algo(struct isp_mod *mod)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);

	if (awb->awb_algo) {
		awb->awb_algo->cleanup(mod->owner_id);
		awb->awb_algo = NULL;
	}
	return RTS_ISP_OK;
}

static int mod_awb_update_awb_info(struct isp_mod *mod,
				   struct rts_isp_awb_info *info)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);

	info->stat_info.win = awb->hw_info.grid_info.size;
	info->stat_info.pixels_per_cell = awb->pixels_per_cell;
	info->stat_info.fine_pixels = (info->stat_info.pixels_per_cell *
				       info->stat_info.win.cols *
				       info->stat_info.win.rows);
	switch (awb->iq->which_algo) {
	case isp_iq_awb_t_awb1_tag:
		info->iq = &awb->iq->algo.awb1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	info->algo_param = awb->param;

	return RTS_ISP_OK;
}

static int mod_awb_init_algo(struct isp_mod *mod)
{
	int ret = RTS_ISP_OK;
	struct rts_isp_awb_info info;
	struct isp_mod_awb *awb = get_mod(mod, awb);

	ret = mod_awb_update_awb_info(mod, &info);
	if (ret)
		return ret;

	if (awb->awb_algo) {
		struct rts_isp_awb_result result;

		clear_awb_result_need_update_flag(&result);

		ret = awb->awb_algo->init(mod->owner_id, &info, &result);
		if (ret)
			goto out;

		ret = mod_awb_set_result(mod, &result);
		if (ret)
			goto out;
	}
out:
	if (ret)
		isp_error("awb init handle fail %d", ret);
	//isp_info("%s \r\n",__func__);
	return ret;
}

static int mod_awb_update_algo(struct isp_mod *mod)
{
	int ret = 0;
	struct isp_mod_awb *awb = get_mod(mod, awb);

	mod_awb_cleanup_algo(mod);
	ret = isp_algo_get_awb(isp_top_get_algom(),
			       mod->owner_id, &awb->awb_algo);
	if (ret)
		goto err;
	ret = check_awb(awb->awb_algo);
	if (ret)
		goto err;
	ret = mod_awb_init_algo(mod);
	if (ret)
		goto err;

	return RTS_ISP_OK;
err:
	isp_perror(ret, "update awb algo fail");
	mod_awb_cleanup_algo(mod);
	return ret;
}

static int mod_awb_algo_update(struct isp_mod *mod, void *data)
{
	uint32_t notify_data;

	notify_data = *(uint32_t *)data;
	if (!(notify_data & ISP_ALGO_AWB_CHANGE_BIT))
		return RTS_ISP_OK;
	return mod_awb_update_algo(mod);
}

static int awb_set_default_adj_gain(struct isp_mod *mod)
{
	int ret;
	int ct_index, gain_index;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct rts_isp_awb_rb_gain_adj adj;
	const isp_iq_awb_ct_item_t *ct_item;

	if (awb->awb_algo) {
		if (awb->auto_setting_has_set) {
			ret = awb->awb_algo->ctrl(mod->owner_id, SET_GAIN_ADJ,
						  &awb->_auto_setting);
			if (ret)
				return ret;
		} else {
			ct_index = awb->param->awb.adj_ct_index;
			ct_item = &awb->iq->dyn_ct.ct_items[ct_index];
			gain_index = ct_item->bounds.def_index;
			adj.r_gain_adj = ct_item->adjs[gain_index].r_gain;
			adj.b_gain_adj = ct_item->adjs[gain_index].b_gain;
			ret = awb->awb_algo->ctrl(mod->owner_id, SET_GAIN_ADJ,
						  &adj);
			if (ret)
				return ret;
		}
	}
	return RTS_ISP_OK;
}

static int mod_awb_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);

	awb->iq = isp_iq_get_awb(mod->owner_id);
	if (check_awb_iq(awb->iq)) {
		isp_error("get awb iq fail\n");
		return -RTS_ISP_ENOITEM;
	}
	ret = mod_awb_update_algo(mod);
	if (ret)
		return ret;
	if (awb->awb_ctrl) {
		ret = rtsv_ctrl_s_ctrl(awb->awb_ctrl, 0);
		if (ret)
			return ret;
	}
	if (awb->red_ctrl) {
		ret = rtsv_ctrl_s_ctrl(awb->red_ctrl, awb->iq->def_r_gain);
		if (ret)
			return ret;
			rtsv_ctrl_modify_range(awb->red_ctrl, 256, 2047, 1,
				       awb->iq->def_r_gain);
	}
	if (awb->green_ctrl) {
		ret = rtsv_ctrl_s_ctrl(awb->green_ctrl, awb->iq->def_g_gain);
		if (ret)
			return ret;
		rtsv_ctrl_modify_range(awb->green_ctrl, 256, 2047, 1,
				       awb->iq->def_g_gain);
	}
	if (awb->blue_ctrl) {
		ret = rtsv_ctrl_s_ctrl(awb->blue_ctrl, awb->iq->def_b_gain);
		if (ret)
			return ret;
		rtsv_ctrl_modify_range(awb->blue_ctrl, 256, 2047, 1,
				       awb->iq->def_b_gain);
	}
	//printf("v4l2_ctrl_s_ctrl r %d g %d b %d\n", __func__, awb->iq->def_r_gain, awb->iq->def_g_gain, awb->iq->def_b_gain);

	if (awb->awb_ctrl) {
		ret = rtsv_ctrl_s_ctrl(awb->awb_ctrl, awb->iq->enable);
		if (ret)
			return ret;
	}
	awb->param->awb.adj_ct_index = awb->iq->dyn_ct.bounds.def_index;
	ret = awb_set_default_adj_gain(mod);
		if (ret)
			return ret;

	if (awb->iq->dyn_ct.enable || awb->iq->dyn_gain.enable)
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	else
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
	//isp_info("%s done \r\n", __func__);
	return ret;
}

static int mod_awb_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);
	isp_iq_awb_gain_adj_t iq_gain_adj;
	struct rts_isp_awb_rb_gain_adj rb_gain_adj = {0x100, 0x100};
	const isp_iq_awb_t *iq = awb->iq;
	const isp_iq_awb_ct_item_t *ct_item;
	const struct isp_notify_dynamic *dyn = data;
	isp_algo_param_awb_t *param = &awb->param->awb;

	if (!awb->awb_algo || awb->auto_setting_has_set)
		return RTS_ISP_OK;

	if (iq->dyn_ct.enable)
		param->adj_ct_index =
			isp_iq_get_hysteresis_bound(&iq->dyn_ct.bounds,
							    dyn->awb.color_temp,
						    param->adj_ct_index);
	ct_item = &iq->dyn_ct.ct_items[param->adj_ct_index];

	if (iq->dyn_gain.enable) {
		int index;
		uint32_t dyn_value;

		if (ct_item->based_on_et_gain)
			dyn_value = dyn->ae.exp_gain;
		else
			dyn_value = dyn->ae.gain;

		index = isp_iq_get_bound(&ct_item->bounds, dyn_value);
		param->adj_gain_index = index;

		if (index == 0) {
			iq_gain_adj = ct_item->adjs[index];
		} else if (index == ct_item->bounds.bounds_count) {
			iq_gain_adj = ct_item->adjs[index - 1];
		} else {
			iq_gain_adj.r_gain = linear_intp(dyn_value,
					      ct_item->bounds.bounds[index - 1],
					      ct_item->adjs[index - 1].r_gain,
					      ct_item->bounds.bounds[index],
					      ct_item->adjs[index].r_gain);
			iq_gain_adj.b_gain = linear_intp(dyn_value,
					      ct_item->bounds.bounds[index - 1],
					      ct_item->adjs[index - 1].b_gain,
					      ct_item->bounds.bounds[index],
					      ct_item->adjs[index].b_gain);
		}

	} else {
		param->adj_gain_index = ct_item->bounds.def_index;
		iq_gain_adj = ct_item->adjs[param->adj_gain_index];
	}

	if (rb_gain_adj.r_gain_adj != iq_gain_adj.r_gain ||
	    rb_gain_adj.b_gain_adj != iq_gain_adj.b_gain) {
		rb_gain_adj.r_gain_adj = iq_gain_adj.r_gain;
		rb_gain_adj.b_gain_adj = iq_gain_adj.b_gain;
		return awb->awb_algo->ctrl(mod->owner_id, SET_GAIN_ADJ,
									&rb_gain_adj);
	} else {
		return RTS_ISP_OK;
	}
}

static int mod_awb_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	rts_isp_grid_t grid;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	const rts_isp_rect_t *rect = data;

	ret = rts_isp_get_grid_from_rect(&grid, rect, &awb->hw_info.grid_info);
	if (ret)
		return ret;
	ret = awb_calc_pixels(awb, &grid);
	if (ret)
		return ret;
	return awb->hw_ops->set_statis(mod->owner_id, &grid);
}

static int mod_awb_fps_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	int i;

	awb->algo_delay = awb->iq->algo_delay;
	return 0;
}

static struct isp_mod_action_info awb_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_awb_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_ALGO_UPDATE, mod_awb_algo_update),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_awb_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_awb_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_awb_mcrop_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_FPS_CHANGE, mod_awb_fps_change),
};

static int isp_mod_awb_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_awb *awb;

	awb = get_mod(mod, awb);

	awb->hw_ops = isp_hw_awb_get_ops();
	if (!awb->hw_ops) {
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	awb->param = isp_iq_get_algo_param(mod->owner_id);
	ret = awb->hw_ops->get_hw_info(mod->owner_id, &awb->hw_info);
	if (ret)
		goto err;
	awb->mod_iq = isp_mod_get_sibling(mod, MOD_IQ);
	if (!awb->mod_iq)
		goto err;
	awb->mode = RTS_ISP_AWB_AUTO_MODE;
	awb->_auto_setting.r_gain_adj = 256;
	awb->_auto_setting.b_gain_adj = 256;
	awb->awb_clip = 1;

	return RTS_ISP_OK;

err:
	return ret;
}

static int isp_mod_awb_cleanup(struct isp_mod *mod)
{
	mod_awb_cleanup_algo(mod);

	return RTS_ISP_OK;
}

static int awb_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_awb *awb = get_mod(mod, awb);

	if (ctrl->id != V4L2_CID_AUTO_WHITE_BALANCE)
		return -RTS_ISP_ECTRL;

	awb->color_temp_ctrl->val = awb->color_temp;
	awb->red_ctrl->val = awb->gain.r_gain;
	awb->green_ctrl->val = (awb->gain.gr_gain + awb->gain.gb_gain) / 2;
	awb->blue_ctrl->val = awb->gain.b_gain;

	return RTS_ISP_OK;
}

static int awb_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct rts_isp_awb_gain_result result;

	if (ctrl->id != V4L2_CID_AUTO_WHITE_BALANCE)
		return -RTS_ISP_ECTRL;

	if (awb->awb_ctrl->is_new) {
		if (awb->awb_ctrl->val)
			ret = isp_mod_add_notify(mod, ISP_NOTIFY_STATIS_DONE);
		else
			ret = isp_mod_del_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			return ret;
	}

	if (awb->red_ctrl->is_new ||
	    awb->green_ctrl->is_new  || awb->blue_ctrl->is_new) {
		result.gain.r_gain = awb->red_ctrl->val;
		result.gain.gr_gain = awb->green_ctrl->val;
		result.gain.gb_gain = awb->green_ctrl->val;
		result.gain.b_gain = awb->blue_ctrl->val;
		ret = awb->awb_algo->ctrl(mod->owner_id, GAIN_TO_COLOR_TEMP,
					  &result);
		if (ret) {
			isp_perror(ret, "get color temp from gain fail");
			return ret;
		}
		result.color_temperature =
			clamp_t(uint32_t, result.color_temperature,
				awb->color_temp_ctrl->minimum,
				awb->color_temp_ctrl->maximum);
		//printf("%s r %d gr %d gb %d b %d\n", __func__, result.gain.r_gain, result.gain.gr_gain, result.gain.gb_gain, result.gain.b_gain);
		ret = mod_awb_set_gain_result(mod, &result);
		if (ret)
			return ret;

		awb->color_temp_ctrl->val = result.color_temperature;
		awb->color_temp_ctrl->cur.val = result.color_temperature;
	} else if (awb->color_temp_ctrl->is_new) {
		result.color_temperature = awb->color_temp_ctrl->val;
		ret = awb->awb_algo->ctrl(mod->owner_id,
					  COLOR_TEMP_TO_GAIN, &result);
		if (ret) {
			isp_perror(ret, "get gain from color temp fail");
			return ret;
		}

		ret = mod_awb_set_gain_result(mod, &result);
		if (ret)
			return ret;

		awb->red_ctrl->val = result.gain.r_gain;
		awb->green_ctrl->val = (result.gain.gr_gain +
					result.gain.gb_gain) / 2;
		awb->blue_ctrl->val = result.gain.b_gain;
		awb->red_ctrl->cur.val = result.gain.r_gain;
		awb->green_ctrl->cur.val = (result.gain.gr_gain +
					    result.gain.gb_gain) / 2;
		awb->blue_ctrl->cur.val = result.gain.b_gain;
	}

	return RTS_ISP_OK;
}

static const struct v4l2_ctrl_ops awb_ctrl_ops = {
	.g_volatile_ctrl = awb_g_volatile_ctrl,
	.s_ctrl = awb_s_ctrl,
};

static int isp_mod_awb_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_awb *awb = get_mod(mod, awb);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config green_config = {
		.ops = &awb_ctrl_ops,
		.id = RTS_V4L2_CID_GREEN_BALANCE,
		.name = "Green Balance",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 256,
		.max = 2047,
		.step = 1,
		.def = awb->iq->def_g_gain,
		.flags = V4L2_CTRL_FLAG_SLIDER,
	};

	awb->awb_ctrl = rtsv_ctrl_new_std(handler, &awb_ctrl_ops,
					  V4L2_CID_AUTO_WHITE_BALANCE,
					  0, 1, 1, awb->iq->enable, mod);
	awb->red_ctrl = rtsv_ctrl_new_std(handler, &awb_ctrl_ops,
					  V4L2_CID_RED_BALANCE,
					  256, 2047, 1, awb->iq->def_r_gain,
					  mod);
	awb->green_ctrl = rtsv_ctrl_new_custom(handler, &green_config, mod);
	awb->blue_ctrl = rtsv_ctrl_new_std(handler, &awb_ctrl_ops,
					   V4L2_CID_BLUE_BALANCE,
					   256, 2047, 1, awb->iq->def_b_gain,
					   mod);
	awb->color_temp_ctrl =
		rtsv_ctrl_new_std(handler, &awb_ctrl_ops,
				  V4L2_CID_WHITE_BALANCE_TEMPERATURE,
				  1000, 10000, 1, 5000, mod);
	rtsv_ctrl_auto_cluster(5, &awb->awb_ctrl, 0, RTS_ISP_TRUE);
	if (handler->error) {
		isp_perror(handler->error, "add awb ctrls fail");
		return handler->error;
	}
	awb->red_ctrl->flags |= V4L2_CTRL_FLAG_UPDATE;
	awb->green_ctrl->flags |= V4L2_CTRL_FLAG_UPDATE;
	awb->blue_ctrl->flags |= V4L2_CTRL_FLAG_UPDATE;
	awb->color_temp_ctrl->flags |= V4L2_CTRL_FLAG_UPDATE;

	return RTS_ISP_OK;
}

static struct isp_mod_awb awb;

int isp_register_mod_awb(void)
{
	memset(&awb, 0, sizeof(awb));
	awb.mod.id = MOD_AWB;
	awb.mod.name = "awb";
	awb.mod.notify_bits = ISP_ALGO_UPDATE_BIT | ISP_IQ_CHANGE_BIT |
			      ISP_MCROP_CHANGE_BIT | ISP_FPS_CHANGE_BIT;
	awb.mod.init = isp_mod_awb_init;
	awb.mod.cleanup = isp_mod_awb_cleanup;
	awb.mod.add_ctrl = isp_mod_awb_add_ctrl;
	awb.mod.info_actions = awb_info_actions;
	awb.mod.info_actions_num = ARRAY_SIZE(awb_info_actions);
	awb.mod.exec_actions = awb_exec_actions;
	awb.mod.exec_actions_num = ARRAY_SIZE(awb_exec_actions);
	awb.mod.notify_actions = awb_notify_actions;
	awb.mod.notify_actions_num = ARRAY_SIZE(awb_notify_actions);
	return isp_mod_register(&awb.mod);
}

void isp_unregister_mod_awb(void)
{
	isp_mod_unregister(&awb.mod);
}

