/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <math.h>
#include <rts_isp.h>
#include <rts_isp_ae.h>
#include <isp_top.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_algo.h>
#include <isp_driver.h>
#include <isp_notify.h>
#include <isp_statis.h>
#include <isp_v4l2_ctrl.h>
#include <isp_iq.h>
#include <isp_mod_sensor.h>
#include <isp_mod_ae.h>
#include <isp_mod_iq.h>
#include <isp_mod_crop.h>
#include <isp_hw_ae.h>
#include <isp_debug.h>
#include "rt_code.h"
#define ISP_DEBUG_TYPE ISP_DEBUG_AE

struct isp_mod_ae {
	struct isp_mod mod;
	const struct rts_isp_ae_algo *ae_algo;
	const struct isp_hw_ae_ops *hw_ops;
	struct isp_ae_hw_info hw_info;
	rts_isp_grid_t grid;

	enum rts_isp_sensor_hdr_mode hdr;
	float sensor_max_fps;
	float sensor_min_fps;
	float exposure_step;
	enum rts_isp_power_line_freq power_line_freq;
	const struct rts_isp_exp_gain_tune_ops *tune_ops;
	int algo_delay;

	struct rts_isp_ae_exp_gain exp_gain;
	float dyn_fps;
	float exp_ratio[RTS_ISP_HDR_CHAN_MAX - 1];
	float ratio[RTS_ISP_HDR_CHAN_MAX - 1];

	uint32_t hdr_phy_addr;

	struct {
		struct rts_isp_ae_auto_setting auto_setting;
		int auto_setting_has_set;
	};
	int patch_target_delta;

	const isp_iq_ae_t *iq;
	isp_algo_param_ae_t *algo_param;

	struct {
		enum rts_isp_ae_algo_status ae_status;
		uint8_t ae_stable_cnt;
	};

	struct {
		struct v4l2_ctrl *auto_gain_ctrl;
		struct v4l2_ctrl *exposure_ctrl;
		struct v4l2_ctrl *gain_ctrl;
	};
	struct v4l2_ctrl *exp_priority_ctrl;
	struct v4l2_ctrl *dyn_fps_ctrl;
	struct v4l2_ctrl *hdr_ctrl;
	struct {
		struct v4l2_ctrl *auto_hdr_ratio_ctrl;
		struct v4l2_ctrl *hdr_ratio_ctrl;
	};
	struct v4l2_ctrl *smart_ir_mode_ctrl;
	struct v4l2_ctrl *smart_ir_manual_level_ctrl;

	struct v4l2_ctrl *ae_min_fps_ctrl;
	struct v4l2_ctrl *ae_max_fps_ctrl;
	ae_fps_status_cb fps_change_cb;
	enum rts_isp_ae_dyn_hdr_mode dyn_hdr_mode;
	struct rts_ae_dbg_buf ae_algo_dbg_buf;
};

static uint8_t ae_algo_dbg_buf[ISP_DEBUG_INFO_LEN];

static int ae_algo_set_ctrls(struct isp_mod_ae *ae);

