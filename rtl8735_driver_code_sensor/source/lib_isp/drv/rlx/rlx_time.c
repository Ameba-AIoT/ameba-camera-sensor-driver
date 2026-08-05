/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#if 0

#include <common.h>
#include <watchdog.h>
#include <div64.h>
#include <asm/io.h>

#if CONFIG_SYS_HZ != 1000
#warning "CONFIG_SYS_HZ must be 1000 and should not be defined by platforms"
#endif

#ifndef CONFIG_WD_PERIOD
# define CONFIG_WD_PERIOD	(10 * 1000 * 1000)	/* 10 seconds default*/
#endif

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SYS_TIMER_RATE
ulong notrace get_tbclk(void)
{
	return CONFIG_SYS_TIMER_RATE;
}
#endif

#ifdef CONFIG_SYS_TIMER_COUNTER
unsigned long notrace timer_read_counter(void)
{
#ifdef CONFIG_SYS_TIMER_COUNTS_DOWN
	return ~readl(CONFIG_SYS_TIMER_COUNTER);
#else
	return readl(CONFIG_SYS_TIMER_COUNTER);
#endif
}
#else
extern unsigned long timer_read_counter(void);
#endif

unsigned long long __weak notrace get_ticks(void)
{
	unsigned long now = timer_read_counter();

	/* increment tbu if tbl has rolled over */
	if (now < gd->timebase_l)
		gd->timebase_h++;
	gd->timebase_l = now;
	return ((unsigned long long)gd->timebase_h << 32) | gd->timebase_l;
}

static unsigned long long notrace tick_to_time(uint64_t tick)
{
	unsigned int div = get_tbclk();

	tick *= CONFIG_SYS_HZ;
	do_div(tick, div);
	return tick;
}

ulong __weak get_timer(ulong base)
{
	return tick_to_time(get_ticks()) - base;
}

unsigned long __weak notrace timer_get_us(void)
{
	return tick_to_time(get_ticks() * 1000);
}
static unsigned long long usec_to_tick(unsigned long usec)
{
	uint64_t tick = usec;
	tick *= get_tbclk();
	do_div(tick, 1000000);
	return tick;
}

void __weak __udelay(unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = usec_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		;
}

/* ------------------------------------------------------------------------- */

void udelay(unsigned long usec)
{
	ulong kv;

	do {
		WATCHDOG_RESET();
		kv = usec > CONFIG_WD_PERIOD ? CONFIG_WD_PERIOD : usec;
		__udelay(kv);
		usec -= kv;
	} while (usec);
}

void mdelay(unsigned long msec)
{
	while (msec--)
		udelay(1000);
}



// ----------------------------------------------------------------------------
// Frank, below is our temporaty implementation. the above is u-boot version.
// ----------------------------------------------------------------------------
#include "rlx_inc.h"
#include "sheipa.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"

// ----------------------------------------------------------------------------
// code ref from arch/rlx/cpu/taroko/time.c
// ----------------------------------------------------------------------------
//#define TAROKO_TIMER
#ifdef TAROKO_TIMER

static unsigned long timestamp = 0;

/* how many counter cycles in a jiffy */
#define CYCLES_PER_JIFFY	\
	((CONFIG_SYS_MIPS_TIMER_FREQ + CONFIG_SYS_HZ / 2) / CONFIG_SYS_HZ)

/*
 * timer without interrupts
 */
int timer_init(void)
{
	/* Set up the timer for the first expiration. */
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);

	return 0;
}

// Frank:
unsigned long get_timer(unsigned long base)
{
	unsigned int count;
	unsigned int expirelo = read_c0_compare();

	/* Check to see if we have missed any timestamps. */
	count = read_c0_count();
	while ((count - expirelo) < 0x7fffffff) {
		expirelo += CYCLES_PER_JIFFY;
		timestamp++;
	}
	write_c0_compare(expirelo);

	return timestamp - base;
}

#else

unsigned long get_timer(unsigned long base)
{
	return ((read_c0_count()/CPU_MS_TICKS) - base);
}

#endif	//!TAROKO_TIMER
#endif
