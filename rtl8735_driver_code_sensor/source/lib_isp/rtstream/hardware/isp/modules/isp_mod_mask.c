/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_mod_rgb2yuv.h>
#include <isp_mod_mcrop.h>
#include <isp_mod_mask.h>
#include <isp_hw_mask.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_MASK

struct isp_mod_mask {
	struct isp_mod mod;
	struct isp_mask mask;
	const struct isp_hw_mask_ops *hw_ops;
};

static int convert_rgb_to_ycbcr(struct isp_mod *mod,
				uint32_t rgb, uint32_t *ycbcr)
{
	int ret;

	if (!ycbcr)
		return -RTS_ISP_EINVAL;

	ret = isp_mod_sibling_execute(mod, MOD_RGB2YUV, RGB2YUV_EXEC_CONVERT,
				      &rgb, sizeof(rgb));
	if (ret)
		return ret;

	*ycbcr = rgb;

	return RTS_ISP_OK;
}

static int mask_check(const struct isp_mask *mask, const rts_isp_size_t *size)
{
	int i;

	for (i = 0; i < (int)ARRAY_SIZE(mask->entries); i++) {
		const struct isp_mask_entry *entry = &mask->entries[i];

		if (entry->type == RTS_ISP_GRID) {
			if (i >= ISP_MASK_GRID_NUM)
				return -RTS_ISP_EINVAL;
			if (entry->max_cols != ISP_MASK_GRID_COLS ||
			    entry->max_rows != ISP_MASK_GRID_ROWS)
				return -RTS_ISP_EINVAL;
			if (entry->grid.cell.w & 1 ||
			    !entry->grid.size.cols || !entry->grid.size.rows ||
			    entry->grid.size.cols & 7 ||
			    entry->grid.size.cols > (int)entry->max_cols ||
			    entry->grid.size.rows > (int)entry->max_rows)
				return -RTS_ISP_EINVAL;
			if (entry->grid.start.x < 0 || entry->grid.start.y < 0)
				return -RTS_ISP_EINVAL;
			if (entry->grid.start.x & 1 || entry->grid.start.y & 1)
				return -RTS_ISP_EINVAL;
		} else {
			if (i < ISP_MASK_GRID_NUM)
				return -RTS_ISP_EINVAL;
			if (entry->rect.left < 0 || entry->rect.top < 0)
				return -RTS_ISP_EINVAL;
			if (entry->rect.left & 1 || entry->rect.right & 1)
				return -RTS_ISP_EINVAL;
			if (entry->rect.left > entry->rect.right ||
			    entry->rect.top > entry->rect.bottom)
				return -RTS_ISP_EINVAL;
			if (entry->rect.right > (int)size->w ||
			    entry->rect.bottom > (int)size->h)
				return -RTS_ISP_EINVAL;
		}
	}
	return RTS_ISP_OK;
}

static int to_bitmap_index(int id)
{
	return id;
}

static int mod_mask_set_entries(struct isp_mod *mod,
				const struct isp_mask *set,
				const rts_isp_size_t *size)
{
	int i;
	int ret;
	struct isp_mod_mask *mask = get_mod(mod, mask);

	for (i = 0; i < ISP_MASK_NUM; i++) {
		struct isp_mask_area area;
		const struct isp_mask_entry *entry = &set->entries[i];

		ret = mask->hw_ops->enable(mod->owner_id, i, RTS_ISP_FALSE);
		if (ret)
			return ret;
		area.id = i;
		area.type = entry->type;
		if (entry->type == RTS_ISP_GRID)
			area.grid = entry->grid;
		else
			area.rect = entry->rect;
		ret = mask->hw_ops->set_area(mod->owner_id, &area, size);
		if (ret)
			return ret;

		if (entry->type == RTS_ISP_GRID) {
			struct isp_mask_bitmap bitmap = {
				.id = i,
				.size = entry->grid.size,
				.bitmap = set->bitmap[to_bitmap_index(i)],
				.num = (entry->grid.size.cols *
					entry->grid.size.rows),
			};

			ret = mask->hw_ops->set_bitmap(mod->owner_id, &bitmap);
			if (ret)
				return ret;
		}
		ret = mask->hw_ops->enable(mod->owner_id, i, entry->enable);
		if (ret)
			return ret;
	}
	return RTS_ISP_OK;
}

