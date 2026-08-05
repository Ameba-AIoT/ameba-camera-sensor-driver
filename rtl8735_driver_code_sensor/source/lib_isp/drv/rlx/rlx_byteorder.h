// brief:
//  a temp solution to replace uboot's byteorder function.
//  ex: use rlx_cpu_to_be32() to replace cpu_to_be32() in driver code.
//
//  someday in future, maybe totally get rid of uboot's code,
//  we can replace rlx_cpu_to_be32() back to new version's cpu_to_be32().
//
// Frank: this file is from uboot's /arch/rlx/include/asm/byteorder.h
#ifndef __RLX_BYTEORDER_H__
#define __RLX_BYTEORDER_H__
#include "rlx_inc.h"

#define rlx_uswap_16(x) \
	((((x) & 0xff00) >> 8) | \
	 (((x) & 0x00ff) << 8))

#define rlx_uswap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))

#define _rlx_uswap_64(x, sfx) \
	((((x) & 0xff00000000000000##sfx) >> 56) | \
	 (((x) & 0x00ff000000000000##sfx) >> 40) | \
	 (((x) & 0x0000ff0000000000##sfx) >> 24) | \
	 (((x) & 0x000000ff00000000##sfx) >>  8) | \
	 (((x) & 0x00000000ff000000##sfx) <<  8) | \
	 (((x) & 0x0000000000ff0000##sfx) << 24) | \
	 (((x) & 0x000000000000ff00##sfx) << 40) | \
	 (((x) & 0x00000000000000ff##sfx) << 56))
#if defined(__GNUC__)
# define rlx_uswap_64(x) _rlx_uswap_64(x, ull)
#else
//# define rlx_uswap_64(x) _rlx_uswap_64(x, )
#endif

# define rlx_cpu_to_le16(x)		(x)
# define rlx_cpu_to_le32(x)		(x)
# define rlx_cpu_to_le64(x)		(x)
# define rlx_le16_to_cpu(x)		(x)
# define rlx_le32_to_cpu(x)		(x)
# define rlx_le64_to_cpu(x)		(x)
# define rlx_cpu_to_be16(x)		rlx_uswap_16(x)
# define rlx_cpu_to_be32(x)		rlx_uswap_32(x)
# define rlx_cpu_to_be64(x)		rlx_uswap_64(x)
# define rlx_be16_to_cpu(x)		rlx_uswap_16(x)
# define rlx_be32_to_cpu(x)		rlx_uswap_32(x)
# define rlx_be64_to_cpu(x)		rlx_uswap_64(x)

// ----------------------------------------------------------------------------
static __inline__ uint16_t swab16(uint16_t x)
{
	return x<<8 | x>>8;
}

static __inline__ uint32_t swab32(uint32_t x)
{
	return (x<<24 | x>>24 | (x & 0x0000ff00UL)<<8 | (x & 0x00ff0000UL)>>8);
}

// copy from uboot's /arch/rlx/include/asm/io.h
// ----------------------------------------------------------------------------
/*
 * Sane hardware offers swapping of I/O space accesses in hardware; less
 * sane hardware forces software to fiddle with this ...
 */
//#if defined(CONFIG_SWAP_IO_SPACE) && defined(__MIPSEB__)
#if 0

#define __ioswab8(x) (x)
#define __ioswab16(x) swab16(x)
#define __ioswab32(x) swab32(x)

#else
// Frank: for current build of uboot in SDK, the compiler will go this area.
#define __ioswab8(x) (x)
#define __ioswab16(x) (x)
#define __ioswab32(x) (x)

#endif

#endif	// __RLX_BYTEORDER_H__
