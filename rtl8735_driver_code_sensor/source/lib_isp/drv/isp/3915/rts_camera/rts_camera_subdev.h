/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_subdev.h
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_CAMERA_SUBDEV_H
#define _RTS_CAMERA_SUBDEV_H

#include "rts_camera_config.h"
#include "linux/rts_camera_soc.h"
#include "rts_camera_zoom.h"

struct rtscam_subdev_dev_desc {
	u8 length;
	u8 type;
	u16 hwversion;
	u16 fwversion;
	u8 streamnum;
	u8 frmivalnum;
};

struct rtscam_subdev_unit_desc {
	u8 length;
	u8 type;
	u8 controlsize;
	u8 bmcontrols[32];

	unsigned int ncontrols;
	struct rtscam_video_ctrl *controls;
};

enum {
	RTSCAM_EVT_FPS_DYNAMIC_CHANGED = 0,
	RTSCAM_EVT_RESERVED
};

struct rtscam_subdev_strm_desc {
	u32 format_bitmap;
	u32 width;
	u32 height;
};

enum {
	RTSCAM_SUBDEV_FPS_DISCRETE = 0,
	RTSCAM_SUBDEV_FPS_CONTINUOUS
};

struct rtscam_subdev_fps {
	u8 type;
	union {
		struct {
			u16 fps[RTSCAM_MAX_FPS_COUNT];
		} discrete;
		struct {
			u16 max;
			u16 min;
			u16 step;
		} stepwise;
	};
};


struct rtscam_subdev_desc {
	struct rtscam_subdev_dev_desc dev_desc;
	struct rtscam_subdev_unit_desc entities[3];
	struct rtscam_subdev_strm_desc strms[RTSCAM_MAX_STM_COUNT];
	struct rtscam_subdev_fps fps;
};

struct rtscam_subdev_crop_info {
	int mode;
	struct rtsv_rect rect;
};

struct rtscam_subdev_t {
	//struct device *dev;
	struct rtscam_subdev_desc desc;

	int (*enable)(struct rtscam_subdev_t *sub, int enable);
	int (*set_stream)(struct rtscam_subdev_t *sub,
			  int streamid, int enable);
	int (*pause_stream)(struct rtscam_subdev_t *sub,
			    int streamid, int resume);
	int (*set_fmt)(struct rtscam_subdev_t *sub, int streamid,
		       u32 fmt, u32 w, u32 h);
	int (*get_fmt)(struct rtscam_subdev_t *sub, int streamid,
		       u32 *fmt, u32 *w, u32 *h);
	int (*set_crop)(struct rtscam_subdev_t *sub, int streamid,
			struct rtscam_subdev_crop_info *crop);
	int (*get_crop)(struct rtscam_subdev_t *sub, int streamid,
			struct rtscam_subdev_crop_info *crop,
			int user_crop);
	int (*set_fps)(struct rtscam_subdev_t *sub, int streamid, u16 fps);
	int (*get_fps)(struct rtscam_subdev_t *sub, int streamid, u16 *fps);
	u32 (*read_reg)(struct rtscam_subdev_t *sub, off_t reg);
	void (*write_reg)(struct rtscam_subdev_t *sub, u32 value, off_t reg);
	int (*set_hook)(struct rtscam_subdev_t *sub, void *master,
			int (*hook)(void *master, int id, void *arg));
	int (*query_ctrl)(struct rtscam_subdev_t *sub, void *cmd);
	int (*exec_cmd)(struct rtscam_subdev_t *sub, void *cmd);

	int (*set_ive_ctrl)(struct rtscam_subdev_t *sub,
			    struct rtscam_soc_ive_ctrl *ctrl);
	int (*get_ive_ctrl)(struct rtscam_subdev_t *sub,
			    struct rtscam_soc_ive_ctrl *ctrl);
	int (*set_vinfo)(struct rtscam_subdev_t *sub,
			struct rtscam_soc_verify_info *info);
	void *master;
};

int rtscam_register_subdev(struct rtscam_subdev_t *subdev);
int rtscam_unregister_subdev(struct rtscam_subdev_t *subdev);

int rtscam_register_subdev_ext(struct rtscam_subdev_t *subdev);
int rtscam_unregister_subdev_ext(struct rtscam_subdev_t *subdev);

void rtscam_soc_isp_control(u8 idx, int enable);
void rtscam_soc_reset_isp_reg(u8 idx);

#endif
