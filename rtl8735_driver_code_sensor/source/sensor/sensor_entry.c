#include "include/voe_ops.h"

extern const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void);

voe_ops_t *voe_ops = (void*)0;

void rts_isp_set_voe_ops(voe_ops_t *ops)
{
	voe_ops = ops;
}

void* sensor_entry[] = {
	(void*)rts_isp_get_sensor_ops,
	(void*)rts_isp_set_voe_ops
};

__attribute__((weak))
int isp_driver_is_fpga(void)
{
	// no more fpga
	return 0;
}