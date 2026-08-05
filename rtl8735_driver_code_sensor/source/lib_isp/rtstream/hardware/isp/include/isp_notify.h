#ifndef _ISP_NOTIFY_H_INC_
#define _ISP_NOTIFY_H_INC_

#include <stdint.h>
#include <rts_isp_patch.h>
#include <isp_avl.h>
#include <isp_mod.h>
#include <isp_statis.h>

enum isp_notify_num {
	_ISP_STATIS_DONE,
	_ISP_START_PRE,
	_ISP_START_POST,
	_ISP_STOP_PRE,
	_ISP_STOP_POST,
	_ISP_FPS_CHANGE,
	_ISP_IQ_CHANGE,
	_ISP_DYNAMIC,
	_ISP_DYNAMIC_POST,
	_ISP_ALGO_UPDATE,
	_ISP_HDR_MODE_CHANGE,
	_ISP_MCROP_CHANGE,
	_ISP_CROP_CHANGE,
	_ISP_NOTIFY_NUM,
};

enum isp_notify_ids {
	ISP_NOTIFY_STATIS_DONE = isp_action_w(NOTIFY_TYPE, _ISP_STATIS_DONE,
					      struct rts_isp_statis),
	ISP_NOTIFY_START_PRE = isp_action(NOTIFY_TYPE, _ISP_START_PRE),
	ISP_NOTIFY_START_POST = isp_action(NOTIFY_TYPE, _ISP_START_POST),
	ISP_NOTIFY_STOP_PRE = isp_action(NOTIFY_TYPE, _ISP_STOP_PRE),
	ISP_NOTIFY_STOP_POST = isp_action(NOTIFY_TYPE, _ISP_STOP_POST),
	ISP_NOTIFY_FPS_CHANGE = isp_action_w(NOTIFY_TYPE, _ISP_FPS_CHANGE,
					     float),
	ISP_NOTIFY_IQ_CHANGE = isp_action_w(NOTIFY_TYPE, _ISP_IQ_CHANGE,
					    uint32_t),
	ISP_NOTIFY_DYNAMIC_POST = isp_action(NOTIFY_TYPE, _ISP_DYNAMIC_POST),
	ISP_NOTIFY_DYNAMIC = isp_action_w(NOTIFY_TYPE, _ISP_DYNAMIC,
					  struct isp_notify_dynamic),
	ISP_NOTIFY_ALGO_UPDATE = isp_action_w(NOTIFY_TYPE, _ISP_ALGO_UPDATE,
					      uint32_t),
	ISP_NOTIFY_HDR_MODE_CHANGE = isp_action(NOTIFY_TYPE, _ISP_HDR_MODE_CHANGE),
	ISP_NOTIFY_MCROP_CHANGE = isp_action_w(NOTIFY_TYPE, _ISP_MCROP_CHANGE,
						      rts_isp_rect_t),
	ISP_NOTIFY_CROP_CHANGE = isp_action_w(NOTIFY_TYPE, _ISP_CROP_CHANGE,
						     rts_isp_point_t),
};

enum isp_notify_bit {
	ISP_STATIS_DONE_BIT = 1 << _ISP_STATIS_DONE,
	ISP_START_PRE_BIT = 1 << _ISP_START_PRE,
	ISP_START_POST_BIT = 1 << _ISP_START_POST,
	ISP_STOP_PRE_BIT = 1 << _ISP_STOP_PRE,
	ISP_STOP_POST_BIT = 1 << _ISP_STOP_POST,
	ISP_FPS_CHANGE_BIT = 1 << _ISP_FPS_CHANGE,
	ISP_IQ_CHANGE_BIT = 1 << _ISP_IQ_CHANGE,
	ISP_DYNAMIC_BIT = 1 << _ISP_DYNAMIC,
	ISP_DYNAMIC_POST_BIT = 1 << _ISP_DYNAMIC_POST,
	ISP_ALGO_UPDATE_BIT = 1 << _ISP_ALGO_UPDATE,
	ISP_HDR_MODE_CHANGE_BIT = 1 << _ISP_HDR_MODE_CHANGE,
	ISP_MCROP_CHANGE_BIT = 1 << _ISP_MCROP_CHANGE,
	ISP_CROP_CHANGE_BIT = 1 << _ISP_CROP_CHANGE,
};

struct isp_notify {
	int notify_num;
	struct avl_tree *mods;
};

int isp_notify_init(struct isp_notify *notify);
int isp_notify_cleanup(struct isp_notify *notify);
int isp_notify_add_mod(struct isp_notify *notify, struct isp_mod *mod);
int isp_notify_del_mod(struct isp_notify *notify, struct isp_mod *mod);
int isp_notify_add_entry(struct isp_notify *notify, struct isp_mod *mod,
			 enum isp_notify_ids id);
int isp_notify_del_entry(struct isp_notify *notify, struct isp_mod *mod,
			 enum isp_notify_ids id);
int isp_notify(struct isp_notify *notify, enum isp_notify_ids id,
	       void *data, ssize_t len);

#endif /* _ISP_NOTIFY_H_INC_ */
