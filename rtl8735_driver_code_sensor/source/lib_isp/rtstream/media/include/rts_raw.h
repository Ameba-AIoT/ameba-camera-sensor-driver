/*
 * Realtek Semiconductor Corp.
 *
 * raw/rts_raw.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */

/**
 * @file rts_raw.h
 * @brief RTStream raw API reference
 * @defgroup raw RTStream Raw API
 * @brief RTStream get raw image API reference
 * @{
 */

#ifndef _INCLUDE_RTS_RAW_H
#define _INCLUDE_RTS_RAW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define RTS_RAW_HEADER_LENGTH		128

/**
 * @brief raw handler
 */
struct rts_raw_t {
	/**
	 * header of raw, RTS_RAW_HEADER_LENGTH equals to 128.\n
	 * byte[0]~byte[3]: format, which is 0x32595559.\n
	 * byte[4]~byte[7]: width of raw image.\n
	 * byte[8]~byte[11]: height of raw image.\n
	 * byte[12]~byte[15]: length of raw data.\n
	 * byte[16]~byte[19]: sensor format.
	 */
	uint8_t header[RTS_RAW_HEADER_LENGTH];
	uint32_t length; /**< raw data length */
	uint8_t *pdata; /**< raw data */
	uint32_t width; /**< width of raw image */
	uint32_t height; /**< height of raw image */
	uint32_t fmt; /**< format, which is 0x32595559 */
	 /**
	  * sensor format, see more in \ref rts_raw_fmt
	  */
	unsigned int snr_fmt;
	unsigned int raw_fmt; /**< raw source, see more in \ref rts_raw_src */
	int streamid; /**< stream id */
	int fd; /**< fd of raw video device */
	int initialized; /**< flag of initialize raw handler */
	int skip_count; /**< get raw image after skipping how many frames */
	void (*make_raw_data)(struct rts_raw_t *praw, uint8_t *pdata, int offset_uv);
};

/**
 * @brief source of raw data
 */
enum rts_raw_src {
	RTS_RAW_SRC_DISABLE = 0, /**< disable raw */

	RTS_RAW_SRC_BLC_LONGEXP_B = 0x1, /**< raw data before BLC of long exposure path */
	RTS_RAW_SRC_BLC_SHORTEXP_B = 0x2, /**< raw data before BLC of short exposure path */

	RTS_RAW_SRC_BLC_LONGEXP_A = 0x3, /**< raw data after BLC of long exposure path */
	RTS_RAW_SRC_BLC_SHORTEXP_A = 0x4, /**< raw data after BLC of short exposure path */

	RTS_RAW_SRC_DPC_LONGEXP_A = 0x5, /**< raw data after DPC of long exposure path */
	RTS_RAW_SRC_DNS_LONGEXP_A = 0x6, /**< raw data after raw denoise(TNR) of long exposure path */
	RTS_RAW_SRC_DNS_SHORTEXP_A = 0x7, /**< raw data after raw denoise(TNR) of short exposure path */

	RTS_RAW_SRC_LSC_A = 0x8, /**< raw data after LSC */

	RTS_RAW_SRC_AE_B = 0x9, /**< raw data before AE(after AWB) */

	RTS_RAW_SRC_INTP_B = 0xa, /**< raw data before Interpolation */

	/**
	 * R data before CCM
	 */
	RTS_RAW_SRC_R_CCM_B = 0xb,

	/**
	 * G data before CCM
	 */
	RTS_RAW_SRC_G_CCM_B = 0xc,

	/**
	 * B data before CCM
	 */
	RTS_RAW_SRC_B_CCM_B = 0xd,

	/**
	 * R data before RGB to YUV
	 */
	RTS_RAW_SRC_R_RGB2YUV_B = 0xe,

	/**
	 * G data before RGB to YUV
	 */
	RTS_RAW_SRC_G_RGB2YUV_B = 0xf,

	/**
	 * B data before RGB to YUV
	 */
	RTS_RAW_SRC_B_RGB2YUV_B = 0x10,

	/**
	 * data after MASK
	 */
	RTS_RAW_SRC_MASK_OUT = 0x11,

	RTS_RAW_SRC_RESERVED
};
/**
 * @brief format of sensor raw data
 */
enum rts_raw_fmt {
	RTS_RAW_FMT_RAW8 = 8, /**< raw8 */
	RTS_RAW_FMT_RAW10 = 10, /**< raw10 */
	RTS_RAW_FMT_RAW12 = 12, /**< raw12 */
	RTS_RAW_FMT_YUV = 0xFF, /**< YUYV */
	RTS_RAW_FMT_RAW14 = 14, /**< raw14, only supported by RTS3915 */
	RTS_RAW_FMT_RESERVED
};

/**
 * @example example_get_raw_pict.c
 */

/**
 * @brief Initialize raw handler
 * @param[in] raw_fmt source of raw data, see detail in \ref rts_raw_src
 * @param[out] ppraw address of raw handler pointer,
 * raw handler see \ref rts_raw_t for more
 * @attention Raw format can be updated by \ref rts_update_raw_fmt
 * after initializing.
 * Raw handler must be released by \ref rts_release_raw at last.
 * @return 0 : success, minus : fail
 */
int rts_init_raw(unsigned int raw_fmt, struct rts_raw_t **ppraw);
/**
 * @brief Release raw handler
 * @param[in] praw raw handler obtained by \ref rts_init_raw
 */
void rts_release_raw(struct rts_raw_t *praw);
/**
 * @brief Get raw data
 * @param[out] praw raw handler obtained by \ref rts_init_raw.
 * @note Raw data will store in pdata of \ref rts_raw_t.
 * @return 0 : success, minus : fail
 */
int rts_get_raw_frame(struct rts_raw_t *praw);
int rts_get_raw_header(struct rts_raw_t *praw);
/**
 * @brief Update raw format
 * @param[in] raw_fmt format of raw data, see detail in \ref rts_raw_src
 * @param[in] praw raw handler obtained by \ref rts_init_raw.
 * @return 0 : success, minus : fail
 */
int rts_update_raw_fmt(unsigned int raw_fmt, struct rts_raw_t *praw);
/*!@}*/

int rts_hal_set_raw(uint8_t streamid, uint32_t fmt);


#ifdef __cplusplus
}
#endif
#endif
