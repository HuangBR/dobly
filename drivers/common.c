#include "common.h"

void outb(u16 port, u8 value)
{
    __asm__ volatile ("out %%al, %%dx" 
            : 
            : "a"(value), "dN"(port));
}

u8 inb(u16 port)
{
    u8 value;
    __asm__ volatile ("in %%dx, %%al" 
            : "=a"(value) 
            : "dN"(port) );
    return value;
}

void outw(u16 port, u16 value)
{
    __asm__ volatile ("out %%ax, %%dx"
            :
            : "a"(value), "dN"(port)
            );
}

u16 inw(u16 port)
{
    u16 value;
    __asm__ volatile ("in %%dx, %%ax"
            : "=a"(value)
            : "dN"(port)
            );
    return value;
}
