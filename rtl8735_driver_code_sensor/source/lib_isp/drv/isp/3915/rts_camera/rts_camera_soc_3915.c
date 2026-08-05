/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_soc_3915.h
 *
 * Copyright (C) 2019      Wil_shi<wil_shi@realsil.com.cn>
 */


#include "cmsis_os2.h"
#include <errno.h>
#include "rt_task.h"
#include "rts_errno.h"
#include <media/videobuf2-core.h>
#include "rts_camera_soc_priv.h"
#include "rts_camera_subdev.h"
#include "rts_camera_soc_3915_regs.h"
#include "rts_hw_id.h"
#include "rlx_irq.h"
#include "rlx_reg.h"
#include "isp_reg_tnr.h"
#include "rtx_mutex.h"
#include "rt_time.h"
#include "hal_timer.h"
#include "isp_debug.h"

static void isp_frdn_irq_bh(void const *data);
static osThreadId socBH_task_handle = NULL;
//osThreadDef (socdev_process_isp_irq_bh, osPriorityRealtime, 1, 64*1024);		// thread object
osThreadDef (isp_frdn_irq_bh, (osPriority)4, 1, 64*1024);		// thread object

static struct rtscam_soc_video_in gbl_video_in={0};
//static int frame_err_flag = 0;
static osSemaphoreId_t socBHSemaphore;
volatile u32 isp_int_time = 0;
//#define RTS_VIDEOIN_HEIGHT_ALIGN	16

extern volatile int buf_done[5][3];
extern volatile int buf_release[5][3];
//#ifdef RTS_VIDEOIN_HEIGHT_ALIGN
unsigned int rtscam_socdev_get_height_align(void)
{
	return 0;
}
//#endif

static struct rtscam_soc_dev *to_rsocdev_obj(
		struct rtscam_soc_video_in *video_in)
{
	return video_in->priv;
}

static u32 rtscam_socdev_read_reg(
		struct rtscam_soc_video_in *video_in, off_t reg)
{
	return *((u32*)((u32)video_in->base + reg));
}

static void rtscam_socdev_write_reg(struct rtscam_soc_video_in *video_in,
		u32 value, off_t reg)
{
	*((u32*)((u32)video_in->base + reg)) = value;
}

static void rtscam_socdev_isp_control(struct rtscam_soc_video_in *video_in,
		u8 idx, int enable)
{
	u32 reg;

	if (idx > RTSCAM_RGB_YONLY_STRM_IDX)
		return;

	if (idx == RTSCAM_RGB_YONLY_STRM_IDX)
		reg = RTS_REG_ISP_RGB_YONLY_STREAM_EN;
	else
		reg = RTS_REG_ISP_STREAM_EN_BASE + 4 * idx;

	if (enable)
		rtscam_socdev_write_reg(video_in, 1, reg);
	else
		rtscam_socdev_write_reg(video_in, 0, reg);
}

static void rtscam_socdev_reset_isp_reg(
		struct rtscam_soc_video_in *video_in, u8 idx)
{
	u32 reg;

	if (idx == RTSCAM_RGB_YONLY_STRM_IDX)
		reg = RTS_REG_ISP_RGB_YONLY_STREAM_RST;
	else
		reg = RTS_REG_ISP_STREAM_RST_BASE + 4 * idx;

	rtscam_socdev_write_reg(video_in, 1, reg);
	udelay(500);
	rtscam_socdev_write_reg(video_in, 0, reg);

	udelay(100);
	//vTaskDelay(1);
	//osDelay(1);
}

static int rtscam_socdev_submit_buffer(struct rtscam_soc_video_in *video_in,
	struct rtscam_video_stream *stream, u32 phy_addr, int nr)
{
	u32 reg_addr;
	u32 reg_index;
	u32 reg_status;
	u32 status;

	if (!video_in || !stream)
		return -EINVAL;

