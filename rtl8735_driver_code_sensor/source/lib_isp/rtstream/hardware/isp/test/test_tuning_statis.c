/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <rts_isp_tuning.h>

#if 0
int main(int argc, char *argv[])
#else //hrchen
int cmd_test_tuning_statis(int argc, char *argv[])
#endif
{
	int ret;
#if 0
	int fd;
#endif
	int i;
	struct rts_isp_tuning_statis *statis;

	ret = rts_isp_tuning_query_statis(ISP0, &statis);
	if (ret) {
		rts_isp_perror(ret, "query statis fail");
		return ret;
	}
	for (i = RTS_ISP_TUNING_STATIS_ALL; i <= RTS_ISP_TUNING_STATIS_Y; i++) {
		const char *file_name[RTS_ISP_TUNING_STATIS_Y + 1] = {
			"tuning_statis.bin",
			"tuning_statis_raw.bin",
			"tuning_statis_awb.bin",
			"tuning_statis_ae.bin",
			"tuning_statis_af.bin",
			"tuning_statis_flick.bin",
			"tuning_statis_y.bin",
		};

		statis->type = i;
		ret = rts_isp_tuning_get_statis(ISP0, statis);
		if (ret) {
			rts_isp_perror(ret, "get statis fail");
			rts_isp_tuning_release_statis(ISP0, statis);
			return ret;
		}

		printf("get %s, type: %d buf: %p, size: %u\n",
		       file_name[i], statis->type, statis->buf,  (unsigned int)statis->len);
#if 0
		fd = open(file_name[i], O_RDWR | O_CREAT, 0644);
		write(fd, statis->buf, statis->len);
		close(fd);
#else //hrchen
#endif
	}
	rts_isp_tuning_release_statis(ISP0, statis);

	return 0;
}

