/*
 * Realtek Semiconductor Corp.
 *
 * media/video/md2/rts_img_proc.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <rtscamkit.h>
#include "rts_img_proc.h"

static void IBpp_sety(void *img, uint32_t index, uint8_t y)
{
	int d = index / 8;
	int off = index % 8;

	if (y)
		((uint8_t *)img)[d] |= (1 << off);
	else
		((uint8_t *)img)[d] &= (~(1 << off));
}

static void IBpp_gety(void *img, uint32_t index, uint8_t *y)
{
	int off = index % 8;
	int d = index / 8;
	uint8_t val = ((uint8_t *)img)[d] & (1 << off);

	*y = val ? 255 : 0;
}

static uint32_t IBpp_get_img_buflen(uint32_t img_size)
{
	return (img_size + 7) / 8;
}


static int IBpp_exec_cmd(void *img, int cmd, void *arg)
{
	switch (cmd) {
	case IBPP_CMD_GET_BYTE:
		{
			int *arr = arg;
			int index = arr[0];

			arr[1] = ((uint8_t *)img)[index];
		}
		break;
	case IBPP_CMD_SET_BYTE:
		{
			int *arr = arg;
			int index = arr[0];

			((uint8_t *)img)[index] = (uint8_t)arr[1];
		}
		break;
	default:
		return -1;
	}
	return 0;
}


static struct pix_ops Ibpp_ops = {
	.fmt = PIX_FMT_1BPP,
	.set_y = IBpp_sety,
	.get_y = IBpp_gety,
	.exec_cmd = IBpp_exec_cmd,
	.bits_per_pix = 1,
	.get_img_buflen = IBpp_get_img_buflen,
};


static void Yonly_sety(void *img, uint32_t index, uint8_t y)
{
	((uint8_t *)img)[index] = y;
}

static void Yonly_gety(void *img, uint32_t index, uint8_t *y)
{
	*y = ((uint8_t *)img)[index];
}

static int Yonly_exec_cmd(void *img, int cmd, void *arg)
{
	return 0;
}

static uint32_t Yonly_get_img_buflen(uint32_t img_size)
{
	return img_size;
}

static struct pix_ops Yonly_ops = {
	.fmt = PIX_FMT_Y_ONLY,
	.set_y = Yonly_sety,
	.get_y = Yonly_gety,
	.exec_cmd = Yonly_exec_cmd,
	.bits_per_pix = 8,
	.get_img_buflen = Yonly_get_img_buflen,
};


static struct pix_ops *g_pix_ops[] = {
	&Ibpp_ops,
	&Yonly_ops,
};


struct pix_ops *find_pix_ops(int fmt)
{
	struct pix_ops *l_ops = NULL;

	for (int i = 0; i < (int)(sizeof(g_pix_ops) / sizeof(g_pix_ops[0])); i++) {
		if (g_pix_ops[i]->fmt  == fmt) {
			l_ops = g_pix_ops[i];
			break;
		}
	}

	if (!l_ops)
		RTS_ERR("Do not support this pix_fmt yet.\n");

	return l_ops;
}

/*
 *			algorithm opertors
 */

typedef struct __loc_info {
	int w, h;
	int x, y, index;
	//only for boundary
	int u, b, l, r;
	//for avoid mutiply
	int u_base, b_base, row_base;
} loc_info;

typedef struct {
	void (*kernel_boundary)(struct pix_ops *ops, loc_info *loc,
		void *src, void *dst, void *priv);

	void (*kernel)(struct pix_ops *ops, loc_info *loc,
		void *src, void *dst, void *priv);

	void (*pre_process)(struct pix_ops *ops, int w, int h,
				void *src, void *dst, void *priv);
	void (*post_process)(struct pix_ops *ops, int w, int h,
				void *src, void *dst, void *priv);
	int boundary;
} operator_t;


static void clear_dst_img(struct pix_ops *pixops, int w, int h,
			void *src, void *dst, void *priv)
{
	uint32_t imgsz = get_img_buflen(pixops, w * h);

	memset(dst, 0, imgsz);
}

