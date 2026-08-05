/*
 * Realtek Semiconductor Corp.
 * Copyright (C) 2017 Grant Shen <grant_shen@realsil.com.cn>
 * Copyright (C) 2019 Sherry Cheng <sherry_cheng@realsil.com.cn>
 */

/*******************************************************************************

- Normal Preview Mode (if init preview is defined as 1080p RAW12)
  ATII=i2c,write,0x0100,0x00
  ATII=i2c,write,0x030F,0x39
  ATII=i2c,write,0x3022,0x24
  ATII=i2c,write,0x0100,0x01
  
- Normal Preview Mode (if init preview is defined as 360p RAW10)
  ATII=i2c,write,0x0100,0x00
  ATII=i2c,write,0x030F,0x32
  ATII=i2c,write,0x3022,0x24
  ATII=i2c,write,0x0100,0x01

- AO mode start
  ATII=i2c,write,0x0100,0x00
  ATII=i2c,write,0x3022,0x24
  ATII=i2c,write,0x0100,0x11

  use the following command to check if AO mode is active
  ATII=i2c,read,0x3128
  the value will continue to change

- Pre-Roll mode start
  ATII=i2c,write,0x0100,0x00
  ATII=i2c,write,0x030F,0x32 (360p RAW10)
  ATII=i2c,write,0x3022,0x23
  ATII=i2c,write,0x0100,0xA1

- Stop (srop normal preview, stop AO, stop pre-roll, etc.)
  ATII=i2c,write,0x0100,0x00

*******************************************************************************/

#include <stdio.h>
#include <sensor_entry.h>
#include "rts_isp_sensor_lib.h"

//#if _NT99236_SENSOR_

///////////////////////////////////////////////////////////////////////////////
// Novatek NT99236 configuration start ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// NT99236 initial mode
#define NT99236_Preview 0
#define NT99236_AO 1
#define NT99236_Pre_Roll 2

// NT99236 initial preview output
#define NT99236_Preview_1080P 0 // RAW12
#define NT99236_Preview_360P 1 // RAW10, for test only

#define Subsample_360P_X_Bin_Y_Bin 0
#define Subsample_360P_X_Bin_Y_Skip 1
#define Subsample_360P_X_Skip_Y_Skip 2

#define AO_Linear 0
#define AO_DCG 1

// select one
#define NT99236_Mode_Select NT99236_Preview
//#define NT99236_Mode_Select NT99236_AO
//#define NT99236_Mode_Select NT99236_Pre_Roll // RAW10

#if (NT99236_Mode_Select == NT99236_Pre_Roll) 
  // if pre-roll, only 1080p can be selected
  #define NT99236_Preview_Size NT99236_Preview_1080P
#else // preview or AO
  #define NT99236_Preview_Size NT99236_Preview_1080P
  //#define NT99236_Preview_Size NT99236_Preview_360P 
#endif

#if (NT99236_Preview_Size == NT99236_Preview_360P)
  // select one
  #define Preview_360P_Subsample Subsample_360P_X_Bin_Y_Bin
  //#define Preview_360P_Subsample Subsample_360P_X_Bin_Y_Skip
  //#define Preview_360P_Subsample Subsample_360P_X_Skip_Y_Skip 
#endif

// select one
//#define AO_360P_Subsample Subsample_360P_X_Bin_Y_Bin
//#define AO_360P_Subsample Subsample_360P_X_Bin_Y_Skip
#define AO_360P_Subsample Subsample_360P_X_Skip_Y_Skip

// select one
//#define AO_DR_Type AO_Linear
#define AO_DR_Type AO_DCG

///////////////////////////////////////////////////////////////////////////////
// Novatek NT99236 configuration end //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define SUPPORTED_ISP_NUM 1
#define RTS_ISP_HDR_CHAN_MAX 2

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define abs(x) ((x) >= 0 ? (x) : -(x))

struct fps_info {
	float fps;
	uint32_t hts;
	uint32_t clk;
};

struct nt99236_status {
	enum rts_isp_sensor_hdr_mode hdr;
	int min_vts;
	float exp_step;
	float last_exposure;
	int num;
	struct rts_isp_i2c_reg regs1[3];
};

struct nt99236_gain_config {
	uint8_t regValue;
	uint16_t gainValue;
};

static struct nt99236_status g_status[SUPPORTED_ISP_NUM] = {[0].hdr = LINEAR_MODE};

static const struct fps_info g_nt99236_fps_info_asic[] = {
	//{29.94f, 1182, 40000000},
	//{30.00f, 1182, 40000000}, // fps=30
	{24.00f, 1182, 40000000}, // fps=24
};

static struct rts_isp_i2c_reg g_nt99236_i2c_init_regs_asic[] = {
  //[Normal_Setting]
  {0x36E1, 0xC8},
  {0x36E3, 0xF6},
  {0x36E4, 0x06},
  {0x3688, 0x06},
  {0x3252, 0x11},
  {0x3690, 0x17},
  {0x36B2, 0x74},
  {0x36B3, 0x83},
  {0x32E1, 0x03},
  {0x3327, 0x01},   // VX settle
  {0x3328, 0x2C},
  {0x3334, 0x00},   // LCG VX settle
  {0x3335, 0x64},
  {0x325E, 0x0C}, 
  {0x303A, 0x12},
  {0x303B, 0x13},
  {0x3382, 0x04},
  {0x3383, 0x04},
  {0x3384, 0x04},
  {0x3385, 0x04},
  {0x3A0A, 0x03},  // Temperature sensor
  {0x0B04, 0x01},  // BLC Enable
  {0x0138, 0x01},  // Temperature Sensor
  {0x82E3, 0x03},
  {0x833F, 0x03},
  {0x803F, 0x20},
  {0x0B06, 0x01},  // DPC ON
  {0x0350, 0x00},
  
  //[Normal_Setting_DCG]
  {0x36B2, 0x94},
  {0x36B3, 0xA3},
  {0x325E, 0x06}, 
  {0x336C, 0x00},
  {0x336D, 0x60},
  {0x337A, 0x00},
  {0x337B, 0x60},
  {0x336E, 0x01},
  {0x336F, 0x08},
  {0x32B8, 0x05},
  {0x32B9, 0x88},
  {0x32F3, 0x02}, 
  {0x3328, 0x40},
  {0x3334, 0x01}, 
  {0x3335, 0x14},
  {0x3618, 0x53}, 
  {0x3260, 0x17},

#if (NT99236_Preview_Size == NT99236_Preview_1080P)  
  //[Mode17_MIPI_HDR_1920x1080_12b_29.94FPS]
  // MCLK:      24.00MHz 
  // BitDepth:  12bit
  // Datarate:  456.00Mbps
  // MIPI:      2 Lane
  // PCLK:      40.000Mhz
  // Size:      1920x1080 
  // FPS:       29.92~29.92 
  // Line:      1182 
  // Frame:     1131 
  // Mode:      HDR 
  
