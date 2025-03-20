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

// void *memset(void *ptr, int value, u32 num) {
//     unsigned char *p = (unsigned char *)ptr;
//     while (num--) *p++ = (unsigned char)value;
//     return ptr;
// }

#ifndef asm
#define asm __asm__ volatile
#endif  