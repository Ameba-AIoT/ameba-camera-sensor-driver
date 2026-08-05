/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/rtsosd2.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cmsis_os2.h"
#include <errno.h>
#include "rt_config.h"
#include <rtscamkit.h>
#include <rtscolor.h>
#include <rts_queue.h>
#include <rtsc.h>
#include "rtsosd2.h"
#include "rtsosd2_priv.h"
#include "osd2ewl.h"
#include "osd2register.h"
#include "osd2cmd.h"
#include "osd2color.h"
#include "rts_camera.h"
#include "rtsvideo.h"
#include "rtx_mutex.h"
#include "rts_camera_mem.h"
#include "hal_timer.h"
#include "isp_debug.h"
#include "isp_mem.h"
#include "rt_code.h"
//#include "hal_cache.h"


#define RTS_OSD2_CMD_SIZE		32
#define RTS_OSD2_INIT_BUF_NUM		4096
#define RTS_OSD2_MEM_ALIGN_SIZE		32

#define OSD2_WIDTH_MIN			16
#define OSD2_HEIGHT_MIN			16
#define OSD2_WIDTH_MAX			3840
#define OSD2_HEIGHT_MAX			2160
#define OSD2_SIZE_UNIT			2

#define OSD2_DFT_COLOR			0xff

#define OSD2_FLICK_FREQ_MAX		30

#define RTS_OSD2_BLK_FIXED_BUF_LEN	(80 * 1024)

enum {
	OSD2_CMDCODE_S_FRAME_INFO = 0,
	OSD2_CMDCODE_S_COLOE_TABLE = 1,
	OSD2_CMDCODE_S_BLOCK_INFO = 2
};

enum {
	OSD2_S_BLOCK_OVERLAY_MODE_MASK = 0,
	OSD2_S_BLOCK_OVERLAY_MODE_IMAGE = 1,
	OSD2_S_BLOCK_OVERLAY_MODE_ALPHA = 2
};

struct cmd_attribute {
	uint8_t valid:1,
		end:1,
		intrupt:1,
		link:1,
		nop:1;
};

struct rts_osd2_cmd {
	struct cmd_attribute attribute;
	struct rtsc_dma_buffer command;
};

struct rts_osd2_blk_info {
	int blkidx;
	struct rts_osd2_blk blk;
	struct rts_osd2_attr_t attr;
	struct rts_osd2_cmd blk_info;
	struct rtsc_dma_buffer pict;
	struct rts_osd2_special_cfg special;
	uint32_t flick_cnt;
	int enable;
};

struct rts_osd2_t {
	const void *ewl;

	struct rts_osd2_config config;
	struct rts_osd2_blk_info *blocks;

	struct rts_osd2_cmd frame_info;
	struct rts_osd2_cmd color_info;
	uint32_t color_table_addr;
	struct rtsc_dma_buffer color_buf;

	struct rtsc_dma_buffer dma_buf;
	int offset;

	osMutexId_t mutex;
	int flag_adma;
	int framesize_updated;
	int RSVD[1];
};

__attribute__((aligned(32))) int gbl_osd2_vm_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};
__attribute__((aligned(32))) int gbl_osd2_phy_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};

__attribute__((aligned(32))) int gbl_osd_block_vm_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};
__attribute__((aligned(32))) int gbl_osd_block_phy_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};

__attribute__((aligned(32))) int gbl_attr_block_vm_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};
__attribute__((aligned(32))) int gbl_attr_block_phy_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};

u32 gbl_osd2_block_num[CFG_OSD_SUPPORT_MAX_CHNS] = {0};

#define osd2enc_vm_to_noncache(vm)   vm //((uint32_t)(vm) | 0xA0000000)

#ifdef _OSD_DEBUG_LOG

struct osd_cmd_time_t {
	uint32_t frame;
	uint32_t color;
	uint32_t blk;
	uint32_t end;

};

#define ADDR_CNT 25
struct osd_cmd_time_t osd_update_addr_time[11] = {0};
uint32_t osd_update_addr_link[11][ADDR_CNT] = {0};
uint32_t osd_init_addr_link[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM][8] = {0};
int osd_update_link_blk_idx = 0;
int osd_update_link_lnk_idx = 0;
#endif

