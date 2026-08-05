#ifndef _RTS_ISP_TUNING_H_INC_
#define _RTS_ISP_TUNING_H_INC_

#include <stdint.h>
#include <rts_isp.h>
#include "hal_isp.h"
#ifdef __cplusplus
extern "C"
{
#endif

enum rts_isp_tuning_statis_type {
	RTS_ISP_TUNING_STATIS_ALL,
	RTS_ISP_TUNING_STATIS_RAW,
	RTS_ISP_TUNING_STATIS_AWB,
	RTS_ISP_TUNING_STATIS_AE,
	RTS_ISP_TUNING_STATIS_AF,
	RTS_ISP_TUNING_STATIS_FLICK,
	RTS_ISP_TUNING_STATIS_Y,
	__RTS_ISP_TUNING_STATIS_NUM,
};

struct rts_isp_tuning_statis {
	enum rts_isp_tuning_statis_type type;
	const void * const buf;
	const uint32_t len;
};

int rts_isp_tuning_query_statis(uint32_t isp_id,
				struct rts_isp_tuning_statis **statis);
int rts_isp_tuning_get_statis(uint32_t isp_id,
			      struct rts_isp_tuning_statis *statis);
void rts_isp_tuning_release_statis(uint32_t isp_id,
				   struct rts_isp_tuning_statis *statis);

enum rts_isp_tuning_param_type {
	RTS_ISP_TUNING_PARAM_ALL,
	RTS_ISP_TUNING_PARAM_AE,
	RTS_ISP_TUNING_PARAM_AWB,
	RTS_ISP_TUNING_PARAM_FLICK,
	RTS_ISP_TUNING_PARAM_WDR,
	RTS_ISP_TUNING_PARAM_MD,
	__RTS_ISP_TUNING_PARAM_NUM,
};

struct rts_isp_tuning_param {
	enum rts_isp_tuning_param_type type;
	uint8_t *buf;
	uint32_t len;
	const uint32_t max_len;
};

struct rts_isp_meta_param {

	float exposure_h;
	float gain_h;
	float exposure_l;
	float gain_l;
	uint32_t cur_y_target;
	float cur_dyn_fps;

	int wb_r_gain;
	int wb_b_gain;
	int wb_g_gain;
	int colot_temperature;

    uint32_t white_num;
    uint32_t rg_sum;
    uint32_t bg_sum;
	int y_average;
    uint32_t hist_contrast_origin;
    uint32_t hist_contrast;

	uint8_t ae_algo_dbg_buf[ISP_DEBUG_INFO_LEN];
};


int rts_isp_tuning_query_param(uint32_t isp_id,
			       struct rts_isp_tuning_param **param);
int rts_isp_tuning_get_param(uint32_t isp_id,
			     struct rts_isp_tuning_param *param);
int rts_isp_tuning_set_param(uint32_t isp_id,
			     struct rts_isp_tuning_param *param);
void rts_isp_tuning_release_param(uint32_t isp_id,
				  struct rts_isp_tuning_param *param);
enum rts_isp_tuning_iq_type {
	RTS_ISP_TUNING_IQ_TABLE_ALL,
	RTS_ISP_TUNING_IQ_TABLE_BLC,
	RTS_ISP_TUNING_IQ_TABLE_NLSC,
	RTS_ISP_TUNING_IQ_TABLE_MLSC,
	RTS_ISP_TUNING_IQ_TABLE_AE,
	RTS_ISP_TUNING_IQ_TABLE_AWB,
	RTS_ISP_TUNING_IQ_TABLE_AF,
	RTS_ISP_TUNING_IQ_TABLE_CCM,
	RTS_ISP_TUNING_IQ_TABLE_GAMMA,
	RTS_ISP_TUNING_IQ_TABLE_WDR,
	RTS_ISP_TUNING_IQ_TABLE_YGC,
	RTS_ISP_TUNING_IQ_TABLE_UVTUNE,
	RTS_ISP_TUNING_IQ_TABLE_SPE,
	RTS_ISP_TUNING_IQ_TABLE_TEXTURE,
	RTS_ISP_TUNING_IQ_TABLE_DAYNIGHT,
	RTS_ISP_TUNING_IQ_TABLE_HIGH_TEMP,
	RTS_ISP_TUNING_IQ_TABLE_TM,
	RTS_ISP_TUNING_IQ_TABLE_MD,
	__RTS_ISP_TUNING_IQ_TABLE_NUM
};

struct rts_isp_tuning_iq {
	enum rts_isp_tuning_iq_type type;
	void *buf;
	uint32_t len;
	const uint32_t max_len;
};

struct rts_isp_tuning_reg {
	uint32_t offset;
	uint32_t value;
	uint32_t mask; /* 0 means no mask */
};

int rts_isp_tuning_query_iq(uint32_t isp_id,
			    struct rts_isp_tuning_iq **iq);
int rts_isp_tuning_get_iq(uint32_t isp_id,
			  struct rts_isp_tuning_iq *iq);
int rts_isp_tuning_set_iq(uint32_t isp_id,
			  struct rts_isp_tuning_iq *iq);
void rts_isp_tuning_release_iq(uint32_t isp_id,
			       struct rts_isp_tuning_iq *iq);
int rts_isp_tuning_read_regs(uint32_t isp_id,
			     struct rts_isp_tuning_reg *regs, uint32_t num);
int rts_isp_tuning_write_regs(uint32_t isp_id,
			      struct rts_isp_tuning_reg *regs, uint32_t num);
const char *rts_isp_tuning_packed_iq_path(uint32_t isp_id);
int rts_isp_tuning_reload_packed_iq(uint32_t isp_id);
int rts_isp_get_meta_param(uint32_t isp_id, struct rts_isp_meta_param *m_param);
#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_TUNING_H_INC_ */
