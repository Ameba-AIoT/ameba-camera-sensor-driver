#ifndef _ISP_HW_BLC_H_INC_
#define _ISP_HW_BLC_H_INC_

#include <rts_isp_geom.h>
#include <isp_iq_table.pb.h>

struct isp_hw_blc_ops {
	int (*get_num)(uint32_t isp_id);
	int (*set)(uint32_t isp_id, const isp_iq_blc_offset_t *blc, int bits);
};

const struct isp_hw_blc_ops *isp_hw_blc_get_ops(void);

#endif /* _ISP_HW_BLC_H_INC_ */
