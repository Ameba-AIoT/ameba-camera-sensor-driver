#include "FreeRTOS.h"
#include "task.h"
#include "voe.h"

void vAssertCalled( uint32_t ulLine, const char *pcfile )
{
	// 
    volatile int lock_assert = 1;
    printf("line %d file: %s\n\r", (int)ulLine, pcfile);
	while(lock_assert);
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	asm(" nop");
	printf("=== stack overflow === \n\r");
	printf("Task name : %s, TCB : %x\n\r", pcTaskName, (u32)xTask);
	printf("PSP %lx PSPLIM %lx\n\r", __get_PSP(), __get_PSPLIM());
	printf("MSP %lx MSPLIM %lx\n\r", __get_MSP(), __get_MSPLIM());
	printf("====================== \n\r");
}

void vApplicationTickHook( void )
{
	asm(" nop");
}

void vApplicationMallocFailedHook( void )
{
	asm(" nop");
}

// defined in port.c
void vPortUsageFaultHandler(void);
void osUsageFaultHook(void)
{
	vPortUsageFaultHandler();
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
								   StackType_t **ppxIdleTaskStackBuffer,
								   uint32_t *pulIdleTaskStackSize)
{
	/* If the buffers to be provided to the Idle task are declared inside this
	 * function then they must be declared static - otherwise they will be allocated on
	 * the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle
	 * task's state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
									StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize)
{
	/* If the buffers to be provided to the Timer task are declared inside this
	 * function then they must be declared static - otherwise they will be allocated on
	 * the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle
	 * task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationDaemonTaskStartupHook(void)
{
#if (configENABLE_TRUSTZONE == 1)
	/* allocate secure context for timer task when trustzone is enabled */
	portALLOCATE_SECURE_CONTEXT((((size_t) configTIMER_TASK_STACK_DEPTH) * sizeof(StackType_t)));
#endif
}