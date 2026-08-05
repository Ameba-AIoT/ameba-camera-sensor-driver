#ifndef _RTS_ISP_AE_H_INC_
#define _RTS_ISP_AE_H_INC_

#include <stdint.h>
#include <rts_isp_define.h>
#include <rts_isp_errno.h>
#include <rts_isp_geom.h>
#include <rts_isp_sensor.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define AE_API_VERSION_MAGIC ((uint32_t)'a' << 8 | (uint32_t)'e')
#define AE_API_MAJOR_VERSION 2
#define AE_API_MINOR_VERSION 0
#define AE_API_VERSION (AE_API_VERSION_MAGIC << 16 | \
			AE_API_MAJOR_VERSION << 8 | AE_API_MINOR_VERSION)
#define AE_VERSION_MASK ((1 << 16) - 1)

enum rts_isp_power_line_freq {
	POWER_LINE_NONE,
	POWER_LINE_50HZ,
	POWER_LINE_60HZ,
};

enum rts_isp_ae_dyn_hdr_mode {
	AE_DYN_HDR_OFF, /* only use long frame on sensor hdr mode */
	AE_DYN_HDR_ON, /* use long and short frame on sensor hdr mode */
	AE_DYN_HDR_AUTO, /* let ae algo to determin on or off */
};

enum rts_isp_ae_sort_mode {
	SORT_DISABLE,
	SORT_AUTO,
	SORT_BRIGHT,
	SORT_DARK,
	SORT_MANUAL
};

enum rts_isp_ae_region {
	UPPER_LEFT,
	UPPER_RIGHT,
	LOWER_LEFT,
	LOWER_RIGHT,
};

struct rts_isp_ae_exp_gain {
	enum rts_isp_sensor_hdr_mode hdr;
	float exposure[RTS_ISP_HDR_CHAN_MAX]; /* us */
	float analog_gain[RTS_ISP_HDR_CHAN_MAX];
	float digital_gain[RTS_ISP_HDR_CHAN_MAX];
	float isp_hdr_gain[RTS_ISP_HDR_CHAN_MAX];
	float isp_gain;
};

struct rts_isp_ae_ratio_range {
	int min_ratio;
	int max_ratio;
};

struct rts_isp_ae_hdr_stat_info {
	rts_isp_grid_size_t win;
	uint16_t hist_bins;
};

struct rts_isp_ae_stat_info {
	rts_isp_grid_size_t win;
	uint16_t hist_bins;
	struct rts_isp_ae_hdr_stat_info hdr[RTS_ISP_HDR_CHAN_MAX];
};

struct rts_isp_exp_gain_tune_ops {
	int (*get_exposure_range)(int32_t isp_id, float fps,
				  float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				  float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				  float max_exposure[RTS_ISP_HDR_CHAN_MAX]);
	int (*get_tuned_again)(uint32_t isp_id,
			       float again[RTS_ISP_HDR_CHAN_MAX]);
	int (*get_tuned_dgain)(uint32_t isp_id,
			       float dgain[RTS_ISP_HDR_CHAN_MAX]);
};

struct rts_isp_ae_info {
	struct rts_isp_ae_stat_info stat_info;
	const struct rts_isp_exp_gain_tune_ops *tune;
	const void *iq; /* only used for internal*/
	void *algo_param; /* only used for internal*/
	uint8_t resv[8];
};

struct rts_isp_ae_hdr_statis {
	const uint16_t *y_mean;
	const uint32_t *hist;
};

struct rts_isp_ae_statis {
	uint32_t frame_count;
	const uint16_t *y_mean;
	const uint32_t *hist;
	struct rts_isp_ae_hdr_statis hdr[RTS_ISP_HDR_CHAN_MAX];
	uint8_t resv[8];
};

struct rts_isp_ae_result {
	uint32_t need_update;
	struct rts_isp_ae_exp_gain exp_gain;
	float dyn_fps;
	uint8_t resv[8];
};

enum rts_isp_ae_ctrls {
	/* base information */
	SET_SENSOR_BASE_FPS = 0, /* const float */
	SET_EXP_GAIN, /* const struct rts_isp_ae_exp_gain */
	SET_EXPOSURE_UNIT, /* const float (us) */

	/* v4l2 ctrl information */
	SET_POWER_LINE_FREQ = 100, /* const enum rts_isp_power_line_freq */
	SET_DYNAMIC_FPS_ENABLE, /* const int */
	SET_DYNAMIC_HDR_MODE, /* cont enum rts_isp_ae_dyn_hdr_mode */
	SET_HDR_RATIO_RANGE, /* const struct rts_isp_ae_ratio_range */
	SET_HDR_RATIO, /* const int, 0 for auto */
	SET_SORT_MODE, /* const enum rts_ae_sort_mode */
	SET_SORT_MANUAL_LEVEL, /* const int */
	SET_MIN_FPS,
	SET_MAX_FPS,

	/* ae api information */
	SET_WIN_WEIGHTS = 200, /* const uint8_t[win_num] */
	SET_TARGET_DELTA, /* const int */
	SET_GAIN_MAX, /* const float */
	SET_SENSOR_MIN_FPS, /* const float */
	SET_MAX_DYN_REGION_ENABLE, /* const uint8_t */
	SET_AE_DBG_BUF,
};

struct rts_ae_dbg_buf {
	void *buf_ptr;
	size_t buf_len;
};

struct rts_isp_ae_algo {
	uint32_t api_version;
	int (*init)(uint32_t isp_id, const struct rts_isp_ae_info *info);
	int (*run)(uint32_t isp_id, const struct rts_isp_ae_statis *statis,
		   struct rts_isp_ae_result *result);
	int (*ctrl)(uint32_t isp_id, enum rts_isp_ae_ctrls id, void *data);
	int (*cleanup)(uint32_t isp_id);
};

const struct rts_isp_ae_algo *rts_isp_get_ae_algo(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_AE_H_INC_ */
