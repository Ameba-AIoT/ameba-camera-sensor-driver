#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rt_hconf.h"

#define entry_type_cfg(id, len, def)	id, #id, HCONF_TYPE_CFG, len, .def_cfg = def
#define entry_type_str(id, len, def)	id, #id, HCONF_TYPE_STR, len, .def_str = def

// brief:
//  if you add new hconf group and offset,
//  please remember to modify this function to reflect the change.
// note:
//  please set non-unsed array entry to zero in offset[].
//
void hconf_get_offset_info(OUT int offset[16])
{
	int data[] = {
		OFS_HEADER,
		OFS_CONFIG_ISP,
		OFS_CONFIG_SYS,
		OFS_CONFIG_MMF,
		OFS_CONFIG_AUDIO,
		OFS_STRTBL,
	};
	int size = ARRAY_SIZE(data);

	memset(offset, 0, 16*sizeof(int));
	memcpy(offset, data, size*sizeof(int));
	return;
}

// make sure the following rules
// - len must be 4-byte aligned for type_cfg
// - def must be "interger" type for type_cfg
// - def must be "string" type for type_str

hconf_entry_st hconf_tbl[] =
{
	// id & name & type,						len,	def
	// header
	{entry_type_cfg(HCONF_MAGIC,				4,		MAGIC_VALUE)},
	{entry_type_cfg(HCONF_VERSION,				4,		VERSION_VALUE)},
	{entry_type_cfg(HCONF_ADDR,					4,		0)},
	{entry_type_cfg(HCONF_TOTAL_SZ,				2,		SZ_TOTAL)},
	{entry_type_cfg(HCONF_HEADER_SZ,			2,		SZ_HEADER)},
	{entry_type_cfg(HCONF_CONFIG_SZ,			2,		SZ_CONFIG)},
	{entry_type_cfg(HCONF_STRTBL_SZ,			2,		SZ_STRTBL)},
	// config - isp
	{entry_type_cfg(ISP_SENSOR_FPS,				1,		CFG_ISP_SENSOR_FPS)},
	{entry_type_cfg(ISP_TASK_FPS_0,				1,		CFG_ISP_TASK_FPS_0)},
	{entry_type_cfg(ISP_TASK_FPS_1,				1,		CFG_ISP_TASK_FPS_1)},
	{entry_type_cfg(ISP_TASK_FPS_2,				1,		CFG_ISP_TASK_FPS_2)},
	// config - app
	{entry_type_cfg(NET_RTSP_PORT,				4,		CFG_NET_RTSP_PORT)},
	{entry_type_cfg(REBOOT_TIMEOUT,				1,		CFG_REBOOT_TIMEOUT)},
	// config - shell
	{entry_type_cfg(SHELL_HIST_EN,				1,		CFG_SHELL_HIST_EN)},
	// config - mmf
	{entry_type_cfg(MMF_S0_H264_QP,				4,		CFG_MMF_S0_H264_QP)},
	{entry_type_cfg(MMF_S0_H264_BITRATE_MODE,	4,		CFG_MMF_S0_H264_BITRATE_MODE)},
	{entry_type_cfg(MMF_S0_H264_BITRATE,		4,		CFG_MMF_S0_H264_BITRATE)},
	{entry_type_cfg(MMF_S0_H264_MAX_BITRATE,	4,		CFG_MMF_S0_H264_MAX_BITRATE)},
	{entry_type_cfg(MMF_S0_H264_MIN_BITRATE,	4,		CFG_MMF_S0_H264_MIN_BITRATE)},
	{entry_type_cfg(MMF_S0_H264_GOP,			4,		CFG_MMF_S0_H264_GOP)},
	{entry_type_cfg(MMF_S0_H264_VIDEOSTAB,		4,		CFG_MMF_S0_H264_VIDEOSTAB)},
	{entry_type_cfg(MMF_S0_H264_LEVEL,			1,		CFG_MMF_S0_H264_LEVEL)},
	{entry_type_cfg(MMF_S0_VFORMAT,				1,		CFG_MMF_S0_VFORMAT)},
	{entry_type_cfg(MMF_S0_WIDTH,				2,		CFG_MMF_S0_WIDTH)},
	{entry_type_cfg(MMF_S0_HEIGHT,				2,		CFG_MMF_S0_HEIGHT)},
	{entry_type_cfg(MMF_S0_PAD,					2,		0)},
	{entry_type_cfg(MMF_S1_H264_QP,				4,		CFG_MMF_S1_H264_QP)},
	{entry_type_cfg(MMF_S1_H264_BITRATE_MODE,	4,		CFG_MMF_S1_H264_BITRATE_MODE)},
	{entry_type_cfg(MMF_S1_H264_BITRATE,		4,		CFG_MMF_S1_H264_BITRATE)},
	{entry_type_cfg(MMF_S1_H264_MAX_BITRATE,	4,		CFG_MMF_S1_H264_MAX_BITRATE)},
	{entry_type_cfg(MMF_S1_H264_MIN_BITRATE,	4,		CFG_MMF_S1_H264_MIN_BITRATE)},
	{entry_type_cfg(MMF_S1_H264_GOP,			4,		CFG_MMF_S1_H264_GOP)},
	{entry_type_cfg(MMF_S1_H264_VIDEOSTAB,		4,		CFG_MMF_S1_H264_VIDEOSTAB)},
	{entry_type_cfg(MMF_S1_H264_LEVEL,			1,		CFG_MMF_S1_H264_LEVEL)},
	{entry_type_cfg(MMF_S1_VFORMAT,				1,		CFG_MMF_S1_VFORMAT)},
	{entry_type_cfg(MMF_S1_WIDTH,				2,		CFG_MMF_S1_WIDTH)},
	{entry_type_cfg(MMF_S1_HEIGHT,				2,		CFG_MMF_S1_HEIGHT)},
	{entry_type_cfg(MMF_S1_PAD,					2,		0)},
	{entry_type_cfg(MMF_S2_H264_QP,				4,		CFG_MMF_S2_H264_QP)},
	{entry_type_cfg(MMF_S2_H264_BITRATE_MODE,	4,		CFG_MMF_S2_H264_BITRATE_MODE)},
	{entry_type_cfg(MMF_S2_H264_BITRATE,		4,		CFG_MMF_S2_H264_BITRATE)},
	{entry_type_cfg(MMF_S2_H264_MAX_BITRATE,	4,		CFG_MMF_S2_H264_MAX_BITRATE)},
	{entry_type_cfg(MMF_S2_H264_MIN_BITRATE,	4,		CFG_MMF_S2_H264_MIN_BITRATE)},
	{entry_type_cfg(MMF_S2_H264_GOP,			4,		CFG_MMF_S2_H264_GOP)},
	{entry_type_cfg(MMF_S2_H264_VIDEOSTAB,		4,		CFG_MMF_S2_H264_VIDEOSTAB)},
	{entry_type_cfg(MMF_S2_H264_LEVEL,			1,		CFG_MMF_S2_H264_LEVEL)},
	{entry_type_cfg(MMF_S2_VFORMAT,				1,		CFG_MMF_S2_VFORMAT)},
	{entry_type_cfg(MMF_S2_WIDTH,				2,		CFG_MMF_S2_WIDTH)},
	{entry_type_cfg(MMF_S2_HEIGHT,				2,		CFG_MMF_S2_HEIGHT)},
	{entry_type_cfg(MMF_S2_PAD,					2,		0)},
	{entry_type_cfg(MMF_S0_MAX_FRAMES,			4,		CFG_MMF_S0_MAX_FRAMES)},
	{entry_type_cfg(MMF_S1_MAX_FRAMES,			4,		CFG_MMF_S1_MAX_FRAMES)},
	{entry_type_cfg(MMF_S2_MAX_FRAMES,			4,		CFG_MMF_S2_MAX_FRAMES)},
	{entry_type_cfg(MMF_S0_EN,					1,		CFG_MMF_S0_EN)},
	{entry_type_cfg(MMF_S1_EN,					1,		CFG_MMF_S1_EN)},
	{entry_type_cfg(MMF_S2_EN,					1,		CFG_MMF_S2_EN)},
	{entry_type_cfg(MMF_S0_LINK_OPT,			1,		CFG_MMF_S0_LINK_OPT)},
	{entry_type_cfg(MMF_S1_LINK_OPT,			1,		CFG_MMF_S1_LINK_OPT)},
	{entry_type_cfg(MMF_S2_LINK_OPT,			1,		CFG_MMF_S2_LINK_OPT)},
	// config - audio
	{entry_type_cfg(AUDIO_SAMPLE_RATE,			2,		CFG_AUDIO_SAMPLE_RATE)},
	{entry_type_cfg(AUDIO_BITS_PER_SAMPLE,		1,		CFG_AUDIO_BITS_PER_SAMPLE)},
	{entry_type_cfg(AUDIO_AEC_OPT,				1,		CFG_AUDIO_AEC_OPT)},
	{entry_type_cfg(AUDIO_TX_MUTE,				1,		CFG_AUDIO_TX_MUTE)},
	{entry_type_cfg(AUDIO_TX_VOLUME,			1,		CFG_AUDIO_TX_VOLUME)},
	// string
	{entry_type_str(SHELL_PROMPT_STR,			8,		CFG_SHELL_PROMPT_STR)},
	{entry_type_str(APP_NAME,					32,		CFG_APP_NAME)},
	{entry_type_str(ENV_DHCP,					4,		CFG_ENV_DHCP)},
	{entry_type_str(ENV_ETHADDR,				20,		CFG_ENV_ETHADDR)},
	{entry_type_str(ENV_IPADDR,					20,		CFG_ENV_IPADDR)},
	{entry_type_str(ENV_NETMASK,				20,		CFG_ENV_NETMASK)},
	{entry_type_str(ENV_GATEWAYIP,				20,		CFG_ENV_GATEWAYIP)},
	{entry_type_str(ENV_SERVERIP,				20,		CFG_ENV_SERVERIP)},
	{entry_type_str(ENV_NTPSERVER,				32,		CFG_ENV_NTPSERVER)},
	{entry_type_str(ENV_INIT_SCRIPT,			256,	CFG_ENV_INIT_SCRIPT)},
	{entry_type_str(ENV_MBUF,					16,		CFG_ENV_MBUF)},
	{entry_type_str(MMF_S0_FOUT_PATH,			256,	CFG_MMF_S0_FOUT_PATH)},
	{entry_type_str(MMF_S1_FOUT_PATH,			256,	CFG_MMF_S1_FOUT_PATH)},
	{entry_type_str(MMF_S2_FOUT_PATH,			256,	CFG_MMF_S2_FOUT_PATH)},
	// last one
	{entry_type_str(HCONF_MAX,					0,		NULL)}

};

