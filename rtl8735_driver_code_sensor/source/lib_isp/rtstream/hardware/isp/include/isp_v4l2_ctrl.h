#ifndef _ISP_V4L2_CTRL_H_INC_
#define _ISP_V4L2_CTRL_H_INC_

/*
 * Ported from linux driver
 */

#include <stdint.h>
#include <isp_list.h>
#include <linux/videodev2.h>

struct v4l2_ctrl;

union v4l2_ctrl_ptr {
	int32_t *p_s32;
	int64_t *p_s64;
	uint8_t *p_u8;
	uint16_t *p_u16;
	uint32_t *p_u32;
	char *p_char;
	void *p;
};

/**
 * struct v4l2_ctrl_ops - The control operations that the driver has to provide.
 *
 * @g_volatile_ctrl: Get a new value for this control. Generally only relevant
 *		for volatile (and usually read-only) controls such as a control
 *		that returns the current signal strength which changes
 *		continuously.
 *		If not set, then the currently cached value will be returned.
 * @try_ctrl:	Test whether the control's value is valid. Only relevant when
 *		the usual min/max/step checks are not sufficient.
 * @s_ctrl:	Actually set the new control value. s_ctrl is compulsory. The
 *		ctrl->handler->lock is held when these ops are called, so no
 *		one else can access controls owned by that handler.
 */
struct v4l2_ctrl_ops {
	int (*g_volatile_ctrl)(struct v4l2_ctrl *ctrl);
	int (*try_ctrl)(struct v4l2_ctrl *ctrl);
	int (*s_ctrl)(struct v4l2_ctrl *ctrl);
};

struct v4l2_ctrl_type_ops {
	int (*equal)(const struct v4l2_ctrl *ctrl, uint32_t idx,
		     union v4l2_ctrl_ptr ptr1,
		     union v4l2_ctrl_ptr ptr2);
	void (*init)(const struct v4l2_ctrl *ctrl, uint32_t idx,
		     union v4l2_ctrl_ptr ptr);
	void (*log)(const struct v4l2_ctrl *ctrl);
	int (*validate)(const struct v4l2_ctrl *ctrl, uint32_t idx,
			union v4l2_ctrl_ptr ptr);
};

/**
 * struct v4l2_ctrl - The control structure.
 *
 * @list:	The list node.
 * @handler:	The handler that owns the control.
 * @cluster:	Point to start of cluster array.
 * @ncontrols:	Number of controls in cluster array.
 * @modified:	Internal flag: set means ctrl has set by user.
 * @done:	Internal flag: set for each processed control.
 * @is_new:	Set when the user specified a new value for this control. It
 *		is also set when called from v4l2_ctrl_handler_setup(). Drivers
 *		should never set this flag.
 * @has_changed: Set when the current value differs from the new value. Drivers
 *		should never use this flag.
 * @is_auto:   If set, then this control selects whether the other cluster
 *		members are in 'automatic' mode or 'manual' mode. This is
 *		used for autogain/gain type clusters. Drivers should never
 *		set this flag directly.
 * @is_int:    If set, then this control has a simple integer value (i.e. it
 *		uses ctrl->val).
 * @is_string: If set, then this control has type %V4L2_CTRL_TYPE_STRING.
 * @is_ptr:	If set, then this control is an array and/or has type >=
 *		%V4L2_CTRL_COMPOUND_TYPES
 *		and/or has type %V4L2_CTRL_TYPE_STRING. In other words, &struct
 *		v4l2_ext_control uses field p to point to the data.
 * @is_array: If set, then this control contains an N-dimensional array.
 * @has_volatiles: If set, then one or more members of the cluster are volatile.
 *		Drivers should never touch this flag.
 * @call_notify: If set, then call the handler's notify function whenever the
 *		control's value changes.
 * @manual_mode_value: If the is_auto flag is set, then this is the value
 *		of the auto control that determines if that control is in
 *		manual mode. So if the value of the auto control equals this
 *		value, then the whole cluster is in manual mode. Drivers should
 *		never set this flag directly.
 * @ops:	The control ops.
 * @type_ops:	The control type ops.
 * @id:	The control ID.
 * @name:	The control name.
 * @type:	The control type.
 * @minimum:	The control's minimum value.
 * @maximum:	The control's maximum value.
 * @default_value: The control's default value.
 * @step:	The control's step value for non-menu controls.
 * @elems:	The number of elements in the N-dimensional array.
 * @elem_size:	The size in bytes of the control.
 * @dims:	The size of each dimension.
 * @nr_of_dims:The number of dimensions in @dims.
 * @menu_skip_mask: The control's skip mask for menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works for
 *		menus with <= 32 menu items. There are no menus that come
 *		close to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a uint64_t or a bit array.
 * @qmenu:	A const char * array for all menu items. Array entries that are
 *		empty strings ("") correspond to non-existing menu items (this
 *		is in addition to the menu_skip_mask above). The last entry
 *		must be NULL.
 *		Used only if the @type is %V4L2_CTRL_TYPE_MENU.
 * @qmenu_int:	A 64-bit integer array for with integer menu items.
 *		The size of array must be equal to the menu size, e. g.:
 *		:math:`ceil(\frac{maximum - minimum}{step}) + 1`.
 *		Used only if the @type is %V4L2_CTRL_TYPE_INTEGER_MENU.
 * @flags:	The control's flags.
 * @cur:	Structure to store the current value.
 * @cur.val:	The control's current value, if the @type is represented via
 *		a uint32_t integer (see &enum v4l2_ctrl_type).
 * @val:	The control's new int32_t value.
 * @priv:	The control's private pointer. For use by the driver. It is
 *		untouched by the control framework. Note that this pointer is
 *		not freed when the control is deleted. Should this be needed
 *		then a new internal bitfield can be added to tell the framework
 *		to free this pointer.
 * @p_cur:	The control's current value represented via a union with
 *		provides a standard way of accessing control types
 *		through a pointer.
 * @p_new:	The control's new value represented via a union with provides
 *		a standard way of accessing control types
 *		through a pointer.
 */
