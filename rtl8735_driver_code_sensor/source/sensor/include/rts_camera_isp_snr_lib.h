/*
 * Realtek Semiconductor Corp.
 * ../../../../include/uapi/linux/rts_camera_isp_snr.h
 * Copyright (C) 2014 Grant Shen <grant_shen@realsil.com.cn>
 */
#ifndef _U_RTS_CAMERA_ISP_SNR_H
#define _U_RTS_CAMERA_ISP_SNR_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

enum rts_isp_snr_pwr_type {
	SNR_RST_GPIO,
	SNR_PWDN_GPIO,
	SNR_PWRCTRL_GPIO,
	SNR_HCLK,
	SNR_IO_POWER,
	SNR_ANALOG_POWER,
	SNR_CORE_POWER,
	_MAX_SNR_POWER_TYPE,
};

struct rts_isp_snr_pwr_item {
	enum rts_isp_snr_pwr_type type;
	__u32 value;
	__u32 delay; /* us */
};

struct rts_isp_snr_pwr {
	__u32 num;
	struct rts_isp_snr_pwr_item items[16];
};

struct rts_isp_i2c_info {
	__u8 i2c_id;
	__u8 addr_len;
	__u8 data_len;
};

struct rts_isp_i2c_reg {
	__u16 addr;
	__u16 data;
};

struct rts_isp_i2c {
	struct rts_isp_i2c_info info;
	__u32 num;
	struct rts_isp_i2c_reg regs[16];
};

struct rts_isp_i2c_reg_mask {
	__u16 addr;
	__u16 data;
	__u16 mask;
};

struct rts_isp_reg_mask {
	__u32 addr;
	__u32 data;
	__u32 mask;
};

enum rts_isp_interrupt {
	RTS_ISP_INT_NONE,
	RTS_ISP_INT_DATA_START,
	RTS_ISP_INT_FRAME_END,
	_MAX_RTS_ISP_INT,
};

enum rts_isp_sync_reg_type {
	RTS_ISP_SYNC_REG_TYPE_I2C,
	RTS_ISP_SYNC_REG_TYPE_REG,
	_MAX_RTS_ISP_SYNC_REG_TYPE,
};

struct rts_isp_sync_info {
	__u32 delay_frames; /* max 4 */
	enum rts_isp_sync_reg_type type;
	enum rts_isp_interrupt interrupt;
};

struct rts_isp_sync_reg {
	struct rts_isp_sync_info info;
	union {
		struct rts_isp_i2c_reg_mask i2c;
		struct rts_isp_reg_mask reg;
	};
};

struct rts_isp_sync_regs {
	__u32 num;
	struct rts_isp_sync_reg reg[32]; /* max 32 regs for sensor */
	__u32 isp_gain_delay;
	__u32 isp_gain;

	/* private fields, do not set in sensor model */
	struct rts_isp_i2c_info i2c_info;
	__u32 split_index;
};

#endif /* U_RTS_CAMERA_ISP_SNR_H */