  // Mode Control 
  {0x0100, 0x00},  // Mode select
  
  // PLL 
  {0x0136, 0x18},  // External clock (INCK) frequency in MHZ
  {0x0137, 0x00},  // External clock (INCK) frequency in MHZ
  {0x0114, 0x01},  // Number of data lanes in use.
  {0x0303, 0x01},  // Video timing system clock divider value
  {0x0305, 0x03},  // Pre PLL clock divder value
  {0x0307, 0x50},  // PLL multiplier value
  {0x0309, 0x0A},  // Output timing pixel clock divider
  {0x030A, 0x0A},  // Output timing pixel clock divider2
  {0x030B, 0x03},  // Output timing system clock divider value
  {0x030C, 0x04},  // Output timing tg clock divider value
  {0x030F, 0x39},  // 2nd PLL multiplier value (for RAW12 MIPI datarate 480Mbps)
  //{0x030F, 0x32},  // 2nd PLL multiplier value (for RAW10 MIPI datarate 400Mbps)
  {0x302D, 0x04},  // System clock = (PLL1/4) / (Pix_Rto * Vt_sys_cLK_div -1)
  {0x3500, 0x80},  // 
  {0x3502, 0xD0},  // 
  {0x3530, 0x40},  // 

  // SIZE/FPS 
  {0x0342, 0x04},  // Line length
  {0x0343, 0x9E},  // Line length
  //{0x0340, 0x04},  // Frame length, fps=30, 1131
  //{0x0341, 0x6B},  // Frame length
  {0x0340, 0x05},  // Frame length, fps=24, 1415
  {0x0341, 0x87},  // Frame length
  {0x0344, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0345, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0346, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0347, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0348, 0x07},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x0349, 0x7F},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034A, 0x04},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034B, 0x37},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
  {0x0381, 0x01},  // Increment for even pixels ?0  2  4
  {0x0383, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0385, 0x01},  // Increment for even pixels ?0  2  4
  {0x0387, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0900, 0x00},  // Binning mode
  {0x0901, 0x11},  // High-nibble 7:4  = column binning factor
  {0x0408, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x0409, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x040A, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040B, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040C, 0x07},  // Image width after digital crop. (Multiples of 4)
  {0x040D, 0x80},  // Image width after digital crop. (Multiples of 4)
  {0x040E, 0x04},  // Image height after digital crop. (Multiples of 4)
  {0x040F, 0x38},  // Image height after digital crop. (Multiples of 4)
  {0x034C, 0x07},  // Width of image data output from the sensor
  {0x034D, 0x80},  // Width of image data output from the sensor
  {0x034E, 0x04},  // Height of image data output from the sensor
  {0x034F, 0x38},  // Height of image data output from the sensor
  {0x0389, 0x00},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  {0x038A, 0x00},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  {0x0280, 0x01},  // Output format control (RAW12)
  //{0x0280, 0x41},  // Output format control (RAW10)
  
#elif (NT99236_Preview_Size == NT99236_Preview_360P)

/*
  // X Binning Y Skip
  
  //[Mode18_MIPI_HDR_640x360_10b_30.00FPS]
  // MCLK:      24.00MHz 
  // BitDepth:  10bit
  // Datarate:  400Mbps //456.00Mbps                                                                
  // MIPI:      2 Lane
  // PCLK:      40.000Mhz
  // Size:      640x360 
  // FPS:       30.00~30.00 
  // Line:      1182 
  // Frame:     1128 
  // Mode:      HDR 
  
  // Mode Control 
  {0x0100, 0x00},  // Mode select
  
  // PLL 
  {0x0136, 0x18},  // External clock (INCK) frequency in MHZ
  {0x0137, 0x00},  // External clock (INCK) frequency in MHZ
  {0x0114, 0x01},  // Number of data lanes in use.
  {0x0303, 0x01},  // Video timing system clock divider value
  {0x0305, 0x03},  // Pre PLL clock divder value
  {0x0307, 0x50},  // PLL multiplier value
  {0x0309, 0x0A},  // Output timing pixel clock divider
  {0x030A, 0x0A},  // Output timing pixel clock divider2
  {0x030B, 0x03},  // Output timing system clock divider value
  {0x030C, 0x04},  // Output timing tg clock divider value
  //{0x030F, 0x39},  // 2nd PLL multiplier value (for RAW12 MIPI datarate 480Mbps)
  {0x030F, 0x32},  // 2nd PLL multiplier value (for RAW10 MIPI datarate 400Mbps)
  {0x302B, 0x00},  //
  {0x302D, 0x04},  // System clock = (PLL1/4) / (Pix_Rto * Vt_sys_cLK_div -1)
  {0x3500, 0x80},  // 
  {0x3502, 0xD0},  // 
  {0x3530, 0x40},  // 

  // SIZE/FPS 
  {0x0342, 0x04},  // Line length
  {0x0343, 0x9E},  // Line length
  //{0x0340, 0x04},  // Frame length, fps=30, 1128
  //{0x0341, 0x68},  // Frame length
  {0x0340, 0x05},  // Frame length, fps=24, 1415
  {0x0341, 0x87},  // Frame length
  {0x0344, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0345, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0346, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0347, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0348, 0x07},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x0349, 0x7F},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034A, 0x04},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034B, 0x37},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
  {0x0381, 0x01},  // Increment for even pixels ?0  2  4
  {0x0383, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0385, 0x01},  // Increment for even pixels ?0  2  4
  {0x0387, 0x05},  // Increment for odd pixels ?1  3  5
  {0x0900, 0x01},  // Binning mode
  {0x0901, 0x31},  // High-nibble 7:4  = column binning factor
  {0x0408, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x0409, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x040A, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040B, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040C, 0x02},  // Image width after digital crop. (Multiples of 4)
  {0x040D, 0x80},  // Image width after digital crop. (Multiples of 4)
  {0x040E, 0x01},  // Image height after digital crop. (Multiples of 4)
  {0x040F, 0x68},  // Image height after digital crop. (Multiples of 4)
  {0x034C, 0x02},  // Width of image data output from the sensor
  {0x034D, 0x80},  // Width of image data output from the sensor
  {0x034E, 0x01},  // Height of image data output from the sensor
  {0x034F, 0x68},  // Height of image data output from the sensor
  {0x0389, 0x00},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  {0x038A, 0x07},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  //{0x0280, 0x01},  // Output format control (RAW12)
  {0x0280, 0x41},  // Output format control (RAW10)
*/
  
 
  // X Binning Y Binning
  
  //[Mode18_MIPI_HDR_640x360_10b_30.00FPS]
  // MCLK:      24.00MHz 
  // BitDepth:  10bit
  // Datarate:  400Mbps //456.00Mbps                                                                
  // MIPI:      2 Lane
  // PCLK:      40.000Mhz
  // Size:      640x360 
  // FPS:       30.00~30.00 
  // Line:      1182 
  // Frame:     1128 
  // Mode:      HDR 
  
  // Mode Control 
  {0x0100, 0x00},  // Mode select
  
  // PLL 
  {0x0136, 0x18},  // External clock (INCK) frequency in MHZ
  {0x0137, 0x00},  // External clock (INCK) frequency in MHZ
  {0x0114, 0x01},  // Number of data lanes in use.
  {0x0303, 0x01},  // Video timing system clock divider value
  {0x0305, 0x03},  // Pre PLL clock divder value
  {0x0307, 0x50},  // PLL multiplier value
  {0x0309, 0x0A},  // Output timing pixel clock divider
  {0x030A, 0x0A},  // Output timing pixel clock divider2
  {0x030B, 0x03},  // Output timing system clock divider value
  {0x030C, 0x04},  // Output timing tg clock divider value
  //{0x030F, 0x39},  // 2nd PLL multiplier value (for RAW12 MIPI datarate 480Mbps)
  {0x030F, 0x32},  // 2nd PLL multiplier value (for RAW10 MIPI datarate 400Mbps)
  {0x302B, 0x00},  //
  {0x302D, 0x04},  // System clock = (PLL1/4) / (Pix_Rto * Vt_sys_cLK_div -1)
  {0x3500, 0x80},  // 
  {0x3502, 0xD0},  // 
  {0x3530, 0x40},  // 

  // SIZE/FPS 
  {0x0342, 0x04},  // Line length
  {0x0343, 0x9E},  // Line length
  //{0x0340, 0x04},  // Frame length, fps=30, 1128
  //{0x0341, 0x68},  // Frame length
  {0x0340, 0x05},  // Frame length, fps=24, 1415
  {0x0341, 0x87},  // Frame length
  {0x0344, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0345, 0x00},  // X address of the top left corner of the visible pixel data (Even Only)
  {0x0346, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0347, 0x00},  // Y address of the top left corner of the visible pixel data (Even Only)
  {0x0348, 0x07},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x0349, 0x7F},  // X address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034A, 0x04},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
  {0x034B, 0x37},  // Y address of the bottom right corner of the visible pixel data (Odd Only)
