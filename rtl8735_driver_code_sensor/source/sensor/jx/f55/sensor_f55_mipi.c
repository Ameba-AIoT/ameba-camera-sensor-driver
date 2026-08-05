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

#define ANALOG_GAIN_MAX_RATIO (float)15.5f							/* Max sensor gain ratio => 0x3f = 15.5x */
#define DEFAULT_VTS (1125 * 2)
#define ORIENTATION 0	
#define SENSOR_HDR 0		

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct jxf55_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure[2];
	int last_gain;
	int last_vts;
	uint16_t size_h;
};

#if (SENSOR_HDR == 0)
static struct jxf55_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct jxf55_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

static const struct fps_info g_jxf55_fps_info_asic[] = {
	{30.0f, 2560, 86400000},
};

static const struct fps_info g_jxf55_HDR_fps_info_asic[] = {
	{30.0f, 2560, 172800000},
};

static struct rts_isp_i2c_reg g_jxf55_i2c_init_regs_asic[] = {
	{0x12,0x40},
	{0x48,0x8F},
	{0x48,0x0F},
	{0x0E,0x11},
	{0x0F,0x04},
	{0x10,0x20},
	{0x11,0x80},
	{0x46,0x18},
	{0x0D,0xA0},
	{0x57,0x60},
	{0x58,0x18},
	{0x5F,0x42},
	{0x60,0x2B},
	{0x20,0x00},
	{0x21,0x05},
	{0x22,0x65},
	{0x23,0x04},
	{0x24,0xC2},
	{0x25,0x3C},
	{0x26,0x43},
	{0x27,0xFC},
	{0x28,0x17},
	{0x29,0x04},
	{0x2A,0xF0},
	{0x2B,0x14},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x15},
	{0x2F,0x44},
	{0x41,0xC4},
	{0x42,0x33},
	{0x47,0x52},
	{0x80,0x02},
	{0xAF,0x22},
	{0xBD,0x84},
	{0xBE,0x07},
	{0x9B,0x83},
	{0xAB,0x00},
	{0x82,0x20},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x68,0x00},
	{0x70,0x8D},
	{0x71,0x6E},
	{0x72,0x2A},
	{0x73,0x36},
	{0x75,0x94},
	{0x74,0x12},
	{0x89,0x09},
	{0x0C,0xD0},
	{0x6B,0x20},
	{0x86,0x00},
	{0x6E,0x4C},
	{0x78,0x44},
	{0xA1,0xAF},
	{0x32,0x1F},
	{0x33,0x54},
	{0x35,0x5F},
	{0x56,0x0A},
	{0x59,0xF3},
	{0x61,0xA0},
	{0x84,0x00},
	{0x85,0xA8},
	{0x8E,0xA0},
	{0x8F,0x90},
	{0x91,0x14},
	{0x93,0x62},
	{0x9F,0x40},
	{0xBF,0x01},
	{0x57,0x24},
	{0xBF,0x00},
	{0x5A,0x41},
	{0x5B,0xA0},
	{0x5C,0x08},
	{0x5D,0x33},
	{0x5E,0x85},
	{0x63,0x0F},
	{0x64,0xCC},
	{0x65,0x20},
	{0x66,0x00},
	{0x67,0x71},
	{0x69,0xF4},
	{0x7A,0x88},
	{0x9D,0x10},
	{0xBF,0x01},
	{0x5F,0x0E},
	{0x60,0x09},
	{0xBF,0x00},
	{0x97,0x7A},
	{0x13,0x01},
	{0x96,0x04},
	{0x4A,0x01},
	{0x50,0x02},
	{0x49,0x10},
	{0xBF,0x01},
	{0x4E,0x11},
	{0x50,0x00},
	{0x51,0x8F},
	{0x62,0xFF},
	{0x63,0x07},
	{0x64,0xE0},
	{0x6A,0x15},
	{0x6B,0x80},
	{0x6C,0x32},
	{0xBF,0x00},
	{0x7E,0xCC},
	{0x7F,0x4F},
	{0x8B,0x01},
	{0xA7,0x00},
	{0x6A,0x41},
	{0x39,0x71},
	{0x19,0x20},
	{0x1B,0x4F},
#if (ORIENTATION == 1)
	{0x12,0x30},
#else
	{0x12,0x00},
#endif
};

