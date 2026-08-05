#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 0
#include "rt_log.h"
#include "rt_config_rlx.h"
#include "cmsis_voe.h"
#include "rlx_cpu.h"

int g_log_enable = 1;
int g_log_level = CFG_LOG_LEVEL;

// ----------------------------------------------------------------------------
//  time (cycle count) log
// ----------------------------------------------------------------------------
#if CFG_TLOG_EN

#define TLOG_NUM         256
#define TLOG_NAME_LEN    32

typedef struct
{
	int idx;
	unsigned int time[TLOG_NUM];
	char name[TLOG_NUM][TLOG_NAME_LEN];
} tlog_st;

static tlog_st tlog = {0};
static unsigned char tlog_en = 0;

void tlog_set_en(unsigned char en)
{
	if (en) {
		RLX_InitCycleCounter(); /* enable DWT hardware */
		RLX_ResetCycleCounter(); /* reset cycle counter */
		RLX_EnableCycleCounter(); /* start counting */
	} else {
		RLX_DisableCycleCounter(); /* disable counting if not used any more */
	}
	tlog_en = en;
}

void tlog_clear(void)
{
	memset(&tlog, 0, sizeof(tlog_st));
}

void tlog_record(char *name)
{
	if (!tlog_en)
		return;
	//if (tlog.idx >= TLOG_NUM-1) // to avoid overflow.
	//    return;
	//
	//asm volatile ("mfc0 %0, $9" : "=r" (tlog.time[tlog.idx]));
	tlog.time[tlog.idx] = RLX_GetCycleCounter();
	if (name != NULL)
		strncpy(tlog.name[tlog.idx], name, TLOG_NAME_LEN);
	//
	tlog.idx++;
	if (TLOG_NUM == tlog.idx) {
		tlog_print();
		tlog.idx = 0;
	}
}

void tlog_print(void)
{
	int diff, i;
	char str[128];

	if (!tlog_en)
		return;
	//
	if (tlog.idx == 0)
	{
		_rtl_printf("\n(time log empty)\n");
		return;
	}
	// else, non-empty
	printf("\nstart: %3.4f ms\n\n", cycle2ms(tlog.time[0]));
	for (i = 1; i < tlog.idx; i++)
	{
		diff = abs(tlog.time[i] - tlog.time[i-1]);
		if (tlog.name[i][0] != 0)
			sprintf(str, "%02d. %7.4f ms (%s)\n", i, cycle2ms(diff), tlog.name[i]);
		else
			sprintf(str, "%02d. %7.4f ms\n", i, cycle2ms(diff));
		printf("%s", str);
	}
	printf("\nend: %3.4f ms\n", cycle2ms(tlog.time[tlog.idx-1]));
}
#else
void    tlog_set_en(u8 en)      { return; }
void    tlog_clear(void)        { return; }
void    tlog_record(char *name) { return; }
void    tlog_print(void)        { return; }
#endif  // CFG_TLOG_EN
#endif
