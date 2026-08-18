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
#define SHORT_EXP_SHIFT_MAX 69
//#define SHORT_LSB_EXP_MAX 234
//#define SHORT_EXP_MAX 475
#define SHORT_EXP_MAX 		62
#define PROJECT_FL			1
#define ORIENTATION			0	/* Default sensor mirror and flip mode => 0:default, 1:rotate180 */
#define MAX_GAIN_USAGE		0	/* 0=15.75x, 1=31x */
#define BINNING_MODE		0
#define BINNING_MODE_FPS	1	
/* 
	0=30fps, 1=20fps 
	in order to support binning mode (1284*724), sensor could only work under 20 fps 
*/

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct k306p_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure[2];
	int num;
	struct rts_isp_i2c_reg regs1[3];
};


static struct k306p_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_k306p_fps_info_linear[] = {
#if BINNING_MODE && BINNING_MODE_FPS
	{20.0f, 5760, 172800000},
#else
	{30.0f, 3840, 172800000},
#endif
};

static const struct fps_info g_k306p_fps_info_hdr[] = {
	{15.0f, 3840, 172800000},
};

static struct rts_isp_i2c_reg g_k306p_i2c_init_regs_linear[] = {
	/****system****/
	{0x12,0x60},
	{0x48,0x86},
	{0x48,0x06},
	{0x0E,0x11},
	{0x0F,0x0C},
	{0x10,0x48},
	{0x0C,0x00},
	{0x0D,0xA0},
	{0x57,0x67},
	{0x58,0x1F},
	{0x5F,0x41},
	{0x60,0x20},
	{0x20,0xC0},
	{0x21,0x03},
	{0x22,0xDC},
	{0x23,0x05},
	{0x24,0x84},	//80
	{0x25,0xA4},	//a0
	{0x26,0x52},
	{0x27,0xBD},	//0xbc
	{0x28,0x15},
	{0x29,0x03},
	{0x2A,0xB6},
	{0x2B,0x13},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x6E},
	{0x2F,0x04},
	{0x41,0x04},
	{0x42,0x05},
	{0x47,0x46},
	{0x76,0x80},
	{0x77,0x0C},
	{0x80,0x04},
	{0xAF,0x22},
	{0x46,0x08},
	{0xAA,0x80},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x9E,0xB8},
	{0x6F,0x00},
	{0x6E,0x2C},
	{0x70,0xD9},
	{0x71,0xDD},
	{0x72,0xCC},
	{0x73,0x7A},
	{0x74,0x02},
	{0x78,0x1B},
	{0x89,0x01},
	{0x6B,0x20},
	{0x86,0x40},
	{0xB0,0x02},
	{0xBF,0x01},
	{0x0A,0xC3},
	{0xBF,0x00},
	{0x7F,0x56},
	{0x08,0x10},
	{0x30,0x8D},
	{0x31,0x08},
	{0x32,0x28},
	{0x33,0x5C},
	{0x34,0x38},
	{0x35,0x38},
	{0x3A,0xB6},
	{0x56,0x92},
	{0x59,0x48},
	{0x5A,0x01},
	{0x61,0x18},
	{0x64,0xE0},
	{0x85,0x40},
	{0x8A,0x00},
	{0x91,0x40},
	{0x94,0xE0},
	{0x9B,0x8F},
	{0x9F,0xD5},
	{0xA4,0x87},
	{0xA6,0x02},
	{0xA7,0x80},
	{0xA9,0x4C},
	{0x45,0x09},
	{0x5B,0xA5},
	{0x5C,0x8C},
	{0x5D,0x87},
	{0x5E,0xCE},
	{0x65,0x3B},
	{0x66,0x80},
	{0x67,0x41},
	{0x68,0x00},
	{0x69,0x7C},
	{0x6A,0x2B},
	{0x7A,0xCA},
	{0x8D,0x6F},
	{0x8F,0x94},
	{0xA5,0x0F},
	{0xB7,0x21},
	{0x97,0x20},
	{0x13,0x81},
	{0x96,0x84},
	{0x4A,0x01},
	{0xB1,0x00},
	{0xA1,0x0F},
	{0xB5,0x44},
	{0xA3,0x40},
	{0xBF,0x01},
	{0x03,0x01},
	{0x04,0x80},
	{0x05,0x32},
	{0xBF,0x00},
	{0x50,0x02},
	{0x49,0x40},
	{0x7E,0x4C},
	{0x8C,0xFF},
	{0x8E,0x00},
	{0x8B,0x01},
	{0xBD,0x10},
	{0xA0,0x20},
	{0xBC,0x12},
	{0x82,0x00},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x12,0x20},
	{0x48,0x86},
	{0x48,0x06},
};

