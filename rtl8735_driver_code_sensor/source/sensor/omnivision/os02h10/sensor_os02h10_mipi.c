/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2023 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <platform_conf.h>
#include <math.h>
#include <isp_reg_lib.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"



//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

/*						XAVI-NEO 	| XAVI-THRONE 	| RTK
	-------------------------------------------------------
	XAVI_PROJECT 	|		1		|		1		|  0
	Linear_MCLK27M	|		0		|		1		|  0
	SENSOR_ID_SELECT|		1		|		1		|  0
*/
#define XAVI_PROJECT		0
#define Linear_MCLK27M		0	/* 0 = linear_24M, 1 = linear_27M*/
#define SENSOR_ID_SELECT	0	/* 0 = 0x3c, 1 = 0x3B*/

#define HAL_WRITE32(base, addr, value32)  \
        ((*((volatile u32*)(base + addr))) = rtk_cpu_to_le32(value32))

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define Short_to_Long 17									/* VHDR mode min interval between long exposure and short exposure frame (long exp + short exp) */

#define ORIENTATION 0												/* Default sensor mirror and flip mode => 0:default, 1:rotate180 */
#define SENSOR_MIN_EXP_LINE 1.0
#define SENSOR_MIN_EXP_LINE_VHDR_OFF 1.0
#define RESOLUTION	0			/* 0=1920*1080*30, 1=960*540*60 */


struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct os02h10_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
	uint8_t gain_reg_num;
	uint8_t last_gain_reg_num;
	uint8_t fusion_mode;
	uint16_t short_exp_mode_exit_thd;
};



static struct os02h10_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_os02h10_fps_info_linear[] = {
/*   FPS    HTS       VTS     PCLK      */
#if	(RESOLUTION == 0 && (Linear_MCLK27M == 0))
	//#if (Linear_MCLK27M == 0)
	{30, (1244*2), (1930), (144000000)},
	
	
#elif (RESOLUTION == 0 && (Linear_MCLK27M == 1))
	{30, (1250*2), (1125), (84375000)},
	
#else 
	{60, (1244*2), (965), (144000000)},
#endif
};

/* HDR frame rate table*/
static const struct fps_info g_os02h10_fps_info_hdr[] = {
/*   FPS    HTS       VTS       PCLK      */
#if	(RESOLUTION == 0)
	{30.0, (1244*4), (1125), (167940000)},
#else
	{60.0, (1244*2), (1126), (168089280)},
#endif
};

static struct rts_isp_i2c_reg g_os02h10_i2c_init_regs_linear1[] = {
	{0xfd, 0x00},
	{0x20, 0x00},
};

static struct rts_isp_i2c_reg g_os02h10_i2c_init_regs_linear2[] = {
#if (!Linear_MCLK27M)
	
	{0x53, 0xfe},
	{0x54, 0x7f},
	{0x61, 0x78},
	{0x63, 0x05},
	{0x64, 0x00},
	{0x65, 0x00},
	{0x66, 0x02},
	{0x67, 0x00},
	{0x8d, 0x00},
	{0x8e, 0x07},
	{0x8f, 0x88},
	{0x90, 0x04},
	{0x91, 0x40},
	{0x95, 0x88},
	{0x98, 0x88},
	{0xb6, 0x40},
	{0x23, 0x00},
	{0x24, 0x05},
	{0x26, 0x4d},
	{0x29, 0x00},
	{0x2a, 0x03},
	{0x31, 0x90},
	{0x32, 0x04},
	{0x33, 0x00},
	{0x38, 0x00},
	{0x55, 0x00},
	{0xf5, 0x01},
	{0xfd, 0x01},
	{0x03, 0x00},
	{0x04, 0x04},
	{0x05, 0x06},
	{0x06, 0xE8},
	{0x09, 0x01},
	{0x0a, 0x00},
	{0x24, 0xf8},
	{0x3e, 0x3c},
	{0x3f, 0x01},
	{0x01, 0x01},
	{0x11, 0x40},
	{0x14, 0x65},
	{0x15, 0x00},
	{0x16, 0x95},
	{0x18, 0xf3},
	{0x19, 0x47},
	{0x1a, 0x01},
	{0x1b, 0x70},
	{0x1c, 0xf2},
	{0x1e, 0x00},
	{0x1f, 0x27},
	{0x21, 0x74},
	{0x22, 0x90},
	{0x25, 0x00},
	{0x26, 0x77},
	{0x27, 0xf9},
	{0x2a, 0x4e},
	{0x2e, 0x28},
	{0x34, 0xf6},
	{0x35, 0x22},
	{0x36, 0xa2},
	{0x50, 0x00},
	{0x51, 0x08},
	{0x52, 0x07},
	{0x53, 0x00},
	{0x55, 0x35},
	{0x56, 0x01},
	{0x57, 0x0a},
	{0x59, 0x01},
	{0x5b, 0x14},
	{0x5d, 0x08},
	{0x5e, 0x00},
	{0x5f, 0x1d},
	{0x60, 0x1e},
	{0x68, 0x05},
	{0x69, 0x04},
	{0x6a, 0x00},
	{0x70, 0x64},
	{0x71, 0x15},
	{0x72, 0x42},
	{0x7b, 0x40},
	{0x80, 0x08},
	{0x83, 0x08},
	{0x85, 0x14},
	{0x86, 0x2d},
	{0x8a, 0xf9},
	{0x95, 0x25},
	{0x97, 0x10},
	{0x99, 0x30},
	{0x9f, 0x10},
	{0xa8, 0x10},
	{0xad, 0x00},
	{0xb0, 0x63},
	{0xb1, 0x63},
	{0xb2, 0x63},
	{0xb3, 0x63},
	{0xb4, 0x61},
	{0xb5, 0x61},
	{0xb6, 0x61},
	{0xb7, 0x61},
	{0xb8, 0x77},
	{0xb9, 0x66},
	{0xba, 0x07},
	{0xbb, 0x07},
	{0xbc, 0x07},
	{0xbd, 0x07},
	{0x29, 0x0a},
	{0x2b, 0x03},
	{0x30, 0x04},
	{0x92, 0x05},
	{0xc4, 0x00},
	{0xc5, 0x00},
	{0xc6, 0x13},
	{0xc7, 0x6d},
	{0xc9, 0x00},
	{0xd0, 0x77},
	{0xd1, 0x66},
	{0xd5, 0x11},
	{0xd7, 0x40},
	{0xdc, 0x01},
	{0xdd, 0x01},
	{0xde, 0x04},
	{0xfd, 0x02},
	{0x00, 0x18}, //dpc disable
	{0x68, 0x02},
	{0x6d, 0x5d},
	{0x6e, 0xdc},
	{0x72, 0x40}, //blc=256 in 12b
	{0x73, 0x40}, //blc=256 in 12b
	{0x74, 0x40}, //blc=256 in 12b
	{0x75, 0x40}, //blc=256 in 12b
	{0x76, 0x00}, //blc=256 in 12b
	{0x78, 0x70},
	{0x79, 0x70},
	{0x7a, 0x70},
	{0x7b, 0x70},
	{0x80, 0x60},
	{0x81, 0x60},
	{0x82, 0x12},
	{0x83, 0x60},
	{0x84, 0x60},
	{0x9f, 0x12},
	{0xa1, 0x05},
	{0xa2, 0x04},
	{0xa3, 0x40}, //1088
	{0xa5, 0x04},
	{0xa6, 0x07},
	{0xa7, 0x88}, //1928
	{0x72, 0x40},
	{0x73, 0x40},
	{0x74, 0x40},
	{0x75, 0x40},
	{0xfd, 0x06},
	{0x00, 0x04},
	{0x01, 0x7c},
	{0x02, 0xbf},
	{0x03, 0x86},
	{0x04, 0xbd},
	{0x05, 0x02},
	{0xfd, 0x00},
	{0xb1, 0x02},
	{0xfd, 0x01},
#else
	
