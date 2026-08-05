/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_ystat.h>
#include <isp_reg_ystat.h>

#define YSTAT_WIN_COLS 16
#define YSTAT_WIN_ROWS 16
#define YSTAT_WIN_SAMPLE_GAP_H 4
#define YSTAT_WIN_SAMPLE_GAP_V 4
#define YSTAT_HIST_BINS 256
#define YSTAT_HIST_SAMPLE_GAP_H 4
#define YSTAT_HIST_SAMPLE_GAP_V 4

static int isp_hw_ystat_get_hw_info(uint32_t isp_id,
				 struct isp_ystat_hw_info *info)
{
	if (!info)
		return -RTS_ISP_EINVAL;

	info->grid_info.size.cols = YSTAT_WIN_COLS;
	info->grid_info.size.rows = YSTAT_WIN_ROWS;
	info->grid_info.cell_align.w = YSTAT_WIN_SAMPLE_GAP_H;
	info->grid_info.cell_align.h = YSTAT_WIN_SAMPLE_GAP_V;
	info->cell_sample.w = YSTAT_WIN_SAMPLE_GAP_H;
	info->cell_sample.h = YSTAT_WIN_SAMPLE_GAP_V;
	info->hist_bins = YSTAT_HIST_BINS;
	info->hist_sample.w = YSTAT_HIST_SAMPLE_GAP_H;
	info->hist_sample.h = YSTAT_HIST_SAMPLE_GAP_V;
	info->y_mean_size = 2;
	info->hist_bin_size = 4;

	return RTS_ISP_OK;
}

static int isp_hw_ystat_set_statis(uint32_t isp_id, const rts_isp_grid_t *grid)
{
	rts_isp_point_t end;
	int win_sample_num;

	end.x = grid->start.x + grid->cell.w * grid->size.cols;
	end.y = grid->start.y + grid->cell.h * grid->size.rows;
	win_sample_num = (grid->cell.w * grid->cell.h /
			  YSTAT_WIN_SAMPLE_GAP_H / YSTAT_WIN_SAMPLE_GAP_V);

	isp_write_reg(grid->start.x | grid->start.y << 16, YSTAT_WIN_START);
	isp_write_reg((grid->cell.w / YSTAT_WIN_SAMPLE_GAP_H) |
		      (grid->cell.h / YSTAT_WIN_SAMPLE_GAP_V) << 8 |
		      grid->size.cols << 16 | grid->size.rows << 24,
		      YSTAT_WIN_SIZE);
	isp_write_reg(win_sample_num, YSTAT_WIN_CAL_NUM);
	isp_write_reg(grid->start.x | grid->start.y << 16, YSTAT_HWIN_START);
	isp_write_reg(end.x | end.y << 16, YSTAT_HWIN_END);

	isp_write_reg(0x01, YSTAT_CTRL);

	return RTS_ISP_OK;
}

static const struct isp_hw_ystat_ops hw_ystat_ops = {
	.get_hw_info = isp_hw_ystat_get_hw_info,
	.set_statis = isp_hw_ystat_set_statis,
};

const struct isp_hw_ystat_ops *isp_hw_ystat_get_ops(void)
{
	return &hw_ystat_ops;
}
