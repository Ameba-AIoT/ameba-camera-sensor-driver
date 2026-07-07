#ifndef __SECTION_CONFIG_VOE_H__
#define __SECTION_CONFIG_VOE_H__


#define SECTION_VECTOR_ROM     SECTION(".vector.rom")
#define SECTION_ITCM_RAM       SECTION(".itcm.ram")
#define SECTION_DTCM_ROM       SECTION(".dtcm.rom")
#define SECTION_DTCM_RAM       SECTION(".dtcm.ram")

#define SECTION_SYSVIEW        SECTION(".sysview.start")
#define SECTION_VIDEO_E2O      SECTION(".video_e2o.dtcm")
#define SECTION_VIDEO_MD       SECTION(".video_md.dtcm")
#define SECTION_VIDEO_DEBUG    SECTION(".video_debug.dtcm")
#define SECTION_VIDEO_ROI      SECTION(".video_roi.dtcm")
#define SECTION_VIDEO_ERR      SECTION(".video_err.dtcm")

#define SECTION_VIDEO_CMD0     SECTION(".video_cmd0.dtcm")
#define SECTION_VIDEO_CMD1     SECTION(".video_cmd1.dtcm")
#define SECTION_VIDEO_CMD2     SECTION(".video_cmd2.dtcm")
#define SECTION_VIDEO_CMD3     SECTION(".video_cmd3.dtcm")
#define SECTION_VIDEO_CMD4     SECTION(".video_cmd4.dtcm")
#define SECTION_GMON           SECTION(".voe_gmon.ddr")
#define SECTION_FCS            SECTION(".fcs.itcm")
#define SECTION_FCS_DATA       SECTION(".fcs.dtcm")

#define SECTION_ISP_MASK_MAP   SECTION(".isp_grid_map.ddr")
#define SECTION_ISP_IQ_CALI    SECTION(".isp_iq_cali_data.ddr")


#endif

