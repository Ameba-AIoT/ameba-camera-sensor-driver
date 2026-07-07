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

typedef struct isp_fcs_data_for_k351_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
}isp_fcs_data_for_k351_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_k351_t fcs_data_k351_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x5104,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_k351_t),
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
		.gpio_list = {	[0] = PIN_A5,   // pwr_ctrl
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
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, 0, 1),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),

//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms
						
//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 1),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms
						
//	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
						COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),				//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 5 ms
						
//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 0),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms
						
//	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, 1),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms
						
//	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
						COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, 0),
						COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0),					// delay 1 ms
						
						
						COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 108, 54),
		COMBINE_CMD(0x12, 0x40,	0xAD, 0x01),
		COMBINE_CMD(0xAD, 0x00,	0x0E, 0x11),
		COMBINE_CMD(0x0F, 0x0C,	0x10, 0x3F),
		COMBINE_CMD(0x0C, 0x00,	0x67, 0xA2),
		COMBINE_CMD(0x0D, 0x21,	0x64, 0x31),
		COMBINE_CMD(0x65, 0x9D,	0xBE, 0x18),
		COMBINE_CMD(0xBF, 0x60,	0xBC, 0xC0),
		COMBINE_CMD(0x20, 0x2C,	0x21, 0x01),
		COMBINE_CMD(0x22, 0x34,	0x23, 0x08),
		COMBINE_CMD(0x24, 0xF6,	0x25, 0xD8),
		COMBINE_CMD(0x26, 0x71,	0x27, 0x0C),
		COMBINE_CMD(0x28, 0x0D,	0x29, 0x00),
		COMBINE_CMD(0x2B, 0x10,	0x2C, 0x00),
		COMBINE_CMD(0x2D, 0x05,	0x2E, 0xFB),
		COMBINE_CMD(0x2F, 0x14,	0x30, 0xF8),
		COMBINE_CMD(0x87, 0xC5,	0x9D, 0xB9),
		COMBINE_CMD(0xAC, 0x00,	0x1D, 0x00),
		COMBINE_CMD(0x1E, 0x10,	0x3A, 0xD5),
		COMBINE_CMD(0x3B, 0x9B,	0x3C, 0x6D),
		COMBINE_CMD(0x3D, 0x59,	0x3E, 0x12),
		COMBINE_CMD(0x3F, 0x14,	0x42, 0x11),
		COMBINE_CMD(0x43, 0x00,	0x70, 0xA0),
		COMBINE_CMD(0x71, 0x24,	0x76, 0x08),
		COMBINE_CMD(0x06, 0x00,	0x08, 0x04),
		COMBINE_CMD(0x9F, 0x4C,	0x7E, 0x0B),
		COMBINE_CMD(0x31, 0x04,	0x32, 0x04),
		COMBINE_CMD(0x33, 0xCC,	0x38, 0xCA),
		COMBINE_CMD(0x6F, 0x00,	0x78, 0x49),
		COMBINE_CMD(0xB0, 0x14,	0xB1, 0xA0),
		COMBINE_CMD(0xB2, 0x24,	0xB3, 0x14),
		COMBINE_CMD(0xB5, 0x50,	0xB6, 0x57),
		COMBINE_CMD(0xB8, 0x06,	0xB9, 0x08),
		COMBINE_CMD(0xBA, 0x8B,	0xBB, 0x8B),
		COMBINE_CMD(0xC3, 0x90,	0xF9, 0x00),
		COMBINE_CMD(0x56, 0xF1,	0x57, 0x60),
		COMBINE_CMD(0x58, 0x42,	0x59, 0x66),
		COMBINE_CMD(0x5A, 0x80,	0x5B, 0x10),
		COMBINE_CMD(0x5C, 0x10,	0x5D, 0x49),
		COMBINE_CMD(0x60, 0x60,	0x61, 0x00),
		COMBINE_CMD(0x62, 0x60,	0x68, 0x00),
		COMBINE_CMD(0x69, 0x90,	0xA5, 0x08),
		COMBINE_CMD(0xAA, 0x00,	0xC1, 0xC0),
		COMBINE_CMD(0xC4, 0x00,	0xD4, 0xFF),
		COMBINE_CMD(0xEB, 0x15,	0xEC, 0x03),
		COMBINE_CMD(0xE1, 0xF2,	0x80, 0x81),
		COMBINE_CMD(0x81, 0x44,	0xFB, 0x20),
		COMBINE_CMD(0xFC, 0x32,	0xFA, 0x01),
		COMBINE_CMD(0x16, 0xFF,	0x17, 0x08),
		COMBINE_CMD(0x49, 0x10,	0x85, 0x00),
		COMBINE_CMD(0xB4, 0x01,	0xD2, 0x80),
		COMBINE_CMD(0xD0, 0x00,	0xD3, 0x2D),
		COMBINE_CMD(0x39, 0x8A,	0xFF, 0x01),
		COMBINE_CMD(0x74, 0x04,	0xFF, 0x00),
		COMBINE_CMD(0x89, 0x00,	0x12, 0x00),
	}
};

