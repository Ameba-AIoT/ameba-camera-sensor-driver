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

#if _OV13B10_SENSOR_

#define SENSOR_I2C_0x10		1

// #define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define HAL_WRITE32(base, addr, value32)  \
        ((*((volatile u32*)(base + addr))) = rtk_cpu_to_le32(value32))

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define Short_to_Long 17									/* VHDR mode min interval between long exposure and short exposure frame (long exp + short exp) */


#define BINNING	1			/* 0=Full_Crop, 1=3M_binning */


struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct ov13b10_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure;
	uint32_t last_vts;
	uint16_t min_vts;
	uint8_t gain_reg_num;
	uint8_t last_gain_reg_num;
	uint8_t fusion_mode;
	uint16_t short_exp_mode_exit_thd;
};



static struct ov13b10_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_ov13b10_fps_info_linear[] = {
/*   FPS    HTS       VTS     PCLK      */
#if	(BINNING == 0)
	{10, (6007), (3196), (192000000)},
#else
	{30, (2400), (1598), (115056000)},
#endif
};


static struct rts_isp_i2c_reg g_ov13b10_i2c_init_binning_regs[] = {
		
	
		{0x0103,0x01},
		{0x0303,0x01},
		{0x0305,0x23},
		{0x0321,0x00},
		{0x0323,0x04},
		{0x0324,0x01},
		{0x0325,0x50},
		{0x0326,0x81},
		{0x0327,0x04},
		{0x3011,0x7c},
		{0x3012,0x07},
		{0x3013,0x32},
		{0x3016,0x32},  //2lane
		{0x3106,0x29},  //2lane
		{0x3107,0x23},
		{0x3501,0x06},
		{0x3502,0x10},
		{0x3504,0x08},
		{0x3508,0x07},
		{0x3509,0xc0},
		{0x3600,0x16},
		{0x3601,0x54},
		{0x3612,0x4e},
		{0x3620,0x00},
		{0x3621,0x68},
		{0x3622,0x66},
		{0x3623,0x03},
		{0x3662,0x88},
		{0x3666,0xbb},
		{0x3667,0x44},
		{0x366e,0xff},
		{0x366f,0xf3},
		{0x3675,0x44},
		{0x3676,0x00},
		{0x367f,0xe9},
		{0x3681,0x32},
		{0x3682,0x1f},
		{0x3683,0x0b},
		{0x3684,0x0b},
		{0x3704,0x0f},
		{0x3706,0x40},
		{0x3708,0x3b},
		{0x3709,0x72},
		{0x370b,0xa2},
		{0x3714,0x28},
		{0x371a,0x3e},
		{0x3725,0x42},
		{0x3739,0x10},
		{0x3767,0x00},
		{0x377a,0x0d},
		{0x3789,0x18},
		{0x3790,0x40},
		{0x3791,0xa2},
		{0x37c2,0x14},
		{0x37c3,0xf1},
		{0x37d9,0x06},
		{0x37da,0x02},
		{0x37dc,0x02},
		{0x37e1,0x04},
		{0x37e2,0x0c},
		{0x37e4,0x00},
		{0x3800,0x00},
		{0x3801,0x00},
		{0x3802,0x00},
		{0x3803,0x08},
		{0x3804,0x10},
		{0x3805,0x8f},
		{0x3806,0x0c},
		{0x3807,0x47},
		{0x3808,0x08},
		{0x3809,0x38},
		{0x380a,0x06},
		{0x380b,0x18},
		{0x380c,0x09},  //hts = 2400
		{0x380d,0x30},  //hts = 2400
		{0x380e,0x06},
		{0x380f,0x46},
		{0x3811,0x07},
		{0x3813,0x05},
		{0x3814,0x03},
		{0x3815,0x01},
		{0x3816,0x03},
		{0x3817,0x01},
		{0x381f,0x08},
		{0x3820,0x8b},
		{0x3821,0x00},
		{0x3822,0x14},
		{0x3823,0x18},
		{0x3827,0x01},
		{0x382e,0xe6},
		{0x3c80,0x00},
		{0x3c87,0x01},
		{0x3c8c,0x18},
		{0x3c8d,0x1c},
		{0x3ca0,0x00},
		{0x3ca1,0x00},
		{0x3ca2,0x00},
		{0x3ca3,0x00},
		{0x3ca4,0x50},
		{0x3ca5,0x11},
		{0x3ca6,0x01},
		{0x3ca7,0x00},
		{0x3ca8,0x00},
		{0x4008,0x00},
		{0x4009,0x05},
		{0x400a,0x01},
		{0x400b,0x19},
		{0x4011,0x21},
		{0x4017,0x08},
		{0x4019,0x04},
		{0x401a,0x58},
		{0x4032,0x1e},
		{0x4050,0x00},
		{0x4051,0x05},
		{0x405e,0x00},
		{0x4066,0x02},
		{0x4501,0x08},
		{0x4502,0x10},
		{0x4505,0x04},
		{0x4800,0x64},
		{0x481b,0x3e},
		{0x481f,0x30},
		{0x4825,0x34},
		{0x4837,0x1d},
		{0x484b,0x01},
		{0x4883,0x02},
		{0x5000,0xfd},
		{0x5001,0x0d},
		{0x5045,0x20},
		{0x5046,0x20},
		{0x5047,0xa4},
		{0x5048,0x20},
		{0x5049,0xa4},
		
