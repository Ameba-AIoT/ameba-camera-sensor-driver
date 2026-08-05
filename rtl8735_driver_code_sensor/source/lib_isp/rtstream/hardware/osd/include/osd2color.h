/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/include/osd2color.h
 *
 * Copyright (C) 2016      Wil Shi<wil_shi@realsil.com.cn>
 */
#ifndef _RTSOSD2_COLOR_H
#define _RTSOSD2_COLOR_H

#include <stdint.h>
#include <rtsc.h>
#include <rtsosd2.h>

#define OSD2_COLOR_TABLE_CHAR_NUM	224

enum osd2_color_type {
	OSD2_COLOR_TYPE_A,
	OSD2_COLOR_TYPE_R,
	OSD2_COLOR_TYPE_G,
	OSD2_COLOR_TYPE_B,
	OSD2_COLOR_TYPE_RESERVED,
};

int osd2_set_color_table(struct rtsc_dma_buffer *buffer,
		int fmt, uint32_t val,
		uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
uint32_t osd2_get_color_table(struct rtsc_dma_buffer *buffer,
		int fmt, uint8_t red, uint8_t green,
		uint8_t blue, uint8_t alpha);
int osd2_set_default_color_table(struct rtsc_dma_buffer *buffer);
int osd2_dump_color_table(struct rtsc_dma_buffer *buffer);

#endif


