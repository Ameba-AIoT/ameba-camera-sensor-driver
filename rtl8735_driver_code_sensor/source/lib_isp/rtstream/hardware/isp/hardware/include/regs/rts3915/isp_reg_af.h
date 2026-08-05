#ifndef _ISP_REG_AF_H_INC_
#define _ISP_REG_AF_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define AF_CTRL (AF_REG_BASE + 0x0000)
#define AF_THD1 (AF_REG_BASE + 0x0004)
#define AF_START0_X (AF_REG_BASE + 0x0008)
#define AF_START0_Y (AF_REG_BASE + 0x000C)
#define AF_END0_X (AF_REG_BASE + 0x0010)
#define AF_END0_Y (AF_REG_BASE + 0x0014)
#define AF_START1_X (AF_REG_BASE + 0x0018)
#define AF_START1_Y (AF_REG_BASE + 0x001C)
#define AF_END1_X (AF_REG_BASE + 0x0020)
#define AF_END1_Y (AF_REG_BASE + 0x0024)
#define AF_NUM0 (AF_REG_BASE + 0x0030)
#define AF_NUM1 (AF_REG_BASE + 0x0034)
#define AF_WIN_START_X (AF_REG_BASE + 0x0038)
#define AF_WIN_START_Y (AF_REG_BASE + 0x003C)
#define AF_WIN_WIDTH (AF_REG_BASE + 0x0040)
#define AF_WIN_HEIGHT (AF_REG_BASE + 0x0044)
#define AF_WIN_SUM0 (AF_REG_BASE + 0x0048)
#define AF_WIN_SUM1 (AF_REG_BASE + 0x004C)
#define AF_WIN_SUM2 (AF_REG_BASE + 0x0050)
#define AF_WIN_SUM3 (AF_REG_BASE + 0x0054)
#define AF_WIN_SUM4 (AF_REG_BASE + 0x0058)
#define AF_WIN_SUM5 (AF_REG_BASE + 0x005C)
#define AF_WIN_SUM6 (AF_REG_BASE + 0x0060)
#define AF_WIN_SUM7 (AF_REG_BASE + 0x0064)
#define AF_WIN_SUM8 (AF_REG_BASE + 0x0068)
#define AF_WIN_SUM9 (AF_REG_BASE + 0x006C)
#define AF_WIN_SUM10 (AF_REG_BASE + 0x0070)
#define AF_WIN_SUM11 (AF_REG_BASE + 0x0074)
#define AF_WIN_SUM12 (AF_REG_BASE + 0x0078)
#define AF_WIN_SUM13 (AF_REG_BASE + 0x007C)
#define AF_WIN_SUM14 (AF_REG_BASE + 0x0080)
#define AF_WIN_SUM15 (AF_REG_BASE + 0x0084)
#define AF_WIN_SUM16 (AF_REG_BASE + 0x0088)
#define AF_WIN_SUM17 (AF_REG_BASE + 0x008C)
#define AF_WIN_SUM18 (AF_REG_BASE + 0x0090)
#define AF_WIN_SUM19 (AF_REG_BASE + 0x0094)
#define AF_WIN_SUM20 (AF_REG_BASE + 0x0098)
#define AF_WIN_SUM21 (AF_REG_BASE + 0x009C)
#define AF_WIN_SUM22 (AF_REG_BASE + 0x00A0)
#define AF_WIN_SUM23 (AF_REG_BASE + 0x00A4)
#define AF_WIN_SUM24 (AF_REG_BASE + 0x00A8)
#define AF_SUM0 (AF_REG_BASE + 0x00AC)
#define AF_SUM1 (AF_REG_BASE + 0x00B0)
#define AF_SUM0L (AF_REG_BASE + 0x00B4)
#define AF_SUM1L (AF_REG_BASE + 0x00B8)

