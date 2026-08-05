/*
 * (C) Copyright 2009
 * Frank Bodammer <frank.bodammer@gcd-solutions.de>
 * (C) Copyright 2009 Semihalf, Grzegorz Bernacki
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#if 0

#include "rt_log.h"
#include "rt_drv.h"
#include "rt_config_rlx.h"
#include "spi.h"
#include "rlx_spi.h"
#include "rlx_bitops.h"
#include "rt_time.h"

// NOTE: please use rt_printf() for msg output through entire file.

static uint8_t QPIMode;
static uint8_t internal_dummy = 1;
static uint8_t flash_rx_cmd(struct rlx_spi_slave *rlxslave, uint8_t cmd);

void spi_init(void)
{

}

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus < 2 && cs < 3;
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
				  unsigned int max_hz, unsigned int mode)
{
	struct rlx_spi_slave *rlxslave;

	if (!spi_cs_is_valid(bus, cs))
		return NULL;

	rlxslave = spi_alloc_slave(struct rlx_spi_slave, bus, cs);
	if (!rlxslave) {
		rt_err("spi_alloc_slave() fail!\n");
		return NULL;
	}

	rlxslave->base_address = get_rlx_spi_base();
	rlxslave->mode = mode;
	rlxslave->fifo_depth = RLX_SPI_FIFO_DEPTH;
	rlxslave->input_hz = 166666700;
	rlxslave->speed_hz = rlxslave->input_hz / 2;
	rlxslave->req_hz = max_hz;
	rlxslave->base_address->ser = 1;
#ifdef CONFIG_TARGET_ASIC
	rlxslave->base_address->baudr = 8;
#endif
#ifdef CONFIG_TARGET_FPGA
	rlxslave->base_address->baudr = 8;
#endif
	rlxslave->base_address->fbaudr = rlxslave->base_address->baudr;

	/*default SPI mode*/
	QPIMode = 0;
	rlxslave->base_address->ssienr = 0;
	rlxslave->base_address->ctrlr0 &= BRADR_SICHAL_RX_HS;
	/*rt_printf("base_addr:%lx, 0x28:%lx,  0x2c:%x,  0xE0:%x, 0xE4:%x,
	0xE8:%x, 0xEC:%x\n",
	rlxslave->base_address, rlxslave->base_address->sr,
	rlxslave->base_address->imr, rlxslave->base_address->rd_fast_single,
	rlxslave->base_address->rd_dual_o, rlxslave->base_address->rd_dual_io,
	rlxslave->base_address->rd_quad_o);*/
	return &rlxslave->slave;
}



/***** spi_flash.functions/spi_flash_setctrlr1()
 * DESCRIPTION
 *  This function is used to set the ctrlr1 controller.
 *  ARGUMENTS
 *  dev         -- DMA controller device handle
 * RETURN VALUE
 *  0           -- if successful
 *  -DW_EINVAL  -- if num_frame is out of range.
 * SEE ALSO
 *  dw_device
 * SOURCE
 */

uint32_t spi_flash_setctrlr1(struct rlx_spi_slave *rlxslave, uint32_t num_frame)
{
	struct spi_flash_portmap *spi_flash_map;

	spi_flash_map = rlxslave->base_address;
	if (num_frame > OVER_MAX_DATA_FRAME) {
		return DW_ENODATA;
	} else {
		spi_flash_map->ctrlr1 = num_frame;

/*	rt_printf("spi_flash_setctrlr1 = 0x%08x\n", spi_flash_map->ctrlr1);*/

		return 0;
	}
}


/*****/

/***** spi_flash.functions/spi_flash_getdr()
 * DESCRIPTION
 *  This function is used to read the ctrlr1 controller.
 *  ARGUMENTS
 *  dev         -- DMA controller device handle
 * RETURN VALUE
 *  uint32_t    -- data popping from FIFO
 * SEE ALSO
 *  dw_device
 * SOURCE
 */

uint32_t spi_flash_getdr(struct rlx_spi_slave *rlxslave,
			enum spi_flash_dr_number dr_num,
			enum spi_flash_byte_num byte_num)
{
	uint32_t data;
	struct spi_flash_portmap *spi_flash_map;

	spi_flash_map = rlxslave->base_address;
#ifdef CONFIG_BOARD_RTS3903
	if (dr_num > DR63)
#else
	if (dr_num > DR31)
#endif
		return DW_ECHRNG;
	else {
		if (byte_num == DATA_BYTE) {
			data = spi_flash_map->dr[0].byte & DR_DATA_BYTE;
		} else if (byte_num == DATA_HALF) {
			data = spi_flash_map->dr[0].half & DR_DATA_HALF;
		} else if (byte_num == DATA_WORD) {
			data =  spi_flash_map->dr[0].word;
		} else
			return DW_EIO;
	}

