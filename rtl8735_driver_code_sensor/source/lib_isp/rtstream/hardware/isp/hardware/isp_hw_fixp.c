/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_interface.h>
#include <isp_reg_fixp.h>
#include <isp_log.h>

static int isp_hw_fixp_start_transfer(uint32_t isp_id,
				     const struct isp_interface_info *info)
{
	isp_info("%s \r\n",__FUNCTION__);
	isp_set_reg_bit(FIXP_SSOR_RUN_OFFSET, FIXP_CTRL);
	return RTS_ISP_OK;
}

static int isp_hw_fixp_stop_transfer(uint32_t isp_id,
				    const struct isp_interface_info *info)
{
	isp_clr_reg_bit(FIXP_SSOR_RUN_OFFSET, FIXP_CTRL);
	return RTS_ISP_OK;
}

static const struct isp_hw_interface_ops hw_fixp_ops = {
	.start_transfer = isp_hw_fixp_start_transfer,
	.stop_transfer = isp_hw_fixp_stop_transfer,
};

const struct isp_hw_interface_ops *isp_hw_fixp_get_ops(void)
{
	return &hw_fixp_ops;
}
