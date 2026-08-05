#ifndef __RT_TYPES_H__
#define __RT_TYPES_H__

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#if 0
#include "rlx_types.h"

#define IN
#define OUT
#define INOUT

typedef signed char			s8;
typedef unsigned char		u8;

typedef signed short		s16;
typedef unsigned short		u16;

typedef signed int			s32;
typedef unsigned int		u32;

typedef signed long long	s64;
typedef unsigned long long	u64;

typedef unsigned int		size_t;

#ifndef bool
typedef unsigned char		bool;
#endif

#ifndef handle_t
typedef u32					handle_t;
#endif

// ----------------------------------------------------------------------------
// Win32 style
// ----------------------------------------------------------------------------
#ifndef BOOL
#define BOOL			unsigned char
#endif

#ifndef FALSE
#define FALSE			0
#endif

#ifndef TRUE
#define TRUE			(!FALSE)
#endif

#ifndef BYTE
typedef unsigned char	BYTE;
#endif

#ifndef SHORT
typedef short			SHORT;
#endif

#ifndef WORD
typedef unsigned short	WORD;
#endif

#ifndef WCHAR
typedef unsigned short	WCHAR;
#endif

#ifndef INT
typedef int				INT;
#endif

#ifndef UINT
typedef unsigned int	UINT;
#endif

#ifndef LONG
typedef long			LONG;
#endif

#ifndef DWORD
typedef unsigned long	DWORD;
#endif

#ifndef ULONG
typedef unsigned long	ULONG;
#endif

// ----------------------------------------------------------------------------
// sysv style
// ----------------------------------------------------------------------------
typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

// ----------------------------------------------------------------------------
// ref from uboot's /arch/rlx/include/asm/types.h
// maybe remove in future.
// ----------------------------------------------------------------------------
typedef signed char		__s8;
typedef unsigned char	__u8;

typedef signed short	__s16;
typedef unsigned short	__u16;

typedef signed int		__s32;
typedef unsigned int	__u32;

typedef signed long long	__s64;
typedef unsigned long long	__u64;
#endif



// ----------------------------------------------------------------------------
// functions implemented in my_def.c
// ----------------------------------------------------------------------------
#define RT_TYPE_DEFINE(_sign, _size)	(((_sign) << 4) | (_size))

typedef enum
{
	// special type
	RT_TYPE_VOID	= RT_TYPE_DEFINE(8, 0),
	RT_TYPE_STR		= RT_TYPE_DEFINE(9, 0),
	// simple type
	RT_TYPE_U8		= RT_TYPE_DEFINE(0, 1),
	RT_TYPE_S8		= RT_TYPE_DEFINE(1, 1),
	RT_TYPE_U16		= RT_TYPE_DEFINE(0, 2),
	RT_TYPE_S16		= RT_TYPE_DEFINE(1, 2),
	RT_TYPE_U32		= RT_TYPE_DEFINE(0, 4),
	RT_TYPE_S32		= RT_TYPE_DEFINE(1, 4),
} RT_TYPE_E;

#define RT_TYPE_SIZEOF(t)		((t) & 0x0f)
#define RT_TYPE_IS_SIGNED(t)	((t) & 0x10)
#define RT_TYPE_IS_SPECIAL(t)	((t) & 0x80)
#define RT_TYPE_IS_SIMPLE(t)	((t) & 0x80 == 0)
#define RT_TYPE_IS_VOID(t)		((t) == RT_TYPE_VOID)
#define RT_TYPE_IS_STR(t)		((t) == RT_TYPE_STR)

// example:
//  RT_TYPE_CAST(RT_TYPE_U8, 0xFF) will return 255
//  RT_TYPE_CAST(RT_TYPE_S8, 0xFF) will return  -1
//
// note: NO @type checking.
//
s64 RT_TYPE_CAST(RT_TYPE_E type, s64 val);

// step:
// (1) convert buf[] to a s64 value
// (2) call RT_TYPE_CAST()
//
s64 RT_TYPE_CAST_BY_STR(RT_TYPE_E type, u8 *buf, u8 len);

#endif	// __RT_TYPES_H__
