#ifndef _ISP_MOD_YSTAT_H_INC_
#define _ISP_MOD_YSTAT_H_INC_

#include <isp_utils.h>
#include <isp_statis.h>

struct isp_mod_ystat_stat_info {
	struct rts_isp_y_stat_info info;

	uint8_t win_mean_size;
	uint8_t hist_bin_size;
};

enum isp_mod_ystat_get_info_type {
	YSTAT_INFO_STATIS = isp_action_r(INFO_TYPE, 0,
					 struct isp_mod_ystat_stat_info),
};

#endif /* _ISP_MOD_YSTAT_H_INC_ */

