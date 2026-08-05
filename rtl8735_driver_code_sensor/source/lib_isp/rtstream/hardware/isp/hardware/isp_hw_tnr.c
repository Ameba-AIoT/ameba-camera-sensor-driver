/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdlib.h>
#include <isp_utils.h>
#include <isp_hw_tnr.h>
#include <isp_reg_tnr.h>
#include <isp_reg_sys.h>
#include "hal_isp.h"

#define IDLE_VAL 0x1DF

static int isp_hw_tnr_set_ddr(uint32_t isp_id, uint32_t addr, uint32_t len,
			      int bit)
{
	isp_write_reg(addr, TNR_STREAM_FRAME_ADDR);
	isp_write_reg(len, TNR_STREAM_DDR_LEN);
	// isp_write_reg(1, TNR_STREAM_EN);
	isp_set_reg_bit(DATA_REQ_EN_TPNR_OFFSET, TNR_STREAM_CTRL);
	if (bit < 12) {
		isp_write_reg(0xF, TNR_COMPR_CTRL);
		isp_set_reg_bit(GE_CUR_ONLY_EN_OFFSET, TNR_GE_CTRL);
	} else {
		isp_write_reg(0, TNR_COMPR_CTRL);
		isp_clr_reg_bit(GE_CUR_ONLY_EN_OFFSET, TNR_GE_CTRL);
	}

	return RTS_ISP_OK;
}

static int isp_hw_tnr_enable_axi(uint32_t isp_id, int enable)
{
	u32 sys_idle_val = 0;

	if (enable) {
		isp_write_reg(TPNR_EN_MASK, TNR_STREAM_EN);
	} else {

		isp_clr_reg_bit(TPNR_EN_OFFSET, TNR_STREAM_EN);
		sys_idle_val = (isp_read_reg(SYS_FRAME_IDLE) & IDLE_VAL == IDLE_VAL) ? 1 : 0;
		if ( !hal_isp_is_verify_path_on() || sys_idle_val == 0 ) {

			if ( hal_isp_is_verify_path_on() )
				printf("streaming when verify path disable tnr\n");

			udelay(10000);  // need to confirm
		}
	}

	return RTS_ISP_OK;
}

static int isp_hw_tnr_enable(uint32_t isp_id, int enable)
{
	if (enable) {
		if (!hal_isp_is_verify_path_on())
			isp_write_reg_mask(0x4F, TNR_CTRL, 0x6F);
		else
			isp_write_reg_mask(0x0F, TNR_CTRL, 0x6F);
	}
	else
		isp_write_reg_mask(0xE, TNR_CTRL, 0x6F);

	return RTS_ISP_OK;
}

static void isp_hw_tnr_total_gain(uint32_t isp_id, float sensor_gain)
{
	uint16_t total_gain;
	float sensor_total_gain;

	sensor_total_gain = min(sensor_gain, 16.0f);
	total_gain = clamp_t(uint16_t, (sensor_total_gain * 16 + 0.5), 0, 256);

	isp_write_reg(total_gain, TNR_TOTAL_GAIN);
}

