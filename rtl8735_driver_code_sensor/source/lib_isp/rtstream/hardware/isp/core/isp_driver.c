/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rt_task.h"
#include "rts_ioctl.h"
#define ioctl rts_ioctl
#include <rts_camera_isp.h>
#include <isp_utils.h>
#include <isp_log.h>
#include <isp_stream.h>
#include <isp_driver.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_DRIVER

#define xioctl(fd, request, ...) \
({ \
	int ret; \
	ret = ioctl(fd, request, ##__VA_ARGS__); \
	if (ret == -1) \
		ret = -RTS_ISP_EPERM; \
	ret; \
})

void *isp_io_base;
static int g_driver_fd = -1;

static inline int driver_get_fd(void)
{
	return g_driver_fd;
}

static int driver_set_io_base(int fd)
{
	int ret;
	uint32_t start;
	uint32_t size;
	void *io_base;

	if (fd < 0)
		return -RTS_ISP_EINVAL;

	ret = xioctl(fd, RTSISP_IOC_GET_IO_START, &start);
	if (ret)
		goto err;
	//debug("io start is 0x%x\r\n", start);
	ret = xioctl(fd, RTSISP_IOC_GET_IO_SIZE, &size);
	if (ret)
		goto err;
	//debug("io size is 0x%x\r\n", size);
	io_base = isp_driver_mmap(start, size);
	if (!io_base) {
		ret = -RTS_ISP_ENOTREADY;
		goto err;
	}
	//debug("map io to %p\r\n", io_base);

	isp_io_base = io_base;

	return RTS_ISP_OK;

err:
	isp_perror(ret, "map io fail");
	return ret;
}

static void driver_unset_io_base(int fd)
{
	int ret;
	uint32_t size;

	if (fd < 0)
		return;

	ret = xioctl(fd, RTSISP_IOC_GET_IO_SIZE, &size);
	if (ret)
		return;

	isp_io_base = NULL;
}

int isp_driver_init(void)
{
	int fd;
	int ret;

	fd = rts_open("/dev/rtsisp");
	if (fd == -1)
		return -RTS_ISP_ENOTREADY;
	g_driver_fd = fd;

	//debug("%s fd: %d\n", __func__, fd);

	ret = isp_closexec(fd, 1);
	if (ret)
		goto out;
	ret = driver_set_io_base(fd);
	if (ret)
		goto out;
out:
	if (ret)
		isp_close(g_driver_fd);
	return ret;
}

void isp_driver_cleanup(void)
{
	driver_unset_io_base(g_driver_fd);
	isp_close(g_driver_fd);
}

//int isp_driver_stream_add(isp_poll_t p)
int isp_driver_stream_add(void *p)
{
	int ret;
	int fd;

	if (!p) {
		ret = -RTS_ISP_EINVAL;
		goto err;
	}
	fd = driver_get_fd();
	if (fd < 0) {
		ret = -RTS_ISP_ENOTREADY;
		goto err;
	}
	ret = isp_stream_client_add(p, fd);
	if (ret)
		goto err;
	isp_poll_set_fd_nonclose(p, fd, RTS_ISP_TRUE);

	debug("%s fd:%d ok\n", __func__, fd);

	return RTS_ISP_OK;
err:
	isp_perror(ret, "isp driver stream init fail");
	return ret;
}

int isp_driver_register_subdev(const struct rts_isp_info *info)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!info)
		return -RTS_ISP_EINVAL;

	ret = xioctl(fd, RTSISP_IOC_REG_SUBDEV, info);
	if (ret)
		isp_perror(ret, "register subdev fail");
	else
		debug("%s ok\r\n", __func__);

	return ret;
}

int isp_driver_unregister_subdev(void)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	ret = xioctl(fd, RTSISP_IOC_UNREG_SUBDEV);
	if (ret)
		isp_error("%s unregister subdev fail %d \r\n",__func__, ret);
	else
		isp_info("%s ok\r\n", __func__);
	return ret;
}

int isp_driver_set_power(const struct rts_isp_snr_pwr *pwr)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!pwr)
		return -RTS_ISP_EINVAL;

	return xioctl(fd, RTSISP_IOC_POWER, pwr);
}

int isp_driver_write_sync_regs(const struct rts_isp_sync_regs *regs)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!regs)
		return -RTS_ISP_EINVAL;

	return xioctl(fd, RTSISP_IOC_SYNC_WRITE, regs);
}

int isp_driver_init_statis(uint32_t size)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	return xioctl(fd, RTSISP_IOC_INIT_STATIS, &size);
}

int isp_driver_cleanup_statis(void)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	return xioctl(fd, RTSISP_IOC_CLEANUP_STATIS);
}

int isp_driver_get_statis_info(struct rts_isp_statis_info *info)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	return xioctl(fd, RTSISP_IOC_GET_STATIS_INFO, info);
}

int isp_driver_put_statis(uint32_t id)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	return xioctl(fd, RTSISP_IOC_PUT_STATIS, &id);
}

int isp_driver_i2c_read(struct rts_isp_i2c *i2c)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!i2c)
		return -RTS_ISP_EINVAL;

	ret = xioctl(fd, RTSISP_IOC_I2C_READ, i2c);
	if (ret)
		return ERR_ID_DRV_I2C_READ_FAIL;

	return RTS_ISP_OK;
}

