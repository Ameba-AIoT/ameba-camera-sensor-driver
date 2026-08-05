#include <stdio.h>
#include <stdlib.h>
#include <rtsavisp.h>

static int error_usage(void)
{
	printf("Usage: test_algo_bind ae/awb/af/other 0/1/2/3\n");
	return (EINVAL);
}

int cmd_test_algo_bind(int argc, char *argv[])
{
	int id;
	int ret;
	enum rts_isp_algo_type type = -1;
	int index;

	if (argc != 3)
		return error_usage();

	if (strcmp(argv[1], "ae") == 0)
		type = RTS_ISP_ALGO_AE;
	else if (strcmp(argv[1], "awb") == 0)
		type = RTS_ISP_ALGO_AWB;
	else if (strcmp(argv[1], "af") == 0)
		type = RTS_ISP_ALGO_AF;
	else if (strcmp(argv[1], "other") == 0)
		type = RTS_ISP_ALGO_OTHER;
	else
		return error_usage();

	index = strtol(argv[2], NULL, 0);
	if (index < 0 || index > 3)
		return error_usage();
	id = type * _RTS_ISP_ALGO_TYPE_NUM + index;

	ret = rts_av_isp_bind_algo(ISP0, id);
	if (ret)
		rts_isp_perror(ret, "bind %s %s to isp0 fail",
			       argv[1], argv[2]);
	else
		printf("bind %s %s to isp0\n", argv[1], argv[2]);

	return 0;
}
