#ifndef RT_SHELL_H
#define RT_SHELL_H
#include "rt_types.h"
#include "rt_code.h"
#include "rt_config.h"
#include "my_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int		(*shell_cmd_hdr_t)(int argc, char *argv[]);

/**
  \brief  Defines the ASCII code for the shell command input control keys.
*/
enum shell_ctrl_key_ascii_e {
	SHELL_ASCII_NUL             = 0x00,     ///< Null character.
	SHELL_ASCII_BEL             = 0x07,     ///< Bell.
	SHELL_ASCII_BS              = 0x08,     ///< Backspace.
	SHELL_ASCII_HT              = 0x09,     ///< Horizontal Tab.
	SHELL_ASCII_LF              = 0x0A,     ///< Line Feed.
	SHELL_ASCII_CR              = 0x0D,     ///< Carriage Return.
	SHELL_ASCII_ESC             = 0x1B,     ///< Escape.
	SHELL_ASCII_US              = 0x1F,     ///< Unit Separator.
	SHELL_ASCII_SP              = 0x20,     ///< Space.
	SHELL_ASCII_DEL             = 0x7F      ///< Delete.
};

// shell error codes
enum  {
	//
	RT_E_SHELL_EXIT_OK          = (RT_CODE_BASE_SHELL -  1),    // exit shell normally
	RT_E_SHELL_EXIT_FAIL        = (RT_CODE_BASE_SHELL -  2),    // exit shell wrongly
	RT_E_SHELL_CMD_CONFLICT     = (RT_CODE_BASE_SHELL -  3),    // shell command name conflict
	RT_E_SHELL_CMD_OVERFLOW     = (RT_CODE_BASE_SHELL -  4),    // shell command overflow
	RT_E_SHELL_CMD_NOT_FOUND    = (RT_CODE_BASE_SHELL -  5),    // shell command not found
	RT_E_SHELL_CMD_EMPTY        = (RT_CODE_BASE_SHELL -  6),    // user input an empty command
	RT_E_SHELL_CMD_WRONG_ARG    = (RT_CODE_BASE_SHELL -  7),    // wrong arg
	RT_E_SHELL_CMD_NOT_EN       = (RT_CODE_BASE_SHELL -  8),    // some feature is not enabled.
	RT_E_SHELL_STDIO_NOT_AVAIL  = (RT_CODE_BASE_SHELL -  9),    // the stdio_port (console) not available. (maybe not inited).

	// note: the following is copied from 'shell.h' in sdk-ameba-v5.0a
	RT_E_SHELL_ARGCOUNT         = (RT_CODE_BASE_SHELL - 20),     ///< There are missing arguments for the command
	RT_E_SHELL_OUTOFRANGE       = (RT_CODE_BASE_SHELL - 21),     ///< The program received an argument that is out of range
	RT_E_SHELL_VALUE            = (RT_CODE_BASE_SHELL - 22),     ///< The program received an argument with a value different than expected
	RT_E_SHELL_ACTION           = (RT_CODE_BASE_SHELL - 23),     ///< Invalid action requested for the current state
	RT_E_SHELL_PARSE            = (RT_CODE_BASE_SHELL - 24),     ///< Cannot parse the user input
	RT_E_SHELL_STORAGE          = (RT_CODE_BASE_SHELL - 25),     ///< Cannot access storage device or memory device
	RT_E_SHELL_IO               = (RT_CODE_BASE_SHELL - 26),     ///< IO device error caused program interruption
};

typedef struct
{
	char	*name_str;
	shell_cmd_hdr_t		handler;
	char	*help_str;
} shell_cmd_st;

typedef struct
{
	shell_cmd_st	cmd_list[CFG_SHELL_MAX_CMDS];
	int		cmd_list_cnt;
	char	prompt_str[8];	// command prompt string
	BOOL	hist_en;
	uint8_t	hist_no_add;	// a counter, if this value > 0, then the shell "decrement by one and won't do hist_add()".
} shell_st;

// return:
//  RT_E_SHELL_CMD_OVERFLOW
//  RT_E_SHELL_STDIO_NOT_AVAIL
int     shell_init(shell_st *obj);
void    shell_deinit(void);
// return:
//  RT_E_SHELL_EXIT_OK
//  RT_E_SHELL_EXIT_FAIL
int     shell_run(void);

int     shell_exec_cmd_str(char *cmd_str);
// brief: append src to dst
// return:
//  RT_E_SHELL_CMD_OVERFLOW: after append, if the command list length >= CFG_SHELL_MAX_CMDS.
//  RT_E_SHELL_CMD_CONFLICT: some entry of dst & src have same cmd name_str.
//
int     shell_cmd_list_append(shell_cmd_st *dst, shell_cmd_st *src);
int     shell_cmd_list_cnt(shell_cmd_st *cmd_list);
void    shell_cmd_list_show(shell_cmd_st *cmd_list);

BOOL    shell_get_hist(uint32_t hist_idx, char str[CFG_SHELL_MAX_INPUT]);
void    shell_clr_hist(void);
void    shell_del_last_hist(void);
void    shell_set_hist_en(int hist_en);
void    shell_inc_hist_no_add(void);
void    shell_dec_hist_no_add(void);
BOOL    shell_get_hist_en(void);
void    shell_show_hist(void);

void    shell_dump_argc_argv(int argc, char *argv[]);
void    shell_show_prompt(void);
void    shell_show_help(void);

typedef enum {
	STOP_DEF = 0,    // default behavior
	STOP_ERR = 1,    // only RT_OK can continue to run, else stop.
} stopmode_e;
void    shell_script_set_stopmode(stopmode_e mode);
void    shell_script_set_showline(uint8_t is_show);
int     shell_script_exec_dskfile(char *path);
int     shell_script_exec_memfile(void *addr, int len);

#ifdef __cplusplus
}
#endif

#endif  // RT_SHELL_H
