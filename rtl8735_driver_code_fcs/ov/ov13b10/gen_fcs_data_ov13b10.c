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
#define SENSOR_CMD_CNT 		150

#define SNR_PWRCTRL_GPIO	0
#define SNR_RST_GPIO		1
#define SNR_PWDN_GPIO		2
#define GPIO_LOW			0
#define GPIO_HIGH			1

typedef struct isp_fcs_data_for_ov13b10_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	//uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
}isp_fcs_data_for_ov13b10_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


isp_fcs_data_for_ov13b10_t fcs_data_ov13b10_v1 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION|0xb1f0,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_ov13b10_t),
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
		//.i2c_slave_addr = 0x36,
		.i2c_slave_addr = 0x10,
	},
	.sensor_init_data  = {	
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 10, 0),
		//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),
		//set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWDN_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_24M, 0),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB|ETA_PL_ATTB|END_ATTB, 0, 134),
		COMBINE_CMD16(0x0103,0x01),
		COMBINE_CMD16(0x0303,0x01),
		COMBINE_CMD16(0x0305,0x23),
		COMBINE_CMD16(0x0321,0x00),
		COMBINE_CMD16(0x0323,0x04),
		COMBINE_CMD16(0x0324,0x01),
		COMBINE_CMD16(0x0325,0x50),
		COMBINE_CMD16(0x0326,0x81),
		COMBINE_CMD16(0x0327,0x04),
		COMBINE_CMD16(0x3011,0x7c),
		COMBINE_CMD16(0x3012,0x07),
		COMBINE_CMD16(0x3013,0x32),
		COMBINE_CMD16(0x3016,0x32),  //2lane
		COMBINE_CMD16(0x3106,0x29),  //2lane
		COMBINE_CMD16(0x3107,0x23),
		COMBINE_CMD16(0x3501,0x06),
		COMBINE_CMD16(0x3502,0x10),
		COMBINE_CMD16(0x3504,0x08),
		COMBINE_CMD16(0x3508,0x07),
		COMBINE_CMD16(0x3509,0xc0),
		COMBINE_CMD16(0x3600,0x16),
		COMBINE_CMD16(0x3601,0x54),
		COMBINE_CMD16(0x3612,0x4e),
		COMBINE_CMD16(0x3620,0x00),
		COMBINE_CMD16(0x3621,0x68),
		COMBINE_CMD16(0x3622,0x66),
		COMBINE_CMD16(0x3623,0x03),
		COMBINE_CMD16(0x3662,0x88),
		COMBINE_CMD16(0x3666,0xbb),
		COMBINE_CMD16(0x3667,0x44),
		COMBINE_CMD16(0x366e,0xff),
		COMBINE_CMD16(0x366f,0xf3),
		COMBINE_CMD16(0x3675,0x44),
		COMBINE_CMD16(0x3676,0x00),
		COMBINE_CMD16(0x367f,0xe9),
		COMBINE_CMD16(0x3681,0x32),
		COMBINE_CMD16(0x3682,0x1f),
		COMBINE_CMD16(0x3683,0x0b),
		COMBINE_CMD16(0x3684,0x0b),
		COMBINE_CMD16(0x3704,0x0f),
		COMBINE_CMD16(0x3706,0x40),
		COMBINE_CMD16(0x3708,0x3b),
		COMBINE_CMD16(0x3709,0x72),
		COMBINE_CMD16(0x370b,0xa2),
		COMBINE_CMD16(0x3714,0x28),
		COMBINE_CMD16(0x371a,0x3e),
		COMBINE_CMD16(0x3725,0x42),
		COMBINE_CMD16(0x3739,0x10),
		COMBINE_CMD16(0x3767,0x00),
		COMBINE_CMD16(0x377a,0x0d),
		COMBINE_CMD16(0x3789,0x18),
		COMBINE_CMD16(0x3790,0x40),
		COMBINE_CMD16(0x3791,0xa2),
		COMBINE_CMD16(0x37c2,0x14),
		COMBINE_CMD16(0x37c3,0xf1),
		COMBINE_CMD16(0x37d9,0x06),
		COMBINE_CMD16(0x37da,0x02),
		COMBINE_CMD16(0x37dc,0x02),
		COMBINE_CMD16(0x37e1,0x04),
		COMBINE_CMD16(0x37e2,0x0c),
		COMBINE_CMD16(0x37e4,0x00),
		COMBINE_CMD16(0x3800,0x00),
		COMBINE_CMD16(0x3801,0x00),
		COMBINE_CMD16(0x3802,0x00),
		COMBINE_CMD16(0x3803,0x08),
		COMBINE_CMD16(0x3804,0x10),
		COMBINE_CMD16(0x3805,0x8f),
		COMBINE_CMD16(0x3806,0x0c),
		COMBINE_CMD16(0x3807,0x47),
		COMBINE_CMD16(0x3808,0x08),
		COMBINE_CMD16(0x3809,0x38),
		COMBINE_CMD16(0x380a,0x06),
		COMBINE_CMD16(0x380b,0x18),
		COMBINE_CMD16(0x380c,0x09),  //hts = 2400
		COMBINE_CMD16(0x380d,0x30),  //hts = 2400
		COMBINE_CMD16(0x380e,0x06),
		COMBINE_CMD16(0x380f,0x3e),
		COMBINE_CMD16(0x3811,0x07),
		COMBINE_CMD16(0x3813,0x05),
		COMBINE_CMD16(0x3814,0x03),
		COMBINE_CMD16(0x3815,0x01),
		COMBINE_CMD16(0x3816,0x03),
		COMBINE_CMD16(0x3817,0x01),
		COMBINE_CMD16(0x381f,0x08),
		COMBINE_CMD16(0x3820,0x8b),
		COMBINE_CMD16(0x3821,0x00),
		COMBINE_CMD16(0x3822,0x14),
		COMBINE_CMD16(0x3823,0x18),
		COMBINE_CMD16(0x3827,0x01),
		COMBINE_CMD16(0x382e,0xe6),
		COMBINE_CMD16(0x3c80,0x00),
		COMBINE_CMD16(0x3c87,0x01),
		COMBINE_CMD16(0x3c8c,0x18),
		COMBINE_CMD16(0x3c8d,0x1c),
		COMBINE_CMD16(0x3ca0,0x00),
		COMBINE_CMD16(0x3ca1,0x00),
		COMBINE_CMD16(0x3ca2,0x00),
		COMBINE_CMD16(0x3ca3,0x00),
		COMBINE_CMD16(0x3ca4,0x50),
		COMBINE_CMD16(0x3ca5,0x11),
		COMBINE_CMD16(0x3ca6,0x01),
		COMBINE_CMD16(0x3ca7,0x00),
		COMBINE_CMD16(0x3ca8,0x00),
		COMBINE_CMD16(0x4008,0x00),
		COMBINE_CMD16(0x4009,0x05),
		COMBINE_CMD16(0x400a,0x01),
		COMBINE_CMD16(0x400b,0x19),
		COMBINE_CMD16(0x4011,0x21),
		COMBINE_CMD16(0x4017,0x08),
		COMBINE_CMD16(0x4019,0x04),
		COMBINE_CMD16(0x401a,0x58),
		COMBINE_CMD16(0x4032,0x1e),
		COMBINE_CMD16(0x4050,0x00),
		COMBINE_CMD16(0x4051,0x05),
		COMBINE_CMD16(0x405e,0x00),
		COMBINE_CMD16(0x4066,0x02),
		COMBINE_CMD16(0x4501,0x08),
		COMBINE_CMD16(0x4502,0x10),
		COMBINE_CMD16(0x4505,0x04),
		COMBINE_CMD16(0x4800,0x64),
		COMBINE_CMD16(0x481b,0x3e),
		COMBINE_CMD16(0x481f,0x30),
		COMBINE_CMD16(0x4825,0x34),
		COMBINE_CMD16(0x4837,0x1d),
		COMBINE_CMD16(0x484b,0x01),
		COMBINE_CMD16(0x4883,0x02),
		COMBINE_CMD16(0x5000,0xfd),
		COMBINE_CMD16(0x5001,0x0d),
		COMBINE_CMD16(0x5045,0x20),
		COMBINE_CMD16(0x5046,0x20),
		COMBINE_CMD16(0x5047,0xa4),
		COMBINE_CMD16(0x5048,0x20),
		COMBINE_CMD16(0x5049,0xa4),
		COMBINE_CMD16(0x0100,0x01)
	}
};

int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_ov13b10_v0.bin","wb");
	if (ofile==NULL) {
		printf ("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_ov13b10_v1,sizeof(isp_fcs_data_for_ov13b10_t), 1, ofile);
	fclose(ofile);
	

	return 0;
}







