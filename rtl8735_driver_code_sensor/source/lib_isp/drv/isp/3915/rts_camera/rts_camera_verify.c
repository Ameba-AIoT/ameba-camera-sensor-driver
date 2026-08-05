/*
 * convert image device driver (kernel module)
 *
 * Realtek Semiconductor Corp.
 *
 * rts_camera_verify.c
 *
 * Copyright (C) 2019      Wil_shi<wil_shi@realsil.com.cn>
 */

#define TAG	"VERIFY"


#include "cmsis_os2.h"
#include <errno.h>
#include <linux/_errno.h>
#include "rt_types.h"
#include "rt_util.h"
#include <reset/reset-rts3915.h>
#include <reset/reset-rtsmem3915.h>
#include <media/videobuf2-core.h>
#include <rtscamkit.h>
#include "linux/rts_camera_soc.h"
#include "rts_camera_zoom.h"
#include "rts_camera_verify_reg.h"
//#include "rts_camera_isp_clk.h"
#include "rts_camera_isp_mfd.h"
#include "rts_camera.h"
#include "rts_hw_id.h"
#include "rlx_reg.h"
#include "rtx_mutex.h"
#include "rt_time.h"

#define RTS_VERIFY_LOCATION_LDC		0x10   /*select ldc for verify*/
#define RTS_VERIFY_DUMMY_LINE_CONFIG	200


#define RTS_VERIFY_DRV_NAME		"rts_verify"
#define RTS_VERIFY_DEV_NAME		"rtsverify"

struct rtscam_verify {
	//struct device *dev;
	//void *hwregs;
	//unsigned long iobaseaddr;
	//unsigned int iosize;
	struct rtscam_isp_mfd *mfd;

	u32 sel_reg_val;

	struct rtscam_ge_device *jdev;

	struct rtscam_zoom_verify zoom_verify;
};

struct rtscam_verify gbl_rverify={0};

static u32 rtscam_verify_read_reg(struct rtscam_verify *rverify, off_t reg)
{
	//WARN_ON(!rverify);

	//return REG_R32(rverify->hwregs + reg);
	return rverify->mfd->read_reg(rverify->mfd,
			RTS_MFD_MODUAL_ID_VERIFY, reg);
}

static void rtscam_verify_write_reg(struct rtscam_verify *rverify,
				u32 value, off_t reg)
{
	//WARN_ON(!rverify);

	//REG_W32(rverify->hwregs + reg, value);
	rverify->mfd->write_reg(rverify->mfd,
			RTS_MFD_MODUAL_ID_VERIFY, reg, value);
}

static int rtscam_verify_set_isp_clock(struct rtscam_verify *verify, int enable)
{
	printf("%s %d\r\n", __func__, enable);
	return verify->mfd->set_clk(verify->mfd, enable);
}

static int __check_verify_info(struct rtscam_verify_info *vinfo)
{
	if (!vinfo)
		return -EINVAL;

	if (!vinfo->width || !vinfo->height || !vinfo->phyaddr)
		return -EINVAL;

	if (!vinfo->scale_v || !vinfo->scale_h ||
			vinfo->scale_h > 15 || vinfo->scale_v > 15) {
		rtsprintk(RTS_TRACE_ERROR, "verify scale is invalid\n");
		return -EINVAL;
	}

	if (vinfo->fmt != RTS_VERIFY_FMT_YUV422_SEMI &&
			vinfo->fmt != RTS_VERIFY_FMT_YUV422_INTER) {
		rtsprintk(RTS_TRACE_ERROR, "verify fmt is not supportted\n");
		return -EINVAL;
	}

	return 0;
}

static int __wait_verify_finish(struct rtscam_verify *rverify)
{
	int cnt = 0;

	while (cnt++ < 200) {
		if (rtscam_verify_read_reg(
				rverify, RTS_VERIFY_INT_FLAG))
			break;
		if (cnt == 200)
			return -EINVAL;
		mdelay(10);
	}
	rtscam_verify_write_reg(rverify, 0x1, RTS_VERIFY_INT_FLAG);
	return 0;
}

static int rtscam_verify_set_info(struct rtscam_zoom_verify *zoom_verify,
		struct rtscam_verify_info *vinfo)
{
	struct rtscam_verify *rtscam_verify;
	u32 src_w, src_h, src_len;
	u32 src_y, src_uv;

