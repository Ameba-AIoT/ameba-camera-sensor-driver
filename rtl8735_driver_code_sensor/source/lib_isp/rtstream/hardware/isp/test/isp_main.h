/*
 * isp_main.h
 *
 *  Created on: 2021¦~3¤ë17¤é
 *      Author: martinhuang
 */

#ifndef HAL_ISP_MAIN_H_
#define HAL_ISP_MAIN_H_

#include "hal_isp.h"

//#define _OSD_EN_

int isp_main_thread(void const *argument);
int start_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id);
int get_stream_cnt(uint8_t stream_id);
int stream_close(uint8_t stream_id);
uint32_t get_latest_frame_buffer(uint8_t stream_id);
int release_frame_buffer(uint8_t stream_id, uint32_t buf_addr);
int check_isp_running(void);
int isp_main_close(void *argument);
int init_main(hal_isp_adapter_t *isp_adpt);
int get_skip_para(uint8_t stream_id, uint32_t *skip_m, uint32_t *skip_n);

#endif /* HAL_RTL8735B_LIB_SOURCE_RAM_VIDEO_ISP_RTSTREAM_HARDWARE_ISP_TEST_ISP_MAIN_H_ */
