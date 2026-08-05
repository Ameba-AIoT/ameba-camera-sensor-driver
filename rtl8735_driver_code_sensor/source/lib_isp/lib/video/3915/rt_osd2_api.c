#include "cmsis_os2.h"
#include "rtsosd.h"
#include "rt_osd2_api.h"
#include "rt_log.h"
#include "rt_util.h"
#include "mpool.h"
#include "rts_video_osdenc.h"
#include "rtsavdef.h"
#include "rtscamkit.h"
#include <rtsc.h>
#include "isp_log.h"
#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM
#include "hal_cache.h"
#endif

#include "isp_debug.h"
//#ifndef DEVICE_ISP
//#error "OSD2 API need ISP driver"
//#endif

extern int rtscam_osd2_open(void);
extern int rtscam_osd2_close(void);
extern int rtscam_osd2_probe(void);
extern int rtscam_osd2_remove(void);

typedef struct
{
	BOOL is_probed;
	BOOL is_inited;
	struct rts_osd2_config cfg;
	BOOL chn_inited[CFG_OSD_SUPPORT_MAX_CHNS];
	struct rts_video_osd2_attr *osd2_attr[CFG_OSD_SUPPORT_MAX_CHNS][CFG_PING_PONG_MAX_BUF_NUM];
} osd2_data_st;

static osd2_data_st s_data = {0};
extern u32 gbl_osd2_block_num[CFG_OSD_SUPPORT_MAX_CHNS];

static int rt_osd2_probe(void)
{
	int ret;
	//printf("%s start\r\n", __func__);
	if (s_data.is_probed)
		return RT_OK;
	// prepare sw resource of osd2
	if ((ret = rtscam_osd2_probe()) == RT_OK)
	{
		s_data.is_probed = 1;
	}
	return ret;
}

static int rt_osd2_remove(void)
{
	int ret;

	if (!s_data.is_probed)
		return RT_OK;
	// destroy sw resource of osd2
	if ((ret = rtscam_osd2_remove()) == RT_OK)
	{
		s_data.is_probed = 0;
	}
	return ret;
}

BOOL rt_osd2_is_inited(void)
{
	return s_data.is_inited;
}

BOOL rt_osd2_chn_profile_is_inited(int chn_id)
{
	return s_data.chn_inited[chn_id];
}

int rt_osd2_init_chn_profile(int chn_id, enum RTS_AV_FMT fmt, uint32_t width, uint32_t height,
		uint32_t numerator, uint32_t denominator)
{
	rt_av_profile_st profile;
	int ret;
	int i;

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS) {
		//printf("ch %d not support OSD\n\r", chn_id);
		return RT_OK;
	}

	if (gbl_osd2_block_num[chn_id] == 0)
		return RT_OK;

	ret = alloc_osd2_struct_buf(chn_id);
	if (ret)
	{
		ret = ERR_ID_OSD_API_MALLOC_FAIL;
		printf("OSD alloc buf fail: %d\n\r", ret);
		return ret;
	}

	//printf("%s start\r\n", __func__);
	// init osd channel profile
	rts_av_osdenc_init(chn_id);  //set osdenc attr, no reverse
	profile.fmt					= fmt;
	profile.video.width			= width;
	profile.video.height		= height;
	profile.video.numerator		= numerator;
	profile.video.denominator	= denominator;

	// call to rts_osd2_init(), mpalloc & set osd2 enc attr, reverse of rts_av_osdenc_cleanup()
	for (i = 0; i < CFG_PING_PONG_MAX_BUF_NUM; i++) {
		ret = rts_av_osdenc_set_profile(chn_id, i, &profile);
		if (ret != RT_OK)
		{
			ret = ERR_ID_OSD_API_SET_PROFILE_FAIL;
			isp_error("rts_av_osdenc_set_profile() failed= %d\n", ret);
			return ret;
		}
	}
	s_data.chn_inited[chn_id] = TRUE;
#ifdef __OSD_LOG__
	printf("%s end %d \r\n", __func__, ret);
#endif
	return ret;
}

