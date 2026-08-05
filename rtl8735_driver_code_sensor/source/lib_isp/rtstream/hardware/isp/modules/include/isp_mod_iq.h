#ifndef _ISP_MOD_IQ_H_INC_
#define _ISP_MOD_IQ_H_INC_

#include <rtsavisp.h>
#include <rts_isp_tuning.h>
#include <isp_utils.h>
#include <isp_notify.h>
#include <rts_isp_tuning.h>
#include <isp_algo_param.pb.h>


#define TUNING_PARAM_SHM_SIZE 256
#define TUNING_IQ_TABLE_SHM_SIZE (32 * 1024)
extern char TUNING_PARAM_SHM_NAME[];
extern char TUNING_IQ_TABLE_SHM_NAME[];

struct isp_packed_iq_info {
	void *bfr;
};

enum isp_mod_iq_get_info_type {
	IQ_INFO_DYNAMIC = isp_action_r(INFO_TYPE, 0,
				       const struct isp_notify_dynamic *),
	IQ_INFO_IQ_SEL = isp_action_r(INFO_TYPE, 1, int),
	IQ_INFO_PACKED_IQ = isp_action_r(INFO_TYPE, 2,
					 struct isp_packed_iq_info),
	IQ_INFO_PLUGINS_VERSION = isp_action_r(INFO_TYPE, 3,
					       struct rts_isp_plugins_version),
};

struct isp_iq_tuning_regs {
	struct rts_isp_tuning_reg *regs;
	int num;
};

enum isp_mod_iq_execute_type {
	IQ_EXEC_SET_DYNAMIC_AE = isp_action_w(EXEC_TYPE, 0,
					      struct isp_notify_dynamic_ae),
	IQ_EXEC_SET_DYNAMIC_AWB = isp_action_w(EXEC_TYPE, 1,
					       struct isp_notify_dynamic_awb),
	IQ_EXEC_SET_DYNAMIC_MD = isp_action_w(EXEC_TYPE, 2,
					       struct isp_notify_dynamic_md),
	IQ_EXEC_BIND_ALGO = isp_action_w(EXEC_TYPE, 3, int),
	IQ_EXEC_UNBIND_ALGO = isp_action_w(EXEC_TYPE, 4, int),
	IQ_EXEC_GET_ALGO_PARAM = isp_action_wr(EXEC_TYPE, 5,
					       struct rts_isp_tuning_param),
	IQ_EXEC_SET_ALGO_PARAM = isp_action_w(EXEC_TYPE, 6,
					      struct rts_isp_tuning_param),
	IQ_EXEC_GET_IQ_TABLE = isp_action_wr(EXEC_TYPE, 7,
					    struct rts_isp_tuning_iq),
	IQ_EXEC_SET_IQ_TABLE = isp_action_w(EXEC_TYPE, 8,
					    struct rts_isp_tuning_iq),
	IQ_EXEC_SET_DYNAMIC_SENSOR = isp_action_w(EXEC_TYPE, 9,
					struct isp_notify_dynamic_sensor),
	IQ_EXEC_READ_REGS = isp_action_wr(EXEC_TYPE, 10,
					  struct isp_iq_tuning_regs),
	IQ_EXEC_WRITE_REGS = isp_action_w(EXEC_TYPE, 11,
					  struct isp_iq_tuning_regs),
	IQ_EXEC_RELOAD_PACKED_IQ = isp_action(EXEC_TYPE, 12),
	IQ_EXEC_GET_META_PARAM = isp_action_wr(EXEC_TYPE, 13,
					       struct rts_isp_meta_param),
};

#endif /* _ISP_MOD_IQ_H_INC_ */
