/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2018 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

#include <rts_isp_other.h>
#include <isp_top.h>
#include <isp_v4l2_ctrl.h>
#include <isp_core.h>
#include <isp_statis.h>
#include <isp_notify.h>
#include <isp_iq.h>
#include <isp_mod.h>
#include <isp_mod_crop.h>
#include <isp_mod_sensor.h>
#include <isp_mod_ae.h>
#include <isp_mod_flick.h>
#include <isp_hw_flick.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_FLICK

struct isp_mod_flick {
	struct isp_mod mod;
	const struct rts_isp_flick_algo *flick_algo;
	const struct isp_hw_flick_ops *hw_ops;
	float ae_exposure;
	struct {
		enum rts_isp_ae_algo_status ae_status;
		int ae_status_first_set;
	};
	struct v4l2_ctrl *flick_ctrl;
};

static int mod_flick_set_result(struct isp_mod *mod,
				const struct rts_isp_flick_result *result)
{
	int ret = RTS_ISP_OK;
	uint32_t insert_dummy = result->config.insert_dummy_line;
	uint32_t power_line_freq = result->power_line_freq;
	//printf("insert_dummy %d power_line_freq %d \n", insert_dummy, power_line_freq);
	if (result->config.need_update) {
		ret = isp_mod_sibling_execute(mod, MOD_SENSOR,
					      SENSOR_EXEC_SET_DUMMY,
					      &insert_dummy,
					      sizeof(insert_dummy));
		if (ret)
			goto out;
	}

	if (result->need_update) {
		ret = isp_mod_sibling_execute(mod, MOD_AE,
					      AE_EXEC_SET_PLFREQ,
					      &power_line_freq,
					      sizeof(power_line_freq));
		if (ret)
			goto out;
	}

out:
	if (ret)
		isp_perror(ret, "isp set flick result fail");
	return ret;
}

static int set_ae_info(struct isp_mod *mod)
{
	int ret;
	float ae_exposure;
	enum rts_isp_ae_algo_status ae_status;
	struct isp_mod_flick *flick = get_mod(mod, flick);

	ret = isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_EXPOSURE,
				       &ae_exposure, sizeof(ae_exposure));
	if (ret)
		goto out;
	ret = isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_STATUS,
				       &ae_status, sizeof(ae_status));
	if (ret)
		goto out;
	if (flick->ae_exposure != ae_exposure) {
		flick->ae_exposure = ae_exposure;
		if (flick->flick_algo)
			ret = flick->flick_algo->ctrl(mod->owner_id,
						      SET_AE_EXPOSURE,
						      &flick->ae_exposure);
		if (ret)
			isp_perror(ret, "set ae exposure fail");
		return ret;

	}
	if (flick->ae_status_first_set || flick->ae_status != ae_status) {
		flick->ae_status = ae_status;
		if (flick->flick_algo) {
			ret = flick->flick_algo->ctrl(mod->owner_id,
						      SET_AE_STATUS,
						      &flick->ae_status);
			if (ret) {
			isp_perror(ret, "set ae status fail");
		return ret;
	}
			flick->ae_status_first_set = 0;
		}
	}
out:
	if (ret)
		isp_perror(ret, "flick get ae info fail");
	return ret;
}

static int mod_flick_statis_done(struct isp_mod *mod, void *data)
{
	int ret = RTS_ISP_OK;
	const struct rts_isp_flick_statis *statis;
	struct isp_mod_flick *flick = get_mod(mod, flick);


	statis = &((const struct rts_isp_statis *)data)->flick;
	if (flick->flick_algo && statis->valid) {
		static struct rts_isp_flick_result result;

		ret = set_ae_info(mod);
		if (ret)
			goto out;
		result.need_update = RTS_ISP_FALSE;
		result.config.need_update = RTS_ISP_FALSE;
		ret = flick->flick_algo->run(mod->owner_id, statis, &result);
		if (ret)
			goto out;
		ret = mod_flick_set_result(mod, &result);
		if (ret)
			goto out;
	}
out:
	if (ret)
		isp_perror(ret, "flick statis done handle fail");
	//isp_info("%s \r\n",__func__);
	return ret;
}

static int mod_flick_cleanup_algo(struct isp_mod *mod)
{
	struct isp_mod_flick *flick = get_mod(mod, flick);

	if (flick->flick_algo) {
		flick->flick_algo->cleanup(mod->owner_id);
		flick->flick_algo = NULL;
	}
	return RTS_ISP_OK;
}

static int check_flick(const struct rts_isp_flick_algo *flick_algo)
{
	if (!flick_algo)
		return -RTS_ISP_EINVAL;
	if (!flick_algo->init || !flick_algo->cleanup)
		return -RTS_ISP_EINVAL;
	if (!flick_algo->run || !flick_algo->ctrl)
		return -RTS_ISP_EINVAL;
	return RTS_ISP_OK;
}

static int mod_flick_init_algo(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_flick *flick = get_mod(mod, flick);
	struct rts_isp_flick_info info;
	struct isp_mod_ae_stat_info ae_info;

	ret = isp_mod_sibling_get_info(mod, MOD_AE, AE_INFO_STATIS,
				       &ae_info, sizeof(ae_info));
	if (ret)
		return ret;
	info.stat_info = ae_info.info;
	info.cur_power_line_freq = flick->flick_ctrl->cur.val;
	info.algo_param = isp_iq_get_algo_param(mod->owner_id);

	ret = flick->flick_algo->init(mod->owner_id, &info);
	if (ret)
		return ret;
	flick->ae_status_first_set = 1;

	return ret;
}

