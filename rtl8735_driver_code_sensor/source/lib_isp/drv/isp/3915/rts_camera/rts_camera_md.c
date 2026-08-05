/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_md.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */

#define TAG "MD"

#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include <linux/poll.h>
#include "rt_types.h"
#include "rt_util.h"
#include "rts_errno.h"
#include "rts_camera.h"
//#include "rts_camera_isp_clk.h"
#include "rts_camera_isp_mfd.h"
#include "linux/rts_camera_md.h"
#include "rlx_reg.h"
#include "rlx_irq.h"
#include "rtsdef.h"
#include "rtx_mutex.h"
#include "rt_time.h"

#define md_err(...) rtsprintk(RTS_TRACE_ERROR, __VA_ARGS__)
#define md_info(...) rtsprintk(RTS_TRACE_INFO, __VA_ARGS__)
#define md_debug(...) rtsprintk(RTS_TRACE_DEBUG, __VA_ARGS__)

#define RTS_ISP_MD_DEV_NAME "rtsmd"
#define RTS_ISP_MD_DRV_NAME "rts_md"

#define MD_FRAME_DONE_BIT 0

/* registers */
#define MD_REG_BIN_CTRL			0x003c
#define MD_REG_INT_EN			0x005c
#define MD_REG_INT_CLR			0x0060
#define MD_REG_IC_HISTBUF		0x0050
#define MD_REG_IC_RESULTBUF		0x006c

#define MD_BIN_CTRL_MASK_PAUSE		0x8
#define MD_BIN_CTRL_MASK_EN		0x10
#define MD_BIN_CTRL_MASK_RESET		0x20

#define MD_INT_EN_MASK_HIST		0x1
#define MD_INT_EN_MASK_RESULT		0x2

#define MD_INT_MASK_HIST		0x1
#define MD_INT_MASK_RESULT		0x2
#define MD_INT_MASK_IC_HISTBUF_OL	0x4
#define MD_INT_MASK_IC_RESULTBUF_OL	0x8
#define MD_INT_MASK_HISTDDR_OL		0x10
#define MD_INT_MASK_RESULTDDR_OL	0x20

#define MD_INT_MASK_MD_UL		0x40
#define MD_INT_MASK_HIST_OL		0x80
#define MD_INT_MASK_RESULT_OL		0x100

#define MD_INT_MASK_OL			0x3fc

enum {
	MD_IN_WIDTH = 0,
	MD_IN_HEIGHT,
	MD_IN_SCALE_X,
	MD_IN_SCALE_Y,
	MD_IN_START_X,
	MD_IN_START_Y,
	MD_OUT_WIDTH,
	MD_OUT_HEIGHT,
	MD_OUT_SCALE_X,
	MD_OUT_SCALE_Y,
	MD_OUT_START_X,
	MD_OUT_START_Y,
	MD_OUT_DS_THD,
	MD_ROI_START_X,
	MD_ROI_START_Y,
	MD_ROI_END_X,
	MD_ROI_END_Y,
	MD_NR_BINS,
	MD_BIN_BITS,
	MD_TRAIN,
	MD_RESET_BUF,
	//MD_DATA_REQ,
	MD_ENABLE_SKIP,
	MD_SKIP_FRAMES,
	MD_BACK_THD,
	MD_LEARN_THD,
	MD_FORGET_THD,
	MD_MOTION_THD,
	MD_TRAIN_FRAMES,
	MD_HIST_ADDR,
	MD_HIST_LEN,
	MD_HIST_AXI_ADDR,
	MD_HIST_AXI_LEN,
	MD_HIST_PIX_CNT,
	MD_INT_FLAG,
	MD_BURST_LEN_SEL_WR0,
	MD_RESULT_ADDR,
	MD_RESULT_LEN,
	MD_RESULT_AXI_ADDR,
	MD_RESULT_AXI_LEN,
	MD_RESULT_PIX_CNT,
	MD_BURST_LEN_SEL_WR1,
	MD_BURST_LEN_SEL_RD,
	MD_FLAG,
	MD_MOTION_PIX_CNT,
};

typedef struct {
	off_t offset;
	int lsb;
	int bits;
} reg_desc_t;

