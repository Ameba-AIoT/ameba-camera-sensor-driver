/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_iq.h>
#include <isp_reg.h>
#include <isp_reg_base.h>
#include <isp_reg_virtual.h>

#define IQ_REG_OFFSET_OFFSET 27
#define IQ_REG_OFFSET_BITS 5
#define IQ_REG_OFFSET_MASK \
	(((1 << IQ_REG_OFFSET_BITS) - 1) << IQ_REG_OFFSET_OFFSET)
#define IQ_REG_BITS_OFFSET 22
#define IQ_REG_BITS_BITS 5
#define IQ_REG_BITS_MASK \
	(((1 << IQ_REG_BITS_BITS) - 1) << IQ_REG_BITS_OFFSET)
#define IQ_REG_ADDR_OFFSET 0
#define IQ_REG_ADDR_BITS 22
#define IQ_REG_ADDR_MASK \
	(((1 << IQ_REG_ADDR_BITS) - 1) << IQ_REG_ADDR_OFFSET)

#define iq_get_addr(addr) \
	(((addr) & IQ_REG_ADDR_MASK) >> IQ_REG_ADDR_OFFSET)
#define iq_get_offset(addr) \
	(((addr) & IQ_REG_OFFSET_MASK) >> IQ_REG_OFFSET_OFFSET)
#define iq_get_bits(addr) \
	(((addr) & IQ_REG_BITS_MASK) >> IQ_REG_BITS_OFFSET)

static int isp_hw_iq_init_vreg(uint32_t isp_id)
{
	isp_write_vreg(NR_LEVEL_CTRL_DEF, VNR_LEVEL);
	isp_write_vreg(DE_LEVEL_CTRL_DEF, VDE_LEVEL);
	return RTS_ISP_OK;
}

static void isp_write_iq_reg(uint32_t value, uint32_t offset)
{
	if (!(offset & IQ_REG_ADDR_MASK))
		return;
	if (offset & IQ_REG_BITS_MASK) {
		uint32_t reg_offset = iq_get_addr(offset);
		int bits = iq_get_bits(offset);
		int bit_offset = iq_get_offset(offset);

		if (reg_offset < VIRTUAL_REG_BASE)
			isp_write_reg_mask(value << bit_offset, reg_offset,
					   ((1 << bits) - 1) << bit_offset);
		else
			isp_write_vreg_mask(value << bit_offset, reg_offset,
					    ((1 << bits) - 1) << bit_offset);
	} else {
		if (offset < VIRTUAL_REG_BASE)
			isp_write_reg(value, offset);
		else
			isp_write_vreg(value, offset);
	}
}

static inline void isp_write_iq_level_reg(int32_t value, uint32_t offset,
					  const isp_iq_level_t *l_info,
					  int level)
{
	value = clamp_t(int32_t, value + level * l_info->multiple + 0.5f,
			l_info->min_val, l_info->max_val);
	isp_write_iq_reg(value, offset);
}

static int isp_hw_iq_set_static_regs(uint32_t isp_id,
				     const isp_iq_texture_static_t *static_regs)
{
	int i;

	if (!static_regs)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < static_regs->offsets_count; i++)
		isp_write_iq_reg(static_regs->values[i],
				 static_regs->offsets[i]);

	return RTS_ISP_OK;
}

