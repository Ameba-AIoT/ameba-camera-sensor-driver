#ifndef RLX_REG_ISP_H
#define RLX_REG_ISP_H

/* 0xB8040000UL */
typedef struct rlx_mcu_reg
{
	uint32_t DATA0_HOST_TO_MCU;
	uint32_t DATA1_HOST_TO_MCU;
	uint32_t DATA2_HOST_TO_MCU;
	uint32_t DATA3_HOST_TO_MCU;
	uint32_t DATA4_HOST_TO_MCU;
	uint32_t DATA5_HOST_TO_MCU;
	uint32_t DATA6_HOST_TO_MCU;
	uint32_t DATA7_HOST_TO_MCU;

	/* 0x20 */
	uint32_t DATA0_MCU_TO_HOST;
	uint32_t DATA1_MCU_TO_HOST;
	uint32_t DATA2_MCU_TO_HOST;
	uint32_t DATA3_MCU_TO_HOST;
	uint32_t DATA4_MCU_TO_HOST;
	uint32_t DATA5_MCU_TO_HOST;
	uint32_t DATA6_MCU_TO_HOST;
	uint32_t DATA7_MCU_TO_HOST;

	/* 0x40 */
	uint32_t CMD0_HOST_TO_MCU;
	uint32_t CMD1_HOST_TO_MCU;

	uint32_t MCU_CMD_STATUS;
} rlx_reg_isp_mcu_st;

