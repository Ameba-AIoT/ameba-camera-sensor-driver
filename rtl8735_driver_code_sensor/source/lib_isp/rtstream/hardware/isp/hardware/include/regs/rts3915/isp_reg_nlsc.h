#ifndef _ISP_REG_NLSC_H_INC_
#define _ISP_REG_NLSC_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define NLSC_MODE (NLSC_REG_BASE + 0x0000)
#define NLSC_ADJ_RATE (NLSC_REG_BASE + 0x0004)
#define NLSC_GAIN_STEP (NLSC_REG_BASE + 0x0008)
#define NLSC_GAIN_CTRL (NLSC_REG_BASE + 0x000C)
#define NLSC_CENTER_R (NLSC_REG_BASE + 0x0010)
#define NLSC_DISTANCE_CFG_R (NLSC_REG_BASE + 0x0014)
#define NLSC_CURVE_R_P0_P1 (NLSC_REG_BASE + 0x0018)
#define NLSC_CURVE_R_P2_P3 (NLSC_REG_BASE + 0x001C)
#define NLSC_CURVE_R_P4_P5 (NLSC_REG_BASE + 0x0020)
#define NLSC_CURVE_R_P6_P7 (NLSC_REG_BASE + 0x0024)
#define NLSC_CURVE_R_P8_P9 (NLSC_REG_BASE + 0x0028)
#define NLSC_CURVE_R_P10_P11 (NLSC_REG_BASE + 0x002C)
#define NLSC_CURVE_R_P12_P13 (NLSC_REG_BASE + 0x0030)
#define NLSC_CURVE_R_P14_P15 (NLSC_REG_BASE + 0x0034)
#define NLSC_CURVE_R_P16_P17 (NLSC_REG_BASE + 0x0038)
#define NLSC_CURVE_R_P18_P19 (NLSC_REG_BASE + 0x003C)
#define NLSC_CURVE_R_P20_P21 (NLSC_REG_BASE + 0x0040)
#define NLSC_CURVE_R_P22_P23 (NLSC_REG_BASE + 0x0044)
#define NLSC_CURVE_R_P24_P25 (NLSC_REG_BASE + 0x0048)
#define NLSC_CURVE_R_P26_P27 (NLSC_REG_BASE + 0x004C)
#define NLSC_CURVE_R_P28_P29 (NLSC_REG_BASE + 0x0050)
#define NLSC_CURVE_R_P30_P31 (NLSC_REG_BASE + 0x0054)
#define NLSC_CENTER_G (NLSC_REG_BASE + 0x0058)
#define NLSC_DISTANCE_CFG_G (NLSC_REG_BASE + 0x005C)
#define NLSC_CURVE_G_P0_P1 (NLSC_REG_BASE + 0x0060)
#define NLSC_CURVE_G_P2_P3 (NLSC_REG_BASE + 0x0064)
#define NLSC_CURVE_G_P4_P5 (NLSC_REG_BASE + 0x0068)
#define NLSC_CURVE_G_P6_P7 (NLSC_REG_BASE + 0x006C)
#define NLSC_CURVE_G_P8_P9 (NLSC_REG_BASE + 0x0070)
#define NLSC_CURVE_G_P10_P11 (NLSC_REG_BASE + 0x0074)
#define NLSC_CURVE_G_P12_P13 (NLSC_REG_BASE + 0x0078)
#define NLSC_CURVE_G_P14_P15 (NLSC_REG_BASE + 0x007C)
#define NLSC_CURVE_G_P16_P17 (NLSC_REG_BASE + 0x0080)
#define NLSC_CURVE_G_P18_P19 (NLSC_REG_BASE + 0x0084)
#define NLSC_CURVE_G_P20_P21 (NLSC_REG_BASE + 0x0088)
#define NLSC_CURVE_G_P22_P23 (NLSC_REG_BASE + 0x008C)
#define NLSC_CURVE_G_P24_P25 (NLSC_REG_BASE + 0x0090)
#define NLSC_CURVE_G_P26_P27 (NLSC_REG_BASE + 0x0094)
#define NLSC_CURVE_G_P28_P29 (NLSC_REG_BASE + 0x0098)
#define NLSC_CURVE_G_P30_P31 (NLSC_REG_BASE + 0x009C)
#define NLSC_CENTER_B (NLSC_REG_BASE + 0x00A0)
#define NLSC_DISTANCE_CFG_B (NLSC_REG_BASE + 0x00A4)
#define NLSC_CURVE_B_P0_P1 (NLSC_REG_BASE + 0x00A8)
#define NLSC_CURVE_B_P2_P3 (NLSC_REG_BASE + 0x00AC)
#define NLSC_CURVE_B_P4_P5 (NLSC_REG_BASE + 0x00B0)
#define NLSC_CURVE_B_P6_P7 (NLSC_REG_BASE + 0x00B4)
#define NLSC_CURVE_B_P8_P9 (NLSC_REG_BASE + 0x00B8)
#define NLSC_CURVE_B_P10_P11 (NLSC_REG_BASE + 0x00BC)
#define NLSC_CURVE_B_P12_P13 (NLSC_REG_BASE + 0x00C0)
#define NLSC_CURVE_B_P14_P15 (NLSC_REG_BASE + 0x00C4)
#define NLSC_CURVE_B_P16_P17 (NLSC_REG_BASE + 0x00C8)
#define NLSC_CURVE_B_P18_P19 (NLSC_REG_BASE + 0x00CC)
#define NLSC_CURVE_B_P20_P21 (NLSC_REG_BASE + 0x00D0)
#define NLSC_CURVE_B_P22_P23 (NLSC_REG_BASE + 0x00D4)
#define NLSC_CURVE_B_P24_P25 (NLSC_REG_BASE + 0x00D8)
#define NLSC_CURVE_B_P26_P27 (NLSC_REG_BASE + 0x00DC)
#define NLSC_CURVE_B_P28_P29 (NLSC_REG_BASE + 0x00E0)
#define NLSC_CURVE_B_P30_P31 (NLSC_REG_BASE + 0x00E4)
#define NLSC_OVEREXP_RATIO (NLSC_REG_BASE + 0x00E8)
#define NLSC_OVEREXP_THD (NLSC_REG_BASE + 0x00EC)
#define NLSC_CENTER_RGB_CTRL (NLSC_REG_BASE + 0x00F0)

