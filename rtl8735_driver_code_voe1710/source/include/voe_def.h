#ifndef _VOE_DEF_H_
#define _VOE_DEF_H_

#include "hal_video_common.h"

SECTION_VIDEO_CMD0 volatile __attribute__ ((aligned (32))) commandLine_s cmd0
= {

		.CodecType           = CODEC_H264,

		.firstPic            = 0,
		.lastPic             = 0,
		.inputRateNumer      = 30,				// -j
		.inputRateDenom      = 1,				//
		.outputRateNumer     = 30,				// -f
		.outputRateDenom     = 1,

		.width               = 1920,
		.height              = 1080,
		.lumWidthSrc         = 1920,
		.lumHeightSrc        = 1080,
		.horOffsetSrc        = DEFAULT,
		.verOffsetSrc        = DEFAULT,
		.videoStab           = DEFAULT,
		.rotation            = 0,				// -r
		.inputFormat         = 1, 				// Modify default input format is NV12

		.intraPicRate        = 30,				// -R
		// default HEVC
#if 0
		.outputFormat     = VCENC_VIDEO_CODEC_HEVC,
		.max_cu_size      = 64,
		.min_cu_size      = 8,
		.max_tr_size      = 16,
		.min_tr_size      = 4,
		.tr_depth_intra   = 2, 							 //mfu =>0
		.tr_depth_inter   = 4,							// (.max_cu_size == 64) ? 4 : 3,

		.level            = VCENC_HEVC_LEVEL_6,
		.profile          = VCENC_HEVC_MAIN_PROFILE,	// default is HEVC MAIN profile
#else
		.outputFormat     = VCENC_VIDEO_CODEC_H264,
		.max_cu_size      = 16,
		.min_cu_size      = 8,
		.max_tr_size      = 16,
		.min_tr_size      = 4,
		.tr_depth_intra   = 1,
		.tr_depth_inter   = 2,
		.level            = VCENC_H264_LEVEL_5_1,
		.profile          = VCENC_H264_HIGH_PROFILE,	// default is HEVC HIGH profile

#endif
		.tier             = VCENC_HEVC_MAIN_TIER,


		.bitPerSecond = 1024000,						// -B
		.bitVarRangeI = 10000,
		.bitVarRangeP = 10000,
		.tolMovingBitRate = 2000,
		.monitorFrames = DEFAULT,
		.tolCtbRcInter = DEFAULT,
		.tolCtbRcIntra = DEFAULT,
		.u32StaticSceneIbitPercent = 80,
		.intraQpDelta = DEFAULT,

		.disableDeblocking = 0,

		.tc_Offset = -2,
		.beta_Offset = 5,

		.qpHdr = DEFAULT,
		.qpMin = DEFAULT,
		.qpMax = DEFAULT,
		.qpMinI = DEFAULT,
		.qpMaxI = DEFAULT,
		.picRc = 1,
		.ctbRc = 0, //CTB_RC
		.cpbSize = 1000000,
		.bitrateWindow = DEFAULT,
		.fixedIntraQp = 0,
		.hrdConformance = 0,
		.smoothPsnrInGOP = 0,
		.vbr = 0,

		.byteStream = VCENC_BYTE_STREAM,		// cml->byteStream = (cml->byteStream) ? VCENC_BYTE_STREAM : VCENC_NAL_UNIT_STREAM;

		.chromaQpOffset = 0,

		.enableSao = 1,

		.strong_intra_smoothing_enabled_flag = 0,

		.pcm_loop_filter_disabled_flag = 0,

		.intraAreaLeft = -1,
		.intraAreaRight = -1,
		.intraAreaTop = -1,
		.intraAreaBottom = -1,

		.gdrDuration = 0,

		.picSkip = 0,

		.sliceSize = 0,

		.enableCabac = 1,
		.cabacInitFlag = 0,
		.cirStart = 0,
		.cirInterval = 0,
		.enableDeblockOverride = 0,
		.deblockOverride = 0,

		.enableScalingList = 0,

		.compressor = 3,
		.sei = 0,
		.videoRange = 0,
		.bitDepthLuma = DEFAULT,
		.bitDepthChroma = DEFAULT,
		.blockRCSize = DEFAULT,
		.rcQpDeltaRange = DEFAULT,
		.rcBaseMBComplexity = DEFAULT,
		.picQpDeltaMin = DEFAULT,
		.picQpDeltaMax = DEFAULT,
		.ctbRcRowQpStep = DEFAULT,

		.gopSize = 1,
		.gopCfg = NULL,
		.gopLowdelay = 0,
		.longTermGap = 0,
		.longTermGapOffset = 0,
		.longTermQpDelta = 0,
		.ltrInterval = DEFAULT,

		.outReconFrame = 1,

		.roiMapDeltaQpBlockUnit = 0,
		.roiMapDeltaQpEnable = 1,
		.roiMapDeltaQpFile = NULL,
		.roiMapDeltaQpBinFile = NULL,
		.roiMapInfoBinFile        = NULL,
		.RoimapCuCtrlInfoBinFile  = NULL,
		.RoimapCuCtrlIndexBinFile = NULL,
		.RoiCuCtrlVer  = 0,
		.RoiQpDeltaVer = 1,
		.ipcmMapFile = NULL,
		.roi_ctrl[0].roiQp = DEFAULT,
		.roi_ctrl[1].roiQp = DEFAULT,
		.roi_ctrl[2].roiQp = DEFAULT,
		.roi_ctrl[3].roiQp = DEFAULT,
		.roi_ctrl[4].roiQp = DEFAULT,
		.roi_ctrl[5].roiQp = DEFAULT,
		.roi_ctrl[6].roiQp = DEFAULT,
		.roi_ctrl[7].roiQp = DEFAULT,

		.interlacedFrame = 0,

		/*stride*/
		.exp_of_input_alignment = 4,
		.exp_of_ref_alignment = 0,
		.exp_of_ref_ch_alignment = 0,


		.enableOutputCuInfo = 0,

		.rdoLevel = 3,
		.hashtype = 0,
		.verbose = 0,

		/* constant chroma control */
		.constChromaEn = 0,
		.constCb = DEFAULT,
		.constCr = DEFAULT,

		.tiles_enabled_flag = 0,
		.num_tile_columns = 1,
		.num_tile_rows  = 1,
		.loop_filter_across_tiles_enabled_flag = 1,

		.skip_frame_enabled_flag = 0,
		.skip_frame_poc = 0,

		.picOrderCntType = 0,
		.log2MaxPicOrderCntLsb = 16,
		.log2MaxFrameNum = 12,

		.RpsInSliceHeader = 0,
		.vui_timing_info_enable = 1,
		.halfDsInput = NULL,

		/* skip mode */
		.skipMapEnable = 0,
		.skipMapFile = NULL,
		.skipMapBlockUnit = 0,

		/* Frame-level core parallelism option */


		/*dump register*/
		.dumpRegister = 0,

		.rasterscan = 0,
		.cuInfoVersion = -1,

	#ifdef RECON_REF_1KB_BURST_RW
		.exp_of_input_alignment = 10,
		.exp_of_ref_alignment = 10,
		.exp_of_ref_ch_alignment = 10,
		.compressor = 2,
	#endif
	#ifdef RECON_REF_ALIGN64
		.exp_of_ref_alignment = 6,
		.exp_of_ref_ch_alignment = 6,
	#endif

		.enableRdoQuant = DEFAULT,

		/*CRF constant*/
		.crf = -1,

		/* AXI alignment */
		.AXIAlignment = 0,

		/*Ivf support*/
		.ivf = 1,

		/*PSY factor*/
		.PsyFactor = 0,
		.codedChromaIdc = VCENC_CHROMA_IDC_420,
		.aq_mode = 0,
		.aq_strength = 1.0,

		.preset = DEFAULT,

		.writeReconToDDR = 1,

		.qLevel = 1,
		.restartInterval = 0,

		//.frameType = 0,
		.colorConversion = 0,
		.partialCoding = 0,
		.codingMode = 0,
		.markerType = 0,
		.unitsType = 0,
		.xdensity = 1,
		.ydensity = 1,

		.hashtype = 0,
//		.mirror = 0,
		.constChromaEn = 0,
		.constCb = 0x80,
		.constCr = 0x80,

		.rcMode        = 1,
		.picQpDeltaMin = -2,
		.picQpDeltaMax = 3,
		.qpmin = 0,
		.qpmax = 51,
		.fixedQP = -1,
		.exp_of_input_alignment = 4,


	// AmebaPro2 add
		.out_buf_size		= 2*1024*1024,
		.out_rsvd_size		= 512*1024,
		.isp_buf_num		= 2,

		.ch					= 0,
		.EncMode			= 3,
		.JpegMode			= 0,
		.YuvMode			= 0,
		.osd				= 0,
		.voe_dbg			= 0,
		.fcs				= 1,
		.osd_block_num		= 24,

};

