


MEMORY
{
  ITCM_ROM   (rx)       : ORIGIN = 0x00000000, LENGTH = 0x400					/* 1KB	*/
  ITCM_RAM   (rwx)      : ORIGIN = 0x00040000, LENGTH = 0x10000  				/* 64KB */
  DTCM_ROM   (rx)       : ORIGIN = 0x20010000, LENGTH = 0x4000    				/* 16KB	*/
  DTCM_RAM   (rwx)      : ORIGIN = 0x20000000, LENGTH = 0xFF00					/* 63KB	*/
  ROM_RESV   (rwx)      : ORIGIN = 0x2000FF00, LENGTH = 0x100					/* 128B	*/   
  VOE_HEAD   (rwx)      : ORIGIN = 0x70000000, LENGTH = 0x70000040 - 0x70000000	/* 64B */  
  SENSOR     (rwx)      : ORIGIN = 0x70000040, LENGTH = 0x70008000 - 0x70000040	/* 32KB - 64B */  
  IQ         (rwx)      : ORIGIN = 0x70008000, LENGTH = 0x70035000 - 0x70008000	/* 180KB */
  IQ_CALI    (rwx)      : ORIGIN = 0x70035000, LENGTH = 0x7003A000 - 0x70035000	/* 20KB */    
  DDR_CMD    (rwx)      : ORIGIN = 0x7003A000, LENGTH = 0x7003C000 - 0x7003A000	/* 8KB   */
  DDR        (rwx)      : ORIGIN = 0x7003C000, LENGTH = 0x7009A000 - 0x7003C000	/* 376KB */
  DDR_2      (rwx)      : ORIGIN = 0x7009A000, LENGTH = 0x700E8000 - 0x7009A000	/* 312KB */
  BSS        (rwx)      : ORIGIN = 0x700E8000, LENGTH = 0x70100000 - 0x700E8000	/* 96KB  */
  
}


/* Library configurations */
/*GROUP(libgcc.a libc.a libm.a libnosys.a libsemihost.a)*/
GROUP(libgcc.a)

