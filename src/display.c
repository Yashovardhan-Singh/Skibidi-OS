#include "display.h"

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

void update_cursor() {
    u16 pos = cursor_y * SCREEN_WIDTH + cursor_x;

    outb(0x3D4, 0x0F);           // Cursor low byte
    outb(0x3D5, (pos & 0xFF));
    outb(0x3D4, 0x0E);           // Cursor high byte
    outb(0x3D5, ((pos >> 8) & 0xFF));
}

// Basic character output function
void putchar(char c, FgColor fg, BgColor bg) {
    volatile unsigned char* video = (volatile unsigned char*)VIDEO_MEMORY;
    unsigned int offset = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
    u8 attribute = (bg << 4) | (fg & 0x0F);
    
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        video[offset] = c;          // Character
        video[offset + 1] = attribute;  // Color attribute
        cursor_x++;
    }
    
    // Handle line wrap and scrolling
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= SCREEN_HEIGHT) {
        // Simple scroll up
        for (int i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; i++) {
            video[i] = video[i + SCREEN_WIDTH * 2];
        }
        // Clear last line
        for (int i = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH * 2; 
             i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i += 2) {
            video[i] = ' ';
            video[i + 1] = attribute;
        }
        cursor_y = SCREEN_HEIGHT - 1;
    }
    
    update_cursor();
}

void print_hex(unsigned char value, FgColor fg, BgColor bg) {
    const char hex_digits[] = "0123456789ABCDEF";
    char hex_str[5];
    
    hex_str[0] = '0';
    hex_str[1] = 'x';
    hex_str[2] = hex_digits[(value >> 4) & 0xF];
    hex_str[3] = hex_digits[value & 0xF];
    hex_str[4] = '\0';
    
    for (int i = 0; hex_str[i]; i++) {
        putchar(hex_str[i], fg, bg);
    }
}