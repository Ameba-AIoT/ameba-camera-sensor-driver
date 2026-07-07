/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2023 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <platform_conf.h>
#include <math.h>
#include <isp_reg_lib.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"


// #define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define AE_MAX_SHORT_EXP_BASE 108									/* VHDR mode min interval between long exposure and short exposure frame (long exp + short exp) */
#define SENSOR_GAIN_FULL 1
#if (SENSOR_GAIN_FULL == 1)
#define ANALOG_GAIN_MAX_RATIO (float)75.828125f						/* Max sensor gain ratio => 4853/64 = 75.828125x */
#else
#define ANALOG_GAIN_MAX_RATIO (float)16.f							/* Max sensor gain ratio => 1024/64 = 16.0x */
#endif
#define ORIENTATION 0												/* Default sensor mirror and flip mode => 0:default, 1:rotate180 */
#define SENSOR_MIN_EXP_LINE 8.0
#define SENSOR_MIN_EXP_LINE_VHDR_OFF 1.0


struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct gc4663_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
	uint8_t gain_reg_num;
	uint8_t last_gain_reg_num;
	uint8_t fusion_mode;
	uint16_t short_exp_mode_exit_thd;
};

struct gc4663_gain_config {
	uint8_t reg_02b3;
	uint8_t reg_02b4;
	uint8_t reg_02b8;
	uint8_t reg_02b9;
	uint8_t reg_0515;
	uint8_t reg_0519;
	uint8_t reg_02d9;
	uint16_t gain_value;
};

static struct gc4663_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_gc4663_fps_info_linear[] = {
/*   FPS    HTS       VTS     PCLK      */
	{30.0, (3200/2), (1500), (144000000)},
};

/* HDR frame rate table*/
static const struct fps_info g_gc4663_fps_info_hdr[] = {
/*   FPS    HTS       VTS       PCLK      */
	{20.0, (1437*2*2), (1600), (184000000)},
};

static struct rts_isp_i2c_reg g_gc4663_i2c_init_regs_linear[] = {
	/* ---------Linear-------- */
	/*
	Resolution: 2560x1440
	Frame rate: 30fps
	MCLK: 24MHz
	MIPI CLK: 648Mbps
	MIPI: 2Lane
	Bit depth: 10bit
	*/

	{0x03fe, 0xf0},
	{0x03fe, 0x00},
	{0x0317, 0x00},
	{0x0320, 0x77},
	{0x0324, 0xc8},
	{0x0325, 0x06},
	{0x0326, 0x6c},
	{0x0327, 0x03},
	{0x0334, 0x40},
	{0x0336, 0x6c},
	{0x0337, 0x82},
	{0x0315, 0x25},
	{0x031c, 0xc6},
	{0x0287, 0x18},
	{0x0084, 0x00},
	{0x0087, 0x50},
	{0x029d, 0x08},
	{0x0290, 0x00},
	{0x0340, 0x05},
	{0x0341, 0xdc},
	{0x0345, 0x06},
	{0x034b, 0xb0},
	{0x0352, 0x08},
	{0x0354, 0x08},
	{0x02d1, 0xe0},
	{0x0223, 0xf2},
	{0x0238, 0xa4},
	{0x02ce, 0x7f},
	{0x0232, 0xc4},
	{0x02d3, 0x05},
	{0x0243, 0x06},
	{0x02ee, 0x30},
	{0x026f, 0x70},
	{0x0257, 0x09},
	{0x0211, 0x02},
	{0x0219, 0x09},
	{0x023f, 0x2d},
	{0x0518, 0x00},
	{0x0519, 0x01},
	{0x0515, 0x08},
	{0x02d9, 0x3f},
	{0x02da, 0x02},
	{0x02db, 0xe8},
	{0x02e6, 0x20},
	{0x021b, 0x10},
	{0x0252, 0x22},
	{0x024e, 0x22},
	{0x02c4, 0x01},
	{0x021d, 0x17},
	{0x024a, 0x01},
	{0x02ca, 0x02},
	{0x0262, 0x10},
	{0x029a, 0x20},
	{0x021c, 0x0e},
	{0x0298, 0x03},
	{0x029c, 0x00},
	{0x027e, 0x14},
	{0x02c2, 0x10},
	{0x0540, 0x20},
	{0x0546, 0x01},
	{0x0548, 0x01},
	{0x0544, 0x01},
	{0x0242, 0x1b},
	{0x02c0, 0x1b},
	{0x02c3, 0x20},
	{0x02e4, 0x20},
	{0x022e, 0x00},
	{0x027b, 0x3f},
	{0x0269, 0x0f},
	{0x02d2, 0x40},
	{0x027c, 0x08},
	{0x023a, 0x2e},
	{0x0245, 0xce},
	{0x0530, 0x20},
	{0x0531, 0x02},
	{0x0228, 0x50},
	{0x02ab, 0x00},
	{0x0250, 0x00},
	{0x0221, 0x50},
	{0x02ac, 0x00},
	{0x02a5, 0x02},
	{0x0260, 0x0b},
	{0x0216, 0x04},
	{0x0299, 0x1C},
	{0x02bb, 0x0d},
	{0x02a3, 0x02},
	{0x02a4, 0x02},
	{0x021e, 0x02},
	{0x024f, 0x08},
	{0x028c, 0x08},
	{0x0532, 0x3f},
	{0x0533, 0x02},
	{0x0277, 0xc0},
	{0x0276, 0xc0},
	{0x0239, 0xc0},
	{0x0202, 0x05},
	{0x0203, 0xd0},
	{0x0205, 0xc0},
	{0x02b0, 0x68},
	{0x0002, 0xa9},
	{0x0004, 0x01},
	{0x021a, 0x98},
	{0x0266, 0xa0},
	{0x0020, 0x01},
	{0x0021, 0x03},
	{0x0022, 0x00},
	{0x0023, 0x04},
	{0x0342, 0x06},
	{0x0343, 0x40},
	{0x03fe, 0x10},
	{0x03fe, 0x00},
	{0x0106, 0x78},
	{0x0108, 0x0c},
	{0x0114, 0x01},
	{0x0115, 0x10},
	{0x0180, 0x46},
	{0x0181, 0x30},
	{0x0182, 0x05},
	{0x0185, 0x01},
	{0x03fe, 0x10},
	{0x03fe, 0x00},
	{0x0100, 0x09},					/* stream on */
#if (ORIENTATION == 1)
	{0x0101,0x03},
#endif
	{0x000f, 0x00},

