// brief: build config for RLX layer.
//
#ifndef __RT_CONFIG_RLX_H__
#define __RT_CONFIG_RLX_H__

#include <FreeRTOS.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif

// ----------------------------------------------
// from uboot's board/rlxboard/rlxboard.h
//
// DON'T modify unless you know what you doing.
// ----------------------------------------------
#define CONFIG_SYS_TEXT_BASE    0xbfc00000

#define CONFIG_TARGET_ASIC

/*cpu frequency setting*/
#ifdef CONFIG_TARGET_ASIC
#define CPU_FREQUCNCY			configCPU_CLOCK_HZ /*Pro2 VOE*/
#endif	// CONFIG_TARGET_ASIC

#ifdef CONFIG_TARGET_FPGA
#define CPU_FREQUCNCY			50000000
#endif
#define CONFIG_SYS_MIPS_TIMER_FREQ	CPU_FREQUCNCY
#define CONFIG_SYS_HZ			1000

// ----------------------------------------------
// our define
// ----------------------------------------------
// brief: board chip & package
// chip : 3903, 3904, 3905
// pkg  : 'A' -> BGA151 or BGA234 (just for sw convenient use)
//        'N' -> QFN88
// note : valid combination for now
//        3903N,
//        3904A, 3904N
//        3905N
//
#define CFG_BOARD_CHIP			3915
#define CFG_BOARD_PKG			'\0'

#define CPU_ARCH_MIPS			1
#define CPU_ARCH_ARM			2

#define CFG_CPU_ARCH			CPU_ARCH_MIPS
#define CFG_CPU_BITS			32
#define CFG_CPU_FREQ			CPU_FREQUCNCY

#define CPU_1S_TICKS			(CFG_CPU_FREQ)
#define CPU_MS_TICKS			(CFG_CPU_FREQ/1000)
#define CPU_US_TICKS			(CFG_CPU_FREQ/1000000)
#define cycle2ms(t)				((t)/(CFG_CPU_FREQ/1000.0))

#define CFG_32BIT				(CFG_CPU_BITS == 32)
#define CFG_64BIT				(CFG_CPU_BITS == 64)

#define CFG_LITTLE_ENDIAN		(1)
#define CFG_BIG_ENDIAN			(0)

#define CFG_SYS_ENDIAN			(CFG_LITTLE_ENDIAN)

// brief: whether to run sys_info code segment inside init_bsp() or not.
// value: 0, 1
#define CFG_INIT_BSP_SYSINFO	0
// brief: whether to print sf info during spi_flash_probe_slave() or not.
// value: 0, 1
#define CFG_INIT_BSP_SF			0

#endif	// __RT_CONFIG_RLX_H__
