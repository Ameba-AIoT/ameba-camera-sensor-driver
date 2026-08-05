#ifndef _ISP_REG_AWB_H_INC_
#define _ISP_REG_AWB_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define AWB_STATIS_CTRL (AWB_REG_BASE + 0x0000)
#define AWB_GAIN_CTRL (AWB_REG_BASE + 0x0004)
#define AWB_GAIN_R (AWB_REG_BASE + 0x0008)
#define AWB_GAIN_G (AWB_REG_BASE + 0x000C)
#define AWB_GAIN_B (AWB_REG_BASE + 0x0010)
#define AWB_GAIN_IR (AWB_REG_BASE + 0x0014)
#define AWB_GAIN_STEP (AWB_REG_BASE + 0x0018)
#define AWB_GAIN_R_NOW (AWB_REG_BASE + 0x001C)
#define AWB_GAIN_G_NOW (AWB_REG_BASE + 0x0020)
#define AWB_GAIN_B_NOW (AWB_REG_BASE + 0x0024)
#define AWB_GAIN_IR_NOW (AWB_REG_BASE + 0x0028)
#define AWB_FINE_TUNE_GAIN (AWB_REG_BASE + 0x002C)
#define AWB_WIN_START (AWB_REG_BASE + 0x0040)
#define AWB_WIN_SIZE (AWB_REG_BASE + 0x0044)
#define AWB_BRIGHT_COEF (AWB_REG_BASE + 0x0050)
#define AWB_WIN_LIMIT_ENABLE (AWB_REG_BASE + 0x0054)
#define AWB_WIN_BRIGHT_THD (AWB_REG_BASE + 0x0058)
#define AWB_WIN_R_THD (AWB_REG_BASE + 0x005C)
#define AWB_WIN_G_THD (AWB_REG_BASE + 0x0060)
#define AWB_WIN_B_THD (AWB_REG_BASE + 0x0064)
#define AWB_WIN_RG_THD (AWB_REG_BASE + 0x0068)
#define AWB_WIN_BG_THD (AWB_REG_BASE + 0x006C)
#define AWB_RGBC_K1 (AWB_REG_BASE + 0x0070)
#define AWB_RGBC_C1 (AWB_REG_BASE + 0x0074)
#define AWB_RGBC_C2 (AWB_REG_BASE + 0x0078)
#define AWB_FINE_RG_THD (AWB_REG_BASE + 0x007C)
#define AWB_FINE_BG_THD (AWB_REG_BASE + 0x0080)
#define AWB_FINE_BRIGHT_THD (AWB_REG_BASE + 0x0084)
#define AWB_FINE_WP_NUM (AWB_REG_BASE + 0x0088)
#define AWB_FINE_SUM_R (AWB_REG_BASE + 0x008C)
#define AWB_FINE_SUM_G (AWB_REG_BASE + 0x0090)
#define AWB_FINE_SUM_B (AWB_REG_BASE + 0x0094)
#define AWB_FINE_DIV (AWB_REG_BASE + 0x0098)
#define AWB_ROUGH_RG_THD (AWB_REG_BASE + 0x009C)
#define AWB_ROUGH_BG_THD (AWB_REG_BASE + 0x00A0)
#define AWB_ROUGH_BRIGHT_THD (AWB_REG_BASE + 0x00A4)
#define AWB_ROUGH_GAIN_R_1_2 (AWB_REG_BASE + 0x00A8)
#define AWB_ROUGH_GAIN_R_3_4 (AWB_REG_BASE + 0x00AC)
#define AWB_ROUGH_GAIN_R_5_6 (AWB_REG_BASE + 0x00B0)
#define AWB_ROUGH_GAIN_B_1_2 (AWB_REG_BASE + 0x00B4)
#define AWB_ROUGH_GAIN_B_3_4 (AWB_REG_BASE + 0x00B8)
#define AWB_ROUGH_GAIN_B_5_6 (AWB_REG_BASE + 0x00BC)
#define AWB_WP_NUM1 (AWB_REG_BASE + 0x00C0)
#define AWB_WP_NUM2 (AWB_REG_BASE + 0x00C4)
#define AWB_WP_NUM3 (AWB_REG_BASE + 0x00C8)
#define AWB_WP_NUM4 (AWB_REG_BASE + 0x00CC)
#define AWB_WP_NUM5 (AWB_REG_BASE + 0x00D0)
#define AWB_WP_NUM6 (AWB_REG_BASE + 0x00D4)
#define AWB_WIN_STATIS_ADDR (AWB_REG_BASE + 0x00D8)
#define AWB_WIN_STATIS_PIXEL_NUM (AWB_REG_BASE + 0x00DC)
#define AWB_WIN_BG_RG_MEAN_DIV (AWB_REG_BASE + 0x00E0)
#define AWB_WIN_MEAN0 (AWB_REG_BASE + 0x00E4)
#define AWB_WIN_MEAN1 (AWB_REG_BASE + 0x00E8)
#define AWB_WIN_R_SUM (AWB_REG_BASE + 0x00EC)
#define AWB_WIN_G_SUM (AWB_REG_BASE + 0x00F0)
#define AWB_WIN_B_SUM (AWB_REG_BASE + 0x00F4)
#define AWB_OVER_EXP_REDUCT_EN (AWB_REG_BASE + 0x00F8)

