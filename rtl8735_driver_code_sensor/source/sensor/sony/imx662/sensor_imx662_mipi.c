/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include <math.h>
#include <isp_reg_lib.h>


//#if _IMX662_SENSOR_

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


#define BRL 1120
#define VMAX_VHDR 1250
#define VMAX_LINEAR 1250

#define SHR1_MIN 5
//#define RHS1_MIN 7
#define VPB1 8
#define RHS1_MIN (VPB1 * 2) + 3

#define ANALOG_GAIN_MAX_RATIO 31.6227f //analog gain 30dB

struct imx662_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
};

static struct imx662_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static struct rts_isp_i2c_reg g_imx662_i2c_init_regs_linear[] = {
	/*
	{0x303C, 0x00}, 	//WIN H Start
	{0x303D, 0x00}, 
	{0x303E, 0x90}, 	//WIN H Width =1936
	{0x303F, 0x07}, 
	
	{0x3044, 0x00}, 	//WIN V Start
	{0x3045, 0x00}, 
	{0x3046, 0x4C}, 	//WIN V Width =1100
	{0x3047, 0x04}, 
	
	{0x3028, 0xE2}, 	//VMAX 4E2=1250
	{0x3029, 0x04}, 
	{0x302A, 0x00}, 
	*/
	{0x3002, 0x00}, 
	
	{0x3014, 0x04}, 
	{0x3015, 0x07}, 
	{0x301A, 0x00}, 
	{0x301C, 0x00}, 
	{0x302C, 0xBC}, //HMAX 7BC=1980 
	{0x302D, 0x07}, 
	{0x3050, 0x04}, 
	{0x3051, 0x00}, 
	{0x3054, 0x0E}, 
	{0x3060, 0x16}, 
	{0x3061, 0x01}, 
	{0x30A6, 0x00}, 
	{0x3400, 0x01}, 
	{0x3444, 0xAC}, 
	{0x3460, 0x21}, 
	{0x3492, 0x08}, 
	{0x3B00, 0x39}, 
	{0x3B23, 0x2D}, 
	{0x3B45, 0x04}, 
	{0x3C0A, 0x1F}, 
	{0x3C0B, 0x1E}, 
	{0x3C38, 0x21}, 
	{0x3C44, 0x00}, 
	{0x3CB6, 0xD8}, 
	{0x3CC4, 0xDA}, 
	{0x3E24, 0x79}, 
	{0x3E2C, 0x15}, 
	{0x3EDC, 0x2D}, 
	{0x4498, 0x05}, 
	{0x449C, 0x19}, 
	{0x449D, 0x00}, 
	{0x449E, 0x32}, 
	{0x449F, 0x01}, 
	{0x44A0, 0x92}, 
	{0x44A2, 0x91}, 
	{0x44A4, 0x8C}, 
	{0x44A6, 0x87}, 
	{0x44A8, 0x82}, 
	{0x44AA, 0x78}, 
	{0x44AC, 0x6E}, 
	{0x44AE, 0x69}, 
	{0x44B0, 0x92}, 
	{0x44B2, 0x91}, 
	{0x44B4, 0x8C}, 
	{0x44B6, 0x87}, 
	{0x44B8, 0x82}, 
	{0x44BA, 0x78}, 
	{0x44BC, 0x6E}, 
	{0x44BE, 0x69}, 
	{0x44C0, 0x7F}, 
	{0x44C1, 0x01}, 
	{0x44C2, 0x7F}, 
	{0x44C3, 0x01}, 
	{0x44C4, 0x7A}, 
	{0x44C5, 0x01}, 
	{0x44C6, 0x7A}, 
	{0x44C7, 0x01}, 
	{0x44C8, 0x70}, 
	{0x44C9, 0x01}, 
	{0x44CA, 0x6B}, 
	{0x44CB, 0x01}, 
	{0x44CC, 0x6B}, 
	{0x44CD, 0x01}, 
	{0x44CE, 0x5C}, 
	{0x44CF, 0x01}, 
	{0x44D0, 0x7F}, 
	{0x44D1, 0x01}, 
	{0x44D2, 0x7F}, 
	{0x44D3, 0x01}, 
	{0x44D4, 0x7A}, 
	{0x44D5, 0x01}, 
	{0x44D6, 0x7A}, 
	{0x44D7, 0x01}, 
	{0x44D8, 0x70}, 
	{0x44D9, 0x01}, 
	{0x44DA, 0x6B}, 
	{0x44DB, 0x01}, 
	{0x44DC, 0x6B}, 
	{0x44DD, 0x01}, 
	{0x44DE, 0x5C}, 
	{0x44DF, 0x01}, 
	{0x4534, 0x1C}, 
	{0x4535, 0x03}, 
	{0x4538, 0x1C}, 
	{0x4539, 0x1C}, 
	{0x453A, 0x1C}, 
	{0x453B, 0x1C}, 
	{0x453C, 0x1C}, 
	{0x453D, 0x1C}, 
	{0x453E, 0x1C}, 
	{0x453F, 0x1C}, 
	{0x4540, 0x1C}, 
	{0x4541, 0x03}, 
	{0x4542, 0x03}, 
	{0x4543, 0x03}, 
	{0x4544, 0x03}, 
	{0x4545, 0x03}, 
	{0x4546, 0x03}, 
	{0x4547, 0x03}, 
	{0x4548, 0x03}, 
	{0x4549, 0x03}, 

