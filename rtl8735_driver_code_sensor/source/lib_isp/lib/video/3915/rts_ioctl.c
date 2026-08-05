/*
 * Realtek Semiconductor Corp.
 *
 * librtspigeon/src/buffer.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#include <stdio.h>
#include <stdarg.h>

#include "cmsis_os2.h"

#include "linux/v4l2-osdep.h"
#include <isp_poll.h>
#include "rts_ioctl.h"
//#include "isp_cmd.h"
#include <linux/rts_camera_isp.h>
#include <linux/rts_camera_md.h>
#include <isp_msg_buf.h>
#include <isp_log.h>
#include "rt_time.h"

extern long rtscam_video_do_ioctl(int fd, unsigned int cmd, void *arg);

//extern int rtstream_do_ioctl(int fd, unsigned int cmd, void *arg);
//extern long rtscam_jpgenc_ioctl(int fd, unsigned int cmd, void *arg);
//extern long rtscam_hx280_ioctl(int fd, unsigned int cmd, void *arg);
extern long rtscam_osd2_ioctl(int fd, unsigned int cmd, void *arg);

int rts_ioctl(int fd, unsigned long int request, ...)
{
	void *arg;
	va_list ap;
	int result = 0;

//fprintf(stdout, "rts_ioctl\n");

	va_start(ap, request);
	arg = va_arg(ap, void *);
	switch (fd)
	{
		case ID_RTS_ISP_DEV:  // /dev/rtsisp
			result = rtscam_isp_ioctl(request, (int)arg);
			break;

		case ID_RTS_VIDEO_DEV1:  // /dev/video51
		case ID_RTS_VIDEO_DEV2:  // /dev/video52
		case ID_RTS_VIDEO_DEV3:  // /dev/video53
		case ID_RTS_VIDEO_DEV4:  // /dev/video54
		case ID_RTS_NN_DEV:  	// /dev/video61
			result = rtscam_video_do_ioctl(fd, request, arg);
			break;

		case ID_RTS_MD2_DEV:  // /dev/rtsmd
			result = rtscam_isp_md_ioctl(fd, request, arg);
			break;

		case 1001:  // /dev/rtscamctrl
		case 1004:  // /dev/rtstream
			//if (_IOC_TYPE(request) == 'r')  //RTSCAMIOC_XXX
			//	result = rtstream_do_ioctl(fd, request, arg);
			//else
			//	result = rtscam_video_do_ioctl(fd, request, arg);
			break;
		case 1003:  // /dev/rtscam
			//result = rtstream_do_ioctl(fd, request, arg);
			break;
		case 1005:  // /dev/rtsjpgenc
			//result = rtscam_jpgenc_ioctl(fd, request, arg);
			break;
		case 1006:  // /dev/rtshx280enc
			//result = rtscam_hx280_ioctl(fd, request, arg);
			break;
		case 1007:  // /dev/rtsosd2
			result = rtscam_osd2_ioctl(fd, request, arg);
			break;
		default:
			printf("rts_ioctl error fd:%d\n", fd);
			break;
	}

	va_end(ap);

	return result;

}

extern int isp_uds_message_simple(uint32_t isp_id, uint32_t mod_id,
			   uint32_t action, void *data, uint32_t len);

//call from driver into user space
int rts_rev_ioctl(void *data, void *buf, int len)
{
	struct isp_msg_hdr *hdr = data;

	return isp_uds_message_simple(hdr->isp_id, hdr->mod_id, hdr->action,
					      buf, len);
}

int rts_epoll_wait(int fd)
{
	int ret = -1;

	switch (fd)
	{
		case ID_RTS_ISP_DEV:  // /dev/rtsisp
			ret = rts_ioctl(fd, RTSISP_IOC_POLL, osWaitForever);
			break;
		default:
			isp_error("dev:%d not support poll\r\n", fd);
			break;
	}

	return ret;
}

#define RTS_ISP_CTRL_DEV	"/dev/rtscamctrl"
#define RTS_ISP_MEM_DEV		"/dev/rtsmem"
#define RTS_ISP_SOC_DEV		"/dev/rtscam"
#define RTS_ISP_STRM_DEV	"/dev/rtstream"
#define RTS_ENC_MJPG_DEV	"/dev/rtsjpgenc"
#define RTS_ENC_H264_DEV	"/dev/rtshx280enc"
#define RTS_ENC_OSD2_DEV	"/dev/rtsosd2"

#define RTS_ISP_DEV			"/dev/rtsisp"

#define RTS_VIDEO_DEV1		"/dev/video51"
#define RTS_VIDEO_DEV2		"/dev/video52"
#define RTS_VIDEO_DEV3		"/dev/video53"
#define RTS_VIDEO_DEV4		"/dev/video54"
#define RTS_NN_DEV			"/dev/video61"

#define RTS_MD2_DEV			"/dev/rtsmd"

#define RTS_UDS_SOCK		"/var/run/rtsisp.sock"

#define RTS_POLL_WQ			"/poll/wq"
#define RTS_POLL_TRIG		"/poll/trig"

extern int rtscam_isp_open(void);
int rts_open(const char *pathname)
{
	isp_info(" %s: %s \r\n",  __func__, pathname);
	if (!strcmp(pathname, RTS_ISP_DEV)) {
		rtscam_isp_open();
		return ID_RTS_ISP_DEV;
	}

	if (!strcmp(pathname, RTS_VIDEO_DEV1)) {
		return ID_RTS_VIDEO_DEV1;
	}
	if (!strcmp(pathname, RTS_VIDEO_DEV2)) {
		return ID_RTS_VIDEO_DEV2;
	}
	if (!strcmp(pathname, RTS_VIDEO_DEV3)) {
		return ID_RTS_VIDEO_DEV3;
	}
	if (!strcmp(pathname, RTS_VIDEO_DEV4)) {
		return ID_RTS_VIDEO_DEV4;
	}
	if (!strcmp(pathname, RTS_NN_DEV)) {
		return ID_RTS_NN_DEV;
	}

	if (!strcmp(pathname, RTS_MD2_DEV)) {
		rtscam_isp_md_open();
		return ID_RTS_MD2_DEV;
	}

	if (!strcmp(pathname, RTS_UDS_SOCK)) {
		return ID_RTS_UDS_SOCK;
	}

	if (!strcmp(pathname, RTS_POLL_WQ)) {
		return ID_RTS_POLL_WQ;
	}
	if (!strcmp(pathname, RTS_POLL_TRIG)) {
		return ID_RTS_POLL_TRIG;
	}

/*
	if (!strcmp(pathname, RTS_ISP_CTRL_DEV))
		return 1001;
	if (!strcmp(pathname, RTS_ISP_MEM_DEV))
		return 1002;
	if (!strcmp(pathname, RTS_ISP_SOC_DEV))
		return 1003;
	if (!strcmp(pathname, RTS_ISP_STRM_DEV))
		return 1004;
	if (!strcmp(pathname, RTS_ENC_MJPG_DEV))
		return 1005;
	if (!strcmp(pathname, RTS_ENC_H264_DEV))
		return 1006;
*/
	if (!strcmp(pathname, RTS_ENC_OSD2_DEV))
		return 1007;

	return -1;  //open failed
}
extern int rtscam_isp_close(void);
int rts_close(int fd)
{
	if (fd == ID_RTS_ISP_DEV)
		rtscam_isp_close();

	if (fd == ID_RTS_MD2_DEV)
		rtscam_isp_md_close();

	return 0;
}

