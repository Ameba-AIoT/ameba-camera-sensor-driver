#ifndef _ISP_MOD_NLSC_H_INC_
#define _ISP_MOD_NLSC_H_INC_

#include <isp_utils.h>
#include <rts_isp_geom.h>

enum isp_mod_nlsc_execute_type {
	NLSC_EXEC_SET_OFFSET = isp_action_w(EXEC_TYPE, 0, rts_isp_point_t),
};

#endif /* _ISP_MOD_NLSC_H_INC_ */

