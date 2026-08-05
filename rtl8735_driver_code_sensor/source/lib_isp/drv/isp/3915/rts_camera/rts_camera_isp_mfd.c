/*
 * rtsisp device driver (kernel module)
 * Realtek Semiconductor Corp.
 * rts_camera_isp_mfd.c
 * Copyright (C) 2020    Wil_Shi<wil_shi@realsil.com.cn>
 */

#define TAG "ISP MFD"


#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include "rt_util.h"
#include <reset/reset-rts3915.h>
#include <rtscamkit.h>
#include "rlx_reg.h"
#include "rlx_irq.h"
#include "rlx_clk.h"
#include "rts_camera.h"
#include "rts_camera_isp_mfd.h"
#include "rtx_mutex.h"
#include "rt_time.h"
#include "platform_conf.h"

#define RTS_ISP_MFD_DRV_NAME		"rts_isp_mfd"
#define RTS_ISP_MFD_DEV_NAME		"rtsispmfd"

#define DEFAULT_MFD_ISP_CLK 80e6

struct rtscam_isp_mfd_irq_node {
	irq_ops ops;
	void *master;
	struct list_head list;
};

struct rtscam_isp_mfd_ex {
	//struct device *dev;
	struct rtscam_isp_mfd mfd;

	void *reg_base;
	struct rtscam_isp_mfd_resource res;

	struct clk_rlx  *isp_clk;
	int isp_clk_refcnt;

	//struct reset_control *isp_reset;

	int irq;
	struct list_head irq_ops;
	struct list_head irq_thread_ops;

	bool is_fpga;
};

/*
 * This struct describes the MFD part ("cell").
 * After registration the copy of this structure will become the platform data
 * of the resulting platform_device
 */
struct mfd_cell {
	const char		*name;

	/*
	 * Device Tree compatible string
	 * See: Documentation/devicetree/usage-model.txt Chapter 2.2 for details
	 */
	const char		*of_compatible;
};

struct isp_mfd_cell_info {
	struct mfd_cell *cells;
	u32 num;
};

struct rtscam_isp_mfd_reg {
	enum RTS_MFD_MODUAL_ID id;
	u32 base;
	u32 size;
};

/*
static struct mfd_cell rts3915_isp_mfd_cells[] = {
	{
		.name = "rts_isp",
		.of_compatible = "realtek,rts3915-isp",
	},
	{
		.name = "rts_md",
		.of_compatible = "realtek,rts3915-md",
	},
	{
		.name = "rts_zoom",
		.of_compatible = "realtek,rts3915-zoom",
	},
	{
		.name = "rts_verify",
		.of_compatible = "realtek,rts3915-verify",
	},
};

static const struct isp_mfd_cell_info rts3915_mfd_info = {
	.cells = rts3915_isp_mfd_cells,
	.num = ARRAY_SIZE(rts3915_isp_mfd_cells),
};
*/

static struct rtscam_isp_mfd_reg mfd_regs[4] = {
	{RTS_MFD_MODUAL_ID_ISP, 0, 0},
	{RTS_MFD_MODUAL_ID_ZOOM, 0, 0},
	{RTS_MFD_MODUAL_ID_MD, 0, 0},
	{RTS_MFD_MODUAL_ID_VERIFY, 0, 0},
};

struct rtscam_isp_mfd_ex gbl_isp_mfd_ex={0};

struct rtscam_isp_mfd *rtscam_get_isp_mfd(void)
{
	return &gbl_isp_mfd_ex.mfd;
}

static int __mfd_set_clk_rate(struct rtscam_isp_mfd_ex *mfd_ex,
				unsigned long *rate)
{
	//int ret = 0;
	struct clk_rlx *isp_clk = mfd_ex->isp_clk;
	isp_info("%s %d start\r\n", __func__, *rate);
	if (!rate)
		return -EINVAL;

	if (*rate == 0)
		return 0;

	if (!mfd_ex->is_fpga) {
		clk_set_rate(isp_clk, clk_round_rate(isp_clk, *rate));
	}

	*rate = clk_get_rate(isp_clk);
	//printf("%s %d end\r\n", __func__, *rate);
	return 0;
}

