/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static void query_ae_ctrl(void)
{
	int i;
	uint32_t ids[] = {
		V4L2_CID_AUTOGAIN,
		V4L2_CID_EXPOSURE,
		V4L2_CID_GAIN,
		V4L2_CID_EXPOSURE_AUTO_PRIORITY,
		RTS_V4L2_CID_DYNAMIC_FPS,
	};

	printf("query ae ctrls...\n");
	for (i = 0; i < (int)ARRAY_SIZE(ids); i++)
		print_ctrl(ISP0, &ids[i]);
}

int cmd_test_ae(int argc, char *argv[])
{
	int ret;
	int choice;

	while (1) {
		printf("==== isp ae test ====\n");
		printf("0. query ae ctrls.\n");
		printf("1. get auto mode.\n");
		printf("2. set auto mode.\n");
		printf("3. get exposure.\n");
		printf("4. set exposure.\n");
		printf("5. get gain.\n");
		printf("6. set gain.\n");
		printf("7. get dyn fps enable.\n");
		printf("8. set dyn fps enable.\n");
		printf("9. get dyn fps.\n");
		printf("10. exit.\n");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			query_ae_ctrl();
			break;
		case 1:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_AUTOGAIN);
			break;
		case 2:
			printf("input mode, 0: manual, 1: auto => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_AUTOGAIN);
			break;
		case 3:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_EXPOSURE);
			break;
		case 4:
			printf("input exposure(us) => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_EXPOSURE);
			break;
		case 5:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_GAIN);
			break;
		case 6:
			printf("input gain(8 bit precision) => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_GAIN);
			break;
		case 7:
			ret = get_ctrl_stdio(ISP0,
					     V4L2_CID_EXPOSURE_AUTO_PRIORITY);
			break;
		case 8:
			printf("input enable => ");
			ret = set_ctrl_stdio(ISP0,
					     V4L2_CID_EXPOSURE_AUTO_PRIORITY);
			break;
		case 9:
			ret = get_ctrl_stdio(ISP0, RTS_V4L2_CID_DYNAMIC_FPS);
			break;
		case 10:
			ret = 0;
			goto exit;
			break;
		default:
			break;
		}
	}

exit:
	return -ret;
}
