/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <rts_isp.h>

static void print_help(void)
{
	printf("Usage: test_sen_reg OPTION PARAMS...\n\n"
	       "OPTION can be:\n"
	       "-h, --help                         print this message\n"
	       "-r, --read-reg offset [num]        read sensor regs\n"
	       "-w, --write-reg offset values...   write sensor regs\n");
}

static void need_more_argument(const char * const long_name,
			       const char * const short_name)
{
	printf("need more argument for --%s/-%s\n", long_name, short_name);
}

extern int optind;  //for reset getopt_long()
int cmd_test_sen_reg(int argc, char *argv[])
{
	int ret = 0;
	int c;
	int i;
	int num;
	uint16_t reg_data[4096];
	struct rts_isp_i2c_reg reg;
	const struct option opts[] = {
		{"-r", required_argument, NULL, 'r'},
		{"-w", required_argument, NULL, 'w'},
		{"help", no_argument, NULL, 'h'},
		{0},
	};

	if (argc < 2) {
		print_help();
		return EINVAL;
	}

	optind = 0;  //thread need reset global vars of getopt_long()
	while ((c = getopt_long(argc, argv, "r:w:h", opts, NULL)) != -1) {
		switch (c) {
		case 'r':
			reg.addr = strtoul(optarg, NULL, 0);
			if (optind >= argc || argv[optind][0] == '-')
				num = 1;
			else
				num = strtoul(argv[optind++], NULL, 0);
			while (num--) {
				ret = rts_isp_read_sensor_reg(ISP0, &reg);
				if (!ret)
					printf("%#x => %#x\n",
					       reg.addr, reg.data);
				else
					break;
				reg.addr++;
			}
			printf("\n");
			break;
		case 'w':
			if (optind >= argc) {
				need_more_argument("write", "w");
				return EINVAL;
			}
			reg.addr = strtoul(optarg, NULL, 0);
			num = 0;
			while (optind < argc && argv[optind][0] != '-') {
				reg_data[num] = strtoul(argv[optind++],
							NULL, 0);
				num++;
			}
			if (!num) {
				print_help();
				return EINVAL;

			}
			for (i = 0; i < num; i++) {
				reg.data = reg_data[i];
				ret = rts_isp_write_sensor_reg(ISP0, &reg);
				if (ret) {
					rts_isp_perror(ret,
						"write reg %#x => %#x fail\n",
						reg.addr, reg.data);
					break;

				}
				reg.addr++;
			}
			break;
		case 'h':
		case '?':
		default:
			print_help();
			return EINVAL;
			break;
		}
	}
	if (ret)
		rts_isp_perror(ret, "read/write sensor reg fail");
	return -ret;
}
