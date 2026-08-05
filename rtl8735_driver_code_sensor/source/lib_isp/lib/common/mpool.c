#include "rt_log.h"
#include "rt_task.h"
#include "mpool.h"

#if 0
#define MPOOL_TRACE_USAGE	0

void mpool_sub_alloc_size(int val);
void mpool_add_alloc_size(int val);

#define PBNAME(size) pool_bfr##size
#define PBFRVAR(size, count) static char *PBNAME(size)[size * count] __attribute__((aligned(32)))
#define PDITEM(size, count)				\
	{									\
		.queue_sz = count,				\
		.item_sz = size,				\
		.pool = (void *)NULL,	\
								\
	}

#define PBADDR 0
#define PBSIZE 1
#define PBADDR_SZ(size) { (uint32_t)pool_bfr##size, size}
#define PBADDR_SZ_LAST(size)	\
	PBADDR_SZ(size),	\
	{ (uint32_t)pool_bfr##size+(uint32_t)sizeof(pool_bfr##size), -1}	\

#pragma GCC push_options
#pragma GCC optimize("O0")

// declare buffer
PBFRVAR(32,   256);
PBFRVAR(64,   128);
PBFRVAR(128,  128);
PBFRVAR(256,   16);
PBFRVAR(1024, 128);
PBFRVAR(2176, 128);
PBFRVAR(4096,  20);
PBFRVAR(6144,   4);
PBFRVAR(16384,  2);
PBFRVAR(28160,  1);
PBFRVAR(45056,  1);
#pragma GCC pop_options

// declare pool
static osPoolDef_t pool_def[] = {
		{32,   256, NULL},
		{64,   128, NULL},
		{128,  128, NULL},
		{256,   16, NULL},
		{1024, 128, NULL},
		{2176, 128, NULL},
		{4096,  20, NULL},
		{6144,   4, NULL},
		{16384,  2, NULL},
		{28160,  1, NULL},
		{45056,  1, NULL}
};

#define POOL_NUM ((int)(sizeof(pool_def)/sizeof(osPoolDef_t)))

//for memory pool malloc/free, identify memory belongs to which pool
static uint32_t pool_buffer_addr[POOL_NUM+1][2] = {
	PBADDR_SZ(32),
	PBADDR_SZ(64),
	PBADDR_SZ(128),
	PBADDR_SZ(256),
	PBADDR_SZ(1024),
	PBADDR_SZ(2176),
	PBADDR_SZ(4096),
	PBADDR_SZ(6144),
	PBADDR_SZ(16384),
	PBADDR_SZ(28160),
	PBADDR_SZ_LAST(45056),
};


static MemoryPool_t mpool[POOL_NUM];
static osPoolId pool_id[POOL_NUM] = {0};
static osSemaphoreId_t pool_sema[POOL_NUM];

#define MPOOL_TASK_NUM  64
#define ITASK_ALLOC_NUM 0
#define ITASK_FREE_NUM  1
#define ITASK_USE_BYTE  2
static uint32_t task_mpalloc_size[MPOOL_TASK_NUM][3];

/* memory pool can not be free
 * rtn: 1 success, 0 fail
 */
int mpool_create(void)
{
	int i;

	for (i = 0; i < POOL_NUM; i++)
	{
		pool_def[i].attr.cb_mem = &mpool[i];
		pool_id[i] = osPoolCreate(&pool_def[i]);
		if (!pool_id[i])
			goto fail;

		pool_sema[i] = osSemaphoreNew(pool_def[i].pool_sz, pool_def[i].pool_sz, NULL);
		if (!pool_sema[i]) {
			printf("mpool_create pool_sema[%d] fail\n", i);
			goto fail;
		}
	};
	memset(task_mpalloc_size, 0, sizeof(task_mpalloc_size));
	return 1;

fail:
	rt_printf("{mpool} create fail! i = #%d\n", i);
	return 0;

}

void *mpool_alloc(uint32_t size)
{
	int i;
	void *rtn;

	if (size <= 0)
		return NULL;

	//search pool id by item size
	for (i = 0; i < POOL_NUM; i++)
	{
		if (size <= pool_buffer_addr[i][PBSIZE])
			break;
	}
	if (i >= POOL_NUM)
	{
		rt_printf("{mpool} NO pool. task:%s, #%d, sz: %d\n", (char *)pcTaskGetName(NULL), i, (int)size);
		return NULL;
	}

	if (osOK != osSemaphoreAcquire(pool_sema[i], portMAX_DELAY))
	{
		rt_printf("{mpool} alloc sema acquire fail. task:%s, #%d, sz:%d cnt:%d\n", (char *)pcTaskGetName(NULL), i, (int)size, (int)osSemaphoreGetCount(pool_sema[i]));
		return NULL;
	}
	rtn = osPoolAlloc(pool_id[i]);
	if (!rtn)
	{
		rt_printf("{mpool} alloc fail. task:%s, #%d, sz:%d\n", (char *)pcTaskGetName(NULL), i, (int)size);
	}
	//update mem usage
	mpool_add_alloc_size(pool_buffer_addr[i][PBSIZE]);

#if MPOOL_TRACE_USAGE
	rt_printf("{mpool} alloc: 0x%08x, %6d (%d)\n", (u32)rtn, (int)pool_buffer_addr[i][PBSIZE], (int)size);
#endif
	return rtn;
}

void mpool_free(void *addr)
{
	int i;

	if (!addr)
		return;

	//search pool id by address
	for (i = 0; i < (POOL_NUM+1); i++)
	{
		if ((uint32_t)addr < pool_buffer_addr[i][PBADDR])
		{
			i--;
			break;
		}
	}
	if ((0 <= i) && (i <= POOL_NUM))
	{
		osStatus sts;
		sts = osPoolFree(pool_id[i], addr);
		if (sts)
		{
			rt_printf("{mpool} osPoolFree fail, task:%s, sts= %d\n", pcTaskGetName(NULL), (int)sts);
		} else {
			sts = osSemaphoreRelease(pool_sema[i]);
			if (sts)
			{
				rt_printf("{mpool} osPoolFree sema release fail, task:%s, sts= %d\n", pcTaskGetName(NULL), (int)sts);
			}
		}
	}
	else
	{
		rt_printf("{mpool} free fail. task:%s, addr:%08x, i= %d\n", pcTaskGetName(NULL), (unsigned int)addr, i);
	}

	//update mem usage
	mpool_sub_alloc_size(pool_buffer_addr[i][PBSIZE]);
#if MPOOL_TRACE_USAGE
	my_printf("{mpool} free : 0x%08x, %6d\n", (u32)addr, (int)pool_buffer_addr[i][PBSIZE]);
#endif
}

uint32_t *mpool_get_alloc_size(uint32_t task_id)
{
	if (MPOOL_TASK_NUM <= task_id)
	{
		rt_printf("{mpool} get_alloc_size: Task ID %d unknown\n", (int)task_id);
		return 0;
	}
	return task_mpalloc_size[task_id];
}

void mpool_add_alloc_size(int val)
{
	TaskHandle_t xHandle = xTaskGetCurrentTaskHandle();
	unsigned int *ptr = (unsigned int *)xHandle;
	int task_id = ptr[16];

	if (MPOOL_TASK_NUM <= task_id)
	{
		rt_printf("{mpool} add_alloc_size: Task(%s) ID %d unknown\n", (char *)&ptr[13], task_id);
		return;
	}

	task_mpalloc_size[task_id][ITASK_ALLOC_NUM]++;
	task_mpalloc_size[task_id][ITASK_USE_BYTE] += val;
}

void mpool_sub_alloc_size(int val)
{
	TaskHandle_t xHandle = xTaskGetCurrentTaskHandle();
	unsigned int *ptr = (unsigned int *)xHandle;
	int task_id = ptr[16];

	if (MPOOL_TASK_NUM <= task_id)
	{
		rt_printf("{mpool} sub_alloc_size: Task(%s) ID %d unknown\n", (char *)&ptr[13], task_id);
		return;
	}

	task_mpalloc_size[task_id][ITASK_FREE_NUM]++;
	task_mpalloc_size[task_id][ITASK_USE_BYTE] -= val;
}

void *RTK_Calloc(size_t size)
{
	return mpool_alloc(size);
}

void RTK_Free(void *addr)
{
	return mpool_free(addr);
}
#endif
