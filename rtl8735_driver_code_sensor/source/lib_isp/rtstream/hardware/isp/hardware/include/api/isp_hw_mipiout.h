#ifndef _ISP_HW_MIPIOUT_H_INC_
#define _ISP_HW_MIPIOUT_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>
#include <rtsavisp.h>

struct isp_mipiout_info {
	int is_fpga;
	uint32_t mipi_clk;
	rts_isp_size_t size;
	struct rts_isp_mipiout mipiout;
};

struct isp_hw_mipiout_ops {
	int (*set)(uint32_t isp_id, const struct isp_mipiout_info *info);
};

const struct isp_hw_mipiout_ops *isp_hw_mipiout_get_ops(void);

#endif /* _ISP_HW_MIPIOUT_H_INC_ */

