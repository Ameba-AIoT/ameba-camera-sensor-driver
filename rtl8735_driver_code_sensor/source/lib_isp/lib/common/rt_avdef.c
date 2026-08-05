#include <string.h>
#include "rt_avdef.h"
#include "rt_log.h"
#include "my_def.h"
#include "rlx_lds.h"

int rt_calc_frm_size(u8 fmt, int width, int height)
{
	int size = 0;

	switch (fmt)
	{
	case RT_V_YUV420_SEMIPLANAR:
		size = VRAM_SIZE_YUV420(width, height);
		break;
	case RT_V_YUV422_SEMIPLANAR:
		size = VRAM_SIZE_YUV422(width, height);
		break;
	default:
		rt_should_not_reach();
		break;
	}
	return size;
}

void rt_res_from_str(char *str, int *w, int *h)
{
	*w = 0; *h = 0;
	if (!strcmp(str, "fhd"))    { *w = 1920; *h = 1080; return; }
	if (!strcmp(str, "hd"))     { *w = 1280; *h =  720; return; }
	if (!strcmp(str, "vga"))    { *w =  640; *h =  480; return; }
	if (!strcmp(str, "qvga"))   { *w =  320; *h =  240; return; }
	if (!strcmp(str, "cif"))    { *w =  352; *h =  288; return; }
	if (!strcmp(str, "qcif"))   { *w =  176; *h =  144; return; }
	return;
}

char *rt_av_fmt_str(rt_av_fmt_t f)
{
	if (f == RT_V_YUV420_SEMIPLANAR) return "YUV420";
	if (f == RT_V_YUV422_SEMIPLANAR) return "YUV422";
	if (f == RT_V_BAYER)             return "BAYER";
	if (f == RT_V_MJPG)              return "MJPG";
	if (f == RT_V_H264)              return "H264";
	//
	if (f == RT_A_MP3)   return "MP3";
	if (f == RT_A_ULAW)  return "ULAW";
	if (f == RT_A_ALAW)  return "ALAW";
	if (f == RT_A_PCM)   return "PCM";
	if (f == RT_A_G726)  return "G726";
	if (f == RT_A_AMRNB) return "AMRNB";
	if (f == RT_A_AAC)   return "AAC";
	if (f == RT_A_SBC)   return "SBC";
	if (f == RT_A_OPUS)  return "OPUS";
	if (f == RT_A_WAV)   return "WAV";

	return "N/A";
}

// brief: get format from file path (file extension)
rt_av_fmt_t rt_av_fmt_from_path(char *abs_path)
{
	char *pch = strrchr(abs_path, '.');

	if (pch == NULL)
		return RT_AV_NONE;
	pch++;
	if (!strcmp(pch, "yuv"))  return RT_V_YUV420_SEMIPLANAR;
	if (!strcmp(pch, "mjpg")) return RT_V_MJPG;
	if (!strcmp(pch, "h264")) return RT_V_H264;
	//
	if (!strcmp(pch, "pcm"))  return RT_A_PCM;
	if (!strcmp(pch, "aac"))  return RT_A_AAC;
	if (!strcmp(pch, "wav"))  return RT_A_WAV;
	if (!strcmp(pch, "ulaw")) return RT_A_ULAW;
	//
	return RT_AV_NONE;
}

