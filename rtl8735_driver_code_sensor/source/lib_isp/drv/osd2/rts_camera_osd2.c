/*
 * osd device driver (kernel module)
 *
 * Realtek Semiconductor Corp.
 *
 * rts_camera_osd2.c
 *
 * Copyright (C) 2016      Wil_shi<wil_shi@realsil.com.cn>
 */

#define TAG	"OSD2"

#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include "rts_camera_osd2.h"
#include <linux/irqreturn.h>
#include <rtscamkit.h>
#include "rts_camera.h"
#include "rts_hw_id.h"
#include "rlx_reg.h"
#include "rlx_irq.h"
#include "rlx_clk.h"
#include "rlx_bitops.h"
#include "rtx_mutex.h"
#include "isp_debug.h"


#define RTS_OSD2_DRV_NAME		"rts_osd2"
#define RTS_OSD2_DEV_NAME		"rtsosd2"

#define OSD2_FRAME_DONE_BIT		0

#define RTS_REG_INT_EN_OSD2_TO_HOST		0x0000003c
#define RTS_REG_INT_FLAG_OSD2_TO_HOST		0x00000040
#define RTS_REG_OSD2_ISP_BUF_CONFIG		0x0000005c
#define RTS_REG_OSD2_BUSIF_ENABLE		0x00000064
#define RTS_REG_OSD2_BUSIF_RST			0x00000068

struct rtscam_osd2 {
	//struct device *dev;
	void *hwregs;
	unsigned long iobaseaddr;
	unsigned int iosize;

	int irq_enable;

	//struct rtscam_ge_device *jdev;
	int use_count;

	osMutexId_t lock;

	unsigned long status;
	osSemaphoreId_t alarm_wq;

	unsigned int ic_type;
	struct rtscam_region config;
};

static struct rtscam_osd2 gbl_rosd2={0};

static int rtscam_osd2_enable_clk(struct rtscam_osd2 *rosd2, int enable)
{
	return 0;
}

static int rtscam_osd2_read_reg(struct rtscam_osd2 *rosd2, off_t reg)
{
	return REG_R32((u32)rosd2->hwregs + reg);
}

static void rtscam_osd2_write_reg(struct rtscam_osd2 *rosd2,
				  u32 value, off_t reg)
{
	REG_W32((u32)rosd2->hwregs + reg, value);
}

static int rtscam_osd2_config_isp_buffer(struct rtscam_osd2 *rosd2)
{
	rtscam_osd2_write_reg(rosd2, rosd2->config.base >> 4,
			      RTS_REG_OSD2_ISP_BUF_CONFIG);

	return 0;
}

static int rtscam_osd2_enable_bus(struct rtscam_osd2 *rosd2)
{
	if (rosd2->ic_type != TYPE_RTS3915)
		return 0;

	rtscam_osd2_write_reg(rosd2, 0, RTS_REG_OSD2_BUSIF_RST);
	rtscam_osd2_write_reg(rosd2, 0x1, RTS_REG_OSD2_BUSIF_RST);
	rtscam_osd2_write_reg(rosd2, 0, RTS_REG_OSD2_BUSIF_RST);
	rtscam_osd2_write_reg(rosd2, 0x1, RTS_REG_OSD2_BUSIF_ENABLE);

	return 0;
}

static int rtscam_osd2_disable_bus(struct rtscam_osd2 *rosd2)
{
	if (rosd2->ic_type != TYPE_RTS3915)
		return 0;

	rtscam_osd2_write_reg(rosd2, 0, RTS_REG_OSD2_BUSIF_ENABLE);

	return 0;
}

static int rtscam_osd2_irq(void *data);

static int rtscam_osd2_enable_interrupt(struct rtscam_osd2 *rosd2,
					int enable)
{
	u32 int_en;
	u32 int_f = 0xffffffff;

	if (!xPortIsInsideInterrupt()) taskENTER_CRITICAL();

	if (enable) {
		int_en = 0xffffff03;



		RLX_SetVideoInIrqVector_woCS(VIDEOIN_ID_OSD, (u32)rtscam_osd2_irq);
		RLX_EnableVideoInIRQ_woCS(VIDEOIN_ID_OSD);

		rtscam_osd2_write_reg(rosd2, int_f, RTS_REG_INT_FLAG_OSD2_TO_HOST);
		
		RLX_ClearPendingIRQ(VIDEOIN_IRQn);		
		
		rtscam_osd2_write_reg(rosd2, int_en, RTS_REG_INT_EN_OSD2_TO_HOST);


	} else {
		int_en = 0;
		rtscam_osd2_write_reg(rosd2, int_en, RTS_REG_INT_EN_OSD2_TO_HOST);
		rtscam_osd2_write_reg(rosd2, int_f, RTS_REG_INT_FLAG_OSD2_TO_HOST);

		RLX_ClearPendingIRQ(VIDEOIN_IRQn);
		RLX_DisableVideoInIRQ_woCS(VIDEOIN_ID_OSD);		
		RLX_SetVideoInIrqVector_woCS(VIDEOIN_ID_OSD, (u32)0);

	}


	if (!xPortIsInsideInterrupt()) taskEXIT_CRITICAL();



	return 0;
}


