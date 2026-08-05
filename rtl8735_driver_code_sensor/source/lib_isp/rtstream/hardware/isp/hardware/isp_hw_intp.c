/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */

#include <stdlib.h>
#include <math.h>
#include <isp_utils.h>
#include <isp_driver.h>
#include <isp_hw_intp.h>
#include <isp_reg_virtual.h>
#include <isp_reg_sys.h>
#include <isp_reg_intp.h>

static void isp_hw_intp_set_moire_rate(uint32_t isp_id)
{
	uint8_t moire_r_rate, moire_b_rate;
	uint16_t moire_r_num, moire_g_num, moire_b_num;
	uint32_t moire_r_sum, moire_g_sum, moire_b_sum;
	float r_ratio, g_ratio, b_ratio;

	moire_r_num = isp_read_reg(INTP_MOIRE_NUM_R);
	moire_g_num = isp_read_reg(INTP_MOIRE_NUM_G);
	moire_b_num = isp_read_reg(INTP_MOIRE_NUM_B);
	moire_r_sum = isp_read_reg(INTP_MOIRE_SUM_R);
	moire_g_sum = isp_read_reg(INTP_MOIRE_SUM_G);
	moire_b_sum = isp_read_reg(INTP_MOIRE_SUM_B);

	if (moire_r_num != 0)
		r_ratio = (float)moire_r_sum / moire_r_num;
	else
		r_ratio = 0;
	if (moire_g_num != 0)
		g_ratio = (float)moire_g_sum / moire_g_num;
	else
		g_ratio = 0;
	if (moire_b_num != 0)
		b_ratio = (float)moire_b_sum / moire_b_num;
	else
		b_ratio = 0;

	if (g_ratio != 0) {
		moire_r_rate = (uint8_t)128 * r_ratio / g_ratio;
		moire_b_rate = (uint8_t)128 * b_ratio / g_ratio;
	} else {
		moire_r_rate = 0;
		moire_b_rate = 0;
	}

	isp_write_reg_mask(moire_r_rate << MOIRE_R_RATE_OFFSET |
			   moire_b_rate << MOIRE_B_RATE_OFFSET,
			   INTP_MOIRE_RGB,
			   MOIRE_R_RATE_MASK | MOIRE_B_RATE_MASK);
}

static void isp_hw_intp_set_loc_rate(uint32_t isp_id)
{
	uint32_t loc_max;
	uint16_t dist_e, dist_s, loc_rate;

	dist_e = isp_read_reg(SYS_DIST_E);
	dist_s = isp_read_reg(SYS_DIST_S);
	loc_max = isp_read_reg(INTP_EDGE_SMOOTH_ILOC_MAX);

	if (dist_e > dist_s)
		loc_rate = (loc_max << 14) / (dist_e - dist_s);
	else
		loc_rate = 0;

	isp_write_reg_mask(loc_rate << LOC_RATE_OFFSET,
			   INTP_EDGE_SMOOTH_ILOC, LOC_RATE_MASK);
}

static void isp_hw_intp_alpha_blending(uint32_t isp_id, float awb_g_gain,
				      float ae_gain, float sensor_gain)
{
	int i;
	uint32_t edge_thd0;
	uint32_t edge_thd1;
	uint32_t edge_thd0_pts;
	uint32_t edge_thd1_pts;
	uint32_t edge_slope;
	float noise_deviation;
	float noise_c_real;
	float sensor_gain_bound[9] = {1, 2, 4, 6, 8, 10, 12, 14, 16};

	edge_thd0 = isp_read_vreg(VINTP_ALPHA_BLEND_EDGE_THD0);
	edge_thd1 = isp_read_vreg(VINTP_ALPHA_BLEND_EDGE_THD1);

	for (i = 0; i < 9; i++)
		if (sensor_gain <= sensor_gain_bound[i])
			break;

	if (i == 0) {
		noise_c_real = isp_read_vreg_float(VINTP_NOISE_COFF0);
	} else if (i == 9) {
		noise_c_real = isp_read_vreg_float(VINTP_NOISE_COFF0 + 8 * 4);
	} else {
		float gain0;
		float gain1;
		float noise_c0;
		float noise_c1;

		gain0 = sensor_gain_bound[i - 1];
		gain1 = sensor_gain_bound[i];
		noise_c0 = isp_read_vreg_float(VINTP_NOISE_COFF0 + (i - 1) * 4);
		noise_c1 = isp_read_vreg_float(VINTP_NOISE_COFF0 + i * 4);
		noise_c_real = linear_intp_float(sensor_gain, gain0, noise_c0,
						 gain1, noise_c1);
	}

	noise_deviation = sqrt(awb_g_gain * ae_gain) * noise_c_real / 2;
	edge_thd0_pts = clamp_t(uint32_t, edge_thd0 * noise_deviation,
				0, 131071);
	edge_thd1_pts = clamp_t(uint32_t, edge_thd1 * noise_deviation,
				0, 131071);

	if (edge_thd1_pts <= edge_thd0_pts)
		edge_thd1_pts = edge_thd0_pts + 1;

	edge_slope = 8192 * 256 / (edge_thd1_pts - edge_thd0_pts);

	isp_write_reg(edge_thd0_pts, INTP_EDGE_RATE_THD0);
	isp_write_reg(edge_thd1_pts, INTP_EDGE_RATE_THD1);
	isp_write_reg(edge_slope, INTP_EDGE_SLOPE);

	isp_write_reg(1, INTP_SYNC);
}

