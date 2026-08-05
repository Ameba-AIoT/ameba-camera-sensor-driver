#ifndef __RLX_BITOPS_H__
#define __RLX_BITOPS_H__
#include "rlx_inc.h"




#if 0
#include "rlx_reg.h"

# define rlx_set_bit(nr, adr)	REG_W32((adr), (REG_R32(adr) | (1 << (nr))))
# define rlx_clr_bit(nr, adr)	REG_W32((adr), (REG_R32(adr) & (~(1 << (nr)))))
#else
# define rlx_set_bit	set_bit
# define rlx_clr_bit	clear_bit
#endif


#if 0

#define save_and_cli taskENTER_CRITICAL
#define restore_flags taskEXIT_CRITICAL
#define cli taskDISABLE_INTERRUPTS
#if 0
void save_and_cli()
{
	taskENTER_CRITICAL();
}

void restore_flags()
{
	taskEXIT_CRITICAL();
}

void cli()
{
	taskDISABLE_INTERRUPTS();
}
#endif

#endif

#if 0
// ----------------------------------------------------------------------------
// copy from uboot's /arch/rlx/include/asm/system.h
//extern
__inline__ void
__sti(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,0x1f\n\t"
		"xori\t$1,0x1e\n\t"
		"mtc0\t$1,$12\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

/*
 * For cli() we have to insert nops to make shure that the new value
 * has actually arrived in the status register before the end of this
 * macro.
 * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs
 * no nops at all.
 */
//extern
__inline__ void
__cli(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,1\n\t"
		"xori\t$1,1\n\t"
		".set\tnoreorder\n\t"
		"mtc0\t$1,$12\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

#define __save_flags(x)						\
({											\
	__asm__ __volatile__(					\
		".set\tpush\n\t"					\
		".set\treorder\n\t"					\
		"mfc0\t%0,$12\n\t"					\
		".set\tpop\n\t"						\
		: "=r" (x));						\
})

#define __save_and_cli(x)					\
({											\
	__asm__ __volatile__(					\
		".set\tpush\n\t"					\
		".set\treorder\n\t"					\
		".set\tnoat\n\t"					\
		"mfc0\t%0,$12\n\t"					\
		"ori\t$1,%0,1\n\t"					\
		"xori\t$1,1\n\t"					\
		".set\tnoreorder\n\t"				\
		"mtc0\t$1,$12\n\t"					\
		"nop\n\t"							\
		"nop\n\t"							\
		"nop\n\t"							\
		".set\tpop\n\t"						\
		: "=r" (x)							\
		: /* no inputs */					\
		: "$1", "memory");					\
})

#define __restore_flags(flags)				\
do {										\
	unsigned long __tmp1;					\
											\
	__asm__ __volatile__(					\
		".set\tnoreorder\t\t\t# __restore_flags\n\t"		\
		".set\tnoat\n\t"					\
		"mfc0\t$1, $12\n\t"					\
		"andi\t%0, 1\n\t"					\
		"ori\t$1, 1\n\t"					\
		"xori\t$1, 1\n\t"					\
		"or\t%0, $1\n\t"					\
		"mtc0\t%0, $12\n\t"					\
		"nop\n\t"							\
		"nop\n\t"							\
		"nop\n\t"							\
		".set\tat\n\t"						\
		".set\treorder"						\
		: "=r" (__tmp1)						\
		: "0" (flags)						\
		: "$1", "memory");					\
} while (0)
#endif
// ----------------------------------------------------------------------------
// copy from uboot's /arch/rlx/include/asm/bitops.h
#if 0
#ifdef __KERNEL__

/*
 * clear_bit() doesn't provide any barrier for the compiler.
 */
#define smp_mb__before_clear_bit()	barrier()
#define smp_mb__after_clear_bit()	barrier()

/*
 * Only disable interrupt for kernel mode stuff to keep usermode stuff
 * that dares to use kernel include files alive.
 */
#define __bi_flags unsigned long flags
#define __bi_cli() __cli()
#define __bi_save_flags(x) __save_flags(x)
#define __bi_save_and_cli(x) __save_and_cli(x)
#define __bi_restore_flags(x) __restore_flags(x)
#else
#define __bi_flags
#define __bi_cli()
#define __bi_save_flags(x)
#define __bi_save_and_cli(x)
#define __bi_restore_flags(x)
#endif /* __KERNEL__ */


#ifdef CONFIG_CPU_HAS_LLSC

#include <asm/rlxregs.h>

/*
 * These functions for MIPS ISA > 1 are interrupt and SMP proof and
 * interrupt friendly
 */

/*
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static __inline__ void
set_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp;

	__asm__ __volatile__(
		"1:\tll\t%0, %1\t\t# set_bit\n\t"
		"or\t%0, %2\n\t"
		"sc\t%0, %1\n\t"
		"beqz\t%0, 1b"
		: "=&r" (temp), "=m" (*m)
		: "ir" (1UL << (nr & 0x1f)), "m" (*m));
}

/*
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static __inline__ void __set_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);

	*m |= 1UL << (nr & 31);
}
#define PLATFORM__SET_BIT

/*
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static __inline__ void
clear_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp;

	__asm__ __volatile__(
		"1:\tll\t%0, %1\t\t# clear_bit\n\t"
		"and\t%0, %2\n\t"
		"sc\t%0, %1\n\t"
		"beqz\t%0, 1b\n\t"
		: "=&r" (temp), "=m" (*m)
		: "ir" (~(1UL << (nr & 0x1f))), "m" (*m));
}

/*
 * change_bit - Toggle a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static __inline__ void
change_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp;

	__asm__ __volatile__(
		"1:\tll\t%0, %1\t\t# change_bit\n\t"
		"xor\t%0, %2\n\t"
		"sc\t%0, %1\n\t"
		"beqz\t%0, 1b"
		: "=&r" (temp), "=m" (*m)
		: "ir" (1UL << (nr & 0x1f)), "m" (*m));
}

/*
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static __inline__ void __change_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);

	*m ^= 1UL << (nr & 31);
}

/*
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int
test_and_set_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp, res;

	__asm__ __volatile__(
		".set\tnoreorder\t\t# test_and_set_bit\n"
		"1:\tll\t%0, %1\n\t"
		"or\t%2, %0, %3\n\t"
		"sc\t%2, %1\n\t"
		"beqz\t%2, 1b\n\t"
		" and\t%2, %0, %3\n\t"
		".set\treorder"
		: "=&r" (temp), "=m" (*m), "=&r" (res)
		: "r" (1UL << (nr & 0x1f)), "m" (*m)
		: "memory");

	return res != 0;
}

/*
 * __test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_set_bit(int nr, volatile void *addr)
{
	int mask, retval;
	volatile int *a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a |= mask;

	return retval;
}

/*
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int
test_and_clear_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp, res;

	__asm__ __volatile__(
		".set\tnoreorder\t\t# test_and_clear_bit\n"
		"1:\tll\t%0, %1\n\t"
		"or\t%2, %0, %3\n\t"
		"xor\t%2, %3\n\t"
		"sc\t%2, %1\n\t"
		"beqz\t%2, 1b\n\t"
		" and\t%2, %0, %3\n\t"
		".set\treorder"
		: "=&r" (temp), "=m" (*m), "=&r" (res)
		: "r" (1UL << (nr & 0x1f)), "m" (*m)
		: "memory");

	return res != 0;
}

/*
 * __test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_clear_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a &= ~mask;

	return retval;
}

/*
 * test_and_change_bit - Change a bit and return its new value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int
test_and_change_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);
	unsigned long temp, res;

	__asm__ __volatile__(
		".set\tnoreorder\t\t# test_and_change_bit\n"
		"1:\tll\t%0, %1\n\t"
		"xor\t%2, %0, %3\n\t"
		"sc\t%2, %1\n\t"
		"beqz\t%2, 1b\n\t"
		" and\t%2, %0, %3\n\t"
		".set\treorder"
		: "=&r" (temp), "=m" (*m), "=&r" (res)
		: "r" (1UL << (nr & 0x1f)), "m" (*m)
		: "memory");

	return res != 0;
}

/*
 * __test_and_change_bit - Change a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_change_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a ^= mask;

	return retval;
}

#else /* MIPS I */

/*
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static __inline__ void set_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;
	__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	*a |= mask;
	//__bi_restore_flags(flags);
}

/*
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static __inline__ void __set_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	*a |= mask;
}

/*
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static __inline__ void clear_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;
	__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	*a &= ~mask;
	//__bi_restore_flags(flags);
}

/*
 * change_bit - Toggle a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static __inline__ void change_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;
	__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	*a ^= mask;
	//__bi_restore_flags(flags);
}

/*
 * __change_bit - Toggle a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike change_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static __inline__ void __change_bit(int nr, volatile void *addr)
{
	unsigned long *m = ((unsigned long *) addr) + (nr >> 5);

	*m ^= 1UL << (nr & 31);
}

/*
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int test_and_set_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;
	__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	retval = (mask & *a) != 0;
	*a |= mask;
	//__bi_restore_flags(flags);

	return retval;
}

/*
 * __test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_set_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a |= mask;

	return retval;
}

/*
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int test_and_clear_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;
	__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	retval = (mask & *a) != 0;
	*a &= ~mask;
	//__bi_restore_flags(flags);

	return retval;
}

/*
 * __test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_clear_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a &= ~mask;

	return retval;
}

/*
 * test_and_change_bit - Change a bit and return its new value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static __inline__ int test_and_change_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;
	//__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	//__bi_save_and_cli(flags);
	retval = (mask & *a) != 0;
	*a ^= mask;
	//__bi_restore_flags(flags);

	return retval;
}

/*
 * __test_and_change_bit - Change a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is non-atomic and can be reordered.
 * If two examples of this operation race, one can appear to succeed
 * but actually fail.  You must protect multiple accesses with a lock.
 */
static __inline__ int __test_and_change_bit(int nr, volatile void *addr)
{
	int	mask, retval;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	retval = (mask & *a) != 0;
	*a ^= mask;

	return retval;
}

#undef __bi_flags
#undef __bi_cli
#undef __bi_save_flags
#undef __bi_restore_flags

#endif /* MIPS I */


/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline int generic_fls(int x)
{
	int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

#ifndef PLATFORM_FLS
# define fls generic_fls
#endif

// ----------------------------------------------------------------------------
// copy from uboot's /include/common.h
#define DW_BITS_MASK(__bfws, __bits) ((uint32_t) ((__bfws) == 32) ?  \
	0x0 : (((0xffffffff)>>(32 - __bits)) << (__bfws)))

#define DW_BIT_MASK(__bfws) ((uint32_t) ((__bfws) == 32) ?  \
	0x0 : (0x1 << (__bfws)))

#define DW_BIT_MASK_WIDTH(__bfws, __bits) ((uint32_t) ((__bfws) == 32) ?  \
	0xFFFFFFFF : (((1 << (__bits)) - 1) << (__bfws)))

