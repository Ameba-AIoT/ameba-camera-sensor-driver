/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <rts_isp_define.h>
#include <isp_utils.h>
#include <isp_hw_ae.h>
#include <math.h>
// #include <isp_reg_hdr.h>
#include <isp_reg_fusion.h>
#include <isp_reg_tm.h>
#include <isp_reg_ae.h>

#define AE_WIN_COLS 16
#define AE_WIN_ROWS 16
#define AE_WIN_SAMPLE_GAP_H 4
#define AE_WIN_SAMPLE_GAP_V 4
#define AE_HIST_BINS 256
#define AE_HIST_SAMPLE_GAP_H 4
#define AE_HIST_SAMPLE_GAP_V 4
#define AE_HDR_HIST_BINS 256

// #define DEBUG
//#define HDR_READY

#ifdef DEBUG
#define debug(fmt, ...) _rtl_printf(fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif

#undef max
#define max(a, b) (((a) > (b)) ? (a) : (b))

#undef min
#define min(a, b) (((a) < (b)) ? (a) : (b))

#undef min3
#define min3(a, b, c) (min(min((a), (b)), (c)))

#undef clamp
#define clamp(val, lo, hi) min(max(val, lo), hi)

static int reg_offset(int i)
{
	return (AE0_REG_BASE - AE_REG_BASE) + REG_OFFSET(AE, i);
}

static int isp_hw_ae_get_hw_info(uint32_t isp_id,
				 struct isp_ae_hw_info *info)
{
	int i;

	if (!info)
		return -RTS_ISP_EINVAL;

	memset(info, 0, sizeof(*info));
	info->ae.grid_info.size.cols = AE_WIN_COLS;
	info->ae.grid_info.size.rows = AE_WIN_ROWS;
	info->ae.grid_info.cell_align.w = AE_WIN_SAMPLE_GAP_H;
	info->ae.grid_info.cell_align.h = AE_WIN_SAMPLE_GAP_V;
	info->ae.cell_sample.w = AE_WIN_SAMPLE_GAP_H;
	info->ae.cell_sample.h = AE_WIN_SAMPLE_GAP_V;
	info->ae.hist_bins = AE_HIST_BINS;
	info->ae.hist_sample.w = AE_HIST_SAMPLE_GAP_H;
	info->ae.hist_sample.h = AE_HIST_SAMPLE_GAP_V;
	info->ae.y_mean_size = 2;
	info->ae.hist_bin_size = 4;

	for (i = 0; i < RTS_ISP_HDR_CHAN_MAX; i++) {
		info->hdr[i].grid_info.size.cols = AE_WIN_COLS;
		info->hdr[i].grid_info.size.rows = AE_WIN_ROWS;
		info->hdr[i].grid_info.cell_align.w = AE_WIN_SAMPLE_GAP_H;
		info->hdr[i].grid_info.cell_align.h = AE_WIN_SAMPLE_GAP_V;
		info->hdr[i].cell_sample.w = AE_WIN_SAMPLE_GAP_H;
		info->hdr[i].cell_sample.h = AE_WIN_SAMPLE_GAP_V;
		//info->hdr[i].hist_bins = AE_HIST_BINS;
		info->hdr[i].hist_bins = AE_HDR_HIST_BINS;
		info->hdr[i].hist_sample.w = AE_HIST_SAMPLE_GAP_H;
		info->hdr[i].hist_sample.h = AE_HIST_SAMPLE_GAP_V;
		info->hdr[i].y_mean_size = 2;
		info->hdr[i].hist_bin_size = 4;
	}

	return RTS_ISP_OK;
}

static int isp_hw_ae_set_statis(uint32_t isp_id, const rts_isp_grid_t *grid)
{
	int i;
	rts_isp_point_t end;
	int win_sample_num;

	end.x = grid->start.x + grid->cell.w * grid->size.cols;
	end.y = grid->start.y + grid->cell.h * grid->size.rows;
	win_sample_num = (grid->cell.w * grid->cell.h /
			  AE_WIN_SAMPLE_GAP_H / AE_WIN_SAMPLE_GAP_V);

	isp_write_reg(grid->start.x | grid->start.y << 16, AE_WIN_START);
	isp_write_reg((grid->cell.w / AE_WIN_SAMPLE_GAP_H) |
		      (grid->cell.h / AE_WIN_SAMPLE_GAP_V) << 8 |
		      grid->size.cols << 16 | grid->size.rows << 24,
		      AE_WIN_SIZE);
	isp_write_reg(win_sample_num, AE_WIN_CAL_NUM);
	isp_write_reg(grid->start.x | grid->start.y << 16, AE_HWIN_START);
	isp_write_reg(end.x | end.y << 16, AE_HWIN_END);
	isp_write_reg(0x01, AE_CTRL);

	for (i = 0; i < 2; i++) {
		isp_write_reg(grid->start.x | grid->start.y << 16,
			      AE_WIN_START + reg_offset(i));
		isp_write_reg(((grid->cell.w / AE_WIN_SAMPLE_GAP_H) |
			       (grid->cell.h / AE_WIN_SAMPLE_GAP_V) << 8 |
			       grid->size.cols << 16 | grid->size.rows << 24),
			      AE_WIN_SIZE + reg_offset(i));
		isp_write_reg(win_sample_num, AE_WIN_CAL_NUM + reg_offset(i));
		isp_write_reg(grid->start.x | grid->start.y << 16,
			      AE_HWIN_START + reg_offset(i));
		isp_write_reg(end.x | end.y << 16, AE_HWIN_END + reg_offset(i));
		isp_write_reg(0x01, AE_CTRL + reg_offset(i));
	}

	return RTS_ISP_OK;
}

