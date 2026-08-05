/*
 * Realtek Semiconductor Corp.
 *
 * rtstream/media/video/common/rtsvideo.c
 *
 * Copyright (C) 2018      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "cmsis_os2.h"
#include <rtscamkit.h>
#include <rtsc.h>
#include <rtsc_hwver.h>
//#include "rts_video_common.h"
#include "rtsavdef.h"
#ifdef RTS_ENABLE_MCU
#include "rtsmcu.h"
#endif

static osMutexId_t vlock = NULL;

static int __init_video(void)
{
	int register_video = 0;

	rts_get_unit_registered(&register_video,
				NULL, NULL);
	if (register_video) {
		return RTS_OK;
	}

	rts_register_vin();
#ifdef RTS_ENABLE_H1ENCODER
	rts_register_h1();
#endif
#ifdef RTS_ENABLE_W420
	rts_register_w420();
#endif
#if (defined RTS_ENABLE_W521) || (defined RTS_ENABLE_W521MP)
	rts_register_w521();
#endif
#if (defined RTS_ENABLE_JPEG) || (defined RTS_ENABLE_JPU)
	rts_register_mjpeg();
#endif
#ifdef RTS_ENABLE_OSD2
	rts_register_osd2();
#endif
#ifdef RTS_ENABLE_VOUT
	rts_register_vout();
#endif
	register_video = 1;
	rts_set_unit_registered(&register_video,
				NULL, NULL);

	return RTS_OK;
}

int rts_av_create_vin_chn(struct rts_vin_attr *attr)
{
	__init_video();

	if (!attr)
		return RTS_RETURN(RTS_E_NULL_POINT);

	return rts_av_create_chn(RTS_AV_ID_VIN, attr);
}

int rts_av_create_h264_chn(struct rts_h264_attr *attr)
{
	__init_video();

	if (!attr)
		return RTS_RETURN(RTS_E_NULL_POINT);

	return rts_av_create_chn(RTS_AV_ID_H264, attr);
}

int rts_av_create_h265_chn(struct rts_h265_attr *attr)
{
	__init_video();

	if (!attr)
		return RTS_RETURN(RTS_E_NULL_POINT);

	return rts_av_create_chn(RTS_AV_ID_H265, attr);
}

int rts_av_create_mjpeg_chn(struct rts_jpgenc_attr *attr)
{
	__init_video();

	if (!attr)
		return RTS_RETURN(RTS_E_NULL_POINT);

	return rts_av_create_chn(RTS_AV_ID_MJPGENC, attr);
}

int rts_av_create_mjpgdec_chn(struct rts_jpgdec_attr *attr)
{
	__init_video();

	RTS_ASSERT(attr);

	return rts_av_create_chn(RTS_AV_ID_MJPGDEC, attr);
}

int rts_av_create_osd_chn(void)
{
	__init_video();

	return rts_av_create_chn(RTS_AV_ID_OSDENC, NULL);
}

int rts_av_create_vps_chn(void)
{
	__init_video();

	struct rts_vin_attr attr;

	attr.vin_buf_num = 1;
	attr.vin_id = RTS_VIN_CHANNEL_RGB0;
	return rts_av_create_chn(RTS_AV_ID_VPS, &attr);
}

int rts_av_get_vin_attr(unsigned int chnno, struct rts_vin_attr *attr)
{
	return rts_av_get_attr(chnno, RTS_AV_ID_VIN, attr);
}

int rts_av_get_h264_attr(unsigned int chnno, struct rts_h264_attr *attr)
{
	return rts_av_get_attr(chnno, RTS_AV_ID_H264, attr);
}

int rts_av_get_mjpeg_attr(unsigned int chnno, struct rts_jpgenc_attr *attr)
{
	return rts_av_get_attr(chnno, RTS_AV_ID_MJPGENC, attr);
}

int rts_av_get_mjpgdec_attr(unsigned int chnno, struct rts_jpgdec_attr *attr)
{
	return rts_av_get_attr(chnno, RTS_AV_ID_MJPGDEC, attr);
}

int rts_av_get_h265_attr(unsigned int chnno, struct rts_h265_attr *attr)
{
	return rts_av_get_attr(chnno, RTS_AV_ID_H265, attr);
}

int rts_av_create_vout_chn(struct rts_vout_attr *attr)
{
	__init_video();

	return rts_av_create_chn(RTS_AV_ID_VOUT, attr);
}

