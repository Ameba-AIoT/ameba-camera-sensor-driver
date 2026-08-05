#ifndef _ISP_STATIS_H_INC_
#define _ISP_STATIS_H_INC_

#include <rts_camera_isp_info.h>
#include <rts_isp_geom.h>
#include <isp_algo.h>

struct isp_statis_raw_buf_offset {
	uint16_t offset;
	uint16_t r_offset;
	uint16_t gr_offset;
	uint16_t gb_offset;
	uint16_t b_offset;
	uint16_t y_offset;
	uint16_t rg_offset;
	uint16_t bg_offset;
	uint16_t pixels_offset;
	uint16_t size;
};

struct isp_statis_awb_buf_offset {
	uint16_t offset;
	uint16_t r_offset;
	uint16_t g_offset;
	uint16_t b_offset;
	uint16_t y_offset;
	uint16_t rg_offset;
	uint16_t bg_offset;
	uint16_t pixels_offset;
	uint16_t size;
};

struct isp_statis_ae_hdr_buf_offset {
	uint16_t y_offset;
	uint16_t hist_offset;
};

struct isp_statis_ae_buf_offset {
	uint16_t offset;
	uint16_t hdr_offset;
	uint16_t y_offset;
	uint16_t hist_offset;
	struct isp_statis_ae_hdr_buf_offset hdr[RTS_ISP_HDR_CHAN_MAX];
	uint16_t size;
	uint16_t hdr_size;
};

struct isp_statis_af_buf_offset {
	uint16_t offset;
	uint16_t edge_offset;
	uint16_t size;
};

struct isp_statis_y_buf_offset {
	uint16_t offset;
	uint16_t y_offset;
	uint16_t hist_offset;
	uint16_t size;
};

struct isp_statis_buf_offset {
	struct isp_statis_raw_buf_offset raw;
	struct isp_statis_awb_buf_offset awb;
	struct isp_statis_ae_buf_offset ae;
	struct isp_statis_af_buf_offset af;
	struct isp_statis_y_buf_offset y;
	uint16_t size;
};

struct rts_isp_statis {
	const void *buf;
	struct rts_isp_raw_statis raw;
	struct rts_isp_awb_statis awb;
	struct rts_isp_ae_statis ae;
	struct rts_isp_af_statis af;
	struct rts_isp_flick_statis flick;
	struct rts_isp_y_statis y;
};

struct isp_statis {
	const void *virt_addr;
	struct rts_isp_statis_info info;
	uint32_t total_size;
	int buf_id;

	struct rts_isp_statis *all;
	int *refcnt;
};

int isp_statis_init(struct isp_statis *statis,
		    const struct isp_statis_buf_offset *offset);
int isp_statis_cleanup(struct isp_statis *statis);
int isp_statis_update(struct isp_statis *statis,
		      const struct rts_isp_statis_data *data);
int isp_statis_get_all(struct isp_statis *statis,
		       const struct rts_isp_statis **all);
void isp_statis_ref(struct isp_statis *statis,
		    const struct rts_isp_statis *all);
void isp_statis_unref(struct isp_statis *statis,
		      const struct rts_isp_statis *all);

#endif /* _ISP_STATIS_H_INC_ */
