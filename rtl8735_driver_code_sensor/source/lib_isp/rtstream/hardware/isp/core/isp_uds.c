/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */


#include "cmsis_os2.h"
#include "rt_types.h"
#include "rt_task.h"
#include <isp_mem.h>
#include <isp_log.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_notify.h>
#include <isp_uds.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_UDS

struct isp_uds_stream {
	isp_stream_t stream;
};

static int uds_listen(const char *name)
{
#if 0
	int fd;
	int ret;
	size_t len;
	struct sockaddr_un un;

	if (!name)
		return -RTS_ISP_EINVAL;

	if (strlen(name) >= sizeof(un.sun_path))
		return -RTS_ISP_ENAMETOOLONG;
	fd = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	if (fd < 0)
		return -errno;
	unlink(name);
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_LOCAL;
	strcpy(un.sun_path, name);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
	if (bind(fd, (struct sockaddr *)&un, len) < 0) {
		ret = -errno;
		goto err;
	}
	if (listen(fd, 4) < 0) {
		ret = -errno;
		goto err;
	}

	return fd;
err:
	isp_close(fd);
	return ret;
#else  //hrchen
	printf("%s not implement yet\n", __func__);
	return -RTS_ISP_EINVAL;
#endif
}

static int uds_accept_fd(int fd)
{
#if 0
	int ret;
	int client_fd;

	if (fd < 0)
		return -RTS_ISP_EINVAL;

	client_fd = accept(fd, NULL, NULL);
	if (client_fd >= 0) {
		ret = isp_closexec(client_fd, 1);
		if (ret == 0)
			ret = isp_nonblock(client_fd, 1);
		if (ret) {
			isp_close(client_fd);
			return -errno;
		}
		return client_fd;
	} else {
		return -errno;
	}
#else  //hrchen
	printf("%s not implement yet\n", __func__);
	return -RTS_ISP_EINVAL;
#endif
}

#if 0
static int uds_accept(isp_stream_t stream, int fd)
{
	int ret;
	int client_fd;

	if (!stream || fd < 0)
		return -RTS_ISP_EINVAL;

	client_fd = uds_accept_fd(fd);
	if (client_fd == -EAGAIN || client_fd == -EWOULDBLOCK)
		return RTS_ISP_OK;
	if (client_fd == -ECONNABORTED)
		return RTS_ISP_OK;
	ret = isp_stream_client_add(isp_stream_get_poll(stream), client_fd);
	if (ret)
		goto err;
	debug("%s fd:%d ok\n", __func__, client_fd);

	return RTS_ISP_OK;

err:
	isp_close(client_fd);
	isp_perror(ret, "uds accept fail");
	return ret;
}

void uds_stream_cleanup(void *priv)
{
	struct isp_uds_stream *uds_stream;

	if (!priv)
		return;

	uds_stream = priv;
	isp_free(uds_stream);

	debug("%s ok\n", __func__);
}

int isp_uds_stream_init(isp_stream_t *pstream, isp_poll_t p)
{
	int ret;
	int fd;
	struct isp_uds_stream *uds_stream = NULL;

	if (!pstream || !p) {
		ret = -RTS_ISP_EINVAL;
		goto err;
	}

	if (!isp_calloc_item(uds_stream)) {
		ret = -RTS_ISP_ENOMEM;
		goto err;
	}

	fd = uds_listen(ISP_UDS_SERVER_SOCKET);
	if (fd < 0) {
		ret = fd;
		goto err;
	}
	ret = isp_stream_init(&uds_stream->stream, p, fd, uds_accept);
	if (ret)
		goto err;

	isp_stream_set_priv(uds_stream->stream, uds_stream);
	isp_stream_set_release(uds_stream->stream, uds_stream_cleanup);

	*pstream = uds_stream->stream;
	debug("%s fd:%d ok\n", __func__, fd);

	return RTS_ISP_OK;

err:
	if (uds_stream) {
		isp_close(fd);
		isp_free(uds_stream);
	}
	isp_perror(ret, "%s");
	return ret;
}
#endif

