/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/src/rtsosd2cmd.c
 *
 * Copyright (C) 2016     Wil Shi<wil_shi@realsil.com.cn>
 */
#include <stdio.h>
#include <rtscamkit.h>
#include <rtscolor.h>
#include <osd2color.h>
//#include <assert.h>
#include <rtsc.h>
#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM // Run on KM4
#include <cmsis_voe.h>
#else
#include <cmsis.h>
#endif
#include "isp_log.h"
//#include "hal_cache.h"

struct osd2_color_field_t {
	int name;
	uint8_t type;
	uint8_t base;
	uint8_t	size;
};

static const struct osd2_color_field_t ColorTableDesc[] = {
	{RTS_PIX_FMT_1BPP,
			OSD2_COLOR_TYPE_RESERVED,	192,	2},
	{RTS_PIX_FMT_RGBA1111,
			OSD2_COLOR_TYPE_A,		190,	2},
	{RTS_PIX_FMT_RGBA1111,
			OSD2_COLOR_TYPE_R,		188,	2},
	{RTS_PIX_FMT_RGBA1111,
			OSD2_COLOR_TYPE_G,		186,	2},
	{RTS_PIX_FMT_RGBA1111,
			OSD2_COLOR_TYPE_B,		184,	2},
	{RTS_PIX_FMT_RGBA2222,
			OSD2_COLOR_TYPE_A,		180,	4},
	{RTS_PIX_FMT_RGBA2222,
			OSD2_COLOR_TYPE_R,		176,	4},
	{RTS_PIX_FMT_RGBA2222,
			OSD2_COLOR_TYPE_G,		172,	4},
	{RTS_PIX_FMT_RGBA2222,
			OSD2_COLOR_TYPE_B,		168,	4},
	{RTS_PIX_FMT_RGBA4444,
			OSD2_COLOR_TYPE_A,		152,	16},
	{RTS_PIX_FMT_RGBA4444,
			OSD2_COLOR_TYPE_R,		136,	16},
	{RTS_PIX_FMT_RGBA4444,
			OSD2_COLOR_TYPE_G,		120,	16},
	{RTS_PIX_FMT_RGBA4444,
			OSD2_COLOR_TYPE_B,		104,	16},
	{RTS_PIX_FMT_RGBA5551,
			OSD2_COLOR_TYPE_A,		96,	2},
	{RTS_PIX_FMT_RGBA5551,
			OSD2_COLOR_TYPE_R,		64,	32},
	{RTS_PIX_FMT_RGBA5551,
			OSD2_COLOR_TYPE_G,		32,	32},
	{RTS_PIX_FMT_RGBA5551,
			OSD2_COLOR_TYPE_B,		0,	32},
};



static const struct osd2_color_field_t *__find_color_field(
			int name, int type)
{
	int i = 0;
	int len = RTS_ARRAY_SIZE(ColorTableDesc);

	for (i = 0; i < len; i++) {
		if (ColorTableDesc[i].name == name &&
				ColorTableDesc[i].type == type)
			return &ColorTableDesc[i];
	}

	return NULL;
}

int osd2_dump_color_table(struct rtsc_dma_buffer *buffer)
{
	int i;
	int j;
	int c;
	uint8_t *addr;
	const struct osd2_color_field_t *field;

	addr = (uint8_t *)buffer->vm_addr;
	for (j = RTS_PIX_FMT_RGBA4444; j >= RTS_PIX_FMT_RGBA1111; j--) {
		for (i = (OSD2_COLOR_TYPE_RESERVED - 1); i >= 0; i--) {
			field = __find_color_field(j, i);
			if (!field) {
				isp_error("osd2_dump_color_table err field==NULL\n\r");
				return RTS_RETURN(RTS_E_NULL_POINT);
			}
			for (c = 0; c < field->size; c++)
				isp_info("%d %d %d: %02x\n",
					j, i, c, *(addr + field->base + c));
		}
	}
	return RTS_OK;

}

