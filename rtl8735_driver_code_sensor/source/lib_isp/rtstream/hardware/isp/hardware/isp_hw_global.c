/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <isp_utils.h>
#include <isp_hw_global.h>
#include <isp_reg_sys.h>

static uint32_t gdrop_frame_num = 0;
static uint32_t gdrop_frame_num_sw = 0;
u32 g_isp_drop_frame_cnt = 0;

static int hw_global_get_bypass_bitmap(uint32_t isp_id,
				       struct rts_isp_bypass bypass)
{
	int i;
	uint32_t value = 0;
	static const uint8_t bit_mapping[] = {
		BLC_EN_OFFSET, BLC2_EN_OFFSET, DPC_EN_OFFSET, DPC2_EN_OFFSET, TNR_EN_OFFSET,
		TM_EN_OFFSET, NLSC_EN_OFFSET, MLSC_EN_OFFSET, AWB_EN_OFFSET, AE_EN_OFFSET,
		CCM_EN_OFFSET, GAMMA_EN_OFFSET, DEHAZE_EN_OFFSET, HDR_EN_OFFSET,
		YGC_EN_OFFSET, UVTUNE_EN_OFFSET, LDC_EN_PRE_OFFSET, EEH_EN_OFFSET,
		SPE_EN_OFFSET, YGAMMA_EN_OFFSET
	};

	for (i = 0; i < (int)ARRAY_SIZE(bit_mapping); i++)
		if ((1 << i) & bypass.all)
			isp_set_bit(value, bit_mapping[i]);
	return value;
}

static int isp_hw_global_set_func_enable(uint32_t isp_id,
					 struct isp_global_snr_info snr_info,
					 struct rts_isp_bypass bypass)
{
	uint32_t control_value;
	uint32_t clk_ctrl;
	uint32_t bypass_bits;

	if (isp_id >= _ISP_ID_NUM)
		return -RTS_ISP_EINVAL;

	if (snr_info.type == RAW_SENSOR) {
		if (snr_info.hdr==LINEAR_MODE) {
			if (!hal_isp_is_verify_path_on()) {
				control_value = (BLC_EN_MASK | DPC_EN_MASK | TNR_EN_MASK |
						NLSC_EN_MASK | MLSC_EN_MASK | AWB_EN_MASK |
						AE_EN_MASK | CCM_EN_MASK | GAMMA_EN_MASK |
						DEHAZE_EN_MASK | HDR_EN_MASK | YGC_EN_MASK |
						UVTUNE_EN_MASK | LDC_EN_PRE_MASK | EEH_EN_MASK |
						SPE_EN_MASK | YGAMMA_EN_MASK | ZOOM_EN_MASK);
			} else {
				control_value = (BLC_EN_MASK | DPC_EN_MASK | TNR_EN_MASK |
						NLSC_EN_MASK | /*MLSC_EN_MASK |*/ AWB_EN_MASK |
						AE_EN_MASK | CCM_EN_MASK | GAMMA_EN_MASK |
						DEHAZE_EN_MASK | HDR_EN_MASK | YGC_EN_MASK |
						UVTUNE_EN_MASK | /*LDC_EN_PRE_MASK |*/ EEH_EN_MASK |
						SPE_EN_MASK | YGAMMA_EN_MASK | ZOOM_EN_MASK);
			}

			clk_ctrl = (DEHAZE_FUNC_CLK_ON_MASK | MTD_FUNC_CLK_ON_MASK |
					HDR_FUNC_CLK_ON_MASK | UVT_FUNC_CLK_ON_MASK |
					LDC_FUNC_CLK_ON_MASK);
		} else {
			control_value = (BLC_EN_MASK | DPC_EN_MASK | TNR_EN_MASK |
					NLSC_EN_MASK | MLSC_EN_MASK | AWB_EN_MASK |
					AE_EN_MASK | CCM_EN_MASK | GAMMA_EN_MASK |
					DEHAZE_EN_MASK | HDR_EN_MASK | YGC_EN_MASK |
					UVTUNE_EN_MASK | LDC_EN_PRE_MASK | EEH_EN_MASK |
					SPE_EN_MASK | YGAMMA_EN_MASK | ZOOM_EN_MASK |
					BLC2_EN_MASK | DPC2_EN_MASK | TM_EN_MASK);

			clk_ctrl = (DEHAZE_FUNC_CLK_ON_MASK | MTD_FUNC_CLK_ON_MASK |
					HDR_FUNC_CLK_ON_MASK | UVT_FUNC_CLK_ON_MASK |
					LDC_FUNC_CLK_ON_MASK | VHDRTM_FUNC_CLK_ON_MASK |
					DPC2_RNR_SHORT_EXP_FUNC_CLK_ON_MASK);
		}


	} else {
		control_value = (CCM_EN_MASK | GAMMA_EN_MASK | DEHAZE_EN_MASK |
						HDR_EN_MASK | YGC_EN_MASK | UVTUNE_EN_MASK |
						LDC_EN_PRE_MASK | EEH_EN_MASK | SPE_EN_MASK |
						YGAMMA_EN_MASK | ZOOM_EN_MASK | TM_EN_MASK);

		clk_ctrl = (DUMMY_CLK_ON_MASK | DEHAZE_FUNC_CLK_ON_MASK |
			    MTD_FUNC_CLK_ON_MASK | HDR_FUNC_CLK_ON_MASK |
			    UVT_FUNC_CLK_ON_MASK | LDC_FUNC_CLK_ON_MASK |
			    YUVSIN_FUNC_CLK_ON_MASK | YUV2RGB_FUNC_CLK_ON_MASK);
	}

