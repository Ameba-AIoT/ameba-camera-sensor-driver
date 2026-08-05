/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <rtsavisp.h>
#include "isp_log.h"
#include "rt_osd2_api.h"


#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif


//#include "rtl8735b_sys_ctrl.h"
//#define  _SYSTEM_CONNECT_READY_
#include "isp_main.h"

#include "rlx_irq.h"
#include "rlx_clk.h"
#include  "reset-rts3915.h"
#include  "rts_camera_isp_mfd.h"
#include  "rts_camera_zoom.h"
#include  "rts_camera_verify.h"
#include  "rts_camera_md.h"
#include  "isp_algo.h"
#include "rtl8735b_i2c_simple.h"
#include "rtl8735b_gpio_simple.h"
#include "isp_debug.h"
extern int rtscam_isp_probe(void);
extern int rtscam_soc_probe(void);

//#include "fixp_bin.h"
#define SENSOR_PATH "libsensor_fixp.so"

//#define IQ_PATH  ((char*)iq_bin)


#define ALGO_DIR "/usr/lib/rtsisp/algos"
#define ALGO_AE_ID RTS_ISP_ALGO_AE_ID0
#define ALGO_AE_PATH ALGO_DIR"/librts_algo_ae.so"
#define ALGO_AWB_ID RTS_ISP_ALGO_AWB_ID0
#define ALGO_AWB_PATH ALGO_DIR"/librts_algo_awb.so"
#define ALGO_AF_ID RTS_ISP_ALGO_AF_ID0
#define ALGO_AF_PATH ALGO_DIR"/librts_algo_af.so"
#define ALGO_MD_ID RTS_ISP_ALGO_MD_ID0
#define ALGO_MD_PATH ALGO_DIR"/librts_algo_md.so"
#define ALGO_OTHER_ID RTS_ISP_ALGO_OTHER_ID0
#define ALGO_OTHER_PATH ALGO_DIR"/librts_algo_other.so"


#if 0
static void isp_signal_handle(int signo)
{
	rts_av_isp_stop();
}
#endif

static int register_algo(enum rts_isp_algo_id id, char *path)
{
	int ret;
	struct rts_isp_algo algo;

	if (!path)
		return -RTS_ISP_EINVAL;

	algo.id = id;
	algo.path = path;

	ret = rts_av_isp_register_algo(&algo);
	if (ret < 0)
		return ret;
	ret = rts_av_isp_bind_algo(ISP0, id);
		if (ret)
			return ret;

	return RTS_ISP_OK;
}




static int register_all_algos(void)
{
	int ret;

	printf("algo ver %s \n", rts_get_lib3A_version());

	ret = register_algo(ALGO_AE_ID, ALGO_AE_PATH);
	if (ret)
		goto out;
	ret = register_algo(ALGO_AWB_ID, ALGO_AWB_PATH);
	if (ret)
		goto out;
	ret = register_algo(ALGO_AF_ID, ALGO_AF_PATH);
	if (ret)
		goto out;
	ret = register_algo(ALGO_MD_ID, ALGO_MD_PATH);
	if (ret)
		goto out;
	ret = register_algo(ALGO_OTHER_ID, ALGO_OTHER_PATH);
out:
	if (ret)
		printf("register algos fail %d \n", ret);
	return ret;
}

static int g_sensor_id = 0;

//static int register_sensor_iq(void)
static int register_sensor_iq(char * iq_addr, char * cali_iq_addr)
{
	int ret = RTS_ISP_OK;
	int sensor_id;
	const struct rts_isp_sensor sensor = {
		.path = SENSOR_PATH,
	};

	sensor_id = rts_av_isp_register_sensor(&sensor);
	if (sensor_id < 0) {
		ret = sensor_id;
		goto out;
	}
	g_sensor_id = sensor_id;
	ret = rts_av_isp_bind_sensor(ISP0, sensor_id);
	if (ret)
		goto out;
	if ( cali_iq_addr != NULL ) {
		ret = rts_av_isp_set_iq_calb(ISP0, (struct isp_iq_calb *)cali_iq_addr);
		if (ret)
			goto out;
	}


	//	ret = rts_av_isp_register_iq(ISP0, IQ_PATH);
	ret = rts_av_isp_register_iq(ISP0, iq_addr);
out:
	if (ret)
		printf("register sensor iq fail %d \n", ret);
	return ret;
}

