#ifndef _ISP_REG_SNR_H_INC_
#define _ISP_REG_SNR_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define SNR_CTRL                       (SNR_REG_BASE + 0x0000)
#define SNR_DP_BRIGHT_DARK_THD         (SNR_REG_BASE + 0x0004)
#define SNR_DP_BRIGHT_DARK_RATE        (SNR_REG_BASE + 0x0008)
#define SNR_NR_RMIN_THD                (SNR_REG_BASE + 0x000C)
#define SNR_NR_R_SLOPE_G_CLIP_DELTA    (SNR_REG_BASE + 0x0010)
#define SNR_SHARP_RMAX_THD             (SNR_REG_BASE + 0x0014)
#define SNR_SHARP_DRAW_R_SLOPE         (SNR_REG_BASE + 0x0018)
#define SNR_GE_THD_STRENGTH            (SNR_REG_BASE + 0x001C)
#define SNR_NR_BASE_CURVE_Y0_Y1        (SNR_REG_BASE + 0x0020)
#define SNR_NR_BASE_CURVE_Y2_Y3        (SNR_REG_BASE + 0x0024)
#define SNR_NR_BASE_CURVE_Y4_Y5        (SNR_REG_BASE + 0x0028)
#define SNR_NR_BASE_CURVE_Y6_Y7        (SNR_REG_BASE + 0x002C)
#define SNR_NR_BASE_CURVE_Y8_Y9        (SNR_REG_BASE + 0x0030)
#define SNR_NR_BASE_CURVE_RATIO_OFFSET (SNR_REG_BASE + 0x0034)

/* SNR_CTRL                       0x0000 */
#define DP_THD_D1_OFFSET 16
#define DP_THD_D1_BITS 4
#define DP_THD_D1_MASK (((1 << 4) - 1) << 16)

#define DP_GROUP_SQUARE_OFFSET 7
#define DP_GROUP_SQUARE_BITS 1
#define DP_GROUP_SQUARE_MASK (((1 << 1) - 1) << 7)

#define DDP2_EN_OFFSET 6
#define DDP2_EN_BITS 1
#define DDP2_EN_MASK (((1 << 1) - 1) << 6)

#define DP_RP_EN_OFFSET 5
#define DP_RP_EN_BITS 1
#define DP_RP_EN_MASK (((1 << 1) - 1) << 5)

#define EDGE_DRAW_EN_OFFSET 4
#define EDGE_DRAW_EN_BITS 1
#define EDGE_DRAW_EN_MASK (((1 << 1) - 1) << 4)

#define DPC_SRD_SEL_OFFSET 3
#define DPC_SRD_SEL_BITS 1
#define DPC_SRD_SEL_MASK (((1 << 1) - 1) << 3)

#define NR_EN_OFFSET 2
#define NR_EN_BITS 1
#define NR_EN_MASK (((1 << 1) - 1) << 2)

#define SHARPEN_EN_OFFSET 1
#define SHARPEN_EN_BITS 1
#define SHARPEN_EN_MASK (((1 << 11) - 1) << 1)

#define GE_EN_OFFSET 0
#define GE_EN_BITS 1
#define GE_EN_MASK (((1 << 1) - 1) << 0)

/* SNR_DP_BRIGHT_DARK_THD         0x0004 */
#define DP_DARK_MAX_OFFSET 24
#define DP_DARK_MAX_BITS 5
#define DP_DARK_MAX_MASK (((1 << 5) - 1) << 24)

#define DP_DARK_MIN_OFFSET 16
#define DP_DARK_MIN_BITS 4
#define DP_DARK_MIN_MASK (((1 << 4) - 1) << 16)

#define DP_BRIT_MAX_OFFSET 8
#define DP_BRIT_MAX_BITS 5
#define DP_BRIT_MAX_MASK (((1 << 5) - 1) << 8)

#define DP_BRIT_MIN_OFFSET 0
#define DP_BRIT_MIN_BITS 4
#define DP_BRIT_MIN_MASK (((1 << 4) - 1) << 0)

/* SNR_DP_BRIGHT_DARK_RATE        0x0008 */
#define RB_DP_DARK_RATE_OFFSET 24
#define RB_DP_DARK_RATE_BITS 5
#define RB_DP_DARK_RATE_MASK (((1 << 5) - 1) << 24)

#define RB_DP_BRIGHT_RATE_OFFSET 16
#define RB_DP_BRIGHT_RATE_BITS 5
#define RB_DP_BRIGHT_RATE_MASK (((1 << 5) - 1) << 16)

#define G_DP_DARK_RATE_OFFSET 8
#define G_DP_DARK_RATE_BITS 5
#define G_DP_DARK_RATE_MASK (((1 << 5) - 1) << 8)

#define G_DP_BRIGHT_RATE_OFFSET 0
#define G_DP_BRIGHT_RATE_BITS 5
#define G_DP_BRIGHT_RATE_MASK (((1 << 5) - 1) << 0)

