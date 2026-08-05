#ifndef _RTS_ISP_SENSOR_H_INC_
#define _RTS_ISP_SENSOR_H_INC_

#include <stdint.h>
#include <rts_camera_isp_snr.h>
#include <rts_isp_errno.h>
#include <rts_isp_geom.h>

#ifdef __cplusplus
extern "C"
{
#endif



#define SENSOR_OPS_VERSION_MAGIC ((uint32_t)'s' << 8)
#define SENSOR_OPS_MAJOR_VERSION 0
#define SENSOR_OPS_MINOR_VERSION 5
#define SENSOR_OPS_VERSION \
	(SENSOR_OPS_VERSION_MAGIC << 16 | SENSOR_OPS_MAJOR_VERSION << 8 | \
	 SENSOR_OPS_MINOR_VERSION)
#define SENSOR_VERSION_MASK ((1 << 16) - 1)

#define SENSOR_FPS_PRECISION 1000
#define RTS_ISP_HDR_CHAN_MAX 2

#define set_init_i2c_regs(info, _regs, _udelay) ({ \
	typeof(info) *_info = &info; \
	_info->regs = _regs; \
	_info->num = ARRAY_SIZE(_regs); \
	_info->udelay = _udelay; })

static inline void set_power_item(struct rts_isp_snr_pwr_item *item,
				  enum rts_isp_snr_pwr_type type,
				  __u32 value, __u32 delay)
{
	item->type = type;
	item->value = value;
	item->delay = delay;
}
static inline void set_init_i2c(struct rts_isp_i2c_reg *reg,
				__u16 addr, __u16 data)
{
	reg->addr = addr;
	reg->data = data;
}

static inline void set_sync_i2c(struct rts_isp_sync_reg *reg,
				__u16 addr, __u16 data)
{
	reg->i2c.addr = addr;
	reg->i2c.data = data;
}

static inline void set_sync_isp(struct rts_isp_sync_reg *reg,
				__u32 addr, __u32 data)
{
	reg->reg.addr = addr;
	reg->reg.data = data;
	reg->info.type = RTS_ISP_SYNC_REG_TYPE_REG;
}

static inline void set_sync_i2c_mask(struct rts_isp_sync_reg *reg,
				     __u16 addr, __u16 data, __u16 mask)
{
	reg->i2c.addr = addr;
	reg->i2c.data = data;
	reg->i2c.mask = mask;
}

static inline void set_sync_isp_mask(struct rts_isp_sync_reg *reg,
				     __u32 addr, __u32 data, __u32 mask)
{
	reg->reg.addr = addr;
	reg->reg.data = data;
	reg->reg.mask = mask;
	reg->info.type = RTS_ISP_SYNC_REG_TYPE_REG;
}

enum rts_isp_interface {
	SNR_INTERFACE_NONE,
	SNR_INTERFACE_DVP,
	SNR_INTERFACE_MIPI,

	/* only for debug */
	SNR_INTERFACE_FIXP,
};

struct rts_isp_dvp_info {
	uint8_t sample_rising;
	uint8_t hsync_active_high;
	uint8_t vsync_active_high;
};

enum rts_isp_mipi_lane {
	MIPI_LANE0 = 1 << 0,
	MIPI_LANE1 = 1 << 1,
	MIPI_LANE2 = 1 << 2,
	MIPI_LANE3 = 1 << 3,
};

struct rts_isp_mipi_info {
	uint8_t lanes;
	uint8_t hs_term; /* 0 to 0xf */
	uint32_t clk_skew; /* 0 to 0xf */
	uint32_t data_skew; /* 0 to 0xf */
};

enum rts_isp_sensor_type {
	RAW_SENSOR,
	YUV_SENSOR,
};

enum rts_isp_sensor_bit_depth {
	SNR_8BIT = 8,
	SNR_10BIT = 10,
	SNR_12BIT = 12,
};

enum rts_isp_sensor_yuv_type {
	SNR_UYVY = 0,
	SNR_VYUY = 1,
	SNR_YVYU = 2,
	SNR_YUYV = 3,
};

