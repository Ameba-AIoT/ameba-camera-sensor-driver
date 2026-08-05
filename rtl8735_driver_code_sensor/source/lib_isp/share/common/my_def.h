// ============================================================================
// brief:
//  (1) common define macros here.
//  (2) please keep as simple as possible, and not depend on other .h files as possible.
// ============================================================================
#ifndef __MY_DEF_H__
#define __MY_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_PATH
#define MAX_PATH	(256)
#endif

typedef struct
{
	int	cx;
	int cy;
} size_st;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#endif

#define SZ_1K		0x00000400
#define SZ_2K		0x00000800
#define SZ_4K		0x00001000
#define SZ_8K		0x00002000
#define SZ_16K		0x00004000
#define SZ_32K		0x00008000
#define SZ_64K		0x00010000
#define SZ_128K		0x00020000
#define SZ_256K		0x00040000
#define SZ_384K		0x00060000
#define SZ_512K		0x00080000

#define SZ_1M		0x00100000
#define SZ_2M		0x00200000
#define SZ_4M		0x00400000
#define SZ_8M		0x00800000
#define SZ_16M		0x01000000
#define SZ_31M		0x01F00000
#define SZ_32M		0x02000000
#define SZ_64M		0x04000000
#define SZ_128M		0x08000000
#define SZ_256M		0x10000000
#define SZ_512M		0x20000000

#define SZ_1G		0x40000000
#define SZ_2G		0x80000000


#define ASCII_NUL	0x00	// Null character.
#define ASCII_ETX	0x03	// End of Text.
#define ASCII_BEL	0x07	// Bell.
#define ASCII_BS	0x08	// Backspace.
#define ASCII_HT	0x09	// Horizontal Tab.
#define ASCII_LF	0x0A	// Line Feed.
#define ASCII_CR	0x0D	// Carriage Return.
#define ASCII_ESC	0x1B	// Escape.
#define ASCII_US	0x1F	// Unit Separator.
#define ASCII_SP	0x20	// Space.
#define ASCII_DEL	0x7F	// Delete.
#define ASCII_F1	0x7E

// ----------------------------------------------------------------------------
#ifndef SET_IN_RANGE
#define SET_IN_RANGE(x, min, max)	((x) <= (min) ? (min) : ((x) >= (max) ? (max) : (x)))
#endif

#ifndef MAKE_WORD
#define MAKE_WORD(a, b)			((a) | ((b) << 8))
#endif

#ifndef MAKE_DWORD
#define MAKE_DWORD(a, b, c, d)	((d) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#endif

#ifndef MAKE_WORD_BE
#define MAKE_WORD_BE(a, b)		((b) | ((a) << 8))
#endif

#ifndef MAKE_DWORD_LE
#define MAKE_DWORD_LE(a, b, c, d)	((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#endif

#ifndef MAKE_DWORD_BE
#define MAKE_DWORD_BE(a, b, c, d)	((d) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#endif

#define DWORD_GET_BYTE(v, b)		((v) >> (8*(b)) & 0xff)

#define WORD_SET(b1, b0)	(((b1)<<8) | b0)
#define WORD_GET_BYTE(v, b)	((v) >> (8*(b)) & 0xff)

#define GET_BYTE(v, b)		((v) >> (8*(b)) & 0xff)

// 'p': bit position
// 'b': bit value (0 or 1).
#define GET_BIT(v, p)		((v) >> (p) & 1)
#define CLR_BIT(v, p)		((v) = ((v) & (~(1 << (p)))))
#define SET_BIT(v, p, b)	((v) = ((b) ? ((v) | (1 << (p))) : ((v) & (~(1 << (p))))))

// ----------------------------------------------------------------------------
typedef struct
{
	char	*first;
	char	*second;
} pair_cstr_cstr_st;

typedef struct
{
	int		first;
	char	*second;
} pair_int_cstr_st;

typedef struct
{
	unsigned int	first;
	char	*second;
} pair_uint_cstr_st;

typedef struct
{
	char	first;
	char	second;
} pair_char_char_st;

