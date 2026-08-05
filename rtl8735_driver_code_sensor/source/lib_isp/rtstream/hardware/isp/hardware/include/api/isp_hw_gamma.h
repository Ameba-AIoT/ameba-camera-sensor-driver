#ifndef _ISP_HW_GAMMA_H_INC_
#define _ISP_HW_GAMMA_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_gamma_ops {
	int (*set_gamma)(uint32_t isp_id, const isp_iq_gamma_item_t *gamma);
};

const struct isp_hw_gamma_ops *isp_hw_gamma_get_ops(void);

#endif /* _ISP_HW_GAMMA_H_INC_ */

