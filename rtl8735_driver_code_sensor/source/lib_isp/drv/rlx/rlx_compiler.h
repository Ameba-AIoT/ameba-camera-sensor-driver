#ifndef __RLX_COMPILER_H__
#define __RLX_COMPILER_H__

#define __deprecated	__attribute__((deprecated))

#ifndef __packed
# define __packed		__attribute__((packed))
#endif

#define __weak			__attribute__((weak))

#define __noreturn		__attribute__((noreturn))

/* Optimization barrier */
/* The "volatile" is due to gcc bugs */
#define barrier() ({__asm__ __volatile__("" : : : "memory"); })


#endif	// __RLX_COMPILER_H__

