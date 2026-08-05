/**************************************************************************//**
 * @file     rom_i2c.c
 * @brief    This file implements the I2C HAL functions.
 *
 * @version  V1.00
 * @date     2017-03-07
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/


#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif
#include "rtl8735b_i2c_simple.h"
#include "isp_log.h"
#include "hal_timer.h"
#include "platform_conf.h"

#if 1

/**
 * @addtogroup hs_hal_i2c I2C
 * @{
 */

/** \brief Description of hal_rtl_i2c_set_clk_simple
 *
 *    hal_rtl_i2c_set_clk_simple is used to set I2C clock.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return hal_status_t:      HAL status.
 */
hal_status_t hal_rtl_i2c_set_clk_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
    uint32_t clock   = phal_i2c_adapter->init_dat.clock;
    uint32_t ic_hl_cnt;
    uint32_t ic_h_time;
    uint32_t ic_l_time;

    /* Get the IC-Clk setting first for the following process*/
#if CONFIG_FPGA // FPGA
    uint32_t sys_clk  = (400000000/4)/1000000;
#else
    uint32_t sys_clk  = (400000000/4)/1000000;
#endif

    isp_info("hal_rtl_i2c_set_clk_simple, spd mod: %x\n\r", phal_i2c_adapter->init_dat.spd_mod);

    switch (phal_i2c_adapter->init_dat.spd_mod) {
        case I2CStandardSpeed:
            ic_h_time = ((1000000/clock)*I2C_SS_MIN_SCL_HTIME)/(I2C_SS_MIN_SCL_HTIME+I2C_SS_MIN_SCL_LTIME);
            ic_l_time = ((1000000/clock)*I2C_SS_MIN_SCL_LTIME)/(I2C_SS_MIN_SCL_HTIME+I2C_SS_MIN_SCL_LTIME);

            ic_hl_cnt = (ic_h_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_SS_HTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>4) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 4;
            //}

            pi2c_reg->I2C_SS_SCL_HCNT = ic_hl_cnt;
            isp_info("ICHtime:%x\n\r", pi2c_reg->I2C_SS_SCL_HCNT);
            ic_hl_cnt = (ic_l_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_SS_LTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>3) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 3;
            //}
            pi2c_reg->I2C_SS_SCL_LCNT = ic_hl_cnt;
            isp_info("ICLtime:%x\n\r", pi2c_reg->I2C_SS_SCL_LCNT);
            break;

        case I2CFastSpeed:
            ic_h_time = ((1000000/clock)*I2C_FS_MIN_SCL_HTIME)/(I2C_FS_MIN_SCL_HTIME+I2C_FS_MIN_SCL_LTIME);
            ic_l_time = ((1000000/clock)*I2C_FS_MIN_SCL_LTIME)/(I2C_FS_MIN_SCL_HTIME+I2C_FS_MIN_SCL_LTIME);

            ic_hl_cnt = (ic_h_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_FS_HTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                isp_error("h_cnt: %x\n\r", ic_hl_cnt);
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>4) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 4;
            //}

            pi2c_reg->I2C_FS_SCL_HCNT = ic_hl_cnt;
            isp_info("fs_scl_hcnt%d: %x\n\r", phal_i2c_adapter->init_dat.index, pi2c_reg->I2C_FS_SCL_HCNT);
            ic_hl_cnt = (ic_l_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_FS_LTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                isp_error("h_cnt: %x\n\r", ic_hl_cnt);
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>3) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 3;
            //}

            pi2c_reg->I2C_FS_SCL_LCNT = ic_hl_cnt;
            isp_info("fs_scl_lcnt%d: %x\n\r", phal_i2c_adapter->init_dat.index, pi2c_reg->I2C_FS_SCL_LCNT);
            break;

        case I2CHighSpeed:
            ic_hl_cnt = 400;
            pi2c_reg->I2C_SS_SCL_HCNT = ic_hl_cnt;

            ic_hl_cnt = 470;
            pi2c_reg->I2C_SS_SCL_LCNT = ic_hl_cnt;

            ic_hl_cnt = 60;
            pi2c_reg->I2C_FS_SCL_HCNT = ic_hl_cnt;

            ic_hl_cnt = 130;
            pi2c_reg->I2C_FS_SCL_LCNT = ic_hl_cnt;

            ic_h_time = ((1000000/clock)*I2C_HS_MIN_SCL_HTIME_100)/(I2C_HS_MIN_SCL_HTIME_100+I2C_HS_MIN_SCL_LTIME_100);
            ic_l_time = ((1000000/clock)*I2C_HS_MIN_SCL_LTIME_100)/(I2C_HS_MIN_SCL_HTIME_100+I2C_HS_MIN_SCL_LTIME_100);
            isp_info("ICHtime:%x\n\r", ic_h_time);
            isp_info("ICLtime:%x\n\r", ic_l_time);

            ic_hl_cnt = (ic_h_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_HS_HTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>8) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 3;
            //}

            pi2c_reg->I2C_HS_SCL_HCNT = ic_hl_cnt;
            isp_info("hs_scl_hcnt%d: %x\n\r", phal_i2c_adapter->init_dat.index, pi2c_reg->I2C_HS_SCL_HCNT);

            ic_hl_cnt = (ic_l_time * sys_clk)/1000;
            if (ic_hl_cnt < I2C_HS_LTIME_MIN) {
                isp_error("*** I2C clock is not available.\n\r");
                return HAL_ERR_PARA;
            }
            //if (ic_hl_cnt>6) {/*this part is according to the fine-tune result*/
            //    ic_hl_cnt -= 6;
            //}

            pi2c_reg->I2C_HS_SCL_LCNT = ic_hl_cnt;
            isp_info("hs_scl_lcnt%d: %x\n\r", phal_i2c_adapter->init_dat.index, pi2c_reg->I2C_HS_SCL_LCNT);
            break;

        default:
            break;
    }

    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_en_ctrl_simple
 *
 *    hal_rtl_i2c_en_ctrl_simple is used to enable/disable I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable: To enable/disable I2C.\n\r
 *                                  0: Disable.\n\r
 *                                  1: Enable\n\r
 *                                  2: Force Disable
 *   \retrun uint8_t:               I2C enable status.
 */
