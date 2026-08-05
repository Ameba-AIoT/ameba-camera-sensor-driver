/*
 * gen_fcs_data.c
 *
 *  Created on: 2021¦~11¤ë04¤é
 *      Author: martinhuang
 */


#include <stdio.h>
#include "fcs_gen.h"


#define ADC_TH_SET_NUM		2
#define ADC_TH_ITEM			8
#define SENSOR_CMD_CNT 		160

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1
#define PROJECT_LITT		0


typedef struct isp_fcs_data_for_k306p_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
} isp_fcs_data_for_k306p_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_k306p_t fcs_data_k306p_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x0601,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_k306p_t),
		.dtcm_addr = FCS_SRAM_ADDR,
		.i2c_id = 3,
		.i2c_device_cnt = 1,
		.i2c_speed_mode = I2CFastSpeed,
		.i2c_speed = 2000,
		.i2c_timeout = 10000,
		.timer_id = 3,
		.adc_id = 0xFF,   // use 1 gpio
		.pwm_id = 0xFF,   // same function as ir_led
		.gpio_cnt = 4,
		.gpio_list = {
			[0] = PIN_A5,   // pwr_ctrl
			[1] = PIN_E4,  //reset  mapping to E0
			[2] = PIN_D11, //pwdn
			[3] = PIN_E0,
		}, //pwdn

		.i2c_scl = PIN_D12,
		.i2c_sda = PIN_D10,
		.snr_clk_pin = PIN_D13,
		.adc_th_num = ADC_TH_ITEM,
		.adc_th_table_num = ADC_TH_SET_NUM,
		.adc_value_byte = 2,
		.wait_i2c_delay_us = 4000,
		.snr_timeout_us = 5000,
		.adc_trig_delay = 1000
	},
	.i2c_info = {
		.addr_len = 1,
		.data_len = 1,
#if(PROJECT_LITT)
		.i2c_slave_addr = 0x46
#else
		.i2c_slave_addr = 0x40
#endif
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 0, 100),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 0, 100),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),				//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 5 ms

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 0),
#if(PROJECT_LITT)
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 15, 0),					// delay 15 ms
#else
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 10, 0),					// delay 10 ms
#endif

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms


		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 124, 62),
		COMBINE_CMD(0x12, 0x60, 0x48, 0x86),
		COMBINE_CMD(0x48, 0x06, 0x0E, 0x11),
		COMBINE_CMD(0x0F, 0x0C, 0x10, 0x48),
		COMBINE_CMD(0x0C, 0x00, 0x0D, 0xA0),
		COMBINE_CMD(0x57, 0x67, 0x58, 0x1F),
		COMBINE_CMD(0x5F, 0x41, 0x60, 0x20),
		COMBINE_CMD(0x20, 0xC0, 0x21, 0x03),
		COMBINE_CMD(0x22, 0xDC, 0x23, 0x05),
		COMBINE_CMD(0x24, 0x88, 0x25, 0xA8),
		COMBINE_CMD(0x26, 0x52, 0x27, 0xBC),
		COMBINE_CMD(0x28, 0x15, 0x29, 0x03),
		COMBINE_CMD(0x2A, 0xB6, 0x2B, 0x13),
		COMBINE_CMD(0x2C, 0x00, 0x2D, 0x00),
		COMBINE_CMD(0x2E, 0x6E, 0x2F, 0x04),
		COMBINE_CMD(0x41, 0x04, 0x42, 0x05),
		COMBINE_CMD(0x47, 0x46, 0x76, 0x80),
		COMBINE_CMD(0x77, 0x0C, 0x80, 0x04),
		COMBINE_CMD(0xAF, 0x22, 0x46, 0x08),
		COMBINE_CMD(0xAA, 0x80, 0x1D, 0x00),
		COMBINE_CMD(0x1E, 0x04, 0x6C, 0x40),
		COMBINE_CMD(0x9E, 0xB8, 0x6F, 0x00),
		COMBINE_CMD(0x6E, 0x2C, 0x70, 0xD9),
		COMBINE_CMD(0x71, 0xDD, 0x72, 0xCC),
		COMBINE_CMD(0x73, 0x7A, 0x74, 0x02),
		COMBINE_CMD(0x78, 0x1B, 0x89, 0x01),
		COMBINE_CMD(0x6B, 0x20, 0x86, 0x40),
		COMBINE_CMD(0xB0, 0x02, 0xBF, 0x01),
		COMBINE_CMD(0x0A, 0xC3, 0xBF, 0x00),
		COMBINE_CMD(0x7F, 0x56, 0x08, 0x10),
		COMBINE_CMD(0x30, 0x8D, 0x31, 0x08),
		COMBINE_CMD(0x32, 0x28, 0x33, 0x5C),
		COMBINE_CMD(0x34, 0x38, 0x35, 0x38),
		COMBINE_CMD(0x3A, 0xB6, 0x56, 0x92),
		COMBINE_CMD(0x59, 0x48, 0x5A, 0x01),
		COMBINE_CMD(0x61, 0x18, 0x64, 0xE0),
		COMBINE_CMD(0x85, 0x40, 0x8A, 0x00),
		COMBINE_CMD(0x91, 0x40, 0x94, 0xE0),
		COMBINE_CMD(0x9B, 0x8F, 0x9F, 0xD5),
		COMBINE_CMD(0xA4, 0x87, 0xA6, 0x02),
		COMBINE_CMD(0xA7, 0x80, 0xA9, 0x4C),
		COMBINE_CMD(0x45, 0x09, 0x5B, 0xA5),
		COMBINE_CMD(0x5C, 0x8C, 0x5D, 0x87),
		COMBINE_CMD(0x5E, 0xCE, 0x65, 0x3B),
		COMBINE_CMD(0x66, 0x80, 0x67, 0x41),
		COMBINE_CMD(0x68, 0x00, 0x69, 0x7C),
		COMBINE_CMD(0x6A, 0x2B, 0x7A, 0xCA),
		COMBINE_CMD(0x8D, 0x6F, 0x8F, 0x94),
		COMBINE_CMD(0xA5, 0x0F, 0xB7, 0x21),
		COMBINE_CMD(0x97, 0x20, 0x13, 0x81),
		COMBINE_CMD(0x96, 0x84, 0x4A, 0x01),
		COMBINE_CMD(0xB1, 0x00, 0xA1, 0x0F),
		COMBINE_CMD(0xB5, 0x44, 0xA3, 0x40),
		COMBINE_CMD(0xBF, 0x01, 0x03, 0x01),
		COMBINE_CMD(0x04, 0x80, 0x05, 0x32),
		COMBINE_CMD(0xBF, 0x00, 0x50, 0x02),
		COMBINE_CMD(0x49, 0x40, 0x7E, 0x4C),
		COMBINE_CMD(0x8C, 0xFF, 0x8E, 0x00),
		COMBINE_CMD(0x8B, 0x01, 0xBD, 0x10),
		COMBINE_CMD(0xA0, 0x20, 0xBC, 0x12),
		COMBINE_CMD(0x82, 0x00, 0x19, 0x20),
		COMBINE_CMD(0x1B, 0x4F, 0x12, 0x20),
		COMBINE_CMD(0x48, 0x86, 0x48, 0x06),
	}
};

