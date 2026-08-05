/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <rts_isp.h>

static void print_ae_statis(const struct rts_isp_ae_stat_info *stat_info,
			    const struct rts_isp_ae_statis *statis)
{
	int i;
	int win_num;

	win_num = stat_info->win.cols * stat_info->win.rows;

	printf("frame count: %d\n", (int)statis->frame_count);

	printf("y_mean:\n");
	for (i = 0; i < win_num; i++) {
		printf("%03x ", statis->y_mean[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}

	printf("histogram:\n");
	for (i = 0; i < stat_info->hist_bins; i++) {
		printf("%08x ", (unsigned int)statis->hist[i]);
		if ((i + 1) % 8 == 0)
			printf("\n");
	}
}

int cmd_test_ae_statis(int argc, char *argv[])
{
	int ret;
	struct rts_isp_ae_stat_info stat_info;
	const struct rts_isp_ae_statis *statis;

	ret = rts_isp_get_ae_statis_info(ISP0, &stat_info);
	if (ret) {
		rts_isp_perror(ret, "get stat info fail");
		return ret;
	}
	ret = rts_isp_query_ae_statis(ISP0, &statis);
	if (ret) {
		rts_isp_perror(ret, "query statis fail");
		return ret;
	}
	ret = rts_isp_get_ae_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "get statis fail");
		rts_isp_release_ae_statis(ISP0, statis);
		return ret;
	}

	print_ae_statis(&stat_info, statis);

	ret = rts_isp_put_ae_statis(ISP0, statis);
	if (ret) {
		rts_isp_perror(ret, "put statis fail");
		rts_isp_release_ae_statis(ISP0, statis);
		return ret;
	}

	rts_isp_release_ae_statis(ISP0, statis);

	return 0;
}

