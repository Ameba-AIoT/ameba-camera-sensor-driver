/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_video.c
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */

#define TAG	"VIDEO"

#include <fcntl.h>
#include "cmsis_os2.h"
#include <errno.h>
#include "rts_errno.h"
#include <media/videobuf2-core.h>
#include <media/v4l2-dev.h>
#include <rtscamkit.h>
#include <linux/poll.h>
#include "rts_camera_priv.h"
#include "rts_camera.h"
#include "rts_camera_fps.h"
#include "rts_ioctl.h"
#include "rts_camera_soc_3915_regs.h"
#include "isp_reg_base.h"
#include "rtx_mutex.h"
#include "rt_time.h"
#include "rts_camera_soc_priv.h"
#include "rt_osd2_api.h"
#include "hal_timer.h"
#include "rts_camera.h"
#include "isp_debug.h"
volatile u32 send_isp_time = 0;
#include "hal_isp.h"

#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM
#include "voe.h"
extern QueueHandle_t isp2osd_queue;
extern QueueHandle_t isp2tm_queue;
#endif
static int rtscam_video_release_slot(struct rtscam_video_stream *stream, int release_slot);

extern u32 log_time[10];	//   0: reset handle 1-2: open_io_t   2-3: open_enc_t 3-4: open_isp_t
							// 5-6: start_isp_t  6-7: start_enc_t   8: isp_done


static struct rtscam_video_device *gbl_icd=NULL;
extern volatile int buf_done[5][3];
extern volatile int buf_release[5][3];
struct rtscam_video_stream *get_stream(int fd)
{
	int index;

	switch (fd)
	{
		case ID_RTS_VIDEO_DEV1:  // /dev/video51
			index = 0;
			break;
		case ID_RTS_VIDEO_DEV2:  // /dev/video52
			index = 1;
			break;
		case ID_RTS_VIDEO_DEV3:  // /dev/video53
			index = 2;
			break;
		case ID_RTS_VIDEO_DEV4:  // /dev/video54
			index = 3;
			break;
		case ID_RTS_NN_DEV:  	// /dev/video61
			index = 4;
			break;
		default:
			index = -1;
			break;
	}
	if ((index < 0) || (RTSCAM_VIDEO_SUPPORT_MAX_STREAM_NUM <= index))
		return NULL;

	return gbl_icd->streams + index;
}

/*
static int rtscam_convert_addr_from_vm_to_phy(struct rtscam_video_device *icd,
				       unsigned long vm_addr,
				       unsigned long *phy_addr)
{
	struct vm_area_struct *vma = NULL;
	void *buf = NULL;
	int found = 0;
	int i;

	if (!icd->mem_ops ||
	    !icd->mem_ops->get_userptr || !icd->mem_ops->put_userptr ||
	    !icd->mem_ops->cookie)
		return -EINVAL;

	if (!vm_addr)
		return -EINVAL;

	vma = find_vma(current->mm, vm_addr);
	if (NULL == vma)
		return -EINVAL;

	for (i = 0; i < icd->streamnum; i++) {
		struct rtscam_video_stream *stream = icd->streams + i;
		if (vma->vm_file == stream->memory_owner) {
			found = 1;
			break;
		}
	}
	if (!found) {
		rtsprintk(RTS_TRACE_ERROR, "not rts camera video buffer\n");
		return -EINVAL;
	}

	buf = icd->mem_ops->get_userptr(icd->dev,
					vm_addr, vma->vm_end - vma->vm_start,
					!V4L2_TYPE_IS_OUTPUT(icd->type));

	if (!buf)
		return -EINVAL;

	if (phy_addr)
		*phy_addr = *(dma_addr_t *) icd->mem_ops->cookie(buf);

	icd->mem_ops->put_userptr(buf);
	return 0;
}
*/


int rtscam_get_phy_addr(struct rtscam_video_stream *stream, int *phy_addr)
{
	//struct rtscam_video_stream *stream = vb2_get_drv_priv(vb->vb2_queue);
	//struct rtscam_video_device *icd = stream->icd;
	//dma_addr_t *dma_addr = NULL;

#if 1
	*phy_addr = 0;
	for (int i=0; i<stream->stream_buf_num; i++) {
		if (stream->bufs[i].state == RTS_BUF_STATE_READY) {
			*phy_addr = stream->bufs[i].buf_addr;
			stream->bufs[i].state = RTS_BUF_STATE_HW;
			break;
		}
	}
	if (*phy_addr == 0) {
		//isp_warning(" %s stream %d get free buffer failed \r\n", __func__, stream->streamid);
		return -EINVAL;
	}

	//*phy_addr = 0x72000000;//video_malloc(1920*1080*3/2);

#else


	if (!icd->mem_ops)
		return -EINVAL;

	dma_addr = vb2_plane_cookie(vb, 0);
	if (!dma_addr)
		return -EINVAL;

	if (phy_addr)
		*phy_addr = *dma_addr;
#endif

	return 0;


}
//EXPORT_SYMBOL_GPL(rtscam_get_phy_addr);

static void rtscam_init_capture_buffer(struct rtscam_video_stream *stream)
{
	if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock_irq(&stream->lock);
		isp_error("rtscam_init_capture_buffer wait stream->lock timeout\n\r");
		return;
	}
	INIT_LIST_HEAD(&stream->capture);
	rtscam_call_video_op(stream->icd, init_capture_buffers, stream);

	for (int i=0; i<stream->stream_buf_num; i++) {
		if (!stream->bufs[i].buf_addr) {
			isp_error(" %s stream %d  buffer %d NULL \r\n", __func__, stream->streamid, i);
		} else {
			stream->bufs[i].state = RTS_BUF_STATE_READY;
			stream->buf_done[i] = 0;
			stream->buf_release[i] = 0;
			//printf(" %s stream %d  buffer 0x%08x ready \r\n", __func__, stream->streamid , stream->bufs[i].buf_addr);
		}
	}

	xSemaphoreGive(stream->lock);  //	spin_unlock_irq(&stream->lock);
}

struct rtscam_video_buffer *rtscam_get_video_buffer(
		struct rtscam_video_stream *stream, int index)
{
	struct rtscam_video_buffer *buffer = NULL;
	struct vb2_buffer *vb = NULL;

	if (!stream)
		return NULL;

	if (index < 0 || index >= (int)stream->vb2_vidp.num_buffers)
		return NULL;

	vb = stream->vb2_vidp.bufs[index];
	buffer = (struct rtscam_video_buffer *)to_rtscam_vbuf(vb);

	return buffer;
}
//EXPORT_SYMBOL_GPL(rtscam_get_video_buffer);

static int rtscam_set_buffer_state(struct rtscam_video_buffer *buffer,
					int state)
{
#if 0
	if (!buffer)
		return -EINVAL;

	if (state < RTS_BUF_STATE_IDLE || state >= RTS_BUF_STATE_RESERVED)
		return -EINVAL;

	buffer->state = state;
#endif
	return 0;
}
#if 0
static struct rtscam_video_buffer *rtscam_pop_ready_buffer(
		struct rtscam_video_stream *stream)
{
	struct rtscam_video_buffer *buf = NULL;

	if (!stream) {
		rtsprintk(RTS_TRACE_ERROR, "stream Null\n");
		return NULL;
	}

	if (list_empty(&stream->capture)) {
		rtsprintk(RTS_TRACE_NOTICE, "stream->capture queue empty\n");
		return NULL;
	}

	buf = list_first_entry(&stream->capture,
			       struct rtscam_video_buffer, list);
	list_del_init(&buf->list);

	return buf;
}
#endif
int rtscam_push_back_ready_buffer(struct rtscam_video_stream *stream,
				  struct rtscam_video_buffer *buf)
{
#if 0
	struct rtscam_video_buffer *rbuf;

	if (!stream || !buf) {
		rtsprintk(RTS_TRACE_ERROR, "Null arguments\n");
		return -EINVAL;
	}

	list_for_each_entry(rbuf, &stream->capture, list, struct rtscam_video_buffer) {
		if (rbuf == buf) {
			rtsprintk(RTS_TRACE_WARNING, "bfr 0x%08x already in que\n", (u32)rbuf);
			return 0;
		}
	}

	rtscam_set_buffer_state(buf, RTS_BUF_STATE_READY);
	list_add_tail(&buf->list, &stream->capture);
#endif
	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_push_back_ready_buffer);

