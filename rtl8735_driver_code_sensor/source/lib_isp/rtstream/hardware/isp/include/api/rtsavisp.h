#ifndef _RTSAVISP_H_INC_
#define _RTSAVISP_H_INC_

#include <stdint.h>
#include <rts_isp_errno.h>
#include <rts_isp_sensor.h>

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @file rtsavisp.h
 * @brief Strucure and API fot ISP of RTS3915
 */

/**
 * @defgroup isp ISP of RTS3915
 * @brief Structure and API for setting of RTS3915 ISP.
 * ISP must be configured before ISP video stream.
 * @ingroup total
 * @{
 */
#define RTS_ISP_NAME_LEN 32
#define RTS_ISP_PATH_LEN 256

/**
 * @brief ISP ID
 */
enum isp_id {
	ISP0, /**< the first ISP.Only one ISP is supported temporarily. */
	_ISP_ID_NUM,
};

/**
 * @brief Init ISP.
 * @attention This API must be called before any ISP API.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_init(uint8_t fcs_ready, uint32_t hdr_mode, uint32_t mirflp_mode, uint8_t tnr_en);
/**
 * @brief Cleanup ISP.
 * @attention After calling \ref rts_av_isp_init, this API must be called to release.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_cleanup(void);
/**
 * @brief Start ISP preview loop.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_start(void);
/**
 * @brief Stop ISP preview loop.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_stop(void);

/**
 * @brief ISP status
 */
enum rts_isp_status {
	RTS_ISP_UNINITIALIZED, /**< ISP uninitialized */
	RTS_ISP_STOPPED, /**< ISP preview loop stopped */
	RTS_ISP_RUNNING, /**< ISP preview loop is running but not previewing */
	RTS_ISP_STREAMING, /**< ISP preview loop is streaming */
};

/**
 * @brief Get ISP loop status.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @return minus : fail, others : ISP status, see detail in \ref rts_isp_status
 */
enum rts_isp_status rts_av_isp_get_status(void);

/**
 * @brief Type of ISP algorithm.
 */
enum rts_isp_algo_type {
	RTS_ISP_ALGO_AE, /**< AE algorithm */
	RTS_ISP_ALGO_AWB, /**< AWB algorithm */
	RTS_ISP_ALGO_AF, /**< AF algorithm */
	RTS_ISP_ALGO_MD, /**< Other ISP algorithm */
	RTS_ISP_ALGO_OTHER, /**< Other ISP algorithm */
	_RTS_ISP_ALGO_TYPE_NUM,
};

/**
 * @brief ISP algorithm ID
 */
enum rts_isp_algo_id {
	RTS_ISP_ALGO_AE_ID0, /**< AE algorithm 0 */
	RTS_ISP_ALGO_AE_ID1, /**< AE algorithm 1 */
	RTS_ISP_ALGO_AE_ID2, /**< AE algorithm 2 */
	RTS_ISP_ALGO_AE_ID3, /**< AE algorithm 3 */

	RTS_ISP_ALGO_AWB_ID0, /**< AWB algorithm 0 */
	RTS_ISP_ALGO_AWB_ID1, /**< AWB algorithm 1 */
	RTS_ISP_ALGO_AWB_ID2, /**< AWB algorithm 2 */
	RTS_ISP_ALGO_AWB_ID3, /**< AWB algorithm 3 */

	RTS_ISP_ALGO_AF_ID0, /**< AF algorithm 0 */
	RTS_ISP_ALGO_AF_ID1, /**< AF algorithm 1 */
	RTS_ISP_ALGO_AF_ID2, /**< AF algorithm 2 */
	RTS_ISP_ALGO_AF_ID3, /**< AF algorithm 3 */

	RTS_ISP_ALGO_MD_ID0, /**< other ISP algorithm 0 */
	RTS_ISP_ALGO_MD_ID1, /**< other ISP algorithm 1 */
	RTS_ISP_ALGO_MD_ID2, /**< other ISP algorithm 2 */
	RTS_ISP_ALGO_MD_ID3, /**< other ISP algorithm 3 */

