#pragma once

#include "idt.h"

#define PIC1_CMD  0x20  // Master PIC command port
#define PIC1_DATA 0x21  // Master PIC data port
#define PIC2_CMD  0xA0  // Slave PIC command port
#define PIC2_DATA 0xA1  // Slave PIC data port

#define ICW1_INIT 0x11  // Initialize PIC
#define ICW4_8086 0x01  // 8086/88 mode

void PICInit(void);
void PICEnableIrq(u8 irq);

// I/O port helpers (assuming utils.h or elsewhere defines these)
u8 inb(u16 port);
void outb(u16 port, u8 val);