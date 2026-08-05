/*
 * rtx_mutex.h
 *
 *  Created on: 2021¦~4¤ë21¤é
 *      Author: martinhuang
 */

#ifndef _RTX_MUTEX_H_
#define _RTX_MUTEX_H_

#include "cmsis_os2.h"


//#define ISP_SEM_TIMEOUT 3000*portTICK_RATE_MS
//#define ISP_SEM_TIMEOUT 3000*portTICK_RATE_MS*1000/configTICK_RATE_HZ
#define ISP_SEM_TIMEOUT 3000
/// Create and Initialize a Mutex object.
osMutexId_t osMutexNew (const osMutexAttr_t *attr);

osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);

osThreadState_t osThreadGetState (osThreadId_t thread_id);

osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);

/* Limits */
#define MAX_BITS_TASK_NOTIFY      31U
#define MAX_BITS_EVENT_GROUPS     24U
#define THREAD_FLAGS_INVALID_BITS (~((1UL << MAX_BITS_TASK_NOTIFY)  - 1U))
#define EVENT_FLAGS_INVALID_BITS  (~((1UL << MAX_BITS_EVENT_GROUPS) - 1U))


uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);


uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);

void osThreadExit (void);

osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);

osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);

osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);

uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);

int atomic_read_isp(int *v);

void atomic_set_isp(int *v, int i);

void atomic_inc_isp(int *v);

int atomic_inc_return_isp(int *v);

int atomic_inc_and_test_isp(int *v);

void atomic_dec_isp(int *v);

int atomic_dec_return_isp(int *v);

int atomic_dec_and_test_isp(int *v);












#endif /* _RTX_MUTEX_H_ */
