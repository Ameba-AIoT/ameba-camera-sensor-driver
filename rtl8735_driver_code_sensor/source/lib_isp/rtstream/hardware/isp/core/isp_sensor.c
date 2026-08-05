/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_driver.h>
#include <isp_sensor.h>
//#include <isp_core.h>
//#include <isp_mod.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_SENSOR

static int sensor_check(struct isp_sensor_manager *snrm,
			const struct rts_isp_sensor *sensor)
{
	int i;
	struct isp_sensor_attr **attr;

	if (!snrm || !sensor || !sensor->path)
		return -RTS_ISP_EINVAL;

	attr = snrm->sensors;
	for (i = 0; i < ISP_MAX_SENSOR_NUM; i++) {
		if (!attr[i])
			continue;
		if (strcmp(attr[i]->plugin.path, sensor->path) == 0)
			return -RTS_ISP_EEXIST;
	}

	return RTS_ISP_OK;
}

static int sensor_find_sensor_slot(struct isp_sensor_manager *snrm)
{
	int i;
	struct isp_sensor_attr **attr;

	attr = snrm->sensors;
	for (i = 0; i < ISP_MAX_SENSOR_NUM; i++)
		if (!attr[i])
			return i;

	return -RTS_ISP_ENOSPC;
}

static int sensor_find_sensor_avalible(struct isp_sensor_manager *snrm,
				       int exclude)
{
	int i;
	struct isp_sensor_attr **attr;

	attr = snrm->sensors;
	for (i = 0; i < ISP_MAX_SENSOR_NUM; i++)
		if (attr[i] && attr[i]->sensor_id != exclude)
			return i;

	return -1;
}

static int sensor_cleanup(struct isp_sensor_manager *snrm, int index)
{
	uint32_t isp_id;
	struct isp_sensor_attr **attr;

	attr = snrm->sensors;
	if (!attr[index])
		return RTS_ISP_OK;

	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		if (snrm->binding[isp_id] == index)
			isp_sensor_unbind(snrm, isp_id, index);
	isp_sensor_unregister(snrm, attr[index]->sensor_id);

	return RTS_ISP_OK;
}

static int sensor_get_i2c_info(struct isp_sensor_manager *snrm, uint32_t isp_id,
			       struct rts_isp_i2c_info *info)
{
	int ret;
	struct rts_isp_sensor_info snr_info;
	const struct rts_isp_sensor_ops *ops;

	ret = isp_sensor_get_ops(snrm, isp_id, &ops);
	if (ret)
		return ret;
	ret = ops->get_info(isp_id, &snr_info);
	if (ret)
		return ret;
	*info = snr_info.i2c;
	return RTS_ISP_OK;
}

int isp_sensor_init(struct isp_sensor_manager *snrm)
{
	uint32_t isp_id;

	if (!snrm)
		return -RTS_ISP_EINVAL;

	memset(snrm, 0, sizeof(*snrm));
	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		snrm->binding[isp_id] = -1;

	return RTS_ISP_OK;
}

int isp_sensor_cleanup(struct isp_sensor_manager *snrm)
{
	int index;

	if (!snrm)
		return -RTS_ISP_EINVAL;

	for (index = 0; index < ISP_MAX_SENSOR_NUM; index++)
		sensor_cleanup(snrm, index);
	//debug("%s ok\n", __func__);

	return RTS_ISP_OK;
}

extern void* __get_sensor_ops__[];

int isp_sensor_register(struct isp_sensor_manager *snrm,
			const struct rts_isp_sensor *sensor)
{
	int index;
	int ret;
	struct isp_sensor_attr *new_attr;
	const char *func = "rts_isp_get_sensor_ops";

	if (!snrm)
		return -RTS_ISP_EINVAL;
	ret = sensor_check(snrm, sensor);
	if (ret)
		return ret;
	index = sensor_find_sensor_slot(snrm);
	if (index < 0)
		return index;

	if (!isp_calloc_item(new_attr))
		return -RTS_ISP_ENOMEM;
	new_attr->sensor_id = index;

	void* (*_rts_isp_get_sensor_ops)(void) = ( void* (*)(void))(__get_sensor_ops__[0]);
	new_attr->plugin.ops_handle = _rts_isp_get_sensor_ops();

	snrm->sensors[index] = new_attr;

	debug("register sensor %s %s with id = %d ok\n",
	      sensor->path, func, new_attr->sensor_id);

	return new_attr->sensor_id;
}

