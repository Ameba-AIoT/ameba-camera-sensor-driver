/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, <wd@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#if 0

#include "cmsis_voe.h"
#include "rlx_cpu.h"
//#include "rtl8735b_symbns4s.h"
//#include "otp_boot_cfg.h"
//#include "rtl8735b_wdt.h"

extern stdio_port_t _stdio_port;

extern void stdio_uart_port_init(void);
extern void parse_cfsr(uint32_t cfsr);
extern void stack_trace_back(uint32_t msp, uint32_t psp, uint32_t fault_lr, uint32_t trace_ns);
/**
 *  @brief The default hard fault interrupt handler.
 *         It will print out the stack contents and the fault status registers.
 *
 *  @returns    void
 */
void rlx_hard_fault_handler_c(uint32_t mstack[], uint32_t pstack[], uint32_t lr_value, uint32_t fault_id)
{
#if 1
	uint32_t ret, i, src, *stack;
	uint32_t xpsr = __get_xPSR();
	uint32_t CFSR, HFSR, DFSR, MMFAR, BFAR, AFSR;
	// Todo: after dev_lfc define
	//efuse_dev_lfc_state_t dev_lfc_state;

	enum { r0 = 0, r1, r2, r3, r12, lr, pc, psr};
	enum { r4 = 0, r5, r6, r7, r8, r9, r10, r11};

	/*
	    0xE000ED28 CFSR Configurable Fault Status Register
	    0xE000ED28 MMFSR MemManage Fault Status Register
	    0xE000ED29 BFSR BusFault Status Register
	    0xE000ED2A UFSR UsageFault Status Register
	    0xE000ED2C HFSR HardFault Status Register
	    0xE000ED30 DFSR Debug Fault Status Register
	    0xE000ED34 MMFAR MemManage Fault Address Register
	    0xE000ED38 BFAR BusFault Address Register
	    0xE000ED3C AFSR Auxiliary Fault Status Register

	    0xE002ED28 CFSR_NS Configurable Fault Status Register (NS)
	    0xE002ED28 MMFSR_NS MemManage Fault Status Register (NS)
	    0xE002ED29 BFSR_NS BusFault Status Register (NS)
	    0xE002ED2A UFSR_NS UsageFault Status Register (NS)
	    0xE002ED2C HFSR_NS HardFault Status Register (NS)
	    0xE002ED30 DFSR_NS Debug Fault Status Register (NS)
	    0xE002ED34 MMFAR_NS MemManage Fault Address Register (NS)
	    0xE002ED38 BFAR_NS BusFault Address Register (NS)
	    0xE002ED3C AFSR_NS Auxiliary Fault Status Register (NS
	*/
	CFSR  = SCB->CFSR;
	HFSR  = SCB->HFSR;
	DFSR  = SCB->DFSR;
	MMFAR = SCB->MMFAR;
	BFAR  = SCB->BFAR;
	AFSR  = SCB->AFSR;

#if 0  // !defined (CONFIG_BUILD_NONSECURE)
	if (_stdio_port.adapter == NULL) {
		stdio_uart_port_init();
		ConfigDebugErr = 0xFFFFFFFF;
	}
#endif
	if ((lr_value & 0x04) == 0) {
		stack = mstack + 8;     // since we pushed R4 ~ R11 in MSP
	} else {
		stack = pstack;
	}
#if 0
#if !defined (CONFIG_BUILD_NONSECURE)
	efuse_life_cycle_state_read((uint8_t *)&dev_lfc_state.byte);
#else
	dev_lfc_state.byte = 0xFF;
#endif

	if (dev_lfc_state.bit.dev_lfc_state != LfC_Deployed) {
#if !defined (CONFIG_BUILD_NONSECURE)
		dbg_printf("\r\nS-Domain Fault Handler: msp=0x%08x psp=0x%08x lr=0x%08x fault_id=%u\r\n",
				   (uint32_t)mstack, (uint32_t)pstack, lr_value, fault_id);
#else
		dbg_printf("\r\nNS-Domain Fault Handler: msp=0x%08x psp=0x%08x lr=0x%08x fault_id=%u\r\n",
				   (uint32_t)mstack, (uint32_t)pstack, lr_value, fault_id);
#endif
	}
#endif
	if (fault_id == 0) {
		dbg_printf("\r\nHard Fault: \r\n");
		dbg_printf("HardFault Status Reg = 0x%08x\r\n", HFSR);
		if (HFSR & SCB_HFSR_FORCED_Msk) {
			// forced HardFault
			/* When this bit is set to 1, the HardFault handler must read the other
			   fault status registers to find the cause of the fault. */
			dbg_printf("Forced HardFault\r\n");
			dbg_printf("SCB Configurable Fault Status Reg = 0x%08x\r\n", CFSR);
		}

		if (HFSR & SCB_HFSR_VECTTBL_Msk) {
			// Indicates a BusFault on a vector table read during exception processing
			/* When this bit is set to 1, the PC value stacked for the exception return points to
			   the instruction that was preempted by the exception.*/
			dbg_printf("BusFault on vector table read\r\n");
		}
	} else if (fault_id == 1) {
		dbg_printf("\r\nUsage Fault: \r\n");
	} else if (fault_id == 2) {
		dbg_printf("\r\nBus Fault: \r\n");
	} else if (fault_id == 3) {
		dbg_printf("\r\nMemManage Fault: \r\n");
	} else if (fault_id == 4) {
		dbg_printf("\r\nSecurity Fault: \r\n");
	} else if (fault_id == 5) {
		dbg_printf("\r\nDebug Monitor: \r\n");
	} else {
		dbg_printf("\r\nDefault Hard Fault: \r\n");
	}
	parse_cfsr(CFSR);
#if 0
	if (dev_lfc_state.bit.dev_lfc_state == LfC_Deployed) {
		while (1);
	}
#endif
	if ((lr_value & BIT0) == 0) {
		dbg_printf("\r\nNS-domain exception ");
	} else {
		dbg_printf("\r\nS-domain exception ");
	}

	if ((lr_value & BIT3) == 0) {
		dbg_printf("from Handler mode, ");
	} else {
		dbg_printf("from Thread mode, ");
	}

	if ((lr_value & BIT4) == 0) {
		dbg_printf("Extended Stack frame on");
	} else {
		dbg_printf("Standard Stack frame on");
	}

	if ((lr_value & BIT6) == 0) {
		dbg_printf(" NS-");
#if !defined (CONFIG_BUILD_NONSECURE)
		if ((lr_value & 0x04) == 0) {
			stack = (uint32_t *)(__TZ_get_MSP_NS());
		} else {
			stack = (uint32_t *)(__TZ_get_PSP_NS());
		}
#endif
	} else {
		dbg_printf(" S-");
	}

	if ((lr_value & BIT2) == 0) {
		dbg_printf("MSP\r\n");
	} else {
		dbg_printf("PSP\r\n");
	}

	if ((lr_value & BIT5) == 0) {
		dbg_printf("Registers Stacking Skiped\r\n\r\n");
	} else {
		dbg_printf("Registers Saved to stack\r\n\r\n");
	}

	dbg_printf("Stacked: \r\n");
	dbg_printf("R0  = 0x%08x\r\n", stack[r0]);
	dbg_printf("R1  = 0x%08x\r\n", stack[r1]);
	dbg_printf("R2  = 0x%08x\r\n", stack[r2]);
	dbg_printf("R3  = 0x%08x\r\n", stack[r3]);

	// we stacked R4 ~ R11 in the exception handler
	dbg_printf("R4  = 0x%08x\r\n", mstack[r4]);
	dbg_printf("R5  = 0x%08x\r\n", mstack[r5]);
	dbg_printf("R6  = 0x%08x\r\n", mstack[r6]);
	dbg_printf("R7  = 0x%08x\r\n", mstack[r7]);
	dbg_printf("R8  = 0x%08x\r\n", mstack[r8]);
	dbg_printf("R9  = 0x%08x\r\n", mstack[r9]);
	dbg_printf("R10 = 0x%08x\r\n", mstack[r10]);
	dbg_printf("R11 = 0x%08x\r\n", mstack[r11]);
	mstack = (uint32_t *)((uint32_t)mstack + 0x20); // recover stack pointer for we pushed R4 ~ R11

	dbg_printf("R12 = 0x%08x\r\n", stack[r12]);
	dbg_printf("LR  = 0x%08x\r\n", stack[lr]);
	dbg_printf("PC  = 0x%08x\r\n", stack[pc]);
	dbg_printf("PSR = 0x%08x\r\n", stack[psr]);

	dbg_printf("\r\nCurrent: \r\n");
	dbg_printf("LR   = 0x%08x\r\n", lr_value);
	dbg_printf("MSP  = 0x%08x\r\n", mstack);
	dbg_printf("PSP  = 0x%08x\r\n", pstack);
	dbg_printf("xPSR = 0x%08x\r\n", xpsr);

#if !defined (CONFIG_BUILD_NONSECURE)
	dbg_printf("CFSR  = 0x%08x\r\n", CFSR);
	dbg_printf("HFSR  = 0x%08x\r\n", HFSR);
	dbg_printf("DFSR  = 0x%08x\r\n", DFSR);
	dbg_printf("MMFAR = 0x%08x\r\n", MMFAR);
	dbg_printf("BFAR  = 0x%08x\r\n", BFAR);
	dbg_printf("AFSR  = 0x%08x\r\n", AFSR);

	dbg_printf("\r\nCoreDebug: \r\n");
	dbg_printf("DHCSR  = 0x%08x\r\n", CoreDebug->DHCSR);
	dbg_printf("DCRSR  = 0x%08x\r\n", CoreDebug->DCRSR);
	dbg_printf("DCRDR  = 0x%08x\r\n", CoreDebug->DCRDR);
	dbg_printf("DEMCR  = 0x%08x\r\n", CoreDebug->DEMCR);
	dbg_printf("DAUTHCTRL  = 0x%08x\r\n", CoreDebug->DAUTHCTRL);
	dbg_printf("DSCSR  = 0x%08x\r\n", CoreDebug->DSCSR);

if (0) {
volatile uint32_t *ptr;

ptr=(volatile uint32_t *)0xE0001000;
for (i=0;i<0x120/4;i++) {
	_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
	ptr++;
}
ptr =(uint32_t *)(0xE0001000 + 0xFB0);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
ptr =(uint32_t *)(0xE0001000 + 0xFB4);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
ptr =(uint32_t *)(0xE0001000 + 0xFBC);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);

ptr =(uint32_t *)(0xE000EDF0);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
ptr =(uint32_t *)(0xE000EDF4);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
ptr =(uint32_t *)(0xE000EDF8);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);
ptr =(uint32_t *)(0xE000EDFC);
_rtl_printf("0x%08x: 0x%08x\n", (unsigned int)ptr, (unsigned int)*ptr);

