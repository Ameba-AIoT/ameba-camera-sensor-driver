/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp_sensor.h>
#include <rts_isp_patch.h>
#include <isp_utils.h>
#include <isp_top.h>
#include <isp_notify.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_iq.h>
#include <isp_driver.h>
#include <isp_poll.h>
#include <isp_sensor.h>
#include <isp_mod_iq.h>
#include <isp_mod_sensor.h>
#include <isp_mod_global.h>
#include <isp_mod_awb.h>
#include <isp_mod_ae.h>
#include <isp_hw_ae.h>
#include <isp_hw_sensor.h>
#include <isp_v4l2_ctrl.h>
#include <math.h>
#include "rt_code.h"
#define ISP_DEBUG_TYPE ISP_DEBUG_SENSOR

#define sensor_magic(version) ((version) >> 16)
#define sensor_major_version(version) (((version) & 0xff00) >> 8)
#define sensor_minor_version(version) (((version) & 0xff))

//#define DEBUG

#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#undef debug
#define debug(fmt, ...)
#endif

struct isp_mod_sensor {
	struct isp_mod mod;
	const struct rts_isp_sensor_ops *sensor_ops;
	const struct rts_isp_sensor_patch_ops *patch_ops;

	const struct isp_hw_sensor_ops *hw_ops;

	struct rts_isp_sensor_info info;
	struct isp_sensor_mode mode;
	rts_isp_point_t start;
	struct rts_isp_interface_info interface;
	struct rts_isp_i2c_regs init_regs[8];

	float set_fps;
	float fps;
	struct isp_sensor_timing timing;
	int fps_change_notifying;
	/* backup exp_gain during changing fps */
	struct {
		enum rts_isp_sensor_hdr_mode hdr;
		float isp_hdr_gain[RTS_ISP_HDR_CHAN_MAX];
		float isp_gain;
		int isp_sync_num;
		get_sync_regs_cb get_sync_regs_cb;
	} exp_gain_backup;

	struct rts_isp_sensor_exp_gain exp_gain;
	float isp_gain;
	uint32_t isp_gain_delay;

	const isp_iq_high_temp_t *iq;
	isp_algo_param_high_temp_t *param;
	struct isp_notify_dynamic_sensor dynamic;
	isp_timer_handle_t timer;
	int gain_is_high;
	int temp_is_high;

	uint32_t flick_dummy;
	uint32_t focus_pos;

	struct v4l2_ctrl *mirror_flip_ctrl;
	struct v4l2_ctrl *short_exp_thd_ctrl;
	struct v4l2_ctrl *isp_gain_mode_ctrl;
	struct v4l2_ctrl *isp_gain_ctrl;
	uint8_t prev_short_exp_mode;

	uint32_t fast_ae_cnt;

	uint32_t statis_done_cnt;
	int init_hdr_mode;

};


static float precision_fps(float fps)
{
	return roundf(fps * SENSOR_FPS_PRECISION) / SENSOR_FPS_PRECISION;
}

static int check_patch_ops(const struct rts_isp_sensor_patch_ops *patch_ops)
{
	if (!patch_ops)
		return RTS_ISP_OK;
	if (!patch_ops->iq_change && !patch_ops->dynamic)
		return -RTS_ISP_EPLUGIN;
	return RTS_ISP_OK;
}

