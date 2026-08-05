/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_top.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_poll.h>
#include <isp_statis.h>
#include <isp_iq.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_crop.h>
#include <isp_mod_rawstat.h>
#include <isp_hw_rawstat.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_RAWSTAT

struct day_night_info {
	enum rts_isp_day_night cur;
	enum rts_isp_day_night result;
	int is_changing;
	uint32_t etgain;
	uint32_t win_num;
	uint16_t block_cnt;
	isp_timer_handle_t timer;
	const isp_iq_daynight_t *iq;
	int ir2rgb_timer_enable;
	int ir2rgb_timer_cnt;
	int rgb2ir_timer_enable;
	int rgb2ir_timer_cnt;

};

struct isp_mod_rawstat {
	struct isp_mod mod;
	struct isp_rawstat_hw_info hw_info;
	const struct isp_hw_rawstat_ops *hw_ops;
	uint32_t pixels_per_cell;
	uint32_t fine_pixels;

	struct day_night_info dn;
	struct v4l2_ctrl *day_night_detect_ctrl;
};

static int day_night_info_init(struct isp_mod_rawstat *rawstat)
{
	rawstat->dn.win_num = rawstat->hw_info.grid_info.size.cols *
			       rawstat->hw_info.grid_info.size.rows;
	rawstat->dn.block_cnt = 0;
	return RTS_ISP_OK;
}


static int day_night_timer_ir2rgb_start(struct day_night_info *dn)
{
	dn->ir2rgb_timer_enable = TRUE;
	dn->ir2rgb_timer_cnt =0;
	return RTS_ISP_OK;
}

static int day_night_timer_ir2rgb_stop(struct day_night_info *dn)
{
	dn->ir2rgb_timer_enable = FALSE;
	dn->ir2rgb_timer_cnt =0;
	return RTS_ISP_OK;
}

static int day_night_timer_rgb2ir_start(struct day_night_info *dn)
{
	dn->rgb2ir_timer_enable = TRUE;
	dn->rgb2ir_timer_cnt =0;
	return RTS_ISP_OK;
}

static int day_night_timer_rgb2ir_stop(struct day_night_info *dn)
{
	dn->rgb2ir_timer_enable = FALSE;
	dn->rgb2ir_timer_cnt =0;
	return RTS_ISP_OK;
}

static int day_night_set_result(struct day_night_info *dn)
{
	//printf("dn result current %d change %d \n",dn->result, dn->is_changing);
	if (!dn->is_changing)
		return RTS_ISP_OK;

	if (dn->result == RTS_ISP_NIGHT)
		dn->result = RTS_ISP_DAY;
	else
		dn->result = RTS_ISP_NIGHT;

	return RTS_ISP_OK;
}


static int day_night_timer_callback(isp_timer_handle_t *timer, void *data)
{
	struct isp_mod *mod = data;
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	struct day_night_info *dn = &rawstat->dn;

	if (!dn->is_changing)
		return RTS_ISP_OK;

	if (dn->result == RTS_ISP_NIGHT)
		dn->result = RTS_ISP_DAY;
	else
		dn->result = RTS_ISP_NIGHT;

	return RTS_ISP_OK;
}

static void day_night_process_statis(struct day_night_info *dn,
				     const struct rts_isp_raw_statis *statis)
{
	int i;

	dn->block_cnt = 0;
	if (dn->result == RTS_ISP_NIGHT) {
		for (i = 0; i < (int)dn->win_num; i++) {
			if (dn->iq->exit_ir_detect_table[i] &&
			    (statis->rg[i] <= dn->iq->exit_ir_gain_th ||
			     statis->bg[i] <= dn->iq->exit_ir_gain_th)) {
				dn->block_cnt++;
			}
		}
	}

}

