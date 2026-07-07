/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Mike Wong <mike.wong@realtek.com>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include <math.h>
#include <isp_reg_lib.h>


#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define float_tol 0.0001f
#define float_ne(x, y) (fabsf((float)x - (float)y) > float_tol)
#define float_eq(x, y) (fabsf((float)x - (float)y) < float_tol)
#define BRL 1109
#define VMAX_VHDR 1250
#define VMAX_LINEAR 1125
#define VPB1 8
#define RHS1_MIN (VPB1 * 2) + 1
#define ANALOG_GAIN_MAX_RATIO 16
#define SENSOR_HDR 0		

struct imx327_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure;
	uint16_t min_vts;
};

#if (SENSOR_HDR == 0)
static struct imx327_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};
#else
static struct imx327_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = HDR_MODE};
#endif

static struct rts_isp_i2c_reg g_imx327_i2c_init_regs_linear[] = {
	{0x3002, 0x00}, {0x3005, 0x00}, {0x3007, 0x00}, {0x3009, 0x02},
	{0x300A, 0x3C}, {0x3011, 0x02}, {0x3018, 0x65}, {0x3019, 0x04},
	{0x301C, 0x30}, {0x301D, 0x11}, {0x3046, 0x00}, {0x304B, 0x0A},
	{0x305C, 0x18}, {0x305D, 0x03}, {0x305E, 0x20}, {0x305F, 0x01},
	{0x309E, 0x4A}, {0x309F, 0x4A}, {0x30D2, 0x19}, {0x30D7, 0x03},
	{0x3129, 0x1D}, {0x313B, 0x61}, {0x315E, 0x1A}, {0x3164, 0x1A},
	{0x317C, 0x12}, {0x31EC, 0x37}, {0x3405, 0x10}, {0x3407, 0x01},
	{0x3414, 0x0A}, {0x3418, 0x49}, {0x3419, 0x04}, {0x3441, 0x0C},
	{0x3442, 0x0C}, {0x3443, 0x01}, {0x3444, 0x20}, {0x3445, 0x25},
	{0x3446, 0x57}, {0x3447, 0x00}, {0x3448, 0x37}, {0x3449, 0x00},
	{0x344A, 0x1F}, {0x344B, 0x00}, {0x344C, 0x1F}, {0x344D, 0x00},
	{0x344E, 0x1F}, {0x344F, 0x00}, {0x3450, 0x77}, {0x3451, 0x00},
	{0x3452, 0x1F}, {0x3453, 0x00}, {0x3454, 0x17}, {0x3455, 0x00},
	{0x3472, 0x9C}, {0x3473, 0x07}, {0x3480, 0x49}, {0x3000, 0x00},
};

static struct rts_isp_i2c_reg g_imx327_i2c_init_regs_hdr[] = {
	{0x3002, 0x00}, {0x3005, 0x01}, {0x3007, 0x00}, {0x3009, 0x01},
	{0x300A, 0xF0}, {0x300C, 0x11}, {0x3011, 0x02}, {0x3018, 0xE2},
	{0x3019, 0x04}, {0x301C, 0x98}, {0x301D, 0x08}, {0x3020, 0x02},
	{0x3021, 0x00}, {0x3024, 0xC9}, {0x3025, 0x07}, {0x3030, 0x11},
	{0x3031, 0x00}, {0x3045, 0x05}, {0x3046, 0x01}, {0x304B, 0x0A},
	{0x305C, 0x18}, {0x305D, 0x03}, {0x305E, 0x20}, {0x305F, 0x01},
	{0x309E, 0x4A}, {0x309F, 0x4A}, {0x30D2, 0x19}, {0x30D7, 0x03},
	{0x3106, 0x11}, {0x3129, 0x00}, {0x313B, 0x61}, {0x315E, 0x1A},
	{0x3164, 0x1A}, {0x317C, 0x00}, {0x31EC, 0x0E}, {0x3405, 0x00},
	{0x3407, 0x01}, {0x3414, 0x0A}, {0x3415, 0x00}, {0x3418, 0xB4},
	{0x3419, 0x08}, {0x3441, 0x0C}, {0x3442, 0x0C}, {0x3443, 0x01},
	{0x3444, 0x20}, {0x3445, 0x25}, {0x3446, 0x77}, {0x3447, 0x00},
	{0x3448, 0x67}, {0x3449, 0x00}, {0x344A, 0x47}, {0x344B, 0x00},
	{0x344C, 0x37}, {0x344D, 0x00}, {0x344E, 0x3F}, {0x344F, 0x00},
	{0x3450, 0xFF}, {0x3451, 0x00}, {0x3452, 0x3F}, {0x3453, 0x00},
	{0x3454, 0x37}, {0x3455, 0x00}, {0x3472, 0xA0}, {0x3473, 0x07},
	{0x347B, 0x23}, {0x3480, 0x49}, {0x3000, 0x00},
};

