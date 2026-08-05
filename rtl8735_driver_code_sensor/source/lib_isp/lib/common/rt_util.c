#include <stdio.h>
#include <stdlib.h>


char    *rt_code_str(int code)
{
	static char rt_code_buf[32];

	sprintf(rt_code_buf, "RT_CODE(%d)", code);
	return rt_code_buf;
}










#if 0
#include <unistd.h>
#include <ctype.h>

#include "FreeRTOSConfig.h"

#include "rt_util.h"
#include "rt_log.h"
#include "rt_hconf.h"
//#include "rt_console.h"
//#include "rt_fs.h"
//#include "rt_mmc.h"

#include "cmsis_rtx.h"
#include "rlx_reg.h"
#include "rlx_lds.h"

char    *rt_code_str(int code)
{
	static char rt_code_buf[32];

	if (code == RT_OK)                 return "RT_OK";
#if DEBUG
	if (code == RT_E_ALREADY_OPEN)     return "RT_E_ALREADY_OPEN";
	if (code == RT_E_INIT_FAIL)        return "RT_E_INIT_FAIL";
	if (code == RT_E_OPEN_FAIL)        return "RT_E_OPEN_FAIL";
	if (code == RT_E_TIMEOUT)          return "RT_E_TIMEOUT";
	if (code == RT_E_OUT_OF_RANGE)     return "RT_E_OUT_OF_RANGE";
	if (code == RT_E_NOT_INIT)         return "RT_E_NOT_INIT";
	if (code == RT_E_NOT_FOUND)        return "RT_E_NOT_FOUND";
	if (code == RT_E_NOT_OPEN)         return "RT_E_NOT_OPEN";
	if (code == RT_E_NOT_SUPPORT)      return "RT_E_NOT_SUPPORT";
	if (code == RT_E_NOT_MATCH)        return "RT_E_NOT_MATCH";
	if (code == RT_E_ALREADY_INIT)     return "RT_E_ALREADY_INIT";
	if (code == RT_E_ALREADY_START)    return "RT_E_ALREADY_START";
	if (code == RT_E_ALREADY_STOP)     return "RT_E_ALREADY_STOP";
	if (code == RT_E_INVALID_DATA)     return "RT_E_INVALID_DATA";
	if (code == RT_E_INVALID_ARG)      return "RT_E_INVALID_ARG";
	if (code == RT_E_INVALID_SIZE)     return "RT_E_INVALID_SIZE";
	if (code == RT_E_INVALID_ID)       return "RT_E_INVALID_ID";
	if (code == RT_E_INVALID_STATE)    return "RT_E_INVALID_STATE";
	if (code == RT_E_INVALID_MODE)     return "RT_E_INVALID_MODE";
#endif
	sprintf(rt_code_buf, "RT_CODE(%d)", code);
	return rt_code_buf;
}

// brief: dump memory
// example:
//  \n
// 0x00000000: 30 31 32 33 34 35 36 37 38 39 41 42 43 44 45 46     0123456789ABCDEF
// 0x00000010: 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53 54 55 56     GHIJKLMNOPQRSTUV
//  ...
//  \n
//
// @opt: NULL mean using default settings
int rt_dump_mem_ex(unsigned int adr, unsigned int len, rt_dump_opt_st *opt)
{
	#define CH(c)   ((32 <= (c) && (c) <= 126) ? (c) : '.')
	#define SPACES  ("    ")

	rt_dump_opt_st def = {0};
	u32 pos, i;
	u8 v[16];

	if (opt == NULL)
	{
		def.flag.addr_show = 1;
		def.addr_start = adr;
		opt = &def;
	}
	pos = opt->addr_start;
	if (opt->flag.body_uboot)
		goto uboot_fmt;
	//
	while (len >= 16)
	{
		for (i = 0; i < 16; i++)
			v[i] = REG_R8(adr + i);

		if (opt->flag.addr_show)
			rt_printf("0x%08X: ", (int)pos);

		rt_printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
				v[0], v[1], v[2], v[3],
				v[4], v[5], v[6], v[7],
				v[8], v[9], v[10], v[11],
				v[12], v[13], v[14], v[15]);
		if (opt->flag.note_show)
		{
			rt_printf(SPACES);
			rt_printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
					   CH(v[0]), CH(v[1]), CH(v[2]), CH(v[3]),
					   CH(v[4]), CH(v[5]), CH(v[6]), CH(v[7]),
					   CH(v[8]), CH(v[9]), CH(v[10]), CH(v[11]),
					   CH(v[12]), CH(v[13]), CH(v[14]), CH(v[15]));
		}
		rt_printf("\n");
		adr += 16;
		len -= 16;
		pos += 16;
	}
	if (len > 0)
	{
		if (opt->flag.addr_show)
			rt_printf("0x%08X: ", (int)pos);

		for (i = 0; i < len; i++)
			v[i] = REG_R8(adr + i);

		for (i = 0; i < 16; i++)
		{
			if (i < len)
				rt_printf("%02X ", v[i]);
			else
				rt_printf("   ");
		}
		if (opt->flag.note_show)
		{
			rt_printf(SPACES);
			for (i = 0; i < len; i++)
				rt_printf("%c", CH(v[i]));
		}
		rt_printf("\n");
	}
	return RT_OK;