#if (Preview_360P_Subsample == Subsample_360P_X_Bin_Y_Bin) 
  {0x0381, 0x01},  // Increment for even pixels ?0  2  4
  {0x0383, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0385, 0x02},  // Increment for even pixels ?0  2  4
  {0x0387, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0900, 0x01},  // Binning mode
  {0x0901, 0x33},  // High-nibble 7:4  = column binning factor
#elif (Preview_360P_Subsample == Subsample_360P_X_Bin_Y_Skip) 
  {0x0381, 0x01},  // Increment for even pixels ?0  2  4
  {0x0383, 0x01},  // Increment for odd pixels ?1  3  5
  {0x0385, 0x01},  // Increment for even pixels ?0  2  4
  {0x0387, 0x05},  // Increment for odd pixels ?1  3  5
  {0x0900, 0x01},  // Binning mode
  {0x0901, 0x31},  // High-nibble 7:4  = column binning factor
#elif (Preview_360P_Subsample == Subsample_360P_X_Skip_Y_Skip) 
  {0x0381, 0x01},  // Increment for even pixels ?0  2  4
  {0x0383, 0x05},  // Increment for odd pixels ?1  3  5
  {0x0385, 0x01},  // Increment for even pixels ?0  2  4
  {0x0387, 0x05},  // Increment for odd pixels ?1  3  5
  {0x0900, 0x00},  // Binning mode
  {0x0901, 0x11},  // High-nibble 7:4  = column binning factor
#endif
  {0x0408, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x0409, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x040A, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040B, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x040C, 0x02},  // Image width after digital crop. (Multiples of 4)
  {0x040D, 0x80},  // Image width after digital crop. (Multiples of 4)
  {0x040E, 0x01},  // Image height after digital crop. (Multiples of 4)
  {0x040F, 0x68},  // Image height after digital crop. (Multiples of 4)
  {0x034C, 0x02},  // Width of image data output from the sensor
  {0x034D, 0x80},  // Width of image data output from the sensor
  {0x034E, 0x01},  // Height of image data output from the sensor
  {0x034F, 0x68},  // Height of image data output from the sensor
  {0x0389, 0x00},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  {0x038A, 0x05},  // Xstr_csrm sets 5 when x_str is 17 and xkip3 is enable
  //{0x0280, 0x01},  // Output format control (RAW12)
  {0x0280, 0x41},  // Output format control (RAW10)



  