	if (rtscam_soc_is_yuv(stream->rts_code)) {
		u32 idx = 4 * nr;
		u32 offset = stream->streamid *
				RTS_REG_YUV_FRAME_START_ADDRESS_INTERVAL;
		u32 size = stream->user_width * stream->user_height;
		dma_addr_t phy_addr_uv = phy_addr + size;
#ifdef RTS_VIDEOIN_HEIGHT_ALIGN
		if (stream->user_height % RTS_VIDEOIN_HEIGHT_ALIGN) {
			phy_addr_uv += (RTS_VIDEOIN_HEIGHT_ALIGN - stream->user_height % RTS_VIDEOIN_HEIGHT_ALIGN)* stream->user_width;
			isp_info("%s HEIGHT_ALIGN issue %d 0x%08x\r\n", __func__, stream->user_height, phy_addr_uv);
		}
#endif

		reg_addr =
			RTS_REG_YUV_FRAME_Y_START_ADDRESS_BASE + offset + idx;
		reg_index =
			RTS_REG_YUV_FRAME_UV_START_ADDRESS_BASE + offset + idx;
		reg_status = RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE +
			stream->streamid * 4;
		status = 0xc << (4 * nr);

		rtscam_socdev_write_reg(video_in, phy_addr, reg_addr);
		if (stream->rts_code != RTSCAM_FORMAT_TYPE_YUYV &&
			stream->rts_code != RTSCAM_FORMAT_TYPE_YVYU)
			rtscam_socdev_write_reg(
				video_in, phy_addr_uv, reg_index);
	} else if (rtscam_soc_is_rgb(stream->rts_code)) {
		u32 offset = stream->user_width * stream->user_height;

		reg_status = RTS_REG_RGB_YONLY_FRAME_BUFFER_STATUS;
		status = 0x18 << (8 * nr);

		reg_addr = RTS_REG_RGB_R_FRAME_START_ADDRESS_BASE + 4 * nr;
		rtscam_socdev_write_reg(video_in, phy_addr, reg_addr);

		phy_addr += offset;
		reg_addr = RTS_REG_RGB_G_FRAME_START_ADDRESS_BASE  + 4 * nr;
		rtscam_socdev_write_reg(video_in, phy_addr, reg_addr);

		phy_addr += offset;
		reg_addr = RTS_REG_RGB_B_FRAME_START_ADDRESS_BASE  + 4 * nr;
		rtscam_socdev_write_reg(video_in, phy_addr, reg_addr);
		//isp_info("%s rgb buffer summit 0x%08x to reg 0x%08x\r\n",__FUNCTION__, phy_addr, reg_addr);
	} else if (rtscam_soc_is_yonly(stream->rts_code)) {
		reg_status = RTS_REG_RGB_YONLY_FRAME_BUFFER_STATUS;
		status = 0x18 << (8 * nr);
		reg_addr = RTS_REG_RGB_R_FRAME_START_ADDRESS_BASE + 4 * nr;
		rtscam_socdev_write_reg(video_in, phy_addr, reg_addr);
		//isp_info("%s yonly buffer summit 0x%08x to reg 0x%08x\r\n",__FUNCTION__, phy_addr, reg_addr);
	} else {
		rtsprintk(RTS_TRACE_BUF,
			  "invalid stream format (%d)\n", stream->rts_code);
		return -EINVAL;
	}

	rtscam_socdev_write_reg(video_in, status, reg_status);
	//status = rtscam_socdev_read_reg(video_in, reg_status);
	//rtsprintk(RTS_TRACE_DEBUG,
	//	  "clear frame status, reg = 0x%08x, value = 0x%08x\n",
	//	  reg_status, status);
	return 0;
}

static int rtscam_socdev_release_slot(struct rtscam_soc_video_in *video_in,
	struct rtscam_video_stream *stream, int flag_overflow)
{
	u32 reg_addr;
	//u32 reg_index;
	u32 reg_status;
	u32 status;
	u32 last_valid_slot, release_slot;
	u32 release_offset = 0;

	if (flag_overflow)
		release_offset = 1;


