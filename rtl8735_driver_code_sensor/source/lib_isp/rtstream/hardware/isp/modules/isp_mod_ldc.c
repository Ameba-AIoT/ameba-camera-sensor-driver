/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_v4l2_ctrl.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_mod_sensor.h>
#include <isp_mod_ldc.h>
#include <isp_mod_global.h>
#include <isp_hw_ldc.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_LDC

struct isp_mod_ldc {
	struct isp_mod mod;
	struct v4l2_ctrl *ldc_ctrl;
};

static int isp_mod_ldc_init(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_ldc_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int ldc_s_ctrl(struct v4l2_ctrl *ctrl)
{
	uint32_t ldc_enable;
	struct isp_mod *mod = ctrl->priv;

	if (ctrl->id != RTS_V4L2_CID_LDC)
		return -RTS_ISP_ECTRL;
	ldc_enable = ctrl->val;
	return isp_mod_sibling_execute(mod, MOD_GLOBAL,
				       GLOBAL_EXEC_SET_LDC_ENABLE,
				       &ldc_enable, sizeof(ldc_enable));
}

static const struct v4l2_ctrl_ops ldc_ctrl_ops = {
	.s_ctrl = ldc_s_ctrl,
};

static int isp_mod_ldc_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_ldc *ldc = get_mod(mod, ldc);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config ldc_config = {
		.ops = &ldc_ctrl_ops,
		.id = RTS_V4L2_CID_LDC,
		.name = "Lens distortion correction",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	};

	ldc->ldc_ctrl = rtsv_ctrl_new_custom(handler, &ldc_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add ldc ctrls fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_ldc ldc;

int isp_register_mod_ldc(void)
{
	memset(&ldc, 0, sizeof(ldc));
	ldc.mod.id = MOD_LDC;
	ldc.mod.name = "ldc";
	ldc.mod.init = isp_mod_ldc_init;
	ldc.mod.cleanup = isp_mod_ldc_cleanup;
	ldc.mod.add_ctrl = isp_mod_ldc_add_ctrl;
	return isp_mod_register(&ldc.mod);
}

void isp_unregister_mod_ldc(void)
{
	isp_mod_unregister(&ldc.mod);
}

