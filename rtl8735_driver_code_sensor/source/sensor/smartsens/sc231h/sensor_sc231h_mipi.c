/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 * Copyright (C) 2022 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <platform_conf.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#if _SC231H_SENSOR_

//#define DEBUG 
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define interval_between_long_short 196

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define ORIENTATION 0	//0=default, 1=rotate180
#define SHORT_EXP_MAX 50
#define ANALOG_GAIN_MAX_RATIO 15.725f


struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct sc231h_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t min_vts;
	uint16_t last_vts;
	uint16_t max_short_exp;
	uint16_t last_max_short_exp;
	uint16_t gain_reg_num;
	uint16_t last_gain_reg_num;
	uint16_t num
};

struct sc231h_gain_config {
	uint16_t ana_gain;
	uint16_t fine_gain;
	float total_gain;
};

static struct sc231h_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_sc231h_fps_info_asic[] = {
	{30, 2200, 1200, 79200000},
};

static const struct fps_info g_sc231h_fps_info_asic_hdr[] = {
	{30, 2240, 2250, 151200000},
};

static struct rts_isp_i2c_reg g_sc231h_i2c_init_regs_asic[] = {
	//Cleaned_0x14_SC231AI_MIPI_24Minput_2lane_396Mbps_10bit_1920x1080_30fps_¥~¨Ñ.ini
	{0x0103,0x01},
	{0x36e9,0x80},
	{0x37f9,0x80},
	{0x301f,0x14},
	{0x3058,0x21},
	{0x3059,0x53},
	{0x305a,0x40},
	{0x320e,0x04},
	{0x320f,0xb0},
	{0x3210,0x00},
	{0x3211,0x04},
	{0x3212,0x00},
	{0x3213,0x03},
	{0x3250,0x00},
	{0x3301,0x0a},
	{0x3302,0x20},
	{0x3304,0x90},
	{0x3305,0x00},
	{0x3306,0x68},
	{0x3309,0xd0},
	{0x330b,0xd8},
	{0x330d,0x08},
	{0x331c,0x04},
	{0x331e,0x81},
	{0x331f,0xc1},
	{0x3323,0x06},
	{0x3333,0x10},
	{0x3334,0x40},
	{0x3364,0x5e},
	{0x336c,0x8e},
	{0x337f,0x13},
	{0x338f,0x80},
	{0x3390,0x08},
	{0x3391,0x18},
	{0x3392,0xb8},
	{0x3393,0x0e},
	{0x3394,0x14},
	{0x3395,0x10},
	{0x3396,0x88},
	{0x3397,0x98},
	{0x3398,0xf8},
	{0x3399,0x0a},
	{0x339a,0x0e},
	{0x339b,0x10},
	{0x339c,0x16},
	{0x33ae,0x80},
	{0x33af,0xc0},
	{0x33b1,0x80},
	{0x33b2,0x50},
	{0x33b3,0x14},
	{0x33f8,0x00},
	{0x33f9,0x68},
	{0x33fa,0x00},
	{0x33fb,0x68},
	{0x33fc,0x48},
	{0x33fd,0x78},
	{0x349f,0x03},
	{0x34a6,0x40},
	{0x34a7,0x58},
	{0x34a8,0x10},
	{0x34a9,0x10},
	{0x34f8,0x78},
	{0x34f9,0x10},
	{0x3619,0x20},
	{0x361a,0x90},
	{0x3633,0x44},
	{0x3637,0x5c},
	{0x363c,0xc0},
	{0x363d,0x02},
	{0x3660,0x80},
	{0x3661,0x81},
	{0x3662,0x8f},
	{0x3663,0x81},
	{0x3664,0x81},
	{0x3665,0x82},
	{0x3666,0x8f},
	{0x3667,0x08},
	{0x3668,0x80},
	{0x3669,0x88},
	{0x366a,0x98},
	{0x366b,0xb8},
	{0x366c,0xf8},
	{0x3670,0xb2},
	{0x3671,0xa2},
	{0x3672,0x88},
	{0x3680,0x33},
	{0x3681,0x33},
	{0x3682,0x43},
	{0x36c0,0x80},
	{0x36c1,0x88},
	{0x36c8,0x88},
	{0x36c9,0xb8},
	{0x36ea,0x0b},
	{0x36eb,0x0c},
	{0x36ec,0x5c},
	{0x36ed,0x04},
	{0x3718,0x04},
	{0x3722,0x8b},
	{0x3724,0xd1},
	{0x3741,0x08},
	{0x3770,0x17},
	{0x3771,0x9b},
	{0x3772,0x9b},
	{0x37c0,0x88},
	{0x37c1,0xb8},
	{0x37fa,0x0b},
	{0x37fc,0x10},
	{0x37fd,0x04},
	{0x3902,0xc0},
	{0x3903,0x40},
	{0x3909,0x00},
	{0x391f,0x41},
	{0x3926,0xe0},
	{0x3933,0x80},
	{0x3934,0x02},
	{0x3937,0x6f},
	{0x3e00,0x00},
	{0x3e01,0x95},
	{0x3e02,0x50},
	{0x3e08,0x00},
	{0x4509,0x20},
	{0x450d,0x07},
	{0x4837,0x33},
	{0x5780,0x76},
	{0x5784,0x10},
	{0x5787,0x0a},
	{0x5788,0x0a},
	{0x5789,0x08},
	{0x578a,0x0a},
	{0x578b,0x0a},
	{0x578c,0x08},
	{0x578d,0x40},
	{0x5792,0x04},
	{0x5795,0x04},
	{0x57ac,0x00},
	{0x57ad,0x00},
	{0x36e9,0x27},
	{0x37f9,0x27},
	{0x0100,0x01},

};
static struct rts_isp_i2c_reg g_sc231h_i2c_init_regs_asic_hdr[] = {
	//Cleaned_0x69_SC231HAI_MIPI_24Minput_2lane_756Mbps_10bit_1928x1086_30fps_SHDR_VC.ini
    {0x0103,0x01},
    {0x36e9,0x80},
    {0x37f9,0x80},
    {0x301f,0x69},
    {0x3058,0x21},
    {0x3059,0x53},
    {0x305a,0x40},
    {0x3200,0x00},
    {0x3201,0x00},
    {0x3202,0x00},
    {0x3203,0x00},
    {0x3204,0x07},
    {0x3205,0x87},
    {0x3206,0x04},
    {0x3207,0x41},
    {0x3208,0x07},
    {0x3209,0x88},
    {0x320a,0x04},
    {0x320b,0x3e},
    {0x320c,0x08},
    {0x320d,0xc0},
    {0x320e,0x08},
    {0x320f,0xca},
    {0x3210,0x00},
    {0x3211,0x00},
    {0x3212,0x00},
    {0x3213,0x03},   //0x02
    {0x3250,0xff},
    {0x3281,0x01},
    {0x3301,0x0a},
    {0x3302,0x20},
    {0x3304,0x90},
    {0x3305,0x00},
    {0x3306,0x78},
    {0x3309,0xd0},
    {0x330b,0xe8},
    {0x330d,0x08},
    {0x331c,0x04},
    {0x331e,0x81},
    {0x331f,0xc1},
    {0x3323,0x06},
    {0x3333,0x10},
    {0x3334,0x40},
    {0x3364,0x5e},
    {0x336c,0x8c},
    {0x337f,0x13},
    {0x338f,0x80},
    {0x3390,0x08},
    {0x3391,0x18},
    {0x3392,0xb8},
    {0x3393,0x10},
    {0x3394,0x14},
    {0x3395,0x10},
    {0x3396,0x88},
    {0x3397,0x98},
    {0x3398,0xf8},
    {0x3399,0x0a},
    {0x339a,0x0e},
    {0x339b,0x10},
    {0x339c,0x14},
    {0x33ae,0x80},
    {0x33af,0xc0},
    {0x33b1,0x80},
    {0x33b2,0x50},
    {0x33b3,0x08},
    {0x33f8,0x00},
    {0x33f9,0x78},
    {0x33fa,0x00},
    {0x33fb,0x78},
    {0x33fc,0x48},
    {0x33fd,0x78},
    {0x349f,0x03},
    {0x34a6,0x40},
    {0x34a7,0x58},
    {0x34a8,0x08},
    {0x34a9,0x0c},
    {0x34f8,0x78},
    {0x34f9,0x18},
    {0x3619,0x20},
    {0x361a,0x90},
    {0x3633,0x44},
    {0x3637,0x5c},
    {0x363c,0xc0},
    {0x363d,0x02},
    {0x3660,0x80},
    {0x3661,0x81},
    {0x3662,0x8f},
    {0x3663,0x81},
    {0x3664,0x81},
    {0x3665,0x82},
    {0x3666,0x8f},
    {0x3667,0x08},
    {0x3668,0x80},
    {0x3669,0x88},
    {0x366a,0x98},
    {0x366b,0xb8},
    {0x366c,0xf8},
    {0x3670,0xc2},
    {0x3671,0xc2},
    {0x3672,0x98},
    {0x3680,0x43},
    {0x3681,0x54},
    {0x3682,0x54},
    {0x36c0,0x80},
    {0x36c1,0x88},
    {0x36c8,0x88},
    {0x36c9,0xb8},
    {0x36ea,0xc7},
    {0x36eb,0x04},
    {0x36ec,0x4c},
    {0x36ed,0x04},
    {0x3718,0x04},
    {0x3722,0x8b},
    {0x3724,0xd1},
    {0x3741,0x08},
    {0x3770,0x17},
    {0x3771,0x9b},
    {0x3772,0x9b},
    {0x37c0,0x88},
    {0x37c1,0xb8},
    {0x37fa,0xc7},
    {0x37fc,0x00},
    {0x37fd,0x04},
    {0x3902,0xc0},
    {0x3903,0x40},
    {0x3909,0x00},
    {0x391f,0x41},
    {0x3926,0xe0},
    {0x3933,0x80},
    {0x3934,0x02},
    {0x3937,0x6f},
    {0x3e00,0x01},
    {0x3e01,0x02},
    {0x3e02,0x00},
    {0x3e04,0x10},
    {0x3e05,0x20},
    {0x3e08,0x00},
    {0x3e23,0x00},
    {0x3e24,0x64},
    {0x4509,0x20},
    {0x450d,0x07},
    {0x4816,0x71},
    {0x4837,0x1a},
    {0x5780,0x76},
    {0x5784,0x10},
    {0x5787,0x0a},
    {0x5788,0x0a},
    {0x5789,0x08},
    {0x578a,0x0a},
    {0x578b,0x0a},
    {0x578c,0x08},
    {0x578d,0x40},
    {0x5792,0x04},
    {0x5795,0x04},
    {0x57ac,0x00},
    {0x57ad,0x00},
    {0x36e9,0x23},
    {0x37f9,0x23},
    {0x0100,0x01},

};



