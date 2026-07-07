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
#define SENSOR_CMD_CNT 		120

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_imx662_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	//uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
}isp_fcs_data_for_imx662_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_imx662_t fcs_data_imx662_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x6200,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_imx662_t),
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
		.addr_len = 2,
		.data_len = 1,
		.i2c_slave_addr = 0x1A 
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),
		//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 2000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 2000);
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 0, 104),
		COMBINE_CMD16(0x03fe, 0xf0),
		COMBINE_CMD16(0x3002, 0x00), 
		COMBINE_CMD16(0x3014, 0x04), 
		COMBINE_CMD16(0x3015, 0x07), 
		COMBINE_CMD16(0x301A, 0x00), 
		COMBINE_CMD16(0x301C, 0x00), 
		COMBINE_CMD16(0x302C, 0xBC), //HMAX 7BC=1980 
		COMBINE_CMD16(0x302D, 0x07), 
		COMBINE_CMD16(0x3050, 0x04), 
		COMBINE_CMD16(0x3051, 0x00), 
		COMBINE_CMD16(0x3054, 0x0E), 
		COMBINE_CMD16(0x3060, 0x16), 
		COMBINE_CMD16(0x3061, 0x01), 
		COMBINE_CMD16(0x30A6, 0x00), 
		COMBINE_CMD16(0x3400, 0x01), 
		COMBINE_CMD16(0x3444, 0xAC), 
		COMBINE_CMD16(0x3460, 0x21), 
		COMBINE_CMD16(0x3492, 0x08), 
		COMBINE_CMD16(0x3B00, 0x39), 
		COMBINE_CMD16(0x3B23, 0x2D), 
		COMBINE_CMD16(0x3B45, 0x04), 
		COMBINE_CMD16(0x3C0A, 0x1F), 
		COMBINE_CMD16(0x3C0B, 0x1E), 
		COMBINE_CMD16(0x3C38, 0x21), 
		COMBINE_CMD16(0x3C44, 0x00), 
		COMBINE_CMD16(0x3CB6, 0xD8), 
		COMBINE_CMD16(0x3CC4, 0xDA), 
		COMBINE_CMD16(0x3E24, 0x79), 
		COMBINE_CMD16(0x3E2C, 0x15), 
		COMBINE_CMD16(0x3EDC, 0x2D), 
		COMBINE_CMD16(0x4498, 0x05), 
		COMBINE_CMD16(0x449C, 0x19), 
		COMBINE_CMD16(0x449D, 0x00), 
		COMBINE_CMD16(0x449E, 0x32), 
		COMBINE_CMD16(0x449F, 0x01), 
		COMBINE_CMD16(0x44A0, 0x92), 
		COMBINE_CMD16(0x44A2, 0x91), 
		COMBINE_CMD16(0x44A4, 0x8C), 
		COMBINE_CMD16(0x44A6, 0x87), 
		COMBINE_CMD16(0x44A8, 0x82), 
		COMBINE_CMD16(0x44AA, 0x78), 
		COMBINE_CMD16(0x44AC, 0x6E), 
		COMBINE_CMD16(0x44AE, 0x69), 
		COMBINE_CMD16(0x44B0, 0x92), 
		COMBINE_CMD16(0x44B2, 0x91), 
		COMBINE_CMD16(0x44B4, 0x8C), 
		COMBINE_CMD16(0x44B6, 0x87), 
		COMBINE_CMD16(0x44B8, 0x82), 
		COMBINE_CMD16(0x44BA, 0x78), 
		COMBINE_CMD16(0x44BC, 0x6E), 
		COMBINE_CMD16(0x44BE, 0x69), 
		COMBINE_CMD16(0x44C0, 0x7F), 
		COMBINE_CMD16(0x44C1, 0x01), 
		COMBINE_CMD16(0x44C2, 0x7F), 
		COMBINE_CMD16(0x44C3, 0x01), 
		COMBINE_CMD16(0x44C4, 0x7A), 
		COMBINE_CMD16(0x44C5, 0x01), 
		COMBINE_CMD16(0x44C6, 0x7A), 
		COMBINE_CMD16(0x44C7, 0x01), 
		COMBINE_CMD16(0x44C8, 0x70), 
		COMBINE_CMD16(0x44C9, 0x01), 
		COMBINE_CMD16(0x44CA, 0x6B), 
		COMBINE_CMD16(0x44CB, 0x01), 
		COMBINE_CMD16(0x44CC, 0x6B), 
		COMBINE_CMD16(0x44CD, 0x01), 
		COMBINE_CMD16(0x44CE, 0x5C), 
		COMBINE_CMD16(0x44CF, 0x01), 
		COMBINE_CMD16(0x44D0, 0x7F), 
		COMBINE_CMD16(0x44D1, 0x01), 
		COMBINE_CMD16(0x44D2, 0x7F), 
		COMBINE_CMD16(0x44D3, 0x01), 
		COMBINE_CMD16(0x44D4, 0x7A), 
		COMBINE_CMD16(0x44D5, 0x01), 
		COMBINE_CMD16(0x44D6, 0x7A), 
		COMBINE_CMD16(0x44D7, 0x01), 
		COMBINE_CMD16(0x44D8, 0x70), 
		COMBINE_CMD16(0x44D9, 0x01), 
		COMBINE_CMD16(0x44DA, 0x6B), 
		COMBINE_CMD16(0x44DB, 0x01), 
		COMBINE_CMD16(0x44DC, 0x6B), 
		COMBINE_CMD16(0x44DD, 0x01), 
		COMBINE_CMD16(0x44DE, 0x5C), 
		COMBINE_CMD16(0x44DF, 0x01), 
		COMBINE_CMD16(0x4534, 0x1C), 
		COMBINE_CMD16(0x4535, 0x03), 
		COMBINE_CMD16(0x4538, 0x1C), 
		COMBINE_CMD16(0x4539, 0x1C), 
		COMBINE_CMD16(0x453A, 0x1C), 
		COMBINE_CMD16(0x453B, 0x1C), 
		COMBINE_CMD16(0x453C, 0x1C), 
		COMBINE_CMD16(0x453D, 0x1C), 
		COMBINE_CMD16(0x453E, 0x1C), 
		COMBINE_CMD16(0x453F, 0x1C), 
		COMBINE_CMD16(0x4540, 0x1C), 
		COMBINE_CMD16(0x4541, 0x03), 
		COMBINE_CMD16(0x4542, 0x03), 
		COMBINE_CMD16(0x4543, 0x03), 
		COMBINE_CMD16(0x4544, 0x03), 
		COMBINE_CMD16(0x4545, 0x03), 
		COMBINE_CMD16(0x4546, 0x03), 
		COMBINE_CMD16(0x4547, 0x03), 
		COMBINE_CMD16(0x4548, 0x03), 
		COMBINE_CMD16(0x4549, 0x03), 
		COMBINE_CMD16(0x3000, 0x00)
	}
};

