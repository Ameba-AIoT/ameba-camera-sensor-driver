


MEMORY
{
  ITCM_ROM   (rx)       : ORIGIN = 0x00000000, LENGTH = 0x400					/* 1KB	*/
  ITCM_RAM   (rwx)      : ORIGIN = 0x00040000, LENGTH = 0x10000  				/* 64KB */
  DTCM_ROM   (rx)       : ORIGIN = 0x20010000, LENGTH = 0x4000    				/* 16KB	*/
  DTCM_RAM   (rwx)      : ORIGIN = 0x20000000, LENGTH = 0xFF00					/* 63KB	*/
  ROM_RESV   (rwx)      : ORIGIN = 0x2000FF00, LENGTH = 0x100					/* 128B	*/   
  VOE_HEAD   (rwx)      : ORIGIN = 0x70000000, LENGTH = 0x70000040 - 0x70000000	/* 64B */  
  SENSOR     (rwx)      : ORIGIN = 0x70000040, LENGTH = 0x70008000 - 0x70000040	/* 32KB - 64B */  
  IQ         (rwx)      : ORIGIN = 0x70008000, LENGTH = 0x70034000 - 0x70008000	/* 200KB */  
  DDR        (rwx)      : ORIGIN = 0x7003A000, LENGTH = 0x700E0000 - 0x7003A000	/* 384KB */
  DDR_2      (rwx)      : ORIGIN = 0x700E0000, LENGTH = 0x700F0000 - 0x700E0000	/* 64KB */
  BSS        (rwx)      : ORIGIN = 0x700F0000, LENGTH = 0x70100000 - 0x700F0000	/* 64KB */
  
}


/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

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
		. = ALIGN(32);
	

	} > DTCM_RAM	
	
	.fcs.itcm :
	{

	} > ITCM_RAM
	
	.fcs.dtcm :
	{
	

	} > DTCM_RAM
	
	
  	.sensor :
	{
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
	
	.cmd.ddr :
	{
		KEEP(*(.video_adp.dtcm))
		KEEP(*(.video_cmd0.dtcm))
		KEEP(*(.video_cmd1.dtcm))
		KEEP(*(.video_cmd2.dtcm))
		KEEP(*(.video_cmd3.dtcm))
		KEEP(*(.video_cmd4.dtcm))		
		KEEP(*(.voe_gmon.ddr))				
		. = ALIGN(8192);
		
		KEEP(*(.sysview.start))	
		KEEP(*SEGGER_*.o(.data*))
		KEEP(*SEGGER_*.o(.text*))
		KEEP(*SEGGER_*.o(.rodata*))		
	} > DDR	

	.fcs.ddr :
	{
		*voe_main.o(.bss*)
		*(.data*)
		
		/* Sys Init use*/
		*run_voe.o(.text.SCB_InvalidateDCache_by_Addr*)
		*run_voe.o(.text.voe_open*)
		
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
		
		*rtsosd2.o(*osd2_alloc_dma*)
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
		*isp_stream_client.o(*stream_message_execute*)
		*isp_stream_client.o(*isp_stream_client_add*)
		
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
				

		*isp_sensor.o(*isp_sensor_init*)
		*isp_sensor.o(*isp_sensor_register*)
		*isp_sensor.o(*isp_sensor_bind*)
		*isp_sensor.o(*isp_sensor_check_all_bound*)
		*isp_sensor.o(*isp_sensor_get_ops*)
		*isp_sensor.o(*isp_sensor_get_info*)
					
		/**/	
		/**/
		
		*isp_top.o(.text* .rodata* .data*)
		*isp_algo.o(.text* .rodata* .data*)
		*isp_driver.o(.text* .rodata* .data*)
		*isp_poll.o(.text* .rodata* .data*)
		*isp_utils.o(.text* .rodata* .data*)
		*isp_notify.o(.text* .rodata* .data*)
		*isp_modules.o(.text* .rodata* .data*)
		
		*isp_hw_*.o(.text* .rodata* .data*)
		*isp_stream.o(.text* .rodata* .data*)

		*rts_algo_*.o(.text* .rodata* .data*)
			
		*pb_decode.o(.text* .rodata* .data*)
		*pb_common.o(.text* .rodata* .data*)

		*isp_iq_table.pb.o(.text* .rodata* .data*)


		*_aeabi*.o(.text*)
		*_udivmoddi4.o(.text*)
		*_dvmd_tls.o(.text*)
		*_fixsfdi.o(.text*)
		*_fixunssfdi.o(.text*)
		
		
		*_arm_*.o(.text*)
		*lib_a*.o(.text*)
		*lib_a-*.o(.text*)
		*lib_a*(.text* .rodata* .data* COMMON)
		*(.text_*)

				
	} > DDR
	
	.enc.ddr :
	{

		. = ALIGN(32);

	} > DDR_2
	
	.ddr :
	{
		/* SYSTEM library */		
		*_arm_*(.text* .rodata* .data*)		
		*(*.text* .rodata* .data*)
		
		*(COMMON)		
		*(.bss*)
		
	} > DDR	
  
    /* .bss section which is used for uninitialized data */
    .bss :
    {
		. = ALIGN(32);
		__bss_start__ = .;		
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
