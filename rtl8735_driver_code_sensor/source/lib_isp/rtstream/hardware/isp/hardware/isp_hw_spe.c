/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_spe.h>
#include <isp_reg_spe.h>
#include <isp_reg_virtual.h>

static inline void isp_hw_spe_sync(uint32_t isp_id)
{
	isp_write_reg(1, SPE_SYNC);
}

static int isp_hw_spe_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(0, VSPE_Y_OFFSET);
	isp_write_vreg(32, VSPE_Y_CONTRAST);
	isp_write_vreg(64, VSPE_UV_GAIN);
	isp_write_vreg(SATURATION_CTRL_DEF, VSATURATION);
	isp_write_vreg(CONTRAST_CTRL_DEF, VCONTRAST);
	return RTS_ISP_OK;
}

static int isp_hw_spe_set_uv_offset(uint32_t isp_id,
				const isp_iq_uv_offset_item_t *uv_offset)
{
	if (!uv_offset)
		return -RTS_ISP_EINVAL;

	isp_write_reg(uv_offset->u, SPE_U_OFFSET);
	isp_write_reg(uv_offset->v, SPE_V_OFFSET);

	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_spe_set_brightness(uint32_t isp_id, int value)
{
	int y_offset;
	const int vy_offset = isp_read_vreg(VSPE_Y_OFFSET);

	if (value < BRIGHT_CTRL_DEF)
		y_offset = linear_intp(value,
				       BRIGHT_CTRL_MIN, BRIGHT_CTRL_MIN,
				       BRIGHT_CTRL_DEF, vy_offset);
	else
		y_offset = linear_intp(value,
				       BRIGHT_CTRL_DEF, vy_offset,
				       BRIGHT_CTRL_MAX, BRIGHT_CTRL_MAX);

	isp_write_reg(y_offset, SPE_Y_OFFSET);
	//printf("isp_hw_spe_set_brightness %d \n", y_offset);
	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_spe_set_contrast(uint32_t isp_id, int value)
{
	int contrast;
	const int min = 16;
	const int max = 80;
	const int def = isp_read_vreg(VSPE_Y_CONTRAST);  // 32
	const int val_def = isp_read_vreg(VCONTRAST);    // 50

	if (value < CONTRAST_CTRL_DEF)
		value = linear_intp(value,
				    CONTRAST_CTRL_MIN, CONTRAST_CTRL_MIN,
				    CONTRAST_CTRL_DEF, val_def);
	else
		value = linear_intp(value,
				    CONTRAST_CTRL_DEF, val_def,
				    CONTRAST_CTRL_MAX, CONTRAST_CTRL_MAX);

	if (value < CONTRAST_CTRL_DEF)
		contrast = linear_intp(value, CONTRAST_CTRL_MIN, min,
				       CONTRAST_CTRL_DEF, def);
	else
		contrast = linear_intp(value, CONTRAST_CTRL_DEF, def,
				       CONTRAST_CTRL_MAX, max);

	isp_write_reg_mask(contrast << YCONTRAST_OFFSET,
			   SPE_YCONTRAST, YCONTRAST_MASK);
	//printf("isp_hw_spe_set_contrast %d v %d after\n", contrast, value);

	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_spe_set_saturation(uint32_t isp_id, int value)
{
	int saturation;
	const int min = 0;
	const int max = 255;
	const int def = isp_read_vreg(VSPE_UV_GAIN);
	const int val_def = isp_read_vreg(VSATURATION);

	if (value < SATURATION_CTRL_DEF)
		value = linear_intp(value,
				    SATURATION_CTRL_MIN, SATURATION_CTRL_MIN,
				    SATURATION_CTRL_DEF, val_def);
	else
		value = linear_intp(value,
				    SATURATION_CTRL_DEF, val_def,
				    SATURATION_CTRL_MAX, SATURATION_CTRL_MAX);

	if (value < SATURATION_CTRL_DEF)
		saturation = linear_intp(value, SATURATION_CTRL_MIN, min,
					 SATURATION_CTRL_DEF, def);
	else
		saturation = linear_intp(value, SATURATION_CTRL_DEF, def,
					 SATURATION_CTRL_MAX, max);

	isp_write_reg(saturation, SPE_U_GAIN);
	isp_write_reg(saturation, SPE_V_GAIN);
	//printf("isp_hw_spe_set_saturation %d v %d after\n", saturation, value);
	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_spe_set_gray_mode(uint32_t isp_id, int enable)
{
	isp_write_reg_mask(enable << GRAY_EN_OFFSET, SPE_CTRL_EN, GRAY_EN_MASK);

	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_spe_set_y_gain(uint32_t isp_id, int value)
{
	int y_gain;
	const int min = 0x40;
	const int max = 0xe0;
	const int def = 0x80;

	if (value < YGAIN_CTRL_DEF)
		y_gain = linear_intp_bound(value, YGAIN_CTRL_MIN, min,
					   YGAIN_CTRL_DEF, def);
	else
		y_gain = linear_intp_bound(value, YGAIN_CTRL_DEF, def,
					   YGAIN_CTRL_MAX, max);

	isp_write_reg(y_gain, SPE_Y_GAIN);

	isp_hw_spe_sync(isp_id);

	return RTS_ISP_OK;
}

static const struct isp_hw_spe_ops hw_spe_ops = {
	.init_vreg = isp_hw_spe_init_vreg,
	.set_uv_offset = isp_hw_spe_set_uv_offset,
	.set_brightness = isp_hw_spe_set_brightness,
	.set_contrast = isp_hw_spe_set_contrast,
	.set_saturation = isp_hw_spe_set_saturation,
	.set_gray_mode = isp_hw_spe_set_gray_mode,
	.set_y_gain = isp_hw_spe_set_y_gain,
};

const struct isp_hw_spe_ops *isp_hw_spe_get_ops(void)
{
	return &hw_spe_ops;
}