// mpool, sf, uart & console(terminal)
extern hal_i2c_adapter_t  i2c_master_sample;
//extern hal_i2c_adapter_t  i2c_master_aphy_sample;
hal_isp_adapter_t g_isp_adpt = {0};

static int init_i2c(hal_isp_adapter_t *isp_adpt)
{
	uint8_t i2c_idx = g_isp_adpt.i2c_id = isp_adpt->i2c_id;
	uint8_t i2c_v_speed = I2CFastSpeed;
	memset(&i2c_master_sample, 0, sizeof(i2c_master_sample));
	hal_rtl_i2c_load_default_simple(&i2c_master_sample, i2c_idx);
	i2c_master_sample.init_dat.master = I2CMasterMode;
	i2c_master_sample.init_dat.addr_mod = I2CAddress7bit;
	i2c_master_sample.op_mode = I2CModePoll;//polling mode
	i2c_master_sample.irq_config.priority = 0;
	i2c_master_sample.init_dat.spd_mod = i2c_v_speed;
	i2c_master_sample.pltf_dat.tr_time_out = 10000;

	hal_i2c_init_simple(&(i2c_master_sample));

	i2c_master_sample.init_dat.clock = g_isp_adpt.i2c_clock = isp_adpt->i2c_clock;
	hal_rtl_i2c_set_clk_simple(&i2c_master_sample);

#if CONFIG_FPGA // FPGA
	uint8_t i2c_aphy_idx = 2;
	hal_rtl_i2c_load_default_simple(&i2c_master_aphy_sample, i2c_aphy_idx);
	i2c_master_aphy_sample.init_dat.master = I2CMasterMode;
	i2c_master_aphy_sample.init_dat.addr_mod = I2CAddress7bit;
	i2c_master_aphy_sample.op_mode = I2CModePoll;//polling mode
	i2c_master_aphy_sample.irq_config.priority = 0;
	i2c_master_aphy_sample.init_dat.spd_mod = i2c_v_speed;
	i2c_master_aphy_sample.pltf_dat.tr_time_out = 10000;
	hal_i2c_init_simple(&(i2c_master_aphy_sample));

	i2c_master_aphy_sample.init_dat.clock = 400;
	hal_rtl_i2c_set_clk_simple(&i2c_master_aphy_sample);
#endif
	return 0;

}

int reinit_i2c(void)
{
	//check if i2c already init
	if (i2c_master_sample.init_dat.clock != 0 && g_isp_adpt.i2c_clock != 0) {

		hal_i2c_deinit_simple(&(i2c_master_sample));

		init_i2c(&g_isp_adpt);
	}

	return 0;

}

extern hal_gpio_adapter_t gpio_pin_pwrctrl;
extern hal_gpio_adapter_t gpio_pin_reset;
extern hal_gpio_adapter_t gpio_pin_pwdn;

static int init_gpio(hal_isp_adapter_t *isp_adpt)
{
	hal_gpio_init_simple(&gpio_pin_reset, isp_adpt->sensor_rst_pin);
	hal_gpio_init_simple(&gpio_pin_pwdn, isp_adpt->sensor_pwdn_pin);

	hal_gpio_set_dir_simple(&gpio_pin_reset, GPIO_OUT);
	hal_gpio_set_dir_simple(&gpio_pin_pwdn, GPIO_OUT);
}

static int init_gpio_fcs(hal_isp_adapter_t *isp_adpt)
{
	hal_gpio_init_simple_fcs(&gpio_pin_reset, isp_adpt->sensor_rst_pin);
	hal_gpio_init_simple_fcs(&gpio_pin_pwdn, isp_adpt->sensor_pwdn_pin);

	//hal_gpio_set_dir_simple(&gpio_pin_pwrctrl, GPIO_OUT);
	//hal_gpio_set_dir_simple(&gpio_pin_reset, GPIO_OUT);
	//hal_gpio_set_dir_simple(&gpio_pin_pwdn, GPIO_OUT);
}


