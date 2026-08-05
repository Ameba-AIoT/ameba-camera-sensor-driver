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

#define ORIENTATION 	 0	//0=default, 1=rotate180
#define SENSOR_GAIN_FULL 0	//0=16x, 1=64x
#if (SENSOR_GAIN_FULL == 1)
#define ANALOG_GAIN_MAX_RATIO (float)64.f	/* Max sensor gain ratio => 4096/64 = 64.0x */
#else
#define ANALOG_GAIN_MAX_RATIO (float)16.f	/* Max sensor gain ratio => 1024/64 = 16.0x */
#endif

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct gc3003_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
};

struct gc3003_gain_config {
	uint8_t reg_00d1;
	uint8_t reg_00d0;
	uint8_t reg_00b8;
	uint8_t reg_00b9;
	uint8_t reg_0155;
	uint8_t reg_006e;
	uint8_t reg_0080;
	uint16_t value;
};

static struct gc3003_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc3003_fps_info[] = {
	{30, 3144, 126400000},
};

static struct rts_isp_i2c_reg g_gc3003_i2c_init_regs[] = {
	//release_v1.0_2lane_10bit_2304x1296_30fps_24mhz_GC3003.txt
	//mclk 24Mhz
	//mipi_data rate=632Mbps/lane
	//vts = 1340
	//window_size=2304x1296
	//row time=24.889us
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0x00},
	{0x03f3,0x00},
	{0x03f5,0xc0},
	{0x03f6,0x06},
	{0x03f7,0x01},
	{0x03f8,0x4f},
	{0x03f9,0x13},
	{0x03fa,0x00},
	{0x03e0,0x16},
	{0x03e1,0x0d},
	{0x03e2,0x36},
	{0x03e4,0x08},
	{0x03fc,0xce},
	{0x0d05,0x05},
	{0x0d06,0x40},
	{0x0d76,0x00},
	{0x0d41,0x05},
	{0x0d42,0x3c},
	{0x0d0a,0x02},
	{0x000c,0x02},
	{0x0d0d,0x05},
	{0x0d0e,0x18},
	{0x000f,0x09},
	{0x0010,0x08},
	{0x0017,0x0c},
	{0x0d53,0x12},
	{0x0051,0x03},
	{0x0082,0x01},
	{0x0086,0x20}, 
	{0x008a,0x01},
	{0x008b,0x1d}, 
	{0x008c,0x05}, 
	{0x008d,0xd0}, 
	{0x0db7,0x01}, 
	{0x0db0,0x05},  
	{0x0db1,0x00},      
	{0x0db2,0x04}, 
	{0x0db3,0x54}, 
	{0x0db4,0x00},      
	{0x0db5,0x17},   
	{0x0db6,0x08},   
	{0x0d25,0xcb}, 
	{0x0d4a,0x04}, 
	{0x00d2,0x70},  
	{0x00d7,0x19},  
	{0x00d9,0x10}, 
	{0x00da,0xc1},
	{0x0d55,0x1b},
	{0x0d92,0x17},
	{0x0dc2,0x30},
	{0x0d2a,0x30},
	{0x0d19,0x51},
	{0x0d29,0x30},
	{0x0d20,0x30},
	{0x0d72,0x12},
	{0x0d4e,0x12},
	{0x0d43,0x20},
	{0x0050,0x0c},
	{0x006e,0x03},
	{0x0153,0x50},
	{0x0192,0x02},  //04
	{0x0194,0x02},  //04
	{0x0195,0x05},	//510 = 1296
	{0x0196,0x14},	//10 
	{0x0197,0x09},	//900 = 2304
	{0x0198,0x04}, 	//00
	{0x0077,0x01}, 
	{0x0078,0x65}, 
	{0x0079,0x04}, 
	{0x0067,0xc0}, 
	{0x0054,0xff}, 
	{0x0055,0x02}, 
	{0x0056,0x00}, 
	{0x0057,0x04},
	{0x005a,0xff},
	{0x005b,0x07},
	{0x00d5,0x03},
	{0x0102,0x10},
	{0x0d4a,0x04},
	{0x04e0,0xff},
	{0x031e,0x3e},
	{0x0159,0x01},
	{0x014f,0x28},
	{0x0150,0x40},
	{0x0026,0x00},
	{0x0d26,0xa0}, 
	{0x0414,0x74},
	{0x0415,0x74},
	{0x0416,0x74},
	{0x0417,0x74},
	{0x0155,0x00},
	{0x0170,0x3e},
	{0x0171,0x3e},
	{0x0172,0x3e},
	{0x0173,0x3e},
	{0x0428,0x0b},
	{0x0429,0x0b},
	{0x042a,0x0b},
	{0x042b,0x0b},
	{0x042c,0x0b},
	{0x042d,0x0b},
	{0x042e,0x0b},
	{0x042f,0x0b}, //b_use
	{0x0430,0x05},
	{0x0431,0x05},
	{0x0432,0x05},
	{0x0433,0x05},
	{0x0434,0x04},
	{0x0435,0x04},
	{0x0436,0x04},
	{0x0437,0x04}, //a_use
	{0x0438,0x18},
	{0x0439,0x18},
	{0x043a,0x18},
	{0x043b,0x18},
	{0x043c,0x1d},
	{0x043d,0x20},
	{0x043e,0x22},
	{0x043f,0x24}, //d_use
	{0x0468,0x04},
	{0x0469,0x04},
	{0x046a,0x04},
	{0x046b,0x04},
	{0x046c,0x04},
	{0x046d,0x04},
	{0x046e,0x04},
	{0x046f,0x04}, //c_use
	{0x0108,0xf0},
	{0x0109,0x80}, 
	{0x0d03,0x05},
	{0x0d04,0x00},
	{0x007a,0x60},
	{0x00d0,0x00},
	{0x0080,0x09},
	{0x0291,0x0f},
	{0x0292,0xff},
	{0x0201,0x27},
	{0x0202,0x53},
	{0x0203,0x4e},
	{0x0206,0x03},
	{0x0212,0x0b},
	{0x0213,0x40},
	{0x0215,0x12},
	{0x023e,0x99},
	{0x03fe,0x10},
	{0x0183,0x09},
	{0x0187,0x51},
	{0x0d22,0x04},
	{0x0d21,0x3C},
	{0x0d03,0x01},
	{0x0d04,0x28},
	{0x0d23,0x0e},
	{0x03fe,0x00},
};

