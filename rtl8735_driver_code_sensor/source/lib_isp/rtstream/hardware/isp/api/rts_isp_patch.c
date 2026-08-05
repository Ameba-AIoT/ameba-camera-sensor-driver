/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_top.h>
#include <isp_mod.h>
#include <isp_mod_iq.h>

static void write_vreg(uint32_t isp_id, int data, int offset)
{
	struct rts_isp_tuning_reg reg;
	struct isp_iq_tuning_regs regs;

	reg.offset = 0x200000 + offset;
	reg.value = data;
	reg.mask = 0;
	regs.regs = &reg;
	regs.num = 1;

	isp_mod_execute(isp_top_get_mod(isp_id, MOD_IQ),
			IQ_EXEC_WRITE_REGS, &regs, sizeof(regs));
}

void rts_isp_patch_set_sharpness(uint32_t isp_id, int sharpness)
{
	write_vreg(isp_id, sharpness, 0x005C);
}

void rts_isp_patch_set_saturation(uint32_t isp_id, int saturation)
{
	write_vreg(isp_id, saturation, 0x0060);
}

void rts_isp_patch_set_contrast(uint32_t isp_id, int contrast)
{
	write_vreg(isp_id, contrast, 0x0064);
}

void rts_isp_patch_set_nr_level(uint32_t isp_id, int nr_level)
{
	write_vreg(isp_id, nr_level, 0x0068);
}

void rts_isp_patch_set_de_level(uint32_t isp_id, int de_level)
{
	write_vreg(isp_id, de_level, 0x006C);
}

