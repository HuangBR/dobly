#ifndef _IO_H
#define _IO_H

#include "types.h"

static inline void outb(u16 port, u8 value)
{
    __asm__ volatile ("out %%al, %%dx" 
            : 
            : "a"(value), "d"(port));
}

static inline u8 inb(u16 port)
{
    u8 value;
    __asm__ volatile ("in %%dx, %%al" 
            : "=a"(value) 
            : "d"(port) );
    return value;
}

static inline void outw(u16 port, u16 value)
{
    __asm__ volatile ("out %%ax, %%dx"
            :
            : "a"(value), "d"(port)
            );
}

static inline u16 inw(u16 port)
{
    u16 value;
    __asm__ volatile ("in %%dx, %%ax"
            : "=a"(value)
            : "d"(port)
            );
    return value;
}

#endif /* _IO_H */
