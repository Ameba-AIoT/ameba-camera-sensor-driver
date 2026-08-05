#ifndef _ISP_HW_MCROP_H_INC_
#define _ISP_HW_MCROP_H_INC_

#include <rts_isp_geom.h>

struct isp_hw_mcrop_ops {
	int (*set_crop)(uint32_t isp_id, rts_isp_rect_t *rect);
};

const struct isp_hw_mcrop_ops *isp_hw_mcrop_get_ops(void);

#endif /* _ISP_HW_MCROP_H_INC_ */