static void clear_yonly_img(struct pix_ops *pixops, int w, int h,
			void *src, void *dst, void *priv)
{
	memset(dst, 0, w * h);
}

static void dilate_4n_b(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t val;
	void (*m_set_y)(void *img, uint32_t index, uint8_t y) = pixops->set_y;

	get_y(pixops, src, loc->index, &val);

	if (!val)
		return;

	m_set_y(dst, loc->u_base + loc->x, 255);
	m_set_y(dst, loc->b_base + loc->x, 255);
	m_set_y(dst, loc->index, 255);
	m_set_y(dst, loc->row_base + loc->l, 255);
	m_set_y(dst, loc->row_base + loc->r, 255);
}


static void dilate_4n_to_yonly_b(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t val;


	get_y(pixops, src, loc->index, &val);
	if (!val)
		return;

	((uint8_t *)dst)[loc->u_base + loc->x] = 255;
	((uint8_t *)dst)[loc->b_base + loc->x] = 255;
	((uint8_t *)dst)[loc->index] = 255;
	((uint8_t *)dst)[loc->row_base + loc->l] = 255;
	((uint8_t *)dst)[loc->row_base + loc->r] = 255;
}


static void dilate_8n_b(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t val;
	void (*m_set_y)(void *img, uint32_t index, uint8_t y) = pixops->set_y;


	get_y(pixops, src, loc->index, &val);
	if (!val)
		return;

	m_set_y(dst, loc->u_base + loc->l, 255);
	m_set_y(dst, loc->u_base + loc->x, 255);
	m_set_y(dst, loc->u_base + loc->r, 255);
	m_set_y(dst, loc->row_base + loc->l, 255);
	m_set_y(dst, loc->index, 255);
	m_set_y(dst, loc->row_base + loc->r, 255);
	m_set_y(dst, loc->b_base + loc->l, 255);
	m_set_y(dst, loc->b_base + loc->x, 255);
	m_set_y(dst, loc->b_base + loc->r, 255);
}


static void erode_4n_b(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t vals[5];
	void (*m_get_y)(void *img, uint32_t index, uint8_t *y) = pixops->get_y;

	m_get_y(src, loc->u_base + loc->x, &vals[0]);
	m_get_y(src, loc->b_base + loc->x, &vals[1]);
	m_get_y(src, loc->row_base + loc->l, &vals[2]);
	m_get_y(src, loc->row_base + loc->r, &vals[3]);
	m_get_y(src, loc->index, &vals[4]);

	if (vals[0] && vals[1] && vals[2] && vals[3] && vals[4])
		set_y(pixops, dst, loc->index, 255);
}


static void erode_8n_b(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t vals[9];
	void (*m_get_y)(void *img, uint32_t index, uint8_t *y) = pixops->get_y;

	m_get_y(src, loc->u_base + loc->l, &vals[0]);
	m_get_y(src, loc->u_base + loc->x, &vals[1]);
	m_get_y(src, loc->u_base + loc->r, &vals[2]);
	m_get_y(src, loc->b_base + loc->l, &vals[3]);
	m_get_y(src, loc->b_base + loc->x, &vals[4]);
	m_get_y(src, loc->b_base + loc->r, &vals[5]);
	m_get_y(src, loc->row_base + loc->l, &vals[6]);
	m_get_y(src, loc->row_base + loc->r, &vals[8]);
	m_get_y(src, loc->index, &vals[7]);

	if (vals[0]
		&& vals[1]
		&& vals[2]
		&& vals[3]
		&& vals[4]
		&& vals[5]
		&& vals[6]
		&& vals[7]
		&& vals[8])
		set_y(pixops, dst, loc->index, 255);
}

static inline int find_parent(struct CC *cc, int l)
{
	while (cc[l].parent_label != l)
		l = cc[l].parent_label;
	return l;
}