static int rtscam_isp_mfd_reset(struct rtscam_isp_mfd *mfd)
{
	//struct rtscam_isp_mfd_ex *mfd_ex;
	//int ret;

	//printf("%s\r\n", __func__);
	if (!mfd)
		return -EINVAL;

	//mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	//ret = reset_control_reset(mfd_ex->isp_reset);
	//if (ret)
	//	return ret;
	rts_sys_force_reset(FORCE_RESET_ISP);
	udelay(1);

	return 0;
}

static int rtscam_isp_mfd_change_clk_rate(
			struct rtscam_isp_mfd *mfd, unsigned long *rate)
{
	struct rtscam_isp_mfd_ex *mfd_ex;

	//isp_info("%s\r\n", __func__);
	if (!mfd)
		return -EINVAL;

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	__mfd_set_clk_rate(mfd_ex, rate);

	return 0;
}

static int rtscam_isp_mfd_set_clk(struct rtscam_isp_mfd *mfd, int enable)
{
	struct rtscam_isp_mfd_ex *mfd_ex;
	unsigned long rate = DEFAULT_MFD_ISP_CLK;

	if (!mfd)
		return -EINVAL;

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	//dbg_printf("%s 0x%08x %d\r\n", __func__, mfd_ex, enable);
	if (enable) {
		if (!atomic_read_isp(&mfd_ex->isp_clk_refcnt))
			__mfd_set_clk_rate(mfd_ex, &rate);

		atomic_inc(&mfd_ex->isp_clk_refcnt);


		clk_prepare_enable(mfd_ex->isp_clk);


	} else {
		//WARN_ON(!atomic_read(&mfd_ex->isp_clk_refcnt));
		if (!atomic_read_isp(&mfd_ex->isp_clk_refcnt))
			isp_error("%s mfd clk refcnt==0 error\r\n", __func__);
		atomic_dec(&mfd_ex->isp_clk_refcnt);
		if (!atomic_read_isp(&mfd_ex->isp_clk_refcnt))
			clk_disable_unprepare(mfd_ex->isp_clk);
	}

	return 0;
}

static int rtscam_isp_mfd_get_child_res(struct rtscam_isp_mfd *mfd,
					enum RTS_MFD_MODUAL_ID id,
					struct rtscam_isp_mfd_resource *res)
{
	int ret = 0;
	//struct device_node *node;
	struct rtscam_isp_mfd_ex *mfd_ex;

	if (!mfd || !res)
		return -EINVAL;

	//isp_info("%s\r\n", __func__);
	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);
	//node = child_dev->of_node;

	//if (of_device_is_compatible(node, "realtek,rts3915-isp")) {
		res->io_start = mfd_ex->res.io_start +
					mfd_regs[RTS_MFD_MODUAL_ID_ISP].base;
		res->io_size = mfd_regs[RTS_MFD_MODUAL_ID_ISP].size;
	//} else {
	//	ret = -EINVAL;
	//}

	return ret;
}

static void rtscam_isp_mfd_write_reg(struct rtscam_isp_mfd *mfd,
			u8 id, u32 reg, u32 val)
{
	struct rtscam_isp_mfd_ex *mfd_ex;

	//WARN_ON(!mfd);
	if (id >= RTS_MFD_MODUAL_ID_RESERVED) {
		rtsprintk(RTS_TRACE_ERROR,
				"mfd write invalid modual(%d)\n", id);
		return;
	}

	if (reg >= mfd_regs[id].size) {
		rtsprintk(RTS_TRACE_ERROR, "mfd write invalid reg(%d %d)\n",
				id, reg);
		return;
	}

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	//iowrite32(cpu_to_le32(val), mfd_ex->reg_base + mfd_regs[id].base + reg);
	REG_W32((u32)(mfd_ex->reg_base) + mfd_regs[id].base + reg, val);
}

static u32 rtscam_isp_mfd_read_reg(struct rtscam_isp_mfd *mfd, u8 id, u32 reg)
{
	struct rtscam_isp_mfd_ex *mfd_ex;

	//WARN_ON(!mfd);

	if (id >= RTS_MFD_MODUAL_ID_RESERVED) {
		isp_error("mfd read invalid modual(%d)\r\n", id);
		return -EINVAL;
	}

	if (reg >= mfd_regs[id].size) {
		isp_error("mfd read invalid reg(%d %d)\r\n", id, reg);
		return -EINVAL;
	}

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);
	//printf("0x%08x 0x%08x 0x%08x\r\n",(u32)mfd_ex->reg_base, mfd_regs[id].base,  reg);
	return REG_R32((u32)mfd_ex->reg_base + mfd_regs[id].base + reg);
}