static struct sc231h_gain_config gain_mapping[] = {
	{0x0000, 0x20, 1.000}, 
	{0x0000, 0x21, 1.031}, 
	{0x0000, 0x22, 1.063}, 
	{0x0000, 0x23, 1.094}, 
	{0x0000, 0x24, 1.125}, 
	{0x0000, 0x25, 1.156}, 
	{0x0000, 0x26, 1.188}, 
	{0x0000, 0x27, 1.219}, 
	{0x0000, 0x28, 1.250}, 
	{0x0000, 0x29, 1.281}, 
	{0x0000, 0x2a, 1.313}, 
	{0x0000, 0x2b, 1.344}, 
	{0x0000, 0x2c, 1.375}, 
	{0x0000, 0x2d, 1.406}, 
	{0x0000, 0x2e, 1.438}, 
	{0x0000, 0x2f, 1.469}, 
	{0x0000, 0x30, 1.500}, 
	{0x0000, 0x31, 1.531}, 
	{0x0000, 0x32, 1.563}, 
	{0x0000, 0x33, 1.594}, 
	{0x0000, 0x34, 1.625}, 
	{0x0000, 0x35, 1.656}, 
	{0x0000, 0x36, 1.688}, 
	{0x0000, 0x37, 1.719}, 
	{0x0000, 0x38, 1.750}, 
	{0x0000, 0x39, 1.781}, 
	{0x0000, 0x3a, 1.813}, 
	{0x0000, 0x3b, 1.844}, 
	{0x0000, 0x3c, 1.875}, 
	{0x0000, 0x3d, 1.906}, 
	{0x0000, 0x3e, 1.938}, 
	{0x0000, 0x3f, 1.969}, 
	{0x0100, 0x20, 2.000}, 
	{0x0100, 0x21, 2.063}, 
	{0x0100, 0x22, 2.125}, 
	{0x0100, 0x23, 2.188}, 
	{0x0100, 0x24, 2.250}, 
	{0x0100, 0x25, 2.313}, 
	{0x0100, 0x26, 2.375}, 
	{0x0100, 0x27, 2.438}, 
	{0x0100, 0x28, 2.500}, 
	{0x0100, 0x29, 2.563}, 
	{0x0100, 0x2a, 2.625}, 
	{0x0100, 0x2b, 2.688}, 
	{0x0100, 0x2c, 2.750}, 
	{0x0100, 0x2d, 2.813}, 
	{0x0100, 0x2e, 2.875}, 
	{0x0100, 0x2f, 2.938}, 
	{0x0100, 0x30, 3.000}, 
	{0x0100, 0x31, 3.063}, 
	{0x0100, 0x32, 3.125}, 
	{0x0100, 0x33, 3.188}, 
	{0x0100, 0x34, 3.250}, 
	{0x0100, 0x35, 3.313}, 
	{0x0100, 0x36, 3.375}, 
	{0x0100, 0x37, 3.438},
	{0x0100, 0x38, 3.500},
	{0x0100, 0x39, 3.563},
	{0x0100, 0x3a, 3.625},	
	{0x0100, 0x3b, 3.688},	
	{0x8000, 0x20, 3.700}, 
	{0x8000, 0x21, 3.816}, 
	{0x8000, 0x22, 3.931}, 
	{0x8000, 0x23, 4.047}, 
	{0x8000, 0x24, 4.163}, 
	{0x8000, 0x25, 4.278}, 
	{0x8000, 0x26, 4.394}, 
	{0x8000, 0x27, 4.509}, 
	{0x8000, 0x28, 4.625}, 
	{0x8000, 0x29, 4.741}, 
	{0x8000, 0x2a, 4.856}, 
	{0x8000, 0x2b, 4.972}, 
	{0x8000, 0x2c, 5.088}, 
	{0x8000, 0x2d, 5.203}, 
	{0x8000, 0x2e, 5.319}, 
	{0x8000, 0x2f, 5.434}, 
	{0x8000, 0x30, 5.550}, 
	{0x8000, 0x31, 5.666}, 
	{0x8000, 0x32, 5.781}, 
	{0x8000, 0x33, 5.897}, 
	{0x8000, 0x34, 6.013}, 
	{0x8000, 0x35, 6.128}, 
	{0x8000, 0x36, 6.244}, 
	{0x8000, 0x37, 6.359}, 
	{0x8000, 0x38, 6.475}, 
	{0x8000, 0x39, 6.591}, 
	{0x8000, 0x3a, 6.706}, 
	{0x8000, 0x3b, 6.822}, 
	{0x8000, 0x3c, 6.938}, 
	{0x8000, 0x3d, 7.053}, 
	{0x8000, 0x3e, 7.169}, 
	{0x8000, 0x3f, 7.284}, 
	{0x8100, 0x20, 7.400}, 
	{0x8100, 0x21, 7.631}, 
	{0x8100, 0x22, 7.863}, 
	{0x8100, 0x23, 8.094}, 
	{0x8100, 0x24, 8.325}, 
	{0x8100, 0x25, 8.556}, 
	{0x8100, 0x26, 8.788}, 
	{0x8100, 0x27, 9.019}, 
	{0x8100, 0x28, 9.250}, 
	{0x8100, 0x29, 9.481}, 
	{0x8100, 0x2a, 9.713}, 
	{0x8100, 0x2b, 9.944}, 
	{0x8100, 0x2c, 10.175}, 
	{0x8100, 0x2d, 10.406}, 
	{0x8100, 0x2e, 10.638}, 
	{0x8100, 0x2f, 10.869},
	{0x8100, 0x30, 11.100},
	{0x8100, 0x31, 11.331},
	{0x8100, 0x32, 11.563},
	{0x8100, 0x33, 11.794},
	{0x8100, 0x34, 12.025},
	{0x8100, 0x35, 12.256},
	{0x8100, 0x36, 12.488},
	{0x8100, 0x37, 12.719},
	{0x8100, 0x38, 12.950},
	{0x8100, 0x39, 13.181},
	{0x8100, 0x3a, 13.413},
	{0x8100, 0x3b, 13.644},
	{0x8100, 0x3c, 13.875},
	{0x8100, 0x3d, 14.106},
	{0x8100, 0x3e, 14.338},
	{0x8100, 0x3f, 14.569},
	{0x8300, 0x20, 14.800},
	{0x8300, 0x21, 15.263},
	{0x8300, 0x22, 15.725},
	
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x30	//0x60(default)
#define SLAVE_ADDR_1 0x32	//0x64

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;
static int sc231h_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = g_sc231h_fps_info_asic[0].fps;			//@MLCK=24MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_sc231h_fps_info_asic_hdr[0].fps;			//@MLCK=24MHz
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	//set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 500);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 500);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 8000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *sc231h_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;
	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_sc231h_fps_info_asic_hdr); i++)
			if (fps == g_sc231h_fps_info_asic_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc231h_fps_info_asic_hdr))
			return NULL;

		return &g_sc231h_fps_info_asic_hdr[i];
	}
	else
	{
		for (i = 0; i < ARRAY_SIZE(g_sc231h_fps_info_asic); i++)
			if (fps == g_sc231h_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc231h_fps_info_asic))
			return NULL;

		return &g_sc231h_fps_info_asic[i];
	}
}