static int check_algo_version(uint32_t version)
{
	if (algo_magic(version) != AE_API_VERSION_MAGIC ||
	    algo_major_version(version) != AE_API_MAJOR_VERSION ||
	    algo_minor_version(version) > 0)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_algo(const struct rts_isp_ae_algo *ae_algo)
{
	if (!ae_algo || check_algo_version(ae_algo->api_version))
		return ERR_ID_MOD_AE_CHECK_ALGO_VER_FAIL;
	printf("ae ver 0x%08x \n",ae_algo->api_version);
	if (!ae_algo->init || !ae_algo->cleanup)
		return -RTS_ISP_EINVAL;
	if (!ae_algo->run || !ae_algo->ctrl)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static void ae_release_hdr_memory(struct isp_mod_ae *ae)
{
	if (ae->hdr_phy_addr) {
		isp_driver_mem_free(ae->hdr_phy_addr);
		ae->hdr_phy_addr = 0;
	}
}

static int ae_check_exp_gain(struct isp_mod_ae *ae,
			     const struct rts_isp_ae_exp_gain *exp_gain)
{
	int i;

	if (!ae || !exp_gain)
		return -RTS_ISP_EINVAL;
	for (i = 0; i < hdr_chan_num(ae->hdr); i++) {
		if (!isnormal(exp_gain->exposure[i]) ||
		    !isnormal(exp_gain->analog_gain[i]) ||
		    !isnormal(exp_gain->digital_gain[i]) ||
		    !isnormal(exp_gain->isp_hdr_gain[i]) ||
		    exp_gain->exposure[i] < ae->exposure_step ||
		    exp_gain->analog_gain[i] < 1.0f ||
		    exp_gain->digital_gain[i] < 1.0f ||
		    exp_gain->isp_hdr_gain[i] < 1.0f)

			{
				isp_error("%d %d %d %d %d %d %d %d\n",
				!isnormal(exp_gain->exposure[i]) ,
		    !isnormal(exp_gain->analog_gain[i]) ,
		    !isnormal(exp_gain->digital_gain[i]) ,
		    !isnormal(exp_gain->isp_hdr_gain[i]) ,
		    exp_gain->exposure[i] < ae->exposure_step ,
		    exp_gain->analog_gain[i] < 1.0f ,
		    exp_gain->digital_gain[i] < 1.0f ,
		    exp_gain->isp_hdr_gain[i] < 1.0f);
			isp_error("%d %f %f %f %f %f\n",i,
				exp_gain->exposure[i],
		    	exp_gain->analog_gain[i] ,
		    	exp_gain->digital_gain[i] ,
		    	exp_gain->isp_hdr_gain[i],
				ae->exposure_step);

				if (exp_gain->exposure[i] < ae->exposure_step)
					return ERR_ID_MOD_AE_EXP_TOO_SHORT;

				return ERR_ID_MOD_AE_CHECK_AE_EXP_GAIN_FAIL;}
	}
	if (!isnormal(exp_gain->isp_gain) || exp_gain->isp_gain < 1.0f)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static float ae_total_gain(struct isp_mod_ae *ae)
{
	return ae->exp_gain.analog_gain[0] * ae->exp_gain.digital_gain[0] *
	       ae->exp_gain.isp_hdr_gain[0] * ae->exp_gain.isp_gain;
}

static float ae_total_ratio(struct isp_mod_ae *ae)
{
	int i;
	float ratio = 1;

	for (i = 0; i < hdr_chan_num(ae->hdr) - 1; i++)
		ratio *= ae->exp_ratio[i];
	return ratio;
}

static void ae_set_exp_gain_unused(struct isp_mod_ae *ae,
				   struct rts_isp_ae_exp_gain *exp_gain)
{
	int i;

	for (i = hdr_chan_num(ae->hdr); i < RTS_ISP_HDR_CHAN_MAX; i++) {
		exp_gain->analog_gain[i] = exp_gain->analog_gain[i - 1];
		exp_gain->digital_gain[i] = exp_gain->digital_gain[i - 1];
		exp_gain->isp_hdr_gain[i] = exp_gain->isp_hdr_gain[i - 1];
	}
}

static int ae_tune_exposure_gain(struct isp_mod_ae *ae,
				 struct rts_isp_ae_exp_gain *exp_gain)
{
	int i;
	int ret;
	float min_hdr_gain;
	int num = hdr_chan_num(ae->hdr);
	float min_exposure[RTS_ISP_HDR_CHAN_MAX];
	float max_exposure[RTS_ISP_HDR_CHAN_MAX];
	float gain[RTS_ISP_HDR_CHAN_MAX];

	ret = ae_check_exp_gain(ae, exp_gain);
	if (ret) {
		isp_error("ae_tune_exposure_gain failed\n");
		return ret;
	}

	ret = ae->tune_ops->get_exposure_range(ae->mod.owner_id,
					       ae->dyn_fps, ae->exp_ratio,
					       min_exposure, max_exposure);
	if (ret)
		return ret;

	exp_gain->exposure[0] = clamp(exp_gain->exposure[0],
				      min_exposure[0], max_exposure[0]);
	for (i = 1; i < num; i++)
		exp_gain->exposure[i] =
			clamp(exp_gain->exposure[i - 1] / ae->exp_ratio[i - 1],
			      min_exposure[i], max_exposure[i]);

	isp_memcpy_array(gain, exp_gain->analog_gain, num);
	ret = ae->tune_ops->get_tuned_again(ae->mod.owner_id,
					    exp_gain->analog_gain);
	if (ret)
		return ret;
	for (i = 0; i < num; i++)
		exp_gain->digital_gain[i] *= gain[i] / exp_gain->analog_gain[i];
	isp_memcpy_array(gain, exp_gain->digital_gain, num);
	ret = ae->tune_ops->get_tuned_dgain(ae->mod.owner_id,
					    exp_gain->digital_gain);
	if (ret)
		return ret;
	for (i = 0; i < num; i++) {
		gain[i]  /= exp_gain->digital_gain[i];
	}
	min_hdr_gain = gain[0];
	for (i = 1; i < num; i++)
		min_hdr_gain = min(min_hdr_gain, gain[i]);
	exp_gain->isp_gain *= min_hdr_gain;

	ae_set_exp_gain_unused(ae, exp_gain);

	return RTS_ISP_OK;
}

static int ae_algo_prepare_info(struct isp_mod_ae *ae,
				struct rts_isp_ae_info *info)
{
	int i;
	const isp_iq_ae1_t *iq;

	info->stat_info.win = ae->hw_info.ae.grid_info.size;
	info->stat_info.hist_bins = ae->hw_info.ae.hist_bins;
	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		info->stat_info.hdr[i].win = ae->hw_info.hdr[i].grid_info.size;
		info->stat_info.hdr[i].hist_bins = ae->hw_info.hdr[i].hist_bins;
	}

	switch (ae->iq->which_algo) {
	case isp_iq_ae_t_ae1_tag:
		iq = &ae->iq->algo.ae1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	info->tune = ae->tune_ops;
	info->iq = iq;
	info->algo_param = ae->algo_param;

	return RTS_ISP_OK;
}

static int ae_algo_set_auto(struct isp_mod_ae *ae, int auto_mode)
{
	if (auto_mode) {
		int ret;

		ret = ae_algo_set_ctrls(ae);
		if (ret)
			return ret;
		return isp_mod_add_notify(&ae->mod, ISP_NOTIFY_STATIS_DONE);
	} else {
		return isp_mod_del_notify(&ae->mod, ISP_NOTIFY_STATIS_DONE);
	}
}

static int ae_algo_init(struct isp_mod_ae *ae)
{
	int ret;
	struct rts_isp_ae_info info;

	ret = isp_algo_get_ae(isp_top_get_algom(), ae->mod.owner_id,
			      &ae->ae_algo);
	if (ret)
		return ret;
	ret = check_algo(ae->ae_algo);
	if (ret)
		return ret;
	ret = ae_algo_prepare_info(ae, &info);
	//printf("%s: ret=%d\n", __func__, ret);
	if (ret)
		return ret;
	return ae->ae_algo->init(ae->mod.owner_id, &info);
}

static int ae_algo_cleanup(struct isp_mod_ae *ae)
{
	if (ae->ae_algo) {
		ae->ae_algo->cleanup(ae->mod.owner_id);
		ae->ae_algo = NULL;
	}
	//if (ae->ae_algo_dbg_buf.buf_len) {
	//	ae->ae_algo_dbg_buf.buf_len = 0;
	//	ae->ae_algo_dbg_buf.buf_ptr = NULL;
	//}
	return RTS_ISP_OK;
}

static int ae_algo_set_api_ctrls(struct isp_mod_ae *ae,
				 const struct rts_isp_ae_auto_setting *setting)
{
	int ret;
	float gain_max = setting->gain_max / 16.0f;
	float min_fps = setting->min_fps;

	if (!ae->auto_setting_has_set)
		return RTS_ISP_OK;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_WIN_WEIGHTS,
				setting->win_weights);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_TARGET_DELTA,
				(void *)&setting->target_delta);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_GAIN_MAX, &gain_max);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_SENSOR_MIN_FPS, &min_fps);
	if (ret)
		return ret;
	//Not Supported
	//ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_EXPOSURE_MAX, &max_et);
	return ret;
}

static int ae_algo_set_ctrls(struct isp_mod_ae *ae)
{
	int ret;
	struct rts_isp_ae_ratio_range range;
	int ratio;
	float max_fps = ae->ae_max_fps_ctrl->cur.val;
	float min_fps = ae->ae_min_fps_ctrl->cur.val;

	min_fps = max(ae->sensor_min_fps, min_fps);

	range.min_ratio = ae->hdr_ratio_ctrl->minimum;
	range.max_ratio = ae->hdr_ratio_ctrl->maximum;
	ratio = ae->auto_hdr_ratio_ctrl->val ? 0 : ae->hdr_ratio_ctrl->val;
	if (ae->exp_gain.hdr != ae->hdr)
		printf("ae hdr: %d, sensor hdr: %d\n\r", ae->exp_gain.hdr, ae->hdr);
	ae->exp_gain.hdr = ae->hdr;

	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_SENSOR_BASE_FPS, &ae->sensor_max_fps);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_MAX_FPS,
				&max_fps);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_MIN_FPS,
				&min_fps);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_POWER_LINE_FREQ,
				&ae->power_line_freq);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_EXP_GAIN, &ae->exp_gain);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_EXPOSURE_UNIT,
				&ae->exposure_step);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_DYNAMIC_FPS_ENABLE,
				&ae->exp_priority_ctrl->cur.val);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_DYNAMIC_HDR_MODE,
				&ae->hdr_ctrl->cur.val);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_HDR_RATIO_RANGE, &range);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_HDR_RATIO, &ratio);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_SORT_MODE,
				&ae->smart_ir_mode_ctrl->cur.val);
	if (ret)
		return ret;
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_SORT_MANUAL_LEVEL,
				&ae->smart_ir_manual_level_ctrl->cur.val);
	if (ret)
		return ret;

	if (ae->ae_algo_dbg_buf.buf_ptr == NULL) {
		ae->ae_algo_dbg_buf.buf_ptr = &ae_algo_dbg_buf[0];
		ae->ae_algo_dbg_buf.buf_len = ISP_DEBUG_INFO_LEN;
	}
	ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_AE_DBG_BUF,
				&ae->ae_algo_dbg_buf);
	if (ret)
		return ret;

	return ae_algo_set_api_ctrls(ae, &ae->auto_setting);
}

