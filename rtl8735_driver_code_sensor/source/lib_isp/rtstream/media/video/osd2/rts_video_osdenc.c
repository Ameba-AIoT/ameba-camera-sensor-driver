/*
 * Realtek Semiconductor Corp.
 *
 * media/video/osd/rts_video_osdenc.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
//#include <assert.h>
#include <signal.h>
#include "cmsis_os2.h"
#include <rtscamkit.h>
#include <rtsosd2.h>
#include "rtsavunit.h"
#include "rtsavdef.h"
#include "rtsavfunc.h"
#include "rtsvideo.h"
#include "rtsvideo_func.h"
#include "rts_video_osd2_ctrl.h"
#include "rt_avdef.h"
#include "rt_config.h"
#include "isp_log.h"
#define RTS_ENC_USE_EPOLL               1
#define RTS_ENC_USE_SIGIO               0
#define RTS_AV_USE_ADMA                 0

struct rts_av_osdenc_t {
	int start;
	struct rts_av_profile profile;
	RtsOsd2Inst posd[CFG_PING_PONG_MAX_BUF_NUM];

	int use_epoll;
	int use_sigio;
	//struct rts_av_poll_fd pfd;
	//struct rts_av_timer_task timeout;
	unsigned long e_count;
	unsigned long t_count;
	uint64_t tv_s;
	//int encoding;
	//struct rts_av_unit *unit;
	int chn_id;
};

static struct rts_av_osdenc_t gbl_osdenc[CFG_OSD_SUPPORT_MAX_CHNS];
extern u32 gbl_osd2_block_num[CFG_OSD_SUPPORT_MAX_CHNS];

static void __init_osdenc_attr(int chn_id, int buf_id, RtsOsd2Inst posd)
{
	rts_av_set_osdenc_attr(chn_id, buf_id, posd);  //set osdenc attr

	return;
}

struct rts_video_osd2_attr *__get_osdenc_attr(int chn_id, int buf_id)
{
	return rts_av_to_osdenc_attr(chn_id, buf_id);
}

static int __query_osdenc_attr(int chn_id, int buf_id, struct rts_video_osd2_attr **ppattr)
{
	struct rts_video_osd2_attr *pattr;
	int ret;

	pattr = __get_osdenc_attr(chn_id, buf_id);

	ret = rts_av_get_osd2(pattr, chn_id, buf_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("__query_osdenc_attr rts_av_get_osd2 error: %d\n\r", ret);
		memset(pattr->blocks, 0, sizeof(struct rts_video_osd2_block)*gbl_osd2_block_num[chn_id]);
		return ret;
	}

	*ppattr = pattr;
	return RTS_OK;
}

static int __cleanup_osdenc(struct rts_av_osdenc_t *osdenc, int chn_id)
{
	int i;
	
	if (!osdenc) {
		isp_error("__cleanup_osdenc osdenc==NULL\n\r");
		return RTS_OK;
	}

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {
		if (osdenc->posd[i])
			rts_osd2_release(osdenc->posd[i], chn_id);
            osdenc->posd[i] = NULL;
	}
	//RTS_SAFE_DELETE(osdenc);
	memset(osdenc, 0, sizeof(struct rts_av_osdenc_t));

	return RTS_OK;
}

int rts_av_osdenc_init(int chn_id)
{
	struct rts_av_osdenc_t *osdenc = NULL;
	int i = 0;
	osdenc = &gbl_osdenc[chn_id];

	osdenc->start = 0;

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++)
		__init_osdenc_attr(chn_id, i, osdenc->posd[i]);  //set osdenc attr

	osdenc->use_epoll = RTS_ENC_USE_EPOLL;
	osdenc->use_sigio = RTS_ENC_USE_SIGIO;

	isp_info("osd2 notify : %d, %d\n",
		 osdenc->use_epoll, osdenc->use_sigio);

	return RTS_OK;
}

int rts_av_osdenc_cleanup(int chn_id)
{
	struct rts_av_osdenc_t *osdenc;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS)
		return RTS_OK;

	if (gbl_osd2_block_num[chn_id] == 0)
		return RTS_OK;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);
	osdenc->start = 0;

	return __cleanup_osdenc(osdenc, chn_id);  //mpfree osd2 buffer
}

int rts_av_osdenc_start(int chn_id)
{
	struct rts_av_osdenc_t *osdenc;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);

	osdenc->e_count = 0;
	osdenc->t_count = 0;
	osdenc->start = 1;

	return RTS_OK;
}

int rts_av_osdenc_stop(int chn_id)
{
	struct rts_av_osdenc_t *osdenc;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);
	osdenc->start = 0;

	if (osdenc->use_epoll)
		isp_info("[osd2]epoll = %ld,timeout = %ld\n",
			 osdenc->e_count, osdenc->t_count);

	return RTS_OK;
}

int rts_av_osdenc_check_ready(int chn_id)
{
	struct rts_av_osdenc_t *osdenc;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);

	return osdenc->start;
}

int rts_av_osdenc_check_enable(int chn_id, int buf_id)
{
	struct rts_video_osd2_attr *pattr;
	int i, ret;

	pattr = __get_osdenc_attr(chn_id, buf_id);
	ret = 0;
	for (i = 0; i < pattr->number; i++) {
		if (pattr->blocks[i].enable)
			ret++;
	}
	return ret;
}

int rts_av_osdenc_get_profile(int chn_id, struct rts_av_profile *profile);

static int __pre_run(struct rts_av_osdenc_t *osdenc, void *buffer, int chn_id, int buf_id)
{
	struct rts_av_profile profile;

	if (!osdenc || !buffer) {
		isp_error("osd __pre_run error osdenc=%x, buffer: %x\n\r", osdenc, buffer);
		return RTS_RETURN(RTS_E_NOT_READY);
	}

	memset(&profile, 0, sizeof(profile));
	rts_av_osdenc_get_profile(chn_id, &profile);

	if (!profile.fmt) {
		isp_error("osd __pre_run undefined format %x\n\r", profile.fmt);
		return RTS_OK;
	}

	if (profile.fmt != osdenc->profile.fmt ||
	    profile.video.width != osdenc->profile.video.width ||
	    profile.video.height != osdenc->profile.video.height) {
	    isp_error("osd __pre_run format and size error\n\r");
		return RTS_RETURN(RTS_E_CHANGED);
	}

	if (profile.video.numerator == osdenc->profile.video.numerator &&
	    profile.video.denominator == osdenc->profile.video.denominator)
		return RTS_OK;

	osdenc->profile.video.numerator = profile.video.numerator;
	osdenc->profile.video.denominator = profile.video.denominator;

	rts_av_set_osdenc_fps(chn_id, buf_id, osdenc->profile.video.numerator,
			      osdenc->profile.video.denominator);

	if (osdenc->posd[buf_id])
		return rts_av_update_osdenc_flick_info(chn_id, buf_id);

	return RTS_OK;
}

extern unsigned int rtscam_socdev_get_height_align(void);

#ifdef _OSD_DEBUG_LOG

struct osd2_log_info {
	uint32_t buf_id;
	uint32_t enable[RTS_OSD2_BLK_MAX_NUMBER];
	uint32_t blk_addr[RTS_OSD2_BLK_MAX_NUMBER];
	uint32_t time;

};
#define OSD_LOG_CNT 20
struct osd2_log_info  osd_log[OSD_LOG_CNT];
int record_osd_cnt = 0;

#endif


int rt_osd2_encode_buf(int chn_id, int buf_id, void *frm_dat, u32 frm_len)
{
	int ret = RTS_OK;
	struct rts_av_osdenc_t *osdenc;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);

	ret = __pre_run(osdenc, frm_dat, chn_id, buf_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("rt_osd2_encode_buf __pre_run error: %x\n\r", ret);
		goto exit;
	}

	if (osdenc->posd[buf_id]) {
		struct rts_osd2_encin encin;
		uint32_t width = osdenc->profile.video.width;
		uint32_t height = osdenc->profile.video.height;
		int align_h, offset_uv;

		encin.bus_luma = (uint32_t)frm_dat;
		//get offset of UV buffer start, see rts_camera_soc_3915.c/rtscam_socdev_submit_buffer()
		offset_uv = width * height;
		align_h = rtscam_socdev_get_height_align();
		if (align_h) {
			if (height % align_h)
				offset_uv += (align_h - height % align_h) * width;
		}
		encin.bus_chroma = (uint32_t)frm_dat + offset_uv;
		encin.pbuf = (void *)frm_dat;
		encin.buf_size = frm_len;

#ifdef _OSD_DEBUG_LOG
		if ( record_osd_cnt < OSD_LOG_CNT ) {
			osd_log[record_osd_cnt].time = hal_read_curtime_us();
			osd_log[record_osd_cnt].buf_id = buf_id;
		}
#endif
		ret = rts_osd2_encode(osdenc->posd[buf_id], &encin, chn_id);
		if (RTS_IS_ERR(ret))
			isp_error("rts osd2 encode fail\n");
	}

#ifdef _OSD_DEBUG_LOG
	if ( record_osd_cnt == OSD_LOG_CNT ) {
		for (int j = 0; j < OSD_LOG_CNT; j++) {
			printf("%d buf %d encode time %d blk %d %d %d %d %d %d \r\n", j, osd_log[j].buf_id, osd_log[j].time, osd_log[j].enable[0],
					osd_log[j].enable[1],osd_log[j].enable[2],osd_log[j].enable[3],osd_log[j].enable[4],osd_log[j].enable[5]);
			printf("0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\r\n", osd_log[j].blk_addr[0],
					osd_log[j].blk_addr[1],osd_log[j].blk_addr[2],osd_log[j].blk_addr[3],osd_log[j].blk_addr[4],osd_log[j].blk_addr[5]);

		}
		record_osd_cnt++;
	}
#endif

exit:
	return ret;
}

int rts_av_osdenc_get_profile(int chn_id,
			      struct rts_av_profile *profile)
{
	struct rts_av_osdenc_t *osdenc;

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);

	if (profile)
		memcpy(profile, &osdenc->profile, sizeof(*profile));

	return RTS_OK;
}

int rts_av_osdenc_set_profile(int chn_id, int buf_id,
			      struct rts_av_profile *profile)
{
	struct rts_av_osdenc_t *osdenc;
	struct rts_osd2_config config;
	int ret;

	if (!profile) {
		isp_error("rts_av_osdenc_set_profile profile==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	osdenc = &gbl_osdenc[chn_id];  //rts_av_get_unit_priv(unit);

	if (profile->fmt != RTS_V_FMT_YUV420SEMIPLANAR) {
		isp_error("rts_av_osdenc_set_profile format error: %x\n\r", profile->fmt);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (!profile->video.width || !profile->video.height) {
		isp_error("rts_av_osdenc_set_profile size error: %x %x\n\r", profile->video.width, profile->video.height);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	config.format = RTS_PIX_FMT_NV12;
	config.width = profile->video.width;
	config.height = profile->video.height;

	if (/*osdenc->posd[buf_id]*/0) {
		if (!memcmp(profile, &osdenc->profile, sizeof(*profile)))
			return RTS_OK;
		rts_osd2_update(osdenc->posd[buf_id], &config);
		goto next;
	}

	ret = rts_osd2_init(chn_id, buf_id, &osdenc->posd[buf_id], &config);  //mpalloc ewl & osd2 buffer
	if (RTS_IS_ERR(ret)) {
		isp_error("rts_av_osdenc_set_profile rts_osd2_init error: %x\n\r", ret);
		return ret;
	}

	rts_osd2_set_adma_copy(osdenc->posd[buf_id], RTS_AV_USE_ADMA);

	rts_av_set_osdenc_attr_owner(chn_id, buf_id, osdenc->posd[buf_id]);
next:
	memcpy(&osdenc->profile, profile, sizeof(*profile));

	rts_av_set_osdenc_fps(chn_id, buf_id, 
			      profile->video.numerator,
			      profile->video.denominator);
	return RTS_OK;
}

int rts_av_osdenc_exec_cmd(int chn_id, int buf_id, struct rts_av_cmd_t *pcmd)
{
	int ret = RTS_RETURN(RTS_E_NO_REALIZED);

	if (!pcmd)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = RTS_RETURN(RTS_E_NO_REALIZED);
	switch (pcmd->cmd_id) {
	case RTS_AV_CMD_QUERY_OSDENC_ATTR:
		if (pcmd->pdata) {
			struct rts_video_osd2_attr **ppattr = pcmd->pdata;

			ret = __query_osdenc_attr(chn_id, buf_id, ppattr);
		}
		break;
	default:
		ret = RTS_RETURN(RTS_E_NO_REALIZED);
		break;
	}

	return ret;
}

