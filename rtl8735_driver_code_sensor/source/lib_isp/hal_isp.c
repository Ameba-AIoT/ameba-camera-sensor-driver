/*
 * hal_isp.c
 *
 *  Created on: 2021¦~3¤ë17¤é
 *      Author: martinhuang
 */



#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "platform_stdlib.h"
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#include "cmsis_os.h"
#endif

#include "hal_isp.h"
#include "isp_main.h"
#include "videodev2.h"
#include "rts_isp_errno.h"
#include "isp_mod_ae.h"
#include "isp_mod.h"
#include "rts_raw.h"
#include "isp_debug.h"
#include "rtsvideo.h"
#include "rtsavisp.h"

#include "isp_top.h"
#include "rtx_mutex.h"
#include <rts_isp_tuning.h>
#include "isp_hw_nlsc.h"

#include "rt_code.h"

#ifdef CONFIG_ISP_EN

int hal_isp_init(hal_isp_adapter_t *isp_adpt)
{
	int ret = 0;
	if (isp_adpt == NULL) {
		printf("%s hal_isp_adapter NULL\r\n",__func__);
		return -1;
	}
	if (!isp_adpt->isp_device_probe_done) {

		ret = init_main(isp_adpt);
		isp_adpt->isp_device_probe_done = 1;

		if (ret != 0)
			return ret;
	} else {
		if ( hal_isp_is_verify_path_on() )
			return ERR_ID_ISP_VERIFY_REOPEN_FAIL;

		printf ("isp_device_probe had done\r\n");
	}
#ifdef __OSD_EN__
	ret = rt_osd2_init();
	if (ret) {
		isp_error("rt_osd2_init failed %d \r\n", ret);
	}
#endif

	return ret;

}


void* isp_soc_start(hal_isp_adapter_t *isp_adpt, int *ret)
{
	__rts_isp_force_keep_helper_funcs();

	if (!isp_adpt) {
		printf("%s isp hal_isp_adapter NULL\r\n", __func__);
		return NULL;
	}

	if (!isp_adpt->isp_device_probe_done) {
        printf("hal_isp_init error\r\n");
        return NULL;
	}

#if 0 // remove cmsis_os
	osThreadId tid_isp;                             			// thread id

	tid_isp = osThreadCreate(osThread(isp_main_thread), isp_adpt);
    if (tid_isp == 0) {
        printf ("Create isp_main_thread task error\r\n");
        return NULL;
    }
#else


#if ISP_MAIN

#else
	xTaskHandle tid_isp;                             			// thread id
	tid_isp = 1;
	*ret = isp_main_thread((void *)isp_adpt);

#endif

#endif
    return tid_isp;
}

int isp_locate_buffer(hal_isp_adapter_t *isp_adpt, uint8_t stream_id)
{
	hal_isp_stream_t *steam_pt;
	int align_size = 256;
	int buffer_size;
#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif

	steam_pt = &(isp_adpt->video_stream[stream_id]);
	switch (steam_pt->fmt) {
	case NV12_FORMAT:
	case NV21_FORMAT:
		steam_pt->bits_pixel = 12;
		break;
	case NV16_FORMAT:
	case NV61_FORMAT:
		steam_pt->bits_pixel = 16;
		break;
	case RGB888_FORMAT:
		steam_pt->bits_pixel = 24;
		break;
//			case YONLY_FORMAT:
//				steam_pt->bits_pixel = 8;
//				break;
	default:
		printf(" %s stream %d fmt error %ld \r\n", __func__, stream_id, steam_pt->fmt);
		return -1;
	}
	for (int i=0; i<(int)isp_adpt->video_stream[stream_id].buff_num; i++) {


		buffer_size = steam_pt->user_width*steam_pt->user_height*steam_pt->bits_pixel/8+align_size;
#ifdef RTS_VIDEOIN_HEIGHT_ALIGN
		if (steam_pt->bits_pixel != RGB888_FORMAT && steam_pt->user_height % RTS_VIDEOIN_HEIGHT_ALIGN) {
			buffer_size += (RTS_VIDEOIN_HEIGHT_ALIGN - steam_pt->user_height % RTS_VIDEOIN_HEIGHT_ALIGN)* steam_pt->user_width;
			printf("%s HEIGHT_ALIGN issue %d %d \r\n", __func__, steam_pt->user_height, buffer_size);
		}
#endif

		steam_pt->bufs[i].org_buf_addr = (uint32_t)pvPortMalloc(buffer_size);
		if (steam_pt->bufs[i].org_buf_addr) {
			steam_pt->bufs[i].buf_addr = (steam_pt->bufs[i].org_buf_addr+align_size-1)&(0xFFFFFFFF^(align_size-1));
			printf("stream %d  buffer %x: 0x%08x size %d \r\n", stream_id, i, steam_pt->bufs[i].buf_addr, steam_pt->user_width*steam_pt->user_height*steam_pt->bits_pixel/8);

#if defined(_DEBUG_MEM_USEAGE_)
			printf(" %s stream %d  buffer 0x%08x size %d \r\n", __func__, stream_id, steam_pt->bufs[i].buf_addr, steam_pt->user_width*steam_pt->user_height*steam_pt->bits_pixel/8);

#endif


		} else {
			printf(" %s malloc buffer failed \r\n", __func__);
			return -1;
		}
	}
#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("isp_locate_buffer heap_used %d heap %d \n", heap_before-heap_after, heap_after);
#endif

	return 0;

}


