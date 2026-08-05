/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_mod_spe.h>
#include <isp_hw_spe.h>
#include <isp_v4l2_ctrl.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_SPE

struct isp_mod_spe {
	struct isp_mod mod;
	const struct isp_hw_spe_ops *hw_ops;
	const isp_iq_spe_t *iq;

	isp_algo_param_spe_t *param;

	struct v4l2_ctrl *brightness_ctrl;
	struct v4l2_ctrl *contrast_ctrl;
	struct v4l2_ctrl *saturation_ctrl;
	struct v4l2_ctrl *gray_mode_ctrl;
	struct v4l2_ctrl *y_gain_ctrl;
};

static int check_spe_iq(const isp_iq_spe_t *iq)
{
	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (isp_iq_check_hysteresis_bounds(&iq->uv_offset.bounds,
					   iq->uv_offset.items_count))
		return -RTS_ISP_EINVAL;

	return -RTS_ISP_OK;
}

static int spe_set_brightness(struct isp_mod *mod, int value)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->set_brightness(mod->owner_id, value);
}

static int spe_set_contrast(struct isp_mod *mod, int value)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->set_contrast(mod->owner_id, value);
}

static int spe_set_saturation(struct isp_mod *mod, int value)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->set_saturation(mod->owner_id, value);
}

static int spe_set_gray_mode(struct isp_mod *mod, int enable)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->set_gray_mode(mod->owner_id, enable);
}

static int spe_set_y_gain(struct isp_mod *mod, int value)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->set_y_gain(mod->owner_id, value);
}

static int spe_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ret = spe_set_brightness(mod, ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		ret = spe_set_contrast(mod, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		ret = spe_set_saturation(mod, ctrl->val);
		break;
	case RTS_V4L2_CID_GRAY:
		ret = spe_set_gray_mode(mod, ctrl->val);
		break;
	case RTS_V4L2_CID_Y_GAIN:
		ret = spe_set_y_gain(mod, ctrl->val);
		break;
	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set spe ctrl fail");
	return ret;
}

static const struct v4l2_ctrl_ops spe_ctrl_ops = {
	.s_ctrl = spe_s_ctrl,
};

static int isp_mod_spe_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_spe *spe;

	spe = get_mod(mod, spe);
	spe->hw_ops = isp_hw_spe_get_ops();
	if (spe->hw_ops == NULL) {
		isp_error("get spe hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	spe->param = &isp_iq_get_algo_param(mod->owner_id)->spe;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_spe_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_spe_hardware_init(struct isp_mod *mod)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);

	return spe->hw_ops->init_vreg(mod->owner_id);
}

static int mod_spe_change_dyn_iq_notify(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_spe *spe = get_mod(mod, spe);
	const isp_iq_spe_t *iq = spe->iq;

	if (iq->uv_offset.enable)
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	else
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

static int mod_spe_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_spe *spe = get_mod(mod, spe);
	const isp_iq_spe_t *iq;

	spe->iq = isp_iq_get_spe(mod->owner_id);
	if (check_spe_iq(spe->iq))
		return -RTS_ISP_EINVAL;
	iq = spe->iq;

	spe->param->ct_index = iq->uv_offset.bounds.def_index;
	ret = spe->hw_ops->set_uv_offset(mod->owner_id,
			&iq->uv_offset.items[spe->param->ct_index]);
	if (ret)
		return ret;
	//isp_info("%s done \r\n", __func__);
	return mod_spe_change_dyn_iq_notify(mod);
}

static int mod_spe_dynamic(struct isp_mod *mod, void *data)
{
	int index;
	struct isp_mod_spe *spe = get_mod(mod, spe);
	const isp_iq_spe_t *iq = spe->iq;
	const struct isp_notify_dynamic *dyn = data;

	index = isp_iq_get_hysteresis_bound(&iq->uv_offset.bounds,
					    dyn->awb.color_temp,
					    spe->param->ct_index);
	if (index == spe->param->ct_index)
		return RTS_ISP_OK;

	spe->param->ct_index = index;

	return spe->hw_ops->set_uv_offset(mod->owner_id,
					  &iq->uv_offset.items[index]);
}

static int mod_spe_dynamic_post(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_spe *spe = get_mod(mod, spe);

	if (!spe->brightness_ctrl ||
	    !spe->saturation_ctrl || !spe->contrast_ctrl)
		return RTS_ISP_OK;

	ret = spe_set_brightness(mod, spe->brightness_ctrl->cur.val);
	if (ret)
		return ret;
	ret = spe_set_saturation(mod, spe->saturation_ctrl->cur.val);
	if (ret)
		return ret;
	return spe_set_contrast(mod, spe->contrast_ctrl->cur.val);
}

static struct isp_mod_action_info spe_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_spe_iq_change),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC, mod_spe_dynamic),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_DYNAMIC_POST, mod_spe_dynamic_post),
};

static int isp_mod_spe_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_spe *spe = get_mod(mod, spe);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config gray_config = {
		.ops = &spe_ctrl_ops,
		.id = RTS_V4L2_CID_GRAY,
		.name = "Gray Mode",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = 0,
	};
	const struct v4l2_ctrl_config ygain_config = {
		.ops = &spe_ctrl_ops,
		.id = RTS_V4L2_CID_Y_GAIN,
		.name = "y gain",
		.type = V4L2_CTRL_TYPE_U8,
		.min = YGAIN_CTRL_MIN,
		.max = YGAIN_CTRL_MAX,
		.step = 1,
		.def = YGAIN_CTRL_DEF,
	};

	spe->brightness_ctrl = rtsv_ctrl_new_std(handler, &spe_ctrl_ops,
						 V4L2_CID_BRIGHTNESS,
						 BRIGHT_CTRL_MIN,
						 BRIGHT_CTRL_MAX, 1,
						 BRIGHT_CTRL_DEF, mod);
	spe->contrast_ctrl = rtsv_ctrl_new_std(handler, &spe_ctrl_ops,
					       V4L2_CID_CONTRAST,
					       CONTRAST_CTRL_MIN,
					       CONTRAST_CTRL_MAX, 1,
					       CONTRAST_CTRL_DEF, mod);
	spe->saturation_ctrl = rtsv_ctrl_new_std(handler, &spe_ctrl_ops,
						 V4L2_CID_SATURATION,
						 SATURATION_CTRL_MIN,
						 SATURATION_CTRL_MAX, 1,
						 SATURATION_CTRL_DEF, mod);
	spe->gray_mode_ctrl = rtsv_ctrl_new_custom(handler, &gray_config, mod);
	spe->y_gain_ctrl = rtsv_ctrl_new_custom(handler, &ygain_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add spe ctrl fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_spe spe;

int isp_register_mod_spe(void)
{
	memset(&spe, 0, sizeof(spe));
	spe.mod.id = MOD_SPE;
	spe.mod.name = "spe";
	spe.mod.notify_bits = ISP_IQ_CHANGE_BIT | ISP_DYNAMIC_POST_BIT;
	spe.mod.init = isp_mod_spe_init;
	spe.mod.cleanup = isp_mod_spe_cleanup;
	spe.mod.hardware_init = isp_mod_spe_hardware_init;
	spe.mod.add_ctrl = isp_mod_spe_add_ctrl;
	spe.mod.notify_actions = spe_notify_actions;
	spe.mod.notify_actions_num = ARRAY_SIZE(spe_notify_actions);
	return isp_mod_register(&spe.mod);
}

void isp_unregister_mod_spe(void)
{
	isp_mod_unregister(&spe.mod);
}