static int ae_algo_update(struct isp_mod_ae *ae)
{
	int ret;

	ret = ae_algo_cleanup(ae);
	if (ret)
		return ret;
	ret = ae_algo_init(ae);
	if (ret)
		return ret;
	if (ae->auto_gain_ctrl)
		return ae_algo_set_ctrls(ae);
	return RTS_ISP_OK;
}

static int ae_algo_need_delay(struct isp_mod_ae *ae)
{

	if (ae->algo_delay) {
		ae->algo_delay--;
		return RTS_ISP_TRUE;
	}
	return RTS_ISP_FALSE;
}

static int mod_ae_info_statis(struct isp_mod *mod, void *data)
{
	int i;
	struct isp_mod_ae *ae = get_mod(mod, ae);
	struct isp_mod_ae_stat_info *info = data;

	info->info.win = ae->hw_info.ae.grid_info.size;
	info->info.hist_bins = ae->hw_info.ae.hist_bins;
	info->win_mean_size = ae->hw_info.ae.y_mean_size;
	info->hist_bin_size = ae->hw_info.ae.hist_bin_size;

	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		info->info.hdr[i].win = ae->hw_info.hdr[i].grid_info.size;
		info->info.hdr[i].hist_bins = ae->hw_info.hdr[i].hist_bins;
		info->hdr[i].win_mean_size = ae->hw_info.hdr[i].y_mean_size;
		info->hdr[i].hist_bin_size = ae->hw_info.hdr[i].hist_bin_size;
	}

	return RTS_ISP_OK;
}

static int mod_ae_info_exposure(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	*(float *)data = ae->exp_gain.exposure[0];

	return RTS_ISP_OK;
}

static int mod_ae_info_status(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	*(enum rts_isp_ae_algo_status *)data = ae->ae_status;

	return RTS_ISP_OK;
}

static int mod_ae_info_gain(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	*(float *)data = ae_total_gain(ae);

	return RTS_ISP_OK;
}

static int mod_ae_info_version(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	uint16_t *version = data;

	*version = ae->ae_algo->api_version & AE_VERSION_MASK;

	return RTS_ISP_OK;
}

