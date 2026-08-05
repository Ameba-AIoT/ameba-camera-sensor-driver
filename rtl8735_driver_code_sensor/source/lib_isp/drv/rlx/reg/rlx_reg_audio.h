#ifndef RLX_REG_AUDIO_H
#define RLX_REG_AUDIO_H

#define AUDIO_FIFO_BASE		0xB8500000UL
#define AUDIO_CONF_BASE		0xB8500070UL

typedef struct
{
	uint32_t RX_FIFO_THRESHOLD;
	uint32_t TX_FIFO_THRESHOLD;
	uint32_t RX_SA;
	uint32_t RX_LEN;
	uint32_t RX_RP;
	uint32_t RX_WP;
	uint32_t TX_SA;
	uint32_t TX_LEN;
	uint32_t TX_RP;
	uint32_t TX_WP;
	uint32_t FIFO_ENABLE;
	uint32_t FIFO_CTL;
	uint32_t AUDIO_CTL;
	uint32_t RX_BUFFER_THRESHOLD;
	uint32_t RX_TIMER_COUNT;
	uint32_t RX_TIMER_THRESHOLD;
	uint32_t TX_BUFFER_THRESHOLD;
	uint32_t TX_TIMER_COUNT;
	uint32_t TX_TIMER_THRESHOLD;
	uint32_t AUDIO_INT_EN;
	uint32_t AUDIO_INT_STS;
	uint32_t RX_FIFO_STATUS;
	uint32_t TX_FIFO_STATUS;
	uint32_t FIFO_ACCESS_ADDR;
	uint32_t FIFO_ACCESS_DATA;
} rlx_reg_audio_fifo_st;

typedef struct
{
	uint32_t DAC_CFG;
	uint32_t DAC_PDM_DFG;
	uint32_t ADC_CFG1;
	uint32_t ADC_CFG2;
	uint32_t AGC_CFG1;
	uint32_t AGC_CFG2;
	uint32_t AGC_CFG3;
	uint32_t AGC_CFG4;
	uint32_t AGC_CFG5;
	uint32_t AGC_CFG6;
	uint32_t TCON_CFG;
	// 0x9C
	uint32_t ADDA_ANA_CFG1;
	uint32_t ADDA_ANA_CFG2;
	uint32_t ADDA_ANA_CFG3;
	uint32_t ADDA_ANA_CFG4;
	uint32_t ADDA_ANA_CFG5;
} rlx_reg_audio_conf_st;

#endif	// RLX_REG_AUDIO_H