	return data;
}

void spi_free_slave(struct spi_slave *slave)
{
	rt_free(slave);
}

int spi_claim_bus(struct spi_slave *slave)
{
	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
	return;
}



/*****/
/***** spi_flash.functions/spi_flash_wait_nobusy()
 * DESCRIPTION
 *  This function is used to wait the spi_flash is not at busy state.
 *  ARGUMENTS
 *  dev         -- DMA controller device handle
 * SEE ALSO
 *  dw_device
 * SOURCE
 */

int spi_flash_wait_busy(struct rlx_spi_slave *rlxslave)
{
	struct spi_flash_portmap *spi_flash_map;

	spi_flash_map = rlxslave->base_address;
	int res = 0;

	while (1)
	{
		if (DW_BIT_GET_UNSHIFTED(spi_flash_map->sr, bfoSPI_FLASH_SR_TXE))
		{
			rt_err("transfer error.\n");
			res = -1;
			break;
		}
		else if ((!DW_BIT_GET_UNSHIFTED(spi_flash_map->sr, bfoSPI_FLASH_SR_BUSY)))   /* not busy*/
		{
			break;
		}
		else
		{
			rt_busy_wait_us(25);
			break;
		}
	}
	return res;
}


/*****/

/***** spi_flash.functions/spi_flash_setdr()
 * DESCRIPTION
 *  This function is used to set the ctrlr1 controller.
 *  ARGUMENTS
 *  dev         -- DMA controller device handle
 * RETURN VALUE
 *  0           -- if successful
 *  -DW_ECHRNG  -- if dr_number is out the range
 *  -DW_EINVAL  -- if byte_num argument isn't available
 * SEE ALSO
 *  dw_device
 * SOURCE
 */

uint32_t spi_flash_setdr(struct spi_flash_portmap *spi_flash_map, enum spi_flash_dr_number dr_num,
			uint32_t data, enum spi_flash_byte_num byte_num)
{
	uint32_t wr_data;
	wr_data = data;

#ifdef CONFIG_BOARD_RTS3903
	if (dr_num > DR63)
#else
	if (dr_num > DR31)
#endif
		return DW_EINVAL;
	else {
		if (byte_num == DATA_BYTE) {
			spi_flash_map->dr[0].byte = wr_data;
		} else if (byte_num == DATA_HALF) {
			spi_flash_map->dr[0].half = wr_data;
		} else if (byte_num == DATA_WORD) {
			spi_flash_map->dr[0].word = wr_data;
		} else {
			return DW_EINVAL;
		}
	}
	return 0;
}




uint8_t flash_get_status(struct rlx_spi_slave *rlxslave)
{
	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;

	uint8_t cmd_rdsr = 0x05;

	/* Disable SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/* Set Ctrlr1; 1 byte data frames*/
	spi_flash_map->ctrlr1 = 1;

	spi_flash_map->addr_length = 0;
	/* Set tuning dummy cycles*/
	DW_BITS_SET_VAL(spi_flash_map->auto_length, bfoSPI_FLASH_AUTO_LEN_DUM,
	0, bfwSPI_FLASH_AUTO_LEN_DUM);

	flash_rx_cmd(rlxslave, cmd_rdsr);

	return spi_flash_getdr(rlxslave, DR0, DATA_BYTE);
}
void manual_check_flash_status(struct rlx_spi_slave *rlxslave)
{
	struct spi_flash_portmap *spi_flash_map;

	spi_flash_map = rlxslave->base_address;
	/*Check flash is in write progress or not*/
	while (1) {
		if (!(flash_get_status(rlxslave) & 0x1)) {
			spi_flash_map->ssienr = 0;
			break; }
	}
}
void auto_check_flash_status(struct rlx_spi_slave *rlxslave)
{
	struct spi_flash_portmap *spi_flash_map;
	u8 timeout_flag = 0;

	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = spi_flash_map->ssienr & SPIC_DISABLE;
	spi_flash_map->ctrlr0 = (spi_flash_map->ctrlr0 | TIME_OUT_VALUE_H) & TIME_OUT_VALUE_L;
	spi_flash_map->imr = spi_flash_map->imr | AUTO_CHECK_INT_EN;
	spi_flash_map->ssienr = spi_flash_map->ssienr | 3;
	/*rt_printf("ssienr=%x,ctrlr0=%x,imr=%x\n",spi_flash_map->ssienr,spi_flash_map->ctrlr0,spi_flash_map->imr);*/
	while (1) {
		if (DW_BIT_GET_UNSHIFTED(spi_flash_map->risr, bfoSPI_FLASH_RISR_ACSIR)) {
			DW_BIT_SET(spi_flash_map->icr, 0);
			spi_flash_map->ssienr = 0;
			/*rt_printf("risr = %x\n",spi_flash_map->risr);*/
			break; }
		else if (DW_BIT_GET_UNSHIFTED(spi_flash_map->risr, bfoSPI_FLASH_RISR_ACTIR)) {
			DW_BIT_SET(spi_flash_map->icr, 0);
			timeout_flag = 1;
			break;
			/*rt_printf("auto-check timeout\n");*/} }
	if (timeout_flag == 1) {
		timeout_flag = 0;
		manual_check_flash_status(rlxslave);
	}
}