	if (!video_in || !stream)
		return -EINVAL;
	//isp_info("%s addr 0x%08x nr %d \r\n",__FUNCTION__, phy_addr, nr);
	if (rtscam_soc_is_yuv(stream->rts_code)) {
		reg_addr = RTS_REG_YUV_Y_CUR_FRAME_INDEX_OFFSET_BASE + stream->streamid * RTS_REG_YUV_CUR_FRAME_INDEX_OFFSET_INTERVAL;
		last_valid_slot = rtscam_socdev_read_reg(video_in, reg_addr) & 0x3;
		if ( last_valid_slot > 0 )
			last_valid_slot--;
		else
			last_valid_slot = stream->hw_slot_num-1;
		stream->latest_done_buf = last_valid_slot;
		release_slot = (last_valid_slot+release_offset)%stream->hw_slot_num;
		reg_status = RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE + stream->streamid * 4;
		status = 0xc << (4 * release_slot);

	} else if (rtscam_soc_is_rgb(stream->rts_code) || rtscam_soc_is_yonly(stream->rts_code) ) {
		reg_addr = RTS_REG_RGB_R_CUR_FRAME_INDEX_OFFSET;
		last_valid_slot = rtscam_socdev_read_reg(video_in, reg_addr) & 0x3;
		//last_valid_slot = rtscam_socdev_read_reg(video_in, reg_addr) & 0x3;
		if ( last_valid_slot > 0 )
			last_valid_slot--;
		else
			last_valid_slot = stream->hw_slot_num-1;

		stream->latest_done_buf = last_valid_slot;
		release_slot = (last_valid_slot+release_offset)%stream->hw_slot_num;
		reg_status = RTS_REG_RGB_YONLY_FRAME_BUFFER_STATUS;
		status = 0x18 << (8 * release_slot);
	} else {
		isp_error("%s invalid stream format (%d)\r\n", __func__, stream->rts_code);
		return -EINVAL;
	}
	rtscam_socdev_write_reg(video_in, status, reg_status);
	//status = rtscam_socdev_read_reg(video_in, reg_status);
	isp_info("%s clear frame status, reg = 0x%08x, value = 0x%08x\n", __func__, reg_status, rtscam_socdev_read_reg(video_in, reg_status));
	return 0;
}
static int rtscam_socdev_process_frame(struct rtscam_soc_video_in *video_in,
		struct rtscam_video_stream *stream, int frameid)
{
	struct rtscam_soc_dev *rsocdev = to_rsocdev_obj(video_in);
	struct rtscam_soc_slot_info *info;
	struct rtscam_video_buffer rbuf;
	u32 reg;
	//u32 reg_index;
	u32 status;
	u32 mask;
	u8 idx = rtscam_soc_get_stream_reg_index(stream);
	//unsigned long bytesused;
	int skip;
	uint32_t done_buffer;

	info = rtscam_soc_get_skip_info(rsocdev, stream->streamid);

	if (frameid < 0 || frameid >= info->slot_num)
		return -EINVAL;

	reg = RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE + 4 * idx;
	status = rtscam_socdev_read_reg(video_in, reg);

	if (rtscam_soc_is_yuv(stream->rts_code))
		mask = 0x8 << (4 * frameid);
	else
		mask = 0x10 << (8 * frameid);
	if (!(mask & status))
		return 0;

	//rbuf = info->slots[frameid];
	done_buffer = info->slots[frameid];
	info->slots[frameid] = 0;
	//stream->latest_done_slot = frameid;
	rbuf.buf_addr = done_buffer;
#if 1
	if (rtscam_soc_is_yuv(stream->rts_code))
		mask = 1 << (4 * frameid + 2);
	else
		mask = 1 << (8 * frameid + 3);
	if (mask & status) {
		//rtscam_submit_buffer(stream, &rbuf);
		rtscam_socdev_release_slot(video_in, stream, FALSE);

		rtscam_socdev_write_reg(video_in, mask, reg);
		rtscam_soc_inc_errors(stream);

		return 0;
	}
#endif
	//if (rbuf == NULL) {
	//	isp_error("%s rtscam_soc_get_drops\r\n", __FUNCTION__);
	//	return -EINVAL;
	//}
	if (stream->bufs[frameid].state == RTS_BUF_STATE_DONE)
		return 0;

	extern u32 g_isp_drop_frame_cnt;
	if (!rtscam_soc_is_yuv(stream->rts_code) && g_isp_drop_frame_cnt < isp_hw_global_get_drop_frame_num_sw()) {
		g_isp_drop_frame_cnt++;
		rtscam_socdev_release_slot(video_in, stream, FALSE);
		return 0;
	}

	skip = rtscam_skip_frame(stream);

	//isp_info("frameid = %d, skip = %d\r\n", frameid, skip);
	if (skip) {
		rtscam_soc_inc_skips(stream);
		//rtscam_submit_buffer(stream, &rbuf);
		rtscam_socdev_release_slot(video_in, stream, FALSE);
		//printf("%s rtscam_soc_inc_skips\r\n", __FUNCTION__);
		return 0;
	}

	//bytesused = stream->sizeimage;



	rtscam_buffer_done(stream, &rbuf, frameid);
#if 0
	for (int i=0; i<3; i++) {
		if (stream->bufs[i].state == RTS_BUF_STATE_DONE )
		{
			//isp_info("%s stream %d state %d buf %d change to ready \r\n", __FUNCTION__, stream->streamid, stream->bufs[i].state, i);
			stream->bufs[i].state = RTS_BUF_STATE_READY;
		}
	}
#endif

	//rtscam_submit_buffer(stream, NULL);
	//isp_info("%s stream %d cnt %d \r\n", __FUNCTION__, stream->streamid, stream->frame_count);

	return 0;
}
#if 0
static int __pre_process_rgb_yonly_irq(struct rtscam_soc_video_in *video_in)
{

}
#endif
//static int ddr_overflow_cnt_rgb= 0;
//static ddr_overflow_cnt= 0;

