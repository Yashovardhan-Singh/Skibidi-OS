// Kernel entry

#include "test.h"

void kernel_main() {
    unsigned short* VGA_MEMORY = (unsigned short*) (0xb8000);
    
    // Message to print
    char msg[11] = "SKIBIDI OS";
    int j = 0;
    
    // Clear background
    for (int i = 0; i < 2000; i++) VGA_MEMORY[i] = 0b0011010 << 8;
    
    pts(VGA_MEMORY, msg);
    
    // Forever loop
    for (;;);
}
