#ifndef _ISP_REG_AE_H_INC_
#define _ISP_REG_AE_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define AE_CTRL (AE_REG_BASE + 0x0000)
#define AE_WIN_START (AE_REG_BASE + 0x0004)
#define AE_WIN_SIZE (AE_REG_BASE + 0x0008)
#define AE_WIN_CAL_NUM (AE_REG_BASE + 0x000C)
#define AE_HWIN_START (AE_REG_BASE + 0x0010)
#define AE_HWIN_END (AE_REG_BASE + 0x0014)
#define AE_BRIGHT_COEF (AE_REG_BASE + 0x0018)
#define AE_Y_THD0 (AE_REG_BASE + 0x001C)
#define AE_Y_THD1 (AE_REG_BASE + 0x0020)
#define AE_R_THD0 (AE_REG_BASE + 0x0024)
#define AE_R_THD1 (AE_REG_BASE + 0x0028)
#define AE_GR_THD0 (AE_REG_BASE + 0x002C)
#define AE_GR_THD1 (AE_REG_BASE + 0x0030)
#define AE_GB_THD0 (AE_REG_BASE + 0x0034)
#define AE_GB_THD1 (AE_REG_BASE + 0x0038)
#define AE_B_THD0 (AE_REG_BASE + 0x003C)
#define AE_B_THD1 (AE_REG_BASE + 0x0040)
#define AE_SUM_MAX_Y (AE_REG_BASE + 0x0044)
#define AE_SUM_MIN_Y (AE_REG_BASE + 0x0048)
#define AE_SUM_MAX_R (AE_REG_BASE + 0x004C)
#define AE_SUM_MIN_R (AE_REG_BASE + 0x0050)
#define AE_SUM_MAX_GR (AE_REG_BASE + 0x0054)
#define AE_SUM_MIN_GR (AE_REG_BASE + 0x0058)
#define AE_SUM_MAX_GB (AE_REG_BASE + 0x005C)
#define AE_SUM_MIN_GB (AE_REG_BASE + 0x0060)
#define AE_SUM_MAX_B (AE_REG_BASE + 0x0064)
#define AE_SUM_MIN_B (AE_REG_BASE + 0x0068)
#define AE_YWIN_START (AE_REG_BASE + 0x006C)
#define AE_YWIN_END (AE_REG_BASE + 0x0070)
#define AE_YSUM (AE_REG_BASE + 0x0074)
#define AE_ADDR (AE_REG_BASE + 0x0078)
#define AE_WIN_RESULT (AE_REG_BASE + 0x007C)
#define AE_GAIN (AE_REG_BASE + 0x0080)
#define AE_GAIN_CTRL (AE_REG_BASE + 0x0088)