	{0x3000, 0x00}, 
};

static struct rts_isp_i2c_reg g_imx662_i2c_init_regs_hdr[] = {

	{0x3002, 0x00}, 
			
	{0x3014, 0x04}, 
	{0x3015, 0x07}, 
	{0x301A, 0x01}, 
	{0x301C, 0x01}, 
	{0x302C, 0xDE}, //HMAX 7BC=990 
	{0x302D, 0x03}, 
	{0x3050, 0xdc}, //SHR0	shutter of LEF					//0x97a
	{0x3051, 0x05}, 
	{0x3054, 0x05}, //SHR1	shutter of SEF1
	{0x3060, 0x63}, //RHS1	readout timimg of SEF1			//0x0d 
	{0x3061, 0x00}, 
	{0x30A6, 0x00}, 
	{0x3400, 0x00}, 
	{0x3444, 0xAC}, 
	{0x3460, 0x21}, 
	{0x3492, 0x08}, 
	{0x3B00, 0x39}, 
	{0x3B23, 0x2D}, 
	{0x3B45, 0x04}, 
	{0x3C0A, 0x1F}, 
	{0x3C0B, 0x1E}, 
	{0x3C38, 0x21}, 
	{0x3C44, 0x00}, 
	{0x3CB6, 0xD8}, 
	{0x3CC4, 0xDA}, 
	{0x3E24, 0x79}, 
	{0x3E2C, 0x15}, 
	{0x3EDC, 0x2D}, 
	{0x4498, 0x05}, 
	{0x449C, 0x19}, 
	{0x449D, 0x00}, 
	{0x449E, 0x32}, 
	{0x449F, 0x01}, 
	{0x44A0, 0x92}, 
	{0x44A2, 0x91}, 
	{0x44A4, 0x8C}, 
	{0x44A6, 0x87}, 
	{0x44A8, 0x82}, 
	{0x44AA, 0x78}, 
	{0x44AC, 0x6E}, 
	{0x44AE, 0x69}, 
	{0x44B0, 0x92}, 
	{0x44B2, 0x91}, 
	{0x44B4, 0x8C}, 
	{0x44B6, 0x87}, 
	{0x44B8, 0x82}, 
	{0x44BA, 0x78}, 
	{0x44BC, 0x6E}, 
	{0x44BE, 0x69}, 
	{0x44C0, 0x7F}, 
	{0x44C1, 0x01}, 
	{0x44C2, 0x7F}, 
	{0x44C3, 0x01}, 
	{0x44C4, 0x7A}, 
	{0x44C5, 0x01}, 
	{0x44C6, 0x7A}, 
	{0x44C7, 0x01}, 
	{0x44C8, 0x70}, 
	{0x44C9, 0x01}, 
	{0x44CA, 0x6B}, 
	{0x44CB, 0x01}, 
	{0x44CC, 0x6B}, 
	{0x44CD, 0x01}, 
	{0x44CE, 0x5C}, 
	{0x44CF, 0x01}, 
	{0x44D0, 0x7F}, 
	{0x44D1, 0x01}, 
	{0x44D2, 0x7F}, 
	{0x44D3, 0x01}, 
	{0x44D4, 0x7A}, 
	{0x44D5, 0x01}, 
	{0x44D6, 0x7A}, 
	{0x44D7, 0x01}, 
	{0x44D8, 0x70}, 
	{0x44D9, 0x01}, 
	{0x44DA, 0x6B}, 
	{0x44DB, 0x01}, 
	{0x44DC, 0x6B}, 
	{0x44DD, 0x01}, 
	{0x44DE, 0x5C}, 
	{0x44DF, 0x01}, 
	{0x4534, 0x1C}, 
	{0x4535, 0x03}, 
	{0x4538, 0x1C}, 
	{0x4539, 0x1C}, 
	{0x453A, 0x1C}, 
	{0x453B, 0x1C}, 
	{0x453C, 0x1C}, 
	{0x453D, 0x1C}, 
	{0x453E, 0x1C}, 
	{0x453F, 0x1C}, 
	{0x4540, 0x1C}, 
	{0x4541, 0x03}, 
	{0x4542, 0x03}, 
	{0x4543, 0x03}, 
	{0x4544, 0x03}, 
	{0x4545, 0x03}, 
	{0x4546, 0x03}, 
	{0x4547, 0x03}, 
	{0x4548, 0x03}, 
	{0x4549, 0x03}, 
	{0x3000, 0x00}, 

};

