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
#define SENSOR_CMD_CNT 		200

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_f51_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
} isp_fcs_data_for_f51_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_f51_t fcs_data_f51_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x5100,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_f51_t),
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
		.i2c_slave_addr = 0x40
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_27M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 118, 59),
		COMBINE_CMD(0x12, 0x40, 0x48, 0x8B),
		COMBINE_CMD(0x48, 0x0B, 0x0E, 0x12),
		COMBINE_CMD(0x0F, 0x04, 0x10, 0x50),
		COMBINE_CMD(0x11, 0x80, 0x0D, 0x50),
		COMBINE_CMD(0x57, 0x60, 0x58, 0x1B),
		COMBINE_CMD(0x5F, 0x42, 0x60, 0x2B),
		COMBINE_CMD(0x61, 0x08, 0x07, 0x08),
		COMBINE_CMD(0x20, 0x58, 0x21, 0x02),
		COMBINE_CMD(0x22, 0xD0, 0x23, 0x07),
		COMBINE_CMD(0x24, 0x82, 0x25, 0x08),
		COMBINE_CMD(0x26, 0x61, 0x27, 0x4E),
		COMBINE_CMD(0x28, 0x11, 0x29, 0x02),
		COMBINE_CMD(0x2A, 0x48, 0x2B, 0x12),
		COMBINE_CMD(0x2C, 0x02, 0x2D, 0x00),
		COMBINE_CMD(0x2E, 0x86, 0x2F, 0x44),
		COMBINE_CMD(0x41, 0x04, 0x42, 0x03),
		COMBINE_CMD(0x46, 0x18, 0x47, 0x42),
		COMBINE_CMD(0x80, 0x01, 0xAF, 0x12),
		COMBINE_CMD(0xBD, 0x08, 0xBE, 0x06),
		COMBINE_CMD(0xAB, 0x00, 0x1D, 0x00),
		COMBINE_CMD(0x1E, 0x04, 0x6C, 0x40),
		COMBINE_CMD(0x70, 0xD1, 0x71, 0x8B),
		COMBINE_CMD(0x72, 0x6D, 0x73, 0x49),
		COMBINE_CMD(0x75, 0x1B, 0x74, 0x12),
		COMBINE_CMD(0x89, 0x11, 0x0C, 0x00),
		COMBINE_CMD(0x6B, 0x00, 0x86, 0x40),
		COMBINE_CMD(0x6E, 0x2C, 0x78, 0x14),
		COMBINE_CMD(0x76, 0x67, 0x2F, 0x44),
		COMBINE_CMD(0x31, 0x10, 0x32, 0x25),
		COMBINE_CMD(0x33, 0x5C, 0x34, 0x23),
		COMBINE_CMD(0x35, 0x2B, 0x3A, 0xA1),
		COMBINE_CMD(0x3B, 0xA0, 0x3C, 0x2B),
		COMBINE_CMD(0x3D, 0x00, 0x3E, 0x00),
		COMBINE_CMD(0x3F, 0x8E, 0x40, 0x93),
		COMBINE_CMD(0x56, 0x12, 0x59, 0x40),
		COMBINE_CMD(0x5A, 0x10, 0x85, 0x3A),
		COMBINE_CMD(0xBF, 0x01, 0x4D, 0x08),
		COMBINE_CMD(0x53, 0x01, 0xBF, 0x00),
		COMBINE_CMD(0x9C, 0xA1, 0x62, 0x21),
		COMBINE_CMD(0x64, 0xE0, 0x65, 0x33),
		COMBINE_CMD(0x66, 0x13, 0x67, 0x57),
		COMBINE_CMD(0x68, 0x00, 0x69, 0xFC),
		COMBINE_CMD(0x6A, 0x44, 0x7A, 0x40),
		COMBINE_CMD(0x8F, 0x10, 0xBF, 0x01),
		COMBINE_CMD(0x45, 0x07, 0x46, 0x3C),
		COMBINE_CMD(0x47, 0x88, 0x48, 0xFC),
		COMBINE_CMD(0x49, 0x21, 0x4B, 0x42),
		COMBINE_CMD(0xBF, 0x00, 0x97, 0xA2),
		COMBINE_CMD(0x13, 0x81, 0x96, 0x04),
		COMBINE_CMD(0x4A, 0x05, 0x7E, 0xC9),
		COMBINE_CMD(0xA7, 0x04, 0x50, 0x02),
		COMBINE_CMD(0x49, 0x10, 0x7B, 0x4A),
		COMBINE_CMD(0x7C, 0x0A, 0x7F, 0x57),
		COMBINE_CMD(0x90, 0x00, 0x8C, 0xFF),
		COMBINE_CMD(0x8D, 0xC7, 0x8E, 0x80),
		COMBINE_CMD(0x8B, 0x01, 0xBF, 0x01),
		COMBINE_CMD(0x4E, 0x11, 0xBF, 0x00),
		COMBINE_CMD(0x82, 0x00, 0x19, 0x20),
		COMBINE_CMD(0x12, 0x30, 0x00, 0x00)
	}
};