//*ptr |= (uint32_t)(1U<<17);  //trigger DebugMon pend
}

#else
	dbg_printf("CFSR_NS  = 0x%08x\r\n", CFSR);
	dbg_printf("HFSR_NS  = 0x%08x\r\n", HFSR);
	dbg_printf("DFSR_NS  = 0x%08x\r\n", DFSR);
	dbg_printf("MMFAR_NS = 0x%08x\r\n", MMFAR);
	dbg_printf("BFAR_NS  = 0x%08x\r\n", BFAR);
	dbg_printf("AFSR_NS  = 0x%08x\r\n", AFSR);
#endif
	ret = __get_PRIMASK();
	dbg_printf("PriMask = 0x%08x\r\n", ret);
//    ret = __get_BASEPRI();
//    dbg_printf("BasePri 0x%08x\r\n", ret);
	dbg_printf("SVC priority: 0x%02x\r\n", HAL_READ8(0xE000ED1F, 0));
	dbg_printf("PendSVC priority: 0x%02x\r\n", HAL_READ8(0xE000ED22, 0));
	dbg_printf("Systick priority: 0x%02x\r\n", HAL_READ8(0xE000ED23, 0));

	dbg_printf("\r\nMSP Data:\r\n");
	src = (uint32_t)mstack;
	for (i = 0; i < 64; i += 4, src += 16) {
		if (*(u32 *)(src) == 0xDEADBEEF) {
			break;
		}
		dbg_printf("%08X:    %08X", src, *(u32 *)(src));
		dbg_printf("    %08X", *(u32 *)(src + 4));
		dbg_printf("    %08X", *(u32 *)(src + 8));
		dbg_printf("    %08X\r\n", *(u32 *)(src + 12));
	}

	src = (uint32_t)pstack;
	if (src != 0) {
		dbg_printf("\r\nPSP Data:\r\n");
		for (i = 0; i < 64; i += 4, src += 16) {
			dbg_printf("%08X:    %08X", src, *(u32 *)(src));
			dbg_printf("    %08X", *(u32 *)(src + 4));
			dbg_printf("    %08X", *(u32 *)(src + 8));
			dbg_printf("    %08X\r\n", *(u32 *)(src + 12));
		}
	}

