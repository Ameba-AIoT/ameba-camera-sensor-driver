#ifndef _ISP_MOD_CONTROL_H_INC_
#define _ISP_MOD_CONTROL_H_INC_

#include <stdint.h>
#include <rts_camera_isp_info.h>
#include <isp_utils.h>

enum isp_mod_control_execute_type {
	CONTROL_EXEC_SET_FPS = RTS_ISP_SET_FPS,
	CONTROL_EXEC_STATIS_DONE = RTS_ISP_STATIS_DONE,
};

#endif /* _ISP_MOD_CONTROL_H_INC_ */
