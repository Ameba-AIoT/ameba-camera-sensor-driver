/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static void enumerate_menu(const struct v4l2_queryctrl *qc)
{
	struct v4l2_querymenu qm;

	memset(&qm, 0, sizeof(qm));
	qm.id = qc->id;
	for (qm.index = qc->minimum; (int)qm.index <= qc->maximum; qm.index++)
		if (!rts_isp_v4l2_query_menu(ISP0, &qm))
			printf("              %d -> %s\n", qm.index, qm.name);
}

int print_ctrl(uint32_t isp_id, uint32_t *id)
{
	int ret;
	struct v4l2_queryctrl qc;

	if (!id)
		return -EINVAL;

	memset(&qc, 0, sizeof(qc));
	qc.id = *id;
	ret = rts_isp_v4l2_query_ctrl(isp_id, &qc);
	if (ret) {
		rts_isp_perror(ret, "failed to query ctrl 0x%08x", *id);
		return ret;
	}

	*id = qc.id;
	printf("query ctrl => id: 0x%x\n"
	       "              type: %u\n"
	       "              name: %s\n"
	       "              min: %d\n"
	       "              max: %d\n"
	       "              step: %d\n"
	       "              def: %d\n"
	       "              flags: 0x%x\n",
	       qc.id, qc.type, qc.name, qc.minimum, qc.maximum,
	       qc.step, qc.default_value, qc.flags);
	if (qc.type == V4L2_CTRL_TYPE_MENU)
		enumerate_menu(&qc);

	return 0;
}

int get_ctrl(uint32_t isp_id, uint32_t id, int *value)
{
	int ret;
	struct v4l2_control c;

	if (!value)
		return -EINVAL;

	c.id = id;
	ret = rts_isp_v4l2_g_ctrl(isp_id, &c);
	if (ret) {
		rts_isp_perror(ret, "failed to get ctrl 0x%08x", id);
		return ret;
	}
	*value = c.value;

	return 0;
}

int set_ctrl(uint32_t isp_id, uint32_t id, int *value)
{
	int ret;
	struct v4l2_control c;

	if (!value)
		return -EINVAL;

	c.id = id;
	c.value = *value;
	ret = rts_isp_v4l2_s_ctrl(isp_id, &c);
	if (ret) {
		rts_isp_perror(ret, "failed to set ctrl 0x%08x", id);
		return ret;
	}
	*value = c.value;
	return 0;
}

int get_ctrl_stdio(uint32_t isp_id, uint32_t id)
{
	int ret;
	int value;

	ret = get_ctrl(isp_id, id, &value);
	if (!ret)
		printf("%d\n", value);
	return ret;
}

int set_ctrl_stdio(uint32_t isp_id, uint32_t id)
{
	int ret;
	int value;

	scanf("%d", &value);
	ret = set_ctrl(isp_id, id, &value);
	if (!ret)
		printf("%d\n", value);
	return ret;
}
