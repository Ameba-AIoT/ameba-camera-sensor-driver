#ifndef __ISPFW_H__
#define __ISPFW_H__
#include "rt_types.h"

typedef struct
{
	u32		addr;
	u32		size;
	BOOL	from_sf;
	char	*name;
} ispfw_st;

// brief:
//  (1) save global ispfw info.
//  (2) copy ispfw.bin from sf or use hard-coded ispfw.
//
void ispfw_load_global(void);

// note: this func MUST always success.
void ispfw_get_global(ispfw_st *out);

#endif
