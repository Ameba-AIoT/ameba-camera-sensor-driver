ifeq ($(shell uname), Linux)

ifeq ($(tc), pico)
ASDK_DIR = /toolchain/asdk-10.3.1/linux/picolibc
else
ASDK_DIR = /toolchain/asdk-10.3.0/linux/newlib
endif
else

ifeq ($(tc), pico)
ASDK_DIR = /asdk-10.3.1/mingw32/picolibc
else
ASDK_DIR = /asdk-10.3.0/mingw32/newlib
endif
endif

CC	= $(ASDK_DIR)/bin/arm-none-eabi-gcc  
AR	= $(ASDK_DIR)/bin/arm-none-eabi-ar
AS	= $(ASDK_DIR)/bin/arm-none-eabi-gcc
LD	= $(ASDK_DIR)/bin/arm-none-eabi-gcc 
NM	= $(ASDK_DIR)/bin/arm-none-eabi-nm
STRIP	= $(ASDK_DIR)/bin/arm-none-eabi-strip
OBJDUMP	= $(ASDK_DIR)/bin/arm-none-eabi-objdump
OBJCOPY	= $(ASDK_DIR)/bin/arm-none-eabi-objcopy
CC_SIZE	= $(ASDK_DIR)/bin/arm-none-eabi-size

export CC AR AS LD NM STRIP OBJDUMP OBJCOPY CC_SIZE

fpu = soft

ROOT_DIR		= ../../../..
VOE_BIN_DIR		= $(ROOT_DIR)/hal/rtl8735b/lib/source/ram/video/voe_bin

release	= n

LD_FLAGS =
LD_FLAGS += -march=armv8-m.main
LD_FLAGS += -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=$(fpu)
LD_FLAGS += -nostartfiles -nodefaultlibs -nostdlib
ifeq ($(tc), pico)
LD_FLAGS += --specs=picolibc.specs --oslib=semihost -DPICOLIBC_INTEGER_PRINTF_SCANF
else
LD_FLAGS += --specs=nosys.specs 
endif
LD_FLAGS += -Wl,-Map=text.map  
LD_FLAGS += -u sensor_entry
LD_FLAGS += -O 

ifeq ($(tc), pico)
LD_LIB  = -lm -lc -lsemihost
else
LD_LIB  = -lm -lc -lnosys
endif

EXT_CC 	=
EXT_CC	+= -march=armv8-m.main -mthumb -mcmse -mfpu=fpv5-sp-d16 -mfloat-abi=$(fpu) -D__thumb2__  
EXT_CC  += -g -gstrict-dwarf -gdwarf-3
EXT_CC	+= -fdata-sections -ffunction-sections 
EXT_CC	+= -fdiagnostics-color=always 
EXT_CC	+= -Wall -Wpointer-arith -Wstrict-prototypes -Wundef  
EXT_CC  += -Wno-write-strings -Wno-maybe-uninitialized
EXT_CC  += -fno-exceptions -fno-optimize-sibling-calls 
EXT_CC	+= -DCONFIG_VOE_PLATFORM=1 
EXT_CC 	+= -DBUILD_WITHOUT_VOE=1
EXT_CC	+= -Os
EXT_CC	+= -c

#assign rtos_dir : freertos_v2020, freertos
rtos_dir = freertos

EXT_INC = 
EXT_INC += -I. 
EXT_INC	+= -Iinclude
EXT_INC	+= -I../include
EXT_INC	+= -I../cmsis/voe/include
EXT_INC	+= -I../cmsis/cmsis-core/include
ifeq ($(rtos_dir), freertos)
EXT_CC		+= -DV8M_STKOVF
EXT_INC		+= -I../os/freertos
EXT_INC		+= -I../os/freertos/freertos_v10.1.1/include 
EXT_INC		+= -I../os/freertos/freertos_v10.1.1/portable/GCC/ARM_RTL8735B_VOE
else
EXT_INC		+= -I../os/freertos_v2020 
EXT_INC		+= -I../os/freertos_v2020/freertos_v202012.00/include 
EXT_INC		+= -I../os/freertos_v2020/freertos_v202012.00/portable/GCC/ARM_CM33_NTZ/non_secure
endif

