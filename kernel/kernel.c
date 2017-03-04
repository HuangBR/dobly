#include <types.h>
#include <idt.h>
#include <pic.h>
#include <interrupts.h>
#include "traps.h"
#include "drivers/screen.h"

//void int_32(void);

void main()
{
    clear_screen();
    
    print("kernel is loaded \n");

    cli();
    
    remap_pic(0x20, 0x28);
    mask_irq(IRQ_ALL);
    print("8259 pic remapped\n");

    trap_init();
    print("interruptions loaded\n");

    add_interrupt(48, int32, STS_IG32, 3);
    set_cursor(get_screen_offset(30, 15));
    lidt();
    print("IDT installed\n");

    sti();

    print("welcome to dobly's world\n");
loop:
//    goto loop;
//    __asm__("int $48");

out:
    goto out;
    return;
}

void int_32()
{
    // clear_screen();
    print("test_int called\n");
}

