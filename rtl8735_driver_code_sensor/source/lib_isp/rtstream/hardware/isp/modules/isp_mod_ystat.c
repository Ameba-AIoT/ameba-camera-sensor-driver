/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_top.h>
#include <isp_core.h>
#include <isp_statis.h>
#include <isp_notify.h>
#include <isp_mod.h>
#include <isp_core.h>
#include <isp_mod_crop.h>
#include <isp_mod_ystat.h>
#include <isp_hw_ystat.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_YSTAT

struct isp_mod_ystat {
	struct isp_mod mod;
	const struct isp_hw_ystat_ops *hw_ops;
	struct isp_ystat_hw_info hw_info;
};

static int mod_ystat_info_statis(struct isp_mod *mod, void *data)
{
	struct isp_mod_ystat *ystat = get_mod(mod, ystat);
	struct isp_mod_ystat_stat_info *info = data;

	info->info.win = ystat->hw_info.grid_info.size;
	info->info.hist_bins = ystat->hw_info.hist_bins;
	info->win_mean_size = ystat->hw_info.y_mean_size;
	info->hist_bin_size = ystat->hw_info.hist_bin_size;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info ystat_info_actions[] = {
	ISP_MOD_ACTION(YSTAT_INFO_STATIS, mod_ystat_info_statis),
};

static int isp_mod_ystat_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_ystat *ystat;

	ystat = get_mod(mod, ystat);
	ystat->hw_ops = isp_hw_ystat_get_ops();
	if (ystat->hw_ops == NULL) {
		isp_error("get ystat hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	ret = ystat->hw_ops->get_hw_info(mod->owner_id, &ystat->hw_info);
	if (ret)
		goto err;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_ystat_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_ystat_add_ctrl(struct isp_mod *mod, void *phandler)
{
	return RTS_ISP_OK;
}

static int mod_ystat_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	rts_isp_grid_t grid;
	struct isp_mod_ystat *ystat = get_mod(mod, ystat);
	const rts_isp_rect_t *rect = data;

	ret = rts_isp_get_grid_from_rect(&grid, rect,
					 &ystat->hw_info.grid_info);
	if (ret)
		return ret;
	return ystat->hw_ops->set_statis(mod->owner_id, &grid);
}

static struct isp_mod_action_info ystat_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_ystat_mcrop_change),
};

static struct isp_mod_ystat ystat;

int isp_register_mod_ystat(void)
{
	memset(&ystat, 0, sizeof(ystat));
	ystat.mod.id = MOD_YSTAT;
	ystat.mod.name = "ystat";
	ystat.mod.notify_bits = ISP_MCROP_CHANGE_BIT;
	ystat.mod.init = isp_mod_ystat_init;
	ystat.mod.cleanup = isp_mod_ystat_cleanup;
	ystat.mod.add_ctrl = isp_mod_ystat_add_ctrl;
	ystat.mod.info_actions = ystat_info_actions;
	ystat.mod.info_actions_num = ARRAY_SIZE(ystat_info_actions);
	ystat.mod.notify_actions = ystat_notify_actions;
	ystat.mod.notify_actions_num = ARRAY_SIZE(ystat_notify_actions);
	return isp_mod_register(&ystat.mod);
}

void isp_unregister_mod_ystat(void)
{
	isp_mod_unregister(&ystat.mod);
}
