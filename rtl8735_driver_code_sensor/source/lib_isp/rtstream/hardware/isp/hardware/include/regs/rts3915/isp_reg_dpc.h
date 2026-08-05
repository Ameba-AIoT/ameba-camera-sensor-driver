#ifndef _ISP_REG_DPC_H_INC_
#define _ISP_REG_DPC_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define DPC_ENABLE (DPC_REG_BASE + 0x0000)
#define DPC_THD0 (DPC_REG_BASE + 0x0004)
#define DPC_RATE (DPC_REG_BASE + 0x0008)
#define DPC_THD1 (DPC_REG_BASE + 0x000C)

/* DPC_ENABLE 0x0000 */
#define DDP2_EN_OFFSET 0
#define DDP2_EN_BITS 1
#define DDP2_EN_MASK (((1 << 1) - 1) << 0)
#define DP_RP_EN_OFFSET 1
#define DP_RP_EN_BITS 1
#define DP_RP_EN_MASK (((1 << 1) - 1) << 1)
#define DPC_SRC_SEL_OFFSET 2
#define DPC_SRC_SEL_BITS 1
#define DPC_SRC_SEL_MASK (((1 << 1) - 1) << 2)
#define DP_GROUP_SQUARE_OFFSET 3
#define DP_GROUP_SQUARE_BITS 1
#define DP_GROUP_SQUARE_MASK (((1 << 1) - 1) << 3)
/* DPC_THD0 0x0004 */
#define DP_BRIGHT_THD_MIN_OFFSET 0
#define DP_BRIGHT_THD_MIN_BITS 4
#define DP_BRIGHT_THD_MIN_MASK (((1 << 4) - 1) << 0)
#define DP_BRIGHT_THD_MAX_OFFSET 8
#define DP_BRIGHT_THD_MAX_BITS 5
#define DP_BRIGHT_THD_MAX_MASK (((1 << 5) - 1) << 8)
#define DP_DARK_THD_MIN_OFFSET 16
#define DP_DARK_THD_MIN_BITS 4
#define DP_DARK_THD_MIN_MASK (((1 << 4) - 1) << 16)
#define DP_DARK_THD_MAX_OFFSET 24
#define DP_DARK_THD_MAX_BITS 5
#define DP_DARK_THD_MAX_MASK (((1 << 5) - 1) << 24)
/* DPC_RATE 0x0008 */
#define G_DP_BRIGHT_RATE_OFFSET 0
#define G_DP_BRIGHT_RATE_BITS 5
#define G_DP_BRIGHT_RATE_MASK (((1 << 5) - 1) << 0)
#define G_DP_DARK_RATE_OFFSET 8
#define G_DP_DARK_RATE_BITS 5
#define G_DP_DARK_RATE_MASK (((1 << 5) - 1) << 8)
#define RB_DP_BRIGHT_RATE_OFFSET 16
#define RB_DP_BRIGHT_RATE_BITS 5
#define RB_DP_BRIGHT_RATE_MASK (((1 << 5) - 1) << 16)
#define RB_DP_DARK_RATE_OFFSET 24
#define RB_DP_DARK_RATE_BITS 5
#define RB_DP_DARK_RATE_MASK (((1 << 5) - 1) << 24)
/* DPC_THD1 0x000C */
#define DP_THD_D1_OFFSET 0
#define DP_THD_D1_BITS 4
#define DP_THD_D1_MASK (((1 << 4) - 1) << 0)

#endif /* _ISP_REG_DPC_H_INC_ */

