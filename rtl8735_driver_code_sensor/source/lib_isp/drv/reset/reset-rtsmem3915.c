/*
 * Realtek Semiconductor Corp.
 *
 * Memory power control driver
 *
 * Copyright (C) 2017      Wei WANG (wei_wang@realsil.com.cn)
 */


#include "cmsis_os2.h"
#include "rts_errno.h"
#include <reset/rts-sysmem.h>
#include "rlx_reg.h"
#include "rtx_mutex.h"
#if 0
struct rts_sysmem_regs {
	u32 resvd[136];
	u32 sys_mem_ls;
	u32 sys_mem_ds;
	u32 sys_mem_sd;
#define NN_MEM_SD		BIT(22)
#define JPEG_MEM_SD		BIT(21)
#define MIPITX_MEM_SD		BIT(20)
#define LCDC_MEM_SD		BIT(19)
#define NAND_MEM_SD		(BIT(17) | BIT(18))
#define ONCHIP_MEM_SD		BIT(16)
#define H265_MEM_SD		BIT(15)
#define DRAM_MEM_SD		BIT(14)
#define CPU_MEM_SD		BIT(13)
#define VIDEO_MEM_SD		(BIT(10) | BIT(11) | BIT(12))
#define ISP_DMA_MEM_SD		BIT(9)
#define ISP_MEM_SD		BIT(8)
#define SDIO1_MEM_SD		BIT(7)
#define SDIO0_MEM_SD		BIT(6)
#define RSA_MEM_SD		BIT(5)
#define GE_MEM_SD		BIT(4)
#define ETH_MEM_SD		BIT(3)
#define CIPHER_MEM_SD		BIT(2)
#define AUDIO_MEM_SD		BIT(1)
#define U2DEV_MEM_SD		BIT(0)
};

struct rts_sysmem_data {
	osMutexId_t				lock;
	struct rts_sysmem_regs *regs;
	//struct reset_controller_dev	rcdev;
};

#define SYS_ISP_MEM_ALL_MASK	0xFFFFFFFF
#define SYS_VIDEO_MEM_ALL_MASK	0xFFFFFFFF

#define RTS_REG_SET(addr, mask)				\
do {							\
	u32 val;					\
	val = REG_R32(addr);				\
	val |= (mask);					\
	REG_W32(addr, val);				\
} while (0)

#define RTS_REG_CLR(addr, mask)				\
do {							\
	u32 val;					\
	val = REG_R32(addr);				\
	val &= ~(mask);					\
	REG_W32(addr, val);				\
} while (0)

struct rts_sysmem_data gbl_sysmem_data={0};

int rts_sysmem_deassert(unsigned long id)
{

	struct rts_sysmem_data *rdata = &gbl_sysmem_data;

	struct rts_sysmem_regs *regs = rdata->regs;

	xSemaphoreTake(rdata->lock, portMAX_DELAY);

	switch (id) {
	case SYS_ISP_MEM:
		RTS_REG_CLR((u32)&regs->sys_mem_sd), ISP_MEM_SD);
printf("DEASSERT SYS_ISP_MEM\n");
		break;

	case SYS_VIDEO_MEM:
		RTS_REG_CLR((u32)&regs->sys_mem_sd), VIDEO_MEM_SD);
printf("DEASSERT SYS_VIDEO_MEM\n");
		break;
#if
	case SYS_MEM_SD_NAND_SPIC:
		RTS_REG_CLR(&regs->sys_mem_sd, NAND_MEM_SD);
printf("DEASSERT SYS_MEM_SD_NAND_SPIC\n");
		break;

	case SYS_MEM_SD_ETH:
		RTS_REG_CLR(&regs->sys_mem_sd, ETH_MEM_SD);
printf("DEASSERT SYS_MEM_SD_ETH\n");
		break;

	case SYS_MEM_SD_CIPHER:
		RTS_REG_CLR(&regs->sys_mem_sd, CIPHER_MEM_SD);
printf("DEASSERT SYS_MEM_SD_CIPHER\n");
		break;

	case SYS_MEM_SD_AUDIO:
		RTS_REG_CLR(&regs->sys_mem_sd, AUDIO_MEM_SD);
printf("DEASSERT SYS_MEM_SD_AUDIO\n");
		break;

	case SYS_MEM_SD_H265:
		RTS_REG_CLR(&regs->sys_mem_sd, H265_MEM_SD);
printf("DEASSERT SYS_MEM_SD_H265\n");
		break;

	case SYS_MEM_SD_U2DEV:
		RTS_REG_CLR(&regs->sys_mem_sd, U2DEV_MEM_SD);
printf("DEASSERT SYS_MEM_SD_U2DEV\n");
		break;

	case SYS_MEM_SD_SDIO0:
		RTS_REG_CLR(&regs->sys_mem_sd, SDIO0_MEM_SD);
printf("DEASSERT SYS_MEM_SD_SDIO0\n");
		break;

	case SYS_MEM_SD_SDIO1:
		RTS_REG_CLR(&regs->sys_mem_sd, SDIO1_MEM_SD);
printf("DEASSERT SYS_MEM_SD_SDIO1\n");
		break;

	case SYS_MEM_SD_GE:
		RTS_REG_CLR(&regs->sys_mem_sd, GE_MEM_SD);
printf("DEASSERT SYS_MEM_SD_GE\n");
		break;

	case SYS_MEM_SD_RSA:
		RTS_REG_CLR(&regs->sys_mem_sd, RSA_MEM_SD);
printf("DEASSERT SYS_MEM_SD_RSA\n");
		break;

	case SYS_MEM_SD_LCDC:
		RTS_REG_CLR(&regs->sys_mem_sd, LCDC_MEM_SD);
