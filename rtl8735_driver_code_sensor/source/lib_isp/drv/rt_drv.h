// ============================================================================
// brief: a common header that all rt_drv code must include.
//
// rules:
//	- MUST include rt_config_rlx.h
//	  rt_drv directly on top of rlx layer, so they have to share same h/w
//	  define macros, for example, CPU_FREQUCNCY, CFG_SYS_ENDIAN, ...,etc.
//
// ============================================================================
#ifndef __RT_DRV_H__
#define __RT_DRV_H__

#include "rt_types.h"
#include "rt_code.h"
#include "rt_config_rlx.h"
#include "rt_config_drv.h"
#include "rt_config_sys.h"
#include "rt_log.h"
#include "my_def.h"

// ----------------------------------------------------------------------------
//  original from uboot
// ----------------------------------------------------------------------------
// file: \drv\uboot_rlx\rlxboard.h
//#define CONFIG_UPDATE_KERNEL_FROM_SD

// NOTE: this MUST be defined.
//#define CONFIG_BOARD_RTS3903

// file: \drv\mtd\spi\rt_sf_probe.c
//#define CONFIG_DUAL_CHANNEL

// file: \drv\crypto\rt_cryto.c
// note: for now, this option is not support, must keep undefined.
//#define LOAD_KEY_FROM_EFUSE

#endif	// __RT_DRV_H__