	if (!zoom_verify)
		return -EINVAL;

	if (__check_verify_info(vinfo)) {
		rtsprintk(RTS_TRACE_ERROR, "verify info is not supportted\n");
		return -EINVAL;
	}

	rtscam_verify = container_of(zoom_verify,
				struct rtscam_verify, zoom_verify);

	src_w = vinfo->width;
	src_h = vinfo->height;
	src_len = src_w * src_h;
	src_y = vinfo->phyaddr;
	src_uv = src_y + src_len;

	rtscam_verify_set_isp_clock(rtscam_verify, 1);

	rtscam_verify_write_reg(rtscam_verify,
			RTS_VERIFY_LOCATION_LDC, RTS_VERIFY_SEL);
	rtscam_verify_write_reg(rtscam_verify, src_y, RTS_VERIFY_Y_DDR_ADDR0);
	rtscam_verify_write_reg(rtscam_verify, src_y, RTS_VERIFY_Y_DDR_ADDR1);

	if (vinfo->fmt == RTS_VERIFY_FMT_YUV422_INTER) {
		rtscam_verify_write_reg(rtscam_verify,
				src_len * 2, RTS_VERIFY_Y_DDR_LEN);
	} else if (vinfo->fmt == RTS_VERIFY_FMT_YUV422_SEMI) {
		rtscam_verify_write_reg(rtscam_verify,
				src_len, RTS_VERIFY_Y_DDR_LEN);
		rtscam_verify_write_reg(rtscam_verify,
				src_len, RTS_VERIFY_UV_DDR_LEN);

		rtscam_verify_write_reg(rtscam_verify,
				src_uv, RTS_VERIFY_UV_DDR_ADDR0);
		rtscam_verify_write_reg(rtscam_verify,
				src_uv, RTS_VERIFY_UV_DDR_ADDR1);
	}

	rtscam_verify_write_reg(rtscam_verify, 1, RTS_VERIFY_FRAME_NUM);
	rtscam_verify_write_reg(rtscam_verify,
			vinfo->fmt, RTS_VERIFY_FRAME_FORMAT);
	rtscam_verify_write_reg(rtscam_verify, (src_w - 1) | (src_h - 1) << 16,
			RTS_VERIFY_FRAME_SIZE);

	if (vinfo->scale_h > 1 || vinfo->scale_v > 1) {
		rtscam_verify_write_reg(rtscam_verify,
				(vinfo->scale_v << 4) | (vinfo->scale_h),
				RTS_VERIFY_SCALE_COEF);
		rtscam_verify_write_reg(rtscam_verify, 1, RTS_VERIFY_SCALE_EN);
	}

	rtscam_verify_write_reg(rtscam_verify, 0x1010, RTS_VERIFY_FRAME_CONFG0);
	rtscam_verify_write_reg(rtscam_verify,
				(RTS_VERIFY_DUMMY_LINE_CONFIG - 1) |
				(RTS_VERIFY_DUMMY_LINE_CONFIG - 1) << 16,
				RTS_VERIFY_FRAME_CONFG1);
	rtscam_verify_write_reg(rtscam_verify, 1, RTS_VERIFY_INT_FLAG);

	rtscam_verify_write_reg(rtscam_verify, 0x3d, RTS_VERIFY_CTRL);
	rtscam_verify_write_reg(rtscam_verify, 1, RTS_VERIFY_START_FLAG);

	if (__wait_verify_finish(rtscam_verify)) {
		rtsprintk(RTS_TRACE_ERROR, "wait verify finish fail\n");
		rtscam_verify_set_isp_clock(rtscam_verify, 0);
		return -EINVAL;
	}
	rtscam_verify_set_isp_clock(rtscam_verify, 0);
	return 0;
}

static int __verify_isp_reset(struct rtscam_verify *rverify)
{
	int ret;

	//rts_sys_force_reset(FORCE_RESET_ISP);
	ret = rverify->mfd->reset(rverify->mfd);
	if (ret)
		return ret;
	udelay(1);

	return 0;
}

static int rtscam_verify_reset_isp(struct rtscam_zoom_verify *zoom_verify)
{
	struct rtscam_verify *rverify;

	rverify = container_of(zoom_verify, struct rtscam_verify, zoom_verify);

	return __verify_isp_reset(rverify);
}

