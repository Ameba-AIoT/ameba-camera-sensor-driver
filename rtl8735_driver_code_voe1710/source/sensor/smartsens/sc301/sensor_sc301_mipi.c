/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 * Copyright (C) 2022 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

#if _SC301_SENSOR_

/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define AE_MAX_SHORT_EXP_BASE 56							/* 0x38 */

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define ORIENTATION 0	//0=default, 1=rotate180
#define SENSOR_HDR 1

#define ANALOG_GAIN_MAX_RATIO 50.208f

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct sc301_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t min_vts;
	uint16_t max_short_exp;
	uint16_t last_max_short_exp;
};

struct sc301_gain_config {
	uint8_t Again_RegValue;
	float gainValue;
};

#if (SENSOR_HDR == 0)
static struct sc301_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct sc301_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

/* Linear frame rate table*/
static const struct fps_info g_sc301_fps_info_asic_linear[] = {
	{30.0, 1125, 1600, 108000000},
};

/* HDR frame rate table*/
static const struct fps_info g_sc301_fps_info_asic_hdr[] = {
	{20.0, 1125, 3200, 144000000},
	//{30.0, 1125, 3200, 216000000},
};

static struct rts_isp_i2c_reg g_sc301_i2c_init_regs_asic_linear[] = {
	/* ---------Linear-------- */

	/*
	Resolution: 2050x1538
	Frame rate: 30fps
	MCLK: 27MHz
	MIPI CLK:540Mbps (2 Lane)
	MIPI: 2Lane
	Bit depth: 10bit
	Form Smartsens David
	*/

	{0x0103, 0x01},
	{0x0100, 0x00},
	{0x36e9, 0x80},
	{0x37f9, 0x80},
	{0x301c, 0x78},
	{0x301f, 0x40},
	{0x30b8, 0x44},
	{0x3208, 0x08},		//0x0802: 2050
	{0x3209, 0x02},
	{0x320a, 0x06},		//0x0602: 1538
	{0x320b, 0x02},
	{0x320c, 0x04},		//0x0465: 1125
	{0x320d, 0x65},
	{0x320e, 0x06},		//0x0640: 1600
	{0x320f, 0x40},
	{0x3211, 0x02},
	{0x3213, 0x03},
	{0x3214, 0x11},
	{0x3215, 0x11},
	{0x3223, 0xc0},
	{0x3253, 0x0c},
	{0x3274, 0x09},
	{0x3301, 0x08},
	{0x3306, 0x58},
	{0x3308, 0x08},
	{0x330a, 0x00},
	{0x330b, 0xe0},
	{0x330e, 0x10},
	{0x3314, 0x14},
	{0x331e, 0x55},
	{0x331f, 0x7d},
	{0x3333, 0x10},
	{0x3334, 0x40},
	{0x335e, 0x06},
	{0x335f, 0x08},
	{0x3364, 0x5e},
	{0x337c, 0x02},
	{0x337d, 0x0a},
	{0x3390, 0x01},
	{0x3391, 0x03},
	{0x3392, 0x07},
	{0x3393, 0x08},
	{0x3394, 0x08},
	{0x3395, 0x08},
	{0x3396, 0x08},
	{0x3397, 0x09},
	{0x3398, 0x1f},
	{0x3399, 0x08},
	{0x339a, 0x0a},
	{0x339b, 0x40},
	{0x339c, 0x88},
	{0x33a2, 0x04},
	{0x33ad, 0x0c},
	{0x33b1, 0x80},
	{0x33b3, 0x30},
	{0x33f9, 0x68},
	{0x33fb, 0x80},
	{0x33fc, 0x48},
	{0x33fd, 0x5f},
	{0x349f, 0x03},
	{0x34a6, 0x48},
	{0x34a7, 0x5f},
	{0x34a8, 0x30},
	{0x34a9, 0x30},
	{0x34aa, 0x00},
	{0x34ab, 0xf0},
	{0x34ac, 0x01},
	{0x34ad, 0x08},
	{0x34f8, 0x5f},
	{0x34f9, 0x10},
	{0x3630, 0xf0},
	{0x3631, 0x85},
	{0x3632, 0x74},
	{0x3633, 0x22},
	{0x3637, 0x4d},
	{0x3638, 0xcb},
	{0x363a, 0x8b},
	{0x363b, 0x02},
	{0x363c, 0x08},
	{0x3640, 0x00},
	{0x3641, 0x00},
	{0x3670, 0x4e},
	{0x3674, 0xc0},
	{0x3675, 0xb0},
	{0x3676, 0xa0},
	{0x3677, 0x83},
	{0x3678, 0x87},
	{0x3679, 0x8a},
	{0x367c, 0x49},
	{0x367d, 0x4f},
	{0x367e, 0x48},
	{0x367f, 0x4b},
	{0x3690, 0x33},
	{0x3691, 0x33},
	{0x3692, 0x44},
	{0x3699, 0x8a},
	{0x369a, 0xa1},
	{0x369b, 0xc2},
	{0x369c, 0x48},
	{0x369d, 0x4f},
	{0x36a2, 0x4b},
	{0x36a3, 0x4f},
	{0x36e9, 0x24},
	{0x370f, 0x01},
	{0x3714, 0x80},
	{0x3722, 0x09},
	{0x3724, 0x41},
	{0x3725, 0xc1},
	{0x3728, 0x00},
	{0x3771, 0x09},
	{0x3772, 0x05},
	{0x3773, 0x05},
	{0x377a, 0x48},
	{0x377b, 0x49},
	{0x37f9, 0x24},
	{0x3905, 0x8d},
	{0x391d, 0x08},
	{0x3922, 0x1a},
	{0x3926, 0x21},
	{0x3933, 0x80},
	{0x3934, 0x0d},
	{0x3937, 0x6a},
	{0x3939, 0x00},
	{0x393a, 0x0e},
	{0x39dc, 0x02},
	{0x3e00, 0x00},
	{0x3e01, 0x63},
	{0x3e02, 0x80},
	{0x3e03, 0x0b},
	{0x3e1b, 0x2a},
	{0x4407, 0x34},
	{0x440e, 0x02},
	{0x5001, 0x40},
	{0x5007, 0x80},
	{0x36e9, 0x24},
	{0x37f9, 0x24},
	{0x0100, 0x01},
};