#if !defined (CONFIG_BUILD_NONSECURE)
#if  (__ARM_FEATURE_CMSE == 3U)
	if (((SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk) == 0) || (fault_id == 4)) {
		// BusFault, HardFault & NMI handler are in secure state or in SecureFault
		uint32_t CFSR_NS, HFSR_NS, DFSR_NS, MMFAR_NS, BFAR_NS, AFSR_NS;
		uint32_t MSP_NS, PSP_NS;

		CFSR_NS  = SCB_NS->CFSR;
		HFSR_NS  = SCB_NS->HFSR;
		DFSR_NS  = SCB_NS->DFSR;
		MMFAR_NS = SCB_NS->MMFAR;
		BFAR_NS  = SCB_NS->BFAR;
		AFSR_NS  = SCB_NS->AFSR;

		MSP_NS = __TZ_get_MSP_NS();
		PSP_NS = __TZ_get_PSP_NS();
		dbg_printf("\r\n == NS Dump ==\r\n", CFSR_NS);
		dbg_printf("CFSR_NS  = 0x%08x\r\n", CFSR_NS);
		dbg_printf("HFSR_NS  = 0x%08x\r\n", HFSR_NS);
		dbg_printf("DFSR_NS  = 0x%08x\r\n", DFSR_NS);
		dbg_printf("MMFAR_NS = 0x%08x\r\n", MMFAR_NS);
		dbg_printf("BFAR_NS  = 0x%08x\r\n", BFAR_NS);
		dbg_printf("AFSR_NS  = 0x%08x\r\n", AFSR_NS);

		dbg_printf("MSP_NS   = 0x%08x\r\n", MSP_NS);
		dbg_printf("PSP_NS   = 0x%08x\r\n", PSP_NS);

		dbg_printf("NS HardFault Status Reg = 0x%08x\r\n", HFSR_NS);
		if (HFSR_NS & SCB_HFSR_FORCED_Msk) {
			// forced HardFault
			/* When this bit is set to 1, the HardFault handler must read the other
			   fault status registers to find the cause of the fault. */
			dbg_printf("Forced HardFault\r\n");
			dbg_printf("SCB Configurable Fault Status Reg = 0x%08x\r\n", HFSR_NS);
		}

		if (HFSR_NS & SCB_HFSR_VECTTBL_Msk) {
			// Indicates a BusFault on a vector table read during exception processing
			/* When this bit is set to 1, the PC value stacked for the exception return points to
			   the instruction that was preempted by the exception.*/
			dbg_printf("NS BusFault on vector table read\r\n");
		}

		parse_cfsr(CFSR_NS);

		if (MSP_NS != 0) {
			dbg_printf("\r\nNS MSP Data:\r\n");
			src = (uint32_t)MSP_NS;
			for (i = 0; i < 64; i += 4, src += 16) {
				dbg_printf("%08X:    %08X", src, *(u32 *)(src));
				dbg_printf("    %08X", *(u32 *)(src + 4));
				dbg_printf("    %08X", *(u32 *)(src + 8));
				dbg_printf("    %08X\r\n", *(u32 *)(src + 12));
			}
		}

		if (PSP_NS != 0) {
			dbg_printf("\r\nNS PSP Data:\r\n");
			src = (uint32_t)PSP_NS;
			for (i = 0; i < 64; i += 4, src += 16) {
				dbg_printf("%08X:    %08X", src, *(u32 *)(src));
				dbg_printf("    %08X", *(u32 *)(src + 4));
				dbg_printf("    %08X", *(u32 *)(src + 8));
				dbg_printf("    %08X\r\n", *(u32 *)(src + 12));
			}
		}
	}
