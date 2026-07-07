/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <platform_conf.h>
#include "rts_isp_sensor_lib.h"
#include <sensor_entry.h>
#include <isp_reg_lib.h>

// #define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif


#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ANALOG_GAIN_MAX_RATIO (float)73.21875

#define SENSOR_MIN_EXP_LINE 8.0

#define AE_MAX_SHORT_EXP_BASE 126


#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct gc2093_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t last_vts;
	uint16_t min_vts;
	uint8_t gain_reg_num;
	uint8_t last_gain_reg_num;
};

struct gc2093_gain_config {
	uint8_t reg_00b3;
	uint8_t reg_00b8;
	uint8_t reg_00b9;
	uint8_t reg_0155;
	uint8_t reg_00c2;
	uint8_t reg_00cf;
	uint8_t reg_00d9;
	uint16_t gain_value;
};

static struct gc2093_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc2093_fps_info_linear[] = {
	{30.0, (1422*2), 1125, 95985000},
	//{30.0f, 3200, 108000000},
};
static const struct fps_info g_gc2093_fps_info_hdr[] = {
	{30.0, (660*2*2*2), 1250, 99000000*2},
	//{30.0, 3200, 120000000},
};

static struct rts_isp_i2c_reg g_gc2093_i2c_init_regs_linear[] = {
	/*MIPI clk:384Mbps/lane
	pclk:96Mbyte
	Wpclk:384MHz
	Rpclk:192MHz
	row time:29.625us
	window height:1125 
	size:1920*1080*/
	/****system****/
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0xf0},
	{0x03fe,0x00},
	{0x03f2,0x00},
	{0x03f3,0x00},
	{0x03f4,0x36},
	{0x03f5,0xc0},
	{0x03f6,0x0B},
	{0x03f7,0x11},
	{0x03f8,0x30},
	{0x03f9,0x42},
	{0x03fc,0x8e},
	/****CISCTL & ANALOG****/
	{0x0087,0x18},
	{0x00ee,0x30},
	{0x00d0,0xbf},
	{0x01a0,0x00},
	{0x01a4,0x40},
	{0x01a5,0x40},
	{0x01a6,0x40},
	{0x01af,0x09},
	{0x0003,0x04},
	{0x0004,0x65},
	{0x0005,0x05},	//line length = 0x58e =  1422
	{0x0006,0x8e},
	{0x0007,0x00},
	{0x0008,0x11},	//V blank
	{0x0009,0x00},
	{0x000a,0x02},
	{0x000b,0x00},
	{0x000c,0x04},
	{0x000d,0x04},
	{0x000e,0x40},
	{0x000f,0x07},
	{0x0010,0x8c},
	{0x0013,0x15},
	{0x0019,0x0c}, 
	{0x0041,0x04},	//frame length = 0x465 =  1125
	{0x0042,0x65},
	{0x0053,0x60}, 
	{0x008d,0x92}, 
	{0x0090,0x00},
	{0x00c7,0xe1}, 
	{0x001b,0x73}, 
	{0x0028,0x0d}, 
	{0x0029,0x40}, 
	{0x002b,0x04}, 
	{0x002e,0x23}, 
	{0x0037,0x03},
	{0x0043,0x04},
	{0x0044,0x30}, 
	{0x004a,0x01},
	{0x004b,0x28}, 
	{0x0055,0x30}, 
	{0x0066,0x3f},
	{0x0068,0x3f},
	{0x006b,0x44},
	{0x0077,0x00}, 
	{0x0078,0x20}, 
	{0x007c,0xa1}, 
	{0x00ce,0x7c}, 
	{0x00d3,0xd4}, 
	{0x00e6,0x50}, 
	/*gain*/
	{0x00b6,0xc0},
	{0x00b0,0x68}, 
	{0x00b3,0x00}, 
	{0x00b8,0x01}, 
	{0x00b9,0x00}, 
	{0x00b1,0x01},
	{0x00b2,0x00},
	/*isp*/
	{0x0101,0x0c},
	{0x0102,0x89},
	{0x0104,0x01},
	{0x0107,0xa6},
	{0x0108,0xa9},
	{0x0109,0xa8},
	{0x010a,0xa7},
	{0x010b,0xff},
	{0x010c,0xff},
	{0x010f,0x00},
	{0x0158,0x00},
	{0x0428,0x86},
	{0x0429,0x86},
	{0x042a,0x86},
	{0x042b,0x68},
	{0x042c,0x68},
	{0x042d,0x68},
	{0x042e,0x68},
	{0x042f,0x68},
	{0x0430,0x4f},
	{0x0431,0x68},
	{0x0432,0x67},
	{0x0433,0x66},
	{0x0434,0x66},
	{0x0435,0x66},
	{0x0436,0x66},
	{0x0437,0x66},
	{0x0438,0x62},
	{0x0439,0x62},
	{0x043a,0x62},
	{0x043b,0x62},
	{0x043c,0x62},
	{0x043d,0x62},
	{0x043e,0x62},
	{0x043f,0x62},
	/*dark sun*/
	{0x0123,0x08},
	{0x0123,0x00},
	{0x0120,0x01},
	{0x0121,0x04},
	{0x0122,0x65},
	{0x0124,0x03},
	{0x0125,0xff},
	{0x001a,0x8c},
	{0x00c6,0xe0},
	/*blk*/
	{0x0026,0x30},
	{0x0142,0x00},
	{0x0149,0x1e},
	{0x014a,0x0f},
	{0x014b,0x00},
	{0x0155,0x07},
	{0x0414,0x78},
	{0x0415,0x78},
	{0x0416,0x78},
	{0x0417,0x78},
	{0x04e0,0x18},
	/*window*/
	{0x0192,0x02},	//Out window y = 2 
	{0x0194,0x02},	//Out window x = 2 
	{0x0195,0x04},	//Out window height = 1080
	{0x0196,0x38},
	{0x0197,0x07},	//Out window width = 1920
	{0x0198,0x80}, 
	/****DVP & MIPI****/
	{0x019a,0x06},
	{0x007b,0x2a},
	{0x0023,0x2d},
	{0x0201,0x27},
	{0x0202,0x56},
	{0x0203,0xb6},
	{0x0212,0x80},
	{0x0213,0x07},
	{0x0215,0x10},
	{0x003e,0x91},
};
static struct rts_isp_i2c_reg g_gc2093_i2c_init_regs_hdr[] = {
	//*MIPI clk:792Mbps
	//pclk:99Mbyte
	//Wpclk:396MHz
	//Rpclk:198MHz
	//row time:13.3333us
	//window height:1250
	//size:1920*1080
	//short_exp<126,short_exp+long_exp<1236
	/****system****/
	{0x03fe, 0xf0},
	{0x03fe, 0xf0},
	{0x03fe, 0xf0},
	{0x03fe, 0x00},
	{0x03f2, 0x00},
	{0x03f3, 0x00},
	{0x03f4, 0x36},
	{0x03f5, 0xc0},
	{0x03f6, 0x0B},
	{0x03f7, 0x01},
	{0x03f8, 0x63},
	{0x03f9, 0x40},
	{0x03fc, 0x8e},
	/****CISCTL & ANALOG****/
	{0x0087, 0x18},
	{0x00ee, 0x30},
	{0x00d0, 0xbf},
	{0x01a0, 0x00},
	{0x01a4, 0x40},
	{0x01a5, 0x40},
	{0x01a6, 0x40},
	{0x01af, 0x09},
	{0x0001, 0x00},
	{0x0002, 0x08},	//min exp = 8
	{0x0003, 0x04},
	{0x0004, 0x02},
	{0x0005, 0x02},	//line length = 0x294 =  660
	{0x0006, 0x94},
	{0x0007, 0x00},
	{0x0008, 0x11},	//V blank
	{0x0009, 0x00},
	{0x000a, 0x02},
	{0x000b, 0x00},
	{0x000c, 0x04},
	{0x000d, 0x04},	//win_height = 0x440 = 1088
	{0x000e, 0x40},
	{0x000f, 0x07},
	{0x0010, 0x8c},
	{0x0013, 0x15},
	{0x0019, 0x0c},
	{0x0041, 0x04},	//frame length = 0x4E2 =  1250
	{0x0042, 0xE2},
	{0x0053, 0x60},
	{0x008d, 0x92},
	{0x0090, 0x00},
	{0x00c7, 0xe1},
	{0x001b, 0x73},
	{0x0028, 0x0d},
	{0x0029, 0x24},
	{0x002b, 0x04},
	{0x002e, 0x23},
	{0x0037, 0x03},
	{0x0043, 0x04},
	{0x0044, 0x28},
	{0x004a, 0x01},
	{0x004b, 0x20},
	{0x0055, 0x28},
	{0x0066, 0x3f},
	{0x0068, 0x3f},
	{0x006b, 0x44},
	{0x0077, 0x00},
	{0x0078, 0x20},
	{0x007c, 0xa1},
	{0x00ce, 0x7c},
	{0x00d3, 0xd4},
	{0x00e6, 0x50},
	/*gain*/
	{0x00b6, 0xc0},
	{0x00b0, 0x68},
	/*isp*/
	{0x0101, 0x0c},
	{0x0102, 0x89},
	{0x0104, 0x01},
	{0x010e, 0x01},
	{0x0107, 0xa6},
	{0x0108, 0xa9},
	{0x0109, 0xa8},
	{0x010a, 0xa7},
	{0x010b, 0xff},
	{0x010c, 0xff},
	{0x010f, 0x00},
	{0x0158, 0x00},
	{0x0428, 0x86},
	{0x0429, 0x86},
	{0x042a, 0x86},
	{0x042b, 0x68},
	{0x042c, 0x68},
	{0x042d, 0x68},
	{0x042e, 0x68},
	{0x042f, 0x68},
	{0x0430, 0x4f},
	{0x0431, 0x68},
	{0x0432, 0x67},
	{0x0433, 0x66},
	{0x0434, 0x66},
	{0x0435, 0x66},
	{0x0436, 0x66},
	{0x0437, 0x66},
	{0x0438, 0x62},
	{0x0439, 0x62},
	{0x043a, 0x62},
	{0x043b, 0x62},
	{0x043c, 0x62},
	{0x043d, 0x62},
	{0x043e, 0x62},
	{0x043f, 0x62},
	/*dark sun*/
	{0x0123, 0x08},
	{0x0123, 0x00},
	{0x0120, 0x01},
	{0x0121, 0x04},
	{0x0122, 0xd8},
	{0x0124, 0x03},
	{0x0125, 0xff},
	{0x001a, 0x8c},
	{0x00c6, 0xe0},
	/*blk*/
	{0x0026, 0x30},
	{0x0142, 0x00},
	{0x0149, 0x1e},
	{0x014a, 0x0f},
	{0x014b, 0x00},
	{0x0155, 0x07},
	{0x0414, 0x78},
	{0x0415, 0x78},
	{0x0416, 0x78},
	{0x0417, 0x78},
	{0x0454, 0x78},
	{0x0455, 0x78},
	{0x0456, 0x78},
	{0x0457, 0x78},
	{0x04e0, 0x18},
	/*window*/
	{0x0192, 0x02},	//Out window y = 2 
	{0x0194, 0x02},	//Out window x = 2 
	{0x0195, 0x04},	//Out window height = 1080
	{0x0196, 0x38},
	{0x0197, 0x07},	//Out window width = 1920
	{0x0198, 0x80}, 
	/****DVP & MIPI****/
	{0x019a, 0x06},
	{0x007b, 0x2a},
	{0x0023, 0x2d},
	{0x0201, 0x27},
	{0x0202, 0x56},
	{0x0203, 0xb6}, //try 0xce or 0x8e
	{0x0212, 0x80},
	{0x0213, 0x07},
	{0x0215, 0x10},
	{0x003e, 0x91},
	/****HDR EN****/
	{0x0027, 0x71}, 
	{0x0215, 0x92}, //0x92
	{0x024d, 0x01}, 

};

