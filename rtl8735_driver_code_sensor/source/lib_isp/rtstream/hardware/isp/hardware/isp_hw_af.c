/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_af.h>
#include <isp_reg_af.h>

#define AF_WIN_COLS 5
#define AF_WIN_ROWS 5
#define AF_WIN_SAMPLE_GAP_H 8
#define AF_WIN_SAMPLE_GAP_V 8

static int isp_hw_af_get_hw_info(uint32_t isp_id,
				 struct isp_af_hw_info *info)
{
	if (!info)
		return -RTS_ISP_EINVAL;

	info->grid_info.size.cols = AF_WIN_COLS;
	info->grid_info.size.rows = AF_WIN_ROWS;
	info->grid_info.cell_align.w = AF_WIN_SAMPLE_GAP_H;
	info->grid_info.cell_align.h = AF_WIN_SAMPLE_GAP_V;
	info->cell_sample.w = AF_WIN_SAMPLE_GAP_H;
	info->cell_sample.h = AF_WIN_SAMPLE_GAP_V;
	info->win_edge_size = 4;

	return RTS_ISP_OK;
}

static int isp_hw_af_set_statis(uint32_t isp_id, const rts_isp_grid_t *grid)
{
	rts_isp_point_t end;

	end.x = grid->start.x + grid->cell.w * grid->size.cols;
	end.y = grid->start.y + grid->cell.h * grid->size.rows;

	isp_write_reg(grid->start.x, AF_WIN_START_X);
	isp_write_reg(grid->start.y, AF_WIN_START_Y);
	isp_write_reg(grid->cell.w / AF_WIN_SAMPLE_GAP_H, AF_WIN_WIDTH);
	isp_write_reg(grid->cell.h / AF_WIN_SAMPLE_GAP_V, AF_WIN_HEIGHT);

	isp_write_reg(grid->start.x, AF_START0_X);
	isp_write_reg(grid->start.y, AF_START0_Y);
	isp_write_reg(end.x, AF_END0_X);
	isp_write_reg(end.y, AF_END0_Y);
	isp_write_reg(grid->start.x + grid->cell.w, AF_START1_X);
	isp_write_reg(grid->start.y + grid->cell.h, AF_START1_Y);
	isp_write_reg(end.x - grid->cell.w, AF_END1_X);
	isp_write_reg(end.y - grid->cell.h, AF_END1_Y);
	isp_write_reg(0x138, AF_CTRL);

	return RTS_ISP_OK;
}

static int isp_hw_af_set_statis_th(uint32_t isp_id, uint8_t statis_th)
{
	isp_write_reg(statis_th, AF_THD1);
	return RTS_ISP_OK;
}

static const struct isp_hw_af_ops hw_af_ops = {
	.get_hw_info = isp_hw_af_get_hw_info,
	.set_statis = isp_hw_af_set_statis,
	.set_statis_th = isp_hw_af_set_statis_th,
};

const struct isp_hw_af_ops *isp_hw_af_get_ops(void)
{
	return &hw_af_ops;
}

