/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"
/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct mis2008_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};
int isp_driver_is_fpga(void);

static struct mis2008_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_mis2008_fps_info_asic[] = {
	{30.0f, 2200, 74250000},
};


static struct rts_isp_i2c_reg g_mis2008_i2c_init_regs_asic[] = {
	//MIPI_2LAN MCLK=27Mhz,PCLK=74.25Mhz
	//Windows(2200*1125)
	{0x300a,0x01},
	{0x3006,0x02},
	 //RAW10	
	{0x3011,0x2b},
	{0x3c20,0x2b},
	{0x3c21,0x2b},
	{0x3c22,0x2b},
	{0x3c23,0x2b},
	{0x3637,0x1e},
	{0x3c40,0x8d},
	{0x3c01,0x10},
	{0x3c0e,0xf7},
	{0x3c0f,0x34},
	{0x3b01,0x3f},
	{0x3b03,0x3f},
	{0x3902,0x01},
	{0x3904,0x00},
	{0x3903,0x00},
	{0x3906,0x1e},
	{0x3905,0x00},
	{0x3908,0xb0},
	{0x3907,0x10},
	{0x390a,0xff},
	{0x3909,0x1f},
	{0x390c,0x83},	//2021.12.09 Zako: 0xC3
	{0x390b,0x03},
	{0x390e,0x77},
	{0x390d,0x00},
	{0x3910,0xb0},
	{0x390f,0x10},
	{0x3912,0xff},
	{0x3911,0x1f},
	{0x3919,0x00},
	{0x3918,0x00},
	{0x391b,0xfd},
	{0x391a,0x00},
	{0x3983,0x5a},
	{0x3982,0x00},
	{0x3985,0x0f},
	{0x3984,0x00},
	{0x391d,0x00},
	{0x391c,0x00},
	{0x391f,0xa4},
	{0x391e,0x10},
	{0x3921,0xff},
	{0x3920,0x1f},
	{0x3923,0xff},
	{0x3922,0x1f},
	{0x3932,0x00},
	{0x3931,0x00},
	{0x3934,0xd0},
	{0x3933,0x00},
	{0x393f,0x61},
	{0x393e,0x00},
	{0x3941,0x89},
	{0x3940,0x00},
	{0x3943,0x16},
	{0x3942,0x01},
	{0x3945,0x10},
	{0x3944,0x03},
	{0x3925,0x95},
	{0x3924,0x00},
	{0x3927,0x3d},
	{0x3926,0x03},
	{0x3947,0xee},
	{0x3946,0x00},
	{0x3949,0x9e},
	{0x3948,0x0f},
	{0x394b,0x9e},
	{0x394a,0x03},
	{0x394d,0x9c},
	{0x394c,0x00},
	{0x3913,0x01},
	{0x3915,0x0f},
	{0x3914,0x00},
	{0x3917,0xc3},
	{0x3916,0x03},
	{0x392a,0x1e},
	{0x3929,0x00},
	{0x392c,0x0f},
	{0x392b,0x00},
	{0x392e,0x0f},
	{0x392d,0x00},
	{0x3930,0xca},
	{0x392f,0x03},
	{0x397f,0x00},
	{0x397e,0x00},
	{0x3981,0x77},
	{0x3980,0x00},
	{0x395d,0xbe},
	{0x395c,0x10},
	{0x3962,0xdc},
	{0x3961,0x10},
	{0x3977,0x22},
	{0x3976,0x00},
	{0x396d,0x10},
	{0x396c,0x03},
	{0x396f,0x10},
	{0x396e,0x03},
	{0x3971,0x10},
	{0x3970,0x03},
	{0x3973,0x10},
	{0x3972,0x03},
	{0x3978,0x00},
	{0x3979,0x04},
	{0x3012,0x01},
	{0x3600,0x13},
	{0x3601,0x02},
	{0x360e,0x00},
	{0x360f,0x00},
	{0x3610,0x02},
	{0x3707,0x00},
	{0x3708,0x10},
	{0x3709,0x00},
	{0x370a,0x10},
	{0x370b,0x00},
	{0x370c,0x10},
	{0x370d,0x00},
	{0x370e,0x10},
	{0x3800,0x01},
	{0x3a03,0x1b},	//2021.12.09 Zako: 0x3f
	{0x3a02,0x0a},
	{0x3a08,0x34},	//2021.12.09 Zako: 0xb4
	{0x3a1b,0x54},
	{0x3a1e,0x00},
	//{0x3100,0x04},
	//{0x3101,0x64},
	{0x3a1c,0x30},	//2021.12.09 Zako: 0x10
	{0x3a0C,0x04},
	{0x3a0D,0x12},
	{0x3a0E,0x15},
	{0x3a0F,0x18},
	{0x3a10,0x20},
	{0x3a11,0x3c},
				  
