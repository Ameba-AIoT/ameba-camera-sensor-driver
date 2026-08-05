/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */
#include <isp_top.h>
#include <rts_isp.h>
#include <isp_notify.h>
#include <isp_driver.h>
#include <isp_v4l2_ctrl.h>
#include <isp_mod.h>
#include <isp_mod_crop.h>
#include <isp_mod_iq.h>
#include <isp_mod_tnr.h>
#include <isp_mod_sensor.h>
#include <isp_hw_tnr.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_TNR

struct isp_mod_tnr {
	struct isp_mod mod;
	const struct isp_hw_tnr_ops *hw_ops;
	struct v4l2_ctrl *tnr_ctrl;
	uint32_t phy_addr_align;
	uint32_t phy_addr_vm;
};

static void tnr_release_memory(struct isp_mod_tnr *tnr)
{
	if (tnr->phy_addr_vm) {
		isp_driver_mem_free(tnr->phy_addr_vm);
		tnr->phy_addr_vm = tnr->phy_addr_align = 0;
	}
}

static int isp_mod_tnr_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_tnr *tnr;

	tnr = get_mod(mod, tnr);
	tnr->hw_ops = isp_hw_tnr_get_ops();
	if (tnr->hw_ops == NULL) {
		isp_error("get tnr hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_tnr_cleanup(struct isp_mod *mod)
{
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);

	if (!isp_top_get_raw_mode_tnr_en())
		return 0;

	tnr_release_memory(tnr);

	return RTS_ISP_OK;
}

static int mod_tnr_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);
	const struct isp_notify_dynamic *dynamic;

	if (!isp_top_get_raw_mode_tnr_en())
		return 0;

	ret = tnr->hw_ops->estimation(mod->owner_id);
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_IQ, IQ_INFO_DYNAMIC,
				       &dynamic, sizeof(dynamic));
	if (ret)
		return ret;
	//isp_info("%s \r\n",__func__);
	//HDR related change
	return tnr->hw_ops->dynamic(mod->owner_id, *dynamic->ae.total_gain);
}

static int mod_tnr_start_pre(struct isp_mod *mod, void *data)
{
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);

	if (!isp_top_get_raw_mode_tnr_en())
		return 0;

	return tnr->hw_ops->enable_axi(mod->owner_id, RTS_ISP_TRUE);
}

static int mod_tnr_stop_pre(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);

	if (!isp_top_get_raw_mode_tnr_en())
		return 0;

	ret = tnr->hw_ops->enable(mod->owner_id, RTS_ISP_FALSE);
	if (ret)
		return ret;
	return tnr->hw_ops->enable_axi(mod->owner_id, RTS_ISP_FALSE);
}

static int mod_tnr_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	int bit;
	uint32_t length;
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);
	const struct isp_sensor_mode mode;

	if (!isp_top_get_raw_mode_tnr_en())
		return 0;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		return ret;
	tnr_release_memory(tnr);
	ret = isp_driver_get_tnr_bit();
	if (ret < 0)
		goto out;
	bit = ret;
	length = mode.size.isp.w * mode.size.isp.h * bit / 8 + 256;
	ret = isp_driver_mem_alloc(&tnr->phy_addr_vm, length, "TNR");
	if (ret)
		goto out;
	tnr->phy_addr_align = ((tnr->phy_addr_vm + 255) & ~255);
	ret = tnr->hw_ops->set_ddr(mod->owner_id, tnr->phy_addr_align, length, bit);
	if (ret)
		goto out;

out:
	if (ret)
		tnr_release_memory(tnr);
	//printf("%s 0x%08x size %d \r\n",__func__, tnr->phy_addr_align, length);
	return ret;
}

static struct isp_mod_action_info tnr_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_tnr_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_START_PRE, mod_tnr_start_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_PRE, mod_tnr_stop_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_tnr_mode_change),
};

static int tnr_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);

	if (ctrl->id != RTS_V4L2_CID_TEMPORAL_DENOISE)
		return -RTS_ISP_ECTRL;
	return tnr->hw_ops->enable(mod->owner_id, ctrl->val);
}

static const struct v4l2_ctrl_ops tnr_ctrl_ops = {
	.s_ctrl = tnr_s_ctrl,
};

static int isp_mod_tnr_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_tnr *tnr = get_mod(mod, tnr);
	struct v4l2_ctrl_handler *handler = phandler;
	const struct v4l2_ctrl_config tnr_config = {
		.ops = &tnr_ctrl_ops,
		.id = RTS_V4L2_CID_TEMPORAL_DENOISE,
		.name = "Temporal denoise",
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.min = 0,
		.max = 1,
		.step = 1,
		.def = isp_top_get_raw_mode_tnr_en(),
	};

	tnr->tnr_ctrl = rtsv_ctrl_new_custom(handler, &tnr_config, mod);
	if (handler->error) {
		isp_perror(handler->error, "add tnr ctrls fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_tnr tnr;

int isp_register_mod_tnr(void)
{
	memset(&tnr, 0, sizeof(tnr));
	tnr.mod.id = MOD_TNR;
	tnr.mod.name = "tnr";
	tnr.mod.notify_bits = ISP_STATIS_DONE_BIT | ISP_START_PRE_BIT | ISP_STOP_PRE_BIT |
						  ISP_HDR_MODE_CHANGE_BIT;
	tnr.mod.init = isp_mod_tnr_init;
	tnr.mod.cleanup = isp_mod_tnr_cleanup;
	tnr.mod.notify_actions = tnr_notify_actions;
	tnr.mod.notify_actions_num = ARRAY_SIZE(tnr_notify_actions);
	tnr.mod.add_ctrl = isp_mod_tnr_add_ctrl;
	return isp_mod_register(&tnr.mod);
}

void isp_unregister_mod_tnr(void)
{
	isp_mod_unregister(&tnr.mod);
}

