/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_md.h>
#include <isp_reg_virtual.h>
#include <isp_reg_awb.h>
#include <isp_reg_ae.h>
#include <isp_utils.h>
#include <isp_mem.h>

static int isp_hw_md_get_win_num(uint32_t isp_id, uint16_t *ae_win_num, uint16_t *awb_win_num)
{
	uint32_t ae_win_size_reg = isp_read_reg(AE_WIN_SIZE);
	uint32_t awb_win_size_reg = isp_read_reg(AWB_WIN_SIZE);

	*ae_win_num =
		((ae_win_size_reg & AE_WIN_NUM_H_MASK) >>
		 AE_WIN_NUM_H_OFFSET) *
		((ae_win_size_reg & AE_WIN_NUM_V_MASK) >> AE_WIN_NUM_V_OFFSET);

	*awb_win_num = ((awb_win_size_reg & AWB_WIN_NUM_H_MASK) >>
		       AWB_WIN_NUM_H_OFFSET) *
		      ((awb_win_size_reg & AWB_WIN_NUM_V_MASK) >>
		       AWB_WIN_NUM_V_OFFSET);

	return RTS_ISP_OK;
}

static const struct isp_hw_md_ops hw_md_ops = {
	.get_win_num = isp_hw_md_get_win_num
};

const struct isp_hw_md_ops *isp_hw_md_get_ops(void)
{
	return &hw_md_ops;
}