static void rtscam_clr_ready_buffer(struct rtscam_video_stream *stream)
{
	struct rtscam_video_buffer *buffer;
	struct rtscam_video_buffer *tmp;

	if (!stream)
		return;

	list_for_each_entry_safe(buffer, tmp, &stream->capture, list, struct rtscam_video_buffer) {
		list_del_init(&buffer->list);
		rtscam_set_buffer_state(buffer, RTS_BUF_STATE_IDLE);
	}

	INIT_LIST_HEAD(&stream->capture);
}

static void rtscam_return_buffers(struct rtscam_video_stream *stream)
{

}

int rtscam_submit_buffer(struct rtscam_video_stream *stream,
			 struct rtscam_video_buffer *buf)
{
	struct rtscam_video_buffer *rbuf = NULL;
	int ret;
	//isp_info("%s buf 0x%08x \r\n",__FUNCTION__, buf);
#if 0
	if (buf) {
		rtscam_push_back_ready_buffer(stream, buf);
	}

	rbuf = rtscam_pop_ready_buffer(stream);
	if (!rbuf) {
		//rtsprintk(RTS_TRACE_ERROR, "can't get free buffer\n");
		return -EINVAL;
	}
#endif
	ret = rtscam_call_video_op(stream->icd, submit_buffer, stream, rbuf);
	if (ret) {
		//isp_error("set HW frame buffer fail & recycle 0x%08x\r\n", (u32)rbuf);
		//rtscam_push_back_ready_buffer(stream, rbuf);
		return ret;
	}

	//rtscam_set_buffer_state(rbuf, RTS_BUF_STATE_HW);

	return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_submit_buffer);

#if 0
static void __rtscam_buffer_done(struct rtscam_video_buffer *buffer)
{
	if (!buffer)
		return;

	rtscam_set_buffer_state(buffer, RTS_BUF_STATE_DONE);
	vb2_buffer_done(&buffer->buf.vb2_buf, VB2_BUF_STATE_DONE);  //wake __vb2_get_done_vb
}
#endif
/*
static void rtscam_buffer_wq_handle(struct work_struct *work)
{
	struct delayed_work *dwork;
	struct rtscam_video_buffer *rbuf;

	if (!work)
		return;

	dwork = to_delayed_work(work);
	rbuf = container_of(dwork, struct rtscam_video_buffer, dwork);

	__rtscam_buffer_done(rbuf);
}

static void rtscam_delay_buffer(struct rtscam_video_buffer *rbuf,
			unsigned long delay)
{
	struct delayed_work *dwork = &rbuf->dwork;

	INIT_DELAYED_WORK(dwork, rtscam_buffer_wq_handle);

	rtscam_set_buffer_state(rbuf, RTS_BUF_STATE_DELAYED);

	schedule_delayed_work(dwork, delay * HZ / 1000);
}

static void rtscam_clr_delayed_buffer(struct rtscam_video_stream *stream)
{
	int i;
	struct rtscam_video_buffer *buffer;

	if (!stream)
		return;

	for (i = 0; i < stream->vb2_vidp.num_buffers; i++) {
		buffer = rtscam_get_video_buffer(stream, i);
		if (!buffer)
			continue;

		if (buffer->state == RTS_BUF_STATE_DELAYED) {
			cancel_delayed_work_sync(&buffer->dwork);
			rtscam_set_buffer_state(buffer, RTS_BUF_STATE_IDLE);
		}

	}
}
*/

static int TTFF_log_once = 0;
//static int buf_done[5][3] = {0};
//static int buf_release[5][3] = {0};
void rtscam_buffer_done(struct rtscam_video_stream *stream,
			struct rtscam_video_buffer *rbuf,
			unsigned long frameid)
{
	//struct rtscam_video_format *format;
	//uint64_t ts;
	//int more_valid_frame_flag = FALSE;
	//int ret;
	//u32 t1 =0, t2=0;

	volatile u32 reg_value;

#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM

	isp2enc_t i2e = {0};
	//BaseType_t xHigherPriorityTaskWoken;

#endif
	int valid_slot_send = frameid;
	//if (!stream || !rbuf)
	if (!stream )
		return;



	//xSemaphoreTake(stream->queue_lock , portMAX_DELAY);
	//printf("rtscam_buffer_done %d  %d %d \n",stream->streamid, valid_slot_send, stream->bufs[valid_slot_send].state);
#if defined (CONFIG_VERIFY_ISP_SDK) && CONFIG_VERIFY_ISP_SDK
	if (stream->bufs[valid_slot_send].state != RTS_BUF_STATE_DONE && stream->bufs[valid_slot_send].state != RTS_BUF_STATE_DEQUEUED ) {
#else
	if (stream->bufs[valid_slot_send].state != RTS_BUF_STATE_DONE /*&& stream->bufs[valid_slot_send].state != RTS_BUF_STATE_DEQUEUED*/ ) {
#endif
	rtscam_soc_inc_frames(stream);
	//rtscam_get_timestamp(&ts);
		//} else {


	//rtscam_get_timestamp(&ts);

			//printf("stream %d state %d buf %d done \r\n", stream->streamid, stream->bufs[valid_slot_send].state, valid_slot_send);
			stream->bufs[valid_slot_send].state = RTS_BUF_STATE_DONE;
			stream->buf_done[valid_slot_send]++;


#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM // Run on KM
			QueueHandle_t isp_send_queue = 0x0;
			TickType_t delay_time = 0x0;

			if (!TTFF_log_once) {
				send_isp_time = hal_read_curtime_us();
				TTFF_log_once = 1;
				log_time[8] = send_isp_time;
			}

			if(stream->sync == 0) { // Normal mode
				isp_send_queue = isp2osd_queue;
				delay_time = portMAX_DELAY;
			}
			else {					// TM Sync mode
				isp_send_queue = isp2tm_queue;
				delay_time = 0;
			}

			if (isp_send_queue) {
				i2e.ch = stream->streamid;
				i2e.slot = valid_slot_send;
				i2e.time_stamp = hal_read_curtime_us()/1000;
				i2e.frame_cnt = stream->frame_count;

				if (xQueueSend(isp_send_queue, &i2e, delay_time) != pdPASS) {
					printf("%s Queue Full \n",(stream->sync==0)?"ISP2OSD":"ISP2TM");
				}
			}
			else {
				printf("Queue disable \n");
			}

#endif

		//}

	} else {
		if ( stream->buf_done[valid_slot_send] <= stream->buf_release[valid_slot_send] ) {
			printf("[WARN]stream %d slot %d done %d release %d STATE_DONE cnt mismatch, force release\n", stream->streamid, valid_slot_send, stream->buf_done[valid_slot_send], stream->buf_release[valid_slot_send], stream->bufs[valid_slot_send].state);
			rtscam_video_release_slot(stream, valid_slot_send);
			stream->bufs[valid_slot_send].state = RTS_BUF_STATE_READY;
			stream->buf_done[valid_slot_send] = 0;
			stream->buf_release[valid_slot_send] = 0;
		}
	}
//	}


	//xSemaphoreGive(stream->queue_lock);
	//rbuf->buf.vb2_buf.timestamp = ts;
	//rtsprintk(RTS_TRACE_PTS, "0x%08x\n", rbuf->pts);
	//vb2_set_plane_payload(&rbuf->buf.vb2_buf, 0, bytesused);

//	if (stream->delay)
//		rtscam_delay_buffer(rbuf, stream->delay);
//	else
	//	__rtscam_buffer_done(rbuf);
}
//EXPORT_SYMBOL_GPL(rtscam_buffer_done);

#define RTS_CAM_ALIGN(x, a)          (((x) + (a) - 1) & (~((a) - 1)))

static int rtscam_queue_setup(struct vb2_queue *q,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[]/*, struct device *alloc_devs[]*/)
{
	struct rtscam_video_stream *stream = vb2_get_drv_priv(q);
	struct rtscam_video_format *format = NULL;
	u32 pixelformat;
	u32 height;

	pixelformat = stream->user_format;

	format = find_format_by_fourcc(stream, pixelformat);
	if (!format)
		return -EINVAL;

	//sizes[0] = ((stream->user_width * format->bpp) >> 3) *
	//		stream->user_height;
	height = stream->user_height;

	/*Align stream->user_height by 16 for jpu*/
	if (stream->user_height_align) {
		if (pixelformat == V4L2_PIX_FMT_NV12 ||
				pixelformat == V4L2_PIX_FMT_NV16)
			height = RTS_CAM_ALIGN(stream->user_height,
					stream->user_height_align);
	}

	sizes[0] = ((stream->user_width * format->bpp) >> 3) * height;

	if (sizes[0] == 0) {
		rtsprintk(RTS_TRACE_ERROR, "frame buf size is 0\n");
		return -EINVAL;
	}

//	alloc_devs[0] = stream->icd->dev;

	if (!(*num_buffers))
		*num_buffers = 2;

	if (*num_buffers > RTSCAM_MAX_BUFFER_NUM)
		*num_buffers = RTSCAM_MAX_BUFFER_NUM;

	*num_planes = 1;

	return 0;
}

static int rtscam_buf_init(struct vb2_buffer *vb)
{
	struct rtscam_video_buffer *buf = to_rtscam_vbuf(vb);

	rtscam_set_buffer_state(buf, RTS_BUF_STATE_IDLE);

	return 0;
}

static int rtscam_buf_prepare(struct vb2_buffer *vb)
{
	struct rtscam_video_buffer *buf = to_rtscam_vbuf(vb);

	rtscam_set_buffer_state(buf, RTS_BUF_STATE_QUEUED);

	return 0;
}

static void rtscam_buf_finish(struct vb2_buffer *vb)
{
	struct rtscam_video_buffer *buf = to_rtscam_vbuf(vb);

	rtscam_set_buffer_state(buf, RTS_BUF_STATE_DEQUEUED);
}

static void rtscam_buf_cleanup(struct vb2_buffer *vb)
{
}

static int rtscam_buf_start_streaming(struct vb2_queue *q, unsigned int count)
{
	return 0;
}

static void rtscam_buf_stop_streaming(struct vb2_queue *q)
{
	struct rtscam_video_stream *stream = vb2_get_drv_priv(q);

//	rtscam_clr_delayed_buffer(stream);
	if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock_irq(&stream->lock);
		isp_error("rtscam_buf_stop_streaming wait stream->lock timeout\n\r");
		return;
	}
	rtscam_clr_ready_buffer(stream);
	rtscam_return_buffers(stream);
	xSemaphoreGive(stream->lock);  //	spin_unlock_irq(&stream->lock);

}

