/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static void query_awb_ctrl(void)
{
	int i;
	uint32_t ids[] = {
		V4L2_CID_AUTO_WHITE_BALANCE,
		V4L2_CID_WHITE_BALANCE_TEMPERATURE,
		V4L2_CID_RED_BALANCE,
		RTS_V4L2_CID_GREEN_BALANCE,
		V4L2_CID_BLUE_BALANCE,
	};

	printf("query awb ctrls...\n");
	for (i = 0; i < (int)ARRAY_SIZE(ids); i++)
		print_ctrl(ISP0, &ids[i]);
}

int cmd_test_awb(int argc, char *argv[])
{
	int ret;
	int choice;

	while (1) {
		printf("==== isp awb test ====\n");
		printf("0. query awb ctrls.\n");
		printf("1. get auto mode.\n");
		printf("2. set auto mode.\n");
		printf("3. get color temperature.\n");
		printf("4. set color temperature.\n");
		printf("5. get red balance.\n");
		printf("6. set red balance.\n");
		printf("7. get green balance.\n");
		printf("8. set green balance.\n");
		printf("9. get blue balance.\n");
		printf("10. set blue balance.\n");
		printf("11. exit.\n");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			query_awb_ctrl();
			break;
		case 1:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_AUTO_WHITE_BALANCE);
			break;
		case 2:
			printf("input mode, 0: manual, 1: auto => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_AUTO_WHITE_BALANCE);
			break;
		case 3:
			ret = get_ctrl_stdio(ISP0,
				     V4L2_CID_WHITE_BALANCE_TEMPERATURE);
			break;
		case 4:
			printf("input color temperature => ");
			ret = set_ctrl_stdio(ISP0,
				     V4L2_CID_WHITE_BALANCE_TEMPERATURE);
			break;
		case 5:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_RED_BALANCE);
			break;
		case 6:
			printf("input red gain(8 bit precision) => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_RED_BALANCE);
			break;
		case 7:
			ret = get_ctrl_stdio(ISP0, RTS_V4L2_CID_GREEN_BALANCE);
			break;
		case 8:
			printf("input green gain(8 bit precision) => ");
			ret = set_ctrl_stdio(ISP0, RTS_V4L2_CID_GREEN_BALANCE);
			break;
		case 9:
			ret = get_ctrl_stdio(ISP0, V4L2_CID_BLUE_BALANCE);
			break;
		case 10:
			printf("input blue gain(8 bit precision) => ");
			ret = set_ctrl_stdio(ISP0, V4L2_CID_BLUE_BALANCE);
			break;
		case 11:
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
