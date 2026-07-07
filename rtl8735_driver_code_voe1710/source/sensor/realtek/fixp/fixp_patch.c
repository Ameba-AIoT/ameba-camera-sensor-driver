/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2020 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <stdio.h>
#include <rts_isp_patch.h>
#include <sensor_entry.h>
/* #define DEBUG */
#ifdef DEBUG
#define debug(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

static int fixp_patch_init(uint32_t isp_id)
{
	debug("fixp patch init\n");
	return RTS_ISP_OK;
}

static int fixp_patch_cleanup(uint32_t isp_id)
{
	debug("fixp patch cleanup\n");
	return RTS_ISP_OK;
}

static int fixp_patch_preview_start(uint32_t isp_id)
{
	debug("fixp patch preview_start\n");
	return RTS_ISP_OK;
}

static int fixp_patch_preview_stop(uint32_t isp_id)
{
	debug("fixp patch preview_stop\n");
	return RTS_ISP_OK;
}

static int fixp_patch_iq_change(uint32_t isp_id, int iq_sel, int night)
{
	debug("fixp patch iq change\n");
	debug("iq_sel: %d, night: %d\n", iq_sel, night);
	return RTS_ISP_OK;
}

static int fixp_patch_dynamic(uint32_t isp_id,
				const struct isp_notify_dynamic *dynamic)
{
	debug("fixp patch dynamic\n");
	debug("gain: %u, color_temp: %u\n",
	      dynamic->ae.gain, dynamic->awb.color_temp);
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_patch_ops fixp_patch_ops = {
	.init = fixp_patch_init,
	.cleanup = fixp_patch_cleanup,
	.preview_start = fixp_patch_preview_start,
	.preview_stop = fixp_patch_preview_stop,
	.iq_change = fixp_patch_iq_change,
	.dynamic = fixp_patch_dynamic,
};

const void *fixp_get_patch_ops(void)
{
	return &fixp_patch_ops;
}

