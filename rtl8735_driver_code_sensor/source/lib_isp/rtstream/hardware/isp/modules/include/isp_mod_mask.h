#ifndef _ISP_MOD_MASK_H_INC_
#define _ISP_MOD_MASK_H_INC_

#include <rts_isp_geom.h>
#include <isp_utils.h>
#include <isp_define.h>

struct isp_mask_entry {
	enum rts_isp_geom_type type;
	int enable;
	union {
		struct {
			uint32_t max_cols;
			uint32_t max_rows;
			rts_isp_grid_t grid;
		};
		struct {
			rts_isp_prect_t rect;
		};
	};
};

struct isp_mask {
	uint32_t color; /* rgb888 */
	struct isp_mask_entry entries[ISP_MASK_NUM];
	uint8_t bitmap[ISP_MASK_GRID_NUM][(ISP_MASK_GRID_CELLS + 7) / 8];
};

enum isp_mod_mask_exec_type {
	MASK_EXEC_GET = isp_action_r(EXEC_TYPE, 0, struct isp_mask),
	MASK_EXEC_SET = isp_action_w(EXEC_TYPE, 1, struct isp_mask),
};

#endif /* _ISP_MOD_MASK_H_INC_ */