	{0x53, 0xfe},
	{0x54, 0x7f},
	{0x61, 0x7d},
	{0x63, 0x05},
	{0x64, 0x01},
	{0x65, 0x00},
	{0x66, 0x02},
	{0x67, 0x00},
	{0x8d, 0x00},
	{0x8e, 0x07},
	{0x8f, 0x88}, //1928
	{0x90, 0x04},
	{0x91, 0x40}, //1088
	{0xa1, 0x02},
	{0xb6, 0x40},
	{0x23, 0x00},
	{0x24, 0x05},
	{0x26, 0x45},
	{0x29, 0x00},
	{0x2a, 0x03},
	{0x31, 0x80},
	{0x32, 0x04},
	{0x33, 0x00},
	{0x38, 0x00},
	{0x55, 0x00},
	{0xf5, 0x01},
	{0xfd, 0x01},
	{0x03, 0x00},
	{0x04, 0x04},
	{0x09, 0x00},
	{0x0a, 0xd0},
	{0x24, 0xff},
	{0x3e, 0x3c},
	{0x3f, 0x01},
	{0x01, 0x01},
	{0x11, 0x40},
	{0x14, 0x65},
	{0x15, 0x00},
	{0x16, 0x95},
	{0x18, 0xf3},
	{0x19, 0x47},
	{0x1a, 0x03},
	{0x1b, 0x50},
	{0x1c, 0xf0},
	{0x1d, 0x3d},
	{0x1e, 0x00},
	{0x1f, 0x27},
	{0x21, 0x74},
	{0x22, 0x90},
	{0x25, 0x00},
	{0x26, 0x77},
	{0x27, 0xf9},
	{0x2a, 0x4e},
	{0x2e, 0x28},
	{0x34, 0xf6},
	{0x35, 0x22},
	{0x36, 0xa2},
	{0x50, 0x00},
	{0x51, 0x08},
	{0x52, 0x07},
	{0x53, 0x00},
	{0x55, 0x35},
	{0x56, 0x01},
	{0x57, 0x0a},
	{0x59, 0x01},
	{0x5a, 0x01},
	{0x5b, 0x4e},
	{0x5d, 0x08},
	{0x5e, 0x00},
	{0x5f, 0x1d},
	{0x60, 0x1e},
	{0x68, 0x05},
	{0x69, 0x04},
	{0x6a, 0x00},
	{0x70, 0x64},
	{0x71, 0x15},
	{0x72, 0x42},
	{0x7b, 0x40},
	{0x80, 0x08},
	{0x83, 0x08},
	{0x85, 0x14},
	{0x86, 0x2d},
	{0x8a, 0xf9},
	{0x95, 0x25},
	{0x97, 0x10},
	{0x99, 0x30},
	{0x9f, 0x10},
	{0xa8, 0x10},
	{0xad, 0x00},
	{0xb0, 0x63},
	{0xb1, 0x63},
	{0xb2, 0x63},
	{0xb3, 0x63},
	{0xb4, 0x61},
	{0xb5, 0x61},
	{0xb6, 0x61},
	{0xb7, 0x61},
	{0xb8, 0x77},
	{0xb9, 0x66},
	{0xba, 0x07},
	{0xbb, 0x07},
	{0xbc, 0x07},
	{0xbd, 0x07},
	
	{0x29, 0x0a},
	{0x2b, 0x03},
	{0x30, 0x04},
	{0x92, 0x05},
	{0xc4, 0x00},
	{0xc5, 0x00},
	{0xc6, 0x13},
	{0xc7, 0x6d},
	{0xc9, 0x00},
	