/* AF_CTRL 0x0000 */
#define AF_GOING_OFFSET 0
#define AF_GOING_BITS 1
#define AF_GOING_MASK (((1 << 1) - 1) << 0)
#define AF_SAMPLE_MODE_OFFSET 1
#define AF_SAMPLE_MODE_BITS 2
#define AF_SAMPLE_MODE_MASK (((1 << 2) - 1) << 1)
#define AF_SUM_MODE_OFFSET 3
#define AF_SUM_MODE_BITS 1
#define AF_SUM_MODE_MASK (((1 << 1) - 1) << 3)
#define AF_SUM0_MODE_OFFSET 4
#define AF_SUM0_MODE_BITS 1
#define AF_SUM0_MODE_MASK (((1 << 1) - 1) << 4)
#define AF_SUM1_MODE_OFFSET 5
#define AF_SUM1_MODE_BITS 1
#define AF_SUM1_MODE_MASK (((1 << 1) - 1) << 5)
#define AF_STOP_OFFSET 6
#define AF_STOP_BITS 1
#define AF_STOP_MASK (((1 << 1) - 1) << 6)
#define AF_START_OFFSET 7
#define AF_START_BITS 1
#define AF_START_MASK (((1 << 1) - 1) << 7)
#define AF_MODE_OFFSET 8
#define AF_MODE_BITS 2
#define AF_MODE_MASK (((1 << 2) - 1) << 8)
/* AF_THD1 0x0004 */
#define AFCHX_THD_OFFSET 0
#define AFCHX_THD_BITS 14
#define AFCHX_THD_MASK (((1 << 14) - 1) << 0)
/* AF_START0_X 0x0008 */
#define START_X0_OFFSET 0
#define START_X0_BITS 12
#define START_X0_MASK (((1 << 12) - 1) << 0)
/* AF_START0_Y 0x000C */
#define START_Y0_OFFSET 0
#define START_Y0_BITS 12
#define START_Y0_MASK (((1 << 12) - 1) << 0)
/* AF_END0_X 0x0010 */
#define END_X0_OFFSET 0
#define END_X0_BITS 12
#define END_X0_MASK (((1 << 12) - 1) << 0)
/* AF_END0_Y 0x0014 */
#define END_Y0_OFFSET 0
#define END_Y0_BITS 12
#define END_Y0_MASK (((1 << 12) - 1) << 0)
/* AF_START1_X 0x0018 */
#define START_X1_OFFSET 0
#define START_X1_BITS 12
#define START_X1_MASK (((1 << 12) - 1) << 0)
/* AF_START1_Y 0x001C */
#define START_Y1_OFFSET 0
#define START_Y1_BITS 12
#define START_Y1_MASK (((1 << 12) - 1) << 0)
/* AF_END1_X 0x0020 */
#define END_X1_OFFSET 0
#define END_X1_BITS 12
#define END_X1_MASK (((1 << 12) - 1) << 0)
/* AF_END1_Y 0x0024 */
#define END_Y1_OFFSET 0
#define END_Y1_BITS 12
#define END_Y1_MASK (((1 << 12) - 1) << 0)
/* AF_NUM0 0x0030 */
#define AF_NUM0_OFFSET 0
#define AF_NUM0_BITS 23
#define AF_NUM0_MASK (((1 << 23) - 1) << 0)
/* AF_NUM1 0x0034 */
#define AF_NUM1_OFFSET 0
#define AF_NUM1_BITS 23
#define AF_NUM1_MASK (((1 << 23) - 1) << 0)
/* AF_WIN_START_X 0x0038 */
#define AF_START_X_OFFSET 0
#define AF_START_X_BITS 12
#define AF_START_X_MASK (((1 << 12) - 1) << 0)
/* AF_WIN_START_Y 0x003C */
#define AF_START_Y_OFFSET 0
#define AF_START_Y_BITS 12
#define AF_START_Y_MASK (((1 << 12) - 1) << 0)
/* AF_WIN_WIDTH 0x0040 */
#define AF_WIN_WIDTH_OFFSET 0
#define AF_WIN_WIDTH_BITS 8
#define AF_WIN_WIDTH_MASK (((1 << 8) - 1) << 0)
/* AF_WIN_HEIGHT 0x0044 */
#define AF_WIN_HEIGHT_OFFSET 0
#define AF_WIN_HEIGHT_BITS 8
#define AF_WIN_HEIGHT_MASK (((1 << 8) - 1) << 0)
/* AF_WIN_SUM0 0x0048 */
/* AF_WIN_SUM1 0x004C */
/* AF_WIN_SUM2 0x0050 */
/* AF_WIN_SUM3 0x0054 */
/* AF_WIN_SUM4 0x0058 */
/* AF_WIN_SUM5 0x005C */
/* AF_WIN_SUM6 0x0060 */
/* AF_WIN_SUM7 0x0064 */
/* AF_WIN_SUM8 0x0068 */
/* AF_WIN_SUM9 0x006C */
/* AF_WIN_SUM10 0x0070 */
/* AF_WIN_SUM11 0x0074 */
/* AF_WIN_SUM12 0x0078 */
/* AF_WIN_SUM13 0x007C */
/* AF_WIN_SUM14 0x0080 */
/* AF_WIN_SUM15 0x0084 */
/* AF_WIN_SUM16 0x0088 */
/* AF_WIN_SUM17 0x008C */
/* AF_WIN_SUM18 0x0090 */
/* AF_WIN_SUM19 0x0094 */
/* AF_WIN_SUM20 0x0098 */
/* AF_WIN_SUM21 0x009C */
/* AF_WIN_SUM22 0x00A0 */
/* AF_WIN_SUM23 0x00A4 */
/* AF_WIN_SUM24 0x00A8 */
/* AF_SUM0 0x00AC */
/* AF_SUM1 0x00B0 */
/* AF_SUM0L 0x00B4 */
#define AF_SUM0_L_OFFSET 0
#define AF_SUM0_L_BITS 4
#define AF_SUM0_L_MASK (((1 << 4) - 1) << 0)
/* AF_SUM1L 0x00B8 */
#define AF_SUM1_L_OFFSET 0
#define AF_SUM1_L_BITS 4
#define AF_SUM1_L_MASK (((1 << 4) - 1) << 0)

#endif /* _ISP_REG_AF_H_INC_ */