		{0x0100,0x01}, //Stream on
};

static struct rts_isp_i2c_reg g_ov13b10_i2c_init_full_regs[] = {
	
		{0x0103,0x01},
		{0x0303,0x01},
		{0x0305,0x3c}, //0x46 for 1120Mbps, 0x3c for 960Mbps
		{0x0321,0x00},
		{0x0323,0x04},
		{0x0324,0x01},
		{0x0325,0x50},
		{0x0326,0x81},
		{0x0327,0x04},
		{0x3011,0x7c},
		{0x3012,0x07},
		{0x3013,0x32},
		{0x3016,0x32}, //2lane
		{0x3106,0x29}, //2lane
		{0x3107,0x23},
		{0x3501,0x0c},		
		{0x3502,0x10},
		{0x3504,0x08},
		{0x3508,0x07},
		{0x3509,0xc0},
		{0x3600,0x16},
		{0x3601,0x54},
		{0x3612,0x4e},
		{0x3620,0x00},
		{0x3621,0x68},
		{0x3622,0x66},
		{0x3623,0x03},
		{0x3662,0x92},
		{0x3666,0xbb},
		{0x3667,0x44},
		{0x366e,0xff},
		{0x366f,0xf3},
		{0x3675,0x44},
		{0x3676,0x00},
		{0x367f,0xe9},
		{0x3681,0x32},
		{0x3682,0x1f},
		{0x3683,0x0b},
		{0x3684,0x0b},
		{0x3704,0x0f},
		{0x3706,0x40},
		{0x3708,0x3b},
		{0x3709,0x72},
		{0x370b,0xa2},
		{0x3714,0x24},
		{0x371a,0x3e},
		{0x3725,0x42},
		{0x3739,0x12},
		{0x3767,0x00},
		{0x377a,0x0d},
		{0x3789,0x18},
		{0x3790,0x40},
		{0x3791,0xa2},
		{0x37c2,0x04},
		{0x37c3,0xf1},
		{0x37d9,0x0c},
		{0x37da,0x02},
		{0x37dc,0x02},
		{0x37e1,0x04},
		{0x37e2,0x0a},
		{0x3800,0x00},
		{0x3801,0x00},
		{0x3802,0x00},
		{0x3803,0x08},
		{0x3804,0x10},
		{0x3805,0x8f},
		{0x3806,0x0c},
		{0x3807,0x47},
		{0x3808,0x0f},    // x=4208  0x10
		{0x3809,0xc0},    // x=4208  0x70
		{0x380a,0x0b},
		{0x380b,0xd0},
		{0x380c,0x0d},   // hts=7056(5fps) 0x1b   3504(10fps) 0x0d
		{0x380d,0xb0},   // hts=7056(5fps) 0x90   3504(10fps) 0xb0
		{0x380e,0x0c},
		{0x380f,0x7c},
		{0x3811,0x0f},
		{0x3813,0x09},
		{0x3814,0x01},
		{0x3815,0x01},
		{0x3816,0x01},
		{0x3817,0x01},
		{0x381f,0x08},
		{0x3820,0x88},
		{0x3821,0x00},
		{0x3822,0x14}, 
		{0x3823,0x18}, 
		{0x3827,0x01}, 
		{0x382e,0xe6},
		{0x3c80,0x00},
		{0x3c87,0x01},
		{0x3c8c,0x19},
		{0x3c8d,0x1c},
		{0x3ca0,0x00},
		{0x3ca1,0x00},
		{0x3ca2,0x00},
		{0x3ca3,0x00},
		{0x3ca4,0x50},
		{0x3ca5,0x11},
		{0x3ca6,0x01},
		{0x3ca7,0x00},
		{0x3ca8,0x00},
		{0x4008,0x02},
		{0x4009,0x0f},
		{0x400a,0x01},
		{0x400b,0x19},
		{0x4011,0x21},
		{0x4017,0x08},
		{0x4019,0x04},
		{0x401a,0x58},
		{0x4032,0x1e},
		{0x4050,0x02},
		{0x4051,0x09},
		{0x405e,0x00},
		{0x4066,0x02},
		{0x4501,0x00},
		{0x4502,0x10},
		{0x4505,0x00},
		{0x4800,0x64},
		{0x481b,0x3e},
		{0x481f,0x30},
		{0x4825,0x34},
		{0x4837,0x11}, //0x3c for 1120Mbps 0x11 for 960Mbps
		{0x484b,0x01},
		{0x4883,0x02},
		{0x5000,0xff},
		{0x5001,0x0f},
		{0x5045,0x20},
		{0x5046,0x20},
		{0x5047,0xa4},
		{0x5048,0x20},
		{0x5049,0xa4},
		