static int imx662_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	//debug("@ imx662_get_info isp_id = %d\n",isp_id);

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30.0f; //@MLCK=24MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30.0f; //@MLCK=24MHz
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = 0x1A;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 500);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 2000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 2000);
	
	up->num = i;
	i = 0;
	
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1);
	set_power_item(&down->items[i++], SNR_IO_POWER, 0, 0);
	set_power_item(&down->items[i++], SNR_CORE_POWER, 0, 0);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, 0, 0);
	down->num = i;

	return RTS_ISP_OK;
}


static int imx662_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct imx662_status *status;
	//uint32_t DDR_Addr_tmp, DDR_Lens_tmp;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//debug("@ imx662_get_init_info mode->fps = %d\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	if (mode->hdr == HDR_MODE) {
		//debug("hdr line 2to1 mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx662_i2c_init_regs_hdr, 24000);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_12BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = VC_HDR;

		info->size.w = 1936;
		info->size.h = 1100;
		info->start.x = 9;
		info->start.y = 16;
		
		//info->hts = 990;
		//info->pclk = 74250000
		info->hts = 5280;
		info->pclk = 198000000;
		info->min_vts = status->min_vts = VMAX_VHDR;
		info->max_vts = info->min_vts * 2;

		status->exp_step = 1e6 * info->hts /2/ info->pclk; /* us */ //13.33us
	} else {
		//debug("linear mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx662_i2c_init_regs_linear, 24000);

		//imx662_register_check();

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_12BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 1936;
		info->size.h = 1100;
		info->start.x = 9;
		info->start.y = 10;

		//info->hts = 1980;
		//info->pclk = 74250000;
		info->hts = 5280;			//198000000/30/1250=5280
		info->pclk = 198000000;		//MIPI data rate = 594Mbps,  594*4/12=198Mbps
		
		info->min_vts = status->min_vts = VMAX_LINEAR;
		info->max_vts = 65535 - info->min_vts;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */  //26.66us
	}

	return RTS_ISP_OK;
}

static int imx662_start(uint32_t isp_id)
{
	struct imx662_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;

	return RTS_ISP_OK;
}


