#ifndef __RT_TIME_H__
#define __RT_TIME_H__
#include "rt_drv.h"
#include "cmsis_os2.h"

#ifdef __cplusplus
extern "C" {
#endif

BOOL	time_is_connect_to_server(void);
long	time_get_uptime(void);
int		time_set_date_by_sec(long sec);
int		time_set_date(char *string);
long	time_get_date(void);
void	time_set_time_zone(int minutes);
long	time_get_time_zone(void);

// --------------------------------------------------------
//  time stat
// --------------------------------------------------------
#define TIME_STATS		1

#if TIME_STATS

#define TIME_STATS_NUM	64
#define TIME_START(x)	time_stats_start(#x)
#define TIME_STOP(x)	time_stats_stop(#x)

int time_stats_start(char *name);
int time_stats_stop(char *name);
int time_stats_show(void);

#else

#define TIME_START(x)
#define TIME_STOP(x)

#define time_stats_start(name)
#define time_stats_stop(name)
#define time_stats_show()

#endif	// TIME_STATS

// --------------------------------------------------------
//  tickcount, us/ms
// --------------------------------------------------------
// convertion between second & millisecond.
#define ms2s(t)		((t)/1000.0f)
#define s2ms(t)		((t)*1000)

void	udelay(unsigned long usec);
void	mdelay(unsigned long msec);

void	rt_busy_wait_us(unsigned long usec);
void	rt_busy_wait_ms(unsigned long msec);

#define rt_get_tickcount	osKernelGetTickCount

// Caution!!!
//  (1) since we use osKernelGetTickCount(), the precision is ms.
//  (2) in our real experiment, to keep precision.
//      it is better that time period >= 3 ms at least.
//
// return: time period in ms.
//
// example code:
// {
//     u64 t0 = rt_get_tickcount();
//     do_your_job();
//     u64 t1 = rt_get_tickcount();
//     printf("period: %lu (ms)\n", rt_get_period(t1-t0));
// }
//
u32		rt_get_period(u64 ticks);


#ifdef __cplusplus
}
#endif

#endif	// __RT_TIME_H__

