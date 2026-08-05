/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_gamma.h>
#include <isp_reg_gamma.h>

static int isp_hw_set_gamma(uint32_t isp_id, const isp_iq_gamma_item_t *gamma)
{
	int i;

	if (!gamma || gamma->curve_count != 35)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < gamma->curve_count; i += 2)
		if (i != gamma->curve_count - 1)
			isp_write_reg(gamma->curve[i] << GAMMA_P0_OFFSET |
				      gamma->curve[i + 1] << GAMMA_P1_OFFSET,
				      GAMMA_PARAMETER0 + i * 2);
		else
			isp_write_reg(gamma->curve[i] << GAMMA_P0_OFFSET,
				      GAMMA_PARAMETER0 + i * 2);
	isp_write_reg(GAMMA_PLOAD_DLY_MASK, GAMMA_SYNC);

	return RTS_ISP_OK;
}

static const struct isp_hw_gamma_ops hw_gamma_ops = {
	.set_gamma = isp_hw_set_gamma,
};

const struct isp_hw_gamma_ops *isp_hw_gamma_get_ops(void)
{
	return &hw_gamma_ops;
}

