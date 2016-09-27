
TARGET = kernel7.img
LIST = kernel7.list
MAP = kernel7.map

INSTALL_TARGET = /Volumes/boot/

LINKER = kernel7.ld
BUILD = build
SOURCE = source
ELF = $(BUILD)/kernel7.elf

OBJECTS_S := $(patsubst $(SOURCE)/%.s, $(BUILD)/%.o, $(wildcard $(SOURCE)/*.s))
OBJECTS_C := $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(wildcard $(SOURCE)/*.c))

ARMGNU ?= arm-none-eabi
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump
LD = $(ARMGNU)-ld
AS = $(ARMGNU)-as
CC = $(ARMGNU)-gcc

CCOPTS = -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7

all: $(TARGET) $(LIST)

install: all
	cp -fv $(TARGET) config.txt $(INSTALL_TARGET)

$(LIST): $(ELF)
	$(OBJDUMP) -d $< > $@

$(TARGET): $(ELF)
	$(OBJCOPY) $< -O binary $@

$(ELF): $(OBJECTS_S) $(OBJECTS_C) $(LINKER)
	$(LD) --no-undefined $(OBJECTS_S) $(OBJECTS_C) -Map $(MAP) -o $@ -T $(LINKER)

$(BUILD)/%.o: $(SOURCE)/%.s
	@mkdir -p build
	$(AS) -I $(SOURCE) $< -o $@

$(BUILD)/%.o: $(SOURCE)/%.c
	@mkdir -p build
	$(CC) $(CCOPTS) -I $(SOURCE) -c $< -o $@

clean: 
	rm -rf $(BUILD)
	rm -f $(TARGET) $(LIST) $(MAP)

.PHONY: all clean install
