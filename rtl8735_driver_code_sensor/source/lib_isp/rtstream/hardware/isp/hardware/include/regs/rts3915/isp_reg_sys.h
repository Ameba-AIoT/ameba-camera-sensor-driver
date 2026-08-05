#ifndef _ISP_REG_SYS_H_INC_
#define _ISP_REG_SYS_H_INC_

#include <isp_reg.h>
#include <isp_reg_base.h>

#define SYS_CONTROL0 (SYS_REG_BASE + 0x0000)
#define SYS_CONTROL1 (SYS_REG_BASE + 0x0004)
#define SYS_CONTROL2 (SYS_REG_BASE + 0x0008)
#define SYS_CONTROL3 (SYS_REG_BASE + 0x000C)
#define SYS_INT_EN0 (SYS_REG_BASE + 0x0010)
#define SYS_INT_FLAG0 (SYS_REG_BASE + 0x0014)
#define SYS_ABORT_CNT (SYS_REG_BASE + 0x001C)
#define SYS_FRAME_CNT (SYS_REG_BASE + 0x0020)
#define SYS_ERROR_CNT (SYS_REG_BASE + 0x0024)
#define SYS_FRAME_IDLE (SYS_REG_BASE + 0x0028)
#define SYS_SPEED_CTRL (SYS_REG_BASE + 0x002C)
#define SYS_LAST_BREAK (SYS_REG_BASE + 0x0030)
#define SYS_LOW_DISABLE (SYS_REG_BASE + 0x0038)
#define SYS_DATA_ENABLE (SYS_REG_BASE + 0x003C)
#define SYS_DATA_DELAY (SYS_REG_BASE + 0x0040)
#define SYS_INPUT_CTRL (SYS_REG_BASE + 0x0044)
#define SYS_IMAGE_SEL0 (SYS_REG_BASE + 0x0048)
#define SYS_IMAGE_SEL1 (SYS_REG_BASE + 0x004C)
#define SYS_IMAGE_SEL2 (SYS_REG_BASE + 0x0050)
#define SYS_IMAGE_SEL3 (SYS_REG_BASE + 0x0054)
#define SYS_PATH_SEL (SYS_REG_BASE + 0x0058)
#define SYS_DIST_E (SYS_REG_BASE + 0x005C)
#define SYS_DIST_S (SYS_REG_BASE + 0x0060)
#define SYS_IMAGE_MODE_SEL (SYS_REG_BASE + 0x0064)
#define SYS_IMAGE_CHAN_SEL (SYS_REG_BASE + 0x0068)
#define SYS_STATIS_CTRL (SYS_REG_BASE + 0x006C)
#define SYS_ISP_CLK_CTRL (SYS_REG_BASE + 0x0070)
#define SYS_IMAGE_AI_CHAN_SEL (SYS_REG_BASE + 0x0078)