struct v4l2_ctrl {
	/* Administrative fields */
	struct isp_list list;
	struct v4l2_ctrl_handler *handler;
	struct v4l2_ctrl **cluster;
	unsigned int ncontrols;

	unsigned int modified:1;

	unsigned int done:1;

	unsigned int is_new:1;
	unsigned int has_changed:1;
	unsigned int is_auto:1;
	unsigned int is_int:1;
	unsigned int is_string:1;
	unsigned int is_ptr:1;
	unsigned int is_array:1;
	unsigned int has_volatiles:1;
	unsigned int call_notify:1;
	unsigned int manual_mode_value:8;

	const struct v4l2_ctrl_ops *ops;
	const struct v4l2_ctrl_type_ops *type_ops;
	uint32_t id;
	const char *name;
	enum v4l2_ctrl_type type;
	int64_t minimum, maximum, default_value;
	uint32_t elems;
	uint32_t elem_size;
	uint32_t dims[V4L2_CTRL_MAX_DIMS];
	uint32_t nr_of_dims;
	union {
		uint64_t step;
		uint64_t menu_skip_mask;
	};
	union {
		const char * const *qmenu;
		const int64_t *qmenu_int;
	};
	unsigned long flags;
	void *priv;
	int32_t val;
	struct {
		int32_t val;
	} cur;

	union v4l2_ctrl_ptr p_new;
	union v4l2_ctrl_ptr p_cur;
};

/**
 * struct v4l2_ctrl_ref - The control reference.
 *
 * @list:	List node for the sorted list.
 * @next:	Single-link list node for the hash.
 * @ctrl:	The actual control information.
 * @helper:	Pointer to helper struct. Used internally in
 *		``prepare_ext_ctrls`` function at ``v4l2-ctrl.c``.
 *
 * Each control handler has a list of these refs. The list_head is used to
 * keep a sorted-by-control-ID list of all controls, while the next pointer
 * is used to link the control in the hash's bucket.
 */
struct v4l2_ctrl_ref {
	struct isp_list list;
	struct v4l2_ctrl_ref *next;
	struct v4l2_ctrl *ctrl;
	struct v4l2_ctrl_helper *helper;
};

/**
 * struct v4l2_ctrl_handler - The control handler keeps track of all the
 *	controls: both the controls owned by the handler and those inherited
 *	from other handlers.
 *
 * @_lock:	Default for "lock".
 * @lock:	Lock to control access to this handler and its controls.
 *		May be replaced by the user right after init.
 * @ctrls:	The list of controls owned by this handler.
 * @ctrl_refs:	The list of control references.
 * @cached:	The last found control reference. It is common that the same
 *		control is needed multiple times, so this is a simple
 *		optimization.
 * @buckets:	Buckets for the hashing. Allows for quick control lookup.
 * @notify:	A notify callback that is called whenever the control changes
 *		value.
 *		Note that the handler's lock is held when the notify function
 *		is called!
 * @notify_priv: Passed as argument to the v4l2_ctrl notify callback.
 * @nr_of_buckets: Total number of buckets in the array.
 * @error:	The error code of the first failed control addition.
 * @setting:	set to 1 means user is setting ctrl.
 */
struct v4l2_ctrl_handler {
	struct isp_list ctrls;
	struct isp_list ctrl_refs;
	struct v4l2_ctrl_ref *cached;
	struct v4l2_ctrl_ref **buckets;
	uint16_t nr_of_buckets;
	int error;
	int setting;
};

/**
 * struct v4l2_ctrl_config - Control configuration structure.
 *
 * @ops:	The control ops.
 * @type_ops:	The control type ops. Only needed for compound controls.
 * @id:	The control ID.
 * @name:	The control name.
 * @type:	The control type.
 * @min:	The control's minimum value.
 * @max:	The control's maximum value.
 * @step:	The control's step value for non-menu controls.
 * @def:	The control's default value.
 * @dims:	The size of each dimension.
 * @elem_size:	The size in bytes of the control.
 * @flags:	The control's flags.
 * @menu_skip_mask: The control's skip mask for menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works for
 *		menus with <= 64 menu items. There are no menus that come
 *		close to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a bit array.
 * @qmenu:	A const char * array for all menu items. Array entries that are
 *		empty strings ("") correspond to non-existing menu items (this
 *		is in addition to the menu_skip_mask above). The last entry
 *		must be NULL.
 * @qmenu_int:	A const int64_t integer array for all menu items of the type
 *		V4L2_CTRL_TYPE_INTEGER_MENU.
 * @is_private: If set, then this control is private to its handler and it
 *		will not be added to any other handlers.
 */
