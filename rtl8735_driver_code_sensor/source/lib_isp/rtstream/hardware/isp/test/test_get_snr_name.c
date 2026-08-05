/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>

int cmd_test_get_snr_name(int argc, char *argv[])
{
	const char *bound_sensor_name;

	bound_sensor_name = rts_isp_get_bound_sensor_name(ISP0);
	if (!bound_sensor_name) {
		printf("get bound sensor name fail\n");
		exit(EFAULT);
	}
	printf("current bound sensor name: %s\n", bound_sensor_name);
	return 0;
}

