/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include <pb_encode.h>
#include <isp_top.h>
#include <isp_statis.pb.h>
#include <isp_shm.h>
#include <isp_core.h>
#include <isp_statis.h>
#include <isp_notify.h>
#include <isp_mod.h>
#include <isp_mod_rawstat.h>
#include <isp_mod_awb.h>
#include <isp_mod_ae.h>
#include <isp_mod_af.h>
#include <isp_mod_ystat.h>
#include <isp_mod_statis.h>
#include <isp_mod_sensor.h>
#include <isp_hw_statis.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_STATIS
#define ISP_AMEBA_STATIS_TYPE 1
char AE_STATIS_SHM_NAME[]	 = "/isp_statis_ae.shm";
char AWB_STATIS_SHM_NAME[] = "/isp_statis_awb.shm";
char AF_STATIS_SHM_NAME[] = "/isp_statis_af.shm";
char TUNING_STATIS_SHM_NAME[] = "/isp_statis_tuning.shm";

struct statis_info {
	struct isp_mod_rawstat_stat_info raw;
	struct isp_mod_awb_stat_info awb;
	struct isp_mod_ae_stat_info ae;
	struct isp_mod_af_stat_info af;
	struct isp_mod_ystat_stat_info y;
};

struct statis_raw_buf_size {
	uint16_t rgby_size;
	uint16_t rgbg_size;
	uint16_t pixels_size;
};

struct statis_awb_buf_size {
	uint16_t rgby_size;
	uint16_t rgbg_size;
	uint16_t pixels_size;
};

struct statis_ae_hdr_buf_size {
	uint16_t win_size;
	uint16_t hist_size;
};

struct statis_ae_buf_size {
	uint16_t win_size;
	uint16_t hist_size;
	struct statis_ae_hdr_buf_size hdr[RTS_ISP_HDR_CHAN_MAX];
};

struct statis_af_buf_size {
	uint16_t win_size;
};

struct statis_y_buf_size {
	uint16_t win_size;
	uint16_t hist_size;
};

struct statis_buf_size {
	struct statis_raw_buf_size raw;
	struct statis_awb_buf_size awb;
	struct statis_ae_buf_size ae;
	struct statis_af_buf_size af;
	struct statis_y_buf_size y;
};

struct isp_mod_statis {
	struct isp_mod mod;
	struct statis_buf_size size;
	struct isp_statis_buf_offset offset;
	const struct isp_hw_statis_ops *hw_ops;

	struct isp_statis *statis_man;
	const struct rts_isp_statis *all;

	struct isp_shm ae_shm;
	struct isp_shm awb_shm;
	struct isp_shm af_shm;
	struct isp_shm tuning_shm;
	isp_statis_t tuning_stat;

	enum rts_isp_sensor_hdr_mode hdr_mode;


	int initialized:1;
};

static int statis_get_all_info(struct isp_mod *mod, struct statis_info *info)
{
	int ret;

	ret = isp_mod_sibling_get_info(mod, MOD_RAWSTAT, RAWSTAT_INFO_STATIS,
				       &info->raw, sizeof(info->raw));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_AWB, AWB_INFO_STATIS,
				       &info->awb, sizeof(info->awb));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_STATIS,
				       &info->ae, sizeof(info->ae));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_AF, AF_INFO_STATIS,
				       &info->af, sizeof(info->af));
	if (ret)
		return ret;
	ret = isp_mod_sibling_get_info(mod, MOD_YSTAT, YSTAT_INFO_STATIS,
				       &info->y, sizeof(info->y));
	return ret;

}

static inline int statis_get_size(int num, int size)
{
	return num * size;
}

