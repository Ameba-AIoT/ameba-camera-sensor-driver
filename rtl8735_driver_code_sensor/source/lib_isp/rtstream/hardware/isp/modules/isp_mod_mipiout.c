/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */
#if 0
#include <isp_mod.h>
#include <isp_driver.h>
#include <isp_mod_global.h>
#include <isp_mod_sensor.h>
#include <isp_mod_crop.h>
#include <isp_mod_mcrop.h>
#include <isp_mod_mipiout.h>
#include <isp_hw_mipiout.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_MIPIOUT

struct isp_mod_mipiout {
	struct isp_mod mod;
	struct isp_mipiout_info info;
	const struct isp_hw_mipiout_ops *hw_ops;
};

static int mipiout_check_config(const struct rts_isp_mipiout *mipiout)
{
	int lane_num;
	if (!mipiout || !mipiout->lanes)
		return -RTS_ISP_EINVAL;
	lane_num = isp_get_val_weight(mipiout->lanes);

	if (lane_num != 1 && lane_num != 2 && lane_num != 4)
		return -RTS_ISP_EINVAL;
	if (mipiout->position < RTS_ISP_MIPIOUT_BEFORE_CROP ||
	    mipiout->position > RTS_ISP_MIPIOUT_BEFORE_ZOOM)
		return -RTS_ISP_EINVAL;
	if (mipiout->type < RTS_ISP_MIPIOUT_RAW8 ||
	    mipiout->type > RTS_ISP_MIPIOUT_YUYV)
		return -RTS_ISP_EINVAL;
	if (mipiout->position == RTS_ISP_MIPIOUT_BEFORE_ZOOM &&
	    mipiout->type != RTS_ISP_MIPIOUT_YUYV)
		return -RTS_ISP_EINVAL;
	if (mipiout->position != RTS_ISP_MIPIOUT_BEFORE_ZOOM &&
	    mipiout->type == RTS_ISP_MIPIOUT_YUYV)
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int mipiout_get_bit_depth(enum rts_isp_mipiout_type type)
{
	switch (type) {
	case RTS_ISP_MIPIOUT_RAW8:
		return 8;
	case RTS_ISP_MIPIOUT_RAW10:
		return 10;
	case RTS_ISP_MIPIOUT_RAW12:
		return 12;
	case RTS_ISP_MIPIOUT_YUYV:
	default:
		return 16;
	}
}

static int mod_mipiout_set(struct isp_mod *mod,
			   const struct rts_isp_mipiout *mo)
{
	int ret;
	uint32_t isp_clk;
	struct isp_mipiout_info info;
	struct isp_mod_mipiout *mipiout = get_mod(mod, mipiout);
	uint32_t mipiout_rate;

	ret = isp_mod_sibling_get_info(mod, MOD_GLOBAL, GLOBAL_INFO_ISP_CLK,
				       &isp_clk, sizeof(isp_clk));
	if (ret)
		return ret;
	if (!isp_clk)
		return -RTS_ISP_ENOTREADY;
	info.mipiout = *mo;
	info.is_fpga = mipiout->info.is_fpga;
	info.mipi_clk = ((float)isp_clk * mipiout_get_bit_depth(mo->type) /
			 isp_get_val_weight(mo->lanes));
	mipiout_rate = info.mipiout.enable;
	if (mo->position == RTS_ISP_MIPIOUT_BEFORE_CROP)
		ret = isp_mod_sibling_get_info(mod, MOD_SENSOR,
					       SENSOR_INFO_SIZE,
					       &info.size, sizeof(info.size));
	else if (mo->position == RTS_ISP_MIPIOUT_AFTER_CROP)
		ret = isp_mod_sibling_get_info(mod, MOD_CROP,
					       CROP_INFO_ISP_SIZE,
					       &info.size, sizeof(info.size));
	else
		ret = isp_mod_sibling_get_info(mod, MOD_MCROP,
					       MCROP_INFO_ISP_SIZE,
					       &info.size, sizeof(info.size));
	if (ret)
		return ret;
	ret = isp_driver_set_clk(CLK_MIPIOUT, &mipiout_rate);
	if (ret)
		return ret;
	ret = mipiout->hw_ops->set(mod->owner_id, &info);
	if (ret) {
		mipiout->hw_ops->set(mod->owner_id, &mipiout->info);
		mipiout_rate = mipiout->info.mipiout.enable;
		isp_driver_set_clk(CLK_MIPIOUT, &mipiout_rate);
		return ret;
	}

	mipiout->info.mipi_clk = info.mipi_clk;
	mipiout->info.size = info.size;

	return RTS_ISP_OK;
}

static int mod_mipiout_exec_get(struct isp_mod *mod, void *data)
{
	struct isp_mod_mipiout *mipiout = get_mod(mod, mipiout);

	*(struct rts_isp_mipiout *)data = mipiout->info.mipiout;

	return RTS_ISP_OK;
}

static int mod_mipiout_exec_set(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_mipiout *mipiout = get_mod(mod, mipiout);
	const struct rts_isp_mipiout *mo = data;

	ret = mipiout_check_config(mo);
	if (ret)
		return ret;

	if (memcmp(mo, &mipiout->info.mipiout, sizeof(*mo)) == 0)
		return RTS_ISP_OK;

	if (!mo->enable && !mipiout->info.mipiout.enable) {
		mipiout->info.mipiout = *mo;
		return RTS_ISP_OK;
	}

	ret = mod_mipiout_set(mod, mo);
	if (ret)
		return ret;

	mipiout->info.mipiout = *mo;

	return RTS_ISP_OK;
}

static struct isp_mod_action_info mipiout_exec_actions[] = {
	ISP_MOD_ACTION(MIPIOUT_EXEC_GET, mod_mipiout_exec_get),
	ISP_MOD_ACTION(MIPIOUT_EXEC_SET, mod_mipiout_exec_set),
};

static int isp_mod_mipiout_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_mipiout *mipiout;

	mipiout = get_mod(mod, mipiout);
	mipiout->hw_ops = isp_hw_mipiout_get_ops();
	if (mipiout->hw_ops == NULL) {
		isp_error("get mipiout hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	ret = isp_mod_sibling_get_info(mod, MOD_GLOBAL, GLOBAL_INFO_IS_FPGA,
				       &mipiout->info.is_fpga,
				       sizeof(mipiout->info.is_fpga));
	if (ret)
		goto err;
	mipiout->info.mipiout.enable = 0;
	mipiout->info.mipiout.lanes = 0xf;
	mipiout->info.mipiout.position = RTS_ISP_MIPIOUT_AFTER_CROP;
	mipiout->info.mipiout.type = RTS_ISP_MIPIOUT_RAW12;

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_mipiout_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static struct isp_mod_mipiout mipiout;

int isp_register_mod_mipiout(void)
{
	memset(&mipiout, 0, sizeof(mipiout));
	mipiout.mod.id = MOD_MIPIOUT;
	mipiout.mod.name = "mipiout";
	mipiout.mod.init = isp_mod_mipiout_init;
	mipiout.mod.cleanup = isp_mod_mipiout_cleanup;
	mipiout.mod.exec_actions = mipiout_exec_actions;
	mipiout.mod.exec_actions_num = ARRAY_SIZE(mipiout_exec_actions);
	return isp_mod_register(&mipiout.mod);
}

void isp_unregister_mod_mipiout(void)
{
	isp_mod_unregister(&mipiout.mod);
}
#endif