int isp_free_buffer(hal_isp_adapter_t *isp_adpt, uint8_t stream_id)
{
	hal_isp_stream_t *steam_pt;
	steam_pt = &(isp_adpt->video_stream[stream_id]);

	for (int i=0; i<(int)isp_adpt->video_stream[stream_id].buff_num; i++) {
		if (steam_pt->bufs[i].org_buf_addr) {
			//printf(" %s stream %d  buffer 0x%08x free \r\n", __func__, stream_id, steam_pt->bufs[i].org_buf_addr);
			free((void *)steam_pt->bufs[i].org_buf_addr);
		} else {
			printf(" %s no buffer need to be free \r\n", __func__);
			return -1;
		}
	}

	return 0;

}
int check_isp_soc_start_done(hal_isp_adapter_t *isp_adpt)
{

	if ( !isp_adpt->isp_init_done ) {
		while (!check_isp_running()) {
			vTaskDelay(1);	// delay 10ms
		}
		isp_adpt->isp_init_done = TRUE;
		//printf("%s isp_init_done\r\n", __func__);
	}
	return 0;
}

static void isp_ae_fps_status(float curfps)
{
	printf("change fps to %f \r\n", curfps);
	return 0;
}

int isp_open_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id, uint32_t init_raw)
{
	if (init_raw)
		hal_isp_set_raw_fmt(stream_id, RTS_RAW_SRC_BLC_LONGEXP_B);
	rts_isp_register_ae_fps_change_cb(0, isp_ae_fps_status);
	return start_stream(isp_adpt, stream_id);
}

int isp_close_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id)
{
	isp_adpt->video_stream[stream_id].stream_running = FALSE;
	return stream_close(stream_id);
}

int isp_get_stream_cnt(uint8_t stream_id)
{
	return get_stream_cnt(stream_id);
}

uint32_t isp_get_frame_buffer(uint8_t stream_id)
{
	return get_latest_frame_buffer(stream_id);
}

int isp_release_frame_buffer(uint8_t stream_id, uint32_t buf_addr)
{
	return release_frame_buffer(stream_id, buf_addr);
}


int hal_isp_get_ctrl(uint32_t id, int *value)
{
	int ret;
	struct v4l2_control c;
	int final_id;
	if (!value)
		return -EINVAL;
	final_id = V4L2_CID_BASE+id;
	printf("isp_ctrl 0x%08x id %ld \r\n", final_id, id);
	c.id = final_id;
	ret = rts_isp_v4l2_g_ctrl(0, &c);
	if (ret) {
		isp_error("failed to get ctrl 0x%08lx ret 0x%08x", id, ret);
		return ret;
	}
	*value = c.value;

	return 0;
}


int hal_isp_set_ctrl(uint32_t id, int *value)
{
	int ret;
	struct v4l2_control c;
	int final_id;
	if (!value)
		return -EINVAL;
	final_id = V4L2_CID_BASE+id;
	//printf("isp_ctrl 0x%08x id %ld \r\n", final_id, id);
	c.id = final_id;
	c.value = *value;
	ret = rts_isp_v4l2_s_ctrl(0, &c);
	if (ret) {
		isp_error("failed to set ctrl 0x%08lx ret 0x%08x", id, ret);
		return ret;
	}
	*value = c.value;

	return 0;
}



#if 0

int hal_isp_query_ae_setting(struct rts_isp_ae_setting **ae_setting)
{
	int ret;
	struct rts_isp_ae_setting *setting;
	struct isp_mod_ae_stat_info info;
	uint32_t isp_id = 0;
	if (!ae_setting)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_AE, AE_INFO_STATIS,
				     &info, sizeof(info));
	if (ret)
		return ret;
	setting = alloc_ae_setting(&info);
	if (!setting)
		return -RTS_ISP_ENOMEM;
	ret = rts_isp_get_ae_setting(isp_id, setting);
	if (ret)
		goto err;
	*ae_setting = setting;
	return RTS_ISP_OK;
err:
	isp_perror(ret, "query ae setting fail");
	free_ae_setting(setting);
	return ret;
}
#endif
#if 0