#endif
                      
  //[AO_CW_Size]
  {0x3100, 0x20},  // Timer mode 
  //{0x3100, 0x21},  // Time+Trigger Mode
  {0x3101, 0x04},  // Pre-clock divider for AWM clock
  {0x3102, 0x03},  // AWM time unit = 1/(AWM clock/AWM_Time_Unit)
  {0x3103, 0xE8},  // AWM time unit = 1/(AWM clock/AWM_Time_Unit)
  //{0x3104, 0x03},  // test AWM timer auto trigger period = AWM_Timer_Period * AWM time unit  Ex : 1000 * 1ms  = 1s
  //{0x3105, 0xE8},  // test AWM timer auto trigger period = AWM_Timer_Period * AWM time unit  Ex : 1000 * 1ms  = 1s
  {0x3104, 0x00},  // AWM timer auto trigger period = AWM_Timer_Period * AWM time unit  Ex : 1000 * 1ms  = 1s
  {0x3105, 0xC8},  // AWM timer auto trigger period = AWM_Timer_Period * AWM time unit  Ex : 1000 * 1ms  = 1s
  {0x3106, 0x00},  // AWM output frame count (AWM_Total_Frame + 1) in each wakeup trigger
  {0x3107, 0x01},  // AWM output frame count (AWM_Total_Frame + 1) in each wakeup trigger
  //{0x3107, 0x00},  // AWM output frame count (AWM_Total_Frame + 1) in each wakeup trigger
  {0x310A, 0x00},  // AWM action repeat times after every trigger
  {0x310D, 0x20},  // 
  {0x310E, 0x00},  // 
  {0x310F, 0x00},  // 
  {0x3110, 0x15},  // Enable 1-frame mode, external trigger to preview, trigger without image 
  //{0x3110, 0x14},  // Disable 1-frame mode, external trigger to preview, trigger without image 
  //{0x3110, 0x1C},  // Disable 1-frame mode, external trigger to preview, trigger with image 
  {0x3048, 0x40},  // 
  {0x3B01, 0x02},  // 

  //[AO_SPI_640x360]
  //{0x3B02, 0x85},  // AS test pattern
  {0x3B05, 0x00},  // 
  {0x3B06, 0xE5},  // 
  {0x3B07, 0x02},  // Pre-roll read out X size
  {0x3B08, 0x80},  // Pre-roll read out X size
  {0x3B09, 0x01},  // Pre-roll read out Y size
  {0x3B0A, 0x68},  // Pre-roll read out Y size
  {0x3B51, 0x06},  // 
  {0x3B56, 0x38},  // SPI write data command
  {0x3B57, 0xEB},  // SPI read data command
  {0x3B58, 0x00},  // SPI Command Enable write statue
  {0x3B59, 0x00},  // SPI Command Enable read statue
  {0x3B5A, 0x97},  // SPI Command Enable write data
  {0x3B5B, 0xB7},  // SPI Command Enable read data
  {0x3123, 0x80},  // 
  {0x3124, 0x00},  // SPI write initial address Low byte
  {0x3125, 0x00},  // SPI write end address
  {0x3126, 0x22},  // SPI write end address
  {0x3130, 0x01},  // 
  {0x0701, 0x0D},  // 
  {0x0764, 0xF7},  // 
  {0x0765, 0x08},  // Output current fine trimming (2% per step)
  {0x3262, 0x01},  // 
  {0x3263, 0x6C},  // 

  //[F2A_TG]
  {0x0505, 0x04},  // Fae_l_len
  {0x0506, 0x9E},  // Fae_l_len
  {0x0503, 0x02},  // Fae_f_len
  {0x0504, 0x3C},  // Fae_f_len
  {0x0507, 0x00},  // Fae_ystr
  {0x0508, 0x00},  // Fae_ystr
  {0x0509, 0x04},  // Fae_Yend
  {0x050A, 0x37},  // Fae_Yend
  {0x050B, 0x02},  // Fae_y_sz
  {0x050C, 0x1C},  // Fae_y_sz
  {0x050E, 0x13},  // 
  {0x050F, 0x13},  // 
  {0x0510, 0x00},  // Fae_xstr
  {0x0511, 0x00},  // 
  {0x0512, 0x07},  // Fae_xend
  {0x0513, 0x7F},  // 
  {0x0514, 0x03},  // Fae_x_sz
  {0x0515, 0xC0},  // 
  {0x0410, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x0411, 0x00},  // Offset from x address of the top left corner visible pixel data after analog crop and binning. 
  {0x0412, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x0413, 0x00},  // Offset from y address of the top left corner of the visible pixel data after analog crop and bi
  {0x0414, 0x03},  // Image width after digital crop. (Multiples of 4)
  {0x0415, 0xC0},  // Image width after digital crop. (Multiples of 4)
  {0x0416, 0x02},  // Image height after digital crop. (Multiples of 4)
  {0x0417, 0x1C},  // Image height after digital crop. (Multiples of 4)

  //[CS_AO_640x360]
  {0x3108, 0x00},
#if (AO_DR_Type == AO_Linear)
  {0x3150, 0x03},
  {0x3151, 0x42},
  {0x3152, 0x01},
  {0x3154, 0x03},
  {0x3155, 0x43},
  {0x3156, 0x27},
#elif (AO_DR_Type == AO_DCG)
  {0x3150, 0x03},
  {0x3151, 0x42},
  {0x3152, 0x04},
  {0x3154, 0x03},
  {0x3155, 0x43},
  {0x3156, 0x9E},
#endif
  {0x3158, 0x03},
  {0x3159, 0x40},
  {0x315A, 0x04},
  {0x315C, 0x03},
  {0x315D, 0x41},
  {0x315E, 0x6C},
  {0x3160, 0x03},
  {0x3161, 0x44},
  {0x3162, 0x00},
  {0x3164, 0x03},
  {0x3165, 0x45},
  {0x3166, 0x00},
  {0x3168, 0x03},
  {0x3169, 0x46},
  {0x316A, 0x00},
  {0x316C, 0x03},
  {0x316D, 0x47},
  {0x316E, 0x00},
  {0x3170, 0x03},
  {0x3171, 0x48},
  {0x3172, 0x07},
  {0x3174, 0x03},
  {0x3175, 0x49},
  {0x3176, 0x7F},
  {0x3178, 0x03},
  {0x3179, 0x4A},
  {0x317A, 0x04},
  {0x317C, 0x03},
  {0x317D, 0x4B},
  {0x317E, 0x37},
/*
  {0x3180, 0x03},
  {0x3181, 0x81},
  {0x3182, 0x01},
  {0x3184, 0x03},
  {0x3185, 0x83},
  {0x3186, 0x05},
  {0x3188, 0x03},
  {0x3189, 0x85},
  {0x318A, 0x01},
  {0x318C, 0x03},
  {0x318D, 0x87},
  {0x318E, 0x05},
  {0x3108, 0x01},
  {0x3150, 0x09},
  {0x3151, 0x00},
  {0x3152, 0x00},
  {0x3154, 0x09},
  {0x3155, 0x01},
  {0x3156, 0x11},
*/
#if (AO_360P_Subsample == Subsample_360P_X_Bin_Y_Bin)
  {0x3180, 0x03},
  {0x3181, 0x81},
  {0x3182, 0x01},
  {0x3184, 0x03},
  {0x3185, 0x83},
  {0x3186, 0x01},
  {0x3188, 0x03},
  {0x3189, 0x85},
  {0x318A, 0x02},
  {0x318C, 0x03},
  {0x318D, 0x87},
  {0x318E, 0x01},
  {0x3108, 0x01},
  {0x3150, 0x09},
  {0x3151, 0x00},
  {0x3152, 0x01},
  {0x3154, 0x09},
  {0x3155, 0x01},
  {0x3156, 0x33},
