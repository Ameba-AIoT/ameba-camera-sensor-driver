
#include "cmsis_os2.h"
#include "rt_types.h"
#include "rt_task.h"
#include "rlx_irq.h"
#include "rlx_inc.h"
#include "rlx_reg.h"
#include "rlx_sys.h"
#include "isp_log.h"

typedef void (*irq_handler)(void);
struct share_irq_s {
	int enable;
	irq_handler handler;
};

//static struct share_irq_s irq4_handler[OTHERS_SH_NUMBER];
static struct share_irq_s irqC_handler[VIDEOIN_SH_NUMBER];

volatile int isp_isr_alive = 0;

volatile int yuv_isr_ng = 0, osd_isr_ng = 0, isp_isr_ng = 0;

#if 0
static void	rlx_sh_irq4_handler(void)
{
	int i;

	for (i=0; i<OTHERS_SH_NUMBER; i++) {
		if (irq4_handler[i].enable && irq4_handler[i].handler) {
			irq4_handler[i].handler();
		}
	}
	return;
}

void RLX_EnableOthersIRQ(int id)
{
	if (id>OTHERS_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irq4_handler[id].enable = 1;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

void RLX_DisableOthersIRQ(int id)
{
	if (id>OTHERS_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irq4_handler[id].enable = 0;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

void RLX_SetOthersIrqVector(int id, u32 func)
{
	if (id>OTHERS_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irq4_handler[id].handler = (irq_handler)func;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}
#endif
static void	rlx_sh_irqC_handler(void)
{
	int i;
	uint32_t ispctrl_enable_status, yuv_enable_status,  rgb_enable_status,  md_enable_status,  osd_enable_status;

#if CONFIG_VERIFY_SYSVIEW
	traceISR_ENTER();
#endif

	isp_isr_alive = 1;

	for (i=0; i<VIDEOIN_SH_NUMBER; i++) {
		if (irqC_handler[i].enable && irqC_handler[i].handler) {

			irqC_handler[i].handler();

		}
	}
	__DSB();
	__ISB();

	if( !IS_AFTER_CUT_C(hal_sys_get_rom_ver()) ) {


#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM // Run on KM
	u32 reg_value32;
	/*Clean ISP status bit*/
	reg_value32 = HAL_READ32( VOE_REG_BASE, 0x110);
	reg_value32 = (reg_value32 & (~BIT4)) | (BIT4);
	HAL_WRITE32(VOE_REG_BASE, 0x110, (u32) reg_value32);
#endif

#if 1 // workaround for B-cut, reset isp interrupt for edge-sensitive voe isr handling


	ispctrl_enable_status = HAL_READ32(0x40300000, 0x10);
	yuv_enable_status = HAL_READ32(0x403F0000, 0x250);
	rgb_enable_status = HAL_READ32(0x403F0000, 0x260);
	md_enable_status = HAL_READ32(0x40312000, 0x5C);
	osd_enable_status = HAL_READ32(0x403E0000, 0x3C);


	if ( (yuv_enable_status || rgb_enable_status) &&  !irqC_handler[VIDEOIN_ID_SOC].enable ) {
		irqC_handler[VIDEOIN_ID_SOC].enable = 1;
		yuv_isr_ng++;
		printf("[WARN]isr sync 0x%08x 0x%08x %d %d %d %d \n", yuv_enable_status, rgb_enable_status, yuv_isr_ng, isp_isr_ng, osd_isr_ng, hal_read_curtime_us());
	}

	if ( (ispctrl_enable_status || md_enable_status) &&  !irqC_handler[VIDEOIN_ID_MFD].enable ) {
		irqC_handler[VIDEOIN_ID_MFD].enable = 1;
		isp_isr_ng++;
		printf("[WARN]isr sync %d %d %d \n", yuv_isr_ng, isp_isr_ng, osd_isr_ng);
	}

	if ( osd_enable_status &&  !irqC_handler[VIDEOIN_ID_OSD].enable ) {
		irqC_handler[VIDEOIN_ID_OSD].enable = 1;
		osd_isr_ng++;
		printf("[WARN]isr sync %d %d %d \n", yuv_isr_ng, isp_isr_ng, osd_isr_ng);
	}


		HAL_WRITE32(0x40300000, 0x10, 0);
		HAL_WRITE32(0x403F0000, 0x250, 0);
		HAL_WRITE32(0x403F0000, 0x260, 0);
		HAL_WRITE32(0x40312000, 0x5C, 0);
		HAL_WRITE32(0x403E0000, 0x3C, 0);

		HAL_WRITE32(0x40300000, 0x10, ispctrl_enable_status);
		HAL_WRITE32(0x403F0000, 0x250, yuv_enable_status);
		HAL_WRITE32(0x403F0000, 0x260, rgb_enable_status);
		HAL_WRITE32(0x40312000, 0x5C, md_enable_status);
		HAL_WRITE32(0x403E0000, 0x3C, osd_enable_status);


#endif





		__DSB();
		__ISB();


	}
#if CONFIG_VERIFY_SYSVIEW
	traceISR_EXIT();
#endif

	return;
}

void RLX_EnableVideoInIRQ(int id)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irqC_handler[id].enable = 1;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

void RLX_DisableVideoInIRQ(int id)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irqC_handler[id].enable = 0;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}

void RLX_SetVideoInIrqVector(int id, unsigned int func)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();
	irqC_handler[id].handler = (irq_handler)func;
	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();
}


void RLX_EnableVideoInIRQ_woCS(int id)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;

	irqC_handler[id].enable = 1;

}

void RLX_DisableVideoInIRQ_woCS(int id)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;
	irqC_handler[id].enable = 0;
}

void RLX_SetVideoInIrqVector_woCS(int id, unsigned int func)
{
	if (id>=VIDEOIN_SH_NUMBER)
		return;
	irqC_handler[id].handler = (irq_handler)func;

}










void RLX_InitSharedIrq(void)
{
#if 0
	memset(irq4_handler, 0, sizeof(irq4_handler));
	RLX_ClearPendingIRQ(OTHERS_IRQn);
	RLX_SetVector(OTHERS_IRQn, (u32)rlx_sh_irq4_handler);
	RLX_EnableIRQ(OTHERS_IRQn);
#endif
	memset(irqC_handler, 0, sizeof(irqC_handler));
	RLX_ClearPendingIRQ(ISP_IRQn);
	RLX_SetVector(ISP_IRQn, (u32)rlx_sh_irqC_handler);
	RLX_SetPriority(ISP_IRQn, ISP_IRQPri);
	RLX_EnableIRQ(ISP_IRQn);



}

