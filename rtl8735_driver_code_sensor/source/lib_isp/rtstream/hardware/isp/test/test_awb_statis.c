/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <rts_isp.h>

static void print_awb_statis(const struct rts_isp_awb_stat_info *stat_info,
			     const struct rts_isp_awb_statis *statis)
{
	int i;
	int win_num;

	win_num = stat_info->win.cols * stat_info->win.rows;

	printf("frame count: %d\n", (int)statis->frame_count);

	printf("r_mean:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->r_mean[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("g_mean:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->g_mean[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("b_mean:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->g_mean[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("y_mean:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->y_mean[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("rg:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->rg[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("bg:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->bg[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("pixels:\n");
	for (i = 0; i < win_num; i++) {
		printf("%04x ", statis->pixels[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("illum_white_pixels:\n");
	for (i = 0; i < 6; i++)
		printf("%06x ", (unsigned int)statis->illum_white_pixels[i]);
	printf("\n");

	printf("fine_r_sum: %08x\n", (unsigned int)statis->fine_r_sum);
	printf("fine_g_sum: %08x\n", (unsigned int)statis->fine_g_sum);
	printf("fine_b_sum: %08x\n", (unsigned int)statis->fine_b_sum);
	printf("fine_white_pixels: %06x\n", (unsigned int)statis->fine_white_pixels);
}

int cmd_test_awb_statis(int argc, char *argv[])
{
	int ret;
	struct rts_isp_awb_stat_info stat_info;
	const struct rts_isp_awb_statis *statis;

	ret = rts_isp_get_awb_statis_info(ISP0, &stat_info);
	if (ret) {
		rts_isp_perror(ret, "get stat info fail");
		return ret;
	}
	ret = rts_isp_query_awb_statis(ISP0, &statis);
	if (ret) {
		rts_isp_perror(ret, "query statis fail");
		return ret;
	}
	ret = rts_isp_get_awb_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "get statis fail");
		rts_isp_release_awb_statis(ISP0, statis);
		return ret;
	}

	print_awb_statis(&stat_info, statis);

	ret = rts_isp_put_awb_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "put statis fail");
		rts_isp_release_awb_statis(ISP0, statis);
		return ret;
	}

	rts_isp_release_awb_statis(ISP0, statis);

	return 0;
}

