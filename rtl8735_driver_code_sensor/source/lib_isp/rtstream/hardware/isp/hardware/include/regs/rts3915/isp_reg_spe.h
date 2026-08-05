#ifndef _ISP_REG_SPE_H_INC_
#define _ISP_REG_SPE_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define SPE_CTRL_EN (SPE_REG_BASE + 0x0000)
#define SPE_Y_MONO (SPE_REG_BASE + 0x0008)
#define SPE_TUNE (SPE_REG_BASE + 0x000C)
#define SPE_UV_TARGET (SPE_REG_BASE + 0x0010)
#define SPE_YCONTRAST (SPE_REG_BASE + 0x0014)
#define SPE_Y_OFFSET (SPE_REG_BASE + 0x0018)
#define SPE_U_OFFSET (SPE_REG_BASE + 0x001C)
#define SPE_V_OFFSET (SPE_REG_BASE + 0x0020)
#define SPE_Y_GAIN (SPE_REG_BASE + 0x0024)
#define SPE_U_GAIN (SPE_REG_BASE + 0x0028)
#define SPE_V_GAIN (SPE_REG_BASE + 0x002C)
#define SPE_SYNC (SPE_REG_BASE + 0x0030)

/* SPE_CTRL_EN 0x0000 */
#define SPE_EN_OFFSET 0
#define SPE_EN_BITS 1
#define SPE_EN_MASK (((1 << 1) - 1) << 0)
#define NEGATIVE_EN_OFFSET 1
#define NEGATIVE_EN_BITS 1
#define NEGATIVE_EN_MASK (((1 << 1) - 1) << 1)
#define MONO_EN_OFFSET 2
#define MONO_EN_BITS 1
#define MONO_EN_MASK (((1 << 1) - 1) << 2)
#define GRAY_EN_OFFSET 3
#define GRAY_EN_BITS 1
#define GRAY_EN_MASK (((1 << 1) - 1) << 3)
/* SPE_Y_MONO 0x0008 */
#define MONO_MEAN_Y_OFFSET 0
#define MONO_MEAN_Y_BITS 8
#define MONO_MEAN_Y_MASK (((1 << 8) - 1) << 0)
/* SPE_TUNE 0x000C */
#define SPE_TUNE_OFFSET 0
#define SPE_TUNE_BITS 6
#define SPE_TUNE_MASK (((1 << 6) - 1) << 0)
/* SPE_UV_TARGET 0x0010 */
#define SPE_U_TARGET_OFFSET 0
#define SPE_U_TARGET_BITS 8
#define SPE_U_TARGET_MASK (((1 << 8) - 1) << 0)
#define SPE_V_TARGET_OFFSET 8
#define SPE_V_TARGET_BITS 8
#define SPE_V_TARGET_MASK (((1 << 8) - 1) << 8)
/* SPE_YCONTRAST 0x0014 */
#define YCONTRAST_OFFSET 0
#define YCONTRAST_BITS 8
#define YCONTRAST_MASK (((1 << 8) - 1) << 0)
#define YCONTRAST_MEAN_OFFSET 8
#define YCONTRAST_MEAN_BITS 8
#define YCONTRAST_MEAN_MASK (((1 << 8) - 1) << 8)
/* SPE_Y_OFFSET 0x0018 */
#define Y_OFFSET_OFFSET 0
#define Y_OFFSET_BITS 8
#define Y_OFFSET_MASK (((1 << 8) - 1) << 0)
/* SPE_U_OFFSET 0x001C */
#define U_OFFSET_OFFSET 0
#define U_OFFSET_BITS 6
#define U_OFFSET_MASK (((1 << 6) - 1) << 0)
/* SPE_V_OFFSET 0x0020 */
#define V_OFFSET_OFFSET 0
#define V_OFFSET_BITS 6
#define V_OFFSET_MASK (((1 << 6) - 1) << 0)
/* SPE_Y_GAIN 0x0024 */
#define Y_GAIN_OFFSET 0
#define Y_GAIN_BITS 8
#define Y_GAIN_MASK (((1 << 8) - 1) << 0)
/* SPE_U_GAIN 0x0028 */
#define U_GAIN_OFFSET 0
#define U_GAIN_BITS 8
#define U_GAIN_MASK (((1 << 8) - 1) << 0)
/* SPE_V_GAIN 0x002C */
#define V_GAIN_OFFSET 0
#define V_GAIN_BITS 8
#define V_GAIN_MASK (((1 << 8) - 1) << 0)
/* SPE_SYNC 0x0030 */
#define SPE_SYNC_OFFSET 0
#define SPE_SYNC_BITS 1
#define SPE_SYNC_MASK (((1 << 1) - 1) << 0)

#endif /* _ISP_REG_SPE_H_INC_ */

