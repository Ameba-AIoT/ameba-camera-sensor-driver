#ifndef MPOOL_H
#define MPOOL_H

#if 0
#include "cmsis_os.h"
//#include "freertos_lib.h"

int mpool_create(void);
void *mpool_alloc(uint32_t size);
void mpool_free(void *addr);
uint32_t *mpool_get_alloc_size(uint32_t task_id);

void *RTK_Calloc(size_t size);
void RTK_Free(void *addr);
#endif
#endif
