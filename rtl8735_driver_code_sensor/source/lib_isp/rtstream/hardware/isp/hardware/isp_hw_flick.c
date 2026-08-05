/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_flick.h>
#include <isp_reg_flick.h>

static int isp_hw_flick_set_statis(uint32_t isp_id, const rts_isp_rect_t *rect)
{
	uint32_t step_h, step_v;

	step_h = rect->w * 16 / 512;
	step_v = (rect->h > 1080) ? (1080 * 16 / 256) : (rect->h * 16 / 256);
	isp_write_reg(step_h << FLICK_H_DEC_OFFSET |
		      step_v << FLICK_V_DEC_OFFSET,
		      FLICK_SAMPLE_STEP);
	isp_write_reg(rounddown(rect->x, 8) << FLICK_START_H_OFFSET |
		      rounddown(rect->y, 8) << FLICK_START_V_OFFSET,
		      FLICK_SAMPLE_START);
	isp_write_reg_mask(6 << FLICK_SHIFT_BITS_OFFSET,
			   FLICK_FFT_RESULT_CONTRL, FLICK_SHIFT_BITS_MASK);
	isp_write_reg(0x10, FLICK_CTRL);
	return RTS_ISP_OK;
}

static const struct isp_hw_flick_ops hw_flick_ops = {
	.set_statis = isp_hw_flick_set_statis,
};

const struct isp_hw_flick_ops *isp_hw_flick_get_ops(void)
{
	return &hw_flick_ops;
}
