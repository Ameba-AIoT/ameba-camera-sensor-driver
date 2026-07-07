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
#define ORIENTATION 0	//0=default, 1=rotate180
#define PROJECT_BIRNNO	0

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ps5262_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

static struct ps5262_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ps5262_fps_info_asic[] = {
	{30.0f, 2370, 80000000},
};

static struct rts_isp_i2c_reg g_ps5262_i2c_init_regs_asic[] = {
	//PS319_5262_1928x1088_27M_30fps_Pxclk74p25M_MIPI_2Lane_RAW10_400Mbps_NonImgSyn_20210429_B04A_reduce.asc
	{0x56FF, 0x00}, //Zako, 2025.07.28 clear MD interrupt pin
	{0x410B, 0x83}, //Cmd_Sw_TriState=1
	{0x0114, 0x08}, //Cmd_LineTime[12:0]=2200
	{0x0115, 0x98}, //Cmd_LineTime[12:0]=2200
	{0x0162, 0x02}, //Cmd_Np[3:0]=2
	{0x4178, 0xB0}, //B04A: Version
	{0x4179, 0x4A}, //B04A: Version
	{0x0226, 0x16}, //T_spll_predivider=22
	{0x0227, 0x1F}, //T_spll_postdivider=31
	{0x0225, 0x11}, //T_spll_enh[0]=1
	{0x0242, 0x11}, //T_MIPI_EnL[0]=0, T_MIPI_sel[0]=1
	{0x0246, 0x19}, //T_pll_predivider=25
	{0x0247, 0x26}, //T_pll_postdivider=38
	{0x0248, 0x61}, //T_pll_enh[0]=1
	{0x0249, 0x11}, //T_pll_div2_EnH=1
	{0x4212, 0xC0}, //T_FAE_CLK_SEL[0]=0
	{0x0654, 0x01}, //R_comp_rst_r1=500
	{0x0655, 0xF5}, //R_comp_rst_r1=500
	{0x0657, 0x19}, //R_comp_rst_r2=281
	{0x0659, 0x90}, //R_comp_rst_r3=400
	{0x065B, 0x2B}, //R_comp_rst_r4=1323
	{0x06A3, 0x40}, //Cmd_RDAC_G2=54->64
	{0x06AC, 0x08}, //Cmd_vbt_isel_R_G3=6->8
	{0x0906, 0x08}, //R_DLNU_ABC_Modify1=520
	{0x0908, 0x1C}, //R_DLNU_FDC_Modify1=540
	{0x090F, 0x08}, //R_DLNU_ABC_Modify2=520
	{0x0911, 0x1C}, //R_DLNU_FDC_Modify2=540
	{0x0919, 0x03}, //R_DLNU_Scale_1=3
	{0x091A, 0x03}, //R_DLNU_Scale_2=3
	{0x0B0C, 0x00}, //Cmd_MIPI_Clk_Gated[0]=0
	{0x1415, 0x05}, //R_LPX_prd[7:0]=5
	{0x1417, 0x03}, //R_HsPrep_prd[7:0]=3
	{0x1418, 0x03}, //R_HsEoT_prd[7:0]=3
	{0x145B, 0x10}, //R_MIPI_frm_rst_en=1
	{0x140F, 0x01}, //R_CSI2_enable=1
	{0x0111, 0x01}, //UpdateFlag[0]=1
	{0x010F, 0x01}, //Sensor_EnH[0]=1
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x48	//0x90(I2C_ID_SEL=low, Default)
#define SLAVE_ADDR_1 0x4C	//0x98(I2C_ID_SEL=high)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int ps5262_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.mode[0].fps = g_ps5262_fps_info_asic[0].fps;
	info->modes.num = 1;
	
	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
#if(!PROJECT_BIRNNO)
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 0);
#endif
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 50000);
	up->num = i;
	i = 0;
	//set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 5000);
	//set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 10000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	down->num = i;
		
	return RTS_ISP_OK;
}

static const struct fps_info *ps5262_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_ps5262_fps_info_asic); i++)
		if (fps == (int)g_ps5262_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_ps5262_fps_info_asic))
		return NULL;
	return &g_ps5262_fps_info_asic[i];

}

