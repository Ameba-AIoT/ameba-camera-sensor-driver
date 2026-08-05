#ifndef __RT_HCONF_H
#define __RT_HCONF_H
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"
#include "rt_hconf_data.h"

typedef struct
{
	int		id;
	char	*name;
	int		type;
	int		len;
	union
	{
		int def_cfg;
		char *def_str;
	};
	int offset;
} hconf_entry_st;


// brief: init hconf framework.
void	hconf_init(void);
BOOL	hconf_is_inited(void);
void	hconf_load_global(void);

typedef struct
{
	u8	major;
	u8	minor;
} hconf_version_st;

void	hconf_get_version(hconf_version_st *out);

// brief: check against MAGIC & VERSION.
BOOL	hconf_check(void);
int		hconf_set_hconf_addr(void *addr);
void	*hconf_get_hconf_addr(void);

// return:
//  if success, return current value of @id.
//  if fail,    return @old_value.
//
int		hconf_get_config(int id, int old_value);
// return rt_code.
int		hconf_set_config(int id, int value);

// return NULL if fail.
char	*hconf_get_strptr(int id);
// note: @string is changed only if success.
// return: rt_code
int		hconf_get_string(int id, INOUT char *string, int len);
// return: rt_code
int		hconf_set_string(int id, IN char *string, int len);

void	hconf_restore(void);
// brief: memory block formatted to default at @mem_addr.
void	hconf_set_default(void *mem_addr);
void	hconf_dump(void);
void	hconf_dump_hex(void);

BOOL	hconf_is_exist(void);
u32		hconf_size(void);
u32		hconf_max_size(void);

int		hconf_cmd_get(char *id_name);
int		hconf_cmd_set(char *id_name, char *string);

int		hconf_get_shell(INOUT void *out);
int		hconf_get_strm_attr(int chn_id, INOUT void *out);
int		hconf_get_h264_attr(int chn_id, INOUT void *out);
// note: fout_prm_t.opt will not be get.
int		hconf_get_fout_prm(int chn_id, INOUT void *out);

#endif	// __RT_HCONF_H

