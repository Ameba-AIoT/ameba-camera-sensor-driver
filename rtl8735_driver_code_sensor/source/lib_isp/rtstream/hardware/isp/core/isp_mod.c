/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rtscamkit.h>
#include <isp_top.h>
#include <isp_mem.h>
#include <isp_log.h>
#include <isp_core.h>
#include <isp_mod.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_MOD
//#define  _ISP_MOD_INFO


static int check_actions(const struct isp_mod_action_info *actions,
			 uint32_t actions_num, int is_notify)
{
	int i;

	if (!!actions ^ !!actions_num)
		return -RTS_ISP_EINVAL;
	if (is_notify) {
		for (i = 0; i < (int)actions_num; i++)
			if (!actions[i].id || !actions[i].action)
				return -RTS_ISP_EINVAL;
	} else {
		for (i = 0; i < (int)actions_num; i++)
			if ((int)ISP_AID_NR(actions[i].id) != i ||
			    !actions[i].action)
				return -RTS_ISP_EINVAL;
	}
	return RTS_ISP_OK;
}

static int check_mod(const struct isp_mod *mod)
{
	if (!mod || !mod->id || !mod->name)
		return -RTS_ISP_EINVAL;
	if (!mod->init || !mod->cleanup)
		return -RTS_ISP_EINVAL;
	if (mod->virtual && (mod->hardware_init || mod->hardware_cleanup))
		return -RTS_ISP_EINVAL;
	if (mod->notify_bits && !mod->notify_actions)
		return -RTS_ISP_EINVAL;
	if (check_actions(mod->info_actions, mod->info_actions_num, 0) ||
	    check_actions(mod->exec_actions, mod->exec_actions_num, 0) ||
	    check_actions(mod->notify_actions, mod->notify_actions_num, 1))
		return -RTS_ISP_EINVAL;
	if (mod->next || mod->real_notify_bits || mod->owner)
		return -RTS_ISP_EINVAL;
	if (mod->initialized || mod->hardware_initialized || mod->ctrl_added)
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int check_id_data(uint32_t id, uint8_t type, void *data, size_t len)
{
	if (ISP_AID_TYPE(id) != type) {
		isp_error("%s type error 0x%08x %d %d\r\n", __FUNCTION__, id, ISP_AID_TYPE(id), type);
		return -RTS_ISP_EINVAL;
	}
	if (ISP_AID_SIZE(id) != len){
		isp_error("%s len error 0x%08x %d %d \r\n", __FUNCTION__, id, ISP_AID_SIZE(id), len);
		return -RTS_ISP_EINVAL;
	}
	if (len && !data){
		isp_error("%s data error\r\n", __FUNCTION__);
		return -RTS_ISP_EINVAL;
	}
	return RTS_ISP_OK;
}

static int mod_do_action(struct isp_mod *mod, uint32_t id, void *data,
			     const struct isp_mod_action_info *actions,
			     size_t actions_num)
{
	if (ISP_AID_NR(id) >= actions_num)
		return -RTS_ISP_EINVAL;
	if (!actions || !actions_num)
		return -RTS_ISP_EPERM;
	return actions[ISP_AID_NR(id)].action(mod, data);
}

int isp_mod_register(struct isp_mod *mod)
{
	int ret;
	isp_core_t core;

	if (check_mod(mod)) {
		isp_error("%s module format error\n", mod ? mod->name : "nil");
		return -RTS_ISP_EINVAL;
	}

	core = isp_top_get_core(mod->owner_id);
	if (!core) {
		ret = -RTS_ISP_EINVAL;
		goto err;
	}
	ret = isp_core_register_mod(core, mod);
	if (ret)
		goto err;
	mod->owner = core;
#ifdef _ISP_MOD_INFO
	isp_info("module %s registered\r\n", mod->name);
#endif
	return RTS_ISP_OK;

err:
	isp_perror(ret, "register module %s fail", mod->name);
	return ret;
}

int isp_mod_unregister(struct isp_mod *mod)
{
	if (!mod)
		return -RTS_ISP_EINVAL;

	isp_core_unregister_mod(mod->owner, mod);

	mod->next = NULL;
	mod->real_notify_bits = 0;
	mod->owner = NULL;
	mod->initialized = RTS_ISP_FALSE;
	mod->hardware_initialized = RTS_ISP_FALSE;
	mod->ctrl_added = RTS_ISP_FALSE;

	//isp_info("module %s unregistered\n", mod->name);
	return RTS_ISP_OK;
}

int isp_mod_init(struct isp_mod *mod)
{
	int ret;

	if (!mod)
		return -RTS_ISP_EINVAL;
	if (mod->initialized)
		return RTS_ISP_OK;

	if (isp_call_op_ret(ret, mod, init)) {
		isp_perror(ret, "module %s init fail", mod->name);
	} else {
		mod->initialized = RTS_ISP_TRUE;
		//isp_info("module %s init ok\r\n", mod->name);
	}

	return ret;
}

int isp_mod_cleanup(struct isp_mod *mod)
{
	int ret;

	if (!mod)
		return -RTS_ISP_EINVAL;
	if (!mod->initialized)
		return RTS_ISP_OK;
	if (mod->hardware_initialized)
		return -RTS_ISP_EBUSY;

	if (isp_call_op_ret(ret, mod, cleanup)) {
		isp_perror(ret, "module %s cleanup fail", mod->name);
	} else {
		mod->initialized = RTS_ISP_FALSE;
		//isp_info("module %s cleanup ok\n", mod->name);
	}

	return ret;
}

int isp_mod_hardware_init(struct isp_mod *mod)
{
	int ret;

	if (!mod)
		return -RTS_ISP_EINVAL;
	if (mod->hardware_initialized)
		return RTS_ISP_OK;
	if (!mod->initialized)
		return -RTS_ISP_ENOTREADY;
	if (!mod->hardware_init) {
		mod->hardware_initialized = RTS_ISP_TRUE;
		return RTS_ISP_OK;
	}

	if (isp_call_op_ret(ret, mod, hardware_init)) {
		isp_perror(ret, "module %s hardware init fail", mod->name);
	} else {
		mod->hardware_initialized = RTS_ISP_TRUE;
		//isp_info("module %s hardware init ok\r\n", mod->name);
	}

	return ret;
}

int isp_mod_hardware_cleanup(struct isp_mod *mod)
{
	int ret;

	if (!mod)
		return -RTS_ISP_EINVAL;
	if (!mod->hardware_initialized)
		return RTS_ISP_OK;
	if (!mod->hardware_cleanup) {
		mod->hardware_initialized = RTS_ISP_FALSE;
		return RTS_ISP_OK;
	}

	if (isp_call_op_ret(ret, mod, hardware_cleanup)) {
		isp_perror(ret, "module %s hardware cleanup fail", mod->name);
	} else {
		mod->hardware_initialized = RTS_ISP_FALSE;
		//isp_info("module %s hardware cleanup ok\r\n", mod->name);
	}

	return ret;
}

int isp_mod_add_ctrl(struct isp_mod *mod, void *phandler)
{
	int ret;

	if (!mod || !phandler)
		return -RTS_ISP_EINVAL;
	if (!mod->initialized)
		return -RTS_ISP_ENOTREADY;
	if (!mod->virtual && !mod->hardware_initialized)
		return -RTS_ISP_ENOTREADY;

	if (mod->ctrl_added)
		return RTS_ISP_OK;

	if (!mod->add_ctrl)
		return RTS_ISP_OK;

	if (isp_call_op_ret(ret, mod, add_ctrl, phandler)) {
		isp_perror(ret, "module %s add ctrl fail", mod->name);
	} else {
		mod->ctrl_added = RTS_ISP_TRUE;
#ifdef _ISP_MOD_INFO
		isp_info("module %s add ctrl ok\r\n", mod->name);
#endif
	}

	return ret;
}

int isp_mod_action_need_block(struct isp_mod *mod, uint32_t id,
			      void *data, size_t len)
{
	int ret;

	if (!mod || ISP_AID_SIZE(id) != len || (len && !data))
		return -RTS_ISP_EINVAL;
	if (!mod->initialized)
		return -RTS_ISP_ENOTREADY;
	if (!mod->need_block)
		return RTS_ISP_FALSE;

	isp_call_op_ret(ret, mod, need_block, id, data);

	return ret;
}

int isp_mod_get_info(struct isp_mod *mod, uint32_t id, void *info, size_t len)
{
	int ret;

	if (!mod || check_id_data(id, INFO_TYPE, info, len))
		return -RTS_ISP_EINVAL;
	if (!mod->initialized && isp_mod_init(mod))
		return -RTS_ISP_ENOTREADY;

	ret = mod_do_action(mod, id, info, mod->info_actions,
			    mod->info_actions_num);
	if (ret)
		isp_error("module %s get info 0x%x fail %d \r\n", mod->name, id, ret);
#ifdef _ISP_MOD_INFO
	else
		isp_info("module %s get info 0x%x ok\r\n", mod->name, id);
#endif

	return ret;
}

int isp_mod_execute(struct isp_mod *mod, uint32_t id, void *data, size_t len)
{
	int ret;

	if (!mod || !mod->name || check_id_data(id, EXEC_TYPE, data, len))
	{
		isp_error("%s id 0x%08x fail\r\n", __FUNCTION__, id);
		return -RTS_ISP_EINVAL;
	}
	if (!mod->initialized)
		return -RTS_ISP_ENOTREADY;
	if (!mod->virtual && !mod->hardware_initialized)
		return -RTS_ISP_ENOTREADY;

	ret = mod_do_action(mod, id, data, mod->exec_actions,
			    mod->exec_actions_num);
	if (ret)
		isp_error("module %s execute 0x%x fail %d \r\n", mod->name, id, ret);
#ifdef _ISP_MOD_INFO
	else
		isp_info("module %s execute 0x%x ok\r\n", mod->name, id);
#endif

	return ret;
}

int isp_mod_notify(struct isp_mod *mod, uint32_t id, void *data, size_t len)
{
	int i;
	int ret;
	isp_mod_action action = NULL;
#ifdef _ISP_MOD_INFO
	int start_t, end_t;
#endif
	if (!mod || !mod->name || check_id_data(id, NOTIFY_TYPE, data, len)) {
		isp_error("%s mod_id: 0x%08x fail \r\n", __func__, id);
		return -RTS_ISP_EINVAL;
	}


	if (!mod->initialized) {
		isp_error("%s module %s 0x%08x mod initialized \r\n", __func__, mod->name, id);
		return -RTS_ISP_ENOTREADY;
	}

	if (!mod->virtual && !mod->hardware_initialized) {
		isp_error("%s module %s 0x%08x mod hardware_initialized \r\n", __func__, mod->name, id);
		return -RTS_ISP_ENOTREADY;
	}

	if ((mod->real_notify_bits & (1 << ISP_AID_NR(id))) == 0)
		return RTS_ISP_OK;
	for (i = 0; i < (int)mod->notify_actions_num; i++)
		if (mod->notify_actions[i].id == id) {
			action = mod->notify_actions[i].action;
			//printf("%s module %s id 0x%08x action_num %d \r\n", __func__, mod->name, id, i);
		}

	if (!action) {
		isp_error("%s module %s 0x%08x action %d NULL \r\n", __func__, mod->name, id, i);
		return -RTS_ISP_EINVAL;
	}

#ifdef _ISP_MOD_INFO
		start_t = hal_read_curtime_us();
#endif
	ret = action(mod, data);

#ifdef _ISP_MOD_INFO
		end_t = hal_read_curtime_us();
		dbg_printf("module %s 0x%08x  time %d \r\n", mod->name, id, end_t-start_t);
#endif



	if (ret)
		isp_perror(ret, "module %s notify 0x%x fail", mod->name, id);
#ifdef _ISP_MOD_INFO
	else
		isp_info("module %s notify 0x%x ok\r\n", mod->name, id);
#endif
	return ret;
}

int isp_mod_do_action(struct isp_mod *mod, uint32_t id, void *data, size_t len)
{
	int ret;

	if (!mod || ISP_AID_SIZE(id) != len || (len && !data))
		return -RTS_ISP_EINVAL;
	if (!mod->initialized)
		return -RTS_ISP_ENOTREADY;
	if (!mod->virtual && !mod->hardware_initialized)
		return -RTS_ISP_ENOTREADY;

	switch (ISP_AID_TYPE(id)) {
	case INFO_TYPE:
		ret = mod_do_action(mod, id, data, mod->info_actions,
				    mod->info_actions_num);
		break;
	case EXEC_TYPE:
		ret = mod_do_action(mod, id, data, mod->exec_actions,
				    mod->exec_actions_num);
		break;
	case NOTIFY_TYPE:
		ret = -RTS_ISP_EACCES;
		break;
	default:
		ret = -RTS_ISP_ENOOPS;
	}
	if (ret) {
		isp_error("module %s do action 0x%x fail %d \r\n", mod->name, id, ret);
	}

#ifdef _ISP_MOD_INFO
	else
		isp_info("module %s do action 0x%x ok\r\n", mod->name, id);
#endif

	return ret;
}

int isp_mod_add_notify(struct isp_mod *mod, uint32_t notify_id)
{
	if (!mod)
		return -RTS_ISP_EINVAL;
#ifdef _ISP_MOD_INFO
	isp_info("%s %s id 0x%08x\r\n", __FUNCTION__, mod->name, notify_id);
#endif

	return isp_core_add_notify_entry(mod->owner, mod, notify_id);
}

int isp_mod_del_notify(struct isp_mod *mod, uint32_t notify_id)
{
	if (!mod)
		return -RTS_ISP_EINVAL;
#ifdef _ISP_MOD_INFO
	isp_info("%s %s id 0x%08x\r\n", __FUNCTION__, mod->name, notify_id);
#endif
	return isp_core_del_notify_entry(mod->owner, mod, notify_id);
}

int isp_mod_sibling_get_info(struct isp_mod *mod, int mod_id, int id,
			     void *data, size_t len)
{
	return isp_mod_get_info(isp_mod_get_sibling(mod, mod_id),
				id, data, len);
}

int isp_mod_sibling_execute(struct isp_mod *mod, int mod_id, int id,
			    void *data, size_t len)
{
	return isp_mod_execute(isp_mod_get_sibling(mod, mod_id),
			       id, data, len);
}

int isp_mod_sibling_notify(struct isp_mod *mod, int mod_id, int id,
			   void *data, size_t len)
{
	return isp_mod_notify(isp_mod_get_sibling(mod, mod_id),
			      id, data, len);
}

struct isp_mod *isp_mod_get_sibling(struct isp_mod *mod, int mod_id)
{
	struct isp_mod *get;

	if (!mod)
		return NULL;
	if (isp_core_get_mod(mod->owner, mod_id, &get))
		return NULL;
	return get;
}

/* helper functions */
#include <isp_notify.h>

int isp_mod_set_smooth_notify(struct isp_mod *mod, int add)
{
	int ret;

	if (add) {
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			return ret;
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_DYNAMIC);
	} else {
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			return ret;
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_DYNAMIC);
	}
#ifdef _ISP_MOD_INFO
	isp_info("%s %s done \n", __func__, mod->name);
#endif
	return ret;
}
