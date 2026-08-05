#ifndef _ISP_REG_WDR_H_INC_
#define _ISP_REG_WDR_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define WDR_ENABLE (WDR_REG_BASE + 0x0000)
#define WDR_MODE (WDR_REG_BASE + 0x0004)
#define WDR_LOAD (WDR_REG_BASE + 0x0008)
#define WDR_STEP (WDR_REG_BASE + 0x000C)
#define WDR_LEVEL (WDR_REG_BASE + 0x0010)
#define WDR_LEVEL_NOW (WDR_REG_BASE + 0x0014)
#define WDR_CONT_RATE_BOUND (WDR_REG_BASE + 0x0018)
#define WDR_CONT_PARAM0 (WDR_REG_BASE + 0x0020)
#define WDR_CONT_PARAM1 (WDR_REG_BASE + 0x0024)
#define WDR_CONT_PARAM2 (WDR_REG_BASE + 0x0028)
#define WDR_CONT_PARAM3 (WDR_REG_BASE + 0x002C)
#define WDR_PARAM0 (WDR_REG_BASE + 0x0030)
#define WDR_PARAM1 (WDR_REG_BASE + 0x0034)
#define WDR_PARAM2 (WDR_REG_BASE + 0x0038)
#define WDR_PARAM3 (WDR_REG_BASE + 0x003C)
#define WDR_PARAM4 (WDR_REG_BASE + 0x0040)
#define WDR_PARAM5 (WDR_REG_BASE + 0x0044)
#define WDR_PARAM6 (WDR_REG_BASE + 0x0048)
#define WDR_LPF_COEF0 (WDR_REG_BASE + 0x0050)
#define WDR_LPF_COEF1 (WDR_REG_BASE + 0x0054)
#define WDR_LPF_COEF2 (WDR_REG_BASE + 0x0058)
#define WDR_LOC_ADJUST_THD (WDR_REG_BASE + 0x0060)
#define WDR_INC_RATE (WDR_REG_BASE + 0x0064)
#define WDR_HER_DIFF_THD (WDR_REG_BASE + 0x0068)
#define WDR_HER_DIFF_INV (WDR_REG_BASE + 0x006C)
#define WDR_HER_ADJ_THD (WDR_REG_BASE + 0x0070)
#define WDR_HER_ADJ_INV (WDR_REG_BASE + 0x0074)
#define WDR_HER_ADJ_MIN (WDR_REG_BASE + 0x0078)
#define WDR_DE_THD (WDR_REG_BASE + 0x007C)
#define WDR_DE_INV (WDR_REG_BASE + 0x0080)
#define WDR_AL_PARAM (WDR_REG_BASE + 0x0084)
#define WDR_AL_M (WDR_REG_BASE + 0x0088)
#define WDR_AL_RATIO (WDR_REG_BASE + 0x008C)
#define WDR_AL_RATIO_AUTO (WDR_REG_BASE + 0x0090)