	{0xd0, 0x77},
	{0xd1, 0x66},
	{0xd5, 0x11},
	{0xd7, 0x40},
	{0xdc, 0x01},
	{0xdd, 0x01},
	{0xde, 0x04},
	{0xfd, 0x02},
	{0x00, 0x18}, //dpc disable
	{0x68, 0x02},
	{0x6d, 0x5d},
	{0x6e, 0xdc},
	{0x72, 0x40}, //blc=256 in 12b
	{0x73, 0x40}, //blc=256 in 12b
	{0x74, 0x40}, //blc=256 in 12b
	{0x75, 0x40}, //blc=256 in 12b
	{0x76, 0x00}, //blc=256 in 12b	
	{0x78, 0x70},
	{0x79, 0x70},
	{0x7a, 0x70},
	{0x7b, 0x70},
	{0x80, 0x60},
	{0x81, 0x60},
	{0x82, 0x12},
	{0x83, 0x60},
	{0x84, 0x60},
	{0x9f, 0x12},
	{0xa1, 0x05},
	{0xa2, 0x04},
	{0xa3, 0x40}, //1088
	{0xa5, 0x04},
	{0xa6, 0x07},
	{0xa7, 0x88}, //1928
	{0x72, 0x40},
	{0x73, 0x40},
	{0x74, 0x40},
	{0x75, 0x40},
	
	{0xfd, 0x06},
	{0x00, 0x04},
	{0x01, 0x7c},
	{0x02, 0xbf},
	{0x03, 0x86},
	{0x04, 0xbd},
	{0x05, 0x02},
	{0xfd, 0x02},
	{0x52, 0xff},
	{0xfd, 0x01},
	{0xfd, 0x00},
	{0xb1, 0x02},
	{0xfd, 0x01},
#endif	
};

		

static struct rts_isp_i2c_reg g_os02h10_i2c_init_regs_hdr1[] = {
	{0xfd, 0x00},
	{0x20, 0x00},
};


static struct rts_isp_i2c_reg g_os02h10_i2c_init_regs_hdr2[] = {
	{0x53,  0xfe},
	{0x54,  0x7f},
	{0x61,  0x8c},
	{0x63,  0x05},
	{0x64,  0x00},
	{0x65,  0x00},
	{0x66,  0x02},
	{0x67,  0x00},
	{0x8d,  0x00},
	{0x8e,  0x07},  
	{0x8f,  0x88},  
	{0x90,  0x04},	
	{0x91,  0x40},  
	{0x95,  0x88},
	{0x98,  0x88},
	{0x9a,  0x2b},
	{0xb6,  0x40},
	{0x23,  0x00},
	{0x24,  0x05},
	{0x26,  0x4d},
	{0x29,  0x00},
	{0x2a,  0x03},
	{0x31,  0x90},
	{0x32,  0x04},
	{0x33,  0x00},
	{0x38,  0x00},
	{0x55,  0x00},
	{0xf5,  0x01},
	{0xfd,  0x01},
	{0x03,  0x01},
	{0x04,  0x00},
	{0x05,  0x00},
	{0x06,  0x00},
	{0x4c,  0x00},
	{0x4d,  0x04},
	{0x24,  0xff},
	{0x45,  0xff},
	{0x09,  0x00},
	{0x0a,  0x00},
	//{0x31,  0x20}, // variable hdr
	{0x31,  0x60}, // fixed hdr
	{0x3e,  0x3c},
	{0x3f,  0x01},
	{0x01,  0x01},
	{0x11,  0x40},
	{0x14,  0x65},
	{0x15,  0x00},
	{0x16,  0x95},
	{0x18,  0xf3},
	{0x19,  0x47},
	{0x1a,  0x03},
	{0x1b,  0x50},
	{0x1c,  0xf0},
	{0x1d,  0x3d},
	{0x1e,  0x00},
	{0x1f,  0x27},
	{0x21,  0x74},
	{0x22,  0x90},
	{0x25,  0x00},
	{0x26,  0x77},
	{0x27,  0xf9},
	{0x2a,  0x4e},
	{0x2e,  0x28},
	{0x34,  0xf6},
	{0x35,  0x22},
	{0x36,  0xa2},
	{0x50,  0x00},
	{0x51,  0x08},
	{0x52,  0x07},
	{0x53,  0x00},
	{0x55,  0x35},
	{0x56,  0x01},
	{0x57,  0x0a},
	{0x59,  0x01},
	{0x5b,  0x13},
	{0x5d,  0x08},
	{0x5e,  0x00},
	{0x5f,  0x1d},
	{0x60,  0x1e},
	{0x68,  0x05},
	{0x69,  0x04},
	{0x6a,  0x00},
	{0x70,  0x64},
	{0x71,  0x15},
	{0x72,  0x42},
	{0x7b,  0x40},
	{0x80,  0x08},
	{0x86,  0x2d},
	{0x8a,  0xf9},
	{0x95,  0x25},
	{0x97,  0x10},
	{0x99,  0x30},
	{0x9f,  0x10},
	{0xa8,  0x10},
	{0xad,  0x00},
	{0xb0,  0x63},
	{0xb1,  0x63},
	{0xb2,  0x63},
	{0xb3,  0x63},
	{0xb4,  0x61},
	{0xb5,  0x61},
	{0xb6,  0x61},
	{0xb7,  0x61},
	{0xb8,  0x77},
	{0xb9,  0x66},
	{0xba,  0x07},
	{0xbb,  0x07},
	{0xbc,  0x07},
	{0xbd,  0x07},
	
