/*
 * Realtek Semiconductor Corp.
 * ../../../../include/uapi/linux/rts_camera_isp.h
 * Copyright (C) 2014 Grant Shen <grant_shen@realsil.com.cn>
 */
#ifndef _U_RTS_CAMERA_ISP_H
#define _U_RTS_CAMERA_ISP_H

#include "v4l2-osdep.h"
#include "rts_camera_isp_snr.h"
#include "rts_camera_isp_info.h"

struct rtscam_isp_mem_alloc_info {
	__u32 phy_addr;
	__u32 length;
	char info[32];
};

enum rtscam_isp_pin_state {
	PIN_STATE_NONE,
	PIN_STATE_DVP,
	PIN_STATE_MIPI,
};

enum rtscam_isp_clock_type {
	CLOCK_INTERFACE,
	CLOCK_ISP,
	CLOCK_MIPIOUT,
};

struct rtscam_isp_clock {
	enum rtscam_isp_clock_type type;
	unsigned long rate;
};

enum rtscam_isp_event {
	RTSCAM_ISP_DATA_START,
	RTSCAM_ISP_FRAME_END,
};

#define RTSISP_IOC_MAGIC 'E'

#define RTSISP_IOC_GET_IO_START _IOCTL_IOR(RTSISP_IOC_MAGIC, 0, __u32)
#define RTSISP_IOC_GET_IO_SIZE _IOCTL_IOR(RTSISP_IOC_MAGIC, 1, __u32)
#define RTSISP_IOC_POWER _IOCTL_IOW(RTSISP_IOC_MAGIC, 2, struct rts_isp_snr_pwr)
#define RTSISP_IOC_I2C_READ _IOCTL_IOWR(RTSISP_IOC_MAGIC, 3, struct rts_isp_i2c)
#define RTSISP_IOC_I2C_WRITE _IOCTL_IOW(RTSISP_IOC_MAGIC, 4, struct rts_isp_i2c)
#define RTSISP_IOC_REG_SUBDEV _IOCTL_IOW(RTSISP_IOC_MAGIC, 5, struct rts_isp_info)
#define RTSISP_IOC_UNREG_SUBDEV _IOCTL_IO(RTSISP_IOC_MAGIC, 6)
#define RTSISP_IOC_SYNC_WRITE _IOCTL_IOW(RTSISP_IOC_MAGIC, 7, \
				   struct rts_isp_sync_regs)
#define RTSISP_IOC_INIT_STATIS _IOCTL_IOW(RTSISP_IOC_MAGIC, 8, __u32)
#define RTSISP_IOC_CLEANUP_STATIS _IOCTL_IO(RTSISP_IOC_MAGIC, 9)
#define RTSISP_IOC_GET_STATIS_INFO _IOCTL_IOR(RTSISP_IOC_MAGIC, 10, \
					struct rts_isp_statis_info)
#define RTSISP_IOC_PUT_STATIS _IOCTL_IOW(RTSISP_IOC_MAGIC, 11, __u32)
#define RTSISP_IOC_MEM_ALLOC _IOCTL_IOWR(RTSISP_IOC_MAGIC, 12, \
				   struct rtscam_isp_mem_alloc_info)
#define RTSISP_IOC_MEM_FREE _IOCTL_IOW(RTSISP_IOC_MAGIC, 13, __u32)
#define RTSISP_IOC_SEL_PIN_STATE _IOCTL_IOW(RTSISP_IOC_MAGIC, 14, \
				      enum rtscam_isp_pin_state)
#define RTSISP_IOC_NOTIFY_DYN_FPS _IOCTL_IOW(RTSISP_IOC_MAGIC, 15, __u32)
#define RTSISP_IOC_GET_ISP_CLOCK _IOCTL_IO(RTSISP_IOC_MAGIC, 16)
#define RTSISP_IOC_PUT_ISP_CLOCK _IOCTL_IO(RTSISP_IOC_MAGIC, 17)
#define RTSISP_IOC_SET_CLOCK _IOCTL_IOWR(RTSISP_IOC_MAGIC, 18, \
				   struct rtscam_isp_clock)
#define RTSISP_IOC_IS_FPGA _IOCTL_IOR(RTSISP_IOC_MAGIC, 19, __s32)


#define RTSISP_IOC_WAIT_EVENT _IOCTL_IOR(RTSISP_IOC_MAGIC, 20, __s32)
#define RTSISP_IOC_SYNC_LOCK _IOCTL_IOR(RTSISP_IOC_MAGIC, 21, __s32)
#define RTSISP_IOC_TEST_PREVIEW _IOCTL_IOW(RTSISP_IOC_MAGIC, 22, __u32)
#define RTSISP_IOC_GET_TNR_BIT _IOCTL_IOR(RTSISP_IOC_MAGIC, 23, __u32)

#define RTSISP_IOC_POLL _IOCTL_IOR(RTSISP_IOC_MAGIC, 24, __s32)
//#define RTSISP_IOC_POLL _IOCTL_IOR(RTSISP_IOC_MAGIC, 22, __s32)
#define RTSISP_IOC_APHY_I2C_WRITE _IOCTL_IOWR(RTSISP_IOC_MAGIC, 30, struct rts_isp_i2c)





#endif /* _U_RTS_CAMERA_ISP_H */
