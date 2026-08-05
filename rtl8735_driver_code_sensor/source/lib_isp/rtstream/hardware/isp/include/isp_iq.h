#ifndef _ISP_IQ_H_INC_
#define _ISP_IQ_H_INC_

#include <rts_isp.h>
#include <isp_utils.h>
#include <isp_iq_table.pb.h>
#include <isp_algo_param.pb.h>

#define _MAX_ISP_IQ_NUM 4
#define _MAX_ISP_IQ_BINARY_NUM 8

struct isp_iq_entry {
	char name[RTS_ISP_NAME_LEN];
	uint8_t day_id;
	uint8_t night_id;
	int16_t other_id;
};

struct isp_iq_binary_desc {
	uint32_t offset;
	uint32_t length;
};

struct isp_iq {
	int id;
	int dn;

	void *bfr;
	struct isp_iq_entry *entries;
	struct isp_iq_binary_desc *binaries;
	isp_iq_table_t *iq_table;
	isp_algo_param_t algo_param;
	struct {
		uint16_t major;
		uint16_t minor;
	} packed_version;
	uint8_t cus_version;

	uint32_t entry_bits;

	uint32_t owner_id;

	struct isp_iq_calb calb_data;
};

int isp_iq_init(struct isp_iq *iq);
int isp_iq_cleanup(struct isp_iq *iq);
int isp_iq_register(struct isp_iq *iq, const char *path);
int isp_iq_apply_awb_calb(isp_iq_awb1_t *awb, struct isp_iq_calb_awb *awb_calb);
int isp_iq_apply_mlsc_calb(isp_iq_mlsc_t *mlsc, struct isp_iq_calb_mlsc *mlsc_calb);
int isp_iq_apply_nlsc_calb(isp_iq_nlsc_t *nlsc, struct isp_iq_calb_nlsc *nlsc_calb);
int isp_iq_apply_calibration(struct isp_iq *iq, isp_iq_table_t *iq_table);
int isp_iq_load_from_file(struct isp_iq *iq);
int isp_iq_change_table(struct isp_iq *iq, int id);
int isp_iq_change_day_night(struct isp_iq *iq, int dn);
int isp_iq_reload_packed_iq(struct isp_iq *iq);
int isp_iq_get_hysteresis_bound(const isp_iq_hysteresis_bounds_t *bounds,
				int32_t value, int current_index);
int isp_iq_get_bound(const isp_iq_bounds_t *bounds, int32_t value);
int isp_iq_check_hysteresis_bounds(const isp_iq_hysteresis_bounds_t *bounds,
				   uint32_t item_count);
int isp_iq_check_bounds(const isp_iq_bounds_t *bounds, uint32_t item_count);

const isp_iq_blc_t *isp_iq_get_blc(uint32_t isp_id);
const isp_iq_nlsc_t *isp_iq_get_nlsc(uint32_t isp_id);
const isp_iq_mlsc_t *isp_iq_get_mlsc(uint32_t isp_id);
const isp_iq_ae_t *isp_iq_get_ae(uint32_t isp_id);
const isp_iq_awb_t *isp_iq_get_awb(uint32_t isp_id);
const isp_iq_af_t *isp_iq_get_af(uint32_t isp_id);
const isp_iq_ccm_t *isp_iq_get_ccm(uint32_t isp_id);
const isp_iq_gamma_t *isp_iq_get_gamma(uint32_t isp_id);
const isp_iq_wdr_t *isp_iq_get_wdr(uint32_t isp_id);
const isp_iq_ygc_t *isp_iq_get_ygc(uint32_t isp_id);
const isp_iq_uvtune_t *isp_iq_get_uvtune(uint32_t isp_id);
const isp_iq_spe_t *isp_iq_get_spe(uint32_t isp_id);
const isp_iq_texture_t *isp_iq_get_texture(uint32_t isp_id);
const isp_iq_daynight_t *isp_iq_get_daynight(uint32_t isp_id);
const isp_iq_high_temp_t *isp_iq_get_high_temp(uint32_t isp_id);
const isp_iq_tm_t *isp_iq_get_tm(uint32_t isp_id);
const isp_iq_snr_t *isp_iq_get_snr(uint32_t isp_id);
const isp_iq_md_t *isp_iq_get_md(uint32_t isp_id);

isp_algo_param_t *isp_iq_get_algo_param(uint32_t isp_id);

int isp_iq_is_ae_on(void);
int isp_iq_is_awb_on(void);

#endif /* _ISP_IQ_H_INC_ */
