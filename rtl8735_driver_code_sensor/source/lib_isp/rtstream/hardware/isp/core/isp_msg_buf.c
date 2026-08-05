/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <linux/uio.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_msg_buf.h>

struct isp_msg_buf *isp_msg_new(void *data, uint32_t len, int shared)
{
	uint32_t total;
	struct isp_msg_buf *msg;

	if (!data && len && shared)
		return NULL;

	total = shared ? sizeof(*msg) : sizeof(*msg) + len;
	msg = isp_malloc(total);
	if (!msg)
		return NULL;

	memset(&msg->hdr, 0, sizeof(msg->hdr));
	msg->hdr.msg_len = sizeof(msg->hdr) + len;
	if (shared) {
		msg->refcnt = -1;
		msg->data = data;
	} else {
		msg->refcnt = 1;
		msg->data = msg + 1;
		if (data && len)
			isp_memcpy(msg->data, data, len);
	}

	return msg;
}

struct isp_msg_buf *isp_msg_get(struct isp_msg_buf *msg)
{
	struct isp_msg_buf *new;

	if (msg->refcnt == -1) {
		new = isp_msg_new(msg->data, isp_msg_data_len(&msg->hdr), 0);
		if (!new)
			return NULL;
		new->hdr = msg->hdr;
		return new;
	}
	msg->refcnt += 1;
	return msg;
}

void isp_msg_put(struct isp_msg_buf *msg)
{
	switch (msg->refcnt) {
	case -1:
	case 1:
		isp_free(msg);
		//isp_info("%s 0x%08x\r\n", __FUNCTION__, msg);
		break;
	default:
		msg->refcnt--;
	}
}

struct isp_msg_buf *isp_msg_req_to_resp(struct isp_msg_buf *req, int retval)
{
	struct isp_msg_buf *resp;

	resp = isp_msg_get(req);
	if (resp) {
		resp->hdr.msg_len = retval ? sizeof(resp->hdr) : req->hdr.ret_len;
		resp->hdr.ret_len = 0;
		resp->hdr.ret_val = retval;
	}

	return resp;
}

int isp_msg_write(int fd, struct isp_msg_buf *msg, uint32_t offset)
{
	printf("%s not implement\n", __func__);
	return RTS_FAIL;
}

int isp_msg_read(int fd, struct isp_msg_buf *msg, uint32_t offset)
{
	printf("%s not implement\n", __func__);
	return RTS_FAIL;
}

int isp_msg_read_hdr(int fd, struct isp_msg_hdr *hdr, uint32_t offset)
{
	printf("%s not implement\n", __func__);
	return RTS_FAIL;
}

int isp_msg_relocate(struct isp_msg_buf *msg)
{
	uintptr_t *ptr;
	uintptr_t *end;
	uintptr_t offset;

	if (!msg)
		return -RTS_ISP_EINVAL;

	/* first item is the real ptr of reloc table at peer */
	ptr = (uintptr_t *)((u32)msg->data + msg->hdr.reloc_pos);
	end = ptr + msg->hdr.reloc_num;
	offset = (uintptr_t)ptr - *ptr;
	/* update relocation table */
	*ptr += offset;
	while (++ptr < end) {
		if (*ptr == 0)
			return -RTS_ISP_EFAULT;
		/* update relocation table */
		*ptr += offset;
		/* update pointer at buf */
		*(uintptr_t *)(*ptr) += offset;
	}

	return RTS_ISP_OK;
}

