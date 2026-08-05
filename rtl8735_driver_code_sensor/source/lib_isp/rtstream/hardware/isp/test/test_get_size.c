/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>

int cmd_test_get_size(int argc, char *argv[])
{
	int ret;
	struct rts_isp_image_size size;

	ret = rts_isp_get_image_size(ISP0, &size);
	if (ret) {
		rts_isp_perror(ret, "get isp image size fail");
		return ret;
	}
	printf("sensor bit depth: %d\n", size.sensor_bit_depth);
	printf("sensor size: %ux%u\n", (unsigned int)size.sensor_size.w, (unsigned int)size.sensor_size.h);
	printf("isp middle size: %ux%u\n",
	       (unsigned int)size.isp_middle_size.w, (unsigned int)size.isp_middle_size.h);
	printf("isp final size: %ux%u\n",
	       (unsigned int)size.isp_final_size.w, (unsigned int)size.isp_final_size.h);
	return 0;
}