static int __union_cc(struct CC *cc, int labela, int labelb)
{
	int l1, l2;

	l1 = find_parent(cc, labela);
	l2 = find_parent(cc, labelb);

	if (l1 != l2) {
		if (l1 < l2) {
			cc[l2].parent_label = l1;
			return l1;
		}

		cc[l1].parent_label = l2;
		return l2;
	}

	return l1;
}

/*
 *static void clear_label_img(struct pix_ops *pixops, int w, int h,
 *                        void *src, void *dst, void *priv)
 *{
 *        memset(dst, 0, w * h);
 *}
 */

static void label_cc_4n(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *cc_con)
{
	uint32_t *label_img = dst;
	uint8_t val;

	get_y(pixops, src, loc->index, &val);
	if (!val) {
		label_img[loc->index] = 0;
		return;
	}

	struct CC_context *con = cc_con;
	struct CC *_cc = con->cc;
	int min_label = 1e6;
	int l1, l2;

	if (loc->x != 0) {
		l1 = label_img[loc->index - 1];
		if (l1 > 0)
			min_label = (min_label == 1e6) ? l1
				: __union_cc(_cc, l1, min_label);
		}
	if (loc->y != 0) {
		l2 = label_img[loc->index - loc->w];
		if (l2 > 0)
			min_label = (min_label == 1e6) ? l2
					: __union_cc(_cc, l2, min_label);
	}


	if (min_label != 1e6) {
		label_img[loc->index] = min_label;
		_cc[min_label].pixel_cnt++;

		if (loc->y < _cc[min_label].u)
			_cc[min_label].u = loc->y;
		else if (loc->y > _cc[min_label].b)
			_cc[min_label].b = loc->y;
		if (loc->x < _cc[min_label].l)
			_cc[min_label].l = loc->x;
		else if (loc->x > _cc[min_label].r)
			_cc[min_label].r = loc->x;
	} else {
		label_img[loc->index] = ++con->cc_index;
		_cc[con->cc_index].parent_label = con->cc_index;
		_cc[con->cc_index].pixel_cnt = 1;

		_cc[con->cc_index].u = loc->y;
		_cc[con->cc_index].b = loc->y;
		_cc[con->cc_index].l = loc->x;
		_cc[con->cc_index].r = loc->x;
	}
}


static const int dir_8n[][2] = { {-1, 0}, {-1, -1}, {0, -1}, {1, -1} };
static void label_cc_8n(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *cc_con)
{
	uint32_t *label_img = dst;
	uint8_t val;

	get_y(pixops, src, loc->index, &val);
	if (!val) {
		label_img[loc->index] = 0;
		return;
	}

	struct CC_context *con = cc_con;
	struct CC *_cc = con->cc;
	int min_label = 1e6;

	for (int i = 0; i < (int)(sizeof(dir_8n)/sizeof(dir_8n[0])); i++) {
		int iy = loc->y + dir_8n[i][1];
		int ix = loc->x + dir_8n[i][0];

		if (iy < 0 || iy >= loc->h || ix < 0 || ix >= loc->w)
			continue;

		int label_val = label_img[iy * loc->w + ix];

		if (label_val > 0) {
			if (min_label == 1e6)
				min_label = label_val;
			else
				min_label = __union_cc(_cc,
						min_label, label_val);
		}
	}

	if (min_label != 1e6) {
		label_img[loc->index] = min_label;
		_cc[min_label].pixel_cnt++;

		if (loc->y < _cc[min_label].u)
			_cc[min_label].u = loc->y;
		else if (loc->y > _cc[min_label].b)
			_cc[min_label].b = loc->y;
		if (loc->x < _cc[min_label].l)
			_cc[min_label].l = loc->x;
		else if (loc->x > _cc[min_label].r)
			_cc[min_label].r = loc->x;
	} else {
		label_img[loc->index] = ++con->cc_index;
		_cc[con->cc_index].parent_label = con->cc_index;
		_cc[con->cc_index].pixel_cnt = 1;

		_cc[con->cc_index].u = loc->y;
		_cc[con->cc_index].b = loc->y;
		_cc[con->cc_index].l = loc->x;
		_cc[con->cc_index].r = loc->x;
	}
}

