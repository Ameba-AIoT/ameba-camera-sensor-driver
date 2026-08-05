#ifndef _ISP_LOG_H_INC
#define _ISP_LOG_H_INC

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <rt_log.h>
#define __FILENAME__ __FILE__
#include <rts_isp_errno.h>

enum isp_log_level {
	ISP_LOG_ERR = LOG_ERR,
	ISP_LOG_WARNING = LOG_WARNING,
	ISP_LOG_INFO = LOG_INFO,
	ISP_LOG_DEBUG = LOG_DEBUG,
};

enum {
	_DEBUG_CORE = 1,
	_DEBUG_MOD,
	_DEBUG_POLL,
	_DEBUG_V4L2,
	_DEBUG_ALGO,
	_DEBUG_STREAM,
	_DEBUG_UDS,
	_DEBUG_DRIVER,
	_DEBUG_NOTIFY,
	_DEBUG_RGB2YUV,
	_DEBUG_CONTROL,
	_DEBUG_VCTRL,
	_DEBUG_SENSOR,
	_DEBUG_GLOBAL,
	_DEBUG_INTERFACE,
	_DEBUG_CROP,
	_DEBUG_BLC,
	_DEBUG_AE,
	_DEBUG_AWB,
	_DEBUG_FLICK,
	_DEBUG_WDR,
};

enum isp_debug_type {
	ISP_DEBUG_CORE = 1 << _DEBUG_CORE,
	ISP_DEBUG_MOD = 1 << _DEBUG_MOD,
	ISP_DEBUG_POLL = 1 << _DEBUG_POLL,
	ISP_DEBUG_V4L2 = 1 << _DEBUG_V4L2,
	ISP_DEBUG_ALGO = 1 << _DEBUG_ALGO,
	ISP_DEBUG_STREAM = 1 << _DEBUG_STREAM,
	ISP_DEBUG_UDS = 1 << _DEBUG_UDS,
	ISP_DEBUG_DRIVER = 1 << _DEBUG_DRIVER,
	ISP_DEBUG_NOTIFY = 1 << _DEBUG_NOTIFY,
	ISP_DEBUG_RGB2YUV = 1 << _DEBUG_RGB2YUV,
	ISP_DEBUG_GLOBAL = 1 << _DEBUG_GLOBAL,
	ISP_DEBUG_CONTROL = 1 << _DEBUG_CONTROL,
	ISP_DEBUG_VCTRL = 1 << _DEBUG_VCTRL,
	ISP_DEBUG_SENSOR = 1 << _DEBUG_SENSOR,
	ISP_DEBUG_INTERFACE = 1 << _DEBUG_INTERFACE,
	ISP_DEBUG_CROP = 1 << _DEBUG_CROP,
	ISP_DEBUG_BLC = 1 << _DEBUG_BLC,
	ISP_DEBUG_AE = 1 << _DEBUG_AE,
	ISP_DEBUG_AWB = 1 << _DEBUG_AWB,
	ISP_DEBUG_FLICK = 1 << _DEBUG_FLICK,
	ISP_DEBUG_WDR = 1 << _DEBUG_WDR,
};

#define ISP_DEBUG_CORE_ALL (ISP_DEBUG_CORE | ISP_DEBUG_MOD | \
			    ISP_DEBUG_POLL | ISP_DEBUG_STREAM | \
			    ISP_DEBUG_UDS | ISP_DEBUG_DRIVER | \
			    ISP_DEBUG_NOTIFY)

enum isp_log_to {
	ISP_LOG2LOG,
	ISP_LOG2CONS,
	ISP_LOG2FILE,
	ISP_LOG2KMSG,
};

void isp_log_open(int behavor, uint32_t debug_sel);
void isp_log_close(void);
void isp_log(int level, const char *fmt, ...);
void isp_log_config(int behavor, int sel);
#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#define isp_warning DBG_ISP_WARN
#define isp_info DBG_ISP_INFO
#define isp_error DBG_ISP_ERR
#else
#define isp_warning(fmt, arg...)	printf("[%s][%lu]Warn"fmt"\r",__func__,__LINE__, ##arg)
#define isp_info(fmt, arg...)		do { ; } while(0)
//#define isp_info(fmt, arg...)		printf("[%s][%d]Info"fmt"\r",__func__,__LINE__, ##arg)
#define isp_error(fmt, arg...)		printf("[%s][%u]Err"fmt"\r",__func__,__LINE__, ##arg)
#endif



#define isp_perror(errnum, fmt, ...) \
	do { \
		/*char buf[256]; */\
		/*rts_isp_strerror(errnum, buf, sizeof(buf)); */\
		isp_error(fmt " -> %d\n", ##__VA_ARGS__, errnum); \
	} while (0)

#define isp_info_cont isp_info

#ifndef ISP_NO_DEBUG
void isp_debug(uint32_t type, const char *fmt, ...);
#define debug(fmt, ...) isp_info(fmt, ##__VA_ARGS__)
#else
#define isp_debug(fmt, ...)
#define debug(fmt, ...)
#endif

#define isp_assert(expr) \
	do { \
		if (!(expr)) { \
			isp_error("Failed to assert: %s\n", #expr); \
			abort(); \
		} \
	} while (0)

#endif /* _ISP_LOG_H_INC */