static int mod_ae_info_target(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	const isp_iq_ae1_t *iq;

	switch (ae->iq->which_algo) {
	case isp_iq_ae_t_ae1_tag:
		iq = &ae->iq->algo.ae1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	*(uint16_t *)data = iq->y_mean_target;

	return RTS_ISP_OK;
}

static int mod_ae_info_debug_buf(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	uint8_t *debug_buf = data;

	if (debug_buf != NULL && ae->ae_algo_dbg_buf.buf_ptr != NULL) {
		memcpy(debug_buf, ae->ae_algo_dbg_buf.buf_ptr, ISP_DEBUG_INFO_LEN);
		return RTS_ISP_OK;
	} else {
		return -RTS_ISP_EINVAL;
	}
}

static struct isp_mod_action_info ae_info_actions[] = {
	ISP_MOD_ACTION(AE_INFO_STATIS, mod_ae_info_statis),
	ISP_MOD_ACTION(AE_INFO_EXPOSURE, mod_ae_info_exposure),
	ISP_MOD_ACTION(AE_INFO_STATUS, mod_ae_info_status),
	ISP_MOD_ACTION(AE_INFO_GAIN, mod_ae_info_gain),
	ISP_MOD_ACTION(AE_INFO_VERSION, mod_ae_info_version),
	ISP_MOD_ACTION(AE_INFO_TARGET, mod_ae_info_target),
	ISP_MOD_ACTION(AE_INFO_DEBUG_BUF, mod_ae_info_debug_buf),
};

static int ae_notify_exp_gain_change(struct isp_mod_ae *ae)
{
	int i;
	struct isp_notify_dynamic_ae dyn;
	float ratio;

	dyn.num = hdr_chan_num(ae->hdr);
	isp_memcpy_array(dyn.exposure, ae->exp_gain.exposure, dyn.num);
	isp_memcpy_array(dyn.analog_gain, ae->exp_gain.analog_gain, dyn.num);
	isp_memcpy_array(dyn.digital_gain, ae->exp_gain.digital_gain, dyn.num);
	isp_memcpy_array(dyn.isp_hdr_gain, ae->exp_gain.isp_hdr_gain, dyn.num);
	dyn.isp_gain = ae->exp_gain.isp_gain;

	for (i = 0; i < dyn.num; i++) {
		dyn.sensor_gain[i] = dyn.analog_gain[i] * dyn.digital_gain[i];
		dyn.total_gain[i] = (dyn.sensor_gain[i] * dyn.isp_hdr_gain[i] *
				     dyn.isp_gain);
		dyn.iq_sensor_gain[i] = dyn.sensor_gain[i] * 16;
		dyn.iq_total_gain[i] = dyn.total_gain[i] * 16;
		dyn.iq_exp_gain[i] = dyn.exposure[i] * dyn.total_gain[i] / 100;
		if (i) {
			ratio =
				((dyn.exposure[i - 1] * dyn.total_gain[i - 1]) /
				 (dyn.exposure[i] * dyn.total_gain[i]));
			ratio = clamp(ratio, AE_MIN_RATIO, AE_MAX_RATIO);
			ratio = pow(2, round(log2(ratio)));
			dyn.iq_ratio[i] = ratio;
		}
	}
	ratio = ((dyn.exposure[0] * dyn.total_gain[0]) /
			   (dyn.exposure[dyn.num - 1] *
			    dyn.total_gain[dyn.num - 1]));
	ratio = clamp(ratio, AE_MIN_RATIO, AE_MAX_RATIO);
	ratio = pow(2, round(log2(ratio)));
	dyn.iq_ratio[0] = ratio;

	// Make sure the iq ratio is same as fusion
	dyn.iq_ratio[0] = clamp(dyn.iq_ratio[0], AE_MIN_RATIO, AE_MAX_RATIO);
	dyn.iq_ratio[0] = pow(2, round(log2(dyn.iq_ratio[0])));

	for (i = dyn.num; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		dyn.exposure[i] = dyn.exposure[i - 1];
		dyn.analog_gain[i] = dyn.analog_gain[i - 1];
		dyn.digital_gain[i] = dyn.digital_gain[i - 1];
		dyn.isp_hdr_gain[i] = dyn.isp_hdr_gain[i - 1];
		dyn.sensor_gain[i] = dyn.sensor_gain[i - 1];
		dyn.total_gain[i] = dyn.total_gain[i - 1];
		dyn.iq_sensor_gain[i] = dyn.iq_sensor_gain[i - 1];
		dyn.iq_total_gain[i] = dyn.iq_total_gain[i - 1];
		dyn.iq_exp_gain[i] = dyn.iq_exp_gain[i - 1];
		dyn.iq_ratio[i] = 1;
	}

	dyn.gain = dyn.total_gain[0] * 16;
	dyn.exp_gain = dyn.exposure[0] * dyn.total_gain[0] / 100;

	dyn.hdr_mode = ae->hdr;

	return isp_mod_sibling_execute(&ae->mod, MOD_IQ, IQ_EXEC_SET_DYNAMIC_AE,
				       &dyn, sizeof(dyn));
}

static int ae_set_fine_exp_gain(struct isp_mod_ae *ae,
				const struct rts_isp_ae_exp_gain *exp_gain,
				float fps)
{
	int ret;
	struct isp_sensor_exp_gain snr_exp_gain;

	ret = ae_check_exp_gain(ae, exp_gain);
	if (ret != 0) {
		return ret;
	}
	if (fps < ae->sensor_min_fps || fps > ae->sensor_max_fps) {
		isp_error("ae_set_fine_exp_gain failed min_fps=%f", ae->sensor_min_fps);
		return ERR_ID_MOD_AE_AE_FPS_OUT_RANGE;
	}

	/* we trust exp_gain here */
	snr_exp_gain.exp_gain = exp_gain;
	snr_exp_gain.fps = fps;
	snr_exp_gain.isp_sync_num = 16;
	snr_exp_gain.get_sync_regs_cb = ae->hw_ops->get_sync_regs;

	ret = isp_mod_sibling_execute(&ae->mod, MOD_SENSOR,
				      SENSOR_EXEC_SET_EXP_GAIN, &snr_exp_gain,
				      sizeof(snr_exp_gain));
	if (ret)
		return ret;

	if (float_ne(ae->dyn_fps, fps)) {
#ifdef _FPS_LOG_
		printf("%s ae->dyn_fps %.2f fps %.2f \n", __func__, ae->dyn_fps, fps);
#endif
		if (float_eq(ae->dyn_fps, 0.0f))
			return RTS_ISP_OK;
		ret = isp_driver_notify_dynamic_fps(fps);   // [To Be comfirm with PC] use to-be-update fps
		if (ret)
			return ret;
	}

	ae->exp_gain = *exp_gain;
	ae->dyn_fps = fps;

	ae_notify_exp_gain_change(ae);

	return RTS_ISP_OK;
}

static int ae_clone_iq_to_setting(struct isp_mod_ae *ae)
{

	struct rts_isp_ae_auto_setting *setting = &ae->auto_setting;
	int win_num = (ae->hw_info.ae.grid_info.size.cols *
		       ae->hw_info.ae.grid_info.size.rows);

	const isp_iq_ae1_t *iq;

	switch (ae->iq->which_algo) {
	case isp_iq_ae_t_ae1_tag:
		iq = &ae->iq->algo.ae1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	if (ae->auto_setting_has_set)
		return RTS_ISP_OK;

	isp_assert(win_num == ARRAY_SIZE(iq->win_weight));
	if (!setting->window_num) {
		void *weight = isp_malloc(sizeof(iq->win_weight));

		if (!weight)
			return -RTS_ISP_ENOMEM;
		set_const_var(setting->window_num, win_num);
		set_const_var_type(uint8_t *, setting->win_weights, weight);
	}
	memcpy(setting->win_weights, iq->win_weight,
	       sizeof(iq->win_weight));
	setting->target_delta = ae->patch_target_delta;
	setting->gain_max = iq->total_gain_max;
	if (!ae->ae_min_fps_ctrl)
		setting->min_fps = iq->dyn_fps_min;
	else
		setting->min_fps = ae->ae_min_fps_ctrl->val;
	setting->max_exposure = 1e6f / setting->min_fps;

	return RTS_ISP_OK;
}

static int ae_set_auto_setting(struct isp_mod_ae *ae,
			       const struct rts_isp_ae_auto_setting *setting)
{
	struct rts_isp_ae_auto_setting *current = &ae->auto_setting;
	struct isp_ae_hw_info *info = &ae->hw_info;
	int win_num = (info->ae.grid_info.size.cols *
		       info->ae.grid_info.size.rows);
	int ret = RTS_ISP_OK;

	if (setting->window_num != win_num || !setting->win_weights)
		return -RTS_ISP_EINVAL;

	ae->auto_setting_has_set = RTS_ISP_TRUE;
	ret = ae_algo_set_api_ctrls(ae, setting);
	if (ret) {
		isp_perror(ret, "set ae setting ctrl fail");
		return ret;
	}

	memcpy(current->win_weights, setting->win_weights,
	       win_num * sizeof(*current->win_weights));
	current->target_delta = setting->target_delta;
	current->gain_max = setting->gain_max;
	current->min_fps = setting->min_fps;
	current->max_exposure = setting->max_exposure;

	return RTS_ISP_OK;
}

static int ae_set_manual_setting(struct isp_mod_ae *ae,
		const struct rts_isp_ae_manual_setting *setting)
{
	int i;
	int ret;
	uint16_t exposure;
	uint16_t gain;
	uint16_t analog_gain;
	uint16_t digital_gain;
	uint16_t isp_gain;
	struct rts_isp_ae_exp_gain exp_gain = ae->exp_gain;

	exposure = rtsv_ctrl_g_ctrl(ae->exposure_ctrl);
	gain = rtsv_ctrl_g_ctrl(ae->gain_ctrl);
	isp_gain = ae->exp_gain.isp_gain * 256;
	analog_gain = ae->exp_gain.analog_gain[0] * 256;
	digital_gain = ae->exp_gain.digital_gain[0] * 256;

	/* TODO: ae setting API support hdr */
	if (float_ne(setting->exposure_time, exposure)) {
		exp_gain.exposure[0] = setting->exposure_time;
		for (i = 0; i < hdr_chan_num(ae->hdr) - 1; i++)
			exp_gain.exposure[i + 1] =
				exp_gain.exposure[i] / ae->exp_ratio[i];
	}
	if (setting->gain.analog_gain != analog_gain ||
	    setting->gain.digital_gain != digital_gain ||
	    setting->gain.isp_gain != isp_gain) {
		for (i = 0; i < hdr_chan_num(ae->hdr); i++) {
			exp_gain.analog_gain[i] =
				setting->gain.analog_gain / 256.0f;
			exp_gain.digital_gain[i] =
				setting->gain.digital_gain / 256.0f;
		}
		exp_gain.isp_gain = setting->gain.isp_gain / 256.0f;
	} else if (float_ne(setting->total_gain, gain)) {
		for (i = 0; i < hdr_chan_num(ae->hdr); i++) {
			exp_gain.analog_gain[i] = setting->total_gain / 256.0f;
			exp_gain.digital_gain[i] = 1.0f;
		}
		exp_gain.isp_gain = 1.0f;
	}

	ret = ae_tune_exposure_gain(ae, &exp_gain);
	if (ret)
		return ret;
	//printf("%s ae->dyn_fps %.2f \n", __func__, ae->dyn_fps);
	ret = ae_set_fine_exp_gain(ae, &exp_gain, ae->dyn_fps);
	if (ret)
		{
			isp_error("ae_set_fine_exp_gain failed");
			return ret;}

	ae->exposure_ctrl->cur.val = ae->exp_gain.exposure[0];
	ae->gain_ctrl->cur.val = ae_total_gain(ae) * 256;

	return RTS_ISP_OK;
}

static int ae_ctrl_modify_ae_min_max_fps(struct isp_mod_ae *ae)
{
	int ret;

	ret = rtsv_ctrl_modify_range(ae->ae_min_fps_ctrl,
								ae->sensor_min_fps,
								ae->sensor_max_fps, 1,
								clamp(ae->ae_min_fps_ctrl->val,
								ae->sensor_min_fps,
								ae->sensor_max_fps));
	if (ret)
		return ret;

	ret = rtsv_ctrl_modify_range(ae->ae_max_fps_ctrl,
								ae->ae_min_fps_ctrl->val,
								ae->sensor_max_fps, 1,
								clamp(ae->ae_max_fps_ctrl->val,
								ae->ae_min_fps_ctrl->val,
								ae->sensor_max_fps));
	return ret;
}

static int ae_ctrl_modify_range(struct isp_mod_ae *ae)
{
	int ret;
	float min_exposure[RTS_ISP_HDR_CHAN_MAX];
	float max_exposure[RTS_ISP_HDR_CHAN_MAX];

	ret = ae->tune_ops->get_exposure_range(ae->mod.owner_id, ae->dyn_fps,
					       ae->exp_ratio, min_exposure,
					       max_exposure);
	if (ret)
		return ret;
	ret = rtsv_ctrl_modify_range(ae->exposure_ctrl,
				     ceilf(min_exposure[0]),
				     floorf(max_exposure[0]),
				     1, clamp(ae->iq->def_exposure,
					      ceilf(min_exposure[0]),
					      floorf(max_exposure[0])));
	if (ret)
		return ret;
	return rtsv_ctrl_modify_range(ae->dyn_fps_ctrl,
				      ae->sensor_min_fps * SENSOR_FPS_PRECISION,
				      ae->sensor_max_fps * SENSOR_FPS_PRECISION,
				      1, ae->sensor_max_fps * SENSOR_FPS_PRECISION);
}

static int mod_ae_exec_set_plfreq(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ae->power_line_freq = *(enum rts_isp_power_line_freq *)data;

	ret = ae->ae_algo->ctrl(mod->owner_id, SET_POWER_LINE_FREQ,
				&ae->power_line_freq);
	if (ret)
		isp_perror(ret, "set power line freq fail");
	return ret;
}

static int mod_ae_exec_get_setting(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	struct rts_isp_ae_setting *setting = data;
	struct rts_isp_ae_auto_setting *auto_setting = &ae->auto_setting;

	isp_assert(auto_setting->window_num);
	isp_assert(auto_setting->window_num == setting->_auto.window_num);

	setting->mode = (enum rts_isp_ae_mode)rtsv_ctrl_g_ctrl(ae->auto_gain_ctrl);

	memcpy(setting->_auto.win_weights, auto_setting->win_weights,
	       auto_setting->window_num * sizeof(*auto_setting->win_weights));
	setting->_auto.gain_max = auto_setting->gain_max;
	setting->_auto.min_fps = auto_setting->min_fps;
	setting->_auto.max_exposure = auto_setting->max_exposure;
	if (ae->auto_setting_has_set)
		setting->_auto.target_delta = auto_setting->target_delta;
	else
		setting->_auto.target_delta = ae->patch_target_delta;

	setting->_manual.exposure_time = rtsv_ctrl_g_ctrl(ae->exposure_ctrl);
	setting->_manual.total_gain = rtsv_ctrl_g_ctrl(ae->gain_ctrl);
	setting->_manual.gain.analog_gain = ae->exp_gain.analog_gain[0] * 256;
	setting->_manual.gain.digital_gain = ae->exp_gain.digital_gain[0] * 256;
	setting->_manual.gain.isp_gain = ae->exp_gain.isp_gain * 256;

	return RTS_ISP_OK;
}

static int mod_ae_exec_set_setting(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ae *ae = get_mod(mod, ae);
	struct rts_isp_ae_setting *setting = data;

	if (setting->mode != RTS_ISP_AE_AUTO_MODE &&
	    setting->mode != RTS_ISP_AE_MANUAL_MODE)
		return ERR_ID_MOD_AE_INVALID_MODE;

	ret = rtsv_ctrl_s_ctrl(ae->auto_gain_ctrl, setting->mode);
	if (ret)
		return ret;
	if (setting->mode == RTS_ISP_AE_AUTO_MODE)
		ret = ae_set_auto_setting(ae, &setting->_auto);
	else
		ret = ae_set_manual_setting(ae, &setting->_manual);
	if (ret)
		return ret;
	return mod_ae_exec_get_setting(mod, setting);
}

static int mod_ae_exec_set_target_delta(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ae->patch_target_delta = *(int *)data;
	if (!ae->auto_setting_has_set)
		ae->ae_algo->ctrl(mod->owner_id, SET_TARGET_DELTA,
				  &ae->patch_target_delta);
	return RTS_ISP_OK;
}

static int mod_ae_exec_set_fps_change_cb(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	ae_fps_status_cb *cb = data;

	if(*cb)
		ae->fps_change_cb = *cb;
	else
		return RTS_ISP_EPERM;

	return RTS_ISP_OK;
}

static int mod_ae_exec_set_dyn_vhdr_mode(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ae->dyn_hdr_mode = *(enum rts_isp_ae_dyn_hdr_mode *)data;

	ret = ae->ae_algo->ctrl(mod->owner_id, SET_DYNAMIC_HDR_MODE,
				&ae->dyn_hdr_mode);
	if (ret)
		isp_perror(ret, "set dynamic vhdr fail");
	return ret;
}

static int mod_ae_exec_get_max_dyn_region(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	*(enum rts_isp_ae_region *)data = ae->algo_param->cur_drc_region;
	return ret;
}

static int mod_ae_exec_set_max_dyn_region_enable(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ret = ae->ae_algo->ctrl(mod->owner_id, SET_MAX_DYN_REGION_ENABLE,
		(uint8_t *)data);
	if (ret)
		isp_perror(ret, "set max dynamic region enable fail");
	return ret;
}

static struct isp_mod_action_info ae_exec_actions[] = {
	ISP_MOD_ACTION(AE_EXEC_SET_PLFREQ, mod_ae_exec_set_plfreq),
	ISP_MOD_ACTION(AE_EXEC_GET_SETTING, mod_ae_exec_get_setting),
	ISP_MOD_ACTION(AE_EXEC_SET_SETTING, mod_ae_exec_set_setting),
	ISP_MOD_ACTION(AE_EXEC_SET_TARGET_DELTA, mod_ae_exec_set_target_delta),
	ISP_MOD_ACTION(AE_EXEC_SET_FPS_CHANGE_CB, mod_ae_exec_set_fps_change_cb),
	ISP_MOD_ACTION(AE_EXEC_SET_DYN_VHDR_MODE, mod_ae_exec_set_dyn_vhdr_mode),
	ISP_MOD_ACTION(AE_EXEC_GET_MAX_DYN_REGION, mod_ae_exec_get_max_dyn_region),
	ISP_MOD_ACTION(AE_EXEC_SET_MAX_DYN_REGION_ENABLE, mod_ae_exec_set_max_dyn_region_enable),
};

static int ae_set_result(struct isp_mod_ae *ae,
			 struct rts_isp_ae_result *result)
{
	int i;
	int ret = RTS_ISP_OK;
	struct rts_isp_ae_exp_gain *exp_gain;

	if (!ae->exp_priority_ctrl->val)
		result->dyn_fps = ae->sensor_max_fps;
	exp_gain = &result->exp_gain;
	//printf("%s ae->dyn_fps %.2f \n", __func__, result->dyn_fps);
	ret = ae_set_fine_exp_gain(ae, exp_gain, result->dyn_fps);
	if (ret)
			goto out;
	// confirm with PC2, HDR only use single exposure setting.
	for (i = 0; i < ARRAY_SIZE(ae->exp_ratio); i++)
		ae->exp_ratio[i] = (exp_gain->exposure[i] /
					exp_gain->exposure[i + 1]);
out:
	if (ret)
		isp_perror(ret, "isp set result fail");
	return ret;
}

static int mod_ae_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ae *ae = get_mod(mod, ae);
	struct rts_isp_sensor_again sensor_again;
	const struct rts_isp_ae_statis *statis;
	struct rts_isp_ae_result result;

	if (ae_algo_need_delay(ae) || !ae->ae_algo)
		return RTS_ISP_OK;

	result.need_update = RTS_ISP_FALSE;
	statis = &((const struct rts_isp_statis *)data)->ae;
	ret = ae->ae_algo->run(mod->owner_id, statis, &result);
	if (ret) {
		isp_perror(ret, "ae algo run fail");
		return ret;
	}

	result.exp_gain.isp_hdr_gain[0] = 1.0f;
	result.exp_gain.isp_hdr_gain[1] = 1.0f;

	if (result.need_update) {
		if (result.exp_gain.hdr != ae->hdr &&
		    result.exp_gain.hdr != LINEAR_MODE) {
			ret = ERR_ID_MOD_AE_HDR_MODE_OUT_RANGE;
			isp_perror(ret, "hdr mode range error");
			return ret;
		}

		if (ae->fps_change_cb && ae->dyn_fps != result.dyn_fps)
			ae->fps_change_cb(result.dyn_fps);

		ae->ae_status = AE_UNSTABLE;
		ae->ae_stable_cnt = 0;
		/* we trust algo result, so do not tune it here */
		ae_set_exp_gain_unused(ae, &result.exp_gain);
		ret = ae_set_result(ae, &result);
		if (ret) {
			isp_perror(ret, "set ae result fail");
			return ret;
		}
	} else {
		if (ae->ae_stable_cnt < 4)
			ae->ae_stable_cnt++;
		else
			ae->ae_status = AE_STABLE;
	}

	/* Sensor Temperature Control */
	if(ae->hdr == LINEAR_MODE && !result.need_update) {
		// TODO: add an iq item to control if enable this feature or not
		sensor_again.total_gain = ae_total_gain(ae);
		sensor_again.again_val = 1.0f;
		sensor_again.isp_gain_val = 1.0f;

		ret = isp_mod_sibling_execute(&ae->mod, MOD_SENSOR, SENSOR_EXEC_SET_GAIN,
				       &sensor_again, sizeof(sensor_again));
		if (ret)
			return ret;
	}

	return RTS_ISP_OK;
}

static int mod_ae_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_sensor_mode mode;
	memset(&mode, 0, sizeof(mode));
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		return ret;

	ae->hdr = mode.hdr;
	ae->sensor_min_fps = mode.min_fps;
	ae->sensor_max_fps = mode.max_fps;
	if (hal_isp_get_init_frame_rate() == 0)
		ae->dyn_fps = mode.max_fps;
	else
		ae->dyn_fps = (float)hal_isp_get_init_frame_rate();
	ae->exposure_step = mode.exposure_step;

	ae->exp_gain.hdr = ae->hdr;

	ae->ratio[0] = ae->exp_ratio[0] = AE_DEF_RATIO;

	printf("min_fps %f, max_fps %f, exp_step %f dyn_fps %f\n",
				ae->sensor_min_fps, ae->sensor_max_fps, mode.exposure_step, ae->dyn_fps);

	if (mode.hdr != LINEAR_MODE) {
		ret = ae->hw_ops->set_hdr(mod->owner_id);
		if (ret) {
			return ret;
		}
	}

	return RTS_ISP_OK;
}

