/*
 * Realtek Semiconductor Corp.
 *
 * lib/rtsv4l2.c
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "rt_task.h"
#include "rts_ioctl.h"
//#define open rts_open
//#define close rts_close
#define ioctl rts_ioctl
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <rtscamkit.h>
#include "rtsv4l2.h"
#include "isp_log.h"
#include "rtsavisp.h"
#include "isp_main.h"
#include "rts_camera.h"
#include "isp_top.h"

extern uint32_t ameba_get_stream_cnt(int fd);
uint32_t get_v4l2_format(uint32_t ameba_fmt);
uint32_t get_stream_fd(uint8_t stream_id);


extern struct rtscam_video_stream *get_stream(int fd);

int check_isp_running(void)
{
	return (isp_top_get_status() == RTS_ISP_RUNNING );
}


int rts_v4l2_open(const char *path, int oflag)
{
	if (!path)
		return RTS_RETURN(RTS_E_NULL_POINT);

	return rts_open(path);
}

int rts_v4l2_close(int fd)
{
	RTS_SAFE_CLOSE(fd, rts_close);

	return RTS_OK;
}

int check_valid_value(uint32_t value, uint32_t min, uint32_t max, uint32_t step)
{
	if (value < min)
		return RTS_RETURN(RTS_E_OUT_OF_RANGE);

	if (value > max)
		return RTS_RETURN(RTS_E_OUT_OF_RANGE);

	if ((value - min) % step != 0)
		return RTS_RETURN(RTS_E_INVALID_DATA);

	return RTS_OK;
}

int valid_frmsize_stepwise(uint32_t width, uint32_t height,
			   struct v4l2_frmsize_stepwise *stepwise)
{
	int ret;

	ret = check_valid_value(width, stepwise->min_width,
				stepwise->max_width, stepwise->step_width);
	if (RTS_IS_ERR(ret))
		return ret;

	ret = check_valid_value(height, stepwise->min_height,
				stepwise->max_height, stepwise->step_height);
	if (RTS_IS_ERR(ret))
		return ret;

	return RTS_OK;
}

int valid_frmival_stepwise(uint32_t numerator, uint32_t denominator,
			   struct v4l2_frmival_stepwise *stepwise)
{
	int ret;

	ret = check_valid_value(
			      numerator,
			      stepwise->min.numerator,
			      stepwise->max.numerator,
			      stepwise->step.numerator);
	if (RTS_IS_ERR(ret))
		return ret;

	ret = check_valid_value(
			      denominator,
			      stepwise->min.denominator,
			      stepwise->max.denominator,
			      stepwise->step.denominator);
	if (RTS_IS_ERR(ret))
		return ret;

	return RTS_OK;
}

int rts_v4l2_check_fmt(int fd, uint32_t fmt, uint32_t width, uint32_t height)
{
	struct v4l2_fmtdesc fmtdesc;
	struct v4l2_frmsizeenum frmsize;
	int i = 0, j = 0;
	int ret = 0;

	while (1) {
		ret = rts_v4l2_enum_fmt(fd, i, &fmtdesc);
		if (RTS_IS_ERR(ret))
			break;
		i++;
		if (fmtdesc.pixelformat != fmt)
			continue;
		j = 0;
		while (1) {
			ret = rts_v4l2_enum_frmsizes(fd, fmt, j, &frmsize);
			if (RTS_IS_ERR(ret))
				break;
			if (V4L2_FRMSIZE_TYPE_DISCRETE == frmsize.type) {
				if (frmsize.discrete.width == width &&
				    frmsize.discrete.height == height)
					return RTS_OK;
			} else {
				ret = valid_frmsize_stepwise(width, height,
							     &frmsize.stepwise);
				if (ret == RTS_OK)
					return RTS_OK;
			}
			j++;
		}
	}

	return ERR_ID_ISP_V4l2_FMT_NOT_SUPPORT;
}

int rts_v4l2_check_frmival(int fd, uint32_t fmt,
			   uint32_t width, uint32_t height,
			   uint32_t numerator, uint32_t denominator)
{
	struct v4l2_frmivalenum frmival;
	int ret = RTS_OK;
	int i = 0;

	if (numerator * denominator == 0)
		return ERR_ID_ISP_V4l2_FPS_NOT_SUPPORT;

	while (1) {
		ret = rts_v4l2_enum_frmival(fd,
					    fmt, width, height, i, &frmival);
		if (RTS_IS_ERR(ret))
			break;
		i++;
		if (V4L2_FRMIVAL_TYPE_DISCRETE == frmival.type) {
			if (numerator * frmival.discrete.denominator ==
			    denominator * frmival.discrete.numerator)
				return RTS_OK;
		} else {
			ret = valid_frmival_stepwise(numerator, denominator,
						     &frmival.stepwise);
			if (!ret)
				return RTS_OK;
		}
	}

	return ERR_ID_ISP_V4l2_FPS_NOT_SUPPORT;
}

int rts_v4l2_get_selection(int fd, uint32_t *x, uint32_t *y,
		uint32_t *width, uint32_t *height)
{
	struct v4l2_selection selection;
	int ret = 0;
	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (!x || !y || !width || !height)
		return RTS_RETURN(RTS_E_NULL_POINT);

	memset(&selection, 0, sizeof(selection));
	ret = ioctl(fd, VIDIOC_G_SELECTION, &selection);
	if (ret < 0) {
		isp_error("v4l2 ioctl G_SELECTION fail. %d\n", ret);
		return ret;
	}

	*x = selection.r.left;
	*y = selection.r.top;
	*width = selection.r.width;
	*height = selection.r.height;
	return RTS_OK;
}

int rts_v4l2_set_selection(int fd, uint32_t x, uint32_t y,
		uint32_t width, uint32_t height)
{
	struct v4l2_selection selection;
	int ret = 0;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	memset(&selection, 0, sizeof(selection));
	selection.r.left = x;
	selection.r.top = y;
	selection.r.width = width;
	selection.r.height = height;

	ret = ioctl(fd, VIDIOC_S_SELECTION, &selection);
	if (ret < 0) {
		isp_error("v4l2 ioctl S_SELECTION fail. %d\n", ret);
		return ret;
	}
	return RTS_OK;
}

int rts_v4l2_get_fmt(int fd, uint32_t *pfmt, uint32_t *pw, uint32_t *ph)
{
	struct v4l2_format format;
	int ret = 0;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(fd, VIDIOC_G_FMT, &format);
	if (0 > ret) {
		isp_error("v4l2 ioctl G_FMT fail. %d\n", ret);
		return ret;
	}

	if (pfmt)
		*pfmt = format.fmt.pix.pixelformat;
	if (pw)
		*pw = format.fmt.pix.width;
	if (ph)
		*ph = format.fmt.pix.height;

	return RTS_OK;
}

int rts_v4l2_set_fmt(int fd, uint32_t fmt, uint32_t width, uint32_t height)
{
	struct v4l2_format format;
	int ret = RTS_OK;

	if (fd < 0) {
		isp_error("%s fd %d error\r\n", __func__, fd);
		return RTS_RETURN(RTS_E_NOT_OPEN);
	}


	ret = rts_v4l2_check_fmt(fd, fmt, width, height);
	if (RTS_IS_ERR(ret)) {
		isp_error("%s rts_v4l2_check_fmt error ret = %d \r\n", __func__, ret);
		return ret;
	}


	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(fd, VIDIOC_G_FMT, &format);
	if (0 > ret) {
		isp_error("%s VIDIOC_G_FMT error %d \r\n", __func__, ret);
		return ret;
	}

	format.fmt.pix.pixelformat = fmt;
	format.fmt.pix.width = width;
	format.fmt.pix.height = height;
	ret = ioctl(fd, VIDIOC_S_FMT, &format);
	if (0 > ret) {
		isp_error("%s VIDIOC_S_FMT error %d \r\n", __func__, ret);
		return ret;
	}

	if (format.fmt.pix.pixelformat != fmt ||
	    format.fmt.pix.width != width ||
	    format.fmt.pix.height != height) {
		isp_error("rts v4l2 set fmt (%c%c%c%c %dx%d) fail, not support\n",
			(fmt) & 0xff,
			(fmt >> 8) & 0xff,
			(fmt >> 16) & 0xff,
			(fmt >> 24) & 0xff,
			width,
			height);
		return ERR_ID_ISP_V4l2_FMT_NOT_SUPPORT;
	}

	return RTS_OK;
}

int rts_v4l2_get_frmival(int fd, uint32_t *numerator, uint32_t *denominator)
{
	struct v4l2_streamparm parm;
	int ret = 0;
	if (fd < 0)
		return -RTS_E_NOT_OPEN;

	memset(&parm, 0, sizeof(parm));

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = ioctl(fd, VIDIOC_G_PARM, &parm);
	if (0 > ret) {
		isp_error("v4l2 ioctl G_PARM fail. %d\n", ret);
		return ret;
	}

	if (numerator)
		*numerator = parm.parm.capture.timeperframe.numerator;
	if (denominator)
		*denominator = parm.parm.capture.timeperframe.denominator;

	return RTS_OK;
}

int rts_v4l2_set_frmival(int fd, uint32_t numerator, uint32_t denominator)
{
	struct v4l2_streamparm parm;
	uint32_t fmt;
	uint32_t width = 0;
	uint32_t height = 0;
	int ret = RTS_OK;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	rts_v4l2_get_fmt(fd, &fmt, &width, &height);
	if (width == 0 || height == 0)
		return RTS_RETURN(RTS_E_GET_FAIL); 

	ret = rts_v4l2_check_frmival(fd, fmt, width, height,
				     numerator, denominator);
	if (RTS_IS_ERR(ret))
		return ret;

	memset(&parm, 0, sizeof(parm));

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	parm.parm.capture.timeperframe.numerator = numerator;
	parm.parm.capture.timeperframe.denominator = denominator;

	ret = ioctl(fd, VIDIOC_S_PARM, &parm);
	if (0 > ret) {
		isp_error("v4l2 ioctl S_PARM fail. %d\n", ret);
		return ret;
	}
	if (parm.parm.capture.timeperframe.numerator != numerator ||
	    parm.parm.capture.timeperframe.denominator != denominator) {
		isp_error("rts v4l2 set framerate (%d/%d) fail, not support\n",
			numerator, denominator);
		return ERR_ID_ISP_V4l2_FPS_NOT_SUPPORT;
	}

	return RTS_OK;
}

int rts_v4l2_enum_fmt(int fd, int index, struct v4l2_fmtdesc *fmtdesc)
{
	int ret;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (index < 0)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	if (!fmtdesc)
		return RTS_RETURN(RTS_E_NULL_POINT);

	memset(fmtdesc, 0, sizeof(struct v4l2_fmtdesc));

	fmtdesc->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmtdesc->index = index;

	ret = ioctl(fd, VIDIOC_ENUM_FMT, fmtdesc);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_enum_frmsizes(int fd, uint32_t fmt, int index,
			   struct v4l2_frmsizeenum *frmsize)
{
	int ret;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (index < 0)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	if (!frmsize)
		return RTS_RETURN(RTS_E_NULL_POINT);

	memset(frmsize, 0, sizeof(struct v4l2_frmsizeenum));

	frmsize->pixel_format = fmt;
	frmsize->index = index;

	ret = ioctl(fd, VIDIOC_ENUM_FRAMESIZES, frmsize);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_enum_frmival(int fd, uint32_t fmt,
			  uint32_t width, uint32_t height,
			  int index, struct v4l2_frmivalenum *frmival)
{
	int ret;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (index < 0)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	if (!frmival)
		return RTS_RETURN(RTS_E_NULL_POINT);

	memset(frmival, 0, sizeof(struct v4l2_frmivalenum));

	frmival->pixel_format = fmt;
	frmival->width = width;
	frmival->height = height;
	frmival->index = index;

	ret = ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, frmival);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_request_bufs(int fd, unsigned int num)
{
	struct v4l2_requestbuffers v4l2_reqbufs;
	int ret = RTS_OK;

	if (fd <= 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	memset(&v4l2_reqbufs, 0, sizeof(v4l2_reqbufs));
	v4l2_reqbufs.count = num;
	v4l2_reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2_reqbufs.memory = V4L2_MEMORY_MMAP;

	ret = ioctl(fd, VIDIOC_REQBUFS, &v4l2_reqbufs);
	if (ret < 0) {
		isp_error("v4l2 ioctl REQBUFS fail, %d\n", ret);
		return ret;
	}

	return v4l2_reqbufs.count;
}

int rts_v4l2_query_buffer(int fd, uint32_t index, struct v4l2_buffer *pbuf)
{
	int ret = RTS_OK;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (!pbuf)
		return RTS_RETURN(RTS_E_NULL_POINT);

	pbuf->index = index;
	pbuf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	pbuf->memory = V4L2_MEMORY_MMAP;

	ret = ioctl(fd, VIDIOC_QUERYBUF, pbuf);
	if (ret < 0) {
		isp_error("v4l2 ioctl querybuf fail, %d\n", ret);
		return ret;
	}

	return RTS_OK;
}

int rts_v4l2_query_mmap_buf(int fd, int index, void **ppbuf, uint32_t *plength)
{
	struct v4l2_buffer v4l2_buf;
	int ret = RTS_OK;

	if (fd <= 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (index < 0)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	if (!ppbuf || !plength)
		return RTS_RETURN(RTS_E_NULL_POINT);

	memset(&v4l2_buf, 0, sizeof(v4l2_buf));
	v4l2_buf.index = index;
	v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2_buf.memory = V4L2_MEMORY_MMAP;

	ret = ioctl(fd, VIDIOC_QUERYBUF, &v4l2_buf);
	if (ret < 0) {
		isp_error("v4l2 ioctl querybuf fail, %d\n", ret);
		return ret;
	}
	*plength = v4l2_buf.length;
	//just for convenience, for RTOS only
	*ppbuf = (void*)v4l2_buf.reserved;

	return RTS_OK;
}

int rts_v4l2_munmap_buf(void *pbuf, uint32_t length)
{
	return RTS_FAIL;
}

int __queue_buffers(int fd)
{
	struct v4l2_buffer v4l2_buf;
	int ret;
	int i = 0;

	memset(&v4l2_buf, 0, sizeof(v4l2_buf));
	v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2_buf.memory = V4L2_MEMORY_MMAP;

	while (1) {
		v4l2_buf.index = i;

		ret = ioctl(fd, VIDIOC_QUERYBUF, &v4l2_buf);
		if (ret < 0)
			break;

		ret = ioctl(fd, VIDIOC_QBUF, &v4l2_buf);
		if (ret < 0) {
			isp_error("queue buffer %d fail, %d\n",
				i, ret);
			return ret;
		}
		i++;
	}

	if (i == 0)
		return RTS_RETURN(RTS_E_GET_FAIL);

	return RTS_OK;
}

int rts_v4l2_streamon(int fd)
{
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	int ret = 0;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	//ret = __queue_buffers(fd);
	//if (RTS_IS_ERR(ret))
	//	return  ret;

	ret = ioctl(fd, VIDIOC_STREAMON, &type);
	if (ret < 0) {
		isp_error("v4l2 ioctl STREAMON fail, %d\n", ret);
		return ret;
	}

	return RTS_OK;
}

int rts_rtsv_streamoff(int fd)
{
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	int ret = 0;
	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	ret = ioctl(fd, VIDIOC_STREAMOFF, &type);
	if (ret < 0) {
		isp_error("v4l2 ioctl STREAMOFF fail, %d\n", ret);
		return ret;
	}
	if (isp_top_get_status() != RTS_ISP_STREAMING)
		isp_driver_cleanup_statis();

	return RTS_OK;
}

int rts_v4l2_get_buffer(int fd , uint32_t *pbuf)
{
	int ret = RTS_OK;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (!pbuf)
		return RTS_RETURN(RTS_E_NULL_POINT);

	//memset(pbuf, 0, sizeof(struct v4l2_buffer));
	//pbuf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	//pbuf->memory = V4L2_MEMORY_MMAP;
	//pbuf->index = -1;

	ret = ioctl(fd, VIDIOC_DQBUF, pbuf);
	if (ret < 0) {
		isp_error("v4l2 ioctl DQBUF fail, %d\n", ret);
		return ret;
	}

	return RTS_OK;
}

int rts_rtsv_put_buffer(int fd, uint32_t *pbuf)
{
	int ret = RTS_OK;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (!pbuf)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = ioctl(fd, VIDIOC_QBUF, pbuf);
	if (ret < 0) {
		isp_error("v4l2 ioctl QBUF %x fail, %d\n",
			(unsigned int)pbuf, ret);
		return ret;
	}

	return RTS_OK;
}
#if 0
int rts_v4l2_put_buffer_by_index(int fd, int index)
{
	int ret = RTS_OK;
	struct v4l2_buffer buffer;

	ret = rts_v4l2_query_buffer(fd, index, &buffer);
	if (RTS_IS_ERR(ret)) {
		isp_error("query buffer %d fail, ret = %d\n", index, ret);
		return ret;
	}

	return rts_v4l2_put_buffer(fd, &buffer);
}
#endif

int rts_v4l2_pollin(int fd, int timeout)
{
	return rts_pollin(fd, timeout);
}

int rts_v4l2_check_frame(int fd)
{
	return rts_v4l2_pollin(fd, 1);
}

int rts_v4l2_queryctrl(int fd, struct v4l2_queryctrl *pqctrl)
{
	int ret = RTS_OK;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	if (!pqctrl)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = ioctl(fd, VIDIOC_QUERYCTRL, pqctrl);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_query_next_ctrl(int fd, struct v4l2_queryctrl *pqctrl)
{
	if (!pqctrl)
		return RTS_RETURN(RTS_E_NULL_POINT);

	if (pqctrl->id)
		pqctrl->id |= V4L2_CTRL_FLAG_NEXT_CTRL;
	else
		pqctrl->id = V4L2_CTRL_FLAG_NEXT_CTRL;

	return rts_v4l2_queryctrl(fd, pqctrl);
}

int rts_v4l2_get_ctrl(int fd, struct v4l2_control *pctrl)
{
	int ret = RTS_OK;

	if (!pctrl)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	ret = ioctl(fd, VIDIOC_G_CTRL, pctrl);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_set_ctrl(int fd, struct v4l2_control *pctrl)
{
	int ret = RTS_OK;

	if (!pctrl)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	ret = ioctl(fd, VIDIOC_S_CTRL, pctrl);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_get_ext_ctrls(int fd, struct v4l2_ext_controls *ctrls)
{
	int ret = RTS_OK;

	if (!ctrls)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, ctrls);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_set_ext_ctrls(int fd, struct v4l2_ext_controls *ctrls)
{
	int ret = RTS_OK;

	if (!ctrls)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, ctrls);
	if (ret < 0)
		return ret;

	return RTS_OK;
}

int rts_v4l2_get_max_frmsize(int fd, uint32_t fmt, uint32_t *w, uint32_t *h)
{
	int ret;
	int index = 0;
	struct v4l2_frmsizeenum frmsize;
	uint32_t width = 0;
	uint32_t height = 0;

	do {
		ret = rts_v4l2_enum_frmsizes(fd, fmt, index++, &frmsize);
		if (RTS_IS_ERR(ret))
			break;
		if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
			if (width * height <
			    frmsize.discrete.width * frmsize.discrete.height) {
				width = frmsize.discrete.width;
				height = frmsize.discrete.height;
			}
		} else {
			width = frmsize.stepwise.max_width;
			height = frmsize.stepwise.max_height;
			break;
		}
	} while (1);

	if ((width * height) == 0 )
		return RTS_RETURN(RTS_E_GET_FAIL);

	if (w)
		*w = width;
	if (h)
		*h = height;

	return RTS_OK;
}

int rts_v4l2_get_sensor_frmsize(uint32_t *w, uint32_t *h)
{
	struct v4l2_fmtdesc fmtdesc;
	int i = 0, j = 0;
	int ret = 0;
	int fd;
	char dev_node[64];
	uint32_t w_max = 0, h_max = 0;
	uint32_t w_temp, h_temp;

	for (i = 0; i < 4; i++) {
		snprintf(dev_node, sizeof(dev_node), "/dev/video%d", 51 + i);
		//fd = rts_v4l2_open(dev_node, O_RDWR | O_NONBLOCK | O_CLOEXEC);
		fd = rts_open(dev_node);
		if (fd < 0)
			continue;

		j = 0;
		while (1) {
			ret = rts_v4l2_enum_fmt(fd, j, &fmtdesc);
			if (RTS_IS_ERR(ret))
				break;
			j++;
			ret = rts_v4l2_get_max_frmsize(fd, fmtdesc.pixelformat,
					&w_temp, &h_temp);
			if (RTS_IS_ERR(ret))
				continue;

			if (w_temp * h_temp > w_max * h_max) {
				w_max = w_temp;
				h_max = h_temp;
			}
		}

		rts_v4l2_close(fd);
	}

	*w = w_max;
	*h = h_max;

	return RTS_OK;
}



int start_preview(hal_isp_adapter_t *isp_adpt, uint8_t stream_id)
{

	int v4l2_fd;

	uint32_t fmt, width, height, numerator, denominator;

	v4l2_fd = get_stream_fd(stream_id);
	if (!v4l2_fd) {
		isp_error("%s stream id error %d \r\n", __func__, stream_id);
		return -1;
	}

	fmt = get_v4l2_format(isp_adpt->video_stream[stream_id].fmt);
	if (fmt == 0) {
		isp_error("%s stream fmt error %d \r\n", __func__, isp_adpt->video_stream[stream_id].fmt);
		return -1;
	}


	width = isp_adpt->video_stream[stream_id].user_width;
	height = isp_adpt->video_stream[stream_id].user_height;
	numerator = isp_adpt->video_stream[stream_id].rate_numerator;
	denominator = isp_adpt->video_stream[stream_id].rate_denominator;

	int ret = 0;
	//int i,j;
	struct rtscam_video_stream *stream;
#if 0
	if (fd >= 0)
		v4l2_fd = fd;
	else
		v4l2_fd = rts_v4l2_open("/dev/video51", O_RDWR);

	if (v4l2_fd < 0)
		return -1;
#endif


	//memset(buffers, 0, sizeof(buffers));

	rts_v4l2_set_fmt(v4l2_fd, fmt, width, height);
	rts_v4l2_set_frmival(v4l2_fd, numerator, denominator);

	printf("%c%c%c%c %dx%d %d/%d\r\n",
	       (int)fmt & 0xff, (int)(fmt >> 8) & 0xff,
	       (int)(fmt >> 16) & 0xff, (int)(fmt >> 24) & 0xff,
	       (int)width, (int)height,
	       (int)numerator, (int)denominator);


	stream = get_stream(v4l2_fd);
	if (stream == NULL) {
		isp_error("%s get_stream \r\n", __func__);
		return -1;
	}
	stream->hw_slot_num = isp_adpt->video_stream[stream_id].hw_slot_num;
	stream->stream_buf_num = isp_adpt->video_stream[stream_id].buff_num;

	stream->stream_frame_done = xQueueCreate( stream->stream_buf_num, sizeof(int) );
	isp_info("%s stream_frame_done xQueueCreate item %d \r\n", __func__, stream->stream_buf_num);

	if ( !stream->stream_frame_done ) {
		isp_error("%s stream->stream_frame_done xQueueCreate fail\r\n", __func__);
		return -1;
	}
	for (int i=0; i<isp_adpt->video_stream[stream_id].buff_num; i++) {
		if (isp_adpt->video_stream[stream_id].bufs[i].buf_addr)
			stream->bufs[i].buf_addr = isp_adpt->video_stream[stream_id].bufs[i].buf_addr;
		else {
			isp_error("%s stream%d bufs[%d].buf_addr NULL\r\n", __func__, stream_id, i);
			return -1;
		}
	}

	ret = rts_v4l2_request_bufs(v4l2_fd, stream->stream_buf_num);
	if (ret <= 0) {
		isp_error("%s rts_v4l2_request_bufs error %d \r\n", __func__, ret);
		ret = -1;
		return ret;
	}

	ret = rts_v4l2_streamon(v4l2_fd);
	//ret = iot_soc_s_stream(v4l2_fd, 1);
	//printf("%s ret %d \r\n", __FUNCTION__, ret);


#if 0

	int v4l2_fd;
	int number = 4;
	struct test_buffer buffers[MAX_FRAME_NUM];
	//uint64_t start;
	int ret;
	int i,j;
	int chn_id;
	int align_h, offset_uv;

	if (fd >= 0)
		v4l2_fd = fd;
	else
		v4l2_fd = rts_v4l2_open("/dev/video51", O_RDWR);

	if (v4l2_fd < 0)
		return -1;

	memset(buffers, 0, sizeof(buffers));

	rts_v4l2_set_fmt(v4l2_fd, fmt, width, height);
	rts_v4l2_set_frmival(v4l2_fd, numerator, denominator);

	printf("%c%c%c%c %dx%d %d/%d\n",
	       (int)fmt & 0xff, (int)(fmt >> 8) & 0xff,
	       (int)(fmt >> 16) & 0xff, (int)(fmt >> 24) & 0xff,
	       (int)width, (int)height,
	       (int)numerator, (int)denominator);

	ret = rts_v4l2_request_bufs(v4l2_fd, MAX_FRAME_NUM);
	if (ret <= 0) {
		ret = -1;
		goto exit;
	}
	number = ret;
	for (i = 0; i < number; i++) {
		ret = rts_v4l2_query_mmap_buf(v4l2_fd, i, &buffers[i].pbuf,
					      &buffers[i].length);
		if (RTS_IS_ERR(ret))
			goto exit1;
	}

	chn_id = (v4l2_fd % 10) - 1;
	if (check_chn_id(chn_id)) {  //valid chn, init osd2
		ret = rt_osd2_init_chn_profile(chn_id, RTS_V_FMT_YUV420SEMIPLANAR, width, height,
										numerator, denominator);
		if (ret != RT_OK)
			goto exit2;
	}
	printf("{osd2} create chn#0, %s\n", rt_code_str(ret));

	ret = rts_v4l2_streamon(v4l2_fd);

	//get offset of UV buffer start, see rts_camera_soc_3915.c/rtscam_socdev_submit_buffer()
	offset_uv = width * height;
	align_h = rtscam_socdev_get_height_align();
	if (align_h) {
		if (height % align_h)
			offset_uv += (align_h - height % align_h) * width;
	}

	//start = get_time();
	i=j=0;
	gbl_snap_shot = 0;
	while (1) {
		struct v4l2_buffer buf;
		//if (get_time() - start > 1e6 * timeout)
		if (fnum == 0)
			break;

j++;
		ret = rts_v4l2_get_buffer(v4l2_fd, &buf);
		if (RTS_IS_ERR(ret))
			continue;

		if (fnum > 0) fnum--;

/*
		taskENTER_CRITICAL();
		printf("frame %d:0x%08x size:%d use:%d try:%d get:%d data:0x%08x\n",
			buf.index,
			(unsigned int)buffers[buf.index].pbuf, (int)buffers[buf.index].length, buf.bytesused,
			i, j, *((int*)buffers[buf.index].pbuf));
		taskEXIT_CRITICAL();
*/

		ret = rt_osd2_encode(chn_id, (void*)buffers[buf.index].pbuf, buf.bytesused);
		if ((ret != RT_E_NOT_INIT) && (ret != RT_E_NOT_START) && (ret != RT_OK))
		{
			printf("rt_osd2_encode(), %s\n", rt_code_str(ret));
		}

		if (socket_fd >= 0 && gbl_snap_shot &&
			buffers[buf.index].pbuf && buf.bytesused) {
			send_to_host(socket_fd, buffers[buf.index].pbuf, width*height, offset_uv, width*height/2);
			gbl_snap_shot = 0;
		}
		rts_v4l2_put_buffer(v4l2_fd, &buf);
	}

	rts_v4l2_streamoff(v4l2_fd);

