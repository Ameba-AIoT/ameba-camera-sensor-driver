/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include <math.h>
#include <isp_reg_lib.h>


//#if _IMX775_SENSOR_

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

struct imx775_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure[2];
	uint32_t last_vts;
	uint16_t min_vts;
};

static struct imx775_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static struct rts_isp_i2c_reg g_imx775_i2c_init_regs_standby[] = {
	{0x25b1,0x96},
	{0x25b1,0x69}
};

static struct rts_isp_i2c_reg g_imx775_i2c_init_regs_linear[] = {
	{0x00E1,0x01},
};

// chip prepare must be run before this call
static int get_chip_state(uint32_t isp_id)
{
	struct rts_isp_i2c_reg reg;
	int ret;


	//read 0x25e4 to get the state of the device
	reg.addr = 0x25e4;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (!ret) {
		printf("%s: sensor state = 0x%04x\r\n", __func__, reg.data);
	} else {
		printf("%s: error %d getting sensor state\r\n", __func__, ret);
	}
	return ret;
};

static int imx775_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	//debug("@ imx775_get_info isp_id = %d\n",isp_id);

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2592;
	info->modes.mode[i].size.h = 1944;
	info->modes.mode[i].fps = 30.0f; //@MLCK=24MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 2592;
	info->modes.mode[i].size.h = 1944;
	info->modes.mode[i].fps = 30.0f; //@MLCK=24MHz
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = 0x1b;//0x1b, 0x1a, 0x36, 0x34
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	#if 1	//sensor responds to target address 0x1B
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);	//turn on GPIOA_5, which isn't connected to sensor imx775
	set_power_item(&up->items[i++], SNR_HCLK, CLK_NONE, 50);			//stop the clock
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 10);		//de-assert reset
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 50);		//de-assert SSOR_PDN / SSPDN - turns off PP_IOVDD, disables level translator
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10);			//assert reset
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 100);			//start the 24MHz clock, requires >= 100 microseconds of cycles while reset asserted
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 200);	//assert SSOR_PDN/SSPDN - turns on PP_IOVDD, enables level translation
	//set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 1000);			//assert reset
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 500);		//de-assert reset; I2C won't work for another 250 microseconds
	#elif 1	//sensor responds to target address 0x1B
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);	//power on - assert SSOR_PDN/SSPDN - turns on PP_IOVDD, enables level translation
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);		//into reset
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);		//start the clock
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);	//out of reset
	#else //orig from Realtek
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 500);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
	#endif

	up->num = i;
	i = 0;
	
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 1);
	set_power_item(&down->items[i++], SNR_HCLK, CLK_NONE, 1);
	down->num = i;

	return RTS_ISP_OK;
}


static int imx775_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct imx775_status *status;
	//uint32_t DDR_Addr_tmp, DDR_Lens_tmp;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//debug("@ imx775_get_init_info mode->fps = %d\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	if (mode->hdr == HDR_MODE) {

	} else {
		//debug("linear mode\n");
		
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx775_i2c_init_regs_standby, 8000);
				  
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx775_i2c_init_regs_linear, 24000);
		
		
		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1 | MIPI_LANE2 | MIPI_LANE3;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_12BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 2600;
		info->size.h = 1952;
		info->start.x = 4;
		info->start.y = 4;

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

static int imx775_start(uint32_t isp_id)
{
	struct imx775_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	//printf("%s %d **************************************\r\n", __func__, __LINE__);
	status = &g_status[isp_id];

	status->last_exposure[0] = 0;

	//get_chip_state(isp_id);
	return RTS_ISP_OK;
}


static int imx775_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx775_status *status;

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

static int imx775_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct imx775_status *status;

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

static int imx775_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx775_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int imx775_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	return RTS_ISP_OK;
}

static int imx775_set_mirror_flip(uint32_t isp_id,
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
			set_sync_i2c(&reg[i++], 0x28b2, 0x00);
			set_sync_i2c(&reg[i++], 0x764e, 0x00);
		break;
		case 1:		// Mirror (HFlip)
			set_sync_i2c(&reg[i++], 0x28b2, 0x00);
			set_sync_i2c(&reg[i++], 0x764e, 0x01);
		break;
		case 2:		// VFlip
			set_sync_i2c(&reg[i++], 0x28b2, 0x01);
			set_sync_i2c(&reg[i++], 0x764e, 0x00);
		break;
		case 3:		// Rotate
			set_sync_i2c(&reg[i++], 0x28b2, 0x01);
			set_sync_i2c(&reg[i++], 0x764e, 0x01);
		break;
	}

	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int imx775_check(uint32_t isp_id)
{
	int ret;
	int id;

//	vTaskDelay(15);
//	imx775_register_check(1);

	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x2509;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x25b1;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	printf(" imx775_register: id=%d\n",id);
	if (id == 0xa328)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;

}

static const struct rts_isp_sensor_ops imx775_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "imx775",
	.get_info = imx775_get_info,
	.get_init_info = imx775_get_init_info,
	.start = imx775_start,
	.get_exposure_range = imx775_get_exposure_range,
	.get_tuned_again = imx775_get_tuned_again,
	.get_tuned_dgain = imx775_get_tuned_dgain,
	.get_exposure_gain_info = imx775_get_exposure_gain_info,
	.set_mirror_flip = imx775_set_mirror_flip,
	.check = imx775_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &imx775_ops;
}

//#endif
