#ifndef __RLX_CPU_H__
#define __RLX_CPU_H__

#if 0
//////////////////////////////////////////
//DWT function
#define RLX_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))	/* DEMCR: Debug Exception and Monitor Control Register */
#define RLX_TRCENA_BIT              (1UL<<24)							/* Trace enable bit in DEMCR register */
#define RLX_MONENA_BIT              (1UL<<16)							/* Monitor enable bit in DEMCR register */

/* TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */
#define RLX_InitWatchpoint()	RLX_DEMCR |= RLX_MONENA_BIT

#define RLX_InitCycleCounter()	RLX_DEMCR |= RLX_TRCENA_BIT

//Cycle count related
#define RLX_DWT_CYCCNTENA_BIT       (1UL<<0)							/* CYCCNTENA bit in DWT_CONTROL register */

/* Reset cycle counter */
#define RLX_ResetCycleCounter() DWT->CYCCNT = 0

/* Enable cycle counter */
#define RLX_EnableCycleCounter() DWT->CTRL |= RLX_DWT_CYCCNTENA_BIT
 
/* Disable cycle counter */
#define RLX_DisableCycleCounter() DWT->CTRL &= ~RLX_DWT_CYCCNTENA_BIT

/* Read cycle counter register */
#define RLX_GetCycleCounter() DWT->CYCCNT


//////////////////////////////////////////
#define WATCH_R 2
#define WATCH_W 1

void rlx_flush_cache(unsigned long start_addr, unsigned long size);
void rlx_flush_dcache_range(unsigned long start_addr, unsigned long stop);
void rlx_invalidate_dcache_range(unsigned long start_addr, unsigned long stop);

void rlx_set_watchpoint(int id, unsigned long start_addr, unsigned long type);

#endif

#endif	// __RLX_CPU_H__