volatile int ddr_overflow_cnt_rgb= 0;
volatile int ddr_overflow_cnt= 0;

static int process_rgb_yonly_irq(struct rtscam_soc_video_in *video_in)
{
	const u32 reg = RTS_REG_INT_FLAG_RGB_YONLY_HOST;
	u32 status;
	u32 mask = 0;
	int i;
#ifdef _FRAME_CNT_OVERFLOW_
	u32 t1=0, t2=0;
#endif
	struct rtscam_video_stream *stream = NULL;

	status = rtscam_socdev_read_reg(video_in, reg);
	//isp_info(" %s status 0x%08x\r\n", __func__, status);
	if (!status)
		return 0;
	//isp_info(" %s status 0x%08x\r\n", __func__, status);
	/*
	 * clear reserved isp_host interrupt
	 * clear DDR frame length overflow and AXI overflow
	 */
	mask = 0xffffffe7;
	if (status & mask) {
		rtscam_socdev_write_reg(video_in, mask, reg);
		isp_error(" %s DDR frame length overflow and AXI overflow status 0x%08x\r\n", __func__, status);
	}

	mask = 0x8;
	if (status & mask) {

		rtscam_socdev_write_reg(video_in, mask, reg);
#ifdef _FRAME_CNT_OVERFLOW_
		t2 = hal_read_curtime_us();
		if ((ddr_overflow_cnt_rgb%302)==0 ) {
			isp_warning("rgb ddr frame count overflow : int_status 0x%08x buf_status 0x%08x time %d cnt %d\r\n", status, rtscam_socdev_read_reg(video_in, RTS_REG_RGB_YONLY_FRAME_BUFFER_STATUS),  t2 - t1, ddr_overflow_cnt_rgb);
		}
		ddr_overflow_cnt_rgb++;
		t1 = t2;
#endif
		rtscam_soc_inc_overflow(to_rsocdev_obj(video_in),
				RTSCAM_RGB_YONLY_STRM_IDX);

		//stream = rtscam_soc_get_stream_from_reg_index(to_rsocdev_obj(video_in),	RTSCAM_RGB_YONLY_STRM_IDX);
		//xSemaphoreTake(stream->lock, portMAX_DELAY);  //spin_lock(&stream->lock);
		//rtscam_socdev_release_slot(video_in, stream, TRUE);
		//rtscam_submit_buffer(stream, NULL);
		//osMutexRelease(stream->lock);  //spin_unlock(&stream->lock);
	}

	mask = 1 << 4;
	if (status & mask) {
		int cnt;

		rtscam_socdev_write_reg(video_in, mask, reg);

		stream = rtscam_soc_get_stream_from_reg_index(
				to_rsocdev_obj(video_in),
				RTSCAM_RGB_YONLY_STRM_IDX);
		if (stream == NULL) {
			isp_warning("no stream found\n");
			return 1;
		}

		if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock(&stream->lock);
			isp_error("process_rgb_yonly_irq wait stream->lock timeout\n\r");
			return 1;
		}
		mask = 0x3;
		i = mask & rtscam_socdev_read_reg(video_in,
				RTS_REG_RGB_R_CUR_FRAME_INDEX_OFFSET);
		if ( i > 0 )
			i--;
		else
			i = stream->hw_slot_num-1;

		stream->latest_done_buf = i;


		for (cnt = 0; cnt < stream->hw_slot_num; cnt++) {
			rtscam_socdev_process_frame(video_in, stream, i++);
			i %= stream->hw_slot_num;
		}
		//osMutexRelease(stream->lock);  //spin_unlock(&stream->lock);
		xSemaphoreGive(stream->lock);

	}

	return 0;


}



static void rtscam_socdev_bh_enable_interrupt(
			struct rtscam_soc_video_in *video_in, int enable)
{
	u32 int_en;



	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();



	if (enable)
		RLX_EnableVideoInIRQ_woCS(VIDEOIN_ID_SOC);

	if (enable)
		int_en = 0xFFFF;//0xcccc;
	else
		int_en = 0;

	rtscam_socdev_write_reg(video_in, int_en, RTS_REG_INT_EN_ISP_TO_HOST);

	if (enable)
		int_en = 0x18;
	else
		int_en = 0;

	rtscam_socdev_write_reg(video_in, int_en, RTS_REG_INT_EN_RGB_YONLY_TO_HOST);

	if (!enable)
		RLX_DisableVideoInIRQ_woCS(VIDEOIN_ID_SOC);


	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();







