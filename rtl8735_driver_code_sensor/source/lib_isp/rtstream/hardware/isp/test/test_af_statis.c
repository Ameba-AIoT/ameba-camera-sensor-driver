/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <rts_isp.h>

static void print_af_statis(const struct rts_isp_af_stat_info *stat_info,
			    const struct rts_isp_af_statis *statis)
{
	int i;
	int win_num;

	win_num = stat_info->win.cols * stat_info->win.rows;

	printf("frame count: %d\n", (int)statis->frame_count);
	printf("num0: %d\n", (int)statis->num0);
	printf("sum0: %d\n", (int)statis->sum0);
	printf("num1: %d\n", (int)statis->num1);
	printf("sum1: %d\n", (int)statis->sum1);

	printf("edges:\n");
	for (i = 0; i < win_num; i++) {
		printf("%08x ", (unsigned int)statis->edges[i]);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}

}

int cmd_test_af_statis(int argc, char *argv[])
{
	int ret;
	struct rts_isp_af_stat_info stat_info;
	const struct rts_isp_af_statis *statis;

	ret = rts_isp_get_af_statis_info(ISP0, &stat_info);
	if (ret) {
		rts_isp_perror(ret, "get stat info fail");
		return ret;
	}
	ret = rts_isp_query_af_statis(ISP0, &statis);
	if (ret) {
		rts_isp_perror(ret, "query statis fail");
		return ret;
	}
	ret = rts_isp_get_af_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "get statis fail");
		rts_isp_release_af_statis(ISP0, statis);
		return ret;
	}

	print_af_statis(&stat_info, statis);

	ret = rts_isp_put_af_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "put statis fail");
		rts_isp_release_af_statis(ISP0, statis);
		return ret;
	}

	rts_isp_release_af_statis(ISP0, statis);

	return 0;
}

