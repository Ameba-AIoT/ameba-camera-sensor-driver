/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"
#include "isp_reg_fixp_lib.h"

#if _FIXP_SENSOR_

#define SUPPORTED_ISP_NUM 1


#if CONFIG_FPGA // FPGA
#define SENSOR_WIDTH 640
#define SENSOR_HEIGHT 480
#define SENSOR_HTS (SENSOR_WIDTH+180)
#define SENSOR_MAX_FPS 30
#else  // ASIC // PXP
#define SENSOR_WIDTH 1920
#define SENSOR_HEIGHT 1080
#define SENSOR_HTS (SENSOR_WIDTH+180)
#define SENSOR_MAX_FPS 30
#endif

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#if 0
#define FIXP_FRAME_WIDTH 0x0800
#define FIXP_FRAME_HEIGHT 0x0804
#define FIXP_DUMMY_PIX 0x0808
#define FIXP_DUMMY_LINE 0x080c
#define FIXP_CTRL 0x0820
#define BLOCK_START_X 0x0828
#define BLOCK_START_Y 0x082c
#define BLOCK_WIDTH 0x0830
#define BLOCK_HEIGHT 0x0834
#define MARGIN_WIDTH 0x0838
#define MARGIN_HEIGHT 0x083c
#endif
#define FIXP_START 0x10
#define FIXP_STOP  0x00

struct fixp_status {
	enum rts_isp_sensor_hdr_mode hdr;
	uint16_t fps;
	uint32_t isp_clk;
	uint32_t min_vts;
};

int isp_driver_is_fpga(void);

//extern void *isp_io_base;

static struct fixp_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static int fixp_get_info(uint32_t isp_id,
			 struct rts_isp_sensor_info *info)
{
	int i;
	struct fixp_status *status;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	if (isp_driver_is_fpga()) {
		status->fps = SENSOR_MAX_FPS;//15;
		status->isp_clk = 20e6;//48e6;
	} else {
		status->fps = 30;
		status->isp_clk = 200e6;
	}
	status->min_vts = status->isp_clk / status->fps / SENSOR_HTS;
	if (status->min_vts <= SENSOR_HEIGHT)
		return -RTS_ISP_ERANGE;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = SENSOR_WIDTH;
	info->modes.mode[i].size.h = SENSOR_HEIGHT;
	info->modes.mode[i].fps = status->fps;
	i++;

	info->modes.num = i;

	info->i2c.i2c_id = 0;
	info->i2c.data_len = 1;
	info->i2c.addr_len = 1;


	up->num = 0;
	down->num = 0;

	return RTS_ISP_OK;
}


static int fixp_get_init_info(uint32_t isp_id,
			      const struct rts_isp_sensor_mode *mode,
			      struct rts_isp_sensor_init_info *info)
{
	struct fixp_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("fixp get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	info->interface.interface = SNR_INTERFACE_FIXP;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = SENSOR_WIDTH;
	info->size.h = SENSOR_HEIGHT;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = SENSOR_HTS;
	info->pclk = status->isp_clk;
	info->min_vts = status->min_vts;
	info->max_vts = 65535;

	return RTS_ISP_OK;
}

static int fixp_start(uint32_t isp_id)
{
	struct fixp_status *status;
	uint32_t block_width, block_height, block_start_x, block_start_y;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	isp_write_reg(SENSOR_WIDTH, FIXP_FRAME_WIDTH);
	isp_write_reg(SENSOR_HEIGHT, FIXP_FRAME_HEIGHT);
	isp_write_reg(SENSOR_HTS - SENSOR_WIDTH, FIXP_DUMMY_PIX);
	isp_write_reg(status->min_vts - SENSOR_HEIGHT, FIXP_DUMMY_LINE);

	block_start_x = SENSOR_WIDTH/20;
	block_start_y = SENSOR_HEIGHT/10;

    u16 margin_w = block_start_x/2;
    u16 margin_h = block_start_y/2;

	block_width = (SENSOR_WIDTH - block_start_x*2 - margin_w*7)/6;
	block_height = (SENSOR_HEIGHT - block_start_y*2 - margin_h*5)/4;

	//block_start_x = 0 + block_width;
	//block_start_y = 0 + block_height;

	isp_write_reg(block_width, BLOCK_WIDTH);
	isp_write_reg(block_height, BLOCK_HEIGHT);

    isp_write_reg(margin_w, MARGIN_WIDTH);
    isp_write_reg(margin_h, MARGIN_HEIGHT);

	isp_write_reg(block_start_x, BLOCK_START_X);
	isp_write_reg(block_start_y, BLOCK_START_Y);

	HAL_WRITE32(0x40300000, FIXP_SPEED_CTRL, 0);
	HAL_WRITE32(0x40300000, FIXP_FRAME_NUM, 0);

	return RTS_ISP_OK;
}

static int fixp_stop(uint32_t isp_id)
{
	//isp_write_reg(FIXP_STOP, FIXP_CTRL);
	HAL_WRITE32(0x40300000, FIXP_CTRL, FIXP_STOP);
	return RTS_ISP_OK;
}

static int fixp_get_tuned_again(uint32_t isp_id,
				float again[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int fixp_get_tuned_dgain(uint32_t isp_id,
				float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	return RTS_ISP_OK;
}

static int fixp_get_exposure_gain_info(uint32_t isp_id,
				       const struct rts_isp_sensor_exp_gain *exp_gain,
				       struct rts_isp_sync_regs *regs)
{
	uint32_t dummy;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	dummy = exp_gain->vts - SENSOR_HEIGHT;

	//isp_write_reg(dummy, FIXP_DUMMY_LINE);
	HAL_WRITE32(0x40300000, FIXP_DUMMY_LINE, dummy);	
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops fixp_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "fixp",
	.get_info = fixp_get_info,
	.get_init_info = fixp_get_init_info,
	.start = fixp_start,
	.stop = fixp_stop,
	.get_tuned_again = fixp_get_tuned_again,
	.get_tuned_dgain = fixp_get_tuned_dgain,
	.get_exposure_gain_info = fixp_get_exposure_gain_info,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &fixp_ops;
}

#endif