static struct rts_isp_i2c_reg g_sc301_i2c_init_regs_asic_hdr_vc[] = {
	/* ---------VHDR-------- */

	/*
	Resolution: 2048x1536
	Frame rate: 20fps
	MCLK: 27MHz
	MIPI CLK:720Mbps (2 Lane)
	MIPI: 2Lane
	Bit depth: 10bit
	Form Smartsens David
	*/

	{0x0103, 0x01},
	{0x0100, 0x00},
	{0x36e9, 0x80},
	{0x37f9, 0x80},
	{0x301c, 0x78},
	{0x301f, 0x2e},
	{0x30b8, 0x44},
	{0x3200, 0x00},
	{0x3201, 0x00},
	{0x3202, 0x00},
	{0x3203, 0x00},
	{0x3204, 0x08},
	{0x3205, 0x07},
	{0x3206, 0x06},
	{0x3207, 0x07},
	{0x3208, 0x08},		//0x0800: 2048
	{0x3209, 0x00},
	{0x320a, 0x06},		//0X0600: 1536
	{0x320b, 0x00},
	{0x320c, 0x04},		//0x0465: 1125
	{0x320d, 0x65},
	{0x320e, 0x0c},		//0x0c80: 3200
	{0x320f, 0x80},
	{0x3210, 0x00},
	{0x3211, 0x04},
	{0x3212, 0x00},
	{0x3213, 0x03},
	{0x3214, 0x11},
	{0x3215, 0x11},
	{0x3223, 0xd0},
	{0x3231, 0x01},
	{0x3250, 0xff},
	{0x3253, 0x0c},
	{0x3274, 0x09},
	{0x3281, 0x01},
	{0x3301, 0x08},
	{0x3304, 0x80},
	{0x3306, 0x58},
	{0x3308, 0x08},
	{0x3309, 0xa0},
	{0x330a, 0x00},
	{0x330b, 0xe0},
	{0x330e, 0x10},
	{0x3314, 0x14},
	{0x331e, 0x71},
	{0x331f, 0x91},
	{0x3333, 0x10},
	{0x3334, 0x40},
	{0x335e, 0x06},
	{0x335f, 0x08},
	{0x3364, 0x5e},
	{0x337c, 0x02},
	{0x337d, 0x0a},
	{0x3390, 0x01},
	{0x3391, 0x03},
	{0x3392, 0x07},
	{0x3393, 0x08},
	{0x3394, 0x08},
	{0x3395, 0x08},
	{0x3396, 0x08},
	{0x3397, 0x09},
	{0x3398, 0x1f},
	{0x3399, 0x08},
	{0x339a, 0x14},
	{0x339b, 0x28},
	{0x339c, 0x78},
	{0x33a2, 0x04},
	{0x33ad, 0x0c},
	{0x33b1, 0x80},
	{0x33b3, 0x38},
	{0x33f9, 0x58},
	{0x33fb, 0x80},
	{0x33fc, 0x48},
	{0x33fd, 0x4f},
	{0x349f, 0x03},
	{0x34a6, 0x48},
	{0x34a7, 0x4f},
	{0x34a8, 0x38},
	{0x34a9, 0x28},
	{0x34aa, 0x00},
	{0x34ab, 0xe0},
	{0x34ac, 0x01},
	{0x34ad, 0x08},
	{0x34f8, 0x5f},
	{0x34f9, 0x18},
	{0x3630, 0xf0},
	{0x3631, 0x85},
	{0x3632, 0x74},
	{0x3633, 0x22},
	{0x3637, 0x4d},
	{0x3638, 0xcb},
	{0x363a, 0x8b},
	{0x363c, 0x08},
	{0x3641, 0x38},
	{0x3670, 0x4e},
	{0x3674, 0xc0},
	{0x3675, 0xa0},
	{0x3676, 0x90},
	{0x3677, 0x83},
	{0x3678, 0x86},
	{0x3679, 0x89},
	{0x367c, 0x48},
	{0x367d, 0x4f},
	{0x367e, 0x48},
	{0x367f, 0x4b},
	{0x3690, 0x33},
	{0x3691, 0x44},
	{0x3692, 0x55},
	{0x3699, 0x8a},
	{0x369a, 0xa1},
	{0x369b, 0xc2},
	{0x369c, 0x48},
	{0x369d, 0x4f},
	{0x36a2, 0x4b},
	{0x36a3, 0x4f},
	{0x36ea, 0x0a},
	{0x36eb, 0x0c},
	{0x36ec, 0x0c},
	{0x36ed, 0x15},
	{0x370f, 0x01},
	{0x3714, 0x80},
	{0x3722, 0x01},
	{0x3724, 0x41},
	{0x3725, 0xc1},
	{0x3728, 0x00},
	{0x3771, 0x09},
	{0x3772, 0x09},
	{0x3773, 0x05},
	{0x377a, 0x48},
	{0x377b, 0x4f},
	{0x37fa, 0x08},
	{0x37fb, 0x31},
	{0x37fc, 0x10},
	{0x37fd, 0x18},
	{0x3905, 0x8d},
	{0x391d, 0x08},
	{0x3922, 0x1a},
	{0x3926, 0x21},
	{0x3933, 0x80},
	{0x3934, 0x0d},
	{0x3937, 0x6a},
	{0x3939, 0x00},
	{0x393a, 0x0e},
	{0x39dc, 0x02},
	{0x3e00, 0x00},
	{0x3e01, 0x30},
	{0x3e02, 0x00},
	{0x3e03, 0x0b},
	{0x3e04, 0x03},
	{0x3e05, 0x00},
	{0x3e1b, 0x2a},
	{0x3e23, 0x00},
	{0x3e24, 0x38},
	{0x4407, 0x34},
	{0x440e, 0x02},
	{0x4509, 0x10},
	{0x4800, 0x44},
	{0x4816, 0x71},
	{0x5001, 0x40},
	{0x5007, 0x80},
	{0x36e9, 0x44},
	{0x37f9, 0x44},
	{0x0100, 0x01},
};

