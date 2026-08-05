/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct k06a_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure[2];
	int num;
	struct rts_isp_i2c_reg regs1[3];
};


static struct k06a_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_k06a_fps_info_asic[] = {
	{30.0f, 3840, 172800000},
};

//mclk=27mhz,pclk=74.25mhz
//pixel_line_total=2200,line_frame_total=1125
//row_time=29.629us,frame_rate=30fps
//Mipi_clk=594 Mbps

static struct rts_isp_i2c_reg g_k06a_i2c_init_regs_asic[] = {
	/****system****/
	{0x12,0x70},
	{0x48,0x86},
	{0x48,0x06},
	{0x0E,0x11},
	{0x0F,0x04},
	{0x10,0x48},
	{0x11,0x80},
	{0x46,0x08},
	{0x7F,0x5E},
	{0x0D,0xA0},
	{0x57,0x67},
	{0x58,0x1F},
	{0x5F,0x41},
	{0x60,0x20},
	{0x20,0xC0},
	{0x21,0x03},
	{0x22,0xDC},
	{0x23,0x05},
	{0x24,0x82},
	{0x25,0xA8},
	{0x26,0x52},
	{0x27,0xBB},
	{0x28,0x15},
	{0x29,0x03},
	{0x2A,0xB6},
	{0x2B,0x13},
	{0x2C,0x00},
	{0x2D,0x00},
	{0x2E,0x6F},
	{0x2F,0x04},
	{0x41,0x06},
	{0x42,0x05},
	{0x47,0x46},
	{0x76,0x8A},
	{0x77,0x0C},
	{0x80,0x01},
	{0xAF,0x12},
	{0xAA,0x84},
	{0x1D,0x00},
	{0x1E,0x04},
	{0x6C,0x40},
	{0x9E,0x38},
	{0x0C,0x00},
	{0x6E,0x2C},
	{0x70,0xF9},
	{0x71,0xDD},
	{0x72,0xD5},
	{0x73,0x5A},
	{0x74,0x02},
	{0x78,0x1C},
	{0x89,0x01},
	{0x6B,0x20},
	{0x86,0x40},
	{0x6F,0x00},
	{0x30,0x8D},
	{0x31,0x08},
	{0x32,0x20},
	{0x33,0x5C},
	{0x34,0x30},
	{0x35,0x30},
	{0x3A,0xB9},
	{0x56,0x92},
	{0x59,0x40},
	{0x5A,0x01},
	{0x61,0x00},
	{0x64,0xC0},
	{0x85,0x44},
	{0x8A,0x00},
	{0x91,0x58},
	{0x94,0xA0},
	{0x9B,0x8F},
	{0xA6,0x02},
	{0xA7,0xA0},
	{0xA9,0x48},
	{0x45,0x09},
	{0x5B,0xA5},
	{0x5C,0x8C},
	{0x5D,0x97},
	{0x5E,0x48},
	{0x65,0x32},
	{0x66,0x80},
	{0x67,0x44},
	{0x68,0x00},
	{0x69,0x74},
	{0x6A,0x2B},
	{0x7A,0x82},
	{0x8D,0x6F},
	{0x8F,0x90},
	{0xA4,0xC7},
	{0xA5,0xAF},
	{0xB7,0x61},
	{0x97,0x20},
	{0x13,0x81},
	{0x96,0x84},
	{0x4A,0x01},
	{0x7E,0x4C},
	{0x8E,0x80},
	{0x50,0x02},
	{0x93,0x00},
	{0xB5,0x4C},
	{0xB1,0x00},
	{0xA1,0x0F},
	{0xA3,0x40},
	{0x49,0x40},  //blc tgt = 10b 64
	{0x8C,0xFF},
	{0x8B,0x01},
	{0xBC,0x11},
	{0x82,0x00},
	{0x9F,0x50},
	{0x19,0x20},
	{0x1B,0x4F},
	{0x12,0x30},
	{0x48,0x86},
	{0x48,0x06},
	{0x00,0x10},
};

#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x40	//0x6e(default, D[0]=D[1]=0)
#define SLAVE_ADDR_1 0x46	//0x8c(D[0]=D[1]=1)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;

static int k06a_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;
	info->modes.mode[0].size.w = 2560;
	info->modes.mode[0].size.h = 1440;
	info->modes.mode[0].fps = g_k06a_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 1;
	info->i2c.data_len = 1;


	//g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;


	i = 0;
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1);
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 10000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 1000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, GPIO_LOW, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 100);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 100);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *k06a_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_k06a_fps_info_asic); i++)
		if (fps == g_k06a_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_k06a_fps_info_asic))
		return NULL;
	return &g_k06a_fps_info_asic[i];
}

static int k06a_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct k06a_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("k06a get fps %.1f init info\n", mode->fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = k06a_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;
#ifdef _SENSOR_LOG_
	printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);
#endif

	set_init_i2c_regs(info->sensor_regs[0], g_k06a_i2c_init_regs_asic, 0);
	set_init_i2c_regs(info->sensor_regs[1], status->regs1, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x3;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2568;
	info->size.h = 1448;
	info->start.x = 5;
	info->start.y = 1;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = 1500;
	info->max_vts = info->min_vts * 30;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	//info->exposure_step = status->exp_step;

	return RTS_ISP_OK;
}

