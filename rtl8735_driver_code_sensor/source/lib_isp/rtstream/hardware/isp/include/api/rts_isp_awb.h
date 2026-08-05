#ifndef _RTS_ISP_AWB_H_INC_
#define _RTS_ISP_AWB_H_INC_

#include <stdint.h>
#include <rts_isp_errno.h>
#include <rts_isp_geom.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define AWB_API_VERSION_MAGIC ((uint32_t)'w' << 8 | (uint32_t)'b')
#define AWB_API_MAJOR_VERSION 1
#define AWB_API_MINOR_VERSION 0
#define AWB_API_VERSION (AWB_API_VERSION_MAGIC << 16 | \
			 AWB_API_MAJOR_VERSION << 8 | AWB_API_MINOR_VERSION)
#define AWB_VERSION_MASK ((1 << 16) - 1)

struct rts_isp_awb_stat_info {
	rts_isp_grid_size_t win;
	uint16_t pixels_per_cell;
	uint32_t fine_pixels;
};

struct rts_isp_awb_info {
	struct rts_isp_awb_stat_info stat_info;
	const void *iq; /* only used for internal*/
	void *algo_param; /* only used for internal*/
	uint8_t resv[8];
};

struct rts_isp_awb_statis {
	uint32_t frame_count;
	const uint16_t *r_mean; /* 12.0 bit precision */
	const uint16_t *g_mean; /* 12.0 bit precision */
	const uint16_t *b_mean; /* 12.0 bit precision */
	const uint16_t *y_mean; /* 12.0 bit precision */
	const uint16_t *rg; /* 3.8 bit precision */
	const uint16_t *bg; /* 3.8 bit precision */
	const uint16_t *pixels;
	uint32_t illum_white_pixels[6];
	uint32_t fine_r_sum;
	uint32_t fine_g_sum;
	uint32_t fine_b_sum;
	uint32_t fine_white_pixels;
	uint8_t resv[8];
};

struct rts_isp_awb_gain {
	uint16_t r_gain; /* 3.8 bit precision */
	uint16_t gr_gain; /* 3.8 bit precision */
	uint16_t gb_gain; /* 3.8 bit precision */
	uint16_t b_gain; /* 3.8 bit precision */
};

struct rts_isp_awb_gain_result {
	uint32_t need_update;
	uint32_t color_temperature;
	struct rts_isp_awb_gain gain;
};

struct rts_isp_awb_rough_gain {
	uint32_t need_update;
	uint16_t r_gain; /* 3.8 bit precision */
	uint16_t b_gain; /* 3.8 bit precision */
};

struct rts_isp_awb_rough_limit {
	uint32_t need_update;
	uint16_t y_min; /* 12.0 bit precision */
	uint16_t y_max; /* 12.0 bit precision */
	uint16_t r_min; /* 12.0 bit precision */
	uint16_t r_max; /* 12.0 bit precision */
	uint16_t g_min; /* 12.0 bit precision */
	uint16_t g_max; /* 12.0 bit precision */
	uint16_t b_min; /* 12.0 bit precision */
	uint16_t b_max; /* 12.0 bit precision */
	uint16_t rg_min;  /* 3.8 bit precision */
	uint16_t rg_max;  /* 3.8 bit precision */
	uint16_t bg_min;  /* 3.8 bit precision */
	uint16_t bg_max;  /* 3.8 bit precision */
};

struct rts_isp_awb_fine_limit {
	uint32_t need_update;
	uint16_t y_min; /* 12.0 bit precision */
	uint16_t y_max; /* 12.0 bit precision */
	uint16_t rg_min;  /* 3.8 bit precision */
	uint16_t rg_max;  /* 3.8 bit precision */
	uint16_t bg_min;  /* 3.8 bit precision */
	uint16_t bg_max;  /* 3.8 bit precision */
};

struct rts_isp_awb_illums {
	uint32_t need_update;
	uint16_t r_gain[6]; /* 3.8 bit precision */
	uint16_t b_gain[6]; /* 3.8 bit precision */
	uint16_t rg_min; /* 3.8 bit precision */
	uint16_t rg_max; /* 3.8 bit precision */
	uint16_t bg_min; /* 3.8 bit precision */
	uint16_t bg_max; /* 3.8 bit precision */
	uint16_t y_min; /* 12.0 bit precision */
	uint16_t y_max; /* 12.0 bit precision */
};

struct rts_isp_awb_stat_config {
	struct rts_isp_awb_rough_gain rough_gain;
	struct rts_isp_awb_rough_limit rough_limit;
	struct rts_isp_awb_fine_limit fine_limit;
	struct rts_isp_awb_illums illums;
};

struct rts_isp_awb_result {
	struct rts_isp_awb_gain_result result;
	struct rts_isp_awb_stat_config config;
	uint8_t resv[8];
};

struct rts_isp_awb_rb_gain_adj {
	uint16_t r_gain_adj;
	uint16_t b_gain_adj;
};

enum rts_isp_awb_ctrls {
	COLOR_TEMP_TO_GAIN, /* struct rts_isp_awb_gain_result */
	GAIN_TO_COLOR_TEMP, /* struct rts_isp_awb_gain_result */
	SET_GAIN_ADJ, /* const struct rts_isp_awb_rb_gain_adj */
};

struct rts_isp_awb_algo {
	uint32_t api_version;
	int (*init)(uint32_t isp_id, const struct rts_isp_awb_info *info,
		   struct rts_isp_awb_result *result);
	int (*run)(uint32_t isp_id, const struct rts_isp_awb_statis *statis,
		   struct rts_isp_awb_result *result);
	int (*ctrl)(uint32_t isp_id, enum rts_isp_awb_ctrls id, void *data);
	int (*cleanup)(uint32_t isp_id);
};

const struct rts_isp_awb_algo *rts_isp_get_awb_algo(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_AWB_H_INC_ */
