/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <unistd.h>
#include "cmsis_os2.h"
#include "rt_task.h"
#include "rts_ioctl.h"
#include <isp_top.h>
#include <isp_core.h>
#include <isp_mod.h>
#include <isp_algo.h>
#include <isp_sensor.h>
#include <isp_driver.h>
#include <isp_uds.h>
#include <isp_iq.h>
#include "rtx_mutex.h"
#include "rt_time.h"



#define ISP_DEBUG_TYPE ISP_DEBUG_CORE

#define RTS_ISP_PID_FILE "/var/run/rtsisp.pid"

struct isp_top {
	isp_poll_t p;
	isp_stream_t *stream_uds;

	isp_core_t core[_ISP_ID_NUM];

	struct isp_algo_manager algom;
	struct isp_sensor_manager snrm;

	enum rts_isp_status status;
	uint8_t fcs_done;
	int pid_fd;
	uint32_t direct_i2c_mode;
	uint32_t hdr_mode;
	uint32_t mirrorflip_mode;

	/*
		0: Disable TNR only enable SNR
		1: Enable TNR and SNR
	*/
	uint8_t tnr_en;

};

static struct isp_top *g_isp;
  static osMutexId_t g_isp_lock;
  static int gbl_isp_pid=0;

static int isp_top_lock(void)
{
	int ret = 0;
	if (!g_isp_lock) {

		g_isp_lock = xSemaphoreCreateMutex();
		if (!g_isp_lock) {
			isp_error("%s: mutex alloc fail\n", __func__);
			return -RTS_ISP_EINVAL;
		}
	}

	ret = xSemaphoreTake(g_isp_lock, ISP_SEM_TIMEOUT);
	if(ret == pdTRUE) {
		return osOK;
	}
	else {
        return osErrorOS;

	}

	//return ret;
}

static void isp_top_unlock(void)
{
	if (g_isp_lock)
		xSemaphoreGive(g_isp_lock);
	else
		isp_error("%s: NULL error!\r\n", __func__);
}

static int isp_top_core_stop(struct isp_top *isp);
static int isp_top_core_cleanup(struct isp_top *isp);

static int isp_top_poll_add(struct isp_top *isp)
{
	int ret;

	if (!isp)
		return -RTS_ISP_EINVAL;

	ret = isp_driver_stream_add(isp->p);
	if (ret)
		goto err;

	return RTS_ISP_OK;
err:
	isp_perror(ret, "poll add handles fail");
	return ret;
}

static int isp_top_poll_del(struct isp_top *isp)
{
	if (!isp)
		return -RTS_ISP_EINVAL;

	return RTS_ISP_OK;
}

static int isp_top_core_init(struct isp_top *isp)
{
	int ret;
	int i;

	if (!isp)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < _ISP_ID_NUM; i++) {
		//ret = isp_core_pre_init(&isp->core[i]);
		ret = isp_core_create(&isp->core[i]);
		if (ret) {
			isp_perror(ret, "create isp core%d failed", i);
			goto err;
		}
	}
	ret = isp_register_all_modules();
	if (ret)
		return ret;
	for (i = 0; i < _ISP_ID_NUM; i++) {
		ret = isp_core_init(isp->core[i]);
		if (ret) {
			isp_perror(ret, "init isp core%d failed", i);
			goto err;
		}
	}

	return RTS_ISP_OK;

err:
	isp_top_core_cleanup(isp);
	return ret;
}

static int isp_top_core_cleanup(struct isp_top *isp)
{
	int i;

	if (!isp)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < _ISP_ID_NUM; i++)
		isp_core_cleanup(isp->core[i]);
	isp_unregister_all_modules();
	for (i = 0; i < _ISP_ID_NUM; i++)
		//isp_core_post_cleanup(&isp->core[i]);
		isp_core_release(&isp->core[i]);

	return RTS_ISP_OK;
}

