/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 * Copyright (C) 2022 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#if _SC400AI_SENSOR_

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
#define SENSOR_HDR 0

#define ANALOG_GAIN_MAX_RATIO 23.320f

struct fps_info {
	float fps;
	uint32_t hts;//line length
	uint32_t vts;//frame length
	uint32_t clk;//pixel clk
};

struct sc400ai_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t min_vts;
	uint16_t max_short_exp;
	uint16_t last_max_short_exp;
};

struct sc400ai_gain_config {
	uint16_t ana_gain;
	uint16_t fine_gain;
	float gainValue;
//	uint8_t ana_gain;
//	float gainValue;
};

#if (SENSOR_HDR == 0)
static struct sc400ai_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct sc400ai_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

/* Linear frame rate table*/
static const struct fps_info g_sc400ai_fps_info_asic_linear[] = {
	{30.0, 2800, 1500, 126000000},//fps,hts:line length,vts:frame length,pixel clk
};

/* HDR frame rate table*/
static const struct fps_info g_sc400ai_fps_info_asic_hdr[] = {
#if 0
	{30.0, 2800, 3000, 252000000},
#else
	{ 5.0, 2800, 3000, 42000000},
#endif
	//{30.0, 1125, 3200, 216000000},
};

static struct rts_isp_i2c_reg g_sc400ai_i2c_init_regs_asic_linear[] = {
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
	{0x36f9, 0x80},
	{0x301c, 0x78},
	{0x301f, 0x82},
	{0x3200, 0x00},
	{0x3201, 0x00},		
	{0x3202, 0x00},
	{0x3203, 0x00},		
	{0x3204, 0x0a},
	{0x3205, 0x07},		
	{0x3206, 0x05},
	{0x3207, 0xa7},		
	{0x3208, 0x0a},
	{0x3209, 0x04},
	{0x320a, 0x05},
	{0x320b, 0xa4},
	{0x320e, 0x05},
	{0x320f, 0xdc},
	{0x3210, 0x00},
	{0x3211, 0x02},
	{0x3212, 0x00},
	{0x3213, 0x02},
	{0x3214, 0x11},
	{0x3215, 0x11},
	{0x3223, 0x80},
	{0x3250, 0x00},
	{0x3253, 0x08},
	{0x3274, 0x01},
	{0x3301, 0x20},
	{0x3302, 0x18},
	{0x3303, 0x10},
	{0x3304, 0x50},
	{0x3306, 0x38},
	{0x3308, 0x18},
	{0x3309, 0x60},
	{0x330b, 0xc0},
	{0x330d, 0x10},
	{0x330e, 0x18},
	{0x330f, 0x04},
	{0x3310, 0x02},
	{0x331c, 0x04},
	{0x331e, 0x41},
	{0x331f, 0x51},
	{0x3320, 0x09},
	{0x3333, 0x10},
	{0x334c, 0x08},
	{0x3356, 0x09},
	{0x3364, 0x17},
	{0x338e, 0xfd},
	{0x3390, 0x08},
	{0x3391, 0x18},
	{0x3392, 0x38},
	{0x3393, 0x20},
	{0x3394, 0x20},
	{0x3395, 0x20},
	{0x3396, 0x08},
	{0x3397, 0x18},
	{0x3398, 0x38},
	{0x3399, 0x20},
	{0x339a, 0x20},
	{0x339b, 0x20},
	{0x339c, 0x20},
	{0x33ac, 0x10},
	{0x33ae, 0x18},
	{0x33af, 0x19},
	{0x360f, 0x01},
	{0x3620, 0x08},
	{0x3637, 0x25},
	{0x363a, 0x12},
	{0x3670, 0x0a},
	{0x3671, 0x07},
	{0x3672, 0x57},
	{0x3673, 0x5e},
	{0x3674, 0x84},
	{0x3675, 0x88},
	{0x3676, 0x8a},
	{0x367a, 0x58},
	{0x367b, 0x78},
	{0x367c, 0x58},
	{0x367d, 0x78},
	{0x3690, 0x33},
	{0x3691, 0x43},
	{0x3692, 0x34},
	{0x369c, 0x40},
	{0x369d, 0x78},
	{0x36ea, 0x39},
	{0x36eb, 0x0d},
	{0x36ec, 0x2c},
	{0x36ed, 0x24},
	{0x36fa, 0x39},
	{0x36fb, 0x33},
	{0x36fc, 0x10},
	{0x36fd, 0x34},
	{0x3908, 0x41},
	{0x396c, 0x0e},
	{0x3e00, 0x00},
	{0x3e01, 0xb6},
	{0x3e02, 0x00},
	{0x3e03, 0x0b},
	{0x3e08, 0x03},
	{0x3e09, 0x40},
	{0x3e1b, 0x2a},
	{0x4509, 0x30},
	{0x5001, 0x44},
	{0x57a8, 0xd0},
	{0x36e9, 0x23},
	{0x36f9, 0x24},
	{0x0100, 0x01},
};

