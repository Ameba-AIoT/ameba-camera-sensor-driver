#ifndef _ISP_REG_CCM_H_INC_
#define _ISP_REG_CCM_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define CCM_SYNC (CCM_REG_BASE + 0x0000)
#define CCM_R_AF_R (CCM_REG_BASE + 0x0020)
#define CCM_G_AF_R (CCM_REG_BASE + 0x0024)
#define CCM_B_AF_R (CCM_REG_BASE + 0x0028)
#define CCM_R_AF_G (CCM_REG_BASE + 0x002C)
#define CCM_G_AF_G (CCM_REG_BASE + 0x0030)
#define CCM_B_AF_G (CCM_REG_BASE + 0x0034)
#define CCM_R_AF_B (CCM_REG_BASE + 0x0038)
#define CCM_G_AF_B (CCM_REG_BASE + 0x003C)
#define CCM_B_AF_B (CCM_REG_BASE + 0x0040)
#define CCM_R_AF_R_SYNC (CCM_REG_BASE + 0x0050)
#define CCM_G_AF_R_SYNC (CCM_REG_BASE + 0x0054)
#define CCM_B_AF_R_SYNC (CCM_REG_BASE + 0x0058)
#define CCM_R_AF_G_SYNC (CCM_REG_BASE + 0x005C)
#define CCM_G_AF_G_SYNC (CCM_REG_BASE + 0x0060)
#define CCM_B_AF_G_SYNC (CCM_REG_BASE + 0x0064)
#define CCM_R_AF_B_SYNC (CCM_REG_BASE + 0x0068)
#define CCM_G_AF_B_SYNC (CCM_REG_BASE + 0x006C)
#define CCM_B_AF_B_SYNC (CCM_REG_BASE + 0x0070)
#define PFR_CTRL (CCM_REG_BASE + 0x0074)
#define PFR_EDGE_OFFSET (CCM_REG_BASE + 0x0078)
#define PFR_SAT_OFFSET (CCM_REG_BASE + 0x007C)
#define PFR_SAT_THD (CCM_REG_BASE + 0x0080)
#define PFR_GRAY_RATE (CCM_REG_BASE + 0x0084)
#define PFR_FLITER_MODE (CCM_REG_BASE + 0x0088)
#define PFR_MEAN_COEF0 (CCM_REG_BASE + 0x008C)
#define PFR_MEAN_COEF1 (CCM_REG_BASE + 0x0090)
#define PFR_Y_COEF (CCM_REG_BASE + 0x0094)
#define PFR_Q_CURVE0 (CCM_REG_BASE + 0x0098)
#define PFR_Q_CURVE1 (CCM_REG_BASE + 0x009C)
#define PFR_Q_CURVE2 (CCM_REG_BASE + 0x00A0)
#define PFR_Q_CURVE3 (CCM_REG_BASE + 0x00A4)
#define PFR_Q_CURVE4 (CCM_REG_BASE + 0x00A8)
#define PFR_EDGE_TH_ARR0 (CCM_REG_BASE + 0x00AC)
#define PFR_EDGE_TH_ARR1 (CCM_REG_BASE + 0x00B0)
#define PFR_EDGE_TH_ARR2 (CCM_REG_BASE + 0x00B4)
#define PFR_EDGE_TH_ARR3 (CCM_REG_BASE + 0x00B8)
#define PFR_EDGE_TH_ARR4 (CCM_REG_BASE + 0x00BC)

