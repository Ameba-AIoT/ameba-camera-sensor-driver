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
#define SENSOR_ID_SELECTION	0	/* 0 = 0x78, 1 = 0x7A*/

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ov2735_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct ov2735_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct ov2735_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ov2735_fps_info_asic[] = {
	{30.0f, 2106, 84000000},
};

static struct rts_isp_i2c_reg g_ov2735_i2c_init_regs_asic_1[] = {
	{0xfd,0x00},
	{0x20,0x00},
};

static struct rts_isp_i2c_reg g_ov2735_i2c_init_regs_asic_2[] = {
	{0xfd,0x00},
	{0x2f,0x10},
	{0x34,0x00},
	{0x30,0x15},
	{0x33,0x01},
	{0x35,0x20},
	{0xfd,0x01},
	{0x0d,0x10},
	{0x30,0x00},
	{0x03,0x01},
	{0x04,0x8f},
	{0x01,0x01},
	{0x09,0x00},
	{0x0a,0x20},
	{0x06,0x0a},
	{0x24,0x10},
	{0x01,0x01},
	{0xfb,0x73},
	{0x01,0x01},
	{0xfd,0x01},
	{0x1a,0x6b},
	{0x1c,0xea},
	{0x16,0x0c},
	{0x21,0x00},
	{0x11,0x63},
	{0x19,0xc3},
	{0x26,0x5a},
	{0x29,0x01},
	{0x33,0x6f},
	{0x2a,0xd2},
	{0x2c,0x40},
	{0xd0,0x02},
	{0xd1,0x01},
	{0xd2,0x20},
	{0xd3,0x04},
	{0xd4,0x2a},
	{0x50,0x00},
	{0x51,0x2c},
	{0x52,0x29},
	{0x53,0x00},
	{0x55,0x44},
	{0x58,0x29},
	{0x5a,0x00},
	{0x5b,0x00},
	{0x5d,0x00},
	{0x64,0x2f},
	{0x66,0x62},
	{0x68,0x5b},
	{0x75,0x46},
	{0x76,0x36},
	{0x77,0x4f},
	{0x78,0xef},
	{0x72,0xcf},
	{0x73,0x36},
	{0x7d,0x0d},
	{0x7e,0x0d},
	{0x8a,0x77},
	{0x8b,0x77},
	{0xfd,0x01},
	{0xb1,0x83},//DPHY enable 8b
	{0xb3,0x0b},//0b;09;1d
	{0xb4,0x14},//MIPI PLL enable;14;35;36
	{0x9d,0x40},//mipi hs dc level 40/03/55
	{0xa1,0x05},//speed/03
	{0x94,0x44},//dphy time
	{0x95,0x33},//dphy time
	{0x96,0x1f},//dphy time
	{0x98,0x45},//dphy time
	{0x9c,0x10},//dphy time
	{0xb5,0x70},//30
	{0xa0,0x01},//mipi enable
	{0x25,0xe0},
	{0x20,0x7b},
	{0x8f,0x88},
	{0x91,0x40},
	{0xfd,0x01},
	{0xfd,0x02},
	{0xa1,0x04},
	{0xa3,0x40},
	{0xa5,0x02},
	{0xa7,0xc4},
	{0xfd,0x01},
	{0x86,0x77},
	{0x89,0x77},
	{0x87,0x74},
	{0x88,0x74},
	{0xfc,0xe0},
	{0xfe,0xe0},
	{0xf0,0x40},
	{0xf1,0x40},
	{0xf2,0x40},
	{0xf3,0x40},
	{0xfd,0x02},	
	{0xa0,0x00},	//Image vertical start MSB3bits
	{0xa1,0x08},	//Image vertical start LSB8bits
	{0xa2,0x04},	//image vertical size  MSB8bits
	{0xa3,0x50},	//image vertical size  LSB8bits//438
	{0xa4,0x00},
	{0xa5,0x06},	//H start 8Lsb
	{0xa6,0x03},
	{0xa7,0xcc},	//Half H size Lsb8bits//3c0
	{0xfd,0x01},
	{0x8e,0x07},
	{0x8f,0x88},	//MIPI column number
	{0x90,0x04},	//MIPI row number
	{0x91,0x40},
	{0xfd,0x01},
	{0x06,0xe0},	//insert dummy line , the frame rate is 30.01.
	{0x01,0x01},
};

static int ov2735_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_ov2735_fps_info_asic[0].fps;
	info->modes.num = 1;
	
#if (SENSOR_ID_SELECTION == 0)
	info->i2c.i2c_id = 0x3C;
#else
	info->i2c.i2c_id = 0x3D;
#endif

	info->i2c.addr_len = 1;
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

static const struct fps_info *ov2735_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_ov2735_fps_info_asic); i++)
		if (fps == g_ov2735_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_ov2735_fps_info_asic))
		return NULL;
	return &g_ov2735_fps_info_asic[i];

}

static int ov2735_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ov2735_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("ov2735 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = ov2735_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
#if 0
	set_init_i2c_regs(info->sensor_regs[0], g_ov2735_i2c_init_regs_asic_1, 5000);
	set_init_i2c_regs(info->sensor_regs[1], g_ov2735_i2c_init_regs_asic_2, 3000);
#else
	set_init_i2c_regs(info->sensor_regs[0], g_ov2735_i2c_init_regs_asic_2, 3000);
#endif
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1936;
	info->size.h = 1096;
	info->start.x = 0;
	info->start.y = 1;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1329;
	//info->max_vts = 6750;
	info->max_vts = info->min_vts * 15;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int ov2735_start(uint32_t isp_id)
{
	struct ov2735_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int ov2735_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ov2735_status *status;

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

static uint16_t get_sensor_gain_reg(float fAGain, struct ov2735_status *status)
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
static int ov2735_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ov2735_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int ov2735_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int ov2735_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ov2735_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;
		
	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	
	i = 0;
	set_sync_i2c(&reg[i++], 0xfd, 0x01);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x03, (exposure_rows & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x04, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x24, status->num);
	set_sync_i2c(&reg[i++], 0x0E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0F, vts & 0xff);
	set_sync_i2c(&reg[i++], 0x01, 0x01);
	regs->num = i;
	return RTS_ISP_OK;
}

static int ov2735_set_mirror_flip(uint32_t isp_id,
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
	return RTS_ISP_OK;
}

static int ov2735_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0xFD;
	reg.data = 0x00;
	ret = rts_isp_write_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}

	reg.addr = 0x02;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
	
	reg.addr = 0x03;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0x2735)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops ov2735_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov2735",

	.get_info = ov2735_get_info,
	.get_init_info = ov2735_get_init_info,
	.start = ov2735_start,
	//.get_exposure_range = ov2735_get_exposure_range,
	.get_tuned_again = ov2735_get_tuned_again,
	.get_tuned_dgain = ov2735_get_tuned_dgain,
	.get_exposure_gain_info = ov2735_get_exposure_gain_info,
	.set_mirror_flip = ov2735_set_mirror_flip,
	.check = ov2735_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ov2735_ops;
}