int isp_lock_rgb_buf_and_replace(hal_isp_adapter_t *isp_adpt, uint32_t lock_buf, uint8_t hw_slot)
{

	hal_isp_stream_t *steam_pt;
	steam_pt = &(isp_adpt->video_stream[4]);
	uint32_t free_buf;
	int ret = 0;


	ret = rgb_lock_buffer(lock_buf, hw_slot);

	if (ret) {
		printf("rgb_lock_buffer error\r\n");
		return ret;
	}

	if (steam_pt->bufs[hw_slot].buf_addr != lock_buf ) {
		printf("lock buf 0x%08x differ from slot 0x%08x\r\n", lock_buf, steam_pt->bufs[hw_slot].buf_addr);
		return -1;
	}

	free_buf = steam_pt->bufs[steam_pt->buff_num-1].buf_addr;
	steam_pt->bufs[hw_slot].buf_addr = free_buf;
	steam_pt->bufs[steam_pt->buff_num-1].buf_addr = lock_buf;

	return ret;


}

int isp_rgb_release_buffer(void)
{
	return rgb_release_buffer();
}

#endif

int hal_isp_set_raw_fmt(uint8_t streamid, uint32_t fmt)
{
	return rts_hal_set_raw(streamid, fmt);
}

extern void md2_set_ctrl(struct rts_md2_ctrl *pctrl);
extern struct rts_md2_attr* md2_get_attr(void);
extern void isp_hw_global_set_drop_frame_num(uint32_t num);

int hal_isp_set_md2(struct rts_md2_ctrl **ctrl, struct rts_md2_attr *attr)
{
	int ret = 0;

	ret = rts_av_query_md2(ctrl, attr);
	if (ret) {
		printf("query md2 failed [%d]\n", ret);
		return ret;
	}

	md2_set_ctrl(*ctrl);
	ret = rts_av_set_md2(*ctrl);

	return ret;
}

int hal_isp_get_md2_result(struct rts_md2_ctrl *ctrl, struct rts_md2_result *res)
{
	int wret = 0;
	wret = rts_av_poll_md2(ctrl, ISP_SEM_TIMEOUT);
	if (wret == RTS_FALSE) {
		isp_error("poll md2 timeout\n");
		return wret;
	}

	wret = rts_av_get_md2_result(ctrl, res);
	return wret;
}

struct rts_md2_attr* hal_isp_get_md2_attr(void)
{
	return md2_get_attr();
}

void hal_isp_release_md2(struct rts_md2_ctrl *ctrl)
{
	rts_av_release_md2(ctrl);
}

void hal_isp_set_drop_frame_num(uint32_t num)
{
	isp_hw_global_set_drop_frame_num(num);
}

void hal_isp_set_drop_frame_num_sw(uint32_t num)
{
	isp_hw_global_set_drop_frame_num_sw(num);
}

void hal_isp_update_fcs_status(uint8_t fcs_status)
{
	isp_top_update_fcs_ready(fcs_status);
}

int hal_isp_set_sensor_mode(int mode, int fps) // mode 0: linear 1: hdr
{
	uint32_t isp_id = 0;
	int i;
	struct rts_isp_sensor_modes sensor_modes;
	rts_av_isp_enum_sensor_modes(isp_id, &sensor_modes);
	for (i = 0; i < sensor_modes.num; i++) {
		if (sensor_modes.mode[i].hdr == mode && floor(sensor_modes.mode[i].fps) == (double)fps)
			break;
	}
	if (i == sensor_modes.num) {
		printf("No compatible mode found\n");
		return -1;
	}
	return rts_av_isp_set_sensor_mode(isp_id, &sensor_modes.mode[i]);
}

int hal_isp_get_sensor_mode(int *mode, int *fps) // mode 0: linear 1: hdr
{
	uint32_t isp_id = 0;
	int ret;
	struct rts_isp_sensor_mode sensor_mode;
	memset(&sensor_mode, 0, sizeof(sensor_mode));

	ret = rts_av_isp_get_sensor_mode(isp_id, &sensor_mode);

	if (!ret) {
		*mode = sensor_mode.hdr;
		*fps = (int)sensor_mode.fps;
	}
	return ret;

}



