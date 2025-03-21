#include "utils.h"
#include "size.h"

#include "idt.h"
#include "pic.h"

static u16 cursor = 0;

void kernel_main() {
    PICInit();
    IDTInit(cursor); // Move before PICEnableIrq to ensure IDT is ready
    PICEnableIrq(0);

    i32 color = vga_attrib(FG_BLUE, BG_GREEN);
    clear_color(color);
    print("Checking ISR32...\n", color, &cursor);

    asm("int $32"); // Manual interrupt

    asm("sti"); // Enable interrupts

    for(;;);
}