enum rts_isp_sensor_power {
	PWR_NONE =  0,
	PWR_1V2 = 1200000,
	PWR_1V5 = 1500000,
	PWR_1V8 = 1800000,
	PWR_2V7 = 2700000,
	PWR_2V8 = 2800000,
	PWR_2V9 = 2900000,
	PWR_3V0 = 3000000,
	PWR_3V3 = 3300000,
};

enum rts_isp_sensor_clock {
	CLK_NONE = 0,
	CLK_12M = 12000000,
	CLK_24M = 24000000,
	CLK_27M = 27000000,
	CLK_37M125 = 37125000,
	CLK_54M = 54000000,
	CLK_74M25 = 74250000,
};

enum rts_isp_sensor_gpio {
	GPIO_LOW = 0,
	GPIO_HIGH = 1,
};

enum rts_isp_sensor_open_mode {
	OPEN_MODE = 0,
	RESUME_MODE = 1,
};

enum rts_isp_sensor_close_mode {
	CLOSE_MODE = 0,
	SUSPEND_MODE = 1,
};


struct rts_isp_interface_info {
	enum rts_isp_interface interface;
	union {
		struct rts_isp_dvp_info dvp;
		struct rts_isp_mipi_info mipi;
	};
	enum rts_isp_sensor_bit_depth bit_depth;
	enum rts_isp_sensor_type type;
	enum rts_isp_sensor_yuv_type yuv_type; /* only for yuv sensor */
	uint32_t vhdr_start_line_tnr:0x20;
	uint32_t mipi_max_short_exp;
};

struct rts_isp_fps_info {
	uint32_t num;
	uint16_t fps[32];
};

struct rts_isp_focus_info {
	uint32_t min;
	uint32_t max;
};

enum rts_isp_sensor_hdr_behavor {
	VC_HDR, /* virtual channel hdr */
	STAGGER_DUMMY_HDR, /* multi-exposure stagger with dummy */
	STAGGER_NODUMMY_HDR, /* multi-exposure stagger without dummy */
	FID_BASED_HDR, /* sony fid based hdr */
	NONE_HDR,
};

enum rts_isp_sensor_hdr_mode {
	LINEAR_MODE,
	HDR_MODE,
};

enum rts_isp_sensor_vhdr_exp_mode {
	VHDR_EXP_MODE_MULTIPLE,
	VHDR_EXP_MODE_SINGLE,
};

struct rts_isp_stagger_hdr_info {
	uint32_t max_short_exp;
};

struct rts_isp_fid_hdr_info {
	uint32_t fid;
};

struct rts_isp_hdr_info {
	int supported;
	enum rts_isp_sensor_hdr_behavor behavor;
	float fps;
	union {
		struct rts_isp_stagger_hdr_info stagger;
		struct rts_isp_fid_hdr_info fid;
	};
};

struct rts_isp_sensor_mode {
	enum rts_isp_sensor_hdr_mode hdr; /**< sensor hdr mode */
	rts_isp_size_t size; /**< sensor size after isp crop */
	float fps; /**< sensor base fps */
};

struct rts_isp_sensor_modes {
	uint32_t num; /**< modes num */
	struct rts_isp_sensor_mode mode[8]; /**< modes list array */
};

struct rts_isp_sensor_info {
	struct rts_isp_sensor_modes modes;
	enum rts_isp_sensor_hdr_mode cur_hdr_mode;
	struct rts_isp_i2c_info i2c;
	struct rts_isp_snr_pwr power_up;
	struct rts_isp_snr_pwr resume;
	struct rts_isp_snr_pwr suspend;
	struct rts_isp_snr_pwr power_down;
	struct rts_isp_focus_info focus;
};

struct rts_isp_i2c_regs {
	uint32_t num;
	struct rts_isp_i2c_reg *regs;
	uint32_t udelay;
};

static inline int hdr_chan_num(enum rts_isp_sensor_hdr_mode hdr)
{
	if (hdr == HDR_MODE)
		return 2;
	return 1;
}

struct rts_isp_sensor_init_info {
	struct rts_isp_i2c_regs sensor_regs[8];
	enum rts_isp_sensor_hdr_behavor mipi_behavor;
	struct rts_isp_interface_info interface;
	rts_isp_size_t size;
	rts_isp_point_t start;
	uint32_t pclk;
	uint32_t hts;
	uint32_t min_vts;
	uint32_t max_vts;
	float exposure_step; /* us */
};

