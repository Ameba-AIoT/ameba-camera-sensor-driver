#ifndef _ISP_HW_DEHAZE_H_INC_
#define _ISP_HW_DEHAZE_H_INC_

#include <rts_isp_geom.h>

#define DEHAZE_LEVEL_CTRL_MIN 0
#define DEHAZE_LEVEL_CTRL_DEF 128
#define DEHAZE_LEVEL_CTRL_MAX 255

struct isp_hw_dehaze_ops {
	int (*init)(uint32_t isp_id, const rts_isp_rect_t *rect);
	int (*init_vreg)(uint32_t);
	int (*set_enable)(uint32_t isp_id, int enable);
	int (*set_level)(uint32_t isp_id, int level);
	//int (*get_iq_level)(uint32_t isp_id);
};

const struct isp_hw_dehaze_ops *isp_hw_dehaze_get_ops(void);

#endif /* _ISP_HW_DEHAZE_H_INC_ */

