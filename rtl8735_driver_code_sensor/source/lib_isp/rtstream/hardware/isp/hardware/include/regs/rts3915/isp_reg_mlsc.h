#ifndef _ISP_REG_MLSC_H_INC_
#define _ISP_REG_MLSC_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define MLSC_PARA0 (MLSC_REG_BASE + 0x0000)
#define MLSC_CTRL (MLSC_REG_BASE + 0x1800)

/* MLSC_PARA0 0x0000 */
#define RF_MLSC_R_DAT_OFFSET 0
#define RF_MLSC_R_DAT_BITS 6
#define RF_MLSC_R_DAT_MASK (((1 << 6) - 1) << 0)
#define RF_MLSC_GB_DAT_OFFSET 8
#define RF_MLSC_GB_DAT_BITS 6
#define RF_MLSC_GB_DAT_MASK (((1 << 6) - 1) << 8)
#define RF_MLSC_GR_DAT_OFFSET 16
#define RF_MLSC_GR_DAT_BITS 6
#define RF_MLSC_GR_DAT_MASK (((1 << 6) - 1) << 16)
#define RF_MLSC_B_DAT_OFFSET 24
#define RF_MLSC_B_DAT_BITS 6
#define RF_MLSC_B_DAT_MASK (((1 << 6) - 1) << 24)
/* MLSC_CTRL 0x1800 */
#define RF_MLSC_MODE_OFFSET 0
#define RF_MLSC_MODE_BITS 2
#define RF_MLSC_MODE_MASK (((1 << 2) - 1) << 0)

#endif /* _ISP_REG_MLSC_H_INC_ */

