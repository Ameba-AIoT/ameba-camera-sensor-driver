#ifndef __RT_CONFIG_APP_H
#define __RT_CONFIG_APP_H

// ----------------------------------------------------------------------------
// rt_cmd_basic
// ----------------------------------------------------------------------------
// note : hconf
// note : max strlen = 32
#define CFG_APP_NAME					"riot"
// brief: timeout of 'reboot' cmd.
// note : hconf
// value: 0(1S), 1(2S), 2(4S), 3(8S)
#define CFG_REBOOT_TIMEOUT				0
// note : hconf
// value: 0(VT100)
#define CFG_TERMINAL					0

// ----------------------------------------------------------------------------
// env default value
//
// note : hconf, env
// ----------------------------------------------------------------------------
// value: absolute path
#define CFG_ENV_INIT_SCRIPT				"/init.sh"
// value: "0", "1"
#define CFG_ENV_DHCP					"0"
#define CFG_ENV_ETHADDR					"00:11:22:33:44:55"
#define CFG_ENV_IPADDR					"192.168.1.168"
#define CFG_ENV_NETMASK					"255.255.255.0"
#define CFG_ENV_GATEWAYIP				"192.168.1.1"
#define CFG_ENV_SERVERIP				"192.168.1.12"
#define CFG_ENV_NTPSERVER				"pool.ntp.org"
#define CFG_ENV_MBUF					"0x83000000"

// ----------------------------------------------------------------------------
//  rt_cmd_net
// ----------------------------------------------------------------------------
// note : hconf
#define CFG_NET_RTSP_PORT				43794

// ----------------------------------------------------------------------------
//  rt_cmd_mtd
// ----------------------------------------------------------------------------
// brief: 'mtd update kernel' from VRAM or malloc().
// value: 0 or 1
#define CFG_MTD_UPDATE_KERNEL_VRAM		0

// ----------------------------------------------------------------------------
//  rt_cmd_mmf
//  note : hconf
// ----------------------------------------------------------------------------
// brief: for module_rtsp debug use.
// value: positive number, -1 (means forever)
#define CFG_MMF_RTSP_MAX_FRAMES			-1

// brief: when recieving connection request from network remote peer,
//        the next(first) frame is encoded as h264 key frame or not.
//        of course, this is a kind of h264 mmf strm.
// value: 0, 1
#define CFG_MMF_CFG_REQ_KEY_FRAME_ON_CONNECT	1

// brief: open mmf_strm or not.
// value: 0, 1
#define CFG_MMF_S0_EN					1
#define CFG_MMF_S1_EN					1
#define CFG_MMF_S2_EN					1

