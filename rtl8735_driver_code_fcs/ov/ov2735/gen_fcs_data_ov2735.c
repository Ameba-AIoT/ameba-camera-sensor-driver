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
#define SENSOR_CMD_CNT 		100

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_ov2735_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	//uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
}isp_fcs_data_for_ov2735_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


isp_fcs_data_for_ov2735_t fcs_data_ov2735_v1 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x3501,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_ov2735_t),
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
		.i2c_slave_addr = 0x3d 
	},
	.sensor_init_data  = {	
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 4, 0),	//6
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 4, 0),	//8
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_8, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 110, 55),		
		COMBINE_CMD(0xfd,0x00,0x2f,0x10),
		COMBINE_CMD(0x34,0x00,0x30,0x15),
		COMBINE_CMD(0x33,0x01,0x35,0x20),
		COMBINE_CMD(0xfd,0x01,0x0d,0x10),
		COMBINE_CMD(0x30,0x00,0x03,0x01),
		COMBINE_CMD(0x04,0x8f,0x01,0x01),
		COMBINE_CMD(0x09,0x00,0x0a,0x20),
		COMBINE_CMD(0x06,0x0a,0x24,0x10),
		COMBINE_CMD(0x01,0x01,0xfb,0x73),
		COMBINE_CMD(0x01,0x01,0xfd,0x01),
		COMBINE_CMD(0x1a,0x6b,0x1c,0xea),
		COMBINE_CMD(0x16,0x0c,0x21,0x00),
		COMBINE_CMD(0x11,0x63,0x19,0xc3),
		COMBINE_CMD(0x26,0x5a,0x29,0x01),
		COMBINE_CMD(0x33,0x6f,0x2a,0xd2),
		COMBINE_CMD(0x2c,0x40,0xd0,0x02),
		COMBINE_CMD(0xd1,0x01,0xd2,0x20),
		COMBINE_CMD(0xd3,0x04,0xd4,0x2a),
		COMBINE_CMD(0x50,0x00,0x51,0x2c),
		COMBINE_CMD(0x52,0x29,0x53,0x00),
		COMBINE_CMD(0x55,0x44,0x58,0x29),
		COMBINE_CMD(0x5a,0x00,0x5b,0x00),
		COMBINE_CMD(0x5d,0x00,0x64,0x2f),
		COMBINE_CMD(0x66,0x62,0x68,0x5b),
		COMBINE_CMD(0x75,0x46,0x76,0x36),
		COMBINE_CMD(0x77,0x4f,0x78,0xef),
		COMBINE_CMD(0x72,0xcf,0x73,0x36),
		COMBINE_CMD(0x7d,0x0d,0x7e,0x0d),
		COMBINE_CMD(0x8a,0x77,0x8b,0x77),
		COMBINE_CMD(0xfd,0x01,0xb1,0x83),
		COMBINE_CMD(0xb3,0x0b,0xb4,0x14),
		COMBINE_CMD(0x9d,0x40,0xa1,0x05),
		COMBINE_CMD(0x94,0x44,0x95,0x33),
		COMBINE_CMD(0x96,0x1f,0x98,0x45),
		COMBINE_CMD(0x9c,0x10,0xb5,0x70),
		COMBINE_CMD(0xa0,0x01,0x25,0xe0),
		COMBINE_CMD(0x20,0x7b,0x8f,0x88),
		COMBINE_CMD(0x91,0x40,0xfd,0x01),
		COMBINE_CMD(0xfd,0x02,0xa1,0x04),
		COMBINE_CMD(0xa3,0x40,0xa5,0x02),
		COMBINE_CMD(0xa7,0xc4,0xfd,0x01),
		COMBINE_CMD(0x86,0x77,0x89,0x77),
		COMBINE_CMD(0x87,0x74,0x88,0x74),
		COMBINE_CMD(0xfc,0xe0,0xfe,0xe0),
		COMBINE_CMD(0xf0,0x40,0xf1,0x40),
		COMBINE_CMD(0xf2,0x40,0xf3,0x40),
		COMBINE_CMD(0xfd,0x02,0xa0,0x00),
		COMBINE_CMD(0xa1,0x08,0xa2,0x04),
		COMBINE_CMD(0xa3,0x50,0xa4,0x00),
		COMBINE_CMD(0xa5,0x06,0xa6,0x03),
		COMBINE_CMD(0xa7,0xcc,0xfd,0x01),
		COMBINE_CMD(0x8e,0x07,0x8f,0x88),
		COMBINE_CMD(0x90,0x04,0x91,0x40),
		COMBINE_CMD(0xfd,0x01,0x06,0xe0),
		COMBINE_CMD(0x01,0x01,0x01,0x01)
	}
};


int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_ov2735_v1.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_ov2735_v1,sizeof(isp_fcs_data_for_ov2735_t), 1, ofile);
	fclose(ofile);

	return 0;
}







