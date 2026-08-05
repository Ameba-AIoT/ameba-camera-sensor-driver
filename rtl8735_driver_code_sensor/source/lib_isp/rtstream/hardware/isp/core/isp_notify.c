/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp_errno.h>
#include <isp_list.h>
#include <isp_mem.h>
#include <isp_log.h>
#include <isp_notify.h>
#include <isp_debug.h>

//#define __DEBUG_NOTIFY__
#define ISP_DEBUG_TYPE ISP_DEBUG_NOTIFY

struct isp_notify_entry {
	struct isp_mod *mod;
	isp_mod_action action;
	struct avl_node avl;
};

static int notify_entry_cmp(const void *k1, const void *k2, void *ptr)
{
	return *(const int *)k1 - *(const int *)k2;
}

static int notify_add_entry(struct isp_notify *notify, struct isp_mod *mod,
			    enum isp_notify_num num)
{
	int i;
	isp_mod_action action = NULL;
	struct isp_notify_entry *notify_entry;

	if (mod->real_notify_bits & (1 << num))
		return RTS_ISP_OK;

	for (i = 0; i < (int)mod->notify_actions_num; i++)
		if (ISP_AID_NR(mod->notify_actions[i].id) == num)
			action = mod->notify_actions[i].action;
	if (!action)
		return -RTS_ISP_EINVAL;
	if (!isp_calloc_item(notify_entry))
		return -RTS_ISP_ENOMEM;

	notify_entry->mod = mod;
	notify_entry->action = action;
	notify_entry->avl.key = &mod->id;
	avl_insert(&notify->mods[num], &notify_entry->avl);
	mod->real_notify_bits |= (1 << num);
#ifdef __DEBUG_NOTIFY__
	//isp_info("mod %s add notfiy %d\r\n", mod->name, num);
#endif

	return RTS_ISP_OK;
}

static int notify_del_entry(struct isp_notify *notify, struct isp_mod *mod,
			    enum isp_notify_num num)
{
	struct isp_notify_entry *notify_entry;

	if (!(mod->real_notify_bits & (1 << num)))
		return RTS_ISP_OK;

	notify_entry = avl_find_element(&notify->mods[num],
					&mod->id, notify_entry, avl);
	isp_assert(notify_entry);
	avl_delete(&notify->mods[num], &notify_entry->avl);
	isp_free(notify_entry);
	mod->real_notify_bits &= ~(1 << num);
#ifdef __DEBUG_NOTIFY__
	//isp_info("mod %s del notfiy %d\r\n", mod->name, num);
#endif

	return RTS_ISP_OK;
}

int isp_notify_init(struct isp_notify *notify)
{
	int i;

	if (!notify)
		return -RTS_ISP_EINVAL;

	notify->notify_num = _ISP_NOTIFY_NUM;
	if (!isp_calloc_array(notify->mods, notify->notify_num))
		return -RTS_ISP_ENOMEM;
	for (i = 0; i < notify->notify_num; i++)
		avl_init(&notify->mods[i], notify_entry_cmp,
			 RTS_ISP_FALSE, NULL);
	return RTS_ISP_OK;
}

int isp_notify_cleanup(struct isp_notify *notify)
{
	int i;

	if (!notify)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < notify->notify_num; i++)
		isp_assert(avl_is_empty(&notify->mods[i]));
	isp_free(notify->mods);
	notify->notify_num = 0;
	return RTS_ISP_OK;
}

int isp_notify_add_mod(struct isp_notify *notify, struct isp_mod *mod)
{
	int i;
	int ret;

	if (!notify || !mod)
		return -RTS_ISP_EINVAL;
	if (!mod->notify_bits)
		return RTS_ISP_OK;
	for (i = 0; i < notify->notify_num; i++)
		if (avl_find(&notify->mods[i], &mod->id))
			return -RTS_ISP_EEXIST;
	for (i = 0; i < notify->notify_num; i++) {
		if (mod->notify_bits & (1 << i)) {
			ret = notify_add_entry(notify, mod, (enum isp_notify_num)i);
			if (ret)
				goto err;
		}
	}
	return RTS_ISP_OK;
err:
	isp_notify_del_mod(notify, mod);
	return ret;
}

