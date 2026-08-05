/*
 * Realtek Semiconductor Corp.
 *
 * include/uapi/linux/rts_rtstream.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTS_RTSTREAM_H
#define _INCLUDE_RTS_RTSTREAM_H

#include <linux/v4l2-osdep.h>

struct rtstream_cmd_t {
	__u32 status;
	__u32 target;
	__u32 cmdcode;
	__s32 errcode;
	__u32 args[4];
	__u32 reserved[8];
	__u8 data[1024];
};

struct rtstream_sys_t {
	struct rtstream_cmd_t info;
	__u8 sn_bitmap[64];
	__u8 reserved[64];
	__u32 vreg[1024];
};

#define RTS_RTSTREAM_IOC_MAGIC		'R'

#define RTSTREAM_IOC_G_VMEM		_IOWR(RTS_RTSTREAM_IOC_MAGIC, 0x1, unsigned long)
#define RTSTREAM_IOC_LOCK		_IO(RTS_RTSTREAM_IOC_MAGIC, 0x2)
#define RTSTREAM_IOC_UNLOCK		_IO(RTS_RTSTREAM_IOC_MAGIC, 0x3)

#endif
