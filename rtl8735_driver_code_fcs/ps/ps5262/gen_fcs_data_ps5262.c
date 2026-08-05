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

typedef struct isp_fcs_data_for_ps5262_s {
	isp_fcs_header_t header;
	isp_i2c_info_t i2c_info;
	uint16_t adc_lut[ADC_TH_SET_NUM][ADC_TH_ITEM];
	uint32_t sensor_init_data[SENSOR_CMD_CNT];
} isp_fcs_data_for_ps5262_t;

#define COMBINE_CMD(cmd_id, cmd_attb, payload0, payload1)  ( (((payload1)&0xFF)<<24) | (((payload0)&0xFF)<<16) | (((cmd_attb)&0xFF)<<8) | ((cmd_id)&0xFF) )
#define COMBINE_CMD16(payload0, payload1)  ( (((payload1)&0xFFFF)<<16)  | ((payload0)&0xFFFF) )
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

isp_fcs_data_for_ps5262_t fcs_data_ps5262_v0 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x6200,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_ps5262_t),
		.dtcm_addr = FCS_SRAM_ADDR,
		.i2c_id = 3,
		.i2c_device_cnt = 1,
		.i2c_speed_mode = I2CFastSpeed,
		.i2c_speed = 1000,
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
		.addr_len = 2,
		.data_len = 1,
		.i2c_slave_addr = 0x48
	},
	.sensor_init_data  = {
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 8, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 10, 0), //5
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_27M, 0),	//set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 2000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 0, 37),
		//PS319_5262_1928x1088_27M_30fps_Pxclk74p25M_MIPI_2Lane_RAW10_400Mbps_NonImgSyn_20210429_B04A_reduce.asc
		COMBINE_CMD16(0x56FF, 0x00), //Zako, 2025.07.28 clear MD interrupt pin
		COMBINE_CMD16(0x410B, 0x83), //Cmd_Sw_TriState=1
		COMBINE_CMD16(0x0114, 0x08), //Cmd_LineTime[12:0]=2200
		COMBINE_CMD16(0x0115, 0x98), //Cmd_LineTime[12:0]=2200
		COMBINE_CMD16(0x0162, 0x02), //Cmd_Np[3:0]=2
		COMBINE_CMD16(0x4178, 0xB0), //B04A: Version
		COMBINE_CMD16(0x4179, 0x4A), //B04A: Version
		COMBINE_CMD16(0x0226, 0x16), //T_spll_predivider=22
		COMBINE_CMD16(0x0227, 0x1F), //T_spll_postdivider=31
		COMBINE_CMD16(0x0225, 0x11), //T_spll_enh[0]=1
		COMBINE_CMD16(0x0242, 0x11), //T_MIPI_EnL[0]=0, T_MIPI_sel[0]=1
		COMBINE_CMD16(0x0246, 0x19), //T_pll_predivider=25
		COMBINE_CMD16(0x0247, 0x26), //T_pll_postdivider=38
		COMBINE_CMD16(0x0248, 0x61), //T_pll_enh[0]=1
		COMBINE_CMD16(0x0249, 0x11), //T_pll_div2_EnH=1
		COMBINE_CMD16(0x4212, 0xC0), //T_FAE_CLK_SEL[0]=0
		COMBINE_CMD16(0x0654, 0x01), //R_comp_rst_r1=500
		COMBINE_CMD16(0x0655, 0xF5), //R_comp_rst_r1=500
		COMBINE_CMD16(0x0657, 0x19), //R_comp_rst_r2=281
		COMBINE_CMD16(0x0659, 0x90), //R_comp_rst_r3=400
		COMBINE_CMD16(0x065B, 0x2B), //R_comp_rst_r4=1323
		COMBINE_CMD16(0x06A3, 0x40), //Cmd_RDAC_G2=54->64
		COMBINE_CMD16(0x06AC, 0x08), //Cmd_vbt_isel_R_G3=6->8
		COMBINE_CMD16(0x0906, 0x08), //R_DLNU_ABC_Modify1=520
		COMBINE_CMD16(0x0908, 0x1C), //R_DLNU_FDC_Modify1=540
		COMBINE_CMD16(0x090F, 0x08), //R_DLNU_ABC_Modify2=520
		COMBINE_CMD16(0x0911, 0x1C), //R_DLNU_FDC_Modify2=540
		COMBINE_CMD16(0x0919, 0x03), //R_DLNU_Scale_1=3
		COMBINE_CMD16(0x091A, 0x03), //R_DLNU_Scale_2=3
		COMBINE_CMD16(0x0B0C, 0x00), //Cmd_MIPI_Clk_Gated[0]=0
		COMBINE_CMD16(0x1415, 0x05), //R_LPX_prd[7:0]=5
		COMBINE_CMD16(0x1417, 0x03), //R_HsPrep_prd[7:0]=3
		COMBINE_CMD16(0x1418, 0x03), //R_HsEoT_prd[7:0]=3
		COMBINE_CMD16(0x145B, 0x10), //R_MIPI_frm_rst_en=1
		COMBINE_CMD16(0x140F, 0x01), //R_CSI2_enable=1
		COMBINE_CMD16(0x0111, 0x01), //UpdateFlag[0]=1
		COMBINE_CMD16(0x010F, 0x01), //Sensor_EnH[0]=1
	}
};

