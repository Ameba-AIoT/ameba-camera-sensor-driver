/*
 * Realtek Semiconductor Corp.
 *
 * rtsraw/rts_raw.c
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <rtsv4l2.h>
#include <rtscamkit.h>
#include <rtsc_hwver.h>
#include <rtsc.h>
#include <rts_isp.h>
#include "rts_raw.h"
#include "hal_isp.h"

#define RTS_ENABLE_ISP

#define RTS_RAW_VIDEO_DEV		"/dev/video51"
#define RTS_RAW_INITIALIZED		0x32

static void make_raw_header(struct rts_raw_t *praw)
{
	uint32_t fmt = 0x32595559;
	int pos = 0;

	if (!praw)
		return;

	praw->header[pos++] = fmt & 0xff;
	praw->header[pos++] = (fmt >> 8) & 0xff;
	praw->header[pos++] = (fmt >> 16) & 0xff;
	praw->header[pos++] = (fmt >> 24) & 0xff;

	praw->header[pos++] = praw->width & 0xff;
	praw->header[pos++] = (praw->width >> 8) & 0xff;
	praw->header[pos++] = (praw->width >> 16) & 0xff;
	praw->header[pos++] = (praw->width >> 24) & 0xff;

	praw->header[pos++] = praw->height & 0xff;
	praw->header[pos++] = (praw->height >> 8) & 0xff;
	praw->header[pos++] = (praw->height >> 16) & 0xff;
	praw->header[pos++] = (praw->height >> 24) & 0xff;

	praw->header[pos++] = praw->length & 0xff;
	praw->header[pos++] = (praw->length >> 8) & 0xff;
	praw->header[pos++] = (praw->length >> 16) & 0xff;
	praw->header[pos++] = (praw->length >> 24) & 0xff;

	praw->header[pos++] = praw->snr_fmt & 0xff;
	praw->header[pos++] = (praw->snr_fmt >> 8) & 0xff;
	praw->header[pos++] = (praw->snr_fmt >> 16) & 0xff;
	/* 0xAA for TAG */
	praw->header[pos++] = ((praw->snr_fmt >> 24) & 0xff) | 0xAA;
}

#ifdef RTS_ENABLE_ISP
static void make_raw_data_422(struct rts_raw_t *praw, uint8_t *pbuf, int offset_uv)
{
	int i, j;
	int index;
	uint16_t value;

	index = 0;
	for (j = 0; j < (int)praw->height; j++) {
		for (i = 0; i < (int)praw->width; i++) {
			value = pbuf[index] << 8 | pbuf[index + offset_uv];

			praw->pdata[2 * index] = value & 0xff;
			praw->pdata[2 * index + 1] = (value >> 8) & 0xff;
			index++;
		}
	}
}

static void make_raw_data_from_raw422(struct rts_raw_t *praw, uint8_t *pbuf, int offset_uv)
{
	make_raw_data_422(praw, pbuf, offset_uv);
}
#elif defined RTS_ENABLE_MCU
static void make_raw_data_420(struct rts_raw_t *praw, uint8_t *pbuf, int offset_uv,
			      unsigned int shift)
{
	int i, j;
	int index;
	uint16_t value;

	index = 0;
	for (j = 0; j < praw->height; j++) {
		for (i = 0; i < praw->width; i++) {
			uint32_t a = offset_uv + index / 2;
			uint32_t b = index % 2;

			b *= 4;
			value = ((uint16_t)pbuf[index]) << 4;
			value |= ((pbuf[a] >> b) & 0xf);
			value = value >> shift;

			praw->pdata[2 * index] = value & 0xff;
			praw->pdata[2 * index + 1] = (value >> 8) & 0xff;
			index++;
		}
	}
}

static void make_raw_data_from_raw420(struct rts_raw_t *praw, uint8_t *pbuf, int offset_uv)
{
	unsigned int shift = 0;

	switch (praw->snr_fmt) {
	case RTS_RAW_FMT_RAW8:
		shift = 4;
		break;
	case RTS_RAW_FMT_RAW10:
		shift = 2;
		break;
	case RTS_RAW_FMT_RAW12:
		shift = 0;
		break;
	default:
		break;
	}

	make_raw_data_420(praw, pbuf, offset_uv, shift);
}
#endif

