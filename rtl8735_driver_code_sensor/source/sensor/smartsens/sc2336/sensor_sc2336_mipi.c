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

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct sc2336_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct sc2336_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct sc2336_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_sc2336_fps_info_asic[] = {
	{30.0f, 2200, 74250000},
};

static struct rts_isp_i2c_reg g_sc2336_i2c_init_regs_asic[] = {
	{0x0103,0x01},
	{0x0100,0x00},
	{0x36e9,0x80},
	{0x37f9,0x80},
	{0x301f,0x1a},
	{0x3106,0x05},
	{0x3200,0x00},
	{0x3201,0x00},
	{0x3202,0x00},
	{0x3203,0x00},
	{0x3204,0x07},
	{0x3205,0x8b},
	{0x3206,0x04},
	{0x3207,0x43},
	{0x3208,0x07},
	{0x3209,0x88},
	{0x320a,0x04},
	{0x320b,0x40},
	{0x320c,0x08},
	{0x320d,0x98},
	{0x3210,0x00},
	{0x3211,0x02},
	{0x3212,0x00},
	{0x3213,0x02},
	{0x3248,0x04},
	{0x3249,0x0b},
	{0x3253,0x08},
	{0x3301,0x09},
	{0x3302,0xff},
	{0x3303,0x10},
	{0x3306,0x60},
	{0x3307,0x02},
	{0x330a,0x01},
	{0x330b,0x10},
	{0x330c,0x16},
	{0x330d,0x90},
	{0x3318,0x02},
	{0x3321,0x0a},
	{0x3327,0x0e},
	{0x332b,0x12},
	{0x3333,0x10},
	{0x3334,0x40},
	{0x335e,0x06},
	{0x335f,0x0a},
	{0x3364,0x1f},
	{0x337c,0x02},
	{0x337d,0x0e},
	{0x3390,0x09},
	{0x3391,0x0f},
	{0x3392,0x1f},
	{0x3393,0x20},
	{0x3394,0x20},
	{0x3395,0xff},
	{0x33a2,0x04},
	{0x33b1,0x80},
	{0x33b2,0x68},
	{0x33b3,0x42},
	{0x33f9,0x70},
	{0x33fb,0xd0},
	{0x33fc,0x0f},
	{0x33fd,0x1f},
	{0x349f,0x03},
	{0x34a6,0x0f},
	{0x34a7,0x1f},
	{0x34a8,0x42},
	{0x34a9,0x06},
	{0x34aa,0x01},
	{0x34ab,0x23},
	{0x34ac,0x01},
	{0x34ad,0x84},
	{0x3630,0xf4},
	{0x3633,0x22},
	{0x3639,0xf4},
	{0x363c,0x47},
	{0x3670,0x09},
	{0x3674,0xf4},
	{0x3675,0xfb},
	{0x3676,0xed},
	{0x367c,0x09},
	{0x367d,0x0f},
	{0x3690,0x33},
	{0x3691,0x33},
	{0x3692,0x43},
	{0x3698,0x89},
	{0x3699,0x96},
	{0x369a,0xD0},
	{0x369b,0xD0},
	{0x369c,0x09},
	{0x369d,0x0f},
	{0x36a2,0x09},
	{0x36a3,0x0f},
	{0x36a4,0x1f},
	{0x36d0,0x01},
	{0x3722,0xE1},
	{0x3724,0x41},
	{0x3725,0xc1},
	{0x3728,0x20},
	{0x3900,0x0d},
	{0x3905,0x98},
	{0x391b,0x81},
	{0x391c,0x10},
	{0x3933,0x81},
	{0x3934,0xc9},
	{0x3940,0x6d},
	{0x3942,0x01},
	{0x3943,0xcb},
	{0x3952,0x02},
	{0x3953,0x0f},
	{0x3e01,0x46},
	{0x3e08,0x1f},
	{0x3e1b,0x14},
	{0x440e,0x02},
	{0x4509,0x38},
	{0x5799,0x06},
	{0x5ae0,0xfe},
	{0x5ae1,0x40},
	{0x5ae2,0x30},
	{0x5ae3,0x28},
	{0x5ae4,0x20},
	{0x5ae5,0x30},
	{0x5ae6,0x28},
	{0x5ae7,0x20},
	{0x5ae8,0x3c},
	{0x5ae9,0x30},
	{0x5aea,0x28},
	{0x5aeb,0x3c},
	{0x5aec,0x30},
	{0x5aed,0x28},
	{0x5aee,0xfe},
	{0x5aef,0x40},
	{0x5af4,0x30},
	{0x5af5,0x28},
	{0x5af6,0x20},
	{0x5af7,0x30},
	{0x5af8,0x28},
	{0x5af9,0x20},
	{0x5afa,0x3c},
	{0x5afb,0x30},
	{0x5afc,0x28},
	{0x5afd,0x3c},
	{0x5afe,0x30},
	{0x5aff,0x28},
	{0x36e9,0x20},
	{0x37f9,0x27},
	/*2021.11.12 Zako Update for Mipi Test*/
	{0x4800,0x44},//continue mode
	{0x3250,0x40},
	/*D2021.11.12 Done*/
	{0x0100,0x01},
};
static struct sc2336_gain_config g_sc2336_gain_config[] = {
//   0x3E09 Gain(16=1x)
	{0x00,  16},
	{0x08,  32},
	{0x09,  64},
	{0x0B,  128},
	{0x0F,  256},
	{0x1F,  512},
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x30	//0x60(default)
#define SLAVE_ADDR_1 0x32	//0x64

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int sc2336_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_sc2336_fps_info_asic[0].fps;
	info->modes.num = 1;

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
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 8000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *sc2336_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_sc2336_fps_info_asic); i++)
		if (fps == g_sc2336_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_sc2336_fps_info_asic))
		return NULL;
	return &g_sc2336_fps_info_asic[i];

}

