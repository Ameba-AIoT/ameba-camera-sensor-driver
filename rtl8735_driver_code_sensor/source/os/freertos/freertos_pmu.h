#ifndef __FREERTOS_PMU_H_
#define __FREERTOS_PMU_H_

#ifdef CONFIG_PLATFORM_8195A
#include "sleep_ex_api.h"
#endif

#ifndef BIT
#define BIT(n)                   (1<<n)
#endif
// wakelock for system usage
#define WAKELOCK_OS              BIT(0)
#define WAKELOCK_WLAN            BIT(1)
#define WAKELOCK_LOGUART         BIT(2)
#define WAKELOCK_SDIO_DEVICE     BIT(3)

// wakelock for user defined
#define WAKELOCK_USER_BASE       BIT(16)

// default locked by OS and not to sleep until OS release wakelock in somewhere
#define DEFAULT_WAKELOCK         (WAKELOCK_OS)

#define DEFAULT_WAKEUP_EVENT (SLEEP_WAKEUP_BY_STIMER | SLEEP_WAKEUP_BY_GTIMER | SLEEP_WAKEUP_BY_GPIO_INT | SLEEP_WAKEUP_BY_WLAN)

// it's nDeviceId base number that user can use it to register sleep callback
#define PMU_DEVICE_USER_BASE       (0x80000000)

typedef uint32_t (*PSM_HOOK_FUN)( unsigned int, void* param_ptr );

/** Acquire wakelock
 *
 *  A wakelock is a 32-bit map. Each module own 1 bit in this bit map.
 *  FreeRTOS tickless reference the wakelock and decide that if it can or cannot enter sleep state.
 *  If any module acquire and hold a bit in wakelock, then the whole system won't enter sleep state.
 *
 *  If wakelock is not equals to 0, then the system won't enter sleep.
 *
 *  @param lock_id        : The bit which is attempt to add into wakelock
 */
void acquire_wakelock(uint32_t lock_id);

/** Release wakelock
 *
 *  If wakelock equals to 0, then the system may enter sleep state if it is in idle state.
 *
 *  @param lock_id        : The bit which is attempt to remove from wakelock
 */
void release_wakelock(uint32_t lock_id);

/** Get current wakelock bit map value
 *
 *  @return               : the current wakelock bit map value
 */
uint32_t get_wakelock_status(void);

#if (configGENERATE_RUN_TIME_STATS == 1)

/** enable to keep wakelock stats
 *
 */
void enable_wakelock_stats( unsigned char enable );

/** Get text report that contain the statics of wakelock holding time
 *
 *  Each time a module acquries or releases wakelock, a holding time is calculated and sum up to a table.
 *  It is for debug that which module is power saving killer.
 *
 *  @param pcWriteBuffer  : The char buffer that contain the report
 */
void get_wakelock_hold_stats( char *pcWriteBuffer );

/** Recalculate the wakelock statics
 *
 *  By default the wakelock statics is calculated from system boot up.
 *  If we want to debug power saving killer from a specified timestamp, we can reset the statics.
 */
void clean_wakelock_stat();

#endif

void add_wakeup_event(uint32_t event);
void del_wakeup_event(uint32_t event);

void register_sleep_callback(uint32_t nDeviceId, PSM_HOOK_FUN sleep_hook_fun, void* sleep_param_ptr, PSM_HOOK_FUN wakeup_hook_fun, void* wakeup_param_ptr);
void unregister_sleep_callback(uint32_t nDeviceId);

#ifdef CONFIG_PLATFORM_8195A
/** Set PLL reserved or not when sleep is called
 *
 *  @param reserve: true for sleep with PLL reserve
 */
void set_pll_reserved(unsigned char reserve);
#endif

#endif