uint8_t hal_rtl_i2c_en_ctrl_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
    I2C_TypeDef *pi2c_reg = phal_i2c_adapter->init_dat.reg_base;
    uint32_t ic_en_tmp;

    ic_en_tmp = pi2c_reg->I2C_ENABLE;
    if (enable == 2) {
        HAL_SET_BIT(ic_en_tmp, I2C_BIT_ABRT);
        HAL_CLEAR_BIT(ic_en_tmp, I2C_BIT_EN);
    } else if (enable == 0) {
        HAL_CLEAR_BIT(ic_en_tmp, I2C_BIT_ABRT);
        HAL_CLEAR_BIT(ic_en_tmp, I2C_BIT_EN);
    } else {
        HAL_CLEAR_BIT(ic_en_tmp, I2C_BIT_ABRT);
        HAL_SET_BIT(ic_en_tmp, I2C_BIT_EN);
    }

    /* Enable/Disable I2C module */
    pi2c_reg->I2C_ENABLE = ic_en_tmp;
    isp_info("ic_enable(%x): %x, %x\n\r", &(pi2c_reg->I2C_ENABLE), pi2c_reg->I2C_ENABLE, ic_en_tmp);
    //DBG_8195BL("ic_enable(%x): %x\n\r", &(pi2c_reg->enable), pi2c_reg->enable);

    if (enable != 1) {
        while (pi2c_reg->I2C_EN_STS & I2C_BIT_EN_STS) {
        }
    } else {
        while (!(pi2c_reg->I2C_EN_STS & I2C_BIT_EN_STS)) {
        }
    }

    return (uint8_t)(pi2c_reg->I2C_EN_STS & I2C_BIT_EN_STS);
}


/// @cond DOXYGEN_ROM_HAL_API

/** \brief Description of hal_rtl_i2c_timeout_chk_simple
 *
 *    hal_rtl_i2c_timeout_chk_simple is used to check if I2C operation is time-out.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter: Pointer to I2C control adapter.
 *   \param[in] uint32_t start_cnt: Start system time count.
 *
 *   \return uint8_t:       Time out result \n\r\t
 *                          0: NOT time-out, 1: Time-out.
 */
uint8_t hal_rtl_i2c_timeout_chk_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint32_t start_cnt)
{
    uint32_t time_out_cnt = 0;
    uint32_t curr_cnt = 0;
    uint32_t expire_cnt = 0;
	static uint32_t i2c_log_cnt = 0;

    if ((phal_i2c_adapter->pltf_dat.tr_time_out != HP_I2C_TIMEOUT_DISABLE) &&
                (phal_i2c_adapter->pltf_dat.tr_time_out != HP_I2C_TIMEOUT_ENDLESS)) {
        time_out_cnt = phal_i2c_adapter->pltf_dat.tr_time_out;
        curr_cnt = hal_read_curtime_us();

        if (start_cnt <= curr_cnt) {
            expire_cnt =  curr_cnt - start_cnt;//(0xFFFFFFFF - curr_cnt) + start_cnt;
        } else {
            expire_cnt = (0xFFFFFFFF - start_cnt) + curr_cnt;//start_cnt - curr_cnt;
        }

        if (time_out_cnt < expire_cnt){
            return 1;//time-out
        } else {
        	if (time_out_cnt > 30000 && i2c_log_cnt == 0) {
        		printf("i2c time_out_cnt: %x, curr_cnt: %x, start_cnt: %x, expire_cnt: %x\n\r",
					time_out_cnt, curr_cnt, start_cnt, expire_cnt);
				i2c_log_cnt = 1;
        	} else if (time_out_cnt < 30000) {
				i2c_log_cnt = 0;
        	}
            return 0;
        }
    } else if (phal_i2c_adapter->pltf_dat.tr_time_out == HP_I2C_TIMEOUT_DISABLE) {
        return 1;   //time-out
    }

    return 0;
}

/** \brief Description of hal_rtl_i2c_chk_mod_simple
 *
 *    hal_rtl_i2c_chk_mod_simple is used to check I2C operation mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:           Check mode status. \n\r
 *                              0: Slave mode\n\r
 *                              1: Master mode\n\r
 *                              2: Configuration error.\n\r
 */
uint8_t hal_rtl_i2c_chk_mod_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    uint32_t ic_con_tmp;

    ic_con_tmp = phal_i2c_adapter->init_dat.reg_base->I2C_CON;

    if (((ic_con_tmp & I2C_BIT_MST_MOD) == 0) &&
        ((ic_con_tmp & (I2C_BIT_SLV_DIS | I2C_BIT_SLV_DIS_1)) != (I2C_BIT_SLV_DIS | I2C_BIT_SLV_DIS_1))) {
        /* 0 for slave mode */
        return 0;
    } else if (((ic_con_tmp & I2C_BIT_MST_MOD) == 1) &&
               ((ic_con_tmp & (I2C_BIT_SLV_DIS | I2C_BIT_SLV_DIS_1)) == (I2C_BIT_SLV_DIS | I2C_BIT_SLV_DIS_1))) {
        /* 1 for master mode */
        return 1;
    } else {
        /* 2 for error config */
        return 2;
    }
}

/** \brief Description of hal_rtl_i2c_pure_init_simple
 *
 *    hal_rtl_i2c_pure_init_simple is used to initialize I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t :      i2c enable status
 */
