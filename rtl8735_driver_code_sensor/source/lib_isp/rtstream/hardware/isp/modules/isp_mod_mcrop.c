/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_notify.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_mod_sensor.h>
#include <isp_mod_mcrop.h>
#include <isp_hw_mcrop.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_MCROP

struct isp_mod_mcrop {
	struct isp_mod mod;
	rts_isp_rect_t rect;
	const struct isp_hw_mcrop_ops *hw_ops;
};

static int mod_mcrop_info_mcrop_size(struct isp_mod *mod, void *data)
{
	struct isp_mod_mcrop *mcrop = get_mod(mod, mcrop);
	rts_isp_size_t *size = data;

	if (!mcrop->rect.w)
		return -RTS_ISP_ENOTREADY;

	*size = mcrop->rect.size;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info mcrop_info_actions[] = {
	ISP_MOD_ACTION(MCROP_INFO_ISP_SIZE, mod_mcrop_info_mcrop_size),
};

static int isp_mod_mcrop_init(struct isp_mod *mod)
{
	struct isp_mod_mcrop *mcrop;

	mcrop = get_mod(mod, mcrop);
	mcrop->hw_ops = isp_hw_mcrop_get_ops();
	if (mcrop->hw_ops == NULL) {
		isp_error("get mcrop hw ops fail\n");
		return -RTS_ISP_ENOOPS;
	}

	return RTS_ISP_OK;
}

static int isp_mod_mcrop_cleanup(struct isp_mod *mod)
{

	return RTS_ISP_OK;
}

static int mod_mcrop_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct rts_isp_info info;
	struct isp_mod_mcrop *mcrop = get_mod(mod, mcrop);
	const struct isp_sensor_mode mode;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		return ret;

	mcrop->rect.start.x = mcrop->rect.start.y = 0;
	mcrop->rect.size = mode.size.isp;
	ret = mcrop->hw_ops->set_crop(mod->owner_id, &mcrop->rect);
	if (ret)
		return ret;

	ret = isp_core_notify(mod->owner, ISP_NOTIFY_MCROP_CHANGE,
				    &mcrop->rect, sizeof(mcrop->rect));

	return ret;
}

static struct isp_mod_action_info mcrop_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_mcrop_mode_change),
};

static struct isp_mod_mcrop mcrop;

int isp_register_mod_mcrop(void)
{
	memset(&mcrop, 0, sizeof(mcrop));
	mcrop.mod.id = MOD_MCROP;
	mcrop.mod.name = "mcrop";
	mcrop.mod.notify_bits = ISP_HDR_MODE_CHANGE_BIT;
	mcrop.mod.init = isp_mod_mcrop_init;
	mcrop.mod.cleanup = isp_mod_mcrop_cleanup;
	mcrop.mod.info_actions = mcrop_info_actions;
	mcrop.mod.info_actions_num = ARRAY_SIZE(mcrop_info_actions);
	mcrop.mod.notify_actions = mcrop_notify_actions;
	mcrop.mod.notify_actions_num = ARRAY_SIZE(mcrop_notify_actions);
	return isp_mod_register(&mcrop.mod);
}

void isp_unregister_mod_mcrop(void)
{
	isp_mod_unregister(&mcrop.mod);
}

