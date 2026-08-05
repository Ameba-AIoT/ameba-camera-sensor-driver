/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_blc.h>
#include <isp_reg_blc.h>

/*
#define div_u32_round(v0, v1) \
	(((uint32_t)(v0) + (uint32_t)(v1) / 2) / (uint32_t)(v1))
#define get_blc_gain(offset) \
	div_u32_round((uint32_t)offset << 12, 4095 - offset)
*/
static uint32_t get_blc_gain(uint32_t offset, uint32_t m)
{
	uint32_t v0;
	uint32_t v1;

	v0 = (offset + m) << 12;
	v1 = 4095 - m - offset;

	return (v0 + v1 - 1) / v1;
}

static int isp_hw_blc_info_get_num(uint32_t isp_id)
{
	return 2;
}

static int isp_hw_blc_info_set(uint32_t isp_id,
			       const isp_iq_blc_offset_t *blc, int bits)
{
	int m;

	if (!blc)
		return -RTS_ISP_EINVAL;

	m = (1 << (12 - bits)) - 1;

	isp_write_reg(blc->r[1], BLC_SE_OFFSET_R);
	isp_write_reg(blc->gr[1], BLC_SE_OFFSET_GR);
	isp_write_reg(blc->gb[1], BLC_SE_OFFSET_GB);
	isp_write_reg(blc->b[1], BLC_SE_OFFSET_B);
	isp_write_reg(get_blc_gain(blc->r[1], m), BLC_SE_GAIN_R);
	isp_write_reg(get_blc_gain(blc->gr[1], m), BLC_SE_GAIN_GR);
	isp_write_reg(get_blc_gain(blc->gb[1], m), BLC_SE_GAIN_GB);
	isp_write_reg(get_blc_gain(blc->b[1], m), BLC_SE_GAIN_B);
	isp_write_reg(BLC_REGISTER_LOAD_MASK, BLC_SE_SYNC);

	isp_write_reg(blc->r[0], BLC_LE_OFFSET_R);
	isp_write_reg(blc->gr[0], BLC_LE_OFFSET_GR);
	isp_write_reg(blc->gb[0], BLC_LE_OFFSET_GB);
	isp_write_reg(blc->b[0], BLC_LE_OFFSET_B);
	isp_write_reg(get_blc_gain(blc->r[0], m), BLC_LE_GAIN_R);
	isp_write_reg(get_blc_gain(blc->gr[0], m), BLC_LE_GAIN_GR);
	isp_write_reg(get_blc_gain(blc->gb[0], m), BLC_LE_GAIN_GB);
	isp_write_reg(get_blc_gain(blc->b[0], m), BLC_LE_GAIN_B);
	isp_write_reg(BLC_REGISTER_LOAD_MASK, BLC_LE_SYNC);

	return RTS_ISP_OK;
}

static const struct isp_hw_blc_ops hw_blc_ops = {
	.get_num = isp_hw_blc_info_get_num,
	.set = isp_hw_blc_info_set,
};

const struct isp_hw_blc_ops *isp_hw_blc_get_ops(void)
{
	return &hw_blc_ops;
}
