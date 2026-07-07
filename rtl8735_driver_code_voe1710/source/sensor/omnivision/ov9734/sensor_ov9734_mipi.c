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

#define ORIENTATION 0			/* 0=default, 1=rotate180*/
#define SENSOR_ID_SELECTION	0	/* 0=0x78, 1 = 0x7A*/
#define RESOLUTION	1			/* 0=1280*720*30, 1=640*360*60 */

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ov9734_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct ov9734_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct ov9734_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ov9734_fps_info_asic[] = {
#if (RESOLUTION == 0)
	{30.0f, 1478, 36000000},
#else
	{60.0f, 1478, 36000000},
#endif
};

static struct rts_isp_i2c_reg g_ov9734_i2c_init_regs_asic_hd30[] = {
	{0x0103, 0x01},
	{0x0100, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3007, 0x00},
	{0x3010, 0x00},
	{0x3011, 0x08},
	{0x3014, 0x22},
	{0x301e, 0x15},
	{0x3030, 0x19},
	{0x3080, 0x02},
	{0x3081, 0x3c},
	{0x3082, 0x04},
	{0x3083, 0x00},
	{0x3084, 0x02},
	{0x3085, 0x01},
	{0x3086, 0x01},
	{0x3089, 0x01},
	{0x308a, 0x00},
	{0x3103, 0x01},
	{0x3600, 0x55},
	{0x3601, 0x02},
	{0x3605, 0x22},
	{0x3611, 0xe7},
	{0x3654, 0x10},
	{0x3655, 0x77},
	{0x3656, 0x77},
	{0x3657, 0x07},
	{0x3658, 0x22},
	{0x3659, 0x22},
	{0x365a, 0x02},
	{0x3784, 0x05},
	{0x3785, 0x55},
	{0x37c0, 0x07},
	{0x3800, 0x00},
	{0x3801, 0x04},
	{0x3802, 0x00},
	{0x3803, 0x04},
	{0x3804, 0x05},
	{0x3805, 0x0b},
	{0x3806, 0x02},
	{0x3807, 0xdb},
	{0x3808, 0x05},
	{0x3809, 0x00},
	{0x380a, 0x02},
	{0x380b, 0xd0},
	{0x380c, 0x05},	//5c6 = 1478
	{0x380d, 0xc6},
	{0x380e, 0x03},	//322 = 802
	{0x380f, 0x22},
	{0x3810, 0x00},
	{0x3811, 0x04},
	{0x3812, 0x00},
	{0x3813, 0x04},
	{0x3816, 0x00},
	{0x3817, 0x00},
	{0x3818, 0x00},
	{0x3819, 0x04},
	{0x3820, 0x18},
	{0x3821, 0x00},
	{0x382c, 0x06},
	{0x3500, 0x00},
	{0x3501, 0x31},
	{0x3502, 0x00},
	{0x3503, 0x03},
	{0x3504, 0x00},
	{0x3505, 0x00},
	{0x3509, 0x10},
	{0x350a, 0x00},
	{0x350b, 0x40},
	{0x3d00, 0x00},
	{0x3d01, 0x00},
	{0x3d02, 0x00},
	{0x3d03, 0x00},
	{0x3d04, 0x00},
	{0x3d05, 0x00},
	{0x3d06, 0x00},
	{0x3d07, 0x00},
	{0x3d08, 0x00},
	{0x3d09, 0x00},
	{0x3d0a, 0x00},
	{0x3d0b, 0x00},
	{0x3d0c, 0x00},
	{0x3d0d, 0x00},
	{0x3d0e, 0x00},
	{0x3d0f, 0x00},
	{0x3d80, 0x00},
	{0x3d81, 0x00},
	{0x3d82, 0x38},
	{0x3d83, 0xa4},
	{0x3d84, 0x00},
	{0x3d85, 0x00},
	{0x3d86, 0x1f},
	{0x3d87, 0x03},
	{0x3d8b, 0x00},
	{0x3d8f, 0x00},
	{0x4001, 0xe0},
	{0x4009, 0x0b},
	{0x4300, 0x03},
	{0x4301, 0xff},
	{0x4304, 0x00},
	{0x4305, 0x00},
	{0x4309, 0x00},
	{0x4600, 0x00},
	{0x4601, 0x80},
	{0x4800, 0x00},
	{0x4805, 0x00},
	{0x4821, 0x50},
	{0x4823, 0x50},
	{0x4837, 0x2d},
	{0x4a00, 0x00},
	{0x4f00, 0x80},
	{0x4f01, 0x10},
	{0x4f02, 0x00},
	{0x4f03, 0x00},
	{0x4f04, 0x00},
	{0x4f05, 0x00},
	{0x4f06, 0x00},
	{0x4f07, 0x00},
	{0x4f08, 0x00},
	{0x4f09, 0x00},
	{0x5000, 0x2f},
	{0x500c, 0x00},
	{0x500d, 0x00},
	{0x500e, 0x00},
	{0x500f, 0x00},
	{0x5010, 0x00},
	{0x5011, 0x00},
	{0x5012, 0x00},
	{0x5013, 0x00},
	{0x5014, 0x00},
	{0x5015, 0x00},
	{0x5016, 0x00},
	{0x5017, 0x00},
	{0x5080, 0x00},
	{0x5180, 0x01},
	{0x5181, 0x00},
	{0x5182, 0x01},
	{0x5183, 0x00},
	{0x5184, 0x01},
	{0x5185, 0x00},
	{0x5708, 0x06},
	{0x380f, 0x2a},
	{0x5780, 0x3e},
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x01},
	{0x5786, 0x00},
	{0x5787, 0x04},
	{0x5788, 0x02},
	{0x5789, 0x0f},
	{0x578a, 0xfd},
	{0x578b, 0xf5},
	{0x578c, 0xf5},
	{0x578d, 0x03},
	{0x578e, 0x08},
	{0x578f, 0x0c},
	{0x5790, 0x08},
	{0x5791, 0x04},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3},
	{0x5000, 0x3f},
	{0x3801, 0x00},//;04
	{0x3803, 0x00},//;04
	{0x3805, 0x0f},//;0b
	{0x3807, 0xdf},//;db
	{0x3809, 0x08},//;00
	{0x380b, 0xd8},//;d0
	{0x3811, 0x04},
	{0x3813, 0x04},
	{0x4003, 0x40},	
	{0x0100, 0x01},	
};