/*
static void rtscam_isp_mfd_wake_irq_thread(
			struct rtscam_isp_mfd *mfd, void *data)
{
	struct rtscam_isp_mfd_ex *mfd_ex;

	if (!mfd || !data)
		return;

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	irq_wake_thread(mfd_ex->irq, data);
}
*/

static int rtscam_isp_mfd_register_irq(struct rtscam_isp_mfd *mfd, void *master,
			irq_ops ops, irq_ops thread_ops)
{
	struct rtscam_isp_mfd_ex *mfd_ex;
	struct rtscam_isp_mfd_irq_node *irq;
	struct rtscam_isp_mfd_irq_node *irq_thread;

	isp_info("%s\r\n", __func__);
	if (!mfd || !ops)
		return -EINVAL;

	mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	irq = rts_malloc(sizeof(*irq));
	if (!irq)
		return -ENOMEM;

	INIT_LIST_HEAD(&irq->list);
	irq->master = master;
	irq->ops = ops;
	list_add_tail(&irq->list, &mfd_ex->irq_ops);

	if (!thread_ops)
		return 0;

	irq_thread = rts_malloc(sizeof(*irq_thread));
	if (!irq_thread) {
		rts_free(irq);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&irq_thread->list);
	irq_thread->master = master;
	irq_thread->ops = thread_ops;
	list_add_tail(&irq_thread->list, &mfd_ex->irq_thread_ops);

	return 0;
}

static int rtscam_isp_mfd_check_clk(struct rtscam_isp_mfd_ex *mfd_ex)
{
	//WARN_ON(!mfd_ex);

	return atomic_read_isp(&mfd_ex->isp_clk_refcnt);
}

static void rtscam_isp_mfd_irq(void)
{
	struct rtscam_isp_mfd_irq_node *item;
	struct rtscam_isp_mfd_ex *mfd_ex = &gbl_isp_mfd_ex;
	int ret;

	if (!rtscam_isp_mfd_check_clk(mfd_ex))
		return;

	//WARN_ON(list_empty(&mfd_ex->irq_ops));
	//printf("%s\r\n", __func__);
	list_for_each_entry(item, &mfd_ex->irq_ops, list, struct rtscam_isp_mfd_irq_node) {
		ret = item->ops(item->master);
		if (ret == IRQ_NONE)
			continue;
		return;
	}
	return;
}

/*
static irqreturn_t rtscam_isp_mfd_irq_thread(int irq, void *data)
{
	struct rtscam_isp_mfd_irq_node *item;
	struct rtscam_isp_mfd_ex *mfd_ex = data;
	int ret;

	if (list_empty(&mfd_ex->irq_thread_ops))
		return IRQ_NONE;

	if (!rtscam_isp_mfd_check_clk(mfd_ex))
		return IRQ_NONE;

	list_for_each_entry(item, &mfd_ex->irq_thread_ops, list, struct rtscam_isp_mfd_irq_node) {
		ret = item->ops(item->master);
		if (ret == IRQ_NONE)
			continue;
		return ret;
	}
	return ret;
}

static int rtscam_isp_mfd_parse_region(struct rtscam_isp_mfd_reg *reg,
				   struct device_node *np)
{
	int ret;

	ret = of_property_read_u32_index(np, "reg", 0, &reg->base);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR, "fail to get reg address\n");
		return ret;
	}
	ret = of_property_read_u32_index(np, "reg", 1, &reg->size);
	if (ret) {
		rtsprintk(RTS_TRACE_ERROR, "fail to get reg size\n");
		return ret;
	}

	return 0;
}
*/

