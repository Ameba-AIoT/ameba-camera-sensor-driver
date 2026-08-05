#ifndef _ISP_SHM_H_INC_
#define _ISP_SHM_H_INC_

#include <isp_atomic.h>
#include "cmsis_os2.h"

#define SHM_FN_SIZE	32
struct isp_shm {
	void *handle;
	void *buf;
	char fn[SHM_FN_SIZE];
};

int isp_shm_init(struct isp_shm *shm, int size, const char *name);
void isp_shm_cleanup(struct isp_shm *shm, int size, const char *name);

#endif /* _ISP_SHM_H_INC_ */

