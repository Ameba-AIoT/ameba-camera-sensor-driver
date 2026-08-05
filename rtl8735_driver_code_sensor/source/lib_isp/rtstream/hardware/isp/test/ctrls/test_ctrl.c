/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "common.h"

static void list_ctrl(void)
{
	uint32_t id = 0;

	printf("query all ctrls...\n");
	id |= V4L2_CTRL_FLAG_NEXT_CTRL;
	while (!print_ctrl(ISP0, &id)) {
		id |= V4L2_CTRL_FLAG_NEXT_CTRL;
	}
}

static void print_help(void)
{
	printf("Usage: test_ctrl OPTION [PARAMS...]\n\n"
	       "OPTION can be:\n"
	       "-h, --help               print this message\n"
	       "-l, --list-ctrl          list all ctrls\n"
	       "-g, --get-ctrl id        get val of ctrl id\n"
	       "-s, --set-ctrl id val    set ctrl id to val\n");
}

static void need_more_argument(const char * const long_name,
			       const char * const short_name)
{
	printf("need more argument for --%s/-%s\n", long_name, short_name);
	//exit(EINVAL);
}

extern int optind;  //for reset getopt_long()
int cmd_test_ctrl(int argc, char *argv[])
{
	int ret = 0;
	int c;
	uint32_t id;
	int value;
	const struct option opts[] = {
		{"list-ctrl", no_argument, NULL, 'l'},
		{"get-ctrl", required_argument, NULL, 'g'},
		{"set-ctrl", required_argument, NULL, 's'},
		{"help", no_argument, NULL, 'h'},
		{0},
	};

	if (argc < 2) {
		print_help();
		ret = EINVAL;
		goto exit;
	}

	optind = 0;  //thread need reset global vars of getopt_long()
	while ((c = getopt_long(argc, argv, "lg:s:h", opts, NULL)) != -1) {
		switch (c) {
		case 'l':
			list_ctrl();
			break;
		case 'g':
			id = strtoul(optarg, NULL, 0);
			ret = get_ctrl_stdio(ISP0, id);
			break;
		case 's':
			if (optind >= argc) {
				need_more_argument("set-ctrl", "s");
				ret = EINVAL;
				goto exit;

			}
			id = strtoul(optarg, NULL, 0);
			value = strtol(argv[optind], NULL, 0);
			ret = set_ctrl(ISP0, id, &value);
			if (!ret)
				printf("%d\n", value);
			break;
		case 'h':
		case '?':
		default:
			print_help();
			ret = EINVAL;
			goto exit;
			break;
		}
	}

exit:
	return ret;
}
