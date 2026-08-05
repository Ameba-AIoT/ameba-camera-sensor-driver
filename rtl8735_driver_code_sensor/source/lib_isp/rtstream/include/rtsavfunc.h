/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsavfunc.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSAVFUNC_H
#define _INCLUDE_RTSAVFUNC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "rtsavdef.h"

enum {
	RTS_CMD_DIR_N = 0,
	RTS_CMD_DIR_R = (1 << 0),
	RTS_CMD_DIR_W = (1 << 1),
	RTS_CMD_DIR_RW = RTS_CMD_DIR_R | RTS_CMD_DIR_W
};

#define rts_av_cmd_id(type, dir, id)	rts_av_fourcc('r', type, dir, id)

#define __AV_CMD_TYPE(cmd)		(((cmd) >> 8) & 0xff)
#define __AV_CMD_DIR(cmd)		(((cmd) >> 16) & 0xff)

#ifdef __cplusplus
}
#endif
#endif
