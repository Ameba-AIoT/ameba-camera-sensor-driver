/*
 * Copyright 2019 Realtek Semiconductor Corp.
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "cmsis_os2.h"
#include "errno.h"
#include "rt_types.h"
#include "rts_errno.h"
#include "rlx_reg.h"

#include "rlx_clk.h"
#include "rts3915-clock.h"
#include "bspchip.h"
#include "my_def.h"
#include "rt_time.h"
#include "platform_conf.h"
#include "rts_isp_sensor.h"
#include "rtl8735b_syson_s_type_simple.h"
#include "isp_debug.h"

enum {
	TYPE_RLE0745 = 1,
	TYPE_RTS3901 = 2,
	TYPE_RTS3903 = 3,
	TYPE_RLE0943 = 4,
	TYPE_RTS3915 = 5,

	TYPE_FPGA = (1 << 16),
};
#if 0
#define CLK_CHANGE_R		(0)
#define UART_CLK_LP_EN_R	(0x04)

#define DRAM_CLK_CFG_R		(0x0c)
#define CPU_CLK_CFG_R		(0x10)
#define XB2_CLK_CFG_R		(0x14)
#define BUS_CLK_CFG_R		(0x18)
#define I2S_CLK_CFG_R		(0x1c)
#define CIPHER_CLK_CFG_R	(0x20)
#define UART_CLK_CFG_R		(0x28)
#define I2C_CLK_CFG_R		(0x2c)

#define RTC32K_DIV_CFG0_R	(0x3c)
#define RTC32K_DIV_CFG1_R	(0x40)
#define RTC32K_DIV_CFG2_R	(0x44)
#define RTC_CLK_CFG_R		(0x48)
#define USBPHY_CLK_CFG_R	(0x4c)
#define JPEG_CLK_CFG_R		(0x50)

#define ISP_SCAN_CLK_CFG_R	(0x58)
#define MIPI_SCAN_CLK_CFG_R	(0x5c)
#define SPDIF_CLK_CFG_R		(0x60)

#define CODEC_CLK_CFG_R		(0x68)

#define GE_CLK_EN_R			(0x78)
#define H265_ACLK_CFG_R		(0x80)
#define H265_BCLK_CFG_R		(0x84)
#define H265_CCLK_CFG_R		(0x88)
#define SSOR_HCLK_CFG_R		(0x8C)
#define SSOR_CLK_OE_R		(0x90)
#define RSA_CLK_EN_R		(0xA0)
#define SHA_CLK_EN_R		(0xA4)
#define NN_BUS_CLK_CFG_R	(0xB0)
#define NN_CORE_CLK_CFG_R	(0xB4)
#define NN_SH_CLK_CFG_R		(0xB8)
#define TRNG_CLK_CFG_R		(0xBC)
#define LCDC_DRAM_CLK_CFG_R	(0xC0)
#define ETHERNET_CLK_CFG_R	(0xC4)
#define EFUSE_CLK_CFG_R		(0xC8)
#define MAC_BYPASS_CLK_CFG_R	(0xCC)
#define JPEG_DRAM_CLK_CFG_R		(0xD0)
#define MIPI_TX_CFG_R		(0xD4)
#define DMA_CLK_CFG_R		(0xD8)
#define MIPI_TX_LOW_CLK_CFG_R	(0xDC)

#define BSP_CLK_GPLL0_BASE_R		(0x000)
#define BSP_CLK_GPLL1_BASE_R		(0x100)
#define BSP_CLK_GPLL2_BASE_R		(0x200)
#define BSP_CLK_GPLL3_BASE_R		(0x300)

#define GPLL_CTRL 0x00
#define GPLL_CFG 0x04
#define GPLL_SCCG_CFG0 0x08
#define GPLL_SCCG_CFG1 0x0C
#define GPLL_STATUS 0x10
#define GPLL_SCCG_CFG2 0x14
#define GPLL_SCCG_CFG3 0x18

#define PPOW_LDO (1<<1)
#define GPLL_EN (1<<0)
#define SYSPLL_CK_RDY (1<<0)
#define REG_EN_SSC (1<<31)
#define CMU_SSC_RSTB (1<<0)
#define CMU_SSC_EN (1<<0)

#define LVDS_BASE_RF				(0x000)

#define R_LVDS_ANA_TOP_CFG_0		0x00
#define R_LVDS_ANA_TOP_CFG_1		0x04
#define R_LVDS_ANA_TOP_CFG_2		0x08
#define R_LVDS_ANA_TOP_CFG_3		0x0C
#define R_LVDS_ANA_TOP_CFG_4		0x10
#define R_LVDS_ANA_TOP_CFG_5		0x14
#define R_LVDS_ANA_TOP_CFG_6		0x18
#define R_LVDS_ANA_TOP_CFG_7		0x1C
#define R_LVDS_ANA_TOP_CFG_8		0x20
#define R_LVDS_ANA_TOP_CFG_9		0x24
#define R_LVDS_ANA_TOP_CFG_10		0x28
#define R_LVDS_ANA_TOP_CFG_11		0x2C
#define R_LVDS_ANA_TOP_CFG_12		0x30
#define R_LVDS_ANA_TOP_CFG_13		0x34
#define R_LVDS_ANA_TOP_CFG_14		0x38
#define R_LVDS_ANA_TOP_CFG_15		0x3C
#define R_LVDS_ANA_TOP_CFG_16		0x40
#define R_LVDS_ANA_TOP_CFG_17		0x44
#define R_LVDS_ANA_TOP_CFG_18		0x48
#define R_LVDS_ANA_TOP_CFG_19		0x4C
#define R_LVDS_ANA_TOP_CFG_20		0x50
#define R_LVDS_ANA_TOP_CFG_21		0x54
#define R_LVDS_ANA_TOP_CFG_22		0x58
#define R_POW_PIF_P1_TXL			0x5c
#define R_LVDS_ANA_GPIO_SEL			0x60
#define R_LVDS_ANA_GPIO_O			0x64
#define R_LCDC_CLK_CFG_REG			0x68
#define R_FPGA_CLK_CFG_REG			0x6C
#define LVDS_SSCG_CFG0				0x70
#define LVDS_SSCG_CFG1				0x74
#define LVDS_SSCG_CFG2				0x78

#define REG_PIF_EN_LV_LDO (1<<8)
#define REG_PIF_H_CMU_POW (1<<0)
#define REG_POW_PIF (1<<5)

#define BUS_CK_CHANGE			0x7
#define XB2_CK_CHANGE			0x6
#define CPU_CK_CHANGE			0x5
#define DRAM_CK_CHANGE			0x4
#define CK_CHANGE_NULL			0

#define BIG_SHORT_NUM	2
#define BIG_LONG_NUM	4

#endif

/*
 * flags used across common struct clk.  these flags should only affect the
 * top-level framework.  custom flags for dealing with hardware specifics
 * belong in struct clk_foo
 */
#define CLK_SET_RATE_GATE	BIT(0) /* must be gated across rate change */
#define CLK_SET_PARENT_GATE	BIT(1) /* must be gated across re-parent */
#define CLK_SET_RATE_PARENT	BIT(2) /* propagate rate change up one level */
#define CLK_IGNORE_UNUSED	BIT(3) /* do not gate even if unused */
				/* unused */
#define CLK_IS_BASIC		BIT(5) /* Basic clk, can't do a to_clk_foo() */
#define CLK_GET_RATE_NOCACHE	BIT(6) /* do not use the cached clk rate */
#define CLK_SET_RATE_NO_REPARENT BIT(7) /* don't re-parent on rate change */
#define CLK_GET_ACCURACY_NOCACHE BIT(8) /* do not use the cached clk accuracy */
#define CLK_RECALC_NEW_RATES	BIT(9) /* recalc rates after notifications */
#define CLK_SET_RATE_UNGATE	BIT(10) /* clock needs to run to set rate */
#define CLK_IS_CRITICAL		BIT(11) /* do not gate, ever */
/* parents need enable during gate/ungate, set rate and re-parent */
#define CLK_OPS_PARENT_ENABLE	BIT(12)


//static DEFINE_SPINLOCK(clk_spinlock);

static struct clk_rlx *clks[RLX_CLK_MIPITX_LOW + 1]={0};
static u32 clk_reg_v[100]={0};
static unsigned int clk_platform_type;

#define DEFINE_CLK_RLX(_name,	\
	_parent_names, _ops, _clk_reg, _clk_change)	\
	static struct clk_rlx _name = {	\
		.name = #_name,					\
		.parent_names = _parent_names,		\
		.num_parents = ARRAY_SIZE(_parent_names), \
		.ops = &_ops, \
		.clkreg	= _clk_reg,		\
		.clk_change	= _clk_change,			\
		.reg_v		= clk_reg_v,	\
		.reg_i		= (((u32)_clk_reg & 0xff) >> 2),	\
	}

#if 0
static volatile unsigned int *clk_mapped_addr;
static volatile unsigned int *pll_mapped_addr;
static volatile unsigned int *lvds_pll_mapped_addr;

#define to_clk_rlx(_hw) container_of(_hw, struct clk_rlx, hw)

static const char * const rlx_root_parent_names[] = {
	"sys_osc",
};

static const char * const rlx_usb_parent_names[] = {
	"usb_pll",
};

static const char * const rlx_gpll0_parent_names[] = {
	"gpll0",
};
static const char * const rlx_gpll1_parent_names[] = {
	"gpll1",
};
static const char * const rlx_gpll2_parent_names[] = {
	"gpll2",
};
static const char * const rlx_gpll3_parent_names[] = {
	"gpll3",
};

static const char * const rlx_lvds_pll_parent_names[] = {
	"lvds_pll",
};


static const char * const rlx_names_bus_div[] = {
	"usb_pll_2", "gpll0_2", "gpll0_5", "gpll1_7"
};

static const char * const rlx_names_bus_dec[] = {
	"bus_ck_div"
};

static const char * const rlx_names_cpu_div[] = {
	"usb_pll_3", "gpll0", "gpll1", "usb_pll",
};

static const char * const rlx_names_cpu_dec[] = {
	"cpu_ck_div"
};

static const char * const rlx_names_dram_div[] = {
	"usb_pll_2", "gpll0", "usb_pll", "gpll1_2"
};

static const char * const rlx_names_dram_dec[] = {
	"dram_ck_div"
};

static const char * const rlx_names_h265_aclk[] = {
	"dram_ck"
};

static const char * const rlx_names_h265_bclk_div[] = {
	"usb_pll_2", "usb_pll_3", "gpll0_2", "gpll1_2"
};

static const char * const rlx_names_h265_bclk_dec[] = {
	"h265_bclk_div"
};

static const char * const rlx_names_h265_cclk_div[] = {
	"usb_pll_2", "usb_pll_3", "gpll0_2", "gpll1_2"
};

static const char * const rlx_names_h265_cclk_dec[] = {
	"h265_cclk_div"
};

static const char * const rlx_names_nncore_div[] = {
	"usb_pll_2", "gpll0", "usb_pll", "gpll1_2"
};

static const char * const rlx_names_nncore_dec[] = {
	"nncore_ck_div"
};

static const char * const rlx_names_isp_div[] = {
	"usb_pll_2", "gpll0_3", "usb_pll_3", "gpll1_2"
};

static const char * const rlx_names_isp_dec[] = {
	"isp_ck_div"
};

static const char * const rlx_names_jpeg_div[] = {
	"usb_pll_2", "usb_pll_3", "gpll0_3", "gpll1_2"
};

static const char * const rlx_names_jpeg_dec[] = {
	"jpeg_ck_div"
};

static const char * const rlx_names_mipi_div[] = {
	"usb_pll_2", "gpll0_2", "usb_pll_3", "gpll1_2"
};

static const char * const rlx_names_mipi_dec[] = {
	"mipi_ck_div"
};

static const char * const rlx_names_ssor_hclk_div[] = {
	"usb_pll_5", "RESERVED", "gpll0_5", "gpll2_2"
};

static const char * const rlx_names_codec_div[] = {
	"usb_pll_5", "usb_pll_3", "gpll0_3", "gpll3_2"
};

static const char * const rlx_names_i2s_div[] = {
	"usb_pll_5", "usb_pll_3", "gpll0_3", "gpll3_2",
};

static const char * const rlx_names_spdif_div[] = {
	"usb_pll_5", "usb_pll_3", "gpll0_3", "gpll3_2"
};

static const char * const rlx_names_i2c_div[] = {
	"usb_pll_5", "usb_pll_3", "gpll0_5"
};

static const char * const rlx_names_uart_div[] = {
	"usb_pll_5", "gpll0_5", "gpll1_5"
};

static const char * const rlx_names_xb2_div[] = {
	"usb_pll_2", "gpll0_5", "gpll0_2"
};

static const char * const rlx_names_lcdc_div[] = {
	"lvds_pll_7", "usb_pll_3", "gpll0_5", "gpll1_7"
};

static const char * const rlx_names_macbypass_div[] = {
	"gpll0_2", "gpll1", "gll2_2", "gpll3_2"
};

static const char * const rlx_names_mipitx_lowdiv[] = {
	"usb_pll", "gpll0", "gpll1_2", "gpll1_3"
};

static const char * const rlx_names_v[] = {
	"dummy"
};

static inline u32 rts_clk_readl(u32 offset)
{
	return REG_R32(clk_mapped_addr + offset);
}

static inline void rts_clk_writel(unsigned int val, u32 offset)
{
	REG_W32(clk_mapped_addr + offset, val);
}