static struct rts_isp_i2c_reg g_sc400ai_i2c_init_regs_asic_hdr_vc[] = {
#if 0
	/* ---------VHDR-------- */

	/*
	Resolution: 2560x1440
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
	{0x36f9, 0x80},
	{0x301c, 0x78},
	{0x301f, 0x83},
	{0x3106, 0x01},
	{0x3200, 0x00},
	{0x3201, 0x00},
	{0x3202, 0x00},
	{0x3203, 0x00},
	{0x3204, 0x0a},
	{0x3205, 0x07},
	{0x3206, 0x05},
	{0x3207, 0xa7},
	{0x3208, 0x0a},		
	{0x3209, 0x04},
	{0x320a, 0x05},		
	{0x320b, 0xa4},
	{0x320e, 0x0b},		
	{0x320f, 0xb8},
	{0x3210, 0x00},		
	{0x3211, 0x02},
	{0x3212, 0x00},
	{0x3213, 0x02},
	{0x3214, 0x11},
	{0x3215, 0x11},
	{0x3220, 0x53},
	{0x3223, 0x80},
	{0x3250, 0xff},
	{0x3253, 0x08},
	{0x3274, 0x01},
	{0x3301, 0x08},
	{0x3302, 0x18},
	{0x3303, 0x10},
	{0x3304, 0x70},
	{0x3306, 0x40},
	{0x3308, 0x10},
	{0x3309, 0x70},
	{0x330b, 0xb0},
	{0x330d, 0x20},
	{0x330e, 0x20},
	{0x330f, 0x04},
	{0x3310, 0x02},
	{0x331c, 0x08},
	{0x331e, 0x61},
	{0x331f, 0x61},
	{0x3320, 0x0f},
	{0x3333, 0x10},
	{0x334c, 0x10},
	{0x3356, 0x0f},
	{0x3364, 0x17},
	{0x338e, 0xfd},
	{0x3390, 0x08},
	{0x3391, 0x18},
	{0x3392, 0x38},
	{0x3393, 0x08},
	{0x3394, 0x10},
	{0x3395, 0x20},
	{0x3396, 0x08},
	{0x3397, 0x18},
	{0x3398, 0x38},
	{0x3399, 0x08},
	{0x339a, 0x10},
	{0x339b, 0x20},
	{0x339c, 0x20},
	{0x33ac, 0x15},
	{0x33ae, 0x1f},
	{0x33af, 0x1f},
	{0x3415, 0x42},
	{0x360f, 0x01},
	{0x3620, 0x08},
	{0x3637, 0x4a},
	{0x363a, 0x12},
	{0x3670, 0x0a},
	{0x3671, 0x07},
	{0x3672, 0x07},
	{0x3673, 0x57},
	{0x3674, 0x74},
	{0x3675, 0x78},
	{0x3676, 0x7a},
	{0x367a, 0x48},
	{0x367b, 0x58},
	{0x367c, 0x58},
	{0x367d, 0x78},
	{0x3690, 0x45},
	{0x3691, 0x35},
	{0x3692, 0x36},
	{0x369c, 0x40},
	{0x369d, 0x48},
	{0x36ea, 0x39},
	{0x36eb, 0x0c},
	{0x36ec, 0x1c},
	{0x36ed, 0x24},
	{0x36fa, 0x39},
	{0x36fb, 0x04},
	{0x36fc, 0x00},
	{0x36fd, 0x24},
	{0x3908, 0x41},
	{0x391f, 0x10},
	{0x396c, 0x0e},
	{0x3e00, 0x01},
	{0x3e01, 0x5e},
	{0x3e02, 0x00},
	{0x3e03, 0x0b},
	{0x3e04, 0x15},
	{0x3e05, 0xe0},
	{0x3e06, 0x00},
	{0x3e07, 0x80},
	{0x3e08, 0x03},
	{0x3e09, 0x40},
	{0x3e10, 0x00},
	{0x3e11, 0x80},
	{0x3e12, 0x03},
	{0x3e13, 0x40},    
	{0x3e1b, 0x2a},
	{0x3e23, 0x00},
	{0x3e24, 0xb4},
	{0x440e, 0x02},
	{0x4509, 0x30},
	{0x4800, 0x44},
	{0x4816, 0x71},
	{0x4819, 0x08},
	{0x481b, 0x05},
	{0x481d, 0x11},
	{0x481f, 0x04},
	{0x4821, 0x09},
	{0x4823, 0x04},
	{0x4825, 0x04},
	{0x4827, 0x04},
	{0x4829, 0x07},
	{0x5001, 0x44},	
	{0x5011, 0x80},
	{0x57a8, 0xd0},
	{0x36e9, 0x23},
	{0x36f9, 0x53},
	{0x0100, 0x01},
#else
	{0x0103,0x01},
	{0x0100,0x00},
	{0x36e9,0x80},
	{0x36f9,0x80},
	{0x3018,0x3a},
	{0x3019,0x0c},
	{0x301c,0x78},
	{0x301f,0xef},
	{0x3208,0x0a},
	{0x3209,0x00},
	{0x320a,0x05},
	{0x320b,0xa0},
	{0x320c,0x05},
	{0x320d,0xa0},
	{0x320e,0x0b},
	{0x320f,0xb8},
	{0x3211,0x04},
	{0x3213,0x04},	//04->03
	{0x3214,0x11},
	{0x3215,0x11},
	{0x3220,0x53},
	{0x3223,0x80},
	{0x3250,0xff},
	{0x3253,0x08},
	{0x3274,0x01},
	{0x3301,0x20},
	{0x3302,0x18},
	{0x3303,0x10},
	{0x3304,0x50},
	{0x3306,0x38},
	{0x3308,0x18},
	{0x3309,0x60},
	{0x330b,0xc0},
	{0x330d,0x10},
	{0x330e,0x18},
	{0x330f,0x04},
	{0x3310,0x02},
	{0x331c,0x04},
	{0x331e,0x41},
	{0x331f,0x51},
	{0x3320,0x09},
	{0x3333,0x10},
	{0x334c,0x08},
	{0x3356,0x09},
	{0x3364,0x17},
	{0x338e,0xfd},
	{0x3390,0x08},
	{0x3391,0x18},
	{0x3392,0x38},
	{0x3393,0x20},
	{0x3394,0x20},
	{0x3395,0x20},
	{0x3396,0x08},
	{0x3397,0x18},
	{0x3398,0x38},
	{0x3399,0x20},
	{0x339a,0x20},
	{0x339b,0x20},
	{0x339c,0x20},
	{0x33ac,0x10},
	{0x33ae,0x18},
	{0x33af,0x19},
	{0x3415,0x42},
	{0x360f,0x01},
	{0x3620,0x08},
	{0x3637,0x25},
	{0x363a,0x12},
	{0x3670,0x0a},
	{0x3671,0x07},
	{0x3672,0x57},
	{0x3673,0x5e},
	{0x3674,0x84},
	{0x3675,0x88},
	{0x3676,0x8a},
	{0x367a,0x58},
	{0x367b,0x78},
	{0x367c,0x58},
	{0x367d,0x78},
	{0x3690,0x33},
	{0x3691,0x43},
	{0x3692,0x34},
	{0x369c,0x40},
	{0x369d,0x78},
	{0x36ea,0x37},
	{0x36eb,0x0d},
	{0x36ec,0x1c},
	{0x36ed,0x04},
	{0x36fa,0x37},
	{0x36fb,0x33},
	{0x36fc,0x10},
	{0x36fd,0x14},
	{0x3908,0x41},
	{0x396c,0x0e},
	{0x3e00,0x01},
	{0x3e01,0x5e},
	{0x3e02,0x00},
	{0x3e03,0x0b},
	{0x3e04,0x15},
	{0x3e05,0xe0},
	{0x3e06,0x00},
	{0x3e07,0x80},
	{0x3e08,0x03},
	{0x3e09,0x40},
	{0x3e10,0x00},
	{0x3e11,0x80},
	{0x3e12,0x03},
	{0x3e13,0x40},
	{0x3e1b,0x2a},
	{0x3e23,0x00},
	{0x3e24,0xb4},
	{0x440e,0x02},
	{0x4509,0x30},
	{0x4816,0x71},
	{0x4819,0x04},
	{0x481b,0x02},
	{0x481d,0x06},
	{0x481f,0x02},
	{0x4821,0x07},
	{0x4823,0x02},
	{0x4825,0x02},
	{0x4827,0x02},
	{0x4829,0x03},
	{0x5001,0x44},
	{0x5011,0x80},
	{0x57a8,0xd0},
	{0x36e9,0x04},
	{0x36f9,0x30},
	{0x0100,0x01},
#endif
};



static struct sc400ai_gain_config gain_mapping[] = {
	{0x0003, 0x0040, 1.000},
	{0x0003, 0x0041, 1.016},
	{0x0003, 0x0042, 1.031},
	{0x0003, 0x0043, 1.047},
	{0x0003, 0x0044, 1.063},
	{0x0003, 0x0045, 1.078},
	{0x0003, 0x0046, 1.094},
	{0x0003, 0x0047, 1.109},
	{0x0003, 0x0048, 1.125},
	{0x0003, 0x0049, 1.141},
	{0x0003, 0x004A, 1.156},
	{0x0003, 0x004B, 1.172},
	{0x0003, 0x004C, 1.188},
	{0x0003, 0x004D, 1.203},
	{0x0003, 0x004E, 1.219},
	{0x0003, 0x004F, 1.234},
	{0x0003, 0x0050, 1.250},
	{0x0003, 0x0051, 1.266},
	{0x0003, 0x0052, 1.281},
	{0x0003, 0x0053, 1.297},
	{0x0003, 0x0054, 1.313},
	{0x0003, 0x0055, 1.328},
	{0x0003, 0x0056, 1.344},
	{0x0003, 0x0057, 1.359},
	{0x0003, 0x0058, 1.375},
	{0x0003, 0x0059, 1.391},
	{0x0003, 0x005A, 1.406},
	{0x0003, 0x005B, 1.422},
	{0x0003, 0x005C, 1.438},
	{0x0003, 0x005D, 1.453},
	{0x0023, 0x0040, 1.469},
	{0x0023, 0x0041, 1.492},
	{0x0023, 0x0042, 1.515},
	{0x0023, 0x0043, 1.538},
	{0x0023, 0x0044, 1.561},
	{0x0023, 0x0045, 1.584},
	{0x0023, 0x0046, 1.607},
	{0x0023, 0x0047, 1.630},
	{0x0023, 0x0048, 1.653},
	{0x0023, 0x0049, 1.676},
	{0x0023, 0x004A, 1.699},
	{0x0023, 0x004B, 1.721},
	{0x0023, 0x004C, 1.744},
	{0x0023, 0x004D, 1.767},
	{0x0023, 0x004E, 1.790},
	{0x0023, 0x004F, 1.813},
	{0x0023, 0x0050, 1.836},
	{0x0023, 0x0051, 1.859},
	{0x0023, 0x0052, 1.882},
	{0x0023, 0x0053, 1.905},
	{0x0023, 0x0054, 1.928},
	{0x0023, 0x0055, 1.951},
	{0x0023, 0x0056, 1.974},
	{0x0023, 0x0057, 1.997},
	{0x0023, 0x0058, 2.020},
	{0x0023, 0x0059, 2.043},
	{0x0023, 0x005A, 2.066},
	{0x0023, 0x005B, 2.089},
	{0x0023, 0x005C, 2.112},
	{0x0023, 0x005D, 2.135},
	{0x0023, 0x005E, 2.158},
	{0x0023, 0x005F, 2.181},
	{0x0023, 0x0060, 2.204},
	{0x0023, 0x0061, 2.226},
	{0x0023, 0x0062, 2.249},
	{0x0023, 0x0063, 2.272},
	{0x0023, 0x0064, 2.295},
	{0x0023, 0x0065, 2.318},
	{0x0023, 0x0066, 2.341},
	{0x0023, 0x0067, 2.364},
	{0x0023, 0x0068, 2.387},
	{0x0023, 0x0069, 2.410},
	{0x0023, 0x006A, 2.433},
	{0x0023, 0x006B, 2.456},
	{0x0023, 0x006C, 2.479},
	{0x0023, 0x006D, 2.502},
	{0x0023, 0x006E, 2.525},
	{0x0023, 0x006F, 2.548},
	{0x0023, 0x0070, 2.571},
	{0x0023, 0x0071, 2.594},
	{0x0023, 0x0072, 2.617},
	{0x0023, 0x0073, 2.640},
	{0x0023, 0x0074, 2.663},
	{0x0023, 0x0075, 2.686},
	{0x0023, 0x0076, 2.708},
	{0x0023, 0x0077, 2.731},
	{0x0023, 0x0078, 2.754},
	{0x0023, 0x0079, 2.777},
	{0x0023, 0x007A, 2.800},
	{0x0023, 0x007B, 2.823},
	{0x0023, 0x007C, 2.846},
	{0x0023, 0x007D, 2.869},
	{0x0023, 0x007E, 2.892},
	{0x0023, 0x007F, 2.915},
	{0x0027, 0x0040, 2.938},
	{0x0027, 0x0041, 2.984},
	{0x0027, 0x0042, 3.030},
	{0x0027, 0x0043, 3.076},
	{0x0027, 0x0044, 3.122},
	{0x0027, 0x0045, 3.168},
	{0x0027, 0x0046, 3.213},
	{0x0027, 0x0047, 3.259},
	{0x0027, 0x0048, 3.305},
	{0x0027, 0x0049, 3.351},
	{0x0027, 0x004A, 3.397},
	{0x0027, 0x004B, 3.443},
	{0x0027, 0x004C, 3.489},
	{0x0027, 0x004D, 3.535},
	{0x0027, 0x004E, 3.581},
	{0x0027, 0x004F, 3.627},
	{0x0027, 0x0050, 3.673},
	{0x0027, 0x0051, 3.718},
	{0x0027, 0x0052, 3.764},
	{0x0027, 0x0053, 3.810},
	{0x0027, 0x0054, 3.856},
	{0x0027, 0x0055, 3.902},
	{0x0027, 0x0056, 3.948},
	{0x0027, 0x0057, 3.994},
	{0x0027, 0x0058, 4.040},
	{0x0027, 0x0059, 4.086},
	{0x0027, 0x005A, 4.132},
	{0x0027, 0x005B, 4.177},
	{0x0027, 0x005C, 4.223},
	{0x0027, 0x005D, 4.269},
	{0x0027, 0x005E, 4.315},
	{0x0027, 0x005F, 4.361},
	{0x0027, 0x0060, 4.407},
	{0x0027, 0x0061, 4.453},
	{0x0027, 0x0062, 4.499},
	{0x0027, 0x0063, 4.545},
	{0x0027, 0x0064, 4.591},
	{0x0027, 0x0065, 4.637},
	{0x0027, 0x0066, 4.682},
	{0x0027, 0x0067, 4.728},
	{0x0027, 0x0068, 4.774},
	{0x0027, 0x0069, 4.820},
	{0x0027, 0x006A, 4.866},
	{0x0027, 0x006B, 4.912},
	{0x0027, 0x006C, 4.958},
	{0x0027, 0x006D, 5.004},
	{0x0027, 0x006E, 5.050},
	{0x0027, 0x006F, 5.096},
	{0x0027, 0x0070, 5.142},
	{0x0027, 0x0071, 5.187},
	{0x0027, 0x0072, 5.233},
	{0x0027, 0x0073, 5.279},
	{0x0027, 0x0074, 5.325},
	{0x0027, 0x0075, 5.371},
	{0x0027, 0x0076, 5.417},
	{0x0027, 0x0077, 5.463},
	{0x0027, 0x0078, 5.509},
	{0x0027, 0x0079, 5.555},
	{0x0027, 0x007A, 5.601},
	{0x0027, 0x007B, 5.646},
	{0x0027, 0x007C, 5.692},
	{0x0027, 0x007D, 5.738},
	{0x0027, 0x007E, 5.784},
	{0x0027, 0x007F, 5.830},
	{0x002F, 0x0040, 5.876},
	{0x002F, 0x0041, 5.968},
	{0x002F, 0x0042, 6.060},
	{0x002F, 0x0043, 6.151},
	{0x002F, 0x0044, 6.243},
	{0x002F, 0x0045, 6.335},
	{0x002F, 0x0046, 6.427},
	{0x002F, 0x0047, 6.519},
	{0x002F, 0x0048, 6.611},
	{0x002F, 0x0049, 6.702},
	{0x002F, 0x004A, 6.794},
	{0x002F, 0x004B, 6.886},
	{0x002F, 0x004C, 6.978},
	{0x002F, 0x004D, 7.070},
	{0x002F, 0x004E, 7.161},
	{0x002F, 0x004F, 7.253},
	{0x002F, 0x0050, 7.345},
	{0x002F, 0x0051, 7.437},
	{0x002F, 0x0052, 7.529},
	{0x002F, 0x0053, 7.620},
	{0x002F, 0x0054, 7.712},
	{0x002F, 0x0055, 7.804},
	{0x002F, 0x0056, 7.896},
	{0x002F, 0x0057, 7.988},
	{0x002F, 0x0058, 8.080},
	{0x002F, 0x0059, 8.171},
	{0x002F, 0x005A, 8.263},
	{0x002F, 0x005B, 8.355},
	{0x002F, 0x005C, 8.447},
	{0x002F, 0x005D, 8.539},
	{0x002F, 0x005E, 8.630},
	{0x002F, 0x005F, 8.722},
	{0x002F, 0x0060, 8.814},
	{0x002F, 0x0061, 8.906},
	{0x002F, 0x0062, 8.998},
	{0x002F, 0x0063, 9.089},
	{0x002F, 0x0064, 9.181},
	{0x002F, 0x0065, 9.273},
	{0x002F, 0x0066, 9.365},
	{0x002F, 0x0067, 9.457},
	{0x002F, 0x0068, 9.549},
	{0x002F, 0x0069, 9.640},
	{0x002F, 0x006A, 9.732},
	{0x002F, 0x006B, 9.824},
	{0x002F, 0x006C, 9.916},
	{0x002F, 0x006D, 10.008},
	{0x002F, 0x006E, 10.099},
	{0x002F, 0x006F, 10.191},
	{0x002F, 0x0070, 10.283},
	{0x002F, 0x0071, 10.375},
	{0x002F, 0x0072, 10.467},
	{0x002F, 0x0073, 10.558},
	{0x002F, 0x0074, 10.650},
	{0x002F, 0x0075, 10.742},
	{0x002F, 0x0076, 10.834},
	{0x002F, 0x0077, 10.926},
	{0x002F, 0x0078, 11.018},
	{0x002F, 0x0079, 11.109},
	{0x002F, 0x007A, 11.201},
	{0x002F, 0x007B, 11.293},
	{0x002F, 0x007C, 11.385},
	{0x002F, 0x007D, 11.477},
	{0x002F, 0x007E, 11.568},
	{0x002F, 0x007F, 11.660},
	{0x003F, 0x0040, 11.752},
	{0x003F, 0x0041, 11.936},
	{0x003F, 0x0042, 12.119},
	{0x003F, 0x0043, 12.303},
	{0x003F, 0x0044, 12.487},
	{0x003F, 0x0045, 12.670},
	{0x003F, 0x0046, 12.854},
	{0x003F, 0x0047, 13.037},
	{0x003F, 0x0048, 13.221},
	{0x003F, 0x0049, 13.405},
	{0x003F, 0x004A, 13.588},
	{0x003F, 0x004B, 13.772},
	{0x003F, 0x004C, 13.956},
	{0x003F, 0x004D, 14.139},
	{0x003F, 0x004E, 14.323},
	{0x003F, 0x004F, 14.506},
	{0x003F, 0x0050, 14.690},
	{0x003F, 0x0051, 14.874},
	{0x003F, 0x0052, 15.057},
	{0x003F, 0x0053, 15.241},
	{0x003F, 0x0054, 15.425},
	{0x003F, 0x0055, 15.608},
	{0x003F, 0x0056, 15.792},
	{0x003F, 0x0057, 15.975},
	{0x003F, 0x0058, 16.159},
	{0x003F, 0x0059, 16.343},
	{0x003F, 0x005A, 16.526},
	{0x003F, 0x005B, 16.710},
	{0x003F, 0x005C, 16.894},
	{0x003F, 0x005D, 17.077},
	{0x003F, 0x005E, 17.261},
	{0x003F, 0x005F, 17.444},
	{0x003F, 0x0060, 17.628},
	{0x003F, 0x0061, 17.812},
	{0x003F, 0x0062, 17.995},
	{0x003F, 0x0063, 18.179},
	{0x003F, 0x0064, 18.363},
	{0x003F, 0x0065, 18.546},
	{0x003F, 0x0066, 18.730},
	{0x003F, 0x0067, 18.913},
	{0x003F, 0x0068, 19.097},
	{0x003F, 0x0069, 19.281},
	{0x003F, 0x006A, 19.464},
	{0x003F, 0x006B, 19.648},
	{0x003F, 0x006C, 19.832},
	{0x003F, 0x006D, 20.015},
	{0x003F, 0x006E, 20.199},
	{0x003F, 0x006F, 20.382},
	{0x003F, 0x0070, 20.566},
	{0x003F, 0x0071, 20.750},
	{0x003F, 0x0072, 20.933},
	{0x003F, 0x0073, 21.117},
	{0x003F, 0x0074, 21.301},
	{0x003F, 0x0075, 21.484},
	{0x003F, 0x0076, 21.668},
	{0x003F, 0x0077, 21.851},
	{0x003F, 0x0078, 22.035},
	{0x003F, 0x0079, 22.219},
	{0x003F, 0x007A, 22.402},
	{0x003F, 0x007B, 22.586},
	{0x003F, 0x007C, 22.770},
	{0x003F, 0x007D, 22.953},
	{0x003F, 0x007E, 23.137},
	{0x003F, 0x007F, 23.320},
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x30	//0x60(default)
#define SLAVE_ADDR_1 0x32	//0x64

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int sc400ai_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if (SENSOR_HDR == 0)
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_sc400ai_fps_info_asic_linear[0].fps;			//@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;								//RTS_ISP_HDR_NONE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_sc400ai_fps_info_asic_hdr[0].fps; 		//@MLCK=27MHz
	i++;
#else
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_sc400ai_fps_info_asic_hdr[0].fps;			//@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = LINEAR_MODE;								//RTS_ISP_HDR_NONE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_sc400ai_fps_info_asic_linear[0].fps; 		//@MLCK=27MHz
	i++;
#endif
	info->modes.num = i;

	info->i2c.i2c_id = real_slave_addr;
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
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 6000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *sc400ai_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;
	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_sc400ai_fps_info_asic_hdr); i++)
			if (fps == g_sc400ai_fps_info_asic_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc400ai_fps_info_asic_hdr))
			return NULL;

		return &g_sc400ai_fps_info_asic_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc400ai_fps_info_asic_linear); i++)
			if (fps == g_sc400ai_fps_info_asic_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc400ai_fps_info_asic_linear))
			return NULL;

		return &g_sc400ai_fps_info_asic_linear[i];
	}
}

static int sc400ai_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc400ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = sc400ai_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		set_init_i2c_regs(info->sensor_regs[0],
				g_sc400ai_i2c_init_regs_asic_hdr_vc, 0);
				
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;//ori 0x5
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		// Fusion DDR latency
		info->interface.vhdr_start_line_tnr = 2;
		info->mipi_behavor = VC_HDR;

		info->size.w = 2564;
		info->size.h = 1444;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / 2 / info->pclk; /* us */
		info->exposure_step = 1e6 * info->hts / info->pclk;
	} else {

		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc400ai_i2c_init_regs_asic_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x4;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2564;
		info->size.h = 1444;
		info->start.x = 0;
		info->start.y = 1;

		info->hts = fps_info->hts;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = info->min_vts * 30;
		status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	}

	return RTS_ISP_OK;
}
static int sc400ai_start(uint32_t isp_id)
{
	struct sc400ai_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	status->max_short_exp = AE_MAX_SHORT_EXP_BASE;
	status->last_max_short_exp = AE_MAX_SHORT_EXP_BASE;

	return RTS_ISP_OK;
}

