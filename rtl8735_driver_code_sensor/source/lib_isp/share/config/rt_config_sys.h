#ifndef __RT_CONFIG_SYS_H__
#define __RT_CONFIG_SYS_H__

// ----------------------------------------------------------------------------
//  build code features
// ----------------------------------------------------------------------------
// brief: use hconf or not.
#define CFG_FEATURE_HCONF				0
// brief: MMF framework & app
#define CFG_FEATURE_MMF					1

// ----------------------------------------------------------------------------
//  hconf, MTD
// ----------------------------------------------------------------------------
// value: 0, 1
#define CFG_HCONF_FROM_SF				0
// caution! this value must be multiple of RT_SF_READ_UNIT_SZ(= 32).
#define CFG_UBOOT_HCONF_SIZE			512

#if (CFG_UBOOT_HCONF_SIZE % 32)
#error CFG_UBOOT_HCONF_SIZE value is not multiple of 32 !!!!!!!!!!!!
#endif

#define CFG_HCONF_MAX_SIZE				SZ_4K

// ----------------------------------------------------------------------------
//  TASK
// ----------------------------------------------------------------------------
#define CFG_TASK_MAX_NUM				36
#define CFG_TASK_MAX_PRIORITY			(configMAX_PRIORITIES - 1)
#define CFG_TASK_USER_PRIORITY			3

#define CFG_TASK_MAIN_NAME				"main_thre"
#define CFG_TASK_MAIN_PRIORITY			1
#define CFG_TASK_MAIN_DELAY				pdMS_TO_TICKS(1000)

#define CFG_TASK_SHELL_NAME				"SHELL"
#define CFG_TASK_SHELL_PRIORITY			1
#define CFG_TASK_SHELL_DELAY			pdMS_TO_TICKS(20)
#define CFG_TASK_SHELL_STACK_SIZE		SZ_8K

#define CFG_TASK_ETH_NAME				"eth_task"
#define CFG_TASK_ETH_PRIORITY			CFG_TASK_USER_PRIORITY
#define CFG_TASK_ETH_DELAY				pdMS_TO_TICKS(10)
#define CFG_TASK_ETH_STACK_SIZE			SZ_1K

#define CFG_TASK_ISP_NAME_0				"isp_task0"
#define CFG_TASK_ISP_NAME_1				"isp_task1"
#define CFG_TASK_ISP_NAME_2				"isp_task2"

#define CFG_TASK_ISP_PRIORITY			4  //CFG_TASK_USER_PRIORITY
#define CFG_TASK_ISP_DELAY				0
#define CFG_TASK_ISP_STACK_SIZE			SZ_8K

#define CFG_TASK_FWD_NAME				"fwd_task"
#define CFG_TASK_FWD_PRIORITY			CFG_TASK_USER_PRIORITY
#define CFG_TASK_FWD_DELAY				pdMS_TO_TICKS(20)
#define CFG_TASK_FWD_STACK_SIZE			SZ_1K

#define CFG_TASK_AUDIO_TX_NAME			"audio_tx"
#define CFG_TASK_AUDIO_TX_PRIORITY		CFG_TASK_USER_PRIORITY
#define CFG_TASK_AUDIO_TX_DELAY			0
#define CFG_TASK_AUDIO_TX_STACK_SIZE	SZ_8K

#define CFG_TASK_AUDIO_RX_NAME			"audio_rx"
#define CFG_TASK_AUDIO_RX_PRIORITY		CFG_TASK_USER_PRIORITY
#define CFG_TASK_AUDIO_RX_DELAY			0
#define CFG_TASK_AUDIO_RX_STACK_SIZE	SZ_8K

// note: the below macro will apply to all siso task.
// note: the siso task name is gen dynamically.
#define CFG_TASK_SISO_PRIORITY			CFG_TASK_USER_PRIORITY
#define CFG_TASK_SISO_DELAY				pdMS_TO_TICKS(10)
#define CFG_TASK_SISO_STACK_SIZE		SZ_1K

#define CFG_TASK_SIMO_PRIORITY			CFG_TASK_USER_PRIORITY
#define CFG_TASK_SIMO_DELAY				pdMS_TO_TICKS(10)
#define CFG_TASK_SIMO_STACK_SIZE		SZ_1K

#define CFG_TASK_MMC_NAME				"mmc_task"
#define CFG_TASK_MMC_PRIORITY			CFG_TASK_USER_PRIORITY
#define CFG_TASK_MMC_DELAY				pdMS_TO_TICKS(200)
#define CFG_TASK_MMC_STACK_SIZE			SZ_1K

// ----------------------------------------------------------------------------
//  main & rt_cmd_mtd
//  brief: default setting for sf probe cmd
//  note : it is better not change values in this section.
// ----------------------------------------------------------------------------
// value: max hz
#define CFG_SF_PROBE_SPEED				1000000
// value: 0~3, means SPI_MODE_(0~3)
#define CFG_SF_PROBE_MODE				3
#define CFG_SF_PROBE_CS					0
#define CFG_SF_PROBE_BUS				0

// ----------------------------------------------------------------------------
//  isp, ispfw
// ----------------------------------------------------------------------------
#define CFG_ISP_MAX_CHNS				5
// value: 10, 15, 20, 30
#define CFG_ISP_SENSOR_FPS				15

#define CFG_ISP_TASK_FPS_0				15
#define CFG_ISP_TASK_FPS_1				15
#define CFG_ISP_TASK_FPS_2				5

#define CFG_OSD_SUPPORT_MAX_CHNS		4

#define check_chn_id(n)		((((n) >= 0) && ((n) < CFG_OSD_SUPPORT_MAX_CHNS)) ? TRUE : FALSE)
// ----------------------------------------------------------------------------
//  mmf
// ----------------------------------------------------------------------------
// brief: conn module name max length
// note: it is recommand to set 10 because it is also max FreeRTOS task name length.
//
#define CFG_MMF_MAX_CONN_NAME			10
#define CFG_MMF_MAX_VENCS				2
#define CFG_MMF_MAX_VOUTS				2

// note:
//  in our real experiments, it show us when video size > VGA,
//  the savefile behavior will affect the rtsp streaming.
//
#define CFG_MMF_MJPG_MAX_WIDTH			640
#define CFG_MMF_MJPG_MAX_HEIGHT			480

// ----------------------------------------------------------------------------
//  LOG or DEBUG or internal use
// ----------------------------------------------------------------------------
// brief: the default log level
// value: 0~7
#define CFG_LOG_LEVEL					6

// brief: log color enable/disable
// value: 0, 1
#define CFG_LOG_COLOR_EN				1

// brief: enable/disable tlog
// value: 0, 1
#define CFG_TLOG_EN					0

// brief: when = 1, will print all footprint of
//        rt_malloc/rt_free/.../rts_malloc/rts_free/...,etc.
// value: 0, 1
#define CFG_TRACE_RT_MEM				0

// brief: enable/disable task mem stat
// value: 0, 1
#define CFG_TASK_MEM_STAT_EN			1

#define CFG_DEBUG_ISP_CMD				0
#define CFG_DEBUG_ISP_RW_XMEM			0
#define CFG_DEBUG_ISP_MSG				1			// turn on/off isp message for time statistics
#define CFG_DEBUG_MMF_MSG				1			// turn on/off mmf message for time statistics
#define CFG_DEBUG_LWIP_MEM_PER_TASK		0

#endif	// __RT_CONFIG_SYS_H__