static int check_mode(const struct rts_isp_sensor_mode *mode)
{
	if (mode->hdr != LINEAR_MODE && mode->hdr != HDR_MODE)
		return -RTS_ISP_EINVAL;
	if (mode->size.w < 64 || mode->size.h < 64 ||
	    mode->size.w % 2 || mode->size.h % 2 ||
	    mode->fps < 0.1)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_modes(const struct rts_isp_sensor_modes *modes)
{
	int i;

	if (!modes->num || modes->num > ARRAY_SIZE(modes->mode))
		return -RTS_ISP_EINVAL;
	for (i = 0; i < modes->num; i++)
		if (check_mode(&modes->mode[i]))
			return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_mode_compatible(const struct rts_isp_sensor_mode *mode,
				 const struct rts_isp_sensor_modes *modes)
{
	int i;

	for (i = 0; i < modes->num; i++)
		if (mode->hdr == modes->mode[i].hdr &&
		    mode->size.w <= modes->mode[i].size.w &&
		    mode->size.h <= modes->mode[i].size.h &&
		    float_eq(mode->fps, modes->mode[i].fps))
			break;
	if (i == modes->num)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int check_info(const struct rts_isp_sensor_info *info)
{
	if (check_modes(&info->modes))
		return ERR_ID_MOD_SENSOR_CHECK_MOD_FAIL;
	if ((info->i2c.addr_len != 1 && info->i2c.addr_len != 2) ||
	    (info->i2c.data_len != 1 && info->i2c.data_len != 2))
		return ERR_ID_MOD_SENSOR_CHECK_I2C_FORMAT_FAIL;
	if (info->power_down.num > ARRAY_SIZE(info->power_down.items) ||
	    info->power_down.num > ARRAY_SIZE(info->power_down.items))
		return ERR_ID_MOD_SENSOR_CHECK_GPIO_FAIL;
	return RTS_ISP_OK;
}

static int check_init_info(const struct rts_isp_sensor_init_info *info,
			   const struct rts_isp_sensor_mode *mode)
{
	if (info->start.x + mode->size.w > info->size.w ||
	    info->start.y + mode->size.h > info->size.h) {
		printf("sensor init size out of range: w %d h %d all x %d y %d w %d h %d \n", mode->size.w, mode->size.h, info->start.x, info->start.y, info->size.w, info->size.h);
		return ERR_ID_MOD_SENSOR_CHECK_SIZE_OUT_RANGE;
	}
	if (fabs(info->hts * info->min_vts * mode->fps - info->pclk) >
	    0.01 * info->pclk) {
		printf("sensor init hts %d vts %d fps %.2f pclk %d out of range\n", info->hts, info->min_vts,  mode->fps, info->pclk);
		return ERR_ID_MOD_SENSOR_CHECK_CLOCK_OUT_RANGE;
	};
	if (!info->pclk || !info->hts ||
	    !info->min_vts || info->max_vts < info->min_vts)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int refine_fps(struct rts_isp_sensor_modes *modes)
{
	int i;

	if (!modes)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < modes->num; i++)
		modes->mode[i].fps = precision_fps(modes->mode[i].fps);
	return RTS_ISP_OK;
}

static int sensor_get_exposure_range(struct isp_mod_sensor *sensor,
				     uint32_t vts,
				     float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				     float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				     float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	int i;
	int max_short_exp_cnt;
	int cur_max_exp_cnt;
	int min_delay_cnt;
	int remain_cnt;
	float real_ratio = 1;
	float ratio_sum = real_ratio;
	const int gap = 4;
	const int num = hdr_chan_num(sensor->mode.hdr);
	const float step = 1e6 * sensor->mode.hts / num / sensor->mode.pclk;

	for (i = num - 2; i >= 0; i--) {
		if (ratio[i] < 1)
			return -RTS_ISP_EINVAL;
		real_ratio = real_ratio * ratio[i];
		ratio_sum += real_ratio;
	}

	/* calc min exposure */
	min_exposure[num - 1] = sensor->mode.exposure_step;
	for (i = num - 2; i >= 0; i--)
		min_exposure[i] = min_exposure[i + 1] * ratio[i];

	/* calc max exposure */
	min_delay_cnt = ISP_SENSOR_MIN_EXP_DELAY;
	remain_cnt = (vts - gap) * num;
	max_short_exp_cnt =
		min((uint32_t)(remain_cnt / ratio_sum),
		    roundup_div(sensor->mode.min_vts, AE_MIN_RATIO) - gap);
	do {
		cur_max_exp_cnt = max_short_exp_cnt;
		for (i = num - 1; i > 0; i--) {
			if (min_exposure[i] > cur_max_exp_cnt * step)
				return -RTS_ISP_EINVAL;
			remain_cnt -= max(min_delay_cnt, cur_max_exp_cnt);
			cur_max_exp_cnt = cur_max_exp_cnt * ratio[i - 1];
		}
		if (cur_max_exp_cnt <= remain_cnt)
			break;
	} while (--max_short_exp_cnt);
	if (max_short_exp_cnt == 0)
		return -RTS_ISP_EINVAL;
	max_exposure[0] = step * cur_max_exp_cnt;
	for (i = 1; i < num; i++)
		max_exposure[i] = max_exposure[i - 1] / ratio[i - 1];

	return RTS_ISP_OK;
}

static int get_exposure_range(int32_t isp_id, float fps,
			      float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
			      float min_exposure[RTS_ISP_HDR_CHAN_MAX],
			      float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	uint32_t vts;
	struct isp_mod *mod;
	struct isp_mod_sensor *sensor;

	mod = isp_top_get_mod(isp_id, MOD_SENSOR);
	if (!mod)
		return -RTS_ISP_EINVAL;

	sensor = get_mod(mod, sensor);

	if (fps < sensor->mode.min_fps || fps > sensor->mode.max_fps ||
	    (hdr_chan_num(sensor->mode.hdr) > 1 && !ratio) ||
	    !min_exposure || !max_exposure) {
			isp_error("fps=%f, %d %d %d %d %d \n",fps, fps < sensor->mode.min_fps , fps > sensor->mode.max_fps ,
			(hdr_chan_num(sensor->mode.hdr) > 1 && !ratio) ,
			!min_exposure , !max_exposure);
			if (fps < sensor->mode.min_fps || fps > sensor->mode.max_fps)
				return ERR_ID_MOD_SENSOR_FPS_OUT_RANGE;
			if (hdr_chan_num(sensor->mode.hdr) > 1 && !ratio)
				return ERR_ID_MOD_SENSOR_HDR_RATIO_ERR;

			return ERR_ID_MOD_SENSOR_EXP_OUT_RANGE;
		}

	vts = sensor->mode.min_vts * sensor->mode.max_fps / fps;

	if (sensor->sensor_ops->get_exposure_range)
		return sensor->sensor_ops->get_exposure_range(
				sensor->mod.owner_id, vts, ratio,
				min_exposure, max_exposure);

	if (sensor->mode.hdr == LINEAR_MODE) {
		/* can set 40ms exposure at 25 fps by a little fps reducing */
		min_exposure[0] = sensor->mode.exposure_step;
		max_exposure[0] = 1e6f / fps;
		return RTS_ISP_OK;
	}

	return sensor_get_exposure_range(sensor, vts, ratio, min_exposure,
					 max_exposure);
}

static int get_tuned_again(uint32_t isp_id, float again[RTS_ISP_HDR_CHAN_MAX])
{
	struct isp_mod *mod;

	mod = isp_top_get_mod(isp_id, MOD_SENSOR);
	if (!mod || !again)
		return -RTS_ISP_EINVAL;
	return get_mod(mod, sensor)->sensor_ops->get_tuned_again(isp_id, again);
}

static int get_tuned_dgain(uint32_t isp_id, float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct isp_mod *mod;

	mod = isp_top_get_mod(isp_id, MOD_SENSOR);
	if (!mod || !dgain)
		return -RTS_ISP_EINVAL;
	return get_mod(mod, sensor)->sensor_ops->get_tuned_dgain(isp_id, dgain);
}

static const struct rts_isp_exp_gain_tune_ops exp_gain_tune_ops = {
	.get_exposure_range = get_exposure_range,
	.get_tuned_again = get_tuned_again,
	.get_tuned_dgain = get_tuned_dgain,
};

static const char *get_hdr_str(enum rts_isp_sensor_hdr_mode hdr)
{
	switch (hdr) {
	case LINEAR_MODE:
		return "linear";
	case HDR_MODE:
		return "hdr line 2to1";
	default:
		return "unknown mode";
	}
}

static int sensor_init_plugin(struct isp_mod_sensor *sensor)
{
	int ret;

	ret = isp_sensor_get_ops(isp_top_get_snrm(), sensor->mod.owner_id,
				 &sensor->sensor_ops);
	if (ret)
		goto err;

	if (!sensor->sensor_ops) {
		ret = -RTS_ISP_EINVAL;
		goto err;
	}
	if (sensor->sensor_ops->get_patch_ops)
		sensor->patch_ops = sensor->sensor_ops->get_patch_ops();
	ret = check_patch_ops(sensor->patch_ops);
	if (ret)
		goto err;
	if (sensor->sensor_ops->init) {
		ret = sensor->sensor_ops->init(sensor->mod.owner_id);
		if (ret)
			goto err;
	}
	if (sensor->patch_ops && sensor->patch_ops->init) {
		ret = sensor->patch_ops->init(sensor->mod.owner_id);
		if (ret) {
			if (sensor->sensor_ops && sensor->sensor_ops->cleanup)
				sensor->sensor_ops->cleanup(
						sensor->mod.owner_id);
			goto err;
		}
	}
	return RTS_ISP_OK;
err:
	sensor->sensor_ops = NULL;
	sensor->patch_ops = NULL;
	return ret;
}

static void sensor_cleanup_plugin(struct isp_mod_sensor *sensor)
{
	if (sensor->sensor_ops && sensor->sensor_ops->cleanup)
		sensor->sensor_ops->cleanup(sensor->mod.owner_id);
	if (sensor->patch_ops && sensor->patch_ops->cleanup)
		sensor->patch_ops->cleanup(sensor->mod.owner_id);

	sensor->sensor_ops = NULL;
	sensor->patch_ops = NULL;
}

static int sensor_get_info(struct isp_mod_sensor *sensor)
{
	int ret;

	memset(&sensor->info, 0, sizeof(sensor->info));
	ret = sensor->sensor_ops->get_info(sensor->mod.owner_id, &sensor->info);
	if (ret)
		return ret;
	ret = check_info(&sensor->info);
	if (ret)
		return ret;
	return refine_fps(&sensor->info.modes);
}

static void sensor_set_mode(struct isp_mod_sensor *sensor,
			    const struct rts_isp_sensor_init_info *init_info,
			    const struct rts_isp_sensor_mode *mode)
{
	//printf(" %s min_vts %d max_vts %d exposure_step%f\n", __func__, init_info->min_vts, init_info->max_vts, init_info->exposure_step);
	sensor->mode.hdr = mode->hdr;
	sensor->mode.size.snr = init_info->size;
	sensor->mode.size.isp = mode->size;
	sensor->mode.max_fps = mode->fps;
	sensor->mode.min_fps = (sensor->mode.max_fps * init_info->min_vts /
				init_info->max_vts);

	printf("fps max %f min %f \n", sensor->mode.max_fps, sensor->mode.min_fps);

	sensor->mode.hts = init_info->hts;
	sensor->mode.min_vts = init_info->min_vts;
	sensor->mode.max_vts = init_info->max_vts;
	sensor->mode.pclk = init_info->pclk;
	sensor->mode.mipi_behavor = init_info->mipi_behavor;
	if (float_ne(init_info->exposure_step, 0))
		sensor->mode.exposure_step = init_info->exposure_step;
	else
		sensor->mode.exposure_step =
			(1e6 * sensor->mode.hts /
			 hdr_chan_num(sensor->mode.hdr) / init_info->pclk);

	printf("exposure_step %f\n", sensor->mode.exposure_step);
}

static int sensor_change_mode(struct isp_mod_sensor *sensor,
			      const struct rts_isp_sensor_mode *mode)
{
	int ret;
	struct rts_isp_sensor_init_info init_info;

	memset(&init_info, 0, sizeof(init_info));
	ret = sensor->sensor_ops->get_init_info(sensor->mod.owner_id, mode,
						&init_info);
	if (ret)
		return ret;
	ret = check_init_info(&init_info, mode);
	if (ret)
		return ret;

	sensor_set_mode(sensor, &init_info, mode);
	sensor->start = init_info.start;
	sensor->interface = init_info.interface;
	if (sizeof(sensor->init_regs) != sizeof(init_info.sensor_regs)) {
		isp_error("sensor_change_mode init_regs(%d) != sensor_regs(%d) \r\n", sizeof(sensor->init_regs), sizeof(sensor->init_regs));
		return -RTS_ISP_EINVAL;
	}
	isp_memcpy(sensor->init_regs, init_info.sensor_regs,
		   sizeof(sensor->init_regs));
	printf("change sensor mode => %dx%d@%.3ffps - '%s' \n",
		 mode->size.w, mode->size.h, mode->fps, get_hdr_str(mode->hdr));

	return RTS_ISP_OK;
}

static int sensor_handle_short_exp_mode(struct isp_mod_sensor *sensor)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = &sensor->mod;
	uint32_t vhdr_en;
	uint32_t awb_clip;
	uint32_t ae_dyn_vhdr_mode;

	if (!sensor->sensor_ops->get_short_exp_mode) {
		return ERR_ID_MOD_SENSOR_NOT_SUPPORT_SHORT_EXP;
	}

	if (sensor->sensor_ops->get_short_exp_mode(sensor->mod.owner_id) ==
	    sensor->prev_short_exp_mode) {
		return ret;
	}

	if (sensor->prev_short_exp_mode) {
		// Enable vhdr
		sensor->prev_short_exp_mode = VHDR_EXP_MODE_MULTIPLE;
		vhdr_en = 1;
		awb_clip = 0;
		ae_dyn_vhdr_mode = 1;
	}
	else {
		// Disable vhdr
		sensor->prev_short_exp_mode = VHDR_EXP_MODE_SINGLE;
		vhdr_en = 0;
		awb_clip = 1;
		ae_dyn_vhdr_mode = 0;
	}

	ret = isp_mod_sibling_execute(mod, MOD_GLOBAL, GLOBAL_EXEC_SET_VHDR_ENABLE,
				      &vhdr_en, sizeof(vhdr_en));
	if (ret) {
		isp_error("set vhdr enable failed, ret = %d\n", ret);
		goto out;
	}

	ret = isp_mod_sibling_execute(mod, MOD_AWB, AWB_EXEC_SET_AWB_CLIP,
				      &awb_clip, sizeof(awb_clip));
	if (ret) {
		isp_error("set awb clip failed, ret = %d\n", ret);
		goto out;
	}

	ret = isp_mod_sibling_execute(mod, MOD_AE, AE_EXEC_SET_DYN_VHDR_MODE,
				      &ae_dyn_vhdr_mode, sizeof(ae_dyn_vhdr_mode));
	if (ret) {
		isp_error("set ae dynamic vhd mode failed, ret = %d\n", ret);
		goto out;
	}

out:
	return ret;
}

static void sensor_init_timing(struct isp_mod_sensor *sensor)
{
	sensor->timing.pclk = sensor->mode.pclk;
	sensor->timing.hts = sensor->mode.hts;
	sensor->timing.vts = sensor->mode.min_vts;
	sensor->timing.isp_width = sensor->mode.size.isp.w;
	sensor->timing.isp_height = sensor->mode.size.isp.h;
	sensor->timing.snr_width = sensor->mode.size.snr.w;
	sensor->timing.snr_height = sensor->mode.size.snr.h;
	sensor->timing.exposure_unit = sensor->mode.hts * 1e6f / sensor->mode.pclk;
}

static void sensor_cleanup_timing(struct isp_mod_sensor *sensor)
{
	memset(&sensor->timing, 0, sizeof(sensor->timing));
}

enum rts_isp_sensor_open_mode sensor_open_mode = OPEN_MODE;
enum rts_isp_sensor_close_mode sensor_close_mode = CLOSE_MODE;

int rts_isp_sensor_get_open_mode(void)
{
	return sensor_open_mode;
}

void rts_isp_sensor_set_open_mode(int val)
{
	sensor_open_mode = val;
}

int rts_isp_sensor_get_close_mode(void)
{
	return sensor_close_mode;
}

void rts_isp_sensor_set_close_mode(int val)
{
	sensor_close_mode = val;
}

static int sensor_set_power(struct isp_mod_sensor *sensor, int enable)
{
	if (enable) {
		if (sensor_open_mode == OPEN_MODE) {
			printf("sensor power on\n");
			return isp_driver_set_power(&sensor->info.power_up);
		} else { // RESUME_MODE
			printf("sensor resume\n");
			return isp_driver_set_power(&sensor->info.resume);
		}
	}
	else {
		if (sensor_close_mode == CLOSE_MODE) {
			printf("sensor power off\n");
			return isp_driver_set_power(&sensor->info.power_down);
		} else { //SUSPEND_MODE
			printf("sensor suspend\n");
			return isp_driver_set_power(&sensor->info.suspend);
		}
	}

}

static int sensor_initialize(struct isp_mod_sensor *sensor)
{
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(sensor->init_regs); i++) {
		if (!sensor->init_regs[i].num)
			break;
		ret = rts_isp_write_i2c_regs(&sensor->info.i2c,
					     &sensor->init_regs[i]);
		if (ret)
			return ret;

	}
	return RTS_ISP_OK;
}

static void sensor_restore_exp_gain(struct isp_mod_sensor *sensor,
				    struct rts_isp_ae_exp_gain *exp_gain)
{
	isp_memcpy(exp_gain->exposure, sensor->exp_gain.exposure,
		   sizeof(exp_gain->exposure));
	isp_memcpy(exp_gain->analog_gain, sensor->exp_gain.analog_gain,
		   sizeof(exp_gain->analog_gain));
	isp_memcpy(exp_gain->digital_gain, sensor->exp_gain.digital_gain,
		   sizeof(exp_gain->digital_gain));
	exp_gain->hdr = sensor->exp_gain_backup.hdr;
	isp_memcpy(exp_gain->isp_hdr_gain, sensor->exp_gain_backup.isp_hdr_gain,
		   sizeof(exp_gain->isp_hdr_gain));
	exp_gain->isp_gain = sensor->exp_gain_backup.isp_gain;
}
extern int __rtscam_isp_set_gain(struct rts_isp_sync_regs *regs);
extern int __rtscam_isp_set_i2c(const struct rts_isp_sync_reg *reg, u32 num, const struct rts_isp_i2c_info *i2c_info);
static int sensor_set_exp_gain(struct isp_mod_sensor *sensor,
			       const struct isp_sensor_exp_gain *snr_exp_gain, bool direct_i2c)
{
	int ret;
	int isp_sync_num;
	get_sync_regs_cb get_sync_regs_cb;
	const struct rts_isp_ae_exp_gain *ae_exp_gain;
	struct rts_isp_ae_exp_gain restore_exp_gain;
	const int snr_sync_num = 32;
	struct rts_isp_sync_regs regs = {};
	const struct rts_isp_sensor_ops *ops = sensor->sensor_ops;

	if (snr_exp_gain) {
		isp_sync_num = snr_exp_gain->isp_sync_num;
		get_sync_regs_cb = snr_exp_gain->get_sync_regs_cb;
		ae_exp_gain = snr_exp_gain->exp_gain;
	} else if (sensor->exp_gain_backup.get_sync_regs_cb) {
		sensor_restore_exp_gain(sensor, &restore_exp_gain);
		isp_sync_num = sensor->exp_gain_backup.isp_sync_num;
		get_sync_regs_cb = sensor->exp_gain_backup.get_sync_regs_cb;
		ae_exp_gain = &restore_exp_gain;
	} else {
		isp_sync_num = 0;
		get_sync_regs_cb = NULL;
		ae_exp_gain = NULL;
	}
	sensor->exp_gain_backup.isp_sync_num = 0;
	sensor->exp_gain_backup.get_sync_regs_cb = NULL;
	if (isp_sync_num > 16) {
			isp_error("isp_sync_num too large %d \r\n", isp_sync_num);
			return -RTS_ISP_EINVAL;
	}

	regs.num = 0;
	// regs.reg = isp_malloc((snr_sync_num + isp_sync_num) *
	// 		      sizeof(*regs.reg));
	// if (!regs.reg)
	// 	return -RTS_ISP_ENOMEM;

	// memset(regs.reg, 0, (snr_sync_num + isp_sync_num) *
	// 		      sizeof(*regs.reg));

	/* sensor exp gain func may change sensor->isp_gain_delay */
	sensor->isp_gain_delay = 1;
	//printf("%s AG %.2f DG %.2f EXP %.2f\n", __func__, sensor->exp_gain.analog_gain[0], sensor->exp_gain.digital_gain[0], sensor->exp_gain.exposure[0]);
	ret = ops->get_exposure_gain_info(sensor->mod.owner_id,
					  &sensor->exp_gain, &regs);
	if (ret) {
		isp_error("get sensor exposure gain info fail ret %d \r\n", ret);
		goto out;
	}
	if (regs.num > snr_sync_num) {
		ret = -RTS_ISP_ERANGE;
		isp_error("sensor sync regs number > %d ret %d \r\n", snr_sync_num, ret);
		goto out;
	}
	if (get_sync_regs_cb) {
		ret = get_sync_regs_cb(sensor->mod.owner_id,
				       sensor->isp_gain_delay,
				       &regs.reg[regs.num],
				       &isp_sync_num, ae_exp_gain);
		if (ret) {
			isp_error("get isp sync regs fail %d \r\n", ret);
			goto out;
		}
		if (ae_exp_gain == NULL) {
			ret = -RTS_ISP_EINVAL;
			isp_error("ae_exp_gain NULL\r\n");
			goto out;
		}

		if (sensor->isp_gain_mode_ctrl->cur.val == RTS_ISP_SENSOR_ISP_GAIN_MODE_AUTO) {
			sensor->isp_gain = ae_exp_gain->isp_gain;
		} else { // RTS_ISP_SENSOR_ISP_GAIN_MODE_MANUAL.
			sensor->isp_gain = sensor->isp_gain_ctrl->cur.val / 256.0;
		}
		regs.isp_gain = sensor->isp_gain * 2048;
		regs.isp_gain_delay = sensor->isp_gain_delay;
	}


	regs.split_index = regs.num;
	regs.i2c_info = sensor->info.i2c;
	regs.num += isp_sync_num;

	//printf("AG %.2f DG %.2f EXP %.2f isp_gain 0x%08x cnt %d isp_sync_num %d\n", sensor->exp_gain.analog_gain[0], sensor->exp_gain.digital_gain[0], sensor->exp_gain.exposure[0], regs.isp_gain, sensor->fast_ae_cnt, isp_sync_num);


	if ( (sensor->fast_ae_cnt > 0 ) && (isp_top_get_direct_i2c_mode() != 0 ) ) {
		rts_isp_sensor_access_prepare();

		__rtscam_isp_set_gain(&regs);

		__rtscam_isp_set_i2c(regs.reg, regs.num,
							 &(regs.i2c_info));

		rts_isp_sensor_access_unprepare();
		if (direct_i2c)
			sensor->fast_ae_cnt--;

	} else {
		ret = isp_driver_write_sync_regs(&regs);
	}



	if (ret) {
		isp_error("isp_driver_write_sync_regs %d \r\n", ret);
		goto out;
	}

	/* If set sensor register failed,
		we shouldn't decrease the min exposure */
	if (sensor->mode.hdr == HDR_MODE) {
		ret = sensor_handle_short_exp_mode(sensor);
		if (ret == ERR_ID_MOD_SENSOR_NOT_SUPPORT_SHORT_EXP) {
			isp_info("short_exp_mode API is not supported.\n");
			return RTS_ISP_OK;
		}
	}

out:
	//isp_free(regs.reg);
	return ret;
}

static int sensor_calc_vts(struct isp_mod_sensor *sensor, float fps)
{
	uint32_t vts;

	vts = sensor->mode.min_vts * sensor->mode.max_fps / fps;
	if (sensor->mode.hdr == LINEAR_MODE) {
		uint32_t exp_lines;

		/* can set 40ms exposure at 25 fps by a little fps reducing */
		exp_lines = (sensor->exp_gain.exposure[0] /
			     (1e6 / sensor->mode.max_fps) *
			     sensor->mode.min_vts);
		if (vts < exp_lines) {
			printf(" sensor_calc_vts conflict vts %d exp_lines %d exp %.3f fps %.3f, force to fps \r\n", vts, exp_lines, sensor->exp_gain.exposure[0], fps);
			exp_lines = vts;
			//return -RTS_ISP_ERANGE;
		}
		vts = max(exp_lines + 4, vts);
	}
	sensor->exp_gain.vts = clamp(vts + sensor->flick_dummy,
				     sensor->mode.min_vts,
				     sensor->mode.max_vts);
	return RTS_ISP_OK;
}

static int sensor_set_exp_gain_fps_ex(struct isp_mod_sensor *sensor, float fps,
				const struct isp_sensor_exp_gain *snr_exp_gain, bool direct_i2c)
{
	int ret;

	if (float_eq(sensor->set_fps, 0) || float_eq(fps, 0) ||
	    sensor->fps_change_notifying)
		return RTS_ISP_OK;

	ret = sensor_calc_vts(sensor, fps);
	if (ret) {
		isp_error(" sensor_calc_vts %d \r\n", ret);
		return ret;
	}

	sensor->fps = fps;
	//printf("%s AG %.2f DG %.2f EXP %.2f\n", __func__, sensor->exp_gain.analog_gain[0], sensor->exp_gain.digital_gain[0], sensor->exp_gain.exposure[0]);

	return sensor_set_exp_gain(sensor, snr_exp_gain, direct_i2c);
}

static int sensor_set_exp_gain_fps(struct isp_mod_sensor *sensor, float fps, bool direct_i2c)
{
	return sensor_set_exp_gain_fps_ex(sensor, fps, NULL, direct_i2c);
}

static int sensor_timer_callback(isp_timer_handle_t *timer, void *data)
{
	int ret;
	struct isp_mod *mod = data;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	const struct isp_notify_dynamic *dyn;
	uint32_t gain_th;

	// coverity[bad_sizeof]
	ret = isp_mod_sibling_get_info(mod, MOD_IQ, IQ_INFO_DYNAMIC,
				       &dyn, sizeof(dyn));
	if (ret)
		return ret;
	gain_th = sensor->gain_is_high ?
		sensor->iq->gain.exit_th : sensor->iq->gain.enter_th;
	if (dyn->ae.gain > gain_th) {
		int temp;
		int temp_th;

		sensor->gain_is_high = RTS_ISP_TRUE;
		temp = sensor->sensor_ops->get_temperature(mod->owner_id);
		temp = max(temp, 0);
		temp_th = sensor->temp_is_high ?
			sensor->iq->temp.exit_th : sensor->iq->temp.enter_th;
		if (temp > temp_th) {
			sensor->temp_is_high = RTS_ISP_TRUE;
			sensor->dynamic.temperature = temp;
		} else {
			sensor->temp_is_high = RTS_ISP_FALSE;
		}
	} else {
		sensor->gain_is_high = RTS_ISP_FALSE;
	}
	sensor->dynamic.high_temp_en =
		sensor->gain_is_high && sensor->temp_is_high;
	sensor->param->high_temp_en = sensor->dynamic.high_temp_en;

	return isp_mod_sibling_execute(mod, MOD_IQ, IQ_EXEC_SET_DYNAMIC_SENSOR,
				       &sensor->dynamic,
				       sizeof(sensor->dynamic));
}

static int sensor_high_temp_start(struct isp_mod_sensor *sensor, int start)
{
	int ret;

	sensor->dynamic.high_temp_en = RTS_ISP_FALSE;
	sensor->gain_is_high = RTS_ISP_FALSE;
	sensor->temp_is_high = RTS_ISP_FALSE;

	if (start && sensor->iq->enable &&
	    sensor->sensor_ops->get_temperature) {
		ret = isp_timer_start(&sensor->timer, 0,
				      max(5000U, sensor->iq->interval));
	} else {
		ret = isp_timer_stop(&sensor->timer);
		if (ret)
			return ret;
		ret = isp_mod_sibling_execute(&sensor->mod, MOD_IQ,
					      IQ_EXEC_SET_DYNAMIC_SENSOR,
					      &sensor->dynamic,
					      sizeof(sensor->dynamic));
	}
	return ret;
}

static int sensor_set_focus(struct isp_mod_sensor *sensor)
{
	if (float_eq(sensor->set_fps, 0))
		return RTS_ISP_OK;

	if (sensor->sensor_ops->set_focus) {
		if (sensor->focus_pos > sensor->info.focus.max ||
		    sensor->focus_pos < sensor->info.focus.min)
			return -RTS_ISP_EINVAL;
		return sensor->sensor_ops->set_focus(sensor->mod.owner_id,
						     sensor->focus_pos);
	}
	return RTS_ISP_OK;
}
uint32_t set_pwr_time, set_i2c_time, set_i2c_end_time, sensor_start_time, sensor_end_time;
extern volatile uint32_t switch_start_ae_count;
uint32_t sensor_init_done = false;
BOOL data_start_error = FALSE;
BOOL frame_end_error = FALSE;

#if 1
static int sensor_init_set_mirror_flip(struct isp_mod_sensor *sensor,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int ret;
	int len;


	struct rts_isp_i2c_reg ml_reg;

	memset(&mf_info->regs, 0, sizeof(mf_info->regs));

	if (!sensor->sensor_ops->set_mirror_flip) {
		//isp_error("set_mirror_flip is not supported\n");
		return RTS_ISP_OK;
	}

	ret = sensor->sensor_ops->set_mirror_flip(sensor->mod.owner_id,
											  mf_info);
	if (ret) {
		isp_error("[M&L] set_mirror_flip error %d \n", ret);
		return ret;
	}

	if (mf_info->regs.num) {

		for (int i=0; i<mf_info->regs.num; i++ ) {

			ml_reg.addr = mf_info->regs.reg[i].i2c.addr;
			ml_reg.data = mf_info->regs.reg[i].i2c.data;

			ret = rts_isp_write_i2c_reg(&(sensor->info.i2c), &ml_reg);

			if (ret) {
				isp_error("[M&L] rts_isp_write_i2c_reg error %d \n", ret);
				return ret;
			}


		}

	}

	return ret;

}

#endif



int slave_addr_idx = 0;
extern int reinit_i2c(void);

int sensor_get_slave_addr_idx(void)
{
	return slave_addr_idx;
}

static int sensor_start(struct isp_mod_sensor *sensor)
{
	int ret;
	uint32_t tnr_en;
	sensor_start_time = hal_read_curtime_us();
	struct rts_isp_sensor_mirror_flip mf_info;
	uint32_t t1, t2;
	int slave_addr_num = 1;
	struct rts_isp_sensor_info s_info;
	set_pwr_time = hal_read_curtime_us();
	if (isp_top_get_direct_i2c_mode() != 0 ) {
		if ( isp_top_get_direct_i2c_mode() == 2 ) {
			sensor->fast_ae_cnt = switch_start_ae_count;
		} else {
			sensor->fast_ae_cnt = switch_start_ae_count+1;
		}
	} else {
		sensor->fast_ae_cnt = 0;
	}

	//sensor->fast_ae_cnt = 0;
	if ( sensor->fast_ae_cnt > 0 ) {
		printf("%s set fast ae cnt %d \n", __func__, sensor->fast_ae_cnt);
	}

	tnr_en = (sensor->prev_short_exp_mode) ? 0 : 1;
	ret = isp_mod_sibling_execute(&sensor->mod, MOD_GLOBAL, GLOBAL_EXEC_SET_TNR_ENABLE,
				      &tnr_en, sizeof(tnr_en));
	if (ret) {
		isp_error("set tnr enable failed, ret = %d\n", ret);
		goto err;
	}

	if (!isp_top_get_fcs_ready()) {
		sensor_init_done = false;
		if (sensor_open_mode == RESUME_MODE) {
			if (sensor->sensor_ops->pre_resume) {
				ret = sensor->sensor_ops->pre_resume(sensor->mod.owner_id);
				if (ret) {
					isp_error("%s sensor pre_resume fail \r\n",__FUNCTION__);
					goto err;
				}
			}
		}

		ret = sensor_set_power(sensor, RTS_ISP_TRUE);
		if (ret) {
			isp_error("%s sensor_set_power err \r\n",__FUNCTION__);
			goto err;
		}

		if (sensor->sensor_ops->check) {

			if (sensor->sensor_ops->get_slave_addr_num)
				slave_addr_num = sensor->sensor_ops->get_slave_addr_num(sensor->mod.owner_id);


			for ( ; slave_addr_idx < slave_addr_num; slave_addr_idx++) {

				ret = sensor->sensor_ops->check(sensor->mod.owner_id);
				if (ret == RTS_ISP_OK)
					break;

				reinit_i2c();
			}

			if (ret) {
				isp_error("%s check sensor id err \r\n",__FUNCTION__);
				goto err;
			}
		}


		set_i2c_time = hal_read_curtime_us();
		rts_isp_sensor_access_prepare();
		t1 = hal_read_curtime_us();

		//Sensor_initialize and mirror flip will not re-call get_info to get slave addr
		//so change slave addr here when sensor has multiple i2c slave addrs
		if (sensor->sensor_ops->get_info) {
			sensor->sensor_ops->get_info(sensor->mod.owner_id, &s_info);
			sensor->info.i2c.i2c_id = s_info.i2c.i2c_id;
		}

		ret = sensor_initialize(sensor);
		if (ret) {
			isp_error("sensor_initialize err %d \r\n",ret);
			rts_isp_sensor_access_unprepare();
			goto err;
		}
		t2 = hal_read_curtime_us();
		printf("sensor_initialize: %d\n\r", t2-t1);
		sensor_init_done = true;


		//0xFFFF: diable this initial feature
		if ( isp_top_get_mirrorflip_mode() != 0xFFFF ) {

			mf_info.flip_en = (isp_top_get_mirrorflip_mode() & 0x2) >> 1;
			mf_info.mirror_en = isp_top_get_mirrorflip_mode() & 0x1;

			sensor->hw_ops->set_mirror_flip(sensor->mod.owner_id, mf_info.mirror_en, mf_info.flip_en);

			//0xFx: early mirror/flip operation
			if (isp_top_get_mirrorflip_mode() & 0xF0 ) {

				printf("early mirror/flip %d %d\r\n", mf_info.flip_en, mf_info.mirror_en);
				ret = sensor_init_set_mirror_flip(sensor, &mf_info);
				if (ret) {
					isp_error("sensor initialize  mirror/flip err %d \r\n", ret);
				}
			}
		}


		rts_isp_sensor_access_unprepare();
	} else {
		set_i2c_time = hal_read_curtime_us();
		sensor_init_done = true;
	}
	set_i2c_end_time = hal_read_curtime_us();
	//printf("sensor_initialize done\n");
	if (sensor->sensor_ops->start) {
		ret = sensor->sensor_ops->start(sensor->mod.owner_id);
		if (ret) {
			isp_error("%s start err \r\n",__FUNCTION__);
			goto err;
		}
	}

	sensor->fps = sensor->mode.max_fps;
	sensor->exp_gain.vts = sensor->mode.min_vts;

	if (sensor->patch_ops && sensor->patch_ops->preview_start) {
		ret = sensor->patch_ops->preview_start(sensor->mod.owner_id);
		if (ret) {
			isp_error("%s preview_start err \r\n",__FUNCTION__);
			goto err_sensor_start;
		}
	}
	ret = sensor_high_temp_start(sensor, RTS_ISP_TRUE);
	if (ret) {
		isp_error("%s sensor_high_temp_start err \r\n",__FUNCTION__);
		goto err_patch_start;
	}

	sensor_init_timing(sensor);

	sensor_end_time = hal_read_curtime_us();
	return RTS_ISP_OK;

err_patch_start:
	if (sensor->patch_ops && sensor->patch_ops->preview_stop)
		sensor->patch_ops->preview_stop(sensor->mod.owner_id);
err_sensor_start:
	if (sensor->sensor_ops->stop)
		sensor->sensor_ops->stop(sensor->mod.owner_id);
err:
	sensor_high_temp_start(sensor, RTS_ISP_FALSE);
	sensor_set_power(sensor, RTS_ISP_FALSE);
	isp_error("start sensor fail %d \r\n", ret);
	sensor_init_done = false;
	return ret;
}

static int sensor_stop(struct isp_mod_sensor *sensor)
{
	isp_info("stop sensor\n");

	sensor->fps = 0;
	sensor->set_fps = 0;
	sensor->exp_gain.vts = sensor->mode.min_vts;

	sensor_high_temp_start(sensor, RTS_ISP_FALSE);
	sensor_cleanup_timing(sensor);
	if (sensor->patch_ops && sensor->patch_ops->preview_stop)
		sensor->patch_ops->preview_stop(sensor->mod.owner_id);
	if (sensor->sensor_ops->stop)
		sensor->sensor_ops->stop(sensor->mod.owner_id);
	sensor_set_power(sensor, RTS_ISP_FALSE);
	sensor_init_done = false;
	data_start_error = FALSE;
	frame_end_error = FALSE;

	return RTS_ISP_OK;
}

static int sensor_change_fps(struct isp_mod_sensor *sensor, float fps)
{
	int ret;

	if (float_eq(fps, 0))
		return RTS_ISP_OK;
#ifdef _FPS_LOG_
	printf("change sensor fps to %.3f\n", fps);
#endif
	/*
	 * first send fps change, so ae can change exposure to good range,
	 * use fps_change_notifying to prevent ae set exp gain to sensor
	 */
	sensor->set_fps = fps;
	sensor->fps_change_notifying = RTS_ISP_TRUE;
	ret = isp_core_notify(sensor->mod.owner, ISP_NOTIFY_FPS_CHANGE,
			      &fps, sizeof(fps));
	sensor->fps_change_notifying = RTS_ISP_FALSE;
	if (ret) {
		isp_error("ISP_NOTIFY_FPS_CHANGE error %d \r\n", ret);
		return ret;
	}

	ret = sensor_set_focus(sensor);
	if (ret) {
		isp_error("sensor_set_focus error %d \r\n", ret);
		return ret;
	}
	return sensor_set_exp_gain_fps(sensor, fps, 1);
}

static int mod_sensor_exec_set_fps(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	float fps = *(float *)data;

	if (fps < 0 || fps > sensor->mode.max_fps) {
		printf("fps out of range %.3f max %.3f \r\n", fps, sensor->mode.max_fps);
		return -RTS_ISP_ERANGE;
	}


	if (float_eq(fps, sensor->set_fps))
		return RTS_ISP_OK;

	if (float_eq(sensor->set_fps, 0))
		ret = sensor_start(sensor);
	else if (float_eq(fps, 0))
		ret = sensor_stop(sensor);
	if (ret)
		return ret;

	return sensor_change_fps(sensor, fps);
}

static int sensor_set_mirror_flip(struct isp_mod_sensor *sensor,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int ret;
	int len;
	memset(&mf_info->regs, 0, sizeof(mf_info->regs));

	if (!sensor->sensor_ops->set_mirror_flip) {
		//isp_error("set_mirror_flip is not supported\n");
		return RTS_ISP_OK;
	}

	ret = sensor->sensor_ops->set_mirror_flip(sensor->mod.owner_id,
											  mf_info);
	if (ret)
		return ret;

	sensor->hw_ops->set_mirror_flip(sensor->mod.owner_id, mf_info->mirror_en,
									mf_info->flip_en);

	if (float_ne(sensor->set_fps, 0)) {
		len = sizeof(struct rts_isp_sensor_mirror_flip*);
		ret = isp_mod_sibling_execute(&sensor->mod, MOD_GLOBAL,
									GLOBAL_EXEC_SET_DELAY_FRAMES, mf_info,
									len);
		if (ret)
			return ret;
	}

	mf_info->regs.split_index = mf_info->regs.num;
	mf_info->regs.i2c_info = sensor->info.i2c;

	return isp_driver_write_sync_regs(&mf_info->regs);

}

static int mod_sensor_exec_set_exp_gain(struct isp_mod *mod, void *data)
{
	float max_fps;
	float total_ae_gain, bound_val;
	int temperature;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct isp_sensor_exp_gain *snr_exp_gain = data;
	struct rts_isp_ae_exp_gain *exp_gain;

	if (float_eq(sensor->set_fps, 0))
		max_fps = sensor->mode.max_fps;
	else
		max_fps = sensor->set_fps;

	if (!snr_exp_gain->exp_gain ||
	    snr_exp_gain->fps > max_fps ||
	    snr_exp_gain->fps < sensor->mode.min_fps ||
	    snr_exp_gain->isp_sync_num > 16 ||
	    !snr_exp_gain->get_sync_regs_cb) {
		printf("mod_sensor_exec_set_exp_gain error fps %.3f isp_sync_num %d \r\n", snr_exp_gain->fps, snr_exp_gain->isp_sync_num);
		return -RTS_ISP_ERANGE;
	}


	/* exposure, gain and fps has been verified at mod ae, we trust it */
	exp_gain = snr_exp_gain->exp_gain;
	isp_memcpy(sensor->exp_gain.exposure, exp_gain->exposure,
		   sizeof(sensor->exp_gain.exposure));
	isp_memcpy(sensor->exp_gain.analog_gain, exp_gain->analog_gain,
		   sizeof(sensor->exp_gain.analog_gain));
	isp_memcpy(sensor->exp_gain.digital_gain, exp_gain->digital_gain,
		   sizeof(sensor->exp_gain.digital_gain));

	/* Sensor Temperature Control */
	if (sensor->mode.hdr == LINEAR_MODE && sensor->iq->enable) {
		// TODO: add an iq item to control if enable this feature or not
		if (!sensor->sensor_ops->get_temperature ||
		    !sensor->sensor_ops->get_bound) {
			isp_error(
				"get_temperature or get_bound is not supported\n");
			goto snr_ctl_end;
		}

		if (isp_top_get_status() == RTS_ISP_STREAMING) {
			total_ae_gain = exp_gain->analog_gain[0] *
					exp_gain->digital_gain[0] *
					exp_gain->isp_gain *
					exp_gain->isp_hdr_gain[0];

			temperature = sensor->sensor_ops->get_temperature(
				mod->owner_id);

			bound_val = sensor->sensor_ops->get_bound(mod->owner_id,
								  temperature);

			//printf("%s analog_gain %.2f bound %.2f \n", __func__, sensor->exp_gain.analog_gain[0], bound_val);

			if (exp_gain->analog_gain[0] > bound_val) {
				sensor->exp_gain.analog_gain[0] = bound_val;
			} else {
				sensor->exp_gain.analog_gain[0] =
					exp_gain->analog_gain[0];
			}

			exp_gain->isp_gain = total_ae_gain /
					     sensor->exp_gain.analog_gain[0] /
					     sensor->exp_gain.digital_gain[0];


		}
	}

snr_ctl_end:

	if (sensor->fps_change_notifying) {
		sensor->exp_gain_backup.isp_sync_num =
			snr_exp_gain->isp_sync_num;
		sensor->exp_gain_backup.get_sync_regs_cb =
			snr_exp_gain->get_sync_regs_cb;
		sensor->exp_gain_backup.hdr = exp_gain->hdr;
		isp_memcpy(sensor->exp_gain_backup.isp_hdr_gain,
			   exp_gain->isp_hdr_gain,
			   sizeof(sensor->exp_gain_backup.isp_hdr_gain));
		sensor->exp_gain_backup.isp_gain = exp_gain->isp_gain;
	}

	return sensor_set_exp_gain_fps_ex(sensor, snr_exp_gain->fps,
					  snr_exp_gain, 1);
}

/* Sensor Temperature Control */
static int sensor_set_gain(struct isp_mod_sensor *sensor,
			   struct rts_isp_sensor_again *again_info)
{
	int ret;
	uint32_t temperature;
	float bound_val;

	memset(&again_info->regs, 0, sizeof(again_info->regs));

	if (!sensor->sensor_ops->get_temperature) {
		isp_error("get_temperature is not supported\n");
		return RTS_ISP_OK;
	}

	if (!sensor->sensor_ops->get_bound) {
		isp_error("get_bound is not supported\n");
		return RTS_ISP_OK;
	}

	if (!sensor->sensor_ops->set_again) {
		isp_error("set_again is not supported\n");
		return RTS_ISP_OK;
	}

	temperature = sensor->sensor_ops->get_temperature(sensor->mod.owner_id);
	bound_val = sensor->sensor_ops->get_bound(sensor->mod.owner_id,
						  temperature);

	if (sensor->exp_gain.analog_gain[0] > bound_val) {
		sensor->exp_gain.analog_gain[0] = bound_val;
	}
	again_info->again_val = sensor->exp_gain.analog_gain[0];

	again_info->isp_gain_val = again_info->total_gain /
				   sensor->exp_gain.analog_gain[0] /
				   sensor->exp_gain.digital_gain[0];

	ret = sensor->sensor_ops->set_again(sensor->mod.owner_id, again_info);
	if (ret)
		return ret;

	again_info->regs.split_index = again_info->regs.num;
	again_info->regs.i2c_info = sensor->info.i2c;
	again_info->regs.isp_gain = (uint32_t)(again_info->isp_gain_val * 2048);

	again_info->regs.isp_gain_delay = 1;

	return isp_driver_write_sync_regs(&again_info->regs);
}

/* Sensor Temperature Control */
static int mod_sensor_exec_set_gain(struct isp_mod *mod, void *data)
{
	struct rts_isp_sensor_again *again_info = data;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	//printf("%s enable %d \n", __func__, sensor->iq->enable);
	if (sensor->iq->enable) {
		sensor->statis_done_cnt++;
		if ( sensor->statis_done_cnt >= sensor->iq->interval ) {
			//printf("%s interval %d \n", __func__, sensor->iq->interval);
			sensor->statis_done_cnt = 0;
			return sensor_set_gain(sensor, again_info);
		}
	}

	return RTS_ISP_OK;
}

static int mod_sensor_exec_read_sen_reg(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct rts_isp_i2c_reg *reg = data;

	if (float_eq(sensor->set_fps, 0))
		return -RTS_ISP_ENOTREADY;
	return rts_isp_read_i2c_reg(&sensor->info.i2c, reg);
}

static int mod_sensor_exec_write_sen_reg(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct rts_isp_i2c_reg *reg = data;

	if (float_eq(sensor->set_fps, 0))
		return -RTS_ISP_ENOTREADY;
	return rts_isp_write_i2c_reg(&sensor->info.i2c, reg);
}

static int mod_sensor_exec_set_dummy(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	sensor->flick_dummy = *(uint32_t *)data;

	return sensor_set_exp_gain_fps(sensor, sensor->fps, 0);
}

static int mod_sensor_exec_set_focus(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	int ret;

	sensor->focus_pos = *(uint32_t *)data;

	ret = sensor_set_focus(sensor);
	if (ret)
		isp_perror(ret, "sensor set focus fail");
	return ret;
}

static int mod_sensor_exec_enum_modes(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	*(struct rts_isp_sensor_modes *)data = sensor->info.modes;

	return RTS_ISP_OK;
}

static int mod_sensor_exec_get_mode(struct isp_mod *mod, void *data)
{
	struct rts_isp_sensor_mode *mode = data;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	mode->hdr = sensor->mode.hdr;
	mode->size = sensor->mode.size.isp;
	mode->fps = sensor->mode.max_fps;

	return RTS_ISP_OK;
}

static int mod_sensor_exec_set_mode(struct isp_mod *mod, void *data)
{
	int ret;
	struct rts_isp_sensor_mode *mode = data;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	const struct rts_isp_sensor_modes *modes = &sensor->info.modes;

	if (sensor->set_fps)
		return -RTS_ISP_EBUSY;

	mode->size.w = sensor->mode.size.isp.w;  // force fixed resolution after crop
	mode->size.h = sensor->mode.size.isp.h; // force fixed resolution after crop


	if (check_mode(mode)) {
		isp_error("%s check_mode failed \n", __func__);
		return -RTS_ISP_EINVAL;
	}
	if (check_mode_compatible(mode, modes)) {
		isp_error("%s check_mode_compatible failed \n", __func__);
		return -RTS_ISP_EINVAL;
	}

	if (mode->hdr == sensor->mode.hdr &&
	    mode->size.w == sensor->mode.size.isp.w &&
	    mode->size.h == sensor->mode.size.isp.h &&
	    float_eq(mode->fps, sensor->mode.max_fps))
		return RTS_ISP_OK;

	ret = sensor_change_mode(sensor, mode);
	if (ret)
		return ret;
	return isp_core_notify(mod->owner, ISP_NOTIFY_HDR_MODE_CHANGE, NULL, 0);
}

static int mod_sensor_exec_set_mirror_flip(struct isp_mod *mod, void *data)
{
	struct rts_isp_sensor_mirror_flip *mf_info = data;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	return sensor_set_mirror_flip(sensor, mf_info);
}

static struct isp_mod_action_info sensor_exec_actions[] = {
	ISP_MOD_ACTION(SENSOR_EXEC_SET_FPS, mod_sensor_exec_set_fps),
	ISP_MOD_ACTION(SENSOR_EXEC_SET_EXP_GAIN, mod_sensor_exec_set_exp_gain),
	ISP_MOD_ACTION(SENSOR_EXEC_READ_SEN_REG, mod_sensor_exec_read_sen_reg),
	ISP_MOD_ACTION(SENSOR_EXEC_WRITE_SEN_REG,
		       mod_sensor_exec_write_sen_reg),
	ISP_MOD_ACTION(SENSOR_EXEC_SET_DUMMY, mod_sensor_exec_set_dummy),
	ISP_MOD_ACTION(SENSOR_EXEC_SET_FOCUS, mod_sensor_exec_set_focus),
	ISP_MOD_ACTION(SENSOR_EXEC_ENUM_MODES, mod_sensor_exec_enum_modes),
	ISP_MOD_ACTION(SENSOR_EXEC_GET_MODE, mod_sensor_exec_get_mode),
	ISP_MOD_ACTION(SENSOR_EXEC_SET_MODE, mod_sensor_exec_set_mode),
	/* Sensor Temperature Control */
	ISP_MOD_ACTION(SENSOR_EXEC_SET_GAIN, mod_sensor_exec_set_gain),
	// ISP_MOD_ACTION(SENSOR_EXEC_SET_MIRROR_FLIP, mod_sensor_exec_set_mirror_flip),
};

static int mod_sensor_info_size(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	rts_isp_size_t *size = data;

	*size = sensor->mode.size.snr;
	return RTS_ISP_OK;
}

static int mod_sensor_info_crop(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	rts_isp_rect_t *crop = data;

	crop->start = sensor->start;
	crop->size = sensor->mode.size.isp;

	return RTS_ISP_OK;
}

static int mod_sensor_info_timing(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct isp_sensor_timing *timing = data;

	if (float_eq(sensor->set_fps, 0))
		return -RTS_ISP_ENOTREADY;

	*timing = sensor->timing;

	return RTS_ISP_OK;
}

static int mod_sensor_info_interface(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	const struct rts_isp_interface_info **info = data;

	*info = &sensor->interface;

	return RTS_ISP_OK;
}

static int mod_sensor_info_bound_snr_name(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	isp_strlcpy(data, sensor->sensor_ops->name,
		    ISP_AID_SIZE(SENSOR_INFO_BOUND_SNR_NAME));
	return RTS_ISP_OK;
}

static int mod_sensor_info_vcm(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct rts_isp_focus_info *value = data;

	*value = sensor->info.focus;
	return RTS_ISP_OK;
}

static int mod_sensor_info_patch_ops(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	*(const void **)data = sensor->patch_ops;

	return RTS_ISP_OK;
}

static int mod_sensor_info_hdr_mode(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct isp_sensor_mode *mode = data;

	*mode = sensor->mode;

	return RTS_ISP_OK;
}

static int mod_sensor_info_version(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	const struct rts_isp_sensor_ops *ops;
	uint16_t *version = data;

	if (sensor->sensor_ops) {
		*version = (sensor->sensor_ops->ops_version &
			    SENSOR_VERSION_MASK);
		return RTS_ISP_OK;
	}
	ret = isp_sensor_get_ops(isp_top_get_snrm(), mod->owner_id, &ops);
	if (ret)
		return ret;
	*version = ops->ops_version & SENSOR_VERSION_MASK;

	return RTS_ISP_OK;
}

static int mod_sensor_info_tune_ops(struct isp_mod *mod, void *data)
{
	const struct rts_isp_exp_gain_tune_ops **ops = data;

	*ops = &exp_gain_tune_ops;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info sensor_info_actions[] = {
	ISP_MOD_ACTION(SENSOR_INFO_SIZE, mod_sensor_info_size),
	ISP_MOD_ACTION(SENSOR_INFO_CROP, mod_sensor_info_crop),
	ISP_MOD_ACTION(SENSOR_INFO_TIMING, mod_sensor_info_timing),
	ISP_MOD_ACTION(SENSOR_INFO_INTERFACE, mod_sensor_info_interface),
	ISP_MOD_ACTION(SENSOR_INFO_HDR_MODE, mod_sensor_info_hdr_mode),
	ISP_MOD_ACTION(SENSOR_INFO_BOUND_SNR_NAME,
		       mod_sensor_info_bound_snr_name),
	ISP_MOD_ACTION(SENSOR_INFO_VCM, mod_sensor_info_vcm),
	ISP_MOD_ACTION(SENSOR_INFO_PATCH_OPS, mod_sensor_info_patch_ops),
	ISP_MOD_ACTION(SENSOR_INFO_VERSION, mod_sensor_info_version),
	ISP_MOD_ACTION(SENSOR_INFO_TUNE_OPS, mod_sensor_info_tune_ops),
	//ISP_MOD_ACTION(SENSOR_INFO_FRONT_SIZE, mod_sensor_info_front_size),
};

static int mod_sensor_iq_change(struct isp_mod *mod, void *data)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	int ret;
	int iq_sel = 0;
	int night = *(int *)data;

	sensor->iq = isp_iq_get_high_temp(mod->owner_id);
	//printf("%s enable %d\n", __func__, sensor->iq->enable);
	if (!sensor->iq)
		return -RTS_ISP_ENOITEM;

	if (sensor->patch_ops) {

		ret = isp_mod_sibling_get_info(mod, MOD_IQ, IQ_INFO_IQ_SEL,
					       &iq_sel, sizeof(iq_sel));
		if (ret)
			return ret;
		ret = sensor->patch_ops->iq_change(mod->owner_id,
						   iq_sel, night);
		if (ret)
			return ret;
	}

	if (isp_top_get_status() == RTS_ISP_STREAMING)
		return sensor_high_temp_start(sensor, RTS_ISP_TRUE);

	return RTS_ISP_OK;
}

static struct isp_mod_action_info sensor_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_sensor_iq_change),
};

