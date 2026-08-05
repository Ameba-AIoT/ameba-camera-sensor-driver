/*
 * rtszoom device driver (kernel module)
 * Realtek Semiconductor Corp.
 * rts_camera_zoom.c
 * Copyright (C) 2014 Grant Shen <grant_shen@realsil.com.cn>
 */

//#define TAG "ZOOM"

#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include <linux/poll.h>
#include "rt_types.h"
#include "rt_util.h"
#include "rt_task.h"
#include "rts_errno.h"
#include <media/videobuf2-core.h>
#include "rlx_reg.h"

#include "rts_camera_isp_regs.h"
#include "linux/rts_camera_isp_info.h"
#include "rts_camera.h"
#include "rts_camera_zoom.h"
#include "rts_camera_isp_mfd.h"
#include "rts_camera_zoom_reg.h"
#include "rts_camera_subdev.h"
#include "rlx_bitops.h"
#include "rtx_mutex.h"
#include "rt_time.h"
#include "isp_debug.h"
#include "hal_isp.h"

#define RTS_ZOOM_DRV_NAME		"rts_zoom"
#define RTS_ZOOM_DEV_NAME		"rtszoom"

struct rtscam_zoom_info {
	__u32 zoom_src_w;
	__u32 zoom_src_h;
	__u32 zoom_dst_w;
	__u32 zoom_dst_h;
};

struct rtscam_zoom_stream_fmt {
	__u32 fmt;
	__u16 width;
	__u16 height;
};

#define RTS_ZOOM_MAX_STREAM		RTSCAM_MAX_STM_COUNT
#define RTS_ZOOM_RGB_YONLY_STREAM_ID	RTSCAM_RGB_YONLY_STRM_IDX
#define RTS_ZOOM_SRC_MAX_WIDTH		2592
#define RTS_ZOOM_SRC_MAX_HEIGHT		1944

struct rtscam_zoom_stream_info {
	__u32 stream_num;
	struct rtscam_zoom_stream_fmt fmt[RTS_ZOOM_MAX_STREAM];
};

struct rtscam_zoom {
	//struct device *dev;
	//struct rtscam_ge_device *gdev;
	osMutexId_t lock;

	struct rtscam_isp_mfd *mfd;

	struct rtscam_subdev_t subdev;

	struct rtscam_zoom_isp *isp;
	struct rtscam_zoom_verify *verify;

	//void *reg_base;

	struct rtscam_zoom_stream_info dt_stream_info;
	struct rtscam_zoom_stream_info stream_info;

	int (*hook)(void *master, int id, void *arg);
	void *master;

	unsigned long streaming;
	u16 current_fps;
	struct rtscam_zoom_stream_fmt current_fmt[RTS_ZOOM_MAX_STREAM];
	struct rtsv_rect crop_info[RTS_ZOOM_MAX_STREAM];
	struct rtsv_rect last_crop_info[RTS_ZOOM_MAX_STREAM];

	char subdev_type[20];
	u32 system_reg_val[9];

	bool zoom_in_enable;
	bool zoom_in_flag;
};

static struct rtscam_zoom gbl_rtszoom={0};
static struct rtscam_zoom *m_rtszoom;

static bool rtsv_rect_contain(struct rtsv_rect *r1, struct rtsv_rect *r2)
{
	return (r1->left <= r2->left && r1->top <= r2->top &&
		r1->left + r1->width >= r2->left + r2->width &&
		r1->top + r1->height >= r2->top + r2->height);
}

static int __subdev_is_verify(void)
{
	if (!m_rtszoom)
		return -EINVAL;

	if (!strcmp(m_rtszoom->subdev_type, "verify"))
		return 1;
	return 0;
}

static int __subdev_is_isp(void)
{
	if (!m_rtszoom)
		return -EINVAL;

	if (!strcmp(m_rtszoom->subdev_type, "isp"))
		return 1;
	return 0;
}

static inline u32 rtscam_zoom_read_reg(struct rtscam_zoom *zoom, u32 offset)
{
	//return REG_R32(zoom->reg_base + offset);
	return zoom->mfd->read_reg(zoom->mfd, RTS_MFD_MODUAL_ID_ZOOM, offset);
}

static inline void rtscam_zoom_write_reg(struct rtscam_zoom *zoom,
					 u32 value, u32 offset)
{
	//REG_W32(zoom->reg_base + offset, value);
	zoom->mfd->write_reg(zoom->mfd, RTS_MFD_MODUAL_ID_ZOOM, offset, value);
}

static inline int __get_zoom_reg_offset(struct rtscam_zoom *zoom, int stream_id)
{
	int fmt;

	fmt = zoom->current_fmt[stream_id].fmt;
	if (fmt == RTSCAM_FORMAT_TYPE_RGB || fmt == RTSCAM_FORMAT_TYPE_Y_ONLY)
		stream_id = RTS_ZOOM_RGB_YONLY_STREAM_ID;
	return stream_id * ZOOM_CH_REG_OFFSET;
}

#define ZOOM_FILTER_COEF_NUM 20
static u8 zoom_filter_for_scale_down[13][ZOOM_FILTER_COEF_NUM] = {
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 255, 255, 255,
		255
	},
	{
		16, 16, 15, 14, 12, 9, 6, 2, 0, 0, 5, 15, 31, 52, 78, 105, 133,
		156, 175, 184
	},
	{
		9, 8, 7, 6, 3, 2, 0, 0, 2, 7, 16, 29, 46, 66, 89, 112, 133,
		152, 165, 172
	},
	{
		7, 6, 5, 4, 2, 0, 0, 1, 4, 10, 20, 33, 50, 70, 91, 112, 132,
		149, 161, 167
	},
	{
		3, 3, 2, 1, 0, 0, 1, 3, 8, 16, 26, 40, 56, 74, 93, 112, 130,
		143, 154, 159
	},
	{
		2, 1, 1, 0, 0, 0, 2, 5, 11, 19, 30, 44, 59, 76, 94, 111, 127,
		140, 149, 153
	},
	{
		0, 0, 1, 1, 3, 5, 9, 14, 21, 30, 40, 52, 65, 79, 92, 105, 116,
		125, 131, 135
	},
	{
		3, 3, 4, 7, 10, 14, 19, 25, 32, 41, 50, 59, 68, 78, 86, 95,
		101, 107, 110, 112
	},
	{
		4, 5, 6, 9, 12, 17, 22, 28, 36, 43, 51, 60, 69, 77, 84, 91, 97,
		102, 105, 106
	},
	{
		6, 7, 9, 11, 15, 19, 25, 31, 38, 45, 53, 61, 68, 76, 82, 88,
		93, 97, 99, 101
	},
	{
		7, 8, 9, 13, 16, 21, 26, 33, 39, 46, 54, 61, 68, 75, 81, 86,
		91, 95, 97, 98
	},
	{
		7, 8, 10, 13, 17, 21, 27, 33, 40, 47, 54, 61, 68, 75, 81, 86,
		90, 93, 96, 97
	},
	// Verify Path
	{
		0, 0, 1, 1, 3, 5, 9, 14, 21, 30, 40, 52, 65, 79, 92, 105, 116,
		125, 131, 135
	},
};
static const u8 zoom_filter_for_scale_up[ZOOM_FILTER_COEF_NUM] = {
	18, 18, 18, 18, 16, 13, 9, 5, 1, 0, 3, 10, 25, 46, 72, 101, 131, 157,
	176, 187
};

static const u8 *get_zoom_filter(u32 scale, u32 manual)
{
	if (manual)
		return zoom_filter_for_scale_down[12];
	if (scale >= 1365 * 16)
		return zoom_filter_for_scale_down[11];
	if (scale >= 518 * 16)
		return zoom_filter_for_scale_down[10];
	if (scale >= 341 * 16)
		return zoom_filter_for_scale_down[9];
	if (scale >= 256 * 16)
		return zoom_filter_for_scale_down[8];
	if (scale >= 192 * 16)
		return zoom_filter_for_scale_down[7];
	if (scale >= 128 * 16)
		return zoom_filter_for_scale_down[6];
	if (scale >= 101 * 16)
		return zoom_filter_for_scale_down[5];
	if (scale >= 96 * 16)
		return zoom_filter_for_scale_down[4];
	if (scale >= 86 * 16)
		return zoom_filter_for_scale_down[3];
	if (scale >= 81 * 16)
		return zoom_filter_for_scale_down[2];
	if (scale >= 68 * 16)
		return zoom_filter_for_scale_down[1];
	if (scale == 64 * 16)
		return zoom_filter_for_scale_down[0];
	return zoom_filter_for_scale_up;
}

