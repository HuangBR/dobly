#include <types.h>
#include <string.h>
#include <io.h>
#include "pic.h"

void intr_init()
{
    u8 md, sd;

    /* remap interrupt to 0x20 */
    md = inb(PIC1_DATA);
    sd = inb(PIC2_DATA);

    outb(PIC1_CMD, ICW1_INIT + ICW1_ICW4); /* starts the initialization sequence (in cascade mode) */
    outb(PIC2_CMD, ICW1_INIT + ICW1_ICW4);

    outb(PIC1_DATA, IRQ0_VECTOR); /* ICW2: new Master PIC vector offset */
    outb(PIC2_DATA, IRQ8_VECTOR); /* ICW2: new Slave PIC vector offset  */

    outb(PIC1_DATA, 0x04); /* ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) */
    outb(PIC2_DATA, 0x02); /* ICW3: tell Slave PIC its cascade identity (0000 0010) */

    outb(PIC1_DATA, ICW4_8086); /* ICW4  fully nested mode, non-buffered mode, normal EOI, IA processor*/
    outb(PIC2_DATA, ICW4_8086);

    /* restore interrupt mask register */
    outb(PIC1_DATA, md);
    outb(PIC2_DATA, sd);

    /* End of interrupt */
    outb(PIC1_CMD, EOI);
    outb(PIC2_CMD, EOI);

    /* copy BIOS vectors to  new location, so we can still make BIOS call*/
#if BIOS_IRQ0_VEC != IRQ0_VECTOR
    memcpy((void *) (BIOS_VECTOR(0) * 4), (void *) (VECTOR(0) * 4), 4 * 8);
#endif

#if  BIOS_IRQ8_VEC != IRQ8_VECTOR
    memcpy((void *) (BIOS_VECTOR(8) * 4), (void *) (VECTOR(8) * 4), 4 * 8);
#endif

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

