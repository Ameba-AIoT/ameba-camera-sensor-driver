#ifndef _ISP_UTIL_H_INC_
#define _ISP_UTIL_H_INC_

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define ___PASTE(a, b) a##b
#define __PASTE(a, b) ___PASTE(a, b)
#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#define __min(t1, t2, min1, min2, x, y) ({ \
	t1 min1 = (x); \
	t2 min2 = (y); \
	(void) ((int)&min1 == (int)&min2); \
	min1 < min2 ? min1 : min2; })
#ifdef min
  #undef min
#endif
#define min(x, y) \
	__min(typeof(x), typeof(y), \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_), \
	      x, y)

#define __max(t1, t2, max1, max2, x, y) ({ \
	t1 max1 = (x); \
	t2 max2 = (y); \
	(void) ((int)&max1 == (int)&max2); \
	max1 > max2 ? max1 : max2; })
#ifdef max
  #undef max
#endif
#define max(x, y) \
	__max(typeof(x), typeof(y), \
	      __UNIQUE_ID(max1_), __UNIQUE_ID(max2_), \
	      x, y)

#define min3(x, y, z) min((typeof(x))min(x, y), z)
#define max3(x, y, z) max((typeof(x))max(x, y), z)

#define clamp(val, lo, hi) min((typeof(val))max(val, lo), hi)
#define clamp_t(type, val, lo, hi) min_t(type, max_t(type, val, lo), hi)

#define min_t(type, x, y) \
	__min(type, type, \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_), \
	      x, y)

#define max_t(type, x, y) \
	__max(type, type, \
	      __UNIQUE_ID(min1_), __UNIQUE_ID(min2_), \
	      x, y)

/*
#define container_of(ptr, type, member) ({ \
	const typeof(((type *)0)->member) *__mptr = (ptr); \
	(type *)((char *)__mptr - offsetof(type, member)); })
*/

#ifdef ARRAY_SIZE
  #undef ARRAY_SIZE
