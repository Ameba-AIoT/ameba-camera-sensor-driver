#ifndef _ISP_REG_TONEMAPPING_H_INC_
#define _ISP_REG_TONEMAPPING_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define TM_CTRL (TM_REG_BASE + 0x0000)
#define TM_EXP_RATIO_INV (TM_REG_BASE + 0x0004)
#define TM_FS_LE_DIFF_THD_0_0 (TM_REG_BASE + 0x0020)
#define TM_FS_LE_DIFF_THD_0_1 (TM_REG_BASE + 0x0024)
#define TM_FS_LE_DIFF_THD_0_2 (TM_REG_BASE + 0x0028)
#define TM_FS_LE_DIFF_THD_0_3 (TM_REG_BASE + 0x002C)
#define TM_FS_LE_DIFF_THD_0_4 (TM_REG_BASE + 0x0030)
#define TM_FS_LE_DIFF_THD_0_5 (TM_REG_BASE + 0x0034)
#define TM_FS_LE_DIFF_THD_0_6 (TM_REG_BASE + 0x0038)
#define TM_FS_LE_DIFF_THD_0_7 (TM_REG_BASE + 0x003C)
#define TM_FS_LE_DIFF_THD_0_8 (TM_REG_BASE + 0x0040)
#define TM_FS_LE_DIFF_THD_0_9 (TM_REG_BASE + 0x0044)
#define TM_FS_LE_DIFF_THD_0_10 (TM_REG_BASE + 0x0048)
#define TM_FS_SE_DIFF_THD_0_0 (TM_REG_BASE + 0x0050)
#define TM_FS_SE_DIFF_THD_0_1 (TM_REG_BASE + 0x0054)
#define TM_FS_SE_DIFF_THD_0_2 (TM_REG_BASE + 0x0058)
#define TM_FS_SE_DIFF_THD_0_3 (TM_REG_BASE + 0x005C)
#define TM_FS_SE_DIFF_THD_0_4 (TM_REG_BASE + 0x0060)
#define TM_FS_SE_DIFF_THD_0_5 (TM_REG_BASE + 0x0064)
#define TM_FS_SE_DIFF_THD_0_6 (TM_REG_BASE + 0x0068)
#define TM_FS_SE_DIFF_THD_0_7 (TM_REG_BASE + 0x006C)
#define TM_FS_SE_DIFF_THD_0_8 (TM_REG_BASE + 0x0070)
#define TM_FS_SE_DIFF_THD_0_9 (TM_REG_BASE + 0x0074)
#define TM_FS_SE_DIFF_THD_0_10 (TM_REG_BASE + 0x0078)
#define TM_CURVE_0_0 (TM_REG_BASE + 0x0100)
#define TM_CURVE_0_1 (TM_REG_BASE + 0x0104)
#define TM_CURVE_1_0 (TM_REG_BASE + 0x0110)
#define TM_CURVE_1_1 (TM_REG_BASE + 0x0114)
#define TM_CURVE_1_2 (TM_REG_BASE + 0x0118)
#define TM_CURVE_2_0 (TM_REG_BASE + 0x0120)
#define TM_CURVE_2_1 (TM_REG_BASE + 0x0124)
#define TM_CURVE_2_2 (TM_REG_BASE + 0x0128)
#define TM_CURVE_2_3 (TM_REG_BASE + 0x012C)
#define TM_CURVE_3_0 (TM_REG_BASE + 0x0130)
#define TM_CURVE_3_1 (TM_REG_BASE + 0x0134)
#define TM_CURVE_3_2 (TM_REG_BASE + 0x0138)
#define TM_CURVE_3_3 (TM_REG_BASE + 0x013C)
#define TM_CURVE_3_4 (TM_REG_BASE + 0x0140)
#define TM_CURVE_4_0 (TM_REG_BASE + 0x0150)
#define TM_CURVE_4_1 (TM_REG_BASE + 0x0154)
#define TM_CURVE_4_2 (TM_REG_BASE + 0x0158)
#define TM_CURVE_4_3 (TM_REG_BASE + 0x015C)
#define TM_CURVE_4_4 (TM_REG_BASE + 0x0160)
#define TM_CURVE_4_5 (TM_REG_BASE + 0x0164)
#define TM_CURVE_5_0 (TM_REG_BASE + 0x0170)
#define TM_CURVE_5_1 (TM_REG_BASE + 0x0174)
#define TM_CURVE_5_2 (TM_REG_BASE + 0x0178)
#define TM_CURVE_5_3 (TM_REG_BASE + 0x017C)
#define TM_CURVE_5_4 (TM_REG_BASE + 0x0180)
#define TM_CURVE_5_5 (TM_REG_BASE + 0x0184)
#define TM_CURVE_5_6 (TM_REG_BASE + 0x0188)
#define TM_CURVE_6_0 (TM_REG_BASE + 0x0190)
#define TM_CURVE_6_1 (TM_REG_BASE + 0x0194)
#define TM_CURVE_6_2 (TM_REG_BASE + 0x0198)
#define TM_CURVE_6_3 (TM_REG_BASE + 0x019C)
#define TM_CURVE_6_4 (TM_REG_BASE + 0x01A0)
#define TM_CURVE_6_5 (TM_REG_BASE + 0x01A4)
#define TM_CURVE_6_6 (TM_REG_BASE + 0x01A8)
#define TM_CURVE_6_7 (TM_REG_BASE + 0x01AC)
#define TM_REG_LOAD (TM_REG_BASE + 0x0200)