uint8_t hal_rtl_i2c_pure_init_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    uint8_t  restart;
    uint32_t ic_value_tmp;
    i2c_init_dat_t *pi2c_init_data = (i2c_init_dat_t *)&(phal_i2c_adapter->init_dat);
    I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
    uint32_t ic_con_tmp;
    uint32_t ic_tar_tmp;
    uint32_t ic_filter_tmp;

    isp_info("hal_rtl_i2c_pure_init_simple\n\r");

    restart = 0;

    /* Disable the IC first */
    hal_rtl_i2c_en_ctrl_simple(phal_i2c_adapter, I2CDisable);

    /* Master case*/
    if (pi2c_init_data->master) {
        /*RESTART MUST be set in these condition in Master mode.
               But it might be NOT compatible in old slaves.*/
        if ((pi2c_init_data->addr_mod == I2CAddress10bit) || (pi2c_init_data->spd_mod == I2CHighSpeed)) {
            restart = 1;
        }

        ic_con_tmp = 0;
        HAL_SET_BIT(ic_con_tmp, I2C_BIT_SLV_DIS|I2C_BIT_SLV_DIS_1
                                            |(restart<<I2C_SHIFT_RSTRT_EN)
                                            |(pi2c_init_data->addr_mod<<I2C_SHIFT_MST_10BIT_ADDR)
                                            |(pi2c_init_data->spd_mod<<I2C_SHIFT_SPD)
                                            |(pi2c_init_data->master<<I2C_SHIFT_MST_MOD));
        pi2c_reg->I2C_CON = ic_con_tmp;
        isp_info("Init master, con[%2x]: %x, %x\n\r", &(pi2c_reg->I2C_CON), pi2c_reg->I2C_CON, ic_con_tmp);
        /* To set target addr.*/
        ic_tar_tmp = 0;
        HAL_SET_BIT(ic_tar_tmp, (pi2c_init_data->addr_mod<<I2C_SHIFT_TAR_10BIT_ADDR)
                                            |(pi2c_init_data->ack_addr0<<I2C_SHIFT_TAR));
        pi2c_reg->I2C_TAR = ic_tar_tmp;
        isp_info("Init master, tar[%2x]: %x, %x\n\r", &(pi2c_reg->I2C_TAR), pi2c_reg->I2C_TAR, ic_tar_tmp);

        /* To Set I2C clock*/
        hal_rtl_i2c_set_clk_simple(phal_i2c_adapter);

        /* Set master code */
        pi2c_reg->I2C_HS_MADDR = pi2c_init_data->hs_maddr;
        isp_info("Init master, hs_maddr[%2x]: %x, %x\n\r", &(pi2c_reg->I2C_HS_MADDR), pi2c_reg->I2C_HS_MADDR, pi2c_init_data->hs_maddr);
    }else {
        ic_con_tmp = 0;
        HAL_SET_BIT(ic_con_tmp, (pi2c_init_data->master<<I2C_SHIFT_SLV_DIS)
                                            |(pi2c_init_data->master<<I2C_SHIFT_SLV_DIS_1)
                                            |(pi2c_init_data->addr_mod<<I2C_SHIFT_SLV_10BIT_ADDR)
                                            |(pi2c_init_data->spd_mod<<I2C_SHIFT_SPD)
                                            |(pi2c_init_data->master<<I2C_SHIFT_MST_MOD));
        pi2c_reg->I2C_CON = ic_con_tmp;
        isp_info("Init slave, con%d[%2x]: %x\n\r", pi2c_init_data->index, &pi2c_reg->I2C_CON, pi2c_reg->I2C_CON);

        /* To set slave addr. 0 */
        pi2c_reg->I2C_SAR = pi2c_init_data->ack_addr0;
        isp_info("Init slave, sar%d[%2x]: %x\n\r", pi2c_init_data->index, &pi2c_reg->I2C_SAR, pi2c_reg->I2C_SAR);

        /* To set slave addr. 1 */
        pi2c_reg->I2C_SAR1 = pi2c_init_data->ack_addr1;
        isp_info("Init slave, sar1%d[%2x]: %x\n\r", pi2c_init_data->index, &pi2c_reg->I2C_SAR1, pi2c_reg->I2C_SAR1);

        /* To Set I2C clock*/
        hal_rtl_i2c_set_clk_simple(phal_i2c_adapter);


    }

    /* to set SDA hold time */
    ic_con_tmp = pi2c_reg->I2C_CON;
    if (((ic_con_tmp & I2C_MASK_SPD)>>I2C_SHIFT_SPD) == I2CStandardSpeed) {
        ic_value_tmp = pi2c_reg->I2C_SS_SCL_LCNT;
    } else if (((ic_con_tmp & I2C_MASK_SPD)>>I2C_SHIFT_SPD) == I2CFastSpeed) {
        ic_value_tmp = pi2c_reg->I2C_FS_SCL_LCNT;
    } else {
        ic_value_tmp = pi2c_reg->I2C_HS_SCL_LCNT;
    }

    if (pi2c_init_data->master) {
        if (pi2c_init_data->sda_hold > (ic_value_tmp-2)) {
            ic_value_tmp = (ic_value_tmp-2);
            if (ic_value_tmp < I2C_MST_SDA_HOLD_MIN) {
                ic_value_tmp = I2C_MST_SDA_HOLD_MIN;
            }
            pi2c_reg->I2C_SDA_HOLD = ic_value_tmp;
        } else {
            pi2c_reg->I2C_SDA_HOLD = pi2c_init_data->sda_hold;
        }
    } else {
        if (pi2c_init_data->sda_hold > (ic_value_tmp-2)) {
            ic_value_tmp = (ic_value_tmp-2);
            if (ic_value_tmp < I2C_SLV_SDA_HOLD_MIN) {
                ic_value_tmp = I2C_SLV_SDA_HOLD_MIN;
            }
            pi2c_reg->I2C_SDA_HOLD = ic_value_tmp;
        } else {
            pi2c_reg->I2C_SDA_HOLD = pi2c_init_data->sda_hold;
        }

        /* to set SDA setup time, only for slave-transmitter */
        pi2c_reg->I2C_SDA_SETUP = (ic_value_tmp>>1);
    }

    isp_info("sda_setup: %x\n\r", pi2c_reg->I2C_SDA_SETUP);
    isp_info("sda_hold: %x\n\r", pi2c_reg->I2C_SDA_HOLD);
    //DBG_8195BL("sda_setup: %x\n\r", pi2c_reg->sda_setup);
    //DBG_8195BL("sda_hold: %x\n\r", pi2c_reg->sda_hold);
    /* To set default digital filter */
    ic_filter_tmp = 0;
    HAL_SET_BIT(ic_filter_tmp, (pi2c_init_data->dig_fltr_en<<I2C_SHIFT_DIG_FLTR_EN)
                                    |(pi2c_init_data->dig_fltr_lvl<<I2C_SHIFT_DIG_FLTR_DEG));
    pi2c_reg->I2C_FLTR  = ic_filter_tmp;

    /* To set TX_Empty Level */
    pi2c_reg->I2C_TX_TL = pi2c_init_data->ff_txtl;

    /* To set RX_Full Level */
    pi2c_reg->I2C_RX_TL = pi2c_init_data->ff_rxtl;

    isp_info("pi2c_reg->tx_tl[%x]: %x\n\r", &pi2c_reg->I2C_TX_TL, pi2c_reg->I2C_TX_TL);
    isp_info("pi2c_reg->rx_tl[%x]: %x\n\r", &pi2c_reg->I2C_RX_TL, pi2c_reg->I2C_RX_TL);
    /* To set DMA default TX/RX FIFO level */
    pi2c_reg->I2C_DMA_TDLR = 0x09;
    pi2c_reg->I2C_DMA_RDLR = 0x03;
    isp_info("Init i2c dev, dma_tdlr%d[%2x]: %x\n\r", pi2c_init_data->index, &pi2c_reg->I2C_DMA_TDLR, pi2c_reg->I2C_DMA_TDLR);
    isp_info("Init i2c dev, dma_rdlr%d[%2x]: %x\n\r", pi2c_init_data->index, &pi2c_reg->I2C_DMA_RDLR, pi2c_reg->I2C_DMA_RDLR);

    /*I2C Clear all interrupts first*/
    READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_INTR);

    /* Enable the IC first and return the enable status */
    return hal_rtl_i2c_en_ctrl_simple(phal_i2c_adapter, I2CEnable);
}