static int mod_mask_set(struct isp_mod *mod, const struct isp_mask *set)
{
	int ret;
	uint32_t yuv;
	rts_isp_size_t size;
	struct isp_mod_mask *mask = get_mod(mod, mask);

	if (!set)
		return -RTS_ISP_EINVAL;

	ret = isp_mod_sibling_get_info(mod, MOD_MCROP, MCROP_INFO_ISP_SIZE,
				       &size, sizeof(size));
	if (ret)
		return ret;
	ret = mask_check(set, &size);
	if (ret)
		return ret;

	ret = convert_rgb_to_ycbcr(mod, set->color, &yuv);
	if (ret)
		goto err;
	ret = mask->hw_ops->set_color(mod->owner_id, yuv);
	if (ret)
		goto err;
	ret = mod_mask_set_entries(mod, set, &size);
	if (ret)
		goto err;

	mask->mask = *set;

	return RTS_ISP_OK;
err:
	if (set != &mask->mask)
		mod_mask_set(mod, &mask->mask);
	isp_perror(ret, "set mask fail");
	return ret;
}

static int mod_mask_exec_get(struct isp_mod *mod, void *data)
{
	struct isp_mod_mask *mask = get_mod(mod, mask);

	*(struct isp_mask *)data = mask->mask;
	return RTS_ISP_OK;
}

static int mod_mask_exec_set(struct isp_mod *mod, void *data)
{
	return mod_mask_set(mod, data);
}

static struct isp_mod_action_info mask_exec_actions[] = {
	ISP_MOD_ACTION(MASK_EXEC_GET, mod_mask_exec_get),
	ISP_MOD_ACTION(MASK_EXEC_SET, mod_mask_exec_set),
};

static int isp_mod_mask_init_info(struct isp_mask *mask,
				  const rts_isp_size_t *size)
{
	int i;
	struct isp_mask_entry *entry;

	mask->color = 0x808080;
	for (i = 0; i < ISP_MASK_GRID_NUM; i++) {
		entry = &mask->entries[i];
		entry->type = RTS_ISP_GRID;
		entry->enable = RTS_ISP_FALSE;
		entry->max_cols = ISP_MASK_GRID_COLS;
		entry->max_rows = ISP_MASK_GRID_ROWS;
		entry->grid.start.x = 0;
		entry->grid.start.y = 0;
		entry->grid.size.cols = entry->max_cols;
		entry->grid.size.rows = entry->max_rows;
		entry->grid.cell.w = (size->w / entry->grid.size.cols) & ~1;
		entry->grid.cell.h = (size->h / entry->grid.size.rows);
	}
	for (i = ISP_MASK_GRID_NUM; i < ISP_MASK_NUM; i++) {
		entry = &mask->entries[i];
		entry->type = RTS_ISP_RECT;
		entry->enable = RTS_ISP_FALSE;
	}
	return RTS_ISP_OK;
}

static int mod_mask_mcrop_change(struct isp_mod *mod, void *data)
{
	const rts_isp_rect_t *rect = data;
	struct isp_mod_mask *mask = get_mod(mod, mask);

	isp_mod_mask_init_info(&mask->mask, &rect->size);

	return mod_mask_set(mod, &mask->mask);
}

static struct isp_mod_action_info mask_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_mask_mcrop_change),
};

static int isp_mod_mask_init(struct isp_mod *mod)
{
	int ret;
	rts_isp_size_t size;
	struct isp_mod_mask *mask;

	mask = get_mod(mod, mask);
	mask->hw_ops = isp_hw_mask_get_ops();
	if (mask->hw_ops == NULL) {
		isp_error("get mask hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_mask_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_mask_hardware_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_mask *mask = get_mod(mod, mask);

	ret = isp_mod_hardware_init(isp_mod_get_sibling(mod, MOD_RGB2YUV));
	return ret;
}

static struct isp_mod_mask mask;

int isp_register_mod_mask(void)
{
	memset(&mask, 0, sizeof(mask));
	mask.mod.id = MOD_MASK;
	mask.mod.name = "mask";
	mask.mod.notify_bits = ISP_MCROP_CHANGE_BIT;
	mask.mod.init = isp_mod_mask_init;
	mask.mod.cleanup = isp_mod_mask_cleanup;
	mask.mod.hardware_init = isp_mod_mask_hardware_init;
	mask.mod.exec_actions = mask_exec_actions;
	mask.mod.exec_actions_num = ARRAY_SIZE(mask_exec_actions);
	mask.mod.notify_actions = mask_notify_actions;
	mask.mod.notify_actions_num = ARRAY_SIZE(mask_notify_actions);
	return isp_mod_register(&mask.mod);
}

void isp_unregister_mod_mask(void)
{
	isp_mod_unregister(&mask.mod);
}

