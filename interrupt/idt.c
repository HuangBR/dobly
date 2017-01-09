#include "types.h"
#include "idt.h"
#include "interrupts.h"

struct idtr_struct idtr;
struct gate_desc_struct idt[256];

void lidt()
{
    idtr.limit = 256 * (sizeof(struct gate_desc_struct) - 1),
    idtr.base  = idt;

    __asm__ volatile ("LIDT (%0)":: "p"(&idtr));
}

/*
 * @num: interrupt vector
 * @handler: interrupt handler
 * @dpl: descriptor privilege level
 *
 */
void add_interrupt(int num, interrupt_func_t handler, u8 type, u8 dpl)
{
    u32 offset = (u32) handler;

    idt[num].low_offset   = (offset & 0xffff);
    idt[num].cs = 0x80;
    idt[num].resv = 0;
    idt[num].args = 0;
    idt[num].type = type;
    idt[num].dpl = dpl;
    idt[num].s   = 0;
    idt[num].p = 1;
    idt[num]. high_offset = (offset >> 16);
}
