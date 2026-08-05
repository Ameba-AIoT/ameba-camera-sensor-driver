#ifndef _ISP_HW_SPE_H_INC_
#define _ISP_HW_SPE_H_INC_

#include <stdint.h>
#include <isp_iq_table.pb.h>

#define BRIGHT_CTRL_MIN -64
#define BRIGHT_CTRL_MAX 64
#define BRIGHT_CTRL_DEF 0
#define CONTRAST_CTRL_MIN 0
#define CONTRAST_CTRL_MAX 100
#define CONTRAST_CTRL_DEF 50
#define SATURATION_CTRL_MIN 0
#define SATURATION_CTRL_MAX 100
#define SATURATION_CTRL_DEF 50
#define YGAIN_CTRL_MIN 0
#define YGAIN_CTRL_MAX 128
#define YGAIN_CTRL_DEF 64

struct isp_hw_spe_ops {
	int (*init_vreg)(uint32_t isp_id);
	int (*set_uv_offset)(uint32_t isp_id,
			     const isp_iq_uv_offset_item_t *uv_offset);
	int (*set_brightness)(uint32_t isp_id, int value);
	int (*set_contrast)(uint32_t isp_id, int value);
	int (*set_saturation)(uint32_t isp_id, int value);
	int (*set_gray_mode)(uint32_t isp_id, int enable);
	int (*set_y_gain)(uint32_t isp_id, int value);
};

const struct isp_hw_spe_ops *isp_hw_spe_get_ops(void);

#endif /* _ISP_HW_SPE_H_INC_ */

