#ifndef _ISP_MOD_SENSOR_H_INC_
#define _ISP_MOD_SENSOR_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>
#include <rts_isp_ae.h>
#include <rts_isp_sensor.h>
#include <isp_utils.h>

#define ISP_SENSOR_MIN_EXP_DELAY 8

struct isp_sensor_mode {
	enum rts_isp_sensor_hdr_mode hdr;
	enum rts_isp_sensor_hdr_behavor mipi_behavor;
	struct {
		rts_isp_size_t snr;
		rts_isp_size_t isp;
	} size;
	float max_fps;
	float min_fps;

	uint32_t hts;
	uint32_t min_vts;
	uint32_t max_vts;
	uint32_t pclk;
	float exposure_step;
};

struct isp_sensor_i2c_msg {
	uint8_t i2c_id;
	uint8_t is_read;
	void *buf;
	uint16_t len;
};

struct isp_front_size {
	enum rts_isp_sensor_bit_depth bit_depth;
	rts_isp_size_t snr;
	rts_isp_size_t isp;
};

struct isp_sensor_timing {
	uint32_t pclk;
	uint32_t hts;
	uint32_t vts;
	uint32_t snr_width;
	uint32_t snr_height;
	uint32_t isp_width;
	uint32_t isp_height;
	float exposure_unit;
};


typedef int (*get_sync_regs_cb)(uint32_t isp_id, uint32_t delay,
				struct rts_isp_sync_reg *reg, int *num,
				const struct rts_isp_ae_exp_gain *exp_gain);

struct isp_sensor_exp_gain {
	const struct rts_isp_ae_exp_gain *exp_gain;
	float fps;

	int isp_sync_num;
	get_sync_regs_cb get_sync_regs_cb;
};

enum isp_mod_sensor_get_info_type {
	SENSOR_INFO_SIZE = isp_action_r(INFO_TYPE, 0, rts_isp_size_t),
	SENSOR_INFO_CROP = isp_action_r(INFO_TYPE, 1, rts_isp_rect_t),
	SENSOR_INFO_TIMING = isp_action_r(INFO_TYPE, 2,
					  struct isp_sensor_timing),
	SENSOR_INFO_INTERFACE = isp_action_r(INFO_TYPE, 3,
					const struct rts_isp_interface_info *),
	SENSOR_INFO_BOUND_SNR_NAME = isp_action_r(INFO_TYPE, 4, char[32]),
	SENSOR_INFO_VCM = isp_action_r(INFO_TYPE, 5,
					       struct rts_isp_focus_info),
	SENSOR_INFO_HDR_MODE = isp_action_r(INFO_TYPE, 6,
				       struct isp_sensor_mode),
	SENSOR_INFO_PATCH_OPS = isp_action_r(INFO_TYPE, 7, const void *),
	SENSOR_INFO_TUNE_OPS = isp_action_r(INFO_TYPE, 8,
				const struct rts_isp_exp_gain_tune_ops *),
	SENSOR_INFO_VERSION = isp_action_r(INFO_TYPE, 9, uint16_t),

};

enum isp_mod_sensor_execute_type {
	SENSOR_EXEC_SET_FPS = isp_action_w(EXEC_TYPE, 0, float),
	SENSOR_EXEC_SET_EXP_GAIN = isp_action_w(EXEC_TYPE, 1,
						struct isp_sensor_exp_gain),
	SENSOR_EXEC_READ_SEN_REG = isp_action_wr(EXEC_TYPE, 2,
						 struct rts_isp_i2c_reg),
	SENSOR_EXEC_WRITE_SEN_REG = isp_action_w(EXEC_TYPE, 3,
						 struct rts_isp_i2c_reg),
	SENSOR_EXEC_SET_DUMMY = isp_action_w(EXEC_TYPE, 4, uint32_t),
	SENSOR_EXEC_SET_FOCUS = isp_action_w(EXEC_TYPE, 5, uint32_t),
	SENSOR_EXEC_ENUM_MODES = isp_action_r(EXEC_TYPE, 6,
					      struct rts_isp_sensor_modes),
	SENSOR_EXEC_GET_MODE = isp_action_r(EXEC_TYPE, 7,
					    struct rts_isp_sensor_mode),
	SENSOR_EXEC_SET_MODE = isp_action_w(EXEC_TYPE, 8,
					    struct rts_isp_sensor_mode),
	SENSOR_EXEC_SET_GAIN = isp_action_wr(EXEC_TYPE, 9,								/* Sensor Temperature Control */
						 struct rts_isp_sensor_again),
	// SENSOR_EXEC_I2C_TRANSFER = isp_action_wr(EXEC_TYPE, 9,
	// 					 struct isp_sensor_i2c_msg),
	// SENSOR_EXEC_SET_MIRROR_FLIP = isp_action_wr(EXEC_TYPE, 10,
	// 					 struct rts_isp_sensor_mirror_flip),

};
int rts_isp_sensor_get_open_mode(void);
void rts_isp_sensor_set_open_mode(int val);
int rts_isp_sensor_get_close_mode(void);
void rts_isp_sensor_set_close_mode(int val);
int sensor_get_slave_addr_idx(void);

#endif /* _ISP_MOD_SENSOR_H_INC_ */
