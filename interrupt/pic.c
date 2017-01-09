#include <types.h>
#include <io.h>
#include "pic.h"

void remap_pic(int pci1, int pci2)
{
    u8 md, sd;

    md = inb(PIC1_DATA);
    sd = inb(PIC2_DATA);

    outb(PIC1_, EOI);      /* send EOI reset the chip */

    outb(PIC1_, ICW1_INIT + ICW1_ICW4);
    outb(PIC2_, ICW1_INIT + ICW1_ICW4);

    outb(PIC1_DATA, pic1);
    outb(PIC2_DATA, pic2);

    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, md);
    outb(PIC2_DATA, sd);
}

void mask_irq(u8 irq)
{
    u16 port;
    u8 value;
    if (irq == IRQ_ALL) {
        outb(PIC1_DATA, 0xFF);
        outb(PIC2_DATA, 0xFF);
    } else {
        if(irq < 8)
            port = PIC1_DATA;
        else {
            port = PIC2_DATA;
            irq -= 8;
        }
        value = inb(port) | (1 << irq);
        outb(port, value);
    }
}

void umask_irq(u8 irq)
{
    u16 port;
    u8 value;
    if(irq == IRQ_ALL) {
        outb(PIC1_DATA, 0x00);
        outb(PIC2_DATA, 0x00);
    } else {
        if(irq < 8) {
            port = PIC1_DATA;
        } else {
            port = PIC2_DATA;
            irq -= 8;
        }

        value = inb(port) & ~(1 << irq);
        outb(port, value);
    }
}