typedef struct
{
	short	first;
	short	second;
} pair_short_short_st;

typedef struct
{
	int		first;
	int		second;
} pair_int_int_st;

typedef struct
{
	unsigned char	first;
	unsigned char	second;
} pair_uchar_uchar_st;

typedef struct
{
	unsigned short	first;
	unsigned short	second;
} pair_ushort_ushort_st;

typedef struct
{
	unsigned int	first;
	unsigned int	second;
} pair_uint_uint_st;

typedef struct
{
	unsigned long long	first;
	unsigned long long	second;
} pair_u64_u64_st;

// NOTE: plz keep in mind
//  (1) this macro is lack of error detection.
//      use this feature "if not found, out_var's value keep the same" to detect error.
//  (2) use this macro plainly as possible.
//      use a whole line to call it. don't mixed (composed) with other code.
//
#define pair_array_find(out_var, array, find_var) \
{ \
	for (int _i = 0; _i < (int)ARRAY_SIZE(array); _i++) { \
		if ((find_var) == array[_i].first) { \
			(out_var) = array[_i].second; \
			break; \
		} \
	} \
}

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

//
// container_of - cast a member of a structure out to the containing structure
// @ptr:	the pointer to the member.
// @type:	the type of the container struct this is embedded in.
// @member:	the name of the member within the struct.
//
#if 0
#ifndef container_of
#define container_of(ptr, type, member) ({			\
	const typeof(((type *)0)->member) *__mptr = (ptr);	\
	(type *)((char *)__mptr - offsetof(type, member)); })
#endif
#endif

#define abs64(x) ({				\
		s64 __x = (x);			\
		(__x < 0) ? -__x : __x;		\
	})

#if 0
#define min(X, Y)				\
	({ typeof(X) __x = (X);			\
		typeof(Y) __y = (Y);		\
		(__x < __y) ? __x : __y; })

#define max(X, Y)				\
	({ typeof(X) __x = (X);			\
		typeof(Y) __y = (Y);		\
		(__x > __y) ? __x : __y; })

#define MIN(x, y)  min(x, y)
#define MAX(x, y)  max(x, y)
#else

#  ifndef min
#  define min(a, b) (((a) < (b))?(a):(b))
#  endif

#  ifndef max
#  define max(a, b) (((a) > (b))?(a):(b))
#  endif

#  ifndef MIN
#  define MIN(a, b) (((a) < (b))?(a):(b))
#  endif
#  ifndef MAX
#  define MAX(a, b) (((a) > (b))?(a):(b))
#  endif

#endif

#define ROUND(a, b)			(((a) + (b) - 1) & ~((b) - 1))
#define DIV_ROUND(n, d)		(((n) + ((d)/2)) / (d))
#define DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))
//#define roundup(x, y)		((((x) + ((y) - 1)) / (y)) * (y))

// ----------------------------------------------------------------------------
//  memory handling.
// ----------------------------------------------------------------------------
#if (CFG_TRACE_RT_MEM)
#include <malloc.h>
#include <string.h>
void *__rt_malloc(size_t size, const char *caller, int line);
void __rt_free(void *ptr, const char *caller, int line);
void *__rt_memalign(size_t alignment, size_t size, const char *caller, int line);

#define rt_malloc(s)		__rt_malloc((s), __func__, __LINE__)
#define rt_free(p)			__rt_free((p), __func__, __LINE__)
#define rt_memalign(a, s)	__rt_memalign((a), (s), __func__, __LINE__)

#else

//#include <malloc.h>
#include <string.h>
#include "memleak.h"
#define rt_malloc		malloc
#define rt_free			free
#define rt_memalign		memalign
#endif	// CFG_TRACE_RT_MEM

#ifndef rt_safe_free
#define rt_safe_free(p) \
	do { \
		if (p) { rt_free((p)); } \
		(p) = NULL; \
	} while (0)
#endif

#ifndef rt_safe_release
#define rt_safe_release(p, func) \
	do { \
		if (p) { func((p)); } \
		(p) = NULL; \
	} while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif	// __MY_DEF_H__