static struct rts_isp_i2c_reg g_ov9734_i2c_init_regs_asic_vga60[] = {
	{0x0103, 0x01},
	{0x0100, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3007, 0x00},
	{0x3010, 0x00},
	{0x3011, 0x08},
	{0x3014, 0x22},
	{0x301e, 0x15},
	{0x3030, 0x19},
	{0x3080, 0x02},
	{0x3081, 0x3c},
	{0x3082, 0x04},
	{0x3083, 0x00},
	{0x3084, 0x02},
	{0x3085, 0x01},
	{0x3086, 0x01},
	{0x3089, 0x01},
	{0x308a, 0x00},
	{0x3103, 0x01},
	{0x3600, 0x55},
	{0x3601, 0x02},
	{0x3605, 0x22},
	{0x3611, 0xe7},
	{0x3654, 0x10},
	{0x3655, 0x77},
	{0x3656, 0x77},
	{0x3657, 0x07},
	{0x3658, 0x22},
	{0x3659, 0x22},
	{0x365a, 0x02},
	{0x3784, 0x05},
	{0x3785, 0x55},
	{0x37c0, 0x07},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x05},
	{0x3805, 0x0f},
	{0x3806, 0x02},
	{0x3807, 0xdf},
	{0x3808, 0x02},
	{0x3809, 0x80},	//0x80
	{0x380a, 0x01},
	{0x380b, 0x68},	//0x68
	{0x380c, 0x05},	//5c6 = 1478
	{0x380d, 0xc6},
	{0x380e, 0x01},	//194 = 404
	{0x380f, 0x94},
	{0x3810, 0x00},
	{0x3811, 0x03},
	{0x3812, 0x00},
	{0x3813, 0x04},
	{0x3816, 0x00},
	{0x3817, 0x00},
	{0x3818, 0x00},
	{0x3819, 0x04},
	{0x3820, 0x1b},
	{0x3821, 0x09},
	{0x382c, 0x06},
	{0x3500, 0x00},
	{0x3501, 0x18},
	{0x3502, 0x00},
	{0x3503, 0x03},
	{0x3504, 0x00},
	{0x3505, 0x00},
	{0x3509, 0x10},
	{0x350a, 0x00},
	{0x350b, 0x40},
	{0x3d00, 0x00},
	{0x3d01, 0x00},
	{0x3d02, 0x00},
	{0x3d03, 0x00},
	{0x3d04, 0x00},
	{0x3d05, 0x00},
	{0x3d06, 0x00},
	{0x3d07, 0x00},
	{0x3d08, 0x00},
	{0x3d09, 0x00},
	{0x3d0a, 0x00},
	{0x3d0b, 0x00},
	{0x3d0c, 0x00},
	{0x3d0d, 0x00},
	{0x3d0e, 0x00},
	{0x3d0f, 0x00},
	{0x3d80, 0x00},
	{0x3d81, 0x00},
	{0x3d82, 0x38},
	{0x3d83, 0xa4},
	{0x3d84, 0x00},
	{0x3d85, 0x00},
	{0x3d86, 0x1f},
	{0x3d87, 0x03},
	{0x3d8b, 0x00},
	{0x3d8f, 0x00},
	{0x4001, 0xe0},
	{0x4009, 0x05},
	{0x4300, 0x03},
	{0x4301, 0xff},
	{0x4304, 0x00},
	{0x4305, 0x00},
	{0x4309, 0x00},
	{0x4600, 0x00},
	{0x4601, 0x40},
	{0x4800, 0x00},
	{0x4805, 0x00},
	{0x4821, 0x50},
	{0x4823, 0x50},
	{0x4837, 0x2d},
	{0x4a00, 0x00},
	{0x4f00, 0x80},
	{0x4f01, 0x10},
	{0x4f02, 0x00},
	{0x4f03, 0x00},
	{0x4f04, 0x00},
	{0x4f05, 0x00},
	{0x4f06, 0x00},
	{0x4f07, 0x00},
	{0x4f08, 0x00},
	{0x4f09, 0x00},
	{0x5000, 0x2f},
	{0x500c, 0x00},
	{0x500d, 0x00},
	{0x500e, 0x00},
	{0x500f, 0x00},
	{0x5010, 0x00},
	{0x5011, 0x00},
	{0x5012, 0x00},
	{0x5013, 0x00},
	{0x5014, 0x00},
	{0x5015, 0x00},
	{0x5016, 0x00},
	{0x5017, 0x00},
	{0x5080, 0x00},
	{0x5180, 0x01},
	{0x5181, 0x00},
	{0x5182, 0x01},
	{0x5183, 0x00},
	{0x5184, 0x01},
	{0x5185, 0x00},
	{0x5708, 0x06},
	{0x5780, 0x3e},
	{0x5781, 0x0f},
	{0x5782, 0x44},
	{0x5783, 0x02},
	{0x5784, 0x01},
	{0x5785, 0x01},
	{0x5786, 0x00},
	{0x5787, 0x04},
	{0x5788, 0x02},
	{0x5789, 0x0f},
	{0x578a, 0xfd},
	{0x578b, 0xf5},
	{0x578c, 0xf5},
	{0x578d, 0x03},
	{0x578e, 0x08},
	{0x578f, 0x0c},
	{0x5790, 0x08},
	{0x5791, 0x04},
	{0x5792, 0x00},
	{0x5793, 0x52},
	{0x5794, 0xa3},
	{0x5000, 0x3f},
	{0x0100, 0x01},
};