#elif (AO_360P_Subsample == Subsample_360P_X_Bin_Y_Skip)
  {0x3180, 0x03},
  {0x3181, 0x81},
  {0x3182, 0x01},
  {0x3184, 0x03},
  {0x3185, 0x83},
  {0x3186, 0x01},
  {0x3188, 0x03},
  {0x3189, 0x85},
  {0x318A, 0x01},
  {0x318C, 0x03},
  {0x318D, 0x87},
  {0x318E, 0x05},
  {0x3108, 0x01},
  {0x3150, 0x09},
  {0x3151, 0x00},
  {0x3152, 0x01},
  {0x3154, 0x09},
  {0x3155, 0x01},
  {0x3156, 0x31},
#elif (AO_360P_Subsample == Subsample_360P_X_Skip_Y_Skip)
  {0x3180, 0x03},
  {0x3181, 0x81},
  {0x3182, 0x01},
  {0x3184, 0x03},
  {0x3185, 0x83},
  {0x3186, 0x05},
  {0x3188, 0x03},
  {0x3189, 0x85},
  {0x318A, 0x01},
  {0x318C, 0x03},
  {0x318D, 0x87},
  {0x318E, 0x05},
  {0x3108, 0x01},
  {0x3150, 0x09},
  {0x3151, 0x00},
  {0x3152, 0x00},
  {0x3154, 0x09},
  {0x3155, 0x01},
  {0x3156, 0x11},
#endif
  {0x3158, 0x04},
  {0x3159, 0x08},
  {0x315A, 0x00},
  {0x315C, 0x04},
  {0x315D, 0x09},
  {0x315E, 0x00},
  {0x3160, 0x04},
  {0x3161, 0x0A},
  {0x3162, 0x00},
  {0x3164, 0x04},
  {0x3165, 0x0B},
  {0x3166, 0x00},
  {0x3168, 0x04},
  {0x3169, 0x0C},
  {0x316A, 0x02},
  {0x316C, 0x04},
  {0x316D, 0x0D},
  {0x316E, 0x80},
  {0x3170, 0x04},
  {0x3171, 0x0E},
  {0x3172, 0x01},
  {0x3174, 0x04},
  {0x3175, 0x0F},
  {0x3176, 0x68},
  {0x3178, 0x03},
  {0x3179, 0x4C},
  {0x317A, 0x02},
  {0x317C, 0x03},
  {0x317D, 0x4D},
  {0x317E, 0x80},
  {0x3180, 0x03},
  {0x3181, 0x4E},
  {0x3182, 0x01},
  {0x3184, 0x03},
  {0x3185, 0x4F},
  {0x3186, 0x68},
  {0x3188, 0x03},
  {0x3189, 0x89},
  {0x318A, 0x00},
  {0x318C, 0x03},
  {0x318D, 0x8A},
  {0x318E, 0x05},
  {0x3108, 0x02},
  {0x3150, 0x36},
  {0x3151, 0xE1},
  {0x3152, 0xC8},
  {0x3154, 0x36},
  {0x3155, 0xE3},
  {0x3156, 0xF6},
  {0x3158, 0x36},
  {0x3159, 0xE4},
  {0x315A, 0x06},
  {0x315C, 0x36},
  {0x315D, 0x88},
  {0x315E, 0x06},
  {0x3160, 0x32},
  {0x3161, 0x52},
  {0x3162, 0x80},
  {0x3164, 0x36},
  {0x3165, 0x90},
  {0x3166, 0x17},
  {0x3168, 0x36},
  {0x3169, 0xB2},
  {0x316A, 0x74},
  {0x316C, 0x36},
  {0x316D, 0xB3},
  {0x316E, 0x83},
  {0x3170, 0x32},
  {0x3171, 0xE1},
  {0x3172, 0x03},
  {0x3174, 0x33},
  {0x3175, 0x27},
  {0x3176, 0x01},
  {0x3178, 0x33},
  {0x3179, 0x28},
  {0x317A, 0x2C},
  {0x317C, 0x33},
  {0x317D, 0x34},
  {0x317E, 0x00},
  {0x3180, 0x33},
  {0x3181, 0x35},
  {0x3182, 0x64},
  {0x3184, 0x32},
  {0x3185, 0x5E},
  {0x3186, 0x0C},
  {0x3188, 0x30},
  {0x3189, 0x3A},
  {0x318A, 0x12},
  {0x318C, 0x30},
  {0x318D, 0x3B},
  {0x318E, 0x13},
  {0x3108, 0x03},
  {0x3150, 0x33},
  {0x3151, 0x82},
  {0x3152, 0x04},
  {0x3154, 0x33},
  {0x3155, 0x83},
  {0x3156, 0x04},
  {0x3158, 0x33},
  {0x3159, 0x84},
  {0x315A, 0x04},
  {0x315C, 0x33},
  {0x315D, 0x85},
  {0x315E, 0x04},
  {0x3160, 0x3A},
  {0x3161, 0x0A},
  {0x3162, 0x03},
  {0x3164, 0x0B},
  {0x3165, 0x04},
  {0x3166, 0x01},
  {0x3168, 0x01},
  {0x3169, 0x38},
  {0x316A, 0x01},
  {0x316C, 0x82},
  {0x316D, 0xE3},
  {0x316E, 0x03},
  {0x3170, 0x83},
  {0x3171, 0x3F},
  {0x3172, 0x03},
  {0x3174, 0x80},
  {0x3175, 0x3F},
  {0x3176, 0x20},
  {0x3178, 0x0B},
  {0x3179, 0x06},
  {0x317A, 0x01},
  {0x317C, 0x03},
  {0x317D, 0x50},
  {0x317E, 0x00},
  {0x3180, 0x36},
  {0x3181, 0x18},
  {0x3182, 0x43},
  {0x3184, 0x32},
  {0x3185, 0x60},
  {0x3186, 0x0F},
#if (AO_DR_Type == AO_Linear)
  {0x3188, 0x02},
  {0x3189, 0x80},
  {0x318A, 0x10},
#elif (AO_DR_Type == AO_DCG)
  {0x3188, 0x02},
  {0x3189, 0x80},
  {0x318A, 0x51},
