/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_v4l2_ctrl.h>
#include <isp_uds.h>
#include <isp_mod.h>
#include <isp_mod_vctrl.h>

int rts_isp_v4l2_query_ctrl(uint32_t isp_id, struct v4l2_queryctrl *qc)
{
	return isp_uds_message_simple(isp_id, MOD_VCTRL, VCTRL_EXEC_QUERY_CTRL,
				      qc, sizeof(*qc));
}

int rts_isp_v4l2_query_menu(uint32_t isp_id, struct v4l2_querymenu *qm)
{
	return isp_uds_message_simple(isp_id, MOD_VCTRL, VCTRL_EXEC_QUERY_MENU,
				      qm, sizeof(*qm));
}

int rts_isp_v4l2_g_ctrl(uint32_t isp_id, struct v4l2_control *control)
{
	return isp_uds_message_simple(isp_id, MOD_VCTRL, VCTRL_EXEC_G_CTRL,
				      control, sizeof(*control));
}

int rts_isp_v4l2_s_ctrl(uint32_t isp_id, struct v4l2_control *control)
{
	return isp_uds_message_simple(isp_id, MOD_VCTRL, VCTRL_EXEC_S_CTRL,
				      control, sizeof(*control));
}

static int v4l2_ext_ctrl_serial(struct v4l2_ext_controls *ecs,
				struct isp_msg_buf *msg)
{
	int ret;
	int i;
	void *buf;
	uintptr_t end;
	void *reloc_begin;
	struct v4l2_ext_controls *buf_ecs;

	if (!ecs || !msg)
		return -RTS_ISP_EINVAL;

	buf = msg->data;
	buf_ecs = buf;
	end = (uintptr_t)buf + isp_msg_data_len(&msg->hdr);

	ret = copy_from_src(buf, ecs, sizeof(*ecs), end);
	if (ret)
		return ret;
	buf_ecs->controls = buf;
	for (i = 0; i < (int)ecs->count; i++) {
		ret = copy_from_src(buf, &ecs->controls[i],
				     sizeof(ecs->controls[i]), end);
		if (ret)
			return ret;
	}
	for (i = 0; i < (int)ecs->count; i++) {
		if (!ecs->controls[i].size)
			continue;

		buf_ecs->controls[i].ptr = buf;
		ret  = copy_from_src(buf, ecs->controls[i].ptr,
				      ecs->controls[i].size, end);
		if (ret)
			return ret;
	}

	/* add_reloc_table */
	reloc_begin = buf;
	ret = set_one_reloc_item(buf, reloc_begin, end);
	if (ret)
		return ret;
	ret = set_one_reloc_item(buf, &buf_ecs->controls, end);
	if (ret)
		return ret;
	for (i = 0; i < (int)ecs->count; i++) {
		if (ecs->controls[i].size)
			ret = set_one_reloc_item(buf, &buf_ecs->controls[i].ptr,
						 end);
		if (ret)
			return ret;
	}
	msg->hdr.msg_len = (u32)buf - (u32)msg->data + sizeof(msg->hdr);
	msg->hdr.ret_len = msg->hdr.msg_len;
	msg->hdr.reloc_pos = (u32)reloc_begin - (u32)msg->data;
	msg->hdr.reloc_num = ((u32)buf - (u32)reloc_begin) / sizeof(uintptr_t);

	return RTS_ISP_OK;
}

static int v4l2_ext_ctrl_deserial(struct v4l2_ext_controls *ecs,
				  struct isp_msg_buf *msg)
{
	int ret;
	int i;
	void *buf;
	uintptr_t end;
	void *ptr;

	if (!msg || !ecs)
		return -RTS_ISP_EINVAL;

	if (msg->hdr.ret_val)
		return msg->hdr.ret_val;

	ret = isp_msg_relocate(msg);
	if (ret)
		return ret;

	end = (uintptr_t)msg->data + isp_msg_data_len(&msg->hdr);
	buf = msg->data;

	ptr = ecs->controls;
	ret = copy_to_src(ecs, buf, sizeof(*ecs), end);
	if (ret)
		return ret;
	ecs->controls = ptr;

	for (i = 0; i < (int)ecs->count; i++) {
		if (ecs->controls[i].size)
			ptr = ecs->controls[i].ptr;
		ret = copy_to_src(&ecs->controls[i], buf,
				  sizeof(*ecs->controls), end);
		if (ret)
			return ret;
		if (ecs->controls[i].size) {
			ecs->controls[i].ptr = ptr;
			ret = copy_to_src(ptr, buf, ecs->controls[i].size, end);
			if (ret)
				return ret;
		}
	}

	return RTS_ISP_OK;
}

static int __process_ext_ctrls(uint32_t isp_id, uint32_t action,
			       struct v4l2_ext_controls *ecs)
{
	int ret;
	uint8_t buf[2048];
	struct isp_msg_buf *msg;

	if (isp_id >= _ISP_ID_NUM || !ecs)
		return -RTS_ISP_EINVAL;

	msg = isp_msg_new(buf, sizeof(buf), 1);
	if (!msg)
		return -RTS_ISP_ENOMEM;

	ret = v4l2_ext_ctrl_serial(ecs, msg);
	if (ret < 0)
		goto out;

	msg->hdr.isp_id = isp_id;
	msg->hdr.mod_id = MOD_VCTRL;
	msg->hdr.action = action;
	msg->hdr.ret_val = -1;

	ret = isp_uds_message_process(msg);
	if (ret)
		goto out;
	ret = v4l2_ext_ctrl_deserial(ecs, msg);
out:
	isp_release(msg, isp_msg_put);
	return ret;
}

int rts_isp_v4l2_query_ext_ctrl(uint32_t isp_id,
				struct v4l2_query_ext_ctrl *qec)
{
	return isp_uds_message_simple(isp_id, MOD_VCTRL,
				      VCTRL_EXEC_QUERY_EXT_CTRL,
				      qec, sizeof(*qec));
}

int rts_isp_v4l2_g_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ecs)
{
	return __process_ext_ctrls(isp_id, VCTRL_EXEC_G_EXT_CTRLS, ecs);
}

int rts_isp_v4l2_s_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ecs)
{
	return __process_ext_ctrls(isp_id, VCTRL_EXEC_S_EXT_CTRLS, ecs);
}

int rts_isp_v4l2_try_ext_ctrls(uint32_t isp_id, struct v4l2_ext_controls *ecs)
{
	return __process_ext_ctrls(isp_id, VCTRL_EXEC_TRY_EXT_CTRLS, ecs);
}

