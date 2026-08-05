#include <stdio.h>
#include <stdlib.h>
#if 0
#include "rt_shell.h"
#include "rt_log.h"
#include "rt_task.h"
#include "rt_util.h"

#include "rt_console.h"
#include "rlx_time.h"

// shell internal private data
typedef struct
{
	char     cmd_str_buf[CFG_SHELL_MAX_INPUT];

	// history ring buffer
	char     hist_buf[CFG_SHELL_HIST_CAPACITY][CFG_SHELL_MAX_INPUT];
	uint32_t hist_begin, hist_size;
	int      hist_ptr;
} shell_priv_st;

static shell_st *s_shell = NULL;
static shell_priv_st s_priv;

__STATIC_INLINE
BOOL _hist_is_empty()
{
	return (s_priv.hist_size == 0);
}

static void _hist_clear(void)
{
	memset(s_priv.hist_buf, 0, CFG_SHELL_HIST_CAPACITY*CFG_SHELL_MAX_INPUT*sizeof(char));
	s_priv.hist_begin = 0;
	s_priv.hist_size = 0;
}

// return the hist_buf array index, -1 means error.
__STATIC_INLINE
int _hist_idx_to_bufidx(uint32_t hist_idx)
{
	int i, ret;

	if (s_priv.hist_size == 0)
		return -1;
	if (hist_idx >= s_priv.hist_size)
		return -1;
	//
	ret = s_priv.hist_begin;
	for (i = 0; i < (int)hist_idx; i++)
	{
		ret++;
		if (ret >= CFG_SHELL_HIST_CAPACITY)
			ret = 0;
	}
	return ret;
}

// brief: get history string by 'hist_idx'.
static BOOL _hist_get_idx_str(int hist_idx, char str[CFG_SHELL_MAX_INPUT])
{
	int idx;

	if ((idx = _hist_idx_to_bufidx(hist_idx)) < 0)
		return 0;

	memset(str, 0, CFG_SHELL_MAX_INPUT*sizeof(char));
	strcpy(str, s_priv.hist_buf[idx]);
	return 1;
}

__STATIC_INLINE
void _hist_ptr_reset(void)
{
	s_priv.hist_ptr = -1;
}

// return: the array index after moving.
__STATIC_INLINE
int _hist_ptr_move_last(void)
{
	if (_hist_is_empty())
		return -1;

	s_priv.hist_ptr = s_priv.hist_size - 1;
	return s_priv.hist_ptr;
}

// note: if 'hist_ptr' = -1, move it to last
//
// return: the array index after moving.
__STATIC_INLINE
int _hist_ptr_move_prev(void)
{
	if (s_priv.hist_ptr < 0)
		_hist_ptr_move_last();
	else if (s_priv.hist_ptr == 0)
		s_priv.hist_ptr = 0;
	else
		s_priv.hist_ptr--;

	return s_priv.hist_ptr;
}

// return: the array index after moving.
__STATIC_INLINE
int _hist_ptr_move_next(void)
{
	if ((s_priv.hist_ptr >= 0) && (s_priv.hist_ptr < (int)s_priv.hist_size))
		s_priv.hist_ptr++;

	return s_priv.hist_ptr;
}

// brief: ask for a new slot in history ring buffer.
//        it the buffer already full, the oldest slot will dropped.
// note: always success.
static void _hist_ask_new(void)
{
	s_priv.hist_size++;
	if (s_priv.hist_size > CFG_SHELL_HIST_CAPACITY)
	{
		// if ring buf is full, drop the oldest slot.
		s_priv.hist_size--;
		s_priv.hist_begin++;
		if (s_priv.hist_begin >= CFG_SHELL_HIST_CAPACITY)
			s_priv.hist_begin = 0;
	}
	return;
}

// add a new string to history ring buffer.
static BOOL _hist_add(char *str)
{
	int buf_idx;

	_hist_ask_new();
	buf_idx = _hist_idx_to_bufidx(s_priv.hist_size - 1);
	assert(buf_idx >= 0);
	//
	strcpy(s_priv.hist_buf[buf_idx], str);

	return TRUE;
}

void _hist_show(void)
{
	int i;
	char str[CFG_SHELL_MAX_INPUT];

	rt_printf("\ncmd history (size = %d):\n", (int)s_priv.hist_size);
	if (s_priv.hist_size > 0)
	{
		for (i = 0; i < (int)s_priv.hist_size; i++)
		{
			if (!_hist_get_idx_str(i, str))
			{
				//my_debug("%s(): _hist_get_idx_str() fail!, i = %d\n", __func__, i);
				break;
			}
			rt_printf("[%d] %s\n", i, str);
		}
	}
	rt_printf("\n");
}

