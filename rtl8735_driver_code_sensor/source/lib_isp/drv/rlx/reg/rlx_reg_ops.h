#ifndef RLX_REG_OPS_H
#define RLX_REG_OPS_H
#include "rlx_inc.h"

// ----------------------------------------------------------------------------
// from uboot's /bsp/RTS3903/bspchip.h
// ----------------------------------------------------------------------------
#ifndef REG64
#define REG64(reg)		(*(volatile unsigned long long *)(reg))
#endif
#ifndef REG32
#define REG32(reg)		(*(volatile unsigned int *)(reg))
#endif
#ifndef REG16
#define REG16(reg)		(*(volatile unsigned short *)(reg))
#endif
#ifndef REG8
#define REG8(reg)		(*(volatile unsigned char *)(reg))
#endif

#ifndef MEM32
#define MEM32(addr)		(*(volatile unsigned int *)(addr))
#endif

// ----------------------------------------------------------------------------
// Frank add
// ----------------------------------------------------------------------------
#define REG_R8(adr)			(REG8(adr))
#define REG_W8(adr, val)	(REG8(adr) = (val))

#define REG_R16(adr)		(REG16(adr))
#define REG_W16(adr, val)	(REG16(adr) = (val))

#define REG_R32(adr)		(REG32(adr))
#define REG_W32(adr, val)	(REG32(adr) = (val))

// ----------------------------------------------------------------------------
// from uboot's /arch/rlx/include/asm/io.h
// ----------------------------------------------------------------------------
#include "rlx_byteorder.h"

/*
 * XXX We need system specific versions of these to handle EISA address bits
 * 24-31 on SNI.
 * XXX more SNI hacks.
 */
#define __raw_readb(addr) (*(volatile unsigned char *)(addr))
#define __raw_readw(addr) (*(volatile unsigned short *)(addr))
#define __raw_readl(addr) (*(volatile unsigned int *)(addr))
#define readb(addr) __raw_readb((addr))
#define readw(addr) __ioswab16(__raw_readw((addr)))
#define readl(addr) __ioswab32(__raw_readl((addr)))

#define __raw_writeb(b, addr) ((*(volatile unsigned char *)(addr)) = (b))
#define __raw_writew(b, addr) ((*(volatile unsigned short *)(addr)) = (b))
#define __raw_writel(b, addr) ((*(volatile unsigned int *)(addr)) = (b))
#define writeb(b, addr) __raw_writeb((b), (addr))
#define writew(b, addr) __raw_writew(__ioswab16(b), (addr))
#define writel(b, addr) __raw_writel(__ioswab32(b), (addr))

#endif	// RLX_REG_OPS_H
