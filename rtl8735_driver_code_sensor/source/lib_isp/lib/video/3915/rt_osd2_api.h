// brief: osd2 encode api
//
#ifndef __RT_OSD2_API_H__
#define __RT_OSD2_API_H__
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
//#include "my_def.h"

#include "rt_avdef.h"
#include "rtsvideo.h"

struct rts_video_osd_block {
	struct rts_video_rect rect;
	uint8_t bg_enable;
	uint32_t bg_color;
	uint32_t ch_color;

	uint8_t h_gap : 4,
		v_gap : 4;

	uint8_t flick_enable;
	uint32_t flick_speed;
	uint8_t char_color_alpha;

	uint8_t stroke_enable;
	uint8_t stroke_direct;
	uint8_t stroke_delta;

	struct rts_osd_text_t *pshowtext;
	BITMAP_S *pbitmap;
	uint8_t blk_hide;
};

#if 0
enum rts_osd_char_rotation {
	osd_char_rotation_0 = 0,
	osd_char_rotation_90 = 1,
	osd_char_rotation_180 = 2,
	osd_char_rotation_270 = 3
};


enum rts_osd_time_fmt {
	osd_time_fmt_no = 0,	/*not show time*/
	osd_time_fmt_24,
	osd_time_fmt_12,
	osd_time_fmt_12_1,
	osd_time_fmt_12_2,
	osd_time_fmt_12_3,
	osd_time_fmt_12_4,
	osd_time_fmt_12_5,
	osd_time_fmt_12_6,
	osd_time_fmt_12_7,
	osd_time_fmt_reserved
};

enum rts_osd_date_fmt {
	osd_date_fmt_no = 0,	/*not show date*/
	osd_date_fmt_0,		/*dd/MM/yyyy, eg. 26/05/2015*/
	osd_date_fmt_1,		/*dd/MM/yy, eg. 26/05/15*/
	osd_date_fmt_2,		/*d/M/yy, eg. 26/5/15*/
	osd_date_fmt_3,		/*M/d/yyyy, eg. 5/26/2015*/
	osd_date_fmt_4,		/*M/d/yy, eg. 5/26/15*/
	osd_date_fmt_5,		/*MM/dd/yy, eg. 05/26/15*/
	osd_date_fmt_6,		/*MM/dd/yyyy, eg. 05/26/2015*/
	osd_date_fmt_7,		/*yyyy/M/d, eg. 2015/5/26*/
	osd_date_fmt_8,		/*yyyy-M-d, eg. 2015-5-26*/
	osd_date_fmt_9,		/*yyyy-MM-dd, eg. 2015-05-26*/
	osd_date_fmt_10,	/*yyyy/MM/dd, eg. 2015/05/26*/
	osd_date_fmt_11,	/*yy-MM-dd, eg. 15-05-26*/
	osd_date_fmt_12,	/*yy/M/d, eg. 15/5/26*/
	osd_date_fmt_13,	/*yy-M-d, eg. 15-5-26*/
	osd_date_fmt_14,	/*yy/MM/dd, eg. 15/05/26*/
	osd_date_fmt_reserved
};
#endif

struct rts_video_osd_attr {
	int number;
	struct rts_video_osd_block *blocks;

	enum rts_osd_time_fmt time_fmt;
	uint8_t time_blkidx;
	int time_pos;
	enum rts_osd_date_fmt date_fmt;
	uint8_t date_blkidx;
	int date_pos;

	unsigned int single_font_addr;
	unsigned int double_font_addr;

	uint8_t osd_char_w;
	uint8_t osd_char_h;
	struct rts_osd_text_t *presettext;

	BITMAP_S *ppresetbitmap[4];
	int presetbmpidx[4];
	int presetbmpnum;

	uint32_t reserved[4];
};

struct rt_osd2_en_rec {
	u32 blk_idx;
	u32 osd_addr;
	u32 en;
};

int rt_osd2_init(void);
int rt_osd2_deinit(int ch, int voe_ch_cnt);
BOOL rt_osd2_is_inited(void);
int rt_osd2_init_chn_profile(int chn_id, enum RTS_AV_FMT fmt, uint32_t width, uint32_t height, 
		uint32_t numerator, uint32_t denominator);
BOOL rt_osd2_chn_profile_is_inited(int chn_id);

// @width, @height:
// if @width or @height = 0 means "use current width & height to do encode".
// else it will set width & height before encode & restore back after encode.
//
// @output:
//  (1) the programmer must do malloc()/free() totally by himself
//      before/after calling rt_osd2_encode().
//  (2) the buffer must be aligned on 32-byte boundary!!
//
int rt_osd2_encode(int chn_id, int buf_id, void *frm_dat, u32 frm_len);

typedef struct {
	int blk_idx;

	struct rts_video_osd2_attr *attr;
	enum rts_osd2_blk_fmt blk_fmt;
	uint32_t start_x;
	uint32_t start_y;
	uint32_t end_x;
	uint32_t end_y;
	uint32_t color_1bpp;

	uint8_t *buf;
	uint32_t len;

	int flick_enable;
	uint32_t show_time;
	uint32_t hide_time;
	uint8_t RSVD[12];
} rt_osd2_info_st;

typedef struct {
	void *font_lib_addr;

	uint8_t block_alpha;    //0~15
	uint32_t ch_color;
	uint8_t bg_enable;
	uint32_t bg_color;

	uint8_t h_gap : 4,
			v_gap : 4;

	uint8_t osd_char_w;
	uint8_t osd_char_h;

	enum rts_osd_time_fmt time_fmt;
	enum rts_osd_date_fmt date_fmt;
} rt_font_st;
#define OSD_COLOR_TABLE_R_NUM_MAX 32
#define OSD_COLOR_TABLE_G_NUM_MAX 32
#define OSD_COLOR_TABLE_B_NUM_MAX 32
#define OSD_COLOR_TABLE_A_NUM_MAX 16

typedef struct {

	int fmt;

	BOOL b_update_all;

	uint8_t ch_id;

	uint8_t r_idx;
	uint8_t g_idx;
	uint8_t b_idx;
	uint8_t a_idx;

	uint8_t r_val;
	uint8_t g_val;
	uint8_t b_val;
	uint8_t a_val;

	uint8_t r_val_full[OSD_COLOR_TABLE_R_NUM_MAX];
	uint8_t g_val_full[OSD_COLOR_TABLE_G_NUM_MAX];
	uint8_t b_val_full[OSD_COLOR_TABLE_B_NUM_MAX];
	uint8_t a_val_full[OSD_COLOR_TABLE_A_NUM_MAX];

	uint8_t RSVD[2];

} rt_osd2_color_table_st;

int rt_query_osd2_attr(int chn_id, int buf_id, struct rts_video_osd2_attr **attr);
int rt_update_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id);
int rt_enable_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id);
int rt_disable_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id);
int rt_set_color_table_osd2(rt_osd2_info_st *osd2, int chn_id, int buf_id, int fmt, uint32_t val,
				uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif	// __RT_OSD2_API_H__