static struct gc2093_gain_config g_gc2093_gain_config[] = {

   //0xb3, 0xb8, 0xb9, 0x155, 0xc2, 0xcf, 0xd9, gain value(1x = 64) 
	{0x00,0x01,0x00,0x08,0x10,0x08,0x0a,64},	  
	{0x10,0x01,0x0c,0x08,0x10,0x08,0x0a,76},
	{0x20,0x01,0x1b,0x08,0x11,0x08,0x0c,91},
	{0x30,0x01,0x2c,0x08,0x12,0x08,0x0e,107},
	{0x40,0x01,0x3f,0x08,0x14,0x08,0x12,125},
	{0x50,0x02,0x16,0x08,0x15,0x08,0x14,147},
	{0x60,0x02,0x35,0x08,0x17,0x08,0x18,177},
	{0x70,0x03,0x16,0x08,0x18,0x08,0x1a,211},
	{0x80,0x04,0x02,0x08,0x1a,0x08,0x1e,248},
	{0x90,0x04,0x31,0x08,0x1b,0x08,0x20,297},
	{0xa0,0x05,0x32,0x08,0x1d,0x08,0x24,356},
	{0xb0,0x06,0x35,0x08,0x1e,0x08,0x26,425},
	{0xc0,0x08,0x04,0x08,0x20,0x08,0x2a,504},
	{0x5a,0x09,0x19,0x08,0x1e,0x08,0x2a,599},
	{0x83,0x0b,0x0f,0x08,0x1f,0x08,0x2a,709},
	{0x93,0x0d,0x12,0x08,0x21,0x08,0x2e,836},
	{0x84,0x10,0x00,0x0b,0x22,0x08,0x30,978},
	{0x94,0x12,0x3a,0x0b,0x24,0x08,0x34,1153},
	{0x5d,0x1a,0x02,0x0b,0x26,0x08,0x34,1647},
	{0x9b,0x1b,0x20,0x0b,0x26,0x08,0x34,1651},
	{0x8c,0x20,0x0f,0x0b,0x26,0x08,0x34,1935},
	{0x9c,0x26,0x07,0x12,0x26,0x08,0x34,2292},
	{0xB6,0x36,0x21,0x12,0x26,0x08,0x34,3239},
	{0xad,0x37,0x3a,0x12,0x26,0x08,0x34,3959},
	{0xbd,0x3d,0x02,0x12,0x26,0x08,0x34,4686},
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x37	//0x6e(default)
#define SLAVE_ADDR_1 0x7e	//0xfc

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;
static int gc2093_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].fps = g_gc2093_fps_info_linear[0].fps;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	i++;
	info->modes.mode[i].fps = g_gc2093_fps_info_hdr[0].fps;
	info->modes.mode[i].hdr = HDR_MODE;;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
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