static void rtscam_buf_wait_prepare(struct vb2_queue *q)
{
	/*unlock*/
	struct rtscam_video_stream *stream = vb2_get_drv_priv(q);
	xSemaphoreGive(stream->queue_lock);
}

static void rtscam_buf_wait_finish(struct vb2_queue *q)
{
	/*lock*/
	struct rtscam_video_stream *stream = vb2_get_drv_priv(q);
	if (xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_buf_wait_finish wait stream->queue_lock timeout\n\r");
	}
}

static void rtscam_buf_queue(struct vb2_buffer *vb)
{
#if defined (CONFIG_VERIFY_ISP_SDK) && CONFIG_VERIFY_ISP_SDK
	struct rtscam_video_stream *stream = vb2_get_drv_priv(vb->vb2_queue);
	struct rtscam_video_buffer *buf = to_rtscam_vbuf(vb);

	if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock_irq(&stream->lock);
		isp_error("rtscam_buf_queue wait stream->lock timeout\n\r");
		return;
	}
	rtscam_submit_buffer(stream, buf);
	xSemaphoreGive(stream->lock);  //	spin_unlock_irq(&stream->lock);
#endif
	printf("disable this API for buffer simplification \r\n");

}

static struct vb2_ops rtscam_vb2_ops = {
	.queue_setup = rtscam_queue_setup,
	.wait_prepare = rtscam_buf_wait_prepare,
	.wait_finish = rtscam_buf_wait_finish,
	.buf_init = rtscam_buf_init,
	.buf_prepare = rtscam_buf_prepare,
	.buf_finish = rtscam_buf_finish,
	.buf_cleanup = rtscam_buf_cleanup,
	.start_streaming = rtscam_buf_start_streaming,
	.stop_streaming = rtscam_buf_stop_streaming,
	.buf_queue = rtscam_buf_queue,
};

static int rtscam_video_init_videobuf2(struct vb2_queue *queue,
				       struct rtscam_video_stream *stream)
{
	struct rtscam_video_device *icd = stream->icd;

	queue->type = icd->type;
	queue->io_modes = VB2_MMAP | VB2_USERPTR;
	queue->drv_priv = stream;
	queue->ops = &rtscam_vb2_ops;
	queue->mem_ops = icd->mem_ops;
	queue->buf_struct_size = sizeof(struct rtscam_video_buffer);
	queue->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;


	INIT_LIST_HEAD(&stream->capture);

	return 0;
}

static void rtscam_video_release_videobuf2(struct vb2_queue *queue,
					   struct rtscam_video_stream *stream)
{
	if (xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_video_release_videobuf2 wait stream->queue_lock timeout\n\r");
		return;
	}
	//vb2_queue_release(queue);
	xSemaphoreGive(stream->queue_lock);
}

static int rtscam_video_alloc_buffers(struct rtscam_video_stream *stream,
				      int fd,
				      struct v4l2_requestbuffers *p)
{
	int ret = 0;

	ret = xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_video_alloc_buffers wait stream->queue_lock timeout\n\r");
		return -ETIMEDOUT;
	}
	//ret = vb2_reqbufs(&stream->vb2_vidp, p);
	rtscam_init_capture_buffer(stream);

	xSemaphoreGive(stream->queue_lock);

	return ret;
}

static void rtscam_video_free_buffers(struct rtscam_video_stream *stream)
{
	if (xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_video_free_buffers wait stream->queue_lock\n\r");
		return;
	}
	//vb2_queue_release(&stream->vb2_vidp);
	xSemaphoreGive(stream->queue_lock);
}

static int rtscam_video_query_buffer(struct rtscam_video_stream *stream,
				     struct v4l2_buffer *buf)
{
	int ret = 0;

	ret = xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_video_query_buffer wait stream->queue_lock timeout\n\r");
		return -ETIMEDOUT;
	}
	//ret = vb2_querybuf(&stream->vb2_vidp, buf);
	xSemaphoreGive(stream->queue_lock);

	return ret;
}

static int rtscam_video_release_slot(struct rtscam_video_stream *stream, int release_slot)
{
	//u32 reg_addr;
	//u32 reg_index;
	u32 reg_status;
	volatile u32 status;
	volatile u32 check_status;

	if (!stream)
		return -EINVAL;
	//isp_info("%s addr 0x%08x nr %d \r\n",__FUNCTION__, phy_addr, nr);
	if (rtscam_soc_is_yuv(stream->rts_code)) {
		reg_status = RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE + stream->streamid * 4;
		status = 0xc << (4 * release_slot);
		check_status = HAL_READ32(ISP_BASE + VIDEOIN_REG_BASE, reg_status);
		if ( (check_status&(0x8 <<(4 * release_slot))) != 0 ) {
			if ( stream->buf_release[release_slot] < stream->buf_done[release_slot] ) {
				stream->buf_release[release_slot]++;
			} else {
				printf("[WARN]release s%d slot%d cnt mismatch done %d release %d \r\n", stream->streamid, release_slot, stream->buf_done[release_slot], stream->buf_release[release_slot]);
			}
		} else {
			printf("[WARN]useless release s%d slot%d status 0x%08x \r\n", stream->streamid, release_slot, check_status);
		}

	} else if (rtscam_soc_is_rgb(stream->rts_code) || rtscam_soc_is_yonly(stream->rts_code) ) {
		reg_status = RTS_REG_RGB_YONLY_FRAME_BUFFER_STATUS;
		status = 0x18 << (8 * release_slot);
		check_status = HAL_READ32(ISP_BASE + VIDEOIN_REG_BASE, reg_status);
		if ( (check_status&(0x10 << (8 * release_slot))) != 0 ) {
			if ( stream->buf_release[release_slot] < stream->buf_done[release_slot] ) {
				stream->buf_release[release_slot]++;
			} else {
				printf("[WARN]release s%d slot%d cnt mismatch done %d release %d \r\n", stream->streamid, release_slot, stream->buf_done[release_slot], stream->buf_release[release_slot]);
			}
		} else {
			printf("[WARN]useless release s%d slot%d status 0x%08x \r\n", stream->streamid, release_slot, check_status);
		}
	} else {
		isp_error("%s invalid stream format (%ld)\r\n", __func__, stream->rts_code);
		return -EINVAL;
	}
	HAL_WRITE32(ISP_BASE + VIDEOIN_REG_BASE, reg_status, status);
	//status = HAL_READ32(ISP_BASE + VIDEOIN_REG_BASE, reg_status);
	//printf("clear frame status, reg = 0x%08x, release %d value = 0x%08x\n", reg_status, release_slot, status);
	return 0;
}