static struct rts_isp_i2c_reg g_jxf55_HDR_i2c_init_regs_asic[] = {
	{0x12,0x48},
	{0x48,0x8B},
	{0x48,0x0B},
	{0x0E,0x11},
	{0x0F,0x04},
	{0x10,0x40},
	{0x11,0x80},
	{0x46,0x1C},
	{0x0D,0x50},
	{0x57,0x60},
	{0x58,0x18},
	{0x5F,0x42},
	{0x60,0x2B},
	{0x20,0x80},
	{0x21,0x02},
	{0x22,0xCA},
	{0x23,0x08},
	{0x24,0xE1},
	{0x25,0x3C},
	{0x26,0x41},
	{0x27,0x77},
	{0x28,0x2D},
	{0x29,0x02},
	{0x2A,0x70},
	{0x2B,0x12},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x15},
	{0x2F,0x44},
	{0x41,0xC5},
	{0x42,0x33},
	{0x47,0x52},
	{0x80,0x02},
	{0xAF,0x12},
	{0xBD,0x84},
	{0xBE,0x07},
	{0x9B,0x83},
	{0xAB,0x00},
	{0x82,0x20},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x68,0x00},
	{0x70,0xD5},
	{0x71,0xBB},
	{0x72,0x6D},
	{0x73,0x49},
	{0x75,0x96},
	{0x74,0x12},
	{0x89,0x16},
	{0x0C,0xD0},
	{0x6B,0x20},
	{0x86,0x00},
	{0x6E,0x4C},
	{0x78,0x44},
	{0xA1,0xAF},
	{0x32,0x1F},
	{0x33,0x54},
	{0x35,0x5F},
	{0x56,0x0A},
	{0x59,0x7A},
	{0x61,0xA0},
	{0x84,0x00},
	{0x85,0x67},
	{0x8E,0xA0},
	{0x8F,0x90},
	{0x91,0x14},
	{0x93,0x62},
	{0x9F,0x40},
	{0xBF,0x01},
	{0x57,0x24},
	{0xBF,0x00},
	{0x5A,0x41},
	{0x5B,0xA0},
	{0x5C,0x08},
	{0x5D,0x33},
	{0x5E,0x85},
	{0x63,0x0F},
	{0x64,0xCC},
	{0x65,0x20},
	{0x66,0x00},
	{0x67,0x71},
	{0x69,0xF4},
	{0x7A,0x88},
	{0x9D,0x10},
	{0xBF,0x01},
	{0x5F,0x0E},
	{0x60,0x09},
	{0xBF,0x00},
	{0x97,0x7A},
	{0x13,0x01},
	{0x96,0x04},
	{0x4A,0x01},
	{0x50,0x02},
	{0x49,0x10},
	{0xBF,0x01},
	{0x4E,0x11},
	{0x50,0x00},
	{0x51,0x8F},
	{0x62,0xFF},
	{0x63,0x07},
	{0x64,0xE0},
	{0x6A,0x15},
	{0x6B,0x80},
	{0x6C,0x32},
	{0xBF,0x00},
	{0x7E,0xCC},
	{0x7F,0xEF},
	{0x8B,0x01},
	{0xA7,0x00},
	{0x6A,0x41},
	{0x39,0x71},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x07,0x07},
	{0x06,0x03},
	{0x08,0x00},
	{0x03,0xFF},
	{0x04,0xFF},
	{0xBF,0x01},
	{0x6B,0xC0},
	{0xBF,0x00},
#if (ORIENTATION == 1)
	{0x12,0x38},
#else
	{0x12,0x08},
#endif
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x40	//0x6e(default, D[0]=D[1]=0)
#define SLAVE_ADDR_1 0x46	//0x8c(D[0]=D[1]=1)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int jxf55_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	
#if (SENSOR_HDR == 0)
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = g_jxf55_fps_info_asic[0].fps; //@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = g_jxf55_HDR_fps_info_asic[0].fps; //@MLCK=27MHz
	i++;
	info->modes.num = i;
#else
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = g_jxf55_HDR_fps_info_asic[0].fps; //@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = g_jxf55_fps_info_asic[0].fps; //@MLCK=27MHz
	i++;
	info->modes.num = i;
#endif

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *jxf55_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_jxf55_HDR_fps_info_asic); i++)
			if (fps == (int)g_jxf55_HDR_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxf55_HDR_fps_info_asic))
			return NULL;

		return &g_jxf55_HDR_fps_info_asic[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_jxf55_fps_info_asic); i++)
			if (fps == (int)g_jxf55_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_jxf55_fps_info_asic))
			return NULL;

		return &g_jxf55_fps_info_asic[i];
	}

}

