/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2026 Hank Chang <hank.chang@realtek.com>
 */

#include <stdio.h>
#include <platform_conf.h>
#include <rts_isp_sensor_lib.h>
#include <sensor_entry.h>

// #define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2
#define ANALOG_GAIN_MAX_RATIO (float)160.0

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t vts;
	uint32_t clk;
};

struct gc4693_status {
	enum rts_isp_sensor_hdr_mode hdr;
	float exp_step;
	float last_exposure;
	uint16_t last_vts;
	uint16_t min_vts;
};

static struct gc4693_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_gc4693_fps_info_4m[] = {
	{30.0f, 3200, 1525, 146400000},
};

static struct rts_isp_i2c_reg g_gc4693_i2c_init_regs_4m[] = {
	//mipi_rate 732Mbps/lane					
	//wpclk=366Mhz,rpclk=146.4Mhz				
	//FL=1525,HB=1000,rowtime=21.86us  
	{0x03fe, 0xf0}, 							  
	{0x03fe, 0x00}, 							  
	{0x03fe, 0x10}, 							  
	{0x0b66, 0x02}, 							  
	{0x0b69, 0x70}, 							  
	{0x0d47, 0x03}, 							  
	{0x03be, 0x7f}, 							  
	{0x01c6, 0x44}, 							  
	{0x01c8, 0x00}, 							  
	{0x01c9, 0xf4}, 							  
	{0x01c6, 0x44}, 							  
	{0x01ca, 0x21}, 							  
	{0x01cb, 0x08}, 							  
	{0x0102, 0x80}, 							  
	{0x01c7, 0x6a}, 							  
	{0x03c7, 0x1f}, 							  
	{0x03ba, 0x01}, 							  
	{0x03bb, 0x33}, 							  
	{0x031c, 0x47}, 							  
	{0x03be, 0x7f}, 							  
	{0x0d43, 0x35}, 							  
	{0x0b67, 0x77}, 							  
	{0x0e0a, 0x00}, 							  
	{0x0e0c, 0x08}, 							  
	{0x0e43, 0xbd}, 							  
	{0x0e45, 0xb7}, 							  
	{0x0e0e, 0x00}, 							  
	{0x0e0f, 0x00}, 							  
	{0x0d48, 0x00}, 							  
	{0x0d49, 0x00}, 							  
	{0x0b62, 0x34}, 							  
	{0x0d40, 0x08}, 							  
	{0x0d44, 0xff}, 							  
	{0x0d4c, 0xff}, 							  
	{0x0d41, 0x05}, 							  
	{0x0d4b, 0x05}, 							  
	{0x0e27, 0x04}, 							  
	{0x0e49, 0xb0}, 							  
	{0x0e19, 0xaa}, 							  
	{0x0e23, 0xc0}, 							  
	{0x0e40, 0x6e}, 							  
	{0x0e1f, 0x05}, 							  
	{0x0e47, 0xa6}, 							  
	{0x0e41, 0x31}, 							  
	{0x0e3f, 0x31}, 							  
	{0x0b63, 0x0c}, 							  
	{0x0e35, 0x89}, 							  
	{0x03be, 0x7f}, 							  
	{0x0d42, 0x42}, 							  
	{0x0e36, 0x1e}, 							  
	{0x0e4e, 0x00}, 							  
	{0x0e4f, 0xbb}, 							  
	{0x0c23, 0x40}, 							  
	{0x0e22, 0x30}, 							  
	{0x0e6e, 0x02}, 							  
	{0x0e23, 0x00}, 							  
	{0x0e26, 0xcf}, 							  
	{0x0e37, 0xad}, 							  
	{0x0e31, 0x2d}, 							  
	{0x03be, 0x7f}, 							  
	{0x0e21, 0x09}, 							  
	{0x0e37, 0xad}, 							  
	{0x0e12, 0x00}, 							  
	{0x0b64, 0x20}, 							  
	{0x03bd, 0x5f}, 							  
	{0x0151, 0x0a}, 							  
	{0x03bf, 0x40}, 							  
	{0x014d, 0x01}, 							  
	{0x0006, 0x07}, 							  
	{0x0e50, 0xf4}, 							  
	{0x0e08, 0x05}, 							  
	{0x0212, 0x20}, 							  
	{0x0213, 0x04}, 							  
	{0x0219, 0xc6}, 							  
	{0x0259, 0x05}, 							  
	{0x025a, 0xbc}, 							  
	{0x0340, 0x05}, 							  
	{0x0341, 0xf5}, 							  
	{0x0342, 0x03}, 							  
	{0x0343, 0xe8}, 							  
	{0x0217, 0x06}, 							  
	{0x0346, 0x00}, 							  
	{0x0347, 0x04}, 							  
	{0x0348, 0x0a}, 							  
	{0x0349, 0x08}, 							  
	{0x034a, 0x05}, 							  
	{0x034b, 0xa8}, 							  
	{0x0346, 0x00}, 							  
	{0x0347, 0x04}, 							  
	{0x0b0c, 0x00}, 							  
	{0x0b0d, 0x04}, 							  
	{0x0b0e, 0x0a}, 							  
	{0x0b0f, 0x0c}, 							  
	{0x034e, 0x0a}, 							  
	{0x034f, 0x28}, 							  
	{0x0239, 0x00}, 							  
	{0x023a, 0x41}, 							  
	{0x0089, 0x00}, 							  
	{0x0073, 0x85}, 							  
	{0x0004, 0x0f}, 							  
	{0x0038, 0x00}, 							  
	{0x0039, 0x00}, 							  
	{0x003a, 0x00}, 							  
	{0x003b, 0x00}, 							  
	{0x003c, 0x00}, 							  
	{0x003d, 0x00}, 							  
	{0x003e, 0x00}, 							  
	{0x003f, 0x00}, 							  
	{0x0082, 0x00}, 							  
	{0x0083, 0x00}, 							  
	{0x0096, 0x05}, 							  
	{0x0097, 0xa0}, 							  
	{0x0094, 0x0a}, 							  
	{0x0095, 0x00}, 							  
	{0x004a, 0x00}, 							  
	{0x004b, 0x00}, 							  
	{0x0099, 0x04}, 							  
	{0x009b, 0x04}, 							  
	{0x0310, 0x00}, 							  
	{0x035a, 0x00}, 							  
	{0x035b, 0x40}, 							  
	{0x0d41, 0x05}, 							  
	{0x0202, 0x00}, 							  
	{0x0203, 0x50}, 							  
	{0x0070, 0x40}, 							  
	{0x0089, 0x00}, 							  
	{0x0073, 0x85}, 							  
	{0x0e0b, 0x00}, 							  
	{0x0d04, 0x01}, 							  
	{0x0e37, 0xad}, 							  
	{0x0e31, 0x2d}, 							  
	{0x0485, 0x62}, 							  
	{0x0800, 0x01}, 							  
	{0x0810, 0x01}, 							  
	{0x0810, 0x00}, 							  
	{0x0801, 0xff}, 							  
	{0x0803, 0xc0}, 							  
	{0x080b, 0x78}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x00}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x40}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x5a}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x93}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0xcd}, 							  
	{0x0885, 0x01}, 							  
	{0x0886, 0x26}, 							  
	{0x0885, 0x01}, 							  
	{0x0886, 0xa6}, 							  
	{0x0885, 0x02}, 							  
	{0x0886, 0x4d}, 							  
	{0x0885, 0x03}, 							  
	{0x0886, 0x40}, 							  
	{0x0885, 0x04}, 							  
	{0x0886, 0x8d}, 							  
	{0x0885, 0x06}, 							  
	{0x0886, 0x53}, 							  
	{0x0885, 0x09}, 							  
	{0x0886, 0x0d}, 							  
	{0x0885, 0x0d}, 							  
	{0x0886, 0x20}, 							  
	{0x0885, 0x12}, 							  
	{0x0886, 0x6d}, 							  
	{0x0885, 0x1a}, 							  
	{0x0886, 0x73}, 							  
	{0x0885, 0x24}, 							  
	{0x0886, 0xd3}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x0f}, 							  
	{0x0885, 0x0e}, 							  
	{0x0886, 0x0b}, 							  
	{0x0885, 0x0d}, 							  
	{0x0886, 0x04}, 							  
	{0x0885, 0x0e}, 							  
	{0x0886, 0x23}, 							  
	{0x0885, 0x0b}, 							  
	{0x0886, 0x62}, 							  
	{0x0885, 0x0e}, 							  
	{0x0886, 0x22}, 							  
	{0x0885, 0x0e}, 							  
	{0x0886, 0x0c}, 							  
	{0x0885, 0x0b}, 							  
	{0x0886, 0x63}, 							  
	{0x0885, 0x0e}, 							  
	{0x0886, 0x0c}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x17}, 							  
	{0x0885, 0x30}, 							  
	{0x0886, 0x01}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x34}, 							  
	{0x0885, 0x30}, 							  
	{0x0886, 0x00}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x00}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x1b}, 							  
	{0x0885, 0x30}, 							  
	{0x0886, 0x02}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x34}, 							  
	{0x0885, 0x2f}, 							  
	{0x0886, 0x00}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x00}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x1f}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x01}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x34}, 							  
	{0x0885, 0x30}, 							  
	{0x0886, 0x00}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x00}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x23}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x02}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x34}, 							  
	{0x0885, 0x2f}, 							  
	{0x0886, 0x00}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x00}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x27}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x03}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x2a}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x2b}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x04}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x28}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x2f}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x05}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x26}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x33}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x06}, 							  
	{0x0885, 0x80}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x18}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x37}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x07}, 							  
	{0x0885, 0x80}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x14}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x3b}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x0f}, 							  
	{0x0885, 0x80}, 							  
	{0x0886, 0x35}, 							  
	{0x0885, 0x0f}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x3f}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x17}, 							  
	{0x0885, 0x80}, 							  
	{0x0886, 0x36}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x43}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x1f}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x36}, 							  
	{0x0885, 0x1b}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x47}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x27}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x36}, 							  
	{0x0885, 0x18}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x4b}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x2f}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x37}, 							  
	{0x0885, 0x17}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x0c}, 							  
	{0x0886, 0x08}, 							  
	{0x0880, 0x00}, 							  
	{0x0881, 0x4f}, 							  
	{0x0885, 0x00}, 							  
	{0x0886, 0x37}, 							  
	{0x0885, 0x40}, 							  
	{0x0886, 0x38}, 							  
	{0x0885, 0x15}, 							  
	{0x0886, 0x08}, 							  
	{0x0885, 0x68}, 							  
	{0x0886, 0x08}, 							  
	{0x080c, 0x4b}, 							  
	{0x0803, 0xc1}, 							  
	{0x0807, 0x00}, 							  
	{0x0808, 0x40}, 							  
	{0x0080, 0x02}, 							  
	{0x05be, 0x01}, 							  
	{0x0a67, 0x80}, 							  
	{0x0a51, 0x45}, 							  
	{0x0a58, 0x0c}, 							  
	{0x0a59, 0x0c}, 							  
	{0x0a53, 0x4e}, 							  
	{0x0a74, 0x0c}, 							  
	{0x0a68, 0x08}, 							  
	{0x0a6f, 0x08}, 							  
	{0x0a4e, 0x00}, 							  
	{0x0a4f, 0x00}, 							  
	{0x05be, 0x00}, 							  
	{0x05a9, 0x01}, 							  
	{0x0021, 0x00}, 							  
	{0x0a90, 0x83}, 							  
	{0x0aac, 0x00}, 							  
	{0x0aad, 0xe0}, 							  
	{0x0028, 0x0a}, 							  
	{0x0029, 0x08}, 							  
	{0x002a, 0x05}, 							  
	{0x002b, 0xa8}, 							  
	{0x0a94, 0x80}, 							  
	{0x05be, 0x01}, 							  
	{0x0080, 0x02}, 							  
	{0x0004, 0x0b}, 							  
	{0x022c, 0x00}, 							  
	{0x0100, 0x03}, 							  
	{0x0109, 0x05}, 							  
	{0x010a, 0x01}, 							  
	{0x01cd, 0x13}, 							  
	{0x010b, 0x01}, 							  
	{0x010c, 0x2b}, 							  
	{0x010d, 0x0c}, 							  
	{0x010e, 0x80}, 							  
	{0x0261, 0x1b}, 							  
	{0x0327, 0x46}, 							  
	{0x0336, 0x01}, 							  
	{0x0336, 0x00}, 							  
	{0x03fe, 0x00},
};
#define SLAVE_ADDR_NUM 2
#define SLAVE_ADDR_0 0x31	//0x52(ID_SEL=0,default)
#define SLAVE_ADDR_1 0x10	//0x20(ID_SEL=1)