static int isp_top_core_run(struct isp_top *isp)
{
	int ret;
	int i;
	struct rts_isp_info info;

	if (!isp)
		return -RTS_ISP_EINVAL;

	for (i = 0; i < _ISP_ID_NUM; i++) {
		if (!isp->core[i]) {
			ret = -RTS_ISP_ENOTREADY;
			goto err;
		}
		ret = isp_core_start(isp->core[i]);
		if (ret)
			goto err;
		ret = isp_sensor_get_info(&isp->snrm, i, &info);
		if (ret)
			goto err;
		ret = isp_driver_register_subdev(&info);
		if (ret)
			goto err;
	}
	return RTS_ISP_OK;

err:
	isp_perror(ret, "isp core run fail");
	isp_top_core_stop(isp);
	return ret;
}

static int isp_top_core_stop(struct isp_top *isp)
{
	int i;

	if (!isp)
		return -RTS_ISP_EINVAL;

	isp_driver_unregister_subdev();

	for (i = 0; i < _ISP_ID_NUM; i++)
		if (isp->core[i])
			isp_core_stop(isp->core[i]);

	return RTS_ISP_OK;
}

static int isp_pid_file_init(struct isp_top *isp)
{
	int fd;
	if (isp->pid_fd)
		return -RTS_ISP_EEXIST;

	fd = gbl_isp_pid = (int)xTaskGetCurrentTaskHandle();
	isp->pid_fd = fd;
	isp_info("%s %d/r/n",__func__, fd);

	return RTS_ISP_OK;
}

static int isp_pid_file_cleanup(struct isp_top *isp)
{
	isp->pid_fd = 0;
	return RTS_ISP_OK;
}

static struct isp_top *isp_top_get_unlock(void)
{
	return g_isp;
}

static struct isp_top *isp_top_get(void)
{
	if (isp_top_lock() != osOK) {
		isp_error("isp_top_get isp_top_lock fail\n\r");
		return NULL;
	}
	if (!g_isp || isp_top_get_status() == RTS_ISP_UNINITIALIZED) {
		isp_top_unlock();
		return NULL;
	}
	return g_isp;
}

static void isp_top_put(struct isp_top *isp)
{
	if (isp && isp == g_isp)
		isp_top_unlock();
}

static int isp_top_rw_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg,
				 int is_read)
{
	int ret = RTS_ISP_ENOTREADY;

	if (isp_top_get_status() == RTS_ISP_UNINITIALIZED)
		goto out;
	if (is_read)
		ret = isp_sensor_read_reg(isp_top_get_snrm(), isp_id, reg);
	else
		ret = isp_sensor_write_reg(isp_top_get_snrm(), isp_id, reg);
out:
	return ret;
}

int isp_top_init(uint8_t fcs_ready, uint32_t hdr_mode, uint32_t mirflp_mode, uint8_t tnr_en)
{
	int ret;
	struct isp_top *isp;

	ret = isp_top_lock();
	if (ret != osOK) {
		isp_error("isp_top_init isp_top_lock fail\n\r");
		return -RTS_ISP_EAGAIN;
	}
	if (g_isp) {
		enum rts_isp_status status = (enum rts_isp_status)isp_top_get_status();

		isp_top_unlock();
		if (status != RTS_ISP_UNINITIALIZED)
			return RTS_ISP_OK;
		else
			return -RTS_ISP_EAGAIN;
	}

	if (!isp_calloc_item(isp)) {
		isp_top_unlock();
		return -RTS_ISP_ENOMEM;
	}
	isp->fcs_done = fcs_ready;
	isp->hdr_mode = hdr_mode;
	isp->mirrorflip_mode = mirflp_mode;
	isp->tnr_en = tnr_en;

	ret = isp_pid_file_init(isp);
	if (ret) {
		isp_free(isp);
		isp_top_unlock();
		return ret;
	}

	//isp_log_open(ISP_LOG2LOG, 0);

	ret = isp_driver_init();
	if (ret)
		goto err_driver_init;
	isp_driver_isp_clk_get();
	/* g_isp has been used in init, so must be assigned here */
	g_isp = isp;
	ret = isp_top_core_init(isp);
	if (ret)
		goto err_core_init;
	ret = isp_algo_init(&isp->algom);
	if (ret)
		goto err_algo_init;
	ret = isp_sensor_init(&isp->snrm);
	if (ret)
		goto err_sensor_init;
	//ret = isp_poll_init(&isp->p);
	ret = isp_poll_create(&isp->p);
	if (ret)
		goto err_poll_init;
	ret = isp_top_poll_add(isp);
	if (ret)
		goto err_poll_add;

	isp_poll_update_time(isp->p);

	isp_top_set_status(RTS_ISP_STOPPED);
	isp_driver_isp_clk_put();

	isp_info("rts isp init ok\n");

	isp_top_unlock();
	return RTS_ISP_OK;

err_poll_add:
	//isp_release(isp->p, isp_poll_cleanup);
	isp_release(isp->p, isp_poll_release);
err_poll_init:
	isp_sensor_cleanup(&isp->snrm);
err_sensor_init:
	isp_algo_cleanup(&isp->algom);
err_algo_init:
	isp_top_core_cleanup(isp);
err_core_init:
	isp_driver_isp_clk_put();
err_driver_init:
	isp_driver_cleanup();
	isp_pid_file_cleanup(isp);
	//isp_log_close();
	//isp_free(g_isp);
	isp_free(isp);
	g_isp = NULL;
	isp_top_unlock();
	return ret;
}

