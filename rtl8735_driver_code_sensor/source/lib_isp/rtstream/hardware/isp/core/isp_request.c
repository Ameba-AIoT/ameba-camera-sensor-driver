/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_log.h>
#include <isp_mem.h>
#include <isp_utils.h>
#include <isp_request.h>

struct isp_request *isp_request_new(isp_stream_t *stream,
				    struct isp_msg_buf *msg,
				    respond_cb respond)
{
	struct isp_request *req;

	if (!stream || !msg || !respond)
		return NULL;
	if (!isp_calloc_item(req))
		return NULL;

	req->msg = isp_msg_get(msg);
	req->respond = respond;

	req->stream = stream;
	list_init(&req->list);

	return req;
}

void isp_request_free(struct isp_request *req)
{
	if (!req)
		return;
	isp_release(req->msg, isp_msg_put);
	req->respond = NULL;

	req->stream = NULL;
	list_remove_init(&req->list);
	isp_free(req);
}