int hal_isp_get_af_statis(af_statis_t *p_af_statis)
{
	int ret;
	struct rts_isp_af_stat_info stat_info;
	const struct rts_isp_af_statis *statis;
	//printf("get stat info \n");
	ret = rts_isp_get_af_statis_info(ISP0, &stat_info);
	if (ret) {
		printf("get af stat info fail %d \n", ret);
		return ret;
	}
	//printf("rts_isp_query_af_statis \n");
	ret = rts_isp_query_af_statis(ISP0, &statis);
	if (ret) {
		printf("query af statis fail %d \n", ret);
		return ret;
	}
	//printf("rts_isp_get_af_statis \n");
	ret = rts_isp_get_af_statis(ISP0, statis);
	if (ret) {
		printf("get af statis fail %d \n", ret);
		rts_isp_release_af_statis(ISP0, statis);
		return ret;
	}


	p_af_statis->win_cnt = stat_info.win.cols * stat_info.win.rows;
	p_af_statis->frame_count = statis->frame_count;
	p_af_statis->num0 = statis->num0;
	p_af_statis->sum0 = statis->sum0;
	p_af_statis->num1 = statis->num1;
	p_af_statis->sum1 = statis->sum1;
	p_af_statis->frame_count = statis->frame_count;

	//printf("fr %ld af0 %ld %ld af1 %ld %ld \n", p_af_statis->frame_count, p_af_statis->sum0, p_af_statis->num0, p_af_statis->sum1, p_af_statis->num1);
/*
	printf("rts_isp_put_af_statis \n");
	ret = rts_isp_put_af_statis(ISP0, statis);
	if (ret) {
		printf("put_af_statis fail %d \n", ret);
		rts_isp_release_af_statis(ISP0, statis);
		return ret;
	}
*/

	//printf("edges:\n");
	//for (i = 0; i < p_af_statis->win_cnt ; i++) {
	//	printf("%08x ", (unsigned int)statis->edges[i]);
	//	if ((i + 1) % 5 == 0)
	//		printf("\n");
	//}
	//printf("rts_isp_release_af_statis \n");
	rts_isp_release_af_statis(ISP0, statis);

	return 0;
}

int hal_isp_set_init_ae(int init_exposure, int init_gain)
{

	struct v4l2_control c_exp, c_gain, c_autoexp;
	int ret;

	c_exp.id = V4L2_CID_EXPOSURE;
	c_exp.value = init_exposure;

	c_gain.id = V4L2_CID_GAIN;
	c_gain.value = init_gain;

	c_autoexp.id = V4L2_CID_AUTOGAIN;
	c_autoexp.value = 0;

	ret = rts_isp_v4l2_s_ctrl(0, &c_autoexp);

	if (ret) {
		printf("%s disable AUTOGAIN failed ret = %d \n", __func__, ret);
		return ret;
	}

	ret = rts_isp_v4l2_s_ctrl(0, &c_exp);

	if (ret) {
		printf("%s set init EXPOSURE failed ret = %d \n", __func__, ret);
		return ret;
	}

	ret = rts_isp_v4l2_s_ctrl(0, &c_gain);

	if (ret) {
		printf("%s set init GAIN failed ret = %d \n", __func__, ret);
		return ret;
	}

	if (isp_iq_is_ae_on()) {
		c_autoexp.value = 1;
		ret = rts_isp_v4l2_s_ctrl(0, &c_autoexp);

		if (ret) {
			printf("%s re-enable AUTOGAIN failed ret = %d \n", __func__, ret);
			return ret;
		}
	}

	return 0;

}

int hal_isp_set_init_awb(int init_r_gain, int init_b_gain)
{

	struct v4l2_control c_r_gain, c_b_gain, c_auto_wb;
	int ret;

	c_r_gain.id = V4L2_CID_RED_BALANCE;
	c_r_gain.value = init_r_gain;

	c_b_gain.id = V4L2_CID_BLUE_BALANCE;
	c_b_gain.value = init_b_gain;

	c_auto_wb.id = V4L2_CID_AUTO_WHITE_BALANCE;
	c_auto_wb.value = 0;

	ret = rts_isp_v4l2_s_ctrl(0, &c_auto_wb);

	if (ret) {
		printf("%s disable AUTO WB failed ret = %d \n", __func__, ret);
		return ret;
	}

	ret = rts_isp_v4l2_s_ctrl(0, &c_r_gain);

	if (ret) {
		printf("%s set init RED_BALANCE failed ret = %d \n", __func__, ret);
		return ret;
	}

	ret = rts_isp_v4l2_s_ctrl(0, &c_b_gain);

	if (ret) {
		printf("%s set init BLUE_BALANCE failed ret = %d \n", __func__, ret);
		return ret;
	}

	if (isp_iq_is_awb_on()) {
		c_auto_wb.value = 1;
		ret = rts_isp_v4l2_s_ctrl(0, &c_auto_wb);

		if (ret) {
			printf("%s re-enable AUTO WB failed ret = %d \n", __func__, ret);
			return ret;
		}
	}

	return 0;

}


