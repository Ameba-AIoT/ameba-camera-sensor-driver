#ifndef RESET_RTSMEM3915_H
#define RESET_RTSMEM3915_H

#include "rts-sysmem.h"

int rts_sysmem_assert(unsigned long id);
int rts_sysmem_deassert(unsigned long id);

int rts_sysmem_probe(void);

#endif