SECTIONS
{
	.itcm.rom :
	{ 
	} > ITCM_ROM 
	
	.dtcm.rom :
	{
	} > DTCM_ROM  
  
	/*.itcm.ram :*/
	.text :
	{
	/*	ITCM_ROM start, move because ROM not ready */	
		KEEP(*(.vector.rom))	
		KEEP(*startup*.o(.text.HAL_Init))
	
		KEEP(*(.itcm.ram))	
	
	} > ITCM_RAM
	
  	.tm_voe_share :
	{
		KEEP(*(.video_e2o.dtcm))	
		KEEP(*(.video_roi.dtcm))	
		KEEP(*(.video_md.dtcm))	
		KEEP(*(.video_debug.dtcm))			
		KEEP(*(.video_err.dtcm))			
		. = ALIGN(32);
	

	} > DTCM_RAM	
	
	
	
	.symbol.ddr2 :
	{
		/* System init non FCS symbol*/
		
		*voe_main.o(*notify_tm_message*)
		*voe_main.o(*recv_tm9_cmd*)
		*hal_voe_peri.o(*voe_wdt_enable*)
		*hal_voe_peri.o(*voe_wdt_refresh*)
		

		
		
	
				
		/* ISP init non FCS symbol*/

		*test_md2.o(*md2_set_ctrl*)
		*test_md2.o(*md2_get_attr*)
		*test_md2.o(*md2_init*)
		*rtsosd2cmd.o(*__osd2_get_val*)
		*rtsosd2cmd.o(*rts_osd2_set_cmd*)
	
	
		*pb_decode.o(*iter_from_extension*)
		*pb_decode.o(*pb_dec_fixed_length_bytes*)
		*pb_decode.o(*pb_dec_string*)
		*pb_decode.o(*pb_dec_bytes*)
		*pb_decode.o(*pb_skip_field*)
		*pb_decode.o(*pb_decode_fixed64*)
		*pb_decode.o(*pb_dec_fixed64*)

	
		*isp_msg_buf.o(*isp_msg_write*)
		*isp_msg_buf.o(*isp_msg_relocate*)

/*
		*isp_uds_client.o(*isp_uds_message_process*)
*/
		*rts_isp_utils.o(*rts_isp_read_sensor_reg*)
		*rts_isp_utils.o(*rts_isp_write_sensor_reg*)
		*rts_isp_utils.o(*rts_isp_get_image_size*)
		*rts_isp_utils.o(*rts_isp_get_bypass*)
		*rts_isp_utils.o(*rts_isp_set_bypass*)
	
	
		*rtsc_utils.o(*rtsc_rtsv_close*)
		*rtsc_utils.o(*rtsc_ctrl_open*)
		*rtsc_utils.o(*rtsc_ctrl_close*)
		*rtsc_utils.o(*rtsc_exec_vendor_cmd*)
	
		*rt_util.o(*rt_code_str*)
	
		*rts_camera_ctrl.o(*rtscam_query_ctrl*)
		*rts_camera_ctrl.o(*rtscam_ctrl_populate_cache*)
		*rts_camera_ctrl.o(*rtscam_video_release_ctrl*)
			
		*hal_isp.o(*isp_free_buffer*)
		*hal_isp.o(*isp_close_stream*)
		*hal_isp.o(*isp_release_frame_buffer*)
		*hal_isp.o(*hal_isp_get_ctrl*)
/*		
		*hal_isp.o(*hal_isp_set_ctrl*)
*/
		*hal_isp.o(*hal_isp_set_raw_fmt*)
		*hal_isp.o(*hal_isp_set_md2*)
		*hal_isp.o(*hal_isp_get_md2_result*)
		*hal_isp.o(*hal_isp_get_md2_attr*)
		*hal_isp.o(*hal_isp_release_md2*)
		*hal_isp.o(*hal_isp_update_fcs_status*)
		*hal_isp.o(*hal_isp_get_sensor_mode*)
		*hal_isp.o(*hal_isp_get_af_statis*)
		*hal_isp.o(*hal_isp_get_ae_statis*)
		*hal_isp.o(*hal_isp_get_awb_statis*)

		*isp_mod.o(*isp_mod_unregister*)
		*isp_mod.o(*isp_mod_cleanup*)
		*isp_mod.o(*isp_mod_hardware_cleanup*)


		*rtsc_regs.o(*__isp_reg_info*)
		*rtsc_regs.o(*__read_reg*)
		*rtsc_regs.o(*rtsc_reg_close*)
		*rtsc_regs.o(*rtsc_reg_read_reg*)
		*rtsc_regs.o(*rtsc_reg_write_reg*)
		*rtsc_regs.o(*rtsc_reg_osd2_close*)
		*rtsc_regs.o(*rtsc_reg_osd2_done*)

			
		*rts_camera.o(*find_frame*)
		*rts_camera.o(*rtscam_clr_format*)
/*
		*rts_isp.o(*process_i2c_regs*)
		*rts_isp.o(*rts_isp_read_i2c_regs*)
		*rts_isp.o(*rts_isp_write_i2c_regs*)
		*rts_isp.o(*rts_isp_read_i2c_reg*)
		*rts_isp.o(*rts_isp_write_i2c_reg*)
*/
		*isp_iq.o(*isp_iq_cleanup*)

		*isp_algo.o(*isp_algo_unregister*)
		*isp_algo.o(*isp_algo_unbind*)
		*isp_algo.o(*isp_algo_cleanup*)
		*isp_algo.o(*isp_algo_get_af*)

		*isp_core.o(*isp_core_release*)
		*isp_core.o(*isp_core_unregister_mod*)
		*isp_core.o(*isp_core_cleanup*)
		*isp_core.o(*isp_core_stop*)

		*isp_top.o(*isp_top_core_cleanup*)
		*isp_top.o(*isp_top_core_stop*)
		*isp_top.o(*isp_top_read_sensor_reg*)
		*isp_top.o(*isp_top_write_sensor_reg*)
		*isp_top.o(*isp_top_unbind_algo_unlock*)
		
		*isp_top.o(*isp_top_update_fcs_ready*)


		*isp_algo.o(*isp_algo_unregister*)
		*isp_algo.o(*isp_algo_unbind*)
		*isp_algo.o(*isp_algo_cleanup*)
		*isp_algo.o(*isp_algo_get_af*)

		*isp_utils.o(*calc_smooth*)
		
		*isp_notify.o(*isp_notify_cleanup*)
		*isp_notify.o(*isp_notify_del_mod*)
		
		*isp_video_ctrl.o(*std_log*)
		*isp_video_ctrl.o(*prepare_ext_ctrls*)
		*isp_video_ctrl.o(*new_to_user*)
		*isp_video_ctrl.o(*def_to_user*)
		*isp_video_ctrl.o(*try_set_ext_ctrls*)
		*isp_video_ctrl.o(*get_ctrl*)
		*isp_video_ctrl.o(*rtsv_ctrl_handler_free*)
		*isp_video_ctrl.o(*rtsv_ctrl_handler_backup_auto*)
		*isp_video_ctrl.o(*rtsv_query_ext_ctrl*)
		*isp_video_ctrl.o(*rtsv_queryctrl*)
		*isp_video_ctrl.o(*rtsv_querymenu*)
		*isp_video_ctrl.o(*rtsv_g_ext_ctrls*)
		*isp_video_ctrl.o(*rtsv_g_ctrl*)
		*isp_video_ctrl.o(*rtsv_ctrl_g_ctrl*)
		*isp_video_ctrl.o(*rtsv_try_ext_ctrls*)
		*isp_video_ctrl.o(*rtsv_s_ext_ctrls*)


		*rts_camera_fps.o(*rtscam_skip_frame*)
		*rts_camera_fps.o(*rtscam_exec_sensor_fps_setting*)
		*rts_camera_fps.o(*rtscam_change_dynamic_fps*)
		*rts_camera_fps.o(*rtscam_clr_frmival*)
		*rts_camera_fps.o(*rtscam_release_sensor_fps*)
		
		*rts_camera_soc_3915.o(*rtscam_socdev_release_3915*)
		*rts_camera_soc_3915.o(*rtscam_socdev_release_slot*)
		*rts_camera_soc_3915.o(*rtscam_socdev_process_frame*)
		*rts_camera_soc_3915.o(*rtscam_socdev_get_height_align*)
		
		*rts_camera_md.o(*md_enable_clk*)
		*rts_camera_md.o(*md_enable_interrupt*)
		*rts_camera_md.o(*md_enable*)
		*rts_camera_md.o(*md_set_icfg*)
		*rts_camera_md.o(*md_irq*)
		*rts_camera_md.o(*rtscam_isp_md_open*)
		*rts_camera_md.o(*rtscam_isp_md_close*)
		*rts_camera_md.o(*rtscam_isp_md_ioctl*)
		*rts_camera_md.o(*rtscam_isp_md_remove*)


		*rts_camera_verify.o(*rtscam_verify_init*)
		*rts_camera_verify.o(*rtscam_verify_reset_isp*)
		*rts_camera_verify.o(*rtscam_verify_set_info*)

		*rts_camera_zoom.o(*rtscam_zoom_on_event*)
		*rts_camera_zoom.o(*rtscam_zoom_subdev_set_ive_ctrl*)
		*rts_camera_zoom.o(*rtscam_zoom_subdev_get_ive_ctrl*)
		*rts_camera_zoom.o(*rtscam_zoom_subdev_set_vinfo*)
		*rts_camera_zoom.o(*rtscam_zoom_unregister_isp*)
		
		*rts_camera_soc.o(*rtscam_soc_start_clock*)
		*rts_camera_soc.o(*rtscam_soc_put_ctrl*)
		*rts_camera_soc.o(*rtscam_soc_query_ctrl*)
		*rts_camera_soc.o(*rtscam_soc_on_event*)
		*rts_camera_soc.o(*rtscam_soc_release_video_device*)
		*rts_camera_soc.o(*rtscam_soc_release*)
		*rts_camera_soc.o(*rtscam_soc_stop_clock*)
		*rts_camera_soc.o(*rtscam_soc_exec_vcmd*)
		*rts_camera_soc.o(*rtscam_soc_get_stream_reg_index*)
		*rts_camera_soc.o(*rtscam_soc_get_stream_from_reg_index*)
		*rts_camera_soc.o(*rtscam_soc_dec_drops*)
		*rts_camera_soc.o(*rtscam_soc_get_drops*)
		*rts_camera_soc.o(*rtscam_soc_inc_overflow*)
		*rts_camera_soc.o(*rtscam_soc_inc_frames*)
		*rts_camera_soc.o(*rtscam_soc_inc_skips*)
		*rts_camera_soc.o(*rtscam_soc_inc_errors*)
		*rts_camera_soc.o(*rtscam_soc_is_rgb*)
		*rts_camera_soc.o(*rtscam_soc_is_yonly*)
		*rts_camera_soc.o(*rtscam_soc_get_skip_info*)
		*rts_camera_soc.o(*rtscam_register_subdev_ext*)
/*
		*rts_camera_isp.o(*list_del*)
		*rts_camera_isp.o(*list_del_init*)
		
		*rts_camera_isp.o(*__rtscam_isp_sync_add_regs*)
		*rts_camera_isp.o(*rtscam_isp_sync_write*)
		

		*rts_camera_isp.o(*i2c_master_rxc_callback*)
		*rts_camera_isp.o(*rtscam_isp_sync_lock*)
*/		
		*rts_camera_isp.o(*rtscam_isp_aphy_i2c_write*)
		*rts_camera_isp.o(*rtscam_isp_put_statis*)
		*rts_camera_isp.o(*i2c_master_err_callback*)
		*rts_camera_isp.o(*rtscam_isp_wait_event*)
		*rts_camera_isp.o(*rtscam_isp_sync_clean_list*)
		*rts_camera_isp.o(*rtscam_isp_statis_cleanup*)
		*rts_camera_isp.o(*rtscam_isp_cleanup_statis*)
		*rts_camera_isp.o(*rtscam_isp_poll*)

		*rts_camera_isp.o(*rtscam_isp_notify_dyn_fps*)
		*rts_camera_isp.o(*rtscam_isp_unregister_subdev*)
		*rts_camera_isp.o(*rtscam_isp_set_power*)
		*rts_camera_isp.o(*rtscam_isp_test_preview*)
		*rts_camera_isp.o(*rtscam_isp_i2c_read*)
		*rts_camera_isp.o(*rtscam_isp_close*)	
		
		*clk-rts3915.o(*rlx_clk_is_enabled*)
		*clk-rts3915.o(*rlx_enable_clk*)
		*clk-rts3915.o(*rlx_disable_clk*)
		*clk-rts3915.o(*hclk_set_rate*)	
		
		*rts_rtsv.o(*valid_frmival_stepwise*)
		*rts_rtsv.o(*rts_rtsv_streamoff*)
		*rts_rtsv.o(*rts_rtsv_put_buffer*)
		*rts_rtsv.o(*stream_close*)
		*rts_rtsv.o(*release_frame_buffer*)
		
		*rts_ioctl.o(*rts_close*)		
		
		*rts_errno.o(*rts_strerrno*)
		
		
		
		/* isp_hw_* ae/af/dvp/global/intp/iq/mipi/tnr/uvtune/vinf/vreg/wdr/sensor/snr */		
		*isp_hw_af.o(*isp_hw_af_set_statis_th*)
		*isp_hw_dvp.o(*isp_hw_dvp_stop_transfer*)
		*isp_hw_dvp.o(*isp_hw_dvp_start_transfer*)
		*isp_hw_dvp.o(*isp_hw_dvp_get_ops*)
		*isp_hw_eeh.o(*isp_hw_eeh_est*)
/*		
		*isp_hw_global.o(*isp_hw_global_delay_data*)
*/		
		*isp_hw_global.o(*isp_hw_global_stop_transfer*)
		*isp_hw_intp.o(*isp_hw_intp_dyn*)
		*isp_hw_intp.o(*isp_hw_intp_est*)
		*isp_hw_iq.o(*isp_hw_iq_read_regs*)
		*isp_hw_iq.o(*isp_hw_iq_write_regs*)
		*isp_hw_mipi.o(*isp_hw_mipi_stop_transfer*)
		*isp_hw_tnr.o(*isp_hw_tnr_dyn*)
		*isp_hw_tnr.o(*isp_hw_tnr_est*)
		*isp_hw_uvtune.o(*isp_hw_uvtune_estimation*)
		*isp_hw_vinf.o(*isp_hw_vinf_start_transfer*)
		*isp_hw_vinf.o(*isp_hw_vinf_stop_transfer*)
		*isp_hw_vinf.o(*isp_hw_vinf_get_ops*)
		*isp_hw_vreg.o(*isp_read_vreg_float*)
		*isp_hw_wdr.o(*isp_hw_wdr_set_step*)
		*isp_hw_snr.o(*isp_hw_snr_est*)
		*isp_hw_snr.o(*isp_hw_snr_enable*)
		
		

		*isp_modules.o(*isp_unregister_all_modules*)

		/* isp_mod_* ae/af/awb */
		
		*isp_mod_ae.o(*mod_ae_info_exposure*)
		*isp_mod_ae.o(*mod_ae_info_status*)
		*isp_mod_ae.o(*mod_ae_info_version*)
		*isp_mod_ae.o(*mod_ae_info_target*)
		*isp_mod_ae.o(*mod_ae_exec_get_setting*)
		*isp_mod_ae.o(*isp_mod_ae_cleanup*)
		*isp_mod_ae.o(*mod_ae_info_gain*)
		*isp_mod_ae.o(*mod_ae_algo_update*)
		*isp_mod_ae.o(*mod_ae_exec_set_setting*)
		*isp_mod_ae.o(*mod_ae_statis_done*)
		*isp_mod_ae.o(*isp_unregister_mod_ae*)	
		*isp_mod_af.o(*mod_af_dynamic*)
		*isp_mod_af.o(*af_g_volatile_ctrl*)
		*isp_mod_af.o(*isp_mod_af_cleanup*)
		*isp_mod_af.o(*set_ae_status*)
		*isp_mod_af.o(*mod_af_info_version*)
		*isp_mod_af.o(*mod_af_update_algo*)
		*isp_mod_af.o(*mod_af_algo_update*)
		*isp_mod_af.o(*mod_af_statis_done*)
		*isp_mod_af.o(*isp_unregister_mod_af*)		
		*isp_mod_awb.o(*isp_mod_awb_cleanup*)
		*isp_mod_awb.o(*mod_awb_exec_get_setting*)
		*isp_mod_awb.o(*mod_awb_exec_set_setting*)
		*isp_mod_awb.o(*mod_awb_info_version*)
		*isp_mod_awb.o(*mod_awb_algo_update*)
		*isp_mod_awb.o(*mod_awb_statis_done*)
		*isp_mod_awb.o(*isp_unregister_mod_awb*)

		/* isp_mod_* blc/ccm/control/crop */
		
		*isp_mod_blc.o(*isp_mod_blc_cleanup*)
		*isp_mod_blc.o(*mod_blc_statis_done*)
		*isp_mod_blc.o(*isp_unregister_mod_blc*)
		*isp_mod_ccm.o(*isp_mod_ccm_cleanup*)
		*isp_mod_ccm.o(*ccm_g_volatile_ctrl*)
		*isp_mod_ccm.o(*mod_ccm_statis_done*)
		*isp_mod_ccm.o(*isp_unregister_mod_ccm*)
		*isp_mod_control.o(*mod_control_exec_statis_done*)
		*isp_mod_control.o(*stop_isp_pipeline*)
		*isp_mod_control.o(*isp_mod_control_cleanup*)
		*isp_mod_control.o(*isp_unregister_mod_control*)
		*isp_mod_crop.o(*mod_crop_info_crop_size*)
		*isp_mod_crop.o(*isp_mod_crop_cleanup*)
		*isp_mod_crop.o(*isp_unregister_mod_crop*)

		/* isp_mod_* dehaze/eeh/flick/gamma */

		*isp_mod_dehaze.o(*isp_mod_dehaze_cleanup*)
		*isp_mod_dehaze.o(*isp_mod_dehaze_hardware_cleanup*)
		*isp_mod_dehaze.o(*isp_unregister_mod_dehaze*)
		*isp_mod_eeh.o(*mod_eeh_statis_done*)
		*isp_mod_eeh.o(*isp_mod_eeh_cleanup*)
		*isp_mod_eeh.o(*isp_unregister_mod_eeh*)
		*isp_mod_flick.o(*isp_mod_flick_cleanup*)
/*		
		*isp_mod_flick.o(*mod_flick_update_algo*)
		*isp_mod_flick.o(*mod_flick_algo_update*)
*/		
		*isp_mod_flick.o(*mod_flick_statis_done*)
		*isp_mod_flick.o(*isp_unregister_mod_flick*)
		*isp_mod_gamma.o(*gamma_g_volatile_ctrl*)
		*isp_mod_gamma.o(*isp_mod_gamma_cleanup*)
		*isp_mod_gamma.o(*mod_gamma_statis_done*)
		*isp_mod_gamma.o(*isp_unregister_mod_gamma*)

		/* isp_mod_* global/interface/intp/iq */
		
		*isp_mod_global.o(*mod_global_info_isp_clk*)
		*isp_mod_global.o(*mod_global_exec_get_bypass*)
		*isp_mod_global.o(*mod_global_exec_set_bypass*)
		*isp_mod_global.o(*mod_global_exec_set_delay_frames*)
		*isp_mod_global.o(*isp_mod_global_cleanup*)
		*isp_mod_global.o(*mod_global_exec_stop*)
		*isp_mod_global.o(*isp_unregister_mod_global*)
		*isp_mod_interface.o(*mod_interface_exec_stop*)
		*isp_mod_interface.o(*isp_mod_interface_cleanup*)
		*isp_mod_interface.o(*isp_unregister_mod_interface*)
		*isp_mod_intp.o(*isp_mod_intp_cleanup*)
		*isp_mod_intp.o(*mod_intp_statis_done*)
		*isp_mod_intp.o(*isp_unregister_mod_intp*)
		*isp_mod_iq.o(*mod_iq_info_dynamic*)
		*isp_mod_iq.o(*mod_iq_info_iq_sel*)
		*isp_mod_iq.o(*mod_iq_info_packed_iq*)
		*isp_mod_iq.o(*iq_get_type_info*)
		*isp_mod_iq.o(*mod_iq_exec_set_dynamic_md*)
		*isp_mod_iq.o(*mod_iq_exec_read_regs*)

		*isp_mod_iq.o(*mod_iq_exec_unbind_algo*)
		*isp_mod_iq.o(*mod_iq_exec_bind_algo*)
		*isp_mod_iq.o(*mod_iq_stop_post*)
		*isp_mod_iq.o(*isp_mod_iq_cleanup*)
		*isp_mod_iq.o(*mod_iq_exec_write_regs*)
		*isp_mod_iq.o(*iq_timer_callback*)
		*isp_mod_iq.o(*mod_iq_info_plugins_version*)
		*isp_mod_iq.o(*isp_unregister_mod_iq*)
		
		/* isp_mod_* ldc/mask/mcrop/mlsc/rawstat/rgb2yuv */
		
		*isp_mod_ldc.o(*isp_mod_ldc_cleanup*)
		*isp_mod_ldc.o(*isp_unregister_mod_ldc*)
		/* *isp_mod_mask.o(*mod_mask_exec_get*) */
		*isp_mod_mask.o(*isp_mod_mask_cleanup*)
		/* *isp_mod_mask.o(*mod_mask_exec_set*) */
		*isp_mod_mask.o(*isp_unregister_mod_mask*)
		*isp_mod_mcrop.o(*isp_mod_mcrop_cleanup*)
		*isp_mod_mcrop.o(*isp_unregister_mod_mcrop*)
		*isp_mod_mlsc.o(*isp_mod_mlsc_cleanup*)
		*isp_mod_mlsc.o(*isp_unregister_mod_mlsc*)
		*isp_mod_nlsc.o(*isp_mod_nlsc_cleanup*)
		*isp_mod_nlsc.o(*mod_nlsc_statis_done*)
		*isp_mod_nlsc.o(*isp_unregister_mod_nlsc*)
		*isp_mod_rawstat.o(*rawstat_g_volatile_ctrl*)
		*isp_mod_rawstat.o(*mod_rawstat_statis_done*)
		*isp_mod_rawstat.o(*isp_mod_rawstat_cleanup*)
		*isp_mod_rawstat.o(*day_night_timer_callback*)
		*isp_mod_rawstat.o(*isp_unregister_mod_rawstat*)
		*isp_mod_rgb2yuv.o(*isp_mod_rgb2yuv_cleanup*)
		*isp_mod_rgb2yuv.o(*isp_unregister_mod_rgb2yuv*)


		/* isp_mod_* sensor/spe/tnr/uvtune */

		*isp_mod_sensor.o(*sensor_cleanup_plugin*)
		*isp_mod_sensor.o(*mod_sensor_exec_get_mode*)
		*isp_mod_sensor.o(*mod_sensor_info_size*)
		*isp_mod_sensor.o(*mod_sensor_info_timing*)
		*isp_mod_sensor.o(*sensor_timer_callback*)
		*isp_mod_sensor.o(*mod_sensor_info_bound_snr_name*)
		*isp_mod_sensor.o(*mod_sensor_exec_write_sen_reg*)
		*isp_mod_sensor.o(*mod_sensor_exec_read_sen_reg*)
		*isp_mod_sensor.o(*isp_mod_sensor_cleanup*)
		*isp_mod_sensor.o(*mod_sensor_info_version*)
		*isp_mod_sensor.o(*mod_sensor_exec_set_dummy*)
		*isp_mod_sensor.o(*isp_unregister_mod_sensor*)
		*isp_mod_spe.o(*isp_mod_spe_cleanup*)
		*isp_mod_spe.o(*isp_unregister_mod_spe*)
		*isp_mod_tnr.o(*isp_mod_tnr_cleanup*)
		*isp_mod_tnr.o(*mod_tnr_stop_pre*)
		*isp_mod_tnr.o(*mod_tnr_statis_done*)
		*isp_mod_tnr.o(*isp_unregister_mod_tnr*)
		*isp_mod_uvtune.o(*mod_uvtune_statis_done*)
		*isp_mod_uvtune.o(*isp_mod_uvtune_cleanup*)
		*isp_mod_uvtune.o(*isp_unregister_mod_uvtune*)


		/* isp_mod_* vctrl/wdr/ygamma/ygc/ystat */

		*isp_mod_vctrl.o(*mod_vctrl_exec_try_ext_ctrls*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_s_ext_ctrls*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_g_ext_ctrls*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_query_ext_ctrl*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_g_ctrl*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_query_menu*)
		*isp_mod_vctrl.o(*mod_vctrl_exec_query_ctrl*)
		*isp_mod_vctrl.o(*isp_mod_vctrl_cleanup*)
		*isp_mod_vctrl.o(*isp_unregister_mod_vctrl*)
		*isp_mod_wdr.o(*isp_mod_wdr_cleanup*)
		*isp_mod_wdr.o(*mod_wdr_statis_done*)
		 /*  *isp_mod_wdr.o(*mod_wdr_update_algo*)  */
		*isp_mod_wdr.o(*mod_wdr_algo_update*)
		*isp_mod_wdr.o(*isp_unregister_mod_wdr*)
		*isp_mod_ygamma.o(*ygamma_g_volatile_ctrl*)
		*isp_mod_ygamma.o(*isp_mod_ygamma_cleanup*)
		*isp_mod_ygamma.o(*isp_unregister_mod_ygamma*)
		*isp_mod_ygc.o(*isp_mod_ygc_cleanup*)
		*isp_mod_ygc.o(*mod_ygc_statis_done*)
		*isp_mod_ygc.o(*isp_unregister_mod_ygc*)
		*isp_mod_ystat.o(*isp_mod_ystat_cleanup*)
		*isp_mod_ystat.o(*isp_unregister_mod_ystat*)

		/* isp_mod_* snr/md/tm */
		
		*isp_mod_snr.o(*isp_mod_snr_cleanup*)
		*isp_mod_snr.o(*mod_snr_statis_done*)
		*isp_mod_snr.o(*isp_unregister_mod_snr*)

		*isp_mod_md.o(*isp_mod_md_cleanup*)
		*isp_mod_md.o(*mod_md_algo_update*)
		*isp_mod_md.o(*mod_md_statis_done*)
		*isp_mod_md.o(*mod_md_stop_pre*)
		*isp_mod_md.o(*isp_unregister_mod_md*)

		*isp_mod_tm.o(*isp_mod_tm_cleanup*)
		*isp_mod_tm.o(*mod_tm_statis_done*)
		*isp_mod_tm.o(*isp_unregister_mod_tm*)	
	} > DDR_2	
	
	.fcs.itcm :
	{
		**startup.o(.text.Reset_Handler)			
		*(.text.SystemInit)				
		*(.text.sau_setup)				
		*(.text.startup.main)				
		*(.text.hal_vector_irq_en_voe)							
		*(.text.voe_rx_task)
		*(.text.startup.main*)
		*(.text.voe_open*)

				
		*heap_4_2*.o(.text.*)					
		*queue*.o(.text.*)		
					
		*tasks*.o(.text.*)				
		*port*.o(.text.*)					
		*list*.o(.text.*)					
		*timers.o(.text.*)			
		
							
		*libc_wrap_voe.o(.text.*)					
		
		/* need review */
		*rts_mem.o(.text*)
		*rtx_mutex.o(.text*)
		*rtl8735b_i2c_simple.o(.text*)
		*rt_time.o(.text*)  			
		
		*hal_timer.o(.text*)		
		*memory.o(.text*)				
		*(.text.SCB*)
  
	} > ITCM_RAM
	
	.fcs.dtcm :
	{
	

	} > DTCM_RAM
	
	
  	.sensor :
	{
		__get_sensor_ops__ = .;
		KEEP(*sensor_*.o(.text.rts_isp_get_sensor_ops*))
		KEEP(*sensor_*.o(.bss*))
		KEEP(*sensor_*.o(.data*))
		KEEP(*sensor_*.o(.text*))
		KEEP(*sensor_*.o(.rodata*))		
	} > SENSOR
	
	.iq :
	{
		. = ALIGN(4);
		__voe_iq_start__ = .;
		
	} > IQ		
	
	.iq_cali :
	{
		. = ALIGN(4);
		__voe_iq_cali_start__ = .;
		KEEP(*(.isp_iq_cali_data.ddr))				
	} > IQ_CALI			
	

	
	
	.cmd.ddr :
	{
		KEEP(*(.video_cmd0.dtcm))
		KEEP(*(.video_cmd1.dtcm))
		KEEP(*(.video_cmd2.dtcm))
		KEEP(*(.video_cmd3.dtcm))
		KEEP(*(.video_cmd4.dtcm))
		KEEP(*(.data.load_time))
		KEEP(*(.data.hal_voe_version))
		KEEP(*(.isp_grid_map.ddr))		

	} > DDR_CMD	

	.fcs.ddr :
	{
		KEEP(*(.voe_gmon.ddr))				
		. = ALIGN(8192);
		
		KEEP(*(.sysview.start))	
		KEEP(*SEGGER_*.o(.data*))
		KEEP(*SEGGER_*.o(.text*))
		KEEP(*SEGGER_*.o(.rodata*))		
	
	
		*voe_main.o(.bss*)
		/* Sys Init use*/
		*run_voe.o(.text.SCB_InvalidateDCache_by_Addr*)
		*run_voe.o(*voe_open*)
		*run_voe.o(*config_osd_block_num*)
		
		/* ISP Init use*/
		*rts_camera_osd2.o(*rtscam_osd2_irq*)
		*rts_camera_osd2.o(*rtscam_osd2_enable_interrupt.constprop.4*)
		*rts_camera_osd2.o(*rtscam_osd2_ioctl*)
		*rts_camera_osd2.o(*rtscam_osd2_probe*)
		
		*rt_osd2_api.o(*rt_osd2_init_chn_profile*)
		*rt_osd2_api.o(*rt_osd2_init*)
		
		*rts_video_osdenc.o(*rts_av_osdenc_init*)
		*rts_video_osdenc.o(*rts_av_osdenc_set_profile*)
		
		*rts_video_osd2_ctrl.o(*rts_av_set_osdenc_attr_owner*)
		*rts_video_osd2_ctrl.o(*rts_av_set_osdenc_attr*)
		*rts_video_osd2_ctrl.o(*rts_av_set_osdenc_fps*)
		*rts_video_osd2_ctrl.o(*rts_av_to_osdenc_t*)

		*rtsosd2.o(*osd2_alloc_dma*)
		*rtsosd2.o(*alloc_osd2_struct_buf*)
		*rtsosd2.o(*__check_osd2_config*)
		*rtsosd2.o(*__init_osd2_cmd*)
		*rtsosd2.o(*__init_osd2_blocks*)
		*rtsosd2.o(*__alloc_osd2_dma_buf*)
		*rtsosd2.o(*__init_osd2_color_table*)
		*rtsosd2.o(*rts_osd2_init*)
		*rtsosd2.o(*rts_osd2_get_blk_max_num*)
		*rtsosd2.o(*rts_osd2_set_adma_copy*)
		
		*ewl_osd2_common.o(*osd2_ewl_init*)		
		*rtsosd2color.o(*__find_color_field*)
		*rtsosd2color.o(*osd2_set_default_color_table*)
		
		*isp_statis.o(*isp_statis_init*)
		
		*rts-dma-contig.o(*rtscam_mem_alloc*)
		
		*isp_shm.o(*isp_shm_init*)
		
		*rts_camera_video.o(*rtscam_video_try_fmt*)
		*rts_camera_video.o(*rtscam_video_queue_allocated*)
		*rts_camera_video.o(*rtscam_acquire_privileges*)
		*rts_camera_video.o(*get_stream*)
		*rts_camera_video.o(*rtscam_get_phy_addr*)
		*rts_camera_video.o(*rtscam_submit_buffer*)
		*rts_camera_video.o(*rtscam_video_do_ioctl*)
		*rts_camera_video.o(*rtscam_video_register_device*)
		*rts_camera_video.o(.rodata.CSWTCH.40*)
			
		*isp_mod_statis.o(*mod_statis_mode_change*)
		*isp_mod_statis.o(*isp_shm_mutex_init*)
		*isp_mod_statis.o(*mod_statis_start_post*)
		*isp_mod_statis.o(*isp_mod_statis_init*)
		*isp_mod_statis.o(*isp_register_mod_statis*)
		*isp_mod_statis.o(*AE_STATIS_SHM_NAME*)
		*isp_mod_statis.o(*AWB_STATIS_SHM_NAME*)
		*isp_mod_statis.o(*AF_STATIS_SHM_NAME*)
		*isp_mod_statis.o(*TUNING_STATIS_SHM_NAME*)

		*isp_sensor.o(*isp_sensor_init*)
		*isp_sensor.o(*isp_sensor_register*)
		*isp_sensor.o(*isp_sensor_bind*)
		*isp_sensor.o(*isp_sensor_check_all_bound*)
		*isp_sensor.o(*isp_sensor_get_ops*)
		*isp_sensor.o(*isp_sensor_get_info*)

		*rts_isp_sensor.o(*rts_av_isp_set_sensor_mode*)
		*rts_isp_sensor.o(*rts_av_isp_enum_sensor_modes*)
		*isp_mod_sensor.o(*mod_sensor_exec_set_mode*)
		*isp_mod_sensor.o(*mod_sensor_exec_enum_modes*)
		*rts_camera_isp.o(*rtscam_isp_mem_free*)

		*isp_hw_ae.o(*isp_hw_ae_set_hdr*)		
		*isp_hw_ae.o(*isp_hw_ae_enable_hdr*)		

		*isp_iq.o(*isp_iq_change_table*)
		*isp_iq.o(*isp_iq_change_day_night*)
		*isp_iq.o(*isp_iq_reload_packed_iq*)
		*isp_iq.o(*switch_start_ae_count*)
		*isp_mod_iq.o(*apply_iq_table*)
		*isp_mod_iq.o(*mod_iq_exec_reload_packed_iq*)
		*isp_mod_iq.o(*mod_iq_exec_set_iq_table*)
		*isp_mod.o(*isp_mod_notify*) 
		*isp_mod_iq.o(*iq_reset_notified_value*)
		*isp_mod_iq.o(*mod_iq_exec_get_iq_table*)
		*isp_mod_iq.o(*mod_iq_exec_get_algo_param*)
		*isp_mod_iq.o(*mod_iq_exec_set_algo_param*)
		*isp_mod_iq.o(*TUNING_PARAM_SHM_NAME*)
		*isp_mod_iq.o(*TUNING_IQ_TABLE_SHM_NAME*)
		*isp_video_ctrl.o(*rtsv_ctrl_s_ctrl*)
		*isp_hw_dvp.o(*isp_hw_dvp_get_ops*)
		*pb_decode.o(*pb_release_single_field*)

		*isp_driver.o(*isp_driver_stream_add*)
		*isp_driver.o(*isp_driver_register_subdev*)
		*isp_driver.o(*isp_driver_init_statis*)
		*isp_driver.o(*isp_driver_get_statis_info*)
		*isp_driver.o(*isp_driver_mem_alloc*)
		*isp_driver.o(*isp_driver_mmap*)
		*isp_driver.o(*isp_driver_init*)
		*isp_driver.o(*isp_driver_sel_pin_state*)
		*isp_driver.o(*isp_driver_set_clk*)
		*isp_driver.o(*isp_driver_isp_clk_get*)
		*isp_driver.o(*isp_driver_isp_clk_put*)
		*isp_driver.o(*isp_driver_is_fpga*)
		*isp_driver.o(*isp_driver_get_tnr_bit*)
		*isp_driver.o(*isp_driver_write_sync_regs*)
		*isp_driver.o(*isp_driver_sync_lock*)
		*isp_driver.o(*isp_driver_i2c_write*)
		*isp_driver.o(*isp_driver_i2c_read*)
		*isp_poll.o(*isp_timer_init*)
		*isp_poll.o(*isp_timer_stop*)
		*isp_poll.o(*isp_timer_start*)
		*isp_poll.o(*isp_io_event_add*)
		*isp_poll.o(*isp_io_set_release*)
		*isp_poll.o(*isp_io_init*)
		*isp_poll.o(*isp_poll_update_time*)
		*isp_poll.o(*isp_poll_create*)
		*isp_poll.o(*isp_poll_loop_run*)
		*isp_poll.o(*isp_poll_set_fd_nonclose*)
		*isp_poll.o(.rodata)

		*isp_stream.o(*isp_stream_set_release*)
		*isp_stream.o(*isp_stream_init*)

		*isp_stream_client.o(*stream_message_execute*)
		*isp_stream_client.o(*isp_stream_client_add*)


		*reset-rts3915.o(*rts_sys_force_reset*)
		*reset-rts3915.o(*rts_reset_probe*)
		
		*event_groups.o(*xEventGroupCreate*)

		*rts_isp_ae.o(*rts_isp_register_ae_fps_change_cb*)	
		*rts_isp_ae.o(*rts_isp_set_max_dyn_region_en*)	

		*rtl8735b_gpio_simple.o(hal_gpio_init_simple_fcs*)

	} > DDR
	
	.enc.ddr :
	{
	
		*lib_a-f*(.text* .rodata*)

		/* */
		*startup.o(.text* .rodata*)
		
		*run_voe.o(.text* .rodata*)


		
		
		/* ISP init */
		
/*		
		*(.rodata.__func__* .rodata.__FUNCTION__*)
		*rt_osd2_api.o(.text* .rodata*)
		*rts_camera_osd2.o(.text* .rodata*)	
		*rts_camera_video.o(.text* .rodata*)		
*/	
			
		*rtsosd2.o(.text* .rodata*)
		*rtsosd2color.o(.text*)
		*rtsosd2registers.o(.text* .rodata*)

		*ewl_osd2_common.o(.text* .rodata*)
		*rtsav_md2.o(.text* .rodata*)

		*pb_encode.o(.text* .rodata*)
	
		*rts_video_osdenc.o(.text* .rodata*)
		*rts_video_osd2_ctrl.o(.text* .rodata*)
		
		*rts_isp_ae.o(.text* .rodata*)
		*rts_isp_af.o(.text* .rodata*)
		*rts_isp_awb.o(.text* .rodata*)
		*rts_isp_md.o(.text* .rodata*)
		*rts_isp_tuning.o(.text* .rodata*)
		
		

	
		*rts_img_proc.o(.text* .rodata*)
		*rts_pprc.o(.text* .rodata*)	
		*rts_raw.o(.text* .rodata*)
		*rts-dma-contig.o(.text* .rodata*)
		
		*isp_stream_client.o(.text* .rodata*)
		*isp_shm.o(.text* .rodata*)
		
		*isp_mod_statis.o(.text* .rodata*)
		*isp_sensor.o(.text* .rodata*)
/*		
		*isp_driver.o(.text* .rodata*)
		*isp_driver.o(.text*)
*/		
		*isp_poll.o(.text* .rodata*)		
		*isp_stream.o(.text* .rodata*)
		*isp_statis.o(.text* .rodata*)
		*isp_errno.o(.text* .rodata*)
		
		*isp_hw_fixp.o(.text* .rodata*)
		
		*reset-rts3915.o(.text* .rodata*)
		
		*event_groups.o(.text* .rodata*)
		
		

		/* ENC */
	
	
		*vidstabcommon.o(.text*)
		*vidstabalg.o(.text*)

		*ewl_ameba.o(.text*)
		*encasiccontroller.o(.text*)
		*encswhwregisters.o(.text*)
		*hevcencapi.o(.text*)
		*sw_put_bits.o(.text*)
		*sw_nal_unit.o(.text*)
		*hash.o(.text*)
		*checksum.o(.text*)
		*crc.o(.text*)
		*hevcSei.o(.text*)
		*rate_control_picture.o(.text*)
		*sw_picture.o(.text*)
		*sw_parameter_set.o(.text*)
		*encpreprocess.o(.text*)
		*sw_slice.o(.text*)
		*queue_enc.o(.text*)
		*tools.o(.text*)
		*test_bench_utils.o(.text*)
		*encasiccontroller_v2.o(.text*)
		
		*JpegEncApi.o(.text*)
		*EncJpegInit.o(.text*)
		*EncJpeg.o(.text*)
		*EncJpegCodeFrame.o(.text*)
		*EncJpegPutBits.o(.text*)
		
		*vidstabcommon.o(.bss* .rodata* COMMON .data*)
		*vidstabalg.o(.bss* .rodata* COMMON .data*)
		
		*ewl_ameba.o(.bss* .rodata* COMMON .data*)
		*encasiccontroller.o(.bss* .rodata* COMMON .data*)
		*encswhwregisters.o(.bss* .rodata* COMMON .data*)
		*hevcencapi.o(.bss* .rodata* COMMON .data*)
		*sw_put_bits.o(.bss* .rodata* COMMON .data*)
		*sw_nal_unit.o(.bss* .rodata* COMMON .data*)
		*hash.o(.bss* .rodata* COMMON .data*)
		*checksum.o(.bss* .rodata* COMMON .data*)
		*crc.o(.bss* .rodata* COMMON .data*)
		*hevcSei.o(.bss* .rodata* COMMON .data*)
		*rate_control_picture.o(.bss* .rodata* COMMON .data*)
		*sw_picture.o(.bss* .rodata* COMMON .data*)
		*sw_parameter_set.o(.bss* .rodata* COMMON .data*)
		*encpreprocess.o(.bss* .rodata* COMMON .data*)
		*sw_slice.o(.bss* .rodata* COMMON .data*)
		*queue_enc.o(.bss* .rodata* COMMON .data*)
		*tools.o(.bss* .rodata* COMMON .data*)
		*test_bench_utils.o(.bss* .rodata* COMMON .data*)
		*encasiccontroller_v2.o(.bss* .rodata* COMMON .data*)
		
		*JpegEncApi.o(.bss* .rodata* COMMON .data*)
		*EncJpegInit.o(.bss* .rodata* COMMON .data*)
		*EncJpeg.o(.bss* .rodata* COMMON .data*)
		*EncJpegCodeFrame.o(.bss* .rodata* COMMON .data*)
		*EncJpegPutBits.o(.bss* .rodata* COMMON .data*)
		
	} > DDR_2
	
	.ddr :
	{
		/* SYSTEM library */		
		*_arm_*(.text* .rodata* .data*)		
		*lib_a*(.text* .rodata* .data*)
		*(*.text* .rodata* .data*)
		
		
				
	} > DDR	
  
    /* .bss section which is used for uninitialized data */
    .bss :
    {
		. = ALIGN(32);
		__bss_start__ = .;		
		*(.bss*)
		*(COMMON)		
        . = ALIGN(32);
        __bss_end__ = .;  
         
  	} > BSS  

     /* .ARM.exidx is sorted, so has to go in its own output section.  */
	PROVIDE_HIDDEN (__exidx_start = .);
	
    .ARM.exidx :
    {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > DDR
    
    PROVIDE_HIDDEN (__exidx_end = .);
    __etext = .;
    _sidata = .;




  

    /* .stack section doesn't contains any symbols. It is only
     * used for linker to reserve space for the main stack section
     * WARNING: .stack should come immediately after the last secure memory
     * section.  This provides stack overflow detection. */

	 
    .stack (NOLOAD):
    {
	. = ALIGN(8);
	__StackLimit = .;
        *(.stack*);
     /*   . += 0x400 - (. - __StackLimit); */
        . += (ORIGIN(DTCM_RAM) + LENGTH(DTCM_RAM) - 8 - .); 
    } > DTCM_RAM
	
    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ADDR(.stack) + SIZEOF(.stack);
    PROVIDE(__stack = __StackTop);
	
}
