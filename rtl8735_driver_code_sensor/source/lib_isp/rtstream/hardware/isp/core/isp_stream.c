/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "rt_types.h"
#include <linux/eventpoll.h>
#include <isp_top.h>
#include <isp_utils.h>
#include <isp_log.h>
#include <isp_mem.h>
#include <isp_stream.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_STREAM

/*struct isp_stream {
	isp_io_handle_t io;

	isp_stream_read_cb read_cb;
	struct isp_list write_queue;
	uint32_t write_offset;

	void *priv;
	isp_stream_release_cb release;

	int closing;
};*/

struct isp_stream_write_req {
	struct isp_list list;
	isp_stream_write_done_cb write_cb;
	struct isp_msg_buf *msg;
};

static void stream_write_cb_finish(struct isp_stream_write_req *req,
				   isp_stream_t *stream, int ret)
{
	stream->write_offset = 0;
	if (req->write_cb)
		req->write_cb(stream, ret);
	list_remove_init(&req->list);
	isp_release(req->msg, isp_msg_put);
	isp_free(req);
}

static int stream_write_queue(struct isp_stream *stream)
{
	int ret = RTS_ISP_OK;
	struct isp_list *list;
	isp_io_handle_t *io;
	struct isp_stream_write_req *req;

	if (!stream)
		return -RTS_ISP_EINVAL;

	io = &stream->io;

	while (!isp_list_empty(&stream->write_queue)) {
		debug("write queue once\n");
		list = list_head(&stream->write_queue);
		req = list_data(list, struct isp_stream_write_req, list);
		ret = isp_msg_write(isp_io_fd(io), req->msg,
				    stream->write_offset);
		if (ret < 0) {
			if (ret == -EAGAIN)
				break;
			stream_write_cb_finish(req, stream, ret);
			break;
		}
		stream->write_offset += ret;
		if (stream->write_offset < req->msg->hdr.msg_len)
			break;

		stream_write_cb_finish(req, stream, RTS_ISP_OK);
	}

	if (isp_list_empty(&stream->write_queue))
		isp_io_event_del(io, EPOLLOUT);

	return RTS_ISP_OK;
}

static int stream_callback(isp_io_handle_t *io, uint32_t events)
{
	//int ret;
	struct isp_stream *stream;

	if (!io || !events)
		return -RTS_ISP_EINVAL;

	//stream = isp_io_get_priv(io);
	stream = container_of(io, isp_stream_t, io);
	/*
	 * stream may be released in callback,
	 * so we only handle one callback for each callback processing
	 */
	if (events & EPOLLIN) {
		isp_assert(stream->read_cb);
		//ret = stream->read_cb(stream, isp_io_fd(stream->io));
		//if (ret)
		//	return ret;
		return stream->read_cb(stream, isp_io_fd(io));
	}
	if (events & EPOLLOUT) {
		//ret = stream_write_queue(stream);
		//if (ret)
		//	return ret;
		return stream_write_queue(stream);
	}

	return RTS_ISP_OK;
}

//static void stream_release(void *priv)
static void stream_release(isp_io_handle_t *io)
{
	//isp_stream_t stream;
	//struct isp_stream_write_req *req;
	//struct isp_stream_write_req *next;
	isp_stream_t *stream = container_of(io, isp_stream_t, io);

	//if (!priv)
	if (!io)
		return;

	/*stream = priv;

	stream->closing = RTS_ISP_TRUE;
	if (stream->release)
		stream->release(stream->priv);
	list_foreach_data_safe(req, next, &stream->write_queue, list)
		stream_write_cb_finish(req, stream, -RTS_ISP_ECANCELD);
	isp_free(stream);

	debug("%s ok\n", __func__);*/
	isp_assert(stream->release);
	stream->release(stream);
}