static int imx327_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;
#if (SENSOR_HDR == 0)
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30.0f; //@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 27.0f; //@MLCK=27MHz
	i++;
	info->modes.num = i;
#else
	info->modes.mode[i].hdr = HDR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 27.0f; //@MLCK=27MHz
	i++;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 1920;
	info->modes.mode[i].size.h = 1080;
	info->modes.mode[i].fps = 30.0f; //@MLCK=27MHz
	i++;
	info->modes.num = i;
#endif

	info->i2c.i2c_id = 0x1A;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	//set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V2, 0);
	//set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 0);
	//set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V9, 1);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_37M125, 500);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_12M, 500);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 500);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 20000);
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


static int imx327_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				   struct rts_isp_sensor_init_info *info)
{
	struct imx327_status *status;
	//uint32_t DDR_Addr_tmp, DDR_Lens_tmp;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	if (mode->hdr == HDR_MODE) {
		//debug("hdr line 2to1 mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx327_i2c_init_regs_hdr, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_12BIT;
		info->interface.vhdr_start_line_tnr = 3;
		info->mipi_behavor = FID_BASED_HDR;

		info->size.w = 1948;
		info->size.h = 1097;
		info->start.x = 13;
		info->start.y = 8;

		info->hts = 4400;
		info->pclk = 148500000;
		info->min_vts = status->min_vts = VMAX_VHDR;
		//info->max_vts = info->min_vts * 2;
		info->max_vts = info->min_vts * 15;

		status->exp_step = 1e6 * info->hts / 2 / info->pclk; /* us */
	} else {
		//debug("linear mode\n");
		set_init_i2c_regs(info->sensor_regs[0],
				  g_imx327_i2c_init_regs_linear, 0);

		info->interface.interface = SNR_INTERFACE_MIPI;
		info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
		info->interface.mipi.hs_term = 0x3;
		info->interface.type = RAW_SENSOR;
		info->interface.bit_depth = SNR_12BIT;
		info->mipi_behavor = NONE_HDR;

		info->size.w = 1948;
		info->size.h = 1097;
		info->start.x = 13;
		info->start.y = 4;

		info->hts = 2200;
		info->pclk = 74250000;
		info->min_vts = status->min_vts = VMAX_LINEAR;
		//info->max_vts = 65535 - info->min_vts;
		info->max_vts = info->min_vts * 30;

		status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	}

	return RTS_ISP_OK;
}

static int imx327_start(uint32_t isp_id)
{
	struct imx327_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static int imx327_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx327_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 4) * status->exp_step;
	} else {
		uint32_t tmp1;
		uint32_t tmp2;
		uint32_t tmp3;

		tmp1 = (uint32_t)((vts * 2 - 8) / (ratio[0] + 1));
		tmp2 = vts * 2 - BRL * 2 - 21 - (2 + 1);
		tmp3 = (VMAX_VHDR + 7) / 8 * 2 - 1 - 2; /* vbp1 <= round(1350 / 8) */
		tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		tmp1 = tmp1 < tmp3 ? tmp1 : tmp3;
		max_exposure[1] = tmp1 * status->exp_step;
		min_exposure[1] = status->exp_step;
		max_exposure[0] = max_exposure[1] * ratio[0];
		min_exposure[0] = min_exposure[1] * ratio[0];
	}

	// _rtl_printf("max_exposure %f %f\n", max_exposure[0], max_exposure[1]);
	// _rtl_printf("min_exposure %f %f\n", min_exposure[0], min_exposure[1]);
	// _rtl_printf("ratio vts    %f %d\n", ratio[0], vts);

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	reg_value = (uint16_t)(66.4386 * log10f(fgain));

	if (fgain >= ANALOG_GAIN_MAX_RATIO)
		reg_value = 0x50;
	else
		reg_value = (uint16_t)(66.4386 * log10f(fgain));

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain;

	gain = (float)pow(10.0, (double)reg_value / 66.4386);

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

static int imx327_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct imx327_status *status;

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

static int imx327_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct imx327_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	dgain[0] = 1.0f;
	if (status->hdr == HDR_MODE)
		dgain[1] = 1.0f;

	return RTS_ISP_OK;
}

