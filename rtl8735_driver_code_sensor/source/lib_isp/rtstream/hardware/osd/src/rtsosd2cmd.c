/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/src/rtsosd2cmd.c
 *
 * Copyright (C) 2016     Wil Shi<wil_shi@realsil.com.cn>
 */
#include <stdio.h>
#include <rtscamkit.h>
#include <osd2cmd.h>
#include "isp_log.h"
//#include <assert.h>

struct osd2_cmd_field_t {
	uint8_t name;
	uint8_t base;
	uint32_t mask;
	uint8_t lsb;
	uint8_t rw;
	char *description;
};

#define RO	1
#define WO	2
#define RW	(RO | WO)

static const struct osd2_cmd_field_t CmdDesc[] = {
	{OSD2_PAINTER_CMD_CODE,		0x00,
			0x0f000000,	24,	RW,	"cmd code"},
	{OSD2_PAINTER_ATTRIBUTE,	0x00,
			0x001f0000,	16,	RW,     "cmd attibute"},
	{OSD2_PAINTER_FRAME_WIDTH,	0x01,
			0x0000ffff,	 0,	RW,	"frame width"},
	{OSD2_PAINTER_FRAME_HEIGHT,	0x02,
			0x0000ffff,	 0,	RW,	"frame height"},
	{OSD2_PAINTER_FRAME_Y_ADDR,	0x03,
			0xfffffff8,	 0,	RW,	"frame Y addr"},
	{OSD2_PAINTER_FRAME_UV_ADDR,	0x04,
			0xfffffff8,	 0,	RW,	"frame UV addr"},
	{OSD2_PAINTER_LINK_ADDR,	0x07,
			0xfffffff8,	 0,	RW,	"link addr"},
	{OSD2_PAINTER_BLK_START_X,	0x01,
			0xffff0000,	16,	RW,	"block start X"},
	{OSD2_PAINTER_BLK_START_Y,	0x01,
			0x0000ffff,	 0,	RW,	"block start Y"},
	{OSD2_PAINTER_BLK_WIDTH,	0x02,
			0xffff0000,	16,	RW,	"block width"},
	{OSD2_PAINTER_BLK_HEIGHT,	0x02,
			0x0000ffff,	 0,	RW,	"block height"},
	{OSD2_PAINTER_BLK_START_ADDR,	0x03,
			0xfffffff8,	 0,	RW,	"block start addr"},
	{OSD2_PAINTER_BLK_OVERLAY_MODE,	0x04,
			0x00000f00,	 8,	RW,	"block overlay mode"},
	{OSD2_PAINTER_BLK_COLOR_MODE,	0x04,
			0x0000000f,	 0,	RW,	"block color mode"},
	{OSD2_PAINTER_BLK_PURE_COLOR_RGB, 0x5,
			0xffffffff,	 0,	RW,	"block pure color RGB"},
	{OSD2_PAINTER_BLK_UV_DISABLE, 0x6,
			0x00000001,	 0,	RW,	"block UV disable"},
	{OSD2_PAINTER_BLK_RGB2YUV_BYPASS, 0x6,
			0x00000002,	 1,	RW,	"block RGB2YUV bypass"},
	{OSD2_PAINTER_BLK_Y_INCR_ENABLE, 0x6,
			0x00000004,	 2,	RW,	"block Y incr enable"},
	{OSD2_PAINTER_BLK_Y_INCREASE, 0x6,
			0x0000ff00,	 8,	RW,	"block Y increase"},
	{OSD2_PAINTER_BLK_Y_INCR_THD, 0x6,
			0x00ff0000,	 16,	RW,	"block Y incr thd"},
	{OSD2_PAINTER_COLOR_TABLE_ADDR,	 0x1,
			0xfffffff8,	 0,	RW,	"color table address"},
};

static const struct osd2_cmd_field_t *__find_cmd_field(enum osd2_cmd_name name)
{
	int i = 0;
	int len = RTS_ARRAY_SIZE(CmdDesc);

	for (i = 0; i < len; i++) {
		if (CmdDesc[i].name == name)
			return &CmdDesc[i];
	}

	return NULL;
}

static uint32_t __osd2_get_val(uint8_t *addr, uint8_t num)
{
	uint32_t val;

	val =  *(addr + num) | (*(addr + num + 1) << 8)
		| (*(addr + num + 2) << 16) | (*(addr + num + 3) << 24);
	return val;
}

void rts_osd2_set_cmd(uint8_t *addr, enum osd2_cmd_name name,
		uint32_t value)
{
	uint32_t val = 0;
	const struct osd2_cmd_field_t *field = __find_cmd_field(name);

	if (!addr) {
		printf("%s addr NULL\n", __func__);
		return;
	}

	if (!field) {
		isp_error("Can't find cmd(%d).\n", name);
		return;
	}

	if (!(field->rw & WO)) {
		isp_error("cmd(%d) isn't writable.\n", name);
		return;
	}

	val = __osd2_get_val(addr, field->base*4) & ~(field->mask);
	val = ((value << field->lsb) & field->mask) | val;
	*(addr + field->base*4) = (uint8_t)(val & 0xff);
	*(addr + field->base*4 + 1) = (uint8_t)((val >> 8) & 0xff);
	*(addr + field->base*4 + 2) = (uint8_t)((val >> 16) & 0xff);
	*(addr + field->base*4 + 3) = (uint8_t)((val >> 24) & 0xff);
}

uint32_t rts_osd2_get_cmd(uint8_t *addr, enum osd2_cmd_name name)
{
	uint32_t val;
	const struct osd2_cmd_field_t *field = __find_cmd_field(name);
	if (!addr) {
		printf("%s addr NULL\n", __func__);
		return 0;
	}

	if (!field) {
		isp_error("Can't find cmd(%d).\n", name);
		return 0;
	}

	if (!(field->rw & RO)) {
		isp_error("cmd(%d) isn't readable.\n", name);
		return 0;
	}

	val = __osd2_get_val(addr, field->base*4);
	val = (val & field->mask) >> field->lsb;

	return val;
}