static void merge_cc(struct pix_ops *ops, int w, int h,
			void *src, void *dst, void *priv)
{
	struct CC_context *con = priv;
	struct CC *cc = con->cc;

	for (int i = 1; i <= con->cc_index; i++) {
		int lp = find_parent(cc, i);

		if (lp != i) {
			cc[lp].pixel_cnt += cc[i].pixel_cnt;

			cc[lp].u = min(cc[lp].u, cc[i].u);
			cc[lp].b = max(cc[lp].b, cc[i].b);
			cc[lp].l = min(cc[lp].l, cc[i].l);
			cc[lp].r = max(cc[lp].r, cc[i].r);
		} else
			cc[i].flags |= CC_FLAG_ROOT;
	}

}

static void get_cc_map(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *cc_con)
{
	int label = ((uint32_t *)src)[loc->index];

	if (!label) {
		set_y(pixops, dst, loc->index, 0);
		return;
	}

	struct CC *pcc = ((struct CC_context *)cc_con)->cc;

	if ((pcc[label].flags & CC_FLAG_FILTERED))
		set_y(pixops, dst, loc->index, 0);
	else
		set_y(pixops, dst, loc->index, 255);
}


static void to_1bpp(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t val;
	int d = loc->index / 8;
	int off = loc->index % 8;

	get_y(pixops, src, loc->index, &val);

	if (val)
		((uint8_t *)dst)[d] |= (1 << off);
	else
		((uint8_t *)dst)[d] &= (~(1 << off));
}

static void to_yonly(struct pix_ops *pixops, loc_info *loc,
		void *src, void *dst, void *priv)
{
	uint8_t val;

	get_y(pixops, src, loc->index, &val);

	if (val)
		((uint8_t *)dst)[loc->index] = 255;
	else
		((uint8_t *)dst)[loc->index] = 0;
}

struct bitmap_header {
	struct file_header {
		char filetype[2];
		uint32_t filesize;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t data_offset;
	} __attribute__((packed)) fh;

	struct bmp_header {
		int32_t bmpheader_size;
		int32_t width;
		int32_t height;
		int16_t planes;
		int16_t bitcount_perpix;
		int32_t compression;
		int32_t sizeimage;
		int32_t xpixpermeter;
		int32_t ypixpermeter;
		int32_t clrused;
		int32_t clrimportant;
	} __attribute__((packed)) bh;
} __attribute__((packed));

struct rgb_pattern {
	unsigned char rgb[4];
};

static const struct rgb_pattern pt_bw[] = {
	{ {0, 0, 0, 0} },
	{ {255, 255, 255, 0} },
};

static const unsigned char reverse_table[] = {
	[0x0] = 0x0,
	[0x1] = 0x8,
	[0x2] = 0x4,
	[0x3] = 0xc,
	[0x4] = 0x2,
	[0x5] = 0xa,
	[0x6] = 0x6,
	[0x7] = 0xe,
	[0x8] = 0x1,
	[0x9] = 0x9,
	[0xa] = 0x5,
	[0xb] = 0xd,
	[0xc] = 0x3,
	[0xd] = 0xb,
	[0xe] = 0x7,
	[0xf] = 0xf,
};

uint8_t reverse_byte(uint8_t b)
{
	return ((reverse_table[b & 0xf] << 4) | reverse_table[(b >> 4)]);
}