static int rtscam_video_queue_buffer(struct rtscam_video_stream *stream,
				     uint32_t *buf)
{
	int ret = 0;
	uint32_t buf_addr;
	int free_target_id = -1;

	if (!buf)
		return -EINVAL;
	//isp_info("%s xSemaphoreTake stream->lock \r\n", __FUNCTION__);

	ret = xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_video_queue_buffer wait stream->lock timeout\n\r");
		xSemaphoreGive(stream->lock);
		return -ETIMEDOUT;
	}

	if (*buf < 4) {
		free_target_id = *buf;
		printf("release s%d isp buffer %d \n", stream->streamid, *buf);
	} else {

		for (int i=0; i<stream->hw_slot_num; i++ ) {
			buf_addr = stream->bufs[i].buf_addr ;
			if ( buf_addr == *buf ) {
				free_target_id = i;
				break;
			}
		}
	}
	if ( free_target_id < 0 ) {
		isp_error("%s release buf didn't match isp buff pool 0x%08x \r\n", __func__, (int)*buf);
		xSemaphoreGive(stream->lock);
		return -1;
	}
	if ( stream->bufs[free_target_id].state != RTS_BUF_STATE_DONE && *buf > 3 ) {
#if 1
		printf("[WARN]stream %d release buf %d 0x%08x wasn't STATE_DONE stream dn %d rls %d voe dn %d %d rel %d %d \r\n", stream->streamid, free_target_id, *buf,
				stream->buf_done[free_target_id], stream->buf_release[free_target_id], buf_done[stream->streamid][0],buf_done[stream->streamid][1], buf_release[stream->streamid][0], buf_release[stream->streamid][1]);
#endif
		//return -1;
	}
	//isp_info("%s stream %d state %d buf %d release \r\n", __FUNCTION__, stream->streamid, stream->bufs[free_target_id].state, free_target_id);
	rtscam_video_release_slot(stream, free_target_id);

	stream->bufs[free_target_id].state = RTS_BUF_STATE_READY;

	////isp_info("%s done \r\n", __func__);

#if 0
	if (buffer->state == RTS_BUF_STATE_QUEUED)
		ret = 0;
	else
		ret = vb2_qbuf(&stream->vb2_vidp, buf);
#endif
	xSemaphoreGive(stream->lock);

	return ret;
}





static int rtscam_video_dequeue_buffer(struct rtscam_video_stream *stream,
				      uint32_t *buf, int nonblocking)
{
	int ret = 0;
	//int state;
#if defined (CONFIG_VERIFY_ISP_SDK) && CONFIG_VERIFY_ISP_SDK
	int latest_done_buf;

	if (! stream->stream_frame_done) {
		isp_warning("%s Null stream->stream_frame_done\r\n", __func__);
		return -1;
	}
	if (xQueueReceive(stream->stream_frame_done, &latest_done_buf, portMAX_DELAY) == pdFALSE) {
		rtsprintk(RTS_TRACE_ERROR, "urb queue recv failed\n");
		return -1;
	} else {
		/*
		 * Only remove the buffer from done_list if all planes can be
		 * handled. Some cases such as V4L2 file I/O and DVB have pb
		 * == NULL; skip the check then as there's nothing to verify.
		 */
		ret = xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("rtscam_video_dequeue_buffer wait stream->queue_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		//state = stream->bufs[latest_done_buf].state;
		//if (  state != RTS_BUF_STATE_DONE ) {
		//	isp_warning("%s error buffer status stream %d buf %d %d state %d\r\n", __func__, stream->streamid, stream->latest_done_buf, latest_done_buf, state);
		//}

		*buf = stream->bufs[latest_done_buf].buf_addr;
		stream->bufs[latest_done_buf].state = RTS_BUF_STATE_DEQUEUED;
		//isp_info("%s done s%d f%d 0x%08x\r\n", __func__, stream->streamid, latest_done_buf, buf->memory);
		xSemaphoreGive(stream->queue_lock);
#if 0
		if (pb) {
			xSemaphoreTake(q->done_lock, portMAX_DELAY);
			ret = call_bufop(q, verify_planes_array, *vb, pb);
//			if (!ret)
//				list_del(&(*vb)->done_entry);
			xSemaphoreGive(q->done_lock);
		}
#endif
	}


	//ret = vb2_dqbuf(&stream->vb2_vidp, buf, nonblocking);
	////isp_info("%s done \r\n", __func__);

#endif
	printf("%s remove this APIs \r\n", __func__);
	return ret;
}

/*
static int rtscam_video_queue_mmap(struct rtscam_video_stream *stream,
				   void *vma)
{
	int ret=0;

	xSemaphoreTake(stream->queue_lock, portMAX_DELAY);
	//ret = vb2_mmap(&stream->vb2_vidp, vma);
	stream->vb2_vidp = vma;
	xSemaphoreGive(stream->queue_lock);

	return ret;
}

static int rtscam_video_queue_poll(struct rtscam_video_stream *stream)
{
	int ret;

	xSemaphoreTake(stream->queue_lock, portMAX_DELAY);
	ret = vb2_poll(&stream->vb2_vidp);  //wait vb2_buffer_done
	xSemaphoreGive(stream->queue_lock);

	return ret;
}
*/

static int rtscam_video_queue_allocated(struct rtscam_video_stream *stream)
{
	int allocated = 0;

	if (xSemaphoreTake(stream->queue_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_video_queue_allocated wait stream->queue_lock timeout\n\r");
		return allocated;
	}
	allocated = vb2_is_busy(&stream->vb2_vidp);
	xSemaphoreGive(stream->queue_lock);

	return allocated;
}
// setup the stream on flag used for fps opeation process
#if 1

static int vb2_streamon_pro2(struct vb2_queue *q)
{
	int ret;

	if (q->streaming) {
		printf("already streaming\n");
		return 0;
	}

	q->streaming = 1;

	//printf("%s successful\n", __func__);
	return 0;
}



static int vb2_streamoff_pro2(struct vb2_queue *q)
{

	q->streaming = 0;

	//printf("%s successful\n", __func__);
	return 0;
}












static int rtscam_video_queue_enable(struct rtscam_video_stream *stream,
				     int enable)
{
	int ret;

	xSemaphoreTake(stream->queue_lock, portMAX_DELAY);
	if (enable) {
		ret = vb2_streamon_pro2(&stream->vb2_vidp);
		if (ret < 0)
			goto done;
	} else {
		ret = vb2_streamoff_pro2(&stream->vb2_vidp);
		if (ret < 0)
			goto done;
	}

done:
	xSemaphoreGive(stream->queue_lock);

	return ret;
}
#endif
static int rtscam_video_querycap(struct rtscam_video_stream *stream,
				 struct v4l2_capability *cap)
{
	strlcpy((char*)cap->driver, stream->icd->drv_name, sizeof(cap->driver));
	if (stream->icd->dev_name)
		strlcpy((char*)cap->card, stream->icd->dev_name, sizeof(cap->card));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;

	return 0;
}

static int rtscam_video_enum_fmt(struct rtscam_video_stream *stream,
				 struct v4l2_fmtdesc *f)
{
	struct rtscam_video_format *format;
	uint32_t index = 0;

	if (f->type != stream->icd->type) {
		isp_error("%s f->type %ld stream->icd->type %d \r\n", __FUNCTION__, f->type, stream->icd->type);
		return -EINVAL;
	}


//f->index is u32 & never <0
//	if (f->index < 0)
//		f->index = 0;

	format = stream->user_formats;
	index = 0;

	while (format) {
		if (index == f->index)
			break;
		format = format->next;
		index++;
	}

	if (!format)
		return ERR_ID_DRV_VIDEO_INVALID_FMT;

	strlcpy((char*)f->description, format->name, sizeof(f->description));
	f->pixelformat = format->fourcc;

	return 0;
}

static int rtscam_video_try_fmt(struct rtscam_video_stream *stream,
				struct v4l2_format *f)
{
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	if (f->type != stream->icd->type)
		return -EINVAL;

	ret = rtscam_try_user_format(stream, pix->pixelformat,
				     pix->width, pix->height);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR,
			  "format (%ld) (%ld x %ld) unsupportted\n",
			  pix->pixelformat,
			  pix->width, pix->height);
		return ret;
	}

	return 0;
}

static int rtscam_video_set_selection(struct rtscam_video_stream *stream,
			struct v4l2_selection *selection)
{
	return  rtscam_call_video_op(stream->icd,
			set_selection, stream, selection);
}

static int rtscam_video_get_selection(struct rtscam_video_stream *stream,
			struct v4l2_selection *selection, int user)
{
	return  rtscam_call_video_op(stream->icd,
			get_selection, stream, selection, user);
}

