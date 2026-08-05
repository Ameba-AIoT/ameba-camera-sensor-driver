/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "cmsis_os2.h"
#include "rt_task.h"
#include <rts_isp_errno.h>
#include <isp_utils.h>
#include <isp_atomic.h>
#include <isp_log.h>

#define ISP_LOG_FILE "/var/log/isp.log"
#define ISP_LOG_FILE_ROLL "/var/log/isp.log.0"
#define ISP_LOG_FILE_SIZE (32 * 1024)
#define ISP_LOG_TIME_LEN sizeof("0000-00-00 00:00:00")
#if 0
struct isp_log_handle {
	uint32_t behavor;
	uint32_t debug_sel;
	FILE *logf;

	int opened:1;
	int need_header:1;
};

static osMutexId_t log_lock=NULL;
static struct isp_log_handle log_handle;

extern long	time_get_date(void);

static const char *get_time_str(void)
{
	long n;
	struct tm *tm;
	static char buf[ISP_LOG_TIME_LEN];

	n = time_get_date();
	tm = localtime((time_t const*)&n);
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
		 tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		 tm->tm_hour, tm->tm_min, tm->tm_sec);
	return buf;
}

static void write_line_header(char *logf, int level)
{
	const char *type_str;

	if (!log_handle.need_header)
		return;

	switch (level) {
	case ISP_LOG_ERR:
		type_str = "error";
		break;
	case ISP_LOG_WARNING:
		type_str = "warning";
		break;
	case ISP_LOG_INFO:
		type_str = "info";
		break;
	default:
		type_str = "debug";
		break;
	}
	sprintf(logf, "%s [%s]: ", get_time_str(), type_str);
	log_handle.need_header = RTS_ISP_FALSE;
}

static void write_line_tail(char *logf)
{
	sprintf(logf, "%s\n", logf);
	log_handle.need_header = RTS_ISP_TRUE;
}

static void __isp_log(int level, const char *fmt, va_list ap)
{
	char begin[64], buf[256], end[16];

	if (!log_handle.opened)
		return;

	if (log_handle.behavor != ISP_LOG2CONS)
		return;

	write_line_header(begin, level);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	write_line_tail(end);
	taskENTER_CRITICAL();
	printf("%s%s%s", begin, buf, end);
	taskEXIT_CRITICAL();
}

void isp_log_open(int behavor, uint32_t debug_sel)
{
	if (behavor < ISP_LOG2LOG || behavor > ISP_LOG2KMSG)
		return;

	if (!log_lock) {

		log_lock = xSemaphoreCreateMutex();
		if ( !log_lock ) {
			taskENTER_CRITICAL();
			printf("{%s} lock mutex alloc fail\n", __func__);
			taskEXIT_CRITICAL();
			//ret = RT_E_CREATE_FAIL;
			return;
		}
	}

	xSemaphoreTake(log_lock, portMAX_DELAY);

	if (log_handle.opened)
		goto out;

	switch (behavor) {
	case ISP_LOG2LOG:
	case ISP_LOG2CONS:
		break;
	case ISP_LOG2FILE:
		log_handle.logf = fopen(ISP_LOG_FILE, "a");
		break;
	case ISP_LOG2KMSG:
		log_handle.logf = fopen("/dev/kmsg", "a");
		break;
	}

	log_handle.behavor = behavor;
	log_handle.debug_sel = debug_sel;
	log_handle.need_header = RTS_ISP_TRUE;

	log_handle.opened = RTS_ISP_TRUE;
out:
	if (log_lock)
		osMutexRelease(log_lock);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
}

void isp_log_close(void)
{
	if (log_lock)
		xSemaphoreTake(log_lock, portMAX_DELAY);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
	isp_release(log_handle.logf, fclose);
	log_handle.opened = RTS_ISP_FALSE;
	if (log_lock)
		osMutexRelease(log_lock);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
}

void isp_log(int level, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (log_lock)
		xSemaphoreTake(log_lock, portMAX_DELAY);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
	__isp_log(level, fmt, ap);
	if (log_lock)
		osMutexRelease(log_lock);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
	va_end(ap);
}

void isp_debug(uint32_t type, const char *fmt, ...)
{
	if (log_lock)
		xSemaphoreTake(log_lock, portMAX_DELAY);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
	if (log_handle.debug_sel & type) {
		va_list ap;

		va_start(ap, fmt);
		__isp_log(ISP_LOG_DEBUG, fmt, ap);
		va_end(ap);
	}
	if (log_lock)
		osMutexRelease(log_lock);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}
}

void isp_log_config(int behavor, int sel)
{
	if (log_lock)
		xSemaphoreTake(log_lock, portMAX_DELAY);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}

	if (!log_handle.opened)
		goto out;
	if (behavor < ISP_LOG2LOG || behavor > ISP_LOG2KMSG)
		goto out;

	if (behavor != (int)log_handle.behavor) {
		isp_release(log_handle.logf, fclose);
		switch (behavor) {
		case ISP_LOG2LOG:
		case ISP_LOG2CONS:
			break;
		case ISP_LOG2FILE:
			log_handle.logf = fopen(ISP_LOG_FILE, "a");
			log_handle.need_header = RTS_ISP_TRUE;
			break;
		case ISP_LOG2KMSG:
			log_handle.logf = fopen("/dev/kmsg", "a");
			break;
		}
		log_handle.behavor = behavor;
	}
	log_handle.debug_sel = sel;
out:
	if (log_lock)
		osMutexRelease(log_lock);
	else {
		taskENTER_CRITICAL();
		printf("%s: log_lock NULL error!\n", __func__);
		taskEXIT_CRITICAL();
	}

}
#endif
