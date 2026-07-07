/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 * Copyright (C) 2022 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#if _SC450AI_SENSOR_

#define DEBUG 
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define ORIENTATION 0	//0=default, 1=rotate180

#define ANALOG_GAIN_MAX_RATIO 50.208f

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct sc450ai_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t min_vts;
	uint16_t max_short_exp;
	uint16_t last_max_short_exp;
};

struct sc450ai_gain {
	uint16_t ana_gain;
	uint16_t fine_gain;
	float total_gain;
};


static struct sc450ai_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_sc450ai_fps_info_asic_linear[] = {
	{30, 3076, 1560, 144000000},
};



static struct rts_isp_i2c_reg g_sc450ai_i2c_init_regs_asic_linear[] = {


		{0x0103,0x01},
		{0x0100,0x00},
		{0x36e9,0x80},
		{0x36f9,0x80},
		{0x3018,0x3a},
		{0x3019,0x0c},
		{0x301c,0x78},
		{0x301f,0x15},
		{0x302d,0xa0},
		{0x302e,0x00},
		{0x3200,0x00},
		{0x3201,0x00},
		{0x3202,0x00},
		{0x3203,0x00},
		{0x3204,0x0a},
		{0x3205,0x8f},
		{0x3206,0x05},
		{0x3207,0xff},
		{0x3208,0x0a},
		{0x3209,0x00},  //Active x = 2560
		{0x320a,0x05},
		{0x320b,0xa0},	//Active y = 1440
		{0x320c,0x02},
		{0x320d,0xee},
		{0x320e,0x06},
		{0x320f,0x18},
		{0x3210,0x00},
		{0x3211,0x48},	//start x = 8+64
		{0x3212,0x00},
		{0x3213,0x31},  //start y = 8+40+1
		{0x3214,0x11},
		{0x3215,0x11},
		{0x3220,0x00},
		{0x3223,0xc0},
		{0x3253,0x10},
		{0x325f,0x44},
		{0x3274,0x09},
		{0x3280,0x01},
		{0x3301,0x07},
		{0x3306,0x20},
		{0x3308,0x08},
		{0x330b,0x58},
		{0x330e,0x18},
		{0x3315,0x00},
		{0x335d,0x60},
		{0x3364,0x56},
		{0x338f,0x80},
		{0x3390,0x08},
		{0x3391,0x18},
		{0x3392,0x38},
		{0x3393,0x07},
		{0x3394,0x10},
		{0x3395,0x18},
		{0x3396,0x08},
		{0x3397,0x18},
		{0x3398,0x38},
		{0x3399,0x10},
		{0x339a,0x13},
		{0x339b,0x15},
		{0x339c,0x18},
		{0x33af,0x18},
		{0x3400,0x16},
		{0x360f,0x13},
		{0x3621,0xec},
		{0x3622,0x00},
		{0x3625,0x0b},
		{0x3627,0x20},
		{0x3630,0x90},
		{0x3633,0x56},
		{0x3637,0x1d},
		{0x3638,0x12},
		{0x363c,0x0f},
		{0x363d,0x0f},
		{0x363e,0x08},
		{0x3670,0x4a},
		{0x3671,0xe0},
		{0x3672,0xe0},
		{0x3673,0xe0},
		{0x3674,0xc0},
		{0x3675,0x87},
		{0x3676,0x8c},
		{0x367a,0x48},
		{0x367b,0x58},
		{0x367c,0x48},
		{0x367d,0x58},
		{0x3690,0x22},
		{0x3691,0x33},
		{0x3692,0x44},
		{0x3699,0x03},
		{0x369a,0x0f},
		{0x369b,0x1f},
		{0x369c,0x40},
		{0x369d,0x78},
		{0x36a2,0x48},
		{0x36a3,0x78},
		{0x36b0,0x53},
		{0x36b1,0x74},
		{0x36b2,0x34},
		{0x36b3,0x40},
		{0x36b4,0x78},
		{0x36b7,0xa0},
		{0x36b8,0xa0},
		{0x36b9,0x20},
		{0x36bd,0x40},
		{0x36be,0x48},
		{0x36d0,0x20},
		{0x36e0,0x08},
		{0x36e1,0x08},
		{0x36e2,0x12},
		{0x36e3,0x48},
		{0x36e4,0x78},
		{0x36ea,0x0f},
		{0x36eb,0x05},
		{0x36ec,0x43},
		{0x36ed,0x14},
		{0x36fa,0xcd},
		{0x36fb,0xb4},
		{0x36fc,0x00},
		{0x36fd,0x04},
		{0x3907,0x00},
		{0x3908,0x40},		//BLC=10b 64
		{0x391e,0xf1},
		{0x391f,0x11},
		{0x3921,0x10},
		{0x3933,0x82},
		{0x3934,0x30},
		{0x3935,0x02},
		{0x3936,0xc7},
		{0x3937,0x76},
		{0x3938,0x76},
		{0x3939,0x00},
		{0x393a,0x28},
		{0x393b,0x00},
		{0x393c,0x23},
		{0x3e01,0xc2},
		{0x3e02,0x60},
		{0x3e03,0x0b},
		{0x3e08,0x03},
		{0x3e1b,0x2a},
		{0x440e,0x02},
		{0x4509,0x20},
		{0x4837,0x16},
		{0x5000,0x0e},
		{0x5001,0x44},
		{0x5780,0x76},
		{0x5784,0x08},
		{0x5785,0x04},
		{0x5787,0x0a},
		{0x5788,0x0a},
		{0x5789,0x0a},
		{0x578a,0x0a},
		{0x578b,0x0a},
		{0x578c,0x0a},
		{0x578d,0x40},
		{0x5790,0x08},
		{0x5791,0x04},
		{0x5792,0x04},
		{0x5793,0x08},
		{0x5794,0x04},
		{0x5795,0x04},
		{0x5799,0x46},
		{0x579a,0x77},
		{0x57a1,0x04},
		{0x57a8,0xd0},
		{0x57aa,0x2a},
		{0x57ab,0x7f},
		{0x57ac,0x00},
		{0x57ad,0x00},
		{0x59e0,0xfe},
		{0x59e1,0x40},
		{0x59e2,0x3f},
		{0x59e3,0x38},
		{0x59e4,0x30},
		{0x59e5,0x3f},
		{0x59e6,0x38},
		{0x59e7,0x30},
		{0x59e8,0x3f},
		{0x59e9,0x3c},
		{0x59ea,0x38},
		{0x59eb,0x3f},
		{0x59ec,0x3c},
		{0x59ed,0x38},
		{0x59ee,0xfe},
		{0x59ef,0x40},
		{0x59f4,0x3f},
		{0x59f5,0x38},
		{0x59f6,0x30},
		{0x59f7,0x3f},
		{0x59f8,0x38},
		{0x59f9,0x30},
		{0x59fa,0x3f},
		{0x59fb,0x3c},
		{0x59fc,0x38},
		{0x59fd,0x3f},
		{0x59fe,0x3c},
		{0x59ff,0x38},
		{0x36e9,0x20},
		{0x36f9,0x53},
		{0x0100,0x01},
};



