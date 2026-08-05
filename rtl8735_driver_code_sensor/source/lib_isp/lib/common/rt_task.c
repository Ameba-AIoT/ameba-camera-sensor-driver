#include <stdio.h>
#include <stdlib.h>
#if 0
#include "rt_task.h"
#include "rt_log.h"
#include "rt_util.h"

#include "task.h"
//#include "rt_console.h"

#include "mpool.h"

task_st g_task[CFG_TASK_MAX_NUM] = {0};
uint32_t g_task_num = 0;

// return 0 if fail
int _task_user_find_empty_slot(void)
{
	int i;

	for (i = TASK_IDX_USER_BEGIN; i < CFG_TASK_MAX_NUM; i++)
	{
		if (g_task[i].handle == NULL)
			return i;
	}
	return 0;
}

char task_state_char(eTaskState state)
{
	static char s_task_state_char[6] =
	{           // eTaskState
		('X'),  // eRunning = 0
		('R'),  // eReady,
		('B'),  // eBlocked,
		('S'),  // eSuspended,
		('D'),  // eDeleted,
		0x00,   // eInvalid
	};
	return s_task_state_char[state];
}

void    task_dump(task_st *task)
{
	if (!task)
	{
		rt_warning("task = NULL\n");
		return;
	}
	TaskStatus_t x;
	vTaskGetInfo(task->handle, &x, pdTRUE, eInvalid);
	char cStatus = task_state_char(x.eCurrentState);
	rt_printf("%-16s%u\t%c\t%u\t%u", x.pcTaskName, (UINT)x.xTaskNumber, cStatus, (UINT)x.uxCurrentPriority, (UINT)x.usStackHighWaterMark);
	rt_printf("\t%u", (UINT)task->delay);
	rt_printf("\n");
	return;
}

extern void dump_stack(TaskHandle_t curr_task);

static int _compare_task_number(const void *a, const void *b)
{
	TaskStatus_t *ts_a = (TaskStatus_t *)a;
	TaskStatus_t *ts_b = (TaskStatus_t *)b;

	int id_a = ts_a->xTaskNumber;
	int id_b = ts_b->xTaskNumber;

	if (id_a < id_b) return -1;
	if (id_a > id_b) return 1;

	return 0;
}

#ifdef MBED_HEAP_STATS_ENABLED
	extern uint32_t *mem_get_alloc_size(uint32_t task_id);
#endif

void    task_dump_all(int id)
{
#if 0
	// by FreeRTOS api.
	char    str[1024];
	vTaskList(str);
	rt_printf("%s\n", str);
	return;
#endif

	TaskStatus_t xTaskStatusArray[CFG_TASK_MAX_NUM];
	volatile UBaseType_t uxArraySize, x;
	char cStatus;

	task_st *t;
	TaskStatus_t *p;
	uint32_t uxNumberOfTasks = uxTaskGetNumberOfTasks();

	if (uxNumberOfTasks > CFG_TASK_MAX_NUM) uxNumberOfTasks = CFG_TASK_MAX_NUM;
	// Take a snapshot of the number of tasks in case it changes while this function is executing.
	uxArraySize = uxNumberOfTasks;

	// Allocate an array index for each task.
	// NOTE!  if configSUPPORT_DYNAMIC_ALLOCATION is set to 0 then pvPortMalloc() will equate to NULL.
	//pxTaskStatusArray = pvPortMalloc( uxNumberOfTasks * sizeof( TaskStatus_t ) );
	//if (!pxTaskStatusArray)
	//    return;

	// Generate the (binary) data.
	uxArraySize = uxTaskGetSystemState(xTaskStatusArray, uxArraySize, NULL);

	// Sort by xTaskNumber
	qsort(xTaskStatusArray, uxArraySize, sizeof(TaskStatus_t), _compare_task_number);

	// Create a human readable table from the binary data.
	//vTaskSuspendAll();
#ifndef MBED_HEAP_STATS_ENABLED
	rt_printf("NAME\t\tID\tST\tPRI\tSTACK\tDELAY\tStopAddr\tPAlloc#\tPFree#\tPTotal\n");
	rt_printf("------------------------------------------------------------------------------------------------\n");
#else
	rt_printf("NAME\t\tID\tST\tPRI\tSTACK\tDELAY\tStopAddr\tAlloc#\tFree#\tTotal\tPAlloc#\tPFree#\tPTotal\n");
	rt_printf("------------------------------------------------------------------------------------------------------------------------\n");
#endif
	for (x = 0; x < uxArraySize; x++)
	{
		p = &xTaskStatusArray[x];
		cStatus = task_state_char(p->eCurrentState);
		// note: configMAX_TASK_NAME_LEN = 16

		//get return address
		unsigned int *ptr = (unsigned int *)p->xHandle;
		unsigned int ulRA = 0;
		uint32_t *num;
		ptr = (unsigned int *)*ptr;
		ulRA = *((unsigned int *)((int)ptr-4));

		rt_printf("%-16s%u\t%c\t%u\t%u", p->pcTaskName, (UINT)p->xTaskNumber, cStatus,
				(UINT)p->uxCurrentPriority, (UINT)p->usStackHighWaterMark);
		if ((t = task_from_handle(p->xHandle)) != NULL)
			rt_printf("\t%lu", t->delay*1000/configTICK_RATE_HZ);
		else
			rt_printf("\t");
		rt_printf("\t%08x", ulRA);
#ifdef MBED_HEAP_STATS_ENABLED
		num = mem_get_alloc_size(p->xTaskNumber);
		if (num) {
			rt_printf("\t%u\t%u\t%d", (UINT)num[0], (UINT)num[1], (int)num[2]);
		} else {
			rt_printf("\t%u\t%u\t%d", 0, 0, 0);
		}
#endif
		num = mpool_get_alloc_size(p->xTaskNumber);
		if (num) {
			rt_printf("\t%u\t%u\t%d", (UINT)num[0], (UINT)num[1], (int)num[2]);
		} else {
			rt_printf("\t%u\t%u\t%d", 0, 0, 0);
		}
		rt_printf("\n");
		if (id) {
			rt_printf("Stop At:%08x", ulRA);
#if defined(OS_TRACE_EN)
			dump_stack(p->xHandle);
#endif
			rt_printf("\n");
		}
	}
	extern void dump_heap(void);
	dump_heap();
	//( void ) xTaskResumeAll();

	// Free the array again.
	// NOTE! If configSUPPORT_DYNAMIC_ALLOCATION is 0 then vPortFree() will be #defined to nothing.
	//vPortFree(pxTaskStatusArray);

	task_mem_stat_dump();
	return;
}