static inline u32 rts_pll_readl(u32 offset)
{
	return REG_R32(pll_mapped_addr + offset);
}

static inline void rts_pll_writel(unsigned int val, u32 offset)
{
	REG_W32(pll_mapped_addr + offset, val);
}

static inline u32 rts_lvds_pll_readl(u32 offset)
{
	return REG_R32(lvds_pll_mapped_addr + offset);
}

static inline void rts_lvds_pll_writel(unsigned int val, u32 offset)
{
	REG_W32(lvds_pll_mapped_addr + offset, val);
}
#endif

#if 0
static void setchgbit(int nr)
{
	u32 val;

	val = rts_clk_readl(CLK_CHANGE_R);
	val |=	(1<<nr);
	rts_clk_writel(val, CLK_CHANGE_R);
}

static void clrchgbit(int nr)
{
	u32 val;

	val = rts_clk_readl(CLK_CHANGE_R);
	val &=	~(1<<nr);
	rts_clk_writel(val, CLK_CHANGE_R);
}

static short bignumcmp(unsigned short *a, unsigned short *b)
{
	short i;

	for (i = BIG_SHORT_NUM - 1; i >= 0; i--) {
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	}

	return 0;
}

static short bignumsub(unsigned short *a, unsigned short *b)
{
	short i, sub = 0;

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		if (a[i] < b[i]) {
			a[i] -= b[i] + sub;
			sub = 1;
		} else {
			a[i] -= b[i];
			if (!a[i] && sub) {
				a[i] = 0xffff;
				sub = 1;
			} else {
			  a[i] -= sub;
			  sub = 0;
			}
		}
	}

	return sub;
}

static short bignumsubs(unsigned short *a, unsigned short *b)
{
	short i, sub = 0;

	for (i = 0; i < BIG_SHORT_NUM + 1; i++) {
		if (a[i] < b[i]) {
			a[i] -= b[i];
			a[i] -= sub;
			sub = 1;
		} else {
			a[i] -= b[i];
			if (!a[i] && sub) {
				a[i] = 0xffff;
				sub = 1;
			} else {
				a[i] -= sub;
				sub = 0;
			}
		}
	}

	return sub;
}

static void bignummuls(unsigned short *c,
	unsigned short *a, unsigned short b)
{
	short i, k;
	unsigned short add;
	unsigned long m;

	for (i = 0; i < BIG_SHORT_NUM + 1; i++)
		c[i] = 0;

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		m = (unsigned long)a[i] * (unsigned long)b;
		c[i] += m & 0xffff;

		if (c[i] < (m & 0xffff))
			add = (m >> 16) + 1;
		else
			add = m >> 16;
		k = i + 1;

		for (; c[k] += add, c[k] < add; add = 1, k++)
			;
	}
}

static void bignummul(unsigned short *c,
	unsigned short *a, unsigned short *b)
{
	short i, j, k;
	unsigned short add;
	unsigned long m;

	memset((void *)c, 0, BIG_LONG_NUM * 2);

	for (i = 0; i < BIG_SHORT_NUM; i++) {
		for (j = 0; j < BIG_SHORT_NUM; j++) {

			m = (unsigned long)a[i] * (unsigned long)b[j];

			c[i + j] += m & 0xffff;
			if (c[i + j] < (m & 0xffff))
				add = (m >> 16) + 1;
			else
				add = m >> 16;
			k = i + j + 1;

			for (; c[k] += add, c[k] < add; add = 1, k++)
				;
		}
	}
}

static void bignumdiv(unsigned short *a,
	unsigned short *c, unsigned short *b)
{
	short i, h;
	unsigned long m, n;
	unsigned short *d, e[BIG_SHORT_NUM + 1];

	for (i = 0; i < BIG_SHORT_NUM; i++)
		a[i] = 0;

	d = (unsigned short *)&c[BIG_SHORT_NUM];

	for (i = BIG_SHORT_NUM - 1; i >= 0; i--) {
		for (; h = bignumcmp(d, b), h >= 0;
		     bignumsub(d, b), a[i + 1]++)
			;

		d = (unsigned short *)&c[i];

		do {
			m = ((unsigned long)c[i + BIG_SHORT_NUM] << 16) +
			    (unsigned long)c[i + BIG_SHORT_NUM - 1];
			n = m / ((unsigned long)b[BIG_SHORT_NUM - 1] + 1);
			if (n)
				a[i] += n;
			else {
				if (m > b[BIG_SHORT_NUM - 1]) {
					d[BIG_SHORT_NUM - 1] =
					    1 - bignumsub(d, b);
					a[i]++;
				}
				break;
			}

			memset((void *)e, 0, (BIG_SHORT_NUM + 1) << 1);

			bignummuls(e, b, (unsigned short)n);
			bignumsubs(d, e);

		} while (1);
	}

	for (; h = bignumcmp(d, b), h >= 0; bignumsub(d, b), a[0]++)
		;
}
#endif


u32 clk_get_rate(struct clk_rlx *clk)
{
	if (!clk) return 0;

	return clk->rate;
}

static unsigned long clk_recalc(struct clk_rlx *clk,
				unsigned long parent_rate)
{
	if (clk->ops->recalc_rate)
		return clk->ops->recalc_rate(clk, parent_rate);
	return parent_rate;
}

void clk_set_rate(struct clk_rlx *clk, u32 rate)
{
	u32 old_rate, new_rate=rate;
	int i;

	if (!clk) return;

	old_rate = clk->rate;
	/* calculate new rates */
	if (clk->ops->round_rate)
		new_rate = clk->ops->round_rate(clk, rate,
						(unsigned long *)&clk->parent->rate);

	/* change to new rates */
	if (clk->ops->set_rate)
		clk->ops->set_rate(clk, new_rate, clk->parent->rate);

	clk->rate = clk_recalc(clk, clk->parent->rate);
	
	if (clk->num_siblins && (clk->rate != old_rate)) {  //update siblins' rate
		for (i=0; i < clk->num_siblins; i++) {
			struct clk_rlx *sib_clk = clk->siblins[i];
			sib_clk->rate = clk->rate * sib_clk->mult / sib_clk->div;
		}
	}

	return;
}
uint8_t hclk_timeout_chk (uint32_t start_cnt)
{
	uint32_t time_out_cnt = 0;
	uint32_t curr_cnt = 0;
	uint32_t expire_cnt = 0;

	time_out_cnt = 10000;
	curr_cnt = hal_read_curtime_us();

	if (start_cnt < curr_cnt) {
		expire_cnt =  curr_cnt - start_cnt;//(0xFFFFFFFF - curr_cnt) + start_cnt;
	} else {
		expire_cnt = (0xFFFFFFFF - start_cnt) + curr_cnt;//start_cnt - curr_cnt;
	}

	if (time_out_cnt < expire_cnt){
		return 1;//time-out
	} else {
		return 0;
	}

	return 0;
}

