/**************************************************************************//**
 * @file     hal_voe_rom.h
 * @brief    Define the data structure for VOE ROM Boot functions.
 * @version  V1.00
 * @date     2021-07-04
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _FCS_GEN_H_
#define _FCS_GEN_H_

#ifdef  __cplusplus
extern "C"
{
#endif

//#define _FPGA_MIPI_APHY_
//#define _USE_RAM_SIM_FCS_


#define ISP_MULTI_FCS_MAGIC_NUM	0x5343464D /* 'M', 'F', 'C', 'S' */
#define ISP_MFCS_DATA_VERSION   0x00010001    /*  Major-[31:16] */
#define MULTI_FCS_MAX			10


#define ISP_FCS_DATA_MAGIC_NUM	0x53434649 /* 'I', 'F', 'C', 'S' */
#define ISP_FCS_DATA_VERSION	0x00010000    /*  Major-[31:16] */ //B-cut
#define ISP_FCS_DATA_VERSION_C	0x00020000    /*  Major-[31:16] */ //C-cut
#define ISP_FCS_VERION_MJR_MASK 0xFFFF0000
#define FCS_SRAM_ADDR			0x2000F000

#define GPIO_MAX                12
#define I2C_MAX					2

#define ISP_FCS_OK				0x0


#define FCS_DATA_LOAD_OK_TM		0x0001
#define FULL_LOAD_OK_FCS_OK_TM	0x0002
#define FULL_LOAD_OK_FCS_NG_TM	0x0003
#define FULL_LOAD_OK_FCS_NK_TM	0x0004

#define FCS_INIT_ROM_RDY_KM		0x0080
#define FCS_WAIT_SNR_CLK_KM		0x0081
#define FCS_RUN_DATA_OK_KM		0x0082
#define FCS_RUN_DATA_NG_KM		0x2081



#define TM_ERROR				0x1000
#define FCS_DATA_HEADER_ERR		0x1001
#define FCS_DATA_GPIO_CNT_ERR	0x1002
#define FCS_CPY_FUNC_ERR		0x1003
#define FCS_ITCM_INFO_ERR		0x1004
#define FCS_DTCM_INFO_ERR		0x1005
#define MFCS_DATA_HEADER_ERR	0x1006
#define MFCS_FCS_CNT_ID_ERR		0x1007
#define MFCS_FCS_ADDR_SZ_ERR	0x1008
#define FCS_WAIT_KM_TMOUT_ERR	0x1009
#define FCS_WAIT_SNR_TMOUT_ERR	0x100A
#define FCS_INVALID_CMD_ERR		0x100B

#define KM_ERROR				0x2000
#define FCS_CMD_INVALID_ERR		0x2006
#define FCS_ERR_CMDID			0x2007
#define FCS_SNR_CLK_TYPE_ERR	0x2008
#define FCS_GPIO_INIT_ERR		0x2009
#define FCS_I2C_INIT_ERR		0x200A
#define FCS_ADC_INIT_ERR		0x200B
#define FCS_PWM_INIT_ERR		0x200C
#define FCS_DATA_I2C_CNT_ERR	0x200D

#define FCS_ADC_NIDLE_ERR		0x2010
#define FCS_ADC_INPROG_ERR		0x2011
#define FCS_ADC_SINREAD_ERR		0x2012
#define FCS_ADC_CALIPARA_ERR	0x2013
#define FCS_ADC_DIVBYZERO_ERR	0x2014
#define FCS_ADC_NEGVALUE_ERR	0x2015
#define FCS_ADC_OVERFLOW_ERR	0x2016


#define FCS_I2C_TRANS_ERR		0x2100
#define FCS_I2C_CMP_ERR			0x21FF
#define FCS_I2C_BSTWRITE_ERR	0x21FE
#define FCS_I2C_CB_ERR			0x21FD

#define KM_STATUS				0x40492004
#define KM_FCS_ERROR_REG		0x40492008

#define TM_STATUS				0x40009154

#define REMAP_S7_ITCM 0x04000000   //0x04000000~0x0407FFFF
#define REMAP_S7_DTCM 0x00080000   //0x20080000~0x200FFFFF

