/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <rts_isp_sensor.h>
#include <sensor_entry.h>
#ifdef _MIPIOUT_SENSOR_


#include <rtsavisp.h>
#include <fcntl.h>
//#include <sys/ioctl.h>  //Marked by Martin 20201223
#include <rts_ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define MIPI_I2C_CONTROLLER "/dev/i2c-0"

#define FPGA_FPS_SETTING

/* #define RESOLUTION_2M */
#define RESOLUTION_5M

/* #define RAW_8BIT */
/* #define RAW_10BIT */
/* #define RAW_12BIT */
#define YUV_YUYV8

/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1

#ifdef RESOLUTION_2M
#define SENSOR_WIDTH 1920
#define SENSOR_HEIGHT 1080
#define SENSOR_VTS 2560
#ifdef FPGA_FPS_SETTING
#define FPS 5
#define PCLK 48000000
#else
#define FPS 25
#define PCLK 72000000
#endif
#endif

#ifdef RESOLUTION_5M
#define SENSOR_WIDTH 2592
#define SENSOR_HEIGHT 1944
#define SENSOR_VTS 2560
#ifdef FPGA_FPS_SETTING
#define FPS 5
#define PCLK 48000000
#else
#define FPS 25
#define PCLK 180000000
#endif
#endif

#ifdef RAW_8BIT
#define BIT_DEPTH SNR_8BIT
#define TYPE RAW_SENSOR
#define MIPIOUT_TYPE RTS_ISP_MIPIOUT_RAW8
#endif
#ifdef RAW_10BIT
#define BIT_DEPTH SNR_10BIT
#define TYPE RAW_SENSOR
#define MIPIOUT_TYPE RTS_ISP_MIPIOUT_RAW10
#endif
#ifdef RAW_12BIT
#define BIT_DEPTH SNR_12BIT
#define TYPE RAW_SENSOR
#define MIPIOUT_TYPE RTS_ISP_MIPIOUT_RAW12
#endif
#ifdef YUV_YUYV8
#define BIT_DEPTH SNR_8BIT
#define TYPE YUV_SENSOR
#define MIPIOUT_TYPE RTS_ISP_MIPIOUT_YUYV
#endif

#define FIXP_FRAME_WIDTH 0x0800
#define FIXP_FRAME_HEIGHT 0x0804
#define FIXP_DUMMY_PIX 0x0808
#define FIXP_DUMMY_LINE 0x080c
#define FIXP_CTRL 0x0820
#define BLOCK_START_X 0x0828
#define BLOCK_START_Y 0x082c
#define BLOCK_WIDTH 0x0830
#define BLOCK_HEIGHT 0x0834
#define MARGIN_WIDTH 0x8038
#define MARGIN_HEIGHT 0x803c

#define MIPI_TX_EN 0xd0000
#define MIPI_TX_LANE_CFG 0xd0008
#define MIPI_TX_MULTI_LANE 0xd0044
#define MIPI_TX_START_POINT_CH0 0xd0054
#define MIPI_TX_FRAME_WIDTH 0xd0070
#define MIPI_TX_CH0_CFG 0xd004C
#define MIPI_TX_DIN_SEL 0xd00CC

#define DATA_TYPE_CH0_OFFSET 8
#define BYTE_SWP_CH0_OFFSET 5
#define UV_ORDER_CH0_OFFSET 6
#define RAW_EN_CH0_OFFSET 0
#define DATA_TYPE_CH0_MASK (((1 << 8) - 1) << 8)
#define UV_ORDER_CH0_MASK (((1 << 2) - 1) << 6)
#define BYTE_SWP_CH0_MASK (((1 << 1) - 1) << 5)
#define RAW_EN_CH0_MASK (((1 << 4) - 1) << 0)

struct mipi_out_i2c_reg {
	uint16_t addr;
	uint16_t val;
};

struct mipiout_config {
	enum rts_isp_sensor_bit_depth bit_depth;
	enum rts_isp_sensor_type type;
	enum rts_isp_mipiout_type mipiout_type;
	uint16_t fps;
	uint16_t vts;
	uint32_t pclk;
	uint32_t width;
	uint32_t height;
	uint8_t lanes;
};

struct mipiout_status {
	uint16_t hts;
	uint8_t lanes_num;
};

static const struct mipiout_config g_config = {
	.bit_depth = BIT_DEPTH,
	.type = TYPE,
	.mipiout_type = MIPIOUT_TYPE,
	.fps = FPS,
	.vts = SENSOR_VTS,
	.pclk = PCLK,
	.width = SENSOR_WIDTH,
	.height = SENSOR_HEIGHT,
	.lanes = MIPI_LANE0 | MIPI_LANE1,
};

static struct rts_isp_i2c_info mipiout_i2c_info = {
	.i2c_id = 0,
	.addr_len = 2,
	.data_len = 1,
};

extern void *isp_io_base;

struct mipiout_status g_status[SUPPORTED_ISP_NUM];

static inline uint32_t isp_read_reg(uint32_t offset)
{
	uint32_t value;

	value = *(volatile uint32_t *)(isp_io_base + offset);
	__sync_synchronize();
	return value;
}