#endif
  {0x318C, 0x32},
  {0x318D, 0xF3},
  {0x318E, 0x02},
  {0x3108, 0x04},
  {0x3150, 0x35},
  {0x3151, 0x00},
  {0x3152, 0x00},
  {0x3154, 0x35},
  {0x3155, 0x30},
  {0x3156, 0xC0},
  {0x3158, 0x30},
  {0x3159, 0x2B},
  {0x315A, 0x01},
#if (AO_DR_Type == AO_Linear)
  {0x315C, 0x03},
  {0x315D, 0x03},
  {0x315E, 0x04},
#elif (AO_DR_Type == AO_DCG)
  {0x315C, 0x03},
  {0x315D, 0x03},
  {0x315E, 0x01},
#endif
  {0x3160, 0x03},
  {0x3161, 0x05},
  {0x3162, 0x01},
  {0x3164, 0x03},
  {0x3165, 0x07},
  {0x3166, 0xA0},
  {0x3168, 0x03},
  {0x3169, 0x0F},
  {0x316A, 0x71},
  {0x316C, 0x03},
  {0x316D, 0x0B},
  {0x316E, 0x02}, //0x00
  {0x3170, 0x33},
  {0x3171, 0x6C},
  {0x3172, 0x00},
  {0x3174, 0x33},
  {0x3175, 0x6D},
  {0x3176, 0x60},
  {0x3178, 0x33},
  {0x3179, 0x6E},
  {0x317A, 0x01},
  {0x317C, 0x33},
  {0x317D, 0x6F},
  {0x317E, 0x08},
  {0x3180, 0x32},
  {0x3181, 0xB8},
  {0x3182, 0x05},
  {0x3184, 0x32},
  {0x3185, 0xB9},
  {0x3186, 0x88},
  {0x3188, 0x3B},
  {0x3189, 0x0E},
  {0x318A, 0x7F},
  {0x318C, 0x30}, // add to fix trigger to preview bug 
  {0x318D, 0x69}, // Reg 0x3069 = 0x1A
  {0x318E, 0x1A},
  {0x3109, 0x50},
  
  // AE 
  //{0x8205, 0x03},  // AE on 
  //{0x8206, 0x03},  // AWB on
  {0x82BB, 0x67},  // 
  {0x82B8, 0x06},  // AE detect range upper
  {0x82B9, 0x06},  // AE detect range lower
  {0x82BC, 0x38},  // AE target luminance
  {0x82CB, 0x20},  // AE target luminance at dark environment  must less than AE_Target_Lum
  {0x82BD, 0x03},  // AE convergence range upper
  {0x82BE, 0x03},  // AE convergence range lower
  {0x82BF, 0x50},  // Minimum exposure line limit for AEC (Log value)
  {0x82C0, 0x5A},  // AE_Max_ExpLine for AEC.
  {0x82C1, 0x5A},  // For P_chart. (Log Base) (Undocumented)
  {0x82C2, 0x5A},  // For P_chart. (Log Base) (Undocumented)
  {0x82C3, 0x00},  // AE auto gain control minimum limit
  {0x82C4, 0x3F},  // AE auto gain control maximum limit
  {0x82C5, 0x0F},  // For P_chart. (Undocumented)
  {0x82C6, 0x1F},  // For P_chart. (Undocumented)
  {0x82D3, 0x01},  // AE flicker exposure line for 50Hz (1/100 sec).
  {0x82D4, 0x52},  // AE flicker exposure line for 50Hz (1/100 sec).
  {0x82D5, 0x85},  // Base on Flicker_Base_50 value.
  {0x82D6, 0x01},  // AE flicker exposure line for 60Hz (1/120 sec).
  {0x82D7, 0x1A},  // AE flicker exposure line for 60Hz (1/120 sec).
  {0x82D8, 0x81},  // Base on Flicker_Base_60 value.
  {0x82E3, 0x03},  // LA result selection for AE input
  {0x8741, 0x4C},  // LSC bottom EV boundary
  
  // additional add for Realtek platform
  {0x804C, 0x01},  // OB_Const_H
  {0x804D, 0x00},  // OB_Const_L
  
#if (NT99236_Mode_Select == NT99236_Preview)
  // Normal Prevoew Mode 
  {0x3022, 0x24},  // MIPI ID
  {0x0100, 0x01},  // Mode select
#elif (NT99236_Mode_Select == NT99236_AO)
  // AO Mode 
  {0x3022, 0x24},  // MIPI ID
  {0x0100, 0x11},  // Mode select  
#elif (NT99236_Mode_Select == NT99236_Pre_Roll)
  // Pre-Roll
  {0x030F, 0x32},  // 2nd PLL multiplier value (for RAW10 MIPI datarate 400Mbps)
  {0x3022, 0x23},  // MIPI ID
  {0x0100, 0xA1},  // Mode select
#endif
};

static struct nt99236_gain_config g_nt99236_gain_config[] = {
//   Reg 0x0206/0x0207 Gain(16=1x)
#if 1
  {0x00, 16},
  {0x01, 17},
  {0x02, 18},
  {0x03, 19},
  {0x04, 20},
  {0x05, 21},
  {0x06, 22},
  {0x07, 23},
  {0x08, 24},
  {0x09, 25},
  {0x0A, 26},
  {0x0B, 27},
  {0x0C, 28},
  {0x0D, 29},
  {0x0E, 30},
  {0x0F, 31},
  {0x10, 32},
  {0x11, 34},
  {0x12, 36},
  {0x13, 38},
  {0x14, 40},
  {0x15, 42},
  {0x16, 44},
  {0x17, 46},
  {0x18, 48},
  {0x19, 50},
  {0x1A, 52},
  {0x1B, 54},
  {0x1C, 56},
  {0x1D, 58},
  {0x1E, 60},
  {0x1F, 62},
  {0x20, 64},
  {0x21, 68},
  {0x22, 72},
  {0x23, 76},
  {0x24, 80},
  {0x25, 84},
  {0x26, 88},
  {0x27, 92},
  {0x28, 96},
  {0x29, 100},
  {0x2A, 104},
  {0x2B, 108},
  {0x2C, 112},
  {0x2D, 116},
  {0x2E, 120},
  {0x2F, 124},
  {0x30, 128},
  {0x31, 136},
  {0x32, 144},
  {0x33, 152},
  {0x34, 160},
  {0x35, 168},
  {0x36, 176},
  {0x37, 184},
  {0x38, 192},
  {0x39, 200},
  {0x3A, 208},
  {0x3B, 216},
  {0x3C, 224},
  {0x3D, 232},
  {0x3E, 240},
  {0x3F, 248},
  {0x40, 256},
  {0x41, 272},
  {0x42, 288},
  {0x43, 304},
  {0x44, 320},
  {0x45, 336},
  {0x46, 352},
  {0x47, 368},
  {0x48, 384},
  {0x49, 400},
  {0x4A, 416},
  {0x4B, 432},
  {0x4C, 448},
  {0x4D, 464},
  {0x4E, 480},
  {0x4F, 496},
  {0x50, 512},
#else
  {0x00, 16},
  {0x10, 32},
  {0x20, 64},
  {0x30, 128},
  {0x40, 256},
  {0x50, 512},
#endif
};

