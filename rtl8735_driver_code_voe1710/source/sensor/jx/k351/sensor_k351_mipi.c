/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"


#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define float_tol 0.0001f
#define float_ne(x, y) (fabsf((float)x - (float)y) > float_tol)
#define float_eq(x, y) (fabsf((float)x - (float)y) < float_tol)
#define VMAX_VHDR 4200
#define VMAX_LINEAR 2100
#define SENSOR_MIN_EXP_LINE 1.0
#define AE_MAX_SHORT_EXP_BASE 200

#define ORIENTATION 0	//0=default, 1=rotate180
#define SENSOR_HDR 0		

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct jxk351_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t min_vts;
	int num;
};

#if (SENSOR_HDR == 0)
static struct jxk351_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct jxk351_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

/* Linear frame rate table*/
static const struct fps_info g_jxk351_fps_info_linear[] = {
/*   FPS    HTS       VTS     PCLK      */
	{30.0, (2400), (2100), (151200000)},
};

/* HDR frame rate table*/
static const struct fps_info g_jxk351_fps_info_hdr[] = {
/*   FPS    HTS       VTS       PCLK      */
	{20, (2400), (2100*2), (201600000)},
};

static struct rts_isp_i2c_reg g_jxk351_i2c_init_regs_linear[] = {
	{0x12, 0x40},
	{0xAD, 0x01},
	{0xAD, 0x00},
	{0x0E, 0x11},
	{0x0F, 0x0C},
	{0x10, 0x3F},
	{0x0C, 0x00},
	{0x67, 0xA2},
	{0x0D, 0x21},
	{0x64, 0x31},
	{0x65, 0x9D},
	{0xBE, 0x18},
	{0xBF, 0x60},
	{0xBC, 0xC0},
	{0x20, 0x2C},
	{0x21, 0x01},
	{0x22, 0x34},
	{0x23, 0x08},
	{0x24, 0xF6},
	{0x25, 0xD8},
	{0x26, 0x71},
	{0x27, 0x0C},
	{0x28, 0x0D},
	{0x29, 0x00},
	{0x2B, 0x10},
	{0x2C, 0x00},
	{0x2D, 0x05},
	{0x2E, 0xFB},
	{0x2F, 0x14},
	{0x30, 0xF8},
	{0x87, 0xC5},
	{0x9D, 0xB9},
	{0xAC, 0x00},
	{0x1D, 0x00},
	{0x1E, 0x10},
	{0x3A, 0xD5},
	{0x3B, 0x9B},
	{0x3C, 0x6D},
	{0x3D, 0x59},
	{0x3E, 0x12},
	{0x3F, 0x14},
	{0x42, 0x11},
	{0x43, 0x00},
	{0x70, 0xA0},
	{0x71, 0x24},
	{0x76, 0x08},
	{0x06, 0x00},
	{0x08, 0x04},
	{0x9F, 0x4C},
	{0x7E, 0x0B},
	{0x31, 0x04},
	{0x32, 0x04},
	{0x33, 0xCC},
	{0x38, 0xCA},
	{0x6F, 0x00},
	{0x78, 0x49},
	{0xB0, 0x14},
	{0xB1, 0xA0},
	{0xB2, 0x24},
	{0xB3, 0x14},
	{0xB5, 0x50},
	{0xB6, 0x57},
	{0xB8, 0x06},
	{0xB9, 0x08},
	{0xBA, 0x8B},
	{0xBB, 0x8B},
	{0xC3, 0x90},
	{0xF9, 0x00},
	{0x56, 0xF1},
	{0x57, 0x60},
	{0x58, 0x42},
	{0x59, 0x66},
	{0x5A, 0x80},
	{0x5B, 0x10},
	{0x5C, 0x10},
	{0x5D, 0x49},
	{0x60, 0x60},
	{0x61, 0x00},
	{0x62, 0x60},
	{0x68, 0x00},
	{0x69, 0x90},
	{0xA5, 0x08},
	{0xAA, 0x00},
	{0xC1, 0xC0},
	{0xC4, 0x00},
	{0xD4, 0xFF},
	{0xEB, 0x15},
	{0xEC, 0x03},
	{0xE1, 0xF2},
	{0x80, 0x81},
	{0x81, 0x44},
	{0xFB, 0x20},
	{0xFC, 0x32},
	{0xFA, 0x01},
	{0x16, 0xFF},
	{0x17, 0x08},
	{0x49, 0x10},
	{0x85, 0x00},
	{0xB4, 0x01},
	{0xD2, 0x80},
	{0xD0, 0x00},
	{0xD3, 0x2D},
	{0x39, 0x8A},
	{0xFF, 0x01},
	{0x74, 0x04},
	{0xFF, 0x00},
	{0x89, 0x00},
	{0x12, 0x00},
};

