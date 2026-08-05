/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_top.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_notify.h>
#include <isp_statis.h>
#include <isp_v4l2_ctrl.h>
#include <isp_iq.h>
#include <isp_core.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_CORE

//#define DEFAULT_ISP_MOD_BUCKETS_NUM 23
#define DEFAULT_ISP_MOD_BUCKETS_NUM 37

struct isp_mod_hash_table {
	struct isp_mod **mod_buckets;
	uint32_t nmod_buckets;
};

struct isp_core {
	struct isp_mod_hash_table hash;
	struct isp_notify notify;
	struct v4l2_ctrl_handler ctrl_handler;
	struct isp_statis statis;
	struct isp_iq iq;

	int initialized;
	int running;
};

static int core_mod_hash_table_init(struct isp_mod_hash_table *hash)
{
	if (!hash)
		return -RTS_ISP_EINVAL;

	hash->nmod_buckets = DEFAULT_ISP_MOD_BUCKETS_NUM;
	// coverity[bad_sizeof]
	if (!isp_calloc_array(hash->mod_buckets, hash->nmod_buckets)) {
		isp_error("alloc mod hash table memory fail\n");
		return -RTS_ISP_ENOMEM;
	}
	return RTS_ISP_OK;
}

static int core_mod_hash_table_cleanup(struct isp_mod_hash_table *hash)
{
	if (!hash)
		return -RTS_ISP_EINVAL;

	isp_free(hash->mod_buckets);
	hash->nmod_buckets = 0;

	return RTS_ISP_OK;
}

static int core_add_mod_to_hash(struct isp_mod_hash_table *hash,
				struct isp_mod *mod)
{
	struct isp_mod *node;
	int bucket;

	if (!hash || !mod)
		return -RTS_ISP_EINVAL;

	bucket = mod->id % hash->nmod_buckets;
	node = hash->mod_buckets[bucket];

	while (node) {
		if (node->id == mod->id)
			return -RTS_ISP_EEXIST;
		if (!node->next)
			break;
		node = node->next;
	}

	if (!node)
		hash->mod_buckets[bucket] = mod;
	else
		node->next = mod;

	return RTS_ISP_OK;
}

static int core_del_mod_from_hash(struct isp_mod_hash_table *hash,
				  const struct isp_mod *mod)
{
	struct isp_mod *pre = NULL;
	struct isp_mod *node;
	int bucket;

	if (!hash || !mod)
		return -RTS_ISP_EINVAL;

	bucket = mod->id % hash->nmod_buckets;
	node = hash->mod_buckets[bucket];

	while (node) {
		if (node->id == mod->id)
			break;
		pre = node;
		node = node->next;
	}

	if (node) {
		if (pre)
			pre->next = node->next;
		else
			hash->mod_buckets[bucket] = node->next;
	}

	return RTS_ISP_OK;
}

static int core_parse_all_mod(isp_core_t core, int (*func)(struct isp_mod *))
{
	int ret;
	int i;
	struct isp_mod_hash_table *hash;
	struct isp_mod *mod;

	if (!core || !func)
		return -RTS_ISP_EINVAL;

	hash = &core->hash;
	for (i = 0; i < (int)hash->nmod_buckets; i++) {
		mod = hash->mod_buckets[i];
		while (mod) {
			ret = func(mod);
			if (ret) {
				isp_perror(ret, "parse module: %s error",
					   mod->name);
				return ret;
			}
			mod = mod->next;
		}
	}
	return RTS_ISP_OK;
}

static int core_parse_all_mod_data(isp_core_t core,
				   int (*func)(struct isp_mod *, void *data),
				   void *data)
{
	int ret;
	int i;
	struct isp_mod_hash_table *hash;
	struct isp_mod *mod;

	if (!core || !func)
		return -RTS_ISP_EINVAL;

	hash = &core->hash;
	for (i = 0; i < (int)hash->nmod_buckets; i++) {
		mod = hash->mod_buckets[i];
		while (mod) {
			ret = func(mod, &core->ctrl_handler);
			if (ret) {
				isp_perror(ret, "parse module: %s error",
					   mod->name);
				return ret;
			}
			mod = mod->next;
		}
	}
	return RTS_ISP_OK;
}

