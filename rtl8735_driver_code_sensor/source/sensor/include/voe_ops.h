#ifndef _VOE_OPS_H_INC_
#define _VOE_OPS_H_INC_

#include <stdint.h>

typedef struct voe_ops_s{
	// add new function after old function,
	// do not adjust order
	union{
		struct ops_s{
			int (*printf)(const char *, ...);
			
			void (*rts_isp_sensor_access_prepare)(void);
			void (*rts_isp_sensor_access_unprepare)(void);
			int  (*rts_isp_read_sensor_reg)(uint32_t isp_id, 
											struct rts_isp_i2c_reg *reg);
			int  (*rts_isp_write_sensor_reg)(uint32_t isp_id, 
											 struct rts_isp_i2c_reg *reg);
			
			int (*rts_isp_read_i2c_regs)(const struct rts_isp_i2c_info *info,
										 const struct rts_isp_i2c_regs *regs);
			int (*rts_isp_write_i2c_regs)(const struct rts_isp_i2c_info *info,
										  const struct rts_isp_i2c_regs *regs);
			int (*rts_isp_read_i2c_reg)(const struct rts_isp_i2c_info *info,
										struct rts_isp_i2c_reg *reg);
			int (*rts_isp_write_i2c_reg)(const struct rts_isp_i2c_info *info,
										 struct rts_isp_i2c_reg *reg);
			int (*rts_isp_sensor_get_open_mode)(void);
			int (*rts_isp_sensor_get_close_mode)(void);

			int (*hal_delay_us)(uint32_t);
			int (*isp_driver_mem_alloc)(uint32_t *phy_addr, uint32_t length, const char *info);
			int (*isp_driver_mem_free)(uint32_t);
			void* (*isp_driver_mmap)(uint32_t, uint32_t);
			int (*hal_isp_get_verify_info)(struct verify_ctrl_config *v_cfg);

			int (*sensor_get_slave_addr_idx)(void);

		} ops;
		unsigned char resv[192];	// 48*4
	}
}voe_ops_t;

#endif