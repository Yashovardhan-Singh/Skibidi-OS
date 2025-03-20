#include "colors.h"
#include "size.h"

i32 strlen(char* msg) {
    i32 len = 0;
    if (msg == 0) return 0;
    while (msg[len] != '\0') len++;
    return len;
}

void print(char* msg, i32 attrib, u16* cursor) {

    u16* mem = (u16*) (0xb8000);
    i32 n = strlen(msg);
    
    for (i32 i = 0; i < n; i++) {
        do { switch (msg[i]) {
            case '\n':
                *cursor += 80 - (*cursor % 80);
                continue;
            case '\t':
                *cursor += 4;
                continue;
        }} while(0);    // Wrapped in do while so switch can break, and continue works
        mem[(*cursor)++] = (attrib << 8 | msg[i]);
    }
}

void clear_screen() {
    u16* mem = (u16*) (0xb8000);
    for (i32 i = 0; i < 2000; i++) mem[i] = vga_attrib(FG_WHITE, BG_BLACK);
}

void clear_color(i32 attrib) {
    u16* mem = (u16*) (0xb8000);
    for (i32 i = 0; i < 2000; i++) mem[i] = (attrib << 8) | ' ';
}

i32 vga_attrib(FgColor fg, BgColor bg) {
    return (bg << 4) | (fg & 0x0F);
}