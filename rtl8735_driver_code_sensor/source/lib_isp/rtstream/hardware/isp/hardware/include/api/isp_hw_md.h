#ifndef _ISP_HW_MD_H_INC_
#define _ISP_HW_MD_H_INC_

#include <stdint.h>

struct isp_hw_md_ops {
	int (*get_win_num)(uint32_t isp_id, uint16_t *ae_win_num,
				     uint16_t *awb_win_num);
};

const struct isp_hw_md_ops *isp_hw_md_get_ops(void);

#endif /* _ISP_HW_MD_H_INC_ */
