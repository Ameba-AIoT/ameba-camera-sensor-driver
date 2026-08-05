/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#define usleep udelay

#include <rts_isp.h>
#include <isp_uds.h>
#include <isp_driver.h>
#include <isp_top_api.h>
#include <isp_mod_iq.h>
#include "rtx_mutex.h"
#include <isp_mod_global.h>
#include <isp_mod_wdr.h>

static const void *volatile __rts_isp_force_keep_func;

void __rts_isp_force_keep_helper_funcs(void)
{
//	__rts_isp_force_keep_func = __rts_isp_force_keep_helper_funcs;
	__rts_isp_force_keep_func = rts_isp_read_sensor_reg;
//	__rts_isp_force_keep_func = rts_isp_write_sensor_reg;
//	__rts_isp_force_keep_func = rts_isp_sensor_access_prepare;
//	__rts_isp_force_keep_func = rts_isp_sensor_access_unprepare;
}

static int process_i2c_regs(const struct rts_isp_i2c_info *info,
			    const struct rts_isp_i2c_regs *regs,
			    int is_read)
{
	int ret = -RTS_ISP_EINVAL;
	uint32_t num;
	struct rts_isp_i2c i2c;

	if (!info || !regs || !regs->regs || !regs->num)
		return ret;

	i2c.info = *info;
	num = 0;
	while (num < regs->num) {
		int i;
		int count;

		if (regs->num - num > ARRAY_SIZE(i2c.regs))
			count = ARRAY_SIZE(i2c.regs);
		else
			count = regs->num - num;
		i2c.num = count;
		isp_memcpy(&i2c.regs, regs->regs + num,
			   i2c.num * sizeof(i2c.regs[0]));
		if (is_read)
			ret = isp_driver_i2c_read(&i2c);
		else
			ret = isp_driver_i2c_write(&i2c);
		if (ret)
			break;
		for (i = 0; i < (int)i2c.num; i++)
			regs->regs[num + i].data = i2c.regs[i].data;
		num += count;
	}
	if (!ret && regs->udelay)
		usleep(regs->udelay);
	return ret;
}

int rts_av_isp_init(uint8_t fcs_ready, uint32_t hdr_mode, uint32_t mirflp_mode, uint8_t tnr_en)
{
	return isp_top_init(fcs_ready, hdr_mode, mirflp_mode, tnr_en);
}

int rts_av_isp_cleanup(void)
{
	return isp_top_cleanup();
}

int rts_av_isp_start(void)
{
	return isp_top_start();
}

int rts_av_isp_stop(void)
{
	return isp_top_stop();
}

enum rts_isp_status rts_av_isp_get_status(void)
{
	return (enum rts_isp_status)isp_top_status();
}

int rts_av_isp_register_algo(const struct rts_isp_algo *algo)
{
	return isp_top_register_algo(algo);
}

int rts_av_isp_unregister_algo(enum rts_isp_algo_id id)
{
	return isp_top_unregister_algo(id);
}

int rts_av_isp_get_algo(struct rts_isp_algo *algo)
{
	return isp_top_get_algo(algo);
}

int rts_av_isp_bind_algo(uint32_t isp_id, enum rts_isp_algo_id id)
{
	int ret;
	osThreadId_t pid;

	ret = isp_top_get_pid_from_file(&pid);
	if (ret)
		return ret;

	if (pid == xTaskGetCurrentTaskHandle())
		return isp_top_bind_algo(isp_id, id);
	else if (osThreadGetState(pid) != osThreadError)  //if pid exists
		return isp_uds_message_simple(isp_id, MOD_IQ,
					      IQ_EXEC_BIND_ALGO,
					      &id, sizeof(id));
	else
		return -RTS_ISP_ENOTREADY;
}

