/*
 * Realtek Semiconductor Corp.
 *
 * media/video/md2/rtsav_md2.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <rts_isp_md.h>
#include <rtsc.h>

#define RTS_LOG_TAG "md2"
#include <rtscamkit.h>
#include "cmsis_os2.h"
#include <rtsvideo.h>
#include "rtx_mutex.h"

#include "rts_img_proc.h"
#include "isp_log.h"
#define RC(x) RTS_RETURN(RTS_E_##x)
#define MD2_OBJ_NAME "rtsmd2.obj"
#define MD2_RES_BUF_CNT (2)
#define MD_IN(inst) xSemaphoreTake(inst->lock, ISP_SEM_TIMEOUT)
#define MD_OUT(inst) xSemaphoreGive(inst->lock)

#define RTS_MD2_MDIN_MAX_SCALE ((1 << 4) - 1)
#define RTS_MD2_MDOUT_MAX_SCALE ((1 << 3) - 1)

struct rts_md2_instance {
	void *hw;

	int sensitivity;
	int train_enable;
	uint32_t scene_change_thd;

	struct rts_isp_md_attr isp_md_attr;
	struct rts_isp_md_extra_attr isp_md_eattr;
	struct rtsc_dma_buffer hist;
	struct rtsc_dma_buffer res[MD2_RES_BUF_CNT];
	uint32_t res_index;
	uint32_t hist_sz, res_sz;

	struct rts_pprc_attr pprc_attr;
	struct rts_pprc_filter pprc_filter;
	struct rts_pprc_instance pprc;

	void *res_buf;
	uint32_t res_buf_len;
	void *roi_buf;
	uint32_t roi_buf_len;
	void *inst_buf;
	uint32_t total_buf_len;

	struct rts_md2_attr attr;
	struct rts_md2_ctrl ctrl;

	int initialized;
	osMutexId_t lock;
};


static struct rts_md2_instance *__to_md2_instance(
		struct rts_md2_ctrl *ctrl)
{
	struct rts_md2_instance *inst =
		container_of(ctrl, struct rts_md2_instance, ctrl);

	return inst;
}


static void __release_md2(struct rts_md2_instance *inst)
{
	if (!inst)
		return;

	if (MD_IN(inst) != pdTRUE) {
		isp_error("__release_md2 wait inst->lock timeout\n\r");
		return;
	}

	inst->initialized = 0;
	/*release hw related*/
	if (inst->hw) {
		rts_isp_md_enable(inst->hw, 0);
		RTS_SAFE_RELEASE(inst->hw, rts_isp_md_release);
	}
	rts_isp_md_free_dma(&inst->hist);
	for (int i = 0; i < MD2_RES_BUF_CNT; i++)
		rts_isp_md_free_dma(&inst->res[i]);

	/*release pprc*/
	rts_pprc_release(&inst->pprc);

	/*release all*/
	RTS_SAFE_DELETE(inst->inst_buf);

	MD_OUT(inst);
	if(inst->lock != NULL) {
		vSemaphoreDelete(inst->lock);
		inst->lock = NULL;
	}
//	osMutexDelete(inst->lock);
	RTS_SAFE_DELETE(inst);
}


static int __factorization(int s, int *x, int *y)
{
	int rem, r;
	int i;

	for (i = 2; i <= RTS_MD2_MDOUT_MAX_SCALE; i++) {
		rem = s % i;
		r = s / i;
		if ((!rem) && r <= RTS_MD2_MDIN_MAX_SCALE) {
			*x = r;
			*y = i;
			return 0;
		}
	}
	return -1;
}


static int __check_sample_scale(struct rts_md2_attr *attr)
{
	int x, y, r;

	if (attr->sample.scale_x > RTS_MD2_MDIN_MAX_SCALE) {
		r = __factorization(attr->sample.scale_x, &x, &y);
		if (r)
			goto failed;
	}

	if (attr->sample.scale_y > RTS_MD2_MDIN_MAX_SCALE) {
		r = __factorization(attr->sample.scale_y, &x, &y);
		if (r)
			goto failed;
	}

	return 0;
failed:
	RTS_ERR("invaild scale, too large&cant combined smaller than %dx%d\n",
			RTS_MD2_MDIN_MAX_SCALE, RTS_MD2_MDOUT_MAX_SCALE);
	return -1;
}

