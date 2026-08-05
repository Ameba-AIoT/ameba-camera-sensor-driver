#ifndef RT_UTIL_H
#define RT_UTIL_H
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// caution!!
//	this function only allow one call in the same printf.
//  the following example will lead to wrong result.
//    printf("%s, %s\n", rt_code_str(err0), rt_code_str(err1));
//
char    *rt_code_str(int code);

// brief: the 3-area format dump option
//
//  |-- ADDR --| : |-- BODY --| (SPACES) |-- NOTE --|
//
typedef struct
{
	union {
		u32		value;
		struct {
		BOOL	addr_show:1;
		BOOL	note_show:1;
		BOOL	body_ascii:1;	// is ascii or hex
		BOOL	body_uboot:1;	// when body_ascii = FALSE
								//  TRUE : 04030201
								//  FALSE: 01 02 03 04
		};
	} flag;
	u32     addr_start;
} rt_dump_opt_st;


// brief: dump memory
// example:
//  \n
// 0x00000000: 30 31 32 33 34 35 36 37 38 39 41 42 43 44 45 46     0123456789ABCDEF
// 0x00000010: 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56     GHIJKLMNOPQRSTUV
//  ...
//  \n
//
// @opt: NULL mean using default settings
int rt_dump_mem_ex(unsigned int adr, unsigned int len, rt_dump_opt_st *opt);
#define rt_dump_mem(a, l)	rt_dump_mem_ex((a), (l), NULL)

void rt_dump_ld_symbols(void);

// for convenient, can remove in future.
void rt_dump_buf_ex(void *_buf, int _len, unsigned int _show_addr);
#define rt_dump_buf(buf, len)	rt_dump_buf_ex((buf), (len), 0)
void rt_dump_reg(char *title, unsigned int *regs, int cnt);

// brief: convert size to IEC prefix string.
//        "xxx KiB", "xxx.y KiB", "xxx MiB", "xxx.y MiB",...,etc.
// eg:
//  1024		-> 1 KiB
//  1024*1024	-> 1 MiB
//
char *size_to_str(unsigned long long size, char out[32]);


// note: for the definition of BLANK char, plz directly ref source code.
int str_is_blank_line(const char *str);
BOOL str_is_numeric(char *str);
void str_remove_line_comment(char *str, char delim);
// replace all 'before' char in 'str' to 'after'
void str_replace_char(char *str, char before, char after);
// return:
//  RT_E_INVALID_DATA: will set 'val' = 0
//
int strtol_base10(const char *str, int *val);
// note: assume that the leftmost 2 char is '0x' or '0X'
// return:
//  RT_E_INVALID_DATA: will set 'val' = 0
//
int strtol_base16(const char *str, int *val);
// return:
//  RT_E_INVALID_DATA: will set 'val' = 0
int strtol_base1610(const char *str, int *val);

void env_print(void);
int env_load(pair_cstr_cstr_st arr[], int arr_size);

// brief: try to assign g_env_default[] from hconf env entries.
void env_try_load_hconf(void);
// brief:save g_env_default[] to hconf env entries.
void env_save_hconf(void);

#define env_get_str			getenv
#define env_set_str(s, v)	setenv((s), (v), 1)

int env_get_i32(char *str, int *val);
int env_get_u32(char *str, unsigned int *val);

#define env_set_i32(s, v)	env_set_fmt_i64((s), "%d", (v))
#define env_set_u32(s, v)	env_set_fmt_i64((s), "%d", (v))

#define env_set_fmt_i32		env_set_fmt_i64
#define env_set_fmt_u32		env_set_fmt_i64
int env_set_fmt_i64(char *str, char *fmt, long long val);

// ----------------------------------------------------------------------------
//  mmc fatfs
// ----------------------------------------------------------------------------
//       @is_hex    @sz
// text: 0          N/A
// hex : 1          (int)
int rt_f_dumpfile(char *abs_path, BOOL is_hex, int sz);
int rt_f_read_buf(char *abs_path, void *buf, UINT len, UINT *nread);
int rt_f_save_buf(char *abs_path, void *buf, UINT len);

// (1) if file not exist, equal to rt_f_save_buf()
// (2) if file     exist, write buf to end of file.
//
int rt_f_append_buf(char *abs_path, void *buf, UINT len);

// = f_seek + f_write. fopen flag is RT_OPEN_EXISTING
// file must be exist.
int rt_f_update_buf(char *abs_path, void *buf, UINT len, int ofs);

#ifdef __cplusplus
}
#endif

#endif	// RT_UTIL_H

