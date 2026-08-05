/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2018 Grant Shen <grant_shen@realsil.com.cn>
 */

#include <fcntl.h>
#include <strings.h>
#include <sys/stat.h>
#include <isp_top.h>
#include <isp_log.h>
#include <isp_utils.h>
#include <isp_mem.h>
#include <isp_core.h>
#include <isp_iq.h>
#include <pb_decode.h>
#include <isp_debug.h>
#include "rt_code.h"
#define ISP_IQ_MAGIC_NUM 0x49515442 /* 'I', 'Q', 'T', 'B' */
//#define ISP_IQ_VERSION 0x00000001
#define ISP_IQ_MAJOR_VERSION 0x0001
#define ISP_IQ_TABLE_SIZE_MAX (128 * 1024)

#define ISP_PACKED_IQ_MAGIC_NUM 0x504B4951 /* 'P', 'K', 'I', 'Q' */
#define ISP_PACKED_IQ_MAJOR_VERSION 0x0
#define ISP_PACKED_IQ_MINOR_VERSION 0x2

#define ISP_ALGO_PARAM_MAGIC_NUM 0x414C474F
#define ISP_ALGO_PARAM_VERSION 0x00010006

struct isp_packed_iq_header {
	uint32_t length;
	uint32_t magic;
	uint32_t version;
	uint64_t timestamp;
	uint8_t group_num;
	uint8_t def_group;
	uint8_t binary_num;
	uint8_t cus_version;
	uint8_t reserved[12];
} __attribute__((packed));

struct isp_packed_iq_group {
	uint8_t name[RTS_ISP_NAME_LEN];
	uint8_t day_id;
	uint8_t night_id;
	uint8_t other_id;
	uint8_t reserved[13];
} __attribute__((packed));

struct isp_packed_iq_binary {
	uint32_t offset;
	uint32_t length;
	uint8_t extend_length;
	uint8_t reserved[7];
} __attribute__((packed));

static void iq_reset_info(struct isp_iq *iq)
{
	iq->id = 0;
	iq->entry_bits = 0;
	iq->bfr = NULL;
	isp_free(iq->entries);
	isp_free(iq->binaries);
}

static int iq_check_set_packed_iq(struct isp_iq *iq, const char *path)
{
	int i;
	//int fd;
	int ret = RTS_ISP_OK;
	//struct stat iq_stat;
	struct isp_packed_iq_header header;
	struct isp_packed_iq_group group;
	struct isp_packed_iq_binary binary;
	char *ptr = (char*)path;

	iq_reset_info(iq);

	//fd = open(path, O_RDONLY);
	//if (fd < 0)
	//	return -errno;
	//ret = fstat(fd, &iq_stat);
	//if (ret) {
	//	ret = -errno;
	//	goto out;
	//}
	memcpy(&header, ptr, sizeof(header)); ptr += sizeof(header);
	if (header.magic != ISP_PACKED_IQ_MAGIC_NUM ||
	    header.group_num > _MAX_ISP_IQ_NUM ||
	    header.binary_num > _MAX_ISP_IQ_BINARY_NUM ||
	    header.def_group >= header.group_num) {
		ret = -RTS_ISP_EINVAL;
		isp_error("iq header error\n");
		goto out;
	}

	iq->packed_version.minor = header.version & 0xffff;
	iq->packed_version.major = (header.version >> 16) & 0xffff;
	if (iq->packed_version.major != ISP_PACKED_IQ_MAJOR_VERSION) {
		ret = -RTS_ISP_EINVAL;
		isp_error("iq packed_version.major error %d \n", iq->packed_version.major);
		goto out;
	}

	iq->id = header.def_group;
	iq->cus_version = header.cus_version;
	//memcpy(&iq->bfr, &path+4, sizeof(void*));
	iq->bfr = (void*) path + 4;
	isp_calloc_array(iq->entries, header.group_num);
	isp_calloc_array(iq->binaries, header.binary_num);
	if (!iq->entries || !iq->binaries) {
		ret = -RTS_ISP_ENOMEM;
		goto out;
	}
#ifdef _IQ_LOG_
	printf("length 0x%08x pk_verison %d cur_ver%d group %d binary %d \r\n", header.length, iq->packed_version, iq->cus_version, header.group_num, header.binary_num);
#endif
	for (i = 0; i < header.group_num; i++) {
		memcpy(&group, ptr, sizeof(group)); ptr += sizeof(group);
		if (iq->entry_bits & (1 << i) ||
		    group.day_id >= header.binary_num ||
		    group.night_id >= header.binary_num) {
			ret = -RTS_ISP_EINVAL;
			goto out;
		}
		iq->entry_bits |= 1 << i;
		memcpy(iq->entries[i].name, group.name, RTS_ISP_NAME_LEN);
		iq->entries[i].day_id = group.day_id;
		iq->entries[i].night_id = group.night_id;

		if (group.other_id < header.binary_num &&
			iq->packed_version.major == 0 &&
			iq->packed_version.minor >= 2) {
			iq->entries[i].other_id = group.other_id;
		} else {
			printf("other_id or packed_iq version isn't valid\n");
			iq->entries[i].other_id = -1;
		}
	}
	for (i = 0; i < header.binary_num; i++) {
		memcpy(&binary, ptr, sizeof(binary)); ptr += sizeof(binary);
		if (binary.offset + binary.length > header.length) {
			ret = -RTS_ISP_EINVAL;
			goto out;
		}
		iq->binaries[i].offset = binary.offset;
		iq->binaries[i].length = binary.length;
		//isp_info("%s binary %d offset %d length %d\r\n", __func__, i, iq->binaries[i].offset, iq->binaries[i].length);

	}
	ret = RTS_ISP_OK;
out:
	//isp_close(fd);
	if (ret) {
		isp_error("%s error \r\n", __func__);
		iq_reset_info(iq);
	}

	return ret;
}