#include <rts_isp.h>
int __get_snr_fmt(uint32_t *w, uint32_t *h, uint32_t *fmt)
{
	int ret;
	struct rts_isp_image_size size;

	if (!w || !h || !fmt)
		return RTS_RETURN(RTS_E_NULL_POINT);

	ret = rts_isp_get_image_size(ISP0, &size);
	if (ret < 0) {
		RTS_ERR("get image size fail\n");
		return ret;
	}

	*w = size.isp_middle_size.w;
	*h = size.isp_middle_size.h;
	*fmt = size.sensor_bit_depth;

	return RTS_OK;
}


static int __check_md2_attr(struct rts_md2_attr *attr)
{
	int ret = 0;
	uint32_t w = 1920, h = 1080, fmt;

	ret = __get_snr_fmt(&w, &h, &fmt);
	if (ret < 0)
		RTS_ERR("get snr fmt failed(%s), use default 1080p\n",
				rts_strerrno(ret));

	if (attr->nr_bins >= RTS_MD2_NR_BINS_MAX) {
		RTS_ERR("nr_bins set err %d\n", attr->nr_bins);
		return -1;
	}

	if (attr->bin_bits >= RTS_MD2_BIN_BITS_MAX) {
		RTS_ERR("bin_bits set err %d\n", attr->bin_bits);
		return -1;
	}

	if (attr->skip_frames < 0 || attr->skip_frames > 100) {
		RTS_ERR("skip_frames set err %d\n", attr->skip_frames);
		return -1;
	}

	if (
		attr->sample.x >= w || attr->sample.y >= h
		|| (attr->sample.x + attr->sample.w * attr->sample.scale_x > w)
		|| (attr->sample.y + attr->sample.h * attr->sample.scale_y > h)
		|| __check_sample_scale(attr)
		) {
		RTS_ERR("sample region incorrect (%d %d %d %d %d %d)\n",
			attr->sample.x, attr->sample.y,
			attr->sample.w, attr->sample.h,
			attr->sample.scale_x, attr->sample.scale_y);

		return -1;
	}


	return 0;
};

static void __set_sensi(struct rts_md2_instance *inst)
{
	struct rts_isp_md_attr *pa = &inst->isp_md_attr;
	struct rts_pprc_filter *fl = &inst->pprc_filter;
	enum RTS_MD2_BIN_BITS bin_bits = inst->attr.bin_bits;
	int ibin_bits;
	int max_bin_val;
	int img_sz = inst->attr.sample.w * inst->attr.sample.h;

	if (inst->sensitivity == 0)
		return;

	if (bin_bits == RTS_MD2_BIN_BITS_2)
		ibin_bits = 2;
	else
		ibin_bits = 4;
	max_bin_val = (1 << ibin_bits) - 1;

	pa->thd.back = (int)roundf((max_bin_val - 1)
				* (inst->sensitivity - 1) / 6.0) + 1;
	fl->nr_cc_thd = (int)ceilf(0.02 * img_sz
			* exp2((float)(8 - inst->sensitivity)) / 128.0);
}


static int __init_md2_hw(struct rts_md2_instance *inst,
		struct rts_md2_attr *attr)
{
	struct rts_isp_md_attr *isp_attr = &inst->isp_md_attr;
	struct rts_isp_md_extra_attr *e_attr = &inst->isp_md_eattr;
	int ret = 0;
	int x = 0, y = 0;


	//find mdin & mdout scale
	if (attr->sample.scale_x > RTS_MD2_MDIN_MAX_SCALE) {
		__factorization(attr->sample.scale_x, &x, &y);
		isp_attr->md_in.scale_x = x;
		isp_attr->md_out.scale_x = y;
	} else {
	isp_attr->md_in.scale_x = attr->sample.scale_x;
		isp_attr->md_out.scale_x = 1;
	}

