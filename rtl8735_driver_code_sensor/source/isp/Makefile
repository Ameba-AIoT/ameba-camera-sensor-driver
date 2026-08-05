
.PHONY: all clean obj_copy

MKDIR= mkdir

ROOT_DIR= ../../../..
LIB_DIR	    = ../lib
OUTPUT_DIR	= ../output

release = n

export ASDK_DIR ROOT_DIR

#ifeq (../lib_isp, $(wildcard ../lib_isp))	# lib_isp exist

ifeq ($(release),y) 
ISP_LIB_DIR	= ../lib_isp
else
ISP_LIB_DIR	= $(ROOT_DIR)/hal/rtl8735b/verify/video/lib_isp
endif

ISP_OSD_DIR = $(ROOT_DIR)/source/video_demo/osd

OUTLIB		= voe_isp.a


EXT_CC		+= -l3A -lOSD2

EXT_INC		=
EXT_INC		+= -I../cmsis/cmsis-core/include
EXT_INC += -I../cmsis/voe/include
EXT_INC += -I../cmsis
EXT_INC += -I../hal

ifeq ($(fpu), soft)
LINK_LIBS	= $(ISP_LIB_DIR)/lib/lib3A_soft.a
else ifeq ($(fpu), softfp)
LINK_LIBS	= $(ISP_LIB_DIR)/lib/lib3A_softfp.a
else
LINK_LIBS	= $(ISP_LIB_DIR)/lib/lib3A_hard.a
endif

ifeq ($(rtos_dir), freertos)
EXT_INC += -I../os/freertos
EXT_INC += -I../os/freertos/freertos_v10.1.1/include 
EXT_INC += -I../os/freertos/freertos_v10.1.1/portable/GCC/ARM_RTL8735B_VOE
else

EXT_INC += -I../os/freertos_v2020 
EXT_INC += -I../os/freertos_v2020/freertos_v202012.00/include 
EXT_INC += -I../os/freertos_v2020/freertos_v202012.00/portable/GCC/ARM_CM33_NTZ/non_secure
endif

EXT_INC += -I../voe/segger_sysview
EXT_INC += -I../include

EXT_INC += -I$(ROOT_DIR)/hal/rtl8735b/lib/source/ram/video

EXT_INC += -I$(ISP_LIB_DIR)

EXT_INC += -I$(ISP_LIB_DIR)/drv  
EXT_INC += -I$(ISP_LIB_DIR)/drv/bsp
EXT_INC += -I$(ISP_LIB_DIR)/drv/clk
EXT_INC += -I$(ISP_LIB_DIR)/drv/clk/linux 
EXT_INC += -I$(ISP_LIB_DIR)/drv/gpio  
EXT_INC += -I$(ISP_LIB_DIR)/drv/i2c
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/kernel 
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/kernel/include  
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/kernel/include/linux  
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/rts_camera
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/rts_camera/linux
EXT_INC += -I$(ISP_LIB_DIR)/drv/isp/3915/rts_camera/media
EXT_INC += -I$(ISP_LIB_DIR)/drv/reset 
EXT_INC += -I$(ISP_LIB_DIR)/drv/rlx
EXT_INC += -I$(ISP_LIB_DIR)/drv/rlx/reg
EXT_INC += -I$(ISP_LIB_DIR)/drv/time
EXT_INC += -I$(ISP_LIB_DIR)/drv/i2c
EXT_INC += -I$(ISP_LIB_DIR)/drv/osd2  
EXT_INC += -I$(ISP_LIB_DIR)/lib  
EXT_INC += -I$(ISP_LIB_DIR)/lib/common
EXT_INC += -I$(ISP_LIB_DIR)/lib/common/tlsf  
EXT_INC += -I$(ISP_LIB_DIR)/lib/config
EXT_INC += -I$(ISP_LIB_DIR)/lib/video 
EXT_INC += -I$(ISP_LIB_DIR)/lib/video/3915
EXT_INC += -I$(ISP_LIB_DIR)/lib/video/3915/include 
EXT_INC += -I$(ISP_LIB_DIR)/lib/video/3915/include/linux 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/core 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hal
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/api 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/core
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/hardware  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/api
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/regs  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/regs/rts3915
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/include
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/include/api  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/include/common  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/modules
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/modules/include 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/proto  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/proto/nanopb 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/test
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/isp/test/ctrls
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2/include
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2/test
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2/test  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2/test 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/md2/test 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/osd/ewl
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/osd/include
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/hardware/osd/src  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/include 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/media
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/media/include 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/media/video
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/media/video/md2
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/media/video/osd2
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtscamkit  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtscamkit/include
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtscamkit/src 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsutils
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsutils/include 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsutils/src  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsv4l2 
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/include  
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/src
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/test
EXT_INC += -I$(ISP_LIB_DIR)/rtstream/raw 
EXT_INC += -I$(ISP_LIB_DIR)/share
EXT_INC += -I$(ISP_LIB_DIR)/share/common
EXT_INC += -I$(ISP_LIB_DIR)/share/config
EXT_INC += -I$(ISP_LIB_DIR)/share/ispfw
EXT_INC += -I$(ISP_LIB_DIR)/sys
EXT_INC += -I$(ISP_OSD_DIR)


