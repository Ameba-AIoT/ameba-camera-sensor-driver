/*
 * Realtek Semiconductor Corp.
 *
 * force reset driver
 *
 * Copyright (C) 2014      Wei WANG (wei_wang@realsil.com.cn)
 */


#include "cmsis_os2.h"
#include "rt_types.h"
#include "rts_errno.h"
#include <reset/rts-resets.h>
#include "rlx_irq.h"
#include "rlx_reg.h"
#include "isp_log.h"
#include "rtx_mutex.h"

#define FORCE_BUS_SD1_RESET		BIT(9)
#define FORCE_BUS_VIDEO_RESET		BIT(8)
#define FORCE_BUS_SD0_RESET		BIT(7)
#define FORCE_BUS_I2S_RESET		BIT(6)
#define FORCE_BUS_U2DEV_RESET		BIT(5)
#define FORCE_BUS_U2HOST_RESET		BIT(4)
#define FORCE_BUS_RESET			BIT(3)
#define FORCE_XB2_RESET			BIT(2)
#define FORCE_CPU_RESET			BIT(1)
#define FORCE_DRAM_RESET		BIT(0)

#define FORCE_DRAM_LCDC_RESET		BIT(13)
#define FORCE_BUS_SHA256_RESET		BIT(12)
#define FORCE_DRAM_RSA_RESET		BIT(11)
#define FORCE_DRAM_GE_RESET		BIT(10)
#define FORCE_FEPHY_RESET		BIT(5)
#define FORCE_LCDC_RESET		BIT(4)
#define FORCE_RTC32K_RESET		BIT(3)
#define FORCE_U2DEV_UTMI_RESET		BIT(2)
#define FORCE_U2HOST_UTMI_RESET		BIT(1)

#define FORCE_MIPI_TX_CLK_ASYNC_RESET	BIT(21)
#define FORCE_DRAM_JPG_CLK_ASYNC_RESET	BIT(20)
#define FORCE_NN_CORE_CLK_ASYNC_RESET	BIT(19)
#define FORCE_DRAM_NN_CLK_ASYNC_RESET	BIT(18)
#define FORCE_EFUSE_CLK_ASYNC_RESET	BIT(17)
#define FORCE_TRNG_CLK_ASYNC_RESET	BIT(16)
#define FORCE_SD1_CLK_ASYNC_RESET	BIT(15)
#define FORCE_H265_CCLK_ASYNC_RESET	BIT(14)
#define FORCE_H265_BCLK_ASYNC_RESET	BIT(13)
#define FORCE_H265_ACLK_ASYNC_RESET	BIT(12)
#define FORCE_CODEC_CLK_ASYNC_RESET	BIT(11)
#define FORCE_SPDIF_CLK_ASYNC_RESET	BIT(10)
#define FORCE_H264_ASYNC_RESET          BIT(9)
#define FORCE_I2C_CLK_ASYNC_RESET	BIT(8)
#define FORCE_UART_CLK_ASYNC_RESET	BIT(7)
#define FORCE_ETHERNET_CLK_ASYNC_RESET	BIT(6)
#define FORCE_SD0_CLK_ASYNC_RESET	BIT(5)
#define FORCE_CIPHER_CLK_ASYNC_RESET	BIT(4)
#define FORCE_I2S_CLK_ASYNC_RESET	BIT(3)
#define FORCE_ISP_CLK_ASYNC_RESET	BIT(2)
#define FORCE_JPG_CLK_ASYNC_RESET	BIT(1)
#define FORCE_MIPI_CLK_ASYNC_RESET	BIT(0)

struct rts_force_reset_regs {
	u32 force_reg_reset;
	u32 force_reg_reset_fwc;
	u32 force_reg_async_reset;
};

/**
 * struct reset_control_ops
 *
 * @reset: for self-deasserting resets, does all necessary
 *         things to reset the device
 * @assert: manually assert the reset line, if supported
 * @deassert: manually deassert the reset line, if supported
 * @status: return the status of the reset line, if supported
 */
struct reset_control_ops {
        int (*reset)(unsigned long id);
        int (*assert)(unsigned long id);
        int (*deassert)(unsigned long id);
        int (*status)(unsigned long id);
};

struct rts_reset_data {
	osMutexId_t				lock;
	struct rts_force_reset_regs *regs;
	const struct reset_control_ops *ops;
};

#define ALL_MASK	0xFFFFFFFF

#define RTS_FRR_SET(addr, mask)				\
do {							\
	u32 val;					\
	val = *((u32*)(addr));				\
	val |= (mask);					\
	*((u32*)(addr)) = val;				\
} while (0)

