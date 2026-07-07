/*
 * voe_isp.h
 *
 *  Created on: 2021¦~5¤ë4¤é
 *      Author: martinhuang
 */

#ifndef CMSIS_VOE_SOURCE_VOE_ISP_H_
#define CMSIS_VOE_SOURCE_VOE_ISP_H_

int voe_isp_all(void *video_adpt, int frame_cnt);
uint32_t get_adpt(void);
i32 voe_isp_ctrl(uint32_t id, int *value, int set_flag);


#endif /* CMSIS_VOE_SOURCE_VOE_ISP_H_ */