int hal_isp_get_ae_statis(ae_statis_t *p_ae_statis, enum ISP_AE_statis_type type)
{
	int ret;
	struct rts_isp_ae_stat_info stat_info;
	const struct rts_isp_ae_statis *statis;

	ret = rts_isp_get_ae_statis_info(ISP0, &stat_info);
	if (ret) {
		printf("get ae stat info fail %d \n", ret);
		return ret;
	}
	ret = rts_isp_query_ae_statis(ISP0, &statis);
	if (ret) {
		printf("query ae statis fail %d \n", ret);
		return ret;
	}
	ret = rts_isp_get_ae_statis(ISP0, statis);
	if (ret) {
		printf("get ae statis fail %d \n", ret);
		rts_isp_release_ae_statis(ISP0, statis);
		return ret;
	}

	//print_ae_statis(&stat_info, statis);


	int i;
	p_ae_statis->win_cnt = stat_info.win.cols * stat_info.win.rows;

	if (type == AE_STATIS_HIST) {
		printf("AE_STATIS_HIST\n\r");
		for (i = 0; i < 256; i++ ) {
			p_ae_statis->hist[i] = statis->hist[i];
		}
	} else {
		printf("AE_STATIS_YMEAN\n\r");
		for (i = 0; i < 256; i++ ) {
			p_ae_statis->hist[i] = statis->y_mean[i];
		}
	}

	p_ae_statis->frame_count = statis->frame_count;

	rts_isp_release_ae_statis(ISP0, statis);

	return 0;
}


int hal_isp_get_awb_statis(awb_statis_t *p_awb_statis)
{
	int ret;
	struct rts_isp_awb_stat_info stat_info;
	const struct rts_isp_awb_statis *statis;

	ret = rts_isp_get_awb_statis_info(ISP0, &stat_info);
	if (ret) {
		printf("get awb stat info fail %d \n", ret);
		return ret;
	}
	ret = rts_isp_query_awb_statis(ISP0, &statis);
	if (ret) {
		printf("query awb statis fail %d \n", ret);
		return ret;
	}
	ret = rts_isp_get_awb_statis(ISP0, statis);
	if (ret) {
		printf("get awb statis fail %d \n", ret);
		rts_isp_release_awb_statis(ISP0, statis);
		return ret;
	}

	//print_ae_statis(&stat_info, statis);


	int i;
	p_awb_statis->win_cnt = stat_info.win.cols * stat_info.win.rows;
	for (i = 0; i < p_awb_statis->win_cnt; i++ ) {
		//p_awb_statis->r_mean[i] = statis->r_mean[i];
		//p_awb_statis->g_mean[i] = statis->g_mean[i];
		//p_awb_statis->b_mean[i] = statis->b_mean[i];
		p_awb_statis->rg[i] = statis->rg[i];
		p_awb_statis->bg[i] = statis->bg[i];
	}

	p_awb_statis->frame_count = statis->frame_count;

	rts_isp_release_awb_statis(ISP0, statis);


	return 0;
}

int hal_isp_set_init_dn_mode(int dn_mode)
{

	struct v4l2_control c_dn_mode;
	int ret;

	c_dn_mode.id = RTS_V4L2_CID_DAY_NIGHT;
	c_dn_mode.value = dn_mode;

	ret = rts_isp_v4l2_s_ctrl(0, &c_dn_mode);

	if (ret) {
		printf("%s set init day/night mode failed ret = %d \n", __func__, ret);
		return ret;
	}

	printf("set initial day/night mode : %s mode \n", (dn_mode==RTS_ISP_DAY)?"day":"night");

	return 0;

}

void hal_isp_set_direct_i2c_mode(uint32_t direct_i2c_mode)
{
	isp_top_set_direct_i2c_mode(direct_i2c_mode);
	if (direct_i2c_mode != 0 ) {
		printf("turn direct_i2c_mode %ld \n", direct_i2c_mode);
	}
}

int hal_isp_set_init_gray_mode(int gray_mode)
{

	struct v4l2_control c_gray_mode;
	int ret;

	c_gray_mode.id = RTS_V4L2_CID_GRAY;
	c_gray_mode.value = gray_mode;

	ret = rts_isp_v4l2_s_ctrl(0, &c_gray_mode);

	if (ret) {
		printf("%s set init gray_mode failed ret = %d \n", __func__, ret);
		return ret;
	}



	return 0;

}


