/**************************************************************************//**
 * @file     voe_uart.h
 * @brief    The HAL related definition and macros for the UART device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2020-03-10
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

#ifndef _RTL_8735B_UART_H_
#define _RTL_8735B_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_voe.h"
#include "rtl8735b_uart_type.h"

/**
 * @addtogroup hs_hal_uart UART
 * @ingroup 8735b_hal
 * @{
 * @brief The UART HAL module of the AmebaProII platform.
 */

/// The number of UART port on this platform
#define MAX_UART_PORT                   4

/**
  \brief  Defines the FIFO size.
*/
enum uart_fifo_size_e {
    Uart_Tx_FIFO_Size   = 16,
    Uart_Rx_FIFO_Size   = 32
};

#define UART_DMA_MBLK_NUM       16      // maximum block number for each DMA transfer, it must <= 16
#define UART_DMA_BLOCK_SIZE     4092    // the block size of multiple block DMA, it cannot over 4095

/**
  \brief  Define the UART port ID.
*/
enum  uart_id_e {
    Uart0             = 0,
    Uart1             = 1,
    Uart2             = 2,
    Uart3             = 3,
    Uart4             = 4,  //BT UART

    MaxUartNum        = MAX_UART_PORT
};
typedef uint8_t uart_id_t;

/// @cond DOXYGEN_ROM_HAL_API

/// the minimum OVSR value for baud rate setting calculation
#define UART_OVSR_POOL_MIN      1000    // 10.0
/// the maximum OVSR value for baud rate setting calculation
#define UART_OVSR_POOL_MAX      2099    //20.9
/// the setp size of the divisor increasing for the baud rate setting calculation
#define DIVISOR_RESOLUTION      10
#define JITTER_LIMIT            100
/// the setp size of the divisor increasing for the baud rate setting calculation
#define UART_SCLK               PLATFORM_SCLK

enum uart_pin_func_type_e {
    UART_Pin_TX         = 0,
    UART_Pin_RX         = 1,
    UART_Pin_RTS        = 2,
    UART_Pin_CTS        = 3
};
typedef uint8_t uart_pin_func_t;

/**
  \brief  Define the level for RX FIFO empty event trigger.
*/
enum uart_rxfifo_trigger_level_e {
    OneByte       = 0x00,
    FourBytes     = 0x01,
    EightBytes    = 0x10,
    FourteenBytes = 0x11
};

/**
  \brief  Defines the hardware auto folw control setting, same as register's definition.
*/
enum uart_flow_ctrl_e {
    AutoFlowCtrlDisable = 0,
    AutoFlowCtrlEnable = 1
};

/**
  \brief  Defines the selection for the bit length of a word, same as register's definition.
*/
enum uart_word_len_sel_e {
    UartWordLen7b = 0,
    UartWordLen8b = 1
};

/**
  \brief  Defines the number of stop bits of a frame, same as register's definition.
*/
enum uart_stop_bits_e {
    UartStopBits_1 = 0,
    UartStopBits_2 = 1,
};

/**
  \brief  Defines the parity checking control, same as register's definition.
*/
enum uart_parity_control_e {
    UartParityDisable = 0,
    UartParityEnable = 1
};

/**
  \brief  Defines the parity checking type.
*/
enum uart_parity_type_e {
    UartParityNone = 0,
    UartParityOdd = 1,
    UartParityEven = 2,
    UartParityForced1 = 3,
    UartParityForced0 = 4
};

/**
  \brief  Defines the stick parity checking control, same as register's definition.
*/
enum uart_stick_parity_control_e {
    UartStickParityDisable = 0,
    UartStickParityEnable = 1
};

/**
  \brief  Defines the interrupt ID, same as register's definition.
*/
enum uart_interrupt_id_e {
    ModemStatus           = 0,
    TxFifoEmpty           = 1,
    ReceiverDataAvailable = 2,
    ReceivLineStatus      = 3,
    TimeoutIndication     = 6
};

/**
  \brief  Defines the RX filter match pattern length, 1 byte or 2 bytes.
*/
enum uart_rx_filter_len_e {
    UartRxFilter1Byte     = 0,
    UartRxFilter2Bytes    = 1
};

/**
  \brief  Defines the RX filter pattern matching mode.
*/
enum uart_rx_filter_op_e {
    UartRxFilter_OpAnd    = 0,
    UartRxFilter_OpOr     = 1,
    UartRxFilter_OpXor    = 2
};

/**
  \brief  Defines the trigger levels of the TX FIFO empty interrupt.
*/
enum _uart_tx_fifo_level_e {
    UartTxFifoLow_4bytes    = 0,
    UartTxFifoLow_8bytes    = 1
};

/**
  \brief  Define the trigger levels of the RX FIFO full interrupt.
*/
enum _uart_rx_fifo_level_e {
    UartRxFifoLev_1byte      = 0,
    UartRxFifoLev_8bytes     = 1,
    UartRxFifoLev_16bytes    = 2,
    UartRxFifoLev_28bytes    = 3
};

/**
  \brief  Defines the UART HAL states.
*/
enum HAL_UART_State_e {
  HAL_UART_STATE_NULL              = 0x00,    ///< UART hardware not been initial yet
  HAL_UART_STATE_TX_BUSY           = 0x01,    ///< UART is buzy on TX
  HAL_UART_STATE_RX_BUSY           = 0x02,    ///< UART is busy on RX
  HAL_UART_STATE_TIMEOUT           = 0x04,    ///< Transfer timeout
  HAL_UART_STATE_DMATX_BUSY        = 0x10,    ///< UART is buzy on DMA TX
  HAL_UART_STATE_DMARX_BUSY        = 0x20,    ///< UART is busy on DMA RX
  HAL_UART_STATE_ERROR             = 0x80     ///< UART Error
};

