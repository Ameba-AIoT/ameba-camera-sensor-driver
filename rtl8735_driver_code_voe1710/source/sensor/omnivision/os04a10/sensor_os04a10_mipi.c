/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2023 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ORIENTATION 1												/* Default sensor mirror and flip mode => 0:default, 1:rotate180 */
#define ANALOG_GAIN_MAX_RATIO (float)15.5f							/* Max sensor gain ratio = 15.5x */
#define MIPI_4_LANE	1

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct os04a10_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure;
	uint16_t last_vts;
	//struct rts_isp_i2c_reg regs1[3];
};

struct os04a10_Again_config {
	uint8_t coeff_1;
	uint8_t coeff_2;
	float gain_ratio;
	uint16_t gain_reg;
};

static struct os04a10_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_os04a10_fps_info[] = {
/*   FPS    HTS     VTS   PCLK    */
	{30.0, 	(1464*2),  1624, 144000000},
};

static struct rts_isp_i2c_reg g_os04a10_i2c_init_regs[] = {
	/* ---------Linear-------- */
	/*
	Resolution: 2560x1440
	Frame rate: 30fps
	MCLK: 24MHz
	MIPI CLK: 720Mbps
	PCK = 144MHz
	MIPI: 2Lane
	Bit depth: 10bit
	*/