	{0x29,  0x0a},
	{0x2b,  0x03},
	{0x30,  0x04},
	{0x92,  0x05},
	{0xc4,  0x00},
	{0xc5,  0x00},
	{0xc6,  0x13},
	{0xc7,  0x6d},
	{0xc9,  0x00},
	
	{0xd0,  0x77},
	{0xd1,  0x66},
	{0xd5,  0x12},
	{0xd7,  0x40},
	{0xd8,  0x00},
	{0xd9,  0x32},	// max_short_exp=50
	{0xdc,  0x00},
	{0xdd,  0x01},
	{0xde,  0x04},
	{0xfd,  0x02},
	{0x00,  0x18}, //dpc disable
	{0x68,  0x02},
	{0x6d,  0x5d},
	{0x6e,  0xdc},
	{0x72,  0x40}, //blc=256 in 12b
	{0x73,  0x40}, //blc=256 in 12b
	{0x74,  0x40}, //blc=256 in 12b
	{0x75,  0x40}, //blc=256 in 12b
	{0x76,  0x00}, //blc=256 in 12b
	{0x78,  0x70},
	{0x79,  0x70},
	{0x7a,  0x70},
	{0x7b,  0x70},
	{0x80,  0x60},
	{0x81,  0x60},
	{0x82,  0x12},
	{0x83,  0x60},
	{0x84,  0x60},
	{0x9f,  0x12},
	{0xa1,  0x05},
	{0xa2,  0x04},
	{0xa3,  0x3c},	//1084
	{0xa5,  0x04},
	{0xa6,  0x07},
	{0xa7,  0x84},	//1924
	{0x72,  0x40},
	{0x73,  0x40},
	{0x74,  0x40},
	{0x75,  0x40},
	{0xf4,  0x00},
	
	{0xfd,  0x06},
	{0x00,  0x04},
	{0x01,  0x7c},
	{0x02,  0xbf},
	{0x03,  0x86},
	{0x04,  0xbd},
	{0x05,  0x02},
	{0xfd,  0x02},
	{0x52,  0xff},
	{0xfd,  0x01},
	
	{0xfd,  0x00},
	{0xb1,  0x02},
	{0xfd,  0x01},
};

static struct rts_isp_i2c_reg g_os02h10_i2c_init_regs_hdr2_binning[] = {
	{0x53, 0xfe},
	{0x54, 0x7f},
	{0x61, 0x8c},
	{0x63, 0x05},
	{0x64, 0x01},
	{0x65, 0x00},
	{0x66, 0x02},
	{0x67, 0x00},
	{0x8d, 0x00},
	{0x8e, 0x03},
	{0x8f, 0xc0},
	{0x90, 0x02},
	{0x91, 0x1c},
	{0x95, 0x54},
	{0x98, 0x76},
	{0x9a, 0x2b},
	{0xa1, 0x02},
	{0xb6, 0x40},
	{0x23, 0x00},
	{0x24, 0x05},
	{0x26, 0x4d},
	{0x29, 0x00},
	{0x2a, 0x03},
	{0x31, 0x10},
	{0x32, 0x05},
	{0x33, 0x00},
	{0x38, 0x00},
	{0x55, 0x00},
	{0xf5, 0x01},
	{0xfd, 0x01},
	{0x03, 0x01},
	{0x04, 0x00},
	{0x4c, 0x00},
	{0x4d, 0x40},
	{0x09, 0x00},
	{0x0a, 0x00},
	{0x24, 0xff},
	{0x45, 0xff},
	//{0x31, 0x22}, // variable hdr
	{0x31, 0x62}, // fixed hdr
	{0x3e, 0x3c},
	{0x3f, 0x81},
	{0x01, 0x01},
	{0x11, 0x40},
	{0x14, 0x65},
	{0x15, 0x00},
	{0x16, 0x95},
	{0x18, 0xf3},
	{0x19, 0x47},
	{0x1a, 0x03},
	{0x1b, 0x50},
	{0x1c, 0xf0},
	{0x1d, 0x3d},
	{0x1e, 0x00},
	{0x1f, 0x27},
	{0x21, 0x74},
	{0x22, 0x90},
	{0x25, 0x00},
	{0x26, 0x77},
	{0x27, 0xf9},
	{0x2a, 0x4e},
	{0x2e, 0x28},
	{0x34, 0xf6},
	{0x35, 0x22},
	{0x36, 0xa2},
	{0x50, 0x00},
	{0x51, 0x08},
	{0x52, 0x07},
	{0x53, 0x00},
	{0x55, 0x35},
	{0x56, 0x01},
	{0x57, 0x0a},
	{0x59, 0x01},
	{0x5b, 0x13},
	{0x5d, 0x08},
	{0x5e, 0x00},
	{0x5f, 0x1d},
	{0x60, 0x1e},
	{0x68, 0x05},
	{0x69, 0x04},
	{0x6a, 0x00},
	{0x70, 0x64},
	{0x71, 0x15},
	{0x72, 0x42},
	{0x7b, 0x40},
	{0x80, 0x08},
	{0x83, 0x08},
	{0x85, 0x14},
	{0x86, 0x2d},
	{0x8a, 0xf9},
	{0x95, 0x25},
	{0x97, 0x10},
	{0x99, 0x30},
	{0x9f, 0x10},
	{0xa8, 0x10},
	{0xad, 0x00},
	{0xb0, 0x63},
	{0xb1, 0x63},
	{0xb2, 0x63},
	{0xb3, 0x63},
	{0xb4, 0x61},
	{0xb5, 0x61},
	{0xb6, 0x61},
	{0xb7, 0x61},
	{0xb8, 0x77},
	{0xb9, 0x66},
	{0xba, 0x07},
	{0xbb, 0x07},
	{0xbc, 0x07},
	{0xbd, 0x07},

