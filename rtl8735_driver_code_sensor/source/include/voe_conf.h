/**************************************************************************//**
 * @file     voe_conf.h
 * @brief    The configuration for AmebaPro2(KM) platform.
 * @version  V1.00
 * @date     2020-12-28
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
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
#ifndef _VOE_CONFIG_H_
#define _VOE_CONFIG_H_

#if CONFIG_FPGA
// FPGA
#define XTAL                                (20000000U)     /* 20Mhz */
#define CONFIG_CPU_CLK                      (XTAL)
#define PLATFORM_SCLK                       (40000000)       /* FPGA PCLK 40MHz */
#define CHIP_VER                            (CHIP_A_CUT)

#elif CONFIG_PXP
#define CONFIG_CPU_CLK                      (500000000U)
#define PLATFORM_SCLK                       (40000000U)
#define CHIP_VER                            (CHIP_A_CUT)
#else
// ASIC
#define CONFIG_CPU_CLK                      (500000000U)
#define PLATFORM_SCLK                       (40000000U)
#define CHIP_VER                            (CHIP_A_CUT)
#endif


#endif // _VOE_CONFIG_H_
