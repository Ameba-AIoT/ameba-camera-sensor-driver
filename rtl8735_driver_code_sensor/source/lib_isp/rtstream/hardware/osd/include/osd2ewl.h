/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/include/osd2ewl.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTSOSD2_INCLUDE_EWL_H
#define _RTSOSD2_INCLUDE_EWL_H

#include <stdint.h>

const void *osd2_ewl_init(void);
int osd2_ewl_release(const void *inst);
uint32_t osd2_ewl_read_reg(const void *inst, uint32_t offset);
void osd2_ewl_write_reg(const void *inst, uint32_t offset, uint32_t val);

int32_t osd2_ewl_reserve_hw(const void *inst);
int32_t osd2_ewl_wait_hw_ready(const void *inst);
void osd2_ewl_release_hw(const void *inst);
void osd2_ewl_start_hw(const void *inst);

int osd2_ewl_check_done(const void *inst);
int osd2_ewl_make_rdy(const void *inst);
int osd2_ewl_set_epoll_hook(const void *inst, void *master,
			    int (*hook_func)(void *master, int fd));
int osd2_ewl_use_sigio(const void *inst, int sigio_need);
int osd2_ewl_use_inter(const void *inst, int inter_need);
int osd2_ewl_print(const void *inst);
#endif
