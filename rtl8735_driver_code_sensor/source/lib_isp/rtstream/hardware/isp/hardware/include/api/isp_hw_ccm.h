#ifndef _ISP_HW_CCM_H_INC_
#define _ISP_HW_CCM_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_ccm_ops {
	int (*set_ccm)(uint32_t isp_id, const isp_iq_ccm_item_t *ccm);
	int (*update_cac)(uint32_t isp_id);
};

const struct isp_hw_ccm_ops *isp_hw_ccm_get_ops(void);

#endif /* _ISP_HW_CCM_H_INC_ */
