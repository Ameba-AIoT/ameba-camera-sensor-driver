#ifndef __RT_CONFIG_DRV_H__
#define __RT_CONFIG_DRV_H__

// ----------------------------------------------------------------------------
//  ISP
// ----------------------------------------------------------------------------
#define CFG_ISP_CMD_DATA_W_NUM	16
#define CFG_ISP_CMD_DATA_R_NUM	48

// ----------------------------------------------------------------------------
//  crypto
// ----------------------------------------------------------------------------
#define CFG_CRYPTO_KEY_LEN		32

// ----------------------------------------------------------------------------
//  fwd
// ----------------------------------------------------------------------------
#define CFG_FWD_ITEMS			4

// ----------------------------------------------------------------------------
//  MTD
// ----------------------------------------------------------------------------
//#define CFG_MTD0_SIZE			(SZ_4M)
#define CFG_MTD0_NAME			"global"

#define CFG_MTD1_SIZE			SZ_384K
#define CFG_MTD1_NAME			"boot"

#define CFG_MTD2_SIZE			SZ_256K
#define CFG_MTD2_NAME			"hconf"

#define CFG_MTD3_SIZE			(3*SZ_1M)
#define CFG_MTD3_NAME			"kernel"

#define CFG_MTD4_SIZE			SZ_384K
#define CFG_MTD4_NAME			"free"


#define CFG_HCONF_MTD_IDX		2
// NOTE:
//  please sync with the above definitions.
//
#define CFG_KERNEL_MTD_IDX		3
#define CFG_KERNEL_MTD_OFS		0
#define CFG_KERNEL_MTD_SIZE		CFG_MTD3_SIZE

#define CFG_FREE_MTD_IDX		4
#define CFG_FREE_MTD_OFS		0
#define CFG_FREE_MTD_SIZE		CFG_MTD4_SIZE

// ----------------------------------------------------------------------------
// very important!!! keep this value = MMC_MAX_BLOCK_LEN in mmc.h
#define CFG_DRV_MMC_BLOCK_SIZE	512


#endif	// __RT_CONFIG_DRV_H__
