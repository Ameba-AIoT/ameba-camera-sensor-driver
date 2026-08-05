
# select toolchain
ifeq ($(shell uname), Linux)

ifeq ($(tc), pico)
ASDK_DIR = /toolchain/asdk-10.3.1/linux/picolibc
else
ASDK_DIR = /toolchain/asdk-10.3.0/linux/newlib
#ASDK_DIR = /toolchain/asdk-10.3.1/linux/newlib
endif
else

ifeq ($(tc), pico)
ASDK_DIR = /asdk-10.3.1/mingw32/picolibc
else
ASDK_DIR = /asdk-10.3.0/mingw32/newlib
endif
endif


export ASDK_DIR 

CC	    = $(ASDK_DIR)/bin/arm-none-eabi-gcc  
AR		= $(ASDK_DIR)/bin/arm-none-eabi-ar
AS		= $(ASDK_DIR)/bin/arm-none-eabi-gcc
LD		= $(ASDK_DIR)/bin/arm-none-eabi-gcc 
NM		= $(ASDK_DIR)/bin/arm-none-eabi-nm
STRIP	= $(ASDK_DIR)/bin/arm-none-eabi-strip
OBJDUMP	= $(ASDK_DIR)/bin/arm-none-eabi-objdump
OBJCOPY	= $(ASDK_DIR)/bin/arm-none-eabi-objcopy
CC_SIZE	= $(ASDK_DIR)/bin/arm-none-eabi-size

export CC AR AS LD NM STRIP OBJDUMP OBJCOPY CC_SIZE

#assign build system view: y, n
dbg 	= n
#assign build relese: y, n
release	= n
sensor	= gc2053

#assign rtos_dir : freertos_v2020, freertos
rtos_dir = freertos

#assign fpu : soft, softfp, hard
fpu = soft

MKDIR	= mkdir

ROOT_DIR		= ../../..
LIB_DIR			= ./lib
OUTPUT_DIR		= ./output

ENC_LIB_DIR		= $(ROOT_DIR)/hal/rtl8735b/verify/video/lib_enc
VOE_BIN_DIR		= $(ROOT_DIR)/hal/rtl8735b/lib/source/ram/video/voe_bin
HAL_VIDEO_DIR	= $(ROOT_DIR)/hal/rtl8735b/lib/source/ram/video
HAL_INCLUDE_DIR	= $(ROOT_DIR)/hal/rtl8735b/lib/include

LD_FLAGS = -march=armv8-m.main
LD_FLAGS += -mthumb -mcmse -mfpu=fpv5-sp-d16 -mfloat-abi=$(fpu)
LD_FLAGS += -nostartfiles -nodefaultlibs -nostdlib

ifeq ($(tc), pico)
LD_FLAGS += --specs=picolibc.specs --oslib=semihost -DPICOLIBC_INTEGER_PRINTF_SCANF
else
LD_FLAGS += --specs=nosys.specs 
endif
LD_FLAGS += -Wl,--gc-sections -Wl,--warn-section-align -Wl,-Map=$(OUTPUT_DIR)/text.map
LD_FLAGS += -Wl,--cref -Wl,--build-id=none -Wl,--use-blx -Wl,--cmse-implib
LD_FLAGS += -O
LD_FLAGS += -Wl,-wrap,malloc -Wl,-wrap,free -Wl,-wrap,realloc  -Wl,-wrap,calloc 
LD_FLAGS += -Wl,-wrap,printf -Wl,-wrap,puts
LD_FLAGS += -Wl,-wrap,memset -Wl,-wrap,memcpy -Wl,-wrap,memcmp -Wl,-wrap,memmove 
LD_FLAGS += -Wl,-wrap,strcpy -Wl,-wrap,strlcpy -Wl,-wrap,strncpy -Wl,-wrap,strlen
LD_FLAGS += -Wl,-wrap,strncmp -Wl,-wrap,strcmp -Wl,-wrap,strchr
LD_FLAGS  += -fno-exceptions

ifeq ($(tc), pico)
LD_LIB  = -lm -lc -lsemihost
else
LD_LIB  = -lm -lc -lnosys
endif


