#ifndef _ISP_UDS_H_INC_
#define _ISP_UDS_H_INC_

#include <isp_stream.h>

#define ISP_UDS_SERVER_SOCKET "/var/run/rtsisp.sock"

int isp_uds_stream_alloc(isp_stream_t **pstream, isp_poll_t p);
void isp_uds_stream_release(isp_stream_t *stream);

/* default 500ms timeout */
int isp_uds_message_process(struct isp_msg_buf *msg);
int isp_uds_message_simple(uint32_t isp_id, uint32_t mod_id,
			   uint32_t action, void *data, uint32_t len);
int isp_uds_message_process_timeout(struct isp_msg_buf *msg, long timeout);
int isp_uds_message_simple_timeout(uint32_t isp_id, uint32_t mod_id,
				   uint32_t action, void *data, uint32_t len,
				   long timeout);

#endif /* _ISP_UDS_H_INC_ */

