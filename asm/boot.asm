; Simple bootloader
; Stage-1 (Creating an OS)
; Volt-A-Bit, Manipal Institute of Technology

bits 16                     ; 16 Bit, starts in real mode
org 0x7c00                  ; Load from

; Entry
start:
    mov si, load_s_msg      ; Intro message
    call printstr           ; call to print

    ; Load more sectors off the disk
    mov bx, 0x0000          ; setup for ES
    mov es, bx              ; load ES with 0x0000
    mov bx, 0x7e00          ; Memory address where sectors will be stored
    mov al, 0x4             ; Number of sectors to load: 4 (512*4=512 bytes=0.5KiB)
    call readsectors        ; Call to function

    mov si, done_s_msg      ; Confirmation message
    call printstr           ; call to print

; Setup protected mode
enable_protected_mode:
    lgdt [gdt_descriptor]   ; load GDT
    lidt [idt_descriptor]   ; load IDT

    cli                     ; clear interrupts

    in al, 0x92             ; use port 0x92 (fast A20 gate)
    or al, 2                ; Set BIT 1 of A20 gate to 1
    out 0x92, al            ; Write back to port 0x92, Enabling it

    mov eax, cr0            ; Read control register 0
    or eax, 0x1             ; Set bit 0 to 1 (enable protection mode)
    mov cr0, eax            ; Write back to control register 0

    jmp 0x08:protected_mode ; Far jump to protected mode (32-Bit Land)

bits 32                     ; 32 Bit code, protected mode

; Entry for protected mode
protected_mode:

    mov ax, 0x10            ; Data to ax
    mov ds, ax              ; setup data seg
    mov ss, ax              ; stack seg
    mov es, ax              ; extra seg
    mov fs, ax              ; fs
    mov gs, ax              ; gs

    mov esp, 0x9cf00        ; stack pointer
    mov ebp, esp            ; base pointer

    ; TODO: find a better way to jump to kernel entry than memory locations
    jmp 0x8:0x7e70          ; jump to kernel

    cli
    hlt

;------------------------------
; FUNCTIONS                   |
;------------------------------

bits 16                     ; Set it back to 16 bit code

; Print messages to screen
; @parameter si: pointer to the message
printstr:
    mov ah, 0x0e            ; Set to teletype mode
    mov bx, 0x0007          ; Page 0, Set white on black
.loop:
    mov al, [si]            ; mov into al, *SI
    or al, al               ; test for null byte
    jz .exit                ; string printed
    int 0x10                ; interrupt
    inc si
    jmp .loop               ; Jump back to loop
.exit:
    call newline
    ret

; @parameter al: number of sectors to load
; @parameter es: which segment (optional, for now)
; @parameter bx: start of memory
readsectors:
    mov ah, 0x02            ; intterupt 2h    
    mov cx, 0x0002          ; high is cylinder: 0, low is sector(1 indexing): 2
    mov dx, 0x0080          ; high is sector: 0, low is disk: 0x80h (80 is first drive/HDD)
    int 0x13                ; interrupt
    jc .error               ; jump to error handling subroutine
    jmp .exit               ; return from subroutine
.error:
    mov si, err_load_s_msg  ; print error message
    call printstr           ; call print
    jmp .exit                 ; jump to end of execution
.exit: ret

; newline function
; @parameter: none
newline:
    mov ah, 0x03            ; Get cursor data
    mov bh, 0               ; Page number
    int 0x10                ; Interrupt 16/10h

    inc dh                  ; Last interrupt returned row position in DH
    mov dl, 0               ; Set to first column
    mov ah, 0x02            ; Change interrupt to move cursor
    int 0x10                ; Interrupt

    ret

;-----------------------
; DATA                 |
;-----------------------

; Message stored in memory as null terminated byte string
load_s_msg: db "Loading Sectors", 0
err_load_s_msg: db "Error loading Sectors", 0
done_s_msg: db "Loaded Sectors", 0

; Global descriptor table
gdt:
    dq 0x0000000000000000   ; Null segment, necessary,  0x00
    dq 0x00CF9A000000FFFF   ; Code segment, executable, 0x08
    dq 0x00CF92000000FFFF   ; Data segment, read/write, 0x10
.end:

; Struct for Global descriptor table metadata
gdt_descriptor:
    dw gdt.end - gdt - 1    ; size
    dd gdt                  ; offset

; Struct for Interrupt descriptor table metadata (Empty)
; No interrupts, for now
idt_descriptor:
    dw 0                    ; size
    dd 0                    ; offset


; Pad first sector with 0
; $ means current address, $$ means sector begin
; 510 bytes, first sector = 512 - (2 bytes for magic boot number) = 510
; $ - $$: size of our code, 510 - ($ - $$): size of padding
times 510 - ($ - $$) db 0
dw 0xaa55                   ; Magic number