void flash_wait_busy(struct rlx_spi_slave *rlxslave)
{

#ifdef CONFIG_BOARD_RTS3903
	auto_check_flash_status(rlxslave);
#else
	manual_check_flash_status(rlxslave);
#endif
}

static uint8_t flash_rx_cmd(struct rlx_spi_slave *rlxslave, uint8_t cmd)
{
	struct spi_flash_portmap *spi_flash_map;
	uint32_t rd_data;
	int res = 0;


	spi_flash_map = rlxslave->base_address;
	/*rt_printf("set rx_cmd address:%x\n", (int)spi_flash_map);*/
	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/* set ctrlr0: RX_mode*/
	rd_data = spi_flash_map->ctrlr0;

	if (QPIMode == 1)
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS) | RX_MODE|QPI_CHN_SETTING;
	else
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS) | RX_MODE;

	/* set flash_cmd: write cmd to fifo*/
	spi_flash_setdr(spi_flash_map, DR0, cmd, DATA_BYTE);

	/*rt_printf("bef enable spi_flash, cmd is %x, ser is %x, ctrl0 is %x\n", cmd, spi_flash_map->ser, spi_flash_map->ctrlr0);*/
	/* Enable SPI_FLASH*/
	spi_flash_map->ssienr = 1;
	/*rt_printf("rx cmd wait\n");*/
	res = spi_flash_wait_busy(rlxslave);

	if (res != 0) {
		rt_err("spi_flash_wait_busy, res= %d\n", res);
		return res;
	}

	/*rt_printf("rx_cmd end\n");*/

	return res;
}


int flash_tx_cmd(struct rlx_spi_slave *rlxslave, uint8_t cmd)
{
	struct spi_flash_portmap *spi_flash_map;
	/* struct device_info inst_info;*/
	uint32_t rd_data;
	int tmp, res = 0;

	spi_flash_map = rlxslave->base_address;

	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;
	tmp = spi_flash_map->auto_length;

	/* set ctrlr0: TX mode*/
	rd_data = spi_flash_map->ctrlr0;
	if (QPIMode == 1)
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS) | QPI_CHN_SETTING;
	else
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS);

	/* set flash_cmd: wren to fifo*/
	spi_flash_setdr(spi_flash_map, DR0, cmd, DATA_BYTE);

	/* Enable SPI_FLASH*/
	spi_flash_map->ssienr = 1;

	res = spi_flash_wait_busy(rlxslave);

	spi_flash_map->ssienr = 0;
	spi_flash_map->auto_length = tmp;

	if (res != 0) {
		rt_err("spi_flash_wait_busy, res= %d\n", res);
		return res;
	}

	return res;
}



int flash_set_status(struct spi_slave *spi, u16 data, u8 cmd, u8 data_len)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;
	uint8_t cmd_wrsr, rd_data;
	uint32_t info;
	int res = 0;
	info = spi_flash_map->addr_length;


	/* Set flash_cmd: WREN to FIFO*/
	res = flash_tx_cmd(rlxslave, spi->wrsr_en_cmd);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	/* Disable SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/* set ctrlr0: TX mode*/
	rd_data = spi_flash_map->ctrlr0;
	if (QPIMode == 1)
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS) | QPI_CHN_SETTING;
	else
		spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS);

	spi_flash_map->addr_length = data_len;

	/* Set flash_cmd: WRSR to FIFO*/
	cmd_wrsr = cmd;

	spi_flash_map->dr[DR0].byte = cmd_wrsr;


	spi_flash_map->dr[DR0].byte = data&0xff;
	if (data_len == 2)
		spi_flash_map->dr[DR0].byte = data>>8;

	spi_flash_map->ssienr = 1;
	spi_flash_wait_busy(rlxslave);

	spi_flash_map->ssienr = 0;
	spi_flash_map->addr_length = info;

	flash_wait_busy(rlxslave);
	return res;
}