static struct rts_isp_i2c_reg g_k306p_i2c_init_regs_hdr[] = {
	
	{0x12,0x68},
	{0x48,0x86},
	{0x48,0x06},
	{0x0E,0x11},
	{0x0F,0x0C},
	{0x10,0x48},
	{0x0C,0x00},
	{0x0D,0xA0},
	{0x57,0x67},
	{0x58,0x1F},
	{0x5F,0x41},
	{0x60,0x20},
	{0x20,0xC0},
	{0x21,0x03},
	{0x22,0xB8},
	{0x23,0x0B},
	{0x24,0x84},	//0x80
	{0x25,0xA4},	//0xA0
	{0x26,0x52},
	{0x27,0xBC},
	{0x28,0x29},
	{0x29,0x03},
	{0x2A,0xB6},
	{0x2B,0x13},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x6E},
	{0x2F,0x04},
	{0x41,0x04},
	{0x42,0x25},
	{0x47,0x46},
	{0x76,0x80},
	{0x77,0x0C},
	{0x80,0x04},
	{0xAF,0x22},
	{0x46,0x0C},
	{0xAA,0x80},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x9E,0xB8},
	{0x6F,0x00},
	{0x6E,0x2C},
	{0x70,0xD9},
	{0x71,0xDD},
	{0x72,0xCC},
	{0x73,0x7A},
	{0x74,0x02},
	{0x78,0x1B},
	{0x89,0x81},
	{0x6B,0x20},
	{0x86,0x40},
	{0xB0,0x02},
	{0xBF,0x01},
	{0x0A,0xC3},
	{0xBF,0x00},
	{0x7F,0x76},
	{0x08,0x18},
	{0x30,0x8D},
	{0x31,0x08},
	{0x32,0x28},
	{0x33,0x5C},
	{0x34,0x38},
	{0x35,0x38},
	{0x3A,0xB6},
	{0x56,0x92},
	{0x59,0x48},
	{0x5A,0x01},
	{0x61,0x18},
	{0x64,0xE0},
	{0x85,0x40},
	{0x8A,0x00},
	{0x91,0x40},
	{0x94,0xE0},
	{0x9B,0x8F},
	{0x9F,0xD5},
	{0xA4,0x87},
	{0xA6,0x02},
	{0xA7,0x80},
	{0xA9,0x4C},
	{0x45,0x09},
	{0x5B,0xA5},
	{0x5C,0x8C},
	{0x5D,0x87},
	{0x5E,0xCE},
	{0x65,0x3B},
	{0x66,0x80},
	{0x67,0x41},
	{0x68,0x00},
	{0x69,0x7C},
	{0x6A,0x2B},
	{0x7A,0xCA},
	{0x8D,0x6F},
	{0x8F,0x94},
	{0xA5,0x0F},
	{0xB7,0x21},
	{0x97,0x20},
	{0x13,0x81},
	{0x96,0x84},
	{0x4A,0x01},
	{0xB1,0x00},
	{0xA1,0x0F},
	{0xB5,0x44},
	{0xA3,0x40},
	{0xBF,0x01},
	{0x03,0x01},
	{0x04,0x80},
	{0x05,0x06},//0x32
	{0xBF,0x00},
	{0x50,0x02},
	{0x49,0x40},
	{0x7E,0x4C},
	{0x8C,0xFF},
	{0x8E,0x00},
	{0x8B,0x01},
	{0xBD,0x10},
	{0xA0,0x20},
	{0xBC,0x12},
	{0x82,0x00},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x07,0x43},
	{0x06,0x0d},//0x23 0x10
	{0x03,0xFF},
	{0x04,0xFF},
	{0xBF,0x01},
	{0x04,0xC0},
	{0xBF,0x00},
	{0x12,0x28},
	{0x48,0x86},
	{0x48,0x06},
};

