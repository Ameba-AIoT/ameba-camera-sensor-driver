#ifndef _RTS_ISP_MD_H_INC_
#define _RTS_ISP_MD_H_INC_

#include <stdint.h>
#include <rts_isp_define.h>
#include <rts_isp_errno.h>
#include <rts_isp_ae.h>
#include <rts_isp_awb.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MD_API_VERSION_MAGIC ((uint32_t)'m' << 8 | (uint32_t)'d')
#define MD_API_MAJOR_VERSION 1
#define MD_API_MINOR_VERSION 0
#define MD_API_VERSION                                                         \
	(MD_API_VERSION_MAGIC << 16 | MD_API_MAJOR_VERSION << 8 |              \
	 MD_API_MINOR_VERSION)
#define MD_VERSION_MASK ((1 << 16) - 1)

enum rts_isp_md_ctrls {
	SET_WIN_NUM,
	SET_NOISE_THD,
	SET_DECAY_RATIO,
	SET_ENABLE_MD_AE,
	SET_ENABLE_MD_AWB,
	SET_RATIO
};

enum rts_isp_md_enable {
	MD_DISABLE_ALL,
	MD_ENABLE_AE,
	MD_ENABLE_AWB,
	MD_ENABLE_ALL
};

enum rts_isp_md_type { MD_AE, MD_R, MD_G, MD_B, MD_MAX_TYPE };

struct rts_isp_md_algo_statis {
	const struct rts_isp_ae_statis *ae_statis;
	const struct rts_isp_awb_statis *awb_statis;
	uint8_t resv[8];
};

struct rts_isp_algo_md_win_num_info {
	uint16_t ae_win_num;
	uint16_t awb_win_num;
};

struct rts_isp_algo_md_noise_thd_info {
	uint16_t noise_thd[MD_MAX_TYPE];
};

struct rts_isp_algo_md_result {
	uint16_t md_val;
};

struct rts_isp_algo_md_init_info {
	struct rts_isp_algo_md_win_num_info win_num_info;
	const void *iq; /* only used for internal*/
	void *algo_param; /* only used for internal*/
	uint8_t resv[8];
};

struct rts_isp_md_algo {
	uint32_t api_version;
	int (*init)(uint32_t isp_id,
		    const struct rts_isp_algo_md_init_info *info);
	int (*run)(uint32_t isp_id, const struct rts_isp_md_algo_statis *statis,
		   struct rts_isp_algo_md_result *result);
	int (*ctrl)(uint32_t isp_id, enum rts_isp_md_ctrls id, void *data);
	int (*cleanup)(uint32_t isp_id);
};

const struct rts_isp_md_algo *rts_isp_get_md_algo(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_MD_H_INC_ */