int osd2_set_default_color_table(struct rtsc_dma_buffer *buffer)
{
	int i;
	int j = 0;
	int c;
	uint8_t *addr = (uint8_t *)buffer->vm_addr;
	const struct osd2_color_field_t *field;

	if (!addr) {
		isp_error("osd2_set_default_color_table err addr==NULL\n\r");
		return RTS_OK;
	}

	for (j = RTS_PIX_FMT_RGBA4444; j >= RTS_PIX_FMT_RGBA1111; j--) {
		for (i = (OSD2_COLOR_TYPE_RESERVED - 1); i >= 0; i--) {
			field = __find_color_field(j, i);
			if (!field) {
				isp_error("osd2_set_default_color_table err field==NULL\n\r");
				return RTS_RETURN(RTS_E_NULL_POINT);
			}
			for (c = 0; c < field->size; c++)
				*(addr + field->base + c) =
					c * (0xff / (field->size - 1));
		}
	}
	/*special set for PURE COLOR MODE*/
	*(addr + 192) = 0;
	*(addr + 193) = 0xff;
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr, buffer->length);

	//printf("def color 0x%08x 0x%08x \n", addr + 192, *(uint32_t *)(addr + 192));
	return RTS_OK;
}

int osd2_set_color_table(struct rtsc_dma_buffer *buffer,
		int fmt, uint32_t val,
		uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	int i;
	uint8_t value[4];
	uint8_t *addr;
	uint8_t len[4] = {alpha, red, green, blue};
	const struct osd2_color_field_t *field;

	if (!buffer || !buffer->vm_addr) {
		isp_error("osd2_set_color_table err buffer=%x, buffer->vm_addr: %x\n\r", buffer, buffer->vm_addr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	addr = (uint8_t *)buffer->vm_addr;
	if (fmt == RTS_PIX_FMT_1BPP) {
		field = __find_color_field(fmt, OSD2_COLOR_TYPE_RESERVED);
		if (!field) {
			isp_error("osd2_set_color_table err field==NULL\n\r");
			return RTS_RETURN(RTS_E_NULL_POINT);
		}
		if (alpha > field->size) {
			isp_error("osd2_set_color_table err alpha=%d, field->size: %d\n\r", alpha, field->size);
			return RTS_RETURN(RTS_E_INVALID_LENGTH);
		}
		value[0] = (uint8_t)(val & 0xff);
		*(addr + field->base + alpha) = value[0];
		return RTS_OK;
	}

	value[0] = (uint8_t)(val & 0xff);
	value[1] = (uint8_t)((val >> 24) & 0xff);
	value[2] = (uint8_t)((val >> 16) & 0xff);
	value[3] = (uint8_t)((val >> 8) & 0xff);

	for (i = 0; i < OSD2_COLOR_TYPE_RESERVED; i++) {
		field = __find_color_field(fmt, i);
		if (!field) {
			printf("Can't find color(%d).\n", fmt);
			return RTS_RETURN(RTS_E_NULL_POINT);
		}
		if (len[i] > field->size) {
			printf("invalid rgba index\n");
			return RTS_RETURN(RTS_E_INVALID_ARG);
		}
		*(addr + field->base + len[i]) = value[i];
	}
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr, buffer->length);
	return RTS_OK;
}

uint32_t osd2_get_color_table(struct rtsc_dma_buffer *buffer,
		int fmt, uint8_t red, uint8_t green,
		uint8_t blue, uint8_t alpha)
{
	int i;
	uint8_t value[4] = {0, 0, 0, 0};
	uint32_t val;
	uint8_t *addr;
	uint8_t len[4] = {alpha, red, green, blue};
	const struct osd2_color_field_t *field;

	if (!buffer || !buffer->vm_addr) {
		isp_error("osd2_get_color_table err buffer=%x, buffer->vm_addr: %x\n\r", buffer, buffer->vm_addr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	addr = (uint8_t *)buffer->vm_addr;
	if (fmt == RTS_PIX_FMT_1BPP) {
		field = __find_color_field(fmt, OSD2_COLOR_TYPE_RESERVED);
		if (!field) {
			isp_error("Can't find color(%d).\n", fmt);
			return 0;
		}
		value[0] = *(addr + field->base + 0);
		value[1] = *(addr + field->base + 1);
		goto exit;
	}

	for (i = 0; i < OSD2_COLOR_TYPE_RESERVED; i++) {
		field = __find_color_field(fmt, i);
		if (!field) {
			isp_error("Can't find color(%d).\n", fmt);
			return 0;
		}
		if (len[i] > field->size) {
			isp_error("invalid rgba index\n");
			return 0;
		}
		value[i] = *(addr + field->base + len[i]);
	}
exit:
	val = (uint32_t)((value[1] << 24)|
			(value[2] << 16) | (value[3] << 8) | value[0]);
	return val;
}

