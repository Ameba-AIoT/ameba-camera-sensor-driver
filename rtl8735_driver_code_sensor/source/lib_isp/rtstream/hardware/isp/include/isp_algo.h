#ifndef _ISP_ALGO_H_INC_
#define _ISP_ALGO_H_INC_

#include <rtsavisp.h>
#include <rts_isp_awb.h>
#include <rts_isp_ae.h>
#include <rts_isp_af.h>
#include <rts_isp_md_algo.h>
#include <rts_isp_other.h>
#include <isp_list.h>
#include <isp_plugin.h>

#define ISP_MAX_ALGO_NUM 4

#define algo_magic(verion) ((version) >> 16)
#define algo_major_version(verion) (((version) & 0xff00) >> 8)
#define algo_minor_version(verion) (((version) & 0xff))

struct isp_algo_attr {
	enum rts_isp_algo_id id;
	struct isp_plugin plugin;
};

struct isp_algo_binding {
	int index[_RTS_ISP_ALGO_TYPE_NUM];
};

struct isp_algo_manager {
	struct isp_algo_attr *ae[ISP_MAX_ALGO_NUM];
	struct isp_algo_attr *awb[ISP_MAX_ALGO_NUM];
	struct isp_algo_attr *af[ISP_MAX_ALGO_NUM];
	struct isp_algo_attr *md[ISP_MAX_ALGO_NUM];
	struct isp_algo_attr *other[ISP_MAX_ALGO_NUM];
	struct isp_algo_binding binding[_ISP_ID_NUM];
};

enum isp_algo_change_bit {
	ISP_ALGO_AE_CHANGE_BIT = 1 << RTS_ISP_ALGO_AE,
	ISP_ALGO_AWB_CHANGE_BIT = 1 << RTS_ISP_ALGO_AWB,
	ISP_ALGO_AF_CHANGE_BIT = 1 << RTS_ISP_ALGO_AF,
	ISP_ALGO_MD_CHANGE_BIT = 1 << RTS_ISP_ALGO_MD,
	ISP_ALGO_OTHER_CHANGE_BIT = 1 << RTS_ISP_ALGO_OTHER,
};

int isp_algo_init(struct isp_algo_manager *algom);
int isp_algo_cleanup(struct isp_algo_manager *algom);
int isp_algo_register(struct isp_algo_manager *algom,
		      const struct rts_isp_algo *algo);
int isp_algo_unregister(struct isp_algo_manager *algom,
			enum rts_isp_algo_id id);
int isp_algo_get(struct isp_algo_manager *algom, struct rts_isp_algo *algo);
int isp_algo_bind(struct isp_algo_manager *algom, uint32_t isp_id,
		  enum rts_isp_algo_id id);
int isp_algo_unbind(struct isp_algo_manager *algom, uint32_t isp_id,
		    enum rts_isp_algo_id id);
int isp_algo_check_all_bound(struct isp_algo_manager *algom);

int isp_algo_get_ae(struct isp_algo_manager *algom, uint32_t isp_id,
		     const struct rts_isp_ae_algo **ae_algo);
int isp_algo_get_awb(struct isp_algo_manager *algom, uint32_t isp_id,
		     const struct rts_isp_awb_algo **awb_algo);
int isp_algo_get_af(struct isp_algo_manager *algom, uint32_t isp_id,
		    const struct rts_isp_af_algo **af_algo);
int isp_algo_get_flick(struct isp_algo_manager *algom, uint32_t isp_id,
		       const struct rts_isp_flick_algo **flick_algo);
int isp_algo_get_wdr(struct isp_algo_manager *algom, uint32_t isp_id,
		     const struct rts_isp_wdr_algo **wdr_algo);
int isp_algo_get_md(struct isp_algo_manager *algom, uint32_t isp_id,
		     const struct rts_isp_md_algo **md_algo);

#endif /* _ISP_ALGO_H_INC_ */
