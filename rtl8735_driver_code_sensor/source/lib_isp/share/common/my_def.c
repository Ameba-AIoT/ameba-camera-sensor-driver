#include "rt_types.h"
#include "rt_log.h"
#include "my_def.h"
#include <stdio.h>

s64 RT_TYPE_CAST(RT_TYPE_E type, s64 val)
{
	switch (type)
	{
	case RT_TYPE_U8:  val = (u8) val;	break;
	case RT_TYPE_S8:  val = (s8) val;	break;
	case RT_TYPE_U16: val = (u16)val;	break;
	case RT_TYPE_S16: val = (s16)val;	break;
	case RT_TYPE_U32: val = (u32)val;	break;
	case RT_TYPE_S32: val = (s32)val;	break;
	default:
		RT_ASSERT(1);
		break;
	}
	return val;
}

// step:
// (1) convert buf[] to a s64 value
// (2) call RT_TYPE_CAST()
//
s64 RT_TYPE_CAST_BY_STR(RT_TYPE_E type, u8 *buf, u8 len)
{
	s64 val = 0;
	int n = MIN(len, RT_TYPE_SIZEOF(type));

	for (int i = n-1; i >= 0; i--)
		val = (val << 8) | buf[i];

	return RT_TYPE_CAST(type, val);
}

#if (CFG_TRACE_RT_MEM)
int g_print_rt_mem = 1;

void *__rt_malloc(size_t size, const char *caller, int line)
{
	void *ptr = malloc(size);
	if (g_print_rt_mem)
		printf("[D] %-12s : 0x%08X, %6d, %s#%d\n", "malloc", (u32)ptr, size, caller, line);
	return ptr;
}

void __rt_free(void *ptr, const char *caller, int line)
{
	free(ptr);
	if (g_print_rt_mem)
		printf("[D] %-12s : 0x%08X, %6s, %s#%d\n", "free", (u32)ptr, " ", caller, line);
}

void *__rt_memalign(size_t alignment, size_t size, const char *caller, int line)
{
	void *ptr = memalign(alignment, size);
	if (g_print_rt_mem)
		printf("[D] %-12s : 0x%08X, %6d, %6d, %s#%d\n", "memalign", (u32)ptr, alignment, size, caller, line);
	return ptr;
}
#endif	// TRACE_RT_MEM

