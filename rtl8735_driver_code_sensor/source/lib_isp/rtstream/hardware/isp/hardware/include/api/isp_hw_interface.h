#ifndef _ISP_HW_INTERFACE_H_INC_
#define _ISP_HW_INTERFACE_H_INC_

#include <rts_isp_sensor.h>

struct isp_interface_info {
	enum rts_isp_sensor_hdr_mode mode;
	struct rts_isp_hdr_info hdr;
	const struct rts_isp_interface_info *info;
	rts_isp_size_t size;
	uint32_t pixel_clk;
	uint32_t interface_clk;
	int is_fpga;
};

struct isp_hw_interface_ops {
	int (*start_transfer)(uint32_t isp_id,
			      const struct isp_interface_info *info);
	int (*stop_transfer)(uint32_t isp_id,
			     const struct isp_interface_info *info);
};

int isp_driver_i2c_write(const struct rts_isp_i2c *i2c);
int isp_driver_aphy_i2c_write(const struct rts_isp_i2c *i2c);

const struct isp_hw_interface_ops *isp_hw_dvp_get_ops(void);
const struct isp_hw_interface_ops *isp_hw_mipi_get_ops(void);
const struct isp_hw_interface_ops *isp_hw_fixp_get_ops(void);
const struct isp_hw_interface_ops *isp_hw_vinf_get_ops(void);

#endif /* _ISP_HW_INTERFACE_H_INC_ */