// VFORMAT: 1(YUV420_SEMIPLANAR)
// WH: (1920, 1080) (1280, 720) (640, 480) (320, 240) (352, 288) (176, 144)
// Max WH (ISPFW_JXF22_DVP):
//      chn#0: (1920, 1080)
//      chn#1: ( 640,  480)
//      chn#2: ( 320,  240)
// BITRATE_MODE:
//      CBR     = (1 << 1),
//      VBR     = (1 << 2),
//      C_VBR   = (1 << 3),
// H264 LEVEL:
//       1 (H264_LEVEL_1	)
//       2 (H264_LEVEL_1_b	)
//       3 (H264_LEVEL_1_1	)
//       4 (H264_LEVEL_1_2	)
//       5 (H264_LEVEL_1_3	)
//       6 (H264_LEVEL_2	)
//       7 (H264_LEVEL_2_1	)
//       8 (H264_LEVEL_2_2	)
//       9 (H264_LEVEL_3	)
//      10 (H264_LEVEL_3_1	)
//      11 (H264_LEVEL_3_2	)
//      12 (H264_LEVEL_4	)
//      13 (H264_LEVEL_4_1	)
//      14 (H264_LEVEL_4_2	)
//      15 (H264_LEVEL_5	)
//      16 (H264_LEVEL_5_1	)
// MAX_FRAMES: -1 means forever
// FOUT_PATH: must be absolute path. doesn't need file extension.
//            the app layer will autoly add it.
// LINK_OPT:
//      0 (ISP_FOUT)
//      1 (ISP_H264_FOUT)
//      2 (ISP_H264_RTSP)
//      3 (ISP_H264_RTSP_FOUT)
//      4 (ISP_MJPG_FOUT)
//      5 (ISP_H264_RTSPxMJPG_FOUT)
//
#define CFG_MMF_S0_VFORMAT				1
#define CFG_MMF_S0_WIDTH				1920
#define CFG_MMF_S0_HEIGHT				1080
#define CFG_MMF_S0_H264_LEVEL			12
#define CFG_MMF_S0_H264_QP				(-1)
#define CFG_MMF_S0_H264_BITRATE			(1*1024*1024)
#define CFG_MMF_S0_H264_BITRATE_MODE	(2)
#define CFG_MMF_S0_H264_MAX_BITRATE		(20*1024*1024)
#define CFG_MMF_S0_H264_MIN_BITRATE		(16*1024)
#define CFG_MMF_S0_H264_GOP				40
#define CFG_MMF_S0_H264_VIDEOSTAB		0
#define CFG_MMF_S0_MAX_FRAMES			300
#define CFG_MMF_S0_FOUT_PATH			"/s0"
#define CFG_MMF_S0_LINK_OPT				2

#define CFG_MMF_S1_VFORMAT				1
#define CFG_MMF_S1_WIDTH				640
#define CFG_MMF_S1_HEIGHT				480
#define CFG_MMF_S1_H264_LEVEL			12
#define CFG_MMF_S1_H264_QP				(-1)
#define CFG_MMF_S1_H264_BITRATE			(256*1024)
#define CFG_MMF_S1_H264_BITRATE_MODE	(2)
#define CFG_MMF_S1_H264_MAX_BITRATE		(20*256*1024)
#define CFG_MMF_S1_H264_MIN_BITRATE		(16*256)
#define CFG_MMF_S1_H264_GOP				30
#define CFG_MMF_S1_H264_VIDEOSTAB		0
#define CFG_MMF_S1_MAX_FRAMES			300
#define CFG_MMF_S1_FOUT_PATH			"/s1"
#define CFG_MMF_S1_LINK_OPT				5

#define CFG_MMF_S2_VFORMAT				1
#define CFG_MMF_S2_WIDTH				192
#define CFG_MMF_S2_HEIGHT				108
#define CFG_MMF_S2_H264_LEVEL			12
#define CFG_MMF_S2_H264_QP				(-1)
#define CFG_MMF_S2_H264_BITRATE			(128*1024)
#define CFG_MMF_S2_H264_BITRATE_MODE	(2)
#define CFG_MMF_S2_H264_MAX_BITRATE		(20*128*1024)
#define CFG_MMF_S2_H264_MIN_BITRATE		(16*128)
#define CFG_MMF_S2_H264_GOP				10
#define CFG_MMF_S2_H264_VIDEOSTAB		0
#define CFG_MMF_S2_MAX_FRAMES			300
#define CFG_MMF_S2_FOUT_PATH			"/s2"
#define CFG_MMF_S2_LINK_OPT				0

// ----------------------------------------------------------------------------
//  rt_cmd_audio
// ----------------------------------------------------------------------------
// value: 8000, 16000
#define CFG_AUDIO_SAMPLE_RATE			8000
// value: 8, 16
#define CFG_AUDIO_BITS_PER_SAMPLE		16
// value: (0: NONE) (1: AECNS) (2: NSONLY)
#define CFG_AUDIO_AEC_OPT				0
// value: 0, 1
#define CFG_AUDIO_TX_MUTE				0
// value: 0~127
#define CFG_AUDIO_TX_VOLUME				100

#endif	// __RT_CONFIG_APP_H

