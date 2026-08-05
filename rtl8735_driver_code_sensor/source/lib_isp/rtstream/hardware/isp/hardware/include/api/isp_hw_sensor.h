#ifndef _ISP_HW_SENSOR_H_INC_
#define _ISP_HW_SENSOR_H_INC_

#include <stdint.h>

struct isp_hw_sensor_ops {
	int (*get_mirror_flip)(uint32_t isp_id, uint8_t *mirror_en, uint8_t *flip_en);
	int (*set_mirror_flip)(uint32_t isp_id, uint8_t mirror_en, uint8_t flip_en);
	int (*init_vreg)(uint32_t isp_id);
};

const struct isp_hw_sensor_ops *isp_hw_sensor_get_ops(void);

#endif /* _ISP_HW_SENSOR_H_INC_ */

