/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_crop.h>
#include <isp_reg_crop.h>

static int isp_hw_crop_set_crop(uint32_t isp_id, rts_isp_rect_t *rect)
{
	if (!rect)
		return -RTS_ISP_EINVAL;

	//Short Exp. Path Crop
	isp_write_reg(rect->start.x, CROP_SE_START_X);
	isp_write_reg(rect->start.y, CROP_SE_START_Y);
	isp_write_reg(rect->size.w, CROP_SE_FRAME_WIDTH);
	isp_write_reg(rect->size.h, CROP_SE_FRAME_HEIGHT);
	isp_write_reg(CROP_REG_LOAD_MASK, CROP_SE_REG_LOAD);

	//LONG Exp. Path Crop
	isp_write_reg(rect->start.x, CROP_LE_START_X);
	isp_write_reg(rect->start.y, CROP_LE_START_Y);
	isp_write_reg(rect->size.w, CROP_LE_FRAME_WIDTH);
	isp_write_reg(rect->size.h, CROP_LE_FRAME_HEIGHT);
	isp_write_reg(CROP_REG_LOAD_MASK, CROP_LE_REG_LOAD);

	return RTS_ISP_OK;
}

static const struct isp_hw_crop_ops hw_crop_ops = {
	.set_crop = isp_hw_crop_set_crop,
};

const struct isp_hw_crop_ops *isp_hw_crop_get_ops(void)
{
	return &hw_crop_ops;
}