	/* otp  */
	{0x0080, 0x02},
	{0x0097, 0x0a},
	{0x0098, 0x10},
	{0x0099, 0x05},
	{0x009a, 0xb0},
	{0x0317, 0x08},
	{0x0a67, 0x80},
	{0x0a70, 0x03},
	{0x0a82, 0x00},
	{0x0a83, 0x10},
	{0x0a80, 0x2b},
	{0x05be, 0x00},
	{0x05a9, 0x01},
	{0x0313, 0x80},
	{0x05be, 0x01},
	{0x0317, 0x00},
	{0x0a67, 0x00},
};

static struct rts_isp_i2c_reg g_gc4663_i2c_init_regs_hdr[] = {
	/* ---------VHDR-------- */
	/*
	Resolution: 2560x1440
	Frame rate: 20fps
	MCLK: 24MHz
	MIPI CLK: 996Mbps (184MHz)
	MIPI: 2Lane
	Bit depth: 10bit
	*/

	{0x03fe, 0xf0},
	{0x03fe, 0x00},
	{0x0317, 0x00},
	{0x0320, 0x77},
	{0x0324, 0xc4},
	{0x0326, 0x2e},
	{0x0327, 0x03},
	{0x0321, 0x10},
	{0x0314, 0x50},
	{0x0334, 0x40},
	{0x0335, 0xd1},
	{0x0336, 0x53},
	{0x0337, 0x82},
	{0x0315, 0x33},
	{0x031c, 0xce},
	{0x0287, 0x18},
	{0x0084, 0x00},
	{0x0087, 0x50},
	{0x029d, 0x08},
	{0x0290, 0x00},
	{0x0340, 0x06},
	{0x0341, 0x40},
	{0x0345, 0x06},
	{0x034b, 0xb0},
	{0x0352, 0x08},
	{0x0354, 0x08},
	{0x02d1, 0xc0},
	{0x023c, 0x04},
	{0x0238, 0xb4},
	{0x0223, 0xfb},
	{0x0232, 0xc4},
	{0x0279, 0x53},
	{0x02d3, 0x01},
	{0x0243, 0x06},
	{0x02ce, 0xbf},
	{0x02ee, 0x30},
	{0x026f, 0x70},
	{0x0257, 0x09},
	{0x0211, 0x02},
	{0x0219, 0x09},
	{0x023f, 0x2d},
	{0x0518, 0x00},
	{0x0519, 0x14},
	{0x0515, 0x18},
	{0x02d9, 0x50},
	{0x02da, 0x02},
	{0x02db, 0xe8},
	{0x02e6, 0x20},
	{0x021b, 0x10},
	{0x0252, 0x22},
	{0x024e, 0x22},
	{0x02c4, 0x01},
	{0x021d, 0x17},
	{0x024a, 0x01},
	{0x02ca, 0x02},
	{0x0262, 0x10},
	{0x029a, 0x20},
	{0x021c, 0x0e},
	{0x0298, 0x03},
	{0x029c, 0x00},
	{0x027e, 0x14},
	{0x02c2, 0x10},
	{0x0540, 0x20},
	{0x0546, 0x01},
	{0x0548, 0x01},
	{0x0544, 0x01},
	{0x0242, 0x36},
	{0x02c0, 0x36},
	{0x02c3, 0x4d},
	{0x02e4, 0x10},
	{0x022e, 0x00},
	{0x027b, 0x3f},
	{0x0269, 0x0f},
	{0x02d2, 0x40},
	{0x027c, 0x08},
	{0x023a, 0x2e},
	{0x0245, 0xce},
	{0x0530, 0x3f},
	{0x0531, 0x02},
	{0x0228, 0x50},
	{0x02ab, 0x00},
	{0x0250, 0x00},
	{0x0221, 0x50},
	{0x02ac, 0x00},
	{0x02a5, 0x02},
	{0x0260, 0x0b},
	{0x0216, 0x04},
	{0x0299, 0x1C},
	{0x021a, 0x98},
	{0x0266, 0xd0},
	{0x0020, 0x01},
	{0x0021, 0x05},
	{0x0022, 0xc0},
	{0x0023, 0x08},