static struct gc3003_gain_config g_gc3003_gain_config[] = {
//   00d1  00d0  00b8  00b9  0155  006e  0080  gain
	{ 0x00, 0x00, 0x01, 0x00, 0x04, 0x03, 0x09, 64},//1.00
	{ 0x0A, 0x00, 0x01, 0x0c, 0x04, 0x03, 0x0b, 76},//1.18
	{ 0x00, 0x01, 0x01, 0x1a, 0x04, 0x03, 0x0d, 90},//1.40
	{ 0x0A, 0x01, 0x01, 0x2a, 0x04, 0x04, 0x10, 106},//1.65
	{ 0x20, 0x00, 0x02, 0x00, 0x04, 0x05, 0x17, 128},//2.00
	{ 0x25, 0x00, 0x02, 0x18, 0x04, 0x06, 0x1e, 152},//2.37
	{ 0x20, 0x01, 0x02, 0x33, 0x04, 0x07, 0x22, 179},//2.79
	{ 0x25, 0x01, 0x03, 0x14, 0x04, 0x08, 0x28, 212},//3.31
	{ 0x30, 0x00, 0x04, 0x00, 0x04, 0x08, 0x2c, 256},//4.00
	{ 0x32, 0x80, 0x04, 0x2f, 0x04, 0x08, 0x2e, 303},//4.73
	{ 0x30, 0x01, 0x05, 0x26, 0x04, 0x08, 0x2f, 358},//5.59
	{ 0x32, 0x81, 0x06, 0x29, 0x04, 0x08, 0x30, 425},//6.64
	{ 0x38, 0x00, 0x08, 0x00, 0x04, 0x07, 0x2f, 512},//8.00
	{ 0x39, 0x40, 0x09, 0x1f, 0x06, 0x07, 0x2e, 607},//9.48
	{ 0x38, 0x01, 0x0b, 0x0d, 0x06, 0x06, 0x2b, 717},//11.18
	{ 0x39, 0x41, 0x0d, 0x12, 0x06, 0x04, 0x24, 849},//13.25
	{ 0x30, 0x08, 0x10, 0x00, 0x06, 0x03, 0x27, 1024},//16.00
#if (SENSOR_GAIN_FULL == 1)
	{ 0x32, 0x88, 0x12, 0x3e, 0x06, 0x03, 0x29, 1213},//18.96
	{ 0x30, 0x09, 0x16, 0x1a, 0x06, 0x03, 0x2a, 1434},//22.40
	{ 0x32, 0x89, 0x1a, 0x23, 0x06, 0x03, 0x2d, 1699},//26.54
	{ 0x38, 0x08, 0x20, 0x00, 0x06, 0x03, 0x31, 2048},//32.00
	{ 0x39, 0x48, 0x25, 0x3b, 0x09, 0x03, 0x36, 2427},//37.92
	{ 0x38, 0x09, 0x2c, 0x33, 0x0b, 0x03, 0x3a, 2867},//44.76
	{ 0x39, 0x49, 0x35, 0x06, 0x0d, 0x03, 0x3c, 3398},//53.01
	{ 0x38, 0x0A, 0x3f, 0x3f, 0x0f, 0x03, 0x3f, 4096},//64.00
#endif	
};   
                                  
