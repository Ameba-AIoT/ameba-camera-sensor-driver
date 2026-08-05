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
#include <isp_mod_ae.h>
#include <isp_mod_statis.h>
#include "rtx_mutex.h"

static void free_ae_setting(struct rts_isp_ae_setting *setting)
{
	if (setting->_auto.win_weights)
		free(setting->alloc_win_weights);
	isp_free(setting);
}

static struct rts_isp_ae_setting *
alloc_ae_setting(const struct isp_mod_ae_stat_info *info)
{
	int win_num;
	uint8_t *weights;
	struct rts_isp_ae_setting *setting;

	if (!isp_calloc_item(setting))
		goto err;
	win_num = info->info.win.cols * info->info.win.rows;
	weights = isp_calloc(win_num, sizeof(*weights)+256);
	if (!weights) {
		isp_free(setting);
		goto err;
	}
	setting->alloc_win_weights = weights;
	set_const_var(setting->_auto.window_num, win_num);
	set_const_var_type(uint8_t *, setting->_auto.win_weights, (uint8_t*)(((int)weights+255)&~255));

	return setting;
err:
	free_ae_setting(setting);
	return NULL;
}

static int ae_setting_serial(struct rts_isp_ae_setting *setting,
			     struct isp_msg_buf *msg)
{
	int ret;
	void *buf;
	uintptr_t end;
	void *reloc_begin;
	struct rts_isp_ae_setting *buf_setting;
	uint8_t *weights;

	if (!setting || !msg)
		return -RTS_ISP_EINVAL;

	weights = setting->_auto.win_weights;
	buf = msg->data;
	buf_setting = buf;
	end = (uintptr_t)buf + isp_msg_data_len(&msg->hdr);

	ret = copy_from_src(buf, setting, sizeof(*setting), end);
	if (ret)
		return ret;
	set_const_var_type(uint8_t *, buf_setting->_auto.win_weights, buf);
	ret = copy_from_src(buf, weights,
			    setting->_auto.window_num * sizeof(*weights), end);

	/* add_reloc_table */
	reloc_begin = buf;
	ret = set_one_reloc_item(buf, reloc_begin, end);
	if (ret)
		return ret;
	ret = set_one_reloc_item(buf, &buf_setting->_auto.win_weights, end);
	if (ret)
		return ret;

	msg->hdr.msg_len = (u32)buf - (u32)msg->data + sizeof(msg->hdr);
	msg->hdr.ret_len = msg->hdr.msg_len;
	msg->hdr.reloc_pos = (u32)reloc_begin - (u32)msg->data;
	msg->hdr.reloc_num = ((u32)buf - (u32)reloc_begin) / sizeof(uintptr_t);

	return RTS_ISP_OK;
}

static int ae_setting_deserial(struct rts_isp_ae_setting *setting,
			       struct isp_msg_buf *msg)
{
	int ret;
	void *buf;
	uintptr_t end;
	uint8_t *weights;

	if (!msg || !setting)
		return -RTS_ISP_EINVAL;

	if (msg->hdr.ret_val)
		return msg->hdr.ret_val;

	ret = isp_msg_relocate(msg);
	if (ret)
		return ret;

	end = (uintptr_t)msg->data + isp_msg_data_len(&msg->hdr);
	buf = msg->data;

	weights = setting->_auto.win_weights;
	ret = copy_to_src(setting, buf, sizeof(*setting), end);
	if (ret)
		return ret;
	set_const_var_type(uint8_t *, setting->_auto.win_weights, weights);

	copy_to_src(setting->_auto.win_weights, buf,
		    setting->_auto.window_num * sizeof(*weights), end);

	return RTS_ISP_OK;
}

static int __process_ae_setting(uint32_t isp_id, uint32_t action,
			   struct rts_isp_ae_setting *ae_setting)
{
	int ret;
	uint8_t buf[2048];
	struct isp_msg_buf *msg;

	if (isp_id >= _ISP_ID_NUM || !ae_setting)
		return -RTS_ISP_EINVAL;

	msg = isp_msg_new(buf, sizeof(buf), 1);
	if (!msg)
		return -RTS_ISP_ENOMEM;

	ret = ae_setting_serial(ae_setting, msg);
	if (ret)
		goto out;

	msg->hdr.isp_id = isp_id;
	msg->hdr.mod_id = MOD_AE;
	msg->hdr.action = action;
	msg->hdr.ret_val = -1;

	ret = isp_uds_message_process(msg);
	if (ret)
		goto out;
	ret = ae_setting_deserial(ae_setting, msg);
out:
	isp_release(msg, isp_msg_put);
	return ret;
}

int rts_isp_query_ae_setting(uint32_t isp_id,
			     struct rts_isp_ae_setting **ae_setting)
{
	int ret;
	struct rts_isp_ae_setting *setting;
	struct isp_mod_ae_stat_info info;

	if (isp_id >= _ISP_ID_NUM || !ae_setting)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_AE, AE_INFO_STATIS,
				     &info, sizeof(info));
	if (ret)
		return ret;
	setting = alloc_ae_setting(&info);
	if (!setting)
		return -RTS_ISP_ENOMEM;
	ret = rts_isp_get_ae_setting(isp_id, setting);
	if (ret)
		goto err;
	*ae_setting = setting;
	return RTS_ISP_OK;
err:
	isp_perror(ret, "query ae setting fail");
	free_ae_setting(setting);
	return ret;
}

int rts_isp_get_ae_setting(uint32_t isp_id,
			   struct rts_isp_ae_setting *ae_setting)
{
	return __process_ae_setting(isp_id, AE_EXEC_GET_SETTING, ae_setting);
}

