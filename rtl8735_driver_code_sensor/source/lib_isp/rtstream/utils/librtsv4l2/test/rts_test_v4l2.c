/*
 * Realtek Semiconductor Corp.
 *
 * rtscamutils/rts_test_v4l2.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
//#include <time.h>
#include <errno.h>
#include "cmsis_os2.h"
#include "rts_ioctl.h"
#include "isp_log.h"
#include "rtsavisp.h"
#include "isp_main.h"
//#include "rt_app.h"
#include "rt_log.h"
#include "rt_osd2_api.h"
#include "rts_video_osdenc.h"
#include "isp_mem.h"
#include <rtscamkit.h>
#include <rtsv4l2.h>

#include <rtsavdef.h>
#include "rts_camera.h"
#include "rt_util.h"
#include "isp_debug.h"
#include "hal_isp.h"
#include "hal_timer.h"
#include "rts_raw.h"

//#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
//#define malloc rts_malloc
//#endif

struct test_buffer {
	void *pbuf;
	uint32_t length;
};

struct v4l2_arg_s {
	int frame_num;
	char *host_ip;
};

#define MAX_FRAME_NUM		4

/*
static uint64_t get_time(void)
{
        uint64_t tm;
        tm = (uint64_t)(xTaskGetTickCount() / portTICK_PERIOD_MS) * (uint64_t)1000000;
        return tm;
}
*/

extern int send_frame_init(char *ipaddr);
//extern int send_to_host(int socket_fd, char *ptrY, int sizeY, int offset_uv, int sizeUV);
#ifdef RTS_VIDEOIN_HEIGHT_ALIGN
extern unsigned int rtscam_socdev_get_height_align(void);
#endif
extern struct rtscam_video_stream *get_stream(int fd);
int gbl_snap_shot=0;

extern uint32_t set_pwr_time, set_i2c_time, set_i2c_end_time, sensor_start_time, sensor_end_time;

