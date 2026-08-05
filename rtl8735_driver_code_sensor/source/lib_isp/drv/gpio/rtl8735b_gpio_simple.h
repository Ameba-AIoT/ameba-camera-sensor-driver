/**************************************************************************//**
 * @file     rtl8735b_gpio.h
 * @brief    This file defines GPIO HAL macros and data types.
 *
 * @version  V1.00
 * @date     2016-11-18
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

/**
 * @addtogroup hs_hal_gpio GPIO
 * @ingroup 8195bh_hal
 * @{
 * @brief The GPIO HAL module of the HS platform.
 */

#ifndef RTL8735B_GPIO_H
#define RTL8735B_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

// AON/PON/SYSON GPIO IP level registers
#include "rtl8735b_gpio_type_simple.h"

// System level AON/PON/SYSON regions registers
#include "rtl8735b_aon_type_simple.h"
#include "rtl8735b_pon_type_simple.h"
#include "rtl8735b_syson_type_simple.h"

#if !defined(CONFIG_BUILD_NONSECURE)

#undef AON_GPIO
#define AON_GPIO    (AON_GPIO_S_ADDR) // Secure address
#undef PON_GPIO
#define PON_GPIO    (PON_GPIO_S_ADDR) // Secure address
#undef SYSON_GPIO
#define SYSON_GPIO  (SYSON_GPIO_S_ADDR) // Secure address

#else

#undef AON_GPIO
#define AON_GPIO    (AON_GPIO_ADDR) // Non-Secure address
#undef PON_GPIO
#define PON_GPIO    (PON_GPIO_ADDR) // Non-Secure address
#undef SYSON_GPIO
#define SYSON_GPIO  (SYSON_GPIO_ADDR) // Non-Secure address

#endif

// Weide adapted from Crypto Example

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

/// @cond DOXYGEN_GPIO_REG_TYPE


/* ================================================================================================================ */
/* ================                          Device Specific Peripheral Address Map                           ===== */
/* ================================================================================================================ */


/** @addtogroup device_gpio_addr AON/PON/SYSON GPIO Register Base Addresses
 *  @ingroup hal_gpio
 *  @{
 */

#define AON_GPIO_S_BASE               0x5000A800UL
#define AON_GPIO_NS_BASE              0x4000A800UL

#define PON_GPIO_S_BASE               0x5000AC00UL
#define PON_GPIO_NS_BASE              0x4000AC00UL

#define SYSON_GPIO_S_BASE             0x50001000UL
#define SYSON_GPIO_NS_BASE            0x40001000UL

/** @} */ /* End of group device_gpio_addr */


/* ================================================================================================================ */
/* ================                                  Peripheral declaration                                   ===== */
/* ================================================================================================================ */


/** @addtogroup device_gpio_decl AON/PON/SYSON GPIO Device Type
 *  @ingroup hal_gpio
 *  @{
 */

#define AON_GPIO_S_ADDR                             ((GPIO_TypeDef *)           AON_GPIO_S_BASE)
#define AON_GPIO_ADDR                               ((GPIO_TypeDef *)           AON_GPIO_NS_BASE)

#define PON_GPIO_S_ADDR                             ((GPIO_TypeDef *)           PON_GPIO_S_BASE)
#define PON_GPIO_ADDR                               ((GPIO_TypeDef *)           PON_GPIO_NS_BASE)

#define SYSON_GPIO_S_ADDR                           ((GPIO_TypeDef *)           SYSON_GPIO_S_BASE)
#define SYSON_GPIO_ADDR                             ((GPIO_TypeDef *)           SYSON_GPIO_NS_BASE)

/** @} */ /* End of group device_gpio_decl */

/// @endcond /* End of condition DOXYGEN_GPIO_REG_TYPE */


/**
  \brief  Defines the data type for GPIO pin name, a GPIO pin name is
          from combination of GPIO port and GPIO pin index.
 */
typedef struct gpio_pin_s {
	union {
		uint8_t pin_name;
		struct {
			uint8_t pin: 5;             ///< bit:  4.. 0  the pin index in a port
			uint8_t port: 3;            ///< bit:  7.. 5 the port index
		} pin_name_b;
	};
} gpio_pin_t, *pgpio_pin_t;

/**
  \brief  Defines the data type of GPIO port. The GPIO port data type is from the
          combination of port index, pin mask and the offset of the 1st pin.
 */
