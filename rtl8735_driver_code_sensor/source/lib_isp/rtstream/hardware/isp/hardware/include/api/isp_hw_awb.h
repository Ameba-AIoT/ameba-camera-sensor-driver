#ifndef _ISP_HW_AWB_H_INC_
#define _ISP_HW_AWB_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>
#include <rts_isp_awb.h>

struct isp_awb_hw_info {
	rts_isp_grid_info_t grid_info;
	rts_isp_size_t cell_sample;

	/* sizeof each statis entry */
	uint8_t rgby_size;
	uint8_t rgbg_size;
	uint8_t pixels_size;
};

struct isp_hw_awb_ops {
	int (*get_hw_info)(uint32_t isp_id, struct isp_awb_hw_info *info);
	int (*set_statis)(uint32_t isp_id, const rts_isp_grid_t *grid);
	int (*set_statis_config)(uint32_t isp_id,
				 const struct rts_isp_awb_stat_config *config);
	int (*set_final_gain)(uint32_t isp_id,
			      const struct rts_isp_awb_gain *gain);
	int (*set_clip)(uint32_t isp_id, int enable)
};

const struct isp_hw_awb_ops *isp_hw_awb_get_ops(void);

#endif /* _ISP_HW_AWB_H_INC_ */