SECTION_VIDEO_CMD1 volatile __attribute__ ((aligned (32))) commandLine_s cmd1
= {

		.CodecType			 = CODEC_H264,

		.firstPic			 = 0,
		.lastPic			 = 0,
		.inputRateNumer 	 = 30,				// -j
		.inputRateDenom 	 = 1,				//
		.outputRateNumer	 = 30,				// -f
		.outputRateDenom	 = 1,

		.width				 = 1280,
		.height 			 = 720,
		.lumWidthSrc		 = 1280,
		.lumHeightSrc		 = 720,
		.horOffsetSrc		 = DEFAULT,
		.verOffsetSrc		 = DEFAULT,
		.videoStab			 = DEFAULT,
		.rotation			 = 0,				// -r
		.inputFormat		 = 1,				// Modify default input format is NV12

		.intraPicRate		 = 30,				// -R
		// default HEVC
#if 0
		.outputFormat	  = VCENC_VIDEO_CODEC_HEVC,
		.max_cu_size	  = 64,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 2,							 //mfu =>0
		.tr_depth_inter   = 4,							// (.max_cu_size == 64) ? 4 : 3,

		.level			  = VCENC_HEVC_LEVEL_6,
		.profile		  = VCENC_HEVC_MAIN_PROFILE,	// default is HEVC MAIN profile
#else
		.outputFormat	  = VCENC_VIDEO_CODEC_H264,
		.max_cu_size	  = 16,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 1,
		.tr_depth_inter   = 2,
		.level			  = VCENC_H264_LEVEL_5_1,
		.profile		  = VCENC_H264_HIGH_PROFILE,	// default is HEVC HIGH profile

#endif
		.tier			  = VCENC_HEVC_MAIN_TIER,


		.bitPerSecond = 1024000,						// -B
		.bitVarRangeI = 10000,
		.bitVarRangeP = 10000,
		.tolMovingBitRate = 2000,
		.monitorFrames = DEFAULT,
		.tolCtbRcInter = DEFAULT,
		.tolCtbRcIntra = DEFAULT,
		.u32StaticSceneIbitPercent = 80,
		.intraQpDelta = DEFAULT,

		.disableDeblocking = 0,

		.tc_Offset = -2,
		.beta_Offset = 5,

		.qpHdr = DEFAULT,
		.qpMin = DEFAULT,
		.qpMax = DEFAULT,
		.qpMinI = DEFAULT,
		.qpMaxI = DEFAULT,
		.picRc = 1,
		.ctbRc = 0, //CTB_RC
		.cpbSize = 1000000,
		.bitrateWindow = DEFAULT,
		.fixedIntraQp = 0,
		.hrdConformance = 0,
		.smoothPsnrInGOP = 0,
		.vbr = 0,

		.byteStream = VCENC_BYTE_STREAM,		// cml->byteStream = (cml->byteStream) ? VCENC_BYTE_STREAM : VCENC_NAL_UNIT_STREAM;

		.chromaQpOffset = 0,

		.enableSao = 1,

		.strong_intra_smoothing_enabled_flag = 0,

		.pcm_loop_filter_disabled_flag = 0,

		.intraAreaLeft = -1,
		.intraAreaRight = -1,
		.intraAreaTop = -1,
		.intraAreaBottom = -1,
		.gdrDuration = 0,

		.picSkip = 0,

		.sliceSize = 0,

		.enableCabac = 1,
		.cabacInitFlag = 0,
		.cirStart = 0,
		.cirInterval = 0,
		.enableDeblockOverride = 0,
		.deblockOverride = 0,

		.enableScalingList = 0,

		.compressor = 3,
		.sei = 0,
		.videoRange = 0,
		.bitDepthLuma = DEFAULT,
		.bitDepthChroma = DEFAULT,
		.blockRCSize = DEFAULT,
		.rcQpDeltaRange = DEFAULT,
		.rcBaseMBComplexity = DEFAULT,
		.picQpDeltaMin = DEFAULT,
		.picQpDeltaMax = DEFAULT,
		.ctbRcRowQpStep = DEFAULT,

		.gopSize = 1,
		.gopCfg = NULL,
		.gopLowdelay = 0,
		.longTermGap = 0,
		.longTermGapOffset = 0,
		.longTermQpDelta = 0,
		.ltrInterval = DEFAULT,

		.outReconFrame = 1,

		.roiMapDeltaQpBlockUnit = 0,
		.roiMapDeltaQpEnable = 1,
		.roiMapDeltaQpFile = NULL,
		.roiMapDeltaQpBinFile = NULL,
		.roiMapInfoBinFile		  = NULL,
		.RoimapCuCtrlInfoBinFile  = NULL,
		.RoimapCuCtrlIndexBinFile = NULL,
		.RoiCuCtrlVer  = 0,
		.RoiQpDeltaVer = 1,
		.ipcmMapFile = NULL,
		.roi_ctrl[0].roiQp = DEFAULT,
		.roi_ctrl[1].roiQp = DEFAULT,
		.roi_ctrl[2].roiQp = DEFAULT,
		.roi_ctrl[3].roiQp = DEFAULT,
		.roi_ctrl[4].roiQp = DEFAULT,
		.roi_ctrl[5].roiQp = DEFAULT,
		.roi_ctrl[6].roiQp = DEFAULT,
		.roi_ctrl[7].roiQp = DEFAULT,

		.interlacedFrame = 0,

		/*stride*/
		.exp_of_input_alignment = 4,
		.exp_of_ref_alignment = 0,
		.exp_of_ref_ch_alignment = 0,


		.enableOutputCuInfo = 0,

		.rdoLevel = 3,
		.hashtype = 0,
		.verbose = 0,

		/* constant chroma control */
		.constChromaEn = 0,
		.constCb = DEFAULT,
		.constCr = DEFAULT,

		.tiles_enabled_flag = 0,
		.num_tile_columns = 1,
		.num_tile_rows	= 1,
		.loop_filter_across_tiles_enabled_flag = 1,

		.skip_frame_enabled_flag = 0,
		.skip_frame_poc = 0,

		.picOrderCntType = 0,
		.log2MaxPicOrderCntLsb = 16,
		.log2MaxFrameNum = 12,

		.RpsInSliceHeader = 0,
		.vui_timing_info_enable = 1,
		.halfDsInput = NULL,

		/* skip mode */
		.skipMapEnable = 0,
		.skipMapFile = NULL,
		.skipMapBlockUnit = 0,

		/* Frame-level core parallelism option */


		/*dump register*/
		.dumpRegister = 0,

		.rasterscan = 0,
		.cuInfoVersion = -1,

#ifdef RECON_REF_1KB_BURST_RW
		.exp_of_input_alignment = 10,
		.exp_of_ref_alignment = 10,
		.exp_of_ref_ch_alignment = 10,
		.compressor = 2,
#endif
#ifdef RECON_REF_ALIGN64
		.exp_of_ref_alignment = 6,
		.exp_of_ref_ch_alignment = 6,
#endif

		.enableRdoQuant = DEFAULT,

		/*CRF constant*/
		.crf = -1,

		/* AXI alignment */
		.AXIAlignment = 0,

		/*Ivf support*/
		.ivf = 1,

		/*PSY factor*/
		.PsyFactor = 0,
		.codedChromaIdc = VCENC_CHROMA_IDC_420,
		.aq_mode = 0,
		.aq_strength = 1.0,

		.preset = DEFAULT,

		.writeReconToDDR = 1,

		.qLevel = 1,
		.restartInterval = 0,

		//.frameType = 0,
		.colorConversion = 0,
		.partialCoding = 0,
		.codingMode = 0,
		.markerType = 0,
		.unitsType = 0,
		.xdensity = 1,
		.ydensity = 1,

		.hashtype = 0,
//		.mirror = 0,
		.constChromaEn = 0,
		.constCb = 0x80,
		.constCr = 0x80,

		.rcMode 	   = 1,
		.picQpDeltaMin = -2,
		.picQpDeltaMax = 3,
		.qpmin = 0,
		.qpmax = 51,
		.fixedQP = -1,
		.exp_of_input_alignment = 4,


	// AmebaPro2 add
		.out_buf_size		= 2*1024*1024,
		.out_rsvd_size		= 512*1024,
		.isp_buf_num		= 2,

		.ch 				= 1,
		.EncMode			= 3,
		.JpegMode			= 0,
		.YuvMode			= 0,
		.osd				= 0,
		.voe_dbg			= 0,
		.fcs				= 0,
		.osd_block_num		= 24,
};

