/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rt_types.h"
#include "rt_task.h"
#include "rts_ioctl.h"
#include <linux/eventpoll.h>
#define uint64_t __u64
#include <rts_isp_errno.h>
#include <isp_mem.h>
#include <isp_log.h>
#include <isp_utils.h>
#include <isp_poll.h>
#include <rtsavisp.h>
#include "rtx_mutex.h"
#include "rt_time.h"

#define ISP_DEBUG_TYPE ISP_DEBUG_POLL

struct isp_work_handle {
	isp_poll_t p;

	void *data;
	int ret;
	isp_work_cb work;
	isp_work_done_cb done;

	struct isp_list list;
};

struct isp_work_queue {
	isp_io_handle_t wq_io;

	osMutexId_t lock;
#if ISP_MAIN
	osSemaphoreId_t cond;
#endif
	struct isp_list queue;
	int queue_handles;
	struct isp_list done;
	struct isp_list idle;
	int idle_handles;

	osThreadId_t threads[4];
	int idle_threads;

	int shutdown;
	int shutdown_done;
};

struct isp_poll {
	//event move into isp_io_handle
	uint64_t time;
	/* if timer num become too large, change to heap or rbtree */
	struct avl_tree timers;
	struct isp_list pendings;
	struct isp_list watchers;

	struct isp_work_queue wq;

	isp_io_handle_t trig;

	int enable;
};

static int poll_timer_insert(isp_poll_t p, isp_timer_handle_t *timer);
static int poll_wq_cleanup(isp_poll_t p);

int isp_timer_init(isp_timer_handle_t *timer, isp_poll_t p,
		   isp_timer_cb cb, void *data)
{
#if 0
	if (!timer || !p || !cb)
		return -RTS_ISP_EINVAL;

	memset(timer, 0, sizeof(*timer));
	timer->p = p;
	timer->cb = cb;
	timer->data = data;
	timer->avl.key = &timer->time;
	timer->started = RTS_ISP_FALSE;
#endif
	return RTS_ISP_OK;
}

void isp_timer_cleanup(isp_timer_handle_t *timer)
{
	if (!timer || !timer->p)
		return;

	isp_timer_stop(timer);
	timer->p = NULL;
	timer->time = 0;
	timer->cb = NULL;
	timer->data = NULL;
}

int isp_timer_start(isp_timer_handle_t *timer,
		    uint32_t timeout, uint32_t interval)
{
#if 0    // disable software timer
	int ret;

	if (!timer)
		return -RTS_ISP_EINVAL;
	if (!timer->p)
		return -RTS_ISP_ENOTREADY;

	if (timer->started)
		isp_timer_stop(timer);
	timer->time = timer->p->time + timeout;
	timer->interval = interval;
	ret = poll_timer_insert(timer->p, timer);
	if (ret)
		return ret;
	timer->started = RTS_ISP_TRUE;
#endif
	return RTS_ISP_OK;
}

int isp_timer_stop(isp_timer_handle_t *timer)
{
#if 0
	if (!timer)
		return -RTS_ISP_EINVAL;
	if (!timer->p)
		return -RTS_ISP_ENOTREADY;
	if (!timer->started)
		return RTS_ISP_OK;
	avl_delete(&timer->p->timers, &timer->avl);
	timer->started = RTS_ISP_FALSE;
#endif
	return RTS_ISP_OK;
}
static inline int io_fd_removed(isp_io_handle_t *io)
{
	return io->fd < 0;
}

static int io_remove_fd(isp_io_handle_t *io)
{
	if (io_fd_removed(io))
		return RTS_ISP_OK;

	//debug("io %p remove fd %d\n", io, isp_io_fd(io));
	if (!isp_list_empty(&io->pending))
		list_remove_init(&io->pending);
	if (!isp_list_empty(&io->watcher)) {
		int status;
		status = osEventFlagsDelete(io->evt_id);
		if ( status != osOK )
			isp_perror(status, "%s: osEventFlagsDelete err", __func__);
		io->evt_id = NULL;
		list_remove_init(&io->watcher);
	}
	if (io->nonclose)
		io->fd = -1;
	else
		isp_close(io->fd);
	io->p = NULL;
	io->events = 0;

	return RTS_ISP_OK;
}

static void io_release(isp_io_handle_t *io)
{
	isp_assert(io->release);
	io->release(io);
}

