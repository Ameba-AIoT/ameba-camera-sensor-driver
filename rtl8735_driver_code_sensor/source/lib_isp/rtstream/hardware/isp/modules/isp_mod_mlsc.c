/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_iq.h>
#include <isp_notify.h>
#include <isp_mod.h>
#include <isp_mod_mlsc.h>
#include <isp_hw_mlsc.h>

#define ISP_DEBUG_TYPE ISP_DEBUG_LSC

struct isp_mod_mlsc {
	struct isp_mod mod;
	const struct isp_hw_mlsc_ops *hw_ops;
	const isp_iq_mlsc_t *iq;
};

static int check_mlsc_iq(const isp_iq_mlsc_t *iq)
{
	if (!iq)
		return -RTS_ISP_ENOITEM;
	if (iq->matrix_r_count != iq->matrix_g_count ||
	    iq->matrix_r_count != iq->matrix_b_count)
		return -RTS_ISP_EINVAL;

	return -RTS_ISP_OK;
}

static int isp_mod_mlsc_init(struct isp_mod *mod)
{
	int ret;
	struct isp_mod_mlsc *mlsc;

	mlsc = get_mod(mod, mlsc);
	mlsc->hw_ops = isp_hw_mlsc_get_ops();
	if (mlsc->hw_ops == NULL) {
		isp_error("get mlsc hw ops fail\n");
		ret = -RTS_ISP_ENOOPS;
		goto err;
	}

	return RTS_ISP_OK;
err:
	return ret;
}

static int isp_mod_mlsc_cleanup(struct isp_mod *mod)
{
	return RTS_ISP_OK;
}

static int mod_mlsc_iq_change(struct isp_mod *mod, void *data)
{
	int ret;
	struct isp_mod_mlsc *mlsc = get_mod(mod, mlsc);

	mlsc->iq = isp_iq_get_mlsc(mod->owner_id);
	if (check_mlsc_iq(mlsc->iq))
		return -RTS_ISP_EINVAL;

	ret = mlsc->hw_ops->set_mlsc(mod->owner_id, mlsc->iq);
	if (ret)
		goto err;
	//isp_info("%s done \r\n", __func__);
	return RTS_ISP_OK;
err:
	isp_perror(ret, "mlsc iq change");
	return ret;
}

static struct isp_mod_action_info mlsc_notify_actions[] = {
	ISP_NOTIFY_ACTION(ISP_NOTIFY_IQ_CHANGE, mod_mlsc_iq_change),

};

static struct isp_mod_mlsc mlsc;

int isp_register_mod_mlsc(void)
{
	memset(&mlsc, 0, sizeof(mlsc));
	mlsc.mod.id = MOD_MLSC;
	mlsc.mod.name = "mlsc";
	mlsc.mod.notify_bits = ISP_IQ_CHANGE_BIT;
	mlsc.mod.init = isp_mod_mlsc_init;
	mlsc.mod.cleanup = isp_mod_mlsc_cleanup;
	mlsc.mod.notify_actions = mlsc_notify_actions;
	mlsc.mod.notify_actions_num = ARRAY_SIZE(mlsc_notify_actions);
	return isp_mod_register(&mlsc.mod);
}

void isp_unregister_mod_mlsc(void)
{
	isp_mod_unregister(&mlsc.mod);
}