int isp_notify_del_mod(struct isp_notify *notify, struct isp_mod *mod)
{
	int i;

	if (!notify || !mod)
		return -RTS_ISP_EINVAL;
	if (!mod->real_notify_bits)
		return RTS_ISP_OK;
	for (i = 0; i < notify->notify_num; i++)
		if (mod->real_notify_bits & (1 << i))
			notify_del_entry(notify, mod, (enum isp_notify_num)i);
	return RTS_ISP_OK;
}

int isp_notify_add_entry(struct isp_notify *notify, struct isp_mod *mod,
			 enum isp_notify_ids id)
{
	enum isp_notify_num num = (enum isp_notify_num)ISP_AID_NR(id);
	char type = ISP_AID_TYPE(id);

	if (!notify || !mod ||
	    num >= _ISP_NOTIFY_NUM || type != NOTIFY_TYPE)
		return -RTS_ISP_EINVAL;

	if (mod->real_notify_bits & (1 << num))
		return RTS_ISP_OK;

	return notify_add_entry(notify, mod, num);
}

int isp_notify_del_entry(struct isp_notify *notify, struct isp_mod *mod,
			 enum isp_notify_ids id)
{
	enum isp_notify_num num = (enum isp_notify_num)ISP_AID_NR(id);
	char type = ISP_AID_TYPE(id);

	if (!notify || !mod ||
	    num >= _ISP_NOTIFY_NUM || type != NOTIFY_TYPE)
		return -RTS_ISP_EINVAL;

	if (!(mod->real_notify_bits & (1 << num)))
		return RTS_ISP_OK;

	return notify_del_entry(notify, mod, num);
}

int isp_notify(struct isp_notify *notify, enum isp_notify_ids id,
	       void *data, ssize_t len)
{
	int ret;
	enum isp_notify_num num = (enum isp_notify_num)ISP_AID_NR(id);
	struct isp_notify_entry *notify_entry;
	struct isp_notify_entry *next;

#ifdef __DEBUG_NOTIFY__
	int start_t, end_t;
#endif
	if (!notify)
		return -RTS_ISP_EINVAL;
	if (ISP_AID_TYPE(id) != NOTIFY_TYPE || ISP_AID_SIZE(id) != (unsigned int)len)
		return -RTS_ISP_EINVAL;
	if (len && !data)
		return -RTS_ISP_EINVAL;
	//isp_info("%s 0x%08x 0x%08x\r\n", __func__, &notify->mods[num],  &next);
#ifdef __DEBUG_NOTIFY__
	if (id ==  0x80f44e00 ) {
		start_t = hal_read_curtime_us();
	}
#endif
	avl_for_each_element_safe(&notify->mods[num], notify_entry, avl, next)
	{
#ifdef __DEBUG_NOTIFY__
		//start_t = hal_read_curtime_us();
#endif	
		//isp_info("%s %s 0x%08x 0x%08x \r\n", __func__, notify_entry->mod->name, notify_entry, notify_entry->action);
		ret = notify_entry->action(notify_entry->mod, data);
#ifdef __DEBUG_NOTIFY__
		//printf("%s %s 0x%08x %d \r\n", __func__, notify_entry->mod->name, notify_entry->action, num);
		//end_t = hal_read_curtime_us();
		//printf("%s 0x%08x %d time %d \r\n", notify_entry->mod->name, id, num, end_t-start_t);
#endif
		if (ret) {
			isp_perror(ret, "mod %s notify %d pro fail", notify_entry->mod->name, num);
			return ret;
		}

	}
#ifdef __DEBUG_NOTIFY__
	if (id ==  0x80f44e00 ) {
		end_t = hal_read_curtime_us();
		printf("%s time %d \r\n", __func__, end_t-start_t);
	}
#endif
	return RTS_ISP_OK;
}
