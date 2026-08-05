/*
 * Realtek Semiconductor Corp.
 *
 * librtspigeon/include/buffer.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBRTSUOCTL_H
#define _LIBRTSUOCTL_H

#include <rts_time.h>
#include "basic_types.h"
//#include "rts_camera_soc.h"

/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
#define	IOCPARM_MASK	0x1fff		// parameter length, at most 13 bits
#define	IOCPARM_LEN(x)	(((x) >> 16) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~IOCPARM_MASK)
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

#define	IOCPARM_MAX	NBPG		// max size of ioctl, mult. of NBPG
#define	IOC_VOID	0x20000000	// no parameters
#define	IOC_OUT		0x40000000	// copy out parameters
#define	IOC_IN		0x80000000	// copy in parameters
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
#define	IOC_DIRMASK	0xe0000000	// mask for IN/OUT/VOID

#define _IOC(inout,group,num,len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
// this should be _IORW, but stdio got there first
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))
*/

#define ID_RTS_ISP_DEV		10001

#define ID_RTS_VIDEO_DEV1	10051
#define ID_RTS_VIDEO_DEV2	10052
#define ID_RTS_VIDEO_DEV3	10053
#define ID_RTS_VIDEO_DEV4	10054
#define ID_RTS_NN_DEV		10061

#define ID_RTS_MD2_DEV		11001

#define ID_RTS_UDS_SOCK		20001

#define ID_RTS_POLL_WQ		30001
#define ID_RTS_POLL_TRIG	30002


typedef void (*isp_callback_t)(void *);
void hal_isp_en_mcu_interrupt(BOOL en, int id, isp_callback_t callback, void *para);

int rts_ioctl(int, unsigned long, ...);
int rts_epoll_wait(int fd);
int rts_rev_ioctl(void *data, void *buf, int len);
int rts_open(const char *pathname);
int rts_close(int fd);
long rts_get_pgsize(void);
void *rts_reg_mmap(unsigned long base, unsigned int size);
void rts_reg_munmap(void *preg, unsigned int size);
void *rts_mmap(int fd, unsigned long base, unsigned int size);
void rts_munmap(void *preg, unsigned int size);
int rts_usleep(unsigned int usec);
int rts_waitevent(unsigned int *sem, unsigned int usec);
int rts_setevent(unsigned int sem);
int rts_irqsetevent(unsigned int sem);
int get_file_size(unsigned int addr);
//int rts_isp_send_cmd(struct rtscam_soc_cmd_stru *cmd, unsigned int timeout);
int rts_reg_isr_cb(BOOL en, int id, isp_callback_t callback, void *para);
int rts_gettime(struct tm *ptime);
int rts_get_time_count(void);

#endif