int flash_flush_rst_fifo(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = 0;
	spi_flash_map->flush_fifo = 2;

	return 0;
}

int flash_enable_prm(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = 0;
	spi_flash_map->valid_cmd = spi_flash_map->valid_cmd | PRM_MODE_EN;

	return 0;
}

int flash_disable_prm(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;

	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = 0;
	spi_flash_map->valid_cmd = spi_flash_map->valid_cmd & PRM_MODE_DIS;

	return 0;
}

int flash_set_reset_test(struct spi_slave *spi, u8 channel, u8 cmd)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	struct spi_flash_portmap *spi_flash_map;

	u8 channel_tmp, cmd_tmp, tmp;
	int res = 0;
	uint32_t rd_data;
	channel_tmp = channel;
	cmd_tmp = cmd;
	if (channel_tmp == 4)
	{
		QPIMode = 1;
		res = flash_tx_cmd(rlxslave, cmd_tmp);
	}
	else if (channel_tmp == 1)
	{
		QPIMode = 0;
		res = flash_tx_cmd(rlxslave, cmd_tmp);
	}
	else
	{
		spi_flash_map = rlxslave->base_address;

		/* Disble SPI_FLASH*/
		spi_flash_map->ssienr = 0;
		tmp = spi_flash_map->auto_length;

		/* set ctrlr0: TX mode*/
		rd_data = spi_flash_map->ctrlr0;
		spi_flash_map->ctrlr0 = (rd_data & 0xffc0fcff) | 0x00100000;

		/* set flash_cmd: wren to fifo*/
		spi_flash_setdr(spi_flash_map, DR0, cmd, DATA_BYTE);

		/* Enable SPI_FLASH*/
		spi_flash_map->ssienr = 1;

		res = spi_flash_wait_busy(rlxslave);

		spi_flash_map->ssienr = 0;
		spi_flash_map->auto_length = tmp;

		if (res != 0)
		{
			rt_err("spi_flash_wait_busy, res= %d\n", res);
			return res;
		}
	}
	/*res = flash_tx_cmd(rlxslave, cmd_tmp);*/
	rt_printf("send channel = %x cmd = %x\n", channel_tmp, cmd_tmp);
	return res;
}

/*only in QPI mode*/
int flash_set_read_para(struct spi_slave *spi, u16 data, u8 cmd, u8 data_len)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;
	uint8_t cmd_wrsr, rd_data;
	uint32_t info;
	int res = 0;
	info = spi_flash_map->addr_length;


	/* Set flash_cmd: WREN to FIFO*/
	res = flash_tx_cmd(rlxslave, 0x06);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	/* Disable SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/* set ctrlr0: TX mode*/
	rd_data = spi_flash_map->ctrlr0;

	spi_flash_map->ctrlr0 = (rd_data & BRADR_SICHAL_TX_HS) | QPI_CHN_SETTING;

	spi_flash_map->addr_length = data_len;

	/* Set flash_cmd: WRSR to FIFO*/
	cmd_wrsr = cmd;

	spi_flash_map->dr[DR0].byte = cmd_wrsr;

	spi_flash_map->dr[DR0].byte = data&0xff;

	spi_flash_map->ssienr = 1;
	spi_flash_wait_busy(rlxslave);

	spi_flash_map->ssienr = 0;
	spi_flash_map->addr_length = info;

	flash_wait_busy(rlxslave);
	return res;
}


int flash_enable_write(struct spi_slave *spi)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;
	/*   spi_flash_map = dev->base_address;*/

	res = flash_tx_cmd(rlxslave, 0x06);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

/*	rt_printf("wren end\n");*/
	return res;
}


int flash_disable_write(struct spi_slave *spi)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;

	res = flash_tx_cmd(rlxslave, 0x04);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	return res;
}

int flash_enable_qpi(struct spi_slave *spi, u8 cmd)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;

	/* Set flash_cmd: WREN to FIFO*/
	res = flash_tx_cmd(rlxslave, 0x06);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	res = flash_tx_cmd(rlxslave, cmd);

	QPIMode = 1;
	flash_wait_busy(rlxslave);
	return res;
}

