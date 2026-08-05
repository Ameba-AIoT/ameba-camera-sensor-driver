/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Eric Yang <eric_yang@realsil.com.cn>
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

struct gc1084_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
};

struct gc1084_gain_config {
	uint8_t reg_00d1;
	uint8_t reg_00d0;
	uint8_t reg_0dc1;
	uint8_t reg_00b8;
	uint8_t reg_00b9;
	uint8_t reg_0155;
	uint16_t value;
};

static struct gc1084_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc1084_fps_info[] = {
	{30, 1760, 39600000},
};

static struct rts_isp_i2c_reg g_gc1084_i2c_init_regs[] = {
	//mclk=27mhz
	//Mipi_clk=396Mbps/lane
	//HB=2200,FL=750
	//Rowtime=44.444us,frame rate=30FPS
	//window size:1280x720
	//bayer :GRBG
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0x00},
	{0x03f2,0x00},
	{0x03f3,0x00},
	{0x03f4,0x36},
	{0x03f5,0xc0},
	{0x03f6,0x13},
	{0x03f7,0x01},
	{0x03f8,0x2c},
	{0x03f9,0x21},
	{0x03fc,0xae},
	{0x0d05,0x08},
	{0x0d06,0x98},
	{0x0d08,0x10},
	{0x0d0a,0x02},
	{0x000c,0x03},
	{0x0d0d,0x02},
	{0x0d0e,0xd4},
	{0x000f,0x05},
	{0x0010,0x08},
	{0x0017,0x08},
	{0x0d73,0x92},
	{0x0076,0x00},
	{0x0d76,0x00},
	{0x0d41,0x02},
	{0x0d42,0xee},
	{0x0d7a,0x0a},
	{0x006b,0x18},
	{0x0db0,0x9d},
	{0x0db1,0x00},
	{0x0db2,0xac},
	{0x0db3,0xd5},
	{0x0db4,0x00},
	{0x0db5,0x97},
	{0x0db6,0x09},
	{0x00d2,0xfc},
	{0x0d19,0x31},
	{0x0d20,0x40},
	{0x0d25,0xcb},
	{0x0d27,0x03},
	{0x0d29,0x40},
	{0x0d43,0x20},
	{0x0058,0x60},
	{0x00d6,0x66},
	{0x00d7,0x19},
	{0x0093,0x02},
	{0x00d9,0x14},
	{0x00da,0xc1},
	{0x0d2a,0x00},
	{0x0d28,0x04},
	{0x0dc2,0x84},
	{0x0050,0x30},
	{0x0080,0x07},
	{0x008c,0x05},
	{0x008d,0xa8},
	{0x0077,0x01},
	{0x0078,0xee},
	{0x0079,0x02},
	{0x0067,0xc0},
	{0x0054,0xff},
	{0x0055,0x02},
	{0x0056,0x00},
	{0x0057,0x04},
	{0x005a,0xff},
	{0x005b,0x07},
	{0x00d5,0x03},
	{0x0102,0xa9},
	{0x0d03,0x02},
	{0x0d04,0xd0},
	{0x007a,0x60},
	{0x04e0,0xff},
	{0x0414,0x75},
	{0x0415,0x75},
	{0x0416,0x75},
	{0x0417,0x75},
	{0x0122,0x00},
	{0x0121,0x80},
	{0x0428,0x10},
	{0x0429,0x10},
	{0x042a,0x10},
	{0x042b,0x10},
	{0x042c,0x14},
	{0x042d,0x14},
	{0x042e,0x18},
	{0x042f,0x18},
	{0x0430,0x05},
	{0x0431,0x05},
	{0x0432,0x05},
	{0x0433,0x05},
	{0x0434,0x05},
	{0x0435,0x05},
	{0x0436,0x05},
	{0x0437,0x05},
	{0x0153,0x00},
	{0x0190,0x01},
	{0x0192,0x02},
	{0x0194,0x04},
	{0x0195,0x02},	//720
	{0x0196,0xd0},
	{0x0197,0x05},	//1280
	{0x0198,0x00},
	{0x0201,0x23},
	{0x0202,0x53},
	{0x0203,0xce},
	{0x0208,0x39},
	{0x0212,0x06},
	{0x0213,0x40},
	{0x0215,0x12},
	{0x0229,0x05},
	{0x023e,0x98},
	{0x031e,0x3e},
};

