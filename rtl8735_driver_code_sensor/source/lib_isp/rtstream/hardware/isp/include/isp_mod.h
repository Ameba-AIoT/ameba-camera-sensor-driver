#ifndef _ISP_MOD_H_INC_
#define _ISP_MOD_H_INC_

#include <stdint.h>
#include <isp_utils.h>
#include <isp_mem.h>
#include <isp_log.h>
#include <cmsis_os2.h>

#define MOD_CONTROL	isp_fourcc('c', 't', 'r', 'l')
#define MOD_IQ		isp_fourcc('i', 'q', 0, 0)
#define MOD_VCTRL	isp_fourcc('v', 'c', 't', 'l')
#define MOD_GLOBAL	isp_fourcc('g', 'l', 'o', 'b')
#define MOD_SENSOR	isp_fourcc('s', 'e', 's', 'r')
#define MOD_INTERFACE	isp_fourcc('c', 'i', 'n', 'f')
#define MOD_CROP	isp_fourcc('c', 'r', 'o', 'p')
#define MOD_BLC		isp_fourcc('b', 'l', 'c', 0)
#define MOD_DPC		isp_fourcc('d', 'p', 'c', 0)
#define MOD_RAWSTAT	isp_fourcc('r', 's', 't', 'a')
#define MOD_TNR		isp_fourcc('t', 'n', 'r', 0)
#define MOD_NLSC	isp_fourcc('n', 'l', 's', 'c')
#define MOD_MLSC	isp_fourcc('m', 'l', 's', 'c')
#define MOD_AWB		isp_fourcc('a', 'w', 'b', 0)
#define MOD_AE		isp_fourcc('a', 'e', 0, 0)
#define MOD_AF		isp_fourcc('a', 'f', 0, 0)
#define MOD_INTP	isp_fourcc('i', 'n', 't', 'p')
#define MOD_CCM		isp_fourcc('c', 'c', 'm', 0)
#define MOD_GAMMA	isp_fourcc('g', 'a', 'm', 'a')
#define MOD_DEHAZE	isp_fourcc('d', 'h', 'a', 'z')
#define MOD_WDR		isp_fourcc('w', 'd', 'r', 0)
#define MOD_RGB2YUV	isp_fourcc('r', '2', 'y', 0)
#define MOD_YGC		isp_fourcc('y', 'g', 'c', 0)
#define MOD_YSTAT	isp_fourcc('y', 's', 't', 'a')
#define MOD_UVTUNE	isp_fourcc('u', 'v', 't', 'u')
#define MOD_FLICK	isp_fourcc('f', 'l', 'i', 'c')
#define MOD_LDC		isp_fourcc('l', 'd', 'c', 0)
#define MOD_EEH		isp_fourcc('e', 'e', 'h', 0)
#define MOD_MCROP	isp_fourcc('m', 'c', 'r', 'p')
#define MOD_SPE		isp_fourcc('s', 'p', 'e', 0)
#define MOD_YGAMMA	isp_fourcc('y', 'g', 'm', 'a')
#define MOD_MASK	isp_fourcc('m', 'a', 's', 'k')
#define MOD_STATIS	isp_fourcc('s', 't', 'a', 't')
#define MOD_TM		isp_fourcc('t', 'm', 0, 0)
#define MOD_SNR		isp_fourcc('s', 'n', 'r', 0)
#define MOD_MD		isp_fourcc('m', 'd', 0, 0)
//#define MOD_MIPIOUT	isp_fourcc('m', 'p', 'o', 't')

enum isp_mod_status {
	UNINITIALIZED,
	INITIALIZED,
};

struct isp_mod;

typedef int (*isp_mod_action)(struct isp_mod *mod, void *data);

struct isp_mod_action_info {
	uint32_t id;
	isp_mod_action action;
};

#define ISP_MOD_ACTION(_id, _action) \
	[ISP_AID_NR(_id)] = { \
		.id = _id, \
		.action = _action, \
	}

#define ISP_NOTIFY_ACTION(_id, _action) \
	{ \
		.id = _id, \
		.action = _action, \
	}

#define get_mod(ptr, name) container_of(ptr, struct isp_mod_##name, mod)

struct isp_mod {
	uint32_t id;
	//const char name[16];
	const char *name;
	uint32_t owner_id;
	uint32_t notify_bits;

	/* do not directly use these callbacks, use api in this file */
	int (*init)(struct isp_mod *mod);
	int (*cleanup)(struct isp_mod *mod);
	int (*hardware_init)(struct isp_mod *mod);
	int (*hardware_cleanup)(struct isp_mod *mod);
	int (*add_ctrl)(struct isp_mod *mod, void *phandler);
	int (*need_block)(struct isp_mod *mod, uint32_t id, void *data);
	struct isp_mod_action_info *exec_actions;
	size_t exec_actions_num;
	struct isp_mod_action_info *info_actions;
	size_t info_actions_num;
	struct isp_mod_action_info *notify_actions;
	size_t notify_actions_num;
	int virtual;

	/* private, only used for internal */
	struct isp_mod *next;
	uint32_t real_notify_bits;
	void *owner;
	int initialized;
	int hardware_initialized;
	int ctrl_added;
};

int isp_mod_register(struct isp_mod *mod);
int isp_mod_unregister(struct isp_mod *mod);
int isp_mod_init(struct isp_mod *mod);
int isp_mod_cleanup(struct isp_mod *mod);
int isp_mod_hardware_init(struct isp_mod *mod);
int isp_mod_hardware_cleanup(struct isp_mod *mod);
int isp_mod_add_ctrl(struct isp_mod *mod, void *phandler);
int isp_mod_action_need_block(struct isp_mod *mod, uint32_t id,
			      void *data, size_t len);
int isp_mod_get_info(struct isp_mod *mod, uint32_t id, void *info, size_t len);
int isp_mod_execute(struct isp_mod *mod, uint32_t id, void *data, size_t len);
int isp_mod_notify(struct isp_mod *mod, uint32_t id, void *data, size_t len);
int isp_mod_do_action(struct isp_mod *mod, uint32_t id, void *data, size_t len);
int isp_mod_add_notify(struct isp_mod *mod, uint32_t notify_id);
int isp_mod_del_notify(struct isp_mod *mod, uint32_t notify_id);
int isp_mod_sibling_get_info(struct isp_mod *mod, int mod_id, int id,
			     void *data, size_t len);
int isp_mod_sibling_execute(struct isp_mod *mod, int mod_id, int id,
			    void *data, size_t len);
int isp_mod_sibling_notify(struct isp_mod *mod, int mod_id, int id,
			   void *data, size_t len);
struct isp_mod *isp_mod_get_sibling(struct isp_mod *mod, int mod_id);

/* helper functions */
int isp_mod_set_smooth_notify(struct isp_mod *mod, int add);

int isp_register_all_modules(void);
void isp_unregister_all_modules(void);

#endif /* _ISP_MOD_H_INC_ */