int isp_stream_init(isp_stream_t *stream, isp_poll_t p, int fd,
		    isp_stream_read_cb read_cb)
{
	//isp_stream_t stream = NULL;
	int ret;

	//if (!pstream || !p || fd < 0 || !read_cb) {
	if (!stream || !p || fd < 0) {
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	//if (!isp_calloc_item(stream)) {
	//	ret = -RTS_ISP_ENOMEM;
	//	goto err;
	//}
	//
	//stream->read_cb = read_cb;
	//list_init(&stream->write_queue);
	memset(stream, 0, sizeof(*stream));

	ret = isp_io_init(&stream->io, p, fd, stream_callback);
	if (ret)
		goto err;
	stream->opened = RTS_ISP_TRUE;
	stream->read_cb = read_cb;
	list_init(&stream->write_queue);
#if ENABLE_POLL
	//read_cb=stream_service_client is NULL function in FreeRTOS
	if (read_cb)
		isp_io_event_add(&stream->io, EPOLLIN);
#endif
	//isp_io_set_priv(stream->io, stream);
	//isp_io_set_release(stream->io, stream_release);
	//
	//*pstream = stream;
	isp_io_set_release(&stream->io, stream_release);
	isp_stream_set_release(stream, isp_stream_cleanup);

	return RTS_ISP_OK;
err:
	//isp_free(stream);
	isp_perror(ret, "isp stream init fail");
	return ret;
}

void isp_stream_cleanup(isp_stream_t *stream)
{
	//if (stream)
	//	return isp_io_cleanup(stream->io);
	struct isp_stream_write_req *req;
	struct isp_stream_write_req *next;

	if (!stream || !stream->opened)
		return;

	stream->opened = RTS_ISP_FALSE;
	list_foreach_data_safe(req, next, &stream->write_queue, list)
		stream_write_cb_finish(req, stream, -RTS_ISP_ECANCELD);
	stream->read_cb = NULL;
	stream->write_offset = 0;
	stream->release = NULL;

	isp_io_cleanup(&stream->io);

	//debug("%s ok\n", __func__);
}

//void isp_stream_set_priv(isp_stream_t stream, void *priv)
//{
//	if (stream)
//		stream->priv = priv;
//}
//void *isp_stream_get_priv(isp_stream_t stream)
//{
//	if (stream)
//		return stream->priv;
//	return NULL;
//}

int isp_stream_set_release(isp_stream_t *stream, isp_stream_release_cb release)
{
	//if (stream)
	//	stream->release = release;
	if (!stream || !release)
		return -RTS_ISP_EINVAL;
	if (!stream->opened)
		return -RTS_ISP_ENOTREADY;
	stream->release = release;
	return RTS_ISP_OK;
}

#if ENABLE_POLL
isp_poll_t isp_stream_get_poll(isp_stream_t *stream)
{
	//if (stream)
	//	return isp_io_get_poll(stream->io);
	if (stream && stream->opened)
		return isp_io_get_poll(&stream->io);
	return NULL;
}

int isp_stream_write(isp_stream_t *stream, struct isp_msg_buf *msg,
		     isp_stream_write_done_cb write_cb)
{
	struct isp_stream_write_req *req;

	if (!stream || !msg)
		return -RTS_ISP_EINVAL;
	//if (stream->closing) {
	if (!stream->opened) {
		write_cb(stream, -RTS_ISP_ECANCELD);
		return RTS_ISP_OK;
	}
	stream_write_queue(stream);
	if (isp_list_empty(&stream->write_queue)) {
		int ret;

		//ret = isp_msg_write(isp_io_fd(stream->io), msg, 0);
		ret = isp_msg_write(isp_io_fd(&stream->io), msg, 0);
		if (ret > 0) {
			if (ret == (int)msg->hdr.msg_len) {
				write_cb(stream, RTS_ISP_OK);
				return RTS_ISP_OK;
			}
			stream->write_offset += ret;
		}
	}
	if (!isp_calloc_item(req)) {
		isp_release(stream, isp_stream_cleanup);
		return -RTS_ISP_ENOMEM;
	}
	req->msg = isp_msg_get(msg);
	req->write_cb = write_cb;
	list_init(&req->list);
	list_insert_tail(&stream->write_queue, &req->list);
	//isp_io_event_add(stream->io, EPOLLOUT);
	isp_io_event_add(&stream->io, EPOLLOUT);

	return RTS_ISP_OK;
}
#endif

