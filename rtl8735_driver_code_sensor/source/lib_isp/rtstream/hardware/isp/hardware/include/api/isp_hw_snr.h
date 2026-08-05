#ifndef _ISP_HW_SNR_H_INC_
#define _ISP_HW_SNR_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

struct isp_hw_snr_ops {
	int (*enable)(uint32_t isp_id, int enable);
	int (*estimation)(uint32_t isp_id);
	int (*set)(uint32_t isp_id, const isp_iq_snr_item_t *snr);
};

const struct isp_hw_snr_ops *isp_hw_snr_get_ops(void);

#endif /* _ISP_HW_SNR_H_INC_ */
