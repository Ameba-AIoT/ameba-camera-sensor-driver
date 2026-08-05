#ifndef _ISP_HW_FLICK_H_INC_
#define _ISP_HW_FLICK_H_INC_

#include <rts_isp_geom.h>

struct isp_hw_flick_ops {
	int (*set_statis)(uint32_t isp_id, const rts_isp_rect_t *rect);
};

const struct isp_hw_flick_ops *isp_hw_flick_get_ops(void);

#endif /* _ISP_HW_FLICK_H_INC_ */

