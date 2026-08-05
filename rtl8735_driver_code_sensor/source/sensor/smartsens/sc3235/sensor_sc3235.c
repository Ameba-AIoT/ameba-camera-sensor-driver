/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <rts_isp_sensor.h>
#include <sensor_entry.h>
#ifdef _SC3235_SENSOR_


/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint16_t hts;
	uint32_t clk;
};

struct sc3235_status {
	float row_time;
	float last_exposure;
	uint16_t min_vts;
	struct rts_isp_i2c_reg regs1[2];
};

int isp_driver_is_fpga(void);
const void *sc3235_get_patch_ops(void);

static struct sc3235_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_sc3235_fps_info_fpga[] = {
	{15, 2400, 48600000},
};

static const struct fps_info g_sc3235_fps_info_asic[] = {
	{30, 2400, 97200000},
};

static struct rts_isp_i2c_reg g_sc3235_i2c_init_regs_fpga[] = {
	{0x0103, 0x01}, {0x0100, 0x00}, {0x3641, 0x0c}, {0x36e9, 0x07},
	{0x36eb, 0x05}, {0x36ec, 0x15}, {0x36ed, 0x04}, {0x36f9, 0x33},
	{0x36fb, 0x23}, {0x36fc, 0x01}, {0x36fd, 0x14}, {0x3641, 0x00},
	{0x3e09, 0x20}, {0x3637, 0x2c}, {0x3630, 0x83}, {0x3635, 0x10},
	{0x363b, 0x10}, {0x363c, 0x07}, {0x3306, 0x58}, {0x330a, 0x00},
	{0x330b, 0xd8}, {0x3638, 0x28}, {0x331c, 0x01}, {0x3304, 0x30},
	{0x331e, 0x29}, {0x3320, 0x03}, {0x3356, 0x01}, {0x57a4, 0xa0},
	{0x5781, 0x04}, {0x5782, 0x04}, {0x5783, 0x02}, {0x5784, 0x02},
	{0x5785, 0x40}, {0x5786, 0x20}, {0x5787, 0x18}, {0x5788, 0x10},
	{0x5789, 0x10}, {0x578a, 0x30}, {0x3908, 0x11}, {0x3622, 0xf6},
	{0x3e25, 0x03}, {0x3e26, 0x20}, {0x3902, 0xc5}, {0x3905, 0x99},
	{0x3314, 0x94}, {0x3347, 0x05}, {0x3301, 0x80}, {0x3630, 0xc3},
	{0x3633, 0x42}, {0x363a, 0xa8}, {0x3614, 0x80}, {0x3632, 0x18},
	{0x3631, 0x8a}, {0x3e01, 0x62}, {0x363b, 0x20}, {0x3635, 0x20},
	{0x3314, 0x94}, {0x330e, 0x30}, {0x3367, 0x10}, {0x3368, 0x04},
	{0x3369, 0x00}, {0x336a, 0x00}, {0x336b, 0x00}, {0x334c, 0x10},
	{0x3633, 0x44}, {0x3622, 0xf6}, {0x3301, 0x11}, {0x3630, 0xc3},
	{0x3632, 0x18}, {0x3306, 0x50}, {0x330b, 0xd0}, {0x360f, 0x05},
	{0x367a, 0x08}, {0x367b, 0x38}, {0x3671, 0xf6}, {0x3672, 0x76},
	{0x3673, 0x16}, {0x3670, 0x08}, {0x369c, 0x08}, {0x369d, 0x38},
	{0x3690, 0x64}, {0x3691, 0x63}, {0x3692, 0x64}, {0x3670, 0x0a},
	{0x367c, 0x08}, {0x367d, 0x38}, {0x3674, 0xa0}, {0x3675, 0x98},
	{0x3676, 0x6a}, {0x3364, 0x17}, {0x3301, 0x11}, {0x3393, 0x1a},
	{0x3394, 0x88}, {0x3395, 0x88}, {0x3390, 0x08}, {0x3391, 0x38},
	{0x3392, 0x38}, {0x301f, 0x01}, {0x3213, 0x01}, {0x3933, 0x0a},
	{0x3934, 0x28}, {0x3942, 0x02}, {0x3943, 0x33}, {0x3940, 0x68},
	{0x3e1b, 0x35}, {0x3038, 0x66}, {0x363c, 0x06}, {0x3253, 0x08},
	{0x391d, 0x04}, {0x391e, 0x00}, {0x3905, 0xd1}, {0x3905, 0xd1},
	{0x3909, 0x00}, {0x390a, 0x19}, {0x390d, 0x00}, {0x390e, 0x19},
	{0x390b, 0x00}, {0x390c, 0x4c}, {0x390f, 0x00}, {0x3910, 0x4c},
	{0x3920, 0x00}, {0x3921, 0x4c}, {0x3924, 0x00}, {0x3925, 0x4c},
	{0x3922, 0x00}, {0x3923, 0x19}, {0x3926, 0x00}, {0x3927, 0x19},
	{0x3900, 0x29}, {0x3937, 0x13}, {0x3906, 0x62}, {0x3935, 0x18},
	{0x3936, 0x08}, {0x391e, 0x00}, {0x3e01, 0xa8}, {0x3e02, 0x40},
	{0x3632, 0x18}, {0x3306, 0x50}, {0x330b, 0xd0}, {0x3031, 0x0c},
	{0x3037, 0x40}, {0x36e9, 0x54}, {0x36ea, 0x34}, {0x36eb, 0x07},
	{0x36ec, 0x17}, {0x36ed, 0x14}, {0x36f9, 0x54}, {0x36fa, 0x30},
	{0x36fb, 0x17}, {0x36fc, 0x10}, {0x36fd, 0x14}, {0x330b, 0x5c},
	{0x3306, 0x28}, {0x4837, 0x53}, {0x330b, 0x68}, {0x0100, 0x01},
};

