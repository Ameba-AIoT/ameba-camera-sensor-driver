/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct gc4103_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
};

struct gc4103_gain_config {
	uint8_t reg_0914;
	uint8_t reg_0915;
	uint8_t reg_0225;
	uint8_t reg_0e67;
	uint8_t reg_0e68;
	uint8_t reg_0242;
	uint16_t gain_value;
};

static struct gc4103_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc4103_fps_info_asic[] = {
	//{30.0f, 2200, 74250000},
	{25.0f, 3200, 198400000},
	//{30.0f, 3840, 86400000},
};

static struct rts_isp_i2c_reg g_gc4103_i2c_init_regs_asic[] = {
	{0x03fe,0xf0},
	{0x03fe,0x00},
	{0x03fe,0x10},
	{0x0938,0x01},
	{0x0360,0xfd},
	{0x091b,0x1a},
	{0x091c,0x18},
	{0x091e,0x00},
	{0x091d,0x06},
	{0x091f,0x7c},//81
	{0x0920,0xa1},
	{0x0922,0x3a},
	{0x0923,0x10},
	{0x0928,0x00},
	{0x0934,0xb7},
	{0x0935,0x06},
	{0x0936,0x00},
	{0x0937,0x7c},//81
	{0x031b,0x00},
	{0x031c,0x4f},
	{0x031e,0x00},
	{0x03e0,0x00},
	{0x0314,0x10},
	{0x0219,0x47},
	{0x022b,0x10},
	{0x0259,0x08},
	{0x025a,0x44},
	{0x025b,0x10},
	{0x0340,0x09},//08
	{0x0341,0xb0},//66
	{0x0342,0x03},
	{0x0343,0xe8},
	{0x0346,0x00},
	{0x0347,0x40},
	{0x0348,0x08},
	{0x0349,0x20},
	{0x034a,0x08},
	{0x034b,0x20},
	{0x070c,0x9f},
	{0x070d,0x00},
	{0x070e,0x5c},
	{0x070f,0x09},
	{0x0053,0x05},
	{0x0099,0x0c},//10
	{0x009b,0x0c},//10
	{0x0094,0x08},
	{0x0095,0x08},//00
	{0x0096,0x08},
	{0x0097,0x08},//00
	{0x0e4c,0x3c},
	{0x0902,0x0b},
	{0x0903,0x15},
	{0x0904,0x14},
	{0x0907,0x14},
	{0x0908,0x15},
	{0x090e,0x26},
	{0x090f,0x15},
	{0x0244,0x76},
	{0x0724,0x0c},
	{0x0727,0x0c},
	{0x072a,0x18},
	{0x072b,0x19},
	{0x0709,0x40},
	{0x0719,0x40},
	{0x0912,0x01},
	{0x0913,0x00},
	{0x0e66,0x10},
	{0x0e69,0x80},
	{0x0e6a,0xc0},
	{0x0e6b,0x02},
	{0x0223,0x00},
	{0x0e81,0x02},
	{0x0e30,0x00},
	{0x0e33,0x80},
	{0x0242,0x65},
	{0x0361,0xbc},
	{0x0362,0x0f},
	{0x0e34,0x04},
	{0x0e47,0x55},
	{0x0e61,0x0d},
	{0x0e62,0x0d},
	{0x023a,0x05},
	{0x0e64,0x0c},
	{0x0e20,0x0c},
	{0x0e6e,0x50},
	{0x0e6f,0x58},
	{0x0e70,0x24},
	{0x0e71,0x28},
	{0x0e28,0x38},
	{0x0e4d,0x80},
	{0x0245,0x08},
	{0x0240,0x06},
	{0x0e63,0x06},
	{0x0236,0x02},
	{0x0261,0x60},
	{0x0262,0x28},
	{0x0072,0x00},
	{0x0074,0x01},
	{0x0087,0x53},
	{0x0704,0x07},
	{0x0705,0x28},
	{0x0706,0x02},
	{0x0715,0x28},
	{0x0716,0x02},
	{0x0708,0xc0},
	{0x0718,0xc0},
	{0x0076,0x01},
	{0x021a,0x10},
	{0x0052,0x02},
	{0x0448,0x06},
	{0x0449,0x04},
	{0x044a,0x04},
	{0x044b,0x06},
	{0x044c,0x78},
	{0x044d,0x7a},
	{0x044e,0x7a},
	{0x044f,0x78},
	{0x0046,0x30},
	{0x0002,0xa9},
	{0x0005,0x83},
	{0x0006,0x83},
	{0x001a,0x83},
	{0x0075,0x65},
	{0x0202,0x01},
	{0x0203,0xe0},
	{0x0914,0x01},
	{0x0915,0x00},
	{0x0225,0x00},
	{0x0e67,0x0f},
	{0x0e68,0x0f},
	{0x0089,0x03},
	{0x0144,0x00},
	{0x0122,0x08},
	{0x0123,0x27},
	{0x0126,0x0a},
	{0x0129,0x08},
	{0x012a,0x0d},
	{0x012b,0x0a},
	{0x0180,0x46},
	{0x0181,0x30},
	{0x0185,0x01},
	{0x0106,0x38},
	{0x010d,0x0a},
	{0x010e,0x0a},//00
	{0x0111,0x2b},
	{0x0112,0x0a},
	{0x0113,0x0a},
	{0x0114,0x01},
	{0x0100,0x09},
	{0x0221,0x05},
	{0x023b,0x13},
	{0x0352,0x70},
	{0x0357,0x00},
	{0x0b00,0x40},
	{0x08ef,0x01},
	{0x03fe,0x00},
	{0x031f,0x01},
	{0x031f,0x00},
	{0x0318,0x0e},
	{0x0a67,0x80},
	{0x0a50,0x41},
	{0x0a51,0x41},
	{0x0a52,0x41},
	{0x0a54,0x26},
	{0x0a55,0x26},
	{0x0a4e,0x0c},
	{0x0a4f,0x0c},
	{0x0a65,0x17},
	{0x0a53,0x00},
	{0x0a98,0x04},
	{0x05be,0x00},
	{0x05a9,0x01},
	{0x0a67,0x80},
	{0x0a88,0x20},
	{0x0a89,0x08},
	{0x0a8a,0x20},
	{0x0a8b,0x08},
	{0x0028,0x08},
	{0x0029,0x20},
	{0x002a,0x08},
	{0x002b,0x20},
	{0x0023,0x00},
	{0x0024,0x01},
	{0x0025,0x38},
	{0x0a70,0x07},
	{0x0a73,0xe0},
	{0x0a80,0x7b},
	{0x0a82,0x00},
	{0x0a83,0x80},
	{0x0a5a,0x80},
	//sleep 20
	{0x05be,0x01},
	{0x0a70,0x00},
	{0x0080,0x02},
	{0x0021,0x40},
	{0x0a67,0x00},
};

