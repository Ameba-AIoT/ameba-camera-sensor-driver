/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_uds.h>
#include <isp_top.h>
#include <isp_mod.h>
#include <isp_mod_sensor.h>
#include <isp_mod_interface.h>

int rts_av_isp_enum_sensor_modes(uint32_t isp_id,
				 struct rts_isp_sensor_modes *modes)
{
	return isp_uds_message_simple(isp_id, MOD_SENSOR,
				      SENSOR_EXEC_ENUM_MODES,
				      modes, sizeof(*modes));
}

int rts_av_isp_get_sensor_mode(uint32_t isp_id,
			       struct rts_isp_sensor_mode *mode)
{
	return isp_uds_message_simple(isp_id, MOD_SENSOR, SENSOR_EXEC_GET_MODE,
				      mode, sizeof(*mode));
}

int rts_av_isp_set_sensor_mode(uint32_t isp_id,
			       struct rts_isp_sensor_mode *mode)
{
	return isp_uds_message_simple(isp_id, MOD_SENSOR, SENSOR_EXEC_SET_MODE,
				      mode, sizeof(*mode));
}