EXT_CC	= -march=armv8-m.main -mthumb -mcmse -mfpu=fpv5-sp-d16 -mfloat-abi=$(fpu) -D__thumb2__  
EXT_CC  += -g -gstrict-dwarf -gdwarf-3
EXT_CC	+= -D__ARM_ARCH_8M_MAIN__=1 -DARM_MATH_ARMV8MML
EXT_CC	+= -fdata-sections -ffunction-sections 
EXT_CC	+= -fdiagnostics-color=always 
EXT_CC	+= -Wall -Wpointer-arith -Wstrict-prototypes -Wundef  
EXT_CC  += -Wno-write-strings -Wno-maybe-uninitialized
EXT_CC  += -fno-exceptions -fno-optimize-sibling-calls
 
EXT_CC	+= -Os
EXT_CC	+= -c
#EXT_CC	+= -Werror
#EXT_CC	+= -save-temps -MMD -fstack-usage

ifneq ($(fpu), soft)
EXT_CC	+= -D__ARMVFP__
endif


# ENC related  
EXT_CC	+= -DCTBRC_STRENGTH -DVIDEOSTAB_ENABLED  
EXT_CC	+= -DCONFIG_VOE_PLATFORM=1



LINK_LIBS	= $(LIB_DIR)/lib3A.a
LINK_LIBS	+= $(LIB_DIR)/voe.a
LINK_LIBS	+= $(LIB_DIR)/voe_enc.a
LINK_LIBS	+= $(LIB_DIR)/voe_isp.a
LINK_LIBS	+= $(LIB_DIR)/voe_sensor.a

EXT_INC		=
EXT_INC		+= -Icmsis/cmsis-core/include
EXT_INC		+= -Icmsis/voe/include
EXT_INC		+= -Icmsis
EXT_INC		+= -Ihal

ifeq ($(rtos_dir), freertos)
EXT_CC		+= -DV8M_STKOVF
EXT_INC		+= -Ios/freertos
EXT_INC		+= -Ios/freertos/freertos_v10.1.1/include 
EXT_INC		+= -Ios/freertos/freertos_v10.1.1/portable/GCC/ARM_RTL8735B_VOE
else
EXT_INC		+= -Ios/freertos_v2020 
EXT_INC		+= -Ios/freertos_v2020/freertos_v202012.00/include 
EXT_INC		+= -Ios/freertos_v2020/freertos_v202012.00/portable/GCC/ARM_CM33_NTZ/non_secure
endif

EXT_INC		+= -Iinclude

EXT_INC		+= -I$(ISP_LIB_DIR)
EXT_INC		+= -I$(ISP_LIB_DIR)/rtstream/hardware/isp  
EXT_INC		+= -I$(ISP_LIB_DIR)/rtstream/hardware/isp/test
EXT_INC		+= -I$(ISP_LIB_DIR)/share
EXT_INC		+= -I$(ISP_LIB_DIR)/share/common
EXT_INC		+= -I$(ISP_LIB_DIR)/share/config
EXT_INC		+= -I$(ISP_LIB_DIR)/share/ispfw
EXT_INC		+= -I$(ISP_LIB_DIR)/sys

export EXT_CC

OBJS		= def.o

# lib_isp exist is release mode
ifeq (lib_isp, $(wildcard lib_isp))
ISP_LIB_DIR = lib_isp
SUBDIRS     = isp
#SUBDIRS 	+= sensor
release		= y

# release mode without lib_isp
else ifeq ($(release), y)
#SUBDIRS 	+= sensor
release		= y

# internal debug mode
else

OBJS		+= startup.o
OBJS 		+= syscalls.o
ISP_LIB_DIR	= $(ROOT_DIR)/hal/rtl8735b/verify/video/lib_isp
SUBDIRS 	=
SUBDIRS 	+= isp
SUBDIRS		+= enc
#SUBDIRS 	+= sensor
SUBDIRS 	+= voe

endif


# dbg condition 
ifeq ($(dbg), y)
sysview		= 1
gprof		= 0
else
sysview		= 0
gprof		= 0
endif

ifeq ($(sysview), 1)
# Build sysview
EXT_INC		+= -Ivoe/segger_sysview
SUBDIRS 	+= voe/segger_sysview
endif

ifeq ($(gprof), 1)
# Build gprof
EXT_INC		+= -Ivoe/gprof
EXT_INC		+= -pg
SUBDIRS 	+= voe/gprof
endif

EXT_CC		+= -DCONFIG_VERIFY_SYSVIEW=$(sysview)
EXT_CC		+= -DCONFIG_GPROF=$(gprof)

