/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

											/* Default sensor mirror and flip mode => 0:default, 1:rotate180 */
#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define SENSOR_MIN_EXP_LINE 1		//The minimum interval must be >= 8line. For SOI sensor, short exposure line =1 line, the interval line =16, therefore there is no need to limit the minimum short exposure time. 
//#define AE_MAX_SHORT_EXP_BASE 244	//1800-1536-12-8= 244
#define SENSOR_HDR 0												/* Default sensor hdr mode => 0:linear, 1:hdr */
#define ORIENTATION 1	

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct jxf51_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure[2];
	int again_reg;
	struct rts_isp_i2c_reg regs1[3];
};

#if (SENSOR_HDR == 0)
static struct jxf51_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct jxf51_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

/* Linear frame rate table*/
static const struct fps_info g_jxf51_fps_info_linear[] = {
	{30.0f, 2400, 2000, 144000000},
};

/* HDR frame rate table*/
static const struct fps_info g_jxf51_fps_info_hdr[] = {
	{20.0f, 2000, 3600, 144000000},
};

static struct rts_isp_i2c_reg g_jxf51_i2c_init_regs_linear[] = {
	{0x12,0x40},
	{0x48,0x8B},
	{0x48,0x0B},
	{0x0E,0x12},
	{0x0F,0x04},
	{0x10,0x50},
	{0x11,0x80},
	{0x0D,0x50},
	{0x57,0x60},
	{0x58,0x1B},
	{0x5F,0x42},
	{0x60,0x2B},
	{0x61,0x08},
	{0x07,0x08},
	{0x20,0x58}, //Frame Width 600x4 =2400
	{0x21,0x02},
	{0x22,0xD0}, //Frame height 2000
	{0x23,0x07},
	{0x24,0x82},
	{0x25,0x08},
	{0x26,0x61},
	{0x27,0x4E},
	{0x28,0x11},
	{0x29,0x02},
	{0x2A,0x48},
	{0x2B,0x12},
//	{0x2C,0x00},
	{0x2C,0x02},//Mirror / Flip  control set value from 0x00 to 0x02
	{0x2D,0x00},
	{0x2E,0x86},
	{0x2F,0x44},
	{0x41,0x04},
	{0x42,0x03},
	{0x46,0x18},
	{0x47,0x42},
	{0x80,0x01},
	{0xAF,0x12},
	{0xBD,0x08},
	{0xBE,0x06},
	{0xAB,0x00},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x70,0xD1},
	{0x71,0x8B},
	{0x72,0x6D},
	{0x73,0x49},
	{0x75,0x1B},
	{0x74,0x12},
	{0x89,0x11},
	{0x0C,0x00},
	{0x6B,0x00},
	{0x86,0x40},
	{0x6E,0x2C},
	{0x78,0x14},
	{0x76,0x67},
	{0x2F,0x44},
	{0x31,0x10},
	{0x32,0x25},
	{0x33,0x5C},
	{0x34,0x23},
	{0x35,0x2B},
	{0x3A,0xA1},
	{0x3B,0xA0},
	{0x3C,0x2B},
	{0x3D,0x00},
	{0x3E,0x00},
	{0x3F,0x8E},
	{0x40,0x93},
	{0x56,0x12},
	{0x59,0x40},
	{0x5A,0x10},
	{0x85,0x3A},
	{0xBF,0x01},
	{0x4D,0x08},
	{0x53,0x01},
	{0xBF,0x00},
	{0x9C,0xA1},
	{0x62,0x21},
	{0x64,0xE0},
	{0x65,0x33},
	{0x66,0x13},
	{0x67,0x57},
	{0x68,0x00},
	{0x69,0xFC},
	{0x6A,0x44},
	{0x7A,0x40},
	{0x8F,0x10},
	{0xBF,0x01},
	{0x45,0x07},
	{0x46,0x3C},
	{0x47,0x88},
	{0x48,0xFC},
	{0x49,0x21},
	{0x4B,0x42},
	{0xBF,0x00},
	{0x97,0xA2},
	{0x13,0x81},
	{0x96,0x04},
	{0x4A,0x05},
	{0x7E,0xC9},
	{0xA7,0x04},
	{0x50,0x02},
	{0x49,0x10},
	{0x7B,0x4A},
	{0x7C,0x0A},
	{0x7F,0x57},
	{0x90,0x00},
	{0x8C,0xFF},
	{0x8D,0xC7},
	{0x8E,0x80},
	{0x8B,0x01},
	{0xBF,0x01},
	{0x4E,0x11},
	{0xBF,0x00},
	{0x82,0x00},
	{0x19,0x20},
#if (ORIENTATION == 1)
	{0x12,0x30},
