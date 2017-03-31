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

    printk("");

    // __asm__ ("int $0x03\n");

    char *s = "welcome to dobly's world";
    char info[512];
    size_t n = strlen(s);
    memset(info, '\0', 512);
    memcpy(info, s, n); 
    printk("%s %n  version: %d beta", info, n, 1);


out:
    goto out;
    return;
}