# sensor condition
#SENSOR_DIRS  =
SENSOR_DIRS  = gc4653
SENSOR_DIRS  += rs0551c rs0551c2K rs0551c4M rs0551c60fps  rs0551cft2 rs0551c1360X768 rs0551cYUV pseudo_5m pseudo_2m
SENSOR_DIRS  += verify
SENSOR_DIRS  += fixp fixp2K fixp5M fixp4M169
SENSOR_DIRS  += imx307 imx307hdr
SENSOR_DIRS  += imx327
SENSOR_DIRS  += imx471
SENSOR_DIRS  += imx681
SENSOR_DIRS  += ps5258 k05 mis2008 ps5270
SENSOR_DIRS  += sc2336 sc2310
SENSOR_DIRS  += f37
SENSOR_DIRS  += gc4023
SENSOR_DIRS  += gc4663
SENSOR_DIRS  += gc2083
SENSOR_DIRS  += gc2053

ifneq ($(sensor), all)
SENSOR_DIRS  = $(sensor)
endif


all:

ifneq ($(shell uname), Linux)
ifneq ($(release), y)
	pip list | grep 'protobuf' > check_protobuf.txt;\
	if [ ! -s check_protobuf.txt ];\
	then\
		pip install protobuf;\
	fi;\

	#make gen_pb