isp_fcs_data_for_imx662_t fcs_data_imx662_hdr_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0x62F0,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_imx662_t),
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
		.addr_len = 2,
		.data_len = 1,
		.i2c_slave_addr = 0x1A 
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 3, 0),
		//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 2000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 2000);
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 2, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 0, 103),
		COMBINE_CMD16(0x3002, 0x00), 
		COMBINE_CMD16(0x3014, 0x04), 
		COMBINE_CMD16(0x3015, 0x07), 
		COMBINE_CMD16(0x301A, 0x01), 
		COMBINE_CMD16(0x301C, 0x01), 
		COMBINE_CMD16(0x302C, 0xDE), //HMAX 7BC=990 
		COMBINE_CMD16(0x302D, 0x03), 
		COMBINE_CMD16(0x3050, 0xdc), //SHR0	shutter of LEF					//0x97a
		COMBINE_CMD16(0x3051, 0x05), 
		COMBINE_CMD16(0x3054, 0x05), //SHR1	shutter of SEF1
		COMBINE_CMD16(0x3060, 0x63), //RHS1	readout timimg of SEF1			//0x0d 
		COMBINE_CMD16(0x3061, 0x00), 
		COMBINE_CMD16(0x30A6, 0x00), 
		COMBINE_CMD16(0x3400, 0x00), 
		COMBINE_CMD16(0x3444, 0xAC), 
		COMBINE_CMD16(0x3460, 0x21), 
		COMBINE_CMD16(0x3492, 0x08), 
		COMBINE_CMD16(0x3B00, 0x39), 
		COMBINE_CMD16(0x3B23, 0x2D), 
		COMBINE_CMD16(0x3B45, 0x04), 
		COMBINE_CMD16(0x3C0A, 0x1F), 
		COMBINE_CMD16(0x3C0B, 0x1E), 
		COMBINE_CMD16(0x3C38, 0x21), 
		COMBINE_CMD16(0x3C44, 0x00), 
		COMBINE_CMD16(0x3CB6, 0xD8), 
		COMBINE_CMD16(0x3CC4, 0xDA), 
		COMBINE_CMD16(0x3E24, 0x79), 
		COMBINE_CMD16(0x3E2C, 0x15), 
		COMBINE_CMD16(0x3EDC, 0x2D), 
		COMBINE_CMD16(0x4498, 0x05), 
		COMBINE_CMD16(0x449C, 0x19), 
		COMBINE_CMD16(0x449D, 0x00), 
		COMBINE_CMD16(0x449E, 0x32), 
		COMBINE_CMD16(0x449F, 0x01), 
		COMBINE_CMD16(0x44A0, 0x92), 
		COMBINE_CMD16(0x44A2, 0x91), 
		COMBINE_CMD16(0x44A4, 0x8C), 
		COMBINE_CMD16(0x44A6, 0x87), 
		COMBINE_CMD16(0x44A8, 0x82), 
		COMBINE_CMD16(0x44AA, 0x78), 
		COMBINE_CMD16(0x44AC, 0x6E), 
		COMBINE_CMD16(0x44AE, 0x69), 
		COMBINE_CMD16(0x44B0, 0x92), 
		COMBINE_CMD16(0x44B2, 0x91), 
		COMBINE_CMD16(0x44B4, 0x8C), 
		COMBINE_CMD16(0x44B6, 0x87), 
		COMBINE_CMD16(0x44B8, 0x82), 
		COMBINE_CMD16(0x44BA, 0x78), 
		COMBINE_CMD16(0x44BC, 0x6E), 
		COMBINE_CMD16(0x44BE, 0x69), 
		COMBINE_CMD16(0x44C0, 0x7F), 
		COMBINE_CMD16(0x44C1, 0x01), 
		COMBINE_CMD16(0x44C2, 0x7F), 
		COMBINE_CMD16(0x44C3, 0x01), 
		COMBINE_CMD16(0x44C4, 0x7A), 
		COMBINE_CMD16(0x44C5, 0x01), 
		COMBINE_CMD16(0x44C6, 0x7A), 
		COMBINE_CMD16(0x44C7, 0x01), 
		COMBINE_CMD16(0x44C8, 0x70), 
		COMBINE_CMD16(0x44C9, 0x01), 
		COMBINE_CMD16(0x44CA, 0x6B), 
		COMBINE_CMD16(0x44CB, 0x01), 
		COMBINE_CMD16(0x44CC, 0x6B), 
		COMBINE_CMD16(0x44CD, 0x01), 
		COMBINE_CMD16(0x44CE, 0x5C), 
		COMBINE_CMD16(0x44CF, 0x01), 
		COMBINE_CMD16(0x44D0, 0x7F), 
		COMBINE_CMD16(0x44D1, 0x01), 
		COMBINE_CMD16(0x44D2, 0x7F), 
		COMBINE_CMD16(0x44D3, 0x01), 
		COMBINE_CMD16(0x44D4, 0x7A), 
		COMBINE_CMD16(0x44D5, 0x01), 
		COMBINE_CMD16(0x44D6, 0x7A), 
		COMBINE_CMD16(0x44D7, 0x01), 
		COMBINE_CMD16(0x44D8, 0x70), 
		COMBINE_CMD16(0x44D9, 0x01), 
		COMBINE_CMD16(0x44DA, 0x6B), 
		COMBINE_CMD16(0x44DB, 0x01), 
		COMBINE_CMD16(0x44DC, 0x6B), 
		COMBINE_CMD16(0x44DD, 0x01), 
		COMBINE_CMD16(0x44DE, 0x5C), 
		COMBINE_CMD16(0x44DF, 0x01), 
		COMBINE_CMD16(0x4534, 0x1C), 
		COMBINE_CMD16(0x4535, 0x03), 
		COMBINE_CMD16(0x4538, 0x1C), 
		COMBINE_CMD16(0x4539, 0x1C), 
		COMBINE_CMD16(0x453A, 0x1C), 
		COMBINE_CMD16(0x453B, 0x1C), 
		COMBINE_CMD16(0x453C, 0x1C), 
		COMBINE_CMD16(0x453D, 0x1C), 
		COMBINE_CMD16(0x453E, 0x1C), 
		COMBINE_CMD16(0x453F, 0x1C), 
		COMBINE_CMD16(0x4540, 0x1C), 
		COMBINE_CMD16(0x4541, 0x03), 
		COMBINE_CMD16(0x4542, 0x03), 
		COMBINE_CMD16(0x4543, 0x03), 
		COMBINE_CMD16(0x4544, 0x03), 
		COMBINE_CMD16(0x4545, 0x03), 
		COMBINE_CMD16(0x4546, 0x03), 
		COMBINE_CMD16(0x4547, 0x03), 
		COMBINE_CMD16(0x4548, 0x03), 
		COMBINE_CMD16(0x4549, 0x03), 
		COMBINE_CMD16(0x3000, 0x00)
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_imx662_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_imx662_v0,sizeof(isp_fcs_data_for_imx662_t), 1, ofile);
	fclose(ofile);
	
	ofile = fopen("fcs_data_imx662_hdr_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_imx662_hdr_v0,sizeof(isp_fcs_data_for_imx662_t), 1, ofile);
	fclose(ofile);
	
	return 0;
}