static struct rts_isp_i2c_reg g_sc3235_i2c_init_regs_asic[] = {
	{0x0103, 0x01}, {0x0100, 0x00}, {0x3641, 0x0c}, {0x36e9, 0x07},
	{0x36eb, 0x05}, {0x36ec, 0x15}, {0x36ed, 0x04}, {0x36f9, 0x33},
	{0x36fb, 0x23}, {0x36fc, 0x01}, {0x36fd, 0x14}, {0x3641, 0x00},
	{0x3e09, 0x20}, {0x3637, 0x2c}, {0x3630, 0x83}, {0x3635, 0x10},
	{0x363b, 0x10}, {0x363c, 0x07}, {0x3306, 0x58}, {0x330a, 0x00},
	{0x330b, 0xd8}, {0x3638, 0x28}, {0x331c, 0x01}, {0x3304, 0x30},
	{0x331e, 0x29}, {0x3320, 0x03}, {0x3356, 0x01}, {0x57a4, 0xa0},
	{0x5781, 0x04}, {0x5782, 0x04}, {0x5783, 0x02}, {0x5784, 0x02},
	{0x5785, 0x40}, {0x5786, 0x20}, {0x5787, 0x18}, {0x5788, 0x10},
	{0x5789, 0x10}, {0x578a, 0x30}, {0x3908, 0x11}, {0x3622, 0xf6},
	{0x3e25, 0x03}, {0x3e26, 0x20}, {0x3902, 0xc5}, {0x3905, 0x99},
	{0x3314, 0x94}, {0x3347, 0x05}, {0x3301, 0x80}, {0x3630, 0xc3},
	{0x3633, 0x42}, {0x363a, 0xa8}, {0x3614, 0x80}, {0x3632, 0x18},
	{0x3631, 0x8a}, {0x3e01, 0x62}, {0x363b, 0x20}, {0x3635, 0x20},
	{0x3314, 0x94}, {0x330e, 0x30}, {0x3367, 0x10}, {0x3368, 0x04},
	{0x3369, 0x00}, {0x336a, 0x00}, {0x336b, 0x00}, {0x334c, 0x10},
	{0x3633, 0x44}, {0x3622, 0xf6}, {0x3301, 0x11}, {0x3630, 0xc3},
	{0x3632, 0x18}, {0x3306, 0x50}, {0x330b, 0xd0}, {0x360f, 0x05},
	{0x367a, 0x08}, {0x367b, 0x38}, {0x3671, 0xf6}, {0x3672, 0x76},
	{0x3673, 0x16}, {0x3670, 0x08}, {0x369c, 0x08}, {0x369d, 0x38},
	{0x3690, 0x64}, {0x3691, 0x63}, {0x3692, 0x64}, {0x3670, 0x0a},
	{0x367c, 0x08}, {0x367d, 0x38}, {0x3674, 0xc3}, {0x3675, 0x98},
	{0x3676, 0x6c}, {0x3364, 0x17}, {0x3301, 0x11}, {0x3393, 0x1a},
	{0x3394, 0x90}, {0x3395, 0x90}, {0x3390, 0x08}, {0x3391, 0x38},
	{0x3392, 0x38}, {0x301f, 0x01}, {0x3933, 0x0a}, {0x3934, 0x28},
	{0x3942, 0x02}, {0x3943, 0x33}, {0x3940, 0x68}, {0x3e1b, 0x35},
	{0x3038, 0x66}, {0x363c, 0x06}, {0x3211, 0x08}, {0x3213, 0x07},
	{0x3e01, 0xa8}, {0x3e02, 0x40}, {0x5000, 0x00}, {0x0100, 0x01},
};

