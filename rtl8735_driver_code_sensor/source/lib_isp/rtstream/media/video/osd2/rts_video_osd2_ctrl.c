/*
 * Realtek Semiconductor Corp.
 *
 * media/video/osd/rts_video_osd_ctrl.c
 *
 * Copyright (C) 2017      Wil Shi<wil_shi@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "cmsis_os2.h"
#include <rtscamkit.h>
#include "rtsavunit.h"
#include "rtsosd.h"
#include "rt_osd2_api.h"
#include "rtsvideo.h"
#include "rts_video_osd2_ctrl.h"
#include "rtsvideo_func.h"
#include "rt_config.h"
#include "isp_log.h"

__attribute__((aligned(32))) int gbl_av_osdenc_attr_vm_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};
__attribute__((aligned(32))) int gbl_av_osdenc_attr_phy_addr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM] = {0};

int rts_av_check_ready_buf_idx(int chn_id, rts_osd_buf_status status)
{
	int i;
	struct rts_av_osdenc_attr *p;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS)
		return 0;

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {
		if (gbl_av_osdenc_attr_phy_addr[chn_id][i] == 0) {
			//isp_error("rts_av_check_ready_buf_idx attr_phy_addr[%x][%x]==NULL!\n\r", chn_id, i);
			return 0;
		}

		p = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][i];
		if (!p->bActiveStatus && status == osd_buf_update)
			return i;
		else if (p->bActiveStatus && status == osd_buf_encode)
			return i;
	}
	return 0;
}

void rts_av_set_ready_buf_idx(int chn_id, int buf_id)
{
	int i;
	struct rts_av_osdenc_attr *p;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS)
		return;

	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {
		if (gbl_av_osdenc_attr_phy_addr[chn_id][i] == 0) {
			isp_error("rts_av_set_ready_buf_idx attr_phy_addr[%x][%x]==NULL!\n\r", chn_id, i);
			return;
		}
		p = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][i];

		p->bActiveStatus = 0;
	}

	p = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][buf_id];
	p->bActiveStatus = 1;

}
static int __get_osdenc_attr_single(struct rts_av_osdenc_attr *osd_attr,
				    int blkidx, int chn_id)
{
	int ret;
	struct rts_video_osd2_block *block;
	struct rts_osd2_blk blk;
	struct rts_osd2_attr_t attr;

	if (!osd_attr) {
		isp_error("__get_osdenc_attr_single error osd_attr==NULL!\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	block = osd_attr->attr.blocks + blkidx;

	ret = rts_osd2_query_block(osd_attr->posd, blkidx, &blk,
				   &block->enable, chn_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("__get_osdenc_attr_single rts_osd2_query_block error: %d\n\r", ret);
		return ret;
	}

	block->rect.left = blk.area.start.x;
	block->rect.right = blk.area.end.x;
	block->rect.top = blk.area.start.y;
	block->rect.bottom = blk.area.end.y;

	block->picture.pixel_fmt = (enum rts_osd2_blk_fmt)blk.pixel_fmt;
	block->picture.length = blk.length;
	block->picture.pure_color = blk.pure_color;
	block->picture.pdata = blk.pdata;

	ret = rts_osd2_get_attr(osd_attr->posd, blkidx, &attr, chn_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("__get_osdenc_attr_single rts_osd2_get_attr error: %d\n\r", ret);
		return ret;
	}

	block->flick.flick_enable = attr.flick_enable;

	//block->fixed_buf_len = blk.fixed_buf_len;

	return RTS_OK;
}

static int __set_osdenc_flick_single(struct rts_av_osdenc_attr *osd_attr,
				     int blkidx, int chn_id)
{
	struct rts_video_osd2_block *block;
	struct rts_osd2_attr_t attr;
	uint32_t denominator;
	uint32_t numerator;

	if (!osd_attr) {
		isp_error("__set_osdenc_flick_single osd_attr==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	block = osd_attr->attr.blocks + blkidx;

	denominator = osd_attr->fps.denominator;
	numerator = osd_attr->fps.numerator;

	attr.flick_enable = block->flick.flick_enable;
	attr.show_num = RTS_DIV_ROUND_UP(block->flick.show_time * denominator,
					 RTS_MSEC_PER_SEC * numerator);
	attr.hide_num = RTS_DIV_ROUND_UP(block->flick.hide_time * denominator,
					 RTS_MSEC_PER_SEC * numerator);

	return rts_osd2_set_attr(osd_attr->posd, blkidx, &attr, chn_id);
}

static int __set_osdenc_attr_single(struct rts_av_osdenc_attr *osd_attr,
				    int blkidx, int chn_id)
{
	int ret;
	struct rts_video_osd2_block *block;
	struct rts_osd2_blk blk;
	int len;

	if (!osd_attr) {
		isp_error("__set_osdenc_attr_single osd_attr==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	block = osd_attr->attr.blocks + blkidx;

	if (block->enable != RTS_TRUE) {
#ifdef _OSD_DEBUG_LOG
		printf("rts_osd2_disable_block\n\r");
#endif
		return rts_osd2_disable_block(osd_attr->posd, blkidx, chn_id);
	}

	blk.area.start.x = block->rect.left;
	blk.area.end.x = block->rect.right;
	blk.area.start.y = block->rect.top;
	blk.area.end.y = block->rect.bottom;

	blk.pixel_fmt = block->picture.pixel_fmt;
	blk.length = block->picture.length;
	blk.pure_color = block->picture.pure_color;
	blk.pdata = block->picture.pdata;
	//blk.fixed_buf_len = block->fixed_buf_len;

	ret = rts_osd2_config_block(osd_attr->posd, blkidx, &blk, chn_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("__set_osdenc_attr_single rts_osd2_config_block error: %d\n\r", ret);
		return ret;
	}

	ret = __set_osdenc_flick_single(osd_attr, blkidx, chn_id);
	if (RTS_IS_ERR(ret)) {
		isp_error("__set_osdenc_attr_single __set_osdenc_flick_single error: %d\n\r", ret);
		return ret;
	}

	if (blk.pdata)
		ret = rts_osd2_enable_block(osd_attr->posd, blkidx, chn_id);

	len = sizeof(struct rts_av_osdenc_attr);
	SCB_CleanInvalidateDCache_by_Addr((uint32_t *)osd_attr, len);

	return ret;
}

static int __init_osdenc_attr(int chn_id, int buf_id, struct rts_av_osdenc_attr *osd_attr)
{
	struct rts_video_osd2_attr *pattr;
	int cnt;
	int i;

	if (!osd_attr) {
		isp_error("__init_osdenc_attr osd_attr==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}
	pattr = &osd_attr->attr;

	cnt = rts_osd2_get_blk_max_num(chn_id);
	//RTS_CALLOC_ARRAY(pattr->blocks, cnt);
	//if (!pattr->blocks)
	//	return RTS_RETURN(RTS_E_NULL_POINT);

	for (i = 0; i < cnt; i++) {
		pattr->blocks[i].enable = RTS_FALSE;
		pattr->blocks[i].flick.flick_enable = RTS_FALSE;
		//pattr->blocks[i].fixed_buf_len = 0;
	}

	RTS_S_C_VAR(pattr->number, cnt, int);
	return RTS_OK;
}

struct rts_av_osdenc_attr *rts_av_to_osdenc_t(int chn_id, int buf_id)
{
	struct rts_av_osdenc_attr *osd_attr;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS || buf_id >= CFG_PING_PONG_MAX_BUF_NUM) {
		isp_error("rts_av_to_osdenc_t ch: %x, buf_id: %x\n\r", chn_id, buf_id);
		return NULL;
	}
	if (gbl_av_osdenc_attr_phy_addr[chn_id][buf_id] == 0) {
		isp_error("rts_av_to_osdenc_t attr_phy_addr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return NULL;
	}

	osd_attr = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][buf_id];

	return osd_attr;
}

struct rts_video_osd2_attr *rts_av_to_osdenc_attr(int chn_id, int buf_id)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);
	if (osd_attr == NULL) {
		isp_error("rts_av_to_osdenc_attr osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return NULL;
	}
	return &osd_attr->attr;
}

int rts_av_set_osdenc_attr_owner(int chn_id, int buf_id, RtsOsd2Inst posd)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);

	if (osd_attr == NULL) {
		isp_error("rts_av_set_osdenc_attr_owner osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	osd_attr->posd = posd;

	return RTS_OK;
}

void rts_av_set_osdenc_attr(int chn_id, int buf_id, RtsOsd2Inst posd)
{
	struct rts_av_osdenc_attr *osd_attr;
	//struct rts_av_obj *obj;
	int ret;

	//RTS_CALLOC_STRU(osd_attr);

	osd_attr = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][buf_id];
	if (!osd_attr) {
		isp_error("rts_av_set_osdenc_attr osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return;
	}

	//rts_av_obj_init(&osd_attr->obj, __osdenc_attr_release);
	//obj = rts_av_obj_get(&osd_attr->obj);
	osd_attr->chn_id = chn_id;

	osd_attr->priv = osd_attr;

	ret = __init_osdenc_attr(chn_id, buf_id, osd_attr);
	if (RTS_IS_ERR(ret)) {
		isp_error("rts_av_set_osdenc_attr __init_osdenc_attr error: %d\n\r", ret);
		goto error;
	}

	ret = rts_av_set_osdenc_attr_owner(chn_id, buf_id, posd);
	if (RTS_IS_ERR(ret)) {
		isp_error("rts_av_set_osdenc_attr rts_av_set_osdenc_attr_owner error: %d\n\r", ret);
		goto error;
	}

	//return obj;
	return;
error:
	//rts_av_obj_put(obj);
	return;
}

void rts_av_set_osdenc_fps(int chn_id, int buf_id,
			   uint32_t numerator, uint32_t denominator)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);
	if (osd_attr == NULL) {
		isp_error("rts_av_set_osdenc_fps osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return;
	}

	osd_attr->fps.numerator = numerator;
	osd_attr->fps.denominator = denominator;
}

int rts_av_update_osdenc_flick_info(int chn_id, int buf_id)
{
	struct rts_av_osdenc_attr *osd_attr;
	int ret;
	int i;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);
	if (osd_attr == NULL) {
		isp_error("rts_av_update_osdenc_flick_info osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	for (i = 0; i < osd_attr->attr.number; i++) {
		ret = __set_osdenc_flick_single(osd_attr, i, chn_id);
		if (RTS_IS_ERR(ret)) {
			isp_error("rts_av_update_osdenc_flick_info __set_osdenc_flick_single error: %d\n\r", ret);
			return ret;
		}
	}

	return RTS_OK;
}

int rts_av_get_osdenc_attr_single(int chn_id, int buf_id, int blkidx)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);
	if (osd_attr == NULL) {
		isp_error("rts_av_get_osdenc_attr_single osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (blkidx < 0 || blkidx >= osd_attr->attr.number) {
		isp_error("rts_av_get_osdenc_attr_single blkidx: %d out of range\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}

	return __get_osdenc_attr_single(osd_attr, blkidx, chn_id);
}

int rts_av_set_osdenc_attr_single(int chn_id, int buf_id, int blkidx)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = rts_av_to_osdenc_t(chn_id, buf_id);
	if (osd_attr == NULL) {
		isp_error("rts_av_set_osdenc_attr_single osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	if (blkidx < 0 || blkidx >= osd_attr->attr.number) {
		isp_error("rts_av_set_osdenc_attr_single blkidx: %d out of range\n\r", blkidx);
		return ERR_ID_OSD_API_BLOCK_IDX_INVALID;
	}

	return __set_osdenc_attr_single(osd_attr, blkidx, chn_id);
}

int rts_av_query_osd2(unsigned int chnno, int buf_id, struct rts_video_osd2_attr **attr)
{
	struct rts_av_cmd_t vcmd;

	if (!attr) {
		isp_error("rts_av_query_osd2 attr==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	vcmd.cmd_id = RTS_AV_CMD_QUERY_OSDENC_ATTR;
	vcmd.pdata = attr;

	//return rts_av_do_cmd(chnno, RTS_AV_ID_OSDENC, &vcmd);
	return rts_av_osdenc_exec_cmd(chnno, buf_id, &vcmd);
}

int rts_av_set_osd2_single(struct rts_video_osd2_attr *attr, int chn_id, int buf_id, int blkidx)
{
	return rts_av_set_osdenc_attr_single(chn_id, buf_id, blkidx);
}

int rts_av_get_osd2(struct rts_video_osd2_attr *attr, int chn_id, int buf_id)
{
	int i;
	int ret;

	if (!attr) {
		isp_error("rts_av_get_osd2 attr==NULL\n\r");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	for (i = 0; i < attr->number; i++) {
		ret = rts_av_get_osdenc_attr_single(chn_id, buf_id, i);
		if (RTS_IS_ERR(ret)) {
			isp_error("rts_av_get_osd2 rts_av_get_osdenc_attr_single error: %d\n\r", ret);
			return ret;
		}
	}
	return RTS_OK;
}

int rts_av_set_osd2_color_table(struct rts_video_osd2_attr *attr,
				int chn_id, int buf_id, int fmt, uint32_t val,
				uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][buf_id];
	if (osd_attr == NULL) {
		isp_error("rts_av_set_osdenc_attr_single osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	return rts_osd2_set_color_table(osd_attr->posd, fmt, val, r, g, b, a);
}

uint32_t rts_av_get_osd2_color_table(struct rts_video_osd2_attr *attr, int chn_id, int buf_id, int fmt,
				     uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	struct rts_av_osdenc_attr *osd_attr;

	osd_attr = (struct rts_av_osdenc_attr *)gbl_av_osdenc_attr_phy_addr[chn_id][buf_id];
	if (osd_attr == NULL) {
		isp_error("rts_av_set_osdenc_attr_single osd_attr[%x][%x] == NULL!\n\r", chn_id, buf_id);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	return rts_osd2_get_color_table(osd_attr->posd, fmt, r, g, b, a);
}