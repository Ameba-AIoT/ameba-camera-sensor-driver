/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_eeh.h>
#include <isp_reg_virtual.h>
#include <isp_reg_eeh.h>

static float m_suppress;

static void isp_hw_eeh_nr_rate_slope(uint32_t isp_id)
{
	uint8_t nr_rate0, nr_rate1;
	uint16_t nr_th0, nr_th1, nr_dis_th0, nr_dis_th1;
	uint16_t nr_slope;
	uint32_t nr_rate_x_slope, nr_dis_slope;

	nr_th0 = isp_read_reg(EEH_NR_THD0);
	nr_th1 = isp_read_reg(EEH_NR_THD1);
	nr_rate0 = isp_read_reg(EEH_NR_RATE0);
	nr_rate1 = isp_read_reg(EEH_NR_RATE1);
	nr_dis_th0 = isp_read_reg(EEH_NR_DIS_THD0);
	nr_dis_th1 = isp_read_reg(EEH_NR_DIS_THD1);

	if (nr_th1 <= nr_th0)
		nr_th1 = nr_th0 + 1;
	nr_slope = clamp_t(uint16_t, (1024.0 / (nr_th1 - nr_th0) + 0.5),
			   0, 1023);
	nr_rate_x_slope = clamp_t(uint32_t, ((nr_rate0 - nr_rate1) * 1024.0 /
				  (nr_th1 - nr_th0) + 0.5), 0, 65536);
	if (nr_dis_th1 <= nr_dis_th0)
		nr_dis_th1 = nr_dis_th0 + 1;
	nr_dis_slope = clamp_t(uint32_t, (4096.0 / (nr_dis_th1 - nr_dis_th0) +
			       0.5), 0, 65536);

	isp_write_reg(nr_slope, EEH_NR_SLOPE);
	isp_write_reg(nr_rate_x_slope, EEH_NR_RATE_SLOPE);
	isp_write_reg(nr_dis_slope, EEH_NR_DIS_SLOPE);
}

static void isp_hw_eeh_sharp_thd_offset(uint32_t isp_id)
{
	uint16_t sh_thd0_offset, sh_rate0, sh_rate1;
	uint16_t sh_dis_th0, sh_dis_th1;
	uint16_t sh_rate_slope;
	uint32_t sh_rate_x_slope, sh_dis_slope;

	sh_thd0_offset = isp_read_reg(EEH_SH_THD_OFFSET);
	sh_rate0 = isp_read_reg(EEH_SH_RATE0);
	sh_rate1 = isp_read_reg(EEH_SH_RATE1);
	sh_dis_th0 = isp_read_reg(EEH_SH_DIS_THD0);
	sh_dis_th1 = isp_read_reg(EEH_SH_DIS_THD1);

	sh_rate_slope = clamp_t(uint16_t, (2048.0 / sh_thd0_offset + 0.5),
				0, 2047);
	sh_rate_x_slope = clamp_t(uint32_t, ((sh_rate1 - sh_rate0) * 2048.0 /
				  sh_thd0_offset + 0.5), 0, ((1 << 21) - 1));
	if (sh_dis_th1 <= sh_dis_th0)
		sh_dis_th1 = sh_dis_th0 + 1;
	sh_dis_slope = clamp_t(uint32_t, (4096.0 / (sh_dis_th1 - sh_dis_th0) +
			       0.5), 0, 4095);

	isp_write_reg(sh_rate_slope, EEH_SH_RATE_SLOPE);
	isp_write_reg(sh_rate_x_slope, EEH_SH_RATE_X_SLOPE);
	isp_write_reg(sh_dis_slope, EEH_SH_DIS_SLOPE);
}

