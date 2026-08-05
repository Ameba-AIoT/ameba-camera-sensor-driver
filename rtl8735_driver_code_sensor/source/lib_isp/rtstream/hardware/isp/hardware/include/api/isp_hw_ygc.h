#ifndef _ISP_HW_YGC_H_INC_
#define _ISP_HW_YGC_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_ygc_ops {
	int (*set_ygc)(uint32_t isp_id, const isp_iq_ygc_item_t *ygc);
};

const struct isp_hw_ygc_ops *isp_hw_ygc_get_ops(void);

#endif /* _ISP_HW_YGC_H_INC_ */