typedef struct gpio_port_s {
	union {
		uint32_t port_name;
		struct {
			/*uint32_t mask:16;             ///< bit: 15.. 0  the pin mask of the port
			uint32_t offset:5;            ///< bit: 20.. 16 the 1st pin offset
			uint32_t :3;                  ///< bit: 23.. 21 reserved
			uint32_t port:3;              ///< bit: 26.. 24 the GPIO IP port index*/
			// weide unsure
			uint32_t mask: 18;            ///< bit: 17.. 0  the pin mask of the port
			uint32_t offset: 5;           ///< bit: 22.. 18 the 1st pin offset
			uint32_t : 1;                 ///< bit: 23.. 23 reserved
			uint32_t port: 3;             ///< bit: 26.. 24 the GPIO IP port index
		} port_name_b;
	};
} gpio_port_t, *pgpio_port_t;

/// Defines the maximum GPIO pin in a port
#define GPIO_MAX_PIN_IDX            32     // the maximum pin number in a GPIO IP port

/// Defines the maximum GPIO interrupt pins. It is the number of the PON or SYSON GPIO IRQ pins this platform can support.
#define GPIO_MAX_INT_PIN            16     // 0 ~ 15, one SYSON or PON GPIO IP only support 16 configurable interrupt pins
/// Defines the maximum GPIO interrupt pins. It is the number of the AON GPIO IRQ pins this platform can support.
#define AON_GPIO_MAX_INT_PIN        6     // 0 ~ 5, one AON GPIO IP only support 6 configurable interrupt pins

/// Defines the maximum GPIO debounce pins. It is the number of GPIO pin can enable the debounce function simultaneously.
#define GPIO_MAX_DEBOUNCE_PIN       16     // 0 ~ 15, one GPIO IP only support 16 configurable de-bounce pins
/// Defines the maximum GPIO debounce pins. It is the number of GPIO pin can enable the debounce function simultaneously.
#define AON_GPIO_MAX_DEBOUNCE_PIN   6     // 0 ~ 5, one GPIO IP only support 16 configurable de-bounce pins

/// define the GPIO port number. It's the number of the GPIO port this platform have.
#define GPIO_MAX_PORT_NUM           4      // 0 ~ 3, the port number of the GPIO IP // should be be 1 right?

/**
  \brief  Defines the GPIO port name
 */
enum {
	GPIO_IP_PORT0         = 0,
	GPIO_IP_PORT1         = 1,
	GPIO_IP_PORT2         = 2,
	GPIO_IP_PORT3         = 3,

	GPIO_IP_MAX_PORT_ID   = 4
};

/**
  \brief  Defines type of GPIO - AON/PON/SYSON GPIO.
 */
enum gpio_type_e {
	AonGPIO  = 0,
	SysonGPIO = 1,
	PonGPIO  = 2
};
typedef uint8_t gpio_type_t;

/**
  \brief  Defines GPIO interrupt polarity status
 */
enum {
	GPIO_LevelHigh      = 0,
	GPIO_LevelLow       = 1,
	GPIO_EdgeRising     = 0,
	GPIO_EdgeFalling    = 1,
	GPIO_EdgeDual       = 2
};

/**
  \brief  Defines GPIO interrupt trigger event type.
 */
enum  gpio_int_trigger_type_e {
	GPIO_IntType_None           = 0,
	GPIO_IntType_EdgeRising     = 1,
	GPIO_IntType_EdgeFalling    = 2,
	GPIO_IntType_LevelLow       = 3,
	GPIO_IntType_LevelHigh      = 4,
	GPIO_IntType_EdgeDual       = 5,

	GPIO_IntType_Invalid        = 0x0F
};
typedef uint8_t gpio_int_trig_type_t;

/**
  \brief  Defines GPIO pin direction.
 */
enum  gpio_dir_e {
	GPIO_IN                  = 0,
	GPIO_OUT                 = 1
};
typedef uint8_t gpio_dir_t;


/**
  \brief  Defines GPIO Interrupt clock source.
 */
enum  gpio_int_clk_e {
	GPIO_IntClk_100K    = 0, // 100k clk
	GPIO_IntClk_4M      = 1 // 4M clk
};
typedef uint8_t gpio_int_clk_t;

/**
  \brief  Defines IO pad pull control type.
 */
enum pin_pull_ctrl_e {
	GPIO_REG_PullCtrl_Set_HighZ = 0,
	GPIO_REG_PullCtrl_SetLow = 1,
	GPIO_REG_PullCtrl_SetHigh = 2
};

/**
  \brief  Defines IO pad pull type hardware supported.
 */
enum pin_pull_type_e {
	Pin_PullNone  = 0,
	Pin_PullUp    = 1,
	Pin_PullDown  = 2,
	Pin_PullDefault = Pin_PullNone
};
typedef uint8_t pin_pull_type_t;

/**
  \brief  Defines GPIO interrupt call back function type.
 */
typedef void (*gpio_irq_callback_t)(uint32_t int_id, gpio_int_trig_type_t int_type);