int flash_exit_qpi(struct spi_slave *spi, u8 cmd)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;

	res = flash_tx_cmd(rlxslave, cmd);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	QPIMode = 0;
	flash_wait_busy(rlxslave);

	return res;
}

int flash_enable_4B(struct spi_slave *spi)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;
	/*   spi_flash_map = dev->base_address;*/

	res = flash_tx_cmd(rlxslave, ENABLE_4BYTE_MODE);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

/*	rt_printf("wren end\n");*/
	return res;
}


int flash_exit_4B(struct spi_slave *spi)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int res = 0;

	res = flash_tx_cmd(rlxslave, EXIT_4BYTE_MODE);
	if (res) {
		rt_err("flash_tx_cmd, res= %d\n", res);
		return res;
	}

	return res;
}

int spi_flash_set_AutoRead_AddrLen(struct spi_slave *spi, u8 addr_len)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = 0;
	spi_flash_map = rlxslave->base_address;
	if (addr_len == 4)
		DW_BITS_SET_VAL(spi_flash_map->auto_length, bfoSPI_FLASH_AUTO_LEN_ADDR,
		0, bfwSPI_FLASH_AUTO_LEN_ADDR);
	else
		DW_BITS_SET_VAL(spi_flash_map->auto_length, bfoSPI_FLASH_AUTO_LEN_ADDR,
		3, bfwSPI_FLASH_AUTO_LEN_ADDR);

	return 0;
}

/*****/

/***** spi_flash.functions/dw_set_dummy_cycle()
 * DESCRIPTION
 *  This function is used to set the Baudr controller.
 *  ARGUMENTS
 *  dev         -- DMA controller device handle
 * RETURN VALUE
 *  0           -- if successful
 *  -DW_EINVAL  -- if dum_cycle is out the range
 * SEE ALSO
 *  dw_device
 * SOURCE
 */
uint32_t spi_flash_set_dummy_cycle(struct spi_flash_portmap *spi_flash_map, uint32_t dum_cycle)
{
	uint32_t cycle;

	/* Disable SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/* if using fast_read baud_rate*/
	if (((spi_flash_map->ctrlr0) & 0x00400000))
		cycle = (spi_flash_map->fbaudr);
	else
		cycle = (spi_flash_map->baudr);

	if (dum_cycle != 0)
		cycle = (cycle * dum_cycle * 2) + internal_dummy;
	else
		cycle = 0;

	if (cycle > 0x10000)
		return DW_ECHRNG;

	DW_BITS_SET_VAL(spi_flash_map->auto_length, bfoSPI_FLASH_AUTO_LEN_DUM,
			cycle, bfwSPI_FLASH_AUTO_LEN_DUM);

	return 0;
}


uint32_t rlx_flash_read(struct rlx_spi_slave *rlxslave, const u8 *cmd, size_t cmd_len, u8 *data_in, u16 data_len)
{
	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;

	uint32_t ctrlr0, rd_data = 0;
	int i, j, res = 0;

	/* set ctrlr0: RX_mode*/
	ctrlr0 = spi_flash_map->ctrlr0;
	if (QPIMode == 1)
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE
			| QPI_CHN_SETTING;
	/* SPI mode */
	else if (rlxslave->slave.autoread_type & RD_QUAD_IO_T)
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE
			| CMD_1CHN | ADDR_4CHN | DATA_4CHN;
	else if (rlxslave->slave.autoread_type & RD_QUAD_O_T)
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE
			| CMD_1CHN | ADDR_1CHN | DATA_4CHN;
	else if (rlxslave->slave.autoread_type & RD_DUAL_IO_T)
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE
			| CMD_1CHN | ADDR_2CHN | DATA_2CHN;
	else if (rlxslave->slave.autoread_type & RD_DUAL_O_T)
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE
			| CMD_1CHN | ADDR_1CHN | DATA_2CHN;
	else
		spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | RX_MODE;

#if defined(CONFIG_SPI_NOR_PRM_MODE)
	if (cmd_len == 5)
		spi_flash_map->addr_length = 4;
	else
		spi_flash_map->addr_length = 0;
#else
	spi_flash_map->addr_length = (cmd_len - 1)%4;
#endif

	if (cmd[0] == 0x9f)
		spi_flash_set_dummy_cycle(spi_flash_map, 0);
	else
		spi_flash_set_dummy_cycle(spi_flash_map, rlxslave->slave.dummy_cycle);
	spi_flash_setctrlr1(rlxslave, data_len);


	/* Write cmd, addr, data into FIFO*/
	spi_flash_setdr(spi_flash_map, DR0, cmd[0], DATA_BYTE);
	for (i = 1; i <= (int)(cmd_len - 1); i++) {
		spi_flash_setdr(spi_flash_map, DR0, cmd[i], DATA_BYTE);
	}

	/*add one byte 0xff for invalid PRM value*/
#if defined(CONFIG_SPI_NOR_PRM_MODE)
	spi_flash_setdr(spi_flash_map, DR0, 0xff, DATA_BYTE);
#endif

	/* Enable SPI_FLASH*/
	spi_flash_map->ssienr = 1;

	res = spi_flash_wait_busy(rlxslave);
	if (res) {
		rt_err("spi_flash_wait_busy, res= %d\n", res);
		return res;
	}
	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	for (i = 0; i < (data_len/4); i++) {
		rd_data = spi_flash_getdr(rlxslave, i, DATA_WORD);
		for (j = 0; j < 4; j++) {
			*data_in = ((rd_data >> (j*8))&0xff);
			data_in++;
		}
	}

	for (i = 0; i < (data_len%4); i++) {
		rd_data = spi_flash_getdr(rlxslave, i, DATA_BYTE);
		*data_in = rd_data&0xff;
		data_in++;
	}

	return res;
}



