/**************************************************************************//**
 * @file     rtl8735b_gpio.c
 * @brief    This file implements the GPIO HAL functions.
 *
 * @version  V1.00
 * @date     2020-11-11
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

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#include "rtl8735b_gpio_simple.h"
#include "isp_log.h"

#if CONFIG_GPIO_EN

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#else
/// Defines the macro to convert port index and pin index to a pin name
#define PIN_NAME(port_id, pin_id)           (((port_id) << 5) | (pin_id))
/// Defines the macro to get the port index by the given pin name
#define PIN_NAME_2_PORT(pin_name)           (((pin_name) >> 5) & 0xF)
/// Defines the macro to get the pin index by the given pin name
#define PIN_NAME_2_PIN(pin_name)            ((pin_name) & 0x1F)
/// Defines maximum number of pin in a GPIO port
#define MAX_PIN_IN_PORT     18  // not including DDR pins

enum {
	PORT_A          = 0,
	PORT_B          = 1,
	PORT_C          = 2,
	PORT_D          = 3,
	PORT_E          = 4,
	PORT_F          = 5,
	PORT_S          = 6,
	PORT_DDR        = 7,

	PORT_MAX_NUM    = 8
};

#endif

/**
  * @brief The table of all GPIO (SYSON/AON/PON) port data mode direction status registers address.
  */
static const volatile uint32_t *pport_dmd_sts[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_DMD_STS),
	&(PON_GPIO->GPIO_PORT_A_DMD_STS),
	&(SYSON_GPIO->GPIO_PORT_A_DMD_STS),
	&(SYSON_GPIO->GPIO_PORT_B_DMD_STS)
};

/**
  * @brief The table of all GPIO (SYSON/AON/PON) port data mode input enable registers address.
  */
static const volatile uint32_t *pport_idm_en[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_IDM_EN),
	&(PON_GPIO->GPIO_PORT_A_IDM_EN),
	&(SYSON_GPIO->GPIO_PORT_A_IDM_EN),
	&(SYSON_GPIO->GPIO_PORT_B_IDM_EN)
};

/**
  * @brief The table of all GPIO port (SYSON/AON/PON) data mode output enable registers address.
  */
static const volatile uint32_t *pport_odm_en[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_ODM_EN),
	&(PON_GPIO->GPIO_PORT_A_ODM_EN),
	&(SYSON_GPIO->GPIO_PORT_A_ODM_EN),
	&(SYSON_GPIO->GPIO_PORT_B_ODM_EN)
};

/**
  * @brief The table of all GPIO (SYSON/AON/PON) port data mode output low registers address.
  */
static const volatile uint32_t *pport_odl_en[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_ODL_EN),
	&(PON_GPIO->GPIO_PORT_A_ODL_EN),
	&(SYSON_GPIO->GPIO_PORT_A_ODL_EN),
	&(SYSON_GPIO->GPIO_PORT_B_ODL_EN)
};

/**
  * @brief The table of all GPIO (SYSON/AON/PON) port data mode output high registers address.
  */
static const volatile uint32_t *pport_odh_en[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_ODH_EN),
	&(PON_GPIO->GPIO_PORT_A_ODH_EN),
	&(SYSON_GPIO->GPIO_PORT_A_ODH_EN),
	&(SYSON_GPIO->GPIO_PORT_B_ODH_EN)
};

/**
  * @brief The table of all GPIO (SYSON/AON/PON) port data mode output toggle registers address.
  */
static const volatile uint32_t *pport_odt_en[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_ODT_EN),
	&(PON_GPIO->GPIO_PORT_A_ODT_EN),
	&(SYSON_GPIO->GPIO_PORT_A_ODT_EN),
	&(SYSON_GPIO->GPIO_PORT_B_ODT_EN)

};

/**
  * @brief The table of all GPIO port data pin status registers address. AON GPIO uses only Port A in ProII.
  */
static const volatile uint32_t *pport_dp_sts[GPIO_MAX_PORT_NUM] = {
	&(AON_GPIO->GPIO_PORT_A_DP_STS),
	&(PON_GPIO->GPIO_PORT_A_DP_STS),
	&(SYSON_GPIO->GPIO_PORT_A_DP_STS),
	&(SYSON_GPIO->GPIO_PORT_B_DP_STS)

};

/**
 *  @brief Initials a GPIO pin.
 *           - Defult configure the GPIO pin as a normal input pin (not an interrupt pin).
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO pin initialization OK.
 */