static int isp_hw_iq_set_dynamic_regs(uint32_t isp_id,
				      uint32_t gain, int nr_level, int de_level,
					  uint16_t md_val,
				      const isp_iq_texture_dynamic_t *dynamic,
				      uint32_t index)
{
	int i;
	const isp_iq_texture_dynamic_value_t *val0;
	const isp_iq_texture_dynamic_offset_t *offset;
	const int nr_def = isp_read_vreg(VNR_LEVEL);
	const int de_def = isp_read_vreg(VDE_LEVEL);

	if (nr_level < NR_LEVEL_CTRL_DEF)
		nr_level = linear_intp(nr_level,
				       NR_LEVEL_CTRL_MIN, NR_LEVEL_CTRL_MIN,
				       NR_LEVEL_CTRL_DEF, nr_def);
	else
		nr_level = linear_intp(nr_level,
				       NR_LEVEL_CTRL_DEF, nr_def,
				       NR_LEVEL_CTRL_MAX, NR_LEVEL_CTRL_MAX);
	if (de_level < DE_LEVEL_CTRL_DEF)
		de_level = linear_intp(de_level,
				       DE_LEVEL_CTRL_MIN, DE_LEVEL_CTRL_MIN,
				       DE_LEVEL_CTRL_DEF, de_def);
	else
		de_level = linear_intp(de_level,
				       DE_LEVEL_CTRL_DEF, de_def,
				       DE_LEVEL_CTRL_MAX, DE_LEVEL_CTRL_MAX);

	if (!dynamic || index > dynamic->bounds.bounds_count)
		return -RTS_ISP_EINVAL;

	offset = &dynamic->offset;

	if (index == dynamic->bounds.bounds_count)
		val0 = &dynamic->values[index - 1];
	else
		val0 = &dynamic->values[index];

	/* write discrete regs */
	for (i = 0; i < offset->discrete_offsets_count; i++)
		isp_write_iq_reg(val0->discrete_values[i],
				 offset->discrete_offsets[i]);
	for (i = 0; i < offset->nr_discrete_offsets_count; i++)
		isp_write_iq_level_reg(val0->nr_discrete_values[i],
				       offset->nr_discrete_offsets[i],
				       &offset->nr_discrete_levels[i],
				       nr_level);
	for (i = 0; i < offset->de_discrete_offsets_count; i++)
		isp_write_iq_level_reg(val0->de_discrete_values[i],
				       offset->de_discrete_offsets[i],
				       &offset->de_discrete_levels[i],
				       de_level);
	for (i = 0; i < offset->md_discrete_offsets_count; i++) {
		if (val0->md_ind_discrete_enable[i])
			isp_write_iq_level_reg(val0->md_discrete_values[i],
						offset->md_discrete_offsets[i],
						&offset->md_discrete_levels[i],
						md_val);
		else
			isp_write_iq_reg(val0->md_discrete_values[i],
						offset->md_discrete_offsets[i]);
	}

	/* write continuous regs */
	if (index > 0 && index < dynamic->bounds.bounds_count) {
		int value;
		int th0;
		int th1;
		const isp_iq_texture_dynamic_value_t *val1;

		th0 = dynamic->bounds.bounds[index];
		th1 = dynamic->bounds.bounds[index - 1];
		val1 = &dynamic->values[index - 1];

		for (i = 0; i < offset->continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->continuous_values[i],
					    th1, val1->continuous_values[i]);
			isp_write_iq_reg(value, offset->continuous_offsets[i]);
		}
		for (i = 0; i < offset->nr_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->nr_continuous_values[i],
					    th1, val1->nr_continuous_values[i]);
			isp_write_iq_level_reg(value,
					       offset->nr_continuous_offsets[i],
					       &offset->nr_continuous_levels[i],
					       nr_level);
		}
		for (i = 0; i < offset->de_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->de_continuous_values[i],
					    th1, val1->de_continuous_values[i]);
			isp_write_iq_level_reg(value,
					       offset->de_continuous_offsets[i],
					       &offset->de_continuous_levels[i],
					       de_level);
		}
		for (i = 0; i < offset->md_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->md_continuous_values[i],
					    th1, val1->md_continuous_values[i]);
			if (val0->md_ind_continuous_enable[i])
				isp_write_iq_level_reg(value,
					       offset->md_continuous_offsets[i],
					       &offset->md_continuous_levels[i],
							md_val);
			else
				isp_write_iq_reg(value, offset->md_continuous_offsets[i]);
		}

	} else {
		for (i = 0; i < offset->continuous_offsets_count; i++)
			isp_write_iq_reg(val0->continuous_values[i],
					 offset->continuous_offsets[i]);
		for (i = 0; i < offset->nr_continuous_offsets_count; i++)
			isp_write_iq_level_reg(val0->nr_continuous_values[i],
					       offset->nr_continuous_offsets[i],
					       &offset->nr_continuous_levels[i],
					       nr_level);
		for (i = 0; i < offset->de_continuous_offsets_count; i++)
			isp_write_iq_level_reg(val0->de_continuous_values[i],
					       offset->de_continuous_offsets[i],
					       &offset->de_continuous_levels[i],
					       de_level);
		for (i = 0; i < offset->md_continuous_offsets_count; i++)
			if (val0->md_ind_continuous_enable[i])
				isp_write_iq_level_reg(val0->md_continuous_values[i],
					       offset->md_continuous_offsets[i],
					       &offset->md_continuous_levels[i],
							md_val);
			else
				isp_write_iq_reg(val0->md_continuous_values[i],
							offset->md_continuous_offsets[i]);
	}

	return RTS_ISP_OK;
}

