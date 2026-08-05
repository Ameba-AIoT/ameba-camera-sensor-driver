#ifndef _ISP_MOD_AE_H_INC_
#define _ISP_MOD_AE_H_INC_

#include <rts_isp.h>
#include <isp_utils.h>
#include <isp_statis.h>
#include "hal_isp.h"
struct isp_mod_ae_hdr_stat_info {
	uint8_t win_mean_size;
	uint8_t hist_bin_size;
};

struct isp_mod_ae_stat_info {
	struct rts_isp_ae_stat_info info;
	uint8_t win_mean_size;
	uint8_t hist_bin_size;
	struct isp_mod_ae_hdr_stat_info hdr[RTS_ISP_HDR_CHAN_MAX];
};

struct isp_mod_ae_debug_info {
	uint8_t ae_debug_info[ISP_DEBUG_INFO_LEN];
};


enum isp_mod_ae_get_info_type {
	AE_INFO_STATIS = isp_action_r(INFO_TYPE, 0,
				      struct isp_mod_ae_stat_info),
	AE_INFO_EXPOSURE = isp_action_r(INFO_TYPE, 1, float),
	AE_INFO_STATUS = isp_action_r(INFO_TYPE, 2,
				      enum rts_isp_ae_algo_status),
	AE_INFO_GAIN = isp_action_r(INFO_TYPE, 3, float),
	AE_INFO_VERSION = isp_action_r(INFO_TYPE, 4, uint16_t),
	AE_INFO_TARGET = isp_action_r(INFO_TYPE, 5, uint16_t),
	AE_INFO_DEBUG_BUF = isp_action_r(INFO_TYPE, 6, struct isp_mod_ae_debug_info),

};

enum isp_mod_ae_exec_type {
	AE_EXEC_SET_PLFREQ = isp_action_w(EXEC_TYPE, 0,
					  uint32_t),
	AE_EXEC_GET_SETTING = isp_action_wr(EXEC_TYPE, 1,
					    struct rts_isp_ae_setting),
	AE_EXEC_SET_SETTING = isp_action_wr(EXEC_TYPE, 2,
					    struct rts_isp_ae_setting),
	AE_EXEC_SET_TARGET_DELTA = isp_action_wr(EXEC_TYPE, 3, int),
	AE_EXEC_SET_FPS_CHANGE_CB = isp_action_w(EXEC_TYPE, 4,
						ae_fps_status_cb),
	AE_EXEC_SET_DYN_VHDR_MODE = isp_action_w(EXEC_TYPE, 5, int),
	AE_EXEC_GET_MAX_DYN_REGION = isp_action_r(EXEC_TYPE, 6,
						enum rts_isp_ae_region),
	AE_EXEC_SET_MAX_DYN_REGION_ENABLE = isp_action_w(EXEC_TYPE, 7,
						uint8_t),
};

#endif /* _ISP_MOD_AE_H_INC_ */
