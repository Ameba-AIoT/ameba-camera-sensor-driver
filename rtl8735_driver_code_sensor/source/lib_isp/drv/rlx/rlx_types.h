// ============================================================================
// brief: type definition for /rlx layer
// rule:
//	- ALLOW
//		- C-lang  : char, short, int, unsigned char, ...
//		- stdint.h: int8_t, int16_t, int32_t, uint8_t, ...
//		- 64-bit  :
//			'signed   long long' as signed   64-bits
//			'unsigned long long' as unsigned 64-bits
//	- FORBID
//		- rt_types.h : BOOL, bool, s8, u8, s16, u16, ...
//		- Win32 style: BYTE, WORD, DWORD, ...
//		- sysv style : uchar, ushort, uint, ulong, ...
//
// note: rt_types.h also include this file.
//
// ============================================================================
#ifndef RLX_TYPES_H
#define RLX_TYPES_H

#if 1
#include <stdint.h>
#else
typedef signed char		int8_t;
typedef unsigned char	uint8_t;

typedef signed short	int16_t;
typedef unsigned short	uint16_t;

typedef signed int		int32_t;
typedef unsigned int	uint32_t;
#endif

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(COND,MSG) typedef char __STATIC_ASSERT(__LINE__, __COUNTER__)[(COND)?1:-1];
#define __STATIC_ASSERT(LINE, COUNTER) ___STATIC_ASSERT(LINE, COUNTER)
#define ___STATIC_ASSERT(LINE, COUNTER) pb_static_assertion_##LINE##COUNTER
#endif

//STATIC_ASSERT(sizeof(long long) == 4, "64-bit type not support by compiler!");

// ----------------------------------------------------------------------------
// types that conceptually below driver layer
// ----------------------------------------------------------------------------
//typedef unsigned int	dma_addr_t;
typedef unsigned int	phys_addr_t;
typedef unsigned int	phys_size_t;
// ----------------------------------------------------------------------------
// bit macros
// ----------------------------------------------------------------------------
#define BIT0		0x0001
#define BIT1		0x0002
#define BIT2		0x0004
#define BIT3		0x0008
#define BIT4		0x0010
#define BIT5		0x0020
#define BIT6		0x0040
#define BIT7		0x0080
#define BIT8		0x0100
#define BIT9		0x0200
#define BIT10		0x0400
#define BIT11		0x0800
#define BIT12		0x1000
#define BIT13		0x2000
#define BIT14		0x4000
#define BIT15		0x8000
#define BIT16		0x00010000
#define BIT17		0x00020000
#define BIT18		0x00040000
#define BIT19		0x00080000
#define BIT20		0x00100000
#define BIT21		0x00200000
#define BIT22		0x00400000
#define BIT23		0x00800000
#define BIT24		0x01000000
#define BIT25		0x02000000
#define BIT26		0x04000000
#define BIT27		0x08000000
#define BIT28		0x10000000
#define BIT29		0x20000000
#define BIT30		0x40000000
#define BIT31		0x80000000

#ifndef BIT_
#define BIT_(__n)	(1<<(__n))
#endif

#ifndef BIT
#define BIT(__n)	(1<<(__n))
#endif


#endif	// RLX_TYPES_H
