PROJECT := cxx-device-model-example
LD_FILE := stm32f107vct6.ld
OPENOCD_CFG_FILE = hacked-stlinkv2-clone-via-nucleo.cfg

ASRC := \
	src/startup_stm32f10x_cl.s

CSRC := \
	src/core_cm3.c \
	src/system_stm32f10x.c \

CXXSRC := \
	src/main.cpp \

INCLUDE_DIRS := \
	include

########################

AOBJS := $(patsubst %.s, obj/%.s.o, $(ASRC))
COBJS := $(patsubst %.c, obj/%.c.o, $(CSRC))
CXXOBJS := $(patsubst %.cpp, obj/%.cpp.o, $(CXXSRC))

ADEPS := $(patsubst %.s, obj/%.s.d, $(ASRC))
CDEPS := $(patsubst %.c, obj/%.c.d, $(CSRC))
CXXDEPS := $(patsubst %.cpp, obj/%.cpp.d, $(CXXSRC))

COMMON_FLAGS := -DSTM32F10X_CL -mthumb -mcpu=cortex-m3 -O1

CFLAGS_INCLUDES := $(foreach I,$(INCLUDE_DIRS),-I $(I))
CFLAGS := $(COMMON_FLAGS) -ffunction-sections -fdata-sections -g $(CFLAGS_INCLUDES)

CXXFLAGS := \
	$(COMMON_FLAGS) \
	-ffunction-sections -fdata-sections -g \
	$(CFLAGS_INCLUDES) \
	-nostartfiles -ffreestanding -nodefaultlibs -nostdlib \
	-fno-rtti -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables

LDFLAGS_FILE := -T $(LD_FILE)
LDFLAGS := $(COMMON_FLAGS) --static -nostartfiles -Wl,--gc-sections $(LDFLAGS_FILE)

.PHONY: all clean flash

all: dist/$(PROJECT).hex

clean:
	rm -f $(AOBJS) $(COBJS) $(CXXOBJS) dist/$(PROJECT).elf dist/$(PROJECT).hex

flash: dist/$(PROJECT).hex
	openocd -f $(OPENOCD_CFG_FILE) -c "init; reset halt; flash write_image erase $<; reset run; shutdown"

gdb:
	openocd -f $(OPENOCD_CFG_FILE)

$(AOBJS): obj/%.s.o : %.s
	mkdir -p $(@D)
	arm-none-eabi-gcc -c -MMD $(CFLAGS) -o $@ $<

$(COBJS): obj/%.c.o : %.c
	mkdir -p $(@D)
	arm-none-eabi-gcc -c -MMD $(CFLAGS) -o $@ $<

$(CXXOBJS): obj/%.cpp.o : %.cpp
	mkdir -p $(@D)
	arm-none-eabi-g++ -c -MMD $(CXXFLAGS) -o $@ $<

dist/$(PROJECT).elf: $(AOBJS) $(COBJS) $(CXXOBJS)
	mkdir -p $(@D)
	arm-none-eabi-gcc -o $@ $^ $(LDFLAGS)

dist/$(PROJECT).hex: dist/$(PROJECT).elf
	mkdir -p $(@D)
	arm-none-eabi-objcopy -O ihex $< $@

-include ${ADEPS}
-include ${CDEPS}
-include ${CXXDEPS}
