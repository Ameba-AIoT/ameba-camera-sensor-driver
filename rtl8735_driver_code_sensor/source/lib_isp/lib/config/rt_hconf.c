#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rt_hconf.h"
#include "rt_log.h"
#include "rt_util.h"
#include "rt_shell.h"
#include "rt_mtd.h"
#if defined(CONFIG_PLATFORM_RTS3905)
  #include "rtsavapi.h"
#endif
#include "mpool.h"

#if defined(CONFIG_PLATFORM_RTS3905)
  #include "mmf2_strm.h"
  #include "mmf2_module.h"
  #include "module_fout.h"
  #include "rt_osd2_api.h"
#endif

extern hconf_entry_st hconf_tbl[];

void *g_hconf = NULL;
BOOL s_is_inited = FALSE;

#define _check_exist()				\
do {								\
	if (!hconf_is_exist()) {		\
		rt_err("not exist\n");		\
		return RT_E_NOT_EXIST;		\
	}								\
} while (0)

int _get_cfg_entry_value(void *hconf_addr, hconf_entry_st *p, int old_value)
{
	RT_ASSERT(hconf_addr);
	RT_ASSERT(p);
	RT_ASSERT(p->type == HCONF_TYPE_CFG);

	void *entry_addr = hconf_addr + p->offset;
	int ret = old_value;
	switch (p->len)
	{
	case 1: ret = *(s8 *)entry_addr; break;
	case 2: ret = *(s16 *)entry_addr; break;
	case 4: ret = *(s32 *)entry_addr; break;
	default:
		rt_should_not_reach();
		break;
	}
	return ret;
}

static void _set_cfg_entry_value(void *hconf_addr, hconf_entry_st *p, int val)
{
	RT_ASSERT(hconf_addr);
	RT_ASSERT(p);
	RT_ASSERT(p->type == HCONF_TYPE_CFG);

	void *entry_addr = hconf_addr + p->offset;
	switch (p->len)
	{
	case 1: *(s8 *)entry_addr = (s8)val; break;
	case 2: *(s16 *)entry_addr = (s16)val; break;
	case 4: *(s32 *)entry_addr = (s32)val; break;
	default:
		rt_should_not_reach();
		break;
	}
}

void _get_str_entry_value(void *hconf_addr, hconf_entry_st *p, OUT char *str, int len)
{
	RT_ASSERT(hconf_addr);
	RT_ASSERT(p);
	RT_ASSERT(p->type == HCONF_TYPE_STR);

	void *entry_addr = hconf_addr + p->offset;

	memset(str, 0, len);
	strncpy(str, entry_addr, MIN(p->len, len));
}

static void _set_str_entry_value(void *hconf_addr, hconf_entry_st *p, char *val)
{
	RT_ASSERT(hconf_addr);
	RT_ASSERT(p);
	RT_ASSERT(p->type == HCONF_TYPE_STR);

	void *entry_addr = hconf_addr + p->offset;

	memset(entry_addr, 0, p->len);
	strncpy(entry_addr, val, p->len-1);
}

static hconf_entry_st *_get_entry_by_id(int id)
{
	hconf_entry_st *p = hconf_tbl;

	while (p->id != HCONF_MAX)
	{
		if (p->id == id)
			return p;
		//
		p++;
	}
	return NULL;
}

static hconf_entry_st *_get_entry_by_name(char *name)
{
	hconf_entry_st *p = hconf_tbl;

	while (p->id != HCONF_MAX)
	{
		if (!strcmp(p->name, name))
			return p;
		//
		p++;
	}
	return NULL;
}

// return:
//  if success, return current value of @id.
//  if fail,    return @old_value.
//
int hconf_get_config(int id, int old_value)
{
#if CFG_FEATURE_HCONF
	if (!hconf_is_inited())
		return old_value;
	if (!hconf_is_exist())
		return old_value;
	//
	hconf_entry_st *p = _get_entry_by_id(id);
	if (!p)
	{
		//my_error("invalid id, %d (0x%04X)\n", id, id);
		return old_value;
	}
	//
	return _get_cfg_entry_value(g_hconf, p, old_value);
#else
	return old_value;
#endif
}

// return rt_code.
int hconf_set_config(int id, int value)
{
	if (!hconf_is_inited())
		return RT_E_NOT_INIT;
	if (!hconf_is_exist())
		return RT_E_NOT_EXIST;
	//
	hconf_entry_st *p = _get_entry_by_id(id);
	if (!p)
	{
		//my_error("invalid id, %d (0x%04X)\n", id, id);
		return RT_E_INVALID_ID;
	}
	//
	_set_cfg_entry_value(g_hconf, p, value);
	return RT_OK;
}

