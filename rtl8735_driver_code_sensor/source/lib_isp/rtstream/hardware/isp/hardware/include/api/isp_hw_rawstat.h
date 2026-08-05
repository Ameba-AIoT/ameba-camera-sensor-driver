#ifndef _ISP_HW_RAWSTAT_H_INC_
#define _ISP_HW_RAWSTAT_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>
#include <rts_isp_other.h>

struct isp_rawstat_hw_info {
	rts_isp_grid_info_t grid_info;
	rts_isp_size_t cell_sample;

	/* sizeof each statis entry */
	uint8_t rgby_size;
	uint8_t rgbg_size;
	uint8_t pixels_size;
};

struct isp_hw_rawstat_ops {
	int (*get_hw_info)(uint32_t isp_id, struct isp_rawstat_hw_info *info);
	int (*set_statis)(uint32_t isp_id, const rts_isp_grid_t *grid);
};

const struct isp_hw_rawstat_ops *isp_hw_rawstat_get_ops(void);

#endif /* _ISP_HW_RAWSTAT_H_INC_ */