// note: assume that the input param 'cfg.cmd_list_cnt' = 0.
// return:
//  RT_E_SHELL_CMD_OVERFLOW
//  RT_E_SHELL_STDIO_NOT_AVAIL
int shell_init(shell_st *obj)
{
	int n;

	assert(obj);

	if (!console_is_inited())
		return RT_E_SHELL_STDIO_NOT_AVAIL;

	n = shell_cmd_list_cnt(obj->cmd_list);
	if (n >= CFG_SHELL_MAX_CMDS)
	{
		//my_debug("%s(): cmd list overflow! n= %d\n", __func__, n);
		return RT_E_SHELL_CMD_OVERFLOW;
	}

	s_shell = obj;
	s_shell->cmd_list_cnt = n;
	memset(&s_priv, 0, sizeof(shell_priv_st));
	_hist_clear();
	return RT_OK;
}

void shell_deinit(void)
{
	s_shell = NULL;
	memset(&s_priv, 0, sizeof(shell_priv_st));
	_hist_clear();
	return;
}

void shell_show_prompt(void)
{
	int i;

	for (i = 0; i < (int)strlen(s_shell->prompt_str); i++)
		console_putc(s_shell->prompt_str[i]);
}

void shell_clr_hist(void)
{
	_hist_clear();
}

BOOL shell_get_hist(uint32_t hist_idx, char str[CFG_SHELL_MAX_INPUT])
{
	return _hist_get_idx_str(hist_idx, str);
}

void shell_del_last_hist(void)
{
	if (_hist_is_empty())
		return;

	s_priv.hist_size--;
	if (s_priv.hist_ptr >= (int)s_priv.hist_size)
		s_priv.hist_ptr--;
}

void shell_set_hist_en(int hist_en)
{
	s_shell->hist_en = hist_en;
}

void shell_inc_hist_no_add(void)
{
	s_shell->hist_no_add++;
}

void shell_dec_hist_no_add(void)
{
	if (s_shell->hist_no_add > 0)
		s_shell->hist_no_add--;
}

BOOL shell_get_hist_en(void)
{
	return s_shell->hist_en;
}

void shell_show_hist(void)
{
	_hist_show();
}

void shell_show_help(void)
{
	int i;
	shell_cmd_st *cmd_ptr;

	cmd_ptr = s_shell->cmd_list;
	for (i = 0; i < s_shell->cmd_list_cnt; i++)
	{
		rt_printf("%-12s: %s\n", cmd_ptr->name_str, cmd_ptr->help_str);
		cmd_ptr++;
	}
	rt_printf("\n");
}

void shell_dump_argc_argv(int argc, char *argv[])
{
	int i;

	rt_printf("argc = %d\n", argc);
	for (i = 0; i < argc; i++)
	{
		rt_printf("[%d] (%2d) %s\n", i, strlen(argv[i]), argv[i]);
	}
	rt_printf("\n");
}

int shell_cmd_list_cnt(shell_cmd_st *cmd_list)
{
	shell_cmd_st *cmd_ptr;
	int i, n;

	cmd_ptr = cmd_list;
	n = 0;
	for (i = 0; i < CFG_SHELL_MAX_CMDS; i++)
	{
		//my_debug("[%d] %08X: %s, %s\n", i, cmd_ptr->handler, cmd_ptr->name_str, cmd_ptr->help_str);
		if (cmd_ptr->handler == 0)
			break;
		n++;
		cmd_ptr++;
	}
	return n;
}

void shell_cmd_list_show(shell_cmd_st *cmd_list)
{
	shell_cmd_st *cmd_ptr;
	int i, cnt;

	cnt = shell_cmd_list_cnt(cmd_list);
	rt_printf("cmd_list cnt= %d\n", cnt);
	cmd_ptr = cmd_list;
	for (i = 0; i < cnt; i++)
	{
		rt_printf("[%d] 0x%08X: %-12s, %s\n", i, (unsigned int)cmd_ptr->handler, cmd_ptr->name_str, cmd_ptr->help_str);
		cmd_ptr++;
	}
}

