/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <math.h>
#include <isp_utils.h>
#include <isp_hw_ccm.h>
#include <isp_reg_ccm.h>
#include <isp_reg_virtual.h>

static int isp_hw_ccm_set_ccm(uint32_t isp_id, const isp_iq_ccm_item_t *ccm)
{
	int i;
	uint32_t offset;

	if (!ccm)
		return -RTS_ISP_EINVAL;

	int16_t row_sum = 0;
	for (i = 0, offset = CCM_R_AF_R; i < 9; i++, offset += 4) {
		int16_t cur_val = ccm->ccm[i];
		row_sum += cur_val;

		if (i % 3 == 2) { // Row sum should be 256, otherwise, add difference to third column
			cur_val += (256 - row_sum);
			row_sum = 0;
		}

		isp_write_reg(cur_val, offset);
	}

	isp_write_reg(CCM_REG_LOAD_MASK, CCM_SYNC);

	return RTS_ISP_OK;
}

static int isp_hw_ccm_update_cac(uint32_t isp_id)
{
	float thd0;
	float thd1;
	float log10_thd0;
	float log10_thd1;
	int sat_thd1_offset;
	int sat_thd_diff_offset;
	int sat_thd_slope;
#define log10_4096 3.61236f /* log10f(4096.0) */

	thd0 = clamp(isp_read_vreg(VCAC_SAT_THD0) / 1024.0f,
		     0.01f, 0.99f);
	thd1 = clamp(isp_read_vreg(VCAC_SAT_THD1) / 1024.0f,
		     thd0 + 0.01f, 1.0f);
	log10_thd0 = log10f(thd0);
	log10_thd1 = log10f(thd1);

	sat_thd1_offset = (4095.0f / log10_4096) * -log10_thd1 + 0.5f;
	sat_thd_diff_offset = ((4095.0f / log10_4096) *
			       (log10_thd1 - log10_thd0) + 0.5f);
	sat_thd_slope = (float)(1 << 20) / sat_thd_diff_offset + 0.5f;

	isp_write_reg(sat_thd_slope, PFR_SAT_THD);
	isp_write_reg(sat_thd1_offset << SAT_THD1_OFFSET_OFFSET |
		      sat_thd_diff_offset << SAT_THD_DIFF_OFFSET_OFFSET,
		      PFR_SAT_OFFSET);
	return RTS_ISP_OK;
}

static const struct isp_hw_ccm_ops hw_ccm_ops = {
	.set_ccm = isp_hw_ccm_set_ccm,
	.update_cac = isp_hw_ccm_update_cac,
};

const struct isp_hw_ccm_ops *isp_hw_ccm_get_ops(void)
{
	return &hw_ccm_ops;
}