static int statis_calc_buf_size(struct statis_buf_size *size,
				const struct statis_info *info)
{
	const struct isp_mod_rawstat_stat_info *raw = &info->raw;
	const struct isp_mod_awb_stat_info *awb = &info->awb;
	const struct isp_mod_ae_stat_info *ae = &info->ae;
	const struct isp_mod_af_stat_info *af = &info->af;
	const struct isp_mod_ystat_stat_info *y = &info->y;
	uint16_t win_num;
	int i;

	win_num = raw->info.win.cols * raw->info.win.rows;
	size->raw.rgby_size = statis_get_size(win_num, raw->rgby_size);
	size->raw.rgbg_size = statis_get_size(win_num, raw->rgbg_size);
	size->raw.pixels_size = statis_get_size(win_num, raw->pixels_size);

	win_num = awb->info.win.cols * awb->info.win.rows;
	size->awb.rgby_size = statis_get_size(win_num, awb->rgby_size);
	size->awb.rgbg_size = statis_get_size(win_num, awb->rgbg_size);
	size->awb.pixels_size = statis_get_size(win_num, awb->pixels_size);

	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		win_num = ae->info.hdr[i].win.cols * ae->info.hdr[i].win.rows;
		size->ae.hdr[i].win_size =
			statis_get_size(win_num, ae->hdr[i].win_mean_size);
		size->ae.hdr[i].hist_size =
			statis_get_size(ae->info.hdr[i].hist_bins,
					ae->hdr[i].hist_bin_size);
	}

	win_num = ae->info.win.cols * ae->info.win.rows;
	size->ae.win_size = statis_get_size(win_num, ae->win_mean_size);
	size->ae.hist_size = statis_get_size(ae->info.hist_bins,
					     ae->hist_bin_size);

	win_num = af->info.win.cols * af->info.win.rows;
	size->af.win_size = statis_get_size(win_num, af->win_edge_size);

	win_num = y->info.win.cols * y->info.win.rows;
	size->y.win_size = statis_get_size(win_num, y->win_mean_size);
	size->y.hist_size = statis_get_size(y->info.hist_bins,
					    y->hist_bin_size);

	return RTS_ISP_OK;
}

#define set_offset(_offset, _size, _pos) ({ _offset = _pos; _pos += _size; })
#define set_size(_size, _begin, _end) ({ _size = _end - _begin; })

static int statis_calc_buf_offset_size(struct isp_mod_statis *statis)
{
	int i;
	uint32_t pos;
	struct statis_buf_size *size = &statis->size;
	struct isp_statis_buf_offset *offset = &statis->offset;

	pos = 0;
	set_offset(offset->raw.offset, 0, pos);
	set_offset(offset->raw.r_offset, size->raw.rgby_size, pos);
	set_offset(offset->raw.gr_offset, size->raw.rgby_size, pos);
	set_offset(offset->raw.gb_offset, size->raw.rgby_size, pos);
	set_offset(offset->raw.b_offset, size->raw.rgby_size, pos);
	set_offset(offset->raw.y_offset, size->raw.rgby_size, pos);
	set_offset(offset->raw.rg_offset, size->raw.rgbg_size, pos);
	set_offset(offset->raw.bg_offset, size->raw.rgbg_size, pos);
	set_offset(offset->raw.pixels_offset, size->raw.pixels_size, pos);
	set_size(offset->raw.size, offset->raw.offset, pos);

#if ISP_AMEBA_STATIS_TYPE
	set_offset(offset->ae.hdr_offset, 0, pos);
	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		set_offset(offset->ae.hdr[i].hist_offset,
			   size->ae.hdr[i].hist_size, pos);
		set_offset(offset->ae.hdr[i].y_offset,
			   size->ae.hdr[i].win_size, pos);
	}
	set_size(offset->ae.hdr_size, offset->ae.hdr_offset, pos);
#endif

	set_offset(offset->awb.offset, 0, pos);
	set_offset(offset->awb.r_offset, size->awb.rgby_size, pos);
	set_offset(offset->awb.g_offset, size->awb.rgby_size, pos);
	set_offset(offset->awb.b_offset, size->awb.rgby_size, pos);
	set_offset(offset->awb.y_offset, size->awb.rgby_size, pos);
	set_offset(offset->awb.rg_offset, size->awb.rgbg_size, pos);
	set_offset(offset->awb.bg_offset, size->awb.rgbg_size, pos);
	set_offset(offset->awb.pixels_offset, size->awb.pixels_size, pos);
	set_size(offset->awb.size, offset->awb.offset, pos);

	set_offset(offset->ae.offset, 0, pos);
