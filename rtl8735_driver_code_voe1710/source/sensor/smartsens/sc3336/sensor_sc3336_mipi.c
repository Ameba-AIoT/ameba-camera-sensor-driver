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

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct sc3336_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct sc3336_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct sc3336_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_sc3336_fps_info_asic[] = {
	{30.0f, 2500, 102000000},
};

static struct rts_isp_i2c_reg g_sc3336_i2c_init_regs_asic[] = {
	//cleaned_0x02_SC3336_MIPI_24Minput_2Lane_10bit_510Mbps_2304x1296_30fps.ini
	{0x0103,0x01},
	{0x36e9,0x80},
	{0x37f9,0x80},
	{0x301f,0x02},
	{0x30b8,0x33},
	{0x320e,0x05},	//1360
	{0x320f,0x50},
	{0x3253,0x10},
	{0x325f,0x20},
	{0x3301,0x04},
	{0x3306,0x50},
	{0x3309,0xa8},
	{0x330a,0x00},
	{0x330b,0xd8},
	{0x3314,0x13},
	{0x331f,0x99},
	{0x3333,0x10},
	{0x3334,0x40},
	{0x335e,0x06},
	{0x335f,0x0a},
	{0x3364,0x5e},
	{0x337c,0x02},
	{0x337d,0x0e},
	{0x3390,0x01},
	{0x3391,0x03},
	{0x3392,0x07},
	{0x3393,0x04},
	{0x3394,0x04},
	{0x3395,0x04},
	{0x3396,0x08},
	{0x3397,0x0b},
	{0x3398,0x1f},
	{0x3399,0x04},
	{0x339a,0x0a},
	{0x339b,0x3a},
	{0x339c,0xa0},
	{0x33a2,0x04},
	{0x33ac,0x08},
	{0x33ad,0x1c},
	{0x33ae,0x10},
	{0x33af,0x30},
	{0x33b1,0x80},
	{0x33b3,0x48},
	{0x33f9,0x60},
	{0x33fb,0x74},
	{0x33fc,0x4b},
	{0x33fd,0x5f},
	{0x349f,0x03},
	{0x34a6,0x4b},
	{0x34a7,0x5f},
	{0x34a8,0x20},
	{0x34a9,0x18},
	{0x34ab,0xe8},
	{0x34ac,0x01},
	{0x34ad,0x00},
	{0x34f8,0x5f},
	{0x34f9,0x18},
	{0x3630,0xc0},
	{0x3631,0x84},
	{0x3632,0x64},
	{0x3633,0x32},
	{0x363b,0x03},
	{0x363c,0x08},
	{0x3641,0x38},
	{0x3670,0x4e},
	{0x3674,0xc0},
	{0x3675,0xc0},
	{0x3676,0xc0},
	{0x3677,0x86},
	{0x3678,0x86},
	{0x3679,0x86},
	{0x367c,0x48},
	{0x367d,0x49},
	{0x367e,0x4b},
	{0x367f,0x5f},
	{0x3690,0x32},
	{0x3691,0x32},
	{0x3692,0x42},
	{0x369c,0x4b},
	{0x369d,0x5f},
	{0x36b0,0x87},
	{0x36b1,0x90},
	{0x36b2,0xa1},
	{0x36b3,0xd8},
	{0x36b4,0x49},
	{0x36b5,0x4b},
	{0x36b6,0x4f},
	{0x36ea,0x11},
	{0x36eb,0x0d},
	{0x36ec,0x1c},
	{0x36ed,0x26},
	{0x370f,0x01},
	{0x3722,0x09},
	{0x3724,0x41},
	{0x3725,0xc1},
	{0x3771,0x09},
	{0x3772,0x09},
	{0x3773,0x05},
	{0x377a,0x48},
	{0x377b,0x5f},
	{0x37fa,0x11},
	{0x37fb,0x33},
	{0x37fc,0x11},
	{0x37fd,0x08},
	{0x3904,0x04},
	{0x3905,0x8c},
	{0x391d,0x04},
	{0x3921,0x20},
	{0x3926,0x21},
	{0x3933,0x80},
	{0x3934,0x0a},
	{0x3935,0x00},
	{0x3936,0x2a},
	{0x3937,0x6a},
	{0x3938,0x6a},
	{0x39dc,0x02},
	{0x3e01,0x54},
	{0x3e02,0x80},
	{0x3e09,0x00},
	{0x440d,0x10},
	{0x440e,0x01},
	{0x4509,0x20},
	{0x5ae0,0xfe},
	{0x5ae1,0x40},
	{0x5ae2,0x38},
	{0x5ae3,0x30},
	{0x5ae4,0x28},
	{0x5ae5,0x38},
	{0x5ae6,0x30},
	{0x5ae7,0x28},
	{0x5ae8,0x3f},
	{0x5ae9,0x34},
	{0x5aea,0x2c},
	{0x5aeb,0x3f},
	{0x5aec,0x34},
	{0x5aed,0x2c},
	{0x36e9,0x54},
	{0x37f9,0x47},
	{0x3213,0x03},
	{0x0100,0x01},
};
static struct sc3336_gain_config g_sc3336_gain_config[] = {
//   0x3E09 Gain(64=1x)
	{0x00,  64},
	{0x40,  97},
	{0x48,  194},
	{0x49,  389},
	{0x4B,  778},
	{0x4F,  1556},
	{0x5F,  3113},
};
static int sc3336_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2304;
	info->modes.mode[0].size.h = 1296;
	info->modes.mode[0].fps = g_sc3336_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x30;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 6000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *sc3336_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_sc3336_fps_info_asic); i++)
		if (fps == g_sc3336_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_sc3336_fps_info_asic))
		return NULL;
	return &g_sc3336_fps_info_asic[i];

}

