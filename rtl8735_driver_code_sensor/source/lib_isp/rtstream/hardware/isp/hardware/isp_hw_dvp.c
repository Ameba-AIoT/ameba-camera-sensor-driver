/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_interface.h>
#include <isp_reg_dvp.h>

#define PULL_UP 2
#define PULL_DOWN 1
#define PULL_NONE 0

#define SAMPLE_RISING 1
#define SAMPLE_FALLING 0

#define ACTIVE_HIGH 1
#define ACTIVE_LOW 0

static int isp_hw_dvp_start_transfer(uint32_t isp_id,
				     const struct isp_interface_info *info)
{
	const struct rts_isp_dvp_info *dvp;

	if (!info || info->info->interface != SNR_INTERFACE_DVP)
		return -RTS_ISP_EINVAL;

	dvp = &info->info->dvp;
	isp_write_reg((PULL_NONE << DOUT_PULLCTL_OFFSET |
		       PULL_NONE << HSYNC_PULLCTL_OFFSET |
		       PULL_NONE << VSYNC_PULLCTL_OFFSET |
		       PULL_NONE << PIX_CLK_PULLCTL_OFFSET |
		       PULL_NONE << SYS_CLK_PULLCTL_OFFSET),
		      DVP_PULL_CTL);
	isp_write_reg(FW_RST_MASK, DVP_TRANSFER);
	isp_write_reg_mask(dvp->hsync_active_high << HSYNC_POLARITY_OFFSET,
			   DVP_CONFIG, HSYNC_POLARITY_MASK);
	isp_write_reg_mask(dvp->vsync_active_high << VSYNC_POLARITY_OFFSET,
			   DVP_CONFIG, VSYNC_POLARITY_MASK);
	isp_write_reg_mask(dvp->sample_rising << PIXCLK_EDGE_SEL_OFFSET,
			   DVP_CONFIG, PIXCLK_EDGE_SEL_MASK);

	isp_write_reg(isp_read_reg(DVP_CONFIG) & 0xf, DVP_CONFIG);
	if (info->info->bit_depth == SNR_12BIT)
		isp_set_reg_bit(SSOR_RAW12_MODE_OFFSET, DVP_CONFIG);

	if (info->info->type == RAW_SENSOR)
		isp_write_reg(info->size.w, DVP_CROP_WIDTH);
	else
		isp_write_reg(info->size.w * 2, DVP_CROP_WIDTH);
	isp_write_reg(info->size.h, DVP_CROP_HEIGHT);

	isp_write_reg(CCS_EN_MASK, DVP_TRANSFER);
	return RTS_ISP_OK;
}

static int isp_hw_dvp_stop_transfer(uint32_t isp_id,
				    const struct isp_interface_info *info)
{
	isp_write_reg((PULL_DOWN << DOUT_PULLCTL_OFFSET |
		       PULL_DOWN << HSYNC_PULLCTL_OFFSET |
		       PULL_DOWN << VSYNC_PULLCTL_OFFSET |
		       PULL_DOWN << PIX_CLK_PULLCTL_OFFSET |
		       PULL_DOWN << SYS_CLK_PULLCTL_OFFSET),
		      DVP_PULL_CTL);

	isp_write_reg(FW_RST_MASK, DVP_TRANSFER);
	return RTS_ISP_OK;
}

static const struct isp_hw_interface_ops hw_dvp_ops = {
	.start_transfer = isp_hw_dvp_start_transfer,
	.stop_transfer = isp_hw_dvp_stop_transfer,
};

const struct isp_hw_interface_ops *isp_hw_dvp_get_ops(void)
{
	return &hw_dvp_ops;
}
