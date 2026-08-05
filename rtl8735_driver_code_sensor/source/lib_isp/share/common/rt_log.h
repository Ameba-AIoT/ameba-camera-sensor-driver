// ============================================================================
// Important!! since rt_log may be called from /rlx
//	- MUST follow same rule with /rlx
//	- NOT depaneds on rt_types & rt_code.
// ============================================================================
#ifndef RT_LOG_H
#define RT_LOG_H
#include <stdio.h>
#include "rt_config.h"
//#include "rt_printf.h"

#ifndef rt_printf
#define rt_printf           printf
#endif

/**
 * priorities/facilities are encoded into a single 32-bit quantity, where the
 * bottom 3 bits are the priority (0-7) and the top 28 bits are the facility
 * (0-big number).	Both the priorities and the facilities map roughly
 * one-to-one to strings in the syslogd(8) source code.	 This mapping is
 * included in this file.
 *
 * priorities (these are ordered)
 */

// log level
#define	LOG_EMERG			0				// system is unusable
#define LOG_FATAL			LOG_EMERG
#define	LOG_ALERT			1				// action must be taken immediately
#define	LOG_CRIT			2				// critical conditions
#define	LOG_ERR				3				// error conditions
#define	LOG_WARNING			4				// warning conditions
#define	LOG_NOTICE			5				// normal but significant condition
#define	LOG_INFO			6				// informational
#define	LOG_DEBUG			7				// debug-level messages
// log tag
#define TAG_EMERG			"<F> "
#define TAG_FATAL			TAG_EMERG
#define TAG_ALERT			"<A> "
#define TAG_CRIT			"<C> "
#define TAG_ERR				"<E> "
#define TAG_WARNING			"<W> "
#define TAG_NOTICE			"<N> "
#define TAG_INFO			"<I> "
#define TAG_DEBUG			"<D> "

#define CLR_RESET			"\x1B[0m"

#if CFG_LOG_COLOR_EN
#define CLR_EMERG			"\x1B[1;31m"	// Bright Red
#define CLR_FATAL			CLR_EMERG
#define CLR_ALERT			"\x1B[1;33m"	// Bright Yellow
#define CLR_CRIT			"\x1B[35m"		// Magenta
#define CLR_ERR				"\x1B[31m"		// Red
#define CLR_WARNING			"\x1B[33m"		// Yellow
#define CLR_NOTICE			"\x1B[36m"		// Cyan
#define CLR_INFO			"\x1B[34m"		// Blue
#define CLR_DEBUG			"\x1B[32m"		// Green
#else
#define CLR_EMERG
#define CLR_FATAL
#define CLR_ALERT
#define CLR_CRIT
#define CLR_ERR
#define CLR_WARNING
#define CLR_NOTICE
#define CLR_INFO
#define CLR_DEBUG
#endif	// CFG_LOG_COLOR_EN

extern int g_log_enable;
extern int g_log_level;

#define rt_log_get_enable()		(g_log_enable)
#define rt_log_set_enable(b)	(g_log_enable = (b))
#define rt_log_get_level()		(g_log_level)
#define	rt_log_set_level(n)		(g_log_level = (n))

// note: the last printf() is for reseting color
#define rt_fatal(fmt, args...) \
do { \
	printf(CLR_FATAL TAG_FATAL "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	printf("\n"); \
	while (1); \
} while (0)

#define rt_alert(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_ALERT) { \
		printf(CLR_ALERT TAG_ALERT "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_crit(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_CRIT) { \
		printf(CLR_CRIT TAG_CRIT "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_err(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_ERR) { \
		printf(CLR_ERR TAG_ERR "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_warning(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_WARNING) { \
		printf(CLR_WARNING TAG_WARNING "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_notice(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_NOTICE) { \
		printf(CLR_NOTICE TAG_NOTICE "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_info(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_INFO) { \
		printf(CLR_INFO TAG_INFO "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

// note:
//	this should define in DEBUG build and not defined in RELEASE build.
//	since it can't pass linking in current DEBUG build, we always define it for now.
//
#define rt_debug(fmt, args...) \
do { \
	if (g_log_enable && g_log_level >= LOG_DEBUG) { \
		printf(CLR_DEBUG TAG_DEBUG "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args); \
	} \
} while (0)

#define rt_should_not_reach()	rt_fatal("should not reach!!\n")

#ifndef RT_BUG
#define RT_BUG() \
	do { \
		rt_alert("BUG!!\n"); \
		while (1); \
	} while (0)

#define RT_BUG_ON(cond) \
	do { \
		if (cond) { RT_BUG(); } \
	} while (0)
#endif	// RT_BUG

#define RT_WARN_ON(cond) \
	do { \
		if (cond) { rt_warning(); } \
	} while (0)

#ifdef DEBUG
# define RT_ASSERT(cond) \
	do { \
		if (!(cond)) { rt_alert("assert!!\n"); while (1); } \
	} while (0)

#else
# define RT_ASSERT(cond)
#endif	// DEBUG

// ----------------------------------------------------------------------------
//  my_xxx: for programmer temporary use, she/he can remove after coding.
// ----------------------------------------------------------------------------
#ifndef my_printf
#define my_printf	printf
#endif

#ifndef my_debug
#define my_debug(fmt, args...)	printf(CLR_DEBUG TAG_DEBUG "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args)
#endif

#ifndef my_err
#define my_err(fmt, args...)	printf(CLR_ERR TAG_ERR "[%s, %d] " fmt CLR_RESET, __func__, __LINE__, ##args)
#endif

#ifndef my_trace
#define my_trace(fmt, args...)	printf("<T> [%s, %d] " fmt, __func__, __LINE__, ##args)
#endif

// ----------------------------------------------------------------------------
//  time (cpu clock cycles) log
// ----------------------------------------------------------------------------
void	tlog_set_en(unsigned char en);
void	tlog_clear(void);
void	tlog_record(char *name);
void	tlog_print(void);

#endif	// RT_LOG_H