static int mod_ae_fps_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ae *ae = get_mod(mod, ae);
	float fps = *(float *)data;

	ae->algo_delay = ae->iq->algo_delay;

	if ( ae->dyn_fps == ae->sensor_max_fps) {
		ae->dyn_fps = fps;
	}
	ae->sensor_max_fps = fps;

	ret = ae_ctrl_modify_ae_min_max_fps(ae);
	if (ret)
		return ret;
#ifdef _FPS_LOG_
	printf("%s dyn_fps %.2f min %.2f max %.2f fps %.2f\n", __func__, ae->dyn_fps, ae->sensor_min_fps, ae->sensor_max_fps, fps);
#endif
	ae->dyn_fps = clamp(ae->dyn_fps, ae->sensor_min_fps,
						ae->sensor_max_fps);

	ret = ae_ctrl_modify_range(ae);
	if (ret)
		return ret;
	ret = ae_tune_exposure_gain(ae, &ae->exp_gain);
	if (ret)
		return ret;
#ifdef _FPS_LOG_
	printf("%s ae->dyn_fps %.2f fps %.2f \n", __func__, ae->dyn_fps, fps);
#endif
	ret = ae_set_fine_exp_gain(ae, &ae->exp_gain, ae->dyn_fps);
	if (ret)
		return ret;
	if (ae->dyn_fps > ae->ae_max_fps_ctrl->cur.val ) {
		ae->ae_max_fps_ctrl->cur.val = ae->dyn_fps;
	}
	return ae_algo_set_ctrls(ae);
}

