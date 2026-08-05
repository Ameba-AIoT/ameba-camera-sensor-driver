#ifndef _ISP_CORE_H_INC_
#define _ISP_CORE_H_INC_

#include <unistd.h>
#include <rtsavisp.h>

struct isp_mod;
typedef struct isp_core *isp_core_t;

int isp_core_create(isp_core_t *pcore);
int isp_core_release(isp_core_t *pcore);
int isp_core_register_mod(isp_core_t core, struct isp_mod *mod);
int isp_core_unregister_mod(isp_core_t core, struct isp_mod *mod);
int isp_core_get_mod(isp_core_t core, uint32_t id, struct isp_mod **pmod);
int isp_core_init(isp_core_t core);
int isp_core_cleanup(isp_core_t core);
int isp_core_start(isp_core_t core);
int isp_core_stop(isp_core_t core);
int isp_core_add_notify_entry(isp_core_t core, struct isp_mod *mod,
			      uint32_t notify_id);
int isp_core_del_notify_entry(isp_core_t core, struct isp_mod *mod,
			      uint32_t notify_id);
int isp_core_notify(isp_core_t core, uint32_t id, void *data, ssize_t len);
struct isp_statis *isp_core_get_statis(isp_core_t core);
struct isp_iq *isp_core_get_iq(isp_core_t core);
int isp_core_set_iq_mode(isp_core_t core, int iq_dn_mode);

#endif /* _ISP_CORE_H_INC_ */