int hal_isp_get_real_fps(int ch, int *fps100)
{


	int ret = 0;
	int exposure;
	int max_fps;
	int min_fps;
	int exp_maxfps;
	int realfps100;
	int sensor_fps;
	int stream_fps;
	uint32_t skip_m, skip_n;
	struct v4l2_control c;
	struct rts_isp_meta_param m_param = {0};

	//The exp obtained from v4l2 uses ceil, so the calculated fps will be lower.
	//The exp obtained from meta uses truncate, so the calculated fps will be higher.
	//Therefore, when comparing with exp_maxfps in the following conditional statement, the max fps is used
	ret = rts_isp_get_meta_param(ISP0, &m_param);
	if (ret) {
		printf("rts_isp_get_meta_param %d\n", ret);
		return ret;
	}
	exposure = (int)m_param.exposure_h;
	if ( exposure == 0 ) {
		printf("%s meta exposure = 0 \n", __func__);
		return NOK;

	}

	c.id = RTS_V4L2_CID_AE_MAX_FPS;
	ret = rts_isp_v4l2_g_ctrl(0, &c);
	if (ret != 0 ) {
		printf("%s set get v4l2 MAX_FPS failed ret = %d \n", __func__, ret);
		return ret;
	}
	max_fps = c.value;

	c.id = RTS_V4L2_CID_AE_MIN_FPS;
	ret = rts_isp_v4l2_g_ctrl(0, &c);
	if (ret != 0 ) {
		printf("%s set get v4l2 MIN_FPS failed ret = %d \n", __func__, ret);
		return ret;
	}
	min_fps = c.value;

	//printf("exposure %d maxfps %d minfps %d \n", exposure, max_fps, min_fps);
	exp_maxfps = 1000000/max_fps;

	if ( exposure <= exp_maxfps ) {
		realfps100 = max_fps*100;
	} else {
		realfps100 = 100000000/exposure;
	}

	get_skip_para(ch, &skip_m, &skip_n);
	printf("sensor fps %d isp skip %ld/%ld \n", realfps100, skip_n, skip_m);
	//printf("realfps100 %d skipm %d n %d \n", realfps100, skip_m, skip_n);

	if ( skip_n && skip_m && (skip_m > skip_n) ) {
		*fps100 = realfps100*(skip_m-skip_n)/skip_m;
	} else if ( skip_n == 0 && skip_m == 1 ){
		*fps100 = realfps100;
	} else {
		printf("skip info invalid %ld/%ld \n", skip_n, skip_m);
		return NOK;
	}

	return OK;

}

int hal_isp_set_ae_weight(uint8_t *weights, int win_num)
{
		int ret;
		struct rts_isp_ae_setting *setting;

		ret = rts_isp_query_ae_setting(ISP0, &setting);
		if (ret) {
			isp_error("query setting fail %d \n", ret);
			return ret;
		}
		if ( win_num != setting->_auto.window_num) {
			isp_error("input num %d isn't equal to ae weight num %d \n", win_num, setting->_auto.window_num);
			return NOK;
		}
		memcpy((void *)setting->_auto.win_weights, (void *)weights, sizeof(uint8_t)*setting->_auto.window_num);

		ret = rts_isp_set_ae_setting(ISP0, setting);
		if (ret) {
			isp_error("set_ae_setting fail %d \n", ret);
			rts_isp_release_ae_setting(ISP0, setting);
			return ret;
		}
		rts_isp_release_ae_setting(ISP0, setting);
		return 0;
}

int hal_isp_get_ae_weight(uint8_t *weights, int *win_num)
{
		int ret;
		struct rts_isp_ae_setting *setting;

		ret = rts_isp_query_ae_setting(ISP0, &setting);
		if (ret) {
			isp_error("query setting fail %d \n", ret);
			return ret;
		}
		*win_num = setting->_auto.window_num;

		memcpy((void *)weights, (void *)setting->_auto.win_weights, sizeof(uint8_t)*setting->_auto.window_num);
		rts_isp_release_ae_setting(ISP0, setting);
		return 0;
}

int hal_isp_get_max_dyn_region(enum hal_isp_ae_region *region)
{
	return rts_isp_get_max_dyn_region(ISP0, (enum rts_isp_ae_region *)region);
}

int hal_isp_set_max_dyn_region_en(uint8_t max_dyn_region_en)
{
	return rts_isp_set_max_dyn_region_en(ISP0, max_dyn_region_en);
}

