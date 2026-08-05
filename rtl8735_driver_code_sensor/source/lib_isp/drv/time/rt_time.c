
#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#include "hal_timer.h"

#if 0
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rt_time.h"
#include "rt_task.h"

#include "sheipa.h"
#include "FreeRTOS.h"
#include "task.h"

// -----------------------------------
// base_sec : system bootup time
// tick_sec : system has been running
// unix_sec : current time
//
// base_sec + tick_sec = unix_sec
//
// 1970/01/01 00:00:00  -->  0
// 2038/01/19 03:14:07  -->  2147483647 (0x7FFFFFFF)
// 1901/12/13 20:45:52  -->  2147483648 (0x80000000)
// 1969/12/31 23:59:59  -->  4294967295 (0xFFFFFFFF)
// -----------------------------------

static long gbl_base_sec = 0;
static long gblTimeZone = 0*60;

BOOL time_is_connect_to_server(void)
{
	BOOL ret = (gbl_base_sec ? TRUE : FALSE);

	return ret;
}

long time_get_uptime(void)
{
	long tick_sec;

	tick_sec = (xTaskGetTickCount() / portTICK_PERIOD_MS / 1000);

	return tick_sec;
}

int time_set_date_by_sec(long sec)
{
	long unix_sec;
	long tick_sec;

	unix_sec = sec;
	tick_sec = time_get_uptime();
	gbl_base_sec = unix_sec - tick_sec;

	//rt_printf("base %ld + tick %lu = unix %lu\n", gbl_base_sec, tick_sec, unix_sec);

	return RT_OK;
}

int time_set_date(char *string)
{
	struct tm cal = {0};
	long unix_sec;

	if (strptime(string, "%Y/%m/%d/%H:%M:%S", &cal))
	{
		unix_sec = mktime(&cal);
		time_set_date_by_sec(unix_sec);
	}
	else
	{
		return RT_FAIL;
	}

	return RT_OK;
}

long time_get_date(void)
{
	long unix_sec;
	long tick_sec;

	tick_sec = time_get_uptime();
	unix_sec = tick_sec + gbl_base_sec + gblTimeZone*60;

	//rt_printf("base %ld + tick %lu = unix %lu\n", gbl_base_sec, tick_sec, unix_sec);

	return unix_sec;
}

void time_set_time_zone(int minutes)
{
	gblTimeZone = minutes;
}

long time_get_time_zone(void)
{
	return gblTimeZone;
}

#if TIME_STATS

struct time_stats
{
	char name[16];
	uint start;
	uint stop;
};

static struct time_stats s_time_stats[TIME_STATS_NUM] = {0};

int time_stats_start(char *name)
{
	int i, idx = -1;

	for (i = 0; i < TIME_STATS_NUM; i++)
	{
		/* find the 1st empty entry */
		if (s_time_stats[i].name[0] == 0)
		{
			idx = i;
			break;
		}
		/* find the 1st matched entry */
		if (strcmp(s_time_stats[i].name, name) == 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		rt_printf("%s: table full\n", __func__);
		return RT_FAIL;
	}

	/* record timestamp */
	strncpy(s_time_stats[idx].name, name, 15);
	s_time_stats[idx].start = rt_get_tickcount();

	return RT_OK;
}

int time_stats_stop(char *name)
{
	int i, idx = -1;

	for (i = 0; i < TIME_STATS_NUM; i++)
	{
		/* find the 1st matched entry */
		if (strcmp(s_time_stats[i].name, name) == 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		rt_printf("%s: entry %s not found\n", __func__, name);
		return RT_FAIL;
	}

	/* record timestamp */
	s_time_stats[idx].stop = rt_get_tickcount();

	return RT_OK;
}

int time_stats_show(void)
{
	struct time_stats *stats = NULL;

	rt_printf("%-16s %8s %8s %8s\n", "name", "start", "stop", "diff");
	rt_printf("--------------------------------------------\n");

	for (int i = 0; i < TIME_STATS_NUM; i++)
	{
		stats = &s_time_stats[i];

		if (s_time_stats[i].name[0] != 0)
		{
			rt_printf("%-16s ", stats->name);
			rt_printf("%8d ", stats->start);
			rt_printf("%8d ", stats->stop);
			rt_printf("%8d ", stats->stop - stats->start);
			rt_printf("\n");
		}
	}

	return RT_OK;
}

#endif	// TIME_STATS
#endif
// --------------------------------------------------------
//  tickcount, us/ms
// --------------------------------------------------------
void rt_busy_wait_us(unsigned long usec)
{
	//uint64_t start_time, timeout_time, current_time;

#if 0
	start_time = ((uint64_t)read_c0_count())&0x0FFFFFFFFL;
	timeout_time = (uint64_t)(usec * (CONFIG_SYS_MIPS_TIMER_FREQ / 1000000));
	timeout_time += start_time;

	do {
		current_time = ((uint64_t)read_c0_count())&0x0FFFFFFFFL;
		if (current_time < start_time)  //tick count overflow
			current_time += 0x100000000L;
	} while (timeout_time > current_time);
#endif

	hal_delay_us(usec);
}

// note: can't directly call rt_busy_wait_us(t*1000), because "~8s overflow" restriction.
void rt_busy_wait_ms(unsigned long msec)
{
#if 0
	while (msec-- > 0)
	{
		rt_busy_wait_us(1000);
	}
#endif

	hal_delay_us(msec*1000);
		
}

void mdelay(unsigned long msec)
{
	vTaskDelay(pdMS_TO_TICKS(msec));
}

// since cpu register is 32bit, the original udelay() implementation
// has "about ~8s overflow" problem,
//
// the below new implementation can get rid of this kind of problem.
//
void udelay(unsigned long usec)
{

	if (usec / 1000)
		mdelay(usec / 1000);

	if (usec % 1000)
		rt_busy_wait_us(usec % 1000);

}

u32 rt_get_period(u64 ticks)
{
	return (u32)ticks;
}
