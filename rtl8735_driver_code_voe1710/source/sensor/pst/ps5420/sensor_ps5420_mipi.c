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

#define ORIENTATION 0	//0=default, 1=rotate180
#define SENSOR_HDR 0
#define PROJECT_PARROT	0
struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ps5420_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

static struct ps5420_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ps5420_fps_info_asic[] = {
	//{30.0f, 2700, 160000000},
#if (SENSOR_HDR == 0)
	{30.0f, 2828, 168000000},
#else
	{30.0f, 2828, 168000000},
#endif
};

static struct rts_isp_i2c_reg g_ps5420_i2c_init_regs_asic[] = {
	//PS313B01_5420_1944x1944x30fps_2Lane_RAW10_840Mbps_noImgSyn_20190408_B04A.asc
	{0xEF, 0x05},
	{0x0F, 0x00},
	{0x43, 0x02},
	{0x44, 0x00},//T_pll_enh=0
	{0xED, 0x01},
	{0xEF, 0x01},
	{0xF5, 0x01},
	{0x09, 0x01},
	{0xEF, 0x00},
	{0x10, 0x80},//Cmd_BYTECLK_InvSel=0 for PS308
	{0x11, 0x80},//GatedAllClk enable
	{0x35, 0x01},
	{0x36, 0x1E},
	{0x37, 0x1E},
	{0x38, 0xE0},
	{0x60, 0x58},
	{0x61, 0xE4},
	{0x62, 0x39},
	{0x69, 0x10},
	{0x6A, 0x40},
	{0x85, 0xB0},
	{0x98, 0x02},
	{0x9E, 0x00},
	{0xA0, 0x02},
	{0xA2, 0x0A},
	{0xD8, 0x10},
	{0xDF, 0x24},
	{0xE2, 0x05},
	{0xE3, 0x24},
	{0xE6, 0x05},
	{0xF3, 0xB0},//B04A: Version
	{0xF8, 0x4A},//B04A: Version
	{0xED, 0x01},
	{0xEF, 0x01},
	{0x05, 0x0B},
	{0x0D, 0x02},//NY min=2
#if (ORIENTATION == 1)
	{0x1B, 0x8A},//Rotate
	{0x1C, 0x2F},
	{0x1D, 0x87},
#endif
	{0x2A, 0x74},
	{0x37, 0xBA},
	{0x39, 0xC2},
	{0x3E, 0x21},
	{0x3F, 0x32},
	{0x40, 0xC2},//B03A: F4->C2
	{0x41, 0x14},//B03A: 13->14
	{0x42, 0xF4},
	{0x43, 0x2E},//B03A: FC->2E
	{0x51, 0x28},
	{0x5C, 0x1E},
	{0x5D, 0x0A},
	{0x68, 0x00},
	{0x69, 0x00},
	{0x75, 0x74},
	{0x8F, 0x08},
	{0xA3, 0x00},//Cmd_WOI_VOffset=22
	{0xA4, 0x16},//Cmd_WOI_VOffset=22
	{0xA5, 0x07},//Cmd_WOI_VSize=1944
	{0xA6, 0x9C},//Cmd_WOI_VSize=1948
	{0xA7, 0x01},//Cmd_WOI_HOffset=332
	{0xA8, 0x4C},//Cmd_WOI_HOffset=332
	{0xA9, 0x07},//Cmd_WOI_HSize=1944
	{0xAA, 0xA0},//Cmd_WOI_HSize=1952
	{0xAB, 0x01},
	{0xAE, 0x50},
	{0xB0, 0x50},
	{0xB3, 0x07},
	{0xC6, 0x10},
	{0xC9, 0x55},
	{0xCE, 0x30},
	{0xD0, 0x02},
	{0xD1, 0x60},
	{0xD3, 0x01},
	{0xD4, 0x04},
	{0xD5, 0x61},
	{0xD8, 0xA0},
	{0xDD, 0x42},
	{0xE2, 0x0A},
	{0xF0, 0x9D},
	{0xF1, 0x19}, //16
	{0xF2, 0x26}, //26
	{0xF3, 0x0C},
	{0xF5, 0x19},
	{0x09, 0x01},
	{0xEF, 0x02},
	{0x2E, 0x04},
	{0x33, 0x84},
	{0x3C, 0xFA},
	{0x4E, 0x02},
	{0xED, 0x01},
	{0xEF, 0x05},
	{0x06, 0x64},//RAW10
	{0x09, 0x09},
	{0x0A, 0x05},
	{0x0D, 0x5E},
	{0x0E, 0x01},
	{0x0F, 0x00},//MIPI CSI disable
	{0x10, 0x02},//2Lane
	{0x11, 0x01},
	{0x15, 0x07},
	{0x17, 0x06},//Update from James.Yang 2023.01.17
	{0x18, 0x05},
	{0x3B, 0x00},
	{0x40, 0x19},//16
	{0x41, 0x28},//1D
	{0x43, 0x02},
	//{0x43, 0x0A},
	{0x44, 0x01},
	{0x49, 0x01},
	{0x4F, 0x01},
	{0x5B, 0x10},//00, B04A, Reset_by_Vsync_En=1
	{0x94, 0x04},
	//{0xB0, 0x01},
	{0xB0, 0x00},
	{0xED, 0x01},
	{0xEF, 0x06},
	{0x00, 0x0C},
	{0x02, 0x13},
	{0x06, 0x02},
	{0x09, 0x02},
	{0x0A, 0x15},
	{0x0B, 0x90},
	{0x0C, 0x90},
	{0x0D, 0x90},
	{0x0F, 0x1B},
	{0x10, 0x20},
	{0x11, 0x1B},
	{0x12, 0x20},
	{0x18, 0x40},
	{0x1A, 0x40},
	{0x28, 0x03},
	{0x2B, 0x20},
	{0x2D, 0x00},
	{0x2E, 0x20},
	{0x2F, 0x20},
	{0x4A, 0x40},
	{0x4B, 0x40},
	{0x98, 0x06}, //LTM bypass, LTM_EnH=0
	{0x99, 0x23},
	{0x9E, 0x42},
	{0x9F, 0x44}, // Cmd_LTM_LThd[4:0]=8
	{0xF1, 0x01},
	{0xEF, 0x05},
	{0x3B, 0x00},//R_Cmd_Gated_MIPI_Clk=0
	{0xED, 0x01},
	{0xEF, 0x01},
	{0x02, 0xFB},//ResetTG
	{0x09, 0x01},
	{0xEF, 0x00},
	{0x11, 0x00},//GatedAllClk disable, this command move to before MIPI CSI enable(avoid LTM on display abnormal)
	//{0xDL, 0x2 ],
	//{0xEF, 0x05],
	//{0x0F, 0x01],//MIPI CSI enable
	//{0xED, 0x01],
};

