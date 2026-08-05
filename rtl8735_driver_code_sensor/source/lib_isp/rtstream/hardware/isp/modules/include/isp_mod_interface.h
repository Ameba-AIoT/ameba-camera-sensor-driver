#ifndef _ISP_MOD_INTERFACE_H_INC_
#define _ISP_MOD_INTERFACE_H_INC_

#include <isp_utils.h>

enum isp_mod_interface_execution_type {
	INTERFACE_EXEC_START = isp_action(EXEC_TYPE, 0),
	INTERFACE_EXEC_STOP = isp_action(EXEC_TYPE, 1),
};

#endif /* _ISP_MOD_INTERFACE_H_INC_ */