static int ps5262_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *sfps_info;
	struct ps5262_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	sfps_info = ps5262_get_fps_info(mode->fps);
	if (!sfps_info)
		return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0], g_ps5262_i2c_init_regs_asic, 5);
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;
	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 0;
	info->start.y = 1;
	info->hts = sfps_info->hts;
	info->pclk = sfps_info->clk;
	info->min_vts = status->min_vts = 1125;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int ps5262_start(uint32_t isp_id)
{
	struct ps5262_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static int ps5262_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct ps5262_status *status;

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

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

// ps5262 Gain Table for 1.0x ~ 32x (U.9)
const unsigned int ps5262_gain_table[81] = {
	 256, 272, 288, 304, 320, 336, 352, 368, 384, 400, 416, 432, 448, 464, 480, 496,
	 512, 544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 960, 992,
	1024,1088,1152,1216,1280,1344,1408,1472,1536,1600,1664,1728,1792,1856,1920,1984,
	2048,2176,2304,2432,2560,2688,2816,2944,3072,3200,3328,3456,3584,3712,3840,3968,
	4096,4352,4608,4864,5120,5376,5632,5888,6144,6400,6656,6912,7168,7424,7680,7936,
	8192 
};

static uint16_t get_sensor_gain_reg(float fAGain, struct ps5262_status *status)
{
	int i;
	uint16_t gain = fAGain * 256;
	for (i = 0; i < (81 - 1); i++) {
		if (gain >= ps5262_gain_table[i] &&
		    gain < ps5262_gain_table[i+1]) {
			gain = ps5262_gain_table[i];
			status->num = i;
			break;
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 256.0f;
}

static int ps5262_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ps5262_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int ps5262_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

uint32_t bVts = 0;

static int ps5262_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct ps5262_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;

	i = 0;
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = clip_d_word(exposure_rows, 1, vts - 2);
		if(bVts != vts)
		{
			set_sync_i2c(&reg[i++], 0x0116, vts >> 8);
			set_sync_i2c(&reg[i++], 0x0117, vts & 0xff);
			bVts = vts;
		}
		set_sync_i2c(&reg[i++], 0x0118, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0119, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x012B, status->num);
	set_sync_i2c(&reg[i++], 0x0111, 0x01);
	regs->num = i;
	return RTS_ISP_OK;
}

static int ps5262_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	/*
	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)//
	{
	#if (ORIENTATION == 0)
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x0140, 0x00);
            set_sync_i2c(&reg[i++], 0x0141, 0x00);
            set_sync_i2c(&reg[i++], 0x0149, 0x00);
            set_sync_i2c(&reg[i++], 0x014A, 0x02);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x0140, 0x01);
            set_sync_i2c(&reg[i++], 0x0141, 0x00);
            set_sync_i2c(&reg[i++], 0x0149, 0x00);
            set_sync_i2c(&reg[i++], 0x014A, 0x02);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x0140, 0x00);
            set_sync_i2c(&reg[i++], 0x0141, 0x01);
            set_sync_i2c(&reg[i++], 0x0149, 0x04);
            set_sync_i2c(&reg[i++], 0x014A, 0x44);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x0140, 0x01);
            set_sync_i2c(&reg[i++], 0x0141, 0x01);
            set_sync_i2c(&reg[i++], 0x0149, 0x04);
            set_sync_i2c(&reg[i++], 0x014A, 0x44);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
	#else
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x0140, 0x01);
            set_sync_i2c(&reg[i++], 0x0141, 0x01);
            set_sync_i2c(&reg[i++], 0x0149, 0x04);
            set_sync_i2c(&reg[i++], 0x014A, 0x44);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 2: 	// Mirror
           	set_sync_i2c(&reg[i++], 0x0140, 0x00);
            set_sync_i2c(&reg[i++], 0x0141, 0x01);
            set_sync_i2c(&reg[i++], 0x0149, 0x04);
            set_sync_i2c(&reg[i++], 0x014A, 0x44);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x0140, 0x01);
            set_sync_i2c(&reg[i++], 0x0141, 0x00);
            set_sync_i2c(&reg[i++], 0x0149, 0x00);
            set_sync_i2c(&reg[i++], 0x014A, 0x02);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
		case 3: 	// Rotate            
            set_sync_i2c(&reg[i++], 0x0140, 0x00);
            set_sync_i2c(&reg[i++], 0x0141, 0x00);
            set_sync_i2c(&reg[i++], 0x0149, 0x00);
            set_sync_i2c(&reg[i++], 0x014A, 0x02);
            set_sync_i2c(&reg[i++], 0x0111, 0x01);
			break;
	#endif
	}
	*/
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ps5262_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();

	reg.addr = 0x4100;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id = reg.data << 8;

	reg.addr = 0x4101;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret)
		return ret;
	id |= reg.data;
	
	if (id == 0x5262)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int ps5262_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops ps5262_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ps5262",

	.get_info = ps5262_get_info,
	.get_init_info = ps5262_get_init_info,
	.start = ps5262_start,
	.get_exposure_range = ps5262_get_exposure_range,
	.get_tuned_again = ps5262_get_tuned_again,
	.get_tuned_dgain = ps5262_get_tuned_dgain,
	.get_exposure_gain_info = ps5262_get_exposure_gain_info,
	.set_mirror_flip = ps5262_set_mirror_flip,
	.check = ps5262_check,
	.get_slave_addr_num = ps5262_get_slave_addr_num,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ps5262_ops;
}

