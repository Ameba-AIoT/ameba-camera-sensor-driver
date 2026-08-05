/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rts_ioctl.h"
#include <rtscamkit.h>
#include <rts_isp.h>
#include <isp_atomic.h>
#include <isp_mod.h>
#include <isp_uds.h>
#include <isp_mod_af.h>
#include <isp_mod_statis.h>
#include "rtx_mutex.h"

//#define AF_STATIS_LOCK_FILE "/var/lock/isp_af_statis.lock"
//
struct rts_isp_af_statis_ex {
	struct rts_isp_af_statis s;
	void *ptr;
	osMutexId_t lock;
	uint32_t size;
//	isp_atomic_t locked;
};

//static int af_statis_lock_fd = -1;
//  static osMutexId_t af_statis_mutex_lock = 0;
  extern void *gbl_af_shm;

int rts_isp_get_af_statis_info(uint32_t isp_id,
			       struct rts_isp_af_stat_info *info)
{
	int ret;
	struct isp_mod_af_stat_info stat_info;

	if (isp_id > _ISP_ID_NUM || !info)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_AF, AF_INFO_STATIS,
				     &stat_info, sizeof(stat_info));
	if (ret)
		return ret;
	*info = stat_info.info;

	return RTS_ISP_OK;
}

int rts_isp_query_af_statis(uint32_t isp_id,
			    const struct rts_isp_af_statis **statis)
{
	int ret;
//	int fd = -1;
	struct rts_isp_af_statis_ex *ex;
	struct isp_statis_buf_offset offset;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

/*
	if (!af_statis_mutex_lock) {
		af_statis_mutex_lock = xSemaphoreCreateMutex();
		if ( !af_statis_mutex_lock ) {
			isp_perror(-1, "af mutex alloc fail");
			return -1;
		}
	}

	xSemaphoreTake(af_statis_mutex_lock, osWaitForever);
	if (af_statis_lock_fd == -1)
		af_statis_lock_fd = rts_open(AF_STATIS_LOCK_FILE);
	xSemaphoreGive(af_statis_mutex_lock);
*/



	if (!isp_calloc_item(ex))
		return -RTS_ISP_ENOMEM;

	ret = isp_uds_message_simple(isp_id, MOD_STATIS,
				     STATIS_INFO_BUF_OFFSET,
				     &offset, sizeof(offset));
	if (ret)
		goto err;
	ex->size = offset.af.size + sizeof(osMutexId_t);
	ex->ptr = (void*)gbl_af_shm;
	ex->lock = xSemaphoreCreateMutex();//*((osMutexId_t*)((u32)ex->ptr + offset.af.size));
	if (!ex->lock) {
		isp_perror(-1, "af NULL mutex");
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	ex->s.edges = (uint32_t *)((u32)ex->ptr + offset.af.edge_offset - offset.af.offset);

	*statis = &ex->s;

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

int rts_isp_get_af_statis(uint32_t isp_id,
			  const struct rts_isp_af_statis *statis)
{
	int ret;
	struct rts_isp_af_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_af_statis_ex, s);
	//isp_atomic_bool_cmp_swap(&ex->locked, 0, 1);
	if (ex == NULL || ex->lock == NULL)
		return -RTS_ISP_EINVAL;
	ret = xSemaphoreTake(ex->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE)
		return -RTS_ISP_ETIMEDOUT;

	ret = isp_uds_message_simple(isp_id, MOD_STATIS, STATIS_INFO_AF_STAT,
				     &ex->s, sizeof(ex->s));
	//if (ret)
	//	xSemaphoreGive(ex->lock);
	return ret;
}

int rts_isp_put_af_statis(uint32_t isp_id,
			  const struct rts_isp_af_statis *statis)
{
	struct rts_isp_af_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_af_statis_ex, s);
	xSemaphoreGive(ex->lock);

	return RTS_ISP_OK;
}

void rts_isp_release_af_statis(uint32_t isp_id,
			       const struct rts_isp_af_statis *statis)
{
	struct rts_isp_af_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return;

	ex = container_of(statis, struct rts_isp_af_statis_ex, s);
	//rts_isp_put_af_statis(isp_id, statis);
	xSemaphoreGive(ex->lock);
	//osMutexDelete(ex->lock);
	if (ex->lock) {
		vSemaphoreDelete(ex->lock);
		ex->lock = NULL;
	}
	isp_free(ex);
}

