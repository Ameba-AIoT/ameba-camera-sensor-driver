#ifndef _ISP_MEM_H_INC_
#define _ISP_MEM_H_INC_

#include <stdlib.h>
#include <string.h>

#include <rtscamkit.h>

#define isp_malloc(size) rts_malloc(size)
#define isp_calloc(nmemb, size) rts_calloc(nmemb, size)
#define isp_realloc(ptr, size) rts_realloc(ptr, size)
#define isp_free(ptr) do {if (ptr) {rts_free(ptr); } } while (0)

//#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#define malloc isp_malloc
#define free isp_free
#define calloc isp_calloc
#define realloc isp_realloc
//#endif

#define isp_memcpy(dst, src, size) memcpy(dst, src, size)

#define isp_calloc_item(item) (item = isp_calloc(1, sizeof(*(item))))
#define isp_calloc_array(item, n) (item = isp_calloc(n, sizeof(*(item))))
#define isp_memcpy_array(dst, src, size) ({ \
	typeof(dst[0]) *_dst = (dst); \
	typeof(src[0]) *_src = (src); \
	const typeof(dst[0]) *__dst = _dst; \
	const typeof(src[0]) *__src = _src; \
	(void) (&__src == &__dst); \
	memcpy(_dst, _src, (size) * sizeof(*_dst)); \
})
#define isp_memcmp_array(arr0, arr1, count) ({ \
	typeof(arr0) _arr0 = arr0; \
	typeof(arr1) _arr1 = arr1; \
	(void) (&_arr0 == &_arr1); \
	memcmp(_arr0, _arr1, count * sizeof(*_arr0)); \
})

#endif /* _ISP_MEM_H_INC_ */
