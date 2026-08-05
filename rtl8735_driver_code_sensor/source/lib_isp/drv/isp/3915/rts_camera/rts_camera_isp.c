/*
 * rtsisp device driver (kernel module)
 * Realtek Semiconductor Corp.
 * rts_camera_isp.c
 * Copyright (C) 2014 Grant Shen <grant_shen@realsil.com.cn>
 */

#define DEBUG 0

#define TAG "ISP"

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include <linux/poll.h>
#include "rt_types.h"
#include "rt_util.h"
#include "rt_task.h"
#include "rts_errno.h"
#include <reset/reset-rts3915.h>
#include <reset/reset-rtsmem3915.h>
#include <media/videobuf2-core.h>
#include "rts_camera_isp.h"
#include "rts_camera_isp_mfd.h"
#include <rtscamkit.h>
#include "rts_camera_isp_regs.h"
#include "rts_camera.h"
#include "rts_camera_subdev.h"
#include "rts_camera_zoom.h"
#include "rts_isp_mem.h"
#include "rts_hw_id.h"
#include "rlx_reg.h"
#include "rlx_irq.h"
#include "rlx_clk.h"
#include <isp_utils.h>
#include "rts-dma-contig.h"
#include "rts_ioctl.h"
#include "isp_log.h"
#include "linux_list.h"
#include "rtx_mutex.h"
#include "rt_time.h"
#include "rtl8735b_i2c_simple.h"
#include "rtl8735b_gpio_simple.h"
#include "isp_debug.h"
#include "platform_conf.h"
#include "hal_isp.h"


static void isp_irq_thread(const void *data);
static void isp_statis_thread(const void *data);
extern voe_adp_t *voe_adp;

static osThreadId isp_handle = NULL;
static osThreadId isp_statis_handle = NULL;
osThreadDef(isp_irq_thread, osPriorityRealtime, 1, 64*1024);				// thread object
osThreadDef(isp_statis_thread, osPriorityRealtime, 1, 64*1024);		// thread object

//volatile int test_fix_method = 0;


static inline void __read_once_size(volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(u8 *)res = *(volatile u8 *)p; break;
	case 2: *(u16 *)res = *(volatile u16 *)p; break;
	case 4: *(u32 *)res = *(volatile u32 *)p; break;
#ifdef CONFIG_64BIT
	case 8: *(u64 *)res = *(volatile u64 *)p; break;
#endif
	}
}

#define READ_ONCE(p) \
		({ typeof(p) __val; __read_once_size(&p, &__val, sizeof(__val)); __val; })

#define list_first_entry_or_null(ptr, type, member) ({ \
        struct list_head *head__ = (ptr); \
        struct list_head *pos__ = READ_ONCE(head__->next); \
        pos__ != head__ ? list_entry(pos__, type, member) : NULL; \
})

#define RTS_ISP_DRV_NAME		"rts_isp"
#define RTS_ISP_DEV_NAME		"rtsisp"

#define MAX_SYNC_DELAY 4

#define STATIS_BUF_NUM 4
#define STATIS_MSG_SIZE (sizeof(struct rts_isp_msg_hdr) + \
			 sizeof(struct rts_isp_statis_data))

#define MOD_CONTROL v4l2_fourcc('c', 't', 'r', 'l')

//#define DEFAULT_ISP_CLK 80e6

#define off_t int
#define ssize_t int
#define size_t int

volatile u32 statis_updating = 0;
volatile unsigned long statis_cnt = 0;

#undef atomic_inc_return
static inline int atomic_inc_return(int *v)
{
	int ret;
	taskENTER_CRITICAL();
	*v = *v + 1;
	ret = *v;
	taskEXIT_CRITICAL();
	return ret;
}



struct rtscam_isp_message {
	osMutexId_t dev_lock;  //dev mutex //struct mutex *dev_lock;
	osSemaphoreId_t completion;  //for msg rspd //struct completion completion;

	u32 sequence;
	int msg_pending;
	size_t read_remain;
	u8 read_buf[256];
	off_t write_offset;
	u8 write_buf[256];

	osSemaphoreId_t wq;  //for msg req //wait_queue_head_t wq;
	u32 timeout;
};

struct rtscam_isp_snr_power {
	//struct device *dev;
	enum rts_isp_snr_pwr_type type;
	const char *name;
	void *handle; /* can be gpio/clk, no regulator */
	int current_value;
};

struct rtscam_isp_statis_node {
	void *addr;
	struct rts_isp_statis_data data;
	struct list_head list;
};

struct rtscam_isp_statis {
	int valid;

	//struct device *dev;
	struct rts_isp_statis_info info;
	void *alloc_addr;
	void *dma_addr;

	osMutexId_t lock;  //spinlock_t lock;
	//for statis info
	struct list_head idle;  //free list head
	struct list_head busy;  //collecting list head
	struct list_head done;  //ready list head
	struct list_head user;  //for user read out list head

	size_t read_remain;
	u8 msg_buf[STATIS_MSG_SIZE];
};

struct rtscam_isp_sync_item {
	struct list_head list;
	struct rts_isp_sync_reg reg;
	struct rts_isp_i2c_info i2c_info;
};

struct rtscam_isp_sync_delay {
	/* no item for RTS_ISP_INT_NONE */
	struct list_head irq[_MAX_RTS_ISP_INT - 1];
};

struct rtscam_isp_sync {
	osMutexId_t lock;  //struct mutex lock;
	int irq;
	struct rtscam_isp_sync_delay delay[MAX_SYNC_DELAY + 1];
	u32 index;
	struct list_head idle;
	u32 idle_num;
};

struct rtscam_isp_mem_item {
	struct list_head list;
	void *virt_addr;  //for alloc/free
	void *phy_addr;   //align32 of virt_addr
	size_t size;
};

struct rtscam_isp {
	//struct device *dev;
	//struct rtscam_ge_device *gdev;
	int user_count;
	osMutexId_t lock;

	int frame_count;
	int statis_count;

//	void *reg_base;
//	unsigned long io_start;
//	size_t io_size;
//	int irq;
	struct rtscam_isp_mfd *mfd;
	struct rtscam_isp_mfd_resource res;

	//clock
	struct {
//		struct clk_rlx *isp_clk;
		int isp_clk_refcnt;
//		int isp_clk_subdev_refcnt;
		struct clk_rlx *inf_clk;  //mipi clock
		int inf_clk_refcnt;
		struct clk_rlx *mipiout_clk;
		int mipiout_clk_refcnt;

		u32 isp_clk_fix;
	};
	//GPIO
	//struct {
	//	struct pinctrl *p;
	//	struct pinctrl_state *default_state;
	//	struct pinctrl_state *dvp_state;
	//	struct pinctrl_state *mipi_state;
	//} pins;

	struct rtscam_zoom_isp zoom_isp;
	int (*hook)(void *master, int id, void *arg);

	struct rtscam_isp_snr_power power[_MAX_SNR_POWER_TYPE];
	struct rtscam_isp_message message;
	struct rtscam_isp_statis statis;
	struct rtscam_isp_sync sync;
	//struct rtscam_mem_info *mem_info;  //video mem block handle
	struct list_head mem_list;  //list for user allocated kernel mem
	//struct i2c_adapter *adapter;
	struct rtscam_region i2c_cfg;
	struct rtscam_region statis_cfg;
	struct rtscam_region tnr_cfg;

	osSemaphoreId_t data_start_completion;  //data start event  //struct completion data_start_completion;
	osSemaphoreId_t frame_end_completion;  //frame end event  //struct completion frame_end_completion;

	//for HW internal mem reset
	//struct reset_control *sysmem;
	//struct reset_control *mipiout_sysmem;
	//struct reset_control *mipi_reset;
	//struct reset_control *mipiout_reset;
	u16 current_fps;

	u32 is_fpga:1;
	u32 has_pmu:1;
	u32 stopping:1;
	u32 data_start_done:1;

	u8 tnr_bit;
};


struct rtscam_isp_ioctl_info {
	unsigned int cmd;
	int (*func)(struct rtscam_isp *isp, void *arg);
};

//frome rts3916n.dtsi
#define SSOR_RST 9		//rst-gpio = <&pinctrl 9 GPIO_OPEN_DRAIN>;
#define SSOR_PWDN 10	  //pwdn-gpio = <&pinctrl 10 GPIO_OPEN_DRAIN>;

hal_gpio_adapter_t gpio_pin_pwrctrl;
hal_gpio_adapter_t gpio_pin_reset;
hal_gpio_adapter_t gpio_pin_pwdn;

static struct rtscam_isp gbl_isp={0};
static struct rtscam_isp *m_isp;
static osSemaphoreId_t isptaskSemaphore, ispstatisSemaphore;

#define ISP_IOCTL_INFO(isp_cmd, isp_func) \
	[_IOC_NR(isp_cmd)] = { \
		.cmd = isp_cmd, \
		.func = isp_func, \
	}

static inline u32 rtscam_isp_read_reg(struct rtscam_isp *isp, u32 offset)
{
	//return REG_R32(isp->reg_base + offset);
	return isp->mfd->read_reg(isp->mfd, RTS_MFD_MODUAL_ID_ISP, offset);
}

static inline void rtscam_isp_write_reg(struct rtscam_isp *isp,
					u32 value, u32 offset)
{
	//REG_W32(isp->reg_base + offset, value);
	isp->mfd->write_reg(isp->mfd, RTS_MFD_MODUAL_ID_ISP, offset, value);
}

static inline int power_is_gpio(const struct rtscam_isp_snr_power *power)
{
	return power->type <= SNR_PWRCTRL_GPIO;
}

static inline int power_is_clk(const struct rtscam_isp_snr_power *power)
{
	return power->type == SNR_HCLK;
}

static int rtscam_isp_snr_power_init(struct rtscam_isp *isp,
				     struct rtscam_isp_snr_power *power,
				     u32 type)
{
	static const char * const type_str[] = {
		//mapping defined in "rts3916n.dtsi"
		"rst",  //rst-gpio = <&pinctrl 9 GPIO_ACTIVE_HIGH>;
		"pwdn",  //pwdn-gpio = <&pinctrl 10 GPIO_ACTIVE_HIGH>;
		"pwrctrl",  //pwr control
		"hclk",  //<&clks RLX_CLK_SSOR_HCLK>;
		"io",
		"analog",
		"core",  //<&reset FORCE_RESET_H265_CORE>,
	};

	if (!power)
		return -EINVAL;

	//power->dev = dev;
	power->type = (enum rts_isp_snr_pwr_type)type;
	power->name = type_str[type];
	power->handle = NULL;
	power->current_value = 0;
	switch (type) {
		case 0:  //ssor_rst
			//GPIO_OE default 0, GPIO_PULLCTRL defaule 5
			break;
		case 1:  //ssor_pwdn
			//GPIO_OE default 0, GPIO_PULLCTRL defaule 5
			break;
	}

	return 0;
}
#if 0
static int gpiod_get(const char *name)
{
	int pin, ret = -1;

	if (!strcmp(name, "rst"))
		pin = SSOR_RST;
	else if (!strcmp(name, "pwdn"))
		pin = SSOR_PWDN;
	else {
		printf("ISP error set PIN \"%s-gpio\"\n", name);
		pin = -1;
	}

	if (pin >= 0) {  //request gpio
		//ret = rts_gpiod_request(pin);
		ret = 0;
		if (ret) {
			printf("ISP error request PIN \"%s-gpio\"\n", name);
			pin = -1;
		}
	}

	return pin;
}
#endif
static void gpiod_put(void *data)
{
	int pin = (int)data;

	if ((pin != SSOR_RST) && (pin != SSOR_PWDN)) {
		printf("ISP error put PIN \"#%d-gpio\"\n", pin);
		return;
	}

	//rts_gpiod_free(pin);
}
static int rtscam_isp_snr_power_put(struct rtscam_isp *isp,
				    struct rtscam_isp_snr_power *power)
{

	if (!power)
		return -EINVAL;

	if (!power->handle)
		return 0;

	if (power_is_gpio(power)) {
		gpiod_put(power->handle);
	} else if (power_is_clk(power)) {
#if 0 //juling--
		if (power->current_value)
			clk_disable_unprepare(power->handle);
		clk_put(power->handle);
#endif
	}
	//else if (power_is_voltage(power) && isp->has_pmu) {
	//	if (power->current_value)
	//		regulator_disable(power->handle);
	//	devm_regulator_put(power->handle);
	//}

	power->handle = NULL;
	power->current_value = 0;

	return 0;
}

//static int rtscam_isp_msg_check(const struct rts_isp_msg_hdr *req,
//				const struct rts_isp_msg_hdr *resp)
//{
//	return (req->sequence != resp->sequence ||
//		req->ret_len != resp->msg_len || req->isp_id != resp->isp_id ||
//		req->mod_id != resp->mod_id || req->action != resp->action);
//}

static inline bool
rtscam_isp_message_can_read(struct rtscam_isp_message *message)
{
	return message->read_remain > 0;
}

static inline bool
rtscam_isp_message_can_write(struct rtscam_isp_message *message)
{
	struct rts_isp_msg_hdr *hdr;

	hdr = (struct rts_isp_msg_hdr *)message->write_buf;
	//isp_info("%s: %d %d \r\n", __FUNCTION__, message->write_offset, hdr->msg_len);

	return (message->write_offset == 0 ||
		message->write_offset < (int)hdr->msg_len);
}

static inline void
rtscam_isp_message_set_sequence(struct rtscam_isp_message *message,
				struct rts_isp_msg_hdr *hdr)
{
	hdr->sequence = ++message->sequence;
}

static inline bool
rtscam_isp_message_check_sequence(struct rtscam_isp_message *message,
				  struct rts_isp_msg_hdr *hdr)
{
	return hdr->sequence == message->sequence;
}

static int rtscam_isp_message_init(struct rtscam_isp_message *message,
				   osMutexId_t dev_lock)
{
	if (!message)
		return -EINVAL;

	message->dev_lock = dev_lock;
	message->timeout = 1000;
	//osSemaphoreAttr_t msgcmpltAttr = { .name = "msgcmpltSemaphore" };
	//message->completion = osSemaphoreNew(1, 0, &msgcmpltAttr);
	message->completion = xSemaphoreCreateCounting(1, 0);
	if (message->completion == NULL)
	{
		printf("{isp->rtscam_isp_message_init} new completion fail!\r\n");
		return RT_E_CREATE_FAIL;
	}

	//osSemaphoreAttr_t msgwqAttr = { .name = "msgwqSemaphore" };
	//message->wq = osSemaphoreNew(1, 0, &msgwqAttr);
	message->wq = xSemaphoreCreateCounting(1, 0);
	if (message->wq == NULL)
	{
		printf("{isp->rtscam_isp_message_init} new wq fail!\r\n");
		return RT_E_CREATE_FAIL;
	}

	return 0;
}

static int rtscam_isp_message_reinit(struct rtscam_isp_message *message)
{
	if (!message)
		return -EINVAL;

	message->msg_pending = FALSE;
	message->read_remain = 0;
	message->write_offset = 0;
	//reinit_completion(&message->completion);
	//osSemaphoreAcquire(message->completion, 0);  //reset to 0
	message->sequence = hal_read_curtime_us();  //get_random_int();

	return 0;
}