int isp_sensor_unregister(struct isp_sensor_manager *snrm, int sensor_id)
{
	uint32_t isp_id;
	struct isp_sensor_attr **attr;

	if (!snrm || sensor_id < 0 || sensor_id >= ISP_MAX_SENSOR_NUM)
		return -RTS_ISP_EINVAL;

	attr = snrm->sensors;
	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		if (snrm->binding[isp_id] == sensor_id)
			return -RTS_ISP_EBUSY;

	attr[sensor_id]->plugin.ops_handle = (void*)NULL;
	isp_free(attr[sensor_id]);

	//debug("unregister sensor %d ok\n", sensor_id);

	return RTS_ISP_OK;
}

int isp_sensor_get(struct isp_sensor_manager *snrm, int sensor_id,
		   struct rts_isp_sensor *sensor)
{
	struct isp_sensor_attr **attr;

	//if (!snrm || !sensor || sensor_id < 0 || sensor_id > ISP_MAX_SENSOR_NUM)
	if (!snrm || !sensor || sensor_id < 0 ||
		sensor_id >= ISP_MAX_SENSOR_NUM)
		return -RTS_ISP_EINVAL;
	attr = snrm->sensors;
	if (!attr[sensor_id])
		return -RTS_ISP_EINVAL;

	sensor->path = attr[sensor_id]->plugin.path;

	return RTS_ISP_OK;
}

int isp_sensor_check(struct isp_sensor_manager *snrm,
		     uint32_t isp_id, int sensor_id)
{
	int ret;
	int sensor_id_backup;
	const struct rts_isp_sensor_ops *ops;
	struct rts_isp_sensor_info info;

	if (!snrm || isp_id > _ISP_ID_NUM ||
	    sensor_id < 0 || sensor_id >= ISP_MAX_SENSOR_NUM)
		return -RTS_ISP_EINVAL;

	sensor_id_backup = snrm->binding[isp_id];
	snrm->binding[isp_id] = sensor_id;

	ret = isp_sensor_get_ops(snrm, isp_id, &ops);
	if (ret)
		goto out_bind;
	if (!ops->get_info || !ops->check) {
		ret = -RTS_ISP_ENOOPS;
		goto out_bind;
	}
	if (ops->init) {
		ret = ops->init(isp_id);
		if (ret)
			goto out_bind;
	}
	ret = ops->get_info(isp_id, &info);
	if (ret)
		goto out_init;
	ret = isp_driver_set_power(&info.power_up);
	if (ret)
		goto out_power;
	ret = ops->check(isp_id);

out_power:
	isp_driver_set_power(&info.power_down);
out_init:
	if (ops->cleanup)
		ops->cleanup(isp_id);
out_bind:
	snrm->binding[isp_id] = sensor_id_backup;
	return ret;
}

int isp_sensor_bind(struct isp_sensor_manager *snrm,
		    uint32_t isp_id, int sensor_id)
{
	struct isp_sensor_attr **attr;
	const struct rts_isp_sensor_ops *ops;

	if (!snrm || isp_id >= _ISP_ID_NUM ||
	    sensor_id < 0 || sensor_id >= ISP_MAX_SENSOR_NUM)
		return -RTS_ISP_EINVAL;
	attr = snrm->sensors;
	if (!attr[sensor_id])
		return -RTS_ISP_EINVAL;
	ops = attr[sensor_id]->plugin.ops_handle;
	if (!ops)
		return -RTS_ISP_EINVAL;

	snrm->binding[isp_id] = sensor_id;

	//isp_info("bind sensor %s to isp%d\n", ops->name, isp_id);

	return RTS_ISP_OK;
}