vpath %.c realtek/fixp
vpath %.c realtek/rs0551c
vpath %.c realtek/pseudo
vpath %.c realtek/tof
vpath %.c realtek/yuv
vpath %.c gc/gc1084
vpath %.c gc/gc2053
vpath %.c gc/gc2083
vpath %.c gc/gc2093
vpath %.c gc/gc3003
vpath %.c gc/gc4023
vpath %.c gc/gc4103
vpath %.c gc/gc4653
vpath %.c gc/gc4663
vpath %.c gc/gc4693
vpath %.c gc/gc5035
vpath %.c gc/gc5603
vpath %.c pst/ps5258
vpath %.c pst/ps5262
vpath %.c pst/ps5268
vpath %.c pst/ps5270
vpath %.c pst/ps5420
vpath %.c sony/imx307
vpath %.c sony/imx471
vpath %.c sony/imx681
vpath %.c sony/imx327
vpath %.c sony/imx662
vpath %.c sony/imx775
vpath %.c smartsens/sc2336
vpath %.c smartsens/sc2310
vpath %.c smartsens/sc231h
vpath %.c smartsens/sc2333
vpath %.c smartsens/sc301
vpath %.c smartsens/sc3336
vpath %.c smartsens/sc5356
vpath %.c smartsens/sc400ai
vpath %.c smartsens/sc450ai
vpath %.c smartsens/sc485sl
vpath %.c samsung/hm6s
vpath %.c imagedesign/mis2008
vpath %.c jx/k05
vpath %.c jx/f37
vpath %.c jx/f35
vpath %.c jx/f38
vpath %.c jx/f51
vpath %.c jx/f53
vpath %.c jx/f55
vpath %.c jx/f57
vpath %.c jx/k351
vpath %.c jx/k06a
vpath %.c jx/k306p
vpath %.c omnivision/ov50a40
vpath %.c omnivision/ov50e40
vpath %.c omnivision/ov50m40
vpath %.c omnivision/os04a10
vpath %.c omnivision/os04d10
vpath %.c omnivision/os04e10
vpath %.c omnivision/os02h10
vpath %.c omnivision/ov13b10
vpath %.c omnivision/ov12890
vpath %.c omnivision/ov2735
vpath %.c omnivision/ov5647
vpath %.c omnivision/ov5693
vpath %.c omnivision/ov9734
vpath %.c st/vd550g
vpath %.c novatek/nt99236
vpath %.c cv/cv2003

SENSOR = $(shell echo $(sensor) | tr a-z A-Z)
OBJS =  

OBJS += sensor_entry.o

ifeq ($(sensor), tof)
OBJS += sensor_tof_mipi.o
endif

ifeq ($(sensor), gc2053)
OBJS += sensor_gc2053_mipi.o
endif

ifeq ($(sensor), gc2083)
OBJS += sensor_gc2083_mipi.o
endif

ifeq ($(sensor), gc2093)
OBJS += sensor_gc2093_mipi.o
endif

ifeq ($(sensor), gc1084)
OBJS += sensor_gc1084_mipi.o
endif

ifeq ($(sensor), gc3003)
OBJS += sensor_gc3003_mipi.o
endif

ifeq ($(sensor), yuv)
OBJS += sensor_yuv_mipi.o
endif

ifeq ($(sensor), gc4023)
OBJS += sensor_gc4023_mipi.o
endif

ifeq ($(sensor), gc4103)
OBJS += sensor_gc4103_mipi.o
endif

ifeq ($(sensor), gc4653)
OBJS += sensor_gc4653_mipi.o
endif

ifeq ($(sensor), gc4663)
OBJS += sensor_gc4663_mipi.o
endif

ifeq ($(sensor), gc4693)
OBJS += sensor_gc4693_mipi.o
endif

ifeq ($(sensor), gc5035)
OBJS += sensor_gc5035_mipi.o
endif

ifeq ($(sensor), gc5603)
OBJS += sensor_gc5603_mipi.o
endif

ifeq ($(sensor), hm6s)
OBJS += sensor_hm6s_mipi.o
endif

ifeq ($(sensor), ov50a40)
OBJS += sensor_ov50a40_mipi.o
endif

ifeq ($(sensor), ov50e40)
OBJS += sensor_ov50e40_mipi.o
endif

ifeq ($(sensor), ov50m40)
OBJS += sensor_ov50m40_mipi.o
endif

