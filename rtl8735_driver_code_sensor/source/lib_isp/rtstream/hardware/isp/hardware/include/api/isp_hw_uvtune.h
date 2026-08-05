#ifndef _ISP_HW_UVTUNE_H_INC_
#define _ISP_HW_UVTUNE_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_uvtune_ops {
	int (*set_regs)(uint32_t isp_id, const isp_iq_uvtune_item_t *item);
	int (*estimation)(uint32_t isp_id);
};

const struct isp_hw_uvtune_ops *isp_hw_uvtune_get_ops(void);

#endif /* _ISP_HW_UVTUNE_H_INC_ */