static struct rts_isp_i2c_reg g_sc301_i2c_init_regs_asic_hdr_vc1[] = {
	/* ---------VHDR-------- */

	/*
	Resolution: 2048x1536
	Frame rate: 30fps
	MCLK: 27MHz
	MIPI CLK:1080Mbps (2 Lane)
	MIPI: 2Lane
	Bit depth: 10bit
	Form Smartsens David
	*/
	{0x0103,0x01},
	{0x0100,0x00},
	{0x36e9,0x80},
	{0x37f9,0x80},
	{0x3714,0x80},
	{0x3728,0x00},
	{0x301c,0x78},
	{0x3208,0x08},
	{0x3209,0x00},
	{0x320a,0x06},
	{0x320b,0x00},
	{0x320e,0x06},
	{0x320f,0x40},
	{0x3210,0x00},
	{0x3211,0x04},
	{0x3212,0x00},
	{0x3213,0x03},
	{0x3214,0x11},
	{0x3215,0x11},
	{0x3274,0x09},
	{0x320c,0x04},
	{0x320d,0x65},
	{0x3223,0xc0},
	{0x3e1b,0x2a},
	{0x3e03,0x0b},
	{0x3e00,0x00},
	{0x3e01,0x64},
	{0x3e02,0x00},
	{0x5007,0x80},
	{0x5001,0x40},
	{0x3304,0x80},
	{0x3309,0xa0},
	{0x331e,0x71},
	{0x331f,0x91},
	{0x337c,0x02},
	{0x337d,0x0a},
	{0x33a2,0x04},
	{0x335e,0x06},
	{0x335f,0x08},
	{0x3641,0xa8},
	{0x36ea,0x0a},
	{0x36eb,0x0c},
	{0x36ec,0x0c},
	{0x36ed,0x15},
	{0x37fa,0x08},
	{0x37fb,0x31},
	{0x37fc,0x10},
	{0x37fd,0x18},
	{0x3722,0x01},
	{0x4509,0x10},
	{0x3306,0x78},
	{0x330b,0x00},
	{0x330a,0x01},
	{0x349f,0x00},
	{0x3253,0x0c},
	{0x3637,0x4c},
	{0x3333,0x10},
	{0x3334,0x40},
	{0x3632,0x74},
	{0x33b1,0x80},
	{0x3301,0x08},
	{0x33b3,0x38},
	{0x3633,0x22},
	{0x3306,0x58},
	{0x3630,0xf0}, 
	{0x330b,0xe0},
	{0x330a,0x00},
	{0x3631,0x85},
	{0x363a,0x8b},          
	{0x3638,0xcb},
	{0x30b8,0x44},
	{0x3637,0x4d},
	{0x3905,0x8d},
	{0x3933,0x80},
	{0x3934,0x02},
	{0x3937,0x72},
	{0x3939,0x00},
	{0x393a,0x03},
	{0x39dc,0x02},
	{0x3905,0x8d},
	{0x3933,0x80},
	{0x3934,0x0d},
	{0x3937,0x6a},
	{0x3939,0x00},
	{0x393a,0x0e},
	{0x39dc,0x02},
	{0x3926,0x21},
	{0x391d,0x08},
	{0x330e,0x10},
	{0x3308,0x08},
	{0x33ad,0x0c},
	{0x3364,0x5e},
	{0x3390,0x01},
	{0x3391,0x03},
	{0x3392,0x07},
	{0x3301,0x08},
	{0x3393,0x08},
	{0x3394,0x08},
	{0x3395,0x08},
	{0x3396,0x08},
	{0x3397,0x09},
	{0x3398,0x1f},
	{0x3399,0x08},
	{0x339a,0x14},
	{0x339b,0x28},
	{0x339c,0x78},
	{0x349f,0x03},
	{0x34a6,0x48},
	{0x34a7,0x4f},
	{0x34f8,0x5f},
	{0x33b3,0x38},
	{0x34a8,0x38},
	{0x34a9,0x28},
	{0x34f9,0x18},
	{0x3670,0x4e},
	{0x369c,0x48},
	{0x369d,0x4f},
	{0x3690,0x33},
	{0x3691,0x44},
	{0x3692,0x55},
	{0x3364,0x5e},
	{0x33fc,0x48},
	{0x33fd,0x4f},
	{0x3306,0x58},
	{0x33f9,0x58},
	{0x33fb,0x80},
	{0x349f,0x03},
	{0x34a6,0x48},
	{0x34a7,0x4f},
	{0x330a,0x00},
	{0x330b,0xe0},
	{0x34aa,0x00},
	{0x34ab,0xe0},
	{0x34ac,0x01},
	{0x34ad,0x08},
	{0x3670,0x4e},
	{0x367c,0x48},
	{0x367d,0x4f},
	{0x3674,0xc0},
	{0x3675,0xa0},
	{0x3676,0x90},
	{0x3670,0x4e},
	{0x367e,0x48},
	{0x367f,0x4b},
	{0x3677,0x83},
	{0x3678,0x86},
	{0x3679,0x89},
	{0x370f,0x01},
	{0x377a,0x48},
	{0x377b,0x4f},
	{0x3771,0x09},
	{0x3772,0x09},
	{0x3773,0x05},
	{0x3670,0x4e},
	{0x36a2,0x4b},
	{0x36a3,0x4f},
	{0x3699,0x8a},
	{0x369a,0xa1},
	{0x369b,0xc2},
	{0x301f,0x02},
	{0x3641,0xf8},
	{0x4407,0x34},
	{0x440e,0x02},
	{0x3641,0x38},
	{0x3314,0x14},
	{0x363c,0x08},
	{0x3e01,0x63},
	{0x3e02,0x80},
	{0x3922,0x1a},
	{0x3724,0x41},
	{0x3725,0xc1},
	{0x301f,0x07},
	{0x3281,0x01},
	{0x4816,0x71},
	{0x3250,0xff},
	{0x320e,0x0c},
	{0x320f,0x80},
	{0x3e00,0x00},
	{0x3e01,0xb9},
	{0x3e02,0xc0},
	{0x3e04,0x0b},
	{0x3e05,0xa0},
	{0x3e23,0x00},
	{0x3e24,0xbf},
	{0x301f,0x12},
	{0x36ea,0x09},
	{0x36eb,0x0d},
	{0x36ec,0x0c},
	{0x36ed,0x25},
	{0x37fa,0x09},
	{0x37fb,0x31},
	{0x37fc,0x10},
	{0x37fd,0x18},
	{0x3223,0xd0},
	{0x3231,0x01},
	{0x3677,0x85},
	{0x363b,0x02},
	{0x301f,0x34},
	{0x4800,0x44},
	{0x3e00,0x00},
	{0x3e01,0xc0},
	{0x3e02,0x00},
	{0x3e04,0x03},
	{0x3e05,0x00},
	{0x3e23,0x00},
	{0x3e24,0x39},
	{0x36ea,0x08},
	{0x36eb,0x0d},
	{0x36ec,0x0c},
	{0x36ed,0x25},
	{0x37fa,0x08},
	{0x37fb,0x31},
	{0x37fc,0x10},
	{0x37fd,0x18},
	{0x36e9,0x24},
	{0x37f9,0x24},
	{0x0100,0x01},
};