#endif
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define isp_fourcc(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | \
				((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))
static inline void isp_fourcc_str(char str[5], uint32_t fourcc)
{
	if (!str)
		return;
	str[0] = ((fourcc >> 0) & 0xff);
	str[1] = ((fourcc >> 8) & 0xff);
	str[2] = ((fourcc >> 16) & 0xff);
	str[3] = ((fourcc >> 24) & 0xff);
	str[4] = '\0';
}

#define has_op(master, op) ((master)->op)
#define isp_call_op(master, op, ...) \
	(has_op(master, op) ? \
	(master)->op(master, ##__VA_ARGS__) : -RTS_ISP_ENOOPS)
#define isp_call_op_ret(ret, master, op, ...) \
	(ret = isp_call_op(master, op, ##__VA_ARGS__))

#define isp_close(fd) \
	do { \
		if (fd >= 0) \
			close(fd); \
		fd = -1; \
	} while (0)

#define isp_release(ptr, call_back) \
	do { \
		if (ptr) \
			call_back(ptr); \
		ptr = NULL; \
	} while (0)

#define ___constant_swab16(x) ((uint16_t)( \
	(((uint16_t)(x) & (uint16_t)0x00ffU) << 8) | \
	(((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define ___constant_swab32(x) ((uint32_t)( \
	(((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) | \
	(((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) | \
	(((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) | \
	(((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define ___constant_swab64(x) ((uint64_t)( \
	(((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) | \
	(((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) | \
	(((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) | \
	(((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) | \
	(((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) | \
	(((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) | \
	(((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) | \
	(((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

#define cpu_to_eb64(x) ___constant_swab64(x)
#define cpu_to_eb32(x) ___constant_swab32(x)
#define cpu_to_eb16(x) ___constant_swab16(x)
#define eb64_to_cpu(x) ___constant_swab64(x)
#define eb32_to_cpu(x) ___constant_swab32(x)
#define eb16_to_cpu(x) ___constant_swab16(x)

#define ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define ALIGN(x, a) ALIGN_MASK(x, (typeof(x))(a) - 1)
#define ALIGN_DOWN(x, a) ALIGN((x) - ((a) - 1), (a))
#define PTR_ALIGN(p, a) ((typeof(p))ALIGN((unsigned long)(p), (a)))

#ifdef roundup
  #undef roundup
#endif
#define roundup(x, y) ( \
{ \
	const typeof(y) __y = y; \
	(((x) + (__y - 1)) / __y) * __y; \
} \
)
#define rounddown(x, y) ( \
{ \
	typeof(x) __x = (x); \
	__x - (__x % (y)); \
} \
)
#define roundup_div(x, y) ( \
{ \
	const typeof(y) __y = y; \
	((x) + (__y - 1)) / __y; \
} \
)

#define float_tol 0.0001f
#define float_ne(x, y) (fabsf((float)x - (float)y) > float_tol)
#define float_eq(x, y) (fabsf((float)x - (float)y) < float_tol)


#define set_const_var(var, value) \
	do { \
		typeof((var) + 0) *pvar = (typeof((var) + 0) *)&var; \
		*pvar = value; \
	} while (0)

#define set_const_var_type(type, var, value) \
	do { \
		type *pvar = (type *)&var; \
		*pvar = value; \
	} while (0)

#define isp_set_bit(val, bit) ((val) |= (1 << (bit)))
#define isp_clr_bit(val, bit) ((val) &= ~(1 << (bit)))
#define isp_test_bit(val, bit) ((val) & (1 << (bit)))

#define _ISP_AID_NRBITS 8
#define _ISP_AID_TYPEBITS 8
#define _ISP_AID_SIZEBITS 14
#define _ISP_AID_DIRBITS 2

#define _ISP_AID_NRMASK ((1 << _ISP_AID_NRBITS) - 1)
#define _ISP_AID_TYPEMASK ((1 << _ISP_AID_TYPEBITS) - 1)
#define _ISP_AID_SIZEMASK ((1 << _ISP_AID_SIZEBITS) - 1)
#define _ISP_AID_DIRMASK ((1 << _ISP_AID_DIRBITS) - 1)

#define _ISP_AID_NRSHIFT 0
#define _ISP_AID_TYPESHIFT (_ISP_AID_NRSHIFT + _ISP_AID_NRBITS)
#define _ISP_AID_SIZESHIFT (_ISP_AID_TYPESHIFT + _ISP_AID_TYPEBITS)
#define _ISP_AID_DIRSHIFT (_ISP_AID_SIZESHIFT + _ISP_AID_SIZEBITS)

#define ISP_AID_TYPE(id) (((id) >> _ISP_AID_TYPESHIFT) & _ISP_AID_TYPEMASK)
#define ISP_AID_NR(id) (((id) >> _ISP_AID_NRSHIFT) & _ISP_AID_NRMASK)
#define ISP_AID_SIZE(id) (((id) >> _ISP_AID_SIZESHIFT) & _ISP_AID_SIZEMASK)
#define ISP_AID_DIR(id) (((id) >> _ISP_AID_DIRSHIFT) & _ISP_AID_DIRMASK)

#define _AID_NONE 0
#define _AID_READ 1
#define _AID_WRITE 2

#define ISP_AID_IS_NONE(action) (!ISP_AID_DIR(action))
#define ISP_AID_IS_READ(action) (ISP_AID_DIR(action) & _AID_READ)
#define ISP_AID_IS_WRITE(action) (ISP_AID_DIR(action) & _AID_WRITE)

#define ISP_AID_HAS_DATA(action) (!!ISP_AID_SIZE(action))
#define ISP_AID_HAS_READ_DATA(action) \
	(ISP_AID_IS_READ(action) && ISP_AID_SIZE(action))
#define ISP_AID_HAS_WRITE_DATA(action) \
	(ISP_AID_IS_WRITE(action) && ISP_AID_SIZE(action))

#define isp_action_size(dir, type, nr, size) \
	(uint32_t)(((dir) << _ISP_AID_DIRSHIFT) | \
		   ((type) << _ISP_AID_TYPESHIFT) | \
		   ((nr) << _ISP_AID_NRSHIFT) | \
		   ((size) << _ISP_AID_SIZESHIFT))

#define isp_action(type, nr) \
	isp_action_size(_AID_NONE, type, nr, 0)
#define isp_action_r(type, nr, data) \
	isp_action_size(_AID_READ, type, nr, sizeof(data))
#define isp_action_w(type, nr, data) \
	isp_action_size(_AID_WRITE, type, nr, sizeof(data))
#define isp_action_wr(type, nr, data) \
	isp_action_size(_AID_READ | _AID_WRITE, type, nr, sizeof(data))

#define INFO_TYPE 'I'
#define EXEC_TYPE 'E'
#define NOTIFY_TYPE 'N'


uint32_t isp_upper_power_of_2(uint32_t val);
int isp_closexec(int fd, int set);
int isp_nonblock(int fd, int set);
int isp_lock_file(int fd, int block);
int isp_unlock_file(int fd, int block);
ssize_t isp_strlcpy(char *dest, const char *src, size_t size);
int isp_get_val_weight(uint32_t val);

int linear_intp(int x, int x0, int y0, int x1, int y1);
float linear_intp_float(float x, float x0, float y0, float x1, float y1);
int linear_intp_bound(int x, int x0, int y0, int x1, int y1);
#define linear_intp_array(arr, x, x0, arr0, x1, arr1, count) ({ \
	int i; \
	int ret = RTS_ISP_OK; \
	if ((arr) == NULL || (arr0) == NULL || (arr1) == NULL) \
		ret = -RTS_ISP_EINVAL; \
	else \
		for (i = 0; i < (int)(count); i++) \
			(arr)[i] = linear_intp((x), (x0), (arr0)[i], \
					       (x1), (arr1)[i]); \
	ret; \
})

int calc_smooth(int current, int target, int div, int max);
#define calc_smooth_array(current, target, div, max, count) \
	do { \
		int i; \
		for (i = 0; i < (int)(count); i++) \
			(current)[i] = calc_smooth((current)[i], (target)[i], \
						   (div), (max)); \
	} while (0)

float calc_smooth_float(float current, float target, float div, float max);

#endif /* _ISP_UTIL_H_INC_ */
