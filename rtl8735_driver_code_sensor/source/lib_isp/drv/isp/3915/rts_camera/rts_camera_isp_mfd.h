#ifndef _RTS_CAMERA_ISP_MFD_H
#define _RTS_CAMERA_ISP_MFD_H

//#include <linux/device.h>
//#include <linux/interrupt.h>
#include <linux/irqreturn.h>

struct rtscam_isp_mfd_resource {
	unsigned long io_start;
	size_t io_size;
};

enum RTS_MFD_MODUAL_ID {
	RTS_MFD_MODUAL_ID_ISP,
	RTS_MFD_MODUAL_ID_ZOOM,
	RTS_MFD_MODUAL_ID_MD,
	RTS_MFD_MODUAL_ID_VERIFY,
	RTS_MFD_MODUAL_ID_RESERVED
};

typedef int (*irq_ops)(void *data);

struct rtscam_isp_mfd {
	int (*get_child_resource)(struct rtscam_isp_mfd *mfd,
				  enum RTS_MFD_MODUAL_ID id,
				  struct rtscam_isp_mfd_resource *res);

	int (*register_irq)(struct rtscam_isp_mfd *mfd, void *master,
				irq_ops ops, irq_ops thread_ops);
	void (*wake_irq_thread)(struct rtscam_isp_mfd *mfd, void *data);

	int (*change_clk_rate)(struct rtscam_isp_mfd *mfd, unsigned long *rate);
	int (*set_clk)(struct rtscam_isp_mfd *mfd, int enable);
	int (*reset)(struct rtscam_isp_mfd *mfd);

	void (*write_reg)(struct rtscam_isp_mfd *mfd, u8 id, u32 reg, u32 val);
	u32 (*read_reg)(struct rtscam_isp_mfd *mfd, u8 id, u32 reg);
};

struct rtscam_isp_mfd *rtscam_get_isp_mfd(void);

int rtscam_isp_mfd_probe(void);
int rtscam_isp_mfd_remove(void);

#endif /* _RTS_CAMERA_ISP_MFD_H */

