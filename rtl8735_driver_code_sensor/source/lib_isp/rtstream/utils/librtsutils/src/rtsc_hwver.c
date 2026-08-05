/*
 * Realtek Semiconductor Corp.
 *
 * rtsutils/rtsc_hwver.c
 *
 * Copyright (C) 2019      Wind Han<wind_han@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os2.h"
#include "rt_task.h"
#include "linux/rts_camera_soc.h"
#include "rts_ioctl.h"
#define ioctl rts_ioctl
#include <string.h>
#include <errno.h>
#include <rtscamkit.h>
#include "rts_camera_soc.h"
#include "rtsc_hwver.h"
#include "rtsc.h"

static struct rtsc_hw_id rts_hw_id = {
	.hw_ver = RTSC_HW_ID_VER_UNKNOWN,
	.hw_id = 0,
};

#define HWVER_PATH		"/sys/devices/platform/ocp/rts_xb2/hwver"
#define HWID_PATH		"/sys/devices/platform/ocp/rts_xb2/hwid"

struct rtsc_hw_id __rtsc_get_hw_id(void)
{
	struct rtsc_hw_id rts_hwid;

	rts_hwid.hw_ver = RTSC_HW_ID_VER_RTS3915;
	rts_hwid.hw_id = (uint32_t)0x03000005;

	return rts_hwid;
}

struct rtsc_hw_id rtsc_get_hw_id(void)
{
	if (rts_hw_id.hw_ver == RTSC_HW_ID_VER_UNKNOWN)
		rts_hw_id = __rtsc_get_hw_id();

	return rts_hw_id;
}