int rt_osd2_init(void)
{
	int ret = RT_OK;

	if (s_data.is_inited)
		return RT_OK;
	//
	if (RT_OK != rt_osd2_probe())
	{
		ret = ERR_ID_OSD_API_PROBE_FAIL;
		isp_error("rt_osd2_init rt_osd2_probe fail ret=%d\n\r", ret);
		goto error;
	}
	// check hw_ready
	if (!s_data.is_probed)
	{
		ret = ERR_ID_OSD_API_HW_NOT_INIT;
		isp_error("rt_osd2_init not inited ret=%d\n\r", ret);
		goto error;
	}
	// open encoder
	//if ((ret = rtscam_osd2_open()) != RT_OK)  //init osd2 hw clk, reverse of rtscam_osd2_close()
	//{
	//	rt_printf("{osd2} open encoder, %s\n", rt_code_str(ret));
	//	ret = RT_E_OPEN_FAIL;
	//	goto error;
	//}
	//
	s_data.is_inited = 1;
	return RT_OK;

error:
	return ret;
}

struct rt_osd2_en_rec osd2_en_rec[CFG_OSD_SUPPORT_MAX_CHNS][RTS_OSD2_BLK_MAX_NUMBER] = {0};

int rt_osd2_deinit(int ch, int voe_ch_cnt)
{
	int i, j;
	int ret = RT_OK;

	if (!s_data.is_inited)
	{
		ret = ERR_ID_OSD_API_ALREADY_DEINIT;
		isp_error("rt_osd2_init not inited ret=%d\n\r", ret);
		return ret;
	}

	if (ch < CFG_OSD_SUPPORT_MAX_CHNS) {
		rts_av_osdenc_cleanup(ch);

		ret = free_osd2_attr_enc_buf(ch);
		if (ret) {
			ret = ERR_ID_OSD_API_FREE_BUF_FAIL;
			isp_error("rt_osd2_init free mem fail ret=%d\n\r", ret);
			return ret;
		}
		for (j = 0; j < CFG_PING_PONG_MAX_BUF_NUM; j++) {
			s_data.osd2_attr[ch][j] = 0;
		}
		memset(&osd2_en_rec[ch], 0, sizeof(struct rt_osd2_en_rec) * RTS_OSD2_BLK_MAX_NUMBER);
		printf("ch: %d rt_osd2_deinit\n\r", ch);
	}

	if (voe_ch_cnt != 0)
		return RT_OK;

	s_data.is_inited = 0;

	rt_osd2_remove();
	printf("All channel rt_osd2_deinit\n\r", ch);

	return RT_OK;
}

// @width, @height:
// if @width or @height = 0 means "use current width & height to do encode".
// else it will set width & height before encode & restore back after encode.
//

u32 osd2_start_encode_flag = 0;
#ifdef _OSD_DEBUG_LOG
int osd_debug_log_cnt = 0;
#endif
int rt_osd2_encode(int chn_id, int buf_id, void *frm_dat, u32 frm_len)
{
	int ret = RT_OK;
#ifdef _OSD_DEBUG_LOG
	if (osd_debug_log_cnt == 29)
		osd_debug_log_cnt = 0;
#endif
	//printf("%s start\r\n", __func__);
	if (!s_data.is_inited) {
		ret = ERR_ID_OSD_API_HW_NOT_INIT;
		isp_error("rt_osd2_encode not inited ret=%d\n\r", ret);
		return ret;
	}

	if (chn_id >= CFG_OSD_SUPPORT_MAX_CHNS)
		return RT_OK;

	if (gbl_osd2_block_num[chn_id] == 0) {
		return RT_OK;
	}

	if (!rts_av_osdenc_check_enable(chn_id, buf_id)) {
		return ERR_ID_OSD_API_BLOCK_NOT_ENABLE;
	}
	// check 32-byte align addr
	if ((int)frm_dat & 0x1F)
	{
		isp_error("frame_addr (0x%08x), not 32-byte aligned\n", (unsigned int)frm_dat);
		return ERR_ID_OSD_API_FRAME_NOT_ALIGN;
	}
	osd2_start_encode_flag = buf_id<<4 | 1;

	if ((ret = rt_osd2_encode_buf(chn_id, buf_id, frm_dat, frm_len)) != RT_OK)
	{
		ret = ERR_ID_OSD_API_ENCODE_FAIL;
		isp_error("{osd2} encode, %s\r\n", rt_code_str(ret));
	}
#ifdef _OSD_DEBUG_LOG
	osd_debug_log_cnt++;
#endif
#ifdef __OSD_LOG__
	printf("%s ret %d\r\n", __func__, ret);
#endif
	osd2_start_encode_flag = buf_id<<4 | 0;

	return ret;
}

