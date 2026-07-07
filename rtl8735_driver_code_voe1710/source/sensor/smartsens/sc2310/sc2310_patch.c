/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <rts_isp_patch.h>
#include <rts_isp_sensor_lib.h>
#include <sensor_entry.h>

#ifdef _SC2310_SENSOR_

static int sc2310_patch_init(uint32_t isp_id)
{
	printf("sc2310 patch init\n");
	return RTS_ISP_OK;
}

static int sc2310_patch_cleanup(uint32_t isp_id)
{
	printf("sc2310 patch cleanup\n");
	return RTS_ISP_OK;
}

static int sc2310_patch_preview_start(uint32_t isp_id)
{
	printf("sc2310 patch preview_start\n");
	return RTS_ISP_OK;
}

static int sc2310_patch_preview_stop(uint32_t isp_id)
{
	printf("sc2310 patch preview_stop\n");
	return RTS_ISP_OK;
}

static int sc2310_patch_iq_change(uint32_t isp_id, int iq_sel, int night)
{
	printf("sc2310 patch iq change\n");
	printf("iq_sel: %d, night: %d\n", iq_sel, night);
	return RTS_ISP_OK;
}

static int sc2310_patch_dynamic(uint32_t isp_id,
				const struct isp_notify_dynamic *dynamic)
{
	printf("sc2310 patch dynamic\n");
	printf("gain: %u, color_temp: %u\n",
	      dynamic->ae.gain, dynamic->awb.color_temp);
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_patch_ops sc3235_patch_ops = {
	.init = sc2310_patch_init,
	.cleanup = sc2310_patch_cleanup,
	.preview_start = sc2310_patch_preview_start,
	.preview_stop = sc2310_patch_preview_stop,
	.iq_change = sc2310_patch_iq_change,
	.dynamic = sc2310_patch_dynamic,
};

const void *sc2310_get_patch_ops(void)
{
	return &sc2310_patch_ops;
}
#endif