int isp_iq_init(struct isp_iq *iq)
{
	if (!iq)
		return -RTS_ISP_EINVAL;
	memset(iq, 0, sizeof(*iq));
	iq->algo_param.header.magic = ISP_ALGO_PARAM_MAGIC_NUM;
	iq->algo_param.header.version = ISP_ALGO_PARAM_VERSION;
	return RTS_ISP_OK;
}

int isp_iq_cleanup(struct isp_iq *iq)
{
	if (!iq)
		return -RTS_ISP_EINVAL;
	iq_reset_info(iq);
	pb_release(isp_iq_table_t_fields, iq->iq_table);
	isp_free(iq->iq_table);
	memset(iq, 0, sizeof(*iq));
	return RTS_ISP_OK;
}

int isp_iq_register(struct isp_iq *iq, const char *path)
{
	if (!iq || !path)
		return -RTS_ISP_EINVAL;

	if (strlen(path) >= RTS_ISP_PATH_LEN)
		return -RTS_ISP_ERANGE;

	return iq_check_set_packed_iq(iq, path);
}
#if 0
static void show_hys_bounds(isp_iq_hysteresis_bounds_t *bounds)
{
	isp_info("%s 0x%08x def %d\r\n", __func__, bounds, bounds->def_index, bounds->bounds_count);
	for (int i=0; i<bounds->bounds_count; i++ ) {
		isp_info("%d 0x%08x  enter %d exit %d \r\n", i, &(bounds->bounds[i]), bounds->bounds[i].enter_th, bounds->bounds[i].exit_th);
	}
}

static void show_bounds(isp_iq_bounds_t *bounds)
{
	isp_info("%s 0x%08x def %d\r\n", __func__, bounds, bounds->def_index, bounds->bounds_count);
	for (int i=0; i<bounds->bounds_count; i++ ) {
		isp_info("%d bound 0x%08x %d \r\n", i, &(bounds->bounds[i]), bounds->bounds[i]);
	}
}
#endif

int isp_iq_apply_awb_calb(isp_iq_awb1_t *awb, struct isp_iq_calb_awb *awb_calb)
{
	int i;

	/*
	Patch the following item by calibration data
	repeated isp_iq_point_t ct = 3;
	repeated isp_iq_point_t white_area_up = 8;
	repeated isp_iq_point_t white_area_down = 9;
	repeated isp_iq_point_t gray_area_up = 10;
	repeated isp_iq_point_t gray_area_down = 11;
	*/

	if (!awb || !awb_calb)
		return -APPLY_AWB_CALB_FAILED;

	for (i = 0; i < awb->ct_count; i++) {
		awb->ct[i].x += awb_calb->x_offset;
		awb->ct[i].y += awb_calb->y_offset;
	}

	for (i = 0; i < awb->white_area_up_count; i++) {
		awb->white_area_up[i].x += awb_calb->x_offset;
		awb->white_area_up[i].y += awb_calb->y_offset;
	}

	for (i = 0; i < awb->white_area_down_count; i++) {
		awb->white_area_down[i].x += awb_calb->x_offset;
		awb->white_area_down[i].y += awb_calb->y_offset;
	}

	for (i = 0; i < awb->gray_area_up_count; i++) {
		awb->gray_area_up[i].x += awb_calb->x_offset;
		awb->gray_area_up[i].y += awb_calb->y_offset;
	}

	for (i = 0; i < awb->gray_area_down_count; i++) {
		awb->gray_area_down[i].x += awb_calb->x_offset;
		awb->gray_area_down[i].y += awb_calb->y_offset;
	}
	return 0;
}