	/* tony_ add */
	{0x0098, 0x10},
	{0x009a, 0xb0},
	{0x02bb, 0x0d},
	{0x02a3, 0x02},
	{0x02a4, 0x02},
	{0x021e, 0x02},
	{0x024f, 0x08},
	{0x028c, 0x08},
	{0x0532, 0x3f},
	{0x0533, 0x02},
	{0x0277, 0x70},					/* tx_width */
	{0x0276, 0xc0},
	{0x0239, 0xc0},
	{0x0200, 0x00},
	{0x0201, 0x50},
	{0x0202, 0x05},
	{0x0203, 0x00},
	{0x0205, 0xc0},
	{0x02b0, 0x68},
	{0x000f, 0x00},
	{0x0006, 0xe0},
	{0x0002, 0xa9},
	{0x0004, 0x01},
	{0x0060, 0x40},
	{0x0218, 0x12},
	{0x0342, 0x05},
	{0x0343, 0x9d},
	{0x03fe, 0x10},
	{0x03fe, 0x00},
	{0x0106, 0x78},
	{0x0107, 0x89},
	{0x0108, 0x0c},
	{0x0114, 0x01},
	{0x0115, 0x10},
	{0x0180, 0x4f},
	{0x0181, 0x30},
	{0x0182, 0x05},
	{0x0185, 0x01},
	{0x03fe, 0x10},
	{0x03fe, 0x00},
	{0x0100, 0x09},
#if (ORIENTATION == 1)
	{0x0101,0x03},
#endif

	/* otp */
	{0x0080, 0x02},
	{0x0097, 0x0a},
	{0x0098, 0x10},
	{0x0099, 0x05},
	{0x009a, 0xb0},
	{0x0317, 0x08},
	{0x0a67, 0x80},
	{0x0a70, 0x03},
	{0x0a82, 0x00},
	{0x0a83, 0x10},
	{0x0a80, 0x2b},
	{0x05be, 0x00},
	{0x05a9, 0x01},
	{0x0313, 0x80},
	{0x05be, 0x01},
	{0x0317, 0x00},
	{0x0a67, 0x00},
};