static int sc3336_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc3336_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("sc3336 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = sc3336_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	set_init_i2c_regs(info->sensor_regs[0], g_sc3336_i2c_init_regs_asic, 0);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 2304;
	info->size.h = 1296;
	info->start.x = 0;
	info->start.y = 0;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1360;
	//info->max_vts = 6750;
	info->max_vts = info->min_vts * 15;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int sc3336_start(uint32_t isp_id)
{
	struct sc3336_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int sc3336_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct sc3336_status *status;

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

static uint16_t get_sensor_gain_reg(float fAGain, struct sc3336_status *status)
{
	int i;
	uint16_t gain = fAGain * 64;
	
	if (gain >= 3113) {	//32x
		gain = 3113;
		status->num = 6;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc3336_gain_config) - 1; i++) {
			if (gain >= g_sc3336_gain_config[i].gainValue &&
			    gain < g_sc3336_gain_config[i + 1].gainValue) {
				gain = g_sc3336_gain_config[i].gainValue;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 64.0f;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}
static int sc3336_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc3336_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int sc3336_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int sc3336_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct sc3336_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows;

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
	set_sync_i2c(&reg[i++], 0x3e09, g_sc3336_gain_config[status->num].regValue);
	set_sync_i2c(&reg[i++], 0x320E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x320F, vts & 0xff);
	//set_sync_i2c(&reg[i++], 0x3812, 0x30);
	regs->num = i;
	return RTS_ISP_OK;
}

static int sc3336_set_mirror_flip(uint32_t isp_id,
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

static int sc3336_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

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
	
	if (id == 0xcc41)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops sc3336_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc3336",

	.get_info = sc3336_get_info,
	.get_init_info = sc3336_get_init_info,
	.start = sc3336_start,
	//.get_exposure_range = sc3336_get_exposure_range,
	.get_tuned_again = sc3336_get_tuned_again,
	.get_tuned_dgain = sc3336_get_tuned_dgain,
	.get_exposure_gain_info = sc3336_get_exposure_gain_info,
	.set_mirror_flip = sc3336_set_mirror_flip,
	.check = sc3336_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc3336_ops;
}