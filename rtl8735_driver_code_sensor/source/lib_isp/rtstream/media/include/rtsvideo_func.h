/*
 * Realtek Semiconductor Corp.
 *
 * media/include/rtsvideo_func.h
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef __RTSVIDEO_FUNC_H
#define __RTSVIDEO_FUNC_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "rtsavfunc.h"

#define rts_video_cmd_id(dir, id)	rts_av_cmd_id('v', dir, id)
#define rts_video_cmd_n(id)		rts_video_cmd_id(RTS_CMD_DIR_N, id)
#define rts_video_cmd_r(id)		rts_video_cmd_id(RTS_CMD_DIR_R, id)
#define rts_video_cmd_w(id)		rts_video_cmd_id(RTS_CMD_DIR_W, id)
#define rts_video_cmd_rw(id)		rts_video_cmd_id(RTS_CMD_DIR_RW, id)

#define RTS_AV_CMD_QUERY_MD_ATTR	rts_video_cmd_rw(10)

#define RTS_AV_CMD_QUERY_MASK_ATTR	rts_video_cmd_rw(20)

#define RTS_AV_CMD_QUERY_OSD_ATTR	rts_video_cmd_rw(30)

#define RTS_AV_CMD_QUERY_H264_CTRL	rts_video_cmd_rw(40)
#define RTS_AV_CMD_H264_R_KEY		rts_video_cmd_rw(42)
#define RTS_AV_CMD_G_H264_INFO		rts_video_cmd_rw(43)
#define RTS_AV_CMD_G_H264_PROFILE	rts_video_cmd_rw(45)
#define RTS_AV_CMD_S_H264_COLOR_COEF	rts_video_cmd_rw(46)
#define RTS_AV_CMD_G_H264_CROP		rts_video_cmd_rw(47)
#define RTS_AV_CMD_S_H264_CROP		rts_video_cmd_rw(48)

#define RTS_AV_CMD_QUERY_JPG_CTRL	rts_video_cmd_rw(50)
#define RTS_AV_CMD_GET_JPG_CTRL		rts_video_cmd_rw(51)
#define RTS_AV_CMD_SET_JPG_CTRL		rts_video_cmd_rw(52)
#define RTS_AV_CMD_GET_JPGDEC_CTRL	rts_video_cmd_rw(53)
#define RTS_AV_CMD_SET_JPGDEC_CTRL	rts_video_cmd_rw(54)
#define RTS_AV_CMD_SET_JPG_LEVEL	rts_video_cmd_rw(55)

#define RTS_AV_CMD_QUERY_ROI		rts_video_cmd_rw(60)
#define RTS_AV_CMD_QUERY_H264_MV_INFO   rts_video_cmd_rw(61)
#define RTS_AV_CMD_QUERY_H264_VUI       rts_video_cmd_rw(62)
#define RTS_AV_CMD_QUERY_H264_BG_DETECT rts_video_cmd_rw(63)

#define RTS_AV_CMD_QUERY_AE_CTRL	rts_video_cmd_rw(80)
#define RTS_AV_CMD_QUERY_AWB_CTRL	rts_video_cmd_rw(83)
#define RTS_AV_CMD_QUERY_AF_CTRL	rts_video_cmd_rw(86)

#define RTS_AV_CMD_QUERY_OSDENC_ATTR	rts_video_cmd_rw(92)

#define RTS_AV_CMD_QUERY_ROI_MAP	rts_video_cmd_rw(100)
#define RTS_AV_CMD_QUERY_MB_MODE_MAP    rts_video_cmd_rw(101)

#define RTS_AV_CMD_REQUEST_KEY_FRAME	RTS_AV_CMD_H264_R_KEY

#define RTS_AV_CMD_QUERY_H265_ROI_MAP   rts_video_cmd_rw(110)

#define RTS_AV_CMD_QUERY_H265_CTU_MODE_MAP rts_video_cmd_rw(112)
#define RTS_AV_CMD_QUERY_H265_CTU_QP_MAP rts_video_cmd_rw(113)
#define RTS_AV_CMD_G_H265_INFO          rts_video_cmd_rw(115)
#define RTS_AV_CMD_QUERY_H265_MV_INFO   rts_video_cmd_rw(116)
#define RTS_AV_CMD_QUERY_H265_BG_DETECT rts_video_cmd_rw(117)
#define RTS_AV_CMD_QUERY_H265_VUI       rts_video_cmd_rw(118)
#define RTS_AV_CMD_QUERY_H265_3DNR      rts_video_cmd_rw(119)

#ifdef __cplusplus
}
#endif
#endif
