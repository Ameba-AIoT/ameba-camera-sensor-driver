#ifndef _ISP_MOD_AF_H_INC_
#define _ISP_MOD_AF_H_INC_

#include <isp_utils.h>
#include <isp_statis.h>

struct isp_mod_af_stat_info {
	struct rts_isp_af_stat_info info;

	uint8_t win_edge_size;
};

enum isp_mod_af_get_info_type {
	AF_INFO_STATIS = isp_action_r(INFO_TYPE, 0,
				      struct isp_mod_af_stat_info),
	AF_INFO_VERSION = isp_action_r(INFO_TYPE, 1, uint16_t),
};

#endif /* _ISP_MOD_AF_H_INC_ */

