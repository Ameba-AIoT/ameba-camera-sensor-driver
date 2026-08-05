#ifndef _ISP_MOD_MCROP_H_INC_
#define _ISP_MOD_MCROP_H_INC_

#include <rts_isp_geom.h>
#include <isp_utils.h>

enum isp_mod_mcrop_get_info_type {
	MCROP_INFO_ISP_SIZE = isp_action_r(INFO_TYPE, 0, rts_isp_size_t),
};

#endif /* _ISP_MOD_MCROP_H_INC_ */