#define RTS_FRR_CLR(addr, mask)				\
do {							\
	u32 val;					\
	val = *((u32*)(addr));				\
	val &= ~(mask);					\
	*((u32*)(addr)) = val;				\
} while (0)

#define RTS_FORCE_RESET_AUTO(addr, mask)	RTS_FRR_SET(addr, mask)

#define RTS_FORCE_RESET(addr, mask)			\
do {							\
	RTS_FRR_SET(addr, mask);			\
	RTS_FRR_CLR(addr, mask);			\
} while (0)

static struct rts_reset_data gbl_freset={0};

int rts_sys_force_reset(unsigned long id)
{
	struct rts_reset_data *rdata = &gbl_freset;
	int ret = 0;

	//struct rts_force_reset_regs *regs = rdata->regs;

	ret = xSemaphoreTake(rdata->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rts_sys_force_reset wait rdata->lock timeout\n\r");
		return -ETIMEDOUT;
	}

	switch (id) {

	case FORCE_RESET_VIDEO:
		//RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
		//	FORCE_BUS_VIDEO_RESET);
		isp_info("%s FORCE_RESET_VIDEO\r\n", __func__);
		break;

	case FORCE_RESET_ISP:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_ISP_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_ISP\r\n", __func__);
		break;

	case FORCE_RESET_MIPI:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_MIPI_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_MIPI\r\n", __func__);
		break;

#if 0



	case FORCE_RESET_H264:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_H264_ASYNC_RESET);
		isp_info("%s FORCE_RESET_H264\r\n", __func__);
		break;

	case FORCE_RESET_JPG:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_JPG_CLK_ASYNC_RESET);
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_DRAM_JPG_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_JPG\r\n", __func__);
		break;

	case FORCE_RESET_MIPI:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_MIPI_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_MIPI\r\n", __func__);
		break;

	case FORCE_RESET_SDIO0:
		//RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
		//	FORCE_BUS_SD0_RESET);
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_SD0_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_SDIO0\r\n", __func__);
		break;

	case FORCE_RESET_SDIO1:
		//RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
		//	FORCE_BUS_SD1_RESET);
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_SD1_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_SDIO1\r\n", __func__);
		break;

	case FORCE_RESET_CIPHER:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//	FORCE_CIPHER_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_CIPHER\r\n", __func__);
		break;

	case FORCE_RESET_CODEC:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
				FORCE_CODEC_CLK_ASYNC_RESET);
		//isp_info("%s FORCE_RESET_CODEC\r\n", __func__);
		break;

	case FORCE_RESET_I2S:
		//RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
		//	FORCE_BUS_I2S_RESET);
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//		FORCE_I2S_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_I2S\r\n", __func__);
		break;

	case FORCE_RESET_SPDIF:
		//RTS_FORCE_RESET(&regs->force_reg_async_reset,
		//		FORCE_SPDIF_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_SPDIF\r\n", __func__);
		break;

	case FORCE_RESET_I2C:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_I2C_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_I2C\r\n", __func__);
		break;

	case FORCE_RESET_U2DEV:
		RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
			FORCE_BUS_U2DEV_RESET);
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_U2DEV_UTMI_RESET);
		isp_info("%s FORCE_RESET_U2DEV\r\n", __func__);
		break;

	case FORCE_RESET_U2HOST:
		RTS_FORCE_RESET_AUTO(&regs->force_reg_reset,
			FORCE_BUS_U2HOST_RESET);
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_U2HOST_UTMI_RESET);
		isp_info("%s FORCE_RESET_U2HOST\r\n", __func__);
		break;

	case FORCE_RESET_ISP:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_ISP_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_ISP\r\n", __func__);
		break;

	case FORCE_RESET_UART:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_UART_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_UART\r\n", __func__);
		break;

	case FORCE_RESET_ETHERNET:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_ETHERNET_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_ETHERNET\r\n", __func__);
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
printf("%s FORCE_RESET_H265_AXI\r\n", __func__);
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_H265_BPU\r\n", __func__);
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_H265_CORE\r\n", __func__);
		break;

	case FORCE_RESET_H265:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_H265\r\n", __func__);
		break;

	case FORCE_RESET_GE:
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_GE_RESET);
		isp_info("%s FORCE_RESET_GE\r\n", __func__);
		break;

	case FORCE_RESET_RSA:
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_RSA_RESET);
		isp_info("%s FORCE_RESET_RSA\r\n", __func__);
		break;

	case FORCE_RESET_SHA256:
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_BUS_SHA256_RESET);
		isp_info("%s FORCE_RESET_SHA256\r\n", __func__);
		break;

	case FORCE_RESET_TRNG:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_TRNG_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_TRNG\r\n", __func__);
		break;

	case FORCE_RESET_DRAM_LCDC:
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_LCDC_RESET);
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_LCDC_RESET);
		isp_info("%s FORCE_RESET_DRAM_LCDC\r\n", __func__);
		break;

	case FORCE_RESET_FEPHY:
		RTS_FORCE_RESET(&regs->force_reg_reset_fwc,
			FORCE_FEPHY_RESET);
		isp_info("%s FORCE_RESET_FEPHY\r\n", __func__);
		break;

	case FORCE_RESET_EFUSE:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_EFUSE_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_EFUSE\r\n", __func__);
		break;

	case FORCE_RESET_NN:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_DRAM_NN_CLK_ASYNC_RESET);
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_NN_CORE_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_NN\r\n", __func__);
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FORCE_RESET(&regs->force_reg_async_reset,
			FORCE_MIPI_TX_CLK_ASYNC_RESET);
		isp_info("%s FORCE_RESET_MIPI_TX\r\n", __func__);
		break;