static struct rts_isp_i2c_reg g_k306p_i2c_init_regs_asic_bin_mode[] = {
#if !BINNING_MODE_FPS
	//K306P_Map#114_No_14543_20260525-R.ini
	{0x12,0x62},
	{0x48,0x86},
	{0x48,0x06},
	{0x0E,0x11},
	{0x0F,0x2C},
	{0x10,0x48},
	{0x0C,0x00},
	{0x0D,0xA0},
	{0x57,0x67},
	{0x58,0x1F},
	{0x5F,0x41},
	{0x60,0x20},
	{0x20,0xC0},
	{0x21,0x03},
	{0x22,0xDC},
	{0x23,0x05},
	{0x24,0x82},
	{0x25,0xD6},	//D4 (724 -> 726)
	{0x26,0x22},
	{0x27,0xBD},
	{0x28,0x09},
	{0x29,0x03},
	{0x2A,0xB6},
	{0x2B,0x13},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x6F},
	{0x2F,0x04},
	{0x41,0x06},
	{0x42,0x05},
	{0x47,0x46},
	{0x76,0x45},
	{0x77,0x06},
	{0x80,0x02},
	{0xAB,0x00},
	{0xAF,0x12},
	{0x50,0x03},
	{0x46,0x0A},
	{0xAA,0xA0},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x9E,0xB8},
	{0x6F,0x00},
	{0x6E,0x2C},
	{0x70,0x6D},
	{0x71,0x6D},
	{0x72,0x68},
	{0x73,0x46},
	{0x74,0x02},
	{0x78,0x1B},
	{0x89,0x01},
	{0x6B,0x20},
	{0x86,0x40},
	{0xB0,0x02},
	{0xBF,0x01},
	{0x0A,0xC3},
	{0xBF,0x00},
	{0x7F,0x56},
	{0x08,0x10},
	{0x30,0x8D},
	{0x31,0x08},
	{0x32,0x28},
	{0x33,0x5C},
	{0x34,0x38},
	{0x35,0x38},
	{0x3A,0xB6},
	{0x56,0x92},
	{0x59,0x48},
	{0x5A,0x01},
	{0x61,0x18},
	{0x64,0xE0},
	{0x85,0x40},
	{0x8A,0x00},
	{0x91,0x40},
	{0x94,0xE0},
	{0x9B,0x8F},
	{0x9F,0xD5},
	{0xA4,0x87},
	{0xA6,0x02},
	{0xA7,0x80},
	{0xA9,0x4C},
	{0x45,0x09},
	{0x5B,0xA5},
	{0x5C,0x8C},
	{0x5D,0x87},
	{0x5E,0xCE},
	{0x65,0x3B},
	{0x66,0x80},
	{0x67,0x41},
	{0x68,0x00},
	{0x69,0x7C},
	{0x6A,0x2B},
	{0x7A,0xCA},
	{0x8D,0x6F},
	{0x8F,0x94},
	{0xA5,0x0F},
	{0xB7,0x21},
	{0x97,0x20},
	{0x13,0x81},
	{0x96,0x84},
	{0x4A,0x01},
	{0xB1,0x00},
	{0xA1,0x0F},
	{0xB5,0x44},
	{0xA3,0x40},
	{0xBF,0x01},
	{0x03,0x01},
	{0x04,0x80},
	{0x05,0x32},
	{0xBF,0x00},
	{0x49,0x40},
	{0x7E,0x4C},
	{0x8C,0xFF},
	{0x8E,0x00},
	{0x8B,0x01},
	{0xBD,0x10},
	{0xA0,0x20},
	{0xBC,0x12},
	{0x82,0x00},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x12,0x22},
	{0x48,0x86},
	{0x48,0x06},
