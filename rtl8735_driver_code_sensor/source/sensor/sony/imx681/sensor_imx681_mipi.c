/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include <math.h>
#include <isp_reg_lib.h>


#if _IMX681_SENSOR_

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define float_tol 0.0001f
#define float_ne(x, y) (fabsf((float)x - (float)y) > float_tol)
#define float_eq(x, y) (fabsf((float)x - (float)y) < float_tol)

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define ANALOG_GAIN_MAX_RATIO 16 //analog gain

#define HAL_WRITE32(base, addr, value32)  \
        ((*((volatile u32*)(base + addr))) = rtk_cpu_to_le32(value32))
        

enum {
	BINNING_MODE=0,
	FULL_MODE
};

static int sensor_mode = BINNING_MODE;	//0=BINNING, 1=FULL


struct imx681_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
};

static struct imx681_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static struct rts_isp_i2c_reg g_imx681_i2c_init_regs_global[] = {
	/*Global Setting*/
	{0x0136,0x18},
	{0x0137,0x00},
				 
	{0x002C,0x01},
	{0x002D,0x05},
				 
	{0x0111,0x02},
				 
	{0x30EB,0x05},
	{0x30EB,0x0C},
	{0x300A,0xFF},
	{0x300B,0xFF},
	{0x3532,0xFF},
	{0x3533,0xFF},
				 