static void isp_hw_tnr_scence_change_diff(uint32_t isp_id)
{
	uint16_t lp_y_th0, lp_y_th1, lp_rb_th0, lp_rb_th1;
	uint16_t lp_g_th0, lp_g_th1, hp_g_th0, hp_g_th1;
	uint32_t lp_y_m, lp_rb_m, lp_g_m, hp_g_m;

	lp_y_th0 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_Y_TH0);
	lp_y_th1 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_Y_TH1);
	lp_rb_th0 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_RB_TH0);
	lp_rb_th1 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_RB_TH1);
	lp_g_th0 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_G_TH0);
	lp_g_th1 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_LP_G_TH1);
	hp_g_th0 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_HP_G_TH0);
	hp_g_th1 = isp_read_reg(TNR_SCENCE_CHANGE_DIFF_HP_G_TH1);

	if (lp_y_th1 <= lp_y_th0)
		lp_y_th1 = lp_y_th0 + 1;
	lp_y_m = (uint32_t)((1.0 / ((lp_y_th1 - lp_y_th0) / 1024.0)) *
			    1024.0 + 0.5);
	if (lp_rb_th1 <= lp_rb_th0)
		lp_rb_th1 = lp_rb_th0 + 1;
	lp_rb_m = (uint32_t)((1.0 / ((lp_rb_th1 - lp_rb_th0) / 1024.0)) *
			    1024.0 + 0.5);
	if (lp_g_th1 <= lp_g_th0)
		lp_g_th1 = lp_g_th0 + 1;
	lp_g_m = (uint32_t)((1.0 / ((lp_g_th1 - lp_g_th0) / 1024.0)) *
			    1024.0 + 0.5);
	if (hp_g_th1 <= hp_g_th0)
		hp_g_th1 = hp_g_th0 + 1;
	hp_g_m = (uint32_t)((1.0 / ((hp_g_th1 - hp_g_th0) / 1024.0)) *
			    1024.0 + 0.5);

	isp_write_reg(lp_y_m, TNR_SCENCE_CHANGE_DIFF_LP_Y_M);
	isp_write_reg(lp_rb_m, TNR_SCENCE_CHANGE_DIFF_LP_RB_M);
	isp_write_reg(lp_g_m, TNR_SCENCE_CHANGE_DIFF_LP_G_M);
	isp_write_reg(hp_g_m, TNR_SCENCE_CHANGE_DIFF_HP_G_M);
}

static void isp_hw_tnr_weight_slope(uint32_t isp_id)
{
	uint16_t cmpdiff_lp_th0, cmpdiff_lp_th1;
	uint16_t cmpdiff_hp_th0, cmpdiff_hp_th1;
	uint16_t w_slope_lp, w_slope_hp;

	cmpdiff_lp_th0 = isp_read_reg(TNR_CMPDIFF_LP_TH0);
	cmpdiff_lp_th1 = isp_read_reg(TNR_CMPDIFF_LP_TH1);
	cmpdiff_hp_th0 = isp_read_reg(TNR_CMPDIFF_HP_TH0);
	cmpdiff_hp_th1 = isp_read_reg(TNR_CMPDIFF_HP_TH1);

	if (cmpdiff_lp_th1 <= cmpdiff_lp_th0)
		cmpdiff_lp_th1 = cmpdiff_lp_th0 + 1;
	w_slope_lp = (uint16_t)((64.0 / (cmpdiff_lp_th1 - cmpdiff_lp_th0)) *
				64.0 + 0.5);
	if (cmpdiff_hp_th1 <= cmpdiff_hp_th0)
		cmpdiff_hp_th1 = cmpdiff_hp_th0 + 1;
	w_slope_hp = (uint16_t)((64.0 / (cmpdiff_hp_th1 - cmpdiff_hp_th0)) *
				64.0 + 0.5);

	isp_write_reg(w_slope_hp, TNR_WEIGHT_SLOPE_HP);
	isp_write_reg(w_slope_lp, TNR_WEIGHT_SLOPE_LP);
}

