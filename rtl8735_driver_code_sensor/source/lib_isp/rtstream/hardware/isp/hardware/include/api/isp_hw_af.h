#ifndef _ISP_HW_AF_H_INC_
#define _ISP_HW_AF_H_INC_

#include <rts_isp_geom.h>

struct isp_af_hw_info {
	rts_isp_grid_info_t grid_info;
	rts_isp_size_t cell_sample;

	/* sizeof each statis entry */
	uint8_t win_edge_size;
};

struct isp_hw_af_ops {
	int (*get_hw_info)(uint32_t isp_id, struct isp_af_hw_info *info);
	int (*set_statis)(uint32_t isp_id, const rts_isp_grid_t *grid);
	int (*set_statis_th)(uint32_t isp_id, uint8_t statis_th);
};

const struct isp_hw_af_ops *isp_hw_af_get_ops(void);

#endif /* _ISP_HW_AF_H_INC_ */

