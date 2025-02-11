OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(kernel_main)

SECTIONS
{
    . = 0x7E00;  /* Kernel entry point */

    .text ALIGN(512) : {
        *(.text)
    }

    .rodata ALIGN(512) : {
        *(.rodata)
    }

    .data ALIGN(512) : {
        *(.data)
    }

    .bss ALIGN(512) : {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    }

    . = ALIGN(512);
}
