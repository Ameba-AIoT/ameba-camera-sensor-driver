/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Kelsey Chen <kelsey_chen@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <isp_algo_param.pb.h>
#include <rts_isp_tuning.h>

void print_all_tuning_param(isp_algo_param_t algo_param)
{
	printf("algo tuning param ae:\n");
	printf("\ty_mean: %d\n", algo_param.ae.y_mean);
	printf("\tgain: %f\n", algo_param.ae.gain);
	printf("\texposure: %f\n", algo_param.ae.exposure);
	printf("\tsaturated_ratio: %f\n", algo_param.ae.saturated_ratio);
	printf("\tae_ctrl_force: %d\n", algo_param.ae.ae_ctrl_force);

	printf("algo tuning param awb:\n");
	printf("\tgray gain: %d, %d\n", algo_param.awb.gray_gain.x,
					algo_param.awb.gray_gain.y);
	printf("\tgreen gain: %d, %d\n", algo_param.awb.green_gain.x,
					 algo_param.awb.green_gain.y);
	printf("\trough gain: %d, %d\n", algo_param.awb.rough_gain.x,
					 algo_param.awb.rough_gain.y);
	printf("\tresult gain: %d, %d\n", algo_param.awb.result_gain.x,
					  algo_param.awb.result_gain.y);
	printf("\tcolor temperature: %d\n", (int)algo_param.awb.color_temperature);
	printf("\tawb_ctrl_force: %d\n", algo_param.awb.awb_ctrl_force);

	printf("algo tuning param flick:\n");
	printf("\tcurrent frequence:%d\n", (int)algo_param.flick.cur_freq);
	printf("\tinsert dummy line:%d\n", algo_param.flick.insert_dummy_line);

	printf("algo tuning param wdr:\n");
	printf("\tday night is:%d\n", (int)algo_param.wdr.day_night);
	printf("\tlow bound is:%d\n", algo_param.wdr.low_bound);
	printf("\twdr level is:%d\n", algo_param.wdr.wdr_level);

	printf("algo tuning param blc:\n");
	printf("\tct index is:%d\n", algo_param.blc.ct_index);
	printf("\tgain index is:%d\n", algo_param.blc.gain_index);
	printf("\tht index is:%d\n", algo_param.blc.ht_index);
}

int cmd_test_tuning_param(int argc, char *argv[])
{
	int ret = RTS_ISP_OK;
	struct rts_isp_tuning_param *param;
	isp_algo_param_t algo_param;
	pb_ostream_t ostream;
	pb_istream_t istream;

	ret = rts_isp_tuning_query_param(ISP0, &param);
	if (ret) {
		rts_isp_perror(ret, "query algo tuning param fail");
		return ret;
	}

	param->type = RTS_ISP_TUNING_PARAM_ALL;
	ret = rts_isp_tuning_get_param(ISP0, param);
	if (ret) {
		rts_isp_perror(ret, "get tuning algo param fail");
		goto out;
	}

	istream = pb_istream_from_buffer(param->buf, param->len);
	if (!pb_decode(&istream, isp_algo_param_t_fields, &algo_param)) {
		ret = -RTS_ISP_EPROTOBUF;
		rts_isp_perror(ret, "decode protobuf fail");
		goto out;
	}

	print_all_tuning_param(algo_param);

	algo_param.ae.ae_ctrl_force = 1;
	algo_param.awb.awb_ctrl_force = 1;
	ostream = pb_ostream_from_buffer(param->buf, param->max_len);
	if (!pb_encode(&ostream, isp_algo_param_t_fields, &algo_param)) {
		ret = -RTS_ISP_EPROTOBUF;
		rts_isp_perror(ret, "encode protobuf fail");
		goto out;
	}

	param->len = ostream.bytes_written;

	ret = rts_isp_tuning_set_param(ISP0, param);
	if (ret) {
		rts_isp_perror(ret, "set algo tuning param fail");
		goto out;
	}
out:
	rts_isp_tuning_release_param(ISP0, param);
	return ret;
}