static int sc3235_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x2;
	info->interface.type = RAW_SENSOR;
	if (isp_driver_is_fpga())
		info->interface.bit_depth = SNR_12BIT;
	else
		info->interface.bit_depth = SNR_10BIT;

	info->i2c.i2c_id = 0x30;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	info->size.w = 2304;
	info->size.h = 1296;
	info->crop.x = 0;
	info->crop.y = 0;
	info->crop.w = 2304;
	info->crop.h = 1296;

	i = 0;
	if (isp_driver_is_fpga())
		set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 5000);
	else
		set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 5000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_IO_POWER, PWR_1V8, 0);
	set_power_item(&up->items[i++], SNR_CORE_POWER, PWR_1V5, 1000);
	set_power_item(&up->items[i++], SNR_ANALOG_POWER, PWR_2V8, 2000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 5000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 5000);
	up->num = i;

	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&down->items[i++], SNR_IO_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_CORE_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_ANALOG_POWER, PWR_NONE, 0);
	set_power_item(&down->items[i++], SNR_HCLK, CLK_NONE, 0);
	down->num = i;

	if (isp_driver_is_fpga()) {
		if (ARRAY_SIZE(g_sc3235_fps_info_fpga) >
		    ARRAY_SIZE(info->fps.fps))
			return -RTS_ISP_ERANGE;
		for (i = 0; i < ARRAY_SIZE(g_sc3235_fps_info_fpga); i++)
			info->fps.fps[i] = g_sc3235_fps_info_fpga[i].fps;
		info->fps.num = ARRAY_SIZE(g_sc3235_fps_info_fpga);
	} else {
		if (ARRAY_SIZE(g_sc3235_fps_info_asic) >
		    ARRAY_SIZE(info->fps.fps))
			return -RTS_ISP_ERANGE;
		for (i = 0; i < ARRAY_SIZE(g_sc3235_fps_info_asic); i++)
			info->fps.fps[i] = g_sc3235_fps_info_asic[i].fps;
		info->fps.num = ARRAY_SIZE(g_sc3235_fps_info_asic);
	}

	return RTS_ISP_OK;
}

static const struct fps_info *sc3235_get_fps_info(uint16_t fps)
{
	int i;

	if (isp_driver_is_fpga()) {
		for (i = 0; i < ARRAY_SIZE(g_sc3235_fps_info_fpga); i++)
			if (fps == g_sc3235_fps_info_fpga[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc3235_fps_info_fpga))
			return NULL;

		return &g_sc3235_fps_info_fpga[i];
	} else {
		for (i = 0; i < ARRAY_SIZE(g_sc3235_fps_info_asic); i++)
			if (fps == g_sc3235_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_sc3235_fps_info_asic))
			return NULL;

		return &g_sc3235_fps_info_asic[i];
	}
}