#else
	{0x12,0x62},
	{0x48,0x86},
	{0x48,0x06},
	{0x0E,0x11},
	{0x0F,0x2C},
	{0x10,0x48},
	{0x0C,0x00},
	{0x0D,0xA0},
	{0x57,0x67},
	{0x58,0x1F},
	{0x5F,0x41},
	{0x60,0x20},
	{0x20,0xA0},
	{0x21,0x05},
	{0x22,0xDC},
	{0x23,0x05},
	{0x24,0x82},
	{0x25,0xD6},	//D4 (724 -> 726)
	{0x26,0x22},
	{0x27,0xB6},
	{0x28,0x09},
	{0x29,0x04},
	{0x2A,0xB0},
	{0x2B,0x14},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x6F},
	{0x2F,0x04},
	{0x41,0x06},
	{0x42,0x05},
	{0x47,0x46},
	{0x76,0x45},
	{0x77,0x06},
	{0x80,0x02},
	{0xAB,0x00},
	{0xAF,0x12},
	{0x50,0x03},
	{0x46,0x0A},
	{0xAA,0xA0},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x9E,0xB8},
	{0x6F,0x00},
	{0x6E,0x2C},
	{0x70,0x6D},
	{0x71,0x6D},
	{0x72,0x68},
	{0x73,0x46},
	{0x74,0x02},
	{0x78,0x1B},
	{0x89,0x01},
	{0x6B,0x20},
	{0x86,0x40},
	{0xB0,0x02},
	{0xBF,0x01},
	{0x0A,0xC3},
	{0xBF,0x00},
	{0x7F,0x56},
	{0x08,0x10},
	{0x30,0x8D},
	{0x31,0x08},
	{0x32,0x28},
	{0x33,0x5C},
	{0x34,0x38},
	{0x35,0x38},
	{0x3A,0xB6},
	{0x56,0x92},
	{0x59,0x48},
	{0x5A,0x01},
	{0x61,0x18},
	{0x64,0xE0},
	{0x85,0x40},
	{0x8A,0x00},
	{0x91,0x40},
	{0x94,0xE0},
	{0x9B,0x8F},
	{0x9F,0xD5},
	{0xA4,0x87},
	{0xA6,0x02},
	{0xA7,0x80},
	{0xA9,0x4C},
	{0x45,0x09},
	{0x5B,0xA5},
	{0x5C,0x8C},
	{0x5D,0x87},
	{0x5E,0xCE},
	{0x65,0x3B},
	{0x66,0x80},
	{0x67,0x41},
	{0x68,0x00},
	{0x69,0x7C},
	{0x6A,0x2B},
	{0x7A,0xCA},
	{0x8D,0x6F},
	{0x8F,0x94},
	{0xA5,0x0F},
	{0xB7,0x21},
	{0x97,0x20},
	{0x13,0x81},
	{0x96,0x84},
	{0x4A,0x01},
	{0xB1,0x00},
	{0xA1,0x0F},
	{0xB5,0x44},
	{0xA3,0x40},
	{0xBF,0x01},
	{0x03,0x01},
	{0x04,0x80},
	{0x05,0x32},
	{0xBF,0x00},
	{0x49,0x40},
	{0x7E,0x4C},
	{0x8C,0xFF},
	{0x8E,0x00},
	{0x8B,0x01},
	{0xBD,0x10},
	{0xA0,0x20},
	{0xBC,0x12},
	{0x82,0x00},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x12,0x22},
	{0x48,0x86},
	{0x48,0x06},
#endif
};


#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x40	//0x6e(default, D[0]=D[1]=0)
#define SLAVE_ADDR_1 0x46	//0x8c(D[0]=D[1]=1)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int k306p_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;
	
#if !BINNING_MODE
	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;	
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_k306p_fps_info_linear[0].fps;
	i++;
	info->modes.mode[i].hdr = HDR_MODE;		
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_k306p_fps_info_hdr[0].fps;
#else
	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;	
	info->modes.mode[i].size.w = 1284;
	info->modes.mode[i].size.h = 724;
	info->modes.mode[i].fps = g_k306p_fps_info_linear[0].fps;
#endif

	i++;
	info->modes.num = i;
	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 3000);
#if !PROJECT_FL
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
#else
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 15000);
#endif
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 3000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 3000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *k306p_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_k306p_fps_info_hdr); i++)
			if (fps == g_k306p_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_k306p_fps_info_hdr))
			return NULL;
		return &g_k306p_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_k306p_fps_info_linear); i++)
			if (fps == g_k306p_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_k306p_fps_info_linear))
			return NULL;
		return &g_k306p_fps_info_linear[i];
	}
}

