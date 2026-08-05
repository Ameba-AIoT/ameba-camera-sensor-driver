/*
 * Realtek Semiconductor Corp.
 *
 * rts_hw_id.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_HW_ID_H
#define _RTS_HW_ID_H

enum {
	TYPE_RLE0745 = 1,
	TYPE_RTS3901 = 2,
	TYPE_RTS3903 = 3,
	TYPE_RTS3913 = 4,
	TYPE_RTS3915 = 5,

	TYPE_FPGA = (1 << 16),
};

#define RTS_SOC_CAM_HW_ID(type)		((type) & 0xff)

#endif