	{0x0103, 0x01},
	{0x0109, 0x01},
	{0x0104, 0x02},
	{0x0102, 0x00},
	{0x0305, 0x3c},
	{0x0306, 0x00},
	{0x0307, 0x00},
	{0x0308, 0x04},
	{0x030a, 0x01},
	{0x0317, 0x09},
	{0x0322, 0x01},
	{0x0323, 0x02},
	{0x0324, 0x00},
	{0x0325, 0x90},
	{0x0327, 0x05},
	{0x0329, 0x02},
	{0x032c, 0x02},
	{0x032d, 0x02},
	{0x032e, 0x02},
	{0x300f, 0x11},
	{0x3026, 0x10},
	{0x3027, 0x08},
	{0x302d, 0x24},
	{0x3104, 0x01},
	{0x3106, 0x11},
	{0x3400, 0x00},
	{0x3408, 0x05},
	{0x340c, 0x0c},
	{0x340d, 0xb0},
	{0x3425, 0x51},
	{0x3426, 0x10},
	{0x3427, 0x14},
	{0x3428, 0x10},
	{0x3429, 0x10},
	{0x342a, 0x10},
	{0x342b, 0x04},
	{0x3501, 0x02},
	{0x3504, 0x08},
	{0x3508, 0x01},
	{0x3509, 0x00},
	{0x350a, 0x01},
	{0x3544, 0x08},
	{0x3548, 0x01},
	{0x3549, 0x00},
	{0x3584, 0x08},
	{0x3588, 0x01},
	{0x3589, 0x00},
	{0x3601, 0x70},
	{0x3604, 0xe3},
	{0x3605, 0x7f},
	{0x3606, 0x80},
	{0x3608, 0xa8},
	{0x360a, 0xd0},
	{0x360b, 0x08},
	{0x360e, 0xc8},
	{0x360f, 0x66},
	{0x3610, 0x89},
	{0x3611, 0x8a},
	{0x3612, 0x4e},
	{0x3613, 0xbd},
	{0x3614, 0x9b},
	{0x362a, 0x0e},
	{0x362b, 0x0e},
	{0x362c, 0x0e},
	{0x362d, 0x0e},
	{0x362e, 0x1a},
	{0x362f, 0x34},
	{0x3630, 0x67},
	{0x3631, 0x7f},
	{0x3638, 0x00},
	{0x3643, 0x00},
	{0x3644, 0x00},
	{0x3645, 0x00},
	{0x3646, 0x00},
	{0x3647, 0x00},
	{0x3648, 0x00},
	{0x3649, 0x00},
	{0x364a, 0x04},
	{0x364c, 0x0e},
	{0x364d, 0x0e},
	{0x364e, 0x0e},
	{0x364f, 0x0e},
	{0x3650, 0xff},
	{0x3651, 0xff},
	{0x365a, 0x00},
	{0x365b, 0x00},
	{0x365c, 0x00},
	{0x365d, 0x00},
	{0x3661, 0x07},
	{0x3662, 0x02},
	{0x3663, 0x20},
	{0x3665, 0x12},
	{0x3667, 0xd4},
	{0x3668, 0x80},
	{0x366c, 0x00},
	{0x366d, 0x00},
	{0x366e, 0x00},
	{0x366f, 0x00},
	{0x3671, 0x08},
	{0x3673, 0x2a},
	{0x3681, 0x80},
	{0x3700, 0x2d},
	{0x3701, 0x22},
	{0x3702, 0x25},
	{0x3703, 0x20},
	{0x3705, 0x00},
	{0x3706, 0x72},
	{0x3707, 0x0a},
	{0x3708, 0x36},
	{0x3709, 0x57},
	{0x370a, 0x01},
	{0x370b, 0x14},
	{0x3714, 0x01},
	{0x3719, 0x1f},
	{0x371b, 0x16},
	{0x371c, 0x00},
	{0x371d, 0x08},
	{0x373f, 0x63},
	{0x3740, 0x63},
	{0x3741, 0x63},
	{0x3742, 0x63},
	{0x3743, 0x01},
	{0x3756, 0x9d},
	{0x3757, 0x9d},
	{0x3762, 0x1c},
	{0x376c, 0x04},
	{0x3776, 0x05},
	{0x3777, 0x22},
	{0x3779, 0x60},
	{0x377c, 0x48},
	{0x3784, 0x06},
	{0x3785, 0x0a},
	{0x3790, 0x10},
	{0x3793, 0x04},
	{0x3794, 0x07},
	{0x3796, 0x00},
	{0x3797, 0x02},
	{0x379c, 0x4d},
	{0x37a1, 0x80},
	{0x37bb, 0x88},
	{0x37be, 0x48},
	{0x37bf, 0x01},
	{0x37c0, 0x01},
	{0x37c4, 0x72},
	{0x37c5, 0x72},
	{0x37c6, 0x72},
	{0x37ca, 0x21},
	{0x37cc, 0x13},
	{0x37cd, 0x90},
	{0x37cf, 0x02},
	{0x37d0, 0x00},
	{0x37d1, 0x72},
	{0x37d2, 0x01},
	{0x37d3, 0x14},
	{0x37d4, 0x00},
	{0x37d5, 0x6c},
	{0x37d6, 0x00},
	{0x37d7, 0xf7},
	{0x37d8, 0x01},
	{0x37dc, 0x00},
	{0x37dd, 0x00},
	{0x37da, 0x00},
	{0x37db, 0x00},
	{0x3800, 0x00},
	{0x3801, 0x00},
	{0x3802, 0x00},
	{0x3803, 0x00},
	{0x3804, 0x0a},
	{0x3805, 0x8f},
	{0x3806, 0x05},
	{0x3807, 0xff},
	{0x3808, 0x0a},
	{0x3809, 0x80},
	{0x380a, 0x05},
	{0x380b, 0xf0},
	{0x380c, 0x02},
	{0x380d, 0xdc},
	{0x380e, 0x06},
	{0x380f, 0x58},
	{0x3811, 0x08},
	{0x3813, 0x08},
	{0x3814, 0x01},
	{0x3815, 0x01},
	{0x3816, 0x01},
	{0x3817, 0x01},
	{0x381c, 0x00},
#if (ORIENTATION == 0)
	{0x3820, 0x02},
#else
	{0x3820, 0x04},
#endif
	{0x3821, 0x00},
	{0x3822, 0x14},
	{0x3823, 0x18},
	{0x3826, 0x00},
	{0x3827, 0x00},
	{0x3833, 0x40},
	{0x384c, 0x02},
	{0x384d, 0xdc},
	{0x3858, 0x3c},
	{0x3865, 0x02},
	{0x3866, 0x00},
	{0x3867, 0x00},
	{0x3868, 0x02},
	{0x3900, 0x13},
	{0x3940, 0x13},
	{0x3980, 0x13},
	{0x3c01, 0x11},
	{0x3c05, 0x00},
	{0x3c0f, 0x1c},
	{0x3c12, 0x0d},
	{0x3c19, 0x00},
	{0x3c21, 0x00},
	{0x3c3a, 0x10},
	{0x3c3b, 0x18},
	{0x3c3d, 0xc6},
	{0x3c55, 0xcb},
	{0x3c5a, 0x55},
	{0x3c5d, 0xcf},
	{0x3c5e, 0xcf},
	{0x3d8c, 0x70},
	{0x3d8d, 0x10},
	{0x4000, 0xf9},
	{0x4001, 0x2f},
	{0x4004, 0x00},
	{0x4005, 0x40},
	{0x4008, 0x02},
	{0x4009, 0x11},
	{0x400a, 0x06},
	{0x400b, 0x40},
	{0x400e, 0x40},
	{0x402e, 0x00},
	{0x402f, 0x40},
	{0x4030, 0x00},
	{0x4031, 0x40},
	{0x4032, 0x0f},
	{0x4033, 0x80},
	{0x4050, 0x00},
	{0x4051, 0x07},
	{0x4011, 0xbb},
	{0x410f, 0x01},
	{0x4288, 0xcf},
	{0x4289, 0x00},
	{0x428a, 0x46},
	{0x430b, 0x0f},
	{0x430c, 0xfc},
	{0x430d, 0x00},
	{0x430e, 0x00},
	{0x4314, 0x04},
	{0x4500, 0x18},
	{0x4501, 0x18},
	{0x4503, 0x10},
	{0x4504, 0x00},
	{0x4506, 0x32},
	{0x4507, 0x02},
	{0x4601, 0x30},
	{0x4603, 0x00},
	{0x460a, 0x50},
	{0x460c, 0x60},
	{0x4640, 0x62},
	{0x4646, 0xaa},
	{0x4647, 0x55},
	{0x4648, 0x99},
	{0x4649, 0x66},
	{0x464d, 0x00},
	{0x4654, 0x11},
	{0x4655, 0x22},
	{0x4800, 0x44},
	{0x480e, 0x00},
	{0x4810, 0xff},
	{0x4811, 0xff},
	{0x4813, 0x00},
	{0x481f, 0x30},
	{0x4837, 0x0e},
	{0x484b, 0x27},
	{0x4d00, 0x4d},
	{0x4d01, 0x9d},
	{0x4d02, 0xb9},
	{0x4d03, 0x2e},
	{0x4d04, 0x4a},
	{0x4d05, 0x3d},
	{0x4d09, 0x4f},
	{0x5000, 0x1f},
	{0x5001, 0x0d},
	{0x5080, 0x00},
	{0x50c0, 0x00},
	{0x5100, 0x00},
	{0x5200, 0x00},
	{0x5201, 0x00},
	{0x5202, 0x03},
	{0x5203, 0xff},
	{0x5393, 0x30},
	{0x5395, 0x18},
	{0x5397, 0x00},
	{0x539a, 0x01},
	{0x539b, 0x01},
	{0x539c, 0x01},
	{0x539d, 0x01},
	{0x539e, 0x01},
	{0x539f, 0x01},
	{0x5413, 0x18},
	{0x5415, 0x0c},
	{0x5417, 0x00},
	{0x541a, 0x01},
	{0x541b, 0x01},
	{0x541c, 0x01},
	{0x541d, 0x01},
	{0x541e, 0x01},
	{0x541f, 0x01},
	{0x5493, 0x06},
	{0x5495, 0x03},
	{0x5497, 0x00},
	{0x549a, 0x01},
	{0x549b, 0x01},
	{0x549c, 0x01},
	{0x549d, 0x01},
	{0x549e, 0x01},
	{0x549f, 0x01},
	{0x5393, 0x30},
	{0x5395, 0x18},
	{0x5397, 0x00},
	{0x539a, 0x01},
	{0x539b, 0x01},
	{0x539c, 0x01},
	{0x539d, 0x01},
	{0x539e, 0x01},
	{0x539f, 0x01},
	{0x5413, 0x18},
	{0x5415, 0x0c},
	{0x5417, 0x00},
	{0x541a, 0x01},
	{0x541b, 0x01},
	{0x541c, 0x01},
	{0x541d, 0x01},
	{0x541e, 0x01},
	{0x541f, 0x01},
	{0x5493, 0x06},
	{0x5495, 0x03},
	{0x5497, 0x00},
	{0x549a, 0x01},
	{0x549b, 0x01},
	{0x549c, 0x01},
	{0x549d, 0x01},
	{0x549e, 0x01},
	{0x549f, 0x01},
	{0x5780, 0x53},
	{0x5782, 0x18},
	{0x5783, 0x3c},
	{0x5786, 0x01},
	{0x5788, 0x18},
	{0x5789, 0x3c},
	{0x5792, 0x11},
	{0x5793, 0x33},
	{0x5857, 0xff},
	{0x5858, 0xff},
	{0x5859, 0xff},
	{0x58d7, 0xff},
	{0x58d8, 0xff},
	{0x58d9, 0xff},
	{0x0100, 0x01},
	{0x0100, 0x01},
	{0x3808, 0x0a},
	{0x3809, 0x00},
	{0x380a, 0x05},
	//{0x380b, 0xa0},
	{0x380b, 0xa2},		//Output height change to 1442 (For RAW order)
	{0x3810, 0x00},
	{0x3811, 0x48},
	{0x3812, 0x00},
	{0x3813, 0x30},
	{0x380c, 0x05},
	{0x380d, 0xb8},
#if (MIPI_4_LANE)
	{0x3012, 0x41},
#else
	{0x3012, 0x21},
#endif
	{0x0100, 0x00},
	{0x5080, 0x80},	//Color bar
	{0x0100, 0x01},
};

