#ifndef RT_TLSF
#define RT_TLSF

int rt_tlsf_init(void);
void *rt_tlsf_malloc(size_t size);
void rt_tlsf_free(void* ptr);
void *rt_tlsf_calloc(size_t nitems, size_t size);
void* rt_tlsf_realloc(void *ptr, size_t size);

#endif