#ifdef _OSD_LOG_INT_

#define CMD_LOG_CNT 5
#define ENCODE_LOG_CNT 11

struct osd_irq_cnt_t {
	uint32_t cmd[CMD_LOG_CNT];
	uint32_t blk[CMD_LOG_CNT];
	uint32_t color[CMD_LOG_CNT];
	uint32_t done[CMD_LOG_CNT];
	uint32_t err[CMD_LOG_CNT];

};


struct osd_irq_cnt_t irq_cnt[ENCODE_LOG_CNT] = {0};
int osd_encode_cnt = 0;
int osd_blk_cnt = 0;
int osd_color_cnt = 0;
int osd_cmd_cnt = 0;
int osd_done_cnt = 0;
int osd_err_cnt = 0;

#endif

//int osd_cmd_cnt = 0;
static int rtscam_osd2_irq(void *data)
{

	struct rtscam_osd2 *rosd2 = &gbl_rosd2;
	u32 status;
	u32 mask;
    portBASE_TYPE taskWoken = pdFALSE;

	const off_t reg = RTS_REG_INT_FLAG_OSD2_TO_HOST;

	status = rtscam_osd2_read_reg(rosd2, reg);

	if (!status)
		return IRQ_NONE;
	//printf("%s status 0x%08x\r\n", __func__, status);

	/*encode finish*/
	mask = 0x1;
	if (status & mask) {
		rtscam_osd2_write_reg(rosd2, mask, reg);


		//set_bit(OSD2_FRAME_DONE_BIT, &rosd2->status);
		rosd2->status |= 1;
		rosd2->status &= ~0x08;
		//wake_up_interruptible(&rosd2->alarm_wq);
#if 1
		if (rosd2->alarm_wq != NULL) {
			xSemaphoreGiveFromISR(rosd2->alarm_wq, &taskWoken);
			portEND_SWITCHING_ISR(taskWoken);
		}

#ifdef _OSD_LOG_INT_
        if (osd_done_cnt < CMD_LOG_CNT && osd_encode_cnt < ENCODE_LOG_CNT) {
        	irq_cnt[osd_encode_cnt].done[osd_done_cnt++] = hal_read_curtime_us();
			osd_encode_cnt++;
			osd_blk_cnt = 0;
			osd_color_cnt = 0;
			osd_cmd_cnt = 0;
			osd_done_cnt = 0;
			osd_err_cnt = 0;
        }
#endif
#else
		osSemaphoreRelease(rosd2->alarm_wq);
#endif
		//rtscam_ge_kill_fasync(rosd2->jdev, SIGIO, POLL_IN);
		return IRQ_HANDLED;
	}

	/*run done a cmd*/
	mask = 0x2;
	if (status & mask) {
		rtscam_osd2_write_reg(rosd2, mask, reg);
#ifdef _OSD_LOG_INT_
        if (osd_cmd_cnt < CMD_LOG_CNT && osd_encode_cnt < ENCODE_LOG_CNT) {
        	irq_cnt[osd_encode_cnt].cmd[osd_cmd_cnt++] = hal_read_curtime_us();
        }
#endif
		return IRQ_HANDLED;
	}

#ifdef _OSD_LOG_INT_
	mask = 0x20;
	if (status & mask) {
		//rtscam_osd2_write_reg(rosd2, mask, reg);
        if (osd_blk_cnt < CMD_LOG_CNT && osd_encode_cnt < ENCODE_LOG_CNT) {
        	irq_cnt[osd_encode_cnt].blk[osd_blk_cnt++] = hal_read_curtime_us();
        }

		return IRQ_HANDLED;
	}

	mask = 0x40;
	if (status & mask) {
		//rtscam_osd2_write_reg(rosd2, mask, reg);
        if (osd_color_cnt < CMD_LOG_CNT && osd_encode_cnt < ENCODE_LOG_CNT) {
        	irq_cnt[osd_encode_cnt].color[osd_color_cnt++] = hal_read_curtime_us();
        }
		return IRQ_HANDLED;
	}
#endif

	mask = 0x8;
	if (status & mask) {
		//rtscam_osd2_write_reg(rosd2, mask, reg);
	
		//rosd2->status |= 8;
#ifdef _OSD_LOG_INT_
        if (osd_err_cnt < CMD_LOG_CNT && osd_encode_cnt < ENCODE_LOG_CNT) {
        	irq_cnt[osd_encode_cnt].err[osd_err_cnt++] = hal_read_curtime_us();
        }
#endif
#if 1
		if (rosd2->alarm_wq != NULL) {
			xSemaphoreGiveFromISR(rosd2->alarm_wq, &taskWoken);
			portEND_SWITCHING_ISR(taskWoken);
		}

#else
		osSemaphoreRelease(rosd2->alarm_wq);
#endif
		return IRQ_HANDLED;
	}

	return IRQ_HANDLED;
}