static int k306p_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct k306p_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = k306p_get_fps_info(mode->fps, &mode->hdr);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		printf("k306p_get_init_info HDR_2K_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_k306p_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 2564;
		info->size.h = 1444;
		info->start.x = 0;
		info->start.y = 1;
		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = 3000;
		info->max_vts = 65536;

		status->exp_step = 1e6 * info->hts /info->pclk; /* us */
		//info->exposure_step = status->exp_step;
	} else {
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

	#if !BINNING_MODE
		//info->size.w = 2568;
		//info->size.h = 1448;
		info->size.w = 2564;
		info->size.h = 1444;
		info->start.x = 0;
		info->start.y = 1;
		printf("k306p_get_init_info LINEAR_2K_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_k306p_i2c_init_regs_linear, 0);
	#else
		info->size.w = 1284;
		info->size.h = 726;
		info->start.x = 0;
		info->start.y = 1;
		printf("k306p_get_init_info LINEAR_BINNING_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_k306p_i2c_init_regs_asic_bin_mode, 0);
	#endif
		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = 1500;
		info->max_vts = 65536;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */
		//info->exposure_step = status->exp_step;
	}

	return RTS_ISP_OK;
}

static int k306p_start(uint32_t isp_id)
{
	struct k306p_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;

	return RTS_ISP_OK;
}

static int k306p_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct k306p_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];
	
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = vts * status->exp_step;
		
		//debug("expusre_min = %1.f , expusre_max = %1.f\n", min_exposure[0],max_exposure[0]);
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_exp = vts;
		float define_sensor_short_exp_min;
	
		tmp1 = (uint32_t)(max_exp / (ratio[0] + 1));
		tmp2 = SHORT_EXP_MAX;
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
	
		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
		
		//debug("long_max_exposure_=%f, long_min_exposure=%f\n", max_exposure[0], min_exposure[0]);
		//debug("short_max_exposure_=%f, short_min_exposure=%f\n", max_exposure[1], min_exposure[1]);
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct k306p_status *status)
{
	int wAgainReg;
	if(fAGain>=1.0 && fAGain<2.0){
		wAgainReg = (int)(16.0f*(fAGain-1.0));
	}
	else if(fAGain>=2.0 && fAGain<4.0){
		wAgainReg = (int)(8.0f*(fAGain-2.0) + 16.0);
	}
	else if(fAGain>=4.0 && fAGain<8.0){
		wAgainReg = (int)(4.0f*(fAGain-4.0) + 32.0);
	}
	else if(fAGain>=8.0 && fAGain<16){
		wAgainReg = (int)(2.0f*(fAGain-8.0) + 48.0);
	}
#if(MAX_GAIN_USAGE)
	else if(fAGain>=16.0 && fAGain<32) {
		wAgainReg = (int)((fAGain-16.0) + 64.0);
	}
	else 
		wAgainReg = 0x4f;
#else
	else 
		wAgainReg = 0x3f;
#endif
		
	status->num = wAgainReg;
	return wAgainReg;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	float fAgainReg;
	float ftemp = wAGain;
	if(wAGain>=0 && wAGain<16){
		fAgainReg = (float)(ftemp/16.0 + 1);
	}
	else if(wAGain>=16 && wAGain<32){
		fAgainReg = (float)(ftemp/8.0);
	}
	else if(wAGain>=32 && wAGain<48){
		fAgainReg = (float)(ftemp/4.0 - 4);
	}
	else if(wAGain>=48 && wAGain<64){
		fAgainReg = (float)(ftemp/2.0 - 16);
	}
#if(MAX_GAIN_USAGE)
	else if(wAGain>=64 && wAGain<80){
		fAgainReg = (float)(ftemp - 48);
	}
#endif
	return (fAgainReg);
}

static int k306p_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct k306p_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	

	if (status->hdr == HDR_MODE) {
		gain_reg = get_sensor_gain_reg(again[1], status);
		again[1] = get_sensor_real_gain(gain_reg);
	}

	return RTS_ISP_OK;
}

