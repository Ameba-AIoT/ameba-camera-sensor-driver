/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <math.h>
#include <isp_utils.h>
#include <isp_hw_mlsc.h>
#include <isp_reg_mlsc.h>

#define MLSC_MATRIX_COUNT 1536

static int isp_hw_set_mlsc(uint32_t isp_id, const isp_iq_mlsc_t *mlsc)
{
	int i;
	uint32_t offset;

	if (!mlsc || mlsc->matrix_r_count != MLSC_MATRIX_COUNT ||
	    mlsc->matrix_g_count != MLSC_MATRIX_COUNT ||
	    mlsc->matrix_b_count != MLSC_MATRIX_COUNT)
		return -RTS_ISP_EINVAL;

	for (i = 0, offset = MLSC_PARA0; i < mlsc->matrix_r_count;
	     i++, offset += 4)
		isp_write_reg(mlsc->matrix_r[i] << RF_MLSC_R_DAT_OFFSET |
			      mlsc->matrix_g[i] << RF_MLSC_GR_DAT_OFFSET |
			      mlsc->matrix_g[i] << RF_MLSC_GB_DAT_OFFSET |
			      mlsc->matrix_b[i] << RF_MLSC_B_DAT_OFFSET,
			      offset);
	isp_write_reg(mlsc->mode, MLSC_CTRL);
	return RTS_ISP_OK;
}

static const struct isp_hw_mlsc_ops hw_mlsc_ops = {
	.set_mlsc = isp_hw_set_mlsc,
};

const struct isp_hw_mlsc_ops *isp_hw_mlsc_get_ops(void)
{
	return &hw_mlsc_ops;
}