#else
	{0x12,0x00},
#endif
};
static struct rts_isp_i2c_reg g_jxf51_i2c_init_regs_hdr[] = {
	{0x12,0x48},
	{0x48,0x8B},
	{0x48,0x0B},
	{0x0E,0x12},
	{0x0F,0x04},
	{0x10,0x50},
	{0x11,0x80},
	{0x0D,0x50},
	{0x57,0x60},
	{0x58,0x1B},
	{0x5F,0x42},
	{0x60,0x2B},
	{0x61,0x08},
	{0x07,0x0B},
	{0x20,0xF4},//Frame Width 500x4=2000
	{0x21,0x01},
	{0x22,0x10},//Frame height 3600
	{0x23,0x0E},
	{0x24,0x80},
	{0x25,0x00},
	{0x26,0x61},
	{0x27,0xEB},
//	{0x28,0x29},
	{0x28,0x27},//For ISP bayer Order
	{0x29,0x01},
	{0x2A,0xE4},
	{0x2B,0x11},
//	{0x2C,0x00},
	{0x2C,0x02},//Mirror / Flip  control set value from 0x00 to 0x02
	{0x2D,0x00},
	{0x2E,0x86},
	{0x2F,0x44},
	{0x41,0x04},
	{0x42,0x03},
	{0x46,0x1C},
	{0x47,0x42},
	{0x80,0x01},
	{0xAF,0x12},
	{0xBD,0x00},
	{0xBE,0x06},
	{0xAB,0x00},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x70,0xD5},
	{0x71,0x96},
	{0x72,0x6D},
	{0x73,0x49},
	{0x75,0x96},
	{0x74,0x12},
	{0x89,0x14},
	{0x0C,0x00},
	{0x6B,0x00},
	{0x86,0x40},
	{0x6E,0x2C},
	{0x78,0x14},
	{0x76,0x67},
	{0x2F,0x44},
	{0x31,0x10},
	{0x32,0x25},
	{0x33,0x5C},
	{0x34,0x23},
	{0x35,0x2B},
	{0x3A,0xA1},
	{0x3B,0xA0},
	{0x3C,0x2B},
	{0x3D,0x00},
	{0x3E,0x00},
	{0x3F,0x8E},
	{0x40,0x93},
	{0x56,0x12},
	{0x59,0x40},
	{0x5A,0x10},
	{0x85,0x3A},
	{0xBF,0x01},
	{0x4D,0x08},
	{0x53,0x01},
	{0xBF,0x00},
	{0x9C,0xA1},
	{0x62,0x21},
	{0x64,0xE0},
	{0x65,0x33},
	{0x66,0x13},
	{0x67,0x57},
	{0x68,0x00},
	{0x69,0xFC},
	{0x6A,0x44},
	{0x7A,0x40},
	{0x8F,0x10},
	{0x9D,0x01},
	{0xBF,0x01},
	{0x45,0x07},
	{0x46,0x3C},
	{0x47,0x88},
	{0x48,0xFC},
	{0x49,0x21},
	{0x4B,0x42},
	{0xBF,0x00},
	{0x97,0xA2},
	{0x13,0x81},
	{0x96,0x04},
	{0x4A,0x05},
	{0x7E,0xC9},
	{0xA7,0x04},
	{0x50,0x02},
	{0x49,0x10},
	{0x7B,0x4A},
	{0x7C,0x0A},
	{0x7F,0x57},
	{0x90,0x00},
	{0x8C,0xFF},
	{0x8D,0xC7},
	{0x8E,0x80},
	{0x8B,0x01},
	{0xBF,0x01},
	{0x4E,0x11},
	{0xBF,0x00},
	{0x82,0x00},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x06,0x23},
	{0x03,0xFF},
	{0x04,0xFF},
#if (ORIENTATION == 1)
	{0x12,0x38},
#else
	{0x12,0x08},
#endif

//	{0x05,0x14},	// this initial setting (remove after AE control has completed)
//	{0x01,0x0f},	// this initial setting (remove after AE control has completed)
//	{0x02,0x02},	// this initial setting (remove after AE control has completed)
};


static int jxf51_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if (SENSOR_HDR == 0)
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1536;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_jxf51_fps_info_linear[0].fps;
	i++;

	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1536;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_jxf51_fps_info_hdr[0].fps;
	i++;
#else
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1536;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_jxf51_fps_info_hdr[0].fps;
	i++;

	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1536;
	info->modes.mode[i].size.h = 1536;
	info->modes.mode[i].fps = g_jxf51_fps_info_linear[0].fps;
	i++;