static int rtscam_isp_message_call(struct rtscam_isp_message *message,
				   u32 isp_id, u32 cmd, void *buf, size_t len)
{
	int status, ret = 0;
	struct rts_isp_msg_hdr *req;
	struct rts_isp_msg_hdr *resp;

	if (!message)
		return -EINVAL;
	if (!buf && len)
		return -EINVAL;

	if (len + sizeof(*req) > sizeof(message->read_buf))
		return -ERANGE;
	if (message->msg_pending || message->read_remain)
		return -EBUSY;

	req = (struct rts_isp_msg_hdr *)message->read_buf;
	resp = (struct rts_isp_msg_hdr *)message->write_buf;

	rtscam_isp_message_set_sequence(message, req);
	req->msg_len = sizeof(*req) + len;
	req->ret_len = sizeof(*req);
	req->isp_id = isp_id;
	req->mod_id = MOD_CONTROL;
	req->action = cmd;
	req->ret_val = 0;
	req->reloc_pos = 0;
	req->reloc_num = 0;
	memcpy(req + 1, buf, len);

	message->msg_pending = FALSE;  //TRUE;
	message->read_remain = 0;  //req->msg_len;
	/* wake up read request */
	//wake_up(&message->wq);
//	if (osSemaphoreRelease(message->wq) != osOK)
//		rtsprintk(RTS_TRACE_ERROR, "{%s} message enqueue failed\n", __func__);
	//osMutexRelease(message->dev_lock);
	xSemaphoreGive(message->dev_lock);
//asm("sdbbp");
	status = rts_rev_ioctl((void*)req, buf, len);  //call to user space cb()
	if (status) {
		rtsprintk(RTS_TRACE_ERROR, "{%s} message exec failed\n", __func__);
		return status;
	}

//	status = osSemaphoreAcquire(message->completion,
//					     message->timeout*portTICK_RATE_MS);
	ret = xSemaphoreTake(message->dev_lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_isp_message_call waiit message->dev_lock timeout\n\r");
		return -ETIMEDOUT;
	}

	message->msg_pending = FALSE;
//	if (status != osOK) {
//		/* does not read any read message */
//		if ((int)req->msg_len == message->read_remain)
//			message->read_remain = 0;
//		/* timeout ocurred before wakeup */
//		if ((int)resp->msg_len == message->write_offset) {
//			message->write_offset = 0;
//			//wake_up(&message->wq);
//			if (osSemaphoreRelease(message->wq) != osOK)
//		        rtsprintk(RTS_TRACE_ERROR, "{%s} message enqueue failed\n", __func__);
//		}
//		rtsprintk(RTS_TRACE_ERROR, "message call timeout\n");
//		return -ETIMEDOUT;
//	}

	/* wakeup success mean write done */
	message->write_offset = 0;
	//wake_up(&message->wq);
//	if (osSemaphoreRelease(message->wq) != osOK)
//        rtsprintk(RTS_TRACE_ERROR, "{%s} message enqueue failed\n", __func__);
	//if (rtscam_isp_msg_check(req, resp))
	//	return -ENOMSG;
	return resp->ret_val;
}

static ssize_t rtscam_isp_message_read(struct rtscam_isp_message *message,
				       char __user *buf, size_t size)
{
	off_t off;
	struct rts_isp_msg_hdr *hdr;

	hdr = (struct rts_isp_msg_hdr *)message->read_buf;
	off = hdr->msg_len - message->read_remain;
	size = min(size, message->read_remain);

	memcpy(buf, (char *)hdr + off, size);
	message->read_remain -= size;

	return size;
}
#if 0
static ssize_t rtscam_isp_message_write(struct rtscam_isp_message *message,
					const char *buf, size_t size)
{
	struct rts_isp_msg_hdr *hdr;

	hdr = (struct rts_isp_msg_hdr *)message->write_buf;

	if (message->write_offset == 0) {
		/* write header */
		if (size < (int)sizeof(*hdr))
			return -ERANGE;
		size = sizeof(*hdr);
		if (memcpy(hdr, buf, size))
			return -EFAULT;
		message->write_offset += size;
		if ((int)hdr->msg_len == size)
			goto check;
		return size;
	}

	/* write body */
	size = min((int)(hdr->msg_len - sizeof(*hdr)), size);
	if (size == 0)
		return -EAGAIN;
	if (memcpy(hdr, buf, size))
		return -EFAULT;
	message->write_offset += size;

	if (message->write_offset < (int)hdr->msg_len)
		return size;


check:
	if (rtscam_isp_message_check_sequence(message, hdr)) {
		if (message->msg_pending)
			osSemaphoreRelease(message->completion);
		else
			message->write_offset = 0;
	} else {
		message->write_offset = 0;
		rtsprintk(RTS_TRACE_ERROR, "error sequence: %u != %u\n",
			  hdr->sequence, message->sequence);
	}

	return size;
}
#endif

static inline int rtscam_isp_statis_valid(struct rtscam_isp_statis *statis)
{
	return atomic_read_isp(&statis->valid);
}

static inline bool
rtscam_isp_statis_read_partial(struct rtscam_isp_statis *statis)
{
	struct rts_isp_msg_hdr *hdr;

	hdr = (struct rts_isp_msg_hdr *)statis->msg_buf;
	return statis->read_remain > 0 && statis->read_remain < (int)hdr->msg_len;
}

static int rtscam_isp_statis_cleanup(struct rtscam_isp_statis *statis);

static int rtscam_isp_statis_init(struct rtscam_isp_statis *statis,
				  u32 each_buf_size)
{
	int i;
	struct rts_isp_statis_info *info;

	if (!statis)
		return -EINVAL;

	info = &statis->info;
	atomic_set_isp(&statis->valid, 0);
	//spin_lock_init(&statis->lock);

	statis->lock = xSemaphoreCreateMutex();
	if ( !statis->lock ) {
		rtsprintk(RTS_TRACE_ERROR, "statis->lock mutex alloc fail\n");
		return -ENOMEM;
	}
	INIT_LIST_HEAD(&statis->idle);
	INIT_LIST_HEAD(&statis->busy);
	INIT_LIST_HEAD(&statis->done);
	INIT_LIST_HEAD(&statis->user);
	info->num = STATIS_BUF_NUM;
	info->size = ALIGN(each_buf_size, 32);

	statis->alloc_addr = rts_malloc(info->size * info->num + 32);
	if (!statis->alloc_addr) {
		rtsprintk(RTS_TRACE_ERROR, "alloc statis buffer fail\n");
		return -ENOMEM;
	}
	//statis->dma_addr = (void*)(ALIGN((int)statis->alloc_addr, 32) & ~0xA0000000);
	statis->dma_addr = (void*)(ALIGN((int)statis->alloc_addr, 32));

	info->phy_addr = (__u32)statis->dma_addr;
	//statis->dev = dev;
	//isp_info("%s statis buf 0x%08x size %d %d \r\n", __FUNCTION__, info->phy_addr, info->size, info->size * info->num + 32);

	for (i = 0; i < (int)info->num; i++) {
		struct rtscam_isp_statis_node *node;

		node = rts_malloc(sizeof(*node));
		if (!node) {
			rtsprintk(RTS_TRACE_ERROR, "alloc statis node fail\n");
			rtscam_isp_statis_cleanup(statis);
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&node->list);
		node->data.buf_id = i;
		node->addr = (void*)(info->phy_addr + i * info->size);
		//printf("%s %d buf 0x%08x size %d \r\n", __func__, node->data.buf_id, node->addr, info->size);
		list_add_tail(&node->list, &statis->idle);
	}
	//isp_info("%s move idle to busy 0x%08x \r\n", __FUNCTION__, statis->idle.next);
	list_move_tail(statis->idle.next, &statis->busy);

	return 0;
}

static int rtscam_isp_statis_cleanup(struct rtscam_isp_statis *statis)
{
	//unsigned long flags;
	struct rtscam_isp_statis_node *node;
	struct rtscam_isp_statis_node *next;
	int ret;
	//if (!statis->dev)
	//	return 0;

	//spin_lock_irqsave(&statis->lock, flags);
	ret = xSemaphoreTake(statis->lock, 5000);
	if (ret != pdTRUE) {
		isp_error(" %s statis->lock error result %d \r\n", __func__, ret);
		return ret;
	}
	list_for_each_entry_safe(node, next, &statis->user, list, struct rtscam_isp_statis_node) {
		list_del_init(&node->list);
#ifdef _DEBUG_MEM_
		isp_info("%s 0x%08x \r\n", __func__, node);
#endif
		rts_free(node);
	}
	list_for_each_entry_safe(node, next, &statis->idle, list, struct rtscam_isp_statis_node) {
		list_del_init(&node->list);
#ifdef _DEBUG_MEM_
		isp_info("%s 0x%08x \r\n", __func__, node);
#endif
		rts_free(node);
	}
	list_for_each_entry_safe(node, next, &statis->busy, list, struct rtscam_isp_statis_node) {
		list_del_init(&node->list);
#ifdef _DEBUG_MEM_
		isp_info("%s 0x%08x \r\n", __func__, node);
#endif
		rts_free(node);
	}
	list_for_each_entry_safe(node, next, &statis->done, list, struct rtscam_isp_statis_node) {
		list_del_init(&node->list);
#ifdef _DEBUG_MEM_
		isp_info("%s 0x%08x \r\n", __func__, node);
#endif
		rts_free(node);
	}

	if (statis->alloc_addr) {
		rts_free(statis->alloc_addr);
	}


	//spin_unlock_irqrestore(&statis->lock, flags);
	if(statis->lock) {

		//osMutexRelease(statis->lock);
		xSemaphoreGive(statis->lock);
		//osMutexDelete(statis->lock);
		if (statis->lock != NULL) {
			vSemaphoreDelete(statis->lock);
			statis->lock = NULL;
		}
	}
	atomic_set_isp(&statis->valid, 0);
	//dma_free_coherent(statis->dev, statis->info.size * statis->info.num,
	//		  statis->virt_addr, statis->info.phy_addr);
	//statis->dev = NULL;

	return 0;
}

/*
static struct rtscam_isp_statis_node *
__rtscam_isp_statis_get_node(struct rtscam_isp_statis *statis,
			     struct list_head *list, u32 buf_id)

{
	struct rtscam_isp_statis_node *node;

	if (!statis || buf_id >= statis->info.num || !list)
		return NULL;

	list_for_each_entry(node, list, list, struct rtscam_isp_statis_node) {
		if (buf_id == node->data.buf_id)
			return node;
	}
	return NULL;
}
*/