BOOL task_is_sys(int task_id)
{
	for (int i = 0; i < TASK_IDX_USER_BEGIN; i++)
	{
		if (task_id == g_task[i].id)
			return TRUE;
	}
	return FALSE;
}

BOOL task_is_shell(int task_id)
{
	task_st *task = task_from_name(CFG_TASK_SHELL_NAME);
	RT_ASSERT(task);

	for (int i = TASK_IDX_USER_BEGIN; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (task->id == task_id)
			return TRUE;
	}
	return FALSE;
}

// brief: check if user rt_task
BOOL task_is_user(int task_id)
{
	task_st *task = task_from_id(task_id);
	if (!task)
		return FALSE;

	for (int i = TASK_IDX_USER_BEGIN; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (task->id == g_task[i].id)
			return TRUE;
	}
	return FALSE;
}

task_st *task_from_id(int task_id)
{
	for (int i = 0; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (task_id == g_task[i].id)
			return &(g_task[i]);
	}
	return NULL;
}

task_st *task_from_handle(TaskHandle_t handle)
{
	for (int i = 0; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (handle == g_task[i].handle)
			return &(g_task[i]);
	}
	return NULL;
}

task_st *task_from_name(char *name)
{
	TaskStatus_t xInfo;

	for (int i = 0; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (!g_task[i].handle)
			continue;

		vTaskGetInfo(g_task[i].handle, &xInfo, pdTRUE, eInvalid);
		if (strcmp(name, xInfo.pcTaskName) == 0)
			return &(g_task[i]);
	}
	return NULL;
}

// @handle: if NULL, means current task
void task_delete(TaskHandle_t handle)
{
	task_st *t;

	if (handle == NULL) {
		handle = xTaskGetCurrentTaskHandle();
	}

	for (int i = 0; i < (int)CFG_TASK_MAX_NUM; i++)
	{
		if (handle == g_task[i].handle)
		{
			t = &(g_task[i]);
			if (t->pre_del_cb)
			{
				t->pre_del_cb(t);
			}
			g_task_num--;
			memset(t, 0, sizeof(task_st));
			vTaskDelete(handle);
			return;
		}
	}
	return;
}