static int mod_ae_algo_update(struct isp_mod *mod, void *data)
{
	uint32_t notify_data;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	notify_data = *(uint32_t *)data;
	if (!(notify_data & ISP_ALGO_AE_CHANGE_BIT))
		return RTS_ISP_OK;

	return ae_algo_update(ae);
}

static int mod_ae_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ae->iq = isp_iq_get_ae(mod->owner_id);
	if (!ae->iq) {
		isp_error("get ae iq fail\n");
		return -RTS_ISP_ENOITEM;
	}

	ret = ae_algo_update(ae);
	if (ret)
		return ret;

	if (ae->auto_gain_ctrl) {
		//isp_error("auto_gain_ctrl\n");
		ret = rtsv_ctrl_s_ctrl(ae->auto_gain_ctrl, ae->iq->enable);
		//isp_error("v4l2_ctrl_s_ctrl %d\n", ret);
		if (ret)
			return ret;
	}

	ret = ae_clone_iq_to_setting(ae);
	return ret;
}

static int mod_ae_start_pre(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	return ae->hw_ops->enable_hdr(mod->owner_id,
				      ae->hdr != LINEAR_MODE);
}

static int mod_ae_stop_pre(struct isp_mod *mod, void *data)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	return ae->hw_ops->enable_hdr(mod->owner_id, RTS_ISP_FALSE);
}

static int mod_ae_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_ae *ae = get_mod(mod, ae);
	const rts_isp_rect_t *rect = data;

	ret = rts_isp_get_grid_from_rect(&ae->grid, rect,
					 &ae->hw_info.ae.grid_info);
	if (ret)
		return ret;
	return ae->hw_ops->set_statis(mod->owner_id, &ae->grid);
}


static struct isp_mod_action_info ae_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_ae_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_ALGO_UPDATE, mod_ae_algo_update),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_ae_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_ae_mode_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_FPS_CHANGE, mod_ae_fps_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_ae_mcrop_change),
	// ISP_NOTIFY_ACTION(ISP_NOTIFY_START_POST_PRE, mod_ae_start_pre),
	// ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_PRE_PRE, mod_ae_stop_pre),
};

