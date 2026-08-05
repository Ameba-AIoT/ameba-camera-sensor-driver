#ifndef _ISP_REG_RGB2YUV_H_INC_
#define _ISP_REG_RGB2YUV_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define RGB2YUV0 (RGB2YUV_REG_BASE + 0x0000)
#define RGB2YUV1 (RGB2YUV_REG_BASE + 0x0004)
#define RGB2YUV2 (RGB2YUV_REG_BASE + 0x0008)
#define RGB2YUV3 (RGB2YUV_REG_BASE + 0x000C)
#define RGB2YUV4 (RGB2YUV_REG_BASE + 0x0010)
#define RGB2YUV_YOFFSET (RGB2YUV_REG_BASE + 0x0014)

/* RGB2YUV0 0x0000 */
#define YBT709_YR_OFFSET 0
#define YBT709_YR_BITS 12
#define YBT709_YR_MASK (((1 << 12) - 1) << 0)
#define YBT709_YG_OFFSET 16
#define YBT709_YG_BITS 12
#define YBT709_YG_MASK (((1 << 12) - 1) << 16)
/* RGB2YUV1 0x0004 */
#define YBT709_YB_OFFSET 0
#define YBT709_YB_BITS 12
#define YBT709_YB_MASK (((1 << 12) - 1) << 0)
#define YBT709_UR_OFFSET 16
#define YBT709_UR_BITS 12
#define YBT709_UR_MASK (((1 << 12) - 1) << 16)
/* RGB2YUV2 0x0008 */
#define YBT709_UG_OFFSET 0
#define YBT709_UG_BITS 12
#define YBT709_UG_MASK (((1 << 12) - 1) << 0)
#define YBT709_UB_OFFSET 16
#define YBT709_UB_BITS 12
#define YBT709_UB_MASK (((1 << 12) - 1) << 16)
/* RGB2YUV3 0x000C */
#define YBT709_VR_OFFSET 0
#define YBT709_VR_BITS 12
#define YBT709_VR_MASK (((1 << 12) - 1) << 0)
#define YBT709_VG_OFFSET 16
#define YBT709_VG_BITS 12
#define YBT709_VG_MASK (((1 << 12) - 1) << 16)
/* RGB2YUV4 0x0010 */
#define YBT709_VB_OFFSET 0
#define YBT709_VB_BITS 12
#define YBT709_VB_MASK (((1 << 12) - 1) << 0)
/* RGB2YUV_YOFFSET 0x0014 */
#define YBT709_OFFSET_OFFSET 0
#define YBT709_OFFSET_BITS 5
#define YBT709_OFFSET_MASK (((1 << 5) - 1) << 0)

#endif /* _ISP_REG_RGB2YUV_H_INC_ */