isp_fcs_data_for_ps5262_t fcs_data_ps5262_v1 = {
	.header = {
		.magic = ISP_FCS_DATA_MAGIC_NUM,
		.version = ISP_FCS_DATA_VERSION | 0x6201,
		.itcm_size = 0,
		.dtcm_size = sizeof(isp_fcs_data_for_ps5262_t),
		.dtcm_addr = FCS_SRAM_ADDR,
		.i2c_id = 3,
		.i2c_device_cnt = 1,
		.i2c_speed_mode = I2CFastSpeed,
		.i2c_speed = 1000,
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
		.addr_len = 2,
		.data_len = 1,
		.i2c_slave_addr = 0x48
	},
	.sensor_init_data  = {
		//COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_PWRCTRL_GPIO, GPIO_HIGH),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_LOW),
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 8, 0),
		COMBINE_CMD(ISP_FCS_GPIO_SET, VALID_ATTB, SNR_RST_GPIO, GPIO_HIGH),			//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 10, 0), //5
		COMBINE_CMD(ISP_FCS_SNR_HCLK_SET, VALID_ATTB, CLK_27M, 0),					//set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 2000);
		COMBINE_CMD(ISP_FCS_TIMER_DELAYMS, VALID_ATTB, 5, 0),
		COMBINE_CMD(ISP_FCS_I2C_BSTWRITE_16, VALID_ATTB | ETA_PL_ATTB | END_ATTB, 0, 37),
		//PS319_5262_1928x1088_27M_30fps_Pxclk74p25M_MIPI_2Lane_RAW10_400Mbps_NonImgSyn_20210429_B04A_reduce.asc
		COMBINE_CMD16(0x56FF, 0x00), //Zako, 2025.07.28 clear MD interrupt pin
		COMBINE_CMD16(0x410B, 0x83), //Cmd_Sw_TriState=1
		COMBINE_CMD16(0x0114, 0x08), //Cmd_LineTime[12:0]=2200
		COMBINE_CMD16(0x0115, 0x98), //Cmd_LineTime[12:0]=2200
		COMBINE_CMD16(0x0162, 0x02), //Cmd_Np[3:0]=2
		COMBINE_CMD16(0x4178, 0xB0), //B04A: Version
		COMBINE_CMD16(0x4179, 0x4A), //B04A: Version
		COMBINE_CMD16(0x0226, 0x16), //T_spll_predivider=22
		COMBINE_CMD16(0x0227, 0x1F), //T_spll_postdivider=31
		COMBINE_CMD16(0x0225, 0x11), //T_spll_enh[0]=1
		COMBINE_CMD16(0x0242, 0x11), //T_MIPI_EnL[0]=0, T_MIPI_sel[0]=1
		COMBINE_CMD16(0x0246, 0x19), //T_pll_predivider=25
		COMBINE_CMD16(0x0247, 0x26), //T_pll_postdivider=38
		COMBINE_CMD16(0x0248, 0x61), //T_pll_enh[0]=1
		COMBINE_CMD16(0x0249, 0x11), //T_pll_div2_EnH=1
		COMBINE_CMD16(0x4212, 0xC0), //T_FAE_CLK_SEL[0]=0
		COMBINE_CMD16(0x0654, 0x01), //R_comp_rst_r1=500
		COMBINE_CMD16(0x0655, 0xF5), //R_comp_rst_r1=500
		COMBINE_CMD16(0x0657, 0x19), //R_comp_rst_r2=281
		COMBINE_CMD16(0x0659, 0x90), //R_comp_rst_r3=400
		COMBINE_CMD16(0x065B, 0x2B), //R_comp_rst_r4=1323
		COMBINE_CMD16(0x06A3, 0x40), //Cmd_RDAC_G2=54->64
		COMBINE_CMD16(0x06AC, 0x08), //Cmd_vbt_isel_R_G3=6->8
		COMBINE_CMD16(0x0906, 0x08), //R_DLNU_ABC_Modify1=520
		COMBINE_CMD16(0x0908, 0x1C), //R_DLNU_FDC_Modify1=540
		COMBINE_CMD16(0x090F, 0x08), //R_DLNU_ABC_Modify2=520
		COMBINE_CMD16(0x0911, 0x1C), //R_DLNU_FDC_Modify2=540
		COMBINE_CMD16(0x0919, 0x03), //R_DLNU_Scale_1=3
		COMBINE_CMD16(0x091A, 0x03), //R_DLNU_Scale_2=3
		COMBINE_CMD16(0x0B0C, 0x00), //Cmd_MIPI_Clk_Gated[0]=0
		COMBINE_CMD16(0x1415, 0x05), //R_LPX_prd[7:0]=5
		COMBINE_CMD16(0x1417, 0x03), //R_HsPrep_prd[7:0]=3
		COMBINE_CMD16(0x1418, 0x03), //R_HsEoT_prd[7:0]=3
		COMBINE_CMD16(0x145B, 0x10), //R_MIPI_frm_rst_en=1
		COMBINE_CMD16(0x140F, 0x01), //R_CSI2_enable=1
		COMBINE_CMD16(0x0111, 0x01), //UpdateFlag[0]=1
		COMBINE_CMD16(0x010F, 0x01), //Sensor_EnH[0]=1
	}
};


int main()
{
	FILE *ofile;
	/* Open files */
	ofile = fopen("fcs_data_ps5262_v1.bin", "wb");
	if (ofile == NULL) {
		printf("Error opening files\n");
		return 1;
	}
	fwrite(&fcs_data_ps5262_v1, sizeof(isp_fcs_data_for_ps5262_t), 1, ofile);
	fclose(ofile);

	return 0;
}







