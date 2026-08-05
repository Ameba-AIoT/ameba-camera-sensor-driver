/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include "cmsis_os2.h"
#include "rt_types.h"
#include "rt_task.h"
#include <rts_isp_errno.h>
#include <isp_mem.h>
#include <isp_core.h>
#include <isp_utils.h>
#include <isp_uds.h>

#define DEFAULT_TIMEOUT 500
//#define __LOG_MESSAGE__

struct isp_uds_client_item {
	struct isp_list list;
	int fd;
	uint32_t message_sequence;
	int atfork_initialized;
};

struct isp_uds_client_pool {
	osMutexId_t lock;
	struct isp_list idle;
	int idle_count;
};

static struct isp_uds_client_pool g_client_pool = {
	.lock = NULL,
	.idle = LIST_INITIALIZER(g_client_pool.idle),
	.idle_count = 0,
};

static int uds_check_message(struct isp_msg_buf *msg)
{
	struct isp_msg_hdr *hdr = &msg->hdr;

	if (hdr->msg_len < simple_write_msg_size(hdr->action) ||
	    hdr->ret_len < simple_read_msg_size(hdr->action))
		return -RTS_ISP_ERANGE;

	return RTS_ISP_OK;
}

extern int stream_message_execute(struct isp_msg_buf *msg);
int isp_uds_message_process_timeout(struct isp_msg_buf *msg, long timeout)
{
	int retval;

	if (!msg)
		return -RTS_ISP_EINVAL;

	if (uds_check_message(msg))
		return -RTS_ISP_ERANGE;

	retval = stream_message_execute(msg);
	msg->hdr.msg_len = retval ? sizeof(msg->hdr) : msg->hdr.ret_len;
	msg->hdr.ret_len = 0;
	msg->hdr.ret_val = retval;

	return retval;
}

int isp_uds_message_process(struct isp_msg_buf *msg)
{
	return isp_uds_message_process_timeout(msg, DEFAULT_TIMEOUT);
}

int isp_uds_message_simple_timeout(uint32_t isp_id, uint32_t mod_id,
				   uint32_t action, void *data, uint32_t len,
				   long timeout)
{
	int ret;
	struct isp_msg_buf *msg;

	if (isp_id > _ISP_ID_NUM)
		return -RTS_ISP_EINVAL;
	if (ISP_AID_HAS_DATA(action) && !data)
		return -RTS_ISP_EINVAL;
	if (ISP_AID_SIZE(action) != len)
		return -RTS_ISP_EINVAL;

	msg = isp_msg_new(data, len, 1);
	if (!msg)
		return -RTS_ISP_ENOMEM;
#ifdef __LOG_MESSAGE__
	dbg_printf("%s 0x%08x\r\n", __func__, msg);
#endif
	msg->hdr.msg_len = simple_write_msg_size(action);
	msg->hdr.ret_len = simple_read_msg_size(action);
	msg->hdr.isp_id = isp_id;
	msg->hdr.mod_id = mod_id;
	msg->hdr.action = action;
	msg->hdr.ret_val = -1;
	msg->hdr.reloc_pos = 0;
	msg->hdr.reloc_num = 0;

	ret = isp_uds_message_process_timeout(msg, timeout);

	isp_release(msg, isp_msg_put);
#ifdef __LOG_MESSAGE__
	dbg_printf("%s 0x%08x done\r\n", __func__, msg);
#endif
	return ret;
}

int isp_uds_message_simple(uint32_t isp_id, uint32_t mod_id,
			   uint32_t action, void *data, uint32_t len)
{
	return isp_uds_message_simple_timeout(isp_id, mod_id, action,
					      data, len, DEFAULT_TIMEOUT);
}