#endif
	default:
		isp_error("ERROR: invalid reset model %ld\r\n", id);
		break;
	}

//	osMutexRelease(rdata->lock);
	xSemaphoreGive(rdata->lock);
	return 0;
}

int rts_sys_reset_deassert(unsigned long id)
{
#if 0
	struct rts_reset_data *rdata = &gbl_freset;
	struct rts_force_reset_regs *regs = rdata->regs;

	xSemaphoreTake(rdata->lock, portMAX_DELAY);

	switch (id) {
	case FORCE_RESET_ETHERNET:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_ETHERNET_CLK_ASYNC_RESET);
printf("DEASSERT FORCE_RESET_ETHERNET\n");
		break;

	case FORCE_RESET_FEPHY:
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_FEPHY_RESET);
printf("DEASSERT FORCE_RESET_FEPHY\n");
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
printf("DEASSERT FORCE_RESET_H265_AXI\n");
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
printf("DEASSERT FORCE_RESET_H265_BPU\n");
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
printf("DEASSERT FORCE_RESET_H265_CORE\n");
		break;

	case FORCE_RESET_H265:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
printf("DEASSERT FORCE_RESET_H265\n");
		break;

	case FORCE_RESET_CIPHER:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_CIPHER_CLK_ASYNC_RESET);
printk("DEASSERT FORCE_RESET_CIPHER\n");
		break;

	case FORCE_RESET_GE:
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_DRAM_GE_RESET);
printk("DEASSERT FORCE_RESET_GE\n");
		break;

	case FORCE_RESET_DRAM_LCDC:
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_DRAM_LCDC_RESET);
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_LCDC_RESET);
printk("DEASSERT FORCE_RESET_DRAM_LCDC\n");
		break;

	case FORCE_RESET_RSA:
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_DRAM_RSA_RESET);
printk("DEASSERT FORCE_RESET_RSA\n");
		break;

	case FORCE_RESET_SHA256:
		RTS_FRR_CLR(&regs->force_reg_reset_fwc,
			FORCE_BUS_SHA256_RESET);
printk("DEASSERT FORCE_RESET_SHA256\n");
		break;

	case FORCE_RESET_NN:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_DRAM_NN_CLK_ASYNC_RESET);
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_NN_CORE_CLK_ASYNC_RESET);
printk("DEASSERT FORCE_RESET_NN\n");
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FRR_CLR(&regs->force_reg_async_reset,
			FORCE_MIPI_TX_CLK_ASYNC_RESET);
printk("DEASSERT FORCE_RESET_MIPI_TX\n");
		break;

	default:
		printf("ERROR: invalid deassert model %ld\n", id);
		break;
	}

	osMutexRelease(rdata->lock);
#endif
	return 0;
}

int rts_sys_reset_assert(unsigned long id)
{
#if 0
	struct rts_reset_data *rdata = &gbl_freset;
	struct rts_force_reset_regs *regs = rdata->regs;

	xSemaphoreTake(rdata->lock, portMAX_DELAY);

	switch (id) {

	case FORCE_RESET_ETHERNET:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_ETHERNET_CLK_ASYNC_RESET);
printf("ASSERT FORCE_RESET_ETHERNET\n");
		break;

	case FORCE_RESET_FEPHY:
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_FEPHY_RESET);
printf("ASSERT FORCE_RESET_FEPHY\n");
		break;

	case FORCE_RESET_H265_AXI:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
printf("ASSERT FORCE_RESET_H265_AXI\n");
		break;

	case FORCE_RESET_H265_BPU:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
printf("ASSERT FORCE_RESET_H265_BPU\n");
		break;

	case FORCE_RESET_H265_CORE:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
