/*
 * videobuf2-dma-contig.c - DMA contig memory allocator for videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */


#include "cmsis_os2.h"
#include <errno.h>
#include "rts_errno.h"
#include <media/videobuf2-core.h>
#include <media/videobuf2-memops.h>
#include <rtscamkit.h>
#include "rts-dma-contig.h"
#include "rts_isp_mem.h"
#include "isp_log.h"

struct rts_dc_buf {
//	struct rtscam_mem_info	*rtsmem;
//	struct device			*dev;
	void				*vaddr;
	unsigned long			size;
	void				*dma_addr;
	enum dma_data_direction		dma_dir;
//	struct sg_table			*dma_sgt;
	int                             buf_io;

	/* MMAP related */
//	struct vb2_vmarea_handler	handler;
	int			refcount;
//	struct sg_table			*sgt_base;

	/* USERPTR related */
//	struct vm_area_struct		*vma;

	/* DMABUF related */
//	struct dma_buf_attachment	*db_attach;
};

/*********************************************/
/*        scatterlist table functions        */
/*********************************************/


/*
static void rts_dc_sgt_foreach_page(struct sg_table *sgt,
				    void (*cb)(struct page *pg))
{
	struct scatterlist *s;
	unsigned int i;

	for_each_sg(sgt->sgl, s, sgt->orig_nents, i) {
		struct page *page = sg_page(s);
		unsigned int n_pages = PAGE_ALIGN(s->offset + s->length)
				       >> PAGE_SHIFT;
		unsigned int j;

		for (j = 0; j < n_pages; ++j, ++page)
			cb(page);
	}
}

static unsigned long rts_dc_get_contiguous_size(struct sg_table *sgt)
{
	struct scatterlist *s;
	dma_addr_t expected = sg_dma_address(sgt->sgl);
	unsigned int i;
	unsigned long size = 0;

	for_each_sg(sgt->sgl, s, sgt->nents, i) {
		if (sg_dma_address(s) != expected)
			break;
		expected = sg_dma_address(s) + sg_dma_len(s);
		size += sg_dma_len(s);
	}
	return size;
}
*/

/*********************************************/
/*         callbacks for all buffers         */
/*********************************************/

static void *rts_dc_cookie(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;

	return &buf->dma_addr;
}

static void *rts_dc_vaddr(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;

	return buf->vaddr;
}

static unsigned int rts_dc_num_users(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;

	return atomic_read_isp(&buf->refcount);
}

/*
static void rts_dc_prepare(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;
	struct sg_table *sgt = buf->dma_sgt;

	// DMABUF exporter will flush the cache for us
	if (buf->db_attach || !buf->buf_io)
		return;

	dma_sync_sg_for_device(buf->dev, sgt->sgl, sgt->nents, buf->dma_dir);
}

static void rts_dc_finish(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;
	struct sg_table *sgt = buf->dma_sgt;

	// DMABUF exporter will flush the cache for us
	if (buf->db_attach || !buf->buf_io)
		return;

	dma_sync_sg_for_cpu(buf->dev, sgt->sgl, sgt->nents, buf->dma_dir);
}
*/

/*********************************************/
/*        callbacks for MMAP buffers         */
/*********************************************/

void *rtscam_mem_alloc(size_t size, void **phy_addr, unsigned int align_bit)
{
	void *vaddr;
	int align_size;
	
	if (align_bit > 12) {  //phy addr align bit#
		align_bit = 12;
		printf("{%s} physical addr align bit %d too large, set to 12\n", __func__, align_bit);
	} else if (align_bit < 2) {
		align_bit = 2;
	}
	align_size = 1 << align_bit;
	vaddr = rts_malloc(size + align_size);
	if (!vaddr)
		return NULL;
	
	if ((int)vaddr & (align_size-1)) {
		*phy_addr = (void*)(((int)vaddr + align_size) & (-align_size) /*& ~0x80000000*/ );
	} else {
		*phy_addr = (void*)((int)vaddr /*& ~0x80000000*/ );
	}
	//printf("{%s} 0x%08x \r\n", __func__, (uint32_t)*phy_addr);
	return vaddr;
}

void rtscam_mem_free(void *vaddr)
{
#ifdef _DEBUG_MEM_
	isp_info("%s rts_free 0x%08x \r\n", __func__, vaddr);
#endif
	rts_free(vaddr);
}

static void rts_dc_put(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;

	if (!atomic_dec_and_test_isp(&buf->refcount))
		return;

	rtscam_mem_free(buf->vaddr);
	rts_free(buf);
}

static void *rts_dc_alloc(unsigned long attrs,
			  unsigned long size, enum dma_data_direction dma_dir)
{
	struct rts_dc_buf *buf;

	buf = rts_calloc(1, sizeof(*buf));
	if (!buf)
		return NULL;

	buf->vaddr = rtscam_mem_alloc(size, &buf->dma_addr, 12);  //2^12 = 4096 bytes aligned
	if (!buf->vaddr) {
		isp_error("alloc memory of size %ld failed\r\n", size);
		rts_free(buf);
		return NULL;
	}

	/* Prevent the device from being released while the buffer is used */
	buf->size = size;
	buf->dma_dir = dma_dir;

//	buf->handler.refcount = &buf->refcount;
//	buf->handler.put = rts_dc_put;
//	buf->handler.arg = buf;

	atomic_inc_isp(&buf->refcount);

	return buf;
}

