/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rtsmem.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#include "isp_log.h"
#include "rt_tlsf.h"
#include "rtscamkit.h"
#include "rtx_mutex.h"
#include "FreeRTOSConfig.h"
#include "isp_debug.h"




#ifdef RTS_MQ_DEBUG
#include "list.h"

static LIST_HEAD(mem_list);

struct rts_mem_item {
	size_t length;
	struct list_head list;
	const char *func;
	int line;
	uint8_t ptr[0];
};
static unsigned long mem_used;
static unsigned long mem_count;
static pthread_mutex_t mem_lock = PTHREAD_MUTEX_INITIALIZER;

#endif

static size_t __get_rts_size(size_t size)
{
#ifdef RTS_MQ_DEBUG
	return size + sizeof(struct rts_mem_item);
#else
	return size;
#endif
};

static void *__get_rts_ptr(void *ptr)
{
#ifdef RTS_MQ_DEBUG
	if (ptr)
		return container_of(ptr, struct rts_mem_item, ptr);
	else
		return ptr;
#else
	return ptr;
#endif
}

static void *__get_user_ptr(void *ptr)
{
#ifdef RTS_MQ_DEBUG
	if (ptr)
		return ((struct rts_mem_item *)ptr)->ptr;
	else
		return ptr;
#else
	return ptr;
#endif
}

#ifdef RTS_MQ_DEBUG
static void __inc_mem(void *ptr, size_t size, const char *func, int line)
{
	struct rts_mem_item *item = NULL;

	pthread_mutex_lock(&mem_lock);

	item = (struct rts_mem_item *)ptr;
	item->length = size;
	item->func = func;
	item->line = line;
	list_add_tail(&item->list, &mem_list);
	mem_used += __get_rts_size(size);

	mem_count++;
	pthread_mutex_unlock(&mem_lock);
	if (item->func) {
		rts_log(RTS_LOG_MEM,
			"++++0x%08lx\t:%d \t(%ld, %ld) \t<%s, %d>\n",
			(unsigned long)__get_user_ptr(ptr), size,
			mem_count, mem_used,
			item->func, item->line);
	} else {
		rts_log(RTS_LOG_MEM, "++++0x%08lx\t:%d \t(%ld, %ld)\n",
			(unsigned long)__get_user_ptr(ptr), size,
			mem_count, mem_used);
	}
}
#else
static void __inc_mem(void *ptr, size_t size)
{
	RTS_LOG(RTS_LOG_MEM, "++++0x%08lx\t:%d\n",
		(unsigned long)__get_user_ptr(ptr), size);
}
#endif

static int __dec_mem(void *ptr)
{

#ifdef RTS_MQ_DEBUG
	int found = RTS_TRUE;
	struct rts_mem_item *item = NULL, *tmp;
	size_t size = 0;
	const char *func = NULL;
	int line = 0;

	pthread_mutex_lock(&mem_lock);
	list_for_each_entry(tmp, &mem_list, list) {
		if (ptr == (void *)tmp) {
			item = tmp;
			break;
		}
	}
	if (item) {
		list_del_init(&item->list);
		size = __get_rts_size(item->length);
		func = item->func;
		line = item->line;
		mem_used -= size;
		mem_count--;
	} else {
		found = RTS_FALSE;
	}
	pthread_mutex_unlock(&mem_lock);
	if (!found)
		return RTS_RETURN(RTS_E_NOT_FOUND);
	if (func) {
		rts_log(RTS_LOG_MEM,
			"----0x%08lx\t:%d \t(%ld, %ld) \t<%s, %d>\n",
			(unsigned long)__get_user_ptr(ptr), size,
			mem_count, mem_used,
			func, line);
	} else {
		rts_log(RTS_LOG_MEM, "----0x%08lx\t:%d \t(%ld, %ld)\n",
			(unsigned long)__get_user_ptr(ptr), size,
			mem_count, mem_used);
	}
#else
	RTS_LOG(RTS_LOG_MEM, "----0x%08lx\n",
		(unsigned long)__get_user_ptr(ptr));
#endif

	return RTS_OK;
}