uint32_t slave_addr_list[SLAVE_ADDR_NUM] = { SLAVE_ADDR_0, SLAVE_ADDR_1 };
uint32_t real_slave_addr = SLAVE_ADDR_0;
static int gc4693_get_info(uint32_t isp_id,
				struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	i = 0;

	info->modes.mode[i].fps = g_gc4693_fps_info_4m[0].fps;
	info->modes.mode[i].hdr = LINEAR_MODE;
	info->modes.mode[i].size.w = 2560;
	info->modes.mode[i].size.h = 1440;
	
	i++;
	info->modes.num = i;

	info->i2c.i2c_id = real_slave_addr;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	info->cur_hdr_mode = g_status->hdr;

	i = 0;
	set_power_item(&up->items[i++], SNR_HCLK, 0, 0);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 5000);
	
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 1000);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_HIGH, 1000);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 8000);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 10000);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 10000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 10000);
	down->num = i;

	return RTS_ISP_OK;
}

static const struct fps_info *gc4693_get_fps_info(uint16_t fps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(g_gc4693_fps_info_4m); i++)
		if (fps == g_gc4693_fps_info_4m[i].fps)
			break;
	if (i == ARRAY_SIZE(g_gc4693_fps_info_4m))
		return NULL;
	return &g_gc4693_fps_info_4m[i];
}