		{0x0100,0x01}, //Stream on

};



static int ov13b10_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if(BINNING == 0)	
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2104;
	info->modes.mode[i].size.h = 1560;
	info->modes.mode[i].fps = 10;
	i++;

	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2104;
	info->modes.mode[i].size.h = 1560;
	info->modes.mode[i].fps = 10;			//@MLCK=24MHz
#else
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2096;     //2104
	info->modes.mode[i].size.h = 1560;     //1560
	info->modes.mode[i].fps = 30.0f;
	i++;

	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2096;     //2104
	info->modes.mode[i].size.h = 1560;     //1560
	info->modes.mode[i].fps = 30.0f;			//@MLCK=24MHz
#endif	
	i++;
	info->modes.num = i;

#if SENSOR_I2C_0x10
	info->i2c.i2c_id = 0x10;
#else
	info->i2c.i2c_id = 0x36;										//Write=0x52/Read=0x53
#endif
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);	
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);

	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 50);
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	down->num = i;

	return RTS_ISP_OK;
}

static int ov13b10_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ov13b10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	debug("ov13b10 get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	//fps_info = ov13b10_get_fps_info(mode->fps, &mode->hdr);

	//if (!fps_info)
	//	return -RTS_ISP_EINVAL;

#if(BINNING == 0)	
	set_init_i2c_regs(info->sensor_regs[0], g_ov13b10_i2c_init_full_regs, 5000);
#else
	set_init_i2c_regs(info->sensor_regs[0], g_ov13b10_i2c_init_binning_regs, 5000);
#endif
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x3;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

#if(BINNING == 0)	
	info->size.w = 4032;
	info->size.h = 3024;
	info->start.x = 964;
	info->start.y = 732;	
	info->hts = 6007; //7056;
	info->min_vts = 3196;
	info->pclk = 192000000;
#else	
	info->size.w = 2096;
	info->size.h = 1560;
	info->start.x = 0;
	info->start.y = 0;	
	info->hts = 2400;
	info->min_vts = 1606;
	info->pclk = 115056000;
#endif
	info->max_vts = 65535 - info->min_vts;			

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	info->exposure_step = status->exp_step;
	

	return RTS_ISP_OK;
}