static void make_1bpp_bmp_header(struct pix_ops *ops, int w, int h,
				void *src, void *dst, void *priv)
{
	struct Ibpp_bmp_attr *attr = priv;
	struct bitmap_header bhr;
	int row_size = (attr->width + 31) / 32 * 4;
	int abs_h = attr->height < 0 ? -(attr->height) : (attr->height);
	int offset = 0;

	memset(&bhr, 0, sizeof(bhr));
	bhr.fh.filetype[0] = 'B';
	bhr.fh.filetype[1] = 'M';
	bhr.fh.filesize = row_size * abs_h + sizeof(bhr) + sizeof(pt_bw[0]) * 2;
	bhr.fh.data_offset = sizeof(bhr) + sizeof(pt_bw[0]) * 2;
	bhr.bh.bmpheader_size = sizeof(bhr.bh);
	bhr.bh.width = attr->width;
	bhr.bh.height = -attr->height;
	bhr.bh.planes = 1;
	bhr.bh.bitcount_perpix = 1;

	memcpy(dst, &bhr, sizeof(bhr));
	offset += sizeof(bhr);
	memcpy((void *)((uint32_t)dst + offset), pt_bw, sizeof(pt_bw[0]) * 2);
	//offset += sizeof(pt_bw[0]) * 2;

	attr->row_size = row_size;
	attr->data_offset = bhr.fh.data_offset;
	attr->filesize = bhr.fh.filesize;

	if (ops->fmt == PIX_FMT_1BPP && !(attr->width % 8))
		attr->flag_quick = 1;
}

static void to_1bpp_bmp(struct pix_ops *pixops, loc_info *loc,
			void *src, void *dst, void *priv)
{
	struct Ibpp_bmp_attr *attr = priv;
	int off = loc->x % 8;

	if (attr->flag_quick && off)
		return;

	int d = loc->x / 8;
	int index = attr->data_offset + attr->row_size * loc->y + d;
	uint8_t val;

	if (attr->flag_quick) {
		int arr[2];

		arr[0] = (loc->index) / 8;
		exec_cmd(pixops, src, IBPP_CMD_GET_BYTE, arr);
		val = reverse_byte(arr[1]);

		((uint8_t *)dst)[index] = val;
	} else {
		get_y(pixops, src, loc->index, &val);

		if (val)
			((uint8_t *)dst)[index] |= (1 << (7 - off));
		else
			((uint8_t *)dst)[index] &= (~(1 << (7 - off)));
	}
}


static void read_1bpp_bmp_header(struct pix_ops *ops, int w, int h,
				void *src, void *dst, void *priv)
{
	struct Ibpp_bmp_attr *attr = priv;
	struct bitmap_header *bhr = src;

	attr->width = -1;
	attr->height = -1;

	if (bhr->fh.filetype[0] != 'B' || bhr->fh.filetype[1] != 'M')
		return;
	attr->filesize = bhr->fh.filesize;
	attr->data_offset = bhr->fh.data_offset;

	if (bhr->bh.planes != 1 || bhr->bh.bitcount_perpix != 1)
		return;

	attr->width = bhr->bh.width;
	attr->height = abs(bhr->bh.height);
	attr->row_size = (attr->width + 31) / 32 * 4;
	if (bhr->bh.height > 0)
		attr->flag_dir_reverse = 1;

	if (ops->fmt == PIX_FMT_1BPP && !(attr->width % 8))
		attr->flag_quick = 1;
}

static void from_1bpp_bmp(struct pix_ops *pixops, loc_info *loc,
			void *src, void *dst, void *priv)
{
	struct Ibpp_bmp_attr *attr = priv;
	int off = loc->x % 8;

	if (attr->flag_quick && off)
		return;

	int d = loc->x / 8;
	int index;
	uint8_t *bmp = src;

	if (attr->flag_dir_reverse)
		index = attr->data_offset
			+ attr->row_size * (attr->height - loc->y + 1) + d;
	else
		index = attr->data_offset + attr->row_size * loc->y + d;

	if (attr->flag_quick) {
		int arr[2];

		arr[0] = (loc->index) / 8;
		arr[1] = reverse_byte(bmp[index]);
		exec_cmd(pixops, dst, IBPP_CMD_SET_BYTE, arr);
	} else {
		if (bmp[index] & (1 << (7 - off)))
			set_y(pixops, dst, loc->index, 255);
		else
			set_y(pixops, dst, loc->index, 0);
	}
}

