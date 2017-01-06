#ifndef _IDT_H
#define _IDT_H

#include "common.h"

/*
 * Interrupt types
 */

#define INT_0 0x8E00     /* 1000111000000000 = present,ring0,int_gate */
#define INT_3 0xEE00     /* 1110111000000000 = present,ring3,int_gate */

typedef void (*interrupt_func_t) ();

struct idt_desc_struct {
    u16 low_offset;
    u16 selector;
    u16 settings;
    u16 high_offset;
} __attribute__ ((packed));

struct idtr_struct {
    u16 limit;
    struct idt_desc_struct *base;
} __attribute__ ((packed));

void load_idtr();
void add_interrupt(int , interrupt_func_t, u32);

#endif /* _IDT_H */