	//printf(" enable %d\r\n", enable);
}
extern voe_adp_t *voe_adp;
static void isp_frdn_irq_bh(void const *data)
{
	struct rtscam_soc_video_in *video_in=(struct rtscam_soc_video_in *)data;
	const u32 reg_isp = RTS_REG_INT_FLAG_ISP_HOST;
	u32 status;
	u32 mask = 0, mask_fidx = 0;
	int i, cnt, fidx;
	struct rtscam_video_stream *stream = NULL;
	u32 t1 =0, t2 =0;
	//printf("bh start \r\n");
//	char str[64];
	while (1) {
//		if (osSemaphoreAcquire(socBHSemaphore, osWaitForever) != osOK) {
		if (xSemaphoreTake(socBHSemaphore, osWaitForever) != pdTRUE) {

			if(voe_adp->voe_ch_cnt != 0) {
				printf("isp_frdn_irq_bh wait semaphore timeout ch(%d)\n", voe_adp->voe_ch_cnt);
			}
			continue;
			//isp_error("socBHSemaphore acquire error\r\n");
			//break;
		}
		//printf("bh run \r\n");
		status = rtscam_socdev_read_reg(video_in, reg_isp);
		//printf(" status 0x%08x\r\n", status);
		if (!status) {


//#if CONFIG_VERIFY_SYSVIEW
//	sprintf(str,"<ISP> <%s><%d> \r\n", __func__,__LINE__);
//	SEGGER_SYSVIEW_Print(str);
//#endif
			goto next;
		}
		//printf(" <%s> status 0x%08x\r\n", __func__,status);
		/*
		 * clear reserved isp_host interrupt
		 * clear DDR frame length overflow and AXI overflow
		 */
		mask = 0xffff3333;
		if (status & mask) {
			isp_error(" %s DDR frame length overflow and AXI overflow 0x%08x\r\n", __func__, status);
			rtscam_socdev_write_reg(video_in, mask, reg_isp);
			//return RTS_E_OVERFLOW;
		}

		//check isp overflow
		mask = 0x04444;
		if (status & mask) {
			for (i = 0; i < RTSCAM_YUV_MAX_STRM_NUM; i++) {
				mask = 0x4 << (4 * i);
				if (status & mask) {
					rtscam_socdev_write_reg(video_in, mask, reg_isp);
					rtscam_soc_inc_overflow(to_rsocdev_obj(video_in), i);
		
					stream = rtscam_soc_get_stream_from_reg_index(to_rsocdev_obj(video_in), i);

					//stream = rtscam_soc_get_stream_from_reg_index(to_rsocdev_obj(video_in), i);
					if (stream) {

						if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock(&stream->lock);
							isp_error("isp_frdn_irq_bh wait stream->lock timeout\n\r");
							continue;
						}
						mask_fidx = 0x3;
						fidx = mask_fidx & rtscam_socdev_read_reg(video_in,
								RTS_REG_YUV_Y_CUR_FRAME_INDEX_OFFSET_BASE +
								i * RTS_REG_YUV_CUR_FRAME_INDEX_OFFSET_INTERVAL);

						for (int j = 0; j < stream->hw_slot_num; j++) {
							if ( (stream->buf_done[j] <= stream->buf_release[j])  &&  (stream->buf_release[j] != 0) && fidx == j ) {
								if ( (status & (1 <<(4*j+3)) ) != 0 ) {
								printf("[WARN]enc free but isp had valid data %d slot %d done %d release %d state %d status 0x%08x\n", stream->streamid, j, stream->buf_done[j], stream->buf_release[j], stream->bufs[j].state, status);
								rtscam_socdev_release_slot(video_in, stream, j);
								stream->buf_done[j] = 0;
								stream->buf_release[j] = 0;

								}
								stream->bufs[j].state = RTS_BUF_STATE_READY;
							}
						}
						t2 = hal_read_curtime_us();
						if ( ((ddr_overflow_cnt%302)==0) ) {
#ifndef __TTFF_ISP__
							printf("[WARN]slot full : s%d int 0x%08x buf 0x%08x time %d cnt %d slot0 dn %d rls %d slot1 %d %d osd_t dn %d %d rel %d %d \r\n", i, status, rtscam_socdev_read_reg(video_in, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE+ 4 * i),
									t2 - t1, ddr_overflow_cnt, stream->buf_done[0], stream->buf_release[0], stream->buf_done[1], stream->buf_release[1], buf_done[i][0],  buf_done[i][1], buf_release[i][0],  buf_release[i][1]);
#endif

	    				}
						ddr_overflow_cnt++;
						t1 = t2;


						//osMutexRelease(stream->lock);  //spin_unlock(&stream->lock);
						xSemaphoreGive(stream->lock);

					} else {
						isp_error("no stream found\r\n");
					}

					//rtscam_submit_buffer(stream, NULL);
					//rtscam_socdev_release_slot(video_in, stream, 0); // add to drop latest frame
					//rtscam_socdev_release_slot(video_in, stream, TRUE); // force release isp target frame but didn't release sema
					//osMutexRelease(stream->lock);  //spin_unlock(&stream->lock);




				}
			}
		}
		//int index = rtscam_socdev_read_reg(video_in, RTS_REG_YUV_Y_CUR_FRAME_INDEX_OFFSET_BASE);
		//rtscam_socdev_write_reg(video_in, 0xffffffff, reg_isp);
		//rtscam_socdev_write_reg(video_in, 0xffffffff, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE);
		//printf ("%d status 0x%08x \r\n", index, status);
		//check frame ready
		mask = 0x08888;
		if (status & mask) {
			for (i = 0; i < RTSCAM_MAX_STREAM_NUM; i++) {
				mask = 1 << (4 * i + 3);
				if (status & mask) {
					rtscam_socdev_write_reg(video_in, mask, reg_isp);
					
					stream = rtscam_soc_get_stream_from_reg_index(
							to_rsocdev_obj(video_in), i);
					if (stream) {


						if (xSemaphoreTake(stream->lock, ISP_SEM_TIMEOUT) != pdTRUE) {  //spin_lock(&stream->lock);
							isp_error("isp_frdn_irq_bh xSemaphoreTake fail\n\r");
							continue;
						}
						mask_fidx = 0x3;
						fidx = mask_fidx & rtscam_socdev_read_reg(video_in,
								RTS_REG_YUV_Y_CUR_FRAME_INDEX_OFFSET_BASE +
								i * RTS_REG_YUV_CUR_FRAME_INDEX_OFFSET_INTERVAL);

						if ( fidx > 0 )
							fidx--;
						else
							fidx = stream->hw_slot_num-1;

						stream->latest_done_buf = fidx;
						//printf("stream %d status 0x%08x fidx %d \r\n", stream->streamid, status, stream->latest_done_buf);

						for (cnt = 0; cnt < stream->hw_slot_num; cnt++) {
							rtscam_socdev_process_frame(video_in, stream, fidx++);
							fidx %= stream->hw_slot_num;
						}
						//osMutexRelease(stream->lock);  //spin_unlock(&stream->lock);
						xSemaphoreGive(stream->lock);

					} else {
						isp_error("no stream found\r\n");
					}
				}
			}
		}

next:
		process_rgb_yonly_irq(video_in);
		//re-enable HW/SW irq
		rtscam_socdev_bh_enable_interrupt(video_in, 1);
#ifdef _MIPI_DEBUG_
		uint32_t ecc_err = isp_read_reg(0xC0144); //MIPI_DPHY_ECC_CNT_L
		uint32_t crc_err = isp_read_reg(0xC014C); //MIPI_DPHY_CRC_CNT_L
		uint32_t mipi_err = isp_read_reg(0xC0148); //MIPI_DPHY_CHECK
		if (ecc_err || crc_err || mipi_err)
			printf("mipi 0x%08x ecc 0x%08x crc 0x%08x\r\n", mipi_err, ecc_err, crc_err);
#endif


		//RLX_ClearPendingIRQ(ISP_IRQn);
		//RLX_EnableIRQ(ISP_IRQn);
	}
	printf("%s osThreadTerminate\r\n", __func__);