static struct sc450ai_gain gain_mapping[] = {
	{0x0300, 0x40, 1.000},
	{0x0300, 0x41, 1.016},
	{0x0300, 0x42, 1.031},
	{0x0300, 0x43, 1.047},
	{0x0300, 0x44, 1.063},
	{0x0300, 0x45, 1.078},
	{0x0300, 0x46, 1.094},
	{0x0300, 0x47, 1.109},
	{0x0300, 0x48, 1.125},
	{0x0300, 0x49, 1.141},
	{0x0300, 0x4a, 1.156},
	{0x0300, 0x4b, 1.172},
	{0x0300, 0x4c, 1.188},
	{0x0300, 0x4d, 1.203},
	{0x0300, 0x4e, 1.219},
	{0x0300, 0x4f, 1.234},
	{0x0300, 0x50, 1.250},
	{0x0300, 0x51, 1.266},
	{0x0300, 0x52, 1.281},
	{0x0300, 0x53, 1.297},
	{0x0300, 0x54, 1.313},
	{0x0300, 0x55, 1.328},
	{0x0300, 0x56, 1.344},
	{0x0300, 0x57, 1.359},
	{0x0300, 0x58, 1.375},
	{0x0300, 0x59, 1.391},
	{0x0300, 0x5a, 1.406},
	{0x0300, 0x5b, 1.422},
	{0x0300, 0x5c, 1.438},
	{0x0300, 0x5d, 1.453},
	{0x0300, 0x5e, 1.469},
	{0x0300, 0x5f, 1.484},
	{0x0300, 0x60, 1.500},
	{0x0300, 0x61, 1.516},
	{0x0300, 0x62, 1.531},
	{0x0300, 0x63, 1.547},
	{0x0300, 0x64, 1.563},
	{0x0300, 0x65, 1.578},
	{0x0300, 0x66, 1.594},
	{0x0300, 0x67, 1.609},
	{0x0300, 0x68, 1.625},
	{0x0300, 0x69, 1.641},
	{0x0300, 0x6a, 1.656},
	{0x0300, 0x6b, 1.672},
	{0x0300, 0x6c, 1.688},
	{0x0300, 0x6d, 1.703},
	{0x0300, 0x6e, 1.719},
	{0x0300, 0x6f, 1.734},
	{0x0300, 0x70, 1.750},
	{0x0300, 0x71, 1.766},
	{0x0300, 0x72, 1.781},
	{0x0300, 0x73, 1.797},
	{0x0300, 0x74, 1.813},
	{0x0300, 0x75, 1.828},
	{0x0300, 0x76, 1.844},
	{0x0300, 0x77, 1.859},
	{0x0300, 0x78, 1.875},
	{0x0300, 0x79, 1.891},
	{0x0300, 0x7a, 1.906},
	{0x0300, 0x7b, 1.922},
	{0x0300, 0x7c, 1.938},
	{0x0300, 0x7d, 1.953},
	{0x0300, 0x7e, 1.969},
	{0x0300, 0x7f, 1.984},
	{0x0700, 0x40, 2.000},
	{0x0700, 0x41, 2.031},
	{0x0700, 0x42, 2.063},
	{0x0700, 0x43, 2.094},
	{0x0700, 0x44, 2.125},
	{0x0700, 0x45, 2.156},
	{0x0700, 0x46, 2.188},
	{0x0700, 0x47, 2.219},
	{0x0700, 0x48, 2.250},
	{0x0700, 0x49, 2.281},
	{0x0700, 0x4a, 2.313},
	{0x0700, 0x4b, 2.344},
	{0x0700, 0x4c, 2.375},
	{0x0700, 0x4d, 2.406},
	{0x0700, 0x4e, 2.438},
	{0x0700, 0x4f, 2.469},
	{0x0700, 0x50, 2.500},
	{0x0700, 0x51, 2.531},
	{0x0700, 0x52, 2.563},
	{0x0700, 0x53, 2.594},
	{0x0700, 0x54, 2.625},
	{0x0700, 0x55, 2.656},
	{0x0700, 0x56, 2.688},
	{0x0700, 0x57, 2.719},
	{0x0700, 0x58, 2.750},
	{0x0700, 0x59, 2.781},
	{0x0700, 0x5a, 2.813},
	{0x0700, 0x5b, 2.844},
	{0x0700, 0x5c, 2.875},
	{0x0700, 0x5d, 2.906},
	{0x0700, 0x5e, 2.938},
	{0x0700, 0x5f, 2.969},
	{0x0700, 0x60, 3.000},
	{0x0700, 0x61, 3.031},
	{0x0700, 0x62, 3.063},
	{0x0700, 0x63, 3.094},
	{0x0700, 0x64, 3.125},
	{0x0700, 0x65, 3.156},
	{0x0700, 0x66, 3.188},
	{0x0700, 0x67, 3.219},
	{0x0700, 0x68, 3.250},
	{0x0700, 0x69, 3.281},
	{0x0700, 0x6a, 3.313},
	{0x0700, 0x6b, 3.344},
	{0x0700, 0x6c, 3.375},
	{0x0700, 0x6d, 3.406},
	{0x0700, 0x6e, 3.438},
	{0x0700, 0x6f, 3.469},
	{0x0700, 0x70, 3.500},
	{0x0700, 0x71, 3.531},
	{0x0700, 0x72, 3.563},
	{0x0700, 0x73, 3.594},
	{0x0700, 0x74, 3.625},
	{0x0700, 0x75, 3.656},
	{0x0700, 0x76, 3.688},
	{0x0700, 0x77, 3.719},
	{0x0700, 0x78, 3.750},
	{0x0700, 0x79, 3.781},
	{0x2300, 0x40, 3.813},
	{0x2300, 0x41, 3.872},
	{0x2300, 0x42, 3.932},
	{0x2300, 0x43, 3.991},
	{0x2300, 0x44, 4.051},
	{0x2300, 0x45, 4.110},
	{0x2300, 0x46, 4.170},
	{0x2300, 0x47, 4.229},
	{0x2300, 0x48, 4.289},
	{0x2300, 0x49, 4.349},
	{0x2300, 0x4a, 4.408},
	{0x2300, 0x4b, 4.468},
	{0x2300, 0x4c, 4.527},
	{0x2300, 0x4d, 4.587},
	{0x2300, 0x4e, 4.646},
	{0x2300, 0x4f, 4.706},
	{0x2300, 0x50, 4.766},
	{0x2300, 0x51, 4.825},
	{0x2300, 0x52, 4.885},
	{0x2300, 0x53, 4.944},
	{0x2300, 0x54, 5.004},
	{0x2300, 0x55, 5.063},
	{0x2300, 0x56, 5.123},
	{0x2300, 0x57, 5.183},
	{0x2300, 0x58, 5.242},
	{0x2300, 0x59, 5.302},
	{0x2300, 0x5a, 5.361},
	{0x2300, 0x5b, 5.421},
	{0x2300, 0x5c, 5.480},
	{0x2300, 0x5d, 5.540},
	{0x2300, 0x5e, 5.600},
	{0x2300, 0x5f, 5.659},
	{0x2300, 0x60, 5.719},
	{0x2300, 0x61, 5.778},
	{0x2300, 0x62, 5.838},
	{0x2300, 0x63, 5.897},
	{0x2300, 0x64, 5.957},
	{0x2300, 0x65, 6.017},
	{0x2300, 0x66, 6.076},
	{0x2300, 0x67, 6.136},
	{0x2300, 0x68, 6.195},
	{0x2300, 0x69, 6.255},
	{0x2300, 0x6a, 6.314},
	{0x2300, 0x6b, 6.374},
	{0x2300, 0x6c, 6.434},
	{0x2300, 0x6d, 6.493},
	{0x2300, 0x6e, 6.553},
	{0x2300, 0x6f, 6.612},
	{0x2300, 0x70, 6.672},
	{0x2300, 0x71, 6.731},
	{0x2300, 0x72, 6.791},
	{0x2300, 0x73, 6.851},
	{0x2300, 0x74, 6.910},
	{0x2300, 0x75, 6.970},
	{0x2300, 0x76, 7.029},
	{0x2300, 0x77, 7.089},
	{0x2300, 0x78, 7.148},
	{0x2300, 0x79, 7.208},
	{0x2300, 0x7a, 7.268},
	{0x2300, 0x7b, 7.327},
	{0x2300, 0x7c, 7.387},
	{0x2300, 0x7d, 7.446},
	{0x2300, 0x7e, 7.506},
	{0x2300, 0x7f, 7.565},
	{0x2700, 0x40, 7.625},
	{0x2700, 0x41, 7.744},
	{0x2700, 0x42, 7.863},
	{0x2700, 0x43, 7.982},
	{0x2700, 0x44, 8.102},
	{0x2700, 0x45, 8.221},
	{0x2700, 0x46, 8.340},
	{0x2700, 0x47, 8.459},
	{0x2700, 0x48, 8.578},
	{0x2700, 0x49, 8.697},
	{0x2700, 0x4a, 8.816},
	{0x2700, 0x4b, 8.936},
	{0x2700, 0x4c, 9.055},
	{0x2700, 0x4d, 9.174},
	{0x2700, 0x4e, 9.293},
	{0x2700, 0x4f, 9.412},
	{0x2700, 0x50, 9.531},
	{0x2700, 0x51, 9.650},
	{0x2700, 0x52, 9.770},
	{0x2700, 0x53, 9.889},
	{0x2700, 0x54, 10.008},
	{0x2700, 0x55, 10.127},
	{0x2700, 0x56, 10.246},
	{0x2700, 0x57, 10.365},
	{0x2700, 0x58, 10.484},
	{0x2700, 0x59, 10.604},
	{0x2700, 0x5a, 10.723},
	{0x2700, 0x5b, 10.842},
	{0x2700, 0x5c, 10.961},
	{0x2700, 0x5d, 11.080},
	{0x2700, 0x5e, 11.199},
	{0x2700, 0x5f, 11.318},
	{0x2700, 0x60, 11.438},
	{0x2700, 0x61, 11.557},
	{0x2700, 0x62, 11.676},
	{0x2700, 0x63, 11.795},
	{0x2700, 0x64, 11.914},
	{0x2700, 0x65, 12.033},
	{0x2700, 0x66, 12.152},
	{0x2700, 0x67, 12.271},
	{0x2700, 0x68, 12.391},
	{0x2700, 0x69, 12.510},
	{0x2700, 0x6a, 12.629},
	{0x2700, 0x6b, 12.748},
	{0x2700, 0x6c, 12.867},
	{0x2700, 0x6d, 12.986},
	{0x2700, 0x6e, 13.105},
	{0x2700, 0x6f, 13.225},
	{0x2700, 0x70, 13.344},
	{0x2700, 0x71, 13.463},
	{0x2700, 0x72, 13.582},
	{0x2700, 0x73, 13.701},
	{0x2700, 0x74, 13.820},
	{0x2700, 0x75, 13.939},
	{0x2700, 0x76, 14.059},
	{0x2700, 0x77, 14.178},
	{0x2700, 0x78, 14.297},
	{0x2700, 0x79, 14.416},
	{0x2700, 0x7a, 14.535},
	{0x2700, 0x7b, 14.654},
	{0x2700, 0x7c, 14.773},
	{0x2700, 0x7d, 14.893},
	{0x2700, 0x7e, 15.012},
	{0x2700, 0x7f, 15.131},
	{0x2f00, 0x40, 15.250},
	{0x2f00, 0x41, 15.488},
	{0x2f00, 0x42, 15.727},
	{0x2f00, 0x43, 15.965},
	{0x2f00, 0x44, 16.203},
	{0x2f00, 0x45, 16.441},
	{0x2f00, 0x46, 16.680},
	{0x2f00, 0x47, 16.918},
	{0x2f00, 0x48, 17.156},
	{0x2f00, 0x49, 17.395},
	{0x2f00, 0x4a, 17.633},
	{0x2f00, 0x4b, 17.871},
	{0x2f00, 0x4c, 18.109},
	{0x2f00, 0x4d, 18.348},
	{0x2f00, 0x4e, 18.586},
	{0x2f00, 0x4f, 18.824},
	{0x2f00, 0x50, 19.063},
	{0x2f00, 0x51, 19.301},
	{0x2f00, 0x52, 19.539},
	{0x2f00, 0x53, 19.777},
	{0x2f00, 0x54, 20.016},
	{0x2f00, 0x55, 20.254},
	{0x2f00, 0x56, 20.492},
	{0x2f00, 0x57, 20.730},
	{0x2f00, 0x58, 20.969},
	{0x2f00, 0x59, 21.207},
	{0x2f00, 0x5a, 21.445},
	{0x2f00, 0x5b, 21.684},
	{0x2f00, 0x5c, 21.922},
	{0x2f00, 0x5d, 22.160},
	{0x2f00, 0x5e, 22.398},
	{0x2f00, 0x5f, 22.637},
	{0x2f00, 0x60, 22.875},
	{0x2f00, 0x61, 23.113},
	{0x2f00, 0x62, 23.352},
	{0x2f00, 0x63, 23.590},
	{0x2f00, 0x64, 23.828},
	{0x2f00, 0x65, 24.066},
	{0x2f00, 0x66, 24.305},
	{0x2f00, 0x67, 24.543},
	{0x2f00, 0x68, 24.781},
	{0x2f00, 0x69, 25.020},
	{0x2f00, 0x6a, 25.258},
	{0x2f00, 0x6b, 25.496},
	{0x2f00, 0x6c, 25.734},
	{0x2f00, 0x6d, 25.973},
	{0x2f00, 0x6e, 26.211},
	{0x2f00, 0x6f, 26.449},
	{0x2f00, 0x70, 26.688},
	{0x2f00, 0x71, 26.926},
	{0x2f00, 0x72, 27.164},
	{0x2f00, 0x73, 27.402},
	{0x2f00, 0x74, 27.641},
	{0x2f00, 0x75, 27.879},
	{0x2f00, 0x76, 28.117},
	{0x2f00, 0x77, 28.355},
	{0x2f00, 0x78, 28.594},
	{0x2f00, 0x79, 28.832},
	{0x2f00, 0x7a, 29.070},
	{0x2f00, 0x7b, 29.309},
	{0x2f00, 0x7c, 29.547},
	{0x2f00, 0x7d, 29.785},
	{0x2f00, 0x7e, 30.023},
	{0x2f00, 0x7f, 30.262},
	{0x3f00, 0x40, 30.500},
	{0x3f00, 0x41, 30.977},
	{0x3f00, 0x42, 31.453},
	{0x3f00, 0x43, 31.930},
	{0x3f00, 0x44, 32.406},
	{0x3f00, 0x45, 32.883},
	{0x3f00, 0x46, 33.359},
	{0x3f00, 0x47, 33.836},
	{0x3f00, 0x48, 34.313},
	{0x3f00, 0x49, 34.789},
	{0x3f00, 0x4a, 35.266},
	{0x3f00, 0x4b, 35.742},
	{0x3f00, 0x4c, 36.219},
	{0x3f00, 0x4d, 36.695},
	{0x3f00, 0x4e, 37.172},
	{0x3f00, 0x4f, 37.648},
	{0x3f00, 0x50, 38.125},
	{0x3f00, 0x51, 38.602},
	{0x3f00, 0x52, 39.078},
	{0x3f00, 0x53, 39.555},
	{0x3f00, 0x54, 40.031},
	{0x3f00, 0x55, 40.508},
	{0x3f00, 0x56, 40.984},
	{0x3f00, 0x57, 41.461},
	{0x3f00, 0x58, 41.938},
	{0x3f00, 0x59, 42.414},
	{0x3f00, 0x5a, 42.891},
	{0x3f00, 0x5b, 43.367},
	{0x3f00, 0x5c, 43.844},
	{0x3f00, 0x5d, 44.320},
	{0x3f00, 0x5e, 44.797},
	{0x3f00, 0x5f, 45.273},
	{0x3f00, 0x60, 45.750},
	{0x3f00, 0x61, 46.227},
	{0x3f00, 0x62, 46.703},
	{0x3f00, 0x63, 47.180},
	{0x3f00, 0x64, 47.656},
	{0x3f00, 0x65, 48.133},
	{0x3f00, 0x66, 48.609},
	{0x3f00, 0x67, 49.086},
	{0x3f00, 0x68, 49.563},
	{0x3f00, 0x69, 50.039},
	{0x3f00, 0x6a, 50.516},
	{0x3f00, 0x6b, 50.992},
	{0x3f00, 0x6c, 51.469},
	{0x3f00, 0x6d, 51.945},
	{0x3f00, 0x6e, 52.422},
	{0x3f00, 0x6f, 52.898},
	{0x3f00, 0x70, 53.375},
	{0x3f00, 0x71, 53.852},
	{0x3f00, 0x72, 54.328},
	{0x3f00, 0x73, 54.805},
	{0x3f00, 0x74, 55.281},
	{0x3f00, 0x75, 55.758},
	{0x3f00, 0x76, 56.234},
	{0x3f00, 0x77, 56.711},
	{0x3f00, 0x78, 57.188},
	{0x3f00, 0x79, 57.664},
	{0x3f00, 0x7a, 58.141},
	{0x3f00, 0x7b, 58.617},
	{0x3f00, 0x7c, 59.094},
	{0x3f00, 0x7d, 59.570},
	{0x3f00, 0x7e, 60.047},
	{0x3f00, 0x7f, 60.523},
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x30	//0x60(default)
#define SLAVE_ADDR_1 0x32	//0x64

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int sc450ai_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;
	info->modes.mode[0].size.w = 2560;
	info->modes.mode[0].size.h = 1440;
	info->modes.mode[0].fps = g_sc450ai_fps_info_asic_linear[0].fps;			//@MLCK=27MHz
	info->modes.num = 1;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 5000);
	set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 1000);
	set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V5, 1000);
	set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 5000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 10000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, 0, 0);
	set_power_item(&down->items[i++], SNR_CORE_POWER, 0, 0);
	set_power_item(&down->items[i++], SNR_IO_POWER, 0, 0);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *sc450ai_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

		for (i = 0; i < ARRAY_SIZE(g_sc450ai_fps_info_asic_linear); i++)
			if (fps == g_sc450ai_fps_info_asic_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc450ai_fps_info_asic_linear))
			return NULL;

		return &g_sc450ai_fps_info_asic_linear[i];
	
}