int isp_top_cleanup(void)
{
	struct isp_top *isp;

	if (isp_top_lock() != osOK) {
		isp_error("isp_top_cleanup isp_top_lock fail\n\r");
		return -RTS_ISP_EBUSY;
	}
	if (!g_isp) {
		isp_top_unlock();
		return RTS_ISP_OK;
	}
	isp = g_isp;
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		isp_top_unlock();
		isp_error("%s RTS_ISP_RUNNING\r\n", __func__);
		return -RTS_ISP_EBUSY;
	}

	isp_driver_isp_clk_get();
	isp_top_set_status(RTS_ISP_UNINITIALIZED);
	isp_top_poll_del(isp);
	//isp_release(isp->p, isp_poll_cleanup);
	isp_release(isp->p, isp_poll_release);
	isp_sensor_cleanup(&isp->snrm);
	isp_algo_cleanup(&isp->algom);
	isp_top_core_cleanup(isp);
	isp_driver_isp_clk_put();
	isp_driver_cleanup();
	isp_pid_file_cleanup(isp);
	isp_info("rts isp cleanup ok\r\n");
	//isp_log_close();
	isp_free(g_isp);
	isp_top_unlock();

	return RTS_ISP_OK;
}
uint32_t top_core_run_time;
int isp_top_start(void)
{
	int ret = RTS_ISP_OK;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;

	isp_driver_isp_clk_get();
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		ret = -RTS_ISP_EBUSY;
		goto out;
	}

	ret = isp_sensor_check_all_bound(&isp->snrm);
	if (ret) {
		isp_error("you must bind all sensors before run\n");
		goto out;
	}
	ret = isp_algo_check_all_bound(&isp->algom);
	if (ret) {
		isp_error("you must bind all algorithms before run\n");
		goto out;
	}
	top_core_run_time = hal_read_curtime_us();
	ret = isp_top_core_run(isp);
	if (ret)
		goto out;
	//dbg_printf("rts isp loop start\r\n");
	//isp_top_set_status(RTS_ISP_RUNNING);
	isp_top_put(isp);
	isp_driver_isp_clk_put();

	ret = isp_poll_loop_run(isp->p);
	return ret;
	isp_driver_isp_clk_get();
	isp = isp_top_get();

	//isp_info("rts isp loop stopped\r\n");
	isp_top_core_stop(isp);

out:
	isp_driver_isp_clk_put();
	isp_top_put(isp);
	isp_top_set_status(RTS_ISP_STOPPED);
	return ret;
}

int isp_top_stop(void)
{
	struct isp_top *isp;

	isp = isp_top_get_unlock();
	if (!isp)
		return -RTS_ISP_ENOTREADY;

	if (isp_top_get_status() < RTS_ISP_RUNNING)
		return RTS_ISP_OK;

	if (isp_top_get_status() > RTS_ISP_RUNNING) {
		isp_error("%s isp_top_status %d \r\n", __func__, isp_top_get_status());
		return -RTS_ISP_EBUSY;
	}

	isp_poll_loop_stop(isp->p);
	while (isp_top_get_status()>= RTS_ISP_RUNNING) {
		;
	}

	return RTS_ISP_OK;
}

