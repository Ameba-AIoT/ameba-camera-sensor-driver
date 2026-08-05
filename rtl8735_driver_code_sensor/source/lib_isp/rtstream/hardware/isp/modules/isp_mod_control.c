/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#define DEBUG

#include <isp_top.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_v4l2_ctrl.h>
#include <isp_statis.h>
#include <isp_driver.h>
#include <isp_mod_sensor.h>
#include <isp_mod_interface.h>
#include <isp_mod_global.h>
#include <isp_mod_statis.h>
#include <isp_mod_control.h>
#include "hal_timer.h"
#include <math.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_CONTROL

#define MAX_STREAM_NUM 8

struct isp_mod_control {
	struct isp_mod mod;
	struct v4l2_ctrl_handler *ctrl_handler;
	float current_fps;
};

static int stop_isp_pipeline(struct isp_mod *mod);

static int set_sensor_fps(struct isp_mod *mod, float fps)
{
	return isp_mod_sibling_execute(mod, MOD_SENSOR, SENSOR_EXEC_SET_FPS,
				       &fps, sizeof(fps));
}

static int start_isp_pipeline(struct isp_mod *mod)
{
	int ret;

	isp_info("start isp pipeline\n");

	ret = isp_mod_sibling_execute(mod, MOD_GLOBAL, GLOBAL_EXEC_START, NULL,
				      0);
	if (ret)
		goto err;
	ret = isp_mod_sibling_execute(mod, MOD_INTERFACE, INTERFACE_EXEC_START,
				      NULL, 0);
	if (ret)
		goto err;
	return RTS_ISP_OK;

err:
	isp_perror(ret, "start isp pipeline fail");
	stop_isp_pipeline(mod);
	return ret;
}

static int stop_isp_pipeline(struct isp_mod *mod)
{
	int ret;

	isp_info("stop isp pipeline\n");

	ret = isp_mod_sibling_execute(mod, MOD_INTERFACE, INTERFACE_EXEC_STOP,
				      NULL, 0);
	if (ret)
		goto err;
	//isp_error("stop isp pipeline GLOBAL_EXEC_STOP\n");
	ret = isp_mod_sibling_execute(mod, MOD_GLOBAL, GLOBAL_EXEC_STOP, NULL,
				      0);
	if (ret)
		goto err;
	return RTS_ISP_OK;
err:
	isp_perror(ret, "stop isp pipeline fail");
	return ret;
}
uint32_t setv4l2 = 0, aftipipe = 0, aftsetfps = 0;
static int mod_control_start_isp(struct isp_mod *mod, float fps)
{
	int ret;
	struct isp_mod_control *control = get_mod(mod, control);
	setv4l2 = hal_read_curtime_us();
	ret = rtsv_ctrl_handler_setup(control->ctrl_handler);
	if (ret)
		goto err;

	//mod_iq_start_pre already call iq_dynamic_notify
	//so remove iq_dynamic_run here

	ret = isp_core_notify(mod->owner, ISP_NOTIFY_START_PRE, NULL, 0);
	if (ret)
		goto err;
	ret = start_isp_pipeline(mod);
	if (ret)
		goto err;
	aftipipe = hal_read_curtime_us();
	ret = set_sensor_fps(mod, fps);
	aftsetfps = hal_read_curtime_us();
	if (ret)
		goto err;
	ret = isp_core_notify(mod->owner, ISP_NOTIFY_START_POST, NULL, 0);
	if (ret)
		goto err;

	isp_top_set_status(RTS_ISP_STREAMING);

	return RTS_ISP_OK;

err:
	set_sensor_fps(mod, 0);
	stop_isp_pipeline(mod);
	isp_perror(ret, "fail to start isp pipeline");
	return ret;
}