int rts_av_isp_unbind_algo(uint32_t isp_id, enum rts_isp_algo_id id)
{
	int ret;
	osThreadId_t pid;

	ret = isp_top_get_pid_from_file(&pid);
	if (ret) {
		isp_error("%s isp_top_get_pid_from_file failed %d \r\n", __func__, ret);
			return ret;
	}


	if (pid == xTaskGetCurrentTaskHandle()) {
		return isp_top_unbind_algo(isp_id, id);
	} else if (osThreadGetState(pid) != osThreadError) { //if pid exists
		isp_warning("%s isp_uds_message_simple \r\n", __func__);
		return isp_uds_message_simple(isp_id, MOD_IQ, IQ_EXEC_UNBIND_ALGO, &id, sizeof(id));
	} else
		return -RTS_ISP_ENOTREADY;
}

int rts_av_isp_register_sensor(const struct rts_isp_sensor *sensor)
{
	return isp_top_register_sensor(sensor);
}

int rts_av_isp_unregister_sensor(int sensor_id)
{
	return isp_top_unregister_sensor(sensor_id);
}

int rts_av_isp_get_sensor(int sensor_id,
			  struct rts_isp_sensor *sensor)
{
	return isp_top_get_sensor(sensor_id, sensor);
}

int rts_av_isp_check_sensor(uint32_t isp_id, int sensor_id)
{
	return isp_top_check_sensor(isp_id, sensor_id);
}

int rts_av_isp_bind_sensor(uint32_t isp_id, int sensor_id)
{
	return isp_top_bind_sensor(isp_id, sensor_id);
}

int rts_av_isp_unbind_sensor(uint32_t isp_id, int sensor_id)
{
	return isp_top_unbind_sensor(isp_id, sensor_id);
}

int rts_av_isp_register_iq(uint32_t isp_id, const char *path)
{
	return isp_top_register_iq(isp_id, path);
}

int rts_isp_read_i2c_regs(const struct rts_isp_i2c_info *info,
			  const struct rts_isp_i2c_regs *regs)
{
	return process_i2c_regs(info, regs, RTS_ISP_TRUE);
}

int rts_isp_write_i2c_regs(const struct rts_isp_i2c_info *info,
			   const struct rts_isp_i2c_regs *regs)
{
	return process_i2c_regs(info, regs, RTS_ISP_FALSE);
}

int rts_isp_read_i2c_reg(const struct rts_isp_i2c_info *info,
			 struct rts_isp_i2c_reg *reg)
{
	struct rts_isp_i2c_regs regs;

	regs.num = 1;
	regs.regs = reg;
	regs.udelay = 0;
	return rts_isp_read_i2c_regs(info, &regs);
}

int rts_isp_write_i2c_reg(const struct rts_isp_i2c_info *info,
			  struct rts_isp_i2c_reg *reg)
{
	struct rts_isp_i2c_regs regs;

	regs.num = 1;
	regs.regs = reg;
	regs.udelay = 0;
	return rts_isp_write_i2c_regs(info, &regs);
}

/*
void rts_isp_sensor_access_prepare(void)
{
	isp_driver_sync_lock(RTS_ISP_TRUE);
}

void rts_isp_sensor_access_unprepare(void)
{
	isp_driver_sync_lock(RTS_ISP_FALSE);
}
*/

int rts_av_isp_set_iq_calb(uint32_t isp_id, struct isp_iq_calb *data)
{
	return isp_top_set_iq_calb_data(isp_id, data);
}

int rts_av_isp_set_iq_calb_en(uint32_t isp_id, uint8_t en)
{
	return isp_top_set_iq_calb_en(isp_id, en);
}

int rts_isp_set_statis_irq_en(uint32_t isp_id, uint32_t en)
{
	return isp_uds_message_simple(isp_id, MOD_GLOBAL,
		GLOBAL_EXEC_SET_STATIS_IRQ_ENABLE,
		&en, sizeof(en));
}

int rts_isp_get_dir_wdr_level(uint32_t isp_id, uint8_t *level)
{
	return isp_uds_message_simple(isp_id, MOD_WDR,
				      WDR_EXEC_GET_DIR_LEVEL,
				      level, sizeof(*level));
}

int rts_isp_set_dir_wdr_level(uint32_t isp_id, uint8_t *level)
{
	return isp_uds_message_simple(isp_id, MOD_WDR,
				      WDR_EXEC_SET_DIR_LEVEL,
				      level, sizeof(*level));
}

