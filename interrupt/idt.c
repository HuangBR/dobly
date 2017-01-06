#include "idt.h"
#include "interrupts.h"

struct idtr_struct idtr;
struct idt_desc_struct idt[256];

void load_idtr()
{
    idtr.limit = 256 * (sizeof(struct idt_desc_struct) - 1),
    idtr.base  = idt;

    __asm__ volatile ("LIDT (%0)":: "p"(&idtr));
}

/*
 * @num: interrupt vector
 * @handler: interrupt handler
 * @dpl: descriptor privilege level
 *
 */
void add_interrupt(int num, interrupt_func_t handler, u32 dpl)
{
    u16 selector = 0x08;
    u16 settings;
    u16 offset = (u32) handler;

    __asm__ __volatile__ ("movw %%cs, %0" : "=g" (selector));

    switch(dpl)
    {
        case 0: 
            settings = INT_0;
            break;
        case 1:
        case 2:
        case 3:
            settings = INT_3;
            break;
        default:
            return;
    }

    idt[num].low_offset   = (offset & 0xffff);
    idt[num].selector     = selector;
    idt[num].settings     = settings;
    idt[num]. high_offset = (offset >> 16);
}