/* NLSC_MODE 0x0000 */
#define LENS_MODE_OFFSET 0
#define LENS_MODE_BITS 2
#define LENS_MODE_MASK (((1 << 2) - 1) << 0)
#define ADJRATE_R_EN_OFFSET 2
#define ADJRATE_R_EN_BITS 1
#define ADJRATE_R_EN_MASK (((1 << 1) - 1) << 2)
#define ADJRATE_G_EN_OFFSET 3
#define ADJRATE_G_EN_BITS 1
#define ADJRATE_G_EN_MASK (((1 << 1) - 1) << 3)
#define ADJRATE_B_EN_OFFSET 4
#define ADJRATE_B_EN_BITS 1
#define ADJRATE_B_EN_MASK (((1 << 1) - 1) << 4)
/* NLSC_ADJ_RATE 0x0004 */
#define ADJRATE_R_OFFSET 0
#define ADJRATE_R_BITS 6
#define ADJRATE_R_MASK (((1 << 6) - 1) << 0)
#define ADJRATE_G_OFFSET 8
#define ADJRATE_G_BITS 6
#define ADJRATE_G_MASK (((1 << 6) - 1) << 8)
#define ADJRATE_B_OFFSET 16
#define ADJRATE_B_BITS 6
#define ADJRATE_B_MASK (((1 << 6) - 1) << 16)
/* NLSC_GAIN_STEP 0x0008 */
#define NLSC_STEP_R_OFFSET 0
#define NLSC_STEP_R_BITS 5
#define NLSC_STEP_R_MASK (((1 << 5) - 1) << 0)
#define NLSC_STEP_G_OFFSET 8
#define NLSC_STEP_G_BITS 5
#define NLSC_STEP_G_MASK (((1 << 5) - 1) << 8)
#define NLSC_STEP_B_OFFSET 16
#define NLSC_STEP_B_BITS 5
#define NLSC_STEP_B_MASK (((1 << 5) - 1) << 16)
/* NLSC_GAIN_CTRL 0x000C */
#define NLSC_ADJ_MODE_OFFSET 0
#define NLSC_ADJ_MODE_BITS 1
#define NLSC_ADJ_MODE_MASK (((1 << 1) - 1) << 0)
#define NLSC_ADJ_STOP_OFFSET 6
#define NLSC_ADJ_STOP_BITS 1
#define NLSC_ADJ_STOP_MASK (((1 << 1) - 1) << 6)
#define NLSC_ADJ_TRIG_OFFSET 7
#define NLSC_ADJ_TRIG_BITS 1
#define NLSC_ADJ_TRIG_MASK (((1 << 1) - 1) << 7)
#define NLSC_ADJ_GOING_OFFSET 8
#define NLSC_ADJ_GOING_BITS 1
#define NLSC_ADJ_GOING_MASK (((1 << 1) - 1) << 8)
/* NLSC_CENTER_R 0x0010 */
#define LENS_CENTER_X_R_OFFSET 0
#define LENS_CENTER_X_R_BITS 12
#define LENS_CENTER_X_R_MASK (((1 << 12) - 1) << 0)
#define LENS_CENTER_Y_R_OFFSET 16
#define LENS_CENTER_Y_R_BITS 12
#define LENS_CENTER_Y_R_MASK (((1 << 12) - 1) << 16)
/* NLSC_DISTANCE_CFG_R 0x0014 */
#define LENS_FS_DST_R_OFFSET 0
#define LENS_FS_DST_R_BITS 12
#define LENS_FS_DST_R_MASK (((1 << 12) - 1) << 0)
#define LENS_FS_ERR_R_OFFSET 16
#define LENS_FS_ERR_R_BITS 15
#define LENS_FS_ERR_R_MASK (((1 << 15) - 1) << 16)
/* NLSC_CURVE_R_P0_P1 0x0018 */
#define SHADE_R_P0_OFFSET 0
#define SHADE_R_P0_BITS 10
#define SHADE_R_P0_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_P1_OFFSET 16
#define SHADE_R_P1_BITS 10
#define SHADE_R_P1_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P2_P3 0x001C */
#define SHADE_R_P2_OFFSET 0
#define SHADE_R_P2_BITS 10
#define SHADE_R_P2_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_P3_OFFSET 16
#define SHADE_R_P3_BITS 10
#define SHADE_R_P3_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P4_P5 0x0020 */
#define SHADE_R_P4_OFFSET 0
#define SHADE_R_P4_BITS 10
#define SHADE_R_P4_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_P5_OFFSET 16
#define SHADE_R_P5_BITS 10
#define SHADE_R_P5_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P6_P7 0x0024 */
#define SHADE_R_P6_OFFSET 0
#define SHADE_R_P6_BITS 10
#define SHADE_R_P6_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_P7_OFFSET 16
#define SHADE_R_P7_BITS 10
#define SHADE_R_P7_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P8_P9 0x0028 */
#define SHADE_R_P8_OFFSET 0
#define SHADE_R_P8_BITS 10
#define SHADE_R_P8_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_P9_OFFSET 16
#define SHADE_R_P9_BITS 10
#define SHADE_R_P9_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P10_P11 0x002C */
#define SHADE_R_PA_OFFSET 0
#define SHADE_R_PA_BITS 10
#define SHADE_R_PA_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_PB_OFFSET 16
#define SHADE_R_PB_BITS 10
#define SHADE_R_PB_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P12_P13 0x0030 */
#define SHADE_R_PC_OFFSET 0
#define SHADE_R_PC_BITS 10
#define SHADE_R_PC_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_PD_OFFSET 16
#define SHADE_R_PD_BITS 10
#define SHADE_R_PD_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P14_P15 0x0034 */
#define SHADE_R_PE_OFFSET 0
#define SHADE_R_PE_BITS 10
#define SHADE_R_PE_MASK (((1 << 10) - 1) << 0)
#define SHADE_R_PF_OFFSET 16
#define SHADE_R_PF_BITS 10
#define SHADE_R_PF_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_R_P16_P17 0x0038 */
#define SHADE_R_PG_OFFSET 0
#define SHADE_R_PG_BITS 11
#define SHADE_R_PG_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PH_OFFSET 16
#define SHADE_R_PH_BITS 11
#define SHADE_R_PH_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P18_P19 0x003C */
#define SHADE_R_PI_OFFSET 0
#define SHADE_R_PI_BITS 11
#define SHADE_R_PI_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PJ_OFFSET 16
#define SHADE_R_PJ_BITS 11
#define SHADE_R_PJ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P20_P21 0x0040 */
#define SHADE_R_PK_OFFSET 0
#define SHADE_R_PK_BITS 11
#define SHADE_R_PK_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PL_OFFSET 16
#define SHADE_R_PL_BITS 11
#define SHADE_R_PL_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P22_P23 0x0044 */
#define SHADE_R_PM_OFFSET 0
#define SHADE_R_PM_BITS 11
#define SHADE_R_PM_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PN_OFFSET 16
#define SHADE_R_PN_BITS 11
#define SHADE_R_PN_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P24_P25 0x0048 */
#define SHADE_R_PP_OFFSET 0
#define SHADE_R_PP_BITS 11
#define SHADE_R_PP_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PQ_OFFSET 16
#define SHADE_R_PQ_BITS 11
#define SHADE_R_PQ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P26_P27 0x004C */
#define SHADE_R_PR_OFFSET 0
#define SHADE_R_PR_BITS 11
#define SHADE_R_PR_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PS_OFFSET 16
#define SHADE_R_PS_BITS 11
#define SHADE_R_PS_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P28_P29 0x0050 */
#define SHADE_R_PT_OFFSET 0
#define SHADE_R_PT_BITS 11
#define SHADE_R_PT_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PU_OFFSET 16
#define SHADE_R_PU_BITS 11
#define SHADE_R_PU_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_R_P30_P31 0x0054 */
#define SHADE_R_PV_OFFSET 0
#define SHADE_R_PV_BITS 11
#define SHADE_R_PV_MASK (((1 << 11) - 1) << 0)
#define SHADE_R_PW_OFFSET 16
#define SHADE_R_PW_BITS 11
#define SHADE_R_PW_MASK (((1 << 11) - 1) << 16)
/* NLSC_CENTER_G 0x0058 */
#define LENS_CENTER_X_G_OFFSET 0
#define LENS_CENTER_X_G_BITS 12
#define LENS_CENTER_X_G_MASK (((1 << 12) - 1) << 0)
#define LENS_CENTER_Y_G_OFFSET 16
#define LENS_CENTER_Y_G_BITS 12
#define LENS_CENTER_Y_G_MASK (((1 << 12) - 1) << 16)
/* NLSC_DISTANCE_CFG_G 0x005C */
#define LENS_FS_DST_G_OFFSET 0
#define LENS_FS_DST_G_BITS 12
#define LENS_FS_DST_G_MASK (((1 << 12) - 1) << 0)
#define LENS_FS_ERR_G_OFFSET 16
#define LENS_FS_ERR_G_BITS 15
#define LENS_FS_ERR_G_MASK (((1 << 15) - 1) << 16)
/* NLSC_CURVE_G_P0_P1 0x0060 */
#define SHADE_G_P0_OFFSET 0
#define SHADE_G_P0_BITS 10
#define SHADE_G_P0_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_P1_OFFSET 16
#define SHADE_G_P1_BITS 10
#define SHADE_G_P1_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P2_P3 0x0064 */
#define SHADE_G_P2_OFFSET 0
#define SHADE_G_P2_BITS 10
#define SHADE_G_P2_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_P3_OFFSET 16
#define SHADE_G_P3_BITS 10
#define SHADE_G_P3_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P4_P5 0x0068 */
#define SHADE_G_P4_OFFSET 0
#define SHADE_G_P4_BITS 10
#define SHADE_G_P4_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_P5_OFFSET 16
#define SHADE_G_P5_BITS 10
#define SHADE_G_P5_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P6_P7 0x006C */
#define SHADE_G_P6_OFFSET 0
#define SHADE_G_P6_BITS 10
#define SHADE_G_P6_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_P7_OFFSET 16
#define SHADE_G_P7_BITS 10
#define SHADE_G_P7_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P8_P9 0x0070 */
#define SHADE_G_P8_OFFSET 0
#define SHADE_G_P8_BITS 10
#define SHADE_G_P8_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_P9_OFFSET 16
#define SHADE_G_P9_BITS 10
#define SHADE_G_P9_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P10_P11 0x0074 */
#define SHADE_G_PA_OFFSET 0
#define SHADE_G_PA_BITS 10
#define SHADE_G_PA_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_PB_OFFSET 16
#define SHADE_G_PB_BITS 10
#define SHADE_G_PB_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P12_P13 0x0078 */
#define SHADE_G_PC_OFFSET 0
#define SHADE_G_PC_BITS 10
#define SHADE_G_PC_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_PD_OFFSET 16
#define SHADE_G_PD_BITS 10
#define SHADE_G_PD_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P14_P15 0x007C */
#define SHADE_G_PE_OFFSET 0
#define SHADE_G_PE_BITS 10
#define SHADE_G_PE_MASK (((1 << 10) - 1) << 0)
#define SHADE_G_PF_OFFSET 16
#define SHADE_G_PF_BITS 10
#define SHADE_G_PF_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_G_P16_P17 0x0080 */
#define SHADE_G_PG_OFFSET 0
#define SHADE_G_PG_BITS 11
#define SHADE_G_PG_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PH_OFFSET 16
#define SHADE_G_PH_BITS 11
#define SHADE_G_PH_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P18_P19 0x0084 */
#define SHADE_G_PI_OFFSET 0
#define SHADE_G_PI_BITS 11
#define SHADE_G_PI_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PJ_OFFSET 16
#define SHADE_G_PJ_BITS 11
#define SHADE_G_PJ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P20_P21 0x0088 */
#define SHADE_G_PK_OFFSET 0
#define SHADE_G_PK_BITS 11
#define SHADE_G_PK_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PL_OFFSET 16
#define SHADE_G_PL_BITS 11
#define SHADE_G_PL_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P22_P23 0x008C */
#define SHADE_G_PM_OFFSET 0
#define SHADE_G_PM_BITS 11
#define SHADE_G_PM_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PN_OFFSET 16
#define SHADE_G_PN_BITS 11
#define SHADE_G_PN_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P24_P25 0x0090 */
#define SHADE_G_PP_OFFSET 0
#define SHADE_G_PP_BITS 11
#define SHADE_G_PP_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PQ_OFFSET 16
#define SHADE_G_PQ_BITS 11
#define SHADE_G_PQ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P26_P27 0x0094 */
#define SHADE_G_PR_OFFSET 0
#define SHADE_G_PR_BITS 11
#define SHADE_G_PR_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PS_OFFSET 16
#define SHADE_G_PS_BITS 11
#define SHADE_G_PS_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P28_P29 0x0098 */
#define SHADE_G_PT_OFFSET 0
#define SHADE_G_PT_BITS 11
#define SHADE_G_PT_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PU_OFFSET 16
#define SHADE_G_PU_BITS 11
#define SHADE_G_PU_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_G_P30_P31 0x009C */
#define SHADE_G_PV_OFFSET 0
#define SHADE_G_PV_BITS 11
#define SHADE_G_PV_MASK (((1 << 11) - 1) << 0)
#define SHADE_G_PW_OFFSET 16
#define SHADE_G_PW_BITS 11
#define SHADE_G_PW_MASK (((1 << 11) - 1) << 16)
/* NLSC_CENTER_B 0x00A0 */
#define LENS_CENTER_X_B_OFFSET 0
#define LENS_CENTER_X_B_BITS 12
#define LENS_CENTER_X_B_MASK (((1 << 12) - 1) << 0)
#define LENS_CENTER_Y_B_OFFSET 16
#define LENS_CENTER_Y_B_BITS 12
#define LENS_CENTER_Y_B_MASK (((1 << 12) - 1) << 16)
/* NLSC_DISTANCE_CFG_B 0x00A4 */
#define LENS_FS_DST_B_OFFSET 0
#define LENS_FS_DST_B_BITS 12
#define LENS_FS_DST_B_MASK (((1 << 12) - 1) << 0)
#define LENS_FS_ERR_B_OFFSET 16
#define LENS_FS_ERR_B_BITS 15
#define LENS_FS_ERR_B_MASK (((1 << 15) - 1) << 16)
/* NLSC_CURVE_B_P0_P1 0x00A8 */
#define SHADE_B_P0_OFFSET 0
#define SHADE_B_P0_BITS 10
#define SHADE_B_P0_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_P1_OFFSET 16
#define SHADE_B_P1_BITS 10
#define SHADE_B_P1_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P2_P3 0x00AC */
#define SHADE_B_P2_OFFSET 0
#define SHADE_B_P2_BITS 10
#define SHADE_B_P2_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_P3_OFFSET 16
#define SHADE_B_P3_BITS 10
#define SHADE_B_P3_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P4_P5 0x00B0 */
#define SHADE_B_P4_OFFSET 0
#define SHADE_B_P4_BITS 10
#define SHADE_B_P4_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_P5_OFFSET 16
#define SHADE_B_P5_BITS 10
#define SHADE_B_P5_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P6_P7 0x00B4 */
#define SHADE_B_P6_OFFSET 0
#define SHADE_B_P6_BITS 10
#define SHADE_B_P6_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_P7_OFFSET 16
#define SHADE_B_P7_BITS 10
#define SHADE_B_P7_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P8_P9 0x00B8 */
#define SHADE_B_P8_OFFSET 0
#define SHADE_B_P8_BITS 10
#define SHADE_B_P8_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_P9_OFFSET 16
#define SHADE_B_P9_BITS 10
#define SHADE_B_P9_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P10_P11 0x00BC */
#define SHADE_B_PA_OFFSET 0
#define SHADE_B_PA_BITS 10
#define SHADE_B_PA_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_PB_OFFSET 16
#define SHADE_B_PB_BITS 10
#define SHADE_B_PB_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P12_P13 0x00C0 */
#define SHADE_B_PC_OFFSET 0
#define SHADE_B_PC_BITS 10
#define SHADE_B_PC_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_PD_OFFSET 16
#define SHADE_B_PD_BITS 10
#define SHADE_B_PD_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P14_P15 0x00C4 */
#define SHADE_B_PE_OFFSET 0
#define SHADE_B_PE_BITS 10
#define SHADE_B_PE_MASK (((1 << 10) - 1) << 0)
#define SHADE_B_PF_OFFSET 16
#define SHADE_B_PF_BITS 10
#define SHADE_B_PF_MASK (((1 << 10) - 1) << 16)
/* NLSC_CURVE_B_P16_P17 0x00C8 */
#define SHADE_B_PG_OFFSET 0
#define SHADE_B_PG_BITS 11
#define SHADE_B_PG_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PH_OFFSET 16
#define SHADE_B_PH_BITS 11
#define SHADE_B_PH_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P18_P19 0x00CC */
#define SHADE_B_PI_OFFSET 0
#define SHADE_B_PI_BITS 11
#define SHADE_B_PI_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PJ_OFFSET 16
#define SHADE_B_PJ_BITS 11
#define SHADE_B_PJ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P20_P21 0x00D0 */
#define SHADE_B_PK_OFFSET 0
#define SHADE_B_PK_BITS 11
#define SHADE_B_PK_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PL_OFFSET 16
#define SHADE_B_PL_BITS 11
#define SHADE_B_PL_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P22_P23 0x00D4 */
#define SHADE_B_PM_OFFSET 0
#define SHADE_B_PM_BITS 11
#define SHADE_B_PM_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PN_OFFSET 16
#define SHADE_B_PN_BITS 11
#define SHADE_B_PN_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P24_P25 0x00D8 */
#define SHADE_B_PP_OFFSET 0
#define SHADE_B_PP_BITS 11
#define SHADE_B_PP_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PQ_OFFSET 16
#define SHADE_B_PQ_BITS 11
#define SHADE_B_PQ_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P26_P27 0x00DC */
#define SHADE_B_PR_OFFSET 0
#define SHADE_B_PR_BITS 11
#define SHADE_B_PR_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PS_OFFSET 16
#define SHADE_B_PS_BITS 11
#define SHADE_B_PS_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P28_P29 0x00E0 */
#define SHADE_B_PT_OFFSET 0
#define SHADE_B_PT_BITS 11
#define SHADE_B_PT_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PU_OFFSET 16
#define SHADE_B_PU_BITS 11
#define SHADE_B_PU_MASK (((1 << 11) - 1) << 16)
/* NLSC_CURVE_B_P30_P31 0x00E4 */
#define SHADE_B_PV_OFFSET 0
#define SHADE_B_PV_BITS 11
#define SHADE_B_PV_MASK (((1 << 11) - 1) << 0)
#define SHADE_B_PW_OFFSET 16
#define SHADE_B_PW_BITS 11
#define SHADE_B_PW_MASK (((1 << 11) - 1) << 16)
/* NLSC_OVEREXP_RATIO 0x00E8 */
#define OVEREXP_RATIO_OFFSET 0
#define OVEREXP_RATIO_BITS 13
#define OVEREXP_RATIO_MASK (((1 << 13) - 1) << 0)
/* NLSC_OVEREXP_THD 0x00EC */
#define OVEREXP_TH0_OFFSET 0
#define OVEREXP_TH0_BITS 12
#define OVEREXP_TH0_MASK (((1 << 12) - 1) << 0)
#define OVEREXP_TH1_OFFSET 16
#define OVEREXP_TH1_BITS 12
#define OVEREXP_TH1_MASK (((1 << 12) - 1) << 16)
/* NLSC_CENTER_RGB_CTRL 0x00F0 */
#define CENTER_TRIG_OFFSET 0
#define CENTER_TRIG_BITS 1
#define CENTER_TRIG_MASK (((1 << 1) - 1) << 0)

#endif /* _ISP_REG_NLSC_H_INC_ */

