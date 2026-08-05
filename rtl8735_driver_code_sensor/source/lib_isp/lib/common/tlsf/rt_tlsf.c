#include "cmsis_os2.h"
#include <errno.h>
#include "rt_types.h"
#include "rt_util.h"
#include "rt_task.h"
#include "tlsf.h"
#include "rtx_mutex.h"

#define RT_TLSF_POOL_SIZE (16*1024*1024)
static tlsf_t gbl_tlsf = NULL;
static osMutexId_t gbl_tlsf_lock;

int rt_tlsf_init(void)
{
#if 0
	int size = RT_TLSF_POOL_SIZE;
	char * mem;

	if (gbl_tlsf) {
		printf("%s: tlsf pool already create\n", __func__);
		return RT_OK;
	}

	mem = malloc(size);
	if(mem == NULL) {
		printf("%s: tlsf pool create failed\n", __func__);
		return RT_E_CREATE_FAIL;
	}
	gbl_tlsf = tlsf_create_with_pool(mem, size);


	gbl_tlsf_lock = xSemaphoreCreateMutex();
	if ( !gbl_tlsf_lock ) {
		printf("%s: mutex alloc fail\n", __func__);
		return RT_E_CREATE_FAIL;
	}
#endif
	return RT_OK;
}

void *rt_tlsf_malloc(size_t size)
{
	void * p = NULL;
	
	if(!gbl_tlsf) {
		return NULL;
	}
	
	if (xSemaphoreTake(gbl_tlsf_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rt_tlsf_malloc wait gbl_tlsf_lock timeout\n\r");
		return NULL;
	}
	p = tlsf_malloc(gbl_tlsf, size);
	if (p == NULL) {
		printf("%s: out of memory\n", __func__);
	}
	xSemaphoreGive(gbl_tlsf_lock);
	
	return p;
}

void rt_tlsf_free(void* ptr)
{
	if(!gbl_tlsf) {
		return;
	}
	
	if (xSemaphoreTake(gbl_tlsf_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rt_tlsf_free wait gbl_tlsf_lock timeout\n\r");
		return;
	}
	tlsf_free(gbl_tlsf, ptr);
	xSemaphoreGive(gbl_tlsf_lock);
}

void *rt_tlsf_calloc(size_t nitems, size_t size)
{
	size_t total_size = nitems * size;
	void *ptr;
	
	ptr = rt_tlsf_malloc(total_size);
	if (ptr == NULL) {
		goto exit;
	}
	memset(ptr, 0, total_size);
	
exit:
	return ptr;
}

void* rt_tlsf_realloc(void *ptr, size_t size)
{
	void *p = NULL;
	
	if(!gbl_tlsf) {
		return NULL;
	}
	
	if (xSemaphoreTake(gbl_tlsf_lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rt_tlsf_realloc wait gbl_tlsf_lock timeout\n\r");
		return NULL;
	}
	p = tlsf_realloc(gbl_tlsf, ptr, size);
	xSemaphoreGive(gbl_tlsf_lock);
	
	return p;
}