	RTS_ISP_ALGO_OTHER_ID0, /**< other ISP algorithm 0 */
	RTS_ISP_ALGO_OTHER_ID1, /**< other ISP algorithm 1 */
	RTS_ISP_ALGO_OTHER_ID2, /**< other ISP algorithm 2 */
	RTS_ISP_ALGO_OTHER_ID3, /**< other ISP algorithm 3 */

	_RTS_ISP_ALGO_ID_NUM,
};

/**
 * @brief Structure of ISP algorithm.
 */
struct rts_isp_algo {
	enum rts_isp_algo_id id; /**< ID of algorithm */
	const char *path; /**< path of algorithm */
};

/**
 * @brief Register ISP algorithm.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] algo pointer of \ref rts_isp_algo.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_register_algo(const struct rts_isp_algo *algo);
/**
 * @brief Unregister ISP algorithm.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] id ID of unregistered algorithm.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_unregister_algo(enum rts_isp_algo_id id);
/**
 * @brief Get ISP algorithm path by ID.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] algo pointer of \ref rts_isp_algo, ID of algo must be specified.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_get_algo(struct rts_isp_algo *algo);
/**
 * @brief Bind ISP algorithm with specified ISP.
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[in] id ID of ISP algorithm.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_bind_algo(uint32_t isp_id, enum rts_isp_algo_id id);
/**
 * @brief Unbind ISP algorithm from specified ISP.
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[in] id ID of ISP algorithm.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_unbind_algo(uint32_t isp_id, enum rts_isp_algo_id id);

/**
 * @brief ISP sensor
 */
struct rts_isp_sensor {
	const char *path; /**< path of sensor */
};

/**
 * @brief Register ISP sensor.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] snr pointer of \ref rts_isp_sensor.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_register_sensor(const struct rts_isp_sensor *snr);
/**
 * @brief Unregister specofied sensor.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] snr_id ID of sensor
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_unregister_sensor(int snr_id);
/**
 * @brief Obtain ISP sensor path by sensor ID.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] snr_id sensor ID.
 * @param[in] snr pointer of \ref rts_isp_sensor.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_get_sensor(int snr_id, struct rts_isp_sensor *snr);
/**
 * @brief Check whether sensor is connected with specified ISP or not.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] isp_id ID of ISP.
 * @param[in] snr_id ID of sensor.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_check_sensor(uint32_t isp_id, int snr_id);
/**
 * @brief Bind ISP sensor with specified ISP.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] isp_id ID of ISP.
 * @param[in] snr_id ID of sensor.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_bind_sensor(uint32_t isp_id, int snr_id);
/**
 * @brief Unbind ISP sensor from specified ISP.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] isp_id ID of ISP.
 * @param[in] snr_id ID of sensor.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_unbind_sensor(uint32_t isp_id, int snr_id);

#define IQ_CALB_EN_AWB  (0x1 << 0)
#define IQ_CALB_EN_MLSC (0x1 << 1)
#define IQ_CALB_EN_NLSC (0x1 << 2)

enum apply_calb_failed_item {
	APPLY_AWB_CALB_FAILED = 1,
	APPLY_MLSC_CALB_FAILED,
	APPLY_NLSC_CALB_FAILED
};

struct isp_iq_calb_point {
	int32_t x;
	int32_t y;
} __attribute__((packed));

struct isp_iq_calb_nlsc {
	struct isp_iq_calb_point r_center;
	struct isp_iq_calb_point g_center;
	struct isp_iq_calb_point b_center;
	float curve_ratio;
} __attribute__((packed));

struct isp_iq_calb_mlsc {
	uint8_t matrix_r[1536];
	uint8_t matrix_g[1536];
	uint8_t matrix_b[1536];
} __attribute__((packed));

struct isp_iq_calb_awb {
	int32_t x_offset;
	int32_t y_offset;
} __attribute__((packed));

struct isp_iq_calb {
	uint8_t enable;
	struct isp_iq_calb_awb awb;
	struct isp_iq_calb_mlsc mlsc;
	struct isp_iq_calb_nlsc nlsc;
} __attribute__((packed));

/**
 * @brief Register IQ to specified ISP.
 * @attention This API must be called at the same process that called \ref rts_av_isp_init.
 * @param[in] isp_id ISP ID.
 * @param[in] path file path of IQ binary
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_register_iq(uint32_t isp_id, const char *path);

/**
 * @brief Set IQ calibration data to specified ISP.
 * @param[in] isp_id ISP ID.
 * @param[in] data calibration data
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_set_iq_calb(uint32_t isp_id, struct isp_iq_calb *data);

/**
 * @brief Set Enable bitmask to calibration function to specified ISP
 * @param[in] isp_id ISP ID.
 * @param[in] en Enable bitmask
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_set_iq_calb_en(uint32_t isp_id, uint8_t en);

/**
 * @brief type of out of ISP mipi
 */
