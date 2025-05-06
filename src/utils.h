#pragma once

// Unsinged integers
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed integers
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

// Size integers
typedef u32 usize;
typedef u32 uintptr;

// Float and double
typedef float f32;
typedef double f64;

// Ah yes, 8 bit boolean for storing 0/1
typedef unsigned char boolean;

// uintptr too verbose
typedef unsigned long ptr;

// Just in case
#define true (1)
#define false (0)

// NEED NULL
#define NULL ((void *)0)

// asm macro
#ifndef asm
#define asm __asm__ volatile
#endif

// no padding
#define PACKED __attribute__((packed))

// PIC constants
#define PIC1_CMD  0x20  // Master PIC command port
#define PIC1_DATA 0x21  // Master PIC data port
#define PIC2_CMD  0xA0  // Slave PIC command port
#define PIC2_DATA 0xA1  // Slave PIC data port

#define ICW1_INIT 0x11  // Initialize PIC
#define ICW4_8086 0x01  // 8086/88 mode

// Display constants
#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// memset
static inline void *memset(void *ptr, u8 value, usize n) {
    u8 *p = (u8*) ptr;
    while (n--) *p++ = (unsigned char) value;
    return p;
}

// memcpy
static inline void *memcpy(void* dst, const void* src, usize n) {
    u8 *d = dst;
    const u8 *s = src;
    while(n-- > 0) *d++ = *s++;
    return d;
}

// strlen
static inline usize strlen(char* msg) {
    usize len = 0;
    while (*(msg++) != 0) len++;
    return len;
}

static u8 inb(u16 port) {
    u8 ret;
    asm("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static void outb(u16 port, u8 val) {
    asm("outb %0, %1" : : "a"(val), "Nd"(port));
}