	if (attr->sample.scale_y > RTS_MD2_MDIN_MAX_SCALE) {
		__factorization(attr->sample.scale_y, &x, &y);
		isp_attr->md_in.scale_y = x;
		isp_attr->md_out.scale_y = y;
	} else {
	isp_attr->md_in.scale_y = attr->sample.scale_y;
		isp_attr->md_out.scale_y = 1;
	}

	isp_attr->md_in.x = attr->sample.x;
	isp_attr->md_in.y = attr->sample.y;
	isp_attr->md_in.w = attr->sample.w * isp_attr->md_out.scale_x;
	isp_attr->md_in.h = attr->sample.h * isp_attr->md_out.scale_y;

	isp_attr->md_out.x = 0;
	isp_attr->md_out.y = 0;
	isp_attr->md_out.w = attr->sample.w;
	isp_attr->md_out.h = attr->sample.h;

	isp_attr->roi.x = 0;
	isp_attr->roi.y = 0;
	isp_attr->roi.w = isp_attr->md_in.w;
	isp_attr->roi.h = isp_attr->md_in.h;

	isp_attr->thd.back = 2;
	isp_attr->thd.learn = 248;
	isp_attr->thd.forget = 10;
	isp_attr->thd.ds
		= isp_attr->md_out.scale_x * isp_attr->md_out.scale_y / 2;
	isp_attr->thd.motion = 0;

	isp_attr->nr_bins = (enum MD_NR_BINS)attr->nr_bins;
	isp_attr->bin_bits = (enum MD_BIN_BITS)attr->bin_bits;
	isp_attr->train_frames = 1.2 * (isp_attr->thd.back + 1);

	inst->sensitivity = 6;
	__set_sensi(inst);

	inst->train_enable = 1;
	inst->scene_change_thd = attr->sample.w * attr->sample.h * 0.5;

	e_attr->burst_length.hist_write = 1;
	e_attr->burst_length.res_write = 1;
	e_attr->burst_length.isp_read = 1;

	e_attr->skip.enable = 0;
	e_attr->skip.frames = 1;
	if (attr->skip_frames > 0) {
		e_attr->skip.enable = 1;
		e_attr->skip.frames = attr->skip_frames;
	}

	ret = rts_isp_md_init(&inst->hw);
	if (ret)
		return ret;

	ret = rts_isp_md_set_attr(inst->hw, isp_attr);
	if (ret)
		return ret;

	ret = rts_isp_md_set_extra_attr(inst->hw, e_attr);
	if (ret)
		return ret;

	rts_isp_md_calc_dma_size(&inst->isp_md_attr, &inst->hist_sz,
			&inst->res_sz);

	inst->hist.length = inst->hist_sz;
	inst->hist.direction |= RTSC_CMA_BUFFER_DEFAULT;
	sprintf(inst->hist.name, "Md Hist");
	ret = rts_isp_md_alloc_dma(&inst->hist);//w*h HW hist buf
	for (int i = 0; i < MD2_RES_BUF_CNT; i++) {//HW result buf 2 ping pong buf w*h/8 align to 4096
		inst->res[i].length = inst->res_sz;
		inst->res[i].direction |= RTSC_CMA_BUFFER_DEFAULT;
		sprintf(inst->res[i].name, "Md Result");
		ret |= rts_isp_md_alloc_dma(&inst->res[i]);
	}
	if (ret)
		return ret;

	ret = rts_isp_md_set_dma_addr(inst->hw, inst->hist.phy_addr,
					inst->hist.length,
					inst->res[inst->res_index].phy_addr,
					inst->res[inst->res_index].length);
	if (ret)
		return ret;

