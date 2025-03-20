bits 32

; So that it always gets set at 0x7e00
section .text.entry
    global _start           ; Export the entry symbol
    global LoadIdt

    extern kernel_main      ; Kernel entry, from C

_start:
    cli                     ; Clear interrupts
    call kernel_main        ; Call kernel
    jmp $                   ; Hang? idk, it's just a fallback