static int ov13b10_start(uint32_t isp_id)
{
	struct ov13b10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;


	return RTS_ISP_OK;
}

uint32_t clip_d_word(uint32_t current, uint32_t minimum, uint32_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

/*static const struct fps_info *ov13b10_get_fps_info(uint16_t fps, const struct rts_isp_sensor_mode *mode)
{
	int i;

	if (mode->hdr == HDR_MODE) {
		for (i = 0; i < ARRAY_SIZE(g_ov13b10_fps_info_hdr); i++)
			if (fps <= g_ov13b10_fps_info_hdr[i].fps)
				break;
		if (i == ARRAY_SIZE(g_ov13b10_fps_info_hdr))
			return NULL;

		return &g_ov13b10_fps_info_hdr[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_ov13b10_fps_info_linear); i++)
			if (fps <= g_ov13b10_fps_info_linear[i].fps)
				break;
		if (i == ARRAY_SIZE(g_ov13b10_fps_info_linear))
			return NULL;

		return &g_ov13b10_fps_info_linear[i];
	}
}*/






static int ov13b10_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ov13b10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];


	min_exposure[0] = status->exp_step * 4;
	max_exposure[0] = (vts - 8) * status->exp_step;

	debug("max_exposure = %f, min_exposure = %f\n", max_exposure[0], min_exposure[0]);
	

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;	

	reg_value = (uint16_t)(fgain * 128.0);	
	reg_value = clip_d_word(reg_value, 128, 128 * 15.5);	

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return (float)reg_value / 128;
}

static int ov13b10_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;	

	if (isp_id >= SUPPORTED_ISP_NUM || !again)		
		return -RTS_ISP_EINVAL;	

	gain_reg = get_sensor_gain_reg(again[0]);	
	again[0] = get_sensor_real_gain(gain_reg);	


	return RTS_ISP_OK;
}

static int ov13b10_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct ov13b10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int ov13b10_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t total_line;
	struct ov13b10_status *status;
	struct rts_isp_sync_reg *reg;

	uint32_t exposure_rows;
	
	uint16_t gain;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	
	gain = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);

	total_line = exp_gain->vts;

	exposure_rows =  exp_gain->exposure[0] / status->exp_step + 0.5f;
	exposure_rows =
		clip_d_word(exposure_rows, 4, ( total_line - 8));
	

	reg = regs->reg;
	i = 0;

	// set vts
	set_sync_i2c(&reg[i++], 0x380e, exp_gain->vts >> 8);
	set_sync_i2c(&reg[i++], 0x380f, exp_gain->vts & 0xff);	
	
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {

	
		// set exposure
		set_sync_i2c(&reg[i++], 0x3502, (exposure_rows ) & 0xff);
		set_sync_i2c(&reg[i++], 0x3501, (exposure_rows ) >> 8);
		set_sync_i2c(&reg[i++], 0x3500, (exposure_rows ) >> 16);
		
		status->last_exposure = exp_gain->exposure[0];
	} 		
	/* gain */
	set_sync_i2c(&reg[i++], 0x3508, gain >> 7);
	set_sync_i2c(&reg[i++], 0x3509, (gain<<1) & 0xff);
	regs->num = i;
	return RTS_ISP_OK;
}

static int ov13b10_get_short_exp_mode(uint32_t isp_id)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct ov13b10_status *status = &g_status[isp_id];
	return status->fusion_mode;
}

static int ov13b10_set_short_exp_exit_thd(uint32_t isp_id, uint16_t exit_thd)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	struct ov13b10_status *status = &g_status[isp_id];

	if (status->fusion_mode && exit_thd <= 512) {
		status->fusion_mode = VHDR_EXP_MODE_MULTIPLE;
	}
	status->short_exp_mode_exit_thd = exit_thd;
	return 0;
}