static int ae_set_exp_gain_ctrl(struct isp_mod_ae *ae, int dyn_hdr)
{
	int i;
	int ret;
	struct rts_isp_ae_exp_gain exp_gain;

	exp_gain.hdr = (enum rts_isp_sensor_hdr_mode)dyn_hdr;
	exp_gain.exposure[0] = ae->exposure_ctrl->val;
	for (i = 0; i < hdr_chan_num(ae->hdr) - 1; i++)
		exp_gain.exposure[i + 1] =
			exp_gain.exposure[i] / ae->exp_ratio[i];
	for (i = 0; i < hdr_chan_num(ae->hdr); i++) {
		exp_gain.analog_gain[i] = ae->gain_ctrl->val / 256.0f;
		exp_gain.digital_gain[i] = 1.0f;
		exp_gain.isp_hdr_gain[i] = 1.0f;
	}
	exp_gain.isp_gain = 1.0f;
	ret = ae_tune_exposure_gain(ae, &exp_gain);
	if (ret)
		return ret;
#ifdef _FPS_LOG_
	printf("%s ae->dyn_fps %.2f \n", __func__, ae->dyn_fps);
#endif
	return ae_set_fine_exp_gain(ae, &exp_gain, ae->dyn_fps);
}

static int ae_set_hdr_ctrl(struct isp_mod_ae *ae)
{
	int hdr;

	if (ae->hdr == LINEAR_MODE)
		return RTS_ISP_OK;

	if (ae->auto_gain_ctrl->val)
		return ae->ae_algo->ctrl(ae->mod.owner_id, SET_DYNAMIC_HDR_MODE,
					 &ae->hdr_ctrl->val);

	hdr = ae->hdr_ctrl->val == 0 ?  LINEAR_MODE : ae->hdr;
	return ae_set_exp_gain_ctrl(ae, hdr);
}

static int ae_set_hdr_ratio_ctrl(struct isp_mod_ae *ae)
{
	int i;
	int ret;
	float ratio;
	int back_exposure;
	float back_ratio[RTS_ISP_HDR_CHAN_MAX - 1];
	float back_exp_ratio[RTS_ISP_HDR_CHAN_MAX - 1];

	if (ae->hdr == LINEAR_MODE)
		return RTS_ISP_OK;

	if (ae->auto_gain_ctrl->val) {
		int val;

		if (ae->auto_hdr_ratio_ctrl->val)
			val = 0;
		else
			val = ae->hdr_ratio_ctrl->val;
		return ae->ae_algo->ctrl(ae->mod.owner_id, SET_HDR_RATIO, &val);
	}

	if (!ae->hdr_ratio_ctrl->is_new)
		return RTS_ISP_OK;

	back_exposure = ae->exposure_ctrl->val;
	isp_memcpy_array(back_ratio, ae->ratio, ARRAY_SIZE(back_ratio));
	isp_memcpy_array(back_exp_ratio, ae->exp_ratio,
			 ARRAY_SIZE(back_exp_ratio));
	ratio = pow(ae->hdr_ratio_ctrl->val, 1.0 / (hdr_chan_num(ae->hdr) - 1));
	for (i = 0; i < hdr_chan_num(ae->hdr) - 1; i++)
		ae->ratio[i] = ae->exp_ratio[i] = ratio;
	for (i = hdr_chan_num(ae->hdr) - 1; i < RTS_ISP_HDR_CHAN_MAX - 1; i++)
		ae->ratio[i] = ae->exp_ratio[i] = 1.0;
	ret = ae_ctrl_modify_range(ae);
	if (!ret)
		ret = ae_set_exp_gain_ctrl(ae, ae->exp_gain.hdr);
	if (ret) {
		isp_memcpy_array(ae->ratio, back_ratio, ARRAY_SIZE(ae->ratio));
		isp_memcpy_array(ae->exp_ratio, back_exp_ratio,
				 ARRAY_SIZE(ae->exp_ratio));
		ret = ae_ctrl_modify_range(ae);
		if (ret)
			return ret;
		ae->exposure_ctrl->val = back_exposure;
		ret = ae_set_exp_gain_ctrl(ae, ae->exp_gain.hdr);
	}
	return ret;
}

static int ae_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		ae->exposure_ctrl->val = ceilf(ae->exp_gain.exposure[0]);
		ae->gain_ctrl->val = ae_total_gain(ae) * 256;
		break;
	case RTS_V4L2_CID_DYNAMIC_FPS:
		ae->dyn_fps_ctrl->val = ae->dyn_fps * SENSOR_FPS_PRECISION;
		break;
	case RTS_V4L2_CID_AUTO_HDR_RATIO:
		ae->hdr_ratio_ctrl->val = ae_total_ratio(ae);
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int ae_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	float min_fps, max_fps;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ae *ae = get_mod(mod, ae);

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		if (ae->auto_gain_ctrl->is_new) {
			ret = ae_algo_set_auto(ae, ae->auto_gain_ctrl->val);
			if (ret)
				break;
		}
		if (ae->exposure_ctrl->is_new || ae->gain_ctrl->is_new)
			ret = ae_set_exp_gain_ctrl(ae, ae->exp_gain.hdr);
		break;
	case V4L2_CID_EXPOSURE_AUTO_PRIORITY:
		if (ae->exp_priority_ctrl->is_new)
			ret = ae->ae_algo->ctrl(mod->owner_id,
						SET_DYNAMIC_FPS_ENABLE,
						&ae->exp_priority_ctrl->val);
		break;
	case V4L2_CID_WIDE_DYNAMIC_RANGE:
		ret = ae_set_hdr_ctrl(ae);
		break;
	case RTS_V4L2_CID_AUTO_HDR_RATIO:
		ret = ae_set_hdr_ratio_ctrl(ae);
		break;
	case RTS_V4L2_CID_SMART_IR_MODE:
		ret = ae->ae_algo->ctrl(mod->owner_id, SET_SORT_MODE,
					&ctrl->val);
		break;
	case RTS_V4L2_CID_SMART_IR_MANUAL_LEVEL:
		ret = ae->ae_algo->ctrl(mod->owner_id, SET_SORT_MANUAL_LEVEL,
					&ctrl->val);
		break;
	case RTS_V4L2_CID_AE_MIN_FPS:
		min_fps = ctrl->val;
		min_fps = max(ae->sensor_min_fps, min_fps);
		ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_MIN_FPS,
					&min_fps);
		if (ret)
			break;
		ret = rtsv_ctrl_modify_range(ae->ae_max_fps_ctrl,
								ae->ae_min_fps_ctrl->val,
								ae->sensor_max_fps, 1,
								clamp(ae->ae_max_fps_ctrl->val,
								ae->ae_min_fps_ctrl->val,
								ae->sensor_max_fps));
		break;
	case RTS_V4L2_CID_AE_MAX_FPS:
		max_fps = ctrl->val;
		ret = ae->ae_algo->ctrl(ae->mod.owner_id, SET_MAX_FPS, &max_fps);
		break;

	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set ae ctrl fail ops=%d", ctrl->id - V4L2_CID_BASE);
	return ret;
}

static const struct v4l2_ctrl_ops ae_ctrl_ops = {
	.g_volatile_ctrl = ae_g_volatile_ctrl,
	.s_ctrl = ae_s_ctrl,
};

static int isp_mod_ae_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_ae *ae;
	isp_algo_param_t *isp_algo;

	ae = get_mod(mod, ae);
	ae->hw_ops = isp_hw_ae_get_ops();
	if (ae->hw_ops == NULL) {
		isp_error("get ae hw ops fail\n");
		return -RTS_ISP_ENOOPS;
	}

	ret = ae->hw_ops->get_hw_info(mod->owner_id, &ae->hw_info);
	if (ret)
		return ret;

	isp_algo = isp_iq_get_algo_param(mod->owner_id);
	if (!isp_algo) {
		isp_error("get ae algo param fail\n");
		return -RTS_ISP_EINVAL;
	}

	ae->algo_param = &isp_algo->ae;

	// coverity[bad_sizeof]
	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_TUNE_OPS,
				       &ae->tune_ops, sizeof(ae->tune_ops));
	if (ret)
		return ret;

	ae->power_line_freq = POWER_LINE_50HZ;

	return RTS_ISP_OK;
}