static int ov9734_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
#if(RESOLUTION == 0)
	info->modes.mode[0].size.w = 1280;
	info->modes.mode[0].size.h = 720;
	info->modes.mode[0].fps = g_ov9734_fps_info_asic[0].fps;
#else
	info->modes.mode[0].size.w = 640;
	info->modes.mode[0].size.h = 360;
	info->modes.mode[0].fps = g_ov9734_fps_info_asic[0].fps;
#endif
	info->modes.num = 1;
	
#if (SENSOR_ID_SELECTION == 0)
	info->i2c.i2c_id = 0x36;
#else
	info->i2c.i2c_id = 0x10;
#endif

	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 4000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 8000);
	
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *ov9734_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_ov9734_fps_info_asic); i++)
		if (fps == g_ov9734_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_ov9734_fps_info_asic))
		return NULL;
	return &g_ov9734_fps_info_asic[i];

}

static int ov9734_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ov9734_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = ov9734_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

#if (RESOLUTION == 0)		
	set_init_i2c_regs(info->sensor_regs[0], g_ov9734_i2c_init_regs_asic_hd30, 3000);
#else
	set_init_i2c_regs(info->sensor_regs[0], g_ov9734_i2c_init_regs_asic_vga60, 3000);
#endif	

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0;
	//info->interface.mipi.hs_term = 0x5;
	info->interface.mipi.hs_term = 0x3;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