static void __rtscam_isp_statis_msg_prepare(struct rtscam_isp_statis *statis)
{
	//unsigned long flags;
	struct rts_isp_msg_hdr *hdr;
	struct rtscam_isp_statis_node *node;

	if (statis->read_remain)
		return;

	//spin_lock_irqsave(&statis->lock, flags);
	if (xSemaphoreTake(statis->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("__rtscam_isp_statis_msg_prepare wait statis->lock timeout\n\r");
		return;
	}
	//WARN_ON(list_empty(&statis->done));
	node = list_first_entry(&statis->done,
				struct rtscam_isp_statis_node, list);

	//mark as DMA-able from HW
	//dma_sync_single_range_for_cpu(statis->dev, statis->info.phy_addr,
	//			      node->addr - statis->info.phy_addr,
	//			      statis->info.size, DMA_FROM_DEVICE);

	hdr = (struct rts_isp_msg_hdr *)statis->msg_buf;
	hdr->sequence = node->data.frame_count;
	hdr->msg_len = STATIS_MSG_SIZE;
	hdr->ret_len = 0;
	hdr->isp_id = 0;
	hdr->mod_id = MOD_CONTROL;
	hdr->action = RTS_ISP_STATIS_DONE;
	hdr->ret_val = 0;
	hdr->reloc_pos = 0;
	hdr->reloc_num = 0;
	//memcpy(hdr + 1, &node->data, sizeof(node->data));

	statis->read_remain = STATIS_MSG_SIZE;

	list_move(&node->list, &statis->user);
	//spin_unlock_irqrestore(&statis->lock, flags);
	//osMutexRelease(statis->lock);
	xSemaphoreGive(statis->lock);
}

static ssize_t __rtscam_isp_statis_msg_read(struct rtscam_isp_statis *statis,
					    char __user *buf, size_t size)
{
	off_t off;
	//unsigned long flags;

	size = min(size, statis->read_remain);
	off = STATIS_MSG_SIZE - statis->read_remain;
	memcpy(buf, statis->msg_buf + off, size);
	statis->read_remain -= size;
	if (statis->read_remain > 0)
		return size;

	//spin_lock_irqsave(&statis->lock, flags);
	if (xSemaphoreTake(statis->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("__rtscam_isp_statis_msg_read wait statis->lock timeout\n\r");
		return size;
	}
	if (list_empty(&statis->done))
		atomic_set_isp(&statis->valid, 0);
	//spin_unlock_irqrestore(&statis->lock, flags);
	//osMutexRelease(statis->lock);
	xSemaphoreGive(statis->lock);
	return size;
}

static ssize_t rtscam_isp_statis_read(struct rtscam_isp_statis *statis,
				      char __user *buf, size_t size)
{
	__rtscam_isp_statis_msg_prepare(statis);
	return __rtscam_isp_statis_msg_read(statis, buf, size);
}

static inline int rtscam_isp_sync_max_delay(struct rtscam_isp_sync *sync)
{
	return ARRAY_SIZE(sync->delay) - 1;
}

static inline int rtscam_isp_sync_index(struct rtscam_isp_sync *sync, int delay)
{
	return (sync->index + delay) % ARRAY_SIZE(sync->delay);
}

static inline struct list_head *
rtscam_isp_sync_get_head(struct rtscam_isp_sync *sync, int delay, int irq)
{
	return &sync->delay[rtscam_isp_sync_index(sync, delay)].irq[irq - 1];
}

static int rtscam_isp_sync_init(struct rtscam_isp_sync *sync)
{
	int i;
	int j;
	struct rtscam_isp_sync_item *item;

	if (!sync)
		return -EINVAL;

	//mutex_init(&sync->lock);
	sync->lock = xSemaphoreCreateMutex();
	if ( !sync->lock ) {
		rtsprintk(RTS_TRACE_ERROR, "sync->lock mutex alloc fail\r\n");
		return RTS_FAIL;
	}
	atomic_set_isp(&sync->irq, RTS_ISP_INT_NONE);
	for (i = 0; i < (int)ARRAY_SIZE(sync->delay); i++)
		for (j = 0; j < (int)ARRAY_SIZE(sync->delay->irq); j++)
			INIT_LIST_HEAD(&sync->delay[i].irq[j]);
	INIT_LIST_HEAD(&sync->idle);
	sync->idle_num = 0;

	for (i = 0; i < 32; i++) {
		item = rts_malloc(sizeof(*item));
		if (item)
			INIT_LIST_HEAD(&item->list);
			
		list_add(&item->list, &sync->idle);
		sync->idle_num++;
	}
	return RTS_OK;
}

static int rtscam_isp_sync_clean_list(struct list_head *head)
{
	struct rtscam_isp_sync_item *item;
	struct rtscam_isp_sync_item *next;
	//isp_info("%s 0x%08x \r\n", __func__, head);
	list_for_each_entry_safe(item, next, head, list, struct rtscam_isp_sync_item) {
#ifdef _DEBUG_MEM_
		isp_info("%s rts_free 0x%08x 0x%08x \r\n", __func__, &item->list, item);
#endif
		list_del(&item->list);
		rts_free(item);
	}
	return 0;
}

static int rtscam_isp_sync_cleanup(struct rtscam_isp_sync *sync)
{
	int i;
	int j;
	int ret = 0;

	ret = xSemaphoreTake(sync->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_isp_sync_cleanup wait sync->lock timeout\n\r");
		return -ETIMEDOUT;
	}
	atomic_set_isp(&sync->irq, RTS_ISP_INT_NONE);
	for (i = 0; i < (int)ARRAY_SIZE(sync->delay); i++)
		for (j = 0; j < (int)ARRAY_SIZE(sync->delay->irq); j++)
			rtscam_isp_sync_clean_list(&sync->delay[i].irq[j]);
	sync->index = 0;
	rtscam_isp_sync_clean_list(&sync->idle);
	sync->idle_num = 0;
	//osMutexRelease(sync->lock);
	xSemaphoreGive(sync->lock);
	return 0;
}

static struct rtscam_isp_sync_item *
__rtscam_isp_sync_get_idle(struct rtscam_isp_sync *sync)
{
	struct rtscam_isp_sync_item *item;

	if (!sync)
		return NULL;

	if (sync->idle_num) {
		item = list_last_entry(&sync->idle,
				       struct rtscam_isp_sync_item, list);
		list_del_init(&item->list);
		sync->idle_num--;
	} else {
		item = rts_malloc(sizeof(*item));
		if (item)
			INIT_LIST_HEAD(&item->list);
	}

	return item;
}

static int __rtscam_isp_sync_put_idle(struct rtscam_isp_sync *sync,
				      struct rtscam_isp_sync_item *item)
{
	if (!sync || !item)
		return -EINVAL;

	list_add(&item->list, &sync->idle);
	sync->idle_num++;
	//if (sync->idle_num <= 32) {
		//isp_info("%s idle_num %d 0x%08x \r\n", __func__, sync->idle_num, item);
	//	return 0;
	//}
	while (sync->idle_num > 32) {
		item = list_last_entry(&sync->idle,
				       struct rtscam_isp_sync_item, list);
		list_del(&item->list);
#ifdef _DEBUG_MEM_
		isp_info("%s rts_free %d 0x%08x 0x%08x \r\n", __func__, sync->idle_num, &item->list, item);
#endif
		rts_free(item);
		sync->idle_num--;
	}
	return 0;
}

static int __rtscam_isp_sync_add_regs(struct rtscam_isp_sync *sync,
				      const struct rts_isp_sync_reg *reg,
				      u32 num,
				      const struct rts_isp_i2c_info *i2c_info)
{
	int i;
	struct rtscam_isp_sync_item *item;

	for (i = 0; i < (int)num; i++) {
		struct list_head *head;

		item = __rtscam_isp_sync_get_idle(sync);
		if (!item)
			return -ENOMEM;
		item->reg = reg[i];
		if (i2c_info)
			item->i2c_info = *i2c_info;
		head = rtscam_isp_sync_get_head(sync,
						item->reg.info.delay_frames,
						item->reg.info.interrupt);
		list_add_tail(&item->list, head);
#ifdef _DEBUG_I2C_
		if (i2c_info)
			printf("%s i2c 0x%08x 0x%08x delay %d int %d list 0x%08x \r\n", __func__, reg->i2c.addr, reg->i2c.data, item->reg.info.delay_frames, item->reg.info.interrupt, &item->list);
		else
			printf("%s reg 0x%08x 0x%08x delay %d int %d list 0x%08x \r\n", __func__, reg->reg.addr,  reg->reg.data, item->reg.info.delay_frames, item->reg.info.interrupt, &item->list);
#endif
	}

	return 0;
}

static int __rtscam_isp_sync_add_gain(struct rtscam_isp_sync *sync,
				      struct rts_isp_sync_regs *regs)
{
	struct rts_isp_sync_reg gain_reg[2];

	if (!regs->isp_gain)
		return 0;

	gain_reg[0].reg.addr = AE_GAIN;
	gain_reg[0].reg.data = regs->isp_gain;
	gain_reg[0].reg.mask = 0;
	gain_reg[1].reg.addr = AE_GAIN_CTRL;
	gain_reg[1].reg.data = 0x100 | min(regs->isp_gain_delay, 3U);
	gain_reg[1].reg.mask = 0;
	if (regs->num) {
		gain_reg[0].info = regs->reg[0].info;
		gain_reg[0].info.type = RTS_ISP_SYNC_REG_TYPE_REG;
		gain_reg[1].info = gain_reg[0].info;
	} else {
		gain_reg[0].info.delay_frames = 0;
		gain_reg[0].info.interrupt = (enum rts_isp_interrupt)(RTS_ISP_INT_NONE + 1);
		gain_reg[0].info.type = RTS_ISP_SYNC_REG_TYPE_REG;
		gain_reg[1].info = gain_reg[0].info;
	}
	return __rtscam_isp_sync_add_regs(sync, gain_reg, ARRAY_SIZE(gain_reg),
					  NULL);
}

static int rtscam_isp_sync_check_refine_regs(struct rtscam_isp_sync *sync,
					     struct rts_isp_sync_regs *regs)
{
	int i;
	int total_delay = 0;
	int last_int = RTS_ISP_INT_NONE + 1;

	if (!sync || !regs)
		return -EINVAL;

	for (i = 0; i < (int)regs->num; i++) {
		struct rts_isp_sync_reg *reg = &regs->reg[i];

		if (reg->info.type >= _MAX_RTS_ISP_SYNC_REG_TYPE ||
		    reg->info.interrupt >= _MAX_RTS_ISP_INT)
			return -EINVAL;

		if (reg->info.interrupt == RTS_ISP_INT_NONE)
			reg->info.interrupt = (enum rts_isp_interrupt)last_int;
		if (reg->info.delay_frames)
			last_int = RTS_ISP_INT_NONE + 1;
		else
			last_int = reg->info.interrupt;

		if (i == 0 && reg->info.delay_frames == 0 &&
		    reg->info.interrupt <= (u32)atomic_read_isp(&sync->irq))  //the moment of handling RTS_ISP_INT_FRAME_END int
			reg->info.delay_frames = 1;
		total_delay += reg->info.delay_frames;
		if (total_delay > rtscam_isp_sync_max_delay(sync)) {
			printf("%s total_delay %d > max_delay", __func__, total_delay);
			return -EINVAL;
		}
		reg->info.delay_frames = total_delay;
	}

	return 0;
}
static int rtscam_isp_write_sync_i2c(struct rtscam_isp *isp,
				     struct rts_isp_i2c_reg_mask *i2c_mask,
				     struct rts_isp_i2c_info *i2c_info);
static int rtscam_isp_write_sync_reg(struct rtscam_isp *isp,
				     struct rts_isp_reg_mask *reg);
int __rtscam_isp_set_gain(struct rts_isp_sync_regs *regs)
{
	struct rts_isp_sync_reg gain_reg[2];

	if (!regs->isp_gain)
		return 0;

	gain_reg[0].reg.addr = AE_GAIN;
	gain_reg[0].reg.data = regs->isp_gain;
	gain_reg[0].reg.mask = 0;
	gain_reg[1].reg.addr = AE_GAIN_CTRL;
	gain_reg[1].reg.data = 0x100 | min(regs->isp_gain_delay, 3U);
	gain_reg[1].reg.mask = 0;
	if (regs->num) {
		gain_reg[0].info = regs->reg[0].info;
		gain_reg[0].info.type = RTS_ISP_SYNC_REG_TYPE_REG;
		gain_reg[1].info = gain_reg[0].info;
	} else {
		gain_reg[0].info.delay_frames = 0;
		gain_reg[0].info.interrupt = RTS_ISP_INT_NONE + 1;
		gain_reg[0].info.type = RTS_ISP_SYNC_REG_TYPE_REG;
		gain_reg[1].info = gain_reg[0].info;
	}
	rtscam_isp_write_sync_reg(m_isp, &(gain_reg[0].reg));
	rtscam_isp_write_sync_reg(m_isp, &(gain_reg[1].reg));

	//printf("gain_reg 0: 0x%08x 0x%08x 1: 0x%08x 0x%08x \n", gain_reg[0].reg.addr, gain_reg[0].reg.data, gain_reg[1].reg.addr, gain_reg[1].reg.data);
}

int __rtscam_isp_set_i2c(const struct rts_isp_sync_reg *reg,
				      u32 num,
				      const struct rts_isp_i2c_info *i2c_info)
{
	int i;


	for (i = 0; i < (int)num; i++) {

		if (reg[i].info.type == RTS_ISP_SYNC_REG_TYPE_REG) {
			rtscam_isp_write_sync_reg(m_isp, &(reg[i].reg));
		}
		else {
			rtscam_isp_write_sync_i2c(m_isp, &(reg[i].i2c), i2c_info);
		}

	}

	return 0;
}


static int rtscam_isp_sync_add_regs(struct rtscam_isp_sync *sync,
				    struct rts_isp_sync_regs *regs)
{
	//int i;
	int ret = 0;
	//struct rtscam_isp_sync_item *item;

	ret = xSemaphoreTake(sync->lock, ISP_SEM_TIMEOUT);
	if (ret != pdTRUE) {
		isp_error("rtscam_isp_sync_add_regs wait sync->lock timeout\n\r");
		return -ETIMEDOUT;
	}
	ret = rtscam_isp_sync_check_refine_regs(sync, regs);
	if (ret){
		printf("%s rtscam_isp_sync_check_refine_regs ret=%d\n", __func__, ret);
		goto out;
	}
/*
	for (i = 0; i < (int)regs->num; i++) {
		struct list_head *head;

		item = __rtscam_isp_sync_get_idle(sync);
		if (!item) {
			ret = -ENOMEM;
			goto out;
		}
		item->reg = regs->reg[i];
		item->i2c_info = regs->i2c_info;
		head = rtscam_isp_sync_get_head(sync,
						item->reg.info.delay_frames,
						item->reg.info.interrupt);
		list_add_tail(&item->list, head);
	}
*/
	ret = __rtscam_isp_sync_add_gain(sync, regs);
	if (ret)
		goto out;
	ret = __rtscam_isp_sync_add_regs(sync, regs->reg, regs->num,
					 &regs->i2c_info);
out:
//	osMutexRelease(sync->lock);
	xSemaphoreGive(sync->lock);
	return ret;
}

static int rtscam_isp_get_io_start(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printk("ioctl RTSISP_IOC_GET_IO_START\n");
	*(u32 *)args = isp->res.io_start;
	return 0;
}

static int rtscam_isp_get_io_size(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printk("ioctl RTSISP_IOC_GET_IO_SIZE\n");
	*(u32 *)args = isp->res.io_size;
	return 0;
}

static int rtscam_isp_set_power(struct rtscam_isp *isp, void *arg)
{
	int i;
	int ret = 0;
	struct rts_isp_snr_pwr *power = arg;

	if (!isp || !arg)
		return -EINVAL;

	if (power->num > ARRAY_SIZE(power->items))
		return -EINVAL;

	for (i = 0; i < (int)power->num; i++)
		if (power->items[i].type >= _MAX_SNR_POWER_TYPE)
			return -EINVAL;

	for (i = 0; i < (int)power->num; i++) {
		u32 type = power->items[i].type;
		u32 value = power->items[i].value;
#if 0
		ret = rtscam_isp_snr_power_get(isp, &isp->power[type]);
		if (ret)
			break;
		ret = rtscam_isp_snr_power_set(isp, &isp->power[type], value);
		if (ret)
			break;
#else
	if (power_is_gpio(&isp->power[type])) {
#ifdef _PWR_SNRPLL_LOG_
		printf("GPIO set %s\n\r", isp->power[type].name);
#endif
		if (!strcmp(isp->power[type].name, "rst"))
			hal_gpio_write_simple(&gpio_pin_reset, value);
		else if (!strcmp(isp->power[type].name, "pwdn"))
			hal_gpio_write_simple(&gpio_pin_pwdn, value);
	} else if (power_is_clk(&isp->power[type])) {
#ifdef _PWR_SNRPLL_LOG_
		printf("sensor clock: %u\n\r", value);
#endif
		hclk_set_rate(value);
	}
#endif
		udelay(power->items[i].delay);
	}

	return ret;
}

volatile hal_i2c_adapter_t  i2c_master_sample = {0};
//volatile hal_i2c_adapter_t  i2c_master_aphy_sample;

volatile int     masterTXC;
volatile int     masterRXC;
// Rx
#define CLEAR_MST_RXC_FLAG	(masterRXC = 0)
#define SET_MST_RXC_FLAG	(masterRXC = 1)
#define WAIT_MST_RXC		while(masterRXC == 0){;}
// Tx
#define CLEAR_MST_TXC_FLAG	(masterTXC = 0)
#define SET_MST_TXC_FLAG	(masterTXC = 1)
#define WAIT_MST_TXC		while(masterTXC == 0){;}

static void i2c_master_rxc_callback(void *userdata)
{
    SET_MST_RXC_FLAG;
}
static void i2c_master_txc_callback(void *userdata)
{
    //printf("i2c_master_txc_callback\n\r");
    SET_MST_TXC_FLAG;
}
static int i2c_result = 0;
static void i2c_master_err_callback(void *userdata)
{
    SET_MST_RXC_FLAG;
    SET_MST_TXC_FLAG;
    printf("i2c_master_err_callback ERR:%x, tx_len: %x, rx_len: %x\n\r", i2c_master_sample.err_type, i2c_master_sample.tx_dat.len, i2c_master_sample.rx_dat.len);
    printf("i2c tx abrt source: %x\n\r", i2c_master_sample.init_dat.reg_base->I2C_TX_ABRT_SRC);
    printf("i2c txflr: %x\n\r", i2c_master_sample.init_dat.reg_base->I2C_TXFLR);
    i2c_result = ((i2c_master_sample.init_dat.reg_base->I2C_TX_ABRT_SRC&0xFFFF)<<16) | (i2c_master_sample.err_type &0xFFFF);
}

static int __rtscam_isp_i2c_transfer(struct rtscam_isp *isp, u8 slave_id,
				     u8 *buf, u16 len, u8 is_read)
{
#if 1
	i2c_result = 0;

	i2c_master_sample.usr_cb.txc.cb = i2c_master_txc_callback;
	i2c_master_sample.usr_cb.rxc.cb = i2c_master_rxc_callback;
	i2c_master_sample.usr_cb.err.cb = i2c_master_err_callback;

	if (is_read) {
		i2c_master_sample.rx_dat.addr = slave_id;
		i2c_master_sample.rx_dat.buf = buf;
		i2c_master_sample.rx_dat.len = len;
		i2c_master_sample.rx_dat.mst_stop = I2CEnable;
		CLEAR_MST_RXC_FLAG;
		hal_i2c_receive_simple(&i2c_master_sample);
		WAIT_MST_RXC;

	} else {

		i2c_master_sample.tx_dat.len = len;
		i2c_master_sample.tx_dat.buf = buf;
		i2c_master_sample.tx_dat.mst_stop = I2CEnable;
		i2c_master_sample.tx_dat.addr = slave_id;
		CLEAR_MST_TXC_FLAG;
		hal_i2c_send_simple(&i2c_master_sample);
		WAIT_MST_TXC;
	}

	return i2c_result;
#else
	int ret;
	struct i2c_msg msg;

	rtsprintk(RTS_TRACE_DEBUG, "i2c_xfer: 0x%02x %c %d\n", slave_id, is_read?'R':'W', len);
	//taskENTER_CRITICAL();
	//printf("i2c_xfer: 0x%02x %c 0x%08x %d\n", slave_id, is_read?'R':'W', (u32)buf, len);
	//taskEXIT_CRITICAL();

	msg.addr = slave_id;
	msg.flags = is_read ? I2C_M_RD : 0;
	msg.buf = buf;
	msg.len = len;
	//ret = i2c_dw_xfer(&msg, 1);
	//if (ret != 0) {
	//	rtsprintk(RTS_TRACE_ERROR, "i2c %#x transfer fail\n", slave_id);
	/* EGAIN is caused by snr soft reset(arbitration lost), we bypass it */
	if (ret != 1 && ret != -EAGAIN) {
		/* ignore error message during sensor detecting */
		if (isp->current_fps)
			rtsprintk(RTS_TRACE_ERROR,
				  "i2c %#x transfer fail\n", slave_id);
		return ret;
	}
	return 0;
#endif
}

static int __rtscam_isp_aphy_i2c_transfer(struct rtscam_isp *isp, u8 slave_id,
										  u8 *buf, u16 len, u8 is_read)
{
#if CONFIG_FPGA // FPGA

	i2c_master_aphy_sample.usr_cb.txc.cb = i2c_master_txc_callback;
	i2c_master_aphy_sample.usr_cb.rxc.cb = i2c_master_rxc_callback;
	i2c_master_aphy_sample.usr_cb.err.cb = i2c_master_err_callback;

	if (is_read) {
		i2c_master_aphy_sample.rx_dat.addr = slave_id;
		i2c_master_aphy_sample.rx_dat.buf = buf;
		i2c_master_aphy_sample.rx_dat.len = len;
		i2c_master_aphy_sample.rx_dat.mst_stop = I2CEnable;
		CLEAR_MST_RXC_FLAG;
		hal_i2c_receive_simple(&i2c_master_aphy_sample);
		WAIT_MST_RXC;

	} else {

		i2c_master_aphy_sample.tx_dat.len = len;
		i2c_master_aphy_sample.tx_dat.buf = buf;
		i2c_master_aphy_sample.tx_dat.mst_stop = I2CEnable;
		i2c_master_aphy_sample.tx_dat.addr = slave_id;
		CLEAR_MST_TXC_FLAG;
		hal_i2c_send_simple(&i2c_master_aphy_sample);
		WAIT_MST_TXC;
	}
#endif
	return 0;
}

static inline int __rtscam_isp_i2c_read(struct rtscam_isp *isp, u8 slave_id,
					u8 *buf, u16 len)
{
	return __rtscam_isp_i2c_transfer(isp, slave_id, buf, len, 1);
}

static inline int __rtscam_isp_i2c_write(struct rtscam_isp *isp, u8 slave_id,
					 u8 *buf, u16 len)
{
	return __rtscam_isp_i2c_transfer(isp, slave_id, buf, len, 0);
}

static inline int __rtscam_isp_aphy_i2c_write(struct rtscam_isp *isp, u8 slave_id,
										  u8 *buf, u16 len)
{
	return __rtscam_isp_aphy_i2c_transfer(isp, slave_id, buf, len, 0);
}

static int __rtscam_isp_set_clk_rate(struct rtscam_isp *isp,
				     int type, unsigned long *rate)
{
	struct clk_rlx *clk;

	if (!rate)
		return -EINVAL;

	switch (type) {
	case CLOCK_INTERFACE:
		clk = isp->inf_clk;
		break;
	//case CLOCK_ISP:
	//	clk = isp->isp_clk;
	//	*rate = isp->isp_clk_fix ? isp->isp_clk_fix : *rate;
	//	break;
	case CLOCK_MIPIOUT:
		clk = isp->mipiout_clk;
		break;
	case CLOCK_ISP:
		*rate = isp->isp_clk_fix ? isp->isp_clk_fix : *rate;
		return isp->mfd->change_clk_rate(isp->mfd, rate);
	default:
		return -EINVAL;
	}
	//isp_info("type %d inf_clk 0x%08x isp_clk 0x%08x  mipiout_clk 0x%08x \r\n", type, isp->inf_clk, isp->isp_clk, isp->mipiout_clk);
#ifdef _CLK_LOG_
	printf("type %d rate %d clk %d \r\n", type, *rate, clk->rate);
#endif
	if (*rate) {
		if (!isp->is_fpga) {
			clk_set_rate(clk, clk_round_rate(clk, *rate));
		}
		*rate = clk_get_rate(clk);
	}
	return 0;
}

/*
static void __rtscam_isp_subdev_ref_isp_clk(struct rtscam_isp *isp)
{
//	unsigned long rate = DEFAULT_ISP_CLK;
//
//	if (!isp->isp_clk_refcnt && !isp->isp_clk_subdev_refcnt)
//		__rtscam_isp_set_clk_rate(isp, CLOCK_ISP, &rate);
	isp->isp_clk_subdev_refcnt++;
//	clk_prepare_enable(isp->isp_clk);
}

static void __rtscam_isp_subdev_unref_isp_clk(struct rtscam_isp *isp)
{
	//WARN_ON(!isp->isp_clk_subdev_refcnt);
	isp->isp_clk_subdev_refcnt--;
//	if (!isp->isp_clk_subdev_refcnt)
//		clk_disable_unprepare(isp->isp_clk);
}
*/

static void __rtscam_isp_ref_clk(struct rtscam_isp *isp, int type)
{
	//unsigned long rate = DEFAULT_ISP_CLK;

	switch (type) {
	case CLOCK_INTERFACE:
		isp->inf_clk_refcnt++;
		clk_prepare_enable(isp->inf_clk);
		break;
	case CLOCK_ISP:
		isp->isp_clk_refcnt++;
		isp->mfd->set_clk(isp->mfd, 1);
		break;
	case CLOCK_MIPIOUT:
		isp->mipiout_clk_refcnt++;
		clk_prepare_enable(isp->mipiout_clk);
		break;
	}
}

static void __rtscam_isp_unref_clk(struct rtscam_isp *isp, int type)
{

	//printf("%s %d isp_clk_refcnt %d \r\n", __func__, type,  isp->isp_clk_refcnt);

	switch (type) {
	case CLOCK_INTERFACE:
		if (!isp->inf_clk_refcnt) rtsprintk(RTS_TRACE_ERROR, "inf_clk_refcnt==0\n");
		isp->inf_clk_refcnt--;
		clk_disable_unprepare(isp->inf_clk);
		break;
	case CLOCK_ISP:
		if (!isp->isp_clk_refcnt) rtsprintk(RTS_TRACE_ERROR, "isp_clk_refcnt==0\n");
		isp->isp_clk_refcnt--;
		isp->mfd->set_clk(isp->mfd, 0);
		break;
	case CLOCK_MIPIOUT:
		if (!isp->mipiout_clk_refcnt) rtsprintk(RTS_TRACE_ERROR, "mipiout_clk_refcnt==0\n");
		isp->mipiout_clk_refcnt--;
		clk_disable_unprepare(isp->mipiout_clk);
		break;
	}
}

static void __rtscam_isp_free_clk(struct rtscam_isp *isp)
{
	while (isp->inf_clk_refcnt)
		__rtscam_isp_unref_clk(isp, CLOCK_INTERFACE);
	while (isp->isp_clk_refcnt)
		__rtscam_isp_unref_clk(isp, CLOCK_ISP);
	while (isp->mipiout_clk_refcnt)
		__rtscam_isp_unref_clk(isp, CLOCK_MIPIOUT);
}

/*
static int __rtscam_isp_set_isp_clk(struct rtscam_isp *isp, int enable)
{
	if (!isp)
		return -EINVAL;

	if (enable)
		__rtscam_isp_subdev_ref_isp_clk(isp);
	else
		__rtscam_isp_subdev_unref_isp_clk(isp);

	return 0;
}

int rtscam_isp_set_isp_clock(int enable)
{
	return __rtscam_isp_set_isp_clk(m_isp, enable);
}
//EXPORT_SYMBOL_GPL(rtscam_isp_set_isp_clock);

int rtscam_isp_check_isp_clock(void)
{
	if (!m_isp)
		return 0;

	if (m_isp->current_fps)
		return 1;
	else
		return 0;
}
//EXPORT_SYMBOL_GPL(rtscam_isp_check_isp_clock);
*/

static int rtscam_isp_read_i2c_reg(struct rtscam_isp *isp,
				   const struct rts_isp_i2c_info *info,
				   struct rts_isp_i2c_reg *reg)
{
	int ret;
	u8 buf[2];

	if (!info || !reg)
		return -EINVAL;

	if (info->addr_len == 1) {
		buf[0] = reg->addr & 0xff;
	} else if (info->addr_len == 2) {
		buf[0] = reg->addr >> 8;
		buf[1] = reg->addr & 0xff;
	} else {
		return -EINVAL;
	}

	ret = __rtscam_isp_i2c_write(isp, info->i2c_id, buf, info->addr_len);
	if (ret)
		return ret;
	ret = __rtscam_isp_i2c_read(isp, info->i2c_id, buf, info->data_len);
	if (ret)
		return ret;

	if (info->data_len == 1)
		reg->data = buf[0];
	else
		reg->data = (buf[0] << 8) | buf[1];

	return 0;
}

static int rtscam_isp_write_i2c_reg(struct rtscam_isp *isp,
				    const struct rts_isp_i2c_info *info,
				    const struct rts_isp_i2c_reg *reg)
{
	int j = 0;
	u8 buf[4];

	if (info->addr_len == 1) {
		buf[j++] = reg->addr & 0xff;
	} else {
		buf[j++] = reg->addr >> 8;
		buf[j++] = reg->addr & 0xff;
	}
	if (info->data_len == 1) {
		buf[j++] = reg->data & 0xff;
	} else {
		buf[j++] = reg->data >> 8;
		buf[j++] = reg->data & 0xff;
	}
	//printf("I2C %02x %04x %04x \n", info->i2c_id, reg->addr, reg->data);
	return __rtscam_isp_i2c_write(isp, info->i2c_id, buf, j);
}

static int rtscam_isp_i2c_read(struct rtscam_isp *isp, void *args)
{
	u32 i;
	struct rts_isp_i2c *i2c = args;

	if (!isp || !args)
		return -EINVAL;

	if (!i2c || !i2c->num || i2c->num > ARRAY_SIZE(i2c->regs))
		return -EINVAL;

	if (!i2c->info.addr_len || i2c->info.addr_len > 2 ||
	    !i2c->info.data_len || i2c->info.data_len > 2)
		return -EINVAL;

if (DEBUG>2) printk("ioctl RTSISP_IOC_I2C_READ\n");
	for (i = 0; i < i2c->num; i++) {
		int ret;

		ret = rtscam_isp_read_i2c_reg(isp, &i2c->info, i2c->regs + i);
		if (ret)
			return ret;
	}

	return 0;
}

static int rtscam_isp_aphy_write_i2c_reg(struct rtscam_isp *isp,
				    const struct rts_isp_i2c_info *info,
				    const struct rts_isp_i2c_reg *reg)
{
	int j = 0;
	u8 buf[4];

	if (info->addr_len == 1) {
		buf[j++] = reg->addr & 0xff;
	} else {
		buf[j++] = reg->addr >> 8;
		buf[j++] = reg->addr & 0xff;
	}
	if (info->data_len == 1) {
		buf[j++] = reg->data & 0xff;
	} else {
		buf[j++] = reg->data >> 8;
		buf[j++] = reg->data & 0xff;
	}

	return __rtscam_isp_aphy_i2c_write(isp, info->i2c_id, buf, j);
}

static int rtscam_isp_i2c_write(struct rtscam_isp *isp, void *args)
{
	u32 i;
	struct rts_isp_i2c *i2c = args;

	if (!isp || !args)
		return -EINVAL;

	if (!i2c || !i2c->num || i2c->num > ARRAY_SIZE(i2c->regs))
		return -EINVAL;

	if (!i2c->info.addr_len || i2c->info.addr_len > 2 ||
	    !i2c->info.data_len || i2c->info.data_len > 2)
		return -EINVAL;

if (DEBUG>2) printk("ioctl RTSISP_IOC_I2C_WRITE\n");
	for (i = 0; i < i2c->num; i++) {
		int ret;

		ret = rtscam_isp_write_i2c_reg(isp, &i2c->info, i2c->regs + i);
		if (ret)
			return ret;
	}

	return 0;
}

static int rtscam_isp_aphy_i2c_write(struct rtscam_isp *isp, void *args)
{
	u32 i;
	struct rts_isp_i2c *i2c = args;

	if (!isp || !args)
		return -EINVAL;

	if (!i2c || !i2c->num || i2c->num > ARRAY_SIZE(i2c->regs))
		return -EINVAL;

	if (!i2c->info.addr_len || i2c->info.addr_len > 2 ||
	    !i2c->info.data_len || i2c->info.data_len > 2)
		return -EINVAL;

	for (i = 0; i < i2c->num; i++) {
		int ret;

		ret = rtscam_isp_aphy_write_i2c_reg(isp, &i2c->info, i2c->regs + i);
		if (ret)
			return ret;
	}

	return 0;
}

static int __rtscam_isp_set_fps(struct rtscam_isp *isp, u16 fps)
{
	int ret = 0;
	int fps_backup;
	struct rts_isp_preview_info info;

	if (!isp)
		return -EINVAL;

	if (isp->current_fps == fps)
		return 0;

	if (isp->current_fps == 0) {
		atomic_set_isp(&isp->frame_count, 0);
		atomic_set_isp(&isp->statis_count, 0);
	}
	info.fps = fps;

	__rtscam_isp_ref_clk(isp, CLOCK_ISP);
	fps_backup = isp->current_fps;
	if (fps)
		isp->current_fps = fps;
	else
		isp->stopping = TRUE;

	ret = rtscam_isp_message_call(&isp->message, 0, RTS_ISP_SET_FPS,
				      &info, sizeof(info));
	if (ret) {
		isp->current_fps = fps_backup;
		isp_error("%s rtscam_isp_message_call %d \r\n",__FUNCTION__, ret);
		goto out;
	}

	if (!fps) {
		rtscam_isp_sync_cleanup(&isp->sync);
		isp->current_fps = fps;
		isp->stopping = FALSE;
		isp->data_start_done = FALSE;
	}


out:
	//printf("%s before __rtscam_isp_unref_clk \r\n",__func__);
	__rtscam_isp_unref_clk(isp, CLOCK_ISP);
	return ret;
}

static int rtscam_isp_subdev_set_fps(struct rtscam_zoom_isp *zoom_isp, int fps)
{
	int ret = 0;
	//int fps_backup;
	struct rtscam_isp *isp;
	//struct rts_isp_preview_info info;

	if (!zoom_isp)
		return -EINVAL;

if (DEBUG>2) printk("%s: fps:%d\n", __func__, fps);

	isp = container_of(zoom_isp, struct rtscam_isp, zoom_isp);

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_subdev_set_fps wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}
/*	if (isp->current_fps == fps) {
		osMutexRelease(isp->lock);
		return ret;
	}
	if (isp->current_fps == 0) {
		atomic_set(&isp->frame_count, 0);
		atomic_set(&isp->statis_count, 0);
	}
	info.fps = fps;

	__rtscam_isp_ref_clk(isp, CLOCK_ISP);  //enable clock if reference count > 0
	fps_backup = isp->current_fps;
	if (fps)
		isp->current_fps = fps;

	ret = rtscam_isp_message_call(&isp->message, 0, RTS_ISP_SET_FPS,
				      &info, sizeof(info));
	if (ret) {
		isp->current_fps = fps_backup;
		goto out;
	}

	if (!fps) {
		rtscam_isp_sync_cleanup(&isp->sync);
		isp->current_fps = fps;
	}
	ret = __rtscam_isp_set_fps(isp, fps);
out:
	__rtscam_isp_unref_clk(isp, CLOCK_ISP);
*/
#ifdef _FPS_LOG_
	printf("%s __rtscam_isp_set_fps %d \r\n",__FUNCTION__, fps);
#endif
	ret = __rtscam_isp_set_fps(isp, fps);
	//osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);
	return ret;
}

static int rtscam_isp_subdev_set_mcrop(struct rtscam_zoom_isp *zoom_isp,
				       const struct rtsv_rect *crop)
{
	struct rtscam_isp *isp;

	if (!zoom_isp)
		return -EINVAL;

	isp = container_of(zoom_isp, struct rtscam_isp, zoom_isp);

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE)
		return -ERESTARTSYS;

	rtscam_isp_write_reg(isp, crop->left, MCROP_START_X);
	rtscam_isp_write_reg(isp, crop->top, MCROP_START_Y);
	rtscam_isp_write_reg(isp, crop->width, MCROP_FRAME_WIDTH);
	rtscam_isp_write_reg(isp, crop->height, MCROP_FRAME_HEIGHT);
	rtscam_isp_write_reg(isp, 1, MCROP_REG_LOAD);

	xSemaphoreGive(isp->lock);
	return 0;
}

