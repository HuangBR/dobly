#include "common.h"

void outb(u16 port, u8 value)
{
    __asm__ volatile ("out %%dx, %%al" : : "a"(port), "d"(value));
}

u8 inb(u16 port)
{
    u8 value;
    __asm__ volatile ("in %0, %%al" : "=r"(value) : "a"(port) );
    return value;
}

void outw(u16 port, u16 value)
{
    __asm__ volatile ("out %%ax, %%dx"
            :
            : "a"(value), "d"(port)
            );
}

u16 inw(u16 port)
{
    u16 value;
    __asm__ volatile ("in %%dx %%ax"
            : "=a"(value)
            : "=d"(port)
            );
    return value;
}