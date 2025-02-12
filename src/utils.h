#pragma once

#include "colors.h"
#include "size.h"

int strlen(char* msg);
void pts(unsigned short* mem, char* msg, int attrib, int* cursor);
int vga_attrib(FgColor fg, BgColor bg);