static struct os04a10_Again_config os04a10_Again_config[] = {
/*   Sensor gain coefficient										*/
/*   (DEC) (DEC) 													*/
/*	 coeff 1, coeff 2,  gain value, reg value(Max = 15.5x)			*/
	{	16,		16,		1.99,		0x1ff},
	{	32,		8,   	3.99,		0x3ff},
	{	64,		4,   	7.99,		0x7ff},
	{	128,	2,  	15.50,		0xf80},
};

static int os04a10_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_os04a10_fps_info[0].fps;
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = 0x36;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_HCLK, CLK_12M, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 2000);
	up->num = i;

	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 200);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *os04a10_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_os04a10_fps_info); i++)
		if (fps == g_os04a10_fps_info[i].fps)
			break;
	if (i == ARRAY_SIZE(g_os04a10_fps_info))
		return NULL;

	return &g_os04a10_fps_info[i];
}

static int os04a10_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct os04a10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = os04a10_get_fps_info(mode->fps);

	if (!fps_info)
		return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0],
			g_os04a10_i2c_init_regs, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
#if (MIPI_4_LANE)
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
	info->interface.mipi.hs_term = 0x1;
#else
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x6;
#endif
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2560;
	info->size.h = 1442;
	info->start.x = 0;
	info->start.y = 1;

	info->hts = fps_info->hts;
	info->min_vts = fps_info->vts;
	info->pclk = fps_info->clk;
	info->max_vts = 65535 - info->min_vts;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */

	return RTS_ISP_OK;
}

