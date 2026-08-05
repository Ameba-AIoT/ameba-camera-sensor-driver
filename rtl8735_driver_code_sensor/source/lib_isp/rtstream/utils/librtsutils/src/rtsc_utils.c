/*
 * Realtek Semiconductor Corp.
 *
 * rtsutils/rtsc_utils.c
 *
 * Copyright (C) 2019      Wind Han<wind_han@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cmsis_os2.h"
#include "rlx_cpu.h"
#include <rts_camera_soc.h>
#include <rts_camera.h>
#include "rts_ioctl.h"
#include "rts_camera_mem.h"
//#define open rts_open
//#define close rts_close
#define ioctl rts_ioctl
#include <errno.h>
#include <string.h>
//#include <assert.h>
#include <rtscamkit.h>
#include <rtsv4l2.h>
#include "rts_isp_mem.h"
#include "rts_camera_soc.h"
#include "rts_camera_hx280enc.h"
#include "rts_camera_jpgenc.h"
//#include "rts_camera_lock.h"
#include "rts_camera_osd2.h"
#include "rtsc.h"

#define RTSC_CTRL_DEV			"/dev/rtscamctrl"
#define RTSC_MEM_DEV			"/dev/rtsmem"
#define RTSC_SOC_DEV			"/dev/rtscam"
//#define RTSC_LOCK_DEV			"/dev/rtslock"
#define RTSC_ZOOM_DEV			"/dev/rtszoom"
#define RTSC_RTSTREAM_DEV		"/dev/rtstream"

#define RTSC_VIDEO_ID_OFFSET		51

int rtsc_v4l2_open(int isp_id)
{
	char dev_node[64];
	int fd;

	if (isp_id < 0)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	snprintf(dev_node, sizeof(dev_node), "/dev/video%d",
		RTSC_VIDEO_ID_OFFSET + isp_id);

	fd = rts_open(dev_node);
	if (fd < 0) {
		isp_error("open isp device %s fail, error = %d\n",
			dev_node, RTS_RETURN(RTS_E_OPEN_FAIL));
		return RTS_RETURN(RTS_E_OPEN_FAIL);
	}

	return fd;
}

int rtsc_rtsv_close(int fd)
{
	RTS_SAFE_CLOSE(fd, rts_close);

	return RTS_OK;
}

int rtsc_zoom_open(void)
{
	return rts_open(RTSC_ZOOM_DEV);
}

int rtsc_zoom_close(int fd)
{
	RTS_SAFE_CLOSE(fd, rts_close);
	return RTS_OK;
}

unsigned long rtsc_get_video_phy_addr(int fd, unsigned long vm_addr)
{
	int ret;
	unsigned long addr = vm_addr;

	if (fd < 0)
		return 0;

	ret = ioctl(fd, RTSCAMIOC_GET_PHYADDDR, &addr);
	if (ret)
		return 0;

	return addr;
}

int rtsc_ctrl_open(void)
{
	return rts_open(RTSC_CTRL_DEV);
}

int rtsc_ctrl_close(int fd)
{
	RTS_SAFE_CLOSE(fd, rts_close);

	return RTS_OK;
}

int rtsc_exec_vendor_cmd(int fd, unsigned int cmdcode, void *arg)
{
	struct rtscam_vcmd rts_cmd;
	int ret;

	if (fd < 0)
		return RTS_RETURN(RTS_E_NOT_OPEN);

	rts_cmd.cmdcode = cmdcode;
	rts_cmd.arg = arg;

	ret = ioctl(fd, RTSCAMIOC_VENDOR_CMD, &rts_cmd);
	if (ret) {
		isp_error("exec vendor cmd fail, %d\n", RTS_RETURN(RTS_E_IOCTL));
		return RTS_RETURN(RTS_E_IOCTL);
	}

	return RTS_OK;
}

int rtsc_get_streamid(int fd)
{
	int streamid = 0;
	int ret = RTS_OK;

	ret = rtsc_exec_vendor_cmd(fd, RTSOCIOC_G_STREAMID, &streamid);
	if (ret) {
		isp_error("get stream id fail, ret = %d\n", ret);
		return ret;
	}

	return streamid;
}

int rtsc_soc_open(int oflag)
{
	return rts_open(RTSC_SOC_DEV);
}

int rtsc_soc_close(int fd)
{
	RTS_SAFE_CLOSE(fd, rts_close);

	return RTS_OK;
}

int rtsc_pause(void)
{
	int ret = RTS_OK;
	int fd = rtsc_ctrl_open();

	if (fd < 0)
		return RTS_RETURN(RTS_E_OPEN_FAIL);

	ret = rtsc_exec_vendor_cmd(fd, RTSOCIOC_PAUSE, NULL);
	RTS_SAFE_CLOSE(fd, rtsc_ctrl_close);

	return ret;
}

int rtsc_resume(void)
{
	int ret = RTS_OK;
	int fd = rtsc_ctrl_open();

	if (fd < 0)
		return RTS_RETURN(RTS_E_OPEN_FAIL);

	ret = rtsc_exec_vendor_cmd(fd, RTSOCIOC_RESUME, NULL);
	RTS_SAFE_CLOSE(fd, rtsc_ctrl_close);

	return ret;
}

int rtsc_soc_detach(void)
{
	int ret;
	int fd = rtsc_soc_open(O_RDWR | O_NONBLOCK);

	if (fd < 0)
		return RTS_RETURN(RTS_E_OPEN_FAIL);

	ret = ioctl(fd, RTSOCIOC_CAMERA_DETACH);
	RTS_SAFE_CLOSE(fd, rtsc_soc_close);

	if (ret)
		return RTS_RETURN(RTS_FAIL);

	return RTS_OK;
}

int rtsc_soc_attach(void)
{
	int ret;
	int fd = rtsc_soc_open(O_RDWR | O_NONBLOCK);

	if (fd < 0)
		return RTS_RETURN(RTS_E_OPEN_FAIL);

	ret = ioctl(fd, RTSOCIOC_CAMERA_ATTACH);
	RTS_SAFE_CLOSE(fd, rtsc_soc_close);

	if (ret)
		return RTS_RETURN(RTS_FAIL);

	return RTS_OK;
}