#define MLSC_MATRIX_COUNT 1536

int isp_iq_apply_mlsc_calb(isp_iq_mlsc_t *mlsc, struct isp_iq_calb_mlsc *mlsc_calb)
{
	int i;

	if (!mlsc || !mlsc_calb || mlsc->matrix_r_count != MLSC_MATRIX_COUNT ||
	    mlsc->matrix_g_count != MLSC_MATRIX_COUNT ||
	    mlsc->matrix_b_count != MLSC_MATRIX_COUNT)
		return -APPLY_MLSC_CALB_FAILED;

	for (i = 0; i < mlsc->matrix_r_count; i++) {
		mlsc->matrix_r[i] = mlsc_calb->matrix_r[i];
		mlsc->matrix_g[i] = mlsc_calb->matrix_g[i];
		mlsc->matrix_b[i] = mlsc_calb->matrix_b[i];
	}

	return 0;
}

int isp_iq_apply_nlsc_calb(isp_iq_nlsc_t *nlsc, struct isp_iq_calb_nlsc *nlsc_calb)
{
	if (!nlsc || !nlsc_calb)
		return -APPLY_NLSC_CALB_FAILED;

	nlsc->common.r_center.x = nlsc_calb->r_center.x;
	nlsc->common.r_center.y = nlsc_calb->r_center.y;
	nlsc->common.g_center.x = nlsc_calb->g_center.x;
	nlsc->common.g_center.y = nlsc_calb->g_center.y;
	nlsc->common.b_center.x = nlsc_calb->b_center.x;
	nlsc->common.b_center.y = nlsc_calb->b_center.y;

	if (nlsc_calb->curve_ratio > 1 || nlsc_calb->curve_ratio < 0) {
		printf("%s: curve_ratio is invalid. Bypass patching curve\n",
		       __func__);
		return 0;
	}

	for (size_t i = 0; i < nlsc->common.r_curve_count; i++) {
		nlsc->common.r_curve[i] = (max(nlsc->common.r_curve[i], 128) - 128) *
						  nlsc_calb->curve_ratio + 128;
		nlsc->common.g_curve[i] = (max(nlsc->common.g_curve[i], 128) - 128) *
						  nlsc_calb->curve_ratio + 128;
		nlsc->common.b_curve[i] = (max(nlsc->common.b_curve[i], 128) - 128) *
						  nlsc_calb->curve_ratio + 128;
	}

	return 0;
}

int isp_iq_apply_calibration(struct isp_iq *iq, isp_iq_table_t *iq_table)
{
	int ret = 0;

	if (iq->calb_data.enable & IQ_CALB_EN_AWB) {
		//printf("apply AWB calibration data\n");
		ret = isp_iq_apply_awb_calb(&iq_table->awb->algo.awb1, &iq->calb_data.awb);
		if (ret)
			return ret;
	}

	if (iq->calb_data.enable & IQ_CALB_EN_MLSC) {
		//printf("apply MLSC calibration data\n");
		ret = isp_iq_apply_mlsc_calb(iq_table->mlsc, &iq->calb_data.mlsc);
		if (ret)
			return ret;
	}

	if (iq->calb_data.enable & IQ_CALB_EN_NLSC) {
		//printf("apply NLSC calibration data\n");
		ret = isp_iq_apply_nlsc_calb(iq_table->nlsc,
					     &iq->calb_data.nlsc);
		if (ret)
			return ret;
	}
	if ((iq->calb_data.enable & 0xF0) == 0xF0 ) {

	printf("awb_calb offset %d %d \n",
			iq->calb_data.awb.x_offset, iq->calb_data.awb.y_offset);

	printf("MLSC index0 r 0x%02x g 0x%02x b 0x%02x \n",
					iq->calb_data.mlsc.matrix_r[0],
					iq->calb_data.mlsc.matrix_g[0],
					iq->calb_data.mlsc.matrix_b[0]);
	printf("MLSC index768 r 0x%02x g 0x%02x b 0x%02x \n",
					iq->calb_data.mlsc.matrix_r[768],
					iq->calb_data.mlsc.matrix_g[768],
					iq->calb_data.mlsc.matrix_b[768]);
	printf("MLSC index1535 r 0x%02x g 0x%02x b 0x%02x \n",
					iq->calb_data.mlsc.matrix_r[1535],
					iq->calb_data.mlsc.matrix_g[1535],
					iq->calb_data.mlsc.matrix_b[1535]);

		printf("nlsc_calb r %d %d g %d %d b %d %d %.4f\n",
				iq->calb_data.nlsc.r_center.x,
				iq->calb_data.nlsc.r_center.y,
				iq->calb_data.nlsc.g_center.x,
				iq->calb_data.nlsc.g_center.y,
				iq->calb_data.nlsc.b_center.x,
				iq->calb_data.nlsc.b_center.y,
				iq->calb_data.nlsc.curve_ratio);
	}

	return 0;
}

