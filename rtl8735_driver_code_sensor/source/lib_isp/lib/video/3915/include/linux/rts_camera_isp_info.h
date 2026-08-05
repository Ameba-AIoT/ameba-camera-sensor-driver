/*
 * Realtek Semiconductor Corp.
 * ../../../../include/uapi/linux/rts_camera_isp_info.h
 * Copyright (C) 2014 Grant Shen <grant_shen@realsil.com.cn>
 */
#ifndef _U_RTS_CAMERA_ISP_INFO_H
#define _U_RTS_CAMERA_ISP_INFO_H

#include "rt_types.h"

/* MUST be same as struct isp_message */
struct rts_isp_msg_hdr {
	__u32 sequence; /* set by internal */
	__u32 msg_len;
	__u32 ret_len;
	__u32 isp_id;
	__u32 mod_id;
	__u32 action;
	__s32 ret_val;
	__u16 reloc_pos;
	__u16 reloc_num;
};

struct rts_isp_info {
	__u16 width;
	__u16 height;
	__u32 fps;
};

struct rts_isp_preview_info {
	__u16 fps;
};

struct rts_isp_statis_info {
	__u32 phy_addr;
	__u32 size;
	__u32 num;
};

struct rts_isp_statis_awb_reg {
	__u32 illum_white_pixels[6];
	__u32 fine_r_sum;
	__u32 fine_g_sum;
	__u32 fine_b_sum;
	__u32 fine_white_pixels;
};

struct rts_isp_statis_af_reg {
	__u32 num0;
	__u32 sum0;
	__u32 num1;
	__u32 sum1;
};

struct rts_isp_statis_flick_reg {
	__u32 fft_sum2_9;
	__u32 fft_sum2_127;
	__u32 valid;
};

struct rts_isp_statis_data {
	__u32 buf_id;

	__u32 frame_count;
	struct rts_isp_statis_awb_reg awb_reg;
	struct rts_isp_statis_af_reg af_reg;
	struct rts_isp_statis_flick_reg flick_reg;
};

#define _DRIVER_ACTC(dir, type, nr, size) \
	(__u32)((dir) << 30 | (size) << 16 | (type) << 8 | (nr) << 0)
#define _DRIVER_ACT(type, nr) _DRIVER_ACTC(0, type, nr, 0)
#define _DRIVER_ACTR(type, nr, size) _DRIVER_ACTC(1, type, nr, sizeof(size))
#define _DRIVER_ACTW(type, nr, size) _DRIVER_ACTC(2, type, nr, sizeof(size))
#define _DRIVER_ACTWR(type, nr, size) _DRIVER_ACTC(3, type, nr, sizeof(size))

#define RTS_ISP_EXEC_TYPE 'E'

enum rts_isp_driver_action {
	RTS_ISP_SET_FPS = _DRIVER_ACTW(RTS_ISP_EXEC_TYPE, 0,
				       struct rts_isp_preview_info),
	RTS_ISP_STATIS_DONE = _DRIVER_ACTW(RTS_ISP_EXEC_TYPE, 1,
					   struct rts_isp_statis_data),
};

#endif /* _U_RTS_CAMERA_ISP_INFO_H */