int start_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id)
{

	int v4l2_fd;

	uint32_t fmt, width, height, numerator, denominator;
	uint32_t crop_x, crop_y, crop_w, crop_h;

	v4l2_fd = get_stream_fd(stream_id);
	if (!v4l2_fd) {
		isp_error("%s stream id error %d \r\n", __func__, stream_id);
		return -1;
	}

	fmt = get_v4l2_format(isp_adpt->video_stream[stream_id].fmt);
	if (fmt == 0) {
		isp_error("%s stream fmt error %d \r\n", __func__, isp_adpt->video_stream[stream_id].fmt);
		return -1;
	}


	width = isp_adpt->video_stream[stream_id].user_width;
	height = isp_adpt->video_stream[stream_id].user_height;
	numerator = isp_adpt->video_stream[stream_id].rate_numerator;
	denominator = isp_adpt->video_stream[stream_id].rate_denominator;

	crop_x = isp_adpt->video_stream[stream_id].crop_x;
	crop_y = isp_adpt->video_stream[stream_id].crop_y;
	crop_w = isp_adpt->video_stream[stream_id].crop_w;
	crop_h = isp_adpt->video_stream[stream_id].crop_h;
	//printf("crop_x: %d, crop_y: %d, crop_w: %d, crop_h: %d\n\r", crop_x, crop_y, crop_w, crop_h);

	int ret = 0;
	//int i,j;
	struct rtscam_video_stream *stream;

	ret = rts_v4l2_set_selection(v4l2_fd, crop_x, crop_y, crop_w, crop_h);
	if (ret) {
		isp_error("%s rts_v4l2_set_selection error %d \r\n", __func__, ret);
		return ret;
	}
	ret = rts_v4l2_set_fmt(v4l2_fd, fmt, width, height);
	if (ret) {
		isp_error("%s rts_v4l2_set_fmt error %d \r\n", __func__, ret);
		return ret;
	}
	ret = rts_v4l2_set_frmival(v4l2_fd, numerator, denominator);
	if (ret) {
		isp_error("%s rts_v4l2_set_frmival error %d \r\n", __func__, ret);
		return ret;
	}

	//isp_adpt->set_frmival_time = hal_read_curtime_us();

#ifdef _STREAM_FMT_
	printf("%c%c%c%c %dx%d %d/%d\r\n",
	       (int)fmt & 0xff, (int)(fmt >> 8) & 0xff,
	       (int)(fmt >> 16) & 0xff, (int)(fmt >> 24) & 0xff,
	       (int)width, (int)height,
	       (int)numerator, (int)denominator);
#endif

	stream = get_stream(v4l2_fd);
	if (stream == NULL) {
		isp_error("%s get_stream \r\n", __func__);
		return -1;
	}
	stream->sync = isp_adpt->video_stream[stream_id].sync;

	stream->hw_slot_num = isp_adpt->video_stream[stream_id].hw_slot_num;
	stream->stream_buf_num = isp_adpt->video_stream[stream_id].buff_num;

	stream->stream_frame_done = xQueueCreate( stream->stream_buf_num, sizeof(int) );
	isp_info("%s stream_frame_done xQueueCreate item %d \r\n", __func__, stream->stream_buf_num);

	if ( !stream->stream_frame_done ) {
		isp_error("%s stream->stream_frame_done xQueueCreate fail\r\n", __func__);
		return -1;
	}
	for (int i=0; i<isp_adpt->video_stream[stream_id].buff_num; i++) {
		if (isp_adpt->video_stream[stream_id].bufs[i].buf_addr)
			stream->bufs[i].buf_addr = isp_adpt->video_stream[stream_id].bufs[i].buf_addr;
		else {
			isp_error("%s stream%d bufs[%d].buf_addr NULL\r\n", __func__, stream_id, i);
			return -1;
		}
	}
	ret = rts_v4l2_request_bufs(v4l2_fd, stream->stream_buf_num);
	if (ret <= 0) {
		isp_error("%s rts_v4l2_request_bufs error %d \r\n", __func__, ret);
		return ret;
	}


	//isp_adpt->streamon_time = hal_read_curtime_us();
	//_rtl_printf("TTFF [%s] rts_v4l2_streamon %d \r\n",__func__,hal_read_curtime_us());
	ret = rts_v4l2_streamon(v4l2_fd);
	//ret = iot_soc_s_stream(v4l2_fd, 1);
	//printf("%s ret %d \r\n", __FUNCTION__, ret);
	isp_adpt->set_pwr_time = set_pwr_time;
	isp_adpt->set_i2c_time = set_i2c_time;
	isp_adpt->set_i2c_end_time = set_i2c_end_time;
	isp_adpt->sensor_start = sensor_start_time;
	isp_adpt->sensor_end = sensor_end_time;
	if (!ret)
		isp_adpt->video_stream[stream_id].stream_running = TRUE;
	else {
		printf("%s stream on failed %d \r\n", __FUNCTION__, ret);
	}
#if 0
	if (isp_adpt->raw_fmt != RTS_RAW_SRC_DISABLE && isp_adpt->raw_fmt < RTS_RAW_SRC_RESERVED  ) {
		if ( isp_adpt->video_stream[stream_id].fmt	!= NV16_FORMAT ) {
			printf("rts_hal_set_raw only support NV16 \r\n");
		} else {
			rts_hal_set_raw(stream_id, isp_adpt->raw_fmt);
		}
	}
#endif

	//HAL_WRITE32(0x40300000, 0x0048, 5);
	//printf("%s READ 0x%08x\r\n", __FUNCTION__, HAL_READ32(0x40300000, 0x0048));

	return ret;
}