static int ov13b10_set_mirror_flip(uint32_t isp_id,
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
		#if (BINNING == 0)
			case 0: //normal
			default:
	          set_sync_i2c(&reg[i++], 0x3811, 0x0f);
              set_sync_i2c(&reg[i++], 0x3813, 0x09);			
              set_sync_i2c(&reg[i++], 0x3820, 0x88);	
			break;
			case 1: 	// Mirror
	          set_sync_i2c(&reg[i++], 0x3811, 0x10);
              set_sync_i2c(&reg[i++], 0x3813, 0x09);			
              set_sync_i2c(&reg[i++], 0x3820, 0x80);
			break;
			case 2: 		// VFlip
	          set_sync_i2c(&reg[i++], 0x3811, 0x0f);
              set_sync_i2c(&reg[i++], 0x3813, 0x08);			
              set_sync_i2c(&reg[i++], 0x3820, 0x98);	
			break;
			case 3: 	// Rotate
	          set_sync_i2c(&reg[i++], 0x3811, 0x10);
              set_sync_i2c(&reg[i++], 0x3813, 0x08);			
              set_sync_i2c(&reg[i++], 0x3820, 0x90);		
			break;
		#else
			case 0: //normal
			default:
           	 set_sync_i2c(&reg[i++], 0x3811, 0x07);
           	 set_sync_i2c(&reg[i++], 0x3813, 0x05);			
           	 set_sync_i2c(&reg[i++], 0x3820, 0x8b);
			break;
			case 1: 	// Mirror
          	  set_sync_i2c(&reg[i++], 0x3811, 0x08);
          	  set_sync_i2c(&reg[i++], 0x3813, 0x05);			
          	  set_sync_i2c(&reg[i++], 0x3820, 0x83);
			break;
			case 2: 		// VFlip
          	  set_sync_i2c(&reg[i++], 0x3811, 0x07);
          	  set_sync_i2c(&reg[i++], 0x3813, 0x04);	
          	  set_sync_i2c(&reg[i++], 0x3820, 0x9b);
			break;
			case 3: 	// Rotate
           	 set_sync_i2c(&reg[i++], 0x3811, 0x08);
           	 set_sync_i2c(&reg[i++], 0x3813, 0x04);	       
   		   	 set_sync_i2c(&reg[i++], 0x3820, 0x93);
			break;
		#endif	
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ov13b10_check(uint32_t isp_id)
{
	int ret;
	uint32_t id;
	struct rts_isp_i2c_reg reg;


    rts_isp_sensor_access_prepare();


	//reg.addr = 0x300A;
	//ret = rts_isp_read_sensor_reg(isp_id, &reg);
	//if (ret)
	//	return ret;
	//id = reg.data << 16;
	
	reg.addr = 0x300B;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;	

	reg.addr = 0x300C;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
	rts_isp_sensor_access_unprepare();
	
	
	if (ret)
		return ret;

	id |= reg.data;

	if ((id >> 8) == 0x0D) //id = 0x0D43 or 0x0D42
		return RTS_ISP_OK;

	else
	
		return -RTS_ISP_EINVAL;
	
}

static const struct rts_isp_sensor_ops ov13b10_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov13b10",
	.get_info = ov13b10_get_info,
	.get_init_info = ov13b10_get_init_info,
	.start = ov13b10_start,
	.get_exposure_range = ov13b10_get_exposure_range,
	.get_tuned_again = ov13b10_get_tuned_again,
	.get_tuned_dgain = ov13b10_get_tuned_dgain,
	.get_exposure_gain_info = ov13b10_get_exposure_gain_info,
	.set_mirror_flip = ov13b10_set_mirror_flip,
	.set_short_exp_exit_thd = ov13b10_set_short_exp_exit_thd,
	.get_short_exp_mode = ov13b10_get_short_exp_mode,
	.check = ov13b10_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ov13b10_ops;
}

#endif