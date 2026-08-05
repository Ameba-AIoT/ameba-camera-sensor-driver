// ============================================================================
// brief: ALL .h/.c files under /rlx MUST include this file.
//
// rlx is close to h/w layer, for simplicity, follow the below
// rules:
//	- follow the rules in rlx_types.h
//	- CAN use rt_log (which follows same rules with rlx layer)
//	- NOT use rt_code
//		- let function defines it's own return value
//
// ============================================================================
#ifndef RLX_INC_H
#define RLX_INC_H
#include "rlx_types.h"
#include "rt_config_rlx.h"
#include "rt_log.h"


#endif	// RLX_INC_H
