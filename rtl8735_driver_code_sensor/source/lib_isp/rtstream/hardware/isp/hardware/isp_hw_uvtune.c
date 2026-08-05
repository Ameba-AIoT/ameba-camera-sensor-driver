/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_uvtune.h>
#include <isp_reg_uvtune.h>

static void hw_uvtune_uv_slope(uint32_t isp_id)
{
	uint32_t uvs_thd0;
	uint32_t uvs_thd1;
	uint32_t uv_slope;

	uvs_thd0 = isp_read_reg(UVS_THD) & UVS_THD0_MASK;
	uvs_thd1 = isp_read_reg(UVS_THD) >> UVS_THD1_OFFSET;

	if (uvs_thd1 <= uvs_thd0)
		uvs_thd1 = uvs_thd0 + 1;

	uv_slope = 16384.0f / (uvs_thd1 - uvs_thd0) + 0.5f;

	isp_write_reg(uv_slope, UV_SLOPE);
}

static int isp_hw_uvtune_set_regs(uint32_t isp_id,
				  const isp_iq_uvtune_item_t *item)
{
	int i;

	if (!item || !item->mats || item->mats_count != 64)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < item->mats_count; i += 2)
		isp_write_reg((uint16_t)item->mats[i] << UN_TUNE_MAT0_OFFSET |
			     (uint16_t)item->mats[i + 1] << UN_TUNE_MAT1_OFFSET,
			      UVTUNE_MAT0 + i * 2);

	isp_write_reg(1, UV_SYNC);
	return RTS_ISP_OK;
}

static int isp_hw_uvtune_estimation(uint32_t isp_id)
{
	hw_uvtune_uv_slope(isp_id);
	return RTS_ISP_OK;
}

static const struct isp_hw_uvtune_ops hw_uvtune_ops = {
	.set_regs = isp_hw_uvtune_set_regs,
	.estimation = isp_hw_uvtune_estimation,
};

const struct isp_hw_uvtune_ops *isp_hw_uvtune_get_ops(void)
{
	return &hw_uvtune_ops;
}

