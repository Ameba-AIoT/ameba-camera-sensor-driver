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

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct ps5258_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

static struct ps5258_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_ps5258_fps_info_asic[] = {
	{30.0f, 2200, 74250000},
};

static struct rts_isp_i2c_reg g_ps5258_i2c_init_regs_asic[] = {
	{0x010B, 0x07},	//Cmd_Sw_TriState[0]=1
	{0x0178, 0xB0},	//B07A: Version
	{0x0179, 0x7A},	//B07A: Version
	{0x020A, 0x35},	//T_ODACMODE=1, B04A - improve streaking, B07A - Reverse T_IBDN[1:0] setting
	{0x020D, 0x01},	//T_GDACMODE=1, B04A - improve streaking
	{0x022D, 0x01},	//T_spll_enh[0]=1
	{0x021C, 0x00},	//T_FAE_CLK_SEL[0]=0
	{0x023C, 0x37},	//T_clamp_offset_lvl[2:0]=3, B05A - improve streaking
	{0x0240, 0x15},	//T_compf_fast[2:0]=5, B03A - improve RTS noise & LowVol preformance
	{0x0254, 0x61},	//T_pll_enh[0]=1
	{0x0659, 0x5E},	//R_comp_rst_r3[7:0]=94 - improve left/right display uniformity
	{0x0684, 0x00},	//R_cout_reset_enl_f1=2, B02A - improve straight line
	{0x0685, 0x02},	//R_cout_reset_enl_f1=2, B02A - improve straight line
	{0x069A, 0x00},	//Cmd_INTREFHD_enH=0, B03A
	{0x06AC, 0x04},	//Cmd_vbt_isel_R_G3[6:0]=4, B04A - improve streaking
	{0x0B02, 0x02},	//Cmd_RClkDly_Sel[3:0]=2, B05A
	{0x0B0C, 0x00},	//Cmd_MIPI_Clk_Gated[0]=0
	{0x14B0, 0x01},	//R_MIPI_line_num_en=0, R_MIPI_frm_num_en=0, R_MIPI_skip_line_sp=1,  B04A - work-around MIPI display
	{0x140F, 0x01},	//R_CSI2_enable=1
	{0x0111, 0x01},	//UpdateFlag
	{0x010F, 0x01},	//Sensor_EnH=1
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x48	//0x90(I2C_ID_SEL=low, Default)
#define SLAVE_ADDR_1 0x4C	//0x98(I2C_ID_SEL=high)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int ps5258_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info) {
		return -RTS_ISP_EINVAL;
	}

	info->modes.mode[0].fps = g_ps5258_fps_info_asic[0].fps;
	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	info->modes.num = 1;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_27M, 5000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 6000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 1000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *ps5258_get_fps_info(float fps)
{
	int i;


		for (i = 0; i < ARRAY_SIZE(g_ps5258_fps_info_asic); i++)
			if (fps == g_ps5258_fps_info_asic[i].fps)
				break;
		if (i == ARRAY_SIZE(g_ps5258_fps_info_asic))
			return NULL;
		return &g_ps5258_fps_info_asic[i];

}

static int ps5258_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct ps5258_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = ps5258_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0], g_ps5258_i2c_init_regs_asic, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x4;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 1928;
	info->size.h = 1088;
	info->start.x = 0;
	info->start.y = 1;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1125;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */

	return RTS_ISP_OK;
}


static int ps5258_start(uint32_t isp_id)
{
	struct ps5258_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}



static uint16_t get_sensor_gain_reg(float fAGain, struct ps5258_status *status)
{
	unsigned short wAgainReg;
	if(fAGain>=1.0 && fAGain<2.0){
		wAgainReg = (unsigned short)(16.0f*(fAGain-1.0));
	}
	else if(fAGain>=2.0 && fAGain<4.0){
		wAgainReg = (unsigned short)(8.0f*(fAGain-2.0) + 16.0);
	}
	else if(fAGain>=4.0 && fAGain<8.0){
		wAgainReg = (unsigned short)(4.0f*(fAGain-4.0) +32.0);
	}
	else if(fAGain>=8.0 && fAGain<16.0){
		wAgainReg = (unsigned short)(2.0f*(fAGain-8.0) +48.0);
	}
	else if(fAGain>=16.0 && fAGain<=32.0){
		wAgainReg = (unsigned short)((fAGain-16.0) +64.0);
	}
	status->num = wAgainReg;

	return (wAgainReg);
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	float fAgainReg;
	float ftemp = wAGain;
	if(wAGain>=0 && wAGain<16){
		fAgainReg = (float)(ftemp/16.0 +1);
	}
	else if(wAGain>=16 && wAGain<32){
		fAgainReg = (float)(ftemp/8.0);
	}
	else if(wAGain>=32 && wAGain<48){
		fAgainReg = (float)(ftemp/4.0 - 4);
	}
	else if(wAGain>=48 && wAGain<64){
		fAgainReg = (float)(ftemp/2.0 - 16);
	}
	else if(wAGain>=64 && wAGain<=80){
		fAgainReg = (float)(ftemp - 48);
	}

	return (fAgainReg);
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int ps5258_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct ps5258_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	return RTS_ISP_OK;
}

static int ps5258_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;
	return RTS_ISP_OK;
}

static int ps5258_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint16_t gain_reg;
	uint32_t vts;
	struct ps5258_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;  //exp_gain->extra_dummy + status->min_vts;
	
	/*
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] *
				       exp_gain->digital_gain[0], status);
	*/
	reg = regs->reg;
	
	i = 0;
	set_sync_i2c(&reg[i++], 0x0116, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0117, vts & 0xff);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = clip_d_word(exposure_rows, 2, vts - 1);
		exposure_rows = vts - exposure_rows;
		set_sync_i2c(&reg[i++], 0x0118, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0119, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	//set_sync_i2c(&reg[i++], 0x012A, 0);
	set_sync_i2c(&reg[i++], 0x012B, status->num);
	set_sync_i2c(&reg[i++], 0x0111, 1);
	regs->num = i;

	return RTS_ISP_OK;
}

static int ps5258_set_mirror_flip(uint32_t isp_id,
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
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int ps5258_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();

	reg.addr = 0x0100;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x0101;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

	if (id == 0x5258)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int ps5258_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops ps5258_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ps5258",

	.get_info = ps5258_get_info,
	.get_init_info = ps5258_get_init_info,
	.start = ps5258_start,
	.get_exposure_gain_info = ps5258_get_exposure_gain_info,
	.get_tuned_again = ps5258_get_tuned_again,
	.get_tuned_dgain = ps5258_get_tuned_dgain,
	.set_mirror_flip = ps5258_set_mirror_flip,
	.check = ps5258_check,
	.get_slave_addr_num = ps5258_get_slave_addr_num,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &ps5258_ops;
}


