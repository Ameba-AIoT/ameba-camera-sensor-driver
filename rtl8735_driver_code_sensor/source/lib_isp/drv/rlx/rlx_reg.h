#ifndef RLX_REG_H
#define RLX_REG_H
#include "rlx_reg_ops.h"

#include "rlx_reg_base.h"
#include "rlx_reg_sys.h"
#include "rlx_reg_audio.h"
#include "rlx_reg_crypto.h"
#include "rlx_reg_gpio.h"
#if !defined(CONFIG_PLATFORM_RTS3915)
  #include "rlx_reg_i2c.h"
#endif
#include "rlx_reg_isp.h"
#include "rlx_reg_saradc.h"

#endif	// RLX_REG_H