int isp_sensor_unbind(struct isp_sensor_manager *snrm,
		      uint32_t isp_id, int sensor_id)
{
	//const struct rts_isp_sensor_ops *ops;

	if (!snrm || isp_id >= _ISP_ID_NUM ||
	    sensor_id < 0 || sensor_id >= ISP_MAX_SENSOR_NUM)
		return -RTS_ISP_EINVAL;

	if (snrm->binding[isp_id] != sensor_id)
		return RTS_ISP_OK;
	snrm->binding[isp_id] = sensor_find_sensor_avalible(snrm, sensor_id);

	//ops = snrm->sensors[sensor_id]->plugin.ops_handle;
	//isp_info("unbind sensor %s from isp%d\n", ops->name, isp_id);

	return RTS_ISP_OK;
}

int isp_sensor_check_all_bound(struct isp_sensor_manager *snrm)
{
	uint32_t isp_id;

	if (!snrm)
		return -RTS_ISP_EINVAL;

	for (isp_id = 0; isp_id < _ISP_ID_NUM; isp_id++)
		if (snrm->binding[isp_id] == -1)
			return -RTS_ISP_ENOTREADY;
	return RTS_ISP_OK;
}

int isp_sensor_get_ops(struct isp_sensor_manager *snrm, uint32_t isp_id,
		       const struct rts_isp_sensor_ops **sensor_ops)
{
	int index;

	if (!snrm || isp_id >= _ISP_ID_NUM || !sensor_ops)
		return -RTS_ISP_EINVAL;

	index = snrm->binding[isp_id];
	if (index < 0 || index >= ISP_MAX_SENSOR_NUM)
		*sensor_ops = NULL;
	else
		*sensor_ops = snrm->sensors[index]->plugin.ops_handle;
	if (!*sensor_ops)
		return -RTS_ISP_ENOTREADY;

	return RTS_ISP_OK;
}

int isp_sensor_get_info(struct isp_sensor_manager *snrm, uint32_t isp_id,
			struct rts_isp_info *info)
{
	int ret;
	struct rts_isp_sensor_info snr_info;
	const struct rts_isp_sensor_ops *ops;
	enum rts_isp_sensor_hdr_mode cur_hdr_mode;

	if (!snrm || isp_id >= _ISP_ID_NUM || !info)
		return -RTS_ISP_EINVAL;

	ret = isp_sensor_get_ops(snrm, isp_id, &ops);
	if (ret)
		return ret;
	if (!ops)
		return -RTS_ISP_ENOTREADY;
	ret = ops->get_info(isp_id, &snr_info);
	if (ret)
		return ret;
	cur_hdr_mode = snr_info.cur_hdr_mode;
	printf("cur_hdr_mode = %d\n", cur_hdr_mode);
	info->width = snr_info.modes.mode[cur_hdr_mode].size.w;
	info->height = snr_info.modes.mode[cur_hdr_mode].size.h;
	info->fps = (u32) snr_info.modes.mode[cur_hdr_mode].fps;

	return RTS_ISP_OK;
}

int isp_sensor_read_reg(struct isp_sensor_manager *snrm, uint32_t isp_id,
			struct rts_isp_i2c_reg *reg)
{
	int ret;
	struct rts_isp_i2c_info info;

	ret = sensor_get_i2c_info(snrm, isp_id, &info);
	if (ret)
		return ret;
	return rts_isp_read_i2c_reg(&info, reg);
}

int isp_sensor_write_reg(struct isp_sensor_manager *snrm, uint32_t isp_id,
			 struct rts_isp_i2c_reg *reg)
{
	int ret;
	struct rts_isp_i2c_info info;

	ret = sensor_get_i2c_info(snrm, isp_id, &info);
	if (ret)
		return ret;
	return rts_isp_write_i2c_reg(&info, reg);
}
