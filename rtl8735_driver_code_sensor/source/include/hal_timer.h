/**************************************************************************//**
 * @file     hal_timer.h
 * @brief    The HAL API implementation for the G-Timer device.
 * @version  V1.00
 * @date     2020-11-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_
//#include "cmsis_voe.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_timer TIMER
 * @ingroup 8195bh_hal
 * @{
 * @brief The TIMER HAL module of the HS platform.
 */

/**
  * @brief The stubs functions table to exports TIMER HAL functions in ROM.
  */



uint32_t hal_read_curtime_us (void);
void hal_delay_us (uint32_t time_us);
uint32_t hal_timer_alarm (uint32_t usec, void *cb);
void hal_timer_alarm_isr_update(void);

/** @} */ /* End of group hs_hal_timer */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_TIMER_H_"