static struct rts_isp_i2c_reg g_jxk351_i2c_init_regs_hdr[] = {
	{0x12, 0x48},
	{0xAD, 0x01},
	{0xAD, 0x00},
	{0x0E, 0x11},
	{0x0F, 0x0C},
	{0x10, 0x2A},
	{0x0C, 0x00},
	{0x67, 0x91},
	{0x0D, 0x20},
	{0x64, 0x31},
	{0x65, 0x9D},
	{0xBE, 0x18},
	{0xBF, 0x60},
	{0xBC, 0xC0},
	{0x20, 0x96},
	{0x21, 0x00},
	{0x22, 0x34},
	{0x23, 0x08},
	{0x24, 0xF6},
	{0x25, 0xD8},
	{0x26, 0x71},
	{0x27, 0x08},
	{0x28, 0x0C},
	{0x29, 0x00},
	{0x2B, 0x10},
	{0x2C, 0x00},
	{0x2D, 0x05},
	{0x2E, 0xFB},
	{0x2F, 0x14},
	{0x30, 0xF8},
	{0x87, 0xC5},
	{0x9D, 0xB9},
	{0xAC, 0x00},
	{0x1D, 0x00},
	{0x1E, 0x10},
	{0x3A, 0x49},
	{0x3B, 0x2D},
	{0x3C, 0x29},
	{0x3D, 0x25},
	{0x3E, 0x12},
	{0x3F, 0x24},
	{0x42, 0x12},
	{0x43, 0x00},
	{0x70, 0xA0},
	{0x71, 0x24},
	{0x76, 0x08},
	{0x06, 0x00},
	{0x08, 0x04},
	{0x9F, 0x4C},
	{0x7E, 0x0B},
	{0x31, 0x03},
	{0x32, 0x03},
	{0x33, 0xC8},
	{0x34, 0x04},
	{0x38, 0xCA},
	{0x6F, 0x00},
	{0x78, 0x49},
	{0xB0, 0x14},
	{0xB1, 0xA0},
	{0xB2, 0x1C},
	{0xB3, 0x0E},
	{0xB5, 0x50},
	{0xB6, 0x57},
	{0xB8, 0x06},
	{0xB9, 0x08},
	{0xBA, 0x8B},
	{0xBB, 0x8B},
	{0xC3, 0x90},
	{0xF9, 0x00},
	{0x56, 0xF1},
	{0x57, 0x60},
	{0x58, 0x42},
	{0x59, 0x66},
	{0x5A, 0x80},
	{0x5B, 0x10},
	{0x5C, 0x10},
	{0x5D, 0x49},
	{0x60, 0x60},
	{0x61, 0x00},
	{0x62, 0x60},
	{0x68, 0x00},
	{0x69, 0x90},
	{0xA5, 0x08},
	{0xAA, 0x00},
	{0xC1, 0xC0},
	{0xC4, 0x00},
	{0xD4, 0xFF},
	{0xEB, 0x15},
	{0xEC, 0x03},
	{0xE1, 0xF2},
	{0x80, 0x81},
	{0x81, 0x44},
	{0xFB, 0x20},
	{0xFC, 0x32},
	{0xFA, 0x01},
	{0x16, 0xFF},
	{0x17, 0x08},
	{0x49, 0x10},
	{0x85, 0x00},
	{0xB4, 0x01},
	{0xD2, 0x80},
	{0xD0, 0x00},
	{0xD3, 0x2D},
	{0x39, 0x8A},
	{0xFF, 0x01},
	{0x74, 0x04},
	{0xFF, 0x00},
	{0x1B, 0x07},
	{0x05, 0x07},
	{0x7D, 0x21},
	{0xA4, 0x19},
	{0x88, 0x08},
	{0x37, 0x44},
	{0x44, 0x64},
	{0x04, 0xC0},
	{0x6F, 0x00},
	{0x89, 0x00},
	{0x12, 0x08},
};


static int jxk351_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	
#if (SENSOR_HDR == 0)
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2000;
	info->modes.mode[i].size.h = 2000;
	info->modes.mode[i].fps = g_jxk351_fps_info_linear[0].fps; 
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2000;
	info->modes.mode[i].size.h = 2000;
	info->modes.mode[i].fps = g_jxk351_fps_info_hdr[0].fps;
	i++;
	info->modes.num = i;
#else
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2000;
	info->modes.mode[i].size.h = 2000;
	info->modes.mode[i].fps = g_jxk351_fps_info_hdr[0].fps; 
	i++;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2000;
	info->modes.mode[i].size.h = 2000;
	info->modes.mode[i].fps = g_jxk351_fps_info_linear[0].fps;
	i++;
	info->modes.num = i;
#endif

	info->i2c.i2c_id = 0x40;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *jxk351_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_jxk351_fps_info_hdr); i++)
			if (fps <= g_jxk351_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxk351_fps_info_hdr))
			return NULL;

		return &g_jxk351_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_jxk351_fps_info_linear); i++)
			if (fps <= g_jxk351_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxk351_fps_info_linear))
			return NULL;

		return &g_jxk351_fps_info_linear[i];
	}
}