#if ISP_AMEBA_STATIS_TYPE
	set_offset(offset->ae.hist_offset, size->ae.hist_size, pos);
	set_offset(offset->ae.y_offset, size->ae.win_size, pos);
#else
	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		set_offset(offset->ae.hdr[i].hist_offset,
			   size->ae.hdr[i].hist_size, pos);
		set_offset(offset->ae.hdr[i].y_offset,
			   size->ae.hdr[i].win_size, pos);
	}
	set_offset(offset->ae.hist_offset, size->ae.hist_size, pos);
	set_offset(offset->ae.y_offset, size->ae.win_size, pos);
#endif
	set_size(offset->ae.size, offset->ae.offset, pos);

#if ISP_AMEBA_STATIS_TYPE
	//offset->ae.size = offset->ae.size + offset->ae.hdr_size;
#endif

	set_offset(offset->af.offset, 0, pos);
	set_offset(offset->af.edge_offset, size->af.win_size, pos);
	set_size(offset->af.size, offset->af.offset, pos);

	set_offset(offset->y.offset, 0, pos);
	set_offset(offset->y.hist_offset, size->y.hist_size, pos);
	set_offset(offset->y.y_offset, size->y.win_size, pos);
	set_size(offset->y.size, offset->y.offset, pos);

	set_size(offset->size, 0, pos);

	return RTS_ISP_OK;
}

static void isp_shm_mutex_cleanup(struct isp_shm *shm,
				  int size, const char *name)
{
	osMutexId_t *lock;

	if (!shm)
		return;
	lock = (osMutexId_t*)((uint32_t)shm->buf + size);
	//osMutexDelete(*lock);
	if (*lock) {
		vSemaphoreDelete(*lock);
		*lock = NULL;
	}
	isp_shm_cleanup(shm, size, name);
}

static int isp_shm_mutex_init(struct isp_shm *shm, int size, const char *name)
{
	int ret;
	osMutexId_t *lock;

	ret = isp_shm_init(shm, size + sizeof(osMutexId_t), name);
	if (ret)
		return ret;

	lock = (osMutexId_t*)((uint32_t)shm->buf + size);

	*lock = xSemaphoreCreateMutex();
	if ( !*lock ) {
		printf("%s shm mutex alloc fail\n", name);
		ret = RTS_ISP_ENOMEM;
	}

	return ret;
}

static void statis_all_shm_cleanup(struct isp_mod_statis *statis)
{
	isp_shm_mutex_cleanup(&statis->ae_shm, statis->offset.ae.size,
			AE_STATIS_SHM_NAME);
	isp_shm_mutex_cleanup(&statis->awb_shm, statis->offset.awb.size,
			AWB_STATIS_SHM_NAME);
	isp_shm_mutex_cleanup(&statis->af_shm, statis->offset.af.size,
			AF_STATIS_SHM_NAME);
	isp_shm_cleanup(&statis->tuning_shm, TUNING_STATIS_SHM_SIZE,
			TUNING_STATIS_SHM_NAME);
}

static int statis_all_shm_init(struct isp_mod_statis *statis)
{
	int ret;

	ret = isp_shm_mutex_init(&statis->ae_shm, statis->offset.ae.size,
			   AE_STATIS_SHM_NAME);
	if (ret)
		goto out;
	ret = isp_shm_mutex_init(&statis->awb_shm, statis->offset.awb.size,
			   AWB_STATIS_SHM_NAME);
	if (ret)
		goto out;
	ret = isp_shm_mutex_init(&statis->af_shm, statis->offset.af.size,
			   AF_STATIS_SHM_NAME);
	if (ret)
		goto out;
	ret = isp_shm_init(&statis->tuning_shm, TUNING_STATIS_SHM_SIZE,
			   TUNING_STATIS_SHM_NAME);
	if (ret)
		goto out;
out:
	if (ret)
		statis_all_shm_cleanup(statis);
	return ret;
}