static int sc231h_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc231h_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("sc231h get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;
	
	printf("sc231h_get_init_info hdr: %x fps: %d\n\r", mode->hdr, mode->fps);
	fps_info = sc231h_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		printf("sc231h_get_init_info HDR mode\n\r");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc231h_i2c_init_regs_asic_hdr, 0);
		
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = VC_HDR;
		
		info->size.w = 1928;
		info->size.h = 1086;
		info->start.x = 0;
		info->start.y = 0;
		
		info->hts = fps_info->hts ;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;
		
		status->exp_step = 1e6 * info->hts / info->pclk; 
	}
	else{
		printf("sc231h_get_init_info linear mode\n\r");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc231h_i2c_init_regs_asic, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 0;
	info->start.y = 0;
		info->hts = fps_info->hts ;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; 
	}

	return RTS_ISP_OK;
}
static int sc231h_start(uint32_t isp_id)
{
	struct sc231h_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	//status->max_short_exp = AE_MAX_SHORT_EXP_BASE;
	//status->last_max_short_exp = AE_MAX_SHORT_EXP_BASE;

	return RTS_ISP_OK;
}

static int sc231h_get_exposure_range(uint32_t isp_id, uint32_t vts,
				     float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				     float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				     float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc231h_status *status;


	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];


	if (status->hdr == HDR_MODE) {

		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t dummy = vts - status->min_vts;
		uint16_t short_exp_max_dummy = SHORT_EXP_MAX + (dummy / 65);
		
		uint16_t max_exp_line = (( 2 * vts ) - ( 2 * short_exp_max_dummy ) -21 )/2 + 0.5;
		//
		tmp1 = (2 * short_exp_max_dummy - 19)/2 + 0.5;
		tmp2 = (uint32_t)(max_exp_line / (ratio[0] + 1));
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		
		
		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = 2 * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];

		//printf("long_max_exposure_=%f, long_min_exposure=%f\n", max_exposure[0], min_exposure[0]);
		//printf("short_max_exposure_=%f, short_min_exposure=%f\n", max_exposure[1], min_exposure[1]);
	}
	else{
		//printf("\x1b[33m Linear %d\x1b[0m\n");

		min_exposure[0] = 2* status->exp_step;
		max_exposure[0] = ((2*vts - 11)/2+0.5) * status->exp_step;
		//printf("vts:%d  exp_step:%f.\r\n", vts, status->exp_step);
		//printf("expusre_min = %.2f , expusre_max = %1.f\n", min_exposure[0],max_exposure[0]);

	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct sc231h_status *status)
{
	uint16_t reg_value = 0;
	int i;

	if (fgain >= ANALOG_GAIN_MAX_RATIO) {
		reg_value = 0x8322;
		status->gain_reg_num = (uint8_t)(ARRAY_SIZE(gain_mapping) - 1);

	} else {
		for (i = 0; i < ((ARRAY_SIZE(gain_mapping)) - 1); i++) {
			if ((gain_mapping[i].total_gain <= fgain) &&
			    (fgain < gain_mapping[i + 1].total_gain)) {
				reg_value = gain_mapping[i].ana_gain | gain_mapping[i].fine_gain;
				status->gain_reg_num = i;
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

	if (reg_value >= 0x8322) {
		gain = ANALOG_GAIN_MAX_RATIO;
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

static int sc231h_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc231h_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	//printf("\x1b[33mget_tuned again: %d\x1b[0m\n", isp_id);

	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	if (status->hdr == HDR_MODE) {
		gain_reg = get_sensor_gain_reg(again[1], status);
		again[1] = get_sensor_real_gain(gain_reg);
	}
	
	
	return RTS_ISP_OK;
}

static int sc231h_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc231h_status *status;
	
	
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	//printf("\x1b[33mget_tuned dgain: %d\x1b[0m\n", isp_id);

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;	
	
	return RTS_ISP_OK;
}

static int sc231h_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct sc231h_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows[2];
	uint32_t gain_reg[2];
	uint32_t exposure_step;
	uint32_t exposure_step_short;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;


	if (status->hdr == HDR_MODE) {
		i = 0;
		
		uint16_t dummy = vts - status->min_vts;
		uint16_t short_exp_max_dummy = SHORT_EXP_MAX + (dummy / 65);

		for (i = 0; i < 2; i++) {
		exposure_rows[i] = exp_gain->exposure[i] / status->exp_step + 0.5f;
		gain_reg[i] = get_sensor_gain_reg(exp_gain->analog_gain[i] * exp_gain->digital_gain[i],status);
		

		
	}
		
		/* set vts */
		if (abs(status->last_vts - vts) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x320E, vts >> 8);
			set_sync_i2c(&reg[i++], 0x320F, vts & 0xff);
			set_sync_i2c(&reg[i++], 0x3e23, (short_exp_max_dummy >> 7));
			set_sync_i2c(&reg[i++], 0x3e24, (( short_exp_max_dummy <<1 )& 0xff));	
			status->last_vts = vts;
		}
		
		/* set exposure */	
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			//printf("exp_gain->exposure[0] = %f, ori_exposure_rows[0] = %d, exp_gain->exposure[1] = %f, ori_exposure_rows[1] = %d \n ",exp_gain->exposure[0], exposure_rows[0], exp_gain->exposure[1], exposure_rows[1]);	

			exposure_rows[0] = clip_d_word(exposure_rows[0], 2, (vts - short_exp_max_dummy - 11));	
			exposure_step = exposure_rows[0] << 1;			//in the unit of half line
			exposure_step = exposure_step << 4;			
		
			set_sync_i2c(&reg[i++], 0x3e00, (exposure_step & 0xff0000) >> 16);
			set_sync_i2c(&reg[i++], 0x3e01, (exposure_step & 0xff00) >> 8);
			set_sync_i2c(&reg[i++], 0x3e02, exposure_step & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];
			//printf("status->exp_step = %f, vts = %d, exposure_rows[0] = %d, exposure_step = %d \n ",status->exp_step, vts,exposure_rows[0],exposure_step);	
		}

		/* set gain */
		if (abs(status->last_gain_reg_num - status->gain_reg_num) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3e08, (gain_reg[0] >> 8));
			set_sync_i2c(&reg[i++], 0x3e09, (gain_reg[0] & 0xff));
		
			set_sync_i2c(&reg[i++], 0x3e12, (gain_reg[1] >> 8));
			set_sync_i2c(&reg[i++], 0x3e13, (gain_reg[1] & 0xff));
			status->last_gain_reg_num = status->gain_reg_num;
		}

		/* set exposure */	
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			exposure_rows[1] = clip_d_word(exposure_rows[1], 2, (short_exp_max_dummy - 10) );	
			exposure_step_short = exposure_rows[1] << 1;			//in the unit of half line
			exposure_step_short = exposure_step_short << 4;					
			set_sync_i2c(&reg[i++], 0x3e22, (exposure_step_short & 0xff0000) >> 16);
			set_sync_i2c(&reg[i++], 0x3e04, (exposure_step_short & 0xff00) >> 8);
			set_sync_i2c(&reg[i++], 0x3e05, exposure_step_short & 0xff);
			status->last_exposure[1] = exp_gain->exposure[1];
			//printf("vts = %d, exposure_rows[1] = %d, exposure_step_short = %d \n ",vts,exposure_rows[1],exposure_step_short);
		}
			
	}
	else{
		i = 0;
		
		
		/* set vts */
		if (abs(status->last_vts - vts) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x320E, vts >> 8);
			set_sync_i2c(&reg[i++], 0x320F, vts & 0xff);
			status->last_vts = vts;
		}
		
		/* set exposure */	
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			exposure_rows[0] = clip_d_word(exposure_rows[0], 1, (vts  - 6));
			exposure_step = exposure_rows[0] << 1;			//in the unit of half line
			exposure_step = exposure_step << 4;
			
			//printf("vts = %d, exposure_rows[0] = %d, exposure_step = %d \n ",vts,exposure_rows[0],exposure_step);

			
			set_sync_i2c(&reg[i++], 0x3e00, (exposure_step & 0xff0000) >> 16);
			set_sync_i2c(&reg[i++], 0x3e01, (exposure_step & 0xff00) >> 8);
			set_sync_i2c(&reg[i++], 0x3e02, exposure_step & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		
		/* set gain */
		if (abs(status->last_gain_reg_num - status->gain_reg_num) > 0.001f) {
			gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] * exp_gain->digital_gain[0],status);
			set_sync_i2c(&reg[i++], 0x3e08, (gain_reg[0] >> 8));
			set_sync_i2c(&reg[i++], 0x3e09, (gain_reg[0] & 0xff));
			status->last_gain_reg_num = status->gain_reg_num;
		}
		//printf("vts=%d, exp[0]=%f, exp[1]=%f\n", vts, exp_gain->exposure[0],exp_gain->exposure[1]);
		//printf("gain_nem=%d, gain_reg[0]=%d, gain_reg[1]=%d\n", status->gain_reg_num,gain_reg[0],gain_reg[1]);

	}
	regs->num = i;
	
	return RTS_ISP_OK;
}