/* AE_CTRL 0x0000 */
#define AE_MODE_OFFSET 0
#define AE_MODE_BITS 2
#define AE_MODE_MASK (((1 << 2) - 1) << 0)
#define AE_DLY_OFFSET 2
#define AE_DLY_BITS 2
#define AE_DLY_MASK (((1 << 2) - 1) << 2)
#define AE_WIN_STATS_MODE_OFFSET 4
#define AE_WIN_STATS_MODE_BITS 1
#define AE_WIN_STATS_MODE_MASK (((1 << 1) - 1) << 4)
#define AE_GOING_OFFSET 5
#define AE_GOING_BITS 1
#define AE_GOING_MASK (((1 << 1) - 1) << 5)
#define AE_STOP_OFFSET 6
#define AE_STOP_BITS 1
#define AE_STOP_MASK (((1 << 1) - 1) << 6)
#define AE_START_OFFSET 7
#define AE_START_BITS 1
#define AE_START_MASK (((1 << 1) - 1) << 7)
/* AE_WIN_START 0x0004 */
#define AE_START_X_OFFSET 0
#define AE_START_X_BITS 12
#define AE_START_X_MASK (((1 << 12) - 1) << 0)
#define AE_START_Y_OFFSET 16
#define AE_START_Y_BITS 12
#define AE_START_Y_MASK (((1 << 12) - 1) << 16)
/* AE_WIN_SIZE 0x0008 */
#define AE_WIN_WIDTH_OFFSET 0
#define AE_WIN_WIDTH_BITS 8
#define AE_WIN_WIDTH_MASK (((1 << 8) - 1) << 0)
#define AE_WIN_HEIGHT_OFFSET 8
#define AE_WIN_HEIGHT_BITS 8
#define AE_WIN_HEIGHT_MASK (((1 << 8) - 1) << 8)
#define AE_WIN_NUM_H_OFFSET 16
#define AE_WIN_NUM_H_BITS 5
#define AE_WIN_NUM_H_MASK (((1 << 5) - 1) << 16)
#define AE_WIN_NUM_V_OFFSET 24
#define AE_WIN_NUM_V_BITS 5
#define AE_WIN_NUM_V_MASK (((1 << 5) - 1) << 24)
/* AE_WIN_CAL_NUM 0x000C */
#define AE_WIN_CAL_NUM_OFFSET 0
#define AE_WIN_CAL_NUM_BITS 16
#define AE_WIN_CAL_NUM_MASK (((1 << 16) - 1) << 0)
/* AE_HWIN_START 0x0010 */
#define AE_YST_X_OFFSET 0
#define AE_YST_X_BITS 12
#define AE_YST_X_MASK (((1 << 12) - 1) << 0)
#define AE_YST_Y_OFFSET 16
#define AE_YST_Y_BITS 12
#define AE_YST_Y_MASK (((1 << 12) - 1) << 16)
/* AE_HWIN_END 0x0014 */
#define AE_END_X_OFFSET 0
#define AE_END_X_BITS 12
#define AE_END_X_MASK (((1 << 12) - 1) << 0)
#define AE_END_Y_OFFSET 16
#define AE_END_Y_BITS 12
#define AE_END_Y_MASK (((1 << 12) - 1) << 16)
/* AE_BRIGHT_COEF 0x0018 */
#define COEF_R_OFFSET 0
#define COEF_R_BITS 4
#define COEF_R_MASK (((1 << 4) - 1) << 0)
#define COEF_B_OFFSET 8
#define COEF_B_BITS 4
#define COEF_B_MASK (((1 << 4) - 1) << 8)
/* AE_Y_THD0 0x001C */
#define MIN_Y_OFFSET 0
#define MIN_Y_BITS 10
#define MIN_Y_MASK (((1 << 10) - 1) << 0)
/* AE_Y_THD1 0x0020 */
#define MAX_Y_OFFSET 0
#define MAX_Y_BITS 10
#define MAX_Y_MASK (((1 << 10) - 1) << 0)
/* AE_R_THD0 0x0024 */
#define MIN_R_OFFSET 0
#define MIN_R_BITS 10
#define MIN_R_MASK (((1 << 10) - 1) << 0)
/* AE_R_THD1 0x0028 */
#define MAX_R_OFFSET 0
#define MAX_R_BITS 10
#define MAX_R_MASK (((1 << 10) - 1) << 0)
/* AE_GR_THD0 0x002C */
#define MIN_GR_OFFSET 0
#define MIN_GR_BITS 10
#define MIN_GR_MASK (((1 << 10) - 1) << 0)
/* AE_GR_THD1 0x0030 */
#define MAX_GR_OFFSET 0
#define MAX_GR_BITS 10
#define MAX_GR_MASK (((1 << 10) - 1) << 0)
/* AE_GB_THD0 0x0034 */
#define MIN_GB_OFFSET 0
#define MIN_GB_BITS 10
#define MIN_GB_MASK (((1 << 10) - 1) << 0)
/* AE_GB_THD1 0x0038 */
#define MAX_GB_OFFSET 0
#define MAX_GB_BITS 10
#define MAX_GB_MASK (((1 << 10) - 1) << 0)
/* AE_B_THD0 0x003C */
#define MIN_B_OFFSET 0
#define MIN_B_BITS 10
#define MIN_B_MASK (((1 << 10) - 1) << 0)
/* AE_B_THD1 0x0040 */
#define MAX_B_OFFSET 0
#define MAX_B_BITS 10
#define MAX_B_MASK (((1 << 10) - 1) << 0)
/* AE_SUM_MAX_Y 0x0044 */
#define MAX_SUM_Y_OFFSET 0
#define MAX_SUM_Y_BITS 19
#define MAX_SUM_Y_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MIN_Y 0x0048 */
#define MIN_SUM_Y_OFFSET 0
#define MIN_SUM_Y_BITS 19
#define MIN_SUM_Y_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MAX_R 0x004C */
#define MAX_SUM_R_OFFSET 0
#define MAX_SUM_R_BITS 19
#define MAX_SUM_R_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MIN_R 0x0050 */
#define MIN_SUM_R_OFFSET 0
#define MIN_SUM_R_BITS 19
#define MIN_SUM_R_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MAX_GR 0x0054 */
#define MAX_SUM_GR_OFFSET 0
#define MAX_SUM_GR_BITS 19
#define MAX_SUM_GR_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MIN_GR 0x0058 */
#define MIN_SUM_GR_OFFSET 0
#define MIN_SUM_GR_BITS 19
#define MIN_SUM_GR_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MAX_GB 0x005C */
#define MAX_SUM_GB_OFFSET 0
#define MAX_SUM_GB_BITS 19
#define MAX_SUM_GB_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MIN_GB 0x0060 */
#define MIN_SUM_GB_OFFSET 0
#define MIN_SUM_GB_BITS 19
#define MIN_SUM_GB_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MAX_B 0x0064 */
#define MAX_SUM_B_OFFSET 0
#define MAX_SUM_B_BITS 19
#define MAX_SUM_B_MASK (((1 << 19) - 1) << 0)
/* AE_SUM_MIN_B 0x0068 */
#define MIN_SUM_B_OFFSET 0
#define MIN_SUM_B_BITS 19
#define MIN_SUM_B_MASK (((1 << 19) - 1) << 0)
/* AE_YWIN_START 0x006C */
#define YSTA_X_OFFSET 0
#define YSTA_X_BITS 12
#define YSTA_X_MASK (((1 << 12) - 1) << 0)
#define YSTA_Y_OFFSET 16
#define YSTA_Y_BITS 12
#define YSTA_Y_MASK (((1 << 12) - 1) << 16)
/* AE_YWIN_END 0x0070 */
#define YEND_X_OFFSET 0
#define YEND_X_BITS 12
#define YEND_X_MASK (((1 << 12) - 1) << 0)
#define YEND_Y_OFFSET 16
#define YEND_Y_BITS 12
#define YEND_Y_MASK (((1 << 12) - 1) << 16)
/* AE_YSUM 0x0074 */
#define YSUM_OFFSET 0
#define YSUM_BITS 29
#define YSUM_MASK (((1 << 29) - 1) << 0)
/* AE_ADDR 0x0078 */
#define AE_ADDR_OFFSET 0
#define AE_ADDR_BITS 9
#define AE_ADDR_MASK (((1 << 9) - 1) << 0)
/* AE_WIN_RESULT 0x007C */
#define AE_RESULT_OFFSET 0
#define AE_RESULT_BITS 22
#define AE_RESULT_MASK (((1 << 22) - 1) << 0)
/* AE_GAIN 0x0080 */
#define AE_GAIN_OFFSET 0
#define AE_GAIN_BITS 16
#define AE_GAIN_MASK (((1 << 16) - 1) << 0)
/* AE_GAIN_CTRL 0x0088 */
#define AE_GAIN_DELAY_OFFSET 0
#define AE_GAIN_DELAY_BITS 2
#define AE_GAIN_DELAY_MASK (((1 << 2) - 1) << 0)
#define AE_GAIN_TRIG_OFFSET 8
#define AE_GAIN_TRIG_BITS 1
#define AE_GAIN_TRIG_MASK (((1 << 1) - 1) << 8)

#endif /* _ISP_REG_AE_H_INC_ */

