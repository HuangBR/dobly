#ifndef _PIC_H
#define _PIC_H


/* Suitable irq bases for hardware interrupts.  Reprogram the 8259(s) from
 * the PC BIOS defaults since the BIOS doesn't respect all the processor's
 * reserved vectors (0 to 31).
 */
#define BIOS_IRQ0_VEC   0x08    /* base of IRQ0-7 vectors used by BIOS */
#define BIOS_IRQ8_VEC   0x70    /* base of IRQ8-15 vectors used by BIOS */
#define IRQ0_VECTOR     0x20    /* nice vectors to relocate IRQ0-7 to */
#define IRQ8_VECTOR     0x28    /* no need to move IRQ8-15 */

/* Interrupt number to hardware vector. */
#define BIOS_VECTOR(irq)        \
            (((irq) < 8 ? BIOS_IRQ0_VEC : BIOS_IRQ8_VEC) + ((irq) & 0x07))
#define VECTOR(irq)     \
            (((irq) < 8 ? IRQ0_VECTOR : IRQ8_VECTOR) + ((irq) & 0x07))

/*
 *  IRQ macros
 */
#define IRQ_ALL     0xFF
#define TIMER       0x0
#define KEYBOARD    0x1
#define CASCADE     0x2
#define COM2_4      0x3
#define COM1_3      0x4
#define LPT         0x5
#define FLOPPY      0x6
#define FREE7       0x7
#define CLOCK       0x8
#define FREE9       0x9
#define NIC         0xA
#define USB         0xB
#define PS2MOUSE    0xC
#define COPROC      0xD
#define IDE_1       0xE
#define IDE_2       0xF

/*
 *  PIC macros
 *  Master: PIC chip 1
 *  Slave: PIC chip 2
 */
#define PIC1        0x20
#define PIC1_CMD    PIC1
#define PIC1_DATA   0x21
#define PIC2        0xA0
#define PIC2_CMD    PIC2
#define PIC2_DATA   0xA1
#define EOI         0x20

/*
 * ICW1 and ICW4 control words are the only ones we have to worry about
 */
#define ICW1_ICW4       0x01               /* there IS an ICW4 control word */
#define ICW1_SINGLE     0x02               /* only PIC1 (not cascaded) */
#define ICW1_INTERVAL4  0x04               /* Call address interval 4 (8) */
#define ICW1_EDGE       0x08               /* edge triggered IRQs */
#define ICW1_INIT       0x10               /* required for PIC initialisation */

#define ICW4_8086       0x01               /* 80/86 Mode */
#define ICW4_AEOI       0x02               /* Auto EOI */
#define ICW4_PIC1       0x04               /* this is the Master PIC */
#define ICW4_BUF_SLAVE  0x08               /* Buffered Mode  slave */
#define ICW4_BUF_MASTER 0x0C               /* Buffered Mode  master */
#define ICW4_SFNM       0x10               /* Special Fully Nested Mode */

void intr_init(void);
void mask_irq(BYTE irq);
void umask_irq(BYTE irq);

static inline void sti(void)
{
    __asm__ ("sti");
}

static inline void cli(void)
{
    __asm__ ("cli");
}

#endif /* _PIC_H */
