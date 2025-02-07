void _start() {
    unsigned short* VGA_MEMORY = (unsigned short*) (0xb8000);
    char msg[13] = "Hello, World!";
    for (int i = 0; i < 13; i++) {
        VGA_MEMORY[i] = (0b0011010 << 8 | msg[i]);
    }
    for (;;);
}