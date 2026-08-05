/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <rtsavisp.h>

static void print_help(void)
{
	printf("Usage: test_mipiout OPTION PARAMS...\n\n"
	       "OPTION can be:\n"
	       "-h, --help                print this message\n"
	       "-e, --enable              enable/disable mipi out\n"
	       "-l, --lanenum lanenum     config lanes\n"
	       "                          1: 1 lane\n"
	       "                          2: 2 lanes\n"
	       "                          4: 4 lanes\n"
	       "-t, --type type           config data type\n"
	       "                          0: RAW8\n"
	       "                          1: RAW10\n"
	       "                          2: RAW12\n"
	       "                          3: YUYV\n"
	       "-p, --position position   config output position\n"
	       "                          0: before crop\n"
	       "                          1: after crop\n"
	       "                          2: before zoom\n");
}

extern int optind;  //for reset getopt_long()
int cmd_test_mipiout(int argc, char *argv[])
{
	int ret;
	int c;
	struct rts_isp_mipiout mipiout;
	const struct option opts[] = {
		{"help", no_argument, NULL, 'h'},
		{"enable", required_argument, NULL, 'e'},
		{"lanes", required_argument, NULL, 'l'},
		{"type", required_argument, NULL, 't'},
		{"position", required_argument, NULL, 'p'},
		{0},
	};

	if (argc < 2) {
		print_help();
		return RTS_ISP_EINVAL;
	}

	ret = rts_av_isp_get_mipiout(ISP0, &mipiout);
	if (ret) {
		rts_isp_perror(ret, "get mipiout fail");
		return (-ret);
	};

	optind = 0;  //thread need reset global vars of getopt_long()
	while ((c = getopt_long(argc, argv, "e:l:t:p:h", opts, NULL)) != -1) {
		switch (c) {
		case 'e':
			mipiout.enable = strtoul(optarg, NULL, 0);
			break;
		case 'l':
			mipiout.lanes = (1 << strtoul(optarg, NULL, 0)) - 1;
			break;
		case 't':
			mipiout.type = strtoul(optarg, NULL, 0);
			break;
		case 'p':
			mipiout.position = strtoul(optarg, NULL, 0);
			break;
		case 'h':
			print_help();
			return 0;
			break;
		case '?':
		default:
			print_help();
			return RTS_ISP_EINVAL;
			break;
		}
	}
	ret = rts_av_isp_set_mipiout(ISP0, &mipiout);
	if (ret)
		rts_isp_perror(ret, "set mipi out fail");

	return -ret;
}