	{0x051E,0x00},
	{0x0905,0x04},
	{0x2029,0x01},
	{0x202A,0x11},
	{0x20A1,0x00},
	{0x20A2,0x02},
	{0x20A3,0x03},
	{0x20AC,0x01},
	{0x20AD,0x01},
	{0x20AE,0x01},
	{0x20AF,0x01},
	{0x20B0,0x00},
	{0x20B1,0x01},
	{0x20B2,0x02},
	{0x20B3,0x03},
	{0x706F,0x00},
	{0x7130,0x08},
	{0x7131,0x08},
	{0x7408,0x89},
	{0x7437,0x3D},
	{0x7439,0x29},
	{0x7443,0x38},
	{0x7447,0x55},
	{0x744B,0x00},
	{0x7451,0x8E},
	{0x746D,0x29},
	{0x747D,0x68},
	{0x7481,0x60},
	{0x7491,0x2D},
	{0x7493,0x31},
	{0x74A5,0x52},
	{0x74AF,0x4A},
	{0x74B5,0x1F},
	{0x74B7,0x31},
	{0x74BD,0x75},
	{0x74C5,0x06},
	{0x74C9,0x52},
	{0x74D3,0x4A},
	{0x74D9,0x1F},
	{0x74DB,0x31},
	{0x74E1,0x75},
	{0x74E9,0x06},
	{0x74ED,0x52},
	{0x74F7,0x4A},
	{0x74FD,0x1F},
	{0x74FF,0x31},
	{0x7505,0x75},
	{0x750D,0x06},
	{0x7537,0x38},
	{0x753D,0x4A},
	{0x753F,0x4A},
	{0x7541,0x4A},
	{0x7549,0x8E},
	{0x754F,0x75},
	{0x7551,0x75},
	{0x7553,0x75},
	{0x792B,0x39},
	{0x792D,0x43},
	{0x79D3,0x25},
	{0x79D6,0x8E},
	{0x79D7,0x01},
	{0x79D8,0xE7},
	{0x79D9,0x25},
	{0x79DB,0x76},
	{0x79DC,0x8E},
	{0x79DD,0x01},
	{0x79DE,0xE7},
	{0x79DF,0x25},
	{0x79E1,0x76},
	{0x79E2,0x8E},
	{0x79E3,0x01},
	{0x79E4,0xE7},
	{0x79E5,0x25},
	{0x79E7,0x76},
	{0x79E8,0x8E},
	{0x7A01,0xFF},
	{0x7A29,0x6C},
	{0x7A2B,0xDA},
	{0x7A34,0x6C},
	{0x7A37,0xDA},
	{0x7A40,0x6C},
	{0x7A43,0xDA},
	{0x7B08,0x00},
	{0x7B09,0x01},
	{0x7C03,0x38},
	{0x7C09,0x4A},
	{0x7C0B,0x4A},
	{0x7C0D,0x4A},
	{0x7C13,0x8E},
	{0x7C19,0x75},
	{0x7C1B,0x75},
	{0x7C1D,0x75},
	{0x7C90,0x00},
	{0x7C91,0x00},
	{0x7C92,0x00},
	{0x7C9D,0x01},
	{0x7C9E,0x01},
	{0x7C9F,0x01},
	{0x7E9B,0x07},
	{0x7F09,0x00},
	{0x7F36,0x00},
	{0x7F4F,0x0A},
	{0x7F50,0x0A},
	{0x7F51,0x0A},
	{0x7F55,0x05},
	{0x7F56,0x05},
	{0x7F57,0x05},
	{0x7F5B,0x03},
	{0x7F5C,0x03},
	{0x7F5D,0x03},
	{0x7F61,0x03},
	{0x7F62,0x03},
	{0x7F63,0x03},
	{0x7F67,0x03},
	{0x7F68,0x03},
	{0x7F69,0x03},
	{0x7F6A,0x05},
	{0x7F6B,0x05},
	{0x7F6C,0x05},
	{0x7F6D,0x11},
	{0x7F6E,0x14},
	{0x7F6F,0x14},
	{0x7F73,0x14},
	{0x7F74,0x1C},
	{0x7F75,0x14},
	{0x7F76,0x08},
	{0x7F79,0x14},
	{0x7F7A,0x1C},
	{0x7F7B,0x14},
	{0x7F7F,0x1C},
	{0x7F80,0x1C},
	{0x7F81,0x1C},
	{0x7F85,0x1C},
	{0x7F86,0x1C},
	{0x7F87,0x1C},
	{0x7F9D,0x09},
	{0x7F9E,0x09},
	{0x7F9F,0x09},
	{0x7FA3,0x09},
	{0x7FA4,0x09},
	{0x7FA5,0x09},
	{0x7FAC,0x00},
	{0x7FAD,0x00},
	{0x7FAE,0x00},
	{0x7FAF,0x00},
	{0x7FB0,0x00},
	{0x7FB1,0x00},
	{0x7FB2,0x00},
	{0x7FB3,0x00},
	{0x7FB4,0x00},
	{0x7FB5,0x00},
	{0x7FB6,0x00},
	{0x7FB7,0x00},
	{0x7FB8,0x00},
	{0x7FB9,0x00},
	{0x7FBA,0x00},
	{0x7FBB,0x00},
	{0x7FBC,0x00},
	{0x7FBD,0x00},
	{0x7FBE,0x00},
	{0x7FBF,0x00},
	{0x7FC0,0x00},
	{0x7FC1,0x00},
	{0x7FC2,0x00},
	{0x7FC3,0x00},
	{0x7FCB,0x37},
	{0x7FCD,0x37},
	{0x7FCF,0x37},
	{0x7FD7,0x44},
	{0x7FD9,0x44},
	{0x7FDB,0x44},
	{0x7FDD,0x38},
	{0x7FE3,0x4A},
	{0x7FE5,0x4A},
	{0x7FE7,0x4A},
	{0x7FEF,0x4A},
	{0x7FF1,0x4A},
	{0x7FF3,0x4A},
	{0x7FFB,0x4A},
	{0x7FFD,0x4A},
	{0x7FFF,0x4A},
	{0x8007,0x62},
	{0x8009,0x62},
	{0x800B,0x62},
	{0x8013,0x6F},
	{0x8015,0x6F},
	{0x8017,0x6F},
	{0x8019,0x8E},
	{0x801F,0x75},
	{0x8021,0x75},
	{0x8023,0x75},
	{0x802B,0x75},
	{0x802D,0x75},
	{0x802F,0x75},
	{0x8037,0x75},
	{0x8039,0x75},
	{0x803B,0x75},
	{0x803C,0x13},
	{0x803D,0x17},
	{0x803E,0x15},
	{0x803F,0x11},
	{0x8040,0x0A},
	{0x8041,0x08},
	{0x8047,0x17},
	{0x80F0,0x24},
	{0x80F1,0x1B},
	{0x80F2,0x1A},
	{0x80F3,0x14},
	{0x80F4,0x14},
	{0x80F5,0x12},
	{0x80F6,0x25},
	{0x80F7,0x1C},
	{0x80F8,0x1B},
	{0x80F9,0x18},
	{0x80FA,0x17},
	{0x80FB,0x18},
	{0x80FC,0x26},
	{0x80FD,0x1E},
	{0x80FE,0x1D},
	{0x80FF,0x1C},
	{0x8100,0x1B},
	{0x8101,0x1C},
	{0x8102,0x27},
	{0x8103,0x1E},
	{0x8104,0x1D},
	{0x8105,0x1E},
	{0x8106,0x1E},
	{0x8107,0x1E},
	{0x8108,0x27},
	{0x8109,0x1E},
	{0x810A,0x1E},
	{0x810B,0x1E},
	{0x810C,0x1E},
	{0x810D,0x1F},
	{0x810E,0x00},
	{0x8168,0x0B},
	{0x8169,0x0B},
	{0x816A,0x09},
	{0x816B,0x0F},
	{0x816C,0x0F},
	{0x816D,0x0F},
	{0x816E,0x0B},
	{0x816F,0x0B},
	{0x8170,0x0A},
	{0x8171,0x0F},
	{0x8172,0x0F},
	{0x8173,0x0F},
	{0x8174,0x0D},
	{0x8175,0x0C},
	{0x8176,0x09},
	{0x8177,0x0F},
	{0x8178,0x0F},
	{0x8179,0x0F},
	{0x817A,0x0C},
	{0x817B,0x0D},
	{0x817C,0x09},
	{0x817D,0x0F},
	{0x817E,0x0F},
	{0x817F,0x0F},
	{0x8180,0x0D},
	{0x8181,0x0D},
	{0x8182,0x09},
	{0x8183,0x0F},
	{0x8184,0x0F},
	{0x8185,0x0F},
	{0x81B0,0x03},
	{0x81E3,0x04},
	{0x81E4,0x04},
	{0x81E9,0x04},
	{0x81EA,0x04},
	{0x81EF,0x04},
	{0x81F0,0x04},
	{0x9186,0x00},
	{0xD030,0x01},
	{0xD04C,0x10},
	{0xD123,0x75},
	{0xD144,0x10},
	{0xD1AF,0x08},
	{0xD1BD,0x67},
	{0xD1D4,0x04},
	{0xD1D5,0x04},
	{0xD1D6,0x07},
	{0xD1D7,0x07},
	{0xD1D9,0x40},
	{0xD1DB,0x58},
	{0xD1DD,0xD4},
	{0xD1DF,0xD4},
	{0xD1E1,0xD4},
	{0xD348,0x0F},
	{0xD357,0x00},
	{0xD3AE,0x11},
	{0xD3AF,0x44},
	{0xD3B1,0x7D},
	{0xD803,0xF0},
	{0xD80B,0xF0},
	{0xD813,0xF1},
	{0xD81B,0xF0},
	{0xD843,0xF1},
	{0xD84F,0xF0},
	{0xD934,0x23},
	{0xD935,0xC8},
	{0xD938,0x27},
	{0xD939,0x10},
	{0xD93A,0x23},
	{0xD93B,0xC8},
	{0xD955,0x07},
	{0xD95A,0x04},
	{0xD95B,0x0A},
	{0xD95C,0x1E},
	{0xD95D,0x00},
	{0xD95E,0x14},
	{0xD95F,0x21},
	{0xD960,0x00},
	{0xD961,0x00},
	{0xD962,0x0A},
	{0xD963,0x50},
	{0xD964,0x0A},
	{0xD965,0xA0},
	{0xD966,0x00},
	{0xD967,0x28},
	{0xD968,0x0A},
	{0xD969,0x50},
	{0xD96A,0x0A},
	{0xD96B,0xA0},
	{0xD96C,0x00},
	{0xD96D,0x00},
	{0xD96E,0x0A},
	{0xD96F,0x44},
	{0xD970,0x0A},
	{0xD971,0x50},
	{0xD972,0x00},
	{0xD973,0x00},
	{0xD974,0x0A},
	{0xD975,0x44},
	{0xD976,0x0A},
	{0xD977,0x50},
	{0xDA10,0x00},
	{0xDA11,0x14},
	{0xDA12,0x64},
	{0xDA13,0x00},
	{0xDA14,0x14},
	{0xDA15,0xC8},
	{0xDA22,0x00},
	{0xDA23,0x56},
	{0xDA24,0x00},
	{0xDA25,0xB5},
	{0xDA26,0x00},
	{0xDA27,0xE8},
	{0xDA28,0x08},
	{0xDA29,0xA6},
	{0xDA2A,0x00},
	{0xDA2B,0xA2},
	{0xDA2F,0x01},
};

