/*
 * Realtek Semiconductor Corp.
 *
 * rtsosd2/ewl/ewl_osd2_common.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
//#include <stdio.h>
#include <stdint.h>
#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include <linux/rts_camera_osd2.h>
#include <rtscamkit.h>
#include <rtsc.h>
#include "rts_ioctl.h"
#include "osd2ewl.h"
#include "ewl_osd2_common.h"
#include "osd2register.h"
#include "rtx_mutex.h"
#include "isp_log.h"
struct rts_osd2_ewl_t gbl_osd2_ewl={0};
extern osMutexId_t ewl_lock;

const void *osd2_ewl_init(void)
{
	struct rts_osd2_ewl_t *ewl = NULL;
	//key_t key = 0x0831;
	int ret;
	RtsRegInst reginst;

	ewl = &gbl_osd2_ewl;
	if (ewl->inited == TRUE) {
		return ewl;
	}


	ewl->lock = ewl_lock;
	if ( !ewl->lock ) {
		isp_error("osd2 ewl: ewl->lock alloc fail\n");
		goto error;
	}

	ret = rtsc_reg_osd2_open(&reginst);
	if (ret) {
		isp_error("ewl: failed to open osd2 reg\n");
		goto error;
	}
	ewl->reginst = reginst;

	ret = rtsc_reg_osd2_set_enabled(ewl->reginst, 1);
	if (ret) {
		isp_error("ewl: failed to enable osd2 encoder\n");
		goto error;
	}

	ewl->inited = TRUE;
	return ewl;
error:
//	if (ewl->lock) osMutexDelete(ewl->lock);
	if (ewl->lock) {
		vSemaphoreDelete(ewl->lock);
		ewl->lock = NULL;
		ewl_lock = NULL;
	}

	osd2_ewl_release(ewl);
	isp_error("ewl %s fail, return NULL\n", __func__);
	return NULL;
}

int osd2_ewl_release(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl || ewl->inited == FALSE)
		return RTS_OK;

	rtsc_reg_osd2_set_enabled(ewl->reginst, 0);
	RTS_SAFE_RELEASE(ewl->reginst, rtsc_reg_osd2_close);
	//osMutexDelete(ewl->lock);
	if (ewl->lock) {
		vSemaphoreDelete(ewl->lock);
		ewl->lock = NULL;
		ewl_lock = NULL;
	}
	ewl->inited = FALSE;

	return RTS_OK;
}

uint32_t osd2_ewl_read_reg(const void *inst, uint32_t offset)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;
	uint32_t val;

	if (!ewl || !ewl->reginst)
		return 0;

	val = rtsc_reg_read_reg(ewl->reginst, offset);

	return val;
}

void osd2_ewl_write_reg(const void *inst, uint32_t offset, uint32_t val)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl || !ewl->reginst)
		return ;

	rtsc_reg_write_reg(ewl->reginst, offset, val);
}

int32_t osd2_ewl_reserve_hw(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;
	int ret;

	if (!ewl || !ewl->reginst)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	ret = xSemaphoreTake(ewl->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("wq lock wait fail, ret = %d\r\n", ret);
		return RTS_RETURN(RTS_E_LOCK_FAIL);
	}

	rts_osd2_set_register(ewl, OSD2_REG_PAINTER_STOP, 1);


	if (!rts_osd2_get_register(ewl, OSD2_REG_PAINTER_IDLE)) {
		isp_error("osd painter is busy\n");
		if (pdTRUE != xSemaphoreGive(ewl->lock))
			isp_error("osd2 ewl: Release HW failed\n");
		return RTS_RETURN(RTS_E_INUSE);
	}
	return RTS_OK;
}

void osd2_ewl_release_hw(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl || !ewl->reginst)
		return ;

	rts_osd2_set_register(ewl, OSD2_REG_PAINTER_STOP, 1);

	if (pdTRUE != xSemaphoreGive(ewl->lock))
		isp_error("osd2 ewl: Release HW failed\n");
}

void osd2_ewl_start_hw(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl || !ewl->reginst)
		return;

	rts_osd2_set_register(ewl, OSD2_REG_PAINTER_START, 1);
}

int osd2_ewl_check_done(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;
	uint32_t val;

	if (!ewl)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	val = rts_osd2_get_register(ewl, OSD2_REG_PAINTER_IDLE);
	if (val)
		return RTS_OK;
	else
		return RTS_RETURN(RTS_E_NOT_READY);
}

static int __osd2_ewl_done(struct rts_osd2_ewl_t *ewl)
{
	int ret;

	rtsc_reg_osd2_done(ewl->reginst);

	if (rts_osd2_get_register(ewl, OSD2_REG_CMD_ERROR)) {
		printf("OSD2_REG_CMD_ERROR \n");
		rts_osd2_set_register(ewl, OSD2_REG_CMD_ERROR, 1);
		ret = RTS_RETURN(RTS_E_CMD_ERROR);
	} else if (rts_osd2_get_register(ewl, OSD2_REG_VALID_ERROR)) {
		printf("OSD2_REG_VALID_ERROR \n");
		rts_osd2_set_register(ewl, OSD2_REG_VALID_ERROR, 1);
		ret = RTS_RETURN(RTS_E_INVALID_CMD);
	} else if (rts_osd2_get_register(ewl, OSD2_REG_BUSRD_MISMATCH)) {
		printf("OSD2_REG_BUSRD_MISMATCH \n");
		rts_osd2_set_register(ewl, OSD2_REG_BUSRD_MISMATCH, 1);
		ret = RTS_RETURN(RTS_E_MISMATCH);
	} else if (rts_osd2_get_register(ewl, OSD2_REG_BUF_OVERFL)) {
		printf("OSD2_REG_BUF_OVERFL \n");
		rts_osd2_set_register(ewl, OSD2_REG_BUF_OVERFL, 1);
		ret = RTS_RETURN(RTS_E_OVERFLOW);
	} else {
		ret = RTS_OK;
	}

	return ret;
}

static int osd2_ewl_wait_rdy(struct rts_osd2_ewl_t *ewl)
{
	int fd;

	fd = rts_open("/dev/rtsosd2");
	if (fd < 0) {
		isp_error("Can't open /dev/rtsosd2\n");
		return RTS_RETURN(RTS_E_OPEN_FAIL);
	}
	(void)rts_ioctl(fd, RTSOSD2_IOC_WAIT_INTERRUPT, osWaitForever);
	rts_close(fd);

	return __osd2_ewl_done(ewl);
}

int32_t osd2_ewl_wait_hw_ready(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;
	int32_t ret = RTS_RETURN(RTS_E_TIMEOUT);

	if (!ewl)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	ret = osd2_ewl_wait_rdy(ewl);

	return ret;
}

int osd2_ewl_use_inter(const void *inst, int inter_need)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	ewl->e_count = 0;
	ewl->t_count = 0;

	return RTS_OK;
}

int osd2_ewl_print(const void *inst)
{
	struct rts_osd2_ewl_t *ewl = (struct rts_osd2_ewl_t *)inst;

	if (!ewl)
		return RTS_RETURN(RTS_E_INVALID_ARG);

	isp_info("[osd2]encode = %ld,timeout = %ld\n",
		ewl->e_count, ewl->t_count);
	return RTS_OK;
}