//	osThreadTerminate (socBH_task_handle);
	vTaskDelete(socBH_task_handle);
	//vTaskDelete(NULL);
}

static int rtscam_socdev_process_isp_irq(
		struct rtscam_soc_video_in *video_in)
{
	const u32 reg_isp = RTS_REG_INT_FLAG_ISP_HOST;
	u32 status;
	u32 mask = 0;

	//if (__pre_process_rgb_yonly_irq(video_in))
	//	return RTS_OK;

	const u32 rgb_reg = RTS_REG_INT_FLAG_RGB_YONLY_HOST;
	u32 rgb_status;
	u32 rgb_mask = 0;


	rgb_status = rtscam_socdev_read_reg(video_in, rgb_reg);
//	if (frame_err_flag == 1) {
//		printf("s0 0x%08x s1 0x%08x rgb 0x%08x\r\n", rtscam_socdev_read_reg(video_in, reg_isp), rtscam_socdev_read_reg(video_in, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE),rgb_status);
//	}

	if (rgb_status) {
		//printf(" rgb status 0x%08x\r\n", rgb_status);
		/*
		 * clear reserved isp_host interrupt
		 * clear DDR frame length overflow and AXI overflow
		 */
		rgb_mask = 0xffffffe7;
		if (rgb_status & rgb_mask) {
			rtscam_socdev_write_reg(video_in, rgb_mask, rgb_reg);
			isp_error("rgb DDR frame length overflow and AXI overflow 0x%08x\r\n", rgb_status);
			return RTS_OK;
		}
	}


