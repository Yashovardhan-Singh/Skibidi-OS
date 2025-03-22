#pragma once

#include "utils.h"

#define PACKED __attribute__((packed))

typedef struct PACKED {
    u16 offset_low;   // Lower 16 bits of ISR address
    u16 selector;     // GDT segment selector (e.g., code segment)
    u8 zero;         // Always 0
    u8 type_attr;    // Gate type and attributes (e.g., 0x8E for interrupt gate)
    u16 offset_high;
} IDTEntry;

typedef struct PACKED {
    u16 limit;
    u32 base;
} IDTPointer;

void IDTSetGate(u8 num, u32 base, u16 sel, u8 flags);
void IDTInit();
void InterruptHandler();

#include "irq.h"