isp_fcs_data_for_k351_t fcs_data_k351_hdr_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x51F0,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_k351_t),
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
		.gpio_list = {	[0] = PIN_A5,   // pwr_ctrl
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
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),					
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),					
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),				
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),				
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),					
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),					
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 118, 59),
		COMBINE_CMD(0x12,0x48,0xAD,0x01),
		COMBINE_CMD(0xAD,0x00,0x0E,0x11),
		COMBINE_CMD(0x0F,0x0C,0x10,0x2A),
		COMBINE_CMD(0x0C,0x00,0x67,0x91),
		COMBINE_CMD(0x0D,0x20,0x64,0x31),
		COMBINE_CMD(0x65,0x9D,0xBE,0x18),
		COMBINE_CMD(0xBF,0x60,0xBC,0xC0),
		COMBINE_CMD(0x20,0x96,0x21,0x00),
		COMBINE_CMD(0x22,0x34,0x23,0x08),
		COMBINE_CMD(0x24,0xF6,0x25,0xD8),
		COMBINE_CMD(0x26,0x71,0x27,0x08),
		COMBINE_CMD(0x28,0x0C,0x29,0x00),
		COMBINE_CMD(0x2B,0x10,0x2C,0x00),
		COMBINE_CMD(0x2D,0x05,0x2E,0xFB),
		COMBINE_CMD(0x2F,0x14,0x30,0xF8),
		COMBINE_CMD(0x87,0xC5,0x9D,0xB9),
		COMBINE_CMD(0xAC,0x00,0x1D,0x00),
		COMBINE_CMD(0x1E,0x10,0x3A,0x49),
		COMBINE_CMD(0x3B,0x2D,0x3C,0x29),
		COMBINE_CMD(0x3D,0x25,0x3E,0x12),
		COMBINE_CMD(0x3F,0x24,0x42,0x12),
		COMBINE_CMD(0x43,0x00,0x70,0xA0),
		COMBINE_CMD(0x71,0x24,0x76,0x08),
		COMBINE_CMD(0x06,0x00,0x08,0x04),
		COMBINE_CMD(0x9F,0x4C,0x7E,0x0B),
		COMBINE_CMD(0x31,0x03,0x32,0x03),
		COMBINE_CMD(0x33,0xC8,0x34,0x04),
		COMBINE_CMD(0x38,0xCA,0x6F,0x00),
		COMBINE_CMD(0x78,0x49,0xB0,0x14),
		COMBINE_CMD(0xB1,0xA0,0xB2,0x1C),
		COMBINE_CMD(0xB3,0x0E,0xB5,0x50),
		COMBINE_CMD(0xB6,0x57,0xB8,0x06),
		COMBINE_CMD(0xB9,0x08,0xBA,0x8B),
		COMBINE_CMD(0xBB,0x8B,0xC3,0x90),
		COMBINE_CMD(0xF9,0x00,0x56,0xF1),
		COMBINE_CMD(0x57,0x60,0x58,0x42),
		COMBINE_CMD(0x59,0x66,0x5A,0x80),
		COMBINE_CMD(0x5B,0x10,0x5C,0x10),
		COMBINE_CMD(0x5D,0x49,0x60,0x60),
		COMBINE_CMD(0x61,0x00,0x62,0x60),
		COMBINE_CMD(0x68,0x00,0x69,0x90),
		COMBINE_CMD(0xA5,0x08,0xAA,0x00),
		COMBINE_CMD(0xC1,0xC0,0xC4,0x00),
		COMBINE_CMD(0xD4,0xFF,0xEB,0x15),
		COMBINE_CMD(0xEC,0x03,0xE1,0xF2),
		COMBINE_CMD(0x80,0x81,0x81,0x44),
		COMBINE_CMD(0xFB,0x20,0xFC,0x32),
		COMBINE_CMD(0xFA,0x01,0x16,0xFF),
		COMBINE_CMD(0x17,0x08,0x49,0x10),
		COMBINE_CMD(0x85,0x00,0xB4,0x01),
		COMBINE_CMD(0xD2,0x80,0xD0,0x00),
		COMBINE_CMD(0xD3,0x2D,0x39,0x8A),
		COMBINE_CMD(0xFF,0x01,0x74,0x04),
		COMBINE_CMD(0xFF,0x00,0x1B,0x07),
		COMBINE_CMD(0x05,0x07,0x7D,0x21),
		COMBINE_CMD(0xA4,0x19,0x88,0x08),
		COMBINE_CMD(0x37,0x44,0x44,0x64),
		COMBINE_CMD(0x04,0xC0,0x6F,0x00),
		COMBINE_CMD(0x89,0x00,0x12,0x08),
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_k351_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_k351_v0,sizeof(isp_fcs_data_for_k351_t), 1, ofile);
	fclose(ofile);
	
	ofile = fopen("fcs_data_k351_hdr_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_k351_hdr_v0,sizeof(isp_fcs_data_for_k351_t), 1, ofile);
	fclose(ofile);

	return 0;
}