void *__rts_malloc(size_t size, const char *func, int line)
{

#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif

#if 0
	void *ptr = rt_tlsf_malloc(__get_rts_size(size));
#else
	//void *ptr = rt_tlsf_malloc(__get_rts_size(size));  //malloc(__get_rts_size(size));
	void *ptr = pvPortMalloc(__get_rts_size(size));
	if (ptr == NULL) {
		isp_error("<%s> pvPortMallocExt error %d \r\n", __FUNCTION__, __get_rts_size(size));
	}
#ifdef __LOG_RTS_MEM__
	printf("%s %d 0x%08x from %s \r\n", __FUNCTION__, size, ptr, func);
#endif
	//printf("%s %d 0x%08x from %s \r\n", __FUNCTION__, size, ptr, func);
#endif

#ifdef RTS_MQ_DEBUG
	__inc_mem(ptr, size, func, line);
#else
	__inc_mem(ptr, size);
#endif

	ptr = __get_user_ptr(ptr);

#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("__rts_malloc alloc %d 0x%08x heap_used %d heap %d \n", __get_rts_size(size), ptr, heap_before-heap_after, heap_after);
#endif

	return ptr;
}


void rts_free(void *ptr)
{
#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif

	if (!ptr)
		return;
#if 0
	ptr = __get_rts_ptr(ptr);

	if (RTS_OK == __dec_mem(ptr))
	//rt_tlsf_free(ptr);
#endif
#ifdef __LOG_RTS_MEM__
	printf("%s 0x%08x\r\n", __FUNCTION__, ptr);
#endif

	vPortFree(ptr);

#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("rts_free free 0x%08x heap_free %d heap %d \n", ptr, heap_after-heap_before, heap_after);
#endif




}




void *__rts_calloc(size_t nmemb, size_t size, const char *func, int line)
{

#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif



#if 0
	void *ptr = rt_tlsf_calloc(1, __get_rts_size(nmemb * size));
#else
	//void *ptr = rt_tlsf_calloc(1, __get_rts_size(nmemb * size));  //calloc(1, __get_rts_size(nmemb * size));
	void *ptr = pvPortMalloc(nmemb * size);
	if (ptr == NULL) {
		isp_error("<%s> pvPortMallocExt error  %d \r\n", __FUNCTION__, nmemb * size);
	} else {
		memset(ptr, 0, nmemb * size);
	}
#ifdef __LOG_RTS_MEM__
	printf("%s %d : calloc %d 0x%08x\r\n", func, line, size, ptr);
#endif

#endif

#ifdef RTS_MQ_DEBUG
	//__inc_mem(ptr, nmemb * size, func, line);
#else
	//__inc_mem(ptr, nmemb * size);
#endif

	//ptr = __get_user_ptr(ptr);

#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("__rts_calloc alloc %d 0x%08x heap_used %d heap %d \n", __get_rts_size(nmemb * size), ptr, heap_before-heap_after, heap_after);
#endif




	return ptr;
}

void *__rts_realloc(void *ptr, size_t size, const char *func, int line)
{
	void *p = NULL;

#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif

#if 0
	if (ptr) {
		ptr = __get_rts_ptr(ptr);
		__dec_mem(ptr);
	}
	p = rt_tlsf_realloc(ptr, __get_rts_size(size));

	if (p) {
#ifdef RTS_MQ_DEBUG
		__inc_mem(p, size, func, line);
#else
		__inc_mem(p, size);
#endif
		p = __get_user_ptr(p);

#else




	/* Zero-size requests are treated as free. */
	if (!ptr) {
		p = pvPortMalloc(size);
		//isp_warning("<%s> ptr = 0x%08x \r\n", __func__, ptr);
	} else {
		p = pvPortReAlloc(ptr, size);
	}
	if (p == NULL) {
		isp_error("<%s> error \r\n", __FUNCTION__);
	} else {
		//memset(p, 0, size);
		//isp_info("<%s> pvPortMallocExt %d \r\n", __FUNCTION__, size);
	}
#endif

#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("__rts_realloc alloc %d 0x%08x heap_used %d heap %d \n", size, p, heap_before-heap_after, heap_after);
#endif




#ifdef __LOG_RTS_MEM__
	printf("%s %d old 0x%08x new 0x%08x\r\n", __FUNCTION__, size, ptr, p);
#endif
	return p;
}
