/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_mod.h>
#include <isp_mod_ygamma.h>
#include <isp_v4l2_ctrl.h>
#include <isp_hw_ygamma.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_GAMMA

struct isp_mod_ygamma {
	struct isp_mod mod;
	const struct isp_hw_ygamma_ops *hw_ops;
	struct v4l2_ctrl *gamma_ctrl;
	struct {
		struct v4l2_ctrl *auto_ygamma_ctrl;
		struct v4l2_ctrl *ygamma_curve_ctrl;
	};
	uint8_t ygamma_curve_set[16];
};

static int __mod_ygamma_set(struct isp_mod *mod)
{
	struct isp_mod_ygamma *ygamma = get_mod(mod, ygamma);

	if (ygamma->auto_ygamma_ctrl && !ygamma->auto_ygamma_ctrl->val)
		return RTS_ISP_OK;

	return ygamma->hw_ops->set_ygamma(mod->owner_id,
					  ygamma->ygamma_curve_set,
					  ARRAY_SIZE(ygamma->ygamma_curve_set));
}

static int ygamma_set_gamma(struct isp_mod *mod, int value)
{
	struct isp_mod_ygamma *ygamma = get_mod(mod, ygamma);
	int def = ygamma->gamma_ctrl->default_value;
	int max = ygamma->gamma_ctrl->maximum;
	int min = ygamma->gamma_ctrl->minimum;
	uint8_t ygamma_curve_max[16] = {
		0, 8, 16, 45, 61, 73, 84, 93, 102, 118, 133, 146, 159, 182, 204,
		224,
	};
	uint8_t ygamma_curve_min[16] = {
		0, 8, 16, 17, 19, 22, 26, 31, 36, 47, 61, 76, 93, 131, 175, 224,
	};
	uint8_t ygamma_curve_def[16] = {
		0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192,
		224,
	};

	if (value >= def)
		linear_intp_array(ygamma->ygamma_curve_set, value, def,
				  ygamma_curve_def, max, ygamma_curve_max,
				  ARRAY_SIZE(ygamma_curve_def));
	else
		linear_intp_array(ygamma->ygamma_curve_set, value, def,
				  ygamma_curve_def, min, ygamma_curve_min,
				  ARRAY_SIZE(ygamma_curve_def));
	return __mod_ygamma_set(mod);
}

static int ygamma_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	int i;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ygamma *ygamma = get_mod(mod, ygamma);

	switch (ctrl->id) {
	case RTS_V4L2_CID_AUTO_YGAMMA:
		for (i = 0; i < (int)ARRAY_SIZE(ygamma->ygamma_curve_set); i++)
			ygamma->ygamma_curve_ctrl->p_new.p_u8[i] =
						ygamma->ygamma_curve_set[i];
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int ygamma_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_ygamma *ygamma = get_mod(mod, ygamma);
	uint8_t curve[16];
	int i;

	switch (ctrl->id) {
	case V4L2_CID_GAMMA:
		ret = ygamma_set_gamma(mod, ctrl->val);
		break;
	case RTS_V4L2_CID_AUTO_YGAMMA:
		if (ctrl->val) {
			if (ctrl->is_new)
				ret = __mod_ygamma_set(mod);
		} else if (ygamma->ygamma_curve_ctrl->is_new) {
			for (i = 0; i < (int)ARRAY_SIZE(curve); i++)
				curve[i] =
				ygamma->ygamma_curve_ctrl->p_new.p_u8[i];
			ret = ygamma->hw_ops->set_ygamma(mod->owner_id, curve,
							 ARRAY_SIZE(curve));
		}
		break;
	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set ygamma ctrl fail");
	return ret;
}

static const struct v4l2_ctrl_ops ygamma_ctrl_ops = {
	.g_volatile_ctrl = ygamma_g_volatile_ctrl,
	.s_ctrl = ygamma_s_ctrl,
};

static int isp_mod_ygamma_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_ygamma *ygamma;

	ygamma = get_mod(mod, ygamma);
	ygamma->hw_ops = isp_hw_ygamma_get_ops();
	if (ygamma->hw_ops == NULL) {
		isp_error("get ygamma hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_ygamma_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_ygamma_hardware_init(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_ygamma_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_ygamma *ygamma = get_mod(mod, ygamma);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config auto_ygamma_config = {
		.ops = &ygamma_ctrl_ops,
		.id = RTS_V4L2_CID_AUTO_YGAMMA,
		.name = "Auto Ygamma",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 1,
	};
	const struct v4l2_ctrl_config ygamma_curve_config = {
		.ops = &ygamma_ctrl_ops,
		.id = RTS_V4L2_CID_YGAMMA_CURVE,
		.name = "Ygamma Curve",
		.type = V4L2_CTRL_TYPE_U8,
		.min = 0,
		.max = 255,
		.step = 1,
		.def = 0,
		.dims = {ARRAY_SIZE(ygamma->ygamma_curve_set)},
	};

	ygamma->gamma_ctrl = rtsv_ctrl_new_std(handler, &ygamma_ctrl_ops,
					       V4L2_CID_GAMMA,
					       100, 500, 1, 300, mod);
	ygamma->auto_ygamma_ctrl = rtsv_ctrl_new_custom(handler,
						&auto_ygamma_config, mod);
	ygamma->ygamma_curve_ctrl = rtsv_ctrl_new_custom(handler,
						&ygamma_curve_config, mod);
	rtsv_ctrl_auto_cluster(2, &ygamma->auto_ygamma_ctrl, 0, RTS_ISP_TRUE);
	if (handler->error) {
		isp_perror(handler->error, "add ygamma ctrl fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_ygamma ygamma;

int isp_register_mod_ygamma(void)
{
	memset(&ygamma, 0, sizeof(ygamma));
	ygamma.mod.id = MOD_YGAMMA;
	ygamma.mod.name = "ygamma";
	ygamma.mod.init = isp_mod_ygamma_init;
	ygamma.mod.cleanup = isp_mod_ygamma_cleanup;
	ygamma.mod.add_ctrl = isp_mod_ygamma_add_ctrl;
	ygamma.mod.hardware_init = isp_mod_ygamma_hardware_init;
	return isp_mod_register(&ygamma.mod);
}

void isp_unregister_mod_ygamma(void)
{
	isp_mod_unregister(&ygamma.mod);
}