void rtscam_zoom_set_filter_coef(u8 *coeff)
{
	int i;

	for (i = 0; i < ZOOM_FILTER_COEF_NUM; i++) {
		zoom_filter_for_scale_down[12][i] = coeff[i];
	}
}

static int rtscam_zoom_set_zoom_filter(struct rtscam_zoom *zoom,
					     int stream_id, u32 scale)
{
	unsigned long i;
	u32 offset;
	const u8 *filter = NULL;

	if (!hal_isp_is_verify_path_on())
		filter = get_zoom_filter(scale, 0);
	else
		filter = get_zoom_filter(scale, 1);

	for (i = 0, offset = ZOOM_CH0_COEF0 +
			__get_zoom_reg_offset(zoom, stream_id);
			i < ZOOM_FILTER_COEF_NUM; i += 4, offset += 4) {
		u32 filter_value;

		filter_value = (filter[i] | filter[i + 1] << 8 |
				filter[i + 2] << 16 | filter[i + 3] << 24);
		rtscam_zoom_write_reg(zoom, filter_value, offset);
	}

	return 0;
}

static void rtscam_zoom_refine_streams_settings(struct rtscam_zoom *zoom)
{
	int i;
	int x_offset;
	int y_offset;
	u32 val;

	if (!zoom->zoom_in_flag)
		return;

	x_offset = zoom->crop_info[0].left - zoom->last_crop_info[0].left;
	y_offset = zoom->crop_info[0].top - zoom->last_crop_info[0].top;
	for (i = 1; i < RTS_ZOOM_MAX_STREAM; i++) { //refine stream 1~4

		zoom->crop_info[i].left += x_offset;
		zoom->crop_info[i].top += y_offset;

		if (zoom->streaming & (1<<i)) {
			if (zoom->crop_info[i].left < zoom->crop_info[0].left) {
				isp_error("stream %d crop_left: %d, mcrop_left: %d\n\r", i, zoom->crop_info[i].left, zoom->crop_info[0].left);
			}
			if (zoom->crop_info[i].top < zoom->crop_info[0].top) {
				isp_error("stream %d crop_top: %d, mcrop_top: %d\n\r", i, zoom->crop_info[i].top, zoom->crop_info[0].top);
			}
			val = zoom->crop_info[0].left + zoom->crop_info[0].width - zoom->crop_info[i].left;
			if (val < zoom->crop_info[i].width) {
				isp_error("stream %d crop_w: %d, mcrop_w: %d\n\r", i, zoom->crop_info[i].width, val);
			}
			val = zoom->crop_info[0].top + zoom->crop_info[0].height - zoom->crop_info[i].top;
			if (val < zoom->crop_info[i].height) {
				isp_error("stream %d crop_h: %d, mcrop_h: %d\n\r", i, zoom->crop_info[i].height, val);
			}
		}

		zoom->crop_info[i].left =
			max(zoom->crop_info[i].left, zoom->crop_info[0].left);
		zoom->crop_info[i].top =
			max(zoom->crop_info[i].top, zoom->crop_info[0].top);
		zoom->crop_info[i].width = min(zoom->crop_info[i].width,
					       (zoom->crop_info[0].left +
						zoom->crop_info[0].width -
						zoom->crop_info[i].left));
		zoom->crop_info[i].height = min(zoom->crop_info[i].height,
						(zoom->crop_info[0].top +
						 zoom->crop_info[0].height -
						 zoom->crop_info[i].top));
		zoom->last_crop_info[i] = zoom->crop_info[i];
	}
}

