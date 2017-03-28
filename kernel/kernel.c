#include <types.h>
#include <string.h>
#include <dev/screen.h>
#include "idt.h"
#include "pic.h"
#include "traps.h"

void main()
{
    clear_screen();
    
    print("kernel is loaded \n");

    cli();
    
    intr_init();
    mask_irq(IRQ_ALL);
    print("8259 pic remapped\n");

    trap_init();
    printk("interruptions initialize finished\n");

    lidt();
    printk("IDT loaded\n");

    sti();

    printk("welcome to dobly's world\n");

    // __asm__ ("int $0x03\n");

    printk("version %d %s", 1, "beta");


out:
    goto out;
    return;
}