extern void mod_set_voe_for_sensor(void);

#define ISP_MFD_PROBE_ERR	0
#define ZOOM_PROBE_ERR		1
#define ISP_PROBE_ERR		2
#define VERIFY_PROBE_ERR	3
#define SOC_PROBE_ERR		4
#define MD_PROBE_ERR		5

static int init_bsp(hal_isp_adapter_t *isp_adpt)
{

	int init_err_status = 0;

	int isp_mfd_ret = 0;
	int zoom_ret = 0;
	int isp_ret = 0;
	int verify_ret = 0;
	int soc_ret = 0;
	int md_ret = 0;
	// note: console uart must be inited at first,
	//       or the console will display some strange chars in begining.
#if 0
	TIME_START(bsp_uart);
	uart_init(&g_console_uart);
	TIME_STOP(bsp_uart);

	// memory pool
	if (rt_tlsf_init() != RT_OK)
	{
		rt_printf("fail! rt_tlsf_init\n\n");
		return RT_E_NO_SYS;
	}
#endif

	//init others/video_in irq
	RLX_InitSharedIrq();

#if defined (CONFIG_VOE_PLATFORM) && CONFIG_VOE_PLATFORM // Run on TM9


	uint32_t reg_value32;
    reg_value32 = HAL_READ32(0x40492000, 0x114);
    reg_value32 |= (BIT4);
    HAL_WRITE32(0x40492000, 0x114, (u32)reg_value32);
    //printf("%s set ISP irq 0x%08x\r\n", HAL_READ32(0x40492000, 0x114));

#endif


#if defined(_SYSTEM_CONNECT_READY_)
	//init clock device driver
	rlx_clk_init();
#else
	rlx_clk_init0();
#endif
	//probe reset device driver
	rts_reset_probe();

#if defined(_SYSTEM_CONNECT_READY_)

	//probe sysmem device driver
	rts_sysmem_probe();
	//probe gpio device driver
	rts_pinctrl_probe();
	//probe i2c device driver
	i2c_dw_probe();
#endif
	init_i2c(isp_adpt);
//#ifdef _NO_FCS_
	if (!isp_adpt->fcs_ready) {
		//printf("init_gpio \r\n");
		init_gpio(isp_adpt);
	} else {
		init_gpio_fcs(isp_adpt);
		//printf("fcs done for gpio init \r\n");
	}

//#endif
#if 0

	TIME_START(bsp_console);
	console_init(&(g_console_uart.instance));
	console_flush();
	TIME_STOP(bsp_console);
#endif

#if 0
	TIME_START(bsp_mpool);
	if (!mpool_create())
	{
		rt_printf("fail! mpool_create\n\n");
		return RT_E_NO_SYS;
	}
	TIME_STOP(bsp_mpool);
#endif

	//probe mfd device
	isp_mfd_ret = rtscam_isp_mfd_probe();
	if (isp_mfd_ret != 0)
		init_err_status |= (1<<ISP_MFD_PROBE_ERR);

	//probe stream device
	zoom_ret = rtscam_zoom_probe();
	if (zoom_ret != 0)
		init_err_status |= (1<<ZOOM_PROBE_ERR);

	//probe isp device
	isp_ret = rtscam_isp_probe();
	if (isp_ret != 0)
		init_err_status |= (1<<ISP_PROBE_ERR);

	//probe verify device
	verify_ret = rtscam_verify_probe();
	if (verify_ret != 0)
		init_err_status |= (1<<VERIFY_PROBE_ERR);

	//probe soc device, for frame buffer control
	soc_ret = rtscam_soc_probe();
	if (soc_ret != 0)
		init_err_status |= (1<<SOC_PROBE_ERR);

#ifdef __MD_EN__
	//probe md2 device
	md_ret = rtscam_isp_md_probe();
	if (md_ret != 0)
		init_err_status |= (1<<MD_PROBE_ERR);

#endif

	mod_set_voe_for_sensor();


/*
	// sf must always be exist.
	TIME_START(bsp_sf);
	ret = rt_sf_probe(CFG_SF_PROBE_BUS, CFG_SF_PROBE_CS, CFG_SF_PROBE_SPEED, CFG_SF_PROBE_MODE);
	if (ret != RT_OK)
	{
		rt_printf("\nsf: probe ...%s\n", rt_code_str(ret));
		return RT_E_NO_DEV;
	}
	TIME_STOP(bsp_sf);
*/
	if (init_err_status != 0) {
		if (init_err_status & (1<<ISP_MFD_PROBE_ERR)) {
			return ERR_ID_ISP_MFD_PROBE_FAIL;

		} else if (init_err_status & (1<<ZOOM_PROBE_ERR)) {
			return ERR_ID_ISP_ZOOM_PROBE_FAIL;
		} else if (init_err_status & (1<<ISP_PROBE_ERR)) {
			return ERR_ID_ISP_PROBE_FAIL;
		} else if (init_err_status & (1<<VERIFY_PROBE_ERR)) {
			return ERR_ID_ISP_VERIFY_PROBE_FAIL;
		} else if (init_err_status & (1<<SOC_PROBE_ERR)) {
			return ERR_ID_ISP_SOC_PROBE_FAIL;
		} else {
			return ERR_ID_ISP_MD_PROBE_FAIL;
		}
	}
	else
		return 0;
}




