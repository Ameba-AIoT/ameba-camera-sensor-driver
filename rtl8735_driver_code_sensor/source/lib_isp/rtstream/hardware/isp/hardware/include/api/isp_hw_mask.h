#ifndef _ISP_HW_MASK_H_INC_
#define _ISP_HW_MASK_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>

struct isp_mask_area {
	uint32_t id;
	enum rts_isp_geom_type type;
	union {
		rts_isp_grid_t grid;
		rts_isp_prect_t rect;
	};
};

struct isp_mask_bitmap {
	uint32_t id;
	rts_isp_grid_size_t size;
	const void *bitmap;
	int num;
};

struct isp_hw_mask_ops {
	int (*enable)(uint32_t isp_id, uint32_t id, int enable);
	int (*set_color)(uint32_t isp_id, uint32_t color);
	int (*set_area)(uint32_t isp_id, const struct isp_mask_area *area,
			const rts_isp_size_t *size);
	int (*set_bitmap)(uint32_t isp_id, const struct isp_mask_bitmap *bm);
};

const struct isp_hw_mask_ops *isp_hw_mask_get_ops(void);

#endif /* _ISP_HW_MASK_H_INC_ */

