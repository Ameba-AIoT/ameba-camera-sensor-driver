/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2021 Mike Wong <mike.wong@realtek.com>
 */

#include <isp_utils.h>
#include <isp_hw_tm.h>
#include <isp_reg_tm.h>
#include <isp_reg_virtual.h>
#include <math.h>

#define TM_CURVE_NUM 7
#define TM_BIT_RANK 9
#define TM_TARGET_MAX 14
#define TM_TARGET_MIN 12

static int isp_hw_enable_tm(uint32_t isp_id, int enable)
{
	if (enable){
		isp_set_reg_bit(TM_EN_OFFSET, TM_CTRL);
	}
	else{
		isp_clr_reg_bit(TM_EN_OFFSET, TM_CTRL);
	}

	return RTS_ISP_OK;
}

static int isp_hw_set_tm(uint32_t isp_id, const isp_iq_tm_item_t *tm)
{
	int i, j, cal_result;
	float cal_tmp, tm_target;
	static float previous_target = -1.0f;
	int address_offset, addresstmp;

	static int tm_curve_ctrl[TM_CURVE_NUM] = {
		2, 3, 4, 5, 6, 7, 8
	};

	static int tm_bitbase[TM_BIT_RANK] = {
		4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576
	};

	static float tm_gamma[TM_CURVE_NUM] = {
		0.95, 0.6333, 0.475, 0.38, 0.3167, 0.2714, 0.2375
	};

	if (!tm)
		return -RTS_ISP_EINVAL;

	//Limit range
	tm_target = max(tm->value, TM_TARGET_MIN);
	tm_target = min(tm_target, TM_TARGET_MAX);

	isp_write_vreg_float(tm_target, VTM_TARGET);

	if(tm_target == previous_target)
		return RTS_ISP_OK;

	previous_target = tm_target;

	for (i=0; i<TM_CURVE_NUM; i+=1){
		tm_gamma[i] = (float) (14 - tm_target)/(2+i);
	}

	for (i=0; i < TM_CURVE_NUM; i+=1){
		for (j=0; j < tm_curve_ctrl[i]; j+=1){
			cal_tmp = ((float)tm_bitbase[j]) / (((float)pow(2,i)*16384));
			cal_tmp = 16384 * pow(cal_tmp,tm_gamma[i]);
			cal_result = ((int)cal_tmp);

			//Limit Max bound
			cal_result = min(cal_result, 16383);

			//Limit Min bound
			cal_result = max(cal_result, 4096);

			//Address offset
			if(i>=4){
				addresstmp = (i-3)*16;
			}
			else{
				addresstmp = 0;
			}

			address_offset = (256+(i*16))+(j*4)+addresstmp;

			isp_write_reg(cal_result, (TM_REG_BASE + address_offset));
		}
	}
	isp_write_reg(1, TM_REG_LOAD);

	return RTS_ISP_OK;
}

static int isp_hw_set_edge_thd_long(uint32_t isp_id, const isp_iq_tm_item_t *tm)
{
	int i;
	int address_offset;
	//int edge_cal_tmp;

	if (!tm || ARRAY_SIZE(tm->long_luma_thd) != EDGE_LUMA_THD_NUM)
		return -RTS_ISP_EINVAL;

	//Long_Luma_THD
	for (i=0; i<EDGE_LUMA_THD_NUM; i+=1){
		address_offset = (0x20+(i*4)); 
		isp_write_reg(tm->long_luma_thd[i], (TM_REG_BASE + address_offset));
	}
	isp_write_reg(1, TM_REG_LOAD);

	return RTS_ISP_OK;
}

static int isp_hw_set_edge_thd_short(uint32_t isp_id, const isp_iq_tm_item_t *tm)
{
	int i;
	int address_offset;
	//int edge_cal_tmp;

	if (!tm || ARRAY_SIZE(tm->short_luma_thd) != EDGE_LUMA_THD_NUM)
		return -RTS_ISP_EINVAL;

	//Short_Luma_THD
	for (i=0; i<EDGE_LUMA_THD_NUM; i+=1){
		address_offset = (0x50+(i*4)); 
		isp_write_reg(tm->short_luma_thd[i], (TM_REG_BASE + address_offset));
	}
	isp_write_reg(1, TM_REG_LOAD);	

	return RTS_ISP_OK;
}

static int isp_hw_set_edge_param(uint32_t isp_id, const isp_iq_tm_item_t *tm)
{
	int edge_cal_tmp;

	if (!tm)
		return -RTS_ISP_EINVAL;

	//Luma_Offset
	edge_cal_tmp = (tm->long_luma_offset <<8);
	edge_cal_tmp = edge_cal_tmp + tm->short_luma_offset;
	isp_write_reg(edge_cal_tmp, (TM_REG_BASE + 0x10));

	//Direction Factor
	edge_cal_tmp = (tm->direct_factor_k2 <<16);
	edge_cal_tmp = edge_cal_tmp + (tm->direct_factor_k1 <<8);
	edge_cal_tmp = edge_cal_tmp + tm->direct_factor_k0;
	isp_write_reg(edge_cal_tmp, (TM_REG_BASE + 0x08));

	//Direction Weight
	edge_cal_tmp = (tm->direct_weight_w1 <<8);
	edge_cal_tmp = edge_cal_tmp + tm->direct_weight_w0;  
	isp_write_reg(edge_cal_tmp, (TM_REG_BASE + 0x0c));

	//Rate Max and Min
	edge_cal_tmp = (tm->rate_min <<16);
	edge_cal_tmp = edge_cal_tmp + tm->rate_max;  
	isp_write_reg(edge_cal_tmp, (TM_REG_BASE + 0x1c));

	isp_write_reg(1, TM_REG_LOAD);	

	return RTS_ISP_OK;
}

static const struct isp_hw_tm_ops hw_tm_ops = {
	.set_enable = isp_hw_enable_tm,
	.set_target = isp_hw_set_tm,
	.set_edge_thd_long = isp_hw_set_edge_thd_long,
	.set_edge_thd_short = isp_hw_set_edge_thd_short,
	.set_edge_param = isp_hw_set_edge_param,
};

const struct isp_hw_tm_ops *isp_hw_tm_get_ops(void)
{
	return &hw_tm_ops;
}