static int rtscam_isp_mfd_parse_regs(struct rtscam_isp_mfd_ex *isp_mfd_ex)
{
	/*struct device_node *np = isp_mfd_ex->dev->of_node;
	struct device_node *node;
	int ret;
	int i;

	for (i = 0; i < 4; i++) {
		node = of_parse_phandle(np, "reg-region", i);
		if (!node) {
			rtsprintk(RTS_TRACE_DEBUG,
				  "there is no reg-region for mfd[%d]\n", i);
			return -EINVAL;
		}

		ret = rtscam_isp_mfd_parse_region(&mfd_regs[i], node);
		if (ret) {
			rtsprintk(RTS_TRACE_ERROR,
				"fail to get mfd reg range[%d]\n", i);
			return ret;
		}

		of_node_put(node);
		rtsprintk(RTS_TRACE_INFO, "mfd reg-region[%d]: <0x%x 0x%x>\n",
			i, mfd_regs[i].base, mfd_regs[i].size);
	}*/

	mfd_regs[0].base =     0x0; mfd_regs[0].size = 0x100000;
	mfd_regs[1].base =     0x0; mfd_regs[1].size = 0x12000;
	mfd_regs[2].base = 0x12000; mfd_regs[2].size =  0x1000;
	mfd_regs[3].base =  0xb000; mfd_regs[3].size =  0x1000;

	for (int i = 0; i < 4; i++) {
		isp_info("mfd_regs[%d]: <0x%x 0x%x>\r\n", i, mfd_regs[i].base, mfd_regs[i].size);
	}

	return 0;
}

int rtscam_isp_mfd_probe(void)
{
	int irq;
	void *base;
	//struct resource *res;
	//const struct isp_mfd_cell_info *info;
	struct rtscam_isp_mfd_ex *isp_mfd_ex;
	int ret;

	//isp_info("%s\r\n", __func__);

	//info = of_device_get_match_data(&pdev->dev);
	//if (!info)
	//	return -EINVAL;
	//info = &rts3915_mfd_info;
	//irq = platform_get_irq(pdev, 0);
	//if (irq < 0) {
	//	rtsprintk(RTS_TRACE_ERROR, "can not found irq num\n");
	//	return -ENODEV;
	//}
	irq = VIDEOIN_IRQn;
	//res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	//if (!res) {
	//	rtsprintk(RTS_TRACE_ERROR, "Missing platform resource data\n");
	//	return -ENODEV;
	//}
	//base = devm_ioremap_resource(&pdev->dev, res);
	//if (IS_ERR(base)) {
	//	rtsprintk(RTS_TRACE_ERROR, "Couldn't ioremap resource\n");
	//	return PTR_ERR(base);
	//}
	base = (void*)ISP_BASE;

	//isp_mfd_ex = devm_kzalloc(&pdev->dev, sizeof(*isp_mfd_ex), GFP_KERNEL);
	//if (!isp_mfd_ex) {
	//	rtsprintk(RTS_TRACE_ERROR,
	//		  "Couldn't allocate rts camera isp object\n");
	//	return -ENOMEM;
	//}
	isp_mfd_ex = &gbl_isp_mfd_ex;

	//isp_mfd_ex->isp_clk = devm_clk_get(&pdev->dev, "isp_clk");
	isp_mfd_ex->isp_clk = clk_get("isp_clk");
	if (IS_ERR(isp_mfd_ex->isp_clk)) {
		rtsprintk(RTS_TRACE_ERROR, "mfd get isp clk fail\n");
		return -EINVAL;
	}

	//isp_mfd_ex->isp_reset = reset_control_get(&pdev->dev, "isp_reset");
	//if (IS_ERR(isp_mfd_ex->isp_reset)) {
	//	rtsprintk(RTS_TRACE_ERROR, "mfd get isp reset fail\n");
	//	return -EINVAL;
	//}

	INIT_LIST_HEAD(&isp_mfd_ex->irq_ops);
	INIT_LIST_HEAD(&isp_mfd_ex->irq_thread_ops);
	//ret = devm_request_threaded_irq(&pdev->dev, irq,
	//			rtscam_isp_mfd_irq, rtscam_isp_mfd_irq_thread,
	//			IRQF_SHARED, RTS_ISP_MFD_DRV_NAME, isp_mfd_ex);
	//if (ret) {
	//	rtsprintk(RTS_TRACE_ERROR, "request rts isp mfd irq fail\n");
	//	return ret;
	//}
	RLX_ClearPendingIRQ(VIDEOIN_IRQn);
	RLX_SetVideoInIrqVector(VIDEOIN_ID_MFD, (u32)rtscam_isp_mfd_irq);
	RLX_EnableVideoInIRQ(VIDEOIN_ID_MFD);


	atomic_set_isp(&isp_mfd_ex->isp_clk_refcnt, 0);

	isp_mfd_ex->reg_base = base;
	isp_mfd_ex->res.io_start = (int)base;//&(~0xA0000000);  //res->start;
	isp_mfd_ex->res.io_size = 0x100000;  //resource_size(res);
	isp_mfd_ex->mfd.get_child_resource = rtscam_isp_mfd_get_child_res;
	isp_mfd_ex->mfd.register_irq = rtscam_isp_mfd_register_irq;
	//isp_mfd_ex->mfd.wake_irq_thread = rtscam_isp_mfd_wake_irq_thread;
	isp_mfd_ex->mfd.change_clk_rate = rtscam_isp_mfd_change_clk_rate;
	isp_mfd_ex->mfd.set_clk = rtscam_isp_mfd_set_clk;
	isp_mfd_ex->mfd.reset = rtscam_isp_mfd_reset;
	isp_mfd_ex->mfd.write_reg = rtscam_isp_mfd_write_reg;
	isp_mfd_ex->mfd.read_reg = rtscam_isp_mfd_read_reg;
	//isp_mfd_ex->dev = &pdev->dev;
	isp_mfd_ex->irq = irq;
	//platform_set_drvdata(pdev, &isp_mfd_ex->mfd);
	//printf("%s mfd reg: 0x%x(0x%x) irq:%d\r\n",__func__, (unsigned int)isp_mfd_ex->reg_base, (unsigned int)isp_mfd_ex->res.io_size, irq);


#if CONFIG_FPGA // FPGA
	isp_mfd_ex->is_fpga = TRUE;  //of_machine_is_compatible("realtek,rts_fpga");

#else  // ASIC // PXP
	isp_mfd_ex->is_fpga = FALSE;  //of_machine_is_compatible("realtek,rts_fpga");
#endif


	ret = rtscam_isp_mfd_parse_regs(isp_mfd_ex);
	if (ret) {
		isp_error("%s mfd parse reg region fail\r\n", __func__);
		return ret;
	}

	//return devm_mfd_add_devices(&pdev->dev, -1, info->cells, info->num,
	//			    NULL, 0, NULL);
	return RT_OK;
}