enum rts_isp_mipiout_type {
	RTS_ISP_MIPIOUT_RAW8,/**< RAW8 */
	RTS_ISP_MIPIOUT_RAW10,/**< RAW10 */
	RTS_ISP_MIPIOUT_RAW12,/**< RAW12 */
	RTS_ISP_MIPIOUT_YUYV, /**< YUYV */
};

/**
 * @brief position of mipi out
 */
enum rts_isp_mipiout_position {
	RTS_ISP_MIPIOUT_BEFORE_CROP, /**< for raw, out before crop */
	RTS_ISP_MIPIOUT_AFTER_CROP, /**< for raw, out after crop */
	RTS_ISP_MIPIOUT_BEFORE_ZOOM, /**< for yuyv, out before zoom */
};

/**
 * @brief mipi out of ISP
 */
struct rts_isp_mipiout {
	int enable; /**< enable */
	int lanes; /**< number of mipi lane */
	enum rts_isp_mipiout_type type; /**< type of mipi out */
	enum rts_isp_mipiout_position position; /**< position of mipi out */
};

/**
 * @brief Obtain mipi out of specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[in] mipiout pointer of \ref rts_isp_mipiout.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_get_mipiout(uint32_t isp_id, struct rts_isp_mipiout *mipiout);
/**
 * @brief Set mipi out for specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[in] mipiout pointer of \ref rts_isp_mipiout.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_set_mipiout(uint32_t isp_id, struct rts_isp_mipiout *mipiout);

/**
 * @brief version of ISP plugins
 */
struct rts_isp_plugins_version {
	uint16_t ae_api_version; /**< version for ae algo api */
	uint16_t awb_api_version; /**< version for awb algo api */
	uint16_t af_api_version; /**< version for af algo api */
	uint16_t md_algo_api_version; /**< version for md algo api */
	uint16_t sensor_api_version; /**< version for sensor api */
	uint32_t iq_pack_version; /**< version for iq packed format */
	uint32_t iq_proto_version; /**< version for iq protobuf */
	uint8_t iq_customer_version; /**< version for customer iq */
};

/**
 * @brief Obtain mipi out of specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[out] version pointer of \ref rts_isp_plugins_version.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_get_plugins_version(uint32_t isp_id,
				   struct rts_isp_plugins_version *version);


/**
 * @brief Enum modes of sensor connect on specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[out] modes pointer of \ref rts_isp_sensor_modes.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_enum_sensor_modes(uint32_t isp_id,
				 struct rts_isp_sensor_modes *modes);

/**
 * @brief Get mode of sensor connect on specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[out] mode pointer of \ref rts_isp_sensor_mode.
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_get_sensor_mode(uint32_t isp_id,
			       struct rts_isp_sensor_mode *mode);

/**
 * @brief Set mode of sensor connect on specified ISP
 * @attention This API can be called at any process.
 * @param[in] isp_id ID of ISP.
 * @param[in] mode pointer of \ref rts_isp_sensor_mode. size of mode can be
 * smaller than the size of enumed modes
 * @return 0 : success, minus : fail.
 */
int rts_av_isp_set_sensor_mode(uint32_t isp_id,
			       struct rts_isp_sensor_mode *mode);

/*!@}*/
#ifdef __cplusplus
}
#endif

#endif /* _RTSAVISP_H_INC_ */