#if (RESOLUTION == 0)
	info->size.w = 1288;
	info->size.h = 728;
	info->start.x = 0;
	info->start.y = 1;
	info->min_vts = status->min_vts = 810;
#else
	info->size.w = 640;
	info->size.h = 360;
	info->start.x = 0;
	info->start.y = 0;
	info->min_vts = status->min_vts = 404;
#endif
	//info->max_vts = 6750;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->max_vts = info->min_vts * 15;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int ov9734_start(uint32_t isp_id)
{
	struct ov9734_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int ov9734_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ov9734_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 0) * status->exp_step;
		//printf("vts:%d  exp_step:%f.\r\n", vts, status->exp_step);
	} else {
		//uint32_t tmp1;
		//uint32_t tmp2;
		//uint16_t max_exp_line = 2 * (2 * vts - status->max_short_exp - 5);
		//
		//tmp1 = 2 * (status->max_short_exp - 4);
		//tmp2 = (uint32_t)(max_exp_line / (ratio[0] + 1));
		//tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		//max_exposure[1] = tmp1 * status->exp_step;
		//min_exposure[1] = 5 * status->exp_step;
		//max_exposure[0] = max_exposure[1] * ratio[0];
		//min_exposure[0] = min_exposure[1] * ratio[0];
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct ov9734_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	if(gain >= 0xf8)
		gain = 0xf8;
		
	status->num = gain;
	return  gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 16.0f;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}
static int ov9734_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ov9734_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int ov9734_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int ov9734_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ov9734_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;
		
	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	
	i = 0;
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x3501, (exposure_rows & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3502, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x350b, status->num);
	set_sync_i2c(&reg[i++], 0x380E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x380F, vts & 0xff);
	regs->num = i;
	return RTS_ISP_OK;
}

static int ov9734_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
#if 0
	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0x3820, 0x18);
			break;
		case 2: // Mirror
			set_sync_i2c(&reg[i++], 0x3820, 0x10);
			break;
		case 1: // VFlip
			set_sync_i2c(&reg[i++], 0x3820, 0x1C);
			break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x3820, 0x04);
			break;
	#else
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0x3820, 0x04);
			break;
		case 2: // Mirror
			set_sync_i2c(&reg[i++], 0x3820, 0x1C);
			break;
		case 1: // VFlip
			set_sync_i2c(&reg[i++], 0x3820, 0x10);
			break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x3820, 0x18);
			break;
	#endif
	}
#endif
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ov9734_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x300a;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
	
	reg.addr = 0x300b;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0x9734)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops ov9734_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov9734",

	.get_info = ov9734_get_info,
	.get_init_info = ov9734_get_init_info,
	.start = ov9734_start,
	//.get_exposure_range = ov9734_get_exposure_range,
	.get_tuned_again = ov9734_get_tuned_again,
	.get_tuned_dgain = ov9734_get_tuned_dgain,
	.get_exposure_gain_info = ov9734_get_exposure_gain_info,
	.set_mirror_flip = ov9734_set_mirror_flip,
	.check = ov9734_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ov9734_ops;
}