/** \brief Description of hal_rtl_i2c_pure_deinit_simple
 *
 *    hal_rtl_i2c_pure_deinit_simple is used to deinit I2C module.
 *    It's directly to disable I2C module.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t
 */
uint8_t hal_rtl_i2c_pure_deinit_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    return hal_rtl_i2c_en_ctrl_simple(phal_i2c_adapter, I2CDisable);
}

/** \brief Description of hal_rtl_i2c_wr_simple
 *
 *    hal_rtl_i2c_wr_simple is used to send I2C data. In master mode, this function could send write command, too.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] const uint8_t *dat_buf:     Data buffer address for I2C write.
 *   \param[in] uint32_t dat_len:           Data length for I2C write.
 *   \param[in] uint8_t ctrl:           To control what I2C would do when data is all sent. (Only for Master Mode)\n\r
 *                                      In slave mode, this part should be always 0.\n\r
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n\r
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n\r
 *                                      1: Send STOP after the last data.\n\r
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n\r
 *                                      the next transmision would have a START/RESTART condition sent first.\n\r
 *                                      So setting 2 to this field could influence the following transmission.\n\r
 *   \return hal_status_t:      When the given Ctrl is NOT fit with hardware setting, a value of HAL_STS_ERR_HW\n\r
 *                              will be returned. Otherwise, a value of HAL_STS_OK will be returned.
 */
hal_status_t hal_rtl_i2c_wr_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, const uint8_t *dat_buf, uint32_t dat_len, uint8_t ctrl)
{
    I2C_TypeDef *pi2c_reg = phal_i2c_adapter->init_dat.reg_base;
    uint32_t dat_cnt  = 0;
    uint32_t ic_dat_cmd;

    /* Check RESTART configuration is enabled or not */
    //if ((ctrl == 2) && (BIT_GET_IC_RESTART_EN(pi2c_reg->con) == 0)) {
    if ((ctrl == 2) && ((pi2c_reg->I2C_CON & I2C_BIT_RSTRT_EN) == 0)) {
        return HAL_ERR_HW;
    }

    for (dat_cnt = 0; dat_cnt < dat_len; dat_cnt++) {
        ic_dat_cmd = 0;
        if ((dat_cnt == (dat_len -1)) &&  (ctrl != 0)){
            ic_dat_cmd |= (0x01 << (I2C_SHIFT_STP+ctrl-1));
        }
        HAL_SET_BIT(ic_dat_cmd, (((uint8_t)(*(dat_buf+dat_cnt)))<<I2C_SHIFT_DAT));
        HAL_CLEAR_BIT(ic_dat_cmd, I2C_BIT_CMD); /* i2c write */
        isp_info("dat_cnt = %x, dc: %x, ctrl: %x\n\r", dat_cnt, ic_dat_cmd, ctrl);
        pi2c_reg->I2C_DAT_CMD = ic_dat_cmd;
    }

    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_mst_send_rdcmd_simple
 *
 *    hal_rtl_i2c_mst_send_rdcmd_simple is used to send I2C master read command.
 *    It should only be used for master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint32_t cmd_len:           Read commnad length for I2C read.
 *   \param[in] uint8_t ctrl:               To control what I2C would do when data is all sent. (Only for Master Mode)\n\r
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n\r
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n\r
 *                                      1: Send STOP after the last data.\n\r
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n\r
 *                                      the next transmision would have a START/RESTART condition sent first.\n\r
 *                                      So setting 2 to this field could influence the following transmission.
 *
 *  \return void
 */
void hal_rtl_i2c_mst_send_rdcmd_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint32_t cmd_len, uint8_t ctrl)
{
    uint32_t cmd_cnt = 0;
    uint32_t ic_dat_cmd;

    for (cmd_cnt = 0; cmd_cnt < cmd_len; cmd_cnt++) {
        ic_dat_cmd = 0;

        if ((cmd_cnt == (cmd_len -1)) &&  (ctrl != 0)){
            ic_dat_cmd |= (0x01 << (I2C_SHIFT_STP+ctrl-1));
        }

        HAL_SET_BIT(ic_dat_cmd, I2C_BIT_CMD);   /* i2c read */
        phal_i2c_adapter->init_dat.reg_base->I2C_DAT_CMD = ic_dat_cmd;
    }
}