int hconf_get_string(int id, INOUT char *string, int len)
{
#if CFG_FEATURE_HCONF
	if (!hconf_is_inited())
		return RT_E_NOT_INIT;
	if (!hconf_is_exist())
		return RT_E_NOT_EXIST;
	//
	hconf_entry_st *p = _get_entry_by_id(id);
	if (!p)
	{
		//my_error("invalid id, %d (0x%04X)\n", id, id);
		return RT_E_INVALID_ID;
	}
	//
	_get_str_entry_value(g_hconf, p, string, len);
#endif
	return RT_OK;
}

int hconf_set_string(int id, IN char *string, int len)
{
	if (!hconf_is_inited())
		return RT_E_NOT_INIT;
	if (!hconf_is_exist())
		return RT_E_NOT_EXIST;
	//
	hconf_entry_st *p = _get_entry_by_id(id);
	if (!p)
	{
		//my_error("invalid id, %d (0x%04X)\n", id, id);
		return RT_E_INVALID_ID;
	}
	//
	_set_str_entry_value(g_hconf, p, string);
	return RT_OK;
}

// return NULL if fail.
char *hconf_get_strptr(int id)
{
	RT_ASSERT(hconf_is_inited());
	RT_ASSERT(hconf_is_exist());

	if (hconf_group(id) != HCONF_GRP_STRTBL)
	{
		//my_error("not strtbl id, %d (0x%04X)\n", id, id);
		return NULL;
	}
	hconf_entry_st *p = _get_entry_by_id(id);
	if (!p)
	{
		//my_error("invalid id, %d (0x%04X)\n", id, id);
		return NULL;
	}
	//
	return (char *)(g_hconf + p->offset);
}

int hconf_cmd_get(char *id_name)
{
	hconf_entry_st *p;
	int id;

	if (!hconf_is_inited())
	{
		rt_printf("error! hconf not inited\n");
		return RT_E_NOT_EXIST;
	}
	if (!hconf_is_exist())
	{
		rt_printf("error! hconf not exist\n");
		return RT_E_NOT_EXIST;
	}
	if (strtol_base1610(id_name, &id) == RT_OK)
	{
		p = _get_entry_by_id(id);
	}
	else
	{
		p = _get_entry_by_name(id_name);
	}
	if (!p)
	{
		rt_printf("error! invalid id_name\n");
		return RT_E_INVALID_ARG;
	}
	//
	if (p->type == HCONF_TYPE_CFG)
	{
		int data = hconf_get_config(p->id, p->def_cfg);
		rt_printf("%d\n", data);
		return RT_OK;
	}
	if (p->type == HCONF_TYPE_STR)
	{
		char *str = hconf_get_strptr(p->id);
		rt_printf("%s\n", str ? str : "(null)");
		return RT_OK;
	}
	rt_should_not_reach();
	return RT_OK;
}

int hconf_cmd_set(char *id_name, char *string)
{
	hconf_entry_st *p;
	int id, ret, _i32;

	if (!hconf_is_inited())
	{
		rt_printf("error! hconf not inited\n");
		return RT_E_NOT_EXIST;
	}
	if (!hconf_is_exist())
	{
		rt_printf("error! hconf not exist\n");
		return RT_E_NOT_EXIST;
	}
	if (strtol_base1610(id_name, &id) == RT_OK)
	{
		p = _get_entry_by_id(id);
	}
	else
	{
		p = _get_entry_by_name(id_name);
	}
	if (!p)
	{
		rt_printf("error! invalid id_name\n");
		return RT_E_INVALID_ARG;
	}
	if (!string)
	{
		rt_printf("error! null string\n");
		return RT_E_INVALID_ARG;
	}
	//
	if (p->type == HCONF_TYPE_CFG)
	{
		if ((ret = strtol_base1610(string, &_i32)) != RT_OK)
		{
			rt_printf("error! invalid config value\n");
			return RT_E_INVALID_ARG;
		}
		ret = hconf_set_config(p->id, _i32);
		rt_printf("%d\n", _i32);
		rt_printf("\n%s\n", rt_code_str(ret));
		return ret;
	}
	if (p->type == HCONF_TYPE_STR)
	{
		ret = hconf_set_string(p->id, string, strlen(string));
		char *str = hconf_get_strptr(p->id);
		rt_printf("%s\n", str ? str : "(null)");
		rt_printf("\n%s\n", rt_code_str(ret));
		return ret;
	}
	rt_should_not_reach();
	return RT_OK;
}

// use hconf_tbl, gen offset
void hconf_init(void)
{
	hconf_entry_st *p = hconf_tbl;
	int offset[16] = {0};

	hconf_get_offset_info(offset);
	while (p->id != HCONF_MAX)
	{
		int group = (p->id) >> 8;

		p->offset = offset[group];
		offset[group] += p->len;

		p++;
	}
	s_is_inited = TRUE;
	return;
}