static int rtscam_zoom_set_zoom(struct rtscam_zoom *zoom, int stream_id)
{
	u32 up_en;
	u16 src_w, src_h;
	u16 dest_w, dest_h;
	u32 scale_h, scale_v;
	u32 crop_start_x, crop_start_y;
	u32 ch_offset = __get_zoom_reg_offset(zoom, stream_id);
	u32 ch_reg_offset;
	u32 tmp_w, tmp_h, diff = 0;
	struct rtsv_rect crop;
	BOOL keep_h = FALSE;
	BOOL change_mcrop_zoom_seq = FALSE;
	int i;

	crop_start_x = zoom->crop_info[stream_id].left;
	crop_start_y = zoom->crop_info[stream_id].top;
	src_w = zoom->crop_info[stream_id].width;
	src_h = zoom->crop_info[stream_id].height;

	if (zoom->crop_info[stream_id].width == 0 || zoom->crop_info[stream_id].height == 0) {

		if (!zoom->zoom_in_flag) {
			crop_start_x = 0;
			crop_start_y = 0;
			src_w = zoom->isp->info.width;
			src_h = zoom->isp->info.height;
		} else {
			if (stream_id == 0) {
				zoom->crop_info[stream_id].left = zoom->last_crop_info[0].left;
				zoom->crop_info[stream_id].top = zoom->last_crop_info[0].top;
				zoom->crop_info[stream_id].width = zoom->last_crop_info[0].width;
				zoom->crop_info[stream_id].height = zoom->last_crop_info[0].height;
			}

			crop_start_x = zoom->last_crop_info[0].left;
			crop_start_y = zoom->last_crop_info[0].top;
			src_w = zoom->last_crop_info[0].width;
			src_h = zoom->last_crop_info[0].height;
		}

		printf("zoom crop default setting\n\r");
	}

	if (src_w + crop_start_x > zoom->isp->info.width ||
			src_h + crop_start_y > zoom->isp->info.height) {
		isp_error("zoom crop setting error src %d %d crop %d %d \n\r", src_w, src_h, crop_start_x, crop_start_y);
		return ERR_ID_DRV_ZOOM_ROI_OUT_RANGE;
	}

	dest_w = zoom->current_fmt[stream_id].width;
	dest_h = zoom->current_fmt[stream_id].height;

	//isp_info("%s start %d %d src %d %d dest %d %d  \r\n",__FUNCTION__, crop_start_x, crop_start_y, src_w, src_h, dest_w, dest_h);

	scale_h = ((src_w << 10) / dest_w);
	scale_v = ((src_h << 10) / dest_h);

	if ((zoom->crop_info[stream_id].width == 0 || zoom->crop_info[stream_id].height == 0)) {
		if (scale_h > scale_v) {
			scale_h = scale_v;
			keep_h = TRUE;
		}
		else {
			scale_v = scale_h;
			keep_h = FALSE;
		}
	}

	if (scale_h > 0x1ffff || scale_v > 0x1ffff) {
		isp_error("scaling scale error h %d v %d\n\r", scale_h, scale_v);
		return ERR_ID_DRV_ZOOM_SCALE_DW_OUT_RANGE;
	}

	if (stream_id && (scale_h < 0x400 || scale_v < 0x400)) {
		isp_error("scaling up error stream %d \n\r", stream_id);
		return ERR_ID_DRV_ZOOM_SCALE_UP_OUT_RANGE;
	}

	if ((scale_h > 0x400 && scale_v < 0x400) ||
	    (scale_h < 0x400 && scale_v > 0x400)) {
			isp_error("scaling scale error h %d v %d\n\r", scale_h, scale_v);
			return ERR_ID_DRV_ZOOM_1SIDE_UP_1SIDE_DW;
		}

	if ((zoom->crop_info[stream_id].width == 0 || zoom->crop_info[stream_id].height == 0)) {
		if (keep_h) {
			tmp_h = src_h;
			tmp_w = src_h * dest_w / dest_h;
		} else {
			tmp_w = src_w;
			tmp_h = src_w * dest_h / dest_w;
		}

		if (tmp_w > src_w) {
			diff = 0;
			tmp_w = src_w;
		}
		else
			diff = src_w - tmp_w;

		crop_start_x += (diff >> 1);

		if (tmp_h > src_h) {
			diff = 0;
			tmp_h = src_h;
		}
		else
			diff = src_h - tmp_h;

		crop_start_y += (diff >> 1);

		crop_start_x = ((crop_start_x+1) >> 1) << 1;
		crop_start_y = ((crop_start_y+1) >> 1) << 1;
		tmp_w = ((tmp_w+1) >> 1) << 1;
		tmp_h = ((tmp_h+1) >> 1) << 1;
		printf("cropw: %d, croph: %d\n\r", tmp_w, tmp_h);

		zoom->crop_info[stream_id].left = crop_start_x;
		zoom->crop_info[stream_id].top = crop_start_y;
		zoom->crop_info[stream_id].width = tmp_w;
		zoom->crop_info[stream_id].height = tmp_h;

	}

	if (zoom->zoom_in_flag) {
		if (stream_id) {
			if (!rtsv_rect_contain(&zoom->last_crop_info[0],
					       &zoom->crop_info[stream_id])) {
				/*rtsprintk(RTS_TRACE_ERROR,
					  "crop set range error!\n");*/
				isp_error("scaling up error stream %d \n\r", stream_id);
				return ERR_ID_DRV_ZOOM_SCALE_UP_OTHER_CH_ROI_OUT_RANGE;
			}
		}
	}

	up_en = scale_h < 0x400 || scale_v < 0x400;
	//If streaming begins at 1x and needs to scale up, then up_en should be set to 1
	//to avoid switching from scale down to scale up.
	if (!stream_id && (scale_h == 0x400 && scale_v == 0x400) && hal_isp_get_zoom_1x1_up_en())
		up_en = 1;

	//Due to hardware limitations, when zooming back to 1x, DIC recommends keeping up_en set to 1
	//and not dynamically resetting it to 0.
	if (!stream_id && zoom->zoom_in_flag)
		up_en = 1;

	if (up_en && !(zoom->streaming & 0x1) && (zoom->streaming & ~1)) {
		if (zoom->crop_info[0].left !=
				zoom->last_crop_info[0].left ||
			zoom->crop_info[0].top !=
				zoom->last_crop_info[0].top ||
			zoom->crop_info[0].width !=
				zoom->last_crop_info[0].width ||
			zoom->crop_info[0].height !=
				zoom->last_crop_info[0].height) {
			rtsprintk(RTS_TRACE_ERROR,
				  "Please stop stream before switching zoom in\n");
			return ERR_ID_DRV_ZOOM_STREAM_RUN_BEFORE_ZOOM_IN;
		}
	}

	if (up_en) {
		if (zoom->crop_info[0].width <
				zoom->last_crop_info[0].width ||
			zoom->crop_info[0].height <
				zoom->last_crop_info[0].height) {

			change_mcrop_zoom_seq = TRUE;
		}
	}

	if (up_en) {
		if (!stream_id) {
			zoom->zoom_in_flag = up_en;
			rtscam_zoom_refine_streams_settings(zoom);
		}

		if (!stream_id && zoom->isp->set_mcrop && change_mcrop_zoom_seq == FALSE) {
			crop.left = zoom->crop_info[stream_id].left;
			crop.top = zoom->crop_info[stream_id].top;
			crop.width = zoom->crop_info[stream_id].width;
			crop.height = zoom->crop_info[stream_id].height;
			printf("scale up set_mcrop: mcrop -> zoom\n\r");

			zoom->isp->set_mcrop(zoom->isp, &crop);
		}
	}

	zoom->last_crop_info[stream_id] = zoom->crop_info[stream_id];

	if (!zoom->zoom_in_flag) {
		crop.left = 0;
		crop.top = 0;
		crop.width = zoom->isp->info.width;
		crop.height = zoom->isp->info.height;
		printf("scale down set_mcrop\n\r");

		zoom->isp->set_mcrop(zoom->isp, &crop);
	}

	rtscam_zoom_write_reg(zoom, up_en, ZOOM_CH0_SCALE_UP_EN + ch_offset);

	if (zoom->isp->set_mcrop && zoom->zoom_in_flag) {
		rtscam_zoom_write_reg(
			zoom,
			((crop_start_y - zoom->last_crop_info[0].top) << 16 |
			 (crop_start_x - zoom->last_crop_info[0].left)),
			ZOOM_CH0_CROP_START + ch_offset);

			//after refine, need to set zoom register of ch1 - ch4
			if (!stream_id) {
				for (i = 1; i < RTS_ZOOM_MAX_STREAM; i++) {
					ch_reg_offset = __get_zoom_reg_offset(zoom, i);

					rtscam_zoom_write_reg(
					zoom,
					((zoom->last_crop_info[i].top - zoom->last_crop_info[0].top) << 16 |
					 (zoom->last_crop_info[i].left - zoom->last_crop_info[0].left)),
					ZOOM_CH0_CROP_START + ch_reg_offset);
				}
			}

	} else {

		rtscam_zoom_write_reg(zoom, (crop_start_y << 16 | crop_start_x),
				      ZOOM_CH0_CROP_START + ch_offset);
	}

	rtscam_zoom_write_reg(zoom, (dest_w | dest_h << 16),
			      ZOOM_CH0_OUTPUT_SIZE + ch_offset);
	rtscam_zoom_write_reg(zoom, scale_h, ZOOM_CH0_STEP_H + ch_offset);
	rtscam_zoom_write_reg(zoom, scale_v, ZOOM_CH0_STEP_V + ch_offset);
	rtscam_zoom_set_zoom_filter(zoom, stream_id, min(scale_h, scale_v));
	rtscam_zoom_write_reg(zoom, LOAD_ZOOM_PARAM,
			      ZOOM_CH0_REG_LOAD + ch_offset);

	//after refine, need to set zoom register of ch1 - ch4
	if (zoom->isp->set_mcrop && zoom->zoom_in_flag) {
		if (!stream_id) {
			for (i = 1; i < RTS_ZOOM_MAX_STREAM; i++) {
				ch_reg_offset = __get_zoom_reg_offset(zoom, i);

				dest_w = zoom->current_fmt[i].width;
				dest_h = zoom->current_fmt[i].height;
				if (dest_w == 0 || dest_h == 0)
					continue;

				src_w = zoom->last_crop_info[i].width;
				src_h = zoom->last_crop_info[i].height;

				scale_h = ((src_w << 10) / dest_w);
				scale_v = ((src_h << 10) / dest_h);

				rtscam_zoom_write_reg(zoom, scale_h, ZOOM_CH0_STEP_H + ch_reg_offset);
				rtscam_zoom_write_reg(zoom, scale_v, ZOOM_CH0_STEP_V + ch_reg_offset);
				rtscam_zoom_set_zoom_filter(zoom, i, min(scale_h, scale_v));
				rtscam_zoom_write_reg(zoom, LOAD_ZOOM_PARAM,
			      ZOOM_CH0_REG_LOAD + ch_reg_offset);
			}
		}
	}

	if (up_en) {

		if (!stream_id && zoom->isp->set_mcrop && change_mcrop_zoom_seq == TRUE) {
			crop.left = zoom->crop_info[stream_id].left;
			crop.top = zoom->crop_info[stream_id].top;
			crop.width = zoom->crop_info[stream_id].width;
			crop.height = zoom->crop_info[stream_id].height;
			printf("scale up set_mcrop: zoom -> mcrop\n\r");

			zoom->isp->set_mcrop(zoom->isp, &crop);
		}
	}

	return 0;
}

static int rtscam_zoom_enable_zoom(struct rtscam_zoom *zoom, int stream_id)
{
	int ret;
	u32 tmp;
	u32 zoom_ctrl_reg = ZOOM_CH0_CTRL +
			__get_zoom_reg_offset(zoom, stream_id);

	//isp_info("%s stream_id %d \r\n",__FUNCTION__, stream_id);
	if (zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_YUV420_SEMIPLANAR) {
		tmp = rtscam_zoom_read_reg(zoom, SYS_IMAGE_MODE_SEL);
		rtscam_zoom_write_reg(zoom, tmp & ~(1 << stream_id),
				      SYS_IMAGE_MODE_SEL);
	} else if ((zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_YUV422_SEMIPLANAR) ||
		   (zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_YUYV) ||
		   (zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_YVYU)) {
		tmp = rtscam_zoom_read_reg(zoom, SYS_IMAGE_MODE_SEL);
		rtscam_zoom_write_reg(zoom, tmp | (1 << stream_id),
				      SYS_IMAGE_MODE_SEL);
	} else if (zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_RGB) {
		rtscam_zoom_write_reg(zoom, 1, SYS_IMAGE_AI_CHAN_SEL);
	} else if (zoom->current_fmt[stream_id].fmt ==
				RTSCAM_FORMAT_TYPE_Y_ONLY) {
		rtscam_zoom_write_reg(zoom, 0, SYS_IMAGE_AI_CHAN_SEL);
	} else {
		isp_error("%s error\n", __func__);
		return -EINVAL;
	}

	ret = rtscam_zoom_set_zoom(zoom, stream_id);
	if (ret)
		return ret;

	rtscam_zoom_write_reg(zoom, ENABLE_ZOOM, zoom_ctrl_reg);

	return 0;
}

