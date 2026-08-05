// brief: system operations
//
#ifndef __RLX_SYS_H__
#define __RLX_SYS_H__

// ----------------------------------------------------------------------------
//  from uboot's common.h & rlxboard.c
// ----------------------------------------------------------------------------
enum sys_mem_sd_model {
	SYS_MEM_SD_NAND_SPIC,
	SYS_MEM_SD_ETH,
	SYS_MEM_SD_CIPHER,
	SYS_MEM_SD_AUDIO,
	SYS_MEM_SD_H264,
	SYS_MEM_SD_U2DEV,
	SYS_MEM_SD_SDIO
};

void rlx_sys_mem_up(int model);
void rlx_sys_mem_down(int model);

// ----------------------------------------------------------------------------
//  watch dog
// ----------------------------------------------------------------------------
typedef enum {
	WDOG_TIMEOUT_1S = 0x0,
	WDOG_TIMEOUT_2S = 0x1,
	WDOG_TIMEOUT_4S = 0x2,
	WDOG_TIMEOUT_8S = 0x3,
} wdog_time_t;

void	rlx_sys_wdog_restart(wdog_time_t time);

#endif	// __RLX_SYS_H__