static int osd2_alloc_dma(struct rts_osd2_t *osd2,
		   struct rtsc_dma_buffer *buffer)
{
	if (!osd2 || !buffer) {
		isp_error("osd2_alloc_dma err osd2=%x, buffer=%x\n\r", osd2, buffer);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	//printf("%s 0x%08x 0x%08x 0x%08x 0x%08x \r\n", __func__, osd2->dma_buf.phy_addr, (uint32_t)osd2->dma_buf.vm_addr, osd2->offset, buffer->length);
	if (!osd2->dma_buf.vm_addr) {
		isp_error("osd2_alloc_dma err vm_addr=%x\n\r", osd2->dma_buf.vm_addr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (RTS_OSD2_INIT_BUF_NUM - osd2->offset < (int)buffer->length) {
		isp_error("osd2_alloc_dma err offset=%d, length=%d\n\r", osd2->offset, buffer->length);
		return RTS_RETURN(RTS_E_NO_MEMORY);
	}

	buffer->phy_addr = osd2->dma_buf.phy_addr + osd2->offset;
	buffer->vm_addr = (void*)(buffer->phy_addr /* | 0x80000000*/);  //osd2->dma_buf.vm_addr + osd2->offset;
	osd2->offset += RTS_ALIGN(buffer->length, RTS_OSD2_MEM_ALIGN_SIZE);
	//printf("%s 0x%08x 0x%08x 0x%08x \r\n", __func__, buffer->phy_addr, (uint32_t)buffer->vm_addr, buffer->length);

	return RTS_OK;
}

static int __check_osd2_config(struct rts_osd2_config *config)
{
	if (!config) {
		isp_error("__check_osd2_config config==NULL\n\r");
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (config->format != RTS_PIX_FMT_NV12) {
		isp_error("__check_osd2_config err format=%d\n\r", config->format);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (config->width < OSD2_WIDTH_MIN ||
	    config->width > OSD2_WIDTH_MAX) {
	    isp_error("__check_osd2_config size err width=%d\n\r", config->width);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (config->height < OSD2_HEIGHT_MIN ||
	    config->height > OSD2_HEIGHT_MAX) {
	    isp_error("__check_osd2_config size err height=%d\n\r", config->height);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (config->width % OSD2_SIZE_UNIT != 0 ||
	    config->height % OSD2_SIZE_UNIT != 0) {
	    isp_error("__check_osd2_config size not alignment width=%d, height=%d\n\r", config->width, config->height);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return RTS_OK;
}

static int __init_osd2_cmd(struct rts_osd2_t *osd2,
			   struct rts_osd2_cmd *pcmd)
{
	int ret;

	if (!osd2 || !pcmd) {
		isp_error("__init_osd2_cmd err osd=%x, pcmd=%x\n\r", osd2, pcmd);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	memset(&pcmd->command, 0, sizeof(pcmd->command));
	pcmd->command.length = RTS_OSD2_CMD_SIZE;
	ret = osd2_alloc_dma(osd2, &pcmd->command);
	if (ret)
		isp_error("alloc osd command fail, ret = %d\n", ret);

	return ret;
}

static uint32_t __get_pic_size(uint32_t width, uint32_t height,
			       int fmt)
{
	uint32_t length;

	switch (fmt) {
	case RTS_PIX_FMT_NV12:
		length = ((width * 3) * height) >> 1;
		break;
	case RTS_PIX_FMT_NV16:
		length = (width * 2) * height;
		break;
	case RTS_PIX_FMT_1BPP:
		length = (width * height + 7) >> 3;
		break;
	case RTS_PIX_FMT_RGBA1111:
		length = (width * height) >> 1;
		break;
	case RTS_PIX_FMT_RGBA2222:
		length = width * height;
		break;
	case RTS_PIX_FMT_RGBA5551:
	case RTS_PIX_FMT_RGBA4444:
		length = (width * 2) * height;
		break;
	case RTS_PIX_FMT_RGBA8888:
		length = (width * 4) * height;
		break;
	default:
		length = 0;
		break;
	}

	return length;
}

static int __dft_blk_attr(struct rts_osd2_attr_t *attr)
{
	RTS_ASSERT(attr);

	attr->flick_enable = 0;
	attr->show_num = 1;
	attr->hide_num = 0;

	return RTS_OK;
}

static int __check_osd2_blk_attr(struct rts_osd2_attr_t *attr)
{

	if (!attr) {
		isp_error("__check_osd2_blk_attr err attr=%x\n\r", attr);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (attr->flick_enable) {
		if (attr->hide_num == 0 && attr->show_num == 0) {
			isp_error("__check_osd2_blk_attr err hide_num=%d, show_num=%d\n\r", attr->hide_num, attr->show_num);
			return RTS_RETURN(RTS_E_INVALID_ARG);
		}

		attr->flick_enable = RTS_TRUE;
	}

	return RTS_OK;
}

static int __check_osd2_blk(struct rts_osd2_t *osd2, struct rts_osd2_blk *blk)
{
	if (!osd2 || !blk) {
		isp_error("__check_osd2_blk err osd2=%x, blk=%x\n\r", osd2, blk);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (blk->area.start.x < 0) {
		isp_error("start.x(%d) < 0\n", blk->area.start.x);
		return ERR_ID_OSD_API_WRONG_AREA;
	}
	if (blk->area.start.x > blk->area.end.x) {
		isp_error("start.x(%d) > end.x(%d)\n", blk->area.start.x, blk->area.end.x);
		return ERR_ID_OSD_API_WRONG_AREA;
	}

	if ((blk->area.end.x - blk->area.start.x) % 2 ||
	    (blk->area.end.y - blk->area.start.y) % 2) {
		isp_error("width(%d) or height(%d) is odd number\n", (blk->area.end.x - blk->area.start.x), (blk->area.end.y - blk->area.start.y));
		return ERR_ID_OSD_API_COOR_ODD;
	}

	blk->area.start.x = blk->area.start.x & (~(OSD2_SIZE_UNIT - 1));
	blk->area.end.x = blk->area.end.x & (~(OSD2_SIZE_UNIT - 1));

	if (blk->area.start.y < 0) {
		isp_error("start.y(%d) < 0\n", blk->area.start.y);
		return ERR_ID_OSD_API_WRONG_AREA;
	}
	if (blk->area.start.y > blk->area.end.y) {
		isp_error("start.y(%d) > end.y(%d)\n", blk->area.start.y, blk->area.end.y);
		return ERR_ID_OSD_API_WRONG_AREA;
	}
	blk->area.start.y = blk->area.start.y & (~(OSD2_SIZE_UNIT - 1));
	blk->area.end.y = blk->area.end.y & (~(OSD2_SIZE_UNIT - 1));

	if (blk->area.start.x > (int)osd2->config.width ||
	    blk->area.end.x > (int)osd2->config.width) {
		isp_error("start.x(%d) or end.x(%d) out of frame range w: %d\n", blk->area.start.x, blk->area.end.x, osd2->config.width);
		return ERR_ID_OSD_API_WRONG_AREA;
	}

	if (blk->area.start.y > (int)osd2->config.height ||
	    blk->area.end.y > (int)osd2->config.height) {
		isp_error("start.y(%d) or end.y(%d) out of frame range h: %d\n", blk->area.start.y, blk->area.end.y, osd2->config.height);
		return ERR_ID_OSD_API_WRONG_AREA;
	}

	if ((blk->pixel_fmt < RTS_PIX_FMT_RGBA1111 ||
	     blk->pixel_fmt > RTS_PIX_FMT_RGBA8888) &&
	    blk->pixel_fmt != RTS_PIX_FMT_1BPP) {
		isp_error("pixel_fmt(%d) not support\n", blk->pixel_fmt);
		return ERR_ID_OSD_API_FMT_NOT_SUPPORT;
	}

	if (!blk->pure_color)
		blk->pure_color = OSD2_DFT_COLOR;

	return RTS_OK;
}

static void __release_blk_info(struct rts_osd2_blk_info *blk)
{
	if (!blk) {
		isp_error("__release_blk_info err blk=%x\n\r", blk);
		return;
	}

	free(blk->pict.vm_addr);
}

uint32_t __make_attribute(struct cmd_attribute attr)
{
	return (uint32_t)(attr.valid | (attr.end << 1) | (attr.intrupt << 2) |
			  (attr.link << 3) | (attr.nop << 4));
}

uint8_t __get_color_mode_val(int fmt)
{
	uint8_t val;

	switch (fmt) {
	case RTS_PIX_FMT_1BPP:
		val = 0;
		break;
	case RTS_PIX_FMT_RGBA1111:
		val = 1;
		break;
	case RTS_PIX_FMT_RGBA2222:
		val = 2;
		break;
	case RTS_PIX_FMT_RGBA5551:
		val = 3;
		break;
	case RTS_PIX_FMT_RGBA4444:
		val = 4;
		break;
	case RTS_PIX_FMT_RGBA8888:
		val = 5;
		break;
	default:
		val = -1;
		break;
	}
	return val;
}
#ifdef _OSD_DEBUG_LOG
extern int osd_debug_log_cnt;
#endif
int __write_each_blk_info_cmd(struct rts_osd2_blk_info *blk,
			      struct rts_osd2_blk_info *blk_next)
{
	uint8_t *addr_base;
	int32_t start_x;
	int32_t start_y;
	int32_t end_x;
	int32_t end_y;
	uint32_t width;
	uint32_t height;
	uint32_t data_addr;
	uint8_t color_mode;
	uint32_t pure_color;
	uint32_t link_addr;
	struct cmd_attribute attribute;
	struct rts_osd2_special_cfg special;

	if (!blk) {
		isp_error("__write_each_blk_info_cmd err blk=%x\n\r", blk);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (blk->enable != RTS_TRUE) {
		isp_error("__write_each_blk_info_cmd err blk->enable=%d\n\r", blk->enable);
		return RTS_RETURN(RTS_E_DISABLE);
	}

	if (!blk->blk_info.command.vm_addr) {
		isp_error("__write_each_blk_info_cmd err blk_info.command.vm_addr=%x\n\r", blk->blk_info.command.vm_addr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (!blk->pict.vm_addr) {
		isp_error("__write_each_blk_info_cmd err pict.vm_addr=%x\n\r", blk->pict.vm_addr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	addr_base = (uint8_t*)osd2enc_vm_to_noncache(blk->blk_info.command.vm_addr);
	start_x = blk->blk.area.start.x;
	start_y = blk->blk.area.start.y;
	end_x = blk->blk.area.end.x;
	end_y = blk->blk.area.end.y;
	width = abs(end_x - start_x);
	height = abs(end_y - start_y);
	data_addr = osd2enc_vm_to_noncache(blk->pict.phy_addr);
#ifdef _OSD_DEBUG_LOG
	if (osd_debug_log_cnt % 30 == 0)
		printf("osd buf addr: %x\n\r", data_addr);
#endif
	color_mode = __get_color_mode_val(blk->blk.pixel_fmt);
	pure_color = blk->blk.pure_color;
	special = blk->special;

	attribute = blk->blk_info.attribute;
	attribute.valid = 1;
	attribute.intrupt = 0;
	attribute.link = 1;
	attribute.nop = 0;
	if (!blk_next) {
		attribute.end = 1;
		attribute.link = 0;
	} else {
		attribute.end = 0;
	}

	memset(addr_base, 0, RTS_OSD2_CMD_SIZE);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_CMD_CODE, OSD2_CMDCODE_S_BLOCK_INFO);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_ATTRIBUTE, __make_attribute(attribute));
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_START_X, start_x);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_START_Y, start_y);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_WIDTH, width);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_HEIGHT, height);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_OVERLAY_MODE,
			 OSD2_S_BLOCK_OVERLAY_MODE_ALPHA);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_COLOR_MODE, color_mode);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_START_ADDR, data_addr);

	if (blk->blk.pixel_fmt == RTS_PIX_FMT_1BPP)
		rts_osd2_set_cmd(addr_base,
				 OSD2_PAINTER_BLK_PURE_COLOR_RGB, pure_color);

	if (blk_next) {
		link_addr = osd2enc_vm_to_noncache(blk_next->blk_info.command.phy_addr);
		rts_osd2_set_cmd(addr_base, OSD2_PAINTER_LINK_ADDR, link_addr);
		//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)link_addr, blk_next->blk_info.command.length);
	}

	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_UV_DISABLE,
			special.uv_disable);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_RGB2YUV_BYPASS,
			special.bypass);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_Y_INCR_ENABLE,
			special.y_incr_enable);
	if (special.y_incr_enable) {
		rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_Y_INCREASE,
				special.y_incr);
		rts_osd2_set_cmd(addr_base, OSD2_PAINTER_BLK_Y_INCR_THD,
				special.y_incr_thd);
	}



	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr_base, blk->blk_info.command.length);
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)data_addr, blk->pict.length);


#ifdef _OSD_DEBUG_LOG
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = (uint32_t)addr_base;
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = (uint32_t)*((uint32_t *)addr_base );
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = (uint32_t)*((uint32_t *)addr_base+7 );
#endif