static void make_raw_data(struct rts_raw_t *praw, uint8_t *pbuf, int offset_uv)
{
	RTS_ASSERT(praw);
	RTS_ASSERT(pbuf);
	RTS_ASSERT(praw->make_raw_data);

	if (!praw->pdata)
		return;

	if (praw->length != praw->width * praw->height * 2)
		return;

	praw->make_raw_data(praw, pbuf, offset_uv);
}

static void set_raw_fmt(struct rts_raw_t *praw, unsigned int raw_fmt)
{
	praw->raw_fmt = raw_fmt;
#ifdef RTS_ENABLE_ISP
	if ((raw_fmt == RTS_RAW_SRC_LSC_A) ||
	   (raw_fmt == RTS_RAW_SRC_AE_B))
		praw->snr_fmt = RTS_RAW_FMT_RAW14;
	else
		praw->snr_fmt = RTS_RAW_FMT_RAW12;
#elif defined RTS_ENABLE_MCU
	if (raw_fmt >= RTS_RAW_SRC_BLC_A)
		praw->snr_fmt = RTS_RAW_FMT_RAW12;
#endif
}

int rts_init_raw(unsigned int raw_fmt, struct rts_raw_t **ppraw)
{
	struct rts_raw_t *praw = NULL;
	int fd;
	int ret = RTS_OK;

	if (!ppraw)
		return RTS_RETURN(RTS_E_NULL_POINT);

	if (raw_fmt == 0x0 || raw_fmt >= RTS_RAW_SRC_RESERVED)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	praw = (struct rts_raw_t *)rts_calloc(1, sizeof(*praw));
	if (!praw)
		return RTS_RETURN(RTS_E_NULL_POINT);

	fd = rts_v4l2_open(RTS_RAW_VIDEO_DEV, O_RDWR);
	if (fd < 0) {
		ret = RTS_RETURN(RTS_E_OPEN_FAIL);
		goto error;
	}

	ret = rts_v4l2_get_fmt(fd, (uint32_t*)&praw->snr_fmt,
			&praw->width, &praw->height);
	if (ret < 0) {
		RTS_ERR("get sensor fmt fail\n");
		goto error;
	}

	praw->streamid = rtsc_get_streamid(fd);
	if (praw->streamid < 0) {
		RTS_ERR("get raw video stream id fail\n");
		ret = RTS_RETURN(RTS_FAIL);
		goto error;
	}

#ifdef RTS_ENABLE_ISP
	praw->fmt = V4L2_PIX_FMT_NV16;
	praw->make_raw_data = make_raw_data_from_raw422;
#elif defined RTS_ENABLE_MCU
	praw->fmt = V4L2_PIX_FMT_NV12;
	praw->make_raw_data = make_raw_data_from_raw420;
#endif

	set_raw_fmt(praw, raw_fmt);
	praw->fd = fd;

	praw->length = praw->width * praw->height * 2;
	praw->pdata = (uint8_t *)rts_calloc(1, praw->length);
	if (!praw->pdata) {
		ret = RTS_RETURN(RTS_E_NO_MEMORY);
		goto error;
	}
	make_raw_header(praw);
	praw->initialized = RTS_RAW_INITIALIZED;
	praw->skip_count = 17;

	*ppraw = praw;
	return RTS_OK;
error:
	RTS_SAFE_DELETE(praw);
	RTS_SAFE_CLOSE(fd, rts_v4l2_close);
	return ret;
}

void rts_release_raw(struct rts_raw_t *praw)
{
	if (!praw)
		return;

	RTS_SAFE_CLOSE(praw->fd, rts_v4l2_close);
	RTS_SAFE_DELETE(praw->pdata);
	RTS_SAFE_DELETE(praw);
}

int rts_get_raw_header(struct rts_raw_t *praw)
{
	if (!praw)
		return RTS_RETURN(RTS_E_NULL_POINT);

	if (praw->initialized != RTS_RAW_INITIALIZED)
		return RTS_RETURN(RTS_E_INITIALIZED);

	make_raw_header(praw);

	return RTS_OK;
}

