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

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct k05_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct k05_gain_config {
	uint8_t reg_b4;
	uint8_t reg_b3;
	uint8_t reg_b8;
	uint8_t reg_b9;
	uint16_t value;
};

static struct k05_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_k05_fps_info_asic[] = {
	//{30.0f, 2200, 74250000},

{30.0f, 2880, 172800000},

};

//mclk=27mhz,pclk=74.25mhz
//pixel_line_total=2200,line_frame_total=1125
//row_time=29.629us,frame_rate=30fps
//Mipi_clk=594 Mbps

static struct rts_isp_i2c_reg g_k05_i2c_init_regs_asic[] = {
	/****system****/
	{0x12, 0x40},
	{0x0e, 0x11},
	{0x0f, 0x14},
	{0x10, 0x20},
	{0x11, 0x80},
	{0x0d, 0xa0},
	{0x48, 0x0f},
	{0x5f, 0x02},
	{0x60, 0x2b},
	{0x58, 0x30},
	{0x57, 0xc0},
	{0x64, 0xe0},
	{0x20, 0xd0},
	{0x21, 0x02},
	{0x22, 0xd0}, //[6]aec_delay_mode
	{0x23, 0x07}, //[5:4]dwen_sramen
	{0x24, 0x88}, //ramp_en
	{0x25, 0x98},
	{0x26, 0x72},
	{0x27, 0x40}, //05
	{0x28, 0x15}, //60//[11:0]hb
	{0x29, 0x02},
	{0x2a, 0x34},
	{0x2b, 0x12},
	{0x2c, 0x00}, //cisctl row start
	{0x2d, 0x00},
	{0x2e, 0xec}, //cisctl col start
	{0x2f, 0x44}, //vsync_ahead_mode
	{0x41, 0x8c},
	{0x42, 0x12}, //ad_pipe_num
	{0x76, 0xa8}, //eqc1fc_eqc2fc_sw
	{0x77, 0x0c}, //16//eqc2_c2clpen_sw
	{0x07, 0x20}, //eq_post_width
	{0x1d, 0x00}, //c2clpen --eqc2
	{0x1e, 0x04}, //[5]txh_en ->avdd28
	{0x6c, 0x40}, //[3:2]eqc2sel=0
	{0x68, 0x00}, //[3:0]rsgl
	{0x70, 0x68}, //0e//post_tx_width
	{0x71, 0x4c},
	{0x72, 0x29}, //rst_tx_width
	{0x73, 0x25}, //12//ramp_t1_width
	{0x74, 0x12}, //read_tx_width_pp
	{0x78, 0x19}, //18//stspd_width_r1
	{0x89, 0x92}, //40//5//stspd_width_r
	{0x6e, 0x0c}, //dacin  offset x31
	{0x0c, 0x20}, //dacin offset
	{0x31, 0x20}, //[1:0] co1comp
	{0x32, 0x4f}, //12 ramp_t1_ref
	{0x33, 0x70},
	{0x34, 0x5f},
	{0x35, 0x5f},
	{0x3a, 0xa8},
	{0x3b, 0x7c},
	{0x3c, 0xff}, //70//78//[4:2]c1isel
	{0x3f, 0x92},
	{0x40, 0xff}, //[5:3]c2clamp
	{0x56, 0x32}, //{0x39[7]=0,0xd3[3]=1 rsgh=vref
	{0x59, 0x7a}, //ramps offset
	{0x6f, 0x10},//80->dynamic dpc ===c0
	{0x85, 0x44},
	{0x8a, 0x04},
	{0x8e, 0x00},
	{0x8f, 0x90},
	{0x9c, 0xa1}, //[7:0]WB_offset
	{0x5c, 0x08},
	{0x5d, 0x94},
	{0x63, 0x0f},
	{0x66, 0x04}, //[10:0]out_height//40
	{0x67, 0x42},
	{0x6a, 0x49}, //[11:0]out_width
	{0x69, 0x7f},
	{0x7a, 0xc7}, //[3]dpc blending mode
	{0xa7, 0x1b}, //[7:0]BFF_sram_mode
	{0xa9, 0x04}, //[0]DD_en
	{0x4a, 0xf5},
	{0x7e, 0xcd},
	{0x50, 0x03},
	{0x49, 0x10},
	{0x47, 0x02},
	{0x7b, 0x4a},
	{0x7c, 0x0a},
	{0x7f, 0x56},
	{0x62, 0x20},
	{0x90, 0x00},
	{0x8c, 0xff},
	{0x8d, 0xc7},
	{0x8b, 0x01},
	{0xa0, 0xa2},
	{0x65, 0x08},
	{0x80, 0x00},
	{0x19, 0x20},
	{0x12, 0x00},
};


static int k05_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2592;
	info->modes.mode[0].size.h = 1944;
	info->modes.mode[0].fps = g_k05_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x40;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;


	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);

	//set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 1000);
	//set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V2, 1000);
	//set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, 0, 5000);
	set_power_item(&down->items[i++], SNR_CORE_POWER, 0, 5000);
	set_power_item(&down->items[i++], SNR_IO_POWER, 0, 0);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *k05_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_k05_fps_info_asic); i++)
		if (fps == g_k05_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_k05_fps_info_asic))
		return NULL;
	return &g_k05_fps_info_asic[i];
}

static int k05_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct k05_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("k05 get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = k05_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;
#ifdef _SENSOR_LOG_
	printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
#endif

	set_init_i2c_regs(info->sensor_regs[0], g_k05_i2c_init_regs_asic, 0);
	set_init_i2c_regs(info->sensor_regs[1], status->regs1, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
	info->interface.mipi.hs_term = 0x1;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2592;
	info->size.h = 1944;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 2000;
	info->max_vts = 65536;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	//info->exposure_step = status->exp_step;

	return RTS_ISP_OK;
}

static int k05_start(uint32_t isp_id)
{
	struct k05_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct k05_status *status)
{
	return fgain * 64;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 64.0f;
}

static int k05_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct k05_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int k05_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int k05_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct k05_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	i = 0;

	regs->num = i;

	return RTS_ISP_OK;
}

static int k05_check(uint32_t isp_id)
{
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops k05_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "k05",

	.get_info = k05_get_info,
	.get_init_info = k05_get_init_info,
	.start = k05_start,
	.get_tuned_again = k05_get_tuned_again,
	.get_tuned_dgain = k05_get_tuned_dgain,
	.get_exposure_gain_info = k05_get_exposure_gain_info,
	.check = k05_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &k05_ops;
}
