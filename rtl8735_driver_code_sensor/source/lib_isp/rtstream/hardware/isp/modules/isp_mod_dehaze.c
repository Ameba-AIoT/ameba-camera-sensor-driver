/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_crop.h>
#include <isp_mod_dehaze.h>
#include <isp_mod_global.h>
#include <isp_hw_dehaze.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_DEHAZE

struct isp_mod_dehaze {
	struct isp_mod mod;
	const struct isp_hw_dehaze_ops *hw_ops;

	struct v4l2_ctrl *enable_ctrl;
	struct v4l2_ctrl *level_ctrl;
};

static int mod_dehaze_dynamic_post(struct isp_mod *mod, void *data)
{
	struct isp_mod_dehaze *dehaze = get_mod(mod, dehaze);

	if (!dehaze->level_ctrl)
		return RTS_ISP_OK;

	return dehaze->hw_ops->set_level(mod->owner_id,
					 dehaze->level_ctrl->cur.val);
}

static int mod_dehaze_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_dehaze *dehaze = get_mod(mod, dehaze);
	const rts_isp_rect_t *rect = data;

	// rect->x = rect->y = 0;

	ret = dehaze->hw_ops->init_vreg(mod->owner_id);
	if (ret)
		return ret;
	return dehaze->hw_ops->init(mod->owner_id, rect);
}

static struct isp_mod_action_info dehaze_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC_POST, mod_dehaze_dynamic_post),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_dehaze_mcrop_change),
};

static int isp_mod_dehaze_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_dehaze *dehaze;

	dehaze = get_mod(mod, dehaze);
	dehaze->hw_ops = isp_hw_dehaze_get_ops();
	if (dehaze->hw_ops == NULL) {
		isp_error("get dehaze hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_dehaze_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_dehaze_hardware_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int dehaze_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_dehaze *dehaze = get_mod(mod, dehaze);
	uint32_t dehaze_en;
	int ret;

	switch (ctrl->id) {
	case RTS_V4L2_CID_DEHAZE:
		dehaze->hw_ops->set_enable(mod->owner_id, ctrl->val);
		if (ctrl->val) {
			dehaze_en = 1;
			ret = isp_mod_sibling_execute(mod, MOD_GLOBAL,
									  GLOBAL_EXEC_SET_DEHAZE_ENABLE,
									  &dehaze_en, sizeof(dehaze_en));
		}
		break;
	case RTS_V4L2_CID_DEHAZE_LEVEL:
		dehaze->hw_ops->set_level(mod->owner_id, ctrl->val);
		break;
	default:
		return -RTS_ISP_ECTRL;
	}
	return RTS_ISP_OK;
}

static const struct v4l2_ctrl_ops dehaze_ctrl_ops = {
	.s_ctrl = dehaze_s_ctrl,
};

static int isp_mod_dehaze_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_dehaze *dehaze = get_mod(mod, dehaze);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config enable_config = {
		.ops = &dehaze_ctrl_ops,
		.id = RTS_V4L2_CID_DEHAZE,
		.name = "Dehaze",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	};
	const struct v4l2_ctrl_config level_config = {
		.ops = &dehaze_ctrl_ops,
		.id = RTS_V4L2_CID_DEHAZE_LEVEL,
		.name = "Dehaze level",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 255,
		.step = 1,
		.def = 128,
	};
	dehaze->enable_ctrl = rtsv_ctrl_new_custom(handler,
						   &enable_config, mod);
	dehaze->level_ctrl = rtsv_ctrl_new_custom(handler,
						  &level_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add dehaze ctrls fail");
		return handler->error;
	}

	return RTS_ISP_OK;
}

static struct isp_mod_dehaze dehaze;

int isp_register_mod_dehaze(void)
{
	memset(&dehaze, 0, sizeof(dehaze));
	dehaze.mod.id = MOD_DEHAZE;
	dehaze.mod.name = "dehaze";
	dehaze.mod.notify_bits = ISP_DYNAMIC_POST_BIT | ISP_MCROP_CHANGE_BIT;
	dehaze.mod.init = isp_mod_dehaze_init;
	dehaze.mod.cleanup = isp_mod_dehaze_cleanup;
	dehaze.mod.hardware_cleanup = isp_mod_dehaze_hardware_cleanup;
	dehaze.mod.add_ctrl = isp_mod_dehaze_add_ctrl;
	dehaze.mod.notify_actions = dehaze_notify_actions;
	dehaze.mod.notify_actions_num = ARRAY_SIZE(dehaze_notify_actions);
	return isp_mod_register(&dehaze.mod);
}

void isp_unregister_mod_dehaze(void)
{
	isp_mod_unregister(&dehaze.mod);
}