int isp_top_status(void)
{
	enum rts_isp_status status;
	struct isp_top *isp = isp_top_get();

	if (!isp)
		return RTS_ISP_UNINITIALIZED;

	status = (enum rts_isp_status)isp_top_get_status();
	isp_top_put(isp);

	return status;
}

int isp_top_register_algo(const struct rts_isp_algo *algo)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_algo_register(&isp->algom, algo);
	isp_top_put(isp);

	return ret;
}

int isp_top_unregister_algo(enum rts_isp_algo_id id)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_algo_unregister(&isp->algom, id);
	isp_top_put(isp);

	return ret;
}

int isp_top_get_algo(struct rts_isp_algo *algo)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_algo_get(&isp->algom, algo);
	isp_top_put(isp);

	return ret;
}

int isp_top_bind_algo(int isp_id, int id)
{
	int ret;
	struct isp_top *isp = isp_top_get();

	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_top_bind_algo_unlock(isp_id, id);
	isp_top_put(isp);

	return ret;
}

int isp_top_unbind_algo(int isp_id, int id)
{
	int ret;
	struct isp_top *isp = isp_top_get();

	if (!isp)
		return -RTS_ISP_ENOTREADY;

	ret = isp_top_unbind_algo_unlock(isp_id, id);
	isp_top_put(isp);

	return ret;
}

int isp_top_register_sensor(const struct rts_isp_sensor *sensor)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_sensor_register(&isp->snrm, sensor);
	isp_top_put(isp);

	return ret;
}

int isp_top_unregister_sensor(int sensor_id)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_sensor_unregister(&isp->snrm, sensor_id);
	isp_top_put(isp);

	return ret;
}

int isp_top_get_sensor(int sensor_id, struct rts_isp_sensor *sensor)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	ret = isp_sensor_get(&isp->snrm, sensor_id, sensor);
	isp_top_put(isp);

	return ret;
}

int isp_top_check_sensor(uint32_t isp_id, int sensor_id)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		ret = -RTS_ISP_EBUSY;
		goto out;
	}
	ret = isp_sensor_check(&isp->snrm, isp_id, sensor_id);
out:
	isp_top_put(isp);
	return ret;
}

int isp_top_bind_sensor(uint32_t isp_id, int sensor_id)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		ret = -RTS_ISP_EBUSY;
		goto out;
	}
	ret = isp_sensor_bind(&isp->snrm, isp_id, sensor_id);

out:
	isp_top_put(isp);
	return ret;
}

int isp_top_unbind_sensor(uint32_t isp_id, int sensor_id)
{
	int ret;
	struct isp_top *isp;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		ret = -RTS_ISP_EBUSY;
		goto out;
	}
	ret = isp_sensor_unbind(&isp->snrm, isp_id, sensor_id);

out:
	isp_top_put(isp);
	return ret;
}

int isp_top_register_iq(uint32_t isp_id, const char *path)
{
	int ret;
	struct isp_top *isp;
	struct isp_iq *iq;
	//uint32_t iq_size;


	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;
	if (isp_top_get_status() >= RTS_ISP_RUNNING) {
		ret = -RTS_ISP_EBUSY;
		goto out;
	}
	iq = isp_core_get_iq(isp_top_get_core(isp_id));
	ret = isp_iq_register(iq, path);
#if 0
	if (!ret) {
		iq_size = *(uint32_t *)(path);
		isp_info("register iq size %d to isp %d\n", iq_size, isp_id);
	}
#endif
out:
	isp_top_put(isp);
	return ret;
}

int isp_top_set_iq_calb_data(uint32_t isp_id, struct isp_iq_calb *data)
{
	int ret = RTS_ISP_OK;
	struct isp_top *isp;
	struct isp_iq *iq;

	if (!data)
		return -RTS_ISP_EINVAL;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;

	iq = isp_core_get_iq(isp_top_get_core(isp_id));

	iq->calb_data = *data;

	isp_top_put(isp);
	return ret;
}