BOOL hconf_is_inited(void)
{
	return s_is_inited;
}

void hconf_version_from_val(hconf_version_st *out, u32 value)
{
	out->major = (value & MAKE_DWORD_LE(0, 0, 0xff, 0)) >> 16;
	out->minor = (value & MAKE_DWORD_LE(0, 0, 0, 0xff)) >> 24;
}

void hconf_get_version(hconf_version_st *out)
{
	hconf_version_from_val(out, VERSION_VALUE);
}

// brief: check against MAGIC & VERSION.
BOOL hconf_check(void)
{
	RT_ASSERT(hconf_is_inited());
	RT_ASSERT(hconf_is_exist());

	// MAGIC: must full match
	if (MAGIC_VALUE != *(u32 *)(g_hconf))
	{
		//my_debug("magic number check fail!\n");
		return FALSE;
	}
	hconf_version_st v0, v1;
	hconf_version_from_val(&v0, VERSION_VALUE);
	hconf_version_from_val(&v1, (*(u32 *)(g_hconf + 4)));
	// VERSION: MAJOR must match
	if (v1.major != v0.major)
	{
		//my_debug("major version check fail!\n");
		return FALSE;
	}
	// VERSION: MINOR must smaller or equal
	if (v1.minor > v0.minor)
	{
		//my_debug("minor version check fail!\n");
		return FALSE;
	}
	return TRUE;
}

void *hconf_get_hconf_addr(void)
{
	return (void *)g_hconf;
}

int hconf_set_hconf_addr(void *addr)
{
	if (!addr)
		return RT_E_NULL_POINT;

	g_hconf = addr;
	hconf_set_config(HCONF_ADDR, (u32)g_hconf);
	return RT_OK;
}

void hconf_set_default(void *mem_addr)
{
	hconf_entry_st *p = hconf_tbl;

	RT_ASSERT(hconf_is_inited());
	if (!mem_addr)
		return;
	while (p->id != HCONF_MAX)
	{
		if (p->type == HCONF_TYPE_CFG)
			_set_cfg_entry_value(mem_addr, p, p->def_cfg);
		else
			_set_str_entry_value(mem_addr, p, p->def_str);
		p++;
	}
	return;
}

void hconf_restore(void)
{
	RT_ASSERT(hconf_is_exist());
	RT_ASSERT(hconf_is_inited());
	hconf_set_default(g_hconf);
	hconf_set_config(HCONF_ADDR, (u32)g_hconf);
	return;
}

BOOL hconf_is_exist(void)
{
	return (g_hconf != NULL);
}

u32 hconf_size(void)
{
	return SZ_TOTAL;
}

u32 hconf_max_size(void)
{
	return CFG_HCONF_MAX_SIZE;
}

int hconf_get_shell(void *out)
{
#if CFG_FEATURE_HCONF
	_check_exist();
	shell_st *p = (shell_st *)out;
	p->hist_en = hconf_get_config(SHELL_HIST_EN, p->hist_en);
	hconf_get_string(SHELL_PROMPT_STR, p->prompt_str, 8);
#endif
	return RT_OK;
}

int hconf_get_strm_attr(int chn_id, INOUT void *out)
{
#if CFG_FEATURE_HCONF
	_check_exist();
	mm_strm_attr_st *p = (mm_strm_attr_st *)out;
	int n;

	if (0 <= chn_id && chn_id <= 2)
	{
		n = (MMF_S1_PAD - MMF_S0_PAD)*chn_id;	// distance
		p->fmt          = hconf_get_config(MMF_S0_VFORMAT + n, p->fmt);
		p->video.width  = hconf_get_config(MMF_S0_WIDTH   + n, p->video.width);
		p->video.height = hconf_get_config(MMF_S0_HEIGHT  + n, p->video.height);
	}
	else
	{
		// [TODO] AUDIO chn here.
		rt_should_not_reach();
	}
#endif
	return RT_OK;
}

int hconf_get_h264_attr(int chn_id, void *out)
{
#if CFG_FEATURE_HCONF
	_check_exist();
	rt_h264_attr_st *p = (rt_h264_attr_st *)out;
	int n = (MMF_S1_PAD - MMF_S0_PAD)*chn_id;	// distance

	p->level		= hconf_get_config(MMF_S0_H264_LEVEL		+ n, p->level);
	p->qp			= hconf_get_config(MMF_S0_H264_QP			+ n, p->qp);
	p->bitrate_mode	= hconf_get_config(MMF_S0_H264_BITRATE_MODE	+ n, p->bitrate_mode);
	p->bitrate		= hconf_get_config(MMF_S0_H264_BITRATE		+ n, p->bitrate);
	p->max_bitrate	= hconf_get_config(MMF_S0_H264_MAX_BITRATE	+ n, p->max_bitrate);
	p->min_bitrate	= hconf_get_config(MMF_S0_H264_MIN_BITRATE	+ n, p->min_bitrate);
	p->gop			= hconf_get_config(MMF_S0_H264_GOP			+ n, p->gop);
	p->videostab	= hconf_get_config(MMF_S0_H264_VIDEOSTAB	+ n, p->videostab);
#endif
	return RT_OK;
}