uint32_t pb_istream_from_buffer_time= 0, pb_decode_time = 0;
volatile uint32_t switch_start_ae_count = 0;
volatile uint32_t ae_on = 0;
volatile uint32_t awb_on = 0;
int isp_iq_load_from_file(struct isp_iq *iq)
{
	int ret;
	int fd = -1;
	void *bfr;
	uint32_t offset;
	uint32_t length;
	uint8_t *buffer = NULL;
	pb_istream_t stream;
	isp_iq_table_t *iq_table;
	isp_iq_table_t *tmp;
	//uint32_t *buffer32;
	//int i,j;
	int table_size;

	if (!isp_calloc_item(iq_table)) {
		isp_error("isp_calloc_item \r\n");
		return ERR_ID_ISP_IQ_MALLOC_FAIL;
	}


	if (!isp_test_bit(iq->entry_bits, iq->id)) {
		ret = -RTS_ISP_ENOTREADY;
		isp_error("isp_test_bit \r\n");
		goto out;
	}
	bfr = iq->bfr;
	if (iq->dn == RTS_ISP_DAY) {
		offset = iq->binaries[iq->entries[iq->id].day_id].offset;
		length = iq->binaries[iq->entries[iq->id].day_id].length;
	} else if(iq->dn == RTS_ISP_NIGHT) {
		offset = iq->binaries[iq->entries[iq->id].night_id].offset;
		length = iq->binaries[iq->entries[iq->id].night_id].length;
	} else {
		if (iq->entries[iq->id].other_id < 0) {
			isp_error("other_id is not supported.\n");
			ret = ERR_ID_ISP_IQ_ID_NOT_SUPPORT;
			goto out;
		}
		offset = iq->binaries[iq->entries[iq->id].other_id].offset;
		length = iq->binaries[iq->entries[iq->id].other_id].length;
	}
//#ifdef _IQ_LOG_

//#endif
//	fd = open(path, O_RDONLY);
//	if (fd < 0) {
//		ret = -errno;
//		goto out;
//	}
	buffer = isp_malloc(length);
	if (!buffer) {
		isp_error("isp_malloc \r\n");
		ret = ERR_ID_ISP_IQ_MALLOC_FAIL;
		goto out;
	}
//	ret = lseek(fd, offset, SEEK_SET);
//	if (ret < 0) {
//		ret = -errno;
//		goto out;
//	}
//	ret = read(fd, buffer, length);
//	if (ret < 0) {
//		ret = -errno;
//		goto out;
//	} else if (ret != (int)length) {
//		ret = -RTS_ISP_EPROTOBUF;
//		goto out;
//	}
	//memset(buffer, 0, 500*1024);

	memcpy(buffer, (void *)((uint32_t)bfr+offset), length);
	//iq_load_from_file_time = hal_read_curtime_us();
	//buffer32 = (uint32_t *)buffer;
	//isp_info("0x%08x 0x%08x 0x%08x 0x%08x \r\n", buffer32[0], buffer32[1], buffer32[2], buffer32[3]);
	//isp_info("0x%08x 0x%08x 0x%08x 0x%08x \r\n", buffer32[length/4-4], buffer32[length/4-3], buffer32[length/4-2], buffer32[length/4-1]);

	stream = pb_istream_from_buffer(buffer, length);

	table_size = xPortGetFreeHeapSizeExt(0);
	pb_istream_from_buffer_time = hal_read_curtime_us();

	if (!pb_decode(&stream, isp_iq_table_t_fields, iq_table)) {
		ret = ERR_ID_ISP_IQ_PB_DECODE_FAIL;
		isp_error("pb_decode error %s\r\n", stream.errmsg);
		goto out;
	}

	pb_decode_time = hal_read_curtime_us();


	table_size = table_size - xPortGetFreeHeapSizeExt(0) + sizeof(isp_iq_table_t);

	printf("pack_v 0x%04x 0x%04x cus_v %d iq_id %d dn %d day %d night %d other %d offset %d length %d iq_size %d \r\n",
	iq->packed_version.major, iq->packed_version.minor, iq->cus_version, iq->id, iq->dn, iq->entries[iq->id].day_id, iq->entries[iq->id].night_id,  iq->entries[iq->id].other_id, offset, length, table_size);


	if (iq_table->header->magic != ISP_IQ_MAGIC_NUM ||
	    iq_table->header->version >>16 != ISP_IQ_MAJOR_VERSION) {
		isp_error("iq magic or version does not match 0x%08x 0x%08x \r\n", iq_table->header->magic, iq_table->header->version);
		ret = ERR_ID_ISP_IQ_MAGIC_VERSION_FAIL;
		goto out;
	}

	if (iq->calb_data.enable) {
		ret = isp_iq_apply_calibration(iq, iq_table);

		if (ret) {
			isp_error("Apply calibration failed, ret = %d\n", ret);
			ret = ERR_ID_ISP_IQ_APPLY_CALIBRATION_FAIL;
			goto out;
		}
		printf("apply calibration en_flag %d \r\n",iq->calb_data.enable);

	}

#if 0
	isp_iq_blc_ct_item_t *blc_ct_item;

	isp_info("blc 0x%08x 0x%08x 0x%08x 0x%08x \r\n", iq_table->blc, &(iq_table->blc->dyn_ct),  &(iq_table->blc->dyn_gain), &(iq_table->blc->dyn_ht));
	isp_info("blc dyn_ct %d ct_items_count %d dyn_gain %d \r\n", iq_table->blc->dyn_ct.enable, iq_table->blc->dyn_ct.ct_items_count, iq_table->blc->dyn_gain.enable);
	show_hys_bounds(&(iq_table->blc->dyn_ct.bounds));

	for (i=0; i<iq_table->blc->dyn_ct.ct_items_count; i++) {
		blc_ct_item = &(iq_table->blc->dyn_ct.ct_items[i]);
		isp_info("0x%08x based_on_et_gain %d offsets_count %d\r\n", blc_ct_item, blc_ct_item->based_on_et_gain,blc_ct_item->offsets_count);
		show_bounds(&(blc_ct_item->bounds));
		for (j=0; j<blc_ct_item->offsets_count; j++) {
			isp_info("%d gb %d gr %d  b %d r %d\r\n", blc_ct_item->offsets[j].gr[0], blc_ct_item->offsets[j].gb[0], blc_ct_item->offsets[j].r[0], blc_ct_item->offsets[j].b[0]);
		}
	}

	isp_iq_blc_dyn_ht_t *dyn_ht = &(iq_table->blc->dyn_ht);
	isp_info("blc dyn_ht 0x%08x based_on_gain %d enable offsets_count %d\r\n", dyn_ht, dyn_ht->based_on_gain, dyn_ht->enable, dyn_ht->offsets_count);
	show_bounds(&(dyn_ht->bounds));
	for (j=0; j<dyn_ht->offsets_count; j++) {
		isp_info("%d gb %d gr %d  b %d r %d\r\n", dyn_ht->offsets[j].gr[0], dyn_ht->offsets[j].gb[0], dyn_ht->offsets[j].r[0], dyn_ht->offsets[j].b[0]);
	}

	isp_info("blc %d mlsc %d nlsc %d gamma %d \r\n", iq_table->blc->dyn_ct.ct_items_count, iq_table->mlsc->matrix_r_count, iq_table->nlsc->common.b_curve_count, iq_table->gamma->dyn_gain.gain_items_count);
	isp_info("ae %d awb %d af %d ccm %d \r\n", iq_table->ae->which_algo, iq_table->awb->which_algo, iq_table->af->which_algo, iq_table->ccm->dyn_ct.ct_items_count);
	isp_info("wdr %d ygc %d uvtune %d spe %d \r\n", iq_table->wdr->which_algo, iq_table->ygc->dyn_gain.gain_items_count, iq_table->uvtune->dyn_ct.ct_items_count, iq_table->spe->uv_offset.items_count);
	isp_info("texture static %d dynamic %d dynamic bound %d \r\n", iq_table->texture->static_regs.values_count, iq_table->texture->dynamic_regs.values_count, iq_table->texture->dynamic_regs.bounds.bounds_count);

	isp_info("ygc->dyn_gain.bounds.bounds %d %d %d \r\n", iq_table->ygc->dyn_gain.bounds.bounds[0], iq_table->ygc->dyn_gain.bounds.bounds[1], iq_table->ygc->dyn_gain.bounds.bounds[2]);
#endif

	ret = RTS_ISP_OK;
	tmp = iq->iq_table;
	iq->iq_table = iq_table;
	iq_table = tmp;

#if 0
	iq->iq_table->ae->algo.ae1.switch_start_ae_count = 4;
	iq->iq_table->awb->algo.awb1.switch_start_awb_count = 3;
	iq->iq_table->ae->algo.ae1.ae_intp_delay_frame = 3;
	iq->iq_table->awb->algo.awb1.awb_intp_delay_frame = 3;

	iq->iq_table->ae->algo_delay = 0;
	iq->iq_table->awb->algo_delay = 0;

#endif

	printf("Ver 0x%08x Fast3A Cnt AE %d AWB %d period AE %d AWB %d delay %d %d \n", iq->iq_table->header->version, iq->iq_table->ae->algo.ae1.switch_start_ae_count, iq->iq_table->awb->algo.awb1.switch_start_awb_count,
			   iq->iq_table->ae->algo.ae1.ae_intp_delay_frame, iq->iq_table->awb->algo.awb1.awb_intp_delay_frame, iq->iq_table->ae->algo_delay, iq->iq_table->awb->algo_delay);
	switch_start_ae_count = iq->iq_table->ae->algo.ae1.switch_start_ae_count;
	ae_on = iq->iq_table->ae->enable;
	awb_on = iq->iq_table->awb->enable;

out:
	isp_free(buffer);
	pb_release(isp_iq_table_t_fields, iq_table);
	isp_free(iq_table);

	if (ret) {
		isp_error("%s load iq file fail %d \r\n", __func__, ret);
	}
#if 0	
	isp_iq_awb1_t awb_t =  iq->iq_table->awb->algo.awb1;
	printf("awb1_green_t %d %d %d %d %d %d %d %d %d \r\n", (uint32_t)awb_t.green.enable, (uint32_t)awb_t.green.gray_thd, (uint32_t)awb_t.green.enter_green_thd, (uint32_t)awb_t.green.exit_green_thd, (uint32_t)awb_t.green.x_min, (uint32_t)awb_t.green.y_min,  (uint32_t)awb_t.green.x_max, (uint32_t)awb_t.green.y_max, (uint32_t)awb_t.green.b_delta);
	printf("awb1_green_t %f %f %f %f %f %f %f %f \r\n", awb_t.green.k_green_est, awb_t.green.k_gray_est, awb_t.green.d_min, awb_t.green.d_def, awb_t.green.d_max, awb_t.green.b_max,  awb_t.green.b_def, awb_t.green.b_min);
	printf("d50 %d %d d65 %d %d \r\n", (uint32_t)awb_t.green.d50.x, (uint32_t)awb_t.green.d50.y, (uint32_t)awb_t.green.d65.x, (uint32_t)awb_t.green.d65.y);

	isp_iq_awb1_rough_limit_t r_limit = awb_t.config.rough;
	printf("rough_limit %d %d %d %d %d %d %d %d %d %d %d %d\r\n", (uint32_t)r_limit.y_min, (uint32_t)r_limit.y_max, (uint32_t)r_limit.r_min, (uint32_t)r_limit.r_max,(uint32_t)r_limit.g_min, (uint32_t)r_limit.g_max, (uint32_t)r_limit.b_min, (uint32_t)r_limit.b_max, (uint32_t)r_limit.rg_min, (uint32_t)r_limit.rg_max, (uint32_t)r_limit.bg_min, (uint32_t)r_limit.bg_max);

	isp_iq_awb1_fine_limit_t f_limit = awb_t.config.fine;
	printf("fine_limit %d %d %d %d %d %d \r\n", (uint32_t)f_limit.y_min, (uint32_t)f_limit.y_max,  (uint32_t)f_limit.rg_min, (uint32_t)f_limit.rg_max, (uint32_t)f_limit.bg_min, (uint32_t)f_limit.bg_max);


	isp_iq_awb1_illums_t illums = awb_t.config.illums;
	printf("illums limit %d %d %d %d %d %d \r\n", (uint32_t)illums.rg_min, (uint32_t)illums.rg_max, (uint32_t)illums.bg_min, (uint32_t)illums.bg_max, (uint32_t)illums.y_min, (uint32_t)illums.y_max);
	printf("illums rgain %d %d %d %d %d %d %d %d %d %d %d %d\r\n", (uint32_t)illums.r_gain[0], (uint32_t)illums.r_gain[1], (uint32_t)illums.r_gain[2], (uint32_t)illums.r_gain[3], (uint32_t)illums.r_gain[4], (uint32_t)illums.r_gain[5], (uint32_t)illums.b_gain[0], (uint32_t)illums.b_gain[1], (uint32_t)illums.b_gain[2], (uint32_t)illums.b_gain[3], (uint32_t)illums.b_gain[4], (uint32_t)illums.b_gain[5]);
#endif 
#if 0
	isp_iq_awb1_t *p_awb_t =  &(iq->iq_table->awb->algo.awb1);
	p_awb_t->min_bright_th = 20;
#endif 

#if 0
	printf("header 0x%08x blc 0x%08x nlsc 0x%08x mlsc 0x%08x ae 0x%08x awb 0x%08x af 0x%08x ccm 0x%08x\r\n", \
	(uint32_t)iq->iq_table->header,\
    (uint32_t)iq->iq_table->blc,\
    (uint32_t)iq->iq_table->nlsc,\
    (uint32_t)iq->iq_table->mlsc,\
    (uint32_t)iq->iq_table->ae,\
    (uint32_t)iq->iq_table->awb,\
    (uint32_t)iq->iq_table->af,\
    (uint32_t)iq->iq_table->ccm );


	printf("gamma 0x%08x wdr 0x%08x ygc 0x%08x uvtune 0x%08x spe 0x%08x texture 0x%08x daynight 0x%08x high_temp 0x%08x \r\n", \
    (uint32_t)iq->iq_table->gamma,\
    (uint32_t)iq->iq_table->wdr,\
    (uint32_t)iq->iq_table->ygc,\
    (uint32_t)iq->iq_table->uvtune,\
    (uint32_t)iq->iq_table->spe,\
    (uint32_t)iq->iq_table->texture,\
    (uint32_t)iq->iq_table->daynight,\
    (uint32_t)iq->iq_table->high_temp,\
    (uint32_t)iq->iq_table->tm );
#endif
	isp_close(fd);

	return ret;
}

