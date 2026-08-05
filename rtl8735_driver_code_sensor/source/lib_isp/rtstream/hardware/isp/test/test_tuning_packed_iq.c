/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Grant Shen <grant_shen@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>
#include <rts_isp_tuning.h>

static void Usage(void)
{
	printf("Usage: test_tuning_packed_iq OPTION PARAMS...\n\n"
	       "OPTION can be:\n"
	       "-h, --help               print this message\n"
	       "-g, --get-path           get packed iq path\n"
	       "-l, --load-iq            load new packed iq\n");
}

extern int optind;  //for reset getopt_long()
int cmd_test_tuning_packed_iq(int argc, char *argv[])
{
	int ret = RTS_ISP_OK;
	int opt;
	const struct option opts[] = {
		{"get-path", required_argument, NULL, 'g'},
		{"load-iq", required_argument, NULL, 'l'},
		{"help", no_argument, NULL, 'h'},
		{0},
	};

	if (argc < 2) {
		Usage();
		return EINVAL;
	}

	optind = 0;  //thread need reset global vars of getopt_long()
	while ((opt = getopt_long(argc, argv, "glh", opts, NULL)) != -1) {
		switch (opt) {
		case 'g':
			printf("packed iq path is: %s\n",
			       rts_isp_tuning_packed_iq_path(ISP0));
			break;
		case 'l':
			ret = rts_isp_tuning_reload_packed_iq(ISP0);
			if (ret)
				rts_isp_perror(ret, "reload packed iq fail");
			break;
		case 'h':
		default:
			Usage();
			break;
		}
	}

	return (-ret);
};