	{0x29, 0x0a},
	{0x2b, 0x03},
	{0x30, 0x04},
	{0x92, 0x05},
	{0xc4, 0x00},
	{0xc5, 0x00},
	{0xc6, 0x13},
	{0xc7, 0x6d},
	{0xc9, 0x00},

	{0xd0, 0x77},
	{0xd1, 0x66},
	{0xd5, 0x12},
	{0xd7, 0x40},
	{0xd8, 0x00},
	{0xd9, 0x1E},	// max_short_exp=30
	{0xdc, 0x00},
	{0xdd, 0x01},
	{0xde, 0x04},
	{0xfd, 0x02},
	{0x00, 0x18}, //dpc disable
	{0x43, 0x03},
	{0x44, 0xc0},
	{0x60, 0x0f},
	{0x68, 0x02},
	{0x6d, 0x5d},
	{0x6e, 0xdc},
	{0x72, 0x40}, //blc=256 in 12b
	{0x73, 0x40}, //blc=256 in 12b
	{0x74, 0x40}, //blc=256 in 12b
	{0x75, 0x40}, //blc=256 in 12b
	{0x76, 0x00}, //blc=256 in 12b
	{0x78, 0x70},
	{0x79, 0x70},
	{0x7a, 0x70},
	{0x7b, 0x70},
	{0x80, 0x60},
	{0x81, 0x60},
	{0x82, 0x12},
	{0x83, 0x60},
	{0x84, 0x60},
	{0x9f, 0x12},
	{0xa1, 0x02},
	{0xa2, 0x02},
	{0xa3, 0x20},	//544
	{0xa5, 0x00},
	{0xa6, 0x03},
	{0xa7, 0xc4},	//964
	{0x72, 0x40},
	{0x73, 0x40},
	{0x74, 0x40},
	{0x75, 0x40},
	{0xf4, 0x00},

	{0xfd, 0x06},
	{0x00, 0x04},
	{0x01, 0x7c},
	{0x02, 0xbf},
	{0x03, 0x86},
	{0x04, 0xbd},
	{0x05, 0x02},
	{0xfd, 0x02},
	{0x52, 0xff},
	{0xfd, 0x01},

	{0xfd, 0x00},
	{0xb1, 0x02},
	{0xfd, 0x01},
};

static int os02h10_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if(RESOLUTION == 0)	
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30;
	i++;

	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30;			//@MLCK=24MHz
#else
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 956;
	info->modes.mode[i].size.h = 540;
	info->modes.mode[i].fps = 60;
	i++;

	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 956;
	info->modes.mode[i].size.h = 540;
	info->modes.mode[i].fps = 60;			//@MLCK=24MHz
#endif	
	i++;
	info->modes.num = i;
	
#if (!SENSOR_ID_SELECT)
	info->i2c.i2c_id = 0x3C;
#else
	info->i2c.i2c_id = 0x3B;
#endif										//Write=0x52/Read=0x53
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	
#if (!XAVI_PROJECT)
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);
#else
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);
#endif

#if (!Linear_MCLK27M)
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 3500);
#else
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 3500);
#endif
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 50);
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	down->num = i;

	return RTS_ISP_OK;
}

static int os02h10_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct os02h10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//debug("os02h10 get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	//fps_info = os02h10_get_fps_info(mode->fps, &mode->hdr);

	//if (!fps_info)
	//	return -RTS_ISP_EINVAL;

	if (mode->hdr == HDR_MODE) {
		debug("hdr line 2to1 mode\n");
		#if (RESOLUTION == 0)		
			set_init_i2c_regs(info->sensor_regs[0], g_os02h10_i2c_init_regs_hdr1, 5000);
			set_init_i2c_regs(info->sensor_regs[1], g_os02h10_i2c_init_regs_hdr2, 0);
		#else		
			set_init_i2c_regs(info->sensor_regs[0], g_os02h10_i2c_init_regs_hdr1, 5000);
			set_init_i2c_regs(info->sensor_regs[1], g_os02h10_i2c_init_regs_hdr2_binning, 0);
		#endif	

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		#if (RESOLUTION == 0)	
			info->size.w = 1928;
			info->size.h = 1088;
			info->start.x = 0;
			info->start.y = 0;
			info->hts = 1244*4;
			info->min_vts = status->min_vts = 1125;
			info->pclk = 167940000;
			info->max_vts = 65535 - info->min_vts;
			status->exp_step = 1e6 * info->hts  / info->pclk; /* us */
			info->exposure_step = status->exp_step;
		#else
			info->size.w = 964;
			info->size.h = 544;
			info->start.x = 0;
			info->start.y = 0;
			info->hts = 1244*2;
			info->min_vts = status->min_vts = 1126;
			info->pclk = 168089280;
			info->max_vts = 65535 - info->min_vts;
			status->exp_step = 1e6 * info->hts * 2  / info->pclk; /* us */
			info->exposure_step = status->exp_step;
		#endif

	} else {
		debug("linear mode\n");
		set_init_i2c_regs(info->sensor_regs[0], g_os02h10_i2c_init_regs_linear1, 5000);
		set_init_i2c_regs(info->sensor_regs[1], g_os02h10_i2c_init_regs_linear2, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		#if (RESOLUTION == 0)	
			info->size.w = 1928;
			info->size.h = 1088;
			info->start.x = 0;
			info->start.y = 0;
			#if (Linear_MCLK27M == 0)	
				info->hts = 1244*2;
				info->min_vts = status->min_vts = 1930;
				info->pclk = 144000000;
			#else
				info->hts = 1250*2;
				info->min_vts = status->min_vts = 1125;
				info->pclk = 84375000;
			#endif	
			info->max_vts = 65535 - info->min_vts;
			
		#else
			info->size.w = 964;
			info->size.h = 544;			
			info->start.x = 0;
			info->start.y = 0;
			
			info->hts = 1244*2;
			info->min_vts = status->min_vts = 965;
			info->pclk = 144000000;
			info->max_vts = 65535 - info->min_vts;
		#endif	
			status->exp_step = 1e6 * info->hts / info->pclk; /* us */
			info->exposure_step = status->exp_step;
	}

	return RTS_ISP_OK;
}

