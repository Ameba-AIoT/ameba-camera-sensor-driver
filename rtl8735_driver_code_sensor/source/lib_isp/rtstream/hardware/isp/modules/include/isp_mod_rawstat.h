#ifndef _ISP_MOD_RAWSTAT_H_INC_
#define _ISP_MOD_RAWSTAT_H_INC_

#include <isp_utils.h>
#include <isp_statis.h>

struct isp_mod_rawstat_stat_info {
	struct rts_isp_raw_stat_info info;

	uint8_t rgby_size;
	uint8_t rgbg_size;
	uint8_t pixels_size;
};

enum isp_mod_raw_get_info_type {
	RAWSTAT_INFO_STATIS = isp_action_r(INFO_TYPE, 0,
					   struct isp_mod_rawstat_stat_info),
};

#endif /* _ISP_MOD_RAWSTAT_H_INC_ */