#if 0
int test_preview(int fd, int socket_fd, uint32_t fmt, uint32_t width, uint32_t height,
		 uint32_t numerator, uint32_t denominator, int fnum)
{
	int v4l2_fd;
	int number = 4;
	struct test_buffer buffers[MAX_FRAME_NUM];
	//uint64_t start;
	int ret;
	int i,j;
	int chn_id;
	int align_h, offset_uv;

	if (fd >= 0)
		v4l2_fd = fd;
	else
		v4l2_fd = rts_v4l2_open("/dev/video51", O_RDWR);

	if (v4l2_fd < 0)
		return -1;
	isp_info("rts_v4l2_open done \r\n");
	memset(buffers, 0, sizeof(buffers));

	rts_v4l2_set_fmt(v4l2_fd, fmt, width, height);
	rts_v4l2_set_frmival(v4l2_fd, numerator, denominator);

	printf("%c%c%c%c %dx%d %d/%d\n",
	       (int)fmt & 0xff, (int)(fmt >> 8) & 0xff,
	       (int)(fmt >> 16) & 0xff, (int)(fmt >> 24) & 0xff,
	       (int)width, (int)height,
	       (int)numerator, (int)denominator);

	ret = rts_v4l2_request_bufs(v4l2_fd, MAX_FRAME_NUM);
	if (ret <= 0) {
		ret = -1;
		goto exit;
	}
	number = ret;
	for (i = 0; i < number; i++) {
		ret = rts_v4l2_query_mmap_buf(v4l2_fd, i, &buffers[i].pbuf,
					      &buffers[i].length);
		if (RTS_IS_ERR(ret))
			goto exit1;
	}

	chn_id = (v4l2_fd % 10) - 1;
	if (check_chn_id(chn_id)) {  //valid chn, init osd2
		ret = rt_osd2_init_chn_profile(chn_id, RTS_V_FMT_YUV420SEMIPLANAR, width, height,
										numerator, denominator);
		if (ret != RT_OK)
			goto exit2;
	}
	printf("{osd2} create chn#0, %s\n", rt_code_str(ret));

	ret = rts_v4l2_streamon(v4l2_fd);

	//get offset of UV buffer start, see rts_camera_soc_3915.c/rtscam_socdev_submit_buffer()
	offset_uv = width * height;
	align_h = rtscam_socdev_get_height_align();
	if (align_h) {
		if (height % align_h)
			offset_uv += (align_h - height % align_h) * width;
	}

	//start = get_time();
	i=j=0;
	gbl_snap_shot = 0;
	while (1) {
		struct v4l2_buffer buf;
		//if (get_time() - start > 1e6 * timeout)
		if (fnum == 0)
			break;

j++;
		ret = rts_v4l2_get_buffer(v4l2_fd, &buf);
		if (RTS_IS_ERR(ret))
			continue;

		if (fnum > 0) fnum--;

/*
		taskENTER_CRITICAL();
		printf("frame %d:0x%08x size:%d use:%d try:%d get:%d data:0x%08x\n",
			buf.index,
			(unsigned int)buffers[buf.index].pbuf, (int)buffers[buf.index].length, buf.bytesused, 
			i, j, *((int*)buffers[buf.index].pbuf));
		taskEXIT_CRITICAL();
*/

		ret = rt_osd2_encode(chn_id, (void*)buffers[buf.index].pbuf, buf.bytesused);
		if ((ret != RT_E_NOT_INIT) && (ret != RT_E_NOT_START) && (ret != RT_OK))
		{
			printf("rt_osd2_encode(), %s\n", rt_code_str(ret));
		}

		if (socket_fd >= 0 && gbl_snap_shot &&
			buffers[buf.index].pbuf && buf.bytesused) {
			//send_to_host(socket_fd, buffers[buf.index].pbuf, width*height, offset_uv, width*height/2);
			gbl_snap_shot = 0;
		}
		rts_v4l2_put_buffer(v4l2_fd, &buf);
	}

	rts_v4l2_streamoff(v4l2_fd);
	
exit2:
	rts_av_osdenc_cleanup(chn_id);

exit1:
	for (i = 0; i < number; i++)
		rts_v4l2_munmap_buf(buffers[i].pbuf, buffers[i].length);
	rts_v4l2_request_bufs(v4l2_fd, 0);
exit:
	if (fd < 0)
		RTS_SAFE_CLOSE(v4l2_fd, rts_v4l2_close);

	return 0;
}

static void v4l2_start(void *arg)
{
	struct v4l2_arg_s *parg = (struct v4l2_arg_s *)arg;
	int fd = -1;
	int socket_fd;

	socket_fd = (parg->host_ip) ? send_frame_init(parg->host_ip) : -1;

	//isp_log_open(ISP_LOG2CONS, ISP_DEBUG_CORE_ALL);
	test_preview(-1, socket_fd, V4L2_PIX_FMT_NV12, 1920, 1080, 1, 30, parg->frame_num);

	if (socket_fd>=0)
		close(socket_fd);
	RTS_SAFE_CLOSE(fd, rts_v4l2_close);

	vTaskDelete(NULL);
}

int cmd_test_v4l2(int argc, char *argv[])
{
	int ret=0;
	static TaskHandle_t *v4l2_handle = NULL;
	struct v4l2_arg_s args;

	//if (argc > 1)
	//	fd = rts_v4l2_open(argv[1], O_RDWR);
#if 0
	if ((argc < 2)||(3 < argc)) {
		printf("usage: tdrv v4l2 frame_num [host_IP]\n");
		return ret;
	}

	args.frame_num = atoi(argv[1]);
	args.host_ip = (argc == 3) ? argv[2] : NULL;
	task_info_st  task_info =
	{
	    .name       = "v4l2_start",
	    .priority   = 3,
	    .delay      = pdMS_TO_TICKS(100),
	    .func       = v4l2_start,
	    .param      = (void*)&args,
	    .stack_size = SZ_64K,
	    .pre_del_cb = NULL,
	};
	if ((v4l2_handle = task_create_user_by_struct(&task_info, &ret)) == NULL)
	{
	    printf("%s osThreadNew fail\n", __func__);
	    ret = RTS_FAIL;
	}
	
	vTaskResume(v4l2_handle);
#endif
	return ret;
}
#endif