static int rtscam_isp_subdev_set_hook(struct rtscam_zoom_isp *zoom_isp,
		void *master, int (*hook)(void *master, int id, void *arg))
{
	struct rtscam_isp *isp;

	if (!zoom_isp)
		return -EINVAL;

if (DEBUG>2) printf("%s: hook:0x%08x\n", __func__, (int)hook);

	isp = container_of(zoom_isp, struct rtscam_isp, zoom_isp);
	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_subdev_set_hook wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	isp->hook = hook;

//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);

	return 0;
}

/*
static int rtscam_isp_subdev_set_clock(
		struct rtscam_zoom_isp *zoom_isp, int enable)
{
	struct rtscam_isp *isp;

	if (!zoom_isp)
		return -EINVAL;

if (DEBUG>2) printk("%s: en:%d\n", __func__, enable);

	isp = container_of(zoom_isp, struct rtscam_isp, zoom_isp);

	return __rtscam_isp_set_isp_clk(isp, enable);
}
*/

static int rtscam_isp_register_subdev(struct rtscam_isp *isp, void *args)
{
	int ret;
	struct rtscam_zoom_isp *zoom_isp = &isp->zoom_isp;

	if (zoom_isp->master) {
		//osMutexRelease(isp->lock);
		xSemaphoreGive(isp->lock);

		ret = rtscam_zoom_unregister_isp(zoom_isp);
		if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
			isp_error("rtscam_isp_register_subdev wait isp->lock timeout\n\r");
			return -ERESTARTSYS;
		}
		if (ret)
			return -EBUSY;
	}

if (DEBUG>2) printf("ioctl RTSISP_IOC_REG_SUBDEV\n");
	memset(zoom_isp, 0, sizeof(*zoom_isp));
	//zoom_isp->dev = isp->dev;
	zoom_isp->info = *(struct rts_isp_info *)args;
	zoom_isp->set_fps = rtscam_isp_subdev_set_fps;
	zoom_isp->set_mcrop = rtscam_isp_subdev_set_mcrop;
	zoom_isp->set_hook = rtscam_isp_subdev_set_hook;
	//zoom_isp->set_clock = rtscam_isp_subdev_set_clock;

	//return rtscam_zoom_register_isp(&isp->zoom_isp);
