#ifndef __RT_ISP_LIB_H__
#define __RT_ISP_LIB_H__
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"

#define USE_RTSCORE			0

#if (USE_RTSCORE)
# include "rtsisp.h"
# include "rtsvideo.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define RTK_EXT_CTL_SIZE	(0x03 + 1)

// A.4 ISP Processing Control Selectors
#define RTSCAM_SOC_PU_CONTROL_UNDEFINED							0x00
#define RTSCAM_SOC_PU_BACKLIGHT_COMPENSATION_CONTROL			0x01
#define RTSCAM_SOC_PU_BRIGHTNESS_CONTROL						0x02
#define RTSCAM_SOC_PU_CONTRAST_CONTROL							0x03
#define RTSCAM_SOC_PU_GAIN_CONTROL								0x04
#define RTSCAM_SOC_PU_POWER_LINE_FREQUENCY_CONTROL				0x05
#define RTSCAM_SOC_PU_HUE_CONTROL								0x06
#define RTSCAM_SOC_PU_SATURATION_CONTROL						0x07
#define RTSCAM_SOC_PU_SHARPNESS_CONTROL							0x08
#define RTSCAM_SOC_PU_GAMMA_CONTROL								0x09
#define RTSCAM_SOC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL			0x0A
#define RTSCAM_SOC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL	0x0B
#define RTSCAM_SOC_PU_WHITE_BALANCE_COMPONENT_CONTROL			0x0C
#define RTSCAM_SOC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL		0x0D
#define RTSCAM_SOC_PU_DIGITAL_MULTIPLIER_CONTROL				0x0E
#define RTSCAM_SOC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL			0x0F
#define RTSCAM_SOC_PU_HUE_AUTO_CONTROL							0x10
#define RTSCAM_SOC_PU_ANALOG_VIDEO_STANDARD_CONTROL				0x11
#define RTSCAM_SOC_PU_ANALOG_LOCK_STATUS_CONTROL				0x12
#define RTSCAM_SOC_PU_CONTRAST_AUTO_CONTROL						0x13

typedef struct {
	u8 bLength;
	u8 bDescriptorType;
	u8 bControlSize;
	u8 bmControls[RTK_EXT_CTL_SIZE];
} isp_rtk_ext_ctl_des_st;

#define isp_rtk_ext_ctl_des_from_buf(p, buf) \
	do { \
		(p)->bLength = buf[0]; \
		(p)->bDescriptorType = buf[1]; \
		(p)->bControlSize = buf[2]; \
		for (int _i = 0; _i < RTK_EXT_CTL_SIZE; _i++) \
			(p)->bmControls[_i] = buf[3 + _i]; \
	} while (0)

typedef struct
{
	u8 bLength;
	u8 bDescriptorType;
	u8 bControlSize;
	u8 bmControls[3];
} isp_process_des_st, isp_camera_des_st;

#define isp_process_des_from_buf(p, buf) \
	do { \
		(p)->bLength = buf[0]; \
		(p)->bDescriptorType = buf[1]; \
		(p)->bControlSize = buf[2]; \
		(p)->bmControls[0] = buf[3]; \
		(p)->bmControls[1] = buf[4]; \
		(p)->bmControls[2] = buf[5]; \
	} while (0)

#define isp_camera_des_from_buf(p, buf) \
	do { \
		(p)->bLength = buf[0]; \
		(p)->bDescriptorType = buf[1]; \
		(p)->bControlSize = buf[2]; \
		(p)->bmControls[0] = buf[3]; \
		(p)->bmControls[1] = buf[4]; \
		(p)->bmControls[2] = buf[5]; \
	} while (0)

typedef struct {
	u8 length;
	u8 desc_type;
	u8 format_type;
	u16 max_width;
	u16 max_height;
} isp_vs_fmt_des_st;

#define isp_vs_fmt_des_from_buf(p, buf) \
	do { \
		(p)->length = buf[0]; \
		(p)->desc_type = buf[1]; \
		(p)->format_type = buf[2]; \
		(p)->max_width = buf[3] | (buf[4] << 8); \
		(p)->max_height = buf[5] | (buf[6] << 8); \
	} while (0)

