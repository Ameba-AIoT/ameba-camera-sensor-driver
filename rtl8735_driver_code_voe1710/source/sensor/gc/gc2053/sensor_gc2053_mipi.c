/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define ORIENTATION 	 0	//0=default, 1=rotate180
#define SENSOR_GAIN_FULL 1	//0=16x, 1=63.25x
#if (SENSOR_GAIN_FULL == 1)
#define ANALOG_GAIN_MAX_RATIO (float)63.25f	/* Max sensor gain ratio => 7048/64 = 64.0x */
#else
#define ANALOG_GAIN_MAX_RATIO (float)16.f	/* Max sensor gain ratio => 1027/64 = 16.0x */
#endif
#define THERMAL_PROTECT	 0

#if (THERMAL_PROTECT == 1)
char timeCount = 30;	//frame interval for thermal protection
uint16_t maxGain = 581;	//Limited max gain under high temperature condition
uint16_t refIndex = 13;	//Gain index for registable
char timeFlag = 0;
char temperature_flag = 0;
#endif

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct gc2053_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct gc2053_gain_config {
	uint8_t reg_b4;
	uint8_t reg_b3;
	uint8_t reg_b8;
	uint8_t reg_b9;
	uint16_t value;
};

static struct gc2053_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc2053_fps_info_asic[] = {
	{30.0f, 3520, 118800000},
};

static struct rts_isp_i2c_reg g_gc2053_i2c_init_regs_asic[] = {
	//mclk=27mhz,pclk=74.25mhz
	//pixel_line_total=2200,line_frame_total=1125
	//row_time=29.629us,frame_rate=30fps
	//Mipi_clk=594 Mbps
	/****system****/
	{0xfe, 0x80},
	{0xfe, 0x80},
	{0xfe, 0x80},
	{0xfe, 0x00},
	{0xf2, 0x00},
	{0xf3, 0x00},
	{0xf4, 0x36},
	{0xf5, 0xc0},
	{0xf6, 0x44},//0x84
	{0xf7, 0x01},//0x11
	{0xf8, 0x2c},//0x37
	{0xf9, 0x42},//0x82
	{0xfc, 0x8e},
	/****CISCTL & ANALOG****/
	{0xfe, 0x00},
	{0x87, 0x18}, //[6]aec_delay_mode
	{0xee, 0x30}, //[5:4]dwen_sramen
	{0xd0, 0xb7}, //ramp_en
	{0x03, 0x04},
	{0x04, 0x60},
	{0x05, 0x04}, //05
	{0x06, 0x4c}, //60//[11:0]hb
	{0x07, 0x00},
	{0x08, 0x11},
	{0x09, 0x00},
	{0x0a, 0x02}, //cisctl row start
	{0x0b, 0x00},
	{0x0c, 0x02}, //cisctl col start
	{0x0d, 0x04},
	{0x0e, 0x40},
	{0x12, 0xe2}, //vsync_ahead_mode
	{0x13, 0x16},
	{0x19, 0x0a}, //ad_pipe_num
	{0x21, 0x1c}, //eqc1fc_eqc2fc_sw
	{0x28, 0x0a}, //16//eqc2_c2clpen_sw
	{0x29, 0x24}, //eq_post_width
	{0x2b, 0x04}, //c2clpen --eqc2
	{0x32, 0xf8}, //[5]txh_en ->avdd28
	{0x37, 0x03}, //[3:2]eqc2sel=0
	{0x39, 0x15},
	{0x43, 0x07},
	{0x44, 0x40}, //0e//post_tx_width
	{0x46, 0x0b},
	{0x4b, 0x20}, //rst_tx_width
	{0x4e, 0x08}, //12//ramp_t1_width
	{0x55, 0x20}, //read_tx_width_pp
	{0x66, 0x05}, //18//stspd_width_r1
	{0x67, 0x05}, //40//5//stspd_width_r
	{0x77, 0x01},
	{0x78, 0x00},
	{0x7c, 0x93},
	{0x8c, 0x12}, //12 ramp_t1_ref
	{0x8d, 0x92},
	{0x90, 0x00},
	{0x9d, 0x10},
	{0xce, 0x7c},
	{0xd2, 0x41}, //[5:3]c2clamp
	{0xd3, 0xdc},
	{0xe6, 0x50},
	/*gain*/
	{0xb6, 0xc0},
	{0xb0, 0x70},
	{0xb1, 0x01},
	{0xb2, 0x00},
	{0xb3, 0x00},
	{0xb4, 0x00},
	{0xb8, 0x01},
	{0xb9, 0x00},
	/*blk*/
	{0x26, 0x30},
	{0xfe, 0x01},
	{0x40, 0x23},
	{0x55, 0x07},
	{0x60, 0x40}, //[7:0]WB_offset
	{0xfe, 0x04},
	{0x14, 0x78},
	{0x15, 0x78},
	{0x16, 0x78},
	{0x17, 0x78},
	/*window*/
	{0xfe, 0x01},
	{0x92, 0x00},
	{0x94, 0x03},
	{0x95, 0x04},
	{0x96, 0x40},
	{0x97, 0x07},
	{0x98, 0x88}, //[11:0]out_width
	/*ISP*/
	{0xfe, 0x01},
	{0x01, 0x05},
	{0x02, 0x89}, //[7:0]BFF_sram_mode
	{0x04, 0x01}, //[0]DD_en
	{0x07, 0xa6},
	{0x08, 0xa9},
	{0x09, 0xa8},
	{0x0a, 0xa7},
	{0x0b, 0xff},
	{0x0c, 0xff},
	{0x0f, 0x00},
	{0x50, 0x1c},
	{0x89, 0x03},
	/*dpc*/
	{0xfe, 0x04},
	{0x28, 0x86},
	{0x29, 0x86},
	{0x2a, 0x86},
	{0x2b, 0x68},
	{0x2c, 0x68},
	{0x2d, 0x68},
	{0x2e, 0x68},
	{0x2f, 0x68},
	{0x30, 0x4f},
	{0x31, 0x68},
	{0x32, 0x67},
	{0x33, 0x66},
	{0x34, 0x66},
	{0x35, 0x66},
	{0x36, 0x66},
	{0x37, 0x66},
	{0x38, 0x62},
	{0x39, 0x62},
	{0x3a, 0x62},
	{0x3b, 0x62},
	{0x3c, 0x62},
	{0x3d, 0x62},
	{0x3e, 0x62},
	{0x3f, 0x62},
	/****DVP & MIPI****/
	{0xfe, 0x01},
	{0x9a, 0x06},
	{0xfe, 0x00},
	{0x7b, 0x2a},
	{0x23, 0x2d},
	{0xfe, 0x03},
	{0x01, 0x27},
	{0x02, 0x5f},
	{0x03, 0xb6},
	{0x12, 0x80},
	{0x13, 0x07},
	{0x15, 0x12},
	{0xfe, 0x00},
	{0x3e, 0x91},
};