static const struct fps_info *gc2093_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;
	debug("@ gc2093_get_fps_info hdr = %d\n",mode->hdr);

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_gc2093_fps_info_hdr); i++)
			if (fps <= g_gc2093_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_gc2093_fps_info_hdr))
			return NULL;

		return &g_gc2093_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc2093_fps_info_linear); i++)
			if (fps <= g_gc2093_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_gc2093_fps_info_linear))
			return NULL;

		return &g_gc2093_fps_info_linear[i];
	}

}

static int gc2093_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc2093_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc2093_get_fps_info(mode->fps,&mode->hdr);

	debug("@ gc2093_get_fps_info = %d, %d, %d, %d\n",fps_info->fps,fps_info->hts,fps_info->vts,fps_info->clk);
	
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {

		set_init_i2c_regs(info->sensor_regs[0], g_gc2093_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 1920;
		info->size.h = 1080;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = fps_info->vts;
		info->max_vts = info->min_vts * 30;

		status->exp_step = 1e6 * info->hts / info->pclk; /* 1e6 * 660*2*2*2 /99000000*2  26.66 us */ 
	}

	else{
		
		set_init_i2c_regs(info->sensor_regs[0], g_gc2093_i2c_init_regs_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x5;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 1920;
		info->size.h = 1080;
		info->start.x = 0;
		info->start.y = 0;

		info->hts = fps_info->hts;
		info->pclk = fps_info->clk;
		info->min_vts = status->min_vts = fps_info->vts;
		info->max_vts = info->min_vts * 30;

		status->exp_step = 1e6 * info->hts / info->pclk; /* 29.63 us */
	}

	return RTS_ISP_OK;
	

}

static int gc2093_start(uint32_t isp_id)
{
	struct gc2093_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;
	//printf("Sensor timestamp: 2022/07/29 15:18\r\n");

	return RTS_ISP_OK;
}

static int gc2093_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc2093_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE){
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 16) * status->exp_step;
		debug("max_exposure = %f, min_exposure = %f\n", max_exposure[0], min_exposure[0]);
	} 
	else {
		uint32_t tmp1;
		uint32_t tmp2;

		uint16_t max_exp = vts - 14;

		tmp1 = AE_MAX_SHORT_EXP_BASE;
		tmp2 = (uint32_t)(max_exp / (ratio[0] + 1));
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;

		// Sensor exposure formula
		// short_exp < 126
		// short_exp + long_exp < 1236  (vts -14)

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = SENSOR_MIN_EXP_LINE * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];

		debug("long_max_exposure_=%f, long_min_exposure=%f\n", max_exposure[0], min_exposure[0]);
		debug("short_max_exposure_=%f, short_min_exposure=%f\n", max_exposure[1], min_exposure[1]);
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc2093_status *status)
{
	uint16_t sen_gain = (uint16_t)(fgain * 64.f);
	int i;
	
	if (sen_gain >= (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f)) 
	{
		sen_gain = (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f);
		status->gain_reg_num = (uint8_t)(ARRAY_SIZE(g_gc2093_gain_config) - 1);
	} 
	else 
	{
		for (i = 0; i < ARRAY_SIZE(g_gc2093_gain_config) - 1; i++) 
		{
			if (sen_gain >= g_gc2093_gain_config[i].gain_value &&
			    sen_gain < g_gc2093_gain_config[i + 1].gain_value) 
			{
				sen_gain = g_gc2093_gain_config[i].gain_value;
				status->gain_reg_num = i;
				break;
			}
		}
	}
	debug("GAIN INFO fgatin=%f, gain reg num=%d\n", fgain, status->gain_reg_num);

	return sen_gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return (float)(reg_value / 64.f);
}

