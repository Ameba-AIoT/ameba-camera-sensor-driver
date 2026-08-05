#ifndef RLX_REG_SYS_H
#define RLX_REG_SYS_H
#include "rlx_reg_base.h"

// 0xB8080000UL
#define RLX_REG_DDR_PHY_SSC2			(DDR_RBUS_BASE + 0x24)
#define RLX_REG_DDR_PHY_SSC3			(DDR_RBUS_BASE + 0x28)
// 0xB8860000UL
#define RLX_REG_FORCE_REG_RESET			(SYS_BASE)				// Force Register Reset
#define RLX_REG_FORCE_REG_RESET_FWC		(SYS_BASE + 0x04)		// Force Register Reset cleared by FW
#define RLX_REG_FORCE_REG_ASYNC_RESET	(SYS_BASE + 0x08)		// Force Register Async Reset
#define RLX_REG_SYS_DDR_PHY_CFG			(SYS_BASE + 0x24)		//
#define RLX_REG_RST_LOAD_MODE			(SYS_BASE + 0x28)		// Reset Load Mode
// 0xB88D0000UL
#define RLX_REG_CLK_CHANGE				(CLK_BASE)				// Clock Change
#define RLX_REG_UART_CLK_LP_EN			(CLK_BASE + 0x04)		// Uart Clock Low Power Enable
//#define RLX_REG_MCU_SCAN_CLK_CFG		(CLK_BASE + 0x08)		// Clock Source Select
#define RLX_REG_DRAM_CLK_CFG			(CLK_BASE + 0x0C)		// Clock Source Select
#define RLX_REG_CPU_CLK_CFG				(CLK_BASE + 0x10)		// Clock Source Select
#define RLX_REG_XB2_CLK_CFG				(CLK_BASE + 0x14)		// Clock Source Select
#define RLX_REG_BUS_CLK_CFG				(CLK_BASE + 0x18)		// Clock Source Select
#define RLX_REG_I2S_CLK_CFG				(CLK_BASE + 0x1C)		// Clock Source Select
#define RLX_REG_CIPHER_CLK_CFG			(CLK_BASE + 0x20)		// Clock Source Select
//#define RLX_REG_ETHERNET_CLK_CFG		(CLK_BASE + 0x24)		// Clock Source Select
#define RLX_REG_UART_CLK_CFG			(CLK_BASE + 0x28)		// Clock Source Select
#define RLX_REG_I2C_CLK_CFG				(CLK_BASE + 0x2C)		// Clock Source Select
//#define RLX_REG_H264_CLK_CFG			(CLK_BASE + 0x30)		// Clock Source Select
//#define RLX_REG_RC_CLK_CFG				(CLK_BASE + 0x34)		// RC Clock Select Reg
//#define RLX_REG_RC_OSC_POW_CFG			(CLK_BASE + 0x38)		// RC OSC Pow
#define RLX_REG_RTC32K_DIV_CFG0			(CLK_BASE + 0x3C)		// RTC32K Div Cfg0
#define RLX_REG_RTC32K_DIV_CFG1			(CLK_BASE + 0x40)		// RTC32K Div Cfg1
#define RLX_REG_RTC32K_DIV_CFG2			(CLK_BASE + 0x44)		// RTC32K Div Cfg2
#define RLX_REG_RTC_CLK_CFG				(CLK_BASE + 0x48)		// RTC Clock Cfg
#define RLX_REG_USBPHY_CLK_CFG			(CLK_BASE + 0x4C)		// Clock Source Select
#define RLX_REG_JPEG_CLK_CFG			(CLK_BASE + 0x50)		// Clock Source Select
//#define RLX_REG_PLL_BYPASS_CFG			(CLK_BASE + 0x54)		// Clock Source Select
#define RLX_REG_ISP_SCAN_CLK_CFG		(CLK_BASE + 0x58)		// Clock Source Select
#define RLX_REG_MIPI_SCAN_CLK_CFG		(CLK_BASE + 0x5C)		// Clock Source Select
#define RLX_REG_SPDIF_CLK_CFG			(CLK_BASE + 0x60)		// Clock Source Select
//#define RLX_REG_PLATFORM_CONFIGURATION	(CLK_BASE + 0x64)		// Clock Source Select
#define RLX_REG_CODEC_CLK_CFG			(CLK_BASE + 0x68)		// Audio Clock Source Select
//#define RLX_REG_VIDEO_CLK_SEL			(CLK_BASE + 0x6C)		// Video Clock Source Select
#define RLX_REG_GE_CLK_EN				(CLK_BASE + 0x78)		// 
#define RLX_REG_H265_ACLK_CFG			(CLK_BASE + 0x80)		// 
#define RLX_REG_H265_BCLK_CFG			(CLK_BASE + 0x84)		// 
#define RLX_REG_H265_CCLK_CFG			(CLK_BASE + 0x88)		// 
#define RLX_REG_SSOR_HCLK_CFG			(CLK_BASE + 0x8C)		// 
#define RLX_REG_SSOR_CLK_OE				(CLK_BASE + 0x90)		// 
#define RLX_REG_RSA_CLK_EN				(CLK_BASE + 0xA0)		// 
#define RLX_REG_SHA_CLK_EN				(CLK_BASE + 0xA4)		// 
#define RLX_REG_NN_BUS_CLK_CFG			(CLK_BASE + 0xB0)		// 
#define RLX_REG_NN_CORE_CLK_CFG			(CLK_BASE + 0xB4)		// 
#define RLX_REG_TRNG_CLK_CFG			(CLK_BASE + 0xBC)		// 
#define RLX_REG_LCDC_DRAM_CLK_CFG		(CLK_BASE + 0xC0)		// 
#define RLX_REG_ETHERNET_CLK_CFG		(CLK_BASE + 0xC4)		// 
#define RLX_REG_EFUSE_CLK_CFG			(CLK_BASE + 0xC8)		// 
#define RLX_REG_MAC_BYPASS_CLK_CFG		(CLK_BASE + 0xCC)		// 
#define RLX_REG_JPEG_DRAM_CLK_CFG		(CLK_BASE + 0xD0)		// 
#define RLX_REG_MIPI_TX_CFG				(CLK_BASE + 0xD4)		// 
#define RLX_REG_DMA_CLK_CFG				(CLK_BASE + 0xD8)		// 
#define RLX_REG_MIPI_TX_LOW_CLK_CFG		(CLK_BASE + 0xDC)		// 
// 0xB8864100UL
#define RLX_REG_SYS_PLL0_CTRL			(SYS_PLL0_BASE)			// PLL0 Control
#define RLX_REG_SYS_PLL0_CFG			(SYS_PLL0_BASE + 0x04)	// PLL0 Config
#define RLX_REG_SYS_PLL0_SCCG_CFG0		(SYS_PLL0_BASE + 0x08)	// PLL0 SSCG Config0
#define RLX_REG_SYS_PLL0_SCCG_CFG1		(SYS_PLL0_BASE + 0x0C)	// PLL0 SSCG Config1
#define RLX_REG_SYS_PLL0_WDOG			(SYS_PLL0_BASE + 0x10)	// PLL0 WDOG
#define RLX_REG_SYS_PLL0_STATUS			(SYS_PLL0_BASE + 0x14)	// PLL0 Status
// 0xB8864200UL
#define RLX_REG_SYS_PLL1_CTRL			(SYS_PLL1_BASE)			// PLL1 Control
#define RLX_REG_SYS_PLL1_CFG			(SYS_PLL1_BASE + 0x04)	// PLL1 Config
#define RLX_REG_SYS_PLL1_SCCG_CFG0		(SYS_PLL1_BASE + 0x08)	// PLL1 SSCG Config0
#define RLX_REG_SYS_PLL1_SCCG_CFG1		(SYS_PLL1_BASE + 0x0C)	// PLL1 SSCG Config1
#define RLX_REG_SYS_PLL1_WDOG			(SYS_PLL1_BASE + 0x10)	// PLL1 WDOG
#define RLX_REG_SYS_PLL1_STATUS			(SYS_PLL1_BASE + 0x14)	// PLL1 Status
// 0xB8864300UL
#define RLX_REG_SYS_PLL2_CTRL			(SYS_PLL2_BASE)			// PLL2 Control
#define RLX_REG_SYS_PLL2_CFG			(SYS_PLL2_BASE + 0x04)	// PLL2 Config
#define RLX_REG_SYS_PLL2_SCCG_CFG0		(SYS_PLL2_BASE + 0x08)	// PLL2 SSCG Config0
#define RLX_REG_SYS_PLL2_SCCG_CFG1		(SYS_PLL2_BASE + 0x0C)	// PLL2 SSCG Config1
#define RLX_REG_SYS_PLL2_WDOG			(SYS_PLL2_BASE + 0x10)	// PLL2 WDOG
#define RLX_REG_SYS_PLL2_STATUS			(SYS_PLL2_BASE + 0x14)	// PLL2 Status
// 0xB8864400UL
#define RLX_REG_SYS_PLL3_CTRL			(SYS_PLL3_BASE)			// PLL3 Control
#define RLX_REG_SYS_PLL3_CFG			(SYS_PLL3_BASE + 0x04)	// PLL3 Config
#define RLX_REG_SYS_PLL3_SCCG_CFG0		(SYS_PLL3_BASE + 0x08)	// PLL3 SSCG Config0
#define RLX_REG_SYS_PLL3_SCCG_CFG1		(SYS_PLL3_BASE + 0x0C)	// PLL3 SSCG Config1
#define RLX_REG_SYS_PLL3_WDOG			(SYS_PLL3_BASE + 0x10)	// PLL3 WDOG
#define RLX_REG_SYS_PLL3_STATUS			(SYS_PLL3_BASE + 0x14)	// PLL3 Status
// 0xB8866000UL
#define RLX_REG_SYS_MEM_LS				(SYS_MEM_BASE + 0x20)	// System Memory Light Sleep Reg
#define RLX_REG_SYS_MEM_DS				(SYS_MEM_BASE + 0x30)	// System Memory Deep  Sleep Reg
#define RLX_REG_SYS_ISP_MEM_DS			(SYS_MEM_BASE + 0x40)	// System ISP   Memory Shutdown Reg
#define RLX_REG_SYS_VIDEO_MEM_DS		(SYS_MEM_BASE + 0x44)	// System Video Memory Shutdown Reg
#define RLX_REG_SYS_MEM_SD				(SYS_MEM_BASE + 0x48)	// System Memory Shutdown Reg
// 0xB886F000UL
#define RLX_REG_HW_ID					(SYS_VER_BASE + 0x10)

#define RLX_REG_WATCHDOG_CFG			(WDOG_BASE + 0x0000)
#define RLX_REG_WATCHDOG_CTL			(WDOG_BASE + 0x0004)
#define RLX_REG_WATCHDOG_INT_ENABLE		(WDOG_BASE + 0x0008)
#define RLX_REG_WATCHDOG_INT_FLAG		(WDOG_BASE + 0x000c)

#endif	// RLX_REG_SYS_H