static int isp_hw_iq_set_dynamic_ratio_regs(uint32_t isp_id,
				uint32_t gain, int nr_level,
				int de_level, uint16_t md_val,
				const isp_iq_texture_dyn_ratio_t *dyn_ratio,
				uint32_t index, uint32_t gain_index)
{
	int i;
	const isp_iq_texture_dynamic_value_t *val0;
	const isp_iq_texture_dynamic_offset_t *offset;
	const isp_iq_texture_dyn_ratio_item_t *ratio_item;
	const int nr_def = isp_read_vreg(VNR_LEVEL);
	const int de_def = isp_read_vreg(VDE_LEVEL);

	if (nr_level < NR_LEVEL_CTRL_DEF)
		nr_level = linear_intp(nr_level,
				       NR_LEVEL_CTRL_MIN, NR_LEVEL_CTRL_MIN,
				       NR_LEVEL_CTRL_DEF, nr_def);
	else
		nr_level = linear_intp(nr_level,
				       NR_LEVEL_CTRL_DEF, nr_def,
				       NR_LEVEL_CTRL_MAX, NR_LEVEL_CTRL_MAX);
	if (de_level < DE_LEVEL_CTRL_DEF)
		de_level = linear_intp(de_level,
				       DE_LEVEL_CTRL_MIN, DE_LEVEL_CTRL_MIN,
				       DE_LEVEL_CTRL_DEF, de_def);
	else
		de_level = linear_intp(de_level,
				       DE_LEVEL_CTRL_DEF, de_def,
				       DE_LEVEL_CTRL_MAX, DE_LEVEL_CTRL_MAX);

	if (!dyn_ratio || index > dyn_ratio->bounds.bounds_count ||
	     gain_index > dyn_ratio->dyn_gain_bounds.bounds_count)
		return -RTS_ISP_EINVAL;

	offset = &dyn_ratio->offset;

	/* ratio and bounds will always be pow of 2,
	   so we don't have to do lintp on ratio index */
	if (index == dyn_ratio->bounds.bounds_count) {
		ratio_item = &dyn_ratio->ratio_items[index - 1];
	} else {
		ratio_item = &dyn_ratio->ratio_items[index];
	}

	if (gain_index == dyn_ratio->dyn_gain_bounds.bounds_count) {
		val0 = &ratio_item->gain_items[gain_index - 1];
	} else {
		val0 = &ratio_item->gain_items[gain_index];
	}

	/* write discrete regs */
	for (i = 0; i < offset->discrete_offsets_count; i++)
		isp_write_iq_reg(val0->discrete_values[i],
				 offset->discrete_offsets[i]);
	for (i = 0; i < offset->nr_discrete_offsets_count; i++)
		isp_write_iq_level_reg(val0->nr_discrete_values[i],
				       offset->nr_discrete_offsets[i],
				       &offset->nr_discrete_levels[i],
				       nr_level);
	for (i = 0; i < offset->de_discrete_offsets_count; i++)
		isp_write_iq_level_reg(val0->de_discrete_values[i],
				       offset->de_discrete_offsets[i],
				       &offset->de_discrete_levels[i],
				       de_level);
	for (i = 0; i < offset->md_discrete_offsets_count; i++) {
		if (val0->md_ind_discrete_enable[i])
			isp_write_iq_level_reg(val0->md_discrete_values[i],
						offset->md_discrete_offsets[i],
						&offset->md_discrete_levels[i],
						md_val);
		else
			isp_write_iq_reg(val0->md_discrete_values[i],
						offset->md_discrete_offsets[i]);
	}

	/* write continuous regs */
	if (gain_index > 0 && gain_index < dyn_ratio->dyn_gain_bounds.bounds_count) {
		int value;
		int th0;
		int th1;
		const isp_iq_texture_dynamic_value_t *val1;

		th0 = dyn_ratio->dyn_gain_bounds.bounds[gain_index];
		th1 = dyn_ratio->dyn_gain_bounds.bounds[gain_index - 1];
		val1 = &ratio_item->gain_items[gain_index - 1];

		for (i = 0; i < offset->continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->continuous_values[i],
					    th1, val1->continuous_values[i]);
			isp_write_iq_reg(value, offset->continuous_offsets[i]);
		}
		for (i = 0; i < offset->nr_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->nr_continuous_values[i],
					    th1, val1->nr_continuous_values[i]);
			isp_write_iq_level_reg(value,
					       offset->nr_continuous_offsets[i],
					       &offset->nr_continuous_levels[i],
					       nr_level);
		}
		for (i = 0; i < offset->de_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->de_continuous_values[i],
					    th1, val1->de_continuous_values[i]);
			isp_write_iq_level_reg(value,
					       offset->de_continuous_offsets[i],
					       &offset->de_continuous_levels[i],
					       de_level);
		}
		for (i = 0; i < offset->md_continuous_offsets_count; i++) {
			value = linear_intp(gain,
					    th0, val0->md_continuous_values[i],
					    th1, val1->md_continuous_values[i]);
			if (val0->md_ind_continuous_enable[i])
				isp_write_iq_level_reg(value,
					       offset->md_continuous_offsets[i],
					       &offset->md_continuous_levels[i],
							md_val);
			else
				isp_write_iq_reg(value, offset->md_continuous_offsets[i]);
		}

	} else {
		for (i = 0; i < offset->continuous_offsets_count; i++)
			isp_write_iq_reg(val0->continuous_values[i],
					 offset->continuous_offsets[i]);
		for (i = 0; i < offset->nr_continuous_offsets_count; i++)
			isp_write_iq_level_reg(val0->nr_continuous_values[i],
					       offset->nr_continuous_offsets[i],
					       &offset->nr_continuous_levels[i],
					       nr_level);
		for (i = 0; i < offset->de_continuous_offsets_count; i++)
			isp_write_iq_level_reg(val0->de_continuous_values[i],
					       offset->de_continuous_offsets[i],
					       &offset->de_continuous_levels[i],
					       de_level);
		for (i = 0; i < offset->md_continuous_offsets_count; i++)
			if (val0->md_ind_continuous_enable[i])
				isp_write_iq_level_reg(val0->md_continuous_values[i],
					       offset->md_continuous_offsets[i],
					       &offset->md_continuous_levels[i],
							md_val);
			else
				isp_write_iq_reg(val0->md_continuous_values[i],
							offset->md_continuous_offsets[i]);
	}

	return RTS_ISP_OK;
}