	bypass_bits = hw_global_get_bypass_bitmap(isp_id, bypass);

	isp_write_reg(~bypass_bits & control_value, SYS_CONTROL1);
	isp_write_reg(clk_ctrl, SYS_ISP_CLK_CTRL);

	return RTS_ISP_OK;
}

static int isp_hw_global_set_isp_path(uint32_t isp_id,
				      enum rts_isp_sensor_type type)
{
	if (type == RAW_SENSOR)
		isp_write_reg(0, SYS_PATH_SEL);
	else
		isp_write_reg(IMAGE_SOURCE_MASK | PATH_B_SEL_MASK,
			      SYS_PATH_SEL);
	return RTS_ISP_OK;
}

void isp_hw_global_set_drop_frame_num(uint32_t num)
{
	gdrop_frame_num = num;
}

uint32_t isp_hw_global_get_drop_frame_num(void)
{
	return gdrop_frame_num;
}

void isp_hw_global_set_drop_frame_num_sw(uint32_t num)
{
	gdrop_frame_num_sw = num;
	g_isp_drop_frame_cnt = 0;
}

uint32_t isp_hw_global_get_drop_frame_num_sw(void)
{
	return gdrop_frame_num_sw;
}

static int isp_hw_global_enable_data(uint32_t isp_id, int enable)
{
	if (enable) {
		if (gdrop_frame_num == 0)
			isp_set_reg_bit(ISP_DATA_EN_OFFSET, SYS_DATA_DELAY);
		else {
			isp_write_reg(ISP_DATA_TRIG_MASK | (gdrop_frame_num - 1), SYS_DATA_DELAY);
			printf("drop frame: %d\n\r", gdrop_frame_num);
		}
	}
	else {
		isp_clr_reg_bit(ISP_DATA_EN_OFFSET, SYS_DATA_DELAY);

	}
	return RTS_ISP_OK;
}

static int isp_hw_global_delay_data(uint32_t isp_id, int delay,
								  struct rts_isp_sync_regs *regs)
{
	int i;
	struct rts_isp_sync_reg *reg = regs->reg;

	if (delay < 0 || delay > ((1 << ISP_DATA_NUM_BITS) - 1))
		return -RTS_ISP_ERANGE;

	i = regs->num;
	set_sync_isp(&reg[i++], SYS_DATA_DELAY,
				 ISP_DATA_TRIG_MASK | delay);

	regs->num = i;

	return RTS_ISP_OK;
}

static int isp_hw_global_select_interface(uint32_t isp_id,
					  enum rts_isp_interface inf)
{
	//isp_info("%s inf %d \r\n", __FUNCTION__, inf);
	switch (inf) {
	case SNR_INTERFACE_DVP:
		isp_write_reg(0, SYS_INPUT_CTRL);
		break;
	case SNR_INTERFACE_MIPI:
		isp_write_reg(1, SYS_INPUT_CTRL);
		break;
	case SNR_INTERFACE_FIXP:
		isp_write_reg(2, SYS_INPUT_CTRL);
		break;
	case SNR_INTERFACE_NONE:
		isp_write_reg(0, SYS_INPUT_CTRL);
		break;
	default:
		return -RTS_ISP_EINVAL;
	}
	return RTS_ISP_OK;
}