#if (SENSOR_GAIN_FULL == 1)
static struct gc4663_gain_config g_gc4663_gain_config[] = {
/*   Sensor REG addrss												*/
/*   (HEX) (HEX) (HEX) (HEX) (HEX) (HEX) (HEX)						*/
/*	 2B3,  2B4,  2B8,  2B9,  515,  519,  2D9,  gain value(1x = 64)	*/
	{0x00, 0x00, 0x01, 0x00, 0x30, 0x28, 0x66, 64},
	{0x20, 0x00, 0x01, 0x0B, 0x30, 0x2a, 0x68, 75},
	{0x01, 0x00, 0x01, 0x19, 0x30, 0x27, 0x65, 89},
	{0x21, 0x00, 0x01, 0x2A, 0x30, 0x29, 0x67, 106},
	{0x02, 0x00, 0x02, 0x00, 0x30, 0x27, 0x65, 128},
	{0x22, 0x00, 0x02, 0x17, 0x30, 0x29, 0x67, 151},
	{0x03, 0x00, 0x02, 0x33, 0x30, 0x28, 0x66, 179},
	{0x23, 0x00, 0x03, 0x14, 0x30, 0x2a, 0x68, 212},
	{0x04, 0x00, 0x04, 0x00, 0x30, 0x2a, 0x68, 256},
	{0x24, 0x00, 0x04, 0x2F, 0x30, 0x2b, 0x69, 303},
	{0x05, 0x00, 0x05, 0x26, 0x30, 0x2c, 0x6A, 358},
	{0x25, 0x00, 0x06, 0x28, 0x30, 0x2e, 0x6C, 424},
	{0x06, 0x00, 0x08, 0x00, 0x30, 0x2f, 0x6D, 512},
	{0x26, 0x00, 0x09, 0x1E, 0x30, 0x31, 0x6F, 606},
	{0x46, 0x00, 0x0B, 0x0C, 0x30, 0x34, 0x72, 716},
	{0x66, 0x00, 0x0D, 0x11, 0x30, 0x37, 0x75, 849},
	{0x0e, 0x00, 0x10, 0x00, 0x30, 0x3a, 0x78, 1024},
	{0x2e, 0x00, 0x12, 0x3D, 0x30, 0x3e, 0x7C, 1213},
	{0x4e, 0x00, 0x16, 0x19, 0x30, 0x41, 0x7F, 1433},
	{0x6e, 0x00, 0x1A, 0x22, 0x30, 0x45, 0x83, 1698},
	{0x1e, 0x00, 0x20, 0x00, 0x30, 0x49, 0x87, 2048},
	{0x3e, 0x00, 0x25, 0x3A, 0x30, 0x4d, 0x8B, 2426},
	{0x5e, 0x00, 0x2C, 0x33, 0x30, 0x53, 0x91, 2867},
	{0x7e, 0x00, 0x35, 0x05, 0x30, 0x5a, 0x98, 3397},
	{0x9e, 0x00, 0x40, 0x00, 0x30, 0x60, 0x9E, 4096},
	{0xbe, 0x00, 0x4B, 0x35, 0x30, 0x67, 0xA5, 4853},
};
#else
static struct gc4663_gain_config g_gc4663_gain_config[] = {
/*   Sensor REG addrss												*/
/*   (HEX) (HEX) (HEX) (HEX) (HEX) (HEX) (HEX)						*/
/*	 2B3,  2B4,  2B8,  2B9,  515,  519,  2D9,  gain value(1x = 64)	*/
	{0x00, 0x00, 0x01, 0x00, 0x30, 0x28, 0x66, 64},
	{0x20, 0x00, 0x01, 0x0B, 0x30, 0x2a, 0x68, 75},
	{0x01, 0x00, 0x01, 0x19, 0x30, 0x27, 0x65, 89},
	{0x21, 0x00, 0x01, 0x2A, 0x30, 0x29, 0x67, 106},
	{0x02, 0x00, 0x02, 0x00, 0x30, 0x27, 0x65, 128},
	{0x22, 0x00, 0x02, 0x17, 0x30, 0x29, 0x67, 151},
	{0x03, 0x00, 0x02, 0x33, 0x30, 0x28, 0x66, 179},
	{0x23, 0x00, 0x03, 0x14, 0x30, 0x2a, 0x68, 212},
	{0x04, 0x00, 0x04, 0x00, 0x30, 0x2a, 0x68, 256},
	{0x24, 0x00, 0x04, 0x2F, 0x30, 0x2b, 0x69, 303},
	{0x05, 0x00, 0x05, 0x26, 0x30, 0x2c, 0x6A, 358},
	{0x25, 0x00, 0x06, 0x28, 0x30, 0x2e, 0x6C, 424},
	{0x06, 0x00, 0x08, 0x00, 0x30, 0x2f, 0x6D, 512},
	{0x26, 0x00, 0x09, 0x1E, 0x30, 0x31, 0x6F, 606},
	{0x46, 0x00, 0x0B, 0x0C, 0x30, 0x34, 0x72, 716},
	{0x66, 0x00, 0x0D, 0x11, 0x30, 0x37, 0x75, 849},
	{0x0e, 0x00, 0x10, 0x00, 0x30, 0x3a, 0x78, 1024},
};
#endif

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x29	//0x52(ID_SEL=0,default)
#define SLAVE_ADDR_1 0x10	//0x20(ID_SEL=1)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int gc4663_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
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
	info->modes.mode[i].fps = g_gc4663_fps_info_linear[0].fps;
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_gc4663_fps_info_hdr[0].fps;			//@MLCK=24MHz
	i++;

	info->modes.num = i;
	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *gc4663_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_gc4663_fps_info_hdr); i++)
			if (fps <= g_gc4663_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_gc4663_fps_info_hdr))
			return NULL;

		return &g_gc4663_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc4663_fps_info_linear); i++)
			if (fps <= g_gc4663_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_gc4663_fps_info_linear))
			return NULL;

		return &g_gc4663_fps_info_linear[i];
	}
}


