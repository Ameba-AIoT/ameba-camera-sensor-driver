#ifndef _ISP_TOP_API_H_INC_
#define _ISP_TOP_API_H_INC_

#include <unistd.h>
#include <rtsavisp.h>
#include <rts_isp_sensor.h>

int isp_top_init(uint8_t fcs_ready, uint32_t hdr_mode, uint32_t mirflp_mode, uint8_t tnr_en);
int isp_top_cleanup(void);
int isp_top_start(void);
int isp_top_stop(void);
int isp_top_status(void);

int isp_top_register_algo(const struct rts_isp_algo *algo);
int isp_top_unregister_algo(enum rts_isp_algo_id id);
int isp_top_get_algo(struct rts_isp_algo *algo);
int isp_top_bind_algo(int isp_id, int id);
int isp_top_unbind_algo(int isp_id, int id);

int isp_top_register_sensor(const struct rts_isp_sensor *sensor);
int isp_top_unregister_sensor(int sensor_id);
int isp_top_get_sensor(int sensor_id, struct rts_isp_sensor *sensor);
int isp_top_check_sensor(uint32_t isp_id, int sensor_id);
int isp_top_bind_sensor(uint32_t isp_id, int sensor_id);
int isp_top_unbind_sensor(uint32_t isp_id, int sensor_id);

int isp_top_register_iq(uint32_t isp_id, const char *path);
int isp_top_set_iq_calb_data(uint32_t isp_id, struct isp_iq_calb *data);
int isp_top_set_iq_calb_en(uint32_t isp_id, uint8_t en);

int isp_top_get_pid_from_file(osThreadId_t *pid);

int isp_top_read_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);
int isp_top_write_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);

#endif /* _ISP_TOP_API_H_INC_ */
