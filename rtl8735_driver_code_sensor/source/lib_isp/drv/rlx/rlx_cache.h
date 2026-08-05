/*
 * Copyright (c) 2011 The Chromium OS Authors.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
// Frank: this file is from uboot's /arch/rlx/include/asm/cache.h
#ifndef __RLX_MIPS_CACHE_H__
#define __RLX_MIPS_CACHE_H__
#include "rlx_inc.h"

/*
 * The maximum L1 data cache line size on MIPS seems to be 128 bytes.  We use
 * that as a default for aligning DMA buffers unless the board config has
 * specified another cache line size.
 */
//#ifdef CONFIG_SYS_CACHELINE_SIZE
//#define ARCH_DMA_MINALIGN	CONFIG_SYS_CACHELINE_SIZE
//#else
#define ARCH_DMA_MINALIGN	128
//#error "ARCH_DMA_MINALIGN mismatch. Include rlxboard.h before rlx_mman.h"
//#endif

#endif /* __RLX_MIPS_CACHE_H__ */
