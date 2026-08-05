/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_dehaze.h>
#include <isp_reg_dehaze.h>
#include <isp_reg_virtual.h>

static int dehaze_set_window(uint32_t isp_id, const rts_isp_rect_t *rect)
{
	int i;
	int ret;
	int pixels;
	rts_isp_grid_t grid;
	rts_isp_grid_info_t grid_info = {
		.size = {40, 30},
		.cell_align = {1, 1},
	};

	ret = rts_isp_get_grid_from_rect(&grid, rect, &grid_info);
	if (ret)
		return ret;
	isp_write_reg(grid.cell.w << REGF_BLOCK_WIDTH_OFFSET |
		      grid.cell.h << REGF_BLOCK_HEIGHT_OFFSET |
		      grid.size.cols << REGF_BLOCK_COL_NUM_OFFSET |
		      grid.size.rows << REGF_BLOCK_LINE_NUM_OFFSET,
		      DEHAZE_STORE_BLOCK_CFG);
	for (i = 1; i < 128; i++) {
		pixels = (grid.cell.w / i) * (grid.cell.h / i);
		if (pixels <= 256)
			break;
	}
	if (i == 128 || pixels == 0)
		return -RTS_ISP_ERANGE;
	isp_write_reg(i << REGF_DEHAZE_SAMPLEH_OFFSET |
		      i << REGF_DEHAZE_SAMPLEV_OFFSET,
		      DEHAZE_STORE_SAMPLE_CFG);
	isp_write_reg((1 << 16) / pixels, DEHAZE_STORE_MEAN_DIVIDE_PARAMETER);

	return RTS_ISP_OK;
}

static int dehaze_set_mean_win(uint32_t isp_id)
{
	int points;
	rts_isp_prect_t mean_prect = { { {5, 2, 25, 12} } };

	points = ((mean_prect.right - mean_prect.left + 1) *
		  (mean_prect.bottom - mean_prect.top + 1));

	isp_write_reg(mean_prect.left << REGF_DARK_MEAN_X_START_OFFSET |
		      mean_prect.top << REGF_DARK_MEAN_Y_START_OFFSET |
		      mean_prect.right << REGF_DARK_MEAN_X_END_OFFSET |
		      mean_prect.bottom << REGF_DARK_MEAN_Y_END_OFFSET,
		      DEHAZE_DARK_MEAN_WIN);
	isp_write_reg(points, DEHAZE_DARK_MEAN_PARAM);
	isp_write_reg(mean_prect.left << REGF_GRADIENT_MEAN_X_START_OFFSET |
		      mean_prect.top << REGF_GRADIENT_MEAN_Y_START_OFFSET |
		      mean_prect.right << REGF_GRADIENT_MEAN_X_END_OFFSET |
		      mean_prect.bottom << REGF_GRADIENT_MEAN_Y_END_OFFSET,
		      DEHAZE_GRADIENT_WIN);
	isp_write_reg(points, DEHAZE_GRADIENT_MEAN_PARAM);

	return RTS_ISP_OK;
}

static int isp_hw_dehaze_init(uint32_t isp_id, const rts_isp_rect_t *rect)
{
	int ret;

	ret = dehaze_set_window(isp_id, rect);
	if (ret)
		return ret;
	return dehaze_set_mean_win(isp_id);
}

static int isp_hw_dehaze_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(DEHAZE_LEVEL_CTRL_DEF, VDEHAZE_LEVEL);
	return RTS_ISP_OK;
}

static int isp_hw_dehaze_set_enable(uint32_t isp_id, int enable)
{
	if (enable) {
		isp_write_reg(AUTO_DEHAZE_EN_MASK, DEHAZE_AUTO_ENABLE);
	} else {
		isp_write_reg(0, DEHAZE_AUTO_ENABLE);
	}
	return RTS_ISP_OK;
}

static int isp_hw_dehaze_set_level(uint32_t isp_id, int level)
{
	const int val_def = isp_read_vreg(VDEHAZE_LEVEL);

	if (level < DEHAZE_LEVEL_CTRL_DEF)
		level = linear_intp(level, DEHAZE_LEVEL_CTRL_MIN,
				    DEHAZE_LEVEL_CTRL_MIN,
				    DEHAZE_LEVEL_CTRL_DEF, val_def);
	else
		level = linear_intp(level,
				    DEHAZE_LEVEL_CTRL_DEF, val_def,
				    DEHAZE_LEVEL_CTRL_MAX,
				    DEHAZE_LEVEL_CTRL_MAX);

	isp_write_reg_mask(level, DEHAZE_LEVEL_STEP, REGF_DEHAZE_LEVEL_MASK);
	return RTS_ISP_OK;
}

static const struct isp_hw_dehaze_ops hw_dehaze_ops = {
	.init = isp_hw_dehaze_init,
	.init_vreg = isp_hw_dehaze_init_vreg,
	.set_enable = isp_hw_dehaze_set_enable,
	.set_level = isp_hw_dehaze_set_level,
};

const struct isp_hw_dehaze_ops *isp_hw_dehaze_get_ops(void)
{
	return &hw_dehaze_ops;
}