static struct gc4103_gain_config g_gc4103_gain_config[] = {
/*   Sensor REG addrss												*/
/*   (HEX) (HEX) (HEX) (HEX) (HEX) (HEX) (HEX)						*/
/*	 2B3,  2B4,  2B8,  2B9,  515,  519,  2D9,  gain value(1x = 64)	*/
	//0914, 0915, 0225, 0e67, 0e68, 0242    |  CG | ??­¿?|Again dB|
	{ 0x01, 0x00, 0x04, 0x11, 0x11, 0x65, 64},//| LCG |   1.000 |  0.000 |
	{ 0x01, 0x05, 0x04, 0x11, 0x11, 0x65, 75},//| LCG |   1.176 |  1.408 |
	{ 0x21, 0x09, 0x04, 0x12, 0x12, 0x65, 87},//| LCG |   1.362 |  2.682 |
	{ 0xb1, 0x0C, 0x04, 0x12, 0x12, 0x65, 104},//| LCG |   1.637 |  4.279 |
	{ 0x01, 0x00, 0x00, 0x11, 0x11, 0x65, 131},//| HCG |   2.048 |  6.227 |
	{ 0x01, 0x05, 0x00, 0x11, 0x11, 0x65, 158},//| HCG |   2.475 |  7.871 |
	{ 0x21, 0x09, 0x00, 0x12, 0x12, 0x65, 188},//| HCG |   2.944 |  9.379 |
	{ 0xb1, 0x0C, 0x00, 0x12, 0x12, 0x65, 223},//| HCG |   3.491 | 10.859 |
	{ 0x03, 0x00, 0x00, 0x12, 0x12, 0x65, 270},//| HCG |   4.230 | 12.526 |
	{ 0x03, 0x05, 0x00, 0x12, 0x12, 0x65, 318},//| HCG |   4.983 | 13.950 |
	{ 0x23, 0x09, 0x00, 0x14, 0x14, 0x65, 374},//| HCG |   5.847 | 15.338 |
	{ 0xb3, 0x0C, 0x00, 0x15, 0x15, 0x65, 444},//| HCG |   6.941 | 16.829 |
	{ 0x03, 0x10, 0x00, 0x16, 0x16, 0x65, 533},//| HCG |   8.329 | 18.412 |
	{ 0x05, 0x05, 0x00, 0x16, 0x16, 0x65, 636},//| HCG |   9.943 | 19.950 |
	{ 0x25, 0x09, 0x00, 0x17, 0x17, 0x65, 757},//| HCG |  11.834 | 21.462 |
	{ 0xb5, 0x0C, 0x00, 0x18, 0x18, 0x65, 892},//| HCG |  13.948 | 22.890 |
	{ 0x05, 0x10, 0x00, 0x1a, 0x1a, 0x65, 1065},//| HCG |  16.655 | 24.431 |
};