int hal_isp_set_mask(isp_mask_group_t *input_mask)
{
	int i;
	int ret;
	struct rts_isp_mask *mask;
	struct rts_isp_mask_entry *entry;
	isp_grid_mask_entry_t *input_grid_entry;
	isp_rect_t *input_rect_entry;

	ret = rts_isp_query_mask(ISP0, &mask);
	if (ret) {
		isp_error("query mask fail %d \n", ret);
		return ret;
	}
	mask->color = input_mask->color;

	printf("color 0x%06x status %d %d %d %d %d \n",
			input_mask->color, input_mask->grid_mask_set_status,
			input_mask->rect_mask_set_status[0],input_mask->rect_mask_set_status[1],
			input_mask->rect_mask_set_status[2],input_mask->rect_mask_set_status[3]
	);

	for (i = 0; i < mask->number; i++) {

		entry = &mask->entries[i];

		if ( entry->type == RTS_ISP_GRID && i == 0) {

			if (input_mask->grid_mask_set_status == ISP_MASK_SET) {
				input_grid_entry = &(input_mask->grid_mask);
				entry->enable = RTS_ISP_TRUE;
				entry->grid.start.x = input_grid_entry->grid.start_x;
				entry->grid.start.y = input_grid_entry->grid.start_y;
				entry->grid.cell.w = input_grid_entry->grid.cell_w;
				entry->grid.cell.h = input_grid_entry->grid.cell_h;
				entry->grid.size.cols = input_grid_entry->grid.cols;
				entry->grid.size.rows = input_grid_entry->grid.rows;
				memcpy((void *)entry->bitmap, (void *)input_grid_entry->bitmap, (input_grid_entry->grid.cols*input_grid_entry->grid.rows+7)/8);
				printf("grid %d %d %d %d %d %d \n", entry->grid.start.x, entry->grid.start.y, entry->grid.cell.w,
						entry->grid.cell.h, entry->grid.size.cols, entry->grid.size.rows);
			} else if (input_mask->grid_mask_set_status == ISP_MASK_CLEAR) {
				entry->enable = RTS_ISP_FALSE;
			}

		} else if (entry->type == RTS_ISP_RECT && i > 0) {

			if (input_mask->rect_mask_set_status[i-1] == ISP_MASK_SET) {
				input_rect_entry = &(input_mask->rect_mask[i-1]);
				entry->enable = RTS_ISP_TRUE;
				entry->rect.left = input_rect_entry->left;
				entry->rect.top = input_rect_entry->top;
				entry->rect.right = input_rect_entry->right;
				entry->rect.bottom = input_rect_entry->bottom;
				printf("rect %d %d %d %d %d \n", i, entry->rect.left, entry->rect.top, entry->rect.right,
						entry->rect.bottom);


			} else if (input_mask->rect_mask_set_status[i-1] == ISP_MASK_CLEAR) {
				entry->enable = RTS_ISP_FALSE;
			}

		} else {
			isp_error("mask id error type %s id %d \n", (entry->type == RTS_ISP_GRID)?"grid":"rect", i);
			rts_isp_release_mask(ISP0, mask);
			return NOK;
		}
	}
	ret = rts_isp_set_mask(ISP0, mask);
	if (ret) {
		isp_error("set mask fail %d \n", ret);
		rts_isp_release_mask(ISP0, mask);
		return ret;
	}
	rts_isp_release_mask(ISP0, mask);
	return 0;
}

int hal_isp_config_iq_calibration(int config_flag)
{
	rts_av_isp_set_iq_calb_en(ISP0, config_flag);
	rts_isp_tuning_reload_packed_iq(ISP0);
	return 0;
}

void hal_isp_set_hdr_mode(uint32_t hdr_mode)
{
	isp_top_set_hdr_mode(hdr_mode);
}

void hal_isp_set_mirrorflip_mode(uint32_t mirrorflip_mode)
{
	isp_top_set_mirrorflip_mode(mirrorflip_mode);
}

int hal_isp_set_stream_fps(uint32_t ch, uint32_t fps)
{
	int ret;
	int fd;

	fd = get_stream_fd(ch);
	ret = rts_v4l2_set_frmival(fd, 1, fps);

	return ret;
}

static u32 g_init_fps = 0;

void hal_isp_set_init_frame_rate(u32 val)
{
	g_init_fps = val;
	printf("g_init_fps: %d\n\r", g_init_fps);
}
u32 hal_isp_get_init_frame_rate(void)
{
	return g_init_fps;
}

static u32 g_voe_axi_size[BUF_ITEM_NUM] = {
	6144, //ISP_Y0_BUF
	6144, //ISP_UV0_BUF
	3072, //ISP_Y1_BUF
	3072, //ISP_UV1_BUF
	1536, //ISP_Y2_BUF
	1536, //ISP_UV2_BUF
	1536, //ISP_Y3_BUF
	1536, //ISP_UV3_BUF
	10752,//TNR_BUF
	512,  //OSD_BUF
	512,  //STATIS_BUF
	0, //MD0_BUF org: 2560
	0,  //MD1_BUF org: 512
	1536,  //RGB_R_BUF org: 512
	1536,  //RGB_B_BUF org: 512
	1536,  //RGB_G_BUF org: 512
};

//if addr0 & addr1 == 0xffffffff, means last trigger
//if addr0 & addr1 == 0, means not verify path or end
static struct verify_ctrl_config verify_conf = {
	.verify_addr = {0},
	.verify_number = 0,
	.verify_ylen = 0,
	.verify_uvlen = 0,
	.verify_nlsc_center = {0},
};

void hal_isp_set_init_axi_buf(u32 *buf)
{
	int i = 0;
	if (buf != NULL) {
		SCB_InvalidateDCache_by_Addr((uint32_t *)buf, sizeof(u32)*BUF_ITEM_NUM);
		memcpy((void*)g_voe_axi_size, (void*)buf, sizeof(g_voe_axi_size));
	}

	for (i = 0; i <= ISP_UV3_BUF; i++) {
		g_voe_axi_size[i] /= 16;
	}
}

u32 hal_isp_get_axi_buf_size(enum ISP_Buf_Cfg_Order sel)
{
	return g_voe_axi_size[sel];
}

