/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/ewl/ewl_osd2_common.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTSOSD2_EWL_OSD2_COMMON_H
#define _RTSOSD2_EWL_OSD2_COMMON_H
#include <stdint.h>

struct rts_osd2_ewl_t {
	int inited;
	const void *reginst;
	//unsigned long key;

	//int sigio_need;
	//pthread_mutex_t lock;
	osMutexId_t lock;  //protect HW, get from driver
	//pthread_cond_t cond;
	//osSemaphoreId_t cond;  //inform osd process finished
	//int (*get_epoll_hook)(void *master, int fd);
	//void *master;
	//int signal;
	unsigned long e_count;
	unsigned long t_count;
};

#endif
