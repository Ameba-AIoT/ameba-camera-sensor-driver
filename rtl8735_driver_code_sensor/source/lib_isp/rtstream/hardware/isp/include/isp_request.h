#ifndef _ISP_REQUEST_H_INC_
#define _ISP_REQUEST_H_INC_

#include <isp_stream.h>

struct isp_request;
typedef void (*respond_cb)(struct isp_request *r, struct isp_msg_buf *resp);

struct isp_request {
	struct isp_msg_buf *msg;
	respond_cb respond;

	/* only used for internal */
	isp_stream_t *stream;
	struct isp_list list;
};

struct isp_request *isp_request_new(isp_stream_t *stream,
				    struct isp_msg_buf *msg,
				    respond_cb respond);
void isp_request_free(struct isp_request *req);


#endif /* _ISP_REQUEST_H_INC_ */