void hclk_set_rate(uint32_t rate)
{
	SYSON_S_TypeDef *syson_s = SYSON_S;
	volatile uint32_t val;
	uint32_t start_time = 0;

	switch (rate) {
	case CLK_NONE:
		//5000_0834[29]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0834[11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0834[12]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[31]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		return;

	case CLK_12M:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'000111
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (7 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'100
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (4 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'1100110011010
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0x199A << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1111
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (0x0F<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[12]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;
	case CLK_24M:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'000111
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (7 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'100
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (4 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'1100110011010
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0x199A << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1110
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (0x0E<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[12]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;
	case CLK_37M125:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'000101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (5 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'011
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (3 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'0110011001101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0xCCD << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1100
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (0x0C<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[12]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;
	case CLK_74M25:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'000101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (5 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'011
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (3 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'0110011001101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0xCCD << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (8<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[11]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_D2_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;	
	case CLK_27M:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'001000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (8 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'110
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (6 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'0110011001101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0xCCD << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1110
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (0x0E<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[12]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;
	case CLK_54M:
		//5000_0834[12:11]=0
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_REG_CK_EN_D2_ISP|SYSON_S_BIT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[10:5]=6b'001000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_DIVN_SDM_ISP);
		val |= (8 << SYSON_S_SHIFT_DIVN_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0840[18:16]=3b'110
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0N_SDM_ISP);
		val |= (6 << SYSON_S_SHIFT_F0N_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0840[31:19]=13b'0110011001101
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL3;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_F0F_SDM_ISP);
		val |= (0xCCD << SYSON_S_SHIFT_F0F_SDM_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL3 = val;

		//5000_0838[4:1]=4b'0000
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		HAL_CLEAR_BIT(val, SYSON_S_MASK_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[31]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_ERC_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		hal_delay_us(1);

		//5000_0834[29]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_POW_PLL_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0838[4:1]=4b'1100
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL1;
		val |= (0x0C<<SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL1 = val;

		//5000_0834[12]=1
		val = syson_s->SYSON_S_REG_ISP_PLL_CTRL0;
		val |= (1<<SYSON_S_SHIFT_REG_CK_EN_ISP);
		syson_s->SYSON_S_REG_ISP_PLL_CTRL0 = val;

		//5000_0804[0]=0
		val = syson_s->SYSON_S_REG_SYS_ISO_CTRL;
		HAL_CLEAR_BIT(val, SYSON_S_BIT_R3_SET_ISP);
		syson_s->SYSON_S_REG_SYS_ISO_CTRL = val;
		break;
	default:
		printf("ERROR clock setting\n\r");
		return;
	}

	start_time = hal_read_curtime_us();

	//polling pll ready
	while (!(syson_s->SYSON_S_REG_SYS_CLK_CTRL & SYSON_S_BIT_ISPPLL_RDY)) {
		if (hclk_timeout_chk(start_time) == 1) {
			printf("%s timeout\n\r", __func__);
			break;
		}

		hal_delay_us(1);
	}

	
}

void clk_prepare_enable(struct clk_rlx *clk)
{
	if (!clk) return;

	//clk->ops->prepare(clk);  //no prepare
#if defined(_SYSTEM_CONNECT_READY_)
	clk->ops->enable(clk);
#endif
	return;
}

void clk_disable_unprepare(struct clk_rlx *clk)
{
	if (!clk) return;

#if defined(_SYSTEM_CONNECT_READY_)
	clk->ops->disable(clk);
#endif
	//clk->ops->unprepare(clk);  //no unprepare
	return;
}

void clk_put(struct clk_rlx *clk)
{
	return;
}

struct clk_rlx *clk_get(const char *con_id)
{
	int i;
	struct clk_rlx *clk=NULL;

	/* mapping from "rts3915_base.dtsi"
			clock-names = "isp_clk", "inf_clk", "mipiout_clk", \
				       "hclk";
			clocks = <&clks RLX_CLK_ISP_CK>, \
				 <&clks RLX_CLK_MIPI_CK>, \
				 <&clks RLX_CLK_MIPITX>, \
				 <&clks RLX_CLK_SSOR_HCLK>;
	*/
	if (0==strcmp("isp_clk", con_id))
		return clks[RLX_CLK_ISP_CK];
	if (0==strcmp("inf_clk", con_id))
		return clks[RLX_CLK_MIPI_CK];
	if (0==strcmp("mipiout_clk", con_id))
		return clks[RLX_CLK_MIPITX];
	if (0==strcmp("hclk", con_id))
		return clks[RLX_CLK_SSOR_HCLK];


	for (i=0; i < (int)ARRAY_SIZE(clks); i++) {
		if (!clks[i]) continue;

		if ( clks[i]->name && (0==strcmp(clks[i]->name, con_id)) ) {
			clk = clks[i];
			break;
		}
	};
	return clk;
}

long clk_round_rate(struct clk_rlx *clk, u32 rate)
{
	//from drivers/clk/clk.c check and set rate in [min_rate, max_rate]
	return rate;
}
#if 0
static long rlx_gpll_round_rate(struct clk_rlx *clk, unsigned long rate,
			       unsigned long *prate)
{
	u32 parent_rate = *prate;
	int n = rate / parent_rate;
	unsigned long round_rate;
	u64 t = rate;

	t <<= 12;
	t += (parent_rate >> 1);
	bignumdiv((unsigned short *)&n, (unsigned short *)&t,
		(unsigned short *)&parent_rate);

	t = 0;
	bignummul((unsigned short *)&t, (unsigned short *)&parent_rate,
		(unsigned short *)&n);

	round_rate = t >> 12;

	printf("%s round:%lu\n", clk->name, round_rate);

	return round_rate;
}

static int rlx_gpll_set_rate(struct clk_rlx *clk, unsigned long rate,
			   unsigned long parent_rate)
{
	u64 t = rate;
	u32 n, f, reg;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	t <<= 12;
	t += (parent_rate >> 1);
	bignumdiv((unsigned short *)&n, (unsigned short *)&t,
		(unsigned short *)&parent_rate);

	f = n & 0xfff;
	n >>= 12;

	reg = (f<<9) + (n - 2);
	rts_pll_writel(reg,
		clk->clkreg + GPLL_SCCG_CFG1);
	xb2flush();
	return 0;
}

static int rlx_gpll_is_enabled(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 val;

	val = rts_pll_readl(clk->clkreg + GPLL_CTRL);

	return (val & GPLL_EN);
}

static int rlx_gpll_enable_clk(struct clk_rlx *clk)
{
	u32 reg;
	u32 time = 5000;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	reg = rts_pll_readl(clk->clkreg + GPLL_SCCG_CFG2);
	reg |= CMU_SSC_RSTB;
	rts_pll_writel(reg,
		clk->clkreg + GPLL_SCCG_CFG2);

	reg = rts_pll_readl(clk->clkreg + GPLL_SCCG_CFG3);
	reg |= CMU_SSC_EN;
	rts_pll_writel(reg,
		clk->clkreg + GPLL_SCCG_CFG3);

	reg = rts_pll_readl(clk->clkreg + GPLL_CTRL);
	reg |= PPOW_LDO;
	rts_pll_writel(reg, clk->clkreg + GPLL_CTRL);
	udelay(5);
	reg |= GPLL_EN;
	rts_pll_writel(reg, clk->clkreg + GPLL_CTRL);

	while (--time) {
		reg = rts_pll_readl(clk->clkreg + GPLL_STATUS);
		if (reg & SYSPLL_CK_RDY)
			break;
		udelay(1);
	}

	if (time == 0) {
		printf("%s enable failed\n", clk->name);
		return -ETIMEDOUT;
	}

	xb2flush();
	return 0;
}

static void rlx_gpll_disable_clk(struct clk_rlx *clk)
{
	u32 reg;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	reg = rts_pll_readl(clk->clkreg + GPLL_CTRL);
	reg &= ~GPLL_EN;
	rts_pll_writel(reg, clk->clkreg + GPLL_CTRL);
	reg &= ~PPOW_LDO;
	rts_pll_writel(reg, clk->clkreg + GPLL_CTRL);

	reg = rts_pll_readl(clk->clkreg + GPLL_SCCG_CFG0);
	reg &= ~REG_EN_SSC;
	rts_pll_writel(reg, clk->clkreg + GPLL_SCCG_CFG0);

	xb2flush();
}

static unsigned long rlx_gpll_recalc(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	u32 reg, n, f, rate;
	u64 t;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	reg = rts_pll_readl(clk->clkreg + GPLL_SCCG_CFG1);
	reg &= 0x1fffff;
	n = (reg & 0x1ff) + 2;
	f = reg >> 9;

	n <<= 12;
	n += f;

	bignummul((unsigned short *)&t, (unsigned short *)&parent_rate,
		(unsigned short *)&n);

	rate = (t >> 12);

	printf("%s prate: %u\n", clk->name, rate);

	return rate;
}

static const struct clk_ops rlx_gpll_ops = {
	.is_enabled = rlx_gpll_is_enabled,
	.enable = rlx_gpll_enable_clk,
	.disable = rlx_gpll_disable_clk,
	.round_rate = rlx_gpll_round_rate,
	.set_rate = rlx_gpll_set_rate,
	.recalc_rate = rlx_gpll_recalc,
};

int rts_gpll_ssc_config(struct clk_rlx *pll, u32 ppm, u32 freq)
{
	u32 tbase, rate, step, reg;
	u64 tl;
	u32 n1, f1, n2, t1, t2;

	struct clk_rlx *clk = pll;

	tbase = 25000000 / freq;
	tbase &= ~1;

	rate = clk_get_rate(pll);

	n1 = rts_pll_readl(clk->clkreg + GPLL_SCCG_CFG1);
	f1 = n1 >> 9;
	n1 &= 0x1ff;
	n1 += 2;

	n1 <<= 12;
	n1 += f1;

	t1 = 1000000 - ppm;
	bignummul((unsigned short *)&tl, (unsigned short *)&rate,
		(unsigned short *)&t1);

	t1 = 1000000;
	bignumdiv((unsigned short *)&t2, (unsigned short *)&tl,
		(unsigned short *)&t1);

	t1 = 25000000;
	tl = t2;
	tl <<= 12;
	tl += (t1 >> 1);
	bignumdiv((unsigned short *)&n2, (unsigned short *)&tl,
		(unsigned short *)&t1);

	n1 -= n2;

	step = (n1 << 4) / tbase;

	reg = rts_pll_readl(clk->clkreg
		+ GPLL_SCCG_CFG0);
	reg &= 0xfff000;
	reg |= (step << 12);
	reg |= REG_EN_SSC;

	rts_pll_writel(reg, clk->clkreg
		+ GPLL_SCCG_CFG0);

	return 0;
}
//EXPORT_SYMBOL_GPL(rts_gpll_ssc_config);

static int rlx_lvds_enable_clk(struct clk_rlx *clk)
{
	u32 reg;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	rts_lvds_pll_writel(0,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_21);
	reg = rts_lvds_pll_readl(clk->clkreg
			+ R_LVDS_ANA_TOP_CFG_20);
	reg &= 0xffffff;
	reg += 0x3000000;
	rts_lvds_pll_writel(reg,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_20);
	rts_lvds_pll_writel(0x1,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_8);

	rts_lvds_pll_writel(0x3f,
		clk->clkreg + R_POW_PIF_P1_TXL);

	xb2flush();
	return 0;
}

static void rlx_lvds_disable_clk(struct clk_rlx *clk)
{
	u32 reg;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	reg = rts_lvds_pll_readl(clk->clkreg
			+ R_POW_PIF_P1_TXL);
	reg &= ~0X3f;
	rts_lvds_pll_writel(reg,
		clk->clkreg + R_POW_PIF_P1_TXL);

	reg = rts_lvds_pll_readl(clk->clkreg
			+ R_LVDS_ANA_TOP_CFG_7);
	reg &= ~REG_PIF_EN_LV_LDO;
	rts_lvds_pll_writel(reg,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_7);

	reg = rts_lvds_pll_readl(clk->clkreg
			+ R_LVDS_ANA_TOP_CFG_8);
	reg &= ~REG_PIF_H_CMU_POW;
	rts_lvds_pll_writel(reg,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_8);

	xb2flush();
}

static int rlx_lvds_set_rate(struct clk_rlx *clk, unsigned long rate,
			   unsigned long parent_rate)
{
	u64 t = rate;
	u32 n, f, reg;

	//struct clk_rlx *clk = to_clk_rlx(hw);

	t <<= 12;
	t += (parent_rate >> 1);
	bignumdiv((unsigned short *)&n, (unsigned short *)&t,
		(unsigned short *)&parent_rate);

	f = n & 0xfff;
	n >>= 12;

	rts_lvds_pll_writel(0,
		clk->clkreg + R_LVDS_ANA_TOP_CFG_8);
	rts_lvds_pll_writel(0,
		clk->clkreg + R_POW_PIF_P1_TXL);

	reg = (f<<9) + (n - 2);
	rts_lvds_pll_writel(reg,
		clk->clkreg + LVDS_SSCG_CFG1);
	rts_lvds_pll_writel(1,
		clk->clkreg + LVDS_SSCG_CFG2);

	xb2flush();
	return 0;
}

static unsigned long rlx_lvds_recalc(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	u32 reg, n, f, rate;
	u64 t;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	reg = rts_lvds_pll_readl(clk->clkreg + LVDS_SSCG_CFG1);
	reg &= 0x1fffff;
	n = (reg & 0x1ff) + 2;
	f = reg >> 9;

	n <<= 12;
	n += f;

	bignummul((unsigned short *)&t, (unsigned short *)&parent_rate,
		(unsigned short *)&n);

	rate = (t >> 12);

	printf("%s prate: %u\n", clk->name, rate);

	return rate;
}

static const struct clk_ops rlx_lvds_pll_ops = {
	.is_enabled = rlx_gpll_is_enabled,
	.enable = rlx_lvds_enable_clk,
	.disable = rlx_lvds_disable_clk,
	.round_rate = rlx_gpll_round_rate,
	.set_rate = rlx_lvds_set_rate,
	.recalc_rate = rlx_lvds_recalc,
};

static int rlx_dma_enable_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = rts_clk_readl(clk->clkreg) & ~0x3;
	rts_clk_writel(reg, clk->clkreg);
	xb2flush();

	return 0;
}

static void rlx_dma_disable_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = rts_clk_readl(clk->clkreg) & ~0x3;
	reg |= 0x2;
	rts_clk_writel(reg, clk->clkreg);
	xb2flush();
}

static const struct clk_ops rlx_dma_clk_ops = {
	.enable = rlx_dma_enable_clk,
	.disable = rlx_dma_disable_clk,
};

static int usbphy_enable_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = rts_clk_readl(clk->clkreg);
	if (!strcmp(clk->name, "usbphy_host_ck"))
		reg |= USBPHY_HOST_CLK_EN;
	else if (!strcmp(clk->name, "usbphy_dev_ck"))
		reg |= USBPHY_DEV_CLK_EN;
	rts_clk_writel(reg, clk->clkreg);
	xb2flush();

	return 0;
}

static void usbphy_disable_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = rts_clk_readl(clk->clkreg);
	if (!strcmp(clk->name, "usbphy_host_ck"))
		reg &= ~USBPHY_HOST_CLK_EN;
	else if (!strcmp(clk->name, "usbphy_dev_ck"))
		reg &= ~USBPHY_DEV_CLK_EN;
	rts_clk_writel(reg, clk->clkreg);
	xb2flush();
}

static const struct clk_ops usbphy_divider_ops = {
	.enable = usbphy_enable_clk,
	.disable = usbphy_disable_clk,
};

static int rlx_decset_rate(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	u64 p = parent_rate;
	unsigned long divisor;
	unsigned long f, n;
	u32 divreg, reg, t;
	int i;
	//unsigned long  flags;

	//struct clk_rlx *clk = to_clk_rlx(hw);

	printf("setrate:%s p:%ld r:%ld\n", clk->name,
		parent_rate, rate);

	p <<= 6;
	p += (rate>>1);

	bignumdiv((unsigned short *)&divisor, (unsigned short *)&p,
		  (unsigned short *)&rate);

	for (i = 7; i >= 0; i--) {
		t = ((i + 1)  << 6);
		if (t <= divisor)
			break;
	}

	if (i < 0) {
		n = 0;
		f = 0;
	} else {
		n = i;
		f = 64 - (((n + 1) << 12) + (divisor >> 1)) / divisor;
	}

	divreg = (f << 16) | (i << 8);

	clk->rate = rate;

	clk->reg_v[clk->reg_i] &= ~0x3fff00;
	clk->reg_v[clk->reg_i] |= divreg;

	//spin_lock_irqsave(&clk_spinlock, flags);

	reg = rts_clk_readl(clk->clkreg) & ~0x3fffff;

	setchgbit(clk->clk_change);

	reg |= clk->reg_v[clk->reg_i];
	rts_clk_writel(reg, clk->clkreg);

	clrchgbit(clk->clk_change);
	xb2flush();

	//spin_unlock_irqrestore(&clk_spinlock, flags);

	printf("setrate: %s reg:%x\n", clk->name, reg);

	return 0;
}

static unsigned long rlx_decrecalc(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	u32 reg, n, f, rate;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u64 tm;
	u32 t;

	reg = rts_clk_readl(clk->clkreg) & 0xffff00;

	n = (reg & 0x700) >> 8;
	f = (reg & 0x3f0000) >> 16;

	printf("decrecalc0:%s %x %x %x %ld\n",
		clk->name, reg, n, f, parent_rate);

	tm = 0;
	t = 64 - f;
	bignummul((unsigned short *)&tm, (unsigned short *)&parent_rate,
		(unsigned short *)&t);

	tm += ((n + 1) << 5);
	t = (n + 1) << 6;
	rate = 0;
	bignumdiv((unsigned short *)&rate, (unsigned short *)&tm,
		(unsigned short *)&t);

	printf("decrecalc1:%s r:%u, %x\n", clk->name, rate, n);

	return rate + 1;
}

static long rlx_decround_rate(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	unsigned long divisor;
	unsigned long f = 0, n = 1, r = 0;
	int i;
	u32 p = *prate;
	u32 t;
	u64 tm;

	tm = p;
	tm <<= 6;
	tm += (rate>>1);

	bignumdiv((unsigned short *)&divisor, (unsigned short *)&tm,
		  (unsigned short *)&rate);

	for (i = 7; i >= 0; i--) {
		t = ((i + 1)  << 6);
			if (t <= divisor)
				break;
	}

	if (i < 0) {
		n = 0;
		f = 0;
	} else {
		n = i;
		f = 64 - (((n + 1) << 12) + (divisor >> 1)) / divisor;
	}

	printf("round:n %ld f %ld\n", n, f);

	tm = 0;
	t = 64 - f;
	bignummul((unsigned short *)&tm, (unsigned short *)&p,
		(unsigned short *)&t);

	tm += ((n + 1) << 5);
	t = (n + 1) << 6;
	r = 0;
	bignumdiv((unsigned short *)&r, (unsigned short *)&tm,
		(unsigned short *)&t);


	printf("%s round:%ld\n", clk->name, r);

	return r;
}
#endif
static int rlx_clk_is_enabled(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	//u32 val;

	//val = rts_clk_readl(clk->clkreg);

	//return (val & CLK_ENABLE);

	return 1;
}

static int rlx_enable_clk(struct clk_rlx *clk)
{
#if 0
	u32 time = 5000;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg = rts_clk_readl(clk->clkreg);

	reg |= CLK_ENABLE;
	rts_clk_writel(reg, clk->clkreg);

	while (--time) {
		if (rts_clk_readl(clk->clkreg) & CLK_ENABLE)
			break;
		udelay(1);
	}

	if (time == 0) {
		printf("%s enable failed\n", clk->name);
		return -ETIMEDOUT;
	}

	xb2flush();
#endif
	return 0;
}

static void rlx_disable_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	//u32 reg;

	//reg = rts_clk_readl(clk->clkreg);
	//reg &= ~CLK_ENABLE;
	//rts_clk_writel(reg, clk->clkreg);
	//xb2flush();
}
#if 0
static const struct clk_ops rlx_decdivider_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_decround_rate,
	.set_rate = rlx_decset_rate,
	.recalc_rate = rlx_decrecalc,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_parent(struct clk_rlx *clk, u8 field_val)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = clk->reg_v[clk->reg_i] & ~0x3;
	clk->reg_v[clk->reg_i] = (reg | field_val);

	return 0;
}

static u8 rlx_get_parent(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = clk->reg_v[clk->reg_i];
	reg &= 3;

	return reg;
}

static long rlx_round_rate(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long divisor = (parent_rate + rate / 2) / rate;
	int i;

	for (i = 0; i < (int)ARRAY_SIZE(div_array); i++)
		if (divisor <= div_array[i])
			break;

	if (i == ARRAY_SIZE(div_array))
		i--;

	divisor =  div_array[i];

	printf("round: %s %lu\n", clk->name, divisor);

	return parent_rate / divisor;
}

static int rlx_set_rate(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	u32 divreg;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 div = parent_rate / rate;
	u32 i;

	printf("setrate:%s div: %u p:%lu r:%lu\n", clk->name,
		 div, parent_rate, rate);

	clk->rate = rate;

	for (i = 0; i < ARRAY_SIZE(div_array); i++)
		if (div <= div_array[i])
			break;

	if (i == ARRAY_SIZE(div_array))
		i--;

	divreg = i << 2;

	printf("setrate:%s div:%u reg:%x\n", clk->name,
		div_array[i], divreg);

	clk->reg_v[clk->reg_i] &= ~0xfc;
	clk->reg_v[clk->reg_i] |= divreg;

	return 0;
}

static unsigned long rlx_recalc(struct clk_rlx *clk, unsigned long parent_rate)
{
	u32 div;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	div = clk->reg_v[clk->reg_i] & 0x1c;
	div >>= 2;
	div = div_array[div];

	printf("recalc:%s p: %lu, div: %u\n",
		clk->name, parent_rate, div);

	return parent_rate / div;
}

static const struct clk_ops rlx_divider_ops = {
	.round_rate = rlx_round_rate,
	.set_rate = rlx_set_rate,
	.recalc_rate = rlx_recalc,
	.set_parent = rlx_set_parent,
	.get_parent = rlx_get_parent,
};

static int rlx_set_rate_s(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	u32 divreg;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 div = parent_rate / rate;
	u32 i;
	u32 reg;
	//unsigned long flags;

	printf("setrate:%s div: %u p:%lu r:%lu\n", clk->name,
		 div, parent_rate, rate);

printf("%s rate:%d\n", __func__, (int)rate);
	clk->rate = rate;

	for (i = 0; i < ARRAY_SIZE(div_array); i++)
		if (div <= div_array[i])
			break;

	if (i == ARRAY_SIZE(div_array))
		i--;

	divreg = i << 2;

	printf("setrate:%s div:%u reg:%x\n", clk->name,
		div_array[i], divreg);

	clk->reg_v[clk->reg_i] &= ~0x1c;
	clk->reg_v[clk->reg_i] |= divreg;

	reg = rts_clk_readl(clk->clkreg) & ~0x1f;

	//spin_lock_irqsave(&clk_spinlock, flags);
	setchgbit(clk->clk_change);

	reg |= clk->reg_v[clk->reg_i];
	rts_clk_writel(reg, clk->clkreg);
	clrchgbit(clk->clk_change);
	//spin_unlock_irqrestore(&clk_spinlock, flags);

	return 0;
}

static unsigned long rlx_recalc_s(struct clk_rlx *clk,
		unsigned long parent_rate)
{
	u32 div;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	div = rts_clk_readl(clk->clkreg) & 0x1c;
	div >>= 2;
	div = div_array[div];

	printf("recalc_s:%s p: %lu, div: %u\n",
		clk->name, parent_rate, div);

	return parent_rate / div + 1;
}

static const struct clk_ops rlx_divider_ops_s = {
	.round_rate = rlx_round_rate,
	.set_rate = rlx_set_rate_s,
	.recalc_rate = rlx_recalc_s,
	.set_parent = rlx_set_parent,
	.get_parent = rlx_get_parent,
};

static long rlx_round_rate_l(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long divisor = (parent_rate + rate / 2) / rate;
	int i;

	for (i = 0; i < (int)ARRAY_SIZE(div_array_long); i++)
		if (divisor <= div_array_long[i])
			break;

	if (i == ARRAY_SIZE(div_array_long))
		i--;

	divisor =  div_array_long[i];

	printf("round: %s %lu\n", clk->name, divisor);

	return parent_rate / divisor;
}

static int rlx_set_rate_lcdc_div(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	u32 divreg;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 div = parent_rate / rate;
	u32 i;
	u32 reg;
	//unsigned long flags;

	printf("setrate:%s div: %u p:%lu r:%lu\n", clk->name,
		 div, parent_rate, rate);

printf("%s rate:%d\n", __func__, (int)rate);
	clk->rate = rate;

	for (i = 0; i < ARRAY_SIZE(div_array); i++)
		if (div <= div_array[i])
			break;

	if (i == ARRAY_SIZE(div_array))
		i--;

	divreg = i << 2;

	printf("setrate:%s div:%u reg:%x\n", clk->name,
		div_array[i], divreg);

	clk->reg_v[clk->reg_i] &= ~0x3c;
	clk->reg_v[clk->reg_i] |= divreg;

	reg = rts_lvds_pll_readl(clk->clkreg) & ~0x3f;

	//spin_lock_irqsave(&clk_spinlock, flags);
	reg |= clk->reg_v[clk->reg_i];
	rts_lvds_pll_writel(reg, clk->clkreg);
	//spin_unlock_irqrestore(&clk_spinlock, flags);

	return 0;
}

static unsigned long rlx_recalc_lcdc_div(struct clk_rlx *clk,
		unsigned long parent_rate)
{
	u32 div;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	div = rts_lvds_pll_readl(clk->clkreg) & 0x3c;
	div >>= 2;
	div = div_array[div];

	printf("recalc_lcdc_div:%s p: %lu, div: %u\n",
		clk->name, parent_rate, div);

	return parent_rate / div + 1;
}

static const struct clk_ops rlx_divider_lcdc = {
	.round_rate = rlx_round_rate_l,
	.set_rate = rlx_set_rate_lcdc_div,
	.recalc_rate = rlx_recalc_lcdc_div,
	.set_parent = rlx_set_parent,
	.get_parent = rlx_get_parent,
};

static long rlx_round_rate_c(struct clk_rlx *clk, unsigned long rate,
		unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long divisor = (parent_rate + rate / 2) / rate;

	if (divisor > 254)
		divisor = 254;
	else if (divisor == 0)
		divisor = 1;

	if (divisor != 1) {
		divisor >>= 1;
		divisor <<= 1;
	}

	printf("round: %s %lu\n", clk->name, divisor);

	return parent_rate / divisor;
}

static int rlx_set_rate_c(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	u32 reg;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 div = (parent_rate + (rate >> 1)) / rate;
	//unsigned long flags;


	printf("setrate:%s div: %u p:%lu r:%lu\n", clk->name,
		div, parent_rate, rate);

	if (div > 254)
		div = 254;
	else if (div == 0)
		div = 1;

printf("%s rate:%d\n", __func__, (int)rate);
	clk->rate = rate;

	if (div != 1)
		div >>= 1;
	else
		div = 0;

	clk->reg_v[clk->reg_i] &= ~0x1fc;
	clk->reg_v[clk->reg_i] |= (div << 2);

	//spin_lock_irqsave(&clk_spinlock, flags);
	reg = rts_clk_readl(clk->clkreg) & ~0x1ff;

	setchgbit(clk->clk_change);

	reg |= clk->reg_v[clk->reg_i];
	rts_clk_writel(reg, clk->clkreg);
	clrchgbit(clk->clk_change);

	xb2flush();
	//spin_unlock_irqrestore(&clk_spinlock, flags);

	return 0;
}

static unsigned long rlx_recalc_c(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	u32 div;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	div = rts_clk_readl(clk->clkreg) & 0x1fc;
	div >>= 2;
	div <<= 1;

	if (div == 0)
		div++;

	printf("recalc_c:%s p: %lu, div: %u\n",
		clk->name, parent_rate, div);

	return (parent_rate + (div >> 1)) / div + 1;
}

static const struct clk_ops rlx_divider_ops_c = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_c,
	.set_rate = rlx_set_rate_c,
	.set_parent = rlx_set_parent,
	.get_parent = rlx_get_parent,
	.recalc_rate = rlx_recalc_c,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_l(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	u32 divreg;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 div = parent_rate / rate;
	u32 i;
	u32 reg;
	//unsigned long flags;

	printf("setrate:%s div: %u p:%lu r:%lu\n", clk->name,
		 div, parent_rate, rate);

printf("%s rate:%d\n", __func__, (int)rate);
	clk->rate = rate;

	for (i = 0; i < ARRAY_SIZE(div_array_long); i++)
		if (div <= div_array_long[i])
			break;

	if (i == ARRAY_SIZE(div_array_long))
		i--;

	divreg = i << 2;

	printf("setrate:%s div:%u reg:%x\n", clk->name,
		div_array_long[i], divreg);

	clk->reg_v[clk->reg_i] &= ~0x3c;
	clk->reg_v[clk->reg_i] |= divreg;

	reg = rts_clk_readl(clk->clkreg) & ~0x3f;

	//spin_lock_irqsave(&clk_spinlock, flags);
	setchgbit(clk->clk_change);

	reg |= clk->reg_v[clk->reg_i];
	rts_clk_writel(reg, clk->clkreg);
	clrchgbit(clk->clk_change);
	//spin_unlock_irqrestore(&clk_spinlock, flags);

	return 0;
}

static unsigned long rlx_recalc_l(struct clk_rlx *clk,
		unsigned long parent_rate)
{
	u32 div;
	//struct clk_rlx *clk = to_clk_rlx(hw);

	div = rts_clk_readl(clk->clkreg) & 0x3c;
	div >>= 2;
	div = div_array_long[div];

	printf("recalc_l:%s p: %lu, div: %u\n",
		clk->name, parent_rate, div);

	return parent_rate / div + 1;
}

static const struct clk_ops rlx_divider_ops_l = {
	.round_rate = rlx_round_rate_l,
	.set_rate = rlx_set_rate_l,
	.recalc_rate = rlx_recalc_l,
	.set_parent = rlx_set_parent,
	.get_parent = rlx_get_parent,
};

static int rlx_set_rate_cpu(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("cpu_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("cpu_ck_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 800000000:
		clk0 = clk_get("gpll1");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 800000000);
		clk_set_rate(clk2, 800000000);
		break;
	case 700000000:
		clk0 = clk_get("gpll1");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 800000000);
		clk_set_rate(clk2, 700000000);
		break;
	case 600000000:
		clk0 = clk_get("gpll1");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 800000000);
		clk_set_rate(clk2, 600000000);
		break;
	case 500000000:
		clk0 = clk_get("gpll0");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 500000000);
		clk_set_rate(clk2, 500000000);
		break;
	case 480000000:
		clk0 = clk_get("usb_pll");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 480000000);
		clk_set_rate(clk2, 480000000);
		break;
	case 400000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 400000000);
		break;
	case 300000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 300000000);
		break;
	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		clk_set_rate(clk2, 200000000);
		break;
	case 160000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 160000000);
		clk_set_rate(clk2, 160000000);
		break;
	case 50000000:
		clk0 = clk_get("gpll0");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 250000000);
		clk_set_rate(clk2, 50000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_cpu(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate = 0;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("cpu_ck_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);
	rate = clk_get_rate(clk0) - 1;
printf("%s rate:%d\n", __func__, (int)rate);
	clk_put(clk0);

	return rate;
}

static long rlx_round_rate_v(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	return rate;
}

static const struct clk_ops rlx_clk_cpu_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_cpu,
	.recalc_rate = rlx_recalc_cpu,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_jpeg(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("jpeg_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("jpeg_ck_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		clk_set_rate(clk0, 200000000);
		break;
	case 166000000:
		clk0 = clk_get("gpll0_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 166666666);
		clk_set_rate(clk0, 166666666);
		break;
	case 160000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 160000000);
		clk_set_rate(clk0, 160000000);
		break;
	case 125000000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 125000000);
		clk_set_rate(clk0, 125000000);
		break;
	case 120000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 120000000);
		clk_set_rate(clk0, 120000000);
		break;
	case 100000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 100000000);
		clk_set_rate(clk2, 100000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_jpeg(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 30000000;

	clk0 = clk_get("jpeg_ck_dec");
	if (IS_ERR(clk0))
		return -EINVAL;

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_jpeg_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_jpeg,
	.recalc_rate = rlx_recalc_jpeg,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_bus(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("bus_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("bus_ck_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 60000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 60000000);
		clk_set_rate(clk2, 60000000);
		break;
	case 100000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 100000000);
		clk_set_rate(clk2, 100000000);
		break;
	case 120000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 120000000);
		clk_set_rate(clk2, 120000000);
		break;
	case 125000000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 125000000);
		clk_set_rate(clk2, 125000000);
		break;
	case 114000000:
		clk0 = clk_get("gpll1_7");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 114000000);
		clk_set_rate(clk2, 114000000);
		break;

	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_bus(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 30000000;

	clk0 = clk_get("bus_ck_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_bus_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_bus,
	.recalc_rate = rlx_recalc_bus,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_dram(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("dram_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("dram_ck_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 240000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 240000000);
		clk_set_rate(clk2, 240000000);
		break;
	case 500000000:
		clk0 = clk_get("gpll0");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 500000000);
		clk_set_rate(clk2, 500000000);
		break;
	case 480000000:
		clk0 = clk_get("usb_pll");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 480000000);
		clk_set_rate(clk2, 480000000);
		break;
	case 400000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 400000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_dram(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 60000000;

	clk0 = clk_get("dram_ck_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_dram_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_dram,
	.recalc_rate = rlx_recalc_dram,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};
#endif

#define ISP_SYS 35
#define MIPI_SYS 36

void hal_voe_sys_set_clk(uint8_t id, uint8_t sel_val)
{
	SYSON_S_TypeDef *syson_s = SYSON_S;

	volatile uint32_t val;
	switch (id) {

	case ISP_SYS:
		val = syson_s->SYSON_S_REG_SYS_ISP_CTRL;
		val &= ~SYSON_S_MASK_SYS_ISP_SRC_SEL;
		val |= sel_val << SYSON_S_SHIFT_SYS_ISP_SRC_SEL;
		syson_s->SYSON_S_REG_SYS_ISP_CTRL = val;
#ifdef _DEBUG_CLK_
		printf("set isp clk %d \n", sel_val);
#endif
		break;
	// 0: 200Mhz /s4, 1: 166Mhz /c5 2: 125Mhz /c2
	// 3: 100Mhz /s5, 4: 83Mhz /c6

	case MIPI_SYS:
		val = syson_s->SYSON_S_REG_SYS_ISP_CTRL;
		val &= ~SYSON_S_MASK_SYS_MIPI_SRC_SEL;
		val |= sel_val << SYSON_S_SHIFT_SYS_MIPI_SRC_SEL;
		syson_s->SYSON_S_REG_SYS_ISP_CTRL = val;
#ifdef _DEBUG_CLK_
		printf("set mipi clk %d \n", sel_val);
#endif
		break;
	// 0: 250Mhz /c1, 1: 200Mhz /s4, 2: 166Mhz /c5
	// 3: 125Mhz /c2, 4: 100Mhz /s5, 5: 83Mhz /c6
	default:
		break;
	}
}

#define ISP_CLK_SIZE 5

static u32 isp_clock_level = 0;
static u32 mipi_clock_level = 0;
//enum video_clk_type {
//	VIDEO_CLK_ISP = 0,
//	VIDEO_CLK_MIPI = 1,
//};


int hal_voe_set_clock_level(u32 isp_clk_level, u32 mipi_clk_level)
{
	isp_clock_level = isp_clk_level;
	mipi_clock_level = mipi_clk_level;

	return 0;
}
static long rlx_round_rate_isp(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	unsigned long round_rate;
	unsigned long rates_500MHz[] = {83333333, 100000000, 125000000, 166666666, 200000000};
	unsigned long rates_400MHz[] = {66666666, 100000000, 100000000, 133333333, 200000000};
	unsigned long rates_300MHz[] = {50000000, 75000000, 100000000, 100000000, 200000000};
	int i;
	unsigned long *p_clk;
	uint32_t val = (HAL_READ32(0x40009000, 0xFC) & ((u32)0x00000003 << 3)) >> 3;

	if (val == 0)
		p_clk = &(rates_500MHz[0]);
	else if (val == 1)
		p_clk = &(rates_400MHz[0]);
	else
		p_clk = &(rates_300MHz[0]);

	for (i = 0; i < ISP_CLK_SIZE; i++) {
		if (rate <= p_clk[i])
			break;
	}

	i += isp_clock_level;
	
	if (i >= ISP_CLK_SIZE)
		i = ISP_CLK_SIZE - 1;
	//i = ISP_CLK_SIZE - 1;   // for test vHDR SC2310

	round_rate = p_clk[i];
#ifdef _CLK_LOG_
	printf("isp rate %lu round: %lu\n", rate, round_rate);
#endif
	return round_rate;
}

static int rlx_set_rate_isp(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	int ret = 0;
				   
	unsigned long rates_500MHz[] = {200000000, 166666666, 125000000, 100000000, 83333333};
	unsigned long rates_400MHz[] = {200000000, 133333333, 100000000, 100000000, 66666666};
	unsigned long rates_300MHz[] = {200000000, 100000000, 75000000, 100000000, 50000000};
	int i;
	unsigned long *p_clk;
	uint32_t val = (HAL_READ32(0x40009000, 0xFC) & ((u32)0x00000003 << 3)) >> 3;

	if (val == 0)
		p_clk = &(rates_500MHz[0]);
	else if (val == 1)
		p_clk = &(rates_400MHz[0]);
	else
		p_clk = &(rates_300MHz[0]);

	for (i = 0; i < ISP_CLK_SIZE; i++) {
		if (rate == p_clk[i]) {
			hal_voe_sys_set_clk(ISP_SYS, i);//ISP_SYS
			break;
		}
	}
   
	if (i == ISP_CLK_SIZE) {
		 printf("%s %ld not supported yet\n", clk->name, rate);
		ret = -EINVAL;
	}
				   
	clk->rate = rate;
				   
	return ret;

}

static unsigned long rlx_recalc_isp(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	if (clk_platform_type & TYPE_FPGA)
		return 48000000;

	return clk->rate;
}

static const struct clk_ops rlx_clk_isp_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_isp,
	.set_rate = rlx_set_rate_isp,
	.recalc_rate = rlx_recalc_isp,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};
#define MIPI_CLK_SIZE 6
static long rlx_round_rate_mipi(struct clk_rlx *clk, unsigned long rate,
			   unsigned long *prate)
{
	unsigned long round_rate;
	unsigned long rates_500MHz[] = {83333333, 100000000, 125000000, 166666666, 200000000, 250000000};
	unsigned long rates_400MHz[] = {66666666, 100000000, 100000000, 133333333, 200000000, 200000000};
	unsigned long rates_300MHz[] = {50000000, 75000000, 100000000, 100000000, 150000000, 200000000};
	unsigned long *p_clk;
	int i;
	uint32_t val = (HAL_READ32(0x40009000, 0xFC) & ((u32)0x00000003 << 3)) >> 3;

	if (val == 0)
		p_clk = &(rates_500MHz[0]);
	else if (val == 1)
		p_clk = &(rates_400MHz[0]);
	else
		p_clk = &(rates_300MHz[0]);

	for (i = 0; i < MIPI_CLK_SIZE; i++) {
		if (rate <= p_clk[i])
			break;
	}

	i += mipi_clock_level;

	if (i >= MIPI_CLK_SIZE)
		i = MIPI_CLK_SIZE - 1;

	round_rate = p_clk[i];
#ifdef _CLK_LOG_
	printf("mipi rate %lu round: %lu\n", rate, round_rate);
#endif
	return round_rate;
}

static int rlx_set_rate_mipi(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	int ret = 0;
	
	unsigned long rates_500MHz[] = {250000000, 200000000, 166666666, 125000000, 100000000, 83333333};
	unsigned long rates_400MHz[] = {200000000, 200000000, 133333333, 100000000, 100000000, 66666666};
	unsigned long rates_300MHz[] = {150000000, 200000000, 100000000, 75000000, 100000000, 50000000};
	unsigned long *p_clk;
	int i;
	uint32_t val = (HAL_READ32(0x40009000, 0xFC) & ((u32)0x00000003 << 3)) >> 3;

	if (val == 0)
		p_clk = &(rates_500MHz[0]);
	else if (val == 1)
		p_clk = &(rates_400MHz[0]);
	else
		p_clk = &(rates_300MHz[0]);


	for (i = 0; i < MIPI_CLK_SIZE; i++) {
		if (rate == p_clk[i]) {
			hal_voe_sys_set_clk(MIPI_SYS, i);//MIPI_SYS
#ifdef _CLK_LOG_
			printf("rlx_set_rate_mipi: %u\n\r", p_clk[i]);
#endif
			break;
		}
	}
	
	if (i == MIPI_CLK_SIZE) {
		printf("%s %ld not supported yet\n", clk->name, rate);
		ret = -EINVAL;
	}

	clk->rate = rate;

	return ret;
}

static unsigned long rlx_recalc_mipi(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	if (clk_platform_type & TYPE_FPGA)
		return 60000000;

	return clk->rate;
}

static const struct clk_ops rlx_clk_mipi_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_mipi,
	.set_rate = rlx_set_rate_mipi,
	.recalc_rate = rlx_recalc_mipi,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

#if 0

static int rlx_set_rate_i2c(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("i2c_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 96000000:
		clk0 = clk_get("usb_pll_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 96000000);
		break;
	case 80000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 80000000);
		break;
	case 50000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 50000000);
		break;
	case 40000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 40000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_i2c(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("i2c_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);
	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_i2c_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_i2c,
	.recalc_rate = rlx_recalc_i2c,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_xb2(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("xb2_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 60000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 60000000);
		break;
	case 30000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 30000000);
		break;
	case 62500000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 62500000);
		break;
	case 50000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 50000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_xb2(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("xb2_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_xb2_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_xb2,
	.recalc_rate = rlx_recalc_xb2,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_mipitx_low(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("mipitx_lowdiv");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 240000000:
		clk0 = clk_get("usb_pll");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 240000000);
		break;
	case 250000000:
		clk0 = clk_get("gpll0");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 250000000);
		break;
	case 160000000:
		clk0 = clk_get("usb_pll");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 160000000);
		break;
	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static long rlx_round_rate_mipitx(struct clk_rlx *clk, unsigned long rate,
			unsigned long *prate)
{
	unsigned long round_rate;
	unsigned long rates[] = {160000000, 200000000,
					240000000, 250000000};
	int i;

	for (i = 0; i < (int)ARRAY_SIZE(rates); i++) {
		if (rate <= rates[i])
			break;
	}

	if (i == (int)ARRAY_SIZE(div_array))
		i--;

	round_rate = rates[i];

	printf("round: %s %lu\n", clk->name, round_rate);

	return round_rate;
}

static unsigned long rlx_recalc_mipitx_low(struct clk_rlx *clk,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("mipitx_lowdiv");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_mipitx_low_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_mipitx,
	.set_rate = rlx_set_rate_mipitx_low,
	.recalc_rate = rlx_recalc_mipitx_low,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_lcdc(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;
	u32 t, n;
	u32 murate = 7 * rate;
	struct clk_rlx *lcd_ck;

	lcd_ck = clk_get("lcdc_dram_ck");
	clk_prepare_enable(lcd_ck);
	clk_put(lcd_ck);

	clk1 = clk_get("lcdc_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk0 = clk_get("lvds_pll_7");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);
	clk_set_parent(clk1, clk0);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 68935680:
	case 33264000:
	case 29232000:
		clk2 = clk_get("lvds_pll");
		if (IS_ERR(clk2))
			return PTR_ERR(clk2);
		t = clk_round_rate(clk2, murate);
		clk_set_rate(clk2, t);
		clk_prepare_enable(clk2);
		clk_put(clk2);
		clk_set_rate(clk1, t/7);
		break;
	case 9053892:
		n = 400000000 / murate;
		n = n + (4 - n % 4);
		t = murate * n;
		clk2 = clk_get("lvds_pll");
		if (IS_ERR(clk2))
			return PTR_ERR(clk2);
		clk_set_rate(clk2, t);
		clk_prepare_enable(clk2);
		clk_put(clk2);
		clk_set_rate(clk1, clk_round_rate(clk1, rate));
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	return ret;
}

static unsigned long rlx_recalc_lcdc(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("lcdc_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static int rlx_enable_lcdc_clk(struct clk_rlx *clk)
{
	u32 time = 5000;
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg = rts_lvds_pll_readl(clk->clkreg);

	reg |= CLK_ENABLE;
	rts_lvds_pll_writel(reg, clk->clkreg);

	while (--time) {
		if (rts_lvds_pll_readl(clk->clkreg) & CLK_ENABLE)
			break;
		udelay(1);
	}

	if (time == 0) {
		printf("%s enable failed\n", clk->name);
		return -ETIMEDOUT;
	}

	xb2flush();
	return 0;
}

static void rlx_disable_lcdc_clk(struct clk_rlx *clk)
{
	//struct clk_rlx *clk = to_clk_rlx(hw);
	u32 reg;

	reg = rts_lvds_pll_readl(clk->clkreg);
	reg &= ~CLK_ENABLE;
	rts_lvds_pll_writel(reg, clk->clkreg);
	xb2flush();
}

static const struct clk_ops rlx_clk_lcdc_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_lcdc,
	.recalc_rate = rlx_recalc_lcdc,
	.enable = rlx_enable_lcdc_clk,
	.disable = rlx_disable_lcdc_clk,
};

static int rlx_set_rate_uart(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("uart_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 24000000:
		clk0 = clk_get("usb_pll_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 24000000);
		break;
	case 25000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 25000000);
		break;
	case 40000000:
		clk0 = clk_get("gpll1_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 40000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_uart(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 24000000;

	clk0 = clk_get("uart_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_uart_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_uart,
	.recalc_rate = rlx_recalc_uart,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_i2s(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;
	u32 n, t;

	n = 400000000 / rate;
	n = n + (4 - n % 4);
	t = rate * n;

	clk0 = clk_get("gpll3");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);
	clk_set_rate(clk0, t);
	clk_prepare_enable(clk0);
	clk_put(clk0);

	clk1 = clk_get("gpll3_2");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("i2s_ck_div");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

printf("%s rate:%d\n", __func__, (int)rate);
	clk_set_parent(clk2, clk1);
	clk_set_rate(clk2, rate);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_i2s(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("i2s_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_i2s_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_i2s,
	.recalc_rate = rlx_recalc_i2s,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_spdif(struct clk_rlx *clk, unsigned long rate,
			unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;
	u32 n, t;

	n = 400000000 / rate;
	n = n + (4 - n % 4);
	t = rate * n;

	clk0 = clk_get("gpll3");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);
	clk_set_rate(clk0, t);
	clk_prepare_enable(clk0);
	clk_put(clk0);

	clk1 = clk_get("gpll3_2");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("spdif_ck_div");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

printf("%s rate:%d\n", __func__, (int)rate);
	clk_set_parent(clk2, clk1);
	clk_set_rate(clk2, rate);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_spdif(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("spdif_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_spdif_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_spdif,
	.recalc_rate = rlx_recalc_spdif,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_codec(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("codec_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 80000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 80000000);
		break;
	case 83000000:
		clk0 = clk_get("gpll0_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 83333333);
		break;
	case 96000000:
		clk0 = clk_get("usb_pll_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 96000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_codec(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 96000000;

	clk0 = clk_get("codec_ck_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_codec_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_codec,
	.recalc_rate = rlx_recalc_codec,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_h265_clk(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	int ret = 0;

printf("%s rate:%d\n", __func__, (int)rate);
	if (rate != 160000000) {
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	return ret;
}

static unsigned long rlx_recalc_h265_clk(struct clk_rlx *clk,
	unsigned long parent_rate)
{
printf("%s rate:160000000\n", __func__);

	return 160000000;
}

static int rlx_enable_h265_clk(struct clk_rlx *clk)
{
	u32 reg;
	u32 addr;

	addr = H265_ACLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg |= CLK_ENABLE;
	rts_clk_writel(reg, addr);
	udelay(1);

	addr = H265_BCLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg |= CLK_ENABLE;
	rts_clk_writel(reg, addr);
	udelay(1);

	addr = H265_CCLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg |= CLK_ENABLE;
	rts_clk_writel(reg, addr);
	udelay(1);

	xb2flush();
	return 0;
}

static void rlx_disable_h265_clk(struct clk_rlx *clk)
{
	u32 addr;
	u32 reg;

	addr = H265_ACLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg &= ~CLK_ENABLE;
	rts_clk_writel(reg, addr);

	addr = H265_BCLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg &= ~CLK_ENABLE;
	rts_clk_writel(reg, addr);

	addr = H265_CCLK_CFG_R;
	reg = rts_clk_readl(addr);
	reg &= ~CLK_ENABLE;
	rts_clk_writel(reg, addr);
	xb2flush();
}

static const struct clk_ops rlx_clk_h265_clk_ops = {
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_h265_clk,
	.recalc_rate = rlx_recalc_h265_clk,
	.enable = rlx_enable_h265_clk,
	.disable = rlx_disable_h265_clk,
};

static unsigned long rlx_recalc_h265_aclk(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("dram_ck");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) / 2;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_h265_aclk_ops = {
	.recalc_rate = rlx_recalc_h265_aclk,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_h265_bclk(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("h265_bclk_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("h265_bclk_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 120000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 120000000);
		clk_set_rate(clk2, 120000000);
		break;
	case 240000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 240000000);
		clk_set_rate(clk2, 240000000);
		break;
	case 250000000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 250000000);
		clk_set_rate(clk2, 250000000);
		break;
	case 160000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 160000000);
		clk_set_rate(clk2, 160000000);
		break;
	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		clk_set_rate(clk2, 200000000);
		break;
	case 400000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 400000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_h265_bclk(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("h265_bclk_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_h265_bclk_ops = {
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_h265_bclk,
	.recalc_rate = rlx_recalc_h265_bclk,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_h265_cclk(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("h265_cclk_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("h265_cclk_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 120000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 120000000);
		clk_set_rate(clk2, 120000000);
		break;

	case 240000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 240000000);
		clk_set_rate(clk2, 240000000);
		break;

	case 250000000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 250000000);
		clk_set_rate(clk2, 250000000);
		break;

	case 160000000:
		clk0 = clk_get("usb_pll_3");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 160000000);
		clk_set_rate(clk2, 160000000);
		break;

	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		clk_set_rate(clk2, 200000000);
		break;

	case 400000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 400000000);
		break;

	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_h265_cclk(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("h265_cclk_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_h265_cclk_ops = {
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_h265_cclk,
	.recalc_rate = rlx_recalc_h265_cclk,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_hclk(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("ssor_hclk_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 24000000:
		clk0 = clk_get("usb_pll_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 24000000);
		break;
	case 25000000:
		clk0 = clk_get("gpll0_5");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 25000000);
		break;
	case 37125000:
		clk0 = clk_get("gpll2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);
		clk_set_rate(clk0, 594000000);
		clk_prepare_enable(clk0);
		clk_put(clk0);

		clk0 = clk_get("gpll2_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk1 = clk_get("ssor_hclk_div");
		if (IS_ERR(clk1))
			return PTR_ERR(clk1);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 37125000);
		break;
	case 74250000:
		clk0 = clk_get("gpll2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);
		clk_set_rate(clk0, 594000000);
		clk_prepare_enable(clk0);
		clk_put(clk0);

		clk0 = clk_get("gpll2_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk1 = clk_get("ssor_hclk_div");
		if (IS_ERR(clk1))
			return PTR_ERR(clk1);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 74250000);
		break;
	case 27000000:
		clk0 = clk_get("gpll2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);
		clk_set_rate(clk0, 432000000);
		clk_prepare_enable(clk0);
		clk_put(clk0);

		clk0 = clk_get("gpll2_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk1 = clk_get("ssor_hclk_div");
		if (IS_ERR(clk1))
			return PTR_ERR(clk1);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 27000000);
		break;
	case 54000000:
		clk0 = clk_get("gpll2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);
		clk_set_rate(clk0, 432000000);
		clk_prepare_enable(clk0);
		clk_put(clk0);

		clk0 = clk_get("gpll2_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk1 = clk_get("ssor_hclk_div");
		if (IS_ERR(clk1))
			return PTR_ERR(clk1);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 54000000);
		break;

	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_hclk(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 24000000;

	clk0 = clk_get("ssor_hclk_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_hclk_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_hclk,
	.recalc_rate = rlx_recalc_hclk,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static const struct clk_ops rlx_clk_gate_ops = {
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
	.is_enabled = rlx_clk_is_enabled,
};

static int rlx_set_rate_nncore(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1, *clk2;
	int ret = 0;

	clk1 = clk_get("nncore_ck_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

	clk2 = clk_get("nncore_ck_dec");
	if (IS_ERR(clk2))
		return PTR_ERR(clk2);

	clk_set_parent(clk2, clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 100000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 100000000);
		clk_set_rate(clk2, 100000000);
		break;
	case 120000000:
		clk0 = clk_get("usb_pll_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 120000000);
		clk_set_rate(clk2, 120000000);
		break;
	case 200000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 200000000);
		clk_set_rate(clk2, 200000000);
		break;
	case 300000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 300000000);
		break;
	case 400000000:
		clk0 = clk_get("gpll1_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 400000000);
		clk_set_rate(clk2, 400000000);
		break;
	case 480000000:
		clk0 = clk_get("usb_pll");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 480000000);
		clk_set_rate(clk2, 480000000);
		break;
	case 500000000:
		clk0 = clk_get("gpll0");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);

		clk_set_rate(clk1, 500000000);
		clk_set_rate(clk2, 500000000);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);
	clk_put(clk2);

	return ret;
}

static unsigned long rlx_recalc_nncore(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	if (clk_platform_type & TYPE_FPGA)
		return 50000000;

	clk0 = clk_get("nncore_ck_dec");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0) - 1;

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_nncore_ops = {
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_nncore,
	.recalc_rate = rlx_recalc_nncore,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

static int rlx_set_rate_macbypass(struct clk_rlx *clk, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rlx *clk0, *clk1;
	int ret = 0;

	clk1 = clk_get("macbypass_div");
	if (IS_ERR(clk1))
		return PTR_ERR(clk1);

printf("%s rate:%d\n", __func__, (int)rate);
	switch (rate) {
	case 83000000:
		clk0 = clk_get("gpll0_2");
		if (IS_ERR(clk0))
			return PTR_ERR(clk0);

		clk_set_parent(clk1, clk0);
		clk_set_rate(clk1, 83333333);
		break;
	default:
		printf("%s %ld not supported yet\n",
			clk->name, rate);
		ret = -EINVAL;
	}

	clk_put(clk0);
	clk_put(clk1);

	return ret;
}

static unsigned long rlx_recalc_macbypass(struct clk_rlx *clk,
	unsigned long parent_rate)
{
	struct clk_rlx *clk0;
	u32 rate;

	clk0 = clk_get("macbypass_div");
	if (IS_ERR(clk0))
		return PTR_ERR(clk0);

	rate = clk_get_rate(clk0);

printf("%s rate:%d\n", __func__, (int)rate);

	clk_put(clk0);

	return rate;
}

static const struct clk_ops rlx_clk_macbypass_ops = {
	.is_enabled = rlx_clk_is_enabled,
	.round_rate = rlx_round_rate_v,
	.set_rate = rlx_set_rate_macbypass,
	.recalc_rate = rlx_recalc_macbypass,
	.enable = rlx_enable_clk,
	.disable = rlx_disable_clk,
};

DEFINE_CLK_RLX(gpll0, rlx_root_parent_names,
	rlx_gpll_ops, BSP_CLK_GPLL0_BASE_R, 0);
DEFINE_CLK_RLX(gpll1, rlx_root_parent_names,
	rlx_gpll_ops, BSP_CLK_GPLL1_BASE_R, 0);
DEFINE_CLK_RLX(gpll2, rlx_root_parent_names,
	rlx_gpll_ops, BSP_CLK_GPLL2_BASE_R, 0);
DEFINE_CLK_RLX(gpll3, rlx_root_parent_names,
	rlx_gpll_ops, BSP_CLK_GPLL3_BASE_R, 0);

DEFINE_CLK_RLX(lvds_pll, rlx_root_parent_names,
	rlx_lvds_pll_ops, LVDS_BASE_RF, 0);

DEFINE_CLK_RLX(dma_ck, rlx_root_parent_names,
	rlx_dma_clk_ops, DMA_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(usbphy_host_ck, rlx_root_parent_names,
	usbphy_divider_ops, USBPHY_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(usbphy_dev_ck, rlx_root_parent_names,
	usbphy_divider_ops, USBPHY_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(ethernet_ck, rlx_root_parent_names,
	rlx_clk_gate_ops, ETHERNET_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(cpu_ck_div, rlx_names_cpu_div,
	rlx_divider_ops, CPU_CLK_CFG_R, CPU_CK_CHANGE);
DEFINE_CLK_RLX(cpu_ck_dec, rlx_names_cpu_dec,
	rlx_decdivider_ops, CPU_CLK_CFG_R, CPU_CK_CHANGE);
DEFINE_CLK_RLX(cpu_ck, rlx_names_v,
	rlx_clk_cpu_ops, CPU_CLK_CFG_R, CPU_CK_CHANGE);

DEFINE_CLK_RLX(jpeg_ck_div, rlx_names_jpeg_div,
	rlx_divider_ops, JPEG_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(jpeg_ck_dec, rlx_names_jpeg_dec,
	rlx_decdivider_ops, JPEG_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(jpeg_ck, rlx_names_v,
	rlx_clk_jpeg_ops, JPEG_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(bus_ck_div,	rlx_names_bus_div,
	rlx_divider_ops, BUS_CLK_CFG_R, BUS_CK_CHANGE);
DEFINE_CLK_RLX(bus_ck_dec, rlx_names_bus_dec,
	rlx_decdivider_ops, BUS_CLK_CFG_R, BUS_CK_CHANGE);
DEFINE_CLK_RLX(bus_ck, rlx_names_v,
	rlx_clk_bus_ops, BUS_CLK_CFG_R, BUS_CK_CHANGE);

DEFINE_CLK_RLX(dram_ck_div, rlx_names_dram_div,
	rlx_divider_ops, DRAM_CLK_CFG_R, DRAM_CK_CHANGE);
DEFINE_CLK_RLX(dram_ck_dec, rlx_names_dram_dec,
	rlx_decdivider_ops, DRAM_CLK_CFG_R, DRAM_CK_CHANGE);
DEFINE_CLK_RLX(dram_ck, rlx_names_v,
	rlx_clk_dram_ops, DRAM_CLK_CFG_R, DRAM_CK_CHANGE);

DEFINE_CLK_RLX(isp_ck_div, rlx_names_isp_div,
	rlx_divider_ops, ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(isp_ck_dec, rlx_names_isp_dec,
	rlx_decdivider_ops, ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(isp_ck, rlx_names_v,
	rlx_clk_isp_ops, ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(mipi_ck_div, rlx_names_mipi_div,
	rlx_divider_ops, MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(mipi_ck_dec, rlx_names_mipi_dec,
	rlx_decdivider_ops, MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(mipi_ck, rlx_names_v,
	rlx_clk_mipi_ops, MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(i2c_ck_div, rlx_names_i2c_div,
	rlx_divider_ops_s, I2C_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(i2c_ck, rlx_names_v,
	rlx_clk_i2c_ops, I2C_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(xb2_ck_div, rlx_names_xb2_div,
	rlx_divider_ops_s, XB2_CLK_CFG_R, XB2_CK_CHANGE);
DEFINE_CLK_RLX(xb2_ck, rlx_names_v,
	rlx_clk_xb2_ops, XB2_CLK_CFG_R, XB2_CK_CHANGE);

DEFINE_CLK_RLX(lcdc_ck_div, rlx_names_lcdc_div,
	rlx_divider_lcdc, R_LCDC_CLK_CFG_REG, CK_CHANGE_NULL);
DEFINE_CLK_RLX(lcdc_ck, rlx_names_v,
	rlx_clk_lcdc_ops, R_LCDC_CLK_CFG_REG, CK_CHANGE_NULL);

DEFINE_CLK_RLX(uart_ck_div, rlx_names_uart_div,
	rlx_divider_ops_s, UART_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(uart_ck, rlx_names_v,
	rlx_clk_uart_ops, UART_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(i2s_ck_div, rlx_names_i2s_div,
	rlx_divider_ops_c, I2S_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(i2s_ck, rlx_names_v,
	rlx_clk_i2s_ops, I2S_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(spdif_ck_div, rlx_names_spdif_div,
	rlx_divider_ops_c, SPDIF_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(spdif_ck, rlx_names_v,
	rlx_clk_spdif_ops, SPDIF_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(codec_ck_div, rlx_names_codec_div,
	rlx_divider_ops_c, CODEC_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(codec_ck, rlx_names_v,
	rlx_clk_codec_ops, CODEC_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(h265_ck, rlx_names_v,
	rlx_clk_h265_clk_ops, H265_ACLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(h265_aclk_ck, rlx_names_h265_aclk,
	rlx_clk_h265_aclk_ops, H265_ACLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(h265_bclk_div, rlx_names_h265_bclk_div,
	rlx_divider_ops, H265_BCLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(h265_bclk_dec, rlx_names_h265_bclk_dec,
	rlx_decdivider_ops, H265_BCLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(h265_bclk_ck, rlx_names_v,
	rlx_clk_h265_bclk_ops, H265_BCLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(h265_cclk_div, rlx_names_h265_cclk_div,
	rlx_divider_ops, H265_CCLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(h265_cclk_dec, rlx_names_h265_cclk_dec,
	rlx_decdivider_ops, H265_CCLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(h265_cclk_ck, rlx_names_v,
	rlx_clk_h265_cclk_ops, H265_CCLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(ssor_hclk_div, rlx_names_ssor_hclk_div,
	rlx_divider_ops_l, SSOR_HCLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(ssor_hclk_ck, rlx_names_v,
	rlx_clk_hclk_ops, SSOR_HCLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(ecc_ck, rlx_names_v,
	rlx_clk_gate_ops, RSA_CLK_EN_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(sha_ck, rlx_names_v,
	rlx_clk_gate_ops, SHA_CLK_EN_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(nnbus_ck, rlx_names_v,
	rlx_clk_gate_ops, NN_BUS_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(nncore_ck_div, rlx_names_nncore_div,
	rlx_divider_ops, NN_CORE_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(nncore_ck_dec, rlx_names_nncore_dec,
	rlx_decdivider_ops, NN_CORE_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(nncore_ck, rlx_names_v,
	rlx_clk_nncore_ops, NN_CORE_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(ge_ck, rlx_names_v,
	rlx_clk_gate_ops, GE_CLK_EN_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(trng_ck, rlx_names_v,
	rlx_clk_gate_ops, TRNG_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(lcdc_dram_ck, rlx_names_v,
	rlx_clk_gate_ops, LCDC_DRAM_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(efuse_ck, rlx_names_v,
	rlx_clk_gate_ops, EFUSE_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(macbypass_div, rlx_names_macbypass_div,
	rlx_divider_ops, MAC_BYPASS_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(macbypass_ck, rlx_names_v,
	rlx_clk_macbypass_ops, MAC_BYPASS_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(mipitx_ck, rlx_names_v,
	rlx_clk_gate_ops, MIPI_TX_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(jpegdram_ck, rlx_names_v,
	rlx_clk_gate_ops, JPEG_DRAM_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(cipher_ck, rlx_names_v,
	rlx_clk_gate_ops, CIPHER_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(mipitx_lowdiv, rlx_names_mipitx_lowdiv,
	rlx_divider_ops_s, MIPI_TX_LOW_CLK_CFG_R, CK_CHANGE_NULL);
DEFINE_CLK_RLX(mipitx_lowck, rlx_names_v,
	rlx_clk_mipitx_low_ops, MIPI_TX_LOW_CLK_CFG_R, CK_CHANGE_NULL);

#endif

#define ISP_SCAN_CLK_CFG_R	(0x58)
#define MIPI_SCAN_CLK_CFG_R	(0x5c)
#define CK_CHANGE_NULL			0

static const char * const rlx_names_v[] = {
	"dummy"
};

DEFINE_CLK_RLX(isp_ck, rlx_names_v,
	rlx_clk_isp_ops, ISP_SCAN_CLK_CFG_R, CK_CHANGE_NULL);

DEFINE_CLK_RLX(mipi_ck, rlx_names_v,
	rlx_clk_mipi_ops, MIPI_SCAN_CLK_CFG_R, CK_CHANGE_NULL);

#if 0
/*
static int rlx_check_clocks(struct clk_rlx *clks[], unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++)
		if (IS_ERR(clks[i])) {
			printf("rlx clk %u: register failed with NULL\n", i);
			return RTS_FAIL; 
		}
	return RTS_OK;
}
*/

DEFINE_CLK_RLX(dummy, NULL,	*(struct clk_ops*)NULL, 0, 0);

static struct clk_rlx *rlx_register_fixed_rate(const char *name,
		const char *parent_name, unsigned long flags,
		unsigned long fixed_rate)
{
	struct clk_rlx *clk;

	if (strcmp(dummy.name, name)==0)
		clk = &dummy;
	if (!clk) {
		printf("Error! rlx_register_fixed_rate %s failed.\n", name);
		return NULL;
	}

	clk->num_parents = 0;
	clk->mult = clk->div = 1;
	clk->reg_i = -1;
	clk->rate = fixed_rate;
	clk->flags = flags;

	return clk;
}

DEFINE_CLK_RLX(sys_osc, NULL, *(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(usb_pll, NULL, *(struct clk_ops*)NULL, 0, 0);

static struct clk_rlx *rlx_obtain_fixed_clock(
			const char *name, unsigned long rate)
{
	struct clk_rlx *clk=NULL;

	if (strcmp(sys_osc.name, name)==0)
		clk = &sys_osc;
	if (strcmp(usb_pll.name, name)==0)
		clk = &usb_pll;
	if (!clk) {
		printf("Error! rlx_obtain_fixed_clock %s failed.\n", name);
		return NULL;
	}
	clk->num_parents = 0;
	clk->mult = clk->div = 1;
	clk->reg_v = NULL; clk->reg_i = -1;
	clk->rate = rate;

	return clk;
}

static struct clk_rlx *clk_core_get_parent_by_index(struct clk_rlx *rlxclk,
							 u8 index)
{
	struct clk_rlx *ptr=NULL;
	
	if (!rlxclk || index >= rlxclk->num_parents)
		return NULL;

	if (rlxclk->parent_names[index])
		ptr = clk_get(rlxclk->parent_names[index]);

	return ptr;
}

static struct clk_rlx *__clk_init_parent(struct clk_rlx *rlxclk)
{
	u8 index = 0;

	if (rlxclk->num_parents > 1 && rlxclk->ops->get_parent)
		index = rlxclk->ops->get_parent(rlxclk);

	return clk_core_get_parent_by_index(rlxclk, index);
}

static unsigned long clk_core_get_rate_nolock(struct clk_rlx *rlxclk)
{
	unsigned long ret;

	if (!rlxclk) {
		ret = 0;
		goto out;
	}

	ret = rlxclk->rate;

	if (!rlxclk->num_parents)
		goto out;

	if (!rlxclk->parent)
		ret = 0;

out:
	return ret;
}
#endif

static struct clk_rlx *rlx_register_clk(struct clk_rlx *rlxclk, int flags)
{
	//unsigned long rate;

	rlxclk->flags = flags;
#if defined(_SYSTEM_CONNECT_READY_)
	rlxclk->parent = __clk_init_parent(rlxclk);

	/* from __clk_core_init()
	 * Set clk's rate.  The preferred method is to use .recalc_rate.  For
	 * simple clocks and lazy developers the default fallback is to use the
	 * parent's rate.  If a clock doesn't have a parent (or is orphaned)
	 * then rate is set to zero.
	 */
	if (rlxclk->ops->recalc_rate)
		rate = rlxclk->ops->recalc_rate(rlxclk,
				clk_core_get_rate_nolock(rlxclk->parent));
	else if (rlxclk->parent)
		rate = rlxclk->parent->rate;
	else
		rate = 0;

	rlxclk->rate = rate;
#endif

	/*
	 * Enable CLK_IS_CRITICAL clocks so newly added critical clocks
	 * don't get accidentally disabled when walking the orphan tree and
	 * reparenting clocks
	 */
	if (rlxclk->flags & CLK_IS_CRITICAL) {
		clk_prepare_enable(rlxclk);
	}

	return rlxclk;
}
#if 0
DEFINE_CLK_RLX(isp_temp, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(mipi_temp, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(inf_temp, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);


DEFINE_CLK_RLX(usb_pll_2, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(usb_pll_3, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(usb_pll_5, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(usb_pll_7, rlx_usb_parent_names,	*(struct clk_ops*)NULL, 0, 0);

DEFINE_CLK_RLX(gpll0_2, rlx_gpll0_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll0_3, rlx_gpll0_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll0_5, rlx_gpll0_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll0_7, rlx_gpll0_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll1_2, rlx_gpll1_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll1_3, rlx_gpll1_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll1_5, rlx_gpll1_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll1_7, rlx_gpll1_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll2_2, rlx_gpll2_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll2_3, rlx_gpll2_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll2_5, rlx_gpll2_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll2_7, rlx_gpll2_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll3_2, rlx_gpll3_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll3_3, rlx_gpll3_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll3_5, rlx_gpll3_parent_names,	*(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(gpll3_7, rlx_gpll3_parent_names,	*(struct clk_ops*)NULL, 0, 0);

DEFINE_CLK_RLX(lvds_pll_2, rlx_lvds_pll_parent_names, *(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(lvds_pll_3, rlx_lvds_pll_parent_names, *(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(lvds_pll_5, rlx_lvds_pll_parent_names, *(struct clk_ops*)NULL, 0, 0);
DEFINE_CLK_RLX(lvds_pll_7, rlx_lvds_pll_parent_names, *(struct clk_ops*)NULL, 0, 0);

static struct clk_rlx *rlx_register_fixed_factor(
		const char *name, const char *parent_name, unsigned long flags,
		unsigned int mult, unsigned int div)
{
	struct clk_rlx *parent_clk, *clk=NULL;

	if (strcmp(usb_pll_2.name, name)==0) {
		clk = &usb_pll_2; goto set_args; }
	if (strcmp(usb_pll_3.name, name)==0) {
		clk = &usb_pll_3; goto set_args; }
	if (strcmp(usb_pll_5.name, name)==0) {
		clk = &usb_pll_5; goto set_args; }
	if (strcmp(usb_pll_7.name, name)==0) {
		clk = &usb_pll_7; goto set_args; }

	if (strcmp(gpll0_2.name, name)==0) {
		clk = &gpll0_2; goto set_args; }
	if (strcmp(gpll0_3.name, name)==0) {
		clk = &gpll0_3; goto set_args; }
	if (strcmp(gpll0_5.name, name)==0) {
		clk = &gpll0_5; goto set_args; }
	if (strcmp(gpll0_7.name, name)==0) {
		clk = &gpll0_7; goto set_args; }

	if (strcmp(gpll1_2.name, name)==0) {
		clk = &gpll1_2; goto set_args; }
	if (strcmp(gpll1_3.name, name)==0) {
		clk = &gpll1_3; goto set_args; }
	if (strcmp(gpll1_5.name, name)==0) {
		clk = &gpll1_5; goto set_args; }
	if (strcmp(gpll1_7.name, name)==0) {
		clk = &gpll1_7; goto set_args; }

	if (strcmp(gpll2_2.name, name)==0) {
		clk = &gpll2_2; goto set_args; }
	if (strcmp(gpll2_3.name, name)==0) {
		clk = &gpll2_3; goto set_args; }
	if (strcmp(gpll2_5.name, name)==0) {
		clk = &gpll2_5; goto set_args; }
	if (strcmp(gpll2_7.name, name)==0) {
		clk = &gpll2_7; goto set_args; }

	if (strcmp(gpll3_2.name, name)==0) {
		clk = &gpll3_2; goto set_args; }
	if (strcmp(gpll3_3.name, name)==0) {
		clk = &gpll3_3; goto set_args; }
	if (strcmp(gpll3_5.name, name)==0) {
		clk = &gpll3_5; goto set_args; }
	if (strcmp(gpll3_7.name, name)==0) {
		clk = &gpll3_7; goto set_args; }

	if (strcmp(lvds_pll_2.name, name)==0) {
		clk = &lvds_pll_2; goto set_args; }
	if (strcmp(lvds_pll_3.name, name)==0) {
		clk = &lvds_pll_3; goto set_args; }
	if (strcmp(lvds_pll_5.name, name)==0) {
		clk = &lvds_pll_5; goto set_args; }
	if (strcmp(lvds_pll_7.name, name)==0) {
		clk = &lvds_pll_7; goto set_args; }

	if (!clk) {
		printf("Error! rlx_register_fixed_factor %s failed.\n", name);
		return NULL;
	}

set_args:
	clk->flags = flags;
	clk->mult = mult;
	clk->div = div;
	clk->reg_v = NULL; clk->reg_i = -1;
	parent_clk = clk_get(parent_name);
	if (parent_clk) {
		parent_clk->siblins[parent_clk->num_siblins] = clk;
		parent_clk->num_siblins++;
		clk->parent = parent_clk;
		clk->rate = parent_clk->rate * mult / div;
	} else {
		clk->rate = 0;
		printf("rlx_register_fixed_factor(): %s get parent %s error\n", name, parent_name);
	}

	return clk;
}

static void rlx_clock_hw_init(void)
{
	u32 reg;

	/* Disable usbphy */
	reg = rts_clk_readl(USBPHY_CLK_CFG_R);
	reg &= ~(USBPHY_HOST_CLK_EN | USBPHY_DEV_CLK_EN);
	rts_clk_writel(reg, USBPHY_CLK_CFG_R);

	/* Disable ephy */
	reg = rts_clk_readl(ETHERNET_CLK_CFG_R);
	reg &= ~CLK_ENABLE;
	rts_clk_writel(reg, ETHERNET_CLK_CFG_R);

	reg = rts_clk_readl(SSOR_CLK_OE_R);
	reg |= 1;
	rts_clk_writel(reg, SSOR_CLK_OE_R);
}

static int rlx_clocks_init(void)
{
	int i;
	//int clksize;
#ifdef CONFIG_SOC_ENABLE_PLL0  //for 3903
	struct clk_rlx *pll0_clk;
#endif
	//int ret;

	rlx_clock_hw_init();
	for (i = (int)UART_CLK_LP_EN_R; i <= (int)TRNG_CLK_CFG_R; i += 4)
		clk_reg_v[(i&0xff) >> 2] = rts_clk_readl(i);

	clks[RLX_CLK_DUMMY] = rlx_register_fixed_rate(
		"dummy", (char*)NULL, 0, 100000000);
	clks[RLX_CLK_SYS_OSC] = rlx_obtain_fixed_clock("sys_osc", 25000000);
	clks[RLX_CLK_USB_PLL] = rlx_obtain_fixed_clock("usb_pll", 480000000);
	clks[RLX_CLK_USB_PLL_2] = rlx_register_fixed_factor(
		"usb_pll_2", "usb_pll", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_USB_PLL_3] = rlx_register_fixed_factor(
		"usb_pll_3", "usb_pll", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_USB_PLL_5] = rlx_register_fixed_factor(
		"usb_pll_5", "usb_pll", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_USB_PLL_7] = rlx_register_fixed_factor(
		"usb_pll_7", "usb_pll", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_SYS_PLL0] = rlx_register_clk(
		&gpll0, CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SYS_PLL1] = rlx_register_clk(
		&gpll1, CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SYS_PLL2] = rlx_register_clk(
		&gpll2, CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SYS_PLL3] = rlx_register_clk(
		&gpll3, CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SYS_PLL0_2] = rlx_register_fixed_factor(
		"gpll0_2", "gpll0", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_SYS_PLL0_3] = rlx_register_fixed_factor(
		"gpll0_3", "gpll0", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_SYS_PLL0_5] = rlx_register_fixed_factor(
		"gpll0_5", "gpll0", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_SYS_PLL0_7] = rlx_register_fixed_factor(
		"gpll0_7", "gpll0", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_SYS_PLL1_2] = rlx_register_fixed_factor(
		"gpll1_2", "gpll1", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_SYS_PLL1_3] = rlx_register_fixed_factor(
		"gpll1_3", "gpll1", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_SYS_PLL1_5] = rlx_register_fixed_factor(
		"gpll1_5", "gpll1", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_SYS_PLL1_7] = rlx_register_fixed_factor(
		"gpll1_7", "gpll1", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_SYS_PLL2_2] = rlx_register_fixed_factor(
		"gpll2_2", "gpll2", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_SYS_PLL2_3] = rlx_register_fixed_factor(
		"gpll2_3", "gpll2", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_SYS_PLL2_5] = rlx_register_fixed_factor(
		"gpll2_5", "gpll2", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_SYS_PLL2_7] = rlx_register_fixed_factor(
		"gpll2_7", "gpll2", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_SYS_PLL3_2] = rlx_register_fixed_factor(
		"gpll3_2", "gpll3", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_SYS_PLL3_3] = rlx_register_fixed_factor(
		"gpll3_3", "gpll3", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_SYS_PLL3_5] = rlx_register_fixed_factor(
		"gpll3_5", "gpll3", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_SYS_PLL3_7] = rlx_register_fixed_factor(
		"gpll3_7", "gpll3", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_LVDS_PLL] = rlx_register_clk(
		&lvds_pll, CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED);
	clks[RLX_CLK_LVDS_PLL_2] = rlx_register_fixed_factor(
		"lvds_pll_2", "lvds_pll", CLK_SET_RATE_PARENT, 1, 2);
	clks[RLX_CLK_LVDS_PLL_3] = rlx_register_fixed_factor(
		"lvds_pll_3", "lvds_pll", CLK_SET_RATE_PARENT, 1, 3);
	clks[RLX_CLK_LVDS_PLL_5] = rlx_register_fixed_factor(
		"lvds_pll_5", "lvds_pll", CLK_SET_RATE_PARENT, 1, 5);
	clks[RLX_CLK_LVDS_PLL_7] = rlx_register_fixed_factor(
		"lvds_pll_7", "lvds_pll", CLK_SET_RATE_PARENT, 1, 7);

	clks[RLX_CLK_DMA_CK] = rlx_register_clk(&dma_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_USBPHY_HOST_CK] = rlx_register_clk(&usbphy_host_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_USBPHY_DEV_CK] = rlx_register_clk(&usbphy_dev_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_ETHERNET_CK] = rlx_register_clk(&ethernet_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_CPU_CK_DIV] = rlx_register_clk(&cpu_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_CPU_CK_DEC] = rlx_register_clk(&cpu_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_CPU_CK] = rlx_register_clk(&cpu_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_JPEG_CK_DIV] = rlx_register_clk(&jpeg_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_JPEG_CK_DEC] = rlx_register_clk(&jpeg_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_JPEG_CK] = rlx_register_clk(&jpeg_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_BUS_CK_DIV] = rlx_register_clk(&bus_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_BUS_CK_DEC] = rlx_register_clk(&bus_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_BUS_CK] = rlx_register_clk(&bus_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_DRAM_CK_DIV] = rlx_register_clk(&dram_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_DRAM_CK_DEC] = rlx_register_clk(&dram_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_DRAM_CK] = rlx_register_clk(&dram_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_ISP_CK_DIV] = rlx_register_clk(&isp_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_ISP_CK_DEC] = rlx_register_clk(&isp_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_ISP_CK] = rlx_register_clk(&isp_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_MIPI_CK_DIV] = rlx_register_clk(&mipi_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_MIPI_CK_DEC] = rlx_register_clk(&mipi_ck_dec,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_MIPI_CK] = rlx_register_clk(&mipi_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_I2C_CK_DIV] = rlx_register_clk(&i2c_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_I2C_CK] = rlx_register_clk(&i2c_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_XB2_CK_DIV] = rlx_register_clk(&xb2_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_XB2_CK] = rlx_register_clk(&xb2_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_UART_CK_DIV] = rlx_register_clk(&uart_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_UART_CK] = rlx_register_clk(&uart_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_I2S_CK_DIV]	= rlx_register_clk(&i2s_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_I2S_CK] = rlx_register_clk(&i2s_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_SPDIF_CK_DIV] = rlx_register_clk(&spdif_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SPDIF_CK] = rlx_register_clk(&spdif_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_CODEC_CK_DIV] = rlx_register_clk(&codec_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_CODEC_CK] = rlx_register_clk(&codec_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_CIPHER_CK] = rlx_register_clk(&cipher_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_H265_ACLK_CK] =
		rlx_register_clk(&h265_aclk_ck, CLK_IGNORE_UNUSED);

	clks[RLX_CLK_H265_BCLK_CK_DIV] =
		rlx_register_clk(&h265_bclk_div, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_H265_BCLK_CK_DEC] =
		rlx_register_clk(&h265_bclk_dec, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_H265_BCLK_CK] =
		rlx_register_clk(&h265_bclk_ck, CLK_IGNORE_UNUSED);

	clks[RLX_CLK_H265_CCLK_CK_DIV] =
		rlx_register_clk(&h265_cclk_div, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_H265_CCLK_CK_DEC] =
		rlx_register_clk(&h265_cclk_dec, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_H265_CCLK_CK] =
		rlx_register_clk(&h265_cclk_ck, CLK_IGNORE_UNUSED);

	clks[RLX_CLK_H265_CK] = rlx_register_clk(&h265_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_SSOR_HCLK_DIV] = rlx_register_clk(&ssor_hclk_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SSOR_HCLK] = rlx_register_clk(&ssor_hclk_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_RSA] = rlx_register_clk(&ecc_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_SHA] = rlx_register_clk(&sha_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_NN_BUS] = rlx_register_clk(&nnbus_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_NNCORE_CK_DIV] =
		rlx_register_clk(&nncore_ck_div, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_NNCORE_CK_DEC] =
		rlx_register_clk(&nncore_ck_dec, CLK_IGNORE_UNUSED);
	clks[RLX_CLK_NNCORE_CK] =
		rlx_register_clk(&nncore_ck, CLK_IGNORE_UNUSED);

	clks[RLX_CLK_GE] = rlx_register_clk(&ge_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_TRNG] = rlx_register_clk(&trng_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_LCDC_DRAM] = rlx_register_clk(&lcdc_dram_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_EFUSE] = rlx_register_clk(&efuse_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_MACBYPASS_CK_DIV] = rlx_register_clk(&macbypass_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_MACBYPASS_CK] = rlx_register_clk(&macbypass_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_MIPITX] = rlx_register_clk(&mipitx_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_JPEGDRAM] = rlx_register_clk(&jpegdram_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_LCDC_DIV] = rlx_register_clk(&lcdc_ck_div,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_LCDC_CK] = rlx_register_clk(&lcdc_ck,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_MIPITX_LDIV] = rlx_register_clk(&mipitx_lowdiv,
		CLK_IGNORE_UNUSED);
	clks[RLX_CLK_MIPITX_LOW] = rlx_register_clk(&mipitx_lowck,
		CLK_IGNORE_UNUSED);

	//clksize = RLX_CLK_MIPITX_LOW + 1;
	//ret = rlx_check_clocks(clks, clksize);

	//clk_data.clks = clks;
	//clk_data.clk_num = clksize;
	//of_clk_add_provider(node, of_clk_src_onecell_get, &clk_data);

#ifdef CONFIG_SOC_ENABLE_PLL0  //for 3903
	pll0_clk = clk_get("gpll0");
	clk_set_rate(pll0_clk, 1200000000);
	clk_prepare_enable(pll0_clk);
	clk_put(pll0_clk);
#endif

	return RTS_OK;
}

//static const struct of_device_id rlx_clk_match[] = {
//	{
//		.compatible = "realtek,rts3915-clocks",
//		.data = (void *)(TYPE_RTS3915),
//	},
//	{}
//};
//MODULE_DEVICE_TABLE(of, rlx_clk_match);

void rlx_clk_init(void)
{
	clk_platform_type = (int)TYPE_RTS3915;

	clk_mapped_addr = (void*)SYS_BASE;

	pll_mapped_addr = (void*)PLLMAP_BASE;

	lvds_pll_mapped_addr = (void*)LVDS_PLLMAP_BASE;

	if (rlx_clocks_init() != RTS_OK) {
		while (1) ;
	}
}
#endif

void rlx_clk_init0(void)
{
	clk_platform_type = (int)TYPE_RTS3915;


#if defined(_SYSTEM_CONNECT_READY_)
	clks[RLX_CLK_ISP_CK] = rlx_register_clk(&isp_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_MIPI_CK] = rlx_register_clk(&mipi_ck,
		CLK_IGNORE_UNUSED);

	clks[RLX_CLK_MIPITX] = rlx_register_clk(&mipitx_ck,
		CLK_IGNORE_UNUSED);
#else

#if CONFIG_FPGA // FPGA
	clks[RLX_CLK_ISP_CK] = rlx_register_clk(&isp_ck,
		CLK_IGNORE_UNUSED);
	isp_ck.rate = 20000000;

	clks[RLX_CLK_MIPI_CK] = rlx_register_clk(&mipi_ck,
		CLK_IGNORE_UNUSED);
	mipi_ck.rate = 20000000;
#else  // ASIC // PXP
	clks[RLX_CLK_ISP_CK] = rlx_register_clk(&isp_ck,
		CLK_IGNORE_UNUSED);
	isp_ck.rate = 200000000; //ISP_CLK_DEFINE

	clks[RLX_CLK_MIPI_CK] = rlx_register_clk(&mipi_ck,
		CLK_IGNORE_UNUSED);
	mipi_ck.rate = 250000000; //MIPI_CLK_DEFINE
#endif






	//clks[RLX_CLK_MIPITX] = rlx_register_clk(&mipitx_ck,
	//	CLK_IGNORE_UNUSED);
	//mipitx_ck.rate = 20000000;
#endif


}

//CLK_OF_DECLARE(rts3915_clocks, "realtek,rts3915-clocks", rlx_clk_init);