struct rts_isp_sensor_exp_gain {
	float exposure[RTS_ISP_HDR_CHAN_MAX];
	float analog_gain[RTS_ISP_HDR_CHAN_MAX];
	float digital_gain[RTS_ISP_HDR_CHAN_MAX];
	uint32_t vts;
};

struct rts_isp_sensor_mirror_flip {
	uint8_t mirror_en;
	uint8_t flip_en;
	uint8_t delay_frames;
	struct rts_isp_sync_regs regs;
};

struct rts_isp_sensor_again {
	float again_val;
	float isp_gain_val;
	float total_gain;
	struct rts_isp_sync_regs regs;
};

struct rts_isp_sensor_ops {
	uint32_t ops_version;
	char name[32];
	int (*get_info)(uint32_t isp_id, struct rts_isp_sensor_info *info);
	// int (*get_init_info)(uint32_t isp_id, float fps,
	// 		     struct rts_isp_sensor_init_info *info);
	int (*get_init_info)(uint32_t isp_id,
			     const struct rts_isp_sensor_mode *mode,
			     struct rts_isp_sensor_init_info *info);
	int (*get_exposure_range)(uint32_t isp_id, uint32_t vts,
				  float ratio[RTS_ISP_HDR_CHAN_MAX - 1],
				  float min_exposure[RTS_ISP_HDR_CHAN_MAX],
				  float max_exposure[RTS_ISP_HDR_CHAN_MAX]);
	int (*get_tuned_again)(uint32_t isp_id,
			       float again[RTS_ISP_HDR_CHAN_MAX]);
	int (*get_tuned_dgain)(uint32_t isp_id,
			       float dgain[RTS_ISP_HDR_CHAN_MAX]);
	int (*get_exposure_gain_info)(uint32_t isp_id,
			const struct rts_isp_sensor_exp_gain *exp_gain,
			struct rts_isp_sync_regs *regs);
	/* optional */
	int (*init)(uint32_t isp_id);
	int (*cleanup)(uint32_t isp_id);
	int (*start)(uint32_t isp_id);
	int (*stop)(uint32_t isp_id);
	int (*set_focus)(uint32_t isp_id, uint32_t position);
	int (*get_temperature)(uint32_t isp_id);
	int (*set_mirror_flip)(uint32_t isp_id,
						   struct rts_isp_sensor_mirror_flip *mf_info);
	float (*get_bound)(uint32_t isp_id, uint32_t temperature); // analog gain bound
	int (*set_again)(uint32_t isp_id,
						   struct rts_isp_sensor_again *again_info);

	/* for iq patch, optional */
	const void *(*get_patch_ops)(void);

	/* for multi-sensor dectection, optional */
	int (*check)(uint32_t isp_id);
	int (*pre_resume)(uint32_t isp_id);

	/* when entered short_exp_mode, we will disable VHDR(multiple exposure) to use lower exposure time of single exposure */
	int (*get_short_exp_mode)(uint32_t isp_id);
	/* set to lower than 512 to disable this feature */
	int (*set_short_exp_exit_thd)(uint32_t isp_id, uint16_t exit_thd);

	int (*get_slave_addr_num)(uint32_t isp_id);

	uint32_t rsvd[7];
};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void);

/* do not use these APIs as far as possible */
int rts_isp_read_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);
int rts_isp_write_sensor_reg(uint32_t isp_id, struct rts_isp_i2c_reg *reg);
int rts_isp_read_i2c_regs(const struct rts_isp_i2c_info *info,
			  const struct rts_isp_i2c_regs *regs);
int rts_isp_write_i2c_regs(const struct rts_isp_i2c_info *info,
			   const struct rts_isp_i2c_regs *regs);
int rts_isp_read_i2c_reg(const struct rts_isp_i2c_info *info,
			 struct rts_isp_i2c_reg *reg);
int rts_isp_write_i2c_reg(const struct rts_isp_i2c_info *info,
			  struct rts_isp_i2c_reg *reg);

/* need for get_temperature */
void rts_isp_sensor_access_prepare(void);
void rts_isp_sensor_access_unprepare(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTS_ISP_SENSOR_H_INC_ */

