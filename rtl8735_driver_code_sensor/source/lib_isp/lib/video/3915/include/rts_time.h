#ifndef _TIME32
#define _TIME32

#include <sys/time.h>

/*
typedef struct isp_poll *isp_poll_t;
typedef struct isp_timer_handle *isp_timer_handle_t;

//for replace time.h in asdk toolchain dir, the struct are different

#define _DLIB_SUPPORT_FOR_AEABI 1
struct tm
{       // date and time components
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  #if  _DLIB_SUPPORT_FOR_AEABI==1
    int __BSD_bug_filler1;
    int __BSD_bug_filler2;
  #endif
};

int isp_timer_init(isp_timer_handle_t *pt, isp_poll_t p,
		   isp_timer_cb cb, void *data);
int isp_timer_cleanup(isp_timer_handle_t timer);
int isp_timer_start(isp_timer_handle_t timer,
		    uint32_t timeout, uint32_t interval);
int isp_timer_stop(isp_timer_handle_t timer);
*/

#endif