	status = rtscam_socdev_read_reg(video_in, reg_isp);
	//if (status)
	//	printf(" INT 0x%08x s1 0x%08x s2 0x%08x\r\n", status, rtscam_socdev_read_reg(video_in, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE),rtscam_socdev_read_reg(video_in, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE+4));
	if (!status && !rgb_status) {
		return RTS_OK;
	}
	//rtscam_socdev_write_reg(video_in, 0xffffffff, reg_isp);
	//rtscam_socdev_write_reg(video_in, 0xffffffff, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE);
	/*
	 * clear reserved isp_host interrupt
	 * clear DDR frame length overflow and AXI overflow
	 */
	mask = 0xffff3333;
	if (status & mask) {
		rtscam_socdev_write_reg(video_in, mask, reg_isp);
		isp_error(" %s DDR frame length overflow and AXI overflow 0x%08x\r\n", __func__, status);
		return RTS_OK;
	}
	isp_int_time = hal_read_curtime_us();
	//process in bh
	rtscam_socdev_bh_enable_interrupt(video_in, 0);
	//NVIC_DisableIRQ(ISP_IRQn);

#if 1
    portBASE_TYPE taskWoken = pdFALSE;
	if (xSemaphoreGiveFromISR(socBHSemaphore, &taskWoken) != pdTRUE) {
		printf("xSemaphoreGiveFromISR socBH 0x%08x Err \r\n", (unsigned int)socBHSemaphore);
	}
    portEND_SWITCHING_ISR(taskWoken);
#else
	int bh_sema;  //wake rtscam_socdev_process_isp_irq_bh()

	bh_sema = osSemaphoreRelease(socBHSemaphore);
	if (bh_sema)
		printf(" osSemaphoreRelease 0x%08x Err ret 0x%08x\r\n", (unsigned int)socBHSemaphore, bh_sema);
#endif
#if 0
	int index = rtscam_socdev_read_reg(video_in, RTS_REG_YUV_Y_CUR_FRAME_INDEX_OFFSET_BASE);
	int buf_status = rtscam_socdev_read_reg(video_in, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE);
	//rtscam_socdev_write_reg(video_in, 0xffffffff, reg_isp);
	//rtscam_socdev_write_reg(video_in, 0xffffffff, RTS_REG_YUV_FRAME_BUFFER_STATUS_BASE);
	printf ("%d status 0x%08x 0x%08x \r\n", index, status, buf_status);
#endif
	return RTS_OK;
}

static void rtscam_socdev_enable_interrupt(
			struct rtscam_soc_video_in *video_in, int enable)
{
	u32 int_en;

	if (enable)
		int_en = 0xFFFF;//0xcccc;
	else
		int_en = 0;

	rtscam_socdev_write_reg(video_in, int_en, RTS_REG_INT_EN_ISP_TO_HOST);
	rtscam_socdev_write_reg(video_in,
			0xffffffff, RTS_REG_INT_FLAG_ISP_HOST);

	if (enable)
		int_en = 0x18;

	rtscam_socdev_write_reg(video_in,
			int_en, RTS_REG_INT_EN_RGB_YONLY_TO_HOST);
	rtscam_socdev_write_reg(video_in,
			0xffffffff, RTS_REG_INT_FLAG_RGB_YONLY_HOST);

	if (enable)
		RLX_EnableVideoInIRQ(VIDEOIN_ID_SOC);
	else
		RLX_DisableVideoInIRQ(VIDEOIN_ID_SOC);
}

static void rtscam_socdev_release_3915(struct rtscam_soc_video_in *video_in)
{
	//kfree(video_in);
}


