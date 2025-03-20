#include "utils.h"
#include "size.h"

#include "idt.h"
#include "pic.h"

static u16 cursor = 0;

void kernel_main() {

    IDTInit();

    PICInit();
    PICEnableIrq(0);

    // asm("sti");    // NIGHTMARE
    asm("int $32");

    i32 color_scheme = vga_attrib(FG_BLUE, BG_GREEN);
    clear_color(color_scheme);
    print("Hello guys drink tea", color_scheme, &cursor);
    for (;;);
}
