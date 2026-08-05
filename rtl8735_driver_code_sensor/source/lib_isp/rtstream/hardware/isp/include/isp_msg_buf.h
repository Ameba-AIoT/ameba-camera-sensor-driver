#ifndef _ISP_MSG_BUF_H_INC_
#define _ISP_MSG_BUF_H_INC_

#include <stdint.h>

struct isp_msg_hdr {
	uint32_t sequence; /* set by internal */
	uint32_t msg_len;
	uint32_t ret_len;
	uint32_t isp_id;
	uint32_t mod_id;
	uint32_t action;
	int32_t ret_val;
	uint16_t reloc_pos;
	uint16_t reloc_num;
};

struct isp_msg_buf {
	int refcnt;
	struct isp_msg_hdr hdr;
	void *data;
};

static inline uint32_t isp_msg_data_len(const struct isp_msg_hdr *hdr)
{
	return hdr->msg_len - sizeof(*hdr);
}

struct isp_msg_buf *isp_msg_new(void *data, uint32_t len, int shared);
struct isp_msg_buf *isp_msg_get(struct isp_msg_buf *msg);
void isp_msg_put(struct isp_msg_buf *msg);
struct isp_msg_buf *isp_msg_req_to_resp(struct isp_msg_buf *req, int retval);
int isp_msg_write(int fd, struct isp_msg_buf *msg, uint32_t offset);
int isp_msg_read(int fd, struct isp_msg_buf *msg, uint32_t offset);
int isp_msg_read_hdr(int fd, struct isp_msg_hdr *hdr, uint32_t offset);
int isp_msg_relocate(struct isp_msg_buf *msg);

#define simple_msg_size(action) \
	(sizeof(struct isp_msg_hdr) + ISP_AID_SIZE(action))
#define simple_read_msg_size(action) \
	(sizeof(struct isp_msg_hdr) + \
	 (ISP_AID_IS_READ(action) ? ISP_AID_SIZE(action) : 0))
#define simple_write_msg_size(action) \
	(sizeof(struct isp_msg_hdr) + \
	 (ISP_AID_IS_WRITE(action) ? ISP_AID_SIZE(action) : 0))

#define copy_from_src(buf, src, size, end) ({ \
	int ret = RTS_ISP_OK; \
	buf = PTR_ALIGN(buf, 4); \
	if ((uintptr_t)buf + size > end) { \
		ret = -RTS_ISP_ENOSPC; \
	} else { \
		isp_memcpy(buf, src, size); \
		buf = (void *)((u32)buf + size); \
		buf = PTR_ALIGN(buf, 4); \
	} \
	ret; \
})

#define copy_to_src(src, buf, size, end) ({ \
	int ret = RTS_ISP_OK; \
	buf = PTR_ALIGN(buf, 4); \
	if ((uintptr_t)buf + size > end) { \
		ret = -RTS_ISP_ENOSPC; \
	} else { \
		isp_memcpy(src, buf, size); \
		buf = (void *)((u32)buf + size); \
		buf = PTR_ALIGN(buf, 4); \
	} \
	ret; \
})

#define set_one_reloc_item(buf, ptr, end) ({ \
	int ret = RTS_ISP_OK; \
	buf = PTR_ALIGN(buf, 4); \
	if ((u32)buf + sizeof(void *) > (u32)end) { \
		ret = -RTS_ISP_ENOSPC; \
	} else { \
		*(uintptr_t *)buf = (uintptr_t)ptr; \
		buf = (void *)((u32)buf + sizeof(uintptr_t)); \
	} \
	ret; \
})

#endif /* _ISP_MSG_BUF_H_INC_ */