static struct sc301_gain_config gain_mapping[] = {
	{0x00, 1.000},
	{0x40, 1.569},
	{0x48, 3.138},
	{0x49, 6.276},
	{0x4b, 12.552},
	{0x4f, 25.104},
	{0x5f, 50.208},
};

static int sc301_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if (SENSOR_HDR == 0)
	printf("2023.08.31:Linear Mode\r\n");
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2048;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_sc301_fps_info_asic_linear[0].fps;			//@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;								//RTS_ISP_HDR_NONE;
	info->modes.mode[i].size.w = 2048;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_sc301_fps_info_asic_hdr[0].fps; 		//@MLCK=27MHz
	i++;
#else
	printf("2023.08.31:HDR Mode\r\n");
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2048;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_sc301_fps_info_asic_hdr[0].fps;			//@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = LINEAR_MODE;								//RTS_ISP_HDR_NONE;
	info->modes.mode[i].size.w = 2048;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_sc301_fps_info_asic_linear[0].fps; 		//@MLCK=27MHz
	i++;
#endif
	info->modes.num = i;

	info->i2c.i2c_id = 0x30;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 2000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 3000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 6000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *sc301_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;
	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_sc301_fps_info_asic_hdr); i++)
			if (fps == g_sc301_fps_info_asic_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc301_fps_info_asic_hdr))
			return NULL;

		return &g_sc301_fps_info_asic_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc301_fps_info_asic_linear); i++)
			if (fps == g_sc301_fps_info_asic_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc301_fps_info_asic_linear))
			return NULL;

		return &g_sc301_fps_info_asic_linear[i];
	}
}

