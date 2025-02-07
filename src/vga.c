// Kernel entry
void _start() {
    unsigned short* VGA_MEMORY = (unsigned short*) (0xb8000);
    
    // Message to print
    char msg[11] = "SKIBIDI OS";
    int j = 0;
    
    // Clear background
    for (int i = 0; i < 2000; i++) VGA_MEMORY[i] = 0b0011010 << 8;
    
    // 990 is the perfect center for the string in VGA 80x25 mode
    // 1001 is the start of the memory address to print plus the size of string
    for (int i = 990; i < 1001; i++) VGA_MEMORY[i] = (0b0011010 << 8 | msg[j++]);
    
    // Forever loop
    for (;;);
}