int isp_iq_is_ae_on(void)
{
	return ae_on;
}

int isp_iq_is_awb_on(void)
{
	return awb_on;
}

int isp_iq_change_table(struct isp_iq *iq, int id)
{
	int ret;
	int last_id;

	if (!iq || id >= _MAX_ISP_IQ_NUM || !isp_test_bit(iq->entry_bits, id))
		return -RTS_ISP_EINVAL;
	last_id = iq->id;
	iq->id = id;
	ret = isp_iq_load_from_file(iq);
	if (ret)
		iq->id = last_id;
	return ret;
}

int isp_iq_change_day_night(struct isp_iq *iq, int dn)
{
	int ret;
	int last_dn;

	if (!iq || dn < RTS_ISP_DAY || dn > RTS_ISP_DN_OTHER)
		return -RTS_ISP_EINVAL;
	last_dn = iq->dn;
	iq->dn = dn;
	ret = isp_iq_load_from_file(iq);
	if (ret)
		iq->dn = last_dn;
	return ret;
}

int isp_iq_reload_packed_iq(struct isp_iq *iq)
{
	int ret;
	int last_id;
	int last_bits;
	char *last_path;
	struct isp_iq_entry *last_entries;
	struct isp_iq_binary_desc *last_binaries;

	if (!iq)
		return -RTS_ISP_EINVAL;

	last_id = iq->id;
	last_bits = iq->entry_bits;
	last_path = iq->bfr - 4;
	last_entries = iq->entries;
	last_binaries = iq->binaries;
	iq->entries = NULL;
	iq->binaries = NULL;

	ret = iq_check_set_packed_iq(iq, last_path);
	if (ret)
		goto out;
	ret = isp_iq_load_from_file(iq);
out:
	if (ret) {
		iq_reset_info(iq);
		iq->id = last_id;
		iq->entry_bits = last_bits;
		memcpy(&iq->bfr, last_path, sizeof(void*));
		iq->entries = last_entries;
		iq->binaries = last_binaries;
	} else {
		isp_free(last_entries);
		isp_free(last_binaries);
	}
	return ret;
}

