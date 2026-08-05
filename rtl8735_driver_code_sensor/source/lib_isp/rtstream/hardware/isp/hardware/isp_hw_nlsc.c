/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <math.h>
#include <isp_hw_nlsc.h>
#include <isp_reg_nlsc.h>

#define NLSC_CURVE_COUNT 32

static inline int get_step_reg_value(uint32_t step)
{
	switch (step) {
	case 32:
		return 0;
	case 64:
		return 1;
	case 128:
		return 2;
	default:
		return 0;
	}
}

static int hw_set_nlsc_curve(uint32_t isp_id,
			     const isp_iq_nlsc_common_t *nlsc)
{
	int i;

	if (nlsc->r_curve_count != NLSC_CURVE_COUNT ||
	    nlsc->g_curve_count != NLSC_CURVE_COUNT ||
	    nlsc->b_curve_count != NLSC_CURVE_COUNT)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < nlsc->r_curve_count; i += 2) {
		isp_write_reg(nlsc->r_curve[i] << SHADE_R_P0_OFFSET |
			      nlsc->r_curve[i + 1] << SHADE_R_P1_OFFSET,
			      NLSC_CURVE_R_P0_P1 + i * 2);
		isp_write_reg(nlsc->g_curve[i] << SHADE_G_P0_OFFSET |
			      nlsc->g_curve[i + 1] << SHADE_G_P1_OFFSET,
			      NLSC_CURVE_G_P0_P1 + i * 2);
		isp_write_reg(nlsc->b_curve[i] << SHADE_B_P0_OFFSET |
			      nlsc->b_curve[i + 1] << SHADE_B_P1_OFFSET,
			      NLSC_CURVE_B_P0_P1 + i * 2);
	}
	isp_write_reg(get_step_reg_value(nlsc->step) << LENS_MODE_OFFSET |
		      1 << ADJRATE_R_EN_OFFSET |
		      1 << ADJRATE_G_EN_OFFSET |
		      1 << ADJRATE_B_EN_OFFSET, NLSC_MODE);
	return RTS_ISP_OK;
}

int hw_set_nlsc_center_type(uint32_t isp_id,
			    uint16_t center_x, uint16_t center_y, uint8_t type)
{
	uint32_t neg_distance2;
	uint32_t real_distance2;
	uint16_t distance;
	int16_t diff;

	real_distance2 = (uint32_t)center_x * center_x + center_y * center_y;
	distance = (uint16_t)sqrt(real_distance2);
	neg_distance2 = (uint32_t)distance * distance;
	diff = (int16_t)((int32_t)neg_distance2 - real_distance2);

	switch (type) {
	case 0:
		isp_write_reg((center_x << LENS_CENTER_X_R_OFFSET |
			       center_y << LENS_CENTER_Y_R_OFFSET),
			      NLSC_CENTER_R);
		isp_write_reg((distance << LENS_FS_DST_R_OFFSET |
			       diff << LENS_FS_ERR_R_OFFSET),
			      NLSC_DISTANCE_CFG_R);
		break;
	case 1:
		isp_write_reg((center_x << LENS_CENTER_X_G_OFFSET |
			       center_y << LENS_CENTER_Y_G_OFFSET),
			      NLSC_CENTER_G);
		isp_write_reg((distance << LENS_FS_DST_G_OFFSET |
			       diff << LENS_FS_ERR_G_OFFSET),
			      NLSC_DISTANCE_CFG_G);
		break;
	case 2:
		isp_write_reg((center_x << LENS_CENTER_X_B_OFFSET |
			       center_y << LENS_CENTER_Y_B_OFFSET),
			      NLSC_CENTER_B);
		isp_write_reg((distance << LENS_FS_DST_B_OFFSET |
			       diff << LENS_FS_ERR_B_OFFSET),
			      NLSC_DISTANCE_CFG_B);
		break;
	}

	return RTS_ISP_OK;
}

static int hw_set_nlsc_load(uint32_t isp_id)
{
	isp_write_reg(1 << NLSC_STEP_R_OFFSET |
		      1 << NLSC_STEP_G_OFFSET |
		      1 << NLSC_STEP_B_OFFSET, NLSC_GAIN_STEP);
	isp_write_reg(0x20 << ADJRATE_R_OFFSET |
		      0x20 << ADJRATE_G_OFFSET |
		      0x20 << ADJRATE_B_OFFSET, NLSC_ADJ_RATE);
	isp_write_reg(NLSC_ADJ_TRIG_MASK | 0 << NLSC_ADJ_MODE_OFFSET,
		      NLSC_GAIN_CTRL);

	return RTS_ISP_OK;
}

static int isp_hw_set_nlsc(uint32_t isp_id,
			   const isp_iq_nlsc_common_t *nlsc)
{
	int ret;

	if (!nlsc)
		return -RTS_ISP_EINVAL;
	ret = hw_set_nlsc_curve(isp_id, nlsc);
	if (ret)
		return ret;
	ret = hw_set_nlsc_load(isp_id);
	if (ret)
		return ret;
	return RTS_ISP_OK;
}

int isp_hw_nlsc_set_center(uint32_t isp_id,
				  const struct isp_hw_nlsc_center *center)
{
	hw_set_nlsc_center_type(isp_id, center->r.x, center->r.y, 0);
	hw_set_nlsc_center_type(isp_id, center->g.x, center->g.y, 1);
	hw_set_nlsc_center_type(isp_id, center->b.x, center->b.y, 2);
	isp_write_reg(1, NLSC_CENTER_RGB_CTRL);

	return RTS_ISP_OK;
}

static int isp_hw_set_adj(uint32_t isp_id,
			  const isp_iq_nlsc_adj_t *adj)
{
	if (!adj)
		return -RTS_ISP_EINVAL;
	isp_write_reg(adj->r << ADJRATE_R_OFFSET |
		      adj->g << ADJRATE_G_OFFSET |
		      adj->b << ADJRATE_B_OFFSET, NLSC_ADJ_RATE);
	isp_write_reg(NLSC_ADJ_TRIG_MASK | 1 << NLSC_ADJ_MODE_OFFSET,
		      NLSC_GAIN_CTRL);
	return RTS_ISP_OK;
}

static const struct isp_hw_nlsc_ops hw_nlsc_ops = {
	.set_nlsc = isp_hw_set_nlsc,
	.set_center = isp_hw_nlsc_set_center,
	.set_adj = isp_hw_set_adj,
};

const struct isp_hw_nlsc_ops *isp_hw_nlsc_get_ops(void)
{
	return &hw_nlsc_ops;
}