static int k306p_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct k306p_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	
	status = &g_status[isp_id];
	
	dgain[0] = 1.0f;

	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int k306p_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct k306p_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];

	#if 1
	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	
		vts = exp_gain->vts + 4;
	reg = regs->reg;

	i = 0;

	if (status->hdr == LINEAR_MODE) {

		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			
			//debug("exposure = %d \n" , exposure_rows[0]);
		
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		//set gain 		
		set_sync_i2c(&reg[i++], 0x00, status->num);
		//set vts 	
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);

	}else{

		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			exposure_rows[1] = exp_gain->exposure[1] / status->exp_step + 0.5f;
			if ((exposure_rows[1] & 0xff) > SHORT_EXP_MAX){
			//	set_sync_i2c(&reg[i++], 0x08, (exposure_rows[1] >> 8) & 0x01 );
				set_sync_i2c(&reg[i++], 0x05, SHORT_EXP_MAX);
				set_sync_i2c(&reg[i++], 0x06, SHORT_EXP_SHIFT_MAX); 	
			}
			else{
			//	set_sync_i2c(&reg[i++], 0x08, (exposure_rows[1] >> 8) & 0x01 );
				set_sync_i2c(&reg[i++], 0x05,  exposure_rows[1] & 0xff);
				set_sync_i2c(&reg[i++], 0x06, (exposure_rows[1] & 0xff)+7);
			}
			status->last_exposure[1] = exp_gain->exposure[1];
		}
		
		//debug("exposure L = %d, S = %d \n" ,exposure_rows[0], exposure_rows[1]);

		//set gain 		
		set_sync_i2c(&reg[i++], 0x00, status->num);
		//set vts 	
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
	}
	#endif
	regs->num = i;
		
	debug("et-gain_inf vts= %d\n", vts );

	return RTS_ISP_OK;
}

static int k306p_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	int regtmp;
		
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct k306p_status *status;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	status = &g_status[isp_id];
	
	if(status->hdr == HDR_MODE)
		regtmp = 0x08;
	else
	{
	#if !BINNING_MODE
		regtmp = 0x00;
	#else
		regtmp = 0x02;
	#endif
	}
	
	switch(bySnrImgDir)
	{
	#if (ORIENTATION == 1)
		case 0: 	//normal
		default:
			regtmp = regtmp | 0x00;
			break;
		case 1: 	// VFlip
			regtmp = regtmp | 0x10;
			break;
		case 2: 	// Mirror
			regtmp = regtmp | 0x20;
			break;
		case 3: 	// Rotate
			regtmp = regtmp | 0x30;
			break;
	#else
		case 0: 	//normal
		default:
			regtmp = regtmp | 0x30;
			break;
		case 1: 	// VFlip
			regtmp = regtmp | 0x20;
			break;
		case 2: 	// Mirror
			regtmp = regtmp | 0x10;
			break;
		case 3: 	// Rotate
			regtmp = regtmp | 0x00;
			break;
	#endif
	}
	if(status->hdr == HDR_MODE)
		regtmp &= 0xEF;
		
    set_sync_i2c(&reg[i++], 0x12, regtmp);
	mf_info->regs.num = i;
	//printf("[%s]status->hdr:%d,reg=0x%x\r",__FUNCTION__,status->hdr,regtmp);
	return RTS_ISP_OK;
}

static int k306p_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();

	reg.addr = 0x0A;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x0B;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id |= reg.data;
    rts_isp_sensor_access_unprepare();
		
	if (id == 0x0860)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int k306p_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops k306p_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "k306p",
	.get_info = k306p_get_info,
	.get_init_info = k306p_get_init_info,
	.start = k306p_start,
	.get_exposure_range = k306p_get_exposure_range,
	.get_tuned_again = k306p_get_tuned_again,
	.get_tuned_dgain = k306p_get_tuned_dgain,
	.get_exposure_gain_info = k306p_get_exposure_gain_info,
	.set_mirror_flip = k306p_set_mirror_flip,
	.check = k306p_check,
	.get_slave_addr_num = k306p_get_slave_addr_num,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &k306p_ops;
}

