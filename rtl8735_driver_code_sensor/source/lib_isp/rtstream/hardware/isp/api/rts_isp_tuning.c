/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "FreeRTOS.h"
#include "rt_task.h"
#include <rtscamkit.h>
#include <rts_isp_tuning.h>
#include <isp_atomic.h>
#include <isp_mod.h>
#include <isp_uds.h>
#include <isp_mod_statis.h>
#include <isp_mod_iq.h>

struct rts_isp_tuning_statis_ex {
	struct rts_isp_tuning_statis s;
	void *ptr;
	uint32_t size;
};

static int tuning_regs_serial(struct isp_iq_tuning_regs *tuning_regs,
			      struct isp_msg_buf *msg)
{
	int ret;
	void *buf;
	uintptr_t end;
	void *reloc_begin;
	struct rts_isp_tuning_reg *regs;
	struct isp_iq_tuning_regs *buf_tuning_regs;

	if (!tuning_regs || !msg)
		return -RTS_ISP_EINVAL;

	regs = tuning_regs->regs;

	buf = msg->data;
	buf_tuning_regs = buf;
	end = (uintptr_t)buf + isp_msg_data_len(&msg->hdr);

	ret = copy_from_src(buf, tuning_regs, sizeof(*tuning_regs), end);
	if (ret)
		return ret;
	buf_tuning_regs->regs = buf;
	ret = copy_from_src(buf, regs, tuning_regs->num * sizeof(*regs), end);

	/* add_reloc_table */
	reloc_begin = buf;
	ret = set_one_reloc_item(buf, reloc_begin, end);
	if (ret)
		return ret;
	ret = set_one_reloc_item(buf, &buf_tuning_regs->regs, end);
	if (ret)
		return ret;

	msg->hdr.msg_len = (u32)buf - (u32)msg->data + sizeof(msg->hdr);
	msg->hdr.ret_len = msg->hdr.msg_len;
	msg->hdr.reloc_pos = (u32)reloc_begin - (u32)msg->data;
	msg->hdr.reloc_num = ((u32)buf - (u32)reloc_begin) / sizeof(uintptr_t);

	return RTS_ISP_OK;
}

static int tuning_regs_deserial(struct isp_iq_tuning_regs *tuning_regs,
				struct isp_msg_buf *msg)
{
	int ret;
	void *buf;
	uintptr_t end;
	struct rts_isp_tuning_reg *regs;

	if (!msg || !tuning_regs)
		return -RTS_ISP_EINVAL;

	if (msg->hdr.ret_val)
		return msg->hdr.ret_val;

	ret = isp_msg_relocate(msg);
	if (ret)
		return ret;

	end = (uintptr_t)msg->data + isp_msg_data_len(&msg->hdr);
	buf = msg->data;

	regs = tuning_regs->regs;
	ret = copy_to_src(tuning_regs, buf, sizeof(*tuning_regs), end);
	if (ret)
		return ret;
	tuning_regs->regs = regs;

	copy_to_src(regs, buf, tuning_regs->num * sizeof(*regs), end);

	return RTS_ISP_OK;
}

static int __process_tuning_regs(uint32_t isp_id, uint32_t action,
				 struct isp_iq_tuning_regs *tuning_regs)
{
	int ret;
	uint8_t buf[2048];
	struct isp_msg_buf *msg;

	if (isp_id >= _ISP_ID_NUM || !tuning_regs)
		return -RTS_ISP_EINVAL;

	msg = isp_msg_new(buf, sizeof(buf), 1);
	if (!msg)
		return -RTS_ISP_ENOMEM;

	ret = tuning_regs_serial(tuning_regs, msg);
	if (ret)
		goto out;

	msg->hdr.isp_id = isp_id;
	msg->hdr.mod_id = MOD_IQ;
	msg->hdr.action = action;
	msg->hdr.ret_val = -1;

	ret = isp_uds_message_process(msg);
	if (ret)
		goto out;
	ret = tuning_regs_deserial(tuning_regs, msg);
out:
	isp_release(msg, isp_msg_put);
	return ret;
}

extern void *gbl_tuning_shm;
extern void *gbl_tuning_parm_shm;
extern void *gbl_tuning_iqtable_shm;


int rts_isp_tuning_query_statis(uint32_t isp_id,
				struct rts_isp_tuning_statis **statis)
{
	struct rts_isp_tuning_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(ex))
		return -RTS_ISP_ENOMEM;

	ex->size = TUNING_STATIS_SHM_SIZE;
	ex->ptr = (void*)gbl_tuning_shm;

	ex->s.type = RTS_ISP_TUNING_STATIS_ALL;
	*(void **)&ex->s.buf = ex->ptr;
	set_const_var(ex->s.len, TUNING_STATIS_SHM_SIZE);

	*statis = &ex->s;

	return RTS_ISP_OK;
}

int rts_isp_tuning_get_statis(uint32_t isp_id,
			      struct rts_isp_tuning_statis *statis)
{
	struct rts_isp_tuning_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return -RTS_ISP_EINVAL;

	ex = container_of(statis, struct rts_isp_tuning_statis_ex, s);

	set_const_var(ex->s.len, TUNING_STATIS_SHM_SIZE);
	return isp_uds_message_simple(isp_id, MOD_STATIS,
				      STATIS_INFO_TUNING_STAT,
				      &ex->s, sizeof(ex->s));
}