static bool statis_enc_u32(pb_ostream_t *stream,
			   const pb_field_t *field, void *const *arg)
{
	if (!pb_encode_tag_for_field(stream, field))
		return RTS_ISP_FALSE;
	return pb_encode_fixed32(stream, *arg);
}

static bool statis_enc_u16_array(pb_ostream_t *stream, const pb_field_t *field,
				 void *const *arg, int size)
{
	int i;
	uint16_t *arr;

	if (size <= 0)
		return RTS_ISP_FALSE;

	arr = *arg;
	if (!arr)
		PB_RETURN_ERROR(stream, "arg is nil");

	if (!pb_encode_tag(stream, PB_WT_STRING, field->tag))
		return RTS_ISP_FALSE;
	if (!pb_encode_varint(stream, 4 * size))
		return RTS_ISP_FALSE;
	for (i = 0; i < size; i++) {
		uint32_t val = arr[i];

		if (!pb_encode_fixed32(stream, &val))
			return RTS_ISP_FALSE;
	}
	return RTS_ISP_TRUE;
}

static bool statis_enc_u16_array25(pb_ostream_t *stream,
				   const pb_field_t *field, void *const *arg)
{
	return statis_enc_u16_array(stream, field, arg, 25);
}

static bool statis_enc_u16_array256(pb_ostream_t *stream,
				    const pb_field_t *field, void *const *arg)
{
	return statis_enc_u16_array(stream, field, arg, 256);
}

static bool statis_enc_u32_array(pb_ostream_t *stream, const pb_field_t *field,
				 void *const *arg, int size)
{
	int i;
	uint32_t *arr;

	if (size <= 0)
		return RTS_ISP_FALSE;

	arr = *arg;
	if (!arr)
		PB_RETURN_ERROR(stream, "arg is nil");

	if (!pb_encode_tag(stream, PB_WT_STRING, field->tag))
		return RTS_ISP_FALSE;
	if (!pb_encode_varint(stream, 4 * size))
		return RTS_ISP_FALSE;
	for (i = 0; i < size; i++) {
		if (!pb_encode_fixed32(stream, &arr[i]))
			return RTS_ISP_FALSE;
	}
	return RTS_ISP_TRUE;
}

static bool statis_enc_u32_array6(pb_ostream_t *stream,
				  const pb_field_t *field, void *const *arg)
{
	return statis_enc_u32_array(stream, field, arg, 6);
}

static bool statis_enc_u32_array25(pb_ostream_t *stream,
				   const pb_field_t *field, void *const *arg)
{
	return statis_enc_u32_array(stream, field, arg, 25);
}

static bool statis_enc_u32_array256(pb_ostream_t *stream,
				    const pb_field_t *field, void *const *arg)
{
	return statis_enc_u32_array(stream, field, arg, 256);
}

static void statis_tuning_raw_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->raw.r_mean.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.r_mean.arg = (void *)statis->all->raw.r_mean;
	tuning_stat->raw.gr_mean.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.gr_mean.arg = (void *)statis->all->raw.gr_mean;
	tuning_stat->raw.gb_mean.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.gb_mean.arg = (void *)statis->all->raw.gb_mean;
	tuning_stat->raw.b_mean.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.b_mean.arg = (void *)statis->all->raw.b_mean;
	tuning_stat->raw.y_mean.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.y_mean.arg = (void *)statis->all->raw.y_mean;
	tuning_stat->raw.rg.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.rg.arg = (void *)statis->all->raw.rg;
	tuning_stat->raw.bg.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.bg.arg = (void *)statis->all->raw.bg;
	tuning_stat->raw.pixels.funcs.encode = statis_enc_u16_array25;
	tuning_stat->raw.pixels.arg = (void *)statis->all->raw.pixels;
}

