// brief: this file defines all stuff about isp cmd.
#ifndef RLX_ISP_CMD_H
#define RLX_ISP_CMD_H

// ----------------------------------------------------------------------------
//  ISP cmd code
// ----------------------------------------------------------------------------
#define RLX_ISP_CMD_XMEM_R						((0x00 << 8) | 0x81)
#define RLX_ISP_CMD_XMEM_W						((0x00 << 8) | 0x01)
#define RLX_ISP_CMD_I2C_R						((0x00 << 8) | 0x82)
#define RLX_ISP_CMD_I2C_W						((0x00 << 8) | 0x02)
#define RLX_ISP_CMD_READ_SENSOR_REG				((0x00 << 8) | 0x83)
#define RLX_ISP_CMD_WRITE_SENSOR_REG			((0x00 << 8) | 0x03)

#define RLX_ISP_CMD_GET_DEVICE_DES				((0x01 << 8) | 0x81)
#define RLX_ISP_CMD_GET_FRAME_INTERVAL_DES		((0x01 << 8) | 0x82)
#define RLX_ISP_CMD_GET_VS_FMT_DES				((0x01 << 8) | 0x83)
#define RLX_ISP_CMD_GET_ISP_PROCESS_DES			((0x01 << 8) | 0x84)
#define RLX_ISP_CMD_GET_CAMERA_DES				((0x01 << 8) | 0x85)
#define RLX_ISP_CMD_GET_RTK_EXT_CTL_DES			((0x01 << 8) | 0x86)
#define RLX_ISP_CMD_GET_HCLK_CFG_DES			((0x01 << 8) | 0x87)
#define RLX_ISP_CMD_GET_FW_VERSION				((0x01 << 8) | 0x88)
#define RLX_ISP_CMD_GET_SNR_POWER				((0x01 << 8) | 0x89)
#define RLX_ISP_CMD_GET_API_VERSION				((0x01 << 8) | 0x8a)
#define RLX_ISP_CMD_GET_SNR_POWER_SEQ			((0x01 << 8) | 0x8b)
#define RLX_ISP_CMD_GET_SENSOR_ID				((0x01 << 8) | 0x8c)
#define RLX_ISP_CMD_GET_COLOR_RANGE_DES			((0x01 << 8) | 0x8d)
#define RLX_ISP_CMD_GET_SUPPORTED_SENSOR_NAME	((0x01 << 8) | 0x8e)
#define RLX_ISP_CMD_GET_NEW_FW_VERSION			((0x01 << 8) | 0x8f)

#define RLX_ISP_CMD_GET_DYNAMIC_FPS				((0x0a << 8) | 0x95)
#define RLX_ISP_CMD_SET_DYNAMIC_FPS				((0x0a << 8) | 0x15)
#define RLX_ISP_CMD_SET_FPS						((0x02 << 8) | 0x01)
#define RLX_ISP_CMD_START_PREVIEW				((0x02 << 8) | 0x02)
#define RLX_ISP_CMD_STOP_PREVIEW				((0x02 << 8) | 0x03)
#define RLX_ISP_CMD_PAUSE_VIDEO					((0x02 << 8) | 0x05)
#define RLX_ISP_CMD_RESUME_VIDEO				((0x02 << 8) | 0x06)
#define RLX_ISP_CMD_SET_FORMAT					((0x02 << 8) | 0x07)
#define RLX_ISP_CMD_SNR_PWRON_BEF				((0x02 << 8) | 0x09)

#define RLX_ISP_CMD_ISP_GET_CTRL				((0x03 << 8) | 0x81)

#define RLX_ISP_CMD_GET_SNR_FMT					((0x06 << 8) | 0x81)
#define RLX_ISP_CMD_SET_ISP_FUNC				((0x0a << 8) | 0x01)
#define RLX_ISP_CMD_GET_ISP_FUNC				((0x0a << 8) | 0x81)
#define RLX_ISP_CMD_SET_ISP_GRAY_MODE			((0x0a << 8) | 0x02)
#define RLX_ISP_CMD_GET_ISP_GRAY_MODE			((0x0a << 8) | 0x82)
#define RLX_ISP_CMD_GET_TPNR_MODE				((0x0a << 8) | 0x9c)
#define RLX_ISP_CMD_GET_DAYNIGHT_STATIS			((0x0a << 8) | 0xaa)

#define RLX_ISP_CMD_GET_GPIO_USE_STATUS			((0x0c << 8) | 0x81)
#define RLX_ISP_CMD_SET_GPIO_DIR				((0x0c << 8) | 0x02)
#define RLX_ISP_CMD_GET_GPIO_DIR				((0x0c << 8) | 0x82)
#define RLX_ISP_CMD_SET_GPIO_VALUE				((0x0c << 8) | 0x03)
#define RLX_ISP_CMD_GET_GPIO_VALUE				((0x0c << 8) | 0x83)


#endif	// RLX_ISP_CMD_H