u32 hal_isp_get_axi_buf_addr(enum ISP_Buf_Cfg_Order sel)
{
	int i = 0;
	u32 addr = 0;

	if (sel <= ISP_UV3_BUF) {
		for (i = 1; i <= sel; i++) {
			addr += g_voe_axi_size[i-1];
			//printf("i = %d, addr = %x\n\r", i, addr);
		}
	} else {
		for (i = TNR_BUF+1; i <= sel; i++) {
			addr += g_voe_axi_size[i-1];
			//printf("i = %d, addr = %x\n\r", i, addr);
		}
	}

	return addr;
}

void hal_isp_set_verify_info(struct verify_ctrl_config v_cfg)
{
	verify_conf.verify_number = v_cfg.verify_number;
	memcpy(&verify_conf.verify_addr[0], &v_cfg.verify_addr[0], sizeof(verify_conf.verify_addr));
	verify_conf.verify_ylen = v_cfg.verify_ylen;
	verify_conf.verify_uvlen = v_cfg.verify_uvlen;

	memcpy(&verify_conf.verify_nlsc_center[0], &v_cfg.verify_nlsc_center[0], sizeof(verify_conf.verify_nlsc_center));
}

int hal_isp_get_verify_info(struct verify_ctrl_config *v_cfg)
{
	if (v_cfg == NULL)
		return NOK;

	v_cfg->verify_number = verify_conf.verify_number;
	memcpy(&v_cfg->verify_addr[0], &verify_conf.verify_addr[0], sizeof(v_cfg->verify_addr));
	v_cfg->verify_ylen = verify_conf.verify_ylen;
	v_cfg->verify_uvlen = verify_conf.verify_uvlen;

	memcpy(&v_cfg->verify_nlsc_center[0], &verify_conf.verify_nlsc_center[0], sizeof(v_cfg->verify_nlsc_center));

	return OK;
}

int hal_isp_is_verify_path_on(void)
{
	struct verify_ctrl_config v_cfg;
	memset(&v_cfg, 0, sizeof(struct verify_ctrl_config));

	hal_isp_get_verify_info(&v_cfg);

	return (v_cfg.verify_number != 0);
}

void hal_isp_verify_path_config_buf(u32 idx)
{
	isp_hw_verify_path_config_buf(idx);
}

void hal_isp_verify_path_trigger(u32 delay_ms)
{
	isp_hw_verify_path_trigger(delay_ms);
}

static u32 g_verify_counter = 1;
void hal_isp_set_verify_counter(void)
{
	g_verify_counter++;
}

u32 hal_isp_get_verify_counter(void)
{
	return g_verify_counter;
}


int hal_isp_tuning_iq_nlsc(u32 idx, struct verify_ctrl_config v_cfg)
{
	struct isp_hw_nlsc_center center;

	center.r.x = v_cfg.verify_nlsc_center[idx].verify_nlsc_rcenter_x;
	center.r.y = v_cfg.verify_nlsc_center[idx].verify_nlsc_rcenter_y;
	center.g.x = v_cfg.verify_nlsc_center[idx].verify_nlsc_gcenter_x;
	center.g.y = v_cfg.verify_nlsc_center[idx].verify_nlsc_gcenter_y;
	center.b.x = v_cfg.verify_nlsc_center[idx].verify_nlsc_bcenter_x;
	center.b.y = v_cfg.verify_nlsc_center[idx].verify_nlsc_bcenter_y;

	return isp_hw_nlsc_set_center(ISP0, &center);
}

int hal_isp_set_statis_irq_en(u32 statis_irq_en)
{
	return rts_isp_set_statis_irq_en(ISP0, statis_irq_en);
}

void hal_isp_set_zoom_filter_coeff(u8* buff)
{
	rtscam_zoom_set_filter_coef(buff);
}

static u32 g_zoom_1x1_up_en = 0;
void hal_isp_set_zoom_1x1_up_en(u32 en)
{
	g_zoom_1x1_up_en = en;
}

u32 hal_isp_get_zoom_1x1_up_en(void)
{
	return g_zoom_1x1_up_en;
}

BOOL hal_isp_check_err_code_new_ver(int ret)
{
	if ((ret & 0xffff0000) == 0xffff0000)
		return FALSE;
	else
		return TRUE;
}

int hal_isp_get_dir_wdr_level(uint8_t* level)
{
	int ret = OK;

	ret = rts_isp_get_dir_wdr_level(ISP0, level);
	if (ret) {
		isp_error("get wdr level fail %d\r\n", ret);
	}

	return ret;
}

int hal_isp_set_dir_wdr_level(uint8_t* level)
{
	int ret = OK;

	ret = rts_isp_set_dir_wdr_level(ISP0, level);
	if (ret) {
		isp_error("set wdr level fail %d\r\n", ret);
	}

	return ret;
}

#endif