/* 0xB8040100UL */
#define RLX_REG_YUV_FRAME_Y_START_ADDRESS_BASE			(ISP_IMG_BASE)				// Frame 0 Y  Start Address for Stream 0
#define RLX_REG_YUV_FRAME_UV_START_ADDRESS_BASE			(ISP_IMG_BASE + 0x0080)		// Frame 0 UV Start Address for Stream 0
#define RLX_REG_MJPEG_FRAME_BUFFER_START_ADDRESS_BASE	(ISP_IMG_BASE + 0x0110)
#define RLX_REG_MJPEG_FRAME_BUFFER_LENGTH				(ISP_IMG_BASE + 0x0130)
#define RLX_REG_YUV_FRAME_OVERFLOW_COUNT				(ISP_IMG_BASE + 0x0158)		// Frame Overflow Count for YUV Stream
#define RLX_REG_MJPEG_FRAME_OVERFLOW_COUNT				(ISP_IMG_BASE + 0x015C)
#define RLX_REG_FRAME_BUFFER_COUNT						(ISP_IMG_BASE + 0x0160)		// Frame Buffer Count
#define RLX_REG_ISP_CONTROL								(ISP_IMG_BASE + 0x0164)		// ISP Control
#define RLX_REG_YUV_ISP_BUF_CONFIG_BASE					(ISP_IMG_BASE + 0x016C)
#define RLX_REG_YUV_ISP_Y_BUF_CONFIG_S0					(ISP_IMG_BASE + 0x016C)		// Y  ISP Buffer Start Address for Stream 0
#define RLX_REG_YUV_ISP_UV_BUF_CONFIG_S0				(ISP_IMG_BASE + 0x0170)		// UV ISP Buffer Start Address for Stream 0
#define RLX_REG_YUV_ISP_Y_BUF_CONFIG_S1					(ISP_IMG_BASE + 0x0174)		// Y  ISP Buffer Start Address for Stream 1
#define RLX_REG_YUV_ISP_UV_BUF_CONFIG_S1				(ISP_IMG_BASE + 0x0178)		// UV ISP Buffer Start Address for Stream 1
#define RLX_REG_YUV_ISP_Y_BUF_CONFIG_S2					(ISP_IMG_BASE + 0x017C)		// Y  ISP Buffer Start Address for Stream 2
#define RLX_REG_YUV_ISP_UV_BUF_CONFIG_S2				(ISP_IMG_BASE + 0x0180)		// UV ISP Buffer Start Address for Stream 2
#define RLX_REG_YUV_ISP_Y_BUF_CONFIG_S3					(ISP_IMG_BASE + 0x0184)		// Y  ISP Buffer Start Address for Stream 3
#define RLX_REG_YUV_ISP_UV_BUF_CONFIG_S3				(ISP_IMG_BASE + 0x0188)		// UV ISP Buffer Start Address for Stream 3
#define RLX_REG_MJPEG_ISP_BUF_CONFIG					(ISP_IMG_BASE + 0x018C)
#define RLX_REG_TD_ISP_BUF_CONFIG						(ISP_IMG_BASE + 0x0190)		// ISP Buffer Start Address for TD
#define RLX_REG_STREAM_FRAME_INTERVAL_CONFIG			(ISP_IMG_BASE + 0x0198)		// Frame Interval Configure
#define RLX_REG_PTS_VALUE_CONFIG						(ISP_IMG_BASE + 0x01A0)		// PTS Value Config
#define RLX_REG_YUV_FRAME_BUFFER_STATUS_BASE			(ISP_IMG_BASE + 0x01A4)		// Frame Buffer Status for YUV Stream
#define RLX_REG_MJPEG_STREAM_FRAME_BUFFER_STATUS		(ISP_IMG_BASE + 0x01B4)
#define RLX_REG_TD_BUFFER_START_ADDRESS					(ISP_IMG_BASE + 0x01B8)		// Receive Buffer Start Address for TD
#define RLX_REG_TD_BUFFER_LENGTH						(ISP_IMG_BASE + 0x01BC)		// Receive Buffer Length for TD
#define RLX_REG_YUV_CUR_FRAME_INDEX_OFFSET_BASE			(ISP_IMG_BASE + 0x01C0)		// Current Frame Index and Offset for YUV Stream
#define RLX_REG_MJPEG_CUR_FRAME_INDEX					(ISP_IMG_BASE + 0x01D0)		// Current Frame Index for MJPEG Stream
#define RLX_REG_YUV_ISP_Y_BUFFER_OVERFLOW_COUNT			(ISP_IMG_BASE + 0x01D4)		// ISP Y  Overflow Count for YUV Stream
#define RLX_REG_YUV_ISP_UV_BUFFER_OVERFLOW_COUNT		(ISP_IMG_BASE + 0x01D8)		// ISP UV Overflow Count for YUV Stream
#define RLX_REG_MJPEG_TD_ISP_BUFFER_OVERFLOW_COUNT		(ISP_IMG_BASE + 0x01DC)		// ISP Buffer Overflow Count for MJPEG Stream or TD
#define RLX_REG_MJPEG_FRAME_RECVED_LENGTH				(ISP_IMG_BASE + 0x01E0)
#define RLX_REG_LDC_MAP_TABLE_START						(ISP_IMG_BASE + 0x01E0)		// Receive Buffer Start Address for LDC Mapping Table
#define RLX_REG_LDC_MAP_TABLE_SIZE						(ISP_IMG_BASE + 0x01E4)		// LDC Mapping Table Size
#define RLX_REG_ISP_HEADER_ADDR							(ISP_IMG_BASE + 0x01F0)		// ISP Header Start Address
#define RLX_REG_ISP_OCP_IF_DUMMY						(ISP_IMG_BASE + 0x0200)		// ISP OCP IF Dummy

/* 0xB8040400UL */
typedef struct rlx_ispfw_reg
{
	uint32_t MCU_SPI_BASE_ADDR;
	uint32_t CPU_LOCK_MCU;
} rlx_reg_isp_spi_st;

/* 0xB8040500UL */
typedef struct rlx_isp_int_reg
{
	uint32_t INT_EN_MCU_TO_HOST;
	uint32_t INT_EN_ISP_TO_HOST;
	uint32_t INT_FLAG_MCU_TO_HOST;
	uint32_t INT_FLAG_ISP_HOST;
} rlx_reg_isp_int_st;

/* 0xB8041000UL */
#define RLX_REG_ISP_CMD_DATA_HOST_TO_MCU				(ISP_CMD_BASE)				// ISP Cmd Data from CPU to MCU
#define RLX_REG_ISP_CMD_DATA_MCU_TO_HOST				(ISP_CMD_BASE + 0x0100)		// ISP Cmd Data from MCU to CPU

#endif	// RLX_REG_ISP_H