/* TM_CTRL 0x0000 */
#define TM_EN_OFFSET 2
#define TM_EN_BITS 1
#define TM_EN_MASK (((1 << 1) - 1) << 2)
/* TM_EXP_RATIO_INV 0x0004 */
#define TM_EXP_RATIO_INV_OFFSET 0
#define TM_EXP_RATIO_INV_BITS 12
#define TM_EXP_RATIO_INV_MASK (((1 << 12) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_0 0x0020 */
#define TM_FS_LE_DIFF_THD_0_0_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_0_BITS 8
#define TM_FS_LE_DIFF_THD_0_0_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_1 0x0024 */
#define TM_FS_LE_DIFF_THD_0_1_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_1_BITS 8
#define TM_FS_LE_DIFF_THD_0_1_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_2 0x0028 */
#define TM_FS_LE_DIFF_THD_0_2_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_2_BITS 8
#define TM_FS_LE_DIFF_THD_0_2_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_3 0x002C */
#define TM_FS_LE_DIFF_THD_0_3_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_3_BITS 8
#define TM_FS_LE_DIFF_THD_0_3_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_4 0x0030 */
#define TM_FS_LE_DIFF_THD_0_4_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_4_BITS 8
#define TM_FS_LE_DIFF_THD_0_4_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_5 0x0034 */
#define TM_FS_LE_DIFF_THD_0_5_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_5_BITS 8
#define TM_FS_LE_DIFF_THD_0_5_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_6 0x0038 */
#define TM_FS_LE_DIFF_THD_0_6_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_6_BITS 8
#define TM_FS_LE_DIFF_THD_0_6_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_7 0x003C */
#define TM_FS_LE_DIFF_THD_0_7_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_7_BITS 8
#define TM_FS_LE_DIFF_THD_0_7_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_8 0x0040 */
#define TM_FS_LE_DIFF_THD_0_8_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_8_BITS 8
#define TM_FS_LE_DIFF_THD_0_8_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_9 0x0044 */
#define TM_FS_LE_DIFF_THD_0_9_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_9_BITS 8
#define TM_FS_LE_DIFF_THD_0_9_MASK (((1 << 8) - 1) << 0)
/* TM_FS_LE_DIFF_THD_0_10 0x0048 */
#define TM_FS_LE_DIFF_THD_0_10_OFFSET 0
#define TM_FS_LE_DIFF_THD_0_10_BITS 8
#define TM_FS_LE_DIFF_THD_0_10_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_0 0x0050 */
#define TM_FS_SE_DIFF_THD_0_0_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_0_BITS 8
#define TM_FS_SE_DIFF_THD_0_0_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_1 0x0054 */
#define TM_FS_SE_DIFF_THD_0_1_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_1_BITS 8
#define TM_FS_SE_DIFF_THD_0_1_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_2 0x0058 */
#define TM_FS_SE_DIFF_THD_0_2_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_2_BITS 8
#define TM_FS_SE_DIFF_THD_0_2_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_3 0x005C */
#define TM_FS_SE_DIFF_THD_0_3_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_3_BITS 8
#define TM_FS_SE_DIFF_THD_0_3_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_4 0x0060 */
#define TM_FS_SE_DIFF_THD_0_4_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_4_BITS 8
#define TM_FS_SE_DIFF_THD_0_4_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_5 0x0064 */
#define TM_FS_SE_DIFF_THD_0_5_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_5_BITS 8
#define TM_FS_SE_DIFF_THD_0_5_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_6 0x0068 */
#define TM_FS_SE_DIFF_THD_0_6_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_6_BITS 8
#define TM_FS_SE_DIFF_THD_0_6_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_7 0x006C */
#define TM_FS_SE_DIFF_THD_0_7_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_7_BITS 8
#define TM_FS_SE_DIFF_THD_0_7_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_8 0x0070 */
#define TM_FS_SE_DIFF_THD_0_8_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_8_BITS 8
#define TM_FS_SE_DIFF_THD_0_8_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_9 0x0074 */
#define TM_FS_SE_DIFF_THD_0_9_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_9_BITS 8
#define TM_FS_SE_DIFF_THD_0_9_MASK (((1 << 8) - 1) << 0)
/* TM_FS_SE_DIFF_THD_0_10 0x0078 */
#define TM_FS_SE_DIFF_THD_0_10_OFFSET 0
#define TM_FS_SE_DIFF_THD_0_10_BITS 8
#define TM_FS_SE_DIFF_THD_0_10_MASK (((1 << 8) - 1) << 0)