EXT_INC +=  


vpath %.c $(ISP_LIB_DIR)
vpath %.c $(ISP_LIB_DIR)/drv
vpath %.c $(ISP_LIB_DIR)/drv/clk
vpath %.c $(ISP_LIB_DIR)/drv/clk/linux 
vpath %.c $(ISP_LIB_DIR)/drv/gpio  
vpath %.c $(ISP_LIB_DIR)/drv/i2c
vpath %.c $(ISP_LIB_DIR)/drv/isp
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/kernel 
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/kernel/include  
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/kernel/include/linux  
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/rts_camera
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/rts_camera/linux
vpath %.c $(ISP_LIB_DIR)/drv/isp/3915/rts_camera/media
vpath %.c $(ISP_LIB_DIR)/drv/osd2 
vpath %.c $(ISP_LIB_DIR)/drv/reset 
vpath %.c $(ISP_LIB_DIR)/drv/rlx
vpath %.c $(ISP_LIB_DIR)/drv/rlx/reg
vpath %.c $(ISP_LIB_DIR)/drv/time 
vpath %.c $(ISP_LIB_DIR)/drv/i2c 
vpath %.c $(ISP_LIB_DIR)/lib  
vpath %.c $(ISP_LIB_DIR)/lib/common
vpath %.c $(ISP_LIB_DIR)/lib/common/tlsf
vpath %.c $(ISP_LIB_DIR)/lib/config
vpath %.c $(ISP_LIB_DIR)/lib/video 
vpath %.c $(ISP_LIB_DIR)/lib/video/3915
vpath %.c $(ISP_LIB_DIR)/lib/video/3915/include 
vpath %.c $(ISP_LIB_DIR)/lib/video/3915/include/linux 
vpath %.c $(ISP_LIB_DIR)/rtstream  
vpath %.c $(ISP_LIB_DIR)/rtstream/core 
vpath %.c $(ISP_LIB_DIR)/rtstream/hal
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/api 
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/core
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/hardware  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/api
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/regs  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/hardware/include/regs/rts3915
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/include
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/include/api  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/include/common  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/modules
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/modules/include 
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/proto  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/proto/nanopb 
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/test
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/isp/test/ctrls
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/md2  
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/md2/include
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/md2/test
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/osd/ewl
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/osd/include
vpath %.c $(ISP_LIB_DIR)/rtstream/hardware/osd/src
vpath %.c $(ISP_LIB_DIR)/rtstream/include 
vpath %.c $(ISP_LIB_DIR)/rtstream/media
vpath %.c $(ISP_LIB_DIR)/rtstream/media/include 
vpath %.c $(ISP_LIB_DIR)/rtstream/media/video
vpath %.c $(ISP_LIB_DIR)/rtstream/media/video/md2
vpath %.c $(ISP_LIB_DIR)/rtstream/media/video/osd2  
vpath %.c $(ISP_LIB_DIR)/rtstream/utils
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtscamkit  
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtscamkit/include
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtscamkit/src 
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsutils
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsutils/include 
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsutils/src  
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsv4l2 
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/include  
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/src
vpath %.c $(ISP_LIB_DIR)/rtstream/utils/librtsv4l2/test
vpath %.c $(ISP_LIB_DIR)/rtstream/raw  
vpath %.c $(ISP_LIB_DIR)/semihost  
vpath %.c $(ISP_LIB_DIR)/share
vpath %.c $(ISP_LIB_DIR)/share/common
vpath %.c $(ISP_LIB_DIR)/share/config
vpath %.c $(ISP_LIB_DIR)/share/ispfw
vpath %.c $(ISP_LIB_DIR)/sys
vpath %.c $(ISP_OSD_DIR)


