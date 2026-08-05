/**************************************************************************//**
 * @file     cmsis_voe.h
 * @brief    The generic CMSIS include file.
 * @version  V1.00
 * @date     2020-10-14
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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

#ifndef MBED_CMSIS_VOE_H
#define MBED_CMSIS_VOE_H

#define _VOE_PRINT_

#define VOE_IROM_S			0x00000000
#define VOE_IROM_E			0x000003FF		// 1KB
#define VOE_IRAM_S			0x00040000
#define VOE_IRAM_E			0x0004FFFF		// 64KB

#define VOE_DROM_S			0x20010000
#define VOE_DROM_E			0x20013FFF		// 16KB
#define VOE_DRAM_S			0x20000000
#define VOE_DRAM_E			0x2000FFFF		// 64KB


#define VOE_KEEP			0x2000F800		// 8KB

#define VOE_REG_BASE		0x40492000



#define TM9_ITCM_ROM_BASE         (0x00000000UL)
#define TM9_ITCM_RAM_BASE         (0x00010000UL)
#define TM9_ROM_BASE              (0x10000000UL)
#define TM9_DTCM_ROM_BASE         (0x20000000UL)
#define TM9_DTCM_RAM_BASE         (0x20010000UL)
#define TM9_RAM_BASE              (0x20100000UL)

#define TM9_APB_BASE              (0x40000000UL)
#define TM9_SEC_APB_BASE          (0x50000000UL)

#define TM9_SYSON_BASE            (TM9_APB_BASE       + 0x000000UL)
#define TM9_WLAN_BASE             (TM9_APB_BASE       + 0x080000UL)
#define TM9_USB_OTG_BASE          (TM9_APB_BASE       + 0x0C0000UL)
#define TM9_ISP_BASE              (TM9_APB_BASE       + 0x300000UL)     // ISP/MIPI
#define TM9_PSRAMPHY_BASE         (TM9_APB_BASE       + 0x402000UL)     // PSRAM/LPDDR1 Phy. Controller
#define TM9_LPDDRPCAL_BASE        (TM9_APB_BASE       + 0x420000UL)     // LPDDR1 Phy. Calibration
#define TM9_VOE_BASE              (TM9_APB_BASE       + 0x490000UL)     // Video Offload Engine
#define TM9_TFT_BASE              (TM9_APB_BASE       + 0x491000UL)     // TFT Controller
#define TM9_H264_BASE             (TM9_APB_BASE       + 0x500000UL)     // H.264 Encoder
#define TM9_MJPG_BASE             (TM9_APB_BASE       + 0x580000UL)     // MJPG Encoder
#define TM9_PSRAM_BASE            (TM9_APB_BASE       + 0x600000UL)     // PSRAM Controller
#define TM9_LPDDR_BASE            (TM9_APB_BASE       + 0x601000UL)     // LPDDR Controller

#define TM9_PSRAM_MEM_BASE        (0x60000000UL)
#define TM9_LPDDR_MEM_BASE        (0x70000000UL)

#define TM9_IDAU_BASE             (TM9_SEC_APB_BASE   + 0x000000UL)     // Secure Cross-Bar controller (IDAU)

#include "cmsis_compiler.h"
#include "platform_conf.h"
#include "basic_types.h"

#include "rtl8735b_voe.h"
#include "rtl8735b_voe_irq.h"             /* The IRQ priority definition */
#include "section_config_voe.h"
#include "hal_api_voe.h"
#include "core_tm9_cache.h"

#include <arm_cmse.h>   /* Use CMSE intrinsics */


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"


#endif  // end of "#ifndef MBED_CMSIS_VOE_H