static int rtscam_check_fmt_by_crop_info(struct rtscam_video_stream *stream,
			u32 width, u32 height)
{
	struct v4l2_selection selection;
	int ret;

	ret = rtscam_video_get_selection(stream, &selection, 1);
	if (ret) {
		if (ret == -EPERM)
			return 0;

		rtsprintk(RTS_TRACE_ERROR, "get selection setting fail\n");
		return ret;
	}

	if (selection.r.width != 0 && selection.r.height != 0) {
		if (!stream->streamid) {
			if (width >= 2 * selection.r.width ||
					height >= 2 * selection.r.height)
				ret = ERR_ID_DRV_ZOOM_SCALE_UP_OUT_RANGE;

		} else {
			if (width > selection.r.width || height > selection.r.height)
				ret = ERR_ID_DRV_ZOOM_SCALE_UP_OUT_RANGE;
		}
	}

	if (ret)
		rtsprintk(RTS_TRACE_ERROR,
			"invalid resolution(%ldx%ld) for crop setting(%ldx%ld)\n",
			width, height, selection.r.width, selection.r.height);
	return ret;
}

static int rtscam_check_crop_info_by_fmt(struct rtscam_video_stream *stream,
				struct v4l2_selection *selection)
{
	int ret = 0;

	if (!stream->streamid) {
		if (stream->user_width >= 2 * selection->r.width ||
						stream->user_height >= 2 * selection->r.height)
				ret = -EINVAL;
	} else {
		if (stream->user_width > selection->r.width ||
						stream->user_height > selection->r.height)
 				ret = -EINVAL;
	}

	if (ret)
		isp_error("invalid crop setting(%dx%d) for resolution(%dx%d)\n",
		selection->r.width, selection->r.height,
		stream->user_width, stream->user_height);
	return ret;
}

static int rtscam_video_set_fmt(struct rtscam_video_stream *stream,
				struct v4l2_format *f)
{
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct rtscam_video_format *fmt;
	int ret;

	ret = rtscam_video_try_fmt(stream, f);
	if (ret)
		return ret;

	if (rtscam_video_queue_allocated(stream)) {
		ret = -EBUSY;
		goto done;
	}

	if (vb2_is_streaming(&stream->vb2_vidp)) {
		ret = -EBUSY;
		goto done;
	}

	ret = rtscam_check_fmt_by_crop_info(stream, pix->width, pix->height);
	if (ret)
		goto done;

	fmt = find_format_by_fourcc(stream, pix->pixelformat);
	if (fmt == NULL) {
		ret = -ENOTSUP;
		goto done;
	}

	ret = rtscam_set_user_format(stream, pix->pixelformat,
				     pix->width, pix->height);
	if (ret)
		goto done;

	pix->field = fmt->field;
	pix->bytesperline = stream->bytesperline;
	pix->sizeimage = stream->sizeimage;

done:
	return ret;
}

static int rtscam_video_get_fmt(struct rtscam_video_stream *stream,
				struct v4l2_format *f)
{
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct rtscam_video_format *fmt;

	if (f->type != stream->icd->type)
		return -EINVAL;

	fmt = find_format_by_fourcc(stream, stream->user_format);
	if (!fmt)
		return ERR_ID_DRV_VIDEO_INVALID_FMT;

	pix->pixelformat = stream->user_format;
	pix->width = stream->user_width;
	pix->height = stream->user_height;
	pix->bytesperline = stream->bytesperline;
	pix->sizeimage = stream->sizeimage;
	pix->field = fmt->field;
	pix->colorspace = fmt->colorspace;

	return 0;
}

static int rtscam_video_enum_framesizes(struct rtscam_video_stream *stream,
					struct v4l2_frmsizeenum *fsize)
{
	struct rtscam_video_format *format = NULL;

	format = find_format_by_fourcc(stream, fsize->pixel_format);
	if (!format || !format->initialized)
		return -EINVAL;

	if (RTSCAM_SIZE_DISCRETE == format->frame_type) {
		struct rtscam_video_frame *frame = format->discrete.frames;
		uint32_t index = 0;

		while (frame) {
			if (fsize->index == index)
				break;
			frame = frame->next;
			index++;
		}
		if (!frame)
			return ERR_ID_DRV_VIDEO_INVALID_FRAME_SIZE;

		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = frame->size.width;
		fsize->discrete.height = frame->size.height;
	} else {
		if (fsize->index)
			return ERR_ID_DRV_VIDEO_INVALID_FRAME_SIZE;

		fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
		fsize->stepwise.max_width = format->stepwise.max.width;
		fsize->stepwise.max_height = format->stepwise.max.height;
		fsize->stepwise.min_width = format->stepwise.min.width;
		fsize->stepwise.min_height = format->stepwise.min.height;
		fsize->stepwise.step_width = format->stepwise.step.width;
		fsize->stepwise.step_height = format->stepwise.step.height;
	}

	return 0;
}

static int rtscam_video_enum_frameintervals(struct rtscam_video_stream *stream,
					    struct v4l2_frmivalenum *fival)
{
	struct rtscam_video_frmival *frmival = NULL;

	frmival = rtscam_get_video_frmival(stream, fival->pixel_format,
					   fival->width, fival->height);
	if (!frmival || !frmival->initialized)
		return -EINVAL;

	if (RTSCAM_SIZE_DISCRETE == frmival->frmival_type) {
		struct rtscam_frame_frmival *ival = frmival->discrete.frmivals;
		uint32_t index = 0;

		while (ival) {
			if (fival->index == index)
				break;
			ival = ival->next;
			index++;
		}
		if (!ival)
			return ERR_ID_DRV_VIDEO_INVALID_FPS;

		fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
		fival->discrete.numerator = ival->frmival.numerator;
		fival->discrete.denominator = ival->frmival.denominator;
	} else {
		if (fival->index)
			return ERR_ID_DRV_VIDEO_INVALID_FPS;

		fival->type = V4L2_FRMIVAL_TYPE_STEPWISE;
		fival->stepwise.max = frmival->stepwise.max;
		fival->stepwise.min = frmival->stepwise.min;
		fival->stepwise.step = frmival->stepwise.step;
	}

	return 0;
}

static int rtscam_video_get_parm(struct rtscam_video_stream *stream,
				 struct v4l2_streamparm *parm)
{
	if (parm->type != stream->icd->type)
		return -EINVAL;

	parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.capturemode = 0;

	if (vb2_is_streaming(&stream->vb2_vidp)) {
		parm->parm.capture.timeperframe.numerator =
				stream->fps.user_actual.numerator;
		parm->parm.capture.timeperframe.denominator =
				stream->fps.user_actual.denominator;
	} else {
		parm->parm.capture.timeperframe.numerator =
				stream->fps.user_setting.numerator;
		parm->parm.capture.timeperframe.denominator =
				stream->fps.user_setting.denominator;
	}
	if (stream->fps.skip_info.flag == 0 ) {
		parm->parm.capture.skip_m = stream->fps.skip_info.m;
		parm->parm.capture.skip_n = stream->fps.skip_info.n;
	} else {
		parm->parm.capture.skip_m = stream->fps.skip_info.m;
		parm->parm.capture.skip_n = stream->fps.skip_info.m - stream->fps.skip_info.n;
	}


	parm->parm.capture.extendedmode = 0;
	parm->parm.capture.readbuffers = 0;

	return 0;
}

static int rtscam_video_enum_input(struct rtscam_video_stream *stream,
				   struct v4l2_input *input)
{
	if (input->index)
		return -EINVAL;

	input->type = V4L2_INPUT_TYPE_CAMERA;
	strcpy((char*)input->name, "Camera");

	return 0;
}

static int rtscam_video_get_input(struct rtscam_video_stream *stream,
				  unsigned int *i)
{
	*i = 0;

	return 0;
}

static int rtscam_video_set_input(struct rtscam_video_stream *stream,
				  unsigned int i)
{
	if (i)
		return -EINVAL;

	return 0;
}

static int rtscam_video_set_parm(struct rtscam_video_stream *stream,
				 struct v4l2_streamparm *parm)
{
	u32 numerator = parm->parm.capture.timeperframe.numerator;
	u32 denominator = parm->parm.capture.timeperframe.denominator;

	if (parm->type != stream->icd->type)
		return -EINVAL;

	return rtscam_set_user_frmival(stream, numerator, denominator);
}