static int sc301_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc301_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;
printf("sc301_get_init_info hdr: %x fps: %d\n\r", mode->hdr, mode->fps);
	fps_info = sc301_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;
	printf("fps_info: %x\n\r", fps_info);

	if (mode->hdr == HDR_MODE) {
		printf("sc301_get_init_info HDR\n\r");
		set_init_i2c_regs(info->sensor_regs[0],
				g_sc301_i2c_init_regs_asic_hdr_vc, 0);
				
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		// Fusion DDR latency
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 2048;
		info->size.h = 1536;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts * 2;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / 2 / info->pclk; /* us */
		info->exposure_step = 1e6 * info->hts / info->pclk;
	} else {
		printf("sc301_get_init_info linear\n\r");

		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc301_i2c_init_regs_asic_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2050;
		info->size.h = 1538;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts * 2;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	}

	return RTS_ISP_OK;
}
static int sc301_start(uint32_t isp_id)
{
	struct sc301_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	status->max_short_exp = AE_MAX_SHORT_EXP_BASE;
	status->last_max_short_exp = AE_MAX_SHORT_EXP_BASE;

	return RTS_ISP_OK;
}

static int sc301_get_exposure_range(uint32_t isp_id, uint32_t vts,
				     float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				     float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				     float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc301_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = 2 * status->exp_step;
		max_exposure[0] = (vts - 8) * status->exp_step;
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_exp_line = vts - status->max_short_exp - 11;

		tmp1 = status->max_short_exp - 9;
		tmp2 = (uint32_t)(max_exp_line / (ratio[0] + 1));
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = 2 * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;
	int i;

	if (fgain >= (float)ANALOG_GAIN_MAX_RATIO) {
		reg_value = 0x5f;
	} else {
		for (i = 0; i < ((ARRAY_SIZE(gain_mapping)) - 1); i++) {
			if ((gain_mapping[i].gainValue <= fgain) &&
			    (fgain < gain_mapping[i + 1].gainValue)) {
				reg_value = gain_mapping[i].Again_RegValue;
				break;
			}
		}
	}
	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain = 0.0;
	int i;

	if (reg_value >= 0x5f) {
		gain = (float)ANALOG_GAIN_MAX_RATIO;
	} else {
		for (i = 0; i < ARRAY_SIZE(gain_mapping); i++) {
			if (reg_value == gain_mapping[i].Again_RegValue) {
				gain = gain_mapping[i].gainValue;
				break;
			}
		}
	}
	return gain;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int sc301_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc301_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);
	if (status->hdr == HDR_MODE) {
		gain_reg = get_sensor_gain_reg(again[1]);
		again[1] = get_sensor_real_gain(gain_reg);
	}

	return RTS_ISP_OK;
}