static int os04a10_start(uint32_t isp_id)
{
	struct os04a10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static int os04a10_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct os04a10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = 2 * status->exp_step;
		max_exposure[0] = (vts - 8) * status->exp_step;
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;
	int i;

	if (fgain >= (float)ANALOG_GAIN_MAX_RATIO) {
		reg_value = (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * os04a10_Again_config[(ARRAY_SIZE(os04a10_Again_config) - 1)].coeff_2 * os04a10_Again_config[(ARRAY_SIZE(os04a10_Again_config) - 1)].coeff_1 );
	} else {
		for (i = 0; i < ARRAY_SIZE(os04a10_Again_config); i++) {
			if (fgain <= os04a10_Again_config[i].gain_ratio) {
				reg_value = (uint16_t)((float)fgain * os04a10_Again_config[i].coeff_2 * os04a10_Again_config[i].coeff_1 );
				break;
			}
		}
	}
	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float fgain = 0;
	int i;

	if (reg_value >= (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * os04a10_Again_config[(ARRAY_SIZE(os04a10_Again_config) - 1)].coeff_2 * os04a10_Again_config[(ARRAY_SIZE(os04a10_Again_config) - 1)].coeff_1 )) {
		fgain =  (float)ANALOG_GAIN_MAX_RATIO;
	} else {
		for (i = 0; i < ARRAY_SIZE(os04a10_Again_config); i++) {
			if (reg_value <= os04a10_Again_config[i].gain_reg) {
				fgain = (float)(((int)((float)reg_value / os04a10_Again_config[i].coeff_1)) / os04a10_Again_config[i].coeff_2);
				break;
			}
		}
	}
	return (float)fgain;
}