int isp_io_init(isp_io_handle_t *io, isp_poll_t p, int fd, isp_io_cb cb)
{
	int ret;

	if (!io || !p || fd < 0 || !cb)
		return -RTS_ISP_EINVAL;
#if 1
	ret = isp_nonblock(fd, 1);
	if (!ret)
		ret = isp_closexec(fd, 1);
	if (ret)
		return ret;
#endif
	memset(io, 0, sizeof(*io));
	io->p = p;
	io->fd = fd;
	io->cb = cb;
	io->evt_id = osEventFlagsNew(NULL);
	if (io->evt_id == NULL) {
		isp_perror(RTS_ISP_ENOMEM, "isp poll event flag new err");
		return -RTS_ISP_ENOMEM;
	}
	list_init(&io->pending);
	list_init(&io->watcher);
	isp_io_set_release(io, isp_io_cleanup);

	isp_info("%s: 0x%08x\r\n",__func__, (int)cb);
	return RTS_ISP_OK;
}

void isp_io_cleanup(isp_io_handle_t *io)
{
	if (!io || !io->p)
		return;

	//debug("fd: %d, event: %u cleaning up\n", io->fd, io->events);

	io_remove_fd(io);
	io->cb = NULL;
	io->release = NULL;
	io->nonclose = RTS_ISP_FALSE;

	//debug("%s ok\r\n", __func__);
}

int isp_io_event_add(isp_io_handle_t *io, uint32_t events)
{
	events &= EPOLLIN | EPOLLOUT | EPOLLET;

	if (!io || !events)
		return -RTS_ISP_EINVAL;

	if (!io->p)
		return -RTS_ISP_ENOTREADY;

	if (io_fd_removed(io))
		return -RTS_ISP_EPERM;

	if ((io->events & events) == events)
		return RTS_ISP_OK;

	io->events |= events;
	if (isp_list_empty(&io->pending))
		list_insert_tail(&io->p->pendings, &io->pending);

	return RTS_ISP_OK;
}

int isp_io_event_del(isp_io_handle_t *io, uint32_t events)
{
	events &= EPOLLIN | EPOLLOUT | EPOLLET;

	if (!io || !events)
		return -RTS_ISP_EINVAL;

	if (!io->p)
		return -RTS_ISP_ENOTREADY;

	if (io_fd_removed(io))
		return -RTS_ISP_EPERM;

	if ((io->events & events) == 0)
		return RTS_ISP_OK;

	io->events &= ~events;
	if (isp_list_empty(&io->pending))
		list_insert_tail(&io->p->pendings, &io->pending);

	return RTS_ISP_OK;
}

int isp_io_fd(isp_io_handle_t *io)
{
	if (io && io->p)
		return io->fd;
	return -1;
}

isp_poll_t isp_io_get_poll(isp_io_handle_t *io)
{
	if (io && io->p)
		return io->p;
	return NULL;
}

int isp_io_set_release(isp_io_handle_t *io, isp_io_release_cb release)
{
	if (!io || !release)
		return -RTS_ISP_EINVAL;
	if (!io->p)
		return -RTS_ISP_ENOTREADY;
	io->release = release;
	return RTS_ISP_OK;
}

static int poll_timer_cmp(const void *k1, const void *k2, void *ptr)
{
	return *(uint64_t *)k1 - *(uint64_t *)k2;
}

static int poll_timer_insert(isp_poll_t p, isp_timer_handle_t *timer)
{
	if (!p || !timer)
		return -RTS_ISP_EINVAL;

	avl_insert(&p->timers, &timer->avl);

	return RTS_ISP_OK;
}

static int poll_cleanup_handles(isp_poll_t p)
{
	struct isp_list *list;

	if (!p)
		return -RTS_ISP_EINVAL;

	while (!avl_is_empty(&p->timers)) {
		isp_timer_handle_t *timer;

		//debug("cleanup timers\n");
		timer = avl_first_element(&p->timers, timer, avl);
		isp_timer_cleanup(timer);
	}
	while (!isp_list_empty(&p->pendings)) {
		isp_io_handle_t *io;

		//debug("cleanup pendings\n");
		list = list_head(&p->pendings);
		io = list_data(list, struct isp_io_handle, pending);
		isp_release(io, io_release);
	}
	while (!isp_list_empty(&p->watchers)) {
		isp_io_handle_t *io;

		//debug("cleanup watchers\n");
		list = list_head(&p->watchers);
		io = list_data(list, struct isp_io_handle, watcher);
		isp_release(io, io_release);
	}
	return RTS_ISP_OK;
}

static int poll_read_eventfd(isp_io_handle_t *io)
{
	int flag;
	flag = osEventFlagsWait(io->evt_id, io->events|EPOLLDFAULT, 
						osFlagsWaitAny, osWaitForever );
//asm("sdbbp");
	if ( flag < 0 )
		isp_perror(flag, "%s osEventFlagsWait fail", __func__);

	return RTS_ISP_OK;
}

