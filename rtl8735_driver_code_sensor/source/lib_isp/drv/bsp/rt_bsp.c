#include "rt_bsp.h"
#include "rt_util.h"

//#include "rlx_regdef.h"
#include "rlx_reg.h"
#include "rlx_sys.h"

//#include "rlxboard.h"  // Frank: MUST before part.h
#include "rlx_mman.h"
#if 0
// --------------------------------------------------------
//  CPU, byteorder
// --------------------------------------------------------
void rt_bsp_get_board(board_t *out)
{
	RT_ASSERT(out);
	out->chip	= CFG_BOARD_CHIP;
	out->pkg	= CFG_BOARD_PKG;
}

char *prid_to_str(u32 prid, char str[32])
{
	pair_uint_cstr_st table[] = {
		{0x0000dc06, "rx5381"},
		{0x0000dc05, "rx4381"},
		{0x0000dc04, "rx5271"},
		{0x0000dc03, "rx4271"},
		{0x0000dc02, "rx5281"},
		{0x0000dc01, "rx4281"},
	};

	strcpy(str, "unknown");
	for (int i = 0; i < (int)ARRAY_SIZE(table); i++)
	{
		if (prid == table[i].first)
		{
			strcpy(str, table[i].second);
			break;
		}
	}
	return str;
}

void rt_bsp_get_cpu(cpu_t *cpu)
{
	cpu->prid = read_c0_prid() & 0xffff;
	cpu->freq = CFG_CPU_FREQ;
	return;
}

// --------------------------------------------------------
//  DDR
// --------------------------------------------------------
static pair_uint_cstr_st s_dram_base[] =
{
	{GPIO_BASE,     "GPIO"  },
	{I2C0_BASE,     "I2C0"  },
	{I2C1_BASE,     "I2C1"  },
	{UART0_BASE,    "UART0" },
	{UART1_BASE,    "UART1" },
	{UART2_BASE,    "UART2" },
	{WDOG_BASE,     "WDOG"  },
	{SDIO_BASE,     "SDIO"  },
	{ISP_BASE,      "ISP"   },
	{JPEG_BASE,     "JPEG"  },
	{H264_BASE,     "H264"  },
};

void rt_bsp_show_dram_base(void)
{
	for (int i = 0; i < (int)ARRAY_SIZE(s_dram_base); i++)
		rt_printf("%-12s: 0x%08X\n", s_dram_base[i].second, s_dram_base[i].first);
}

// return 0 if not found.
u32 rt_bsp_find_dram_base(char *str)
{
	u32 adr = 0;

	for (int i = 0; i < (int)ARRAY_SIZE(s_dram_base); i++)
	{
		if (strcmp(str, s_dram_base[i].second) == 0)
		{
			adr = s_dram_base[i].first;
			break;
		}
	}
	return adr;
}

static u64 s_dram_size = 0;
u64 rt_bsp_get_dram_size(void)
{
	// probe DDR size
	//  1. use uncachable address to probe size , if use cachable address , the value
	//     will save in cache , the addess seemed not wrapped,
	//  2. for 128MB flash, the address 0xAFFFFFFC will wrap to 0xA7FFFFFC,
	//     for  64MB flash, the address 0xA7FFFFFC will wrap to 0xA3FFFFFC
	//
	// caution!
	//  the way of probe DDR size is to change some content at some memory addr,
	//  so it is safe to use s_dram_size to remember the size.
	//  in the very early stage during main boot, this function will be called
	//  at first time and the s_dram_size will be updated.
	//
	if (s_dram_size == 0)
	{
		MEM32(0xAFFFFFFC) = 0x10000000;
		MEM32(0xA7FFFFFC) = 0x08000000;
		MEM32(0xA3FFFFFC) = 0x04000000;
		MEM32(0xA1FFFFFC) = 0x02000000;
		s_dram_size = MEM32(0xAFFFFFFC);
	}
	return s_dram_size;
}

static s64 s64_div(s64 dividend, s64 divisor)
{
	s64 res = 0;

	if (divisor == 0) {
		rt_printf("error! divisor = 0\n");
		return 0;
	}

	if (dividend < divisor)
		return 0;

	while (dividend > divisor) {
		dividend -= divisor;
		res++;
	}

	if (dividend == divisor)
		res++;

	return res;
}

int rt_bsp_get_dram_clock(void)
{
#define REF_PLL		25000000
	u64 dpi_f_code = MEM32(RLX_REG_DDR_PHY_SSC2) & 0x7ff;
	u64 dpi_n_code = MEM32(RLX_REG_DDR_PHY_SSC3) & 0xff;
	s64 clock = s64_div(REF_PLL * dpi_f_code * 2, 2048);

	clock = s64_div((clock + REF_PLL * (dpi_n_code + 2) * 2 + 500000), 1000000);
	return (int)clock;
}

u32 rt_bsp_virt_to_phys(void *virt_addr)
{
	return rlx_virt_to_phys(virt_addr);
}

void *rt_bsp_phys_to_virt(u32 phys_addr)
{
	return rlx_phys_to_virt(phys_addr);
}

// --------------------------------------------------------
//  register
// --------------------------------------------------------
u8 reg_r8(u32 adr)
{
	return REG_R8(adr);
}

void reg_w8(u32 adr, u8 val)
{
	REG_W8(adr, val);
}

u16 reg_r16(u32 adr)
{
	return REG_R16(adr);
}

void reg_w16(u32 adr, u16 val)
{
	REG_W16(adr, val);
}

u32 reg_r32(u32 adr)
{
	return REG_R32(adr);
}

void reg_w32(u32 adr, u32 val)
{
	REG_W32(adr, val);
}

// --------------------------------------------------------
//  misc
// --------------------------------------------------------
void rt_bsp_restart(restart_time_t timeout)
{
	rlx_sys_wdog_restart((wdog_time_t)timeout);
}
#endif
