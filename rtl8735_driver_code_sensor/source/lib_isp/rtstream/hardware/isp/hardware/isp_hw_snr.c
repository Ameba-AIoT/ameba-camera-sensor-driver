/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2021 Mike Wong <mike.wong@realtek.com>
 */

#include <stdlib.h>
#include <isp_utils.h>
#include <isp_hw_snr.h>
#include <isp_reg_snr.h>
//#include <isp_log.h>

#define SNR_RATIO_MAX 511
#define LSB_r_slope 64

static int isp_hw_snr_enable(uint32_t isp_id, int enable)
{
	if (enable)
		isp_write_reg_mask(1<<GE_EN_OFFSET |
						   1<<SHARPEN_EN_OFFSET |
						   1<<NR_EN_OFFSET |
						   1<<DPC_SRD_SEL_OFFSET |
						   1<<DP_RP_EN_OFFSET |
						   0x4<<DP_THD_D1_OFFSET, SNR_CTRL,
						   GE_EN_MASK & SHARPEN_EN_MASK & NR_EN_MASK & DPC_SRD_SEL_MASK &
						   DP_RP_EN_MASK &  DP_THD_D1_MASK);
	else
		isp_write_reg_mask(1<<GE_EN_OFFSET |
						   1<<SHARPEN_EN_OFFSET |
						   0<<NR_EN_OFFSET |
						   1<<DPC_SRD_SEL_OFFSET |
						   1<<DP_RP_EN_OFFSET |
						   0x4<<DP_THD_D1_OFFSET, SNR_CTRL,
						   GE_EN_MASK & SHARPEN_EN_MASK & NR_EN_MASK & DPC_SRD_SEL_MASK &
						   DP_RP_EN_MASK &  DP_THD_D1_MASK);

	return RTS_ISP_OK;
}

static void isp_hw_snr_slope(uint32_t isp_id)
{
	uint16_t rmix_int, thd1_int, thd0_int;
	uint32_t r_slope_int;

	rmix_int = isp_read_reg(SNR_NR_RMIN_THD) >> nr_rmin_OFFSET;
	thd1_int = isp_read_reg(SNR_NR_RMIN_THD);
	thd1_int = (thd1_int & nr_thd1_MASK) >> nr_thd1_OFFSET;
	thd0_int = isp_read_reg(SNR_NR_RMIN_THD) & nr_thd0_MASK;

	if (thd1_int <= thd0_int)
		thd1_int = thd0_int + 1;

	r_slope_int = (uint32_t)(((float)(256.0-rmix_int) / (float)(thd1_int - thd0_int) * (float)LSB_r_slope) + 0.5);

	// nr_g_clip_delta_tmp | r_slope_int
	r_slope_int = isp_read_reg(SNR_NR_R_SLOPE_G_CLIP_DELTA) | r_slope_int;

	isp_write_reg(r_slope_int, SNR_NR_R_SLOPE_G_CLIP_DELTA);
}

static void isp_hw_snr_sharp_slope(uint32_t isp_id)
{
	uint16_t sh_delta_rmax, sh_thd1_int, sh_thd0_int;
	uint32_t sh_r_slope_int;

	sh_delta_rmax = isp_read_reg(SNR_SHARP_RMAX_THD) >> SH_DELTA_RMAX_OFFSET;
	sh_thd1_int = isp_read_reg(SNR_SHARP_RMAX_THD);
	sh_thd1_int = (sh_thd1_int & SH_THD1_MASK) >> SH_THD1_OFFSET;
	sh_thd0_int = isp_read_reg(SNR_SHARP_RMAX_THD) & SH_THD0_MASK;

	if (sh_thd1_int <= sh_thd0_int)
		sh_thd1_int = sh_thd0_int + 1;

	sh_r_slope_int = (uint32_t)(((float)sh_delta_rmax / (float)(sh_thd1_int - sh_thd0_int) * (float)LSB_r_slope) + 0.5);

	isp_write_reg(sh_r_slope_int, SNR_SHARP_DRAW_R_SLOPE);
}

static int isp_hw_snr_est(uint32_t isp_id)
{
	isp_hw_snr_slope(isp_id);
	isp_hw_snr_sharp_slope(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_snr_set(uint32_t isp_id, const isp_iq_snr_item_t *snr)
{
	int snr_ratio;

	if (!snr)
		return -RTS_ISP_EINVAL;

	snr_ratio = min(snr->ratio, SNR_RATIO_MAX);

	isp_write_reg(snr->offset << BASECURVE_OFFSET_OFFSET |
		      snr_ratio << BASECURVE_RATIO_OFFSET,
			  SNR_NR_BASE_CURVE_RATIO_OFFSET);

	return RTS_ISP_OK;
}

static const struct isp_hw_snr_ops hw_snr_ops = {
	.enable = isp_hw_snr_enable,
	.estimation = isp_hw_snr_est,
	.set = isp_hw_snr_set,
};

const struct isp_hw_snr_ops *isp_hw_snr_get_ops(void)
{
	return &hw_snr_ops;
}
