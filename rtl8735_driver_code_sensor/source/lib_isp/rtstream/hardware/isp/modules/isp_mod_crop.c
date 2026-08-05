/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp.h>
#include <isp_mod.h>
#include <isp_core.h>
#include <isp_notify.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod_sensor.h>
#include <isp_mod_nlsc.h>
#include <isp_mod_crop.h>
#include <isp_hw_crop.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_CROP

struct isp_mod_crop {
	struct isp_mod mod;

	struct isp_sensor_mode mode;

	struct {
		struct v4l2_ctrl *crop_x_ctrl;
		struct v4l2_ctrl *crop_y_ctrl;
	};

	const struct isp_hw_crop_ops *hw_ops;

	rts_isp_point_t offset;
};

static int mod_crop_info_crop_size(struct isp_mod *mod, void *data)
{
	struct isp_mod_crop *crop = get_mod(mod, crop);
	rts_isp_size_t *size = data;

	*size = crop->mode.size.snr;
	return RTS_ISP_OK;
}

static struct isp_mod_action_info crop_info_actions[] = {
	ISP_MOD_ACTION(CROP_INFO_ISP_SIZE, mod_crop_info_crop_size),
};

static int crop_get_ctrl_range(struct isp_mod_crop *crop,
			       rts_isp_point_t *min, rts_isp_point_t *max,
			       rts_isp_point_t *def)
{
	int ret;
	int remain;
	rts_isp_rect_t rect;
	struct isp_sensor_mode *mode = &crop->mode;

	ret = isp_mod_sibling_get_info(&crop->mod, MOD_SENSOR, SENSOR_INFO_CROP,
				       &rect, sizeof(rect));
	if (ret)
		return ret;

	min->x = rect.start.x & 1;
	remain = max_t(int, mode->size.snr.w - mode->size.isp.w - min->x, 0);
	max->x = min->x + ALIGN_DOWN(remain, 2);
	def->x = rect.start.x;

	min->y = rect.start.y & 1;
	remain = max_t(int, mode->size.snr.h - mode->size.isp.h - min->y, 0);
	max->y = min->y + ALIGN_DOWN(remain, 2);
	def->y = rect.start.y;

	return RTS_ISP_OK;
}

static int crop_modify_ctrl_range(struct isp_mod_crop *crop,
				  const rts_isp_point_t *min,
				  const rts_isp_point_t *max,
				  const rts_isp_point_t *def)
{
	int ret;

	rtsv_ctrl_modify_range(crop->crop_x_ctrl, min->x, max->x, 2, def->x);
	rtsv_ctrl_modify_range(crop->crop_y_ctrl, min->y, max->y, 2, def->y);

	ret = rtsv_ctrl_s_ctrl(crop->crop_x_ctrl, def->x);
	if (ret)
		return ret;
	return rtsv_ctrl_s_ctrl(crop->crop_y_ctrl, def->y);
}

static int mod_crop_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	rts_isp_point_t min;
	rts_isp_point_t max;
	rts_isp_point_t def;
	const struct isp_sensor_mode mode;
	struct isp_mod_crop *crop = get_mod(mod, crop);

	ret = isp_mod_sibling_get_info(&crop->mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		return ret;
	crop->mode = mode;

	if (!crop->crop_x_ctrl || !crop->crop_y_ctrl)
		return RTS_ISP_OK;

	ret = crop_get_ctrl_range(crop, &min, &max, &def);
	if (ret)
		return ret;
	return crop_modify_ctrl_range(crop, &min, &max, &def);
}

static struct isp_mod_action_info crop_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_crop_mode_change),
};

static void crop_notify_callback(int ret, void *priv)
{
	isp_free(priv);
}