	return RTS_OK;
}

static int __check_osd2_blk_and_famesize(
			struct rts_osd2_t *osd2, struct rts_osd2_blk *blk)
{
	if (!osd2 || !blk) {
		isp_error("__check_osd2_blk_and_famesize err osd2=%x, blk=%x\n\r", osd2, blk);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (blk->area.start.x > (int)osd2->config.width ||
	    blk->area.end.x > (int)osd2->config.width) {
	    isp_error("__check_osd2_blk_and_famesize err startx=%d, endx=%d, configw\n\r", blk->area.start.x, blk->area.end.x, osd2->config.width);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (blk->area.start.y > (int)osd2->config.height ||
	    blk->area.end.y > (int)osd2->config.height) {
	    isp_error("__check_osd2_blk_and_famesize err starty=%d, endy=%d, configy\n\r", blk->area.start.y, blk->area.end.y, osd2->config.height);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return RTS_OK;
}

int __write_enable_blk_info_cmd(struct rts_osd2_t *osd2, int chn_id)
{
	int i;
	int ret;
	struct rts_osd2_blk_info *blk = NULL;
	struct rts_osd2_blk_info *prev = NULL;
	int status = RTS_TRUE;
#ifdef _OSD_DEBUG_LOG
	uint8_t last_item = 0;
	static uint8_t pre_last_item = 0;
#endif

	for (i = 0; i < gbl_osd2_block_num[chn_id]; i++) {
		blk = &osd2->blocks[i];
		if (blk->enable != RTS_TRUE /*|| blk->pict.length == 0*/)
			continue;

		if (__check_osd2_blk_and_famesize(osd2, &blk->blk))
			continue;

		if (blk->attr.flick_enable) {
#ifdef _OSD_DEBUG_LOG
			if (osd_debug_log_cnt % 30 == 0)
				printf("flick_enable: %d, show_num: %d, hide_num: %d\n\r", blk->attr.flick_enable, blk->attr.show_num, blk->attr.hide_num);
#endif
			if (blk->flick_cnt < blk->attr.show_num)
				status = RTS_TRUE;
			else
				status = RTS_FALSE;

			blk->flick_cnt++;
			blk->flick_cnt %= (blk->attr.show_num +
					   blk->attr.hide_num);

			if (!status)
				continue;
		} else {
			blk->flick_cnt = 0;
		}

		if (!prev)
			goto out;
#ifdef _OSD_DEBUG_LOG
		if (osd_debug_log_cnt % 30 == 0) {
			printf("osd block %x: %x\n\r", last_item, prev->enable);
		}
#endif
		ret = __write_each_blk_info_cmd(prev, blk);
		if (ret != 0) {
			printf("write each blk info cmd fail %d \n", ret);
			return ret;
		}
out:
		prev = blk;
#ifdef _OSD_DEBUG_LOG
		last_item = i;
#endif
	}
	if (!prev) {
		if (status) {
			printf("all osd disable or NULL\n");
			return RTS_RETURN(RTS_E_NOT_FOUND);
		}
		else
			return RTS_OK;
	}
#ifdef _OSD_DEBUG_LOG
	if (osd_debug_log_cnt % 30 == 0) {
		printf("last osd block %x: %x\n\r", last_item, prev->enable);
	}
	if (pre_last_item != last_item)
		printf("pre_last_item: %x: last_item: %x\n\r", pre_last_item, last_item);
#endif
	ret = __write_each_blk_info_cmd(prev, NULL);

#ifdef _OSD_DEBUG_LOG
	pre_last_item = last_item;
#endif
	return ret;
}

int __write_frame_info_cmd(struct rts_osd2_t *osd2,
			   struct rts_osd2_encin *frame)
{
	uint8_t *addr_base = (uint8_t *)osd2enc_vm_to_noncache(osd2->frame_info.command.vm_addr);
	struct cmd_attribute attribute = osd2->frame_info.attribute;
	uint32_t width = osd2->config.width;
	uint32_t height = osd2->config.height;
	uint32_t bus_luma = osd2enc_vm_to_noncache(frame->bus_luma);
	uint32_t bus_chroma = osd2enc_vm_to_noncache(frame->bus_chroma);
	uint32_t color_phy_addr;

	attribute.valid = 1;
	attribute.intrupt = 0;
	attribute.link = 1;
	attribute.nop = 0;
	attribute.end = 0;

	color_phy_addr = osd2enc_vm_to_noncache(osd2->color_info.command.phy_addr);

	memset(addr_base, 0, RTS_OSD2_CMD_SIZE);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_CMD_CODE, OSD2_CMDCODE_S_FRAME_INFO);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_ATTRIBUTE, __make_attribute(attribute));
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_FRAME_WIDTH, width);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_FRAME_HEIGHT, height);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_FRAME_Y_ADDR, bus_luma);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_FRAME_UV_ADDR, bus_chroma);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_LINK_ADDR, color_phy_addr);

	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr_base, osd2->frame_info.command.length);
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)color_phy_addr, osd2->color_info.command.length);
#ifdef _OSD_DEBUG_LOG
	osd_update_addr_time[osd_update_link_blk_idx].frame = hal_read_curtime_us();
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = (uint32_t)addr_base;
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = *((uint32_t *)addr_base);
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = *((uint32_t *)addr_base+7);
#endif

	return RTS_OK;
}

