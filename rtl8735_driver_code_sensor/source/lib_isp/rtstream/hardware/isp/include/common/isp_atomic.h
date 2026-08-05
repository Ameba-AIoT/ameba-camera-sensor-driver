#ifndef _ISP_ATOMIC_H_INC_
#define _ISP_ATOMIC_H_INC_

typedef long isp_atomic_int_t;
typedef unsigned long isp_atomic_uint_t;
typedef volatile isp_atomic_uint_t isp_atomic_t;

#define isp_atomic_fetch_and_add(ptr, val) __sync_fetch_and_add(ptr, val)
#define isp_atomic_fetch_and_sub(ptr, val) __sync_fetch_and_sub(ptr, val)
#define isp_atomic_fetch_and_or(ptr, val) __sync_fetch_and_or(ptr, val)
#define isp_atomic_fetch_and_and(ptr, val) __sync_fetch_and_and(ptr, val)
#define isp_atomic_fetch_and_xor(ptr, val) __sync_fetch_and_xor(ptr, val)
#define isp_atomic_fetch_and_nor(ptr, val) __sync_fetch_and_nor(ptr, val)
#define isp_atomic_fetch_and_nand(ptr, val) __sync_fetch_and_nand(ptr, val)

#define isp_atomic_add_and_fetch(ptr, val) __sync_add_and_fetch(ptr, val)
#define isp_atomic_sub_and_fetch(ptr, val) __sync_sub_and_fetch(ptr, val)
#define isp_atomic_or_and_fetch(ptr, val) __sync_or_and_fetch(ptr, val)
#define isp_atomic_and_and_fetch(ptr, val) __sync_and_and_fetch(ptr, val)
#define isp_atomic_xor_and_fetch(ptr, val) __sync_xor_and_fetch(ptr, val)
#define isp_atomic_nor_and_fetch(ptr, val) __sync_nor_and_fetch(ptr, val)
#define isp_atomic_nand_and_fetch(ptr, val) __sync_nand_and_fetch(ptr, val)

#define isp_atomic_inc(ptr) isp_atomic_add_and_fetch(ptr, 1)
#define isp_atomic_dec(ptr) isp_atomic_sub_and_fetch(ptr, 1)

#define isp_memory_barrier() __sync_synchronize()

#define isp_atomic_val_cmp_swap(ptr, oldval, newval) \
	__sync_val_compare_and_swap(ptr, oldval, newval)
#define isp_atomic_bool_cmp_swap(ptr, oldval, newval) \
	__sync_bool_compare_and_swap(ptr, oldval, newval)

#define isp_atomic_val_set(ptr, value) __sync_lock_test_and_set(ptr, value)
#define isp_atomic_val_clr(ptr, value) __sync_lock_release(ptr, value)

#endif /* _ISP_ATOMIC_H_INC_ */