static int rtscam_video_enable(struct rtscam_video_stream *stream, int enable)
{
	int ret = 0;

	if (enable) {
		isp_info("%s 0x%08x enable\r\n", __func__, stream);
		if (vb2_is_streaming(&stream->vb2_vidp)) {
			isp_error("%s vb2_is_streaming \n", __func__);
			return -EINVAL;
		}

		//if (!rtscam_video_queue_allocated(stream))
		//	return -EINVAL;
		stream->is_streaming = 1;

		ret = rtscam_video_queue_enable(stream, 1);  // setup the flag mainly for fps operation flow
		if (ret) {
			isp_error("%s rtscam_video_queue_enable err %d \n", __func__, ret);
			return ret;
		}

		ret = rtscam_call_video_op(stream->icd, s_stream, stream, 1);
		if (ret)
			rtscam_video_queue_enable(stream, 0);
		else
			stream->icd->streaming_count++;
	} else {
		if (!vb2_is_streaming(&stream->vb2_vidp)) {
			printf("%s vb2_isn't_streaming \n", __func__);
			return 0;
		}
		stream->is_streaming = 0;

		ret = rtscam_call_video_op(stream->icd, s_stream, stream, 0);
		if (!ret)
			ret = rtscam_video_queue_enable(stream, 0); // setup the flag mainly for fps operation flow

		if (!ret)
			stream->icd->streaming_count--;
	}

	return ret;
}

static int rtscam_acquire_privileges(struct rtscam_video_stream *stream)
{
	//if (vb2_is_streaming(&stream->vb2_vidp))
	//	return -EBUSY;

	if (RTSCAM_STATE_ACTIVE == stream->state)
		return 0;

	if (atomic_inc_return_isp(&stream->active) != 1) {
		atomic_dec_isp(&stream->active);
		return -EBUSY;
	}

	stream->state = RTSCAM_STATE_ACTIVE;
	return 0;
}

static void rtscam_dismiss_privileges(struct rtscam_video_stream *stream)
{
	if (stream->state == RTSCAM_STATE_ACTIVE)
		atomic_dec_isp(&stream->active);

	stream->state = RTSCAM_STATE_PASSIVE;
}

static int rtscam_has_privileges(struct rtscam_video_stream *stream)
{
	return stream->state == RTSCAM_STATE_ACTIVE;
}

static int rtscam_video_open(int fd)
{
//	struct video_device *vdev = video_devdata(file);
	struct rtscam_video_stream *stream;
	struct rtscam_video_device *icd;
//	struct rtscam_fh *handle = NULL;
	int ret;

//	if (!vdev || !video_is_registered(vdev))
//		return -ENODEV;

//	stream = video_get_drvdata(vdev);
	stream = get_stream(fd);
	if (stream == NULL)
		return -EINVAL;

	icd = stream->icd;

	if (!icd || !icd->ops)
		return -EINVAL;

//	handle = kzalloc(sizeof(*handle), GFP_KERNEL);
//	if (NULL == handle)
//		return -ENOMEM;

//	ret = try_module_get(icd->ops->owner) ? 0 : -ENODEV;
//
//	if (ret < 0) {
//		rtsprintk(RTS_TRACE_ERROR,
//			  "couldn't lock capture driver\n");
//		return ret;
//	}

//	if (mutex_lock_interruptible(&icd->dev_lock)) {
//		ret = -ERESTARTSYS;
//		goto elockdev;
//	}
	ret = xSemaphoreTake(icd->dev_lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_video_open wait icd->dev_lock timeout\n\r");
		return -ETIMEDOUT;
	}

	if (atomic_inc_return_isp(&icd->use_count) == 1) {
		ret = rtscam_call_video_op(icd, start_clock, icd);
		if (ret < 0) {
			rtsprintk(RTS_TRACE_ERROR,
				  "couldn't activate the camera:%d\n",
				  ret);
			atomic_dec_isp(&icd->use_count);
			goto estartclock;
		}
	}

	xSemaphoreGive(icd->dev_lock);

//	v4l2_fh_init(&handle->vfh, stream->vdev);
//	v4l2_fh_add(&handle->vfh);
//	handle->stream = stream;
	stream->state = RTSCAM_STATE_PASSIVE;
//	file->private_data = handle;

	return 0;

estartclock:
	xSemaphoreGive(icd->dev_lock);
//elockdev:
//	module_put(icd->ops->owner);
	return ret;
}