int isp_iq_get_hysteresis_bound(const isp_iq_hysteresis_bounds_t *bounds,
				int32_t value, int current_index)
{
	int index = current_index;

	if (!bounds || !bounds->bounds_count)
		return 0;
	while (index < bounds->bounds_count &&
	       value >= bounds->bounds[index].enter_th)
		index++;
	while (index > 0 && value < bounds->bounds[index - 1].exit_th)
		index--;
	return index;
}

/*
This function will return index of bounds. When the return index
is equal to bounds_count, the dyn_val is bigger than last bound.
*/
int isp_iq_get_bound(const isp_iq_bounds_t *bounds, int32_t value)
{
	int i;

	if (!bounds)
		return 0;

	for (i = 0; i < bounds->bounds_count; i++)
		if (value <= bounds->bounds[i])
			break;
	return i;
}

int isp_iq_check_hysteresis_bounds(const isp_iq_hysteresis_bounds_t *bounds,
				   uint32_t item_count)
{
	int i;

	if (!bounds)
		return -RTS_ISP_EINVAL;
	if (bounds->bounds_count + 1 != (int)item_count ||
	    bounds->def_index > bounds->bounds_count) {
		isp_error("%s bounds_count %d item_count %d def_index %d \r\n", __func__, bounds->bounds_count, item_count, bounds->def_index);
		return -RTS_ISP_EINVAL;
	}
	//isp_info("%s bounds_count %d item_count %d def_index %d \r\n", __func__, bounds->bounds_count, item_count, bounds->def_index);

	for (i = 0; i < bounds->bounds_count; i++) {
		if (bounds->bounds[i].enter_th < bounds->bounds[i].exit_th) {
			isp_error("%s %d enter_th %d exit_th %d \r\n", __func__,i, bounds->bounds[i].enter_th, bounds->bounds[i].exit_th);
			return -RTS_ISP_EINVAL;
		}
		//isp_info("%s %d enter_th %d exit_th %d \r\n", __func__,i, bounds->bounds[i].enter_th, bounds->bounds[i].exit_th);
	}

	for (i = 0; i < (int)(bounds->bounds_count - 1); i++) {
		if (bounds->bounds[i].enter_th >= bounds->bounds[i + 1].exit_th) {
			isp_error("%s %d enter_th %d exit_th %d \r\n", __func__,i, bounds->bounds[i].enter_th, bounds->bounds[i + 1].exit_th);
			return -RTS_ISP_EINVAL;
		}
	}

	return RTS_ISP_OK;
}