static void isp_hw_tnr_scene_details_m(uint32_t isp_id)
{
	uint16_t alpha_y0, alpha_y1;
	uint16_t alpha_y2, alpha_y3;
	uint16_t th0, th1;
	uint16_t th2, th3;
	uint32_t m01;
	int m12, m23;

	alpha_y0 = isp_read_reg(TNR_SCENCE_DETAILS_Y0);
	alpha_y1 = isp_read_reg(TNR_SCENCE_DETAILS_Y1);
	alpha_y2 = isp_read_reg(TNR_SCENCE_DETAILS_Y2);
	alpha_y3 = isp_read_reg(TNR_SCENCE_DETAILS_Y3);
	th0 = isp_read_reg(TNR_SCENCE_DETAILS_TH0);
	th1 = isp_read_reg(TNR_SCENCE_DETAILS_TH1);
	th2 = isp_read_reg(TNR_SCENCE_DETAILS_TH2);
	th3 = isp_read_reg(TNR_SCENCE_DETAILS_TH3);

	if (th1 == th0) {
		m01 = 0;
	} else {
		m01 = (uint32_t)((((alpha_y1 - alpha_y0) / 256.0) /
				 ((th1 - th0) / 64.0)) * 8192 + 0.5);
	}

	if (th2 == th1) {
		m12 = 0;
	} else if ((alpha_y2 - alpha_y1) >= 0) {
		m12 = (int)((((alpha_y2 - alpha_y1) / 256.0) /
			     ((th2 - th1) / 64.0)) * 8192.0 + 0.5);
	} else {
		m12 = -1 * (int)((((abs(alpha_y2 - alpha_y1)) / 256.0) /
				((th2 - th1) / 64.0)) * 8192.0 + 0.5);
	}

	if (th3 == th2) {
		m23 = 0;
	} else if ((alpha_y3 - alpha_y2) >= 0) {
		m23 = (int)((((alpha_y3 - alpha_y2) / 256.0) /
			     ((th3 - th2) / 64.0)) * 8192.0 + 0.5);
	} else {
		m23 = -1 * (int)((((abs(alpha_y3 - alpha_y2)) / 256.0) /
				((th3 - th2) / 64.0)) * 8192.0 + 0.5);
	}

	isp_write_reg(m01, TNR_SCENCE_DETAILS_M01); // unsigned
	isp_write_reg(m12, TNR_SCENCE_DETAILS_M12); // signed
	isp_write_reg(m23, TNR_SCENCE_DETAILS_M23); // signed
}

static void isp_hw_tnr_ge_edge_detection_m(uint32_t isp_id)
{
	uint16_t th0, th1;
	uint16_t m;

	th0 = isp_read_reg(TNR_GE_EDGE_DETECTION_TH0);
	th1 = isp_read_reg(TNR_GE_EDGE_DETECTION_TH1);

	if (th1 <= th0)
		th1 = th0 + 1;
	m = (uint16_t)((1.0 / ((th1 - th0) / 64.0)) * 256.0 + 0.5);

	isp_write_reg(m, TNR_GE_EDGE_DETECTION_M);
}

static void isp_hw_tnr_ge_loc_rate(uint32_t isp_id)
{
	uint16_t ge_loc_th, ge_loc_d0, ge_loc_d1;
	uint32_t ge_loc_rate;

	ge_loc_th = isp_read_reg(TNR_GE_LOC_TH);
	ge_loc_d0 = isp_read_reg(TNR_GE_LOC_D0);
	ge_loc_d1 = isp_read_reg(TNR_GE_LOC_D1);

	if (ge_loc_d1 <= ge_loc_d0)
		ge_loc_d1 = ge_loc_d0 + 1;
	ge_loc_rate = (uint32_t)(((ge_loc_th / 64.0) /
				 (ge_loc_d1 - ge_loc_d0)) * 262144.0 + 0.5);

	isp_write_reg(ge_loc_rate, TNR_GE_LOC_RATE);
}

static int isp_hw_tnr_est(uint32_t isp_id)
{
	isp_hw_tnr_scence_change_diff(isp_id);
	isp_hw_tnr_weight_slope(isp_id);
	isp_hw_tnr_scene_details_m(isp_id);
	isp_hw_tnr_ge_edge_detection_m(isp_id);
	isp_hw_tnr_ge_loc_rate(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_tnr_dyn(uint32_t isp_id, float sensor_gain)
{
	isp_hw_tnr_total_gain(isp_id, sensor_gain);

	return RTS_ISP_OK;
}

static const struct isp_hw_tnr_ops hw_tnr_ops = {
	.set_ddr = isp_hw_tnr_set_ddr,
	.enable = isp_hw_tnr_enable,
	.enable_axi = isp_hw_tnr_enable_axi,
	.estimation = isp_hw_tnr_est,
	.dynamic = isp_hw_tnr_dyn,
};

const struct isp_hw_tnr_ops *isp_hw_tnr_get_ops(void)
{
	return &hw_tnr_ops;
}
