/*
 * SPI flash probing
 *
 * Copyright (C) 2008 Atmel Corporation
 * Copyright (C) 2010 Reinhard Meyer, EMK Elektronik
 * Copyright (C) 2013 Jagannadha Sutradharudu Teki, Xilinx Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include "rt_drv.h"
#include "rt_config.h"
#include "rt_config_rlx.h"
#include "rt_util.h"
#include "rt_log.h"

#include "spi.h"
#include "spi_flash.h"
#include "sf_internal.h"

// NOTE: please use rt_printf() for msg output through entire file.

/**
 * struct spi_flash_params - SPI/QSPI flash device params structure
 *
 * @name:		Device name ([MANUFLETTER][DEVTYPE][DENSITY][EXTRAINFO])
 * @jedec:		Device jedec ID (0x[1byte_manuf_id][2byte_dev_id])
 * @ext_jedec:		Device ext_jedec ID
 * @sector_size:	Sector size of this device
 * @nr_sectors:		No.of sectors on this device
 * @flags:		Importent param, for flash specific behaviour
 * @reset_flow  Reset fifo command
 **/
struct spi_flash_params {
	const char *name;
	u32 jedec;
	u16 ext_jedec;
	u32 sector_size;
	u32 nr_sectors;
	u16 flags;
	u8 fast_read_cmd;
	u8 autoread_type;
	u8 dummy_cycle;
	u8 fast_write_cmd;
	u8 userwrite_type;
	u8 erase_cmd;
	u8 wrsr_en_cmd;
	u16 reset_flow[4];
};
/*Reset flow command fill format*/
/*bit15:bit12 counter for cycle control during each operation*/
/*bit11:bit10 flow_ctrl for controlling the FSM in PGM_RST module*/
/*bit9:bit8 ctrl_info for controlling SPIC in which channel*/
/*bit7:bit0 cmd/val for executed flash command or value*/
/*e.g 0x4466*/
/*bit15:bit12 0x4 means 2^16 spic_clk*/
/*cycles when spic_clk = 60MHz,time is 1092us*/
/*bit11:bit10 0x1 means FSM is next*/
/*bit9:bit8 0x0 means SPIC is in SPI channel*/
/*bit7:bit0 0x66 means flash reset enable command*/
/*for details refer to spic RXI-310 datasheet*/
static const struct spi_flash_params spi_flash_params_table[] = {
/*configure quad channel*/
#ifdef CONFIG_QUAD_CHANNEL
/* GIGADEVICE */
	/*SPI mode*/
	{"GD25Q64C",	   0xC84017, 0x0,	64 * 1024,   128,
	SR_3REG,	0x6B,	RD_QUAD_O,	8,	0x32,
	WR_QUAD_I,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"GD25Q128C",	   0xC84018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x6B,	RD_QUAD_O,	8,	0x32,
	WR_QUAD_I,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"GD25Q256C",	   0xC84019, 0x0,	64 * 1024,   512,
	SR_3REG1,	0x6C,	RD_QUAD_O,	8,	0x3E,
	WR_QUAD_I, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* MACRONIX */
	/*SPI mode*/
	{"MX25L6433F",	   0xc22017, 0x0,	64 * 1024,   128,
	SR_CFG1,	0x6B,	RD_QUAD_O,	8,	0x38,	WR_QUAD_II,
	CMD_ERASE_64K_3B_4B,	0x06,	{0x4466, 0x8499, 0x0000} },
	{"MX25L12835F",	   0xc22018, 0x0,	64 * 1024,   256,
	SR_CFG,			0x6B,	RD_QUAD_O,	8,	0x38,
	WR_QUAD_II,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX25L25635F",	   0xc22019, 0x0,	64 * 1024,   512,
	SR_CFG,			0x6C,	RD_QUAD_O,	8,	0x38,
	WR_QUAD_II, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX25L51245G",	   0xc2201a, 0x0,	64 * 1024,  1024,
	SR_CFG,			0x6C,	RD_QUAD_O,	8,	0x38,
	WR_QUAD_II, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX66L1G45G",	   0xc2201b, 0x0,	64 * 1024,  2048,
	SR_CFG,			0x6C,	RD_QUAD_O,	8,	0x38,
	WR_QUAD_II, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* WINBOND */
	/*SPI mode*/
	{"W25Q64FV",	   0xef4017, 0x0,	64 * 1024,   128,
	SR_3REG2,	0x6B, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"W25Q128FV",	   0xef4018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x6B, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"W25Q256FV",	   0xef4019, 0x0,	64 * 1024,   512,
	SR_3REG,	0x6C, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* XMC */
	{"XM25QH64A",	   0x207017, 0x0,	64 * 1024,   128,
	SR_REG1,	0x6B, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x50, {0x4466, 0x8499, 0x0000} },
	{"XM25QH128A",	   0x207018, 0x0,	64 * 1024,   256,
	SR_REG1,	0x6B, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x50, {0x4466, 0x8499, 0x0000} },
/* EON */
	{"EN25QH64A",	   0x1c7017, 0x0,	64 * 1024,   128,
	SR_REG1,	0x6B,	RD_QUAD_O,	8,	0x32,
	WR_QUAD_I,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* BYT */
	/*SPI mode*/
	{"BY25Q64AS",	   0x684017, 0x0,	64 * 1024,   128,
	SR_3REG,	0x6B,	RD_QUAD_O,	8,	0x32,
	WR_QUAD_I,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"BY25Q128AS",	   0x684018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x6B, RD_QUAD_O,	8,	0x32,
	WR_QUAD_I, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
#endif
/*configure dual channel*/
#ifdef CONFIG_DUAL_CHANNEL
/* GIGADEVICE */
	/*SPI mode*/
	{"GD25Q32C",	   0xC84016, 0x0,	64 * 1024,    64,
	SR_3REG,	0x3B,	RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"GD25Q64C",	   0xC84017, 0x0,	64 * 1024,   128,
	SR_3REG,	0x3B,	RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x2466, 0x8499, 0x0000} },
	{"GD25Q128C",	   0xC84018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x3B,	RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"GD25Q256C",	   0xC84019, 0x0,	64 * 1024,   512,
	SR_3REG1,	0x3C,	RD_DUAL_O,	8,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* MACRONIX */
	/*SPI mode*/
	/*{"KH25L6406E",	   0xc22017, 0x0,	64 * 1024,   128,
	 *SR_1,	0x3B,	RD_DUAL_O,	8,	0x02,
	 *WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06,
	 *{0x4466, 0x8499, 0x0000} },
	 */
	{"MX25L6433F",	   0xc22017, 0x0,	64 * 1024,   128,
	SR_CFG1,	0xBB,	RD_DUAL_IO,	4,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX25L12835F",	   0xc22018, 0x0,	64 * 1024,   256,
	SR_CFG,	0xBB,	RD_DUAL_IO,	4,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX25L25635F",	   0xc22019, 0x0,	64 * 1024,   512,
	SR_CFG,	0xBC,	RD_DUAL_IO,	4,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX25L51245G",	   0xc2201a, 0x0,	64 * 1024,  1024,
	SR_CFG,	0xBC,	RD_DUAL_IO,	4,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"MX66L1G45G",	   0xc2201b, 0x0,	64 * 1024,  2048,
	SR_CFG,	0xBC,	RD_DUAL_IO,	4,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* WINBOND */
	/*SPI mode*/
	{"W25Q64FV",		0xef4017, 0x0,	64 * 1024,   128,
	SR_3REG2,	0x3B, RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"W25Q128FV",		0xef4018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x3B, RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	{"W25Q256FV",	   0xef4019, 0x0,	64 * 1024,   512,
	SR_3REG,	0x3C, RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* XMC */
	{"XM25QH64A",	   0x207017, 0x0,	64 * 1024,   128,
	SR_REG1,	0xBB, RD_DUAL_IO,	4,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x50, {0x4466, 0x8499, 0x0000} },
	{"XM25QH128A",	   0x207018, 0x0,	64 * 1024,   256,
	SR_REG1,	0xBB, RD_DUAL_IO,	4,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x50, {0x4466, 0x8499, 0x0000} },
/* EON */
	{"EN25QH64A",	   0x1c7017, 0x0,	64 * 1024,   128,
	SR_REG1,	0xBB,	RD_DUAL_IO,	4,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
/* BYT */
	/*SPI mode*/
	{"BY25Q64AS",	   0x684017, 0x0,	64 * 1024,   128,
	SR_3REG,	0x3B,	RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE,	CMD_ERASE_64K_3B_4B, 0x06, {0x2466, 0x8499, 0x0000} },
	{"BY25Q128AS",		0x684018, 0x0,	64 * 1024,   256,
	SR_3REG,	0x3B, RD_DUAL_O,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
#endif
#ifdef CONFIG_QPI_MODE
/* GIGADEVICE */
	{"GD25Q128C",	   0xC84018, 0x0,	64 * 1024,   256,
	SR_3REG|QPI_II,	0xEB,	RD_QUAD_IO,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
/* MACRONIX */
	{"MX25L12835F",	   0xc22018, 0x0,	64 * 1024,   256,
	SR_CFG|QPI_I,	0xEB,	RD_QUAD_IO,	6,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"MX25L25635F",	   0xc22019, 0x0,	64 * 1024,   512,
	SR_CFG|QPI_I,	0xEC,	RD_QUAD_IO,	6,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"MX25L51245G",	   0xc2201a, 0x0,	64 * 1024,  1024,
	SR_CFG|QPI_I,	0xEC,	RD_QUAD_IO,	6,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"MX66L1G45G",	   0xc2201b, 0x0,	64 * 1024,  2048,
	SR_CFG|QPI_I,	0xEC,	RD_QUAD_IO,	6,	0x12,
	WR_MULTI_NONE, CMD_ERASE_64K_4B, 0x06, {0x4666, 0x8699, 0x0000} },
/* WINBOND */
	{"W25Q64FV",		0xef4017, 0x0,	64 * 1024,   128,
	SR_3REG2|QPI_II,	0xEB, RD_QUAD_IO,	6,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"W25Q128FV",	   0xef4018, 0x0,	64 * 1024,   256,
	SR_3REG|QPI_II,	0xEB,	RD_QUAD_IO,	6,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
	{"W25Q256FV",	   0xef4019, 0x0,	64 * 1024,   512,
	SR_3REG|QPI_II,	0xEB,	RD_QUAD_IO,	6,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
/* XMC */
	{"XM25QH64A",	   0x207017, 0x0,	64 * 1024,   128,
	SR_REG1|QPI_II,	0xEB, RD_QUAD_IO,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x50, {0x4666, 0x8699, 0x0000} },
	{"XM25QH128A",	   0x207018, 0x0,	64 * 1024,   256,
	SR_REG1|QPI_II,	0xEB, RD_QUAD_IO,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x50, {0x4666, 0x8699, 0x0000} },
/* EON */
	{"EN25QH64A",	   0x1c7017, 0x0,	64 * 1024,   128,
	SR_REG1|QPI_II,	0xEB, RD_QUAD_IO,	8,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4666, 0x8699, 0x0000} },
#endif
	{"unknown",			0xef0000, 0x0,	64 * 1024,   256,
	SR_3REG,	0x03, FRD_NONE,		0,	0x02,
	WR_MULTI_NONE, CMD_ERASE_64K_3B_4B, 0x06, {0x4466, 0x8499, 0x0000} },
	/*
	 * Note:
	 * Below paired flash devices has similar spi_flash params.
	 * (S25FL129P_64K, S25FL128S_64K)
	 * (W25Q80BL, W25Q80BV)
	 * (W25Q16CL, W25Q16DV)
	 * (W25Q32BV, W25Q32FV_SPI)
	 * (W25Q64CV, W25Q64FV_SPI)
	 * (W25Q128BV, W25Q128FV_SPI)
	 * (W25Q32DW, W25Q32FV_QPI)
	 * (W25Q64DW, W25Q64FV_QPI)
	 * (W25Q128FW, W25Q128FV_QPI)
	 */
};

static struct spi_flash *spi_flash_validate_params(struct spi_slave *spi,
		u8 *idcode)
{
	const struct spi_flash_params *params = &spi_flash_params_table[0];
	struct spi_flash *flash;
	int i;
	u16 jedec = idcode[1] << 8 | idcode[2];
	u16 ext_jedec = idcode[3] << 8 | idcode[4];
	u8 tmp1, tmp2, tmp3;

	/* Get the flash id (jedec = manuf_id + dev_id, ext_jedec) */
	for (i = 0; i < (int)ARRAY_SIZE(spi_flash_params_table); i++) {
		params = &spi_flash_params_table[i];
		if ((params->jedec >> 16) == idcode[0]) {
			if ((params->jedec & 0xFFFF) == jedec) {
				if (params->ext_jedec == 0)
					break;
				else if (params->ext_jedec == ext_jedec)
					break;
			}
		}
	}


	if (i == ARRAY_SIZE(spi_flash_params_table)) {
		rt_printf("SF: Unsupported flash IDs: ");
		rt_printf("manuf %02x, jedec %04x, ext_jedec %04x\n",
		       idcode[0], jedec, ext_jedec);
		/*return NULL;*/
	}

	flash = rt_malloc(sizeof(*flash));
	if (!flash) {
		rt_debug("SF: Failed to allocate spi_flash\n");
		return NULL;
	}
	memset(flash, '\0', sizeof(*flash));

	/* Assign spi data */
	flash->spi = spi;
	flash->name = params->name;
	flash->memory_map = spi->memory_map;

	/* Assign spi_flash ops */
	flash->write = spi_flash_cmd_write_ops;
#ifdef CONFIG_SPI_FLASH_SST
	if (params->flags & SST_WP)
		flash->write = sst_write_wp;
#endif
	flash->erase = spi_flash_cmd_erase_ops;
	flash->read = spi_flash_cmd_read_ops;

	/* Compute the flash size */
	flash->page_size = (ext_jedec == 0x4d00) ? 512 : 256;
	flash->sector_size = params->sector_size;
	flash->size = flash->sector_size * params->nr_sectors;

	/* Compute erase sector and command */
	if (params->flags & SECT_4K) {
		flash->erase_cmd = CMD_ERASE_4K;
		flash->erase_size = 4096;
	} else if (params->flags & SECT_32K) {
		flash->erase_cmd = CMD_ERASE_32K;
		flash->erase_size = 32768;
	} else {
		flash->erase_cmd = params->erase_cmd;
		flash->erase_size = flash->sector_size;
	}

	/* Poll cmd seclection */
	flash->poll_cmd = CMD_READ_STATUS_1;
	flash->spi->read_cmd = params->fast_read_cmd;	/*auto read command*/
	flash->spi->write_cmd = params->fast_write_cmd;	/*user write command*/
	flash->spi->autoread_type = params->autoread_type;
	flash->spi->dummy_cycle = params->dummy_cycle;
	flash->spi->userwrite_type = params->userwrite_type;
	flash->spi->flags = params->flags;
	flash->spi->wrsr_en_cmd = params->wrsr_en_cmd;

#ifdef CONFIG_SPI_FLASH_STMICRO
	if (params->flags & E_FSR)
		flash->poll_cmd = CMD_FLAG_STATUS;
#endif

	/* Configure the BAR - discover bank cmds and read current bank */
#ifdef CONFIG_SPI_FLASH_BAR
	u8 curr_bank = 0;
	if (flash->size > SPI_FLASH_16MB_BOUN) {
		flash->bank_read_cmd = (idcode[0] == 0x01) ?
					CMD_BANKADDR_BRRD : CMD_EXTNADDR_RDEAR;
		flash->bank_write_cmd = (idcode[0] == 0x01) ?
					CMD_BANKADDR_BRWR : CMD_EXTNADDR_WREAR;

		if (spi_flash_read_common(flash, &flash->bank_read_cmd, 1,
					  &curr_bank, 1)) {
			rt_debug("SF: fail to read bank addr register\n");
			return NULL;
		}
		flash->bank_curr = curr_bank;
	} else {
		flash->bank_curr = curr_bank;
	}
#endif

	/* Flash powers up read-only, so clear BP# bits,
	for support quad write ,
	set status register bit6*/
	/*driving strength config.
	 *MX25L6433F need 1 bit in configuration register.
	 *KH25L6406E does not have this config.
	 *MX25L12835F,MX25L25635F,MX25L51245G,MX66L1G45G
	 *is same,need 3 bits in configuration register.
	 *MX25L12845G,MX25L25645G is same,need 2 bits in
	 *configuration register.
	 *For compatibility,configuration register is
	 *configured 0x07.
	 */
		if (params->flags & SR_CFG)
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash, 0x0740,
						   CMD_WRITE_STATUS_1, 2);
#else
			spi_flash_cmd_write_status(flash, 0x0700,
						   CMD_WRITE_STATUS_1, 2);
#endif
		else if (params->flags & SR_CFG1)
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash, 0x0040,
			CMD_WRITE_STATUS_1, 2);
#else
			spi_flash_cmd_write_status(flash, 0x0000,
			CMD_WRITE_STATUS_1, 2);
#endif
		else if (params->flags & SR_3REG) {
			spi_flash_cmd_write_status(flash, 0x00,
			CMD_WRITE_STATUS_1, 1);
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash, 0x02,
			CMD_WRITE_STATUS_2, 1);
#else
			spi_flash_cmd_write_status(flash, 0x00,
			CMD_WRITE_STATUS_2, 1);
#endif
			spi_flash_cmd_write_status(flash, 0x00,
			CMD_WRITE_STATUS_3, 1);
		} else if (params->flags & SR_3REG1) {
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash, 0x40,
						   CMD_WRITE_STATUS_1,
						   1);
#else
			spi_flash_cmd_write_status(flash, 0x00,
						   CMD_WRITE_STATUS_1,
						   1);
#endif
			spi_flash_cmd_write_status(flash, 0x00,
						   CMD_WRITE_STATUS_2,
						   1);
			spi_flash_cmd_write_status(flash, 0x00,
						   CMD_WRITE_STATUS_3,
						   1);
		} else if (params->flags & SR_3REG2) {
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash,
			0x0200, CMD_WRITE_STATUS_1, 2);
#else
			spi_flash_cmd_write_status(flash,
			0x0000, CMD_WRITE_STATUS_1, 2);
#endif
		} else if (params->flags & SR_1) {
			spi_flash_cmd_write_status(flash,
			0x00, CMD_WRITE_STATUS_1, 1);
		} else if (params->flags & SR_REG1) {
			spi_flash_cmd_write_status(flash,
			0x00, CMD_WRITE_STATUS_1, 1);
		} else {
#ifdef CONFIG_QUAD_CHANNEL
			spi_flash_cmd_write_status(flash,
						   0x40, CMD_WRITE_STATUS_1, 1);
#else
			spi_flash_cmd_write_status(flash,
						   0x00, CMD_WRITE_STATUS_1, 1);
#endif
		}

		spi_flash_enable_QPI_ops(flash);

		if ((params->flags & SR_CFG) || (params->flags & SR_CFG1)) {
			spi_flash_cmd_read_status(flash,
						  &tmp1, CMD_READ_STATUS_1);
			spi_flash_cmd_read_status(flash,
						  &tmp2, CMD_READ_CONFIG);
			rt_printf("flash status is %x, %x\n", tmp1, tmp2);
		}

		if (params->flags & SR_3REG) {
			spi_flash_cmd_read_status(flash,
						  &tmp1, CMD_READ_STATUS_1);
			spi_flash_cmd_read_status(flash,
						  &tmp2, CMD_READ_STATUS_2);
			spi_flash_cmd_read_status(flash,
						  &tmp3, CMD_READ_STATUS_3);
			rt_printf("flash status is %x, %x, %x\n", tmp1, tmp2, tmp3);
		}

		if (params->flags & SR_3REG1) {
			spi_flash_cmd_read_status(flash,
						  &tmp1, CMD_READ_STATUS_1);
			spi_flash_cmd_read_status(flash,
						  &tmp2, CMD_READ_STATUS_2);
			spi_flash_cmd_read_status(flash,
						  &tmp3, CMD_READ_STATUS_3);
			rt_printf("flash status is %x, %x, %x\n", tmp1, tmp2, tmp3);
		}

		if (params->flags & SR_3REG2) {
			spi_flash_cmd_read_status(flash,
				&tmp1, CMD_READ_STATUS_1);
			spi_flash_cmd_read_status(flash,
				&tmp2, CMD_READ_STATUS_2);
			rt_printf("flash status is %x, %x\n", tmp1, tmp2);
		}

		if (params->flags & SR_1) {
			spi_flash_cmd_read_status(flash,
				&tmp1, CMD_READ_STATUS_1);
			//rt_printf("flash status is %x\n", tmp1);
		}

		if (params->flags & SR_REG1) {
			spi_flash_cmd_read_status(flash,
			&tmp1, CMD_READ_STATUS_1);
			spi_flash_cmd_read_status(flash,
			&tmp2, CMD_READ_STATUS_4);
			spi_flash_cmd_read_status(flash,
			&tmp3, CMD_READ_STATUS_5);
			rt_printf("flash status is %x, %x, %x\n", tmp1, tmp2, tmp3);
		}

	if (flash->size > 0x1000000) {
		spi_flash_enable_4B_mode(flash->spi);
		spi_flash_set_4B_AutoRead(flash->spi);
	} else {
		spi_flash_set_3B_AutoRead(flash->spi);
	}
#ifdef CONFIG_BOARD_RTS3903
	spi_flash_flush_rst_fifo(flash->spi);
	spi_flash_set_rst_fifo(flash->spi, params->reset_flow[0]);
	spi_flash_set_rst_fifo(flash->spi, params->reset_flow[1]);
	spi_flash_set_rst_fifo(flash->spi, params->reset_flow[2]);
#endif
	spi_flash_set_auto_mode(flash->spi);
#ifdef CONFIG_SPI_NOR_PRM_MODE
	spi_flash_set_prm_mode(flash->spi);
#endif
	return flash;
}

#ifdef CONFIG_OF_CONTROL
int spi_flash_decode_fdt(const void *blob, struct spi_flash *flash)
{
	fdt_addr_t addr;
	fdt_size_t size;
	int node;

	/* If there is no node, do nothing */
	node = fdtdec_next_compatible(blob, 0, COMPAT_GENERIC_SPI_FLASH);
	if (node < 0)
		return 0;

	addr = fdtdec_get_addr_size(blob, node, "memory-map", &size);
	if (addr == FDT_ADDR_T_NONE) {
		rt_debug("Cannot decode address\n");
		return 0;
	}

	if (flash->size != size) {
		rt_debug("Memory map must cover entire device\n");
		return -1;
	}
	flash->memory_map = map_sysmem(addr, size);

	return 0;
}
#endif /* CONFIG_OF_CONTROL */

static struct spi_flash *spi_flash_probe_slave(struct spi_slave *spi)
{
	struct spi_flash *flash = NULL;
	u8 idcode[5];
	int ret;

	// char str[32] = {0};
	// str[0] = 0;	// just for remove compile warning.

	/* Setup spi_slave */
	if (!spi) {
		rt_printf("SF: Failed to set up slave\n");
		return NULL;
	}

	/* Claim spi bus */
	ret = spi_claim_bus(spi);
	if (ret) {
		rt_debug("SF: Failed to claim SPI bus: %d\n", ret);
		goto err_claim_bus;
	}

	/* Read the ID codes */
	ret = spi_flash_cmd(spi, CMD_READ_ID, idcode, sizeof(idcode));
	if (ret) {
		rt_printf("SF: Failed to get idcodes\n");
		goto err_read_id;
	}

#ifdef DEBUG
	rt_printf("SF: idcode[]= %02x,%02x,%02x,%02x,%02x\n", idcode[0], idcode[1], idcode[2], idcode[3], idcode[4]);
#endif

	/* Validate params from spi_flash_params table */
	flash = spi_flash_validate_params(spi, idcode);
	if (!flash)
		goto err_read_id;

#ifdef CONFIG_OF_CONTROL
	if (spi_flash_decode_fdt(gd->fdt_blob, flash)) {
		rt_debug("SF: FDT decode error\n");
		goto err_read_id;
	}
#endif
#if CFG_INIT_BSP_SF
	rt_printf("SF: Detected %s ", flash->name);
	// rt_printf("page size %s, ", size_to_str(flash->page_size, str));
	// rt_printf("erase size %s, ", size_to_str(flash->erase_size, str));
	// rt_printf("total %s, ", size_to_str(flash->size, str));
	if (flash->memory_map)
		rt_printf(", mapped at %p", flash->memory_map);
	puts("\n");
#endif
/*
#ifndef CONFIG_SPI_FLASH_BAR
	if (flash->size > SPI_FLASH_16MB_BOUN) {
		puts("SF: Warning - Only lower 16MiB accessible,");
		puts(" Full access #define CONFIG_SPI_FLASH_BAR\n");
	}
#endif
*/
	/* Release spi bus */
	spi_release_bus(spi);

	return flash;

err_read_id:
	spi_release_bus(spi);
err_claim_bus:
	spi_free_slave(spi);
	return NULL;
}

struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int spi_mode)
{
	struct spi_slave *spi;

	spi = spi_setup_slave(bus, cs, max_hz, spi_mode);
	return spi_flash_probe_slave(spi);
}

int spi_flash_exit_QPI(struct spi_flash *flash)
{
	int ret = 0;
	ret = spi_flash_exit_QPI_ops(flash);
	return ret;
}

int spi_flash_exit_prm(struct spi_flash *flash)
{
	int ret = 0;

	ret = spi_flash_exit_prm_ops(flash);
	return ret;
}

int spi_flash_read_word(struct spi_flash *flash, unsigned int offset)
{
	return spi_flash_read_word_ops(flash, offset);
}

#ifdef CONFIG_OF_SPI_FLASH
struct spi_flash *spi_flash_probe_fdt(const void *blob, int slave_node,
				      int spi_node)
{
	struct spi_slave *spi;

	spi = spi_setup_slave_fdt(blob, slave_node, spi_node);
	return spi_flash_probe_slave(spi);
}
#endif

void spi_flash_free(struct spi_flash *flash)
{
	spi_free_slave(flash->spi);
	rt_free(flash);
}
