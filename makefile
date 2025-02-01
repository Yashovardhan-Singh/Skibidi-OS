# Linux only
# Needs rework

ASM_DIR := asm
OUT_DIR := out

MKDIR := mkdir -p

NASM = nasm
QEMU = qemu-system-i386

BIN = $(OUT_DIR)/boot.bin

NFLAGS = -f bin
QFLAGS = -drive format=raw,file=$(BIN)

default: pre-config bootloader run

pre-config:
	@if [ ! -d "$(OUT_DIR)" ]; then \
		$(MKDIR) $(OUT_DIR); \
	fi
.PHONY: pre-config

bootloader:
	nasm $(ASM_DIR)/boot.asm -o $(BIN) $(NFLAGS)
.PHONY: bootloader

run:
	qemu-system-i386 $(QFLAGS)
.PHONY: run