static int sensor_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	switch (ctrl->id) {
	case RTS_V4L2_CID_SENSOR_ISP_GAIN:
		sensor->isp_gain_ctrl->val = sensor->isp_gain * 256;
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int sensor_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct rts_isp_sensor_mirror_flip mf_info;

	switch (ctrl->id) {
		case RTS_V4L2_CID_SENSOR_MIRROR_FLIP:

		//printf("RTS_V4L2_CID_SENSOR_MIRROR_FLIP %d %d\n", ctrl->val, ctrl->cur.val);
			mf_info.flip_en = (ctrl->val & 0x2) >> 1;
			mf_info.mirror_en = ctrl->val & 0x1;
			if ( mf_info.flip_en || mf_info.mirror_en ) {
				printf("flip_en %d mirror_en %d\n", mf_info.flip_en, mf_info.mirror_en);
			}

			if (sensor_init_done || isp_top_get_fcs_ready()) {
				ret = sensor_set_mirror_flip(sensor, &mf_info);
				if (ret == -RTS_ISP_ENOTREADY) {
					printf("sensor is not ready or start, try again later\n");
					ctrl->val = ctrl->cur.val;
					ret = RTS_ISP_OK;
				}
			}
			break;
		case RTS_V4L2_CID_SENSOR_SHORT_EXP_THD:
			if (!sensor->sensor_ops->set_short_exp_exit_thd ||
			    !sensor->sensor_ops->get_short_exp_mode) {
				printf(
					"short exp mode is not implemented by this sensor.\n");
				ctrl->val = ctrl->cur.val;
				return RTS_ISP_OK;
			}

			sensor->sensor_ops->set_short_exp_exit_thd(
				sensor->mod.owner_id, ctrl->val);
			if (ctrl->val <= 512) {
					uint32_t vhdr_en = 1;
					uint32_t awb_clip = 0;
					uint32_t ae_dyn_vhdr_mode = 1;

					ret = isp_mod_sibling_execute(mod, MOD_GLOBAL, GLOBAL_EXEC_SET_VHDR_ENABLE, &vhdr_en, sizeof(vhdr_en));
					if (ret)
						break;
					ret = isp_mod_sibling_execute(mod, MOD_AWB, AWB_EXEC_SET_AWB_CLIP, &awb_clip, sizeof(awb_clip));
					if (ret)
						break;
					ret = isp_mod_sibling_execute(mod, MOD_AE, AE_EXEC_SET_DYN_VHDR_MODE, &ae_dyn_vhdr_mode, sizeof(ae_dyn_vhdr_mode));
			}
			break;
		case RTS_V4L2_CID_SENSOR_ISP_GAIN_MODE:
			sensor->isp_gain_mode_ctrl->cur.val = ctrl->val;
			break;
		case RTS_V4L2_CID_SENSOR_ISP_GAIN:
			sensor->isp_gain_ctrl->cur.val = ctrl->val;
			break;
		default:
			return -RTS_ISP_ECTRL;
	}

	return ret;
}

