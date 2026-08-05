#ifndef _ISP_HW_INTP_H_INC_
#define _ISP_HW_INTP_H_INC_

#include <stdint.h>
#include <rts_isp.h>
#include <rts_isp_geom.h>

struct isp_hw_intp_ops {
	int (*set_frame_size)(uint32_t isp_id,
			      const rts_isp_size_t *size);
	int (*estimation)(uint32_t isp_id,
		enum rts_isp_drc_mode drc_mode, uint8_t* drc_blending_rate);
	int (*dynamic)(uint32_t isp_id, float awb_g_gain, float ae_gain,
			float sensor_gain);
};

const struct isp_hw_intp_ops *isp_hw_intp_get_ops(void);

#endif /* _ISP_HW_INTP_H_INC_ */
