/*
 * Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
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
 * @file     rtl8735b_voe.h
 * @brief    CMSIS HeaderFile
 * @version  1.0
 * @date     16. September 2020
 * @note     resulted from rtl8710c.h(AmebaZ2), because both are KM4 asic
 */



/** @addtogroup Realtek Semiconductor Corp.
  * @{
  */


/** @addtogroup rtl8735b_voe
  * @{
  */


#ifndef RTL8735B_VOE_H
#define RTL8735B_VOE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn {
/* ========================================  ARM ARMV8MML Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  MemoryManagement_IRQn     = -12,              /*!< -12  Memory Management, MPU mismatch, including Access Violation
                                                     and No Match                                                              */
  BusFault_IRQn             = -11,              /*!< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                     related Fault                                                             */
  UsageFault_IRQn           = -10,              /*!< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
  SecureFault_IRQn          =  -9,              /*!< -9 Secure Fault Handler                                                   */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  DebugMonitor_IRQn         =  -4,              /*!< -4 Debug Monitor                                                          */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
/* ==========================================  rtl8735B Specific Interrupt Numbers  ========================================== */
  System_IRQn				=   0,              /*!< 00 System Interrupt                                                       */
  ISP_IRQn	        		=   1,              /*!< 01 ISP Interrupt                                                          */
  TIMER_IRQn				=   2,              /*!< 02	Timer Group0 Interrupt								                   */
  TM2KM_IRQn                =   3,              /*!< 03 TM Notify KM Interrupt                                                 */
  GPIO_IRQn                 =   4,              /*!< 04 GPIO Interrupt								                           */
  Encoder_IRQn              =   5,              /*!< 05 Encoder Interrupt													   */
  PWM_IRQn                  =   6,              /*!< 06 PWM Interrupt						                                   */
  ADC_IRQn                  =   7,              /*!< 07	ADC Interrupt								                           */
  ERAC_IRQn                 =   8,              /*!< 08 ERAC Interrupt						                                   */
  UART0_IRQn                =   9,              /*!< 09	UART0 Interrupt								                           */
  I2C3_IRQn                 =  10,              /*!< 10	I2C3 Interrupt								                           */
  GDMA0_IRQn                =  11,              /*!< 11	GDMA0 Interrupt								                           */
  GDMA1_IRQn                =  12,              /*!< 12	GDMA1 Interrupt								                           */
  NN_IRQn                   =  13,              /*!< 13 NN Interrupt 									                       */
  I2C2_IRQn                 =  14,              /*!< 14	I2C2 Interrupt										                   */
  SCRYPTO_IRQn              =  15               /*!< 15 SCrypto Interrupt									                   */
}IRQn_Type;

//typedef int32_t IRQn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the ARM ARMV8MML Processor and Core Peripherals  ============================ */
#define __ARMV8MML_REV                 0x0000U  /*!< ARMV8MML Core Revision                                                    */
#define __NVIC_PRIO_BITS               4        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __VTOR_PRESENT                 1        /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
#define __MPU_PRESENT                  1        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  1        /*!< FPU present or not                                                        */
#define __FPU_DP                       0        /*!< unused, Device has no FPU                                                 */
#define __ICACHE_PRESENT               1        /*!< Instruction Cache present                                                 */
#define __DCACHE_PRESENT               1        /*!< Data Cache present                                                        */
#define __ITCM_PRESENT                 1        /*!< Instruction TCM present                                                   */
#define __DTCM_PRESENT                 1        /*!< Data TCM present                                                          */
#define __SAUREGION_PRESENT            1        /*!< SAU region present                                                        */
#define __DSP_PRESENT                  1        /*!< DSP extension present                                                     */

/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_armv8mml.h"                      /*!< ARM ARMV8MML processor and core peripherals                               */
#include "system_rtl8735b_voe.h"                /*!< rtl8735b_voe System                                                       */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
  #define __IOM  __IO
#endif

//#include "rtl8735b_syson_s_type.h"

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#define CONFIG_GPIO_EN                      1


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                           SYSON                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief HS System Power Control (SYSON)
  */

typedef struct {                                /*!< (@ 0x40000000) SYSON Structure                                            */

  union {
    __IM  uint32_t not_exposed_reg;             /*!< (@ 0x00000000) Registers definition is not exposed                        */

    struct {
      __IM  uint32_t temp       : 32;           /*!< [31..0] temp                                                              */
    } not_exposed_reg_b;
  } ;
} SYSON_Type;                                   /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                          SYSON_S                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief Secure System On (SYSON_S)
  */

typedef struct {                                /*!< (@ 0x50000800) SYSON_S Structure                                          */

  union {
    __IM  uint32_t not_exposed_reg;             /*!< (@ 0x00000000) Registers definition is not exposed                        */

    struct {
      __IM  uint32_t temp       : 32;           /*!< [31..0] temp                                                              */
    } not_exposed_reg_b;
  } ;
} SYSON_S_Type;                                 /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief General Purpose I/O (GPIO)
  */

typedef struct {                                /*!< (@ 0x40001000) GPIO Structure                                             */

  union {
    __IM  uint32_t it_sts;                      /*!< (@ 0x00000000) GPIO interrupt type status Register                        */

    struct {
      __IM  uint32_t gpio_it_sts : 16;          /*!< [15..0] For each bit :0: the specific GPIO pin is configured
                                                     to edge sensitive interrupt mode1: the specific GPIO pin
                                                     is configured to levle sensitive interrupt mode.                          */
            uint32_t            : 16;
    } it_sts_b;
  } ;

  union {
    __IOM uint32_t ei_en;                       /*!< (@ 0x00000004) GPIO edge sensitive interrupt mode enable                  */

    struct {
      __IOM uint32_t ei_en      : 16;           /*!< [15..0] For each bit write: 0: No operation1: the conrtolled
                                                     GPIO pin is configured to edge sensitive interrupt mode
                                                     and also cause the corresponging bit of REG_GPIO_IT_STS
                                                     to be read as 0.                                                          */
            uint32_t            : 16;
    } ei_en_b;
  } ;

  union {
    __IOM uint32_t li_en;                       /*!< (@ 0x00000008) GPIO level sensitive interrupt mode enable                 */

    struct {
      __IOM uint32_t li_en      : 16;           /*!< [15..0] For each bit write: 0: No operation1: the conrtolled
                                                     GPIO pin is configured as level sensitive interrupt mode
                                                     and also cause the corresponging bit of REG_GPIO_IT_STS
                                                     to be read as 1.                                                          */
            uint32_t            : 16;
    } li_en_b;
  } ;

  union {
    __IM  uint32_t ip_sts;                      /*!< (@ 0x0000000C) GPIO interrupt polarity status                             */

    struct {
      __IM  uint32_t ip_sts0    : 2;            /*!< [1..0] The interrupt polarity status of GPIO0                             */
      __IM  uint32_t ip_sts1    : 2;            /*!< [3..2] The interrupt polarity status of GPIO1                             */
      __IM  uint32_t ip_sts2    : 2;            /*!< [5..4] The interrupt polarity status of GPIO2                             */
      __IM  uint32_t ip_sts3    : 2;            /*!< [7..6] The interrupt polarity status of GPIO3                             */
      __IM  uint32_t ip_sts4    : 2;            /*!< [9..8] The interrupt polarity status of GPIO4                             */
      __IM  uint32_t ip_sts5    : 2;            /*!< [11..10] The interrupt polarity status of GPIO5                           */
      __IM  uint32_t ip_sts6    : 2;            /*!< [13..12] The interrupt polarity status of GPIO6                           */
      __IM  uint32_t ip_sts7    : 2;            /*!< [15..14] The interrupt polarity status of GPIO7                           */
      __IM  uint32_t ip_sts8    : 2;            /*!< [17..16] The interrupt polarity status of GPIO8                           */
      __IM  uint32_t ip_sts9    : 2;            /*!< [19..18] The interrupt polarity status of GPIO9                           */
      __IM  uint32_t ip_sts10   : 2;            /*!< [21..20] The interrupt polarity status of GPIO10                          */
      __IM  uint32_t ip_sts11   : 2;            /*!< [23..22] The interrupt polarity status of GPIO11                          */
      __IM  uint32_t ip_sts12   : 2;            /*!< [25..24] The interrupt polarity status of GPIO12                          */
      __IM  uint32_t ip_sts13   : 2;            /*!< [27..26] The interrupt polarity status of GPIO13                          */
      __IM  uint32_t ip_sts14   : 2;            /*!< [29..28] The interrupt polarity status of GPIO14                          */
      __IM  uint32_t ip_sts15   : 2;            /*!< [31..30] The interrupt polarity status of GPIO15                          */
    } ip_sts_b;
  } ;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t ir_en;                       /*!< (@ 0x00000014) GPIO interrupt rising-edge enable                          */

    struct {
      __IOM uint32_t ir_en      : 16;           /*!< [15..0] For each bit write: 0: No operation;1: the conrtolled
                                                     GPIO pin is configured to rising-edge interrupt mode or
                                                     high-level mode (depends on REG_GPIO_IT_STS) and also cause
                                                     the corresponding bits of REG_GPIO_IP_STS to be read as
                                                     00b.                                                                      */
            uint32_t            : 16;
    } ir_en_b;
  } ;

  union {
    __IOM uint32_t if_en;                       /*!< (@ 0x00000018) GPIO interrupt falling-edge enable                         */

    struct {
      __IOM uint32_t if_en      : 16;           /*!< [15..0] For each bit write:0: No operation;1: the conrtolled
                                                     GPIO pin is configured to falling-edge interrupt mode or
                                                     low-level interrupt mode (depends on REG_GPIO_IT_STS) and
                                                     cause the corresponding bits of REG_GPIO_IP_STS to be read
                                                     as 01b.                                                                   */
            uint32_t            : 16;
    } if_en_b;
  } ;

  union {
    __IOM uint32_t id_en;                       /*!< (@ 0x0000001C) GPIO interrupt dual-edge enable                            */

    struct {
      __IOM uint32_t id_en      : 16;           /*!< [15..0] For each bit write:0: No operation;1: the conrtolled
                                                     GPIO pin is configured to dual-edge interrupt mode and
                                                     also cause the corresponding bits of REG_GPIO_IP_STS to
                                                     be read as 10b.                                                           */
            uint32_t            : 16;
    } id_en_b;
  } ;

  union {
    __IM  uint32_t ie_sts;                      /*!< (@ 0x00000020) GPIO interrupt enable status                               */

    struct {
      __IM  uint32_t ie_sts     : 16;           /*!< [15..0] For each bit:0: the interrupt of the specific GPIO pin
                                                     is disabled1: the interrupt of the specific GPIO pin is
                                                     enabled                                                                   */
            uint32_t            : 16;
    } ie_sts_b;
  } ;

  union {
    __IOM uint32_t int_en;                      /*!< (@ 0x00000024) GPIO interrupt enable                                      */

    struct {
      __IOM uint32_t int_en     : 16;           /*!< [15..0] For each bit write:0: No operation1: to enable the specific
                                                     GPIO INT and also cause the specified bit of REG_GPIO_IE_STS
                                                     to be read as ONE.                                                        */
            uint32_t            : 16;
    } int_en_b;
  } ;

  union {
    __IOM uint32_t int_dis;                     /*!< (@ 0x00000028) GPIO interrupt disable                                     */

    struct {
      __IOM uint32_t int_dis    : 16;           /*!< [15..0] For each bit write:0: No operation1: to disable the
                                                     specified the GPIO INT and also cause the specified bit
                                                     of REG_GPIO_IE_STS to be read as ZERO.                                    */
            uint32_t            : 16;
    } int_dis_b;
  } ;

  union {
    __IM  uint32_t int_raw_sts;                 /*!< (@ 0x0000002C) GPIO RAW interrupt status                                  */

    struct {
      __IM  uint32_t int_raw_sts : 16;          /*!< [15..0] For each bit:0: the specified GPIO pin has no pending
                                                     interrupt1: the specified GPIO pin's interrupt is pending
                                                     (permasking)                                                              */
            uint32_t            : 16;
    } int_raw_sts_b;
  } ;

  union {
    __IM  uint32_t int_sts;                     /*!< (@ 0x00000030) GPIO interrupt status                                      */

    struct {
      __IM  uint32_t int_sts    : 16;           /*!< [15..0] For each bit:0: the specified GPIO pin has no pending
                                                     interrupt1: the specified GPIO pin's interrupt is pending                 */
            uint32_t            : 16;
    } int_sts_b;
  } ;

  union {
    __IOM uint32_t int_clr;                     /*!< (@ 0x00000034) GPIO interrupt status clear                                */

    struct {
      __IOM uint32_t int_clr    : 16;           /*!< [15..0] For each bit writting:0: No operation;1: Clear edge
                                                     type pending interrupt of the conrtolled GPIO pin and clear
                                                     the specified bits of REG_GPIO_INT_STS as ZERO                            */
            uint32_t            : 16;
    } int_clr_b;
  } ;

  union {
    __IM  uint32_t int_func_en_sts;             /*!< (@ 0x00000038) GPIO interrupt function enable status                      */

    struct {
      __IM  uint32_t int_en_sts : 16;           /*!< [15..0] For each bit:0: the specified GPIO INT is Disable1:
                                                     the specified GPIO INT is Enable                                          */
            uint32_t            : 16;
    } int_func_en_sts_b;
  } ;

  union {
    __IOM uint32_t int_func_en;                 /*!< (@ 0x0000003C) GPIO interrupt function enable                             */

    struct {
      __IOM uint32_t int_en     : 16;           /*!< [15..0] For each bit write:0: No operation1: the specified GPIO
                                                     INT is enabled and also cause the specified bit of REG_GPIO_INT_FUNC_EN_S
                                                     S to be read as ONE.                                                      */
            uint32_t            : 16;
    } int_func_en_b;
  } ;

  union {
    __IOM uint32_t int_func_dis;                /*!< (@ 0x00000040) GPIO interrupt function disable                            */

    struct {
      __IOM uint32_t int_dis    : 16;           /*!< [15..0] For each bit write:0: No operation1: the specified GPIO
                                                     INT is disabled and also cause the specified bit of REG_GPIO_INT_FUNC_EN_
                                                     TS to be read as ZERO.                                                    */
            uint32_t            : 16;
    } int_func_dis_b;
  } ;
  __IM  uint32_t  RESERVED1[3];

  union {
    __IOM uint32_t int0_sel;                    /*!< (@ 0x00000050) GPIO INT0 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT0                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT0                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT0                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int0_sel_b;
  } ;

  union {
    __IOM uint32_t int1_sel;                    /*!< (@ 0x00000054) GPIO INT1 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT1                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT1                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT1                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int1_sel_b;
  } ;

  union {
    __IOM uint32_t int2_sel;                    /*!< (@ 0x00000058) GPIO INT2 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT2                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT2                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT2                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int2_sel_b;
  } ;

  union {
    __IOM uint32_t int3_sel;                    /*!< (@ 0x0000005C) GPIO INT3 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT3                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT3                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT3                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int3_sel_b;
  } ;

  union {
    __IOM uint32_t int4_sel;                    /*!< (@ 0x00000060) GPIO INT4 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT4                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT4                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT4                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int4_sel_b;
  } ;

  union {
    __IOM uint32_t int5_sel;                    /*!< (@ 0x00000064) GPIO INT5 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT5                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT5                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT5                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int5_sel_b;
  } ;

  union {
    __IOM uint32_t int6_sel;                    /*!< (@ 0x00000068) GPIO INT6 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT6                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT6                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT6                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int6_sel_b;
  } ;

  union {
    __IOM uint32_t int7_sel;                    /*!< (@ 0x0000006C) GPIO INT7 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT7                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT7                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT7                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int7_sel_b;
  } ;

  union {
    __IOM uint32_t int8_sel;                    /*!< (@ 0x00000070) GPIO INT8 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT8                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT8                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT8                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int8_sel_b;
  } ;

  union {
    __IOM uint32_t int9_sel;                    /*!< (@ 0x00000074) GPIO INT9 selection                                        */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT9                      */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT9                                  */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT9                    */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int9_sel_b;
  } ;

  union {
    __IOM uint32_t int10_sel;                   /*!< (@ 0x00000078) GPIO INT10 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT10                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT10                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT10                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int10_sel_b;
  } ;

  union {
    __IOM uint32_t int11_sel;                   /*!< (@ 0x0000007C) GPIO INT11 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT11                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT11                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT11                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int11_sel_b;
  } ;

  union {
    __IOM uint32_t int12_sel;                   /*!< (@ 0x00000080) GPIO INT12 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT12                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT12                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT12                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int12_sel_b;
  } ;

  union {
    __IOM uint32_t int13_sel;                   /*!< (@ 0x00000084) GPIO INT13 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT13                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT13                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT13                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int13_sel_b;
  } ;

  union {
    __IOM uint32_t int14_sel;                   /*!< (@ 0x00000088) GPIO INT14 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT14                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT14                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT14                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int14_sel_b;
  } ;

  union {
    __IOM uint32_t int15_sel;                   /*!< (@ 0x0000008C) GPIO INT15 selection                                       */

    struct {
      __IOM uint32_t int_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for GPIO INT15                     */
      __IOM uint32_t int_gp_sel : 2;            /*!< [6..5] GPIO port selection for GPIO INT15                                 */
            uint32_t            : 1;
      __IOM uint32_t int_deb_sel : 4;           /*!< [11..8] Debounce Output signal selection for GPIO INT15                   */
            uint32_t            : 3;
      __IOM uint32_t int_sur_sel : 1;           /*!< [15..15] 0: Useing pin input signal as interrupt signal source1:
                                                     Using debounce output signal as interrupt signal source                   */
            uint32_t            : 16;
    } int15_sel_b;
  } ;
  __IM  uint32_t  RESERVED2[24];

  union {
    __IM  uint32_t deb_sts;                     /*!< (@ 0x000000F0) GPIO port debounce status                                  */

    struct {
      __IM  uint32_t deb_sts    : 16;           /*!< [15..0] For each bit:0: the specific GPIO debounce pin is DISABLE
                                                     debounce1: the specific GPIO debounce pin is ENABLE debounce              */
            uint32_t            : 16;
    } deb_sts_b;
  } ;

  union {
    __IOM uint32_t deb_en;                      /*!< (@ 0x000000F4) GPIO debounce pin enable                                   */

    struct {
      __IOM uint32_t deb_en     : 16;           /*!< [15..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO de-bouncing pin is enabled and also cause the specified
                                                     bit of REG_GPIO_DEB_STS to be read as ONE.                                */
            uint32_t            : 16;
    } deb_en_b;
  } ;

  union {
    __IOM uint32_t deb_dis;                     /*!< (@ 0x000000F8) GPIO debounce pin disable                                  */

    struct {
      __IOM uint32_t deb_dis    : 16;           /*!< [15..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO de-bouncing pin is disabled and also cause the specified
                                                     bit of REG_GPIO_DEB_STS to be read as ZERO.                               */
            uint32_t            : 16;
    } deb_dis_b;
  } ;

  union {
    __IM  uint32_t deb_dp_sts;                  /*!< (@ 0x000000FC) GPIO debounce data pin status                              */

    struct {
      __IM  uint32_t deb_dp_sts : 16;           /*!< [15..0] For each bit reading:read the signal level of the specified
                                                     pin after de-bounce                                                       */
            uint32_t            : 16;
    } deb_dp_sts_b;
  } ;

  union {
    __IOM uint32_t deb0_sel;                    /*!< (@ 0x00000100) GPIO debounce0 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce0                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce0                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb0_sel_b;
  } ;

  union {
    __IOM uint32_t deb1_sel;                    /*!< (@ 0x00000104) GPIO debounce1 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce1                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce1                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb1_sel_b;
  } ;

  union {
    __IOM uint32_t deb2_sel;                    /*!< (@ 0x00000108) GPIO debounce2 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce2                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce2                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb2_sel_b;
  } ;

  union {
    __IOM uint32_t deb3_sel;                    /*!< (@ 0x0000010C) GPIO debounce3 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce3                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce3                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb3_sel_b;
  } ;

  union {
    __IOM uint32_t deb4_sel;                    /*!< (@ 0x00000110) GPIO debounce4 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce4                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce4                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb4_sel_b;
  } ;

  union {
    __IOM uint32_t deb5_sel;                    /*!< (@ 0x00000114) GPIO debounce5 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce5                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce5                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb5_sel_b;
  } ;

  union {
    __IOM uint32_t deb6_sel;                    /*!< (@ 0x00000118) GPIO debounce6 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce6                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce6                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb6_sel_b;
  } ;

  union {
    __IOM uint32_t deb7_sel;                    /*!< (@ 0x0000011C) GPIO debounce7 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce7                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce7                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb7_sel_b;
  } ;

  union {
    __IOM uint32_t deb8_sel;                    /*!< (@ 0x00000120) GPIO debounce8 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce8                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce8                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb8_sel_b;
  } ;

  union {
    __IOM uint32_t deb9_sel;                    /*!< (@ 0x00000124) GPIO debounce9 selection                                   */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce9                      */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce9                                  */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb9_sel_b;
  } ;

  union {
    __IOM uint32_t deb10_sel;                   /*!< (@ 0x00000128) GPIO debounce10 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce10                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce10                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb10_sel_b;
  } ;

  union {
    __IOM uint32_t deb11_sel;                   /*!< (@ 0x0000012C) GPIO debounce11 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce11                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce11                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb11_sel_b;
  } ;

  union {
    __IOM uint32_t deb12_sel;                   /*!< (@ 0x00000130) GPIO debounce12 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce12                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce12                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb12_sel_b;
  } ;

  union {
    __IOM uint32_t deb13_sel;                   /*!< (@ 0x00000134) GPIO debounce13 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce13                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce13                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb13_sel_b;
  } ;

  union {
    __IOM uint32_t deb14_sel;                   /*!< (@ 0x00000138) GPIO debounce14 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce14                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce14                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb14_sel_b;
  } ;

  union {
    __IOM uint32_t deb15_sel;                   /*!< (@ 0x0000013C) GPIO debounce15 selection                                  */

    struct {
      __IOM uint32_t deb_mer_sel : 5;           /*!< [4..0] Pin selection of specified port for debounce15                     */
      __IOM uint32_t deb_gp_sel : 2;            /*!< [6..5] GPIO port selection for debounce15                                 */
            uint32_t            : 1;
      __IOM uint32_t deb_cyc    : 14;           /*!< [21..8] The GPIO signal will be filtered by the number of debounce
                                                     cycles given in this field.                                               */
            uint32_t            : 10;
    } deb15_sel_b;
  } ;
  __IM  uint32_t  RESERVED3[48];

  union {
    __IM  uint32_t port_a_dmd_sts;              /*!< (@ 0x00000200) GPIO port A data mode direction status                     */

    struct {
      __IM  uint32_t dmd_sts    : 32;           /*!< [31..0] For each bit:0: the specific GPIO pin is configured
                                                     to INPUT data mode1: the specific GPIO pin is configured
                                                     to OUTPUT data mode                                                       */
    } port_a_dmd_sts_b;
  } ;

  union {
    __IOM uint32_t port_a_idm_en;               /*!< (@ 0x00000204) GPIO port A input data mode enable                         */

    struct {
      __IOM uint32_t idm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     to input data mode and also cause the specified bit of
                                                     REG_PORT_A_DMD_STS to be read as zero.                                    */
    } port_a_idm_en_b;
  } ;

  union {
    __IOM uint32_t port_a_odm_en;               /*!< (@ 0x00000208) GPIO port A output data mode enable                        */

    struct {
      __IOM uint32_t odm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     as output data mode and also cause the specified bit of
                                                     REG_PORT_A_DMD_STS to be read as one                                      */
    } port_a_odm_en_b;
  } ;

  union {
    __IM  uint32_t port_a_od_sts;               /*!< (@ 0x0000020C) GPIO port A output data status                             */

    struct {
      __IM  uint32_t od_sts     : 32;           /*!< [31..0] For each bit:0: the specified GPIO pin is configured
                                                     as output low 1: the specified GPIO pin is configured as
                                                     output high, if the specific GPIO pin is output data mode.                */
    } port_a_od_sts_b;
  } ;

  union {
    __IOM uint32_t port_a_odl_en;               /*!< (@ 0x00000210) GPIO port A output data low enable                         */

    struct {
      __IOM uint32_t odl_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output low and also cause the
                                                     specified bit of REG_PORT_A_OD_STS is zero.                               */
    } port_a_odl_en_b;
  } ;

  union {
    __IOM uint32_t port_a_odh_en;               /*!< (@ 0x00000214) GPIO port A output data high enable                        */

    struct {
      __IOM uint32_t odh_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output high and also cause the
                                                     specified bit of REG_PORT_A_OD_STS is one.                                */
    } port_a_odh_en_b;
  } ;

  union {
    __IOM uint32_t port_a_odt_en;               /*!< (@ 0x00000218) GPIO port A output data toggle enable                      */

    struct {
      __IOM uint32_t odt_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: Toggle output of
                                                     the conrtolled GPIO pin and the specified bit of REG_PORT_A_OD_STS
                                                     also will be toggled.                                                     */
    } port_a_odt_en_b;
  } ;

  union {
    __IM  uint32_t port_a_dp_sts;               /*!< (@ 0x0000021C) GPIO port A data pin status                                */

    struct {
      __IM  uint32_t dp_sts     : 32;           /*!< [31..0] For each bit reading:If the direction of the specified
                                                     bit is input then read the signal level of the input pin.If
                                                     the direction of the specified bit is output then reads
                                                     the output data register for port A.                                      */
    } port_a_dp_sts_b;
  } ;
  __IM  uint32_t  RESERVED4[8];

  union {
    __IM  uint32_t port_b_dmd_sts;              /*!< (@ 0x00000240) GPIO port B data mode direction status                     */

    struct {
      __IM  uint32_t dmd_sts    : 32;           /*!< [31..0] For each bit:0: the specific GPIO pin is configured
                                                     to INPUT data mode1: the specific GPIO pin is configured
                                                     to OUTPUT data mode                                                       */
    } port_b_dmd_sts_b;
  } ;

  union {
    __IOM uint32_t port_b_idm_en;               /*!< (@ 0x00000244) GPIO port B input data mode enable                         */

    struct {
      __IOM uint32_t idm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     to input data mode and also cause the specified bit of
                                                     REG_PORT_B_DMD_STS to be read as zero.                                    */
    } port_b_idm_en_b;
  } ;

  union {
    __IOM uint32_t port_b_odm_en;               /*!< (@ 0x00000248) GPIO port B output data mode enable                        */

    struct {
      __IOM uint32_t odm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     as output data mode and also cause the specified bit of
                                                     REG_PORT_B_DMD_STS to be read as one                                      */
    } port_b_odm_en_b;
  } ;

  union {
    __IM  uint32_t port_b_od_sts;               /*!< (@ 0x0000024C) GPIO port B output data status                             */

    struct {
      __IM  uint32_t od_sts     : 32;           /*!< [31..0] For each bit:0: the specified GPIO pin is configured
                                                     as output low 1: the specified GPIO pin is configured as
                                                     output high, if the specific GPIO pin is output data mode.                */
    } port_b_od_sts_b;
  } ;

  union {
    __IOM uint32_t port_b_odl_en;               /*!< (@ 0x00000250) GPIO port B output data low enable                         */

    struct {
      __IOM uint32_t odl_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output low and also cause the
                                                     specified bit of REG_PORT_B_OD_STS is zero.                               */
    } port_b_odl_en_b;
  } ;

  union {
    __IOM uint32_t port_b_odh_en;               /*!< (@ 0x00000254) GPIO port B output data high enable                        */

    struct {
      __IOM uint32_t odh_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output high and also cause the
                                                     specified bit of REG_PORT_B_OD_STS is one.                                */
    } port_b_odh_en_b;
  } ;

  union {
    __IOM uint32_t port_b_odt_en;               /*!< (@ 0x00000258) GPIO port B output data toggle enable                      */

    struct {
      __IOM uint32_t odt_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: Toggle output of
                                                     the conrtolled GPIO pin and the specified bit of REG_PORT_B_OD_STS
                                                     also will be toggled.                                                     */
    } port_b_odt_en_b;
  } ;

  union {
    __IM  uint32_t port_b_dp_sts;               /*!< (@ 0x0000025C) GPIO port B data pin status                                */

    struct {
      __IM  uint32_t dp_sts     : 32;           /*!< [31..0] For each bit reading:If the direction of the specified
                                                     bit is input then read the signal level of the input pin.If
                                                     the direction of the specified bit is output then reads
                                                     the output data register for port B.                                      */
    } port_b_dp_sts_b;
  } ;
  __IM  uint32_t  RESERVED5[8];

  union {
    __IM  uint32_t port_c_dmd_sts;              /*!< (@ 0x00000280) GPIO port C data mode direction status                     */

    struct {
      __IM  uint32_t dmd_sts    : 32;           /*!< [31..0] For each bit:0: the specific GPIO pin is configured
                                                     to INPUT data mode1: the specific GPIO pin is configured
                                                     to OUTPUT data mode                                                       */
    } port_c_dmd_sts_b;
  } ;

  union {
    __IOM uint32_t port_c_idm_en;               /*!< (@ 0x00000284) GPIO port C input data mode enable                         */

    struct {
      __IOM uint32_t idm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     to input data mode and also cause the specified bit of
                                                     REG_PORT_C_DMD_STS to be read as zero.                                    */
    } port_c_idm_en_b;
  } ;

  union {
    __IOM uint32_t port_c_odm_en;               /*!< (@ 0x00000288) GPIO port C output data mode enable                        */

    struct {
      __IOM uint32_t odm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     as output data mode and also cause the specified bit of
                                                     REG_PORT_C_DMD_STS to be read as one                                      */
    } port_c_odm_en_b;
  } ;

  union {
    __IM  uint32_t port_c_od_sts;               /*!< (@ 0x0000028C) GPIO port C output data status                             */

    struct {
      __IM  uint32_t od_sts     : 32;           /*!< [31..0] For each bit:0: the specified GPIO pin is configured
                                                     as output low 1: the specified GPIO pin is configured as
                                                     output high, if the specific GPIO pin is output data mode.                */
    } port_c_od_sts_b;
  } ;

  union {
    __IOM uint32_t port_c_odl_en;               /*!< (@ 0x00000290) GPIO port C output data low enable                         */

    struct {
      __IOM uint32_t odl_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output low and also cause the
                                                     specified bit of REG_PORT_C_OD_STS is zero.                               */
    } port_c_odl_en_b;
  } ;

  union {
    __IOM uint32_t port_c_odh_en;               /*!< (@ 0x00000294) GPIO port C output data high enable                        */

    struct {
      __IOM uint32_t odh_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output high and also cause the
                                                     specified bit of REG_PORT_C_OD_STS is one.                                */
    } port_c_odh_en_b;
  } ;

  union {
    __IOM uint32_t port_c_odt_en;               /*!< (@ 0x00000298) GPIO port C output data toggle enable                      */

    struct {
      __IOM uint32_t odt_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: Toggle output of
                                                     the conrtolled GPIO pin and the specified bit of REG_PORT_C_OD_STS
                                                     also will be toggled.                                                     */
    } port_c_odt_en_b;
  } ;

  union {
    __IM  uint32_t port_c_dp_sts;               /*!< (@ 0x0000029C) GPIO port C data pin status                                */

    struct {
      __IM  uint32_t dp_sts     : 32;           /*!< [31..0] For each bit reading:If the direction of the specified
                                                     bit is input then read the signal level of the input pin.If
                                                     the direction of the specified bit is output then reads
                                                     the output data register for port C.                                      */
    } port_c_dp_sts_b;
  } ;
  __IM  uint32_t  RESERVED6[8];

  union {
    __IM  uint32_t port_d_dmd_sts;              /*!< (@ 0x000002C0) GPIO port D data mode direction status                     */

    struct {
      __IM  uint32_t dmd_sts    : 32;           /*!< [31..0] For each bit:0: the specific GPIO pin is configured
                                                     to INPUT data mode1: the specific GPIO pin is configured
                                                     to OUTPUT data mode                                                       */
    } port_d_dmd_sts_b;
  } ;

  union {
    __IOM uint32_t port_d_idm_en;               /*!< (@ 0x000002C4) GPIO port D input data mode enable                         */

    struct {
      __IOM uint32_t idm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     to input data mode and also cause the specified bit of
                                                     REG_PORT_D_DMD_STS to be read as zero.                                    */
    } port_d_idm_en_b;
  } ;

  union {
    __IOM uint32_t port_d_odm_en;               /*!< (@ 0x000002C8) GPIO port D output data mode enable                        */

    struct {
      __IOM uint32_t odm_en     : 32;           /*!< [31..0] For each bit write:0: the configuration of the conrtolled
                                                     GPIO pin is unchanged;1: the conrtolled GPIO pin is configured
                                                     as output data mode and also cause the specified bit of
                                                     REG_PORT_D_DMD_STS to be read as one                                      */
    } port_d_odm_en_b;
  } ;

  union {
    __IM  uint32_t port_d_od_sts;               /*!< (@ 0x000002CC) GPIO port D output data status                             */

    struct {
      __IM  uint32_t od_sts     : 32;           /*!< [31..0] For each bit:0: the specified GPIO pin is configured
                                                     as output low 1: the specified GPIO pin is configured as
                                                     output high, if the specific GPIO pin is output data mode.                */
    } port_d_od_sts_b;
  } ;

  union {
    __IOM uint32_t port_d_odl_en;               /*!< (@ 0x000002D0) GPIO port D output data low enable                         */

    struct {
      __IOM uint32_t odl_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output low and also cause the
                                                     specified bit of REG_PORT_D_OD_STS is zero.                               */
    } port_d_odl_en_b;
  } ;

  union {
    __IOM uint32_t port_d_odh_en;               /*!< (@ 0x000002D4) GPIO port D output data high enable                        */

    struct {
      __IOM uint32_t odh_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: the conrtolled
                                                     GPIO pin is configured as output high and also cause the
                                                     specified bit of REG_PORT_D_OD_STS is one.                                */
    } port_d_odh_en_b;
  } ;

  union {
    __IOM uint32_t port_d_odt_en;               /*!< (@ 0x000002D8) GPIO port D output data toggle enable                      */

    struct {
      __IOM uint32_t odt_en     : 32;           /*!< [31..0] For each bit write:0: No operation1: Toggle output of
                                                     the conrtolled GPIO pin and the specified bit of REG_PORT_D_OD_STS
                                                     also will be toggled.                                                     */
    } port_d_odt_en_b;
  } ;

  union {
    __IM  uint32_t port_d_dp_sts;               /*!< (@ 0x000002DC) GPIO port D data pin status                                */

    struct {
      __IM  uint32_t dp_sts     : 32;           /*!< [31..0] For each bit reading:If the direction of the specified
                                                     bit is input then read the signal level of the input pin.If
                                                     the direction of the specified bit is output then reads
                                                     the output data register for port D.                                      */
    } port_d_dp_sts_b;
  } ;
} GPIO_Type;                                    /*!< Size = 736 (0x2e0)                                                        */



/* =========================================================================================================================== */
/* ================                                           COMP                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 4-channel comparator (COMP)
  */

typedef struct {                                /*!< (@ 0x4000AC00) COMP Structure                                             */

  union {
    __IOM uint32_t ref_ch0;                     /*!< (@ 0x00000000) Comparator Channel 0 Reference Volatage Register           */

    struct {
      __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 0 internal reference
                                                     voltage 0.Vref0 is equal to (the value of BIT_COMP_REF0)
                                                     * 0.1V.Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.5V.
                                                     When BIT_COMP_REF0 is 30, Vref0 is 3.0V.0x00: Vref0 is
                                                     0V.0x01: Vref0 is 0.1V.0x02: Vref0 is 0.2V . . .                          */
            uint32_t            : 8;
      __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 0 internal
                                                     reference voltage 1.Vref1 is equal to (the value of BIT_COMP_REF1)
                                                     * 0.1V.Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.5V.
                                                     When BIT_COMP_REF1 is 30, Vref1 is 3.0V.0x00: Vref1 is
                                                     0V.0x01: Vref1 is 0.1V.0x02: Vref1 is 0.2V . . .                          */
            uint32_t            : 8;
    } ref_ch0_b;
  } ;

  union {
    __IOM uint32_t ref_ch1;                     /*!< (@ 0x00000004) Comparator Channel 1 Reference Volatage Register           */

    struct {
      __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 1 internal reference
                                                     voltage 0.Vref0 is equal to (the value of BIT_COMP_REF0)
                                                     * 0.1V.Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.5V.
                                                     When BIT_COMP_REF0 is 30, Vref0 is 3.0V.0x00: Vref0 is
                                                     0V.0x01: Vref0 is 0.1V.0x02: Vref0 is 0.2V . . .                          */
            uint32_t            : 8;
      __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 1 internal
                                                     reference voltage 1.Vref1 is equal to (the value of BIT_COMP_REF1)
                                                     * 0.1V.Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.5V.
                                                     When BIT_COMP_REF1 is 30, Vref1 is 3.0V.0x00: Vref1 is
                                                     0V.0x01: Vref1 is 0.1V.0x02: Vref1 is 0.2V . . .                          */
            uint32_t            : 8;
    } ref_ch1_b;
  } ;

  union {
    __IOM uint32_t ref_ch2;                     /*!< (@ 0x00000008) Comparator Channel 2 Reference Volatage Register           */

    struct {
      __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 2 internal reference
                                                     voltage 0.Vref0 is equal to (the value of BIT_COMP_REF0)
                                                     * 0.1V.Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.5V.
                                                     When BIT_COMP_REF0 is 30, Vref0 is 3.0V.0x00: Vref0 is
                                                     0V.0x01: Vref0 is 0.1V.0x02: Vref0 is 0.2V . . .                          */
            uint32_t            : 8;
      __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 2 internal
                                                     reference voltage 1.Vref1 is equal to (the value of BIT_COMP_REF1)
                                                     * 0.1V.Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.5V.
                                                     When BIT_COMP_REF1 is 30, Vref1 is 3.0V.0x00: Vref1 is
                                                     0V.0x01: Vref1 is 0.1V.0x02: Vref1 is 0.2V . . .                          */
            uint32_t            : 8;
    } ref_ch2_b;
  } ;

  union {
    __IOM uint32_t ref_ch3;                     /*!< (@ 0x0000000C) Comparator Channel 3 Reference Volatage Register           */

    struct {
      __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 3 internal reference
                                                     voltage 0.Vref0 is equal to (the value of BIT_COMP_REF0)
                                                     * 0.1V.Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.5V.
                                                     When BIT_COMP_REF0 is 30, Vref0 is 3.0V.0x00: Vref0 is
                                                     0V.0x01: Vref0 is 0.1V.0x02: Vref0 is 0.2V . . .                          */
            uint32_t            : 8;
      __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 3 internal
                                                     reference voltage 1.Vref1 is equal to (the value of BIT_COMP_REF1)
                                                     * 0.1V.Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.5V.
                                                     When BIT_COMP_REF1 is 30, Vref1 is 3.0V.0x00: Vref1 is
                                                     0V.0x01: Vref1 is 0.1V.0x02: Vref1 is 0.2V . . .                          */
            uint32_t            : 8;
    } ref_ch3_b;
  } ;

  union {
    __IOM uint32_t intr_ctrl;                   /*!< (@ 0x00000010) Comparator Interrupt Control Register                      */

    struct {
      __IOM uint32_t wk_sys_en_0 : 1;           /*!< [0..0] This bit controls whether the comparator channel 0 sends
                                                     wakeup signal or not when the criterion of BIT_COMP_WK_SYS_CTRL
                                                     matches.0: Disable comparator interrupt (wake up) system.1:
                                                     Enable comparator interrupt (wake up) system.                             */
      __IOM uint32_t wk_sys_ctrl_0 : 2;         /*!< [2..1] This bit defines the criterion of when comparator channel
                                                     0 should interrupt (wake up) system. The comparator should
                                                     send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if
                                                     the criterion matches.0: When Vin < Vref0, the comparator
                                                     interrupts (wake up) system.1: When Vin > Vref1, the Comparator
                                                     interrupts (wake up) system.2: When Vin > Vref0 and Vin
                                                     < Vref1, the Comparator interrupts (wake up) system.3:
                                                     When Vin < Vref0 or Vin > Vref1, the Comparator interrupts
                                                     (wake up) system.                                                         */
      __IOM uint32_t wk_sys_en_1 : 1;           /*!< [3..3] This bit controls whether the comparator channel 1 sends
                                                     interrupt (wake up) signal or not when the criterion of
                                                     BIT_COMP_WK_SYS_CTRL matches.0: Disable comparator interrupt
                                                     (wake up) system.1: Enable comparator interrupt (wake up)
                                                     system.                                                                   */
      __IOM uint32_t wk_sys_ctrl_1 : 2;         /*!< [5..4] This bit defines the criterion of when comparator channel
                                                     1 should interrupt (wake up) system. The comparator should
                                                     send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if
                                                     the criterion matches.0: When Vin < Vref0, the comparator
                                                     interrupt (wake up) system.1: When Vin > Vref1, the Comparator
                                                     interrupt (wake up) system.2: When Vin > Vref0 and Vin
                                                     < Vref1, the Comparator interrupts (wake up) system.3:
                                                     When Vin < Vref0 or Vin > Vref1, the Comparator interrupts
                                                     (wake up) system.                                                         */
      __IOM uint32_t wk_sys_en_2 : 1;           /*!< [6..6] This bit controls whether the comparator channel 2 sends
                                                     interrupt (wake up) signal or not when the criterion of
                                                     BIT_COMP_WK_SYS_CTRL matches.0: Disable comparator interrupt
                                                     (wake up) system.1: Enable comparator interrupt (wake up)
                                                     system.                                                                   */
      __IOM uint32_t wk_sys_ctrl_2 : 2;         /*!< [8..7] This bit defines the criterion of when comparator channel
                                                     2 should interrupt (wake up) system. The comparator should
                                                     send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if
                                                     the criterion matches.0: When Vin < Vref0, the comparator
                                                     interrupts (wake up) system.1: When Vin >= Vref1, the Comparator
                                                     interrupts (wake up) system.2: When Vin > Vref0 and Vin
                                                     < Vref1, the Comparator interrupts (wake up) system.3:
                                                     When Vin < Vref0 or Vin > Vref1, the Comparator interrupts
                                                     (wake up) system.                                                         */
      __IOM uint32_t wk_sys_en_3 : 1;           /*!< [9..9] This bit controls whether the comparator channel 3 sends
                                                     interrupt (wake up) signal or not when the criterion of
                                                     BIT_COMP_WK_SYS_CTRL matches.0: Disable comparator interrupt
                                                     (wake up) system.1: Enable comparator interrupt (wake up)
                                                     system.                                                                   */
      __IOM uint32_t wk_sys_ctrl_3 : 2;         /*!< [11..10] This bit defines the criterion of when comparator channel
                                                     3 should interrupts (wake up) system. The comparator should
                                                     send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if
                                                     the criterion matches.0: When Vin < Vref0, the comparator
                                                     interrupts (wake up) system.1: When Vin > Vref1, the Comparator
                                                     interrupts (wake up) system.2: When Vin > Vref0 and Vin
                                                     < Vref1, the Comparator interrupts (wake up) system.3:
                                                     When Vin < Vref0 or Vin > Vref1, the Comparator interrupts
                                                     (wake up) system.                                                         */
            uint32_t            : 20;
    } intr_ctrl_b;
  } ;

  union {
    __IOM uint32_t intr_sts;                    /*!< (@ 0x00000014) Comparator Interrupt Status Register                       */

    struct {
      __IOM uint32_t wk_sys_sts_0 : 1;          /*!< [0..0] This bit reflects if channle 0 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     0 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 0 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IOM uint32_t wk_sys_sts_1 : 1;          /*!< [3..3] This bit reflects if channle 1 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     1 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 1 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IOM uint32_t wk_sys_sts_2 : 1;          /*!< [6..6] This bit reflects if channle 2 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     2 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 2 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IOM uint32_t wk_sys_sts_3 : 1;          /*!< [9..9] This bit reflects if channle 3 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     3 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 3 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 22;
    } intr_sts_b;
  } ;

  union {
    __IM  uint32_t intr_raw_sts;                /*!< (@ 0x00000018) Comparator Interrupt RAW Status Register                   */

    struct {
      __IM  uint32_t wk_sys_sts_0 : 1;          /*!< [0..0] This bit reflects if channle 0 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     0 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 0 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IM  uint32_t wk_sys_sts_1 : 1;          /*!< [3..3] This bit reflects if channle 1 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     1 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 1 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IM  uint32_t wk_sys_sts_2 : 1;          /*!< [6..6] This bit reflects if channle 2 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     2 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 2 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 2;
      __IM  uint32_t wk_sys_sts_3 : 1;          /*!< [9..9] This bit reflects if channle 3 of comparator module sent
                                                     a interrupt (wake-up) signal to system or not.0: Channel
                                                     3 did NOT send an interrupt (wake-up) signal to system.1:
                                                     Channel 3 has sent an interrupt (wake-up) signal to system.               */
            uint32_t            : 22;
    } intr_raw_sts_b;
  } ;

  union {
    __IOM uint32_t chsw_list;                   /*!< (@ 0x0000001C) Comparator Channel Switch List Register                    */

    struct {
      __IOM uint32_t chsw_0     : 4;            /*!< [3..0] These bits defines the 1st channel to do a comparison
                                                     when the start-compare event takes place.                                 */
      __IOM uint32_t chsw_1     : 4;            /*!< [7..4] These bits defines the 2nd channel to do a comparison
                                                     when the start-compare event takes place.                                 */
      __IOM uint32_t chsw_2     : 4;            /*!< [11..8] These bits defines the 3rd channel to do a comparison
                                                     when the start-compare event takes place.                                 */
      __IOM uint32_t chsw_3     : 4;            /*!< [15..12] These bits defines the 4th channel to do a comparison
                                                     when the start-compare event takes place.                                 */
            uint32_t            : 16;
    } chsw_list_b;
  } ;

  union {
    __IOM uint32_t last_ch;                     /*!< (@ 0x00000020) Comparator Last Channel Register                           */

    struct {
      __IOM uint32_t last_ch    : 2;            /*!< [1..0] These bits reflects the last used channel.                         */
            uint32_t            : 30;
    } last_ch_b;
  } ;

  union {
    __IM  uint32_t busy;                        /*!< (@ 0x00000024) Comparator Busy Status Register                            */

    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] This bit reflects the comparator is busy or not. If the
                                                     comparator is processing a comparison of a channel, this
                                                     bit remains 1 which indicates it's busy. Once a comparison
                                                     is done, this bit becomes 0 which indicates its' ready
                                                     to do another comparison.0: The comparator is ready.1:
                                                     The comparator is busy.                                                   */
            uint32_t            : 31;
    } busy_b;
  } ;

  union {
    __IM  uint32_t ch_sts;                      /*!< (@ 0x00000028) Comparator Channel Status Register                         */

    struct {
      __IM  uint32_t ch_sts_0   : 2;            /*!< [1..0] This bit reflects the channel 0 comparison result.0:
                                                     When Vin < Vref0, the bits should be set to 0.1: When Vin
                                                     >= Vref1, the bits should be set to 1.2:When Vin > Vref0
                                                     and Vin < Vref1, the bits should be set to 2.                             */
      __IM  uint32_t ch_sts_1   : 2;            /*!< [3..2] This bit reflects the channel 1 comparison result.0:
                                                     When Vin < Vref0, the bits should be set to 0.1: When Vin
                                                     >= Vref1, the bits should be set to 1.2:When Vin > Vref0
                                                     and Vin < Vref1, the bits should be set to 2.                             */
      __IM  uint32_t ch_sts_2   : 2;            /*!< [5..4] This bit reflects the channel 2 comparison result.0:
                                                     When Vin < Vref0, the bits should be set to 0.1: When Vin
                                                     >= Vref1, the bits should be set to 1.2:When Vin > Vref0
                                                     and Vin < Vref1, the bits should be set to 2.                             */
      __IM  uint32_t ch_sts_3   : 2;            /*!< [7..6] This bit reflects the channel 3 comparison result.0:
                                                     When Vin < Vref0, the bits should be set to 0.1: When Vin
                                                     >= Vref1, the bits should be set to 1.2:When Vin > Vref0
                                                     and Vin < Vref1, the bits should be set to 2.                             */
            uint32_t            : 24;
    } ch_sts_b;
  } ;

  union {
    __IOM uint32_t auto_shut;                   /*!< (@ 0x0000002C) Comparator Auto Shutdown Register                          */

    struct {
      __IOM uint32_t auto_shut  : 1;            /*!< [0..0] This bit controls the comparator to disable the analog
                                                     module and mux automatically or not after the analog conversion
                                                     is done.0: The analog module and mux will NOT be disabled.The
                                                     comparator module is always enabled.1: The analog module
                                                     and mux will be disabled automatically after the analog
                                                     conversion is done.                                                       */
            uint32_t            : 31;
    } auto_shut_b;
  } ;

  union {
    __IOM uint32_t wk_timer;                    /*!< (@ 0x00000030) Comparator Wake Timer Control Reigster                     */

    struct {
      __IOM uint32_t wk_timer   : 1;            /*!< [0..0] This bit controls the external trigger source of general
                                                     timer enabled or not.If it is enabled, the comparator would
                                                     execute compare process when the timer event sends to comparator
                                                     module.0: Disable external timer trigger1: Enable external
                                                     timer trigger                                                             */
            uint32_t            : 31;
    } wk_timer_b;
  } ;

  union {
    __IOM uint32_t wk_timer_sel;                /*!< (@ 0x00000034) Comparator Wake Timer Select Reigster                      */

    struct {
      __IOM uint32_t wk_timer_sel : 2;          /*!< [1..0] This three bits defines which timer channel would be
                                                     used to wake up the comparator.BIT_COMP_EXT_WK_TIMER_SEL
                                                     is 0: Timer module 0 is used as the comparator external
                                                     trigger source.1: Timer module 1 is used as the comparator
                                                     external trigger source. . . .3: Timer module 3 is used
                                                     as the comparator external trigger source.                                */
            uint32_t            : 30;
    } wk_timer_sel_b;
  } ;

  union {
    __IOM uint32_t rst_list;                    /*!< (@ 0x00000038) Comparator Rest List Register                              */

    struct {
      __IOM uint32_t rst_list   : 1;            /*!< [0..0] This bit controls to reset the channel switch to default
                                                     state or not. Once this bit is set, the auto/manual channel
                                                     switch goes to the first channel as a default state.0:
                                                     Do not reset conversion list to default state.1: Reset
                                                     conversion list to default state.                                         */
            uint32_t            : 31;
    } rst_list_b;
  } ;

  union {
    __IOM uint32_t auto_sw_en;                  /*!< (@ 0x0000003C) Comparator Auto Channel Switch Enable Reigster             */

    struct {
      __IOM uint32_t auto_sw_en : 1;            /*!< [0..0] This bit controls the automatic channel swtich enabled
                                                     or disabled.If it's disabled, comparator could be run in
                                                     software or timer trigger mode.0: Disable the automatic
                                                     channel switch. 1: Enable the automatic channel switch.                   */
            uint32_t            : 31;
    } auto_sw_en_b;
  } ;

  union {
    __IOM uint32_t enable;                      /*!< (@ 0x00000040) Comparator Enable Control Register                         */

    struct {
      __IOM uint32_t enable     : 1;            /*!< [0..0] This bit is for comparator enable control.                         */
      __IOM uint32_t trig_en    : 1;            /*!< [1..1] This bit is a mulitple trigger control source.For software
                                                     trigger (when comparator auto channel switch register (offset:
                                                     0x3C) is NOT set and wake timer control is NOT set), this
                                                     bit is used to be a software trigger source. Each time
                                                     this bit is set to 1 from 0, it drives comparator to do
                                                     a channel comparison.For auto trigger, this bit is used
                                                     to drive comparator to start the auto channel switch operation.           */
            uint32_t            : 30;
    } enable_b;
  } ;

  union {
    __IOM uint32_t wk_shut_cnt;                 /*!< (@ 0x00000044) Comparator Shutdown Counter Register                       */

    struct {
      __IOM uint32_t wk_shut_cnt : 8;           /*!< [7..0] This eight bits defines how long to disable comparator
                                                     analog module when an external trigger event is sent to
                                                     the comparator. The count must include the comparator response
                                                     time to get a correct compare result.                                     */
            uint32_t            : 24;
    } wk_shut_cnt_b;
  } ;
} COMP_Type;                                    /*!< Size = 72 (0x48)                                                          */



/* =========================================================================================================================== */
/* ================                                            TG0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief General Purpose Timer Group Control (TG0)
  */

typedef struct {                                /*!< (@ 0x40002000) TG0 Structure                                              */

  union {
    __IM  uint32_t ists;                        /*!< (@ 0x00000000) Timer Group interrupt status register                      */

    struct {
      __IM  uint32_t ists       : 8;            /*!< [7..0] Each bit indicates the interrupt pending status of corresponding
                                                     timer:0: the specifiied timer has no interrupt pending1:
                                                     the specifiied timer has pending interrupt                                */
            uint32_t            : 24;
    } ists_b;
  } ;

  union {
    __IM  uint32_t raw_ists;                    /*!< (@ 0x00000004) Timer Group raw interrupt status register                  */

    struct {
      __IM  uint32_t rists      : 8;            /*!< [7..0] Each bit indicates the interrupt pending status of corresponding
                                                     timer:0: the specifiied timer has no interrupt pending1:
                                                     the specifiied timer has pending interrupt (pre-masing)                   */
            uint32_t            : 24;
    } raw_ists_b;
  } ;

  union {
    __IOM uint32_t tsel;                        /*!< (@ 0x00000008) Timer Group indirect read control register                 */

    struct {
      __IOM uint32_t tsel       : 3;            /*!< [2..0] The timer index in a timer group, to select the timer
                                                     for indirect read.                                                        */
            uint32_t            : 1;
      __IOM uint32_t sync_mode  : 1;            /*!< [4..4] Sync mode between Timer clock and APB clock0: Freq. of
                                                     APB clock >> Freq. of Timer clock (about 10 times)1: others               */
            uint32_t            : 2;
      __IOM uint32_t poll       : 1;            /*!< [7..7] Set this bit to enable indirect read current value of
                                                     timer selected by tsel. This bit is cleared by HW while
                                                     finishing read and indicate REG_TIMER_TC is ready                         */
            uint32_t            : 24;
    } tsel_b;
  } ;

  union {
    __IM  uint32_t tc;                          /*!< (@ 0x0000000C) Timer Group indirect read timer counter register           */

    struct {
      __IM  uint32_t timer_tc   : 32;           /*!< [31..0] Current counter value of the specifiied timer by register
                                                     tg_tsel.                                                                  */
    } tc_b;
  } ;
} TG_Type;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                            TM0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief General Purpose Timer0 (TM0)
  */

typedef struct {                                /*!< (@ 0x40002040) TM0 Structure                                              */

  union {
    __IOM uint32_t lc;                          /*!< (@ 0x00000000) Timer load count register                                  */

    struct {
      __IOM uint32_t lc         : 32;           /*!< [31..0] The counter value to be loaded into the timer counter
                                                     when timer is enabled or reset.Min = 0, when prescaler
                                                     register > 0; otherwise Min = 1.                                          */
    } lc_b;
  } ;

  union {
    __IOM uint32_t tc;                          /*!< (@ 0x00000004) Timer current counter register                             */

    struct {
      __IOM uint32_t tc         : 32;           /*!< [31..0] Current counter value.                                            */
    } tc_b;
  } ;

  union {
    __IOM uint32_t pc;                          /*!< (@ 0x00000008) Timer prescaler counter register                           */

    struct {
      __IOM uint32_t pc         : 10;           /*!< [9..0] Pre-scaler counter will be increased every clock after
                                                     timer is enabled. When the prescaler counter is equal to
                                                     PR, the next clock increments (decrements) the TC and clears
                                                     the PC.                                                                   */
            uint32_t            : 22;
    } pc_b;
  } ;

  union {
    __IOM uint32_t pr;                          /*!< (@ 0x0000000C) Timer prescaler register                                   */

    struct {
      __IOM uint32_t pr         : 10;           /*!< [9..0] When the PC is equal to this value, the next clock increments
                                                     (decrements) the TC and clears the PC.                                    */
            uint32_t            : 22;
    } pr_b;
  } ;

  union {
    __IOM uint32_t ctrl;                        /*!< (@ 0x00000010) Timer control register                                     */

    struct {
      __IOM uint32_t en         : 1;            /*!< [0..0] Timer enable control:0: Disable1: Enable                           */
      __IOM uint32_t mod        : 1;            /*!< [1..1] Timer operation mode:0: timer mode (periodical mode);
                                                     it reloads LC to TC and repeat the process according to
                                                     the setting when the timeout event occurred.1: counter
                                                     mode (one-shot mode); only one time process.                              */
      __IOM uint32_t imr        : 1;            /*!< [2..2] Timer Interrupt mask:0: disable interrupt1: enable interrupt       */
      __IOM uint32_t cnt_mod    : 1;            /*!< [3..3] Timer counting mode:0: Up-counter1: Down-counter                   */
            uint32_t            : 28;
    } ctrl_b;
  } ;

  union {
    __IOM uint32_t isr;                         /*!< (@ 0x00000014) Timer0 interrupt status register                           */

    struct {
      __IOM uint32_t timeout    : 1;            /*!< [0..0] Timeout interrupt                                                  */
      __IOM uint32_t match_ev0  : 1;            /*!< [1..1] Counter value match event0 interrupt.                              */
      __IOM uint32_t match_ev1  : 1;            /*!< [2..2] Counter value match event1 interrupt.                              */
      __IOM uint32_t match_ev2  : 1;            /*!< [3..3] Counter value match event2 interrupt.                              */
      __IOM uint32_t match_ev3  : 1;            /*!< [4..4] Counter value match event3 interrupt.                              */
            uint32_t            : 27;
    } isr_b;
  } ;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t mectrl;                      /*!< (@ 0x0000001C) Timer match event control register                         */

    struct {
      __IOM uint32_t me0_en     : 1;            /*!< [0..0] Counter value match event0 enable control:0: Disable1:
                                                     Enable                                                                    */
      __IOM uint32_t me1_en     : 1;            /*!< [1..1] Counter value match event1 enable control:0: Disable1:
                                                     Enable                                                                    */
      __IOM uint32_t me2_en     : 1;            /*!< [2..2] Counter value match event2 enable control:0: Disable1:
                                                     Enable                                                                    */
      __IOM uint32_t me3_en     : 1;            /*!< [3..3] Counter value match event3 enable control:0: Disable1:
                                                     Enable                                                                    */
            uint32_t            : 28;
    } mectrl_b;
  } ;

  union {
    __IOM uint32_t me0;                         /*!< (@ 0x00000020) Timer match event0 counter register                        */

    struct {
      __IOM uint32_t me0        : 32;           /*!< [31..0] Timer counter value for metch event0.                             */
    } me0_b;
  } ;

  union {
    __IOM uint32_t me1;                         /*!< (@ 0x00000024) Timer match event1 counter register                        */

    struct {
      __IOM uint32_t me1        : 32;           /*!< [31..0] Timer counter value for metch event1.                             */
    } me1_b;
  } ;

  union {
    __IOM uint32_t me2;                         /*!< (@ 0x00000028) Timer match event2 counter register                        */

    struct {
      __IOM uint32_t me2        : 32;           /*!< [31..0] Timer counter value for metch event2.                             */
    } me2_b;
  } ;

  union {
    __IOM uint32_t me3;                         /*!< (@ 0x0000002C) Timer match event3 counter register                        */

    struct {
      __IOM uint32_t me3        : 32;           /*!< [31..0] Timer counter value for metch event3.                             */
    } me3_b;
  } ;
} TM_Type;                                     /*!< Size = 48 (0x30)                                                          */



/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Real Time Clock (RTC) (RTC)
  */

typedef struct {                                /*!< (@ 0x4000A400) RTC Structure                                              */

  union {
    __IOM uint32_t cmd;                         /*!< (@ 0x00000000) REG_AON_LSFIF_CMD                                          */

    struct {
      __IOM uint32_t lsfif_ad   : 16;           /*!< [15..0] BIT_AON_LSFIF_AD[15:8]=8'h00: RTC register base address           */
            uint32_t            : 8;
      __IOM uint32_t lsfif_we   : 4;            /*!< [27..24] LSF register byte write enable. This field is valid
                                                     during LSF register write transfer, and is ignored during
                                                     LSF register read transfer                                                */
      __IOM uint32_t lsfif_wr   : 1;            /*!< [28..28] LSF register write transfer indicator. 1: LSF register
                                                     write transfer, 0: LSF register read transfer                             */
            uint32_t            : 2;
      __IOM uint32_t lsfif_poll : 1;            /*!< [31..31] Set this bit to do LSF register read or write transfer
                                                     depend on BIT_AON_LSFIF_WR. When transfer done, this bit
                                                     will be clear by HW                                                       */
    } cmd_b;
  } ;

  union {
    __IOM uint32_t lsfif_rwd;                   /*!< (@ 0x00000004) REG_AON_LSFIF_RWD                                          */

    struct {
      __IOM uint32_t lsfif_rwd  : 32;           /*!< [31..0] LSF(low speed function) write                                     */
    } lsfif_rwd_b;
  } ;

  union {
    __IOM uint32_t imr;                         /*!< (@ 0x00000008) REG_AON_RTC_IMR                                            */

    struct {
      __IOM uint32_t cnt_sec_imr : 1;           /*!< [0..0] Interrupt mask of RTC seconds counter                              */
      __IOM uint32_t cnt_min_imr : 1;           /*!< [1..1] Interrupt mask of RTC minutes counter                              */
      __IOM uint32_t cnt_hrs_imr : 1;           /*!< [2..2] Interrupt mask of RTC hours counter                                */
      __IOM uint32_t cnt_dow_imr : 1;           /*!< [3..3] Interrupt mask of RTC day of week counter                          */
      __IOM uint32_t cnt_dom_imr : 1;           /*!< [4..4] Interrupt mask of RTC day of month counter                         */
      __IOM uint32_t cnt_mth_imr : 1;           /*!< [5..5] Interrupt mask of RTC month counter                                */
      __IOM uint32_t cnt_yrs_imr : 1;           /*!< [6..6] Interrupt mask of RTC years counter                                */
      __IOM uint32_t cnt_doy_imr : 1;           /*!< [7..7] Interrupt mask of RTC day of year counter                          */
      __IOM uint32_t alrm_sec_imr : 1;          /*!< [8..8] Interrupt mask of RTC second alarm                                 */
      __IOM uint32_t alrm_min_imr : 1;          /*!< [9..9] Interrupt mask of RTC minute alarm                                 */
      __IOM uint32_t alrm_hrs_imr : 1;          /*!< [10..10] Interrupt mask of RTC hour alarm                                 */
      __IOM uint32_t alrm_dow_imr : 1;          /*!< [11..11] Interrupt mask of RTC day of week alarm                          */
      __IOM uint32_t alrm_dom_imr : 1;          /*!< [12..12] Interrupt mask of RTC day of month alarm                         */
      __IOM uint32_t alrm_mth_imr : 1;          /*!< [13..13] Interrupt mask of RTC month alarm                                */
      __IOM uint32_t alrm_yrs_imr : 1;          /*!< [14..14] Interrupt mask of RTC year alarm                                 */
      __IOM uint32_t alrm_doy_imr : 1;          /*!< [15..15] Interrupt mask of RTC day of year alarm                          */
      __IOM uint32_t alrm_imr   : 1;            /*!< [16..16] Interrupt mask of RTC alarm                                      */
            uint32_t            : 15;
    } imr_b;
  } ;

  union {
    __IOM uint32_t isr;                         /*!< (@ 0x0000000C) REG_AON_RTC_ISR                                            */

    struct {
      __IOM uint32_t cnt_sec_isr : 1;           /*!< [0..0] Indicate increment of the second timer                             */
      __IOM uint32_t cnt_min_isr : 1;           /*!< [1..1] Indicate increment of the minute timer                             */
      __IOM uint32_t cnt_hrs_isr : 1;           /*!< [2..2] Indicate increment of the hour timer                               */
      __IOM uint32_t cnt_dow_isr : 1;           /*!< [3..3] Indicate increment of the day-of-week timer                        */
      __IOM uint32_t cnt_dom_isr : 1;           /*!< [4..4] Indicate increment of the day-of-month timer                       */
      __IOM uint32_t cnt_mth_isr : 1;           /*!< [5..5] Indicate increment of the month timer                              */
      __IOM uint32_t cnt_yrs_isr : 1;           /*!< [6..6] Indicate increment of the year timer                               */
      __IOM uint32_t cnt_doy_isr : 1;           /*!< [7..7] Indicate increment of the Day-of-year timer                        */
      __IOM uint32_t alrm_sec_isr : 1;          /*!< [8..8] Indicate Second timer value match ALRM_SEC                         */
      __IOM uint32_t alrm_min_isr : 1;          /*!< [9..9] Indicate Minute timer value match ALRM_MIN                         */
      __IOM uint32_t alrm_hrs_isr : 1;          /*!< [10..10] Indicate Hour timer value match ALRM_HRS                         */
      __IOM uint32_t alrm_dow_isr : 1;          /*!< [11..11] Indicate DOW timer value match ALRM_DOW                          */
      __IOM uint32_t alrm_dom_isr : 1;          /*!< [12..12] Indicate DOM timer value match ALRM_DOM                          */
      __IOM uint32_t alrm_mth_isr : 1;          /*!< [13..13] Indicate MTH timer value match ALRM_MTH                          */
      __IOM uint32_t alrm_yrs_isr : 1;          /*!< [14..14] Indicate Year timer value match ALRM_YRS                         */
      __IOM uint32_t alrm_doy_isr : 1;          /*!< [15..15] Indicate DOY timer value match ALRM_DOY                          */
      __IOM uint32_t alrm_isr   : 1;            /*!< [16..16] Indicate ALL timer value match ALRM value                        */
            uint32_t            : 15;
    } isr_b;
  } ;
} RTC_Type;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                         PWM_COMM                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief PWM Group Control (PWM_COMM)
  */

typedef struct {                                /*!< (@ 0x40045000) PWM_COMM Structure                                         */

  union {
    __IM  uint32_t enable_status;               /*!< (@ 0x00000000) PWM enable status Register                                 */

    struct {
      __IM  uint32_t pwm_en_sts : 12;           /*!< [11..0] Each bit indicates the enabling status of corresponding
                                                     PWM:0: the specific PWM is Disabled1: the specific PWM
                                                     is Enabled                                                                */
            uint32_t            : 20;
    } enable_status_b;
  } ;

  union {
    __IOM uint32_t enable_ctrl;                 /*!< (@ 0x00000004) PWM enable Register                                        */

    struct {
      __IOM uint32_t pwm_en     : 12;           /*!< [11..0] Each bit is used to enablel the corresponding PWM function:When
                                                     wrote 0: No operation1: the specific PWM is enabled and
                                                     the specific bit of REG_PWM_EN_STS is ONE.                                */
            uint32_t            : 20;
    } enable_ctrl_b;
  } ;

  union {
    __IOM uint32_t disable_ctrl;                /*!< (@ 0x00000008) PWM disable Register                                       */

    struct {
      __IOM uint32_t pwm_dis    : 12;           /*!< [11..0] Each bit is used to disable the corresponding PW6M function:When
                                                     wrote 0: No operation1: the conrtolled PWM is disabled
                                                     and the specific bit of REG_PWM_EN_STS is ZERO.                           */
            uint32_t            : 20;
    } disable_ctrl_b;
  } ;

  union {
    __IOM uint32_t int_status;                  /*!< (@ 0x0000000C) PWM Interrupt Status Register                              */

    struct {
      __IOM uint32_t duty_adj_dn_lim : 8;       /*!< [7..0] To indicate the interrupt pending status for PWM 0 ~
                                                     7 duty auto-adjustment reaches the down-limit.Write 1 clear.
                                                     Bit 0 for PWM0, bit 1 for PWM1, ...bit7 for PWM7.                         */
            uint32_t            : 8;
      __IOM uint32_t duty_adj_up_lim : 8;       /*!< [23..16] To indicate the interrupt pending status for PWM 0
                                                     ~ 7 duty auto-adjustment reaches the up-limit.Write 1 clear.
                                                     Bit 16 for PWM0, bit 17 for PWM1, ...bit23 for PWM7.                      */
      __IOM uint32_t period_end : 8;            /*!< [31..24] This bits are used to indicate the interrupt pending
                                                     status for PWM 0 ~7 period end. Write 1 clear. Bit 24 for
                                                     PWM0, bit 25 for PWM1, ...bit31 for PWM7.                                 */
    } int_status_b;
  } ;

  union {
    __IOM uint32_t int_status1;                 /*!< (@ 0x00000010) PWM Interrupt Status1 Register                             */

    struct {
      __IOM uint32_t duty_adj_dn_lim : 4;       /*!< [3..0] To indicate the interrupt pending status for PWM 8 ~
                                                     B duty auto-adjustment reaches the down-limit.Write 1 clear.
                                                     Bit 0 for PWM8, bit 1 for PWM9, ...bit3 for PWMB.                         */
            uint32_t            : 12;
      __IOM uint32_t duty_adj_up_lim : 4;       /*!< [19..16] To indicate the interrupt pending status for PWM 8
                                                     ~ B duty auto-adjustment reaches the up-limit.Write 1 clear.
                                                     Bit 16 for PWM8, bit 17 for PWM9, ...bit19 for PWMB.                      */
            uint32_t            : 8;
      __IOM uint32_t period_end : 4;            /*!< [31..28] This bits are used to indicate the interrupt pending
                                                     status for PWM 8 ~B period end. Write 1 clear. Bit 24 for
                                                     PWM8, bit 25 for PWM1, ...bit27 for PWMB.                                 */
    } int_status1_b;
  } ;

  union {
    __IOM uint32_t indread_idx;                 /*!< (@ 0x00000014) PWM Index of Indirect Read Register                        */

    struct {
      __IOM uint32_t pwm_sel    : 4;            /*!< [3..0] This field is used to assign the PWM index (0 ~ 7) for
                                                     the auto adjusted duty size indirect reading.                             */
      __IOM uint32_t sync_mode  : 1;            /*!< [4..4] Register sync mode selection for PWM clock and APB clock0:
                                                     Freq. of APB clock >> Freq. of PWM clock (about 10 times)1:
                                                     Freq. of PWM clock >= Freq. of APB clock                                  */
            uint32_t            : 2;
      __IOM uint32_t pool       : 1;            /*!< [7..7] Set this bit to enable indirect read current value of
                                                     timer selected by BIT_PWM_INDREAD_IDX. This bit is cleared
                                                     by HW when reading is finished and indicates REG_PERI_PWM_INDREAD_DUTY
                                                     is ready.                                                                 */
            uint32_t            : 24;
    } indread_idx_b;
  } ;

  union {
    __IOM uint32_t indread_duty;                /*!< (@ 0x00000018) PWM Auto Adjusted Duty Indirect Read Register              */

    struct {
      __IOM uint32_t pwm_duty   : 12;           /*!< [11..0] This field is used to read the auto adjusted duty size
                                                     of the PWM which is assigned by the pwm_sel. The SW should
                                                     assign the PWM to read by write the pwm_sel and then read
                                                     this field to get the current duty size of the specified
                                                     PWM.                                                                      */
            uint32_t            : 20;
    } indread_duty_b;
  } ;

  union {
    __IOM uint32_t complementary;               /*!< (@ 0x0000001C) PWM Complementary Register                                 */

    struct {
      __IOM uint32_t pwm_comp_en : 6;           /*!< [5..0] Enable/Disable PWM Complementary mode. Bit 0 for PWM0_1,
                                                     bit 1 for PWM2_3..bit 5 for PWMA_B                                        */
      __IOM uint32_t pwm_db     : 24;           /*!< [29..6] To indicate the amount of delay. Delay time = (1/Sclk)*PWMX_Y_DB.
                                                     Bit 6~9 for PWM0_1_DB, bit 10~13 for PWM2_3_DB.. Bit 26~29
                                                     for PWMA_B_DB                                                             */
            uint32_t            : 2;
    } complementary_b;
  } ;
} PWM_COMM_Type;                                /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                           PWM0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Pulse Width Modulation 0 (PWM0)
  */

typedef struct {                                /*!< (@ 0x40045020) PWM0 Structure                                             */

  union {
    __IOM uint32_t ctrl;                        /*!< (@ 0x00000000) PWM Control Register                                       */

    struct {
      __IOM uint32_t duty       : 12;           /*!< [11..0] The on-duty duration of PWM pulse. The time unit is
                                                     configured by the GTIMER which is specified by clk_sel
                                                     field. It can be written at any time, but HW will apply
                                                     the changing at PWM enable time or at the end of PWM period.              */
      __IOM uint32_t clk_sel    : 4;            /*!< [15..12] The tick source selection, G-timer 0 ~ 7 or SClk:0:
                                                     GTIMER 01: GTIMER 1...7: GTIMER 78: sclk                                  */
      __IM  uint32_t cur_duty   : 12;           /*!< [27..16] The current duty size which is adjusted by the duty
                                                     auto-adjustment HW. The SW can read this field to know
                                                     the current duty size. However, the latest duty size may
                                                     not be sync to this field on time or the value may transition
                                                     while the SW is reading this field. So use in-direct read
                                                     method to read the duty size is more save and is suggested.               */
      __IOM uint32_t period_ie  : 1;            /*!< [28..28] This bit control the PWM period end interrupt enable
                                                     (1) or disable (0). When the PWM period end interrupt is
                                                     enabled, the PWM HW will assert the interrupt on every
                                                     PWM period end time. This interrupt status can be read
                                                     from pwm_int_status.                                                      */
      __IM  uint32_t run_sts    : 1;            /*!< [29..29] The PWM output running status:0: PWM output is paused1:
                                                     the PWM output is running.                                                */
      __IOM uint32_t pause      : 1;            /*!< [30..30] The paus control:0: Normal running1: To pause the PWM
                                                     out at current PWM period end. Since the PWM output is
                                                     not stopped immediately, the software can poll the BIT_PERI_PWMx_RUNSTS
                                                     to know the PWM out is still running or is paused.                        */
      __IOM uint32_t ctrl_set   : 1;            /*!< [31..31] SW can change setting only at ctrl_set = 0, and set
                                                     ctrl_set = 1 after changing PWM Ctrl. HW will clear ctrl_set
                                                     bit after changing PWM Ctrl.PS. If this PWM is disabled
                                                     (PWMx_EN=0), the HW will not clear this bit.PS. if this
                                                     bit is asserted and the duty auto adjustment is enabled,
                                                     when the PWM is enabled the HW will updates its duty at
                                                     the 1st PWM period and then start the duty adjustment at
                                                     2nd PWM period.                                                           */
    } ctrl_b;
  } ;

  union {
    __IOM uint32_t timing_ctrl;                 /*!< (@ 0x00000004) PWM Timing Control Register                                */

    struct {
      __IOM uint32_t period     : 12;           /*!< [11..0] The period of PWM pulse. The time unit is configured
                                                     by the GTIMER which is specified by the clk_sel field.
                                                     It can be written at any time, but the HW will apply the
                                                     changing at PWM enable time or at the end of PWM period.                  */
            uint32_t            : 4;
      __IOM uint32_t duty_start : 12;           /*!< [27..16] The start of ON duration of PWM pulse in the period.
                                                     The time unit is the same as PWM period.It can be written
                                                     at any time, but HW change setting only at PWM enable and
                                                     the end of period.                                                        */
            uint32_t            : 4;
    } timing_ctrl_b;
  } ;

  union {
    __IOM uint32_t auto_adj_ctrl;               /*!< (@ 0x00000008) PWM Duty Auto Adjustment Control Register                  */

    struct {
      __IOM uint32_t duty_dec_step : 10;        /*!< [9..0] The Duty Decreasing Step size of the Duty Auto Adjustment.         */
            uint32_t            : 2;
      __IOM uint32_t duty_inc_step : 10;        /*!< [21..12] The Duty Increasing Step size of the Duty Auto Adjustment        */
            uint32_t            : 5;
      __IOM uint32_t duty_dn_lim_ie : 1;        /*!< [27..27] This bit is used to enable the Interrupt of the Duty
                                                     Auto Adjustment.0: Disable1: EnableIf the Interrupt is
                                                     enabled, issue an interrupt when the Adjusted Duty reach
                                                     the Down Limit.                                                           */
      __IOM uint32_t duty_up_lim_ie : 1;        /*!< [28..28] This bit is used to enable the Interrupt of the Duty
                                                     Auto Adjustment.0: Disable1: EnableIf the Interrupt is
                                                     enabled, issue an interrupt when the Adjusted Duty reach
                                                     the Up Limit.                                                             */
      __IOM uint32_t adj_loop_en : 1;           /*!< [29..29] This bit is used to enable the Duty Auto Adjustment
                                                     Loop mode.0: Disable1: EnableIf the Loop Mode is enabled,
                                                     reverse the Duty Auto Adjustment direction when the adjusted
                                                     Duty reach the Up Limit or the Down Limit.                                */
      __IOM uint32_t adj_dir    : 1;            /*!< [30..30] This bit is used to set the Duty Ato Adjustment direction.0:
                                                     Decrease Duty1: Increase Duty                                             */
      __IOM uint32_t adj_en     : 1;            /*!< [31..31] This bit is used to enable the Duty Ato Adjustment.0:
                                                     Disable1: EnablePS. If this bit is 1, the duty of the auto
                                                     adjustment will override the duty setting in the pwm_ctrl
                                                     register.                                                                 */
    } auto_adj_ctrl_b;
  } ;

  union {
    __IOM uint32_t auto_adj_limit;              /*!< (@ 0x0000000C) PWM Duty Auto Adjustment Limit Register                    */

    struct {
      __IOM uint32_t duty_adj_dn_lim : 12;      /*!< [11..0] The down limit (in ticks) of the duty period for the
                                                     duty ratio auto adjustment                                                */
            uint32_t            : 4;
      __IOM uint32_t duty_adj_up_lim : 12;      /*!< [27..16] The up limit of the duty period for the duty ratio
                                                     auto adjustment                                                           */
            uint32_t            : 4;
    } auto_adj_limit_b;
  } ;

  union {
    __IOM uint32_t auto_adj_cycle;              /*!< (@ 0x00000010) PWM Duty Auto Adjustment Cycle Count Register              */

    struct {
      __IOM uint32_t adj_cycles : 12;           /*!< [11..0] The Cycle Count of the Duty Auto Adjustment.The Duty
                                                     size will be increased/decreased with a step size every
                                                     Cycle Count of PWM period                                                 */
            uint32_t            : 20;
    } auto_adj_cycle_b;
  } ;

  union {
    __IOM uint32_t out_dma;                     /*!< (@ 0x00000014) PWMx Output DMA Mode Register                              */

    struct {
      __IOM uint32_t chg_duty   : 1;            /*!< [0..0] 1: this parameter defines to update PWM duty register
                                                     for each period-end interrupt. 0: no update.                              */
      __IOM uint32_t chg_period : 1;            /*!< [1..1] 1: this parameter defines to update PWM period register
                                                     for each period-end interrupt. 0: no update.                              */
      __IOM uint32_t dma_mode   : 1;            /*!< [2..2] 1 : Enable, 0: Disable DMA Mode.                                   */
            uint32_t            : 29;
    } out_dma_b;
  } ;

  union {
    __IOM uint32_t dma_buff;                    /*!< (@ 0x00000018) BIT_DMA_BUFF                                               */

    struct {
      __IOM uint32_t buff       : 32;           /*!< [31..0] Data register for DMA mode.                                       */
    } dma_buff_b;
  } ;
} PWM_Type;                                    /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           SPIC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPI Controller to control 4IO DTR Flash (SPIC)
  */

typedef struct {                                /*!< (@ 0x40006000) SPIC Structure                                             */

  union {
    __IOM uint32_t ctrlr0;                      /*!< (@ 0x00000000) SPIC Control Register 0                                    */

    struct {
            uint32_t            : 6;
      __IOM uint32_t scph       : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t scpol      : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t tmod       : 2;            /*!< [9..8] RSVD                                                               */
            uint32_t            : 6;
      __IOM uint32_t addr_ch    : 2;            /*!< [17..16] RSVD                                                             */
      __IOM uint32_t data_ch    : 2;            /*!< [19..18] RSVD                                                             */
      __IOM uint32_t cmd_ch     : 2;            /*!< [21..20] RSVD                                                             */
      __IOM uint32_t fast_rd    : 1;            /*!< [22..22] RSVD                                                             */
      __IOM uint32_t ck_mtimes  : 5;            /*!< [27..23] RSVD                                                             */
      __IOM uint32_t addr_ddr_en : 1;           /*!< [28..28] RSVD                                                             */
      __IOM uint32_t data_ddr_en : 1;           /*!< [29..29] RSVD                                                             */
      __IOM uint32_t cmd_ddr_en : 1;            /*!< [30..30] RSVD                                                             */
      __IOM uint32_t prm_2nd_phase : 1;         /*!< [31..31] RSVD                                                             */
    } ctrlr0_b;
  } ;

  union {
    __IOM uint32_t ctrlr1;                      /*!< (@ 0x00000004) SPIC Control Register 1                                    */

    struct {
      __IOM uint32_t ndf        : 12;           /*!< [11..0] RSVD                                                              */
            uint32_t            : 20;
    } ctrlr1_b;
  } ;

  union {
    __IOM uint32_t ssienr;                      /*!< (@ 0x00000008) SPIC Enable Register                                       */

    struct {
      __IOM uint32_t spic_en    : 1;            /*!< [0..0] RSVD                                                               */
      __OM  uint32_t atck_cmd   : 1;            /*!< [1..1] RSVD                                                               */
            uint32_t            : 30;
    } ssienr_b;
  } ;
  __IOM uint32_t  RSVD;                         /*!< (@ 0x0000000C) RSVD                                                       */

  union {
    __IOM uint32_t ser;                         /*!< (@ 0x00000010) Slave Enable Register                                      */

    struct {
      __IOM uint32_t ser        : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } ser_b;
  } ;

  union {
    __IOM uint32_t baudr;                       /*!< (@ 0x00000014) Baud Rate Select Register                                  */

    struct {
      __IOM uint32_t sckdv      : 12;           /*!< [11..0] RSVD                                                              */
            uint32_t            : 20;
    } baudr_b;
  } ;

  union {
    __IOM uint32_t txftlr;                      /*!< (@ 0x00000018) Transmit FIFO Threshold Level                              */

    struct {
      __IOM uint32_t tft        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } txftlr_b;
  } ;

  union {
    __IOM uint32_t rxftlr;                      /*!< (@ 0x0000001C) Receive FIFO Threshold Level                               */

    struct {
      __IOM uint32_t rft        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } rxftlr_b;
  } ;

  union {
    __IM  uint32_t txflr;                       /*!< (@ 0x00000020) Transmit FIFO Level Register                               */

    struct {
      __IM  uint32_t txtfl      : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } txflr_b;
  } ;

  union {
    __IM  uint32_t rxflr;                       /*!< (@ 0x00000024) Receive FIFO Level Register                                */

    struct {
      __IM  uint32_t rxtfl      : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } rxflr_b;
  } ;

  union {
    __IM  uint32_t sr;                          /*!< (@ 0x00000028) Status Register                                            */

    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] RSVD                                                               */
      __IM  uint32_t tfnf       : 1;            /*!< [1..1] RSVD                                                               */
      __IM  uint32_t tfe        : 1;            /*!< [2..2] RSVD                                                               */
      __IM  uint32_t rfne       : 1;            /*!< [3..3] RSVD                                                               */
      __IM  uint32_t rff        : 1;            /*!< [4..4] RSVD                                                               */
      __IM  uint32_t txe        : 1;            /*!< [5..5] RSVD                                                               */
      __IM  uint32_t dcol       : 1;            /*!< [6..6] RSVD                                                               */
            uint32_t            : 25;
    } sr_b;
  } ;

  union {
    __IOM uint32_t imr;                         /*!< (@ 0x0000002C) Interrupt Mask Register                                    */

    struct {
      __IOM uint32_t txeim      : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t txoim      : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rxuim      : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t rxoim      : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t rxfim      : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t fseim      : 1;            /*!< [5..5] RSVD                                                               */
      __IOM uint32_t wbeim      : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t byeim      : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t aceim      : 1;            /*!< [8..8] RSVD                                                               */
      __IOM uint32_t txsim      : 1;            /*!< [9..9] RSVD                                                               */
            uint32_t            : 22;
    } imr_b;
  } ;

  union {
    __IM  uint32_t isr;                         /*!< (@ 0x00000030) Interrupt Status Register                                  */

    struct {
      __IM  uint32_t txeis      : 1;            /*!< [0..0] RSVD                                                               */
      __IM  uint32_t txois      : 1;            /*!< [1..1] RSVD                                                               */
      __IM  uint32_t rxuis      : 1;            /*!< [2..2] RSVD                                                               */
      __IM  uint32_t rxois      : 1;            /*!< [3..3] RSVD                                                               */
      __IM  uint32_t rxfis      : 1;            /*!< [4..4] RSVD                                                               */
      __IM  uint32_t fseis      : 1;            /*!< [5..5] RSVD                                                               */
      __IM  uint32_t wbeis      : 1;            /*!< [6..6] RSVD                                                               */
      __IM  uint32_t byeis      : 1;            /*!< [7..7] RSVD                                                               */
      __IM  uint32_t aceis      : 1;            /*!< [8..8] RSVD                                                               */
      __IM  uint32_t txsis      : 1;            /*!< [9..9] RSVD                                                               */
      __IM  uint32_t rxsis      : 1;            /*!< [10..10] RSVD                                                             */
            uint32_t            : 21;
    } isr_b;
  } ;

  union {
    __IM  uint32_t risr;                        /*!< (@ 0x00000034) Raw Interrupt Status Register                              */

    struct {
      __IM  uint32_t txeir      : 1;            /*!< [0..0] RSVD                                                               */
      __IM  uint32_t txoir      : 1;            /*!< [1..1] RSVD                                                               */
      __IM  uint32_t rxuir      : 1;            /*!< [2..2] RSVD                                                               */
      __IM  uint32_t rxoir      : 1;            /*!< [3..3] RSVD                                                               */
      __IM  uint32_t rxfir      : 1;            /*!< [4..4] RSVD                                                               */
      __IM  uint32_t fseir      : 1;            /*!< [5..5] RSVD                                                               */
      __IM  uint32_t wbeir      : 1;            /*!< [6..6] RSVD                                                               */
      __IM  uint32_t byeir      : 1;            /*!< [7..7] RSVD                                                               */
      __IM  uint32_t aceir      : 1;            /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } risr_b;
  } ;

  union {
    __IM  uint32_t txoicr;                      /*!< (@ 0x00000038) Transmit FIFO Overflow Interrupt Clear Register            */

    struct {
      __IM  uint32_t txoicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } txoicr_b;
  } ;

  union {
    __IM  uint32_t rxoicr;                      /*!< (@ 0x0000003C) Receive FIFO Overflow Interrupt Clear Register             */

    struct {
      __IM  uint32_t rxoicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } rxoicr_b;
  } ;

  union {
    __IM  uint32_t rxuicr;                      /*!< (@ 0x00000040) Receive FIFO Underflow Interrupt Clear Register            */

    struct {
      __IM  uint32_t rxuicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } rxuicr_b;
  } ;

  union {
    __IM  uint32_t faeicr;                      /*!< (@ 0x00000044) Frame Alignment Interrupt Clear Register                   */

    struct {
      __IM  uint32_t faeicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } faeicr_b;
  } ;

  union {
    __IM  uint32_t icr;                         /*!< (@ 0x00000048) Interrupt Clear Register                                   */

    struct {
      __IM  uint32_t icr        : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } icr_b;
  } ;

  union {
    __IOM uint32_t dmacr;                       /*!< (@ 0x0000004C) DMA Control Register                                       */

    struct {
      __IOM uint32_t rx_dmac_en : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t tx_dmac_en : 1;            /*!< [1..1] RSVD                                                               */
            uint32_t            : 30;
    } dmacr_b;
  } ;

  union {
    __IOM uint32_t dmatdlr;                     /*!< (@ 0x00000050) DMA Transmit Data Level Register                           */

    struct {
      __IOM uint32_t dmatdl     : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } dmatdlr_b;
  } ;

  union {
    __IOM uint32_t dmardlr;                     /*!< (@ 0x00000054) DMA Receive Data Level Register                            */

    struct {
      __IOM uint32_t dmardl     : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } dmardlr_b;
  } ;

  union {
    __IM  uint32_t idr;                         /*!< (@ 0x00000058) Identification Code Register                               */

    struct {
      __IM  uint32_t idcode     : 32;           /*!< [31..0] RSVD                                                              */
    } idr_b;
  } ;

  union {
    __IM  uint32_t spic_ver;                    /*!< (@ 0x0000005C) SPIC Version Register                                      */

    struct {
      __IM  uint32_t spic_version : 32;         /*!< [31..0] RSVD                                                              */
    } spic_ver_b;
  } ;

  union {
    union {
      __IOM uint32_t dr_word;                   /*!< (@ 0x00000060) Data Register                                              */

      struct {
        __IOM uint32_t word     : 32;           /*!< [31..0] RSVD                                                              */
      } dr_word_b;
    } ;

    union {
      __IOM uint16_t dr_half_word;              /*!< (@ 0x00000060) Data Register                                              */

      struct {
        __IOM uint16_t half_word : 16;          /*!< [15..0] RSVD                                                              */
      } dr_half_word_b;
    } ;

    union {
      __IOM uint8_t dr_byte;                    /*!< (@ 0x00000060) Data Register                                              */

      struct {
        __IOM uint8_t byte      : 8;            /*!< [7..0] RSVD                                                               */
      } dr_byte_b;
    } ;
  };
  __IM  uint32_t  RESERVED[31];

  union {
    __IOM uint32_t read_fast_single;            /*!< (@ 0x000000E0) Fast Read Command Register                                 */

    struct {
      __IOM uint32_t frd_cmd    : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } read_fast_single_b;
  } ;

  union {
    __IOM uint32_t read_dual_data;              /*!< (@ 0x000000E4) Dual Read Command Register                                 */

    struct {
      __IOM uint32_t rd_dual_o_cmd : 8;         /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } read_dual_data_b;
  } ;

  union {
    __IOM uint32_t read_dual_addr_data;         /*!< (@ 0x000000E8) Dual IO Read Command Register                              */

    struct {
      __IOM uint32_t rd_dual_io_cmd : 8;        /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } read_dual_addr_data_b;
  } ;

  union {
    __IOM uint32_t read_quad_data;              /*!< (@ 0x000000EC) Quad Read Command Register                                 */

    struct {
      __IOM uint32_t rd_quad_o_cmd : 8;         /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } read_quad_data_b;
  } ;

  union {
    __IOM uint32_t read_quad_addr_data;         /*!< (@ 0x000000F0) Quad IO Read Command Register                              */

    struct {
      __IOM uint32_t rd_quad_io_cmd : 8;        /*!< [7..0] RSVD                                                               */
            uint32_t            : 8;
      __IOM uint32_t prm_value  : 8;            /*!< [23..16] RSVD                                                             */
            uint32_t            : 8;
    } read_quad_addr_data_b;
  } ;

  union {
    __IOM uint32_t write_single;                /*!< (@ 0x000000F4) Single IO Page Program Command Register                    */

    struct {
      __IOM uint32_t wr_cmd     : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } write_single_b;
  } ;

  union {
    __IOM uint32_t write_dual_data;             /*!< (@ 0x000000F8) Dual Page Program Command Register                         */

    struct {
      __IOM uint32_t rd_dual_io_cmd : 8;        /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } write_dual_data_b;
  } ;

  union {
    __IOM uint32_t write_dual_addr_data;        /*!< (@ 0x000000FC) Dual IO Page Program Command Register                      */

    struct {
      __IOM uint32_t wr_dual_ii_cmd : 8;        /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } write_dual_addr_data_b;
  } ;

  union {
    __IOM uint32_t write_quad_data;             /*!< (@ 0x00000100) Quad Page Program Command Register                         */

    struct {
      __IOM uint32_t wr_quad_i_cmd : 8;         /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } write_quad_data_b;
  } ;

  union {
    __IOM uint32_t write_quad_addr_data;        /*!< (@ 0x00000104) Quad IO Page Program Command Register                      */

    struct {
      __IOM uint32_t wr_quad_ii_cmd : 8;        /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } write_quad_addr_data_b;
  } ;

  union {
    __IOM uint32_t write_enable;                /*!< (@ 0x00000108) Write Enable Command Register                              */

    struct {
      __IOM uint32_t wr_en_cmd  : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } write_enable_b;
  } ;

  union {
    __IOM uint32_t read_status;                 /*!< (@ 0x0000010C) Read Status Command Register                               */

    struct {
      __IOM uint32_t rd_st_cmd  : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } read_status_b;
  } ;

  union {
    __IOM uint32_t ctrlr2;                      /*!< (@ 0x00000110) SPIC Control Register 2                                    */

    struct {
      __IOM uint32_t so_dnum    : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 2;
      __IOM uint32_t seq_en     : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t tx_fifo_entry : 4;         /*!< [7..4] RSVD                                                               */
      __IOM uint32_t rx_fifo_entry : 4;         /*!< [11..8] RSVD                                                              */
      __IOM uint32_t cs_active_hold : 2;        /*!< [13..12] RSVD                                                             */
            uint32_t            : 18;
    } ctrlr2_b;
  } ;

  union {
    __IOM uint32_t fbaudr;                      /*!< (@ 0x00000114) Fast Read Baud Rate Select Register                        */

    struct {
      __IOM uint32_t fsckdv     : 12;           /*!< [11..0] RSVD                                                              */
            uint32_t            : 20;
    } fbaudr_b;
  } ;

  union {
    __IOM uint32_t addr_length;                 /*!< (@ 0x00000118) Address Byte Length Register                               */

    struct {
      __IOM uint32_t addr_phase_length : 3;     /*!< [2..0] RSVD                                                               */
            uint32_t            : 29;
    } addr_length_b;
  } ;

  union {
    __IOM uint32_t auto_length;                 /*!< (@ 0x0000011C) Auto Mode Address Byte Length Register                     */

    struct {
      __IOM uint32_t rd_dummy_length : 12;      /*!< [11..0] RSVD                                                              */
            uint32_t            : 4;
      __IOM uint32_t auto_addr_length : 2;      /*!< [17..16] RSVD                                                             */
      __IOM uint32_t auto_dum_len : 8;          /*!< [25..18] RSVD                                                             */
      __IOM uint32_t cs_h_rd_dum_len : 2;       /*!< [27..26] RSVD                                                             */
      __IOM uint32_t cs_h_wr_dum_len : 4;       /*!< [31..28] RSVD                                                             */
    } auto_length_b;
  } ;

  union {
    __IOM uint32_t valid_cmd;                   /*!< (@ 0x00000120) Valid Command Register                                     */

    struct {
      __IOM uint32_t frd_single : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t rd_dual_i  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rd_dual_io : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t rd_quad_o  : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t rd_quad_io : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t wr_dual_i  : 1;            /*!< [5..5] RSVD                                                               */
      __IOM uint32_t wr_dual_ii : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t wr_quad_i  : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t wr_quad_ii : 1;            /*!< [8..8] RSVD                                                               */
      __IOM uint32_t wr_blocking : 1;           /*!< [9..9] RSVD                                                               */
            uint32_t            : 1;
      __IOM uint32_t prm_en     : 1;            /*!< [11..11] RSVD                                                             */
      __IOM uint32_t ctrlr0_ch  : 1;            /*!< [12..12] RSVD                                                             */
            uint32_t            : 19;
    } valid_cmd_b;
  } ;

  union {
    __IOM uint32_t flash_size;                  /*!< (@ 0x00000124) Write Enable Command Register                              */

    struct {
      __IOM uint32_t flash_size : 4;            /*!< [3..0] RSVD                                                               */
            uint32_t            : 28;
    } flash_size_b;
  } ;

  union {
    __IOM uint32_t flush_fifo;                  /*!< (@ 0x00000128) Read Status Command Register                               */

    struct {
      __OM  uint32_t flush_fifio : 1;           /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } flush_fifo_b;
  } ;
} SPIC_Type;                                    /*!< Size = 300 (0x12c)                                                        */



/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief 8-channel ADC with 12-bit resolution and 250K SPS (ADC)
  */

typedef struct {                                /*!< (@ 0x40010000) ADC Structure                                              */

  union {
    __IOM uint32_t conf;                        /*!< (@ 0x00000000) ADC Configuration Register                                 */

    struct {
      __IOM uint32_t ref_in_sel : 1;            /*!< [0..0] This bit selects ADC reference voltage input.0: ADC's
                                                     reference voltage is from internal source.1: ADC's reference
                                                     voltage is from external pin.                                             */
      __IOM uint32_t op_mod     : 3;            /*!< [3..1] These bits selects ADC operation mode.0: Software Trigger
                                                     Mode1: Automatic Mode2: Timer-Trigger Mode                                */
      __IOM uint32_t cvlist_len : 4;            /*!< [7..4] This field defines the number of items in the ADC conversion
                                                     channel list.0 is for 1 item in list.1 is for 2 items in
                                                     list.                                                                     */
            uint32_t            : 1;
      __IOM uint32_t en         : 1;            /*!< [9..9] This bit is for ADC enable control.                                */
            uint32_t            : 22;
    } conf_b;
  } ;

  union {
    __IOM uint32_t in_type;                     /*!< (@ 0x00000004) ADC Input Type Register                                    */

    struct {
      __IOM uint32_t ch0        : 1;            /*!< [0..0] This bit controls channel 0 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     1 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 0 is single-end
                                                     input.1: ADC channel 0 is differential input which is paired
                                                     with channel 1.                                                           */
      __IOM uint32_t ch1        : 1;            /*!< [1..1] This bit controls channel 1 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     0 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 1 is single-end
                                                     input.1: ADC channel 1 is differential input which is paired
                                                     with channel 0.                                                           */
      __IOM uint32_t ch2        : 1;            /*!< [2..2] This bit controls channel 2 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     3 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 2 is single-end
                                                     input.1: ADC channel 2 is differential input which is paired
                                                     with channel 3.                                                           */
      __IOM uint32_t ch3        : 1;            /*!< [3..3] This bit controls channel 3 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     2 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 3 is single-end
                                                     input.1: ADC channel 3 is differential input which is paired
                                                     with channel 2.                                                           */
      __IOM uint32_t ch4        : 1;            /*!< [4..4] This bit controls channel 4 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     5 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 4 is single-end
                                                     input.1: ADC channel 4 is differential input which is paired
                                                     with channel 5.                                                           */
      __IOM uint32_t ch5        : 1;            /*!< [5..5] This bit controls channel 5 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     4 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 5 is single-end
                                                     input.1: ADC channel 5 is differential input which is paired
                                                     with channel 4.                                                           */
      __IOM uint32_t ch6        : 1;            /*!< [6..6] This bit controls channel 6 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     7 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 6 is single-end
                                                     input.1: ADC channel 6 is differential input which is paired
                                                     with channel 7.                                                           */
      __IOM uint32_t ch7        : 1;            /*!< [7..7] This bit controls channel 7 input type. If it is set
                                                     to differential type (value of this bit is 1), channel
                                                     6 should also be set to differentail type since they are
                                                     hardware-fixed differentail pair.0: ADC channel 7 is single-end
                                                     input.1: ADC channel 7 is differential input which is paired
                                                     with channel 6.                                                           */
            uint32_t            : 24;
    } in_type_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch0;                 /*!< (@ 0x00000008) ADC Channel 0 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 0
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     0 for ADC automatic comparison.                                           */
    } comp_th_ch0_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch1;                 /*!< (@ 0x0000000C) ADC Channel 1 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 1
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     1 for ADC automatic comparison.                                           */
    } comp_th_ch1_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch2;                 /*!< (@ 0x00000010) ADC Channel 2 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 2
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     2 for ADC automatic comparison.                                           */
    } comp_th_ch2_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch3;                 /*!< (@ 0x00000014) ADC Channel 3 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 3
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     3 for ADC automatic comparison.                                           */
    } comp_th_ch3_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch4;                 /*!< (@ 0x00000018) ADC Channel 4 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 4
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     4 for ADC automatic comparison.                                           */
    } comp_th_ch4_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch5;                 /*!< (@ 0x0000001C) ADC Channel 5 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 5
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     5 for ADC automatic comparison.                                           */
    } comp_th_ch5_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch6;                 /*!< (@ 0x00000020) ADC Channel 6 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 6
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     6 for ADC automatic comparison.                                           */
    } comp_th_ch6_b;
  } ;

  union {
    __IOM uint32_t comp_th_ch7;                 /*!< (@ 0x00000024) ADC Channel 7 Comparison Threshold Register                */

    struct {
      __IOM uint32_t th_l       : 16;           /*!< [15..0] This field defines the lower threshold of channel 7
                                                     for ADC automatic comparison.                                             */
      __IOM uint32_t th_h       : 16;           /*!< [31..16] This field defines the higher threshold of channel
                                                     7 for ADC automatic comparison.                                           */
    } comp_th_ch7_b;
  } ;

  union {
    __IOM uint32_t comp_ctrl;                   /*!< (@ 0x00000028) ADC Comparison Control Register                            */

    struct {
      __IOM uint32_t ch0        : 2;            /*!< [1..0] This field defines ADC channel comparison criteria which
                                                     would notify system by interrupt when the criterion matches.
                                                     Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH0, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH0, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH0
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH0, comparison crit                         */
      __IOM uint32_t ch1        : 2;            /*!< [3..2] This field defines ADC channel comparison criteria which
                                                     would notify system by interrupt when the criterion matches.
                                                     Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH1, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH1, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH1
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH1, comparison crit                         */
      __IOM uint32_t ch2        : 2;            /*!< [5..4] This field defines ADC channel comparison criteria which
                                                     would notify system by interrupt when the criterion matches.
                                                     Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH2, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH2, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH2
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH2, comparison crit                         */
      __IOM uint32_t ch3        : 2;            /*!< [7..6] This field defines ADC channel comparison criteria which
                                                     would notify system by interrupt when the criterion matches.
                                                     Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH3, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH3, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH3
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH3, comparison crit                         */
      __IOM uint32_t ch4        : 2;            /*!< [9..8] This field defines ADC channel comparison criteria which
                                                     would notify system by interrupt when the criterion matches.
                                                     Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH4, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH4, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH4
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH4, comparison crit                         */
      __IOM uint32_t ch5        : 2;            /*!< [11..10] This field defines ADC channel comparison criteria
                                                     which would notify system by interrupt when the criterion
                                                     matches. Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH5, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH5, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH5
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH5, comparison crit                         */
      __IOM uint32_t ch6        : 2;            /*!< [13..12] This field defines ADC channel comparison criteria
                                                     which would notify system by interrupt when the criterion
                                                     matches. Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH6, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH6, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH6
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH6, comparison crit                         */
      __IOM uint32_t ch7        : 2;            /*!< [15..14] This field defines ADC channel comparison criteria
                                                     which would notify system by interrupt when the criterion
                                                     matches. Once a criterion matches, ADC should send an interrupt
                                                     signal to system if the related interrupt mask is unmask.
                                                     ADC also updates comparison results in REG_ADC_COMP_STS.0:
                                                     When Vin < BIT_ADC_COMP_TH_L_CH7, comparison criterion
                                                     matches.1: When Vin > BIT_ADC_COMP_TH_H_CH7, comparison
                                                     criterion matches.2: When Vin >= BIT_ADC_COMP_TH_L_CH7
                                                     and Vin <= BIT_ADC_COMP_TH_H_CH7, comparison crit                         */
            uint32_t            : 16;
    } comp_ctrl_b;
  } ;

  union {
    __IM  uint32_t comp_sts;                    /*!< (@ 0x0000002C) ADC Comparison Status Register                             */

    struct {
      __IM  uint32_t ch0        : 2;            /*!< [1..0] This field reflects comparison result of chnnel 0 immediately.     */
      __IM  uint32_t ch1        : 2;            /*!< [3..2] This field reflects comparison result of chnnel 1 immediately.     */
      __IM  uint32_t ch2        : 2;            /*!< [5..4] This field reflects comparison result of chnnel 2 immediately.     */
      __IM  uint32_t ch3        : 2;            /*!< [7..6] This field reflects comparison result of chnnel 3 immediately.     */
      __IM  uint32_t ch4        : 2;            /*!< [9..8] This field reflects comparison result of chnnel 4 immediately.     */
      __IM  uint32_t ch5        : 2;            /*!< [11..10] This field reflects comparison result of chnnel 5 immediately.   */
      __IM  uint32_t ch6        : 2;            /*!< [13..12] This field reflects comparison result of chnnel 6 immediately.   */
      __IM  uint32_t ch7        : 2;            /*!< [15..14] This field reflects comparison result of chnnel 7 immediately.   */
            uint32_t            : 16;
    } comp_sts_b;
  } ;

  union {
    __IOM uint32_t chsw_list_0;                 /*!< (@ 0x00000030) ADC Channel Swtich List 0 Register                         */

    struct {
      __IOM uint32_t chsw_0     : 4;            /*!< [3..0] This field defines the 1st channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_1     : 4;            /*!< [7..4] This field defines the 2nd channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_2     : 4;            /*!< [11..8] This field defines the 3rd channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_3     : 4;            /*!< [15..12] This field defines the 4th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_4     : 4;            /*!< [19..16] This field defines the 5th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_5     : 4;            /*!< [23..20] This field defines the 6th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_6     : 4;            /*!< [27..24] This field defines the 7th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_7     : 4;            /*!< [31..28] This field defines the 8th channel to do a conversion
                                                     when a conversion event takes place.                                      */
    } chsw_list_0_b;
  } ;

  union {
    __IOM uint32_t chsw_list_1;                 /*!< (@ 0x00000034) ADC Channel Swtich List 1 Register                         */

    struct {
      __IOM uint32_t chsw_8     : 4;            /*!< [3..0] This field defines the 9th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_9     : 4;            /*!< [7..4] This field defines the 10th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_10    : 4;            /*!< [11..8] This field defines the 11th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_11    : 4;            /*!< [15..12] This field defines the 12th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_12    : 4;            /*!< [19..16] This field defines the 13th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_13    : 4;            /*!< [23..20] This field defines the 14th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_14    : 4;            /*!< [27..24] This field defines the 15th channel to do a conversion
                                                     when a conversion event takes place.                                      */
      __IOM uint32_t chsw_15    : 4;            /*!< [31..28] This field defines the 16th channel to do a conversion
                                                     when a conversion event takes place.                                      */
    } chsw_list_1_b;
  } ;

  union {
    __IOM uint32_t rst_list;                    /*!< (@ 0x00000038) ADC Reset List Register                                    */

    struct {
      __IOM uint32_t rst_list   : 1;            /*!< [0..0] This bit controls to reset the channel switch to default
                                                     state or not. Once this bit is set, the auto/manual channel
                                                     switch goes to the first channel as a default state.0:
                                                     Do not reset conversion list to default state.1: Reset
                                                     conversion list to default state.                                         */
            uint32_t            : 31;
    } rst_list_b;
  } ;

  union {
    __IOM uint32_t auto_chsw_ctrl;              /*!< (@ 0x0000003C) ADC Auto Channel Switch Control Register                   */

    struct {
      __IOM uint32_t auto_chsw_en : 1;          /*!< [0..0] This bit controls the automatic channel swtich enabled
                                                     or disabled.0: Disable the automatic channel switch. If
                                                     an automatic channel switch is in progess, writing 0 will
                                                     terminate the automatic channel switch.1: Enable the automatic
                                                     channel switch. When setting this bit, an automatic channel
                                                     switch starts from the first channel in the channel switch
                                                     list.                                                                     */
            uint32_t            : 31;
    } auto_chsw_ctrl_b;
  } ;

  union {
    __IOM uint32_t sw_trig;                     /*!< (@ 0x00000040) ADC Software Trigger Register                              */

    struct {
      __IOM uint32_t sw_trig    : 1;            /*!< [0..0] This bit controls the ADC module to do a conersion.Every
                                                     time this bit is set to 1, ADC module would switch to a
                                                     new channel and do one conversion. Therefore, this bit
                                                     could be used as a start-convert event which is controlled
                                                     by software. Every time a conversion is done, software
                                                     MUST clear this bit manually.0: Disable the analog module
                                                     and analog mux.1: Enable the analog module and analog mux.
                                                     And then start a new channel conversion.                                  */
            uint32_t            : 31;
    } sw_trig_b;
  } ;

  union {
    __IM  uint32_t last_item;                   /*!< (@ 0x00000044) ADC Last Item Register                                     */

    struct {
      __IM  uint32_t last_item  : 4;            /*!< [3..0] This field reflects the last used channel.                         */
            uint32_t            : 28;
    } last_item_b;
  } ;

  union {
    __IM  uint32_t sts;                         /*!< (@ 0x00000048) ADC Busy_Ready Status Register                             */

    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] This bit reflects the ADC is busy or not. If the ADC
                                                     is processing a conversion of a channel, this bit remains
                                                     1 which indicates it's busy. Once a conversion is done,
                                                     this bit becomes 0 which indicates its' ready to do another
                                                     conversion.0: The ADC is ready.1: The ADC is busy.                        */
      __IM  uint32_t full       : 1;            /*!< [1..1] This bit directly reflects the FIFO full status.0: FIFO
                                                     is full.1: FIFO is NOT full.                                              */
      __IM  uint32_t empty      : 1;            /*!< [2..2] This bit directly reflects the FIFO empty status.0: FIFO
                                                     is empty.1: FIFO is NOT empty.                                            */
            uint32_t            : 29;
    } sts_b;
  } ;

  union {
    __IOM uint32_t intr_ctrl;                   /*!< (@ 0x0000004C) ADC Interrupt Control Register                             */

    struct {
      __IOM uint32_t it_cvlist_end_en : 1;      /*!< [0..0] This bit controls the interrupt is enbled or not when
                                                     a conversion of the last channel in the list is done.For
                                                     example, in automatic mode conversions would be executed
                                                     coninuously. Every time the last channel conversion is
                                                     done, which means all channel conversions in the list is
                                                     done, ADC could notify system if this bit is set.0: This
                                                     interrupt is disabled.1: This interrupt is enabled.                       */
      __IOM uint32_t it_cv_end_en : 1;          /*!< [1..1] This bit controls the interrupt is enbled or not every
                                                     time a conversion is done.No matter ADC module is in what
                                                     kind of operation mode. Every time a conversion is executed,
                                                     ADC module would notify system if this bit is set.0: This
                                                     interrupt is disabled.1: This interrupt is enabled.                       */
      __IOM uint32_t it_chcv_end_en : 1;        /*!< [2..2] This bit controls the interrupt is enbled or not when
                                                     a particular channel conversion is done.Please refer to
                                                     REG_ADC_IT_CHNO_CON0: This interrupt is disabled.1: This
                                                     interrupt is enabled.                                                     */
      __IOM uint32_t it_fifo_full_en : 1;       /*!< [3..3] This bit controls the interrupt is enabled or not when
                                                     a FIFO full state takes place.0: This interrupt is disabled.1:
                                                     This interrupt is enabled.                                                */
      __IOM uint32_t it_fifo_over_en : 1;       /*!< [4..4] This bit controls the interrupt is enabled or not when
                                                     a FIFO overflow state takes place.0: This interrupt is
                                                     disabled.1: This interrupt is enabled.                                    */
      __IOM uint32_t it_fifo_empty_en : 1;      /*!< [5..5] This bit controls the interrupt is enabled or not when
                                                     a FIFO empty state takes place.0: This interrupt is disabled.1:
                                                     This interrupt is enabled.                                                */
      __IOM uint32_t it_dat_ovw_en : 1;         /*!< [6..6] This bit controls the interrupt is enabled or not when
                                                     a data overwritten situation takes place.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_err_en  : 1;            /*!< [7..7] This bit controls the interrupt is enabled or not when
                                                     an error state takes place.0: This interrupt is disabled.1:
                                                     This interrupt is enabled.                                                */
      __IOM uint32_t it_comp_ch0_en : 1;        /*!< [8..8] This bit controls the interrupt is enabled or not when
                                                     channel 0 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch1_en : 1;        /*!< [9..9] This bit controls the interrupt is enabled or not when
                                                     channel 1 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch2_en : 1;        /*!< [10..10] This bit controls the interrupt is enabled or not when
                                                     channel 2 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch3_en : 1;        /*!< [11..11] This bit controls the interrupt is enabled or not when
                                                     channel 3 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch4_en : 1;        /*!< [12..12] This bit controls the interrupt is enabled or not when
                                                     channel 4 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch5_en : 1;        /*!< [13..13] This bit controls the interrupt is enabled or not when
                                                     channel 5 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch6_en : 1;        /*!< [14..14] This bit controls the interrupt is enabled or not when
                                                     channel 6 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
      __IOM uint32_t it_comp_ch7_en : 1;        /*!< [15..15] This bit controls the interrupt is enabled or not when
                                                     channel 7 comparison criterion matches.0: This interrupt
                                                     is disabled.1: This interrupt is enabled.                                 */
            uint32_t            : 16;
    } intr_ctrl_b;
  } ;

  union {
    __IM  uint32_t intr_raw_sts;                /*!< (@ 0x00000050) ADC Interrupt RAW Status Register                          */

    struct {
      __IM  uint32_t it_cvlist_end : 1;         /*!< [0..0] RSVD                                                               */
      __IM  uint32_t it_cv_end  : 1;            /*!< [1..1] RSVD                                                               */
      __IM  uint32_t it_chcv_end : 1;           /*!< [2..2] RSVD                                                               */
      __IM  uint32_t it_fifo_full : 1;          /*!< [3..3] RSVD                                                               */
      __IM  uint32_t it_fifo_over : 1;          /*!< [4..4] RSVD                                                               */
      __IM  uint32_t it_fifo_empty : 1;         /*!< [5..5] RSVD                                                               */
      __IM  uint32_t it_dat_ovw : 1;            /*!< [6..6] RSVD                                                               */
      __IM  uint32_t it_err     : 1;            /*!< [7..7] RSVD                                                               */
      __IM  uint32_t it_comp_ch0 : 1;           /*!< [8..8] RSVD                                                               */
      __IM  uint32_t it_comp_ch1 : 1;           /*!< [9..9] RSVD                                                               */
      __IM  uint32_t it_comp_ch2 : 1;           /*!< [10..10] RSVD                                                             */
      __IM  uint32_t it_comp_ch3 : 1;           /*!< [11..11] RSVD                                                             */
      __IM  uint32_t it_comp_ch4 : 1;           /*!< [12..12] RSVD                                                             */
      __IM  uint32_t it_comp_ch5 : 1;           /*!< [13..13] RSVD                                                             */
      __IM  uint32_t it_comp_ch6 : 1;           /*!< [14..14] RSVD                                                             */
      __IM  uint32_t it_comp_ch7 : 1;           /*!< [15..15] RSVD                                                             */
            uint32_t            : 16;
    } intr_raw_sts_b;
  } ;

  union {
    __IOM uint32_t intr_sts;                    /*!< (@ 0x00000054) ADC Interrupt Status Register                              */

    struct {
      __IOM uint32_t it_cvlist_end : 1;         /*!< [0..0] RSVD                                                               */
      __IOM uint32_t it_cv_end  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t it_chcv_end : 1;           /*!< [2..2] RSVD                                                               */
      __IOM uint32_t it_fifo_full : 1;          /*!< [3..3] RSVD                                                               */
      __IOM uint32_t it_fifo_over : 1;          /*!< [4..4] RSVD                                                               */
      __IOM uint32_t it_fifo_empty : 1;         /*!< [5..5] RSVD                                                               */
      __IOM uint32_t it_dat_ovw : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t it_err     : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t it_comp_ch0 : 1;           /*!< [8..8] RSVD                                                               */
      __IOM uint32_t it_comp_ch1 : 1;           /*!< [9..9] RSVD                                                               */
      __IOM uint32_t it_comp_ch2 : 1;           /*!< [10..10] RSVD                                                             */
      __IOM uint32_t it_comp_ch3 : 1;           /*!< [11..11] RSVD                                                             */
      __IOM uint32_t it_comp_ch4 : 1;           /*!< [12..12] RSVD                                                             */
      __IOM uint32_t it_comp_ch5 : 1;           /*!< [13..13] RSVD                                                             */
      __IOM uint32_t it_comp_ch6 : 1;           /*!< [14..14] RSVD                                                             */
      __IOM uint32_t it_comp_ch7 : 1;           /*!< [15..15] RSVD                                                             */
            uint32_t            : 16;
    } intr_sts_b;
  } ;

  union {
    __IOM uint32_t it_chno_con;                 /*!< (@ 0x00000058) ADC Conversion Interrupt Channel Number Configuration
                                                                    Register                                                   */

    struct {
      __IOM uint32_t it_chno_con : 3;           /*!< [2..0] This field defines that ADC module should send interrupt
                                                     signal to system when a conversion which of channel number
                                                     is the same as this field. This register is only valid
                                                     when BIT_ADC_IT_CHCV_END_EN is set.BIT_ADC_IT_CHNO_CON:
                                                     Channel number.                                                           */
            uint32_t            : 29;
    } it_chno_con_b;
  } ;

  union {
    __IOM uint32_t full_lvl;                    /*!< (@ 0x0000005C) ADC FIFO Full Level Register                               */

    struct {
      __IOM uint32_t full_lvl   : 6;            /*!< [5..0] This field defines the FIFO full entry threshold level
                                                     and it is used for FIFO full interrupt. It should be set
                                                     according to ADC FIFO depth.A value of 0 sets the threshold
                                                     for 1 entry, and a value of 15 sets the threshold for16
                                                     entries.                                                                  */
            uint32_t            : 26;
    } full_lvl_b;
  } ;

  union {
    __IOM uint32_t trig_timer_sel;              /*!< (@ 0x00000060) ADC Trigger Timer Select Register                          */

    struct {
      __IOM uint32_t trig_timer_sel : 3;        /*!< [2..0] This three bits defines which timer channel would be
                                                     used to make ADC module do a conversion.BIT_ADC_EXT_WK_TIMER_SEL
                                                     is 0: Timer module 0 is used as the comparator external
                                                     trigger source.1: Timer module 1 is used as the comparator
                                                     external trigger source. . . .7: Timer module 7 is used
                                                     as the comparator external trigger source.                                */
            uint32_t            : 29;
    } trig_timer_sel_b;
  } ;

  union {
    __IOM uint32_t dat_global;                  /*!< (@ 0x00000064) ADC Global Data Register                                   */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of a
                                                     conversion channel in the list.                                           */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in BIT_ADC_DATA_GLOBAL takes place. A data overwritten
                                                     situation is that a former conversion data is NOT read
                                                     before a new conversion is written into data field.0: There
                                                     is no data overwritten case.1: There is a data overwritten
                                                     case.                                                                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of REG_ADC_DATA_GLOBAL
                                                                                                                               */
      __IOM uint32_t ch         : 3;            /*!< [25..23] This field indicates which channel data is in BIT_ADC_DATA_GLOBAL */
            uint32_t            : 6;
    } dat_global_b;
  } ;

  union {
    __IOM uint32_t dat_ch0;                     /*!< (@ 0x00000068) ADC Channel 0 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     0.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch0 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch0.            */
            uint32_t            : 9;
    } dat_ch0_b;
  } ;

  union {
    __IOM uint32_t dat_ch1;                     /*!< (@ 0x0000006C) ADC Channel 1 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     1.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch1 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch1.            */
            uint32_t            : 9;
    } dat_ch1_b;
  } ;

  union {
    __IOM uint32_t dat_ch2;                     /*!< (@ 0x00000070) ADC Channel 2 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     2.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch2 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch2.            */
            uint32_t            : 9;
    } dat_ch2_b;
  } ;

  union {
    __IOM uint32_t dat_ch3;                     /*!< (@ 0x00000074) ADC Channel 3 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     3.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch3 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch3.            */
            uint32_t            : 9;
    } dat_ch3_b;
  } ;

  union {
    __IOM uint32_t dat_ch4;                     /*!< (@ 0x00000078) ADC Channel 4 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     4.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch4 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch4.            */
            uint32_t            : 9;
    } dat_ch4_b;
  } ;

  union {
    __IOM uint32_t dat_ch5;                     /*!< (@ 0x0000007C) ADC Channel 5 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     5.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch5 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch5.            */
            uint32_t            : 9;
    } dat_ch5_b;
  } ;

  union {
    __IOM uint32_t dat_ch6;                     /*!< (@ 0x00000080) ADC Channel 6 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     6.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch6 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch6.            */
            uint32_t            : 9;
    } dat_ch6_b;
  } ;

  union {
    __IOM uint32_t dat_ch7;                     /*!< (@ 0x00000084) ADC Channel 7 Data Register                                */

    struct {
      __IOM uint32_t dat        : 18;           /*!< [17..0] This field contains the newest conversion data of channel
                                                     7.                                                                        */
            uint32_t            : 3;
      __IOM uint32_t ovw        : 1;            /*!< [21..21] This bit indicates that there is a data overwritten
                                                     situation in dat_ch7 takes place. A data overwritten situation
                                                     is that a former conversion data is NOT read before a new
                                                     conversion is written into data field.0: There is no data
                                                     overwritten case.1: There is a data overwritten case.                     */
      __IOM uint32_t rdy        : 1;            /*!< [22..22] This bit indicates that a conversion is done. Every
                                                     time a conversion is done, this bit should be set to 1
                                                     and it would be cleared to 0 when a read operation of dat_ch7.            */
            uint32_t            : 9;
    } dat_ch7_b;
  } ;

  union {
    __IOM uint32_t dma_con;                     /*!< (@ 0x00000088) ADC DMA Control Register                                   */

    struct {
      __IOM uint32_t en         : 1;            /*!< [0..0] This bit controls that DMA function of ADC is enabled
                                                     or not.0: ADC DMA is disabled.1: ADC DMA is enabled.                      */
            uint32_t            : 7;
      __IOM uint32_t lvl        : 6;            /*!< [13..8] This field defines the FIFO threshold level that ADC
                                                     module should make a DMA request to DMA module.A value
                                                     of 0 sets the threshold for 1 entry, and a value of 15
                                                     sets the threshold for16 entries.                                         */
            uint32_t            : 18;
    } dma_con_b;
  } ;

  union {
    __IOM uint32_t flr;                         /*!< (@ 0x0000008C) ADC FIFO Level Register                                    */

    struct {
      __IOM uint32_t flr        : 7;            /*!< [6..0] This field records the current ADC FIFO entry number.              */
            uint32_t            : 25;
    } flr_b;
  } ;

  union {
    __IOM uint32_t clr_fifo;                    /*!< (@ 0x00000090) ADC Clear FIFO Register                                    */

    struct {
      __IOM uint32_t clr_fifo   : 1;            /*!< [0..0] This bit is used to clear FIFO contents and makes it
                                                     to the default status.Every time this bit is set to 1,
                                                     FIFO would be cleared to the default status. Software should
                                                     set this bit to 0 after FIFO is cleared.0: No effect.1:
                                                     Clear FIFO.                                                               */
            uint32_t            : 31;
    } clr_fifo_b;
  } ;

  union {
    __IOM uint32_t clk_div;                     /*!< (@ 0x00000094) ADC Clock Division Register                                */

    struct {
      __IOM uint32_t clk_div    : 3;            /*!< [2..0] This field defines clock divider level of ADC module.A
                                                     value of 0 is for clock divided by 5.A value of 1 is for
                                                     clock divided by 10.A value of 2 is for clock divided by
                                                     16.A value of 3 is for clock divided by 32.A value of 4
                                                     is for clock divided by 64.                                               */
            uint32_t            : 29;
    } clk_div_b;
  } ;

  union {
    __IOM uint32_t dly_cnt;                     /*!< (@ 0x00000098) ADC Delay Couont Register                                  */

    struct {
      __IOM uint32_t dly_cnt    : 4;            /*!< [3..0] This field defines channel switch delay count.A value
                                                     of 0 is for using default count of hardware.                              */
            uint32_t            : 28;
    } dly_cnt_b;
  } ;

  union {
    __IOM uint32_t pwr_ctrl;                    /*!< (@ 0x0000009C) ADC Power Control Register                                 */

    struct {
      __IOM uint32_t pwr_ctrl   : 1;            /*!< [0..0] This field is used to power control.                               */
            uint32_t            : 31;
    } pwr_ctrl_b;
  } ;

  union {
    __IOM uint32_t ana_ad0;                     /*!< (@ 0x000000A0) ADC Analog Control 0 Register                              */

    struct {
      __IOM uint32_t pwr_cut    : 1;            /*!< [0..0] This field is for analog usage.                                    */
      __IOM uint32_t en         : 1;            /*!< [1..1] This field is for analog usage.                                    */
      __IOM uint32_t ref_en     : 1;            /*!< [2..2] This field is for analog usage.                                    */
      __IOM uint32_t cal_en     : 1;            /*!< [3..3] This field is for analog usage.                                    */
      __IOM uint32_t ext_vref_en : 1;           /*!< [4..4] This field is for analog usage.                                    */
      __IOM uint32_t ck         : 1;            /*!< [5..5] This field is for analog usage.                                    */
      __IOM uint32_t ckd2       : 1;            /*!< [6..6] This field is for analog usage.                                    */
      __IOM uint32_t dly        : 1;            /*!< [7..7] This field is for analog usage.                                    */
      __IOM uint32_t samp       : 1;            /*!< [8..8] This field is for analog usage.                                    */
      __IOM uint32_t revck      : 1;            /*!< [9..9] This field is for analog usage.                                    */
      __IOM uint32_t dout       : 1;            /*!< [10..10] This field is for analog usage.                                  */
      __IOM uint32_t bstca      : 1;            /*!< [11..11] This field is for analog usage.                                  */
      __IOM uint32_t avg        : 1;            /*!< [12..12] This field is for analog usage.                                  */
      __IOM uint32_t bypass     : 6;            /*!< [18..13] This field is for analog usage.                                  */
      __IOM uint32_t dat_sel    : 5;            /*!< [23..19] This field is for analog usage.                                  */
      __IOM uint32_t dummy      : 8;            /*!< [31..24] This field is for analog usage.                                  */
    } ana_ad0_b;
  } ;

  union {
    __IOM uint32_t ana_ad1;                     /*!< (@ 0x000000A4) ADC Analog Control 1 Register                              */

    struct {
      __IOM uint32_t dout0_p    : 2;            /*!< [1..0] This field is for analog usage.                                    */
      __IOM uint32_t dout0_n    : 2;            /*!< [3..2] This field is for analog usage.                                    */
      __IOM uint32_t dout1_p    : 3;            /*!< [6..4] This field is for analog usage.                                    */
      __IOM uint32_t dout1_n    : 3;            /*!< [9..7] This field is for analog usage.                                    */
      __IOM uint32_t dout2_p    : 3;            /*!< [12..10] This field is for analog usage.                                  */
      __IOM uint32_t dout2_n    : 3;            /*!< [15..13] This field is for analog usage.                                  */
      __IOM uint32_t dout3_p    : 4;            /*!< [19..16] This field is for analog usage.                                  */
      __IOM uint32_t dout3_n    : 4;            /*!< [23..20] This field is for analog usage.                                  */
      __IOM uint32_t dout4_n    : 5;            /*!< [28..24] This field is for analog usage.                                  */
      __IOM uint32_t dummy      : 3;            /*!< [31..29] This field is for analog usage.                                  */
    } ana_ad1_b;
  } ;

  union {
    __IOM uint32_t ana_ad2;                     /*!< (@ 0x000000A8) ADC Analog Control 2 Register                              */

    struct {
      __IOM uint32_t dout4_n    : 5;            /*!< [4..0] This field is for analog usage.                                    */
      __IOM uint32_t dout5_p    : 5;            /*!< [9..5] This field is for analog usage.                                    */
      __IOM uint32_t dout5_n    : 5;            /*!< [14..10] This field is for analog usage.                                  */
      __IOM uint32_t dout6_p    : 5;            /*!< [19..15] This field is for analog usage.                                  */
      __IOM uint32_t dout6_n    : 5;            /*!< [24..20] This field is for analog usage.                                  */
      __IOM uint32_t dout7_p    : 5;            /*!< [29..25] This field is for analog usage.                                  */
      __IOM uint32_t dummy      : 2;            /*!< [31..30] This field is for analog usage.                                  */
    } ana_ad2_b;
  } ;

  union {
    __IOM uint32_t ana_ad3;                     /*!< (@ 0x000000AC) ADC Analog Control 3 Register                              */

    struct {
      __IOM uint32_t dout7_n    : 5;            /*!< [4..0] This field is for analog usage.                                    */
      __IOM uint32_t dout8_p    : 5;            /*!< [9..5] This field is for analog usage.                                    */
      __IOM uint32_t dout8_n    : 5;            /*!< [14..10] This field is for analog usage.                                  */
      __IOM uint32_t dout9_p    : 6;            /*!< [20..15] This field is for analog usage.                                  */
      __IOM uint32_t dout9_n    : 6;            /*!< [26..21] This field is for analog usage.                                  */
      __IOM uint32_t dummy      : 5;            /*!< [31..27] This field is for analog usage.                                  */
    } ana_ad3_b;
  } ;

  union {
    __IOM uint32_t ana_ad4;                     /*!< (@ 0x000000B0) ADC Analog Control 4 Register                              */

    struct {
      __IOM uint32_t dout10_p   : 5;            /*!< [4..0] This field is for analog usage.                                    */
      __IOM uint32_t dout10_n   : 5;            /*!< [9..5] This field is for analog usage.                                    */
      __IOM uint32_t dout11_p   : 5;            /*!< [14..10] This field is for analog usage.                                  */
      __IOM uint32_t dout11_n   : 6;            /*!< [20..15] This field is for analog usage.                                  */
            uint32_t            : 5;
      __IOM uint32_t dummy      : 6;            /*!< [31..26] This field is for analog usage.                                  */
    } ana_ad4_b;
  } ;

  union {
    __IOM uint32_t ana_ad5;                     /*!< (@ 0x000000B4) ADC Analog Control 5 Register                              */

    struct {
      __IOM uint32_t dout12_p   : 8;            /*!< [7..0] This field is for analog usage.                                    */
      __IOM uint32_t dout12_n   : 8;            /*!< [15..8] This field is for analog usage.                                   */
      __IOM uint32_t dout13_p   : 8;            /*!< [23..16] This field is for analog usage.                                  */
      __IOM uint32_t dout13_n   : 8;            /*!< [31..24] This field is for analog usage.                                  */
    } ana_ad5_b;
  } ;

  union {
    __IOM uint32_t ana_ad6;                     /*!< (@ 0x000000B8) ADC Analog Control 6 Register                              */

    struct {
      __IOM uint32_t dout_offp  : 6;            /*!< [5..0] This field is for analog usage.                                    */
      __IOM uint32_t dout_offn  : 6;            /*!< [11..6] This field is for analog usage.                                   */
      __IOM uint32_t dummy      : 4;            /*!< [15..12] This field is for analog usage.                                  */
            uint32_t            : 16;
    } ana_ad6_b;
  } ;
} ADC_Type;                                     /*!< Size = 188 (0xbc)                                                         */



/* =========================================================================================================================== */
/* ================                                           UART0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief UART port 0, 7/8 bit frame, 1/2 stop bit, up to 4000000 baud rate (UART0)
  */

typedef struct {                                /*!< (@ 0x40040000) UART0 Structure                                            */

  union {
    __IOM uint32_t dllr;                        /*!< (@ 0x00000000) Divisor Latch (LS) Register                                */

    struct {
      __IOM uint32_t dll        : 8;            /*!< [7..0] Divisor [7:0]; accessible when DLAB = 1                            */
            uint32_t            : 24;
    } dllr_b;
  } ;

  union {
    union {
      __IOM uint32_t dlmr;                      /*!< (@ 0x00000004) Divisor Latch (MS) Register                                */

      struct {
        __IOM uint32_t dlm      : 8;            /*!< [7..0] Divisor [15:8]; accessible when DLAB = 1                           */
              uint32_t          : 24;
      } dlmr_b;
    } ;

    union {
      __IOM uint32_t ier;                       /*!< (@ 0x00000004) Interrupt Enable Register                                  */

      struct {
        __IOM uint32_t erbi     : 1;            /*!< [0..0] Enable Received Data Available Interrupt (ERBFI) (rx
                                                     trigger)0: disabled1: enabled                                             */
        __IOM uint32_t etbei    : 1;            /*!< [1..1] Enable Transmitter FIFO Empty interrupt (ETBEI) (tx fifo
                                                     empty)0: disabled 1: enabled                                              */
        __IOM uint32_t elsi     : 1;            /*!< [2..2] Enable Receiver Line Status Interrupt (ELSI) (receiver
                                                     line status)0: disabled1: enabled                                         */
        __IOM uint32_t edssi    : 1;            /*!< [3..3] Enable Modem Status Interrupt (EDSSI) (modem status transition)0:
                                                     disabled1: enabled                                                        */
              uint32_t          : 28;
      } ier_b;
    } ;
  };

  union {
    union {
      __IM  uint32_t iir;                       /*!< (@ 0x00000008) Interrupt Identification Register                          */

      struct {
        __IM  uint32_t int_pend : 1;            /*!< [0..0] Indicates that an interrupt is pending when it's logic
                                                     ''0''. When it is ''1'', no interrupt is pending0: an interrupt
                                                     is pending and the IIR contents may be used as a pointer
                                                     to the appropriate interrupt service routine1: no interrupt
                                                     is pending                                                                */
        __IM  uint32_t int_id   : 3;            /*!< [3..1] Bit1 and Bit2 the two bits of the IIR are used to identify
                                                     the highest priority interrupt pending as indicated in
                                                     the following tableBit3: In the FIFO mode this bit is set
                                                     along with bit 2 when a timeout interrupt is pending.Bit3~Bit1
                                                     displays the list of possible interrupts along with the
                                                     bits they enable, priority, and their source and reset
                                                     control.''3'b011'': Interrupt Priority: 1st priority (int_3)
                                                     Interrupt Type: Receiver Line Status (read lsr) Interrupt
                                                     Source: Par                                                               */
              uint32_t          : 28;
      } iir_b;
    } ;

    union {
      __OM  uint32_t fcr;                       /*!< (@ 0x00000008) FIFO Control Register                                      */

      struct {
        __OM  uint32_t en_rxfifo_err : 1;       /*!< [0..0] Set as 1 to enable the report of Error in RCVR FIFO field
                                                     in LSR bit [7]                                                            */
        __OM  uint32_t clear_rxfifo : 1;        /*!< [1..1] Writing a Logic ''1'' to Bit 1 clears the Receiver FIFO
                                                     and resets its logic. But it doesn't clear the shift register,
                                                     i.e. receiving of the current character continues.The 1
                                                     that is written to this bit position is self-clearing                     */
        __OM  uint32_t clear_txfifo : 1;        /*!< [2..2] Writing a Logic ''1'' to Bit 2 clears the Transmitter
                                                     FIFO and resets its logic. The shift register is not cleared,
                                                     i.e., transmitting of the current character continues.The
                                                     1 that is written to this bit position is self-clearing                   */
        __OM  uint32_t dma_mode : 1;            /*!< [3..3] Support DMA mode. (cooperate with DW DDMA in the data
                                                     path)                                                                     */
              uint32_t          : 1;
        __OM  uint32_t txfifo_low_level : 1;    /*!< [5..5] Define the Transmission FIFO Low Water Level Interrupt
                                                     trigger.0: 4 byte1: 8 bytes                                               */
        __OM  uint32_t rxfifo_trigger_level : 2;/*!< [7..6] Define the 32-entries Receiver FIFO Interrupt trigger
                                                     level 0~31 bytes''00'': 1 byte''01'': 8 bytes''10'': 16
                                                     bytes''11'': 30 bytes (for some device detect RTS de-assertion
                                                     slower, reserve more RX FIFO space to prevent RX FIFO overflow
                                                     )                                                                         */
              uint32_t          : 24;
      } fcr_b;
    } ;
  };

  union {
    __IOM uint32_t lcr;                         /*!< (@ 0x0000000C) Line Control Register                                      */

    struct {
      __IOM uint32_t wls0       : 1;            /*!< [0..0] Word length selection, 0: data is 7 bit word length.1:
                                                     data is 8 bit word length.                                                */
            uint32_t            : 1;
      __IOM uint32_t stb        : 1;            /*!< [2..2] This bit specifies the number of Stop bits transmitted
                                                     and received in each serial character.0: 1 stop bit. 1:
                                                     2 stop bits.Note that the receiver always checks the first
                                                     stop bit only.                                                            */
      __IOM uint32_t parity_en  : 1;            /*!< [3..3] Parity Enable0: No parity1: Parity bit is generated on
                                                     each outgoing character and is checked on each incoming
                                                     one.                                                                      */
      __IOM uint32_t even_parity_sel : 1;       /*!< [4..4] Even Parity select0: Odd number of Logic ''1'' is transmitted
                                                     and checked in each word (data and parity combined). In
                                                     other words, if the data has an even number of ''1'' in
                                                     it, then the parity bit is ''1''1: Even number of ''1''
                                                     is transmitted in each word.                                              */
      __IOM uint32_t stick_parity_en : 1;       /*!< [5..5] Stick Parity enable control.1: Enable Stick Parity.0:
                                                     Disable Stick Parity.If the stick parity is enabled, the
                                                     parity bit is controlled by the LCR bit[4].LCR[5:4]:00:
                                                     Odd Parity01: Even Parity10: Stick Parity as 011: Stick
                                                     Parity as 1                                                               */
      __IOM uint32_t break_ctrl : 1;            /*!< [6..6] Break Control bit0: break is disabled1: the serial out
                                                     is forced into logic '0' (break state). Break control bit
                                                     causes a break condition to be transmitted to the receiving
                                                     UART. When it is set to logic 1, the serial output (Sout)
                                                     is forced to the Spacing (logic 0) state. The break is
                                                     disabled by setting bit 6 to logic 0. The Break Control
                                                     bit acts only on SOUT and has no effect on the transmitter
                                                     logic.                                                                    */
      __IOM uint32_t dlab       : 1;            /*!< [7..7] Divisor Latch Access bit0: The divisor latches cannot
                                                     be accessed1: The divisor latches can be accessedNote:
                                                     DLL/DLM only can be access when dlab bit = 1 IER only can
                                                     be access when dlab bit = 0 THR/RBR don't care about dlab
                                                     bit value.                                                                */
            uint32_t            : 24;
    } lcr_b;
  } ;

  union {
    __IOM uint32_t mcr;                         /*!< (@ 0x00000010) Modem Control Register                                     */

    struct {
      __IOM uint32_t dtr        : 1;            /*!< [0..0] Data Terminal Ready (DTR) signal control0:DTR is logic
                                                     11:DTR is logic 0This bit controls the Data Terminal Ready
                                                     (DTR_) output. When bit 0 is set to logic 1, the DTR_ output
                                                     is forced to logic 0. When bit0 reset to logic 0, the DTR_
                                                     output is forced to logic 1.                                              */
      __IOM uint32_t rts        : 1;            /*!< [1..1] Request to Send (RTS) signal control''0'' RTS is logic
                                                     1''1'' RTS is logic 0This bit controls the Request to Send
                                                     (RTS) output. The RTS output is controlled as following
                                                     equation:RTS_output = rts_en ? (~rts|FIFO_FlowCtrl):~rts                  */
      __IOM uint32_t out1       : 1;            /*!< [2..2] This bit controls the Output 1 (OUT1_) signal, which
                                                     is an auxiliary user-designated output. Bit 2 affects the
                                                     OUT1_ in a manner identical to that described below for
                                                     bit 0.In loopback mode, connected Ring Indicator (RI) signal
                                                     input                                                                     */
      __IOM uint32_t out2       : 1;            /*!< [3..3] This bit controls the output 2 (OUT2_) signal, which
                                                     is an auxiliary user-designated output. Bit3 affects the
                                                     OUT2_output in a manner identical to that described below
                                                     for bit 0.In loopback mode, connected to Data Carrier Detect
                                                     (DCD)                                                                     */
      __IOM uint32_t loopback_en : 1;           /*!< [4..4] LoopBack mode0: normal operation1: loopback modeThis
                                                     bit provides a local loopback feature for diagnostic testing
                                                     of the UART. When bit 4 is set to logic 1, the following
                                                     occur: the transmitter Serial Output ( SOUT) is set to
                                                     the Marking ( logic 1) state; the receiver Serial Input
                                                     (SIN) is disconnected; the output of the Transmitter Shift
                                                     Register is ''looped back'' into the Receiver Shift Register
                                                     input; the four MODEM control inputs (DSR_, CTS_, RI_ and
                                                     DCD_) are disconnected; and the four MODEM                                */
      __IOM uint32_t cts_en     : 1;            /*!< [5..5] CTS flow control enable (CTSE)This Bit (CTSE) is the
                                                     auto CTS flow control enable. When set (1), the auto CTS
                                                     flow control as described in the detailed description is
                                                     enabled.Note: Auto-CTS_:The Transmitter circuitry checks
                                                     CTS_ before sending the next data byte. When CTS_ is active,
                                                     it sends the next byte. Top stop the transmitter from sending
                                                     the following byte, CTS_ must be released before the middle
                                                     of the last stop bit that is currently being sent. The
                                                     auto-CTS_ function reduces interrupts to th                               */
      __IOM uint32_t rts_en     : 1;            /*!< [6..6] RTS flow control enable (RTSE)This Bit (RTSE) is the
                                                     auto RTS flow control enables. When set (1), the auto RTS
                                                     flow control as described in the detailed description is
                                                     enabled.Note: Auto-RTS_ data flow control originates in
                                                     the receiver timing and control block and is linked to
                                                     the programmed receiver FIFO trigger level. When the receiver
                                                     FIFO level reaches a trigger level, RTS_ is de-asserted.
                                                     The sending communication element may send an additional
                                                     byte after the trigger level is reached (assuming                         */
      __IOM uint32_t sw_cts     : 1;            /*!< [7..7] Software controlled CTS. The software can use this bit
                                                     to pause the UART transmission, just like the HW flow control.
                                                     This is useful for software to implement XOn/XOff SW flow
                                                     control. This bit setting will effects the CTS flow-control:CTS
                                                     = cts_en ? (sw_cts | CTS_input) : sw_cts                                  */
            uint32_t            : 24;
    } mcr_b;
  } ;

  union {
    __IM  uint32_t lsr;                         /*!< (@ 0x00000014) Line Status Register                                       */

    struct {
      __IM  uint32_t rxfifo_datardy : 1;        /*!< [0..0] Data Ready (DR) indicator0: No characters in the Receiver
                                                     FIFO1: At least one character has been received and transferred
                                                     into the FIFO.Bit0 is reset to logic ''0'' by reading all
                                                     of the data in the Receiver Buffer Register or the RX FIFO.               */
      __IM  uint32_t overrun_err : 1;           /*!< [1..1] Overrun Error (OE) indicator0: No Overrun state1: Indicates
                                                     that data in the RX FIFO was not read by the CPU before
                                                     the next character was transferred into the RX FIFO, thereby
                                                     destroying the previous character. The OE indicator is
                                                     set to logic 1 upon detection of an overrun condition and
                                                     reset whenever the CPU reads the contents of the Line Status
                                                     Register. If the FIFO mode data continues to fill the FIFO
                                                     beyond the trigger level, an overrun error will occur only
                                                     after the FIFO is full and the next ch                                    */
      __IM  uint32_t parity_err : 1;            /*!< [2..2] Parity Error (PE) indicator0: No parity error in current
                                                     character1: Indicates that the received data character
                                                     does not have the correct even or odd parity, as selected
                                                     by the even-parity-select bit. The PE bit is set to logic
                                                     ''1'' upon detection of a parity error and is reset to
                                                     logic 0 whenever the CPU reads the contents of the Line
                                                     Status Register. This error is revealed to the CPU when
                                                     its associated character is at the top of the FIFO (next
                                                     character to be read).                                                    */
      __IM  uint32_t framing_err : 1;           /*!< [3..3] Framing Error (FE) indicator0: No framing error in the
                                                     current character1: The received character at the top of
                                                     the FIFO did not have a valid stop bit. Of course, generally,
                                                     it might be that all the following data is corrupt. It
                                                     indicates that the received character did not have a valid
                                                     stop bit. Bit 3 is set to a logic 1 whenever the Stop bit
                                                     following the last data bit or parity bit is detected as
                                                     a logic 0 bit (Spacing level). The FE indicator is reset
                                                     whenever the CPU reads the contents of the Line                           */
      __IM  uint32_t break_err_int : 1;         /*!< [4..4] Break Interrupt (BI) indicator0: No break condition in
                                                     the current character1: set to logic 1 whenever the received
                                                     data input is held in the Spacing (logic 0) state for a
                                                     longer than a full word transmission time (that is, the
                                                     total time of Start bit + data bits + Parity + Stop bits).
                                                     The BI indicator is reset whenever the CPU reads the contents
                                                     of the Line Status Register. This error is revealed to
                                                     the CPU when its associated character is at the top of
                                                     the FIFO. When break occurs only one zero charac                          */
      __IM  uint32_t txfifo_empty : 1;          /*!< [5..5] TXFIFO empty indicator.0: Otherwise1: It indicates that
                                                     the Transmitter FIFO is empty. This bit is set when the
                                                     Transmitter FIFO is empty; it is cleared when at least
                                                     1 byte is written to the Transmitter FIFO.                                */
            uint32_t            : 1;
      __IM  uint32_t rxfifo_err : 1;            /*!< [7..7] Uart_rx_error1: In the FIFO mode, this bit (LSR bit7)
                                                     is set when there is at least on parity error, framing
                                                     error or break indication in the FIFO. LSR7 is clear when
                                                     the CPU reads the LSR, if there are no subsequent errors
                                                     in the FIFO.                                                              */
            uint32_t            : 24;
    } lsr_b;
  } ;

  union {
    __IM  uint32_t msr;                         /*!< (@ 0x00000018) Modem Status Register                                      */

    struct {
      __IM  uint32_t d_cts      : 1;            /*!< [0..0] Delta Clear to Send (DCTS) indicator1: The CTS line has
                                                     changed its state.0: Otherwise                                            */
      __IM  uint32_t d_dsr      : 1;            /*!< [1..1] Delta Data Set Ready (DDSR) indicator1: The DSR line
                                                     has changed its state.0: Otherwise                                        */
      __IM  uint32_t teri       : 1;            /*!< [2..2] Trailing Edge of Ring Indicator (TERI) detector. The
                                                     RI line has changed its state from low to high state                      */
      __IM  uint32_t d_dcd      : 1;            /*!< [3..3] Delta Data Carrier Detect (DDCD) indicator1: The DCD
                                                     line has changed its state.0: Otherwise.                                  */
      __IM  uint32_t r_cts      : 1;            /*!< [4..4] Complement of the CTS input or equals to RTS in loopback
                                                     mode.                                                                     */
      __IM  uint32_t r_dsr      : 1;            /*!< [5..5] Complement of the DSR input or equals to DTR in loopback
                                                     mode.                                                                     */
      __IM  uint32_t r_ri       : 1;            /*!< [6..6] Complement of the RI input or equals to Out1 in loopback
                                                     mode.                                                                     */
      __IM  uint32_t r_dcd      : 1;            /*!< [7..7] Complement of the DCD input or equals to Out2 in loopback
                                                     mode.                                                                     */
            uint32_t            : 24;
    } msr_b;
  } ;

  union {
    __IOM uint32_t scr;                         /*!< (@ 0x0000001C) Scratch Pad Register                                       */

    struct {
            uint32_t            : 3;
      __IOM uint32_t pin_lb_test : 1;           /*!< [3..3] For uart IP txd/rxd/rts/cts pin loopback test                      */
      __IM  uint32_t fl_frame_err : 1;          /*!< [4..4] RSVD                                                               */
      __IM  uint32_t fl_set_bi_err : 1;         /*!< [5..5] RSVD                                                               */
      __IOM uint32_t rx_break_int_en : 1;       /*!< [6..6] rx break signal interrupt enable                                   */
      __IOM uint32_t rx_break_int_sts : 1;      /*!< [7..7] rx break signal interrupt status. Write one clear.                 */
      __IOM uint32_t dbg_sel    : 4;            /*!< [11..8] Debug port selection                                              */
            uint32_t            : 4;
      __IOM uint32_t xfactor_adj : 11;          /*!< [26..16] One factor of Baud rate calculation, i.e., the ovsr_adj[10:0]
                                                     of following formula.                                                     */
            uint32_t            : 5;
    } scr_b;
  } ;

  union {
    __IOM uint32_t stsr;                        /*!< (@ 0x00000020) STS Register                                               */

    struct {
            uint32_t            : 3;
      __IOM uint32_t reset_rcv  : 1;            /*!< [3..3] Reset Uart Receiver                                                */
      __IOM uint32_t xfactor    : 4;            /*!< [7..4] Factor of Baud rate calculation, i.e., the ovsr[3:0]
                                                     of following formula.                                                     */
            uint32_t            : 16;
      __IM  uint32_t dma_mode   : 1;            /*!< [24..24] dma_mode field of FCR bit[3]                                     */
      __IM  uint32_t fifo_en    : 1;            /*!< [25..25] fifo_en field of FCR bit[0]                                      */
      __IM  uint32_t txfifo_low_level : 1;      /*!< [26..26] txfifo_low_level in FCR bit[5], Define the Transmission
                                                     FIFO Low Water Level Interrupt trigger.0: 4 byte1: 8 bytes                */
      __IM  uint32_t rxfifo_trigger_level : 2;  /*!< [28..27] rxfifo_trigger_level in FCR bit[7:6], Define the 32-entries
                                                     Receiver FIFO Interrupt trigger level 0~31 bytes00: 1 byte01:
                                                     8 bytes10: 16 bytes11: 28 bytes (for some device detect
                                                     RTS de-assertion slower, reserve more RX FIFO space to
                                                     prevent RX FIFO overflow )                                                */
            uint32_t            : 3;
    } stsr_b;
  } ;

  union {
    union {
      __IM  uint32_t rbr;                       /*!< (@ 0x00000024) Receiver Buffer Register                                   */

      struct {
        __IM  uint32_t rxdata   : 8;            /*!< [7..0] Rx data.Note: Bit 0 is the least significant bit. It
                                                     is the first bit serially received.                                       */
              uint32_t          : 24;
      } rbr_b;
    } ;

    union {
      __OM  uint32_t thr;                       /*!< (@ 0x00000024) Transmitter Holder Register                                */

      struct {
        __OM  uint32_t txdata   : 8;            /*!< [7..0] Tx data.Note: Bit 0 is the least significant bit. It
                                                     is the first bit serially transmitted.                                    */
              uint32_t          : 24;
      } thr_b;
    } ;
  };

  union {
    __IOM uint32_t miscr;                       /*!< (@ 0x00000028) MISC Control Register                                      */

    struct {
      __IOM uint32_t irda_enable : 1;           /*!< [0..0] 1: UART is co-work with IRDA SIR mode. i.e., txd/rxd
                                                     are irda signals0: UART mode only.                                        */
      __IOM uint32_t txdma_en   : 1;            /*!< [1..1] 1: txdma is enabled (valid when dma_mode in FCR is 1'b1)0:
                                                     txdma is disabled                                                         */
      __IOM uint32_t rxdma_en   : 1;            /*!< [2..2] 1: rxdma is enabled (valid when dma_mode in FCR is 1'b1)0:
                                                     rxdma is disabled                                                         */
      __IOM uint32_t txdma_burstsize : 5;       /*!< [7..3] Txdma burstsize                                                    */
      __IOM uint32_t rxdma_burstsize : 6;       /*!< [13..8] Rxdma burstsize                                                   */
      __IOM uint32_t irda_tx_inv : 1;           /*!< [14..14] Invert irda_tx_o when 1; Default is 0;Note: Default
                                                     IRDA TX Pulse is High Active                                              */
      __IOM uint32_t irda_rx_inv : 1;           /*!< [15..15] Invert irda_rx_i when 1;Default is 0;Note: Default
                                                     IRDA RX pulse is Low Active                                               */
            uint32_t            : 16;
    } miscr_b;
  } ;

  union {
    __IOM uint32_t txplsr;                      /*!< (@ 0x0000002C) IRDA SIR TX Pulse Width Control 0 Register                 */

    struct {
      __IOM uint32_t txpulse_lowbound_shiftval : 15;/*!< [14..0] The shift value of SIR tx pulse's left edge positionThe
                                                     nominal IRDA SIR tx pulse width is 3/16 bit time. If want
                                                     to increase or decrease the left edge position of tx pulse
                                                     then must change the value. Note: In time unit of uart
                                                     clock period. Nominally the 10ns.(100Mhz uart clk)                        */
      __IOM uint32_t lowbound_shiftright : 1;   /*!< [15..15] 0: shift left (minus offset value of txplsr[14:0])1:
                                                     shift right (plus offset value txplsr[14:0])                              */
      __IOM uint32_t txpulse_upperbound_shiftval : 15;/*!< [30..16] The shift value of SIR tx pulse's right edge position.
                                                     The nominal IRDA SIR tx pulse width is 3/16 bit time. If
                                                     want to increase or decrease the right edge position of
                                                     tx pulse then must change this value. Note: In time unit
                                                     of uart clock period. Nominally the 10ns.(100Mhz uart clk)                */
      __IOM uint32_t upperbound_shiftright : 1; /*!< [31..31] 0: shift left (minus offset value of txplsr[30:16])1:
                                                     shift right (plus offset value txplsr[30:16])                             */
    } txplsr_b;
  } ;
  __IM  uint32_t  RESERVED[3];

  union {
    __IM  uint32_t dbg_uart;                    /*!< (@ 0x0000003C) Debug Register                                             */

    struct {
      __IM  uint32_t dbg_uart   : 32;           /*!< [31..0] dbg_urt[31:0]: debug port output value, depend on dbg_sel
                                                     value in SCR[2:0]                                                         */
    } dbg_uart_b;
  } ;

  union {
    __IOM uint32_t rfcr;                        /*!< (@ 0x00000040) RX Filter Control Register                                 */

    struct {
      __IOM uint32_t rf_len     : 1;            /*!< [0..0] Set the length of received data to be check.0: Check
                                                     the first 1 received byte only.1: Check the first 2 received
                                                     bytes.                                                                    */
      __IOM uint32_t rf_mask_en : 1;            /*!< [1..1] Enable the mask operation for received data.0: No mask,
                                                     compare the received bytes with the magic pattern directly.1:
                                                     Mask enabled, received data needs to ''AND'' with mask
                                                     value before it to be compared with magic pattern.                        */
      __IOM uint32_t rf_cmp_op  : 2;            /*!< [3..2] Set the RX filter comparing rule.The ''matched'' condition
                                                     is listed as following table:RF_LEN = 0: RF_CMP_OP =  0
                                                     (AND) 1st byte = Magic Pattern1 1 (OR) (1st byte = Magic
                                                     Pattern1) OR (1st byte = Magic Pattern2) 2 (XOR) (1st byte
                                                     != Magic Pattern1) AND (1st byte != Magic Pattern2)RF_LEN
                                                     = 1: RF_CMP_OP =  0 (AND) (1st byte = Magic Pattern1) AND
                                                     (2nd byte = Magic Pattern2) 1 (OR) (2nd byte = Magic Pattern1)
                                                     OR (2nd byte = Magic Pattern2) 2 (XOR) (1st byte != Magic
                                                     Pa                                                                        */
            uint32_t            : 3;
      __IOM uint32_t rf_en      : 1;            /*!< [7..7] RX Filter enable control0: Disable1: Enable                        */
            uint32_t            : 24;
    } rfcr_b;
  } ;

  union {
    __IOM uint32_t rfmpr;                       /*!< (@ 0x00000044) RX Filter Magic Pattern Register                           */

    struct {
      __IOM uint32_t rf_mp1     : 8;            /*!< [7..0] The magic pattern1 for the 1st received byte checking.             */
      __IOM uint32_t rf_mp2     : 8;            /*!< [15..8] The magic pattern2 for the 2nd received byte checking.            */
            uint32_t            : 16;
    } rfmpr_b;
  } ;

  union {
    __IOM uint32_t rfmvr;                       /*!< (@ 0x00000048) RX Filter Mask Value Register                              */

    struct {
      __IOM uint32_t rf_mv1     : 8;            /*!< [7..0] The mask value for the 1st received byte.                          */
      __IOM uint32_t rf_mv2     : 8;            /*!< [15..8] The mask value for the 2nd received byte.                         */
            uint32_t            : 16;
    } rfmvr_b;
  } ;

  union {
    __IOM uint32_t rftor;                       /*!< (@ 0x0000004C) RX Filter Timeout Register                                 */

    struct {
      __IOM uint32_t rf_timeout : 20;           /*!< [19..0] Set the timeout value of the RX filter idle detection.
                                                     This value is number of ticks. A tick time is equal to
                                                     a UART bit time.                                                          */
            uint32_t            : 12;
    } rftor_b;
  } ;

  union {
    __IOM uint32_t rflvr;                       /*!< (@ 0x00000050) RX FIFO Level Register                                     */

    struct {
      __IM  uint32_t rx_fifo_lv : 6;            /*!< [5..0] The level of the RX FIFO. This value indicates the number
                                                     of data bytes in the RX FIFO.                                             */
            uint32_t            : 26;
    } rflvr_b;
  } ;

  union {
    __IOM uint32_t tflvr;                       /*!< (@ 0x00000054) TX FIFO Level Register                                     */

    struct {
      __IM  uint32_t tx_fifo_lv : 5;            /*!< [4..0] The level of the TX FIFO. This value indicates the number
                                                     of data bytes in the TX FIFO.                                             */
            uint32_t            : 27;
    } tflvr_b;
  } ;

  union {
    __IOM uint32_t visr;                        /*!< (@ 0x00000058) Vendor Interrupt Status Register                           */

    struct {
      __IOM uint32_t rf_match_patt : 1;         /*!< [0..0] The interrupt status of RX filter pattern checking matched.
                                                     Write 1 to clear this interrupt status.0: Interrupt is
                                                     not pending.1: Interrupt is pending.                                      */
      __IOM uint32_t rf_timeout : 1;            /*!< [1..1] This bit indicates the interrupt pending status of the
                                                     RX filter timeout occurred. The RX idle detection mechanism
                                                     is used to check whether the receiving is in idle state
                                                     for re-aquire pattern matching. This mechanism uses a timer
                                                     to monitor new data receiving. This timer will reload the
                                                     initial value whenever a new byte is received. If the timeout
                                                     occurred (timer value countdown to 0), the RX filter will
                                                     be reset to the initialed state and restart the first received
                                                     1 or 2 bytes checking.                                                    */
      __IOM uint32_t tx_fifo_lv : 1;            /*!< [2..2] This bit indicates the interrupt pending status of the
                                                     TX FIFO water level equal to the level setting. The software
                                                     can use this interrupt to know the TX FIFO water level
                                                     is low and refill the TX FIFO. To enable this interrupt,
                                                     IER bit[5] should be written as 1.Write 1 to this bit will
                                                     clear the pending status.                                                 */
      __IOM uint32_t rx_idle_timeout : 1;       /*!< [3..3] This bit indicate the receiver idle timeout interrupt
                                                     pending status. Write 1 to this bit will clear the pending
                                                     status.                                                                   */
            uint32_t            : 28;
    } visr_b;
  } ;

  union {
    __IOM uint32_t vier;                        /*!< (@ 0x0000005C) Vendor Interrupt Enabling Control Register                 */

    struct {
      __IOM uint32_t rf_match_int_en : 1;       /*!< [0..0] The Rx filter pattern matched interrupt enabling control:1:
                                                     enable0: disable                                                          */
      __IOM uint32_t rf_timeout_int_en : 1;     /*!< [1..1] The Rx filter idle timeout interrupt enabling control:1:
                                                     enable0: disable                                                          */
      __IOM uint32_t tx_fifo_lv_int_en : 1;     /*!< [2..2] The TX FIFO water level interrupt enabling control:1:
                                                     enable0: disable                                                          */
      __IOM uint32_t rx_idle_timeout_en : 1;    /*!< [3..3] The RX idle timeout interrupt enabling control:1: enable0:
                                                     disable                                                                   */
            uint32_t            : 28;
    } vier_b;
  } ;

  union {
    __IOM uint32_t ritor;                       /*!< (@ 0x00000060) RX Idle Timeout Register                                   */

    struct {
      __IOM uint32_t rxidle_timeout_value : 4;  /*!< [3..0] Time unit is the duration of a UART bit, depends on the
                                                     baud-rate setting. Default 0.0: 8 bit time. (1*8)1: 16
                                                     bit time. (2*8)2: 32 bit time. (2^2*8)3: 64 bit time. (2^3*8)4:
                                                     128 bit time. (2^4*8)5: 256 bit time. (2^5*8)6: 512 bit
                                                     time. (2^6*8)7: 1024 bit time. (2^7*8)8: 2048 bit time.
                                                     (2^8*8)9: 4096 bit time. (2^9*8)10: 8192 bit time. (2^10*8)11:
                                                     16384 bit time. (2^11*8)12: 32768 bit time. (2^12*8)13:
                                                     65535 bit time. (2^13*8)14: 131072 bit time. (2^14*8)15:
                                                     262144 bit time                                                           */
            uint32_t            : 27;
      __IOM uint32_t rx_idle_timeout_en : 1;    /*!< [31..31] RX idle timeout enable, default 0.                               */
    } ritor_b;
  } ;
} UART_TypeDef;                                   /*!< Size = 100 (0x64)                                                         */



/* =========================================================================================================================== */
/* ================                                           SSI0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SSI supports 8 bit and 16 bit frame format with different combination of clock phase and clock polarity(mode 0 ~ mode 3). SSI0 & SSI1 are SPI master devices. SSI2 & SSI3 are slave devices. (SSI0)
  */

typedef struct {                                /*!< (@ 0x40042800) SSI0 Structure                                             */

  union {
    __IOM uint32_t ctrlr0;                      /*!< (@ 0x00000000) SSI Control Register 0                                     */

    struct {
      __IOM uint32_t dfs        : 4;            /*!< [3..0] RSVD                                                               */
      __IOM uint32_t frf        : 2;            /*!< [5..4] RSVD                                                               */
      __IOM uint32_t scph       : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t scpol      : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t tmod       : 2;            /*!< [9..8] RSVD                                                               */
      __IOM uint32_t slv_oe     : 1;            /*!< [10..10] RSVD                                                             */
            uint32_t            : 1;
      __IOM uint32_t cfs        : 4;            /*!< [15..12] RSVD                                                             */
            uint32_t            : 5;
      __IOM uint32_t tx_byte_swap : 1;          /*!< [21..21] RSVD                                                             */
      __IOM uint32_t tx_bit_swap : 1;           /*!< [22..22] RSVD                                                             */
      __IOM uint32_t rx_byte_swap : 1;          /*!< [23..23] RSVD                                                             */
      __IOM uint32_t rx_bit_swap : 1;           /*!< [24..24] RSVD                                                             */
            uint32_t            : 6;
      __IOM uint32_t ss_t       : 1;            /*!< [31..31] RSVD                                                             */
    } ctrlr0_b;
  } ;

  union {
    __IOM uint32_t ctrlr1;                      /*!< (@ 0x00000004) SSI Control Register 1                                     */

    struct {
      __IOM uint32_t ndf        : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } ctrlr1_b;
  } ;

  union {
    __IOM uint32_t ssienr;                      /*!< (@ 0x00000008) SSI Enable Register                                        */

    struct {
      __IOM uint32_t ssi_en     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } ssienr_b;
  } ;

  union {
    __IOM uint32_t mwcr;                        /*!< (@ 0x0000000C) Microwire Control Register                                 */

    struct {
      __IOM uint32_t mwmod      : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t mdd        : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t mhs        : 1;            /*!< [2..2] RSVD                                                               */
            uint32_t            : 29;
    } mwcr_b;
  } ;

  union {
    __IOM uint32_t ser;                         /*!< (@ 0x00000010) Slave Enable Register                                      */

    struct {
      __IOM uint32_t ser        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } ser_b;
  } ;

  union {
    __IOM uint32_t baudr;                       /*!< (@ 0x00000014) Baud Rate Select Register                                  */

    struct {
      __IOM uint32_t sckdv      : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } baudr_b;
  } ;

  union {
    __IOM uint32_t txftlr;                      /*!< (@ 0x00000018) Transmit FIFO Threshold Level                              */

    struct {
      __IOM uint32_t tft        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } txftlr_b;
  } ;

  union {
    __IOM uint32_t rxftlr;                      /*!< (@ 0x0000001C) Receive FIFO Threshold Level                               */

    struct {
      __IOM uint32_t rft        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } rxftlr_b;
  } ;

  union {
    __IOM uint32_t txflr;                       /*!< (@ 0x00000020) Transmit FIFO Level Register                               */

    struct {
      __IM  uint32_t txtfl      : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } txflr_b;
  } ;

  union {
    __IM  uint32_t rxflr;                       /*!< (@ 0x00000024) Receive FIFO Level Register                                */

    struct {
      __IM  uint32_t rxtfl      : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } rxflr_b;
  } ;

  union {
    __IM  uint32_t sr;                          /*!< (@ 0x00000028) Status Register                                            */

    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] RSVD                                                               */
      __IM  uint32_t tfnf       : 1;            /*!< [1..1] RSVD                                                               */
      __IM  uint32_t tfe        : 1;            /*!< [2..2] RSVD                                                               */
      __IM  uint32_t rfne       : 1;            /*!< [3..3] RSVD                                                               */
      __IM  uint32_t rff        : 1;            /*!< [4..4] RSVD                                                               */
      __IM  uint32_t txe        : 1;            /*!< [5..5] RSVD                                                               */
            uint32_t            : 26;
    } sr_b;
  } ;

  union {
    union {
      __IOM uint32_t imr;                       /*!< (@ 0x0000002C) Interrupt Mask Register                                    */

      struct {
        __IOM uint32_t txeim    : 1;            /*!< [0..0] RSVD                                                               */
        __IOM uint32_t txoim    : 1;            /*!< [1..1] RSVD                                                               */
        __IOM uint32_t rxuim    : 1;            /*!< [2..2] RSVD                                                               */
        __IOM uint32_t rxoim    : 1;            /*!< [3..3] RSVD                                                               */
        __IOM uint32_t rxfim    : 1;            /*!< [4..4] RSVD                                                               */
        __IOM uint32_t mstim    : 1;            /*!< [5..5] RSVD                                                               */
        __IOM uint32_t txuim    : 1;            /*!< [6..6] RSVD                                                               */
        __IOM uint32_t ssrim    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } imr_b;
    } ;

    union {
      __IOM uint32_t imr_slv;                   /*!< (@ 0x0000002C) Interrupt Mask of RTK-SPI Slave Register                   */

      struct {
        __IOM uint32_t txeim    : 1;            /*!< [0..0] RSVD                                                               */
        __IOM uint32_t txoim    : 1;            /*!< [1..1] RSVD                                                               */
        __IOM uint32_t rxuim    : 1;            /*!< [2..2] RSVD                                                               */
        __IOM uint32_t rxoim    : 1;            /*!< [3..3] RSVD                                                               */
        __IOM uint32_t rxfim    : 1;            /*!< [4..4] RSVD                                                               */
        __IOM uint32_t faeim    : 1;            /*!< [5..5] RSVD                                                               */
        __IOM uint32_t txuim    : 1;            /*!< [6..6] RSVD                                                               */
        __IOM uint32_t ssrim    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } imr_slv_b;
    } ;
  };

  union {
    union {
      __IM  uint32_t isr;                       /*!< (@ 0x00000030) Interrupt Status Register                                  */

      struct {
        __IM  uint32_t txeis    : 1;            /*!< [0..0] RSVD                                                               */
        __IM  uint32_t txois    : 1;            /*!< [1..1] RSVD                                                               */
        __IM  uint32_t rxuis    : 1;            /*!< [2..2] RSVD                                                               */
        __IM  uint32_t rxois    : 1;            /*!< [3..3] RSVD                                                               */
        __IM  uint32_t rxfis    : 1;            /*!< [4..4] RSVD                                                               */
        __IM  uint32_t mstis    : 1;            /*!< [5..5] RSVD                                                               */
        __IM  uint32_t txuis    : 1;            /*!< [6..6] RSVD                                                               */
        __IM  uint32_t ssris    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } isr_b;
    } ;

    union {
      __IM  uint32_t isr_slv;                   /*!< (@ 0x00000030) Interrupt Status Register                                  */

      struct {
        __IM  uint32_t txeis    : 1;            /*!< [0..0] RSVD                                                               */
        __IM  uint32_t txois    : 1;            /*!< [1..1] RSVD                                                               */
        __IM  uint32_t rxuis    : 1;            /*!< [2..2] RSVD                                                               */
        __IM  uint32_t rxois    : 1;            /*!< [3..3] RSVD                                                               */
        __IM  uint32_t rxfis    : 1;            /*!< [4..4] RSVD                                                               */
        __IM  uint32_t faeis    : 1;            /*!< [5..5] RSVD                                                               */
        __IM  uint32_t txuis    : 1;            /*!< [6..6] RSVD                                                               */
        __IM  uint32_t ssris    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } isr_slv_b;
    } ;
  };

  union {
    union {
      __IM  uint32_t risr;                      /*!< (@ 0x00000034) Raw Interrupt Status Register                              */

      struct {
        __IM  uint32_t txeir    : 1;            /*!< [0..0] RSVD                                                               */
        __IM  uint32_t txoir    : 1;            /*!< [1..1] RSVD                                                               */
        __IM  uint32_t rxuir    : 1;            /*!< [2..2] RSVD                                                               */
        __IM  uint32_t rxoir    : 1;            /*!< [3..3] RSVD                                                               */
        __IM  uint32_t rxfir    : 1;            /*!< [4..4] RSVD                                                               */
        __IM  uint32_t mstir    : 1;            /*!< [5..5] RSVD                                                               */
        __IM  uint32_t txuir    : 1;            /*!< [6..6] RSVD                                                               */
        __IM  uint32_t ssrir    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } risr_b;
    } ;

    union {
      __IM  uint32_t risr_slv;                  /*!< (@ 0x00000034) Raw Interrupt Status Register                              */

      struct {
        __IM  uint32_t txeir    : 1;            /*!< [0..0] RSVD                                                               */
        __IM  uint32_t txoir    : 1;            /*!< [1..1] RSVD                                                               */
        __IM  uint32_t rxuir    : 1;            /*!< [2..2] RSVD                                                               */
        __IM  uint32_t rxoir    : 1;            /*!< [3..3] RSVD                                                               */
        __IM  uint32_t rxfir    : 1;            /*!< [4..4] RSVD                                                               */
        __IM  uint32_t faeir    : 1;            /*!< [5..5] RSVD                                                               */
        __IM  uint32_t txuir    : 1;            /*!< [6..6] RSVD                                                               */
        __IM  uint32_t ssrir    : 1;            /*!< [7..7] RSVD                                                               */
              uint32_t          : 24;
      } risr_slv_b;
    } ;
  };

  union {
    __IM  uint32_t txoicr;                      /*!< (@ 0x00000038) Transmit FIFO Overflow Interrupt Clear Register            */

    struct {
      __IM  uint32_t txoicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } txoicr_b;
  } ;

  union {
    __IM  uint32_t rxoicr;                      /*!< (@ 0x0000003C) Receive FIFO Overflow Interrupt Clear Register             */

    struct {
      __IM  uint32_t rxoicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } rxoicr_b;
  } ;

  union {
    __IM  uint32_t rxuicr;                      /*!< (@ 0x00000040) Receive FIFO Underflow Interrupt Clear Register            */

    struct {
      __IM  uint32_t rxuicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } rxuicr_b;
  } ;

  union {
    union {
      __IM  uint32_t msticr;                    /*!< (@ 0x00000044) Multi-Master Interrupt Clear Register                      */

      struct {
        __IM  uint32_t msticr   : 1;            /*!< [0..0] RSVD                                                               */
              uint32_t          : 31;
      } msticr_b;
    } ;

    union {
      __IM  uint32_t faeicr;                    /*!< (@ 0x00000044) Frame Alignment Interrupt Clear Register                   */

      struct {
        __IM  uint32_t faeicr   : 1;            /*!< [0..0] RSVD                                                               */
              uint32_t          : 31;
      } faeicr_b;
    } ;
  };

  union {
    __IM  uint32_t icr;                         /*!< (@ 0x00000048) Interrupt Clear Register                                   */
    
    struct {
      __IM  uint32_t icr        : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } icr_b;
  } ;
  
  union {
    __IOM uint32_t dmacr;                       /*!< (@ 0x0000004C) DMA Control Register                                       */
    
    struct {
      __IOM uint32_t rdmae      : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t tdmae      : 1;            /*!< [1..1] RSVD                                                               */
            uint32_t            : 30;
    } dmacr_b;
  } ;
  
  union {
    __IOM uint32_t dmatdlr;                     /*!< (@ 0x00000050) DMA Transmit Data Level Register                           */
    
    struct {
      __IOM uint32_t dmatdl     : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } dmatdlr_b;
  } ;
  
  union {
    __IOM uint32_t dmardlr;                     /*!< (@ 0x00000054) DMA Receive Data Level Register                            */
    
    struct {
      __IOM uint32_t dmardl     : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } dmardlr_b;
  } ;
  
  union {
    __IM  uint32_t txuicr;                      /*!< (@ 0x00000058) Transmit FIFO Underflow Interrupt Clear Register           */
    
    struct {
      __IM  uint32_t txuicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } txuicr_b;
  } ;
  
  union {
    __IM  uint32_t ssricr;                      /*!< (@ 0x0000005C) SS_N Rising Edge Detect Interrupt Clear Register           */
    
    struct {
      __IM  uint32_t ssiicr     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } ssricr_b;
  } ;
  
  union {
    __IOM uint16_t dr;                          /*!< (@ 0x00000060) Data Register                                              */
    
    struct {
      __IOM uint16_t dr         : 16;           /*!< [15..0] RSVD                                                              */
    } dr_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1[35];
  
  union {
    __IOM uint32_t rx_sample_dly;               /*!< (@ 0x000000F0) Rx Sample Delay Register                                   */
    
    struct {
      __IOM uint32_t rsd        : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } rx_sample_dly_b;
  } ;
} SSI_Type;                                    /*!< Size = 244 (0xf4)                                                         */



/* =========================================================================================================================== */
/* ================                                           I2C0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief I2C with 7-bit/10-bit SS/FS/HS mode in master and slave mode transmission (I2C0)
  */

/* =========================================================================================================================== */
/* ================                                            SI                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief Serial Interface for setting the audio codec. (SI)
  */

typedef struct {                                /*!< (@ 0x40013000) SI Structure                                               */
  
  union {
    __IOM uint32_t ctrl;                        /*!< (@ 0x00000000) SI Control Register                                        */
    
    struct {
      __IOM uint32_t si_wr_start : 1;           /*!< [0..0] Write value to codec.0: This bit will be cleared when
                                                     wriring is done.1: Start to perform SI write to audio codec.              */
            uint32_t            : 3;
      __IOM uint32_t si_read_start : 1;         /*!< [4..4] Read value form codec0: This bit will be cleared when
                                                     reading is done.1: Start to perform SI read to audio codec.               */
            uint32_t            : 2;
      __IOM uint32_t si_disable : 1;            /*!< [7..7] 0: Si is enabled.1: Si is disabled.                                */
      __IOM uint32_t si_address : 8;            /*!< [15..8] Set the 8 bit address of audio codec.                             */
      __IOM uint32_t si_data    : 16;           /*!< [31..16] For si write, the data is written to the codec register.For
                                                     si read, the data is read out the codec register.                         */
    } ctrl_b;
  } ;
  
  union {
    __IOM uint32_t clk_ctrl;                    /*!< (@ 0x00000004) SI Clock Control Register                                  */
    
    struct {
      __IOM uint32_t reg_dk_en  : 1;            /*!< [0..0] To save power, reset this bit to gate CLK when the registers
                                                     are already programmed.0: Turn off the clock.1: Turn off
                                                     the clock of the register bank of audio codec.                            */
            uint32_t            : 31;
    } clk_ctrl_b;
  } ;
} SI_Type;                                      /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                           SPORT                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Audio interface for the codec (SPORT)
  */

typedef struct {                                /*!< (@ 0x40066000) SPORT Structure                                            */
  
  union {
    __OM  uint32_t sp_tx_fifo_0;                /*!< (@ 0x00000000) SPORT TX FIFO Register                                     */
    
    struct {
      __OM  uint32_t sp_tx_fifo_0 : 32;         /*!< [31..0] TX FIFO 0 address                                                 */
    } sp_tx_fifo_0_b;
  } ;
  
  union {
    __IOM uint32_t sp_con;                      /*!< (@ 0x00000004) SPORT Control Register                                     */
    
    struct {
      __IOM uint32_t sp_reset   : 1;            /*!< [0..0] Reset SPORT0 module0: disable reset1: reset SPORT0 module.
                                                     Write 1 first and then write 0.                                           */
      __IOM uint32_t sp_tx_inv_i2s_sclk : 1;    /*!< [1..1] Sclk to TX path is inverted.0: sclk to TX path is not
                                                     inverted.1: sclk to TX path is inverted.                                  */
      __IOM uint32_t sp_rx_inv_i2s_sclk : 1;    /*!< [2..2] Sclk to RX path is inverted.0: sclk to RX path is not
                                                     inverted.1: sclk to RX path is inverted.                                  */
      __IOM uint32_t sp_slave_clk_sel : 1;      /*!< [3..3] I2S or PCM slave for CLK path.0: To be not an I2S or
                                                     PCM slave 1: To be an I2S or PCM slave                                    */
      __IOM uint32_t sp_slave_data_sel : 1;     /*!< [4..4] I2S or PCM slave for DATA path.0: To be not an I2S or
                                                     PCM slave 1: To be an I2S or PCM slave                                    */
      __IOM uint32_t sp_wclk_tx_inverse : 1;    /*!< [5..5] Inverte I2S/PCM word clock for TX.0: I2S/PCM word clock
                                                     is not inverted1: I2S/PCM word clock is inverted                          */
      __IOM uint32_t sp_loopback : 1;           /*!< [6..6] Self loopback mode.0: Off.1: Enable self loopback mode.            */
      __IOM uint32_t sp_mcu_ctl_mode : 1;       /*!< [7..7] Select DMA mode or FIFO mode.0: Internal DMA mode.1:
                                                     FIFO mode.                                                                */
      __IOM uint32_t sp_data_format_sel_tx : 2; /*!< [9..8] Set data format00: I2S01: Left Justified10: PCM mode
                                                     A11: PCM mode B                                                           */
      __IOM uint32_t sp_inv_i2s_sclk : 1;       /*!< [10..10] Set bclk inverter0: I2S and PCM sclk is not inverted1:
                                                     I2S and PCM sclk is inverted                                              */
      __IOM uint32_t sp_en_i2s_mono_tx_0 : 1;   /*!< [11..11] Set mono or stereo for TX00: stereo1: mono                       */
      __IOM uint32_t sp_data_len_sel_tx_0 : 3;  /*!< [14..12] Set the TX0 data length000: 16 bits001: 20 bits010:
                                                     24 bits100: 32 bitsOthers: Reserved                                       */
      __IOM uint32_t sp_i2s_self_lpbk_en : 1;   /*!< [15..15] Internal loopback mode.0: Internal loopback mode is
                                                     not enabled1: Internal loopback mode is enabled                           */
      __IOM uint32_t sp_tx_disable : 1;         /*!< [16..16] SPORT TX control.0: SPORT TX is enabled1: SPORT TX
                                                     is disabled                                                               */
      __IOM uint32_t sp_start_tx : 1;           /*!< [17..17] Start TX.0: TX is disabled1: TX is started                       */
      __IOM uint32_t sp_tdm_mode_sel_tx : 2;    /*!< [19..18] TDM TX channel control00: Without TDM01: 4 channels
                                                     in the TDM mode10: 6 channels in the TDM mode11: 8 channels
                                                     in the TDM mode                                                           */
      __IOM uint32_t sp_tdm_mode_sel_rx : 2;    /*!< [21..20] TDM RX channel control00: Without TDM01: 4 channels
                                                     in the TDM mode10: 6 channels in the TDM mode11: 8 channels
                                                     in the TDM mode                                                           */
      __IOM uint32_t sp_tx_lsb_first_0 : 1;     /*!< [22..22] MSB or LSB control for TX0.0: MSB first 1: LSB first             */
      __IOM uint32_t sp_rx_lsb_first_0 : 1;     /*!< [23..23] MSB or LSB control for RX0.0: MSB first 1: LSB first             */
      __IOM uint32_t sp_rx_disable : 1;         /*!< [24..24] SPORT RX control.0: SPORT RX is enabled1: SPORT RX
                                                     is disabled                                                               */
      __IOM uint32_t sp_start_rx : 1;           /*!< [25..25] Start RX.0: RX is disabled1: RX is started                       */
      __IOM uint32_t sp_sel_i2s_tx_ch : 2;      /*!< [27..26] Control L and R channel data for TX.00: L/R01: R/L10:
                                                     L/L11: R/RWithout TDM only                                                */
      __IOM uint32_t sp_sel_i2s_rx_ch : 2;      /*!< [29..28] Control L and R channel data for RX.00: L/R01: R/L10:
                                                     L/L11: R/RWithout TDM only                                                */
      __IOM uint32_t sp_mclk_sel : 2;           /*!< [31..30] Select MCLK output01 and 11: MCLK output = SP_SRC_CLK
                                                     / 100: MCLK output = SP_SRC_CLK / 210: MCLK output = SP_SRC_CLK
                                                     / 4                                                                       */
    } sp_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_fifo_en_clk_con;          /*!< (@ 0x00000008) SPORT FIFO Enable and Clock Control Register               */
    
    struct {
      __IOM uint32_t sp_bclk_reset : 1;         /*!< [0..0] 0: Stop reset1: Stop BCLK, and reset the state machine
                                                     of the clock generator.                                                   */
      __IOM uint32_t sp_tx_fifo_reset : 1;      /*!< [1..1] 0: Stop reset1: Reset TX FIFO to make TX FIFO data become
                                                     zero                                                                      */
      __IOM uint32_t sp_rx_fifo_reset : 1;      /*!< [2..2] 0: Stop reset1: Reset RX FIFO to make TX FIFO data become
                                                     zero                                                                      */
            uint32_t            : 5;
      __IOM uint32_t sp_debug_bus_sel : 3;      /*!< [10..8] 000: Debug_bus_a001: Debug_bus_bect.                              */
      __IOM uint32_t sp_enable_mclk : 1;        /*!< [11..11] 0: Disable1: Enable MCLK                                         */
      __IOM uint32_t sp_clear_tx_err_cnt : 1;   /*!< [12..12] Write 1 and then write 0 to clear TX error counter.              */
      __IOM uint32_t sp_clear_rx_err_cnt : 1;   /*!< [13..13] Write 1 and then write 0 to clear RX error counter.              */
      __IOM uint32_t sp_clk_sel : 2;            /*!< [15..14] 00 and 01: SP_CLK = SP_SRC_CLK10: SP_CLK = SP_SRC_CLK
                                                     / 211: SP_CLK = SP_SRC_CLK / 4                                            */
            uint32_t            : 4;
      __IOM uint32_t sp_tx_src_byte_swap_0 : 1; /*!< [20..20] 0: Disable1: Swap H/L bytes read from the source memory
                                                     of TX_FIFO_0                                                              */
      __IOM uint32_t sp_tx_src_lr_swap_0 : 1;   /*!< [21..21] 0: Disable1: Swap L/R audio samples read from the source
                                                     memory of TX_FIFO_0                                                       */
      __IOM uint32_t sp_rx_snk_byte_swap_0 : 1; /*!< [22..22] 0: Disable1: Swap H/L bytes written to the sink memory
                                                     of RX_FIFO_0                                                              */
      __IOM uint32_t sp_rx_snk_lr_swap_0 : 1;   /*!< [23..23] 0: Disable1: Swap L/R audio samples written to the
                                                     sink memory of RX_FIFO_0                                                  */
      __IOM uint32_t sp_tx_fifo_0_ch0_1_en : 1; /*!< [24..24] 0: Disable1: Enable the CH0 and CH1 of TX_FIFO_0                 */
      __IOM uint32_t sp_tx_fifo_0_ch2_3_en : 1; /*!< [25..25] 0: Disable1: Enable the CH2 and CH3 of TX_FIFO_0                 */
      __IOM uint32_t sp_tx_fifo_1_ch4_5_en : 1; /*!< [26..26] 0: Disable1: Enable the CH4 and CH5 of TX_FIFO_1                 */
      __IOM uint32_t sp_tx_fifo_1_ch6_7_en : 1; /*!< [27..27] 0: Disable1: Enable the CH6 and CH7 of TX_FIFO_1                 */
      __IOM uint32_t sp_rx_fifo_0_ch0_1_en : 1; /*!< [28..28] 0: Disable1: Enable the CH0 and CH1 of RX_FIFO_0                 */
      __IOM uint32_t sp_rx_fifo_0_ch2_3_en : 1; /*!< [29..29] 0: Disable1: Enable the CH2 and CH3 of RX_FIFO_0                 */
      __IOM uint32_t sp_rx_fifo_1_ch4_5_en : 1; /*!< [30..30] 0: Disable1: Enable the CH4 and CH5 of RX_FIFO_1                 */
      __IOM uint32_t sp_rx_fifo_1_ch6_7_en : 1; /*!< [31..31] 0: Disable1: Enable the CH6 and CH7 of RX_FIFO_1                 */
    } sp_fifo_en_clk_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_fifo_intr_con;            /*!< (@ 0x0000000C) SPORT FIFO Interrupt Control Register                      */
    
    struct {
      __IOM uint32_t sp_clr_tx_fifo_th_intr_0 : 1;/*!< [0..0] For MCU mode (bypass DMA), F/W writes 1 and then 0 to
                                                     clear RX interrupt.Note: TX interrupt is to indicate that
                                                     MCU can write audio data to TX FIFO_0                                     */
      __IOM uint32_t sp_clr_rx_fifo_th_intr_0 : 1;/*!< [1..1] For MCU mode (bypass DMA), F/W writes 1 and then 0 to
                                                     clear RX interrupt.Note: RX interrupt is to indicate that
                                                     MCU can get audio data from RX FIFO_0                                     */
      __IOM uint32_t sp_clr_tx_fifo_full_intr_0 : 1;/*!< [2..2] Clear TX FIFO_0 full interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
      __IOM uint32_t sp_clr_rx_fifo_full_intr_0 : 1;/*!< [3..3] Clear RX FIFO_0 full interrupt. F/W writes 1 and then
                                                     0 to clear RX interrupt.                                                  */
      __IOM uint32_t sp_clr_tx_fifo_empty_0 : 1;/*!< [4..4] Clear TX FIFO_0 empty interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
      __IOM uint32_t sp_clr_rx_fifo_empty_0 : 1;/*!< [5..5] Clear RX FIFO_0 empty interrupt. F/W writes 1 and then
                                                     0 to clear RX interrupt.                                                  */
      __IOM uint32_t sp_clr_tx_idle_intr_0 : 1; /*!< [6..6] Clear TX FIFO_0 idle interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
      __IOM uint32_t sp_clr_tx_fifo_th_intr_1 : 1;/*!< [7..7] For MCU mode (bypass DMA), F/W writes 1 and then 0 to
                                                     clear RX interrupt.Note: TX interrupt is to indicate that
                                                     MCU can write audio data to TX FIFO_1                                     */
      __IOM uint32_t sp_clr_rx_fifo_th_intr_1 : 1;/*!< [8..8] For MCU mode (bypass DMA), F/W writes 1 and then 0 to
                                                     clear RX interrupt.Note: RX interrupt is to indicate that
                                                     MCU can get audio data from RX FIFO_1                                     */
      __IOM uint32_t sp_clr_tx_fifo_full_intr_1 : 1;/*!< [9..9] Clear TX FIFO_1 full interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
      __IOM uint32_t sp_clr_rx_fifo_full_intr_1 : 1;/*!< [10..10] Clear RX FIFO_1 full interrupt. F/W writes 1 and then
                                                     0 to clear RX interrupt.                                                  */
      __IOM uint32_t sp_clr_tx_fifo_empty_1 : 1;/*!< [11..11] Clear TX FIFO_1 empty interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
      __IOM uint32_t sp_clr_rx_fifo_empty_1 : 1;/*!< [12..12] Clear RX FIFO_1 empty interrupt. F/W writes 1 and then
                                                     0 to clear RX interrupt.                                                  */
      __IOM uint32_t sp_clr_tx_idle_intr_1 : 1; /*!< [13..13] Clear TX FIFO_1 idle interrupt. F/W writes 1 and then
                                                     0 to clear TX interrupt.                                                  */
            uint32_t            : 2;
      __IOM uint32_t sp_tx_fifo_th_intr_0_en : 1;/*!< [16..16] 0: Disable1: When TX FIFO_0 level is less than SP_TX_FIFO_TH,
                                                     generate the interrupt.                                                   */
      __IOM uint32_t sp_rx_fifo_th_intr_0_en : 1;/*!< [17..17] 0: Disable1: When RX FIFO_0 level is greater than SP_RX_FIFO_TH,
                                                     generate the interrupt.                                                   */
      __IOM uint32_t sp_tx_fifo_full_intr_0_en : 1;/*!< [18..18] 0: Disable1: Enable TX FIFO_0 full interrupt                  */
      __IOM uint32_t sp_rx_fifo_full_intr_0_en : 1;/*!< [19..19] 0: Disable1: Enable RX FIFO_0 full interrupt                  */
      __IOM uint32_t sp_tx_fifo_empty_0_en : 1; /*!< [20..20] 0: Disable1: Enable TX FIFO_0 empty interrupt                    */
      __IOM uint32_t sp_rx_fifo_empty_0_en : 1; /*!< [21..21] 0: Disable1: Enable RX FIFO_0 empty interrupt                    */
      __IOM uint32_t sp_tx_idle_intr_0_en : 1;  /*!< [22..22] 0: Disable1: Generate the interrupt when TX is working,
                                                     and TX FIFO_0 is empty.                                                   */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_fifo_th_intr_1_en : 1;/*!< [24..24] 0: Disable1: When TX FIFO_1 level is less than SP_TX_FIFO_TH,
                                                     generate the interrupt.                                                   */
      __IOM uint32_t sp_rx_fifo_th_intr_1_en : 1;/*!< [25..25] 0: Disable1: When RX FIFO_1 level is greater than SP_RX_FIFO_TH,
                                                     generate the interrupt.                                                   */
      __IOM uint32_t sp_tx_fifo_full_intr_1_en : 1;/*!< [26..26] 0: Disable1: Enable TX FIFO_1 full interrupt                  */
      __IOM uint32_t sp_rx_fifo_full_intr_1_en : 1;/*!< [27..27] 0: Disable1: Enable RX FIFO_1 full interrupt                  */
      __IOM uint32_t sp_tx_fifo_empty_1_en : 1; /*!< [28..28] 0: Disable1: Enable TX FIFO_1 empty interrupt                    */
      __IOM uint32_t sp_rx_fifo_empty_1_en : 1; /*!< [29..29] 0: Disable1: Enable RX FIFO_1 empty interrupt                    */
      __IOM uint32_t sp_tx_idle_intr_1_en : 1;  /*!< [30..30] 0: Disable1: Generate the interrupt when TX is working,
                                                     and TX FIFO_1 is empty.                                                   */
            uint32_t            : 1;
    } sp_fifo_intr_con_b;
  } ;
  
  union {
    __IM  uint32_t sp_rx_fifo_0;                /*!< (@ 0x00000010) SPORT RX FIFO_0 Register                                   */
    
    struct {
      __IM  uint32_t sp_rx_fifo_0 : 32;         /*!< [31..0] RX FIFO_0 data register                                           */
    } sp_rx_fifo_0_b;
  } ;
  
  union {
    __IM  uint32_t sp_fifo_cnt_sta;             /*!< (@ 0x00000014) SPORT FIFO Counter Status Register                         */
    
    struct {
      __IM  uint32_t sp_tx_depth_cnt_0 : 6;     /*!< [5..0] Read TX FIFO_0 depth status.When TX FIFO_0 is empty,
                                                     this value shows 32.                                                      */
            uint32_t            : 2;
      __IM  uint32_t sp_rx_depth_cnt_0 : 6;     /*!< [13..8] Read RX FIFO_0 depth status.When RX FIFO_0 is empty,
                                                     this value shows 32.                                                      */
            uint32_t            : 2;
      __IM  uint32_t sp_tx_depth_cnt_1 : 6;     /*!< [21..16] Read TX FIFO_1 depth status.When TX FIFO_1 is empty,
                                                     this value shows 32.                                                      */
            uint32_t            : 2;
      __IM  uint32_t sp_rx_depth_cnt_1 : 6;     /*!< [29..24] Read RX FIFO_1 depth status.When RX FIFO_1 is empty,
                                                     this value shows 32.                                                      */
            uint32_t            : 2;
    } sp_fifo_cnt_sta_b;
  } ;
  
  union {
    __IM  uint32_t sp_tx_rx_err_sta;            /*!< (@ 0x00000018) SPORT TX and RX Error Status Register                      */
    
    struct {
      __IM  uint32_t sp_tx_err_cnt : 16;        /*!< [15..0] TX error counterNote: This counter should always be
                                                     zero if everything works well.                                            */
      __IM  uint32_t sp_rx_err_cnt : 16;        /*!< [31..16] RX error counterNote: This counter should always be
                                                     zero if everything works well.                                            */
    } sp_tx_rx_err_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx_fra_div;               /*!< (@ 0x0000001C) SPORT TX Fractional Divider Register                       */
    
    struct {
      __IOM uint32_t sp_tx_mi   : 16;           /*!< [15..0] BCLK = 40MHz x (ni/mi) For example: BCLK=3.072MHz=40MHz
                                                     x (48/625)                                                                */
      __IOM uint32_t sp_tx_ni   : 15;           /*!< [30..16] the same mi                                                      */
      __IOM uint32_t sp_tx_mi_ni_update : 1;    /*!< [31..31] Update mi and ni.0: Off1: To update mi and ni to get
                                                     the new clock rate. This bit will be reset automatically
                                                     when the update is done.                                                  */
    } sp_tx_fra_div_b;
  } ;
  
  union {
    __IOM uint32_t sp_lrck_fifo_th_con;         /*!< (@ 0x00000020) SPORT LRCK and FIFO Threshold Control Register             */
    
    struct {
      __IOM uint32_t sp_tx_fifo_th : 6;         /*!< [5..0] Set TX FIFO interrupt and DMA request threshold.                   */
            uint32_t            : 2;
      __IOM uint32_t sp_rx_fifo_th : 6;         /*!< [13..8] Set RX FIFO interrupt and DMA request threshold.                  */
            uint32_t            : 2;
      __IOM uint32_t sp_bclk_div_ratio : 8;     /*!< [23..16] Control LRCK divider.                                            */
      __IOM uint32_t sp_rx_bclk_div_ratio : 8;  /*!< [31..24] Control RX LRCK divider.                                         */
    } sp_lrck_fifo_th_con_b;
  } ;
  
  union {
    __IM  uint32_t sp_fifo_intr_sta;            /*!< (@ 0x00000024) SPORT FIFO Interrupt Status Register                       */
    
    struct {
      __IM  uint32_t sp_tx_fifo_th_intr_0 : 1;  /*!< [0..0] Interrupt status1: It is ready to send data out                    */
      __IM  uint32_t sp_rx_fifo_th_intr_0 : 1;  /*!< [1..1] Interrupt status1: It is ready to send data out                    */
      __IM  uint32_t sp_tx_fifo_full_intr_0 : 1;/*!< [2..2] Interrupt status1: TX FIFO_0 is full                               */
      __IM  uint32_t sp_rx_fifo_full_intr_0 : 1;/*!< [3..3] Interrupt status1: RX FIFO_0 is full                               */
      __IM  uint32_t sp_tx_fifo_empty_intr_0 : 1;/*!< [4..4] Interrupt status1: TX FIFO_0 is empty                             */
      __IM  uint32_t sp_rx_fifo_empty_intr_0 : 1;/*!< [5..5] Interrupt status1: TX FIFO_0 is empty                             */
      __IM  uint32_t sp_tx_idle_intr_0 : 1;     /*!< [6..6] Interrupt status1: TX is working but FIFO_0 is empty.              */
      __IM  uint32_t sp_tx_fifo_th_intr_1 : 1;  /*!< [7..7] Interrupt status1: It is ready to send data out                    */
      __IM  uint32_t sp_rx_fifo_th_intr_1 : 1;  /*!< [8..8] Interrupt status1: It is ready to receive data                     */
      __IM  uint32_t sp_tx_fifo_full_intr_1 : 1;/*!< [9..9] Interrupt status1: TX FIFO_1 is full                               */
      __IM  uint32_t sp_rx_fifo_full_intr_1 : 1;/*!< [10..10] Interrupt status1: RX FIFO_1 is full                             */
      __IM  uint32_t sp_tx_fifo_empty_intr_1 : 1;/*!< [11..11] Interrupt status1: TX FIFO_1 is empty                           */
      __IM  uint32_t sp_rx_fifo_empty_intr_1 : 1;/*!< [12..12] Interrupt status1: RX FIFO_1 is empty                           */
      __IM  uint32_t sp_tx_idle_intr_1 : 1;     /*!< [13..13] Interrupt status1: TX is working but FIFO_1 is empty.            */
            uint32_t            : 10;
      __IM  uint32_t sp_tx_fifo_full_1 : 1;     /*!< [24..24] TX FIFO raw status1: TX FIFO_1 is full                           */
      __IM  uint32_t sp_rx_fifo_full_1 : 1;     /*!< [25..25] RX FIFO raw status1: RX FIFO_1 is full                           */
      __IM  uint32_t sp_tx_fifo_empty_1 : 1;    /*!< [26..26] TX FIFO raw status1: TX FIFO_1 is empty                          */
      __IM  uint32_t sp_rx_fifo_empty_1 : 1;    /*!< [27..27] RX FIFO raw status1: RX FIFO_1 is empty                          */
      __IM  uint32_t sp_tx_fifo_full_0 : 1;     /*!< [28..28] TX FIFO raw status1: TX FIFO_0 is full                           */
      __IM  uint32_t sp_rx_fifo_full_0 : 1;     /*!< [29..29] RX FIFO raw status1: RX FIFO_0 is full                           */
      __IM  uint32_t sp_tx_fifo_empty_0 : 1;    /*!< [30..30] TX FIFO raw status1: TX FIFO_0 is empty                          */
      __IM  uint32_t sp_rx_fifo_empty_0 : 1;    /*!< [31..31] RX FIFO raw status1: RX FIFO_0 is empty                          */
    } sp_fifo_intr_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_form_con;                 /*!< (@ 0x00000028) SPORT Format Control                                       */
    
    struct {
      __IOM uint32_t sp_trx_same_fs : 1;        /*!< [0..0] Support TX and RX use different sample rates.0: TX and
                                                     RX do not have the same sampling rate1: TX and RX have
                                                     the same sampling rate                                                    */
      __IOM uint32_t sp_trx_same_ch : 1;        /*!< [1..1] 0: Do not have the same channel setting.1: Have the same
                                                     channel setting. Both are either stereo or mono.                          */
      __IOM uint32_t sp_trx_same_length : 1;    /*!< [2..2] 0: Do not have the same data length.1: Have the same
                                                     data length.                                                              */
      __IOM uint32_t sp_bclk_out_inverse : 1;   /*!< [3..3] 0: Disable1: Invert the phase of BCLK                              */
            uint32_t            : 1;
      __IOM uint32_t sp_bclk_rx_inverse : 1;    /*!< [5..5] 0: Disable1: Invert the phase of LRCK_RX                           */
      __IOM uint32_t sp_fixed_bclk_sel : 1;     /*!< [6..6] 0: BCLK is fixed at SP_CLK / 41: BCLK is fixed at SP_CLK
                                                     / 2                                                                       */
      __IOM uint32_t sp_fixed_bclk : 1;         /*!< [7..7] 0: Disable the fixed BCLK1: Enable the fixed BCLK                  */
      __IOM uint32_t sp_data_format_sel_rx : 2; /*!< [9..8] It is valid if SP_TRX_SAME_FS is 0.Data format of SD_I00:
                                                     I2S01: Left Justified10: PCM mode A11: PCM mode B                         */
      __IOM uint32_t sp_trx_same_lrck : 1;      /*!< [10..10] 0: LRCK_RX is not as same as LRCK1: LRCK_RX is as same
                                                     as LRCK                                                                   */
      __IOM uint32_t sp_en_i2s_mono_rx_0 : 1;   /*!< [11..11] It is valid if SP_TRX_SAME_FS is 0.Data format of SD_I0:
                                                     stereo1: mono                                                             */
      __IOM uint32_t sp_data_len_sel_rx_0 : 3;  /*!< [14..12] It is valid if SP_TRX_SAME_FS is 0.Data length of SD_I000:
                                                     16 bits001: 20 bits010: 24 bits100: 32 bitsOthers: Reserved               */
            uint32_t            : 9;
      __IOM uint32_t sp_ch_len_sel_tx : 3;      /*!< [26..24] Set TX channel length.000: 16 bits001: 20 bits010:
                                                     24 bits100: 32 bitsOthers: Reserved                                       */
            uint32_t            : 1;
      __IOM uint32_t sp_ch_len_sel_rx : 3;      /*!< [30..28] Set RX channel length.000: 16 bits001: 20 bits010:
                                                     24 bits100: 32 bitsOthers: Reserved                                       */
      __IOM uint32_t sp_trx_same_ch_len : 1;    /*!< [31..31] 0: TX and RX channel length according to SP_CH_LEN_SEL_RX
                                                     and SP_CH_LEN_SEL_RX.1: Force that TX and RX have the same
                                                     channel length                                                            */
    } sp_form_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx_fra_div;               /*!< (@ 0x0000002C) SPORT RX Fractional Divider Register                       */
    
    struct {
      __IOM uint32_t sp_rx_mi   : 16;           /*!< [15..0] This fractional Divider mainly makes LRCK_RX.BCLK =
                                                     40MHz x (ni/mi) For example: BCLK=3.072MHz=40MHz x (48/625)               */
      __IOM uint32_t sp_rx_ni   : 15;           /*!< [30..16] the same mi                                                      */
      __IOM uint32_t sp_rx_mi_ni_update : 1;    /*!< [31..31] Update mi and ni.0: Off1: To update mi and ni to get
                                                     the new clock rate. This bit will be reset automatically
                                                     when the update is done.                                                  */
    } sp_rx_fra_div_b;
  } ;
  __IM  uint32_t  sp_rsvd_0;                    /*!< (@ 0x00000030) SPORT Reserve Register 0                                   */
  __IM  uint32_t  sp_rsvd_1;                    /*!< (@ 0x00000034) SPORT Reserve Register 1                                   */
  __IM  uint32_t  sp_rsvd_2;                    /*!< (@ 0x00000038) SPORT Reserve Register 2                                   */
  
  union {
    __IOM uint32_t sp_tx_slot_sele;             /*!< (@ 0x0000003C) SPORT TX Slot Selection Register                           */
    
    struct {
      __IOM uint32_t sp_tx_slot0_sel : 3;       /*!< [2..0] Select the data of slot 0.0: CH0 Data1: CH1 Data2: CH2
                                                     Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7: CH7
                                                     Data                                                                      */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot1_sel : 3;       /*!< [6..4] Select the data of slot 1.0: CH0 Data1: CH1 Data2: CH2
                                                     Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7: CH7
                                                     Data                                                                      */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot2_sel : 3;       /*!< [10..8] Select the data of slot 2.0: CH0 Data1: CH1 Data2: CH2
                                                     Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7: CH7
                                                     Data                                                                      */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot3_sel : 3;       /*!< [14..12] Select the data of slot 3.0: CH0 Data1: CH1 Data2:
                                                     CH2 Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7:
                                                     CH7 Data                                                                  */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot4_sel : 3;       /*!< [18..16] Select the data of slot 4.0: CH0 Data1: CH1 Data2:
                                                     CH2 Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7:
                                                     CH7 Data                                                                  */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot5_sel : 3;       /*!< [22..20] Select the data of slot 5.0: CH0 Data1: CH1 Data2:
                                                     CH2 Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7:
                                                     CH7 Data                                                                  */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot6_sel : 3;       /*!< [26..24] Select the data of slot 6.0: CH0 Data1: CH1 Data2:
                                                     CH2 Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7:
                                                     CH7 Data                                                                  */
            uint32_t            : 1;
      __IOM uint32_t sp_tx_slot7_sel : 3;       /*!< [30..28] Select the data of slot 7.0: CH0 Data1: CH1 Data2:
                                                     CH2 Data3: CH3 Data4: CH4 Data5: CH5 Data6: CH6 Data7:
                                                     CH7 Data                                                                  */
            uint32_t            : 1;
    } sp_tx_slot_sele_b;
  } ;
  
  union {
    __OM  uint32_t sp_tx_fifo_1;                /*!< (@ 0x00000040) SPORT TX FIFO_1 Register                                   */
    
    struct {
      __OM  uint32_t sp_tx_fifo_1 : 32;         /*!< [31..0] TX FIFO_1 data register                                           */
    } sp_tx_fifo_1_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx1_rx1_dat_con;          /*!< (@ 0x00000044) SPORT TX1 and RX1 Data Control Register                    */
    
    struct {
            uint32_t            : 26;
      __IOM uint32_t sp_tx_src_byte_swap_1 : 1; /*!< [26..26] 0: Disable1: Swap H/L bytes read from the source memory
                                                     of TX_FIFO_1                                                              */
      __IOM uint32_t sp_tx_src_lr_swap_1 : 1;   /*!< [27..27] 0: Disable1: Swap L/R audio samples read from the source
                                                     memory of TX_FIFO_1                                                       */
      __IOM uint32_t sp_rx_snk_byte_swap_1 : 1; /*!< [28..28] 0: Disable1: Swap H/L bytes written to the sink memory
                                                     of RX_FIFO_1                                                              */
      __IOM uint32_t sp_rx_snk_lr_swap_1 : 1;   /*!< [29..29] 0: Disable1: Swap L/R audio samples written to the
                                                     sink memory of RX_FIFO_1                                                  */
      __IOM uint32_t sp_tx_lsb_first_1 : 1;     /*!< [30..30] TX1 transmit0: MSB first1: LSB first                             */
      __IOM uint32_t sp_rx_lsb_first_1 : 1;     /*!< [31..31] RX1 transmit0: MSB first1: LSB first                             */
    } sp_tx1_rx1_dat_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx1_rx1_form_con;         /*!< (@ 0x00000048) SPORT TX1 and RX1 Format Control Register                  */
    
    struct {
            uint32_t            : 24;
      __IOM uint32_t sp_data_len_sel_tx_1 : 3;  /*!< [26..24] 000: 16 bits001: 20 bits010: 24 bits100: 32 bitsOthers:
                                                     Reserved                                                                  */
      __IOM uint32_t sp_en_i2s_mono_tx_1 : 1;   /*!< [27..27] 0: Stereo1: Mono                                                 */
      __IOM uint32_t sp_data_len_sel_rx_1 : 3;  /*!< [30..28] It is valid if SP_TRX_SAME_FS is 0.Data length of SD_I000:
                                                     16 bits001: 20 bits010: 24 bits100: 32 bitsOthers: Reserved               */
      __IOM uint32_t sp_en_i2s_mono_rx_1 : 1;   /*!< [31..31] It is valid if SP_TRX_SAME_FS is 0.Data format of SD_I0:
                                                     stereo1: mono                                                             */
    } sp_tx1_rx1_form_con_b;
  } ;
  __IM  uint32_t  sp_rsvd_3;                    /*!< (@ 0x0000004C) SPORT Reserve Register 3                                   */
  
  union {
    __IM  uint32_t sp_rx_fifo_1;                /*!< (@ 0x00000050) SPORT RX FIFO_1 Register                                   */
    
    struct {
      __IM  uint32_t sp_rx_fifo_1 : 32;         /*!< [31..0] RX FIFO_1 data register                                           */
    } sp_rx_fifo_1_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx_slot_sele_0_3ch;       /*!< (@ 0x00000054) SPORT RX Slot Selection 0-3 Channel Register               */
    
    struct {
      __IOM uint32_t sp_rx_ch0_sel : 3;         /*!< [2..0] Select the slot of CH0.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch1_sel : 3;         /*!< [10..8] Select the slot of CH1.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch2_sel : 3;         /*!< [18..16] Select the slot of CH2.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch3_sel : 3;         /*!< [26..24] Select the slot of CH3.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
    } sp_rx_slot_sele_0_3ch_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx_slot_sele_4_7ch;       /*!< (@ 0x00000058) SPORT RX Slot Selection 4-7 Channel Register               */
    
    struct {
      __IOM uint32_t sp_rx_ch4_sel : 3;         /*!< [2..0] Select the slot of CH4.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch5_sel : 3;         /*!< [10..8] Select the slot of CH5.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch6_sel : 3;         /*!< [18..16] Select the slot of CH6.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
      __IOM uint32_t sp_rx_ch7_sel : 3;         /*!< [26..24] Select the slot of CH7.0: Slot 01: Slot 12: Slot 23:
                                                     Slot 34: Slot 45: Slot 56: Slot 67: Slot 7                                */
            uint32_t            : 5;
    } sp_rx_slot_sele_4_7ch_b;
  } ;
  
  union {
    __IOM uint32_t sp_err_cnt_con;              /*!< (@ 0x0000005C) SPORT Error Count Control Register                         */
    
    struct {
      __IOM uint32_t sp_tx_depth_thr_0 : 6;     /*!< [5..0] Threshold of TX_FIFO_0. Set as the data consumption of
                                                     TX_FIFO_0 in one LRCK. This value is the FIFO layer, and
                                                     one layer is 32 bits.                                                     */
            uint32_t            : 2;
      __IOM uint32_t sp_rx_depth_thr_0 : 6;     /*!< [13..8] Threshold of RX_FIFO_0. Set as the data consumption
                                                     of RX_FIFO_0 in one LRCK. This value is the FIFO layer,
                                                     and one layer is 32 bits.                                                 */
            uint32_t            : 2;
      __IOM uint32_t sp_tx_depth_thr_1 : 6;     /*!< [21..16] Threshold of TX_FIFO_1. Set as the data consumption
                                                     of TX_FIFO_1 in one LRCK. This value is the FIFO layer,
                                                     and one layer is 32 bits.                                                 */
            uint32_t            : 2;
      __IOM uint32_t sp_rx_depth_thr_1 : 6;     /*!< [29..24] Threshold of RX_FIFO_1. Set as the data consumption
                                                     of RX_FIFO_1 in one LRCK. This value is the FIFO layer,
                                                     and one layer is 32 bits.                                                 */
            uint32_t            : 2;
    } sp_err_cnt_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_dma_con;                  /*!< (@ 0x00000060) SPORT DMA Control Register                                 */
    
    struct {
      __IOM uint32_t sp_dma_rstn : 1;           /*!< [0..0] Reset the DMA mechanism like state machine, the DMA pointer.0:
                                                     Make I2S execute the reset1: Make I2S stop the reset                      */
      __IOM uint32_t sp_tx_dma_en : 1;          /*!< [1..1] 0: Disable TX DMA, close Interrupt, and keep the DMA
                                                     pointer.1: Enable TX DMA.                                                 */
      __IOM uint32_t sp_rx_dma_en : 1;          /*!< [2..2] 0: Disable RX DMA, close Interrupt, and keep the DMA
                                                     pointer.1: Enable RX DMA.                                                 */
            uint32_t            : 1;
      __IOM uint32_t sp_dma_ctrl : 1;           /*!< [4..4] DMA Burst-length calculation methods0: Self-calculation
                                                     based on Page Size and Page Pointer settings1: Calculation
                                                     based on FIFO status (default)                                            */
            uint32_t            : 3;
      __IOM uint32_t sp_page_num : 2;           /*!< [9..8] Page number:00 : inactive01 : the page number is 210
                                                     : the page number is 311 : the page number is 4                           */
            uint32_t            : 2;
      __IOM uint32_t sp_burst_size : 2;         /*!< [13..12] Set DMA burst size. When SP_MCU_CTL_MODE is 0, SP_TX_FIFO_TH
                                                     and SP_RX_FIFO_TH also must be set to 15, 7, or 3 according
                                                     SP_BURST_SIZE.For example:When SP_BURST_SIZE is 0, SP_TX_FIFO_TH
                                                     and SP_RX_FIFO_TH are 15.00: Burst size is 16. Total burst
                                                     data is 64 bytes.01: Burst size is 8. Total burst data
                                                     is 32 bytes.10: Burst size is 4. Total burst data is 16
                                                     bytes.Others: Reserved                                                    */
            uint32_t            : 2;
      __IOM uint32_t sp_page_size : 12;         /*!< [27..16] Memory page size = PAGE_SIZE + 1 (word unit)                     */
            uint32_t            : 4;
    } sp_dma_con_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx0_dma_pp;               /*!< (@ 0x00000064) SPORT TX0 DMA Page Pointer Register                        */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t sp_tx0_page_ptr : 30;      /*!< [31..2] TX0 Page pointer. This is a physical address with word-align
                                                     limitation.                                                               */
    } sp_tx0_dma_pp_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx0_dma_int_en;           /*!< (@ 0x00000068) SPORT TX0 DMA Interrupt Enable Register                    */
    
    struct {
      __IOM uint32_t sp_tx0_p0okie : 1;         /*!< [0..0] TX0 Page 0 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_p1okie : 1;         /*!< [1..1] TX0 Page 1 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_p2okie : 1;         /*!< [2..2] TX0 Page 2 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_p3okie : 1;         /*!< [3..3] TX0 Page 3 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx0_page0unava_ie : 1;  /*!< [8..8] TX0 PAGE 0 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page1unava_ie : 1;  /*!< [9..9] TX0 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page2unava_ie : 1;  /*!< [10..10] TX0PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page3unava_ie : 1;  /*!< [11..11] TX0 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx0_page0errie : 1;     /*!< [16..16] TX0 PAGE 0 error Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page1errie : 1;     /*!< [17..17] TX0 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page2errie : 1;     /*!< [18..18] TX0 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx0_page3errie : 1;     /*!< [19..19] TX0 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx0_underflow_ie : 1;   /*!< [24..24] TX0 FIFO Underflow Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 7;
    } sp_tx0_dma_int_en_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx0_dma_int_sta;          /*!< (@ 0x0000006C) SPORT TX0 DMA Interrupt Status Register                    */
    
    struct {
      __OM  uint32_t sp_tx0_p0okip : 1;         /*!< [0..0] TX0 Page 0 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx0_p1okip : 1;         /*!< [1..1] TX0 Page 1 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx0_p2okip : 1;         /*!< [2..2] TX0 Page 2 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx0_p3okip : 1;         /*!< [3..3] TX0 Page 3 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
            uint32_t            : 4;
      __OM  uint32_t sp_tx0_page0unava_ip : 1;  /*!< [8..8] TX0 PAGE 0 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx0_page1unava_ip : 1;  /*!< [9..9] TX0 PAGE 1 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx0_page2unava_ip : 1;  /*!< [10..10] TX0 PAGE 2 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx0_page3unava_ip : 1;  /*!< [11..11] TX0 PAGE 3 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 4;
      __OM  uint32_t sp_tx0_page0errip : 1;     /*!< [16..16] TX0 PAGE 0 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx0_page1errip : 1;     /*!< [17..17] TX0 PAGE 1 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx0_page2errip : 1;     /*!< [18..18] TX0 PAGE 2 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx0_page3errip : 1;     /*!< [19..19] TX0 PAGE 3 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
            uint32_t            : 4;
      __OM  uint32_t sp_tx0_underflow_ip : 1;   /*!< [24..24] TX0 FIFO Underflow Interrupt Pending0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 7;
    } sp_tx0_dma_int_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx1_dma_pp;               /*!< (@ 0x00000070) SPORT TX1 DMA Page Pointer Register                        */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t sp_tx1_page_ptr : 30;      /*!< [31..2] TX1 Page pointer. This is a physical address with word-align
                                                     limitation.                                                               */
    } sp_tx1_dma_pp_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx1_dma_int_en;           /*!< (@ 0x00000074) SPORT TX1 DMA Interrupt Enable Register                    */
    
    struct {
      __IOM uint32_t sp_tx1_p0okie : 1;         /*!< [0..0] TX1 Page 0 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_p1okie : 1;         /*!< [1..1] TX1 Page 1 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_p2okie : 1;         /*!< [2..2] TX1 Page 2 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_p3okie : 1;         /*!< [3..3] TX1 Page 3 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx1_page0unava_ie : 1;  /*!< [8..8] TX1 PAGE 0 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page1unava_ie : 1;  /*!< [9..9] TX1 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page2unava_ie : 1;  /*!< [10..10] TX1 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page3unava_ie : 1;  /*!< [11..11] TX1 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx1_page0errie : 1;     /*!< [16..16] TX1 PAGE 0 error Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page1errie : 1;     /*!< [17..17] TX1 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page2errie : 1;     /*!< [18..18] TX1 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_tx1_page3errie : 1;     /*!< [19..19] TX1 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_tx1_underflow_ie : 1;   /*!< [24..24] TX1 FIFO Underflow Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 7;
    } sp_tx1_dma_int_en_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx1_dma_int_sta;          /*!< (@ 0x00000078) SPORT TX1 DMA Interrupt Status Register                    */
    
    struct {
      __OM  uint32_t sp_tx1_p0okip : 1;         /*!< [0..0] TX1 Page 0 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx1_p1okip : 1;         /*!< [1..1] TX1 Page 1 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx1_p2okip : 1;         /*!< [2..2] TX1 Page 2 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_tx1_p3okip : 1;         /*!< [3..3] TX1 Page 3 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
            uint32_t            : 4;
      __OM  uint32_t sp_tx1_page0unava_ip : 1;  /*!< [8..8] TX1 PAGE 0 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx1_page1unava_ip : 1;  /*!< [9..9] TX1 PAGE 1 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx1_page2unava_ip : 1;  /*!< [10..10] TX1 PAGE 2 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_tx1_page3unava_ip : 1;  /*!< [11..11] TX1 PAGE 3 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 4;
      __OM  uint32_t sp_tx1_page0errip : 1;     /*!< [16..16] TX1 PAGE 0 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx1_page1errip : 1;     /*!< [17..17] TX1 PAGE 1 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx1_page2errip : 1;     /*!< [18..18] TX1 PAGE 2 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_tx1_page3errip : 1;     /*!< [19..19] TX1 PAGE 3 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
            uint32_t            : 4;
      __OM  uint32_t sp_tx1_underflow_ip : 1;   /*!< [24..24] TX1 FIFO Underflow Interrupt Pending0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 7;
    } sp_tx1_dma_int_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx_page_own;              /*!< (@ 0x0000007C) SPORT TX Page Own Register                                 */
    
    struct {
      __IOM uint32_t sp_tx0_p0own : 1;          /*!< [0..0] TX0 Page 0 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx0_p1own : 1;          /*!< [1..1] TX0 Page 1 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx0_p2own : 1;          /*!< [2..2] TX0 Page 2 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx0_p3own : 1;          /*!< [3..3] TX0 Page 3 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx1_p0own : 1;          /*!< [4..4] TX1 Page 0 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx1_p1own : 1;          /*!< [5..5] TX1 Page 1 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx1_p2own : 1;          /*!< [6..6] TX1 Page 2 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_tx1_p3own : 1;          /*!< [7..7] TX1 Page 3 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
            uint32_t            : 24;
    } sp_tx_page_own_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx0_dma_pp;               /*!< (@ 0x00000080) SPORT RX0 DMA Page Pointer Register                        */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t sp_rx0_page_ptr : 30;      /*!< [31..2] RX0 Page pointer. This is a physical address with word-align
                                                     limitation.                                                               */
    } sp_rx0_dma_pp_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx0_dma_int_en;           /*!< (@ 0x00000084) SPORT RX0 DMA Interrupt Enable Register                    */
    
    struct {
      __IOM uint32_t sp_rx0_p0okie : 1;         /*!< [0..0] RX0 Page 0 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_p1okie : 1;         /*!< [1..1] RX0 Page 1 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_p2okie : 1;         /*!< [2..2] RX0 Page 2 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_p3okie : 1;         /*!< [3..3] RX0 Page 3 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx0_page0unava_ie : 1;  /*!< [8..8] RX0 PAGE 0 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page1unava_ie : 1;  /*!< [9..9] RX0 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page2unava_ie : 1;  /*!< [10..10] RX0PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page3unava_ie : 1;  /*!< [11..11] RX0 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx0_page0errie : 1;     /*!< [16..16] RX0 PAGE 0 error Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page1errie : 1;     /*!< [17..17] RX0 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page2errie : 1;     /*!< [18..18] RX0 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx0_page3errie : 1;     /*!< [19..19] RX0 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx0_overflow_ie : 1;    /*!< [24..24] RX0 FIFO overflow Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 7;
    } sp_rx0_dma_int_en_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx0_dma_int_sta;          /*!< (@ 0x00000088) SPORT RX0 DMA Interrupt Status Register                    */
    
    struct {
      __OM  uint32_t sp_rx0_p0okip : 1;         /*!< [0..0] RX0 Page 0 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx0_p1okip : 1;         /*!< [1..1] RX0 Page 1 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx0_p2okip : 1;         /*!< [2..2] RX0 Page 2 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx0_p3okip : 1;         /*!< [3..3] RX0 Page 3 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
            uint32_t            : 4;
      __OM  uint32_t sp_rx0_page0unava_ip : 1;  /*!< [8..8] RX0 PAGE 0 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx0_page1unava_ip : 1;  /*!< [9..9] RX0 PAGE 1 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx0_page2unava_ip : 1;  /*!< [10..10] RX0 PAGE 2 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx0_page3unava_ip : 1;  /*!< [11..11] RX0 PAGE 3 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 4;
      __OM  uint32_t sp_rx0_page0errip : 1;     /*!< [16..16] RX0 PAGE 0 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx0_page1errip : 1;     /*!< [17..17] RX0 PAGE 1 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx0_page2errip : 1;     /*!< [18..18] RX0 PAGE 2 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx0_page3errip : 1;     /*!< [19..19] RX0 PAGE 3 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
            uint32_t            : 4;
      __OM  uint32_t sp_rx0_overflow_ip : 1;    /*!< [24..24] RX0 FIFO overflow Interrupt Pending0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 7;
    } sp_rx0_dma_int_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx1_dma_pp;               /*!< (@ 0x0000008C) SPORT RX1 DMA Page Pointer Register                        */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t sp_rx1_page_ptr : 30;      /*!< [31..2] RX1 Page pointer. This is a physical address with word-align
                                                     limitation.                                                               */
    } sp_rx1_dma_pp_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx1_dma_int_en;           /*!< (@ 0x00000090) SPORT RX1 DMA Interrupt Enable Register                    */
    
    struct {
      __IOM uint32_t sp_rx1_p0okie : 1;         /*!< [0..0] RX1 Page 0 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_p1okie : 1;         /*!< [1..1] RX1 Page 1 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_p2okie : 1;         /*!< [2..2] RX1 Page 2 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_p3okie : 1;         /*!< [3..3] RX1 Page 3 OK Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx1_page0unava_ie : 1;  /*!< [8..8] RX1 PAGE 0 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page1unava_ie : 1;  /*!< [9..9] RX1 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page2unava_ie : 1;  /*!< [10..10] RX1 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page3unava_ie : 1;  /*!< [11..11] RX1 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx1_page0errie : 1;     /*!< [16..16] RX1 PAGE 0 error Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page1errie : 1;     /*!< [17..17] RX1 PAGE 1 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page2errie : 1;     /*!< [18..18] RX1 PAGE 2 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
      __IOM uint32_t sp_rx1_page3errie : 1;     /*!< [19..19] RX1 PAGE 3 unavailable Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 4;
      __IOM uint32_t sp_rx1_underflow_ie : 1;   /*!< [24..24] RX1 FIFO overflow Interrupt Enable0: Disable Interrupt1:
                                                     Enable Interrupt                                                          */
            uint32_t            : 7;
    } sp_rx1_dma_int_en_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx1_dma_int_sta;          /*!< (@ 0x00000094) SPORT RX1 DMA Interrupt Status Register                    */
    
    struct {
      __OM  uint32_t sp_rx1_p0okip : 1;         /*!< [0..0] RX1 Page 0 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx1_p1okip : 1;         /*!< [1..1] RX1 Page 1 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx1_p2okip : 1;         /*!< [2..2] RX1 Page 2 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
      __OM  uint32_t sp_rx1_p3okip : 1;         /*!< [3..3] RX1 Page 3 OK Interrupt Pending0: No Interrupt1: Interrupt
                                                     pending, write 1 to clear                                                 */
            uint32_t            : 4;
      __OM  uint32_t sp_rx1_page0unava_ip : 1;  /*!< [8..8] RX1 PAGE 0 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx1_page1unava_ip : 1;  /*!< [9..9] RX1 PAGE 1 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx1_page2unava_ip : 1;  /*!< [10..10] RX1 PAGE 2 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
      __OM  uint32_t sp_rx1_page3unava_ip : 1;  /*!< [11..11] RX1 PAGE 3 unavailable Interrupt Pending. The controller
                                                     wants to execute the page but this page own bit does not
                                                     be set. This situation will make the interrupt.0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 4;
      __OM  uint32_t sp_rx1_page0errip : 1;     /*!< [16..16] RX1 PAGE 0 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx1_page1errip : 1;     /*!< [17..17] RX1 PAGE 1 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx1_page2errip : 1;     /*!< [18..18] RX1 PAGE 2 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
      __OM  uint32_t sp_rx1_page3errip : 1;     /*!< [19..19] RX1 PAGE 3 Error Interrupt Pending. Fabric bus responses
                                                     DEC/SLV error.0: No error interrupt1: Interrupt pending                   */
            uint32_t            : 4;
      __OM  uint32_t sp_rx1_overflow_ip : 1;    /*!< [24..24] RX1 FIFO overflow Interrupt Pending0: No Interrupt1:
                                                     Interrupt pending, write 1 to clear                                       */
            uint32_t            : 7;
    } sp_rx1_dma_int_sta_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx_page_own;              /*!< (@ 0x00000098) SPORT RX Page Own Register                                 */
    
    struct {
      __IOM uint32_t sp_rx0_p0own : 1;          /*!< [0..0] RX0 Page 0 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx0_p1own : 1;          /*!< [1..1] RX0 Page 1 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx0_p2own : 1;          /*!< [2..2] RX0 Page 2 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx0_p3own : 1;          /*!< [3..3] RX0 Page 3 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx1_p0own : 1;          /*!< [4..4] RX1 Page 0 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx1_p1own : 1;          /*!< [5..5] RX1 Page 1 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx1_p2own : 1;          /*!< [6..6] RX1 Page 2 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
      __IOM uint32_t sp_rx1_p3own : 1;          /*!< [7..7] RX1 Page 3 Own bit0: Page 0 owned by CPU1: Page 0 owned
                                                     by controllerDMA sets this bit to 0 when TX channel 0 Page
                                                     0 is done                                                                 */
            uint32_t            : 24;
    } sp_rx_page_own_b;
  } ;
  
  union {
    __IOM uint32_t sp_tx_axiaddr_err;           /*!< (@ 0x0000009C) SPORT TX AXI address access Error address record
                                                                    Register                                                   */
    
    struct {
      __IOM uint32_t sp_tx_axiaddr : 32;        /*!< [31..0] TX AXI Error Address cause Error interruptlimitation.             */
    } sp_tx_axiaddr_err_b;
  } ;
  __IM  uint32_t  RESERVED[24];
  
  union {
    __IM  uint32_t sp_tx_misc_err;              /*!< (@ 0x00000100) SPORT TX AXI MISC. access Error record Register            */
    
    struct {
      __IM  uint32_t sp_tx_page_size : 12;      /*!< [11..0] Page Size setting                                                 */
      __IM  uint32_t sp_tx_page_num : 2;        /*!< [13..12] Number of page setting                                           */
            uint32_t            : 2;
      __IM  uint32_t sp_tx_burst_len : 4;       /*!< [19..16] TX AXI Burst Length Error transaction causes Error
                                                     interrupt                                                                 */
            uint32_t            : 3;
      __IM  uint32_t sp_tx_dma_ctrl : 1;        /*!< [23..23] DMA Burst length calculation0: Self-calculation1: Burst
                                                     length info from setting (refer to BURST_LEN_SETTING field)               */
      __IM  uint32_t sp_tx_burst_len_setting : 2;/*!< [25..24] Burst length setting in DMA_CTRL = 1                            */
            uint32_t            : 1;
      __IM  uint32_t sp_tx_channel_winner : 1;  /*!< [27..27] Channel that is served by DMA0: Channel 01: Channel
                                                     1                                                                         */
            uint32_t            : 1;
      __IM  uint32_t sp_tx_current_page : 2;    /*!< [30..29] Current page has Error00: page 001: page 110: page
                                                     211: page 3                                                               */
            uint32_t            : 1;
    } sp_tx_misc_err_b;
  } ;
  
  union {
    __IOM uint32_t sp_rx_axiaddr_err;           /*!< (@ 0x00000104) SPORT RX AXI address access Error address record
                                                                    Register                                                   */
    
    struct {
      __IOM uint32_t sp_rx_axiaddr : 32;        /*!< [31..0] RX AXI Error Address cause Error interruptlimitation.             */
    } sp_rx_axiaddr_err_b;
  } ;
  
  union {
    __IM  uint32_t sp_rx_misc_err;              /*!< (@ 0x00000108) SPORT RX AXI MISC. access Error record Register            */
    
    struct {
      __IM  uint32_t sp_rx_page_size : 12;      /*!< [11..0] Page Size setting                                                 */
      __IM  uint32_t sp_rx_page_num : 2;        /*!< [13..12] Number of page setting                                           */
            uint32_t            : 2;
      __IM  uint32_t sp_rx_burst_len : 4;       /*!< [19..16] TX AXI Burst Length Error transaction causes Error
                                                     interrupt                                                                 */
            uint32_t            : 3;
      __IM  uint32_t sp_rx_dma_ctrl : 1;        /*!< [23..23] DMA Burst length calculation0: Self-calculation1: Burst
                                                     length info from setting (refer to BURST_LEN_SETTING field)               */
      __IM  uint32_t sp_rx_burst_len_setting : 2;/*!< [25..24] Burst length setting in DMA_CTRL = 1                            */
            uint32_t            : 1;
      __IM  uint32_t sp_rx_channel_winner : 1;  /*!< [27..27] Channel that is served by DMA0: Channel 01: Channel
                                                     1                                                                         */
            uint32_t            : 1;
      __IM  uint32_t sp_rx_current_page : 2;    /*!< [30..29] Current page has Error00: page 001: page 110: page
                                                     211: page 3                                                               */
            uint32_t            : 1;
    } sp_rx_misc_err_b;
  } ;
} SPORT_Type;                                   /*!< Size = 268 (0x10c)                                                        */



/* =========================================================================================================================== */
/* ================                                           SGPIO                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Serial General Purpose Input / Output (SGPIO)
  */

typedef struct {                                /*!< (@ 0x40046000) SGPIO Structure                                            */
  
  union {
    __IOM uint32_t rxtmr_ctrl;                  /*!< (@ 0x00000000) RX Timer Control Register                                  */
    
    struct {
      __IOM uint32_t rxtmr_cen  : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t rxtmr_crst : 1;            /*!< [1..1] RSVD                                                               */
            uint32_t            : 6;
      __IOM uint32_t rxtmredge_sel : 2;         /*!< [9..8] RSVD                                                               */
            uint32_t            : 22;
    } rxtmr_ctrl_b;
  } ;
  
  union {
    __IOM uint32_t rxprval;                     /*!< (@ 0x00000004) RX Maximum Prescale Register                               */
    
    struct {
      __IOM uint32_t rxprval    : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxprval_b;
  } ;
  
  union {
    __IOM uint32_t rxprtc;                      /*!< (@ 0x00000008) RX Timer Prescale Register                                 */
    
    struct {
      __IOM uint32_t rxprtc     : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxprtc_b;
  } ;
  
  union {
    __IOM uint32_t rxtc;                        /*!< (@ 0x0000000C) RX Timer Counter Register                                  */
    
    struct {
      __IOM uint32_t rxtc       : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxtc_b;
  } ;
  
  union {
    __IOM uint32_t rxmc;                        /*!< (@ 0x00000010) Position Counter Register                                  */
    
    struct {
      __IOM uint32_t rx_mr0i_en : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t rx_mr0rst_en : 1;          /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rx_mr0stop_en : 1;         /*!< [2..2] RSVD                                                               */
      __IOM uint32_t rx_mr0sclk_en : 1;         /*!< [3..3] RSVD                                                               */
      __IOM uint32_t rx_mr1i_en : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t rx_mr1rst_en : 1;          /*!< [5..5] RSVD                                                               */
      __IOM uint32_t rx_mr1stop_en : 1;         /*!< [6..6] RSVD                                                               */
      __IOM uint32_t rx_mr1sclk_en : 1;         /*!< [7..7] RSVD                                                               */
      __IOM uint32_t rx_mr2i_en : 1;            /*!< [8..8] RSVD                                                               */
      __IOM uint32_t rx_mr2rst_en : 1;          /*!< [9..9] RSVD                                                               */
      __IOM uint32_t rx_mr2stop_en : 1;         /*!< [10..10] RSVD                                                             */
      __IOM uint32_t rx_mr2sclk_en : 1;         /*!< [11..11] RSVD                                                             */
      __IOM uint32_t rx_mr0mulrst_en : 1;       /*!< [12..12] RSVD                                                             */
      __IOM uint32_t rx_mr0mulstop_en : 1;      /*!< [13..13] RSVD                                                             */
      __IOM uint32_t rx_posrst_en : 1;          /*!< [14..14] RSVD                                                             */
      __IOM uint32_t rx_posstop_en : 1;         /*!< [15..15] RSVD                                                             */
            uint32_t            : 16;
    } rxmc_b;
  } ;
  
  union {
    __IOM uint32_t rxmr0;                       /*!< (@ 0x00000014) RX Match Register 0                                        */
    
    struct {
      __IOM uint32_t rxmr0      : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxmr0_b;
  } ;
  
  union {
    __IOM uint32_t rxmr1;                       /*!< (@ 0x00000018) RX Match Register 1                                        */
    
    struct {
      __IOM uint32_t rxmr1      : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxmr1_b;
  } ;
  
  union {
    __IOM uint32_t rxmr2;                       /*!< (@ 0x0000001C) RX Match Register 2                                        */
    
    struct {
      __IOM uint32_t rxmr2      : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } rxmr2_b;
  } ;
  
  union {
    __IOM uint32_t cap_ctrl;                    /*!< (@ 0x00000020) Capture Control Register                                   */
    
    struct {
      __IOM uint32_t cap_en     : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t capi_en    : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t capsrc_sel : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t capfe_en   : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t capre_en   : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t cap_rxtcrst_en : 1;        /*!< [5..5] RSVD                                                               */
      __IOM uint32_t cap_rxtcstop_en : 1;       /*!< [6..6] RSVD                                                               */
      __IOM uint32_t cap_cmpval_sel : 1;        /*!< [7..7] RSVD                                                               */
      __IOM uint32_t capvalid_en : 1;           /*!< [8..8] RSVD                                                               */
            uint32_t            : 7;
      __IOM uint32_t cap_cmpval : 16;           /*!< [31..16] RSVD                                                             */
    } cap_ctrl_b;
  } ;
  
  union {
    __IOM uint32_t capr;                        /*!< (@ 0x00000024) Capture Register                                           */
    
    struct {
      __IM  uint32_t capr       : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } capr_b;
  } ;
  
  union {
    __IOM uint32_t multmr_ctrl;                 /*!< (@ 0x00000028) Multiple Timer Control Register                            */
    
    struct {
      __IOM uint32_t multmr_cen : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t multmr_crst : 1;           /*!< [1..1] RSVD                                                               */
            uint32_t            : 6;
      __IOM uint32_t mulmode_en : 2;            /*!< [9..8] RSVD                                                               */
            uint32_t            : 22;
    } multmr_ctrl_b;
  } ;
  
  union {
    __IOM uint32_t mulprval;                    /*!< (@ 0x0000002C) Multiple Maximum Prescale Register                         */
    
    struct {
      __IOM uint32_t mulprval   : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } mulprval_b;
  } ;
  
  union {
    __IOM uint32_t mulprtc;                     /*!< (@ 0x00000030) Multiple Timer Prescale Register                           */
    
    struct {
      __IOM uint32_t mulprtc    : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } mulprtc_b;
  } ;
  
  union {
    __IOM uint32_t multc;                       /*!< (@ 0x00000034) Multiple Timer Counter Register                            */
    
    struct {
      __IOM uint32_t multc      : 16;           /*!< [15..0] RSVD                                                              */
            uint32_t            : 16;
    } multc_b;
  } ;
  
  union {
    __IOM uint32_t mulmc;                       /*!< (@ 0x00000038) Multiple Match Control Register                            */
    
    struct {
      __IOM uint32_t mul_mr0i_en : 1;           /*!< [0..0] RSVD                                                               */
      __IOM uint32_t mul_mr0rst_en : 1;         /*!< [1..1] RSVD                                                               */
      __IOM uint32_t mul_mr0stop_en : 1;        /*!< [2..2] RSVD                                                               */
      __IOM uint32_t mul_mr0sclk_en : 1;        /*!< [3..3] RSVD                                                               */
      __IOM uint32_t mul_mr0rxrst_en : 1;       /*!< [4..4] RSVD                                                               */
      __IOM uint32_t mul_mr0rxstop_en : 1;      /*!< [5..5] RSVD                                                               */
      __IOM uint32_t mul_mr0capsrc_en : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t mul_mr0mcnt_en : 1;        /*!< [7..7] RSVD                                                               */
      __IOM uint32_t mul_mcnti_en : 1;          /*!< [8..8] RSVD                                                               */
      __IOM uint32_t mul_mcntrst_en : 1;        /*!< [9..9] RSVD                                                               */
      __IOM uint32_t mul_mcntstop_en : 1;       /*!< [10..10] RSVD                                                             */
      __IOM uint32_t mul_fmode_en : 1;          /*!< [11..11] RSVD                                                             */
      __IOM uint32_t mul_dma_en : 1;            /*!< [12..12] RSVD                                                             */
      __IOM uint32_t mul_dma_start : 1;         /*!< [13..13] RSVD                                                             */
      __IOM uint32_t mul_dma_unfli_en : 1;      /*!< [14..14] RSVD                                                             */
            uint32_t            : 17;
    } mulmc_b;
  } ;
  
  union {
    __IOM uint32_t mulmr01gp0;                  /*!< (@ 0x0000003C) Multiple Match Register 0 & 1 For Group 0                  */
    
    struct {
      __IOM uint32_t mulmr0_gp0 : 16;           /*!< [15..0] RSVD                                                              */
      __IOM uint32_t mulmr1_gp0 : 16;           /*!< [31..16] RSVD                                                             */
    } mulmr01gp0_b;
  } ;
  
  union {
    __IOM uint32_t mulmr23gp0;                  /*!< (@ 0x00000040) Multiple Match Register 2 & 3 For Group 0                  */
    
    struct {
      __IOM uint32_t mulmr2_gp0 : 16;           /*!< [15..0] RSVD                                                              */
      __IOM uint32_t mulmr3_gp0 : 16;           /*!< [31..16] RSVD                                                             */
    } mulmr23gp0_b;
  } ;
  
  union {
    __IOM uint32_t mulmr01gp1;                  /*!< (@ 0x00000044) Multiple Match Register 0 & 1 For Group 1                  */
    
    struct {
      __IOM uint32_t mulmr0_gp1 : 16;           /*!< [15..0] RSVD                                                              */
      __IOM uint32_t mulmr1_gp1 : 16;           /*!< [31..16] RSVD                                                             */
    } mulmr01gp1_b;
  } ;
  
  union {
    __IOM uint32_t mulmr23gp1;                  /*!< (@ 0x00000048) Multiple Match Register 2 & 3 For Group 1                  */
    
    struct {
      __IOM uint32_t mulmr2_gp1 : 16;           /*!< [15..0] RSVD                                                              */
      __IOM uint32_t mulmr3_gp1 : 16;           /*!< [31..16] RSVD                                                             */
    } mulmr23gp1_b;
  } ;
  
  union {
    __IOM uint32_t mul_mcnt;                    /*!< (@ 0x0000004C) Multiple Match Counter Register                            */
    
    struct {
      __IOM uint32_t mul_mcnt   : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } mul_mcnt_b;
  } ;
  
  union {
    __IOM uint32_t mulemr;                      /*!< (@ 0x00000050) External Match Control Register                            */
    
    struct {
      __IOM uint32_t mulemc1    : 2;            /*!< [1..0] RSVD                                                               */
      __IOM uint32_t mulemc2    : 2;            /*!< [3..2] RSVD                                                               */
      __IOM uint32_t mulemc3    : 2;            /*!< [5..4] RSVD                                                               */
      __IOM uint32_t rxemc0     : 2;            /*!< [7..6] RSVD                                                               */
      __IOM uint32_t rxemc1     : 2;            /*!< [9..8] RSVD                                                               */
      __IOM uint32_t rxemc2     : 2;            /*!< [11..10] RSVD                                                             */
      __IOM uint32_t biout_en   : 1;            /*!< [12..12] RSVD                                                             */
      __IOM uint32_t biout_mode : 2;            /*!< [14..13] RSVD                                                             */
      __IOM uint32_t mulbimc1   : 2;            /*!< [16..15] RSVD                                                             */
      __IOM uint32_t mulbimc2   : 2;            /*!< [18..17] RSVD                                                             */
      __IOM uint32_t mulbimc3   : 2;            /*!< [20..19] RSVD                                                             */
      __IOM uint32_t rxbimc0    : 2;            /*!< [22..21] RSVD                                                             */
      __IOM uint32_t rxbimc1    : 2;            /*!< [24..23] RSVD                                                             */
      __IOM uint32_t rxbimc2    : 2;            /*!< [26..25] RSVD                                                             */
            uint32_t            : 5;
    } mulemr_b;
  } ;
  
  union {
    __IOM uint32_t data_ctrl;                   /*!< (@ 0x00000054) Data Control Register                                      */
    
    struct {
      __IOM uint32_t rxsft_ie   : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t mulsft_ie  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rxload_ie  : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t mulload_ie : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t rxdatasrc_sel : 1;         /*!< [4..4] RSVD                                                               */
      __IOM uint32_t pattern_match_mode : 1;    /*!< [5..5] RSVD                                                               */
      __IOM uint32_t pattern_match_ie : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t rxdata_dir : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t txdata_dir : 1;            /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } data_ctrl_b;
  } ;
  
  union {
    __IOM uint32_t rxdata;                      /*!< (@ 0x00000058) RX Data Register                                           */
    
    struct {
      __IOM uint32_t rxdata     : 32;           /*!< [31..0] RSVD                                                              */
    } rxdata_b;
  } ;
  
  union {
    __IOM uint32_t rxdata_dp;                   /*!< (@ 0x0000005C) RX Data Duplicate Register                                 */
    
    struct {
      __IOM uint32_t rxdata_dp  : 32;           /*!< [31..0] RSVD                                                              */
    } rxdata_dp_b;
  } ;
  
  union {
    __IOM uint32_t rxposr;                      /*!< (@ 0x00000060) RX Position Register                                       */
    
    struct {
      __IOM uint32_t rxpostc    : 5;            /*!< [4..0] RSVD                                                               */
            uint32_t            : 3;
      __IOM uint32_t rxposrst   : 5;            /*!< [12..8] RSVD                                                              */
            uint32_t            : 19;
    } rxposr_b;
  } ;
  
  union {
    __IOM uint32_t rxdatamask;                  /*!< (@ 0x00000064) RX Data Mask Register                                      */
    
    struct {
      __IOM uint32_t rxdatamask : 32;           /*!< [31..0] RSVD                                                              */
    } rxdatamask_b;
  } ;
  
  union {
    __IOM uint32_t muldata;                     /*!< (@ 0x00000068) Multiple Data Register                                     */
    
    struct {
      __IOM uint32_t muldata    : 32;           /*!< [31..0] RSVD                                                              */
    } muldata_b;
  } ;
  
  union {
    __IOM uint32_t muldata_dp;                  /*!< (@ 0x0000006C) Multiple Data Duplicate Register                           */
    
    struct {
      __IOM uint32_t muldata_dp : 32;           /*!< [31..0] RSVD                                                              */
    } muldata_dp_b;
  } ;
  
  union {
    __IOM uint32_t mulposr;                     /*!< (@ 0x00000070) Multiple Position Register                                 */
    
    struct {
      __IOM uint32_t mulpostc   : 5;            /*!< [4..0] RSVD                                                               */
            uint32_t            : 3;
      __IOM uint32_t mulposrst  : 5;            /*!< [12..8] RSVD                                                              */
            uint32_t            : 19;
    } mulposr_b;
  } ;
  
  union {
    __OM  uint32_t mulfdata;                    /*!< (@ 0x00000074) Multiple FIFO Data Register                                */
    
    struct {
      __OM  uint32_t mulfdata   : 32;           /*!< [31..0] RSVD                                                              */
    } mulfdata_b;
  } ;
  
  union {
    __IOM uint32_t is;                          /*!< (@ 0x00000078) SGPIO Interrupt Status Register                            */
    
    struct {
      __IOM uint32_t rx_mr0i_is : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t rx_mr1i_is : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rx_mr2i_is : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t mul_mr0i_is : 1;           /*!< [3..3] RSVD                                                               */
      __IOM uint32_t capi_is    : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t rxsft_is   : 1;            /*!< [5..5] RSVD                                                               */
      __IOM uint32_t mulsft_is  : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t rxload_is  : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t mulload_is : 1;            /*!< [8..8] RSVD                                                               */
      __IOM uint32_t pattern_match_is : 1;      /*!< [9..9] RSVD                                                               */
      __IOM uint32_t mulmcnt_is : 1;            /*!< [10..10] RSVD                                                             */
      __IOM uint32_t mul_dma_unfl_is : 1;       /*!< [11..11] RSVD                                                             */
            uint32_t            : 20;
    } is_b;
  } ;
  
  union {
    __IOM uint32_t gf;                          /*!< (@ 0x0000007C) SGPIO Glitch Filter Register                               */
    
    struct {
      __IOM uint32_t gf         : 8;            /*!< [7..0] RSVD                                                               */
            uint32_t            : 24;
    } gf_b;
  } ;
  
  union {
    __IOM uint32_t output;                      /*!< (@ 0x00000080) SGPIO Output Register                                      */
    
    struct {
      __IOM uint32_t output     : 1;            /*!< [0..0] RSVD                                                               */
            uint32_t            : 31;
    } output_b;
  } ;
  
  union {
    __IOM uint32_t im;                          /*!< (@ 0x00000084) SGPIO Interrupt Mask Register                              */
    
    struct {
      __IOM uint32_t rx_mr0i_im : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t rx_mr1i_im : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t rx_mr2i_im : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t mul_mr0i_im : 1;           /*!< [3..3] RSVD                                                               */
      __IOM uint32_t capi_im    : 1;            /*!< [4..4] RSVD                                                               */
      __IOM uint32_t rxsft_im   : 1;            /*!< [5..5] RSVD                                                               */
      __IOM uint32_t mulsft_im  : 1;            /*!< [6..6] RSVD                                                               */
      __IOM uint32_t rxload_im  : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t mulload_im : 1;            /*!< [8..8] RSVD                                                               */
      __IOM uint32_t pattern_match_im : 1;      /*!< [9..9] RSVD                                                               */
      __IOM uint32_t mulmcnt_im : 1;            /*!< [10..10] RSVD                                                             */
      __IOM uint32_t mul_dma_unfl_im : 1;       /*!< [11..11] RSVD                                                             */
            uint32_t            : 20;
    } im_b;
  } ;
} SGPIO_Type;                                   /*!< Size = 136 (0x88)                                                         */



/* =========================================================================================================================== */
/* ================                                         ETHERNET                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief ETHERNET - for Ethernet connectivity (ETHERNET)
  */

typedef struct {                                /*!< (@ 0x40054000) ETHERNET Structure                                         */
  
  union {
    __IOM uint32_t idr0;                        /*!< (@ 0x00000000) MAC ID Register 1                                          */
    
    struct {
      __IOM uint32_t idr3       : 8;            /*!< [7..0] 4th byte of MAC ID                                                 */
      __IOM uint32_t idr2       : 8;            /*!< [15..8] 3rd byte of MAC ID                                                */
      __IOM uint32_t idr1       : 8;            /*!< [23..16] 2nd byte of MAC ID                                               */
      __IOM uint32_t idr0       : 8;            /*!< [31..24] 1st byte of MAC ID                                               */
    } idr0_b;
  } ;
  
  union {
    __IOM uint32_t idr4;                        /*!< (@ 0x00000004) MAC ID Register 2                                          */
    
    struct {
            uint32_t            : 16;
      __IOM uint32_t idr5       : 8;            /*!< [23..16] 6th byte of MAC ID                                               */
      __IOM uint32_t idr4       : 8;            /*!< [31..24] 5th byte of MAC ID                                               */
    } idr4_b;
  } ;
  
  union {
    __IOM uint32_t mar0;                        /*!< (@ 0x00000008) Multicast Add Register 1                                   */
    
    struct {
      __IOM uint32_t mar3       : 8;            /*!< [7..0] 4st byte of multicast address register                             */
      __IOM uint32_t mar2       : 8;            /*!< [15..8] 3st byte of multicast address register                            */
      __IOM uint32_t mar1       : 8;            /*!< [23..16] 2st byte of multicast address register                           */
      __IOM uint32_t mar0       : 8;            /*!< [31..24] 1st byte of multicast address register                           */
    } mar0_b;
  } ;
  
  union {
    __IOM uint32_t mar4;                        /*!< (@ 0x0000000C) Multicast Add Register 2                                   */
    
    struct {
      __IOM uint32_t mar7       : 8;            /*!< [7..0] 8st byte of multicast address register                             */
      __IOM uint32_t mar6       : 8;            /*!< [15..8] 7st byte of multicast address register                            */
      __IOM uint32_t mar5       : 8;            /*!< [23..16] 6st byte of multicast address register                           */
      __IOM uint32_t mar4       : 8;            /*!< [31..24] 5st byte of multicast address register                           */
    } mar4_b;
  } ;
  
  union {
    __IOM uint32_t txok_rxok;                   /*!< (@ 0x00000010) TxRx Ok Counter Register                                   */
    
    struct {
      __IOM uint32_t rxok       : 16;           /*!< [15..0] 16-bit counter of Rx Ok packets. Rolls over automatically.
                                                     Write to clear.                                                           */
      __IOM uint32_t txok       : 16;           /*!< [31..16] 16-bit counter of Tx Ok packets. Rolls over automatically.
                                                     Write to clear.                                                           */
    } txok_rxok_b;
  } ;
  
  union {
    __IOM uint32_t txerr_rxerr;                 /*!< (@ 0x00000014) TxRx Error Counter Register                                */
    
    struct {
      __IOM uint32_t rxerr      : 16;           /*!< [15..0] 16-bit counter of Rx error packets. Rolls over automatically.
                                                     Write to clear.                                                           */
      __IOM uint32_t txerr      : 16;           /*!< [31..16] 16-bit counter of Tx error packets. Rolls over automatically.
                                                     Write to clear.                                                           */
    } txerr_rxerr_b;
  } ;
  __IM  uint32_t  RESERVED[8];
  
  union {
    __IOM uint32_t com;                         /*!< (@ 0x00000038) Command Register                                           */
    
    struct {
      __IOM uint32_t rst        : 1;            /*!< [0..0] Reset: Setting to 1 forces the Ethernet module to a software
                                                     reset state which disables the transmitter and receiver,
                                                     reinitializes the FIFOs, triggers interrupt Swint for RISC
                                                     to reset the system buffer pointer to the initial value
                                                     Tx/Rx FDP. This bit is 1 during the reset operation, and
                                                     is cleared to 0 by the Ethernet Module when the reset operation
                                                     is complete.                                                              */
      __IOM uint32_t rxchksum   : 1;            /*!< [1..1] Receive checksum offload enable. 1: Enable. 0: Disable.            */
      __IOM uint32_t rxvlan     : 1;            /*!< [2..2] Receive VLAN de-tagging enable. 1: Enable. 0: Disable.             */
      __IOM uint32_t rxjumbo    : 1;            /*!< [3..3] 1: support jumbo packet receiving. The maximum packet
                                                     size is 16384 Bytes (0x4000).0: Does not support jumbo
                                                     packet receiving.                                                         */
            uint32_t            : 28;
    } com_b;
  } ;
  
  union {
    __IOM uint32_t isr_imr;                     /*!< (@ 0x0000003C) Interrupt Status & Interrupt Mask Register                 */
    
    struct {
      __IOM uint32_t isr_rok    : 1;            /*!< [0..0] Interrupt status of Rx ok. Write 1 to clear                        */
      __IOM uint32_t isr_cnt_wrap : 1;          /*!< [1..1] Interrupt status of Tx/Rx counter wrap interrupt. Write
                                                     1 to clear                                                                */
      __IOM uint32_t isr_rer_runt : 1;          /*!< [2..2] Interrupt status of Rx error caused by runt error characterized
                                                     by the frame length in bytes being less than 64 bytes.
                                                     Write 1 to clear                                                          */
            uint32_t            : 1;
      __IOM uint32_t isr_rer_ovf : 1;           /*!< [4..4] Interrupt status of Rx FIFO overflow. Write 1 to clear             */
      __IOM uint32_t isr_rdu    : 1;            /*!< [5..5] Interrupt status of Rx descriptor ring1 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_tok    : 1;            /*!< [6..6] Interrupt status of Tx ok. Write 1 to clear                        */
      __IOM uint32_t isr_ter    : 1;            /*!< [7..7] Interrupt status of Tx error. Write 1 to clear                     */
      __IOM uint32_t isr_linkchg : 1;           /*!< [8..8] Interrupt status of link change. Write 1 to clear                  */
      __IOM uint32_t isr_tdu    : 1;            /*!< [9..9] Interrupt status of Tx descriptor ring1 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_swint  : 1;            /*!< [10..10] Interrupt status of software interrupt pending. Write
                                                     1 to clear                                                                */
      __IOM uint32_t isr_rdu2   : 1;            /*!< [11..11] Interrupt status of Rx descriptor ring2 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_rdu3   : 1;            /*!< [12..12] Interrupt status of Rx descriptor ring3 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_rdu4   : 1;            /*!< [13..13] Interrupt status of Rx descriptor ring4 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_rdu5   : 1;            /*!< [14..14] Interrupt status of Rx descriptor ring5 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t isr_rdu6   : 1;            /*!< [15..15] Interrupt status of Rx descriptor ring6 is unavailable.
                                                     Write 1 to clear                                                          */
      __IOM uint32_t imr_rok    : 1;            /*!< [16..16] Interrupt mask of Rx ok                                          */
      __IOM uint32_t imr_cnt_wrap : 1;          /*!< [17..17] Interrupt mask of Tx/Rx counter wrap interrupt                   */
      __IOM uint32_t imr_rer_runt : 1;          /*!< [18..18] Interrupt mask of Rx error caused by runt error characterized
                                                     by the frame length in bytes being less than 64 bytes                     */
            uint32_t            : 1;
      __IOM uint32_t imr_rer_ovf : 1;           /*!< [20..20] Interrupt mask of Rx FIFO overflow                               */
      __IOM uint32_t imr_rdu    : 1;            /*!< [21..21] Interrupt mask of Rx descriptor ring1 is unavailable             */
      __IOM uint32_t imr_tok    : 1;            /*!< [22..22] Interrupt mask of Tx ok                                          */
      __IOM uint32_t imr_ter    : 1;            /*!< [23..23] Interrupt mask of Tx error                                       */
      __IOM uint32_t imr_linkchg : 1;           /*!< [24..24] Interrupt mask of link change                                    */
      __IOM uint32_t imr_tdu    : 1;            /*!< [25..25] Interrupt mask of Tx descriptor ring1 is unavailable             */
      __IOM uint32_t imr_swint  : 1;            /*!< [26..26] Interrupt mask of software interrupt pending                     */
      __IOM uint32_t imr_rdu2   : 1;            /*!< [27..27] Interrupt mask of Rx descriptor ring2 is unavailable             */
      __IOM uint32_t imr_rdu3   : 1;            /*!< [28..28] Interrupt mask of Rx descriptor ring3 is unavailable             */
      __IOM uint32_t imr_rdu4   : 1;            /*!< [29..29] Interrupt mask of Rx descriptor ring4 is unavailable             */
      __IOM uint32_t imr_rdu5   : 1;            /*!< [30..30] Interrupt mask of Rx descriptor ring5 is unavailable             */
      __IOM uint32_t imr_rdu6   : 1;            /*!< [31..31] Interrupt mask of Rx descriptor ring6 is unavailable             */
    } isr_imr_b;
  } ;
  
  union {
    __IOM uint32_t tc;                          /*!< (@ 0x00000040) Transmit Configuration Register                            */
    
    struct {
      __IOM uint32_t r_tx_nopadding : 1;        /*!< [0..0] 1: HW does not pad short packet (< 60B).0: HW pads short
                                                     packet to 64B.                                                            */
            uint32_t            : 7;
      __IOM uint32_t lbk        : 2;            /*!< [9..8] The loopback function must be independent of the link
                                                     state.2'b00: normal operation2'b01: Loopback mode_R2T (lbkmode_r2t)
                                                     :2'b10: Reserved2'b11: Loopback mode (lbk_mode).                          */
      __IOM uint32_t ifg        : 3;            /*!< [12..10] InterFrameGap Time: This field allows the user to adjust
                                                     the interframe gap time longer than the standard: 9.6 us
                                                     for 10Mbps, 960 ns for 100Mbps. The time can be programmed
                                                     from 9.6 us to 14.4 us (10Mbps) and 960ns to 1440ns (100Mbps)             */
            uint32_t            : 19;
    } tc_b;
  } ;
  
  union {
    __IOM uint32_t rc;                          /*!< (@ 0x00000044) Receive Configuration Register                             */
    
    struct {
      __IOM uint32_t aap        : 1;            /*!< [0..0] Set to 1 to accept all packets with physical destination
                                                     address, 0 to reject                                                      */
      __IOM uint32_t apm        : 1;            /*!< [1..1] Set to 1 to accept physical match packets, 0 to reject.            */
      __IOM uint32_t am         : 1;            /*!< [2..2] Set to 1 to accept multicast packets, 0 to reject.                 */
      __IOM uint32_t ab         : 1;            /*!< [3..3] Set to 1 to accept broadcast packets, 0 to reject                  */
      __IOM uint32_t ar         : 1;            /*!< [4..4] Accept Runt: This bit allows the receiver to accept packets
                                                     that are smaller than 64 bytes. The packet must be at least
                                                     8 bytes long to be accepted as a runt. Set to 1 to accept
                                                     runt packets.                                                             */
      __IOM uint32_t aer        : 1;            /*!< [5..5] Accept Error PacketWhen set to 1, all packets with CRC
                                                     error, alignment error, and/or collided fragments will
                                                     be accepted; When set to 0, all packets with CRC error,
                                                     alignment error, and/or collided fragments will be rejected.              */
      __IOM uint32_t aflow      : 1;            /*!< [6..6] Accept flow control : When set to 1, flow control packet
                                                     will also be received & DMA to rx buffer for debug. Default
                                                     is 0                                                                      */
            uint32_t            : 25;
    } rc_b;
  } ;
  __IM  uint32_t  RESERVED1[4];
  
  union {
    __IOM uint32_t ms;                          /*!< (@ 0x00000058) Media Status Register                                      */
    
    struct {
      __IOM uint32_t refclk_on  : 1;            /*!< [0..0] 1: REF_CLK on0: REF_CLK off                                        */
      __IOM uint32_t refclk_phase : 1;          /*!< [1..1] 1: TXEN/TXD are transitioned in the falling edge; RXD
                                                     are also sampled in the falling edge0: TXEN/TXD are transitioned
                                                     in the rising edge; RXD are also sampled in the rising
                                                     edge                                                                      */
            uint32_t            : 4;
      __IOM uint32_t gmac_md_mst : 1;           /*!< [6..6] 1: GMAC is used to be MDIO master.0: GMAC is used to
                                                     be MDIO slave.                                                            */
      __IOM uint32_t reg_rmii2mii_en : 1;       /*!< [7..7] 1: transfer MII signals to RMII signalsThis function
                                                     is only valid in MII mode.                                                */
            uint32_t            : 2;
      __IOM uint32_t force_spd_mode : 1;        /*!< [10..10] 1: gmac is in force speed mode.0: gmac speed status
                                                     is from md operation.                                                     */
      __IOM uint32_t rgmii_tx_encode_sts : 1;   /*!< [11..11] This bit is valid only in phy mode. 0: Does not support
                                                     rgmii in band status(link status, speed and duplex mode
                                                     of the PHY) by encoding txd.1: Supports rgmii in band status(link
                                                     status, speed and duplex mode of the PHY) by encoding txd.                */
      __IOM uint32_t rgmii_rx_decode_sts : 1;   /*!< [12..12] 0: Does not support rgmii in band status (link status,
                                                     speed and duplex mode of the PHY) by decoding rxd.1: Supports
                                                     rgmii in band status (link status, speed and duplex mode
                                                     of the PHY) by decoding rxd.                                              */
      __IOM uint32_t gmac_phy_mode : 1;         /*!< [13..13] 1: in phy mode.0: not in phy mode.                               */
            uint32_t            : 1;
      __IOM uint32_t gmac_sel_phyif_0 : 1;      /*!< [15..15] 1: phy interface 0.works.0: phy interface 1 works.               */
      __IOM uint32_t force_spd  : 2;            /*!< [17..16] Force gmac in 10/100/GIGA mode.2'b00: 100M2'b01: 10M2'b10:
                                                     GIGA2'b11: not force mode.                                                */
      __IOM uint32_t forcelink  : 1;            /*!< [18..18] Force gmac in link ok mode. 1'b1: force gmac in linkok.1'b0:
                                                     link status is from MDIO auto-polling.                                    */
      __IOM uint32_t forcedfulldup : 1;         /*!< [19..19] Force gmac operates at full duplex mode. 1'b1: force
                                                     gmac in full duplex mode.1'b0: duplex status is from MDIO
                                                     auto-polling. Not means gmac is in half duplex mode.                      */
      __IOM uint32_t sel_mii    : 1;            /*!< [20..20] Indicates in mii mode.                                           */
      __IOM uint32_t nwcomplete : 1;            /*!< [21..21] Nway complete                                                    */
      __IOM uint32_t fulldupreg : 1;            /*!< [22..22] Indicates Full duplex mode from mdio results.                    */
      __IOM uint32_t sel_rgmii  : 1;            /*!< [23..23] Selects RGMII interface                                          */
      __IOM uint32_t rxpf       : 1;            /*!< [24..24] Pause Flag1 = Ethernet module is in backoff state because
                                                     a pause packet received.0 = pause state is clear.                         */
      __IOM uint32_t txpf       : 1;            /*!< [25..25] Tx Pause frame1 = Ethernet module has sent a pause
                                                     packet.0 = the Ethernet module has sent a timer done packet.              */
      __IOM uint32_t linkb      : 1;            /*!< [26..26] Inverse of Link status. 0 = Link OK. 1 = Link Fail.              */
      __IOM uint32_t speed_10   : 1;            /*!< [27..27] {SPEED_1000, SPEED_10} 00: 100Mbps, 01: 10Mbps                   */
      __IOM uint32_t speed_1000 : 1;            /*!< [28..28] {SPEED_1000, SPEED_10} 10: 1000Mbps, 11: not allowed             */
      __IOM uint32_t txfce      : 1;            /*!< [29..29] Tx Flow Control Enable1 = tx flow control enabled.0
                                                     = tx flow control disabled.                                               */
      __IOM uint32_t rxfce      : 1;            /*!< [30..30] RX Flow control Enable: The flow control is enabled
                                                     in full-duplex mode only. Packets are dropped if buffer
                                                     is exhausted. Default is 0.1 = Rx Flow Control Enabled.0
                                                     = Rx Flow Control Disabled.                                               */
      __IOM uint32_t force_trxfce : 1;          /*!< [31..31] Force Tx/RX Flow Control:1 = enabled Flow control in
                                                     the absence of NWAY.0 = disables Flow control in the absence
                                                     of NWAY.                                                                  */
    } ms_b;
  } ;
  
  union {
    __IOM uint32_t miia;                        /*!< (@ 0x0000005C) MII Access Register                                        */
    
    struct {
      __IOM uint32_t data       : 16;           /*!< [15..0] Defines the MII resgister data.                                   */
      __IOM uint32_t regaddr    : 5;            /*!< [20..16] Defines the MII register address.                                */
            uint32_t            : 1;
      __IOM uint32_t disable_auto_polling : 1;  /*!< [22..22] Disable auto polling feature of mdio operation.0: HW
                                                     auto polling PCS status. 1: HW does not auto polling PCS
                                                     status.                                                                   */
            uint32_t            : 3;
      __IOM uint32_t phyaddr    : 5;            /*!< [30..26] Defines the Phy address for the MII.                             */
      __IOM uint32_t flag       : 1;            /*!< [31..31] Flag bit, used to identify access to MII register1:
                                                     Write data to MII register. Turns to 0 automatically upon
                                                     completion of MAC writing to the specified MII register.0:
                                                     Read data from MII register. Turns to 1 automatically upon
                                                     completion of MAC reading the specified MII register.                     */
    } miia_b;
  } ;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t vlan;                        /*!< (@ 0x00000064) VLAN Register                                              */
    
    struct {
            uint32_t            : 15;
      __IOM uint32_t tdsc_vlan_type : 1;        /*!< [15..15] 1: tx_vlan_action field in the Tx command descriptor
                                                     is for s-tag.0: tx_vlan_action field in the Tx command
                                                     descriptor is for c-tag.                                                  */
      __IOM uint32_t stag_pid   : 16;           /*!< [31..16] Set the s-tag protocol identifier.                               */
    } vlan_b;
  } ;
  __IM  uint32_t  RESERVED3[1190];
  
  union {
    __IOM uint32_t txfdp1;                      /*!< (@ 0x00001300) Tx 1st Descriptor Ring Address Register                    */
    
    struct {
      __IOM uint32_t txfdp1     : 32;           /*!< [31..0] Tx 1st priority Descriptor Pointer to the Tx Ring.                */
    } txfdp1_b;
  } ;
  
  union {
    __IOM uint32_t txcdo1;                      /*!< (@ 0x00001304) Tx 1st Current Descriptor Offset Register                  */
    
    struct {
      __IOM uint32_t txcdo1     : 12;           /*!< [11..0] Tx 1st priority current descriptor offset: FDP+CDO =
                                                     current descriptor pointer. CDO increments by 16 bytes
                                                     each time.                                                                */
            uint32_t            : 20;
    } txcdo1_b;
  } ;
  __IM  uint32_t  RESERVED4[58];
  
  union {
    __IOM uint32_t rxfdp1;                      /*!< (@ 0x000013F0) Rx 1st Descriptor Ring Address Register                    */
    
    struct {
      __IOM uint32_t rxfdp1     : 32;           /*!< [31..0] Rx 1st queue Descriptor Pointer to the Rx Ring.                   */
    } rxfdp1_b;
  } ;
  
  union {
    __IOM uint32_t rxrs1cdo1;                   /*!< (@ 0x000013F4) Rx 1st Descriptor Ring Size & 1st Current Descriptor
                                                                    Offset Register                                            */
    
    struct {
      __IOM uint32_t rxringsize_1_h : 4;        /*!< [3..0] This is the bit[11:8] of RxRingSize1.                              */
            uint32_t            : 4;
      __IOM uint32_t rxringsize_1_l : 8;        /*!< [15..8] This is the total number of descriptors in the Rx descriptor
                                                     rings of 1st queue. (bit[7:0] of RxRingSize1)Act as bit
                                                     mask, eg. RxRingSize [11:0]:0000_0000_1111: 16 descriptors0000_0001_1111:
                                                     32 descriptors0000_0011_1111: 64 descriptors0000_0111_1111:
                                                     128 descriptors0000_1111_1111: 256 descriptors0001_1111_1111:
                                                     512 descriptors0011_1111_1111: 1024 descriptors0111_1111_1111:
                                                     2048 descriptors1111_1111_1111: 4096 descriptors Any other
                                                     value in this register yields undefined resul                             */
      __IOM uint32_t rxcdo1     : 12;           /*!< [27..16] Rx Current Descriptor Offset of 1st queue: RxFDP +
                                                     RxCDO = current descriptor pointer. CDO increments by 16
                                                     each time (each increment is one byte).                                   */
            uint32_t            : 4;
    } rxrs1cdo1_b;
  } ;
  __IM  uint32_t  RESERVED5[13];
  
  union {
    __IOM uint32_t rx_pse_des_thres_1_h;        /*!< (@ 0x0000142C) PHY Mode Clock Phase Control Register                      */
    
    struct {
            uint32_t            : 5;
      __IOM uint32_t phy_mode_clk_phase_chg : 1;/*!< [5..5] Changes the clock phase in the PHY mode                            */
            uint32_t            : 26;
    } rx_pse_des_thres_1_h_b;
  } ;
  
  union {
    __IOM uint32_t etnrxcpu1;                   /*!< (@ 0x00001430) Rx Ring1 Threshold Register                                */
    
    struct {
      __IOM uint32_t etnrxcpu1  : 32;           /*!< [31..0] Rx ring1 threshold settings                                       */
    } etnrxcpu1_b;
  } ;
  
  union {
    __IOM uint32_t io_cmd;                      /*!< (@ 0x00001434) I/O Command Register 0                                     */
    
    struct {
      __IOM uint32_t txfn1st    : 1;            /*!< [0..0] 1st Priority DMA-Ethernet Transmit enable.1: Enable.0:
                                                     Disable.                                                                  */
      __IOM uint32_t txfn2nd    : 1;            /*!< [1..1] 2nd Priority DMA-Ethernet Transmit enable.1: Enable.0:
                                                     Disable.                                                                  */
      __IOM uint32_t txfn3rd    : 1;            /*!< [2..2] 3rd Priority DMA-Ethernet Transmit enable.1: Enable.0:
                                                     Disable.                                                                  */
      __IOM uint32_t txfn4th    : 1;            /*!< [3..3] 4th Priority DMA-Ethernet Transmit enable.1: Enable.
                                                     0: Disable.                                                               */
      __IOM uint32_t te         : 1;            /*!< [4..4] Tx Enable                                                          */
      __IOM uint32_t re         : 1;            /*!< [5..5] Rx Enable                                                          */
      __IOM uint32_t reg_int_timer_sel : 2;     /*!< [7..6] RXPktTimer, TXPktTimer Unit (TU)                                   */
      __IOM uint32_t rxintmitigation_l : 3;     /*!< [10..8] This sets the number of packets received before RxOK
                                                     interrupt is triggered.0000: 1 pkt0001: 4 pkts0010: 8 pkts0011:
                                                     12 pkts0100: 16 pkts0101: 20 pkts0110: 24 pkts0111: 28
                                                     pkts                                                                      */
      __IOM uint32_t rxfth      : 2;            /*!< [12..11] Rx Threshold: Specifies the threshold level in the
                                                     Rx FIFO to begin the transmission. When the byte count
                                                     of the data in the Rx FIFO reaches this level, (or the
                                                     FIFO contains at least one complete packet or the end of
                                                     a packet) the Ethernet module will transmit this packet.00:
                                                     1024 Bytes.01: 128 Bytes.10: 256 Bytes.11: 512 Bytes.                     */
      __IOM uint32_t rxpkttimer_l : 3;          /*!< [15..13] Timer to trigger RxOK interrupt before receipt of RxIntMitigation
                                                     pkts.0000: no timer set0001~1111: the timer interval defining
                                                     a multiple of TU Ex: 011 = timer interval set to 3 x 4
                                                     =12 TU This only applies to packets of size larger than
                                                     128 bytes. Once RxOK is asserted the timer mechanism is
                                                     reinitialized. For ingress pkt which is short than 128B,
                                                     RxOK interrupt asserts after DMA completes.                               */
      __IOM uint32_t txintmitigation_l : 3;     /*!< [18..16] This sets the number of packets received before TxOK
                                                     interrupt is triggered.0000: 1 pkt0001: 4 pkts0010: 8 pkts0011:
                                                     12 pkts0100: 16 pkts0101: 20 pkts0110: 24 pkts0111: 28
                                                     pkts                                                                      */
      __IOM uint32_t tsh        : 2;            /*!< [20..19] Tx Threshold: Specifies the threshold level in the
                                                     Tx FIFO to begin the transmission. When the byte count
                                                     of the data in the Tx FIFO reaches this level, (or the
                                                     FIFO contains at least one complete packet or the end of
                                                     a packet) the Ethernet module will transmit this packet.00:
                                                     128 Bytes.01: 256 Bytes.10: 512 Bytes.11: 1024 Bytes.                     */
      __IOM uint32_t rxintmitigation_h : 1;     /*!< [21..21] See bit[19:8]                                                    */
      __IOM uint32_t rxpkttimer_h : 1;          /*!< [22..22] See bit[15:13]                                                   */
      __IOM uint32_t txintmitigation_h : 1;     /*!< [23..23] See bit[18:16]                                                   */
      __IOM uint32_t txpkttimer : 4;            /*!< [27..24] Timer to trigger TxOK interrupt before receipt of TxIntMitigation
                                                     pkts.0000: no timer set0001~1111: the timer interval defining
                                                     a multiple of TUEx: 0011 = timer interval sets to 3 x 4
                                                     =12 TU Once TxOK is asserted the timer mechanism is reinitialized.        */
      __IOM uint32_t en_early_tx : 1;           /*!< [28..28] 0: disable, 1: enable. Disable early tx by GAMC while
                                                     tx command descriptor.IPCS, UDPCS or TCPCS are set to high.               */
      __IOM uint32_t max_dma_sel_h : 1;         /*!< [29..29] See bit[31]                                                      */
      __IOM uint32_t shortdesformat : 1;        /*!< [30..30] Short descriptor format1: tx/rx descriptor will use
                                                     old format (4 x 32-bit each item)0: use new format to support
                                                     sram mapping.                                                             */
      __IOM uint32_t max_dma_sel_l : 1;         /*!< [31..31] Select the dma burst size on bus.00: 16 DW (1DW = 4
                                                     Bytes)01: 32 DW10: 64 DW11: 128DW.                                        */
    } io_cmd_b;
  } ;
  
  union {
    __IOM uint32_t io_cmd1;                     /*!< (@ 0x00001438) I/O Command Register 1                                     */
    
    struct {
            uint32_t            : 8;
      __IOM uint32_t txfn5th    : 1;            /*!< [8..8] 5th Priority DMA-Ethernet Transmit enable.1: Enable.
                                                     0: Disable.                                                               */
            uint32_t            : 5;
      __IOM uint32_t Tx_hl_pri_se : 2;          /*!< [15..14] 2'b00: TX ring uses strict priority.2'b01: TX ring
                                                     uses high and low queue priority. Inside high queue, tx
                                                     ring is round robin. Inside low queue, tx ring is round
                                                     robin. Strict priority is used for high and low queue selection.2'b10
                                                     and 2'b11: Reserved.                                                      */
      __IOM uint32_t rxring1    : 1;            /*!< [16..16] Ethernet-DMA Receive Ring1 enable.1: Enable.0: Disable.          */
      __IOM uint32_t rxring2    : 1;            /*!< [17..17] Ethernet-DMA Receive Ring2 enable.1: Enable. 0: Disable.         */
      __IOM uint32_t rxring3    : 1;            /*!< [18..18] Ethernet-DMA Receive Ring3 enable.1: Enable. 0: Disable.         */
      __IOM uint32_t rxring4    : 1;            /*!< [19..19] Ethernet-DMA Receive Ring4 enable.1: Enable. 0: Disable.         */
      __IOM uint32_t rxring5    : 1;            /*!< [20..20] Ethernet-DMA Receive Ring5 enable.1: Enable. 0: Disable.         */
      __IOM uint32_t rxring6    : 1;            /*!< [21..21] Ethernet-DMA Receive Ring6 enable.1: Enable. 0: Disable.         */
            uint32_t            : 2;
      __IOM uint32_t en_1gb     : 1;            /*!< [24..24] 1: support 1GB addressing in lx master bus.0: Not support.       */
      __IOM uint32_t en_rx_mring : 1;           /*!< [25..25] Enable rx multiple rings.1: rx using multiple rings.
                                                     max: 6 rings (ring1 to ring6).0: rx using single ring (ring1
                                                     only).                                                                    */
      __IOM uint32_t rxokint_msk_128b : 1;      /*!< [26..26] 1: For ingress pkt which is short than 128B, RxOK interrupt
                                                     asserts after DMA completes (compatible issue).0: For ingress
                                                     pkt which is short than 128B, RxOK interrupt does not assert
                                                     after DMA completes.                                                      */
      __IOM uint32_t en_precise_dma : 1;        /*!< [27..27] 0: disable precise DMA transfer.1: enable precise DMA
                                                     transfer.                                                                 */
      __IOM uint32_t dsc_format_extra : 3;      /*!< [30..28] Extra descriptor format.SW should set this field before
                                                     set io_cmd.te or io_cmd.re to 1.                                          */
            uint32_t            : 1;
    } io_cmd1_b;
  } ;
} ETHERNET_Type;                                /*!< Size = 5180 (0x143c)                                                      */



/* =========================================================================================================================== */
/* ================                                           SDMMC                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief SDMMC Host - for SD memory card storage (SDMMC)
  */

typedef struct {                                /*!< (@ 0x40058000) SDMMC Structure                                            */
  __IM  uint32_t  RESERVED[256];
  
  union {
    __IOM uint32_t sram_ctl;                    /*!< (@ 0x00000400) SRAM Control Register                                      */
    
    struct {
      __IOM uint32_t mem_region : 4;            /*!< [3..0] Set this bit to enable buffer SRAM direct access mode.             */
      __IOM uint32_t access_en  : 1;            /*!< [4..4] Set this bit to enable buffer SRAM direct access mode.             */
      __IOM uint32_t map_sel    : 1;            /*!< [5..5] 0: R-Bus = x01020304 => to flash 01, 02, 03, 04; 1: R-Bus
                                                     = x01020304 => to flash 04, 03, 02, 01                                    */
      __IOM uint32_t lx_burst_size : 2;         /*!< [7..6] Set the Lexra burst size.0: 64 Bytes; 1: 128 Bytes; 2:
                                                     256 Bytes; 3: 128 Bytes                                                   */
            uint32_t            : 24;
    } sram_ctl_b;
  } ;
  
  union {
    __IOM uint32_t dma_ctl1;                    /*!< (@ 0x00000404) DMA Control Register 1                                     */
    
    struct {
      __IOM uint32_t dram_sa    : 28;           /*!< [27..0] Dram start address for DMA transfer. This information
                                                     will be map to addcmd. (8 Bytes Unit, 1 means 8B)                         */
            uint32_t            : 4;
    } dma_ctl1_b;
  } ;
  
  union {
    __IOM uint32_t dma_ctl2;                    /*!< (@ 0x00000408) DMA Control Register 2                                     */
    
    struct {
      __IOM uint32_t dma_len    : 16;           /*!< [15..0] Transfer length for DMA transfer between DMA buffer
                                                     and DDR. (512B Unit, 1 means 512B)                                        */
            uint32_t            : 16;
    } dma_ctl2_b;
  } ;
  
  union {
    __IOM uint32_t dma_ctl3;                    /*!< (@ 0x0000040C) DMA Control Register 3                                     */
    
    struct {
      __IOM uint32_t dma_xfer   : 1;            /*!< [0..0] Set this bit to transfer data between DRAM and DMA buffer.
                                                     Direction must be set at next bit. The transfer length
                                                     is reference to DMA_CTL2[15:0]. This bit will be auto clear
                                                     when transfer done.                                                       */
      __IOM uint32_t ddr_wr     : 1;            /*!< [1..1] 1: Move data from DMA buffer to DDR; 0: Move data from
                                                     DDR to DMA Buffer.                                                        */
            uint32_t            : 2;
      __IOM uint32_t rsp17_sel  : 1;            /*!< [4..4] For response is R2 case, reponse will transfer by dma
                                                     and not store in register.1: dma count to 16byte and send
                                                     sb1_req; 0: normal case.                                                  */
      __IOM uint32_t dat64_sel  : 1;            /*!< [5..5] For CMD6 case, read data length is 64byte (less than
                                                     256 byte)1: dma count to 64byte and send sb1_req; 0: normal
                                                     case.                                                                     */
            uint32_t            : 26;
    } dma_ctl3_b;
  } ;
  
  union {
    __IOM uint32_t sys_low_pwr;                 /*!< (@ 0x00000410) Low Power Control Register                                 */
    
    struct {
      __IOM uint32_t dma_sram_rdy_num : 4;      /*!< [3..0] DMA SRAM ready cycle (leave sleep mode)(N+1) * clk_sys
                                                     period                                                                    */
      __IOM uint32_t dma_sram_lp_ena : 1;       /*!< [4..4] DMA SRAM low power enable                                          */
            uint32_t            : 1;
      __IOM uint32_t sys_clk_gate_ena : 1;      /*!< [6..6] DMA clk_sys gating enable                                          */
            uint32_t            : 25;
    } sys_low_pwr_b;
  } ;
  __IM  uint32_t  RESERVED1[4];
  
  union {
    __IOM uint32_t sd_isr;                      /*!< (@ 0x00000424) SD Interrupt Status Register                               */
    
    struct {
      __IOM uint32_t write_data : 1;            /*!< [0..0] 1 to set, 0 to clear bit with 1.                                   */
      __IOM uint32_t int1       : 1;            /*!< [1..1] SD Int1. Card End.                                                 */
      __IOM uint32_t int2       : 1;            /*!< [2..2] SD Int2. Card Error.                                               */
            uint32_t            : 1;
      __IOM uint32_t int4       : 1;            /*!< [4..4] SD Int4. DMA transfer done INT.                                    */
            uint32_t            : 27;
    } sd_isr_b;
  } ;
  
  union {
    __IOM uint32_t sd_isren;                    /*!< (@ 0x00000428) SD Interrupt Enable Register                               */
    
    struct {
      __IOM uint32_t write_data : 1;            /*!< [0..0] 1 to set, 0 to clear bit with 1.                                   */
      __IOM uint32_t int1en     : 1;            /*!< [1..1] SD Int1 EnableCard End INT Enable.                                 */
      __IOM uint32_t int2en     : 1;            /*!< [2..2] SD Int2 EnableCard Error INT Enable.                               */
            uint32_t            : 1;
      __IOM uint32_t int4en     : 1;            /*!< [4..4] SD Int4 Enabledma_clr INT Enable.                                  */
            uint32_t            : 27;
    } sd_isren_b;
  } ;
  __IM  uint32_t  RESERVED2[18];
  
  union {
    __IOM uint32_t pad_ctl;                     /*!< (@ 0x00000474) Pad Control Register                                       */
    
    struct {
      __IOM uint32_t tune3318   : 1;            /*!< [0..0] Pad select 3.3v or 1.8v.1: 3.3v; 0: 1.8v                           */
            uint32_t            : 31;
    } pad_ctl_b;
  } ;
  
  union {
    __IOM uint32_t ckgen_ctl;                   /*!< (@ 0x00000478) Clock Generation Control Register                          */
    
    struct {
      __IOM uint32_t clk_div    : 3;            /*!< [2..0] 000: div1; 001: div2; 010: div4; 011: div8                         */
            uint32_t            : 1;
      __IOM uint32_t crc_clk_src : 2;           /*!< [5..4] 00: ssc_clk; 01: ssc_clk_vp0; 10: ssc_clk_vp1                      */
            uint32_t            : 2;
      __IOM uint32_t sd30_push_clk_src : 2;     /*!< [9..8] 00: ssc_clk; 01: ssc_clk_vp0; 10: ssc_clk_vp1                      */
            uint32_t            : 2;
      __IOM uint32_t sd30_sample_clk_src : 2;   /*!< [13..12] 00: ssc_clk; 01: ssc_clk_vp0; 10: ssc_clk_vp1                    */
            uint32_t            : 2;
      __IOM uint32_t crc_clk_change : 1;        /*!< [16..16] 0: from crc_clk_src; 1: clk4M                                    */
      __IOM uint32_t sd30_push_change : 1;      /*!< [17..17] 0: from sd30_push_clk_src; 1: clk4M                              */
      __IOM uint32_t sd30_sample_change : 1;    /*!< [18..18] 0: from sd30_sample_clk_src; 1: clk4M                            */
            uint32_t            : 13;
    } ckgen_ctl_b;
  } ;
  __IM  uint32_t  RESERVED3[33];
  __IM  uint16_t  RESERVED4;
  
  union {
    __IOM uint8_t card_drive_sel;               /*!< (@ 0x00000502) Card Driving Selection Register                            */
    
    struct {
      __IOM uint8_t cf_drive    : 2;            /*!< [1..0] CF Interface Drive.00: 4mA; 01: 8mA; 10: 12mA; 11: 12mA            */
      __IOM uint8_t xd_drive    : 2;            /*!< [3..2] XD Interface Drive.00: 4mA; 01: 8mA; 10: 12mA; 11: 12mA            */
      __IOM uint8_t sd_drive    : 2;            /*!< [5..4] SD DAT7~4 Interface Drive.00: 4mA; 01: 8mA; 10: 12mA;
                                                     11: 12mA                                                                  */
      __IOM uint8_t ms_drive    : 2;            /*!< [7..6] MS Interface Drive.00: 4mA; 01: 8mA; 10: 12mA; 11: 12mA            */
    } card_drive_sel_b;
  } ;
  
  union {
    __IOM uint8_t card_stop;                    /*!< (@ 0x00000503) Stop Transfer Register                                     */
    
    struct {
      __IOM uint8_t cf_module   : 1;            /*!< [0..0] Target module is CF/MD card module. If set this bit the
                                                     transfer will be stop and the state machine of transfer
                                                     will return idle state.                                                   */
      __IOM uint8_t sm_module   : 1;            /*!< [1..1] Target module is SM/XD card module. If set this bit the
                                                     transfer will be stop and the state machine of transfer
                                                     will return idle state.                                                   */
      __IOM uint8_t sd_module   : 1;            /*!< [2..2] Target module is SD/MMC card module (SD). If set this
                                                     bit the transfer will be stop and the state machine of
                                                     transfer will return idle state.                                          */
      __IOM uint8_t ms_module   : 1;            /*!< [3..3] Target module is MS/MS-Pro/HG card module (MS). If set
                                                     this bit the transfer will be stop and the state machine
                                                     of transfer will return idle state.                                       */
      __IOM uint8_t sd2_module  : 1;            /*!< [4..4] Target module is SD/MMC card module (SD2). If set this
                                                     bit the transfer will be stop and the state machine of
                                                     transfer will return idle state.                                          */
      __IOM uint8_t ms2_module  : 1;            /*!< [5..5] Target module is MS/MS-Pro/HG card module (MS2). If set
                                                     this bit the transfer will be stop and the state machine
                                                     of transfer will return idle state.                                       */
            uint8_t             : 2;
    } card_stop_b;
  } ;
  __IM  uint32_t  RESERVED5[2];
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint8_t card_select;                  /*!< (@ 0x0000050E) Card Type Select Register                                  */
    
    struct {
      __IOM uint8_t card_sel    : 3;            /*!< [2..0] Card Select. Specify the current active card module.000:
                                                     CF module001: XD module010: SD module011: MS module100:
                                                     I2C module101: Reserved110: SD2 module111: MS2 module                     */
            uint8_t             : 5;
    } card_select_b;
  } ;
  __IOM uint8_t   dummy1;                       /*!< (@ 0x0000050F) Dummy Register 1                                           */
  __IM  uint32_t  RESERVED7[3];
  __IM  uint16_t  RESERVED8;
  __IM  uint8_t   RESERVED9;
  
  union {
    __IOM uint8_t card_exist;                   /*!< (@ 0x0000051F) Card Detection Register                                    */
    
    struct {
      __IOM uint8_t cf_exist    : 1;            /*!< [0..0] CF Existence. If this bit is set it means CF/MD card
                                                     is in its socket.                                                         */
      __IOM uint8_t sm_exist    : 1;            /*!< [1..1] SM Existence. If this bit is set it means SM card is
                                                     in its socket.                                                            */
      __IOM uint8_t sd_exist    : 1;            /*!< [2..2] SD Existence. If this bit is set it means SD/MMC card
                                                     is in its socket.                                                         */
      __IOM uint8_t ms_exist    : 1;            /*!< [3..3] MS Existence. If this bit is set it means MS/MS-pro card
                                                     is in its socket.                                                         */
      __IOM uint8_t xd_exist    : 1;            /*!< [4..4] XD Existence. If this bit is set it means XD card is
                                                     in its socket.                                                            */
      __IOM uint8_t sd_wp       : 1;            /*!< [5..5] SD Write Protect. If this bit is set it means SD card
                                                     is mechanical write protected.                                            */
      __IOM uint8_t xd_wp       : 1;            /*!< [6..6] XD_WP Input. If the XD_WP pin is configure as input,
                                                     this bit reflect the level of XD_WP signal directly.                      */
            uint8_t             : 1;
    } card_exist_b;
  } ;
  
  union {
    __IOM uint8_t card_int_en;                  /*!< (@ 0x00000520) Card Interrupt Enable Register                             */
    
    struct {
      __IOM uint8_t cf_int_en   : 1;            /*!< [0..0] CF Card Interrupt Enable. If this bit is set it enables
                                                     the interrupt of CF card                                                  */
      __IOM uint8_t sm_int_en   : 1;            /*!< [1..1] SM Card Interrupt Enable. If this bit is set it enables
                                                     the interrupt of SM card                                                  */
      __IOM uint8_t sd_int_en   : 1;            /*!< [2..2] SD/MMC Interrupt Enable. If this bit is set it enables
                                                     the interrupt of SD/MMC card                                              */
      __IOM uint8_t ms_int_en   : 1;            /*!< [3..3] MS/MS-pro/HG card Interrupt Enable. If this bit is set
                                                     it enables the interrupt of MS/MS-pro card                                */
      __IOM uint8_t xd_int_en   : 1;            /*!< [4..4] XD Card Interrupt Enable. If this bit is set it enables
                                                     the interrupt of XD card                                                  */
      __IOM uint8_t sd2_int_en  : 1;            /*!< [5..5] SD/MMC (SD2) Interrupt Enable. If this bit is set it
                                                     enables the interrupt of SD/MMC card                                      */
      __IOM uint8_t ms2_int_en  : 1;            /*!< [6..6] MS/MS-pro/HG (MS2) card Interrupt Enable. If this bit
                                                     is set it enables the interrupt of MS/MS-pro card                         */
      __IOM uint8_t gpio_int_en : 1;            /*!< [7..7] GPIO[0] Interrupt Enable. If this bit is set it enables
                                                     the interrupt of GPIO0                                                    */
    } card_int_en_b;
  } ;
  
  union {
    __IOM uint8_t card_int_pend;                /*!< (@ 0x00000521) Card Interrupt Status Register                             */
    
    struct {
      __IOM uint8_t cf_int_pend : 1;            /*!< [0..0] CF Card Interrupt Pending. If this bit is set it means
                                                     the interrupt of CF card is pending and write '1' to this
                                                     bit to clear the interrupt flag to '0'                                    */
      __IOM uint8_t sm_int_pend : 1;            /*!< [1..1] SM Card Interrupt Pending. If this bit is set it means
                                                     the interrupt of SM card is pending and write '1' to this
                                                     bit to clear the interrupt flag to '0'                                    */
      __IOM uint8_t sd_int_pend : 1;            /*!< [2..2] SD/MMC Interrupt Pending. If this bit is set it means
                                                     the interrupt of SD/MMC card is pending and write '1' to
                                                     this bit to clear the interrupt flag to '0'                               */
      __IOM uint8_t ms_int_pend : 1;            /*!< [3..3] MS/MS-pro/HG card Interrupt Pending. If this bit is set
                                                     it means the interrupt of MS/MS-pro card is pending and
                                                     write '1' to this bit to clear the interrupt flag to '0'                  */
      __IOM uint8_t xd_int_pend : 1;            /*!< [4..4] XD Card Interrupt Pending. If this bit is set it means
                                                     the interrupt of XD card is pending and write '1' to this
                                                     bit to clear the interrupt flag to '0'                                    */
      __IOM uint8_t sd2_int_pend : 1;           /*!< [5..5] SD/MMC (SD2) Interrupt Pending. If this bit is set it
                                                     means the interrupt of SD/MMC card is pending and write
                                                     '1' to this bit to clear the interrupt flag to '0'                        */
      __IOM uint8_t ms2_int_pend : 1;           /*!< [6..6] MS/MS-pro/HG (MS2) card Interrupt Pending. If this bit
                                                     is set it means the interrupt of MS/MS-pro card is pending
                                                     and write '1' to this bit to clear the interrupt flag to
                                                     '0'                                                                       */
      __IOM uint8_t gpio_int_pend : 1;          /*!< [7..7] GPIO[0] Interrupt Pending. If this bit is set it means
                                                     the interrupt of GPIO0 is pending and write '1' to this
                                                     bit to clear the interrupt flag to '0'                                    */
    } card_int_pend_b;
  } ;
  __IM  uint16_t  RESERVED10;
  __IM  uint32_t  RESERVED11;
  __IM  uint8_t   RESERVED12;
  
  union {
    __IOM uint8_t card_clk_en_ctl;              /*!< (@ 0x00000529) Card Clock Enable Control Register                         */
    
    struct {
      __IOM uint8_t cf_clk_en   : 1;            /*!< [0..0] CF Card Module Clock Enable Control. Disable clock can
                                                     save power. 0: Disable; 1: Enable                                         */
      __IOM uint8_t xd_clk_en   : 1;            /*!< [1..1] XD Card Module Clock Enable Control. Disable clock can
                                                     save power.0: Disable; 1: Enable                                          */
      __IOM uint8_t sd_clk_en   : 1;            /*!< [2..2] SD Card Module Clock Enable Control. Disable clock can
                                                     save power. 0: Disable; 1: Enable                                         */
      __IOM uint8_t ms_clk_en   : 1;            /*!< [3..3] MS Card Module Clock Enable Control. Disable clock can
                                                     save power. 0: Disable; 1: Enable                                         */
      __IOM uint8_t sd2_clk_en  : 1;            /*!< [4..4] SD2 Card Module Clock Enable Control. Disable clock can
                                                     save power.0: Disable; 1: Enable                                          */
      __IOM uint8_t ms2_clk_en  : 1;            /*!< [5..5] MS2 Card Module Clock Enable Control. Disable clock can
                                                     save power. 0: Disable; 1: Enable                                         */
      __IOM uint8_t sw_clk_mode : 1;            /*!< [6..6] Switch Clock Mode. Clk_en use FW configuration of HW
                                                     setting.0: Clk_en use FW configure1: Clk_en use HW setting                */
      __IOM uint8_t auto_cbw    : 1;            /*!< [7..7] Auto CBW Mode. Used for card select option.0: Card select
                                                     is configured by FW.1: Card select is configured by HW.                   */
    } card_clk_en_ctl_b;
  } ;
  __IM  uint16_t  RESERVED13;
  __IM  uint32_t  RESERVED14;
  
  union {
    __IOM uint8_t clk_pad_drive;                /*!< (@ 0x00000530) Clock Pad Driving Register                                 */
    
    struct {
      __IOM uint8_t nmos_drive  : 3;            /*!< [2..0] SD_CLK PAD NMOS drive select 3V3: 1V8:000: x 10.1 x 1.93001:
                                                     x 13.5 x 3.85010,100: x 16.9 x 5.78011,101: x 20.2 x 7.73110:
                                                     x 23.5 x 9.65111: x 26.8 x 11.5                                           */
      __IOM uint8_t pmos_drive  : 3;            /*!< [5..3] SD_CLK PAD PMOS drive select 3V3: 1V8:000: x 7,07 x 2.27001:
                                                     x 14.2 x 4.61010,100: x 21 x 6.68011,101: x 27.9 x 9.14110:
                                                     x 34.9 x 11.5111: x 42.4 x 13.8                                           */
            uint8_t             : 2;
    } clk_pad_drive_b;
  } ;
  
  union {
    __IOM uint8_t cmd_pad_drive;                /*!< (@ 0x00000531) Command Pad Driving Register                               */
    
    struct {
      __IOM uint8_t nmos_drive  : 3;            /*!< [2..0] SD_CMD PAD NMOS drive select 3V3: 1V8:000: x 10.1 x 1.93001:
                                                     x 13.5 x 3.85010,100: x 16.9 x 5.78011,101: x 20.2 x 7.73110:
                                                     x 23.5 x 9.65111: x 26.8 x 11.5                                           */
      __IOM uint8_t pmos_drive  : 3;            /*!< [5..3] SD_CMD PAD PMOS drive select3V3: 1V8:000: x 7,07 x 2.27001:
                                                     x 14.2 x 4.61010,100: x 21 x 6.68011,101: x 27.9 x 9.14110:
                                                     x 34.9 x 11.5111: x 42.4 x 13.8                                           */
            uint8_t             : 2;
    } cmd_pad_drive_b;
  } ;
  
  union {
    __IOM uint8_t dat_pad_drive;                /*!< (@ 0x00000532) Data Pad Driving Register                                  */
    
    struct {
      __IOM uint8_t nmos_drive  : 3;            /*!< [2..0] SD_DAT[3:0] PAD NMOS drive select 3V3: 1V8:000: x 10.1
                                                     x 1.93001: x 13.5 x 3.85010,100: x 16.9 x 5.78011,101:
                                                     x 20.2 x 7.73110: x 23.5 x 9.65111: x 26.8 x 11.5                         */
      __IOM uint8_t pmos_drive  : 3;            /*!< [5..3] SD_DAT[3:0] PAD PMOS drive select3V3: 1V8:000: x 7,07
                                                     x 2.27001: x 14.2 x 4.61010,100: x 21 x 6.68011,101: x
                                                     27.9 x 9.14110: x 34.9 x 11.5111: x 42.4 x 13.8                           */
            uint8_t             : 2;
    } dat_pad_drive_b;
  } ;
  __IM  uint8_t   RESERVED15;
  __IM  uint32_t  RESERVED16[19];
  
  union {
    __IOM uint8_t sd_config1;                   /*!< (@ 0x00000580) SD Configuration Register 1                                */
    
    struct {
      __IOM uint8_t bus_width   : 2;            /*!< [1..0] 00: 1-bit bus01: 4-bit bus10: 8-bit bus11: Reserved                */
      __IOM uint8_t mode_sel    : 2;            /*!< [3..2] 00: SD20 mode (single data rate; internal clock frequency
                                                     is 2 times as SD_CLK)01: DDR mode (double data rate; internal
                                                     clock frequency is 2 times as SD_CLK)10: SD30 mode (single
                                                     data rate; internal clock frequency is the same as SD_CLK;
                                                     sampling point turning can only be used in this mode)11:
                                                     ReservedNote: When access SDR Card that needs to do sampling
                                                     turning, we must select SD30_mode; when access SDR Card
                                                     that needn't sampling turning, both SD20_mode and SD30_mode
                                                     is available.                                                             */
      __IOM uint8_t sd30_async_fifo_rst : 1;    /*!< [4..4] When SD30_mode is asserted, the input CMD/DAT will be
                                                     latched by an asynchronous FIFO. The write clock of FIFO
                                                     is sample clock; the read clock of FIFO is internal clock.Write
                                                     this bit to 1'b0 to reset write/read pointer of FIFO after
                                                     the frequency/phase of sample clock or internal clock is
                                                     changed.                                                                  */
            uint8_t             : 1;
      __IOM uint8_t clk_div     : 1;            /*!< [6..6] Clock Divider (only available when initial mode is set)0:
                                                     SDCLK is divided by 1281: SDCLK is divided by 256                         */
      __IOM uint8_t initial_mode : 1;           /*!< [7..7] Initial Mode (can not be used in SD30 mode)This bit is
                                                     used to control whether the SD clock will be divided by
                                                     clock divider0: The SD clock can not be divided1: The SD
                                                     clock will de divided by the value of Clock Divider                       */
    } sd_config1_b;
  } ;
  
  union {
    __IOM uint8_t sd_config2;                   /*!< (@ 0x00000581) SD Configuration Register 2                                */
    
    struct {
      __IOM uint8_t rsp_type    : 2;            /*!< [1..0] Response Type Configure.00: No response01: 6-byte response10:
                                                     17-byte response11: Reserved                                              */
      __IOM uint8_t crc7_chk    : 1;            /*!< [2..2] CRC7 Check Enable.0: Check CRC71: Not check CRC7                   */
      __IOM uint8_t wait_busy_end : 1;          /*!< [3..3] Wait busy End EnableIf this bit is set, hardware will
                                                     wait (with SD_CLK continually toggling) till SD card is
                                                     ready (SD_DAT0 is 1). This bit is only available when HW
                                                     executes SEND_CMD_GET_RSP command code0: .Not wait busy
                                                     end; HW will stop toggle SD clock after the command/response
                                                     transfer is completed, not concern about whether the SD_DAT0
                                                     is 1b or not1: Wait busy end; HW will continue to toggle
                                                     SD clock if SD_DAT0 is 0b                                                 */
      __IOM uint8_t ignore_crc_sts_err : 1;     /*!< [4..4] Ignore Write CRC Error Enable. Set this bit to ignore
                                                     the write error.0: Check whether CRC status returned by
                                                     card is correct1: Not check whether CRC status returned
                                                     by card is correct                                                        */
      __IOM uint8_t wait_crc_sts_timeout : 1;   /*!< [5..5] Wait Write CRC Status Time Out Enable If this bit is
                                                     set, HW will check whether the write CRC status is sent
                                                     by card in time.(In SD3.0 spec, card should send the CRC
                                                     status within 8 clocks, HW will wait 16 clocks actually)
                                                     0: HW will Check whether the write CRC status is time-out1:
                                                     HW will Not Check whether the write CRC status is time-out                */
      __IOM uint8_t crc16_chk   : 1;            /*!< [6..6] CRC16 Check Enable.0: Check CRC161: Not check CRC16                */
      __IOM uint8_t crc7_cal    : 1;            /*!< [7..7] CRC7 Calculation Enable.0: Calculate CRC71: No calculation         */
    } sd_config2_b;
  } ;
  
  union {
    __IOM uint8_t sd_config3;                   /*!< (@ 0x00000582) SD Configuration Register 3                                */
    
    struct {
      __IOM uint8_t rsp_timeout_en : 1;         /*!< [0..0] SD CMD Response Time Out Enable. If this bit is set,
                                                     HW will not check whether card's response to command is
                                                     time-out. It is considered to time-out if there is no SD
                                                     command response within 80 periods of SD_CLK after the
                                                     end bit of command is on the bus.0: Not check whether the
                                                     response to command is time-out1: Check whether the response
                                                     to command is time-out                                                    */
      __IOM uint8_t addr_mode   : 1;            /*!< [1..1] Address mode. 0: sector address mode SD start data address
                                                     set in SD read/write command argument(CMD18/CMD25) equal
                                                     to (the start sector address) which is set in SCSI command
                                                     read10/write10;1: byte mode SD start data address set in
                                                     SD read/write command argument(CMD18/CMD25) equal to (the
                                                     start sector address <<9)                                                 */
      __IOM uint8_t rsp_chk     : 1;            /*!< [2..2] SD CMD Response Check EnableWhen in Random auto mode,
                                                     If this bit is set, HW will check whether card's response
                                                     is received correctly or not. When not in random auto mode,
                                                     this bit is useless.0: No check whether the response of
                                                     command is correct1: Check whether the response to command
                                                     is correct                                                                */
      __IOM uint8_t sd20_clk_stop : 1;          /*!< [3..3] SD20 Clock Stop After Data Transfer Over Enable. (Default
                                                     Disable)In order to conform to eMMC spec(NAC minimum value
                                                     is 2 SD Clock cycle), when this bit is 1'b1 and data transfer
                                                     is over(Sector Count is 0), SD clock(SD20 mode) is stopped
                                                     immediately.0: Disable1: Enable                                           */
      __IOM uint8_t sd30_clk_stop : 1;          /*!< [4..4] SD30 Clock Stop After Data Transfer Over Enable. (Default
                                                     Disable)In order to conform to eMMC spec(NAC minimum value
                                                     is 2 SD Clock cycle), when this bit is 1'b1 and data transfer
                                                     is over(Sector Count is 0), SD clock(SD30 SDR and DDR mode)
                                                     is stopped immediately.0: Disable1: Enable                                */
      __IOM uint8_t wait_card_idle : 1;         /*!< [5..5] Data Phase Wait Card busy Enable.When this bit is set
                                                     , wait until SD card not busy, then set sd_end.0: No wait
                                                     SD card not busy, set sd_end immediately when data transfer
                                                     is over1: Wait until SD card is not busy, then set sd_end                 */
      __IOM uint8_t cmd_start_wait_card_idle : 1;/*!< [6..6] CMD Start Wait No Card busy.When this bit is set , no
                                                     wait card busy and send command immediately.0: Wait until
                                                     card is not busy, then send the pending command1: No wait
                                                     card busy and send command immediately                                    */
      __IOM uint8_t stop_cmd_start_wait_card_idle : 1;/*!< [7..7] STOP CMD Start No Wait Card busy.This bit is only valid
                                                     when the SD card controller is auto in random auto mode.In
                                                     random auto mode, SD card controller will auto send stop
                                                     cmd(CMD12) after read/write cmd(cmd18/cmd25), this bit
                                                     control whether HW wait busy end before send CMD12 When
                                                     this bit is set , no wait card busy and send stop command
                                                     (CMD12) immediately.0: Wait until card is not busy, then
                                                     send the stop command (CMD12)1: No wait card busy and send
                                                     stop command immediately                                                  */
    } sd_config3_b;
  } ;
  
  union {
    __IOM uint8_t sd_status1;                   /*!< (@ 0x00000583) SD Status Register 1                                       */
    
    struct {
      __IOM uint8_t tune_patrn_err : 1;         /*!< [0..0] SD Tuning Pattern Compare Error.This bit will be set
                                                     to 1'b1, if the tuning data sampled by HW is not correct.                 */
      __IOM uint8_t crc_sts_timeout_err : 1;    /*!< [1..1] Get Write CRC Status Time-out ErrorThis bit will be set
                                                     to 1'b1, if SD card doesn't return write CRC status bits
                                                     to host within 8 SD_CLK cycles after the end bit of data
                                                     packet is on the bus (actually, HW will wait 16 clocks).                  */
      __IOM uint8_t crc_sts_val : 3;            /*!< [4..2] Status Of Write CRC Status. This field reflects write
                                                     error bits returned from SD card. When card check CRC error,
                                                     it sends back CRC status (101); when card check CRC no
                                                     error, it sends back CRC status (010); when flash programming
                                                     error, CRC status read (111).                                             */
      __IOM uint8_t crc_sts_err : 1;            /*!< [5..5] Write CRC Error.This bit will be set to 1'b1, if the
                                                     write CRC status bits are not equal to 3'b010. (this means
                                                     Card detected CRC16 error in the data it received from
                                                     host).                                                                    */
      __IOM uint8_t crc16_err   : 1;            /*!< [6..6] CRC16 Error. This bit will be set to 1'b1, if there is
                                                     CRC16 check error in the data from SD card.                               */
      __IOM uint8_t crc7_err    : 1;            /*!< [7..7] CRC7 Error. This bit will be set to 1'b1, if there is
                                                     CRC7 check error in the response from SD card.                            */
    } sd_status1_b;
  } ;
  
  union {
    __IOM uint8_t sd_status2;                   /*!< (@ 0x00000584) SD Status Register 2                                       */
    
    struct {
      __IOM uint8_t rsp_timeout_err : 1;        /*!< [0..0] SD CMD Response Timeout Error.This bit will be set to
                                                     1'b1, if there is no response within 80 periods of SD_CLK
                                                     after the end bit of command is on the bus.                               */
      __IOM uint8_t rsp_invalid : 1;            /*!< [1..1] SD CMD Response Invalid.If SD_CONFIGURE3 bit[2] is set,
                                                     this bit will reflect when the response is correct or not.
                                                     If this bit is set, sd_end and sd_error (SD_TRANSFER bit[6]
                                                     and bit[4]) will also be set0: The response of command
                                                     is correct1: The response to command is not correct                       */
      __IOM uint8_t cbw_state   : 4;            /*!< [5..2] CBW State Machine.                                                 */
            uint8_t             : 2;
    } sd_status2_b;
  } ;
  
  union {
    __IOM uint8_t sd_bus_status;                /*!< (@ 0x00000585) SD Bus Status Register                                     */
    
    struct {
      __IOM uint8_t cmd         : 1;            /*!< [0..0] This bit reflect the level of pin SD_CMD.                          */
      __IOM uint8_t dat3_0      : 4;            /*!< [4..1] This bit reflect the level of pin SD_DAT3~SD_DAT0.                 */
            uint8_t             : 1;
      __IOM uint8_t stop_sdclk_when_no_xfer : 1;/*!< [6..6] Stop SD_CLK toggling when no cmd/data transfer (ignore
                                                     the level of SDDAT0)                                                      */
      __IOM uint8_t sdclk_toggle : 1;           /*!< [7..7] SD_CLK Toggle Enable. If this bit is set, host will generate
                                                     SDCLK toggle signal even when there is no signal transaction
                                                     on the CMD/DAT bus                                                        */
    } sd_bus_status_b;
  } ;
  __IM  uint16_t  RESERVED17;
  __IM  uint8_t   RESERVED18;
  
  union {
    __IOM uint8_t sd_cmd0;                      /*!< (@ 0x00000589) SD Command Register 0                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[47:40] or Response Data[47:40].                            */
    } sd_cmd0_b;
  } ;
  
  union {
    __IOM uint8_t sd_cmd1;                      /*!< (@ 0x0000058A) SD Command Register 1                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[39:32] or Response Data[39:32].                            */
    } sd_cmd1_b;
  } ;
  
  union {
    __IOM uint8_t sd_cmd2;                      /*!< (@ 0x0000058B) SD Command Register 2                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[31:24] or Response Data[31:24].                            */
    } sd_cmd2_b;
  } ;
  
  union {
    __IOM uint8_t sd_cmd3;                      /*!< (@ 0x0000058C) SD Command Register 3                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[23:16] or Response Data[23:16].                            */
    } sd_cmd3_b;
  } ;
  
  union {
    __IOM uint8_t sd_cmd4;                      /*!< (@ 0x0000058D) SD Command Register 4                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[15:8] or Response Data[15:8].                              */
    } sd_cmd4_b;
  } ;
  
  union {
    __IOM uint8_t sd_cmd5;                      /*!< (@ 0x0000058E) SD Command Register 5                                      */
    
    struct {
      __IOM uint8_t cmd         : 8;            /*!< [7..0] Command[7:0] or Response Data[7:0].                                */
    } sd_cmd5_b;
  } ;
  
  union {
    __IOM uint8_t sd_byte_cnt_l;                /*!< (@ 0x0000058F) Byte Count Register (Low Byte)                             */
    
    struct {
      __IOM uint8_t byte_cnt_l  : 8;            /*!< [7..0] Byte Count[7:0]. Byte count in one block transferred
                                                     from/to SD card.                                                          */
    } sd_byte_cnt_l_b;
  } ;
  
  union {
    __IOM uint8_t sd_byte_cnt_h;                /*!< (@ 0x00000590) Byte Count Register (High Byte)                            */
    
    struct {
      __IOM uint8_t byte_cnt_h  : 3;            /*!< [2..0] Byte Count[10:8]. Byte count in one block transferred
                                                     from/to SD card.                                                          */
            uint8_t             : 5;
    } sd_byte_cnt_h_b;
  } ;
  
  union {
    __IOM uint8_t sd_blk_cnt_l;                 /*!< (@ 0x00000591) Block Count Register (Low Byte)                            */
    
    struct {
      __IOM uint8_t blk_cnt_l   : 8;            /*!< [7..0] Block Count[7:0]. Block count transferred from/to SD
                                                     card.                                                                     */
    } sd_blk_cnt_l_b;
  } ;
  
  union {
    __IOM uint8_t sd_blk_cnt_h;                 /*!< (@ 0x00000592) Block Count Register (High Byte)                           */
    
    struct {
      __IOM uint8_t blk_cnt_h   : 7;            /*!< [6..0] Block Count[14:8]. Byte count transferred from/to SD
                                                     card.                                                                     */
            uint8_t             : 1;
    } sd_blk_cnt_h_b;
  } ;
  
  union {
    __IOM uint8_t sd_xfer;                      /*!< (@ 0x00000593) SD Transfer Control Register                               */
    
    struct {
      __IOM uint8_t cmd_code    : 4;            /*!< [3..0] Command Code. These bits encoded each working mode of
                                                     SD card control module.0000(NORMAL_WRITE): Write 1 or 2
                                                     bytes to SD card and the content are put into SD_CMD2 &
                                                     SD_CMD3 in advance. Hardware ignores write error returned
                                                     from SD card in this case.0001(AUTO_WRITE3): Hardware writes
                                                     data from Ring buffer to SD card and the data length is
                                                     (SD_BYTE_CNT * SD_BLOCK_CNT). Hardware can only write even
                                                     bytes (2, 4, 6, ..., 512) data from SRAM2 buffer to SD
                                                     card if data source is consigned to SRAM2 buffer in                       */
      __IOM uint8_t err         : 1;            /*!< [4..4] If this bit is set which means some error occurs detailed
                                                     error information is in register SD_STAT.                                 */
      __IOM uint8_t idle_ste    : 1;            /*!< [5..5] Status of SD card module state machineWhen this bit is
                                                     set 1, it means that the SD card module state machine is
                                                     in idle state.                                                            */
      __IOM uint8_t end         : 1;            /*!< [6..6] If transfer starts this bit will be clear automatically
                                                     by hardware. And if transfer completes this bit will be
                                                     set and keep 1 until the next Start is set.                               */
      __IOM uint8_t start       : 1;            /*!< [7..7] The transfer is launch if set this bit.                            */
    } sd_xfer_b;
  } ;
  __IM  uint8_t   RESERVED19;
  
  union {
    __IOM uint8_t sd_cmd_ste;                   /*!< (@ 0x00000595) SD Command State Register                                  */
    
    struct {
      __IOM uint8_t cmd_ste     : 4;            /*!< [3..0] CMD State Machine                                                  */
            uint8_t             : 3;
      __IOM uint8_t cmd_ste_is_idle : 1;        /*!< [7..7] CMD State Machine is idleWhen this bit is 1'b1, it indicates
                                                     IDLE state of CMD State Machine                                           */
    } sd_cmd_ste_b;
  } ;
  
  union {
    __IOM uint8_t sd_data_ste;                  /*!< (@ 0x00000596) SD Data State Register                                     */
    
    struct {
      __IOM uint8_t data_ste    : 5;            /*!< [4..0] DATA State Machine                                                 */
            uint8_t             : 2;
      __IOM uint8_t data_ste_is_idle : 1;       /*!< [7..7] DATA State Machine is idleWhen this bit is 1'b1, it indicates
                                                     IDLE state of DATA State Machine                                          */
    } sd_data_ste_b;
  } ;
  __IM  uint8_t   RESERVED20;
} SDMMC_Type;                                   /*!< Size = 1432 (0x598)                                                       */



/* =========================================================================================================================== */
/* ================                                         SDIOHOST                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief SDIO Host - for SDIO card (SDIOHOST)
  */

typedef struct {                                /*!< (@ 0x4005C000) SDIOHOST Structure                                         */
  
  union {
    __IOM uint32_t sdma_system_addr;            /*!< (@ 0x00000000) sdma system address                                        */
    
    struct {
      __IOM uint32_t sdma_system_addr : 32;     /*!< [31..0] sdma system address                                               */
    } sdma_system_addr_b;
  } ;
  __IM  uint32_t  RESERVED[62];
  __IM  uint16_t  RESERVED1;
  
  union {
    __IM  uint16_t HOST_CONTRL_VERSION;         /*!< (@ 0x000000FE) host control version                                       */
    
    struct {
      __IM  uint16_t specification_version : 8; /*!< [7..0] specification version number                                       */
      __IM  uint16_t vendor_version : 8;        /*!< [15..8] vendor version number                                             */
    } HOST_CONTRL_VERSION_b;
  } ;
} SDIOHOST_Type;                                /*!< Size = 256 (0x100)                                                        */



/* =========================================================================================================================== */
/* ================                                           GDMA0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief AXI-Central DMA Controller core that transfer data from a source address to a destination address over AXI bus. (GDMA0)
  */

/* =========================================================================================================================== */
/* ================                                         GDMA0_CH0                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief GDMA control registers for specific channels (GDMA0_CH0)
  */

/* =========================================================================================================================== */
/* ================                                           I2S0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Inter IC Sound (I2S0)
  */

typedef struct {                                /*!< (@ 0x40062000) I2S0 Structure                                             */
  
  union {
    __IOM uint32_t ctrl;                        /*!< (@ 0x00000000) I2S Control Register                                       */
    
    struct {
      __IOM uint32_t iis_en     : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t tx_act     : 2;            /*!< [2..1] RSVD                                                               */
      __IOM uint32_t audio_mono : 2;            /*!< [4..3] RSVD                                                               */
      __IOM uint32_t edge_sw    : 1;            /*!< [5..5] RSVD                                                               */
            uint32_t            : 1;
      __IOM uint32_t loop_back  : 1;            /*!< [7..7] RSVD                                                               */
      __IOM uint32_t format     : 2;            /*!< [9..8] RSVD                                                               */
      __IOM uint32_t lr_swap    : 1;            /*!< [10..10] RSVD                                                             */
      __IOM uint32_t sck_swap   : 1;            /*!< [11..11] RSVD                                                             */
      __IOM uint32_t byte_swap  : 1;            /*!< [12..12] RSVD                                                             */
            uint32_t            : 2;
      __IOM uint32_t debug_switch : 2;          /*!< [16..15] RSVD                                                             */
            uint32_t            : 1;
      __IOM uint32_t burst_size : 5;            /*!< [22..18] RSVD                                                             */
            uint32_t            : 4;
      __IOM uint32_t mute       : 1;            /*!< [27..27] RSVD                                                             */
      __IOM uint32_t slave_mode : 1;            /*!< [28..28] RSVD                                                             */
      __IOM uint32_t wl         : 2;            /*!< [30..29] RSVD                                                             */
      __IOM uint32_t sw_rstn    : 1;            /*!< [31..31] RSVD                                                             */
    } ctrl_b;
  } ;
  
  union {
    __IOM uint32_t page_ptr_tx;                 /*!< (@ 0x00000004) TX Page pointer Register                                   */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t page_ptr_tx : 30;          /*!< [31..2] RSVD                                                              */
    } page_ptr_tx_b;
  } ;
  
  union {
    __IOM uint32_t page_ptr_rx;                 /*!< (@ 0x00000008) RX Page pointer Register                                   */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t page_ptr_rx : 30;          /*!< [31..2] RSVD                                                              */
    } page_ptr_rx_b;
  } ;
  
  union {
    __IOM uint32_t page_size_rate;              /*!< (@ 0x0000000C) Page Size and Sample Rate Register                         */
    
    struct {
      __IOM uint32_t page_size  : 12;           /*!< [11..0] RSVD                                                              */
      __IOM uint32_t page_num   : 2;            /*!< [13..12] RSVD                                                             */
      __IOM uint32_t sr         : 4;            /*!< [17..14] RSVD                                                             */
      __IOM uint32_t clk_switch : 1;            /*!< [18..18] RSVD                                                             */
            uint32_t            : 13;
    } page_size_rate_b;
  } ;
  
  union {
    __IOM uint32_t tx_isr_en;                   /*!< (@ 0x00000010) TX Interrupt Enable Register                               */
    
    struct {
      __IOM uint32_t p0okie_tx  : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t p1okie_tx  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t p2okie_tx  : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t p3okie_tx  : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t page0unava_ie_tx : 1;      /*!< [4..4] RSVD                                                               */
      __IOM uint32_t page1unava_ie_tx : 1;      /*!< [5..5] RSVD                                                               */
      __IOM uint32_t page2unava_ie_tx : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t page3unava_ie_tx : 1;      /*!< [7..7] RSVD                                                               */
      __IOM uint32_t fifo_empty_ie_tx : 1;      /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } tx_isr_en_b;
  } ;
  
  union {
    __IOM uint32_t tx_isr_status;               /*!< (@ 0x00000014) TX Interrupt Status Register                               */
    
    struct {
      __IOM uint32_t p0okip_tx  : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t p1okip_tx  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t p2okip_tx  : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t p3okip_tx  : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t page0unava_ip_tx : 1;      /*!< [4..4] RSVD                                                               */
      __IOM uint32_t page1unava_ip_tx : 1;      /*!< [5..5] RSVD                                                               */
      __IOM uint32_t page2unava_ip_tx : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t page3unava_ip_tx : 1;      /*!< [7..7] RSVD                                                               */
      __IOM uint32_t fifo_empty_ip_tx : 1;      /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } tx_isr_status_b;
  } ;
  
  union {
    __IOM uint32_t rx_isr_en;                   /*!< (@ 0x00000018) RX Interrupt Enable Register                               */
    
    struct {
      __IOM uint32_t p0okie_rx  : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t p1okie_rx  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t p2okie_rx  : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t p3okie_rx  : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t page0unava_ie_rx : 1;      /*!< [4..4] RSVD                                                               */
      __IOM uint32_t page1unava_ie_rx : 1;      /*!< [5..5] RSVD                                                               */
      __IOM uint32_t page2unava_ie_rx : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t page3unava_ie_rx : 1;      /*!< [7..7] RSVD                                                               */
      __IOM uint32_t fifo_full_ie_rx : 1;       /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } rx_isr_en_b;
  } ;
  
  union {
    __IOM uint32_t rx_isr_status;               /*!< (@ 0x0000001C) RX Interrupt Status Register                               */
    
    struct {
      __IOM uint32_t p0okip_rx  : 1;            /*!< [0..0] RSVD                                                               */
      __IOM uint32_t p1okip_rx  : 1;            /*!< [1..1] RSVD                                                               */
      __IOM uint32_t p2okip_rx  : 1;            /*!< [2..2] RSVD                                                               */
      __IOM uint32_t p3okip_rx  : 1;            /*!< [3..3] RSVD                                                               */
      __IOM uint32_t page0unava_ip_rx : 1;      /*!< [4..4] RSVD                                                               */
      __IOM uint32_t page1unava_ip_rx : 1;      /*!< [5..5] RSVD                                                               */
      __IOM uint32_t page2unava_ip_rx : 1;      /*!< [6..6] RSVD                                                               */
      __IOM uint32_t page3unava_ip_rx : 1;      /*!< [7..7] RSVD                                                               */
      __IOM uint32_t fifo_full_ip_rx : 1;       /*!< [8..8] RSVD                                                               */
            uint32_t            : 23;
    } rx_isr_status_b;
  } ;
  
  union {
    __IOM uint32_t tx_page0_own;                /*!< (@ 0x00000020) TX Page0 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p0own_tx   : 1;            /*!< [31..31] RSVD                                                             */
    } tx_page0_own_b;
  } ;
  
  union {
    __IOM uint32_t tx_page1_own;                /*!< (@ 0x00000024) TX Page1 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p1own_tx   : 1;            /*!< [31..31] RSVD                                                             */
    } tx_page1_own_b;
  } ;
  
  union {
    __IOM uint32_t tx_page2_own;                /*!< (@ 0x00000028) TX Page2 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p2own_tx   : 1;            /*!< [31..31] RSVD                                                             */
    } tx_page2_own_b;
  } ;
  
  union {
    __IOM uint32_t tx_page3_own;                /*!< (@ 0x0000002C) TX Page3 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p3own_tx   : 1;            /*!< [31..31] RSVD                                                             */
    } tx_page3_own_b;
  } ;
  
  union {
    __IOM uint32_t rx_page0_own;                /*!< (@ 0x00000030) RX Page0 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p0own_rx   : 1;            /*!< [31..31] RSVD                                                             */
    } rx_page0_own_b;
  } ;
  
  union {
    __IOM uint32_t rx_page1_own;                /*!< (@ 0x00000034) RX Page1 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p1own_rx   : 1;            /*!< [31..31] RSVD                                                             */
    } rx_page1_own_b;
  } ;
  
  union {
    __IOM uint32_t rx_page2_own;                /*!< (@ 0x00000038) RX Page2 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p2own_rx   : 1;            /*!< [31..31] RSVD                                                             */
    } rx_page2_own_b;
  } ;
  
  union {
    __IOM uint32_t rx_page3_own;                /*!< (@ 0x0000003C) RX Page3 Own Bit Register                                  */
    
    struct {
            uint32_t            : 31;
      __IOM uint32_t p3own_rx   : 1;            /*!< [31..31] RSVD                                                             */
    } rx_page3_own_b;
  } ;
  
  union {
    __IM  uint32_t version_id;                  /*!< (@ 0x00000040) Version id                                                 */
    
    struct {
      __IM  uint32_t version_id : 32;           /*!< [31..0] RSVD                                                              */
    } version_id_b;
  } ;
} I2S_Type;                                    /*!< Size = 68 (0x44)                                                          */



/* =========================================================================================================================== */
/* ================                                          CRYPTO                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Crypto in Secure (CRYPTO)
  */

typedef struct {                                /*!< (@ 0x50070000) CRYPTO Structure                                           */
  
  union {
    __IOM uint32_t srcdesc_status_reg;          /*!< (@ 0x00000000) Source Descriptor FIFO status Register                     */
    
    struct {
      __IM  uint32_t fifo_empty_cnt : 8;        /*!< [7..0] Source Descriptor FIFO empty counter                               */
      __IM  uint32_t swptr      : 8;            /*!< [15..8] Source Descriptor FIFO write pointer                              */
      __IM  uint32_t srptr      : 8;            /*!< [23..16] Source Descriptor FIFO read pointer                              */
      __IOM uint32_t src_fail   : 1;            /*!< [24..24] Source Descriptor fail interrupt                                 */
      __IM  uint32_t src_fail_status : 2;       /*!< [26..25] Source Descriptor fail status                                    */
      __IOM uint32_t src_fail_m : 1;            /*!< [27..27] Source Descriptor fail interrupt mask                            */
            uint32_t            : 2;
      __IOM uint32_t pk_up      : 1;            /*!< [30..30] packet base update wptr to engine                                */
      __IOM uint32_t src_rst    : 1;            /*!< [31..31] Source Descriptor reset                                          */
    } srcdesc_status_reg_b;
  } ;
  
  union {
    __IOM uint32_t sdfw_reg;                    /*!< (@ 0x00000004) IPSec Source Descriptor first word                         */
    
    struct {
      __IOM uint32_t sdfw       : 32;           /*!< [31..0] IPSec Source Descriptor first word                                */
    } sdfw_reg_b;
  } ;
  
  union {
    __IOM uint32_t sdsw_reg;                    /*!< (@ 0x00000008) IPSec Source Descriptor second word                        */
    
    struct {
      __IOM uint32_t sdsw       : 32;           /*!< [31..0] IPSec Source Descriptor second word                               */
    } sdsw_reg_b;
  } ;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t ipscsr_reset_isr_conf_reg;   /*!< (@ 0x00000010) IPSec Command/Status Register, for reset / isr
                                                                    poll status                                                */
    
    struct {
      __OM  uint32_t soft_rst   : 1;            /*!< [0..0] Software Resetwrite 1 to reset                                     */
            uint32_t            : 2;
      __IM  uint32_t dma_busy   : 1;            /*!< [3..3] Ipsec dma busy                                                     */
      __IOM uint32_t cmd_ok     : 1;            /*!< [4..4] Command OK interrupt                                               */
            uint32_t            : 2;
      __IOM uint32_t intr_mode  : 1;            /*!< [7..7] Select ok interrupt mode                                           */
      __IM  uint32_t ok_intr_cnt : 8;           /*!< [15..8] OK interrupt counter                                              */
      __IOM uint32_t clear_ok_intr_num : 8;     /*!< [23..16] Clear OK interrupt number                                        */
            uint32_t            : 7;
      __OM  uint32_t ipsec_rst  : 1;            /*!< [31..31] Ipsec engine ResetWrite 1 to reset the crypto engine
                                                     and DMA engine                                                            */
    } ipscsr_reset_isr_conf_reg_b;
  } ;
  
  union {
    __IOM uint32_t ipscsr_int_mask_reg;         /*!< (@ 0x00000014) IPSec Command/Status Register, for interrupt
                                                                    mask                                                       */
    
    struct {
      __IOM uint32_t cmd_ok_m   : 1;            /*!< [0..0] Command OK interrupt Mask1: Mask Enable0: Mask Disable             */
            uint32_t            : 2;
      __IOM uint32_t src_err0_m : 1;            /*!< [3..3] Source Descriptor Error 0 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err1_m : 1;            /*!< [4..4] Source Descriptor Error 1 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err2_m : 1;            /*!< [5..5] Source Descriptor Error 2 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err3_m : 1;            /*!< [6..6] Source Descriptor Error 3 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err4_m : 1;            /*!< [7..7] Source Descriptor Error 4 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err5_m : 1;            /*!< [8..8] Source Descriptor Error 5 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err6_m : 1;            /*!< [9..9] Source Descriptor Error 6 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err7_m : 1;            /*!< [10..10] Source Descriptor Error 7 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err8_m : 1;            /*!< [11..11] Source Descriptor Error 8 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t src_err9_m : 1;            /*!< [12..12] Source Descriptor Error 9 Interrupt Mask1: Mask Enable0:
                                                     Mask Disable                                                              */
      __IOM uint32_t dst_err1_m : 1;            /*!< [13..13] Destination Descriptor Error 1 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
      __IOM uint32_t dst_err2_m : 1;            /*!< [14..14] Destination Descriptor Error 2 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
      __IOM uint32_t dst_err3_m : 1;            /*!< [15..15] Destination Descriptor Error 3 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
      __IOM uint32_t dst_err4_m : 1;            /*!< [16..16] Destination Descriptor Error 4 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
      __IOM uint32_t dst_err5_m : 1;            /*!< [17..17] Destination Descriptor Error 5 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
      __IOM uint32_t dst_err6_m : 1;            /*!< [18..18] Destination Descriptor Error 6 Interrupt Mask1: Mask
                                                     Enable0: Mask Disable                                                     */
            uint32_t            : 13;
    } ipscsr_int_mask_reg_b;
  } ;
  
  union {
    __IOM uint32_t ipscsr_debug_reg;            /*!< (@ 0x00000018) IPSec Command/Status Register, for debug                   */
    
    struct {
      __IOM uint32_t dma_wait_cycle : 16;       /*!< [15..0] wait dma_wait_cycle to assert next dma request                    */
      __IOM uint32_t arbiter_mode : 1;          /*!< [16..16] dma arbiter mode:1'b0 : round-robin1'b1 : detect fifo
                                                     wasted level                                                              */
            uint32_t            : 3;
      __IOM uint32_t debug_port_sel : 4;        /*!< [23..20] Debug port selection:4'd0 : engine_dbg, 4'd1 : dma_lexra_dbg,
                                                     4'd2 : dma_rx_dbg, 4'd3 : dma_tx_dbg                                      */
      __IOM uint32_t engine_clk_en : 1;         /*!< [24..24] Ipsec Engine clock enable                                        */
            uint32_t            : 6;
      __IOM uint32_t debug_wb   : 1;            /*!< [31..31] Debug : write back mode                                          */
    } ipscsr_debug_reg_b;
  } ;
  
  union {
    __IOM uint16_t ipscsr_err_stats_reg;        /*!< (@ 0x0000001C) IPSec Command/Status Register, for error status            */
    
    struct {
      __IOM uint16_t src_err0   : 1;            /*!< [0..0] Source Descriptor Error 0 interruptFirst segment descriptor
                                                     is not set (FS=0), when descriptor is pointing to the first
                                                     segment of the packet. (or) First segment descriptor is
                                                     set (FS=1), when descriptor is polling to the first segment
                                                     of the packet.Write 1 to clear                                            */
      __IOM uint16_t src_err1   : 1;            /*!< [1..1] Source Descriptor Error 1 interruptLast segment descriptor
                                                     is not set (LS=1), when descriptor is pointing to the first
                                                     segment of the packet. Write 1 to clear                                   */
      __IOM uint16_t src_err2   : 1;            /*!< [2..2] Source Descriptor Error 2 interrupt1. Source Descriptor
                                                     Starting Address error(SDSA[1:0]!=2'd0)2. memory protection
                                                     eventWrite 1 to clear                                                     */
      __IOM uint16_t src_err3   : 1;            /*!< [3..3] Source Descriptor Error 3 interruptLength error : 1.
                                                     first descriptor & (CL!=3)2. ((CL=0)&(kl==0)&(il==0)&(pl==0)&(shil==0)Wri
                                                     e 1 to clear                                                              */
      __IOM uint16_t src_err4   : 1;            /*!< [4..4] Source Descriptor Error 4 interruptSource Data Buffer
                                                     Pointer error(SDDB[1:0]!=2'd0)Write 1 to clear                            */
      __IOM uint16_t src_err5   : 1;            /*!< [5..5] Source Descriptor Error 5 interruptData length = a2eo(epl)
                                                     + enl + apl = 0Write 1 to clear                                           */
      __IOM uint16_t src_err6   : 1;            /*!< [6..6] Source Descriptor Error 6 interruptSum(a2eo)!=header
                                                     total lengthWrite 1 to clear                                              */
      __IOM uint16_t src_err7   : 1;            /*!< [7..7] Source Descriptor Error 7 interruptSum(enl)!=encryption
                                                     total lengthWrite 1 to clear                                              */
      __IOM uint16_t src_err8   : 1;            /*!< [8..8] Source Descriptor Error 8 interruptSum(apl)!=hash padding
                                                     total lengthWrite 1 to clear                                              */
      __IOM uint16_t src_err9   : 1;            /*!< [9..9] Source Descriptor Error 9 interruptSum(enl)!=encryption
                                                     padding total lengthWrite 1 to clear                                      */
      __IOM uint16_t des_err1   : 1;            /*!< [10..10] Destination Descriptor Error 1 interrupt1. Destination
                                                     Descriptor Starting Address error(DDSA[1:0]!=2'd0)2. memory
                                                     protection errorWrite 1 to clear                                          */
      __IOM uint16_t des_err2   : 1;            /*!< [11..11] Destination Descriptor Error 2 interrupt(ENC=1'b1),
                                                     when only active hash engineWrite 1 to clear                              */
      __IOM uint16_t des_err3   : 1;            /*!< [12..12] Destination Descriptor Error 2 interrupt(ENC=1'b0),
                                                     when only active encryption engine Write 1 to clear                       */
      __IOM uint16_t des_err4   : 1;            /*!< [13..13] Destination Descriptor Error 4 interrupt1. (enl_sum
                                                     > enc_len)2. (enl==0) & (apl==0)Write 1 to clear                          */
      __IOM uint16_t des_err5   : 1;            /*!< [14..14] Destination Descriptor Error 5 interrupt1. md5: adl>162.
                                                     sha1: adl>203. sha224: adl>284. sha256: adl>325. sha384:
                                                     adl>486. sha512: adl>64Write 1 to clear                                   */
      __IOM uint16_t des_err6   : 1;            /*!< [15..15] Destination Descriptor Error 6 interruptwhen set sequential
                                                     hash1. md5: adl!=162. sha1: adl!=203. sha224/256: adl!=324.
                                                     sha384/512: adl!=64Write 1 to clear                                       */
    } ipscsr_err_stats_reg_b;
  } ;
  __IM  uint16_t  RESERVED1;
  __IM  uint32_t  RESERVED2[4];
  
  union {
    __IOM uint32_t ipscsr_swap_burst_reg;       /*!< (@ 0x00000030) IPSec Command/Status Register, for swap / burst
                                                                    numbers                                                    */
    
    struct {
      __IOM uint32_t set_swap   : 1;            /*!< [0..0] Byte swap for command setting data1: Enable0: Disable              */
      __IOM uint32_t key_iv_swap : 1;           /*!< [1..1] Byte swap for key and iv1: Enable0: Disable                        */
      __IOM uint32_t key_pad_swap : 1;          /*!< [2..2] Byte swap for hmac key1: Enable0: Disable                          */
      __IOM uint32_t hash_inital_value_swap : 1;/*!< [3..3] Byte swap for sequential hash initial value1: Enable0:
                                                     Disable                                                                   */
      __IOM uint32_t dma_in_little_endian : 1;  /*!< [4..4] Input data is little endian1: little endian0: big endian           */
            uint32_t            : 3;
      __IOM uint32_t tx_byte_swap : 1;          /*!< [8..8] Byte swap for dma_tx engine input data1: Enable0: Disable          */
      __IOM uint32_t data_out_little_endian : 1;/*!< [9..9] Output data is little endian1: little endian0: big endian          */
      __IOM uint32_t mac_out_little_endian : 1; /*!< [10..10] Output mac is little endian1: little endian0: big endian         */
      __IOM uint32_t rx_wd_swap : 1;            /*!< [11..11] Word swap for dma_rx engine input data1: Enable0: Disable        */
      __IOM uint32_t tx_wd_swap : 1;            /*!< [12..12] Word swap for dma_tx engine input data1: Enable0: Disable        */
            uint32_t            : 3;
      __IOM uint32_t dma_burst_length : 6;      /*!< [21..16] dma burst lengthMax : 32 Min: 1                                  */
            uint32_t            : 10;
    } ipscsr_swap_burst_reg_b;
  } ;
  __IM  uint32_t  RESERVED3[51];
  
  union {
    __OM  uint32_t crc_rst_reg;                 /*!< (@ 0x00000100) crc reset                                                  */
    
    struct {
      __OM  uint32_t rst        : 1;            /*!< [0..0] reset CRC engine                                                   */
            uint32_t            : 31;
    } crc_rst_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_op_reg;                  /*!< (@ 0x00000104) crc operation                                              */
    
    struct {
      __IOM uint32_t crc_iswap  : 3;            /*!< [2..0] swap input data                                                    */
      __IOM uint32_t crc_oswap  : 1;            /*!< [3..3] swap output data                                                   */
      __IOM uint32_t crc_sel    : 3;            /*!< [6..4] crc sel                                                            */
      __IOM uint32_t crc_dma    : 1;            /*!< [7..7] DMA mode                                                           */
      __IOM uint32_t crc_be     : 2;            /*!< [9..8] big endian                                                         */
            uint32_t            : 2;
      __IOM uint32_t crc_last   : 1;            /*!< [12..12] crc last                                                         */
            uint32_t            : 3;
      __IOM uint32_t crc_length : 16;           /*!< [31..16] length                                                           */
    } crc_op_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_poly_reg;                /*!< (@ 0x00000108) CRC polynomia register                                     */
    
    struct {
      __IOM uint32_t crc_poly   : 32;           /*!< [31..0] crc polynomial coefficients                                       */
    } crc_poly_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_iv_reg;                  /*!< (@ 0x0000010C) CRC initial value register                                 */
    
    struct {
      __IOM uint32_t crc_init   : 32;           /*!< [31..0] crc init value                                                    */
    } crc_iv_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_oxor_reg;                /*!< (@ 0x00000110) CRC initial value register                                 */
    
    struct {
      __IOM uint32_t crc_oxor   : 32;           /*!< [31..0] if output xor mode                                                */
    } crc_oxor_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_data_reg;                /*!< (@ 0x00000114) CRC data register                                          */
    
    struct {
      __IOM uint32_t crc_data   : 32;           /*!< [31..0] din - Command mode : DMA==1'b0SDBP - Source Data Buffer
                                                     Pointer : DMA==1'b1                                                       */
    } crc_data_reg_b;
  } ;
  
  union {
    __IOM uint32_t crc_stat_reg;                /*!< (@ 0x00000118) CRC status register                                        */
    
    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] still busy in previous execution                                   */
      __IOM uint32_t crc_ok     : 1;            /*!< [1..1] finish execution                                                   */
      __IOM uint32_t crc_intr_mask : 1;         /*!< [2..2] interrupt mask                                                     */
      __OM  uint32_t crc_little_endian : 1;     /*!< [3..3] little endian                                                      */
            uint32_t            : 28;
    } crc_stat_reg_b;
  } ;
  
  union {
    __IM  uint32_t crc_result_reg;              /*!< (@ 0x0000011C) CRC result register                                        */
    
    struct {
      __IM  uint32_t crc_out    : 32;           /*!< [31..0] output result                                                     */
    } crc_result_reg_b;
  } ;
  
  union {
    __IM  uint32_t crc_count_reg;               /*!< (@ 0x00000120) CRC count register                                         */
    
    struct {
      __IM  uint32_t crc_cnt    : 16;           /*!< [15..0] count number in bytes                                             */
            uint32_t            : 16;
    } crc_count_reg_b;
  } ;
  __IM  uint32_t  RESERVED4[951];
  
  union {
    __IOM uint32_t dstdesc_status_reg;          /*!< (@ 0x00001000) destination descriptor status                              */
    
    struct {
      __IM  uint32_t fifo_empty_cnt : 8;        /*!< [7..0] Destination Descriptor FIFO empty counter                          */
      __IM  uint32_t dwptr      : 8;            /*!< [15..8] Destination Descriptor FIFO write pointer                         */
      __IM  uint32_t drptr      : 8;            /*!< [23..16] Destination Descriptor FIFO read pointer                         */
      __IOM uint32_t dst_fail   : 1;            /*!< [24..24] Destination Descriptor fail interrupt                            */
      __IM  uint32_t dst_fail_status : 2;       /*!< [26..25] Destination Descriptor fail status                               */
      __IOM uint32_t dst_fail_m : 1;            /*!< [27..27] Destination Descriptor fail interrupt mask                       */
            uint32_t            : 3;
      __IOM uint32_t dst_rst    : 1;            /*!< [31..31] Destination Descriptor reset                                     */
    } dstdesc_status_reg_b;
  } ;
  
  union {
    __IOM uint32_t ddfw_reg;                    /*!< (@ 0x00001004) destination descriptor first word                          */
    
    struct {
      __IOM uint32_t ddfw       : 32;           /*!< [31..0] IPSec Destination Descriptor first word                           */
    } ddfw_reg_b;
  } ;
  
  union {
    __IOM uint32_t ddsw_reg;                    /*!< (@ 0x00001008) destination descriptor second word                         */
    
    struct {
      __IOM uint32_t ddsw       : 32;           /*!< [31..0] IPSec Destination Descriptor second word                          */
    } ddsw_reg_b;
  } ;
  
  union {
    __IOM uint32_t desc_pkt_conf_reg;           /*!< (@ 0x0000100C) descriptor packet setting                                  */
    
    struct {
      __IOM uint32_t dbg_sptr   : 8;            /*!< [7..0] Source Descriptor FIFO empty counter                               */
      __IOM uint32_t dbg_dptr   : 8;            /*!< [15..8] Destination Descriptor FIFO write pointer                         */
      __IM  uint32_t pk_arbiter : 2;            /*!< [17..16] Packet arbiter 2'd0 : bus1, 2'd1 : bus2, 2'd2 : bus3             */
            uint32_t            : 6;
      __IOM uint32_t bus1_priority_th : 2;      /*!< [25..24] Bus1 priority threshold                                          */
      __IOM uint32_t bus2_priority_th : 2;      /*!< [27..26] Bus2 priority threshold                                          */
      __IOM uint32_t bus3_priority_th : 2;      /*!< [29..28] Bus3 priority threshold                                          */
      __IOM uint32_t pk_arbiter_mode : 2;       /*!< [31..30] Packet arbiter mode                                              */
    } desc_pkt_conf_reg_b;
  } ;
} CRYPTO_Type;                                  /*!< Size = 4112 (0x1010)                                                      */



/* =========================================================================================================================== */
/* ================                                           EDDSA                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief EdDSA offload engine (EDDSA)
  */

typedef struct {                                /*!< (@ 0x40046800) EDDSA Structure                                            */
  
  union {
    __IOM uint32_t eng_init_reg;                /*!< (@ 0x00000000) EdDSA Engine Initial Setting Register                      */
    
    struct {
      __IOM uint32_t eng_rst    : 1;            /*!< [0..0] Engine synchronize reset                                           */
            uint32_t            : 7;
      __IOM uint32_t swptr      : 1;            /*!< [8..8] eng_clk_enable                                                     */
            uint32_t            : 23;
    } eng_init_reg_b;
  } ;
  __IOM uint32_t  eng_resv0_reg;                /*!< (@ 0x00000004) EdDSA Engine reserved0 Register                            */
  
  union {
    __IOM uint32_t eng_conf_int_reg;            /*!< (@ 0x00000008) EdDSA Engine Configure Interrupt Register                  */
    
    struct {
      __IOM uint32_t eng_start  : 1;            /*!< [0..0] Start for EdDSA function. It's almost for all EdDSA function,
                                                     except some auto-flow settings. When programer set this
                                                     bit to 1'b1, it means that input values of the engine mode
                                                     are ready, so engine can process the mode. Usually it won't
                                                     be set with HASH_OK.                                                      */
            uint32_t            : 1;
      __IOM uint32_t hash_ok    : 1;            /*!< [2..2] When Hash digest input value is ready, put hask_ok to
                                                     high.Only use this bit in some auto-flow setting. When
                                                     programer set this bit to 1'b1, it means that hash digest
                                                     input value is ready, engine can contiune processing next
                                                     auto-flow step.                                                           */
            uint32_t            : 1;
      __IM  uint32_t eng_idle   : 1;            /*!< [4..4] When engine is busy, this bit will be put high.                    */
            uint32_t            : 3;
      __IOM uint32_t mode0_finish : 1;          /*!< [8..8] Engine mode0 interrupt. Put high to clear mode0 interrupt.         */
      __IOM uint32_t mode1_finish : 1;          /*!< [9..9] Engine mode1 interrupt. Put high to clear mode1 interrupt.         */
      __IOM uint32_t mode2_finish : 1;          /*!< [10..10] Engine mode2 interrupt. Put high to clear mode2 interrupt.       */
      __IOM uint32_t mode3_finish : 1;          /*!< [11..11] Engine mode3 interrupt. Put high to clear mode3 interrupt.       */
      __IOM uint32_t eng_decode_fail : 1;       /*!< [12..12] Engine decode fail interrupt. Put high to clear fail
                                                     interrupt.                                                                */
            uint32_t            : 19;
    } eng_conf_int_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_ctrl_reg;                /*!< (@ 0x0000000C) EdDSA Engine Contol Register                               */
    
    struct {
      __IOM uint32_t mod_sel    : 2;            /*!< [1..0] EdDSA engine mode select.2'd0 : mode02'd1 : mode12'd2
                                                     : mode22'd3 : mode3                                                       */
      __IOM uint32_t fun_sel    : 2;            /*!< [3..2] EdDSA engine function select.2'd0 : Decode point/ add
                                                     point/ sub mod [It depends on bit ecover_x_en and bit ap_en.]2'd1
                                                     : Div mod2'd2 : Add mod2'd3 : Mult mod/ Hash mod #modular1/
                                                     Hash mod #modular2 [It depends on bit h512_en and bit mod_q]              */
      __IOM uint32_t ap_en      : 1;            /*!< [4..4] Add point enable control. It is only used in mode3.1:
                                                     enable0: disable                                                          */
      __IOM uint32_t auto_sp    : 1;            /*!< [5..5] Auto-flow step enable control. Basically, it is used
                                                     to open one pass flow in mode0/mode1 flow. It won't be
                                                     set in mode2/ mode3.                                                      */
      __IOM uint32_t byp_h512   : 1;            /*!< [6..6] SHA512 hash bypass mode control.1: Bypass SHA5120: Without
                                                     bypass SHA512                                                             */
      __IOM uint32_t h512_en    : 1;            /*!< [7..7] SHA512 hash enable control.1: enable using sha5120: disable
                                                     using sha512                                                              */
      __IOM uint32_t mod_q      : 1;            /*!< [8..8] Select modular1 or 2 for Hash mod. Ref. Function Step
                                                     chapter.#modular1 : hash[511:0] modular (2^255 - 19)#modular2
                                                     : hash[511:0] modular (2^252+ 27742317777372353535851937790883648493)     */
      __IOM uint32_t sub_point  : 1;            /*!< [9..9] Point subtraction enable control in mode2.                         */
      __IOM uint32_t recover_x_en : 1;          /*!< [10..10] Reocver(decode) point enable contrl. When this bit
                                                     is set to 1'b1, it means that enable decoding mode.                       */
      __IOM uint32_t eng_decode_fail_mask : 1;  /*!< [11..11] Mask decoding fail interrupt.                                    */
      __IOM uint32_t mode0_f_mask : 1;          /*!< [12..12] Mask mode0 finish interrupt.                                     */
      __IOM uint32_t mode1_f_mask : 1;          /*!< [13..13] Mask mode1 finish interrupt.                                     */
      __IOM uint32_t mode2_f_mask : 1;          /*!< [14..14] Mask mode2 finish interrupt.                                     */
      __IOM uint32_t mode3_f_mask : 1;          /*!< [15..15] Mask mode3 finish interrupt.                                     */
      __IOM uint32_t x1_byte_swap : 1;          /*!< [16..16] x1 byte swap enable control.                                     */
      __IOM uint32_t x1_word_swap : 1;          /*!< [17..17] x1 word swap enable control.                                     */
      __IOM uint32_t y1_byte_swap : 1;          /*!< [18..18] y1 byte swap enable control.                                     */
      __IOM uint32_t y1_word_swap : 1;          /*!< [19..19] y1 word swap enable control.                                     */
      __IOM uint32_t x2_byte_swap : 1;          /*!< [20..20] x2 byte swap enable control.                                     */
      __IOM uint32_t x2_word_swap : 1;          /*!< [21..21] x2 word swap enable control.                                     */
      __IOM uint32_t y2_byte_swap : 1;          /*!< [22..22] y2 byte swap enable control.                                     */
      __IOM uint32_t y2_word_swap : 1;          /*!< [23..23] y2 word swap enable control.                                     */
      __IOM uint32_t xo1_byte_swap : 1;         /*!< [24..24] xo1 byte swap enable control.                                    */
      __IOM uint32_t xo1_word_swap : 1;         /*!< [25..25] xo1 word swap enable control.                                    */
      __IOM uint32_t yo1_byte_swap : 1;         /*!< [26..26] yo1 byte swap enable control.                                    */
      __IOM uint32_t yo1_word_swap : 1;         /*!< [27..27] yo1 word swap enable control.                                    */
      __IOM uint32_t xo2_byte_swap : 1;         /*!< [28..28] xo2 byte swap enable control.                                    */
      __IOM uint32_t xo2_word_swap : 1;         /*!< [29..29] xo2 word swap enable control.                                    */
      __IOM uint32_t yo2_byte_swap : 1;         /*!< [30..30] yo2 byte swap enable control.                                    */
      __IOM uint32_t yo2_word_swap : 1;         /*!< [31..31] yo2 word swap enable control.                                    */
    } eng_ctrl_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p0_reg;               /*!< (@ 0x00000010) EdDSA Engine X1 Point [31:0] Registers                     */
    
    struct {
      __IOM uint32_t eng_x1_p0  : 32;           /*!< [31..0] X1 value [31:0] of an input point.                                */
    } eng_x1_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p1_reg;               /*!< (@ 0x00000014) EdDSA Engine X1 Point [63:32] Registers                    */
    
    struct {
      __IOM uint32_t eng_x1_p1  : 32;           /*!< [31..0] X1 value [63:32] of a input point.                                */
    } eng_x1_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p2_reg;               /*!< (@ 0x00000018) EdDSA Engine X1 Point [95:64] Registers                    */
    
    struct {
      __IOM uint32_t eng_x1_p2  : 32;           /*!< [31..0] X1 value [95:64] of an input point.                               */
    } eng_x1_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p3_reg;               /*!< (@ 0x0000001C) EdDSA Engine X1 Point [127:96] Registers                   */
    
    struct {
      __IOM uint32_t eng_x1_p3  : 32;           /*!< [31..0] X1 value [127:96] of a input point.                               */
    } eng_x1_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p4_reg;               /*!< (@ 0x00000020) EdDSA Engine X1 Point [159:128] Registers                  */
    
    struct {
      __IOM uint32_t eng_x1_p4  : 32;           /*!< [31..0] X1 value [159:128] of an input point.                             */
    } eng_x1_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p5_reg;               /*!< (@ 0x00000024) EdDSA Engine X1 Point [191:160] Registers                  */
    
    struct {
      __IOM uint32_t eng_x1_p5  : 32;           /*!< [31..0] X1 value [191:160] of a input point.                              */
    } eng_x1_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p6_reg;               /*!< (@ 0x00000028) EdDSA Engine X1 Point [223:192] Registers                  */
    
    struct {
      __IOM uint32_t eng_x1_p6  : 32;           /*!< [31..0] X1 value [223:192] of an input point.                             */
    } eng_x1_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x1_p7_reg;               /*!< (@ 0x0000002C) EdDSA Engine X1 Point [255:224] Registers                  */
    
    struct {
      __IOM uint32_t eng_x1_p7  : 32;           /*!< [31..0] X1 value [255:224] of a input point.                              */
    } eng_x1_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p0_reg;               /*!< (@ 0x00000030) EdDSA Engine Y1 Point [31:0] Registers                     */
    
    struct {
      __IOM uint32_t eng_y1_p0  : 32;           /*!< [31..0] Y1 value [31:0] of an input point.                                */
    } eng_y1_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p1_reg;               /*!< (@ 0x00000034) EdDSA Engine Y1 Point [63:32] Registers                    */
    
    struct {
      __IOM uint32_t eng_y1_p1  : 32;           /*!< [31..0] Y1 value [63:32] of a input point.                                */
    } eng_y1_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p2_reg;               /*!< (@ 0x00000038) EdDSA Engine Y1 Point [95:64] Registers                    */
    
    struct {
      __IOM uint32_t eng_y1_p2  : 32;           /*!< [31..0] Y1 value [95:64] of an input point.                               */
    } eng_y1_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p3_reg;               /*!< (@ 0x0000003C) EdDSA Engine Y1 Point [127:96] Registers                   */
    
    struct {
      __IOM uint32_t eng_y1_p3  : 32;           /*!< [31..0] Y1 value [127:96] of a input point.                               */
    } eng_y1_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p4_reg;               /*!< (@ 0x00000040) EdDSA Engine Y1 Point [159:128] Registers                  */
    
    struct {
      __IOM uint32_t eng_y1_p4  : 32;           /*!< [31..0] Y1 value [159:128] of an input point.                             */
    } eng_y1_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p5_reg;               /*!< (@ 0x00000044) EdDSA Engine Y1 Point [191:160] Registers                  */
    
    struct {
      __IOM uint32_t eng_y1_p5  : 32;           /*!< [31..0] Y1 value [191:160] of a input point.                              */
    } eng_y1_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p6_reg;               /*!< (@ 0x00000048) EdDSA Engine Y1 Point [223:192] Registers                  */
    
    struct {
      __IOM uint32_t eng_y1_p6  : 32;           /*!< [31..0] Y1 value [223:192] of an input point.                             */
    } eng_y1_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y1_p7_reg;               /*!< (@ 0x0000004C) EdDSA Engine Y1 Point [255:224] Registers                  */
    
    struct {
      __IOM uint32_t eng_y1_p7  : 32;           /*!< [31..0] Y1 value [255:224] of a input point.                              */
    } eng_y1_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p0_reg;               /*!< (@ 0x00000050) EdDSA Engine X2 Point [31:0] Registers                     */
    
    struct {
      __IOM uint32_t eng_x2_p0  : 32;           /*!< [31..0] X2 value [31:0] of an input point.                                */
    } eng_x2_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p1_reg;               /*!< (@ 0x00000054) EdDSA Engine X2 Point [63:32] Registers                    */
    
    struct {
      __IOM uint32_t eng_x2_p1  : 32;           /*!< [31..0] X2 value [63:32] of a input point.                                */
    } eng_x2_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p2_reg;               /*!< (@ 0x00000058) EdDSA Engine X2 Point [95:64] Registers                    */
    
    struct {
      __IOM uint32_t eng_x2_p2  : 32;           /*!< [31..0] X2 value [95:64] of an input point.                               */
    } eng_x2_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p3_reg;               /*!< (@ 0x0000005C) EdDSA Engine X2 Point [127:96] Registers                   */
    
    struct {
      __IOM uint32_t eng_x2_p3  : 32;           /*!< [31..0] X2 value [127:96] of a input point.                               */
    } eng_x2_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p4_reg;               /*!< (@ 0x00000060) EdDSA Engine X2 Point [159:128] Registers                  */
    
    struct {
      __IOM uint32_t eng_x2_p4  : 32;           /*!< [31..0] X2 value [159:128] of an input point.                             */
    } eng_x2_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p5_reg;               /*!< (@ 0x00000064) EdDSA Engine X2 Point [191:160] Registers                  */
    
    struct {
      __IOM uint32_t eng_x2_p5  : 32;           /*!< [31..0] X2 value [191:160] of a input point.                              */
    } eng_x2_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p6_reg;               /*!< (@ 0x00000068) EdDSA Engine X2 Point [223:192] Registers                  */
    
    struct {
      __IOM uint32_t eng_x2_p6  : 32;           /*!< [31..0] X2 value [223:192] of an input point.                             */
    } eng_x2_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_x2_p7_reg;               /*!< (@ 0x0000006C) EdDSA Engine X2 Point [255:224] Registers                  */
    
    struct {
      __IOM uint32_t eng_x2_p7  : 32;           /*!< [31..0] X2 value [255:224] of a input point.                              */
    } eng_x2_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p0_reg;               /*!< (@ 0x00000070) EdDSA Engine Y2 Point [31:0] Registers                     */
    
    struct {
      __IOM uint32_t eng_y2_p0  : 32;           /*!< [31..0] Y2 value [31:0] of an input point.                                */
    } eng_y2_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p1_reg;               /*!< (@ 0x00000074) EdDSA Engine Y2 Point [63:32] Registers                    */
    
    struct {
      __IOM uint32_t eng_y2_p1  : 32;           /*!< [31..0] Y2 value [63:32] of a input point.                                */
    } eng_y2_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p2_reg;               /*!< (@ 0x00000078) EdDSA Engine Y2 Point [95:64] Registers                    */
    
    struct {
      __IOM uint32_t eng_y2_p2  : 32;           /*!< [31..0] Y2 value [95:64] of an input point.                               */
    } eng_y2_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p3_reg;               /*!< (@ 0x0000007C) EdDSA Engine Y2 Point [127:96] Registers                   */
    
    struct {
      __IOM uint32_t eng_y2_p3  : 32;           /*!< [31..0] Y2 value [127:96] of a input point.                               */
    } eng_y2_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p4_reg;               /*!< (@ 0x00000080) EdDSA Engine Y2 Point [159:128] Registers                  */
    
    struct {
      __IOM uint32_t eng_y2_p4  : 32;           /*!< [31..0] Y2 value [159:128] of an input point.                             */
    } eng_y2_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p5_reg;               /*!< (@ 0x00000084) EdDSA Engine Y2 Point [191:160] Registers                  */
    
    struct {
      __IOM uint32_t eng_y2_p5  : 32;           /*!< [31..0] Y2 value [191:160] of a input point.                              */
    } eng_y2_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p6_reg;               /*!< (@ 0x00000088) EdDSA Engine Y2 Point [223:192] Registers                  */
    
    struct {
      __IOM uint32_t eng_y2_p6  : 32;           /*!< [31..0] Y2 value [223:192] of an input point.                             */
    } eng_y2_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_y2_p7_reg;               /*!< (@ 0x0000008C) EdDSA Engine Y2 Point [255:224] Registers                  */
    
    struct {
      __IOM uint32_t eng_y2_p7  : 32;           /*!< [31..0] Y2 value [255:224] of a input point.                              */
    } eng_y2_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p0_reg;              /*!< (@ 0x00000090) EdDSA Engine X1 Output Point [31:0] Registers              */
    
    struct {
      __IOM uint32_t eng_xo1_p0 : 32;           /*!< [31..0] X1 value [31:0] of an output point.                               */
    } eng_xo1_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p1_reg;              /*!< (@ 0x00000094) EdDSA Engine X1 Output Point [63:32] Registers             */
    
    struct {
      __IOM uint32_t eng_xo1_p1 : 32;           /*!< [31..0] X1 value [63:32] of a output point.                               */
    } eng_xo1_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p2_reg;              /*!< (@ 0x00000098) EdDSA Engine X1 Output Point [95:64] Registers             */
    
    struct {
      __IOM uint32_t eng_xo1_p2 : 32;           /*!< [31..0] X1 value [95:64] of an output point.                              */
    } eng_xo1_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p3_reg;              /*!< (@ 0x0000009C) EdDSA Engine X1 Output Point [127:96] Registers            */
    
    struct {
      __IOM uint32_t eng_xo1_p3 : 32;           /*!< [31..0] X1 value [127:96] of a output point.                              */
    } eng_xo1_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p4_reg;              /*!< (@ 0x000000A0) EdDSA Engine X1 Output Point [159:128] Registers           */
    
    struct {
      __IOM uint32_t eng_xo1_p4 : 32;           /*!< [31..0] X1 value [159:128] of an output point.                            */
    } eng_xo1_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p5_reg;              /*!< (@ 0x000000A4) EdDSA Engine X1 Ouput Point [191:160] Registers            */
    
    struct {
      __IOM uint32_t eng_xo1_p5 : 32;           /*!< [31..0] X1 value [191:160] of a output point.                             */
    } eng_xo1_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p6_reg;              /*!< (@ 0x000000A8) EdDSA Engine X1 Output Point [223:192] Registers           */
    
    struct {
      __IOM uint32_t eng_xo1_p6 : 32;           /*!< [31..0] X1 value [223:192] of an output point.                            */
    } eng_xo1_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo1_p7_reg;              /*!< (@ 0x000000AC) EdDSA Engine X1 Output Point [255:224] Registers           */
    
    struct {
      __IOM uint32_t eng_xo1_p7 : 32;           /*!< [31..0] X1 value [255:224] of a output point.                             */
    } eng_xo1_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p0_reg;              /*!< (@ 0x000000B0) EdDSA Engine Y1 Output Point [31:0] Registers              */
    
    struct {
      __IOM uint32_t eng_yo1_p0 : 32;           /*!< [31..0] Y1 value [31:0] of an output point.                               */
    } eng_yo1_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p1_reg;              /*!< (@ 0x000000B4) EdDSA Engine Y1 Output Point [63:32] Registers             */
    
    struct {
      __IOM uint32_t eng_yo1_p1 : 32;           /*!< [31..0] Y1 value [63:32] of a output point.                               */
    } eng_yo1_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p2_reg;              /*!< (@ 0x000000B8) EdDSA Engine Y1 Output Point [95:64] Registers             */
    
    struct {
      __IOM uint32_t eng_yo1_p2 : 32;           /*!< [31..0] Y1 value [95:64] of an output point.                              */
    } eng_yo1_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p3_reg;              /*!< (@ 0x000000BC) EdDSA Engine Y1 Output Point [127:96] Registers            */
    
    struct {
      __IOM uint32_t eng_yo1_p3 : 32;           /*!< [31..0] Y1 value [127:96] of a output point.                              */
    } eng_yo1_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p4_reg;              /*!< (@ 0x000000C0) EdDSA Engine Y1 Output Point [159:128] Registers           */
    
    struct {
      __IOM uint32_t eng_yo1_p4 : 32;           /*!< [31..0] Y1 value [159:128] of an output point.                            */
    } eng_yo1_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p5_reg;              /*!< (@ 0x000000C4) EdDSA Engine Y1 Ouput Point [191:160] Registers            */
    
    struct {
      __IOM uint32_t eng_yo1_p5 : 32;           /*!< [31..0] Y1 value [191:160] of a output point.                             */
    } eng_yo1_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p6_reg;              /*!< (@ 0x000000C8) EdDSA Engine Y1 Output Point [223:192] Registers           */
    
    struct {
      __IOM uint32_t eng_yo1_p6 : 32;           /*!< [31..0] Y1 value [223:192] of an output point.                            */
    } eng_yo1_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo1_p7_reg;              /*!< (@ 0x000000CC) EdDSA Engine Y1 Output Point [255:224] Registers           */
    
    struct {
      __IOM uint32_t eng_yo1_p7 : 32;           /*!< [31..0] Y1 value [255:224] of a output point.                             */
    } eng_yo1_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p0_reg;              /*!< (@ 0x000000D0) EdDSA Engine X2 Output Point [31:0] Registers              */
    
    struct {
      __IOM uint32_t eng_xo2_p0 : 32;           /*!< [31..0] X2 value [31:0] of an output point.                               */
    } eng_xo2_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p1_reg;              /*!< (@ 0x000000D4) EdDSA Engine X2 Output Point [63:32] Registers             */
    
    struct {
      __IOM uint32_t eng_xo2_p1 : 32;           /*!< [31..0] X2 value [63:32] of a output point.                               */
    } eng_xo2_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p2_reg;              /*!< (@ 0x000000D8) EdDSA Engine X2 Output Point [95:64] Registers             */
    
    struct {
      __IOM uint32_t eng_xo2_p2 : 32;           /*!< [31..0] X2 value [95:64] of an output point.                              */
    } eng_xo2_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p3_reg;              /*!< (@ 0x000000DC) EdDSA Engine X2 Output Point [127:96] Registers            */
    
    struct {
      __IOM uint32_t eng_xo2_p3 : 32;           /*!< [31..0] X2 value [127:96] of a output point.                              */
    } eng_xo2_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p4_reg;              /*!< (@ 0x000000E0) EdDSA Engine X2 Output Point [159:128] Registers           */
    
    struct {
      __IOM uint32_t eng_xo2_p4 : 32;           /*!< [31..0] X2 value [159:128] of an output point.                            */
    } eng_xo2_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p5_reg;              /*!< (@ 0x000000E4) EdDSA Engine X2 Ouput Point [191:160] Registers            */
    
    struct {
      __IOM uint32_t eng_xo2_p5 : 32;           /*!< [31..0] X2 value [191:160] of a output point.                             */
    } eng_xo2_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p6_reg;              /*!< (@ 0x000000E8) EdDSA Engine X2 Output Point [223:192] Registers           */
    
    struct {
      __IOM uint32_t eng_xo2_p6 : 32;           /*!< [31..0] X2 value [223:192] of an output point.                            */
    } eng_xo2_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_xo2_p7_reg;              /*!< (@ 0x000000EC) EdDSA Engine X2 Output Point [255:224] Registers           */
    
    struct {
      __IOM uint32_t eng_xo2_p7 : 32;           /*!< [31..0] X2 value [255:224] of a output point.                             */
    } eng_xo2_p7_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p0_reg;              /*!< (@ 0x000000F0) EdDSA Engine Y2 Output Point [31:0] Registers              */
    
    struct {
      __IOM uint32_t eng_yo2_p0 : 32;           /*!< [31..0] Y2 value [31:0] of an output point.                               */
    } eng_yo2_p0_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p1_reg;              /*!< (@ 0x000000F4) EdDSA Engine Y2 Output Point [63:32] Registers             */
    
    struct {
      __IOM uint32_t eng_yo2_p1 : 32;           /*!< [31..0] Y2 value [63:32] of a output point.                               */
    } eng_yo2_p1_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p2_reg;              /*!< (@ 0x000000F8) EdDSA Engine Y2 Output Point [95:64] Registers             */
    
    struct {
      __IOM uint32_t eng_yo2_p2 : 32;           /*!< [31..0] Y2 value [95:64] of an output point.                              */
    } eng_yo2_p2_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p3_reg;              /*!< (@ 0x000000FC) EdDSA Engine Y2 Output Point [127:96] Registers            */
    
    struct {
      __IOM uint32_t eng_yo2_p3 : 32;           /*!< [31..0] Y2 value [127:96] of a output point.                              */
    } eng_yo2_p3_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p4_reg;              /*!< (@ 0x00000100) EdDSA Engine Y2 Output Point [159:128] Registers           */
    
    struct {
      __IOM uint32_t eng_yo2_p4 : 32;           /*!< [31..0] Y2 value [159:128] of an output point.                            */
    } eng_yo2_p4_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p5_reg;              /*!< (@ 0x00000104) EdDSA Engine Y2 Ouput Point [191:160] Registers            */
    
    struct {
      __IOM uint32_t eng_yo2_p5 : 32;           /*!< [31..0] Y2 value [191:160] of a output point.                             */
    } eng_yo2_p5_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p6_reg;              /*!< (@ 0x00000108) EdDSA Engine Y2 Output Point [223:192] Registers           */
    
    struct {
      __IOM uint32_t eng_yo2_p6 : 32;           /*!< [31..0] Y2 value [223:192] of an output point.                            */
    } eng_yo2_p6_reg_b;
  } ;
  
  union {
    __IOM uint32_t eng_yo2_p7_reg;              /*!< (@ 0x0000010C) EdDSA Engine Y2 Output Point [255:224] Registers           */
    
    struct {
      __IOM uint32_t eng_yo2_p7 : 32;           /*!< [31..0] Y2 value [255:224] of a output point.                             */
    } eng_yo2_p7_reg_b;
  } ;
  __IM  uint32_t  RESERVED[60];
  
  union {
    __IM  uint32_t eng_dbg_output_reg;          /*!< (@ 0x00000200) EdDSA Engine Debug Output Register                         */
    
    struct {
      __IM  uint32_t dbg_add_2_inv_2_finish : 1;/*!< [0..0] inv module finish signal in add_2 module                           */
      __IM  uint32_t dbg_add_2_inv_1_finish : 1;/*!< [1..1] inv module finish signal in add_2 module                           */
      __IM  uint32_t dbg_add_2_mul_2_finish : 1;/*!< [2..2] mul finish signal in add_2 module                                  */
      __IM  uint32_t dbg_add_2_mul_1_finish : 1;/*!< [3..3] mul finish signal in add_2 module                                  */
      __IM  uint32_t dbg_add_2_curr_state : 4;  /*!< [7..4] fsm signal in add_2 module                                         */
      __IM  uint32_t dbg_add_1_inv_2_finish : 1;/*!< [8..8] inv module finish signal in add_1 module                           */
      __IM  uint32_t dbg_add_1_inv_1_finish : 1;/*!< [9..9] inv module finish signal in add_1 module                           */
      __IM  uint32_t dbg_add_1_mul_2_finish : 1;/*!< [10..10] mul finish signal in add_1 module                                */
      __IM  uint32_t dbg_add_1_mul_1_finish : 1;/*!< [11..11] mul finish signal in add_1 module                                */
      __IM  uint32_t dbg_add_1_curr_state : 4;  /*!< [15..12] fsm signal in add_1module                                        */
      __IM  uint32_t dbg_add_2_finish : 1;      /*!< [16..16] finish signal in add_2 module                                    */
      __IM  uint32_t dbg_add_1_finish : 1;      /*!< [17..17] finish signal in add_1 module                                    */
      __IM  uint32_t dbg_curr_state : 4;        /*!< [21..18] fsm signal in top module                                         */
      __IM  uint32_t dbg_func_curr_state : 4;   /*!< [25..22] function fsm signal in top module                                */
      __IM  uint32_t dbg_eng_finish : 1;        /*!< [26..26] fsm signal in top module                                         */
      __IM  uint32_t dbg_reg_eng_rst : 1;       /*!< [27..27] reset signal in top module                                       */
      __IM  uint32_t dbg_decomp_curr_state : 4; /*!< [31..28] fsm signal in decoding module                                    */
    } eng_dbg_output_reg_b;
  } ;
} EDDSA_Type;                                   /*!< Size = 516 (0x204)                                                        */



/* =========================================================================================================================== */
/* ================                                           WLAN                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Wireless LAN (WLAN)
  */
/* =========================================================================================================================== */
/* ================                                           TRNG                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief TRNG real random number generator
  */

typedef struct {                                /*!< (@ 0x4000A400) RTC Structure                                              */
  
  union {
    __IOM uint32_t cmd;                         /*!< (@ 0x00000000) REG_AON_LSFIF_CMD                                          */
    
    struct {
      __IOM uint32_t lsfif_ad   : 16;           /*!< [15..0] BIT_AON_LSFIF_AD[15:8]=8'h00: RTC register base address           */
            uint32_t            : 8;
      __IOM uint32_t lsfif_we   : 4;            /*!< [27..24] LSF register byte write enable. This field is valid
                                                     during LSF register write transfer, and is ignored during
                                                     LSF register read transfer                                                */
      __IOM uint32_t lsfif_wr   : 1;            /*!< [28..28] LSF register write transfer indicator. 1: LSF register
                                                     write transfer, 0: LSF register read transfer                             */
            uint32_t            : 2;
      __IOM uint32_t lsfif_poll : 1;            /*!< [31..31] Set this bit to do LSF register read or write transfer
                                                     depend on BIT_AON_LSFIF_WR. When transfer done, this bit
                                                     will be clear by HW                                                       */
    } cmd_b;
  } ;
  
  union {
    __IOM uint32_t lsfif_rwd;                   /*!< (@ 0x00000004) REG_AON_LSFIF_RWD                                          */
    
    struct {
      __IOM uint32_t lsfif_rwd  : 32;           /*!< [31..0] LSF(low speed function) write                                     */
    } lsfif_rwd_b;
  } ;
  
  union {
    __IOM uint32_t imr;                         /*!< (@ 0x00000008) REG_AON_RTC_IMR                                            */
    
    struct {
      __IOM uint32_t cnt_sec_imr : 1;           /*!< [0..0] Interrupt mask of RTC seconds counter                              */
      __IOM uint32_t cnt_min_imr : 1;           /*!< [1..1] Interrupt mask of RTC minutes counter                              */
      __IOM uint32_t cnt_hrs_imr : 1;           /*!< [2..2] Interrupt mask of RTC hours counter                                */
      __IOM uint32_t cnt_dow_imr : 1;           /*!< [3..3] Interrupt mask of RTC day of week counter                          */
      __IOM uint32_t cnt_dom_imr : 1;           /*!< [4..4] Interrupt mask of RTC day of month counter                         */
      __IOM uint32_t cnt_mth_imr : 1;           /*!< [5..5] Interrupt mask of RTC month counter                                */
      __IOM uint32_t cnt_yrs_imr : 1;           /*!< [6..6] Interrupt mask of RTC years counter                                */
      __IOM uint32_t cnt_doy_imr : 1;           /*!< [7..7] Interrupt mask of RTC day of year counter                          */
      __IOM uint32_t alrm_sec_imr : 1;          /*!< [8..8] Interrupt mask of RTC second alarm                                 */
      __IOM uint32_t alrm_min_imr : 1;          /*!< [9..9] Interrupt mask of RTC minute alarm                                 */
      __IOM uint32_t alrm_hrs_imr : 1;          /*!< [10..10] Interrupt mask of RTC hour alarm                                 */
      __IOM uint32_t alrm_dow_imr : 1;          /*!< [11..11] Interrupt mask of RTC day of week alarm                          */
      __IOM uint32_t alrm_dom_imr : 1;          /*!< [12..12] Interrupt mask of RTC day of month alarm                         */
      __IOM uint32_t alrm_mth_imr : 1;          /*!< [13..13] Interrupt mask of RTC month alarm                                */
      __IOM uint32_t alrm_yrs_imr : 1;          /*!< [14..14] Interrupt mask of RTC year alarm                                 */
      __IOM uint32_t alrm_doy_imr : 1;          /*!< [15..15] Interrupt mask of RTC day of year alarm                          */
      __IOM uint32_t alrm_imr   : 1;            /*!< [16..16] Interrupt mask of RTC alarm                                      */
            uint32_t            : 15;
    } imr_b;
  } ;
  
  union {
    __IOM uint32_t isr;                         /*!< (@ 0x0000000C) REG_AON_RTC_ISR                                            */
    
    struct {
      __IOM uint32_t cnt_sec_isr : 1;           /*!< [0..0] Indicate increment of the second timer                             */
      __IOM uint32_t cnt_min_isr : 1;           /*!< [1..1] Indicate increment of the minute timer                             */
      __IOM uint32_t cnt_hrs_isr : 1;           /*!< [2..2] Indicate increment of the hour timer                               */
      __IOM uint32_t cnt_dow_isr : 1;           /*!< [3..3] Indicate increment of the day-of-week timer                        */
      __IOM uint32_t cnt_dom_isr : 1;           /*!< [4..4] Indicate increment of the day-of-month timer                       */
      __IOM uint32_t cnt_mth_isr : 1;           /*!< [5..5] Indicate increment of the month timer                              */
      __IOM uint32_t cnt_yrs_isr : 1;           /*!< [6..6] Indicate increment of the year timer                               */
      __IOM uint32_t cnt_doy_isr : 1;           /*!< [7..7] Indicate increment of the Day-of-year timer                        */
      __IOM uint32_t alrm_sec_isr : 1;          /*!< [8..8] Indicate Second timer value match ALRM_SEC                         */
      __IOM uint32_t alrm_min_isr : 1;          /*!< [9..9] Indicate Minute timer value match ALRM_MIN                         */
      __IOM uint32_t alrm_hrs_isr : 1;          /*!< [10..10] Indicate Hour timer value match ALRM_HRS                         */
      __IOM uint32_t alrm_dow_isr : 1;          /*!< [11..11] Indicate DOW timer value match ALRM_DOW                          */
      __IOM uint32_t alrm_dom_isr : 1;          /*!< [12..12] Indicate DOM timer value match ALRM_DOM                          */
      __IOM uint32_t alrm_mth_isr : 1;          /*!< [13..13] Indicate MTH timer value match ALRM_MTH                          */
      __IOM uint32_t alrm_yrs_isr : 1;          /*!< [14..14] Indicate Year timer value match ALRM_YRS                         */
      __IOM uint32_t alrm_doy_isr : 1;          /*!< [15..15] Indicate DOY timer value match ALRM_DOY                          */
      __IOM uint32_t alrm_isr   : 1;            /*!< [16..16] Indicate ALL timer value match ALRM value                        */
            uint32_t            : 15;
    } isr_b;
  } ;
} TRNG_Type;                                     /*!< Size = 16 (0x10)                                                          */




/* =========================================================================================================================== */
/* ================                                            USB                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief USB OTG (USB)
  */

/* =========================================================================================================================== */
/* ================                                           USB_S                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief USB OTG_S (USB_S)
  */

/* =========================================================================================================================== */
/* ================                                            ISP                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief ISP (ISP)
  */

/* =========================================================================================================================== */
/* ================                                            VOE                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Video Offload Engine (VOE)
  */

/* =========================================================================================================================== */
/* ================                                          H265Enc                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief H.265 Encoder Engine (H265Enc)
  */

/* =========================================================================================================================== */
/* ================                                            AON                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PON Control Register (AON)
  */

/* =========================================================================================================================== */
/* ================                                            PON                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PON Control Register (PON)
  */

/* =========================================================================================================================== */
/* ================                                           VNDR                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief VNDR Control Register (VNDR)
  */

/* =========================================================================================================================== */
/* ================                                          VNDR_S                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief VNDR_S Control Register (VNDR_S)
  */

/* =========================================================================================================================== */
/* ================                                            NN                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief Nual Network Engine (NN)
  */

/* =========================================================================================================================== */
/* ================                                           DDR2                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief DDR2 Controller (DDR2)
  */

/* =========================================================================================================================== */
/* ================                                           ECDSA                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief ECDSA offload engine (ECDSA)
  */

/* =========================================================================================================================== */
/* ================                                         FLASH_SEC                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief Flash SEC engine (FLASH_SEC)
  */

/* =========================================================================================================================== */
/* ================                                            RSA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief RSA (RSA)
  */

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define SYSON_BASE                  0x40000000UL
#define SYSON_S_BASE                0x50000800UL
#define GPIO_BASE                   0x40001000UL
#define GPIO_S_BASE                 0x50001000UL
#define COMP_BASE                   0x4000AC00UL
#define COMP_S_BASE                 0x5000AC00UL
#define TG0_BASE                    0x40002000UL
#define TG0_S_BASE                  0x50002000UL
#define TM0_BASE                    0x40002040UL
#define TM0_S_BASE                  0x50002040UL
#define TM1_BASE                    0x40002080UL
#define TM1_S_BASE                  0x50002080UL
#define TM2_BASE                    0x400020C0UL
#define TM2_S_BASE                  0x500020C0UL
#define TM3_BASE                    0x40002100UL
#define TM3_S_BASE                  0x50002100UL
#define TM4_BASE                    0x40002140UL
#define TM4_S_BASE                  0x50002140UL
#define TM5_BASE                    0x40002180UL
#define TM5_S_BASE                  0x50002180UL
#define TM6_BASE                    0x400021C0UL
#define TM6_S_BASE                  0x500021C0UL
#define TM7_BASE                    0x40002200UL
#define TM7_S_BASE                  0x50002200UL
#define TG1_BASE                    0x4000B400UL
#define TG1_S_BASE                  0x5000B400UL
#define TM8_BASE                    0x4000B440UL
#define TM8_S_BASE                  0x5000B440UL
#define TG2_BASE                    0x4000B800UL
#define TG2_S_BASE                  0x5000B800UL
#define TM9_BASE                    0x4000B840UL
#define TM9_S_BASE                  0x5000B840UL
#define TM10_BASE                   0x4000B880UL
#define TM10_S_BASE                 0x5000B880UL
#define TM11_BASE                   0x4000B8C0UL
#define TM11_S_BASE                 0x5000B8C0UL
#define TM12_BASE                   0x4000B900UL
#define TM12_S_BASE                 0x5000B900UL
#define TM13_BASE                   0x4000B940UL
#define TM13_S_BASE                 0x5000B940UL
#define TM14_BASE                   0x4000B980UL
#define TM14_S_BASE                 0x5000B980UL
#define TM15_BASE                   0x4000B9C0UL
#define TM15_S_BASE                 0x5000B9C0UL
#define TM16_BASE                   0x4000BA00UL
#define TM16_S_BASE                 0x5000BA00UL
#define TG3_BASE                    0x4000BC00UL
#define TG3_S_BASE                  0x5000BC00UL
#define TM17_BASE                   0x4000BC40UL
#define TM17_S_BASE                 0x5000BC40UL
#define RTC_BASE                    0x4000A400UL
#define RTC_S_BASE                  0x5000A400UL
#define PWM_COMM_BASE               0x40045000UL
#define PWM_COMM_S_BASE             0x50045000UL
#define PWM0_BASE                   0x40045020UL
#define PWM0_S_BASE                 0x50045020UL
#define PWM1_BASE                   0x40045040UL
#define PWM1_S_BASE                 0x50045040UL
#define PWM2_BASE                   0x40045060UL
#define PWM2_S_BASE                 0x50045060UL
#define PWM3_BASE                   0x40045080UL
#define PWM3_S_BASE                 0x50045080UL
#define PWM4_BASE                   0x400450A0UL
#define PWM4_S_BASE                 0x500450A0UL
#define PWM5_BASE                   0x400450C0UL
#define PWM5_S_BASE                 0x500450C0UL
#define PWM6_BASE                   0x400450E0UL
#define PWM6_S_BASE                 0x500450E0UL
#define PWM7_BASE                   0x40045100UL
#define PWM7_S_BASE                 0x50045100UL
#define PWM8_BASE                   0x40045120UL
#define PWM8_S_BASE                 0x50045120UL
#define PWM9_BASE                   0x40045140UL
#define PWM9_S_BASE                 0x50045140UL
#define PWM10_BASE                  0x40045160UL
#define PWM10_S_BASE                0x50045160UL
#define PWM11_BASE                  0x40045180UL
#define PWM11_S_BASE                0x50045180UL
#define SPIC_BASE                   0x40006000UL
#define SPIC_S_BASE                 0x50006000UL
#define SNAFC_BASE                  0x4005D000UL
#define SNAFC_S_BASE                0x5005D000UL
#define ADC_BASE                    0x40010000UL
#define ADC_S_BASE                  0x50010000UL
#define UART0_BASE                  0x40040000UL
#define UART0_S_BASE                0x50040000UL
#define UART1_BASE                  0x40040400UL
#define UART1_S_BASE                0x50040400UL
#define UART2_BASE                  0x40040800UL
#define UART2_S_BASE                0x50040800UL
#define UART3_BASE                  0x40040C00UL
#define UART3_S_BASE                0x50040C00UL
#define UART4_BASE                  0x40041000UL
#define UART4_S_BASE                0x50041000UL
#define SSI0_BASE                   0x40042800UL
#define SSI0_S_BASE                 0x50042800UL
#define SSI1_BASE                   0x40042C00UL
#define SSI1_S_BASE                 0x50042C00UL
#define SSI2_BASE                   0x40074000UL
#define SSI2_S_BASE                 0x50074000UL
#define SSI3_BASE                   0x40074400UL
#define SSI3_S_BASE                 0x50074400UL
#define I2C0_BASE                   0x40044000UL
#define I2C0_S_BASE                 0x50044000UL
#define I2C1_BASE                   0x40044400UL
#define I2C1_S_BASE                 0x50044400UL
#define I2C2_BASE                   0x40003400UL
#define I2C2_S_BASE                 0x50003400UL
#define I2C3_BASE                   0x40044C00UL
#define I2C3_S_BASE                 0x50044C00UL
#define SI_BASE                     0x40013000UL
#define SPORT_BASE                  0x40066000UL
#define SPORT_S_BASE                0x50066000UL
#define SGPIO_BASE                  0x40046000UL
#define SGPIO_S_BASE                0x50046000UL
#define ETHERNET_BASE               0x40054000UL
#define ETHERNET_S_BASE             0x50054000UL
#define SDMMC_BASE                  0x40058000UL
#define SDMMC_S_BASE                0x50058000UL
#define SDIOHOST_BASE               0x4005C000UL
#define SDIOHOST_S_BASE             0x5005C000UL
#define GDMA0_BASE                  0x400612C0UL
#define SGDMA0_BASE                 0x500612C0UL
#define GDMA0_CH0_BASE              0x40061000UL
#define SGDMA0_CH0_BASE             0x50061000UL
#define GDMA0_CH1_BASE              0x40061058UL
#define SGDMA0_CH1_BASE             0x50061058UL
#define GDMA0_CH2_BASE              0x400610B0UL
#define SGDMA0_CH2_BASE             0x500610B0UL
#define GDMA0_CH3_BASE              0x40061108UL
#define SGDMA0_CH3_BASE             0x50061108UL
#define GDMA0_CH4_BASE              0x40061160UL
#define SGDMA0_CH4_BASE             0x50061160UL
#define GDMA0_CH5_BASE              0x400611B8UL
#define SGDMA0_CH5_BASE             0x500611B8UL
#define GDMA1_BASE                  0x400602C0UL
#define SGDMA1_BASE                 0x500602C0UL
#define GDMA1_CH0_BASE              0x40060000UL
#define SGDMA1_CH0_BASE             0x50060000UL
#define GDMA1_CH1_BASE              0x40060058UL
#define SGDMA1_CH1_BASE             0x50060058UL
#define GDMA1_CH2_BASE              0x400600B0UL
#define SGDMA1_CH2_BASE             0x500600B0UL
#define GDMA1_CH3_BASE              0x40060108UL
#define SGDMA1_CH3_BASE             0x50060108UL
#define GDMA1_CH4_BASE              0x40060160UL
#define SGDMA1_CH4_BASE             0x50060160UL
#define GDMA1_CH5_BASE              0x400601B8UL
#define SGDMA1_CH5_BASE             0x500601B8UL
#define I2S0_BASE                   0x40062000UL
#define I2S0_S_BASE                 0x50062000UL
#define I2S1_BASE                   0x40063000UL
#define I2S1_S_BASE                 0x50063000UL
#define CRYPTO_BASE                 0x50070000UL
#define CRYPTO_NS_BASE              0x40070000UL
#define EDDSA_BASE                  0x40046800UL
#define EDDSA_S_BASE                0x50046800UL
#define WLAN_BASE                   0x40080000UL
#define USB_BASE                    0x400C0000UL
#define USB_S_BASE                  0x500C0000UL
#define ISP_BASE                    0x40300000UL
#define VOE_BASE                    0x40492000UL
#define H265Enc_BASE                0x40500000UL
#define AON_BASE                    0x40009000UL
#define PON_BASE                    0x40009800UL
#define VNDR_BASE                   0x40002800UL
#define VNDR_S_BASE                 0x50002C00UL
#define NN_BASE                     0x40580000UL
#define DDR2_BASE                   0x40601000UL
#define ECDSA_BASE                  0x40046400UL
#define ECDSA_S_BASE                0x50046400UL
#define FLASH_SEC_BASE              0x5000B600UL
#define RSA_BASE                    0x40067F00UL
#define RSA_S_BASE                  0x50067F00UL
#define TRNG_BASE                   0x4000B000UL


/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define SYSON                       ((SYSON_TypeDef*)             SYSON_BASE)
#define SYSON_S                     ((SYSON_S_TypeDef*)           SYSON_S_BASE)
#define GPIO                        ((GPIO_TypeDef*)              GPIO_BASE)
#define GPIO_S                      ((GPIO_TypeDef*)              GPIO_S_BASE)
#define COMP                        ((COMP_TypeDef*)              COMP_BASE)
#define COMP_S                      ((COMP_TypeDef*)              COMP_S_BASE)
#define TG0                         ((TG_TypeDef*)               TG0_BASE)
#define TG0_S                       ((TG_TypeDef*)               TG0_S_BASE)
#define TM0                         ((TM_TypeDef*)               TM0_BASE)
#define TM0_S                       ((TM_TypeDef*)               TM0_S_BASE)
#define TM1                         ((TM_TypeDef*)               TM1_BASE)
#define TM1_S                       ((TM_TypeDef*)               TM1_S_BASE)
#define TM2                         ((TM_TypeDef*)               TM2_BASE)
#define TM2_S                       ((TM_TypeDef*)               TM2_S_BASE)
#define TM3                         ((TM_TypeDef*)               TM3_BASE)
#define TM3_S                       ((TM_TypeDef*)               TM3_S_BASE)
#define TM4                         ((TM_TypeDef*)               TM4_BASE)
#define TM4_S                       ((TM_TypeDef*)               TM4_S_BASE)
#define TM5                         ((TM_TypeDef*)               TM5_BASE)
#define TM5_S                       ((TM_TypeDef*)               TM5_S_BASE)
#define TM6                         ((TM_TypeDef*)               TM6_BASE)
#define TM6_S                       ((TM_TypeDef*)               TM6_S_BASE)
#define TM7                         ((TM_TypeDef*)               TM7_BASE)
#define TM7_S                       ((TM_TypeDef*)               TM7_S_BASE)
#define TG1                         ((TG_TypeDef*)               TG1_BASE)
#define TG1_S                       ((TG_TypeDef*)               TG1_S_BASE)
#define TM8                         ((TM_TypeDef*)               TM8_BASE)
#define TM8_S                       ((TM_TypeDef*)               TM8_S_BASE)
#define TG2                         ((TG_TypeDef*)               TG2_BASE)
#define TG2_S                       ((TG_TypeDef*)               TG2_S_BASE)
#define TM9                         ((TM_TypeDef*)               TM9_BASE)
#define TM9_S                       ((TM_TypeDef*)               TM9_S_BASE)
#define TM10                        ((TM_TypeDef*)               TM10_BASE)
#define TM10_S                      ((TM_TypeDef*)               TM10_S_BASE)
#define TM11                        ((TM_TypeDef*)               TM11_BASE)
#define TM11_S                      ((TM_TypeDef*)               TM11_S_BASE)
#define TM12                        ((TM_TypeDef*)               TM12_BASE)
#define TM12_S                      ((TM_TypeDef*)               TM12_S_BASE)
#define TM13                        ((TM_TypeDef*)               TM13_BASE)
#define TM13_S                      ((TM_TypeDef*)               TM13_S_BASE)
#define TM14                        ((TM_TypeDef*)               TM14_BASE)
#define TM14_S                      ((TM_TypeDef*)               TM14_S_BASE)
#define TM15                        ((TM_TypeDef*)               TM15_BASE)
#define TM15_S                      ((TM_TypeDef*)               TM15_S_BASE)
#define TM16                        ((TM_TypeDef*)               TM16_BASE)
#define TM16_S                      ((TM_TypeDef*)               TM16_S_BASE)
#define TG3                         ((TG_TypeDef*)               TG3_BASE)
#define TG3_S                       ((TG_TypeDef*)               TG3_S_BASE)
#define TM17                        ((TM_TypeDef*)               TM17_BASE)
#define TM17_S                      ((TM_TypeDef*)               TM17_S_BASE)
#define RTC                         ((RTC_TypeDef*)               RTC_BASE)
#define RTC_S                       ((RTC_TypeDef*)               RTC_S_BASE)
#define PWM_COMM                    ((PWM_COMM_TypeDef*)          PWM_COMM_BASE)
#define PWM_COMM_S                  ((PWM_COMM_TypeDef*)          PWM_COMM_S_BASE)
#define PWM0                        ((PWM_TypeDef*)              PWM0_BASE)
#define PWM0_S                      ((PWM_TypeDef*)              PWM0_S_BASE)
#define PWM1                        ((PWM_TypeDef*)              PWM1_BASE)
#define PWM1_S                      ((PWM_TypeDef*)              PWM1_S_BASE)
#define PWM2                        ((PWM_TypeDef*)              PWM2_BASE)
#define PWM2_S                      ((PWM_TypeDef*)              PWM2_S_BASE)
#define PWM3                        ((PWM_TypeDef*)              PWM3_BASE)
#define PWM3_S                      ((PWM_TypeDef*)              PWM3_S_BASE)
#define PWM4                        ((PWM_TypeDef*)              PWM4_BASE)
#define PWM4_S                      ((PWM_TypeDef*)              PWM4_S_BASE)
#define PWM5                        ((PWM_TypeDef*)              PWM5_BASE)
#define PWM5_S                      ((PWM_TypeDef*)              PWM5_S_BASE)
#define PWM6                        ((PWM_TypeDef*)              PWM6_BASE)
#define PWM6_S                      ((PWM_TypeDef*)              PWM6_S_BASE)
#define PWM7                        ((PWM_TypeDef*)              PWM7_BASE)
#define PWM7_S                      ((PWM_TypeDef*)              PWM7_S_BASE)
#define PWM8                        ((PWM_TypeDef*)              PWM8_BASE)
#define PWM8_S                      ((PWM_TypeDef*)              PWM8_S_BASE)
#define PWM9                        ((PWM_TypeDef*)              PWM9_BASE)
#define PWM9_S                      ((PWM_TypeDef*)              PWM9_S_BASE)
#define PWM10                       ((PWM_TypeDef*)              PWM10_BASE)
#define PWM10_S                     ((PWM_TypeDef*)              PWM10_S_BASE)
#define PWM11                       ((PWM_TypeDef*)              PWM11_BASE)
#define PWM11_S                     ((PWM_TypeDef*)              PWM11_S_BASE)
#define SPIC                        ((SPIC_TypeDef*)              SPIC_BASE)
#define SPIC_S                      ((SPIC_TypeDef*)              SPIC_S_BASE)
#define SNAFC                       ((SNAFC_TypeDef*)             SNAFC_BASE)
#define SNAFC_S                     ((SNAFC_TypeDef*)             SNAFC_S_BASE)
#define ADC                         ((ADC_TypeDef*)               ADC_BASE)
#define ADC_S                       ((ADC_TypeDef*)               ADC_S_BASE)
#define UART0                       ((UART_TypeDef*)             UART0_BASE)
#define UART0_S                     ((UART_TypeDef*)             UART0_S_BASE)
#define UART1                       ((UART_TypeDef*)             UART1_BASE)
#define UART1_S                     ((UART_TypeDef*)             UART1_S_BASE)
#define UART2                       ((UART_TypeDef*)             UART2_BASE)
#define UART2_S                     ((UART_TypeDef*)             UART2_S_BASE)
#define UART3                       ((UART_TypeDef*)             UART3_BASE)
#define UART3_S                     ((UART_TypeDef*)             UART3_S_BASE)
#define UART4                       ((UART_TypeDef*)             UART4_BASE)
#define UART4_S                     ((UART_TypeDef*)             UART4_S_BASE)
#define SSI0                        ((SSI_TypeDef*)              SSI0_BASE)
#define SSI0_S                      ((SSI_TypeDef*)              SSI0_S_BASE)
#define SSI1                        ((SSI_TypeDef*)              SSI1_BASE)
#define SSI1_S                      ((SSI_TypeDef*)              SSI1_S_BASE)
#define SSI2                        ((SSI_TypeDef*)              SSI2_BASE)
#define SSI2_S                      ((SSI_TypeDef*)              SSI2_S_BASE)
#define SSI3                        ((SSI_TypeDef*)              SSI3_BASE)
#define SSI3_S                      ((SSI_TypeDef*)              SSI3_S_BASE)
#define I2C0                        ((I2C_TypeDef*)              I2C0_BASE)
#define I2C0_S                      ((I2C_TypeDef*)              I2C0_S_BASE)
#define I2C1                        ((I2C_TypeDef*)              I2C1_BASE)
#define I2C1_S                      ((I2C_TypeDef*)              I2C1_S_BASE)
#define I2C2                        ((I2C_TypeDef*)              I2C2_BASE)
#define I2C2_S                      ((I2C_TypeDef*)              I2C2_S_BASE)
#define I2C3                        ((I2C_TypeDef*)              I2C3_BASE)
#define I2C3_S                      ((I2C_TypeDef*)              I2C3_S_BASE)
#define SI                          ((SI_TypeDef*)                SI_BASE)
#define SPORT                       ((SPORT_TypeDef*)             SPORT_BASE)
#define SPORT_S                     ((SPORT_TypeDef*)             SPORT_S_BASE)
#define SGPIO                       ((SGPIO_TypeDef*)             SGPIO_BASE)
#define SGPIO_S                     ((SGPIO_TypeDef*)             SGPIO_S_BASE)
#define ETHERNET                    ((ETHERNET_TypeDef*)          ETHERNET_BASE)
#define ETHERNET_S                  ((ETHERNET_TypeDef*)          ETHERNET_S_BASE)
#define SDMMC                       ((SDMMC_TypeDef*)             SDMMC_BASE)
#define SDMMC_S                     ((SDMMC_TypeDef*)             SDMMC_S_BASE)
#define SDIOHOST                    ((SDIOHOST_TypeDef*)          SDIOHOST_BASE)
#define SDIOHOST_S                  ((SDIOHOST_TypeDef*)          SDIOHOST_S_BASE)
#define GDMA0                       ((GDMA_TypeDef*)             GDMA0_BASE)
#define SGDMA0                      ((GDMA_TypeDef*)             SGDMA0_BASE)
#define GDMA0_CH0                   ((GDMA_CH_TypeDef*)         GDMA0_CH0_BASE)
#define SGDMA0_CH0                  ((GDMA_CH_TypeDef*)         SGDMA0_CH0_BASE)
#define GDMA0_CH1                   ((GDMA_CH_TypeDef*)         GDMA0_CH1_BASE)
#define SGDMA0_CH1                  ((GDMA_CH_TypeDef*)         SGDMA0_CH1_BASE)
#define GDMA0_CH2                   ((GDMA_CH_TypeDef*)         GDMA0_CH2_BASE)
#define SGDMA0_CH2                  ((GDMA_CH_TypeDef*)         SGDMA0_CH2_BASE)
#define GDMA0_CH3                   ((GDMA_CH_TypeDef*)         GDMA0_CH3_BASE)
#define SGDMA0_CH3                  ((GDMA_CH_TypeDef*)         SGDMA0_CH3_BASE)
#define GDMA0_CH4                   ((GDMA_CH_TypeDef*)         GDMA0_CH4_BASE)
#define SGDMA0_CH4                  ((GDMA_CH_TypeDef*)         SGDMA0_CH4_BASE)
#define GDMA0_CH5                   ((GDMA_CH_TypeDef*)         GDMA0_CH5_BASE)
#define SGDMA0_CH5                  ((GDMA_CH_TypeDef*)         SGDMA0_CH5_BASE)
#define GDMA1                       ((GDMA_TypeDef*)             GDMA1_BASE)
#define SGDMA1                      ((GDMA_TypeDef*)             SGDMA1_BASE)
#define GDMA1_CH0                   ((GDMA_CH_TypeDef*)         GDMA1_CH0_BASE)
#define SGDMA1_CH0                  ((GDMA_CH_TypeDef*)         SGDMA1_CH0_BASE)
#define GDMA1_CH1                   ((GDMA_CH_TypeDef*)         GDMA1_CH1_BASE)
#define SGDMA1_CH1                  ((GDMA_CH_TypeDef*)         SGDMA1_CH1_BASE)
#define GDMA1_CH2                   ((GDMA_CH_TypeDef*)         GDMA1_CH2_BASE)
#define SGDMA1_CH2                  ((GDMA_CH_TypeDef*)         SGDMA1_CH2_BASE)
#define GDMA1_CH3                   ((GDMA_CH_TypeDef*)         GDMA1_CH3_BASE)
#define SGDMA1_CH3                  ((GDMA_CH_TypeDef*)         SGDMA1_CH3_BASE)
#define GDMA1_CH4                   ((GDMA_CH_TypeDef*)         GDMA1_CH4_BASE)
#define SGDMA1_CH4                  ((GDMA_CH_TypeDef*)         SGDMA1_CH4_BASE)
#define GDMA1_CH5                   ((GDMA_CH_TypeDef*)         GDMA1_CH5_BASE)
#define SGDMA1_CH5                  ((GDMA_CH_TypeDef*)         SGDMA1_CH5_BASE)
#define I2S0                        ((I2S_TypeDef*)              I2S0_BASE)
#define I2S0_S                      ((I2S_TypeDef*)              I2S0_S_BASE)
#define I2S1                        ((I2S_TypeDef*)              I2S1_BASE)
#define I2S1_S                      ((I2S_TypeDef*)              I2S1_S_BASE)
#define CRYPTO                      ((CRYPTO_TypeDef*)            CRYPTO_BASE)
#define CRYPTO_NS                   ((CRYPTO_TypeDef*)            CRYPTO_NS_BASE)
#define EDDSA                       ((EDDSA_TypeDef*)             EDDSA_BASE)
#define EDDSA_S                     ((EDDSA_TypeDef*)             EDDSA_S_BASE)
#define WLAN                        ((WLAN_TypeDef*)              WLAN_BASE)
#define USB                         ((USB_TypeDef*)               USB_BASE)
#define USB_S                       ((USB_S_TypeDef*)             USB_S_BASE)
#define ISP                         ((ISP_TypeDef*)               ISP_BASE)
#define VOE                         ((VOE_TypeDef*)               VOE_BASE)
#define H265Enc                     ((H265Enc_TypeDef*)           H265Enc_BASE)
#define AON                         ((AON_TypeDef*)               AON_BASE)
#define PON                         ((PON_TypeDef*)               PON_BASE)
#define VNDR                        ((VNDR_TypeDef*)              VNDR_BASE)
#define VNDR_S                      ((VNDR_S_TypeDef*)            VNDR_S_BASE)
#define NN                          ((NN_TypeDef*)                NN_BASE)
#define DDR2                        ((DDR2_TypeDef*)              DDR2_BASE)
#define ECDSA                       ((ECDSA_TypeDef*)             ECDSA_BASE)
#define ECDSA_S                     ((ECDSA_TypeDef*)             ECDSA_S_BASE)
#define FLASH_SEC                   ((FLASH_SEC_TypeDef*)         FLASH_SEC_BASE)
#define RSA                         ((RSA_TypeDef*)               RSA_BASE)
#define RSA_S                       ((RSA_TypeDef*)               RSA_S_BASE)
//#define TRNG   						  ((TRNG_TYPE_TypeDef*)        TRNG_BASE )

/** @} */ /* End of group Device_Peripheral_declaration */


/******************************************************************************/
/*          CoreSight and other Peripheral memory map                         */
/******************************************************************************/
/* CoreSight Components */
#define TPIU_BASE                 0xE0040000UL
#define ETM_BASE                  0xE0041000UL
#define CTI_BASE                  0xE0042000UL
#define FPB_BASE                  0xE0002000UL

#define DWT_CTRL_SYNCTAP24        1 << 10
#define DWT_CTRL_SYNCTAP26        2 << 10
#define DWT_CTRL_SYNCTAP28        3 << 10

#define DWT_FUNC_SAMP_PC          0x1
#define DWT_FUNC_SAMP_DATA        0x2
#define DWT_FUNC_SAMP_PC_DATA     0x3
#define DWT_FUNC_PC_WPT           0x4
#define DWT_FUNC_TRIG_PC          0x8
#define DWT_FUNC_TRIG_RD          0x9
#define DWT_FUNC_TRIG_WR          0xA
#define DWT_FUNC_TRIG_RW          0xB

#define DWT_CTRL_POSTPRESET_10    0xA

#define ITM_TER_STIM0             1 << 0
#define ITM_TER_STIM1             1 << 1
#define ITM_TER_STIM2             1 << 2

#define ITM_TCR_TS_GLOBAL_128     0x01 << ITM_TCR_GTSFREQ_Pos
#define ITM_TCR_TS_GLOBAL_8192    0x10 << ITM_TCR_GTSFREQ_Pos
#define ITM_TCR_TS_GLOBAL_ALL     0x11 << ITM_TCR_GTSFREQ_Pos

/* Peripheral and SRAM base address */

//#define SRAM_BASE                 0x20000000UL
//#define PERIPH_BASE               0x40000000UL



/******************************************************************************/
/*                         Declaration                                        */
/******************************************************************************/
#define ETM                       ((ETM_Type     *) ETM_BASE)
#define TPIU                      ((TPIU_Type    *) TPIU_BASE)
#define CTI                       ((CTI_Type     *) CTI_BASE)

#define GPIO0		          ((GPIO_TypeDef *) GPIO0_BASE)
#define GPIO1		          ((GPIO_TypeDef *) GPIO1_BASE)
#define GPIO2		          ((GPIO_TypeDef *) GPIO2_BASE)

#endif
