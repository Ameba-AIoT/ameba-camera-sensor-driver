/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdarg.h>
#include <rts_isp_errno.h>

#define ISP_PRIV_ERR_BASE RTS_ISP_ENOOPS
#define pri_err_idx(err) ((err) - ISP_PRIV_ERR_BASE)

const char *rts_isp_err_msg[] = {
	[pri_err_idx(RTS_ISP_ENOOPS)] = "No such operating fuction",
	[pri_err_idx(RTS_ISP_ENOITEM)] = "No such item",
	[pri_err_idx(RTS_ISP_ENOTREADY)] = "Does not ready",
	[pri_err_idx(RTS_ISP_EPLUGIN)] = "Plugin error",
	[pri_err_idx(RTS_ISP_EPOLLERR)] = "Poll error",
	[pri_err_idx(RTS_ISP_ECTRL)] = "Control error",
	[pri_err_idx(RTS_ISP_ECONFLICT)] = "Conflict",
	[pri_err_idx(RTS_ISP_ECANCELD)] = "Operation Canceled",
	[pri_err_idx(RTS_ISP_EPROTOBUF)] = "Protobuf Operation Fail",
};

int rts_isp_strerror(int errnum, char *msg_buf, size_t size)
{
	errnum = -errnum;
	if (errnum < ISP_PRIV_ERR_BASE)
		return strerror_r(errnum, msg_buf, size);
	else if (errnum < _MAX_RTS_ISP_ERRNO)
		strncpy(msg_buf, rts_isp_err_msg[pri_err_idx(errnum)], size);
	else
		snprintf(msg_buf, size, "Unknown ISP errno: %d", errnum);
	msg_buf[size - 1] = '\0';
	return RTS_ISP_OK;
}

void rts_isp_perror(int errnum, const char *fmt, ...)
{
	va_list ap;
//	static char msg[256];

//	va_start(ap, fmt);
//	vprintf(fmt, ap);
//	va_end(ap);
//	rts_isp_strerror(errnum, msg, sizeof(msg));
	printf("%s\n",fmt);
//	printf(" -> %s\n", msg);
}
