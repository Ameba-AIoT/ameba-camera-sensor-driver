#ifndef _ISP_MOD_GLOBAL_H_INC_
#define _ISP_MOD_GLOBAL_H_INC_

#include <rts_isp.h>
#include <isp_utils.h>
#include <rts_isp_sensor.h>

enum isp_mod_global_info_type {
	GLOBAL_INFO_IS_FPGA = isp_action_r(INFO_TYPE, 0, int),
	GLOBAL_INFO_ISP_CLK = isp_action_r(INFO_TYPE, 1, uint32_t),
};

enum isp_mod_global_execution_type {
	GLOBAL_EXEC_START = isp_action(EXEC_TYPE, 0),
	GLOBAL_EXEC_STOP = isp_action(EXEC_TYPE, 1),
	GLOBAL_EXEC_SELECT_INTERFACE = isp_action_w(EXEC_TYPE, 2, enum rts_isp_interface),
	GLOBAL_EXEC_GET_BYPASS = isp_action_r(EXEC_TYPE, 3,
					      struct rts_isp_bypass),
	GLOBAL_EXEC_SET_BYPASS = isp_action_w(EXEC_TYPE, 4,
					      struct rts_isp_bypass),
	GLOBAL_EXEC_SET_DELAY_FRAMES = isp_action_wr(EXEC_TYPE, 5,
					      struct rts_isp_sensor_mirror_flip *),
	GLOBAL_EXEC_SET_TNR_ENABLE = isp_action_w(EXEC_TYPE, 6, int),
	GLOBAL_EXEC_SET_DEHAZE_ENABLE = isp_action_w(EXEC_TYPE, 7, int),
	GLOBAL_EXEC_SET_WDR_ENABLE = isp_action_w(EXEC_TYPE, 8, int),
	GLOBAL_EXEC_SET_LDC_ENABLE = isp_action_w(EXEC_TYPE, 9, int),
	GLOBAL_EXEC_SET_VHDR_ENABLE = isp_action_w(EXEC_TYPE, 10, int),
	GLOBAL_EXEC_SET_STATIS_IRQ_ENABLE = isp_action_w(EXEC_TYPE, 11, int),
};

#endif /* _ISP_MOD_GLOBAL_H_INC_ */

