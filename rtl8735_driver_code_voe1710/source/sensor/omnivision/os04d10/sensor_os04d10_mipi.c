/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2023 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#if _OS04D10_SENSOR_

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ANALOG_GAIN_MAX_RATIO (float)15.5f							/* Max sensor gain ratio = 15.5x */

#define HAL_WRITE32(base, addr, value32)  \
        ((*((volatile u32*)(base + addr))) = rtk_cpu_to_le32(value32))


struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct os04d10_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint16_t last_vts;
	uint16_t min_vts;
	//struct rts_isp_i2c_reg regs1[3];
};


static struct os04d10_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

/* Linear frame rate table*/
static const struct fps_info g_os04d10_fps_info[] = {
/*   FPS    HTS     VTS   PCLK    */
	//{30.0, 	(782*4),  1540, 144513600},
	{30.0, 	(782*4),  1473, 138226320},
};

static struct rts_isp_i2c_reg g_os04d10_i2c_init_regs[] = {
	{0xfd, 0x00},
	{0x20, 0x00},
	{0x20, 0x01},
	{0x20, 0x01},
	{0x20, 0x01},
	{0x20, 0x01},
	{0x31, 0x20},
	{0x38, 0x15},
	{0xfd, 0x01},
	{0x03, 0x00},
	{0x04, 0x04},
	{0x06, 0x01},
	{0x24, 0xff},
	{0x42, 0x59},
	{0x45, 0x02},
	{0x48, 0x0c},
	{0x4b, 0x88},
	{0xd4, 0x05},
	{0xd5, 0xd2},
	{0xd7, 0x05},
	{0xd8, 0xd2},
	{0x50, 0x01},
	{0x51, 0x11},
	{0x52, 0x18},
	{0x53, 0x01},
	{0x54, 0x01},
	{0x55, 0x01},
	{0x57, 0x08},
	{0x5c, 0x40},
	{0x7c, 0x1b},
	{0x90, 0x60},
	{0x91, 0x0f},
	{0x92, 0x30},
	{0x93, 0x3a},
	{0x94, 0x0f},
	{0x95, 0x84},
	{0x98, 0x5d},
	{0xa8, 0x50},
	{0xaa, 0x14},
	{0xab, 0x05},
	{0xac, 0x14},
	{0xad, 0x05},
	{0xae, 0x47},
	{0xaf, 0x10},
	{0xc9, 0x28},
	{0xca, 0x5e},
	{0xcb, 0x5e},
	{0xcc, 0x5e},
	{0xcd, 0x5e},
	{0xce, 0x5c},
	{0xcf, 0x5c},
	{0xd0, 0x5c},
	{0xd1, 0x5c},
	{0xd2, 0x7c},
	{0xd3, 0x7c},
	{0xdb, 0x3f},
	
	{0xfd, 0x01},
	{0x46, 0x77},
	{0xdd, 0x00},
	{0xde, 0x3f},
	{0xfd, 0x03},
	{0x2b, 0x0a},
	{0x01, 0x22},
	{0x02, 0x03},
	{0x00, 0x06},
	{0x2a, 0x22},
	{0x29, 0x0b},
	{0x1e, 0x10},
	{0x1f, 0x02},
	{0x1a, 0x24},
	{0x1b, 0x62},
	{0x1c, 0xce},
	{0x1d, 0xd3},
	{0x04, 0x0f},
	{0x36, 0x00},
	{0x37, 0x05},
	{0x38, 0x09},
	{0x39, 0x19},
	{0x3a, 0x38},
	{0x3b, 0x22},
	{0x3c, 0x22},
	{0x3d, 0x22},
	{0x3e, 0x03},
	