hal_status_t hal_gpio_init_simple(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pin_name);
	uint8_t pin_idx = PIN_NAME_2_PIN(pin_name);
	uint32_t bit_mask;
	uint32_t *port_idm_en;

	if ((port_idx >= PORT_MAX_NUM) || (pin_idx >= MAX_PIN_IN_PORT)) {
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	if (((AON->AON_REG_AON_SYS_INFO1 & 0xff) == 0x10) && // Test Chip
		((port_idx == PORT_D) && (pin_idx > 16))) { // pin > D16
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	if (((AON->AON_REG_AON_SYS_INFO1 & 0xff) != 0x10) && // MP Chip
		((port_idx == PORT_E) && (pin_idx > 6))) { // pin > E6
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	// convert chip pin definition to IP pin definition
	/* Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins
	 * Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins
	 * Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins
	 * Port D: GPIO IP Port2[25:9] // SYSON GPIO 17 pins
	 * Port E1: GPIO IP Port2[31:26] // SYSON GPIO 6 pins
	 * Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Port 3 from Port 2)
	 * Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins
	 * Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Port 3 from Port 2)
	 */
	switch (port_idx) {
	case PORT_A: // AON GPIO
		port_idx = 0;
		pin_idx += 0;
		//gpio_type = AonGPIO;
		break;
	case PORT_B:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 0;
		//gpio_type = SysonGPIO;
		break;
	case PORT_C:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 3; // pin starts at 4th position, Pin 3 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	case PORT_D:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 9; // pin starts at 10th position, Pin 9 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	case PORT_E:
		if ((AON->AON_REG_AON_SYS_INFO1 & 0xff) == 0x10) { // Test Chip
			if (pin_idx > 5) {
				port_idx = 3;
				pin_idx -= 6; // because pin_idx = 6 will be mapped to Group B[0], pin_idx = 7 mapped to Group B[1], etc
			} else { // means still at Port A [31:26]
				port_idx = 2;
				pin_idx += 26;
			}
		} else { // MP Chip
			if (pin_idx > 1) {
				port_idx = 3;
				pin_idx -= 2; // because pin_idx = 2 will be mapped to Group B[0], pin_idx = 3 mapped to Group B[1], etc
			} else { // means still at Port A [31:30]
				port_idx = 2;
				pin_idx += 30;
			}
		}
		//gpio_type = SysonGPIO;
		break;
	case PORT_F: // PON GPIO
		port_idx = 1;
		pin_idx += 0;
		//gpio_type = PonGPIO;
		break;
	case PORT_S: // SYSON GPIO Group B
		port_idx = 3;
		pin_idx += 5; // pin starts at 6th position, Pin 5 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	default:
		port_idx = 0;
		pin_idx += 0;
		//gpio_type = AonGPIO;
		break;
	}

	memset((void *) pgpio_adapter, 0, sizeof(hal_gpio_adapter_t));

	bit_mask = 1 << pin_idx;
	isp_info("bit_mask:%x\r\n", bit_mask);

	pgpio_adapter->pin_name = pin_name;
	pgpio_adapter->port_idx = port_idx;
	pgpio_adapter->pin_idx = pin_idx;
	pgpio_adapter->bit_mask = 1 << pin_idx;
	pgpio_adapter->in_port = (uint32_t *)pport_dp_sts[port_idx];
	isp_info("in_port: %x\r\n", pgpio_adapter->in_port);
	pgpio_adapter->out0_port = (uint32_t *)pport_odl_en[port_idx];
	isp_info("out0_port: %x\r\n", pgpio_adapter->out0_port);
	pgpio_adapter->out1_port = (uint32_t *)pport_odh_en[port_idx];
	isp_info("out1_port: %x\r\n", pgpio_adapter->out1_port);
	pgpio_adapter->outt_port = (uint32_t *)pport_odt_en[port_idx];
	isp_info("outt_port: %x\r\n", pgpio_adapter->outt_port);
	pgpio_adapter->debounce_idx = 0xFF; // mark as not using debounce

	// default configure it as an input pin
	port_idm_en = (uint32_t *)pport_idm_en[port_idx];
	*port_idm_en = bit_mask;

	return HAL_OK;
}

/**
 *  @brief Initials a GPIO pin.
 *           - Defult configure the GPIO pin as a normal input pin (not an interrupt pin).
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO pin initialization OK.
 */
hal_status_t hal_gpio_init_simple_fcs(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pin_name);
	uint8_t pin_idx = PIN_NAME_2_PIN(pin_name);
	uint32_t bit_mask;
	uint32_t *port_idm_en;

	if ((port_idx >= PORT_MAX_NUM) || (pin_idx >= MAX_PIN_IN_PORT)) {
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	if (((AON->AON_REG_AON_SYS_INFO1 & 0xff) == 0x10) && // Test Chip
		((port_idx == PORT_D) && (pin_idx > 16))) { // pin > D16
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	if (((AON->AON_REG_AON_SYS_INFO1 & 0xff) != 0x10) && // MP Chip
		((port_idx == PORT_E) && (pin_idx > 6))) { // pin > E6
		printf("GPIO Init Invalid: port=%u pin=%u\r\n", port_idx, pin_idx);
		return HAL_ERR_PARA;
	}
	// convert chip pin definition to IP pin definition
	/* Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins
	 * Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins
	 * Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins
	 * Port D: GPIO IP Port2[25:9] // SYSON GPIO 17 pins
	 * Port E1: GPIO IP Port2[31:26] // SYSON GPIO 6 pins
	 * Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Port 3 from Port 2)
	 * Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins
	 * Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Port 3 from Port 2)
	 */
	switch (port_idx) {
	case PORT_A: // AON GPIO
		port_idx = 0;
		pin_idx += 0;
		//gpio_type = AonGPIO;
		break;
	case PORT_B:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 0;
		//gpio_type = SysonGPIO;
		break;
	case PORT_C:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 3; // pin starts at 4th position, Pin 3 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	case PORT_D:
		port_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 9; // pin starts at 10th position, Pin 9 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	case PORT_E:
		if ((AON->AON_REG_AON_SYS_INFO1 & 0xff) == 0x10) { // Test Chip
			if (pin_idx > 5) {
				port_idx = 3;
				pin_idx -= 6; // because pin_idx = 6 will be mapped to Group B[0], pin_idx = 7 mapped to Group B[1], etc
			} else { // means still at Port A [31:26]
				port_idx = 2;
				pin_idx += 26;
			}
		} else { // MP Chip
			if (pin_idx > 1) {
				port_idx = 3;
				pin_idx -= 2; // because pin_idx = 2 will be mapped to Group B[0], pin_idx = 3 mapped to Group B[1], etc
			} else { // means still at Port A [31:30]
				port_idx = 2;
				pin_idx += 30;
			}
		}
		//gpio_type = SysonGPIO;
		break;
	case PORT_F: // PON GPIO
		port_idx = 1;
		pin_idx += 0;
		//gpio_type = PonGPIO;
		break;
	case PORT_S: // SYSON GPIO Group B
		port_idx = 3;
		pin_idx += 5; // pin starts at 6th position, Pin 5 (Pin 0 is the 1st pin)
		//gpio_type = SysonGPIO;
		break;
	default:
		port_idx = 0;
		pin_idx += 0;
		//gpio_type = AonGPIO;
		break;
	}

	memset((void *) pgpio_adapter, 0, sizeof(hal_gpio_adapter_t));

	bit_mask = 1 << pin_idx;
	isp_info("bit_mask:%x\r\n", bit_mask);

	pgpio_adapter->pin_name = pin_name;
	pgpio_adapter->port_idx = port_idx;
	pgpio_adapter->pin_idx = pin_idx;
	pgpio_adapter->bit_mask = 1 << pin_idx;
	pgpio_adapter->in_port = (uint32_t *)pport_dp_sts[port_idx];
	isp_info("in_port: %x\r\n", pgpio_adapter->in_port);
	pgpio_adapter->out0_port = (uint32_t *)pport_odl_en[port_idx];
	isp_info("out0_port: %x\r\n", pgpio_adapter->out0_port);
	pgpio_adapter->out1_port = (uint32_t *)pport_odh_en[port_idx];
	isp_info("out1_port: %x\r\n", pgpio_adapter->out1_port);
	pgpio_adapter->outt_port = (uint32_t *)pport_odt_en[port_idx];
	isp_info("outt_port: %x\r\n", pgpio_adapter->outt_port);
	pgpio_adapter->debounce_idx = 0xFF; // mark as not using debounce

	// default configure it as an input pin
	//port_idm_en = (uint32_t *)pport_idm_en[port_idx];
	//*port_idm_en = bit_mask;

	return HAL_OK;
}

/**
 *  @brief To de-initial a GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
void hal_gpio_deinit_simple(phal_gpio_adapter_t pgpio_adapter)
{
	uint32_t *port_idm_en;

	port_idm_en = (uint32_t *)pport_idm_en[pgpio_adapter->port_idx];

	// switch to input mode
	*port_idm_en = 1 << pgpio_adapter->pin_idx;
}

/**
 *  @brief To set the direction of the given GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  dir  The direction (IN or OUT).
 *                     - 0: input.
 *                     - 1: output.
 *
 *  @returns    void
 */
void hal_gpio_set_dir_simple(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir)
{
	uint32_t *port_dir_en;

	if (dir == GPIO_IN) {
		port_dir_en = (uint32_t *)pport_idm_en[pgpio_adapter->port_idx];
	} else {
		port_dir_en = (uint32_t *)pport_odm_en[pgpio_adapter->port_idx];
	}

	*port_dir_en = 1 << pgpio_adapter->pin_idx;
}

/**
 *  @brief Gets current direction of the specified GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    The GPIO pin direction.
 *                - 0: input.
 *                - 1: output.
 */
gpio_dir_t hal_gpio_get_dir_simple(phal_gpio_adapter_t pgpio_adapter)
{
	uint32_t *pport_dir_sts;

	pport_dir_sts = (uint32_t *)pport_dmd_sts[pgpio_adapter->port_idx];

	if (*pport_dir_sts & (1 << pgpio_adapter->pin_idx)) {
		return GPIO_OUT;
	} else {
		return GPIO_IN;
	}
}

/**
 *  @brief Sets the output level of the specified GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  io_data  The value to be set to the GPIO pin, 0 or 1.
 *                - 0: the GPIO pin output low level.
 *                - 1: the GPIO pin output high level.
 *
 *  @returns    void
 */
void hal_gpio_write_simple(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data)
{

	if (io_data) {
		*(pgpio_adapter->out1_port) = pgpio_adapter->bit_mask;
		//*((uint32_t *)pport_odh_en[pgpio_adapter->port_idx]) = pgpio_adapter->bit_mask; // test see if need this
	} else {
		//(pgpio_adapter->out0_port) = (uint32_t *)pgpio_adapter->bit_mask; // old
		*(pgpio_adapter->out0_port) = pgpio_adapter->bit_mask;
		//*((uint32_t *)pport_odl_en[pgpio_adapter->port_idx]) = pgpio_adapter->bit_mask; // test see if need this
	}
}

/**
 *  @brief Reads the input level of the specified GPIO pin(direction is IN).
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns The gotton level (0 or 1) of the GPIO input pin.
 *             - 0: the GPIO pin input level is low.
 *             - 1: the GPIO pin input level is high.
 */
uint32_t hal_gpio_read_simple(phal_gpio_adapter_t pgpio_adapter)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pgpio_adapter->pin_name);

	if (pgpio_adapter->debounce_idx >= GPIO_MAX_DEBOUNCE_PIN) {
		isp_info("val in_port:%x\r\n", *((volatile uint32_t *)(pgpio_adapter->in_port)));
		return ((*((volatile uint32_t *)(pgpio_adapter->in_port)) & pgpio_adapter->bit_mask) ? 1 : 0);
	} else {
		isp_info("In GPIO HAL ROM Read with Debounce!\r\n");
		if (port_idx == PORT_A) {
			return (AON_GPIO->GPIO_DEB_DP_STS & (1 << pgpio_adapter->debounce_idx) ? 1 : 0);

		} else if (port_idx == PORT_B || port_idx == PORT_C || port_idx == PORT_D || port_idx == PORT_E || port_idx == PORT_S) {
			return (SYSON_GPIO->GPIO_DEB_DP_STS & (1 << pgpio_adapter->debounce_idx) ? 1 : 0);

		} else if (port_idx == PORT_F) {
			return (PON_GPIO->GPIO_DEB_DP_STS & (1 << pgpio_adapter->debounce_idx) ? 1 : 0);

		} else { // weide added to rm control reaches non-void
			isp_info("Error in port_idx parameter. port_idx: %x\r\n", port_idx);
			return HAL_ERR_PARA;
		}
	}
}

/** @} */ /* End of group hs_hal_gpio_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** @} */ /* End of group hs_hal_gpio */

#endif  // #if CONFIG_GPIO_EN