static int isp_hw_intp_set_frame_size(uint32_t isp_id,
				      const rts_isp_size_t *size)
{
	uint32_t pixels = size->w * size->h;

	isp_write_reg(pixels, DRC_FRAME_SIZE);

	return RTS_ISP_OK;
}

static int isp_hw_intp_set_drc_blending_manual_rate(uint32_t isp_id,
	enum rts_isp_drc_mode drc_mode, uint8_t* drc_blending_rate)
{
	int rate;
	int rate_diff;
	int drc_auto_disable, drc_rate_config;
	static int rate_diff_cnt;
	static int rate_last = 15;
	uint16_t low_bound;
	uint16_t drc_feature;
	struct rts_isp_sync_regs regs = {};

	drc_auto_disable = isp_read_vreg(VDRC_AUTO_DISABLE);
	drc_rate_config = isp_read_vreg(VDRC_RATE_CONFIG);
	rate = drc_rate_config;
	if (drc_auto_disable)
		goto out;

	if (drc_mode == RTS_ISP_DRC_MODE_MANUAL) {
		rate = *drc_blending_rate;
		goto set_reg;
	}

	drc_feature = isp_read_reg(DRC_VAR);
	low_bound = isp_read_reg(DRC_ORG_BLENDING_VALUE0);
	rate += linear_intp_bound(drc_feature, low_bound, 0,
				  low_bound + 1024, 15);

	rate_diff = rate - rate_last;
	if (rate_diff > 0 && rate_diff_cnt >= 0)
		rate_diff_cnt += min(rate_diff, 3);
	else if (rate_diff < 0 && rate_diff_cnt <= 0)
		rate_diff_cnt += max(rate_diff, -3);
	else
		rate_diff_cnt = 0;

	if (abs(rate_diff_cnt) < 15)
		return RTS_ISP_OK;
out:
	rate = clamp(clamp(rate, rate_last - 1, rate_last + 1), 0, 15);
	if (rate == rate_last)
		return RTS_ISP_OK;

set_reg:
	regs.reg[0].info.delay_frames = 0;
	regs.reg[0].info.type = RTS_ISP_SYNC_REG_TYPE_REG;
	regs.reg[0].info.interrupt = RTS_ISP_INT_FRAME_END;
	regs.reg[0].reg.addr = (DRC_ORG_BLENDING_VALUE1);
	regs.reg[0].reg.data = rate;
	regs.num = 1;
	rate_last = rate;

	if (drc_mode == RTS_ISP_DRC_MODE_AUTO) {
		*drc_blending_rate = rate;
	}

	return isp_driver_write_sync_regs(&regs);
}

static int isp_hw_intp_est(uint32_t isp_id,
	enum rts_isp_drc_mode drc_mode, uint8_t* drc_blending_rate)
{
	isp_hw_intp_set_moire_rate(isp_id);
	isp_hw_intp_set_loc_rate(isp_id);

	return isp_hw_intp_set_drc_blending_manual_rate(isp_id,
		drc_mode, drc_blending_rate);
}

static int isp_hw_intp_dyn(uint32_t isp_id, float awb_g_gain,
			   float ae_gain, float sensor_gain)
{
	isp_hw_intp_alpha_blending(isp_id, awb_g_gain, ae_gain, sensor_gain);

	return RTS_ISP_OK;
}

static const struct isp_hw_intp_ops hw_intp_ops = {
	.set_frame_size = isp_hw_intp_set_frame_size,
	.estimation = isp_hw_intp_est,
	.dynamic = isp_hw_intp_dyn,
};

const struct isp_hw_intp_ops *isp_hw_intp_get_ops(void)
{
	return &hw_intp_ops;
}
