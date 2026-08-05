/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_mcrop.h>
#include <isp_reg_mcrop.h>

static int isp_hw_mcrop_set_crop(uint32_t isp_id, rts_isp_rect_t *rect)
{
	if (!rect)
		return -RTS_ISP_EINVAL;

	isp_write_reg(rect->start.x, MCROP_START_X);
	isp_write_reg(rect->start.y, MCROP_START_Y);
	isp_write_reg(rect->size.w, MCROP_FRAME_WIDTH);
	isp_write_reg(rect->size.h, MCROP_FRAME_HEIGHT);
	isp_write_reg(CROP_REG_LOAD_MASK, MCROP_REG_LOAD);

	return RTS_ISP_OK;
}

static const struct isp_hw_mcrop_ops hw_mcrop_ops = {
	.set_crop = isp_hw_mcrop_set_crop,
};

const struct isp_hw_mcrop_ops *isp_hw_mcrop_get_ops(void)
{
	return &hw_mcrop_ops;
}

