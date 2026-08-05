#ifndef _VOE_H_
#define _VOE_H_

#include <stdio.h>

#include "hal_video.h"
#include "hal_isp.h"


typedef struct {
	int size;
	int addr;
}voe_buf_queue_t;

typedef struct {
	int ch;
	int slot;
	u32 time_stamp;
//	int reserved;
	u32 ext_addr;
	unsigned long frame_cnt;
	isp_statis_meta_t statis_data;
	isp_meta_t isp_meta_data;
}isp2enc_t;

typedef struct {
	// ringbuffer
	int	out_size;			// out_buf_size
	int	rsvd_size;			// rsvd_size
	int	queue_size;			// queue_size
	int remain_size;		// remain_size
	int	renew_addr;			// ring buffer force renew pointer address
	int	put_addr;			// ring buffer put pointer address
	int	get_addr;			// ring buffer get pointer address
	int buf_full;			// ring buffer full
	int queue_avail;		// ring buffer queue avail count
	int	size_used;			// ring buffer used size
	int	slot_used;			// ring buffer used slot (frame)
	int	*out_buf;			// start buffer address offset
	int	*rsvd_buf;			// reserved buffer address offset
	void *queue;
//	volatile int status;	// buffer status 0: disable 1: enable

} hal_video_buf_s;

typedef struct {
	VCEncVideoCodecFormat	codecFormat;						// Video Codec Format: HEVC/H264/JPEG
	int						*enc_adp[MAX_CHANNEL];
	int						*jpg_adp[MAX_CHANNEL];

	hal_isp_adapter_t		isp_adp;

	int						*enc_in[MAX_CHANNEL];				// VCEncIn
	int						*enc_out[MAX_CHANNEL];				// VCEncOut

	hal_video_buf_s			*outbuf[MAX_CHANNEL];				// encoder output ring buffer
	hal_video_buf_s			*jpgbuf[MAX_CHANNEL];				// jpeg output ring buffer

	int						stab_slot[MAX_CHANNEL];

	int						isp2tm_time_out[MAX_CHANNEL];

	xTaskHandle				osd_handle;
	xTaskHandle				enc_handle;
	xTaskHandle				out_handle;
	xTaskHandle				wdt_handle;

	volatile int			voe_ch_cnt;							// VOE open channel count
	volatile int			voe_sync_cnt;						// VOE sync TM channel count

	u8 						*input_frame_table[MAX_CHANNEL];
	volatile int            voe_stream_open[MAX_CHANNEL];

}__attribute__((aligned(32))) voe_adp_t;

i32 run_voe(u32 cmd_param1, u32 cmd_param2);
i32 voe_encode(u32 cmd_param1, u32 cmd_param2);

// Show VOE information & debug
i32 voe_buf_info(void);
i32 voe_mem_info(u32 addr);
i32 voe_time_info(int level, int *voe_time);

// VOE normal control flow

i32 voe_open(u32 cmd_param1, int ch);
i32 voe_close(u32 cmd_param1, int ch);

i32 voe_start(u32 cmd_param1, int ch);
i32 voe_stop(u32 cmd_param1, int ch);

void voe_config_sensor_pin(u32 rst_pin, u32 pwdn_pin);

i32 voe_sync(u32 ch);
i32 voe_ext_in(u32 ch, u32 addr);
i32 voe_release_slot(u32 ch, u32 len, u32 type);
i32 voe_force_i (int ch);
i32 voe_set_rc (u32 cmd_param1, int ch);

i32 voe_test(int ch, int value);

i32 voe_set_roi_region (u32 cmd_param1, int ch);
i32 voe_set_obj_region (u32 cmd_param1, int ch);
i32 voe_tuning_iq_table (u32 cmd_param1, i32 req);
i32 voe_tuning_iq_statis (u32 cmd_param1, i32 req);
i32 voe_tuning_iq_param (u32 cmd_param1, i32 req);
i32 voe_set_osd_enc_en (int ch, int en);

i32 voe_yuv_out (int ch, int mode);
i32 voe_jpg_out (int ch, int mode);
i32 voe_enc_out (int ch, int mode);


i32 voe_set_wdt (u32 mode, u32 sec);
i32 voe_isp_release_slot(u32 ch, u32 addr);
i32 voe_tuning_iq_vreg (u32 cmd_param1, i32 req);

void voe_run_task (void const *argument);

void notify_tm_message(u32 cmd, int ch, u32 status);

uint32_t voe_isp_isr(void);
int km_test_hole(void);

#endif // _VOE_H_
