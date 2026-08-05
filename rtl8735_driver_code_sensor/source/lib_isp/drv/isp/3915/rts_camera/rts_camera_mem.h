/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_mem.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_CAMERA_MEM_H
#define _RTS_CAMERA_MEM_H

/*
struct rtscam_mem_info {
	struct device	*dev;
	void            *virt_base;
	unsigned int    device_base;
	unsigned int    pfn_base;
	int             size;
	unsigned long   *bitmap;
	int             bitmap_size;
	int		initialized;
};
*/

void *rtscam_mem_alloc(size_t size, void **phy_addr, unsigned int align_bit);
void rtscam_mem_free(void *vaddr);

#endif