static int nt99236_get_info(uint32_t isp_id, struct rts_isp_sensor_info *info)
{
	int i;
	struct rts_isp_snr_pwr *up = &info->power_up;
	struct rts_isp_snr_pwr *down = &info->power_down;
	printf("[Sensor Driver] Enter nt99236_get_info\r\n");

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;


	info->modes.mode[0].hdr = LINEAR_MODE;//RTS_ISP_HDR_NONE;  
	
#if (NT99236_Mode_Select == NT99236_Preview)
  #if (NT99236_Preview_Size == NT99236_Preview_1080P) 
	info->modes.mode[0].size.w = 1920;
	info->modes.mode[0].size.h = 1080;
	#elif (NT99236_Preview_Size == NT99236_Preview_360P)
	info->modes.mode[0].size.w = 640;  
  info->modes.mode[0].size.h = 360;  
  #endif 	
#elif (NT99236_Mode_Select == NT99236_Pre_Roll)
  info->modes.mode[0].size.w = 640;  
  info->modes.mode[0].size.h = 360;   
#endif

	info->modes.mode[0].fps = g_nt99236_fps_info_asic[0].fps;
	info->modes.num = 1;

	info->i2c.i2c_id = 0x1B;
	info->i2c.addr_len = 2;
	info->i2c.data_len = 1;

	g_status->hdr = LINEAR_MODE; //LINEAR_MODE, HDR_MODE
	info->cur_hdr_mode = g_status->hdr;

  // power on sequence
	i = 0;
	
	set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 500);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_LOW, 0);
	set_power_item(&up->items[i++], SNR_PWDN_GPIO, GPIO_LOW, 0);
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 500);
	//set_power_item(&up->items[i++], SNR_HCLK, 0, 100);
	
	//set_power_item(&up->items[i++], SNR_HCLK, CLK_24M, 500);
	set_power_item(&up->items[i++], SNR_RST_GPIO, GPIO_HIGH, 100);
	up->num = i;
	
	// power off sequence
	i = 0;
	set_power_item(&down->items[i++], SNR_RST_GPIO, 0, 100);
	set_power_item(&down->items[i++], SNR_PWDN_GPIO, 0, 1000);
	set_power_item(&down->items[i++], SNR_HCLK, 0, 1000);
	down->num = i;
	
	printf("[Sensor Driver] NT99236 Power on Sequence! \r\n");
		
	return RTS_ISP_OK;
}

static const struct fps_info *nt99236_get_fps_info(uint16_t fps)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(g_nt99236_fps_info_asic); i++)
		if (fps == g_nt99236_fps_info_asic[i].fps)
			break;
	if (i == ARRAY_SIZE(g_nt99236_fps_info_asic))
		return NULL;
	return &g_nt99236_fps_info_asic[i];

}

static int nt99236_get_init_info(uint32_t isp_id,
				const struct rts_isp_sensor_mode *mode,
				struct rts_isp_sensor_init_info *info)
{
	const struct fps_info *fps_info;
	struct nt99236_status *status;

	if (isp_id >= SUPPORTED_ISP_NUM || !info)
		return -RTS_ISP_EINVAL;

	//printf("nt99236 get fps %u init info\n", fps);

	status = &g_status[isp_id];
	status->hdr = mode->hdr;

	fps_info = nt99236_get_fps_info(mode->fps);
	if (!fps_info)
		return -RTS_ISP_EINVAL;

	//printf("fps: %u, pclk: %u, hts: %u\n", fps_info->fps, fps_info->clk, fps_info->hts);

	set_init_i2c_regs(info->sensor_regs[0], g_nt99236_i2c_init_regs_asic, 0);
	
	info->interface.interface = SNR_INTERFACE_MIPI;
	info->interface.mipi.lanes = MIPI_LANE0 | MIPI_LANE1;
	info->interface.mipi.hs_term = 0x5;
	info->interface.type = RAW_SENSOR;
#if (NT99236_Mode_Select == NT99236_Preview)
  #if (NT99236_Preview_Size == NT99236_Preview_1080P) 
	info->interface.bit_depth = SNR_12BIT;
	info->mipi_behavor = NONE_HDR; 
	info->size.w = 1920;
	info->size.h = 1080;
	#elif (NT99236_Preview_Size == NT99236_Preview_360P) 
	info->interface.bit_depth = SNR_10BIT; // RAW10
  info->mipi_behavor = NONE_HDR; 
  info->size.w = 640;
  info->size.h = 360;
	#endif
#elif (NT99236_Mode_Select == NT99236_Pre_Roll)
  info->interface.bit_depth = SNR_10BIT; // RAW10
  info->mipi_behavor = NONE_HDR; 
  info->size.w = 640;
  info->size.h = 360;
#endif
	info->start.x = 0;
	info->start.y = 0;
	info->hts = fps_info->hts;
	info->pclk = fps_info->clk;
	//info->min_vts = status->min_vts = 1131;
	//info->min_vts = status->min_vts = 1132; // fps=30
	info->min_vts = status->min_vts = 1415; // fps=24
	//info->max_vts = 6786;
	//info->max_vts = 1132; // fps=30
	//info->max_vts = 1415; // fps=24
	info->max_vts = 3396; // fps=10

	status->exp_step = 1e6 * info->hts / info->pclk; /* us */
	return RTS_ISP_OK;
}
static int nt99236_start(uint32_t isp_id)
{
	struct nt99236_status *status;
	if (isp_id >= SUPPORTED_ISP_NUM)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	status->last_exposure = 0;
	return RTS_ISP_OK;
}

static uint16_t get_sensor_gain_reg(float fAGain, struct nt99236_status *status)
{
	int i;
	uint16_t gain = fAGain * 16;
	
	if (gain >= 512) {	//32x
		gain = 512;
		status->num = 5;
	} else {
		for (i = 0; i < ARRAY_SIZE(g_nt99236_gain_config) - 1; i++) {
			if (gain >= g_nt99236_gain_config[i].gainValue &&
			    gain < g_nt99236_gain_config[i + 1].gainValue) {
				gain = g_nt99236_gain_config[i].gainValue;
				status->num = i;
				break;
			}
		}
	}
	return gain;
}