static void statis_tuning_awb_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->awb.r_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.r_mean.arg = (void *)statis->all->awb.r_mean;
	tuning_stat->awb.g_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.g_mean.arg = (void *)statis->all->awb.g_mean;
	tuning_stat->awb.b_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.b_mean.arg = (void *)statis->all->awb.b_mean;
	tuning_stat->awb.y_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.y_mean.arg = (void *)statis->all->awb.y_mean;
	tuning_stat->awb.rg.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.rg.arg = (void *)statis->all->awb.rg;
	tuning_stat->awb.bg.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.bg.arg = (void *)statis->all->awb.bg;
	tuning_stat->awb.pixels.funcs.encode = statis_enc_u16_array256;
	tuning_stat->awb.pixels.arg = (void *)statis->all->awb.pixels;
	tuning_stat->awb.illum_white_pixels.funcs.encode =
		statis_enc_u32_array6;
	tuning_stat->awb.illum_white_pixels.arg =
		(void *)statis->all->awb.illum_white_pixels;
	tuning_stat->awb.fine_r_sum.funcs.encode = statis_enc_u32;
	tuning_stat->awb.fine_r_sum.arg = (void *)&statis->all->awb.fine_r_sum;
	tuning_stat->awb.fine_g_sum.funcs.encode = statis_enc_u32;
	tuning_stat->awb.fine_g_sum.arg = (void *)&statis->all->awb.fine_g_sum;
	tuning_stat->awb.fine_b_sum.funcs.encode = statis_enc_u32;
	tuning_stat->awb.fine_b_sum.arg = (void *)&statis->all->awb.fine_b_sum;
	tuning_stat->awb.fine_white_pixels.funcs.encode = statis_enc_u32;
	tuning_stat->awb.fine_white_pixels.arg =
		(void *)&statis->all->awb.fine_white_pixels;
}

static void statis_tuning_ae_callback_init(struct isp_mod_statis *statis)
{
	int i;
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->ae.y_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->ae.y_mean.arg = (void *)statis->all->ae.y_mean;
	tuning_stat->ae.hist.funcs.encode = statis_enc_u32_array256;
	tuning_stat->ae.hist.arg = (void *)statis->all->ae.hist;
		tuning_stat->ae.hdr[0].y_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->ae.hdr[0].y_mean.arg =
		(void *)statis->all->ae.hdr[0].y_mean;
	tuning_stat->ae.hdr[0].hist.funcs.encode = statis_enc_u32_array256;
	tuning_stat->ae.hdr[0].hist.arg = (void *)statis->all->ae.hdr[0].hist;
	tuning_stat->ae.hdr[1].y_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->ae.hdr[1].y_mean.arg =
		(void *)statis->all->ae.hdr[1].y_mean;
	tuning_stat->ae.hdr[1].hist.funcs.encode = statis_enc_u32_array256;
	tuning_stat->ae.hdr[1].hist.arg = (void *)statis->all->ae.hdr[1].hist;
}

static void statis_tuning_af_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->af.edges.funcs.encode = statis_enc_u32_array25;
	tuning_stat->af.edges.arg = (void *)statis->all->af.edges;
	tuning_stat->af.num0.funcs.encode = statis_enc_u32;
	tuning_stat->af.num0.arg = (void *)&statis->all->af.num0;
	tuning_stat->af.sum0.funcs.encode = statis_enc_u32;
	tuning_stat->af.sum0.arg = (void *)&statis->all->af.sum0;
	tuning_stat->af.num1.funcs.encode = statis_enc_u32;
	tuning_stat->af.num1.arg = (void *)&statis->all->af.num1;
	tuning_stat->af.sum1.funcs.encode = statis_enc_u32;
	tuning_stat->af.sum1.arg = (void *)&statis->all->af.sum1;
}