ifeq ($(sensor), os04a10)
OBJS += sensor_os04a10_mipi.o
endif

ifeq ($(sensor), os04e10)
OBJS += sensor_os04e10_mipi.o
endif

ifeq ($(sensor), os04d10)
OBJS += sensor_os04d10_mipi.o
endif

ifeq ($(sensor), os02h10)
OBJS += sensor_os02h10_mipi.o
endif

ifeq ($(sensor), ov13b10)
OBJS += sensor_ov13b10_mipi.o
endif

ifeq ($(sensor), ov13b10_12m)
OBJS += sensor_ov13b10_mipi_full.o
endif

ifeq ($(sensor), ov13b10_12m_seq)
OBJS += sensor_ov13b10_mipi_seq.o
endif

ifeq ($(sensor), ov12890)
OBJS += sensor_ov12890_mipi.o
endif

ifeq ($(sensor), ov12890_12m)
OBJS += sensor_ov12890_mipi_full.o
endif

ifeq ($(sensor), ov12890_12m_seq)
OBJS += sensor_ov12890_mipi_seq.o
endif

ifeq ($(sensor), ov2735)
OBJS += sensor_ov2735_mipi.o
endif

ifeq ($(sensor), ov9734)
OBJS += sensor_ov9734_mipi.o
endif

ifeq ($(sensor), ov5693)
OBJS += sensor_ov5693_mipi.o
endif

ifeq ($(sensor), ov5647)
OBJS += sensor_ov5647_mipi.o
endif

ifeq ($(sensor), ps5258)
OBJS += sensor_ps5258_mipi.o
endif

ifeq ($(sensor), ps5262)
OBJS += sensor_ps5262_mipi.o
endif

ifeq ($(sensor), ps5268)
OBJS += sensor_ps5268_mipi.o
endif

ifeq ($(sensor), ps5270)
OBJS += sensor_ps5270_mipi.o
endif

ifeq ($(sensor), ps5420)
OBJS += sensor_ps5420_mipi.o
endif

ifeq ($(sensor), imx307)
OBJS += sensor_imx307_mipi.o
endif

ifeq ($(sensor), imx307_hdr)
OBJS += sensor_imx307_mipi_HDR.o
endif

ifeq ($(sensor), imx327)
OBJS += sensor_imx327_mipi.o
endif

ifeq ($(sensor), imx662)
OBJS += sensor_imx662_mipi.o
endif

ifeq ($(sensor), imx775)
OBJS += sensor_imx775_mipi.o
endif

ifeq ($(sensor), imx471)
OBJS += sensor_imx471_mipi.o
endif

ifeq ($(sensor), imx681)
OBJS += sensor_imx681_mipi.o
endif
ifeq ($(sensor), imx681_12m)
OBJS += sensor_imx681_mipi_full.o
endif

ifeq ($(sensor), imx681_12m_seq)
OBJS += sensor_imx681_mipi_seq.o
endif

ifeq ($(sensor), sc2336)
OBJS += sensor_sc2336_mipi.o
endif

ifeq ($(sensor), sc2310)
OBJS += sensor_sc2310.o
endif

ifeq ($(sensor), sc2333)
OBJS += sensor_sc2333_mipi.o
endif

ifeq ($(sensor), sc231h)
OBJS += sensor_sc231h_mipi.o
endif

ifeq ($(sensor), sc301)
OBJS += sensor_sc301_mipi.o
endif

ifeq ($(sensor), sc400ai)
OBJS += sensor_sc400ai_mipi.o
endif

ifeq ($(sensor), sc450ai)
OBJS += sensor_sc450ai_mipi.o
endif

ifeq ($(sensor), sc485sl)
OBJS += sensor_sc485sl_mipi.o
endif

ifeq ($(sensor), sc3336)
OBJS += sensor_sc3336_mipi.o
endif

ifeq ($(sensor), sc5356)
OBJS += sensor_sc5356_mipi.o
endif

ifeq ($(sensor), mis2008)
OBJS += sensor_mis2008_mipi.o
endif

ifeq ($(sensor), k05)
OBJS += sensor_k05_mipi.o
endif

ifeq ($(sensor), f35)
OBJS += sensor_f35_mipi.o
endif

