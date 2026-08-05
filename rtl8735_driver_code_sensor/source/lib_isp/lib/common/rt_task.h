// ------------------------------------------------------------------
// rt_task (a simple FreeRTOS task wrapper)
// will provide these ability in additional to FreeRTOS api:
//  (1) pre-delete callback function
//  (2) volunteer delay of user rt_task
//
// ------------------------------------------------------------------
#ifndef __RT_TASK_H__
#define __RT_TASK_H__
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"

#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_IDX_MAIN       0
#define TASK_IDX_IDLE       1
#define TASK_IDX_USER_BEGIN 2
//NOTE: SHELL task is also user task, but special. MUST created in the begining.
#define TASK_IDX_SHELL      TASK_IDX_USER_BEGIN

// brief: rt_task create info
//
// @delay: volunteer delay time (in ticks) of rt_user task.
//
// @pre_del_cb: pre-delete callback function.
//              if not NULL, will be call before doing real task delete.
// prototype: void (*pre_delete_fn)(void *self);	// 'self' is the task itself.
//
typedef struct
{
	char			*name;
	uint32_t		priority;
	uint32_t		delay;			// in ticks
	TaskFunction_t	func;
	void			*param;			// task function parameter
	uint32_t		stack_size;
	TaskFunction_t	pre_del_cb;
} task_info_st;

typedef struct
{
	uint32_t		delay;			// in ticks
	TaskFunction_t	pre_del_cb;
	// -------- NOT belong to creation info -------
	int				id;
	TaskHandle_t	handle;
} task_st;

// @handle: if NULL, means current task
void task_delete(TaskHandle_t handle);

void task_dump_all(int id);
void task_dump(task_st *task);

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
				int *err);

#define task_create_user_by_struct(t, e) \
	task_create_user((t)->name, (t)->func, (t)->param, (t)->stack_size, (t)->priority, (t)->delay, (t)->pre_del_cb, (e))

// note:
//  all below functions return TRUE only when
//  satisfy both (1) sys/shell/user (2) rt_task
//
BOOL task_is_sys(int task_id);
BOOL task_is_shell(int task_id);
BOOL task_is_user(int task_id);

task_st *task_from_id(int task_id);
task_st *task_from_handle(TaskHandle_t handle);
task_st *task_from_name(char *name);

int task_get_current_id(void);

// note:
//  a FreeRTOS style api. for rt_task(s), xTaskNumber equals to task_st.id
TaskHandle_t xTaskGetHandleFromNumber(uint32_t xTaskNumber);

// brief: calc task memory usage statistics between begin() and end()
//	- begin() must in pair with end() or delete()
//	- NOT allow nesting call
//
void	task_mem_stat_begin(char *name);
void	task_mem_stat_end(char *name);
BOOL	task_mem_stat_delete(char *name);
void	task_mem_stat_dump(void);

#ifdef __cplusplus
}
#endif

#endif	// __RT_TASK_H__