static int day_night_detect(struct day_night_info *dn)
{

	if (dn->result == RTS_ISP_NIGHT) {
		uint8_t block_th;
		block_th = dn->iq->exit_ir_block_th * dn->win_num;


			if (dn->block_cnt > block_th &&
		    dn->etgain < dn->iq->exit_ir_etgain_th) {
			if (!dn->is_changing) {
				dn->is_changing = 1;
				//printf("block cnt %d th %d etgain %d th %d: night2day timer start\n", dn->block_cnt, block_th, dn->etgain, dn->iq->exit_ir_etgain_th);
				return day_night_timer_ir2rgb_start(dn);

				//return isp_timer_start(&dn->timer,
				//		       dn->iq->ir2rgb_time, 0);
			}
		} else {
			if (dn->is_changing) {
				dn->is_changing = 0;
				//printf("cnt %d th %d etgain %d th %d: night2day timer stop\n", dn->block_cnt, block_th, dn->etgain, dn->iq->exit_ir_etgain_th);
				return day_night_timer_ir2rgb_stop(dn);
				//return isp_timer_stop(&dn->timer);
			}
		}
	} else {

		if (dn->etgain > dn->iq->exit_rgb_etgain_th) {
			if (!dn->is_changing) {
				dn->is_changing = 1;
				//printf("etgain %d th %d: day2night timer start\n", dn->etgain, dn->iq->exit_rgb_etgain_th);
				return day_night_timer_rgb2ir_start(dn);
				//return isp_timer_start(&dn->timer,
				//		       dn->iq->rgb2ir_time, 0);
			}
		} else {
			if (dn->is_changing) {
				//printf("etgain %d th %d :day2night timer stop\n", __func__, dn->etgain, dn->iq->exit_rgb_etgain_th);
				dn->is_changing = 0;
				return day_night_timer_rgb2ir_stop(dn);
				//return isp_timer_stop(&dn->timer);
		}
	}
	}
	return RTS_ISP_OK;
}

static int rawstat_calc_pixels(struct isp_mod_rawstat *rawstat,
			       const rts_isp_grid_t *grid)
{
	rawstat->pixels_per_cell = (grid->cell.w * grid->cell.h /
				    rawstat->hw_info.cell_sample.w /
				    rawstat->hw_info.cell_sample.h);
	rawstat->fine_pixels = (rawstat->pixels_per_cell *
				grid->size.cols * grid->size.rows);
	return RTS_ISP_OK;
}

static int mod_rawstat_info_statis(struct isp_mod *mod, void *data)
{
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	struct isp_mod_rawstat_stat_info *info = data;

	info->info.win = rawstat->hw_info.grid_info.size;
	info->info.pixels_per_cell = rawstat->pixels_per_cell;
	info->info.fine_pixels = rawstat->fine_pixels;
	info->rgby_size = rawstat->hw_info.rgby_size;
	info->rgbg_size = rawstat->hw_info.rgbg_size;
	info->pixels_size = rawstat->hw_info.pixels_size;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info rawstat_info_actions[] = {
	ISP_MOD_ACTION(RAWSTAT_INFO_STATIS, mod_rawstat_info_statis),
};

static int mod_rawstat_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	const struct rts_isp_raw_statis *statis;
	struct day_night_info *dn = &rawstat->dn;
	statis = &((const struct rts_isp_statis *)data)->raw;
	day_night_process_statis(&rawstat->dn, statis);

	// change isp_timer to statis_done cnt
	if ( dn->result == RTS_ISP_NIGHT ) {
		if (dn->ir2rgb_timer_enable) {
			dn->ir2rgb_timer_cnt++;
			if ( dn->ir2rgb_timer_cnt >=  dn->iq->ir2rgb_time ) {
				day_night_set_result(dn);
				day_night_timer_ir2rgb_stop(dn);

			}
		}
	} else {
		if (dn->rgb2ir_timer_enable) {
			dn->rgb2ir_timer_cnt++;
			if ( dn->rgb2ir_timer_cnt >=  dn->iq->rgb2ir_time ) {
				day_night_set_result(dn);
				day_night_timer_ir2rgb_stop(dn);
			}
		}
	}

	//isp_info("%s \r\n",__func__);
	return day_night_detect(&rawstat->dn);
}

static int mod_rawstat_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);

	rawstat->dn.cur = *(enum rts_isp_day_night *)data;
	rawstat->dn.result = rawstat->dn.cur;
	rawstat->dn.iq = isp_iq_get_daynight(mod->owner_id);

	if (rawstat->dn.iq) {
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			return ret;
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
		if (ret)
			return ret;
		rawstat->dn.is_changing = 0;
	} else {
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			return ret;
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
	}
	//isp_info("%s done \r\n", __func__);
	return ret;
}

