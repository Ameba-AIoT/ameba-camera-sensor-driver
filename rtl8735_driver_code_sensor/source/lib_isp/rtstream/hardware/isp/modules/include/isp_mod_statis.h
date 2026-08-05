#ifndef _ISP_MOD_STATIS_H_INC_
#define _ISP_MOD_STATIS_H_INC_

#include <rts_isp_tuning.h>
#include <isp_utils.h>
#include <isp_statis.h>

extern char AE_STATIS_SHM_NAME[];
extern char AWB_STATIS_SHM_NAME[];
extern char AF_STATIS_SHM_NAME[];
extern char TUNING_STATIS_SHM_NAME[];

#define TUNING_STATIS_SHM_SIZE (32 * 1024)

enum isp_mod_statis_get_info_type {
	STATIS_INFO_BUF_OFFSET = isp_action_r(INFO_TYPE, 0,
					      struct isp_statis_buf_offset),
	STATIS_INFO_AE_STAT = isp_action_wr(INFO_TYPE, 1,
					    struct rts_isp_ae_statis),
	STATIS_INFO_AWB_STAT = isp_action_wr(INFO_TYPE, 2,
					     struct rts_isp_awb_statis),
	STATIS_INFO_AF_STAT = isp_action_wr(INFO_TYPE, 3,
					    struct rts_isp_af_statis),
	STATIS_INFO_TUNING_STAT = isp_action_wr(INFO_TYPE, 4,
						struct rts_isp_tuning_statis),
};

#endif /* _ISP_MOD_STATIS_H_INC_ */