exit2:
	rts_av_osdenc_cleanup(chn_id);

exit1:
	for (i = 0; i < number; i++)
		rts_v4l2_munmap_buf(buffers[i].pbuf, buffers[i].length);
	rts_v4l2_request_bufs(v4l2_fd, 0);
exit:
	if (fd < 0)
		RTS_SAFE_CLOSE(v4l2_fd, rts_v4l2_close);

#endif

	return ret;
}

uint32_t get_v4l2_format(uint32_t ameba_fmt)
{
	uint32_t fmt = 0;

	switch (ameba_fmt) {
	case NV12_FORMAT:
		fmt = V4L2_PIX_FMT_NV12;
		break;
	case NV16_FORMAT:
		fmt = V4L2_PIX_FMT_NV16;
		break;
	case NV21_FORMAT:
		fmt = V4L2_PIX_FMT_NV21;
		break;
	case NV61_FORMAT:
		fmt = V4L2_PIX_FMT_NV61;
		break;
	case RGB888_FORMAT:
		fmt = V4L2_PIX_FMT_RGB24;
		break;
//	case YONLY_FORMAT:
//		fmt = V4L2_PIX_FMT_GREY;
//		break;
	default:
		isp_error("%s stream fmt error %d \r\n", __func__, ameba_fmt);
		return 0;
	}
	return fmt;
}

