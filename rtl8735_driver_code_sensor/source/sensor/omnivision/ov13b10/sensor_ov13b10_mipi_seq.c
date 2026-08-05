/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <sherry_cheng@realsil.com.cn>
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
// #include <pthread.h>
// #include <sys/mman.h>
#include <sensor_entry.h>
#include <rts_isp_sensor_lib.h>
#include "verify.h"

#if _OV13B10_12M_SEQ_SENSOR_

#define VERIFY_MODE VERIFY_RAW12_LOCATION
#define VERIFY_IMAGE_PATH "/mnt/%u.bin"
// #define VERIFY_BUF_ALLOC_IN_VOE
// #define SENSOR_WIDTH 3072
// #define SENSOR_HEIGHT 2048
#define SENSOR_WIDTH 2112
#define SENSOR_HEIGHT 1616
#define SENSOR_HTS 2400
#define SENSOR_VTS 1800 // VTS should be close to SENSOR_HEIGHT.
#define SENSOR_FPS 6
#define BIT_DEPTH SNR_12BIT

#define ISP_CLK SENSOR_HTS * SENSOR_VTS * SENSOR_FPS

#define SENSOR_DUMMY_PIXEL (SENSOR_HTS - SENSOR_WIDTH)
#define SENSOR_DUMMY_LINE (SENSOR_VTS - SENSOR_HEIGHT)

/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#define SUPPORTED_ISP_NUM 1

struct verify_status {
	// volatile int enable;
	// pthread_t thread;
	uint32_t buffer_addr;
	uint32_t buffer_size;
	uint32_t y_len;
	uint32_t uv_len;
};

static struct verify_status g_status[SUPPORTED_ISP_NUM];

static int verify_get_info(uint32_t isp_id,
			   struct rts_isp_sensor_info *info)
{
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	info->modes.mode[0].hdr = LINEAR_MODE;
	info->modes.mode[0].size.w = SENSOR_WIDTH;
	info->modes.mode[0].size.h = SENSOR_HEIGHT;
	info->modes.mode[0].fps = (float)ISP_CLK / SENSOR_HTS / SENSOR_VTS;
	info->modes.num = 1;

	info->i2c.i2c_id = 0;
	info->i2c.data_len = 1;
	info->i2c.addr_len = 1;

	info->cur_hdr_mode = LINEAR_MODE;

	up->num = 0;
	down->num = 0;

	return RTS_ISP_OK;
}

static int verify_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	debug("verify get fps %.1f init info\n", mode->fps);

	debug("fps: %u, pclk: %u, clk_div: %u, vts: %u\n",
	      fps_info->fps, fps_info->clk, fps_info->clk_div, fps_info->vts);

	info->interface.interface = SNR_INTERFACE_NONE;
	info->interface.bit_depth = BIT_DEPTH;
	info->mipi_behavor = NONE_HDR;

	info->size.w = SENSOR_WIDTH;
	info->size.h = SENSOR_HEIGHT;
	info->start.x = 0;
	info->start.y = 0;

	info->hts = SENSOR_HTS;
	info->pclk = ISP_CLK;
	info->min_vts = SENSOR_VTS;
	info->max_vts = 65535 - SENSOR_VTS;

	return RTS_ISP_OK;
}

static int verify_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	again[0] = 1.0;
	again[1] = 1.0;
	return RTS_ISP_OK;
}

static int verify_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	dgain[0] = 1.0;
	dgain[1] = 1.0;
	return RTS_ISP_OK;
}

static int verify_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
	return RTS_ISP_OK;
}