// brief: append src to dst
// return:
//  RT_E_SHELL_CMD_OVERFLOW: after append, if the command list length >= CFG_SHELL_MAX_CMDS.
//  RT_E_SHELL_CMD_CONFLICT: some entry of dst & src have same cmd name_str.
//
int shell_cmd_list_append(shell_cmd_st *dst, shell_cmd_st *src)
{
	int dst_len, src_len;
	int i, j;

	dst_len = shell_cmd_list_cnt(dst);
	src_len = shell_cmd_list_cnt(src);
	if (dst_len + src_len >= CFG_SHELL_MAX_CMDS)
	{
		rt_debug("shell cmd overflow!\n");
		return RT_E_SHELL_CMD_OVERFLOW;
	}

	for (i = 0; i < src_len; i++)
	{
		for (j = 0; j < dst_len; j++)
		{
			if (strcmp(src[i].name_str, dst[j].name_str) == 0)
			{
				rt_debug("shell cmd conflict!! dst idx= %d, src idx= %d, name= %s\n", j, i, src[i].name_str);
				return RT_E_SHELL_CMD_CONFLICT;
			}
		}
	}

	for (i = 0; i < src_len; i++)
	{
		memcpy(&dst[i+dst_len], &src[i], sizeof(shell_cmd_st));
	}
	// to make sure the last entry to be zero
	memset(&dst[dst_len+src_len], 0, sizeof(shell_cmd_st));
	return RT_OK;
}

// brief: get user's input from console (usually, it is uart)
// return:
//  RT_E_SHELL_CMD_OVERFLOW: exceed CFG_SHELL_MAX_INPUT
//  RT_E_SHELL_CMD_EMPTY
static int _shell_get_cmd_str(char cmd_str[CFG_SHELL_MAX_INPUT])
{
	int ret = RT_OK;
	unsigned int key;
	int n = 0;

	if (s_shell->hist_en)
		_hist_ptr_reset();

	memset(cmd_str, 0, CFG_SHELL_MAX_INPUT*sizeof(char));
	while (1)
	{
		key = console_get_vkey();
		if (key == VKEY_UNDEFINED)
		{
			//my_debug("%s(): error! undefined vkey (0x%08X)\n", __func__, key);
			continue;
		}
		if (key == SHELL_ASCII_CR)
		{
			console_putc((char)key);
			_hist_ptr_reset();
			break;
		}
		if (key == SHELL_ASCII_BS || key == SHELL_ASCII_DEL)
		{
			if (n > 0)
			{
				console_unputc();
				cmd_str[n-1] = 0;
				n--;
			}
			continue;
		}
		if (32 <= key && key <= 126)	// viewable char, from ' ' to '~'
		{
			cmd_str[n++] = (char)key;
			console_putc((char)key);
			if (n >= CFG_SHELL_MAX_INPUT)
			{
				rt_printf("error! shell input len > max limit(%d)\n", CFG_SHELL_MAX_INPUT);
				ret = RT_E_SHELL_CMD_OVERFLOW;
				break;
			}
			continue;
		}
		if (key == VKEY_UP || key == VKEY_DOWN)
		{
			if (!s_shell->hist_en)
				continue;
			if (_hist_is_empty())
				continue;
			//
			console_unputs(cmd_str);
			//
			if (key == VKEY_UP)
			{
				_hist_ptr_move_prev();
			}
			else
			{
				_hist_ptr_move_next();
			}
			//
			memset(cmd_str, 0, CFG_SHELL_MAX_INPUT*sizeof(char));
			_hist_get_idx_str(s_priv.hist_ptr, cmd_str);
			// note: don't use rt_printf here
			console_puts(cmd_str);
			n = strlen(cmd_str);
		}
	}	// end of while

	if (n == 0)
	{
		rt_printf("\n");
		ret = RT_E_SHELL_CMD_EMPTY;
	}

	return ret;
}