int rtscam_isp_mfd_remove(void)
{
	struct rtscam_isp_mfd_ex *mfd_ex=&gbl_isp_mfd_ex;
	//struct rtscam_isp_mfd *mfd = &gbl_isp_mfd_ex.mfd;  //platform_get_drvdata(pdev);
	struct rtscam_isp_mfd_irq_node *item;
	struct rtscam_isp_mfd_irq_node *next;

	//mfd_ex = container_of(mfd, struct rtscam_isp_mfd_ex, mfd);

	list_for_each_entry_safe(item, next, &mfd_ex->irq_ops, list, struct rtscam_isp_mfd_irq_node) {
		list_del_init(&item->list);
#ifdef _DEBUG_MEM_
		isp_info("%s irq_ops rts_free 0x%08x 0x%08x \r\n", __func__, &item->list, item);
#endif
		rts_free(item);
	}

	list_for_each_entry_safe(item, next, &mfd_ex->irq_thread_ops, list, struct rtscam_isp_mfd_irq_node) {
		list_del_init(&item->list);
#ifdef _DEBUG_MEM_
		isp_info("%sirq_thread_ops  rts_free 0x%08x 0x%08x \r\n", __func__, &item->list, item);
#endif
		rts_free(item);
	}

	//reset_control_put(mfd_ex->isp_reset);

	return 0;
}

//static const struct of_device_id rtscam_isp_mfd_ids[] = {
//	{ .compatible = "realtek,rts3915-isp-mfd", .data = &rts3915_mfd_info},
//	{ /* sentinel */ },
//};
//
//static struct platform_driver rtscam_isp_mfd_driver = {
//	.driver = {
//		.name = RTS_ISP_MFD_DRV_NAME,
//		.owner = THIS_MODULE,
//		.of_match_table = of_match_ptr(rtscam_isp_mfd_ids),
//	},
//	.probe = rtscam_isp_mfd_probe,
//	.remove = rtscam_isp_mfd_remove,
//};
//
//module_platform_driver(rtscam_isp_mfd_driver);
//
//MODULE_DESCRIPTION("Realsil isp device driver");
//MODULE_AUTHOR("Grant Shen <grant_shen@realsil.com.cn>");
//MODULE_LICENSE("GPL v2");
//MODULE_VERSION("0.1.0");
//MODULE_ALIAS("platform:" RTS_ISP_MFD_DRV_NAME);