/*
static int rtscam_osd2_open(struct file *filp)
{
	struct rtscam_ge_device *gdev = rtscam_devdata(filp);
	struct rtscam_osd2 *rosd2 = rtscam_ge_get_drvdata(gdev);

	filp->private_data = rosd2;

	return 0;
}

static int rtscam_osd2_close(struct file *filp)
{
	struct rtscam_osd2 *rosd2 = filp->private_data;

	filp->private_data = NULL;

	if (!rosd2)
		return -EINVAL;

	return 0;
}
*/

static long rtscam_osd2_do_ioctl(unsigned int cmd,
				 void *arg)
{
	struct rtscam_osd2 *rosd2 = &gbl_rosd2;
	int err = 0;

	if (_IOC_TYPE(cmd) != RTSOSD2_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > RTSOSD2_IOC_MAXNR)
		return -ENOTTY;
#ifdef __OSD_LOG__
	if (rosd2->lock)
		printf("%s 0x%08x \r\n", __func__, rosd2->lock);
#endif
	switch (cmd) {
	case RTSOSD2_IOCGHWOFFSET:
		*(unsigned long *)arg = (unsigned long)rosd2->hwregs;  //iobaseaddr;
		break;
	case RTSOSD2_IOCGHWIOSIZE:
		*(unsigned int *)arg = rosd2->iosize;
		break;
	case RTSOSD2_IOCDONE:
		clear_bit(OSD2_FRAME_DONE_BIT, &rosd2->status);
		break;
	case RTSOSD2_IOC_ENABLE:
		if (!rosd2->lock) {
			err = -EPERM;
			isp_error("%s RTSOSD2_IOC_ENABLE rosd2->lock==NULL \r\n",__func__);
			break;
		}
		err = xSemaphoreTake(rosd2->lock, ISP_SEM_TIMEOUT);
		if (err != pdTRUE) {
			err = -ETIME;
			isp_error("%s RTSOSD2_IOC_ENABLE rosd2->lock timeout \r\n",__func__);
			break;
		}
		if (atomic_inc_return_isp(&rosd2->use_count) == 1) {
			rtscam_osd2_enable_bus(rosd2);
			rtscam_osd2_enable_clk(rosd2, 1);
			rtscam_osd2_config_isp_buffer(rosd2);
			rtscam_osd2_enable_interrupt(rosd2, rosd2->irq_enable);
		}
		//osMutexRelease(rosd2->lock);
		xSemaphoreGive(rosd2->lock);
		break;
	case RTSOSD2_IOC_DISABLE:
		if (!rosd2->lock) {
			err = -EPERM;
			isp_error("%s RTSOSD2_IOC_ENABLE rosd2->lock==NULL \r\n",__func__);
			break;
		}
		err = xSemaphoreTake(rosd2->lock, ISP_SEM_TIMEOUT);
		if (err != pdTRUE) {
			err = -ETIME;
			isp_error("%s RTSOSD2_IOC_DISABLE rosd2->lock timeout \r\n",__func__);
			break;
		}
		if (atomic_dec_return_isp(&rosd2->use_count) == 0) {
			rtscam_osd2_enable_clk(rosd2, 0);
			rtscam_osd2_disable_bus(rosd2);
		}
		//osMutexRelease(rosd2->lock);
		xSemaphoreGive(rosd2->lock);

		break;
	case RTSOSD2_IOC_WAIT_INTERRUPT:
		if (!rosd2->lock) {
			err = -EPERM;
			isp_error("%s RTSOSD2_IOC_ENABLE rosd2->lock==NULL \r\n",__func__);
			break;
		}
		if (!rosd2->alarm_wq) {
			err = -EPERM;
			isp_error("%s RTSOSD2_IOC_ENABLE rosd2->alarm_wq==NULL \r\n",__func__);
			break;
		}
		err = xSemaphoreTake(rosd2->lock, ISP_SEM_TIMEOUT);
		if (err != pdTRUE) {
			err = -ETIME;
			isp_error("%s RTSOSD2_IOC_WAIT_INTERRUPT rosd2->lock timeout \r\n",__func__);
			break;
		}
		//err = wait_event_interruptible_timeout(rosd2->alarm_wq,
		//	test_bit(OSD2_FRAME_DONE_BIT, &rosd2->status) != 0,
		//	msecs_to_jiffies(30));
		//err = osSemaphoreAcquire(rosd2->alarm_wq, ISP_SEM_TIMEOUT);
		err = xSemaphoreTake(rosd2->alarm_wq, ISP_SEM_TIMEOUT);

		if (err == pdFALSE) {
			err = -ETIME;
		    isp_error("%s RTSOSD2_IOC_WAIT_INTERRUPT rosd2->alarm_wq timeout \r\n",__func__);
			//osMutexRelease(rosd2->lock);
			xSemaphoreGive(rosd2->lock);
			break;
		}

		err = 0;
		//osMutexRelease(rosd2->lock);
		xSemaphoreGive(rosd2->lock);
		break;
	default:
		rtsprintk(RTS_TRACE_ERROR,
			  "unknown[rtsosd2] ioctl 0x%08x, '%c' 0x%x\n",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		err = -ENOTTY;
		break;
	}

	return err;
}

long rtscam_osd2_ioctl(int fd, unsigned int cmd,
			      unsigned long arg)
{
	return rtscam_osd2_do_ioctl(cmd, (void*)arg);
}

/*
static unsigned int rtscam_osd2_poll(struct file *filp,
				     struct poll_table_struct *wait)
{
	struct rtscam_osd2 *rosd2  = &gbl_rosd2;
	unsigned int mask = 0;
	unsigned long req_events = poll_requested_events(wait);

	if (!(req_events & (POLLIN | POLLRDNORM)))
		return mask;

	if (!test_bit(OSD2_FRAME_DONE_BIT, &rosd2->status))
		poll_wait(filp, &rosd2->alarm_wq, wait);

	if (test_bit(OSD2_FRAME_DONE_BIT, &rosd2->status))
		mask = POLLIN | POLLRDNORM;

	return mask;
}

static int rtscam_osd2_mmap(struct file *filp, struct vm_area_struct *vm)
{
	struct rtscam_osd2 *rosd2 = filp->private_data;
	unsigned long addr, size, start, end;

	addr = vm->vm_pgoff << PAGE_SHIFT;
	size = vm->vm_end - vm->vm_start;
	start = rosd2->iobaseaddr;
	end = start + PAGE_ALIGN(rosd2->iosize);

	if (addr < start || (addr + size) > end)
		return -EINVAL;

	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff,
			size, vm->vm_page_prot) ? -EAGAIN : 0;
}

static struct rtscam_ge_file_operations rtscam_osd2_fops = {
	.owner		= THIS_MODULE,
	.open		= rtscam_osd2_open,
	.release	= rtscam_osd2_close,
	.ioctl		= rtscam_osd2_ioctl,
	.poll		= rtscam_osd2_poll,
	.mmap		= rtscam_osd2_mmap,
};

static int __create_device(struct rtscam_osd2 *rosd2)
{

	struct rtscam_ge_device *gdev;
	int ret;

	if (rosd2->jdev)
		return 0;

	gdev = rtscam_ge_device_alloc();
	if (!gdev)
		return -ENOMEM;

	strlcpy(gdev->name, RTS_OSD2_DEV_NAME, sizeof(gdev->name));
	gdev->parent = get_device(rosd2->dev);
	gdev->release = rtscam_ge_device_release;
	gdev->fops = &rtscam_osd2_fops;

	rtscam_ge_set_drvdata(gdev, rosd2);
	ret = rtscam_ge_register_device(gdev);
	if (ret) {
		rtscam_ge_device_release(gdev);
		return ret;
	}

	rosd2->jdev = gdev;

	return 0;
}

static void __remove_device(struct rtscam_osd2 *rosd2)
{
	struct rtscam_ge_device *gdev;

	if (!rosd2->jdev)
		return;

	gdev = rosd2->jdev;
	put_device(gdev->parent);
	rtscam_ge_unregister_device(gdev);
}
*/

static int rtscam_osd2_parse_buffer_config(struct rtscam_region *region)
{
#if 0
	region->base = 0x2a00;
	region->size = 0x200;
#else
	region->base = hal_isp_get_axi_buf_addr(OSD_BUF);
	region->size = hal_isp_get_axi_buf_size(OSD_BUF);
#endif
	//printf("osd buffer config: <0x%x 0x%x>\r\n", region->base, region->size);

	return 0;
}

osMutexId_t ewl_lock = NULL;
osMutexId_t reg_inst_lock = NULL;

int rtscam_osd2_probe(void)
{
	struct rtscam_osd2 *rosd2 = &gbl_rosd2;
	int err = 0;
	const osMutexAttr_t rinstlock_Mutex_attr = {
		"rinstlockMutex",                          // human readable mutex name
		osMutexRecursive | osMutexPrioInherit,    // attr_bits
		NULL,                         // memory for control block   
		0U                   // size for control block
	};

//	osSemaphoreAttr_t osd2semaphoreAttr = { .name = "osd2Semaphore" };



	isp_info("%s\r\n", __func__);

	atomic_set_isp(&rosd2->use_count, 0);
	rosd2->lock = xSemaphoreCreateMutex();
	if (!rosd2->lock) {
		isp_error("Couldn't allocate rts camera rosd2 mutex\r\n");
		err = RTS_FAIL;
		goto error;
	}
	//init_waitqueue_head(&rosd2->alarm_wq);
	//rosd2->alarm_wq = osSemaphoreNew(1, 0, &osd2semaphoreAttr);
	rosd2->alarm_wq = xSemaphoreCreateCounting(1, 0);
	if (rosd2->alarm_wq == NULL)
	{
		isp_error("osd2 alarm_wq sema create fail!\r\n");
		goto error;
	}

	rosd2->ic_type = TYPE_RTS3915;

	rosd2->hwregs = (void *)OSD_ENC_BASE;
	rosd2->iobaseaddr = OSD_ENC_BASE;// & ~0xA0000000;
	rosd2->iosize = 0x00001ffd;

	rosd2->irq_enable = 1;
	rtscam_osd2_enable_interrupt(rosd2, rosd2->irq_enable);

	err = rtscam_osd2_parse_buffer_config(&rosd2->config);
	if (err)
		goto error;

	if (reg_inst_lock == NULL) {
		reg_inst_lock = osMutexNew(&rinstlock_Mutex_attr);
		if ( reg_inst_lock == NULL ) {
			isp_error("reg_inst_lock alloc fail\n");
			err = RTS_FAIL;
			goto error;
		}
	}

	if (ewl_lock == NULL) {
		ewl_lock = xSemaphoreCreateMutex();
		if ( ewl_lock == NULL ) {
			isp_error("ewl_lock fail\n");
			err = RTS_FAIL;
			goto error;
		}
	}
	

	return 0;
error:

	memset(&gbl_rosd2, 0, sizeof(gbl_rosd2));
	return err;
}
extern struct rts_osd2_ewl_t gbl_osd2_ewl;

int rtscam_osd2_remove(void)
{
	struct rtscam_osd2 *rosd2 = &gbl_rosd2;

//	osMutexDelete(rosd2->lock);
//	osSemaphoreDelete(rosd2->alarm_wq);
	osd2_ewl_release(&gbl_osd2_ewl);

	if (rosd2->lock != NULL) {
		vSemaphoreDelete(rosd2->lock);
		rosd2->lock = NULL;
	}
	if (rosd2->alarm_wq != NULL) {
		vSemaphoreDelete(rosd2->alarm_wq);
		rosd2->alarm_wq = NULL;
	}
	//__remove_device(rosd2);
	//put_device(rosd2->dev);
	//rosd2->dev = NULL;
	memset(&gbl_rosd2, 0, sizeof(gbl_rosd2));

	return 0;
}

//static const struct of_device_id rtscam_osd2_ids[] = {
//	{ .compatible = "realtek,rts3903-osd2", },
//	{ .compatible = "realtek,rts3915-osd2", },
//	{ /* sentinel */ },
//};
//
//static struct platform_driver rtscam_osd2_driver = {
//	.driver		= {
//		.name	= RTS_OSD2_DRV_NAME,
//		.owner	= THIS_MODULE,
//		.of_match_table = of_match_ptr(rtscam_osd2_ids),
//	},
//	.probe		= rtscam_osd2_probe,
//	.remove		= rtscam_osd2_remove,
//};
//
//module_platform_driver(rtscam_osd2_driver);
//
//MODULE_DESCRIPTION("Realsil Osd device driver");
//MODULE_AUTHOR("Wil Shi <wil_shi@realsil.com.cn>");
//MODULE_LICENSE("GPL v2");
//MODULE_VERSION("0.1.1");
//MODULE_ALIAS("platform:" RTS_OSD2_DRV_NAME);
