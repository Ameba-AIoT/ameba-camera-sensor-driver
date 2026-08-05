#include <stdio.h>
#include <stdlib.h>
#if 0
#include "rt_types.h"
#include "rt_code.h"
#include "rt_log.h"
#include "my_def.h"
#include "rt_shell.h"

#include "rt_util.h"
#include "rt_task.h"

#include "rt_console.h"
#include "rt_fs.h"


#define LINE_SZ		256

#define WIN_SZ		512
#define DSK_FILE	0
#define MEM_FILE	1

// shell script internal private data
typedef struct
{
	u8 stopmode;		// the mode of "when stop running shell script"
	u8 showline;		// show 'current exec line in script' or not.
	u8 ftype;			// DSK_FILE, MEM_FILE
	RT_FILE dfile;		// file obj of DSK_FILE
	void *mfile;		// file obj of MEM_FILE
	u32 fsize;			// file size
	u32 fpos;			// current file position
	u32 line;			// current line number

	u8 win[WIN_SZ];		// moving view window.
	u32 wlen;			// effective (real data) len in win[], must <= WIN_SZ
	u32 widx;			// current index in win[]
} scr_st;

static scr_st	scr;

void scr_dump(void)
{
#if DEBUG
	rt_printf("%-12s: %d\n", "stopmode", scr.stopmode);
	rt_printf("%-12s: %d\n", "showline", scr.showline);
	rt_printf("%-12s: %d\n", "ftype", scr.ftype);
	rt_printf("%-12s: 0x%08X\n", "mfile", (unsigned int)scr.mfile);
	rt_printf("%-12s: %d\n", "fsize", scr.fsize);
	rt_printf("%-12s: %d\n", "fpos", scr.fpos);
	rt_printf("%-12s: %d\n", "line", scr.line);
	rt_printf("%-12s: %d\n", "widx", scr.widx);
	rt_printf("%-12s: %d\n", "wlen", scr.wlen);
#endif
}

// note: 'fsize' is don't-care on DSK_FILE
static int scr_open(unsigned char ftype, void *path, int fsize)
{
	int ret = RT_OK;

	memset(&scr, 0, sizeof(scr_st));
	scr.ftype = ftype;
	if (scr.ftype == DSK_FILE)
	{
		ret = rt_f_open(&scr.dfile, (char *)path, RT_OPEN_EXISTING | RT_READ);
		if (ret != RT_OK)
			goto exit;
		scr.fsize = rt_fs_get_fsize((char *)path);
	}
	else
	{
		scr.mfile = path;
		scr.fsize = fsize;
	}
exit:
	return ret;
}

static void	scr_close(void)
{
	if (scr.ftype == DSK_FILE)
	{
		rt_f_close(&scr.dfile);
	}
	memset(&scr, 0, sizeof(scr_st));
	return;
}

static int scr_is_feof(void)
{
	return (scr.fpos >= scr.fsize ? 1 : 0);
}

// (1) read data from file & save into win[]
// (2) update fpos & widx & wlen
//
static int scr_win_update(void)
{
	unsigned int nread, len;
	int ret = RT_OK;

	if (scr_is_feof())
		return RT_E_FS_EOF;
	//
	len = ((scr.fsize - scr.fpos) > WIN_SZ) ? WIN_SZ : (scr.fsize - scr.fpos);
	if (scr.ftype == DSK_FILE)
	{
		ret = rt_f_read(&scr.dfile, scr.win, len, &nread);
		if (ret == RT_OK && nread != len)
		{
			//my_debug("[E] %s(): nread(%d) != len(%d)\n", __func__, nread, len);
			ret = RT_E_LENGTH_MISMATCH;
		}
		scr.widx = 0;
		scr.wlen = len;
		scr.fpos += len;
	}
	else
	{
		memcpy(scr.win, scr.mfile + scr.fpos, len);
		scr.widx = 0;
		scr.wlen = len;
		scr.fpos += len;
		ret = RT_OK;
	}
	return ret;
}

#define scr_win_is_empty()	(scr.wlen == 0)
#define scr_win_is_end()	(scr.widx >= (scr.wlen - 1))