static const struct v4l2_ctrl_ops sensor_ctrl_ops = {
	.g_volatile_ctrl = sensor_g_volatile_ctrl,
	.s_ctrl = sensor_s_ctrl,
};

static int isp_mod_sensor_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);
	struct v4l2_ctrl_handler *handler = phandler;
	uint8_t mirror_en, flip_en;
	if ( isp_top_get_mirrorflip_mode() != 0xFFFF ) {
		mirror_en = isp_top_get_mirrorflip_mode() & 0x1;
		flip_en = (isp_top_get_mirrorflip_mode() & 0x2) >> 1;
		sensor->hw_ops->set_mirror_flip(sensor->mod.owner_id, mirror_en, flip_en);
	}

	sensor->hw_ops->get_mirror_flip(mod->owner_id, &mirror_en, &flip_en);

	/*
	* 0: disable mirror and flip
	* 1: enable mirror
	* 2: enable flip
	* 3: enable flip and mirror
	*/
	const struct v4l2_ctrl_config sensor_mirror_flip_config = {
		.ops = &sensor_ctrl_ops,
		.id = RTS_V4L2_CID_SENSOR_MIRROR_FLIP,
		.name = "Enable sensor mirror and flip",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 3,
		.step = 1,
		.def = mirror_en | flip_en << 1,
	};

	const struct v4l2_ctrl_config sensor_short_exp_mode_thd_config = {
		.ops = &sensor_ctrl_ops,
		.id = RTS_V4L2_CID_SENSOR_SHORT_EXP_THD,
		.name = "Sensor short exposure mode threshold",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 65535,
		.step = 1,
		.def = 0,
	};
	const struct v4l2_ctrl_config sensor_isp_gain_mode_config = {
		.ops = &sensor_ctrl_ops,
		.id = RTS_V4L2_CID_SENSOR_ISP_GAIN_MODE,
		.name = "Sensor ISP gain mode",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = RTS_ISP_SENSOR_ISP_GAIN_MODE_AUTO,
		.max = RTS_ISP_SENSOR_ISP_GAIN_MODE_MANUAL,
		.step = 1,
		.def = RTS_ISP_SENSOR_ISP_GAIN_MODE_AUTO,
	};
	const struct v4l2_ctrl_config sensor_isp_gain_config = {
		.ops = &sensor_ctrl_ops,
		.id = RTS_V4L2_CID_SENSOR_ISP_GAIN,
		.name = "Sensor ISP gain",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 256,
		.max = 65535,
		.step = 1,
		.def = 256,
		.flags = V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_EXECUTE_ON_WRITE
	};

	sensor->mirror_flip_ctrl =
		rtsv_ctrl_new_custom(handler, &sensor_mirror_flip_config, mod);

	sensor->short_exp_thd_ctrl = rtsv_ctrl_new_custom(
		handler, &sensor_short_exp_mode_thd_config, mod);

	sensor->isp_gain_mode_ctrl = rtsv_ctrl_new_custom(
		handler, &sensor_isp_gain_mode_config, mod);
	sensor->isp_gain_ctrl = rtsv_ctrl_new_custom(
		handler, &sensor_isp_gain_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add sensor ctrl fail");
		return handler->error;
	}

	sensor->isp_gain = sensor_isp_gain_config.def / 256.0;
	return RTS_ISP_OK;
}

