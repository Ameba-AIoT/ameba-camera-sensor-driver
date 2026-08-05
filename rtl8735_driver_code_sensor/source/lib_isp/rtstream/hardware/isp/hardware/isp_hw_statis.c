/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_statis.h>
#include <isp_reg_statis.h>
#include <isp_reg_sys.h>
#include <isp_driver.h>
#include <rts_isp_sensor.h>
#include "hal_isp.h"

#define LINEAR_STATIS_EN 0x1F
#define HDR_STATIS_EN    0x7F
#define IDLE_VAL 		 0x1DF

static int isp_hw_statis_enable(uint32_t isp_id, int enable, enum rts_isp_sensor_hdr_mode hdr_mode)
{
	u32 sys_idle_val = 0;

	if (enable) {
		isp_write_reg(AEAWBAF_EN_MASK, STATIS_CTRL);
		if(hdr_mode==HDR_MODE)
			isp_write_reg(HDR_STATIS_EN, STATIS_BLOCK_EN);
		else
			isp_write_reg(LINEAR_STATIS_EN, STATIS_BLOCK_EN);

		isp_write_reg(STATIS_TRIGGER_START_MASK, SYS_STATIS_CTRL);
	} else {
		isp_write_reg(0, STATIS_CTRL);
		isp_write_reg(STATIS_TRIGGER_STOP_MASK, SYS_STATIS_CTRL);

		sys_idle_val = (isp_read_reg(SYS_FRAME_IDLE) & IDLE_VAL == IDLE_VAL) ? 1 : 0;
		if ( !hal_isp_is_verify_path_on() || sys_idle_val == 0 ) {

			if ( hal_isp_is_verify_path_on() )
				printf("streaming when verify path disable statis\n");

			isp_driver_wait_event(ISP_DATA_START);
			isp_driver_wait_event(ISP_DATA_START);
		}
	}
	return RTS_ISP_OK;
}

static const struct isp_hw_statis_ops hw_statis_ops = {
	.enable = isp_hw_statis_enable,
};

const struct isp_hw_statis_ops *isp_hw_statis_get_ops(void)
{
	return &hw_statis_ops;
}