OBJS += rtx_mutex.o
OBJS += clk-rts3915.o

#OBJS += hal_gpio_simple.o
OBJS += rtl8735b_gpio_simple.o
#OBJS += hal_i2c_simple.o
OBJS += rtl8735b_i2c_simple.o
OBJS += rts-dma-contig.o
OBJS += rts_camera.o
OBJS += rts_camera_ctrl.o
OBJS += rts_camera_fps.o
OBJS += rts_camera_isp.o
OBJS += rts_camera_isp_mfd.o
OBJS += rts_camera_md.o
OBJS += rts_camera_soc.o
OBJS += rts_camera_soc_3915.o
OBJS += rts_camera_verify.o
OBJS += rts_camera_video.o
OBJS += rts_camera_zoom.o
OBJS += vb2_utils.o
OBJS += videobuf2-core.o
OBJS += rts_camera_osd2.o
OBJS += rts_video_osd2_ctrl.o
OBJS += rts_video_osdenc.o
OBJS += reset-rts3915.o
OBJS += rlx_cpu.o
OBJS += rlx_sh_irq.o
OBJS += rlx_sys.o
OBJS += rlx_time.o
OBJS += rt_time.o
OBJS += memleak.o
OBJS += mpool.o
OBJS += rt_avdef.o
OBJS += rt_shell.o
OBJS += rt_shellscript.o
OBJS += rt_task.o
OBJS += rt_util.o
OBJS += rt_tlsf.o
OBJS += rts_ioctl.o
OBJS += rt_osd2_api.o
OBJS += rtsavobj.o
OBJS += isp_hal.o
OBJS +=	rts_isp.o
OBJS +=	rts_isp_ae.o
OBJS +=	rts_isp_af.o
OBJS +=	rts_isp_awb.o
OBJS +=	rts_isp_ctrl.o
OBJS +=	rts_isp_mask.o
OBJS +=	rts_isp_patch.o
OBJS +=	rts_isp_tuning.o
OBJS += rts_isp_utils.o
OBJS += isp_algo.o
OBJS += isp_avl.o
OBJS += isp_core.o
OBJS += isp_driver.o
OBJS += isp_errno.o
OBJS += isp_geom.o
OBJS += isp_iq.o
#OBJS += isp_log.o
OBJS += isp_mod.o
OBJS += isp_msg_buf.o
OBJS += isp_notify.o
#OBJS += isp_plugin.o
OBJS += isp_poll.o
OBJS += isp_request.o
OBJS += isp_sensor.o
OBJS += isp_shm.o
OBJS += isp_statis.o
OBJS += isp_stream.o
OBJS += isp_stream_client.o
OBJS += isp_top.o
#OBJS += isp_uds.o
OBJS += isp_uds_client.o
OBJS += isp_utils.o
OBJS += isp_video_ctrl.o
OBJS += isp_hw_ae.o
OBJS += isp_hw_af.o
OBJS += isp_hw_awb.o
OBJS += isp_hw_blc.o
OBJS += isp_hw_ccm.o
OBJS += isp_hw_crop.o
OBJS += isp_hw_dehaze.o
OBJS += isp_hw_dvp.o
OBJS += isp_hw_eeh.o
OBJS += isp_hw_fixp.o
OBJS += isp_hw_flick.o
OBJS += isp_hw_gamma.o
OBJS += isp_hw_global.o
OBJS += isp_hw_intp.o
OBJS += isp_hw_iq.o
OBJS += isp_hw_ldc.o
OBJS += isp_hw_mask.o
OBJS += isp_hw_mcrop.o
OBJS += isp_hw_mipi.o
OBJS += isp_hw_mipiout.o
OBJS += isp_hw_mlsc.o
OBJS += isp_hw_nlsc.o
OBJS += isp_hw_rawstat.o
OBJS += isp_hw_rgb2yuv.o
OBJS += isp_hw_spe.o
OBJS += isp_hw_statis.o
OBJS += isp_hw_tnr.o
OBJS += isp_hw_uvtune.o
OBJS += isp_hw_vinf.o
OBJS += isp_hw_vreg.o
OBJS += isp_hw_wdr.o
OBJS += isp_hw_ygamma.o
OBJS += isp_hw_ygc.o
OBJS += isp_hw_ystat.o
OBJS += isp_hw_sensor.o
OBJS += isp_modules.o
OBJS += isp_mod_ae.o
OBJS += isp_mod_af.o
OBJS += isp_mod_awb.o
OBJS += isp_mod_blc.o
OBJS += isp_mod_ccm.o
OBJS += isp_mod_control.o
OBJS += isp_mod_crop.o
OBJS += isp_mod_dehaze.o
OBJS += isp_mod_eeh.o
OBJS += isp_mod_flick.o
OBJS += isp_mod_gamma.o
OBJS += isp_mod_global.o
OBJS += isp_mod_interface.o
OBJS += isp_mod_intp.o
OBJS += isp_mod_iq.o
OBJS += isp_mod_ldc.o
OBJS += isp_mod_mask.o
OBJS += isp_mod_mcrop.o
OBJS += isp_mod_mipiout.o
OBJS += isp_mod_mlsc.o
OBJS += isp_mod_nlsc.o
OBJS += isp_mod_rawstat.o
OBJS += isp_mod_rgb2yuv.o
OBJS += isp_mod_sensor.o
OBJS += isp_mod_spe.o
OBJS += isp_mod_statis.o
OBJS += isp_mod_tnr.o
OBJS += isp_mod_uvtune.o
OBJS += isp_mod_vctrl.o
OBJS += isp_mod_wdr.o
OBJS += isp_mod_ygamma.o
OBJS += isp_mod_ygc.o
OBJS += isp_mod_ystat.o
OBJS += isp_algo_param.pb.o
OBJS += isp_iq_table.pb.o
OBJS += isp_statis.pb.o
OBJS += pb_common.o
OBJS += pb_decode.o
OBJS += pb_encode.o
OBJS += main_isp.o
#OBJS += common.o
#OBJS += test_ae.o
#OBJS += test_awb.o
#OBJS += test_ctrl.o
OBJS += rts_isp_md.o
OBJS += test_md2.o
OBJS += ewl_osd2_common.o
OBJS += rtsosd2.o
OBJS += rtsosd2cmd.o
OBJS += rtsosd2color.o
OBJS += rtsosd2registers.o
#OBJS += rtsvideo.o
OBJS += rtsav_md2.o
OBJS += rts_img_proc.o
OBJS += rts_pprc.o
OBJS += rts_errno.o
#OBJS += rts_log.o
OBJS += rts_mem.o
OBJS += rtsc_hwver.o
OBJS += rtsc_regs.o
OBJS += rtsc_utils.o
OBJS += rts_rtsv.o
OBJS += rts_test_v4l2.o
OBJS += send2host.o
OBJS += my_def.o
OBJS += rt_log.o
OBJS += rt_hconf_data.o
#OBJS += rt_ispfw.o
OBJS += hal_isp.o
OBJS += rts_time.o

OBJS += rts_raw.o

OBJS += isp_hw_snr.o
OBJS += isp_hw_tm.o
OBJS += isp_hw_md.o
OBJS += isp_mod_snr.o
OBJS += isp_mod_tm.o
OBJS += isp_mod_md.o
OBJS +=	rts_isp_sensor.o


SUBDIRS = isp

ifeq ($(sysview), 1)
EXT_INC		+= -I../voe/segger_sysview
endif

ifeq ($(gprof), 1)
EXT_INC		+= -pg
endif

EXT_CC		+= -DCONFIG_VERIFY_SYSVIEW=$(sysview)
EXT_CC		+= -DCONFIG_GPROF=$(gprof)
EXT_CC		+= -DISP_MAIN=0

all: $(OBJS)


%.o:%.c
	$(CC) $(EXT_CC) $(EXT_INC) $< -o $@


%.o:%.S
	$(AS) $< -o $@


clean:
	-rm -f *.o *.i *.d *.s *.su;

obj_copy:
	$(AR) crv $(LIB_DIR)/$(OUTLIB) $(OBJS);\
	cp -f $(LINK_LIBS) $(LIB_DIR)/lib3A.a
	
-include $(patsubst %.o,%.d,$(OBJS))