static int jxf55_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct jxf55_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;
	fps_info = jxf55_get_fps_info(mode->fps, &mode->hdr);

	if (!fps_info)
		return -RTS_ISP_EINVAL;

	printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;

	info->size.w = 1924;
	info->size.h = status->size_h = 1084;
	info->start.x = 0;
	info->start.y = 3;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	//info->max_vts = 6750;
	info->max_vts = 65535 - info->min_vts;

	if (mode->hdr == HDR_MODE) {
		set_init_i2c_regs(info->sensor_regs[0],
					g_jxf55_HDR_i2c_init_regs_asic, 0);

		info->min_vts = status->min_vts = 2250;
		info->mipi_behavor = VC_HDR;
		info->interface.vhdr_start_line_tnr = 3;
	} else {
		set_init_i2c_regs(info->sensor_regs[0],
					g_jxf55_i2c_init_regs_asic, 0);

		info->min_vts = status->min_vts = 1125;
		info->mipi_behavor = NONE_HDR;
	}
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */

	return RTS_ISP_OK;
}
static int jxf55_start(uint32_t isp_id)
{
	struct jxf55_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	status->last_vts = 0;
	status->last_gain = 0;

	return RTS_ISP_OK;
}

static int jxf55_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxf55_status *status;


	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 4) * status->exp_step;
	} else {
		uint32_t tmp1, tmp2, tmp3;

		tmp1 = (uint32_t)((vts - 10) / ratio[0] + 1);
		tmp2 = (vts - 10) - (status->size_h * 2);
		tmp3 = 511;

		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		tmp1 = tmp1 < tmp3 ? tmp1 : tmp3;

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = ((8 * 2) - 6) * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct jxf55_status *status)
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
	else if(fAGain>=8.0 && fAGain<=15.5){
		wAgainReg = (int)(2.0f*(fAGain-8.0) + 48.0);
	}
	else
		wAgainReg = 0x3f;

	return wAgainReg;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	float fAgainReg;

	if(wAGain>=0 && wAGain<16){
		fAgainReg = (float)((float)wAGain/16.0 + 1);
	}
	else if(wAGain>=16 && wAGain<32){
		fAgainReg = (float)((float)wAGain/8.0);
	}
	else if(wAGain>=32 && wAGain<48){
		fAgainReg = (float)((float)wAGain/4.0 - 4);
	}
	else if(wAGain>=48 && wAGain<63){
		fAgainReg = (float)((float)wAGain/2.0 - 16);
	}
	else
		fAgainReg = 15.5;

	return (fAgainReg);
}
static int jxf55_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct jxf55_status *status;

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

static int jxf55_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct jxf55_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	status = &g_status[isp_id];

	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int jxf55_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct jxf55_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exp_lines[2];
	uint16_t gain_reg;
	float gain;
	uint16_t frame_length;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain = exp_gain->analog_gain[0] * exp_gain->digital_gain[0];
	gain_reg = get_sensor_gain_reg(gain, status);

	reg = regs->reg;

	frame_length = exp_gain->vts;
	if (status->hdr == LINEAR_MODE) {
		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x23, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x22, frame_length & 0xff);

			status->last_vts = frame_length;
		}

		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
			set_sync_i2c(&reg[i++], 0x02, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exp_lines[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
	} else {
		for (i = 0; i < 2; i++) {
			exp_lines[i] = (exp_gain->exposure[i] /
					       status->exp_step + 0.5f);
		}

		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x23, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x22, frame_length & 0xff);

			status->last_vts = frame_length;
		}

		/* set exposure */
		/* short exposure*/
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			//set_sync_i2c(&reg[i++], 0x08, (exp_lines[1] >> 8) << 7);
			set_sync_i2c(&reg[i++], 0x08, (exp_lines[1] >> 8) & 0x01);
			set_sync_i2c(&reg[i++], 0x05, exp_lines[1] & 0xff);

			status->last_exposure[1] = exp_gain->exposure[1];
		}

		/* long exposure*/
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x02, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exp_lines[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
	}

	/* set gain */
	if (abs(status->last_gain - gain_reg) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x00, gain_reg);

		status->last_gain = gain_reg;
	}
	regs->num = i;

	return RTS_ISP_OK;
}

static int jxf55_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	int regtmp;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct jxf55_status *status;

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

static int jxf55_check(uint32_t isp_id)
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

	if (id == 0x0855)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int jxf55_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops jxf55_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "jxf55",

	.get_info = jxf55_get_info,
	.get_init_info = jxf55_get_init_info,
	.start = jxf55_start,
	.get_exposure_range = jxf55_get_exposure_range,
	.get_tuned_again = jxf55_get_tuned_again,
	.get_tuned_dgain = jxf55_get_tuned_dgain,
	.get_exposure_gain_info = jxf55_get_exposure_gain_info,
	.set_mirror_flip = jxf55_set_mirror_flip,
	.check = jxf55_check,
	.get_slave_addr_num = jxf55_get_slave_addr_num,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &jxf55_ops;
}

//#endif
