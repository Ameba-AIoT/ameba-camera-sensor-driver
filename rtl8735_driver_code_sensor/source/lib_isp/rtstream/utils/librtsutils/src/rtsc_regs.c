/*
 * Realtek Semiconductor Corp.
 *
 * rtsutils/rtsc_regs.c
 *
 * Copyright (C) 2018      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "cmsis_os2.h"
#include "rt_task.h"
#include "linux/rts_camera_soc.h"
#include "rts_ioctl.h"
#define ioctl rts_ioctl
#include <rtscamkit.h>
#include "rts_camera_mcu.h"
#include "rts_camera_hx280enc.h"
#include "rts_camera_jpgenc.h"
#include "rts_camera_osd2.h"
#include "rtsc.h"
#include "rtx_mutex.h"
#include "isp_log.h"

#define RTSC_H1_H264_DEV		"/dev/rtshx280enc"
#define RTSC_MJPG_DEV			"/dev/rtsjpgenc"
#define RTSC_OSD2_DEV			"/dev/rtsosd2"

enum {
	RTS_REG_IDX_ISP = 0,
	RTS_REG_IDX_H264,
	RTS_REG_IDX_MJPEG,
	RTS_REG_IDX_OSD2,
	RTS_REG_IDX_RESERVED
};

struct rtsc_reg {
	int fd;
	unsigned long start;
	unsigned int size;
	uint32_t *preg;
	const void *inst;
	const char *name;
	int refcount;
	int refcount_clk;
	osMutexId_t lock;
	int (*get_reg_info)(int *fd, unsigned long *, unsigned int *);
};

static int __osd2_reg_info(int *pfd, unsigned long *pbase, unsigned int *psize);

static struct rtsc_reg regs[RTS_REG_IDX_RESERVED] = {

	[RTS_REG_IDX_OSD2] = {
		.name = "osd2",
		.fd = -1,
		.get_reg_info = __osd2_reg_info,
		.lock = NULL,
		.refcount = 0,
		.refcount_clk = 0,
		.inst = &regs[RTS_REG_IDX_OSD2],
	},
};

extern osMutexId_t reg_inst_lock;

static int __lock_reg(struct rtsc_reg *reg_inst)
{
	if (!reg_inst->lock) {
		
		reg_inst->lock = reg_inst_lock;
		if (!reg_inst->lock) {
			printf("%s: mutex alloc fail\n", __func__);
			return RTS_RETURN(RTS_E_NOT_READY);
		}
	}
	if(xSemaphoreTake(reg_inst->lock, ISP_SEM_TIMEOUT) == pdTRUE) {
		return osOK;
	}
	else {
		return osErrorOS;
	}

}

static void __unlock_reg(struct rtsc_reg *reg_inst)
{
	if (reg_inst->lock)
		xSemaphoreGive(reg_inst->lock);
	else
		printf("%s: NULL error!\n", __func__);
}

static uint32_t __read_reg(struct rtsc_reg *reg_inst, unsigned int offset)
{
	if (!reg_inst || reg_inst != reg_inst->inst) {
		RTS_ERR("Invalid enc instance\n");
		return 0;
	}

	if (reg_inst->fd < 0) {
		RTS_WARNING("(%s)read reg(0x%x) after close\n",
			    reg_inst->name, offset);
		RTS_ERR("enc isn't open\n");
		return 0;
	}

	if (!reg_inst->preg) {
		RTS_WARNING("(%s) preg is NULL, reg(0x%x)\n",
			    reg_inst->name, offset);
		RTS_ERR("reg isn't mmap\n");
		return 0;
	}

	if (offset > reg_inst->size) {
		RTS_ERR("reg<%d> is out of range\n", offset);
		return 0;
	}

	RTS_LOG(RTS_LOG_REG, "[%s] R reg : 0x%08x\n", reg_inst->name, offset);

	if (offset % 4 != 0)
		RTS_WARNING("reg(%d) is not aligned\n");

	offset = offset / 4;
	return *(reg_inst->preg + offset);
}

static void __write_reg(struct rtsc_reg *reg_inst,
			unsigned int offset, uint32_t val)
{
	if (!reg_inst || reg_inst != reg_inst->inst) {
		RTS_ERR("Invalid enc instance\n");
		return;
	}

	if (reg_inst->fd < 0) {
		RTS_WARNING("(%s)write reg(0x%x) after close\n",
			    reg_inst->name, offset);
		RTS_ERR("enc isn't open\n");
		return;
	}

	if (!reg_inst->preg) {
		RTS_WARNING("(%s) preg is NULL, reg(0x%x)\n",
			    reg_inst->name, offset);
		RTS_ERR("reg isn't mmap\n");
		return;
	}

	if (offset > reg_inst->size) {
		RTS_ERR("reg<%d> is out of range\n", offset);
		return;
	}

	RTS_LOG(RTS_LOG_REG, "[%s] W reg : 0x%08x/0x%08x\n",
		reg_inst->name, offset, val);

	if (offset % 4 != 0)
		RTS_WARNING("reg(%d) is not aligned\n");

	offset = offset / 4;
	*(reg_inst->preg + offset) = val;
}

static void *rtsc_reg_mmap(int fd, unsigned long base, unsigned int size)
{
	return (void *)base;
}

static int __open_reg(struct rtsc_reg *reg_inst)
{
	int fd = -1;
	unsigned long iobase;
	unsigned int iosize;
	int ret;

	if (!reg_inst || !reg_inst->get_reg_info)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	ret =  reg_inst->get_reg_info(&fd, &iobase, &iosize);
	if (RTS_IS_ERR(ret))
		return ret;

	reg_inst->fd = fd;
	reg_inst->start = iobase;
	reg_inst->size = iosize;
	//printf ("[%s] Open start 0x%08x size 0x%08x\n", reg_inst->name, reg_inst->start, reg_inst->size);

	return RTS_OK;
}

int rtsc_reg_close(RtsRegInst reginst)
{
	struct rtsc_reg *reg_inst = (struct rtsc_reg *)reginst;
	unsigned int size;
	uint32_t *preg;
	int fd;
	int ret = 0;

	if (!reg_inst || reg_inst != reg_inst->inst) {
		RTS_ERR("Invalid enc instance\n");
		return RTS_RETURN(RTS_E_NULL_POINT);
	}

	ret = __lock_reg(reg_inst);
	if (ret != osOK) {
		isp_error("rtsc_reg_close __lock_reg fail\n\r");
		return -ETIMEDOUT;
	}
	if (reg_inst->fd < 0) {
		__unlock_reg(reg_inst);
		return RTS_OK;
	}

	if (reg_inst->refcount > 0) {
		reg_inst->refcount--;
		if (reg_inst->refcount == 0) {
			preg = reg_inst->preg;
			size = reg_inst->size;
			fd = reg_inst->fd;

			reg_inst->start = 0;
			reg_inst->size = 0;
			reg_inst->preg = 0;
			reg_inst->fd = -1;

			RTS_SAFE_CLOSE(fd, rts_close);
			RTS_LOG(RTS_LOG_REG, "[%s] Close\n", reg_inst->name);
		}
	}

	__unlock_reg(reg_inst);

	if (reg_inst->lock) {
		vSemaphoreDelete(reg_inst->lock);
		reg_inst->lock = NULL;
		reg_inst_lock = NULL;
	}

	return RTS_OK;
}

static int __osd2_reg_info(int *pfd, unsigned long *pbase, unsigned int *psize)
{
	int fd;
	unsigned long iobase;
	unsigned int iosize;
	int ret;

	if (!pfd || !pbase || !psize)
		return RTS_RETURN(RTS_E_NULL_POINT);

	fd = rts_open(RTSC_OSD2_DEV);
	if (fd < 0) {
		RTS_ERR("open osd2 device<%s> fail\n", RTSC_OSD2_DEV);
		ret = RTS_RETURN(RTS_E_OPEN_FAIL);
		goto error;
	}

	ret = ioctl(fd, RTSOSD2_IOCGHWOFFSET, &iobase);
	if (ret) {
		RTS_ERR("get osd2 hw reg base fail, errno = %d\n", ret);
		ret = RTS_RETURN(RTS_E_IOCTL);
		goto error;
	}
	ret = ioctl(fd, RTSOSD2_IOCGHWIOSIZE, &iosize);
	if (ret) {
		RTS_ERR("get osd2 hw reg size fail, errno = %d\n", ret);
		ret = RTS_RETURN(RTS_E_IOCTL);
		goto error;
	}

	*pfd = fd;
	*pbase = iobase;
	*psize = iosize;

	return RTS_OK;
error:
	RTS_SAFE_CLOSE(fd, rts_close);
	return ret;
}

uint32_t rtsc_reg_read_reg(RtsRegInst reginst, unsigned int offset)
{
	struct rtsc_reg *reg_inst = (struct rtsc_reg *)reginst;
	uint32_t val;

	if (__lock_reg(reg_inst) != osOK) {
		isp_error("rtsc_reg_read_reg __lock_reg fail\n\r");
		return 0;
	}
	val = __read_reg(reg_inst, offset);
	__unlock_reg(reg_inst);

	return val;
}

void rtsc_reg_write_reg(RtsRegInst reginst,
		       unsigned int offset, uint32_t val)
{
	struct rtsc_reg *reg_inst = (struct rtsc_reg *)reginst;

	if (__lock_reg(reg_inst) != osOK) {
		isp_error("rtsc_reg_write_reg __lock_reg fail\n\r");
		return;
	}
	__write_reg(reg_inst, offset, val);
	__unlock_reg(reg_inst);
}

static int __get_and_open_reg_by_index(int idx, RtsRegInst *reginst)
{
	struct rtsc_reg *reg_inst = NULL;
	int ret = RTS_OK;

	if (idx  < 0 || idx >= RTS_REG_IDX_RESERVED)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	reg_inst = &regs[idx];
	ret = __lock_reg(reg_inst);
	if (ret != osOK) {
		isp_error("__get_and_open_reg_by_index __lock_reg fail\n\r");
		return -ETIMEDOUT;
	}
	if (reg_inst->fd < 0 && reg_inst->refcount == 0) {
		ret = __open_reg(reg_inst);
		if (RTS_IS_ERR(ret)) {
			__unlock_reg(reg_inst);
			return ret;
		}
	}
	reg_inst->refcount++;
	__unlock_reg(reg_inst);

	if (reginst)
		*reginst = reg_inst;

	return ret;
}

int rtsc_reg_set_enabled(RtsRegInst reginst, int enable, int cmd1, int cmd2)
{
	struct rtsc_reg *reg_inst = (struct rtsc_reg *)reginst;
	int ret;
	uint32_t *preg = NULL;

	if (!reg_inst || reg_inst != reg_inst->inst) {
		isp_error("Invalid enc instance\n");
		return RTS_RETURN(RTS_E_INVALID_ARG);
	}

	ret = __lock_reg(reg_inst);
	if (ret != osOK) {
		isp_error("rtsc_reg_set_enabled __lock_reg fail\n\r");
		return -ETIMEDOUT;
	}
	if (reg_inst->fd < 0) {
		isp_error("[%s]: No register instance fd\n", reg_inst->name);
		ret = RTS_RETURN(RTS_E_INVALID_ARG);
		goto exit;
	}

	if ((enable && reg_inst->refcount_clk < 0) ||
			(!enable && reg_inst->refcount_clk <= 0)) {
		isp_error("[%s]: error refcount clk %d, status %d\n",
			reg_inst->name, reg_inst->refcount_clk, enable);
		ret = RTS_RETURN(RTS_E_INVALID_ARG);
		goto exit;
	}

	ret = RTS_OK;
	if (enable) {
		if (reg_inst->refcount_clk > 0) {
			reg_inst->refcount_clk++;
			goto exit;
		}
		reg_inst->refcount_clk++;
	} else {
		reg_inst->refcount_clk--;
		if (reg_inst->refcount_clk > 0)
			goto exit;
	}

	if (!enable) {
		reg_inst->preg = NULL;
	}

	if (enable)
		ret = ioctl(reg_inst->fd, cmd1);
	else
		ret = ioctl(reg_inst->fd, cmd2);

	if (ret < 0) {
		isp_error("[%s]: ioctl error: %d\n", reg_inst->name, ret);
		ret = RTS_RETURN(RTS_E_IOCTL);
		goto exit;
	}

	if (enable) {
		preg = rtsc_reg_mmap(reg_inst->fd,
				reg_inst->start, reg_inst->size);
		if (!preg) {
			isp_error("mmap(%s) reg fail %d 0x%08x 0x%08x \n", reg_inst->name, reg_inst->fd, reg_inst->start, reg_inst->size);
			ret = RTS_RETURN(RTS_E_MMAP_FAIL);
			goto exit;
		}
		reg_inst->preg = (uint32_t *)preg;
	}

	//printf("[%s] clock %s\n", reg_inst->name, enable ? "++enable" : "--disable");

	ret = RTS_OK;
exit:
	__unlock_reg(reg_inst);

	return ret;
}

int rtsc_reg_osd2_set_enabled(RtsRegInst reginst, int enable)
{
	return rtsc_reg_set_enabled(reginst, enable,
			RTSOSD2_IOC_ENABLE, RTSOSD2_IOC_DISABLE);
}

int rtsc_reg_osd2_open(RtsRegInst *reginst)
{
	return __get_and_open_reg_by_index(RTS_REG_IDX_OSD2, reginst);
}

int rtsc_reg_osd2_close(RtsRegInst osd2reg)
{
	return rtsc_reg_close(osd2reg);
}

void rtsc_reg_osd2_done(RtsRegInst reginst)
{
	struct rtsc_reg *reg_inst = (struct rtsc_reg *)reginst;

	if (!reg_inst || reg_inst != reg_inst->inst) {
		RTS_ERR("Invalid enc instance\n");
		return;
	}

	if (__lock_reg(reg_inst) != osOK) {
		isp_error("rtsc_reg_osd2_done __lock_reg fail");
		return;
	}
	if (reg_inst->fd < 0)
		goto exit;
	if (ioctl(reg_inst->fd, RTSOSD2_IOCDONE) < 0)
		RTS_ERR("ioctl fail\n");
exit:
	__unlock_reg(reg_inst);
}