//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);

	ret = rtscam_zoom_register_isp(&isp->zoom_isp);
	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_register_subdev xSemaphoreTake fail\n\r");
		return -ERESTARTSYS;
	}

	return ret;
}

static int rtscam_isp_unregister_subdev(struct rtscam_isp *isp, void *args)
{
	int ret;
	struct rtscam_zoom_isp *zoom_isp = &isp->zoom_isp;

	if (!zoom_isp->master)
		return 0;

if (DEBUG>2) printk("ioctl RTSISP_IOC_UNREG_SUBDEV\n");
	//return rtscam_zoom_unregister_isp(zoom_isp);
//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);

	ret = rtscam_zoom_unregister_isp(zoom_isp);
	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_unregister_subdev wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	return ret;
}

static int rtscam_isp_sync_write(struct rtscam_isp *isp, void *args)
{
	//int ret;
	struct rts_isp_sync_regs *regs = args;

	if (!isp || !args)
		return -EINVAL;

if (DEBUG>2) printf("ioctl RTSISP_IOC_SYNC_WRITE\n");
	//ret = rtscam_isp_sync_add_regs(&isp->sync, regs);
	///* wake up irq thread to write exposure reg earlier */
	//if (!ret)
	//	//irq_wake_thread(isp->irq, isp);
	//	osSemaphoreRelease(isptaskSemaphore);  //wake rtscam_isp_irq_thread()
	//return ret;
	return rtscam_isp_sync_add_regs(&isp->sync, regs);
}

static int rtscam_isp_init_statis(struct rtscam_isp *isp, void *args)
{
	int ret;
	struct rtscam_isp_statis_node *node;

	ret = rtscam_isp_statis_init(&isp->statis, *(u32 *)args);
	if (ret) {
		isp_error("%s rtscam_isp_statis_init %d \r\n", __FUNCTION__, ret);
		return ret;
	}

if (DEBUG>2) printf("ioctl RTSISP_IOC_INIT_STATIS\n");
	node = list_first_entry(&isp->statis.busy,
				struct rtscam_isp_statis_node, list);
#ifdef __DEBUG_STATIS__
	printf("%s node to HW 0x%08x addr 0x%08x size %d \r\n", __FUNCTION__, &(node->list), node->addr, isp->statis.info.size);
#endif
	rtscam_isp_write_reg(isp, (u32)node->addr, STATIS_DDR_ADDR);
	rtscam_isp_write_reg(isp, isp->statis.info.size, STATIS_DDR_LEN);
	statis_cnt = 0;
	return 0;
}

static int rtscam_isp_cleanup_statis(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printf("ioctl RTSISP_IOC_CLEANUP_STATIS\n");
	return rtscam_isp_statis_cleanup(&isp->statis);
}

static int rtscam_isp_get_statis_info(struct rtscam_isp *isp, void *args)
{
	if (!isp || !args)
		return -EINVAL;

if (DEBUG>2) printf("ioctl RTSISP_IOC_GET_STATIS_INFO\n");
	*(struct rts_isp_statis_info *)args = isp->statis.info;
	return 0;
}

static int rtscam_isp_put_statis(struct rtscam_isp *isp, void *args)
{
/* No use cause SW ARCH changed.
	u32 id;
	//unsigned long flags;
	struct rtscam_isp_statis *statis;
	struct rtscam_isp_statis_node *node;

	if (!isp || !args)
		return -EINVAL;

if (DEBUG>2) printf("ioctl RTSISP_IOC_PUT_STATIS\n");
	id = *(u32 *)args;
	statis = &isp->statis;

	//spin_lock_irqsave(&statis->lock, flags);
	xSemaphoreTake(statis->lock, portMAX_DELAY);
	node = __rtscam_isp_statis_get_node(statis, &statis->user, id);
	if (!node) {
		rtsprintk(RTS_TRACE_ERROR, "invalid put statis buf %u\n", id);
		//spin_unlock_irqrestore(&isp->statis.lock, flags);
		osMutexRelease(statis->lock);
		return -ENOENT;
	}
	list_del(&node->list);
	//spin_unlock_irqrestore(&statis->lock, flags);
	osMutexRelease(statis->lock);

	//mark as DMA-able from HW
	//dma_sync_single_range_for_device(statis->dev, statis->info.phy_addr,
	//				 node->addr - statis->info.phy_addr,
	//				 statis->info.size, DMA_FROM_DEVICE);

	//spin_lock_irqsave(&statis->lock, flags);
	xSemaphoreTake(statis->lock, portMAX_DELAY);
	list_add_tail(&node->list, &statis->idle);  //put to idle
	//spin_unlock_irqrestore(&statis->lock, flags);
	osMutexRelease(statis->lock);
*/

	return 0;
}

static int rtscam_isp_mem_alloc(struct rtscam_isp *isp, void *args)
{
	struct rtscam_isp_mem_alloc_info *info = args;
	struct rtscam_isp_mem_item *item;

#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif
//asm("sdbbp");

	item = rts_malloc(sizeof(*item));
	if (!item)
		return -ENOMEM;
if (DEBUG>2) printf("ioctl RTSISP_IOC_MEM_ALLOC\n");
	item->virt_addr = rtscam_mem_alloc(info->length,
				     (void **)&info->phy_addr,
				     5);  //Cache line size 2^5 bytes aligned
	//info->phy_addr = (((__u32)virt_addr+0x0FF) & 0x0FF) & ~0x80000000;
	if (!item->virt_addr) {
		printf("rtscam_isp_mem_alloc alloc buffer fail\n");
#ifdef _DEBUG_MEM_
		isp_info("%s rts_free 0x%08x \r\n", __func__, item);
#endif
		rts_free(item);
		return -ENOMEM;
	}
	//rtscam_mem_add_property(info->phy_addr,
	//			RTSMEM_PROBE_ALLOCATED);

	INIT_LIST_HEAD(&item->list);
	item->phy_addr = (void*)info->phy_addr;
	item->size = info->length;
	list_add_tail(&item->list, &isp->mem_list);

#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("rtscam_isp_mem_alloc alloc %d heap_used %d heap %d \n", sizeof(*item), heap_before-heap_after, heap_after);
#endif
	return 0;
}

static int rtscam_isp_mem_free(struct rtscam_isp *isp, void *args)
{
	void *phy_addr;
	struct rtscam_isp_mem_item *item;
	struct rtscam_isp_mem_item *next;
#if defined(_DEBUG_MEM_USEAGE_)
	int heap_before, heap_after;
	heap_before = xPortGetFreeHeapSizeExt(0);
#endif

//asm("sdbbp");
if (DEBUG>2) printf("ioctl RTSISP_IOC_MEM_FREE\n");
	phy_addr = (void*)*(__u32 *)args;
	list_for_each_entry_safe(item, next, &isp->mem_list, list, struct rtscam_isp_mem_item) {
		if (item->phy_addr == phy_addr) {
			list_del(&item->list);
#ifdef _DEBUG_MEM_
			isp_info("%s rts_free 0x%08x 0x%08x \r\n", __func__, item->virt_addr, item);
#endif
			rts_free(item->virt_addr);
			rts_free(item);
			break;
		}
	}
#if defined(_DEBUG_MEM_USEAGE_)
	heap_after = xPortGetFreeHeapSizeExt(0);
	printf("rtscam_isp_mem_free free 0x%08x heap_free %d heap %d \n", item->virt_addr, heap_after-heap_before, heap_after);
#endif


//	rtscam_mem_free_V2(isp->mem_info, phy_addr);
	return 0;
}

static int rtscam_isp_sel_pin_state(struct rtscam_isp *isp, void *args)
{
	int ret = RTS_OK;
	enum rtscam_isp_pin_state state;

	state = *(enum rtscam_isp_pin_state *)args;
	switch (state) {
	case PIN_STATE_NONE:
if (DEBUG>2) printf("ioctl RTSISP_IOC_SEL_PIN_STATE PIN_STATE_NONE\n");
		ret = RTS_OK;
		break;
	case PIN_STATE_DVP:
if (DEBUG>2) printf("ioctl RTSISP_IOC_SEL_PIN_STATE PIN_STATE_DVP\n");
		//ret = rts_pinmux_enable_setting("ssorfunc", "dvpgrp");
		break;
	case PIN_STATE_MIPI:
if (DEBUG>2) printf("ioctl RTSISP_IOC_SEL_PIN_STATE PIN_STATE_MIPI\n");
		//ret = rts_pinmux_enable_setting("ssorfunc", "mipigrp");
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}

static int rtscam_isp_notify_dyn_fps(struct rtscam_isp *isp, void *args)
{
	int ret = 0;

//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);

if (DEBUG>2) printf("ioctl RTSISP_IOC_NOTIFY_DYN_FPS\n");
	if (isp->hook)
		ret = isp->hook(isp->zoom_isp.master,
				 RTSCAM_EVT_FPS_DYNAMIC_CHANGED, args);

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_notify_dyn_fps wait isp->lock fail\n\r");
		return -ERESTARTSYS;
	}

	return ret;
}

static int rtscam_isp_get_isp_clock(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printf("ioctl RTSISP_IOC_GET_ISP_CLOCK\n");
	__rtscam_isp_ref_clk(isp, CLOCK_ISP);
	return 0;
}

static int rtscam_isp_put_isp_clock(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printf("ioctl RTSISP_IOC_PUT_ISP_CLOCK\n");
	__rtscam_isp_unref_clk(isp, CLOCK_ISP);
	return 0;
}

static int rtscam_isp_set_clock(struct rtscam_isp *isp, void *args)
{
	int ret;
	struct rtscam_isp_clock *clk = args;

if (DEBUG>2) printf("ioctl RTSISP_IOC_SET_CLOCK\n");
	if (clk->rate) {
		if (clk->rate != 1) {
			ret = __rtscam_isp_set_clk_rate(isp, clk->type,
			      &clk->rate);
			if (ret)
				return ret;
		}
		__rtscam_isp_ref_clk(isp, clk->type);
	} else {
		__rtscam_isp_unref_clk(isp, clk->type);
	}

	return 0;
}

static int rtscam_isp_is_fpga(struct rtscam_isp *isp, void *args)
{
if (DEBUG>2) printf("ioctl RTSISP_IOC_IS_FPGA\n");
	*(__s32 *)args = isp->is_fpga;
	return 0;
}

static int rtscam_isp_wait_event(struct rtscam_isp *isp, void *args)
{
	enum rtscam_isp_event event;
	u32 timeout = isp->message.timeout / 4;
	int ret = 0;

	event = (enum rtscam_isp_event)*(__s32 *)args;
	switch (event) {
	case RTSCAM_ISP_DATA_START:
if (DEBUG>2) isp_info("ioctl RTSISP_IOC_WAIT_EVENT RTSCAM_ISP_DATA_START\r\n");
		//reinit_completion(&isp->data_start_completion);
		//wait_for_completion_timeout(&isp->data_start_completion,
		//			    timeout);
		// Reset the semaphore to zero to actually wait the IRQ event
		while (xSemaphoreTake(isp->data_start_completion, 0) != pdFALSE)
			;
//		ret = osSemaphoreAcquire(isp->data_start_completion, timeout*portTICK_RATE_MS);
//		if ( ret != osOK) {
		if (xSemaphoreTake(isp->data_start_completion, timeout) != pdTRUE ) {
			printf("data_start_completion wait semaphore ret = %d timeout %d \n", ret, timeout);
		}
		return ret;
	case RTSCAM_ISP_FRAME_END:
if (DEBUG>2) isp_info("ioctl RTSISP_IOC_WAIT_EVENT RTSCAM_ISP_FRAME_END\r\n");
		//reinit_completion(&isp->frame_end_completion);
		//wait_for_completion_timeout(&isp->frame_end_completion,
		//			    timeout);
		// Reset the semaphore to zero to actually wait the IRQ event
		while (xSemaphoreTake(isp->frame_end_completion, 0) != pdFALSE)
			;
//		ret = osSemaphoreAcquire(isp->frame_end_completion, timeout*portTICK_RATE_MS);
//		if ( ret != osOK) {
		if (xSemaphoreTake(isp->frame_end_completion, timeout) != pdTRUE ) {
			printf("frame_end_completion wait semaphore ret = %d timeout %d \n", ret, timeout);
		}
		return ret;
	default:
		return -EINVAL;
	}
}

static int rtscam_isp_sync_lock(struct rtscam_isp *isp, void *args)
{
	__s32 lock = *(__s32 *)args;
	int ret = 0;

if (DEBUG>2) isp_info("ioctl RTSISP_IOC_SYNC_LOCK lock:%d\r\n", lock);
	if (lock) {
		ret = xSemaphoreTake(isp->sync.lock, ISP_SEM_TIMEOUT);
		if (ret != pdTRUE) {
			isp_error("rtscam_isp_sync_lock wait isp->sync.lock timeout\n\r");
			ret = -ETIMEDOUT;
		}
	}
	else
		//osMutexRelease(isp->sync.lock);
		xSemaphoreGive(isp->sync.lock);

	return ret;
}

static int rtscam_isp_test_preview(struct rtscam_isp *isp, void *args)
{
	return __rtscam_isp_set_fps(isp, *(__u32 *)args);
}

static int rtscam_isp_get_tnr_bit(struct rtscam_isp *isp, void *args)
{
	*(__u32 *)args = isp->tnr_bit;
	return 0;
}

