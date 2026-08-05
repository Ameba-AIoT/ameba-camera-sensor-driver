#ifndef __RT_BOOT_H__
#define __RT_BOOT_H__
#include "rt_types.h"
#include "rt_shell.h"

// note: the main() start time, in cpu ticks.
extern u64 g_start_time;

void app_about(void);
int env_load_default(void);

// brief: let vendor add her/his own shell cmd.
// note:
//  - any two shell cmd names must be different.
//  - the total numbers of shell cmds must < CFG_SHELL_MAX_CMDS
//
int shell_append_vendor_cmd_list(shell_st *shell);

// brief:
//  the vendor can put his HW driver/SW settings load/init codes inside this function
//  which is called after system bootup and before the shell cmd run.
//
// boot flow:
//  Reset (TARGET)
//      -> main (LIBC)
//          -> system bootup
//             (mpool, sf, & console_uart ready)
//          -> shell_task created & shell cmd list is build
//          -> vendor_boot_flow()
//          -> try to exec shell init script
//          -> shell cmd run
//
// return: RT_OK or RT_E_SHELL_EXIT_OK
//    if you want the following 'shell_cmd' run, please return RT_OK.
//    else, return RT_E_SHELL_EXIT_OK.
//
int vendor_boot_flow(void);

#endif	// __RT_BOOT_H__