static inline void isp_write_reg(uint32_t value, uint32_t offset)
{
	__sync_synchronize();
	*(volatile uint32_t *)(isp_io_base + offset) = value;
}

static inline void isp_write_reg_mask(uint32_t value, uint32_t offset,
				      uint32_t mask)
{
	uint32_t v;

	v = (isp_read_reg(offset) & ~mask) | (value & mask);
	isp_write_reg(v, offset);
}

static int mipiout_init(uint32_t isp_id)
{
	uint8_t lanes;

	debug("mipiout mipi init\n");
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	lanes = g_config.lanes;
	g_status[isp_id].lanes_num = 0;
	while (lanes) {
		g_status[isp_id].lanes_num++;
		lanes &= lanes - 1;
	};
	g_status[isp_id].hts = g_config.pclk / g_config.fps / g_config.vts;

	return RTS_ISP_OK;
}

static int mipiout_get_info(uint32_t isp_id,
				 struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = g_config.lanes;
	info->interface.mipi.hs_term = 0xa;
	info->interface.type = g_config.type;
	info->interface.bit_depth = g_config.bit_depth;
	if (info->interface.type == YUV_SENSOR)
		info->interface.yuv_type = SNR_YUYV;

	info->i2c = mipiout_i2c_info;

	info->size.w = g_config.width;
	info->size.h = g_config.height;
	info->crop.x = 0;
	info->crop.y = 0;
	info->crop.w = g_config.width;
	info->crop.h = g_config.height;

	i = 0;
	set_power_item(&up->items[i++], SNR_HCLK, 24000000, 0);
	up->num = i;
	i = 0;
	set_power_item(&down->items[i++], SNR_HCLK, 0, 0);
	down->num = i;

	info->fps.fps[0] = g_config.fps;
	info->fps.num = 1;

	return RTS_ISP_OK;
}
static int mipiout_get_init_info(uint32_t isp_id, uint16_t fps,
				      struct rts_isp_sensor_init_info *info)
{
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->hts = g_status[isp_id].hts;
	info->pclk = g_config.pclk;
	info->min_vts = g_config.vts;
	info->max_vts = g_config.vts;
	return RTS_ISP_OK;
}

static int mipiout_get_exposure_gain_info(uint32_t isp_id,
					struct rts_isp_exp_gain *exp_gain,
					struct rts_isp_sync_regs *regs)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mipiout_fixp_start(uint32_t isp_id)
{
	uint32_t block_width, block_height;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	isp_write_reg(0, FIXP_CTRL);
	isp_write_reg(g_config.width, FIXP_FRAME_WIDTH);
	isp_write_reg(g_config.height, FIXP_FRAME_HEIGHT);
	isp_write_reg(g_status[isp_id].hts - g_config.width, FIXP_DUMMY_PIX);
	isp_write_reg(g_config.vts - g_config.height, FIXP_DUMMY_LINE);

	block_width = (g_config.width - 0x14 * 7) / 8;
	block_height = (g_config.height - 0x14 * 5) / 6;
	isp_write_reg(block_width, BLOCK_START_X);
	isp_write_reg(block_height, BLOCK_START_Y);
	isp_write_reg(block_width, BLOCK_WIDTH);
	isp_write_reg(block_height, BLOCK_HEIGHT);

	if (g_config.type == RAW_SENSOR)
		isp_write_reg(0x80, FIXP_CTRL);
	else
		isp_write_reg(0xc0, FIXP_CTRL);

	return RTS_ISP_OK;
}

static int i2c_write(uint16_t slave_id, int addr_len, int data_len,
		     uint16_t addr, uint16_t val)
{
	int fd;
	int ret;
	int j = 0;
	uint8_t buf[4];
	struct i2c_msg msg;
	struct i2c_rdwr_ioctl_data ioctl_data;

	fd = open(MIPI_I2C_CONTROLLER, O_RDWR);
	if (fd < 0)
		return -errno;

	if (addr_len == 1) {
		buf[j++] = addr & 0xff;
	} else {
		buf[j++] = addr >> 8;
		buf[j++] = addr & 0xff;
	}
	if (data_len == 1) {
		buf[j++] = val & 0xff;
	} else {
		buf[j++] = val >> 8;
		buf[j++] = val & 0xff;
	}

	msg.addr = slave_id;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = j;

	ioctl_data.msgs = &msg;
	ioctl_data.nmsgs = 1;
	ret = ioctl(fd, I2C_RDWR, &ioctl_data);
	if (ret < 0) {
		perror("i2c transfer fail");
		return -errno;
	}
	return RTS_ISP_OK;
}

static int extern_aphy_reg_write(uint16_t addr, uint16_t val)
{
	return i2c_write(0x7A, 2, 1, addr, val);
}

static int extern_aphy_regs_write(struct mipi_out_i2c_reg *regs, int num)
{
	int i;
	int ret;

	if (!regs || !num)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < num; i++) {
		ret = extern_aphy_reg_write(regs[i].addr, regs[i].val);
		if (ret)
			return ret;
	}
	return RTS_ISP_OK;
}


