/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */
#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include <math.h>
#include <isp_reg_lib.h>
//#if _IMX471_SENSOR_
//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif
#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define float_tol 0.0001f
#define float_ne(x, y) (fabsf((float)x - (float)y) > float_tol)
#define float_eq(x, y) (fabsf((float)x - (float)y) < float_tol)
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))
#define ANALOG_GAIN_MAX_RATIO 16 //analog gain
enum {
	BINNING_MODE=0,
	FULL_MODE
};
static int sensor_mode = FULL_MODE;	//0=BINNING, 1=FULL
struct imx471_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
};
static struct imx471_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
static struct rts_isp_i2c_reg g_imx471_i2c_init_regs_binning[] = {
	{0x0136, 0x18},
	{0x0137, 0x00},
	{0x3C7E, 0x01},
	{0x3C7F, 0x05},
	{0x3E35, 0x00},
	{0x3E36, 0x00},
	{0x3E37, 0x00},
	{0x3F7F, 0x01},
	{0x4431, 0x04},
	{0x531C, 0x01},
	{0x531D, 0x02},
	{0x531E, 0x04},
	{0x5928, 0x00},
	{0x5929, 0x2F},
	{0x592A, 0x00},
	{0x592B, 0x85},
	{0x592C, 0x00},
	{0x592D, 0x32},
	{0x592E, 0x00},
	{0x592F, 0x88},
	{0x5930, 0x00},
	{0x5931, 0x3D},
	{0x5932, 0x00},
	{0x5933, 0x93},
	{0x5938, 0x00},
	{0x5939, 0x24},
	{0x593A, 0x00},
	{0x593B, 0x7A},
	{0x593C, 0x00},
	{0x593D, 0x24},
	{0x593E, 0x00},
	{0x593F, 0x7A},
	{0x5940, 0x00},
	{0x5941, 0x2F},
	{0x5942, 0x00},
	{0x5943, 0x85},
	{0x5F0E, 0x6E},
	{0x5F11, 0xC6},
	{0x5F17, 0x5E},
	{0x7990, 0x01},
	{0x7993, 0x5D},
	{0x7994, 0x5D},
	{0x7995, 0xA1},
	{0x799A, 0x01},
	{0x799D, 0x00},
	{0x8169, 0x01},
	{0x8359, 0x01},
	{0x9302, 0x1E},
	{0x9306, 0x1F},
	{0x930A, 0x26},
	{0x930E, 0x23},
	{0x9312, 0x23},
	{0x9316, 0x2C},
	{0x9317, 0x19},
	{0xB046, 0x01},
	{0xB048, 0x01},
	{0x0112, 0x0A},
	{0x0113, 0x0A},
	{0x0114, 0x03},
	{0x0342, 0x0A},	//LINE_LENGTH_PCK[15:8]	2560
	{0x0343, 0x00},	//LINE_LENGTH_PCK[7:0]
	{0x0340, 0x08},	//FRM_LENGTH_LINES[15:8] 2134
	{0x0341, 0x56},	//FRM_LENGTH_LINES[7:0]
	{0x0344, 0x00},
	{0x0345, 0x00},
	{0x0346, 0x00},
	{0x0347, 0x00},
	{0x0348, 0x12},
	{0x0349, 0x2F},
	{0x034A, 0x0D},
	{0x034B, 0xA7},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x01},
	{0x0901, 0x22},
	{0x0902, 0x08},
	{0x3F4C, 0x81},
	{0x3F4D, 0x81},
	{0x0408, 0x00},
	{0x0409, 0x0c},	//DIG_CROP_X_OFFSET[7:0]
	{0x040A, 0x00},
	{0x040B, 0x0A},	//DIG_CROP_Y_OFFSET[7:0]
	{0x040C, 0x09},	//DIG_CROP_IMAGE_WIDTH[12:8]
	{0x040D, 0x00},	//DIG_CROP_IMAGE_WIDTH[7:0]
	{0x040E, 0x06},	//DIG_CROP_IMAGE_HEIGHT[11:8]
	{0x040F, 0xC0},	//DIG_CROP_IMAGE_HEIGHT[7:0]
	{0x034C, 0x09},	//X_OUT_SIZE[12:8]	2304-> 2312
	{0x034D, 0x08},	//X_OUT_SIZE[7:0]
	{0x034E, 0x06},	//Y_OUT_SIZE[11:8]	1728-> 1736
	{0x034F, 0xC8},	//Y_OUT_SIZE[7:0]
	{0x0301, 0x06},
	{0x0303, 0x02},
	{0x0305, 0x02},
	{0x0306, 0x00},
	{0x0307, 0x29},
	{0x030B, 0x01},
	{0x030D, 0x02},
	{0x030E, 0x01},
	{0x030F, 0x22},
	{0x0310, 0x00},
	{0x3F78, 0x01},
	{0x3F79, 0x31},
	{0x3FFE, 0x00},
	{0x3FFF, 0x8A},
	{0x5F0A, 0xB6},
	{0x0202, 0x08},
	{0x0203, 0x44},
	{0x0204, 0x00},
	{0x0205, 0x00},
	{0x020E, 0x01},
	{0x020F, 0x00},
	{0x3F15, 0x00},
	{0x0100, 0x01},
};
static struct rts_isp_i2c_reg g_imx471_i2c_init_regs_full[] = {
	{0x0136, 0x18},
	{0x0137, 0x00},
	{0x3C7E, 0x01},
	{0x3C7F, 0x05},
	{0x3E35, 0x00},
	{0x3E36, 0x00},
	{0x3E37, 0x00},
	{0x3F7F, 0x01},
	{0x4431, 0x04},
	{0x531C, 0x01},
	{0x531D, 0x02},
	{0x531E, 0x04},
	{0x5928, 0x00},
	{0x5929, 0x2F},
	{0x592A, 0x00},
	{0x592B, 0x85},
	{0x592C, 0x00},
	{0x592D, 0x32},
	{0x592E, 0x00},
	{0x592F, 0x88},
	{0x5930, 0x00},
	{0x5931, 0x3D},
	{0x5932, 0x00},
	{0x5933, 0x93},
	{0x5938, 0x00},
	{0x5939, 0x24},
	{0x593A, 0x00},
	{0x593B, 0x7A},
	{0x593C, 0x00},
	{0x593D, 0x24},
	{0x593E, 0x00},
	{0x593F, 0x7A},
	{0x5940, 0x00},
	{0x5941, 0x2F},
	{0x5942, 0x00},
	{0x5943, 0x85},
	{0x5F0E, 0x6E},
	{0x5F11, 0xC6},
	{0x5F17, 0x5E},
	{0x7990, 0x01},
	{0x7993, 0x5D},
	{0x7994, 0x5D},
	{0x7995, 0xA1},
	{0x799A, 0x01},
	{0x799D, 0x00},
	{0x8169, 0x01},
	{0x8359, 0x01},
	{0x9302, 0x1E},
	{0x9306, 0x1F},
	{0x930A, 0x26},
	{0x930E, 0x23},
	{0x9312, 0x23},
	{0x9316, 0x2C},
	{0x9317, 0x19},
	{0xB046, 0x01},
	{0xB048, 0x01},
	{0x0112, 0x0A},
	{0x0113, 0x0A},
	{0x0114, 0x03},
	{0x0342, 0x14},	//LINE_LENGTH_PCK[15:8]	5120
	{0x0343, 0x00},	//LINE_LENGTH_PCK[7:0]
	{0x0340, 0x19},	//FRM_LENGTH_LINES[15:8]	6406
	{0x0341, 0x06},	//FRM_LENGTH_LINES[7:0]
	{0x0344, 0x00},
	{0x0345, 0x00},
	{0x0346, 0x00},
	{0x0347, 0x00},
	{0x0348, 0x12},
	{0x0349, 0x2F},
	{0x034A, 0x0D},
	{0x034B, 0xA7},
	{0x0381, 0x01},
	{0x0383, 0x01},
	{0x0385, 0x01},
	{0x0387, 0x01},
	{0x0900, 0x00},
	{0x0901, 0x11},
	{0x0902, 0x0A},
	{0x3F4C, 0x01},
	{0x3F4D, 0x01},
	{0x0408, 0x01},
	//{0x0409, 0x38},
	{0x0409, 0x36},
	{0x040A, 0x00},
	{0x040B, 0xEC},
	{0x040C, 0x0F},
	{0x040D, 0xC0},
	{0x040E, 0x0B},
	{0x040F, 0xD0},
	{0x034C, 0x0F},	//X_OUT_SIZE[12:8]	4032
	{0x034D, 0xC0},	//X_OUT_SIZE[7:0]
	{0x034E, 0x0B},	//Y_OUT_SIZE[11:8]	3024
	{0x034F, 0xD0},	//Y_OUT_SIZE[7:0]
	{0x0301, 0x06},
	{0x0303, 0x02},
	{0x0305, 0x02},
	{0x0306, 0x00},
	{0x0307, 0x29},
	{0x030B, 0x01},
	{0x030D, 0x02},
	{0x030E, 0x01},
	{0x030F, 0x22},
	{0x0310, 0x00},
	{0x3F78, 0x02},
	{0x3F79, 0x0A},
	{0x3FFE, 0x00},
	{0x3FFF, 0x18},
	{0x5F0A, 0xB2},
	{0x0202, 0x18},
	{0x0203, 0xF4},
	{0x0204, 0x00},
	{0x0205, 0x00},
	{0x020E, 0x01},
	{0x020F, 0x00},
	{0x3F15, 0x00},
	{0x0100, 0x01},
};
static int imx471_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	debug("@ imx471_get_info isp_id = %d\n",isp_id);
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;
	i = 0;
	if(sensor_mode == BINNING_MODE){
		printf("imx471_get_info : BINNING_MODE\n");
		info->modes.mode[i].hdr = LINEAR_MODE;
		info->modes.mode[i].size.w = 2304;
		info->modes.mode[i].size.h = 1728;
		info->modes.mode[i].fps = 30.0f; //@MLCK=24MHz
	}
	else{
		printf("imx471_get_info : FULL_MODE\n");
		info->modes.mode[i].hdr = LINEAR_MODE;
		info->modes.mode[i].size.w = 4032;
		info->modes.mode[i].size.h = 3024;
		info->modes.mode[i].fps = 5.0f; //@MLCK=24MHz
	}
	i++;
	info->modes.num = i;
	info->i2c.i2c_id = 0x10;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;
	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH,8000 );
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	down->num = i;
	return RTS_ISP_OK;
}
static int imx471_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct imx471_status *status;
	//uint32_t DDR_Addr_tmp, DDR_Lens_tmp;
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;
	debug("@ imx471_get_init_info mode->fps = %d\n", mode->fps);
	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr
	if(sensor_mode == BINNING_MODE){
		printf("imx471_get_init_info : BINNING_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_imx471_i2c_init_regs_binning, 0);
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;
//		info->size.w = 2304;
//		info->size.h = 1728;
		info->size.w = 2312;
		info->size.h = 1736;
		info->start.x = 1;
		info->start.y = 0;
		//Line Length 2560 ,  Frame Length 2134
		//info->hts = 2560;
		info->hts = 3047;			//196 800 000/30/2134=3074
		info->pclk = 196800000;		//MIPI data rate = 492Mbps,  492*4/10=196.8Mbps
		info->min_vts = status->min_vts = 2134;
		info->max_vts = 65535 - info->min_vts;
		status->exp_step = 1e6 * info->hts / info->pclk; /* us */  //15.48us
	}
	else{
		printf("imx471_get_init_info : FULL_MODE\n");
		set_init_i2c_regs(info->sensor_regs[0], g_imx471_i2c_init_regs_full, 0);
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_10BIT;
		info->mipi_behavor = NONE_HDR;
		info->size.w = 4032;
		info->size.h = 3024;
		info->start.x = 0;
		info->start.y = 0;
		//Line Length 5120 , Frame Length 6406
		//info->hts = 5120;
		info->hts = 6144;			//196 800 000/5/6406=6144
		//info->hts = 3047;			//196 800 000/30/2134=3074
		info->pclk = 196800000;		//MIPI data rate = 492Mbps,  492*4/10=196.8Mbps
		info->min_vts = status->min_vts = 6406;
		//info->min_vts = status->min_vts = 2134;
		info->max_vts = 65535 - info->min_vts;
		status->exp_step = 1e6 * info->hts / info->pclk; /* us */  //31.21us
	}
	return RTS_ISP_OK;
}
static int imx471_start(uint32_t isp_id)
{
	struct imx471_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure[0] = 0;
	return RTS_ISP_OK;
}
static int imx471_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx471_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 18) * status->exp_step;
	}
	//debug("###[exp range] max L%f S%f, min L%f S%f\n", max_exposure[0], max_exposure[1], min_exposure[0], min_exposure[1]);
	return RTS_ISP_OK;
}
static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;
	if (fgain >= ANALOG_GAIN_MAX_RATIO)
		reg_value = 960;
	else
		reg_value = (uint16_t)((1024*fgain-1024)/fgain);
	//debug("### get_sensor_gain_reg fgain=%f, reg_value=%d\n",fgain,reg_value);
	return reg_value;
}
static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain;
	gain = (float)(1024.0/(1024.0-(float)reg_value));
	//debug("### get_sensor_real_gain gain=%f, reg_value=%d\n",gain,reg_value);
	return gain;
}
uint32_t clip_d_word(uint32_t current, uint32_t minimum, uint32_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}
static int imx471_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct imx471_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int imx471_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx471_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;
	return RTS_ISP_OK;
}
static int period=0;
static int imx471_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
#if 1
	int i=0;
	uint16_t exp_lines[2];
	uint16_t gain_reg[2];
	uint32_t frame_length;
	uint16_t shr0,shr1;
	uint16_t rhs1,last_rhs1;
