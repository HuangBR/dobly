#ifndef _IDT_H
#define _IDT_H

/* Suitable irq bases for hardware interrupts.  Reprogram the 8259(s) from
 * the PC BIOS defaults since the BIOS doesn't respect all the processor's
 * reserved vectors (0 to 31).
 */
#define BIOS_IRQ0_VEC   0x08    /* base of IRQ0-7 vectors used by BIOS */
#define BIOS_IRQ8_VEC   0x70    /* base of IRQ8-15 vectors used by BIOS */
#define IRQ0_VECTOR     0x50    /* nice vectors to relocate IRQ0-7 to */
#define IRQ8_VECTOR     0x70    /* no need to move IRQ8-15 */

/* Interrupt number to hardware vector. */
#define BIOS_VECTOR(irq)        \
            (((irq) < 8 ? BIOS_IRQ0_VEC : BIOS_IRQ8_VEC) + ((irq) & 0x07))
#define VECTOR(irq)     \
            (((irq) < 8 ? IRQ0_VECTOR : IRQ8_VECTOR) + ((irq) & 0x07))


/*
 * Interrupt types
 */

#define INT_0 0x8E00     /* 1000111000000000 = present,ring0,int_gate */
#define INT_3 0xEE00     /* 1110111000000000 = present,ring3,int_gate */

/* system segment types bits */
#define STS_TG      0x5 /* task gate */
#define STS_IG16    0x6 /* 16-bits interrupt gate */
#define STS_TG16    0x7 /* 16-bits trap gate */

#define STS_IG32    0xE /* 32-bits interrupt gate */
#define STS_TG32    0xF /* 32-bits trap gate */

typedef void (*interrupt_func_t) ();

struct gate_desc_struct {
    u32 low_offset : 16;  /* low 16 bits of offset in segment */ 
    u32 cs : 16;          /* code segment selector */
    u32 resv : 5;        /* reserve 0 for traps and interrupt */
    u32 args : 3;         /* # args, 0 for traps and interrupt */
    u32 type : 4;         /* types task gate, interrupt gate or trap gate */
    u32 s : 1;            /* must be 0(system) */
    u32 dpl : 2;          /* descriptor privelege level */
    u32 p : 1;            /* segment present flag */
    u32 high_offset : 16; /* high 16 bits of offset in segment */
};

struct idtr_struct {
    u16 limit;
    struct gate_desc_struct *base;
} __attribute__ ((packed));

void lidt();
void add_interrupt(int , interrupt_func_t, u8, u8);

#endif /* _IDT_H */
