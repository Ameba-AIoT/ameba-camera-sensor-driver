#ifndef _ISP_HW_LSC_H_INC_
#define _ISP_HW_LSC_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_nlsc_center {
	isp_iq_point_t r;
	isp_iq_point_t g;
	isp_iq_point_t b;
};

struct isp_hw_nlsc_ops {
	int (*set_nlsc)(uint32_t isp_id, const isp_iq_nlsc_common_t *nlsc);
	int (*set_adj)(uint32_t isp_id, const isp_iq_nlsc_adj_t *adj);
	int (*set_center)(uint32_t isp_id,
			  const struct isp_hw_nlsc_center *center);
};

const struct isp_hw_nlsc_ops *isp_hw_nlsc_get_ops(void);

#endif /* _ISP_HW_LSC_H_INC_ */

