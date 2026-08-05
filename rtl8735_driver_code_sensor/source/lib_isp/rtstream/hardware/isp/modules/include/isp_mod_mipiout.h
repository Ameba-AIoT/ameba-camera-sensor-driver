#ifndef _ISP_MOD_MIPIOUT_H_INC_
#define _ISP_MOD_MIPIOUT_H_INC_

#include <rtsavisp.h>
#include <isp_utils.h>

enum isp_mod_mipiout_execution_type {
	MIPIOUT_EXEC_GET = isp_action_r(EXEC_TYPE, 0, struct rts_isp_mipiout),
	MIPIOUT_EXEC_SET = isp_action_w(EXEC_TYPE, 1, struct rts_isp_mipiout),
};

#endif /* _ISP_MOD_MIPIOUT_H_INC_ */

