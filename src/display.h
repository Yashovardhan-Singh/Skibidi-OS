#pragma once

#include "colors.h"
#include "utils.h"

void print(char* msg, i32 attrib, u16* cursor);
void clear_screen();
void clear_color(i32 attrib);
i32 vga_attrib(FgColor fg, BgColor bg);