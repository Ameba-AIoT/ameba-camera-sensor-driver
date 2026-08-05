/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>

static void print_ygamma(const struct v4l2_query_ext_ctrl *qec,
			 const struct v4l2_ext_controls *controls,
			 const char *s)
{
	int i;
	struct v4l2_ext_control *ygamma = controls->controls;

	printf("%s\n", s);
	printf("ygamma auto: %d\n", ygamma[0].value);
	for (i = 0; i < (int)qec->elems; i++) {
		uint8_t val;

		val = *(uint8_t *)(ygamma[1].ptr + i * qec->elem_size);
		printf("0x%02x", val);
		if ((i + 1) % 8 == 0)
			printf("\n");
		else
			printf(" ");
	}
}

#if 0
int main(int argc, char *argv[])
#else //hrchen
int cmd_test_ygamma_curve(int argc, char *argv[])
#endif
{
	int i;
	int ret;
	struct v4l2_query_ext_ctrl qec = {};
	struct v4l2_ext_controls controls = {};
	struct v4l2_ext_control ygamma[2] = {};

	qec.id = RTS_V4L2_CID_YGAMMA_CURVE;
	ret = rts_isp_v4l2_query_ext_ctrl(ISP0, &qec);
	if (ret) {
		rts_isp_perror(ret, "query ygamma curve fail");
		return ret;
	}
	printf("id: %x, name: %s, elems: %u, elem_size %u\n",
	       qec.id, qec.name, qec.elems, qec.elem_size);
	ygamma[0].id = RTS_V4L2_CID_AUTO_YGAMMA;
	ygamma[1].id = RTS_V4L2_CID_YGAMMA_CURVE;
	ygamma[1].size = qec.elems * qec.elem_size;
	ygamma[1].ptr = calloc(qec.elems, qec.elem_size);
	controls.count = 2;
	controls.controls = ygamma;
	ret = rts_isp_v4l2_g_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "get ygamma curve fail");
		goto out;
	}
	print_ygamma(&qec, &controls, "get ygamma curve:");

	ygamma[0].value = 0;
	for (i = 0; i < (int)qec.elems; i++)
		*(uint8_t *)(ygamma[1].ptr + i * qec.elem_size) = 128;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "set ygamma curve fail");
		goto out;
	}
	print_ygamma(&qec, &controls, "set ygamma curve:");
	printf("press enter to resume auto ygamma...");
	getchar();
	ygamma[0].value = 1;
	controls.count = 1;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "resume auto ygamma fail");
		goto out;
	}

out:
	free(ygamma[1].ptr);
	return ret;
}