static int poll_write_eventfd(isp_io_handle_t *io)
{
	int status;
	status = osEventFlagsSet(io->evt_id, io->events);  //inform poll stop
	isp_info("%s 0x%08x 0x%08x \r\n", __func__, io->evt_id, io->events);
	if ( status < 0 )
		isp_perror(status, "%s: osEventFlagsSet err", __func__);
	return RTS_ISP_OK;
}

static int poll_trig_read(isp_io_handle_t *io, uint32_t events)
{
	int ret;

	if (!io || !events)
		return -RTS_ISP_EINVAL;

	isp_info("%s read\r\n", __func__);
	isp_assert(events & EPOLLIN);

	ret = poll_read_eventfd(io);
	if (ret)
		return ret;

	printf("%s done\r\n", __func__);


	return RTS_ISP_OK;
}

static int poll_trig_init(isp_poll_t p)
{
	int ret;
	int fd;

	if (!p)
		return -RTS_ISP_EINVAL;

	isp_info("%s\r\n",__func__);
	fd = ID_RTS_ISP_DEV;
	ret = isp_io_init(&p->trig, p, fd, poll_trig_read);
	if (ret) {
		isp_close(fd);
		goto err;
	}
	ret = isp_io_event_add(&p->trig, EPOLLIN);
	if (ret)
		goto err;

	return RTS_ISP_OK;

err:
	isp_io_cleanup(&p->trig);
	return ret;
}

static int poll_trig_cleanup(isp_poll_t p)
{
	if (!p)
		return -RTS_ISP_EINVAL;

	isp_io_cleanup(&p->trig);
	//isp_info("%s ok\r\n", __func__);

	return RTS_ISP_OK;
}

static struct isp_work_handle *poll_wq_get_handle(struct isp_work_queue *wq)
{
	struct isp_work_handle *handle;
	int ret = 0;
	
	ret = xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("poll_wq_get_handle wait wq->lock timeout\n\r");
		return NULL;
	}
	if (wq->shutdown) {
		xSemaphoreGive(wq->lock);
		return NULL;
	}
	if (wq->idle_handles) {
		isp_assert(!isp_list_empty(&wq->idle));
		wq->idle_handles--;
		handle = list_data(list_next(&wq->idle),
				   struct isp_work_handle, list);
		list_remove_init(&handle->list);
	} else {
		if (!isp_calloc_item(handle))
			goto out;
		list_init(&handle->list);
	}
out:
	xSemaphoreGive(wq->lock);
	return handle;
}

static void poll_wq_put_handle(struct isp_work_handle *handle)
{
	struct isp_work_queue *wq;
	int ret = 0;

	if (!handle || !handle->p)
		return;

	wq = &handle->p->wq;
	ret = xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("poll_wq_put_handle wait wq->lock timeout\n\r");
		return;
	}
	if (wq->shutdown || wq->idle_handles > 8) {
		isp_free(handle);
	} else {
		list_insert_tail(&wq->idle, &handle->list);
		wq->idle_handles++;
	}
	xSemaphoreGive(wq->lock);
}

static int poll_wq_read(isp_io_handle_t *io, uint32_t events)
{
	int ret;
	struct isp_work_queue *wq;
	struct isp_list done;
	struct isp_work_handle *handle;
	struct isp_work_handle *next;

	if (!io || !events)
		return -RTS_ISP_EINVAL;

	isp_assert(events & EPOLLIN);

	ret = poll_read_eventfd(io);
	if (ret)
		return ret;

	wq = &io->p->wq;

	ret = xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("poll_wq_read wait wq->lock timeout\n\r");
		return -ETIMEDOUT;
	}
	list_move_list(&wq->done, &done);
	xSemaphoreGive(wq->lock);

	list_foreach_data_safe(handle, next, &done, list) {
		list_remove_init(&handle->list);
		if (handle->done)
			ret = handle->done(handle->data, handle->ret);
		poll_wq_put_handle(handle);
		if (ret) {
			if (xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
				isp_error("poll_wq_read error wait wq->lock timeout\n\r");
				ret = -ETIMEDOUT;
				goto err;
			}
			list_move_list(&done, &wq->done);
			xSemaphoreGive(wq->lock);
			poll_write_eventfd(io);
			goto err;
		}
	}

	debug("%s done\n", __func__);

	return RTS_ISP_OK;