uint32_t get_stream_fd(uint8_t stream_id)
{
	uint32_t v4l2_fd;
	//int ret = 0;
	switch (stream_id) {
	case 0:
		v4l2_fd = ID_RTS_VIDEO_DEV1;
		break;
	case 1:
		v4l2_fd = ID_RTS_VIDEO_DEV2;
		break;
	case 2:
		v4l2_fd = ID_RTS_VIDEO_DEV3;
		break;
	case 3:
		v4l2_fd = ID_RTS_VIDEO_DEV4;
		break;
	case 4:
		v4l2_fd = ID_RTS_NN_DEV;
		break;
	default:
		isp_error("%s stream id error %d \r\n", __func__, stream_id);
		return 0;
	}
	return v4l2_fd;

}

int get_stream_cnt(uint8_t stream_id)
{
	uint32_t v4l2_fd;
	v4l2_fd = get_stream_fd(stream_id);
	//isp_info("%s v4l2_fd %d \r\n", __func__, v4l2_fd);
	if (v4l2_fd) {
		return ameba_get_stream_cnt(v4l2_fd);
	} else {
		return 0;
	}

}

int stream_close(uint8_t stream_id)
{
	uint32_t v4l2_fd;
	int ret = 0;
	struct rtscam_video_stream *stream;
	v4l2_fd = get_stream_fd(stream_id);
	if (v4l2_fd == 0) {
		return -1;
	}
	ret = rts_rtsv_streamoff(v4l2_fd);
	if (ret) {
		printf("rts_rtsv_streamoff failed %d\n", ret);
		return -1;
	} else {
		printf("rts_rtsv_streamoff done <%d> \n", __LINE__);
	}
	ret = rts_v4l2_request_bufs(v4l2_fd, 0);
	if (ret) {
		printf("rts_rtsv_request_bufs off failed %d\n", ret);
		return -1;
	} else {
		printf("rts_rtsv_request_bufs off done<%d> \n", __LINE__);
	}
	stream = get_stream(v4l2_fd);
	if (stream->stream_frame_done)
		vQueueDelete(stream->stream_frame_done);
	stream->stream_frame_done = NULL;
	//rts_v4l2_close(v4l2_fd);

	return ret;
}