#define VOE_IROM_S 0x00000000
#define VOE_IROM_E 0x000003FF       // 1KB
#define VOE_IRAM_S 0x00040000
#define VOE_IRAM_E 0x0004FFFF       // 64KB

#define VOE_DROM_S 0x20010000
#define VOE_DROM_E 0x20013FFF       // 16KB
#define VOE_DRAM_S 0x20000000
#define VOE_DRAM_E 0x2000FFFF       // 64KB


//#define WAIT_KM_INIT_TIMEOUT_US		5000

typedef struct isp_multi_fcs_hdr_s {
    uint32_t magic;
	uint32_t version;
    uint32_t fcs_data_size[MULTI_FCS_MAX];
    uint32_t fcs_data_offset[MULTI_FCS_MAX];
    uint32_t wait_km_init_timeout_us;
	uint8_t  multi_fcs_cnt;
	uint8_t  active_fcs;
	uint8_t  reserved[6];
} isp_multi_fcs_hdr_t;


// this size is not 4 bytes alignment, need padding one bytes
typedef struct isp_fcs_header_s {

	//struct isp_fcs_cmd_attribute_t cmd_attb;
    uint32_t magic;
    uint32_t version;
    uint32_t itcm_size;
    uint32_t itcm_addr;
    uint32_t dtcm_size;
    uint32_t dtcm_addr;


	uint8_t i2c_device_cnt;
    uint8_t i2c_speed_mode;
    uint16_t i2c_speed;		// unit: KHz
    
    uint16_t i2c_timeout;   //unit: us
	uint8_t i2c_id;
	uint8_t timer_id;
		
	uint8_t adc_id;   // use 1 gpio
	uint8_t pwm_id;   // same function as ir_led
	uint8_t gpio_list[GPIO_MAX]; //12
	uint8_t gpio_cnt;
	uint8_t snr_clk_pin; // dedicated gpio
		
	uint8_t i2c_scl; // dedicated gpio
	uint8_t i2c_sda; // dedicated gpio
	uint8_t reserved0;
	uint8_t adc_th_num;
		
	uint8_t adc_th_table_num;
	uint8_t adc_value_byte;
	uint8_t adc_use_cali;

	int16_t	adc_gain_deno;
	int16_t	adc_gain_mole;
		
	int32_t	adc_offset_mole;

	int16_t adc_offset_deno;
	int16_t wait_i2c_delay_us;
		
	uint32_t snr_timeout_us;

	uint16_t adc_trig_delay;
	uint8_t adc_ref_setting;
	uint8_t hclk_strong_driving;
	uint8_t reserved[4];

} isp_fcs_header_t;

typedef struct isp_i2c_info_s {
    uint16_t i2c_slave_addr;
    uint8_t addr_len;
    uint8_t data_len;
}isp_i2c_info_t;


/** \brief i2c speed mode
*/
enum i2c_spd_mode_e {
    I2CStandardSpeed    =   1,              /*!< 1: for i2c standard speed mode    */
    I2CFastSpeed        =   2,              /*!< 2: for i2c fast speed mode    */
    I2CHighSpeed        =   3,              /*!< 3: for i2c high speed mode    */
};

/// Defines the macro to convert port index and pin index to a pin name
#define PIN_NAME(port_id, pin_id)           (((port_id) << 5) | (pin_id))
/// Defines the macro to get the port index by the given pin name
#define PIN_NAME_2_PORT(pin_name)           (((pin_name) >> 5) & 0x07)
/// Defines the macro to get the pin index by the given pin name
#define PIN_NAME_2_PIN(pin_name)            ((pin_name) & 0x1F)

/// Defines maximum number of pin in a GPIO port
#define MAX_PIN_IN_PORT     24

/**
  \brief  Defines Chip's IO port name.
 */
enum {
    PORT_A         = 0,
    PORT_B         = 1,
    PORT_C         = 2,
    PORT_D         = 3,
    PORT_E         = 4,
    PORT_F         = 5,
    PORT_G         = 6,
    PORT_H         = 7,

    PORT_MAX_NUM   = 8
};

// virtual internal port, no pin out
#define PORT_INTERNAL       (4)

/**
  \brief  Defines Chip's IO pin name.
 */