/* SNR_NR_RMIN_THD                0x000C */
#define nr_rmin_OFFSET 16
#define nr_rmin_BITS 9
#define nr_rmin_MASK (((1 << 9) - 1) << 16)

#define nr_thd1_OFFSET 8
#define nr_thd1_BITS 7
#define nr_thd1_MASK (((1 << 7) - 1) << 8)

#define nr_thd0_OFFSET 0
#define nr_thd0_BITS 7
#define nr_thd0_MASK (((1 << 7) - 1) << 0)

/* SNR_NR_R_SLOPE_G_CLIP_DELTA    0x0010 */
#define NR_G_CLIP_DELTA_OFFSET 16
#define NR_G_CLIP_DELTA_BITS 8
#define NR_G_CLIP_DELTA_MASK (((1 << 8) - 1) << 16)

#define NR_R_SLOPE_OFFSET 0
#define NR_R_SLOPE_BITS 15
#define NR_R_SLOPE_MASK (((1 << 15) - 1) << 0)

/* SNR_SHARP_RMAX_THD             0X0014 */
#define SH_DELTA_RMAX_OFFSET 16
#define SH_DELTA_RMAX_BITS 8
#define SH_DELTA_RMAX_MASK (((1 << 8) - 1) << 16)

#define SH_THD1_OFFSET 8
#define SH_THD1_BITS 7
#define SH_THD1_MASK (((1 << 7) - 1) << 8)

#define SH_THD0_OFFSET 0
#define SH_THD0_BITS 7
#define SH_THD0_MASK (((1 << 7) - 1) << 0)

/* SNR_SHARP_DRAW_R_SLOPE         0x0018 */
#define SH_R_SLOPE_OFFSET 0
#define SH_R_SLOPE_BITS 15
#define SH_R_SLOPE_MASK (((1 << 15) - 1) << 0)

/* SNR_GE_THD_STRENGTH            0x001C */
#define GE_STRENGTH_OFFSET 8
#define GE_STRENGTH_BITS 3
#define GE_STRENGTH_MASK (((1 << 3) - 1) << 8)

#define GE_THD_OFFSET 0
#define GE_THD_BITS 4
#define GE_THD_MASK (((1 << 4) - 1) << 0)

/* SNR_NR_BASE_CURVE_Y0_Y1        0X0020 */
#define BASECURVE_Y1_OFFSET 16
#define BASECURVE_Y1_BITS 12
#define BASECURVE_Y1_MASK (((1 << 12) - 1) << 16)

#define BASECURVE_Y0_OFFSET 0
#define BASECURVE_Y0_BITS 12
#define BASECURVE_Y0_MASK (((1 << 12) - 1) << 0)

/* SNR_NR_BASE_CURVE_Y2_Y3        0x0024 */
#define BASECURVE_Y3_OFFSET 16
#define BASECURVE_Y3_BITS 12
#define BASECURVE_Y3_MASK (((1 << 12) - 1) << 16)

#define BASECURVE_Y2_OFFSET 0
#define BASECURVE_Y2_BITS 12
#define BASECURVE_Y2_MASK (((1 << 12) - 1) << 0)

/* SNR_NR_BASE_CURVE_Y4_Y5        0x0028 */
#define BASECURVE_Y5_OFFSET 16
#define BASECURVE_Y5_BITS 12
#define BASECURVE_Y5_MASK (((1 << 12) - 1) << 16)

#define BASECURVE_Y4_OFFSET 0
#define BASECURVE_Y4_BITS 12
#define BASECURVE_Y4_MASK (((1 << 12) - 1) << 0)

/* SNR_NR_BASE_CURVE_Y6_Y7        0x002C */
#define BASECURVE_Y7_OFFSET 16
#define BASECURVE_Y7_BITS 12
#define BASECURVE_Y7_MASK (((1 << 12) - 1) << 16)

#define BASECURVE_Y6_OFFSET 0
#define BASECURVE_Y6_BITS 12
#define BASECURVE_Y6_MASK (((1 << 12) - 1) << 0)

/* SNR_NR_BASE_CURVE_Y8_Y9        0x0030 */
#define BASECURVE_Y9_OFFSET 16
#define BASECURVE_Y9_BITS 12
#define BASECURVE_Y9_MASK (((1 << 12) - 1) << 16)

#define BASECURVE_Y8_OFFSET 0
#define BASECURVE_Y8_BITS 12
#define BASECURVE_Y8_MASK (((1 << 12) - 1) << 0)

/* SNR_NR_BASE_CURVE_RATIO_OFFSET 0x0034 */
#define BASECURVE_OFFSET_OFFSET 16
#define BASECURVE_OFFSET_BITS 10
#define BASECURVE_OFFSET_MASK (((1 << 10) - 1) << 16)

#define BASECURVE_RATIO_OFFSET 0
#define BASECURVE_RATIO_BITS 9
#define BASECURVE_RATIO_MASK (((1 << 9) - 1) << 0)



#endif /* _ISP_REG_SNR_H_INC_ */