uboot_fmt:
	while (len >= 16)
	{
		for (i = 0; i < 16; i++)
			v[i] = REG_R8(adr + i);

		if (opt->flag.addr_show)
			rt_printf("0x%08X: ", (int)pos);

		rt_printf("%02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x ",
					v[3], v[2], v[1], v[0],
					v[7], v[6], v[5], v[4],
					v[11], v[10], v[9], v[8],
					v[15], v[14], v[13], v[12]);
		if (opt->flag.note_show)
		{
			rt_printf(SPACES);
			rt_printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
					CH(v[0]), CH(v[1]), CH(v[2]), CH(v[3]),
					CH(v[4]), CH(v[5]), CH(v[6]), CH(v[7]),
					CH(v[8]), CH(v[9]), CH(v[10]), CH(v[11]),
					CH(v[12]), CH(v[13]), CH(v[14]), CH(v[15]));
		}
		adr += 16;
		len -= 16;
		pos += 16;
	}
	if (len > 0)
	{
		if (len % 4)    // make 'len' be multiple of 4
			len += (4 - (len % 4));

		for (i = 0; i < len; i++)
			v[i] = REG_R8(adr + i);

		if (opt->flag.addr_show)
			rt_printf("0x%08X: ", (int)pos);

		for (i = 0; i < 16; i += 4)
		{
			if (i < len)
				rt_printf("%02x%02x%02x%02x ", v[i+3], v[i+2], v[i+1], v[i+0]);
			else
				rt_printf("         ");
		}
		if (opt->flag.note_show)
		{
			rt_printf(SPACES);
			for (i = 0; i < 16; i += 4)
			{
				if (i < len)
					rt_printf("%c%c%c%c", CH(v[i+0]), CH(v[i+1]), CH(v[i+2]), CH(v[i+3]));
			}
		}
		rt_printf("\n");
	}
	return RT_OK;
}

extern void *__text_start__;
extern void *__text_end__;
extern void *__data_start__;
extern void *__data_end__;
extern void *__bss_start__;
extern void *__bss_end__;
extern void *__HeapBase;
extern void *__HeapLimit;
extern void *__sys_mem_start__;
extern void *__sys_mem_end__;