#define DW_BIT_GET_UNSHIFTED(__datum, __bfws)                       \
	((uint32_t) ((__datum) & DW_BIT_MASK(__bfws)))

#define DW_BITS_SET_VAL(__datum, __bfws, __val, bit_num)                          \
	((__datum) = ((uint32_t) (__datum) & ~DW_BIT_MASK_WIDTH(__bfws, bit_num)) |    \
	((__val << (__bfws)) & DW_BIT_MASK_WIDTH(__bfws, bit_num)))

#define DW_BIT_SET(__datum, __bfws)                          \
	((__datum) = ((uint32_t) (__datum) & ~DW_BIT_MASK(__bfws)) |    \
	(DW_BIT_MASK(__bfws)))

#define DW_BIT_GET(__datum, __bfws)                                 \
	((uint32_t) (((__datum) & DW_BIT_MASK(__bfws)) >>               \
	(__bfws)))

#define DW_BITS_GET(__datum, __bfws, bit_num)                                 \
	((uint32_t) (((__datum) & DW_BIT_MASK_WIDTH(__bfws, bit_num)) >>               \
	(__bfws)))
#endif



/*
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static __inline__ void clear_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	taskENTER_CRITICAL();
	*a &= ~mask;
	taskEXIT_CRITICAL();
}

/*
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * if you do not require the atomic guarantees.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static __inline__ void set_bit(int nr, volatile void *addr)
{
	int	mask;
	volatile int	*a = addr;
	//__bi_flags;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);
	taskENTER_CRITICAL();
	*a |= mask;
	taskEXIT_CRITICAL();
}




#endif	// __RLX_BITOPS_H__