static struct rts_isp_i2c_reg g_ps5420_i2c_init_regs2_asic[] = {
	{0xEF, 0x05},
	{0x0F, 0x01},//MIPI CSI enable
	{0xED, 0x01},
};

static struct rts_isp_i2c_reg g_ps5420_HDR_i2c_init_regs_asic[] = {
	//PS313B01_5420_1944x1944x30fps_2Lane_RAW10_840Mbps_20190731_B05A
	{0xEF, 0x05},
	{0x0F, 0x00},
	{0x43, 0x02},
	{0x44, 0x00},//T_pll_enh=0
	{0xED, 0x01},
	{0xEF, 0x01},
	{0xF5, 0x01},
	{0x09, 0x01},
	{0xEF, 0x00},
	{0x10, 0x80},//Cmd_BYTECLK_InvSel=0 for PS308
	{0x11, 0x80},//GatedAllClk enable
	{0x35, 0x01},
	{0x36, 0x0F},
	{0x37, 0x0F},
	{0x38, 0xE0},
	{0x5F, 0xC2},
	{0x60, 0x2A}, //black inversion 20190603
	{0x61, 0x54},
	{0x62, 0x29},
	{0x69, 0x10},
	{0x6A, 0x40},
	{0x85, 0x22},
	{0x98, 0x02},
	{0x9E, 0x00},
	{0xA0, 0x02},
	{0xA2, 0x0A},
	{0xD8, 0x10},
	{0xDF, 0x24},
	{0xE2, 0x05},
	{0xE3, 0x24},
	{0xE6, 0x05},
	{0xF3, 0xB0},//B05A: Version
	{0xF8, 0x5A},//B05A: Version
	{0xED, 0x01},
	{0xEF, 0x01},
	{0x05, 0x0B},
	{0x0D, 0x03},
#if (ORIENTATION == 1)
	{0x1B, 0x8A},//Rotate
	{0x1C, 0x2F},
	{0x1D, 0x87},
#endif
	{0x2A, 0x56},
	{0x37, 0x2C},
	{0x39, 0x36},
	{0x3F, 0xA6},
	{0x40, 0x8C}, // reduce count R
	{0x42, 0xF4},
	{0x43, 0xD6},
	{0x51, 0x28},
	{0x5C, 0x1E},
	{0x5D, 0x0A},
	{0x68, 0xFA},
	{0x69, 0xC8},
	{0x75, 0x56},
	{0xA3, 0x00},//Cmd_WOI_VOffset=22
	{0xA4, 0x16},//Cmd_WOI_VOffset=22
	{0xA5, 0x07},//Cmd_WOI_VSize=1944
	{0xA6, 0x9C},//Cmd_WOI_VSize=1952
	{0xA7, 0x01},//Cmd_WOI_HOffset=332
	{0xA8, 0x4C},//Cmd_WOI_HOffset=332
	{0xA9, 0x07},//Cmd_WOI_HSize=1944
	{0xAA, 0xA0},//Cmd_WOI_HSize=1952
	//{0xAB, 0x01},
	{0xAE, 0x50},
	{0xB0, 0x50},
	{0xC4, 0x54},
	{0xC6, 0x10},
	{0xC9, 0x55},
	{0xCE, 0x30},
	{0xD0, 0x02},
	{0xD1, 0x50}, //increase comparator current
	{0xD3, 0x01},
	{0xD4, 0x04},
	{0xD5, 0x61},
	{0xD8, 0xA0},
	{0xDD, 0x42},
	{0xE2, 0x0A},
	{0xF0, 0x8D},
	{0xF1, 0x19},
	{0xF5, 0x19},
	{0x09, 0x01},
	{0xEF, 0x02},
	{0x2E, 0x04},
	{0x33, 0x84},
	{0x3C, 0xFA},
	{0x4E, 0x02},
	{0xED, 0x01},
	{0xEF, 0x05},
	{0x06, 0x64},//RAW10
	{0x09, 0x09},
	{0x0A, 0x05},
	{0x0D, 0x5E},
	{0x0E, 0x01},
	{0x0F, 0x00},//MIPI CSI disable
	{0x10, 0x02},//2Lane
	{0x11, 0x01},
	{0x15, 0x07},
	{0x17, 0x06},// For mipi test pass
	{0x18, 0x05},
	{0x3B, 0x00},
	{0x40, 0x19},//840M
	{0x41, 0x28},//840M
	{0x43, 0x02},
	{0x44, 0x01},
	{0x49, 0x01},
	{0x4F, 0x01},
	{0x5B, 0x10},//00, B04A, Reset_by_Vsync_En=1
	{0x94, 0x04},
	{0xB0, 0x01},
	{0xED, 0x01},
	{0xEF, 0x06},
	{0x00, 0x0C},
	{0x02, 0x13},
	{0x06, 0x02},
	{0x09, 0x02},
	{0x0A, 0x15},
	{0x0B, 0x90},
	{0x0C, 0x90},
	{0x0D, 0x90},
	{0x0F, 0x1B},
	{0x10, 0x20},
	{0x11, 0x1B},
	{0x12, 0x20},
	{0x18, 0x40},
	{0x1A, 0x40},
	{0x28, 0x03},
	{0x2B, 0x20},
	{0x2D, 0x00},
	{0x2E, 0x20},
	{0x2F, 0x20},
	{0x4A, 0x40},
	{0x4B, 0x40},
	{0x98, 0x05}, //LTM bypass, LTM_EnH=0
	{0x99, 0x80},
	//{0x9A, 0x68},
	{0x9A, 0x22},
	{0x9E, 0x42},
	{0x9F, 0x44}, // Cmd_LTM_LThd[4:0]=8
	{0xF1, 0x01},
	{0xEF, 0x05},
	{0x3B, 0x00},//R_Cmd_Gated_MIPI_Clk=0
	{0xED, 0x01},
	{0xEF, 0x01},
	{0x02, 0xFB},//ResetTG
	{0x09, 0x01},
	{0xEF, 0x00},
	{0x11, 0x00},//GatedAllClk disable, this command move to before MIPI CSI enable(avoid LTM on display abnormal)
};	

