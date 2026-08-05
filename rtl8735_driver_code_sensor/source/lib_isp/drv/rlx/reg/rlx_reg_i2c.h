#ifndef RLX_REG_I2C_H
#define RLX_REG_I2C_H

/*
linux-3.10/drivers/i2c/busses/
i2c-designware-core.c
i2c-designware-platdrv.c
*/

/* 0xB8880000UL */
typedef struct rlx_i2c_reg
{
	//									offset
	uint32_t DW_IC_CON;					// 0x00
	uint32_t DW_IC_TAR;					// 0x04
	uint32_t DW_IC_SAR;					// 0x08
	uint32_t IC_HS_MADDR;				// 0x0C
	uint32_t DW_IC_DATA_CMD;			// 0x10
	uint32_t DW_IC_SS_SCL_HCNT;			// 0x14
	uint32_t DW_IC_SS_SCL_LCNT;			// 0x18
	uint32_t DW_IC_FS_SCL_HCNT;			// 0x1C
	uint32_t DW_IC_FS_SCL_LCNT;			// 0x20
	uint32_t DW_IC_HS_SCL_HCNT;			// 0x24
	uint32_t DW_IC_HS_SCL_LCNT;			// 0x28
	uint32_t DW_IC_INTR_STAT;			// 0x2C
	uint32_t DW_IC_INTR_MASK;			// 0x30
	uint32_t DW_IC_RAW_INTR_STAT;		// 0x34
	uint32_t DW_IC_RX_TL;				// 0x38
	uint32_t DW_IC_TX_TL;				// 0x3C
	uint32_t DW_IC_CLR_INTR;			// 0x40
	uint32_t DW_IC_CLR_RX_UNDER;		// 0x44
	//
	// datasheet error, DW_IC_CLR_RX_OVER is 0x48
	// All register on datasheet shift +0x04
	//
	uint32_t DW_IC_CLR_RX_OVER;			// 0x48
	uint32_t DW_IC_CLR_TX_OVER;			// 0x4C
	uint32_t DW_IC_CLR_RD_REQ;			// 0x50
	uint32_t DW_IC_CLR_TX_ABRT;			// 0x54
	uint32_t DW_IC_CLR_RX_DONE;			// 0x58
	uint32_t DW_IC_CLR_ACTIVITY;		// 0x5C
	uint32_t DW_IC_CLR_STOP_DET;		// 0x60
	uint32_t DW_IC_CLR_START_DET;		// 0x64
	uint32_t DW_IC_CLR_GEN_CALL;		// 0x68
	uint32_t DW_IC_ENABLE;				// 0x6C
	uint32_t DW_IC_STATUS;				// 0x70
	uint32_t DW_IC_TXFLR;				// 0x74
	uint32_t DW_IC_RXFLR;				// 0x78
	uint32_t DW_IC_SDA_HOLD;			// 0x7c
	uint32_t DW_IC_TX_ABRT_SOURCE;		// 0x80
	uint32_t DW_IC_SLV_DATA_NACK_ONLY;	// 0x84
	uint32_t DW_IC_DMA_CR;				// 0x88
	uint32_t DW_IC_DMA_TDLR;			// 0x8C
	uint32_t DW_IC_DMA_RDLR;			// 0x90
	uint32_t DW_IC_SDA_SETUP;			// 0x94
	uint32_t DW_IC_ACK_GENERAL_CALL;	// 0x98
	uint32_t DW_IC_ENABLE_STATUS;		// 0x9C
} rlx_reg_i2c_st;


#define DW_IC_INTR_RX_UNDER				0x001
#define DW_IC_INTR_RX_OVER				0x002
#define DW_IC_INTR_RX_FULL				0x004
#define DW_IC_INTR_TX_OVER				0x008
#define DW_IC_INTR_TX_EMPTY				0x010
#define DW_IC_INTR_RD_REQ				0x020
#define DW_IC_INTR_TX_ABRT				0x040
#define DW_IC_INTR_RX_DONE				0x080
#define DW_IC_INTR_ACTIVITY				0x100
#define DW_IC_INTR_STOP_DET				0x200
#define DW_IC_INTR_START_DET			0x400
#define DW_IC_INTR_GEN_CALL				0x800

