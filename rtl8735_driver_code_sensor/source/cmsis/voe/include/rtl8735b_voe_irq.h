/**************************************************************************//**
 * @file     rtl8735b_voe_irq.h
 * @brief    CMSIS Device System Header File for the Rtl8735b_voe platform.
 *           Defines the IRQ number for the System interrupts and Peripheral
 *           interrupts.
 * @version  V1.00
 * @date     2020-09-18
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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

#ifndef RTL8735B_VOE_IRQ_H
#define RTL8735B_VOE_IRQ_H


#ifdef __cplusplus
 extern "C" {
#endif
/**
 * @addtogroup rtl8735b_voe_irq IRQ
 * @ingroup rtl8735b_voe
 * @{
 * @brief The IRQ APIs of the VOE platform.
 */
void _default_handler(void);

/**
  \brief  Function type of interrupt handler.
*/
typedef void (*int_vector_t) (void);


/**
  \brief  User application call back function for an interrupt.
*/
typedef void (*irq_handler_t)(void *data);

typedef struct irq_config_s {
    irq_handler_t   irq_fun;
    void            *data;
    int16_t         irq_num;
    uint16_t        priority;
} irq_config_t, *pirq_config_t;


//void hal_vector_irq_en_voe(int irq_num, int priority, irq_handler_t irq_fun);
void hal_vector_irq_en_voe(IRQn_Type irq_num, int priority, irq_handler_t irq_fun);

void hal_vector_irq_dis_voe (irq_config_t *pirq_handle);


 /// Number of interrupt for the system level, it's defined by the ARM Cortex-M CPU.
 #define MAX_SYSTEM_IRQ_NUM                  16
 /// Number of interrupt for peripheral devices on this platform.
 #define MAX_PERIPHERAL_IRQ_NUM              16
 /// Total number of interrupt on this platform.
 #define MAX_VECTOR_TABLE_NUM                (MAX_SYSTEM_IRQ_NUM + MAX_PERIPHERAL_IRQ_NUM)

 /* -------------------------  Interrupt Priority Definition  ------------------------ */
 /**
   \brief  Default interrupt priority for external(peripheral devices) interrupts.
 */
 typedef enum _IRQ_Priority_{
     System_IRQPri					=  1,       /*!< 0  System Interrupt                    */
     ISP_IRQPri						=  5,       /*!< 1  ISP Interrupt                       */
	 TIMER_IRQPri					=  9,       /*!< 2  TIMER Interrupt						*/
     TM2KM_IRQPri  					=  6,      	/*!< 3  TM Notify KMInterrupt               */
	 GPIO_IRQPri  					=  9,      	/*!< 4  GPIO Interrupt						*/
     Encoder_IRQPri                 =  5,       /*!< 5  Encoder Interrupt                   */
	 PWM_IRQPri  					=  9,      	/*!< 6  PWM	Interrupt						*/
     ADC_IRQPri  					=  9,      	/*!< 7  ADC	Interrupt						*/
     ERAC_IRQPri   					=  5,       /*!< 8  ERAC Interrupt						*/
	 UART0_IRQPri					=  9,       /*!< 9	UART0 Interrupt						*/
     I2C3_IRQPri					=  9,       /*!< 10 I2C3 Interrupt						*/
	 GDMA0_IRQPri					=  9,       /*!< 11	GDMA0 Interrupt						*/
	 GDMA1_IRQPri					=  9,       /*!< 12	GDMA1 Interrupt						*/
	 NN_IRQPri					    =  9,       /*!< 13	NN Interrupt						*/
     I2C2_IRQPri					=  9,       /*!< 14	I2C2 Interrupt						*/
	 SCRYPTO_IRQPri					=  9        /*!< 15	SCrypto Interrupt					*/

 } IRQ_Priority;


/** @} */ /* End of group rtl8735b_voe */

#ifdef __cplusplus
}
#endif

#endif //RTL8735B_VOE_IRQ_H


