#ifndef _ISP_MOD_VCTRL_H_INC_
#define _ISP_MOD_VCTRL_H_INC_

#include <isp_utils.h>
#include <linux/videodev2.h>

enum isp_mod_vctrl_execution_type {
	VCTRL_EXEC_QUERY_CTRL = isp_action_wr(EXEC_TYPE, 0,
					      struct v4l2_queryctrl),
	VCTRL_EXEC_QUERY_MENU = isp_action_wr(EXEC_TYPE, 1,
					      struct v4l2_querymenu),
	VCTRL_EXEC_G_CTRL = isp_action_wr(EXEC_TYPE, 2, struct v4l2_control),
	VCTRL_EXEC_S_CTRL = isp_action_wr(EXEC_TYPE, 3, struct v4l2_control),
	VCTRL_EXEC_QUERY_EXT_CTRL = isp_action_wr(EXEC_TYPE, 4,
						  struct v4l2_query_ext_ctrl),
	VCTRL_EXEC_G_EXT_CTRLS = isp_action_wr(EXEC_TYPE, 5,
					       struct v4l2_ext_controls),
	VCTRL_EXEC_S_EXT_CTRLS = isp_action_wr(EXEC_TYPE, 6,
					       struct v4l2_ext_controls),
	VCTRL_EXEC_TRY_EXT_CTRLS = isp_action_wr(EXEC_TYPE, 7,
						 struct v4l2_ext_controls),
};

#endif /* _ISP_MOD_VCTRL_H_INC_ */

