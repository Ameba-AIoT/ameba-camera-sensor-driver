#ifndef _ISP_HW_STATIS_H_INC_
#define _ISP_HW_STATIS_H_INC_

#include <stdint.h>
#include "rts_isp_sensor.h"

struct isp_hw_statis_ops {
	int (*enable)(uint32_t isp_id, int enable, enum rts_isp_sensor_hdr_mode);
};

const struct isp_hw_statis_ops *isp_hw_statis_get_ops(void);

#endif /* _ISP_HW_STATIS_H_INC_ */

