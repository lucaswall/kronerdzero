
TARGET = kernel7.img
LIST = kernel7.list
MAP = kernel7.map

INSTALL_TARGET = /Volumes/boot/kernel7.img

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

all: $(TARGET) $(LIST)

install: all
	cp -fv $(TARGET) $(INSTALL_TARGET)

$(LIST): $(ELF)
	$(OBJDUMP) -d $< > $@

$(TARGET): $(ELF)
	$(OBJCOPY) $< -O binary $@

$(ELF): $(LINKER)

$(ELF): $(OBJECTS_S) $(OBJECTS_C)
	$(LD) --no-undefined $^ -Map $(MAP) -o $@ -T $(LINKER)

$(BUILD)/%.o: $(SOURCE)/%.s $(BUILD)
	$(AS) -I $(SOURCE) $< -o $@

$(BUILD)/%.o: $(SOURCE)/%.c $(BUILD)
	$(CC) -I $(SOURCE) $< -o $@

$(BUILD):
	mkdir $@

clean: 
	rm -rf $(BUILD)
	rm -f $(TARGET) $(LIST) $(MAP)

.PHONY: all clean install