static reg_desc_t m_md_regs[] = {
	[MD_IN_WIDTH]		=	{0x0,	0,	10},
	[MD_IN_HEIGHT]		=	{0x4,	0,	9},
	[MD_IN_SCALE_X]		=	{0x8,	0,	4},
	[MD_IN_SCALE_Y]		=	{0x8,	8,	4},
	[MD_IN_START_X]		=	{0x0c,	0,	10},
	[MD_IN_START_Y]		=	{0x10,	0,	9},
	[MD_OUT_WIDTH]		=	{0x14,	0,	10},
	[MD_OUT_HEIGHT]		=	{0x18,	0,	9},
	[MD_OUT_SCALE_X]	=	{0x1c,	0,	3},
	[MD_OUT_SCALE_Y]	=	{0x1c,	8,	3},
	[MD_OUT_START_X]	=	{0x20,	0,	10},
	[MD_OUT_START_Y]	=	{0x24,	0,	9},
	[MD_OUT_DS_THD]		=	{0x28,	0,	4},
	[MD_ROI_START_X]	=	{0x2c,	0,	10},
	[MD_ROI_START_Y]	=	{0x30,	0,	9},
	[MD_ROI_END_X]		=	{0x34,	0,	10},
	[MD_ROI_END_Y]		=	{0x38,	0,	9},
	[MD_NR_BINS]		=	{0x3c,	0,	1},
	[MD_BIN_BITS]		=	{0x3c,	1,	1},
	[MD_TRAIN]		=	{0x84,	0,	1},
	[MD_RESET_BUF]		=	{0x3c,	5,	1},
	//[MD_DATA_REQ]		=	{0x3c,	6,	1},
	[MD_ENABLE_SKIP]	=	{0x3c,	7,	1},
	[MD_SKIP_FRAMES]	=	{0x3c,	8,	7},
	[MD_BACK_THD]		=	{0x40,	0,	4},
	[MD_LEARN_THD]		=	{0x40,	8,	8},
	[MD_FORGET_THD]		=	{0x40,	16,	8},
	[MD_MOTION_THD]		=	{0x44,	0,	17},
	[MD_TRAIN_FRAMES]	=	{0x48,	0,	5},
	[MD_HIST_ADDR]		=	{0x4c,	0,	32},
	[MD_HIST_LEN]		=	{0x54,	0,	24},
	[MD_HIST_AXI_ADDR]	=	{0x50,	0,	14},
	[MD_HIST_AXI_LEN]	=	{0x50,	16,	16},
	[MD_HIST_PIX_CNT]	=	{0x58,	0,	23},
	[MD_INT_FLAG]		=	{0x60,	0,	10},
	[MD_BURST_LEN_SEL_WR0]	=	{0x64,	0,	1},
	[MD_RESULT_ADDR]	=	{0x68,	0,	32},
	[MD_RESULT_LEN]		=	{0x70,	0,	24},
	[MD_RESULT_AXI_ADDR]	=	{0x6c,	0,	14},
	[MD_RESULT_AXI_LEN]	=	{0x6c,	16,	16},
	[MD_RESULT_PIX_CNT]	=	{0x74,	0,	23},
	[MD_BURST_LEN_SEL_WR1]	=	{0x78,	0,	1},
	[MD_BURST_LEN_SEL_RD]	=	{0x7C,	0,	1},
	[MD_FLAG]		=	{0x80,	0,	1},
	[MD_MOTION_PIX_CNT]	=	{0x80,	1,	17},
};

#define MD_OPS(func, args...)		\
	do {\
		if (func)\
			func(args);\
	} while (0)

struct rtscam_md_ops {
	int (*enable)(void *, int enable);
	int (*enable_interrupt)(void *, int enable);
	int (*enable_clk)(void *, int enable);
	int (*enable_pwr)(void *, int enable);
	int (*reset)(void *);
	void (*set_icfg)(void *);
	int (*irq)(void *);
};

struct rts_hw_buffer_cfg {
	u32 start;
	u32 size;
};

//struct rts_md_resource {
//	unsigned long io_start;
//	unsigned int io_size;
//	void *reg_base;
//	int irq;
//};

struct rtscam_md {
//	struct rtscam_ge_device *gdev;
//	struct device *dev;

	struct rtscam_md_ops *ops;

	//struct rts_md_resource res;
	struct rtscam_isp_mfd *mfd;

	struct rts_hw_buffer_cfg icfg[2];

	osMutexId_t lock;  //struct mutex lock;
	osSemaphoreId_t wq;  //wait_queue_head_t wq;
	int use_count;

	//unsigned long status;
	unsigned int intr_flag;

	osSemaphoreId_t skip_completion;  //struct completion skip_completion;
	u8 skip_completion_flag;
	u8 skip_completion_needed;
};

static struct rtscam_md gbl_md={0};

static inline u32 __md_read_reg(struct rtscam_md *md, off_t reg)
{
	//return REG_R32(md->res.reg_base + reg);
	return md->mfd->read_reg(md->mfd, RTS_MFD_MODUAL_ID_MD, reg);
}

static inline void __md_write_reg(struct rtscam_md *md, off_t reg, u32 val)
{
	//REG_W32(md->res.reg_base + reg, val);
	md->mfd->write_reg(md->mfd, RTS_MFD_MODUAL_ID_MD, reg, val);
}


