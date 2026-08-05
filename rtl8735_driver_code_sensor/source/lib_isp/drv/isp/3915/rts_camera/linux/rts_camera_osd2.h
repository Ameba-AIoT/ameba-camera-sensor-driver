/*
 * Realtek Semiconductor Corp.
 *
 * ../../../../include/uapi/linux/rts_camera_osd2.h
 *
 * Copyright (C) 2016      wil_shi<wil_shi@realsil.com.cn>
 */
#ifndef _U_RTS_CAMERA_OSD_H
#define _U_RTS_CAMERA_OSD_H

#define RTSOSD2_IOC_MAGIC	'o'

#define RTSOSD2_IOCGHWOFFSET \
			_IOCTL_IOR(RTSOSD2_IOC_MAGIC, 1, unsigned long *)
#define RTSOSD2_IOCGHWIOSIZE \
			_IOCTL_IOR(RTSOSD2_IOC_MAGIC, 2, unsigned int *)
#define RTSOSD2_IOCDONE		_IOCTL_IO(RTSOSD2_IOC_MAGIC, 3)
#define RTSOSD2_IOC_ENABLE	_IOCTL_IO(RTSOSD2_IOC_MAGIC, 4)
#define RTSOSD2_IOC_DISABLE	_IOCTL_IO(RTSOSD2_IOC_MAGIC, 5)
#define RTSOSD2_IOC_WAIT_INTERRUPT	_IOCTL_IO(RTSOSD2_IOC_MAGIC, 6)


#define RTSOSD2_IOC_MAXNR	6

#endif
