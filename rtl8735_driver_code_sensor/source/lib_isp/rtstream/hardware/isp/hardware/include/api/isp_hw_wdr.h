#ifndef _ISP_HW_WDR_H_INC_
#define _ISP_HW_WDR_H_INC_

#include <stdint.h>

#define WDR_LEVEL_CTRL_MIN 0
#define WDR_LEVEL_CTRL_DEF 50
#define WDR_LEVEL_CTRL_MAX 100

struct isp_hw_wdr_ops {
	int (*init_vreg)(uint32_t isp_id);
	int (*set_config)(uint32_t isp_id);
	int (*set_enable)(uint32_t isp_id, int enable);
	int (*set_level)(uint32_t isp_id, uint8_t level, int load_mode);
	uint8_t (*get_level)(uint32_t isp_id);
	int (*set_step)(uint32_t isp_id, uint16_t step);
	int (*get_iq_level)(uint32_t isp_id);
};

const struct isp_hw_wdr_ops *isp_hw_wdr_get_ops(void);

#endif /* _ISP_HW_WDR_H_INC_ */