struct v4l2_ctrl_config {
	const struct v4l2_ctrl_ops *ops;
	const struct v4l2_ctrl_type_ops *type_ops;
	uint32_t id;
	const char *name;
	enum v4l2_ctrl_type type;
	int64_t min;
	int64_t max;
	uint64_t step;
	int64_t def;
	uint32_t dims[V4L2_CTRL_MAX_DIMS];
	uint32_t elem_size;
	uint32_t flags;
	uint64_t menu_skip_mask;
	const char * const *qmenu;
	const int64_t *qmenu_int;
};

int rtsv_ctrl_handler_init(struct v4l2_ctrl_handler *hdl, unsigned int nr_hint);
void rtsv_ctrl_handler_free(struct v4l2_ctrl_handler *hdl);
void rtsv_ctrl_handler_log_status(struct v4l2_ctrl_handler *hdl,
				  const char *prefix);
int rtsv_ctrl_handler_setup(struct v4l2_ctrl_handler *hdl);
void rtsv_ctrl_handler_backup_auto(struct v4l2_ctrl_handler *hdl);
struct v4l2_ctrl *rtsv_ctrl_find(struct v4l2_ctrl_handler *hdl, uint32_t id);

struct v4l2_ctrl *rtsv_ctrl_new_custom(struct v4l2_ctrl_handler *hdl,
				       const struct v4l2_ctrl_config *cfg,
				       void *priv);
struct v4l2_ctrl *rtsv_ctrl_new_std(struct v4l2_ctrl_handler *hdl,
				    const struct v4l2_ctrl_ops *ops,
				    uint32_t id, int64_t min, int64_t max,
				    uint64_t step, int64_t def, void *priv);
struct v4l2_ctrl *rtsv_ctrl_new_std_menu(struct v4l2_ctrl_handler *hdl,
					 const struct v4l2_ctrl_ops *ops,
					 uint32_t id, uint8_t max,
					 uint64_t mask, uint8_t def,
					 void *priv);
struct v4l2_ctrl *rtsv_ctrl_new_std_menu_items(struct v4l2_ctrl_handler *hdl,
					       const struct v4l2_ctrl_ops *ops,
					       uint32_t id, uint8_t max,
					       uint64_t mask, uint8_t def,
					       const char * const *qmenu,
					       void *priv);
struct v4l2_ctrl *rtsv_ctrl_new_int_menu(struct v4l2_ctrl_handler *hdl,
					 const struct v4l2_ctrl_ops *ops,
					 uint32_t id, uint8_t max, uint8_t def,
					 const int64_t *qmenu_int, void *priv);

void rtsv_ctrl_cluster(unsigned int ncontrols, struct v4l2_ctrl **controls);
void rtsv_ctrl_auto_cluster(unsigned int ncontrols, struct v4l2_ctrl **controls,
			    uint8_t manual_val, int set_volatile);

void rtsv_ctrl_activate(struct v4l2_ctrl *ctrl, int active);
void rtsv_ctrl_grab(struct v4l2_ctrl *ctrl, int grabbed);

int rtsv_queryctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_queryctrl *qc);
int rtsv_querymenu(struct v4l2_ctrl_handler *hdl, struct v4l2_querymenu *qm);
int rtsv_g_ctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_control *control);
int rtsv_s_ctrl(struct v4l2_ctrl_handler *hdl, struct v4l2_control *control);

int rtsv_query_ext_ctrl(struct v4l2_ctrl_handler *hdl,
			struct v4l2_query_ext_ctrl *qc);
int rtsv_g_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		     struct v4l2_ext_controls *cs);
int rtsv_try_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		       struct v4l2_ext_controls *cs);
int rtsv_s_ext_ctrls(struct v4l2_ctrl_handler *hdl,
		     struct v4l2_ext_controls *cs);

int32_t rtsv_ctrl_g_ctrl(struct v4l2_ctrl *ctrl);
int64_t rtsv_ctrl_g_ctrl_int64(struct v4l2_ctrl *ctrl);
int rtsv_ctrl_s_ctrl(struct v4l2_ctrl *ctrl, int32_t val);
int rtsv_ctrl_s_ctrl_int64(struct v4l2_ctrl *ctrl, int64_t val);
int rtsv_ctrl_s_ctrl_string(struct v4l2_ctrl *ctrl, const char *s);
int rtsv_ctrl_modify_range(struct v4l2_ctrl *ctrl, int64_t min, int64_t max,
			   uint64_t step, int64_t def);

#endif /* _ISP_V4L2_CTRL_H_INC_ */

