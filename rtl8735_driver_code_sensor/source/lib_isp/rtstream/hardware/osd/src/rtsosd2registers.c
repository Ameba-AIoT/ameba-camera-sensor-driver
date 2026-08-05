/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/src/rtsosd2registers.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include <rtscamkit.h>
#include "osd2ewl.h"
#include "osd2register.h"
#include "isp_log.h"
struct osd2_reg_field_t {
	uint32_t name;
	int32_t base;
	uint32_t mask;
	int32_t lsb; /*lsb for this field [31..0]*/
	int32_t rw; /*1=read-only,2=write-only,3=read-write*/
	char *description;
};

#define RO	1
#define WO	2
#define RW	(RO | WO)

static const struct osd2_reg_field_t asicRegisterDesc[] = {
	{OSD2_REG_PAINTER_START,	0x00,	0x00000001,
			0,	RW,	"write 1 to start osd cmd"},
	{OSD2_REG_PAINTER_STOP,		0x00,	0x00000002,
			1,	RW,	"write 1 to stop osd and reset"},
	{OSD2_REG_CMD_ADDR,		0x04,	0xfffffff8,
			0,	RW,	"osd2 cmd address"},
	{OSD2_REG_UV_POS,		0x08,	0x00000004,
			2,	RW,	"osd2 uv pos"},
	{OSD2_REG_UV_MODE,		0x08,	0x00000001,
			0,	RW,	"osd2 uv mode"},
	{OSD2_REG_Y_R,			0x0c,	0x000003ff,
			0,	RW,	"osd2 y r coefficient"},
	{OSD2_REG_Y_G,			0x10,	0x000003ff,
			0,	RW,	"osd2 y g coefficient"},
	{OSD2_REG_Y_B,			0x14,	0x000003ff,
			0,	RW,	"osd2 y b coefficient"},
	{OSD2_REG_U_R,			0x18,	0x000003ff,
			0,	RW,	"osd2 u r coefficient"},
	{OSD2_REG_U_G,			0x1c,	0x000003ff,
			0,	RW,	"osd2 u g coefficient"},
	{OSD2_REG_U_B,			0x20,	0x000003ff,
			0,	RW,	"osd2 u b coefficient"},
	{OSD2_REG_V_R,			0x24,	0x000003ff,
			0,	RW,	"osd2 v r coefficient"},
	{OSD2_REG_V_G,			0x28,	0x000003ff,
			0,	RW,	"osd2 v g coefficient"},
	{OSD2_REG_V_B,			0x2c,	0x000003ff,
			0,	RW,	"osd2 v b coefficient"},
	{OSD2_REG_YUV_SLICE_WIDTH,	0x30,	0x00000fff,
			0,	RW,	"osd2 yuv slice width"},
	{OSD2_REG_ARGB8888_SLICE_WIDTH,	0x34,	0x00000fff,
			0,	RW,	"osd2 argb8888 slice width"},
	{OSD2_REG_PAINTER_CS,		0x38,	0x0000000e,
			1,	RW,	"osd2 painter cs"},
	{OSD2_REG_PAINTER_IDLE,		0x38,	0x00000001,
			0,	RW,	"osd2 painter idle"},
	{OSD2_REG_BUF_OVERFL,		0x40,	0x00000080,
			7,	RW,	"osd2 buf overfl int flag"},
	{OSD2_REG_COLOR_UP_DONE,	0x40,	0x00000040,
			6,	RW,	"osd2 color up done int flag"},
	{OSD2_REG_BLOCK_DONE,		0x40,	0x00000020,
			5,	RW,	"osd2 block done int flag"},
	{OSD2_REG_BUSRD_MISMATCH,	0x40,	0x00000010,
			4,	RW,	"osd2 busrd mismatch int flag"},
	{OSD2_REG_CMD_ERROR,		0x40,	0x00000008,
			3,	RW,	"osd2 cmd error"},
	{OSD2_REG_VALID_ERROR,		0x40,	0x00000004,
			2,	RW,	"osd2 valid error"},
	{OSD2_REG_CMD_DONE,		0x40,	0x00000002,
			1,	RW,	"osd2 cmd done"},
	{OSD2_REG_PAINTER_DONE,		0x40,	0x00000001,
			0,	RW,	"osd2 painter done"},
	{OSD2_REG_BUSRD_CNT,		0x44,	0x00001f00,
			8,	RW,	"osd2 busrd count"},
	{OSD2_REG_BUSRD_LENG,		0x44,	0x0000001f,
			0,	RW,	"osd2 busrd length"},
	{OSD2_REG_COLORMAP_CS,		0x48,	0xe0000000,
			29,	RW,	"osd2 colormap cs"},
	{OSD2_REG_LAYER_CS,		0x48,	0x1f000000,
			24,	RW,	"osd2 layer cs"},
	{OSD2_REG_BUSWR_CS,		0x48,	0x00700000,
			20,	RW,	"osd2 bus write cs"},
	{OSD2_REG_BUSRD_CS,		0x48,	0x00070000,
			16,	RW,	"osd2 bus read cs"},
	{OSD2_REG_BLOCK_CS,		0x48,	0x00007000,
			12,	RW,	"osd2 block read cs"},
	{OSD2_REG_UVBUFF_CS,		0x48,	0x00000f00,
			8,	RW,	"osd2 uv read write buffer cs"},
	{OSD2_REG_YEBUFF_CS,		0x48,	0x000000f0,
			4,	RW,	"osd2 ye read write buffer cs"},
	{OSD2_REG_YOBUFF_CS,		0x48,	0x0000000f,
			0,	RW,	"osd2 yo read write buffer cs"},
	{OSD2_REG_PAINTER_CPU_MODE,	0x50,	0x00000001,
			0,	RW,	"osd2 painter cpu mode"},
	{OSD2_REG_PAINTER_COLOR_START,	0x54,	0x00000010,
			1,	RW,	"osd2 painter color start"},
	{OSD2_REG_PAINTER_BLOCK_START,	0x54,	0x00000001,
			0,	RW,	"osd2 painter block start"},
	{OSD2_REG_NOWAIT_BUFWR_EMPTY,	0x58,	0x00000001,
			0,	RW,	"osd2 nowait bufwr empty"},
	{OSD2_REG_BUF_ADDR_OSD,		0x5c,	0x0000003ff,
			0,	RW,	"osd2 buf addr osd"},
};

