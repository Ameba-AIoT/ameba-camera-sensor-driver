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

#define MAX_REG_NUM 4096
#define LINE_REG_NUM 8

static void __display_values(uint32_t offset, uint32_t *values, uint32_t num,
			     const char * const display_str)
{
	int i;

	for (i = 0; i < (int)num; i++) {
		if (i % LINE_REG_NUM == 0)
			printf("%05x:", (unsigned int)(offset + i * 4));
		printf(display_str, values[i]);
		if ((i + 1) % LINE_REG_NUM == 0)
			printf("\n");
	}
	if (num % LINE_REG_NUM)
		printf("\n");
}

static void __display_line(uint32_t num)
{
	int i;

	printf("      ");
	for (i = 0; i < (int)(num > LINE_REG_NUM ? LINE_REG_NUM : num); i++)
		printf(" ========");
	printf("\n");
}

static void display_values(uint32_t offset, uint32_t *values, uint32_t num)
{
	__display_values(offset, values, num, " %8x");
	__display_line(num);
	__display_values(offset, values, num, " %8u");

}

static int read_regs(uint32_t offset, uint32_t *values, uint32_t num)
{
	int i;
	int ret;
	struct rts_isp_tuning_reg *regs;

	if (!values || !num || num > MAX_REG_NUM) {
		printf("offset, values or num is invalid\n");
		return -EINVAL;
	}
	regs = calloc(num, sizeof(*regs));
	if (!regs)
		return -ENOMEM;
	for (i = 0; i < (int)num; i++) {
		regs[i].offset = offset + i * 4;
		regs[i].mask = 0;
	}
	ret = rts_isp_tuning_read_regs(ISP0, regs, num);
	if (ret)
		goto out;
	for (i = 0; i < (int)num; i++)
		values[i] = regs[i].value;
	display_values(offset, values, num);
out:
	free(regs);
	return ret;
}

static int write_regs(uint32_t offset, uint32_t *values, uint32_t num)
{
	int i;
	int ret;
	struct rts_isp_tuning_reg *regs;

	if (!values || !num || num > MAX_REG_NUM) {
		printf("offset, values or num is invalid\n");
		return -EINVAL;
	}
	regs = calloc(num, sizeof(*regs));
	if (!regs)
		return -ENOMEM;
	for (i = 0; i < (int)num; i++) {
		regs[i].offset = offset + i * 4;
		regs[i].value = values[i];
		regs[i].mask = 0;
	}
	ret = rts_isp_tuning_write_regs(ISP0, regs, num);
	free(regs);
	if (ret)
		return ret;
	return read_regs(offset, values, num);
}

static void Usage(void)
{
	printf("Usage: reg OPTION PARAMS...\n\n"
	       "OPTION can be:\n"
	       "-h, --help                         print this message\n"
	       "-r, --read-reg offset [num]        read isp regs\n"
	       "-w, --write-reg offset values...   write isp regs\n");
}

#if 0
int main(int argc, char *argv[])
#else //hrchen
extern int optind;  //for reset getopt_long()
int cmd_test_tuning_regs(int argc, char *argv[])
#endif
{
	int ret;
	int opt;
	uint32_t offset;
	uint32_t num;
	uint32_t values[MAX_REG_NUM];
	const struct option opts[] = {
		{"read-reg", required_argument, NULL, 'r'},
		{"write-reg", required_argument, NULL, 'w'},
		{"help", no_argument, NULL, 'h'},
		{0},
	};

	if (argc < 2) {
		Usage();
		return (EINVAL);
	}

#if 1
	optind = 0;  //thread need reset global vars of getopt_long()
#endif
	while ((opt = getopt_long(argc, argv, "r:w:h", opts, NULL)) != -1) {
		switch (opt) {
		case 'r':
			offset = strtoul(optarg, NULL, 0);
			if (optind >= argc || argv[optind][0] == '-')
				num = 1;
			else
				num = strtoul(argv[optind++], NULL, 0);
			ret = read_regs(offset, values, num);
			if (ret) {
				rts_isp_perror(ret, "read regs fail");
				return (-ret);
			}
			break;
		case 'w':
			offset = strtoul(optarg, NULL, 0);
			num = 0;
			while (optind < argc && argv[optind][0] != '-') {
				values[num] = strtoul(argv[optind++], NULL, 0);
				num++;
			}
			if (!num) {
				Usage();
				return (EINVAL);
			}
			ret = write_regs(offset, values, num);
			if (ret) {
				rts_isp_perror(ret, "write regs fail");
				return (-ret);
			}
			break;
		case 'h':
			Usage();
			return (0);
			break;
		default:
			Usage();
			return (EINVAL);
			break;
		}
	}

	return (0);
};
