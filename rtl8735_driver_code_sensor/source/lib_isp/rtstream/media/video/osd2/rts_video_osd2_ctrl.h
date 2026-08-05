/*
 * Realtek Semiconductor Corp.
 *
 * media/video/osd/rts_video_osd2_ctrl.h
 *
 * Copyright (C) 2017      Wil Shi<wil_shi@realsil.com.cn>
 */
#ifndef _MEDIA_RTS_VIDEO_OSD_CTRL_H
#define _MEDIA_RTS_VIDEO_OSD_CTRL_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <rtsosd2.h>

struct rts_av_osdenc_attr *rts_av_to_osdenc_t(int chn_id, int buf_id);
struct rts_video_osd2_attr *rts_av_to_osdenc_attr(int chn_id, int buf_id);
void rts_av_set_osdenc_attr(int chn_id, int buf_id, RtsOsd2Inst posd);
int rts_av_set_osdenc_attr_single(int chn_id, int buf_id, int blkidx);
int rts_av_get_osdenc_attr_single(int chn_id, int buf_id, int blkidx);
int rts_av_set_osdenc_attr_owner(int chn_id, int buf_id, RtsOsd2Inst posd);
int rts_av_update_osdenc_flick_info(int chn_id, int buf_id);
void rts_av_set_osdenc_fps(int chn_id, int buf_id,
			   uint32_t numerator, uint32_t denominator);

#ifdef __cplusplus
}
#endif
#endif