static int mod_control_stop_isp(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_control *control = get_mod(mod, control);

	ret = isp_core_notify(mod->owner, ISP_NOTIFY_STOP_PRE, NULL, 0);
	if (ret)
		goto err;
	ret = set_sensor_fps(mod, 0);
	if (ret)
		goto err;
	ret = stop_isp_pipeline(mod);
	if (ret)
		goto err;
	ret = isp_core_notify(mod->owner, ISP_NOTIFY_STOP_POST, NULL, 0);
	if (ret)
		goto err;
	rtsv_ctrl_handler_backup_auto(control->ctrl_handler);

	isp_top_set_status(RTS_ISP_RUNNING);

	return RTS_ISP_OK;

err:
	isp_error(" %s stop isp pipeline 0x%08x \r\n", __func__, ret);
	return ret;
}

static int mod_control_change_fps(struct isp_mod *mod, float fps)
{
	int ret;

	ret = set_sensor_fps(mod, fps);
	if (ret) {
		isp_perror(ret, "change sensor fps fail");
		return ret;
	}

	return RTS_ISP_OK;
}

static int mod_control_exec_set_fps(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_control *control = get_mod(mod, control);
	struct rts_isp_preview_info *info = data;
	float fps = (float) info->fps;
	isp_info("%s info %d current_fps %d \r\n", __func__, info->fps, control->current_fps);
	if (fps == control->current_fps)
		return RTS_ISP_OK;

	if (float_eq(control->current_fps, 0))
		ret = mod_control_start_isp(mod, fps);
	else if (float_eq(fps, 0))
		ret = mod_control_stop_isp(mod);
	else
		ret = mod_control_change_fps(mod, fps);
	if (!ret)
		control->current_fps = fps;
	isp_info("%s info %f current_fps %f done \r\n", __func__, fps, control->current_fps);
	return ret;
}

static int mod_control_exec_statis_done(struct isp_mod *mod, void *data)
{
	int ret;
	isp_core_t core;
	struct isp_statis *statis;
	const struct rts_isp_statis *all = NULL;
	struct rts_isp_statis_data *statis_data = data;

	core = isp_top_get_core(mod->owner_id);
	statis = isp_core_get_statis(core);
	ret = isp_statis_update(statis, statis_data);
	if (ret) {
		isp_driver_put_statis(statis_data->buf_id);
		goto out;
	}
	ret = isp_statis_get_all(statis, &all);
	if (ret) {
		isp_driver_put_statis(statis_data->buf_id);
		goto out;
	}
	isp_statis_ref(statis, all);
	ret = isp_core_notify(core, ISP_NOTIFY_STATIS_DONE,
			      (void *)all, sizeof(*all));
	isp_statis_unref(statis, all);

out:
	if (ret)
		isp_perror(ret, "statis done handle");
	//isp_info("%s \r\n",__func__);
	return ret;
}

static struct isp_mod_action_info control_exec_actions[] = {
	ISP_MOD_ACTION(CONTROL_EXEC_SET_FPS, mod_control_exec_set_fps),
	ISP_MOD_ACTION(CONTROL_EXEC_STATIS_DONE, mod_control_exec_statis_done),
};

static int isp_mod_control_init(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_control_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int isp_mod_control_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_control *control = get_mod(mod, control);

	control->ctrl_handler = phandler;
	return RTS_ISP_OK;
}

static struct isp_mod_control control;

int isp_register_mod_control(void)
{
	memset(&control, 0, sizeof(control));
	control.mod.id = MOD_CONTROL;
	control.mod.name = "control";
	control.mod.init = isp_mod_control_init;
	control.mod.cleanup = isp_mod_control_cleanup;
	control.mod.add_ctrl = isp_mod_control_add_ctrl;
	control.mod.exec_actions = control_exec_actions;
	control.mod.exec_actions_num = ARRAY_SIZE(control_exec_actions);
	control.mod.virtual = RTS_ISP_TRUE;
	return isp_mod_register(&control.mod);
}

void isp_unregister_mod_control(void)
{
	isp_mod_unregister(&control.mod);
}

