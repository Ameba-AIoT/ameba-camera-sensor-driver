/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rtsmem.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cmsis_os.h"

unsigned int rts_get_current_msec(void)
{
	return (xTaskGetTickCount() / portTICK_PERIOD_MS);
}