static struct gc2053_gain_config g_gc2053_gain_config[] = {
	{0x00, 0x00, 0x01, 0x00, 64},
	{0x00, 0x10, 0x01, 0x0c, 74},
	{0x00, 0x20, 0x01, 0x1b, 89},
	{0x00, 0x30, 0x01, 0x2c, 102},
	{0x00, 0x40, 0x01, 0x3f, 127},
	{0x00, 0x50, 0x02, 0x16, 147},
	{0x00, 0x60, 0x02, 0x35, 177},
	{0x00, 0x70, 0x03, 0x16, 203},
	{0x00, 0x80, 0x04, 0x02, 260},
	{0x00, 0x90, 0x04, 0x31, 300},
	{0x00, 0xa0, 0x05, 0x32, 361},
	{0x00, 0xb0, 0x06, 0x35, 415},
	{0x00, 0xc0, 0x08, 0x04, 504},
	{0x00, 0x5a, 0x09, 0x19, 581},
	{0x00, 0x83, 0x0b, 0x0f, 722},
	{0x00, 0x93, 0x0d, 0x12, 832},
	{0x00, 0x84, 0x10, 0x00, 1024},	//1027
#if (SENSOR_GAIN_FULL == 1)
	{0x00, 0x94, 0x12, 0x3a, 1182},
	{0x01, 0x2c, 0x1a, 0x02, 1408},
	{0x01, 0x3c, 0x1b, 0x20, 1621},
	{0x00, 0x8c, 0x20, 0x0f, 1990},
	{0x00, 0x9c, 0x26, 0x07, 2291},
	{0x02, 0x64, 0x36, 0x21, 2850},
	{0x02, 0x74, 0x37, 0x3a, 3282},
	{0x00, 0xc6, 0x3d, 0x02, 4048},
#endif
#if 0	//limit to analog gain lower than 64x
	{0x00, 0xdc, 0x3f, 0x3f, 5180},
	{0x02, 0x85, 0x3f, 0x3f, 5500},
	{0x02, 0x95, 0x3f, 0x3f, 6744},
	{0x00, 0xce, 0x3f, 0x3f, 7073},
#endif
};
#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x37	//0x6e(default)
#define SLAVE_ADDR_1 0x3f	//0x7e

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int gc2053_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	struct rts_isp_snr_pwr *resume = &info->resume;
	struct rts_isp_snr_pwr *suspend = &info->suspend;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;

	info->modes.mode[0].fps = g_gc2053_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;


	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 5000);

	//set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 1000);
	//set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V2, 1000);
	//set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	up->num = i;

	i = 0;
	set_power_item(&resume->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);
	set_power_item(&resume->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&resume->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 5000);

	//set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 1000);
	//set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V2, 1000);
	//set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 1000);
	set_power_item(&resume->items[i++], SNR_HCLK, CLK_27M, 1000);
	set_power_item(&resume->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&resume->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	resume->num = i;

	i = 0;
	set_power_item(&suspend->items[i++], SNR_RST_GPIO, 0, 10000);
	set_power_item(&suspend->items[i++], SNR_PWDN_GPIO, 0, 100000);
	set_power_item(&suspend->items[i++], SNR_HCLK, 0, 10000);
	set_power_item(&suspend->items[i++], SNR_ANALOG_POWER, 0, 5000);
	set_power_item(&suspend->items[i++], SNR_CORE_POWER, 0, 5000);
	set_power_item(&suspend->items[i++], SNR_IO_POWER, 0, 0);
	suspend->num = i;

	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 10000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 100000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 10000);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, 0, 5000);
	set_power_item(&down->items[i++], SNR_CORE_POWER, 0, 5000);
	set_power_item(&down->items[i++], SNR_IO_POWER, 0, 0);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *gc2053_get_fps_info(uint16_t fps)
{
	int i;

		for (i = 0; i < ARRAY_SIZE(g_gc2053_fps_info_asic); i++)
			if (fps == g_gc2053_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_gc2053_fps_info_asic))
			return NULL;
		return &g_gc2053_fps_info_asic[i];

}