static int ps5420_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1952;
	info->modes.mode[0].size.h = 1944;
	info->modes.mode[0].fps = g_ps5420_fps_info_asic[0].fps;
	info->modes.num = 1;
		
	info->i2c.i2c_id = 0x48;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 2000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 2000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 3000);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 5000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	//set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *ps5420_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_ps5420_fps_info_asic); i++)
		if (fps == (int)g_ps5420_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_ps5420_fps_info_asic))
		return NULL;
	return &g_ps5420_fps_info_asic[i];

}

static int ps5420_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *sfps_info;
	struct ps5420_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	sfps_info = ps5420_get_fps_info(mode->fps);
	if (!sfps_info)
		return -RTS_ISP_EINVAL;

#if (SENSOR_HDR == 0)
	set_init_i2c_regs(info->sensor_regs[0],
			  g_ps5420_i2c_init_regs_asic, 1000);
#else
	set_init_i2c_regs(info->sensor_regs[0],
			  g_ps5420_HDR_i2c_init_regs_asic, 1000);
#endif
	set_init_i2c_regs(info->sensor_regs[1],
				  g_ps5420_i2c_init_regs2_asic, 1000);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x2;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1952;
	info->size.h = 1946;
	info->start.x = 0;
	info->start.y = 1;
	info->hts = sfps_info->hts;
	info->pclk = sfps_info->clk;
	info->min_vts = status->min_vts = 1980;
	info->max_vts = 9900;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int ps5420_start(uint32_t isp_id)
{
	struct ps5420_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int ps5420_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ps5420_status *status;

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

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

// ps5420 Gain Table for 1.0x ~ 32x (U.9)
const unsigned int ps5420_gain_table[90] = {
	 256, 272, 288, 304, 320, 336, 352, 368, 384, 400, 416, 432, 448, 464, 480, 496,
	 512, 544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 960, 992,
	1024,1088,1152,1216,1280,1344,1408,1472,1536,1600,1664,1728,1792,1856,1920,1984,
	2048,2176,2304,2432,2560,2688,2816,2944,3072,3200,3328,3456,3584,3712,3840,3968,
	4096,4352,4608,4864,5120,5376,5632,5888,6144,6400,6656,6912,7168,7424,7680,7936,
	8192,12288,14336,16384,22528,24576,27648,29448,31448,32768 
};

static uint16_t get_sensor_gain_reg(float fAGain, struct ps5420_status *status)
{
	int i;
	uint16_t gain = fAGain * 256;
	for (i = 0; i < (90 - 1); i++) {
		if (gain >= ps5420_gain_table[i] &&
		    gain < ps5420_gain_table[i+1]) {
			gain = ps5420_gain_table[i];
			status->num = i;
			break;
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 256.0f;
}

static int ps5420_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ps5420_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int ps5420_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int ps5420_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ps5420_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	i = 0;
	set_sync_i2c(&reg[i++], 0xEF, 0x01);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = clip_d_word(exposure_rows, 2, vts - 1);
		exposure_rows = vts - exposure_rows;
		set_sync_i2c(&reg[i++], 0x0C, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0D, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x0A, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0B, vts & 0xff);
	set_sync_i2c(&reg[i++], 0x83, status->num);
	set_sync_i2c(&reg[i++], 0x09, 0x01);
	#if (SENSOR_HDR == 1)
	float fAGain = ps5420_gain_table[status->num] / 256.0f;
	float ETgain = (fAGain * status->last_exposure) /100;
	int reg_value = 0x68;
	if (ETgain <= 20.0f)
	{
		//set_sync_i2c(&reg[i++], 0x9A, 0x66);
		reg_value = 0x66;
	}
	else if (ETgain > 20.0f && ETgain <= 1200.0f)
	{
		if (ETgain > 20.0f && ETgain <= 610.0f) {
			//set_sync_i2c(&reg[i++], 0x9A, 0x65);
			reg_value = 0x65;
		} else {
			//set_sync_i2c(&reg[i++], 0x9A, 0x55);
			reg_value = 0x55;
		}
	}
	else if (ETgain > 1200.0f && ETgain <= 5000.0f)
	{
		if (ETgain > 1200.0f && ETgain <= 3110.0f) {
			//set_sync_i2c(&reg[i++], 0x9A, 0x54);
			reg_value = 0x54;
		} else {
			//set_sync_i2c(&reg[i++], 0x9A, 0x44);
			reg_value = 0x44;
		}
	}
	else
	{
		if (ETgain > 5000.0f && ETgain <= 7000.0f) {
			//set_sync_i2c(&reg[i++], 0x9A, 0x43);
			reg_value = 0x43;
		} else if (ETgain > 7000.0f && ETgain <= 9000.0f) {
			//set_sync_i2c(&reg[i++], 0x9A, 0x33);
			reg_value = 0x33;
		} else if (ETgain > 9000.0f && ETgain <= 12000.0f) {
			//set_sync_i2c(&reg[i++], 0x9A, 0x32);
			reg_value = 0x32;
		} else {
			//set_sync_i2c(&reg[i++], 0x9A, 0x22);
			reg_value = 0x22;
		}
	}
	set_sync_i2c(&reg[i++], 0xEF, 0x06);
	set_sync_i2c(&reg[i++], 0x9A, reg_value);
	set_sync_i2c(&reg[i++], 0xEF, 0x01);
	//printf("RTK ETgain: %f = (%f * %f)/100, LTM: 0x%02X\r\n", ETgain, fAGain, status->last_exposure, reg_value);
	
	#endif
	regs->num = i;
	return RTS_ISP_OK;
}

static int ps5420_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

#if (PROJECT_PARROT == 0)
	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x0A);
			set_sync_i2c(&reg[i++], 0x1C, 0x30);
			set_sync_i2c(&reg[i++], 0x1D, 0x07);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x8A);
			set_sync_i2c(&reg[i++], 0x1C, 0x2F);
			set_sync_i2c(&reg[i++], 0x1D, 0x07);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x0A);
			set_sync_i2c(&reg[i++], 0x1C, 0x30);
			set_sync_i2c(&reg[i++], 0x1D, 0x87);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x8A);
			set_sync_i2c(&reg[i++], 0x1C, 0x2F);
			set_sync_i2c(&reg[i++], 0x1D, 0x87);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
	#else
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x8A);
			set_sync_i2c(&reg[i++], 0x1C, 0x2F);
			set_sync_i2c(&reg[i++], 0x1D, 0x87);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x0A);
			set_sync_i2c(&reg[i++], 0x1C, 0x30);
			set_sync_i2c(&reg[i++], 0x1D, 0x87);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x8A);
			set_sync_i2c(&reg[i++], 0x1C, 0x2F);
			set_sync_i2c(&reg[i++], 0x1D, 0x07);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xef, 0x01);
			set_sync_i2c(&reg[i++], 0x1B, 0x0A);
			set_sync_i2c(&reg[i++], 0x1C, 0x30);
			set_sync_i2c(&reg[i++], 0x1D, 0x07);
			set_sync_i2c(&reg[i++], 0x09, 0x01);
		break;
	#endif
	}
#endif
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ps5420_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	
	reg.addr = 0xEF;
	reg.data = 0x00;
	ret = rts_isp_write_sensor_reg(isp_id, &reg);
	if (ret) 
		return ret;


	reg.addr = 0x00;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id = reg.data << 8;

	reg.addr = 0x01;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id |= reg.data;
	
	#if (SENSOR_HDR == 0)
		printf("[Test]ps5420_check: SensorID=0x%x, HDR=Off\r\n",id);
	#else
		printf("[Test]ps5420_check: SensorID=0x%x, HDR=On\r\n",id);
	#endif
	
	if (id == 0x5520)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops ps5420_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ps5420",

	.get_info = ps5420_get_info,
	.get_init_info = ps5420_get_init_info,
	.start = ps5420_start,
	//.get_exposure_range = ps5420_get_exposure_range,
	.get_tuned_again = ps5420_get_tuned_again,
	.get_tuned_dgain = ps5420_get_tuned_dgain,
	.get_exposure_gain_info = ps5420_get_exposure_gain_info,
	.set_mirror_flip = ps5420_set_mirror_flip,
	.check = ps5420_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ps5420_ops;
}