/**
  \brief  Defines the UART HAL error status.
*/
enum _HAL_UART_Status_ {
  HAL_UART_STATUS_OK               = 0x00,    ///< Transfer OK
  HAL_UART_STATUS_TIMEOUT          = 0x01,    ///< Transfer Timeout
  HAL_UART_STATUS_ERR_OVERRUN      = 0x02,    ///< RX Over run
  HAL_UART_STATUS_ERR_PARITY       = 0x04,    ///< Parity error
  HAL_UART_STATUS_ERR_FRAM         = 0x08,    ///< Framing Error
  HAL_UART_STATUS_ERR_BREAK        = 0x10,    ///< Break Interrupt
  HAL_UART_STATUS_ERR_PARA         = 0x20,    ///< Parameter error
  HAL_UART_STATUS_ERR_RXFIFO       = 0x80,    ///< RX FIFO error
};

/// the value to check the line status error
#define UART_LSR_ERR                (HAL_UART_STATUS_ERR_OVERRUN | HAL_UART_STATUS_ERR_PARITY | \
                                     HAL_UART_STATUS_ERR_FRAM | HAL_UART_STATUS_ERR_BREAK |\
                                     HAL_UART_STATUS_ERR_RXFIFO)

/**
  \brief  Defines the hardware flow control types.
*/
enum uart_flow_ctrl_setting_e {
    UartFlowCtlNone     = 0,
    UartFlowCtlRTS      = 1,
    UartFlowCtlCTS      = 2,
    UartFlowCtlRTSCTS   = 3
};

/// The special timeout value as the wait forever.
#define UART_WAIT_FOREVER       0xffffffff

#define UART_DMA_MBLK_NUM       16      // maximum block number for each DMA transfer, it must <= 16
#define UART_DMA_BLOCK_SIZE     4092    // the block size of multiple block DMA, it cannot over 4095

/**
  \brief  UART call back function for TX/RX done, RX filter and RX idle events.
*/
typedef void (*uart_callback_t) (void *arg);
/**
  \brief  UART call back function for line status error events.
*/
typedef void (*uart_lsr_callback_t) (uint8_t lsr, void *arg);
/**
  \brief  UART call back function for TX done or RX data ready interrupr.
*/
typedef void (*uart_irq_callback_t)(uint32_t id, uint32_t event);

/**
  * @brief The structure to be used to pass the parameters for
  *        the calculation of OVSR and divisor  for a given baud rate.
  */
#if 0
typedef struct uart_speed_setting_s {
    uint32_t baudrate;       /*!< baud rate setting */
    uint32_t ovsr;           /*!< generated over sampling value */
    uint32_t div;            /*!< generated divisor value */
    uint32_t ovsr_adj;       /*!< generated over sampling adjustment value */
    uint8_t ovsr_adj_max_bits;  /*!< the maximum bits number of a frame, 9: No parity, 10: with Parity */
    uint8_t ovsr_adj_bits;   /*!< the adjustment bits number in a frame */
    uint8_t reserv1[2];
    const uint16_t *ovsr_adj_map;  /*!< the table for adjustment bits */
    uint32_t max_err;        /*!< maximum baud rate error percentage, 10 ~ 100: 30 */
    uint32_t ovsr_min;       /*!< minum value of OVSR, 10 ~ 20: 1000 */
    uint32_t ovsr_max;       /*!< maximum value of OVSR, 10 ~ 20: 2000 */
    uint32_t divisor_resolution; /*!< the step resolution for availabe divisor value seaching, 1 ~ 20: 10 */
    uint32_t jitter_lim;     /*!< limition for jitter of bits, 50 ~ 100: 100 */
    uint32_t sclk;           /*!< the input system clock */
} uart_speed_setting_t, *puart_speed_setting_t;

#endif
/**
  \brief  The data structure for an UART port HAL operations.
*/
typedef struct hal_uart_adapter_s {

	UART_TypeDef *base_addr;       /*!< The UART register base address */
    uint8_t uart_idx;           /*!< The UART index number */

    uint8_t tx_pin;             /*!< TX pin name */
    uint8_t rx_pin;             /*!< RX pin name */

    irq_handler_t   irq_fun;                    /*!< the IRQ handler for UART adapters */
}hal_uart_adapter_t, *phal_uart_adapter_t;


#if 0
/**
  \brief  The data structure to handle the common resource and setting for all UART adapters.
*/
typedef struct hal_uart_group_adapter_s {
    volatile uint32_t critical_lv;                  /*!< to record UART HAL enter critical section level */
    hal_uart_adapter_t *uart_adapter[MaxUartNum];   /*!< All the UART adapters of this platform */
    irq_handler_t   irq_fun[MaxUartNum];            /*!< the IRQ handler for different UART adapters */
} hal_uart_group_adapter_t, *phal_uart_group_adapter_t;
#endif
/**
  \brief  The data structure to be used to initial a new UART adapter.
*/

/**
  \brief  The data type of a element of the pre-defined baud rate table.
          It's used as the hash for bard rate index searching in the baud rate table.
*/
typedef struct hal_uart_baudrate_hash_s {
    uint32_t baud_rate;  /*!< the baud rate */
    uint32_t idx;        /*!< the index of this baud rate in the baud rate table */
} hal_uart_baudrate_hash_t, *phal_uart_baudrate_hash_t;


/**
 * @addtogroup hs_hal_uart_rom_func UART HAL ROM APIs.
 * @{
 */

int voe_uart_putc (void *arg, uint8_t tx_data);
//int voe_uart_getc (phal_uart_adapter_t puart_adapter, char *data);




/** @} */ /* End of group hs_hal_uart */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_UART_H_