static int os02h10_start(uint32_t isp_id)
{
	struct os02h10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_exposure[1] = 0;

	return RTS_ISP_OK;
}

/*static const struct fps_info *os02h10_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_os02h10_fps_info_hdr); i++)
			if (fps <= g_os02h10_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_os02h10_fps_info_hdr))
			return NULL;

		return &g_os02h10_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_os02h10_fps_info_linear); i++)
			if (fps <= g_os02h10_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_os02h10_fps_info_linear))
			return NULL;

		return &g_os02h10_fps_info_linear[i];
	}
}*/






static int os02h10_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct os02h10_status *status;
	

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts) * status->exp_step;

		//debug("max_exposure = %f, min_exposure = %f\n", max_exposure[0], min_exposure[0]);
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint16_t max_long_exp = vts - Short_to_Long -16;
		float define_sensor_short_exp_min;
		uint16_t dummy;
		


		// Sensor exposure formula
		// short exposure <= vb ,vb = frame_length(VTS) - window_height(sensor actually output = 1456) - 20 - 16
		// long exposure + short exposure<= framelength => long exposure <= framelength - short exposure
		// short expousre line(time) = interval between long and short exposure frame.

		//tmp1 = AE_MAX_SHORT_EXP_BASE;
		//tmp2 = (uint32_t)(max_long_exp / (ratio[0] + 1));
		tmp1 = (uint32_t)(max_long_exp / (ratio[0] + 1));
		#if (RESOLUTION == 0)
			dummy = abs( vts - 1125);
			//debug("vts= %d \n", vts);
			//debug("dummy= %d \n", dummy);
			tmp2 = 49 + dummy;
		#else
			dummy = abs( vts - 1126);
			//debug("vts1= %d \n", vts);
			//debug("dummy1= %d \n", dummy);
			tmp2 = 29 + dummy;
		#endif
		
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		
		//debug("tmp1_final = %d \n", tmp1);
		
		if (status->fusion_mode)
			define_sensor_short_exp_min = SENSOR_MIN_EXP_LINE_VHDR_OFF;
		else
			define_sensor_short_exp_min = SENSOR_MIN_EXP_LINE;

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = define_sensor_short_exp_min * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];

		//debug("long_max_exposure_=%f, long_min_exposure=%f\n", max_exposure[0], min_exposure[0]);
		//debug("short_max_exposure_=%f, short_min_exposure=%f\n", max_exposure[1], min_exposure[1]);
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0x00;

	if (fgain >= 15.5)
		reg_value = 0xff;
	else if (fgain >= 15)
		reg_value = 0xf0 | (uint16_t)((fgain - 7) * 16.0f - 128.0f);
	else if (fgain >= 14)
		reg_value = 0xe0 | (uint16_t)((fgain - 6) * 16.0f - 128.0f);
	else if (fgain >= 13)
		reg_value = 0xd0 | (uint16_t)((fgain - 5) * 16.0f - 128.0f);
	else if (fgain >= 12)
		reg_value = 0xc0 | (uint16_t)((fgain - 4) * 16.0f - 128.0f);
	else if (fgain >= 11)
		reg_value = 0xb0 | (uint16_t)((fgain - 3) * 16.0f - 128.0f);
	else if (fgain >= 10)
		reg_value = 0xa0 | (uint16_t)((fgain - 2) * 16.0f - 128.0f);
	else if (fgain >= 9)
		reg_value = 0x90 | (uint16_t)((fgain - 1) * 16.0f - 128.0f);
	else if (fgain >= 8)
		reg_value = 0x80 | (uint16_t)(fgain * 16.0f - 128.0f);
	else if (fgain >= 7)
		reg_value = 0x70 | (uint16_t)((fgain - 3) * 16.0f - 64.0f);
	else if (fgain >= 6)
		reg_value = 0x60 | (uint16_t)((fgain - 2) * 16.0f - 64.0f);
	else if (fgain >= 5)
		reg_value = 0x50 | (uint16_t)((fgain - 1) * 16.0f - 64.0f);
	else if (fgain >= 4)
		reg_value = 0x40 | (uint16_t)(fgain * 16.0f - 64.0f);
	else if (fgain >= 3)
		reg_value = 0x30 | (uint16_t)((fgain - 1) * 16.0f - 32.0f);
	else if (fgain >= 2)
		reg_value = 0x20 | (uint16_t)(fgain * 16.0f - 32.0f);
	else
		reg_value = 0x10 | (uint16_t)(fgain * 16.0f - 16.0f);

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
		float fgain = 1.0;

	if (reg_value >= 0xff)
		fgain = 15.5f;
	else if (reg_value >= 0xf8)
		fgain = 15.5f;
	else if (reg_value >= 0xf0)
		fgain = 15.0f;
	else if (reg_value >= 0xe8)
		fgain = 14.5f;
	else if (reg_value >= 0xe0)
		fgain = 14.0f;
	else if (reg_value >= 0xd8)
		fgain = 13.5f;
	else if (reg_value >= 0xd0)
		fgain = 13.0f;
	else if (reg_value >= 0xc8)
		fgain = 12.5f;
	else if (reg_value >= 0xc0)
		fgain = 12.0f;
	else if (reg_value >= 0xb8)
		fgain = 11.5f;
	else if (reg_value >= 0xb0)
		fgain = 11.0f;
	else if (reg_value >= 0xa8)
		fgain = 10.5f;
	else if (reg_value >= 0xa0)
		fgain = 10.0f;
	else if (reg_value >= 0x98)
		fgain = 9.5f;
	else if (reg_value >= 0x90)
		fgain = 9.0f;
	else if (reg_value >= 0x88)
		fgain = 8.5f;
	else if (reg_value >= 0x80)
		fgain = 8.0f;
	else if (reg_value >= 0x7c)
		fgain = 7.75f;
	else if (reg_value >= 0x78)
		fgain = 7.5f;
	else if (reg_value >= 0x74)
		fgain = 7.25f;
	else if (reg_value >= 0x70)
		fgain = 7.0f;
	else if (reg_value >= 0x6c)
		fgain = 6.75f;
	else if (reg_value >= 0x68)
		fgain = 6.5f;
	else if (reg_value >= 0x64)
		fgain = 6.25f;
	else if (reg_value >= 0x60)
		fgain = 6.0f;
	else if (reg_value >= 0x5c)
		fgain = 5.75f;
	else if (reg_value >= 0x58)
		fgain = 5.5f;
	else if (reg_value >= 0x54)
		fgain = 5.25f;
	else if (reg_value >= 0x50)
		fgain = 5.0f;
	else if (reg_value >= 0x4c)
		fgain = 4.75f;
	else if (reg_value >= 0x48)
		fgain = 4.5f;
	else if (reg_value >= 0x44)
		fgain = 4.25f;
	else if (reg_value >= 0x40)
		fgain = 4.0f;
	else if (reg_value >= 0x3e)
		fgain = 3.875f;
	else if (reg_value >= 0x3c)
		fgain = 3.75f;
	else if (reg_value >= 0x3a)
		fgain = 3.625f;
	else if (reg_value >= 0x38)
		fgain = 3.5f;
	else if (reg_value >= 0x36)
		fgain = 3.375f;
	else if (reg_value >= 0x34)
		fgain = 3.25f;
	else if (reg_value >= 0x32)
		fgain = 3.125f;
	else if (reg_value >= 0x30)
		fgain = 3.0f;
	else if (reg_value >= 0x2e)
		fgain = 2.875f;
	else if (reg_value >= 0x2c)
		fgain = 2.75f;
	else if (reg_value >= 0x2a)
		fgain = 2.625f;
	else if (reg_value >= 0x28)
		fgain = 2.5f;
	else if (reg_value >= 0x26)
		fgain = 2.375f;
	else if (reg_value >= 0x24)
		fgain = 2.25f;
	else if (reg_value >= 0x22)
		fgain = 2.125f;
	else if (reg_value >= 0x20)
		fgain = 2.0f;
	else
		fgain = 1.0f + (float)((reg_value - 0x10) / 16.0f);
	return fgain;
}

