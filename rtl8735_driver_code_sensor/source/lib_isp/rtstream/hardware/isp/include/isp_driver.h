#ifndef _ISP_DRIVER_H_INC_
#define _ISP_DRIVER_H_INC_

#include <rts_camera_isp_info.h>
#include <rts_isp_sensor.h>

enum isp_clock_type {
	CLK_ISP,
	CLK_INTERFACE,
	CLK_MIPIOUT,
};

enum isp_event {
	ISP_DATA_START,
	ISP_FRAME_END,
};

int isp_driver_init(void);
void isp_driver_cleanup(void);
int isp_driver_stream_add(void *p);
int isp_driver_set_power(const struct rts_isp_snr_pwr *pwr);
int isp_driver_register_subdev(const struct rts_isp_info *info);
int isp_driver_unregister_subdev(void);
int isp_driver_write_sync_regs(const struct rts_isp_sync_regs *regs);
int isp_driver_init_statis(uint32_t size);
int isp_driver_cleanup_statis(void);
int isp_driver_get_statis_info(struct rts_isp_statis_info *info);
int isp_driver_put_statis(uint32_t id);
int isp_driver_i2c_read(struct rts_isp_i2c *i2c);
int isp_driver_i2c_write(const struct rts_isp_i2c *i2c);
int isp_driver_aphy_i2c_write(const struct rts_isp_i2c *i2c);
int isp_driver_mem_alloc(uint32_t *phy_addr, uint32_t length, const char *info);
int isp_driver_mem_free(uint32_t phy_addr);
void *isp_driver_mmap(uint32_t start, uint32_t size);
int isp_driver_sel_pin_state(enum rts_isp_interface interface);
int isp_driver_notify_dynamic_fps(uint32_t fps);
int isp_driver_set_clk(enum isp_clock_type type, uint32_t *rate);
void isp_driver_isp_clk_get(void);
void isp_driver_isp_clk_put(void);
int isp_driver_is_fpga(void);
void isp_driver_wait_event(enum isp_event event);
void isp_driver_sync_lock(int lock);
int isp_driver_get_tnr_bit(void);
int isp_driver_test_preview(uint32_t fps);

#endif /* _ISP_DRIVER_H_INC_ */