printf("ASSERT FORCE_RESET_H265_CORE\n");
		break;

	case FORCE_RESET_H265:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_ACLK_ASYNC_RESET);
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_BCLK_ASYNC_RESET);
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_H265_CCLK_ASYNC_RESET);
printf("ASSERT FORCE_RESET_H265\n");
		break;

	case FORCE_RESET_CIPHER:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_CIPHER_CLK_ASYNC_RESET);
printk("ASSERT FORCE_RESET_CIPHER\n");
		break;

	case FORCE_RESET_GE:
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_GE_RESET);
printk("ASSERT FORCE_RESET_GE\n");
		break;

	case FORCE_RESET_DRAM_LCDC:
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_LCDC_RESET);
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_LCDC_RESET);
printk("ASSERT FORCE_RESET_DRAM_LCDC\n");
		break;

	case FORCE_RESET_RSA:
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_DRAM_RSA_RESET);
printk("ASSERT FORCE_RESET_RSA\n");
		break;

	case FORCE_RESET_SHA256:
		RTS_FRR_SET(&regs->force_reg_reset_fwc,
			FORCE_BUS_SHA256_RESET);
printk("ASSERT FORCE_RESET_SHA256\n");
		break;

	case FORCE_RESET_NN:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_DRAM_NN_CLK_ASYNC_RESET);
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_NN_CORE_CLK_ASYNC_RESET);
printk("ASSERT FORCE_RESET_NN\n");
		break;

	case FORCE_RESET_MIPI_TX:
		RTS_FRR_SET(&regs->force_reg_async_reset,
			FORCE_MIPI_TX_CLK_ASYNC_RESET);
printk("ASSERT FORCE_RESET_MIPI_TX\n");
		break;

	default:
		printf("ERROR: invalid assert model %ld\n", id);
		break;
	}

	osMutexRelease(rdata->lock);
#endif
	return 0;
}

static const struct reset_control_ops rlx_reset_ops = {
	.reset		= rts_sys_force_reset,
	.assert		= rts_sys_reset_assert,
	.deassert	= rts_sys_reset_deassert,
};
#if 0
static void rts_force_reset_hw_init(struct rts_force_reset_regs *regs)
{
	RTS_FRR_SET(&regs->force_reg_reset_fwc, FORCE_U2DEV_UTMI_RESET |
			FORCE_U2HOST_UTMI_RESET);
	RTS_FRR_SET(&regs->force_reg_async_reset,
			ALL_MASK & ~(FORCE_EFUSE_CLK_ASYNC_RESET |
				FORCE_UART_CLK_ASYNC_RESET |
				FORCE_I2C_CLK_ASYNC_RESET));
}
#endif

int rts_reset_probe(void)
{
	struct rts_reset_data *rdata;

	rdata = &gbl_freset;

	rdata->lock = xSemaphoreCreateMutex();
	if ( !rdata->lock ) {
		isp_error("reset lock mutex alloc fail\r\n");
		return RTS_FAIL;
	}



	rdata->regs = (struct rts_force_reset_regs*)RESET_BASE;
	isp_info("rts_reset_probe %08x\r\n", (int)rdata->regs);

	//rdata->rcdev.owner = THIS_MODULE;
	//rdata->rcdev.nr_resets = FORCE_RESET_MAX;
	rdata->ops = &rlx_reset_ops;
	//rdata->rcdev.of_node = pdev->dev.of_node;
#if defined(_SYSTEM_CONNECT_READY_)
	rts_force_reset_hw_init(rdata->regs);
#endif
	//return devm_reset_controller_register(&pdev->dev, &rdata->rcdev);
	return RTS_OK;
}

int rts_reset_remove(void)
{
	//struct rts_reset_data *rdata = &gbl_freset;

	//reset_controller_unregister(&rdata->rcdev);

	return RTS_OK;
}

//static const struct of_device_id rts_reset_dt_ids[] = {
//	 { .compatible = "realtek,rts3915-reset", },
//	 { /* sentinel */ },
//};

//static struct platform_driver rts_reset_driver = {
//	.probe	= rts_reset_probe,
//	.remove	= rts_reset_remove,
//	.driver = {
//		.name		= "rts-reset",
//		.of_match_table	= of_match_ptr(rts_reset_dt_ids),
//	},
//};
//
//static int __init rts_reset_init(void)
//{
//	return platform_driver_register(&rts_reset_driver);
//}
//postcore_initcall(rts_reset_init);
//
//static void __exit rts_reset_exit(void)
//{
//	platform_driver_unregister(&rts_reset_driver);
//}
//module_exit(rts_reset_exit);