static int md_enable_interrupt(void *h, int enable)
{
	struct rtscam_md *md = h;
	//u32 s;

	if (!md)
		return 0;

	md_debug("enable intr %d\n", enable);

	//s = __md_read_reg(md, MD_REG_INT_EN);

	if (enable) {
		//RLX_EnableVideoInIRQ(VIDEOIN_ID_MD);
		__md_write_reg(md, MD_REG_INT_EN, 0x3ff);
	} else {
		__md_write_reg(md, MD_REG_INT_EN, 0);
		//RLX_DisableVideoInIRQ(VIDEOIN_ID_MD);
	}

	md_debug("read intr 0x%08x\n", __md_read_reg(md, MD_REG_INT_EN));

	return 0;
}

static int md_enable(void *h, int enable)
{
	struct rtscam_md *md = h;
	u32 b;

	b = __md_read_reg(md, MD_REG_BIN_CTRL);

	if (enable) {
		b = (b | MD_BIN_CTRL_MASK_EN) & (~MD_BIN_CTRL_MASK_RESET);
		__md_write_reg(md, MD_REG_BIN_CTRL, b);
	} else {
		if (b & MD_BIN_CTRL_MASK_EN) {
			b = __md_read_reg(md, MD_REG_BIN_CTRL);
			__md_write_reg(md, MD_REG_BIN_CTRL,
					(b & (~MD_BIN_CTRL_MASK_EN)));
		}
	}

	return 0;
}

static void md_set_icfg(void *h)
{
	struct rtscam_md *md = h;

	if (!md)
		return;

	/*set icbuf addr*/
	__md_write_reg(md, MD_REG_IC_HISTBUF, ((md->icfg[0].size << 16) |
			md->icfg[0].start));
	__md_write_reg(md, MD_REG_IC_RESULTBUF, ((md->icfg[1].size << 16) |
			md->icfg[1].start));
}

static int md_enable_clk(void *h, int enable)
{
	struct rtscam_md *md = h;

	if (!md)
		return -EINVAL;
	//dbg_printf("%s %d\r\n", __func__, enable);
	//return rtscam_isp_set_isp_clock(enable ? 1 : 0);
	return md->mfd->set_clk(md->mfd, enable ? 1 : 0);
}

static int __check_md_busy(u32 val)
{
	if (val & MD_BIN_CTRL_MASK_PAUSE)
		return 1;
	else
		return 0;
}

static void __disable_md_busy(struct rtscam_md *md)
{
	u32 val;

	val = __md_read_reg(md, MD_REG_BIN_CTRL);

	if (!__check_md_busy(val))
		return;

	__md_write_reg(md, MD_REG_BIN_CTRL, val & (~MD_BIN_CTRL_MASK_PAUSE));
}

static void __enable_md_busy(struct rtscam_md *md)
{
	u32 val;

	val = __md_read_reg(md, MD_REG_BIN_CTRL);

	if (__check_md_busy(val))
		return;

	__md_write_reg(md, MD_REG_BIN_CTRL, (val | MD_BIN_CTRL_MASK_PAUSE));
}

static int md_irq(void *data)
{
	struct rtscam_md *md = &gbl_md;
	u32 s;
	u32 b;
	int flag_done = 0;

	//if (!rtscam_isp_check_isp_clock())
	//	return;  // IRQ_NONE;

	s = __md_read_reg(md, MD_REG_INT_CLR);
	b = __md_read_reg(md, MD_REG_BIN_CTRL);
	if (__check_md_busy(b)) {
		if (s & MD_INT_MASK_OL)
			printf("buffer overflow: %x\n\r", s);
		__md_write_reg(md, MD_REG_INT_CLR, s);
		return IRQ_NONE;
	}

	if (!s)
		return IRQ_NONE;

	__md_write_reg(md, MD_REG_INT_CLR, s);

	/*do not handle hist(mtd0) frame end irq*/
	if (s & MD_INT_MASK_RESULT)
		flag_done++;

	if (s & MD_INT_MASK_OL) {
		md_err("buffer overflow [0x%x].\n", s);
		return IRQ_NONE;
	}

	if (flag_done) {
		int ret;
		/*pause the md module*/
		//b = __md_read_reg(md, MD_REG_BIN_CTRL);
		//__md_write_reg(md, MD_REG_BIN_CTRL,
		//		(b | MD_BIN_CTRL_MASK_PAUSE));
		__enable_md_busy(md);

		md->intr_flag = s;
		//set_bit(MD_FRAME_DONE_BIT, &md->status);
		//wake_up_interruptible(&md->wq);
#if 1
	    portBASE_TYPE taskWoken = pdFALSE;
        if (xSemaphoreGiveFromISR(md->wq, &taskWoken) != pdTRUE) {
			rtsprintk(RTS_TRACE_ERROR, "md sema raise failed\n");
        }
	    portEND_SWITCHING_ISR(taskWoken);

#else
	    ret = osSemaphoreRelease(md->wq);

		switch (ret) {
		case osOK:
			break;
		case osErrorResource:
			rtsprintk(RTS_TRACE_WARNING, "md sema max count reached\n");
			break;
		default:
			rtsprintk(RTS_TRACE_ERROR, "md sema raise failed\n");
			break;
		}
#endif
//		rtscam_ge_kill_fasync(md->gdev, SIGIO, POLLIN);

		if (md->skip_completion_needed) {
			//if (md->skip_completion_flag &&
			//	!completion_done(&md->skip_completion)) {
			//	md->skip_completion_flag = 0;
			//	complete(&md->skip_completion);
			//}
			if (md->skip_completion_flag &&
				!osSemaphoreGetCount(md->skip_completion)) {
				md->skip_completion_flag = 0;
#if 1
				portBASE_TYPE taskWoken = pdFALSE;
				if (xSemaphoreGiveFromISR(md->skip_completion, &taskWoken) != pdTRUE) {
					rtsprintk(RTS_TRACE_ERROR, "md skip_completion failed\n");
				}
				portEND_SWITCHING_ISR(taskWoken);

#else
				osSemaphoreRelease(md->skip_completion);
#endif
			}
		}
	}

	return IRQ_HANDLED;
}