static int rtscam_isp_poll(struct rtscam_isp *isp, void *args)
{
	unsigned int mask = 0;
	unsigned long timeout = (unsigned long)args;

	//poll_wait(filp, &isp->message.wq);  //enq to wq only, not wait event
	if (timeout != osWaitForever)
		timeout = timeout * portTICK_RATE_MS;

	//osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);

//	if (osSemaphoreAcquire(isp->message.wq, timeout)) {
	if (xSemaphoreTake(isp->message.wq, timeout) != pdTRUE ) {

		isp_error("rtscam_isp_poll wait isp->message.wq timeout\n\r");
		return -ERESTARTSYS;
	}
	if (xSemaphoreTake(isp->lock, timeout) != pdTRUE) {
		isp_error("rtscam_isp_poll wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	isp_info("%s read %d write %d\r\n", __func__, rtscam_isp_message_can_read(&isp->message), rtscam_isp_message_can_write(&isp->message));
//asm("sdbbp");
	if (rtscam_isp_message_can_read(&isp->message) ||
	    rtscam_isp_statis_valid(&isp->statis))
		mask |= POLLIN | POLLRDNORM;

	if (rtscam_isp_message_can_write(&isp->message))
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}

static struct rtscam_isp_ioctl_info rtscam_isp_ioctl_infos[] = {
	ISP_IOCTL_INFO(RTSISP_IOC_GET_IO_START, rtscam_isp_get_io_start),
	ISP_IOCTL_INFO(RTSISP_IOC_GET_IO_SIZE, rtscam_isp_get_io_size),
	ISP_IOCTL_INFO(RTSISP_IOC_POWER, rtscam_isp_set_power),
	ISP_IOCTL_INFO(RTSISP_IOC_I2C_READ, rtscam_isp_i2c_read),
	ISP_IOCTL_INFO(RTSISP_IOC_I2C_WRITE, rtscam_isp_i2c_write),
	ISP_IOCTL_INFO(RTSISP_IOC_REG_SUBDEV, rtscam_isp_register_subdev),
	ISP_IOCTL_INFO(RTSISP_IOC_UNREG_SUBDEV, rtscam_isp_unregister_subdev),
	ISP_IOCTL_INFO(RTSISP_IOC_SYNC_WRITE, rtscam_isp_sync_write),
	ISP_IOCTL_INFO(RTSISP_IOC_INIT_STATIS, rtscam_isp_init_statis),
	ISP_IOCTL_INFO(RTSISP_IOC_CLEANUP_STATIS, rtscam_isp_cleanup_statis),
	ISP_IOCTL_INFO(RTSISP_IOC_GET_STATIS_INFO, rtscam_isp_get_statis_info),
	ISP_IOCTL_INFO(RTSISP_IOC_PUT_STATIS, rtscam_isp_put_statis),
	ISP_IOCTL_INFO(RTSISP_IOC_MEM_ALLOC, rtscam_isp_mem_alloc),
	ISP_IOCTL_INFO(RTSISP_IOC_MEM_FREE, rtscam_isp_mem_free),
	ISP_IOCTL_INFO(RTSISP_IOC_SEL_PIN_STATE, rtscam_isp_sel_pin_state),
	ISP_IOCTL_INFO(RTSISP_IOC_NOTIFY_DYN_FPS, rtscam_isp_notify_dyn_fps),
	ISP_IOCTL_INFO(RTSISP_IOC_GET_ISP_CLOCK, rtscam_isp_get_isp_clock),
	ISP_IOCTL_INFO(RTSISP_IOC_PUT_ISP_CLOCK, rtscam_isp_put_isp_clock),
	ISP_IOCTL_INFO(RTSISP_IOC_SET_CLOCK, rtscam_isp_set_clock),
	ISP_IOCTL_INFO(RTSISP_IOC_IS_FPGA, rtscam_isp_is_fpga),
	ISP_IOCTL_INFO(RTSISP_IOC_WAIT_EVENT, rtscam_isp_wait_event),
	ISP_IOCTL_INFO(RTSISP_IOC_SYNC_LOCK, rtscam_isp_sync_lock),
	ISP_IOCTL_INFO(RTSISP_IOC_TEST_PREVIEW, rtscam_isp_test_preview),
	ISP_IOCTL_INFO(RTSISP_IOC_GET_TNR_BIT, rtscam_isp_get_tnr_bit),

	ISP_IOCTL_INFO(RTSISP_IOC_POLL, rtscam_isp_poll),
	ISP_IOCTL_INFO(RTSISP_IOC_APHY_I2C_WRITE, rtscam_isp_aphy_i2c_write),


};

static int rtscam_isp_reset_device(struct rtscam_isp *isp)
{
/*	int ret;

	ret = isp->mfd->reset(isp->mfd);
	if (ret)
		goto exit;

	ret = reset_control_reset(isp->mipi_reset);
	if (ret)
		goto exit;
	ret = reset_control_deassert(isp->mipiout_reset);
	if (ret)
		goto exit;

exit:
	return ret;
*/
	rts_sys_force_reset(FORCE_RESET_ISP);
	udelay(1);
	rts_sys_force_reset(FORCE_RESET_MIPI);
	udelay(1);
	//rts_sys_reset_deassert(FORCE_RESET_MIPI_TX);
	//udelay(1);

	return RTS_OK;
}

static void rtscam_isp_assert_device(struct rtscam_isp *isp)
{
	//reset_control_assert(isp->mipiout_reset);
	rts_sys_reset_assert(FORCE_RESET_MIPI_TX);
	udelay(1);
}

static int rtscam_isp_config_buffer(struct rtscam_isp *isp)
{
	u32 value;

	value = isp->tnr_cfg.base | isp->tnr_cfg.size << 16;
	rtscam_isp_write_reg(isp, value, TNR_STREAM_BUF_CFG);
	//printf("%s tnr base %x size %x set_value 0x%08x \r\n", __func__, isp->tnr_cfg.base, isp->tnr_cfg.size, value);

	value = isp->statis_cfg.base << 16 | isp->statis_cfg.size;
	rtscam_isp_write_reg(isp, value, STATIS_BUF_SIZE);
	//printf("%s statis base %x size %x set_value 0x%08x \r\n", __func__, isp->statis_cfg.base, isp->statis_cfg.size, value);

	return 0;
}

static void rtscam_isp_memories_release(struct rtscam_isp *isp)
{
	struct rtscam_isp_mem_item *item;
	struct rtscam_isp_mem_item *next;

	list_for_each_entry_safe(item, next, &isp->mem_list, list, struct rtscam_isp_mem_item) {

		list_del(&item->list);
#ifdef _DEBUG_MEM_
		isp_info("%s rts_free 0x%08x 0x%08x \r\n", __func__, item->phy_addr, item);
#endif
		rts_free(item->phy_addr);
		rts_free(item);
	}
}


ssize_t get_msg_timeout(char *buf)
{
	struct rtscam_isp *isp = &gbl_isp;

	return sprintf(buf, "%ld\n", isp->message.timeout);
}
ssize_t set_msg_timeout(const char *buf, size_t count)
{
	u32 timeout;
	struct rtscam_isp *isp = &gbl_isp;

	if (strtol_base10(buf, (int *)&timeout))
		return -EINVAL;

	isp->message.timeout = clamp_t(u32, timeout, 100, 10000);
	return count;
}
//static DEVICE_ATTR(msg_timeout, 0644, get_msg_timeout, set_msg_timeout);

ssize_t get_fix_clk(char *buf)
{
	struct rtscam_isp *isp = &gbl_isp;

	sprintf(buf, "%ld\n", isp->isp_clk_fix);
	return strlen(buf);
}

ssize_t set_fix_clk(const char *buf, int count)
{
	struct rtscam_isp *isp = &gbl_isp;

	if (strtol_base10(buf, (int *)&isp->isp_clk_fix))
		return -EINVAL;
	return count;
}
//static DEVICE_ATTR(fix_clk, 0644, get_fix_clk, set_fix_clk);

ssize_t show_frame_count(char *buf)
{
	size_t size = 0;
	struct rtscam_isp *isp = &gbl_isp;

	size += sprintf(buf + size,
			  "frame count     statis count\n");
	size += sprintf(buf + size, "%-15u %-15u\n",
			  atomic_read_isp(&isp->frame_count),
			  atomic_read_isp(&isp->statis_count));
	return size;
}

//static DEVICE_ATTR(frame_count, 0444, show_frame_count, NULL);

static void __rtscam_isp_force_stop_preview(struct rtscam_isp *isp)
{
	enum rtscam_isp_event event = RTSCAM_ISP_DATA_START;

	if (!isp->current_fps)
		return;
	printf("%s\r\n", __func__);
	/* stop tnr */
	rtscam_isp_write_reg(isp, 0xe, TNR_CTRL);
	/* stop statis */
	rtscam_isp_write_reg(isp, 0x2, SYS_STATIS_CTRL);
	/* data disable */
	rtscam_isp_write_reg(isp, 0x0, SYS_DATA_DELAY);
	/* wait 2 data start */
	rtscam_isp_wait_event(isp, &event);
	rtscam_isp_wait_event(isp, &event);
	/* stop isp */
	rtscam_isp_write_reg(isp, 0x0, SYS_INT_EN0);
	rtscam_isp_write_reg(isp, 0xffffffff, SYS_INT_FLAG0);
	rtscam_isp_write_reg(isp, 0x2, SYS_CONTROL0);

	isp->current_fps = 0;
}

int rtscam_isp_open(void)
{
	int ret = 0;
	//struct rtscam_ge_device *gdev = rtscam_devdata(filp);
	struct rtscam_isp *isp = &gbl_isp;  //rtscam_ge_get_drvdata(gdev);

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_open wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}

	isp_info("%s 0x%08x 0x%08x 0x%08x \r\n", &(gbl_isp.sync), &(gbl_isp.mem_list), &(gbl_isp.sync.idle));




	__rtscam_isp_ref_clk(isp, CLOCK_ISP);
	if (atomic_inc_return_isp(&isp->user_count) == 1) {
	//if ((isp->user_count++) == 1) {
		ret = rtscam_isp_message_reinit(&isp->message);
		if (ret)
			goto out;
		ret = rtscam_isp_reset_device(isp);
		if (ret)
			goto out;
		ret = rtscam_isp_config_buffer(isp);
		if (ret)
			goto out;
	}

	//filp->private_data = isp;

out:
	if (ret)
		atomic_dec_isp(&isp->user_count);
	__rtscam_isp_unref_clk(isp, CLOCK_ISP);
	//osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);
	return ret;
}

int rtscam_isp_close(void)
{
	struct rtscam_isp *isp = &gbl_isp;

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_close wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}

if (DEBUG>2) isp_info("%s\r\n", __func__);

	if (atomic_dec_return_isp(&isp->user_count) == 0) {
		u32 i;

		__rtscam_isp_force_stop_preview(isp);
		rtscam_isp_assert_device(isp);
		for (i = 0; i < ARRAY_SIZE(isp->power); i++)
			rtscam_isp_snr_power_put(isp, &isp->power[i]);
		rtscam_isp_statis_cleanup(&isp->statis);
		rtscam_isp_memories_release(isp);
		__rtscam_isp_free_clk(isp);
	}

	//osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);
	//filp->private_data = NULL;

	return 0;
}

int rtscam_isp_read(char *buf,
			       int size, int *offset)
{
	int ret;
	struct rtscam_isp *isp = &gbl_isp;

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_read wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	if (rtscam_isp_message_can_read(&isp->message) &&
	    !rtscam_isp_statis_read_partial(&isp->statis))
		ret = rtscam_isp_message_read(&isp->message, buf, size);
	else if (rtscam_isp_statis_valid(&isp->statis))
		ret = rtscam_isp_statis_read(&isp->statis, buf, size);
	else
		ret = -EAGAIN;
if (DEBUG>2) isp_info("%s sz:%d off:%x\r\n", __func__, ret, (int)offset);

//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);
	return ret;
}
#if 0
int rtscam_isp_write(const char *buf,
				int size, int *offset)
{
	int ret;
	struct rtscam_isp *isp = &gbl_isp;

if (DEBUG>2) isp_info("%s sz:%d off:%x\r\n", __func__, size, (int)offset);

	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_write wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	ret = rtscam_isp_message_write(&isp->message, buf, size);
	osMutexRelease(isp->lock);

	return ret;
}
#endif
static long rtscam_isp_do_ioctl(unsigned int cmd, void *arg)
{
	int ret;
	struct rtscam_isp *isp = &gbl_isp;

	if (_IOC_NR(cmd) > ARRAY_SIZE(rtscam_isp_ioctl_infos))
		return -ENOTTY;
	if (cmd != rtscam_isp_ioctl_infos[_IOC_NR(cmd)].cmd)
		return -ENOTTY;
	if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_do_ioctl wait isp->lock timeout\n\r");
		return -ERESTARTSYS;
	}
	__rtscam_isp_ref_clk(isp, CLOCK_ISP);
	ret = rtscam_isp_ioctl_infos[_IOC_NR(cmd)].func(isp, arg);
	__rtscam_isp_unref_clk(isp, CLOCK_ISP);
//	osMutexRelease(isp->lock);
	xSemaphoreGive(isp->lock);
	return ret;
}

long rtscam_isp_ioctl(unsigned int cmd,
			     unsigned long arg)
{
	return rtscam_isp_do_ioctl(cmd, (void*)arg);
}

/*
static unsigned int rtscam_isp_poll(struct file *filp,
				    struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	struct rtscam_isp *isp = filp->private_data;
	unsigned long req_events = poll_requested_events(wait);

	if (!(req_events & (POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM)))
		return mask;

if (DEBUG>2) printk("%s enq wait %x\n", __func__, (u32)req_events);

	poll_wait(filp, &isp->message.wq, wait);  //enq evt, not really wait
//asm("sdbbp");

	if (rtscam_isp_message_can_read(&isp->message) ||
	    rtscam_isp_statis_valid(&isp->statis))
		mask |= POLLIN | POLLRDNORM;

	if (rtscam_isp_message_can_write(&isp->message))
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}

static bool __is_rtscam_isp_regs(struct rtscam_isp *isp,
				 dma_addr_t phy_addr, size_t size)
{
	//return phy_addr == isp->io_start && size == PAGE_ALIGN(isp->io_size);
	return phy_addr == isp->res.io_start &&
			size == PAGE_ALIGN(isp->res.io_size);
}

static bool __is_rtscam_isp_allocated(struct rtscam_isp *isp,
				      dma_addr_t phy_addr, size_t size)
{
	struct rtscam_isp_mem_item *item;

	list_for_each_entry(item, &isp->mem_list, list, struct rtscam_isp_mem_item)
		if (phy_addr == item->phy_addr &&
		    size == PAGE_ALIGN(item->size))
			return TRUE;
	return FALSE;
}

int rtscam_isp_mmap(struct vm_area_struct *vma)
{
	int ret;
	size_t size;
	off_t phy_addr;
	struct rtscam_isp *isp = &gbl_isp;

	phy_addr = vma->vm_pgoff << PAGE_SHIFT;
	size = vma->vm_end - vma->vm_start;

	if (xSemaphoreTake(isp->lock, portMAX_DELAY))
		return -ERESTARTSYS;
	if (__is_rtscam_isp_regs(isp, phy_addr, size) ||
	    __is_rtscam_isp_allocated(isp, phy_addr, size)) {
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		ret = remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				      size, vma->vm_page_prot);
	} else if (phy_addr == isp->statis.info.phy_addr &&
	    size == PAGE_ALIGN(isp->statis.info.num * isp->statis.info.size)) {
		ret = remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				      size, vma->vm_page_prot);
	} else {
		ret = -EPERM;
	}
	osMutexRelease(isp->lock);
	if (ret)
		rtsprintk(RTS_TRACE_ERROR,
			  "mmap param 0x%lx, 0x%x invalid", phy_addr, size);
	return ret;
}
*/

//static struct rtscam_ge_file_operations rtscam_isp_fops = {
//	.owner = THIS_MODULE,
//	.open = rtscam_isp_open,
//	.release = rtscam_isp_close,
//	.read = rtscam_isp_read,
//	.write = rtscam_isp_write,
//	.unlocked_ioctl = rtscam_isp_ioctl,
//	.poll = rtscam_isp_poll,
//	.mmap = rtscam_isp_mmap,
//};
#ifdef _AWB_DEBUG_
static int log_cnt = 0;
static int interval = 60;
#endif
static int __rtscam_isp_read_statis(struct rtscam_isp *isp,
				    struct rtscam_isp_statis_node *node)
{
	int i;
	struct rts_isp_statis_data *data = &node->data;

	data->frame_count = atomic_inc_return(&isp->statis_count);

	data->awb_reg.fine_r_sum = rtscam_isp_read_reg(isp, AWB_FINE_SUM_R);
	data->awb_reg.fine_g_sum = rtscam_isp_read_reg(isp, AWB_FINE_SUM_G);
	data->awb_reg.fine_b_sum = rtscam_isp_read_reg(isp, AWB_FINE_SUM_B);
	data->awb_reg.fine_white_pixels =
		rtscam_isp_read_reg(isp, AWB_FINE_WP_NUM);
	for (i = 0; i < (int)ARRAY_SIZE(data->awb_reg.illum_white_pixels); i++)
		data->awb_reg.illum_white_pixels[i] =
			rtscam_isp_read_reg(isp, AWB_WP_NUM + i * 4);
#ifdef _AWB_DEBUG_
	if ((log_cnt%interval) == 0) {
		printf("SYS_INT_FLAG0 0x%08x r 0x%08x g 0x%08x b 0x%08x wp 0x%08x \r\n", rtscam_isp_read_reg(isp, SYS_INT_FLAG0), data->awb_reg.fine_r_sum, data->awb_reg.fine_g_sum, data->awb_reg.fine_b_sum, data->awb_reg.fine_white_pixels);
		printf("mean1 0x%08x mean2 0x%08x r 0x%08x g 0x%08x b 0x%08x \r\n", rtscam_isp_read_reg(isp, 0xC0E4),  rtscam_isp_read_reg(isp, 0xC0E8), rtscam_isp_read_reg(isp, 0xC0EC),rtscam_isp_read_reg(isp, 0xC0F0), rtscam_isp_read_reg(isp, 0xC0F4));

		printf("ill wp %d %d %d %d %d %d \r\n", data->awb_reg.illum_white_pixels[0], data->awb_reg.illum_white_pixels[1], data->awb_reg.illum_white_pixels[2],
				data->awb_reg.illum_white_pixels[3], data->awb_reg.illum_white_pixels[4],data->awb_reg.illum_white_pixels[5]);
		if (interval == 60) {
			interval = 59;
		} else {
			interval = 60;
		}
	}
	log_cnt++;
#endif
	data->af_reg.num0 = rtscam_isp_read_reg(isp, AF_NUM0);
	data->af_reg.num1 = rtscam_isp_read_reg(isp, AF_NUM1);
	data->af_reg.sum0 = rtscam_isp_read_reg(isp, AF_SUM0);
	data->af_reg.sum1 = rtscam_isp_read_reg(isp, AF_SUM1);