static int gc4693_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct gc4693_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = gc4693_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	set_init_i2c_regs(info->sensor_regs[0], g_gc4693_i2c_init_regs_4m, 0);

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x7;
	info->interface.type = RAW_SENSOR;
	info->interface.bit_depth = SNR_10BIT;
	info->mipi_behavor = NONE_HDR;

	info->size.w = 2560;
	info->size.h = 1440;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	info->min_vts = status->min_vts = fps_info->vts;
	info->max_vts = 65535;

	status->exp_step = 1e6 * info->hts / info->pclk; /* us  1e6 * 3200 / 146400000 =  21.86us*/

	return RTS_ISP_OK;
}

static int gc4693_start(uint32_t isp_id)
{
	struct gc4693_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	status->last_exposure = 0;

	return RTS_ISP_OK;
}

static int gc4693_get_exposure_range(uint32_t isp_id, uint32_t vts,
				float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				float max_exposure[RTS_ISP_HDR_CHAN_MAX])
{
	struct gc4693_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	min_exposure[0] = status->exp_step;
	max_exposure[0] = (vts - 16) * status->exp_step;

	debug("max_exposure = %f, min_exposure = %f\n", max_exposure[0], min_exposure[0]);
	
	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fgain)
{
	uint16_t reg_value = 0;

	if (fgain >= ANALOG_GAIN_MAX_RATIO)
		reg_value = ANALOG_GAIN_MAX_RATIO * 64.f;
	else
		reg_value = fgain * 64.f;
	
	return reg_value;
}