static int k06a_start(uint32_t isp_id)
{
	struct k06a_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure[0] = 0;

	return RTS_ISP_OK;
}

static int k06a_get_exposure_range(uint32_t isp_id, uint32_t vts,
					 float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
					 float min_exposure[RTS_ISP_HDR_CHAN_MAX],
					 float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct k06a_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;


	status = &g_status[isp_id];

	if (status->hdr == LINEAR_MODE) {
		min_exposure[0] = status->exp_step;
		max_exposure[0] = (vts - 4) * status->exp_step;
		
		debug("expusre_min = %1.f , expusre_max = %1.f\n", min_exposure[0],max_exposure[0]);
	} 


	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct k06a_status *status)
{
	int wAgainReg;
	if(fAGain>=1.0 && fAGain<2.0){
		wAgainReg = (int)(16.0f*(fAGain-1.0));
	}
	else if(fAGain>=2.0 && fAGain<4.0){
		wAgainReg = (int)(8.0f*(fAGain-2.0) + 16.0);
	}
	else if(fAGain>=4.0 && fAGain<8.0){
		wAgainReg = (int)(4.0f*(fAGain-4.0) + 32.0);
	}
	else if(fAGain>=8.0 && fAGain<=15.75){
		wAgainReg = (int)(2.0f*(fAGain-8.0) + 48.0);
	}
	else 
		wAgainReg = 0x3f;
		
	status->num = wAgainReg;
	return wAgainReg;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	float fAgainReg;
	float ftemp = wAGain;
	if(wAGain>=0 && wAGain<16){
		fAgainReg = (float)(ftemp/16.0 + 1);
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

	return (fAgainReg);
}

static int k06a_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct k06a_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);
	


	return RTS_ISP_OK;
}

static int k06a_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	struct k06a_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	
	status = &g_status[isp_id];
	
	dgain[0] = 1.0f;
	

	return RTS_ISP_OK;
}

static int k06a_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	int i;
	uint32_t vts;
	struct k06a_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows[2];
	
	
	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	
		vts = exp_gain->vts;
		reg = regs->reg;

		i = 0;
		if (abs(status->last_exposure[0] - exp_gain->exposure[0]) > 0.001f) {
			exposure_rows[0] = exp_gain->exposure[0] / status->exp_step + 0.5f;
			set_sync_i2c(&reg[i++], 0x02, exposure_rows[0] >> 8);
			set_sync_i2c(&reg[i++], 0x01, exposure_rows[0] & 0xff);
			
			debug("exposure = %d \n" , exposure_rows[0]);
		
			status->last_exposure[0] = exp_gain->exposure[0];
		}
		//set gain 		
		set_sync_i2c(&reg[i++], 0x00, status->num);
		//set vts 	
		set_sync_i2c(&reg[i++], 0x23, vts >> 8);
		set_sync_i2c(&reg[i++], 0x22, vts & 0xff);
		regs->num = i;
		
		debug("et-gain_inf vts= %d\n", vts );

	return RTS_ISP_OK;
}

static int k06a_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;
	struct k06a_status *status;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	
	status = &g_status[isp_id];
	
	switch(bySnrImgDir)//
	{
		case 0: //normal
		default:
            set_sync_i2c(&reg[i++], 0x12, 0x30);
			set_sync_i2c(&reg[i++], 0xaa, 0x84 & 0xff);
			break;
		case 2: 	// Mirror
            set_sync_i2c(&reg[i++], 0x12, 0x10);
			set_sync_i2c(&reg[i++], 0xaa, 0x8b & 0xff);
			break;
		case 1: 		// VFlip
            set_sync_i2c(&reg[i++], 0x12, 0x20);
			set_sync_i2c(&reg[i++], 0xaa, 0x84 & 0xff);
			break;
		case 3: 	// Rotate
            set_sync_i2c(&reg[i++], 0x12, 0x00);
			set_sync_i2c(&reg[i++], 0xaa, 0x8b & 0xff);		
			break;	
					
	}
	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int k06a_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;
	int idx = sensor_get_slave_addr_idx();

	if (idx >= SLAVE_ADDR_NUM)
		return -RTS_ISP_EINVAL;

	real_slave_addr = slave_addr_list[idx];

    rts_isp_sensor_access_prepare();

	reg.addr = 0x0A;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x0B;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id |= reg.data;
    rts_isp_sensor_access_unprepare();
		
	if (id == 0x0852)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int k06a_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops k06a_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "k06a",
	.get_info = k06a_get_info,
	.get_init_info = k06a_get_init_info,
	.start = k06a_start,
	.get_exposure_range = k06a_get_exposure_range,
	.get_tuned_again = k06a_get_tuned_again,
	.get_tuned_dgain = k06a_get_tuned_dgain,
	.get_exposure_gain_info = k06a_get_exposure_gain_info,
	.set_mirror_flip = k06a_set_mirror_flip,
	.check = k06a_check,
	.get_slave_addr_num = k06a_get_slave_addr_num,

};


const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &k06a_ops;
}