static int gc3003_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{                                            
	int i;                                   
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
                                             
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2304;
	info->modes.mode[0].size.h = 1296;
	info->modes.mode[0].fps = g_gc3003_fps_info[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x37;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;
	
	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
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

static const struct fps_info *gc3003_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_gc3003_fps_info); i++)
		if (fps == g_gc3003_fps_info[i].fps)
			break;
	if (i == ARRAY_SIZE(g_gc3003_fps_info))
		return NULL;

	return &g_gc3003_fps_info[i];
}

static int gc3003_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc3003_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc3003_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;


	set_init_i2c_regs(info->sensor_regs[0], g_gc3003_i2c_init_regs, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x6;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2308;
	info->size.h = 1300;
	info->start.x = 1;
	info->start.y = 0;
	//info->crop.w = 2560;
	//info->crop.h = 1440;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = 1340;
	info->max_vts = 65535 - info->min_vts;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	status->min_vts = info->min_vts;
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int gc3003_start(uint32_t isp_id)
{
	struct gc3003_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc3003_status *status)
{
	int i;
	uint16_t gain = fgain * 64;

	if (gain >= (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f)) {
		gain = (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f);
		status->num = (uint8_t)(ARRAY_SIZE(g_gc3003_gain_config) - 1);
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc3003_gain_config) - 1; i++) {
			if (gain >= g_gc3003_gain_config[i].value &&
			    gain < g_gc3003_gain_config[i + 1].value) {
				gain = g_gc3003_gain_config[i].value;
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

static int gc3003_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc3003_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int gc3003_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int gc3003_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct gc3003_status *status;
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
				g_gc3003_gain_config[status->num].reg_00d1);
	set_sync_i2c(&reg[i++], 0x00d0,
				g_gc3003_gain_config[status->num].reg_00d0);
	set_sync_i2c(&reg[i++], 0x00b8,
				g_gc3003_gain_config[status->num].reg_00b8);
	set_sync_i2c(&reg[i++], 0x00b9,
				g_gc3003_gain_config[status->num].reg_00b9);
	set_sync_i2c(&reg[i++], 0x0155,
				g_gc3003_gain_config[status->num].reg_0155);
	set_sync_i2c(&reg[i++], 0x006e,
				g_gc3003_gain_config[status->num].reg_006e);
	set_sync_i2c(&reg[i++], 0x0080,
				g_gc3003_gain_config[status->num].reg_0080);
	set_sync_i2c(&reg[i++], 0x0d41, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0d42, vts & 0xff);
	
	regs->num = i;

	return RTS_ISP_OK;
}

static int gc3003_set_mirror_flip(uint32_t isp_id,
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

static int gc3003_check(uint32_t isp_id)
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

	if (id == 0x3003)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops gc3003_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc3003",
	.get_info = gc3003_get_info,
	.get_init_info = gc3003_get_init_info,
	.start = gc3003_start,
	.get_tuned_again = gc3003_get_tuned_again,
	.get_tuned_dgain = gc3003_get_tuned_dgain,
	.get_exposure_gain_info = gc3003_get_exposure_gain_info,
	.set_mirror_flip = gc3003_set_mirror_flip,
	.check = gc3003_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc3003_ops;
}