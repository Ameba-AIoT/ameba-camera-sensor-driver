#ifndef _ISP_SENSOR_H_INC_
#define _ISP_SENSOR_H_INC_

#include <rts_isp_sensor.h>
#include <rts_camera_isp_info.h>
#include <rtsavisp.h>
#include <isp_list.h>
#include <isp_plugin.h>

#define ISP_MAX_SENSOR_NUM 4

struct isp_sensor_attr {
	struct isp_plugin plugin;
	int sensor_id;
};

struct isp_sensor_manager {
	struct isp_sensor_attr *sensors[ISP_MAX_SENSOR_NUM];
	int binding[_ISP_ID_NUM];
};

int isp_sensor_init(struct isp_sensor_manager *snrm);
int isp_sensor_cleanup(struct isp_sensor_manager *snrm);
int isp_sensor_register(struct isp_sensor_manager *snrm,
			const struct rts_isp_sensor *sensor);
int isp_sensor_unregister(struct isp_sensor_manager *snrm, int sensor_id);
int isp_sensor_get(struct isp_sensor_manager *snrm, int sensor_id,
		   struct rts_isp_sensor *sensor);
int isp_sensor_check(struct isp_sensor_manager *snrm,
		     uint32_t isp_id, int sensor_id);
int isp_sensor_bind(struct isp_sensor_manager *snrm, uint32_t isp_id,
		    int sensor_id);
int isp_sensor_unbind(struct isp_sensor_manager *snrm, uint32_t isp_id,
		      int sensor_id);
int isp_sensor_check_all_bound(struct isp_sensor_manager *snrm);
int isp_sensor_get_ops(struct isp_sensor_manager *snrm, uint32_t isp_id,
		       const struct rts_isp_sensor_ops **sensor_ops);
int isp_sensor_get_info(struct isp_sensor_manager *snrm, uint32_t isp_id,
			struct rts_isp_info *info);
int isp_sensor_read_reg(struct isp_sensor_manager *snrm, uint32_t isp_id,
			struct rts_isp_i2c_reg *reg);
int isp_sensor_write_reg(struct isp_sensor_manager *snrm, uint32_t isp_id,
			 struct rts_isp_i2c_reg *reg);

#endif /* _ISP_SENSOR_H_INC_ */
