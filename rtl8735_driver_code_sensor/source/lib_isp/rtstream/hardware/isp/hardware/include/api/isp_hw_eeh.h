#ifndef _ISP_HW_EEN_H_INC_
#define _ISP_HW_EEN_H_INC_

#include <stdint.h>

//#define EEH_CTRL_MIN 0
//#define EEH_CTRL_DEF 50
//#define EEH_CTRL_MAX 100
#define SHARPNESS_CTRL_MIN 0
#define SHARPNESS_CTRL_DEF 50
#define SHARPNESS_CTRL_MAX 100

struct isp_hw_eeh_ops {
	int (*init_vreg)(uint32_t isp_id);
	int (*estimation)(uint32_t isp_id);
	int (*set_sharpness)(uint32_t isp_id, int sharpness);
};

const struct isp_hw_eeh_ops *isp_hw_eeh_get_ops(void);

#endif /* _ISP_HW_EEN_H_INC_ */