long rts_get_pgsize(void)
{
	return 4096;  //sysconf(_SC_PAGE_SIZE);
}

/*
void *rts_reg_mmap(unsigned long base, unsigned int size)
{
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	void *preg = NULL;

	if (fd < 0)
		return NULL;

fprintf(stdout, "rts_reg_mmap\n");

	preg = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
	rts_close(fd);
	fd = -1;
	if (preg == MAP_FAILED)
		return NULL;
	return preg;
}

void rts_reg_munmap(void *preg, unsigned int size)
{
fprintf(stdout, "rts_reg_munmap\n");
	if (preg && size)
		munmap(preg, size);
}

void *rts_mmap(int fd, unsigned long base, unsigned int size)
{
	void *preg = NULL;

	if (fd < 0)
		return NULL;

fprintf(stdout, "rts_mmap\n");
	preg = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
	rts_close(fd);
	fd = -1;
	if (preg == MAP_FAILED)
		return NULL;
	return preg;
}

void rts_munmap(void *preg, unsigned int size)
{
fprintf(stdout, "rts_munmap\n");
	if (preg && size)
		munmap(preg, size);
}
*/

int rts_usleep(unsigned int usec)
{
	udelay(usec);
	return 0;
}

// int rts_isp_send_cmd(struct rtscam_soc_cmd_stru *cmd, unsigned int timeout)
// {
//         int ret=0;

//         isp_send_cmd((struct isp_cmd_data*)cmd);

//         return ret;
// }

// int rts_waitevent(unsigned int *sem, unsigned int usec)
// {
//         int ret = -1;
//         *sem = (unsigned int)xSemaphoreCreateBinary();
//         if (!*sem) {
//                 ret = 0;
//                 goto exit;
//         }

//         xSemaphoreTake((SemaphoreHandle_t)*sem, ( TickType_t ) configTICK_RATE_HZ*usec/1000000);
//         vSemaphoreDelete((SemaphoreHandle_t)*sem);

// exit:
//         return ret;
// }

// int rts_setevent(unsigned int sem)
// {
//         if((SemaphoreHandle_t)sem != NULL) xSemaphoreGive((SemaphoreHandle_t)sem);
//         return -1;
// }

// int rts_irqsetevent(unsigned int sem)
// {
//         static BaseType_t xHigherPriorityTaskWoken;
//         int ret=0;

//         if((SemaphoreHandle_t)sem == NULL) goto exit;

//         xSemaphoreGiveFromISR((SemaphoreHandle_t)sem, &xHigherPriorityTaskWoken);
//         if (xHigherPriorityTaskWoken==pdTRUE) ret=-1;

// exit:
//         return ret;
// }

// int rts_reg_isr_cb(BOOL en, int id, isp_callback_t callback, void *para)
// {
//         int ret=0;
//         hal_isp_en_mcu_interrupt(en , id, callback, para);

//         return ret;
// }

// int rtsTimezone=8;
// int rts_gettime(struct tm *ptime)
// {
//        struct tm tm_now = sntp_gen_system_time(rtsTimezone);

//        ptime->tm_hour = tm_now.tm_hour;
//        ptime->tm_min = tm_now.tm_min;
//        ptime->tm_sec = tm_now.tm_sec;
//        ptime->tm_mday = tm_now.tm_mday;
//        ptime->tm_mon = tm_now.tm_mon;
//        ptime->tm_year = tm_now.tm_year;

//         return -1;
// }

