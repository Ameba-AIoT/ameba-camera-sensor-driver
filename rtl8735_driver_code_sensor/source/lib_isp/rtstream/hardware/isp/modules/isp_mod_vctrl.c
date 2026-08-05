/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_mod.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_vctrl.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_V4L2

struct isp_mod_vctrl {
	struct isp_mod mod;
	struct v4l2_ctrl_handler *handler;
};

static int mod_vctrl_exec_query_ctrl(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_queryctrl *qc = data;

	return rtsv_queryctrl(vctrl->handler, qc);
}

static int mod_vctrl_exec_query_menu(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_querymenu *qm = data;

	return rtsv_querymenu(vctrl->handler, qm);
}

static int mod_vctrl_exec_s_ctrl(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_control *c = data;

	return rtsv_s_ctrl(vctrl->handler, c);
}

static int mod_vctrl_exec_g_ctrl(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_control *c = data;

	return rtsv_g_ctrl(vctrl->handler, c);
}

static int mod_vctrl_exec_query_ext_ctrl(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_query_ext_ctrl *qec = data;

	return rtsv_query_ext_ctrl(vctrl->handler, qec);
}

static int mod_vctrl_exec_g_ext_ctrls(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_ext_controls *ec = data;

	return rtsv_g_ext_ctrls(vctrl->handler, ec);
}

static int mod_vctrl_exec_s_ext_ctrls(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_ext_controls *ec = data;

	return rtsv_s_ext_ctrls(vctrl->handler, ec);
}

static int mod_vctrl_exec_try_ext_ctrls(struct isp_mod *mod, void *data)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);
	struct v4l2_ext_controls *ec = data;

	return rtsv_try_ext_ctrls(vctrl->handler, ec);
}

static struct isp_mod_action_info vctrl_exec_actions[] = {
	ISP_MOD_ACTION(VCTRL_EXEC_QUERY_CTRL, mod_vctrl_exec_query_ctrl),
	ISP_MOD_ACTION(VCTRL_EXEC_QUERY_MENU, mod_vctrl_exec_query_menu),
	ISP_MOD_ACTION(VCTRL_EXEC_G_CTRL, mod_vctrl_exec_g_ctrl),
	ISP_MOD_ACTION(VCTRL_EXEC_S_CTRL, mod_vctrl_exec_s_ctrl),
	ISP_MOD_ACTION(VCTRL_EXEC_QUERY_EXT_CTRL,
		       mod_vctrl_exec_query_ext_ctrl),
	ISP_MOD_ACTION(VCTRL_EXEC_G_EXT_CTRLS, mod_vctrl_exec_g_ext_ctrls),
	ISP_MOD_ACTION(VCTRL_EXEC_S_EXT_CTRLS, mod_vctrl_exec_s_ext_ctrls),
	ISP_MOD_ACTION(VCTRL_EXEC_TRY_EXT_CTRLS, mod_vctrl_exec_try_ext_ctrls),
};

static int isp_mod_vctrl_init(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_vctrl_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_vctrl_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_vctrl *vctrl = get_mod(mod, vctrl);

	vctrl->handler = phandler;
	return RTS_ISP_OK;
}

static struct isp_mod_vctrl vctrl;

int isp_register_mod_vctrl(void)
{
	memset(&vctrl, 0, sizeof(vctrl));
	vctrl.mod.id = MOD_VCTRL;
	vctrl.mod.name = "vctrl";
	vctrl.mod.init = isp_mod_vctrl_init;
	vctrl.mod.cleanup = isp_mod_vctrl_cleanup;
	vctrl.mod.add_ctrl = isp_mod_vctrl_add_ctrl;
	vctrl.mod.exec_actions = vctrl_exec_actions;
	vctrl.mod.exec_actions_num = ARRAY_SIZE(vctrl_exec_actions);
	vctrl.mod.virtual = RTS_ISP_TRUE;
	return isp_mod_register(&vctrl.mod);
}

void isp_unregister_mod_vctrl(void)
{
	isp_mod_unregister(&vctrl.mod);
}