static struct rts_isp_i2c_reg g_imx681_i2c_init_regs_binning[] = {
				 
	/*binning mod setting*/
	{0x0110,0x00},
	{0x0112,0x0A},
	{0x0113,0x0A},
	{0x0114,0x01},
				 
	{0x0342,0x1E},	//LINE_LENGTH_PCK[15:8]
	{0x0343,0xA0},	//LINE_LENGTH_PCK[7:0]	7840
				 
	{0x033D,0x00},	//FRM_LENGTH_LINES[23:16]
	{0x033E,0x0C},	//FRM_LENGTH_LINES[15:8]
	{0x033F,0x06},	//FRM_LENGTH_LINES[7:0]	3060 +18
				 
	{0x0344,0x00},
	{0x0345,0x08},	//X_ADD_STA[7:0]
	{0x0346,0x00},
	{0x0347,0x40},	//Y_ADD_STA[7:0]
	{0x0348,0x0f},	//X_ADD_END[11:8]	
	{0x0349,0xC7},	//X_ADD_END[7:0]		4039		//h2v2:   X_ADD_END+1 multiple 4, max 4040
	{0x034A,0x0C},	//Y_ADD_END[11:8]
	{0x034B,0x0F},	//Y_ADD_END[7:0]		3087		//h2v2:   Y_ADD_END+1 multiple 4, max 3088
				 