err:
	isp_perror(ret, "work queue done callback error");
	return ret;
}
static int poll_wq_init(isp_poll_t p)
{
	int ret;
	int fd;
	struct isp_work_queue *wq;

	if (!p)
		return -RTS_ISP_EINVAL;

	wq = &p->wq;

	const osMutexAttr_t wqlock_Mutex_attr = {
	  "wqlockMutex",                          	// human readable mutex name
	  osMutexRecursive | osMutexPrioInherit,    // attr_bits
	  NULL,                                     // memory for control block   
	  0U                                        // size for control block
	};
	wq->lock = osMutexNew(&wqlock_Mutex_attr);
	if (wq->lock == NULL)
	{
		printf("%s: fail! new wqlockMutex\n", __func__);
		return -RTS_ISP_ENOMEM;
	}
	//osSemaphoreAttr_t wqsemAttr = { .name = "wqSemaphore" };
	//wq->cond = osSemaphoreNew(1, 0, &wqsemAttr);
#if ISP_MAIN
	wq->cond = xSemaphoreCreateCounting(1, 0);

	if (wq->cond == NULL)
	{
		printf("%s: fail! new wqSemaphore\n", __func__);
		return -RTS_ISP_ENOMEM;
	}
#endif
	list_init(&wq->queue);
	list_init(&wq->done);
	list_init(&wq->idle);
	wq->queue_handles = 0;
	wq->idle_handles = 0;
	wq->shutdown = 1;

	//fd = rts_open("/poll/wq");
	fd = ID_RTS_POLL_WQ;
	ret = isp_io_init(&wq->wq_io, p, fd, poll_wq_read);
	if (ret) {
		isp_close(fd);
		goto err;
	}
	ret = isp_io_event_add(&wq->wq_io, EPOLLIN);
	if (ret)
		goto err;

	debug("%s ok\r\n", __func__);
	return RTS_ISP_OK;
err:
	poll_wq_cleanup(p);
	return ret;
}

static void poll_wq_cleanup_handles(struct isp_work_queue *wq)
{
	struct isp_work_handle *handle;
	struct isp_work_handle *next;

	if (!wq || !wq->shutdown)
		return;

	list_foreach_data_safe(handle, next, &wq->queue, list) {
		list_remove_init(&handle->list);
		if (handle->done)
			handle->done(handle->data, -RTS_ISP_ECANCELD);
		isp_free(handle);
	}
	wq->queue_handles = 0;

	list_foreach_data_safe(handle, next, &wq->done, list) {
		list_remove_init(&handle->list);
		if (handle->done)
			handle->done(handle->data, handle->ret);
		isp_free(handle);
	}

	list_foreach_data_safe(handle, next, &wq->idle, list) {
		list_remove_init(&handle->list);
		wq->idle_handles--;
		isp_free(handle);
	}
}

static int poll_wq_cleanup(isp_poll_t p)
{
	struct isp_work_queue *wq;

	if (!p)
		return -RTS_ISP_EINVAL;

	wq = &p->wq;

	isp_assert(wq->shutdown);
	isp_io_cleanup(&wq->wq_io);
	poll_wq_cleanup_handles(wq);
#if ISP_MAIN
	if (wq->cond) {
		vSemaphoreDelete(wq->cond);
		wq->cond = NULL;
	}
#endif
	//osMutexDelete(wq->lock);
	if (wq->lock) {
		vSemaphoreDelete(wq->lock);
		wq->lock = NULL;
	}
	//debug("%s ok\n", __func__);

	return RTS_ISP_OK;
}

int isp_poll_create(isp_poll_t *pp)
{
	int ret;
	isp_poll_t p = NULL;

	if (!pp)
		return -RTS_ISP_EINVAL;
	if (!isp_calloc_item(p))
		return -RTS_ISP_ENOMEM;

	//event move into isp_io_handle
	avl_init(&p->timers, poll_timer_cmp, RTS_ISP_TRUE, NULL);
	list_init(&p->pendings);
	list_init(&p->watchers);
	ret = poll_wq_init(p);
	if (ret)
		goto err;
	ret = poll_trig_init(p);
	if (ret)
		goto err;

	isp_poll_update_time(p);

	*pp = p;

	debug("%s ok\r\n", __func__);

	return RTS_ISP_OK;
err:
	isp_release(p, isp_poll_release);
	return ret;
}

void isp_poll_release(isp_poll_t p)
{
	if (!p)
		return;

	poll_trig_cleanup(p);
	poll_wq_cleanup(p);
	poll_cleanup_handles(p);
	//event move into isp_io_handle
	isp_free(p);
}

