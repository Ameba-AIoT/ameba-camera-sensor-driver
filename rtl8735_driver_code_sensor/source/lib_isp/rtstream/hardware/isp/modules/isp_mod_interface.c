/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_mod.h>
#include <isp_driver.h>
#include <isp_notify.h>
#include <isp_mod_sensor.h>
#include <isp_mod_global.h>
#include <isp_mod_interface.h>
#include <isp_hw_interface.h>
#include <isp_mod_sensor.h>
#include <isp_driver.h>
#include "hal_timer.h"
#include "hal_isp.h"

#define ISP_DEBUG_TYPE ISP_DEBUG_INTERFACE

struct isp_mod_interface {
	struct isp_mod mod;
	struct isp_interface_info info;
	const struct isp_hw_interface_ops *hw_ops;
	int started:1;
};

#include "../sensor/include/voe_ops.h"


voe_ops_t voe_ops ={
	.ops.printf = printf,
	.ops.rts_isp_sensor_access_prepare = rts_isp_sensor_access_prepare,
	.ops.rts_isp_sensor_access_unprepare = rts_isp_sensor_access_unprepare,
	.ops.rts_isp_read_sensor_reg = rts_isp_read_sensor_reg,
	.ops.rts_isp_write_sensor_reg = rts_isp_write_sensor_reg,
	.ops.rts_isp_read_i2c_regs = rts_isp_read_i2c_regs,
	.ops.rts_isp_write_i2c_regs = rts_isp_write_i2c_regs,
	.ops.rts_isp_read_i2c_reg = rts_isp_read_i2c_reg,
	.ops.rts_isp_write_i2c_reg = rts_isp_write_i2c_reg,
	.ops.rts_isp_sensor_get_open_mode = rts_isp_sensor_get_open_mode,
	.ops.rts_isp_sensor_get_close_mode = rts_isp_sensor_get_close_mode,
	.ops.hal_delay_us = hal_delay_us,
	.ops.isp_driver_mem_alloc = isp_driver_mem_alloc,
	.ops.isp_driver_mem_free = isp_driver_mem_free,
	.ops.isp_driver_mmap = isp_driver_mmap,
	.ops.hal_isp_get_verify_info = hal_isp_get_verify_info,
	.ops.sensor_get_slave_addr_idx = sensor_get_slave_addr_idx,
};

void mod_set_voe_for_sensor(void)
{
	extern void* __get_sensor_ops__[];
	void (*_rts_isp_set_voe_ops)(voe_ops_t *ops) = ( void (*)(voe_ops_t *ops))(__get_sensor_ops__[1]);
	_rts_isp_set_voe_ops(&voe_ops);
}

void mod_get_sensor_info(int hdr_mode, int *fps)
{
	struct rts_isp_sensor_info sensor_info;

	extern void* __get_sensor_ops__[];

	struct rts_isp_sensor_ops* (*_rts_isp_get_sensor_ops)(void) = ( struct rts_isp_sensor_ops* (*)(void))(__get_sensor_ops__[0]);
	struct rts_isp_sensor_ops* sensor_ops = _rts_isp_get_sensor_ops();

	sensor_ops->get_info(0,&sensor_info);

	*fps = (int)sensor_info.modes.mode[hdr_mode].fps;
}
static int mod_interface_exec_start(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_interface *interface = get_mod(mod, interface);
	struct isp_interface_info *info = &interface->info;
	enum rts_isp_interface inf;
	struct rts_isp_sensor_info sensor_info;
	uint8_t lanes, lanes_num;

	extern void* __get_sensor_ops__[];

	struct rts_isp_sensor_ops* (*_rts_isp_get_sensor_ops)(void) = ( struct rts_isp_sensor_ops* (*)(void))(__get_sensor_ops__[0]);
	struct rts_isp_sensor_ops* sensor_ops = _rts_isp_get_sensor_ops();

	if (interface->started)
		return RTS_ISP_OK;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_INTERFACE,
				       &info->info, sizeof(info->info));
	if (ret)
		return ret;

	inf = info->info->interface;

	sensor_ops->get_info(0,&sensor_info);
	lanes = info->info->mipi.lanes;
	while (lanes) {
		lanes_num++;
		lanes &= lanes - 1;
	};

	if (inf == SNR_INTERFACE_MIPI) {
		//interface->info.interface_clk = hdr_mode.pclk * info->info->bit_depth / lanes_num / 2;
		info->interface_clk = info->pixel_clk;
		
		ret = isp_driver_set_clk(CLK_INTERFACE,
					 &info->interface_clk);
		if (ret) {
			isp_error("isp_driver_set_clk error %d \n", ret);
			return ret;
		}

		if (info->interface_clk < info->pixel_clk) {
			isp_error("interface_clk: %u, pixel_clk: %u\n\r",
				info->interface_clk, info->pixel_clk);
			info->interface_clk = 0;
			isp_driver_set_clk(CLK_INTERFACE,
					   &info->interface_clk);
			isp_perror(ret, "interface_clk < pixel_clk");
			return -RTS_ISP_ERANGE;
		}
	}

	ret = isp_driver_sel_pin_state(inf);
	if (ret) {
		isp_perror(ret, "isp_driver_sel_pin_state");
		goto out;
	}
	ret = interface->hw_ops->start_transfer(mod->owner_id,
						&interface->info);
	if (ret) {
		isp_perror(ret, "start_transfer");
		goto out;
	}
	ret = isp_mod_sibling_execute(mod, MOD_GLOBAL,
				      GLOBAL_EXEC_SELECT_INTERFACE,
				      &inf, sizeof(inf));
