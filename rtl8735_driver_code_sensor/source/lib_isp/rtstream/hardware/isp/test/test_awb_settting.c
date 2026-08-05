/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <rts_isp.h>

static int get_user_awb_setting(struct rts_isp_awb_setting *setting)
{
	printf("mode: 0 for temperature, 1 for auto, 2 for component: ");
	scanf("%d", (int *)&setting->mode);
	if (setting->mode == RTS_ISP_AWB_TEMPERATURE_MODE) {
		printf("color temperature: ");
		scanf("%u", (unsigned int *)&setting->_temperature.temperature);
	} else if (setting->mode == RTS_ISP_AWB_AUTO_MODE) {
		printf("r gain adjustment: ");
		scanf("%hu", &setting->_auto.r_gain_adj);
		printf("b gain adjustment: ");
		scanf("%hu", &setting->_auto.b_gain_adj);
	} else if (setting->mode == RTS_ISP_AWB_COMPONENT_MODE) {
		printf("r gain: ");
		scanf("%hu", &setting->_component.r_gain);
		printf("g gain: ");
		scanf("%hu", &setting->_component.g_gain);
		printf("b gain: ");
		scanf("%hu", &setting->_component.b_gain);
	} else {
		return -RTS_ISP_EINVAL;
	}
	return RTS_ISP_OK;
}

static void print_awb_setting(const struct rts_isp_awb_setting *setting)
{
	printf("mode is %d\n", setting->mode);

	printf("temperature setting:\n");
	printf("  color temperature is: %u\n",
	       (unsigned int)setting->_temperature.temperature);

	printf("auto setting:\n");
	printf("  r gain adjust is %u\n", setting->_auto.r_gain_adj);
	printf("  b gain adjust is %u\n", setting->_auto.b_gain_adj);

	printf("component setting:\n");
	printf("  r gain is %u\n", setting->_component.r_gain);
	printf("  g gain is %u\n", setting->_component.g_gain);
	printf("  b gain is %u\n", setting->_component.b_gain);
}

int cmd_test_awb_setting(int argc, char *argv[])
{
	int ret;
	struct rts_isp_awb_setting *setting;

	ret = rts_isp_query_awb_setting(ISP0, &setting);
	if (ret) {
		rts_isp_perror(ret, "query setting fail");
		return ret;
	}
	print_awb_setting(setting);
	ret = get_user_awb_setting(setting);
	if (ret)
		return ret;
	ret = rts_isp_set_awb_setting(ISP0, setting);
	if (ret) {
		rts_isp_perror(ret, "set setting fail");
		rts_isp_release_awb_setting(ISP0, setting);
		return ret;
	}
	print_awb_setting(setting);
	rts_isp_release_awb_setting(ISP0, setting);
	return 0;
}