static int isp_hw_ae_get_sync_regs(uint32_t isp_id, uint32_t delay,
				   struct rts_isp_sync_reg *reg, int *num,
				   const struct rts_isp_ae_exp_gain *exp_gain)
{
	int i = 0;
	float ratiof;
	uint32_t fusion_regload;
	uint32_t ratio;
	uint32_t ratio_inv;

	if (!reg || !exp_gain || delay > 2)
		return -RTS_ISP_EINVAL;

	if (exp_gain->hdr == HDR_MODE) {
		fusion_regload = 1;
		ratiof = ((exp_gain->exposure[0] * exp_gain->analog_gain[0] *
			   exp_gain->digital_gain[0] *
			   exp_gain->isp_hdr_gain[0]) /
			  (exp_gain->exposure[1] * exp_gain->analog_gain[1] *
			   exp_gain->digital_gain[1] *
			   exp_gain->isp_hdr_gain[1]));
	} else {
		fusion_regload = 0;
		ratiof = 1.0f;
	}
	ratiof = clamp(ratiof, AE_MIN_RATIO, AE_MAX_RATIO);

	ratio = ratiof * 4;
	ratio_inv = 4096 / ratiof;

	//set_sync_info(&reg[i++], delay, RTS_ISP_INT_DATA_START);
	//RTS_ISP_SYNC_REG_TYPE_REG
	// isp_write_reg( exp_gain->isp_gain * 2048, AE_GAIN);
	// isp_write_reg(0x100, AE_CTRL);

	set_sync_isp_mask(&reg[i++], FUSION_EXP_RATIO,
		     (ratio << FUSION_EXP_RATIO_OFFSET),
			 FUSION_EXP_RATIO_MASK);
	set_sync_isp(&reg[i++], FUSION_REG_LOAD, fusion_regload);
	set_sync_isp(&reg[i++], TM_EXP_RATIO_INV, ratio_inv);
	set_sync_isp(&reg[i++], TM_REG_LOAD, fusion_regload);
	*num = i;

	debug("fusion ratiof = %f, ratio = %d,fusion ratio inv = %d\n", ratiof, ratio, ratio_inv);

	return RTS_ISP_OK;
}

static int isp_hw_ae_set_hdr(uint32_t isp_id)
{
	// Init fusion mode to lumin
	isp_write_reg_mask(0 << FS_MODE_OFFSET, FUSION_EXP_RATIO, FS_MODE_MASK);

	return RTS_ISP_OK;
}

static int isp_hw_ae_enable_hdr(uint32_t isp_id, int enable)
{
	#if HDR_READY
	if (enable) {
		// isp_write_reg(STREAM_EN_VHDR_MASK, HDR_STREAM_EN);
		// __set_hdr_tm_regs();
	} else {
		// int count = 10;

		// isp_set_reg_bit(VHDR_STOP_OFFSET, HDR_STREAM_EN);
		// while (isp_read_reg(HDR_AXI_FSM_STATE) && count--)
		// 	usleep(1000);
		// if (count < 0)
		// 	return -RTS_ISP_EBUSY;
		// __set_linear_tm_regs();
	}
	#endif

	return RTS_ISP_OK;
}

static const struct isp_hw_ae_ops hw_ae_ops = {
	.get_hw_info = isp_hw_ae_get_hw_info,
	.set_statis = isp_hw_ae_set_statis,
	.get_sync_regs = isp_hw_ae_get_sync_regs,
	.set_hdr = isp_hw_ae_set_hdr,
	.enable_hdr = isp_hw_ae_enable_hdr,
};

const struct isp_hw_ae_ops *isp_hw_ae_get_ops(void)
{
	return &hw_ae_ops;
}
