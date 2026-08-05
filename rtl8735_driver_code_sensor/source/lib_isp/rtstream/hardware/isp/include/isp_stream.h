#ifndef _ISP_STREAM_H_INC_
#define _ISP_STREAM_H_INC_

#include <unistd.h>
#include <isp_list.h>
#include <isp_poll.h>
#include <isp_msg_buf.h>

typedef struct isp_stream isp_stream_t;
typedef int (*isp_stream_read_cb)(isp_stream_t *stream, int fd);
typedef void (*isp_stream_write_done_cb)(isp_stream_t *stream, int status);
typedef void (*isp_stream_release_cb)(isp_stream_t *stream);

struct isp_stream {
	isp_io_handle_t io;

	isp_stream_read_cb read_cb;
	struct isp_list write_queue;
	uint32_t write_offset;

	isp_stream_release_cb release;

	int opened;
};

int isp_stream_init(isp_stream_t *stream, isp_poll_t p, int fd,
		    isp_stream_read_cb read_cb);
void isp_stream_cleanup(isp_stream_t *stream);
int isp_stream_write(isp_stream_t *stream, struct isp_msg_buf *msg,
		     isp_stream_write_done_cb write_cb);
int isp_stream_set_release(isp_stream_t *stream, isp_stream_release_cb release);
isp_poll_t isp_stream_get_poll(isp_stream_t *stream);

int isp_stream_client_add(isp_poll_t p, int fd);

#endif /* _ISP_STREAM_H_INC_ */