// return:
//  >= 0: # of readout data bytes in buf[]
//   < 0: error
//
static int scr_get_line(char buf[], int buflen)
{
	int n;
	int ret = RT_OK;

	if (scr_win_is_empty() || scr_win_is_end())
	{
		if ((ret = scr_win_update()) != RT_OK)
			return ret;
	}
	//
	int flag = 0;
	unsigned int i;
	n = 0;
	for (i = 0; i < scr.fsize+32; i++)	// to avoid infinite loop.
	{
		if (n >= (buflen-1))
			return RT_E_OUT_OF_RANGE;
		buf[n++] = scr.win[scr.widx++];
		// check EOL
		if (buf[n-1] == ASCII_LF)
		{
			buf[n] = '\0';	// to let buf[] useless after EOL
			break;
		}
		//
		if (!flag && scr_win_is_end())
		{
			// must copy the last char before scr_win_update()
			buf[n++] = scr.win[scr.widx++];
			//
			ret = scr_win_update();
			if (ret == RT_E_FS_EOF)
			{
				// if reach EOF (the last win[]), then NOT treat it as error
				// the for-loop is still continue and needn't do scr_win_update().
				flag = 1;
			}
			else
			{
				if (ret != RT_OK)	// really error.
					return ret;
			}
			//
			if (buf[n-1] == ASCII_LF)
			{
				buf[n] = '\0';	// to let buf[] useless after EOL
				break;
			}
		}
	}
	if (i > scr.fsize)
		RT_BUG();
	//
	scr.line++;
	return n;
}

// brief: count the mem file size.
//        the first 0xFF in buf[] is regard as memfile's eof.
// note: the EOF (0xFF) is included (count in) the fsize.
//       ex: "abc"+0xFF => fsize = 4.
//
// return:
//  >=0 : the file size.
//  < 0 : error
//
static int shell_get_memfile_size(char *buf, int buflen)
{
	int n;

	for (n = 0; n < buflen; n++)
	{
		if (buf[n] == 0xFF)
			return (n+1);
	}
	return -1;
}


static int shell_try_print_msg_cmd(char *line)
{
	char *p = strchr(line, '@');

	if (p == NULL)
		return RT_E_NOT_FOUND;

	if (strlen(line) >= 3)
		rt_printf("%s", p+2);

	rt_printf("\n");
	return RT_OK;
}

static int shell_is_stop(int code)
{
	if (code == RT_E_SHELL_EXIT_OK || code == RT_E_SHELL_EXIT_FAIL)
		return 1;

	if (scr.stopmode == STOP_ERR)
	{
		if (code != RT_OK)
			return 1;
		return 0;
	}
	if (scr.stopmode == STOP_DEF)
	{
		return 0;
	}
	return 0;
}

static int shell_script_exec(unsigned char ftype, void *path, int fsize)
{
	int ret = RT_OK;
	char line[LINE_SZ];
	int len;
	BOOL old;
	unsigned int i;

	if ((ret = scr_open(ftype, path, fsize)) != RT_OK)
		return ret;
	// check script signature
	if ((len = scr_get_line(line, LINE_SZ)) < 0)
	{
		rt_printf("error! fail to get line of script signature\n");
		ret = len;
		goto close_exit;
	}
	if (strncmp(line, "#!riot", 6) != 0)
	{
		rt_printf("error! script signature not found!\n");
		ret = RT_E_INVALID_FORMAT;
		goto close_exit;
	}
	//
	old = shell_get_hist_en();
	shell_set_hist_en(0);
	for (i = 0; i < scr.fsize+32; i++)	// to avoid infinite loop
	{
		if ((len = scr_get_line(line, LINE_SZ)) < 0)
		{
			ret = len;
			if (ret == RT_E_FS_EOF)
				ret = RT_OK;
			break;
		}
		//rt_printf("%3d: (%3d) %s", scr.line, len, line);
		//
		str_remove_line_comment(line, '#');
		// replace EOL before exec cmd str.
		line[len-1] = '\0';
		if (shell_try_print_msg_cmd(line) == RT_OK)
			continue;
		//
		str_replace_char(line, '\t', ' ');	// replace TAB by SPACE
		if (str_is_blank_line(line))
			continue;
		if (scr.showline)
			rt_printf("> %d: %s", scr.line, line);
		//
		ret = shell_exec_cmd_str(line);
		if (shell_is_stop(ret))
		{
			rt_printf("\nshell script stopped, line %d, code %d\n", scr.line, ret);
			break;
		}
	}
	if (i > scr.fsize)
		RT_BUG();
	//
	shell_set_hist_en(old);

close_exit:
	scr_close();
	return ret;
}

void shell_script_set_stopmode(stopmode_e mode)
{
	scr.stopmode = mode;
}

void shell_script_set_showline(uint8_t is_show)
{
	scr.showline = (is_show > 0) ? 1 : 0;
}

int shell_script_exec_memfile(void *addr, int len)
{
	int fsize = shell_get_memfile_size((char *)addr, len);
	if (fsize < 0)
		return RT_E_INVALID_FORMAT;

	return shell_script_exec(MEM_FILE, addr, fsize);
}

int shell_script_exec_dskfile(char *path)
{
	if (!rt_fs_is_file(path))
	{
		return RT_E_NOT_EXIST;
	}

	return shell_script_exec(DSK_FILE, path, 0);
}
#endif
