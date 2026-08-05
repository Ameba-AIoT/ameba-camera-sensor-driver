/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_interface.h>
#include <isp_reg.h>


#define VERIFY_REG_BASE 0xB000
#define VERIFY_Y_DDR_ADDR0 (VERIFY_REG_BASE + 0x0008)
#define VERIFY_Y_DDR_ADDR1 (VERIFY_REG_BASE + 0x000C)
#define VERIFY_UV_DDR_ADDR0 (VERIFY_REG_BASE + 0x0010)
#define VERIFY_UV_DDR_ADDR1 (VERIFY_REG_BASE + 0x0014)
#define VERIFY_INT_FLAG (VERIFY_REG_BASE + 0x003C)
#define VERIFY_START_FLAG (VERIFY_REG_BASE + 0x0040)

static int isp_hw_vinf_start_transfer(uint32_t isp_id,
				     const struct isp_interface_info *info)
{
	return RTS_ISP_OK;
}

static int isp_hw_vinf_stop_transfer(uint32_t isp_id,
				    const struct isp_interface_info *info)
{
	return RTS_ISP_OK;
}

void isp_hw_verify_path_config_buf(u32 idx)
{
	struct verify_ctrl_config v_cfg;

	hal_isp_get_verify_info(&v_cfg);

	isp_write_reg(v_cfg.verify_addr[idx], VERIFY_Y_DDR_ADDR0);
	isp_write_reg(v_cfg.verify_addr[idx], VERIFY_Y_DDR_ADDR1);
	isp_write_reg(v_cfg.verify_addr[idx] + v_cfg.verify_ylen, VERIFY_UV_DDR_ADDR0);
	isp_write_reg(v_cfg.verify_addr[idx] + v_cfg.verify_ylen, VERIFY_UV_DDR_ADDR1);

}

void isp_hw_verify_path_trigger(u32 delay_ms)
{
	u32 val = 0;

	vTaskDelay(delay_ms);

	val = isp_read_reg(VERIFY_INT_FLAG);

	if (val == 1)
		isp_write_reg(0x1, VERIFY_INT_FLAG);

	isp_write_reg(0x1, VERIFY_START_FLAG);
}

static const struct isp_hw_interface_ops hw_vinf_ops = {
	.start_transfer = isp_hw_vinf_start_transfer,
	.stop_transfer = isp_hw_vinf_stop_transfer,
};

const struct isp_hw_interface_ops *isp_hw_vinf_get_ops(void)
{
	return &hw_vinf_ops;
}