int rlx_flash_write(struct rlx_spi_slave *rlxslave, const u8 *cmd, size_t cmd_len, const u8 *data_out, u16 data_len)
{
	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;

	int res = 0;
	int i, j;
	u32 tmp, tmp_len;
	u32 init_data;

	/*set ctrlr0: TX mode*/
	init_data = spi_flash_map->ctrlr0;
	tmp_len = spi_flash_map->auto_length;

	if (cmd[0] == 0x01)
		spi_flash_map->addr_length = 1;
	else
		spi_flash_map->addr_length = (cmd_len - 1)%4;

	/* Write cmd, addr, data into FIFO*/
	spi_flash_setdr(spi_flash_map, DR0, cmd[0], DATA_BYTE);
/*	rt_printf("write %x ", cmd[0]);*/
	for (i = 1; i < (int)cmd_len; i++) {
/*		rt_printf("%x ", cmd[i]);*/
		spi_flash_setdr(spi_flash_map, DR0, cmd[i], DATA_BYTE);
	}
/*	rt_printf("data len is %x, addr len is %x\n", data_len, spi_flash_map->addr_length);*/

	if (data_out != NULL) {
		switch (rlxslave->slave.userwrite_type) {
		case WR_QUAD_II_T:
			spi_flash_map->ctrlr0 = (init_data & BRADR_SICHAL_TX_HS) | (DA_AD_QUAD);
			break;

		case WR_QUAD_I_T:
			spi_flash_map->ctrlr0 = (init_data & BRADR_SICHAL_TX_HS) | (DA_QUAD_AD_SI);
			break;

		case WR_DUAL_II_T:
			spi_flash_map->ctrlr0 = (init_data & BRADR_SICHAL_TX_HS) | (DA_AD_DUAL);
			break;

		case WR_DUAL_I_T:
			spi_flash_map->ctrlr0 = (init_data & BRADR_SICHAL_TX_HS) | (DA_AD_DUAL);
			break;

		default:
			spi_flash_map->ctrlr0 = init_data & BRADR_SICHAL_TX_HS;
			break;
		}

		for (i = 0; i < (data_len/4); i++) {
			tmp = 0;
			for (j = 0; j < 4; j++) {
				tmp = (*data_out << (j*8)) | tmp;
				data_out++;
			}
			spi_flash_setdr(spi_flash_map, i, tmp, DATA_WORD);
		}

		for (i = 0; i < (data_len%4); i++) {
			tmp = *data_out;
			spi_flash_setdr(spi_flash_map, i, tmp, DATA_BYTE);
			data_out++;
		}
	} else {
			spi_flash_map->ctrlr0 = (init_data & BRADR_SICHAL_TX_HS);
	}

	if (QPIMode == 1)
		spi_flash_map->ctrlr0 |= QPI_CHN_SETTING;

	/*rt_printf("write type %x, %x, %x\n", rlxslave->slave.userwrite_type, cmd[0], spi_flash_map->ctrlr0);*/

	/* Enable SPI_FLASH*/
	spi_flash_map->ssienr = 1;

/*	rt_printf("after enable flash\n");*/

#ifdef INTERRUPT_TEST_SPIC
	/* if write data to flash, send much more to fifo overflow */
	if (data_len > 0x7f) {
		int i = 100;
		*((volatile unsigned int *)0xb803002c) = 0x3f;
		while (i--)
			spi_flash_setdr(spi_flash_map, DR0, 1, DATA_WORD);
		/* Open txfir interrupt */
		while (1)
			;
	}
#endif
	res = spi_flash_wait_busy(rlxslave);

	if (res) {
		rt_err("spi_flash_wait_busy, res= %d\n", res);
		return res;
	}

	flash_wait_busy(rlxslave);
	spi_flash_map->ssienr = 0;
	spi_flash_map->auto_length = tmp_len;
	return res;
}


