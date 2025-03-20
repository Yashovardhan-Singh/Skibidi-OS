#include "idt.h"

IDTEntry idt[256];
IDTPointer idtp;

void IDTSetGate(u8 num, u32 base, u16 sel, u8 flags) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
}

void IDTInit() {
    idtp.limit = (sizeof(IDTEntry) * 256) - 1;
    idtp.base = (u32) &idt;

    // memset(idt, 0, sizeof(IDTEntry) * 256);
    for (int i = 0; i < 256; i++) {
        IDTSetGate(i, 0, 0, 0); // Null entries initially
    }

    IDTSetGate(0, (u32) isr0, 0x08, 0x8e);

    __asm__ volatile ("lidt %0" : : "m" (idtp));
}

void InterruptHandler(u32 *esp) {
    u32 int_num = esp[10];
    if (int_num >= 32 && int_num <= 47) { // PIC IRQs
        if (int_num >= 40) // Slave PIC
            outb(0xA0, 0x20); // Send EOI to slave
        outb(0x20, 0x20); // Send EOI to master
    }
    // Add debug (e.g., print int_num) later
    // __asm__ volatile ("hlt");
}