static int sc3235_get_init_info(uint32_t isp_id, float fps,
			       struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct sc3235_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	debug("sc3235 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;  // Sensor hdr mode select by mode->hdr

	fps_info = sc3235_get_fps_info(fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	debug("fps: %u, pclk: %u, clk_div: %u, hts: %u\n",
	      fps_info->fps, fps_info->clk, fps_info->clk_div, fps_info->hts);

	if (isp_driver_is_fpga())
		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc3235_i2c_init_regs_fpga, 0);
	else
		set_init_i2c_regs(info->sensor_regs[0],
				  g_sc3235_i2c_init_regs_asic, 0);
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1350;
	info->max_vts = 65535 - info->min_vts;

	set_init_i2c(&status->regs1[0], 0x320d, (fps_info->hts) & 0xff);
	set_init_i2c(&status->regs1[1], 0x320c, (fps_info->hts) >> 8);
	set_init_i2c_regs(info->sensor_regs[1], status->regs1, 0);

	status->row_time = 1e6 * info->hts / info->pclk; /* us */
	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	if (fgain >= 15.75) {
		reg_value = 0x1f3f;
	} else {
		if (fgain >= 8)
			reg_value = (uint16_t)(fgain * 4.0f) | 0x1f00;
		else if (fgain >= 4)
			reg_value = (uint16_t)(fgain * 8.0f) | 0x0f00;
		else if (fgain >= 2)
			reg_value = (uint16_t)(fgain * 16.0f) | 0x0700;
		else
			reg_value = (uint16_t)(fgain * 32.0f) | 0x0300;
	}

	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	float gain;

	gain = ((reg_value & 0xff) / 32.0f) *
		((((reg_value >> 8) & 0x1f) >> 2) + 1);

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

static int sc3235_get_exposure_gain_info(uint32_t isp_id,
					struct rts_isp_exp_gain *exp_gain,
					struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t total_line;
	uint16_t gain_reg;
	float exp_reg_value_float;
	uint32_t exp_reg_value;
	struct sc3235_status *status;
	struct rts_isp_sync_reg *reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain *
				       exp_gain->digital_gain);
	exp_reg_value_float =
		2.0 * exp_gain->exposure / status->row_time + 0.5f;
	exp_reg_value =
		clip_d_word(exp_reg_value_float, 0,
			    2 * (status->min_vts + exp_gain->extra_dummy));
	exp_reg_value = exp_reg_value << 4;

	reg = regs->reg;

	i = 0;

	if (abs(status->last_exposure - exp_gain->exposure) > 0.0001f) {
		total_line = status->min_vts + exp_gain->extra_dummy;
		//total length
		set_sync_i2c(&reg[i++], 0x320e, (total_line & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x320f, (total_line & 0xff));

		//set exposure time
		set_sync_i2c(&reg[i++], 0x3e00,
			     (exp_reg_value & 0xff0000) >> 16);
		set_sync_i2c(&reg[i++], 0x3e01, (exp_reg_value & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3e02, exp_reg_value & 0xff);

		//finegain, corsegain at 0x3e09[6:0]
		set_sync_i2c(&reg[i++], 0x3e08, (gain_reg & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3e09, (gain_reg & 0xff));

		status->last_exposure = exp_gain->exposure;
	} else {
		total_line = status->min_vts + exp_gain->extra_dummy;
		//total length
		set_sync_i2c(&reg[i++], 0x320e, (total_line & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x320f, (total_line & 0xff));

		set_sync_i2c(&reg[i++], 0x3e08, (gain_reg & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x3e09, (gain_reg & 0xff));
	}

	if (isp_driver_is_fpga()) {
		if (exp_gain->analog_gain < 2)
			set_sync_i2c(&reg[i++], 0x3632, 0x18);
		else if (exp_gain->analog_gain < 8)
			set_sync_i2c(&reg[i++], 0x3632, 0x58);
		else
			set_sync_i2c(&reg[i++], 0x3632, 0xd8);
	} else {
		set_sync_i2c(&reg[i++], 0x3812, 0x0); //group hold
		if (exp_gain->analog_gain < 2) {
			set_sync_i2c(&reg[i++], 0x3632, 0x18);
			set_sync_i2c(&reg[i++], 0x3306, 0x50);
			set_sync_i2c(&reg[i++], 0x330b, 0xd0);
		} else if (exp_gain->analog_gain < 8) {
			set_sync_i2c(&reg[i++], 0x3632, 0x58);
			set_sync_i2c(&reg[i++], 0x3306, 0x58);
			set_sync_i2c(&reg[i++], 0x330b, 0xd8);
		} else {
			set_sync_i2c(&reg[i++], 0x3632, 0xd8);
			set_sync_i2c(&reg[i++], 0x3306, 0x5c);
			set_sync_i2c(&reg[i++], 0x330b, 0xdb);
		}
		set_sync_i2c(&reg[i++], 0x3812, 0x30); //group enable
	}

	regs->num = i;

	exp_gain->analog_gain = get_sensor_real_gain(gain_reg);
	exp_gain->digital_gain = 1.0f;

	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops sc3235_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "sc3235",
	.get_info = sc3235_get_info,
	.get_init_info = sc3235_get_init_info,
	.get_exposure_gain_info = sc3235_get_exposure_gain_info,
	.get_patch_ops = sc3235_get_patch_ops,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &sc3235_ops;
}

#endif
