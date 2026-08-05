#ifndef _ISP_HW_TM_H_INC_
#define _ISP_HW_TM_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

#define EDGE_LUMA_THD_NUM 11

struct isp_hw_tm_ops {
	int (*set_enable)(uint32_t isp_id, int enable);
	int (*set_target)(uint32_t isp_id, const isp_iq_tm_item_t *tm);
	int (*set_edge_thd_long)(uint32_t isp_id, const isp_iq_tm_item_t *tm);
	int (*set_edge_thd_short)(uint32_t isp_id, const isp_iq_tm_item_t *tm);
	int (*set_edge_param)(uint32_t isp_id, const isp_iq_tm_item_t *tm);
};

const struct isp_hw_tm_ops *isp_hw_tm_get_ops(void);

#endif /* _ISP_HW_TM_H_INC_ */
