#ifndef _RTS_ISP_H_INC_
#define _RTS_ISP_H_INC_

#include <stdint.h>
#include <linux/videodev2.h>
#include <rtsavisp.h>
#include <rts_isp_sensor.h>
#include <rts_isp_ae.h>
#include <rts_isp_awb.h>
#include <rts_isp_af.h>

#ifdef __cplusplus
extern "C"
{
#endif

int rts_isp_v4l2_query_ctrl(uint32_t isp_id, struct v4l2_queryctrl *qc);
int rts_isp_v4l2_query_menu(uint32_t isp_id, struct v4l2_querymenu *qm);
int rts_isp_v4l2_g_ctrl(uint32_t isp_id, struct v4l2_control *control);
int rts_isp_v4l2_s_ctrl(uint32_t isp_id, struct v4l2_control *control);
int rts_isp_v4l2_query_ext_ctrl(uint32_t isp_id,
				struct v4l2_query_ext_ctrl *qec);
int rts_isp_v4l2_g_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ec);
int rts_isp_v4l2_s_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ec);
int rts_isp_v4l2_try_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ec);

#define RTS_V4L2_CID_BASE (V4L2_CID_USER_BASE | 0xf000)
#define RTS_V4L2_CID_GREEN_BALANCE (RTS_V4L2_CID_BASE + 0)
#define RTS_V4L2_CID_IQ_TABLE (RTS_V4L2_CID_BASE + 1)
#define RTS_V4L2_CID_DAY_NIGHT (RTS_V4L2_CID_BASE + 2)
enum rts_isp_day_night {
	RTS_ISP_DAY,
	RTS_ISP_NIGHT,
	RTS_ISP_DN_OTHER
};
#define RTS_V4L2_CID_DYNAMIC_FPS (RTS_V4L2_CID_BASE + 3)
#define RTS_V4L2_CID_DYNAMIC_IQ (RTS_V4L2_CID_BASE + 4)
#define RTS_V4L2_CID_TEMPORAL_DENOISE (RTS_V4L2_CID_BASE + 5)
#define RTS_V4L2_CID_DEHAZE (RTS_V4L2_CID_BASE + 6)
#define RTS_V4L2_CID_DEHAZE_LEVEL (RTS_V4L2_CID_BASE + 7)
#define RTS_V4L2_CID_LDC (RTS_V4L2_CID_BASE + 8)
#define RTS_V4L2_CID_GRAY (RTS_V4L2_CID_BASE + 9)
#define RTS_V4L2_CID_AUTO_CCM (RTS_V4L2_CID_BASE + 10)
#define RTS_V4L2_CID_CCM_MATRIX (RTS_V4L2_CID_BASE + 11)
#define RTS_V4L2_CID_WDR_MODE (RTS_V4L2_CID_BASE + 12)
enum rts_isp_wdr_mode {
	RTS_ISP_WDR_INNER_DISABLE,
	RTS_ISP_WDR_INNER_MANUAL,
	RTS_ISP_WDR_INNER_AUTO,
	RTS_ISP_WDR_INNER_DIRECT,
};
#define RTS_V4L2_CID_WDR_LEVEL (RTS_V4L2_CID_BASE + 13)
#define RTS_V4L2_CID_AUTO_GAMMA (RTS_V4L2_CID_BASE + 14)
#define RTS_V4L2_CID_GAMMA_CURVE (RTS_V4L2_CID_BASE + 15)
#define RTS_V4L2_CID_AUTO_YGAMMA (RTS_V4L2_CID_BASE + 16)
#define RTS_V4L2_CID_YGAMMA_CURVE (RTS_V4L2_CID_BASE + 17)
#define RTS_V4L2_CID_OUTPUT_POSITION (RTS_V4L2_CID_BASE + 18)
#define RTS_V4L2_CID_COLOR_RANGE (RTS_V4L2_CID_BASE + 19)
enum rts_isp_color_range {
	RTS_ISP_COLOR_RANGE_BT601_STUDIO_SWING,
	RTS_ISP_COLOR_RANGE_BT601_FULL_SWING,
	RTS_ISP_COLOR_RANGE_BT709_STUDIO_SWING,
	RTS_ISP_COLOR_RANGE_BT709_FULL_SWING,
};
#define RTS_V4L2_CID_NR_LEVEL (RTS_V4L2_CID_BASE + 20)
#define RTS_V4L2_CID_DE_LEVEL (RTS_V4L2_CID_BASE + 21)
#define RTS_V4L2_CID_SNR_CROP_X (RTS_V4L2_CID_BASE + 22)
#define RTS_V4L2_CID_SNR_CROP_Y (RTS_V4L2_CID_BASE + 23)
#define RTS_V4L2_CID_Y_GAIN (RTS_V4L2_CID_BASE + 24)
#define RTS_V4L2_CID_SMART_IR_MODE (RTS_V4L2_CID_BASE + 25)
#define RTS_V4L2_CID_SMART_IR_MANUAL_LEVEL (RTS_V4L2_CID_BASE + 26)
#define RTS_V4L2_CID_DAYNIGHT_DETECTION (RTS_V4L2_CID_BASE + 27)
//
//int rts_isp_read_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);
//int rts_isp_write_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);
#define RTS_V4L2_CID_OUTPUT_CHANNEL (RTS_V4L2_CID_BASE + 28)
#define RTS_V4L2_CID_AUTO_HDR_RATIO (RTS_V4L2_CID_BASE + 30)
#define RTS_V4L2_CID_HDR_RATIO (RTS_V4L2_CID_BASE + 31)
#define RTS_V4L2_CID_SENSOR_MIRROR_FLIP (RTS_V4L2_CID_BASE + 32)
#define RTS_V4L2_CID_AE_MIN_FPS (RTS_V4L2_CID_BASE + 33)
#define RTS_V4L2_CID_AE_MAX_FPS (RTS_V4L2_CID_BASE + 34)
#define RTS_V4L2_CID_SENSOR_SHORT_EXP_THD (RTS_V4L2_CID_BASE + 35)
#define RTS_V4L2_CID_DYNAMIC_IQ_MODE (RTS_V4L2_CID_BASE + 36)
#define RTS_V4L2_CID_SENSOR_ISP_GAIN (RTS_V4L2_CID_BASE + 37)
#define RTS_V4L2_CID_DRC_MODE (RTS_V4L2_CID_BASE + 38)
#define RTS_V4L2_CID_DRC_BLENDING_RATE (RTS_V4L2_CID_BASE + 39)
#define RTS_V4L2_CID_SENSOR_ISP_GAIN_MODE (RTS_V4L2_CID_BASE + 40)