// 'err' : the error code if function fail, can be NULL.
//
// return 0 if fail
TaskHandle_t
task_create_user(char *name,
				TaskFunction_t func,
				void *param,
				uint32_t stack_size,
				uint32_t priority,
				uint32_t delay,
				TaskFunction_t pre_del_cb,
				int *err)
{
	TaskStatus_t    xInfo;
	BaseType_t      xReturned;
	int     idx;
	int     code = RT_OK;
	task_st *t = NULL;

	if (priority > CFG_TASK_MAX_PRIORITY)
	{
		code = RT_E_INVALID_ARG;
		goto exit;
	}
	//
	if ((idx = _task_user_find_empty_slot()) == 0)
	{
		code = RT_E_FULL;
		goto exit;
	}
	//
	t = &(g_task[idx]);
	// clear at first, to prevent previous(maybe) garbage in memory.
	memset(t, 0, sizeof(task_st));
	t->delay        = delay;
	t->pre_del_cb   = pre_del_cb;
	//
	xReturned = xTaskCreate(func, name, stack_size, param, priority, &(t->handle));
	if (xReturned != pdPASS)
	{
		memset(t, 0, sizeof(task_st));
		//
		code = RT_E_CREATE_FAIL;
		goto exit;
	}
	dbg_printf("debug %s %d %d \n", __FUNCTION__, __LINE__, xReturned);
	vTaskGetInfo(t->handle, &xInfo, pdTRUE, eInvalid);
	t->id = xInfo.xTaskNumber;
	//
	dbg_printf("debug %s %d \n", __FUNCTION__, __LINE__);
	vTaskSuspend(t->handle);
	g_task_num++;
	//
exit:
	if (err)
	{
		*err = code;
	}
	return t->handle;
}

int task_get_current_id(void)
{
	TaskHandle_t xHandle = xTaskGetCurrentTaskHandle();
	unsigned int *ptr = (unsigned int *)xHandle;
	int task_id = ptr[16];

	if (CFG_TASK_MAX_NUM <= task_id)
	{
		rt_printf("{task} task_get_current_id: Task(%s) ID %d unknown\n", (char *)&ptr[13], task_id);
		return -1;
	}

	return task_id;
}

// note:
//  a FreeRTOS style api. for rt_task(s), xTaskNumber equals to task_st.id
TaskHandle_t xTaskGetHandleFromNumber(uint32_t xTaskNumber)
{
	TaskStatus_t xTaskStatusArray[CFG_TASK_MAX_NUM];
	volatile UBaseType_t uxArraySize, x;

	TaskStatus_t *p;
	uint32_t uxNumberOfTasks = uxTaskGetNumberOfTasks();

	if (uxNumberOfTasks > CFG_TASK_MAX_NUM)
		uxNumberOfTasks = CFG_TASK_MAX_NUM;
	// Take a snapshot of the number of tasks in case it changes while this function is executing.
	uxArraySize = uxNumberOfTasks;

	// Generate the (binary) data.
	uxArraySize = uxTaskGetSystemState(xTaskStatusArray, uxArraySize, NULL);

	for (x = 0; x < uxArraySize; x++)
	{
		p = &xTaskStatusArray[x];
		if (p->xTaskNumber == xTaskNumber)
			return p->xHandle;
	}
	return 0;
}

#if CFG_TASK_MEM_STAT_EN
#define	MEM_STAT_MAX	32

typedef struct
{
	u8		status;			// 0: empty, 1: started, 2: finished
	char	name[16];
#ifdef MBED_HEAP_STATS_ENABLED
	u32		mem_beg[3];
	u32		mem_end[3];
#endif
	u32		mpool_beg[3];
	u32		mpool_end[3];
	// parent task handle & number
	TaskHandle_t xTaskHandle;
	u32		xTaskNumber;
} mem_stat_st;

static mem_stat_st	s_mem_stat[MEM_STAT_MAX] = {0};
static int	s_mem_stat_num = 0;
// array index of next empty entry, -1 mean all already full.
static int	s_mem_stat_next = 0;

void	task_mem_stat_update_next(void)
{
	for (int i = 0; i < MEM_STAT_MAX; i++)
	{
		if (s_mem_stat[i].status == 0)
		{
			s_mem_stat_next = i;
			return;
		}
	}
	s_mem_stat_next = -1;
	return;
}

int		task_mem_stat_find(char *name)
{
	for (int i = 0; i < MEM_STAT_MAX; i++)
	{
		if (!strcmp(s_mem_stat[i].name, name))
			return i;
	}
	return -1;
}

