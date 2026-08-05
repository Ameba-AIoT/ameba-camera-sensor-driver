/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_interface.h>
#include <isp_reg_mipiin.h>
#include <isp_reg_tnr.h>
#include <isp_reg_fusion.h>
#include <isp_reg_awb.h>

//#define DEBUG

#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

uint32_t mipi_clk_noncontinous = 0;


static int get_mipi_data_type(int type, int bit_depth)
{
	if (type == YUV_SENSOR) {
		return 0x1E;
	} else if (type == RAW_SENSOR) {
		if (bit_depth == 8)
			return 0x2A;
		else if (bit_depth == 10)
			return 0x2B;
		else
			return 0x2C;
	}
	return -RTS_ISP_EINVAL;
}

static int get_mipi_data_fmt(int type, int bit_depth, int yuv_type)
{
	if (type == YUV_SENSOR) {
		return 0x02 | yuv_type << 8; // different from SDK 4.1
	} else if (type == RAW_SENSOR) {
		if (bit_depth == 8)
			return 0x00;
		else if (bit_depth == 10)
			return 0x01;
		else
			return 0x04;
	}
	return -RTS_ISP_EINVAL;
}

static int get_mipi_rx_pos(uint32_t pclk, uint32_t mipi_clk,
			   int lanes, int bit_num)
{
	int val_weight = isp_get_val_weight(lanes);

	debug("%s: lanes=%d val_weight=%d pclk=%d bit_num=%d\n",__func__, lanes, val_weight, pclk, bit_num);

	return (val_weight != 0)?(mipi_clk * 12 / (pclk * bit_num / val_weight / 4)) : 0;
}

static int mipi_set_enable(int enable)
{
	struct rts_isp_i2c i2c;

	i2c.info.addr_len = 2;
	i2c.info.data_len = 1;
	i2c.info.i2c_id = 0x69;
	i2c.num = 1;
	i2c.regs[0].addr = 0x0410;
	i2c.regs[0].data = !enable;

	return isp_driver_aphy_i2c_write(&i2c);
}

static int mipi_start_extern_aphy(void)
{
	return mipi_set_enable(RTS_ISP_TRUE);
}

static int mipi_stop_extern_aphy(void)
{
	return mipi_set_enable(RTS_ISP_FALSE);
}

static int mipi_config_hdr(uint32_t isp_id,
			   const struct isp_interface_info *info)
{
	if (info->hdr.behavor == NONE_HDR) {
		isp_write_reg(0, MIPI_DPHY_INPUT_MODE);
		debug("mipi in Linear mode\n");

		//VHDR Stream control
		//isp_write_reg(0x03, 0x00021918);
		isp_write_reg_mask(0 << FUSION_CFG_UNDERFLOW_FRAME_START_EN_OFFSET | 0 << FUSION_CFG_LENGTH_FRAME_END_CLR_EN_OFFSET, FUSION_STREAM_CTRL2,
		FUSION_CFG_UNDERFLOW_FRAME_START_EN_MASK | FUSION_CFG_LENGTH_FRAME_END_CLR_EN_MASK);
		//isp_write_reg(0x06, 0x00021908);
		isp_write_reg_mask(0 << FUSION_DATA_REQ_EN_OFFSET | 0 << FUSION_BURST_LENGTH_SEL_RD_OFFSET, FUSION_STREAM_CTRL,
		FUSION_DATA_REQ_EN_MASK | FUSION_BURST_LENGTH_SEL_RD_MASK);

		//VHDR Stream switch (enable)
		isp_write_reg(0, FUSION_STREAM_EN);

		//Clip 14bit (enable)
		isp_set_reg_bit(CLIP_14BITS_ENABLE_OFFSET, AWB_OVER_EXP_REDUCT_EN);

		return RTS_ISP_OK;
	}

	printf("mipi in HDR mode mode %d short_exp %d\n", info->hdr.behavor, info->info->mipi_max_short_exp);
	if (info->hdr.behavor == STAGGER_DUMMY_HDR ||
	    info->hdr.behavor == STAGGER_NODUMMY_HDR) {
		isp_write_reg(info->info->mipi_max_short_exp,
			      MIPI_DPHY_MAX_SRT_EXP);
	} else if (info->hdr.behavor == FID_BASED_HDR) {
		uint32_t fid = info->hdr.fid.fid ? info->hdr.fid.fid : 0x201;
		isp_write_reg(fid, MIPI_DPHY_FID);
	} else {
		isp_write_reg(info->info->mipi_max_short_exp,
			      MIPI_DPHY_MAX_SRT_EXP);
	}

	//if (info->hdr.behavor != FID_BASED_HDR) {
	//	isp_clr_reg_bit(TRANS_MODE_SEL_OFFSET, MIPI_DPHY_LANE_CTRL);
	//}


	isp_write_reg(info->hdr.behavor, MIPI_DPHY_INPUT_MODE);

	// Set over_exposed_data_sel to from fusion
	isp_clr_reg_bit(FUSION_OVEXP_DATA_SEL_OFFSET, FUSION_OVEXP_SLOP);

	//Clip 14bit (disable)
	isp_clr_reg_bit(CLIP_14BITS_ENABLE_OFFSET, AWB_OVER_EXP_REDUCT_EN);

	//DDR Configuration
	debug("%x\n", isp_read_reg(TNR_STREAM_FRAME_ADDR));
	isp_write_reg(isp_read_reg(TNR_STREAM_FRAME_ADDR), FUSION_STREAM_FRAME_ADDR);
	isp_write_reg(isp_read_reg(TNR_STREAM_DDR_LEN), FUSION_STREAM_DDR_LEN);

	//VHDR Stream switch (enable)
	isp_write_reg(1, FUSION_STREAM_EN);

	//VHDR Stream start line set for tnr
	isp_write_reg(info->info->vhdr_start_line_tnr, FUSION_STREAM_START_LINENUM);

	//VHDR Stream control
	//isp_write_reg(0x03, 0x00021918);
	isp_write_reg_mask(1 << FUSION_CFG_UNDERFLOW_FRAME_START_EN_OFFSET | 1 << FUSION_CFG_LENGTH_FRAME_END_CLR_EN_OFFSET, FUSION_STREAM_CTRL2,
	FUSION_CFG_UNDERFLOW_FRAME_START_EN_MASK | FUSION_CFG_LENGTH_FRAME_END_CLR_EN_MASK);
	//isp_write_reg(0x06, 0x00021908);
	isp_write_reg_mask(1 << FUSION_DATA_REQ_EN_OFFSET | 1 << FUSION_BURST_LENGTH_SEL_RD_OFFSET, FUSION_STREAM_CTRL,
	FUSION_DATA_REQ_EN_MASK | FUSION_BURST_LENGTH_SEL_RD_MASK);

	return RTS_ISP_OK;
}

