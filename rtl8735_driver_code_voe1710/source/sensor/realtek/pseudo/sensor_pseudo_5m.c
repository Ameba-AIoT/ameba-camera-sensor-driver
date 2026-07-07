/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2023 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>

#if _PSEUDO_5M_SENSOR_

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define RAW_10BIT
#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

//5M @3fps
#define SENSOR_WIDTH 2592
#define SENSOR_HEIGHT 1944
#define SENSOR_HTS 4000
#define SENSOR_VTS 2000
#define PCLK 24000000

#define FPS (float)PCLK / (float)SENSOR_HTS / (float)SENSOR_VTS

#ifdef RAW_10BIT
#define BIT_DEPTH SNR_10BIT
#define TYPE RAW_SENSOR
#endif

struct pseudo_mipi_status {
	enum rts_isp_sensor_hdr_mode hdr;
};

static struct pseudo_mipi_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static int pseudo_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;
	info->modes.mode[0].size.w = SENSOR_WIDTH;
	info->modes.mode[0].size.h = SENSOR_HEIGHT;
	info->modes.mode[0].fps = FPS;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x01;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	set_power_item(&up->items[0], SNR_HCLK, CLK_24M, 0);
	set_power_item(&up->items[1], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[2], SNR_PWDN_GPIO, GPIO_LOW, 0);
	up->num = 3;
	set_power_item(&down->items[0], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[1], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[2], SNR_ANALOG_POWER, 0, 0);
	set_power_item(&down->items[3], SNR_HCLK, CLK_NONE, 0);
	down->num = 4;

	return RTS_ISP_OK;
}

static int pseudo_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct pseudo_mipi_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	debug("pseudo get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = TYPE;
	info->interface.bit_depth = BIT_DEPTH;
	info->mipi_behavor = NONE_HDR;

	info->size.w = SENSOR_WIDTH;
	info->size.h = SENSOR_HEIGHT;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = SENSOR_HTS;
	info->pclk = PCLK;
	info->min_vts = SENSOR_VTS;
	info->max_vts = 65535;

	return RTS_ISP_OK;
}

static int pseudo_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int pseudo_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int pseudo_get_exposure_gain_info(uint32_t isp_id,
					struct rts_isp_exp_gain *exp_gain,
					struct rts_isp_sync_regs *regs)
{
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops pseudo_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "pseudo",
	.get_info = pseudo_get_info,
	.get_init_info = pseudo_get_init_info,
	.get_exposure_gain_info = pseudo_get_exposure_gain_info,
	.get_tuned_again = pseudo_get_tuned_again,
	.get_tuned_dgain = pseudo_get_tuned_dgain,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &pseudo_ops;
}

#endif