static int rtscam_zoom_disable_zoom(struct rtscam_zoom *zoom, int stream_id)
{
	u32 count = 30;
	u32 zoom_ctrl;
	u32 zoom_ctrl_reg = ZOOM_CH0_CTRL +
			__get_zoom_reg_offset(zoom, stream_id);
	u32 sys_idle_reg = SYS_IDLE, sys_idle_val = 0;

	sys_idle_val = (rtscam_zoom_read_reg(zoom, sys_idle_reg) >> 2) & 0x01;//zoom idle

	zoom_ctrl = rtscam_zoom_read_reg(zoom, zoom_ctrl_reg) | DISABLE_ZOOM;
	rtscam_zoom_write_reg(zoom, zoom_ctrl, zoom_ctrl_reg);

	if ( !hal_isp_is_verify_path_on() || sys_idle_val != 1) {

		if ( hal_isp_is_verify_path_on() )
			printf("streaming when verify path disable zoom\n");

		while (count--) {
			if (!(rtscam_zoom_read_reg(zoom, zoom_ctrl_reg) & DISABLE_ZOOM))
				break;
			mdelay(10);  //usleep_range(10000, 11000);
		}
	}

	return 0;
}

static int rtscam_zoom_enable_stream(struct rtscam_zoom *zoom, int stream_id)
{
	int ret;
#ifdef _FPS_LOG_
	printf("%s fps %d stream %ld \r\n",__FUNCTION__, zoom->current_fps, zoom->streaming);
#endif
	if (zoom->streaming & (1 << stream_id))
		return -EBUSY;

	if (!zoom->current_fps) {
		isp_error("set non-zero fps first\n");
		return -EPERM;
	}

	if (!zoom->streaming) {
		ret = zoom->isp->set_fps(zoom->isp, zoom->current_fps);
		if (ret){
			isp_error("%s zoom->isp->set_fps %d ret: %d \r\n",__FUNCTION__, zoom->current_fps, ret);
			return ret;
		}

	}

	ret = rtscam_zoom_enable_zoom(zoom, stream_id);
	if (ret) {
		isp_error("%s rtscam_zoom_enable_zoom error %d \r\n",__FUNCTION__, ret);
		if (!zoom->streaming) {
			zoom->isp->set_fps(zoom->isp, 0);
			zoom->zoom_in_flag = false;
		}
		return ret;
	}

	set_bit(stream_id, &zoom->streaming);

	return 0;
}

static int rtscam_zoom_set_isp_clock(
			struct rtscam_zoom *zoom, int enable)
{
	//dbg_printf("%s %d\r\n", __func__, enable);
	return zoom->mfd->set_clk(zoom->mfd, enable);
}


static int rtscam_zoom_disable_stream(struct rtscam_zoom *zoom, int stream_id)
{
	int ret;

	if ((zoom->streaming & (1 << stream_id)) == 0)
		return 0;

	ret = rtscam_zoom_disable_zoom(zoom, stream_id);
	if (ret) {
		isp_error("s%d disable zoom fail %d \n", stream_id, ret);
		return ret;
	}
	isp_info("%s streaming 0x%08x s%d disable \r\n", __func__, zoom->streaming, stream_id);
	clear_bit(stream_id, &zoom->streaming);
	if (!zoom->streaming) {
		ret = zoom->isp->set_fps(zoom->isp, 0);
		zoom->zoom_in_flag = false;
		if (ret) {
			isp_error("%s set_fps 0 failed %d \n", __func__, ret);
		}
	}

	return ret;
}

static int __zoom_verify_set_stream(struct rtscam_subdev_t *subdev,
					 int stream_id, int enable)
{
	struct rtscam_zoom *zoom;

	if (!subdev)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (enable)
	//	zoom->verify->set_clock(1);
		rtscam_zoom_set_isp_clock(zoom, 1);

	/*for switch isp and verify dynamically, not to reset isp here*/
	/*zoom->verify->reset_isp(zoom->verify);*/

	rtscam_zoom_write_reg(zoom, 1, RTS_ZOOM_REG_SYS_IMAGE_AI_CHAN_SEL);
	rtscam_zoom_write_reg(zoom, 0x100, RTS_ZOOM_REG_SYS_DATA_DELAY);
	rtscam_zoom_write_reg(zoom, 0x10, RTS_ZOOM_REG_SYS_CONTROL0);
	rtscam_zoom_write_reg(zoom, 0, RTS_ZOOM_REG_SYS_IMAGE_SEL0);
	rtscam_zoom_write_reg(zoom, 2, RTS_ZOOM_REG_SYS_CONTROL1);

	if (!enable)
	//	zoom->verify->set_clock(0);
		rtscam_zoom_set_isp_clock(zoom, 0);

	return 0;
}

static int rtscam_zoom_subdev_set_stream(struct rtscam_subdev_t *subdev,
					 int stream_id, int enable)
{
	int ret;
	struct rtscam_zoom *zoom;

	if (!subdev)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (__subdev_is_verify())
		return __zoom_verify_set_stream(subdev, stream_id, enable);

	if (!zoom->isp)
		return -EINVAL;

	if (stream_id < 0 || stream_id >= (int)zoom->stream_info.stream_num)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_stream wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	//zoom->isp->set_clock(zoom->isp, 1);
	rtscam_zoom_set_isp_clock(zoom, 1);
	if (enable)
		ret = rtscam_zoom_enable_stream(zoom, stream_id);
	else
		ret = rtscam_zoom_disable_stream(zoom, stream_id);
	//zoom->isp->set_clock(zoom->isp, 0);
	rtscam_zoom_set_isp_clock(zoom, 0);
	xSemaphoreGive(zoom->lock);

	return ret;
}

static int rtscam_zoom_subdev_enable(struct rtscam_subdev_t *subdev, int enable)
{
	return 0;
}

static int rtscam_zoom_subdev_set_fmt(struct rtscam_subdev_t *subdev,
				      int stream_id, u32 rts_code, u32 w, u32 h)
{
	int ret = 0;
	struct rtscam_zoom *zoom;

	if (!subdev)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_fmt wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (stream_id >= (int)zoom->stream_info.stream_num) {
		ret = -EINVAL;
		goto out;
	}
	if (!w || w > zoom->stream_info.fmt[stream_id].width ||
	    !h || h > zoom->stream_info.fmt[stream_id].height ||
	    (rts_code & zoom->stream_info.fmt[stream_id].fmt) == 0) {
		ret = -EINVAL;
		goto out;
	}
	if (zoom->streaming & (1 << stream_id)) {
		ret = -EBUSY;
		goto out;
	}

	zoom->current_fmt[stream_id].fmt = rts_code;
	zoom->current_fmt[stream_id].width = w;
	zoom->current_fmt[stream_id].height = h;

out:
	xSemaphoreGive(zoom->lock);

	return ret;
}

static int rtscam_zoom_subdev_set_fps(struct rtscam_subdev_t *subdev,
					int stream_id, u16 fps)
{
	int ret = 0;
	struct rtscam_zoom *zoom;

	if (!subdev || !fps)
		return -EINVAL;
	isp_info("%s fps %d \r\n",__FUNCTION__, fps);

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_fps wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	if (stream_id < 0 || stream_id >= (int)zoom->stream_info.stream_num) {
		ret = -EINVAL;
		goto out;
	}

	if (__subdev_is_isp()) {
		if (!zoom->isp || fps > zoom->isp->info.fps) {
			ret = -EINVAL;
			goto out;
		}

		if (zoom->streaming) {
			ret = zoom->isp->set_fps(zoom->isp, fps);
			if (ret)
				goto out;
		}
	}
#ifdef _FPS_LOG_
	printf("%s zoom->current_fps %d \r\n",__FUNCTION__, fps);
#endif
	zoom->current_fps = fps;
out:
	xSemaphoreGive(zoom->lock);

	return ret;
}