int spi_flash_read_write(struct spi_slave *spi,
				const u8 *cmd, size_t cmd_len,
				const u8 *data_out, u8 *data_in,
				size_t data_len)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	int i, len_tmp, tmp, ret = 0;

	spi_flash_map = rlxslave->base_address;
	/* Disable SPI_FLASH*/
	spi_flash_map->ssienr = 0;


	if (data_in == NULL) {
		/*write command*/
		/* Disble SPI_FLASH*/
		spi_flash_map->ssienr = 0;

		ret = rlx_flash_write(rlxslave, cmd, cmd_len, data_out, data_len);
	} else if (data_out == NULL) {
		/*read command*/
		/*disable SPI_FLASH*/
		spi_flash_map->ssienr = 0;

		tmp = spi_flash_map->auto_length;
		DW_BITS_SET_VAL(spi_flash_map->auto_length, bfoSPI_FLASH_AUTO_LEN_DUM,
				0, bfwSPI_FLASH_AUTO_LEN_DUM);

		if (cmd_len == 1) {
			/*no address read command*/
			if (*cmd == 0x9f)	/*read  id command*/ {
				len_tmp = 3;
			} else {
				len_tmp = data_len;
			}
			spi_flash_setctrlr1(rlxslave, len_tmp);
			flash_rx_cmd(rlxslave, *cmd);
			for (i = 0; i < len_tmp; i++) {
				*data_in = spi_flash_getdr(rlxslave, DR0, DATA_BYTE);
				data_in++;
			}
		} else {
			ret = rlx_flash_read(rlxslave, cmd, cmd_len, data_in, data_len);
		}
		spi_flash_map->ssienr = 0;
		spi_flash_map->auto_length = tmp;
	}

	return ret;
}

int spi_flash_set_auto(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	spi_flash_map = rlxslave->base_address;

	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;



	/*Set valid_cmd_reg: auto_cmd*/
	/*
	if (spi->autorw_type & WR_QUAD_II_T) {
		spi_flash_map->wr_quad_ii = spi->write_cmd;
	} else if(spi->autorw_type & WR_QUAD_I_T) {
		spi_flash_map->wr_quad_i = spi->write_cmd;
	} else if (spi->autorw_type == WR_DUAL_II_T) {
		spi_flash_map->wr_dual_ii = spi->write_cmd;
	} else if (spi->autorw_type == WR_DUAL_I_T) {
		spi_flash_map->wr_dual_i = spi->write_cmd;
	}
	*/

	if (spi->autoread_type & RD_QUAD_IO_T) {
		spi_flash_map->rd_quad_io = spi->read_cmd;
	} else if (spi->autoread_type & RD_QUAD_O_T) {
		spi_flash_map->rd_quad_o = spi->read_cmd;
	} else if (spi->autoread_type & RD_DUAL_IO_T) {
		spi_flash_map->rd_dual_io = spi->read_cmd;
	} else if (spi->autoread_type & RD_DUAL_O_T) {
		spi_flash_map->rd_dual_o = spi->read_cmd;
	} else if (spi->autoread_type & FRD_SINGLE_T) {
		spi_flash_map->rd_fast_single  = spi->read_cmd;
	}

	spi_flash_set_dummy_cycle(spi_flash_map, spi->dummy_cycle);

	spi_flash_map->valid_cmd = (spi->autoread_type | 0x200);

/*	rt_printf("set auto command, %x,  %x, %x\n", spi_flash_map->auto_length,  spi->autoread_type, spi_flash_map->valid_cmd);*/
	return 0;
}


