/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_ygamma.h>
#include <isp_reg_ygamma.h>

static int isp_hw_set_ygamma(uint32_t isp_id, const uint8_t *ygamma, int num)
{
	int i;
	uint32_t offset;

	if (!ygamma || num != 16)
		return -RTS_ISP_EINVAL;

	for (i = 0, offset = YGAMMA_PARAM0; i < num; i += 4, offset += 4) {
		uint32_t ygamma_val = (ygamma[i] |
				       ygamma[i + 1] << 8 |
				       ygamma[i + 2] << 16 |
				       ygamma[i + 3] << 24);
		isp_write_reg(ygamma_val, offset);
	}
	isp_write_reg(YGAMMA_PLOAD_DLY_MASK, YGAMMA_SYNC);

	return RTS_ISP_OK;
}

static const struct isp_hw_ygamma_ops hw_ygamma_ops = {
	.set_ygamma = isp_hw_set_ygamma,
};

const struct isp_hw_ygamma_ops *isp_hw_ygamma_get_ops(void)
{
	return &hw_ygamma_ops;
}

