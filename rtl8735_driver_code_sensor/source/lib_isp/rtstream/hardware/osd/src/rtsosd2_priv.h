/*
 * Realtek Semiconductor Corp.
 *
 * libs/rtsosd/rtsosd_priv.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTSOSD_PRIV_H
#define _RTSOSD_PRIV_H

#include "../include/rtsosd.h"
#include "../include/rtsosd2.h"

#define RTS_OSD2_HEAD_BYTES		16
#define RTS_OSD2_MEM_SINGLE_BASE		0
#define RTS_OSD2_DOUBLE_INDEX		128
#define RTS_OSD2_DOUBLE_END		253
#define RTS_OSD2_MEM_ALIGN_SIZE		4
#define RTS_OSD2_MEM_ATTR_SIZE		96
#define RTS_OSD2_MEM_RESERVED_SIZE	256
#define RTS_OSD2_BLK_MIN_LENGTH		8
#define RTS_OSD2_BLK_SX_DFG		0
#define RTS_OSD2_BLK_SY_DFG		0
#define RTS_OSD2_BLK_EX_DFG		160
#define RTS_OSD2_BLK_EY_DFG		60
#define RTS_OSD2_BLK_ROW_DFT		255
#define rts_osd2_blk_tEXT_NUM		128
#define RTS_OSD2_LIB_FILENAME_LEN	256
#define RTS_OSD2_SINGLE_MAX_LEN		256
#define RTS_OSD2_DOUBLE_MAX_LEN		1024

#define RTS_OSD2_SINGLE_ALL_1		0xfe
#define RTS_OSD2_SINGLE_ALL_0		0xff


struct osd2_font_lib_header_t {
	uint16_t header_length;
	enum osd_char_type char_type;
	uint16_t char_width;
	uint16_t char_height;
	uint16_t width_bytes;
	enum {
		font_song = 0,
	} font_type;
	uint8_t font_size;
	enum {
		coding_utf8 = 0,
		coding_gbk = 1
	} coding_fmt;
	uint8_t char_num;
	uint8_t char_rotation;
	uint8_t reserved[2];
};

struct rts_osd2_font_lib_t {
	uint32_t lib_addr;

	struct osd2_font_lib_header_t header;
	uint16_t mapping_length;
	uint8_t *mapping_info;

	uint16_t start;
	uint16_t size;

	uint32_t lattice_size;

	int load;
	int inuse;
};

/*struct rts_osd2_blk_t {
	int blk_enable;
	struct rts_isp_osd_blk_attr blk_attr;
	uint8_t pdisplay[RTS_OSD2_MEM_RESERVED_SIZE - RTS_OSD2_MEM_ATTR_SIZE];
	unsigned int display_number;
	uint16_t offset;
	uint8_t picidx;
	struct rts_osd_char_t blk_text[rts_osd2_blk_tEXT_NUM];
	unsigned int blk_text_len;
	uint8_t char_type;


	unsigned int bg_color;
	unsigned int ch_color;
};*/

struct rts_osd2_datetime_show {
	int enable;
	uint8_t blkidx;
	int pos;
	uint8_t length;
	uint8_t show_buf[32];
};

/*int rts_osd2_update_attr(struct rts_osd2_t *posd, uint8_t blkidx,
		struct rts_osd2_blk_t *pblk);
int rts_osd2_refresh_blk(struct rts_osd2_t *posd, uint8_t blkidx,
		struct rts_osd2_blk_t *pblk);
int find_single_char_index(struct rts_osd2_t *posd, unsigned char ch);
*/

#endif