enum {
    PIN_A0         = PIN_NAME(PORT_A, 0),
    PIN_A1         = PIN_NAME(PORT_A, 1),
    PIN_A2         = PIN_NAME(PORT_A, 2),
    PIN_A3         = PIN_NAME(PORT_A, 3),
    PIN_A4         = PIN_NAME(PORT_A, 4),
    PIN_A5         = PIN_NAME(PORT_A, 5),
    PIN_A6         = PIN_NAME(PORT_A, 6),
    PIN_A7         = PIN_NAME(PORT_A, 7),
    PIN_A8         = PIN_NAME(PORT_A, 8),
    PIN_A9         = PIN_NAME(PORT_A, 9),
    PIN_A10        = PIN_NAME(PORT_A, 10),
    PIN_A11        = PIN_NAME(PORT_A, 11),
    PIN_A12        = PIN_NAME(PORT_A, 12),
    PIN_A13        = PIN_NAME(PORT_A, 13),
    PIN_A14        = PIN_NAME(PORT_A, 14),
    PIN_A15        = PIN_NAME(PORT_A, 15),
    PIN_A16        = PIN_NAME(PORT_A, 16),
    PIN_A17        = PIN_NAME(PORT_A, 17),
    PIN_A18        = PIN_NAME(PORT_A, 18),
    PIN_A19        = PIN_NAME(PORT_A, 19),
    PIN_A20        = PIN_NAME(PORT_A, 20),
    PIN_A21        = PIN_NAME(PORT_A, 21),
    PIN_A22        = PIN_NAME(PORT_A, 22),
    PIN_A23        = PIN_NAME(PORT_A, 23),

    PIN_B0         = PIN_NAME(PORT_B, 0),
    PIN_B1         = PIN_NAME(PORT_B, 1),
    PIN_B2         = PIN_NAME(PORT_B, 2),
    PIN_B3         = PIN_NAME(PORT_B, 3),
    PIN_B4         = PIN_NAME(PORT_B, 4),
    PIN_B5         = PIN_NAME(PORT_B, 5),
    PIN_B6         = PIN_NAME(PORT_B, 6),
    PIN_B7         = PIN_NAME(PORT_B, 7),
    PIN_B8         = PIN_NAME(PORT_B, 8),
    PIN_B9         = PIN_NAME(PORT_B, 9),
    PIN_B10        = PIN_NAME(PORT_B, 10),
    PIN_B11        = PIN_NAME(PORT_B, 11),
    PIN_B12        = PIN_NAME(PORT_B, 12),

    PIN_C0         = PIN_NAME(PORT_C, 0),
    PIN_C1         = PIN_NAME(PORT_C, 1),
    PIN_C2         = PIN_NAME(PORT_C, 2),
    PIN_C3         = PIN_NAME(PORT_C, 3),
    PIN_C4         = PIN_NAME(PORT_C, 4),
    PIN_C5         = PIN_NAME(PORT_C, 5),
    PIN_C6         = PIN_NAME(PORT_C, 6),
    PIN_C7         = PIN_NAME(PORT_C, 7),
    PIN_C8         = PIN_NAME(PORT_C, 8),
    PIN_C9         = PIN_NAME(PORT_C, 9),
    PIN_C10        = PIN_NAME(PORT_C,10),
    PIN_C11        = PIN_NAME(PORT_C,11),

    PIN_D0         = PIN_NAME(PORT_D, 0),
    PIN_D1         = PIN_NAME(PORT_D, 1),
    PIN_D2         = PIN_NAME(PORT_D, 2),
    PIN_D3         = PIN_NAME(PORT_D, 3),
    PIN_D4         = PIN_NAME(PORT_D, 4),
    PIN_D5         = PIN_NAME(PORT_D, 5),
    PIN_D6         = PIN_NAME(PORT_D, 6),
    PIN_D7         = PIN_NAME(PORT_D, 7),
    PIN_D8         = PIN_NAME(PORT_D, 8),
    PIN_D9         = PIN_NAME(PORT_D, 9),
    PIN_D10        = PIN_NAME(PORT_D,10),
    PIN_D11        = PIN_NAME(PORT_D,11),
    PIN_D12        = PIN_NAME(PORT_D,12),
    PIN_D13        = PIN_NAME(PORT_D,13),
    PIN_D14        = PIN_NAME(PORT_D,14),
    PIN_D15        = PIN_NAME(PORT_D,15),