static int
rtscam_zoom_subdev_set_hook(struct rtscam_subdev_t *subdev, void *master,
			    int (*hook)(void *master, int id, void *arg))
{
	struct rtscam_zoom *zoom;

	if (!subdev)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	/* do not use lock here */
	zoom->hook = hook;
	zoom->master = master;

	return 0;
}

static int rtscam_zoom_subdev_get_ive_ctrl(struct rtscam_subdev_t *subdev,
					   struct rtscam_soc_ive_ctrl *ctrl)
{
	u32 val_norm_mean;
	struct rtscam_zoom *zoom;

	if (!subdev || !ctrl)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_get_ive_ctrl wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	//zoom->isp->set_clock(zoom->isp, 1);
	rtscam_zoom_set_isp_clock(zoom, 1);
	ctrl->enable = rtscam_zoom_read_reg(zoom, IVE_ENABLE);
	val_norm_mean = rtscam_zoom_read_reg(zoom, IVE_NORM_MEAN);
	ctrl->normal_mean.r = val_norm_mean & 0xff;
	ctrl->normal_mean.g = (val_norm_mean >> 8) & 0xff;
	ctrl->normal_mean.b = (val_norm_mean >> 16) & 0xff;
	ctrl->normal_scale =
		rtscam_zoom_read_reg(zoom, IVE_NORM_SCALE) & 0xffff;
	ctrl->quant_len = rtscam_zoom_read_reg(zoom, IVE_QUANT_LEN) & 0x1f;
	ctrl->asym_inv_scale =
		rtscam_zoom_read_reg(zoom, IVE_ASYM_INV_SCALE) & 0x3ffff;
	ctrl->asym_zero_point =
		rtscam_zoom_read_reg(zoom, IVE_ASYM_ZERO_POINT) & 0xff;
	//zoom->isp->set_clock(zoom->isp, 0);
	rtscam_zoom_set_isp_clock(zoom, 0);

	xSemaphoreGive(zoom->lock);

	return 0;
}

static int rtscam_zoom_subdev_set_ive_ctrl(struct rtscam_subdev_t *subdev,
					   struct rtscam_soc_ive_ctrl *ctrl)
{
	u32 val_norm_mean;
	struct rtscam_zoom *zoom;

	if (!subdev || !ctrl)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_ive_ctrl wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	val_norm_mean = (ctrl->normal_mean.r & 0xff) |
		((ctrl->normal_mean.g & 0xff) << 8) |
		((ctrl->normal_mean.b & 0xff) << 16);

	//zoom->isp->set_clock(zoom->isp, 1);
	rtscam_zoom_set_isp_clock(zoom, 1);

	rtscam_zoom_write_reg(zoom, val_norm_mean, IVE_NORM_MEAN);
	rtscam_zoom_write_reg(zoom, ctrl->normal_scale & 0xffff,
			      IVE_NORM_SCALE);
	rtscam_zoom_write_reg(zoom, ctrl->quant_len & 0x1f,
			      IVE_QUANT_LEN);
	rtscam_zoom_write_reg(zoom, ctrl->asym_inv_scale & 0x3ffff,
			      IVE_ASYM_INV_SCALE);
	rtscam_zoom_write_reg(zoom, ctrl->asym_zero_point & 0xff,
			      IVE_ASYM_ZERO_POINT);
	rtscam_zoom_write_reg(zoom, ctrl->enable, IVE_ENABLE);

	//zoom->isp->set_clock(zoom->isp, 0);
	rtscam_zoom_set_isp_clock(zoom, 0);

	xSemaphoreGive(zoom->lock);

	return 0;
}

static int __cvrt_verify_info(struct rtscam_soc_verify_info *vinfo,
			struct rtscam_verify_info *verify_info,
			struct rtscam_zoom_info *zoom_info)
{
	u32 verify_scale_h, verify_scale_v;
	u32 src_w, src_h, src_w_actual, src_h_actual;
	u32 zoom_src_w, zoom_src_h;

	if (!vinfo || !verify_info || !zoom_info)
		return -EINVAL;

	src_w = vinfo->src_w;
	src_h = vinfo->src_h;
	src_w_actual = vinfo->src_w_actual;
	src_h_actual = vinfo->src_h_actual;

	if (src_w % RTS_ZOOM_SRC_MAX_WIDTH)
		verify_scale_h = src_w_actual / RTS_ZOOM_SRC_MAX_WIDTH + 1;
	else
		verify_scale_h = src_w_actual / RTS_ZOOM_SRC_MAX_WIDTH;

	if (src_h % RTS_ZOOM_SRC_MAX_HEIGHT)
		verify_scale_v = src_h_actual / RTS_ZOOM_SRC_MAX_HEIGHT + 1;
	else
		verify_scale_v = src_h_actual / RTS_ZOOM_SRC_MAX_HEIGHT;

	if (verify_scale_h > verify_scale_v)
		verify_scale_v = verify_scale_h;
	else
		verify_scale_h = verify_scale_v;

	while (verify_scale_h <= 15) {
		zoom_src_w = src_w / verify_scale_h;
		zoom_src_h = src_h / verify_scale_v;
		if (zoom_src_w % 2 == 0 && zoom_src_h % 2 == 0)
			break;
		verify_scale_h++;
		verify_scale_v = verify_scale_h;
	}

	if (verify_scale_h > 15) {
		rtsprintk(RTS_TRACE_ERROR,
			"fail to get verify_scale: %d %d %d %d\n",
			src_w_actual, src_h_actual, src_w, src_h);
		return -EINVAL;
	}

	if (zoom_src_w < vinfo->dst_w || zoom_src_h < vinfo->dst_h) {
		rtsprintk(RTS_TRACE_ERROR,
			"zoom dst size is bigger than src: %d %d %ld %ld\n",
			zoom_src_w, zoom_src_h, vinfo->dst_w, vinfo->dst_h);
		return -EINVAL;
	}

	verify_info->scale_h = verify_scale_h;
	verify_info->scale_v = verify_scale_v;
	verify_info->width = src_w_actual;
	verify_info->height = src_h_actual;
	verify_info->phyaddr = vinfo->src_phyaddr;
	verify_info->fmt = vinfo->src_fmt;

	zoom_info->zoom_src_w = zoom_src_w;
	zoom_info->zoom_src_h = zoom_src_h;
	zoom_info->zoom_dst_w = vinfo->dst_w;
	zoom_info->zoom_dst_h = vinfo->dst_h;

	rtsprintk(RTS_TRACE_DEBUG, "verify info: %d %d %d %d %d %d %ld %ld\n",
			src_w_actual, src_h_actual,
			verify_scale_h, verify_scale_v,
			zoom_src_w, zoom_src_h,
			vinfo->dst_w, vinfo->dst_h);
	return 0;
}

static void __save_system_reg(struct rtscam_zoom *zoom)
{
	zoom->verify->init(zoom->verify);

	zoom->system_reg_val[0] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_SYS_CONTROL0);
	zoom->system_reg_val[1] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_SYS_CONTROL1);
	zoom->system_reg_val[2] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_SYS_DATA_DELAY);
	zoom->system_reg_val[3] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_SYS_IMAGE_SEL0);
	zoom->system_reg_val[4] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_SYS_IMAGE_AI_CHAN_SEL);

	zoom->system_reg_val[5] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_MCROP_STARTX);
	zoom->system_reg_val[6] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_MCROP_STARTY);
	zoom->system_reg_val[7] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_MCROP_FRAME_WIDTH);
	zoom->system_reg_val[8] = rtscam_zoom_read_reg(zoom,
					RTS_ZOOM_REG_MCROP_FRAME_HEIGHT);
}