void rt_dump_ld_symbols(void)
{
	u32 n;
	char s[32];
	rt_printf("__sys_mem_start__ : 0x%08X\n", (unsigned int)&__sys_mem_start__);
	rt_printf("__text_start__    : 0x%08X\n", (unsigned int)&__text_start__);
	rt_printf("__text_end__      : 0x%08X\n", (unsigned int)&__text_end__);
	rt_printf("__data_start__    : 0x%08X\n", (unsigned int)&__data_start__);
	rt_printf("__data_end__      : 0x%08X\n", (unsigned int)&__data_end__);
	rt_printf("__bss_start__     : 0x%08X\n", (unsigned int)&__bss_start__);
	rt_printf("__bss_end__       : 0x%08X\n", (unsigned int)&__bss_end__);
	rt_printf("__HeapBase        : 0x%08X\n", (unsigned int)&__HeapBase);
	rt_printf("__HeapLimit       : 0x%08X\n", (unsigned int)&__HeapLimit);
	rt_printf("__StackLimit      : 0x%08X\n", (unsigned int)&__StackLimit);
	rt_printf("__StackTop        : 0x%08X\n", (unsigned int)&__StackTop);
	rt_printf("TDNR_START        : 0x%08X\n", (unsigned int)TDNR_START);
	rt_printf("VRAM_START        : 0x%08X\n", (unsigned int)VRAM_START);
	rt_printf("__sys_mem_end__   : 0x%08X\n", (unsigned int)&__sys_mem_end__);

	rt_printf("\n---- size ----\n");
	n = (unsigned int)&__text_end__ - (unsigned int)&__text_start__;
	rt_printf("text    : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__data_end__ - (unsigned int)&__data_start__;
	rt_printf("data    : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__bss_end__ - (unsigned int)&__bss_start__;
	rt_printf("bss     : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__HeapLimit - (unsigned int)&__HeapBase;
	rt_printf("Heap    : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__StackTop - (unsigned int)&__StackLimit;
	rt_printf("Stack   : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)VRAM_START - (unsigned int)TDNR_START;
	rt_printf("TDNR    : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__sys_mem_end__ - (unsigned int)VRAM_START;
	rt_printf("VRAM    : %8u (%s)\n", n, size_to_str(n, s));
	n = (unsigned int)&__sys_mem_end__ - (unsigned int)&__sys_mem_start__;
	rt_printf("SYS_MEM : %8u (%s)\n", n, size_to_str(n, s));
}

void rt_dump_buf_ex(void *_buf, int _len, unsigned int _show_addr)
{
	unsigned char *buf = (unsigned char *)_buf;

	for (int i = 0; i < _len; i++)
	{
		if (i % 16 == 0)
		{
			if (_show_addr)
				my_printf("\n0x%08x: ", i);
			else
				my_printf("\n");
		}
		//
		my_printf("%02x ", buf[i]);
	}
	my_printf("\n");
}

void rt_dump_reg(char *title, unsigned int *regs, int cnt)
{
	my_printf("\n(reg dump)");
	if (title)
		my_printf("%s", title);
	my_printf("\n");

	for (int i = 0; i < (int)cnt; i++)
		my_printf("[%08X] = 0x%08X\n", regs[i], 0); //(unsigned int)REG_R32(regs[i]));
}

// note: assume that the leftmost 2 char is '0x' or '0X'
// note: 'val' will set to 0 if fail
//
int strtol_base16(const char *str, int *val)
{
	int i, n, len;
	int ret = RT_E_INVALID_ARG;

	len = strlen(str);
	if (len <= 2)
		goto exit;
	//
	if (str[0] != '0')
		goto exit;
	//
	(*val) = 0;
	for (i = 2; i < len; i++)
	{
		n = -1;
		if (('0' <= str[i]) && (str[i] <= '9'))
			n = (str[i] - '0');
		else if (('a' <= str[i]) && (str[i] <= 'f'))
			n = (str[i] - 'a') + 10;
		else if (('A' <= str[i]) && (str[i] <= 'F'))
			n = (str[i] - 'A') + 10;
		//
		if (n < 0)
			goto exit;
		//
		(*val) = (*val)*16 + n;
	}
	ret = RT_OK;

exit:
	if (ret != RT_OK)
		(*val) = 0;
	return ret;
}

// note: 'val' will set to 0 if fail
int strtol_base10(const char *str, int *val)
{
	int i, len, negative;
	int ret = RT_E_INVALID_ARG;

	if ((len = strlen(str)) == 0)
		goto exit;
	//
	negative = 0;
	(*val) = 0;
	for (i = 0; i < len; i++)
	{
		if (str[i] == '-')
		{
			negative = 1;
			continue;
		}
		if ((str[i] < '0') || (str[i] > '9'))
			goto exit;
		//
		(*val) = (*val)*10 + (str[i] - '0');
	}
	if (negative == 1)
	{
		(*val) *= -1;
	}
	ret = RT_OK;

exit:
	if (ret != RT_OK)
		(*val) = 0;
	return ret;
}

// note: 'val' will set to 0 if fail
int strtol_base1610(const char *str, int *val)
{
	if (strtol_base10(str, val) == RT_OK)
		return RT_OK;
	if (strtol_base16(str, val) == RT_OK)
		return RT_OK;

	(*val) = 0;
	return RT_E_INVALID_ARG;
}

char *size_to_str(unsigned long long size, char out[32])
{
	static const char names[] = {'B', 'K', 'M', 'G', 'T'};
	unsigned long long div = 1;
	int i;
	char c = 0;

	for (i = 0; i < (int)ARRAY_SIZE(names); i++)
	{
		if (size < div*1024)
		{
			c = names[i];
			break;
		}
		div *= 1024;
	}
	if (c == 'B')
	{
		sprintf(out, "%llu Bytes", size);
		return out;
	}

	unsigned long long q = size / div;		// quotient
	unsigned long long r = size - q*div;	// remainder
	if (r == 0)
	{
		sprintf(out, "%llu %ciB", q, c);
	}
	else
	{
		unsigned long long n = div/100;
		for (i = 0; i < 100; i++)
		{
			if (n*(i+1) >= r)
				break;
		}
		sprintf(out, "%llu.%02d %ciB", q, i, c);
	}
	return out;
}

int str_is_blank_line(const char *str)
{
	int i;

	i = 0;
	while (i < (int)strlen(str))
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0' || str[i] == ASCII_LF)
		{
			i++;
			continue;
		}
		if (str[i] == ASCII_CR && str[i+1] == ASCII_LF)
		{
			i += 2;
			continue;
		}
		//else, meet non blank char.
		return 0;
	}
	return 1;
}

BOOL str_is_numeric(char *str)
{
	int i = 0;

	for (i = 0; i < (int)strlen(str); i++)
	{
		if (!isdigit(str[i]))
			return FALSE;
	}

	return TRUE;
}

void str_remove_line_comment(char *str, char delim)
{
	char *p;

	if ((p = strchr(str, delim)) == NULL)
		return;
	*p = '\0';
	// for (int i=0; i<(int)strlen(str); i++)  // to avoid infinite loop.
	// {
	//     if (((*p) == '\0') || ((*p) == ASCII_LF))
	//         break;
	//     if ((*p == ASCII_CR) && *(p+1) == ASCII_LF)
	//         break;
	//     *p++ = ' ';
	// }
	return;
}

// replace all 'before' char in 'str' to 'after'
void str_replace_char(char *str, char before, char after)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (str[i] == before)
			str[i] = after;
	}
}

static BOOL s_env_hconf_loaded = FALSE;
extern pair_cstr_cstr_st g_env_default[];
void env_try_load_hconf(void)
{
	if (s_env_hconf_loaded)
		return;

#if CFG_FEATURE_HCONF
	if (!hconf_is_exist())
		return;
	// note: don't use strcpy()
	int i = 0;
	g_env_default[i++].second = hconf_get_strptr(ENV_INIT_SCRIPT);
	g_env_default[i++].second = hconf_get_strptr(ENV_DHCP);
	g_env_default[i++].second = hconf_get_strptr(ENV_ETHADDR);
	g_env_default[i++].second = hconf_get_strptr(ENV_IPADDR);
	g_env_default[i++].second = hconf_get_strptr(ENV_NETMASK);
	g_env_default[i++].second = hconf_get_strptr(ENV_GATEWAYIP);
	g_env_default[i++].second = hconf_get_strptr(ENV_SERVERIP);
	g_env_default[i++].second = hconf_get_strptr(ENV_NTPSERVER);
	g_env_default[i++].second = hconf_get_strptr(ENV_MBUF);
#endif
	s_env_hconf_loaded = TRUE;
	return;
}

void env_save_hconf(void)
{
	hconf_set_string(ENV_INIT_SCRIPT,  env_get_str("init.script"), 256);
	hconf_set_string(ENV_DHCP,         env_get_str("dhcp"),        4);
	hconf_set_string(ENV_ETHADDR,      env_get_str("ethaddr"),     20);
	hconf_set_string(ENV_IPADDR,       env_get_str("ipaddr"),      20);
	hconf_set_string(ENV_NETMASK,      env_get_str("netmask"),     20);
	hconf_set_string(ENV_GATEWAYIP,    env_get_str("gatewayip"),   20);
	hconf_set_string(ENV_SERVERIP,     env_get_str("serverip"),    20);
	hconf_set_string(ENV_NTPSERVER,    env_get_str("ntpserver"),   32);
	hconf_set_string(ENV_MBUF,         env_get_str("mbuf"),        16);
}

void env_print(void)
{
	int i = 1;
	char *s = *environ;

	for (; s; i++)
	{
		rt_printf("%s\n", s);
		s = *(environ+i);
	}
	return;
}

int env_load(pair_cstr_cstr_st arr[], int arr_size)
{
	int i;

	for (i = 0; i < arr_size; i++)
	{
		env_set_str(arr[i].first, arr[i].second);
	}
	return RT_OK;
}

int env_get_i32(char *str, int *val)
{
	int _i32;

	char *env_str = (char *)env_get_str(str);
	if ((env_str) && (strtol_base1610(env_str, &_i32) != RT_OK))
		return RT_E_INVALID_ENV_VAR;

	*val = _i32;
	return RT_OK;
}

int env_get_u32(char *str, unsigned int *val)
{
	int _i32;

	char *env_str = (char *)env_get_str(str);
	if ((env_str) && (strtol_base1610(env_str, &_i32) != RT_OK))
		return RT_E_INVALID_ENV_VAR;

	*val = (unsigned int)_i32;
	return RT_OK;
}

int env_set_fmt_i64(char *str, char *fmt, long long val)
{
	char    buf[32] = {0};

	if ((!str) || (!fmt))
		return RT_E_INVALID_ARG;

	sprintf(buf, fmt, val);
	if (env_set_str(str, buf) == 0)
		return RT_OK;

	return RT_E_OPERATE_FAIL;
}

int rt_f_dumpfile(char *abs_path, BOOL is_hex, int sz)
{
#define BUF_SIZE    512

	rt_dump_opt_st  opt = {0};
	int  len, offset, ln = 0;
	RT_FILE file;
	char buf[BUF_SIZE] = {0};
	int ret = RT_OK;
	UINT nread;

	if (!rt_fs_is_inited())
	{
		rt_printf("%s(): FS not init yet.\n", __func__);
		return RT_E_NOT_INIT;
	}
	if (is_hex)
		goto hex_mode;
//text_mode:
	if ((ret = rt_f_open(&file, abs_path, FA_OPEN_EXISTING | FA_READ)) != RT_OK)
	{
		rt_printf("error! rt_f_open, %s\n", abs_path);
		return ret;
	}
	console_flush();
	ln = 0;
	do {
		if (rt_f_gets(&file, buf, sizeof(buf)) == NULL)
		{
			if (!rt_f_eof(&file))
			{
				rt_printf("error! rt_f_gets, %d\n", ret);
			}
			break;
		}
		rt_printf("%04d: %s", ln++, buf);
		console_flush();
	} while (!rt_f_eof(&file));
	console_flush();
	rt_f_close(&file);
	return ret;
hex_mode:
	offset = 0;
	opt.flag.addr_show = 1;
	opt.flag.note_show = 1;
	console_flush();
	while (sz)
	{
		len = (sz > BUF_SIZE) ? BUF_SIZE : sz;
		sz -= len;
		ret = rt_fs_fread_buf(abs_path, buf, len, offset, &nread);
		if (ret != RT_OK)
		{
			rt_printf("%s(): fread_buf, %s, offset= %d, len= %d\n", __func__, rt_code_str(ret), offset, len);
			break;
		}
		if ((int)nread != len)
		{
			rt_printf("%s(): fread_buf, nread(%d) != len(%d), offset= %d\n", __func__, nread, len, offset);
			ret = RT_E_OPERATE_FAIL;
			break;
		}
		//else, success.
		opt.addr_start = offset;
		rt_dump_mem_ex((uint32_t)buf, len, &opt);
		//
		offset += len;
		console_flush();
	}
	console_flush();
	return ret;
}

int rt_f_read_buf(char *abs_path, void *buf, UINT len, UINT *nread)
{
	RT_FILE file;
	UINT nr;
	int ret = RT_OK;

	if ((ret = rt_f_open(&file, abs_path, FA_OPEN_EXISTING | FA_READ)) != RT_OK)
	{
		rt_printf("rt_f_read_buf(): f_open, %s\n", rt_code_str(ret));
		return ret;
	}
	if (rt_f_size(&file) > len)
	{
		ret = RT_E_NOT_ENOUGH_BUF;
		rt_printf("rt_f_read_buf(): buf len too small, %s\n", rt_code_str(ret));
		goto exit;
	}
	if ((ret = rt_f_read(&file, buf, len, &nr)) != RT_OK)
	{
		rt_printf("rt_f_read_buf(): f_read, %s\n", rt_code_str(ret));
		goto exit;
	}
	*nread = nr;
exit:
	rt_f_close(&file);
	return ret;
}

int rt_f_save_buf(char *abs_path, void *buf, UINT len)
{
	RT_FILE file;
	UINT nw;
	int ret = RT_OK;

	if ((ret = rt_f_open(&file, abs_path, FA_CREATE_ALWAYS | FA_WRITE)) != RT_OK)
	{
		rt_printf("rt_f_save_buf(): f_open, %s\n", rt_code_str(ret));
		return ret;
	}
	if ((ret = rt_f_write(&file, buf, len, &nw)) != RT_OK)
	{
		rt_printf("rt_f_save_buf(): f_write, %s\n", rt_code_str(ret));
		goto exit;
	}
	if (nw != len)
	{
		rt_printf("rt_f_save_buf(): f_write, nw(%d) != len (%d)\n", (int)nw, (int)len);
		goto exit;
	}
	ret = RT_OK;
exit:
	rt_f_close(&file);
	return ret;
}

// (1) if file not exist, equal to rt_f_save_buf()
// (2) if file     exist, write buf to end of file.
//
int rt_f_append_buf(char *abs_path, void *buf, UINT len)
{
	RT_FILE file;
	UINT nw;
	int ret = RT_OK;
	u32 size;

	if (!rt_fs_is_exist(abs_path))
	{
		return rt_f_save_buf(abs_path, buf, len);
	}
	//
	if ((ret = rt_f_open(&file, abs_path, FA_OPEN_EXISTING | FA_WRITE)) != RT_OK)
	{
		rt_printf("rt_f_append_buf(): f_open, %s\n", rt_code_str(ret));
		return ret;
	}
	size = rt_f_size(&file);
	if ((ret = rt_f_lseek(&file, size)) != RT_OK)
	{
		rt_printf("rt_f_append_buf(): f_lseek, %s\n", rt_code_str(ret));
		goto exit;
	}
	if ((ret = rt_f_write(&file, buf, len, &nw)) != RT_OK)
	{
		rt_printf("rt_f_append_buf(): f_write, %s\n", rt_code_str(ret));
		goto exit;
	}
	if (nw != len)
	{
		rt_printf("rt_f_append_buf(): f_write, nw(%d) != len (%d)\n", (int)nw, (int)len);
		goto exit;
	}
	ret = RT_OK;
exit:
	rt_f_close(&file);
	return ret;
}

// = f_seek + f_write. fopen flag is RT_OPEN_EXISTING
// file must be exist.
//
int rt_f_update_buf(char *abs_path, void *buf, UINT len, int ofs)
{
	RT_FILE file;
	UINT nw;
	int size, pos;
	int ret = RT_OK;

	if (!rt_fs_is_exist(abs_path))
	{
		rt_printf("rt_f_update_buf(): path not exist, %s\n", abs_path);
		return RT_E_NOT_EXIST;
	}
	//
	if ((ret = rt_f_open(&file, abs_path, FA_OPEN_EXISTING | FA_WRITE)) != RT_OK)
	{
		rt_printf("rt_f_update_buf(): f_open, %s\n", rt_code_str(ret));
		return ret;
	}
	size = rt_f_size(&file);
	pos = min(size, ofs);
	if ((ret = rt_f_lseek(&file, pos)) != RT_OK)
	{
		rt_printf("rt_f_update_buf(): f_lseek, %s\n", rt_code_str(ret));
		goto exit;
	}
	if ((ret = rt_f_write(&file, buf, len, &nw)) != RT_OK)
	{
		rt_printf("rt_f_update_buf(): f_write, %s\n", rt_code_str(ret));
		goto exit;
	}
	if (nw != len)
	{
		rt_printf("rt_f_update_buf(): f_write, nw(%d) != len (%d)\n", (int)nw, (int)len);
		goto exit;
	}
	ret = RT_OK;
exit:
	rt_f_close(&file);
	return ret;
}
#endif