static int isp_hw_global_set_statis_irq_enable(uint32_t isp_id, uint8_t statis_irq_en)
{
	uint32_t sys_int_en0 = isp_read_reg(SYS_INT_EN0);

	printf("Disable statis irq only for verify path\n\r");

	if (statis_irq_en)
		isp_write_reg(sys_int_en0 | STATIS_INT_EN_MASK, SYS_INT_EN0);
	else
		isp_write_reg(sys_int_en0 & ~STATIS_INT_EN_MASK, SYS_INT_EN0);
	return RTS_ISP_OK;
}

static int isp_hw_global_start_transfer(uint32_t isp_id)
{
	isp_write_reg(0xffffffff, SYS_INT_FLAG0);
	isp_write_reg(DATA_START_INT_EN_MASK | FRAME_END_INT_EN_MASK |
		      STATIS_INT_EN_MASK,
		      SYS_INT_EN0);
	isp_write_reg(ISP_START_MASK, SYS_CONTROL0);
	return RTS_ISP_OK;
}

static int isp_hw_global_stop_transfer(uint32_t isp_id)
{
	isp_write_reg(0, SYS_INT_EN0);
	isp_write_reg(0xffffffff, SYS_INT_FLAG0);
	isp_write_reg(ISP_STOP_MASK, SYS_CONTROL0);
	return RTS_ISP_OK;
}

static int isp_hw_global_set_speed_ctrl(uint32_t isp_id,
					struct isp_speed_ctrl *speed)
{
	const int speed_ctrl = speed->speed_mult << 5 | speed->speed_div;

	isp_write_reg(speed_ctrl << RAW_SPEED_DIV_OFFSET |
		      speed_ctrl << RGB_SPEED_DIV_OFFSET |
		      speed_ctrl << YUV_SPEED_DIV_OFFSET,
		      SYS_SPEED_CTRL);
	isp_write_reg(speed->last_break << RAW_LAST_BREAK_OFFSET |
		      speed->last_break << RGB_LAST_BREAK_OFFSET |
		      speed->last_break << YUV_LAST_BREAK_OFFSET,
		      SYS_LAST_BREAK);

	return RTS_ISP_OK;
}

static int isp_hw_global_get_output_menu(uint32_t isp_id,
					 struct isp_output_menu *menu)
{
	static const char * const menu_str[] = {
		"final output",
		"isp input of long exp path",
		"after crop of long exp path",
		"after tnr of long exp path",
		"before interpolation",
		"before ccm",
		"before rgb to yuv",
		"before yuv444 to yuv422",
		"before ldc",
		"after ldc",
		"after mask",
		"reserved",
		"vhdr raw isp input",
		"isp input of short exp path",
		"after crop of short exp path",
		"after snr of short exp path"
	};

	menu->num = ARRAY_SIZE(menu_str);
	menu->menu = menu_str;

	return RTS_ISP_OK;
}

static int isp_hw_global_set_output(uint32_t isp_id, uint32_t output)
{
	isp_write_reg(output, SYS_IMAGE_SEL0);

	return RTS_ISP_OK;
}

static int isp_hw_global_set_output_chn(uint32_t isp_id, uint32_t output)
{
	isp_write_reg(output, SYS_IMAGE_CHAN_SEL);

	return RTS_ISP_OK;
}

static const struct isp_hw_global_ops hw_global_ops = {
	.set_func_enable = isp_hw_global_set_func_enable,
	.set_isp_path = isp_hw_global_set_isp_path,
	.enable_data = isp_hw_global_enable_data,
	.delay_data = isp_hw_global_delay_data,
	.select_interface = isp_hw_global_select_interface,
	.start_transfer = isp_hw_global_start_transfer,
	.stop_transfer = isp_hw_global_stop_transfer,
	.set_speed_ctrl = isp_hw_global_set_speed_ctrl,
	.get_output_menu = isp_hw_global_get_output_menu,
	.set_output = isp_hw_global_set_output,
	.set_output_chn = isp_hw_global_set_output_chn,
	.set_statis_irq_enable = isp_hw_global_set_statis_irq_enable,
};

const struct isp_hw_global_ops *isp_hw_global_get_ops(void)
{
	return &hw_global_ops;
}