	RTS_DEBUG("mdin (%d %d %d %d %d %d)\n",
			isp_attr->md_in.x,
			isp_attr->md_in.y,
			isp_attr->md_in.w,
			isp_attr->md_in.h,
			isp_attr->md_in.scale_x,
			isp_attr->md_in.scale_y
					);
	RTS_DEBUG("mdout (%d %d %d %d %d %d)\n",
			isp_attr->md_out.x,
			isp_attr->md_out.y,
			isp_attr->md_out.w,
			isp_attr->md_out.h,
			isp_attr->md_out.scale_x,
			isp_attr->md_out.scale_y
					);
	RTS_DEBUG("mdroi_hw (%d %d %d %d)\n",
			isp_attr->roi.x,
			isp_attr->roi.y,
			isp_attr->roi.w,
			isp_attr->roi.h
					);
	return RTS_OK;
}


static int __init_md2_pprc(struct rts_md2_instance *inst,
			struct rts_md2_attr *attr)
{
	int ret = RTS_OK;

	inst->pprc_attr.fmt = PIX_FMT_Y_ONLY;
	inst->pprc_attr.roi_fmt = PIX_FMT_Y_ONLY;
	inst->pprc_attr.width = attr->sample.w;
	inst->pprc_attr.height = attr->sample.h;

	inst->pprc_filter.max_ar = 1.5;
	inst->pprc_filter.min_ar = 0.05;
	inst->pprc_filter.cc_ratio = 0.3;
	inst->pprc_filter.nr_cc_thd = 2;

	ret = rts_pprc_init(&inst->pprc_attr, &inst->pprc);
	if (ret)
		return ret;

	return RTS_OK;
}


static int __get_md2_ctrl(struct rts_md2_instance *inst)
{
	struct rts_md2_ctrl *ctrl = &inst->ctrl;
	struct rts_isp_md_attr *pa = &inst->isp_md_attr;
	struct rts_pprc_filter *fl = &inst->pprc_filter;

	/*bgm*/
	ctrl->sensitivity = inst->sensitivity;
	ctrl->train_enable = inst->train_enable;
	ctrl->scene_change_thd = inst->scene_change_thd;
	ctrl->train_frames = pa->train_frames;
	ctrl->back_thd = pa->thd.back;
	ctrl->learn_thd = pa->thd.learn;
	ctrl->forget_thd = pa->thd.forget;

	/*pprc*/
	ctrl->nr_cc_thd = fl->nr_cc_thd;
	ctrl->max_ar = fl->max_ar;
	ctrl->min_ar = fl->min_ar;
	ctrl->cc_ratio = fl->cc_ratio;

	/*roi*/
	RTS_S_C_VAR(ctrl->roi.width, inst->attr.sample.w, uint32_t);
	RTS_S_C_VAR(ctrl->roi.height, inst->attr.sample.h, uint32_t);
	RTS_S_C_VAR(ctrl->roi.length, inst->roi_buf_len, uint32_t);

	memcpy(inst->roi_buf, inst->pprc.roi.map, inst->pprc.roi.length);
	RTS_S_C_VAR(ctrl->roi.map, inst->roi_buf, uint8_t *);

	return 0;
}

static int __check_md2_ctrl(struct rts_md2_instance *inst)
{
	struct rts_md2_ctrl *ctrl = &inst->ctrl;


	if (ctrl->sensitivity < 0 || ctrl->sensitivity > 7)
		return -1;

	if (ctrl->train_enable < 0)
		return -1;

	if (ctrl->min_ar < 0.0 || ctrl->max_ar <= ctrl->min_ar)
		return -1;
	if (ctrl->cc_ratio >= 1.0 || ctrl->cc_ratio < 0.0)
		return -1;

	return 0;
}