//static int rts_dc_mmap(void *buf_priv, struct vm_area_struct *vma)
//{
//	struct rts_dc_buf *buf = buf_priv;
//	int ret;
//
//	if (!buf) {
//		printf("No buffer to map\n");
//		return -EINVAL;
//	}
//
//	/*
//	 * dma_mmap_* uses vm_pgoff as in-buffer offset, but we want to
//	 * map whole buffer
//	 */
//	vma->vm_pgoff = 0;
//
//	ret = rtscam_mem_mmap(buf->rtsmem, vma, buf->vaddr,
//			      buf->dma_addr, buf->size);
//
//	if (ret) {
//		pr_err("Remapping memory failed, error: %d\n", ret);
//		return ret;
//	}
//
//	vma->vm_flags		|= VM_DONTEXPAND | VM_DONTDUMP;
//	vma->vm_private_data	= &buf->handler;
//	vma->vm_ops		= &vb2_common_vm_ops;
//
//	vma->vm_ops->open(vma);
//
//	pr_debug("%s: mapped dma addr 0x%08lx at 0x%08lx, size %ld\n",
//		 __func__, (unsigned long)buf->dma_addr, vma->vm_start,
//		 buf->size);
//
//	return 0;
//}

/*********************************************/
/*       callbacks for USERPTR buffers       */
/*********************************************/

/*
static int rts_dc_get_user_pages(unsigned long start, struct page **pages,
				 int n_pages, struct vm_area_struct *vma,
				 int write)
{
	return rtscam_get_user_pages(start, pages, n_pages, vma, write);
}

static void rts_dc_put_dirty_page(struct page *page)
{
	set_page_dirty_lock(page);
	put_page(page);
}

static void rts_dc_put_userptr(void *buf_priv)
{
	struct rts_dc_buf *buf = buf_priv;
//	struct sg_table *sgt = buf->dma_sgt;

//	dma_unmap_sg(buf->dev, sgt->sgl, sgt->orig_nents, buf->dma_dir);
//	if (!rtscam_vma_is_io(buf->vma))
//		rts_dc_sgt_foreach_page(sgt, rts_dc_put_dirty_page);
//
//	sg_free_table(sgt);
//	rts_free(sgt);
	buf->vma = NULL;
	rts_free(buf);
}

static void *rts_dc_get_userptr(unsigned long vaddr,
				unsigned long size,
				enum dma_data_direction dma_dir)
{
	struct rts_dc_buf *buf;
	unsigned long start;
	unsigned long end;
	unsigned long offset;
	void *pages;
	int n_pages;
	int ret = 0;
	struct vm_area_struct *vma;
	unsigned long contig_size;
	unsigned long dma_align = dma_get_cache_alignment();

	// Only cache aligned DMA transfers are reliable
	if (!IS_ALIGNED(vaddr | size, dma_align)) {
		printf("user data must be aligned to %lu bytes\n", dma_align);
		return NULL;
	}

	if (!size) {
		pr_debug("size is zero\n");
		return NULL;
	}

	buf = rts_calloc(sizeof * buf);
	if (!buf)
		return NULL;

	buf->dev = dev;
	buf->dma_dir = dma_dir;

	start = vaddr & PAGE_MASK;
	offset = vaddr & ~PAGE_MASK;
	end = PAGE_ALIGN(vaddr + size);
	n_pages = (end - start) >> PAGE_SHIFT;

	pages = rts_malloc(n_pages * sizeof(pages[0]));
	if (!pages) {
		ret = -ENOMEM;
		printf("failed to allocate pages table\n");
		goto fail_buf;
	}

	// current->mm->mmap_sem is taken by videobuf2 core
	vma = find_vma(current->mm, vaddr);
	if (!vma) {
		pr_err("no vma for address %lu\n", vaddr);
		ret = -EFAULT;
		goto fail_pages;
	}

	if (vma->vm_end < vaddr + size) {
		pr_err("vma at %lu is too small for %lu bytes\n", vaddr, size);
		ret = -EFAULT;
		goto fail_pages;
	}

	buf->vma = vma;

	buf->dma_addr = sg_dma_address(sgt->sgl);
	buf->size = size;
//	buf->dma_sgt = sgt;

	return buf;

fail_vma:
	buf->vma = NULL;

fail_pages:
	rts_free(pages); / rts_free is NULL-proof

fail_buf:
	rts_free(buf);

	return NULL;
}
*/

/*********************************************/
/*       DMA CONTIG exported functions       */
/*********************************************/

const struct vb2_mem_ops rts_dma_contig_memops = {
	.alloc		= rts_dc_alloc,
	.put		= rts_dc_put,
	.cookie		= rts_dc_cookie,
	.vaddr		= rts_dc_vaddr,
//	.mmap		= rts_dc_mmap,
//	.get_userptr	= NULL,  //rts_dc_get_userptr,
//	.put_userptr	= NULL,  //rts_dc_put_userptr,
	.prepare	= NULL,  //rts_dc_prepare,
	.finish		= NULL,  //rts_dc_finish,
	.num_users	= rts_dc_num_users,
};
//EXPORT_SYMBOL_GPL(rts_dma_contig_memops);

//MODULE_DESCRIPTION("DMA-contig memory handling routines for videobuf2");
//MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>");
//MODULE_LICENSE("GPL");
