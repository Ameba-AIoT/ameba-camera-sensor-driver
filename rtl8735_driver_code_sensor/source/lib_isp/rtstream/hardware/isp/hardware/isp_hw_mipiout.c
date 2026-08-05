/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */
#if 0 

  #include "rts_ioctl.h"
  #define ioctl rts_ioctl

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <isp_utils.h>
#include <isp_hw_mipiout.h>
#include <isp_reg_mipiout.h>
#include <stdio.h>
#include <math.h>

#define MIPI_I2C_CONTROLLER "/dev/i2c-0"

struct mipi_out_i2c_reg {
	uint16_t addr;
	uint16_t val;
};

struct mipiout_config {
	uint32_t bit_depth;
	uint32_t data_type;
	uint32_t byte_swap;
	uint32_t uv_order;
	uint32_t fmt;
	uint32_t lanes;
	uint32_t lane_num;
	uint32_t position;
};

static int i2c_write(uint16_t slave_id, int addr_len, int data_len,
		     uint16_t addr, uint16_t val)
{
	int fd;
	int ret;
	int j = 0;
	uint8_t buf[4];
	struct i2c_msg msg;
	struct i2c_rdwr_ioctl_data ioctl_data;

	fd = rts_open(MIPI_I2C_CONTROLLER);
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
		isp_close(fd);
		return -errno;
	}
	isp_close(fd);
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

static int mipiout_get_config(struct mipiout_config *config, int lanes,
			      enum rts_isp_mipiout_type type,
			      enum rts_isp_mipiout_position position)
{
	switch (type) {
	case RTS_ISP_MIPIOUT_RAW8:
		config->bit_depth = 8;
		config->data_type = 0x2a;
		config->byte_swap = 1;
		config->uv_order = 0;
		config->fmt = 0;
		break;
	case RTS_ISP_MIPIOUT_RAW10:
		config->bit_depth = 10;
		config->data_type = 0x2b;
		config->byte_swap = 1;
		config->uv_order = 0;
		config->fmt = 1;
		break;
	case RTS_ISP_MIPIOUT_RAW12:
		config->bit_depth = 12;
		config->data_type = 0x2c;
		config->byte_swap = 1;
		config->uv_order = 0;
		config->fmt = 2;
		break;
	case RTS_ISP_MIPIOUT_YUYV:
		config->bit_depth = 16;
		config->data_type = 0x1e;
		config->byte_swap = 0;
		config->uv_order = 3;
		config->fmt = 4;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	config->lanes = lanes;
	config->lane_num = isp_get_val_weight(lanes);
	switch (position) {
	case RTS_ISP_MIPIOUT_BEFORE_CROP:
		config->position = 0x0;
		break;
	case RTS_ISP_MIPIOUT_AFTER_CROP:
		config->position = 0x5;
		break;
	case RTS_ISP_MIPIOUT_BEFORE_ZOOM:
		config->position = 0x1;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	return RTS_ISP_OK;
}

static int mipiout_hs_prpr_time(uint32_t mipi_clk)
{
	/* Tpre = (8 * (cfg + dummy)) * UI, UI = 1 / mipi_clk, dummy = (0~2) */
	/* Tpre min = 40ns + 4 * UI, max = 85ns + 6 * UI */
	/* set it as: Tpre = (min + max) / 2 , dummy = 0 return cfg */
	return ceil(7.8125f * mipi_clk * 1e-9 + 0.625f);
}

static int isp_hw_mipiout_set(uint32_t isp_id,
			      const struct isp_mipiout_info *info)
{
	int ret;
	struct mipiout_config config;

	if (!info->mipiout.enable) {
		isp_write_reg(0x0, MIPI_TX_EN);
		return RTS_ISP_OK;
	}

	ret = mipiout_get_config(&config, info->mipiout.lanes,
				 info->mipiout.type, info->mipiout.position);
	if (ret)
		return ret;

	isp_write_reg(config.lanes, MIPI_TX_LANE_CFG);
	isp_write_reg(config.lane_num - 1, MIPI_TX_MULTI_LANE);
	isp_write_reg(info->size.w, MIPI_TX_FRAME_WIDTH);
	isp_write_reg(info->size.w / 4, MIPI_TX_START_POINT_CH0);

	isp_write_reg_mask(config.data_type << DATA_TYPE_CH0_OFFSET |
			   config.byte_swap << BYTE_SWP_CH0_OFFSET |
			   config.uv_order << UV_ORDER_CH0_OFFSET |
			   config.fmt << RAW_EN_CH0_OFFSET,
			   MIPI_TX_CH0_CFG,
			   DATA_TYPE_CH0_MASK | UV_ORDER_CH0_MASK |
			   BYTE_SWP_CH0_MASK | RAW_EN_CH0_MASK);
	isp_write_reg(config.position, MIPI_TX_DIN_SEL);
	isp_write_reg(mipiout_hs_prpr_time(info->mipi_clk),
		      MIPI_TX_HS_PRPR_TIME);

	isp_write_reg(0x1, MIPI_TX_EN);

	if (info->is_fpga) {
		ret = mipiout_extern_aphy_init();
		if (ret)
			return ret;
		ret = mipiout_extern_aphy_clk_cfg(info->mipi_clk);
		if (ret)
			return ret;
	} else {
		uint8_t div = ceil(max_t(uint32_t, info->mipi_clk, 400e6) /
			      1e6 / 25) - 2;
		/* mipiout aphy parameter optimize */
		isp_write_reg_mask(0x1d << REG_DATA0_DLY_OFFSET,
				   MIPI_TX_APHY_CFG_1, REG_DATA0_DLY_MASK);
		isp_write_reg_mask(0xa << REG_Z0_TX_OFFSET,
				   MIPI_TX_APHY_CFG_11, REG_Z0_TX_MASK);
		isp_write_reg_mask(0x1 << REG_LPLDO_LVL_OFFSET,
				   MIPI_TX_APHY_CFG_4, REG_LPLDO_LVL_MASK);
		/* mipiout aphy clk cfg */
		isp_write_reg_mask(0 << REG_MPLL_PDIV_OFFSET,
				   MIPI_TX_APHY_CFG_6, REG_MPLL_PDIV_MASK);
		isp_write_reg_mask(div << REG_MPLL_DIVN_OFFSET,
				   MIPI_TX_APHY_CFG_5, REG_MPLL_DIVN_MASK);
		isp_write_reg_mask(0x1 << REG_MPLL_PI_PH_OFFSET,
				   MIPI_TX_APHY_CFG_7, REG_MPLL_PI_PH_MASK);
		isp_write_reg_mask(0x1 << REG_PAD_STR_OFFSET,
				   MIPI_TX_APHY_CFG_9, REG_PAD_STR_MASK);
		isp_write_reg(0x1, MIPI_TX_APHY_CFG_12);
	}

	return RTS_ISP_OK;
}

static const struct isp_hw_mipiout_ops hw_mipiout_ops = {
	.set = isp_hw_mipiout_set,
};

const struct isp_hw_mipiout_ops *isp_hw_mipiout_get_ops(void)
{
	return &hw_mipiout_ops;
}
#endif