static const struct osd2_reg_field_t *__find_reg_field(enum osd2_reg_name name)
{
	int i = 0;
	int len = RTS_ARRAY_SIZE(asicRegisterDesc);

	for (i = 0; i < len; i++) {
		if (asicRegisterDesc[i].name == name)
			return &asicRegisterDesc[i];
	}

	return NULL;
}

void rts_osd2_set_register(const void *ewl, enum osd2_reg_name name,
		uint32_t value)
{
	uint32_t regval;
	const struct osd2_reg_field_t *field = __find_reg_field(name);

	if (!ewl) {
		printf("%s ewl NULL\n", __func__);
		return;
	}

	if (!field) {
		isp_error("Can't find register(%d).\n", name);
		return;
	}

	if (!(field->rw & WO)) {
		isp_error("register(%d) isn't writable.\n", name);
		return;
	}

	regval = osd2_ewl_read_reg(ewl, field->base) & ~(field->mask);
	osd2_ewl_write_reg(ewl, field->base,
			regval | ((value << field->lsb) & field->mask));
}

uint32_t rts_osd2_get_register(const void *ewl, enum osd2_reg_name name)
{
	uint32_t regval;
	const struct osd2_reg_field_t *field = __find_reg_field(name);

	if (!ewl) {
		printf("%s ewl NULL\n", __func__);
		return 0;
	} 

	if (!field) {
		isp_error("Can't find register(%d).\n", name);
		return 0;
	}

	if (!(field->rw & RO)) {
		isp_error("register(%d) isn't readable.\n", name);
		return 0;
	}

	regval = (osd2_ewl_read_reg(ewl, field->base) &
			field->mask) >> field->lsb;

	return regval;
}