static int __set_md2_ctrl(struct rts_md2_instance *inst)
{
	struct rts_md2_ctrl *ctrl = &inst->ctrl;
	struct rts_pprc_filter *fl = &inst->pprc_filter;
	struct rts_pprc_filter fl_bak;
	struct rts_isp_md_attr *pa = &inst->isp_md_attr;
	struct rts_isp_md_attr attr_bak;
	int sensi_bak = inst->sensitivity;
	int ret = 0;

	memcpy(&attr_bak, pa, sizeof(*pa));
	memcpy(&fl_bak, fl, sizeof(*fl));
	/*-bgm-*/
	inst->sensitivity = ctrl->sensitivity;
	pa->thd.back = ctrl->back_thd;
	pa->thd.learn = ctrl->learn_thd;
	pa->thd.forget = ctrl->forget_thd;
	pa->train_frames = ctrl->train_frames;
	/*-end of bgm-*/

	/*-pprc-*/
	fl->nr_cc_thd = ctrl->nr_cc_thd;
	fl->max_ar = ctrl->max_ar;
	fl->min_ar = ctrl->min_ar;
	fl->cc_ratio = ctrl->cc_ratio;
	/*-end of pprc-*/

	__set_sensi(inst);
	ctrl->nr_cc_thd = fl->nr_cc_thd;
	ctrl->back_thd = pa->thd.back;
	
	ret = rts_isp_md_set_attr(inst->hw, pa);
	if (ret)
		goto failed;

	sensi_bak = inst->sensitivity;
	inst->sensitivity = sensi_bak;

	inst->train_enable = ctrl->train_enable;
	inst->scene_change_thd = ctrl->scene_change_thd;

	RTS_DEBUG("md thd (back learn forget ds) (%d %d %d %d)\n",
				pa->thd.back,
				pa->thd.learn,
				pa->thd.forget,
				pa->thd.ds
				);
	RTS_DEBUG("md trainframes %d\n", pa->train_frames);
	RTS_DEBUG("md_cc (nr_cc_thd max_ar min_ar cc_ratio) (%d %.2f %.2f %.2f)\n",
				fl->nr_cc_thd,
				fl->max_ar,
				fl->min_ar,
				fl->cc_ratio);
	RTS_DEBUG("md scene_thd (%d)\n", inst->scene_change_thd);

	/*-roi-*/
	memcpy(inst->pprc.roi.map, ctrl->roi.map, inst->pprc.roi.length);
	/*-end of roi-*/
	if (inst->train_enable)
		rts_isp_md_trigger_train(inst->hw);

	return 0;
failed:
	inst->sensitivity = sensi_bak;
	memcpy(pa, &attr_bak, sizeof(*pa));
	memcpy(fl, &fl_bak, sizeof(*fl));
	ret = rts_isp_md_set_attr(inst->hw, pa);

	return ret;
}


int rts_av_query_md2(struct rts_md2_ctrl **ctrl,
			struct rts_md2_attr *attr)
{
	struct rts_md2_instance *inst = NULL;
	uint32_t img_size;
	int ret = 0;

	const osMutexAttr_t instlock_Mutex_attr = {
	  "instlockMutex",                          // human readable mutex name
	  osMutexRecursive | osMutexPrioInherit,    // attr_bits
	  NULL,                         // memory for control block
	  0U                   // size for control block
	};

	if (!attr || __check_md2_attr(attr))
		return RC(INVALID_ARG);

	inst = rts_calloc(1, sizeof(struct rts_md2_instance));
	if (!inst)
		return RC(NO_MEMORY);

	/*- alloc buffer -*/
	img_size = attr->sample.w * attr->sample.h;
	//default img pixfmt yonly
	inst->roi_buf_len = inst->res_buf_len = ALIGNN(img_size, 8);
	inst->total_buf_len = inst->roi_buf_len + inst->res_buf_len;
	inst->inst_buf = rts_calloc(1, inst->total_buf_len);//res_buf(w*h final result) + roi buf(w*h)
	if (!inst->inst_buf)
		goto failed;

	inst->res_buf = inst->inst_buf;
	inst->roi_buf = (void *)((uint32_t)inst->res_buf + inst->res_buf_len);
	/*- end alloc buffer -*/

	ret = __init_md2_pprc(inst, attr);
	if (ret)
		goto failed;

	ret = __init_md2_hw(inst, attr);
	if (ret)
		goto failed;

