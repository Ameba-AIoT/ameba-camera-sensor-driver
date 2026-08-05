/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_fps.h
 *
 * Copyright (C) 2017      Wil shi<wil_shi@realsil.com.cn>
 */

#ifndef _RTS_CAMERA_FPS_H
#define _RTS_CAMERA_FPS_H

//#include <linux/workqueue.h>
#include <videodev2.h>
#include "rts_camera_config.h"

#define RTSCAM_SOC_MAX_FPS			300
#define RTSCAM_SOC_STEP_FPS			1

struct rtscam_soc_skip_info {
	int m;
	int n;
	int flag;
	int count;
	int index;
};

struct rtscam_soc_fps_descriptor {
	u16 fps[RTSCAM_MAX_FPS_COUNT];
	u16 length;
};

struct rtscam_sensor_fps {
	u32 sensor_fps_setting;
	u32 sensor_fps_actual;

	struct rtscam_frame_frmival *frmivals;
	struct rtscam_soc_fps_descriptor desc;

	u8 streamnum;
	int *streaming_count;
	struct rtscam_video_stream *streams;

	int flag_max;

	int (*set_fps)(struct rtscam_video_stream *stream, u32 fps);
	int (*set_fps_dynamic)(struct rtscam_video_stream *stream, u32 fps);
	int (*set_stream)(struct rtscam_video_stream *stream, int enable);
};

struct rtscam_video_fps {
	struct v4l2_fract user_setting;
	struct v4l2_fract user_actual;

	struct rtscam_soc_skip_info skip_info;

	struct rtscam_sensor_fps *sensor_fps;
};

void rtscam_set_user_fps(struct rtscam_video_fps *fps,
				u32 user_numerator, u32 user_denominator);
int rtscam_update_sensor_fps(struct rtscam_video_stream *stream, u32 fps);
void rtscam_adjust_sensor_fps(
			struct rtscam_video_stream *stream, int enable);
void rtscam_adjust_sensor_fps_dynamic(struct rtscam_video_stream *stream,
			u32 user_numerator, u32 user_denominator);
void rtscam_exec_sensor_fps_setting(
			struct rtscam_video_stream *stream, int enable);
void rtscam_enable_snr_fps_max(struct rtscam_sensor_fps *sensor_fps);
void rtscam_disable_snr_fps_max(struct rtscam_sensor_fps *sensor_fps);

int rtscam_change_dynamic_fps(struct rtscam_sensor_fps *sensor_fps, u16 fps);
int rtscam_skip_frame(struct rtscam_video_stream *stream);

int rtscam_init_sensor_fps(struct rtscam_sensor_fps *sensor_fps, int flag_max);
int rtscam_release_sensor_fps(struct rtscam_sensor_fps *sensor_fps);

struct rtscam_frame_size;
int rtscam_register_frmival_discrete(struct rtscam_video_stream *stream,
		__u32 fourcc, struct rtscam_frame_size *size);

#endif