static int imx327_get_exposure_gain_info(uint32_t isp_id,
		const struct rts_isp_sensor_exp_gain *exp_gain,
		struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t exp_lines[2];
	uint16_t shs1;
	uint16_t rhs1;
	uint16_t shs2;
	uint16_t y_out_size;
	uint16_t gain_reg[2];
	uint32_t fsc;
	uint32_t vmax;
	struct imx327_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		exp_lines[0] = exp_gain->exposure[0] / status->exp_step;
		vmax = exp_gain->vts - 20;
		fsc = vmax;
		shs1 = fsc - exp_lines[0] - 1;

		gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] *
						  exp_gain->digital_gain[0]);
		reg = regs->reg;

		i = 0;
		/* set vts */
		set_sync_i2c(&reg[i++], 0x3018, vmax & 0xff);
		set_sync_i2c(&reg[i++], 0x3019, vmax >> 8);
		/* set exposure */
		set_sync_i2c(&reg[i++], 0x3020, shs1 & 0xff);
		set_sync_i2c(&reg[i++], 0x3021, shs1 >> 8);
		/* set gain */
		set_sync_i2c(&reg[i++], 0x3014, gain_reg[0] & 0xff);
		regs->num = i;
	} else if (status->hdr == HDR_MODE) {
		exp_lines[0] = exp_gain->exposure[0] / status->exp_step;
		exp_lines[1] = exp_gain->exposure[1] / status->exp_step;
		vmax = exp_gain->vts;
		fsc = vmax * 2;

		shs1 = (exp_lines[1] % 2) + 2;
		rhs1 = shs1 + exp_lines[1] + 1;

		// Processing time diff between short exp and long exp.
		if (rhs1 < RHS1_MIN) {
			rhs1 = RHS1_MIN;
			shs1 = rhs1 - exp_lines[1] - 1;
		}

		shs2 = fsc - exp_lines[0] - 1;
		if (shs2 < (rhs1+2)) {
			shs2 = (rhs1+2);
		}

		y_out_size = (BRL + (rhs1 - 1) / 2) * 2;

		gain_reg[0] = get_sensor_gain_reg(exp_gain->analog_gain[0] *
						  exp_gain->digital_gain[0]);
		gain_reg[1] = get_sensor_gain_reg(exp_gain->analog_gain[1] *
						  exp_gain->digital_gain[1]);
		reg = regs->reg;

		i = 0;
		/* set gain */
		set_sync_i2c(&reg[i++], 0x3014, gain_reg[0] & 0xff);
		set_sync_i2c(&reg[i++], 0x30f2, gain_reg[1] & 0xff);
		/* set exposure */
		set_sync_i2c(&reg[i++], 0x3020, shs1 & 0xff);
		set_sync_i2c(&reg[i++], 0x3021, shs1 >> 8);
		set_sync_i2c(&reg[i++], 0x3024, shs2 & 0xff);
		set_sync_i2c(&reg[i++], 0x3025, shs2 >> 8);
		//set_sync_info(&reg[i++], 1, RTS_ISP_INT_DATA_START);
		set_sync_i2c(&reg[i++], 0x3030, rhs1 & 0xff);
		set_sync_i2c(&reg[i++], 0x3031, rhs1 >> 8);
		set_sync_i2c(&reg[i++], 0x3418, y_out_size & 0xff);
		set_sync_i2c(&reg[i++], 0x3419, y_out_size >> 8);
		/* set vts */
		set_sync_i2c(&reg[i++], 0x3018, vmax & 0xff);
		set_sync_i2c(&reg[i++], 0x3019, vmax >> 8);
		regs->num = i;
	}
	return RTS_ISP_OK;
}

static int imx327_set_mirror_flip(uint32_t isp_id,
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

	set_sync_i2c(&reg[i++], 0x3007, val);

	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int imx327_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x301E;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;
	
	reg.addr = 0x301F;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	
    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0xB201)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops imx327_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "imx327",
	.get_info = imx327_get_info,
	.get_init_info = imx327_get_init_info,
	.start = imx327_start,
	.get_exposure_range = imx327_get_exposure_range,
	.get_tuned_again = imx327_get_tuned_again,
	.get_tuned_dgain = imx327_get_tuned_dgain,
	.get_exposure_gain_info = imx327_get_exposure_gain_info,
	.set_mirror_flip = imx327_set_mirror_flip,
	.check = imx327_check,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &imx327_ops;
}