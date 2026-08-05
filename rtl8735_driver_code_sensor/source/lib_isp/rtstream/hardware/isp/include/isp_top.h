#ifndef _ISP_TOP_H_INC_
#define _ISP_TOP_H_INC_

#include <rtsavisp.h>

int isp_top_get_status(void);
void isp_top_set_status(enum rts_isp_status status);
void isp_top_lock_internal(void);
void isp_top_unlock_internal(void);
void *isp_top_get_poll(void);
void *isp_top_get_core(uint32_t isp_id);
struct isp_mod *isp_top_get_mod(int isp_id, int mod_id);
struct isp_algo_manager *isp_top_get_algom(void);
struct isp_sensor_manager *isp_top_get_snrm(void);

int isp_top_bind_algo_unlock(int isp_id, int id);
int isp_top_unbind_algo_unlock(int isp_id, int id);
int isp_top_get_fcs_ready(void);
void isp_top_set_direct_i2c_mode(uint32_t direct_i2c_mode);
uint32_t isp_top_get_direct_i2c_mode(void);
void isp_top_set_hdr_mode(uint32_t hdr_mode);
uint32_t isp_top_get_hdr_mode(void);
void isp_top_set_mirrorflip_mode(uint32_t mirrorflip_mode);
uint32_t isp_top_get_mirrorflip_mode(void);
void isp_top_set_raw_mode_tnr_en(uint8_t tnr_en);
uint8_t isp_top_get_raw_mode_tnr_en(void);


#endif /* _ISP_TOP_H_INC_ */