static int gc4663_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc4663_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc4663_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		debug("hdr line 2to1 mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_gc4663_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x6;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 2568;
		info->size.h = 1448;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts;
		info->min_vts = status->min_vts = fps_info->vts;
		info->pclk = fps_info->clk;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / 2 / info->pclk; /* us */
	} else {
		debug("linear mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_gc4663_i2c_init_regs_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x6;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2560;
		info->size.h = 1440;
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

static int gc4663_start(uint32_t isp_id)
{
	struct gc4663_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;

	return RTS_ISP_OK;
}

static int gc4663_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc4663_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 32) * status->exp_step;

		debug("max_exposure = %f, min_exposure = %f\n", max_exposure[0], min_exposure[0]);
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_long_exp = vts - AE_MAX_SHORT_EXP_BASE;
		float define_sensor_short_exp_min;

		// Sensor exposure formula
		// short exposure <= vb ,vb = frame_length(VTS) - window_height(sensor actually output = 1456) - 20 - 16
		// long exposure + short exposure<= framelength => long exposure <= framelength - short exposure
		// short expousre line(time) = interval between long and short exposure frame.

		tmp1 = AE_MAX_SHORT_EXP_BASE;
		tmp2 = (uint32_t)(max_long_exp / (ratio[0] + 1));
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;

		if (status->fusion_mode)
			define_sensor_short_exp_min = SENSOR_MIN_EXP_LINE_VHDR_OFF;
		else
			define_sensor_short_exp_min = SENSOR_MIN_EXP_LINE;

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = define_sensor_short_exp_min * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];

	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc4663_status *status)
{
	uint16_t sen_gain = (uint16_t)(fgain * 64.f);
	int i;

	if (sen_gain >= (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f)) {
		sen_gain = (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f);
		status->gain_reg_num = (uint8_t)(ARRAY_SIZE(g_gc4663_gain_config) - 1);
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc4663_gain_config) - 1; i++) {
			if (sen_gain >= g_gc4663_gain_config[i].gain_value &&
			    sen_gain < g_gc4663_gain_config[i + 1].gain_value) {
				sen_gain = g_gc4663_gain_config[i].gain_value;
				status->gain_reg_num = i;
				break;
			}
		}
	}
	debug("Gain ratio_=%f, gain reg num=%d\n", fgain, status->gain_reg_num);

	return sen_gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return (float)(reg_value / 64.f);
}

static int gc4663_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc4663_status *status;

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