static int gc2053_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc2053_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc2053_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0], g_gc2053_i2c_init_regs_asic, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 3;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1125;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	//info->exposure_step = status->exp_step;

	return RTS_ISP_OK;
}

static int gc2053_start(uint32_t isp_id)
{
	struct gc2053_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct gc2053_status *status)
{
	int i;
	uint16_t gain = fgain * 64;
	
	if (gain >= (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f)) {
		gain = (uint16_t)((float)ANALOG_GAIN_MAX_RATIO * 64.f);
		status->num = (uint8_t)(ARRAY_SIZE(g_gc2053_gain_config) - 1);
	} else {
		for (i = 0; i < ARRAY_SIZE(g_gc2053_gain_config) - 1; i++) {
			if (gain >= g_gc2053_gain_config[i].value &&
			    gain < g_gc2053_gain_config[i + 1].value) {
				gain = g_gc2053_gain_config[i].value;
				status->num = i;
				break;
			}
		}
	}
	
#if (THERMAL_PROTECT == 1)
	if((temperature_flag == 1) && (gain >= maxGain)) {
		gain = maxGain;
		status->num = refIndex;
	}
#endif

	return gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 64.0f;
}

static int gc2053_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc2053_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int gc2053_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static test_flag = 0;

static int gc2053_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct gc2053_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