static int rtscam_video_close(int fd)
{
//	struct video_device *vdev = video_devdata(file);
	struct rtscam_video_stream *stream;
	struct rtscam_video_device *icd;
//	struct rtscam_fh *handle = file->private_data;
	int ret = 0;

//	stream = video_get_drvdata(vdev);
	stream = get_stream(fd);
	if (stream == NULL)
		return -EINVAL;

	icd = stream->icd;

	if (rtscam_has_privileges(stream)) {
		/*stop streaming*/
		ret = xSemaphoreTake(icd->dev_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("rtscam_video_close wait icd->dev_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("rtscam_video_close wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		rtscam_video_enable(stream, 0);
		xSemaphoreGive(stream->stream_lock);
		xSemaphoreGive(icd->dev_lock);

		/*release buffer*/
		rtscam_video_free_buffers(stream);
	}

	rtscam_dismiss_privileges(stream);
//	v4l2_fh_del(&handle->vfh);
//	v4l2_fh_exit(&handle->vfh);
//	kfree(handle);
//	file->private_data = NULL;

	ret = xSemaphoreTake(icd->dev_lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_video_close wait icd->dev_lock timeout\n\r");
		return -ETIMEDOUT;
	}

	if (atomic_dec_return_isp(&icd->use_count) == 0)
		rtscam_call_video_op(icd, stop_clock, icd);
	xSemaphoreGive(icd->dev_lock);
//	module_put(icd->ops->owner);

	return 0;
}

/*
long rtscam_video_do_ctrl_ioctl(struct rtscam_video_device *icd,
				unsigned int cmd, void *arg)
{
	long ret = 0;

	if (!icd)
		return -EINVAL;

	switch (cmd) {
	case VIDIOC_QUERYCTRL:
		ret = rtscam_query_v4l2_ctrl(icd, arg);
		break;
	case VIDIOC_G_CTRL:
		ret = rtscam_get_ctrl(icd, arg);
		break;
	case VIDIOC_S_CTRL:
		ret = rtscam_set_ctrl(icd, arg);
		break;
	case VIDIOC_G_EXT_CTRLS:
		ret = rtscam_get_ext_ctrls(icd, arg);
		break;
	case VIDIOC_S_EXT_CTRLS:
		ret = rtscam_set_ext_ctrls(icd, arg);
		break;
	case VIDIOC_TRY_EXT_CTRLS:
		ret = rtscam_try_ext_ctrls(icd, arg);
		break;
	case RTSCAMIOC_VENDOR_CMD:
		xSemaphoreTake(icd->dev_lock, portMAX_DELAY);
		ret = rtscam_call_video_op(icd, exec_command,
					   icd->streams, arg);
		xSemaphoreGive(icd->dev_lock);
		break;
	case RTSCAMIOC_GET_PHYADDDR: {
		unsigned long vm_addr = *(unsigned long *)arg;
		unsigned long phy_addr = 0;

		ret = rtscam_convert_addr_from_vm_to_phy(icd,
							 vm_addr, &phy_addr);

		if (!ret)
			*(unsigned long *)arg = phy_addr;
		break;
	}
	default:
		rtsprintk(RTS_TRACE_ERROR,
			  "Unknown[ctrl] ioctl 0x%08x, type = '%c' nr = 0x%x\n",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_video_do_ctrl_ioctl);

static unsigned int rtscam_video_poll(int fd)
{
	struct rtscam_video_stream *stream;
	unsigned int err = POLLERR;

	stream = get_stream(fd);
	if (stream == NULL)
		return -EINVAL;

	xSemaphoreTake(stream->stream_lock, portMAX_DELAY);
	err = rtscam_video_queue_poll(stream);
	xSemaphoreGive(stream->stream_lock);

	return err;
}
*/

long rtscam_video_do_ioctl(int fd, unsigned int cmd, void *arg)
{
	struct rtscam_video_stream *stream;
	struct rtscam_video_device *icd;
//	struct rtscam_fh *handle = file->private_data;
	long ret = 0;

	stream = get_stream(fd);
	if (stream == NULL)
		return -EINVAL;

	icd = stream->icd;

	switch (cmd) {
	case VIDIOC_QUERYCAP:
		ret = rtscam_video_querycap(stream, arg);
		break;
//	case VIDIOC_G_PRIORITY:
//		*(u32 *)arg = v4l2_prio_max(stream->vdev->prio);
//		break;
//	case VIDIOC_S_PRIORITY:
//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;
//		ret = v4l2_prio_change(stream->vdev->prio, &handle->vfh.prio,
//				       *(u32 *)arg);
//		break;
	case VIDIOC_ENUM_FMT:
		ret = rtscam_video_enum_fmt(stream, arg);
		break;
	case VIDIOC_G_FMT:
		ret = rtscam_video_get_fmt(stream, arg);
		break;
	case VIDIOC_TRY_FMT:
		ret = rtscam_video_try_fmt(stream, arg);
		break;
	case VIDIOC_S_FMT:
//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_S_FMT wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		if (rtscam_video_queue_allocated(stream)) {
			xSemaphoreGive(stream->stream_lock);
			return -EBUSY;
		}
		ret = rtscam_acquire_privileges(stream);
		if (ret < 0) {
			xSemaphoreGive(stream->stream_lock);
			return ret;
		}

		ret = rtscam_video_set_fmt(stream, arg);
		if (ret)
			rtscam_dismiss_privileges(stream);
		xSemaphoreGive(stream->stream_lock);
		break;
	case VIDIOC_G_SELECTION:
		ret = rtscam_video_get_selection(stream, arg, 0);
		break;
	case VIDIOC_S_SELECTION:
//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_S_SELECTION wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		//if (vb2_is_streaming(&stream->vb2_vidp)) {
		if (stream->is_streaming) {
			ret = rtscam_check_crop_info_by_fmt(stream, arg);
			if (ret < 0) {
				xSemaphoreGive(stream->stream_lock);
				return ERR_ID_DRV_VIDEO_INVALID_CROP_SIZE;
			}
			((struct v4l2_selection *)arg)->type = 1;
			ret = rtscam_video_set_selection(stream, arg);
		} else {
			ret = rtscam_acquire_privileges(stream);
			if (ret < 0) {
				xSemaphoreGive(stream->stream_lock);
				return ret;
			}
			((struct v4l2_selection *)arg)->type = 0;
			ret = rtscam_video_set_selection(stream, arg);
			if (ret)
				rtscam_dismiss_privileges(stream);
		}

		xSemaphoreGive(stream->stream_lock);
		break;
	case VIDIOC_ENUM_FRAMESIZES:
		ret = rtscam_video_enum_framesizes(stream, arg);
		break;
	case VIDIOC_ENUM_FRAMEINTERVALS:
		ret = rtscam_video_enum_frameintervals(stream, arg);
		break;
	case VIDIOC_G_PARM:
		ret = rtscam_video_get_parm(stream, arg);
		break;
	case VIDIOC_S_PARM:
//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_S_PARM wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}

		if (stream->state != RTSCAM_STATE_ACTIVE) {
			if (atomic_inc_return_isp(&stream->active) != 1) {
				atomic_dec_isp(&stream->active);
				xSemaphoreGive(stream->stream_lock);
				return -EBUSY;
			}
			stream->state = RTSCAM_STATE_ACTIVE;
		}

		ret = rtscam_video_set_parm(stream, arg);
		if (ret)
			rtscam_dismiss_privileges(stream);
		xSemaphoreGive(stream->stream_lock);
		break;
	case VIDIOC_ENUMINPUT:
		ret = rtscam_video_enum_input(stream, arg);
		break;
	case VIDIOC_G_INPUT:
		ret = rtscam_video_get_input(stream, arg);
		break;
	case VIDIOC_S_INPUT:
//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_S_INPUT wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		ret = rtscam_acquire_privileges(stream);
		if (ret < 0) {
			xSemaphoreGive(stream->stream_lock);
			return ret;
		}

		ret = rtscam_video_set_input(stream, *(unsigned int *)arg);
		if (ret)
			rtscam_dismiss_privileges(stream);
		xSemaphoreGive(stream->stream_lock);
		break;
//	case VIDIOC_QUERYCTRL:
//	case VIDIOC_G_CTRL:
//	case VIDIOC_S_CTRL:
//	case VIDIOC_G_EXT_CTRLS:
//	case VIDIOC_S_EXT_CTRLS:
//	case VIDIOC_TRY_EXT_CTRLS:
//	case RTSCAMIOC_VENDOR_CMD:
//	case RTSCAMIOC_GET_PHYADDDR:
//		ret = rtscam_video_do_ctrl_ioctl(icd, cmd, arg);
//		break;
	case VIDIOC_REQBUFS: {
		struct v4l2_requestbuffers *p = arg;

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_REQBUFS wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		ret = rtscam_acquire_privileges(stream);
		if (ret < 0) {
			xSemaphoreGive(stream->stream_lock);
			isp_error("%s rtscam_acquire_privileges error %ld \r\n", __func__, ret);
			return ret;
		}

		ret = rtscam_video_alloc_buffers(stream, fd, p);

		stream->memory_owner = fd;

		xSemaphoreGive(stream->stream_lock);

		break;
	}
	case VIDIOC_QUERYBUF:
		if (!rtscam_has_privileges(stream))
			return -EBUSY;

		ret = rtscam_video_query_buffer(stream, arg);
		break;
	case VIDIOC_QBUF:
		if (!rtscam_has_privileges(stream))
			return -EBUSY;

		ret = rtscam_video_queue_buffer(stream, arg);
		break;
	case VIDIOC_DQBUF:
		if (!rtscam_has_privileges(stream))
			return -EBUSY;

		ret = rtscam_video_dequeue_buffer(stream, arg, stream->f_flags & O_NONBLOCK);
		break;
	case VIDIOC_STREAMON: {
		//int *type = arg;

		//if (*type != (int)stream->vb2_vidp.type)
		//	return -EINVAL;

//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;
		isp_info("%s VIDIOC_STREAMON\r\n", __func__);
		if (!rtscam_has_privileges(stream))
			return -EBUSY;

		ret = xSemaphoreTake(icd->dev_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_STREAMON wait icd->dev_lock timeout\n\r");
			return -ETIMEDOUT;
		}

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_STREAMON wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		ret = rtscam_video_enable(stream, 1);
		xSemaphoreGive(stream->stream_lock);

		xSemaphoreGive(icd->dev_lock);

		break;
	}
	case VIDIOC_STREAMOFF: {
		//int *type = arg;

		//if (*type != (int)stream->vb2_vidp.type)
		//	return -EINVAL;

//		ret = v4l2_prio_check(stream->vdev->prio, handle->vfh.prio);
//		if (ret < 0)
//			return ret;

		if (!rtscam_has_privileges(stream))
			return -EBUSY;

		ret = xSemaphoreTake(icd->dev_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_STREAMOFF wait icd->dev_lock timeout\n\r");
			return -ETIMEDOUT;
		}

		ret = xSemaphoreTake(stream->stream_lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("VIDIOC_STREAMOFF wait stream->stream_lock timeout\n\r");
			return -ETIMEDOUT;
		}
		ret = rtscam_video_enable(stream, 0);
		xSemaphoreGive(stream->stream_lock);

		xSemaphoreGive(icd->dev_lock);

		break;
	}
	case VIDIOC_ENUMSTD:
	case VIDIOC_QUERYSTD:
	case VIDIOC_G_STD:
	case VIDIOC_S_STD:
	case VIDIOC_OVERLAY:
	case VIDIOC_ENUMAUDIO:
	case VIDIOC_ENUMAUDOUT:
	case VIDIOC_ENUMOUTPUT:
	case VIDIOC_LOG_STATUS:
	case VIDIOC_SUBSCRIBE_EVENT:
	case VIDIOC_UNSUBSCRIBE_EVENT:
	case VIDIOC_CROPCAP:
	case VIDIOC_G_CROP:
	case VIDIOC_S_CROP:
		rtsprintk(RTS_TRACE_IOCTL,
			  "Unsupport [Analog video standards] ioctl 0x%08x\n",
			  cmd);
		ret = -ENOTTY;
		break;
//	case VIDIOC_POLL:
//		ret = rtscam_video_poll(fd);
//		break;
	default:
		rtsprintk(RTS_TRACE_ERROR,
			  "Unknown[video] ioctl 0x%08x, type = '%c' nr = 0x%x\n",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}
	rtsprintk(RTS_TRACE_DEBUG,
		  "[video] ioctl 0x%08x, type = '%c' nr = 0x%x (%d)\n",
		  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_NR(cmd));

	return ret;
}

static long rtscam_video_ioctl(int fd, unsigned int cmd,
			       unsigned long arg)
{
	return rtscam_video_do_ioctl(fd, cmd, (void*)arg);
}

/*
static int rtscam_video_mmap(int fd, void *vma)
{
	struct rtscam_video_stream *stream;
	int err;

	if (stream == NULL)
		return -EINVAL;

	if (fd != stream->memory_owner)
		return -EINVAL;

//	if (mutex_lock_interruptible(&stream->stream_lock))
//		return -ERESTARTSYS;
	xSemaphoreTake(stream->stream_lock, portMAX_DELAY);

	err = rtscam_video_queue_mmap(stream, vma);

//	mutex_unlock(&stream->stream_lock);
	xSemaphoreGive(stream->stream_lock);

	return err;
}
*/

static struct v4l2_file_operations rtscam_video_fops = {
	//.owner = THIS_MODULE,
	.open = rtscam_video_open,
	.release = rtscam_video_close,
	.unlocked_ioctl = rtscam_video_ioctl,
//	.mmap = rtscam_video_mmap,
//	.poll = rtscam_video_poll,
};


void video_device_release(struct video_device *vdev)
{
	rts_free(vdev);
}

static int video_dev_create(struct rtscam_video_stream *stream)
{
	struct video_device *vdev = rts_malloc(sizeof(struct video_device));
	int nr = stream->video_nr;
	int ret;

	if (!vdev)
		return -ENOMEM;

	ret = rtscam_check_stream_format(stream);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR,
			  "please init stream format first\n");
		return ret;
	}
	ret = rtscam_check_user_format(
			      stream, stream->user_format,
			      stream->user_width,
			      stream->user_height,
			      stream->fps.user_setting.numerator,
			      stream->fps.user_setting.denominator);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR,
			  "please init user format first\n");
		return ret;
	}

	strlcpy(vdev->name, stream->icd->drv_name, sizeof(vdev->name));

