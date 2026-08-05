/*
 * Realtek Semiconductor Corp.
 *
 * rts_camera_mcu.h
 *
 * Copyright (C) 2018      Wil Shi<wil_shi@realsil.com.cn>
 */


struct rtscam_mcu_mtd_state {
	int index;
	int state;
};

struct rtscam_mcu_fw {
	unsigned int length;
	__u8 *fw;
};

#define RTSMCUIOC_REQUEST_GPIO		_IOCTL_IOWR('m', 0x01, int)
#define RTSMCUIOC_FREE_GPIO		_IOCTL_IOWR('m', 0x02, int)

#define RTSMCUIOC_CAMERA_LOAD_FW	_IOCTL_IOW('m', 0x10, struct rtscam_mcu_fw)
#define RTSMCUIOC_CAMERA_DUMP_FW	_IOCTL_IOWR('m', 0x11, struct rtscam_mcu_fw)
#define RTSMCUIOC_CAMERA_G_FW_SIZE	_IOCTL_IOR('m', 0x12, unsigned int)

#define RTSMCUIOC_S_TD			_IOCTL_IOW('m', 0x20, int)
#define RTSMCUIOC_G_TD			_IOCTL_IOR('m', 0x21, int)

#define RTSMCUIOC_G_MTDSTATE	_IOCTL_IOWR('m', 0x30, struct rtscam_mcu_mtd_state)
#define RTSMCUIOC_C_MTDSTATE	_IOCTL_IOWR('m', 0x31, int)
#define RTSMCUIOC_ENABLE_MD	_IOCTL_IOWR('m', 0x32, int)

#define RTSMCUIOC_ISPCMD	_IOCTL_IOWR('m', 0x40, struct rtscam_soc_cmd_stru)
#define RTSMCUIOC_ISP_EXT_CMDS	_IOCTL_IOWR('m', 0x41, struct rtscam_soc_ext_cmds)

#define RTSMCUIOC_G_HWOFFSET	_IOCTL_IOR('m', 0x50, unsigned long)
#define RTSMCUIOC_G_HWIOSIZE	_IOCTL_IOR('m', 0x51, unsigned int)