/** \brief Description of hal_rtl_i2c_dma_ctrl_simple
 *
 *    hal_rtl_i2c_dma_ctrl_simple is used to enable/disable I2C DMA function.\n\r
 *    Enable is used to control that this function performs enable or disable operaiton.\n\r
 *    And it would set/clear related register according to the given DMAEnMsk.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable:             To enable/disable I2C DMA function.\n\r
 *                                      0: Disable.\n\r
 *                                      1: Enable.
 *   \return uint32_t:         I2C DMA enable status.
 */
uint32_t hal_rtl_i2c_dma_ctrl_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
    I2C_TypeDef *pi2c_reg = phal_i2c_adapter->init_dat.reg_base;
    uint32_t ic_dma_cmd_tmp;

    if (enable == I2CForceDisable) {
        /* To disable I2C DMA */
        ic_dma_cmd_tmp = pi2c_reg->I2C_DMA_CMD;
        ic_dma_cmd_tmp &= (uint32_t)(~(I2C_BIT_DMA_EN));

        pi2c_reg->I2C_DMA_CMD = ic_dma_cmd_tmp;
    } else {
        while (pi2c_reg->I2C_DMA_CMD & I2C_BIT_DMA_EN){
        }

        while (pi2c_reg->I2C_RAW_INTR_STAT & I2C_BIT_RAW_DMA_I2C_DONE){
        }

        /* To disable I2C DMA */
        ic_dma_cmd_tmp = pi2c_reg->I2C_DMA_CMD;
        ic_dma_cmd_tmp &= (uint32_t)(~(I2C_BIT_DMA_EN));
        if (enable) {
            ic_dma_cmd_tmp |= (I2C_BIT_DMA_EN);
        }

        pi2c_reg->I2C_DMA_CMD = ic_dma_cmd_tmp;
    }

    isp_info("dam_cmd: %x\n\r", pi2c_reg->I2C_DMA_CMD);
    return (uint32_t)(pi2c_reg->I2C_DMA_CMD);
}

/** \brief Description of hal_rtl_i2c_mst_restr_ctrl_simple
 *
 *    hal_rtl_i2c_mst_restr_ctrl_simple is used to enable/disable RESTART feature.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t restr_en:               To enable/disable I2C RESTART fearture. Software should enable\n\r
 *                                              this feature before it sets RESTART command in REG_IC_DATA_CMD\n\r
 *                                              register.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_mst_restr_ctrl_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint8_t restr_en)
{
    I2C_TypeDef *pi2c_reg = phal_i2c_adapter->init_dat.reg_base;
    uint32_t ic_en_sts_bak;
    uint32_t    ic_con_tmp;

    /* Check if I2C is in master mode. */
    if (hal_rtl_i2c_chk_mod_simple(phal_i2c_adapter) != 1) {
        return HAL_ERR_PARA;
    }

    /* Disable i2c first */
    ic_en_sts_bak = pi2c_reg->I2C_EN_STS;
    if (ic_en_sts_bak & I2C_BIT_EN_STS) {
        if (hal_rtl_i2c_en_ctrl_simple(phal_i2c_adapter, I2CDisable)) {
            return HAL_ERR_HW;
        }
    }

    if (((phal_i2c_adapter->init_dat.addr_mod == I2CAddress10bit) || (phal_i2c_adapter->init_dat.spd_mod == I2CHighSpeed))
        && (restr_en == I2CDisable)) {
        isp_error("RESTART enable could not be disabled in 10bit or high speed mode\n\r");
        return HAL_ERR_PARA;
    }

    ic_con_tmp = pi2c_reg->I2C_CON;
    HAL_CLEAR_BIT(ic_con_tmp, I2C_BIT_RSTRT_EN);
    HAL_SET_BIT(ic_con_tmp, restr_en << I2C_SHIFT_RSTRT_EN);
    pi2c_reg->I2C_CON = ic_con_tmp;

    if (ic_en_sts_bak & I2C_BIT_EN_STS) {
        hal_rtl_i2c_en_ctrl_simple(phal_i2c_adapter, I2CEnable);
    }

    return HAL_OK;
}