int rts_isp_set_ae_setting(uint32_t isp_id,
			   struct rts_isp_ae_setting *ae_setting)
{
	return __process_ae_setting(isp_id, AE_EXEC_SET_SETTING, ae_setting);
}

void rts_isp_release_ae_setting(uint32_t isp_id,
				struct rts_isp_ae_setting *ae_setting)
{
	free_ae_setting(ae_setting);
}

//#define AE_STATIS_LOCK_FILE "/var/lock/isp_ae_statis.lock"
//
struct rts_isp_ae_statis_ex {
	struct rts_isp_ae_statis s;
	void *ptr;
	osMutexId_t lock;
	uint32_t size;
	//isp_atomic_t locked;
};

//static int ae_statis_lock_fd = -1;
  //static osMutexId_t ae_statis_mutex_lock = 0;
  extern void *gbl_ae_shm;

int rts_isp_get_ae_statis_info(uint32_t isp_id,
			       struct rts_isp_ae_stat_info *info)
{
	int ret;
	struct isp_mod_ae_stat_info stat_info;

	if (isp_id > _ISP_ID_NUM || !info)
		return -RTS_ISP_EINVAL;

	ret = isp_uds_message_simple(isp_id, MOD_AE, AE_INFO_STATIS,
				     &stat_info, sizeof(stat_info));
	if (ret)
		return ret;
	*info = stat_info.info;

	return RTS_ISP_OK;
}

int rts_isp_query_ae_statis(uint32_t isp_id,
			    const struct rts_isp_ae_statis **statis)
{
	int i;
	int ret;
//	int fd = -1;
	struct rts_isp_ae_statis_ex *ex;
	struct isp_statis_buf_offset offset;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

/*
	if (!ae_statis_mutex_lock) {

		ae_statis_mutex_lock = xSemaphoreCreateMutex();
		if ( !ae_statis_mutex_lock ) {
			isp_perror(-1, "ae mutex alloc fail");
			return -1;
		}
	}

	xSemaphoreTake(ae_statis_mutex_lock, osWaitForever);
	if (ae_statis_lock_fd == -1)
		ae_statis_lock_fd = rts_open(AE_STATIS_LOCK_FILE);
	xSemaphoreGive(ae_statis_mutex_lock);
*/




	if (!isp_calloc_item(ex))
		return -RTS_ISP_ENOMEM;

	ret = isp_uds_message_simple(isp_id, MOD_STATIS,
				     STATIS_INFO_BUF_OFFSET,
				     &offset, sizeof(offset));
	if (ret)
		goto err;
	ex->size = offset.ae.size + sizeof(osMutexId_t);
	ex->ptr = (void*)gbl_ae_shm;
	ex->lock = xSemaphoreCreateMutex();//*((osMutexId_t*)((u32)ex->ptr + offset.ae.size));
	if (!ex->lock) {
		isp_error("ae NULL mutex");
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		ex->s.hdr[i].hist = (uint32_t *)((u32)ex->ptr +	offset.ae.hdr[i].hist_offset - offset.ae.offset);
		ex->s.hdr[i].y_mean = (uint16_t *)((u32)ex->ptr + offset.ae.hdr[i].y_offset - offset.ae.offset);
	}
	ex->s.hist =  (uint32_t *)((u32)ex->ptr + offset.ae.hist_offset - offset.ae.offset);
	ex->s.y_mean = (uint16_t *)((u32)ex->ptr + offset.ae.y_offset - offset.ae.offset);

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

int rts_isp_get_ae_statis(uint32_t isp_id,
			  const struct rts_isp_ae_statis *statis)
{
	int ret;
	struct rts_isp_ae_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_ae_statis_ex, s);
	//isp_atomic_bool_cmp_swap(&ex->locked, 0, 1);
	ret = xSemaphoreTake(ex->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rts_isp_get_ae_statis wait ex->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	ret = isp_uds_message_simple(isp_id, MOD_STATIS, STATIS_INFO_AE_STAT,
				     &ex->s, sizeof(ex->s));
	//if (ret)
	//	xSemaphoreGive(ex->lock);
	return ret;
}

int rts_isp_put_ae_statis(uint32_t isp_id,
			  const struct rts_isp_ae_statis *statis)
{
	struct rts_isp_ae_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_ae_statis_ex, s);
	xSemaphoreGive(ex->lock);

	return RTS_ISP_OK;
}

void rts_isp_release_ae_statis(uint32_t isp_id,
			       const struct rts_isp_ae_statis *statis)
{
	struct rts_isp_ae_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return;

	ex = container_of(statis, struct rts_isp_ae_statis_ex, s);

	//rts_isp_put_ae_statis(isp_id, statis);
	xSemaphoreGive(ex->lock);
//	osMutexDelete(ex->lock);

	if (ex->lock) {
		vSemaphoreDelete(ex->lock);
		ex->lock = NULL;
	}

	isp_free(ex);
}

int rts_isp_register_ae_fps_change_cb(uint32_t isp_id, ae_fps_status_cb cb)
{
	return isp_uds_message_simple(isp_id, MOD_AE,
				     AE_EXEC_SET_FPS_CHANGE_CB,
				     &cb, sizeof(cb));
}

int rts_isp_get_max_dyn_region(uint32_t isp_id, enum rts_isp_ae_region *region)
{
	return isp_uds_message_simple(isp_id, MOD_AE,
				      AE_EXEC_GET_MAX_DYN_REGION,
				      region, sizeof(*region));
}

int rts_isp_set_max_dyn_region_en(uint32_t isp_id, uint8_t max_dyn_region_en)
{
	return isp_uds_message_simple(isp_id, MOD_AE,
				      AE_EXEC_SET_MAX_DYN_REGION_ENABLE,
				      &max_dyn_region_en, sizeof(max_dyn_region_en));
}