static void __restore_system_reg(struct rtscam_zoom *zoom)
{
	zoom->verify->cleanup(zoom->verify);

	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[0],
					RTS_ZOOM_REG_SYS_CONTROL0);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[1],
					RTS_ZOOM_REG_SYS_CONTROL1);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[2],
					RTS_ZOOM_REG_SYS_DATA_DELAY);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[3],
					RTS_ZOOM_REG_SYS_IMAGE_SEL0);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[4],
					RTS_ZOOM_REG_SYS_IMAGE_AI_CHAN_SEL);

	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[5],
					RTS_ZOOM_REG_MCROP_STARTX);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[6],
					RTS_ZOOM_REG_MCROP_STARTY);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[7],
					RTS_ZOOM_REG_MCROP_FRAME_WIDTH);
	rtscam_zoom_write_reg(zoom, zoom->system_reg_val[8],
					RTS_ZOOM_REG_MCROP_FRAME_HEIGHT);
	rtscam_zoom_write_reg(zoom, 1, RTS_ZOOM_REG_MCROP_LOAD);
}

static int __set_verify_zoom(struct rtscam_zoom *zoom,
		struct rtscam_zoom_info *info)
{
	u32 src_w, src_h, dst_w, dst_h;
	u32 zoom_scale_h, zoom_scale_v;
	u32 ch_offset = 4 * RTS_ZOOM_REG_CH_REG_OFFSET;

	if (!zoom || !info)
		return -EINVAL;

	if (info->zoom_dst_w == 0 || info->zoom_dst_h == 0)
		return -EINVAL;

	src_w = info->zoom_src_w;
	src_h = info->zoom_src_h;
	dst_w = info->zoom_dst_w;
	dst_h = info->zoom_dst_h;

	zoom_scale_h = ((src_w << 10) / dst_w);
	zoom_scale_v = ((src_h << 10) / dst_h);

	rtscam_zoom_write_reg(zoom, 0, RTS_ZOOM_REG_MCROP_STARTX);
	rtscam_zoom_write_reg(zoom, 0, RTS_ZOOM_REG_MCROP_STARTY);
	rtscam_zoom_write_reg(zoom, src_w, RTS_ZOOM_REG_MCROP_FRAME_WIDTH);
	rtscam_zoom_write_reg(zoom, src_h, RTS_ZOOM_REG_MCROP_FRAME_HEIGHT);
	rtscam_zoom_write_reg(zoom, 1, RTS_ZOOM_REG_MCROP_LOAD);

	rtscam_zoom_write_reg(zoom, 0, RTS_ZOOM_REG_CH0_CROP_START + ch_offset);
	rtscam_zoom_write_reg(zoom, (dst_w | dst_h << 16),
				RTS_ZOOM_REG_CH0_OUTPUT_SIZE + ch_offset);
	rtscam_zoom_write_reg(zoom, zoom_scale_h,
				RTS_ZOOM_REG_CH0_STEP_H + ch_offset);
	rtscam_zoom_write_reg(zoom, zoom_scale_v,
				RTS_ZOOM_REG_CH0_STEP_V + ch_offset);

	rtscam_zoom_set_zoom_filter(zoom, 4, 0);
	rtscam_zoom_write_reg(zoom, 1, RTS_ZOOM_REG_CH0_REG_LOAD + ch_offset);
	rtscam_zoom_write_reg(zoom, 1, RTS_ZOOM_REG_CH0_CTRL + ch_offset);

	return 0;
}

static int rtscam_zoom_subdev_set_vinfo(struct rtscam_subdev_t *subdev,
					   struct rtscam_soc_verify_info *vinfo)
{
	struct rtscam_zoom *zoom;
	struct rtscam_verify_info verify_info;
	struct rtscam_zoom_info zoom_info={0};

	if (!subdev || !vinfo)
		return -EINVAL;

	if (__subdev_is_isp()) {
		rtsprintk(RTS_TRACE_ERROR, "not support\n");
		return -EINVAL;
	}

	zoom = container_of(subdev, struct rtscam_zoom, subdev);
	if (!zoom->verify) {
		rtsprintk(RTS_TRACE_ERROR, "no verify available\n");
		return -EINVAL;
	}

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_vinfo wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	__cvrt_verify_info(vinfo, &verify_info, &zoom_info);

	__set_verify_zoom(zoom, &zoom_info);
	zoom->verify->set_vinfo(zoom->verify, &verify_info);

	xSemaphoreGive(zoom->lock);
	return 0;
}

static int rtscam_zoom_subdev_set_crop(struct rtscam_subdev_t *subdev,
			int stream_id, struct rtscam_subdev_crop_info *crop)
{
	struct rtscam_zoom *zoom;
	int ret = 0;

	if (!subdev || !crop)
		return -EINVAL;

	if (__subdev_is_verify()) {
		rtsprintk(RTS_TRACE_ERROR, "not support\n");
		return -EINVAL;
	}

	zoom = container_of(subdev, struct rtscam_zoom, subdev);
	if (!zoom->isp)
		return -EINVAL;

	if (crop->rect.left + crop->rect.width > zoom->isp->info.width ||
		crop->rect.top + crop->rect.height > zoom->isp->info.height)
		return ERR_ID_DRV_ZOOM_ROI_OUT_RANGE;

	if (!memcmp(&zoom->last_crop_info[stream_id], &crop->rect,
		    sizeof(crop->rect)))
		return 0;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_set_crop wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	memcpy(&zoom->crop_info[stream_id], &crop->rect, sizeof(crop->rect));

	if (crop->mode) {
		ret = rtscam_zoom_set_zoom(zoom, stream_id);
		if (ret != 0) {
			xSemaphoreGive(zoom->lock);
			isp_error("invalid crop info\n");
			return ret;
		 }
	}

	xSemaphoreGive(zoom->lock);
	return 0;
}

static int rtscam_zoom_subdev_get_crop(struct rtscam_subdev_t *subdev,
			int stream_id, struct rtscam_subdev_crop_info *crop,
			int user_crop)
{
	struct rtscam_zoom *zoom;

	if (!subdev || !crop)
		return -EINVAL;

	zoom = container_of(subdev, struct rtscam_zoom, subdev);

	if (__subdev_is_verify()) {
		crop->rect.left = 0;
		crop->rect.top= 0;
		crop->rect.width = zoom->stream_info.fmt[stream_id].width;
		crop->rect.height = zoom->stream_info.fmt[stream_id].height;
		return 0;
	}

	if (!zoom->isp)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_subdev_get_crop wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	if (user_crop)
		memcpy(&crop->rect, &zoom->crop_info[stream_id], sizeof(crop->rect));
	else
		memcpy(&crop->rect, &zoom->last_crop_info[stream_id], sizeof(crop->rect));

	xSemaphoreGive(zoom->lock);
	return 0;
}

static int rtscam_zoom_register_subdev_unlock(struct rtscam_zoom *zoom)
{
	int i;
	int ret=0;
	struct rtscam_subdev_t *subdev;
	struct rtscam_zoom_stream_info *info;
	struct rtscam_subdev_fps *fps;
	int flag_regist = 0;

	if (!zoom)
		return -EINVAL;

	if (__subdev_is_isp() && !zoom->isp) {
		rtsprintk(RTS_TRACE_ERROR,
			"no isp available, please regist it\n");
		return -EINVAL;
	}

	if (__subdev_is_verify() && !zoom->verify) {
		rtsprintk(RTS_TRACE_ERROR,
			"no verify available, please regist it\n");
		return -EINVAL;
	}

	subdev = &zoom->subdev;
	if (subdev->master) {
//		rtscam_unregister_subdev_ext(subdev);
		flag_regist = 1;
	}

	memset(subdev, 0, sizeof(*subdev));

	if (__subdev_is_isp() && zoom->isp->info.fps > RTSCAM_SOC_MAX_FPS)
		return -EINVAL;

	fps = &subdev->desc.fps;
	fps->type = RTSCAM_SUBDEV_FPS_CONTINUOUS;
	fps->stepwise.step = 1;
	fps->stepwise.min = 1;
	if (__subdev_is_isp())
		fps->stepwise.max = zoom->isp->info.fps;
	else if (__subdev_is_verify())
		fps->stepwise.max = 1;

	info = &zoom->stream_info;
	for (i = 0; i < (int)info->stream_num; i++) {
		subdev->desc.strms[i].format_bitmap = info->fmt[i].fmt;
		subdev->desc.strms[i].width = info->fmt[i].width;
		subdev->desc.strms[i].height = info->fmt[i].height;
	}

	//subdev->dev = zoom->dev;
	subdev->enable = rtscam_zoom_subdev_enable;
	subdev->set_stream = rtscam_zoom_subdev_set_stream;
	subdev->set_fmt = rtscam_zoom_subdev_set_fmt;
	subdev->set_fps = rtscam_zoom_subdev_set_fps;
	subdev->set_hook = rtscam_zoom_subdev_set_hook;
	subdev->get_ive_ctrl = rtscam_zoom_subdev_get_ive_ctrl;
	subdev->set_ive_ctrl = rtscam_zoom_subdev_set_ive_ctrl;
	subdev->set_vinfo = rtscam_zoom_subdev_set_vinfo;
	subdev->set_crop = rtscam_zoom_subdev_set_crop;
	subdev->get_crop = rtscam_zoom_subdev_get_crop;

	if (flag_regist)
		ret = rtscam_register_subdev_ext(subdev);
	else
		ret = rtscam_register_subdev(subdev);
	if (ret)
		rtsprintk(RTS_TRACE_ERROR,
			  "fail to register rts camera subdev\n");
	return ret;
}

