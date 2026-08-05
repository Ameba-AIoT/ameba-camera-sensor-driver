/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_zoom.h
 *
 * Copyright (C) 2019      Grant Shen<grant_shen@realsil.com.cn>
 */
#ifndef _RTS_CAMERA_ZOOM_H
#define _RTS_CAMERA_ZOOM_H

#include "videodev2.h"
#include "rts_camera_isp_info.h"

struct rtscam_verify_info {
	__u8 fmt;
	__u8 scale_h;
	__u8 scale_v;
	__u32 width;
	__u32 height;
	__u32 phyaddr;
};

struct rtsv_rect {
	__s32   left;
	__s32   top;
	__u32   width;
	__u32   height;
};

struct rtscam_zoom_isp {
	//struct device *dev;
	struct rts_isp_info info;

	int (*set_fps)(struct rtscam_zoom_isp *isp, int fps);
	int (*set_mcrop)(struct rtscam_zoom_isp *isp,
			const struct rtsv_rect *crop);
	int (*set_hook)(struct rtscam_zoom_isp *isp, void *master,
			int (*hook)(void *master, int id, void *arg));
	//int (*set_clock)(struct rtscam_zoom_isp *isp, int enable);

	void *master;
};

int rtscam_zoom_register_isp(struct rtscam_zoom_isp *isp);
int rtscam_zoom_unregister_isp(struct rtscam_zoom_isp *isp);

struct rtscam_zoom_verify {
	//struct device *dev;

	int (*set_vinfo)(struct rtscam_zoom_verify *verify,
			struct rtscam_verify_info *vinfo);
	int (*reset_isp)(struct rtscam_zoom_verify *verify);

	int (*init)(struct rtscam_zoom_verify *verify);
	void (*cleanup)(struct rtscam_zoom_verify *verify);

	//int (*set_clock)(int enable);

	void *master;
};

int rtscam_zoom_register_verify(struct rtscam_zoom_verify *verify);
int rtscam_zoom_unregister_verify(struct rtscam_zoom_verify *verify);

int rtscam_zoom_probe(void);
#endif