	if (rtscam_isp_read_reg(isp, SYS_INT_FLAG0) & FLICK_STATIS_INT) {
		rtscam_isp_write_reg(isp, FLICK_STATIS_INT, SYS_INT_FLAG0);
		data->flick_reg.fft_sum2_9 =
			rtscam_isp_read_reg(isp, FLICK_FFT_RESUT_SUM2_9);
		data->flick_reg.fft_sum2_127 =
			rtscam_isp_read_reg(isp, FLICK_FFT_RESUT_SUM2_127);
		data->flick_reg.valid = TRUE;
	} else {
		data->flick_reg.valid = FALSE;
	}

	return 0;
}

static int rtscam_isp_write_sync_i2c(struct rtscam_isp *isp,
				     struct rts_isp_i2c_reg_mask *i2c_mask,
				     struct rts_isp_i2c_info *i2c_info)
{
	struct rts_isp_i2c_reg i2c;

	i2c.addr = i2c_mask->addr;
	//i2c.data = i2c_mask->data;
	if (i2c_mask->mask) {
		rtscam_isp_read_i2c_reg(isp, i2c_info, &i2c);
		i2c.data &= ~i2c_mask->mask;
		i2c.data |= (i2c_mask->data & i2c_mask->mask);
	} else {
		i2c.data = i2c_mask->data;
	}
	rtscam_isp_write_i2c_reg(isp, i2c_info, &i2c);
	return 0;
}

static int rtscam_isp_write_sync_reg(struct rtscam_isp *isp,
				     struct rts_isp_reg_mask *reg)
{
	u32 data;

	if (reg->mask) {
		data = rtscam_isp_read_reg(isp, reg->addr);
		data &= ~reg->mask;
		data |= (reg->data & reg->mask);
	} else {
		data = reg->data;
	}
	rtscam_isp_write_reg(isp, data, reg->addr);
	return 0;
}
uint32_t sync_i2c_time = 0;
int log_sync_i2c = 0;
extern BOOL data_start_error;
extern BOOL frame_end_error;

static void __rtscam_isp_irq_sync_write_one(struct rtscam_isp *isp,
					    struct rtscam_isp_sync_item *item)
{

	if (item->reg.info.type == RTS_ISP_SYNC_REG_TYPE_REG)
		rtscam_isp_write_sync_reg(isp, &item->reg.reg);
	else {
		if (!log_sync_i2c) {
			sync_i2c_time = hal_read_curtime_us();
			log_sync_i2c = 1;
		}
		rtscam_isp_write_sync_i2c(isp, &item->reg.i2c, &item->i2c_info);
	}
}
static int rtscam_isp_irq_sync(struct rtscam_isp *isp)
{
	struct rtscam_isp_sync *sync = &isp->sync;
	enum rts_isp_interrupt irq = (enum rts_isp_interrupt)(RTS_ISP_INT_NONE + 1);
	struct rtscam_isp_sync_item *item;
	struct rtscam_isp_sync_item *next;

	while (1) {
//		if (osSemaphoreAcquire(isptaskSemaphore, osWaitForever) != osOK ) {
		if (xSemaphoreTake(isptaskSemaphore, osWaitForever) != pdTRUE ) {

			if(voe_adp->voe_ch_cnt != 0) {
				printf("rtscam_isp_irq_sync wait semaphore timeout ch(%d)\n", voe_adp->voe_ch_cnt);
			}
			continue;
			//isp_error("isptaskSemaphore acquire error\r\n");
			//break;
		}
		if (data_start_error) {
			printf("data_start: sensor didn't initialize done !\n\r");
			data_start_error = FALSE;
		}
		if (frame_end_error) {
			printf("frame_end: sensor didn't initialize done !\n\r");
			frame_end_error = FALSE;
		}
		//printf("isptaskSemaphore wait done\r\n");
		/* wait all module data start done */
		if (atomic_read_isp(&sync->irq) == RTS_ISP_INT_DATA_START) {
			    vTaskDelay(2);
				//osDelay(2);
		}

		if (xSemaphoreTake(sync->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
			isp_error("rtscam_isp_irq_sync wait sync->lock timeout\n\r");
			continue;
		}
		for (irq = (enum rts_isp_interrupt)(RTS_ISP_INT_NONE + 1);
		     irq <= (unsigned int)atomic_read_isp(&sync->irq); irq++) {
			struct list_head *head;

			head = &sync->delay[sync->index].irq[irq - 1];
			list_for_each_entry_safe(item, next, head, list, struct rtscam_isp_sync_item) {
				list_del(&item->list);
				//if (item->reg.info.type == RTS_ISP_SYNC_REG_TYPE_REG) {
				//	rtscam_isp_write_sync_reg(isp, &item->reg.reg);
				//} else {
				//	rtscam_isp_write_sync_i2c(isp, &item->reg.i2c,
				//				  &item->i2c_info);
				//}
				if (!isp->stopping)
					__rtscam_isp_irq_sync_write_one(isp, item);
				__rtscam_isp_sync_put_idle(sync, item);
			}
			if (irq == _MAX_RTS_ISP_INT - 1) {
				sync->index = rtscam_isp_sync_index(sync, 1);
				sync->irq = RTS_ISP_INT_NONE;
			}
		}
//		osMutexRelease(sync->lock);
		xSemaphoreGive(sync->lock);
	}
	return 0;
}

static void isp_irq_thread(void const *data)
{
	struct rtscam_isp *isp = (struct rtscam_isp *)data;

	if (data != m_isp ) {
		isp_error("%s data != m_isp /r/n", __func__);
		return;
	}


	rtscam_isp_irq_sync(isp);
	printf("%s osThreadTerminate /r/n", __func__);
	//osThreadTerminate(isp_handle);
	vTaskDelete(isp_handle);
	//vTaskDelete(NULL);
}
extern int isp_meta_out;

static void rtscam_isp_irq_statis(struct rtscam_isp *isp)
{
	struct rtscam_isp_statis_node *node, *node_done;
	struct rtscam_isp_statis *statis = &isp->statis;

	if (xSemaphoreTake(statis->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
		isp_error("rtscam_isp_irq_statis wait statis->lock timeout\n\r");
		return;
	}
	//get_statis_meta_data(&isp_meta_statis);
	if (isp_meta_out)
		statis_cnt++;

	while (!list_empty(&statis->done)) {
		node = list_first_entry(&statis->done,
					struct rtscam_isp_statis_node, list);
		list_move(&node->list, &statis->idle);
	}
	// coverity[bad_sizeof]
	node = list_first_entry_or_null(&statis->idle,
					struct rtscam_isp_statis_node, list);

	if (node) {  //free slot available
		rtscam_isp_write_reg(isp, (u32)node->addr, STATIS_DDR_ADDR);

		//rtscam_isp_write_reg(isp, 0x11c|(1<<6), 0x0000c000); // //Martin add
		rtscam_isp_write_reg(isp, STATIS_STREAM_EN, STATIS_CTRL);
	//rtscam_isp_write_reg(isp, 0x1, SYS_STATIS_CTRL); //Martin add

		__rtscam_isp_read_statis(isp, node);
#ifdef __DEBUG_STATIS__
		printf("%s move to busy 0x%08x \r\n", __FUNCTION__, &node->list);
#endif
		list_move_tail(&node->list, &statis->busy);
#ifdef __DEBUG_STATIS__
		printf("%s move busy to done 0x%08x \r\n", __FUNCTION__, statis->busy.next);
#endif
		list_move(statis->busy.next, &statis->done);

		atomic_set_isp(&statis->valid, 1);
		//Sdk v4.1
		node_done = list_first_entry(&statis->done,
					struct rtscam_isp_statis_node, list);
		SCB_InvalidateDCache_by_Addr((uint32_t *)node_done->addr, rtscam_isp_read_reg(isp, STATIS_DDR_LEN));
		//printf("process 0x%08x node_done 0x%08x \r\n", node->addr, node_done->addr);
#ifdef __DEBUG_STATIS__
		printf("%s process node_done 0x%08x \r\n", __FUNCTION__, &(node_done->list));
#endif
		//printf("%s node_done 0x%08x \r\n", __FUNCTION__, &(node_done->list));
		//wake_up(&isp->message.wq);
		//if (osSemaphoreRelease(isp->message.wq) != osOK)
	    //    rtsprintk(RTS_TRACE_ERROR, "message.wq release failed\n");
		//if (isp_meta_out)
		//	hal_delay_us(200);  // frdn task to record meta data

		if (xSemaphoreTake(isp->lock, ISP_SEM_TIMEOUT) != pdTRUE) {
			isp_error("rtscam_isp_irq_statis wait isp->lock timeout\n\r");
		} else {
//asm("sdbbp");
			if (isp_meta_out)
				statis_updating = hal_read_curtime_us();
			rtscam_isp_message_call(&isp->message, 0, RTS_ISP_STATIS_DONE,
						      &node_done->data, sizeof(node_done->data));
//			osMutexRelease(isp->lock);
			if (isp_meta_out)
				statis_updating = 0;
			xSemaphoreGive(isp->lock);

#ifdef __DEBUG_STATIS__
			printf("%s send message RTS_ISP_STATIS_DONE  0x%08x  data 0x%08x\r\n", __FUNCTION__, &(node_done->list), &node_done->data);
#endif
		}
	} else {
		rtscam_isp_write_reg(isp, STATIS_STREAM_EN, STATIS_CTRL);
		isp_error("statis buffer overflow: w/o idle status slot\r\n");
	}
	rtscam_isp_write_reg(isp, STATIS_ALL_INT, SYS_INT_FLAG0);
	//spin_unlock(&statis->lock);
//	osMutexRelease(statis->lock);
	xSemaphoreGive(statis->lock);

}

static void isp_statis_thread(void const *data)
{
	struct rtscam_isp *isp = (struct rtscam_isp *)data;

	while (1) {
//		if (osSemaphoreAcquire(ispstatisSemaphore, osWaitForever) != osOK ) {
		if (xSemaphoreTake(ispstatisSemaphore, osWaitForever) != pdTRUE ) {
			if(voe_adp->voe_ch_cnt != 0) {
				printf("isp_statis_thread wait semaphore timeout ch(%d)\n", voe_adp->voe_ch_cnt);
			}
			continue;

			//isp_error("ispstatisSemaphore acquire error\n");
			//break;
		}

		//printf("ispstatisSemaphore wait done\r\n");
		rtscam_isp_irq_statis(isp);
	}
	printf("rtscam_isp_irq_statis_thread terminate!\n");
	//osThreadTerminate (isp_statis_handle);
	vTaskDelete (isp_statis_handle);
	//vTaskDelete(NULL);
}

#ifdef _WORKAROUND_FRAME_CHANGE_
int awb_r_gain_wkrnd = 0x100;
int awb_b_gain_wkrnd = 0x100;
#endif

uint32_t data_start_time0[5] = {0};
uint32_t frame_end_time0[5] = {0};
uint32_t *data_start_time, *frame_end_time;
int data_start_log = 0, frame_end_log = 0;
extern uint32_t sensor_init_done;
static int rtscam_isp_irq(void* data)
{
	u32 int_value;
	struct rtscam_isp *isp = &gbl_isp;
    portBASE_TYPE taskWoken = pdFALSE;


	//if (!rtscam_isp_check_isp_clock())
	//	return;
	data_start_time = &data_start_time0[0];
	frame_end_time = &frame_end_time0[0];

	int_value = (rtscam_isp_read_reg(isp, SYS_INT_EN0) &
		     rtscam_isp_read_reg(isp, SYS_INT_FLAG0));
	//printf("%s 0x%08x 0x%08x \r\n", __func__, HAL_READ32(0x40300000, 0x10), HAL_READ32(0x40300000, 0x14));

	if (int_value & DATA_START_INT) {
		rtscam_isp_write_reg(isp, DATA_START_INT, SYS_INT_FLAG0);

		if ( sensor_init_done ) {

			if (!isp->data_start_done) {
				isp->data_start_done = TRUE;
			}
			isp->sync.irq = RTS_ISP_INT_DATA_START;
			if (data_start_log<5) {
				data_start_time0[data_start_log] = hal_read_curtime_us();
				data_start_log++;
			}


			//printf("data_start_time %d \r\n", hal_read_curtime_us());
			//if (!osSemaphoreGetCount(isp->data_start_completion))
#if 1
			if (!uxQueueMessagesWaitingFromISR(isp->data_start_completion)) {
				xSemaphoreGiveFromISR(isp->data_start_completion, &taskWoken);
				portEND_SWITCHING_ISR(taskWoken);
			}
			xSemaphoreGiveFromISR(isptaskSemaphore, &taskWoken);
			portEND_SWITCHING_ISR(taskWoken);

#else
			if (!osSemaphoreGetCount(isp->data_start_completion))
				osSemaphoreRelease(isp->data_start_completion);
			osSemaphoreRelease(isptaskSemaphore);  //wake rtscam_isp_irq_thread()
#endif
		} else {

			data_start_error = TRUE;
		}

		return IRQ_WAKE_THREAD;  //exec rtscam_isp_irq_thread()
	}

	if (int_value & FRAME_END_INT) {
		if (frame_end_log<5) {
			frame_end_time0[frame_end_log] = hal_read_curtime_us();
			frame_end_log++;
		}
		//printf("frame_end_time %d \r\n", hal_read_curtime_us());
		rtscam_isp_write_reg(isp, FRAME_END_INT, SYS_INT_FLAG0);
#ifdef _WORKAROUND_FRAME_CHANGE_
		awb_r_gain_wkrnd += 0x10;
		awb_b_gain_wkrnd += 0x20;
		if(awb_r_gain_wkrnd >=0x400)
			awb_r_gain_wkrnd = 0x100;

		if(awb_b_gain_wkrnd >=0x400)
			awb_b_gain_wkrnd = 0x100;
		//printf("r_gain %x\n",awb_r_gain);
		rtscam_isp_write_reg(isp, awb_r_gain_wkrnd, 0xC000 + 0x0008);
		rtscam_isp_write_reg(isp, 0x100, 0xC000 + 0x000C);
		rtscam_isp_write_reg(isp,awb_b_gain_wkrnd, 0xC000 + 0x0010);

		rtscam_isp_write_reg(isp, (1<<2), 0xC000 + 0x0004);
#endif

		if ( isp->data_start_done && sensor_init_done ) {

			isp->frame_count++;
			isp->sync.irq = RTS_ISP_INT_FRAME_END;
	#if 1
			if (!uxQueueMessagesWaitingFromISR(isp->frame_end_completion)) {
				xSemaphoreGiveFromISR(isp->frame_end_completion, &taskWoken);
				portEND_SWITCHING_ISR(taskWoken);
			}
			xSemaphoreGiveFromISR(isptaskSemaphore, &taskWoken);
			portEND_SWITCHING_ISR(taskWoken);

	#else
			if (!osSemaphoreGetCount(isp->frame_end_completion))
				osSemaphoreRelease(isp->frame_end_completion);
			osSemaphoreRelease(isptaskSemaphore);  //wake rtscam_isp_irq_thread()
	#endif

		} else {
			//printf("Err frame_end event or sensor didn't initialize done !");
			if (!sensor_init_done) {
				frame_end_error = TRUE;
			}
		}
		return IRQ_WAKE_THREAD;  //exec rtscam_isp_irq_thread()
	}

	if (int_value & STATIS_STREAM_INT) {

		//printf("%s 0x%08x 0x%08x \r\n", __func__, HAL_READ32(0x40300000, 0x10), HAL_READ32(0x40300000, 0x14));
		rtscam_isp_write_reg(isp, STATIS_STREAM_INT, SYS_INT_FLAG0);

#if 0	// Test edge-sensitive isr
		if (test_fix_method>0) {
			rtscam_isp_write_reg(isp, STATIS_STREAM_INT, SYS_INT_FLAG0);
			test_fix_method--;
		}
		if (test_fix_method <= 0) {
			test_fix_method = 10;
			printf("%s 0x%08x 0x%08x \r\n", __func__, HAL_READ32(0x40300000, 0x10), HAL_READ32(0x40300000, 0x14));
		}
#endif
		//rtscam_isp_irq_statis(isp); exec in rtscam_isp_irq_statis_thread()
#if 1
        xSemaphoreGiveFromISR(ispstatisSemaphore, &taskWoken);
        portEND_SWITCHING_ISR(taskWoken);

#else
		osSemaphoreRelease(ispstatisSemaphore);  //wake rtscam_isp_irq_statis_thread()
#endif
		return IRQ_HANDLED;
	}

	if (int_value) {
		isp_error("%s EN0 0x%08x FG0 0x%08x \r\n", __FUNCTION__, rtscam_isp_read_reg(isp, SYS_INT_EN0), rtscam_isp_read_reg(isp, SYS_INT_FLAG0));
	}


	return IRQ_NONE;
}

/*
static int __create_device(struct rtscam_isp *isp)
{
	struct rtscam_ge_device *gdev;
	int ret;

	if (isp->gdev)
		return 0;

	gdev = rtscam_ge_device_alloc();
	if (!gdev)
		return -ENOMEM;

	strlcpy(gdev->name, RTS_ISP_DEV_NAME, sizeof(gdev->name));
	//gdev->parent = get_device(isp->dev);
	gdev->release = rtscam_ge_device_release;
	gdev->fops = &rtscam_isp_fops;

	gdev->data = (void*)isp;  //rtscam_ge_set_drvdata(gdev, isp);
	ret = rtscam_ge_register_device(gdev);
	if (ret) {
		rtscam_ge_device_release(gdev);
		return ret;
	}

	isp->gdev = gdev;

	return 0;
}

static void __remove_device(struct rtscam_isp *isp)
{
	struct rtscam_ge_device *gdev;

	gdev = isp->gdev;
	if (!gdev)
		return;
	//put_device(gdev->parent);
	rtscam_ge_unregister_device(gdev);

	isp->gdev = NULL;
}

static int rtscam_isp_parse_i2c_adapter(struct rtscam_isp *isp,
					struct device_node *dev_node)
{
	struct device_node *i2c_node;


	i2c_node = of_parse_phandle(dev_node, "video-i2c", 0);
	if (!i2c_node)
		goto err;
	isp->adapter = of_get_i2c_adapter_by_node(i2c_node);
	of_node_put(i2c_node);
	if (!isp->adapter)
		goto err;
	// do not retry because sensor soft reset may cause EAGAIN
	isp->adapter->retries = 0;

	return 0;
err:
	rtsprintk(RTS_TRACE_ERROR, "get i2c adapter fail\n");
	return -ENXIO;
}

static int rtscam_isp_parse_region(struct rtscam_region *region,
				   struct device_node *dev_node,
				   const char *node_name)
{
	int ret;
	struct device_node *node;

	node = of_parse_phandle(dev_node, node_name, 0);
	if (!node)
		return -ENXIO;

	ret = of_property_read_u32_index(node, "reg", 0, &region->base);
	if (ret)
		goto exit;
	ret = of_property_read_u32_index(node, "reg", 1, &region->size);
	if (ret)
		goto exit;

exit:
	of_node_put(node);
	if (ret)
		rtsprintk(RTS_TRACE_ERROR,
			  "failed to get region %s\n", node_name);
	return ret;
}
*/

static int rtscam_isp_parse_buffer_config(struct rtscam_isp *isp)
{
#if 0
	isp->tnr_cfg.base = 0; isp->tnr_cfg.size = 0x2a00;
	isp->statis_cfg.base = 0x2c00; isp->statis_cfg.size = 0x200;
#else
	isp->tnr_cfg.base = hal_isp_get_axi_buf_addr(TNR_BUF);
	isp->tnr_cfg.size = hal_isp_get_axi_buf_size(TNR_BUF);
	isp->statis_cfg.base = hal_isp_get_axi_buf_addr(STATIS_BUF);
	isp->statis_cfg.size = hal_isp_get_axi_buf_size(STATIS_BUF);
#endif
	//printf("tnr buffer config: <0x%x 0x%x>\n",
	//	  isp->tnr_cfg.base, isp->tnr_cfg.size);
	//printf("statis buffer config: <0x%x 0x%x>\n",
	//	  isp->statis_cfg.base, isp->statis_cfg.size);
	return 0;
}

static int rtscam_isp_parse_dts(struct rtscam_isp *isp)
{
	//int ret;

	if (!isp)
		return -EINVAL;


#if CONFIG_FPGA // FPGA
	isp->is_fpga = TRUE;
#else  // ASIC // PXP
	isp->is_fpga = FALSE;
#endif


	isp->has_pmu = FALSE;

	isp->tnr_bit = 12;
	//rtsprintk(RTS_TRACE_INFO, "tnr_bit: %u\n", isp->tnr_bit);

	//ret = rtscam_isp_parse_i2c_adapter(isp, dev_node);
	//isp->adapter = ;  //video-i2c = <&i2c1> in rts_3915base.dtsi
	isp->i2c_cfg.base = I2C1_BASE; isp->i2c_cfg.size = 0x1000;

	rtscam_isp_parse_buffer_config(isp);

	return RTS_OK;
}

int rtscam_isp_probe(void)
{
	u32 i;
	int ret;
	struct rtscam_isp *isp = &gbl_isp;
	//struct device *dev = &pdev->dev;
	struct rtscam_isp_mfd *mfd;
	static TaskHandle_t isp_handle = NULL;
	static TaskHandle_t isp_statis_handle = NULL;

	//osSemaphoreAttr_t isptasksemaphoreAttr = { .name = "isptaskSemaphore" };
	//osSemaphoreAttr_t ispstatissemaphoreAttr = { .name = "ispstatisSemaphore" };
	//osSemaphoreAttr_t dstartAttr = { .name = "DSTARTSemaphore" };
	//osSemaphoreAttr_t fendAttr = { .name = "FENDSemaphore" };



	isp_info("%s\r\n", __func__);

	mfd = rtscam_get_isp_mfd();  //dev_get_drvdata(dev->parent);
	if (!mfd)
		return -EINVAL;
	isp->mfd = mfd;

	ret = mfd->get_child_resource(mfd, RTS_MFD_MODUAL_ID_ISP, &isp->res);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR,
			  "Couldn't get child resource from mfd\n");
		return ret;
	}

#if defined(_SYSTEM_CONNECT_READY_)

	//isp->isp_clk = clk_get("isp_clk");
	isp->inf_clk = clk_get("inf_clk");
	isp->mipiout_clk = clk_get("mipiout_clk");
	if (IS_ERR(isp->inf_clk) || IS_ERR(isp->mipiout_clk)) {
		rtsprintk(RTS_TRACE_ERROR, "get isp inf or mipi clk fail\n");
		return -EINVAL;
	}
#else
	//isp->isp_clk = clk_get("isp_clk");
	isp->inf_clk = clk_get("inf_clk");
	isp->mipiout_clk = clk_get("mipiout_clk");

	if (isp->inf_clk && isp->mipiout_clk) {
#if CONFIG_FPGA // FPGA
	//isp->isp_clk->rate = 20e6;
	isp->inf_clk->rate = 20e6;
	isp->mipiout_clk->rate = 20e6;
	isp->isp_clk_fix = 20e6;
#elif CONFIG_PXP // PXP
	isp->inf_clk->rate = 250e6;
	isp->mipiout_clk->rate = 200e6;
	isp->isp_clk_fix = 200e6;
#else  // ASIC
	isp->inf_clk->rate = 250e6; //MIPI_CLK_DEFINE
	isp->mipiout_clk->rate = 200e6;
#ifdef CALC_CLK_AUTO
	isp->isp_clk_fix = 0;
#else
	isp->isp_clk_fix = 200e6; //ISP_CLK_DEFINE
#endif
#endif
	}
#endif
	//isp->pins.p = devm_pinctrl_get(dev);
	//if (IS_ERR(isp->pins.p)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get pin ctrl handler fail\n");
	//	return -EINVAL;
	//}
	//isp->pins.default_state = pinctrl_lookup_state(isp->pins.p, "default");
	//isp->pins.dvp_state = pinctrl_lookup_state(isp->pins.p, "dvp");
	//isp->pins.mipi_state = pinctrl_lookup_state(isp->pins.p, "mipi");
	//if (IS_ERR(isp->pins.default_state) ||
	//    IS_ERR(isp->pins.dvp_state) || IS_ERR(isp->pins.mipi_state)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get pin state fail\n");
	//	return -EINVAL;
	//}

	//isp->mem_info = rts_get_mem_info();
	//if (!isp->mem_info) {
	//	rtsprintk(RTS_TRACE_ERROR, "get mem info fail\n");
	//	return -EINVAL;
	//}
	INIT_LIST_HEAD(&isp->mem_list);

	ret = mfd->register_irq(mfd, isp,
			rtscam_isp_irq, NULL);  //rtscam_isp_irq_thread);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR, "regist rts isp irq to mfd fail\n");
		goto err;
	}
	//RLX_ClearPendingIRQ(VIDEOIN_IRQn);
	//RLX_SetVideoInIrqVector(VIDEOIN_ID_ISP, (u32)rtscam_isp_irq);
	//RLX_EnableVideoInIRQ(VIDEOIN_ID_ISP);

	/* Task & Semaphore */
	//isptaskSemaphore = osSemaphoreNew(256, 0, &isptasksemaphoreAttr);
	isptaskSemaphore = xSemaphoreCreateCounting(256, 0);

	if (isptaskSemaphore == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "isp_irq task sema create fail!\r\n");
	    goto err;
	}
   // printf("isptaskSemaphore 0x%08x\r\n", isptaskSemaphore);
	m_isp = isp;

