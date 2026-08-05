#ifndef _ISP_MOD_WDR_H_INC_
#define _ISP_MOD_WDR_H_INC_

#include <isp_utils.h>
#include <rts_isp.h>

enum isp_mod_wdr_execution_type {
	WDR_EXEC_GET_DIR_LEVEL = isp_action_r(EXEC_TYPE, 0, uint8_t),
	WDR_EXEC_SET_DIR_LEVEL = isp_action_w(EXEC_TYPE, 1, uint8_t),
};

#endif /* _ISP_MOD_WDR_H_INC_ */