static int mipiout_extern_aphy_init(void)
{
	struct mipi_out_i2c_reg regs[] = {
		/* Tx PLL On */
		{0x0409, 0x01},
		/* Tx Power On */
		{0x0400, 0x01},
		/* Driving 12mA for high speed */
		{0x0009, 0x0f},
		/* Lane 0 Skew */
		{0x0419, 0x08},
		/* Lane 3 Skew for 0551d pcb length not equal issue */
		{0x041c, 0x08},
	};

	return extern_aphy_regs_write(regs, ARRAY_SIZE(regs));
}

static int mipiout_extern_aphy_clk_cfg(uint32_t mipi_clk)
{
	uint16_t nc = mipi_clk / 12000000 - 2;
	struct mipi_out_i2c_reg regs[] = {
		/* DSI_RG_CMU_PREDV = 0 */
		{0x0415, 0x00},
		/* DSI_RG_CMU_PSTDV = 0 + 2 */
		{0x0424, 0x00},
		/* bypass PstDV */
		{0x042E, 0x00},
		/* DSI_RG_SSC_FC = 0 */
		{0x0434, 0x00},
		{0x0435, 0x00},
		/* DSI_RG_SSC_NC = 18 */
		{0x0436, nc & 0xff},
		{0x0437, nc >> 8},
		/* tx dphy data width = 8bit, mipi_tx_clk = mipi_clk / 8 */
		{0x0468, 0x00},
	};

	return extern_aphy_regs_write(regs, ARRAY_SIZE(regs));
}

static int mipiout_dpthy_config(uint32_t isp_id)
{
	uint32_t data_type, byte_swap, uv_order, fmt;

	isp_write_reg(0x0, MIPI_TX_EN);
	isp_write_reg(g_config.lanes, MIPI_TX_LANE_CFG);
	isp_write_reg(g_status[isp_id].lanes_num - 1, MIPI_TX_MULTI_LANE);
	isp_write_reg(g_config.width, MIPI_TX_FRAME_WIDTH);
	isp_write_reg(g_config.width / 4, MIPI_TX_START_POINT_CH0);

	switch (g_config.mipiout_type) {
	case RTS_ISP_MIPIOUT_RAW8:
		data_type = 0x2a;
		byte_swap = 1;
		uv_order = 0;
		fmt = 0;
		break;
	case RTS_ISP_MIPIOUT_RAW10:
		data_type = 0x2b;
		byte_swap = 1;
		uv_order = 0;
		fmt = 1;
		break;
	case RTS_ISP_MIPIOUT_RAW12:
		data_type = 0x2c;
		byte_swap = 1;
		uv_order = 0;
		fmt = 2;
		break;
	case RTS_ISP_MIPIOUT_YUYV:
		data_type = 0x1e;
		byte_swap = 0;
		uv_order = 3;
		fmt = 4;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	isp_write_reg_mask(data_type << DATA_TYPE_CH0_OFFSET |
			   byte_swap << BYTE_SWP_CH0_OFFSET |
			   uv_order << UV_ORDER_CH0_OFFSET |
			   fmt << RAW_EN_CH0_OFFSET,
			   MIPI_TX_CH0_CFG,
			   DATA_TYPE_CH0_MASK | UV_ORDER_CH0_MASK |
			   BYTE_SWP_CH0_MASK | RAW_EN_CH0_MASK);

	isp_write_reg(0x3, MIPI_TX_DIN_SEL);
	isp_write_reg(0x1, MIPI_TX_EN);
	return RTS_ISP_OK;
}

static int mipiout_mipiout_start(uint32_t isp_id)
{
	uint32_t mipi_clk;
	uint8_t bit_depth;
	int ret;

	ret = mipiout_extern_aphy_init();
	if (ret)
		return ret;

	if (g_config.type == RAW_SENSOR)
		bit_depth = BIT_DEPTH;
	else
		bit_depth = BIT_DEPTH * 2;

	mipi_clk = g_config.pclk * bit_depth / g_status[isp_id].lanes_num;
	ret = mipiout_extern_aphy_clk_cfg(mipi_clk);
	if (ret)
		return ret;
	ret = mipiout_dpthy_config(isp_id);
	if (ret)
		return ret;
	return RTS_ISP_OK;
}

static int mipiout_start(uint32_t isp_id)
{
	int ret;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	ret = mipiout_fixp_start(isp_id);
	if (ret)
		return ret;
	ret = mipiout_mipiout_start(isp_id);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

static int mipiout_stop(uint32_t isp_id)
{
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	isp_write_reg(0, FIXP_CTRL);
	isp_write_reg(0x0, MIPI_TX_EN);

	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops mipiout_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "mipiout",
	.init = mipiout_init,
	.get_info = mipiout_get_info,
	.get_init_info = mipiout_get_init_info,
	.get_exposure_gain_info = mipiout_get_exposure_gain_info,
	.start = mipiout_start,
	.stop = mipiout_stop,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &mipiout_ops;
}

#endif
