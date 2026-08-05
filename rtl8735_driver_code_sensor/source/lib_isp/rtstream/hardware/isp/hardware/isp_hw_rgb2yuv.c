/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_rgb2yuv.h>
#include <isp_reg_sys.h>
#include <isp_reg_rgb2yuv.h>

#define COEF_MULT 4096

static const int yr = 872;
static const int yg = 2929;
static const int yb = 295;
static const int ur = 471;
static const int ug = 1577;
static const int ub = 2048;
static const int vr = 2048;
static const int vg = 1860;
static const int vb = 188;
static const int y_offset;

static int isp_hw_rgb2yuv_init(uint32_t isp_id)
{
	isp_write_reg_mask(YMODE_MASK | YBT709_MASK, SYS_CONTROL2,
			   YMODE_MASK | YBT709_MASK);
	isp_write_reg((yr << YBT709_YR_OFFSET | yg << YBT709_YG_OFFSET),
		      RGB2YUV0);
	isp_write_reg((yb << YBT709_YB_OFFSET | ur << YBT709_UR_OFFSET),
		      RGB2YUV1);
	isp_write_reg((ug << YBT709_UG_OFFSET | ub << YBT709_UB_OFFSET),
		      RGB2YUV2);
	isp_write_reg((vr << YBT709_VR_OFFSET | vg << YBT709_VG_OFFSET),
		      RGB2YUV3);
	isp_write_reg((vb << YBT709_VB_OFFSET), RGB2YUV4);
	isp_write_reg(y_offset, RGB2YUV_YOFFSET);

	return RTS_ISP_OK;
}

static int isp_hw_rgb2yuv_convert(uint32_t isp_id, uint32_t *rgb2yuv)
{
	int r, g, b;
	int y, u, v;

	if (!rgb2yuv)
		return -RTS_ISP_EINVAL;

	r = *rgb2yuv & 0xff;
	g = (*rgb2yuv >> 8) & 0xff;
	b = (*rgb2yuv >> 16) & 0xff;

	y = (yr * r + yg * g + yb * b) / COEF_MULT + y_offset / 4;
	u = (-ur * r - ug * g + ub * b) / COEF_MULT + 128;
	v = (vr * r - vg * g - vb * b) / COEF_MULT + 128;

	*rgb2yuv = y | u << 8 | v << 16;

	return RTS_ISP_OK;
}

static const struct isp_hw_rgb2yuv_ops hw_rgb2yuv_ops = {
	.init = isp_hw_rgb2yuv_init,
	.convert = isp_hw_rgb2yuv_convert,
};

const struct isp_hw_rgb2yuv_ops *isp_hw_rgb2yuv_get_ops(void)
{
	return &hw_rgb2yuv_ops;
}

