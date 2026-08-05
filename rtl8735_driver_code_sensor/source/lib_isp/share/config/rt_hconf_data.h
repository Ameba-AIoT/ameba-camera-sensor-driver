#ifndef __RT_HCONF_DATA_H
#define __RT_HCONF_DATA_H
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"

// [version history]
// (2019/oo/xx) v1.0: initial version.
// (2019/11/19) v1.1: add AUDIO group after MMF.
// (2019/11/27) v1.2: add MMF_Sx_LINK_OPT entries.
// (2019/11/28) v1.3: add OSD_TEXT & OSD_TIMER entries.
// (2019/12/05) v1.4: del SHELL_AUTORUN_INIT_SCRIPT
// (2019/12/06) v1.5: rename ISP_FPS to ISP_SENSOR_FPS
// (2019/12/07) v1.6: del SHELL_AUTORUN_NET_INIT & SHELL_AUTORUN_MMC_INIT.
//                    merge APP & SHELL group into SYS group.
// (2019/12/11) v1.7: add ISP_TASK_FPS_x
//
// (2019/12/16) v2.0: seperate to rt_hconf & rt_hconf_data
// (2019/12/16) v2.1: del all OSD related defines.
// (2019/12/19) v2.2: add MMF_Sx_BITRATE_XXX entries.
// (2020/02/24) v2.3: add AUDIO_BITS_PER_SAMPLE.
// (2020/02/24) v2.4: enlarge SZ_CONFIG_MMF.
// (2020/04/09) v2.5: del ISPFW_NAME, ISPFW_SIZE & ISPFW_FROM_SF.
//
#define VERSION_VALUE		MAKE_DWORD_LE(0, 0, 2, 5)
#define MAGIC_VALUE			MAKE_DWORD_LE('2', '3', '7', '9')

// Caution!!
//  SZ_TOTAL must be multiple of RT_SF_READ_UNIT_SZ(= 32)
//  or init_bsp() flow can't run successfully.
//
#define SZ_HEADER			32
#define SZ_CONFIG			256
#define SZ_STRTBL			1600
#define SZ_TOTAL			(SZ_HEADER + SZ_CONFIG + SZ_STRTBL)

#define SZ_CONFIG_ISP		16
#define SZ_CONFIG_SYS		32
#define SZ_CONFIG_MMF		128
#define SZ_CONFIG_AUDIO		16

#define OFS_HEADER			0
#define OFS_CONFIG_ISP		(SZ_HEADER)
#define OFS_CONFIG_SYS		(OFS_CONFIG_ISP + SZ_CONFIG_ISP)
#define OFS_CONFIG_MMF		(OFS_CONFIG_SYS + SZ_CONFIG_SYS)
#define OFS_CONFIG_AUDIO	(OFS_CONFIG_MMF + SZ_CONFIG_MMF)
#define OFS_STRTBL			(SZ_HEADER + SZ_CONFIG)

#if SZ_CONFIG < (SZ_CONFIG_ISP + SZ_CONFIG_SYS + SZ_CONFIG_MMF + SZ_CONFIG_AUDIO)
#error "SZ_CONFIG is less than the total size of CONFIG group"
#endif

// brief:
//  if you add new hconf group and offset,
//  please remember to modify this function to reflect the change.
// note:
//  please set non-unsed array entry to zero in offset[].
//
void hconf_get_offset_info(OUT int offset[16]);

enum hconf_type
{
	HCONF_TYPE_ERR = -1,
	HCONF_TYPE_CFG = 0,
	HCONF_TYPE_STR,
};

enum hconf_group
{
	HCONF_GRP_HEADER,
	HCONF_GRP_ISP,
	HCONF_GRP_SYS,
	HCONF_GRP_MMF,
	HCONF_GRP_AUDIO,
	HCONF_GRP_STRTBL,
	// last one
	HCONF_GRP_MAX,
};
#define hconf_group(id)		((id) >> 8)