static int jxk351_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct jxk351_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	fps_info = jxk351_get_fps_info(mode->fps, &mode->hdr);
	
	if (!fps_info)
	return -RTS_ISP_EINVAL;
	
	if (mode->hdr == HDR_MODE) {
		set_init_i2c_regs(info->sensor_regs[0],
				  g_jxk351_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 2008;
		info->size.h = 2008;
		info->start.x = 8;
		info->start.y = 1;

		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = VMAX_VHDR;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */	
	} else {
		set_init_i2c_regs(info->sensor_regs[0],
				  g_jxk351_i2c_init_regs_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2008;
		info->size.h = 2008;
		info->start.x = 8;
		info->start.y = 1;

		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = VMAX_LINEAR;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	}

	return RTS_ISP_OK;
}

static int jxk351_start(uint32_t isp_id)
{
	struct jxk351_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;

	return RTS_ISP_OK;
}

static int jxk351_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxk351_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 4) * status->exp_step;
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_exp_line = ( vts - 10 );


		tmp1 = (uint32_t)((max_exp_line) / (ratio[0] + 1));
		tmp2 = AE_MAX_SHORT_EXP_BASE;
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		
		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = status->exp_step * SENSOR_MIN_EXP_LINE;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
	}


	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct jxk351_status *status)
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

	return (fAgainReg);
}

uint32_t clip_d_word(uint32_t current, uint32_t minimum, uint32_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int jxk351_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct jxk351_status *status;

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

static int jxk351_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxk351_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	
	status = &g_status[isp_id];
	
	dgain[0] = 1.0f;
	
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int jxk351_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
int i;
	uint32_t vts;
	struct jxk351_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];



	if (status->hdr == LINEAR_MODE) {
		vts = exp_gain->vts;
		reg = regs->reg;

		i = 0;
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		//set gain 		
		set_sync_i2c(&reg[i++], 0x00, status->num);
		//set vts 	
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
		regs->num = i;
	
	} else if (status->hdr == HDR_MODE) {
		vts = exp_gain->vts;
		reg = regs->reg;
		
		for (i = 0; i < 2; i++) {
			exposure_rows[i] = (exp_gain->exposure[i] /
					       status->exp_step + 0.5f);
		}
		if ((exposure_rows[1] + exposure_rows[0]) > (exp_gain->vts / 2))
			vts = exposure_rows[1] + exposure_rows[0];
		else
			vts = (exp_gain->vts / 2);
		
		
		i = 0;
		
		// set exposure
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			exposure_rows[1] = exp_gain->exposure[1] / status->exp_step + 0.5f;
			exposure_rows[1] = exposure_rows[1] + 49152;  // set reg 0x04 bit 7,6 = 1
			set_sync_i2c(&reg[i++], 0x04, exposure_rows[1] >> 8);
			set_sync_i2c(&reg[i++], 0x03, exposure_rows[1] & 0xff);
			
			status->last_exposure[1] = exp_gain->exposure[1];
		}
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			
			status->last_exposure[0] = exp_gain->exposure[0];
		}		
		// set gain 
		set_sync_i2c(&reg[i++], 0x00, status->num);
		// set vts 
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
		regs->num = i;
	}	
	
	return RTS_ISP_OK;
}

static int jxk351_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct jxk351_status *status;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	
	status = &g_status[isp_id];
	
	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: //normal
		default:
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x00);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x08);	
			break;
		case 2: 	// Mirror
		if (status->hdr == LINEAR_MODE){
           	set_sync_i2c(&reg[i++], 0x12, 0x20);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x28);	
			break;
		case 1: 		// VFlip
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x10);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x18);			
			break;
		case 3: 	// Rotate
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x30);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x38);			
			break;	
	#else
		case 0: //normal
		default:
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x30);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x38);	
			break;
		case 2: 	// Mirror
		if (status->hdr == LINEAR_MODE){
           	set_sync_i2c(&reg[i++], 0x12, 0x20);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x28);	
			break;
		case 1: 		// VFlip
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x10);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x18);			
			break;
		case 3: 	// Rotate
		if (status->hdr == LINEAR_MODE){
            set_sync_i2c(&reg[i++], 0x12, 0x00);
		}else
			set_sync_i2c(&reg[i++], 0x12, 0x08);			
			break;	
	#endif					
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int jxk351_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

	reg.addr = 0x0A;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id = reg.data << 8;

	reg.addr = 0x0B;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0x0856)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops jxk351_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "jxk351",
	.get_info = jxk351_get_info,
	.get_init_info = jxk351_get_init_info,
	.start = jxk351_start,
	.get_exposure_range = jxk351_get_exposure_range,
	.get_tuned_again = jxk351_get_tuned_again,
	.get_tuned_dgain = jxk351_get_tuned_dgain,
	.get_exposure_gain_info = jxk351_get_exposure_gain_info,
	.set_mirror_flip = jxk351_set_mirror_flip,
	.check = jxk351_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &jxk351_ops;
}

//#endif