SECTION_VIDEO_CMD2 volatile __attribute__ ((aligned (32))) commandLine_s cmd2
= {

		.CodecType			 = CODEC_NV12,

		.firstPic			 = 0,
		.lastPic			 = 0,
		.inputRateNumer 	 = 30,				// -j
		.inputRateDenom 	 = 1,				//
		.outputRateNumer	 = 30,				// -f
		.outputRateDenom	 = 1,

		.width				 = 640,
		.height 			 = 360,
		.lumWidthSrc		 = 640,
		.lumHeightSrc		 = 360,
		.horOffsetSrc		 = DEFAULT,
		.verOffsetSrc		 = DEFAULT,
		.videoStab			 = DEFAULT,
		.rotation			 = 0,				// -r
		.inputFormat		 = 1,				// Modify default input format is NV12

		.intraPicRate		 = 30,				// -R
		// default HEVC
#if 0
		.outputFormat	  = VCENC_VIDEO_CODEC_HEVC,
		.max_cu_size	  = 64,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 2,							 //mfu =>0
		.tr_depth_inter   = 4,							// (.max_cu_size == 64) ? 4 : 3,

		.level			  = VCENC_HEVC_LEVEL_6,
		.profile		  = VCENC_HEVC_MAIN_PROFILE,	// default is HEVC MAIN profile
#else
		.outputFormat	  = VCENC_VIDEO_CODEC_NV12,
		.max_cu_size	  = 16,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 1,
		.tr_depth_inter   = 2,
		.level			  = VCENC_H264_LEVEL_5_1,
		.profile		  = VCENC_H264_HIGH_PROFILE,	// default is HEVC HIGH profile

#endif
		.tier			  = VCENC_HEVC_MAIN_TIER,


		.bitPerSecond = 1024000,						// -B
		.bitVarRangeI = 10000,
		.bitVarRangeP = 10000,
		.tolMovingBitRate = 2000,
		.monitorFrames = DEFAULT,
		.tolCtbRcInter = DEFAULT,
		.tolCtbRcIntra = DEFAULT,
		.u32StaticSceneIbitPercent = 80,
		.intraQpDelta = DEFAULT,

		.disableDeblocking = 0,

		.tc_Offset = -2,
		.beta_Offset = 5,

		.qpHdr = DEFAULT,
		.qpMin = DEFAULT,
		.qpMax = DEFAULT,
		.qpMinI = DEFAULT,
		.qpMaxI = DEFAULT,
		.picRc = 1,
		.ctbRc = 0, //CTB_RC
		.cpbSize = 1000000,
		.bitrateWindow = DEFAULT,
		.fixedIntraQp = 0,
		.hrdConformance = 0,
		.smoothPsnrInGOP = 0,
		.vbr = 0,

		.byteStream = VCENC_BYTE_STREAM,		// cml->byteStream = (cml->byteStream) ? VCENC_BYTE_STREAM : VCENC_NAL_UNIT_STREAM;

		.chromaQpOffset = 0,

		.enableSao = 1,

		.strong_intra_smoothing_enabled_flag = 0,

		.pcm_loop_filter_disabled_flag = 0,

		.intraAreaLeft = -1,
		.intraAreaRight = -1,
		.intraAreaTop = -1,
		.intraAreaBottom = -1,
		.gdrDuration = 0,

		.picSkip = 0,

		.sliceSize = 0,

		.enableCabac = 1,
		.cabacInitFlag = 0,
		.cirStart = 0,
		.cirInterval = 0,
		.enableDeblockOverride = 0,
		.deblockOverride = 0,

		.enableScalingList = 0,

		.compressor = 0,
		.sei = 0,
		.videoRange = 0,
		.bitDepthLuma = DEFAULT,
		.bitDepthChroma = DEFAULT,
		.blockRCSize = DEFAULT,
		.rcQpDeltaRange = DEFAULT,
		.rcBaseMBComplexity = DEFAULT,
		.picQpDeltaMin = DEFAULT,
		.picQpDeltaMax = DEFAULT,
		.ctbRcRowQpStep = DEFAULT,

		.gopSize = 1,
		.gopCfg = NULL,
		.gopLowdelay = 0,
		.longTermGap = 0,
		.longTermGapOffset = 0,
		.longTermQpDelta = 0,
		.ltrInterval = DEFAULT,

		.outReconFrame = 1,

		.roiMapDeltaQpBlockUnit = 0,
		.roiMapDeltaQpEnable = 1,
		.roiMapDeltaQpFile = NULL,
		.roiMapDeltaQpBinFile = NULL,
		.roiMapInfoBinFile		  = NULL,
		.RoimapCuCtrlInfoBinFile  = NULL,
		.RoimapCuCtrlIndexBinFile = NULL,
		.RoiCuCtrlVer  = 0,
		.RoiQpDeltaVer = 1,
		.ipcmMapFile = NULL,
		.roi_ctrl[0].roiQp = DEFAULT,
		.roi_ctrl[1].roiQp = DEFAULT,
		.roi_ctrl[2].roiQp = DEFAULT,
		.roi_ctrl[3].roiQp = DEFAULT,
		.roi_ctrl[4].roiQp = DEFAULT,
		.roi_ctrl[5].roiQp = DEFAULT,
		.roi_ctrl[6].roiQp = DEFAULT,
		.roi_ctrl[7].roiQp = DEFAULT,

		.interlacedFrame = 0,

		/*stride*/
		.exp_of_input_alignment = 4,
		.exp_of_ref_alignment = 0,
		.exp_of_ref_ch_alignment = 0,


		.enableOutputCuInfo = 0,

		.rdoLevel = 3,
		.hashtype = 0,
		.verbose = 0,

		/* constant chroma control */
		.constChromaEn = 0,
		.constCb = DEFAULT,
		.constCr = DEFAULT,

		.tiles_enabled_flag = 0,
		.num_tile_columns = 1,
		.num_tile_rows	= 1,
		.loop_filter_across_tiles_enabled_flag = 1,

		.skip_frame_enabled_flag = 0,
		.skip_frame_poc = 0,

		.picOrderCntType = 0,
		.log2MaxPicOrderCntLsb = 16,
		.log2MaxFrameNum = 12,

		.RpsInSliceHeader = 0,
		.vui_timing_info_enable = 1,
		.halfDsInput = NULL,

		/* skip mode */
		.skipMapEnable = 0,
		.skipMapFile = NULL,
		.skipMapBlockUnit = 0,

		/* Frame-level core parallelism option */


		/*dump register*/
		.dumpRegister = 0,

		.rasterscan = 0,
		.cuInfoVersion = -1,

#ifdef RECON_REF_1KB_BURST_RW
		.exp_of_input_alignment = 10,
		.exp_of_ref_alignment = 10,
		.exp_of_ref_ch_alignment = 10,
		.compressor = 2,
#endif
#ifdef RECON_REF_ALIGN64
		.exp_of_ref_alignment = 6,
		.exp_of_ref_ch_alignment = 6,
#endif

		.enableRdoQuant = DEFAULT,

		/*CRF constant*/
		.crf = -1,

		/* AXI alignment */
		.AXIAlignment = 0,

		/*Ivf support*/
		.ivf = 1,

		/*PSY factor*/
		.PsyFactor = 0,
		.codedChromaIdc = VCENC_CHROMA_IDC_420,
		.aq_mode = 0,
		.aq_strength = 1.0,

		.preset = DEFAULT,

		.writeReconToDDR = 1,

		.qLevel = 1,
		.restartInterval = 0,

		//.frameType = 0,
		.colorConversion = 0,
		.partialCoding = 0,
		.codingMode = 0,
		.markerType = 0,
		.unitsType = 0,
		.xdensity = 1,
		.ydensity = 1,

		.hashtype = 0,
//		.mirror = 0,
		.constChromaEn = 0,
		.constCb = 0x80,
		.constCr = 0x80,

		.rcMode 	   = 1,
		.picQpDeltaMin = -2,
		.picQpDeltaMax = 3,
		.qpmin = 0,
		.qpmax = 51,
		.fixedQP = -1,
		.exp_of_input_alignment = 4,


	// AmebaPro2 add
		.out_buf_size		= 2*1024*1024,
		.out_rsvd_size		= 512*1024,
		.isp_buf_num		= 2,

		.ch 				= 2,
		.EncMode			= 0,
		.JpegMode			= 0,
		.YuvMode			= 3,
		.osd				= 0,
		.voe_dbg			= 0,
		.fcs				= 0,
		.osd_block_num		= 24,

};


