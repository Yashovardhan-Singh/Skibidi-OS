#include "pic.h"

#define PIC1_CMD  0x20  // Master PIC command port
#define PIC1_DATA 0x21  // Master PIC data port
#define PIC2_CMD  0xA0  // Slave PIC command port
#define PIC2_DATA 0xA1  // Slave PIC data port

#define ICW1_INIT 0x11  // Initialize PIC
#define ICW4_8086 0x01  // 8086/88 mode

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

// I/O port helpers (assuming utils.h or elsewhere defines these)
u8 inb(u16 port) {
    u8 ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(u16 port, u8 val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
