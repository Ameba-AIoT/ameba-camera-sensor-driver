/*
 * Realtek Semiconductor Corp.
 *
 * media/video/md2/rts_img_proc.h
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */
#ifndef __RTS_IMG_PROC_H__
#define __RTS_IMG_PROC_H__
#include <stddef.h>

enum IMG_PIX_FMT {
	PIX_FMT_1BPP = 0,
	PIX_FMT_Y_ONLY,
};

#define IBPP_CMD_GET_BYTE 0
#define IBPP_CMD_SET_BYTE 1


struct pix_ops {
	int fmt;
	void (*set_y)(void *img, uint32_t index, uint8_t y);
	void (*get_y)(void *img, uint32_t index, uint8_t *y);
	int (*exec_cmd)(void *img, int cmd, void *arg);

	int bits_per_pix;
	uint32_t (*get_img_buflen)(uint32_t img_size);
};

static inline void set_y(struct pix_ops *ops, void *img, uint32_t index, uint8_t y)
{
	ops->set_y(img, index, y);
}

static inline void get_y(struct pix_ops *ops, void *img, uint32_t index, uint8_t *y)
{
	ops->get_y(img, index, y);
}

static inline int exec_cmd(struct pix_ops *ops, void *img, int cmd, void *arg)
{
	return ops->exec_cmd(img, cmd, arg);
}

static inline uint32_t get_img_buflen(struct pix_ops *ops, uint32_t img_sz)
{
	return ops->get_img_buflen(img_sz);
}

struct pix_ops *find_pix_ops(int fmt);

enum {
	OP_dilate_4n = 0,
	OP_dilate_4n_to_yonly = 0,
	OP_dilate_8n,
	OP_erode_4n,
	OP_erode_8n,
	OP_label_cc_4n,
	OP_label_cc_8n,
	OP_get_cc_map,
	OP_to_fmt_yonly,
	OP_to_fmt_1bpp,
	OP_to_1bpp_bmp,
	OP_from_1bpp_bmp,
	OP_filter_roi,
	OP_filter_roi_to_yonly,
};

struct Ibpp_bmp_attr {
	//only need to set width & heigth
	int width;
	int height; //set height < 0 to reverse direction

	int row_size;
	int data_offset;
	//get filesize here
	int filesize;

	int flag_quick;
	int flag_dir_reverse;
};

struct ROI {
	int width, height;
	struct {
		int x, y;
	} begin, end;
};

struct ROI_map {
	int width, height;
	uint32_t length;
	struct pix_ops *map_ops;
	void *map;
};

#define CC_FLAG_PASS		(1)
#define CC_FLAG_FILTERED	(1 << 1) //flag to filter out when get_cc_map
#define CC_FLAG_ROOT		(1 << 2) //flag to get in get max cc

struct CC {
	uint16_t u, b, l, r;
	uint32_t pixel_cnt;
	uint32_t flags : 8;
	uint32_t parent_label : 24;
};

struct CC_context {
	int cc_index;
	struct CC *cc;
};

int img_run_roi_with_priv(struct pix_ops *pixops, int opscode, struct ROI *roi,
		void *src, void *dst, void *priv);

static inline int img_run_roi(struct pix_ops *pix_ops, int opcode, struct ROI *roi,
		void *src, void *dst)
{
	return img_run_roi_with_priv(pix_ops, opcode, roi, src, dst, NULL);
}

int img_run_roimap_with_priv(struct pix_ops *pix_ops, int opcode,
			struct ROI_map *roi, void *src, void *dst, void *priv);

static inline int img_run_roimap(struct pix_ops *pix_ops, int opcode,
			struct ROI_map *map, void *src, void *dst)
{
	return img_run_roimap_with_priv(pix_ops, opcode, map, src, dst, NULL);
}

#ifndef max
  #define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
  #define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef clip
  #define clip(x, a, b) max((b), min((x), (a)))
#endif

#define ALIGNN(len, n) ((len + n - 1) / n * n);


/*
 *		rts_pprc
 */


struct rts_pprc_attr {
	enum IMG_PIX_FMT fmt;
	enum IMG_PIX_FMT roi_fmt;
	uint32_t width;
	uint32_t height;
};

struct rts_pprc_instance {
	struct pix_ops *ops, *bitops;
	struct ROI_map roi;
	struct ROI _roi;
	struct CC_context ccon;
	void *tmp_img[2];
	void *label_img;

	void *data;
};

struct rts_pprc_filter {
	int enable_cc_info;
	int enable_cc_filter;

	uint32_t nr_cc_thd;
	float max_ar;
	float min_ar;
	float cc_ratio;
};

int rts_pprc_init(struct rts_pprc_attr *attr,
		struct rts_pprc_instance *inst);
int rts_pprc_run(struct rts_pprc_instance *pp,
			struct rts_pprc_filter *filter,
			void *src, void *dst);
void rts_pprc_release(struct rts_pprc_instance *pp);


/*
 *		rts_algs
 */

typedef struct __rts_array {
	size_t element_size;
	size_t length;
	void *data;
} rts_array;

static inline void rtsarr_seti(rts_array *arr, int i, void *v) {
	memcpy((void *)((uint32_t)arr->data + i * arr->element_size), v, arr->element_size);
}

static inline void *rtsarr_geti(rts_array *arr, int i) {
	return ((void *)((uint32_t)arr->data + i * arr->element_size));
}

static inline size_t rtsarr_length(rts_array *arr) {
	return arr->length;
}

void rtsarr_swap(rts_array *arr, int i1, int i2, void *tmp);
int rtsarr_init(rts_array *arr, void *data, size_t ele_sz, size_t length);

void rts_build_heap(rts_array *arr, int (*cmp)(void *v1, void *v2));
void rts_reform_heap(rts_array *arr, int (*cmp)(void *v1, void *v2));
int rts_heap_pop(rts_array *arr, int (*cmp)(void *v1, void *v2), void *value);

#endif
