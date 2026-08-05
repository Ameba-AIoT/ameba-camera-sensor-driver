/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_config.h
 *
 * Copyright (C) 2018      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_CAMERA_CONFIG_H
#define _RTS_CAMERA_CONFIG_H

#define RTSCAM_MAX_STM_COUNT		5
#define RTSCAM_MAX_FPS_COUNT		122
#define RTSCAM_FPS_UNIT			10000000

#define RTSCAM_YUV_MAX_STRM_NUM		4
#define RTSCAM_MAX_STREAM_NUM		(RTSCAM_YUV_MAX_STRM_NUM + 1)
#define RTSCAM_RGB_YONLY_STRM_IDX	(RTSCAM_MAX_STREAM_NUM - 1)

/* format type */
#define RTSCAM_FORMAT_TYPE_YUV420_SEMIPLANAR		(1 << 0)
#define RTSCAM_FORMAT_TYPE_YUV422_SEMIPLANAR		(1 << 1)
#define RTSCAM_FORMAT_TYPE_RGB				(1 << 2)
#define RTSCAM_FORMAT_TYPE_Y_ONLY			(1 << 3)
#define RTSCAM_FORMAT_TYPE_YUYV				(1 << 4)
#define RTSCAM_FORMAT_TYPE_YVYU				(1 << 5)

#endif