#define DW_IC_INTR_DEFAULT_MASK	\
	(DW_IC_INTR_RX_FULL | \
	 DW_IC_INTR_TX_EMPTY | \
	 DW_IC_INTR_TX_ABRT | \
	 DW_IC_INTR_STOP_DET)

#define DW_IC_STATUS_ACTIVITY			0x1

#define DW_IC_ERR_TX_ABRT				0x1

/*
 * status codes
 */
#define STATUS_IDLE						0x0
#define STATUS_WRITE_IN_PROGRESS		0x1
#define STATUS_READ_IN_PROGRESS			0x2

/*
  I2C configuration
*/
#define DW_IC_CON_MASTER				0x1
#define DW_IC_CON_SPEED_STD				0x2
#define DW_IC_CON_SPEED_FAST			0x4
#define DW_IC_CON_SPEED_HIGH			0x6
#define DW_IC_CON_10BITADDR_MASTER		0x10
#define DW_IC_CON_RESTART_EN			0x20
#define DW_IC_CON_SLAVE_DISABLE			0x40

/*
 * hardware abort codes from the DW_IC_TX_ABRT_SOURCE register
 *
 * only expected abort codes are listed here
 * refer to the datasheet for the full list
 */
#define ABRT_7B_ADDR_NOACK				0
#define ABRT_10ADDR1_NOACK				1
#define ABRT_10ADDR2_NOACK				2
#define ABRT_TXDATA_NOACK				3
#define ABRT_GCALL_NOACK				4
#define ABRT_GCALL_READ					5
#define ABRT_SBYTE_ACKDET				7
#define ABRT_SBYTE_NORSTRT				9
#define ABRT_10B_RD_NORSTRT				10
#define ABRT_MASTER_DIS					11
#define ARB_LOST						12

#define DW_IC_TX_ABRT_7B_ADDR_NOACK		(1UL << ABRT_7B_ADDR_NOACK)
#define DW_IC_TX_ABRT_10ADDR1_NOACK		(1UL << ABRT_10ADDR1_NOACK)
#define DW_IC_TX_ABRT_10ADDR2_NOACK		(1UL << ABRT_10ADDR2_NOACK)
#define DW_IC_TX_ABRT_TXDATA_NOACK		(1UL << ABRT_TXDATA_NOACK)
#define DW_IC_TX_ABRT_GCALL_NOACK		(1UL << ABRT_GCALL_NOACK)
#define DW_IC_TX_ABRT_GCALL_READ		(1UL << ABRT_GCALL_READ)
#define DW_IC_TX_ABRT_SBYTE_ACKDET		(1UL << ABRT_SBYTE_ACKDET)
#define DW_IC_TX_ABRT_SBYTE_NORSTRT		(1UL << ABRT_SBYTE_NORSTRT)
#define DW_IC_TX_ABRT_10B_RD_NORSTRT	(1UL << ABRT_10B_RD_NORSTRT)
#define DW_IC_TX_ABRT_MASTER_DIS		(1UL << ABRT_MASTER_DIS)
#define DW_IC_TX_ARB_LOST				(1UL << ARB_LOST)

#define DW_IC_TX_ABRT_NOACK	\
	(DW_IC_TX_ABRT_7B_ADDR_NOACK | \
	 DW_IC_TX_ABRT_10ADDR1_NOACK | \
	 DW_IC_TX_ABRT_10ADDR2_NOACK | \
	 DW_IC_TX_ABRT_TXDATA_NOACK | \
	 DW_IC_TX_ABRT_GCALL_NOACK)

#endif	// RLX_REG_I2C_H
