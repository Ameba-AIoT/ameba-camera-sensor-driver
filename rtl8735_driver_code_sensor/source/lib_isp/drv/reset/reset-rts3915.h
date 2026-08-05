#ifndef RESET_RTS3915_H
#define RESET_RTS3915_H

#include "rts-resets.h"

int rts_sys_force_reset(unsigned long id);
int rts_sys_reset_assert(unsigned long id);
int rts_sys_reset_deassert(unsigned long id);

int rts_reset_probe(void);
int rts_reset_remove(void);

#endif