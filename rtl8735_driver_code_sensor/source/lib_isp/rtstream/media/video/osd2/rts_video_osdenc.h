#ifndef _MEDIA_RTS_VIDEO_OSDENC_H
#define _MEDIA_RTS_VIDEO_OSDENC_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <rtsosd2.h>


int rts_av_osdenc_init(int chn_id);
int rts_av_osdenc_cleanup(int chn_id);
int rts_av_osdenc_start(int chn_id);
int rts_av_osdenc_stop(int chn_id);
int rts_av_osdenc_check_ready(int chn_id);
int rts_av_osdenc_check_enable(int chn_id, int buf_id);
int rt_osd2_encode_buf(int chn_id, int buf_id, void *frm_dat, u32 frm_len);
int rts_av_osdenc_get_profile(int chn_id, struct rts_av_profile *profile);
int rts_av_osdenc_set_profile(int chn_id, int buf_id, struct rts_av_profile *profile);

#ifdef __cplusplus
}
#endif
#endif
