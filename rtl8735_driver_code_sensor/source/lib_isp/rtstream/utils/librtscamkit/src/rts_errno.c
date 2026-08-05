/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rts_errno.c
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rts_errno.h>

char *rts_strerrno(int errnum)
{
	char *desc = NULL;

	if (errnum < 0)
		errnum = -errnum;

	switch (errnum) {
	case RTS_FAIL:
		desc = "fail";
		break;
	case RTS_E_NULL_POINT:
		desc = "null point";
		break;
	case RTS_E_NO_MEMORY:
		desc = "out of memory";
		break;
	case RTS_E_NOT_REALIZED:
		desc = "not realized";
		break;
	case RTS_E_EXIST:
		desc = "exist";
		break;
	case RTS_E_NOT_EXIST:
		desc = "not exist";
		break;
	case RTS_E_NOT_FOUND:
		desc = "not found";
		break;
	case RTS_E_NOT_REGISTERED:
		desc = "not registered";
		break;
	case RTS_E_NOT_READY:
		desc = "not ready";
		break;
	case RTS_E_EMPTY:
		desc = "empty";
		break;
	case RTS_E_NOT_EMPTY:
		desc = "not empty";
		break;
	case RTS_E_FULL:
		desc = "full";
		break;
	case RTS_E_INVALID_ARG:
		desc = "invalid argument";
		break;
	case RTS_E_INVALID_TYPE:
		desc = "invalid type";
		break;
	case RTS_E_NOT_MATCH:
		desc = "not match";
		break;
	case RTS_E_OPEN_FAIL:
		desc = "open fail";
		break;
	case RTS_E_CLOSE_FAIL:
		desc = "close fail";
		break;
	case RTS_E_NOT_OPEN:
		desc = "not open";
		break;
	case RTS_E_GET_FAIL:
		desc = "get fail";
		break;
	case RTS_E_SET_FAIL:
		desc = "set fail";
		break;
	case RTS_E_NOT_SUPPORT:
		desc = "not support";
		break;
	case RTS_E_INITIALIZED:
		desc = "initialized";
		break;
	case RTS_E_NOT_INITIALIZED:
		desc = "not initialized";
		break;
	case RTS_E_INUSE:
		desc = "in use";
		break;
	case RTS_E_WRITE_FAIL:
		desc = "write fail";
		break;
	case RTS_E_READ_FAIL:
		desc = "read fail";
		break;
	case RTS_E_LOCK_FAIL:
		desc = "lock fail";
		break;
	case RTS_E_INVALID_LENGTH:
		desc = "invalid length";
		break;
	case RTS_E_TIMEOUT:
		desc = "timeout";
		break;
	case RTS_E_THREAD_FAIL:
		desc = "thread fail";
		break;
	case RTS_E_OVERFLOW:
		desc = "overflow";
		break;
	case RTS_E_BIG:
		desc = "too large";
		break;
	case RTS_E_PERM:
		desc = "operation not permitted";
		break;
	case RTS_E_NO_ENT:
		desc = "no such file or directory";
		break;
	case RTS_E_IO:
		desc = "I/O fail";
		break;
	case RTS_E_AGAIN:
		desc = "try again";
		break;
	case RTS_E_NO_DEV:
		desc = "no such device";
		break;
	case RTS_E_NO_SYS:
		desc = "function not implemented";
		break;
	case RTS_E_IOCTL:
		desc = "ioctl fail";
		break;
	case RTS_E_LESS_DATA:
		desc = "not enough data";
		break;
	case RTS_E_OUT_OF_RANGE:
		desc = "out of range";
		break;
	case RTS_E_MMAP_FAIL:
		desc = "mmap fail";
		break;
	case RTS_E_MUNMAP_FAIL:
		desc = "munmap fail";
		break;
	case RTS_E_INVALID_DATA:
		desc = "wrong data";
		break;
	case RTS_E_NO_REALIZED:
		desc = "not realized";
		break;
	case RTS_E_INVALID_VERSION:
		desc = "wrong version";
		break;
	case RTS_E_UNKNOWN:
		desc = "unknown";
		break;
	case RTS_E_RECEIVE_FAIL:
		desc = "receive fail";
		break;
	case RTS_E_SEND_FAIL:
		desc = "send fail";
		break;
	case RTS_E_DISCONNECT:
		desc = "disconnect";
		break;
	case RTS_E_SAVE_FAIL:
		desc = "file save fail";
		break;
	case RTS_E_CMP_FAIL:
		desc = "data compare fail";
		break;
	case RTS_E_ERASE_FAIL:
		desc = "erase flash fail";
		break;
	case RTS_E_RESET_FAIL:
		desc = "reset flash fail";
		break;
	case RTS_E_DISABLE:
		desc = "disable";
		break;
	case RTS_E_NOT_EQUAL:
		desc = "not equal";
		break;
	case RTS_E_EQUAL:
		desc = "equal";
		break;
	case RTS_E_CMD_ERROR:
		desc = "cmd error";
		break;
	case RTS_E_INVALID_CMD:
		desc = "invalid cmd";
		break;
	case RTS_E_MISMATCH:
		desc = "mismatch";
		break;
	case RTS_E_BUF_OVERFLOW:
		desc = "buffer overflow";
		break;
	case RTS_E_NOT_CROSS:
		desc = "not cross";
		break;
	case RTS_E_NOT_PARALLEL:
		desc = "not parallel";
		break;
	case RTS_E_PARALLEL:
		desc = "parallel";
		break;
	case RTS_E_CONFILCT:
		desc = "conflict";
		break;
	case RTS_E_BUSY:
		desc = "busy";
		break;
	case RTS_E_CHANGED:
		desc = "changed";
		break;
	default:
		desc = "unknown errno";
		break;
	}

	return desc;
}

int RTS_IS_ERR(int ret)
{
	return RTS_IS_ERR_VALUE(ret);
}
