/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_mod.h>
#include <isp_uds.h>
#include <isp_mod_mask.h>

static void free_mask(struct rts_isp_mask *mask)
{
	int i;

	if (!mask)
		return;
	if (!mask->entries) {
		isp_free(mask);
		return;
	}
	for (i = 0; i < ISP_MASK_GRID_NUM; i++)
		isp_free(mask->entries[i].bitmap);
	isp_free(mask->entries);
	isp_free(mask);
}

static struct rts_isp_mask *alloc_mask(const struct isp_mask *isp_mask)
{
	int i;
	struct rts_isp_mask *m;

	if (!isp_calloc_item(m))
		return NULL;
	if (!isp_calloc_array(m->entries, ISP_MASK_NUM))
		goto err;
	for (i = 0; i < ISP_MASK_GRID_NUM; i++)
		if (!isp_calloc_array(m->entries[i].bitmap,
				      sizeof(isp_mask->bitmap[i])))
			goto err;
	return m;
err:
	free_mask(m);
	return NULL;
}

static void make_external_mask(struct rts_isp_mask *mask,
			       const struct isp_mask *isp_mask)
{
	int i;
	struct rts_isp_mask_entry *entry;

	mask->color = isp_mask->color;
	set_const_var(mask->number, ISP_MASK_NUM);
	for (i = 0; i < ISP_MASK_NUM; i++) {
		entry = &mask->entries[i];
		set_const_var(entry->type, isp_mask->entries[i].type);
		entry->enable = isp_mask->entries[i].enable;
		if (entry->type == RTS_ISP_GRID) {
			set_const_var(entry->max_cols,
				      isp_mask->entries[i].max_cols);
			set_const_var(entry->max_rows,
				      isp_mask->entries[i].max_rows);
			entry->grid = isp_mask->entries[i].grid;
			memcpy(entry->bitmap, isp_mask->bitmap[i],
			       sizeof(isp_mask->bitmap[i]));
		} else {
			entry->rect = isp_mask->entries[i].rect;
		}
	}
}

static void make_internal_mask(struct isp_mask *isp_mask,
			       const struct rts_isp_mask *mask)
{
	int i;

	isp_mask->color = mask->color;
	isp_assert(mask->number == ARRAY_SIZE(isp_mask->entries));
	for (i = 0; i < mask->number; i++) {
		isp_mask->entries[i].type = mask->entries[i].type;
		isp_mask->entries[i].enable = mask->entries[i].enable;
		if (isp_mask->entries[i].type == RTS_ISP_GRID) {
			isp_mask->entries[i].max_cols =
				mask->entries[i].max_cols;
			isp_mask->entries[i].max_rows =
				mask->entries[i].max_rows;
			isp_mask->entries[i].grid = mask->entries[i].grid;
			memcpy(isp_mask->bitmap[i], mask->entries[i].bitmap,
			       sizeof(isp_mask->bitmap[i]));
		} else {
			isp_mask->entries[i].rect = mask->entries[i].rect;
		}
	}
}

int rts_isp_query_mask(uint32_t isp_id, struct rts_isp_mask **mask)
{
	int ret;
	struct rts_isp_mask *m;
	struct isp_mask isp_mask;

	if (isp_id >= _ISP_ID_NUM || !mask)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_MASK, MASK_EXEC_GET,
				     &isp_mask, sizeof(isp_mask));
	if (ret)
		return ret;
	m = alloc_mask(&isp_mask);
	if (!m)
		return -RTS_ISP_ENOMEM;
	make_external_mask(m, &isp_mask);

	*mask = m;

	return RTS_ISP_OK;
}

int rts_isp_get_mask(uint32_t isp_id, struct rts_isp_mask *mask)
{
	int ret;
	struct isp_mask isp_mask;

	if (isp_id >= _ISP_ID_NUM || !mask)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_MASK, MASK_EXEC_GET,
				     &isp_mask, sizeof(isp_mask));
	if (ret)
		return ret;
	make_external_mask(mask, &isp_mask);

	return RTS_ISP_OK;
}

int rts_isp_set_mask(uint32_t isp_id, struct rts_isp_mask *mask)
{
	struct isp_mask isp_mask;

	if (isp_id >= _ISP_ID_NUM || !mask)
		return -RTS_ISP_EINVAL;

	make_internal_mask(&isp_mask, mask);

	return isp_uds_message_simple(isp_id, MOD_MASK, MASK_EXEC_SET,
				      &isp_mask, sizeof(isp_mask));
}

void rts_isp_release_mask(uint32_t isp_id, struct rts_isp_mask *mask)
{
	if (isp_id >= _ISP_ID_NUM || !mask)
		return;
	free_mask(mask);
}