enum rts_isp_sensor_isp_gain_mode {
	RTS_ISP_SENSOR_ISP_GAIN_MODE_AUTO,
	RTS_ISP_SENSOR_ISP_GAIN_MODE_MANUAL,
};

enum rts_isp_dynamic_iq_mode {
	RTS_ISP_DYNAMIC_IQ_MODE_STEPPING,
	RTS_ISP_DYNAMIC_IQ_MODE_ONE_SHOT
};

enum rts_isp_drc_mode {
	RTS_ISP_DRC_MODE_AUTO,
	RTS_ISP_DRC_MODE_MANUAL,
};

struct rts_isp_mask_entry {
	const enum rts_isp_geom_type type;

	int enable;
	union {
		struct {
			const uint32_t max_cols;
			const uint32_t max_rows;
			rts_isp_grid_t grid;
			uint8_t *bitmap;
		};
		rts_isp_prect_t rect;
	};
};

struct rts_isp_mask {
	uint32_t color; /* rgb888 */
	const int number;
	struct rts_isp_mask_entry *entries;
};

int rts_isp_query_mask(uint32_t isp_id, struct rts_isp_mask **mask);
int rts_isp_get_mask(uint32_t isp_id, struct rts_isp_mask *mask);
int rts_isp_set_mask(uint32_t isp_id, struct rts_isp_mask *mask);
void rts_isp_release_mask(uint32_t isp_id, struct rts_isp_mask *mask);

enum rts_isp_ae_mode {
	RTS_ISP_AE_MANUAL_MODE,
	RTS_ISP_AE_AUTO_MODE,
};

struct rts_isp_ae_auto_setting {
	const uint32_t window_num;
	uint8_t * const win_weights;
	int target_delta;
	uint16_t gain_max;
	float min_fps;
	float max_exposure;
};

struct rts_isp_ae_manual_setting {
	uint32_t exposure_time;
	uint16_t total_gain;
	struct {
		uint16_t analog_gain;
		uint16_t digital_gain;
		uint16_t isp_gain;
	} gain;
};

struct rts_isp_ae_setting {
	enum rts_isp_ae_mode mode;
	struct rts_isp_ae_auto_setting _auto;
	struct rts_isp_ae_manual_setting _manual;
	uint8_t *alloc_win_weights;

};

int rts_isp_query_ae_setting(uint32_t isp_id,
			     struct rts_isp_ae_setting **ae_setting);
int rts_isp_get_ae_setting(uint32_t isp_id,
			   struct rts_isp_ae_setting *ae_setting);
int rts_isp_set_ae_setting(uint32_t isp_id,
			   struct rts_isp_ae_setting *ae_setting);
void rts_isp_release_ae_setting(uint32_t isp_id,
				struct rts_isp_ae_setting *ae_setting);

int rts_isp_get_ae_statis_info(uint32_t isp_id,
			       struct rts_isp_ae_stat_info *info);
int rts_isp_query_ae_statis(uint32_t isp_id,
			    const struct rts_isp_ae_statis **ae_statis);
int rts_isp_get_ae_statis(uint32_t isp_id,
			  const struct rts_isp_ae_statis *ae_statis);