static int imx662_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx662_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = 4* status->exp_step;
		max_exposure[0] = (vts - 1) * status->exp_step;
	} 
	else {
		uint32_t tmp1,tmp2,tmp3;
		tmp1 = (uint32_t)((vts * 2 - (SHR1_MIN + 2 + 5)) / (ratio[0] + 1));		//max shr0 / ratio
		tmp2 = (BRL * 2 - 1) - SHR1_MIN;											//max rhs1 - min shr1
		tmp3 = (vts * 2) - (BRL * 2) - 1;											//FSC - BRL*2

		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		tmp1 = tmp1 < tmp3 ? tmp1 : tmp3;

		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = 2 * status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
	}
	
	//debug("###[exp range] max L%f S%f, min L%f S%f\n", max_exposure[0], max_exposure[1], min_exposure[0], min_exposure[1]);
	
	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	reg_value = (uint16_t)(66.6666 * log10f(fgain));

	if (fgain >= ANALOG_GAIN_MAX_RATIO)
		reg_value = 0x64;
	else
		reg_value = (uint16_t)(66.6666 * log10f(fgain));

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain;

	gain = (float)pow(10.0, (double)reg_value / 66.6666);

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

static int imx662_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct imx662_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);
	if (status->hdr == HDR_MODE) {
		gain_reg = get_sensor_gain_reg(again[1]);
		again[1] = get_sensor_real_gain(gain_reg);
	}

	return RTS_ISP_OK;
}

static int imx662_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx662_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int imx662_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
#if 1
	int i;
	uint16_t exp_lines[2];
	uint16_t gain_reg[2];

	uint32_t fsc,vmax;
	uint16_t shr0,shr1;
	uint16_t rhs1,last_rhs1;

//	uint32_t frame_length;
	struct imx662_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	reg = regs->reg;

	if (status->hdr == LINEAR_MODE) {
		vmax = exp_gain->vts;
		fsc = vmax;

		debug("###[exp gain info] vmax=%d, last_vts=%d\n",vmax,status->last_vts);
		debug("###[exp gain info] exp[0]=%f, gain=%fx%f\n",exp_gain->exposure[0],exp_gain->analog_gain[0], exp_gain->digital_gain[0]);

		i = 0;

		/* set vts */
		if (abs(status->last_vts - vmax) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3028, vmax & 0xff);
			set_sync_i2c(&reg[i++], 0x3029, vmax >> 8);

			status->last_vts = vmax;
		}

		/* set exposure */
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
			shr0 = vmax - exp_lines[0];
			set_sync_i2c(&reg[i++], 0x3050, shr0 & 0xff);
			set_sync_i2c(&reg[i++], 0x3051, shr0 >> 8);

			status->last_exposure[0] = exp_gain->exposure[0];
		}

		gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] *
						  exp_gain->digital_gain[0]);
		//debug("###[exp gain info] gain_reg=%d\n",gain_reg[0]);

		/* set gain */
		set_sync_i2c(&reg[i++], 0x3070, gain_reg[0] & 0xff);
		set_sync_i2c(&reg[i++], 0x3071, gain_reg[0] >> 8);

	}
	else if (status->hdr == HDR_MODE) {
		vmax = exp_gain->vts;
		fsc = vmax * 2;

		reg = regs->reg;
		i = 0;
		/* set vts */
		if (abs(status->last_vts - vmax) > 0.001f) {
			set_sync_i2c(&reg[i++], 0x3028, vmax & 0xff);
			set_sync_i2c(&reg[i++], 0x3029, vmax >> 8);

			status->last_vts = vmax;
		}

		/* set exposure */
		if ( (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) && (abs(status->last_exposure[1] - exp_gain->exposure[1]) > 0.001f)) {
			exp_lines[0] = (float)(exp_gain->exposure[0] / status->exp_step + 0.5f);
			exp_lines[1] = (float)(exp_gain->exposure[1] / status->exp_step + 0.5f);

			/* long exposure */													
			shr0 = fsc - exp_lines[0];
			shr0 = (shr0 % 2) ? shr0 + 1 : shr0;				//SHR1 must be an even number

			/* short exposure */									//short exposure line must be an even
			shr1 = SHR1_MIN;
			rhs1 = shr1	+ exp_lines[1];

			rhs1 = (rhs1 < (shr0-5)) ? rhs1 : (shr0-5);			//RHS1 setting rule
			rhs1 = (rhs1 > (shr1+2)) ? rhs1 : (shr1+2);
			
			if ((last_rhs1 + (BRL * 2) + 4) > (fsc + rhs1))	//RHS1 changing rule
				rhs1 = (last_rhs1 + (BRL * 2) + 4) - fsc; 
			
			rhs1 = (rhs1 % 2) ? rhs1 : rhs1 + 1;				//RHS1 must be an odd number

			if (rhs1 < RHS1_MIN) {								// Processing time diff between short exp and long exp.
				rhs1 = RHS1_MIN;
				shr1 = rhs1 - exp_lines[1];
				shr1 = (shr1 < (rhs1-2)) ? shr1 : (rhs1-2);		//SHR1 setting rule
				shr1 = (shr1 > SHR1_MIN) ? shr1 : SHR1_MIN;		
				
				shr1 = (shr1 % 2) ? rhs1 : rhs1 - 1;			//SHR1 must be an odd number	
			}	
			
			set_sync_i2c(&reg[i++], 0x3054, shr1 & 0xff);
			set_sync_i2c(&reg[i++], 0x3055, shr1 >> 8);
			
			set_sync_i2c(&reg[i++], 0x3060, rhs1 & 0xff);
			set_sync_i2c(&reg[i++], 0x3061, rhs1 >> 8);
			
			set_sync_i2c(&reg[i++], 0x3050, shr0 & 0xff);
			set_sync_i2c(&reg[i++], 0x3051, shr0 >> 8);

			status->last_exposure[0] = exp_gain->exposure[0];
			status->last_exposure[1] = exp_gain->exposure[1];
			
			last_rhs1 = rhs1;
			
			//debug("###[exp gain] fsc=%d, vmax=%d\n",fsc,vmax);
			//debug("###[exp gain] shr0=%d, shr1=%d, rhs1=%d\n",shr0,shr1,rhs1);
			//debug("###[exp gain] exp[0]=%f,[1]=%f, gain=%fx%f, gain_reg=%d\n",exp_gain->exposure[0],exp_gain->exposure[1],exp_gain->analog_gain[0], exp_gain->digital_gain[0],gain_reg[0]);
		}

		/* set gain */
		gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] *
						  exp_gain->digital_gain[0]);
		gain_reg[1] = get_sensor_gain_reg(exp_gain->analog_gain[1] *
						  exp_gain->digital_gain[1]);

		set_sync_i2c(&reg[i++], 0x3070, gain_reg[0] & 0xff);
		set_sync_i2c(&reg[i++], 0x3071, gain_reg[0] >> 8);
		set_sync_i2c(&reg[i++], 0x3072, gain_reg[1] & 0xff);
		set_sync_i2c(&reg[i++], 0x3073, gain_reg[1] >> 8);	
	}
	
	regs->num = i;