static int _parse_cmd_str(char *cmd_str, int *argc, char *argv[])
{
	int i, len, q, k, p0, p1;
	int begin, end;

	if (!cmd_str)
		return RT_E_SHELL_CMD_EMPTY;
	if ((len = strlen(cmd_str)) <= 0)
		return RT_E_SHELL_CMD_EMPTY;
	//
	*argc = 0;
	// discard 'all space string' case
	q = 0;
	for (i = 0; i < len; i++)
	{
		if (cmd_str[i] != ' ')
		{
			q = 1;
			break;
		}
	}
	if (q == 0)
	{
		return RT_E_SHELL_CMD_EMPTY;
	}
	// trim left
	for (begin = 0; begin < len; begin++)
	{
		if (cmd_str[begin] != ' ')
			break;
	}
	// trim right
	for (end = len-1; end >= 0; end--)
	{
		if (cmd_str[end] != ' ')
		{
			cmd_str[end+1] = '\0';
			break;
		}
	}
	//
	k = 0;		// strlen of non-quoted argv
	q = 0;		// 0: non-quoted mode ; 1: quoted mode
	for (i = begin; i <= end; i++)
	{
		if (q == 0)
		{
			if (cmd_str[i] == ' ')
			{
				if (k > 0)		// ' ' after argv, add newline.
				{
					cmd_str[i] = '\0';
					k = 0;
					(*argc)++;
				}
				//else,			// ' ' before argv, noop.
			}
			else if (cmd_str[i] == '"')		// meet 1st " char for quoted argv
			{
				p0 = i;
				q = 1;
				if (i == end)
				{
					rt_printf("\n{shell} no matching \" char\n");
					return RT_E_SHELL_PARSE;
				}
			}
			else
			{
				if (k == 0)		// meet 1st char of argv.
					argv[*argc] = &(cmd_str[i]);
				k++;
			}
		}
		else
		{
			if (cmd_str[i] == '"')	// meet 2nd " char for quoted argv
			{
				p1 = i;
				if (p0 > 0)
				{
					if (cmd_str[p0-1] != ' ' && cmd_str[p0-1] != '\0')
					{
						rt_printf("\n{shell} invalid prev char of quoted argv\n");
						return RT_E_SHELL_PARSE;
					}
				}
				if (p1 < end)
				{
					if (cmd_str[p1+1] != ' ' && cmd_str[p1+1] != '\0')
					{
						rt_printf("\n{shell} invalid next char of quoted argv\n");
						return RT_E_SHELL_PARSE;
					}
				}
				if (p1-p0 < 2)
				{
					rt_printf("\n{shell} quoted argv is empty string\n");
					return RT_E_SHELL_PARSE;
				}
				// now, get full quoted argv string
				cmd_str[p0]	= ' ';
				cmd_str[p1]	= '\0';
				argv[*argc]	= &(cmd_str[p0+1]);
				if (p1 < end)
					(*argc)++;
				q = 0;
				k = 0;
			}
			else
			{
				if (i == end)
				{
					rt_printf("\n{shell} no matching \" char\n");
					return RT_E_SHELL_PARSE;
				}
			}
		}
		//
		if ((*argc) > CFG_SHELL_MAX_CMD_ARGS)
		{
			rt_printf("\n{shell} argc > max limit (%d).\n", CFG_SHELL_MAX_CMD_ARGS);
			return RT_E_SHELL_PARSE;
		}
		if (k >= CFG_SHELL_MAX_CMD_ARG_LEN)
		{
			rt_printf("\n{shell} cmd arg strlen > max limit (%d).\n", CFG_SHELL_MAX_CMD_ARG_LEN);
			return RT_E_SHELL_PARSE;
		}
	}
	if (q == 0)
		(*argc)++;

	return RT_OK;
}

static int _exec_cmd(int argc, char *argv[])
{
	int i, ret;
	shell_cmd_st *cmd_ptr;

	ret = RT_E_SHELL_CMD_NOT_FOUND;
	cmd_ptr = s_shell->cmd_list;
	for (i = 0; i < s_shell->cmd_list_cnt; i++)
	{
		if (strcmp(cmd_ptr->name_str, argv[0]) == 0)
		{
			// [WORKAROUND] to avoid chaos between rt_printf & serial getc/putc after cmd_str.
			rt_printf("\n");

			ret = cmd_ptr->handler(argc, argv);
			break;
		}
		cmd_ptr++;
	}
	return ret;
}

int shell_exec_cmd_str(char *cmd_str)
{
	int argc, ret;
	char *argv[CFG_SHELL_MAX_CMD_ARGS] = {0};
	char hist_str[CFG_SHELL_MAX_INPUT] = {0};

	if (s_shell->hist_en)
		strcpy(hist_str, cmd_str);
	//
	ret = _parse_cmd_str(cmd_str, &argc, argv);
	if (ret != RT_OK)
		return ret;

	ret = _exec_cmd(argc, argv);
	// caution!:
	//  the below code must be after _exec_cmd().
	//  to let the outer shell cmd handler has a chance to increment 'hist_no_add'.
	//
	if (s_shell->hist_en)
	{
		if (s_shell->hist_no_add == 0)
			_hist_add(hist_str);
		else
			shell_dec_hist_no_add();
	}

	return ret;
}

// return:
//  RT_E_SHELL_EXIT_OK
//  RT_E_SHELL_EXIT_FAIL
int shell_run(void)
{
	int ret = RT_OK;

	task_st *task = task_from_name(CFG_TASK_SHELL_NAME);
	RT_BUG_ON(!task);
	//
	while (1)
	{
		if (task->delay)
		{
			vTaskDelay(task->delay);
		}

		shell_show_prompt();
		ret = _shell_get_cmd_str(s_priv.cmd_str_buf);
		if (ret != RT_OK)
		{
			taskYIELD();
			continue;
		}
		ret = shell_exec_cmd_str(s_priv.cmd_str_buf);
		if (ret == RT_E_SHELL_CMD_NOT_FOUND)
		{
			rt_printf("\ncmd not found!!\n\n");
		}
		if (ret == RT_E_SHELL_EXIT_OK || ret == RT_E_SHELL_EXIT_FAIL)
		{
			break;
		}
	}
	return ret;
}
#endif
