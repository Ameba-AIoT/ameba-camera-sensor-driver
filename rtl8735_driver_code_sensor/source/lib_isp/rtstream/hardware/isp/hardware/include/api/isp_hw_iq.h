#ifndef _ISP_HW_IQ_H_INC_
#define _ISP_HW_IQ_H_INC_

#include <rts_isp_geom.h>
#include <isp_iq_table.pb.h>
#include <rts_isp_tuning.h>

#define NR_LEVEL_CTRL_MIN 0
#define NR_LEVEL_CTRL_MAX 8
#define NR_LEVEL_CTRL_DEF 4
#define DE_LEVEL_CTRL_MIN 0
#define DE_LEVEL_CTRL_MAX 8
#define DE_LEVEL_CTRL_DEF 4

struct isp_hw_iq_ops {
	int (*init_vreg)(uint32_t isp_id);
	int (*set_static_regs)(uint32_t isp_id,
			       const isp_iq_texture_static_t *regs);
	int (*set_dynamic_regs)(uint32_t isp_id,
				uint32_t gain, int nr_level, int de_level,
				uint16_t md_val,
				const isp_iq_texture_dynamic_t *dynamic,
				uint32_t index);
	int (*set_dynamic_ratio_regs)(uint32_t isp_id,
				uint32_t gain, int nr_level,
				int de_level, uint16_t md_val,
				const isp_iq_texture_dyn_ratio_t *dyn_ratio,
				uint32_t index, uint32_t gain_index);
	int (*read_regs)(uint32_t isp_id,
			 struct rts_isp_tuning_reg *regs, uint32_t num);
	int (*write_regs)(uint32_t isp_id,
			  struct rts_isp_tuning_reg *regs, uint32_t num,
			  int *has_vreg);
};

const struct isp_hw_iq_ops *isp_hw_iq_get_ops(void);

#endif /* _ISP_HW_IQ_H_INC_ */