int isp_iq_check_bounds(const isp_iq_bounds_t *bounds, uint32_t item_count)
{
	int i;

	if (!bounds){
		isp_error("%s bounds \r\n", __func__);
		return -RTS_ISP_EINVAL;
	}
	//isp_info("%s bounds_count %d item_count %d def_index %d \r\n", __func__, bounds->bounds_count, item_count, bounds->def_index);

	//for (i = 0; i < bounds->bounds_count; i++)
	//		isp_info("bounds[%d] %d \r\n", i, bounds->bounds[i]);



	if (!bounds->bounds_count || bounds->bounds_count != item_count ||
	    bounds->def_index >= bounds->bounds_count) {
		isp_error("%s %d %d %d %d \r\n", __func__, bounds->bounds_count, item_count, bounds->def_index, bounds->bounds_count);
		return -RTS_ISP_EINVAL;
	}

	for (i = 0; i < (int)(bounds->bounds_count - 1); i++)
		if (bounds->bounds[i] > bounds->bounds[i + 1]) {
		//if (bounds->bounds[i] >= bounds->bounds[i + 1]) {
			isp_error("%s %d %d %d \r\n", __func__, i, bounds->bounds[i], bounds->bounds[i + 1]);
			return -RTS_ISP_EINVAL;
		}

	return RTS_ISP_OK;
}