static int gc4103_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2000;
	info->modes.mode[0].size.h = 2000;
	info->modes.mode[0].fps = g_gc4103_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x31;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;


	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 1);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *gc4103_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_gc4103_fps_info_asic); i++)
		if (fps == g_gc4103_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_gc4103_fps_info_asic))
		return NULL;
	return &g_gc4103_fps_info_asic[i];
}

static int gc4103_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc4103_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("gc4103 get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc4103_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;
#ifdef _SENSOR_LOG_
	printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
#endif

	set_init_i2c_regs(info->sensor_regs[0], g_gc4103_i2c_init_regs_asic, 0);
	//set_init_i2c_regs(info->sensor_regs[1], status->regs1, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x3;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2048;
	info->size.h = 2048;
	info->start.x = 1;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 2480;
	info->max_vts = 65536;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	//info->exposure_step = status->exp_step;

	return RTS_ISP_OK;
}

static int gc4103_start(uint32_t isp_id)
{
	struct gc4103_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static int gc4103_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc4103_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = vts * status->exp_step;
		
		debug("expusre_min = %1.f , expusre_max = %1.f\n", min_exposure[0],max_exposure[0]);
	} 


	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc4103_status *status)
{
	int i;
	uint16_t gain = fgain * 64;

	if (gain >= 1024) {
		gain = 1024;
		status->num = 16;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc4103_gain_config) - 1; i++) {
			if (gain >= g_gc4103_gain_config[i].gain_value &&
			    gain < g_gc4103_gain_config[i + 1].gain_value) {
				gain = g_gc4103_gain_config[i].gain_value;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 64.0f;
}

static int gc4103_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc4103_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	


	return RTS_ISP_OK;
}

static int gc4103_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc4103_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	
	status = &g_status[isp_id];
	
	dgain[0] = 1.0f;
	

	return RTS_ISP_OK;
}

static int gc4103_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct gc4103_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;
	
	
	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	i = 0;
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x0202, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0203, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x0914,
				g_gc4103_gain_config[status->num].reg_0914);
	set_sync_i2c(&reg[i++], 0x0915,
				g_gc4103_gain_config[status->num].reg_0915);
	set_sync_i2c(&reg[i++], 0x0225,
				g_gc4103_gain_config[status->num].reg_0225);
	set_sync_i2c(&reg[i++], 0x0e67,
				g_gc4103_gain_config[status->num].reg_0e67);
	set_sync_i2c(&reg[i++], 0x0e68,
				g_gc4103_gain_config[status->num].reg_0e68);
	set_sync_i2c(&reg[i++], 0x0242,
				g_gc4103_gain_config[status->num].reg_0242);
	set_sync_i2c(&reg[i++], 0x0340, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0341, vts & 0xff);
	regs->num = i;

	return RTS_ISP_OK;
}

static int gc4103_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct gc4103_status *status;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)//
	{
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0x0a73, 0xe0);
			set_sync_i2c(&reg[i++], 0x022c, 0x00);
			set_sync_i2c(&reg[i++], 0x0063, 0x00);
			set_sync_i2c(&reg[i++], 0x0722, 0x00);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0x0a73, 0xe1);
			set_sync_i2c(&reg[i++], 0x022c, 0x01);
			set_sync_i2c(&reg[i++], 0x0063, 0x01);
			set_sync_i2c(&reg[i++], 0x0722, 0x02);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0x0a73, 0xe2);
			set_sync_i2c(&reg[i++], 0x022c, 0x02);
			set_sync_i2c(&reg[i++], 0x0063, 0x02);
			set_sync_i2c(&reg[i++], 0x0722, 0x00);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0x0a73, 0xe3);
			set_sync_i2c(&reg[i++], 0x022c, 0x03);
			set_sync_i2c(&reg[i++], 0x0063, 0x03);
			set_sync_i2c(&reg[i++], 0x0722, 0x02);
		break;
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int gc4103_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

	reg.addr = 0x03f0;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id = reg.data << 8;

	reg.addr = 0x03f1;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id |= reg.data;
	
	printf("sensor id=%x\r\n",id);
	
	if (id == 0x4103)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops gc4103_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc4103",
	.get_info = gc4103_get_info,
	.get_init_info = gc4103_get_init_info,
	.start = gc4103_start,
	.get_exposure_range = gc4103_get_exposure_range,
	.get_tuned_again = gc4103_get_tuned_again,
	.get_tuned_dgain = gc4103_get_tuned_dgain,
	.get_exposure_gain_info = gc4103_get_exposure_gain_info,
	.set_mirror_flip = gc4103_set_mirror_flip,
	.check = gc4103_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc4103_ops;
}