int isp_get_vs_format_desc(u8 streamid, isp_vs_fmt_des_st *out);

typedef struct {
	u8 str[32];
} isp_sensor_id_st, isp_new_fw_version_st;

#define isp_sensor_id_from_buf(p, buf)			memcpy((p)->str, buf, 32)
#define isp_new_fw_version_from_buf(p, buf)		memcpy((p)->str, buf, 32)

typedef struct {
	u8 bLength;
	u8 bDescriptorType;
	u8 bColorMatrixCoff;
	u8 bFullRangeFlag;
} isp_color_range_des_st;

#define isp_color_range_des_from_buf(p, buf) \
	do { \
		(p)->bLength = buf[0]; \
		(p)->bDescriptorType = buf[1]; \
		(p)->bColorMatrixCoff = buf[2]; \
		(p)->bFullRangeFlag = buf[3]; \
	} while (0)

typedef struct {
	u8 str[16];
} isp_supported_sensor_name_st;
#define isp_supported_sensor_name_from_buf(p, buf)	memcpy((p)->str, buf, 16)

typedef struct {
	u8 enable;
} isp_gray_mode_st;

#define isp_gray_mode_from_buf(p, buf) \
	do { \
		(p)->enable = buf[0]; \
	} while (0)

int isp_get_daynight_statis(void);
int isp_set_fps(u32 fps);
u32 isp_get_max_fps(void);
int isp_set_format(u8 streamid, u8 format);

int isp_get_awb_tempature(void);
int isp_get_sensor_reg(uint8_t len, uint16_t addr, uint8_t *data);
int isp_set_sensor_reg(uint8_t len, uint16_t addr, uint8_t *data);

// from struct rts_isp_device_desc in rtsisp.h
typedef struct {
	u8  length;
	u8  type;
	u16 hwversion;
	u16 fwversion;
	u8  streamnum;
	u8  frmivalnum;
} my_isp_device_des_st;

#define	my_isp_device_des_from_buf(p, buf) \
	do { \
		(p)->length = buf[0]; \
		(p)->type = buf[1]; \
		(p)->hwversion = MAKE_WORD(buf[2], buf[3]); \
		(p)->fwversion = MAKE_WORD(buf[4], buf[5]); \
		(p)->streamnum = buf[6]; \
		(p)->frmivalnum = buf[7]; \
	} while (0)

int my_isp_get_device_des(my_isp_device_des_st *out);

// from struct rts_isp_api_version in rtsisp.h
typedef struct {
	u8 main;
	u8 sub;
} my_isp_api_version_st;

#define	my_isp_api_version_from_buf(p, buf) \
	do { \
		(p)->main = buf[0]; \
		(p)->sub = buf[1]; \
	} while (0)

int my_isp_get_api_version(my_isp_api_version_st *out);

// from struct rts_isp_fw_version_t in rtsisp.h
typedef struct {
	u8  header;
	u8  len;
	u32 magictag;
	u16 ic_name;
	u16 vid;
	u16 pid;
	u32 fw_ver;
	u32 cus_ver;
	u8  reserved[12];
} my_isp_fw_version_st;

#define my_isp_fw_version_from_buf(p, buf) \
	do { \
		(p)->header = buf[0]; \
		(p)->len = buf[1]; \
		(p)->magictag = MAKE_DWORD_BE(buf[2], buf[3], buf[4], buf[5]); \
		(p)->ic_name = MAKE_WORD_BE(buf[6], buf[7]); \
		(p)->vid = MAKE_WORD_BE(buf[8], buf[9]); \
		(p)->pid = MAKE_WORD_BE(buf[10], buf[11]); \
		if (2 == ((p)->header >> 4)) { \
			(p)->fw_ver = MAKE_WORD_BE(buf[12], buf[13]); \
			(p)->cus_ver = MAKE_WORD_BE(buf[14], buf[15]); \
			memcpy((p)->reserved, &buf[16], 16); \
		} else if (3 == ((p)->header >> 4)) { \
			(p)->fw_ver = MAKE_DWORD_BE(buf[12], buf[13], buf[14], buf[15]); \
			(p)->cus_ver = MAKE_DWORD_BE(buf[16], buf[17], buf[18], buf[19]); \
			memcpy((p)->reserved, &buf[20], 12); \
		} \
	} while (0)