/* TM_CURVE_0_0  0x0100 */
#define TM_CURVE_0_0_OFFSET 0
#define TM_CURVE_0_0_BITS 14
#define TM_CURVE_0_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_0_1  0x0104 */
#define TM_CURVE_0_1_OFFSET 0
#define TM_CURVE_0_1_BITS 14
#define TM_CURVE_0_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_1_0  0x0110 */
#define TM_CURVE_1_0_OFFSET 0
#define TM_CURVE_1_0_BITS 14
#define TM_CURVE_1_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_1_1  0x0114 */
#define TM_CURVE_1_1_OFFSET 0
#define TM_CURVE_1_1_BITS 14
#define TM_CURVE_1_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_1_2  0x0118 */
#define TM_CURVE_1_2_OFFSET 0
#define TM_CURVE_1_2_BITS 14
#define TM_CURVE_1_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_2_0  0x0120 */
#define TM_CURVE_2_0_OFFSET 0
#define TM_CURVE_2_0_BITS 14
#define TM_CURVE_2_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_2_1  0x0124 */
#define TM_CURVE_2_1_OFFSET 0
#define TM_CURVE_2_1_BITS 14
#define TM_CURVE_2_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_2_2  0x0128 */
#define TM_CURVE_2_2_OFFSET 0
#define TM_CURVE_2_2_BITS 14
#define TM_CURVE_2_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_2_3  0x012C */
#define TM_CURVE_2_3_OFFSET 0
#define TM_CURVE_2_3_BITS 14
#define TM_CURVE_2_3_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_3_0  0x0130 */
#define TM_CURVE_3_0_OFFSET 0
#define TM_CURVE_3_0_BITS 14
#define TM_CURVE_3_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_3_1  0x0134 */
#define TM_CURVE_3_1_OFFSET 0
#define TM_CURVE_3_1_BITS 14
#define TM_CURVE_3_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_3_2  0x0138 */
#define TM_CURVE_3_2_OFFSET 0
#define TM_CURVE_3_2_BITS 14
#define TM_CURVE_3_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_3_3  0x013C */
#define TM_CURVE_3_3_OFFSET 0
#define TM_CURVE_3_3_BITS 14
#define TM_CURVE_3_3_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_3_4  0x0140 */
#define TM_CURVE_3_4_OFFSET 0
#define TM_CURVE_3_4_BITS 14
#define TM_CURVE_3_4_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_0  0x0150 */
#define TM_CURVE_4_0_OFFSET 0
#define TM_CURVE_4_0_BITS 14
#define TM_CURVE_4_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_1  0x0154 */
#define TM_CURVE_4_1_OFFSET 0
#define TM_CURVE_4_1_BITS 14
#define TM_CURVE_4_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_2  0x0158 */
#define TM_CURVE_4_2_OFFSET 0
#define TM_CURVE_4_2_BITS 14
#define TM_CURVE_4_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_3  0x015C */
#define TM_CURVE_4_3_OFFSET 0
#define TM_CURVE_4_3_BITS 14
#define TM_CURVE_4_3_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_4  0x0160 */
#define TM_CURVE_4_4_OFFSET 0
#define TM_CURVE_4_4_BITS 14
#define TM_CURVE_4_4_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_4_5  0x0164 */
#define TM_CURVE_4_5_OFFSET 0
#define TM_CURVE_4_5_BITS 14
#define TM_CURVE_4_5_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_0  0x0170 */
#define TM_CURVE_5_0_OFFSET 0
#define TM_CURVE_5_0_BITS 14
#define TM_CURVE_5_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_1  0x0174 */
#define TM_CURVE_5_1_OFFSET 0
#define TM_CURVE_5_1_BITS 14
#define TM_CURVE_5_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_2  0x0178 */
#define TM_CURVE_5_2_OFFSET 0
#define TM_CURVE_5_2_BITS 14
#define TM_CURVE_5_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_3  0x017C */
#define TM_CURVE_5_3_OFFSET 0
#define TM_CURVE_5_3_BITS 14
#define TM_CURVE_5_3_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_4  0x0180 */
#define TM_CURVE_5_4_OFFSET 0
#define TM_CURVE_5_4_BITS 14
#define TM_CURVE_5_4_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_5  0x0184 */
#define TM_CURVE_5_5_OFFSET 0
#define TM_CURVE_5_5_BITS 14
#define TM_CURVE_5_5_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_5_6  0x0188 */
#define TM_CURVE_5_6_OFFSET 0
#define TM_CURVE_5_6_BITS 14
#define TM_CURVE_5_6_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_0  0x0190 */
#define TM_CURVE_6_0_OFFSET 0
#define TM_CURVE_6_0_BITS 14
#define TM_CURVE_6_0_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_1  0x0194 */
#define TM_CURVE_6_1_OFFSET 0
#define TM_CURVE_6_1_BITS 14
#define TM_CURVE_6_1_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_2  0x0198 */
#define TM_CURVE_6_2_OFFSET 0
#define TM_CURVE_6_2_BITS 14
#define TM_CURVE_6_2_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_3  0x019C */
#define TM_CURVE_6_3_OFFSET 0
#define TM_CURVE_6_3_BITS 14
#define TM_CURVE_6_3_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_4  0x01A0 */
#define TM_CURVE_6_4_OFFSET 0
#define TM_CURVE_6_4_BITS 14
#define TM_CURVE_6_4_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_5  0x01A4 */
#define TM_CURVE_6_5_OFFSET 0
#define TM_CURVE_6_5_BITS 14
#define TM_CURVE_6_5_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_6  0x01A8 */
#define TM_CURVE_6_6_OFFSET 0
#define TM_CURVE_6_6_BITS 14
#define TM_CURVE_6_6_MASK (((1 << 14) - 1) << 0)
/* TM_CURVE_6_7  0x01AC */
#define TM_CURVE_6_7_OFFSET 0
#define TM_CURVE_6_7_BITS 14
#define TM_CURVE_6_7_MASK (((1 << 14) - 1) << 0)
/* TM_REG_LOAD 0x0200 */
#define TM_REG_LOAD_OFFSET 0
#define TM_REG_LOAD_BITS 1
#define TM_REG_LOAD_MASK (((1 << 1) - 1) << 0)

#endif /* _ISP_REG_TONEMAPPING_H_INC_ */

