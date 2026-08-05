/*
 * Realtek Semiconductor Corp.
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _CORE_RTSAVUNIT_H
#define _CORE_RTSAVUNIT_H

#include <stdint.h>
#include <rtsavdef.h>
#include "rtsavpriv.h"

struct rts_av_cmd_t {
	uint32_t cmd_id;
	uint32_t arg[4];
	void *pdata;
};

int rts_av_osdenc_exec_cmd(int chn_id, int buf_id, struct rts_av_cmd_t *pcmd);

#endif