static int sc450ai_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc450ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;
	printf("sc450ai_get_init_info hdr: %x fps: %d\n\r", mode->hdr, mode->fps);
	fps_info = sc450ai_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;
	printf("fps_info: %x\n\r", fps_info);

	printf("sc450ai_get_init_info linear\n\r");

	set_init_i2c_regs(info->sensor_regs[0],
			  g_sc450ai_i2c_init_regs_asic_linear, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x2;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2560;
	info->size.h = 1440;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = fps_info->hts ;
	info->min_vts = status->min_vts = fps_info->vts;
	info->pclk = fps_info->clk;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	

	return RTS_ISP_OK;
}
static int sc450ai_start(uint32_t isp_id)
{
	struct sc450ai_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	//status->max_short_exp = AE_MAX_SHORT_EXP_BASE;
	//status->last_max_short_exp = AE_MAX_SHORT_EXP_BASE;

	return RTS_ISP_OK;
}

static int sc450ai_get_exposure_range(uint32_t isp_id, uint32_t vts,
				     float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				     float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				     float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc450ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	min_exposure[0] = status->exp_step;
	max_exposure[0] = (vts - 8) * status->exp_step;


	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;
	int i;

	if (fgain >= 15.965) {
		reg_value = 0x2f43;
	} else {
		for (i = 0; i < ((ARRAY_SIZE(gain_mapping)) - 1); i++) {
			if ((gain_mapping[i].total_gain <= fgain) &&
			    (fgain < gain_mapping[i + 1].total_gain)) {
				reg_value = gain_mapping[i].ana_gain |
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

	if (reg_value >= 0x2f43) {
		gain = 15.965;
	} else {
		for (i = 0; i < ((ARRAY_SIZE(gain_mapping)) - 1); i++) {
			if (reg_value == (gain_mapping[i].ana_gain |
			    gain_mapping[i].fine_gain)) {
				gain = gain_mapping[i].total_gain;
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

static int sc450ai_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc450ai_status *status;

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

static int sc450ai_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc450ai_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int sc450ai_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	int exp_set;
	uint16_t total_line;
	uint16_t gain_reg;
	float exp_reg_value_float;
	uint32_t exp_reg_value;
	float gain;
	struct sc450ai_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);

	// total_line = status->min_vts + exp_gain[0]->extra_dummy;
	total_line = exp_gain->vts;

	exp_reg_value_float =
		2.0 * exp_gain->exposure[0] / status->exp_step + 0.5f;
	exp_reg_value =
		clip_d_word(exp_reg_value_float, 1, (2 * total_line - 8));
	exp_reg_value = exp_reg_value << 4;

	reg = regs->reg;

	i = 0;

	set_sync_i2c(&reg[i++], 0x320e, (total_line >> 8));
	set_sync_i2c(&reg[i++], 0x320f, (total_line & 0xff));

	exp_set = abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f;
	if (exp_set) {
		set_sync_i2c(&reg[i++], 0x3e00, exp_reg_value >> 16);
		set_sync_i2c(&reg[i++], 0x3e01, (exp_reg_value & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3e02, exp_reg_value & 0xff);
		status->last_exposure[0] = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x3e08, (gain_reg >> 8));
	set_sync_i2c(&reg[i++], 0x3e09, (gain_reg & 0xff));

	regs->num = i;

	//exp_gain->analog_gain[0] = get_sensor_real_gain(gain_reg);
	//exp_gain->digital_gain[0] = 1.0f;

	return RTS_ISP_OK;
}


static int sc450ai_set_mirror_flip(uint32_t isp_id,
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
            set_sync_i2c(&reg[i++], 0x3221, 0x00);
			break;
		case 1: // Mirror
           	set_sync_i2c(&reg[i++], 0x3221, 0x06);
			break;
		case 2:	// VFlip
            set_sync_i2c(&reg[i++], 0x3221, 0x60);
			break;
		case 3:	// Rotate
            set_sync_i2c(&reg[i++], 0x3221, 0x66);
			break;
	}
	mf_info->regs.num = i;
	

	return RTS_ISP_OK;
}

static int sc450ai_check(uint32_t isp_id)
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

	if (id == 0xbd2f)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int sc450ai_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops sc450ai_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc450ai",
	.get_info = sc450ai_get_info,
	.get_init_info = sc450ai_get_init_info,
	.start = sc450ai_start,
	.get_exposure_range = sc450ai_get_exposure_range,
	.get_tuned_again = sc450ai_get_tuned_again,
	.get_tuned_dgain = sc450ai_get_tuned_dgain,
	.get_exposure_gain_info = sc450ai_get_exposure_gain_info,
	.set_mirror_flip = sc450ai_set_mirror_flip,
	.check = sc450ai_check,
	.get_slave_addr_num = sc450ai_get_slave_addr_num,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc450ai_ops;
}

//#endif