int init_main(hal_isp_adapter_t *isp_adpt)
{

	int ret = 0;

#if 0
	g_start_time = rt_get_tickcount();

	#if MEMORY_CHECK
	dbg_init(10);
	#endif
#endif

	ret = init_bsp(isp_adpt);


#if 0
	TIME_START(task_init);
	if ((ret = init_task()) != 0)
	{
		rt_should_not_reach();
	}
	TIME_STOP(task_init);

	TIME_START(task_shell);
	if ((s_shell_handle = task_create_user_by_struct(&shell_task_info, &ret)) == 0)
	{
		rt_printf("create shell task ...%s\n", rt_code_str(ret));
		rt_should_not_reach();
	}
	TIME_STOP(task_shell);

	vTaskResume(s_shell_handle);
	//loop:
	while (1)
	{
		vTaskDelay(CFG_TASK_MAIN_DELAY);
	}
#endif
	return ret;
}



//osThreadId tid_isp_test;                             			// thread id
//osThreadDef (cmd_isp_test_main, osPriorityNormal, 1, 64*1024);  // thread object
uint32_t av_isp_init_time = 0;
int isp_main_thread(void const *argument)
{

	int ret = 0;
	hal_isp_adapter_t *isp_adpt = (hal_isp_adapter_t *)argument;


	ret = rts_av_isp_init(isp_adpt->fcs_ready, isp_adpt->init_hdr_mode, isp_adpt->init_mirrorflip_mode, isp_adpt->isp_raw_mode_tnr_en);
	av_isp_init_time = hal_read_curtime_us();
	if (ret)
		goto exit;

	ret = register_sensor_iq((char *)(isp_adpt->iq_addr), (char *)(isp_adpt->cali_iq_addr));
	if (ret)
		goto exit;
	ret = register_all_algos();
	if (ret)
		goto exit;

	isp_core_set_iq_mode(isp_top_get_core(ISP0), isp_adpt->daynight_mode);


	ret = rts_av_isp_start();
	if (ret)
		goto exit;
	//rts_av_isp_cleanup();

exit:
	if (ret)
		isp_error("%s rts isp fail %d \r\n",__func__,ret);
	return ret;

}

int isp_main_close(void *argument)
{
	int ret = 0;

	ret = rts_av_isp_stop();
	if (ret) {
		isp_error("rts_av_isp_stop failed %d \r\n",ret);
	}

	ret = rts_av_isp_cleanup();
	if (ret) {
		isp_error("rts_av_isp_cleanup failed %d /r/n",ret);
	}

	hal_i2c_deinit_simple(&(i2c_master_sample));
	//hal_i2c_deinit_simple(&(i2c_master_aphy_sample));

	hal_gpio_deinit_simple(&gpio_pin_reset);
	hal_gpio_deinit_simple(&gpio_pin_pwdn);

	printf("peri deinit\n\r");
	printf("%s done\r\n", __func__);
	return ret;
}