    PIN_E0         = PIN_NAME(PORT_E, 0),
    PIN_E1         = PIN_NAME(PORT_E, 1),
    PIN_E2         = PIN_NAME(PORT_E, 2),
    PIN_E3         = PIN_NAME(PORT_E, 3),
    PIN_E4         = PIN_NAME(PORT_E, 4),
    PIN_E5         = PIN_NAME(PORT_E, 5),
    PIN_E6         = PIN_NAME(PORT_E, 6),
    PIN_E7         = PIN_NAME(PORT_E, 7),
    PIN_E8         = PIN_NAME(PORT_E, 8),
    PIN_E9         = PIN_NAME(PORT_E, 9),
    PIN_E10        = PIN_NAME(PORT_E,10),
    PIN_E11        = PIN_NAME(PORT_E,11),
    PIN_E12        = PIN_NAME(PORT_E,12),
    PIN_E13        = PIN_NAME(PORT_E,13),
    PIN_E14        = PIN_NAME(PORT_E,14),
    PIN_E15        = PIN_NAME(PORT_E,15),

    PIN_F0         = PIN_NAME(PORT_F, 0),
    PIN_F1         = PIN_NAME(PORT_F, 1),
    PIN_F2         = PIN_NAME(PORT_F, 2),
    PIN_F3         = PIN_NAME(PORT_F, 3),
    PIN_F4         = PIN_NAME(PORT_F, 4),
    PIN_F5         = PIN_NAME(PORT_F, 5),
    PIN_F6         = PIN_NAME(PORT_F, 6),
    PIN_F7         = PIN_NAME(PORT_F, 7),
    PIN_F8         = PIN_NAME(PORT_F, 8),
    PIN_F9         = PIN_NAME(PORT_F, 9),
    PIN_F10        = PIN_NAME(PORT_F,10),

    PIN_G0         = PIN_NAME(PORT_G, 0),
    PIN_G1         = PIN_NAME(PORT_G, 1),
    PIN_G2         = PIN_NAME(PORT_G, 2),
    PIN_G3         = PIN_NAME(PORT_G, 3),
    PIN_G4         = PIN_NAME(PORT_G, 4),
    PIN_G5         = PIN_NAME(PORT_G, 5),
    PIN_G6         = PIN_NAME(PORT_G, 6),
    PIN_G7         = PIN_NAME(PORT_G, 7),
    PIN_G8         = PIN_NAME(PORT_G, 8),
    PIN_G9         = PIN_NAME(PORT_G, 9),

    PIN_H0         = PIN_NAME(PORT_H, 0),
    PIN_H1         = PIN_NAME(PORT_H, 1),
    PIN_H2         = PIN_NAME(PORT_H, 2),
    PIN_H3         = PIN_NAME(PORT_H, 3),
    PIN_H4         = PIN_NAME(PORT_H, 4),
    PIN_H5         = PIN_NAME(PORT_H, 5),
    PIN_H6         = PIN_NAME(PORT_H, 6),
    PIN_H7         = PIN_NAME(PORT_H, 7),
    PIN_H8         = PIN_NAME(PORT_H, 8),
    PIN_H9         = PIN_NAME(PORT_H, 9),
    PIN_H10        = PIN_NAME(PORT_H,10),
    PIN_H11        = PIN_NAME(PORT_H,11),
    PIN_H12        = PIN_NAME(PORT_H,12),
    PIN_H13        = PIN_NAME(PORT_H,13),
    PIN_H14        = PIN_NAME(PORT_H,14),

// Virtual pin (internal pin, no pin out)
    PIN_UART3_TX   = PIN_NAME(PORT_INTERNAL, 0),
    PIN_UART3_RX   = PIN_NAME(PORT_INTERNAL, 1),
    PIN_UART3_RTS  = PIN_NAME(PORT_INTERNAL, 2),
    PIN_UART3_CTS  = PIN_NAME(PORT_INTERNAL, 3),

    PIN_NC         = 0xFF,
    PIN_LIST_END   = 0xFF
};
typedef uint8_t pin_name_t;