//	uint32_t frame_length;
	struct imx471_status *status;
	struct rts_isp_sync_reg *reg;
	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	reg = regs->reg;
	frame_length = exp_gain->vts;
	debug("###[exp gain info] vmax=%d, last_vts=%d\n",frame_length,status->last_vts);
	debug("###[exp gain info] exp[0]=%f, gain=%fx%f\n",exp_gain->exposure[0],exp_gain->analog_gain[0], exp_gain->digital_gain[0]);
	if (period%10==0){
		printf("### FRM=%d, exp[0]=%f, gain=%fx%f\n",frame_length,exp_gain->exposure[0],exp_gain->analog_gain[0], exp_gain->digital_gain[0]);
	}
	period++;
	i = 0;
	/* set vts */
	if (abs(status->last_vts - frame_length) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x0340, frame_length >> 8);
		set_sync_i2c(&reg[i++], 0x0341, frame_length & 0xff);
		status->last_vts = frame_length;
	}
	/* set exposure */
	if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
		exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
		set_sync_i2c(&reg[i++], 0x0104, 1);	//Group hold
		set_sync_i2c(&reg[i++], 0x0202, exp_lines[0] >> 8);
		set_sync_i2c(&reg[i++], 0x0203, exp_lines[0] & 0xff);
		set_sync_i2c(&reg[i++], 0x0104, 0);	//Group hold
		status->last_exposure[0] = exp_gain->exposure[0];
	}
	gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] * exp_gain->digital_gain[0]);
		/* set gain */
	set_sync_i2c(&reg[i++], 0x0204, gain_reg[0] >> 8);
	set_sync_i2c(&reg[i++], 0x0205, gain_reg[0] & 0xff);
	regs->num = i;
