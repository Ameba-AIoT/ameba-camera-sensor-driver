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

#define ORIENTATION 1			//0=default, 1=rotate180
#define SENSOR_ID_SELECTION	0	/* 0 = 0x6C, 1 = 0x20*/

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ov5693_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct ov5693_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct ov5693_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ov5693_fps_info_asic[] = {
	{30.0f, 2688, 160000000},
};

static struct rts_isp_i2c_reg g_ov5693_i2c_init_regs_asic[] = {
	{0x0100, 0x00},
	{0x0103, 0x01},
	{0x3035, 0x11},
	{0x3036, 0x64},
	{0x303c, 0x11},
	{0x3821, 0x06},
	{0x3820, 0x00},
	{0x370c, 0x0f},
	{0x3612, 0x5b},
	{0x3618, 0x04},
	{0x5000, 0x06},
	{0x5002, 0x40},
	{0x5003, 0x08},
	{0x5a00, 0x08},
	{0x3000, 0xff},
	{0x3001, 0xff},
	{0x3002, 0xff},
	{0x301d, 0xf0},
	{0x3a18, 0x00},
	{0x3a19, 0xf8},
	{0x3c01, 0x80},
	{0x3b07, 0x0c},
	{0x380c, 0x0a},
	{0x380d, 0x8c},
	{0x380e, 0x07},
	{0x380f, 0xb6},
	{0x3814, 0x11},
	{0x3815, 0x11},
	{0x3708, 0x64},
	{0x3709, 0x12},
	{0x3808, 0x0a},
	{0x3809, 0x20},
	{0x380a, 0x07},
	{0x380b, 0x98},
	{0x3800, 0x00},
	{0x3801, 0x0c},
	{0x3802, 0x00},
	{0x3803, 0x04},
	{0x3804, 0x0a},
	{0x3805, 0x33},
	{0x3806, 0x07},
	{0x3807, 0xa3},
	{0x3630, 0x2e},
	{0x3632, 0xe2},
	{0x3633, 0x23},
	{0x3634, 0x44},
	{0x3620, 0x64},
	{0x3621, 0xe0},
	{0x3600, 0x37},
	{0x3704, 0xa0},
	{0x3703, 0x5a},
	{0x3715, 0x78},
	{0x3717, 0x01},
	{0x3731, 0x02},
	{0x370b, 0x60},
	{0x3705, 0x1a},
	{0x3f05, 0x02},
	{0x3f06, 0x10},
	{0x3f01, 0x0a},
	{0x3a08, 0x01},
	{0x3a09, 0x28},
	{0x3a0a, 0x00},
	{0x3a0b, 0xf6},
	{0x3a0d, 0x08},
	{0x3a0e, 0x06},
	{0x3a0f, 0x58},
	{0x3a10, 0x50},
	{0x3a1b, 0x58},
	{0x3a1e, 0x50},
	{0x3a11, 0x60},
	{0x3a1f, 0x28},
	{0x4001, 0x02},
	{0x4004, 0x04},
	{0x4000, 0x09},
	{0x4050, 0x6e},
	{0x4051, 0x8f},
	{0x0100, 0x01},
	{0x3000, 0x00},
	{0x3001, 0x00},
	{0x3002, 0x00},
	{0x3017, 0xe0},
	{0x301c, 0xfc},
	{0x3636, 0x06},
	{0x3016, 0x08},
	{0x3827, 0xec},
	{0x3018, 0x44},
	{0x3035, 0x21},
	{0x3106, 0xf5},
	{0x3034, 0x1a},
	{0x301c, 0xf8},
};

static int ov5693_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2592;
	info->modes.mode[0].size.h = 1944;
	info->modes.mode[0].fps = g_ov5693_fps_info_asic[0].fps;
	info->modes.num = 1;
	
#if (SENSOR_ID_SELECTION == 0)
	info->i2c.i2c_id = 0x36;
#else
	info->i2c.i2c_id = 0x10;
#endif

	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_LOW, 0);
	//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	//set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	//set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 3000);
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 2000);
	//set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 10000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 4000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 4000);
	
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *ov5693_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_ov5693_fps_info_asic); i++)
		if (fps == g_ov5693_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_ov5693_fps_info_asic))
		return NULL;
	return &g_ov5693_fps_info_asic[i];

}