static int isp_mod_sensor_hardware_init(struct isp_mod *mod)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	sensor->hw_ops->init_vreg(mod->owner_id);

	return RTS_ISP_OK;
}

static int isp_mod_sensor_init(struct isp_mod *mod)
{
	int ret;
	int hdr_mode = 0;
	struct isp_mod_sensor *sensor;

	sensor = get_mod(mod, sensor);

	ret = sensor_init_plugin(sensor);
	if (ret) {
		isp_error("sensor_init_plugin err\n");
		goto err;
	}
	ret = sensor_get_info(sensor);
	if (ret) {
		isp_error("sensor_get_info err\n");
		goto err;
	}
	hdr_mode = isp_top_get_hdr_mode();
	if ( hdr_mode >= sensor->info.modes.num ) {
		hdr_mode = 0;
		isp_error("hdr_mode %d is over sensor driver num %d \n", hdr_mode, sensor->info.modes.num);
	}
	printf("hdr_mode %d sensor driver num %d \n", hdr_mode, sensor->info.modes.num);
	ret = sensor_change_mode(sensor, &sensor->info.modes.mode[hdr_mode]);
	if (ret) {
		isp_error("sensor_change_mode err\n");
		goto err;
	}

	ret = isp_timer_init(&sensor->timer, isp_top_get_poll(),
			     sensor_timer_callback, mod);
	if (ret) {
		isp_error("isp_timer_init err\n");
		goto err;
	}
	sensor->param = &isp_iq_get_algo_param(mod->owner_id)->high_temp;
	if (!sensor->param) {
		isp_error("get high_temp algo param fail\n");
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	sensor->hw_ops = isp_hw_sensor_get_ops();
	sensor->fast_ae_cnt = 0;
	sensor->statis_done_cnt	= 0;
	return RTS_ISP_OK;

err:
	sensor_cleanup_plugin(sensor);
	return ret;
}

static int isp_mod_sensor_cleanup(struct isp_mod *mod)
{
	struct isp_mod_sensor *sensor = get_mod(mod, sensor);

	isp_timer_cleanup(&sensor->timer);
	sensor->fast_ae_cnt = 0;
	sensor->statis_done_cnt	= 0;
	sensor_cleanup_plugin(sensor);

	return RTS_ISP_OK;
}

static struct isp_mod_sensor sensor;

int isp_register_mod_sensor(void)
{
	memset(&sensor, 0, sizeof(sensor));
	sensor.mod.id = MOD_SENSOR;
	sensor.mod.name = "sensor";
	sensor.mod.init = isp_mod_sensor_init;
	sensor.mod.hardware_init = isp_mod_sensor_hardware_init;
	sensor.mod.cleanup = isp_mod_sensor_cleanup;
	sensor.mod.add_ctrl = isp_mod_sensor_add_ctrl;
	sensor.mod.notify_bits = ISP_IQ_CHANGE_BIT;
	sensor.mod.exec_actions = sensor_exec_actions;
	sensor.mod.exec_actions_num = ARRAY_SIZE(sensor_exec_actions);
	sensor.mod.info_actions = sensor_info_actions;
	sensor.mod.info_actions_num = ARRAY_SIZE(sensor_info_actions);
	sensor.mod.notify_actions = sensor_notify_actions;
	sensor.mod.notify_actions_num = ARRAY_SIZE(sensor_notify_actions);
	return isp_mod_register(&sensor.mod);
}

void isp_unregister_mod_sensor(void)
{
	isp_mod_unregister(&sensor.mod);
}