int isp_poll_update_time(isp_poll_t p)
{
	if (!p)
		return -RTS_ISP_EINVAL;

	p->time = (uint64_t)xTaskGetTickCount() / portTICK_PERIOD_MS * 1000000;
	return RTS_ISP_OK;
}
extern void isp_top_set_status(enum rts_isp_status status);
uint32_t pull_loop_time = 0;
int isp_poll_loop_run(isp_poll_t p)
{
	int ret;

	isp_top_set_status(RTS_ISP_RUNNING);
	pull_loop_time = hal_read_curtime_us();
#if ISP_MAIN

	//while (poll_alive(p)) {
	while (1) {
		//ret = poll_run(p);
		//if (ret && ret != -RTS_ISP_EINTR) {
		//	isp_perror(ret, "isp poll loop exit err");
		//	break;
		//}

		//osDelay(50000);

//		if (osSemaphoreAcquire(p->wq.cond, osWaitForever) != osOK) {
		if (xSemaphoreTake(p->wq.cond, osWaitForever) != pdTRUE) {
			isp_error("isp_poll_loop_run wait p->wq.cond timeout\n\r");
			continue;
		}

		ret = RTS_ISP_OK;
	}
	//printf("%s event loop stoped\r\n", __func__);
	//poll_wq_stop_threads(&p->wq);
	return ret;
#else
	return RTS_ISP_OK;
	
#endif
}

int isp_poll_loop_stop(isp_poll_t p)
{
	if (!p)
		return -RTS_ISP_EINVAL;
	p->enable = RTS_ISP_FALSE;
	//poll_trig(p);
	return RTS_ISP_OK;
}
#if 0
int isp_poll_add_work(isp_poll_t p, void *data,
		      isp_work_cb work, isp_work_done_cb done)
{
	struct isp_work_handle *handle;
	struct isp_work_queue *wq;
	int ret = 0;

	if (!p || !work)
		return -RTS_ISP_EINVAL;

	wq = &p->wq;
	handle = poll_wq_get_handle(wq);
	if (!handle)
		return -RTS_ISP_ENOTREADY;
	handle->p = p;
	handle->data = data;
	handle->work = work;
	handle->done = done;

	ret = xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("isp_poll_add_work wait wq->lock timeout\n\r");
		return -RTS_ISP_EAGAIN;
	}
	if (wq->shutdown || wq->queue_handles == ARRAY_SIZE(wq->threads)) {
		xSemaphoreGive(wq->lock);
		poll_wq_put_handle(handle);
		return -RTS_ISP_EAGAIN;
	}
	list_insert_tail(&wq->queue, &handle->list);
	wq->queue_handles++;
	if (wq->idle_threads > 0)
		osSemaphoreRelease(wq->cond);
	xSemaphoreGive(wq->lock);

	return RTS_ISP_OK;
}
#endif
int isp_poll_cancel_work(isp_poll_t p, void *data,
			 isp_work_cb work, isp_work_done_cb done)
{
	struct isp_work_queue *wq;
	struct isp_work_handle *handle;
	struct isp_work_handle *next;
	int ret = 0;

	if (!p || !work)
		return -RTS_ISP_EINVAL;

	wq = &p->wq;
	ret = xSemaphoreTake(wq->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("isp_poll_cancel_work wait wq->lock timeout\n\r");
		return -RTS_ISP_ENOTREADY;
	}
	if (wq->shutdown) {
		xSemaphoreGive(wq->lock);
		return -RTS_ISP_ENOTREADY;
	}
	list_foreach_data_safe(handle, next, &wq->queue, list) {
		int ret = RTS_ISP_OK;

		if (handle->p == p && handle->data == data &&
		    handle->work == work && handle->done == done) {
			list_remove_init(&handle->list);
			wq->queue_handles--;
			xSemaphoreGive(wq->lock);
			if (handle->done)
				ret = handle->done(handle->data,
						   -RTS_ISP_ECANCELD);
			poll_wq_put_handle(handle);
			return ret;
		}
	}
	xSemaphoreGive(wq->lock);
	return -RTS_ISP_ENOITEM;
}

void isp_poll_set_fd_nonclose(isp_poll_t p, int fd, int nonclose)
{
	struct isp_io_handle *io;

	if (!p || fd < 0)
		return;

	list_foreach_data(io, &p->pendings, pending) {
		if (io->fd == fd) {
			io->nonclose = nonclose;
			return;
		}
	}
	list_foreach_data(io, &p->watchers, watcher) {
		if (io->fd == fd) {
			io->nonclose = nonclose;
			return;
		}
	}
}