printf("DEASSERT SYS_MEM_SD_LCDC\n");
		break;

	case SYS_MEM_SD_MIPITX:
		RTS_REG_CLR(&regs->sys_mem_sd, MIPITX_MEM_SD);
printf("DEASSERT SYS_MEM_SD_MIPITX\n");
		break;

	case SYS_MEM_SD_JPEG:
		RTS_REG_CLR(&regs->sys_mem_sd, JPEG_MEM_SD);
printf("DEASSERT SYS_MEM_SD_JPEG\n");
		break;

	case SYS_MEM_SD_NN:
		RTS_REG_CLR(&regs->sys_mem_sd, NN_MEM_SD);
printf("DEASSERT SYS_MEM_SD_NN\n");
		break;

	default:
		printf("ERROR: invalid sys mem id %ld\n", id);
		break;
	}

	osMutexRelease(rdata->lock);

	return 0;
}

int rts_sysmem_assert(unsigned long id)
{

	struct rts_sysmem_data *rdata = &gbl_sysmem_data;

	struct rts_sysmem_regs *regs = rdata->regs;

	xSemaphoreTake(rdata->lock, portMAX_DELAY);

	switch (id) {
	case SYS_ISP_MEM:
		RTS_REG_SET((u32)(&regs->sys_mem_sd), ISP_MEM_SD);
printf("ASSERT SYS_ISP_MEM\n");
		break;

	case SYS_VIDEO_MEM:
		RTS_REG_SET((u32)(&regs->sys_mem_sd), VIDEO_MEM_SD);
printf("ASSERT SYS_VIDEO_MEM\n");
		break;

	case SYS_MEM_SD_NAND_SPIC:
		RTS_REG_SET((u32)(&regs->sys_mem_sd), NAND_MEM_SD);
printf("ASSERT SYS_MEM_SD_NAND_SPIC\n");
		break;

	case SYS_MEM_SD_ETH:
		RTS_REG_SET((u32)(&regs->sys_mem_sd, ETH_MEM_SD);
printf("ASSERT SYS_MEM_SD_ETH\n");
		break;

	case SYS_MEM_SD_CIPHER:
		RTS_REG_SET(&regs->sys_mem_sd, CIPHER_MEM_SD);
printf("ASSERT SYS_MEM_SD_CIPHER\n");
		break;

	case SYS_MEM_SD_AUDIO:
		RTS_REG_SET(&regs->sys_mem_sd, AUDIO_MEM_SD);
printf("ASSERT SYS_MEM_SD_AUDIO\n");
		break;

	case SYS_MEM_SD_H265:
		RTS_REG_SET(&regs->sys_mem_sd, H265_MEM_SD);
printf("ASSERT SYS_MEM_SD_H265\n");
		break;

	case SYS_MEM_SD_U2DEV:
		RTS_REG_SET(&regs->sys_mem_sd, U2DEV_MEM_SD);
printf("ASSERT SYS_MEM_SD_U2DEV\n");
		break;

	case SYS_MEM_SD_SDIO0:
		RTS_REG_SET(&regs->sys_mem_sd, SDIO0_MEM_SD);
printf("ASSERT SYS_MEM_SD_SDIO0\n");
		break;

	case SYS_MEM_SD_SDIO1:
		RTS_REG_SET(&regs->sys_mem_sd, SDIO1_MEM_SD);
printf("ASSERT SYS_MEM_SD_SDIO1\n");
		break;

	case SYS_MEM_SD_GE:
		RTS_REG_SET(&regs->sys_mem_sd, GE_MEM_SD);
printf("ASSERT SYS_MEM_SD_GE\n");
		break;

	case SYS_MEM_SD_RSA:
		RTS_REG_SET(&regs->sys_mem_sd, RSA_MEM_SD);
printf("ASSERT SYS_MEM_SD_RSA\n");
		break;

	case SYS_MEM_SD_LCDC:
		RTS_REG_SET(&regs->sys_mem_sd, LCDC_MEM_SD);
printf("ASSERT SYS_MEM_SD_LCDC\n");
		break;

	case SYS_MEM_SD_MIPITX:
		RTS_REG_SET(&regs->sys_mem_sd, MIPITX_MEM_SD);
printf("ASSERT SYS_MEM_SD_MIPITX\n");
		break;

	case SYS_MEM_SD_JPEG:
		RTS_REG_SET(&regs->sys_mem_sd, JPEG_MEM_SD);
printf("ASSERT SYS_MEM_SD_JPEG\n");
		break;

	case SYS_MEM_SD_NN:
		RTS_REG_SET(&regs->sys_mem_sd, NN_MEM_SD);
printf("ASSERT SYS_MEM_SD_NN\n");
		break;
#endif
	default:
		printf("ERROR: invalid sys mem id %ld\n", id);
		break;
	}

	osMutexRelease(rdata->lock);

	return 0;
}
#endif
//static const struct reset_control_ops rlx_sysmem_ops = {
//	.assert		= rts_sysmem_assert,
//	.deassert	= rts_sysmem_deassert,
//};

int rts_sysmem_probe(void)
{
#if 0
	struct rts_sysmem_data *rdata;

	rdata = &gbl_sysmem_data;


	rdata->lock = xSemaphoreCreateMutex();

	rdata->regs = (struct rts_sysmem_regs*)SYSMEM_BASE;
	printf("rts_sysmem_probe reg:%08x\n", (unsigned int)rdata->regs);

	REG_W32((u32)(&rdata->regs->sys_mem_ls), 0);
	REG_W32((u32)(&rdata->regs->sys_mem_ds), 0);
#endif
	return RTS_OK;
}
