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

struct sc231h_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct sc231h_gain_config {
	uint8_t reg_3e08;
	uint8_t reg_3e09;
	uint16_t gainValue;
};

static struct sc231h_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_sc231h_fps_info_asic[] = {
	{30.0f, 2200, 79200000},
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
static struct sc231h_gain_config g_sc231h_gain_config[] = {
//   0x3E08,0x3e09,Gain(16=1x)
	{0x00,	0x20,	16},	//1x
	{0x01,  0x20,	32},	//2x
	{0x01,  0x30,	48},	//3x
	{0x01,  0x38,	56},	//3.5x
	{0x80,  0x34,	96},	//6x
	{0x81,  0x23,	128},	//8x
	{0x81,  0x34,	192},	//12x
	{0x83,  0x24,	266},	//16.65x
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


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_sc231h_fps_info_asic[0].fps;
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
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 8000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *sc231h_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_sc231h_fps_info_asic); i++)
		if (fps == g_sc231h_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_sc231h_fps_info_asic))
		return NULL;
	return &g_sc231h_fps_info_asic[i];

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

	fps_info = sc231h_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	set_init_i2c_regs(info->sensor_regs[0], g_sc231h_i2c_init_regs_asic, 0);
	
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
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1200;
	info->max_vts = info->min_vts * 30;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int sc231h_start(uint32_t isp_id)
{
	struct sc231h_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
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

static uint16_t get_sensor_gain_reg(float fAGain, struct sc231h_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	
	if (gain >= 512) {	//32x
		gain = 512;
		status->num = 5;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc231h_gain_config) - 1; i++) {
			if (gain >= g_sc231h_gain_config[i].gainValue &&
			    gain < g_sc231h_gain_config[i + 1].gainValue) {
				gain = g_sc231h_gain_config[i].gainValue;
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
static int sc231h_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct sc231h_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int sc231h_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
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
	set_sync_i2c(&reg[i++], 0x3e08, g_sc231h_gain_config[status->num].reg_3e08);
	set_sync_i2c(&reg[i++], 0x3e09, g_sc231h_gain_config[status->num].reg_3e09);
	set_sync_i2c(&reg[i++], 0x320E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x320F, vts & 0xff);
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