static void statis_tuning_flick_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->flick.valid.funcs.encode = statis_enc_u32;
	tuning_stat->flick.valid.arg = (void *)&statis->all->flick.valid;
	tuning_stat->flick.fft_sum_2_9.funcs.encode = statis_enc_u32;
	tuning_stat->flick.fft_sum_2_9.arg =
		(void *)&statis->all->flick.fft_sum_2_9;
	tuning_stat->flick.fft_sum_2_127.funcs.encode = statis_enc_u32;
	tuning_stat->flick.fft_sum_2_127.arg =
		(void *)&statis->all->flick.fft_sum_2_127;
}

static void statis_tuning_y_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->y.y_mean.funcs.encode = statis_enc_u16_array256;
	tuning_stat->y.y_mean.arg = (void *)statis->all->y.y_mean;
	tuning_stat->y.hist.funcs.encode = statis_enc_u32_array256;
	tuning_stat->y.hist.arg = (void *)statis->all->y.hist;
}

static void statis_tuning_callback_init(struct isp_mod_statis *statis)
{
	isp_statis_t *tuning_stat = &statis->tuning_stat;

	tuning_stat->frame_count.funcs.encode = statis_enc_u32;
	tuning_stat->frame_count.arg = (void *)&statis->all->raw.frame_count;

	statis_tuning_raw_callback_init(statis);
	statis_tuning_awb_callback_init(statis);
	statis_tuning_ae_callback_init(statis);
	statis_tuning_af_callback_init(statis);
	statis_tuning_flick_callback_init(statis);
	statis_tuning_y_callback_init(statis);
}

static int mod_statis_info_buf_offset(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);
	struct isp_statis_buf_offset *offset = data;

	*offset = statis->offset;

	return RTS_ISP_OK;
}

static int mod_statis_info_ae_stat(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);
	struct rts_isp_ae_statis *ae_stat;
	struct isp_statis_ae_buf_offset *offset;

	if (!statis->all)
		return -RTS_ISP_ENOTREADY;

	ae_stat = data;
	offset = &statis->offset.ae;

	ae_stat->frame_count = statis->all->ae.frame_count;
	isp_memcpy(statis->ae_shm.buf,
			(void *)((uint32_t)statis->all->buf + offset->offset), offset->size);

	return RTS_ISP_OK;
}

static int mod_statis_info_awb_stat(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);
	struct rts_isp_awb_statis *awb_stat;
	struct isp_statis_awb_buf_offset *offset;

	if (!statis->all)
		return -RTS_ISP_ENOTREADY;

	awb_stat = data;
	offset = &statis->offset.awb;

	awb_stat->frame_count = statis->all->awb.frame_count;
	awb_stat->fine_r_sum = statis->all->awb.fine_r_sum;
	awb_stat->fine_g_sum = statis->all->awb.fine_g_sum;
	awb_stat->fine_b_sum = statis->all->awb.fine_b_sum;
	awb_stat->fine_white_pixels = statis->all->awb.fine_white_pixels;
	isp_memcpy(awb_stat->illum_white_pixels,
		   statis->all->awb.illum_white_pixels,
		   sizeof(statis->all->awb.illum_white_pixels));
	isp_memcpy(statis->awb_shm.buf,
			(void *)((uint32_t)statis->all->buf + offset->offset), offset->size);

	return RTS_ISP_OK;
}

static int mod_statis_info_af_stat(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);
	struct rts_isp_af_statis *af_stat;
	struct isp_statis_af_buf_offset *offset;

	if (!statis->all)
		return -RTS_ISP_ENOTREADY;

	af_stat = data;
	offset = &statis->offset.af;

	af_stat->frame_count = statis->all->af.frame_count;
	af_stat->num0 = statis->all->af.num0;
	af_stat->sum0 = statis->all->af.sum0;
	af_stat->num1 = statis->all->af.num1;
	af_stat->sum1 = statis->all->af.sum1;
	isp_memcpy(statis->af_shm.buf,
			(void *)((uint32_t)statis->all->buf + offset->offset), offset->size);

	return RTS_ISP_OK;
}

