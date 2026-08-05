/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn?
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>
#include "isp_mem.h"

static void print_gamma(const struct v4l2_query_ext_ctrl *qec,
		      const struct v4l2_ext_controls *controls, const char *s)
{
	int i;
	struct v4l2_ext_control *gamma = controls->controls;

	printf("%s\n", s);
	printf("gamma auto: %d\n", gamma[0].value);
	for (i = 0; i < (int)qec->elems; i++) {
		uint16_t val;

		val = *(uint16_t *)(gamma[1].ptr + i * qec->elem_size);
		printf("0x%08x", val);
		if ((i + 1) % 5 == 0)
			printf("\n");
		else
			printf(" ");
	}
}

int cmd_test_gamma(int argc, char *argv[])
{
	int i;
	int ret;
	struct v4l2_query_ext_ctrl qec = {};
	struct v4l2_ext_controls controls = {};
	struct v4l2_ext_control gamma[2] = {};

	qec.id = RTS_V4L2_CID_GAMMA_CURVE;
	ret = rts_isp_v4l2_query_ext_ctrl(ISP0, &qec);
	if (ret) {
		rts_isp_perror(ret, "query gamma curve fail");
		return ret;
	}
	printf("id: %x, name: %s, elems: %u, elem_size %u\n",
	       qec.id, qec.name, qec.elems, qec.elem_size);
	gamma[0].id = RTS_V4L2_CID_AUTO_GAMMA;
	gamma[1].id = RTS_V4L2_CID_GAMMA_CURVE;
	gamma[1].size = qec.elems * qec.elem_size;
	gamma[1].ptr = calloc(qec.elems, qec.elem_size);
	controls.count = 2;
	controls.controls = gamma;
	ret = rts_isp_v4l2_g_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "get gamma curve fail");
		goto out;
	}
	print_gamma(&qec, &controls, "get gamma:");

	gamma[0].value = 0;
	for (i = 0; i < (int)qec.elems; i++)
		*(uint16_t *)(gamma[1].ptr + i * qec.elem_size) =
			(i + 1) * 0x40;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "set gamma curve fail");
		goto out;
	}
	print_gamma(&qec, &controls, "set gamma:");
	printf("press enter to resume auto gamma...");
	getchar();
	gamma[0].value = 1;
	controls.count = 1;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "resume auto gamma fail");
		goto out;
	}

out:
	free(gamma[1].ptr);
	return ret;
}