static int sc301_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc301_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int sc301_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	struct sc301_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

#if 1
	if (status->hdr == LINEAR_MODE) {
		uint16_t total_line;
		uint16_t gain_reg;
		uint32_t exp_reg_value;

		gain_reg = get_sensor_gain_reg((float)exp_gain->analog_gain[0] * exp_gain->digital_gain[0]);
		total_line = exp_gain->vts;
		exp_reg_value =
			clip_d_word((float)(exp_gain->exposure[0] / status->exp_step + 0.5f), 2, total_line - 8);
		exp_reg_value = exp_reg_value << 4;

		total_line = (total_line + 1) / 2 * 2;
		reg = regs->reg;

		i = 0;
		/* set vts */
		set_sync_i2c(&reg[i++], 0x320e, (total_line >> 8));
		set_sync_i2c(&reg[i++], 0x320f, (total_line & 0xff));

		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3e00, exp_reg_value >> 16);
			set_sync_i2c(&reg[i++], 0x3e01, (exp_reg_value & 0xff00) >> 8);
			set_sync_i2c(&reg[i++], 0x3e02, exp_reg_value & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}

		/* set gain */
		set_sync_i2c(&reg[i++], 0x3e09, (gain_reg & 0xff));
	} else {
		uint16_t exp_cnt[2];
		uint16_t gain_reg[2];

		for (i = 0; i < 2; i++) {
			exp_cnt[i] = (exp_gain->exposure[i] /
					       status->exp_step + 0.5f);
			gain_reg[i] =
				get_sensor_gain_reg(exp_gain->analog_gain[i] *
						    exp_gain->digital_gain[i]);
		}

		reg = regs->reg;

		i = 0;
		/* set vts */
		//set_sync_i2c(&reg[i++], 0x320e, (2 * exp_gain->vts) >> 8);
		set_sync_i2c(&reg[i++], 0x320e, (exp_gain->vts) >> 8);
		//set_sync_i2c(&reg[i++], 0x320f, (2 * exp_gain->vts) & 0xff);
		set_sync_i2c(&reg[i++], 0x320f, (exp_gain->vts) & 0xff);

		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3e00, (exp_cnt[0] >> 12));
			set_sync_i2c(&reg[i++], 0x3e01, (exp_cnt[0] >> 4) & 0xff);
			set_sync_i2c(&reg[i++], 0x3e02, (exp_cnt[0] << 4) & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];
		}

		/* set gain */
		set_sync_i2c(&reg[i++], 0x3e09, (gain_reg[0] & 0xff));

		/* set exposure */
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3e22, (exp_cnt[1] >> 12));
			set_sync_i2c(&reg[i++], 0x3e04, (exp_cnt[1] >> 4) & 0xff);
			set_sync_i2c(&reg[i++], 0x3e05, (exp_cnt[1] << 4) & 0xff);
			status->last_exposure[1] = exp_gain->exposure[1];
		}

		/* set gain */
		set_sync_i2c(&reg[i++], 0x3e13, (gain_reg[1] & 0xff));
	}
	regs->num = i;
