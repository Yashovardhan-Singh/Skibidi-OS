ASM_DIR := asm
OUT_DIR := out
OBJ_DIR := obj

MKDIR := mkdir -p

NASM = nasm
QEMU = qemu-system-i386

BOOTLOADER = $(OUT_DIR)/boot.bin

NFLAGS = -f bin
QFLAGS = -drive format=raw,file=out/boot.iso
LDFLAGS = -m elf_i386 -Tbuild/linker.ld

CCFLAGS = -m32 -std=c11 -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+= -Wno-pointer-arith -Wno-unused-parameter
CCFLAGS+= -nostdlib -nostdinc -ffreestanding -fno-pic -fno-stack-protector
CCFLAGS+= -fno-builtin-function -fno-builtin

KERNEL_C_SRC = $(wildcard src/*.c)
KERNEL_OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(KERNEL_C_SRC))

default: iso run
.PHONY: default

$(OBJ_DIR)/%.o: src/%.c | pre-config
	gcc -o $@ -c $< $(CCFLAGS)
	rm -f src/*.o

pre-config:
	@if [ ! -d "$(OUT_DIR)" ]; then \
		$(MKDIR) $(OUT_DIR); \
	fi

	@if [ ! -d "$(OBJ_DIR)" ]; then \
		$(MKDIR) $(OUT_DIR); \
	fi
.PHONY: pre-config

bootloader:
	nasm $(ASM_DIR)/boot.asm -o $(BOOTLOADER) $(NFLAGS)
.PHONY: bootloader

run:
	qemu-system-i386 $(QFLAGS)
.PHONY: run

kernel: $(KERNEL_OBJS)
	ld -o out/kernel.bin $^ $(LDFLAGS)
.PHONY: kernel

iso: pre-config bootloader kernel
	dd if=/dev/zero of=out/boot.iso bs=512 count=5
	dd if=out/boot.bin of=out/boot.iso bs=512 count=1 seek=0 conv=notrunc
	dd if=out/kernel.bin of=out/boot.iso bs=512 count=1 seek=1 conv=notrunc
.PHONY: iso