static int os02h10_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct os02h10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);
	if (status->hdr == HDR_MODE) {
		gain_reg = get_sensor_gain_reg(again[1]);
		again[1] = get_sensor_real_gain(gain_reg);
	}

	return RTS_ISP_OK;
}

static int os02h10_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct os02h10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int os02h10_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t gain_reg;
	uint16_t dummy;
	struct os02h10_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;



	status = &g_status[isp_id];

	
	
	if (status->hdr == LINEAR_MODE) {
		//frame_length = exp_gain->vts;
		reg = regs->reg;
		gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);	
		i = 0;
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			uint32_t exposure;
	
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			/* page */
			set_sync_i2c(&reg[i++], 0xfd, 1);
			
			//printf("exposure_rows= %d,exposure time AE =%.f, exp_step = %.f\n",exposure_rows[0],exp_gain->exposure[0],status->exp_step );
			
			dummy = abs(exp_gain->vts - 1125);
			set_sync_i2c(&reg[i++], 0x05, dummy >> 8);
			set_sync_i2c(&reg[i++], 0x06, dummy & 0xff);
	
			/* gain */
			set_sync_i2c(&reg[i++], 0x24, gain_reg);
	
			set_sync_i2c(&reg[i++], 0x3, (exposure_rows[0] >> 8) & 0xff);
			set_sync_i2c(&reg[i++], 0x4, exposure_rows[0] & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];
	
			/* end & launch group1 */
			set_sync_i2c(&reg[i++], 1, 1);
		} else {
			/* page */
			set_sync_i2c(&reg[i++], 0xfd, 0x01);
	
			dummy = abs(exp_gain->vts - 1125);
			set_sync_i2c(&reg[i++], 0x05, dummy >> 8);
			set_sync_i2c(&reg[i++], 0x06, dummy & 0xff);
	
			/* gain */
			set_sync_i2c(&reg[i++], 0x24, gain_reg);
	
			/* end & launch group1 */
			set_sync_i2c(&reg[i++], 0x01, 0x01);
		}
	} else {
		//frame_length = exp_gain->vts;
		reg = regs->reg;
		gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);	
		i = 0;
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			uint32_t exposure;
	
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			/* page */
			set_sync_i2c(&reg[i++], 0xfd, 1);
			set_sync_i2c(&reg[i++], 0x03, (exposure_rows[0] >> 8) & 0xff);
			set_sync_i2c(&reg[i++], 0x04, exposure_rows[0] & 0xff);
			status->last_exposure[0] = exp_gain->exposure[0];		
	
			/* end & launch group1 */
			set_sync_i2c(&reg[i++], 0x01, 0x01);
		}
		if (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f) {
			uint32_t exposure;
	
			exposure_rows[1] = exp_gain->exposure[1] / status->exp_step + 0.5f;
			/* page */
			set_sync_i2c(&reg[i++], 0xfd, 1);
			set_sync_i2c(&reg[i++], 0x4c, (exposure_rows[1] >> 8) & 0xff);
			set_sync_i2c(&reg[i++], 0x4d, exposure_rows[1] & 0xff);
			status->last_exposure[1] = exp_gain->exposure[1];		
	
			/* end & launch group1 */
			set_sync_i2c(&reg[i++], 0x01, 0x01);
		}		
		/* page */
		set_sync_i2c(&reg[i++], 0xfd, 0x01);

		/* gain */
		set_sync_i2c(&reg[i++], 0x24, gain_reg);	//Long exposure gain
		set_sync_i2c(&reg[i++], 0x45, gain_reg);	//Short exposure gain
	
		#if (RESOLUTION == 0)
			dummy = abs(exp_gain->vts - 1125);
		#else
			dummy = abs(exp_gain->vts - 1126);
		#endif
		//debug("vts= %d \n", exp_gain->vts);
		//debug("dummy= %d \n", dummy);
		
		set_sync_i2c(&reg[i++], 0x05, dummy >> 8);
		set_sync_i2c(&reg[i++], 0x06, dummy & 0xff);
		
		/* end & launch group1 */
		set_sync_i2c(&reg[i++], 0x01, 0x01);

	
	}regs->num = i;
	return RTS_ISP_OK;
}