int rtscam_socdev_init_videoin(struct rtscam_soc_video_in **pvideo_in)
{
	struct rtscam_soc_video_in *video_in=&gbl_video_in;
	//int ret;

	if (rtscam_soc_get_devtype() != TYPE_RTS3915)
		return -EINVAL;

	//video_in->reset_video = devm_reset_control_get(dev, "video");
	//if (IS_ERR(video_in->reset_video)) {
	//	rtsprintk(RTS_TRACE_ERROR, "fail to get reset : video\n");
	//	return -EINVAL;
	//}

	//video_in->sysmem = devm_reset_control_get(dev, "video-sysmem-up");
	//if (IS_ERR(video_in->sysmem)) {
	//	rtsprintk(RTS_TRACE_ERROR, "fail to get reset : sysmem\n");
	//	return -EINVAL;
	//}

	video_in->base = (void*)SOC_CAM_BASE;

	video_in->width_step = 4;
	video_in->height_step = 4;
	video_in->height_align = 16;

	video_in->enable_interrupt = rtscam_socdev_enable_interrupt;
	video_in->write_reg = rtscam_socdev_write_reg;
	video_in->read_reg = rtscam_socdev_read_reg;
	video_in->submit_buffer = rtscam_socdev_submit_buffer;
	video_in->process_irq = rtscam_socdev_process_isp_irq;
	video_in->reset_isp_reg = rtscam_socdev_reset_isp_reg;
	video_in->isp_control = rtscam_socdev_isp_control;
	video_in->set_fps = rtscam_soc_set_fps;
	video_in->set_fps_dynamic = rtscam_soc_set_fps;
	video_in->release = rtscam_socdev_release_3915;

	video_in->support_rgb = 1;
	video_in->reg.yuv_axibuf_base = RTS_REG_YUV_AXI_BUF_CONFIG_BASE;
	video_in->reg.yuv_base_val_bit = 4;
	video_in->reg.yuv_size_val_bit = 20;
	video_in->reg.rgb_axibuf_base = RTS_REG_RGB_R_AXI_BUF_CONFIG;
	video_in->reg.rgb_axibuf_interval =
			RTS_REG_RGB_AXI_BUF_CONFIG_INTERVAL;
	video_in->reg.rgb_frame_len_r = RTS_REG_RGB_FRAME_LEN_R;
	video_in->reg.rgb_frame_len_g = RTS_REG_RGB_FRAME_LEN_G;
	video_in->reg.rgb_frame_len_b = RTS_REG_RGB_FRAME_LEN_B;
	video_in->reg.y_frame_len_base = RTS_REG_YUV_FRAME_LEN_Y_BASE;
	video_in->reg.uv_frame_len_base = RTS_REG_YUV_FRAME_LEN_UV_BASE;
	video_in->reg.yuv_frame_len_interval = RTS_REG_YUV_FRAME_LEN_INTERVAL;
	video_in->reg.yuv_frame_buf_cnt = RTS_REG_YUV_FRAME_BUFFER_COUNT;
	video_in->reg.rgb_frame_buf_cnt =
			RTS_REG_RGB_YONLY_FRAME_BUFFER_COUNT;
	video_in->reg.yuv_interleave_select = RTS_REG_YUV_INTERLEAVE_SELECT;
	video_in->reg.isp_nv12_select = RTS_REG_ISP_NV12_SELECT;
	video_in->reg.td_buf_cfg = 0;
	video_in->reg.multi_read = 0;

	//osSemaphoreAttr_t socBHSemaphoreAttr = { .name = "socBHSemaphore" };
	//socBHSemaphore = osSemaphoreNew(1, 0, &socBHSemaphoreAttr);
	socBHSemaphore = xSemaphoreCreateCounting(1, 0);

	if (socBHSemaphore == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "socBH task sema create fail!\n");
	    goto err;
	}
	//printf("socBHSemaphore 0x%08x\r\n", socBHSemaphore);
#if 0
	socBH_task_handle = osThreadCreate (osThread(isp_frdn_irq_bh), (void*)video_in);
    if (socBH_task_handle == 0) {
        isp_error ("Create socBH_task_handle task error\r\n");
    }
#else
    int ret;
	ret = xTaskCreate((TaskFunction_t)isp_frdn_irq_bh,"isp_frdn", 16*1024, video_in, 7, &socBH_task_handle);
	if(ret == pdFAIL) {
        isp_error ("Create socBH_task_handle task error\r\n");
	}
#endif
	isp_info("socBH_task_handle task\r\n");
#if 0
	task_info_st  socBH_task_info =
	{
	    .name       = "socBH_task",
	    .priority   = 4,
	    .delay      = pdMS_TO_TICKS(100),
	    .func       = rtscam_socdev_process_isp_irq_bh,
	    .param      = (void*)video_in,
	    .stack_size = SZ_16K,
	    .pre_del_cb = NULL,
	};
	if ((socBH_task_handle = task_create_user_by_struct(&socBH_task_info, &ret)) == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "socBH task create fail!\n");
	    goto err;
	}
#endif
	*pvideo_in = video_in;
	//vTaskResume(socBH_task_handle);

	return 0;

err:
	*pvideo_in = NULL;
	return -1;
}