int my_isp_get_fw_version(my_isp_fw_version_st *out);

// To USE_RTSCORE:
//  step 1: rename isp_xxx to my_isp_xxx in non-USE_RTSCORE section.
//  step 2: replace rtscore equivalent in USE_RTSCORE section.
//
#if (USE_RTSCORE)
#define isp_api_version_st				struct rts_isp_api_version
#define isp_api_version_from_buf		my_isp_api_version_from_buf
#define isp_get_api_version(x)			rts_isp_get_api_version(1001, (x))

#define isp_fw_version_st				struct rts_isp_fw_version_t
#define isp_fw_version_from_buf			my_isp_fw_version_from_buf
#define isp_get_fw_version(x)			rts_isp_get_fw_version(1001, (x))

#define isp_device_des_st				struct rts_isp_device_desc
#define isp_device_des_from_buf			my_isp_device_des_from_buf
#define isp_get_device_des(x)			rts_isp_get_device_des(1001, (x))

#else	// USE_RTSCORE

#define isp_api_version_st				my_isp_api_version_st
#define isp_api_version_from_buf		my_isp_api_version_from_buf
#define isp_get_api_version				my_isp_get_api_version

#define isp_fw_version_st				my_isp_fw_version_st
#define isp_fw_version_from_buf			my_isp_fw_version_from_buf
#define isp_get_fw_version				my_isp_get_fw_version

#define isp_device_des_st				my_isp_device_des_st
#define isp_device_des_from_buf			my_isp_device_des_from_buf
#define isp_get_device_des				my_isp_get_device_des

#endif	// USE_RTSCORE


int isp_start_preview(u8 streamid, u16 width, u16 height);
int isp_stop_preview(u8 streamid);
int isp_pause_video(u8 streamid);
int isp_resume_video(u8 streamid);

int isp_read_xmem(u16 addr, u8 len, u8 *data);
int isp_write_xmem(u16 addr, u8 len, u8 *data);

void ispcmd_print(u16 code, u16 size, u8 *data);
void isp_device_des_print(isp_device_des_st *p);
void isp_fw_version_print(isp_fw_version_st *p);
void isp_api_version_print(isp_api_version_st *p);
void isp_vs_fmt_des_print(isp_vs_fmt_des_st *p);
void isp_process_des_print(isp_process_des_st *p);
void isp_camera_des_print(isp_camera_des_st *p);
void isp_rtk_ext_ctl_des_print(isp_rtk_ext_ctl_des_st *p);
void isp_color_range_des_print(isp_color_range_des_st *p);
void isp_isp_gray_mode_print(isp_gray_mode_st *p);

// ----------------------------------------------------------------------------
//  ISP control
// ----------------------------------------------------------------------------

// from rts_video_control in rtsvideo.h
typedef struct rts_video_control isp_ctrl_st;

// from enum_rts_video_ctrl_id in rtsvideo.h

// get isp_ctrl from isp hw.
int isp_ctrl_get(u8 id, OUT isp_ctrl_st *ctrl);

// return:
//  RT_E_INVALID_ID  : if id is invalid.
//  RT_E_OUT_OF_RANGE: if cur_val out of (min, max)
//  RT_E_INVALID_DATA: if cur_val not meet 'step' requirement.
//
int isp_ctrl_set(u8 id, int cur_val);
int isp_ctrl_set_def(u8 id);

// ----------------------------------------------------------------------------
//  isp lib
// ----------------------------------------------------------------------------
int isp_lib_init(void);
BOOL isp_lib_is_inited(void);
int isp_lib_deinit(void);
#define isp_lib_try_init()	(isp_lib_is_inited() ? RT_OK : isp_lib_init())

#if defined(__cplusplus)
}
#endif

#endif	// __RT_ISP_LIB_H__

