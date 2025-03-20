ASM_DIR := asm
OUT_DIR := out
OBJ_DIR := out/obj
ISO_DIR := out/iso

MKDIR := mkdir -p
CC = i686-elf-gcc
LD = i686-elf-ld
NASM = nasm
QEMU = qemu-system-i386

BOOTLOADER = $(OUT_DIR)/boot.bin
KERNEL_ELF = $(OUT_DIR)/kernel.elf
KERNEL_BIN = $(OUT_DIR)/kernel.bin
ISO_IMAGE = $(OUT_DIR)/os.iso

NFLAGS = -f bin
QFLAGS = -drive format=raw,file=$(ISO_IMAGE)
LDFLAGS = -m elf_i386 -Tbuild/linker.ld

CCFLAGS = -m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+= -Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+= -nostdlib -nostdinc -ffreestanding -fno-pic -fno-stack-protector
CCFLAGS+= -fno-builtin-function -fno-builtin

KERNEL_C_SRC = $(wildcard src/*.c)
BOOT_ASM_SRC = $(filter-out asm/boot.asm, $(wildcard asm/*.asm))
KERNEL_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(KERNEL_C_SRC))
BOOT_OBJS = $(patsubst asm/%.asm,$(OBJ_DIR)/%.o,$(BOOT_ASM_SRC))

default: clean run
.PHONY: default

$(OBJ_DIR)/%.o: src/%.c | pre-config
	$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: asm/%.asm
	$(NASM) $< -o $@ -f elf32

pre-config:
	@$(MKDIR) $(OUT_DIR) $(OBJ_DIR)
.PHONY: pre-config

bootloader:
	echo $(BOOT_ASM_SRC)
	$(NASM) $(ASM_DIR)/boot.asm -o $(BOOTLOADER) $(NFLAGS)
.PHONY: bootloader

run: iso
	qemu-system-i386 $(QFLAGS)
.PHONY: run

kernel: $(KERNEL_OBJS) $(BOOT_OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_ELF) $^
	objcopy -O binary out/kernel.elf out/kernel.bin
.PHONY: kernel

iso: pre-config bootloader kernel
	dd if=/dev/zero of=$(ISO_IMAGE) bs=512 count=129
	dd if=$(BOOTLOADER) of=$(ISO_IMAGE) bs=512 count=1 seek=0 conv=notrunc
	dd if=$(KERNEL_BIN) of=$(ISO_IMAGE) bs=512 count=5 seek=1 conv=notrunc
.PHONY: iso

clean:
	rm -rf $(OUT_DIR)
.PHONY: clean