static int sc2336_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc2336_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("sc2336 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = sc2336_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	set_init_i2c_regs(info->sensor_regs[0], g_sc2336_i2c_init_regs_asic, 0);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 4;
	info->start.y = 3;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1125;
	//info->max_vts = 6750;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int sc2336_start(uint32_t isp_id)
{
	struct sc2336_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct sc2336_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	
	if (gain >= 512) {	//32x
		gain = 512;
		status->num = 5;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc2336_gain_config) - 1; i++) {
			if (gain >= g_sc2336_gain_config[i].gainValue &&
			    gain < g_sc2336_gain_config[i + 1].gainValue) {
				gain = g_sc2336_gain_config[i].gainValue;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 16.0f;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}
static int sc2336_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc2336_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int sc2336_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int sc2336_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct sc2336_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	
	i = 0;
	//set_sync_i2c(&reg[i++], 0x3812, 0x00);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = exposure_rows << 4;
		set_sync_i2c(&reg[i++], 0x3e00, (exposure_rows & 0xff0000) >> 16);
		set_sync_i2c(&reg[i++], 0x3e01, (exposure_rows & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3e02, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x3e09, g_sc2336_gain_config[status->num].regValue);
	set_sync_i2c(&reg[i++], 0x320E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x320F, vts & 0xff);
	//set_sync_i2c(&reg[i++], 0x3812, 0x30);
	regs->num = i;
	return RTS_ISP_OK;
}

static int sc2336_set_mirror_flip(uint32_t isp_id,
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
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int sc2336_check(uint32_t isp_id)
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

	
	if (id == 0xcb3a)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int sc2336_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops sc2336_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc2336",

	.get_info = sc2336_get_info,
	.get_init_info = sc2336_get_init_info,
	.start = sc2336_start,
	.get_tuned_again = sc2336_get_tuned_again,
	.get_tuned_dgain = sc2336_get_tuned_dgain,
	.get_exposure_gain_info = sc2336_get_exposure_gain_info,
	.set_mirror_flip = sc2336_set_mirror_flip,
	.check = sc2336_check,
	.get_slave_addr_num = sc2336_get_slave_addr_num,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc2336_ops;
}