int spi_flash_set_prm(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);

	spi_flash_map = rlxslave->base_address;

	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	/*set prm value
	 *notice DUAL_IO mode use fast_single register when using prm,
	 *prm value is also for DUAL_IO.
	 */
	if (spi->autoread_type & RD_QUAD_IO_T) {
		spi_flash_map->rd_quad_io = (spi_flash_map->rd_quad_io
					& PRM_VALUE_CLR) | PRM_VALUE_VA;
	} else if (spi->autoread_type & RD_DUAL_IO_T) {
		spi_flash_map->rd_fast_single = spi->read_cmd;
		spi_flash_map->rd_quad_io = (spi_flash_map->rd_quad_io
					& PRM_VALUE_CLR) | PRM_VALUE_VA;
		spi_flash_map->ctrlr0 = (spi_flash_map->ctrlr0 | DA_AD_DUAL);
		spi_flash_map->valid_cmd = spi_flash_map->valid_cmd
					| CTRLR0_CH_FRD_SI_EN;
	}

	spi_flash_map->valid_cmd = spi_flash_map->valid_cmd | PRM_MODE_EN;

	return 0;
}

int spi_flash_set_user(struct spi_slave *spi)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	spi_flash_map = rlxslave->base_address;

	spi_flash_map->ssienr = 0;
	spi_flash_map = rlxslave->base_address;
	spi_flash_map->valid_cmd = 0x200;

	return 0;
}

int flash_set_rst_fifo(struct spi_slave *spi, u16 reset_flow)
{
	struct spi_flash_portmap *spi_flash_map;
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	/*u8 counter_tmp, state_tmp, ctrl_channel_tmp, cmd_val_tmp;*/
	u16 value_tmp;
	spi_flash_map = rlxslave->base_address;


	value_tmp = reset_flow;
	/*counter_tmp = value_tmp >> 12;
	state_tmp = (value_tmp >> 10) & 0x03;
	ctrl_channel_tmp = (value_tmp >> 8) & 0x03;
	cmd_val_tmp = value_tmp & 0x00ff;*/
	/*rt_printf("value=%x counter=%x state=%x ctrl_channel=%x cmd_val=%x\n", value_tmp, counter_tmp, state_tmp, ctrl_channel_tmp, cmd_val_tmp);*/
	/*Set valid_cmd_reg: auto_cmd*/
	/*
	if (spi->autorw_type & WR_QUAD_II_T) {
		spi_flash_map->wr_quad_ii = spi->write_cmd;
	} else if(spi->autorw_type & WR_QUAD_I_T) {
		spi_flash_map->wr_quad_i = spi->write_cmd;
	} else if (spi->autorw_type == WR_DUAL_II_T) {
		spi_flash_map->wr_dual_ii = spi->write_cmd;
	} else if (spi->autorw_type == WR_DUAL_I_T) {
		spi_flash_map->wr_dual_i = spi->write_cmd;
	}
	*/
	/*rt_printf("value=%x\n", value_tmp);*/
	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;

	spi_flash_map->rst_fifo = value_tmp;
/*	rt_printf("set auto command, %x,  %x, %x\n", spi_flash_map->auto_length,  spi->autoread_type, spi_flash_map->valid_cmd);*/
	return 0;
}

/*tx mode,SPIC send 3byte address + 1byte prm value + 2byte data,
 *channel is 4-4-4,
 *all value just only is 0xff,let SPIC and flash exit prm mode.
 */
int flash_exit_prm(struct spi_slave *spi)
{
	struct rlx_spi_slave *rlxslave = to_rlx_spi(spi);
	struct spi_flash_portmap *spi_flash_map = rlxslave->base_address;

	u32 ctrlr0 = 0;
	int i, res = 0;
	char cmd[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	spi_flash_map->ssienr = 0;

	/* set ctrlr0: TX_mode*/
	ctrlr0 = spi_flash_map->ctrlr0;

	spi_flash_map->ctrlr0 = (ctrlr0 & BRADR_SICHAL_TX_HS) | QPI_CHN_SETTING;

	spi_flash_map->addr_length = spi_flash_map->addr_length | 3;

	for (i = 0; i <= 5; i++)
		spi_flash_setdr(spi_flash_map, DR0, cmd[i], DATA_BYTE);

	/* Enable SPI_FLASH*/
	spi_flash_map->ssienr = 1;

	res = spi_flash_wait_busy(rlxslave);
	if (res) {
		rt_err("spi_flash_wait_busy, res= %d\n", res);
		return res;
	}

	/* Disble SPI_FLASH*/
	spi_flash_map->ssienr = 0;
	spi_flash_map->ctrlr0 = ctrlr0;

	return res;
}
#endif