/** \brief Description of hal_rtl_i2c_pin_init_simple
 *
 *    hal_rtl_i2c_pin_init_simple is used to initialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_pin_init_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{

    return HAL_OK;

}

/** \brief Description of hal_rtl_i2c_pin_deinit_simple
 *
 *    hal_rtl_i2c_pin_deinit_simple is used to deinitialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_pin_deinit_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_init_simple
 *
 *    hal_rtl_i2c_init_simple is used to initialize i2c including platform related features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_init_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    hal_rtl_i2c_pure_init_simple(phal_i2c_adapter);

    if (phal_i2c_adapter->init_dat.reg_base->I2C_EN_STS & I2C_BIT_EN_STS) {
        phal_i2c_adapter->status   = I2CStatusInitialized;
        phal_i2c_adapter->init_dat.enable  = I2CEnable;
        phal_i2c_adapter->status   = I2CStatusIdle;
        return HAL_OK;
    } else {
        phal_i2c_adapter->status   = I2CStatusUninitial;
        phal_i2c_adapter->init_dat.enable  = I2CDisable;
        return HAL_ERR_HW;
    }

}

/** \brief Description of hal_rtl_i2c_deinit_simple
 *
 *    hal_rtl_i2c_deinit_simple is used to deinitialize i2c including platform related features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_deinit_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    phal_i2c_adapter->init_dat.enable  = hal_rtl_i2c_pure_deinit_simple(phal_i2c_adapter);

    if (phal_i2c_adapter->init_dat.reg_base->I2C_EN_STS & I2C_BIT_EN_STS) {
        return HAL_ERR_HW;
    } else {
        phal_i2c_adapter->status     = I2CStatusUninitial;
        return HAL_OK;
    }
}

/** \brief Description of hal_rtl_i2c_load_default_simple
 *
 *    hal_rtl_i2c_load_default_simple is used to load default setting for i2c module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t index:   i2c device index.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_load_default_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint8_t index)
{
    i2c_init_dat_t  *pi2c_init_dat      = (i2c_init_dat_t  *)&(phal_i2c_adapter->init_dat);
    i2c_platform_data_t *pi2c_plft_dat  = (i2c_platform_data_t *)&(phal_i2c_adapter->pltf_dat);
    i2c_user_callback_t *pi2c_usr_cb    = (i2c_user_callback_t *)&(phal_i2c_adapter->usr_cb);

    /* Check the input I2C index first */
    if (hal_rtl_i2c_idx_chk(index)) {
        return HAL_ERR_UNKNOWN;
    }

    phal_i2c_adapter->init_dat.index = index;

    /* I2C Initial Default Configuration */
    pi2c_init_dat->enable       = I2CDisable;
    pi2c_init_dat->master       = I2CMasterMode;
    pi2c_init_dat->addr_mod     = I2CAddress7bit;
    pi2c_init_dat->spd_mod      = I2CStandardSpeed;
    pi2c_init_dat->sda_setup    = 2;
    pi2c_init_dat->ff_rxtl      = 0x00;
    pi2c_init_dat->ff_txtl      = 0x00;
    pi2c_init_dat->clock        = 100;              // 100 kHz
    pi2c_init_dat->ack_addr0    = 0x11;
    pi2c_init_dat->ack_addr1    = 0x11;
    pi2c_init_dat->sda_hold     = 4;
    pi2c_init_dat->bus_ld       = 100;
    pi2c_init_dat->dig_fltr_en  = I2CEnable;
    pi2c_init_dat->dig_fltr_lvl = 2;

    pi2c_plft_dat->tr_time_out  = 0xFFFFFFFF;

    /* I2C Interrupt Handle Configuration */
    switch (phal_i2c_adapter->init_dat.index) {
        case 0:
            pi2c_init_dat->reg_base     = (void *)I2C0_BASE;
            break;
        case 1:
            pi2c_init_dat->reg_base     = (void *)I2C1_BASE;
            break;
        case 2:
            pi2c_init_dat->reg_base     = (void *)I2C2_BASE;
            break;
        case 3:
            pi2c_init_dat->reg_base     = (void *)I2C3_BASE;
            break;

        default:
            return HAL_ERR_UNKNOWN;
    }

    phal_i2c_adapter->status   = I2CStatusUninitial;
    phal_i2c_adapter->op_mode  = I2CModePoll;
    //phal_i2c_adapter->mst_spe_func |= I2CAddressRetry;
    phal_i2c_adapter->err_type = I2CErrorNone;
    phal_i2c_adapter->rd_cmd_no= 0;

    /* Clear USER Callback Function Pointer */
    memset(pi2c_usr_cb, 0x00, sizeof(i2c_user_callback_t));

    /* Clear TRX information */
    memset((hal_i2c_adapter_t *)&(phal_i2c_adapter->tx_dat), 0x00, sizeof(i2c_tx_info_t));
    memset((hal_i2c_adapter_t *)&(phal_i2c_adapter->rx_dat), 0x00, sizeof(i2c_rx_info_t));

    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_set_tar_simple
 *
 *    hal_rtl_i2c_set_tar_simple is to set target slave address in master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t mst_rw:   This target address is for read or write usage.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_set_tar_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter, uint8_t mst_rw)
{
    uint32_t start_time = 0;
    I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)(phal_i2c_adapter->init_dat.reg_base);
    uint32_t ic_tar_tmp;

    /* check if it's necessary to update TAR */
    ic_tar_tmp  = pi2c_reg->I2C_TAR;
    if (mst_rw == 0) {
        if (((ic_tar_tmp & I2C_MASK_TAR) >> I2C_SHIFT_TAR) != phal_i2c_adapter->tx_dat.addr) {
            HAL_CLEAR_BIT(ic_tar_tmp, I2C_MASK_TAR);
            HAL_SET_BIT(ic_tar_tmp, phal_i2c_adapter->tx_dat.addr << I2C_SHIFT_TAR);
        } else {
            return HAL_OK;
        }
    } else {
        if ((ic_tar_tmp & I2C_MASK_TAR) >> I2C_SHIFT_TAR != phal_i2c_adapter->rx_dat.addr) {
            HAL_CLEAR_BIT(ic_tar_tmp, I2C_MASK_TAR);
            HAL_SET_BIT(ic_tar_tmp, phal_i2c_adapter->rx_dat.addr << I2C_SHIFT_TAR);
        } else {
            return HAL_OK;
        }
    }

    /* Check TX FIFO status, wait for all tx is done. */
    start_time = hal_read_curtime_us();
    //while (!BIT_GET_IC_TFE(pi2c_reg->status)) {
    while((pi2c_reg->I2C_STS & I2C_BIT_STS_TFE) == 0){
        if (hal_rtl_i2c_timeout_chk_simple(phal_i2c_adapter, start_time) == 1) {
            phal_i2c_adapter->status   = I2CStatusTimeOut;
            phal_i2c_adapter->err_type = I2CErrorTarTimeOut;
            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_TIMEOUT;
        }
    }

    /* Check Master activity status, wait until it's ready */
    start_time  = hal_read_curtime_us();
    //while (BIT_GET_MST_ACTIVITY(pi2c_reg->status)) {
    while(pi2c_reg->I2C_STS & I2C_BIT_STS_MST_ACT){
        if (hal_rtl_i2c_timeout_chk_simple(phal_i2c_adapter, start_time) == 1) {
            phal_i2c_adapter->status   = I2CStatusTimeOut;
            phal_i2c_adapter->err_type = I2CErrorTarTimeOut;
            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_TIMEOUT;
        }
    }

    pi2c_reg->I2C_TAR = ic_tar_tmp;
    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_send_poll_simple
 *
 *    hal_rtl_i2c_send_poll_simple is to send i2c data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_send_poll_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    i2c_tx_info_t   *pi2c_tx_info = (i2c_tx_info_t *)&(phal_i2c_adapter->tx_dat);
    I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
    uint32_t start_time  = 0;
    uint32_t ic_raw_state_tmp;
    uint8_t  wr_ctrl = 0;

    start_time = hal_read_curtime_us();

    for (;;) {
        if (pi2c_tx_info->len == 0) {
            break;
        }

        phal_i2c_adapter->status = I2CStatusTxing;
        ic_raw_state_tmp = pi2c_reg->I2C_RAW_INTR_STAT;
        //if (ic_raw_state_tmp.d32 & (BIT_RAW_TX_OVER | BIT_RAW_TX_ABRT)) {
        if ((ic_raw_state_tmp & I2C_BIT_RAW_TX_OVER) || (ic_raw_state_tmp & I2C_BIT_RAW_TX_ABRT)) {
            phal_i2c_adapter->status = I2CStatusError;
            if (ic_raw_state_tmp & I2C_BIT_RAW_TX_OVER) {
                phal_i2c_adapter->err_type = I2CErrorTxOver;
            } else {
                phal_i2c_adapter->err_type = I2CErrorTxAbort;
            }

            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_ERR_HW;
        //} else if (BIT_GET_IC_TFNF(pi2c_reg->status)) {
        } else if (pi2c_reg->I2C_STS & I2C_BIT_STS_TFNF) {
            /* Wrtie data into I2C TX FIFO */
            wr_ctrl = 0;
            if (pi2c_tx_info->len == 1) {
                if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
                    wr_ctrl = 2;    /* Set RESTART for the next byte */
                } else {
                    if (pi2c_tx_info->mst_stop == 1) {
                        wr_ctrl = 1;    /* Set STOP for the last byte */
                    }
                }
            }
            hal_rtl_i2c_wr_simple(phal_i2c_adapter, pi2c_tx_info->buf, 1, wr_ctrl);
            pi2c_tx_info->buf++;
			if (pi2c_tx_info->len > 10) {
				printf("i2c err len: %x\n\r", pi2c_tx_info->len);
				phal_i2c_adapter->status   = I2CStatusError;
                phal_i2c_adapter->err_type = I2CErrorTxAbort;
                if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                    phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
                }
				return HAL_ERR_PARA;
			}
				
            pi2c_tx_info->len--;
            start_time = hal_read_curtime_us();
            
        } else {
            if (hal_rtl_i2c_timeout_chk_simple(phal_i2c_adapter, start_time) == 1) {
                phal_i2c_adapter->status   = I2CStatusTimeOut;
                phal_i2c_adapter->err_type = I2CErrorTxCmdTimeOut;
                if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                    phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
                }

                return HAL_TIMEOUT;
            }
        }
    }

    start_time = hal_read_curtime_us();
    while(!(pi2c_reg->I2C_STS & I2C_BIT_STS_TFE)) {
        if (hal_rtl_i2c_timeout_chk_simple(phal_i2c_adapter, start_time) == 1) {
            phal_i2c_adapter->status   = I2CStatusTimeOut;
            phal_i2c_adapter->err_type = I2CErrorTxCmdTimeOut;
            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_TIMEOUT;
        }
		ic_raw_state_tmp = pi2c_reg->I2C_RAW_INTR_STAT;
        if ((ic_raw_state_tmp & I2C_BIT_RAW_TX_OVER) || (ic_raw_state_tmp & I2C_BIT_RAW_TX_ABRT)) {
            phal_i2c_adapter->status = I2CStatusError;
            if (ic_raw_state_tmp & I2C_BIT_RAW_TX_OVER) {
                phal_i2c_adapter->err_type = I2CErrorTxOver;
            } else {
                phal_i2c_adapter->err_type = I2CErrorTxAbort;
            }

            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_ERR_HW;
        }
    }
    
    phal_i2c_adapter->status = I2CStatusIdle;
    if (phal_i2c_adapter->usr_cb.txc.cb != NULL) {
        phal_i2c_adapter->usr_cb.txc.cb((void *)phal_i2c_adapter->usr_cb.txc.dat);
    }

    return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_recv_poll_simple
 *
 *    hal_rtl_i2c_recv_poll_simple is to receive I2C data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_rtl_i2c_recv_poll_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    i2c_rx_info_t   *pi2c_rx_info = (i2c_rx_info_t *)&(phal_i2c_adapter->rx_dat);
    I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
    uint32_t ic_sts_tmp;
    uint32_t ic_raw_state_tmp;
    uint32_t start_time  = 0;
    uint8_t  wr_ctrl     = 0;

    if (!(phal_i2c_adapter->mst_spe_func & I2CAddressRetry)) {
        phal_i2c_adapter->rd_cmd_no = pi2c_rx_info->len;
        READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_TX_ABRT);
        READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_ACT);
        READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_INTR);
    }

    start_time = hal_read_curtime_us();
    for (;;) {
        if (pi2c_rx_info->len == 0) {
            break;
        }

        phal_i2c_adapter->status = I2CStatusRxing;
        ic_raw_state_tmp = pi2c_reg->I2C_RAW_INTR_STAT;
        if (((ic_raw_state_tmp) & (I2C_BIT_RAW_RX_UNDER | I2C_BIT_RAW_RX_OVER | I2C_BIT_RAW_TX_OVER | I2C_BIT_RAW_TX_ABRT)) != 0) {
            phal_i2c_adapter->status = I2CStatusError;
            if ((ic_raw_state_tmp & I2C_BIT_RAW_RX_UNDER) != 0) {
                phal_i2c_adapter->err_type= I2CErrorRxUnder;
            } else if ((ic_raw_state_tmp & I2C_BIT_RAW_RX_OVER) != 0) {
                phal_i2c_adapter->err_type= I2CErrorRxOver;
            } else if ((ic_raw_state_tmp & I2C_BIT_RAW_TX_OVER) != 0) {
                phal_i2c_adapter->err_type= I2CErrorTxOver;
            } else if ((ic_raw_state_tmp & I2C_BIT_RAW_TX_ABRT) != 0) {
                phal_i2c_adapter->err_type= I2CErrorTxAbort;
            } else {
                phal_i2c_adapter->err_type= ic_raw_state_tmp;
            }

            if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
            }

            return HAL_ERR_HW;
//        } else if (BIT_GET_IC_TFNF(pi2c_reg->status)) {
        } else if (pi2c_reg->I2C_STS & I2C_BIT_STS_TFE) {
            if (phal_i2c_adapter->rd_cmd_no > 0) {
                /* Wrtie cmd into I2C TX FIFO */
                wr_ctrl = 0;
                if (phal_i2c_adapter->rd_cmd_no == 1) {
                    if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
                        wr_ctrl = 2;    /* Set RESTART for the next byte */
                    } else {
                        if (pi2c_rx_info->mst_stop == 1) {
                            wr_ctrl = 1;    /* Set STOP for the last byte */
                        }
                    }
                }
                isp_info("rx wr_ctrl:%x: %x\n\r", wr_ctrl, (pi2c_reg->I2C_STS & I2C_BIT_STS_TFE));
                hal_rtl_i2c_mst_send_rdcmd_simple(phal_i2c_adapter, 1, wr_ctrl);
                phal_i2c_adapter->rd_cmd_no--;
                start_time = hal_read_curtime_us();
            }
        } else {
            if (hal_rtl_i2c_timeout_chk_simple(phal_i2c_adapter, start_time) == 1) {
                phal_i2c_adapter->status = I2CStatusTimeOut;
                phal_i2c_adapter->err_type= I2CErrorRxCmdTimeOut;
                if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
                    phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
                }

                return HAL_TIMEOUT;
            }
        }

        ic_sts_tmp = pi2c_reg->I2C_STS;
        if (((ic_sts_tmp & I2C_BIT_STS_RFNE) != 0) || ((ic_sts_tmp & I2C_BIT_STS_RFF) != 0)) {
            *(pi2c_rx_info->buf) = pi2c_reg->I2C_DAT_CMD;
            pi2c_rx_info->buf++;
            pi2c_rx_info->len--;
        }
    }

    if (phal_i2c_adapter->usr_cb.rxc.cb != NULL) {
        phal_i2c_adapter->usr_cb.rxc.cb((void *)phal_i2c_adapter->usr_cb.rxc.dat);
    }

    phal_i2c_adapter->status = I2CStatusIdle;
    return HAL_OK;
}



