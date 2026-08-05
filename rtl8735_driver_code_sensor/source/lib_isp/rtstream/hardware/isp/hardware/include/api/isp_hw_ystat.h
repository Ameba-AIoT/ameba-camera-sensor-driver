#ifndef _ISP_HW_YSTAT_H_INC_
#define _ISP_HW_YSTAT_H_INC_

#include <rts_isp_geom.h>

struct isp_ystat_hw_info {
	rts_isp_grid_info_t grid_info;
	rts_isp_size_t cell_sample;

	//uint32_t hist_nums;
	uint16_t hist_bins;
	rts_isp_size_t hist_sample;

	/* sizeof each statis entry */
	uint8_t y_mean_size;
	uint8_t hist_bin_size;
};

struct isp_hw_ystat_ops {
	int (*get_hw_info)(uint32_t isp_id, struct isp_ystat_hw_info *info);
	int (*set_statis)(uint32_t isp_id, const rts_isp_grid_t *grid);
	//int (*get_hist_num)(uint32_t isp_id);
};

const struct isp_hw_ystat_ops *isp_hw_ystat_get_ops(void);

#endif /* _ISP_HW_YSTAT_H_INC_ */