#endif
	if ((lr_value & BIT6) == 0) {
		stack_trace_back((__TZ_get_MSP_NS()), (__TZ_get_PSP_NS()), lr_value, 1);
	} else {
		stack_trace_back((uint32_t)mstack, (uint32_t)pstack, lr_value, 0);
	}
#else
	stack_trace_back((uint32_t)mstack, (uint32_t)pstack, lr_value, 0);
#endif

	if (CoreDebug->DHCSR & 0x01) {
		// Debugger Connected
		__BKPT(0);      // Halt program here
	}
	while (1);
#endif
}

void DMH(void)
{
	_rtl_printf("RTS_DMH\n");
	rlx_hard_fault_handler_c((uint32_t*)__get_MSP(), (uint32_t*)__get_PSP(), (uint32_t)__builtin_return_address(0), 5);
}

void set_DMH(void)
{
	__disable_irq();
	_rtl_printf("ORG_DMH: %08x\n", NVIC_GetVector(-4));
	NVIC_SetVector(-4, (uint32_t)DMH);
	_rtl_printf("NEW_DMH: %08x\n", NVIC_GetVector(-4));
	NVIC_SetPriority(-4, 0);
	__enable_irq();
}

void rlx_set_watchpoint(int id, unsigned long start_addr, unsigned long rw_type)
{
	volatile uint32_t *pCOMP, *pFUNC;
	int type=0;

	if (id & ~3) {  //only 0~3
		_rtl_printf("%s: watchpoint ID%d not support\n", id);
		return;
	}

	if (start_addr == 0) {  //disable watchpoint
		pCOMP = &DWT->COMP0; pFUNC = &DWT->FUNCTION0;
		pCOMP[id] = 0;
		pFUNC[id] = (uint32_t)0;
		return;
	}

	switch(rw_type) {
		case WATCH_R:  //R
			type = 6;
			break;
		case WATCH_W:  //W
			type = 5;
			break;
		case (WATCH_R|WATCH_W):  //R|W
			type = 4;
			break;
		default:
			_rtl_printf("%s: type %d not support\n", rw_type);
			return;
			break;
	}

	CoreDebug->DEMCR |= (uint32_t)((1UL<<24)|(1UL<<16));  //TRCENA|MON_EN

	pCOMP = &DWT->COMP0; pFUNC = &DWT->FUNCTION0;
	pCOMP[id*4] = start_addr;
	pFUNC[id*4] = (uint32_t)((0U<<10)|(1U<<4)|type);  //1B|Gen dbg evt|type
}

#else

#endif