	memcpy(&inst->attr, attr, sizeof(*attr));

	__get_md2_ctrl(inst);

	inst->lock = osMutexNew(&instlock_Mutex_attr);
	if ( !inst->lock ) {
		RTS_ERR("inst->lock mutex alloc fail\n");
		goto failed;
	}
	*ctrl = &inst->ctrl;

	if (inst->train_enable)
		rts_isp_md_trigger_train(inst->hw);
	rts_isp_md_enable(inst->hw, 1);
	inst->initialized = 1;

	return RTS_OK;
failed:
	__release_md2(inst);
	return ret;
}

void rts_av_release_md2(struct rts_md2_ctrl *ctrl)
{
	struct rts_md2_instance *inst = NULL;

	if (!ctrl)
		return;
	inst = __to_md2_instance(ctrl);
	if (!inst->initialized)
		RTS_SAFE_DELETE(inst);

	__release_md2(inst);
}


int rts_av_set_md2(struct rts_md2_ctrl *ctrl)
{
	int ret = 0;
	struct rts_md2_instance *inst = NULL;

	if (!ctrl)
		return RC(NULL_POINT);
	inst = __to_md2_instance(ctrl);

	ret = MD_IN(inst);
	if (ret != pdTRUE) {
		isp_error("rts_av_set_md2 wait inst->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	if (!inst->initialized) {
		ret = RC(NOT_INITIALIZED);
		goto out;
	}

	ret = __check_md2_ctrl(inst);
	if (ret) {
		ret = RC(INVALID_ARG);
		goto out;
	}

	ret = __set_md2_ctrl(inst);
#ifdef MD2_DEBUG
	rts_isp_md_dump_regs(inst->hw);
#endif
out:
	MD_OUT(inst);
	return ret;
}


int rts_av_get_md2(struct rts_md2_ctrl *ctrl)
{
	int ret = 0;
	struct rts_md2_instance *inst = NULL;

	if (!ctrl)
		return RC(NULL_POINT);
	inst = __to_md2_instance(ctrl);

	ret = MD_IN(inst);
	if (ret != pdTRUE) {
		isp_error("rts_av_get_md2 wait inst->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	if (!inst->initialized) {
		ret = RC(NOT_INITIALIZED);
		goto out;
	}
	ret = rts_isp_md_get_attr(inst->hw, &inst->isp_md_attr);
	if (ret)
		goto out;
	__get_md2_ctrl(inst);
out:
	MD_OUT(inst);
	return ret;
}

static void __retrain(struct rts_md2_instance *inst)
{
	RTS_INFO("retraining\n");
	memset((void*)(inst->hist.phy_addr/*|0x80000000*/), 0, inst->hist.length);
	SCB_CleanDCache_by_Addr((uint32_t*)(inst->hist.phy_addr/*|0x80000000*/), inst->hist.length);

	rts_isp_md_trigger_train(inst->hw);
	rts_isp_md_done(inst->hw);
}

static int __poll_md2(struct rts_md2_ctrl *ctrl, int timeout_ms)
{
	struct rts_md2_instance *inst = NULL;
	int ret = 0;
	uint32_t s = 0;
	int v1, v2;
	unsigned int msecs = 0;
	int timetowait;

	if (!ctrl)
		return RC(NULL_POINT);
	inst = __to_md2_instance(ctrl);
	if (!inst->initialized)
		return RC(NOT_INITIALIZED);

	v1 = xTaskGetTickCount() / portTICK_PERIOD_MS;
repoll:
	v2 = xTaskGetTickCount() / portTICK_PERIOD_MS;
	msecs = v2 - v1;

	if (timeout_ms > 0) {
		timetowait = timeout_ms -  msecs;
		if (timetowait < 0)
			return RTS_FALSE;
	} else
		timetowait = timeout_ms;

	ret = rts_isp_md_poll2(inst->hw, timetowait, &s);
	if (ret == RTS_FALSE)
		return RTS_FALSE;

	RTS_DEBUG("poll ret(%d) status(0x%x)\n",
			ret, s);

	if (s & RTSMD_OL_MASK) {
		int fl_retrain = 0;
		int fl_skip = 0;

		if ((s & RTSMD_FL_MTD_UL) || (s & RTSMD_FL_AFIFO_OL)) {
			RTS_ERR("rtsmd mtd underflow or afifo overflow(0x%x)\n",
					s);
			fl_retrain++;
		}
		if ((s & RTSMD_FL_RESULT_OL)
				|| (s & RTSMD_FL_RESULT_AXI_OL)
				|| (s & RTSMD_FL_RESULT_DDR_OL)) {
			RTS_ERR("rtsmd result overflow(0x%x)\n", s);
			fl_skip++;
		}
		if ((s & RTSMD_FL_HISTO_OL)
				|| (s & RTSMD_FL_HISTO_AXI_OL)
				|| (s & RTSMD_FL_HISTO_DDR_OL)) {
			RTS_ERR("rtsmd histo overflow(0x%x)\n", s);
			fl_retrain++;
		}

		if (fl_retrain) {
			__retrain(inst);
			goto repoll;
		} else if (fl_skip) {
			RTS_INFO("skip this frame\n");
			rts_isp_md_done(inst->hw);
			goto repoll;
		}
	}

	return RTS_TRUE;
}

int rts_av_poll_md2(struct rts_md2_ctrl *ctrl, int timeout_ms)
{
	return __poll_md2(ctrl, timeout_ms);
}

int rts_av_poll_md2_result(struct rts_md2_ctrl *ctrl, int timeout_ms)
{
	if (__poll_md2(ctrl, timeout_ms) == RTS_TRUE)
		return 0;
	else
		return RTS_RETURN(RTS_E_EMPTY);
}

static int minheap_cmp_cc(void *v1, void *v2)
{
	struct rts_md2_cc *p1 = v1;
	struct rts_md2_cc *p2 = v2;

	return p1->pixel_cnt < p2->pixel_cnt ? 1 : -1;
}


static int __get_kmax_cc(struct CC_context *ccon, int k,
			struct rts_md2_cc_info  *cc_info)
{
	struct rts_md2_cc *pvcc = cc_info->cc;
	rts_array heap_cc;

	memset(pvcc, 0, sizeof(*pvcc) * k);
	rtsarr_init(&heap_cc, pvcc, sizeof(*pvcc), 0);

	for (int i = 0; i < ccon->cc_index; i++) {
		struct CC *pcc = ccon->cc + i;

		if (
		(!(pcc->flags & CC_FLAG_ROOT))
		|| (pcc->flags & CC_FLAG_FILTERED)
		)
			continue;

		if ((int)heap_cc.length >= k) {
			pvcc = cc_info->cc;
			if (pcc->pixel_cnt > pvcc->pixel_cnt) {
				pvcc->u = pcc->u;
				pvcc->b = pcc->b;
				pvcc->l = pcc->l;
				pvcc->r = pcc->r;
				pvcc->pixel_cnt = pcc->pixel_cnt;
				rts_reform_heap(&heap_cc, minheap_cmp_cc);
			}
		} else {
			pvcc = cc_info->cc + heap_cc.length;
			heap_cc.length++;

			pvcc->u = pcc->u;
			pvcc->b = pcc->b;
			pvcc->l = pcc->l;
			pvcc->r = pcc->r;
			pvcc->pixel_cnt = pcc->pixel_cnt;
			rts_build_heap(&heap_cc, minheap_cmp_cc);
		}
	}

	cc_info->cc_len = heap_cc.length;

	for (int i = (heap_cc.length - 1); i > 0; i--) {
		/*heap sort cc*/
		struct rts_md2_cc vcc;
		struct rts_md2_cc *pvcc2 = cc_info->cc + i;

		rts_heap_pop(&heap_cc, minheap_cmp_cc, &vcc);
		*pvcc2 = vcc;
	}

	return 0;
}


int rts_av_get_md2_result(struct rts_md2_ctrl *ctrl,
		struct rts_md2_result *res)
{
	struct rts_md2_instance *inst = NULL;
	int ret = RTS_OK;
	uint32_t cur_res_index;
	struct rtsc_dma_buffer *dma;
	struct rts_isp_md_result resu;

	if (!ctrl || !res)
		return RC(NULL_POINT);
	inst = __to_md2_instance(ctrl);

	ret = MD_IN(inst);
	if (ret != pdTRUE) {
		isp_error("rts_av_get_md2_result wait inst->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	if (!inst->initialized) {
		ret = RC(NOT_INITIALIZED);
		goto out;
	}

	/*-switch hw buffer-*/
	ret = rts_isp_md_get_result(inst->hw, &resu);
	if (ret)
		goto out;
	cur_res_index = inst->res_index;
	inst->res_index = (cur_res_index + 1) % MD2_RES_BUF_CNT;
	ret = rts_isp_md_set_dma_addr(inst->hw, inst->hist.phy_addr,
				inst->hist.length,
				inst->res[inst->res_index].phy_addr,
				inst->res[inst->res_index].length);
	if (ret)
		goto out;
	rts_isp_md_done(inst->hw);
	/*-end switch hw buffer-*/

	/*-get hw result-*/
	SCB_InvalidateDCache_by_Addr((uint32_t*)(inst->res[cur_res_index].phy_addr), inst->res[cur_res_index].length);
	dma = &inst->res[cur_res_index];
	/*-end get hw result-*/

	res->motion_cnt = resu.motion_count;

	if (res->flags & RTS_MD2_RESULT_FL_ENABLE_POST_PROCESS) {
		inst->pprc_filter.enable_cc_info =
			(res->flags & RTS_MD2_RESULT_FL_ENABLE_CC_INFO) != 0;
		inst->pprc_filter.enable_cc_filter =
			(res->flags & RTS_MD2_RESULT_FL_ENABLE_CC_FILTER) != 0;

		if (res->flags & RTS_MD2_RESULT_FL_ENABLE_MOTION_MAP)
		ret = rts_pprc_run(&inst->pprc, &inst->pprc_filter,
				(void*)(dma->phy_addr/*|0x80000000*/), inst->res_buf);
		else
			ret = rts_pprc_run(&inst->pprc, &inst->pprc_filter,
				(void*)(dma->phy_addr/*|0x80000000*/), NULL);
		if (ret)
			goto out;

		if (!inst->pprc_filter.enable_cc_info) {
			res->cc_info.cc_len = 0;
			goto out;
		}

		res->motion_cnt = 0;
		for (int i = 0; i < inst->pprc.ccon.cc_index; i++) {
			struct CC *pcc = &inst->pprc.ccon.cc[i];

			if ((!(pcc->flags & CC_FLAG_ROOT))
			|| (pcc->flags & CC_FLAG_FILTERED)) {
				continue;
			}

			res->motion_cnt += pcc->pixel_cnt;
		}

		__get_kmax_cc(&inst->pprc.ccon, RTS_MD2_MAX_CC_NUM,
					&res->cc_info);

	} else  { /*count motion in ROI here*/
		if (inst->pprc.ops->fmt == PIX_FMT_Y_ONLY)
			img_run_roimap_with_priv(inst->pprc.bitops,
					OP_filter_roi_to_yonly,
					&inst->pprc.roi,
					(void*)(dma->phy_addr/*|0x80000000*/),
					inst->res_buf,
					&res->motion_cnt);
		else
			img_run_roimap_with_priv(
				inst->pprc.ops,
				OP_filter_roi,
				&inst->pprc.roi,
				(void*)(dma->phy_addr/*|0x80000000*/),
				inst->res_buf,
				&res->motion_cnt);
	}

out:
	if (inst->train_enable && res->motion_cnt >= inst->scene_change_thd)
		rts_isp_md_trigger_train(inst->hw);

	res->motion_map = inst->res_buf;
	MD_OUT(inst);

	return ret;
}