static void isp_hw_eeh_overshoot_undershoot(uint32_t isp_id)
{
	uint16_t y_sharp_rate1;
	uint16_t y_m_turn, y_inv_suppress, inv_y_sharp_rate1;
	float m_sharpen, m_turn;

	y_sharp_rate1 = isp_read_reg(EEH_SH_RATE1);
	m_sharpen = 1.0 + y_sharp_rate1 / 64.0;

	if (m_sharpen <= m_suppress)
		m_sharpen = m_suppress + 1;

	m_turn = m_sharpen * (1.0 - m_suppress) / (m_sharpen - m_suppress);

	y_m_turn = clamp_t(uint16_t, (m_turn * 64 + 0.5), 0, 63);
	y_inv_suppress = clamp_t(uint16_t, (m_suppress * 32768 / m_sharpen +
				 0.5), 0, 32767);
	inv_y_sharp_rate1 = clamp_t(uint16_t, (512 / m_sharpen + 0.5),
				    0, 32767);

	isp_write_reg(y_m_turn, EEH_M_TURN);
	isp_write_reg(y_inv_suppress, EEH_Y_INV_SUPPRESS);
	isp_write_reg(inv_y_sharp_rate1, EEH_INV_SHARP_RATE);
}

static int isp_hw_eeh_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(0xCC, VEEH_M_SUPPRESS);
	isp_write_vreg(0xA0, VEEH_SH_RATE0);
	isp_write_vreg(0x100, VEEH_SH_RATE1);
	isp_write_vreg(SHARPNESS_CTRL_DEF, VSHARPNESS);

	return RTS_ISP_OK;
}

static int isp_hw_eeh_est(uint32_t isp_id)
{
	isp_hw_eeh_nr_rate_slope(isp_id);
	isp_hw_eeh_sharp_thd_offset(isp_id);
	isp_hw_eeh_overshoot_undershoot(isp_id);

	return RTS_ISP_OK;
}

static int isp_hw_eeh_set_sharpness(uint32_t isp_id, int sharpness)
{
	float suppress = isp_read_vreg(VEEH_M_SUPPRESS) / 1024.0f;
	const int val_def = isp_read_vreg(VSHARPNESS);
	int rate0 = isp_read_vreg(VEEH_SH_RATE0);
	int rate1 = isp_read_vreg(VEEH_SH_RATE1);

	if (sharpness < SHARPNESS_CTRL_DEF)
		sharpness = linear_intp(sharpness,
					SHARPNESS_CTRL_MIN, SHARPNESS_CTRL_MIN,
					SHARPNESS_CTRL_DEF, val_def);
	else
		sharpness = linear_intp(sharpness,
					SHARPNESS_CTRL_DEF, val_def,
					SHARPNESS_CTRL_MAX, SHARPNESS_CTRL_MAX);

	if (sharpness < 50) {
		m_suppress = linear_intp_float(sharpness, SHARPNESS_CTRL_MIN, 1,
					       SHARPNESS_CTRL_DEF, suppress);
		isp_write_reg(linear_intp(sharpness, SHARPNESS_CTRL_MIN, 0,
					  SHARPNESS_CTRL_DEF, rate0),
			      EEH_SH_RATE0);
		isp_write_reg(linear_intp(sharpness, SHARPNESS_CTRL_MIN, 0,
					  SHARPNESS_CTRL_DEF, rate1),
			      EEH_SH_RATE1);
	} else {
		m_suppress = linear_intp_float(sharpness, 50, suppress, 100, 0);
		isp_write_reg(linear_intp(sharpness, SHARPNESS_CTRL_DEF, rate0,
					  SHARPNESS_CTRL_MAX, 0x200),
			      EEH_SH_RATE0);
		isp_write_reg(linear_intp(sharpness, SHARPNESS_CTRL_DEF, rate1,
					  SHARPNESS_CTRL_MAX, 0x200),
			      EEH_SH_RATE1);
	}
	return RTS_ISP_OK;
}

static const struct isp_hw_eeh_ops hw_eeh_ops = {
	.init_vreg = isp_hw_eeh_init_vreg,
	.estimation = isp_hw_eeh_est,
	.set_sharpness = isp_hw_eeh_set_sharpness,
};

const struct isp_hw_eeh_ops *isp_hw_eeh_get_ops(void)
{
	return &hw_eeh_ops;
}