static int mipi_init(uint32_t isp_id,
		     const struct isp_interface_info *info)
{
	uint8_t pixel_bits;
	int mipi_data_fmt;
	int mipi_data_type;
	const struct rts_isp_mipi_info *mipi;

	if (!info || info->info->interface != SNR_INTERFACE_MIPI)
		return -RTS_ISP_EINVAL;

	mipi_data_fmt = get_mipi_data_fmt(info->info->type,
					  info->info->bit_depth,
					  info->info->yuv_type);
	mipi_data_type = get_mipi_data_type(info->info->type,
					    info->info->bit_depth);
	if (mipi_data_fmt < 0 || mipi_data_type < 0)
		return -RTS_ISP_EINVAL;

	pixel_bits = info->info->bit_depth;
	if (info->info->type == YUV_SENSOR)
		pixel_bits *= 2;

	mipi = &info->info->mipi;
	if (mipi->lanes == 0)
		return -RTS_ISP_EINVAL;

	isp_write_reg_mask(0x30, MIPI_APHY_REG0, R50_CAL_RG_MASK);
	isp_write_reg_mask(0x0, MIPI_APHY_REG1, EN_R50_AUTO_CAL_RG_MASK);
	isp_write_reg(mipi->data_skew << SDATA0_SKW_RG_OFFSET |
		      mipi->data_skew << SDATA1_SKW_RG_OFFSET,
		      MIPI_APHY_REG7);
	isp_write_reg(mipi->data_skew << SDATA2_SKW_RG_OFFSET |
		      mipi->data_skew << SDATA3_SKW_RG_OFFSET,
		      MIPI_APHY_REG8);
	isp_write_reg(mipi->clk_skew << SCLK0_SKW_RG_OFFSET |
		      mipi->clk_skew << SCLK1_SKW_RG_OFFSET,
		      MIPI_APHY_REG9);
	isp_write_reg(mipi->clk_skew << SCLK2_SKW_RG_OFFSET |
		      mipi->clk_skew << SCLK3_SKW_RG_OFFSET,
		      MIPI_APHY_REG10);
	isp_write_reg(1, MIPI_APHY_REG15);

	if ( mipi_clk_noncontinous ) {
		isp_write_reg(PIX_DIN_MIPI_SEL_MASK | CRC16_EN_MASK | ECC_EN_MASK | CLK_LANE_EN_MASK,
					MIPI_DPHY_CFG0);
		isp_write_reg(LANE0_TERM_EN_CFG_MASK | LANE1_TERM_EN_CFG_MASK | LANE2_TERM_EN_CFG_MASK | LANE3_TERM_EN_CFG_MASK | CLK_TERM_EN_CFG_MASK,
				MIPI_DPHY_TERM_CFG);
		printf("[MIPI]turn on clk lane non-continuous \n");

	} else {
		isp_write_reg(PIX_DIN_MIPI_SEL_MASK | CRC16_EN_MASK | ECC_EN_MASK,
				MIPI_DPHY_CFG0);
		isp_write_reg(LANE0_TERM_EN_CFG_MASK | LANE1_TERM_EN_CFG_MASK | LANE2_TERM_EN_CFG_MASK | LANE3_TERM_EN_CFG_MASK,
				MIPI_DPHY_TERM_CFG);
		//printf("[MIPI]turn off clk lane non-continuous \n");
	}
	isp_write_reg(0, MIPI_DPHY_DIVSEL);
	isp_write_reg(0, MIPI_DPHY_HSCLK_SEL);
	isp_write_reg(mipi->hs_term << HL_INTERVAL_0_OFFSET |
		      mipi->hs_term << HL_INTERVAL_1_OFFSET,
		      MIPI_DPHY_HSTERM0);
	isp_write_reg(mipi->hs_term << HL_INTERVAL_2_OFFSET |
		      mipi->hs_term << HL_INTERVAL_3_OFFSET,
		      MIPI_DPHY_HSTERM1);
	isp_write_reg(mipi_data_fmt << DEC_FORMAT0_OFFSET |
		      (mipi_data_type | 0 << 6) << DEC_ID0_OFFSET,
		      MIPI_DPHY_VC0_DATA_FORMAT);
	isp_write_reg(mipi_data_fmt << DEC_FORMAT1_OFFSET |
		      (mipi_data_type | 1 << 6) << DEC_ID1_OFFSET,
		      MIPI_DPHY_VC1_DATA_FORMAT);
	isp_write_reg(get_mipi_rx_pos(info->pixel_clk, info->interface_clk,
				      mipi->lanes, pixel_bits),
		      MIPI_DPHY_RXPOS_LANE);
	isp_write_reg(0 << LANE0_SEL_OFFSET | 1 << LANE1_SEL_OFFSET |
		      2 << LANE2_SEL_OFFSET | 3 << LANE3_SEL_OFFSET,
		      MIPI_DPHY_LANE_SEL);
	if (info->info->type == RAW_SENSOR)
		isp_set_reg_bit(TRANS_MODE_SEL_OFFSET, MIPI_DPHY_LANE_CTRL);
	else
		isp_clr_reg_bit(TRANS_MODE_SEL_OFFSET, MIPI_DPHY_LANE_CTRL);
	isp_write_reg(info->size.w << FRAME_WIDTH_OFFSET |
		      info->size.h << FRAME_HEIGHT_OFFSET, MIPI_DPHY_FRM_SIZE);

	return mipi_config_hdr(isp_id, info);
}

