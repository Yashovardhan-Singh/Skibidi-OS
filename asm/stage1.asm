bits 32

; So that it always gets set at 0x7e00
section .text.entry

    ; Exports
    global _start           ; Export the entry symbol

    ; Imports
    extern kernel_main      ; Kernel entry, from C
    extern IDTInit          ; IDT init
    extern PICInit          ; Program PIC
    extern PICEnableIrq     ; Enable IRQs

_start:
    cli                     ; Clear interrupts

    call PICInit            ; Remap PIC (pic.h)
    call IDTInit            ; Initialise IDT and load (idt.h)

    push 0                  ; IRQ 0
    call PICEnableIrq       ; Enable IRQ 0
    add esp, 4              ; Clean stack

    push 1                  ; IRQ 1
    call PICEnableIrq       ; Enable IRQ 1
    add esp, 4              ; Clean stack

    sti                     ; Store interrupts

    call kernel_main        ; Call kernel
    jmp $                   ; Hang? idk, it's just a fallback