static int mod_flick_update_algo(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_flick *flick = get_mod(mod, flick);

	mod_flick_cleanup_algo(mod);
	ret = isp_algo_get_flick(isp_top_get_algom(),
				 mod->owner_id, &flick->flick_algo);
	if (ret)
		goto err;
	if (!flick->flick_algo) {
		ret = -RTS_ISP_ENOITEM;
		goto err;
	}
	ret = check_flick(flick->flick_algo);
	if (ret)
		goto err;
	ret = mod_flick_init_algo(mod);
	if (ret)
		goto err;

	return RTS_ISP_OK;
err:
	isp_perror(ret, "update flick algo fail");
	mod_flick_cleanup_algo(mod);
	return ret;
}

static int mod_flick_algo_update(struct isp_mod *mod, void *data)
{
	uint32_t notify_data;

	notify_data = *(uint32_t *)data;
	if (!(notify_data & ISP_ALGO_OTHER_CHANGE_BIT))
		return RTS_ISP_OK;

	return mod_flick_update_algo(mod);
}

static int mod_flick_mcrop_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_flick *flick = get_mod(mod, flick);
	const struct isp_sensor_mode mode;
	const rts_isp_rect_t *isp_rect = data;
	rts_isp_rect_t rect;

	ret = isp_mod_sibling_get_info(mod, MOD_SENSOR, SENSOR_INFO_HDR_MODE,
				       &mode, sizeof(mode));
	if (ret)
		goto err;
	rect.x = isp_rect->x;
	rect.y = isp_rect->y;
	rect.w = isp_rect->w;
	/*
	 * Flicker statis contains up to 9 banding_nums
	 * flick_rect_h <= 9 * banding_lines
	 * banding_lines = min(banding_time_50Hz, banding_time_60Hz) / row_time
	 * row_time = hts / pclk;
	 * row_time_hdr = row_time * 2
	 */
	rect.h = (uint64_t)mode.pclk * 9 / (mode.hts * 120);
	rect.h = min(rect.h, isp_rect->h);
	ret = flick->hw_ops->set_statis(mod->owner_id, &rect);
	if (ret)
		goto err;
	return RTS_ISP_OK;
err:
	isp_perror(ret, "set flick mcrop change fail\n");
	return ret;
}

static struct isp_mod_action_info flick_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_STATIS_DONE, mod_flick_statis_done),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_ALGO_UPDATE, mod_flick_algo_update),
	ISP_NOTIFY_ACTION(ISP_NOTIFY_MCROP_CHANGE, mod_flick_mcrop_change),
};

static int flick_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int ret = RTS_ISP_OK;
	struct isp_mod *mod = ctrl->priv;
	struct isp_mod_flick *flick = get_mod(mod, flick);

	if (ctrl->id != V4L2_CID_POWER_LINE_FREQUENCY)
		return -RTS_ISP_ECTRL;

	if (ctrl->val == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) {
		mod_flick_update_algo(mod);
		if (!flick->flick_algo)
			return -RTS_ISP_ENOTREADY;
		ret = isp_mod_add_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			goto out;
	} else {
		mod_flick_cleanup_algo(mod);
		ret = isp_mod_del_notify(mod, ISP_NOTIFY_STATIS_DONE);
		if (ret)
			goto out;
		//printf("sizeof(ctrl->val)=%d, sizeof(enum rts_isp_power_line_freq)=%d\n",
		//sizeof(ctrl->val),
		//sizeof(enum rts_isp_power_line_freq));
		ret = isp_mod_sibling_execute(mod, MOD_AE, AE_EXEC_SET_PLFREQ,
					      &ctrl->val, sizeof(ctrl->val));
		if (ret)
			goto out;
	}

out:
	if (ret)
		isp_error("set flick ctrl fail %d \n", ret);
	return ret;
}

static const struct v4l2_ctrl_ops flick_ctrl_ops = {
	.s_ctrl = flick_s_ctrl,
};

static int isp_mod_flick_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_flick *flick;

	flick = get_mod(mod, flick);

	flick->hw_ops = isp_hw_flick_get_ops();
	if (!flick->hw_ops) {
		isp_error("get flick hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}


	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_flick_cleanup(struct isp_mod *mod)
{
	mod_flick_cleanup_algo(mod);

	return RTS_ISP_OK;
}

static int isp_mod_flick_add_ctrl(struct isp_mod *mod, void *phandler)
{
	struct isp_mod_flick *flick = get_mod(mod, flick);
	struct v4l2_ctrl_handler *handler = phandler;

	flick->flick_ctrl =
		rtsv_ctrl_new_std_menu(handler, &flick_ctrl_ops,
				       V4L2_CID_POWER_LINE_FREQUENCY,
				       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
					   V4L2_CID_POWER_LINE_FREQUENCY_AUTO, mod);
	if (handler->error) {
		isp_perror(handler->error, "add flick ctrl fail");
		return handler->error;
	}
	return RTS_ISP_OK;
}

static struct isp_mod_flick flick;

int isp_register_mod_flick(void)
{
	memset(&flick, 0, sizeof(flick));
	flick.mod.id = MOD_FLICK;
	flick.mod.name = "flick";
	flick.mod.notify_bits = ISP_ALGO_UPDATE_BIT | ISP_MCROP_CHANGE_BIT;
	flick.mod.init = isp_mod_flick_init;
	flick.mod.cleanup = isp_mod_flick_cleanup;
	flick.mod.add_ctrl = isp_mod_flick_add_ctrl;
	flick.mod.notify_actions = flick_notify_actions;
	flick.mod.notify_actions_num = ARRAY_SIZE(flick_notify_actions);
	return isp_mod_register(&flick.mod);
}

void isp_unregister_mod_flick(void)
{
	isp_mod_unregister(&flick.mod);
}

