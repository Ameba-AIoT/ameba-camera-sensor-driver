#ifndef _ISP_HW_YGAMMA_H_INC_
#define _ISP_HW_YGAMMA_H_INC_

#include <stdint.h>

struct isp_hw_ygamma_ops {
	int (*set_ygamma)(uint32_t isp_id, const uint8_t *ygamma, int num);
};

const struct isp_hw_ygamma_ops *isp_hw_ygamma_get_ops(void);

#endif /* _ISP_HW_YGAMMA_H_INC_ */

