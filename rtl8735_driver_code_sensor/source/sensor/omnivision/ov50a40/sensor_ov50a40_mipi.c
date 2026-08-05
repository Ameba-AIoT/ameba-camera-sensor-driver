/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"
#include "ov50a40_init_registers_backup.h"

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

#define FOV_MODE	0	//0 = full view, 1 = crop mode

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ov50a40_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};


struct ov50a40_gain_config {
	uint8_t reg_b4;
	uint8_t reg_b3;
	uint8_t reg_b8;
	uint8_t reg_b9;
	uint16_t value;
};

static struct ov50a40_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

//TODO: Verify Data
static const struct fps_info g_ov50a40_fps_info_asic[] = {
#if FOV_MODE == 0
	{30.0f, 3308, 160000000},
#else
	{30.0f, 3198, 160000000},
#endif
};

static int ov50a40_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].fps = g_ov50a40_fps_info_asic[0].fps;
	info->modes.mode[0].hdr = LINEAR_MODE;
	info->modes.mode[0].size.w = 2048;
	info->modes.mode[0].size.h = 1536;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x36;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 10000);
	set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 100);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 3000);

	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 10000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100000);

	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 10000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 100000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 10000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *ov50a40_get_fps_info(uint16_t fps)
{
	int i;

		for (i = 0; i < ARRAY_SIZE(g_ov50a40_fps_info_asic); i++)
			if (fps == g_ov50a40_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_ov50a40_fps_info_asic))
			return NULL;
		return &g_ov50a40_fps_info_asic[i];

}

static int ov50a40_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ov50a40_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = ov50a40_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;
		

	set_init_i2c_regs(info->sensor_regs[0], g_ov50a40_i2c_init_regs_asic, 1000);
#if FOV_MODE == 0
	set_init_i2c_regs(info->sensor_regs[1], g_ov50a40_i2c_init_regs_asic_fullmode, 1000);
#else
	set_init_i2c_regs(info->sensor_regs[1], g_ov50a40_i2c_init_regs_asic_crop_mode_0801, 1000);
#endif
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2052;
	info->size.h = 1540;
#if FOV_MODE == 0
	info->start.x = 0;	//2	//0
	info->start.y = 1;	//2	//1
#else
	//info->start.x = 2;	//2	//0
	//info->start.y = 2;	//2	//1
	info->start.x = 1;	//2	//0
	info->start.y = 3;	//2	//1
#endif

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
#if FOV_MODE == 0
	info->min_vts = status->min_vts = 1612;
	info->max_vts = 8060;
#else
	info->min_vts = status->min_vts = 1668;
	info->max_vts = 8340;
#endif

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	//info->exposure_step = status->exp_step;

	return RTS_ISP_OK;
}

static int ov50a40_start(uint32_t isp_id)
{
	struct ov50a40_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain, struct ov50a40_status *status)
{
	uint16_t gain = fgain * 256;
	gain = gain & 0xFFF8;
	status->num = gain;
	return gain;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 256.0f;
}

static int ov50a40_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ov50a40_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int ov50a40_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int ov50a40_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ov50a40_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts + 32;
	reg = regs->reg;

	i = 0;
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x3501, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x3502, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}

	set_sync_i2c(&reg[i++], 0x3508, status->num >> 8);
	set_sync_i2c(&reg[i++], 0x3509, status->num & 0xff);
	set_sync_i2c(&reg[i++], 0x380E, vts >> 8);
	set_sync_i2c(&reg[i++], 0x380F, vts & 0xff);
	regs->num = i;
	
	return RTS_ISP_OK;
}
static int ov50a40_set_mirror_flip(uint32_t isp_id,
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
	/*
	switch(bySnrImgDir)//
	{
		case 0: //normal
		default:
			set_sync_i2c(&reg[i++], 0x3820, 0x43);
			set_sync_i2c(&reg[i++], 0x3821, 0x04);
			set_sync_i2c(&reg[i++], 0x3811, 0x01);
			set_sync_i2c(&reg[i++], 0x3813, 0x02);
			set_sync_i2c(&reg[i++], 0x45C0, 0x0E);
			set_sync_i2c(&reg[i++], 0x45C3, 0x94);
			set_sync_i2c(&reg[i++], 0x45C4, 0x10);
		break;
		case 1: 	// Mirror
			set_sync_i2c(&reg[i++], 0x3820, 0x43);
			set_sync_i2c(&reg[i++], 0x3821, 0x00);
			set_sync_i2c(&reg[i++], 0x3811, 0x02);
			set_sync_i2c(&reg[i++], 0x3813, 0x02);
			set_sync_i2c(&reg[i++], 0x45C0, 0x0E);
			set_sync_i2c(&reg[i++], 0x45C3, 0x14);
			set_sync_i2c(&reg[i++], 0x45C4, 0x10);
		break;
		case 2: 		// VFlip
			set_sync_i2c(&reg[i++], 0x3820, 0x47);
			set_sync_i2c(&reg[i++], 0x3821, 0x04);
			set_sync_i2c(&reg[i++], 0x3811, 0x01);
			set_sync_i2c(&reg[i++], 0x3813, 0x03);
			set_sync_i2c(&reg[i++], 0x45C0, 0x8E);
			set_sync_i2c(&reg[i++], 0x45C3, 0x14);
			set_sync_i2c(&reg[i++], 0x45C4, 0x13);
		break;
		case 3: 	// Rotate
			set_sync_i2c(&reg[i++], 0x3820, 0x47);
			set_sync_i2c(&reg[i++], 0x3821, 0x00);
			set_sync_i2c(&reg[i++], 0x3811, 0x02);
			set_sync_i2c(&reg[i++], 0x3813, 0x03);
			set_sync_i2c(&reg[i++], 0x45C0, 0x8E);
			set_sync_i2c(&reg[i++], 0x45C3, 0x14);
			set_sync_i2c(&reg[i++], 0x45C4, 0x13);
		break;
	}
	*/
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ov50a40_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();


	for(int i=0x7290; i<=0x805f; ++i) {
		reg.addr = i;
		reg.data = 0x80;
		rts_isp_write_sensor_reg(isp_id, &reg);
	}

	reg.addr = 0x300A;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x300B;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	printf("[DRIVER] Sensor ID = 0x%X, expected 0x5650", id);

	if (id == 0x5650)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops ov50a40_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov50a40",

	.get_info = ov50a40_get_info,
	.get_init_info = ov50a40_get_init_info,
	.start = ov50a40_start,
	.get_tuned_again = ov50a40_get_tuned_again,
	.get_tuned_dgain = ov50a40_get_tuned_dgain,
	.get_exposure_gain_info = ov50a40_get_exposure_gain_info,
	.set_mirror_flip = ov50a40_set_mirror_flip,
	.check = ov50a40_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ov50a40_ops;
}