/**
  \brief  The data structure for a GPIO pin HAL operation.
*/
typedef struct hal_gpio_pin_adapter_s {
	uint8_t pin_name;               ///< chip pin name to locate the GPIO pin by port & pin index
	uint8_t port_idx;               ///< the GPIO IP port index of the GPIO pin
	uint8_t pin_idx;                ///< the GPIO IP pin index of the GPIO port
	uint8_t debounce_idx;           ///< the index of GPIO debounce function allocated to this GPIO pin, 0 ~ 15
	uint32_t bit_mask;              ///< the bit mask to read/write register

	volatile uint32_t *in_port;     ///< the IN port address
	volatile uint32_t *out0_port;   ///< the OUT port address for write 0
	volatile uint32_t *out1_port;   ///< the OUT port address for write 1
	volatile uint32_t *outt_port;   ///< the OUT port address for toggling
} hal_gpio_adapter_t, *phal_gpio_adapter_t;

/**
  \brief  The data structure for a GPIO IRQ pin HAL operation.
*/
typedef struct hal_gpio_irq_pin_adapter_s {
	uint8_t     pin_name;           ///< chip pin name to locate the GPIO pin by port & pin index
	uint8_t     ip_pin_name;        ///< IP pin name to locate the GPIO pin by port & pin index
	uint8_t     int_idx;            ///< the GPIO interrupt function index, 0 ~ 15
	uint8_t     debounce_idx;       ///< the GPIO debounce function index, 0 ~ 15
	uint8_t     int_type;           ///< the GPIO interrupt trigger type
	uint8_t     resv[3];
	uint32_t    bit_mask;           ///< the bit mask to read register
	volatile uint32_t    *in_port;  ///< the IN port address
	gpio_irq_callback_t irq_callback;   ///< the call-back function of the GPIO IRQ
	uint32_t irq_callback_arg;      ///< the argument of the IRQ call-back function, it's a priviate data will be pass to the application with the call back function.
	void *pnext;                    ///< point to the next gpio_irq_pin_adapter
} hal_gpio_irq_adapter_t, *phal_gpio_irq_adapter_t;

/**
  \brief  The data structure for a GPIO port HAL operation.
*/
typedef struct hal_gpio_port_adapter_s {
	uint8_t port_idx;               ///< the IP port index
	uint8_t chip_port_idx;          ///< the chip port index (for pinmux reg & unreg purposes)
	uint8_t pin_offset;             ///< the pin0 of this port which is located at the offset of the IP port
	uint8_t reserv0;
	uint8_t reserv1;
	uint32_t pin_mask;              ///< the mask of pin to indicates what pin is included
//    uint32_t bit_mask;            ///< the bit mask to read/write register
	volatile uint32_t *in_port;     ///< the IN port address
	volatile uint32_t *out0_port;   ///< the OUT port address for write 0
	volatile uint32_t *out1_port;   ///< the OUT port address for write 1
	volatile uint32_t *outt_port;   ///< the OUT port address for toggling
} hal_gpio_port_adapter_t, *phal_gpio_port_adapter_t;

/**
  \brief  The data structure for SYSON GPIO Common resource menagement.
*/
typedef struct hal_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        ///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        ///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv;  ///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;    ///< IRQ handler error
			volatile uint32_t init_err: 1;   ///< initial error
		} err_flag;
	};
} hal_gpio_comm_adapter_t, *phal_gpio_comm_adapter_t;

/**
  \brief  The data structure for AON GPIO Common resource menagement.
*/
typedef struct hal_aon_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        ///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        ///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv;  ///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;    ///< IRQ handler error
			volatile uint32_t init_err: 1;   ///< initial error
		} err_flag;
	};
} hal_aon_gpio_comm_adapter_t, *phal_aon_gpio_comm_adapter_t;

/**
  \brief  The data structure for PON GPIO Common resource menagement.
*/
typedef struct hal_pon_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        ///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        ///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv;  ///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;    ///< IRQ handler error
			volatile uint32_t init_err: 1;   ///< initial error
		} err_flag;
	};
} hal_pon_gpio_comm_adapter_t, *phal_pon_gpio_comm_adapter_t;

// #if !defined(CONFIG_BUILD_SECURE) // Sunny commented out

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_gpio_rom_func GPIO HAL ROM APIs.
 * @ingroup hs_hal_gpio
 * @{
 */

hal_status_t hal_gpio_init_simple(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
void hal_gpio_deinit_simple(phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_set_dir_simple(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
gpio_dir_t hal_gpio_get_dir_simple(phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_write_simple(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
uint32_t hal_gpio_read_simple(phal_gpio_adapter_t pgpio_adapter);

#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_GPIO_H */


/** @} */ /* End of group hs_hal_gpio */

