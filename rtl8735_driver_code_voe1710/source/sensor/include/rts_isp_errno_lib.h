#ifndef _RTS_ISP_ERRNO_H_INC_
#define _RTS_ISP_ERRNO_H_INC_

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif


enum rts_isp_boolean {
	RTS_ISP_FALSE = 0,
	RTS_ISP_TRUE,
};

enum rts_isp_errno {
	RTS_ISP_OK = 0,
	RTS_ISP_EPERM = 1,		/* Operation not permitted */
	RTS_ISP_EINTR = 4,		/* Interrupted system call */
	RTS_ISP_EAGAIN = 11,	/* Try again */
	RTS_ISP_ENOMEM = 12,	/* Out of memory */
	RTS_ISP_EACCES = 13,	/* Permission denied */
	RTS_ISP_EFAULT = 14,	/* Bad address */
	RTS_ISP_EBUSY = 16,		/* Device or resource busy */
	RTS_ISP_EEXIST = 17,	/* File exists */
	RTS_ISP_EINVAL = 22,	/* Invalid argument */
	RTS_ISP_ENOSPC = 28,	/* No space left on device */
	RTS_ISP_ERANGE = 34,	/* Math result not representable */
	RTS_ISP_ENAMETOOLONG = 36,  /**< File name too long. */
	RTS_ISP_ECONNRESET = 104,	/* Connection reset by peer */
	RTS_ISP_ETIMEDOUT = 116,	/**< Connection timed out. */
	/* private ERROR */
	RTS_ISP_ENOOPS = 200,
	RTS_ISP_ENOITEM,
	RTS_ISP_ENOTREADY,
	RTS_ISP_EPLUGIN,
	RTS_ISP_EPOLLERR,
	RTS_ISP_ECTRL,
	RTS_ISP_ECONFLICT,
	RTS_ISP_ECANCELD,
	RTS_ISP_EPROTOBUF,
	_MAX_RTS_ISP_ERRNO,
};

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_ERRNO_H_INC_ */