static void filter_roi(struct pix_ops *pixops, loc_info *loc,
			void *src, void *dst, void *priv)
{
	uint8_t val;
	uint32_t *pcount = priv;

	get_y(pixops, src, loc->index, &val);
	if (val) {
		set_y(pixops, dst, loc->index, 255);
		*pcount += 1;
	} else
		set_y(pixops, dst, loc->index, 0);
}


static void filter_roi_to_yonly(struct pix_ops *pixops, loc_info *loc,
			void *src, void *dst, void *priv)
{
	uint8_t val;
	uint32_t *pcount = priv;

	get_y(pixops, src, loc->index, &val);
	if (val) {
		((uint8_t *)dst)[loc->index] = 255;
		*pcount += 1;
	} else
		((uint8_t *)dst)[loc->index] = 0;
}


static operator_t g_dilate_4n = {
	.pre_process = clear_dst_img,
	.kernel_boundary = dilate_4n_b,
	.boundary = 1,
};

static operator_t g_dilate_4n_to_yonly = {
	.pre_process = clear_yonly_img,
	.kernel_boundary = dilate_4n_to_yonly_b,
	.boundary = 1,
};

static operator_t g_dilate_8n = {
	.pre_process = clear_dst_img,
	.kernel_boundary = dilate_8n_b,
	.boundary = 1,
};

static operator_t g_erode_4n = {
	.pre_process = clear_dst_img,
	.kernel_boundary = erode_4n_b,
	.boundary = 1,
};

static operator_t g_erode_8n = {
	.pre_process = clear_dst_img,
	.kernel_boundary = erode_8n_b,
	.boundary = 1,
};

static operator_t g_label_cc_4n = {
	.kernel = label_cc_4n,
	.post_process = merge_cc,
};

static operator_t g_label_cc_8n = {
	.kernel = label_cc_8n,
	.post_process = merge_cc,
};

static operator_t g_get_cc_map = {
	.kernel = get_cc_map,
};

static operator_t g_to_fmt_1bpp = {
	.kernel = to_1bpp,
};

static operator_t g_to_fmt_yonly = {
	.kernel = to_yonly,
};

static operator_t g_to_1bpp_bmp = {
	.pre_process = make_1bpp_bmp_header,
	.kernel = to_1bpp_bmp,
};

static operator_t g_from_1bpp_bmp = {
	.pre_process = read_1bpp_bmp_header,
	.kernel = from_1bpp_bmp,
};


static operator_t g_filter_roi = {
	.kernel = filter_roi,
};

static operator_t g_filter_roi_to_yonly = {
	.kernel = filter_roi_to_yonly,
};

static operator_t *g_opcodes[] = {
	[OP_dilate_4n] = &g_dilate_4n,
	[OP_dilate_4n_to_yonly] = &g_dilate_4n_to_yonly,
	[OP_dilate_8n] = &g_dilate_8n,
	[OP_erode_4n] = &g_erode_4n,
	[OP_erode_8n] = &g_erode_8n,
	[OP_label_cc_4n] = &g_label_cc_4n,
	[OP_label_cc_8n] = &g_label_cc_8n,
	[OP_get_cc_map] = &g_get_cc_map,
	[OP_to_fmt_1bpp] = &g_to_fmt_1bpp,
	[OP_to_fmt_yonly] = &g_to_fmt_yonly,
	[OP_to_1bpp_bmp] = &g_to_1bpp_bmp,
	[OP_from_1bpp_bmp] = &g_from_1bpp_bmp,
	[OP_filter_roi] = &g_filter_roi,
	[OP_filter_roi_to_yonly] = &g_filter_roi_to_yonly,
};