#define ISP_IQ_GET_FUNC(type) \
const isp_iq_##type##_t *isp_iq_get_##type(uint32_t isp_id) \
{ \
	struct isp_iq *iq; \
	iq = isp_core_get_iq(isp_top_get_core(isp_id)); \
	if (!iq) \
		return NULL; \
	return iq->iq_table->type; \
}

ISP_IQ_GET_FUNC(blc);
ISP_IQ_GET_FUNC(nlsc);
ISP_IQ_GET_FUNC(mlsc);
ISP_IQ_GET_FUNC(ae);
ISP_IQ_GET_FUNC(awb);
ISP_IQ_GET_FUNC(af);
ISP_IQ_GET_FUNC(ccm);
ISP_IQ_GET_FUNC(gamma);
ISP_IQ_GET_FUNC(wdr);
ISP_IQ_GET_FUNC(ygc);
ISP_IQ_GET_FUNC(uvtune);
ISP_IQ_GET_FUNC(spe);
ISP_IQ_GET_FUNC(texture);
ISP_IQ_GET_FUNC(daynight);
ISP_IQ_GET_FUNC(high_temp);
ISP_IQ_GET_FUNC(tm);
ISP_IQ_GET_FUNC(snr);
ISP_IQ_GET_FUNC(md);

isp_algo_param_t *isp_iq_get_algo_param(uint32_t isp_id)
{
	struct isp_iq *iq;

	iq = isp_core_get_iq(isp_top_get_core(isp_id));
	if (!iq)
		return NULL;
	return &iq->algo_param;
}
