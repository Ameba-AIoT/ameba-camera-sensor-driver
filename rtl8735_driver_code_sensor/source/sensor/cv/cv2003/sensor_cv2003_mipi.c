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

#define ORIENTATION 1	//0=default, 1=rotate180

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct cv2003_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct cv2003_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct cv2003_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_cv2003_fps_info_asic[] = {
	{30.0f, 2560, 86400000},
};

static struct rts_isp_i2c_reg g_cv2003_i2c_init_regs_asic[] = {
#if 0
	//cv2003_mipi_2lane_1928x1088_30fps.ini
	{0x3020, 0x60},
	{0x3021, 0x09},
	{0x3022, 0x00},
	{0x3024, 0x70},
	{0x3025, 0x02},
	{0x3029, 0x00},
	{0x302a, 0x00},
	{0x3300, 0x01},
	{0x3401, 0x01},
	{0x3422, 0xBF},
	{0x3460, 0x03},
	{0x3440, 0x03},
	{0x3442, 0x00},
	{0x3806, 0x01},
	{0x3908, 0x4b},
	{0x3909, 0x00},
	{0x3158, 0x01},
	{0x3159, 0x01},
	{0x315a, 0x01},
	{0x315b, 0x01},
	{0x3148, 0x64},
	{0x3670, 0x00},
	{0x3679, 0x02},
	{0x35b3, 0x15},
	{0x320e, 0x02},
	{0x3804, 0x10},
	{0x35a1, 0x06},
	{0x35a8, 0x06},
	{0x35a9, 0x06},
	{0x35aa, 0x06},
	{0x35ab, 0x06},
	{0x35ac, 0x06},
	{0x35ad, 0x06},
	{0x35ae, 0x07},
	{0x35af, 0x07},
	{0x333b, 0x01},
	{0x3339, 0x00},
	{0x3031, 0x00},
	{0x3118, 0x01},
	{0x3119, 0x06},
	{0x3330, 0x00},
	{0x3030, 0x01},
	{0x3020, 0x30},
	{0x3021, 0x09},//VTS = 0x930/2 = 1176
	{0x3024, 0x6C},
	{0x3025, 0x02},//HTS = 0x26C*4 = 2480
	{0x3038, 0x00},	//0x04
	{0x3039, 0x00},
	{0x303a, 0x88},	//0x80
	{0x303b, 0x07},
	{0x3034, 0x00},	//0x04
	{0x3035, 0x00},
	{0x3036, 0x40},	//0x38
	{0x3037, 0x04},
	{0x3908, 0x49},
	{0x390a, 0x04},
	{0x3141, 0x01},
	{0x332d, 0x40},
	{0x3000, 0x00}
#else
	{0x3020, 0xCA},
    {0x3021, 0x08},
    {0x3022, 0x00},
    {0x3024, 0x80},
    {0x3025, 0x02},
    {0x3029, 0x00},
    {0x302a, 0x00},
    {0x3300, 0x01},
    {0x3401, 0x01},
    {0x3422, 0xBF},
    {0x3460, 0x03},
    {0x3440, 0x00},
    {0x3442, 0x00},
    {0x3806, 0x01},
    {0x3908, 0x49},
    {0x3909, 0x00},
    {0x3158, 0x01},
    {0x3159, 0x01},
    {0x315a, 0x01},
    {0x315b, 0x01},
    {0x3148, 0x64},
    {0x3670, 0x00},
    {0x3679, 0x02},
    {0x35b3, 0x15},
    {0x320e, 0x02},
    {0x3804, 0x10},
    {0x35a1, 0x06},
    {0x35a8, 0x06},
    {0x35a9, 0x06},
    {0x35aa, 0x06},
    {0x35ab, 0x06},
    {0x35ac, 0x06},
    {0x35ad, 0x06},
    {0x35ae, 0x07},
    {0x35af, 0x07},
    {0x333b, 0x01},
    {0x3339, 0x00},
    {0x3031, 0x00},
    {0x3118, 0x01},
    {0x3119, 0x06},
    {0x3330, 0x00},
    {0x3030, 0x01},
    {0x3038, 0x00},
    {0x3039, 0x00},
    {0x303a, 0x88},
    {0x303b, 0x07},
    {0x3034, 0x00},
    {0x3035, 0x00},
    {0x3036, 0x40},
    {0x3037, 0x04},
    {0x390a, 0x04},
    {0x3141, 0x01},
    {0x332d, 0x40},
    {0x3000, 0x00},
#endif
};
static struct cv2003_gain_config g_cv2003_gain_config[] = {
//   0x3E09 Gain(16=1x)
	{0x00,  16},
	{0x80,  32},
	{0xC0,  64},
	{0xE0,  128},
	{0xF0,  256},
	{0xF8,  512},
};
static int cv2003_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_cv2003_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x35;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	//set_power_item(&up->items[i++], SNR_PWRCTRL_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 6000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 0);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 5000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *cv2003_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_cv2003_fps_info_asic); i++)
		if (fps == g_cv2003_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_cv2003_fps_info_asic))
		return NULL;
	return &g_cv2003_fps_info_asic[i];

}

