#include <types.h>
#include <idt.h>
#include <pic.h>
#include <interrupts.h>
#include "traps.h"
#include "drivers/screen.h"

void int_32(void);

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

    for(int i = 0; i < 255; i++){
        add_interrupt(i, int32, STS_IG32, 3);
    }
    lidt();
    print("IDT installed\n");

    sti();

    print("welcome to dobly's world\n");

    __asm__ ("pushl %ebx            \n"
            "pushf                  \n"
            "movl %esp, %ebx        \n"
            "orl $0x0100, (%ebx)    \n"
            "popf                   \n"
            "popl %ebx                "
            );
    __asm__("int $0");

out:
    goto out;
    return;
}

void int_32()
{
    __asm__ ("sti");
    print("test_int called\n");
}

