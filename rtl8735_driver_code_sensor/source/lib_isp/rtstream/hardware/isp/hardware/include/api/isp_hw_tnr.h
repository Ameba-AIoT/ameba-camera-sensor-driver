#ifndef _ISP_HW_TNR_H_INC_
#define _ISP_HW_TNR_H_INC_

#include <stdint.h>

struct isp_hw_tnr_ops {
	int (*set_ddr)(uint32_t isp_id, uint32_t addr, uint32_t len, int bit);
	int (*enable)(uint32_t isp_id, int enable);
	int (*enable_axi)(uint32_t isp_id, int enable);
	int (*estimation)(uint32_t isp_id);
	int (*dynamic)(uint32_t isp_id, float sensor_gain);
};

const struct isp_hw_tnr_ops *isp_hw_tnr_get_ops(void);

#endif /* _ISP_HW_TNR_H_INC_ */