enum hconf_id
{
	// header
	HCONF_MAGIC = HCONF_GRP_HEADER << 8,
	HCONF_VERSION,
	HCONF_ADDR,
	HCONF_TOTAL_SZ,
	HCONF_HEADER_SZ,
	HCONF_CONFIG_SZ,
	HCONF_STRTBL_SZ,

	// config - isp
	ISP_SENSOR_FPS = HCONF_GRP_ISP << 8,
	ISP_TASK_FPS_0,
	ISP_TASK_FPS_1,
	ISP_TASK_FPS_2,

	// config - sys
	NET_RTSP_PORT = HCONF_GRP_SYS << 8,
	REBOOT_TIMEOUT,
	SHELL_HIST_EN,

	// config - mmf
	// note: MMF_Sx_PAD is necessary, don't remove it.
	MMF_S0_H264_QP = HCONF_GRP_MMF << 8,
	MMF_S0_H264_BITRATE_MODE,
	MMF_S0_H264_BITRATE,
	MMF_S0_H264_MAX_BITRATE,
	MMF_S0_H264_MIN_BITRATE,
	MMF_S0_H264_GOP,
	MMF_S0_H264_VIDEOSTAB,
	MMF_S0_H264_LEVEL,
	MMF_S0_VFORMAT,
	MMF_S0_WIDTH,
	MMF_S0_HEIGHT,
	MMF_S0_MAX_FRAMES,
	MMF_S0_PAD,
	MMF_S1_H264_QP,
	MMF_S1_H264_BITRATE_MODE,
	MMF_S1_H264_BITRATE,
	MMF_S1_H264_MAX_BITRATE,
	MMF_S1_H264_MIN_BITRATE,
	MMF_S1_H264_GOP,
	MMF_S1_H264_VIDEOSTAB,
	MMF_S1_H264_LEVEL,
	MMF_S1_VFORMAT,
	MMF_S1_WIDTH,
	MMF_S1_HEIGHT,
	MMF_S1_MAX_FRAMES,
	MMF_S1_PAD,
	MMF_S2_H264_QP,
	MMF_S2_H264_BITRATE_MODE,
	MMF_S2_H264_BITRATE,
	MMF_S2_H264_MAX_BITRATE,
	MMF_S2_H264_MIN_BITRATE,
	MMF_S2_H264_GOP,
	MMF_S2_H264_VIDEOSTAB,
	MMF_S2_H264_LEVEL,
	MMF_S2_VFORMAT,
	MMF_S2_WIDTH,
	MMF_S2_HEIGHT,
	MMF_S2_MAX_FRAMES,
	MMF_S2_PAD,
	MMF_S0_EN,
	MMF_S1_EN,
	MMF_S2_EN,
	MMF_S0_LINK_OPT,
	MMF_S1_LINK_OPT,
	MMF_S2_LINK_OPT,

	// config - audio
	AUDIO_SAMPLE_RATE = HCONF_GRP_AUDIO << 8,
	AUDIO_BITS_PER_SAMPLE,
	AUDIO_AEC_OPT,
	AUDIO_TX_MUTE,
	AUDIO_TX_VOLUME,

	// string
	SHELL_PROMPT_STR = HCONF_GRP_STRTBL << 8,
	APP_NAME,
	ENV_DHCP,
	ENV_ETHADDR,
	ENV_IPADDR,
	ENV_NETMASK,
	ENV_GATEWAYIP,
	ENV_SERVERIP,
	ENV_NTPSERVER,
	ENV_INIT_SCRIPT,
	ENV_MBUF,
	MMF_S0_FOUT_PATH,
	MMF_S1_FOUT_PATH,
	MMF_S2_FOUT_PATH,
	// last one
	HCONF_MAX = HCONF_GRP_MAX << 8,
};


#endif	// __RT_HCONF_DATA_H

