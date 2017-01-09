#include <types.h>
#include <io.h>
#include <pic.h>

void remap_pic(int pic1, int pic2)
{
    u8 md, sd;

    md = inb(PIC1_DATA);
    sd = inb(PIC2_DATA);

    outb(PIC1_CMD, EOI);      /* send EOI reset the chip */

    outb(PIC1_CMD, ICW1_INIT + ICW1_ICW4); /* starts the initialization sequence (in cascade mode) */
    outb(PIC2_CMD, ICW1_INIT + ICW1_ICW4);

    outb(PIC1_DATA, pic1); /* ICW2: Master PIC vector offset */
    outb(PIC2_DATA, pic2); /* ICW2: Slave PIC vector offset  */

    outb(PIC1_DATA, 0x04); /* ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) */
    outb(PIC2_DATA, 0x02); /* ICW3: tell Slave PIC its cascade identity (0000 0010) */

    outb(PIC1_DATA, ICW4_8086); /* ICW4 */
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