static float get_sensor_real_gain(uint16_t wAGain)
{
	return wAGain / 16.0f;
}

uint16_t clip_d_word(uint16_t current, uint16_t minimum, uint16_t maximum)
{
	if (current > maximum)
		return maximum;
	if (current < minimum)
		return minimum;
	return current;
}

static int nt99236_get_tuned_again(uint32_t isp_id,
				  float again[RTS_ISP_HDR_CHAN_MAX])
{
	int gain_reg;
	struct nt99236_status *status;
	
	if (isp_id >= SUPPORTED_ISP_NUM || !again)
		return -RTS_ISP_EINVAL;
	status = &g_status[isp_id];
	gain_reg = get_sensor_gain_reg(again[0], status);
	again[0] = get_sensor_real_gain(gain_reg);

	return RTS_ISP_OK;
}
static int nt99236_get_tuned_dgain(uint32_t isp_id,
				  float dgain[RTS_ISP_HDR_CHAN_MAX])
{
	if (isp_id >= SUPPORTED_ISP_NUM || !dgain)
		return -RTS_ISP_EINVAL;
	dgain[0] = 1.0f;

	return RTS_ISP_OK;
}

static int nt99236_get_exposure_gain_info(uint32_t isp_id,
					 const struct rts_isp_sensor_exp_gain *exp_gain,
					 struct rts_isp_sync_regs *regs)
{
  //Kenny: need to review again
	int i;
	uint32_t vts;
	struct nt99236_status *status;
	struct rts_isp_sync_reg *reg;
	uint16_t exposure_rows;
  
	if (isp_id >= SUPPORTED_ISP_NUM || !exp_gain || !regs)
		return -RTS_ISP_EINVAL;

	status = &g_status[isp_id];
	vts = exp_gain->vts;
	reg = regs->reg;
	
	i = 0;
	set_sync_i2c(&reg[i++], 0x0104, 0x10);
	if (abs(status->last_exposure - exp_gain->exposure[0]) > 0.001f) {
		exposure_rows = exp_gain->exposure[0] / status->exp_step + 0.5f;
		exposure_rows = exposure_rows << 4;
		set_sync_i2c(&reg[i++], 0x0202, (exposure_rows & 0xff00) >> 8);
		set_sync_i2c(&reg[i++], 0x0203, exposure_rows & 0xff);
		status->last_exposure = exp_gain->exposure[0];
	}
	set_sync_i2c(&reg[i++], 0x0206, g_nt99236_gain_config[status->num].regValue);
	set_sync_i2c(&reg[i++], 0x0207, g_nt99236_gain_config[status->num].regValue);
	set_sync_i2c(&reg[i++], 0x0340, vts >> 8);
	set_sync_i2c(&reg[i++], 0x0341, vts & 0xff);
	set_sync_i2c(&reg[i++], 0x0104, 0x00);
	regs->num = i;

	return RTS_ISP_OK;
}

static int nt99236_set_mirror_flip(uint32_t isp_id,
								  struct rts_isp_sensor_mirror_flip *mf_info)
{
	int i;
	uint16_t bySnrImgDir;
	struct rts_isp_sync_reg *reg;

	bySnrImgDir = mf_info->mirror_en != 0;
	bySnrImgDir = (mf_info->flip_en != 0) << 1 | bySnrImgDir;
	mf_info->delay_frames = 1;

	i = 0;
	reg = mf_info->regs.reg;
	switch(bySnrImgDir)//
	{
		case 0: //normal
		default:
		  printf("[Sensor Driver] Position Normal \r\n");
		  //set_sync_i2c(&reg[i++], 0x0100, 0x00);
      set_sync_i2c(&reg[i++], 0x0101, 0x00);
      //set_sync_i2c(&reg[i++], 0x0100, 0x01);
			break;
		case 1: // Mirror
		  printf("[Sensor Driver] Position Mirror \r\n");
		  //set_sync_i2c(&reg[i++], 0x0100, 0x00);
      set_sync_i2c(&reg[i++], 0x0101, 0x01);
      //set_sync_i2c(&reg[i++], 0x0100, 0x01);
			break;
		case 2: // VFlip
		  printf("[Sensor Driver] Position Flip \r\n");
		  //set_sync_i2c(&reg[i++], 0x0100, 0x00);
      set_sync_i2c(&reg[i++], 0x0101, 0x02);
      //set_sync_i2c(&reg[i++], 0x0100, 0x01);
			break;
		case 3:	// Rotate
		  printf("[Sensor Driver] Position Rotate \r\n");
		  //set_sync_i2c(&reg[i++], 0x0100, 0x00);
      set_sync_i2c(&reg[i++], 0x0101, 0x03);
      //set_sync_i2c(&reg[i++], 0x0100, 0x01);
      break;
	}
	mf_info->regs.num = i;

	return RTS_ISP_OK;
}

static int nt99236_check(uint32_t isp_id)
{
	int ret;
	int id;
	struct rts_isp_i2c_reg reg;

  rts_isp_sensor_access_prepare();

	reg.addr = 0x0000;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);
	if (ret) {
	    rts_isp_sensor_access_unprepare();
		return ret;
	}
	id = reg.data << 8;

	reg.addr = 0x0001;
	ret = rts_isp_read_sensor_reg(isp_id, &reg);

    rts_isp_sensor_access_unprepare();

	if (ret)
		return ret;
	id |= reg.data;

  printf("[Sensor Driver] id = %d !\n", id);
	
	if (id == 0x9236)
		return RTS_ISP_OK;
	else
		return -RTS_ISP_EINVAL;
	
	return RTS_ISP_OK;
}

static const struct rts_isp_sensor_ops nt99236_ops = 
{
	.ops_version = SENSOR_OPS_VERSION,
	.name = "nt99236",

	.get_info = nt99236_get_info,
	.get_init_info = nt99236_get_init_info,
	.start = nt99236_start,
	.get_tuned_again = nt99236_get_tuned_again,
	.get_tuned_dgain = nt99236_get_tuned_dgain,
	.get_exposure_gain_info = nt99236_get_exposure_gain_info,
	.set_mirror_flip = nt99236_set_mirror_flip,
	.check = nt99236_check,

};

const struct rts_isp_sensor_ops *rts_isp_get_sensor_ops(void)
{
	return &nt99236_ops;
}

//#endif


