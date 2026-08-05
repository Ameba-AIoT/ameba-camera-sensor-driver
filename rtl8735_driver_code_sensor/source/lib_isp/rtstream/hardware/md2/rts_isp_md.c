/*
 * Realtek Semiconductor Corp.
 *
 * rtstream/md/rts_isp_md.c
 *
 * Copyright (C) 2019      Anakin Wang<anakin_wang@realsil.com.cn>
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "cmsis_os2.h"
#include <linux/poll.h>
#include "linux/v4l2-osdep.h"
#include "rts_ioctl.h"
#include <isp_utils.h>

//#define open rts_open
//#define close rts_close
#define ioctl rts_ioctl

#include <rts_camera_md.h>
#include <rtscamkit.h>
#include <rtsc.h>

#include "rts_isp_md.h"
#include "isp_log.h"

#define DEV_MD "/dev/rtsmd"

#define RET(x) return RTS_RETURN(RTS_E_##x)

struct rtsmd {
	int fd;
	int flag_enable;
};

int rts_isp_md_done(void *md)
{
	struct rtsmd *p = md;
	int ret;

	ret = ioctl(p->fd, RTSMD_IOC_DONE);
	if (ret) {
		RTS_ERR("ioctl fail[%d]\n", ret);
		RET(CMD_ERROR);
	}

	return RTS_OK;
}

static struct rts_isp_md_extra_attr def_e_attr = {
	.burst_length = {
		.hist_write = 1,
		.res_write = 1,
		.isp_read = 1,
	},

	.skip = {
		.enable = 0,
		.frames = 5,
	},
};

int rts_isp_md_set_extra_attr(void *p, struct rts_isp_md_extra_attr *attr)
{
	struct rtsmd *md = p;
	struct rtscam_md_extra_attr md_attr;
	int ret;

	if (!p || !attr)
		RET(NULL_POINT);

	if (sizeof(*attr) != sizeof(md_attr))
		RET(INVALID_ARG);

	memcpy(&md_attr, attr, sizeof(md_attr));

	ret = ioctl(md->fd, RTSMD_IOC_SET_EXTRA_ATTR, &md_attr);
	if (ret) {
		isp_error("ioctl SET_EXTRA_ATTR failed[%d]\n", ret);
		RET(IOCTL);
	}
	return RTS_OK;
}

int rts_isp_md_trigger_train(void *p)
{
	struct rtsmd *md = p;
	int ret;

	if (!md)
		RET(NULL_POINT);

	ret = ioctl(md->fd, RTSMD_IOC_TRIGGER_TRAIN);
	if (ret) {
		isp_error("ioctl TRIGGER_TRAIN failed[%d]\n", ret);
		RET(IOCTL);
	}
	return RTS_OK;
}

int rts_isp_md_get_fd(void *p)
{
	struct rtsmd *md = p;

	if (!md)
		RET(NULL_POINT);

	return md->fd;
}

static void to_nr_bins(enum MD_NR_BINS *cfg, int *nrbins, int reverse)
{
	if (!reverse) {

		switch (*cfg) {
		case MD_NR_BINS_32:
			*nrbins = 32;
			break;
		default:
			*nrbins = 16;
			break;
		}

	} else {
		if (*nrbins == 32)
			*cfg = MD_NR_BINS_32;
		else
			*cfg = MD_NR_BINS_16;
	}

}

static void to_bin_bits(enum MD_BIN_BITS *cfg, int *bin_bits, int reverse)
{
	if (!reverse) {
		switch (*cfg) {
		case MD_BIN_BITS_4:
			*bin_bits = 4;
			break;
		default:
			*bin_bits = 2;
			break;
		}
	} else {
		if (*bin_bits == 4)
			*cfg = MD_BIN_BITS_4;
		else
			*cfg = MD_BIN_BITS_2;
	}
}


int rts_isp_md_calc_dma_size(struct rts_isp_md_attr *cfg,
			uint32_t *hist_sz, uint32_t *res_sz)
{

	int nr_bins, bin_bits;

	if (!cfg)
		RET(NULL_POINT);

	to_nr_bins(&cfg->nr_bins, &nr_bins, 0);
	to_bin_bits(&cfg->bin_bits, &bin_bits, 0);

	*hist_sz = RTS_ALIGN(cfg->md_in.w * cfg->md_in.h
				* bin_bits * nr_bins / 8, 4096);
	*res_sz = RTS_ALIGN(cfg->md_out.w * cfg->md_out.h / 8, 4096);

	isp_info("md calc dma len: %d %d\n", *hist_sz, &res_sz);

	return RTS_OK;
}

int rts_isp_md_set_dma_addr(void *p,
		uint32_t hist_addr, uint32_t hist_length,
		uint32_t res_addr, uint32_t res_length)
{
	struct rtscam_md_buffer dma;
	struct rtsmd *md = p;
	int ret;

	if (!p)
		RET(NULL_POINT);

	dma.hist_addr = hist_addr;
	dma.hist_length = hist_length;
	dma.res_addr = res_addr;
	dma.res_length = res_length;

	ret = ioctl(md->fd, RTSMD_IOC_SET_DMA_ADDR, &dma);
	if (ret)
		isp_error("ioctl RTSMD_IOC_SET_DMA_ADDR failed[%d]\n", ret);

	return ret;
}

int rts_isp_md_set_axi_buffer(void *p,
		uint32_t hist_addr, uint32_t hist_len,
		uint32_t result_addr, uint32_t result_len)
{
	struct rtscam_md_buffer axi;
	struct rtsmd *md = p;
	int ret;

	if (!p)
		RET(NULL_POINT);

	axi.hist_addr = hist_addr;
	axi.hist_length = hist_len;
	axi.res_addr = result_addr;
	axi.res_length = result_len;

	ret = ioctl(md->fd, RTSMD_IOC_SET_AXI_BUFFER, &axi);
	if (ret)
		isp_error("ioctl RTSMD_IOC_SET_DMA_ADDR failed[%d]\n", ret);

	return ret;
}

int rts_isp_md_set_attr(void *p, struct rts_isp_md_attr *cfg)
{
	struct rtscam_md_attr attr;
	struct rtsmd *md = p;
	int ret;

	if (!p || !cfg)
		RET(NULL_POINT);

	if (sizeof(*cfg) != sizeof(attr))
		RET(INVALID_ARG);

	memcpy(&attr, cfg, sizeof(attr));

	ret = ioctl(md->fd, RTSMD_IOC_SET_ATTR, &attr);
	if (ret)
		isp_error("ioctl RTSMD_IOC_SET_ATTR failed[%d]\n", ret);

	return ret;
}

int rts_isp_md_get_attr(void *p, struct rts_isp_md_attr *cfg)
{
	struct rtscam_md_attr attr;
	struct rtsmd *md = p;
	int ret;

	if (!md || !cfg)
		RET(NULL_POINT);

	if (sizeof(*cfg) != sizeof(attr))
		RET(INVALID_ARG);

	ret = ioctl(md->fd, RTSMD_IOC_GET_ATTR, &attr);
	if (ret) {
		isp_error("ioctl RTSMD_IOC_GET_ATTR failed[%d]\n", ret);
		return ret;
	}

	memcpy(cfg, &attr, sizeof(*cfg));
	return RTS_OK;
}

void rts_isp_md_release(void *p)
{
	struct rtsmd *md = p;

	if (!md)
		return;

	if (md->fd > 0)
		rts_close(md->fd);

	if (md)
		rts_free(md);
}


int rts_isp_md_init(void **omd)
{
	struct rtsmd *md = rts_calloc(1, sizeof(*md));
	int ret = 0;


	if (!md)
		RET(NO_MEMORY);

	md->fd = rts_open(DEV_MD);
	if (md->fd < 0) {
		isp_error("open fd failed[%d]\n", ret);
		ret = RTS_RETURN(RTS_E_OPEN_FAIL);
		goto failed;
	}

	rts_isp_md_set_extra_attr(md, &def_e_attr);

	*omd = md;
	return RTS_OK;

failed:
	rts_isp_md_release(md);
	return ret;
}

int rts_isp_md_enable(void *md, int enable)
{
	struct rtsmd *p = md;
	int ret = 0;

	if (!md)
		RET(NULL_POINT);

	if (enable) {
		//rtsmd_writer(p, MD_RESET_BUF, 0);
		ret = ioctl(p->fd, RTSMD_IOC_ENABLE);
	} else {
		ret = ioctl(p->fd, RTSMD_IOC_DISABLE);
		//rtsmd_writer(p, MD_RESET_BUF, 1);
	}

	if (ret) {
		isp_error("ioctl fail[%d]\n", ret);
		RET(CMD_ERROR);
	}

	p->flag_enable = enable;
	return RTS_OK;
}

int rts_isp_md_get_result(void *p, struct rts_isp_md_result *res)
{
	struct rtscam_md_result result;
	struct rtsmd *md = p;
	int ret;

	if (!md || !res)
		RET(NULL_POINT);

	ret = ioctl(md->fd, RTSMD_IOC_GET_RESULT, &result);
	if (ret) {
		isp_error("ioctl RTSMD_IOC_GET_RESULT failed[%d]\n", ret);
		return ret;
	}

	res->motion_flag = result.motion_flag;
	res->motion_count = result.motion_count;

	return RTS_OK;
}

int rts_isp_md_alloc_dma(struct rtsc_dma_buffer *b)
{
	int ret=0;

	if (!b)
		RET(NULL_POINT);

	b->buf_io = RTSC_BUF_FROM_DEVICE;
	b->length = RTS_ALIGN(b->length, 4096);

	b->phy_addr = (uint32_t)rts_malloc(b->length);
	if (!b->phy_addr)
		return RTS_E_NO_MEMORY;

	b->phy_addr = (uint32_t)(ALIGN((int)b->phy_addr, 32));

	isp_info("md alloc dma len %d, ret %d\n", b->length, ret);

	if (RTS_IS_ERR(ret))
		return ret;

	return RTS_OK;
}

void rts_isp_md_free_dma(struct rtsc_dma_buffer *b)
{
	rts_free((void *)b->phy_addr);
	isp_info("md free dma\n");
}

int rts_isp_md_poll(void *p, int timeout_ms)
{
	return RTS_FALSE;
}

int rts_isp_md_poll2(void *p, int timeout_ms, uint32_t *status)
{
	struct rtsmd *md = p;
	int ret = 0;
	//wait event until timeout_ms & update status if socket error occured
	ret = ioctl(md->fd, RTSMD_IOC_POLL, timeout_ms);
	if (ret < 0) {
		isp_error("get md status failed (%d)\n", ret);
		return RTS_FALSE;
	}

	if (status) {
		*status = 0;
		if (ret & POLLERR) {
			ret = ioctl(md->fd, RTSMD_IOC_STATUS, status);
			if (ret < 0)
				isp_error("get md status failed (%d)\n", ret);
		}
	}

	return RTS_TRUE;
}