int isp_driver_i2c_write(const struct rts_isp_i2c *i2c)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!i2c)
		return -RTS_ISP_EINVAL;

	ret = xioctl(fd, RTSISP_IOC_I2C_WRITE, i2c);
	if (ret)
		return ERR_ID_DRV_I2C_WRITE_FAIL;

	return RTS_ISP_OK;
}

int isp_driver_aphy_i2c_write(const struct rts_isp_i2c *i2c)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!i2c)
		return -RTS_ISP_EINVAL;

	ret = ioctl(fd, RTSISP_IOC_APHY_I2C_WRITE, i2c);
	if (ret)
		return ERR_ID_DRV_I2C_WRITE_FAIL;

	return RTS_ISP_OK;
}

int isp_driver_mem_alloc(uint32_t *phy_addr, uint32_t length, const char *info)
{
	int ret;
	int fd = driver_get_fd();
	struct rtscam_isp_mem_alloc_info alloc_info;

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;
	if (!phy_addr || !length || !info)
		return -RTS_ISP_EINVAL;

	alloc_info.length = length;
	isp_strlcpy(alloc_info.info, info, sizeof(alloc_info.info));
	ret = xioctl(fd, RTSISP_IOC_MEM_ALLOC, &alloc_info);
	if (ret)
		return ret;
	*phy_addr = alloc_info.phy_addr;

	return RTS_ISP_OK;
}

int isp_driver_mem_free(uint32_t phy_addr)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	ret = xioctl(fd, RTSISP_IOC_MEM_FREE, &phy_addr);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

void *isp_driver_mmap(uint32_t start, uint32_t size)
{
	int ret;
	void *virt;
	int fd = driver_get_fd();

	if (fd < 0) {
		ret = -RTS_ISP_ENOTREADY;
		goto err;
	}
	virt = (void*)(start);//|0xA0000000);
	return virt;

err:
	isp_perror(ret, "isp driver mmap start: 0x%x size: 0x%x fail",
		   start, size);
	return NULL;
}

int isp_driver_sel_pin_state(enum rts_isp_interface interface)
{
	int ret;
	int fd = driver_get_fd();
	enum rtscam_isp_pin_state state;

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	switch (interface) {
	case SNR_INTERFACE_NONE:
		state = PIN_STATE_NONE;
		break;
	case SNR_INTERFACE_DVP:
		state = PIN_STATE_DVP;
		break;
	case SNR_INTERFACE_MIPI:
		state = PIN_STATE_MIPI;
		break;
	default:
		state = PIN_STATE_NONE;
	}
	ret = xioctl(fd, RTSISP_IOC_SEL_PIN_STATE, &state);
	if (ret)
		return ret;

	return RTS_ISP_OK;
}

int isp_driver_notify_dynamic_fps(uint32_t fps)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	return xioctl(fd, RTSISP_IOC_NOTIFY_DYN_FPS, &fps);
}

int isp_driver_set_clk(enum isp_clock_type type, uint32_t *rate)
{
	int ret;
	struct rtscam_isp_clock clock;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	switch (type) {
	case CLK_INTERFACE:
		clock.type = CLOCK_INTERFACE;
		break;
	case CLK_ISP:
		clock.type = CLOCK_ISP;
		break;
	case CLK_MIPIOUT:
		clock.type = CLOCK_MIPIOUT;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	clock.rate = *rate;
	ret = xioctl(fd, RTSISP_IOC_SET_CLOCK, &clock);
	if (ret)
		return ret;
	*rate = clock.rate;
	return 0;

}

void isp_driver_isp_clk_get(void)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return;

	(void)xioctl(fd, RTSISP_IOC_GET_ISP_CLOCK, NULL);
}

void isp_driver_isp_clk_put(void)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return;

	(void)xioctl(fd, RTSISP_IOC_PUT_ISP_CLOCK, NULL);
}

int isp_driver_is_fpga(void)
{
	int fd = driver_get_fd();
	int is_fpga = 0;

	if (fd < 0)
		return 0;

	(void)xioctl(fd, RTSISP_IOC_IS_FPGA, &is_fpga);
	//printf("%s %d \r\n", __func__, is_fpga);
	return is_fpga;
}

void isp_driver_wait_event(enum isp_event event)
{
	int fd = driver_get_fd();
	enum rtscam_isp_event e;

	if (fd < 0)
		return;

	switch (event) {
	case ISP_DATA_START:
		e = RTSCAM_ISP_DATA_START;
		break;
	case ISP_FRAME_END:
		e = RTSCAM_ISP_FRAME_END;
		break;
	default:
		return;
	}

	(void)xioctl(fd, RTSISP_IOC_WAIT_EVENT, &e);
}

void isp_driver_sync_lock(int lock)
{
	int fd = driver_get_fd();

	if (fd < 0)
		return;

	(void)xioctl(fd, RTSISP_IOC_SYNC_LOCK, &lock);
}

int isp_driver_get_tnr_bit(void)
{
	int ret;
	uint32_t bit;
	int fd = driver_get_fd();

	if (fd < 0)
		return -RTS_ISP_ENOTREADY;

	ret = xioctl(fd, RTSISP_IOC_GET_TNR_BIT, &bit);
	if (ret)
		return ret;
	return bit;
}

int isp_driver_test_preview(uint32_t fps)
{
	int ret;
	int fd = driver_get_fd();

	if (fd < 0)
		return RTS_ISP_ENOTREADY;

	ret = xioctl(fd, RTSISP_IOC_TEST_PREVIEW, &fps);
	if (ret)
		isp_perror(ret, "test preview @%ufps fail", fps);
	else
		debug("%s ok\n", __func__);

	return ret;
}