void rts_isp_tuning_release_statis(uint32_t isp_id,
				   struct rts_isp_tuning_statis *statis)
{
	struct rts_isp_tuning_statis_ex *ex;

	if (isp_id > _ISP_ID_NUM || !statis)
		return;

	ex = container_of(statis, struct rts_isp_tuning_statis_ex, s);

	isp_free(ex);
}

int rts_isp_tuning_query_param(uint32_t isp_id,
			       struct rts_isp_tuning_param **tuning_param)
{
	int ret;
	int fd = -1;
	struct rts_isp_tuning_param *param;

	if (isp_id > _ISP_ID_NUM || !tuning_param)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(param))
		return -RTS_ISP_ENOMEM;

	set_const_var(param->max_len, TUNING_PARAM_SHM_SIZE);
	param->buf = gbl_tuning_parm_shm;
	param->type = RTS_ISP_TUNING_PARAM_ALL;
	param->len = param->max_len;

	ret = rts_isp_tuning_get_param(isp_id, param);
	if (ret)
		goto err;

	*tuning_param = param;

	return RTS_ISP_OK;
err:
	isp_close(fd);
	if (param) {
		isp_free(param);
	}
	return ret;
}

int rts_isp_get_meta_param(uint32_t isp_id,
			     struct rts_isp_meta_param *m_param)
{
	if (isp_id > _ISP_ID_NUM || !m_param)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_GET_META_PARAM,
			m_param, sizeof(*m_param));
}




int rts_isp_tuning_get_param(uint32_t isp_id,
			     struct rts_isp_tuning_param *param)
{
	if (isp_id > _ISP_ID_NUM || !param)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_GET_ALGO_PARAM,
				      param, sizeof(*param));
}

int rts_isp_tuning_set_param(uint32_t isp_id,
			     struct rts_isp_tuning_param *param)
{
	if (isp_id > _ISP_ID_NUM || !param)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_SET_ALGO_PARAM,
				      param, sizeof(*param));
}

void rts_isp_tuning_release_param(uint32_t isp_id,
				  struct rts_isp_tuning_param *param)
{
	if (isp_id > _ISP_ID_NUM || !param)
		return;

	isp_free(param);
}

int rts_isp_tuning_query_iq(uint32_t isp_id,
			    struct rts_isp_tuning_iq **tuning_iq)
{
	struct rts_isp_tuning_iq *iq;

	if (isp_id > _ISP_ID_NUM || !tuning_iq)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(iq))
		return -RTS_ISP_ENOMEM;

	set_const_var(iq->max_len, TUNING_IQ_TABLE_SHM_SIZE);
	iq->buf = gbl_tuning_iqtable_shm;

	iq->type = RTS_ISP_TUNING_IQ_TABLE_ALL;
	iq->len = iq->max_len;
	*tuning_iq = iq;

	return RTS_ISP_OK;
}

int rts_isp_tuning_get_iq(uint32_t isp_id,
			  struct rts_isp_tuning_iq *iq)
{
	if (isp_id > _ISP_ID_NUM || !iq)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_GET_IQ_TABLE,
				      iq, sizeof(*iq));
}

int rts_isp_tuning_set_iq(uint32_t isp_id,
			  struct rts_isp_tuning_iq *iq)
{
	if (isp_id > _ISP_ID_NUM || !iq)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_SET_IQ_TABLE,
				      iq, sizeof(*iq));
}

void rts_isp_tuning_release_iq(uint32_t isp_id,
			       struct rts_isp_tuning_iq *iq)
{
	if (isp_id > _ISP_ID_NUM || !iq)
		return;
	isp_free(iq);
}

int rts_isp_tuning_read_regs(uint32_t isp_id,
			     struct rts_isp_tuning_reg *regs, uint32_t num)
{
	struct isp_iq_tuning_regs tuning_regs;

	if (isp_id > _ISP_ID_NUM || !regs || !num)
		return -RTS_ISP_EINVAL;

	tuning_regs.regs = regs;
	tuning_regs.num = num;
	return __process_tuning_regs(isp_id, IQ_EXEC_READ_REGS, &tuning_regs);
}

int rts_isp_tuning_write_regs(uint32_t isp_id,
			      struct rts_isp_tuning_reg *regs, uint32_t num)
{
	struct isp_iq_tuning_regs tuning_regs;

	if (isp_id > _ISP_ID_NUM || !regs || !num)
		return -RTS_ISP_EINVAL;

	tuning_regs.regs = regs;
	tuning_regs.num = num;
	return __process_tuning_regs(isp_id, IQ_EXEC_WRITE_REGS, &tuning_regs);
}

const char *rts_isp_tuning_packed_iq_path(uint32_t isp_id)
{
	int ret;
	static struct isp_packed_iq_info info;

	if (isp_id > _ISP_ID_NUM)
		return NULL;

	ret = isp_uds_message_simple(isp_id, MOD_IQ, IQ_INFO_PACKED_IQ,
				     &info, sizeof(info));
	if (ret)
		return NULL;
	//memcpy(info->path, iq->man->bfr, sizeof(void*));
	return info.bfr;
}

int rts_isp_tuning_reload_packed_iq(uint32_t isp_id)
{
	if (isp_id > _ISP_ID_NUM)
		return -RTS_ISP_EINVAL;

	return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_RELOAD_PACKED_IQ,
				      NULL, 0);
}