	{0x017C,0x02},
	{0x017D,0x02},
	{0x017E,0x00},
	{0x017F,0x01},
	{0x0180,0x00},
	{0x038C,0x13},
	{0x038D,0x33},
	{0x2000,0x01},
				 
	{0x0408,0x00},	//DIG_CROP_X_OFFSET[11:8]
	{0x0409,0x00},	//DIG_CROP_X_OFFSET[7:0]
	{0x040A,0x00},	//DIG_CROP_Y_OFFSET[11:8]
	{0x040B,0x00},	//DIG_CROP_Y_OFFSET[7:0]
	{0x040C,0x07},	//DIG_CROP_IMAGE_WIDTH[11:8]
	{0x040D,0xE0},	//DIG_CROP_IMAGE_WIDTH[7:0]		2016			//multiple 4
	{0x040E,0x05},	//DIG_CROP_IMAGE_HEIGHT[11:8]
	{0x040F,0xe8},	//DIG_CROP_IMAGE_HEIGHT[7:0]		1512			//multiple 2
				 
	{0x034C,0x07},	//X_OUT_SIZE[13:8]				2016			//multiple 4
	{0x034D,0xE4},	//X_OUT_SIZE[7:0]
	{0x034E,0x05},	//Y_OUT_SIZE[12:8]				1512			//multiple 2
	{0x034F,0xe8},	//Y_OUT_SIZE[7:0]
				 
	{0x0301,0x06},
	{0x0303,0x02},
	{0x0305,0x03},
	{0x0306,0x01},
	{0x0307,0x0E},
	{0x030D,0x03},
	{0x030E,0x00},
	{0x030F,0xFA},
	{0x0323,0x01},
				 
	{0x0229,0x00},
	{0x022A,0x0B},
	{0x022B,0xE2},
				 
	{0x0204,0x00},
	{0x0205,0x00},
	{0x020E,0x01},
	{0x020F,0x00},
	{0x0210,0x01},
	{0x0211,0x00},
	{0x0212,0x01},
	{0x0213,0x00},
	{0x0214,0x01},
	{0x0215,0x00},
				 
	{0x6A83,0x03},
	{0x7E9B,0x06},
	{0xD1CE,0x00},
	{0xDC3C,0x01},
				 
	{0x0368,0x00},
	{0x036A,0x08},
	{0x036B,0x70},
				 
	{0x0115,0x01},
				 
	{0x0182,0x08},
	{0x0183,0x08},
	{0x0184,0x01},
	{0x0186,0x08},
	{0x0187,0x08},
	{0x0364,0x01},
	{0x0365,0xF8},
	{0x0366,0x01},
	{0x0367,0x7A},
				 
	{0x0100,0x01},

};

