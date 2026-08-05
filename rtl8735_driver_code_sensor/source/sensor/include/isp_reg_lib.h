#ifndef _ISP_REG_H_INC_
#define _ISP_REG_H_INC_

#include <stdint.h>
#include <rts_isp_errno_lib.h>
//#include <isp_log.h>
#ifndef barrier
#define barrier() __asm__ __volatile__("": : :"memory")
#endif


//uint32_t isp_io_base0 = 0x40300000;

static inline uint32_t isp_read_reg(uint32_t offset)
{
	uint32_t value;

	value = *(volatile uint32_t *)(0x40300000 + offset);
	barrier();
	return value;
}

static inline void isp_write_reg(uint32_t value, uint32_t offset)
{
	barrier();
	*(volatile uint32_t *)(0x40300000 + offset) = value;
	//isp_info("%s 0x%08x 0x%08x result 0x%08x\r\n", __func__, (uint32_t)isp_io_base + offset, value, *(volatile uint32_t *)((uint32_t)isp_io_base + offset));
}

static inline void isp_clr_reg_bit(int bit, uint32_t offset)
{
	uint32_t v;

	v = isp_read_reg(offset) & ~(1 << bit);
	isp_write_reg(v, offset);
}

static inline void isp_set_reg_bit(int bit, uint32_t offset)
{
	uint32_t v;

	v = isp_read_reg(offset) | (1 << bit);
	isp_write_reg(v, offset);
}

static inline void isp_write_reg_mask(uint32_t value, uint32_t offset,
				      uint32_t mask)
{
	uint32_t v;

	v = (isp_read_reg(offset) & ~mask) | (value & mask);
	isp_write_reg(v, offset);
}

uint32_t isp_read_vreg(uint32_t offset);
float isp_read_vreg_float(uint32_t offset);
void isp_write_vreg(uint32_t value, uint32_t offset);
void isp_write_vreg_float(float value, uint32_t offset);
void isp_write_vreg_mask(uint32_t value, uint32_t offset, uint32_t mask);


#endif /* _ISP_REG_H_INC_ */
