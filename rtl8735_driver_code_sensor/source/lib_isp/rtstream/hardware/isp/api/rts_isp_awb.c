/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rts_ioctl.h"
#include <rtscamkit.h>
#include <rts_isp.h>
#include <isp_atomic.h>
#include <isp_mod.h>
#include <isp_uds.h>
#include <isp_mod_awb.h>
#include <isp_mod_statis.h>
#include "rtx_mutex.h"

int rts_isp_query_awb_setting(uint32_t isp_id,
			      struct rts_isp_awb_setting **awb_setting)
{
	int ret;
	struct rts_isp_awb_setting *setting;

	if (isp_id >= _ISP_ID_NUM || !awb_setting)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(setting))
		return -RTS_ISP_ENOMEM;
	ret = rts_isp_get_awb_setting(isp_id, setting);
	if (ret) {
		isp_free(setting);
		return ret;
	}
	*awb_setting = setting;
	return RTS_ISP_OK;
}

int rts_isp_get_awb_setting(uint32_t isp_id,
			    struct rts_isp_awb_setting *awb_setting)
{
	return isp_uds_message_simple(isp_id, MOD_AWB, AWB_EXEC_GET_SETTING,
				      awb_setting, sizeof(*awb_setting));
}

int rts_isp_set_awb_setting(uint32_t isp_id,
			    struct rts_isp_awb_setting *awb_setting)
{
	return isp_uds_message_simple(isp_id, MOD_AWB, AWB_EXEC_SET_SETTING,
				      awb_setting, sizeof(*awb_setting));
}

void rts_isp_release_awb_setting(uint32_t isp_id,
				 struct rts_isp_awb_setting *awb_setting)
{
	isp_free(awb_setting);
}

//#define AWB_STATIS_LOCK_FILE "/var/lock/isp_awb_statis.lock"
//
struct rts_isp_awb_statis_ex {
	struct rts_isp_awb_statis statis;
	void *ptr;
	osMutexId_t lock;
	uint32_t size;
	//isp_atomic_t locked;
};

//static int awb_statis_lock_fd = -1;
//  static osMutexId_t awb_statis_mutex_lock = 0;
  extern void *gbl_awb_shm;

int rts_isp_get_awb_statis_info(uint32_t isp_id,
				struct rts_isp_awb_stat_info *info)
{
	int ret;
	struct isp_mod_awb_stat_info stat_info;

	if (isp_id > _ISP_ID_NUM || !info)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_AWB, AWB_INFO_STATIS,
				     &stat_info, sizeof(stat_info));
	if (ret)
		return ret;
	*info = stat_info.info;

	return RTS_ISP_OK;
}

int rts_isp_query_awb_statis(uint32_t isp_id,
			     const struct rts_isp_awb_statis **statis)
{
	int ret;
//	int fd = -1;
	struct rts_isp_awb_statis_ex *ex;
	struct isp_statis_buf_offset offset;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

/*
	if (!awb_statis_mutex_lock) {
		awb_statis_mutex_lock = xSemaphoreCreateMutex();
		if ( !awb_statis_mutex_lock ) {
			isp_perror(-1, "awb mutex alloc fail");
			return -1;
		}
	}

	xSemaphoreTake(awb_statis_mutex_lock, osWaitForever);
	if (awb_statis_lock_fd == -1)
		awb_statis_lock_fd = rts_open(AWB_STATIS_LOCK_FILE);
	xSemaphoreGive(awb_statis_mutex_lock);
*/


	if (!isp_calloc_item(ex))
		return -RTS_ISP_ENOMEM;

	ret = isp_uds_message_simple(isp_id, MOD_STATIS,
				     STATIS_INFO_BUF_OFFSET,
				     &offset, sizeof(offset));
	if (ret)
		goto err;
	ex->size = offset.awb.size + sizeof(osMutexId_t);
	ex->ptr = (void*)gbl_awb_shm;
	ex->lock = xSemaphoreCreateMutex();//*((osMutexId_t*)((u32)ex->ptr + offset.awb.size));
	if (!ex->lock) {
		isp_perror(-1, "awb NULL mutex");
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	ex->statis.r_mean = (uint16_t *)((u32)ex->ptr + offset.awb.r_offset - offset.awb.offset);
	ex->statis.g_mean = (uint16_t *)((u32)ex->ptr + offset.awb.g_offset - offset.awb.offset);
	ex->statis.b_mean = (uint16_t *)((u32)ex->ptr + offset.awb.b_offset - offset.awb.offset);
	ex->statis.y_mean = (uint16_t *)((u32)ex->ptr + offset.awb.y_offset - offset.awb.offset);
	ex->statis.rg = (uint16_t *)((u32)ex->ptr + offset.awb.rg_offset - offset.awb.offset);
	ex->statis.bg =(uint16_t *)((u32) ex->ptr + offset.awb.bg_offset - offset.awb.offset);
	ex->statis.pixels = (uint16_t *)((u32)ex->ptr + offset.awb.pixels_offset - offset.awb.offset);

	*statis = &ex->statis;

	return RTS_ISP_OK;
err:
	if (ex) {
		if (ex->lock) {
//			osMutexDelete(ex->lock);
			vSemaphoreDelete(ex->lock);
			ex->lock = NULL;
		}
		isp_free(ex);
	}
	return ret;
}

int rts_isp_get_awb_statis(uint32_t isp_id,
			   const struct rts_isp_awb_statis *statis)
{
	int ret;
	struct rts_isp_awb_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_awb_statis_ex, statis);

	//isp_atomic_bool_cmp_swap(&ex->locked, 0, 1);
	ret = xSemaphoreTake(ex->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rts_isp_get_awb_statis wait ex->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	ret = isp_uds_message_simple(isp_id, MOD_STATIS, STATIS_INFO_AWB_STAT,
				     &ex->statis, sizeof(ex->statis));
	//if (ret)
	//	xSemaphoreGive(ex->lock);

	return ret;
}

int rts_isp_put_awb_statis(uint32_t isp_id,
			   const struct rts_isp_awb_statis *statis)
{
	struct rts_isp_awb_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_awb_statis_ex, statis);
	xSemaphoreGive(ex->lock);

	return RTS_ISP_OK;
}

void rts_isp_release_awb_statis(uint32_t isp_id,
				const struct rts_isp_awb_statis *statis)
{
	struct rts_isp_awb_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return;

	ex = container_of(statis, struct rts_isp_awb_statis_ex, statis);
	xSemaphoreGive(ex->lock);
	//rts_isp_put_awb_statis(isp_id, statis);
	//osMutexDelete(ex->lock);
	if (ex->lock) {
		vSemaphoreDelete(ex->lock);
		ex->lock = NULL;
	}
	isp_free(ex);
}