static int rtscam_zoom_unregister_subdev_unlock(struct rtscam_zoom *zoom)
{
	return 0;
//	if (!zoom)
//		return -EINVAL;
//
//	if (!zoom->subdev.master)
//		return 0;
//
//	return rtscam_unregister_subdev(&zoom->subdev);
}

static int rtscam_zoom_on_event(void *master, int id, void *arg)
{
	struct rtscam_zoom *zoom = master;

	if (!zoom)
		return -EINVAL;

	if (zoom->hook)
		return zoom->hook(zoom->subdev.master, id, arg);

	return 0;
}

int rtscam_zoom_register_isp(struct rtscam_zoom_isp *isp)
{
	u32 i;
	int ret;
	struct rtscam_zoom *zoom = m_rtszoom;
	struct rtscam_zoom_stream_info *info;
	const struct rtscam_zoom_stream_info *dt_info;

	if (!zoom || !isp)
		return -EINVAL;
	if (!isp->set_fps || !isp->set_hook ||
	    !isp->info.fps || !isp->info.width || !isp->info.height)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_register_isp wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (zoom->isp) {
		rtsprintk(RTS_TRACE_ERROR, "there is already one isp\n");
		xSemaphoreGive(zoom->lock);
		return -EINVAL;
	}
	zoom->isp = isp;
	//get_device(isp->dev);
	isp->master = zoom;
	isp->set_hook(isp, zoom, rtscam_zoom_on_event);

	info = &zoom->stream_info;
	dt_info = &zoom->dt_stream_info;
	info->stream_num = dt_info->stream_num;
	for (i = 0; i < info->stream_num; i++) {
		info->fmt[i].fmt = dt_info->fmt[i].fmt;
		if (i == 0 && zoom->zoom_in_enable) {
			info->fmt[i].width = dt_info->fmt[i].width;
			info->fmt[i].height = dt_info->fmt[i].height;
		} else {
			info->fmt[i].width = min(dt_info->fmt[i].width,
						 isp->info.width);
			info->fmt[i].height = min(dt_info->fmt[i].height,
						  isp->info.height);
		}
		zoom->crop_info[i].left = 0;
		zoom->crop_info[i].top = 0;
		zoom->crop_info[i].width = isp->info.width;
		zoom->crop_info[i].height = isp->info.height;
		zoom->last_crop_info[i] = zoom->crop_info[i];
	}

	ret = rtscam_zoom_register_subdev_unlock(zoom);
	if (ret) {
		isp->set_hook(isp, NULL, NULL);
		//put_device(isp->dev);
		zoom->isp = NULL;
		isp->master = NULL;
	}
	xSemaphoreGive(zoom->lock);
	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_zoom_register_isp);

int rtscam_zoom_unregister_isp(struct rtscam_zoom_isp *isp)
{
	int ret;
	struct rtscam_zoom *zoom;

	if (!isp)
		return -EINVAL;
	zoom = isp->master;
	if (!zoom)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_unregister_isp wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (zoom->isp != isp) {
		isp_error("%s invalid isp to unregister\n", __func__);
		xSemaphoreGive(zoom->lock);
		return -EINVAL;
	}
	isp->set_hook(isp, NULL, NULL);
	//put_device(isp->dev);
	zoom->isp = NULL;
	isp->master = NULL;

	ret = rtscam_zoom_unregister_subdev_unlock(zoom);

	xSemaphoreGive(zoom->lock);

	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_zoom_unregister_isp);

int rtscam_zoom_register_verify(struct rtscam_zoom_verify *verify)
{
	int ret = RTS_OK;
	struct rtscam_zoom *zoom = m_rtszoom;

	if (!zoom || !verify)
		return -EINVAL;
	if (!verify->set_vinfo)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_register_verify wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (zoom->verify) {
		rtsprintk(RTS_TRACE_ERROR, "there is already one verify\n");
		xSemaphoreGive(zoom->lock);
		return -EINVAL;
	}
	zoom->verify = verify;
	//get_device(verify->dev);
	verify->master = zoom;

	xSemaphoreGive(zoom->lock);
	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_zoom_register_verify);

int rtscam_zoom_unregister_verify(struct rtscam_zoom_verify *verify)
{
	struct rtscam_zoom *zoom;

	if (!verify)
		return -EINVAL;
	zoom = verify->master;
	if (!zoom)
		return -EINVAL;

	if (xSemaphoreTake(zoom->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_zoom_unregister_verify wait zoom->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (zoom->verify != verify) {
		rtsprintk(RTS_TRACE_ERROR, "invalid verify to unregister\n");
		xSemaphoreGive(zoom->lock);
		return -EINVAL;
	}
	//put_device(verify->dev);
	zoom->verify = NULL;
	verify->master = NULL;

	xSemaphoreGive(zoom->lock);

	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_zoom_unregister_verify);

static int rtscam_zoom_parse_stream_dt(struct rtscam_zoom_stream_info *info)
{
	//int ret = 0;
	u32 i;

	//from rts3916_evb.dts
	i = 0;
	info->fmt[i].fmt = 0x33;
	info->fmt[i].width = 4032+16;
	info->fmt[i++].height = 3024+16;
	info->fmt[i].fmt = 0x33;
	info->fmt[i].width = 4032;
	info->fmt[i++].height = 3024+16;
	info->fmt[i].fmt = 0x33;
	info->fmt[i].width = 4032;
	info->fmt[i++].height = 3024+16;
	info->fmt[i].fmt = 0x33;
	info->fmt[i].width = 4032;
	info->fmt[i++].height = 3024+16;
	info->fmt[i].fmt = 0x0C;
	info->fmt[i].width = 4032;
	info->fmt[i++].height = 3024+16;


	//from rts3916_evb.dts
	info->stream_num = i;

	for (i = 0; i < info->stream_num; i++) {
		if (!(info->fmt[i].fmt & RTSCAM_FORMAT_TYPE_RGB) &&
				!(info->fmt[i].fmt & RTSCAM_FORMAT_TYPE_Y_ONLY))
			continue;
		if (i != info->stream_num - 1) {
			rtsprintk(RTS_TRACE_ERROR, "invalid stream info, "
				"please adjust RGB/YONLY stream location\n");
			return -EINVAL;
		}
	}
#ifdef _STREAM_INFO_
	for (i = 0; i < info->stream_num; i++)
		printf("stream %u: width: %u, height: %u\r\n", i, info->fmt[i].width, info->fmt[i].height);
#endif
	return 0;
}

static int rtscam_zoom_parse_dt(struct rtscam_zoom *zoom)
{
	int ret;
	//struct device_node *dev_node;

	if (!zoom)
		return -EINVAL;

	//dev_node = zoom->dev->of_node;

	//zoom->zoom_in_enable = of_property_read_bool(dev_node,
	//					     "zoom-in-enable");
	zoom->zoom_in_enable = TRUE;

	ret = rtscam_zoom_parse_stream_dt(&zoom->dt_stream_info);

	memcpy(&zoom->stream_info, &zoom->dt_stream_info,
			sizeof(zoom->stream_info));
	return ret;
}

ssize_t get_subdev_type(char *buf)
{
	struct rtscam_zoom *zoom = &gbl_rtszoom;

	return sprintf(buf, "%s\n", zoom->subdev_type);
}

static int __set_zoom_subdev_to_verify(struct rtscam_zoom *zoom)
{
	int ret;

	if (!zoom)
		return -EINVAL;

	if (!zoom->verify) {
		rtsprintk(RTS_TRACE_ERROR, "no verify available\n");
		return -EINVAL;
	}

	//zoom->verify->set_clock(1);
	rtscam_zoom_set_isp_clock(zoom, 1);
	__save_system_reg(zoom);
	//zoom->verify->set_clock(0);
	rtscam_zoom_set_isp_clock(zoom, 0);
	strncpy(zoom->subdev_type, "verify", sizeof(zoom->subdev_type));

	ret = rtscam_zoom_register_subdev_unlock(zoom);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR,
				"register zoom subdev as verify fail\n");
		return ret;
	}

	rtsprintk(RTS_TRACE_INFO, "set zoom subdev as verify\n");
	return 0;
}