static struct rts_isp_i2c_reg g_imx681_i2c_init_regs_full[] = {
	{0x0110,0x00},
	{0x0112,0x0A},
	{0x0113,0x0A},
	{0x0114,0x01},
	
	{0x0342,0x3B},	//LINE_LENGTH_PCK[15:8]
	{0x0343,0x00},	//LINE_LENGTH_PCK[7:0]		15104	
	
	{0x033D,0x00},	//FRM_LENGTH_LINES[23:16]
	{0x033E,0x0B},	//FRM_LENGTH_LINES[15:8]
	{0x033F,0xED},	//FRM_LENGTH_LINES[7:0]		3053
	
	{0x0344,0x00},
	{0x0345,0x08},	//X_ADD_STA[7:0]
	{0x0346,0x00},
	{0x0347,0x40},	//Y_ADD_STA[7:0]
	{0x0348,0x0F},	//X_ADD_END[11:8]	
	{0x0349,0xC7},	//X_ADD_END[7:0]		4039		//h2v2:   X_ADD_END+1 multiple 8, max 4040
	{0x034A,0x0C},	//Y_ADD_END[11:8]	
	{0x034B,0x0F},	//Y_ADD_END[7:0]		3087		//h2v2:   Y_ADD_END+1 multiple 8, max 3088
	
	{0x017C,0x01},
	{0x017D,0x01},
	{0x017E,0x00},
	{0x017F,0x01},
	{0x0180,0x00},
	{0x038C,0x13},
	{0x038D,0x33},
	{0x2000,0x01},
	
	{0x0408,0x00},
	{0x0409,0x00},	//DIG_CROP_X_OFFSET[7:0]					multiple 4
	{0x040A,0x00},
	{0x040B,0x00},	//DIG_CROP_Y_OFFSET[7:0]					multiple 2
	{0x040C,0x0F},
	{0x040D,0xC0},	//DIG_CROP_IMAGE_WIDTH[7:0]		4032	multiple 4
	{0x040E,0x0B},
	{0x040F,0xD0},	//DIG_CROP_IMAGE_HEIGHT[7:0]		3024	multiple 2
	
	{0x034C,0x0F},
	{0x034D,0xC0},	//X_OUT_SIZE[7:0]					4032	multiple 4
	{0x034E,0x0B},
	{0x034F,0xD0},	//Y_OUT_SIZE[7:0]					3024	multiple 4
	
	{0x0301,0x06},
	{0x0303,0x02},
	{0x0305,0x03},
	{0x0306,0x01},
	{0x0307,0x0E},
	{0x030D,0x03},
	{0x030E,0x00},
	{0x030F,0xFA},
	{0x0323,0x01},
	
	{0x0229,0x00},
	{0x022A,0x0B},
	{0x022B,0xE5},
	
	{0x0204,0x00},
	{0x0205,0x00},
	{0x020E,0x01},
	{0x020F,0x00},
	{0x0210,0x01},
	{0x0211,0x00},
	{0x0212,0x01},
	{0x0213,0x00},
	{0x0214,0x01},
	{0x0215,0x00},
	
	{0x6A83,0x03},
	{0x7E9B,0x02},
	{0xD1CE,0x00},
	{0xDC3C,0x01},
	
	{0x0368,0x01},
	{0x036A,0x0B},
	{0x036B,0xD0},
	
	{0x0115,0x01},
	
	{0x0182,0x08},
	{0x0183,0x08},
	{0x0184,0x01},
	{0x0186,0x08},
	{0x0187,0x08},
	{0x0364,0x01},
	{0x0365,0xF8},
	{0x0366,0x01},
	{0x0367,0x7A},

	{0x0100,0x01},

};

static int imx681_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	debug("@ imx681_get_info isp_id = %d\n",isp_id);

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	if(sensor_mode == BINNING_MODE){
		printf("imx681_get_info : BINNING_MODE\n");
		info->modes.mode[i].hdr = LINEAR_MODE;
		info->modes.mode[i].size.w = 2000;
		info->modes.mode[i].size.h = 1500;
		info->modes.mode[i].fps = 30.01f; //@MLCK=24MHz
	}
	else{		
		printf("imx681_get_info : FULL_MODE\n");
		info->modes.mode[i].hdr = LINEAR_MODE;
		info->modes.mode[i].size.w = 1280;
		info->modes.mode[i].size.h = 720;
		info->modes.mode[i].fps = 15.61f; //@MLCK=24MHz
	}
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = 0x10;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 1000);
	
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH,1000 );	
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 4000);
	
	up->num = i;
	
	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);	
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	
	down->num = i;

	return RTS_ISP_OK;
}