int rts_isp_put_ae_statis(uint32_t isp_id,
			  const struct rts_isp_ae_statis *ae_statis);
void rts_isp_release_ae_statis(uint32_t isp_id,
			       const struct rts_isp_ae_statis *ae_statis);

typedef void (*ae_fps_status_cb)(float);
int rts_isp_register_ae_fps_change_cb(uint32_t isp_id, ae_fps_status_cb cb);
int rts_isp_get_max_dyn_region(uint32_t isp_id, enum rts_isp_ae_region *region);
int rts_isp_set_max_dyn_region_en(uint32_t isp_id, uint8_t max_dyn_region_en);

enum rts_isp_awb_mode {
	RTS_ISP_AWB_TEMPERATURE_MODE,
	RTS_ISP_AWB_AUTO_MODE,
	RTS_ISP_AWB_COMPONENT_MODE,
};

struct rts_isp_awb_setting {
	enum rts_isp_awb_mode mode;

	struct {
		uint32_t temperature;
	} _temperature;

	struct {
		uint16_t r_gain_adj;
		uint16_t b_gain_adj;
	} _auto;

	struct {
		uint16_t r_gain;
		uint16_t g_gain;
		uint16_t b_gain;
	} _component;
};

int rts_isp_query_awb_setting(uint32_t isp_id,
			      struct rts_isp_awb_setting **awb_setting);
int rts_isp_get_awb_setting(uint32_t isp_id,
			    struct rts_isp_awb_setting *awb_setting);
int rts_isp_set_awb_setting(uint32_t isp_id,
			    struct rts_isp_awb_setting *awb_setting);
void rts_isp_release_awb_setting(uint32_t isp_id,
				 struct rts_isp_awb_setting *awb_setting);

int rts_isp_get_awb_statis_info(uint32_t isp_id,
				struct rts_isp_awb_stat_info *info);
int rts_isp_query_awb_statis(uint32_t isp_id,
			     const struct rts_isp_awb_statis **statis);
int rts_isp_get_awb_statis(uint32_t isp_id,
			   const struct rts_isp_awb_statis *statis);
int rts_isp_put_awb_statis(uint32_t isp_id,
			   const struct rts_isp_awb_statis *statis);
void rts_isp_release_awb_statis(uint32_t isp_id,
				const struct rts_isp_awb_statis *statis);

int rts_isp_get_af_statis_info(uint32_t isp_id,
			       struct rts_isp_af_stat_info *info);
int rts_isp_query_af_statis(uint32_t isp_id,
			    const struct rts_isp_af_statis **af_statis);
int rts_isp_get_af_statis(uint32_t isp_id,
			  const struct rts_isp_af_statis *af_statis);
int rts_isp_put_af_statis(uint32_t isp_id,
			  const struct rts_isp_af_statis *af_statis);
void rts_isp_release_af_statis(uint32_t isp_id,
			       const struct rts_isp_af_statis *af_statis);

struct rts_isp_image_size {
	enum rts_isp_sensor_bit_depth sensor_bit_depth;
	rts_isp_size_t sensor_size;
	rts_isp_size_t isp_middle_size;
	rts_isp_size_t isp_final_size;
};

int rts_isp_get_image_size(uint32_t isp_id, struct rts_isp_image_size *size);

struct rts_isp_bypass {
	union {
		uint32_t all;
		struct {
			uint32_t bypass_blc_longexp:1;
			uint32_t bypass_blc_shortexp:1;
			uint32_t bypass_dpc_longexp:1;
			uint32_t bypass_dpc_snr_shortexp:1;
			uint32_t bypass_tnr_longexp:1;
			uint32_t bypass_vhdr:1;
			uint32_t bypass_nlsc:1;
			uint32_t bypass_mlsc:1;
			uint32_t bypass_awb:1;
			uint32_t bypass_ae:1;
			uint32_t bypass_ccm:1;
			uint32_t bypass_gamma:1;
			uint32_t bypass_dehaze:1;
			uint32_t bypass_wdr:1;
			uint32_t bypass_ygc:1;
			uint32_t bypass_uvtune:1;
			uint32_t bypass_ldc:1;
			uint32_t bypass_eeh:1;
			uint32_t bypass_spe:1;
			uint32_t bypass_ygamma:1;
		};
	};
};

int rts_isp_get_bypass(uint32_t isp_id, struct rts_isp_bypass *bypass);
int rts_isp_set_bypass(uint32_t isp_id, struct rts_isp_bypass *bypass);

int rts_isp_get_dir_wdr_level(uint32_t isp_id, uint8_t *level);
int rts_isp_set_dir_wdr_level(uint32_t isp_id, uint8_t *level);

const char *rts_isp_get_bound_sensor_name(uint32_t isp_id);

int rts_isp_set_statis_irq_en(uint32_t isp_id, uint32_t en);

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_H_INC_ */