/**
  \brief  Defines the data type for IO pin.
 */
typedef struct io_pin_s {
    union {
        uint8_t pin_name;
        struct {
            uint8_t pin:5;              ///< bit:  4.. 0  the pin index in a port
            uint8_t port:3;             ///< bit:  7.. 5 the IO port index
        } pin_name_b;
    };
} io_pin_t, *pio_pin_t;

#define VALID_ATTB		0x1
#define END_ATTB		0x2
#define NOP_ATTB		0x4
#define ETA_PL_ATTB		0x8


//#define _GEN_FCS_DATA_


typedef struct isp_fcs_cmd_s{
	uint8_t cmd_id;
	uint8_t cmd_attb;
	uint8_t payload_0;
	uint8_t payload_1; //extra_payload_size
}isp_fcs_cmd_t;

#define BASIC_CMD  0x0
#define PERI_CMD   0x2
#define I2C_CMD	   0x4
#define ADC_CMD    0x6

#define MAX_ADC_SAMPLE	16
#define MAX_ADC_LUT		10


enum isp_fcs_cmd_id_e {

	ISP_FCS_SNR_HCLK_SET		= 0x00,
	ISP_FCS_TIMER_DELAYMS		= 0x01,
	ISP_FCS_GPIO_INIT			= 0x02,
	ISP_FCS_ADC_INIT			= 0x03,
	ISP_FCS_I2C_INIT			= 0x04,

	ISP_FCS_GPIO_SET			= 0x20,			//cmd(gpio_id, value)
	ISP_FCS_GPIO_SET_BYDARK		= 0x21,			//cmd(gpio_id, value)
	ISP_FCS_DARK_SET			= 0x22,			//cmd(value, N/A	)
	ISP_FCS_PWM_START			= 0x23,
	ISP_FCS_PWM_START_BYDARK	= 0x24,
	ISP_FCS_PWM_STOP			= 0x25,

	ISP_FCS_I2C_WRITE_8			= 0x40,
	ISP_FCS_I2C_READ_CMP_8		= 0x41,
	ISP_FCS_I2C_WRITE_16		= 0x42,
	ISP_FCS_I2C_READ_CMP_16		= 0x43,
	ISP_FCS_I2C2_WRITE_8		= 0x44,
	ISP_FCS_I2C2_READ_CMP_8		= 0x45,
	ISP_FCS_I2C2_WRITE_16		= 0x46,
	ISP_FCS_I2C2_READ_CMP_16	= 0x47,
	ISP_FCS_I2C_BSTWRITE_8		= 0x48,
	ISP_FCS_I2C_BSTWRITE_16		= 0x49,
	ISP_FCS_I2C2_BSTWRITE_8		= 0x4A,
	ISP_FCS_I2C2_BSTWRITE_16	= 0x4B,
	ISP_FCS_I2C_READ_WAIT_8		= 0x4C,			// cmd(addr, check_value); timeout
	ISP_FCS_I2C_READ_WAIT_16	= 0x4D,			// cmd; addr; check_value; timeout
	ISP_FCS_I2C_BYPASS_RET_CHECK= 0x4E,


	ISP_FCS_ADC_GET				= 0x60,
	ISP_FCS_ADC_GET_AVERAGE		= 0x61,			// cmd(sample_cnt, N/A)
	ISP_FCS_ADC_SET_MODE		= 0x62,			// cmd(adc_lut_id, N/A)
	ISP_FCS_ADC_SET_DARK		= 0x63,			// cmd(dark_th_LSB, dark_th_MSB)
	ISP_FCS_ADC_JUMP_BY_MODE	= 0x64,
	ISP_FCS_ADC_JUMP			= 0x65,




	//ISP_FCS_I2C_DMA_WRITE_8	= 0x46,
	//ISP_FCS_I2C_DMA_WRITE_16	= 0x47,

};

enum rts_isp_sensor_clock {
	CLK_NONE = 0,
	CLK_12M = 1,
	CLK_24M = 2,
	CLK_27M = 3,
	CLK_37M125 = 4,
	CLK_54M = 5,
	CLK_74M25 = 6,
};

#ifdef  __cplusplus
}
#endif

#endif // end of "#define _FCS_GEN_H_"