static int gc4663_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc4663_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int gc4663_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t frame_length, sen_vts_limit;
	uint16_t exp_lines[2];
	uint16_t min_short_exp;
	struct gc4663_status *status;
	struct rts_isp_sync_reg *reg;
	const struct fps_info *fps_info;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	reg = regs->reg;
	if (status->hdr == LINEAR_MODE) {
		frame_length = exp_gain->vts;

		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0340, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x0341, frame_length & 0xff);

			status->last_vts = frame_length;
		}

		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
			set_sync_i2c(&reg[i++], 0x0202, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x0203, exp_lines[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
	} else {
		for (i = 0; i < 2; i++) {
			exp_lines[i] = (exp_gain->exposure[i] /
					       status->exp_step + 0.5f);
		}

		if (status->fusion_mode)
			min_short_exp = SENSOR_MIN_EXP_LINE_VHDR_OFF;
		else
			min_short_exp = SENSOR_MIN_EXP_LINE;

		if (status->short_exp_mode_exit_thd > 512) {
			float exit_thd = status->short_exp_mode_exit_thd / 256.0;
			if (status->fusion_mode &&
			    exp_lines[1] >
				    (int) SENSOR_MIN_EXP_LINE *
					    exit_thd) {
				status->fusion_mode = VHDR_EXP_MODE_MULTIPLE;
			} else if (exp_lines[1] <= (int) SENSOR_MIN_EXP_LINE) {
				status->fusion_mode = VHDR_EXP_MODE_SINGLE;
			}
		}

		exp_lines[1] = (exp_lines[1] < min_short_exp) ? min_short_exp :
						exp_lines[1];

		exp_lines[0] = (exp_gain->exposure[0] / exp_gain->exposure[1]) *
			       exp_lines[1];

		if ((exp_lines[1] + exp_lines[0]) > exp_gain->vts)
			frame_length = exp_lines[1] + exp_lines[0];
		else
			frame_length = exp_gain->vts;

		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0340, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x0341, frame_length & 0xff);

			status->last_vts = frame_length;
		}

		/* set exposure */
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0200, exp_lines[1] >> 8);
			set_sync_i2c(&reg[i++], 0x0201, exp_lines[1] & 0xff);

			status->last_exposure[1] = exp_gain->exposure[1];
		}

		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0202, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x0203, exp_lines[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
	}

	/* set gain */
	if (abs(status->last_gain_reg_num - status->gain_reg_num) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x02b3,
					g_gc4663_gain_config[status->gain_reg_num].reg_02b3);
		set_sync_i2c(&reg[i++], 0x02b4,
					g_gc4663_gain_config[status->gain_reg_num].reg_02b4);
		set_sync_i2c(&reg[i++], 0x02b8,
					g_gc4663_gain_config[status->gain_reg_num].reg_02b8);
		set_sync_i2c(&reg[i++], 0x02b9,
					g_gc4663_gain_config[status->gain_reg_num].reg_02b9);
		set_sync_i2c(&reg[i++], 0x0515,
					g_gc4663_gain_config[status->gain_reg_num].reg_0515);
		set_sync_i2c(&reg[i++], 0x0519,
					g_gc4663_gain_config[status->gain_reg_num].reg_0519);
		set_sync_i2c(&reg[i++], 0x02d9,
					g_gc4663_gain_config[status->gain_reg_num].reg_02d9);

		status->last_gain_reg_num = status->gain_reg_num;
	}

	regs->num = i;

	return RTS_ISP_OK;
}

static int gc4663_get_short_exp_mode(uint32_t isp_id)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct gc4663_status *status = &g_status[isp_id];
	return status->fusion_mode;
}

static int gc4663_set_short_exp_exit_thd(uint32_t isp_id, uint16_t exit_thd)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct gc4663_status *status = &g_status[isp_id];

	if (status->fusion_mode && exit_thd <= 512) {
		status->fusion_mode = VHDR_EXP_MODE_MULTIPLE;
	}
	status->short_exp_mode_exit_thd = exit_thd;
	return 0;
}

static int gc4663_set_mirror_flip(uint32_t isp_id,
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
			set_sync_i2c(&reg[i++], 0x0101, 0x00);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x0101, 0x01);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x0101, 0x02);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x0101, 0x03);
		break;
	#else
		case 0: // Normal
		default:
			set_sync_i2c(&reg[i++], 0x0101, 0x03);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x0101, 0x02);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x0101, 0x01);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x0101, 0x00);
		break;
	#endif
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int gc4663_check(uint32_t isp_id)
{
	/* Notice: gc4663 chip id is same with gc4653 */
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x03f0;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x03f1;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	if (id == 0x4653)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int gc4023_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops gc4663_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc4663",
	.get_info = gc4663_get_info,
	.get_init_info = gc4663_get_init_info,
	.start = gc4663_start,
	.get_exposure_range = gc4663_get_exposure_range,
	.get_tuned_again = gc4663_get_tuned_again,
	.get_tuned_dgain = gc4663_get_tuned_dgain,
	.get_exposure_gain_info = gc4663_get_exposure_gain_info,
	.set_mirror_flip = gc4663_set_mirror_flip,
	.set_short_exp_exit_thd = gc4663_set_short_exp_exit_thd,
	.get_short_exp_mode = gc4663_get_short_exp_mode,
	.check = gc4663_check,
	.get_slave_addr_num = gc4023_get_slave_addr_num,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc4663_ops;
}

