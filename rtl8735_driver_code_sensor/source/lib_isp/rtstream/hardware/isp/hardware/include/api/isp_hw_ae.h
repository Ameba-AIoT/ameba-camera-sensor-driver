#ifndef _ISP_HW_AE_H_INC_
#define _ISP_HW_AE_H_INC_

#include <stdint.h>
#include <rts_isp_geom.h>
#include <rts_isp_define.h>
#include <rts_isp_sensor.h>
#include <rts_isp_ae.h>

#define AE_MIN_RATIO 2
#define AE_MAX_RATIO 64
#define AE_DEF_RATIO 16

struct isp_ae_hw_desc {
	rts_isp_grid_info_t grid_info;
	rts_isp_size_t cell_sample;

	uint16_t hist_bins;
	rts_isp_size_t hist_sample;

	/* sizeof each statis entry */
	uint8_t y_mean_size;
	uint8_t hist_bin_size;
};

struct isp_ae_hw_info {
	struct isp_ae_hw_desc ae;
	struct isp_ae_hw_desc hdr[RTS_ISP_HDR_CHAN_MAX];
};

struct isp_hw_ae_ops {
	int (*get_hw_info)(uint32_t isp_id, struct isp_ae_hw_info *info);
	int (*set_statis)(uint32_t isp_id, const rts_isp_grid_t *grid);
	int (*get_sync_regs)(uint32_t isp_id, uint32_t delay,
			     struct rts_isp_sync_reg *reg, int *num,
			     const struct rts_isp_ae_exp_gain *exp_gain);
	int (*set_hdr)(uint32_t isp_id);
	int (*enable_hdr)(uint32_t isp_id, int enable);
};

const struct isp_hw_ae_ops *isp_hw_ae_get_ops(void);

#endif /* _ISP_HW_AE_H_INC_ */
