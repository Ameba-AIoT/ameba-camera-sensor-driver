#ifndef _COMMON_H_INC_
#define _COMMON_H_INC_

#include <rts_isp.h>

int print_ctrl(uint32_t isp_id, uint32_t *id);
int get_ctrl(uint32_t isp_id, uint32_t id, int *value);
int set_ctrl(uint32_t isp_id, uint32_t id, int *value);
int get_ctrl_stdio(uint32_t isp_id, uint32_t id);
int set_ctrl_stdio(uint32_t isp_id, uint32_t id);

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#endif /* _COMMON_H_INC_ */