#endif
	info->modes.num = i;

	info->i2c.i2c_id = 0x40;//0x90 divide 2
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 100);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *jxf51_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;
	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_jxf51_fps_info_hdr); i++)
			if (fps <= g_jxf51_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxf51_fps_info_hdr))
			return NULL;

		return &g_jxf51_fps_info_hdr[i];
	}
	else {
		for (i = 0; i < ARRAY_SIZE(g_jxf51_fps_info_linear); i++)
			if (fps == (int)g_jxf51_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxf51_fps_info_linear))
			return NULL;
		return &g_jxf51_fps_info_linear[i];
	}

}

static int jxf51_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *sfps_info;
	struct jxf51_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	sfps_info = jxf51_get_fps_info(mode->fps, &mode->hdr);

	if (!sfps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		set_init_i2c_regs(info->sensor_regs[0], g_jxf51_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x2;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 1536;
		info->size.h = 1536;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = sfps_info->hts;
		info->pclk = sfps_info->clk;
		info->min_vts = status->min_vts = sfps_info->vts;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */	//  2000/144=13.88us
	}
	else{
		set_init_i2c_regs(info->sensor_regs[0], g_jxf51_i2c_init_regs_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x2;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 1544;
		info->size.h = 1544;
		info->start.x = 2;
		info->start.y = 3;

		info->hts = sfps_info->hts;
		info->pclk = sfps_info->clk;
		info->min_vts = status->min_vts = sfps_info->vts;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */	//  2400/144=16us
	}
	return RTS_ISP_OK;
}
static int jxf51_start(uint32_t isp_id)
{
	struct jxf51_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	return RTS_ISP_OK;
}
static int jxf51_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxf51_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 4) * status->exp_step;
	}
	else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_exp_line = ( vts - 10 );

		tmp1 = (uint32_t)((max_exp_line) / (ratio[0] + 1));
	//	tmp2 = AE_MAX_SHORT_EXP_BASE;
	//	tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = status->exp_step * SENSOR_MIN_EXP_LINE;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
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

static uint16_t get_sensor_gain_reg(float fAGain, struct jxf51_status *status)
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
	else if(fAGain>=8.0 && fAGain<=15.75){
		wAgainReg = (int)(2.0f*(fAGain-8.0) + 48.0);
	}
	else
		wAgainReg = 0x3f;

	status->again_reg = wAgainReg;
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

	return (fAgainReg);
}
static int jxf51_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct jxf51_status *status;

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

static int jxf51_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxf51_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	status = &g_status[isp_id];

	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int jxf51_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct jxf51_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

#if 1
	if (status->hdr == LINEAR_MODE) {

		vts = exp_gain->vts;
		reg = regs->reg;

		i = 0;
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = (exp_gain->exposure[0] / status->exp_step + 0.5f);
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		set_sync_i2c(&reg[i++], 0x00, status->again_reg);
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
		regs->num = i;
	}

	else if (status->hdr == HDR_MODE) {
		vts = exp_gain->vts;
		reg = regs->reg;

		for (i = 0; i < 2; i++) {
			exposure_rows[i] = (exp_gain->exposure[i] / status->exp_step + 0.5f);
		}
		if ((exposure_rows[1] + exposure_rows[0]) > exp_gain->vts)
			vts = exposure_rows[1] + exposure_rows[0];
		else
			vts = exp_gain->vts;

		i = 0;
		// set exposure
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			exposure_rows[1] = exp_gain->exposure[1] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x05, exposure_rows[1] & 0xff);

			status->last_exposure[1] = exp_gain->exposure[1];
		}
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
		// set gain
		set_sync_i2c(&reg[i++], 0x00, status->again_reg);
		// set vts
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
		regs->num = i;

	}
#endif
	return RTS_ISP_OK;
}


static int jxf51_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	int regtmp;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct jxf51_status *status;

	status = &g_status[isp_id];

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	regtmp = 0;
	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)
	{
	#if (ORIENTATION == 0)
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

	if (status->hdr == HDR_MODE)
		regtmp |= 0x08;

    set_sync_i2c(&reg[i++], 0x12, regtmp);
	mf_info->regs.num = i;

	return RTS_ISP_OK;
}


static int jxf51_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

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

	if (id == 0x0F51)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops jxf51_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "jxf51",

	.get_info = jxf51_get_info,
	.get_init_info = jxf51_get_init_info,
	.start = jxf51_start,
	.get_exposure_range = jxf51_get_exposure_range,
	.get_tuned_again = jxf51_get_tuned_again,
	.get_tuned_dgain = jxf51_get_tuned_dgain,
	.get_exposure_gain_info = jxf51_get_exposure_gain_info,
	.set_mirror_flip = jxf51_set_mirror_flip,
	.check = jxf51_check,
};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &jxf51_ops;
}