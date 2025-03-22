#include "utils.h"
#include "colors.h"

#include "display.h"

#include "idt.h"
#include "pic.h"

static u16 cursor = 0;

void kernel_main() {
    i32 color = vga_attrib(FG_BLUE, BG_GREEN);
    clear_color(color);
    print("Checking ISR32...\n", color, &cursor);

    for(;;);
}