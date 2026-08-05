/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */

#include <isp_v4l2_ctrl.h>
#include <isp_mod_iq.h>
#include <isp_mod_eeh.h>
#include <isp_hw_eeh.h>

struct isp_mod_eeh {
	struct isp_mod mod;
	const struct isp_hw_eeh_ops *hw_ops;

	struct v4l2_ctrl *sharpness_ctrl;
};

static int mod_eeh_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_eeh *eeh = get_mod(mod, eeh);
	//isp_info("%s \r\n",__func__);
	return eeh->hw_ops->estimation(mod->owner_id);
}

static int mod_eeh_dynamic_post(struct isp_mod *mod, void *data)
{
	struct isp_mod_eeh *eeh = get_mod(mod, eeh);

	if (!eeh->sharpness_ctrl)
		return RTS_ISP_OK;

	return eeh->hw_ops->set_sharpness(mod->owner_id,
					  eeh->sharpness_ctrl->cur.val);
}

static struct isp_mod_action_info eeh_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_eeh_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC_POST, mod_eeh_dynamic_post),
};

static int eeh_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_eeh *eeh = get_mod(mod, eeh);

	switch (ctrl->id) {
	case V4L2_CID_SHARPNESS:
		ret = eeh->hw_ops->set_sharpness(mod->owner_id, ctrl->val);
		break;
	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set eeh ctrl fail");
	return ret;
}

static const struct v4l2_ctrl_ops eeh_ctrl_ops = {
	.s_ctrl = eeh_s_ctrl,
};

static int isp_mod_eeh_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_eeh *eeh;

	eeh = get_mod(mod, eeh);
	eeh->hw_ops = isp_hw_eeh_get_ops();
	if (eeh->hw_ops == NULL) {
		isp_error("get eeh hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_eeh_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_eeh_hardware_init(struct isp_mod *mod)
{
	struct isp_mod_eeh *eeh = get_mod(mod, eeh);

	return eeh->hw_ops->init_vreg(mod->owner_id);
}

static int isp_mod_eeh_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_eeh *eeh = get_mod(mod, eeh);
	struct v4l2_ctrl_handler *handler = phandler;

	eeh->sharpness_ctrl = rtsv_ctrl_new_std(handler, &eeh_ctrl_ops,
						V4L2_CID_SHARPNESS,
						SHARPNESS_CTRL_MIN,
						SHARPNESS_CTRL_MAX,
						1, SHARPNESS_CTRL_DEF, mod);
	return RTS_ISP_OK;
}

static struct isp_mod_eeh eeh;

int isp_register_mod_eeh(void)
{
	memset(&eeh, 0, sizeof(eeh));
	eeh.mod.id = MOD_EEH;
	eeh.mod.name = "eeh";
	eeh.mod.notify_bits = ISP_STATIS_DONE_BIT | ISP_DYNAMIC_POST_BIT;
	eeh.mod.init = isp_mod_eeh_init;
	eeh.mod.cleanup = isp_mod_eeh_cleanup;
	eeh.mod.hardware_init = isp_mod_eeh_hardware_init;
	eeh.mod.add_ctrl = isp_mod_eeh_add_ctrl;
	eeh.mod.notify_actions = eeh_notify_actions;
	eeh.mod.notify_actions_num = ARRAY_SIZE(eeh_notify_actions);
	return isp_mod_register(&eeh.mod);
}

void isp_unregister_mod_eeh(void)
{
	isp_mod_unregister(&eeh.mod);
}

