/*
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------------
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       Mutex functions
 *
 * -----------------------------------------------------------------------------
 */
#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif


#include "cmsis_os2.h"
#include "isp_log.h"
#include "isp_debug.h"

//#define __OS_LOG__

static int inHandlerMode (void)
{
    return __get_IPSR() != 0;
}




/// Create and Initialize a Mutex object.
osMutexId_t osMutexNew (const osMutexAttr_t *attr) {

	osMutexId_t mutexnew;
	mutexnew = xSemaphoreCreateMutex();
#ifdef __OS_LOG__
	isp_info("func %s: %s ID 0x%08x \r\n",__func__, attr->name, mutexnew);
#endif
	return mutexnew;
}

#if 0
/// Acquire a Mutex or timeout if it is locked.
/// \note API identical to osMutexAcquire
osStatus_t svcRtxMutexAcquire (osMutexId_t mutex_id, uint32_t timeout) {

	  return 0;
}
#endif
osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id) {
  return osOK;
}
#if 0
void rlx_flush_dcache_range(unsigned long start_addr, unsigned long stop)
{
	return;
}
#endif

osThreadState_t osThreadGetState (osThreadId_t thread_id) {
  return osThreadRunning;
}

osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout) {

	osStatus_t result;
#ifdef __OS_LOG__
	isp_info(" %s mutex_id 0x%08x timeout %d \r\n", __func__, mutex_id, timeout);
#endif
	result = osMutexWait(mutex_id,  timeout*1000/configTICK_RATE_HZ);
	if (result != osOK ) {
		isp_error(" %s 0x%08x result 0x%08x \r\n", __func__, (unsigned int)mutex_id, result);
	}
	return result;
}

/* Limits */
#define MAX_BITS_TASK_NOTIFY      31U
#define MAX_BITS_EVENT_GROUPS     24U
#define THREAD_FLAGS_INVALID_BITS (~((1UL << MAX_BITS_TASK_NOTIFY)  - 1U))
#define EVENT_FLAGS_INVALID_BITS  (~((1UL << MAX_BITS_EVENT_GROUPS) - 1U))


uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout) {

	EventGroupHandle_t hEventGroup = (EventGroupHandle_t)ef_id;
	BaseType_t wait_all;
	BaseType_t exit_clr;
	uint32_t rflags;

	if ((hEventGroup == NULL) || ((flags & EVENT_FLAGS_INVALID_BITS) != 0U)) {
	rflags = (uint32_t)osErrorParameter;
	}
	else if (inHandlerMode()) {
	rflags = (uint32_t)osErrorISR;
	}
	else {
	if (options & osFlagsWaitAll) {
	  wait_all = pdTRUE;
	} else {
	  wait_all = pdFAIL;
	}

	if (options & osFlagsNoClear) {
	  exit_clr = pdFAIL;
	} else {
	  exit_clr = pdTRUE;
	}

	rflags = xEventGroupWaitBits (hEventGroup, (EventBits_t)flags, exit_clr, wait_all, (TickType_t)timeout);

	if (options & osFlagsWaitAll) {
	  if (flags != rflags) {
		if (timeout > 0U) {
		  rflags = (uint32_t)osErrorTimeout;
		} else {
		  rflags = (uint32_t)osErrorResource;
		}
	  }
	}
	else {
	  if ((flags & rflags) == 0U) {
		if (timeout > 0U) {
		  rflags = (uint32_t)osErrorTimeout;
		} else {
		  rflags = (uint32_t)osErrorResource;
		}
	  }
	}
	}

	return (rflags);
}

uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags) {
	return 0;
}

void osThreadExit (void){
	return;
}
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout) {

	int32_t ret;
#ifdef __OS_LOG__
	isp_info(" id 0x%08x timeout %d \r\n", semaphore_id, timeout);
#endif
	//printf(" id 0x%08x timeout %d \r\n", semaphore_id, timeout);
	//ret = osSemaphoreWait(semaphore_id, timeout*1000/configTICK_RATE_HZ);
	if ( timeout == osWaitForever ) {
		ret = osSemaphoreWait(semaphore_id, timeout);
	} else {
		ret = osSemaphoreWait(semaphore_id, timeout*1000/configTICK_RATE_HZ);
	}

	//if (ret) {
	//	printf("%s 0x%08x error %d\r\n", __func__, semaphore_id, ret);
	//}
	return (osStatus_t)ret;

}
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr) {

	EventGroupHandle_t hEventGroup = NULL;

	hEventGroup = xEventGroupCreate();

	return ((osEventFlagsId_t)hEventGroup);
}

osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr) {

	osSemaphoreId_t SemaNew;
	//osSemaphoreDef_t semaphore_def;
	//semaphore_def.dummy = 0;

	SemaNew = xSemaphoreCreateCounting(max_count, initial_count);
#ifdef __OS_LOG__
	isp_info("%s count %d id 0x%08x %s \r\n", __FUNCTION__, max_count, SemaNew, attr->name);
#endif

#ifdef __SEMA_LOG__
	printf("%s count %d id 0x%08x %s \r\n", __FUNCTION__, max_count, SemaNew, attr->name);
#endif
	return SemaNew;

}

uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id)
{
  SemaphoreHandle_t hSemaphore = (SemaphoreHandle_t)semaphore_id;
  uint32_t count;

  if (hSemaphore == NULL) {
    count = 0U;
  }
  else if (inHandlerMode()) {
    count = uxQueueMessagesWaitingFromISR (hSemaphore);
  } else {
    count = (uint32_t)uxSemaphoreGetCount (hSemaphore);
  }

  return (count);
}


#if 0
osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr) {
	return 0;
}
#endif

int atomic_read_isp(int *v)
{
	int ret;
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	ret = *v;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();

	return ret;
}

void atomic_set_isp(int *v, int i)
{
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = i;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

void atomic_inc_isp(int *v)
{
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v + 1;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

int atomic_inc_return_isp(int *v)
{
	int ret;
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v + 1;
	ret = *v;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
	return ret;
}

int atomic_inc_and_test_isp(int *v)
{
	int ret;
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v + 1;
	ret = (*v == 0) ? TRUE : FALSE;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
	return ret;
}

void atomic_dec_isp(int *v)
{
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v - 1;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

int atomic_dec_return_isp(int *v)
{
	int ret;
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v - 1;
	ret = *v;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
	return ret;
}

int atomic_dec_and_test_isp(int *v)
{
	int ret;
	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	*v = *v - 1;
	ret = (*v == 0) ? TRUE : FALSE;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
	return ret;
}







#if 0
//#include "rtx_lib.h"


//  ==== Library functions ====

/// Release Mutex list when owner Thread terminates.
/// \param[in]  mutex           mutex object.
/// \return 1 - success, 0 - failure.
void osRtxMutexOwnerRelease (os_mutex_t *mutex_list) {
  os_mutex_t  *mutex;
  os_thread_t *thread;

  mutex = mutex_list;
  while (mutex) {
    mutex_list = mutex->owner_next;
    // Check if Mutex is Robust
    if (mutex->attr & osMutexRobust) {
      // Clear Lock counter
      mutex->lock = 0U;
      EvrRtxMutexReleased(mutex, 0U);
      // Check if Thread is waiting for a Mutex
      if (mutex->thread_list != NULL) {
        // Wakeup waiting Thread with highest Priority
        thread = osRtxThreadListGet((os_object_t*)mutex);
        osRtxThreadWaitExit(thread, (uint32_t)osOK, false);
        // Thread is the new Mutex owner
        mutex->owner_thread = thread;
        mutex->owner_next   = thread->mutex_list;
        mutex->owner_prev   = NULL;
        thread->mutex_list  = mutex;
        mutex->lock = 1U;
        EvrRtxMutexAcquired(mutex, 1U);
      }
    }
    mutex = mutex_list;
  }
}


//  ==== Service Calls ====

//  Service Calls definitions
SVC0_1M(MutexNew,      osMutexId_t,  const osMutexAttr_t *)
SVC0_1 (MutexGetName,  const char *, osMutexId_t)
SVC0_2 (MutexAcquire,  osStatus_t,   osMutexId_t, uint32_t)
SVC0_1 (MutexRelease,  osStatus_t,   osMutexId_t)
SVC0_1 (MutexGetOwner, osThreadId_t, osMutexId_t)
SVC0_1 (MutexDelete,   osStatus_t,   osMutexId_t)

/// Create and Initialize a Mutex object.
/// \note API identical to osMutexNew
osMutexId_t svcRtxMutexNew (const osMutexAttr_t *attr) {
  os_mutex_t *mutex;
  uint32_t    attr_bits;
  uint8_t     flags;
  const char *name;

  // Process attributes
  if (attr != NULL) {
    name      = attr->name;
    attr_bits = attr->attr_bits;
    mutex     = attr->cb_mem;
    if (mutex != NULL) {
      if (((uint32_t)mutex & 3U) || (attr->cb_size < sizeof(os_mutex_t))) {
        EvrRtxMutexError(NULL, osRtxErrorInvalidControlBlock);
        return NULL;
      }
    } else {
      if (attr->cb_size != 0U) {
        EvrRtxMutexError(NULL, osRtxErrorInvalidControlBlock);
        return NULL;
      }
    }
  } else {
    name      = NULL;
    attr_bits = 0U;
    mutex     = NULL;
  }

  // Allocate object memory if not provided
  if (mutex == NULL) {
    if (osRtxInfo.mpi.mutex != NULL) {
      mutex = osRtxMemoryPoolAlloc(osRtxInfo.mpi.mutex);
    } else {
      mutex = osRtxMemoryAlloc(osRtxInfo.mem.common, sizeof(os_mutex_t), 1U);
    }
    if (mutex == NULL) {
      EvrRtxMutexError(NULL, osErrorNoMemory);
      return NULL;
    }
    flags = osRtxFlagSystemObject;
  } else {
    flags = 0U;
  }

  // Initialize control block
  mutex->id           = osRtxIdMutex;
  mutex->state        = osRtxObjectActive;
  mutex->flags        = flags;
  mutex->attr         = (uint8_t)attr_bits;
  mutex->name         = name;
  mutex->thread_list  = NULL;
  mutex->owner_thread = NULL;
  mutex->owner_prev   = NULL;
  mutex->owner_next   = NULL;
  mutex->lock         = 0U;

  EvrRtxMutexCreated(mutex);

  return mutex;
}

/// Get name of a Mutex object.
/// \note API identical to osMutexGetName
const char *svcRtxMutexGetName (osMutexId_t mutex_id) {
  os_mutex_t *mutex = (os_mutex_t *)mutex_id;

  // Check parameters
  if ((mutex == NULL) || (mutex->id != osRtxIdMutex)) {
    EvrRtxMutexGetName(mutex, NULL);
    return NULL;
  }

  // Check object state
  if (mutex->state == osRtxObjectInactive) {
    EvrRtxMutexGetName(mutex, NULL);
    return NULL;
  }

  EvrRtxMutexGetName(mutex, mutex->name);

  return mutex->name;
}

/// Acquire a Mutex or timeout if it is locked.
/// \note API identical to osMutexAcquire
osStatus_t svcRtxMutexAcquire (osMutexId_t mutex_id, uint32_t timeout) {
  os_mutex_t  *mutex = (os_mutex_t *)mutex_id;
  os_thread_t *running_thread;

  running_thread = osRtxThreadGetRunning();
  if (running_thread == NULL) {
    EvrRtxMutexError(mutex, osRtxErrorKernelNotRunning);
    return osError;
  }

  // Check parameters
  if ((mutex == NULL) || (mutex->id != osRtxIdMutex)) {
    EvrRtxMutexError(mutex, osErrorParameter);
    return osErrorParameter;
  }

  // Check object state
  if (mutex->state == osRtxObjectInactive) {
    EvrRtxMutexError(mutex, osErrorResource);
    return osErrorResource;
  }

  // Check if Mutex is not locked
  if (mutex->lock == 0U) {
    // Acquire Mutex
    mutex->owner_thread = running_thread;
    mutex->owner_next   = running_thread->mutex_list;
    mutex->owner_prev   = NULL;
    if (running_thread->mutex_list != NULL) {
        running_thread->mutex_list->owner_prev = mutex;
    }
    running_thread->mutex_list = mutex;
    mutex->lock = 1U;
    EvrRtxMutexAcquired(mutex, mutex->lock);
    return osOK;
  }

  // Check if Mutex is recursive and running Thread is the owner
  if ((mutex->attr & osMutexRecursive) && (mutex->owner_thread == running_thread)) {
    // Increment lock counter
    if (mutex->lock == osRtxMutexLockLimit) {
      EvrRtxMutexError(mutex, osRtxErrorMutexLockLimit);
      return osErrorResource;
    }
    mutex->lock++;
    EvrRtxMutexAcquired(mutex, mutex->lock);
    return osOK;
  }

  // Check if timeout is specified
  if (timeout != 0U) {
    // Check if Priority inheritance protocol is enabled
    if (mutex->attr & osMutexPrioInherit) {
      // Raise priority of owner Thread if lower than priority of running Thread
      if (mutex->owner_thread->priority < running_thread->priority) {
        mutex->owner_thread->priority = running_thread->priority;
        osRtxThreadListSort(mutex->owner_thread);
      }
    }
    EvrRtxMutexAcquirePending(mutex, timeout);
    // Suspend current Thread
    osRtxThreadListPut((os_object_t*)mutex, running_thread);
    osRtxThreadWaitEnter(osRtxThreadWaitingMutex, timeout);
    return osErrorTimeout;
  }

  // Mutex was not acquired
  EvrRtxMutexNotAcquired(mutex);

  return osErrorResource;
}

/// Release a Mutex that was acquired by osMutexAcquire.
/// \note API identical to osMutexRelease
osStatus_t svcRtxMutexRelease (osMutexId_t mutex_id) {
  os_mutex_t  *mutex = (os_mutex_t *)mutex_id;
  os_mutex_t  *mutex0;
  os_thread_t *thread;
  os_thread_t *running_thread;
  int8_t       priority;

  running_thread = osRtxThreadGetRunning();
  if (running_thread == NULL) {
    EvrRtxMutexError(mutex, osRtxErrorKernelNotRunning);
    return osError;
  }

  // Check parameters
  if ((mutex == NULL) || (mutex->id != osRtxIdMutex)) {
    EvrRtxMutexError(mutex, osErrorParameter);
    return osErrorParameter;
  }

  // Check object state
  if (mutex->state == osRtxObjectInactive) {
    EvrRtxMutexError(mutex, osErrorResource);
    return osErrorResource;
  }

  // Check if running Thread is not the owner
  if (mutex->owner_thread != running_thread) {
    EvrRtxMutexError(mutex, osRtxErrorMutexNotOwned);
    return osErrorResource;
  }

  // Check if Mutex is not locked
  if (mutex->lock == 0U) {
    EvrRtxMutexError(mutex, osRtxErrorMutexNotLocked);
    return osErrorResource;
  }

  // Decrement Lock counter
  mutex->lock--;
  EvrRtxMutexReleased(mutex, mutex->lock);

  // Check Lock counter
  if (mutex->lock != 0U) {
    return osOK;
  }

  // Remove Mutex from Thread owner list
  if (mutex->owner_next != NULL) {
    mutex->owner_next->owner_prev = mutex->owner_prev;
  }
  if (mutex->owner_prev != NULL) {
    mutex->owner_prev->owner_next = mutex->owner_next;
  } else {
    running_thread->mutex_list = mutex->owner_next;
  }

  // Restore running Thread priority
  if (mutex->attr & osMutexPrioInherit) {
    priority = running_thread->priority_base;
    mutex0   = running_thread->mutex_list;
    while (mutex0) {
      // Mutexes owned by running Thread
      if ((mutex0->thread_list != NULL) && (mutex0->thread_list->priority > priority)) {
        // Higher priority Thread is waiting for Mutex
        priority = mutex0->thread_list->priority;
      }
      mutex0 = mutex0->owner_next;
    }
    running_thread->priority = priority;
  }

  // Check if Thread is waiting for a Mutex
  if (mutex->thread_list != NULL) {
    // Wakeup waiting Thread with highest Priority
    thread = osRtxThreadListGet((os_object_t*)mutex);
    osRtxThreadWaitExit(thread, (uint32_t)osOK, false);
    // Thread is the new Mutex owner
    mutex->owner_thread = thread;
    mutex->owner_next   = thread->mutex_list;
    mutex->owner_prev   = NULL;
    thread->mutex_list  = mutex;
    mutex->lock = 1U;
    EvrRtxMutexAcquired(mutex, 1U);
  }

  osRtxThreadDispatch(NULL);

  return osOK;
}

/// Get Thread which owns a Mutex object.
/// \note API identical to osMutexGetOwner
osThreadId_t svcRtxMutexGetOwner (osMutexId_t mutex_id) {
  os_mutex_t *mutex = (os_mutex_t *)mutex_id;

  // Check parameters
  if ((mutex == NULL) || (mutex->id != osRtxIdMutex)) {
    EvrRtxMutexGetOwner(mutex, NULL);
    return NULL;
  }

  // Check object state
  if (mutex->state == osRtxObjectInactive) {
    EvrRtxMutexGetOwner(mutex, NULL);
    return NULL;
  }

  // Check if Mutex is not locked
  if (mutex->lock == 0U) {
    EvrRtxMutexGetOwner(mutex, NULL);
    return NULL;
  }

  EvrRtxMutexGetOwner(mutex, mutex->owner_thread);

  return mutex->owner_thread;
}

/// Delete a Mutex object.
/// \note API identical to osMutexDelete
osStatus_t svcRtxMutexDelete (osMutexId_t mutex_id) {
  os_mutex_t  *mutex = (os_mutex_t *)mutex_id;
  os_mutex_t  *mutex0;
  os_thread_t *thread;
  int8_t       priority;

  // Check parameters
  if ((mutex == NULL) || (mutex->id != osRtxIdMutex)) {
    EvrRtxMutexError(mutex, osErrorParameter);
    return osErrorParameter;
  }

  // Check object state
  if (mutex->state == osRtxObjectInactive) {
    EvrRtxMutexError(mutex, osErrorResource);
    return osErrorResource;
  }

  // Mark object as inactive
  mutex->state = osRtxObjectInactive;

  // Check if Mutex is locked
  if (mutex->lock != 0U) {

    thread = mutex->owner_thread;

    // Remove Mutex from Thread owner list
    if (mutex->owner_next != NULL) {
      mutex->owner_next->owner_prev = mutex->owner_prev;
    }
    if (mutex->owner_prev != NULL) {
      mutex->owner_prev->owner_next = mutex->owner_next;
    } else {
      thread->mutex_list = mutex->owner_next;
    }

    // Restore owner Thread priority
    if (mutex->attr & osMutexPrioInherit) {
      priority = thread->priority_base;
      mutex0   = thread->mutex_list;
      while (mutex0) {
        // Mutexes owned by running Thread
        if ((mutex0->thread_list != NULL) && (mutex0->thread_list->priority > priority)) {
          // Higher priority Thread is waiting for Mutex
          priority = mutex0->thread_list->priority;
        }
        mutex0 = mutex0->owner_next;
      }
      if (thread->priority != priority) {
        thread->priority = priority;
        osRtxThreadListSort(thread);
      }
    }

    // Unblock waiting threads
    if (mutex->thread_list != NULL) {
      do {
        thread = osRtxThreadListGet((os_object_t*)mutex);
        osRtxThreadWaitExit(thread, (uint32_t)osErrorResource, false);
      } while (mutex->thread_list != NULL);
    }

    osRtxThreadDispatch(NULL);
  }

  // Free object memory
  if (mutex->flags & osRtxFlagSystemObject) {
    if (osRtxInfo.mpi.mutex != NULL) {
      osRtxMemoryPoolFree(osRtxInfo.mpi.mutex, mutex);
    } else {
      osRtxMemoryFree(osRtxInfo.mem.common, mutex);
    }
  }

  EvrRtxMutexDestroyed(mutex);

  return osOK;
}


//  ==== Public API ====

/// Create and Initialize a Mutex object.
osMutexId_t osMutexNew (const osMutexAttr_t *attr) {
  EvrRtxMutexNew(attr);
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexError(NULL, osErrorISR);
    return NULL;
  }
  return __svcMutexNew(attr);
}

/// Get name of a Mutex object.
const char *osMutexGetName (osMutexId_t mutex_id) {
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexGetName(mutex_id, NULL);
    return NULL;
  }
  return __svcMutexGetName(mutex_id);
}

/// Acquire a Mutex or timeout if it is locked.
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout) {
  EvrRtxMutexAcquire(mutex_id, timeout);
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexError(mutex_id, osErrorISR);
    return osErrorISR;
  }
  return __svcMutexAcquire(mutex_id, timeout);
}

/// Release a Mutex that was acquired by \ref osMutexAcquire.
osStatus_t osMutexRelease (osMutexId_t mutex_id) {
  EvrRtxMutexRelease(mutex_id);
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexError(mutex_id, osErrorISR);
    return osErrorISR;
  }
  return __svcMutexRelease(mutex_id);
}

/// Get Thread which owns a Mutex object.
osThreadId_t osMutexGetOwner (osMutexId_t mutex_id) {
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexGetOwner(mutex_id, NULL);
    return NULL;
  }
  return __svcMutexGetOwner(mutex_id);
}

/// Delete a Mutex object.
osStatus_t osMutexDelete (osMutexId_t mutex_id) {
  EvrRtxMutexDelete(mutex_id);
  if (IS_IRQ_MODE() || IS_IRQ_MASKED()) {
    EvrRtxMutexError(mutex_id, osErrorISR);
    return osErrorISR;
  }
  return __svcMutexDelete(mutex_id);
}
#endif