	{0xfd, 0x02},
	{0xce, 0x65},
	{0xfd, 0x03},
	{0x03, 0x30},
	{0x05, 0x00},
	{0x12, 0x20},
	{0x13, 0x40},
	{0x21, 0xca},
	{0x27, 0x85},
	{0x2c, 0x55},
	{0x2d, 0x08},
	{0x2e, 0xca},
	{0x3f, 0xe7},
	{0xfd, 0x00},
	{0x8b, 0x01},
	{0x8d, 0x00},
	{0xfd, 0x01},
	{0x01, 0x02},
	{0xfd, 0x05},
	{0xc4, 0x62},
	{0xc5, 0x62},
	{0xc6, 0x62},
	{0xc7, 0x62},
	{0xf0, 0x40},
	{0xf1, 0x40},
	{0xf2, 0x40},
	{0xf3, 0x40},
	{0xf4, 0x00},
	{0xf9, 0x03},
	{0xfa, 0x5d},
	{0xfb, 0x6b},
	{0xb1, 0x01},
	{0xfd, 0x00},
	{0x20, 0x03},
};



static int os04d10_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	info->modes.mode[i].fps = g_os04d10_fps_info[0].fps;
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = 0x3c;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 10000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 20000);
	up->num = i;

	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 0);
	down->num = i;

	return RTS_ISP_OK;
}

/*static const struct fps_info *os04d10_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_os04d10_fps_info); i++)
		if (fps == g_os04d10_fps_info[i].fps)
			break;
	if (i == ARRAY_SIZE(g_os04d10_fps_info))
		return NULL;

	return &g_os04d10_fps_info[i];
}*/

static int os04d10_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct os04d10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	//fps_info = os04d10_get_fps_info(mode->fps);

	//if (!fps_info)
	//	return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0],
			g_os04d10_i2c_init_regs, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x07;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2568;
	info->size.h = 1448;
	info->start.x = 0;
	info->start.y = 1;

	info->hts = 782*4;
	info->min_vts = status->min_vts = 1473;
	info->pclk = 138226320;
	info->max_vts = 65535 - info->min_vts;
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	info->exposure_step = status->exp_step;
	//printf("max_vts  = %d  , min_vts = %d \n\r", info->max_vts,info->min_vts);
	
	return RTS_ISP_OK;
}

static int os04d10_start(uint32_t isp_id)
{
	struct os04d10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;
	status->last_vts = 0;

	return RTS_ISP_OK;
}

static int os04d10_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct os04d10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] =  status->exp_step;
		max_exposure[0] = (vts - 16) * status->exp_step;
	}
	//printf("exp_range_vts = %d  \n\r", vts );


	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	reg_value = (uint16_t)(fgain * 16.0f);
	if (reg_value < 0x10)
		return 0x10;
	else if (reg_value < 0xf8)
		return reg_value;
	else
		return 0xf8;
}

static float get_sensor_real_gain(uint8_t reg_value)
{
	return ((float)reg_value / 16.0f);
}

static uint32_t clip_d_word(uint32_t current, uint32_t minimum, uint32_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int os04d10_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	uint16_t gain_reg;
	struct os04d10_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int os04d10_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int os04d10_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t gain_reg;
	uint16_t dummy;
	uint16_t exp_reg_value;
	struct os04d10_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	reg = regs->reg;
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0]);
	i = 0;

	set_sync_i2c(&reg[i++], 0xfd, 1);

	/* set vblank (VTS) only when changed */
	if (exp_gain->vts != status->last_vts) {
		dummy = exp_gain->vts - status->min_vts + 1;
		set_sync_i2c(&reg[i++], 0x05, (dummy >> 8) & 0xff);
		set_sync_i2c(&reg[i++], 0x06, dummy & 0xff);
		//set_sync_i2c(&reg[i++], 0x05, (1473 >> 8) & 0xff);
		//set_sync_i2c(&reg[i++], 0x06, 1473 & 0xff);
		status->last_vts = exp_gain->vts;
	}

	/* gain */
	set_sync_i2c(&reg[i++], 0x24, gain_reg);

	/* exposure (only write when changed) */
	if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exp_reg_value = clip_d_word(exposure_rows[0], 1, exp_gain->vts - 16);
		set_sync_i2c(&reg[i++], 0x03, (exp_reg_value >> 8) & 0xff);
		set_sync_i2c(&reg[i++], 0x04, exp_reg_value & 0xff);
		status->last_exposure[0] = exp_gain->exposure[0];
		//printf("exp_gain->vts = %d  exposure_rows = %d,dummy = %d ,exp_reg_value = %d,gain_reg = %d \n\r", exp_gain->vts, exposure_rows[0], dummy, exp_reg_value, gain_reg);
	}

	/* trigger once after all registers are written */
	set_sync_i2c(&reg[i++], 0x01, 0x01);
	set_sync_i2c(&reg[i++], 0xfd, 0x0);
	 regs->num = i;
	return RTS_ISP_OK;
}