/* WDR_ENABLE 0x0000 */
#define LPF_EN_OFFSET 1
#define LPF_EN_BITS 1
#define LPF_EN_MASK (((1 << 1) - 1) << 1)
#define CONT_EN_OFFSET 2
#define CONT_EN_BITS 1
#define CONT_EN_MASK (((1 << 1) - 1) << 2)
#define HER_ENABLE_OFFSET 3
#define HER_ENABLE_BITS 1
#define HER_ENABLE_MASK (((1 << 1) - 1) << 3)
#define DE_ENABLE_OFFSET 4
#define DE_ENABLE_BITS 1
#define DE_ENABLE_MASK (((1 << 1) - 1) << 4)
#define HDR_LOC_ADJ_EN_OFFSET 5
#define HDR_LOC_ADJ_EN_BITS 1
#define HDR_LOC_ADJ_EN_MASK (((1 << 1) - 1) << 5)
#define AL_ENABLE_OFFSET 6
#define AL_ENABLE_BITS 1
#define AL_ENABLE_MASK (((1 << 1) - 1) << 6)
#define AL_STEP_EN_OFFSET 7
#define AL_STEP_EN_BITS 1
#define AL_STEP_EN_MASK (((1 << 1) - 1) << 7)
/* WDR_MODE 0x0004 */
#define HDR_MODE_OFFSET 0
#define HDR_MODE_BITS 1
#define HDR_MODE_MASK (((1 << 1) - 1) << 0)
#define CONT_MODE_OFFSET 1
#define CONT_MODE_BITS 1
#define CONT_MODE_MASK (((1 << 1) - 1) << 1)
#define AL_MODE_OFFSET 2
#define AL_MODE_BITS 1
#define AL_MODE_MASK (((1 << 1) - 1) << 2)
/* WDR_LOAD 0x0008 */
#define ADJ_STOP_OFFSET 0
#define ADJ_STOP_BITS 1
#define ADJ_STOP_MASK (((1 << 1) - 1) << 0)
#define ADJ_TRIG_OFFSET 1
#define ADJ_TRIG_BITS 1
#define ADJ_TRIG_MASK (((1 << 1) - 1) << 1)
#define HDR_REG_LOAD_OFFSET 2
#define HDR_REG_LOAD_BITS 1
#define HDR_REG_LOAD_MASK (((1 << 1) - 1) << 2)
#define ADJ_GOING_OFFSET 3
#define ADJ_GOING_BITS 1
#define ADJ_GOING_MASK (((1 << 1) - 1) << 3)
/* WDR_STEP 0x000C */
#define HDR_STEP_OFFSET 0
#define HDR_STEP_BITS 6
#define HDR_STEP_MASK (((1 << 6) - 1) << 0)
#define CONT_STEP_OFFSET 8
#define CONT_STEP_BITS 6
#define CONT_STEP_MASK (((1 << 6) - 1) << 8)
/* WDR_LEVEL 0x0010 */
#define HDR_LEVEL_OFFSET 0
#define HDR_LEVEL_BITS 8
#define HDR_LEVEL_MASK (((1 << 8) - 1) << 0)
#define CONT_LEVEL_OFFSET 8
#define CONT_LEVEL_BITS 8
#define CONT_LEVEL_MASK (((1 << 8) - 1) << 8)
/* WDR_LEVEL_NOW 0x0014 */
#define HDR_LEVEL_SYNC_OFFSET 0
#define HDR_LEVEL_SYNC_BITS 8
#define HDR_LEVEL_SYNC_MASK (((1 << 8) - 1) << 0)
#define CONT_LEVEL_SYNC_OFFSET 8
#define CONT_LEVEL_SYNC_BITS 8
#define CONT_LEVEL_SYNC_MASK (((1 << 8) - 1) << 8)
/* WDR_CONT_RATE_BOUND 0x0018 */
#define CONT_RATE_MIN_OFFSET 0
#define CONT_RATE_MIN_BITS 6
#define CONT_RATE_MIN_MASK (((1 << 6) - 1) << 0)
#define CONT_RATE_MAX_OFFSET 8
#define CONT_RATE_MAX_BITS 6
#define CONT_RATE_MAX_MASK (((1 << 6) - 1) << 8)
/* WDR_CONT_PARAM0 0x0020 */
#define CONT_P0_OFFSET 0
#define CONT_P0_BITS 6
#define CONT_P0_MASK (((1 << 6) - 1) << 0)
#define CONT_P1_OFFSET 8
#define CONT_P1_BITS 6
#define CONT_P1_MASK (((1 << 6) - 1) << 8)
#define CONT_P2_OFFSET 16
#define CONT_P2_BITS 6
#define CONT_P2_MASK (((1 << 6) - 1) << 16)
#define CONT_P3_OFFSET 24
#define CONT_P3_BITS 6
#define CONT_P3_MASK (((1 << 6) - 1) << 24)
/* WDR_CONT_PARAM1 0x0024 */
#define CONT_P4_OFFSET 0
#define CONT_P4_BITS 6
#define CONT_P4_MASK (((1 << 6) - 1) << 0)
#define CONT_P5_OFFSET 8
#define CONT_P5_BITS 6
#define CONT_P5_MASK (((1 << 6) - 1) << 8)
#define CONT_P6_OFFSET 16
#define CONT_P6_BITS 6
#define CONT_P6_MASK (((1 << 6) - 1) << 16)
#define CONT_P7_OFFSET 24
#define CONT_P7_BITS 6
#define CONT_P7_MASK (((1 << 6) - 1) << 24)
/* WDR_CONT_PARAM2 0x0028 */
#define CONT_P8_OFFSET 0
#define CONT_P8_BITS 6
#define CONT_P8_MASK (((1 << 6) - 1) << 0)
#define CONT_P9_OFFSET 8
#define CONT_P9_BITS 6
#define CONT_P9_MASK (((1 << 6) - 1) << 8)
#define CONT_PA_OFFSET 16
#define CONT_PA_BITS 6
#define CONT_PA_MASK (((1 << 6) - 1) << 16)
#define CONT_PB_OFFSET 24
#define CONT_PB_BITS 6
#define CONT_PB_MASK (((1 << 6) - 1) << 24)
/* WDR_CONT_PARAM3 0x002C */
#define CONT_PC_OFFSET 0
#define CONT_PC_BITS 6
#define CONT_PC_MASK (((1 << 6) - 1) << 0)
#define CONT_PD_OFFSET 8
#define CONT_PD_BITS 6
#define CONT_PD_MASK (((1 << 6) - 1) << 8)
#define CONT_PE_OFFSET 16
#define CONT_PE_BITS 6
#define CONT_PE_MASK (((1 << 6) - 1) << 16)
/* WDR_PARAM0 0x0030 */
#define HDR_P0_OFFSET 0
#define HDR_P0_BITS 8
#define HDR_P0_MASK (((1 << 8) - 1) << 0)
#define HDR_P1_OFFSET 8
#define HDR_P1_BITS 8
#define HDR_P1_MASK (((1 << 8) - 1) << 8)
#define HDR_P2_OFFSET 16
#define HDR_P2_BITS 8
#define HDR_P2_MASK (((1 << 8) - 1) << 16)
#define HDR_P3_OFFSET 24
#define HDR_P3_BITS 8
#define HDR_P3_MASK (((1 << 8) - 1) << 24)
/* WDR_PARAM1 0x0034 */
#define HDR_P4_OFFSET 0
#define HDR_P4_BITS 8
#define HDR_P4_MASK (((1 << 8) - 1) << 0)
#define HDR_P5_OFFSET 8
#define HDR_P5_BITS 8
#define HDR_P5_MASK (((1 << 8) - 1) << 8)
#define HDR_P6_OFFSET 16
#define HDR_P6_BITS 8
#define HDR_P6_MASK (((1 << 8) - 1) << 16)
#define HDR_P7_OFFSET 24
#define HDR_P7_BITS 8
#define HDR_P7_MASK (((1 << 8) - 1) << 24)
/* WDR_PARAM2 0x0038 */
#define HDR_P8_OFFSET 0
#define HDR_P8_BITS 7
#define HDR_P8_MASK (((1 << 7) - 1) << 0)
#define HDR_P9_OFFSET 8
#define HDR_P9_BITS 7
#define HDR_P9_MASK (((1 << 7) - 1) << 8)
#define HDR_PA_OFFSET 16
#define HDR_PA_BITS 7
#define HDR_PA_MASK (((1 << 7) - 1) << 16)
#define HDR_PB_OFFSET 24
#define HDR_PB_BITS 7
#define HDR_PB_MASK (((1 << 7) - 1) << 24)
/* WDR_PARAM3 0x003C */
#define HDR_PC_OFFSET 0
#define HDR_PC_BITS 7
#define HDR_PC_MASK (((1 << 7) - 1) << 0)
#define HDR_PD_OFFSET 8
#define HDR_PD_BITS 7
#define HDR_PD_MASK (((1 << 7) - 1) << 8)
#define HDR_PE_OFFSET 16
#define HDR_PE_BITS 7
#define HDR_PE_MASK (((1 << 7) - 1) << 16)
#define HDR_PF_OFFSET 24
#define HDR_PF_BITS 7
#define HDR_PF_MASK (((1 << 7) - 1) << 24)
/* WDR_PARAM4 0x0040 */
#define HDR_PG_OFFSET 0
#define HDR_PG_BITS 7
#define HDR_PG_MASK (((1 << 7) - 1) << 0)
#define HDR_PH_OFFSET 8
#define HDR_PH_BITS 7
#define HDR_PH_MASK (((1 << 7) - 1) << 8)
#define HDR_PI_OFFSET 16
#define HDR_PI_BITS 7
#define HDR_PI_MASK (((1 << 7) - 1) << 16)
#define HDR_PJ_OFFSET 24
#define HDR_PJ_BITS 7
#define HDR_PJ_MASK (((1 << 7) - 1) << 24)
/* WDR_PARAM5 0x0044 */
#define HDR_PK_OFFSET 0
#define HDR_PK_BITS 7
#define HDR_PK_MASK (((1 << 7) - 1) << 0)
#define HDR_PL_OFFSET 8
#define HDR_PL_BITS 7
#define HDR_PL_MASK (((1 << 7) - 1) << 8)
#define HDR_PM_OFFSET 16
#define HDR_PM_BITS 7
#define HDR_PM_MASK (((1 << 7) - 1) << 16)
#define HDR_PN_OFFSET 24
#define HDR_PN_BITS 7
#define HDR_PN_MASK (((1 << 7) - 1) << 24)
/* WDR_PARAM6 0x0048 */
#define HDR_PO_OFFSET 0
#define HDR_PO_BITS 7
#define HDR_PO_MASK (((1 << 7) - 1) << 0)
#define HDR_PP_OFFSET 8
#define HDR_PP_BITS 7
#define HDR_PP_MASK (((1 << 7) - 1) << 8)
#define HDR_PQ_OFFSET 16
#define HDR_PQ_BITS 7
#define HDR_PQ_MASK (((1 << 7) - 1) << 16)
#define HDR_PR_OFFSET 24
#define HDR_PR_BITS 7
#define HDR_PR_MASK (((1 << 7) - 1) << 24)
/* WDR_LPF_COEF0 0x0050 */
#define LPF_C0_OFFSET 0
#define LPF_C0_BITS 3
#define LPF_C0_MASK (((1 << 3) - 1) << 0)
#define LPF_C1_OFFSET 8
#define LPF_C1_BITS 3
#define LPF_C1_MASK (((1 << 3) - 1) << 8)
#define LPF_C2_OFFSET 16
#define LPF_C2_BITS 3
#define LPF_C2_MASK (((1 << 3) - 1) << 16)
#define LPF_C3_OFFSET 24
#define LPF_C3_BITS 5
#define LPF_C3_MASK (((1 << 5) - 1) << 24)
/* WDR_LPF_COEF1 0x0054 */
#define LPF_C4_OFFSET 0
#define LPF_C4_BITS 5
#define LPF_C4_MASK (((1 << 5) - 1) << 0)
#define LPF_C5_OFFSET 8
#define LPF_C5_BITS 5
#define LPF_C5_MASK (((1 << 5) - 1) << 8)
#define LPF_C6_OFFSET 16
#define LPF_C6_BITS 3
#define LPF_C6_MASK (((1 << 3) - 1) << 16)
#define LPF_C7_OFFSET 24
#define LPF_C7_BITS 3
#define LPF_C7_MASK (((1 << 3) - 1) << 24)
/* WDR_LPF_COEF2 0x0058 */
#define LPF_C8_OFFSET 0
#define LPF_C8_BITS 3
#define LPF_C8_MASK (((1 << 3) - 1) << 0)
/* WDR_LOC_ADJUST_THD 0x0060 */
#define HDR_LOC_ADJ_THD_OFFSET 0
#define HDR_LOC_ADJ_THD_BITS 8
#define HDR_LOC_ADJ_THD_MASK (((1 << 8) - 1) << 0)
#define HDR_LOC_ADJ_THD_INV_OFFSET 8
#define HDR_LOC_ADJ_THD_INV_BITS 8
#define HDR_LOC_ADJ_THD_INV_MASK (((1 << 8) - 1) << 8)
/* WDR_INC_RATE 0x0064 */
#define HDR_INC_RATE0_OFFSET 0
#define HDR_INC_RATE0_BITS 5
#define HDR_INC_RATE0_MASK (((1 << 5) - 1) << 0)
#define HDR_INC_RATE1_OFFSET 8
#define HDR_INC_RATE1_BITS 5
#define HDR_INC_RATE1_MASK (((1 << 5) - 1) << 8)
/* WDR_HER_DIFF_THD 0x0068 */
#define HER_DIFF_THD1_OFFSET 0
#define HER_DIFF_THD1_BITS 8
#define HER_DIFF_THD1_MASK (((1 << 8) - 1) << 0)
#define HER_DIFF_THD2_OFFSET 8
#define HER_DIFF_THD2_BITS 8
#define HER_DIFF_THD2_MASK (((1 << 8) - 1) << 8)
/* WDR_HER_DIFF_INV 0x006C */
#define HER_DIFF_INV_OFFSET 0
#define HER_DIFF_INV_BITS 8
#define HER_DIFF_INV_MASK (((1 << 8) - 1) << 0)
/* WDR_HER_ADJ_THD 0x0070 */
#define HER_ADJ_THD1_OFFSET 0
#define HER_ADJ_THD1_BITS 8
#define HER_ADJ_THD1_MASK (((1 << 8) - 1) << 0)
#define HER_ADJ_THD2_OFFSET 16
#define HER_ADJ_THD2_BITS 8
#define HER_ADJ_THD2_MASK (((1 << 8) - 1) << 16)
/* WDR_HER_ADJ_INV 0x0074 */
#define HER_ADJ_INV_OFFSET 0
#define HER_ADJ_INV_BITS 8
#define HER_ADJ_INV_MASK (((1 << 8) - 1) << 0)
/* WDR_HER_ADJ_MIN 0x0078 */
#define HER_ADJ_MIN_OFFSET 0
#define HER_ADJ_MIN_BITS 7
#define HER_ADJ_MIN_MASK (((1 << 7) - 1) << 0)
/* WDR_DE_THD 0x007C */
#define DE_THD1_OFFSET 0
#define DE_THD1_BITS 8
#define DE_THD1_MASK (((1 << 8) - 1) << 0)
#define DE_THD2_OFFSET 8
#define DE_THD2_BITS 8
#define DE_THD2_MASK (((1 << 8) - 1) << 8)
#define DE_MIN_OFFSET 16
#define DE_MIN_BITS 6
#define DE_MIN_MASK (((1 << 6) - 1) << 16)
#define DE_MAX_OFFSET 24
#define DE_MAX_BITS 6
#define DE_MAX_MASK (((1 << 6) - 1) << 24)
/* WDR_DE_INV 0x0080 */
#define DE_INV_OFFSET 0
#define DE_INV_BITS 8
#define DE_INV_MASK (((1 << 8) - 1) << 0)
/* WDR_AL_PARAM 0x0084 */
#define AL_RATE_OFFSET 0
#define AL_RATE_BITS 5
#define AL_RATE_MASK (((1 << 5) - 1) << 0)
#define AL_STEP_OFFSET 5
#define AL_STEP_BITS 4
#define AL_STEP_MASK (((1 << 4) - 1) << 5)
#define AL_STEP_TRIGGER_RANGE_OFFSET 9
#define AL_STEP_TRIGGER_RANGE_BITS 3
#define AL_STEP_TRIGGER_RANGE_MASK (((1 << 3) - 1) << 9)
/* WDR_AL_M 0x0088 */
#define AL_M1_REG_OFFSET 0
#define AL_M1_REG_BITS 8
#define AL_M1_REG_MASK (((1 << 8) - 1) << 0)
#define AL_M2_REG_OFFSET 8
#define AL_M2_REG_BITS 8
#define AL_M2_REG_MASK (((1 << 8) - 1) << 8)
/* WDR_AL_RATIO 0x008C */
#define AL_RATIO_REG_OFFSET 0
#define AL_RATIO_REG_BITS 10
#define AL_RATIO_REG_MASK (((1 << 10) - 1) << 0)
/* WDR_AL_RATIO_AUTO 0x0090 */
#define AL_RATIO_OFFSET 0
#define AL_RATIO_BITS 10
#define AL_RATIO_MASK (((1 << 10) - 1) << 0)

#endif /* _ISP_REG_WDR_H_INC_ */

