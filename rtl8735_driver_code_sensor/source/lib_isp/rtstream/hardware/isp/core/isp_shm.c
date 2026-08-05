/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 */

#include "cmsis_os2.h"
#include "rt_types.h"
#include "rt_task.h"
#include "rtscamkit.h"
#include <isp_mod_statis.h>
#include <isp_mod_iq.h>

void *gbl_ae_shm=NULL;
void *gbl_af_shm=NULL;
void *gbl_awb_shm=NULL;
void *gbl_tuning_shm=NULL;

void *gbl_tuning_parm_shm=NULL;
void *gbl_tuning_iqtable_shm=NULL;

#include <isp_top.h>
#include <isp_utils.h>
#include <isp_shm.h>

int isp_shm_init(struct isp_shm *shm, int size, const char *name)
{
	int ret = RTS_ISP_OK;
	size_t len = 0;

	shm->fn[0] = 0;
	shm->buf = rts_malloc(size);
	if ( !shm->buf ) {
		printf("%s shm->buf alloc fail\n", name);
		ret = RTS_ISP_ENOMEM;
		goto err;
	}
	if (!strcmp(name, AE_STATIS_SHM_NAME)) {
		gbl_ae_shm = shm->buf;
	} else if (!strcmp(name, AWB_STATIS_SHM_NAME)) {
		gbl_awb_shm = shm->buf;
	} else if (!strcmp(name, AF_STATIS_SHM_NAME)) {
		gbl_af_shm = shm->buf;
	} else if (!strcmp(name, TUNING_STATIS_SHM_NAME)) {
		gbl_tuning_shm = shm->buf;
	}

	if (!strcmp(name, TUNING_PARAM_SHM_NAME)) {
		gbl_tuning_parm_shm = shm->buf;
	} else if (!strcmp(name, TUNING_IQ_TABLE_SHM_NAME)) {
		gbl_tuning_iqtable_shm = shm->buf;
	}

	len = strlen(name);

	if (len < SHM_FN_SIZE) {
		memcpy(shm->fn, name, len);
		shm->fn[len] = '\0';
	} else {
		memset(shm->fn, 0, SHM_FN_SIZE);
	}

err:

	return ret;
}

void isp_shm_cleanup(struct isp_shm *shm, int size, const char *name)
{
	shm->fn[0] = 0;
	rts_free(shm->buf);
}