static int crop_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_crop *crop = get_mod(mod, crop);
	rts_isp_rect_t rect;
	rts_isp_point_t *offset;

	rect.size = crop->mode.size.isp;
	switch (ctrl->id) {
	case RTS_V4L2_CID_SNR_CROP_X:
	case RTS_V4L2_CID_SNR_CROP_Y:
		rect.start.x = crop->crop_x_ctrl->val;
		rect.start.y = crop->crop_y_ctrl->val;
		break;
	default:
		return -RTS_ISP_ECTRL;
	}

	ret = crop->hw_ops->set_crop(mod->owner_id, &rect);
	if (ret)
		return ret;
	offset = &(crop->offset);

	//if (!isp_calloc_item(offset))
	//	return -RTS_ISP_ENOMEM;
	//printf("isp_calloc_item %d \n", sizeof(rts_isp_point_t) );
	offset->x = crop->crop_x_ctrl->val - crop->crop_x_ctrl->default_value;
	offset->y = crop->crop_y_ctrl->val - crop->crop_y_ctrl->default_value;

	return isp_core_notify(mod->owner, ISP_NOTIFY_CROP_CHANGE, offset,
				     sizeof(*offset));
}

static const struct v4l2_ctrl_ops crop_ctrl_ops = {
	.s_ctrl = crop_s_ctrl,
};

static int isp_mod_crop_init(struct isp_mod *mod)
{
	struct isp_mod_crop *crop;

	crop = get_mod(mod, crop);
	crop->hw_ops = isp_hw_crop_get_ops();
	if (crop->hw_ops == NULL) {
		isp_error("get crop hw ops fail\n");
		return -RTS_ISP_ENOOPS;
	}

	return RTS_ISP_OK;
}

static int isp_mod_crop_cleanup(struct isp_mod *mod)
{

	return RTS_ISP_OK;
}

static int isp_mod_crop_add_ctrl(struct isp_mod *mod, void *phandler)
{
	int ret;
	struct isp_mod_crop *crop = get_mod(mod, crop);
	struct v4l2_ctrl_handler *handler = phandler;
	struct v4l2_ctrl_config crop_x_config = {
		.ops = &crop_ctrl_ops,
		.id = RTS_V4L2_CID_SNR_CROP_X,
		.name = "Sensor horizontal crop",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.step = 2,
	};
	struct v4l2_ctrl_config crop_y_config = {
		.ops = &crop_ctrl_ops,
		.id = RTS_V4L2_CID_SNR_CROP_Y,
		.name = "Sensor vertical crop",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.step = 2,
	};
	rts_isp_point_t min;
	rts_isp_point_t max;
	rts_isp_point_t def;

	ret = crop_get_ctrl_range(crop, &min, &max, &def);
	if (ret)
		return ret;
	crop_x_config.min = min.x;
	crop_x_config.max = max.x;
	crop_x_config.def = def.x;
	crop_y_config.min = min.y;
	crop_y_config.max = max.y;
	crop_y_config.def = def.y;

	crop->crop_x_ctrl = rtsv_ctrl_new_custom(handler, &crop_x_config, mod);
	crop->crop_y_ctrl = rtsv_ctrl_new_custom(handler, &crop_y_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add crop ctrls fail");
		return handler->error;
	}

	return RTS_ISP_OK;
}

static struct isp_mod_crop crop;

int isp_register_mod_crop(void)
{
	memset(&crop, 0, sizeof(crop));
	crop.mod.id = MOD_CROP;
	crop.mod.name = "crop";
	crop.mod.notify_bits = ISP_HDR_MODE_CHANGE_BIT;
	crop.mod.init = isp_mod_crop_init;
	crop.mod.cleanup = isp_mod_crop_cleanup;
	crop.mod.add_ctrl = isp_mod_crop_add_ctrl;
	crop.mod.info_actions = crop_info_actions;
	crop.mod.info_actions_num = ARRAY_SIZE(crop_info_actions);
	crop.mod.notify_actions = crop_notify_actions;
	crop.mod.notify_actions_num = ARRAY_SIZE(crop_notify_actions);
	return isp_mod_register(&crop.mod);
}

void isp_unregister_mod_crop(void)
{
	isp_mod_unregister(&crop.mod);
}

