#ifndef __RT_CONFIG_SHELL_H
#define __RT_CONFIG_SHELL_H

// ----------------------------------------------------------------------------
//  main (console uart, shell autorun)
// ----------------------------------------------------------------------------
// value: { 9600, 19200, 38400, 57600, 115200 }
#define CFG_CONSOLE_UART_BAUDRATE		57600
// value: 5, 6, 7, 8
#define CFG_CONSOLE_UART_DATABITS		8
// value: 0(ParityNone), 1(ParityOdd), 2(ParityEven), 3(ParityForced1), 4(ParityForced0)
#define CFG_CONSOLE_UART_PARITY			0
// value: 1, 2
#define CFG_CONSOLE_UART_STOP_BITS		1

// ----------------------------------------------------------------------------
//  rt_shell
// ----------------------------------------------------------------------------
// note : hconf
// note : max strlen = 8.
#define CFG_SHELL_PROMPT_STR			"rtk> "
// brief: The maximum characters that the command input buffer can accept.
#define CFG_SHELL_MAX_INPUT				128
// brief: The maximum number of commands that can be registered.
#define CFG_SHELL_MAX_CMDS				96
// brief: Configures the maximum number of arguments per command tha can be accepted.
#define CFG_SHELL_MAX_CMD_ARGS			24
// brief: Configures the maximum buffer size of each argument string.
#define CFG_SHELL_MAX_CMD_ARG_LEN		64
// brief: Configures the command history is enabled or disabled.
// note : hconf
// value: TRUE, FALSE
#define CFG_SHELL_HIST_EN				TRUE
// brief: Configures the command history capacity (number of entries)
#define CFG_SHELL_HIST_CAPACITY			8

// ----------------------------------------------------------------------------
//  shell cmd support
//
// brief: shell support 'xxx' cmd or not.
// value: 0, 1
// ----------------------------------------------------------------------------
// brief: 'sf' & 'mtd' cmd
#define CFG_SHELL_CMD_SF_MTD			1
// brief: 'mmc' + fs('df'+'cd'+'pwd'+'mkdir'+'chmod'+'ls'+'rm'+'cat'+'cmp'+'cp'+'mv'+'fr'+'fw') cmd.
// note : mmc & fs are bundle together.
#define CFG_SHELL_CMD_MMC_FS			0
// brief: net ('net'+'ping'+'tftp'+'iperf'+'rtsp') cmd.
#define CFG_SHELL_CMD_NET				1
// brief: 'isp' cmd.
#define CFG_SHELL_CMD_ISP				1
// brief: 'mem' cmd
#define CFG_SHELL_CMD_MEM				1
// brief: 'mem e' cmd
#define CFG_SHELL_CMD_MEM_EDIT_MODE		0
// brief: 'crypto' cmd
#define CFG_SHELL_CMD_CRYPTO			0
// brief: 'i2c' cmd.
#define CFG_SHELL_CMD_I2C				1
// brief: 'gpio' cmd.
#define CFG_SHELL_CMD_GPIO				1
// brief: 'saradc' cmd.
#define CFG_SHELL_CMD_SARADC			0
// brief: 'usb' cmd
#define CFG_SHELL_CMD_USB				1
// brief: 'wlan' cmd
#define CFG_SHELL_CMD_WLAN				1
// brief: 'jpg' cmd.
// caution: this cmd will make mmf unusable.
#define CFG_SHELL_CMD_JPG				0
// brief: 'audio' cmd.
#define CFG_SHELL_CMD_AUDIO				0
// brief: 'hconf' cmd
#define CFG_SHELL_CMD_HCONF				1
// brief: 'tmr' cmd
#define CFG_SHELL_CMD_TMR				0
// brief: 'img' cmd
#define CFG_SHELL_CMD_IMG				1
// brief: 'lds' (dump ld symbols) cmd
#define CFG_SHELL_CMD_LDS				0
// brief: 'wpt' (watchpoint) cmd
#define CFG_SHELL_CMD_WPT				1
// brief: 't' (test) cmd
#define CFG_SHELL_CMD_TEST				0
// brief: 'd' (mmf debug) cmd.
#define CFG_SHELL_CMD_MMF_DBG			0
// brief: 'z' (mmf snapshot) cmd.
#define CFG_SHELL_CMD_MMF_SNAPSHOT		0
// brief: 'osd' cmd.
#define CFG_SHELL_CMD_OSD				1
// brief: 'video' cmd.
// caution: this cmd will make mmf unusable.
#define CFG_SHELL_CMD_VIDEO				0
// brief: 'tlog' cmd
#define CFG_SHELL_CMD_TEST_LOG			1
// brief: 'tsf' cmd
#define CFG_SHELL_CMD_TEST_SF			1
// brief: 'tmalloc' cmd
#define CFG_SHELL_CMD_TEST_MALLOC		1
// brief: 'mfw' cmd
// note : CFG_SHELL_CMD_MMC_FS must also be 1 to take effect.
#define CFG_SHELL_CMD_TEST_MFW			1
// brief: 'fwperf' cmd
// note : CFG_SHELL_CMD_MMC_FS must also be 1 to take effect.
#define CFG_SHELL_CMD_TEST_FW			0
// brief: 'dir' cmd
// note : CFG_SHELL_CMD_MMC_FS must also be 1 to take effect.
#define CFG_SHELL_CMD_TEST_DIR			1

#endif	// __RT_CONFIG_SHELL_H