static int rtscam_verify_init(struct rtscam_zoom_verify *zoom_verify)
{
	struct rtscam_verify *rverify;

	rverify = container_of(zoom_verify, struct rtscam_verify, zoom_verify);

	rverify->sel_reg_val = rtscam_verify_read_reg(rverify, RTS_VERIFY_SEL);

	return 0;
}

static void rtscam_verify_cleanup(struct rtscam_zoom_verify *zoom_verify)
{
	struct rtscam_verify *rverify;

	rverify = container_of(zoom_verify, struct rtscam_verify, zoom_verify);

	rtscam_verify_write_reg(rverify, rverify->sel_reg_val, RTS_VERIFY_SEL);
}

static int rtscam_verify_register_subdev(struct rtscam_verify *rverify)
{
	struct rtscam_zoom_verify *zoom_verify = &rverify->zoom_verify;

	if (zoom_verify->master)
		return -EBUSY;

	memset(zoom_verify, 0, sizeof(*zoom_verify));
//	zoom_verify->dev = rverify->dev;

	zoom_verify->set_vinfo = rtscam_verify_set_info;
	zoom_verify->reset_isp = rtscam_verify_reset_isp;
	zoom_verify->init = rtscam_verify_init;
	zoom_verify->cleanup = rtscam_verify_cleanup;
	//zoom_verify->set_clock = rtscam_isp_set_isp_clock;

	return rtscam_zoom_register_verify(zoom_verify);
}

static int rtscam_verify_unregister_subdev(struct rtscam_verify *rverify)
{
	struct rtscam_zoom_verify *zoom_verify = &rverify->zoom_verify;

	if (!zoom_verify->master)
		return 0;

	return rtscam_zoom_unregister_verify(zoom_verify);
}

int rtscam_verify_probe(void)
{
	struct rtscam_verify *rverify;
//	struct resource *res;
//	void __iomem *base;
//	struct device *dev = &pdev->dev;
	struct rtscam_isp_mfd *mfd;
	int err = 0;

	isp_info("%s \r\n", __func__);

	mfd = rtscam_get_isp_mfd();  //dev_get_drvdata(dev->parent);
	if (!mfd)
		return -EINVAL;

	//rverify = devm_kzalloc(dev, sizeof(*rverify), GFP_KERNEL);
	//if (rverify == NULL) {
	//	rtsprintk(RTS_TRACE_ERROR,
	//		  "Couldn't allocate rts camera osd object\n");
	//	return -ENOMEM;
	//}
	rverify = &gbl_rverify;
	rverify->mfd = mfd;
	//rverify->hwregs = (void*)VERIFY_BASE;
	//rverify->iobaseaddr = VERIFY_BASE&(~0xA0000000);
	//rverify->iosize = 0x1000;

	//rverify->dev = get_device(dev);

//	platform_set_drvdata(pdev, rverify);

	err = __verify_isp_reset(rverify);
	if (err) {
		rtsprintk(RTS_TRACE_ERROR, "rtsverify reset fail\n");
		goto error;
	}
	rtscam_verify_register_subdev(rverify);
	return 0;

error:
//	if (rverify && rverify->dev) {
//		put_device(rverify->dev);
//		rverify->dev = NULL;
//	}
	return err;
}

int rtscam_verify_remove(void)
{
	struct rtscam_verify *rverify = &gbl_rverify;

	rtscam_verify_unregister_subdev(rverify);
//	put_device(rverify->dev);
//	rverify->dev = NULL;

	return 0;
}

//static struct platform_driver rtscam_verify_driver = {
//	.driver		= {
//		.name	= RTS_VERIFY_DRV_NAME,
//		.owner	= THIS_MODULE,
//	},
//	.probe		= rtscam_verify_probe,
//	.remove		= rtscam_verify_remove,
//};
//
//module_platform_driver(rtscam_verify_driver);
//
//MODULE_DESCRIPTION("Realsil Verify device driver");
//MODULE_AUTHOR("Wil Shi <wil_shi@realsil.com.cn>");
//MODULE_LICENSE("GPL v2");
//MODULE_VERSION("0.1.1");
//MODULE_ALIAS("platform:" RTS_VERIFY_DRV_NAME);
