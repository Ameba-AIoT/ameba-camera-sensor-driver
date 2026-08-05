// brief: MTD rt_drv interface.
//
#ifndef RT_MTD_H
#define RT_MTD_H
#include "rt_drv.h"

#ifdef __cplusplus
extern "C" {
#endif
// error code define
#define RT_E_MTD_MALLOC		(RT_CODE_BASE_MTD - 1)
#define RT_E_MTD_READ		(RT_CODE_BASE_MTD - 2)
#define RT_E_MTD_WRITE		(RT_CODE_BASE_MTD - 3)
#define RT_E_MTD_ERASE		(RT_CODE_BASE_MTD - 4)

#define RT_SF_READ_UNIT_SZ	32
#define rt_sf_is_valid_readsize(size)	(((size) % RT_SF_READ_UNIT_SZ) == 0)

void rt_sf_print(void);
int rt_sf_probe(unsigned int bus, unsigned int cs, unsigned int speed, unsigned int mode);

int rt_sf_erase(u32 sf_addr, u32 len);
int rt_sf_dump(u32 mem_addr, u32 sf_addr, u32 len);
int rt_sf_read(u32 mem_addr, u32 sf_addr, u32 len);
int rt_sf_write(u32 mem_addr, u32 sf_addr, u32 len);
int rt_sf_update(u32 mem_addr, u32 sf_addr, u32 len);

// brief: read status register (RDSR)
//
// @code: for valid CMD_CODE, please check your flash's datasheet or docment at first.
//
int rt_sf_rdsr(u8 code, u8 *out);
// ----------------------------------------------------------------------------
//  MTD partition info.
// ----------------------------------------------------------------------------
void rt_mtd_dump(void);
u32 rt_mtd_calc_sf_addr(u8 mtd_idx, u32 mtd_ofs);

//
#define rt_sf_size_uboot_hconf()	(CFG_UBOOT_HCONF_SIZE)
#define rt_sf_size_rtos_hconf()		ROUND(hconf_size(), RT_SF_READ_UNIT_SZ)
#define rt_sf_size_entire_hconf()	(rt_sf_size_uboot_hconf() + rt_sf_size_rtos_hconf())
#define rt_sf_size_entire_kernel()	(CFG_KERNEL_MTD_SIZE)
#define rt_sf_size_entire_free()	(CFG_FREE_MTD_SIZE)

#define rt_sf_addr_uboot_hconf()	rt_mtd_calc_sf_addr(CFG_HCONF_MTD_IDX,  0)
#define rt_sf_addr_rtos_hconf()		rt_mtd_calc_sf_addr(CFG_HCONF_MTD_IDX,  rt_sf_size_uboot_hconf())
#define rt_sf_addr_kernel()			rt_mtd_calc_sf_addr(CFG_KERNEL_MTD_IDX, CFG_KERNEL_MTD_OFS)
#define rt_sf_addr_free()			rt_mtd_calc_sf_addr(CFG_FREE_MTD_IDX,   CFG_FREE_MTD_OFS)

#ifdef __cplusplus
}
#endif


#endif