static int __set_zoom_subdev_to_isp(struct rtscam_zoom *zoom)
{
	int ret;

	if (!zoom)
		return -EINVAL;

	//zoom->verify->set_clock(1);
	rtscam_zoom_set_isp_clock(zoom, 1);
	__restore_system_reg(zoom);
	//zoom->verify->set_clock(0);
	rtscam_zoom_set_isp_clock(zoom, 0);
	strncpy(zoom->subdev_type, "isp", sizeof(zoom->subdev_type));

	ret = rtscam_zoom_register_subdev_unlock(zoom);

	rtsprintk(RTS_TRACE_INFO, "set zoom subdev as isp\n");
	return ret;
}

ssize_t set_subdev_type(const char *buf, size_t count)
{
	struct rtscam_zoom *zoom = &gbl_rtszoom;
	char str[20] = {0};
	int ret;

	ret = sscanf(buf, "%19s", str);
	if (ret < 1) {
		rtsprintk(RTS_TRACE_ERROR, "get zoom subdev info fail\n");
		return -EINVAL;
	}

	if (!strcmp(str, zoom->subdev_type)) {
		rtsprintk(RTS_TRACE_INFO,
			"currect is already %s, no need to switch\n",
			zoom->subdev_type);
		return count;
	}

	if (!strcmp(str, "verify"))
		ret = __set_zoom_subdev_to_verify(zoom);
	else if (!strcmp(str, "isp"))
		ret = __set_zoom_subdev_to_isp(zoom);
	else
		rtsprintk(RTS_TRACE_ERROR, "invalid zoom subdev name\n");

	if (ret)
		return -EINVAL;
	return count;
}
//static DEVICE_ATTR(subdev_type, 0664, get_subdev_type, set_subdev_type);

int rtscam_zoom_open(void)
{
	//struct rtscam_ge_device *gdev = rtscam_devdata(filp);
	//struct rtscam_zoom *zoom = &gbl_rtszoom;

	//filp->private_data = zoom;
	return 0;
}

int rtscam_zoom_close(void)
{
	return 0;
}

static long rtscam_zoom_do_ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = -1;

	struct rtscam_zoom *zoom = &gbl_rtszoom;

	switch (cmd) {
	case RTSZOOMIOC_SET_SUBDEV:
		if (*(int *)arg)
			ret = __set_zoom_subdev_to_verify(zoom);
		else
			ret = __set_zoom_subdev_to_isp(zoom);
		break;
	case RTSZOOMIOC_GET_SUBDEV:
		if (!strcmp(zoom->subdev_type, "verify")) {
			*(int *)arg = 1;
			ret = 0;
		} else if (!strcmp(m_rtszoom->subdev_type, "isp")) {
			*(int *)arg = 0;
			ret = 0;
		} else {
			rtsprintk(RTS_TRACE_ERROR,
				"could not get zoom subdev\n");
		}
		break;
	default:
		rtsprintk(RTS_TRACE_ERROR,
			  "Unknown[rtscam] ioctl 0x%08x, type = '%c' nr = 0x%x\n",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

long rtscam_zoom_ioctl(unsigned int cmd,
				 unsigned long arg)
{
	return rtscam_zoom_do_ioctl(cmd, arg);
}

//static struct rtscam_ge_file_operations rtscam_zoom_fops = {
//	.owner = THIS_MODULE,
//	.open = rtscam_zoom_open,
//	.release = rtscam_zoom_close,
//	.ioctl = rtscam_zoom_ioctl,
//};

//static void rtscam_zoom_remove_dev(struct rtscam_zoom *zoom)
//{
//	struct rtscam_ge_device *gdev;
//
//	if (!zoom->gdev)
//		return;
//
//	gdev = zoom->gdev;
//	put_device(gdev->parent);
//	rtscam_ge_unregister_device(gdev);
//}

//static int rtscam_zoom_create_device(struct rtscam_zoom *zoom)
//{
//	struct rtscam_ge_device *gdev;
//	int ret;
//
//	if (zoom->gdev)
//		return 0;
//
//	gdev = rtscam_ge_device_alloc();
//	if (!gdev)
//		return -ENOMEM;
//
//	strlcpy(gdev->name, RTS_ZOOM_DEV_NAME, sizeof(gdev->name));
//	gdev->parent = get_device(zoom->dev);
//	gdev->release = rtscam_ge_device_release;
//	gdev->fops = &rtscam_zoom_fops;
//
//	rtscam_ge_set_drvdata(gdev, zoom);
//	ret = rtscam_ge_register_device(gdev);
//	if (ret) {
//		rtscam_ge_device_release(gdev);
//		return ret;
//	}
//
//	zoom->gdev = gdev;
//
//	return 0;
//}

int rtscam_zoom_probe(void)
{
	int ret;
	//void *base;
	//struct resource *res;
	struct rtscam_zoom *zoom;
	//struct device *dev = &pdev->dev;
	struct rtscam_isp_mfd *mfd;

	//rtsprintk(RTS_TRACE_INFO, "%s\r\n", __func__);

	mfd = rtscam_get_isp_mfd();  //dev_get_drvdata(dev->parent);
	if (!mfd)
		return -EINVAL;

	zoom = &gbl_rtszoom;
	zoom->mfd = mfd;

	//base = (void*)ZOOM_BASE;
	//zoom->reg_base = base;
//rtsprintk(RTS_TRACE_INFO, "%s %08x\n", __func__, (u32)base);

	//zoom->dev = get_device(&pdev->dev);
	//mutex_init(&zoom->lock);
	const osMutexAttr_t zoomlock_Mutex_attr = {
	  "zoomlockMutex",                          // human readable mutex name
	  osMutexRecursive | osMutexPrioInherit,    // attr_bits
	  NULL,                         // memory for control block
	  0U                   // size for control block
	};
	zoom->lock = osMutexNew(&zoomlock_Mutex_attr);
	if ( !zoom->lock ) {
		rtsprintk(RTS_TRACE_ERROR, "zoom->lock mutex alloc fail\n");
		ret = RTS_FAIL;
		return ret;
	}

	strncpy(zoom->subdev_type, "isp", sizeof(zoom->subdev_type));

	ret = rtscam_zoom_parse_dt(zoom);
	if (ret)
		return ret;

	//device_create_file(zoom->dev, &dev_attr_subdev_type);

	//if (rtscam_zoom_create_device(zoom))
	//	rtsprintk(RTS_TRACE_ERROR, "fail to create zoom dev\n");

	//platform_set_drvdata(pdev, zoom);
	m_rtszoom = zoom;

	return 0;
}

int rtscam_zoom_remove(void)
{
	//struct rtscam_zoom *zoom = &gbl_rtszoom;

	//device_remove_file(zoom->dev, &dev_attr_subdev_type);
	//rtscam_unregister_subdev(&zoom->subdev);
	//rtscam_zoom_remove_dev(zoom);
	//put_device(zoom->dev);
	m_rtszoom = NULL;

	return 0;
}

//static struct platform_driver rtscam_zoom_driver = {
//	.driver = {
//		.name = RTS_ZOOM_DRV_NAME,
//		.owner = THIS_MODULE,
//	},
//	.probe = rtscam_zoom_probe,
//	.remove = rtscam_zoom_remove,
//};

//module_platform_driver(rtscam_zoom_driver);
//
//MODULE_DESCRIPTION("Realsil zoom device driver");
//MODULE_AUTHOR("Grant Shen <grant_shen@realsil.com.cn>");
//MODULE_LICENSE("GPL v2");
//MODULE_VERSION("0.1.0");
//MODULE_ALIAS("platform:" RTS_ZOOM_DRV_NAME);