isp_fcs_data_for_k306p_t fcs_data_k306p_binning_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x06F1,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_k306p_t),
		.dtcm_addr = FCS_SRAM_ADDR,
		.i2c_id = 3,
		.i2c_device_cnt = 1,
		.i2c_speed_mode = I2CFastSpeed,
		.i2c_speed = 2000,
		.i2c_timeout = 10000,
		.timer_id = 3,
		.adc_id = 0xFF,   // use 1 gpio
		.pwm_id = 0xFF,   // same function as ir_led
		.gpio_cnt = 4,
		.gpio_list = {
			[0] = PIN_A5,   // pwr_ctrl
			[1] = PIN_E4,  //reset  mapping to E0
			[2] = PIN_D11, //pwdn
			[3] = PIN_E0,
		}, //pwdn

		.i2c_scl = PIN_D12,
		.i2c_sda = PIN_D10,
		.snr_clk_pin = PIN_D13,
		.adc_th_num = ADC_TH_ITEM,
		.adc_th_table_num = ADC_TH_SET_NUM,
		.adc_value_byte = 2,
		.wait_i2c_delay_us = 4000,
		.snr_timeout_us = 5000,
		.adc_trig_delay = 1000
	},
	.i2c_info = {
		.addr_len = 1,
		.data_len = 1,
#if(PROJECT_LITT)
		.i2c_slave_addr = 0x46
#else
		.i2c_slave_addr = 0x40
#endif
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 0, 100),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 0, 100),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),				//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 5 ms

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 0),
#if(PROJECT_LITT)
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 15, 0),					// delay 15 ms
#else
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 10, 0),					// delay 10 ms
#endif

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms

