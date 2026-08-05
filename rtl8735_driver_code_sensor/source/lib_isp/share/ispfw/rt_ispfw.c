#include "rt_types.h"
#include "rt_code.h"
#include "rt_log.h"
#include "my_def.h"
#include "rt_hconf.h"
#include "rt_ispfw.h"

#include "rt_mtd.h"

/* xxd -i ispfw.bin > ISPFW.h */
#define ISPFW_SC2235_DVP	0
#define ISPFW_AR0237_DVP	0
#define ISPFW_JXF22_DVP		1
#define ISPFW_JXF37_MIPI	0

#if ISPFW_SC2235_DVP
#include "ISPFW_SC2235_DVP.h"
#define ISPFW_name "ISPFW_SC2235_DVP"
#endif

#if ISPFW_AR0237_DVP
#include "ISPFW_AR0237_DVP.h"
#define ISPFW_name "ISPFW_AR0237_DVP"
#endif

#if ISPFW_JXF22_DVP
#include "ISPFW_JXF22_DVP.h"
#define ISPFW_name "ISPFW_JXF22_DVP"
#endif

#if ISPFW_JXF37_MIPI
#include "ISPFW_JXF37_MIPI.h"
#define ISPFW_name "ISPFW_JXF37_MIPI"
#endif

static ispfw_st		g_ispfw = {0};

// note: this function is called by main.c & the ONLY ONCE.
void ispfw_load_global(void)
{
	g_ispfw.addr		= (u32)ISPFW_bin;
	g_ispfw.size		= (u32)ISPFW_len;
	g_ispfw.from_sf		= FALSE;
	g_ispfw.name		= ISPFW_name;
	rt_printf("ispfw: %s\n", ISPFW_name);
	return;
}

// note: this func MUST always success.
void ispfw_get_global(ispfw_st *out)
{
	*out = g_ispfw;
}
