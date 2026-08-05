/*
 * Realtek Semiconductor Corp.
 *
 * media/video/md2/rts_pprc.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <rtscamkit.h>
#include "rts_img_proc.h"

#include "isp_mem.h"

#define RTSMD2_PPRC_TMPBUF_NUM (1)
#define RTSMD2_PPRC_BUF_ALIGN (4)

int rts_pprc_init(struct rts_pprc_attr *attr,
		struct rts_pprc_instance *pp)
{
	int ret = 0;
	int tmp_img_len, label_img_len, cc_len, roi_len;

	if (!pp)
		return -EINVAL;

	pp->ops = find_pix_ops(attr->fmt);
	pp->bitops = find_pix_ops(PIX_FMT_1BPP);
	pp->roi.map_ops = find_pix_ops(attr->roi_fmt);

	if (!pp->ops || !pp->roi.map_ops) {
		ret = -EINVAL;
		goto failed;
	}

	pp->roi.width = attr->width;
	pp->roi.height = attr->height;

	pp->_roi.width = attr->width;
	pp->_roi.height = attr->height;
	pp->_roi.begin.x = 0;
	pp->_roi.begin.y = 0;
	pp->_roi.end.x = attr->width;
	pp->_roi.end.y = attr->height;

	tmp_img_len = ALIGNN(get_img_buflen(pp->ops,
			attr->width * attr->height), RTSMD2_PPRC_BUF_ALIGN);//1
	label_img_len = ALIGNN(attr->width * attr->height * sizeof(int),
						RTSMD2_PPRC_BUF_ALIGN);//4
	cc_len = ALIGNN(sizeof(struct CC) * attr->width * attr->height / 2,
				RTSMD2_PPRC_BUF_ALIGN);//8
	roi_len = ALIGNN(get_img_buflen(pp->roi.map_ops,
			attr->width * attr->height), RTSMD2_PPRC_BUF_ALIGN);//1

	/**
	 *totoal size = img_sz * (1 * RTSMD2_PPRC_TMPBUF_NUM + 4 + 1 + 8)
	 * = img_sz * 14
	 */
	pp->data = calloc(1, tmp_img_len * RTSMD2_PPRC_TMPBUF_NUM
				+ label_img_len + roi_len + cc_len);
	if (!pp->data) {
		ret = -ENOMEM;
		goto failed;
	}

	for (int i = 0; i < RTSMD2_PPRC_TMPBUF_NUM; i++)
		pp->tmp_img[i] = (void *)((uint32_t)pp->data + i * tmp_img_len);

	pp->label_img = (void *)((uint32_t)pp->data + RTSMD2_PPRC_TMPBUF_NUM * tmp_img_len);
	pp->roi.map = (void *)((uint32_t)pp->label_img + label_img_len);
	pp->roi.length = roi_len;
	pp->ccon.cc = (void *)((uint32_t)pp->roi.map + roi_len);
	memset(pp->roi.map, 0xff, roi_len);

	return 0;

failed:
	if (pp->data) {
		free(pp->data);
		pp->data = NULL;
	}
	return ret;
}


int rts_pprc_run(struct rts_pprc_instance *pprc,
		struct rts_pprc_filter *filter,
		void *src, void *dst)
{
	memset(pprc->ccon.cc, 0, sizeof(struct CC) * pprc->ccon.cc_index);
	pprc->ccon.cc_index = 0;


	if (!filter->enable_cc_info) {
		if (dst)
			img_run_roi(pprc->bitops, OP_dilate_4n_to_yonly,
				&pprc->_roi, src, dst);
		return 0;
	}

	img_run_roi(pprc->bitops, OP_dilate_4n_to_yonly,
			&pprc->_roi, src, pprc->tmp_img[0]);

/*
 *	img_run_roi(pprc->ops, OP_erode_4n, &pprc->_roi,
 *				pprc->tmp_img[0], pprc->tmp_img[1]);
 */

	img_run_roimap_with_priv(pprc->ops,
			OP_label_cc_4n, &pprc->roi,
			pprc->tmp_img[0], pprc->label_img,
			&pprc->ccon);

	for (int i = 0; i < pprc->ccon.cc_index; i++) {
		struct CC *pcc = &pprc->ccon.cc[i], *pcc2;
		float ar;
		float ratio;
		int w, h;

		if (!filter->enable_cc_filter)
			continue;

		if (!(pcc->flags & CC_FLAG_ROOT)) {
			pcc2 = &pprc->ccon.cc[pcc->parent_label];
			if (pcc2->flags & CC_FLAG_FILTERED)
				pcc->flags |= CC_FLAG_FILTERED;
			continue;
		}

		w = pcc->r - pcc->l;
		h = pcc->b - pcc->u;
		ar = (float)w / (float)h;
		ratio = (float)(pcc->pixel_cnt) / (w * h);

		if (pcc->pixel_cnt >= filter->nr_cc_thd
			&& ar >= filter->min_ar
			&& ar <= filter->max_ar
			&& ratio >= filter->cc_ratio)
			;
		else
			pcc->flags |= CC_FLAG_FILTERED;
	}

	if (!dst)
		return 0;

	img_run_roimap_with_priv(pprc->ops,
			OP_get_cc_map, &pprc->roi,
			pprc->label_img, dst,
			&pprc->ccon);
	return 0;
}


void rts_pprc_release(struct rts_pprc_instance *pp)
{
	if (!pp)
		return;
	if (pp->data) {
		free(pp->data);
		pp->data = NULL;
	}
}