int __write_color_table_info_cmd(struct rts_osd2_t *osd2, int chn_id)
{
	int count;
	int i;
	struct cmd_attribute attribute = osd2->frame_info.attribute;
	uint8_t *addr_base = (uint8_t *)osd2enc_vm_to_noncache(osd2->color_info.command.vm_addr);
	uint32_t blk_phy_addr;
	uint32_t color_table_addr = osd2enc_vm_to_noncache(osd2->color_table_addr);
	struct rts_osd2_blk_info *blk = NULL;

	attribute.valid = 1;
	attribute.intrupt = 0;
	attribute.link = 1;
	attribute.nop = 0;
	attribute.end = 0;

	count = gbl_osd2_block_num[chn_id];
	for (i = 0; i < count; i++) {
		blk = &osd2->blocks[i];
		if (blk->enable == RTS_TRUE)
			break;
	}

	if (i == count) {
		isp_error("__write_color_table_info_cmd all block disable\n\r");
		return RTS_RETURN(RTS_E_DISABLE);
	}

	blk_phy_addr = osd2enc_vm_to_noncache(blk->blk_info.command.phy_addr);

	memset(addr_base, 0, RTS_OSD2_CMD_SIZE);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_CMD_CODE, OSD2_CMDCODE_S_COLOE_TABLE);
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_ATTRIBUTE, __make_attribute(attribute));
	rts_osd2_set_cmd(addr_base,
			 OSD2_PAINTER_COLOR_TABLE_ADDR, color_table_addr);
	rts_osd2_set_cmd(addr_base, OSD2_PAINTER_LINK_ADDR, blk_phy_addr);



	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr_base, osd2->color_info.command.length);
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)blk_phy_addr, blk->blk_info.command.length);
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)color_table_addr, 194);

#ifdef _OSD_DEBUG_LOG
	osd_update_addr_time[osd_update_link_blk_idx].color = hal_read_curtime_us();
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = (uint32_t)addr_base;
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = *((uint32_t *)addr_base);
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = *((uint32_t *)addr_base+7 );
#endif

	return RTS_OK;
}

int __check_blk_valid_num(struct rts_osd2_t *osd2, int chn_id)
{
	int i;
	int num = 0;
	struct rts_osd2_blk_info *blk = NULL;

	for (i = 0; i < gbl_osd2_block_num[chn_id]; i++) {
		blk = &osd2->blocks[i];
		if (blk->enable == RTS_TRUE) {
			if (__check_osd2_blk_and_famesize(osd2, &blk->blk)) {
				if (osd2->framesize_updated)
					isp_error("check osd blk[%d] area and "
					"framesize fail,\n"
					"\tblk_start: [%d %d], "
					"blk_end: [%d %d], "
					"framesize: [%d %d]\n", i,
					blk->blk.area.start.x,
					blk->blk.area.start.y,
					blk->blk.area.end.x,
					blk->blk.area.end.y,
					osd2->config.width,
					osd2->config.height);
				continue;
			}
			num++;
		}
	}

	if (osd2->framesize_updated)
		osd2->framesize_updated = RTS_FALSE;

	return num;
}
#ifdef _OSD_DEBUG_LOG
struct osd2_init_log_info {
	uint32_t blk_addr[RTS_OSD2_BLK_MAX_NUMBER];
	uint32_t init_time;
};


#define OSD_INIT_LOG_CNT 5
struct osd2_init_log_info osd_init_log[OSD_INIT_LOG_CNT];
int record_init_osd_cnt = 0;

#endif

int __init_osd2_blocks(struct rts_osd2_t *osd2,
		       struct rts_osd2_blk_info *blocks, int chn_id)
{
	int i;
	int ret;
	struct rts_osd2_blk_info *blk;