static int gc2093_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc2093_status *status;

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

static int gc2093_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc2093_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int gc2093_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
#if 1
	int i;

	struct gc2093_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exp_lines[2];
	uint16_t frame_length;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	frame_length = exp_gain->vts;
	reg = regs->reg;

	if (status->hdr == LINEAR_MODE){
		//debug("INFO EXP=%f, VTS=%d, gain num=%d\n",exp_gain->exposure[0],exp_gain->vts, status->gain_reg_num);
		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0041, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x0042, frame_length & 0xff);

			status->last_vts = frame_length;
		}
		
		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exp_lines[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x0003, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x0004, exp_lines[0] & 0xff);
			
			status->last_exposure[0] = exp_gain->exposure[0];
		}
	}

	else {
		//debug("INFO EXP=%f, %f, gain=%d, VTS=%d\n", exp_gain->exposure[0],exp_gain->exposure[1],status->gain_reg_num,exp_gain->vts);

		for (i = 0; i < 2; i++) {
			exp_lines[i] = (exp_gain->exposure[i] / status->exp_step + 0.5f);
		}
		i = 0;
		/* set vts */
		if (abs(status->last_vts - frame_length) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0041, frame_length >> 8);
			set_sync_i2c(&reg[i++], 0x0042, frame_length & 0xff);

			status->last_vts = frame_length;
		}

		/* set exposure */
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0001, exp_lines[1] >> 8);
			set_sync_i2c(&reg[i++], 0x0002, exp_lines[1] & 0xff);

			status->last_exposure[1] = exp_gain->exposure[1];
		}

		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x0003, exp_lines[0] >> 8);
			set_sync_i2c(&reg[i++], 0x0004, exp_lines[0] & 0xff);

			status->last_exposure[0] = exp_gain->exposure[0];
		}
	}

	status->gain_reg_num;
	/* set gain */
	if (abs(status->last_gain_reg_num - status->gain_reg_num) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x00b3, g_gc2093_gain_config[status->gain_reg_num].reg_00b3);
		set_sync_i2c(&reg[i++], 0x00b8, g_gc2093_gain_config[status->gain_reg_num].reg_00b8);
		set_sync_i2c(&reg[i++], 0x00b9, g_gc2093_gain_config[status->gain_reg_num].reg_00b9);
		set_sync_i2c(&reg[i++], 0x0155, g_gc2093_gain_config[status->gain_reg_num].reg_0155);
		set_sync_i2c(&reg[i++], 0x031d, 0x2d);
		set_sync_i2c(&reg[i++], 0x00c2, g_gc2093_gain_config[status->gain_reg_num].reg_00c2);
		set_sync_i2c(&reg[i++], 0x00cf, g_gc2093_gain_config[status->gain_reg_num].reg_00cf);
		set_sync_i2c(&reg[i++], 0x00d9, g_gc2093_gain_config[status->gain_reg_num].reg_00d9);
		set_sync_i2c(&reg[i++], 0x031d, 0x28);

