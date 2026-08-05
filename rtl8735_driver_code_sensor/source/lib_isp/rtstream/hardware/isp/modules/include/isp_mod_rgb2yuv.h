#ifndef _ISP_MOD_RGB2YUV_H_INC_
#define _ISP_MOD_RGB2YUV_H_INC_

#include <isp_utils.h>

enum isp_mod_rgb2yuv_exec_type {
	RGB2YUV_EXEC_CONVERT = isp_action_wr(EXEC_TYPE, 0, uint32_t),
};

#endif /* _ISP_MOD_RGB2YUV_H_INC_ */