#if (THERMAL_PROTECT == 1)
	if(timeFlag == 0) 
	{	
		struct rts_isp_i2c_reg i2creg0, i2creg1, i2creg2, i2creg3, i2creg4;
		int i;
		int temperature_value;

		i2creg0.addr = 0xfe;
		i2creg0.data = 0x04;
		i2creg1.addr = 0x0C;
		i2creg2.addr = 0x0D;
		i2creg3.addr = 0x0E;
		i2creg4.addr = 0x0F;
		
		//sync lock handle
    	//rts_isp_sensor_access_prepare();
		rts_isp_write_sensor_reg(isp_id, &i2creg0);
    	rts_isp_read_sensor_reg(isp_id, &i2creg1);
		rts_isp_read_sensor_reg(isp_id, &i2creg2);
		rts_isp_read_sensor_reg(isp_id, &i2creg3);
		rts_isp_read_sensor_reg(isp_id, &i2creg4);
		temperature_value = (i2creg1.data + i2creg2.data + i2creg3.data + i2creg4.data) >> 2;
		if((temperature_value >= 0x38) && (temperature_flag == 0))
		{
			temperature_flag = 1;
			//printf("[SensorThermalCondition]Flag = %d, temperature_value=%d, Value = %x, %x, %x, %x\r\n", temperature_flag, temperature_value, i2creg1.data, i2creg2.data, i2creg3.data, i2creg4.data);
		}
		else if((temperature_value <= 0x20) && (temperature_flag == 1))
		{
			temperature_flag = 0;
			//printf("[SensorThermalCondition]Flag = %d, temperature_value=%d, Value = %x, %x, %x, %x\r\n", temperature_flag, temperature_value, i2creg1.data, i2creg2.data, i2creg3.data, i2creg4.data);
		}		
	}
#endif

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	if(test_flag)
		return;
		
	i = 0;
	set_sync_i2c(&reg[i++], 0xfe, 0x00);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x03, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x04, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}

	//debug("exposure = %f\r\n", exp_gain->exposure[0]);

	set_sync_i2c(&reg[i++], 0xfe, 0x00);
	set_sync_i2c(&reg[i++], 0xb3, g_gc2053_gain_config[status->num].reg_b3);
	//debug("0xb3 = %d\r\n", g_gc2053_gain_config[status->num].reg_b3);
	set_sync_i2c(&reg[i++], 0xb4, g_gc2053_gain_config[status->num].reg_b4);
	//debug("0xb4 = %d\r\n", g_gc2053_gain_config[status->num].reg_b4);
	set_sync_i2c(&reg[i++], 0xb8, g_gc2053_gain_config[status->num].reg_b8);
	//debug("0xb8 = %d\r\n", g_gc2053_gain_config[status->num].reg_b8);
	set_sync_i2c(&reg[i++], 0xb9, g_gc2053_gain_config[status->num].reg_b9);
	//debug("0xb9 = %d\r\n", g_gc2053_gain_config[status->num].reg_b9);
	set_sync_i2c(&reg[i++], 0x41, vts >> 8);
	set_sync_i2c(&reg[i++], 0x42, vts & 0xff);
	//debug("vts      = %d   \r\n", vts);
	regs->num = i;

#if (THERMAL_PROTECT == 1)	
	set_sync_i2c(&reg[i++], 0xfe, 0x04);
	timeFlag++;
	timeFlag = timeFlag % timeCount;
#endif

	return RTS_ISP_OK;
}

static int gc2053_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x80);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x81);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x82);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x83);
		break;
	#else
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x83);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x82);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x81);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0xfe, 0x00);
			set_sync_i2c(&reg[i++], 0x17, 0x80);
		break;
	#endif
	}
	mf_info->regs.num = i;
	
	return RTS_ISP_OK;
}


static int gc2053_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();

	reg.addr = 0xf0;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0xf1;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	if (id == 0x2053)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int gc2053_pre_resume(uint32_t isp_id)
{
	//printf("gc2053_pre_resume: %x\n\r", rts_isp_sensor_get_open_mode());
	return RTS_ISP_OK;
}

static int gc2053_stop(uint32_t isp_id)
{
	//printf("gc2053_stop: %x\n\r", rts_isp_sensor_get_close_mode());
	return RTS_ISP_OK;
}

static int gc2053_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops gc2053_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc2053",

	.get_info = gc2053_get_info,
	.get_init_info = gc2053_get_init_info,
	.start = gc2053_start,
	.get_tuned_again = gc2053_get_tuned_again,
	.get_tuned_dgain = gc2053_get_tuned_dgain,
	.get_exposure_gain_info = gc2053_get_exposure_gain_info,
	.set_mirror_flip = gc2053_set_mirror_flip,
	.check = gc2053_check,
	.pre_resume = gc2053_pre_resume,
	.stop = gc2053_stop,
	.get_slave_addr_num = gc2053_get_slave_addr_num,
};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc2053_ops;
}
