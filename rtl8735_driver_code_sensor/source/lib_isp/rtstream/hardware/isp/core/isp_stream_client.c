/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_top.h>
#include <isp_mod.h>
#include <isp_request.h>
#include <isp_driver.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_STREAM

#define MAX_READ_CNT 4

struct isp_stream_client {
	isp_stream_t stream;
	struct isp_list requests;

	uint32_t read_count;
	uint32_t read_offset;
	struct isp_msg_hdr pending_hdr;
	struct isp_msg_buf *pending_msg;
};

int stream_message_execute(void *data)
{
	int ret;
	struct isp_mod *mod;
	struct isp_msg_hdr *hdr;
	struct isp_msg_buf *msg = data;

	if (!msg)
		return -RTS_ISP_EINVAL;

	hdr = &msg->hdr;

	isp_top_lock_internal();
	isp_driver_isp_clk_get();
	mod = isp_top_get_mod(hdr->isp_id, hdr->mod_id);
	ret = isp_mod_do_action(mod, hdr->action, msg->data,
				ISP_AID_SIZE(hdr->action));
	isp_driver_isp_clk_put();
	isp_top_unlock_internal();
	if (ret)
		return ret;

	//isp_info("%s isp: %u mod: 0x%x action: 0x%x ok \r\n", __func__, hdr->isp_id, hdr->mod_id, hdr->action);

	return RTS_ISP_OK;
}

//static void stream_client_release(void *priv)
static void stream_client_release(isp_stream_t *stream)
{
	struct isp_request *req;
	struct isp_request *next;
	struct isp_stream_client *client;

	//if (!priv)
	if (!stream)
		return;

	//client = priv;
	client = container_of(stream, struct isp_stream_client, stream);

	list_foreach_data_safe(req, next, &client->requests, list) {
		/*
		 * we can not release struct isp_request here, modules may be
		 * using it. It will be released in stream_respond_request
		 */
		req->stream = NULL;
		list_remove_init(&req->list);
	}

	isp_stream_cleanup(stream);
	isp_free(client);

	//debug("%s ok\n", __func__);
}

static int stream_service_client(isp_stream_t *stream, int fd)
{
/*
	struct isp_stream_client *client = isp_stream_get_priv(stream);
	struct isp_msg_buf msg;

	memcpy(&msg.hdr, &client->pending_hdr, sizeof(struct isp_msg_hdr));
	msg.data = (void *)client->pending_msg;
	msg.refcnt = 0;
	ret = stream_message_execute(msg);
	
	return ret;
*/
	return RTS_ISP_OK;
}

int isp_stream_client_add(isp_poll_t p, int fd)
{
	int ret;
	struct isp_stream_client *client = NULL;

	if (!p || fd < 0)
		return -RTS_ISP_EINVAL;

	if (!isp_calloc_item(client))
		return -RTS_ISP_ENOMEM;

	ret = isp_stream_init(&client->stream, p, fd, stream_service_client);
	if (ret)
		goto err;

	list_init(&client->requests);
	//
	//isp_stream_set_priv(client->stream, client);
	//isp_stream_set_release(client->stream, stream_client_release);
	isp_stream_set_release(&client->stream, stream_client_release);

	return RTS_ISP_OK;

err:
	isp_free(client);
	isp_perror(ret, "add stream client fail");
	return ret;
}

