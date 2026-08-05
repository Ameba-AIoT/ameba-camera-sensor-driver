/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <rts_isp.h>

static void get_user_ae_setting(struct rts_isp_ae_setting *setting)
{
	int mode;

	printf("mode: 0 for auto, 1 for manual: ");
	scanf("%d", &mode);
	setting->mode = !!mode;
	if (setting->mode == RTS_ISP_AE_AUTO_MODE) {
		uint8_t weight;

		printf("weight: ");
		scanf("%hhu", &weight);
		memset(setting->_auto.win_weights, weight,
		       setting->_auto.window_num);
		printf("target_delta: ");
		scanf("%d", &setting->_auto.target_delta);
		printf("gain_max: ");
		scanf("%hu", &setting->_auto.gain_max);
		printf("min_fps: ");
		scanf("%hhu", &setting->_auto.min_fps);
	} else {
		printf("exposure: ");
		scanf("%u", (unsigned int *)&setting->_manual.exposure_time);
		printf("total_gain: ");
		scanf("%hu", &setting->_manual.total_gain);
		printf("analog gain: ");
		scanf("%hu", &setting->_manual.gain.analog_gain);
		printf("digital gain: ");
		scanf("%hu", &setting->_manual.gain.digital_gain);
		printf("isp gain: ");
		scanf("%hu", &setting->_manual.gain.isp_gain);
	}
}

static void print_ae_setting(const struct rts_isp_ae_setting *setting)
{
	int i;

	printf("mode is %d\n", setting->mode);

	printf("auto setting:\n");
	printf("  weights is:\n");
	for (i = 0; i < (int)setting->_auto.window_num; i++) {
		if (i % 16 == 0)
			printf("    ");
		printf("%02x ", setting->_auto.win_weights[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("  target_delta is %d\n", setting->_auto.target_delta);
	printf("  gain_max is %u\n", setting->_auto.gain_max);
	printf("  min_fps is %u\n", setting->_auto.min_fps);

	printf("manual setting:\n");
	printf("  exposure is %u\n", (unsigned int)setting->_manual.exposure_time);
	printf("  total_gain is %u\n", setting->_manual.total_gain);
	printf("  analog gain is %u\n", setting->_manual.gain.analog_gain);
	printf("  digital gain is %u\n", setting->_manual.gain.digital_gain);
	printf("  isp gain is %u\n", setting->_manual.gain.isp_gain);
}

int cmd_test_ae_setting(int argc, char *argv[])
{
	int ret;
	struct rts_isp_ae_setting *setting;

	ret = rts_isp_query_ae_setting(ISP0, &setting);
	if (ret) {
		rts_isp_perror(ret, "query setting fail");
		return ret;
	}
	print_ae_setting(setting);
	get_user_ae_setting(setting);
	ret = rts_isp_set_ae_setting(ISP0, setting);
	if (ret) {
		rts_isp_perror(ret, "set setting fail");
		rts_isp_release_ae_setting(ISP0, setting);
		return ret;
	}
	print_ae_setting(setting);
	rts_isp_release_ae_setting(ISP0, setting);
	return 0;
}