//	vdev->v4l2_dev = &stream->icd->v4l2_dev;
	vdev->fops = &rtscam_video_fops;
	vdev->release = video_device_release;
//	vdev->prio = &stream->prio;

//	video_set_drvdata(vdev, stream);

//	ret = video_register_device(vdev, VFL_TYPE_GRABBER, nr);
//	if (ret < 0) {
//		rtsprintk(RTS_TRACE_ERROR,
//			  "register video device %d fail, %d\n", nr, ret);
//		video_device_release(vdev);
//		return ret;
//	}

	ret = rtscam_video_init_videobuf2(&stream->vb2_vidp, stream);
	if (ret < 0) {
		rtsprintk(RTS_TRACE_ERROR,
			  "video device %d init vb2 fail, %d\n", nr, ret);
//		video_unregister_device(vdev);
		return ret;
	}

	stream->vdev = vdev;

	return 0;
}

static int rtscam_video_device_remove(struct rtscam_video_device *icd)
{
	int i;

	rtscam_video_release_ctrl(icd);

	for (i = 0; i < icd->streamnum; i++) {
		struct rtscam_video_stream *stream = icd->streams + i;
		if (!stream->vdev)
			continue;
		rtscam_video_release_videobuf2(&stream->vb2_vidp, stream);
//		video_unregister_device(stream->vdev);
		stream->vdev = NULL;
	}

	return 0;
}

static int rtscam_video_device_probe(struct rtscam_video_device *icd)
{
	int ret = 0;
	int i;
	int num = 0;

	rtsprintk(RTS_TRACE_VIDEO,
		  "Probing video dev\n");

	if (!icd->drv_name)
		return -EINVAL;

	/*init ctrls*/
	ret = rtscam_video_init_ctrl(icd);
	if (ret < 0) {
		rtsprintk(RTS_TRACE_ERROR, "Init ctrls fail\n");
		return ret;
	}

	if (0 == icd->streamnum) {
		rtscam_video_release_ctrl(icd);
		rtsprintk(RTS_TRACE_ERROR, "No stream found in icd\n");
		return -EINVAL;
	}

	for (i = 0; i < icd->streamnum; i++) {
		struct rtscam_video_stream *stream = icd->streams + i;

		if (stream->video_nr < 0 || stream->video_nr > 64)
			stream->video_nr = -1;

		stream->icd = icd;
		stream->vdev = NULL;
		stream->f_flags = O_NONBLOCK;
		stream->is_streaming = 0;

		//v4l2_prio_init(&stream->prio);

		atomic_set_isp(&stream->active, 0);
		atomic_set_isp(&stream->use_count, 0);

		ret = video_dev_create(stream);
		if (ret < 0)
			continue;
		num++;
	}
	if (0 == num) {
		ret = -EINVAL;
		goto error;
	}

	return 0;

error:
	rtscam_video_device_remove(icd);

	return ret;
}

int rtscam_video_register_device(struct rtscam_video_device *icd)
{
	int ret = 0;

	if (gbl_icd) {
		isp_error("%s: Error! Only support 1 video device\n", __func__);
		return -EINVAL;
	}

	if (!icd)
		return -EINVAL;

	if (!icd->mem_ops)
		return -EINVAL;

	if (!icd->initialized)
		return -EINVAL;

//	icd->v4l2_dev.dev = icd->dev;
//	ret = v4l2_device_register(icd->v4l2_dev.dev, &icd->v4l2_dev);
//	if (ret) {
//		rtsprintk(RTS_TRACE_ERROR,
//			  "%s:v4l2_device_register fail\n", __func__);
//		return ret;
//	}

	atomic_set_isp(&icd->use_count, 0);
	icd->streaming_count = 0;

	ret = rtscam_video_device_probe(icd);
	gbl_icd = ret ? NULL : icd;
	if (ret) {
		isp_error("video device <%s> probe fail : %d\n",icd->dev_name, ret);
//		v4l2_device_unregister(&icd->v4l2_dev);
	} else {
		isp_info("video device <%s> registered\r\n",icd->dev_name);
	}

	return ret;
}
//EXPORT_SYMBOL_GPL(rtscam_video_register_device);

int rtscam_video_unregister_device(struct rtscam_video_device *icd)
{
	rtscam_video_device_remove(icd);
	gbl_icd = NULL;

//	v4l2_device_unregister(&icd->v4l2_dev);

	return 0;
}
extern int iot_rtscam_soc_config_hw_slot_num(struct rtscam_video_stream *stream);
extern int __rtscam_soc_s_stream(struct rtscam_video_stream *stream, int enable);

uint32_t ameba_get_stream_cnt(int fd)
{
	struct rtscam_video_stream *stream;
	stream = get_stream(fd);
	return stream ? stream->frame_count : 0;
}

int rgb_lock_buffer(uint32_t lock_buf, uint8_t hw_slot)
{
#if 0
	struct rtscam_video_stream *stream;
	uint32_t free_buf;
	uint32_t reg;
	stream = get_stream(ID_RTS_NN_DEV);

	if (stream->bufs[hw_slot].buf_addr != lock_buf ) {
		printf("lock buf 0x%08x differ from slot 0x%08x\r\n", lock_buf, stream->bufs[hw_slot].buf_addr);
		return -1;
	}
	if ( stream->bufs[stream->stream_buf_num-1].state != RTS_BUF_STATE_READY) {
		printf("last buf isn't available \r\n");
		return -1;
	}
	free_buf = stream->bufs[stream->stream_buf_num-1].buf_addr;
	stream->bufs[hw_slot].buf_addr = free_buf;
	stream->bufs[stream->stream_buf_num-1].buf_addr = lock_buf;
	stream->bufs[stream->stream_buf_num-1].state = RTS_BUF_STATE_DONE;

	//rtscam_video_release_slot(stream, hw_slot);

	reg = RTS_REG_RGB_R_FRAME_START_ADDRESS_BASE + 4 * hw_slot;
	HAL_WRITE32(0x403F0000,  reg, free_buf);
	//printf("reg 0x%08x new_buf 0x%08x lock 0x%08x\r\n", reg, free_buf, lock_buf);
#endif
	printf("disable rgb_lock_buffer API\r\n");

	return 0;
}

int rgb_release_buffer(void)
{
#if 0
	struct rtscam_video_stream *stream;
	uint32_t free_buf;
	uint32_t reg;
	stream = get_stream(ID_RTS_NN_DEV);

	if ( stream->bufs[stream->stream_buf_num-1].state == RTS_BUF_STATE_DONE ) {
		stream->bufs[stream->stream_buf_num-1].state = RTS_BUF_STATE_READY;
		//printf("buffer 2 release 0x%08x\r\n", stream->bufs[2].buf_addr);
		return 0;
	}

	printf("didn't find lock rgb buffer\r\n");
#endif
	printf("disable rgb_release_buffer API\r\n");
	return 0;
}




//EXPORT_SYMBOL_GPL(rtscam_video_unregister_device);