/* SYS_CONTROL0 0x0000 */
#define ISP_STOP_FRAME_OFFSET 0
#define ISP_STOP_FRAME_BITS 1
#define ISP_STOP_FRAME_MASK (((1 << 1) - 1) << 0)
#define ISP_STOP_OFFSET 1
#define ISP_STOP_BITS 1
#define ISP_STOP_MASK (((1 << 1) - 1) << 1)
#define ALL_MEM_IDLE_OFFSET 2
#define ALL_MEM_IDLE_BITS 1
#define ALL_MEM_IDLE_MASK (((1 << 1) - 1) << 2)
#define ISP_STILL_FRAME_OFFSET 3
#define ISP_STILL_FRAME_BITS 1
#define ISP_STILL_FRAME_MASK (((1 << 1) - 1) << 3)
#define ISP_START_OFFSET 4
#define ISP_START_BITS 1
#define ISP_START_MASK (((1 << 1) - 1) << 4)
/* SYS_CONTROL1 0x0004 */
#define YGAMMA_EN_OFFSET 0
#define YGAMMA_EN_BITS 1
#define YGAMMA_EN_MASK (((1 << 1) - 1) << 0)
#define ZOOM_EN_OFFSET 1
#define ZOOM_EN_BITS 1
#define ZOOM_EN_MASK (((1 << 1) - 1) << 1)
#define GAMMA_EN_OFFSET 2
#define GAMMA_EN_BITS 1
#define GAMMA_EN_MASK (((1 << 1) - 1) << 2)
#define MLSC_EN_OFFSET 3
#define MLSC_EN_BITS 1
#define MLSC_EN_MASK (((1 << 1) - 1) << 3)
#define NLSC_EN_OFFSET 4
#define NLSC_EN_BITS 1
#define NLSC_EN_MASK (((1 << 1) - 1) << 4)
#define UVTUNE_EN_OFFSET 5
#define UVTUNE_EN_BITS 1
#define UVTUNE_EN_MASK (((1 << 1) - 1) << 5)
#define HDR_EN_OFFSET 6
#define HDR_EN_BITS 1
#define HDR_EN_MASK (((1 << 1) - 1) << 6)
#define AE_EN_OFFSET 7
#define AE_EN_BITS 1
#define AE_EN_MASK (((1 << 1) - 1) << 7)
#define AWB_EN_OFFSET 8
#define AWB_EN_BITS 1
#define AWB_EN_MASK (((1 << 1) - 1) << 8)
#define BLC_EN_OFFSET 9
#define BLC_EN_BITS 1
#define BLC_EN_MASK (((1 << 1) - 1) << 9)
#define DEHAZE_EN_OFFSET 10
#define DEHAZE_EN_BITS 1
#define DEHAZE_EN_MASK (((1 << 1) - 1) << 10)
#define LDC_EN_PRE_OFFSET 11
#define LDC_EN_PRE_BITS 1
#define LDC_EN_PRE_MASK (((1 << 1) - 1) << 11)
#define YGC_EN_OFFSET 12
#define YGC_EN_BITS 1
#define YGC_EN_MASK (((1 << 1) - 1) << 12)
#define CCM_EN_OFFSET 13
#define CCM_EN_BITS 1
#define CCM_EN_MASK (((1 << 1) - 1) << 13)
#define DPC_EN_OFFSET 14
#define DPC_EN_BITS 1
#define DPC_EN_MASK (((1 << 1) - 1) << 14)
#define EEH_EN_OFFSET 15
#define EEH_EN_BITS 1
#define EEH_EN_MASK (((1 << 1) - 1) << 15)
#define SPE_EN_OFFSET 16
#define SPE_EN_BITS 1
#define SPE_EN_MASK (((1 << 1) - 1) << 16)
#define TNR_EN_OFFSET 17
#define TNR_EN_BITS 1
#define TNR_EN_MASK (((1 << 1) - 1) << 17)
#define BLC2_EN_OFFSET 18
#define BLC2_EN_BITS 1
#define BLC2_EN_MASK (((1 << 1) - 1) << 18)
#define DPC2_EN_OFFSET 19
#define DPC2_EN_BITS 1
#define DPC2_EN_MASK (((1 << 1) - 1) << 19)
#define TM_EN_OFFSET 20
#define TM_EN_BITS 1
#define TM_EN_MASK (((1 << 1) - 1) << 20)
/* SYS_CONTROL2 0x0008 */
#define YMODE_OFFSET 0
#define YMODE_BITS 1
#define YMODE_MASK (((1 << 1) - 1) << 0)
#define YBT709_OFFSET 1
#define YBT709_BITS 1
#define YBT709_MASK (((1 << 1) - 1) << 1)
#define DITHER_EN_OFFSET 2
#define DITHER_EN_BITS 1
#define DITHER_EN_MASK (((1 << 1) - 1) << 2)
#define LFSR_MODE_OFFSET 3
#define LFSR_MODE_BITS 1
#define LFSR_MODE_MASK (((1 << 1) - 1) << 3)
/* SYS_CONTROL3 0x000C */
#define DRC_CLK_ALWAYS_ON_OFFSET 0
#define DRC_CLK_ALWAYS_ON_BITS 1
#define DRC_CLK_ALWAYS_ON_MASK (((1 << 1) - 1) << 0)
/* SYS_INT_EN0 0x0010 */
#define AWB_STATIS_INT_EN_OFFSET 0
#define AWB_STATIS_INT_EN_BITS 1
#define AWB_STATIS_INT_EN_MASK (((1 << 1) - 1) << 0)
#define AF_STATIS_INT_EN_OFFSET 1
#define AF_STATIS_INT_EN_BITS 1
#define AF_STATIS_INT_EN_MASK (((1 << 1) - 1) << 1)
#define FRAME_ABORT_INT_EN_OFFSET 2
#define FRAME_ABORT_INT_EN_BITS 1
#define FRAME_ABORT_INT_EN_MASK (((1 << 1) - 1) << 2)
#define AE_STATIS_INT_EN_OFFSET 3
#define AE_STATIS_INT_EN_BITS 1
#define AE_STATIS_INT_EN_MASK (((1 << 1) - 1) << 3)
#define FRAME_START_INT_EN_OFFSET 4
#define FRAME_START_INT_EN_BITS 1
#define FRAME_START_INT_EN_MASK (((1 << 1) - 1) << 4)
#define FRAME_END_INT_EN_OFFSET 5
#define FRAME_END_INT_EN_BITS 1
#define FRAME_END_INT_EN_MASK (((1 << 1) - 1) << 5)
#define DATA_START_INT_EN_OFFSET 6
#define DATA_START_INT_EN_BITS 1
#define DATA_START_INT_EN_MASK (((1 << 1) - 1) << 6)
#define DATA_END_INT_EN_OFFSET 7
#define DATA_END_INT_EN_BITS 1
#define DATA_END_INT_EN_MASK (((1 << 1) - 1) << 7)
#define FLICK_INT_EN_OFFSET 8
#define FLICK_INT_EN_BITS 1
#define FLICK_INT_EN_MASK (((1 << 1) - 1) << 8)
#define RAW_STATIS_INT_EN_OFFSET 9
#define RAW_STATIS_INT_EN_BITS 1
#define RAW_STATIS_INT_EN_MASK (((1 << 1) - 1) << 9)
#define YUV_STATIS_INT_EN_OFFSET 10
#define YUV_STATIS_INT_EN_BITS 1
#define YUV_STATIS_INT_EN_MASK (((1 << 1) - 1) << 10)
#define STATIS_INT_EN_OFFSET 11
#define STATIS_INT_EN_BITS 1
#define STATIS_INT_EN_MASK (((1 << 1) - 1) << 11)
/* SYS_INT_FLAG0 0x0014 */
#define AWB_STATIS_INT_CLR_OFFSET 0
#define AWB_STATIS_INT_CLR_BITS 1
#define AWB_STATIS_INT_CLR_MASK (((1 << 1) - 1) << 0)
#define AF_STATIS_INT_CLR_OFFSET 1
#define AF_STATIS_INT_CLR_BITS 1
#define AF_STATIS_INT_CLR_MASK (((1 << 1) - 1) << 1)
#define FRAME_ABORT_INT_CLR_OFFSET 2
#define FRAME_ABORT_INT_CLR_BITS 1
#define FRAME_ABORT_INT_CLR_MASK (((1 << 1) - 1) << 2)
#define AE_STATIS_INT_CLR_OFFSET 3
#define AE_STATIS_INT_CLR_BITS 1
#define AE_STATIS_INT_CLR_MASK (((1 << 1) - 1) << 3)
#define FRAME_START_INT_CLR_OFFSET 4
#define FRAME_START_INT_CLR_BITS 1
#define FRAME_START_INT_CLR_MASK (((1 << 1) - 1) << 4)
#define FRAME_END_INT_CLR_OFFSET 5
#define FRAME_END_INT_CLR_BITS 1
#define FRAME_END_INT_CLR_MASK (((1 << 1) - 1) << 5)
#define DATA_START_INT_CLR_OFFSET 6
#define DATA_START_INT_CLR_BITS 1
#define DATA_START_INT_CLR_MASK (((1 << 1) - 1) << 6)
#define DATA_END_INT_CLR_OFFSET 7
#define DATA_END_INT_CLR_BITS 1
#define DATA_END_INT_CLR_MASK (((1 << 1) - 1) << 7)
#define FLICK_INT_CLR_OFFSET 8
#define FLICK_INT_CLR_BITS 1
#define FLICK_INT_CLR_MASK (((1 << 1) - 1) << 8)
#define RAW_STATIS_INT_CLR_OFFSET 9
#define RAW_STATIS_INT_CLR_BITS 1
#define RAW_STATIS_INT_CLR_MASK (((1 << 1) - 1) << 9)
#define YUV_STATIS_INT_CLR_OFFSET 10
#define YUV_STATIS_INT_CLR_BITS 1
#define YUV_STATIS_INT_CLR_MASK (((1 << 1) - 1) << 10)
#define STATIS_INT_CLR_OFFSET 11
#define STATIS_INT_CLR_BITS 1
#define STATIS_INT_CLR_MASK (((1 << 1) - 1) << 11)
/* SYS_ABORT_CNT 0x001C */
#define ABORT_COUNT_OFFSET 0
#define ABORT_COUNT_BITS 16
#define ABORT_COUNT_MASK (((1 << 16) - 1) << 0)
#define ABORT_COUNT_CLR_OFFSET 16
#define ABORT_COUNT_CLR_BITS 1
#define ABORT_COUNT_CLR_MASK (((1 << 1) - 1) << 16)
/* SYS_FRAME_CNT 0x0020 */
#define FCNT_OFFSET 0
#define FCNT_BITS 8
#define FCNT_MASK (((1 << 8) - 1) << 0)
#define FCNT_CLR_OFFSET 8
#define FCNT_CLR_BITS 1
#define FCNT_CLR_MASK (((1 << 1) - 1) << 8)
/* SYS_ERROR_CNT 0x0024 */
#define ERRCNT_OFFSET 0
#define ERRCNT_BITS 8
#define ERRCNT_MASK (((1 << 8) - 1) << 0)
#define ERRCNT_CLR_OFFSET 8
#define ERRCNT_CLR_BITS 1
#define ERRCNT_CLR_MASK (((1 << 1) - 1) << 8)
/* SYS_FRAME_IDLE 0x0028 */
#define DPC_MEM_IS_IDLE_OFFSET 0
#define DPC_MEM_IS_IDLE_BITS 1
#define DPC_MEM_IS_IDLE_MASK (((1 << 1) - 1) << 0)
#define INTP_MEM_IS_IDLE_OFFSET 1
#define INTP_MEM_IS_IDLE_BITS 1
#define INTP_MEM_IS_IDLE_MASK (((1 << 1) - 1) << 1)
#define ZOOM_MEM_IS_IDLE_OFFSET 2
#define ZOOM_MEM_IS_IDLE_BITS 1
#define ZOOM_MEM_IS_IDLE_MASK (((1 << 1) - 1) << 2)
#define EEN_MEM_IS_IDLE_OFFSET 3
#define EEN_MEM_IS_IDLE_BITS 1
#define EEN_MEM_IS_IDLE_MASK (((1 << 1) - 1) << 3)
#define CAMIF_IS_IDLE_OFFSET 4
#define CAMIF_IS_IDLE_BITS 1
#define CAMIF_IS_IDLE_MASK (((1 << 1) - 1) << 4)
#define ISP_FRAME_ABORT_OFFSET 5
#define ISP_FRAME_ABORT_BITS 1
#define ISP_FRAME_ABORT_MASK (((1 << 1) - 1) << 5)
/* SYS_SPEED_CTRL 0x002C */
#define RAW_SPEED_DIV_OFFSET 0
#define RAW_SPEED_DIV_BITS 5
#define RAW_SPEED_DIV_MASK (((1 << 5) - 1) << 0)
#define RAW_SPEED_MULT_OFFSET 5
#define RAW_SPEED_MULT_BITS 3
#define RAW_SPEED_MULT_MASK (((1 << 3) - 1) << 5)
#define RGB_SPEED_DIV_OFFSET 8
#define RGB_SPEED_DIV_BITS 5
#define RGB_SPEED_DIV_MASK (((1 << 5) - 1) << 8)
#define RGB_SPEED_MULT_OFFSET 13
#define RGB_SPEED_MULT_BITS 3
#define RGB_SPEED_MULT_MASK (((1 << 3) - 1) << 13)
#define YUV_SPEED_DIV_OFFSET 16
#define YUV_SPEED_DIV_BITS 5
#define YUV_SPEED_DIV_MASK (((1 << 5) - 1) << 16)
#define YUV_SPEED_MULT_OFFSET 21
#define YUV_SPEED_MULT_BITS 3
#define YUV_SPEED_MULT_MASK (((1 << 3) - 1) << 21)
/* SYS_LAST_BREAK 0x0030 */
#define RAW_LAST_BREAK_OFFSET 0
#define RAW_LAST_BREAK_BITS 10
#define RAW_LAST_BREAK_MASK (((1 << 10) - 1) << 0)
#define RGB_LAST_BREAK_OFFSET 10
#define RGB_LAST_BREAK_BITS 10
#define RGB_LAST_BREAK_MASK (((1 << 10) - 1) << 10)
#define YUV_LAST_BREAK_OFFSET 20
#define YUV_LAST_BREAK_BITS 10
#define YUV_LAST_BREAK_MASK (((1 << 10) - 1) << 20)
/* SYS_LOW_DISABLE 0x0038 */
#define LOW_DISABLE_OFFSET 0
#define LOW_DISABLE_BITS 1
#define LOW_DISABLE_MASK (((1 << 1) - 1) << 0)
#define LOW_DISABLE2_OFFSET 1
#define LOW_DISABLE2_BITS 1
#define LOW_DISABLE2_MASK (((1 << 1) - 1) << 1)
#define RAW_UV_DISABLE_OFFSET 2
#define RAW_UV_DISABLE_BITS 1
#define RAW_UV_DISABLE_MASK (((1 << 1) - 1) << 2)
/* SYS_DATA_ENABLE 0x003C */
#define DATA_EN_OFFSET 0
#define DATA_EN_BITS 1
#define DATA_EN_MASK (((1 << 1) - 1) << 0)
/* SYS_DATA_DELAY 0x0040 */
#define ISP_DATA_NUM_OFFSET 0
#define ISP_DATA_NUM_BITS 7
#define ISP_DATA_NUM_MASK (((1 << 7) - 1) << 0)
#define ISP_DATA_TRIG_OFFSET 7
#define ISP_DATA_TRIG_BITS 1
#define ISP_DATA_TRIG_MASK (((1 << 1) - 1) << 7)
#define ISP_DATA_EN_OFFSET 8
#define ISP_DATA_EN_BITS 1
#define ISP_DATA_EN_MASK (((1 << 1) - 1) << 8)
/* SYS_INPUT_CTRL 0x0044 */
#define MIPI_EN_OFFSET 0
#define MIPI_EN_BITS 1
#define MIPI_EN_MASK (((1 << 1) - 1) << 0)
#define FP_SEL_OFFSET 1
#define FP_SEL_BITS 1
#define FP_SEL_MASK (((1 << 1) - 1) << 1)
/* SYS_IMAGE_SEL0 0x0048 */
#define IMAGE_SEL0_OFFSET 0
#define IMAGE_SEL0_BITS 5
#define IMAGE_SEL0_MASK (((1 << 5) - 1) << 0)
/* SYS_IMAGE_SEL1 0x004C */
#define IMAGE_SEL1_OFFSET 0
#define IMAGE_SEL1_BITS 5
#define IMAGE_SEL1_MASK (((1 << 5) - 1) << 0)
/* SYS_IMAGE_SEL2 0x0050 */
#define IMAGE_SEL2_OFFSET 0
#define IMAGE_SEL2_BITS 5
#define IMAGE_SEL2_MASK (((1 << 5) - 1) << 0)
/* SYS_IMAGE_SEL3 0x0054 */
#define IMAGE_SEL3_OFFSET 0
#define IMAGE_SEL3_BITS 5
#define IMAGE_SEL3_MASK (((1 << 5) - 1) << 0)
/* SYS_PATH_SEL 0x0058 */
#define PATH_B_SEL_OFFSET 0
#define PATH_B_SEL_BITS 1
#define PATH_B_SEL_MASK (((1 << 1) - 1) << 0)
#define PATH_C_SEL_OFFSET 1
#define PATH_C_SEL_BITS 1
#define PATH_C_SEL_MASK (((1 << 1) - 1) << 1)
#define PATH_D_SEL_OFFSET 2
#define PATH_D_SEL_BITS 1
#define PATH_D_SEL_MASK (((1 << 1) - 1) << 2)
#define IMAGE_SOURCE_OFFSET 7
#define IMAGE_SOURCE_BITS 1
#define IMAGE_SOURCE_MASK (((1 << 1) - 1) << 7)
/* SYS_DIST_E 0x005C */
#define DIST_E_OFFSET 0
#define DIST_E_BITS 12
#define DIST_E_MASK (((1 << 12) - 1) << 0)
/* SYS_DIST_S 0x0060 */
#define DIST_S_OFFSET 0
#define DIST_S_BITS 12
#define DIST_S_MASK (((1 << 12) - 1) << 0)
/* SYS_IMAGE_MODE_SEL 0x0064 */
#define DOUT_MODE0_OFFSET 0
#define DOUT_MODE0_BITS 1
#define DOUT_MODE0_MASK (((1 << 1) - 1) << 0)
#define DOUT_MODE1_OFFSET 1
#define DOUT_MODE1_BITS 1
#define DOUT_MODE1_MASK (((1 << 1) - 1) << 1)
#define DOUT_MODE2_OFFSET 2
#define DOUT_MODE2_BITS 1
#define DOUT_MODE2_MASK (((1 << 1) - 1) << 2)
#define DOUT_MODE3_OFFSET 3
#define DOUT_MODE3_BITS 1
#define DOUT_MODE3_MASK (((1 << 1) - 1) << 3)
/* SYS_IMAGE_CHAN_SEL 0x0068 */
#define DOUT_CHAN_SEL0_OFFSET 0
#define DOUT_CHAN_SEL0_BITS 2
#define DOUT_CHAN_SEL0_MASK (((1 << 2) - 1) << 0)
#define DOUT_CHAN_SEL1_OFFSET 2
#define DOUT_CHAN_SEL1_BITS 2
#define DOUT_CHAN_SEL1_MASK (((1 << 2) - 1) << 2)
#define DOUT_CHAN_SEL2_OFFSET 4
#define DOUT_CHAN_SEL2_BITS 2
#define DOUT_CHAN_SEL2_MASK (((1 << 2) - 1) << 4)
#define DOUT_CHAN_SEL3_OFFSET 6
#define DOUT_CHAN_SEL3_BITS 2
#define DOUT_CHAN_SEL3_MASK (((1 << 2) - 1) << 6)
/* SYS_STATIS_CTRL 0x006C */
#define STATIS_TRIGGER_START_OFFSET 0
#define STATIS_TRIGGER_START_BITS 1
#define STATIS_TRIGGER_START_MASK (((1 << 1) - 1) << 0)
#define STATIS_TRIGGER_STOP_OFFSET 1
#define STATIS_TRIGGER_STOP_BITS 1
#define STATIS_TRIGGER_STOP_MASK (((1 << 1) - 1) << 1)
/* SYS_ISP_CLK_CTRL 0x0070 */
#define DUMMY_CLK_ON_OFFSET 0
#define DUMMY_CLK_ON_BITS 1
#define DUMMY_CLK_ON_MASK (((1 << 1) - 1) << 0)
#define DEHAZE_FUNC_CLK_ON_OFFSET 1
#define DEHAZE_FUNC_CLK_ON_BITS 1
#define DEHAZE_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 1)
#define MTD_FUNC_CLK_ON_OFFSET 2
#define MTD_FUNC_CLK_ON_BITS 1
#define MTD_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 2)
#define HDR_FUNC_CLK_ON_OFFSET 3
#define HDR_FUNC_CLK_ON_BITS 1
#define HDR_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 3)
#define UVT_FUNC_CLK_ON_OFFSET 4
#define UVT_FUNC_CLK_ON_BITS 1
#define UVT_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 4)
#define LDC_FUNC_CLK_ON_OFFSET 5
#define LDC_FUNC_CLK_ON_BITS 1
#define LDC_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 5)
#define YUVSIN_FUNC_CLK_ON_OFFSET 6
#define YUVSIN_FUNC_CLK_ON_BITS 1
#define YUVSIN_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 6)
#define YUV2RGB_FUNC_CLK_ON_OFFSET 7
#define YUV2RGB_FUNC_CLK_ON_BITS 1
#define YUV2RGB_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 7)
#define VHDRTM_FUNC_CLK_ON_OFFSET 8
#define VHDRTM_FUNC_CLK_ON_BITS 1
#define VHDRTM_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 8)
#define DPC2_RNR_SHORT_EXP_FUNC_CLK_ON_OFFSET 9
#define DPC2_RNR_SHORT_EXP_FUNC_CLK_ON_BITS 1
#define DPC2_RNR_SHORT_EXP_FUNC_CLK_ON_MASK (((1 << 1) - 1) << 9)
/* SYS_IMAGE_AI_CHAN_SEL 0x0078 */
#define YUV422TORGB888_EN_OFFSET 0
#define YUV422TORGB888_EN_BITS 1
#define YUV422TORGB888_EN_MASK (((1 << 1) - 1) << 0)

#endif /* _ISP_REG_SYS_H_INC_ */