static int isp_mod_ae_cleanup(struct isp_mod *mod)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);

	ae_release_hdr_memory(ae);
	ae_algo_set_auto(ae, RTS_ISP_FALSE);
	ae_algo_cleanup(ae);
	if (ae->auto_setting.win_weights)
		free(ae->auto_setting.win_weights);
	return RTS_ISP_OK;
}

static int isp_mod_ae_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_ae *ae = get_mod(mod, ae);
	struct v4l2_ctrl_handler *handler = phandler;
	const isp_iq_ae1_t *iq;
	const struct v4l2_ctrl_config dyn_fps_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_DYNAMIC_FPS,
		.name = "Dynamic fps",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 1,
		.max = 30,
		.step = 1,
		.def = 30,
		.flags = V4L2_CTRL_FLAG_READ_ONLY | V4L2_CTRL_FLAG_VOLATILE,
	};

	switch (ae->iq->which_algo) {
	case isp_iq_ae_t_ae1_tag:
		iq = &ae->iq->algo.ae1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	const struct v4l2_ctrl_config smart_ir_mode_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_SMART_IR_MODE,
		.name = "Smart IR Mode",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = SORT_DISABLE,
		.max = SORT_MANUAL,
		.step = 1,
		.def = iq->sort_mode,
	};
	const struct v4l2_ctrl_config smart_ir_manual_level_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_SMART_IR_MANUAL_LEVEL,
		.name = "Smart IR Manual Level",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 100,
		.step = 1,
		.def = iq->manual_level,
	};
	static const char * const hdr_menu[] = {
		"HDR off", "HDR on",
	};
	const struct v4l2_ctrl_config hdr_config = {
		.ops = &ae_ctrl_ops,
		.id = V4L2_CID_WIDE_DYNAMIC_RANGE,
		.name = "High Dynamic Range",
		.type = V4L2_CTRL_TYPE_MENU,
		.max = ARRAY_SIZE(hdr_menu) - 1,
		.qmenu = hdr_menu,
		.def = ARRAY_SIZE(hdr_menu) - 1,
	};

	const struct v4l2_ctrl_config auto_hdr_ratio_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_AUTO_HDR_RATIO,
		.name = "HDR exposure ratio, Automatic",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 1,
	};
	const struct v4l2_ctrl_config hdr_ratio_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_HDR_RATIO,
		.name = "HDR exposure ratio",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = AE_MIN_RATIO,
		.max = AE_MAX_RATIO,
		.step = 1,
		.def = AE_DEF_RATIO,
	};

	const struct v4l2_ctrl_config ae_min_fps_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_AE_MIN_FPS,
		.name = "AE min FPS",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 1,
		.max = iq->dyn_fps[0],
		.step = 1,
		.def = iq->dyn_fps_min,
	};

	const struct v4l2_ctrl_config ae_max_fps_config = {
		.ops = &ae_ctrl_ops,
		.id = RTS_V4L2_CID_AE_MAX_FPS,
		.name = "AE max FPS",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = iq->dyn_fps_min,
		.max = ae->sensor_max_fps,
		.step = 1,
		.def = ae->sensor_max_fps,
	};

	ae->auto_gain_ctrl = rtsv_ctrl_new_std(handler, &ae_ctrl_ops,
					       V4L2_CID_AUTOGAIN,
					       0, 1, 1, ae->iq->enable, mod);
	ae->exposure_ctrl = rtsv_ctrl_new_std(handler, &ae_ctrl_ops,
					      V4L2_CID_EXPOSURE,
					      1, 1000000/ae->sensor_min_fps, 1,
					      ae->iq->def_exposure, mod);
	ae->gain_ctrl = rtsv_ctrl_new_std(handler, &ae_ctrl_ops,
					  V4L2_CID_GAIN,
					  256, 128 * 256, 1,
					  ae->iq->def_gain * 256, mod);
	rtsv_ctrl_auto_cluster(3, &ae->auto_gain_ctrl, 0, RTS_ISP_TRUE);
	ae->exp_priority_ctrl =
	    rtsv_ctrl_new_std(handler, &ae_ctrl_ops,
			      V4L2_CID_EXPOSURE_AUTO_PRIORITY,
			      0, 1, 1, 1, mod);
	ae->dyn_fps_ctrl = rtsv_ctrl_new_custom(handler, &dyn_fps_config, mod);
	ae->hdr_ctrl = rtsv_ctrl_new_custom(handler, &hdr_config, mod);
	ae->auto_hdr_ratio_ctrl =
		rtsv_ctrl_new_custom(handler, &auto_hdr_ratio_config, mod);
	ae->hdr_ratio_ctrl =
		rtsv_ctrl_new_custom(handler, &hdr_ratio_config, mod);
	rtsv_ctrl_auto_cluster(2, &ae->auto_hdr_ratio_ctrl, 0, RTS_ISP_TRUE);
	ae->smart_ir_mode_ctrl = rtsv_ctrl_new_custom(handler,
					&smart_ir_mode_config, mod);
	ae->smart_ir_manual_level_ctrl = rtsv_ctrl_new_custom(handler,
					&smart_ir_manual_level_config, mod);

	ae->ae_max_fps_ctrl = rtsv_ctrl_new_custom(handler,
					&ae_max_fps_config, mod);
	ae->ae_min_fps_ctrl = rtsv_ctrl_new_custom(handler,
					&ae_min_fps_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add ae ctrl fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_ae ae;

int isp_register_mod_ae(void)
{
	memset(&ae, 0, sizeof(ae));
	ae.mod.id = MOD_AE;
	ae.mod.name = "ae";
	/*
	ae.mod.notify_bits = (ISP_ALGO_UPDATE_BIT | ISP_MODE_CHANGE_BIT |
			      ISP_IQ_CHANGE_BIT | ISP_FPS_CHANGE_BIT |
			      ISP_MCROP_CHANGE_BIT | ISP_START_PRE_BIT |
			      ISP_STOP_PRE_BIT);
	*/
	ae.mod.notify_bits = (ISP_ALGO_UPDATE_BIT | ISP_HDR_MODE_CHANGE_BIT |
				ISP_IQ_CHANGE_BIT | ISP_FPS_CHANGE_BIT | ISP_MCROP_CHANGE_BIT);
	ae.mod.init = isp_mod_ae_init;
	ae.mod.cleanup = isp_mod_ae_cleanup;
	ae.mod.add_ctrl = isp_mod_ae_add_ctrl;
	ae.mod.info_actions = ae_info_actions;
	ae.mod.info_actions_num = ARRAY_SIZE(ae_info_actions);
	ae.mod.exec_actions = ae_exec_actions;
	ae.mod.exec_actions_num = ARRAY_SIZE(ae_exec_actions);
	ae.mod.notify_actions = ae_notify_actions;
	ae.mod.notify_actions_num = ARRAY_SIZE(ae_notify_actions);
	return isp_mod_register(&ae.mod);
}

void isp_unregister_mod_ae(void)
{
	isp_mod_unregister(&ae.mod);
}