static int cv2003_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct cv2003_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("cv2003 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = cv2003_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	set_init_i2c_regs(info->sensor_regs[0], g_cv2003_i2c_init_regs_asic, 0);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 1;
	info->start.y = 0;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1125;
	//info->max_vts = 6750;
	info->max_vts = info->min_vts * 15;
	
	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int cv2003_start(uint32_t isp_id)
{
	struct cv2003_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int cv2003_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct cv2003_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 0) * status->exp_step;
		//printf("vts:%d  exp_step:%f.\r\n", vts, status->exp_step);
	} else {
		//uint32_t tmp1;
		//uint32_t tmp2;
		//uint16_t max_exp_line = 2 * (2 * vts - status->max_short_exp - 5);
		//
		//tmp1 = 2 * (status->max_short_exp - 4);
		//tmp2 = (uint32_t)(max_exp_line / (ratio[0] + 1));
		//tmp1 = tmp1 < tmp2 ? tmp1 : tmp2;
		//max_exposure[1] = tmp1 * status->exp_step;
		//min_exposure[1] = 5 * status->exp_step;
		//max_exposure[0] = max_exposure[1] * ratio[0];
		//min_exposure[0] = min_exposure[1] * ratio[0];
	}

	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct cv2003_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	
	if (gain >= 512) {	//32x
		gain = 512;
		status->num = 5;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_cv2003_gain_config) - 1; i++) {
			if (gain >= g_cv2003_gain_config[i].gainValue &&
			    gain < g_cv2003_gain_config[i + 1].gainValue) {
				gain = g_cv2003_gain_config[i].gainValue;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 16.0f;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}
static int cv2003_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct cv2003_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}
static int cv2003_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int cv2003_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct cv2003_status *status;
	struct rts_isp_sync_reg *reg;
	uint32_t exposure_rows;
	uint32_t exposure_rows_reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	vts = vts << 1;
	
	i = 0;
	
	set_sync_i2c(&reg[i++], 0x3007, 0x01);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = clip_d_word(exposure_rows, 6, vts - 2);
		exposure_rows = vts - exposure_rows;
		set_sync_i2c(&reg[i++], 0x03049, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x3048, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x3154, g_cv2003_gain_config[status->num].regValue);
	set_sync_i2c(&reg[i++], 0x3021, vts >> 8);
	set_sync_i2c(&reg[i++], 0x3020, vts & 0xff);
	set_sync_i2c(&reg[i++], 0x3007, 0x00);
	
	regs->num = i;
	return RTS_ISP_OK;
}

static int cv2003_set_mirror_flip(uint32_t isp_id,
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
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int cv2003_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x3011;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x3138;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	printf("chip id = 0x%x\r\n", id);
	
	if (id == 0x2003)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static const struct rts_isp_sensor_ops cv2003_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "cv2003",

	.get_info = cv2003_get_info,
	.get_init_info = cv2003_get_init_info,
	.start = cv2003_start,
	//.get_exposure_range = cv2003_get_exposure_range,
	.get_tuned_again = cv2003_get_tuned_again,
	.get_tuned_dgain = cv2003_get_tuned_dgain,
	.get_exposure_gain_info = cv2003_get_exposure_gain_info,
	.set_mirror_flip = cv2003_set_mirror_flip,
	.check = cv2003_check,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &cv2003_ops;
}