//int isp_core_pre_init(isp_core_t *pcore)
int isp_core_create(isp_core_t *pcore)
{
	int ret;
	struct isp_core *isp_table;

	if (!pcore)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(isp_table)) {
		isp_error("alloc isp table memory fail\n");
		ret = -RTS_ISP_ENOMEM;
		goto err;
	}

	ret = core_mod_hash_table_init(&isp_table->hash);
	if (ret)
		goto err;
	ret = isp_notify_init(&isp_table->notify);
	if (ret)
		goto err;
	*pcore = isp_table;

	debug("%s ok\r\n", __func__);

	return RTS_ISP_OK;

err:
	//isp_core_post_cleanup(pcore);
	isp_core_release(&isp_table);
	*pcore = NULL;
	debug("%s fail\n", __func__);
	return ret;
}

//int isp_core_post_cleanup(isp_core_t *pcore)
int isp_core_release(isp_core_t *pcore)
{
	isp_core_t core;

	if (!pcore)
		return -RTS_ISP_EINVAL;
	core = *pcore;
	if (!core)
		return -RTS_ISP_EINVAL;

	isp_notify_cleanup(&core->notify);
	core_mod_hash_table_cleanup(&core->hash);
	isp_free(core);
	*pcore = NULL;
	debug("%s ok\n", __func__);

	return RTS_ISP_OK;
}

int isp_core_register_mod(isp_core_t core, struct isp_mod *mod)
{
	int ret;

	if (!core || !mod)
		return -RTS_ISP_EINVAL;

	ret = core_add_mod_to_hash(&core->hash, mod);
	if (ret) {
		isp_perror(ret, "mod: %s exist", mod->name);
		return ret;
	}
	ret = isp_notify_add_mod(&core->notify, mod);
	if (ret) {
		isp_perror(ret, "add %s to notify list fail", mod->name);
		return ret;
	}

	return RTS_ISP_OK;
}

int isp_core_unregister_mod(isp_core_t core, struct isp_mod *mod)
{
	if (!core || !mod)
		//return RTS_ISP_OK;
		return -RTS_ISP_EINVAL;

	isp_notify_del_mod(&core->notify, mod);
	core_del_mod_from_hash(&core->hash, mod);
	return RTS_ISP_OK;
}

int isp_core_get_mod(isp_core_t core, uint32_t id, struct isp_mod **pmod)
{
	struct isp_mod_hash_table *hash = &core->hash;
	int bucket;
	struct isp_mod *node;

	if (!core || !id || !pmod)
		return -RTS_ISP_EINVAL;

	bucket = id % hash->nmod_buckets;
	node = hash->mod_buckets[bucket];
	while (node) {
		if (node->id == id)
			break;
		node = node->next;
	}

	if (node) {
		*pmod = node;
		return RTS_ISP_OK;
	} else {
		*pmod = NULL;
		return -RTS_ISP_ENOITEM;
	}
}

int isp_core_init(isp_core_t core)
{
	int ret;

	if (!core)
		return -RTS_ISP_EINVAL;
	if (core->running)
		return -RTS_ISP_EBUSY;
	if (core->initialized)
		return RTS_ISP_OK;
	ret = isp_iq_init(&core->iq);
	if (ret)
		goto err;

	core->initialized = RTS_ISP_TRUE;
	isp_info("%s ok\r\n", __func__);

	return RTS_ISP_OK;
err:
	isp_perror(ret, "core init fail");
	return ret;
}

