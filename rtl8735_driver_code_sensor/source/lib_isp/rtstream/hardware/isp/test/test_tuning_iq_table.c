/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2019 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */
#include <stdio.h>
#include <stdlib.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <isp_iq_table.pb.h>
#include <rts_isp_tuning.h>

#define ISP_IQ_MAGIC_NUM 0x49515442 /* 'I', 'Q', 'T', 'B' */
#define TEST(x) ({ \
	if (!(x)) { \
		fprintf(stderr, "Test " #x " failed.\n"); \
		status = false; \
	} \
})

bool check_iq_table(isp_iq_table_t *iq)
{
	bool status = true;

	TEST(iq->header->magic == ISP_IQ_MAGIC_NUM);

	return status;
}

int cmd_test_tuning_iq_table(int argc, char *argv[])
{
	int ret;
	struct rts_isp_tuning_iq *tuning_iq;
	isp_iq_table_t iq;
	pb_ostream_t ostream;
	pb_istream_t istream;

	ret = rts_isp_tuning_query_iq(ISP0, &tuning_iq);
	if (ret) {
		rts_isp_perror(ret, "test query tuning iq fail");
		return ret;
	}

	tuning_iq->type = RTS_ISP_TUNING_IQ_TABLE_ALL;
	ret = rts_isp_tuning_get_iq(ISP0, tuning_iq);
	if (ret) {
		rts_isp_perror(ret, "test get tuning iq fail");
		goto out;
	}

	istream = pb_istream_from_buffer(tuning_iq->buf, tuning_iq->len);
	if (!pb_decode(&istream, isp_iq_table_t_fields, &iq)) {
		ret = -RTS_ISP_EPROTOBUF;
		rts_isp_perror(ret, "test decode fail");
		goto out;
	}

	if (!check_iq_table(&iq)) {
		ret = -RTS_ISP_EINVAL;
		rts_isp_perror(ret, "test check get tuning iq fail");
		goto out;
	}
	printf("check iq table right\n");

	iq.ae->algo.ae1.y_mean_target = 150 * 4;
	printf("set ae target to 150, please change the scene!\n");
	printf("than the brightness will be brighter!\n");

	ostream = pb_ostream_from_buffer(tuning_iq->buf, tuning_iq->max_len);
	if (!pb_encode(&ostream, isp_iq_table_t_fields, &iq)) {
		ret = -RTS_ISP_EPROTOBUF;
		rts_isp_perror(ret, "test encode fail");
		goto out;
	}
	tuning_iq->len = ostream.bytes_written;

	ret = rts_isp_tuning_set_iq(ISP0, tuning_iq);
	if (ret) {
		rts_isp_perror(ret, "test set tuning iq fail");
		goto out;
	}

out:
	pb_release(isp_iq_table_t_fields, &iq);
	rts_isp_tuning_release_iq(ISP0, tuning_iq);
	return ret;
}
