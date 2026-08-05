/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <rts_isp.h>

int cmd_test_mask(int argc, char *argv[])
{
	int i;
	int ret;
	struct rts_isp_mask *mask;

	ret = rts_isp_query_mask(ISP0, &mask);
	if (ret) {
		rts_isp_perror(ret, "query mask fail");
		return ret;
	}
	mask->color = 0xff0000;
	for (i = 0; i < mask->number; i++) {
		struct rts_isp_mask_entry *entry = &mask->entries[i];

		entry->enable = RTS_ISP_TRUE;
		if (entry->type == RTS_ISP_GRID) {
			int j;
			uint8_t *buf = entry->bitmap;

			entry->grid.start.x = 32;
			entry->grid.start.y = 32;
			entry->grid.cell.w = 32;
			entry->grid.cell.h = 32;
			entry->grid.size.cols = 40;
			entry->grid.size.rows = 30;

			for (j = 0; j < (int)entry->grid.size.rows; j += 2) {
				int index = j * entry->grid.size.cols / 8;

				buf[index + 0] = 0x55;
				buf[index + 1] = 0x55;
				buf[index + 2] = 0x55;
				buf[index + 3] = 0x55;
				buf[index + 4] = 0x55;
				buf[index + 5] = 0xaa;
				buf[index + 6] = 0xaa;
				buf[index + 7] = 0xaa;
				buf[index + 8] = 0xaa;
				buf[index + 9] = 0xaa;
			}
		} else {
			entry->rect.left = 1400 + (i - 1) / 2 * 200;
			entry->rect.top = 400 + (i - 1) % 2 * 200;
			entry->rect.right = entry->rect.left + 100;
			entry->rect.bottom = entry->rect.top + 100;
		}
	}
	ret = rts_isp_set_mask(ISP0, mask);
	if (ret) {
		rts_isp_perror(ret, "set mask fail");
		return ret;
	}
	rts_isp_release_mask(ISP0, mask);
	return 0;
}
