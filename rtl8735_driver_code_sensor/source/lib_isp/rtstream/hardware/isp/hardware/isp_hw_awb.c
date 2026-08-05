/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_awb.h>
#include <isp_reg_awb.h>

#define AWB_WIN_COLS 16
#define AWB_WIN_ROWS 16
#define AWB_WIN_ALIGN_H 2
#define AWB_WIN_ALIGN_V 2
#define AWB_WIN_SAMPLE_GAP_H 2
#define AWB_WIN_SAMPLE_GAP_V 2

static int isp_hw_awb_get_hw_info(uint32_t isp_id,
				  struct isp_awb_hw_info *info)
{
	if (!info)
		return -RTS_ISP_EINVAL;

	info->grid_info.size.cols = AWB_WIN_COLS;
	info->grid_info.size.rows = AWB_WIN_ROWS;
	info->grid_info.cell_align.w = AWB_WIN_ALIGN_H;
	info->grid_info.cell_align.h = AWB_WIN_ALIGN_V;
	info->cell_sample.w = AWB_WIN_SAMPLE_GAP_H;
	info->cell_sample.h = AWB_WIN_SAMPLE_GAP_V;
	info->rgby_size = 2;
	info->rgbg_size = 2;
	info->pixels_size = 2;

	return RTS_ISP_OK;
}

static int isp_hw_awb_set_statis(uint32_t isp_id, const rts_isp_grid_t *grid)
{
	if (!grid)
		return -RTS_ISP_EINVAL;

	isp_write_reg(grid->start.x << AWB_START_X_OFFSET |
		      grid->start.y << AWB_START_Y_OFFSET, AWB_WIN_START);
	isp_write_reg((grid->cell.w / AWB_WIN_ALIGN_H) << AWB_WIN_WIDTH_OFFSET |
		      (grid->cell.h / AWB_WIN_ALIGN_V) << AWB_WIN_HEIGHT_OFFSET |
		      grid->size.rows << AWB_WIN_NUM_H_OFFSET |
		      grid->size.cols << AWB_WIN_NUM_V_OFFSET, AWB_WIN_SIZE);
	isp_write_reg(0x22000565, AWB_BRIGHT_COEF);
	isp_write_reg(0x11C, AWB_STATIS_CTRL);
	//printf("w %d h %d rows %d cols %d \r\n", grid->cell.w / AWB_WIN_ALIGN_H, grid->cell.h / AWB_WIN_ALIGN_V, grid->size.rows, grid->size.cols);

	return RTS_ISP_OK;
}