	//MCLK=27Mhz,
	{0x3300,0x37},
	{0x3301,0x02},
	{0x3302,0x02},
	{0x3303,0x05},
	{0x330b,0x01},
	{0x330f,0x07},
	//RAW10 	  
	{0x330d,0x01},
	//Windows(2200*1125)
	{0x3201,0x65},
	{0x3200,0x04},
	{0x3203,0x98},
	{0x3202,0x08},
	{0x3205,0x04},
	{0x3204,0x00},
	{0x3207,0x43},
	{0x3206,0x04},
	{0x3209,0x04},
	{0x3208,0x00},
	{0x320b,0x8B},
	{0x320a,0x07},
	{0x3006,0x00}, 
};

static int mis2008_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_mis2008_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x30;//0x90 divide 2
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	//set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 0);
	//set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V5, 1000);
	//set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 5000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&down->items[i++], SNR_IO_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_CORE_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_HCLK, CLK_NONE, 0);
	down->num = i;


	return RTS_ISP_OK;
}

static const struct fps_info *mis2008_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_mis2008_fps_info_asic); i++)
		if (fps == g_mis2008_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_mis2008_fps_info_asic))
		return NULL;
	return &g_mis2008_fps_info_asic[i];
}

static int mis2008_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct mis2008_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("mis2008 get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = mis2008_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
	
	set_init_i2c_regs(info->sensor_regs[0], g_mis2008_i2c_init_regs_asic, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 1;
	info->start.y = 0;
	//info->crop.w = 1920;
	//info->crop.h = 1080;

	//set_init_i2c_regs(info->sensor_regs[1], status->regs1, 0);
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1125;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int mis2008_start(uint32_t isp_id)
{
	struct mis2008_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct mis2008_status *status)
{
	uint16_t reg_value = 0;

	if (fAGain >= 15.75) {
		reg_value = 0x7f;
	} 
	else {
		if (fAGain >= 8)
		{
			reg_value = (uint16_t)((fAGain - 8) * 4.0f) | 0x60;
		}
		else if (fAGain >= 4)
		{
			reg_value = (uint16_t)((fAGain - 4) * 8.0f) | 0x40;
		}
		else if (fAGain >= 2)
		{
			reg_value = (uint16_t)((fAGain - 2) * 16.0f) | 0x20;
		}
		else
		{
			reg_value = (uint16_t)((fAGain -1) * 32.0f);
		}
	}
	status->num = reg_value;
	
	return (reg_value);
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	uint16_t wGain;
	float ftmp;
	wGain = ((wAGain & 0x0060) >> 5);
	ftmp = ((float)(wAGain&0x001f) / 32.0f + 1) * (float)(1 << wGain);
	return ftmp;
}

static int mis2008_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct mis2008_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int mis2008_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int mis2008_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct mis2008_status *status;
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
		exposure_rows = clip_d_word(exposure_rows, 1, vts-1);
		set_sync_i2c(&reg[i++], 0x3200, vts >> 8);
		set_sync_i2c(&reg[i++], 0x3201, vts & 0xff);
		set_sync_i2c(&reg[i++], 0x3100, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x3101, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
		
		if(exposure_rows < 0x1ff)
		{
			set_sync_i2c(&reg[i++], 0x3a02, 0x0b);
			set_sync_i2c(&reg[i++], 0x3a1c, 0x1f);
		}
		else if(exposure_rows > 0x1ff)
		{
			set_sync_i2c(&reg[i++], 0x3a02, 0x0a);
			set_sync_i2c(&reg[i++], 0x3a1c, 0x30);
		}
	}
	
	set_sync_i2c(&reg[i++], 0x3102, status->num);
	regs->num = i;

	//dbg_printf("%s\n\r", __FUNCTION__);

	return RTS_ISP_OK;
}

static int mis2008_set_mirror_flip(uint32_t isp_id,
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

	set_sync_i2c(&reg[i++], 0x3007, val);

	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int mis2008_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x3000;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}

	id = reg.data << 8;

	reg.addr = 0x3001;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	if (id == 0x2008)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops mis2008_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "mis2008",

	.get_info = mis2008_get_info,
	.get_init_info = mis2008_get_init_info,
	.start = mis2008_start,
	.get_tuned_again = mis2008_get_tuned_again,
	.get_tuned_dgain = mis2008_get_tuned_dgain,
	.get_exposure_gain_info = mis2008_get_exposure_gain_info,
	.set_mirror_flip = mis2008_set_mirror_flip,
	.check = mis2008_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &mis2008_ops;
}

