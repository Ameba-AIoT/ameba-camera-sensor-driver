/*
 * Realtek Semiconductor Corp.
 *
 * Encoder device driver (kernel module header)
 *
 * rts_camera_hx280enc.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
--------------------------------------------------------------------------------
--
--  Abstract : 6280/7280/8270/8290/H1 Encoder device driver (kernel module)
--
------------------------------------------------------------------------------
 */
#ifndef _U_RTS_CAMERA_HX280ENC_H
#define _U_RTS_CAMERA_HX280ENC_H

/*
 * Ioctl definitions
 */

/* Use 'h' as magic number */
#define HX280ENC_IOC_MAGIC  'h'
/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */
#define HX280ENC_IOCGHWOFFSET	_IOCTL_IOR(HX280ENC_IOC_MAGIC,  3, unsigned long)
#define HX280ENC_IOCGHWIOSIZE	_IOCTL_IOR(HX280ENC_IOC_MAGIC,  4, unsigned int)
#define HX280ENC_IOC_CLI	_IOCTL_IO(HX280ENC_IOC_MAGIC,  5)
#define HX280ENC_IOC_STI	_IOCTL_IO(HX280ENC_IOC_MAGIC,  6)
#define HX280ENC_IOCXVIRT2BUS	_IOCTL_IOWR(HX280ENC_IOC_MAGIC, 7, unsigned long)
#define HX280ENC_IOC_SENCODE_TIME	_IOCTL_IO(HX280ENC_IOC_MAGIC,  12)
#define HX280ENC_IOC_GENCODE_TIMEBUF	_IOCTL_IO(HX280ENC_IOC_MAGIC,  13)

/* debugging tool */
#define HX280ENC_IOCHARDRESET      _IOCTL_IO(HX280ENC_IOC_MAGIC, 8)
#define HX280ENC_IOC_DONE	_IOCTL_IO(HX280ENC_IOC_MAGIC, 9)
#define HX280ENC_IOC_ENABLE	_IOCTL_IO(HX280ENC_IOC_MAGIC, 10)
#define HX280ENC_IOC_DISABLE	_IOCTL_IO(HX280ENC_IOC_MAGIC, 11)

#define HX280ENC_IOC_MAXNR	13

#endif
