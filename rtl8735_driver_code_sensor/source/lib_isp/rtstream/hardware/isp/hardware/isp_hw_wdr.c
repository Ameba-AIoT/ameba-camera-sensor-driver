/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_wdr.h>
#include <isp_reg_wdr.h>
#include <isp_reg_virtual.h>

static int isp_hw_wdr_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(WDR_LEVEL_CTRL_DEF, VWDR_LEVEL);
	return RTS_ISP_OK;
}

static int isp_hw_wdr_set_config(uint32_t isp_id)
{
	int i;
	static int lpf_coef[9] = {
		0, 1, 3, 5, 6, 6, 5, 4, 2
	};
	static int curve[28] = {
		72, 67, 62, 57, 52, 47, 43, 39, 35, 32, 29, 26, 23, 20, 18, 16,
		14, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
	};
	static int contrast_curve[15] = {
		24, 26, 26, 24, 20, 20, 20, 20, 20, 20, 20, 20, 20, 23, 26
	};

	for (i = 0; i < (int)ARRAY_SIZE(lpf_coef); i += 4)
		if (i != ARRAY_SIZE(lpf_coef) - 1)
			isp_write_reg(lpf_coef[i] << LPF_C0_OFFSET |
				      lpf_coef[i + 1] << LPF_C1_OFFSET |
				      lpf_coef[i + 2] << LPF_C2_OFFSET |
				      lpf_coef[i + 3] << LPF_C3_OFFSET,
				      WDR_LPF_COEF0 + i);
		else
			isp_write_reg(lpf_coef[i] << LPF_C0_OFFSET,
				      WDR_LPF_COEF0 + i);

	for (i = 0; i < (int)ARRAY_SIZE(curve); i += 4)
		isp_write_reg(curve[i] << HDR_P0_OFFSET |
			      curve[i + 1] << HDR_P1_OFFSET |
			      curve[i + 2] << HDR_P2_OFFSET |
			      curve[i + 3] << HDR_P3_OFFSET,
			      WDR_PARAM0 + i);

	for (i = 0; i < (int)ARRAY_SIZE(contrast_curve); i += 4)
		if (i != ARRAY_SIZE(contrast_curve) - 3)
			isp_write_reg(contrast_curve[i] << CONT_P0_OFFSET |
				      contrast_curve[i + 1] << CONT_P1_OFFSET |
				      contrast_curve[i + 2] << CONT_P2_OFFSET |
				      contrast_curve[i + 3] << CONT_P3_OFFSET,
				      WDR_CONT_PARAM0 + i);
		else
			isp_write_reg(contrast_curve[i] << CONT_P0_OFFSET |
				      contrast_curve[i + 1] << CONT_P1_OFFSET |
				      contrast_curve[i + 2] << CONT_P2_OFFSET,
				      WDR_CONT_PARAM0 + i);

	isp_write_reg_mask(4 << HDR_STEP_OFFSET, WDR_STEP, HDR_STEP_MASK);
	isp_write_reg_mask(16 << CONT_STEP_OFFSET, WDR_STEP, CONT_STEP_MASK);
	isp_write_reg_mask(0 << CONT_LEVEL_OFFSET, WDR_LEVEL, CONT_LEVEL_MASK);
	isp_write_reg_mask(13 << CONT_RATE_MIN_OFFSET, WDR_CONT_RATE_BOUND,
			   CONT_RATE_MIN_MASK);
	isp_write_reg_mask(13 << CONT_RATE_MAX_OFFSET, WDR_CONT_RATE_BOUND,
			   CONT_RATE_MAX_MASK);
	isp_write_reg_mask(5 << HDR_INC_RATE0_OFFSET, WDR_INC_RATE,
			   HDR_INC_RATE0_MASK);
	isp_write_reg_mask(1 << HDR_INC_RATE1_OFFSET, WDR_INC_RATE,
			   HDR_INC_RATE1_MASK);

	return RTS_ISP_OK;
}

static int isp_hw_wdr_set_enable(uint32_t isp_id, int enable)
{
	if (enable) {
		isp_write_reg_mask(1 << LPF_EN_OFFSET | 1 << CONT_EN_OFFSET |
				   1 << HDR_LOC_ADJ_EN_OFFSET, WDR_ENABLE,
				   LPF_EN_MASK | CONT_EN_MASK |
				   HDR_LOC_ADJ_EN_MASK);
	} else {
		isp_write_reg_mask(0 << LPF_EN_OFFSET | 0 << CONT_EN_OFFSET |
				   0 << HDR_LOC_ADJ_EN_OFFSET, WDR_ENABLE,
				   LPF_EN_MASK | CONT_EN_MASK |
				   HDR_LOC_ADJ_EN_MASK);
	}
	return RTS_ISP_OK;
}

static int isp_hw_wdr_set_level(uint32_t isp_id, uint8_t level, int load_mode)
{
	isp_write_reg_mask(level << HDR_LEVEL_OFFSET, WDR_LEVEL,
			   HDR_LEVEL_MASK);
	isp_write_reg_mask(1 << ADJ_TRIG_OFFSET, WDR_LOAD, ADJ_TRIG_MASK);
	isp_write_reg_mask(load_mode << HDR_MODE_OFFSET, WDR_MODE,
			   HDR_MODE_MASK);
	return RTS_ISP_OK;
}

static uint8_t isp_hw_wdr_get_level(uint32_t isp_id)
{
	return isp_read_reg(WDR_LEVEL) & HDR_LEVEL_MASK;
}

static int isp_hw_wdr_set_step(uint32_t isp_id, uint16_t step)
{
	isp_write_reg_mask(step << HDR_STEP_OFFSET, WDR_STEP, HDR_STEP_MASK);
	return RTS_ISP_OK;
}

static int isp_hw_wdr_get_iq_level(uint32_t isp_id)
{
	return isp_read_vreg(VWDR_LEVEL);
}

static const struct isp_hw_wdr_ops hw_wdr_ops = {
	.init_vreg = isp_hw_wdr_init_vreg,
	.set_config = isp_hw_wdr_set_config,
	.set_enable = isp_hw_wdr_set_enable,
	.set_level = isp_hw_wdr_set_level,
	.get_level = isp_hw_wdr_get_level,
	.set_step = isp_hw_wdr_set_step,
	.get_iq_level = isp_hw_wdr_get_iq_level,
};

const struct isp_hw_wdr_ops *isp_hw_wdr_get_ops(void)
{
	return &hw_wdr_ops;
}