static int mod_statis_info_tuning_stat(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);
	struct rts_isp_tuning_statis *tuning_stat = data;
	pb_ostream_t stream;
	const pb_msgdesc_t *fields;
	const void *src_struct;

	if (tuning_stat->type < RTS_ISP_TUNING_STATIS_ALL ||
	    tuning_stat->type >= __RTS_ISP_TUNING_STATIS_NUM ||
	    tuning_stat->len != TUNING_STATIS_SHM_SIZE)
		return -RTS_ISP_EINVAL;

	if (!statis->all)
		return -RTS_ISP_ENOTREADY;

	stream = pb_ostream_from_buffer(statis->tuning_shm.buf,
					tuning_stat->len);
	switch (tuning_stat->type) {
	case RTS_ISP_TUNING_STATIS_ALL:
		fields = isp_statis_t_fields;
		src_struct = &statis->tuning_stat;
		statis_tuning_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_RAW:
		fields = isp_statis_raw_t_fields;
		src_struct = &statis->tuning_stat.raw;
		statis_tuning_raw_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_AWB:
		fields = isp_statis_awb_t_fields;
		src_struct = &statis->tuning_stat.awb;
		statis_tuning_awb_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_AE:
		fields = isp_statis_ae_t_fields;
		src_struct = &statis->tuning_stat.ae;
		statis_tuning_ae_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_AF:
		fields = isp_statis_af_t_fields;
		src_struct = &statis->tuning_stat.af;
		statis_tuning_af_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_FLICK:
		fields = isp_statis_flick_t_fields;
		src_struct = &statis->tuning_stat.flick;
		statis_tuning_flick_callback_init(statis);
		break;
	case RTS_ISP_TUNING_STATIS_Y:
		fields = isp_statis_y_t_fields;
		src_struct = &statis->tuning_stat.y;
		statis_tuning_y_callback_init(statis);
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	if (!pb_encode(&stream, fields, src_struct)) {
		isp_error("encode statis error: %s\n", PB_GET_ERROR(&stream));
		return -RTS_ISP_EPROTOBUF;
	}

	set_const_var(tuning_stat->len, stream.bytes_written);

	return RTS_ISP_OK;
}

static struct isp_mod_action_info statis_info_actions[] = {
	ISP_MOD_ACTION(STATIS_INFO_BUF_OFFSET, mod_statis_info_buf_offset),
	ISP_MOD_ACTION(STATIS_INFO_AE_STAT, mod_statis_info_ae_stat),
	ISP_MOD_ACTION(STATIS_INFO_AWB_STAT, mod_statis_info_awb_stat),
	ISP_MOD_ACTION(STATIS_INFO_AF_STAT, mod_statis_info_af_stat),
	ISP_MOD_ACTION(STATIS_INFO_TUNING_STAT, mod_statis_info_tuning_stat),
};

extern int iq_dynamic_run(void);
static uint32_t dynamic_iq_ref_cnt = 0;
static uint32_t dynamic_iq_period = 3;

// we still have to do first statis done for hw estimation
// after that, we disable statis when output_task receive 1st frame

static int mod_statis_statis_done(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);

	isp_statis_unref(statis->statis_man, statis->all);
	isp_statis_get_all(statis->statis_man, &statis->all);
	isp_statis_ref(statis->statis_man, statis->all);
	//isp_info("%s \r\n",__func__);
	if ((dynamic_iq_ref_cnt%dynamic_iq_period) == 0 ) {
		// mod_iq_start_pre already call iq_dynamic_notify
		// do not call iq_dynamic_run when verify path to ensure the consistency of IQ
		if (!hal_isp_is_verify_path_on())
			iq_dynamic_run();
	}
	dynamic_iq_ref_cnt++;

	return RTS_ISP_OK;
}