int isp_top_set_iq_calb_en(uint32_t isp_id, uint8_t en)
{
	int ret = RTS_ISP_OK;
	struct isp_top *isp;
	struct isp_iq *iq;

	isp = isp_top_get();
	if (!isp)
		return -RTS_ISP_ENOTREADY;

	iq = isp_core_get_iq(isp_top_get_core(isp_id));

	iq->calb_data.enable = en;

	isp_top_put(isp);
	return ret;
}

int isp_top_get_pid_from_file(osThreadId_t *pid)
{
	if (!pid)
		return -RTS_ISP_EINVAL;

	*pid = (osThreadId_t)gbl_isp_pid;

	return RTS_ISP_OK;
}

int isp_top_read_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg)
{
	return isp_top_rw_sensor_reg(isp_id, reg, RTS_ISP_TRUE);
}

int isp_top_write_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg)
{
	return isp_top_rw_sensor_reg(isp_id, reg, RTS_ISP_FALSE);
}

/********** internal api **********/
int isp_top_get_status(void)
{
	struct isp_top *isp  = isp_top_get_unlock();

	if (!isp)
		return RTS_ISP_UNINITIALIZED;
	return isp->status;
}

void isp_top_set_status(enum rts_isp_status status)
{
	struct isp_top *isp  = isp_top_get_unlock();

	if (isp)
		isp->status = status;
}

void isp_top_lock_internal(void)
{
	isp_top_get();
}

void isp_top_unlock_internal(void)
{
	isp_top_put(isp_top_get_unlock());
}

void *isp_top_get_poll(void)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp)
		return NULL;
	return isp->p;
}

void *isp_top_get_core(uint32_t isp_id)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp || isp_id >= _ISP_ID_NUM)
		return NULL;
	return isp->core[isp_id];
}

struct isp_mod *isp_top_get_mod(int isp_id, int mod_id)
{
	struct isp_mod *mod;
	isp_core_t core;

	core = isp_top_get_core(isp_id);
	if (!core)
		return NULL;
	if (isp_core_get_mod(core, mod_id, &mod))
		return NULL;
	return mod;
};

struct isp_algo_manager *isp_top_get_algom(void)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp)
		return NULL;
	return &isp->algom;
}

struct isp_sensor_manager *isp_top_get_snrm(void)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp)
		return NULL;
	return &isp->snrm;
}

int isp_top_bind_algo_unlock(int isp_id, int id)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp)
		return -RTS_ISP_ENOTREADY;
	return isp_algo_bind(&isp->algom, isp_id, (enum rts_isp_algo_id)id);
}

int isp_top_unbind_algo_unlock(int isp_id, int id)
{
	struct isp_top *isp = isp_top_get_unlock();

	if (!isp)
		return -RTS_ISP_ENOTREADY;
	return isp_algo_unbind(&isp->algom, isp_id, (enum rts_isp_algo_id)id);
}

int isp_top_get_fcs_ready(void)
{
	int ret;
	ret = g_isp->fcs_done;
	//printf("%s %d\r\n",__func__, ret);


	return ret;
}

void isp_top_update_fcs_ready(uint8_t fcs_status)
{
g_isp->fcs_done = fcs_status;
}

void isp_top_set_direct_i2c_mode(uint32_t direct_i2c_mode)
{
g_isp->direct_i2c_mode = direct_i2c_mode;
}

uint32_t isp_top_get_direct_i2c_mode(void)
{
	return g_isp->direct_i2c_mode;
}

uint32_t isp_top_get_hdr_mode(void)
{
	return g_isp->hdr_mode;
}

void isp_top_set_mirrorflip_mode(uint32_t mirrorflip_mode)
{
g_isp->mirrorflip_mode = mirrorflip_mode;
}

uint32_t isp_top_get_mirrorflip_mode(void)
{
	return g_isp->mirrorflip_mode;
}

void isp_top_set_raw_mode_tnr_en(uint8_t tnr_en) //only for raw mode
{
	g_isp->tnr_en = tnr_en;
}

uint8_t isp_top_get_raw_mode_tnr_en(void) //only for raw mode
{
	return g_isp->tnr_en;
}

