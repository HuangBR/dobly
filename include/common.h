#ifndef _COMMON_H
#define _COMMON_H

typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

void outb(u16, u8);
u8   inb(u16);

void outw(u16, u16);
u16  inw(u16);

#endif /* _COMMON_H */