#if 1
#if 0
	isp_handle = osThreadCreate (osThread(isp_irq_thread), (void*)isp);
    if (isp_handle == 0) {
        isp_error("Create isp_handle error\r\n");
    }
#else

	ret = xTaskCreate((TaskFunction_t)isp_irq_thread,"isp_irq", 16*1024, isp, 6, &isp_handle);
	if(ret == pdFAIL) {
        isp_error("Create isp_handle error\r\n");
	}
#endif
    isp_info("isp_handle task\r\n");

#else


	task_info_st  isp_irq_task_info =
	{
	    .name       = "isp_irq_task",
	    .priority   = 4,
	    .delay      = pdMS_TO_TICKS(100),
	    .func       = rtscam_isp_irq_thread,
	    .param      = (void*)isp,
	    .stack_size = SZ_16K,
	    .pre_del_cb = NULL,
	};

	if ((isp_handle = task_create_user_by_struct(&isp_irq_task_info, &ret)) == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "isp_irq task create fail!\n");
	    goto err;
	}
	vTaskResume(isp_handle);
#endif

	//ispstatisSemaphore = osSemaphoreNew(1, 0, &ispstatissemaphoreAttr);
	ispstatisSemaphore = xSemaphoreCreateCounting(1, 0);

	if (ispstatisSemaphore == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "isp_irq statis sema create fail!\r\n");
	    goto err;
	}
	//printf("ispstatisSemaphore 0x%08x\r\n", ispstatisSemaphore);
#if 0
	isp_statis_handle = osThreadCreate (osThread(isp_statis_thread), (void*)isp);
    if (isp_statis_handle == 0) {
        isp_error ("Create isp_statis_handle task error\r\n");
    }
#else

	ret = xTaskCreate((TaskFunction_t)isp_statis_thread,"isp_statis", 16*1024, isp, 6, &isp_statis_handle);
	if(ret == pdFAIL) {
        isp_error ("Create isp_statis_handle task error\r\n");
	}
#endif
	isp_info("isp_statis_handle task\r\n");

#if 0
	task_info_st  isp_irq_statis_info =
	{
	    .name       = "isp_irq_statis",
	    .priority   = 3,
	    .delay      = pdMS_TO_TICKS(100),
	    .func       = rtscam_isp_irq_statis_thread,
	    .param      = (void*)isp,
	    .stack_size = SZ_16K,
	    .pre_del_cb = NULL,
	};
	if ((isp_statis_handle = task_create_user_by_struct(&isp_irq_statis_info, &ret)) == NULL)
	{
	    rtsprintk(RTS_TRACE_ERROR, "isp_irq statis create fail!\n");
	    goto err;
	}
	vTaskResume(isp_statis_handle);
#endif


	//RLX_ClearPendingIRQ(VIDEOIN_IRQn);
	//RLX_SetVideoInIrqVector(VIDEOIN_ID_ISP, (u32)rtscam_isp_irq);
	//RLX_EnableVideoInIRQ(VIDEOIN_ID_ISP);

	//isp->reg_base = (void*)ISP_BASE;
	//isp->io_start = ISP_BASE&(~0xA0000000);
	//isp->io_size = 0xe0000;
	//isp->irq = VIDEOIN_IRQn;

	//isp->dev = get_device(dev);
	atomic_set_isp(&isp->user_count, 0);

	ret = rtscam_isp_parse_dts(isp);
	if (ret)
		goto err;

	//mutex_init(&isp->lock);
	isp->lock = xSemaphoreCreateMutex();
	if ( !isp->lock ) {
		rtsprintk(RTS_TRACE_ERROR, "isp->lock mutex alloc fail\r\n");
		ret = RTS_FAIL;
		goto err;
	}
	for (i = 0; i < ARRAY_SIZE(isp->power); i++) {
		ret = rtscam_isp_snr_power_init(isp, &isp->power[i], i);
		if (ret)
			goto err;
	}
	ret = rtscam_isp_message_init(&isp->message, isp->lock);
	if (ret)
		goto err;
	ret = rtscam_isp_sync_init(&isp->sync);
	if (ret)
		goto err;

	//init_completion(&isp->data_start_completion);
	//init_completion(&isp->frame_end_completion);
	//isp->data_start_completion = osSemaphoreNew(1, 0, &dstartAttr);
	isp->data_start_completion = xSemaphoreCreateCounting(1, 0);

	if (isp->data_start_completion == NULL)
	{
		isp_error("{isp->data_start_completion} new Semaphore fail!\r\n");
		ret = RT_E_CREATE_FAIL;
		goto err;
	}

	//isp->frame_end_completion = osSemaphoreNew(1, 0, &fendAttr);
	isp->frame_end_completion = xSemaphoreCreateCounting(1, 0);

	if (isp->frame_end_completion == NULL)
	{
		isp_error("{isp->frame_end_completion} new Semaphore fail!\r\n");
		ret = RT_E_CREATE_FAIL;
		goto err;
	}

	//__create_device(isp);  //call file op API directly

	//isp->sysmem = devm_reset_control_get(isp->dev, "isp-sysmem-up");
	//if (IS_ERR(isp->sysmem)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get isp sysmem reset fail\n");
	//	goto err;
	//}
	//reset_control_deassert(isp->sysmem);
	//rts_sysmem_deassert(SYS_ISP_MEM);

	//isp->mipiout_sysmem = devm_reset_control_get(isp->dev,
	//					     "mipiout_sysmem_up");
	//if (IS_ERR(isp->mipiout_sysmem)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get mipiout sysmem reset fail\n");
	//	goto err;
	//}
	//reset_control_deassert(isp->mipiout_sysmem);
	//rts_sysmem_deassert(SYS_MEM_SD_MIPITX);

	//isp->mipi_reset = devm_reset_control_get(isp->dev, "mipi_reset");
	//if (IS_ERR(isp->mipi_reset)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get mipi reset fail\n");
	//	goto err;
	//}
	//isp->mipiout_reset = devm_reset_control_get(isp->dev, "mipiout_reset");
	//if (IS_ERR(isp->mipiout_reset)) {
	//	rtsprintk(RTS_TRACE_ERROR, "get mipiout reset fail\n");
	//	goto err;
	//}

	//device_create_file(isp->dev, &dev_attr_msg_timeout);
	//device_create_file(isp->dev, &dev_attr_frame_count);
	//device_create_file(isp->dev, &dev_attr_fix_clk);

	//platform_set_drvdata(pdev, isp);


	return RT_OK;

err:
	//i2c_put_adapter(isp->adapter);
	//rts_put_mem_info(isp->mem_info);
	return ret;
}

int rtscam_isp_remove(void)
{
	struct rtscam_isp *isp = &gbl_isp;

	//__remove_device(isp);
	rtscam_isp_sync_cleanup(&isp->sync);
	rtscam_zoom_unregister_isp(&isp->zoom_isp);
	//i2c_put_adapter(isp->adapter);
	//reset_control_assert(isp->sysmem);
	//reset_control_assert(isp->mipiout_sysmem);
	rts_sysmem_assert(SYS_ISP_MEM);
	rts_sysmem_assert(SYS_MEM_SD_MIPITX);
	//put_device(isp->dev);
	//rts_put_mem_info(isp->mem_info);

	//device_remove_file(isp->dev, &dev_attr_msg_timeout);
	//device_remove_file(isp->dev, &dev_attr_frame_count);
	//device_remove_file(isp->dev, &dev_attr_fix_clk);

	m_isp = NULL;
	return RT_OK;
}
