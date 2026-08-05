
.PHONY: all clean mk_build_dir build_lib post_process

DEFAULT_ROOT_MK = /d/AmebaProII/SD9/VOE/20260317/ameba_pro2/root.mk

#Open this line for sub dir build debugging, root makefile have exported the symbols
#include $(DEFAULT_ROOT_MK)

# Ensure makefile is called from root dir
ifeq ($(ROOT_MK),)
ROOT_DIR = $(shell dirname $(DEFAULT_ROOT_MK))
$(error Please call make from root dir: $(ROOT_DIR))
endif

MKDIR= mkdir

OUTLIB = 

EXT_CC=  -DCTBRC_STRENGTH -Wno-format -Wno-implicit-function-declaration -DTB_DEFINED_COMMENT -DRTOS_FREERTOS -DCONFIG_RTS3915 -l3A -lOSD2

EXT_INC=
EXT_INC += -I$(ASDK_DIR)/arm-none-eabi/include
EXT_INC += -I../../../../../cmsis/cmsis-core/include
EXT_INC += -I../../../../../cmsis/cmsis-dsp/include
EXT_INC += -I../../../../../cmsis/rtl8735b/include
EXT_INC += -I../../../../../cmsis/rtl8735b/lib/include
EXT_INC += -I../../../include
EXT_INC += -I../../../lib/include
EXT_INC += -I../../../lib/source/ram/nn
EXT_INC += -I../../../lib/source/ram/nn/VIPLiteDrv
EXT_INC += -I../../../lib/source/ram/nn/model_itp
EXT_INC += -I../../../lib/source/ram/nn/nn_api
EXT_INC += -I../../../lib/source/ram/nn/nn_postprocess
EXT_INC += -I../../../lib/source/ram/nn/nn_preprocess
EXT_INC += -I../../../lib/source/ram/nn/run_facerecog
EXT_INC += -I../../../lib/source/ram/nn/run_itp
EXT_INC += -I../../../lib/source/ram/usb_otg
EXT_INC += -I../../../lib/source/ram/usb_otg/device/class/ethernet/inc
EXT_INC += -I../../../lib/source/ram/usb_otg/device/class/ethernet/src
EXT_INC += -I../../../lib/source/ram/usb_otg/device/class/msc/inc
EXT_INC += -I../../../lib/source/ram/usb_otg/device/class/vendor/inc
EXT_INC += -I../../../lib/source/ram/usb_otg/device/core/inc
EXT_INC += -I../../../lib/source/ram/usb_otg/host/storage/inc
EXT_INC += -I../../../lib/source/ram/usb_otg/host/storage/inc/quirks
EXT_INC += -I../../../lib/source/ram/usb_otg/host/storage/inc/scatterlist
EXT_INC += -I../../../lib/source/ram/usb_otg/host/storage/inc/scsi
EXT_INC += -I../../../lib/source/ram/usb_otg/host/vendor_spec
EXT_INC += -I../../../lib/source/ram/usb_otg/inc
EXT_INC += -I../../../lib/source/ram/video
EXT_INC += -I../../../lib/source/ram/video/semihost
EXT_INC += -I../../i2c
EXT_INC += -I..
EXT_INC += -I../lib_enc/inc
EXT_INC += -I../lib_enc/linux_reference/test/hevc
EXT_INC += -I../lib_enc/linux_reference/test/jpeg
EXT_INC += -I../lib_enc/source/camstab
EXT_INC += -I../lib_enc/source/common
EXT_INC += -I../lib_enc/source/hevc
EXT_INC += -I../lib_enc/source/jpeg
EXT_INC += -I.
EXT_INC += -Idrv
EXT_INC += -Idrv/bsp
EXT_INC += -Idrv/clk
EXT_INC += -Idrv/clk/linux
EXT_INC += -Idrv/gpio
EXT_INC += -Idrv/i2c
EXT_INC += -Idrv/isp/3915/kernel/include
EXT_INC += -Idrv/isp/3915/kernel/include/linux
EXT_INC += -Idrv/isp/3915/rts_camera
EXT_INC += -Idrv/isp/3915/rts_camera/linux
EXT_INC += -Idrv/isp/3915/rts_camera/media
EXT_INC += -Idrv/mtd
EXT_INC += -Idrv/mtd/uboot/drivers/mtd/spi
EXT_INC += -Idrv/mtd/uboot/drivers/spi
EXT_INC += -Idrv/mtd/uboot/include
EXT_INC += -Idrv/reset
EXT_INC += -Idrv/rlx
EXT_INC += -Idrv/rlx/reg
EXT_INC += -Idrv/time
EXT_INC += -Ilib
EXT_INC += -Ilib/common
EXT_INC += -Ilib/common/tlsf
EXT_INC += -Ilib/config
EXT_INC += -Ilib/video
EXT_INC += -Ilib/video/3915
EXT_INC += -Ilib/video/3915/include
EXT_INC += -Ilib/video/3915/include/linux
EXT_INC += -Irtstream/hardware/isp/hardware/include
EXT_INC += -Irtstream/hardware/isp/hardware/include/api
EXT_INC += -Irtstream/hardware/isp/hardware/include/regs
EXT_INC += -Irtstream/hardware/isp/hardware/include/regs/rts3915
EXT_INC += -Irtstream/hardware/isp/include
EXT_INC += -Irtstream/hardware/isp/include/api
EXT_INC += -Irtstream/hardware/isp/include/common
EXT_INC += -Irtstream/hardware/isp/isp_algo_lib
EXT_INC += -Irtstream/hardware/isp/modules/include
EXT_INC += -Irtstream/hardware/isp/proto
EXT_INC += -Irtstream/hardware/isp/proto/nanopb
EXT_INC += -Irtstream/hardware/isp/test
EXT_INC += -Irtstream/hardware/isp/test/ctrls
EXT_INC += -Irtstream/hardware/md2/include
EXT_INC += -Irtstream/hardware/osd/ewl
EXT_INC += -Irtstream/hardware/osd/include
EXT_INC += -Irtstream/hardware/osd/src
EXT_INC += -Irtstream/include
EXT_INC += -Irtstream/media
EXT_INC += -Irtstream/media/include
EXT_INC += -Irtstream/media/video/md2
EXT_INC += -Irtstream/media/video/osd2
EXT_INC += -Irtstream/utils/librtscamkit/include
EXT_INC += -Irtstream/utils/librtsutils/include
EXT_INC += -Irtstream/utils/librtsv4l2/include
EXT_INC += -Ishare/common
EXT_INC += -Ishare/config
EXT_INC += -Ishare/ispfw
EXT_INC += -Isys
EXT_INC += -I../../video_enc
EXT_INC += -I../../video_olt
EXT_INC += -I../../../wlan/realtek/include
EXT_INC += -I../../../wlan/realtek/include/byteorder
EXT_INC += -I../../../wlan/realtek/src/hci
EXT_INC += -I../../../wlan/realtek/src/hci/gspi
EXT_INC += -I../../../wlan/realtek/src/hci/lxbus
EXT_INC += -I../../../wlan/realtek/src/hci/sdio
EXT_INC += -I../../../wlan/realtek/src/osdep
EXT_INC += -I../../../wlan/realtek/src/osdep/freertos
EXT_INC += -I../../../../../mbed-hal/hal
EXT_INC += -I../../../../../mbed-hal/hal_ext
EXT_INC += -I../../../../../mbed-hal/targets/hal/rtl8735b
EXT_INC += -I../../../../../os/freertos_v2020/freertos_v202012.00/include
EXT_INC += -I../../../../../os/freertos_v2020/freertos_v202012.00/portable/GCC/ARM_CM33_NTZ/non_secure
EXT_INC += -I../../../../../os/freertos_v2020/include
EXT_INC += -I../../../../../os/utilities/include
EXT_INC += -I../../../../../source/ft2/include
EXT_INC += -I../../../../../source/video_demo
EXT_INC += -I../../../../../source/video_demo/osd
EXT_INC += -I../../../../../sw/app/file_system/dct
EXT_INC += -I../../../../../sw/app/file_system/drivers/sdio/realtek/sdio_host/inc
EXT_INC += -I../../../../../sw/app/file_system/fatfs/disk_if/inc
EXT_INC += -I../../../../../sw/app/file_system/fatfs/fatfs/source
EXT_INC += -I../../../../../sw/app/rtl_printf/include
EXT_INC += -I../../../../../sw/app/shell
EXT_INC += -I../../../../../sw/app/stdio_port
EXT_INC += -I../../../../../sw/lib/api/platform
EXT_INC += -I../../../../../sw/lib/api/wifi/rtw_wpa_supplicant/src/crypto
EXT_INC += -I../../../../../sw/lib/api/wifi/rtw_wpa_supplicant/src/utils
EXT_INC += -I../../../../../sw/lib/network/ssl/mbedtls-2.4.0/include/mbedtls
EXT_INC += -I../../../wlan/realtek/wlan_func_stubs/rom
EXT_INC += -I../../../wlan/realtek/wlan_ram_map/rom
EXT_INC += -I../../../../../os/freertos/freertos_v10.1.1/secure
EXT_INC += -I../../../../../os/freertos_v2020/freertos_v202012.00/portable/GCC/ARM_CM33/secure
EXT_INC += -I../../../../../sw/app/shell/rom_ns
EXT_INC += -I../../../../../sw/app/xmodem/rom
EXT_INC += -I../../../../../sw/lib/api/wifi/rtw_wpa_supplicant/src/crypto/rom
EXT_INC += -I../../../../../sw/lib/api/wifi/rtw_wpa_supplicant/src/tls/rom
EXT_INC += -I../../../../../sw/lib/api/wifi/rtw_wpa_supplicant/src/utils/rom
EXT_INC += -I../../../../../sw/lib/application/apple/WACServer/External/Curve25519
EXT_INC += -I../../../../../sw/lib/application/apple/apple_func_stubs/rom
EXT_INC += -I../../../../../sw/lib/application/apple/homekit/crypto/ed25519
EXT_INC += -I../../../../../sw/lib/application/apple/homekit/crypto/ed25519/core
EXT_INC += -I../../../../../sw/lib/application/apple/homekit/crypto/sha512
EXT_INC += -I../../../../../sw/lib/audio/faac/libfaac/rom
EXT_INC += -I../../../../../sw/lib/network/ssl/ssl_func_stubs/rom
EXT_INC += -I../../../../../sw/lib/network/ssl/ssl_ram_map/rom

OBJS = 



CPPSOURCES = 

LIBS=

OBJ_LIST =

all: $(OBJS) obj_copy post_process
%.o:%.c
	$(CC) $(EXT_CC) $(EXT_INC) $< -o $@
	@cp -f $@ $(OBJCOPYDIR);

%.o:%.S
	$(AS) $< -o $@
	@-cp -f $@ $(OBJCOPYDIR);



build_lib:
	$(AR) crv $(LIBOUTDIR)/$(OUTLIB) $(OBJS);
	for f in $(OBJ_LIST); do \
		if [ -a $(OBJOUTDIR)/$$f ];\
		then\
			rm $(OBJOUTDIR)/$$f; \
		fi;\
	done


obj_copy:


post_process:
	@-mv -f *.s $(OBJCOPYDIR) &> /dev/null || true;
	@-mv -f *.i $(OBJCOPYDIR) &> /dev/null || true;


clean:


-include $(patsubst %.o,%.d,$(OBJS))
