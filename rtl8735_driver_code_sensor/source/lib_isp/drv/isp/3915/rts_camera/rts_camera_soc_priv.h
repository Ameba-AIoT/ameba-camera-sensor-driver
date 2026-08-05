/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_soc_priv.h
 *
 * Copyright (C) 2019      Wil shi<wil_shi@realsil.com.cn>
 */

#ifndef _RTS_CAMERA_SOC_PRIV_H
#define _RTS_CAMERA_SOC_PRIV_H


#include <linux/ioport.h>
#include "rts_camera.h"
#include "rts_camera_mem.h"
//#include <media/videobuf2-memops.h>


#define RTSCAM_SOC_HW_SLOT_NUM			4

int rtscam_soc_is_yuv(u8 rts_code);
int rtscam_soc_is_rgb(u8 rts_code);
int rtscam_soc_is_yonly(u8 rts_code);

struct rtscam_soc_dev;
void rtscam_soc_inc_overflow(struct rtscam_soc_dev *rsocdev, int i);
void rtscam_soc_inc_frames(struct rtscam_video_stream *stream);
void rtscam_soc_inc_errors(struct rtscam_video_stream *stream);
void rtscam_soc_inc_skips(struct rtscam_video_stream *stream);
void rtscam_soc_dec_drops(struct rtscam_video_stream *stream);
int rtscam_soc_get_drops(struct rtscam_video_stream *stream);
u32 rtscam_soc_get_devtype(void);

struct rtscam_video_stream *rtscam_soc_get_stream_from_reg_index(
		struct rtscam_soc_dev *rsocdev, int index);
u8 rtscam_soc_get_stream_reg_index(struct rtscam_video_stream *stream);
struct rtscam_soc_slot_info *rtscam_soc_get_skip_info(
		struct rtscam_soc_dev *rsocdev, int streamid);
int rtscam_soc_set_fps(struct rtscam_video_stream *stream, u32 fps);

struct rtscam_soc_slot_info {
	u8 slot_index;
	u8 slot_num;
	//struct rtscam_video_buffer *slots[RTSCAM_SOC_HW_SLOT_NUM];
	u32 slots[RTSCAM_SOC_HW_SLOT_NUM];
};

struct rtscam_soc_dma_buffer {
	struct list_head	list;
	struct device		*dev;
	void			*vaddr;
	unsigned long		size;
	dma_addr_t		phy_addr;
	int			initialized;
	u32			index;

	/*MMAP related*/
	//struct vb2_vmarea_handler handler;
	int refcount;
};

void rtscam_soc_free_memory(struct rtscam_soc_dev *rsocdev,
				struct rtscam_soc_dma_buffer *buffer);
int rtscam_soc_alloc_memory(struct rtscam_soc_dev *rsocdev,
				struct rtscam_soc_dma_buffer *buffer,
				int dir, gfp_t gfp, const char *name);
//int rtscam_soc_add_memory_property(struct rtscam_soc_dev *rsocdev,
//				dma_addr_t phy_addr, uint32_t property);

struct rtscam_soc_video_in {
	//struct reset_control *reset_video;
	//struct reset_control *sysmem;
	void *base;

	int support_rgb;
	struct rtscam_subdev_t *subdev;
	struct rtscam_soc_dev *priv;

	u32 (*read_reg)(struct rtscam_soc_video_in *video_in, off_t reg);
	void (*write_reg)(struct rtscam_soc_video_in *video_in,
		u32 value, off_t reg);

	void (*enable_interrupt)(struct rtscam_soc_video_in *video_in, int val);
	int (*config_buffer)(struct rtscam_soc_video_in *video_in);
	int (*submit_buffer)(struct rtscam_soc_video_in *video_in,
		struct rtscam_video_stream *stream, u32 phy_addr, int nr);
	int (*process_irq)(struct rtscam_soc_video_in *video_in);
	void (*isp_control)(struct rtscam_soc_video_in *video_in, u8 idx,
		int enable);
	void (*reset_isp_reg)(struct rtscam_soc_video_in *video_in, u8 idx);
	int (*set_fps)(struct rtscam_video_stream *stream, u32 fps);
	int (*set_fps_dynamic)(struct rtscam_video_stream *stream, u32 fps);
	void (*get_streamon_time)(void);
	void (*delay_stream_off)(void);
	int (*config_isp_head)(struct rtscam_soc_video_in *video_in);
	int (*clear_isp_head)(struct rtscam_soc_video_in *video_in);
	void (*release)(struct rtscam_soc_video_in *video_in);

	int width_step;
	int height_step;
	u8 height_align;

	struct {
		u32 yuv_axibuf_base;
		u32 yuv_base_val_bit;
		u32 yuv_size_val_bit;
		u32 rgb_axibuf_base;
		u32 rgb_axibuf_interval;
		u32 rgb_frame_len_r;
		u32 rgb_frame_len_g;
		u32 rgb_frame_len_b;
		u32 y_frame_len_base;
		u32 uv_frame_len_base;
		u32 yuv_frame_len_interval;
		u32 yuv_frame_buf_cnt;
		u32 rgb_frame_buf_cnt;
		u32 yuv_interleave_select;
		u32 isp_nv12_select;
		u32 td_buf_cfg;
		u32 multi_read;
	} reg;

	/*custom for 3903 or 3913*/
	//struct rtscam_soc_dma_buffer isp_headers;
	//u32 isp_reg;
	//struct rtscam_region td_config;
};

int rtscam_socdev_init_videoin(struct rtscam_soc_video_in **video_in);
#endif