static float get_sensor_real_gain(uint16_t reg_value)
{
	return reg_value / 64.0f;
}

static int gc4693_get_tuned_again(uint32_t isp_id,
				float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct gc4693_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	gain_reg = get_sensor_gain_reg(again[0]);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}

static int gc4693_get_tuned_dgain(uint32_t isp_id,
				float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;

	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int gc4693_get_exposure_gain_info(uint32_t isp_id,
				const struct rts_isp_sensor_exp_gain *exp_gain,
				struct rts_isp_sync_regs *regs)
{
	int i;
	struct gc4693_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows, frame_length, gain_reg;

	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	frame_length = exp_gain->vts;
	reg = regs->reg;

	i = 0;
	/* set vts */
	if (abs(status->last_vts - frame_length) > 0.001f) {
		set_sync_i2c(&reg[i++], 0x0340, frame_length >> 8);
		set_sync_i2c(&reg[i++], 0x0341, frame_length & 0xff);
		status->last_vts = frame_length;
	}

	/* set exposure */	
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		set_sync_i2c(&reg[i++], 0x0202, exposure_rows >> 8);
		set_sync_i2c(&reg[i++], 0x0203, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}

	/* set gain */
	gain_reg = get_sensor_gain_reg(exp_gain->analog_gain[0] * exp_gain->digital_gain[0]);
	
	set_sync_i2c(&reg[i++], 0x0807, gain_reg >> 8);
	set_sync_i2c(&reg[i++], 0x0808, gain_reg & 0xff);
	regs->num = i;
	
	return RTS_ISP_OK;
}

static int gc4693_set_mirror_flip(uint32_t isp_id,
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

	switch(bySnrImgDir)
	{
		case 0: // Normal
		default:
			set_sync_i2c(&reg[i++], 0x022c, 0x00);
		break;
		case 1: // Mirror
			set_sync_i2c(&reg[i++], 0x022c, 0x01);
		break;
		case 2: // VFlip
			set_sync_i2c(&reg[i++], 0x022c, 0x02);
		break;
		case 3: // Rotate
			set_sync_i2c(&reg[i++], 0x022c, 0x03);
		break;
	}

	mf_info->regs.num = i;
	return RTS_ISP_OK;
}

static int gc4693_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

    rts_isp_sensor_access_prepare();

	reg.addr = 0x03f0;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x03f1;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;
	if (id == 0x4693)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
}

static int gc4693_get_slave_addr_num(uint32_t isp_id)
{
	return SLAVE_ADDR_NUM;
}

static const struct rts_isp_sensor_ops gc4693_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "gc4693",

	.get_info = gc4693_get_info,
	.get_init_info = gc4693_get_init_info,
	.start = gc4693_start,
	.get_exposure_range = gc4693_get_exposure_range,
	.get_tuned_again = gc4693_get_tuned_again,
	.get_tuned_dgain = gc4693_get_tuned_dgain,
	.get_exposure_gain_info = gc4693_get_exposure_gain_info,
	.set_mirror_flip = gc4693_set_mirror_flip,
	.check = gc4693_check,
	.get_slave_addr_num = gc4693_get_slave_addr_num,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &gc4693_ops;
}
