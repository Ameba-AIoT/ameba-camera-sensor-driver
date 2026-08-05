#ifndef _ISP_HW_RGB2YUV_H_INC_
#define _ISP_HW_RGB2YUV_H_INC_

#include <stdint.h>

struct isp_hw_rgb2yuv_ops {
	int (*init)(uint32_t isp_id);
	int (*convert)(uint32_t isp_id, uint32_t *rgb2yuv);
};

const struct isp_hw_rgb2yuv_ops *isp_hw_rgb2yuv_get_ops(void);

#endif /* _ISP_HW_RGB2YUV_H_INC_ */