#endif
	return RTS_ISP_OK;
}
static int imx471_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t val;
	struct rts_isp_sync_reg *reg;
	val = mf_info->flip_en != 0;
	val = (mf_info->mirror_en != 0) << 1 | val;
	mf_info->delay_frames = 1;
	i = 0;
	reg = mf_info->regs.reg;
	switch(val)
	{
		case 0:		// Normal
		default:
			set_sync_i2c(&reg[i++], 0x0101, 0x00);
		break;
		case 1:		// Mirror
			set_sync_i2c(&reg[i++], 0x0101, 0x02);
		break;
		case 2:		// VFlip
			set_sync_i2c(&reg[i++], 0x0101, 0x01);
		break;
		case 3:		// Rotate
			set_sync_i2c(&reg[i++], 0x0101, 0x03);
		break;
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}
#if 1
static int imx471_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	/* specify OTP page */
	reg.addr = 0x0a02;
	reg.data = 0x1b;
	ret = rts_isp_write_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	/* Tune on OTP read mode */
	reg.addr = 0x0a00;
	reg.data = 0x01;
	ret = rts_isp_write_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
    rts_isp_sensor_access_prepare();
	reg.addr = 0x0a22;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 4;
	reg.addr = 0x0a23;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
    rts_isp_sensor_access_unprepare();
	if (ret)
		return ret;
	id |= (reg.data >> 4);
	printf("IMX471_check, Sensor ID = %x\n",id);
	return RTS_ISP_OK;
}
#endif
#if 0
static int imx471_check(uint32_t isp_id)
{
	int ret;
	int id, smia;
	struct rts_isp_i2c_reg reg;
    rts_isp_sensor_access_prepare();
	reg.addr = 0x0004;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	smia = reg.data;
	reg.addr = 0x0000;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
	reg.addr = 0x0001;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
    rts_isp_sensor_access_unprepare();
	if (ret)
		return ret;
	id |= reg.data;
	printf("Sensor ID = %x, SMIA ver=%d\n",id,smia);
	return RTS_ISP_OK;
}
#endif
static const struct rts_isp_sensor_ops imx471_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "imx471",
	.get_info = imx471_get_info,
	.get_init_info = imx471_get_init_info,
	.start = imx471_start,
	.get_exposure_range = imx471_get_exposure_range,
	.get_tuned_again = imx471_get_tuned_again,
	.get_tuned_dgain = imx471_get_tuned_dgain,
	.get_exposure_gain_info = imx471_get_exposure_gain_info,
	.set_mirror_flip = imx471_set_mirror_flip,
	.check = imx471_check,
};
const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &imx471_ops;
}
//#endif