int img_run_roi_with_priv(struct pix_ops *pix_ops, int opcode, struct ROI *roi,
				void *src, void *dst, void *priv)
{
	int w = roi->width;
	int h = roi->height;
	operator_t *op;
	loc_info loc;

	if (opcode >= (int)(sizeof(g_opcodes) / sizeof(g_opcodes[0]))) {
		RTS_ERR("Do not support this opcode yet[%d].\n", opcode);
		return -1;
	}
	op = g_opcodes[opcode];

	void (*m_kernel_boundary)(struct pix_ops *ops, loc_info *,
			void *src, void *dst, void *priv)
		= op->kernel_boundary;
	void (*m_kernel)(struct pix_ops *ops, loc_info *,
			void *src, void *dst, void *priv)
		= op->kernel;

	if (op->pre_process)
		op->pre_process(pix_ops, w, h, src, dst, priv);

	loc.w = w;
	loc.h = h;
	if (op->boundary) {
		int s;

		for (loc.y = roi->begin.y; loc.y < roi->end.y; loc.y++) {
			int i1 = roi->begin.x;
			int i2 = roi->end.x - 1;

			s = loc.y * w;
			loc.row_base = s;

			loc.u = max(loc.y - 1, 0);
			loc.b = min(loc.y + 1, h - 1);
			loc.u_base = loc.u * w;
			loc.b_base = loc.b * w;

			loc.x = i1;
			loc.index = s + i1;
			loc.l = i1;
			loc.r = i1 + 1;

			m_kernel_boundary(pix_ops, &loc,
				src, dst, priv);

			for (loc.x = i1 + 1; loc.x < i2; loc.x++) {
				loc.index = s + loc.x;
				loc.l = loc.x - 1;
				loc.r = loc.x + 1;

				m_kernel_boundary(pix_ops, &loc,
					src, dst, priv);
			}

			loc.x = i2;
			loc.index = s + i2;
			loc.l = i2 - 1;
			loc.r = i2;
			m_kernel_boundary(pix_ops, &loc,
				src, dst, priv);
		}
	} else {
		int s;

		for (loc.y = roi->begin.y; loc.y < roi->end.y; loc.y++) {
			s = loc.y * w;

			for (loc.x = roi->begin.x; loc.x < roi->end.x;
							loc.x++) {
				loc.index = s + loc.x;
				m_kernel(pix_ops, &loc,
					src, dst, priv);
			}

		}
	}

	if (op->post_process)
		op->post_process(pix_ops, w, h, src, dst, priv);

	return 0;
}


int img_run_roimap_with_priv(struct pix_ops *pix_ops, int opcode,
			struct ROI_map *map, void *src, void *dst, void *priv)
{
	int w = map->width;
	int h = map->height;
	operator_t *op;
	struct pix_ops *op_map = map->map_ops;
	void *mapdata = map->map;
	uint8_t inroi = 0;
	loc_info loc;

	if (opcode >= (int)(sizeof(g_opcodes) / sizeof(g_opcodes[0]))) {
		RTS_ERR("Do not support this opcode yet[%d].\n", opcode);
		return -1;
	}
	op = g_opcodes[opcode];

	void (*m_get_y)(void *img, uint32_t index, uint8_t *y) = op_map->get_y;
	void (*m_kernel_boundary)(struct pix_ops *ops, loc_info *,
			void *src, void *dst, void *priv)
		= op->kernel_boundary;
	void (*m_kernel)(struct pix_ops *ops,  loc_info *,
			void *src, void *dst, void *priv)
		= op->kernel;

	if (op->pre_process)
		op->pre_process(pix_ops, w, h, src, dst, priv);

	loc.w = w;
	loc.h = h;
	if (!op->boundary) {
		int s;

		for (loc.y = 0; loc.y < h; loc.y++) {
			s = loc.y * w;

			for (loc.x = 0; loc.x < w; loc.x++) {
				loc.index = s + loc.x;

				m_get_y(mapdata, loc.index, &inroi);
				if (inroi)
					m_kernel(pix_ops, &loc,
						src, dst, priv);
			}
		}
	} else {
		int s;

		for (loc.y = 0; loc.y < h; loc.y++) {
			loc.u = max(loc.y - 1, 0);
			loc.b = min(loc.y + 1, h - 1);
			loc.u_base = loc.u * w;
			loc.b_base = loc.b * w;

			s = loc.y * w;
			loc.row_base = s;

			//first element
			loc.index = s;
			m_get_y(mapdata, s, &inroi);
			if (inroi) {
				loc.x = 0;
				loc.l = 0;
				loc.r = 1;
				m_kernel_boundary(pix_ops, &loc,
					src, dst, priv);
			}

			//middle eles
			for (loc.x = 1; loc.x < w - 1; loc.x++) {
				loc.index = s + loc.x;
				m_get_y(mapdata, loc.index, &inroi);
				if (inroi) {
					loc.l = loc.x - 1;
					loc.r = loc.x + 1;
					m_kernel_boundary(pix_ops,
						&loc, src, dst, priv);
				}
			}

			//last ele
			loc.x = w - 1;
			loc.index = s + loc.x;
			m_get_y(mapdata, loc.index, &inroi);
			if (inroi) {
				loc.l = w - 2;
				loc.r = w - 1;
				m_kernel_boundary(pix_ops, &loc,
					src, dst, priv);
			}
		}
	}

