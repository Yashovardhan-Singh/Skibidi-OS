bits 32

section .text

extern InterruptHandler

%macro ISR_NO_ERR 1
global isr%1
isr%1:
    cli
    push dword 0
    push dword %1
    jmp IsrCommon
%endmacro

%macro ISR_ERR 1
global isr%1
isr%1:
    cli
    push dword %1
    jmp IsrCommon
%endmacro

IsrCommon:
    pusha
    push ds
    push es
    push gs
    push fs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax

    push esp
    call InterruptHandler
    pop esp

    pop fs
    pop gs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; global isr32
; isr32:
;     cli
;     iret

%assign i 0
%rep 256
    %if i in (8, 10, 11, 12, 13, 14, 17)
        ISR_ERR i
    %else
        ISR_NO_ERR i
    %endif
    %assign i i+1
%endrep