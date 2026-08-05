/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsc_hwver.h
 *
 * Copyright (C) 2019      Wind Han<wind_han@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSCAM_HWVER_H
#define _INCLUDE_RTSCAM_HWVER_H

#include <stdint.h>

enum {
	RTSC_HW_ID_VER_UNKNOWN = 0,
	RTSC_HW_ID_VER_RLE0745,
	RTSC_HW_ID_VER_RTS3901,
	RTSC_HW_ID_VER_RTS3903,
	RTSC_HW_ID_VER_RTS3913,
	RTSC_HW_ID_VER_RTS3915,
};

struct rtsc_hw_id {
	uint16_t hw_ver;
	uint32_t hw_id;
};

struct rtsc_hw_id rtsc_get_hw_id(void);

#endif
