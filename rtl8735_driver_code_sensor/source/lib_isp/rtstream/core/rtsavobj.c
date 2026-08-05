/*
 * Realtek Semiconductor Corp.
 *
 * core/rtsavobj.c
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cmsis_os2.h"
#include <rtscamkit.h>
//#include "rtsavobj.h"

void rts_av_obj_init(struct rts_av_obj *obj,
		     void (*release)(struct rts_av_obj *))
{
	RTS_ASSERT(obj);


	obj->mutex = xSemaphoreCreateMutex();
	if ( !obj->mutex ) {
		RTS_ERR("obj->mutex alloc fail\n");
		return;
	}
	INIT_LIST_HEAD(&obj->list);
	obj->refcount = 0;
	obj->release = release;
	obj->priv = obj;
}

void rts_av_obj_release(struct rts_av_obj *obj)
{
	if (!obj)
		return;

	list_del_init(&obj->list);

	osMutexDelete(obj->mutex);
}

static void __release_obj(struct rts_av_obj *obj)
{
	if (!obj)
		return;

	if (obj->release)
		obj->release(obj);
}

int rts_av_obj_set_name(struct rts_av_obj *obj, const char *format, ...)
{
	va_list ap;

	RTS_ASSERT(obj);
	RTS_ASSERT(obj->priv == obj);

	va_start(ap, format);
	vsnprintf(obj->name, sizeof(obj->name), format, ap);
	va_end(ap);

	return RTS_OK;
}

char *rts_av_obj_get_name(struct rts_av_obj *obj)
{
	RTS_ASSERT(obj);
	RTS_ASSERT(obj->priv == obj);

	return obj->name;
}

struct rts_av_obj *rts_av_obj_get(struct rts_av_obj *obj)
{
	RTS_ASSERT(obj);
	RTS_ASSERT(obj->priv == obj);

	xSemaphoreTake(obj->mutex, portMAX_DELAY);
	obj->refcount++;
	osMutexRelease(obj->mutex);

	return obj;
}

void rts_av_obj_put(struct rts_av_obj *obj)
{
	int flag = RTS_FALSE;

	RTS_ASSERT(obj);
	RTS_ASSERT(obj->priv == obj);

	xSemaphoreTake(obj->mutex, portMAX_DELAY);
	if (obj->refcount > 0) {
		obj->refcount--;
		if (!obj->refcount)
			flag = RTS_TRUE;
	}
	osMutexRelease(obj->mutex);

	if (flag)
		__release_obj(obj);
}

int rts_av_obj_get_refs(struct rts_av_obj *obj)
{
	RTS_ASSERT(obj);
	RTS_ASSERT(obj->priv == obj);

	return obj->refcount;
}

#endif