static int sc231h_set_mirror_flip(uint32_t isp_id,
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
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x3221, 0x66);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x3221, 0x06);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x3221, 0x60);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x3221, 0x00);
			break;
	#else
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x3221, 0x00);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x3221, 0x60);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x3221, 0x06);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x3221, 0x66);
			break;
	#endif
	}
	mf_info->regs.num = i;
	

	return RTS_ISP_OK;
}

static int sc231h_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	//int idx = sensor_get_slave_addr_idx();

	//if (idx >= SLAVE_ADDR_NUM)
	//	return -RTS_ISP_EINVAL;

	//real_slave_addr = slave_addr_list[idx];

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

	
	if (id == 0xcb6a)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int sc231h_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}


static const struct rts_isp_sensor_ops sc231h_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc231h",
	.get_info = sc231h_get_info,
	.get_init_info = sc231h_get_init_info,
	.start = sc231h_start,
	.get_exposure_range = sc231h_get_exposure_range,
	.get_tuned_again = sc231h_get_tuned_again,
	.get_tuned_dgain = sc231h_get_tuned_dgain,
	.get_exposure_gain_info = sc231h_get_exposure_gain_info,
	.set_mirror_flip = sc231h_set_mirror_flip,
	.check = sc231h_check,
	.get_slave_addr_num = sc231h_get_slave_addr_num,
};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc231h_ops;
}
