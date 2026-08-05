#include "rlx_inc.h"
#include "rlx_reg.h"
#include "rlx_sys.h"

// example: mask = 0x05
//	clr_mask_bits() will set bit2 & bit0 to 0
//	set_mask_bits() will set bit2 & bit0 to 1
#define clr_mask_bits(addr, mask)	REG_W32((addr), (REG_R32(addr) & ~(mask)))
#define set_mask_bits(addr, mask)	REG_W32((addr), (REG_R32(addr) | (mask)))

// system memory shutdown reg fields:
#define NAND_MEM_SD		0x300	// [9:8]
#define ETH_MEM_SD		0x80	// [7]
#define CIPHER_MEM_SD	0x40	// [6]
#define AUDIO_MEM_SD	0x20	// [5]
#define H264_MEM_SD		0x18	// [4:3]
#define U2DEV_MEM_SD	0x04	// [2]
#define SDIO_MEM_SD		0x03	// [1:0]
#if 0
void rlx_sys_mem_up(int model)
{
	switch (model)
	{
	case SYS_MEM_SD_NAND_SPIC:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, NAND_MEM_SD);
		break;

	case SYS_MEM_SD_ETH:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, ETH_MEM_SD);
		break;

	case SYS_MEM_SD_CIPHER:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, CIPHER_MEM_SD);
		break;

	case SYS_MEM_SD_AUDIO:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, AUDIO_MEM_SD);
		break;

	case SYS_MEM_SD_H264:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, H264_MEM_SD);
		break;

	case SYS_MEM_SD_U2DEV:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, U2DEV_MEM_SD);
		break;

	case SYS_MEM_SD_SDIO:
		clr_mask_bits(RLX_REG_SYS_MEM_SD, SDIO_MEM_SD);
		break;

	default:
		rt_err("invalid model = %d\n", model);
		break;
	}
}

void rlx_sys_mem_down(int model)
{
	switch (model)
	{
	case SYS_MEM_SD_NAND_SPIC:
		set_mask_bits(RLX_REG_SYS_MEM_SD, NAND_MEM_SD);
		break;

	case SYS_MEM_SD_ETH:
		set_mask_bits(RLX_REG_SYS_MEM_SD, ETH_MEM_SD);
		break;

	case SYS_MEM_SD_CIPHER:
		set_mask_bits(RLX_REG_SYS_MEM_SD, CIPHER_MEM_SD);
		break;

	case SYS_MEM_SD_AUDIO:
		set_mask_bits(RLX_REG_SYS_MEM_SD, AUDIO_MEM_SD);
		break;

	case SYS_MEM_SD_H264:
		set_mask_bits(RLX_REG_SYS_MEM_SD, H264_MEM_SD);
		break;

	case SYS_MEM_SD_U2DEV:
		set_mask_bits(RLX_REG_SYS_MEM_SD, U2DEV_MEM_SD);
		break;

	case SYS_MEM_SD_SDIO:
		set_mask_bits(RLX_REG_SYS_MEM_SD, SDIO_MEM_SD);
		break;

	default:
		rt_err("invalid model = %d\n", model);
		break;
	}
}


#define WDOG_PAD_PULLDOWN		0x1
#define WDOG_RESET_SYSTEM		0x1
#define WDOG_ENABLE				0x1
#define WDOG_CFG_DATA(t)		((WDOG_PAD_PULLDOWN << 8) | \
								((t) << 16) | \
								(WDOG_RESET_SYSTEM << 1) | \
								(WDOG_ENABLE << 0))

void	rlx_sys_wdog_restart(wdog_time_t time)
{
	unsigned int val = WDOG_CFG_DATA(time&0x0F);
	REG_W8(RLX_REG_WATCHDOG_CFG, val);
	return;
}
#endif