void	task_mem_stat_begin(char *name)
{
	TaskHandle_t xHandle;
	TaskStatus_t xTaskDetails;
	mem_stat_st *p;
	uint32_t *num;

	if (s_mem_stat_next == -1)
	{
		rt_err("s_mem_stat[] array full!, name = %s\n", name);
		return;
	}
	if (task_mem_stat_find(name) >= 0)
	{
		rt_err("reject! already exist before, name = %s\n", name);
		return;
	}
	p = &s_mem_stat[s_mem_stat_next];
	//
	memset(p, 0, sizeof(mem_stat_st));
	xHandle = xTaskGetCurrentTaskHandle();
	vTaskGetInfo(xHandle, &xTaskDetails, pdTRUE, eInvalid);
	p->xTaskHandle = xHandle;
	p->xTaskNumber = xTaskDetails.xTaskNumber;
	strcpy(p->name, name);
#ifdef MBED_HEAP_STATS_ENABLED
	num = mem_get_alloc_size(p->xTaskNumber);
	if (num)
	{
		p->mem_beg[0] = num[0];
		p->mem_beg[1] = num[1];
		p->mem_beg[2] = num[2];
	}
#endif
	num = mpool_get_alloc_size(p->xTaskNumber);
	if (num)
	{
		p->mpool_beg[0] = num[0];
		p->mpool_beg[1] = num[1];
		p->mpool_beg[2] = num[2];
	}
	p->status = 1;
}

void	task_mem_stat_end(char *name)
{
	mem_stat_st *p = &s_mem_stat[s_mem_stat_num];
	uint32_t *num;

	if (s_mem_stat_next == -1)
	{
		rt_err("s_mem_stat[] array full!, name = %s\n", name);
		return;
	}
	p = &s_mem_stat[s_mem_stat_next];
	if (p->status != 1)
	{
		rt_err("invalid status = %d, name = %s\n", p->status, name);
		rt_err("maybe no matching task_mem_stat_begin()\n");
		return;
	}
#ifdef MBED_HEAP_STATS_ENABLED
	num = mem_get_alloc_size(p->xTaskNumber);
	if (num)
	{
		p->mem_end[0] = num[0];
		p->mem_end[1] = num[1];
		p->mem_end[2] = num[2];
	}
#endif
	num = mpool_get_alloc_size(p->xTaskNumber);
	if (num)
	{
		p->mpool_end[0] = num[0];
		p->mpool_end[1] = num[1];
		p->mpool_end[2] = num[2];
	}
	p->status = 2;
	task_mem_stat_update_next();
	s_mem_stat_num++;
}

BOOL	task_mem_stat_delete(char *name)
{
	mem_stat_st *p;
	int i;

	i = task_mem_stat_find(name);
	if (i == -1)
		return FALSE;
	p = &s_mem_stat[i];
	memset(p, 0, sizeof(mem_stat_st));
	s_mem_stat_next = i;
	s_mem_stat_num--;
	return TRUE;
}

void	task_mem_stat_dump(void)
{
	TaskStatus_t xTaskDetails;
	mem_stat_st *p;
	int i;

	rt_printf("\n");
	rt_printf("-- mem stat\n\n");
	if (s_mem_stat_num == 0)
		return;
	rt_printf("%-10s %-12s %-8s %-8s %-10s %-8s %-8s %-8s\n",
			"Parent", "Item", "Alloc#", "Free#", "Total", "PAlloc#", "PFree#", "PTotal");
	rt_printf("-----------------------------------------------------------------------------------\n");
	for (i = 0; i < MEM_STAT_MAX; i++)
	{
		p = &s_mem_stat[i];
		if (p->status == 2)
		{
			vTaskGetInfo(p->xTaskHandle, &xTaskDetails, pdTRUE, eInvalid);
			rt_printf("%-10s %-12s ", xTaskDetails.pcTaskName, p->name);
#ifdef MBED_HEAP_STATS_ENABLED
			rt_printf("%-8u %-8u %-10d ",
					p->mem_end[0] - p->mem_beg[0],
					p->mem_end[1] - p->mem_beg[1],
					p->mem_end[2] - p->mem_beg[2]);
#endif
			rt_printf("%-8u %-8u %-8d\n",
					p->mpool_end[0] - p->mpool_beg[0],
					p->mpool_end[1] - p->mpool_beg[1],
					p->mpool_end[2] - p->mpool_beg[2]);
		}
	}
	rt_printf("\n");
}
#else
void	task_mem_stat_begin(char *name) {};
void	task_mem_stat_end(char *name) {};
BOOL	task_mem_stat_delete(char *name) {return FALSE};
void	task_mem_stat_dump(void) {};
#endif	// CFG_TASK_MEM_STAT_EN

#endif
