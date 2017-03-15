#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef uint pde_t;

typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef unsigned int size_t;

enum {
    false = 0,
    true  = 1
};

#undef  NULL
#define NULL ((void*)0)

typedef uint bool;

#endif /* _TYPES_H */
