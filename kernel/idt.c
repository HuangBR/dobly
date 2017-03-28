#include "types.h"
#include "idt.h"

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
 * @num: interrupt vector 0-255
 * @handler: handler address
 * @type: STS_TG32 for expection and STS_IG32 for interrupt
 * @dpl: descriptor privilege level
 *
 */
void set_gate(int num, void *handler, u8 type, u8 dpl)
{
    u32 offset = (u32) handler;
    
    idt[num].low_offset   = (u16)(offset & 0xffff);
    idt[num].cs = 0x8;
    idt[num].resv = 0;
    idt[num].args = 0;
    idt[num].type = type;
    idt[num].dpl = dpl;
    idt[num].s   = 0;
    idt[num].p = 1;
    idt[num].high_offset = (u16)(offset >> 16);
}
