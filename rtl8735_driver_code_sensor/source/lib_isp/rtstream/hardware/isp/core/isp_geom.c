/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp_errno.h>
#include <rts_isp_geom.h>
#include <isp_utils.h>

int rts_isp_get_grid_from_rect(rts_isp_grid_t *grid,
			       const rts_isp_rect_t *rect,
			       const rts_isp_grid_info_t *info)
{
	if (!rect || !info || !grid ||
	    info->size.cols <= 0 || info->size.rows <= 0 ||
	    info->cell_align.w <= 0 || info->cell_align.h <= 0)
		return -RTS_ISP_EINVAL;

	grid->size = info->size;
	grid->cell.w = rounddown(rect->w / grid->size.cols, info->cell_align.w);
	grid->cell.h = rounddown(rect->h / grid->size.rows, info->cell_align.h);
	if (!grid->cell.w || !grid->cell.h)
		return -RTS_ISP_ERANGE;
	grid->start.x = rect->x + (rect->w -
				   grid->cell.w * grid->size.cols) / 2;
	grid->start.y = rect->y + (rect->h -
				   grid->cell.h * grid->size.rows) / 2;

	return RTS_ISP_OK;
}

int rts_isp_get_rect_from_grid(rts_isp_rect_t *rect,
			       const rts_isp_grid_t *grid)
{
	if (!rect || !grid)
		return -RTS_ISP_EINVAL;

	rect->start = grid->start;
	rect->w = grid->cell.w * grid->size.cols;
	rect->h = grid->cell.h * grid->size.rows;

	return RTS_ISP_OK;
}

int rts_isp_get_grid_from_prect(rts_isp_grid_t *grid,
				const rts_isp_prect_t *prect,
				const rts_isp_grid_info_t *info)
{
	int ret;
	rts_isp_rect_t rect;

	if (!prect || !info || !grid)
		return -RTS_ISP_EINVAL;

	ret = rts_isp_get_rect_from_prect(&rect, prect);
	if (ret)
		return ret;

	return rts_isp_get_grid_from_rect(grid, &rect, info);
}

int rts_isp_get_prect_from_grid(rts_isp_prect_t *prect,
				const rts_isp_grid_t *grid)
{
	if (!prect || !grid)
		return -RTS_ISP_EINVAL;

	prect->start = grid->start;
	prect->right = grid->start.x + grid->cell.w * grid->size.cols;
	prect->bottom = grid->start.y + grid->cell.h * grid->size.rows;

	return RTS_ISP_OK;
}

int rts_isp_get_rect_from_prect(rts_isp_rect_t *rect,
				const rts_isp_prect_t *prect)
{
	if (!rect || !prect ||
	    prect->right < prect->left || prect->bottom < prect->top)
		return -RTS_ISP_EINVAL;
	rect->x = prect->left;
	rect->y = prect->top;
	rect->w = prect->right - prect->left;
	rect->h = prect->bottom - prect->top;
	return RTS_ISP_OK;
}

int rts_isp_get_prect_from_rect(rts_isp_prect_t *prect,
				const rts_isp_rect_t *rect)
{
	if (!rect || !prect)
		return -RTS_ISP_EINVAL;
	prect->left = rect->x;
	prect->top = rect->y;
	prect->right = rect->x + rect->w;
	prect->bottom = rect->y + rect->h;
	if (prect->right < prect->left || prect->bottom < prect->top)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}