	if (!blocks) {
		isp_error("__init_osd2_blocks err blocks=%x\n\r", blocks);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	blk = blocks;
#ifdef _OSD_DEBUG_LOG
	if ( record_init_osd_cnt < OSD_INIT_LOG_CNT ) {
		osd_init_log[record_init_osd_cnt].init_time = hal_read_curtime_us();
	}
#endif


	for (i = 0; i < gbl_osd2_block_num[chn_id]; i++) {
		blk[i].enable = RTS_FALSE;
#ifdef _OSD_DEBUG_LOG
		if ( record_init_osd_cnt < OSD_INIT_LOG_CNT ) {
			osd_init_log[record_init_osd_cnt].blk_addr[i] =(uint32_t) &blk[i];
		}
#endif

		blk[i].pict.vm_addr = NULL;
		__dft_blk_attr(&blk[i].attr);
		ret = __init_osd2_cmd(osd2, &blk[i].blk_info);
		if (ret < 0) {
			isp_error("__init_osd2_blocks __init_osd2_cmd ret=%d\n\r", ret);
			return ret;
		}
		blk[i].flick_cnt = 0;
		blk[i].blk.fixed_buf_len = RTS_OSD2_BLK_FIXED_BUF_LEN;
	}
#ifdef _OSD_DEBUG_LOG
	if ( record_init_osd_cnt < OSD_INIT_LOG_CNT ) {
		record_init_osd_cnt++;
	}
#endif

	return RTS_OK;
}

static int __init_osd2_pameters(struct rts_osd2_t *osd2, int chn_id)
{
	struct rts_osd2_blk_info *blk;
	int i;

	if (!osd2) {
		isp_error("__init_osd2_pameters err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	osd2->flag_adma = RTS_FALSE;
	osd2->framesize_updated = RTS_FALSE;
	osd2->frame_info.command.vm_addr = NULL;
	osd2->color_info.command.vm_addr = NULL;
	blk = osd2->blocks;
	for (i = 0; i < gbl_osd2_block_num[chn_id]; i++)
		blk[i].blk_info.command.vm_addr = NULL;

	return RTS_OK;
}

int __alloc_osd2_dma_buf(struct rts_osd2_t *osd2)
{
	if (!osd2) {
		isp_error("__alloc_osd2_dma_buf err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	memset(&osd2->dma_buf, 0, sizeof(osd2->dma_buf));
	osd2->dma_buf.length = RTS_OSD2_INIT_BUF_NUM;
	osd2->offset = 0;
	sprintf(osd2->dma_buf.name, "OSD2 Inner");

	osd2->dma_buf.vm_addr = rtscam_mem_alloc(osd2->dma_buf.length, (void **)&(osd2->dma_buf.phy_addr), 5);

	return RTS_OK;
}

extern int gbl_av_osdenc_attr_vm_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM];
extern int gbl_av_osdenc_attr_phy_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM];

int alloc_osd2_struct_buf(int chn_id)
{
	int i;
	struct rts_av_osdenc_attr *p_attr = NULL;
	struct rts_osd2_t *p_osd2 = NULL;
	
	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS) {
		isp_error("alloc_osd2_struct_buf invalid ch: %x\n\r", chn_id);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (gbl_osd2_block_num[chn_id] == 0) {
		return RTS_OK;
	}

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {

		if (gbl_av_osdenc_attr_vm_addr[chn_id][i] != 0 || gbl_osd2_vm_addr[chn_id][i] != 0) {
			isp_error("alloc_osd2_struct_buf memory already allocated ch: %x, buf_id: %x\n\r", chn_id, i);
			return RTS_RETURN(RTS_E_NULL_POINT);
		}

		gbl_av_osdenc_attr_vm_addr[chn_id][i] = (int)rtscam_mem_alloc(sizeof(struct rts_av_osdenc_attr), (void **)&gbl_av_osdenc_attr_phy_addr[chn_id][i], 5);
		if (gbl_av_osdenc_attr_vm_addr[chn_id][i] != 0 && gbl_av_osdenc_attr_phy_addr[chn_id][i] != 0)
			memset((void*)gbl_av_osdenc_attr_phy_addr[chn_id][i], 0, sizeof(struct rts_av_osdenc_attr));
		p_attr = (struct rts_av_osdenc_attr*)gbl_av_osdenc_attr_phy_addr[chn_id][i];

		gbl_attr_block_vm_addr[chn_id][i] = (int)rtscam_mem_alloc(sizeof(struct rts_video_osd2_block)*gbl_osd2_block_num[chn_id], (void **)&gbl_attr_block_phy_addr[chn_id][i], 5);
		p_attr->attr.blocks = (struct rts_video_osd2_block*)gbl_attr_block_phy_addr[chn_id][i];
		memset((void*)p_attr->attr.blocks, 0, sizeof(struct rts_video_osd2_block)*gbl_osd2_block_num[chn_id]);
		
		gbl_osd2_vm_addr[chn_id][i] = (int)rtscam_mem_alloc(sizeof(struct rts_osd2_t), (void **)&gbl_osd2_phy_addr[chn_id][i], 5);
		if (gbl_osd2_vm_addr[chn_id][i] != 0 && gbl_osd2_phy_addr[chn_id][i] != 0)
			memset((void*)gbl_osd2_phy_addr[chn_id][i], 0, sizeof(struct rts_osd2_t));
		p_osd2 = (struct rts_osd2_t*)gbl_osd2_phy_addr[chn_id][i];

		gbl_osd_block_vm_addr[chn_id][i] = (int)rtscam_mem_alloc(sizeof(struct rts_osd2_blk_info)*gbl_osd2_block_num[chn_id], (void **)&gbl_osd_block_phy_addr[chn_id][i], 5);
		p_osd2->blocks = (struct rts_osd2_blk_info*)gbl_osd_block_phy_addr[chn_id][i];
		memset((void*)p_osd2->blocks, 0, sizeof(struct rts_osd2_blk_info)*gbl_osd2_block_num[chn_id]);
	}

	return RTS_OK;
}

int free_osd2_attr_enc_buf(int chn_id)
{
	int i;
	struct rts_av_osdenc_attr *p_attr = NULL;
	struct rts_osd2_t *p_osd2 = NULL;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS) {
		isp_error("free_osd2_attr_enc_buf invalid ch: %x\n\r", chn_id);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (gbl_osd2_block_num[chn_id] == 0) {
		return RTS_OK;
	}

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {

		if (gbl_av_osdenc_attr_vm_addr[chn_id][i] == 0 || gbl_osd2_vm_addr[chn_id][i] == 0) {
			isp_error("free_osd2_attr_enc_buf memory already free ch: %x, buf_id: %x\n\r", chn_id, i);
			return RTS_RETURN(RTS_E_NULL_POINT);
		}
		if (gbl_av_osdenc_attr_vm_addr[chn_id][i] != 0) {
			
			free((void*)gbl_attr_block_vm_addr[chn_id][i]);

			free((void*)gbl_av_osdenc_attr_vm_addr[chn_id][i]);
			gbl_av_osdenc_attr_vm_addr[chn_id][i] = 0;
			gbl_av_osdenc_attr_phy_addr[chn_id][i] = 0;
		}

		if (gbl_osd2_vm_addr[chn_id][i] != 0) {

			free((void*)gbl_osd_block_vm_addr[chn_id][i]);

			free((void*)gbl_osd2_vm_addr[chn_id][i]);
			gbl_osd2_vm_addr[chn_id][i] = 0;
			gbl_osd2_phy_addr[chn_id][i] = 0;
		}
	}

	return RTS_OK;
}


void __free_osd2_dma_buf(struct rts_osd2_t *osd2)
{
	if (!osd2) {
		isp_error("__free_osd2_dma_buf err osd2=%x\n\r", osd2);
		return;
	}
	//printf("%s \r\n", __func__);
	//rtsc_free_dma(&osd2->dma_buf);
	free(osd2->dma_buf.vm_addr);
	osd2->dma_buf.length = 0;
	osd2->dma_buf.phy_addr = 0;

}

int __init_osd2_color_table(struct rts_osd2_t *osd2,
			    uint32_t *pdata)
{
	int ret;
	struct rtsc_dma_buffer *buffer = &osd2->color_buf;

	if (!osd2 || !pdata) {
		isp_error("__init_osd2_color_table err osd2=%x, pdata=%x\n\r", osd2, pdata);
		return;
	}

	memset(buffer, 0, sizeof(osd2->color_buf));
	buffer->length = OSD2_COLOR_TABLE_CHAR_NUM;

	ret = osd2_alloc_dma(osd2, buffer);
	if (ret) {
		isp_error("alloc color table dma failed");
		return RTS_RETURN(RTS_FAIL);
	}

	if (buffer->vm_addr)
		*pdata = buffer->phy_addr;

	osd2_set_default_color_table(&osd2->color_buf);
	return RTS_OK;
}

int rts_osd2_init(int chn_id, int buf_id, RtsOsd2Inst *posd,
		  struct rts_osd2_config *config)
{
	struct rts_osd2_t *osd2 = NULL;
	uint32_t color_table_addr;
	int ret;
#ifdef __OSD_LOG__
	printf("%s 0x%08x \r\n", __func__, posd);
#endif
	
	if (!posd || !config) {
		isp_error("rts_osd2_init err posd=%x, config=%x\n\r", posd, config);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	ret = __check_osd2_config(config);
	if (ret) {
		isp_error("invalid config\r\n");
		return ret;
	}

	osd2 = (struct rts_osd2_t *)gbl_osd2_phy_addr[chn_id][buf_id];
	if (!osd2)
		return RTS_RETURN(RTS_E_NO_MEMORY);
	if (osd2->ewl) {
		isp_error("already inited\n");
		return RTS_OK;	//already inited
	}

	osd2->ewl = osd2_ewl_init();
	if (!osd2->ewl) {
		isp_error("init ewl fail\r\n");
		//RTS_SAFE_DELETE(osd2);
		return RTS_RETURN(RTS_E_NOT_INITIALIZED);
	}

	ret = __init_osd2_pameters(osd2, chn_id);
	if (ret) {
		isp_error("init osd2 parameters fail\r\n");
		goto exit;
	}

	ret = __alloc_osd2_dma_buf(osd2);
	if (ret) {
		isp_error("alloc osd2 dma buf fail\r\n");
		goto exit;
	}

	ret = __init_osd2_color_table(osd2, &color_table_addr);
	if (ret < 0) {
		isp_error("init color table fail\r\n");
		goto exit;
	}
	osd2->color_table_addr = color_table_addr;

	ret = __init_osd2_cmd(osd2, &osd2->frame_info);
	if (ret) {
		isp_error("init frame info cmd fail\r\n");
		goto exit;
	}
#ifdef _OSD_DEBUG_LOG
	osd_init_addr_link[chn_id][buf_id][0] = osd2->frame_info.command.phy_addr;
#endif
	ret = __init_osd2_cmd(osd2, &osd2->color_info);
	if (ret) {
		isp_error("init color info cmd fail\r\n");
		goto exit;
	}

#ifdef _OSD_DEBUG_LOG
	osd_init_addr_link[chn_id][buf_id][1] = osd2->color_info.command.phy_addr;
#endif

	ret = __init_osd2_blocks(osd2, osd2->blocks, chn_id);
	if (ret) {
		isp_error("init block info cmd fail\r\n");
		goto exit;
	}

#ifdef _OSD_DEBUG_LOG
	osd_init_addr_link[chn_id][buf_id][2] = osd2->blocks[0].blk_info.command.phy_addr;
	osd_init_addr_link[chn_id][buf_id][3] = osd2->blocks[1].blk_info.command.phy_addr;
	osd_init_addr_link[chn_id][buf_id][4] = osd2->blocks[2].blk_info.command.phy_addr;
	osd_init_addr_link[chn_id][buf_id][5] = osd2->blocks[3].blk_info.command.phy_addr;
	osd_init_addr_link[chn_id][buf_id][6] = osd2->blocks[4].blk_info.command.phy_addr;
	osd_init_addr_link[chn_id][buf_id][7] = osd2->blocks[5].blk_info.command.phy_addr;
#endif

	memcpy(&osd2->config, config, sizeof(*config));

	*posd = osd2;
#ifdef __OSD_LOG__
	//printf("%s done 0x%08x 0x%08x\r\n", __func__, *posd, osd2->mutex);
#endif
	return RTS_OK;
exit:
	rts_osd2_release(osd2, chn_id);
	return ret;
}

int rts_osd2_release(RtsOsd2Inst posd, int chn_id)
{
	int i;
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk;
	//printf("%s \r\n", __func__);
	if (!osd2) {
		isp_error("rts_osd2_release err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	__free_osd2_dma_buf(osd2);

	return RTS_OK;
}

int rts_osd2_update(RtsOsd2Inst posd,
		  struct rts_osd2_config *config)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	//printf("%s \r\n", __func__);
	if (!osd2 || !config) {
		isp_error("rts_osd2_update err osd2=%x, config=%x\n\r", osd2, config);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (__check_osd2_config(config)) {
		isp_error("rts_osd2_update __check_osd2_config err\n\r");
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	memcpy(&osd2->config, config, sizeof(*config));

	osd2->framesize_updated = RTS_TRUE;
	return RTS_OK;
}

int rts_osd2_config_block(RtsOsd2Inst posd,
			  int blkidx, struct rts_osd2_blk *block, int chn_id)
{
	int ret;
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;
	//struct rtsc_dma_buffer blk_pict;
	uint32_t block_w;
	uint32_t block_h;
	uint32_t w_bytes;
	uint32_t w_bytes_align;
	uint32_t block_len_align;
	//int flag_align = 1;

	if (!osd2) {
		isp_error("rts_osd2_config_block err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}
	//printf("%s \r\n", __func__);
	if (blkidx < 0) {
		isp_error("osd2 block index(%d) cann't be minus\n", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}

	ret = __check_osd2_blk(osd2, block);
	if (ret) {
		isp_error("osd block config is invalid, ret = %d\n", ret);
		return ret;
	}

	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("rts_osd2_config_block blkidx invalid:%d\n", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];

	if (block->pdata == NULL) {
		if (!blk->pict.vm_addr)
			return RTS_OK;
		//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
		//osMutexWait(osd2->mutex, portMAX_DELAY);
		__release_blk_info(blk);
		memset(blk, 0, sizeof(struct rts_osd2_blk_info));
		blk->enable = RTS_FALSE;
		//osMutexRelease(osd2->mutex);

		return RTS_OK;
	}

	block_w = block->area.end.x - block->area.start.x;
	block_h = block->area.end.y - block->area.start.y;

	if (block->pixel_fmt == RTS_PIX_FMT_1BPP)
		w_bytes = (block_w + 7) / 8;
	else
		w_bytes = __get_pic_size(block_w, block_h, block->pixel_fmt) /
			  block_h;

	w_bytes_align = ((w_bytes + 7) / 8) * 8;
	block_len_align = w_bytes_align * block_h;

	if (__get_pic_size(block_w, block_h,
			   block->pixel_fmt) > block->length) {
		isp_error("get pic size block_w:%d, block_h: %d, pixel_fmt: %d, length: %d\n", block_w, block_h, block->pixel_fmt, block->length);
		return RTS_RETURN(RTS_E_INVALID_LENGTH);
	}

	blk->pict.vm_addr  = block->pdata;
	blk->pict.length   = block_len_align;
	blk->pict.phy_addr = (uint32_t)blk->pict.vm_addr;// & ~0xA0000000;
	blk->pict.buf_io   = RTSC_BUF_TO_DEVICE;

	/*sync for device*/
	//rtsc_mem_sync_device(blk->pict.phy_addr, block_len_align);

	memcpy(&blk->blk, block, sizeof(*block));
	//SCB_CleanInvalidateDCache_by_Addr((uint32_t *)&blk->blk, sizeof(*block));
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)blk->pict.phy_addr, block_len_align);
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)blk, sizeof(struct rts_osd2_blk_info));

	//osMutexRelease(osd2->mutex);

	return RTS_OK;
}

int rts_osd2_query_block(RtsOsd2Inst posd, int blkidx,
			 struct rts_osd2_blk *block, uint8_t *enable, int chn_id)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;

	if (!osd2) {
		isp_error("rts_osd2_query_block err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("osd2 block index(%d) out of range(max: %d)\n", blkidx, gbl_osd2_block_num[chn_id]);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];
	//printf("%s 0x%08x 0x%08x \r\n", __func__, osd2, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	memcpy(block, &blk->blk, sizeof(*block));
	//osMutexRelease(osd2->mutex);

	*enable = blk->enable;

	return RTS_OK;
}

#ifdef _OSD_DEBUG_LOG
struct osd2_update_log_info {
	uint32_t blk_id;
	uint32_t blk_addr;
	uint32_t update_time;
};


#define OSD_UPDATE_LOG_CNT 20
struct osd2_update_log_info osd_update_log[OSD_UPDATE_LOG_CNT];
int record_update_osd_cnt = 0;
#endif

int rts_osd2_enable_block(RtsOsd2Inst posd, int blkidx, int chn_id)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;
	int ret;

	if (!osd2) {
		isp_error("rts_osd2_enable_block err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("rts_osd2_enable_block blkidx err: %d\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];

	ret = __check_osd2_blk_and_famesize(osd2, &blk->blk);
	if (RTS_IS_ERR(ret)) {
		isp_error("check osd blk[%d] area and framesize fail,\n"
			"\tblk_start: [%d %d], blk_end: [%d %d], "
			"framesize: [%d %d]\n", blkidx,
			blk->blk.area.start.x, blk->blk.area.start.y,
			blk->blk.area.end.x, blk->blk.area.end.y,
			osd2->config.width, osd2->config.height);
		return ret;
	}
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	blk->enable = RTS_TRUE;
	//osMutexRelease(osd2->mutex);

#ifdef _OSD_DEBUG_LOG
	if ( record_update_osd_cnt < OSD_UPDATE_LOG_CNT ) {
		osd_update_log[record_update_osd_cnt].blk_id = blkidx;
		osd_update_log[record_update_osd_cnt].update_time = hal_read_curtime_us();
		osd_update_log[record_update_osd_cnt].blk_addr = (uint32_t)blk;
		record_update_osd_cnt++;
	}
#if 0
	if (record_update_osd_cnt == OSD_UPDATE_LOG_CNT ) {
		for (int j = 0; j < OSD_UPDATE_LOG_CNT; j++) {
			printf("%d update blk %d time %d addr 0x%08x \r\n", j, osd_update_log[j].blk_id, osd_update_log[j].update_time, osd_update_log[j].blk_addr);
		}
		record_update_osd_cnt++;

		for (int j = 0; j < record_init_osd_cnt; j++) {
			printf("%d init time %d addr 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\r\n", j, osd_init_log[j].init_time,
					osd_init_log[j].blk_addr[0], osd_init_log[j].blk_addr[1],osd_init_log[j].blk_addr[2],
					osd_init_log[j].blk_addr[3], osd_init_log[j].blk_addr[4],osd_init_log[j].blk_addr[5]
					);
		}


	}
#endif
#endif

	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)posd, sizeof(struct rts_osd2_t));

	return RTS_OK;
}

int rts_osd2_disable_block(RtsOsd2Inst posd, int blkidx, int chn_id)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;
	//printf("%s \r\n", __func__);
	//RTS_ASSERT(osd2);
	if (!osd2) {
		isp_error("rts_osd2_disable_block err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}
	
	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("rts_osd2_disable_block blkidx err: %d\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	blk->enable = RTS_FALSE;
	//osMutexRelease(osd2->mutex);

	return RTS_OK;
}

int rts_osd2_set_attr(RtsOsd2Inst posd,
		      int blkidx, struct rts_osd2_attr_t *attr, int chn_id)
{
	int ret;
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;

	if (!osd2 || !attr) {
		isp_error("rts_osd2_set_attr err osd2=%x, attr=%x\n\r", osd2, attr);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	ret = __check_osd2_blk_attr(attr);
	if (ret) {
		isp_error("invalid osd block attr, ret = %d\n", ret);
		return ret;
	}

	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("rts_osd2_set_attr blkidx err: %d\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	memcpy(&blk->attr, attr, sizeof(*attr));
	//osMutexRelease(osd2->mutex);

	return RTS_OK;
}

int rts_osd2_get_attr(RtsOsd2Inst posd,
		      int blkidx, struct rts_osd2_attr_t *attr, int chn_id)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;
	struct rts_osd2_blk_info *blk = NULL;

	
	if (!osd2 || !attr) {
		isp_error("rts_osd2_get_attr err osd2=%x, attr=%x\n\r", osd2, attr);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (blkidx < 0 || blkidx >= gbl_osd2_block_num[chn_id]) {
		isp_error("rts_osd2_get_attr blkidx err: %d\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}
	blk = &osd2->blocks[blkidx];
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	memcpy(attr, &blk->attr, sizeof(*attr));
	//osMutexRelease(osd2->mutex);

	return RTS_OK;
}

int __dump_color_table_reg(const void *ewl)
{
	uint32_t regval;
	int count = 200 / 4;
	int i;

	for (i = 0; i <= count; i++) {
		regval = osd2_ewl_read_reg(ewl, 0x100 + i * 4);
		printf("reg:[%04x]: %08x\n\r", i * 4,  (unsigned int)regval);
	}

	return RTS_OK;
}

int osd2_encode_frame(struct rts_osd2_t *osd2, int chn_id)
{
	int ret = RTS_OK;


	if (!osd2) {
		isp_error("osd2_encode_frame err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}
#ifdef __OSD_LOG__
	printf("%s \r\n", __func__);
#endif

	ret = __write_enable_blk_info_cmd(osd2, chn_id);
	if (ret != 0) {
		printf("write enable blk info cmd fail %d \n\r", ret);
		return ret;
	}
#ifdef _OSD_DEBUG_LOG
	osd_update_addr_time[osd_update_link_blk_idx].blk = hal_read_curtime_us();
#endif
	rts_osd2_set_register(osd2->ewl, OSD2_REG_CMD_ADDR,
			      osd2->frame_info.command.phy_addr);
#ifdef _OSD_DEBUG_LOG
	osd_update_addr_link[osd_update_link_blk_idx][osd_update_link_lnk_idx++] = osd2->frame_info.command.phy_addr;
#endif
	osd2_ewl_start_hw(osd2->ewl);

	ret = osd2_ewl_wait_hw_ready(osd2->ewl);
#ifdef _OSD_DEBUG_LOG
	osd_update_addr_time[osd_update_link_blk_idx].end = hal_read_curtime_us();
#endif
	if (ret)
		printf("osd2 encode frame fail, ret = %d\n\r", ret);

	return ret;
}
#ifdef _OSD_DEBUG_LOG

struct osd2_log_info {
	uint32_t buf_id;
	uint32_t enable[RTS_OSD2_BLK_MAX_NUMBER];
	uint32_t blk_addr[RTS_OSD2_BLK_MAX_NUMBER];
	uint32_t time;

};


#define OSD_LOG_CNT 20
extern struct osd2_log_info osd_log[OSD_LOG_CNT];
extern int record_osd_cnt;

#endif

#ifdef _OSD_LOG_INT_

#define CMD_LOG_CNT 5
#define ENCODE_LOG_CNT 11

struct osd_irq_cnt_t {
	uint32_t cmd[CMD_LOG_CNT];
	uint32_t blk[CMD_LOG_CNT];
	uint32_t color[CMD_LOG_CNT];
	uint32_t done[CMD_LOG_CNT];
	uint32_t err[CMD_LOG_CNT];

};

extern struct osd_irq_cnt_t irq_cnt[ENCODE_LOG_CNT];

#endif

int rts_osd2_encode(RtsOsd2Inst posd, struct rts_osd2_encin *frame, int chn_id)
{
	int ret;
	struct rts_osd2_t *osd2;

	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)posd, sizeof(struct rts_osd2_t));
	osd2 = (struct rts_osd2_t *)posd;

#ifdef _OSD_DEBUG_LOG
	if ( record_osd_cnt < OSD_LOG_CNT ) {
		struct rts_osd2_blk_info *blk;
		for (int i = 0; i < gbl_osd2_block_num[chn_id]; i++) {
			blk = &osd2->blocks[i];
			osd_log[record_osd_cnt].enable[i] = blk->enable;
			osd_log[record_osd_cnt].blk_addr[i] = (uint32_t)blk;
		}
		record_osd_cnt++;
	}
#endif



	if (!osd2 || !frame) {
		printf("rts_osd2_encode err osd2=%x, frame=%x\n\r", osd2, frame);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (!frame->bus_luma || !frame->bus_chroma || !frame->pbuf) {
		isp_error("invalid frame for osd\n\r");
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	if (frame->buf_size < __get_pic_size(osd2->config.width,
					     osd2->config.height,
					     RTS_PIX_FMT_NV12)) {
		isp_error("invalid frame length for osd\n\r");
		return RTS_RETURN(RTS_E_INVALID_LENGTH);
	}

	ret = __check_blk_valid_num(osd2, chn_id);
	if (ret == 0) {
		printf("rts_osd2_encode blk valid num=%d\n\r", ret);
		goto exit;
	}

	ret = __write_frame_info_cmd(osd2, frame);
	if (ret < 0) {
		isp_error("write frame info fail\n\r");
		goto exit;
	}

	ret = __write_color_table_info_cmd(osd2, chn_id);
	if (ret) {
		isp_error("write color table fail\n\r");
		goto exit;
	}

	ret = osd2_ewl_reserve_hw(osd2->ewl);
	if (ret) {
		isp_error("chn_id: %d HW unavailable\n\r", chn_id);
		goto exit;
	}

	ret = osd2_encode_frame(osd2, chn_id);
	if (ret < 0)
		isp_error("osd encode frame fail\n\r");

	osd2_ewl_release_hw(osd2->ewl);

#ifdef _OSD_DEBUG_LOG

	if (osd_update_link_blk_idx == 9 ) {

		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 5; i++) {
			printf("0x%08x 0x%08x 0x%08x 0x%08x 0x%08x \r\n",
					osd_update_addr_link[j][i*5],osd_update_addr_link[j][i*5+1],osd_update_addr_link[j][i*5+2],osd_update_addr_link[j][i*5+3],osd_update_addr_link[j][i*5+4]);
			}
			printf("time frame %d color %d blk %d end %d \r\n",
					osd_update_addr_time[j].frame, osd_update_addr_time[j].color, osd_update_addr_time[j].blk,  osd_update_addr_time[j].end);


		}

		for (int j = 0; j < 2; j++) {
			printf("init %d 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\r\n",j,
					osd_init_addr_link[0][j][0],osd_init_addr_link[0][j][1],osd_init_addr_link[0][j][2],osd_init_addr_link[0][j][3],
					osd_init_addr_link[0][j][4],osd_init_addr_link[0][j][5],osd_init_addr_link[0][j][6],osd_init_addr_link[0][j][7]);
			printf("ch 2 init %d 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\r\n",j,
					osd_init_addr_link[1][j][0],osd_init_addr_link[1][j][1],osd_init_addr_link[1][j][2],osd_init_addr_link[1][j][3],
					osd_init_addr_link[1][j][4],osd_init_addr_link[1][j][5],osd_init_addr_link[1][j][6],osd_init_addr_link[1][j][7]);
		}

#ifdef _OSD_LOG_INT_
		for (int j = 0; j < ENCODE_LOG_CNT; j++) {
			printf("encode %d cmd %d %d %d blk %d %d %d color %d %d %d done %d %d err %d %d %d \r\n:", j,
					irq_cnt[j].cmd[0], irq_cnt[j].cmd[1], irq_cnt[j].cmd[2],
					irq_cnt[j].blk[0], irq_cnt[j].blk[1], irq_cnt[j].blk[2],
					irq_cnt[j].color[0], irq_cnt[j].color[1], irq_cnt[j].color[2],
					irq_cnt[j].done[0], irq_cnt[j].done[1],
					irq_cnt[j].err[0], irq_cnt[j].err[1], irq_cnt[j].err[2]
			);
		}
#endif

		osd_update_link_blk_idx++;


		for (int j = 0; j < OSD_UPDATE_LOG_CNT; j++) {
			printf("%d update blk %d time %d addr 0x%08x \r\n", j, osd_update_log[j].blk_id, osd_update_log[j].update_time, osd_update_log[j].blk_addr);
		}

		for (int j = 0; j < record_init_osd_cnt; j++) {
			printf("%d init time %d addr 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\r\n", j, osd_init_log[j].init_time,
					osd_init_log[j].blk_addr[0], osd_init_log[j].blk_addr[1],osd_init_log[j].blk_addr[2],
					osd_init_log[j].blk_addr[3], osd_init_log[j].blk_addr[4],osd_init_log[j].blk_addr[5]
					);
		}





	} else if (osd_update_link_blk_idx < 9 ) {
		osd_update_link_blk_idx++;
	}
	osd_update_link_lnk_idx = 0;

#endif

exit:

	return ret;
}

int rts_osd2_set_color_table(RtsOsd2Inst posd, int fmt, uint32_t val,
			     uint8_t red, uint8_t green, uint8_t blue,
			     uint8_t alpha)
{
	int ret;
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_set_color_table err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	ret = osd2_set_color_table(&osd2->color_buf,
				   fmt, val, red, green, blue, alpha);
	//osMutexRelease(osd2->mutex);

	return ret;
}

uint32_t rts_osd2_get_color_table(RtsOsd2Inst posd, int fmt,
				  uint8_t red, uint8_t green, uint8_t blue,
				  uint8_t alpha)
{
	int ret;
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_get_color_table err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	ret = osd2_get_color_table(&osd2->color_buf,
				   fmt, red, green, blue, alpha);
	//osMutexRelease(osd2->mutex);

	return ret;
}

int rts_osd2_get_blk_max_num(int chn_id)
{
	return gbl_osd2_block_num[chn_id];
}

void rts_osd2_set_adma_copy(RtsOsd2Inst posd, int enable)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_set_adma_copy err osd2=%x\n\r", osd2);
		return;
	}
	//printf("%s 0x%08x \r\n", __func__, osd2->mutex);
	//osMutexWait(osd2->mutex, portMAX_DELAY);
	if (enable)
		osd2->flag_adma = RTS_TRUE;
	else
		osd2->flag_adma = RTS_FALSE;
	//osMutexRelease(osd2->mutex);
}

int rts_osd2_get_adma_copy(RtsOsd2Inst posd)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_get_adma_copy err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2->flag_adma;
}

int rts_osd2_set_epoll_hook(RtsOsd2Inst posd, void *master,
			    int (*hook_func)(void *master, int fd))
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_set_epoll_hook err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_set_epoll_hook(osd2->ewl, master, hook_func);
}

int rts_osd2_check_done(RtsOsd2Inst posd)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_check_done err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_check_done(osd2->ewl);
}

int rts_osd2_make_rdy(RtsOsd2Inst posd)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_make_rdy err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_make_rdy(osd2->ewl);
}

int rts_osd2_use_sigio(RtsOsd2Inst posd, int sigio_need)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_use_sigio err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_use_sigio(osd2->ewl, sigio_need);
}

int rts_osd2_use_inter(RtsOsd2Inst posd, int inter_need)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_use_inter err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_use_inter(osd2->ewl, inter_need);
}
int rts_osd2_print(RtsOsd2Inst posd)
{
	struct rts_osd2_t *osd2 = (struct rts_osd2_t *)posd;

	if (!osd2) {
		isp_error("rts_osd2_print err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	return osd2_ewl_print(osd2->ewl);
}