ifeq ($(sensor), f37)
OBJS += sensor_f37_mipi.o
endif

ifeq ($(sensor), f38)
OBJS += sensor_f38_mipi.o
endif

ifeq ($(sensor), f51)
OBJS += sensor_f51_mipi.o
endif

ifeq ($(sensor), f53)
OBJS += sensor_f53_mipi.o
endif

ifeq ($(sensor), f55)
OBJS += sensor_f55_mipi.o
endif

ifeq ($(sensor), f57)
OBJS += sensor_f57_mipi.o
endif

ifeq ($(sensor), k06a)
OBJS += sensor_k06a_mipi.o
endif

ifeq ($(sensor), k306p)
OBJS += sensor_k306p_mipi.o
endif

ifeq ($(sensor), k351)
OBJS += sensor_k351_mipi.o
endif

ifeq ($(sensor), vd550g)
OBJS += sensor_vd550g_mipi.o
endif

ifeq ($(sensor), nt99236)
OBJS += sensor_nt99236_mipi.o
endif

ifeq ($(sensor), cv2003)
OBJS += sensor_cv2003_mipi.o
endif

ifeq ($(sensor), fixp2K)
OBJS += sensor_fixp2K.o
endif

ifeq ($(sensor), fixp)
OBJS += sensor_fixp.o
endif

ifeq ($(sensor), fixp5M)
OBJS += sensor_fixp5M.o
endif

.PHONY: all clean obj image
all: all_sensor

check:
	echo $(OBJS)
	echo $(EXT_CC)
	echo $(EXT_INC)

obj: $(OBJS)

%.o:%.c
	@sed -i 's/	ENABLE/	DISABLE/g' include/rts_isp_sensor_lib.h
	@sed -i '/#define _$(SENSOR)_SENSOR_/ s/DISABLE/ENABLE/g' include/rts_isp_sensor_lib.h
	@echo [CC] $<
	@$(CC) $(EXT_CC) $(EXT_INC) $< -o $@


%.o:%.S
	$(AS) $< -o $@


clean:
	-rm -f *.o *.i *.d *.s *.su;
		
image: obj
	if [ ! -d build ]; then mkdir build; fi
	$(LD) $(LD_FLAGS) $(OBJS) $(LD_LIB) -T rtl8735b_voe.ld -L. -o sensor.axf
	$(OBJCOPY) -j .sensor -Obinary sensor.axf sensor_ddr.bin
	$(OBJDUMP) -d sensor.axf > build/sensor_$(sensor).asm
	python ./gen_sensor_bin.py
	mv sensor.bin build/sensor_$(sensor).bin
	mv text.map build/sensor_$(sensor).map
	cp build/sensor_$(sensor).bin ../output/sensor.bin
	cp build/sensor_$(sensor).bin ../output/sensor_$(sensor).bin
	mv build/sensor_$(sensor).map ../output/sensor_$(sensor).map
#	@if [ $(release) == 'n' ];	then\
#		cp ../output/sensor_$(sensor).bin $(VOE_BIN_DIR)/sensor.bin;\
#		cp ../output/sensor_$(sensor).bin $(VOE_BIN_DIR)/sensor_$(sensor).bin;\
#	fi

all_sensor:
	make sensor=gc2053 image
	make sensor=gc2083 image
	make sensor=gc2093 image
	make sensor=gc4653 image
	make sensor=gc4023 image
	make sensor=gc4663 image
	make sensor=gc4693 image
	make sensor=sc231h image
	make sensor=sc2333 image
	make sensor=sc2336 image
	make sensor=sc2310 image
	make sensor=sc400ai image
	make sensor=sc450ai image
	make sensor=sc485sl image
	make sensor=f35 image
	make sensor=f37 image
	make sensor=f38 image
	make sensor=f53 image
	make sensor=f55 image
	make sensor=f57 image
	make sensor=imx327 image
	make sensor=imx662 image
	make sensor=ps5258 image
	make sensor=ps5268 image
	make sensor=mis2008 image
	make sensor=ov13b10_12m image
	make sensor=ov13b10_12m_seq image
	make sensor=ov12890 image
	make sensor=ov12890_12m image
	make sensor=ov12890_12m_seq image
	make sensor=gc5035 image
	make sensor=vd550g image
	make sensor=gc1084 image