static int mod_statis_start_post(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_statis *statis = get_mod(mod, statis);

	if (statis->initialized)
		return RTS_ISP_OK;
	ret = isp_statis_init(statis->statis_man, &statis->offset);
	if (ret)
		return ret;
	ret = statis->hw_ops->enable(mod->owner_id, RTS_ISP_TRUE,
				     statis->hdr_mode);
	if (ret) {
		isp_statis_cleanup(statis->statis_man);
		isp_driver_cleanup_statis();
		return ret;
	}
	statis->initialized = RTS_ISP_TRUE;
	return RTS_ISP_OK;
}

static int mod_statis_stop_pre(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);

	isp_statis_unref(statis->statis_man, statis->all);
	statis->all = NULL;

	statis->hw_ops->enable(mod->owner_id, RTS_ISP_FALSE, statis->hdr_mode);
	//isp_statis_cleanup(statis->statis_man);
	statis->initialized = RTS_ISP_FALSE;

	//isp_error("Cleanup!\n");

	return RTS_ISP_OK;
}

static int mod_statis_stop_post(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);

	isp_statis_cleanup(statis->statis_man);

	return RTS_ISP_OK;
}

static int mod_statis_mode_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_statis *statis = get_mod(mod, statis);
	const struct isp_sensor_mode mode;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE, &mode,
				       sizeof(mode));
	if (ret)
		return ret;
	statis->hdr_mode = mode.hdr;

	return RTS_ISP_OK;
}

static int mod_statis_stop(struct isp_mod *mod, void *data)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);

	isp_statis_unref(statis->statis_man, statis->all);
	statis->all = NULL;
	return RTS_ISP_OK;
}

static struct isp_mod_action_info statis_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_statis_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_START_POST, mod_statis_start_post),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_PRE, mod_statis_stop_pre),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STOP_POST, mod_statis_stop_post),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_HDR_MODE_CHANGE, mod_statis_mode_change),
};

static int isp_mod_statis_init(struct isp_mod *mod)
{
	int ret;
	struct statis_info info;
	struct isp_mod_statis *statis;

	statis = get_mod(mod, statis);
	statis->hw_ops = isp_hw_statis_get_ops();
	if (statis->hw_ops == NULL) {
		isp_error("get statis hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}
	statis->statis_man = isp_core_get_statis(
			isp_top_get_core(mod->owner_id));
	if (!statis->statis_man) {
		ret = -RTS_ISP_ENOTREADY;
		goto err;
	}
	ret = statis_get_all_info(mod, &info);
	if (ret)
		goto err;
	ret = statis_calc_buf_size(&statis->size, &info);
	if (ret)
		goto err;
	ret = statis_calc_buf_offset_size(statis);
	if (ret)
		goto err;
	ret = statis_all_shm_init(statis);
	if (ret)
		goto err;


	return RTS_ISP_OK;
err:
	statis_all_shm_cleanup(statis);
	return ret;
}

static int isp_mod_statis_cleanup(struct isp_mod *mod)
{
	struct isp_mod_statis *statis = get_mod(mod, statis);

	statis_all_shm_cleanup(statis);
	return RTS_ISP_OK;
}

static struct isp_mod_statis statis;

int isp_register_mod_statis(void)
{
	memset(&statis, 0, sizeof(statis));
	statis.mod.id = MOD_STATIS;
	statis.mod.name = "statis";
	statis.mod.notify_bits = (ISP_STATIS_DONE_BIT | ISP_HDR_MODE_CHANGE_BIT |
				  ISP_START_POST_BIT | ISP_STOP_PRE_BIT | ISP_STOP_POST_BIT);
	statis.mod.init = isp_mod_statis_init;
	statis.mod.cleanup = isp_mod_statis_cleanup;
	statis.mod.info_actions = statis_info_actions;
	statis.mod.info_actions_num = ARRAY_SIZE(statis_info_actions);
	statis.mod.notify_actions = statis_notify_actions;
	statis.mod.notify_actions_num = ARRAY_SIZE(statis_notify_actions);
	return isp_mod_register(&statis.mod);
}

void isp_unregister_mod_statis(void)
{
	isp_mod_unregister(&statis.mod);
}