static struct gc1084_gain_config g_gc1084_gain_config[] = {
// 0x00d1, 0x00d0, 0x0dc1, 0x00b8, 0x00b9, 0x0155, value
	{0x00,   0x00,   0x00,   0x01,   0x00,   0x00, 64},
	{0x0A,   0x00,   0x00,   0x01,   0x0c,   0x00, 76},
	{0x00,   0x01,   0x00,   0x01,   0x1a,   0x00, 90},
	{0x0A,   0x01,   0x00,   0x01,   0x2a,   0x00, 106},
	{0x00,   0x02,   0x00,   0x02,   0x00,   0x00, 128},
	{0x0A,   0x02,   0x00,   0x02,   0x18,   0x00, 152},
	{0x00,   0x03,   0x00,   0x02,   0x33,   0x00, 179},
	{0x0A,   0x03,   0x00,   0x03,   0x14,   0x00, 212},
	{0x00,   0x04,   0x00,   0x04,   0x00,   0x02, 256},
	{0x0A,   0x04,   0x00,   0x04,   0x2f,   0x02, 303},
	{0x00,   0x05,   0x00,   0x05,   0x26,   0x02, 358},
	{0x0A,   0x05,   0x00,   0x06,   0x29,   0x02, 425},
	{0x00,   0x06,   0x00,   0x08,   0x00,   0x02, 512},
	{0x0A,   0x06,   0x00,   0x09,   0x1f,   0x04, 607},
	{0x12,   0x46,   0x00,   0x0b,   0x0d,   0x04, 717},
	{0x19,   0x66,   0x00,   0x0d,   0x12,   0x06, 849},
	{0x00,   0x04,   0x01,   0x10,   0x00,   0x06, 1024},
	{0x0A,   0x04,   0x01,   0x12,   0x3e,   0x08, 1213},
	{0x00,   0x05,   0x01,   0x16,   0x1a,   0x0a, 1434},
	{0x0A,   0x05,   0x01,   0x1a,   0x23,   0x0c, 1699},
	{0x00,   0x06,   0x01,   0x20,   0x00,   0x0c, 2048},
	{0x0A,   0x06,   0x01,   0x25,   0x3b,   0x0f, 2427},
	{0x12,   0x46,   0x01,   0x2c,   0x33,   0x12, 2867},
	{0x19,   0x66,   0x01,   0x35,   0x06,   0x14, 3398},
	{0x20,   0x06,   0x01,   0x3f,   0x3f,   0x15, 4096},
};   
                                  
static int gc1084_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{                                            
	int i;                                   
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
                                             
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1280;
	info->modes.mode[0].size.h = 720;
	info->modes.mode[0].fps = g_gc1084_fps_info[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x37;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;
	
	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 3000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *gc1084_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_gc1084_fps_info); i++)
		if (fps == g_gc1084_fps_info[i].fps)
			break;
	if (i == ARRAY_SIZE(g_gc1084_fps_info))
		return NULL;

	return &g_gc1084_fps_info[i];
}

static int gc1084_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc1084_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc1084_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;


	set_init_i2c_regs(info->sensor_regs[0], g_gc1084_i2c_init_regs, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0;
	info->interface.mipi.hs_term = 0x6;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 1280;
	info->size.h = 720;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = 750;
	info->max_vts = 65535 - info->min_vts;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	status->min_vts = info->min_vts;
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int gc1084_start(uint32_t isp_id)
{
	struct gc1084_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc1084_status *status)
{
	int i;
	uint16_t gain = fgain * 64;

	if (gain >= 1024) {
		gain = 1024;
		status->num = 16;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc1084_gain_config) - 1; i++) {
			if (gain >= g_gc1084_gain_config[i].value &&
			    gain < g_gc1084_gain_config[i + 1].value) {
				gain = g_gc1084_gain_config[i].value;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 64.0f;
}

static int gc1084_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc1084_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int gc1084_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int gc1084_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct gc1084_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	i = 0;
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x0d03, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0d04, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x00d1,
				g_gc1084_gain_config[status->num].reg_00d1);
	set_sync_i2c(&reg[i++], 0x00d0,
				g_gc1084_gain_config[status->num].reg_00d0);
	set_sync_i2c(&reg[i++], 0x031d, 0x2e);
	set_sync_i2c(&reg[i++], 0x0dc1,
				g_gc1084_gain_config[status->num].reg_0dc1);
	set_sync_i2c(&reg[i++], 0x031d,	0x28);
	set_sync_i2c(&reg[i++], 0x00b8,
				g_gc1084_gain_config[status->num].reg_00b8);
	set_sync_i2c(&reg[i++], 0x00b9,
				g_gc1084_gain_config[status->num].reg_00b9);
	set_sync_i2c(&reg[i++], 0x0155,
				g_gc1084_gain_config[status->num].reg_0155);
	set_sync_i2c(&reg[i++], 0x0340, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0341, vts & 0xff);
	regs->num = i;
	return RTS_ISP_OK;
}

static int gc1084_set_mirror_flip(uint32_t isp_id,
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
            set_sync_i2c(&reg[i++], 0x0015, 0x00);
            set_sync_i2c(&reg[i++], 0x0d15, 0x00);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x0015, 0x02);
            set_sync_i2c(&reg[i++], 0x0d15, 0x02);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x0015, 0x01);
            set_sync_i2c(&reg[i++], 0x0d15, 0x01);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x0015, 0x03);
            set_sync_i2c(&reg[i++], 0x0d15, 0x03);
			break;
	#else
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x0015, 0x03);
            set_sync_i2c(&reg[i++], 0x0d15, 0x03);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x0015, 0x01);
            set_sync_i2c(&reg[i++], 0x0d15, 0x01);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x0015, 0x02);
            set_sync_i2c(&reg[i++], 0x0d15, 0x02);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x0015, 0x00);
            set_sync_i2c(&reg[i++], 0x0d15, 0x00);
			break;
	#endif
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int gc1084_check(uint32_t isp_id)
{
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

	if (id == 0x1084)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops gc1084_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc1084",
	.get_info = gc1084_get_info,
	.get_init_info = gc1084_get_init_info,
	.start = gc1084_start,
	.get_tuned_again = gc1084_get_tuned_again,
	.get_tuned_dgain = gc1084_get_tuned_dgain,
	.get_exposure_gain_info = gc1084_get_exposure_gain_info,
	.set_mirror_flip = gc1084_set_mirror_flip,
	.check = gc1084_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc1084_ops;
}

//#endif
