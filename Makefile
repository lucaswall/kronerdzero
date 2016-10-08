
TARGET = kernel7.img
LIST = kernel7.list
MAP = kernel7.map

INSTALL_TARGET = /Volumes/boot/

LINKER = kernel7.ld
BUILD = build
SOURCE = source
ELF = $(BUILD)/kernel7.elf

OBJECTS_S := $(patsubst $(SOURCE)/%.s, $(BUILD)/%.o, $(wildcard $(SOURCE)/system/*.s))
OBJECTS_C := $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(wildcard $(SOURCE)/system/*.c) $(wildcard $(SOURCE)/art/*.c) $(wildcard $(SOURCE)/game/*.c))
SOURCES_C := $(shell find $(SOURCE) -name '*.c')
SOURCES_H := $(shell find $(SOURCE) -name '*.h')

ARMGNU ?= arm-none-eabi
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump
LD = $(ARMGNU)-ld
AS = $(ARMGNU)-as
CC = $(ARMGNU)-gcc

CFLAGS =  -I $(SOURCE)/system -I $(SOURCE)/art -I $(SOURCE)/game -O2 -Wall -march=armv7-a -mtune=cortex-a7 # -mfpu=vfp -mfloat-abi=hard

all: $(TARGET) $(LIST)

install: all
	cp -fv $(TARGET) config.txt $(INSTALL_TARGET)
	diskutil unmount $(INSTALL_TARGET)

$(LIST): $(ELF)
	$(OBJDUMP) -d $< > $@

$(TARGET): $(ELF)
	$(OBJCOPY) $< -O binary $@

$(ELF): $(OBJECTS_S) $(OBJECTS_C) $(LINKER)
	$(CC) -nostartfiles -nostdlib $(OBJECTS_S) $(OBJECTS_C) -lgcc -Wl,-Map,$(MAP) -o $@ -Wl,-T,$(LINKER)

$(BUILD)/%.o: $(SOURCE)/%.s
	@mkdir -p `dirname $@`
	$(AS) -I $(SOURCE)/system $< -o $@

$(BUILD)/%.o: $(SOURCE)/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/depends: $(SOURCES_C) $(SOURCES_H)
	@mkdir -p build
	$(CC) $(CFLAGS) -MM $(SOURCES_C) | sed 's/.*\.o: source\/\(.*\)\.c/build\/\1.o: source\/\1.c/g' > $@

-include $(BUILD)/depends

clean: 
	rm -rf $(BUILD)
	rm -f $(TARGET) $(LIST) $(MAP)

.PHONY: all clean install