/* CCM_SYNC 0x0000 */
#define CCM_REG_LOAD_OFFSET 0
#define CCM_REG_LOAD_BITS 1
#define CCM_REG_LOAD_MASK (((1 << 1) - 1) << 0)
/* CCM_R_AF_R 0x0020 */
#define R_AFFECT_R_OFFSET 0
#define R_AFFECT_R_BITS 10
#define R_AFFECT_R_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_R 0x0024 */
#define G_AFFECT_R_OFFSET 0
#define G_AFFECT_R_BITS 11
#define G_AFFECT_R_MASK (((1 << 11) - 1) << 0)
/* CCM_B_AF_R 0x0028 */
#define B_AFFECT_R_OFFSET 0
#define B_AFFECT_R_BITS 10
#define B_AFFECT_R_MASK (((1 << 10) - 1) << 0)
/* CCM_R_AF_G 0x002C */
#define R_AFFECT_G_OFFSET 0
#define R_AFFECT_G_BITS 10
#define R_AFFECT_G_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_G 0x0030 */
#define G_AFFECT_G_OFFSET 0
#define G_AFFECT_G_BITS 10
#define G_AFFECT_G_MASK (((1 << 10) - 1) << 0)
/* CCM_B_AF_G 0x0034 */
#define B_AFFECT_G_OFFSET 0
#define B_AFFECT_G_BITS 10
#define B_AFFECT_G_MASK (((1 << 10) - 1) << 0)
/* CCM_R_AF_B 0x0038 */
#define R_AFFECT_B_OFFSET 0
#define R_AFFECT_B_BITS 10
#define R_AFFECT_B_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_B 0x003C */
#define G_AFFECT_B_OFFSET 0
#define G_AFFECT_B_BITS 11
#define G_AFFECT_B_MASK (((1 << 11) - 1) << 0)
/* CCM_B_AF_B 0x0040 */
#define B_AFFECT_B_OFFSET 0
#define B_AFFECT_B_BITS 10
#define B_AFFECT_B_MASK (((1 << 10) - 1) << 0)
/* CCM_R_AF_R_SYNC 0x0050 */
#define R_AFFECT_R_SYNC_OFFSET 0
#define R_AFFECT_R_SYNC_BITS 10
#define R_AFFECT_R_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_R_SYNC 0x0054 */
#define G_AFFECT_R_SYNC_OFFSET 0
#define G_AFFECT_R_SYNC_BITS 11
#define G_AFFECT_R_SYNC_MASK (((1 << 11) - 1) << 0)
/* CCM_B_AF_R_SYNC 0x0058 */
#define B_AFFECT_R_SYNC_OFFSET 0
#define B_AFFECT_R_SYNC_BITS 10
#define B_AFFECT_R_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_R_AF_G_SYNC 0x005C */
#define R_AFFECT_G_SYNC_OFFSET 0
#define R_AFFECT_G_SYNC_BITS 10
#define R_AFFECT_G_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_G_SYNC 0x0060 */
#define G_AFFECT_G_SYNC_OFFSET 0
#define G_AFFECT_G_SYNC_BITS 10
#define G_AFFECT_G_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_B_AF_G_SYNC 0x0064 */
#define B_AFFECT_G_SYNC_OFFSET 0
#define B_AFFECT_G_SYNC_BITS 10
#define B_AFFECT_G_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_R_AF_B_SYNC 0x0068 */
#define R_AFFECT_B_SYNC_OFFSET 0
#define R_AFFECT_B_SYNC_BITS 10
#define R_AFFECT_B_SYNC_MASK (((1 << 10) - 1) << 0)
/* CCM_G_AF_B_SYNC 0x006C */
#define G_AFFECT_B_SYNC_OFFSET 0
#define G_AFFECT_B_SYNC_BITS 11
#define G_AFFECT_B_SYNC_MASK (((1 << 11) - 1) << 0)
/* CCM_B_AF_B_SYNC 0x0070 */
#define B_AFFECT_B_SYNC_OFFSET 0
#define B_AFFECT_B_SYNC_BITS 10
#define B_AFFECT_B_SYNC_MASK (((1 << 10) - 1) << 0)
/* PFR_CTRL 0x0074 */
#define PROGRESSIVE_EN_OFFSET 0
#define PROGRESSIVE_EN_BITS 1
#define PROGRESSIVE_EN_MASK (((1 << 1) - 1) << 0)
#define BLEND_GRAY_EN_OFFSET 1
#define BLEND_GRAY_EN_BITS 1
#define BLEND_GRAY_EN_MASK (((1 << 1) - 1) << 1)
#define BLEND_ORG_EN_OFFSET 2
#define BLEND_ORG_EN_BITS 1
#define BLEND_ORG_EN_MASK (((1 << 1) - 1) << 2)
#define DE_PURPLE_EN_OFFSET 3
#define DE_PURPLE_EN_BITS 1
#define DE_PURPLE_EN_MASK (((1 << 1) - 1) << 3)
#define EDGE_MAP_DEBUG_EN_OFFSET 4
#define EDGE_MAP_DEBUG_EN_BITS 1
#define EDGE_MAP_DEBUG_EN_MASK (((1 << 1) - 1) << 4)
#define SAT_DEBUG_EN_OFFSET 5
#define SAT_DEBUG_EN_BITS 1
#define SAT_DEBUG_EN_MASK (((1 << 1) - 1) << 5)
#define RATE_DEBUG_EN_OFFSET 6
#define RATE_DEBUG_EN_BITS 1
#define RATE_DEBUG_EN_MASK (((1 << 1) - 1) << 6)
#define YMAX_DEBUG_EN_OFFSET 7
#define YMAX_DEBUG_EN_BITS 1
#define YMAX_DEBUG_EN_MASK (((1 << 1) - 1) << 7)
/* PFR_EDGE_OFFSET 0x0078 */
#define EDGE_OFFSET_OFFSET 0
#define EDGE_OFFSET_BITS 8
#define EDGE_OFFSET_MASK (((1 << 8) - 1) << 0)
/* PFR_SAT_OFFSET 0x007C */
#define SAT_THD1_OFFSET_OFFSET 0
#define SAT_THD1_OFFSET_BITS 12
#define SAT_THD1_OFFSET_MASK (((1 << 12) - 1) << 0)
#define SAT_THD_DIFF_OFFSET_OFFSET 16
#define SAT_THD_DIFF_OFFSET_BITS 12
#define SAT_THD_DIFF_OFFSET_MASK (((1 << 12) - 1) << 16)
/* PFR_SAT_THD 0x0080 */
#define SAT_THD_SLOPE_OFFSET 0
#define SAT_THD_SLOPE_BITS 19
#define SAT_THD_SLOPE_MASK (((1 << 19) - 1) << 0)
/* PFR_GRAY_RATE 0x0084 */
#define ORG_GRAY_RATE_OFFSET 0
#define ORG_GRAY_RATE_BITS 9
#define ORG_GRAY_RATE_MASK (((1 << 9) - 1) << 0)
#define BLENDING_RATE_OFFSET 16
#define BLENDING_RATE_BITS 9
#define BLENDING_RATE_MASK (((1 << 9) - 1) << 16)
/* PFR_FLITER_MODE 0x0088 */
#define FILTER_WIN_OFFSET 0
#define FILTER_WIN_BITS 2
#define FILTER_WIN_MASK (((1 << 2) - 1) << 0)
/* PFR_MEAN_COEF0 0x008C */
#define PFR_C0_OFFSET 0
#define PFR_C0_BITS 7
#define PFR_C0_MASK (((1 << 7) - 1) << 0)
#define PFR_C1_OFFSET 8
#define PFR_C1_BITS 7
#define PFR_C1_MASK (((1 << 7) - 1) << 8)
#define PFR_C2_OFFSET 16
#define PFR_C2_BITS 7
#define PFR_C2_MASK (((1 << 7) - 1) << 16)
#define PFR_C3_OFFSET 24
#define PFR_C3_BITS 7
#define PFR_C3_MASK (((1 << 7) - 1) << 24)
/* PFR_MEAN_COEF1 0x0090 */
#define PFR_C4_OFFSET 0
#define PFR_C4_BITS 7
#define PFR_C4_MASK (((1 << 7) - 1) << 0)
#define PFR_C5_OFFSET 8
#define PFR_C5_BITS 7
#define PFR_C5_MASK (((1 << 7) - 1) << 8)
#define PFR_C6_OFFSET 16
#define PFR_C6_BITS 7
#define PFR_C6_MASK (((1 << 7) - 1) << 16)
#define PFR_C7_OFFSET 24
#define PFR_C7_BITS 7
#define PFR_C7_MASK (((1 << 7) - 1) << 24)
/* PFR_Y_COEF 0x0094 */
#define Y_COEF_R_OFFSET 0
#define Y_COEF_R_BITS 5
#define Y_COEF_R_MASK (((1 << 5) - 1) << 0)
#define Y_COEF_G_OFFSET 8
#define Y_COEF_G_BITS 5
#define Y_COEF_G_MASK (((1 << 5) - 1) << 8)
#define Y_COEF_B_OFFSET 16
#define Y_COEF_B_BITS 5
#define Y_COEF_B_MASK (((1 << 5) - 1) << 16)
/* PFR_Q_CURVE0 0x0098 */
#define QCURVE_CUT_Y0_OFFSET 0
#define QCURVE_CUT_Y0_BITS 12
#define QCURVE_CUT_Y0_MASK (((1 << 12) - 1) << 0)
#define QCURVE_CUT_Y1_OFFSET 16
#define QCURVE_CUT_Y1_BITS 12
#define QCURVE_CUT_Y1_MASK (((1 << 12) - 1) << 16)
/* PFR_Q_CURVE1 0x009C */
#define QCURVE_CUT_Y2_OFFSET 0
#define QCURVE_CUT_Y2_BITS 12
#define QCURVE_CUT_Y2_MASK (((1 << 12) - 1) << 0)
#define QCURVE_CUT_Y3_OFFSET 16
#define QCURVE_CUT_Y3_BITS 12
#define QCURVE_CUT_Y3_MASK (((1 << 12) - 1) << 16)
/* PFR_Q_CURVE2 0x00A0 */
#define QCURVE_CUT_Y4_OFFSET 0
#define QCURVE_CUT_Y4_BITS 12
#define QCURVE_CUT_Y4_MASK (((1 << 12) - 1) << 0)
#define QCURVE_CUT_Y5_OFFSET 16
#define QCURVE_CUT_Y5_BITS 12
#define QCURVE_CUT_Y5_MASK (((1 << 12) - 1) << 16)
/* PFR_Q_CURVE3 0x00A4 */
#define QCURVE_CUT_Y6_OFFSET 0
#define QCURVE_CUT_Y6_BITS 12
#define QCURVE_CUT_Y6_MASK (((1 << 12) - 1) << 0)
#define QCURVE_CUT_Y7_OFFSET 16
#define QCURVE_CUT_Y7_BITS 12
#define QCURVE_CUT_Y7_MASK (((1 << 12) - 1) << 16)
/* PFR_Q_CURVE4 0x00A8 */
#define QCURVE_CUT_Y8_OFFSET 0
#define QCURVE_CUT_Y8_BITS 12
#define QCURVE_CUT_Y8_MASK (((1 << 12) - 1) << 0)
/* PFR_EDGE_TH_ARR0 0x00AC */
#define EDGE_TH_ARR0_OFFSET 0
#define EDGE_TH_ARR0_BITS 12
#define EDGE_TH_ARR0_MASK (((1 << 12) - 1) << 0)
#define EDGE_TH_ARR1_OFFSET 16
#define EDGE_TH_ARR1_BITS 12
#define EDGE_TH_ARR1_MASK (((1 << 12) - 1) << 16)
/* PFR_EDGE_TH_ARR1 0x00B0 */
#define EDGE_TH_ARR2_OFFSET 0
#define EDGE_TH_ARR2_BITS 12
#define EDGE_TH_ARR2_MASK (((1 << 12) - 1) << 0)
#define EDGE_TH_ARR3_OFFSET 16
#define EDGE_TH_ARR3_BITS 12
#define EDGE_TH_ARR3_MASK (((1 << 12) - 1) << 16)
/* PFR_EDGE_TH_ARR2 0x00B4 */
#define EDGE_TH_ARR4_OFFSET 0
#define EDGE_TH_ARR4_BITS 12
#define EDGE_TH_ARR4_MASK (((1 << 12) - 1) << 0)
#define EDGE_TH_ARR5_OFFSET 16
#define EDGE_TH_ARR5_BITS 12
#define EDGE_TH_ARR5_MASK (((1 << 12) - 1) << 16)
/* PFR_EDGE_TH_ARR3 0x00B8 */
#define EDGE_TH_ARR6_OFFSET 0
#define EDGE_TH_ARR6_BITS 12
#define EDGE_TH_ARR6_MASK (((1 << 12) - 1) << 0)
#define EDGE_TH_ARR7_OFFSET 16
#define EDGE_TH_ARR7_BITS 12
#define EDGE_TH_ARR7_MASK (((1 << 12) - 1) << 16)
/* PFR_EDGE_TH_ARR4 0x00BC */
#define EDGE_TH_ARR8_OFFSET 0
#define EDGE_TH_ARR8_BITS 12
#define EDGE_TH_ARR8_MASK (((1 << 12) - 1) << 0)

#endif /* _ISP_REG_CCM_H_INC_ */