static int isp_hw_mipi_start_transfer(uint32_t isp_id,
				      const struct isp_interface_info *info)
{
	int ret;

	ret = mipi_init(isp_id, info);
	if (ret)
		return ret;
	if (info->is_fpga) {
		ret = mipi_start_extern_aphy();
		if (ret)
			return ret;
	}

	isp_write_reg(0, MIPI_APHY_REG27);
	isp_write_reg(info->info->mipi.lanes, MIPI_DPHY_PWDB);
	isp_write_reg(info->info->mipi.lanes, MIPI_DPHY_LANE_EN);

	return RTS_ISP_OK;
}

static int isp_hw_mipi_stop_transfer(uint32_t isp_id,
				     const struct isp_interface_info *info)
{
	isp_write_reg(0, MIPI_DPHY_LANE_EN);
	isp_write_reg(0, MIPI_DPHY_PWDB);
	isp_write_reg(1, MIPI_APHY_REG27);

	isp_set_reg_bit(SRST_OFFSET, MIPI_DPHY_LANE_CTRL);
	isp_clr_reg_bit(SRST_OFFSET, MIPI_DPHY_LANE_CTRL);

	if (info->hdr.behavor != NONE_HDR) {
		isp_write_reg(0, FUSION_STREAM_EN);
		printf("FUSION_STREAM Disable\n\r");
	}

	if (info->is_fpga) {
		int ret;

		ret = mipi_stop_extern_aphy();
		if (ret)
			return ret;
	}

	return RTS_ISP_OK;
}

static const struct isp_hw_interface_ops hw_mipi_ops = {
	.start_transfer = isp_hw_mipi_start_transfer,
	.stop_transfer = isp_hw_mipi_stop_transfer,
};

const struct isp_hw_interface_ops *isp_hw_mipi_get_ops(void)
{
	return &hw_mipi_ops;
}