out:
	if (ret) {
		isp_driver_sel_pin_state(SNR_INTERFACE_NONE);
		isp_perror(ret, "interface start fail");
		return ret;
	}
	interface->started = RTS_ISP_TRUE;
	return RTS_ISP_OK;
}

static int mod_interface_exec_stop(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_interface *interface = get_mod(mod, interface);
	enum rts_isp_interface inf = interface->info.info->interface;

	if (!interface->started)
		return RTS_ISP_OK;

	ret = interface->hw_ops->stop_transfer(mod->owner_id, &interface->info);
	if (ret)
		goto err;
	ret = isp_driver_sel_pin_state(SNR_INTERFACE_NONE);
	if (ret)
		goto err;
	if (inf == SNR_INTERFACE_MIPI) {
		interface->info.interface_clk = 0;
		isp_driver_set_clk(CLK_INTERFACE,
				   &interface->info.interface_clk);
	}

	interface->started = RTS_ISP_FALSE;

	return RTS_ISP_OK;
err:
	isp_perror(ret, "interface stop fail");

	return ret;
}

static struct isp_mod_action_info interface_exec_actions[] = {
	ISP_MOD_ACTION(INTERFACE_EXEC_START, mod_interface_exec_start),
	ISP_MOD_ACTION(INTERFACE_EXEC_STOP, mod_interface_exec_stop),
};

static int mod_interface_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_sensor_mode hdr_mode;
	struct isp_mod_interface *interface = get_mod(mod, interface);
	struct isp_interface_info *info = &interface->info;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_INTERFACE,
				       &info->info, sizeof(info->info));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &hdr_mode, sizeof(hdr_mode));
	if (ret)
		return ret;
	info->size = hdr_mode.size.snr;
	info->pixel_clk = hdr_mode.pclk;
	info->mode = hdr_mode.hdr;
	info->hdr.behavor = hdr_mode.mipi_behavor;


	ret = isp_mod_sibling_get_info(mod, MOD_GLOBAL, GLOBAL_INFO_IS_FPGA,
				       &info->is_fpga, sizeof(info->is_fpga));
	if (ret)
		return ret;

	if (info->info->interface == SNR_INTERFACE_DVP)
		interface->hw_ops = isp_hw_dvp_get_ops();
	else if (info->info->interface == SNR_INTERFACE_MIPI)
		interface->hw_ops = isp_hw_mipi_get_ops();
	else if (info->info->interface == SNR_INTERFACE_FIXP)
		interface->hw_ops = isp_hw_fixp_get_ops();
	else if (info->info->interface == SNR_INTERFACE_NONE)
		interface->hw_ops = isp_hw_vinf_get_ops();
	if (interface->hw_ops == NULL) {
		isp_error("get interface hw ops fail\n");
		return -RTS_ISP_ENOOPS;
	}

	return RTS_ISP_OK;
}

static struct isp_mod_action_info interface_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_interface_mode_change),
};

static int isp_mod_interface_init(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_interface_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static struct isp_mod_interface interface;

int isp_register_mod_interface(void)
{
	memset(&interface, 0, sizeof(interface));
	interface.mod.id = MOD_INTERFACE;
	interface.mod.name = "interface";
	interface.mod.notify_bits = ISP_HDR_MODE_CHANGE_BIT;
	interface.mod.init = isp_mod_interface_init;
	interface.mod.cleanup = isp_mod_interface_cleanup;
	interface.mod.exec_actions = interface_exec_actions;
	interface.mod.exec_actions_num = ARRAY_SIZE(interface_exec_actions);
	interface.mod.notify_actions = interface_notify_actions;
	interface.mod.notify_actions_num = ARRAY_SIZE(interface_notify_actions);
	return isp_mod_register(&interface.mod);
}

void isp_unregister_mod_interface(void)
{
	isp_mod_unregister(&interface.mod);
}

