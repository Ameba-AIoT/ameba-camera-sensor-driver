/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>

int cmd_test_bypass(int argc, char *argv[])
{
	int ret;
	struct rts_isp_bypass bypass;

	ret = rts_isp_get_bypass(ISP0, &bypass);
	if (ret) {
		rts_isp_perror(ret, "get isp bypass fail");
		return ret;
	}
	bypass.all = ~0x0;
	ret = rts_isp_set_bypass(ISP0, &bypass);
	if (ret) {
		rts_isp_perror(ret, "set isp bypass fail");
		return ret;
	}
	printf("press enter to resume bypass...");
	getchar();
	bypass.all = 0;
	ret = rts_isp_set_bypass(ISP0, &bypass);
	if (ret) {
		rts_isp_perror(ret, "resume isp bypass fail");
		return ret;
	}
	return 0;
}