static int
isp_hw_awb_set_statis_config(uint32_t isp_id,
			     const struct rts_isp_awb_stat_config *config)
{
	const struct rts_isp_awb_rough_gain *rough_gain = &config->rough_gain;
	const struct rts_isp_awb_rough_limit *rough = &config->rough_limit;
	const struct rts_isp_awb_fine_limit *fine = &config->fine_limit;
	const struct rts_isp_awb_illums *illums = &config->illums;

	if (!config)
		return -RTS_ISP_EINVAL;

	if (rough_gain->need_update)
		isp_write_reg(rough_gain->r_gain << GAIN_R_FINE_OFFSET |
			      rough_gain->b_gain << GAIN_B_FINE_OFFSET,
			      AWB_FINE_TUNE_GAIN);
	if (rough->need_update) {
		isp_write_reg(rough->y_min << MIN_BRIGHT_WIN_OFFSET |
			      rough->y_max << MAX_BRIGHT_WIN_OFFSET,
			      AWB_WIN_BRIGHT_THD);
		isp_write_reg(rough->r_min << MIN_R_WIN_OFFSET |
			      rough->r_max << MAX_R_WIN_OFFSET,
			      AWB_WIN_R_THD);
		isp_write_reg(rough->g_min << MIN_G_WIN_OFFSET |
			      rough->g_max << MAX_G_WIN_OFFSET,
			      AWB_WIN_G_THD);
		isp_write_reg(rough->b_min << MIN_B_WIN_OFFSET |
			      rough->b_max << MAX_B_WIN_OFFSET,
			      AWB_WIN_B_THD);
		isp_write_reg(rough->rg_min << MIN_R_G_WIN_OFFSET |
			      rough->rg_max << MAX_R_G_WIN_OFFSET,
			      AWB_WIN_RG_THD);
		isp_write_reg(rough->bg_min << MIN_B_G_WIN_OFFSET |
			      rough->bg_max << MAX_B_G_WIN_OFFSET,
			      AWB_WIN_BG_THD);
		isp_write_reg(AWB_WIN_RANGE_EN_MASK | AWB_WIN_RATIO_EN_MASK,
			      AWB_WIN_LIMIT_ENABLE);
	}
	if (fine->need_update) {
		isp_write_reg(fine->y_min << MIN_BRIGHT_FINE_OFFSET |
			      fine->y_max << MAX_BRIGHT_FINE_OFFSET,
			      AWB_FINE_BRIGHT_THD);
		isp_write_reg(fine->rg_min << MIN_R_G_FINE_OFFSET |
			      fine->rg_max << MAX_R_G_FINE_OFFSET,
			      AWB_FINE_RG_THD);
		isp_write_reg(fine->bg_min << MIN_B_G_FINE_OFFSET |
			      fine->bg_max << MAX_B_G_FINE_OFFSET,
			      AWB_FINE_BG_THD);
	}
	if (illums->need_update) {
		const uint16_t *gain;

		gain = illums->r_gain;
		isp_write_reg(gain[0] << GAIN_R_ROUGH_1_OFFSET |
			      gain[1] << GAIN_R_ROUGH_2_OFFSET,
			      AWB_ROUGH_GAIN_R_1_2);
		isp_write_reg(gain[2] << GAIN_R_ROUGH_3_OFFSET |
			      gain[3] << GAIN_R_ROUGH_4_OFFSET,
			      AWB_ROUGH_GAIN_R_3_4);
		isp_write_reg(gain[4] << GAIN_R_ROUGH_5_OFFSET |
			      gain[5] << GAIN_R_ROUGH_6_OFFSET,
			      AWB_ROUGH_GAIN_R_5_6);
		gain = illums->b_gain;
		isp_write_reg(gain[0] << GAIN_B_ROUGH_1_OFFSET |
			      gain[1] << GAIN_B_ROUGH_2_OFFSET,
			      AWB_ROUGH_GAIN_B_1_2);
		isp_write_reg(gain[2] << GAIN_B_ROUGH_3_OFFSET |
			      gain[3] << GAIN_B_ROUGH_4_OFFSET,
			      AWB_ROUGH_GAIN_B_3_4);
		isp_write_reg(gain[4] << GAIN_B_ROUGH_5_OFFSET |
			      gain[5] << GAIN_B_ROUGH_6_OFFSET,
			      AWB_ROUGH_GAIN_B_5_6);
		isp_write_reg(illums->rg_min << MIN_RG_ROUGH_OFFSET |
			      illums->rg_max << MAX_RG_ROUGH_OFFSET,
			      AWB_ROUGH_RG_THD);
		isp_write_reg(illums->bg_min << MIN_BG_ROUGH_OFFSET |
			      illums->bg_max << MAX_BG_ROUGH_OFFSET,
			      AWB_ROUGH_BG_THD);
		isp_write_reg(illums->y_min << MIN_BRIGHT_ROUGH_OFFSET |
			      illums->y_max << MAX_BRIGHT_ROUGH_OFFSET,
			      AWB_ROUGH_BRIGHT_THD);
	}
	return RTS_ISP_OK;
}

static int isp_hw_awb_set_final_gain(uint32_t isp_id,
				     const struct rts_isp_awb_gain *gain)
{
	if (!gain)
		return -RTS_ISP_EINVAL;

	isp_write_reg(gain->r_gain, AWB_GAIN_R);
	isp_write_reg((gain->gr_gain + gain->gb_gain) / 2, AWB_GAIN_G);
	isp_write_reg(gain->b_gain, AWB_GAIN_B);
	isp_write_reg(AWB_GAIN_TRIG_MASK, AWB_GAIN_CTRL);

	return RTS_ISP_OK;
}

static int isp_hw_awb_set_clip_mode(uint32_t isp_id, int enable)
{
	if (enable) {
		// Enable clip max data depth to 14bit
		isp_set_reg_bit(CLIP_14BITS_ENABLE_OFFSET, AWB_OVER_EXP_REDUCT_EN);
	}
	else {
		// Disable clip max data depth to 14bit
		isp_clr_reg_bit(CLIP_14BITS_ENABLE_OFFSET, AWB_OVER_EXP_REDUCT_EN);
	}

	return RTS_ISP_OK;
}

static const struct isp_hw_awb_ops hw_awb_ops = {
	.get_hw_info = isp_hw_awb_get_hw_info,
	.set_statis = isp_hw_awb_set_statis,
	.set_statis_config = isp_hw_awb_set_statis_config,
	.set_final_gain = isp_hw_awb_set_final_gain,
	.set_clip = isp_hw_awb_set_clip_mode,
};

const struct isp_hw_awb_ops *isp_hw_awb_get_ops(void)
{
	return &hw_awb_ops;
}
