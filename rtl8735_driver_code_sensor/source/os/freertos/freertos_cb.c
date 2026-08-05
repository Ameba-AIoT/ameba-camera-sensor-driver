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
void vPortUsageFaultHandler( void );
void osUsageFaultHook(void)
{
    vPortUsageFaultHandler();
}