static int imx681_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct imx681_status *status;
	//uint32_t DDR_Addr_tmp, DDR_Lens_tmp;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	debug("@ imx681_get_init_info mode->fps = %d\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	if(sensor_mode == BINNING_MODE){
		printf("imx681_get_init_info : BINNING_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_imx681_i2c_init_regs_global, 0);
		set_init_i2c_regs(info->sensor_regs[1], g_imx681_i2c_init_regs_binning, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2016;
		info->size.h = 1512;
		info->start.x = 0;
		info->start.y = 0;

		//Line Length 7840 ,  Frame Length 3060

		info->hts = 2178;			//200 000 000/30.01/3060 = 2178
		info->pclk = 200000000;		//MIPI data rate = 1000Mbps,  1000*2/10=200Mbps
		
		info->min_vts = status->min_vts = 3060+18;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */  //10.88us
	}
	else{
		printf("imx681_get_init_info : FULL_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_imx681_i2c_init_regs_global, 0);
		set_init_i2c_regs(info->sensor_regs[1], g_imx681_i2c_init_regs_full, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;

//		info->size.w = 4032;
//		info->size.h = 3024;	
		info->size.w = 1288;
		info->size.h = 728;
		info->start.x = 1;
		info->start.y = 0;

		//Line Length 15104 , Frame Length 3053


		info->hts = 4196;			//200 000 000/15.61/3053 = 2178
		info->pclk = 200000000;		//MIPI data rate = 1000Mbps,  1000*2/10=200Mbps
		
		info->min_vts = status->min_vts = 3053;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */  //20.97us
	}

	return RTS_ISP_OK;
}

static int imx681_start(uint32_t isp_id)
{
	struct imx681_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;

	return RTS_ISP_OK;
}


static int imx681_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx681_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == BINNING_MODE) {
		min_exposure[0] = 4 * status->exp_step;
		max_exposure[0] = (vts - 18) * status->exp_step;
	} 
	else {
		min_exposure[0] = 4 * status->exp_step;
		max_exposure[0] = (vts - 8) * status->exp_step;
	} 
	//debug("###[exp range] max L%f S%f, min L%f S%f\n", max_exposure[0], max_exposure[1], min_exposure[0], min_exposure[1]);
	
	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	if (fgain >= ANALOG_GAIN_MAX_RATIO)
		reg_value = 960;
	else
		reg_value = (uint16_t)((1024*fgain-1024)/fgain);
	
	//debug("### get_sensor_gain_reg fgain=%f, reg_value=%d\n",fgain,reg_value);

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain;

	gain = (float)(1024.0/(1024.0-(float)reg_value));

	//debug("### get_sensor_real_gain gain=%f, reg_value=%d\n",gain,reg_value);

	return gain;
}

uint32_t clip_d_word(uint32_t current, uint32_t minimum, uint32_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int imx681_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct imx681_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int imx681_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx681_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

//static int period=0;
static int imx681_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
#if 1

	int i=0;
	uint16_t exp_lines[2];
	uint16_t gain_reg[2];

	uint32_t frame_length;
	uint16_t shr0,shr1;
	uint16_t rhs1,last_rhs1;

//	uint32_t frame_length;
	struct imx681_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	reg = regs->reg;

	frame_length = exp_gain->vts;
		
	debug("###[exp gain info] vmax=%d, last_vts=%d\n",frame_length,status->last_vts);
	debug("###[exp gain info] exp[0]=%f, gain=%fx%f\n",exp_gain->exposure[0],exp_gain->analog_gain[0], exp_gain->digital_gain[0]);
/*
	if (period%10==0){
		printf("### FRM=%d, exp[0]=%f, gain=%fx%f\n",frame_length,exp_gain->exposure[0],exp_gain->analog_gain[0], exp_gain->digital_gain[0]);
	}
	period++;
*/
	i = 0;

	/* set vts */
	if (abs(status->last_vts - frame_length) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x033D, frame_length >> 16);
		set_sync_i2c(&reg[i++], 0x033E, frame_length >> 8);
		set_sync_i2c(&reg[i++], 0x033F, frame_length & 0xff);
		status->last_vts = frame_length;
	}

	/* set exposure */
	if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
		exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
			
		set_sync_i2c(&reg[i++], 0x0104, 1);	//Group hold
		set_sync_i2c(&reg[i++], 0x022b, exp_lines[0] & 0xff);
		set_sync_i2c(&reg[i++], 0x022a, exp_lines[0] >> 8);
		set_sync_i2c(&reg[i++], 0x0229, exp_lines[0] >> 16);
		set_sync_i2c(&reg[i++], 0x0104, 0);	//Group hold

		status->last_exposure[0] = exp_gain->exposure[0];
	}

	gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] * exp_gain->digital_gain[0]);

	/* set gain */
	set_sync_i2c(&reg[i++], 0x0204, gain_reg[0] >> 8);
	set_sync_i2c(&reg[i++], 0x0205, gain_reg[0] & 0xff);

	
	regs->num = i;
