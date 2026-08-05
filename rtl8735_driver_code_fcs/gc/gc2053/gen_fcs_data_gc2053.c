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
#define SENSOR_CMD_CNT 		68

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_gc2053_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	//uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
} isp_fcs_data_for_gc2053_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_gc2053_t fcs_data_gc2053_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x5305,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_gc2053_t),
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
		.adc_th_num = 0,
		.adc_th_table_num = 0,
		.adc_value_byte = 2,
		.wait_i2c_delay_us = 4000,
		.snr_timeout_us = 5000,
		.adc_trig_delay = 1000
	},
	.i2c_info = {
		.addr_len = 1,
		.data_len = 1,
		.i2c_slave_addr = 0x37
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_27M, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 116, (116) >> 1),
		COMBINE_CMD(0xfe, 0x80, 0xfe, 0x80),
		COMBINE_CMD(0xfe, 0x80, 0xfe, 0x00),
		COMBINE_CMD(0xf2, 0x00, 0xf3, 0x00),
		COMBINE_CMD(0xf4, 0x36, 0xf5, 0xc0),
		COMBINE_CMD(0xf6, 0x44, 0xf7, 0x01),
		COMBINE_CMD(0xf8, 0x2c, 0xf9, 0x42),
		COMBINE_CMD(0xfc, 0x8e, 0xfe, 0x00),
		COMBINE_CMD(0x87, 0x18, 0xee, 0x30),
		COMBINE_CMD(0xd0, 0xb7, 0x03, 0x04),
		COMBINE_CMD(0x04, 0x10, 0x05, 0x04),
		COMBINE_CMD(0x06, 0x4c, 0x07, 0x00),
		COMBINE_CMD(0x08, 0x0c, 0x09, 0x00),
		COMBINE_CMD(0x0a, 0x02, 0x0b, 0x00),
		COMBINE_CMD(0x0c, 0x02, 0x12, 0xe2),
		COMBINE_CMD(0x13, 0x16, 0x19, 0x0a),
		COMBINE_CMD(0x21, 0x1c, 0x28, 0x0a),
		COMBINE_CMD(0x29, 0x24, 0x2b, 0x04),
		COMBINE_CMD(0x32, 0xf8, 0x37, 0x03),
		COMBINE_CMD(0x39, 0x17, 0x44, 0x40),
		COMBINE_CMD(0x46, 0x0d, 0x4b, 0x20),
		COMBINE_CMD(0x4e, 0x08, 0x55, 0x20),
		COMBINE_CMD(0x66, 0x05, 0x67, 0x05),
		COMBINE_CMD(0x77, 0x00, 0x78, 0x20),
		COMBINE_CMD(0x7c, 0xb3, 0x8c, 0x12),
		COMBINE_CMD(0x8d, 0x92, 0x90, 0x00),
		COMBINE_CMD(0x41, 0x04, 0x42, 0x64),
		COMBINE_CMD(0x9d, 0x10, 0xce, 0x6c),
		COMBINE_CMD(0xd0, 0xd7, 0xd2, 0x41),
		COMBINE_CMD(0xd3, 0x54, 0xe6, 0x40),
		COMBINE_CMD(0xb6, 0xC0, 0xb0, 0x58),
		COMBINE_CMD(0x26, 0x20, 0xfe, 0x01),
		COMBINE_CMD(0x40, 0x23, 0x60, 0x40),
		COMBINE_CMD(0x87, 0x50, 0x94, 0x01),
		COMBINE_CMD(0x95, 0x04, 0x96, 0x38),
		COMBINE_CMD(0x97, 0x07, 0x98, 0x88),
		COMBINE_CMD(0xfe, 0x01, 0x01, 0x04),
		COMBINE_CMD(0x02, 0x89, 0x04, 0x01),
		COMBINE_CMD(0x50, 0x1c, 0x89, 0x03),
		COMBINE_CMD(0xfe, 0x04, 0x28, 0x86),
		COMBINE_CMD(0x29, 0x86, 0x2a, 0x86),
		COMBINE_CMD(0x2b, 0x68, 0x2c, 0x68),
		COMBINE_CMD(0x2d, 0x68, 0x2e, 0x68),
		COMBINE_CMD(0x2f, 0x68, 0x30, 0x4f),
		COMBINE_CMD(0x31, 0x68, 0x32, 0x67),
		COMBINE_CMD(0x33, 0x66, 0x34, 0x66),
		COMBINE_CMD(0x35, 0x66, 0x36, 0x66),
		COMBINE_CMD(0x37, 0x66, 0x38, 0x62),
		COMBINE_CMD(0x39, 0x62, 0x3a, 0x62),
		COMBINE_CMD(0x3b, 0x62, 0x3c, 0x62),
		COMBINE_CMD(0x3d, 0x62, 0x3e, 0x62),
		COMBINE_CMD(0x3f, 0x62, 0xfe, 0x01),
		COMBINE_CMD(0x9a, 0x03, 0x99, 0x01),
		COMBINE_CMD(0xfe, 0x00, 0x7b, 0x2a),
		COMBINE_CMD(0x23, 0x2d, 0xfe, 0x03),
		COMBINE_CMD(0x01, 0x27, 0x02, 0x56),
		COMBINE_CMD(0x03, 0xb6, 0x12, 0x88),
		COMBINE_CMD(0x13, 0x07, 0x15, 0x12),
		COMBINE_CMD(0xfe, 0x00, 0x3e, 0x91)
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_gc2053_v0.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_gc2053_v0, sizeof(isp_fcs_data_for_gc2053_t), 1, ofile);
	fclose(ofile);
	return 0;
}







