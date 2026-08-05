#ifndef _ISP_POLL_H_INC_
#define _ISP_POLL_H_INC_

#include <stdint.h>
#include <isp_avl.h>
#include "cmsis_os2.h"

typedef struct isp_poll *isp_poll_t;

typedef struct isp_io_handle isp_io_handle_t;
typedef struct isp_timer_handle isp_timer_handle_t;

typedef int (*isp_io_cb)(isp_io_handle_t *io, uint32_t events);
typedef int (*isp_timer_cb)(isp_timer_handle_t *timer, void *data);
typedef int (*isp_work_cb)(void *data);
typedef int (*isp_work_done_cb)(void *data, int ret);
typedef void (*isp_io_release_cb)(isp_io_handle_t *io);

struct isp_io_handle {
	isp_poll_t p;

	int fd;
	osEventFlagsId_t evt_id;
	uint32_t events;

	isp_io_cb cb;

	struct isp_list pending;
	struct isp_list watcher;

	isp_io_release_cb release;

	int nonclose:1;
};

struct isp_timer_handle {
	isp_poll_t p;

	uint64_t time;
	uint32_t interval;
	isp_timer_cb cb;
	void *data;

	struct avl_node avl;

	int started:1;
};


int isp_timer_init(isp_timer_handle_t *timer, isp_poll_t p,
		   isp_timer_cb cb, void *data);
void isp_timer_cleanup(isp_timer_handle_t *timer);
int isp_timer_start(isp_timer_handle_t *timer,
		    uint32_t timeout, uint32_t interval);
int isp_timer_stop(isp_timer_handle_t *timer);

int isp_io_init(isp_io_handle_t *io, isp_poll_t p, int fd, isp_io_cb cb);
void isp_io_cleanup(isp_io_handle_t *io);
int isp_io_event_add(isp_io_handle_t *io, uint32_t events);
int isp_io_event_del(isp_io_handle_t *io, uint32_t events);
int isp_io_fd(isp_io_handle_t *io);
isp_poll_t isp_io_get_poll(isp_io_handle_t *io);
int isp_io_set_release(isp_io_handle_t *io, isp_io_release_cb release);

int isp_poll_create(isp_poll_t *pp);
void isp_poll_release(isp_poll_t p);
int isp_poll_update_time(isp_poll_t p);
int isp_poll_loop_run(isp_poll_t p);
int isp_poll_loop_stop(isp_poll_t p);
//int isp_poll_add_work(isp_poll_t p, void *data,
//		      isp_work_cb work, isp_work_done_cb done);
int isp_poll_cancel_work(isp_poll_t p, void *data,
			 isp_work_cb work, isp_work_done_cb done);
void isp_poll_set_fd_nonclose(isp_poll_t p, int fd, int nonclose);

#endif /* _ISP_POLL_H_INC_ */