#endif

	return RTS_ISP_OK;
}

static int imx681_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t val;
	struct rts_isp_sync_reg *reg;

	val = mf_info->flip_en != 0;
	val = (mf_info->mirror_en != 0) << 1 | val;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;


if(sensor_mode == BINNING_MODE){

	switch(val)
	{
		case 0:		// Normal
		default:
			set_sync_i2c(&reg[i++], 0x0101, 0x00);
			HAL_WRITE32(0x40300000, 0xc00, 1);
			HAL_WRITE32(0x40300000, 0xc04, 0);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 1:		// Mirror
			set_sync_i2c(&reg[i++], 0x0101, 0x02);
			HAL_WRITE32(0x40300000, 0xc00, 1);
			HAL_WRITE32(0x40300000, 0xc04, 1);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 2:		// VFlip
			set_sync_i2c(&reg[i++], 0x0101, 0x01);
			HAL_WRITE32(0x40300000, 0xc00, 0);
			HAL_WRITE32(0x40300000, 0xc04, 0);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 3:		// Rotate
			set_sync_i2c(&reg[i++], 0x0101, 0x03);
			HAL_WRITE32(0x40300000, 0xc00, 0);
			HAL_WRITE32(0x40300000, 0xc04, 1);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
	}
}
else{
	switch(val)
	{
		case 0:		// Normal
		default:
			set_sync_i2c(&reg[i++], 0x0101, 0x00);
			HAL_WRITE32(0x40300000, 0xc00, 1);
			HAL_WRITE32(0x40300000, 0xc04, 0);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 1:		// Mirror
			set_sync_i2c(&reg[i++], 0x0101, 0x02);
			HAL_WRITE32(0x40300000, 0xc00, 1);
			HAL_WRITE32(0x40300000, 0xc04, 1);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 2:		// VFlip
			set_sync_i2c(&reg[i++], 0x0101, 0x01);
			HAL_WRITE32(0x40300000, 0xc00, 0);
			HAL_WRITE32(0x40300000, 0xc04, 0);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
		case 3:		// Rotate
			set_sync_i2c(&reg[i++], 0x0101, 0x03);
			HAL_WRITE32(0x40300000, 0xc00, 0);
			HAL_WRITE32(0x40300000, 0xc04, 1);
			HAL_WRITE32(0x40300000, 0xc10, 1);
		break;
	}

}
	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int imx681_check(uint32_t isp_id)
{
	int ret;
	int id, smia;
	
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();
/*
	reg.addr = 0x0004;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	smia = reg.data;
	

	reg.addr = 0x0000;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
*/

	reg.addr = 0x0022;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 4;

	reg.addr = 0x0023;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= (reg.data >> 4);

	printf("IMX681_check, Sensor ID = %x\n",id);

	return RTS_ISP_OK;


}

static const struct rts_isp_sensor_ops imx681_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "imx681",
	.get_info = imx681_get_info,
	.get_init_info = imx681_get_init_info,
	.start = imx681_start,
	.get_exposure_range = imx681_get_exposure_range,
	.get_tuned_again = imx681_get_tuned_again,
	.get_tuned_dgain = imx681_get_tuned_dgain,
	.get_exposure_gain_info = imx681_get_exposure_gain_info,
	.set_mirror_flip = imx681_set_mirror_flip,
	.check = imx681_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &imx681_ops;
}

#endif