SECTION_VIDEO_CMD3 volatile __attribute__ ((aligned (32))) commandLine_s cmd3
= {
		.CodecType			 = CODEC_NV12,

		.firstPic			 = 0,
		.lastPic			 = 0,
		.inputRateNumer 	 = 30,				// -j
		.inputRateDenom 	 = 1,				//
		.outputRateNumer	 = 30,				// -f
		.outputRateDenom	 = 1,

		.width				 = 640,
		.height 			 = 360,
		.lumWidthSrc		 = 640,
		.lumHeightSrc		 = 360,
		.horOffsetSrc		 = DEFAULT,
		.verOffsetSrc		 = DEFAULT,
		.videoStab			 = DEFAULT,
		.rotation			 = 0,				// -r
		.inputFormat		 = 1,				// Modify default input format is NV12

		.intraPicRate		 = 30,				// -R
			// default HEVC

		.outputFormat	  = VCENC_VIDEO_CODEC_NV12,
		.max_cu_size	  = 16,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 1,
		.tr_depth_inter   = 2,
		.level			  = VCENC_H264_LEVEL_5_1,
		.profile		  = VCENC_H264_HIGH_PROFILE,	// default is HEVC HIGH profile

		.tier			  = VCENC_HEVC_MAIN_TIER,


		.bitPerSecond = 1024000,						// -B
		.bitVarRangeI = 10000,
		.bitVarRangeP = 10000,
		.tolMovingBitRate = 2000,
		.monitorFrames = DEFAULT,
		.tolCtbRcInter = DEFAULT,
		.tolCtbRcIntra = DEFAULT,
		.u32StaticSceneIbitPercent = 80,
		.intraQpDelta = DEFAULT,

		.disableDeblocking = 0,

		.tc_Offset = -2,
		.beta_Offset = 5,
	
		.qpHdr = DEFAULT,
		.qpMin = DEFAULT,
		.qpMax = DEFAULT,
		.qpMinI = DEFAULT,
		.qpMaxI = DEFAULT,
		.picRc = 1,
		.ctbRc = 0, //CTB_RC
		.cpbSize = 1000000,
		.bitrateWindow = DEFAULT,
		.fixedIntraQp = 0,
		.hrdConformance = 0,
		.smoothPsnrInGOP = 0,
		.vbr = 0,

		.byteStream = VCENC_BYTE_STREAM,		// cml->byteStream = (cml->byteStream) ? VCENC_BYTE_STREAM : VCENC_NAL_UNIT_STREAM;

		.chromaQpOffset = 0,

		.enableSao = 1,

		.strong_intra_smoothing_enabled_flag = 0,

		.pcm_loop_filter_disabled_flag = 0,

		.intraAreaLeft = -1,
		.intraAreaRight = -1,
		.intraAreaTop = -1,
		.intraAreaBottom = -1,

		.gdrDuration = 0,

		.picSkip = 0,

		.sliceSize = 0,

		.enableCabac = 1,
		.cabacInitFlag = 0,
		.cirStart = 0,
		.cirInterval = 0,
		.enableDeblockOverride = 0,
		.deblockOverride = 0,

		.enableScalingList = 0,

		.compressor = 0,
		.sei = 0,
		.videoRange = 0,
		.bitDepthLuma = DEFAULT,
		.bitDepthChroma = DEFAULT,
		.blockRCSize = DEFAULT,
		.rcQpDeltaRange = DEFAULT,
		.rcBaseMBComplexity = DEFAULT,
		.picQpDeltaMin = DEFAULT,
		.picQpDeltaMax = DEFAULT,
		.ctbRcRowQpStep = DEFAULT,

		.gopSize = 1,
		.gopCfg = NULL,
		.gopLowdelay = 0,
		.longTermGap = 0,
		.longTermGapOffset = 0,
		.longTermQpDelta = 0,
		.ltrInterval = DEFAULT,

		.outReconFrame = 1,

		.roiMapDeltaQpBlockUnit = 0,
		.roiMapDeltaQpEnable = 1,
		.roiMapDeltaQpFile = NULL,
		.roiMapDeltaQpBinFile = NULL,
		.roiMapInfoBinFile		  = NULL,
		.RoimapCuCtrlInfoBinFile  = NULL,
		.RoimapCuCtrlIndexBinFile = NULL,
		.RoiCuCtrlVer  = 0,
		.RoiQpDeltaVer = 1,
		.ipcmMapFile = NULL,
		.roi_ctrl[0].roiQp = DEFAULT,
		.roi_ctrl[1].roiQp = DEFAULT,
		.roi_ctrl[2].roiQp = DEFAULT,
		.roi_ctrl[3].roiQp = DEFAULT,
		.roi_ctrl[4].roiQp = DEFAULT,
		.roi_ctrl[5].roiQp = DEFAULT,
		.roi_ctrl[6].roiQp = DEFAULT,
		.roi_ctrl[7].roiQp = DEFAULT,

		.interlacedFrame = 0,

		/*stride*/
		.exp_of_input_alignment = 4,
		.exp_of_ref_alignment = 0,
		.exp_of_ref_ch_alignment = 0,


		.enableOutputCuInfo = 0,

		.rdoLevel = 3,
		.hashtype = 0,
		.verbose = 0,

		/* constant chroma control */
		.constChromaEn = 0,
		.constCb = DEFAULT,
		.constCr = DEFAULT,

		.tiles_enabled_flag = 0,
		.num_tile_columns = 1,
		.num_tile_rows	= 1,
		.loop_filter_across_tiles_enabled_flag = 1,

		.skip_frame_enabled_flag = 0,
		.skip_frame_poc = 0,

		.picOrderCntType = 0,
		.log2MaxPicOrderCntLsb = 16,
		.log2MaxFrameNum = 12,

		.RpsInSliceHeader = 0,
		.vui_timing_info_enable = 1,
		.halfDsInput = NULL,

		/* skip mode */
		.skipMapEnable = 0,
		.skipMapFile = NULL,
		.skipMapBlockUnit = 0,

		/* Frame-level core parallelism option */


		/*dump register*/
		.dumpRegister = 0,

		.rasterscan = 0,
		.cuInfoVersion = -1,

#ifdef RECON_REF_1KB_BURST_RW
		.exp_of_input_alignment = 10,
		.exp_of_ref_alignment = 10,
		.exp_of_ref_ch_alignment = 10,
		.compressor = 2,
#endif
#ifdef RECON_REF_ALIGN64
		.exp_of_ref_alignment = 6,
		.exp_of_ref_ch_alignment = 6,
#endif

		.enableRdoQuant = DEFAULT,

		/*CRF constant*/
		.crf = -1,

		/* AXI alignment */
		.AXIAlignment = 0,

		/*Ivf support*/
		.ivf = 1,

		/*PSY factor*/
		.PsyFactor = 0,
		.codedChromaIdc = VCENC_CHROMA_IDC_420,
		.aq_mode = 0,
		.aq_strength = 1.0,

		.preset = DEFAULT,

		.writeReconToDDR = 1,

		.qLevel = 1,
		.restartInterval = 0,

		//.frameType = 0,
		.colorConversion = 0,
		.partialCoding = 0,
		.codingMode = 0,
		.markerType = 0,
		.unitsType = 0,
		.xdensity = 1,
		.ydensity = 1,

		.hashtype = 0,
//		.mirror = 0,
		.constChromaEn = 0,
		.constCb = 0x80,
		.constCr = 0x80,

		.rcMode 	   = 1,
		.picQpDeltaMin = -2,
		.picQpDeltaMax = 3,
		.qpmin = 0,
		.qpmax = 51,
		.fixedQP = -1,
		.exp_of_input_alignment = 4,


	// AmebaPro2 add
		.out_buf_size		= 2*1024*1024,
		.out_rsvd_size		= 512*1024,
		.isp_buf_num		= 2,

		.ch 				= 3,
		.EncMode			= 0,
		.JpegMode			= 0,
		.YuvMode			= 3,
		.osd				= 0,
		.voe_dbg			= 0,
		.fcs				= 0,
		.osd_block_num		= 24,

};

