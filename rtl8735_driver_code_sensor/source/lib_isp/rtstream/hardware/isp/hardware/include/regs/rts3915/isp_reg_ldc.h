#ifndef _ISP_REG_LDC_H_INC_
#define _ISP_REG_LDC_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define LDC_SCALECOFE0 (LDC_REG_BASE + 0x0010)
#define LDC_SCALECOFE1_CX_SQUARE (LDC_REG_BASE + 0x0014)
#define LDC_X_INV0 (LDC_REG_BASE + 0x0018)
#define LDC_X_INV1_CX (LDC_REG_BASE + 0x001C)
#define LDC_Y_INV0 (LDC_REG_BASE + 0x0020)
#define LDC_Y_INV1_CY (LDC_REG_BASE + 0x0024)
#define LDC_CENTER (LDC_REG_BASE + 0x0028)
#define LDC_X0_CX_SQUARE (LDC_REG_BASE + 0x002C)
#define LDC_Y0_CY_SQUARE (LDC_REG_BASE + 0x0030)
#define LDC_SYNC (LDC_REG_BASE + 0x0034)

/* LDC_SCALECOFE0 0x0010 */
#define SCALECOFE0_OFFSET 0
#define SCALECOFE0_BITS 22
#define SCALECOFE0_MASK (((1 << 22) - 1) << 0)
/* LDC_SCALECOFE1_CX_SQUARE 0x0014 */
#define SCALECOFE1_CX_SQUARE_OFFSET 0
#define SCALECOFE1_CX_SQUARE_BITS 28
#define SCALECOFE1_CX_SQUARE_MASK (((1 << 28) - 1) << 0)
/* LDC_X_INV0 0x0018 */
#define X_INV0_OFFSET 0
#define X_INV0_BITS 18
#define X_INV0_MASK (((1 << 18) - 1) << 0)
/* LDC_X_INV1_CX 0x001C */
#define X_INV1_CX_OFFSET 0
#define X_INV1_CX_BITS 23
#define X_INV1_CX_MASK (((1 << 23) - 1) << 0)
/* LDC_Y_INV0 0x0020 */
#define Y_INV0_OFFSET 0
#define Y_INV0_BITS 20
#define Y_INV0_MASK (((1 << 20) - 1) << 0)
/* LDC_Y_INV1_CY 0x0024 */
#define Y_INV1_CY_OFFSET 0
#define Y_INV1_CY_BITS 19
#define Y_INV1_CY_MASK (((1 << 19) - 1) << 0)
/* LDC_CENTER 0x0028 */
#define X_CENTER_OFFSET 0
#define X_CENTER_BITS 12
#define X_CENTER_MASK (((1 << 12) - 1) << 0)
#define Y_CENTER_OFFSET 16
#define Y_CENTER_BITS 12
#define Y_CENTER_MASK (((1 << 12) - 1) << 16)
/* LDC_X0_CX_SQUARE 0x002C */
#define X0_CX_SQUARE_OFFSET 0
#define X0_CX_SQUARE_BITS 24
#define X0_CX_SQUARE_MASK (((1 << 24) - 1) << 0)
/* LDC_Y0_CY_SQUARE 0x0030 */
#define Y0_CY_SQUARE_OFFSET 0
#define Y0_CY_SQUARE_BITS 23
#define Y0_CY_SQUARE_MASK (((1 << 23) - 1) << 0)
/* LDC_SYNC 0x0034 */
#define LDC_REG_LOAD_OFFSET 0
#define LDC_REG_LOAD_BITS 1
#define LDC_REG_LOAD_MASK (((1 << 1) - 1) << 0)

#endif /* _ISP_REG_LDC_H_INC_ */

