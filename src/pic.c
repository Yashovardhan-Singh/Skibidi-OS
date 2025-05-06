#include "pic.h"

void PICInit(void) {
    // Save current masks
    u8 pic1_mask = inb(PIC1_DATA);
    u8 pic2_mask = inb(PIC2_DATA);

    // ICW1: Start initialization
    outb(PIC1_CMD, ICW1_INIT);
    outb(PIC2_CMD, ICW1_INIT);

    // ICW2: Remap IRQs to IDT vectors (32-47)
    outb(PIC1_DATA, 0x20); // Master PIC: IRQs 0-7 to 32-39
    outb(PIC2_DATA, 0x28); // Slave PIC: IRQs 8-15 to 40-47

    // ICW3: Tell master PIC about slave at IRQ2 (bit 2)
    outb(PIC1_DATA, 0x04); // Master: IRQ2 connected to slave
    outb(PIC2_DATA, 0x02); // Slave: ID 2

    // ICW4: Set 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Restore masks (or set to 0 to enable all for now)
    outb(PIC1_DATA, pic1_mask);
    outb(PIC2_DATA, pic2_mask);
}

void PICEnableIrq(u8 irq) {
    u16 port = (irq < 8) ? PIC1_DATA : PIC2_DATA;
    u8 mask = inb(port);
    if (irq >= 8) irq -= 8;
    mask &= ~(1 << irq); // Clear bit to enable IRQ
    outb(port, mask);
}

