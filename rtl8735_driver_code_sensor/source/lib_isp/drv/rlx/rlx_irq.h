#ifndef __RLX_IRQ_H__
#define __RLX_IRQ_H__
//#include <core_rlx.h>
//#include <system_sheipa.h>
//#include "sheipa.h"

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "hal_irq.h"
#else
#include "rtl8735b_voe.h"
#endif


// ----------------------------------------------------------------------------
//    IRQn Assignment
// ----------------------------------------------------------------------------

#if 0
#define OTHERS_IRQn       CPU_IRQ4
#define OTHERS_ID_SPI     0
#define OTHERS_ID_I2C     1
#define OTHERS_ID_GPIO    2
#define OTHERS_ID_RXI     3
#define OTHERS_ID_XB2     4
#endif

#define OTHERS_SH_NUMBER  5


#define VIDEOIN_IRQn      ISP_IRQn
#define VIDEOIN_ID_MFD     0	//include ISP/MD(w/ IRQ), ZOOM/VERIFY(no IRQ)
#define VIDEOIN_ID_SOC     1
#define VIDEOIN_ID_OSD     2
#define VIDEOIN_SH_NUMBER  3

#if 0
#define AES_IRQn          VEC_IRQ8
#define SDIO_IRQn         VEC_IRQ9
#define ETH_IRQn          CPU_IRQ7
#define USBD_IRQn         CPU_IRQ6
#define H264_IRQn         VEC_IRQ11
#define AUDIO_IRQn        VEC_IRQ13
#define TIMER_IRQn        VEC_IRQ14
#endif
// ----------------------------------------------------------------------------

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9

#define RLX_ClearPendingIRQ 	hal_irq_clear_pending
#define RLX_SetVector			hal_irq_set_vector
#define RLX_EnableIRQ			hal_irq_enable
#define RLX_SetPriority			hal_irq_set_priority

#else

#define RLX_ClearPendingIRQ 	NVIC_ClearPendingIRQ
#define RLX_SetVector			NVIC_SetVector
#define RLX_EnableIRQ			NVIC_EnableIRQ
#define RLX_SetPriority			NVIC_SetPriority

#endif



#if 0

#define RLX_SetPriorityGrouping     NVIC_SetPriorityGrouping
#define RLX_GetPriorityGrouping     NVIC_GetPriorityGrouping
#define RLX_EnableIRQ               NVIC_EnableIRQ
#define RLX_GetEnableIRQ            NVIC_GetEnableIRQ
#define RLX_DisableIRQ              NVIC_DisableIRQ
#define RLX_GetPendingIRQ           NVIC_GetPendingIRQ
#define RLX_SetPendingIRQ           NVIC_SetPendingIRQ
#define RLX_ClearPendingIRQ         NVIC_ClearPendingIRQ
#define RLX_GetActive               NVIC_GetActive
#define RLX_SetPriority             NVIC_SetPriority
#define RLX_GetPriority             NVIC_GetPriority
#define RLX_SetVector               NVIC_SetVector
#define RLX_GetVector               NVIC_GetVector

void RLX_EnableOthersIRQ(int id);
void RLX_DisableOthersIRQ(int id);
void RLX_SetOthersIrqVector(int id, unsigned int func);
#endif

void RLX_EnableVideoInIRQ(int id);
void RLX_DisableVideoInIRQ(int id);
void RLX_SetVideoInIrqVector(int id, unsigned int func);
void RLX_InitSharedIrq(void);



#endif	// __RLX_IRQ_H__