static int config_buffer_size(struct verify_status *status)
{
	if (status->buffer_addr)
		return -RTS_ISP_EBUSY;
	switch (VERIFY_MODE) {
	case VERIFY_RAW12_LOCATION:
	case VERIFY_RAW14_LOCATION:
	case VERIFY_YUV422_LOCATION:
	case VERIFY_ZOOM_LOCATION:
	case VERIFY_AI_LOCATION:
		status->buffer_size = SENSOR_WIDTH * SENSOR_HEIGHT * 2;
		status->y_len = SENSOR_WIDTH * SENSOR_HEIGHT;
		status->uv_len = SENSOR_WIDTH * SENSOR_HEIGHT;
		break;
	case VERIFY_RGB_LOCATION:
	case VERIFY_YUV444_LOCATION:
		status->buffer_size = (SENSOR_WIDTH * SENSOR_HEIGHT +
				       2) / 3 * 16;
		status->y_len = status->buffer_size;
		status->uv_len = 0;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}

	printf("config_buffer_size!\n");

	return RTS_ISP_OK;
	/* FIXME: allocate DMA from memory */
	//return isp_driver_mem_alloc(&status->buffer_addr,
	//			    status->buffer_size, "verify");
}
/*
static int __load_image(struct verify_status *status, const char * const path)
{
	int fd;
	int ret;
	void *virt = NULL;

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		ret = errno;
		goto out;
	}
	virt = isp_driver_mmap(status->buffer_addr, status->buffer_size);
	if (!virt) {
		ret = -errno;
		goto out;
	}
	ret = read(fd, virt, status->buffer_size);
	if (ret != status->buffer_size) {
		ret = -RTS_ISP_ERANGE;
		goto out;
	}
	ret = 0;
out:
	if (virt)
		munmap(virt, status->buffer_size);
	if (fd >= 0)
		close(fd);
	return ret;
}
*/
static int __get_location_fmt(int mode, uint32_t *location, uint32_t *format)
{
	if (!location || !format)
		return -RTS_ISP_EINVAL;
	switch (mode) {
	case VERIFY_RAW12_LOCATION:
		*location = 0x1;
		*format = 0x1;
		break;
	case VERIFY_RAW14_LOCATION:
		*location = 0x2;
		*format = 0x2;
		break;
	case VERIFY_RGB_LOCATION:
		*location = 0x4;
		*format = 0x3;
		break;
	case VERIFY_YUV444_LOCATION:
		*location = 0x8;
		*format = 0x3;
		break;
	case VERIFY_YUV422_LOCATION:
		*location = 0x10;
		*format = 0x0;
		break;
	case VERIFY_AI_LOCATION:
		*location = 0x20;
		*format = 0x0;
		break;
	case VERIFY_ZOOM_LOCATION:
		*location = 0x40;
		*format = 0x0;
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	return RTS_ISP_OK;
}

static int __config_regs(struct verify_status *status)
{
	int ret;
	uint32_t location, format;
	struct verify_ctrl_config v_cfg;
	printf("CFG!\n");

	ret = __get_location_fmt(VERIFY_MODE, &location, &format);
	if (ret)
		return ret;
	isp_write_reg(location, VERIFY_SEL);
	isp_write_reg(0x3d, VERIFY_CTRL); // 0011_1101
#if 1
	hal_isp_get_verify_info(&v_cfg);

	isp_write_reg(v_cfg.verify_addr[0], VERIFY_Y_DDR_ADDR0);
	isp_write_reg(v_cfg.verify_addr[0], VERIFY_Y_DDR_ADDR1);
	isp_write_reg(v_cfg.verify_addr[0] + status->y_len, VERIFY_UV_DDR_ADDR0);
	isp_write_reg(v_cfg.verify_addr[0] + status->y_len, VERIFY_UV_DDR_ADDR1);
	isp_write_reg(status->y_len, VERIFY_Y_DDR_LEN);
	isp_write_reg(status->uv_len, VERIFY_UV_DDR_LEN);
    // Buffer allocate in sdk-ameba, dump reg for debug
	printf("0x%x -> 0x%x\n", VERIFY_Y_DDR_ADDR0, isp_read_reg(VERIFY_Y_DDR_ADDR0));
	printf("0x%x -> 0x%x\n", VERIFY_Y_DDR_ADDR1, isp_read_reg(VERIFY_Y_DDR_ADDR1));
	printf("0x%x -> 0x%x\n", VERIFY_UV_DDR_ADDR0, isp_read_reg(VERIFY_UV_DDR_ADDR0));
	printf("0x%x -> 0x%x\n", VERIFY_UV_DDR_ADDR1, isp_read_reg(VERIFY_UV_DDR_ADDR1));
	printf("0x%x -> 0x%x\n", VERIFY_Y_DDR_LEN, isp_read_reg(VERIFY_Y_DDR_LEN));
	printf("0x%x -> 0x%x\n", VERIFY_UV_DDR_LEN, isp_read_reg(VERIFY_UV_DDR_LEN));
#endif
	isp_write_reg(1, VERIFY_FRAME_NUM);
	isp_write_reg(format, VERIFY_FRAME_FORMAT);
	isp_write_reg((SENSOR_WIDTH - 1) | (SENSOR_HEIGHT - 1) << 16,
			  VERIFY_FRAME_SIZE);
	isp_write_reg(0x1010, VERIFY_FRAME_CONFG0);
	isp_write_reg((SENSOR_DUMMY_PIXEL - 1) | (SENSOR_DUMMY_LINE - 1) << 16,
			  VERIFY_FRAME_CONFG1);
	isp_write_reg(0x1, VERIFY_INT_FLAG);

	const uint32_t drc_ctrl_addr = 0x1c78;
	const uint32_t drc_ctrl_org = isp_read_reg(drc_ctrl_addr);
	const uint8_t drc_en_org = (drc_ctrl_org & 0x2) >> 1;

	// 67e: original IQ table.
	// bit-15: drc_update_en should be 0.
	// bit-16: drc_keep_en should be 1.
	uint32_t drc_ctrl_new = (drc_ctrl_org & ~0x1000) | 0x10000; // Disable drc_update_en and enable drc_keep_en.
	// uint32_t drc_ctrl_new = drc_ctrl_org & ~0x2; // Disable drc_en.
	isp_write_reg(drc_ctrl_new, drc_ctrl_addr);

	const uint32_t drc_ctrl_final = isp_read_reg(drc_ctrl_addr);
	const uint8_t drc_en_final = (drc_ctrl_final & 0x2) >> 1;
	printf("[INFO][sensor_ov13b10_mipi_12m_seq][__config_regs] (org) DRC: 0x%x, drc_en: %d\r\n",
		drc_ctrl_org, drc_en_org);
	printf("[INFO][sensor_ov13b10_mipi_12m_seq][__config_regs] (new) DRC: 0x%x, drc_en: %d\r\n",
		drc_ctrl_final, drc_en_final);

	return RTS_ISP_OK;
};
/*
static void *verify_preview_thread(void *data)
{
	int i;
	int cnt;
	char path[256];
	int ret;
	struct verify_status *status = data;

	ret = __config_regs(status);
	if (ret)
		pthread_exit(NULL);

	i = 0;
	while (status->enable) {
		i++;
		snprintf(path, sizeof(path), VERIFY_IMAGE_PATH, i);
		ret = __load_image(status, path);
		if (ret)
			break;
		isp_write_reg(0x1, VERIFY_START_FLAG);
		cnt = 0;
		while (cnt++ < 20 && isp_read_reg(VERIFY_INT_FLAG) == 0)
			usleep(10000);
		isp_write_reg(0x1, VERIFY_INT_FLAG);
	}
	pthread_exit(NULL);
}
*/

static int verify_start(uint32_t isp_id)
{
	int ret = 0;
	struct verify_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];

	ret = config_buffer_size(status);
	if (ret)
		goto out;


	__config_regs(status);
out:
	if (ret && status->buffer_addr) {
		//isp_driver_mem_free(status->buffer_addr);
		status->buffer_addr = 0;
	}
	return ret;
}

static int verify_stop(uint32_t isp_id)
{
	struct verify_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];

	// status->enable = 0;
	//pthread_join(status->thread, NULL);

	if (status->buffer_addr) {
		//isp_driver_mem_free(status->buffer_addr);
		status->buffer_addr = 0;
	}
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops verify_ops = {
	.ops_version = SENSOR_OPS_VERSION,
	.name = "ov13b10_12m_seq",
	.get_info = verify_get_info,
	.get_init_info = verify_get_init_info,
	.get_tuned_again = verify_get_tuned_again,
	.get_tuned_dgain = verify_get_tuned_dgain,
	.get_exposure_gain_info = verify_get_exposure_gain_info,
	.start = verify_start,
	.stop = verify_stop,
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &verify_ops;
}
#endif