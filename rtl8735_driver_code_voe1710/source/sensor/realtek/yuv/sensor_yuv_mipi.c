/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define RESOLUTION 0	/* 0=2M, 1=HD */

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct YUV_SENSOR_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

static struct YUV_SENSOR_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_YUV_SENSOR_fps_info_asic[] = {
#if RESOLUTION
	{60.0f, 1600, 72000000}
#else
	{30.0f, 2000, 90000000}
#endif
};

static int YUV_SENSOR_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info) {
		return -RTS_ISP_EINVAL;
	}

	info->modes.mode[0].fps = g_YUV_SENSOR_fps_info_asic[0].fps;
	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
#if RESOLUTION
	info->modes.mode[0].size.w = 1600;
	info->modes.mode[0].size.h = 1300;
#else
	info->modes.mode[0].size.w = 1280;
	info->modes.mode[0].size.h = 720;
#endif
	info->modes.num = 1;

	info->i2c.i2c_id = 0x48;//0x90 divide 2
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 50000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *YUV_SENSOR_get_fps_info(float fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_YUV_SENSOR_fps_info_asic); i++)
		if (fps == g_YUV_SENSOR_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_YUV_SENSOR_fps_info_asic))
		return NULL;
	return &g_YUV_SENSOR_fps_info_asic[i];

}

static int YUV_SENSOR_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct YUV_SENSOR_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = YUV_SENSOR_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//set_init_i2c_regs(info->sensor_regs[0], g_YUV_SENSOR_i2c_init_regs_asic, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = YUV_SENSOR;
	info->interface.bit_depth = SNR_8BIT;
	info->mipi_behavor = NONE_HDR;
	info->interface.yuv_type = SNR_UYVY;

#if RESOLUTION
	info->size.w = 1600;
	info->size.h = 1300;
#else
	info->size.w = 1280;
	info->size.h = 720;
#endif
	info->start.x = 0;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 750;
	
	info->max_vts = info->min_vts * 15;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */

	return RTS_ISP_OK;
}


static int YUV_SENSOR_start(uint32_t isp_id)
{
	struct YUV_SENSOR_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}



static uint16_t get_sensor_gain_reg(float fAGain, struct YUV_SENSOR_status *status)
{
	return RTS_ISP_OK;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return RTS_ISP_OK;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int YUV_SENSOR_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int YUV_SENSOR_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int YUV_SENSOR_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	return RTS_ISP_OK;
}

static int YUV_SENSOR_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	return RTS_ISP_OK;
}

static int YUV_SENSOR_check(uint32_t isp_id)
{
	printf("[Zako] %s,%d\r",__FUNCTION__, __TIME__);
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops YUV_SENSOR_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "YUV_SENSOR",

	.get_info = YUV_SENSOR_get_info,
	.get_init_info = YUV_SENSOR_get_init_info,
	.start = YUV_SENSOR_start,
	.get_exposure_gain_info = YUV_SENSOR_get_exposure_gain_info,
	.get_tuned_again = YUV_SENSOR_get_tuned_again,
	.get_tuned_dgain = YUV_SENSOR_get_tuned_dgain,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &YUV_SENSOR_ops;
}


