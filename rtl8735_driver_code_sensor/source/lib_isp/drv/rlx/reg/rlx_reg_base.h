#ifndef RLX_REG_BASE_H
#define RLX_REG_BASE_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#define PLLMAP_BASE			0x40300000UL	// PLL Mapped
#define SYS_BASE			0x40300000UL	// System
#define LVDS_PLLMAP_BASE	0x40300000UL	// LVDS PLL Mapped
#define RESET_BASE			0x40300000UL	// Reset
#define SYSMEM_BASE			0x40300000UL	// System Mem
#define MD_BASE				0x40312000UL	// motion detection
#define ZOOM_BASE			0x40310000UL	// ZOOM
#define VERIFY_BASE			0x403B0000UL	// Verify

#define OSD_ENC_BASE		0x403E0000UL	// OSD
#define SOC_CAM_BASE		0x403F0000UL	// Video Input

#if 0
#include "sheipa.h"

#define DDR_BASE			0xB8010000UL	// DDR controller
#define DMA_BASE			0xB8020000UL	// DMA controller
#define SPI_BASE			0xB8030000UL	// SPI controller
#define ISP_MCU_BASE		0xB8040000UL	// Interfaces between CPU and MCU
#define ISP_IMG_BASE		0xB8040100UL	// Interfaces between CPU and ISP
#define ISP_SPI_BASE		0xB8040400UL	// Interfaces between CPU and SPI
#define ISP_INT_BASE		0xB8040500UL	// CPU Interrupters register
#define ISP_CMD_BASE		0xB8041000UL	// ISP Cmd Data between CPU and MCU

#define JPEG_BASE			0xB805E000UL
#define OSD2_BASE			0xB805C000UL
#define H264_BASE			0xB8060000UL
#define DDR_RBUS_BASE		0xB8080000UL	// DDR_RBUS
#define BIST_BASE			0xB80A0000UL	// DDRC BIST controller

#define USB_EHCI_BASE		0xB8100000UL	// USB2.0 Host EHCI
#define USB_OHCI_BASE		0xB8180000UL	// USB2.0 Host OHCI
#define USB_OTG_BASE		0xB8200000UL	// USB2.0 OTG
#define SDIO_BASE			0xB8300000UL
#define ETH_BASE			0xB8400000UL	// Ethernet
#define I2S_MIC_BASE		0xB8500000UL	// I2S & MIC controller
#define AES_BASE			0xB8600000UL	// AES/DES controller
#define GPIO_BASE			0xB8800000UL
#define UART_BASE			0xB8810000UL	// UARTx3 & Timer
#define TIMER_BASE			(UART_BASE)
#define PWM_BASE			0xB8820000UL	// PWMx4
#define SARADC_BASE			0xB8840000UL
#define RTC_BASE			0xB8850000UL

#define PLLMAP_BASE			0xB88B0000UL	// PLL Mapped
#define LVDS_PLLMAP_BASE	0xB8C80000UL	// LVDS PLL Mapped
#define SYSMEM_BASE			0xB88C0000UL	// System Mem
#define SYS_BASE			0xB88D0000UL	// System
#define CLK_BASE			0xB88D0000UL	// Clock
#define RESET_BASE			0xB88D8000UL	// Reset
#define WDOG_BASE			0xB88DA000UL	// Watchdog
#define SYS_PLL0_BASE		0xB8864100UL	// PLL0 Controller
#define SYS_PLL1_BASE		0xB8864200UL	// PLL1 Controller
#define SYS_PLL2_BASE		0xB8864300UL	// PLL2 Controller
#define SYS_PLL3_BASE		0xB8864400UL	// PLL3 Controller
#define SYS_MEM_BASE		0xB8866000UL	// Memory Power control
#define SYS_VER_BASE		0xB886F000UL	// System Version

#define I2C0_BASE			0xB8880000UL
#define I2C1_BASE			0xB8881000UL
#define SF_BASE				0xBC000000UL
#define SF_BOOT_BASE		0xBFC00000UL	// SPI Flash Low 4MB for boot

#define ISP_BASE			0xB8A00000UL	// ISP
#define ZOOM_BASE			0xB8A00000UL	// ZOOM
#define VERIFY_BASE			0xB8A0B000UL	// Verify

#define OSD_ENC_BASE		0xB8AE0000UL	// OSD
#define SOC_CAM_BASE		0xB8AF0000UL	// Video Input

#endif

#endif	// RLX_REG_BASE_H