#endif
	return RTS_ISP_OK;
}


static int sc301_set_mirror_flip(uint32_t isp_id,
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
	switch(bySnrImgDir)
	{
		case 0:	// Normal
		default:
            set_sync_i2c(&reg[i++], 0x3221, 0x66);
			break;
		case 2: // Mirror
           	set_sync_i2c(&reg[i++], 0x3221, 0x06);
			break;
		case 1:	// VFlip
            set_sync_i2c(&reg[i++], 0x3221, 0x60);
			break;
		case 3:	// Rotate
            set_sync_i2c(&reg[i++], 0x3221, 0x00);
			break;
	}
	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int sc301_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

	//rts_isp_sensor_access_prepare();
	reg.addr = 0x3107;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	/*
	if (ret) {
		rts_isp_sensor_access_unprepare();
		return ret;
	}
	*/
	id = reg.data << 8;

	reg.addr = 0x3108;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	//rts_isp_sensor_access_unprepare();
	if (ret)
		return ret;

	id |= reg.data;

	if (id == 0xcc40)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops sc301_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc301",
	.get_info = sc301_get_info,
	.get_init_info = sc301_get_init_info,
	.start = sc301_start,
	.get_exposure_range = sc301_get_exposure_range,
	.get_tuned_again = sc301_get_tuned_again,
	.get_tuned_dgain = sc301_get_tuned_dgain,
	.get_exposure_gain_info = sc301_get_exposure_gain_info,
	.set_mirror_flip = sc301_set_mirror_flip,
	.check = sc301_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc301_ops;
}

#endif