int rts_hal_set_raw(uint8_t streamid, uint32_t fmt)
{
	int ret = RTS_OK;
	struct v4l2_control ctrl;
	int location;
	int channel = -1;
	struct rts_isp_bypass bypass;
	printf("stream %d rawfmt %d \n", streamid, fmt);
	memset(&bypass, 0, sizeof(bypass));
	ret = rts_isp_get_bypass(ISP0, &bypass);
	if (ret) {
		printf("get bypass fail\n");
		return ret;
	}
	printf("set raw fmt=%x [DEC:%d] \r\n", fmt, fmt);

	switch (fmt) {
	case RTS_RAW_SRC_DISABLE:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_blc_shortexp = 0;
		bypass.bypass_dpc_longexp = 0;
		bypass.bypass_dpc_snr_shortexp = 0;
		bypass.bypass_tnr_longexp = 0;
		bypass.bypass_vhdr = 0;
		bypass.bypass_nlsc = 0;
		bypass.bypass_mlsc = 0;
		bypass.bypass_awb = 0;
		bypass.bypass_ae = 0;
		bypass.bypass_ccm = 0;
		bypass.bypass_gamma = 0;
		bypass.bypass_ygc = 0;
		bypass.bypass_uvtune = 0;
		bypass.bypass_eeh = 0;
		bypass.bypass_spe = 0;
		bypass.bypass_ygamma = 0;
		location = 0;
		channel = 0;
		break;
	case RTS_RAW_SRC_BLC_LONGEXP_B:
		location = 2;
		break;
	case RTS_RAW_SRC_BLC_SHORTEXP_B:
		location = 14;
		break;
	case RTS_RAW_SRC_BLC_LONGEXP_A:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_dpc_longexp = 1;
		bypass.bypass_tnr_longexp = 1;
		location = 3;
		break;
	case RTS_RAW_SRC_BLC_SHORTEXP_A:
		bypass.bypass_blc_shortexp = 0;
		bypass.bypass_dpc_snr_shortexp = 1;
		location = 15;
		break;
	case RTS_RAW_SRC_DPC_LONGEXP_A:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_dpc_longexp = 0;
		bypass.bypass_tnr_longexp = 1;
		location = 3;
		break;
	case RTS_RAW_SRC_DNS_LONGEXP_A:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_dpc_longexp = 0;
		bypass.bypass_tnr_longexp = 0;
		location = 3;
		break;
	case RTS_RAW_SRC_DNS_SHORTEXP_A:
		bypass.bypass_blc_shortexp = 0;
		bypass.bypass_dpc_snr_shortexp = 0;
		location = 15;
		break;
	case RTS_RAW_SRC_LSC_A:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_blc_shortexp = 0;
		bypass.bypass_dpc_longexp = 0;
		bypass.bypass_dpc_snr_shortexp = 0;
		bypass.bypass_tnr_longexp = 0;
		bypass.bypass_vhdr = 0;
		bypass.bypass_nlsc = 0;
		bypass.bypass_mlsc = 0;
		bypass.bypass_awb = 1;
		bypass.bypass_ae = 1;
		location = 4;
		break;
	case RTS_RAW_SRC_AE_B:
		bypass.bypass_blc_longexp = 0;
		bypass.bypass_blc_shortexp = 0;
		bypass.bypass_dpc_longexp = 0;
		bypass.bypass_dpc_snr_shortexp = 0;
		bypass.bypass_tnr_longexp = 0;
		bypass.bypass_vhdr = 0;
		bypass.bypass_nlsc = 0;
		bypass.bypass_mlsc = 0;
		bypass.bypass_awb = 0;
		bypass.bypass_ae = 1;
		location = 4;
		break;
	case RTS_RAW_SRC_INTP_B:
		location = 4;
		break;
	case RTS_RAW_SRC_R_CCM_B:
		location = 5;
		channel = 0;
		break;
	case RTS_RAW_SRC_G_CCM_B:
		location = 5;
		channel = 1;
		break;
	case RTS_RAW_SRC_B_CCM_B:
		location = 5;
		channel = 2;
		break;
	case RTS_RAW_SRC_R_RGB2YUV_B:
		location = 6;
		channel = 0;
		break;
	case RTS_RAW_SRC_G_RGB2YUV_B:
		location = 6;
		channel = 1;
		break;
	case RTS_RAW_SRC_B_RGB2YUV_B:
		location = 6;
		channel = 2;
		break;
	case RTS_RAW_SRC_MASK_OUT:
		location = 10;
		break;
	default:
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.id = RTS_V4L2_CID_OUTPUT_POSITION;
	ctrl.value = location;

	ret = rts_isp_v4l2_s_ctrl(ISP0, &ctrl);
	if (ret) {
		printf("set output position fail\n");
		return ret;
	}

	if (channel > -1) {
		memset(&ctrl, 0, sizeof(ctrl));
		ctrl.id = RTS_V4L2_CID_OUTPUT_CHANNEL;
		ctrl.value = channel;

		ret = rts_isp_v4l2_s_ctrl(ISP0, &ctrl);
		if (ret) {
			printf("set output channel fail\n");
			return ret;
		}
	}

	ret = rts_isp_set_bypass(ISP0, &bypass);
	if (ret) {
		printf("set bypass fail\n");
		return ret;
	}

	return RTS_OK;
}

extern unsigned int rtscam_socdev_get_height_align(void);

int rts_get_raw_frame(struct rts_raw_t *praw)
{
	void *frames[3] = {NULL, NULL, NULL};
	uint32_t lengths[3] = {0, 0, 0};
	int count = 0;
	int i, j;
	int got = 0;
	struct v4l2_buffer v4l2_buf;
	int align_h, offset_uv;
	int ret = RTS_OK;

	if (!praw)
		return RTS_RETURN(RTS_E_NULL_POINT);

	if (praw->initialized != RTS_RAW_INITIALIZED)
		return RTS_RETURN(RTS_E_INITIALIZED);

	if (praw->width * praw->height * 2 != praw->length)
		return RTS_RETURN(RTS_E_INITIALIZED);

	if (!praw->pdata)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = rts_v4l2_set_fmt(praw->fd, praw->fmt, praw->width, praw->height);
	if (ret < 0) {
		RTS_ERR("[%s]set fmt fail\n", __func__);
		return ret;
	}

	ret = rts_v4l2_request_bufs(praw->fd, 3);
	if (ret <= 0) {
		RTS_ERR("[%s]request buffer fail\n", __func__);
		return ret;
	}
	count = ret;
	for (i = 0; i < count; i++) {
		ret = rts_v4l2_query_mmap_buf(praw->fd,
					      i, &frames[i], &lengths[i]);
		if (ret < 0) {
			RTS_ERR("[%s]query & mmap buf fail\n", __func__);
			goto exit;
		}
	}

	ret = rts_v4l2_streamon(praw->fd);
	if (ret < 0) {
		RTS_ERR("[%s]stream on fail\n", __func__);
		goto exit;
	}

	ret = rts_hal_set_raw(praw->streamid, praw->raw_fmt);
	if (ret < 0) {
		RTS_ERR("[%s]set raw fmt fail\n", __func__);
		goto exit1;
	}

	//get offset of UV buffer start, see rts_camera_soc_3915.c/rtscam_socdev_submit_buffer()
	offset_uv = praw->width * praw->height;
	align_h = rtscam_socdev_get_height_align();
	if (align_h) {
		if (praw->height % align_h)
			offset_uv += (align_h - praw->height % align_h) * praw->width;
	}
	printf("Frame height align = %d, UV data offset = 0x%x\n", align_h, (unsigned int)offset_uv);

	j = 0;
	for (i = 0; i < 1000; i++) {
		ret = rts_v4l2_get_buffer(praw->fd, (uint32_t *)&v4l2_buf);
		if (ret < 0)
			continue;

		j++;
		if (j > praw->skip_count) {
			make_raw_data(praw, frames[v4l2_buf.index], offset_uv);
			got = 1;
		}
		rts_rtsv_put_buffer(praw->fd, (uint32_t *)&v4l2_buf);

		if (got)
			break;
	}

	rts_hal_set_raw(praw->streamid, RTS_RAW_SRC_DISABLE);
exit1:
	rts_rtsv_streamoff(praw->fd);
exit:
	for (i = 0; i < count; i++)
		rts_v4l2_munmap_buf(frames[i], lengths[i]);

	ret = rts_v4l2_request_bufs(praw->fd, 0);

	return ret;
}

int rts_update_raw_fmt(unsigned int raw_fmt, struct rts_raw_t *praw)
{
	if (!praw)
		return RTS_RETURN(RTS_E_NULL_POINT);

	if (raw_fmt == RTS_RAW_SRC_DISABLE ||
			raw_fmt >= RTS_RAW_SRC_RESERVED)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	set_raw_fmt(praw, raw_fmt);

	return RTS_OK;
}