int hconf_get_fout_prm(int chn_id, INOUT void *out)
{
#if CFG_FEATURE_HCONF
	_check_exist();
	fout_prm_t *p = (fout_prm_t *)out;
	int n;
	char *str;

	if (0 <= chn_id && chn_id <= 2)
	{
		n = (MMF_S1_PAD - MMF_S0_PAD)*chn_id;	// distance
	}
	else
	{
		// [TODO] AUDIO chn here.
		rt_should_not_reach();
	}
	p->max_frames = hconf_get_config(MMF_S0_MAX_FRAMES + n,	p->max_frames);
	str = hconf_get_strptr(MMF_S0_FOUT_PATH + chn_id);
	if (str)
	{
		strncpy(p->path, str, MAX_PATH);
	}
#endif
	return RT_OK;
}

void hconf_load_global(void)
{
#if CFG_FEATURE_HCONF
	int ret_sf_read = RT_FAIL;
	BOOL ret_check = TRUE;

	u32 hconf_addr = (u32)RTK_Calloc(CFG_HCONF_MAX_SIZE);
	hconf_init();
	memset((void *)hconf_addr, 0, hconf_size());
	//
#if CFG_HCONF_FROM_SF
	// caution! the code here is based on the assumption:
	//  "before HCONF_START is VRAM region, it is safe to use here now."
	//
	u32 read_addr   = rt_sf_addr_rtos_hconf();
	u32 read_size   = rt_sf_size_rtos_hconf();
	ret_sf_read     = rt_sf_read(hconf_addr, read_addr, read_size);
#endif
	hconf_set_hconf_addr((void *)hconf_addr);
	if (ret_sf_read != RT_OK)
	{
		hconf_restore();
		goto hconf_end;
	}
	// sf_read success, check it's header
	ret_check = hconf_check();
	if (!ret_check)
	{
		rt_printf("hconf: check not pass\n");
		ret_sf_read = RT_FAIL;
		hconf_restore();
		goto hconf_end;
	}
	// fall through
hconf_end:
	rt_printf("hconf: addr 0x%08x, set %s\n", hconf_addr, (ret_sf_read == RT_OK && ret_check) ? "from sf" : "to default");
	return;
#endif    // CFG_FEATURE_HCONF
}

void hconf_dump(void)
{
	hconf_entry_st *p = hconf_tbl;
	int val;
	char *str;
	hconf_version_st ver;

	if (!hconf_is_exist())
	{
		rt_printf("hconf not exist!\n");
		return;
	}
	rt_printf("%7s  %-28s  %4s  %7s  %s\n", "id", "name", "len", "offset", "data");
	rt_printf("-------------------------------------------------------------------------------\n");
	while (p->id != HCONF_MAX)
	{
		rt_printf("(0x%03x)  %-28s  %4u  (0x%03x)  ", p->id, p->name, p->len, p->offset);
		if (p->type == HCONF_TYPE_CFG)
		{
			val = hconf_get_config(p->id, p->def_cfg);
			if (hconf_group(p->id) == HCONF_GRP_HEADER)
			{
				if (p->id == HCONF_MAGIC || p->id == HCONF_ADDR)
				{
					rt_printf("0x%0*x", (p->len)*2, val);
				}
				else if (p->id == HCONF_VERSION)
				{
					hconf_get_version(&ver);
					rt_printf("0x%0*x (v%d.%d)", (p->len)*2, val, ver.major, ver.minor);
				}
				else
				{
					rt_printf("0x%0*x (%d)", (p->len)*2, val, val);
				}
			}
			else
			{
				rt_printf("%d", val);
			}
		}
		else
		{
			str = hconf_get_strptr(p->id);
			rt_printf("%s", str ? str : "(null)");
		}
		rt_printf("\n");
		p++;
	}
	rt_printf("\n");
	return;
}

void hconf_dump_hex(void)
{
	if (!hconf_is_exist())
	{
		rt_printf("hconf not exist!\n");
		return;
	}
	rt_dump_opt_st  opt = {0};

	rt_printf("\n");
	opt.flag.note_show = 1;
	opt.flag.addr_show = 1;
	opt.addr_start = 0x0;
	rt_dump_mem_ex((unsigned int)g_hconf, SZ_TOTAL, &opt);
	rt_printf("\n");
}

