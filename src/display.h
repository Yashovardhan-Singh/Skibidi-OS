#pragma once

#include "colors.h"
#include "utils.h"

static volatile u32 cursor_x = 0;
static volatile u32 cursor_y = 0;

void print(char* msg, i32 attrib, u16* cursor);
void clear_screen();
void clear_color(i32 attrib);
i32 vga_attrib(FgColor fg, BgColor bg);
void update_cursor();
void putchar(char c, FgColor fg, BgColor bg);
void print_hex(unsigned char value, FgColor fg, BgColor bg);