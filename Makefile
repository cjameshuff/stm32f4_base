
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

#******************************************************************************

EXECNAME = stm_base

INCLUDES += -Isrc
INCLUDES += -Isrc/CMSIS/Include
INCLUDES += -Isrc/STM32F4xx_StdPeriph_Driver/inc

# VPATH = . src

SOURCE = src/main.c
SOURCE += src/startup_stm32f4xx.s
SOURCE += src/delay.c
SOURCE += src/system_stm32f4xx.c
SOURCE += src/int_stm32f4.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/misc.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
# SOURCE += src/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c

#******************************************************************************

CORE = cortex-m4

DEFINES = -DCORE=40 -DSAVE_FPU
# DEFINES += -DHSE_VALUE=8000000
DEFINES += -DUSE_STDPERIPH_DRIVER
# DEFINES += -DDATA_IN_ExtSRAM
# DEFINES += -DVECT_TAB_SRAM

AFLAGS = -mthumb -mcpu=$(CORE) $(INCLUDES)
CFLAGS = -mthumb -mcpu=$(CORE) -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu99 -Wall -Wno-unused -g -Os
CFLAGS += $(DEFINES) $(INCLUDES)

LIBS = -lm -lc -lnosys 

LDFLAGS = -mthumb -mcpu=$(CORE)
LDFLAGS += -nodefaultlibs -nostartfiles
LDFLAGS += -Wl,-Map,$(EXECNAME).map
LDFLAGS += -Wl,--gc-sections
LDSCRIPT = stm32f4.ld

#******************************************************************************
# Generate lists of object and dependency files
#******************************************************************************
CSOURCES = $(filter %.c,$(SOURCE))
CPPSOURCES = $(filter %.cpp,$(SOURCE))
ASMSOURCES = $(filter %.s,$(SOURCE))

OBJECTS = $(addprefix obj/, $(CSOURCES:.c=.c.o)) \
          $(addprefix obj/, $(CPPSOURCES:.cpp=.cpp.o)) \
          $(addprefix obj/, $(ASMSOURCES:.s=.s.o))

DISASM = $(addprefix disasm/, $(CSOURCES:.c=.c.s)) \
          $(addprefix disasm/, $(CPPSOURCES:.cpp=.cpp.s)) \
          $(addprefix disasm/, $(ASMSOURCES:.s=.s.s))

# DEPENDFILES = $(OBJECTS:.o=.d)

LIBGCC = ${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC = ${shell ${CC} ${CFLAGS} -print-file-name=libc.a}

#******************************************************************************
# Dependency rules
#******************************************************************************

.PHONY: all default clean very_clean depend echo none disasm

default: $(EXECNAME).elf Makefile

install:

very_clean:

clean:
	rm -rf obj
	rm -rf deps
	rm -f $(EXECNAME).elf
	rm -f $(EXECNAME).bin
	rm -f $(EXECNAME).map


$(EXECNAME).elf: $(OBJECTS)
	$(LD) -T ${LDSCRIPT} ${LDFLAGS} -o $@ $(OBJECTS) $(LIBS) '${LIBC}' '${LIBGCC}'


disasm: $(DISASM)
	arm-none-eabi-objdump -d $(EXECNAME).elf >disasm/$(EXECNAME).s

flash:
	arm-none-eabi-objcopy -O binary $(EXECNAME).elf $(EXECNAME).bin
	st-flash write $(EXECNAME).bin 0x08000000

obj/%.c.o: %.c
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.cpp.o: %.cpp
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.s.o: %.s
	$(shell if [ ! -d $(addprefix obj/, $(dir $<)) ]; then mkdir -p $(addprefix obj/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -c $< -o $@


disasm/%.c.s: %.c
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

disasm/%.cpp.s: %.cpp
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

disasm/%.s.s: %.s
	$(shell if [ ! -d $(addprefix disasm/, $(dir $<)) ]; then mkdir -p $(addprefix disasm/, $(dir $<)); fi )
	$(CC) $(CFLAGS) -S $< -o $@

#******************************************************************************
# Dependency-generating rules
#******************************************************************************

ifneq ($(MAKECMDGOALS),clean)
-include $(addprefix deps/, $(subst .c,.c.d,$(CSOURCES)))
-include $(addprefix deps/, $(subst .cpp,.cpp.d,$(CPPSOURCES)))
-include $(addprefix deps/, $(subst .s,.s.d,$(ASMSOURCES)))
endif

deps/%.c.d: %.c
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

deps/%.cpp.d: %.cpp
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

deps/%.s.d: %.s
	$(shell if [ ! -d $(addprefix deps/, $(dir $<)) ]; then mkdir -p $(addprefix deps/, $(dir $<)); fi )
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#******************************************************************************
# End of file
#******************************************************************************