endif	
endif	

	@for item in $(SENSOR_DIRS); do \
		rm -rf lib/voe_sensor.a sensor/*.o; \
		make mksubdir obj obj_copy image sensor=$$item ; \
	done

.PHONY: gen_pb
gen_pb:
	make clean -C $(ISP_LIB_DIR)/rtstream/hardware/isp/proto
	make -C $(ISP_LIB_DIR)/rtstream/hardware/isp/proto




obj: $(OBJS)

image:
	if [ ! -d $(OUTPUT_DIR) ];\
	then\
		mkdir $(OUTPUT_DIR); \
	fi;\
	
	$(LD) $(LD_FLAGS)  $(LIB_DIR)/*.o -Wl,--start-group $(LIB_DIR)/*.a $(LD_LIB) -Wl,--end-group -T rtl8735b_voe.ld -L. -o $(OUTPUT_DIR)/voe.axf
	#$(LD) $(LD_FLAGS) $(LIB_DIR)/*.o -Wl,--start-group $(LIB_DIR)/*.a -Wl,--end-group -T rtl8735b_voe_full.ld -L. -o $(OUTPUT_DIR)/voe.axf
	
	#$(STRIP) --strip-unneeded $(OUTPUT_DIR)/voe.axf
	
	$(OBJDUMP)  -d $(OUTPUT_DIR)/voe.axf > $(OUTPUT_DIR)/voe.asm
	$(NM) $(OUTPUT_DIR)/voe.axf | sort > $(OUTPUT_DIR)/voe.map
	$(OBJCOPY) -j .text -j .fcs.itcm -Obinary $(OUTPUT_DIR)/voe.axf $(OUTPUT_DIR)/voeiram.bin		
	$(OBJCOPY) -j .fcs.dtcm -j .fcs.dtcm_s -j .tm_voe_share -Obinary $(OUTPUT_DIR)/voe.axf $(OUTPUT_DIR)/voedram.bin
	$(OBJCOPY) -j .bss -j .ARM.exidx -j .cmd.ddr -j .fcs.ddr -j .ddr -Obinary $(OUTPUT_DIR)/voe.axf $(OUTPUT_DIR)/voe_ddr.bin
	$(OBJCOPY) -j .symbol.ddr2 -j .enc.ddr -Obinary $(OUTPUT_DIR)/voe.axf $(OUTPUT_DIR)/voe_ddr2.bin

	$(OBJCOPY) -j .sensor -Obinary $(OUTPUT_DIR)/voe.axf $(OUTPUT_DIR)/sensor_ddr.bin
	
	@python gen_voe_bin.py
	@if [ ! -d lib_isp ] && [ $(release) == 'n' ];	then\
		cp $(OUTPUT_DIR)/voe.bin $(VOE_BIN_DIR);\
	fi;
	cp $(OUTPUT_DIR)/voe.bin $(OUTPUT_DIR)/voe_$(sensor).bin
	cp $(OUTPUT_DIR)/voe.map $(OUTPUT_DIR)/voe_$(sensor).map
	cp $(OUTPUT_DIR)/text.map $(OUTPUT_DIR)/text_$(sensor).map
	cp $(OUTPUT_DIR)/voe.asm $(OUTPUT_DIR)/voe_$(sensor).asm
	
release: mksubdir $(OBJS) obj_copy image clean
	@echo "Release build"
	@if [ ! -d lib_isp ];	then\
		cp -r $(ISP_LIB_DIR) .; \
	fi;
	rm -rf enc voe hal startup.c syscalls.c
	rm -rf .git 
	rm -rf rom
	tar zcvf ../voe.tar.gz ../source
	
mksubdir:

	@if [ $(release) == "n" ];	then\
		cp $(HAL_VIDEO_DIR)/hal_video_common.h include ; \
		cp $(HAL_VIDEO_DIR)/hal_isp.h include ; \
		cp $(HAL_VIDEO_DIR)/hal_video.h include ; \
		cp $(HAL_VIDEO_DIR)/hal_md_util.h include ; \
		cp $(HAL_VIDEO_DIR)/base_type.h include ; \
		cp $(HAL_INCLUDE_DIR)/rtl8735b_aon_type.h include ; \
		cp $(HAL_VIDEO_DIR)/gmon.h voe/gprof ; \
	fi;

	for dir in $(SUBDIRS); do \
		make -C $$dir all sysview=$(sysview) gprof=$(gprof) release=$(release) sensor=$(sensor) rtos_dir=$(rtos_dir) fpu=$(fpu) || exit "$$?"; \
	done
	
	-rm -f def.o

%.o:%.c
	$(CC) $(EXT_CC) $(EXT_INC) $< -o $@


%.o:%.S
	$(AS) $(EXT_CC) $< -o $@

obj_copy:
	@if [ ! -d $(LIB_DIR) ];\
	then\
		mkdir $(LIB_DIR); \
	fi;
	
	for dir in $(SUBDIRS); do \
		make -C $$dir obj_copy sysview=$(sysview) gprof=$(gprof) dbg=$(dbg) release=$(release) rtos_dir=$(rtos_dir) fpu=$(fpu) || exit "$$?"; \
	done
	@if [ ! -d lib_isp ];	then\
		cp -f $(OBJS) $(LIB_DIR);\
	fi;

clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean sysview=$(sysview) gprof=$(gprof) dbg=$(dbg) release=$(release) rtos_dir=$(rtos_dir) fpu=$(fpu) || exit "$$?"; \
	done
	-rm -f *.o *.i *.d *.s *.su *.a;
	-rm -rf $(OUTPUT_DIR)
	
release-clean:
	-rm -rf isp lib_isp patch os/freertos_v2020
	-rm -rf os/freertos/*.c 
	-rm -rf os/freertos/freertos_v10.1.1/*.c
	-rm -rf os/freertos/freertos_v10.1.1/secure
	-rm -rf os/freertos/freertos_v10.1.1/portable/Common
	-rm -rf os/freertos/freertos_v10.1.1/portable/MemMang
	-rm -rf os/freertos/freertos_v10.1.1/portable/ARM_RTL8735B_VOE/*.c
	-rm -f cmsis/voe/include/core_tm9_cache.h cmsis/voe/include/rtl8735b_voe_irq.h  cmsis/voe/include/rtl8735b_voe.h cmsis/voe/include/cmsis_voe.h
	-cp -f cmsis_voe.release cmsis/voe/include/cmsis_voe.h
	-rm -f include/rtl8735b_aon_type.h include/rtl8735b_uart_type.h
	-rm -f cmsis/cmsis-core/include/cmsis_compiler.h cmsis/cmsis-core/include/cmsis_version.h
		
	@sed -i '/release	= n/ s/n/y/g' Makefile

release-check:
	mkdir ../release_check
	tar zxvf ../voe.tar.gz -C ../release_check
	make -C ../release_check/source
	diff ../release_check/source/output/voe.bin  $(VOE_BIN_DIR)/voe.bin
	rm -rf ../release_check

rlscln-check:
	mkdir ../release_check
	tar zxvf ../voe.tar.gz -C ../release_check
	make -C ../release_check/source release-clean
	make -C ../release_check/source
	diff ../release_check/source/output/voe.bin  $(VOE_BIN_DIR)/voe.bin
	rm -rf ../release_check

	
lib-clean:
	-rm include/hal_video_common.h
	-rm include/hal_isp.h
	-rm include/hal_video.h
	-rm include/hal_md_util.h
	-rm include/base_type.h
	-rm include/rtl8735b_aon_type.h
	-rm voe/gprof/gmon.h
	-rm -rf $(LIB_DIR)
	
-include $(patsubst %.o,%.d,$(OBJS))