//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms


		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 128, 64),
		COMBINE_CMD(0x12, 0x62, 0x48, 0x86),
		COMBINE_CMD(0x48, 0x06, 0x0E, 0x11),
		COMBINE_CMD(0x0F, 0x2C, 0x10, 0x48),
		COMBINE_CMD(0x0C, 0x00, 0x0D, 0xA0),
		COMBINE_CMD(0x57, 0x67, 0x58, 0x1F),
		COMBINE_CMD(0x5F, 0x41, 0x60, 0x20),
		COMBINE_CMD(0x20, 0xA0, 0x21, 0x05),
		COMBINE_CMD(0x22, 0xDC, 0x23, 0x05),
		COMBINE_CMD(0x24, 0x82, 0x25, 0xD6),
		COMBINE_CMD(0x26, 0x22, 0x27, 0xB6),
		COMBINE_CMD(0x28, 0x09, 0x29, 0x04),
		COMBINE_CMD(0x2A, 0xB0, 0x2B, 0x14),
		COMBINE_CMD(0x2C, 0x00, 0x2D, 0x00),
		COMBINE_CMD(0x2E, 0x6F, 0x2F, 0x04),
		COMBINE_CMD(0x41, 0x06, 0x42, 0x05),
		COMBINE_CMD(0x47, 0x46, 0x76, 0x45),
		COMBINE_CMD(0x77, 0x06, 0x80, 0x02),
		COMBINE_CMD(0xAB, 0x00, 0xAF, 0x12),
		COMBINE_CMD(0x50, 0x03, 0x46, 0x0A),
		COMBINE_CMD(0xAA, 0xA0, 0x1D, 0x00),
		COMBINE_CMD(0x1E, 0x04, 0x6C, 0x40),
		COMBINE_CMD(0x9E, 0xB8, 0x6F, 0x00),
		COMBINE_CMD(0x6E, 0x2C, 0x70, 0x6D),
		COMBINE_CMD(0x71, 0x6D, 0x72, 0x68),
		COMBINE_CMD(0x73, 0x46, 0x74, 0x02),
		COMBINE_CMD(0x78, 0x1B, 0x89, 0x01),
		COMBINE_CMD(0x6B, 0x20, 0x86, 0x40),
		COMBINE_CMD(0xB0, 0x02, 0xBF, 0x01),
		COMBINE_CMD(0x0A, 0xC3, 0xBF, 0x00),
		COMBINE_CMD(0x7F, 0x56, 0x08, 0x10),
		COMBINE_CMD(0x30, 0x8D, 0x31, 0x08),
		COMBINE_CMD(0x32, 0x28, 0x33, 0x5C),
		COMBINE_CMD(0x34, 0x38, 0x35, 0x38),
		COMBINE_CMD(0x3A, 0xB6, 0x56, 0x92),
		COMBINE_CMD(0x59, 0x48, 0x5A, 0x01),
		COMBINE_CMD(0x61, 0x18, 0x64, 0xE0),
		COMBINE_CMD(0x85, 0x40, 0x8A, 0x00),
		COMBINE_CMD(0x91, 0x40, 0x94, 0xE0),
		COMBINE_CMD(0x9B, 0x8F, 0x9F, 0xD5),
		COMBINE_CMD(0xA4, 0x87, 0xA6, 0x02),
		COMBINE_CMD(0xA7, 0x80, 0xA9, 0x4C),
		COMBINE_CMD(0x45, 0x09, 0x5B, 0xA5),
		COMBINE_CMD(0x5C, 0x8C, 0x5D, 0x87),
		COMBINE_CMD(0x5E, 0xCE, 0x65, 0x3B),
		COMBINE_CMD(0x66, 0x80, 0x67, 0x41),
		COMBINE_CMD(0x68, 0x00, 0x69, 0x7C),
		COMBINE_CMD(0x6A, 0x2B, 0x7A, 0xCA),
		COMBINE_CMD(0x8D, 0x6F, 0x8F, 0x94),
		COMBINE_CMD(0xA5, 0x0F, 0xB7, 0x21),
		COMBINE_CMD(0x97, 0x20, 0x13, 0x81),
		COMBINE_CMD(0x96, 0x84, 0x4A, 0x01),
		COMBINE_CMD(0xB1, 0x00, 0xA1, 0x0F),
		COMBINE_CMD(0xB5, 0x44, 0xA3, 0x40),
		COMBINE_CMD(0xBF, 0x01, 0x03, 0x01),
		COMBINE_CMD(0x04, 0x80, 0x05, 0x32),
		COMBINE_CMD(0xBF, 0x00, 0x49, 0x40),
		COMBINE_CMD(0x7E, 0x4C, 0x8C, 0xFF),
		COMBINE_CMD(0x8E, 0x00, 0x8B, 0x01),
		COMBINE_CMD(0xBD, 0x10, 0xA0, 0x20),
		COMBINE_CMD(0xBC, 0x12, 0x82, 0x00),
		COMBINE_CMD(0x19, 0x20, 0x1B, 0x4F),
		COMBINE_CMD(0x12, 0x22, 0x48, 0x86),
		COMBINE_CMD(0x48, 0x06, 0x48, 0x06),
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_k306p_v1.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_k306p_v0, sizeof(isp_fcs_data_for_k306p_t), 1, ofile);
	fclose(ofile);

	/* Open files */
	ofile = fopen("fcs_data_k306p_hd_v0.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_k306p_binning_v0, sizeof(isp_fcs_data_for_k306p_t), 1, ofile);
	fclose(ofile);

	return 0;
}