static int os02h10_get_short_exp_mode(uint32_t isp_id)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct os02h10_status *status = &g_status[isp_id];
	return status->fusion_mode;
}

static int os02h10_set_short_exp_exit_thd(uint32_t isp_id, uint16_t exit_thd)
{
	/*if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct os02h10_status *status = &g_status[isp_id];

	if (status->fusion_mode && exit_thd <= 512) {
		status->fusion_mode = VHDR_EXP_MODE_MULTIPLE;
	}
	status->short_exp_mode_exit_thd = exit_thd;
	return 0; */
}

static int os02h10_set_mirror_flip(uint32_t isp_id,
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
		#if (RESOLUTION == 0)
			case 0: //normal
			default:
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x0);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 1);
				HAL_WRITE32(0x40300000, 0xc04, 0);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 1);
				HAL_WRITE32(0x40300000, 0x20c04, 0);
				HAL_WRITE32(0x40300000, 0x20c10, 1);
				
			break;
			case 1: 	// Mirror
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x1);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 0);
				HAL_WRITE32(0x40300000, 0xc04, 0);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 0);
				HAL_WRITE32(0x40300000, 0x20c04, 0);
				HAL_WRITE32(0x40300000, 0x20c10, 1);
			break;
			case 2: 		// VFlip
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x2);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 1);
				HAL_WRITE32(0x40300000, 0xc04, 1);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 1);
				HAL_WRITE32(0x40300000, 0x20c04, 1);
				HAL_WRITE32(0x40300000, 0x20c10, 1);		
			break;
			case 3: 	// Rotate
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x3);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 0);
				HAL_WRITE32(0x40300000, 0xc04, 1);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 0);
				HAL_WRITE32(0x40300000, 0x20c04, 1);
				HAL_WRITE32(0x40300000, 0x20c10, 1);		
			break;
		#else
			case 0: //normal
			default:
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x80);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 1);
				HAL_WRITE32(0x40300000, 0xc04, 1);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 1);
				HAL_WRITE32(0x40300000, 0x20c04, 1);
				HAL_WRITE32(0x40300000, 0x20c10, 1);
				
			break;
			case 1: 	// Mirror
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x81);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 0);
				HAL_WRITE32(0x40300000, 0xc04, 1);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 0);
				HAL_WRITE32(0x40300000, 0x20c04, 1);
				HAL_WRITE32(0x40300000, 0x20c10, 1);
			break;
			case 2: 		// VFlip
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x82);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 1);
				HAL_WRITE32(0x40300000, 0xc04, 0);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 1);
				HAL_WRITE32(0x40300000, 0x20c04, 0);
				HAL_WRITE32(0x40300000, 0x20c10, 1);		
			break;
			case 3: 	// Rotate
				set_sync_i2c(&reg[i++], 0xfd, 0x1);
				set_sync_i2c(&reg[i++], 0x3f, 0x83);
				set_sync_i2c(&reg[i++], 0x01, 0x1);
				HAL_WRITE32(0x40300000, 0xc00, 0);
				HAL_WRITE32(0x40300000, 0xc04, 0);
				HAL_WRITE32(0x40300000, 0xc10, 1);
				HAL_WRITE32(0x40300000, 0x20c00, 0);
				HAL_WRITE32(0x40300000, 0x20c04, 0);
				HAL_WRITE32(0x40300000, 0x20c10, 1);		
			break;
		#endif	
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int os02h10_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;


    rts_isp_sensor_access_prepare();

	/* page */
	reg.addr = 0xfd;
	reg.data = 0x00;
	ret = rts_isp_write_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;

	reg.addr = 0x02;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;

	id = reg.data << 8;

	reg.addr = 0x03;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
	rts_isp_sensor_access_unprepare();
	
	if (ret)
		return ret;

	id |= reg.data;

	if (id == 0x5302)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops os02h10_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "os02h10",
	.get_info = os02h10_get_info,
	.get_init_info = os02h10_get_init_info,
	.start = os02h10_start,
	.get_exposure_range = os02h10_get_exposure_range,
	.get_tuned_again = os02h10_get_tuned_again,
	.get_tuned_dgain = os02h10_get_tuned_dgain,
	.get_exposure_gain_info = os02h10_get_exposure_gain_info,
	.set_mirror_flip = os02h10_set_mirror_flip,
	.set_short_exp_exit_thd = os02h10_set_short_exp_exit_thd,
	.get_short_exp_mode = os02h10_get_short_exp_mode,
	.check = os02h10_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &os02h10_ops;
}

