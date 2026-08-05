/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */

#include <isp_notify.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_crop.h>
#include <isp_mod_iq.h>
#include <isp_mod_intp.h>
#include <isp_hw_intp.h>

struct isp_mod_intp {
	struct isp_mod mod;
	const struct isp_hw_intp_ops *hw_ops;
	uint8_t drc_blending_rate;

	struct v4l2_ctrl *drc_mode_ctrl;
	struct v4l2_ctrl *drc_blending_rate_ctrl;
};

static int mod_intp_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_intp *intp = get_mod(mod, intp);
	const struct isp_notify_dynamic *dynamic;
	float awb_g_gain, ae_gain, sensor_gain;

	if (intp->drc_mode_ctrl->cur.val == RTS_ISP_DRC_MODE_MANUAL) {
		intp->drc_blending_rate = intp->drc_blending_rate_ctrl->cur.val;
	}

	ret = intp->hw_ops->estimation(mod->owner_id,
		(enum rts_isp_drc_mode)intp->drc_mode_ctrl->cur.val,
		&intp->drc_blending_rate);
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_IQ, IQ_INFO_DYNAMIC,
				       &dynamic, sizeof(dynamic));
	if (ret)
		return ret;

	awb_g_gain = dynamic->awb.r_gain;
	ae_gain = dynamic->ae.isp_gain;

	// HDR related change
	sensor_gain = *dynamic->ae.sensor_gain;
	//isp_info("%s \r\n",__func__);
	return intp->hw_ops->dynamic(mod->owner_id, awb_g_gain, ae_gain,
				      sensor_gain);
}

static int mod_intp_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_intp *intp = get_mod(mod, intp);
	const rts_isp_rect_t *rect = data;
	rts_isp_size_t size = rect->size;


	return intp->hw_ops->set_frame_size(mod->owner_id, &size);
}

static struct isp_mod_action_info intp_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_intp_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_intp_mcrop_change),
};

static int intp_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_intp *intp = get_mod(mod, intp);

	switch (ctrl->id) {
	case RTS_V4L2_CID_DRC_BLENDING_RATE:
		intp->drc_blending_rate_ctrl->val = intp->drc_blending_rate;
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	return RTS_ISP_OK;
}

static int intp_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_intp *intp = get_mod(mod, intp);

	switch (ctrl->id) {
	case RTS_V4L2_CID_DRC_MODE:
		intp->drc_mode_ctrl->cur.val = ctrl->val;
		break;
	case RTS_V4L2_CID_DRC_BLENDING_RATE:
		intp->drc_blending_rate_ctrl->cur.val = ctrl->val;
		break;
	default:
		ret = -RTS_ISP_ECTRL;
		break;
	}
	if (ret)
		isp_perror(ret, "set intp ctrl fail");
	return ret;
}

static const struct v4l2_ctrl_ops intp_ctrl_ops = {
	.g_volatile_ctrl = intp_g_volatile_ctrl,
	.s_ctrl = intp_s_ctrl,
};

static int isp_mod_intp_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_intp *intp;

	intp = get_mod(mod, intp);
	intp->hw_ops = isp_hw_intp_get_ops();
	if (intp->hw_ops == NULL) {
		isp_error("get intp hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_intp_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_intp_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_intp *intp = get_mod(mod, intp);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config drc_mode_config = {
		.ops = &intp_ctrl_ops,
		.id = RTS_V4L2_CID_DRC_MODE,
		.name = "DRC Mode",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = RTS_ISP_DRC_MODE_AUTO,
		.max = RTS_ISP_DRC_MODE_MANUAL,
		.step = 1,
		.def = RTS_ISP_DRC_MODE_AUTO,
	};
	const struct v4l2_ctrl_config drc_blending_rate_config = {
		.ops = &intp_ctrl_ops,
		.id = RTS_V4L2_CID_DRC_BLENDING_RATE,
		.name = "DRC Blending Rate",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 0,
		.max = 15,
		.step = 1,
		.def = 15,
		.flags = V4L2_CTRL_FLAG_VOLATILE | V4L2_CTRL_FLAG_EXECUTE_ON_WRITE,
	};

	intp->drc_mode_ctrl = rtsv_ctrl_new_custom(
		handler, &drc_mode_config, mod);
	intp->drc_blending_rate_ctrl = rtsv_ctrl_new_custom(
		handler, &drc_blending_rate_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add intp ctrl fail");
		return handler->error;
	}

	intp->drc_blending_rate = drc_blending_rate_config.def;

	return RTS_ISP_OK;
}

static struct isp_mod_intp intp;

int isp_register_mod_intp(void)
{
	memset(&intp, 0, sizeof(intp));
	intp.mod.id = MOD_INTP;
	intp.mod.name = "intp";
	intp.mod.notify_bits = ISP_STATIS_DONE_BIT | ISP_MCROP_CHANGE_BIT;
	intp.mod.init = isp_mod_intp_init;
	intp.mod.cleanup = isp_mod_intp_cleanup;
	intp.mod.add_ctrl = isp_mod_intp_add_ctrl;
	intp.mod.notify_actions = intp_notify_actions;
	intp.mod.notify_actions_num = ARRAY_SIZE(intp_notify_actions);
	return isp_mod_register(&intp.mod);
}

void isp_unregister_mod_intp(void)
{
	isp_mod_unregister(&intp.mod);
}

