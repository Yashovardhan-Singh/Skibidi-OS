#include "colors.h"

int strlen(char* msg) {
    int len = 0;
    if (msg == 0) return 0;
    while (msg[len] != '\0') len++;
    return len;
}

void pts(unsigned short* mem, char* msg, int attrib, int* cursor) {
    int n = strlen(msg);
    for (int i = 0; i < n; i++) {
        if (msg[i] == '\n') {
            *cursor += 80 - (*cursor % 80);
            continue;
        }
        if (msg[i] == '\t') {
            *cursor += 4;
            continue;
        }
        mem[(*cursor)++] = (attrib << 8 | msg[i]);
    }
}

int vga_attrib(FgColor fg, BgColor bg) {
    return (bg << 4) | (fg & 0x0F);
}