static int mod_rawstat_dynamic(struct isp_mod *mod, void *data)
{
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	struct isp_notify_dynamic *dyn = data;

	rawstat->dn.etgain = dyn->ae.exp_gain;

	return RTS_ISP_OK;
}

static int mod_rawstat_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	rts_isp_grid_t grid;
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	const rts_isp_rect_t *rect = data;

	ret = rts_isp_get_grid_from_rect(&grid, rect,
					 &rawstat->hw_info.grid_info);
	if (ret)
		return ret;
	ret = rawstat_calc_pixels(rawstat, &grid);
	if (ret)
		return ret;
	return rawstat->hw_ops->set_statis(mod->owner_id, &grid);
}

static struct isp_mod_action_info rawstat_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_rawstat_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_rawstat_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_rawstat_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_rawstat_mcrop_change),
};

static int isp_mod_rawstat_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_rawstat *rawstat;

	rawstat = get_mod(mod, rawstat);
	rawstat->hw_ops = isp_hw_rawstat_get_ops();
	if (rawstat->hw_ops == NULL) {
		isp_error("get rawstat hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto out;
	}

	ret = rawstat->hw_ops->get_hw_info(mod->owner_id, &rawstat->hw_info);
	if (ret)
		goto out;

	day_night_info_init(rawstat);

	ret = isp_timer_init(&rawstat->dn.timer, isp_top_get_poll(),
			     day_night_timer_callback, mod);
out:
	return ret;
}

static int isp_mod_rawstat_cleanup(struct isp_mod *mod)
{
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);

	isp_timer_cleanup(&rawstat->dn.timer);
	rawstat->dn.ir2rgb_timer_enable = FALSE;
	rawstat->dn.ir2rgb_timer_cnt = 0;
	rawstat->dn.ir2rgb_timer_enable = FALSE;
	rawstat->dn.ir2rgb_timer_cnt = 0;

	return RTS_ISP_OK;
}

static int rawstat_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);

	switch (ctrl->id) {
	case RTS_V4L2_CID_DAYNIGHT_DETECTION:
		rawstat->day_night_detect_ctrl->val = rawstat->dn.result;
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static const struct v4l2_ctrl_ops rawstat_ctrl_ops = {
	.g_volatile_ctrl = rawstat_g_volatile_ctrl,
};

static int isp_mod_rawstat_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_rawstat *rawstat = get_mod(mod, rawstat);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config get_dn_config = {
		.ops = &rawstat_ctrl_ops,
		.id = RTS_V4L2_CID_DAYNIGHT_DETECTION,
		.name = "Day Night Detect",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
		.flags = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_VOLATILE,
	};

	rawstat->day_night_detect_ctrl =
		rtsv_ctrl_new_custom(handler, &get_dn_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add rawstat ctrls fail");
		return handler->error;
	}

	return RTS_ISP_OK;
}

static struct isp_mod_rawstat rawstat;

int isp_register_mod_rawstat(void)
{
	memset(&rawstat, 0, sizeof(rawstat));
	rawstat.mod.id = MOD_RAWSTAT;
	rawstat.mod.name = "rawstat";
	rawstat.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_MCROP_CHANGE_BIT;
	rawstat.mod.init = isp_mod_rawstat_init;
	rawstat.mod.cleanup = isp_mod_rawstat_cleanup;
	rawstat.mod.add_ctrl = isp_mod_rawstat_add_ctrl;
	rawstat.mod.info_actions = rawstat_info_actions;
	rawstat.mod.info_actions_num = ARRAY_SIZE(rawstat_info_actions);
	rawstat.mod.notify_actions = rawstat_notify_actions;
	rawstat.mod.notify_actions_num = ARRAY_SIZE(rawstat_notify_actions);
	return isp_mod_register(&rawstat.mod);
}

void isp_unregister_mod_rawstat(void)
{
	isp_mod_unregister(&rawstat.mod);
}