uint32_t get_latest_frame_buffer(uint8_t stream_id)
{
	uint32_t v4l2_fd;
	uint32_t buf;
	//struct v4l2_requestbuffers buf;

	int ret = 0;
	v4l2_fd = get_stream_fd(stream_id);
	if (v4l2_fd == 0) {
		isp_error("%s v4l2_fd NULL\r\n", __func__);
		return 0;
	}
	ret = rts_v4l2_get_buffer(v4l2_fd, &buf);

	if (ret) {
		isp_error("%s failed ret %d \r\n", __func__, ret);
		return 0;
	} else {
		return buf;
	}
}

int release_frame_buffer(uint8_t stream_id, uint32_t buf_addr)
{
	uint32_t v4l2_fd;
	uint32_t buf;

	int ret = 0;
	v4l2_fd = get_stream_fd(stream_id);
	if (v4l2_fd == 0) {
		isp_error("%s v4l2_fd NULL \r\n", __func__);
		return -1;
	}
	//if (buf_addr == 0) {
	//	isp_error("%s buf_addr NULL \r\n", __func__);
	//	return -1;
	//}
	//buf.memory = buf_addr;
	buf = buf_addr;
	ret = rts_rtsv_put_buffer(v4l2_fd, &buf);

	if (ret) {
		isp_error("%s failed ret %d \r\n", __func__, ret);
	}

	return ret;


}


int get_skip_para(uint8_t stream_id, uint32_t *skip_m, uint32_t *skip_n)
{
	uint32_t fd;
	struct v4l2_streamparm parm;
	int ret = 0;
	fd = get_stream_fd(stream_id);
	if (fd < 0)
		return -RTS_E_NOT_OPEN;

	memset(&parm, 0, sizeof(parm));

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = ioctl(fd, VIDIOC_G_PARM, &parm);
	if (0 > ret) {
		isp_error("v4l2 ioctl G_PARM fail. %d\n", ret);
		return ret;
	}

	if (skip_m)
		*skip_m = parm.parm.capture.skip_m;
	if (skip_n)
		*skip_n = parm.parm.capture.skip_n;

	return RTS_OK;
}