//		set_sync_i2c(&reg[i++], 0x00b1, g_gc2093_gain_config[status->gain_reg_num].reg_00b1);
//		set_sync_i2c(&reg[i++], 0x00b2, g_gc2093_gain_config[status->gain_reg_num].reg_00b2);
	
		status->last_gain_reg_num = status->gain_reg_num;
	}
	regs->num = i;
#endif	
	return RTS_ISP_OK;

}
static int gc2093_set_mirror_flip(uint32_t isp_id,
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
		case 0: // Normal
		default:
			set_sync_i2c(&reg[i++], 0x0017, 0x00);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x0017, 0x01);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x0017, 0x02);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x0017, 0x03);
		break;

	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int gc2093_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

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

	//printf("@ gc2093_check id  = 0x%x\n",id);

	if (id == 0x2093)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int gc2093_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops gc2093_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc2093",

	.get_info = gc2093_get_info,
	.get_init_info = gc2093_get_init_info,
	.start = gc2093_start,
	.get_exposure_range = gc2093_get_exposure_range,
	.get_tuned_again = gc2093_get_tuned_again,
	.get_tuned_dgain = gc2093_get_tuned_dgain,
	.get_exposure_gain_info = gc2093_get_exposure_gain_info,
	.set_mirror_flip = gc2093_set_mirror_flip,
	.check = gc2093_check,
	.get_slave_addr_num = gc2093_get_slave_addr_num,
};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc2093_ops;
}