static int isp_hw_iq_read_regs(uint32_t isp_id,
			       struct rts_isp_tuning_reg *regs, uint32_t num)
{
	int i;

	if (!regs || !num)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < (int)num; i++) {
		int mask = regs[i].mask ? (int)regs[i].mask : ~0;

		if (regs[i].offset < VIRTUAL_REG_BASE)
			regs[i].value = isp_read_reg(regs[i].offset) & mask;
		else
			regs[i].value = isp_read_vreg(regs[i].offset) & mask;
	}
	return RTS_ISP_OK;
}

static int isp_hw_iq_write_regs(uint32_t isp_id,
				struct rts_isp_tuning_reg *regs, uint32_t num,
				int *has_vreg)
{
	int i;

	if (!regs || !num || !has_vreg)
		return -RTS_ISP_EINVAL;

	*has_vreg = RTS_ISP_FALSE;
	for (i = 0; i < (int)num; i++) {
		if (regs[i].offset < VIRTUAL_REG_BASE) {
			if (regs[i].mask)
				isp_write_reg_mask(regs[i].value,
						   regs[i].offset,
						   regs[i].mask);
			else
				isp_write_reg(regs[i].value, regs[i].offset);
		} else {
			*has_vreg = RTS_ISP_TRUE;
			if (regs[i].mask)
				isp_write_vreg_mask(regs[i].value,
						    regs[i].offset,
						    regs[i].mask);
			else
				isp_write_vreg(regs[i].value, regs[i].offset);
		}
	}
	return RTS_ISP_OK;
}

static const struct isp_hw_iq_ops hw_iq_ops = {
	.init_vreg = isp_hw_iq_init_vreg,
	.set_static_regs = isp_hw_iq_set_static_regs,
	.set_dynamic_regs = isp_hw_iq_set_dynamic_regs,
	.set_dynamic_ratio_regs = isp_hw_iq_set_dynamic_ratio_regs,
	.read_regs = isp_hw_iq_read_regs,
	.write_regs = isp_hw_iq_write_regs,
};

const struct isp_hw_iq_ops *isp_hw_iq_get_ops(void)
{
	return &hw_iq_ops;
}
