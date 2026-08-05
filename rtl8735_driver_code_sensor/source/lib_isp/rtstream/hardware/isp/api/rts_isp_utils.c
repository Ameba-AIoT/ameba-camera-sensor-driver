/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include <rts_isp.h>
#include <isp_driver.h>
#include <isp_top.h>
#include <isp_top_api.h>
#include <isp_uds.h>
#include <isp_mod.h>
#include <isp_mod_global.h>
#include <isp_mod_sensor.h>
#include <isp_mod_crop.h>
#include <isp_mod_mcrop.h>
#include <isp_mod_iq.h>
#include <isp_mod_mipiout.h>

int rts_isp_read_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg)
{
	//int ret;
 	//osThreadId_t pid;

	//ret = isp_top_get_pid_from_file(&pid);
	//if (ret)
	//	return ret;

	//if (pid == osThreadGetId())
		return isp_top_read_sensor_reg(isp_id, reg);
	//else if (!pid)
	//	return isp_uds_message_simple(isp_id, MOD_SENSOR,
	//			      SENSOR_EXEC_READ_SEN_REG,
	//			      reg, sizeof(*reg));
	//else {
	//	printf("ISP not enabled\n");
	//	return -RTS_ISP_ENOTREADY;
	//}
}

int rts_isp_write_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg)
{
	//int ret;
 	//osThreadId_t pid;

	//ret = isp_top_get_pid_from_file(&pid);
	//if (ret)
	//	return ret;

	//if (pid == osThreadGetId())
		return isp_top_write_sensor_reg(isp_id, reg);
	//else if (!pid)
	//	return isp_uds_message_simple(isp_id, MOD_SENSOR,
	//			      SENSOR_EXEC_WRITE_SEN_REG,
	//			      reg, sizeof(*reg));
	//else {
	//	printf("ISP not enabled\n");
	//	return -RTS_ISP_ENOTREADY;
	//}
}

void rts_isp_sensor_access_prepare(void)
{
	isp_driver_sync_lock(RTS_ISP_TRUE);
}

void rts_isp_sensor_access_unprepare(void)
{
	isp_driver_sync_lock(RTS_ISP_FALSE);
}

int rts_av_isp_get_mipiout(uint32_t isp_id, struct rts_isp_mipiout *mipiout)
{
	//if (!mipiout)
		return -RTS_ISP_EINVAL;
	//return isp_uds_message_simple(isp_id, MOD_MIPIOUT, MIPIOUT_EXEC_GET,
	//			      mipiout, sizeof(*mipiout));
}

int rts_av_isp_set_mipiout(uint32_t isp_id, struct rts_isp_mipiout *mipiout)
{
	//if (!mipiout)
		return -RTS_ISP_EINVAL;
	//return isp_uds_message_simple(isp_id, MOD_MIPIOUT, MIPIOUT_EXEC_SET,
	//			      mipiout, sizeof(*mipiout));
}

int rts_isp_get_image_size(uint32_t isp_id, struct rts_isp_image_size *size)
{
	int ret;
	struct rts_isp_interface_info interface_info;

	if (!size)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_SENSOR, SENSOR_INFO_INTERFACE,
				     &interface_info, sizeof(interface_info));
	if (ret)
		return ret;
	size->sensor_bit_depth = interface_info.bit_depth;
	ret = isp_uds_message_simple(isp_id, MOD_SENSOR, SENSOR_INFO_SIZE,
				     &size->sensor_size,
				     sizeof(size->sensor_size));
	if (ret)
		return ret;
	ret = isp_uds_message_simple(isp_id, MOD_CROP, CROP_INFO_ISP_SIZE,
				     &size->isp_middle_size,
				     sizeof(size->isp_middle_size));
	if (ret)
		return ret;
	return isp_uds_message_simple(isp_id, MOD_MCROP, MCROP_INFO_ISP_SIZE,
				      &size->isp_final_size,
				      sizeof(size->isp_final_size));
}

int rts_isp_get_bypass(uint32_t isp_id, struct rts_isp_bypass *bypass)
{
	return isp_uds_message_simple(isp_id, MOD_GLOBAL,
				      GLOBAL_EXEC_GET_BYPASS,
				      bypass, sizeof(*bypass));
}

int rts_isp_set_bypass(uint32_t isp_id, struct rts_isp_bypass *bypass)
{
	return isp_uds_message_simple(isp_id, MOD_GLOBAL,
				      GLOBAL_EXEC_SET_BYPASS,
				      bypass, sizeof(*bypass));
}

const char *rts_isp_get_bound_sensor_name(uint32_t isp_id)
{
	int ret;
	static char name[_ISP_ID_NUM][32];

	if (isp_id >= _ISP_ID_NUM)
		return NULL;

	ret = isp_uds_message_simple(isp_id, MOD_SENSOR,
				     SENSOR_INFO_BOUND_SNR_NAME,
				     name[isp_id], sizeof(name[isp_id]));
	if (ret)
		return NULL;
	return name[isp_id];
}

int rts_isp_test_preview(int fps)
{
	return isp_driver_test_preview(fps);
}

int rts_av_isp_get_plugins_version(uint32_t isp_id,
				   struct rts_isp_plugins_version *version)
{
	return isp_uds_message_simple(isp_id, MOD_IQ,
				      IQ_INFO_PLUGINS_VERSION,
				      version, sizeof(*version));
}

