/*
 * isp_debug.h
 *
 *  Created on: 2021/05/10
 *      Author: martinhuang
 */

#ifndef _ISP_DEBUG_H_
#define _ISP_DEBUG_H_

//#define __TTFF_ISP__

//#define __OSD_LOG__
//#define __DEBUG_STATIS__
//#define __DEBUG_NOTIFY__
//#define _DEBUG_I2C_
#define __3DNR__
//#define __SINGLE__
//#define __SEMA_LOG__
//#define _MIPI_DEBUG_
//#define _AWB_DEBUG_
//#define __LOG_RTS_MEM__
//#define _IQ_LOG_
//#define _STREAM_INFO_
//#define _CLK_LOG_
//#define _ISPBUF_LOG_
//#define _FPS_LOG_
//#define _PWR_SNRPLL_LOG_
//#define _DEBUG_MEM_USEAGE_

//#define _OSD_DEBUG_LOG
//#ifdef _OSD_LOG_INT_

#if !defined(__TTFF_ISP__)
#define _STREAM_FMT_
#endif

//#define _VHDR_
//ISP_CLK_DEFINE
//MIPI_CLK_DEFINE

//#define _WORKAROUND_FRAME_CHANGE_
#define CALC_CLK_AUTO
//#define _DEBUG_CLK_

#define __OSD_EN__
#define __MD_EN__



#endif /* _ISP_DEBUG_H_ */
