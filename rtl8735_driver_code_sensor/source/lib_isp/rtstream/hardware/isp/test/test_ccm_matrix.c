/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <rts_isp.h>
#include "isp_mem.h"

static void print_ccm(const struct v4l2_query_ext_ctrl *qec,
		      const struct v4l2_ext_controls *controls, const char *s)
{
	int i;
	struct v4l2_ext_control *ccm = controls->controls;

	printf("%s\n", s);
	printf("ccm auto: %d\n", ccm[0].value);
	for (i = 0; i < (int)qec->elems; i++) {
		int32_t val;

		val = *(int32_t *)(ccm[1].ptr + i * qec->elem_size);
		printf("0x%08x", (unsigned int)val);
		if ((i + 1) % 3 == 0)
			printf("\n");
		else
			printf(" ");
	}
}

int cmd_test_ccm_matrix(int argc, char *argv[])
{
	int i;
	int ret;
	struct v4l2_query_ext_ctrl qec = {};
	struct v4l2_ext_controls controls = {};
	struct v4l2_ext_control ccm[2] = {};

	qec.id = RTS_V4L2_CID_CCM_MATRIX;
	ret = rts_isp_v4l2_query_ext_ctrl(ISP0, &qec);
	if (ret) {
		rts_isp_perror(ret, "query ccm matrix fail");
		return ret;
	}
	printf("id: %x, name: %s, elems: %u, elem_size %u\n",
	       qec.id, qec.name, qec.elems, qec.elem_size);
	ccm[0].id = RTS_V4L2_CID_AUTO_CCM;
	ccm[1].id = RTS_V4L2_CID_CCM_MATRIX;
	ccm[1].size = qec.elems * qec.elem_size;
	ccm[1].ptr = calloc(qec.elems, qec.elem_size);
	controls.count = 2;
	controls.controls = ccm;
	ret = rts_isp_v4l2_g_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "get ccm matrix fail");
		goto out;
	}
	print_ccm(&qec, &controls, "get ccm:");

	ccm[0].value = 0;
	for (i = 0; i < (int)qec.elems; i++)
		*(int32_t *)(ccm[1].ptr + i * qec.elem_size) = (i + 1) * 0x40;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "set ccm matrix fail");
		goto out;
	}
	print_ccm(&qec, &controls, "set ccm:");
	printf("press enter to resume auto ccm...");
	getchar();
	ccm[0].value = 1;
	controls.count = 1;
	ret = rts_isp_v4l2_s_ext_ctrls(ISP0, &controls);
	if (ret) {
		rts_isp_perror(ret, "resume auto ccm fail");
		goto out;
	}

out:
	free(ccm[1].ptr);
	return ret;
}
