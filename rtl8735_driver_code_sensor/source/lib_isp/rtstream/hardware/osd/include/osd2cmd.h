/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/include/osd2cmd.h
 *
 * Copyright (C) 2016      Wil_shi<wil_shi@realsil.com.cn>
 */
#ifndef _RTSOSD2_CMD_H
#define _RTSOSD2_CMD_H

#include <stdint.h>

enum osd2_cmd_name {
	OSD2_PAINTER_CMD_CODE,
	OSD2_PAINTER_ATTRIBUTE,
	OSD2_PAINTER_LINK_ADDR,

	OSD2_PAINTER_FRAME_WIDTH,
	OSD2_PAINTER_FRAME_HEIGHT,
	OSD2_PAINTER_FRAME_Y_ADDR,
	OSD2_PAINTER_FRAME_UV_ADDR,

	OSD2_PAINTER_BLK_START_X,
	OSD2_PAINTER_BLK_START_Y,
	OSD2_PAINTER_BLK_WIDTH,
	OSD2_PAINTER_BLK_HEIGHT,
	OSD2_PAINTER_BLK_START_ADDR,
	OSD2_PAINTER_BLK_OVERLAY_MODE,
	OSD2_PAINTER_BLK_COLOR_MODE,
	OSD2_PAINTER_BLK_PURE_COLOR_RGB,
	OSD2_PAINTER_BLK_UV_DISABLE,
	OSD2_PAINTER_BLK_RGB2YUV_BYPASS,
	OSD2_PAINTER_BLK_Y_INCR_ENABLE,
	OSD2_PAINTER_BLK_Y_INCREASE,
	OSD2_PAINTER_BLK_Y_INCR_THD,
	OSD2_PAINTER_COLOR_TABLE_ADDR,
};

void rts_osd2_set_cmd(uint8_t *addr, enum osd2_cmd_name name,
		uint32_t value);
uint32_t rts_osd2_get_cmd(uint8_t *addr, enum osd2_cmd_name name);
void rts_dump_frame_cmd(uint8_t *addr);
void rts_dump_blk_cmd(uint8_t *addr);
#endif
