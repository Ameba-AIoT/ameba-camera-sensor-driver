/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <glob.h>
#include <rtsavisp.h>

#define SENSOR_PATH "/usr/lib/rtsisp/sensors/libsensor_sc3235.so"

static int register_bind_sensor(uint32_t isp_id)
{
	int ret;

	int sensor_id;
	const struct rts_isp_sensor sensor = {
		.path = SENSOR_PATH,
	};

	sensor_id = rts_av_isp_register_sensor(&sensor);
	if (sensor_id < 0) {
		ret = sensor_id;
		goto out;
	}
	ret = rts_av_isp_bind_sensor(isp_id, sensor_id);
	if (ret)
		rts_av_isp_unregister_sensor(sensor_id);

out:
	if (ret)
		rts_isp_perror(ret, "register sensor iq fail");
	return ret;
}

int cmd_test_check_sensor(int argc, char *argv[])
{
#if 0
	int ret;

	signal(SIGPIPE, SIG_IGN);

	ret = rts_av_isp_init();
	if (ret) {
		rts_isp_perror(ret, "init isp fail");
		return ret;
	}
	ret = register_bind_sensor(ISP0);
	if (ret) {
		rts_isp_perror(ret, "register and bind sensor fail");
		return ret;
	}
	rts_av_isp_cleanup();
#endif
	return 0;
}
