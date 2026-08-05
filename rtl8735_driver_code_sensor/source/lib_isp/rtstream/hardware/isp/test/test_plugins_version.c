/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>

int cmd_test_plugins_version(int argc, char *argv[])
{
	int ret;
	struct rts_isp_plugins_version version;

	ret = rts_av_isp_get_plugins_version(ISP0, &version);
	if (ret) {
		rts_isp_perror(ret, "get plugins version fail");
		return ret;
	}
	printf("isp plugins version:\n");
	printf("  ae api version: 0x%04x\n", version.ae_api_version);
	printf("  awb api version: 0x%04x\n", version.awb_api_version);
	printf("  af api version: 0x%04x\n", version.af_api_version);
	printf("  sensor api version: 0x%04x\n", version.sensor_api_version);
	printf("  iq_pack version: 0x%08x\n", (unsigned int)version.iq_pack_version);
	printf("  iq_proto version: 0x%08x\n", (unsigned int)version.iq_proto_version);
	printf("  iq_customer version: 0x%02x\n", version.iq_customer_version);
	return 0;
}

