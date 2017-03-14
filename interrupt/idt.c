#include "types.h"
#include "idt.h"
#include "interrupts.h"

struct idtr_struct idtr;
struct gate_desc_struct idt[256];

void lidt()
{
    idtr.limit = 256 * sizeof(struct gate_desc_struct) - 1,
    idtr.base  = idt;

    struct idtr_struct *pidtr = &idtr;

    __asm__ volatile ("LIDT (%0) ":: "r" (pidtr));
}

/*
 * @num: interrupt vector
 * @handler: handler address
 * @istrap: 1 for a trap(exception) and 0 for interrupt 
 * @dpl: descriptor privilege level
 *
 */
void add_interrupt(int num, interrupt_func_t handler, u8 is_trap, u8 dpl)
{
    u32 offset = (u32) handler;
    
    num--;
    idt[num].low_offset   = (u16)(offset & 0xffff);
    idt[num].cs = 0x8;
    idt[num].resv = 0;
    idt[num].args = 0;
    idt[num].type = is_trap ? STS_TG32 : STS_IG32;
    idt[num].dpl = dpl;
    idt[num].s   = 0;
    idt[num].p = 1;
    idt[num].high_offset = (u16)(offset >> 16);
}