int isp_core_cleanup(isp_core_t core)
{
	if (!core)
		return -RTS_ISP_EINVAL;
	if (core->running)
		return -RTS_ISP_EBUSY;
	if (!core->initialized)
		return RTS_ISP_OK;
	isp_iq_cleanup(&core->iq);
	core->initialized = RTS_ISP_FALSE;
	debug("isp core cleaned up ok\n");

	return RTS_ISP_OK;
}
uint32_t parse_all_mod_time = 0, iq_load_end_time = 0, parse_all_mod_data_time = 0;
int isp_core_start(isp_core_t core)
{
	int ret;
	enum rts_isp_day_night dn = (enum rts_isp_day_night)core->iq.dn;

	if (!core)
		return -RTS_ISP_EINVAL;
	if (core->running)
		return RTS_ISP_OK;

	ret = isp_iq_load_from_file(&core->iq);
	if (ret)
		goto err;
	iq_load_end_time = hal_read_curtime_us();
	ret = core_parse_all_mod(core, isp_mod_init);
	//isp_info("isp_mod_init done ret %d \r\n", ret);
	if (ret)
		goto err;
	ret = core_parse_all_mod(core, isp_mod_hardware_init);
	//isp_info("isp_mod_hardware_init done ret %d \r\n", ret);
	if (ret)
		goto err;

	ret = isp_core_notify(core, ISP_NOTIFY_HDR_MODE_CHANGE, NULL, 0);
	if (ret)
		goto err;

	//ret = isp_core_notify(core, ISP_NOTIFY_IQ_CHANGE, &dn, sizeof(dn));
	ret = isp_core_notify(core, ISP_NOTIFY_IQ_CHANGE, &dn, 4); // [Martin] argument sync, sizeof(dn) != sizeof(uint32_t)
	//isp_info("isp_core_notify done ret %d \r\n", ret);
	if (ret)
		goto err;
	parse_all_mod_time = hal_read_curtime_us();
	ret = rtsv_ctrl_handler_init(&core->ctrl_handler, 32);
	//isp_info("v4l2_ctrl_handler_init done ret %d \r\n", ret);
	if (ret)
		goto err;
	ret = core_parse_all_mod_data(core, isp_mod_add_ctrl,
				      &core->ctrl_handler);
	//isp_info("core_parse_all_mod_data done ret %d \r\n", ret);
	parse_all_mod_data_time = hal_read_curtime_us();
	if (ret)
		goto err;

	ret = rtsv_ctrl_handler_setup(&core->ctrl_handler);
	//isp_info("v4l2_ctrl_handler_setup done ret %d \r\n", ret);
	if (ret)
		goto err;
	core->running = RTS_ISP_TRUE;
	//debug("%s ok\n", __func__);

	return RTS_ISP_OK;
err:
	rtsv_ctrl_handler_free(&core->ctrl_handler);
	core_parse_all_mod(core, isp_mod_hardware_cleanup);
	core_parse_all_mod(core, isp_mod_cleanup);
	core->running = RTS_ISP_FALSE;
	return ret;
}

int isp_core_stop(isp_core_t core)
{
	if (!core)
		return -RTS_ISP_EINVAL;

	if (!core->running)
		return RTS_ISP_OK;

	rtsv_ctrl_handler_free(&core->ctrl_handler);
	core_parse_all_mod(core, isp_mod_hardware_cleanup);
	core_parse_all_mod(core, isp_mod_cleanup);
	core->running = RTS_ISP_FALSE;
	//debug("isp core stop running\n");

	return RTS_ISP_OK;
}

int isp_core_add_notify_entry(isp_core_t core, struct isp_mod *mod,
			      uint32_t notify_id)
{
	if (!core || !mod)
		return -RTS_ISP_EINVAL;

	return isp_notify_add_entry(&core->notify, mod, (enum isp_notify_ids)notify_id);
}

int isp_core_del_notify_entry(isp_core_t core, struct isp_mod *mod,
			      uint32_t notify_id)
{
	if (!core || !mod)
		return -RTS_ISP_EINVAL;

	return isp_notify_del_entry(&core->notify, mod, (enum isp_notify_ids)notify_id);
}

int isp_core_notify(isp_core_t core, uint32_t id, void *data, ssize_t len)
{
	if (!core)
		return -RTS_ISP_EINVAL;
	if (len && !data)
		return -RTS_ISP_EINVAL;
	//isp_info("%s 0x%08x 0x%08x 0x%08x %d %d \r\n", __func__, core, &core->notify, data, id, len );
	return isp_notify(&core->notify, (enum isp_notify_ids)id, data, len);
}

struct isp_statis *isp_core_get_statis(isp_core_t core)
{
	if (!core)
		return NULL;
	return &core->statis;
}

struct isp_iq *isp_core_get_iq(isp_core_t core)
{
	if (!core)
		return NULL;
	return &core->iq;
}
volatile int iq_init_dn_mode = 0;

int isp_core_set_iq_mode(isp_core_t core, int iq_dn_mode)
{
	if (!core)
		return -RTS_ISP_EINVAL;
	core->iq.dn = iq_dn_mode;
	iq_init_dn_mode = iq_dn_mode;

}


