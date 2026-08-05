#ifndef __RT_BSP_H__
#define __RT_BSP_H__
#include "rt_drv.h"

// --------------------------------------------------------
//  CPU, byteorder
// --------------------------------------------------------
// convert cpu's endian to big endian
#include "rlx_byteorder.h"

#define rt_cpu_to_be16		rlx_cpu_to_be16
#define rt_cpu_to_be32		rlx_cpu_to_be32
#define rt_cpu_to_be64		rlx_cpu_to_be64

typedef struct
{
	u16		chip;
	char	pkg;
} board_t;

void rt_bsp_get_board(board_t *out);

typedef struct
{
	u32 prid;
	u32 freq;
} cpu_t;

void	rt_bsp_get_cpu(cpu_t *cpu);
char	*prid_to_str(u32 prid, char str[32]);

// --------------------------------------------------------
//  DDR
// --------------------------------------------------------
u64		rt_bsp_get_dram_size(void);
int		rt_bsp_get_dram_clock(void);
// brief: show dram_base table
void	rt_bsp_show_dram_base(void);
// return 0 if not found.
u32		rt_bsp_find_dram_base(char *str);

// virtual & physical address conversion
u32		rt_bsp_virt_to_phys(void *virt_addr);
void	*rt_bsp_phys_to_virt(u32 phys_addr);

// --------------------------------------------------------
//  register
// --------------------------------------------------------
u8		reg_r8(u32 adr);
u16		reg_r16(u32 adr);
u32		reg_r32(u32 adr);

void	reg_w8(u32 adr, u8 val);
void	reg_w16(u32 adr, u16 val);
void	reg_w32(u32 adr, u32 val);

// --------------------------------------------------------
//  misc
// --------------------------------------------------------
typedef enum {
	_1S = 0x0,
	_2S = 0x1,
	_4S = 0x2,
	_8S = 0x3,
} restart_time_t;

void	rt_bsp_restart(restart_time_t timeout);

#endif	// __RT_BSP_H__