int rt_query_osd2_attr(int chn_id, int buf_id, struct rts_video_osd2_attr **attr)
{
	int ret = RT_OK;

	if (!attr) {
		isp_error("rt_query_osd2_attr err attr=%x\n\r", attr);
		return RT_E_NULL_POINT;
	}
	if (!check_chn_id(chn_id)) {
		isp_error("rt_query_osd2_attr invalid ch id: %d\n\r", chn_id);
		return ERR_ID_OSD_API_INVALID_CH;
	}
	// already query before
	if (s_data.osd2_attr[chn_id][buf_id])
	{
		*attr = s_data.osd2_attr[chn_id][buf_id];
		goto success;
	}
	// else, the first time query
	ret = rts_av_query_osd2(chn_id, buf_id, attr);
	if (ret == RT_OK)
	{
		// if success, remember it.
		s_data.osd2_attr[chn_id][buf_id] = *attr;
		goto success;
	}

	return ret;

success:
	//rt_printf("{osd} chn#%d osd2_attr num = %d\n", chn_id, (*attr)->number);
	return RT_OK;
}

static int __set_osd_attr(rt_osd2_info_st *osd2, int chn_id, int buf_id, int blk_idx, int enable)
{
	//int mode;
	struct rts_video_osd2_attr *attr;

	if (!osd2) {
		isp_error("__set_osd_attr err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	attr = osd2->attr;

	//mode = __get_mode_val(osd2->mode);
	//if (mode < 0) {
	//	RTS_ERR("block color mode is invalid\n");
	//	return mode;
	//}
#ifdef _OSD_DEBUG_LOG
	if (osd_debug_log_cnt % 30 == 0)
		printf("osd_attr len: %d, buf: %x\n\r", osd2->len, osd2->buf);
#endif
	attr->blocks[blk_idx].picture.length = osd2->len;
	attr->blocks[blk_idx].picture.pdata = osd2->buf;
	attr->blocks[blk_idx].picture.pixel_fmt = osd2->blk_fmt;
	attr->blocks[blk_idx].picture.pure_color = osd2->color_1bpp;

	attr->blocks[blk_idx].rect.left = osd2->start_x;
	attr->blocks[blk_idx].rect.top = osd2->start_y;
	attr->blocks[blk_idx].rect.right = osd2->end_x;
	attr->blocks[blk_idx].rect.bottom = osd2->end_y;

	attr->blocks[blk_idx].flick.flick_enable = osd2->flick_enable;
	if (!osd2->flick_enable) {
		osd2->show_time = 1;
		osd2->hide_time = 0;
	}
	attr->blocks[blk_idx].flick.show_time = osd2->show_time;
	attr->blocks[blk_idx].flick.hide_time = osd2->hide_time;

	attr->blocks[blk_idx].enable = enable;

	return rts_av_set_osd2_single(attr, chn_id, buf_id, blk_idx);
}

int rt_update_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id)
{
	int ret = RT_OK;

	if (!osd2) {
		isp_error("rt_update_osd2 err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	ret = __set_osd_attr(osd2, chn_id, buf_id, osd2->blk_idx, RTS_TRUE);

	return ret;
}

int rt_enable_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id)
{
	int ret;
#ifdef _OSD_DEBUG_LOG
	printf("rt_enable_osd2\n\r");
#endif
//asm("sdbbp");
	if (!osd2) {
		isp_error("rt_enable_osd2 err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	ret = __set_osd_attr(osd2, chn_id, buf_id, osd2->blk_idx, RTS_TRUE);

	return ret;
}

int rt_disable_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id)
{
	int ret;
#ifdef _OSD_DEBUG_LOG
	printf("rt_disable_osd2\n\r");
#endif
	if (!osd2) {
		isp_error("rt_disable_osd2 err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	ret = __set_osd_attr(osd2, chn_id, buf_id, osd2->blk_idx, RTS_FALSE);

	return ret;
}

int rt_set_color_table_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id, int fmt, uint32_t val,
				uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	struct rts_video_osd2_attr *attr;
	int ret;

	if (!osd2) {
		isp_error("rt_set_color_table_osd2 err osd2=%x\n\r", osd2);
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	attr = osd2->attr;

	ret = rts_av_set_osd2_color_table(attr, chn_id, buf_id, fmt, val, r, g, b, a);

	return ret;
}