static struct rtscam_md_ops m_md_ops = {
	.enable = md_enable,
	.enable_interrupt = md_enable_interrupt,
	.irq = md_irq,
	.set_icfg = md_set_icfg,
	.enable_clk = md_enable_clk,
};


int rtscam_isp_md_open(void)
{
	struct rtscam_md *md = &gbl_md;

	if (xSemaphoreTake(md->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_md_open wait md->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	if (atomic_inc_return_isp(&md->use_count) == 1) {
		MD_OPS(md->ops->enable_clk, md, 1);
		MD_OPS(md->ops->enable_pwr, md, 1);
		MD_OPS(md->ops->set_icfg, md);
		MD_OPS(md->ops->enable_interrupt, md, 1);
		MD_OPS(md->ops->enable_clk, md, 0);
	}
	//osMutexRelease(md->lock);
	xSemaphoreGive(md->lock);
	//filp->private_data = md;
	return 0;
}

int rtscam_isp_md_close(void)
{
	struct rtscam_md *md = &gbl_md;

	if (xSemaphoreTake(md->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_md_close wait md->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	if (atomic_dec_return_isp(&md->use_count) == 0) {
		MD_OPS(md->ops->enable_clk, md, 1);
		MD_OPS(md->ops->enable_pwr, md, 0);
		MD_OPS(md->ops->enable_interrupt, md, 0);
		MD_OPS(md->ops->enable_clk, md, 0);
	}

	//osMutexRelease(md->lock);
	xSemaphoreGive(md->lock);
	//filp->private_data = NULL;

	return 0;
}

static void rtscam_md_write(struct rtscam_md *md, int id, unsigned int val)
{
	unsigned int v;
	unsigned int mask;
	reg_desc_t *des = &m_md_regs[id];

	mask = (unsigned int)(((1LL << des->bits) - 1) << des->lsb);
	v = __md_read_reg(md, des->offset);
	v &= (~mask);

	v |= ((val << des->lsb) & mask);
	__md_write_reg(md, des->offset, v);
}

static int rtscam_md_read(struct rtscam_md *md, int id)
{
	unsigned int v;
	reg_desc_t *des = &m_md_regs[id];

	v = __md_read_reg(md, des->offset);
	return ((v >> des->lsb) & (unsigned int)((1LL << des->bits) - 1));
}

static void __md_set_extra_attr(struct rtscam_md *md,
			struct rtscam_md_extra_attr *attr)
{
	if (!md || !attr)
		return;

	rtscam_md_write(md, MD_BURST_LEN_SEL_RD,
				attr->burst_length.isp_read);
	rtscam_md_write(md, MD_BURST_LEN_SEL_WR0,
				attr->burst_length.hist_write);
	rtscam_md_write(md, MD_BURST_LEN_SEL_WR1,
				attr->burst_length.res_write);


	rtscam_md_write(md, MD_ENABLE_SKIP, attr->skip.enable);
	rtscam_md_write(md, MD_SKIP_FRAMES, attr->skip.frames);
}

static void __md_set_attr(struct rtscam_md *md,
			struct rtscam_md_attr *attr)
{
	if (!md || !attr)
		return;

	rtscam_md_write(md, MD_IN_WIDTH, attr->md_in.w);
	rtscam_md_write(md, MD_IN_HEIGHT, attr->md_in.h);
	rtscam_md_write(md, MD_IN_START_X, attr->md_in.x);
	rtscam_md_write(md, MD_IN_START_Y, attr->md_in.y);
	rtscam_md_write(md, MD_IN_SCALE_X, attr->md_in.scale_x);
	rtscam_md_write(md, MD_IN_SCALE_Y, attr->md_in.scale_y);

	rtscam_md_write(md, MD_OUT_WIDTH, attr->md_out.w);
	rtscam_md_write(md, MD_OUT_HEIGHT, attr->md_out.h);
	rtscam_md_write(md, MD_OUT_START_X, attr->md_out.x);
	rtscam_md_write(md, MD_OUT_START_Y, attr->md_out.y);
	rtscam_md_write(md, MD_OUT_SCALE_X, attr->md_out.scale_x);
	rtscam_md_write(md, MD_OUT_SCALE_Y, attr->md_out.scale_y);

	rtscam_md_write(md, MD_ROI_END_X, attr->roi.x + attr->roi.w);
	rtscam_md_write(md, MD_ROI_END_Y, attr->roi.y + attr->roi.h);
	rtscam_md_write(md, MD_ROI_START_X, attr->roi.x);
	rtscam_md_write(md, MD_ROI_START_Y, attr->roi.y);

	rtscam_md_write(md, MD_NR_BINS, attr->nr_bins);
	rtscam_md_write(md, MD_BIN_BITS, attr->bin_bits);
	rtscam_md_write(md, MD_TRAIN_FRAMES, attr->train_frames);

	rtscam_md_write(md, MD_BACK_THD, attr->thd.back);
	rtscam_md_write(md, MD_LEARN_THD, attr->thd.learn);
	rtscam_md_write(md, MD_FORGET_THD, attr->thd.forget);
	rtscam_md_write(md, MD_OUT_DS_THD, attr->thd.ds);
	rtscam_md_write(md, MD_MOTION_THD, attr->thd.motion);
}

static void __md_get_attr(struct rtscam_md *md,
			struct rtscam_md_attr *attr)
{
	if (!md || !attr)
		return;

	attr->md_in.w = rtscam_md_read(md, MD_IN_WIDTH);
	attr->md_in.h = rtscam_md_read(md, MD_IN_HEIGHT);
	attr->md_in.x = rtscam_md_read(md, MD_IN_START_X);
	attr->md_in.y = rtscam_md_read(md, MD_IN_START_Y);
	attr->md_in.scale_x = rtscam_md_read(md, MD_IN_SCALE_X);
	attr->md_in.scale_y = rtscam_md_read(md, MD_IN_SCALE_Y);

	attr->md_out.w = rtscam_md_read(md, MD_OUT_WIDTH);
	attr->md_out.h = rtscam_md_read(md, MD_OUT_HEIGHT);
	attr->md_out.x = rtscam_md_read(md, MD_OUT_START_X);
	attr->md_out.y = rtscam_md_read(md, MD_OUT_START_Y);
	attr->md_out.scale_x = rtscam_md_read(md, MD_OUT_SCALE_X);
	attr->md_out.scale_y = rtscam_md_read(md, MD_OUT_SCALE_Y);

	attr->roi.x = rtscam_md_read(md, MD_ROI_START_X);
	attr->roi.y = rtscam_md_read(md, MD_ROI_START_Y);
	attr->roi.w = rtscam_md_read(md, MD_ROI_END_X) - attr->roi.x;
	attr->roi.h  = rtscam_md_read(md, MD_ROI_END_Y) - attr->roi.y;

	attr->nr_bins = (enum RTSMD_NR_BINS)rtscam_md_read(md, MD_NR_BINS);
	attr->bin_bits = (enum RTSMD_BIN_BITS)rtscam_md_read(md, MD_BIN_BITS);
	attr->train_frames = rtscam_md_read(md, MD_TRAIN_FRAMES);

	attr->thd.back = rtscam_md_read(md, MD_BACK_THD);
	attr->thd.learn = rtscam_md_read(md, MD_LEARN_THD);
	attr->thd.forget = rtscam_md_read(md, MD_FORGET_THD);
	attr->thd.ds = rtscam_md_read(md, MD_OUT_DS_THD);
	attr->thd.motion = rtscam_md_read(md, MD_MOTION_THD);
}

static void __md_trigger_train(struct rtscam_md *md)
{
	rtscam_md_write(md, MD_TRAIN, 1);
}

static void __md_set_dma_buffer(struct rtscam_md *md,
				struct rtscam_md_buffer *p)
{
	if (!md || !p)
		return;

	rtscam_md_write(md, MD_HIST_ADDR, p->hist_addr);
	rtscam_md_write(md, MD_HIST_LEN, p->hist_length);

	rtscam_md_write(md, MD_RESULT_ADDR, p->res_addr);
	rtscam_md_write(md, MD_RESULT_LEN, p->res_length);

	md_debug("md set dma buffer: 0x%x %d, res 0x%x %d\n",
		p->hist_addr, p->hist_length, p->res_addr, p->res_length);
}

static void __md_set_axi_buffer(struct rtscam_md *md,
				struct rtscam_md_buffer *p)
{
	if (!md || !p)
		return;

	rtscam_md_write(md, MD_HIST_AXI_ADDR, p->hist_addr);
	rtscam_md_write(md, MD_HIST_AXI_LEN, p->hist_length);

	rtscam_md_write(md, MD_RESULT_AXI_ADDR, p->res_addr);
	rtscam_md_write(md, MD_RESULT_AXI_LEN, p->res_length);

	md_debug("md set axi buffer: 0x%x %d, res 0x%x %d\n",
		p->hist_addr, p->hist_length, p->res_addr, p->res_length);
}

static void __md_get_result(struct rtscam_md *md,
				struct rtscam_md_result *p)
{
	if (!md || !p)
		return;

	p->motion_flag = rtscam_md_read(md, MD_FLAG);
	p->motion_count = rtscam_md_read(md, MD_MOTION_PIX_CNT);
}

static unsigned int rtscam_isp_md_poll(struct rtscam_md *md, void *args)
{
	unsigned int mask = 0, ret;
	unsigned long timeout = (unsigned long)args;

	//if (test_bit(MD_FRAME_DONE_BIT, &md->status)) {
		if (timeout != osWaitForever)
			timeout = timeout * portTICK_RATE_MS;

		//osMutexRelease(md->lock);
		xSemaphoreGive(md->lock);
		__disable_md_busy(md);
//		ret = osSemaphoreAcquire(md->wq, timeout);
//		if (ret) {
		if (xSemaphoreTake(md->wq, timeout) != pdTRUE) {
			isp_error("rtscam_isp_md_poll wait md->wq timeout\n\r");
			return -ERESTARTSYS;
		}
		__enable_md_busy(md);

		if (xSemaphoreTake(md->lock, timeout) != pdTRUE) {
			isp_error("rtscam_isp_md_poll wait md->lock timeout\n\r");
			return -ERESTARTSYS;
		}


	if (md->intr_flag & MD_INT_MASK_OL)
		mask |= POLLERR;
	if (md->intr_flag & MD_INT_MASK_RESULT)
		mask |= (POLLIN | POLLRDNORM);
	return mask;
}

static long rtscam_isp_md_do_ioctl(int fd, unsigned int cmd,
				void *arg)
{
	struct rtscam_md *md = &gbl_md;
	int ret = 0;

	md_debug("ioctl cmd 0x%08x, '%c' %d.\n",
			cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));

	if (_IOC_TYPE(cmd) != RTSMD_IOC_MAGIC)
		return -ENOTTY;

	if (_IOC_NR(cmd) > RTSMD_IOC_MAXNR)
		return -ENOTTY;

	if (xSemaphoreTake(md->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_md_do_ioctl wait md->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	switch (cmd) {
	//case RTSMD_IOC_HWOFFSET:
	//	*(unsigned long *)arg = md->res.io_start;
	//	break;
	//case RTSMD_IOC_HWIOSIZE:
	//	*(unsigned int *)arg = md->res.io_size;
	//	break;
	case RTSMD_IOC_ENABLE:
		MD_OPS(md->ops->enable_clk, md, 1);
		MD_OPS(md->ops->enable, md, 1);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_DISABLE:
		MD_OPS(md->ops->enable_clk, md, 1);

		if (md->skip_completion_needed) {
			if (rtscam_md_read(md, MD_ENABLE_SKIP)) {
				__disable_md_busy(md);
				rtscam_md_write(md, MD_ENABLE_SKIP, 0);
				//init_completion(&md->skip_completion);
				md->skip_completion_flag = 1;
				//ret = wait_for_completion_timeout(
				//	&md->skip_completion, 3000 * HZ / 1000);
				//if (ret <= 0)
				//	md_err("md2 wait for skip fail\n");
				//ret = ret > 0 ? 0 : -EINVAL;
//				ret = osSemaphoreAcquire(md->skip_completion, ISP_SEM_TIMEOUT);
				ret = xSemaphoreTake(md->skip_completion, ISP_SEM_TIMEOUT);
				if (ret != pdTRUE) {
					ret = -EINVAL;
					isp_error("RTSMD_IOC_DISABLE wait md->skip_completion timeout\n\r");
				}
			}
		}

		MD_OPS(md->ops->enable, md, 0);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	//case RTSMD_IOC_ENABLE_CLK:
	//	MD_OPS(md->ops->enable_clk, md, 1);
	//	break;
	//case RTSMD_IOC_DISABLE_CLK:
	//	MD_OPS(md->ops->enable_clk, md, 0);
	//	break;
	case RTSMD_IOC_DONE:
		{
			//u32 b;

			MD_OPS(md->ops->enable_clk, md, 1);
			md->intr_flag = 0;
//			clear_bit(MD_FRAME_DONE_BIT, &md->status);
			//b = __md_read_reg(md, MD_REG_BIN_CTRL);
			//__md_write_reg(md, MD_REG_BIN_CTRL,
			//		b & (~MD_BIN_CTRL_MASK_PAUSE));
//			__disable_md_busy(md);
			MD_OPS(md->ops->enable_clk, md, 0);
		}
		break;
	case RTSMD_IOC_STATUS:
		*(unsigned int *) arg = md->intr_flag;
		break;
	case RTSMD_IOC_SET_EXTRA_ATTR:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_set_extra_attr(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_SET_ATTR:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_set_attr(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_GET_ATTR:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_get_attr(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_TRIGGER_TRAIN:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_trigger_train(md);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_SET_DMA_ADDR:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_set_dma_buffer(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_SET_AXI_BUFFER:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_set_axi_buffer(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;
	case RTSMD_IOC_GET_RESULT:
		MD_OPS(md->ops->enable_clk, md, 1);
		__md_get_result(md, arg);
		MD_OPS(md->ops->enable_clk, md, 0);
		break;

	case RTSMD_IOC_POLL:
		ret = rtscam_isp_md_poll(md, arg);
		break;
	default:
		md_err("unrecognized cmd 0x%08x, '%c' %d\n",
				cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	//osMutexRelease(md->lock);
	xSemaphoreGive(md->lock);
	return ret;
}


long rtscam_isp_md_ioctl(int fd, unsigned int cmd, void *arg)
{
	return rtscam_isp_md_do_ioctl(fd, cmd, arg);
}

/*
static unsigned int rtscam_isp_md_poll(int fd,
				struct poll_table_struct *wait)
{
	struct rtscam_md *md = filp->private_data;
	u32 mask = 0;
	unsigned long req_events = poll_requested_events(wait);

	if (!(req_events & (POLLIN | POLLRDNORM)))
		return mask;

	if (!test_bit(MD_FRAME_DONE_BIT, &md->status))
		poll_wait(filp, &md->wq, wait); //enq to wq only, not wait event
	else
		goto out;

	if (test_bit(MD_FRAME_DONE_BIT, &md->status))
		goto out;
	else
		return 0;

out:
	if (md->intr_flag & MD_INT_MASK_OL)
		mask |= POLLERR;
	if (md->intr_flag & MD_INT_MASK_RESULT)
		mask |= (POLLIN | POLLRDNORM);
	return mask;
}

static int rtscam_isp_md_mmap(struct file *filp, struct vm_area_struct *vm)
{
	struct rtscam_md *md = filp->private_data;
	unsigned long addr, size, start, end;

	addr = vm->vm_pgoff << PAGE_SHIFT;
	size = vm->vm_end - vm->vm_start;
	start = md->res.io_start;
	end = start + PAGE_ALIGN(md->res.io_size);

	if (addr < start || (addr + size) > end)
		return -EINVAL;

	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff,
			size, vm->vm_page_prot) ? -EAGAIN : 0;
}
*/

//static struct rtscam_ge_file_operations m_ge_ops = {
//	.owner = THIS_MODULE,
//	.open = rtscam_isp_md_open,
//	.release = rtscam_isp_md_close,
//	.ioctl = rtscam_isp_md_ioctl,
//	.poll = rtscam_isp_md_poll,
//	//.mmap = rtscam_isp_md_mmap,
//};

/*
static int __create_device(struct rtscam_md *md)
{
	struct rtscam_ge_device *gdev;
	int ret;

	if (md->gdev)
		return 0;

	gdev = rtscam_ge_device_alloc();
	if (!gdev)
		return -ENOMEM;

	strlcpy(gdev->name, RTS_ISP_MD_DEV_NAME, sizeof(gdev->name));
	gdev->parent = get_device(md->dev);
	gdev->release = rtscam_ge_device_release;
	gdev->fops = &m_ge_ops;

	rtscam_ge_set_drvdata(gdev, md);
	ret = rtscam_ge_register_device(gdev);
	if (ret) {
		rtscam_ge_device_release(gdev);
		return ret;
	}

	md->gdev = gdev;
	return 0;
}

static void __remove_device(struct rtscam_md *md)
{
	struct rtscam_ge_device *gdev;

	if (!md || !md->gdev)
		return;

	gdev = md->gdev;
	put_device(gdev->parent);
	rtscam_ge_unregister_device(gdev);
}
*/

static int __parse_of_cfg(struct rts_hw_buffer_cfg cfg[2])
{
#if 0
	cfg[0].start = 0x2e00;
	cfg[0].size = 0xa00;
	cfg[1].start = 0x3800;
	cfg[1].size = 0x200;
#else
	cfg[0].start = hal_isp_get_axi_buf_addr(MD0_BUF);
	cfg[0].size = hal_isp_get_axi_buf_size(MD0_BUF);
	cfg[1].start = hal_isp_get_axi_buf_addr(MD1_BUF);
	cfg[1].size = hal_isp_get_axi_buf_size(MD1_BUF);
#endif
	//printf("md icbuf 1 <0x%x 0x%x>\n", cfg[0].start, cfg[0].size);
	//printf("md icbuf 2 <0x%x 0x%x>\n", cfg[1].start, cfg[1].size);

	return 0;
}


int rtscam_isp_md_probe(void)
{
	struct rtscam_md *md = NULL;
//	struct resource *res;
//	int irq;
	int ret = 0;
	//struct device *dev = &pdev->dev;
	struct rtscam_isp_mfd *mfd;

//	osSemaphoreAttr_t mdwqAttr = { .name = "mdwqSemaphore" };

	const osMutexAttr_t mdlock_Mutex_attr = {
	  "mdlockMutex",                          // human readable mutex name
	  osMutexRecursive | osMutexPrioInherit,    // attr_bits
	  NULL,                         // memory for control block   
	  0U                   // size for control block
	};

	mfd = rtscam_get_isp_mfd();  //dev_get_drvdata(dev->parent);
	if (!mfd)
		return -EINVAL;

	md = &gbl_md;

//	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
//	irq = platform_get_irq(pdev, 0);
//	if (!res || irq < 0) {
//		md_err("get resource failed");
//		if (irq < 0)
//			md_err(" irq[%d]", irq);
//		md_err("\n");
//		ret = -ENODEV;
//		goto failed;
//	}
//
	ret = __parse_of_cfg(md->icfg);
	if (ret) {
		md_err("parse err [%d].\n", ret);
		goto failed;
	}

	//md->res.io_start = MD_BASE&(~0xA0000000);
	//md->res.io_size = 0x1000;
	//md->res.reg_base = (void*)MD_BASE;
	//md->res.irq = VIDEOIN_IRQn;

	//md_info("irq %d\n", md->res.irq);
	//md_info("io_start 0x%lx\n", md->res.io_start);
	//md_info("io_size 0x%x\n", md->res.io_size);
	//md_info("reg_base 0x%p\n", md->res.reg_base);
	//if (of_device_is_compatible(dev->of_node, "realtek,rts3915-md"))
	md->skip_completion_needed = 1;

	//md->dev = get_device(&pdev->dev);
	md->ops = &m_md_ops;
	atomic_set_isp(&md->use_count, 0);
	//mutex_init(&md->lock);
	md->lock = osMutexNew(&mdlock_Mutex_attr);
	if ( !md->lock ) {
		md_err("md->lock mutex alloc fail\n");
		ret = RTS_FAIL;
		goto failed;
	}

//	init_waitqueue_head(&md->wq);
	//md->wq = osSemaphoreNew(1, 0, &mdwqAttr);
	md->wq = xSemaphoreCreateCounting(1, 0);

	if (md->wq == NULL) {
		md_err("md->wq semaphore alloc fail\n");
		ret = RTS_FAIL;
		goto failed;
	}
	md->mfd = mfd;

	ret = mfd->register_irq(mfd, (void *)md, md->ops->irq, NULL);
	if (ret) {
		md_err("regist irq to mfd failed [%d].\n", ret);
		goto failed;
	}
	//RLX_ClearPendingIRQ(VIDEOIN_IRQn);
	//RLX_SetVideoInIrqVector(VIDEOIN_ID_MD, (u32)md->ops->irq);
	//RLX_DisableVideoInIRQ(VIDEOIN_ID_MD);

//	ret = __create_device(md);
//	if (ret) {
//		md_err("create device failed [%d].\n", ret);
//		goto failed;
//	}

	//platform_set_drvdata(pdev, md);

	printf("md init success\n\r");
	return 0;

failed:
//	if (md && md->dev) {
//		put_device(md->dev);
//		md->dev = NULL;
//	}
	return ret;
}

int rtscam_isp_md_remove(void)
{
	extern xTaskHandle md2_handle;
	extern osSemaphoreId mdgetbuf;
	
	if(md2_handle == NULL) {
		printf("md ready done\n\r");
		return 0;
	}
	md2_sighandle();



	if (mdgetbuf != NULL) {
		//		osSemaphoreRelease(mdgetbuf);
        xSemaphoreGive(mdgetbuf);
	}

	md2_wait_task_delete();

	md2_handle = NULL;
	printf("md remove\n\r");

	return 0;
}

//static struct platform_driver rtscam_isp_md_driver = {
//	.driver = {
//		.name = RTS_ISP_MD_DRV_NAME,
//		.owner = THIS_MODULE,
//	},
//
//	.probe = rtscam_isp_md_probe,
//	.remove = rtscam_isp_md_remove,
//};
//
//module_platform_driver(rtscam_isp_md_driver);
//
//MODULE_DESCRIPTION("Realsil isp md device driver");
//MODULE_AUTHOR("Anakin Wang <anakin_wang@realsil.com.cn>");
//MODULE_LICENSE("GPL v2");
//MODULE_VERSION("0.1.0");
//MODULE_ALIAS("platform:" RTS_ISP_MD_DRV_NAME);