static int ov5693_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ov5693_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("ov5693 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = ov5693_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
	set_init_i2c_regs(info->sensor_regs[0], g_ov5693_i2c_init_regs_asic, 3000);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 2592;
	info->size.h = 1944;
	info->start.x = 0;
	info->start.y = 0;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1984;
	//info->max_vts = 6750;
	info->max_vts = info->min_vts * 15;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int ov5693_start(uint32_t isp_id)
{
	struct ov5693_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int ov5693_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ov5693_status *status;

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

static uint16_t get_sensor_gain_reg(float fAGain, struct ov5693_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	if(gain >= 0xf8)
		gain = 0xf8;
		
	status->num = gain;
	return  gain;
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
static int ov5693_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ov5693_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int ov5693_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int ov5693_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ov5693_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;
		
	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	
	i = 0;
	//set_sync_i2c(&reg[i++], 0xfd, 0x01);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = exposure_rows << 4;
		set_sync_i2c(&reg[i++], 0x3501, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x3502, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x350B, status->num);
	set_sync_i2c(&reg[i++], 0x380E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x380F, vts & 0xff);
	//set_sync_i2c(&reg[i++], 0x01, 0x01);

	regs->num = i;
	regs->num = i;
	return RTS_ISP_OK;
}

static int ov5693_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	/*
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
			set_sync_i2c(&reg[i++], 0xfd, 0x01);
            set_sync_i2c(&reg[i++], 0x3f, 0x00);
            set_sync_i2c(&reg[i++], 0x01, 0x01);
            set_sync_i2c(&reg[i++], 0xfd, 0x02);
            set_sync_i2c(&reg[i++], 0xA1, 0x08);
			break;
		case 2: 	// Mirror
			//set_sync_i2c(&reg[i++], 0xfd, 0x01);
           	//set_sync_i2c(&reg[i++], 0x3f, 0x02);
			break;
		case 1: 		// VFlip
			//set_sync_i2c(&reg[i++], 0xfd, 0x01);
            //set_sync_i2c(&reg[i++], 0x3f, 0x01);
			break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xfd, 0x01);
            set_sync_i2c(&reg[i++], 0x3f, 0x03);
            set_sync_i2c(&reg[i++], 0x01, 0x01);
            set_sync_i2c(&reg[i++], 0xfd, 0x02);
            set_sync_i2c(&reg[i++], 0xA1, 0x07);
			break;
	#else
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0xfd, 0x01);
            set_sync_i2c(&reg[i++], 0x3f, 0x03);
            set_sync_i2c(&reg[i++], 0x01, 0x01);
            set_sync_i2c(&reg[i++], 0xfd, 0x02);
            set_sync_i2c(&reg[i++], 0xA1, 0x07);
			break;
		case 2: 	// Mirror
			//set_sync_i2c(&reg[i++], 0xfd, 0x01);
           	//set_sync_i2c(&reg[i++], 0x3f, 0x01);
			break;
		case 1: 		// VFlip
			//set_sync_i2c(&reg[i++], 0xfd, 0x01);
            //set_sync_i2c(&reg[i++], 0x3f, 0x02);
			break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xfd, 0x01);
            set_sync_i2c(&reg[i++], 0x3f, 0x00);
            set_sync_i2c(&reg[i++], 0x01, 0x01);
            set_sync_i2c(&reg[i++], 0xfd, 0x02);
            set_sync_i2c(&reg[i++], 0xA1, 0x08);
			break;
	#endif
	}
	
	mf_info->regs.num = i;
	*/
	return RTS_ISP_OK;
}

static int ov5693_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x300a;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
	
	reg.addr = 0x300b;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0x5690)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops ov5693_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov5693",

	.get_info = ov5693_get_info,
	.get_init_info = ov5693_get_init_info,
	.start = ov5693_start,
	//.get_exposure_range = ov5693_get_exposure_range,
	.get_tuned_again = ov5693_get_tuned_again,
	.get_tuned_dgain = ov5693_get_tuned_dgain,
	.get_exposure_gain_info = ov5693_get_exposure_gain_info,
	.set_mirror_flip = ov5693_set_mirror_flip,
	.check = ov5693_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ov5693_ops;
}