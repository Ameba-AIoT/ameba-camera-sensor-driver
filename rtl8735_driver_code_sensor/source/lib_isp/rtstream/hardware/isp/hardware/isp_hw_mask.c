/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_define.h>
#include <isp_utils.h>
#include <isp_hw_mask.h>
#include <isp_reg_mask.h>

static int isp_hw_mask_enable(uint32_t isp_id, uint32_t id, int enable)
{
	if (enable)
		isp_set_reg_bit(id, MASK_GLOBLE_EN);
	else
		isp_clr_reg_bit(id, MASK_GLOBLE_EN);
	return RTS_ISP_OK;
}

static int isp_hw_mask_set_color(uint32_t isp_id, uint32_t color)
{
	isp_write_reg(color, MASK_PATTERN);
	return RTS_ISP_OK;
}

static int calc_mask_grid_size(rts_isp_grid_size_t *grid_size,
			       const struct isp_mask_area *area,
			       const rts_isp_size_t *size)
{
	int32_t n;
	const rts_isp_grid_t *grid;

	if (!grid_size || !area || !size)
		return -RTS_ISP_EINVAL;

	grid = &area->grid;

	if (!grid->cell.w || !grid->cell.h)
		return -RTS_ISP_EINVAL;

	n = (size->w - grid->start.x + grid->cell.w - 1) / grid->cell.w;
	grid_size->cols = min(grid->size.cols, n);
	n = (size->h - grid->start.y + grid->cell.h - 1) / grid->cell.h;
	grid_size->rows = min(grid->size.rows, n);

	return RTS_ISP_OK;
}

static int isp_hw_mask_set_area(uint32_t isp_id,
				const struct isp_mask_area *area,
				const rts_isp_size_t *size)
{
	if (!area)
		return -RTS_ISP_EINVAL;
	if (area->type == RTS_ISP_GRID) {
		int ret;
		rts_isp_grid_size_t grid_size;

		if (area->id >= ISP_MASK_GRID_NUM)
			return -RTS_ISP_EINVAL;

		ret = calc_mask_grid_size(&grid_size, area, size);
		if (ret)
			return ret;
		isp_write_reg(area->grid.start.x << MASK_START_X_OFFSET |
			      area->grid.start.y << MASK_START_Y_OFFSET,
			      MASK_GRID_START);
		isp_write_reg(grid_size.cols << MASK_WINUM_X_OFFSET |
			      grid_size.rows << MASK_WINUM_Y_OFFSET,
			      MASK_GRID_WINUM);
		isp_write_reg(area->grid.cell.w << MASK_WIN_WIDTH_OFFSET |
			      area->grid.cell.h << MASK_WIN_HEIGHT_OFFSET,
			      MASK_GRID_WIN_SIZE);
	} else {
		uint32_t reg_offset;

		if (area->id < ISP_MASK_GRID_NUM ||
		    area->id >= ISP_MASK_GRID_NUM + ISP_MASK_RECT_NUM)
			return -RTS_ISP_EINVAL;

		reg_offset = (MASK_RECTANGLE1_START +
			      (area->id - ISP_MASK_GRID_NUM) *
			      (MASK_RECTANGLE2_START - MASK_RECTANGLE1_START));
		isp_write_reg(area->rect.left << MASK1_START_X_OFFSET |
			      area->rect.top << MASK1_START_Y_OFFSET,
			      reg_offset);
		isp_write_reg(area->rect.right << MASK1_END_X_OFFSET |
			      area->rect.bottom << MASK1_END_Y_OFFSET,
			      reg_offset + 4);
	}
	return RTS_ISP_OK;
}

static int isp_hw_mask_set_bitmap(uint32_t isp_id,
				  const struct isp_mask_bitmap *bitmap)
{
	int row;

	if (!bitmap || bitmap->id >= ISP_MASK_GRID_NUM ||
	    !bitmap->bitmap || bitmap->size.cols & 0x7 ||
	    bitmap->size.cols > ISP_MASK_GRID_COLS ||
	    bitmap->size.rows > ISP_MASK_GRID_ROWS ||
	    bitmap->num != (int)(bitmap->size.cols * bitmap->size.rows))
		return -RTS_ISP_EINVAL;

	for (row = 0; row < (int)bitmap->size.rows; row++) {
		int cols;
		uint32_t val = 0;
		const uint8_t *bits;
		uint32_t reg_offset = MASK_BITMAP0 + row * 2 * 4;

		bits = (uint8_t *)((uint32_t)bitmap->bitmap + row * bitmap->size.cols / 8);

		cols = bitmap->size.cols/8;
		if (cols > 4) {
			isp_write_reg(bits[4], reg_offset + 4);
			cols--;
		}
#if 0
		while (cols)
			val = val << 8 | bits[4 - cols--];
	
#endif
		for (int i=0; i < cols; i++) {
			val = val | bits[i]<<(8*i);
		}
		isp_write_reg(val, reg_offset);
	}
	return RTS_ISP_OK;
}


static const struct isp_hw_mask_ops hw_mask_ops = {
	.enable = isp_hw_mask_enable,
	.set_color = isp_hw_mask_set_color,
	.set_area = isp_hw_mask_set_area,
	.set_bitmap = isp_hw_mask_set_bitmap,
};

const struct isp_hw_mask_ops *isp_hw_mask_get_ops(void)
{
	return &hw_mask_ops;
}