static int sc400ai_get_exposure_range(uint32_t isp_id, uint32_t vts,
				     float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				     float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				     float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc400ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = 3 * status->exp_step;
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

	if (fgain >= ANALOG_GAIN_MAX_RATIO) {
		reg_value = 0x3f7f;
	} else {
		for (i = 0; i < ((ARRAY_SIZE(gain_mapping)) - 1); i++) {
			if ((gain_mapping[i].gainValue <= fgain) &&
			    (fgain < gain_mapping[i + 1].gainValue)) {
				reg_value = gain_mapping[i].ana_gain << 8 |
					    gain_mapping[i].fine_gain;
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

	if (reg_value >= 0x3f7f) {
		gain = ANALOG_GAIN_MAX_RATIO;
	} else {
		for (i = 0; i < ARRAY_SIZE(gain_mapping); i++) {
			if (reg_value == ((gain_mapping[i].ana_gain << 8) |
					  gain_mapping[i].fine_gain)) {
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

static int sc400ai_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc400ai_status *status;

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

static int sc400ai_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc400ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int sc400ai_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	struct sc400ai_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		uint16_t total_line;
		uint16_t gain_reg;
		uint32_t exp_reg_value;

		gain_reg = get_sensor_gain_reg((float)exp_gain->analog_gain[0] * exp_gain->digital_gain[0]);
		total_line = exp_gain->vts;
		exp_reg_value =
			clip_d_word((float)(exp_gain->exposure[0] / status->exp_step + 0.5f), 3, total_line - 8);
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
		set_sync_i2c(&reg[i++], 0x3e08, (gain_reg >> 8));
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
		set_sync_i2c(&reg[i++], 0x3e08, (gain_reg[0]>> 8));
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

	return RTS_ISP_OK;
}


static int sc400ai_set_mirror_flip(uint32_t isp_id,
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

static int sc400ai_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();
	reg.addr = 0x3107;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
		rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x3108;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	rts_isp_sensor_access_unprepare();
	if (ret)
		return ret;

	id |= reg.data;

	if (id == 0xcd2e)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int sc400ai_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops sc400ai_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc400ai",
	.get_info = sc400ai_get_info,
	.get_init_info = sc400ai_get_init_info,
	.start = sc400ai_start,
	.get_exposure_range = sc400ai_get_exposure_range,
	.get_tuned_again = sc400ai_get_tuned_again,
	.get_tuned_dgain = sc400ai_get_tuned_dgain,
	.get_exposure_gain_info = sc400ai_get_exposure_gain_info,
	.set_mirror_flip = sc400ai_set_mirror_flip,
	.check = sc400ai_check,
	.get_slave_addr_num = sc400ai_get_slave_addr_num,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc400ai_ops;
}

//#endif