	if (op->post_process)
		op->post_process(pix_ops, w, h, src, dst, priv);

	return 0;
}


int rtsarr_init(rts_array *arr, void *data, size_t ele_sz, size_t length)
{
	arr->data = data;
	arr->element_size = ele_sz;
	arr->length = length;

	return 0;
}

void rtsarr_swap(rts_array *arr, int i1, int i2, void *tmp)
{
	void *p1 = rtsarr_geti(arr, i1);
	void *p2 = rtsarr_geti(arr, i2);

	memcpy(tmp, p1, arr->element_size);
	memcpy(p1, p2, arr->element_size);
	memcpy(p2, tmp, arr->element_size);
}

#define MAX_HEAP_ELESIZE 64


void rts_build_heap(rts_array *arr, int (*cmp)(void *v1, void *v2))
{
	int index = arr->length - 1;
	int parent;
	void *pp, *pi;
	uint8_t tmp[MAX_HEAP_ELESIZE];

	while (index > 0) {
		parent = (index - 1) / 2;

		pp = rtsarr_geti(arr, parent);
		pi = rtsarr_geti(arr, index);

		if (cmp(pi, pp) > 0) {
			rtsarr_swap(arr, index, parent, tmp);
			index = parent;
		} else
			break;
	}
}

void rts_reform_heap(rts_array *arr, int (*cmp)(void *v1, void *v2))
{
	int root = 0;
	int child_l, child_r;
	uint8_t tmp[MAX_HEAP_ELESIZE];

	void *pr, *pcl, *pcr;

	while (root < (int)arr->length) {
		int flag_l = 0, flag_r = 0;

		child_l = 2 * root + 1;
		child_r = 2 * root + 2;
		pr = rtsarr_geti(arr, root);

		if (child_l < (int)rtsarr_length(arr)) {
			pcl = rtsarr_geti(arr, child_l);
			flag_l = cmp(pcl, pr);
		} else
			flag_l = -1;

		if (child_r < (int)rtsarr_length(arr)) {
			pcr = rtsarr_geti(arr, child_r);
			flag_r = cmp(pcr, pr);
		} else
			flag_r = -1;

		if (flag_l > 0 && flag_r > 0) {
			if (cmp(pcl, pcr) >= 0)
				goto swap_left;
			else
				goto swap_right;
		}

		if (flag_l > 0)
			goto swap_left;
		else if (flag_r > 0)
			goto swap_right;
		else
			break;

swap_left:
		rtsarr_swap(arr, child_l, root, tmp);
		root = child_l;
		continue;

swap_right:
		rtsarr_swap(arr, child_r, root, tmp);
		root = child_r;
		continue;
	}
	return;
}

int rts_heap_pop(rts_array *arr, int (*cmp)(void *v1, void *v2), void *value)
{
	int index = rtsarr_length(arr) - 1;

	if (rtsarr_length(arr) <= 0)
		return -1;
	if (value)
		memcpy(value, rtsarr_geti(arr, 0), arr->element_size);

	if (index > 0)
		rtsarr_seti(arr, 0, rtsarr_geti(arr, index));
	arr->length--;

	rts_reform_heap(arr, cmp);
	return 0;
}
