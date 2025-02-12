#include "utils.h"

static int cursor = 0;

__attribute__((section(".text.entry")))
void kernel_main() {
    unsigned short* VGA_MEMORY = (unsigned short*) (0xb8000);
    
    for (int i = 0; i < 2000; i++) VGA_MEMORY[i] = vga_attrib(FG_WHITE, BG_BLACK);
    
    pts(VGA_MEMORY, "HELLO,\tBRO  \n", vga_attrib(FG_WHITE, BG_BLACK), &cursor);
    pts(VGA_MEMORY, "HELLO,\tBRO 2\n", vga_attrib(FG_WHITE, BG_BLACK), &cursor);
    pts(VGA_MEMORY, "HELLO,\tBRO 3\n", vga_attrib(FG_WHITE, BG_BLACK), &cursor);
    
    // Forever loop
    for (;;);
}