static int os04d10_set_mirror_flip(uint32_t isp_id,
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
		set_sync_i2c(&reg[i++], 0xfd, 0x1);
		set_sync_i2c(&reg[i++], 0x32, 0x0);
		set_sync_i2c(&reg[i++], 0x01, 0x1);
		set_sync_i2c(&reg[i++], 0xfd, 0x0);
		HAL_WRITE32(0x40300000, 0xc00, 0);
		HAL_WRITE32(0x40300000, 0xc04, 1);
		HAL_WRITE32(0x40300000, 0xc10, 1);
	break;
	case 1: // Mirror
		set_sync_i2c(&reg[i++], 0xfd, 0x1);
		set_sync_i2c(&reg[i++], 0x32, 0x1);
		set_sync_i2c(&reg[i++], 0x01, 0x1);
		set_sync_i2c(&reg[i++], 0xfd, 0x0);
		HAL_WRITE32(0x40300000, 0xc00, 1);
		HAL_WRITE32(0x40300000, 0xc04, 1);
		HAL_WRITE32(0x40300000, 0xc10, 1);
	break;
	case 2: // VFlip
		set_sync_i2c(&reg[i++], 0xfd, 0x1);
		set_sync_i2c(&reg[i++], 0x32, 0x2);
		set_sync_i2c(&reg[i++], 0x01, 0x1);
		set_sync_i2c(&reg[i++], 0xfd, 0x0);
		HAL_WRITE32(0x40300000, 0xc00, 0);
		HAL_WRITE32(0x40300000, 0xc04, 0);
		HAL_WRITE32(0x40300000, 0xc10, 1);
	break;
	case 3: // Rotate
		set_sync_i2c(&reg[i++], 0xfd, 0x1);
		set_sync_i2c(&reg[i++], 0x32, 0x3);
		set_sync_i2c(&reg[i++], 0x01, 0x1);
		set_sync_i2c(&reg[i++], 0xfd, 0x0);
		HAL_WRITE32(0x40300000, 0xc00, 1);
		HAL_WRITE32(0x40300000, 0xc04, 0);
		HAL_WRITE32(0x40300000, 0xc10, 1);
	break;

	}

	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int os04d10_check(uint32_t isp_id)
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
		goto done;

	reg.addr = 0x04;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		goto done;

	id = reg.data << 8;

	reg.addr = 0x05;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		goto done;

	id |= reg.data;

	if (id == 0x4410)
		ret = RTS_ISP_OK;
	else
		ret = -RTS_ISP_EINVAL;

done:
	rts_isp_sensor_access_unprepare();
	return ret;
}

static const struct rts_isp_sensor_ops os04d10_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "os04d10",
	.get_info = os04d10_get_info,
	.get_init_info = os04d10_get_init_info,
	.start = os04d10_start,
	.get_exposure_range = os04d10_get_exposure_range,
	.get_tuned_again = os04d10_get_tuned_again,
	.get_tuned_dgain = os04d10_get_tuned_dgain,
	.get_exposure_gain_info = os04d10_get_exposure_gain_info,
	.set_mirror_flip = os04d10_set_mirror_flip,
	.check = os04d10_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &os04d10_ops;
}

//#endif