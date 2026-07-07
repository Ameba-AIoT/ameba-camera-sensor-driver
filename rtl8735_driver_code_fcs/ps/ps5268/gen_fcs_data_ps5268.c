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
#define SENSOR_CMD_CNT 		300

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_ps5268_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
}isp_fcs_data_for_ps5268_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_ps5268_t fcs_data_ps5268_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x6800,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_ps5268_t),
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
		.addr_len = 2,
		.data_len = 1,
		.i2c_slave_addr = 0x48 
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 8, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),			//set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 1, 0), //5	
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0), //5	
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 3000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0), //3
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0), //5
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),	//set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 2000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 0, 38),
		COMBINE_CMD16(0x010B, 0x07), 
		COMBINE_CMD16(0x0114, 0x12), 
		COMBINE_CMD16(0x0115, 0xC0), 
		COMBINE_CMD16(0x0178, 0xC0), 
		COMBINE_CMD16(0x0179, 0x2A), 
		COMBINE_CMD16(0x022E, 0x0E), 
		COMBINE_CMD16(0x022F, 0x19), 
		COMBINE_CMD16(0x022D, 0x01), 
		COMBINE_CMD16(0x0226, 0xB1), 
		COMBINE_CMD16(0x0227, 0x39), 
		COMBINE_CMD16(0x021C, 0x00), 
		COMBINE_CMD16(0x0233, 0x70), 
		COMBINE_CMD16(0x024B, 0x05), 
		COMBINE_CMD16(0x024D, 0x11), 
		COMBINE_CMD16(0x0252, 0x16), 
		COMBINE_CMD16(0x0253, 0x26), 
		COMBINE_CMD16(0x0254, 0x61), 
		COMBINE_CMD16(0x0255, 0x11), 
		COMBINE_CMD16(0x0664, 0x02), 
		COMBINE_CMD16(0x0665, 0xAD), 
		COMBINE_CMD16(0x0B02, 0x02), 
		COMBINE_CMD16(0x0B0A, 0xFF), 
		COMBINE_CMD16(0x0B0C, 0x00), 
		COMBINE_CMD16(0x1200, 0x00), 
		COMBINE_CMD16(0x1201, 0x01), 
		COMBINE_CMD16(0x1300, 0x00), 
		COMBINE_CMD16(0x1301, 0x01), 
		COMBINE_CMD16(0x1409, 0x1A), 
		COMBINE_CMD16(0x140A, 0x15), 
		COMBINE_CMD16(0x1411, 0x01), 
		COMBINE_CMD16(0x1415, 0x04), 
		COMBINE_CMD16(0x1417, 0x03), 
		COMBINE_CMD16(0x1418, 0x02), 
		COMBINE_CMD16(0x1406, 0x04), 
		COMBINE_CMD16(0x1410, 0x02), 
		COMBINE_CMD16(0x140F, 0x01), 
		COMBINE_CMD16(0x0111, 0x01), 
		COMBINE_CMD16(0x010F, 0x01)
	}                
};


int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_ps5268_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_ps5268_v0,sizeof(isp_fcs_data_for_ps5268_t), 1, ofile);
	fclose(ofile);

	return 0;
}







