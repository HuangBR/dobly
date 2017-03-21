#include <types.h>
#include <idt.h>
#include <pic.h>
#include <interrupts.h>
#include "traps.h"
#include "drivers/screen.h"

void main()
{
    clear_screen();
    
    print("kernel is loaded \n");

    cli();
    
    intr_init();
    mask_irq(IRQ_ALL);
    print("8259 pic remapped\n");

    trap_init();
    print("interruptions initialize finished\n");

    lidt();
    print("IDT loaded\n");

    sti();

    print("welcome to dobly's world\n");

    __asm__ ("int $0x03\n");

out:
    goto out;
    return;
}

