/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <isp_hw_ygc.h>
#include <isp_reg_ygc.h>

static int isp_hw_set_ygc(uint32_t isp_id, const isp_iq_ygc_item_t *ygc)
{
	int i;
	uint32_t offset;

	if (!ygc || ygc->curve_count != 63)
		return -RTS_ISP_EINVAL;

	for (i = 0, offset = YGC_CURVE0; i < ygc->curve_count - 1;
	     i += 2, offset += 4)
		isp_write_reg(ygc->curve[i] | (ygc->curve[i + 1] << 16),
			      offset);
	isp_write_reg(ygc->curve[i], offset);
	isp_write_reg(YGC_REG_LOAD_MASK, YGC_REG_LOAD);

	return RTS_ISP_OK;
}

static const struct isp_hw_ygc_ops hw_ygc_ops = {
	.set_ygc = isp_hw_set_ygc,
};

const struct isp_hw_ygc_ops *isp_hw_ygc_get_ops(void)
{
	return &hw_ygc_ops;
}

