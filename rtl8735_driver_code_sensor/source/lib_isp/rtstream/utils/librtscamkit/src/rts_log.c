/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rts_log.c
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#define __USE_BSD
//#define _BSD_SOURCE
#include <stdarg.h>
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include <rt_log.h>
#include <rtscamkit.h>

#define RTS_LOG_LEVEL_LIMIT		(sizeof(uint32_t) * 8)
#if 0
struct rts_log_t {
	uint32_t log_mask;
	uint32_t log_level;
	char ident[128];
	FILE *stream;
	char filename[256];
	void (*log_callback)(const char *, va_list);
	//osMutexId_t log_mutex;
};

static struct rts_log_t log_handle = {
	.log_mask	= RTS_LOG_MASK_SYSLOG,
	.log_level	= 0xfe,
	.ident		= "[rts camera]",
	.stream		= NULL,
	.filename	= "\0",
	.log_callback	= NULL,
};

/*
static int convert_to_syslog_priority(int priority)
{
	int ret = LOG_DEBUG;

	switch (priority) {
	case RTS_LOG_DEBUG:
		ret = LOG_DEBUG;
		break;
	case RTS_LOG_INFO:
		ret = LOG_INFO;
		break;
	case RTS_LOG_NOTICE:
		ret = LOG_NOTICE;
		break;
	case RTS_LOG_WARNING:
		ret = LOG_WARNING;
		break;
	case RTS_LOG_ERR:
		ret = LOG_ERR;
		break;
	case RTS_LOG_CRIT:
		ret = LOG_CRIT;
		break;
	case RTS_LOG_ALERT:
		ret = LOG_ALERT;
		break;
	case RTS_LOG_EMERG:
		ret = LOG_EMERG;
		break;
	default:
		ret = LOG_INFO;
		break;
	}

	return ret;
}

static int __rts_log(FILE *stream, int priority, const char *format, va_list ap)
{
	int ret = 0;

	if (strlen(log_handle.ident) > 0)
		ret = fprintf(stream, "%s : ", log_handle.ident);
	ret += vfprintf(stream, format, ap);

	return ret;
}
*/

void rts_log(int priority, const char *format, ...)
{

}

int rts_set_log_ident(const char *ident)
{
	int ret;

	ret = RTS_OK;

	return ret;
}

static uint32_t __rts_set_log_mask(uint32_t mask)
{
	int idx;

	if (!mask)
		return log_handle.log_mask;

	for (idx = RTS_LOG_IDX_CONS; idx < RTS_LOG_IDX_RESERVED; idx++) {
		uint32_t enable = RTS_CHECK_BIT(mask, idx);
		uint32_t current = RTS_CHECK_BIT(log_handle.log_mask, idx);

		if (enable == current)
			continue;

		if (current) {
			log_handle.log_mask =
					RTS_CLEAR_BIT(log_handle.log_mask, idx);
		} else {
			log_handle.log_mask =
					RTS_SET_BIT(log_handle.log_mask, idx);
		}
	}

	return log_handle.log_mask;
}

uint32_t rts_set_log_mask(uint32_t mask)
{
	mask = __rts_set_log_mask(mask);

	return mask;
}

uint32_t rts_get_log_mask(void)
{
	return log_handle.log_mask;
}

static uint32_t __rts_clr_log_mask(void)
{
	uint32_t mask = log_handle.log_mask;

	log_handle.log_mask = 0;

	return mask;
}

uint32_t rts_clr_log_mask(void)
{
	uint32_t mask;

	mask = __rts_clr_log_mask();

	return mask;
}

static int __rts_set_log_file(const char *filename)
{
	const int size = sizeof(log_handle.filename);

	if (!filename || strlen(filename) == 0) {
//		RTS_SAFE_RELEASE(log_handle.stream, fclose);
		log_handle.filename[0] = '\0';
		return 0;
	}

	if (0 == strncmp(filename, log_handle.filename, size))
		return 0;

//	RTS_SAFE_RELEASE(log_handle.stream, fclose);
	log_handle.stream = fopen(filename, "w");
	if (!log_handle.stream)
		return RTS_RETURN(RTS_E_OPEN_FAIL);

	snprintf(log_handle.filename, size, "%s", filename);

	return RTS_OK;
}

int rts_set_log_file(const char *filename)
{
	int ret;

	ret = __rts_set_log_file(filename);

	return ret;
}

static int __rts_set_log_callback(void (*callback)(const char *, va_list))
{
	log_handle.log_callback = callback;

	return RTS_OK;
}

int rts_set_log_callback(void (*callback)(const char *, va_list))
{
	int ret;

	ret = __rts_set_log_callback(callback);

	return ret;
}

static uint32_t __rts_set_log_level(uint32_t level_mask)
{
	int i;

	if (!level_mask)
		return log_handle.log_level;

	for (i = RTS_LOG_DEBUG; (uint32_t)i < RTS_LOG_LEVEL_LIMIT; i++) {
		if (RTS_CHECK_BIT(level_mask, i)) {
			log_handle.log_level =
					RTS_SET_BIT(log_handle.log_level, i);
		} else {
			log_handle.log_level =
					RTS_CLEAR_BIT(log_handle.log_level, i);
		}
	}

	return log_handle.log_level;
}

uint32_t rts_set_log_level(uint32_t level_mask)
{
	level_mask = __rts_set_log_level(level_mask);

	return level_mask;
}

uint32_t rts_get_log_level(void)
{
	return log_handle.log_level;
}

static int __rts_clr_log_level(void)
{
	uint32_t level = log_handle.log_level;

	log_handle.log_level = 0;

	return level;
}

uint32_t rts_clr_log_level(void)
{
	uint32_t level;

	level = __rts_clr_log_level();

	return level;
}

int rts_check_log_priority(int priority)
{
	if (priority < 0 || (uint32_t)priority > RTS_LOG_LEVEL_LIMIT)
		return RTS_RETURN(RTS_E_OUT_OF_RANGE);

	return RTS_OK;
}


static int __rts_set_log_enable(int priority, int enable)
{
	if (enable)
		log_handle.log_level =
				RTS_SET_BIT(log_handle.log_level, priority);
	else
		log_handle.log_level =
				RTS_CLEAR_BIT(log_handle.log_level, priority);

	return RTS_OK;
}

int rts_set_log_enable(int priority, int enable)
{
	int ret;

	ret = rts_check_log_priority(priority);
	if (RTS_IS_ERR(ret))
		return ret;

	ret = __rts_set_log_enable(priority, enable);

	return ret;
}

int rts_get_log_enable(int priority, int enable)
{
	int ret;

	ret = rts_check_log_priority(priority);
	if (RTS_IS_ERR(ret))
		return 0;

	return RTS_CHECK_BIT(log_handle.log_level, priority);
}

void rts_dump_data(char *data, unsigned int len, unsigned int row)
{
#if 0
//	unsigned int i;

	if (!data || !len)
		return;

	if (!row)
		row = 16;
#endif
	
}
#endif
