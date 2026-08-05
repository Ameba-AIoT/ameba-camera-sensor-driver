/*
 * Realtek Semiconductor Corp.
 *
 * linux/rts_camera_lock.h
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LINUX_RTS_CAMERA_LOCK_H
#define _LINUX_RTS_CAMERA_LOCK_H

#define RTSCAMLOCK_IOC_MAGIC	'l'

struct rtscam_lock_num {
	unsigned long key;
	int num;
};

struct rtscam_lock_name {
	unsigned long key;
	char name[16];
};

#define RTSCAMLOCK_IOC_ALLOC	_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x1, unsigned long)
#define RTSCAMLOCK_IOC_FREE	_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x2, unsigned long)
#define RTSCAMLOCK_IOC_INIT	\
		_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x3, struct rtscam_lock_num)

#define RTSCAMLOCK_IOC_WAIT	_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x4, unsigned long)
#define RTSCAMLOCK_IOC_POST	_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x5, unsigned long)
#define RTSCAMLOCK_IOC_SET_NAME	\
		_IOCTL_IOW(RTSCAMLOCK_IOC_MAGIC, 0x6, struct rtscam_lock_name)

#endif