static int os04a10_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct os04a10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int os04a10_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int os04a10_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t frame_length;
	uint16_t exposure;
	uint16_t gain_reg;
	struct os04a10_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	frame_length = exp_gain->vts;
	//printf("frame_length = %d (DEC)\n", frame_length);
	exposure = (uint16_t)(exp_gain->exposure[0] / status->exp_step + 0.5f);
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);

	reg = regs->reg;
	i = 0;
	/* set vts */
	if (abs(status->last_vts - frame_length) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x380e, frame_length >> 8);
		set_sync_i2c(&reg[i++], 0x380f, frame_length & 0xff);

		status->last_vts = frame_length;
	}

	/* set exposure */
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x3501, exposure >> 8);
		set_sync_i2c(&reg[i++], 0x3502, exposure & 0xff);

		status->last_exposure = exp_gain->exposure[0];
	}

	/* gain */
	/* MSB REG 0x3508 bit[4:0] => Gain value bit[8:4]*/
	/* LSB REG 0x3509 bit[7:4] => Gain value bit[3:0]*/
	set_sync_i2c(&reg[i++], 0x3508, (gain_reg >> 8) & 0x0f);
	set_sync_i2c(&reg[i++], 0x3509, gain_reg & 0xf0);

	regs->num = i;

	return RTS_ISP_OK;
}

static int os04a10_set_mirror_flip(uint32_t isp_id,
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

	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: // Normal
		default:
			set_sync_i2c(&reg[i++], 0x3820, 0x02);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x3820, 0x00);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x3820, 0x06);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x3820, 0x04);
		break;
	#else
		case 0: // Normal
		default:
			set_sync_i2c(&reg[i++], 0x3820, 0x04);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x3820, 0x06);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x3820, 0x00);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x3820, 0x02);
		break;
	#endif
	}

	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int os04a10_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

	reg.addr = 0x300a;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;

	id = reg.data << 8;

	reg.addr = 0x300b;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;

	id |= reg.data;

	if (id == 0x5304)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops os04a10_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "os04a10",
	.get_info = os04a10_get_info,
	.get_init_info = os04a10_get_init_info,
	.start = os04a10_start,
	.get_exposure_range = os04a10_get_exposure_range,
	.get_tuned_again = os04a10_get_tuned_again,
	.get_tuned_dgain = os04a10_get_tuned_dgain,
	.get_exposure_gain_info = os04a10_get_exposure_gain_info,
	.set_mirror_flip = os04a10_set_mirror_flip,
	.check = os04a10_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &os04a10_ops;
}