SECTION_VIDEO_CMD4 volatile __attribute__ ((aligned (32))) commandLine_s cmd4
= {
		.CodecType			 = CODEC_RGB,

		.firstPic			 = 0,
		.lastPic			 = 0,
		.inputRateNumer 	 = 30,				// -j
		.inputRateDenom 	 = 1,				//
		.outputRateNumer	 = 30,				// -f
		.outputRateDenom	 = 1,

		.width				 = 320,
		.height 			 = 180,
		.lumWidthSrc		 = 320,
		.lumHeightSrc		 = 180,
		.horOffsetSrc		 = DEFAULT,
		.verOffsetSrc		 = DEFAULT,
		.videoStab			 = DEFAULT,
		.rotation			 = 0,				// -r
		.inputFormat		 = 1,				// Modify default input format is NV12

		.intraPicRate		 = 30,				// -R
			// default HEVC

		.outputFormat	  = VCENC_VIDEO_CODEC_RGB,
		.max_cu_size	  = 16,
		.min_cu_size	  = 8,
		.max_tr_size	  = 16,
		.min_tr_size	  = 4,
		.tr_depth_intra   = 1,
		.tr_depth_inter   = 2,
		.level			  = VCENC_H264_LEVEL_5_1,
		.profile		  = VCENC_H264_HIGH_PROFILE,	// default is HEVC HIGH profile

		.tier			  = VCENC_HEVC_MAIN_TIER,


		.bitPerSecond = 1024000,						// -B
		.bitVarRangeI = 10000,
		.bitVarRangeP = 10000,
		.tolMovingBitRate = 2000,
		.monitorFrames = DEFAULT,
		.tolCtbRcInter = DEFAULT,
		.tolCtbRcIntra = DEFAULT,
		.u32StaticSceneIbitPercent = 80,
		.intraQpDelta = DEFAULT,

		.disableDeblocking = 0,

		.tc_Offset = -2,
		.beta_Offset = 5,
	
		.qpHdr = DEFAULT,
		.qpMin = DEFAULT,
		.qpMax = DEFAULT,
		.qpMinI = DEFAULT,
		.qpMaxI = DEFAULT,
		.picRc = 1,
		.ctbRc = 0, //CTB_RC
		.cpbSize = 1000000,
		.bitrateWindow = DEFAULT,
		.fixedIntraQp = 0,
		.hrdConformance = 0,
		.smoothPsnrInGOP = 0,
		.vbr = 0,

		.byteStream = VCENC_BYTE_STREAM,		// cml->byteStream = (cml->byteStream) ? VCENC_BYTE_STREAM : VCENC_NAL_UNIT_STREAM;

		.chromaQpOffset = 0,

		.enableSao = 1,
	
		.strong_intra_smoothing_enabled_flag = 0,

		.pcm_loop_filter_disabled_flag = 0,

		.intraAreaLeft = -1,
		.intraAreaRight = -1,
		.intraAreaTop = -1,
		.intraAreaBottom = -1,

		.gdrDuration = 0,

		.picSkip = 0,

		.sliceSize = 0,

		.enableCabac = 1,
		.cabacInitFlag = 0,
		.cirStart = 0,
		.cirInterval = 0,
		.enableDeblockOverride = 0,
		.deblockOverride = 0,

		.enableScalingList = 0,

		.compressor = 0,
		.sei = 0,
		.videoRange = 0,
		.bitDepthLuma = DEFAULT,
		.bitDepthChroma = DEFAULT,
		.blockRCSize = DEFAULT,
		.rcQpDeltaRange = DEFAULT,
		.rcBaseMBComplexity = DEFAULT,
		.picQpDeltaMin = DEFAULT,
		.picQpDeltaMax = DEFAULT,
		.ctbRcRowQpStep = DEFAULT,

		.gopSize = 1,
		.gopCfg = NULL,
		.gopLowdelay = 0,
		.longTermGap = 0,
		.longTermGapOffset = 0,
		.longTermQpDelta = 0,
		.ltrInterval = DEFAULT,

		.outReconFrame = 1,

		.roiMapDeltaQpBlockUnit = 0,
		.roiMapDeltaQpEnable = 1,
		.roiMapDeltaQpFile = NULL,
		.roiMapDeltaQpBinFile = NULL,
		.roiMapInfoBinFile		  = NULL,
		.RoimapCuCtrlInfoBinFile  = NULL,
		.RoimapCuCtrlIndexBinFile = NULL,
		.RoiCuCtrlVer  = 0,
		.RoiQpDeltaVer = 1,
		.ipcmMapFile = NULL,
		.roi_ctrl[0].roiQp = DEFAULT,
		.roi_ctrl[1].roiQp = DEFAULT,
		.roi_ctrl[2].roiQp = DEFAULT,
		.roi_ctrl[3].roiQp = DEFAULT,
		.roi_ctrl[4].roiQp = DEFAULT,
		.roi_ctrl[5].roiQp = DEFAULT,
		.roi_ctrl[6].roiQp = DEFAULT,
		.roi_ctrl[7].roiQp = DEFAULT,

		.interlacedFrame = 0,

		/*stride*/
		.exp_of_input_alignment = 4,
		.exp_of_ref_alignment = 0,
		.exp_of_ref_ch_alignment = 0,


		.enableOutputCuInfo = 0,

		.rdoLevel = 3,
		.hashtype = 0,
		.verbose = 0,

		/* constant chroma control */
		.constChromaEn = 0,
		.constCb = DEFAULT,
		.constCr = DEFAULT,

		.tiles_enabled_flag = 0,
		.num_tile_columns = 1,
		.num_tile_rows	= 1,
		.loop_filter_across_tiles_enabled_flag = 1,

		.skip_frame_enabled_flag = 0,
		.skip_frame_poc = 0,

		.picOrderCntType = 0,
		.log2MaxPicOrderCntLsb = 16,
		.log2MaxFrameNum = 12,

		.RpsInSliceHeader = 0,
		.vui_timing_info_enable = 1,
		.halfDsInput = NULL,

		/* skip mode */
		.skipMapEnable = 0,
		.skipMapFile = NULL,
		.skipMapBlockUnit = 0,

		/* Frame-level core parallelism option */


		/*dump register*/
		.dumpRegister = 0,

		.rasterscan = 0,
		.cuInfoVersion = -1,

#ifdef RECON_REF_1KB_BURST_RW
		.exp_of_input_alignment = 10,
		.exp_of_ref_alignment = 10,
		.exp_of_ref_ch_alignment = 10,
		.compressor = 2,
#endif
#ifdef RECON_REF_ALIGN64
		.exp_of_ref_alignment = 6,
		.exp_of_ref_ch_alignment = 6,
#endif

		.enableRdoQuant = DEFAULT,

		/*CRF constant*/
		.crf = -1,

		/* AXI alignment */
		.AXIAlignment = 0,

		/*Ivf support*/
		.ivf = 1,

		/*PSY factor*/
		.PsyFactor = 0,
		.codedChromaIdc = VCENC_CHROMA_IDC_420,
		.aq_mode = 0,
		.aq_strength = 1.0,

		.preset = DEFAULT,

		.writeReconToDDR = 1,

		.qLevel = 1,
		.restartInterval = 0,

		//.frameType = 0,
		.colorConversion = 0,
		.partialCoding = 0,
		.codingMode = 0,
		.markerType = 0,
		.unitsType = 0,
		.xdensity = 1,
		.ydensity = 1,

		.hashtype = 0,
//		.mirror = 0,
		.constChromaEn = 0,
		.constCb = 0x80,
		.constCr = 0x80,

		.rcMode 	   = 1,
		.picQpDeltaMin = -2,
		.picQpDeltaMax = 3,
		.qpmin = 0,
		.qpmax = 51,
		.fixedQP = -1,
		.exp_of_input_alignment = 4,


	// AmebaPro2 add
		.out_buf_size		= 2*1024*1024,
		.out_rsvd_size		= 512*1024,
		.isp_buf_num		= 2,

		.ch 				= 4,
		.EncMode			= 0,
		.JpegMode			= 0,
		.YuvMode			= 3,
		.osd				= 0,
		.voe_dbg			= 0,
		.fcs				= 0,
		.osd_block_num		= 0,
};



#endif // _VOE_DEF_H_
