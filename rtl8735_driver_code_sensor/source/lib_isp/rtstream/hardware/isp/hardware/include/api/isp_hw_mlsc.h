#ifndef _ISP_HW_MLSC_H_INC_
#define _ISP_HW_MLSC_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_mlsc_ops {
	int (*set_mlsc)(uint32_t isp_id, const isp_iq_mlsc_t *mlsc);
};

const struct isp_hw_mlsc_ops *isp_hw_mlsc_get_ops(void);

#endif /* _ISP_HW_MLSC_H_INC_ */
