/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_hw_sensor.h>
#include <isp_reg_virtual.h>

static int isp_hw_sensor_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(0, VSENSOR_MIRROR_FLIP);
	return RTS_ISP_OK;
}

static int isp_hw_sensor_get_mirror_flip(uint32_t isp_id, uint8_t *mirror_en, uint8_t *flip_en)
{
	uint32_t mirror_flip_stat = isp_read_vreg(VSENSOR_MIRROR_FLIP);

	*mirror_en = mirror_flip_stat & VSENSOR_MIRROR_MASK;
	*flip_en = (mirror_flip_stat & VSENSOR_FLIP_MASK) >> VSENSOR_FLIP_OFFSET;

	return RTS_ISP_OK;
}

static int isp_hw_sensor_set_mirror_flip(uint32_t isp_id, uint8_t mirror_en, uint8_t flip_en)
{
	uint32_t mirror_flip_stat;

	mirror_flip_stat = (mirror_en & 0x1) | (flip_en & 0x1) << VSENSOR_FLIP_OFFSET;
	isp_write_vreg(mirror_flip_stat, VSENSOR_MIRROR_FLIP);

	return RTS_ISP_OK;
}

static const struct isp_hw_sensor_ops hw_sensor_ops = {
	.get_mirror_flip = isp_hw_sensor_get_mirror_flip,
	.set_mirror_flip = isp_hw_sensor_set_mirror_flip,
	.init_vreg = isp_hw_sensor_init_vreg,
};

const struct isp_hw_sensor_ops *isp_hw_sensor_get_ops(void)
{
	return &hw_sensor_ops;
}