#endif
	return RTS_ISP_OK;
}

static int imx662_set_mirror_flip(uint32_t isp_id,
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
			set_sync_i2c(&reg[i++], 0x3020, 0x00);
			set_sync_i2c(&reg[i++], 0x3021, 0x00);
		break;
		case 1:		// Mirror
			set_sync_i2c(&reg[i++], 0x3020, 0x01);
			set_sync_i2c(&reg[i++], 0x3021, 0x00);
		break;
		case 2:		// VFlip
			set_sync_i2c(&reg[i++], 0x3020, 0x00);
			set_sync_i2c(&reg[i++], 0x3021, 0x01);
		break;
		case 3:		// Rotate
			set_sync_i2c(&reg[i++], 0x3020, 0x01);
			set_sync_i2c(&reg[i++], 0x3021, 0x01);
		break;
	}

	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int imx662_check(uint32_t isp_id)
{
	return RTS_ISP_OK;

}

static const struct rts_isp_sensor_ops imx662_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "imx662",
	.get_info = imx662_get_info,
	.get_init_info = imx662_get_init_info,
	.start = imx662_start,
	.get_exposure_range = imx662_get_exposure_range,
	.get_tuned_again = imx662_get_tuned_again,
	.get_tuned_dgain = imx662_get_tuned_dgain,
	.get_exposure_gain_info = imx662_get_exposure_gain_info,
	.set_mirror_flip = imx662_set_mirror_flip,
	.check = imx662_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &imx662_ops;
}

//#endif