/** \brief Description of hal_i2c_send
 *
 *    hal_i2c_send is an upper layer I2C send transfer API. It executes the related send(TX) API according \n\r
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    i2c_tx_info_t   *pi2c_tx_info = (i2c_tx_info_t *)&(phal_i2c_adapter->tx_dat);
    hal_status_t retv = HAL_OK;

    if (phal_i2c_adapter->op_mode <= I2CModeDMA) {
        hal_rtl_i2c_set_tar_simple(phal_i2c_adapter, I2CWrite);

        if (pi2c_tx_info->len == 0) {
            phal_i2c_adapter->status = I2CStatusIdle;
            if (phal_i2c_adapter->usr_cb.txc.cb != NULL) {
                phal_i2c_adapter->usr_cb.txc.cb((void *)phal_i2c_adapter->usr_cb.txc.dat);
            }
            return (hal_status_t)retv;
        }

        retv = hal_rtl_i2c_send_poll_simple(phal_i2c_adapter);

    }  else {
        retv = HAL_ERR_UNKNOWN;
    }

    return (hal_status_t)retv;
}

/** \brief Description of hal_i2c_receive
 *
 *    hal_i2c_receive is an upper layer I2C receive transfer API. It executes the related receive(RX) API according
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_receive_simple (volatile hal_i2c_adapter_t *phal_i2c_adapter)
{
    i2c_rx_info_t   *pi2c_rx_info = (i2c_rx_info_t *)&(phal_i2c_adapter->rx_dat);
    hal_status_t retv = HAL_OK;

    if (phal_i2c_adapter->op_mode <= I2CModeDMA) {
        hal_rtl_i2c_set_tar_simple(phal_i2c_adapter, 1);

        if (pi2c_rx_info->len == 0) {
            phal_i2c_adapter->status = I2CStatusIdle;
            if (phal_i2c_adapter->usr_cb.rxc.cb != NULL) {
                phal_i2c_adapter->usr_cb.rxc.cb((void *)phal_i2c_adapter->usr_cb.rxc.dat);
            }
            return (hal_status_t)retv;
        }

        retv = hal_rtl_i2c_recv_poll_simple(phal_i2c_adapter);

    } else {
        retv = HAL_ERR_UNKNOWN;
    }

    return (hal_status_t)retv;
}

#endif

/** @} */ /* End of group hs_hal_i2c_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** @} */ /* End of group hs_hal_i2c */

