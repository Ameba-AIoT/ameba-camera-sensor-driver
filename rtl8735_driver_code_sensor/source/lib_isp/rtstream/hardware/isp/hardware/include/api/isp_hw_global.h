#ifndef _ISP_HW_GLOBAL_H_INC_
#define _ISP_HW_GLOBAL_H_INC_

#include <stdint.h>
#include <rts_isp.h>

struct isp_speed_ctrl {
	uint8_t speed_mult;
	uint8_t speed_div;
	uint16_t last_break;
};

struct isp_output_menu {
	int num;
	const char * const *menu;
};

struct isp_global_snr_info {
	enum rts_isp_sensor_hdr_mode hdr;
	enum rts_isp_sensor_type type;
};

struct isp_hw_global_ops {
	int (*set_func_enable)(uint32_t isp_id, struct isp_global_snr_info snr_info,
			       struct rts_isp_bypass bypass);
	int (*set_isp_path)(uint32_t isp_id, enum rts_isp_sensor_type type);
	int (*enable_data)(uint32_t isp_id, int enable);
	int (*delay_data)(uint32_t isp_id, int delay, struct rts_isp_sync_regs *regs);
	int (*select_interface)(uint32_t isp_id, enum rts_isp_interface inf);
	int (*start_transfer)(uint32_t isp_id);
	int (*stop_transfer)(uint32_t isp_id);
	int (*set_speed_ctrl)(uint32_t isp_id, struct isp_speed_ctrl *speed);
	int (*get_output_menu)(uint32_t isp_id, struct isp_output_menu *menu);
	int (*set_output)(uint32_t isp_id, uint32_t output);
	int (*set_output_chn)(uint32_t isp_id, uint32_t chn);
	int (*set_statis_irq_enable)(uint32_t isp_id, uint8_t statis_irq_en);
};

const struct isp_hw_global_ops *isp_hw_global_get_ops(void);

#endif /* _ISP_HW_GLOBAL_H_INC_ */
