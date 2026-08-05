#ifndef _ISP_MOD_AWB_H_INC_
#define _ISP_MOD_AWB_H_INC_

#include <rts_isp.h>
#include <isp_utils.h>
#include <isp_statis.h>

struct isp_mod_awb_stat_info {
	struct rts_isp_awb_stat_info info;

	uint8_t rgby_size;
	uint8_t rgbg_size;
	uint8_t pixels_size;
};

enum isp_mod_awb_get_info_type {
	AWB_INFO_STATIS = isp_action_r(INFO_TYPE, 0,
				       struct isp_mod_awb_stat_info),
	AWB_INFO_VERSION = isp_action_r(INFO_TYPE, 1, uint16_t),
};

enum isp_mod_awb_exec_type {
	AWB_EXEC_GET_SETTING = isp_action_wr(EXEC_TYPE, 0,
					     struct rts_isp_awb_setting),
	AWB_EXEC_SET_SETTING = isp_action_wr(EXEC_TYPE, 1,
					     struct rts_isp_awb_setting),
	AWB_EXEC_SET_AWB_CLIP = isp_action_w(EXEC_TYPE, 2,
					     int),
};

#endif /* _ISP_MOD_AWB_H_INC_ */