/* AWB_STATIS_CTRL 0x0000 */
#define CSYS_MODE_OFFSET 0
#define CSYS_MODE_BITS 1
#define CSYS_MODE_MASK (((1 << 1) - 1) << 0)
#define STATS_MODE_OFFSET 1
#define STATS_MODE_BITS 1
#define STATS_MODE_MASK (((1 << 1) - 1) << 1)
#define FINE_EN_OFFSET 2
#define FINE_EN_BITS 1
#define FINE_EN_MASK (((1 << 1) - 1) << 2)
#define ROUGH_EN_OFFSET 3
#define ROUGH_EN_BITS 1
#define ROUGH_EN_MASK (((1 << 1) - 1) << 3)
#define STATS_NUM_MODE_OFFSET 4
#define STATS_NUM_MODE_BITS 1
#define STATS_NUM_MODE_MASK (((1 << 1) - 1) << 4)
#define AWB_STOP_OFFSET 5
#define AWB_STOP_BITS 1
#define AWB_STOP_MASK (((1 << 1) - 1) << 5)
#define AWB_START_OFFSET 6
#define AWB_START_BITS 1
#define AWB_START_MASK (((1 << 1) - 1) << 6)
#define AWB_MODE_OFFSET 8
#define AWB_MODE_BITS 2
#define AWB_MODE_MASK (((1 << 2) - 1) << 8)
/* AWB_GAIN_CTRL 0x0004 */
#define AWB_GAIN_MODE_OFFSET 0
#define AWB_GAIN_MODE_BITS 1
#define AWB_GAIN_MODE_MASK (((1 << 1) - 1) << 0)
#define AWB_GAIN_STOP_OFFSET 1
#define AWB_GAIN_STOP_BITS 1
#define AWB_GAIN_STOP_MASK (((1 << 1) - 1) << 1)
#define AWB_GAIN_TRIG_OFFSET 2
#define AWB_GAIN_TRIG_BITS 1
#define AWB_GAIN_TRIG_MASK (((1 << 1) - 1) << 2)
#define AWB_GAIN_GOING_OFFSET 3
#define AWB_GAIN_GOING_BITS 1
#define AWB_GAIN_GOING_MASK (((1 << 1) - 1) << 3)
/* AWB_GAIN_R 0x0008 */
#define AWB_GAIN_R_OFFSET 0
#define AWB_GAIN_R_BITS 12
#define AWB_GAIN_R_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_G 0x000C */
#define AWB_GAIN_G_OFFSET 0
#define AWB_GAIN_G_BITS 12
#define AWB_GAIN_G_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_B 0x0010 */
#define AWB_GAIN_B_OFFSET 0
#define AWB_GAIN_B_BITS 12
#define AWB_GAIN_B_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_IR 0x0014 */
#define AWB_GAIN_IR_OFFSET 0
#define AWB_GAIN_IR_BITS 12
#define AWB_GAIN_IR_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_STEP 0x0018 */
#define AWB_STEP_R_OFFSET 0
#define AWB_STEP_R_BITS 8
#define AWB_STEP_R_MASK (((1 << 8) - 1) << 0)
#define AWB_STEP_G_OFFSET 8
#define AWB_STEP_G_BITS 8
#define AWB_STEP_G_MASK (((1 << 8) - 1) << 8)
#define AWB_STEP_B_OFFSET 16
#define AWB_STEP_B_BITS 8
#define AWB_STEP_B_MASK (((1 << 8) - 1) << 16)
#define AWB_STEP_IR_OFFSET 24
#define AWB_STEP_IR_BITS 8
#define AWB_STEP_IR_MASK (((1 << 8) - 1) << 24)
/* AWB_GAIN_R_NOW 0x001C */
#define R_GAIN_OFFSET 0
#define R_GAIN_BITS 12
#define R_GAIN_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_G_NOW 0x0020 */
#define GB_GAIN_OFFSET 0
#define GB_GAIN_BITS 12
#define GB_GAIN_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_B_NOW 0x0024 */
#define B_GAIN_OFFSET 0
#define B_GAIN_BITS 12
#define B_GAIN_MASK (((1 << 12) - 1) << 0)
/* AWB_GAIN_IR_NOW 0x0028 */
#define GRIR_GAIN_OFFSET 0
#define GRIR_GAIN_BITS 12
#define GRIR_GAIN_MASK (((1 << 12) - 1) << 0)
/* AWB_FINE_TUNE_GAIN 0x002C */
#define GAIN_R_FINE_OFFSET 0
#define GAIN_R_FINE_BITS 11
#define GAIN_R_FINE_MASK (((1 << 11) - 1) << 0)
#define GAIN_B_FINE_OFFSET 16
#define GAIN_B_FINE_BITS 11
#define GAIN_B_FINE_MASK (((1 << 11) - 1) << 16)
/* AWB_WIN_START 0x0040 */
#define AWB_START_X_OFFSET 0
#define AWB_START_X_BITS 12
#define AWB_START_X_MASK (((1 << 12) - 1) << 0)
#define AWB_START_Y_OFFSET 16
#define AWB_START_Y_BITS 12
#define AWB_START_Y_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_SIZE 0x0044 */
#define AWB_WIN_WIDTH_OFFSET 0
#define AWB_WIN_WIDTH_BITS 8
#define AWB_WIN_WIDTH_MASK (((1 << 8) - 1) << 0)
#define AWB_WIN_HEIGHT_OFFSET 8
#define AWB_WIN_HEIGHT_BITS 8
#define AWB_WIN_HEIGHT_MASK (((1 << 8) - 1) << 8)
#define AWB_WIN_NUM_H_OFFSET 16
#define AWB_WIN_NUM_H_BITS 5
#define AWB_WIN_NUM_H_MASK (((1 << 5) - 1) << 16)
#define AWB_WIN_NUM_V_OFFSET 24
#define AWB_WIN_NUM_V_BITS 5
#define AWB_WIN_NUM_V_MASK (((1 << 5) - 1) << 24)
/* AWB_BRIGHT_COEF 0x0050 */
#define COEF_BRIGHT_R_OFFSET 0
#define COEF_BRIGHT_R_BITS 4
#define COEF_BRIGHT_R_MASK (((1 << 4) - 1) << 0)
#define COEF_BRIGHT_G_OFFSET 4
#define COEF_BRIGHT_G_BITS 4
#define COEF_BRIGHT_G_MASK (((1 << 4) - 1) << 4)
#define COEF_BRIGHT_B_OFFSET 8
#define COEF_BRIGHT_B_BITS 4
#define COEF_BRIGHT_B_MASK (((1 << 4) - 1) << 8)
/* AWB_WIN_LIMIT_ENABLE 0x0054 */
#define AWB_WIN_RANGE_EN_OFFSET 0
#define AWB_WIN_RANGE_EN_BITS 1
#define AWB_WIN_RANGE_EN_MASK (((1 << 1) - 1) << 0)
#define AWB_WIN_RATIO_EN_OFFSET 1
#define AWB_WIN_RATIO_EN_BITS 1
#define AWB_WIN_RATIO_EN_MASK (((1 << 1) - 1) << 1)
#define AWB_WIN_BGRG_EN_OFFSET 2
#define AWB_WIN_BGRG_EN_BITS 1
#define AWB_WIN_BGRG_EN_MASK (((1 << 1) - 1) << 2)
/* AWB_WIN_BRIGHT_THD 0x0058 */
#define MAX_BRIGHT_WIN_OFFSET 0
#define MAX_BRIGHT_WIN_BITS 12
#define MAX_BRIGHT_WIN_MASK (((1 << 12) - 1) << 0)
#define MIN_BRIGHT_WIN_OFFSET 16
#define MIN_BRIGHT_WIN_BITS 12
#define MIN_BRIGHT_WIN_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_R_THD 0x005C */
#define MAX_R_WIN_OFFSET 0
#define MAX_R_WIN_BITS 12
#define MAX_R_WIN_MASK (((1 << 12) - 1) << 0)
#define MIN_R_WIN_OFFSET 16
#define MIN_R_WIN_BITS 12
#define MIN_R_WIN_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_G_THD 0x0060 */
#define MAX_G_WIN_OFFSET 0
#define MAX_G_WIN_BITS 12
#define MAX_G_WIN_MASK (((1 << 12) - 1) << 0)
#define MIN_G_WIN_OFFSET 16
#define MIN_G_WIN_BITS 12
#define MIN_G_WIN_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_B_THD 0x0064 */
#define MAX_B_WIN_OFFSET 0
#define MAX_B_WIN_BITS 12
#define MAX_B_WIN_MASK (((1 << 12) - 1) << 0)
#define MIN_B_WIN_OFFSET 16
#define MIN_B_WIN_BITS 12
#define MIN_B_WIN_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_RG_THD 0x0068 */
#define MAX_R_G_WIN_OFFSET 0
#define MAX_R_G_WIN_BITS 11
#define MAX_R_G_WIN_MASK (((1 << 11) - 1) << 0)
#define MIN_R_G_WIN_OFFSET 16
#define MIN_R_G_WIN_BITS 11
#define MIN_R_G_WIN_MASK (((1 << 11) - 1) << 16)
/* AWB_WIN_BG_THD 0x006C */
#define MAX_B_G_WIN_OFFSET 0
#define MAX_B_G_WIN_BITS 11
#define MAX_B_G_WIN_MASK (((1 << 11) - 1) << 0)
#define MIN_B_G_WIN_OFFSET 16
#define MIN_B_G_WIN_BITS 11
#define MIN_B_G_WIN_MASK (((1 << 11) - 1) << 16)
/* AWB_RGBC_K1 0x0070 */
#define AWB_WIN_K1_OFFSET 0
#define AWB_WIN_K1_BITS 11
#define AWB_WIN_K1_MASK (((1 << 11) - 1) << 0)
/* AWB_RGBC_C1 0x0074 */
#define AWB_WIN_C0_OFFSET 0
#define AWB_WIN_C0_BITS 16
#define AWB_WIN_C0_MASK (((1 << 16) - 1) << 0)
#define AWB_WIN_C2_OFFSET 16
#define AWB_WIN_C2_BITS 16
#define AWB_WIN_C2_MASK (((1 << 16) - 1) << 16)
/* AWB_RGBC_C2 0x0078 */
#define AWB_WIN_C1_OFFSET 0
#define AWB_WIN_C1_BITS 16
#define AWB_WIN_C1_MASK (((1 << 16) - 1) << 0)
#define AWB_WIN_C3_OFFSET 16
#define AWB_WIN_C3_BITS 16
#define AWB_WIN_C3_MASK (((1 << 16) - 1) << 16)
/* AWB_FINE_RG_THD 0x007C */
#define MAX_R_G_FINE_OFFSET 0
#define MAX_R_G_FINE_BITS 11
#define MAX_R_G_FINE_MASK (((1 << 11) - 1) << 0)
#define MIN_R_G_FINE_OFFSET 16
#define MIN_R_G_FINE_BITS 11
#define MIN_R_G_FINE_MASK (((1 << 11) - 1) << 16)
/* AWB_FINE_BG_THD 0x0080 */
#define MAX_B_G_FINE_OFFSET 0
#define MAX_B_G_FINE_BITS 11
#define MAX_B_G_FINE_MASK (((1 << 11) - 1) << 0)
#define MIN_B_G_FINE_OFFSET 16
#define MIN_B_G_FINE_BITS 11
#define MIN_B_G_FINE_MASK (((1 << 11) - 1) << 16)
/* AWB_FINE_BRIGHT_THD 0x0084 */
#define MAX_BRIGHT_FINE_OFFSET 0
#define MAX_BRIGHT_FINE_BITS 12
#define MAX_BRIGHT_FINE_MASK (((1 << 12) - 1) << 0)
#define MIN_BRIGHT_FINE_OFFSET 16
#define MIN_BRIGHT_FINE_BITS 12
#define MIN_BRIGHT_FINE_MASK (((1 << 12) - 1) << 16)
/* AWB_FINE_WP_NUM 0x0088 */
#define WP_NUM_FINE_OFFSET 0
#define WP_NUM_FINE_BITS 21
#define WP_NUM_FINE_MASK (((1 << 21) - 1) << 0)
/* AWB_FINE_SUM_R 0x008C */
/* AWB_FINE_SUM_G 0x0090 */
/* AWB_FINE_SUM_B 0x0094 */
/* AWB_FINE_DIV 0x0098 */
#define GAIN_FINE1_OFFSET 0
#define GAIN_FINE1_BITS 16
#define GAIN_FINE1_MASK (((1 << 16) - 1) << 0)
#define GAIN_FINE2_OFFSET 16
#define GAIN_FINE2_BITS 16
#define GAIN_FINE2_MASK (((1 << 16) - 1) << 16)
/* AWB_ROUGH_RG_THD 0x009C */
#define MAX_RG_ROUGH_OFFSET 0
#define MAX_RG_ROUGH_BITS 11
#define MAX_RG_ROUGH_MASK (((1 << 11) - 1) << 0)
#define MIN_RG_ROUGH_OFFSET 16
#define MIN_RG_ROUGH_BITS 11
#define MIN_RG_ROUGH_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_BG_THD 0x00A0 */
#define MAX_BG_ROUGH_OFFSET 0
#define MAX_BG_ROUGH_BITS 11
#define MAX_BG_ROUGH_MASK (((1 << 11) - 1) << 0)
#define MIN_BG_ROUGH_OFFSET 16
#define MIN_BG_ROUGH_BITS 11
#define MIN_BG_ROUGH_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_BRIGHT_THD 0x00A4 */
#define MAX_BRIGHT_ROUGH_OFFSET 0
#define MAX_BRIGHT_ROUGH_BITS 12
#define MAX_BRIGHT_ROUGH_MASK (((1 << 12) - 1) << 0)
#define MIN_BRIGHT_ROUGH_OFFSET 16
#define MIN_BRIGHT_ROUGH_BITS 12
#define MIN_BRIGHT_ROUGH_MASK (((1 << 12) - 1) << 16)
/* AWB_ROUGH_GAIN_R_1_2 0x00A8 */
#define GAIN_R_ROUGH_1_OFFSET 0
#define GAIN_R_ROUGH_1_BITS 11
#define GAIN_R_ROUGH_1_MASK (((1 << 11) - 1) << 0)
#define GAIN_R_ROUGH_2_OFFSET 16
#define GAIN_R_ROUGH_2_BITS 11
#define GAIN_R_ROUGH_2_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_GAIN_R_3_4 0x00AC */
#define GAIN_R_ROUGH_3_OFFSET 0
#define GAIN_R_ROUGH_3_BITS 11
#define GAIN_R_ROUGH_3_MASK (((1 << 11) - 1) << 0)
#define GAIN_R_ROUGH_4_OFFSET 16
#define GAIN_R_ROUGH_4_BITS 11
#define GAIN_R_ROUGH_4_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_GAIN_R_5_6 0x00B0 */
#define GAIN_R_ROUGH_5_OFFSET 0
#define GAIN_R_ROUGH_5_BITS 11
#define GAIN_R_ROUGH_5_MASK (((1 << 11) - 1) << 0)
#define GAIN_R_ROUGH_6_OFFSET 16
#define GAIN_R_ROUGH_6_BITS 11
#define GAIN_R_ROUGH_6_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_GAIN_B_1_2 0x00B4 */
#define GAIN_B_ROUGH_1_OFFSET 0
#define GAIN_B_ROUGH_1_BITS 11
#define GAIN_B_ROUGH_1_MASK (((1 << 11) - 1) << 0)
#define GAIN_B_ROUGH_2_OFFSET 16
#define GAIN_B_ROUGH_2_BITS 11
#define GAIN_B_ROUGH_2_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_GAIN_B_3_4 0x00B8 */
#define GAIN_B_ROUGH_3_OFFSET 0
#define GAIN_B_ROUGH_3_BITS 11
#define GAIN_B_ROUGH_3_MASK (((1 << 11) - 1) << 0)
#define GAIN_B_ROUGH_4_OFFSET 16
#define GAIN_B_ROUGH_4_BITS 11
#define GAIN_B_ROUGH_4_MASK (((1 << 11) - 1) << 16)
/* AWB_ROUGH_GAIN_B_5_6 0x00BC */
#define GAIN_B_ROUGH_5_OFFSET 0
#define GAIN_B_ROUGH_5_BITS 11
#define GAIN_B_ROUGH_5_MASK (((1 << 11) - 1) << 0)
#define GAIN_B_ROUGH_6_OFFSET 16
#define GAIN_B_ROUGH_6_BITS 11
#define GAIN_B_ROUGH_6_MASK (((1 << 11) - 1) << 16)
/* AWB_WP_NUM1 0x00C0 */
#define WP_NUM_1_OFFSET 0
#define WP_NUM_1_BITS 21
#define WP_NUM_1_MASK (((1 << 21) - 1) << 0)
/* AWB_WP_NUM2 0x00C4 */
#define WP_NUM_2_OFFSET 0
#define WP_NUM_2_BITS 21
#define WP_NUM_2_MASK (((1 << 21) - 1) << 0)
/* AWB_WP_NUM3 0x00C8 */
#define WP_NUM_3_OFFSET 0
#define WP_NUM_3_BITS 21
#define WP_NUM_3_MASK (((1 << 21) - 1) << 0)
/* AWB_WP_NUM4 0x00CC */
#define WP_NUM_4_OFFSET 0
#define WP_NUM_4_BITS 21
#define WP_NUM_4_MASK (((1 << 21) - 1) << 0)
/* AWB_WP_NUM5 0x00D0 */
#define WP_NUM_5_OFFSET 0
#define WP_NUM_5_BITS 21
#define WP_NUM_5_MASK (((1 << 21) - 1) << 0)
/* AWB_WP_NUM6 0x00D4 */
#define WP_NUM_6_OFFSET 0
#define WP_NUM_6_BITS 21
#define WP_NUM_6_MASK (((1 << 21) - 1) << 0)
/* AWB_WIN_STATIS_ADDR 0x00D8 */
#define AWB_ADDR_OFFSET 0
#define AWB_ADDR_BITS 8
#define AWB_ADDR_MASK (((1 << 8) - 1) << 0)
/* AWB_WIN_STATIS_PIXEL_NUM 0x00DC */
#define AWB_WIN_NUM_STATS_OFFSET 0
#define AWB_WIN_NUM_STATS_BITS 15
#define AWB_WIN_NUM_STATS_MASK (((1 << 15) - 1) << 0)
/* AWB_WIN_BG_RG_MEAN_DIV 0x00E0 */
#define COOR_GAIN1_RF_OFFSET 0
#define COOR_GAIN1_RF_BITS 11
#define COOR_GAIN1_RF_MASK (((1 << 11) - 1) << 0)
#define COOR_GAIN2_RF_OFFSET 16
#define COOR_GAIN2_RF_BITS 11
#define COOR_GAIN2_RF_MASK (((1 << 11) - 1) << 16)
/* AWB_WIN_MEAN0 0x00E4 */
#define R_MEAN_RF_OFFSET 0
#define R_MEAN_RF_BITS 12
#define R_MEAN_RF_MASK (((1 << 12) - 1) << 0)
#define G_MEAN_RF_OFFSET 16
#define G_MEAN_RF_BITS 12
#define G_MEAN_RF_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_MEAN1 0x00E8 */
#define B_MEAN_RF_OFFSET 0
#define B_MEAN_RF_BITS 12
#define B_MEAN_RF_MASK (((1 << 12) - 1) << 0)
#define Y_MEAN_RF_OFFSET 16
#define Y_MEAN_RF_BITS 12
#define Y_MEAN_RF_MASK (((1 << 12) - 1) << 16)
/* AWB_WIN_R_SUM 0x00EC */
#define SUM_R_OFFSET 0
#define SUM_R_BITS 27
#define SUM_R_MASK (((1 << 27) - 1) << 0)
/* AWB_WIN_G_SUM 0x00F0 */
#define SUM_G_OFFSET 0
#define SUM_G_BITS 27
#define SUM_G_MASK (((1 << 27) - 1) << 0)
/* AWB_WIN_B_SUM 0x00F4 */
#define SUM_B_OFFSET 0
#define SUM_B_BITS 27
#define SUM_B_MASK (((1 << 27) - 1) << 0)
/* AWB_OVER_EXP_REDUCT_EN 0x00F8 */
#define OVER_EN_OFFSET 0
#define OVER_EN_BITS 1
#define OVER_EN_MASK (((1 << 1) - 1) << 0)
#define CLIP_12BITS_ENABLE_OFFSET 1
#define CLIP_12BITS_ENABLE_BITS 1
#define CLIP_12BITS_ENABLE_MASK (((1 << 1) - 1) << 1)
#define CLIP_14BITS_ENABLE_OFFSET 2
#define CLIP_14BITS_ENABLE_BITS 1
#define CLIP_14BITS_ENABLE_MASK (((1 << 1) - 1) << 2)

#endif /* _ISP_REG_AWB_H_INC_ */