isp_fcs_data_for_f51_t fcs_data_f51_hdr_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x51F0,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_f51_t),
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
		.i2c_slave_addr = 0x40
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_27M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 122, 61),
		COMBINE_CMD(0x12, 0x48, 0x48, 0x8B),
		COMBINE_CMD(0x48, 0x0B, 0x0E, 0x12),
		COMBINE_CMD(0x0F, 0x04, 0x10, 0x50),
		COMBINE_CMD(0x11, 0x80, 0x0D, 0x50),
		COMBINE_CMD(0x57, 0x60, 0x58, 0x1B),
		COMBINE_CMD(0x5F, 0x42, 0x60, 0x2B),
		COMBINE_CMD(0x61, 0x08, 0x07, 0x0B),
		COMBINE_CMD(0x20, 0xF4, 0x21, 0x01),
		COMBINE_CMD(0x22, 0x10, 0x23, 0x0E),
		COMBINE_CMD(0x24, 0x80, 0x25, 0x00),
		COMBINE_CMD(0x26, 0x61, 0x27, 0xEB),
		COMBINE_CMD(0x28, 0x27, 0x29, 0x01),
		COMBINE_CMD(0x2A, 0xE4, 0x2B, 0x11),
		COMBINE_CMD(0x2C, 0x02, 0x2D, 0x00),
		COMBINE_CMD(0x2E, 0x86, 0x2F, 0x44),
		COMBINE_CMD(0x41, 0x04, 0x42, 0x03),
		COMBINE_CMD(0x46, 0x1C, 0x47, 0x42),
		COMBINE_CMD(0x80, 0x01, 0xAF, 0x12),
		COMBINE_CMD(0xBD, 0x00, 0xBE, 0x06),
		COMBINE_CMD(0xAB, 0x00, 0x1D, 0x00),
		COMBINE_CMD(0x1E, 0x04, 0x6C, 0x40),
		COMBINE_CMD(0x70, 0xD5, 0x71, 0x96),
		COMBINE_CMD(0x72, 0x6D, 0x73, 0x49),
		COMBINE_CMD(0x75, 0x96, 0x74, 0x12),
		COMBINE_CMD(0x89, 0x14, 0x0C, 0x00),
		COMBINE_CMD(0x6B, 0x00, 0x86, 0x40),
		COMBINE_CMD(0x6E, 0x2C, 0x78, 0x14),
		COMBINE_CMD(0x76, 0x67, 0x2F, 0x44),
		COMBINE_CMD(0x31, 0x10, 0x32, 0x25),
		COMBINE_CMD(0x33, 0x5C, 0x34, 0x23),
		COMBINE_CMD(0x35, 0x2B, 0x3A, 0xA1),
		COMBINE_CMD(0x3B, 0xA0, 0x3C, 0x2B),
		COMBINE_CMD(0x3D, 0x00, 0x3E, 0x00),
		COMBINE_CMD(0x3F, 0x8E, 0x40, 0x93),
		COMBINE_CMD(0x56, 0x12, 0x59, 0x40),
		COMBINE_CMD(0x5A, 0x10, 0x85, 0x3A),
		COMBINE_CMD(0xBF, 0x01, 0x4D, 0x08),
		COMBINE_CMD(0x53, 0x01, 0xBF, 0x00),
		COMBINE_CMD(0x9C, 0xA1, 0x62, 0x21),
		COMBINE_CMD(0x64, 0xE0, 0x65, 0x33),
		COMBINE_CMD(0x66, 0x13, 0x67, 0x57),
		COMBINE_CMD(0x68, 0x00, 0x69, 0xFC),
		COMBINE_CMD(0x6A, 0x44, 0x7A, 0x40),
		COMBINE_CMD(0x8F, 0x10, 0x9D, 0x01),
		COMBINE_CMD(0xBF, 0x01, 0x45, 0x07),
		COMBINE_CMD(0x46, 0x3C, 0x47, 0x88),
		COMBINE_CMD(0x48, 0xFC, 0x49, 0x21),
		COMBINE_CMD(0x4B, 0x42, 0xBF, 0x00),
		COMBINE_CMD(0x97, 0xA2, 0x13, 0x81),
		COMBINE_CMD(0x96, 0x04, 0x4A, 0x05),
		COMBINE_CMD(0x7E, 0xC9, 0xA7, 0x04),
		COMBINE_CMD(0x50, 0x02, 0x49, 0x10),
		COMBINE_CMD(0x7B, 0x4A, 0x7C, 0x0A),
		COMBINE_CMD(0x7F, 0x57, 0x90, 0x00),
		COMBINE_CMD(0x8C, 0xFF, 0x8D, 0xC7),
		COMBINE_CMD(0x8E, 0x80, 0x8B, 0x01),
		COMBINE_CMD(0xBF, 0x01, 0x4E, 0x11),
		COMBINE_CMD(0xBF, 0x00, 0x82, 0x00),
		COMBINE_CMD(0x19, 0x20, 0x1B, 0x4F),
		COMBINE_CMD(0x06, 0x23, 0x03, 0xFF),
		COMBINE_CMD(0x04, 0xFF, 0x12, 0x38),
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_f51_v0.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_f51_v0, sizeof(isp_fcs_data_for_f51_t), 1, ofile);
	fclose(ofile);

	ofile = fopen("fcs_data_f51_hdr_v0.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_f51_hdr_v0, sizeof(isp_fcs_data_for_f51_t), 1, ofile);
	fclose(ofile);

	return 0;
}







