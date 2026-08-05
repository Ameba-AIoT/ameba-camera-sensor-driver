/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_reg.h>
#include <isp_reg_base.h>

#define VIRTUAL_REG_SIZE 0x100
#define VIRTUAL_REG_NUM (VIRTUAL_REG_SIZE / 4)

static uint8_t isp_vreg_base[VIRTUAL_REG_SIZE];

uint32_t isp_read_vreg(uint32_t offset)
{
	offset -= VIRTUAL_REG_BASE;
	if (offset / 4 >= VIRTUAL_REG_NUM)
		return 0;
	return *(uint32_t *)(isp_vreg_base + (offset >> 2 << 2));
}

float isp_read_vreg_float(uint32_t offset)
{
	offset -= VIRTUAL_REG_BASE;
	if (offset / 4 >= VIRTUAL_REG_NUM)
		return 0;
	return *(float *)(isp_vreg_base + (offset >> 2 << 2));
}

void isp_write_vreg(uint32_t value, uint32_t offset)
{
	offset -= VIRTUAL_REG_BASE;
	if (offset / 4 >= VIRTUAL_REG_NUM)
		return;
	*(uint32_t *)(isp_vreg_base + (offset >> 2 << 2)) = value;
}

void isp_write_vreg_float(float value, uint32_t offset)
{
	offset -= VIRTUAL_REG_BASE;
	if (offset / 4 >= VIRTUAL_REG_NUM)
		return;
	*(float *)(isp_vreg_base + (offset >> 2 << 2)) = value;
}

void isp_write_vreg_mask(uint32_t value, uint32_t offset, uint32_t mask)
{
	uint32_t v;

	v = (isp_read_vreg(offset) & ~mask) | (value & mask);
	isp_write_vreg(v, offset);
}
