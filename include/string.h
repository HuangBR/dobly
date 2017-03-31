#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#define _HAVE_ARCH_STRLEN
static inline size_t strlen(const char *s)
{
    register int n __asm__ ("ecx") = 0xffffffff;

    __asm__ volatile (
            "cld\n\t"
            "repnz scasb\n\t"
            "notl %0\n\t"
            "decl %0"
            : "=&c" (n), "=&D" (s)
            : "0" (n), "1" (s), "a" (0)
            : "memory", "cc"
            );

    return n;
}

#define _HAVE_ARCH_STRNLEN
static inline size_t strnlen(const char * s, size_t count)
{
    register int __res;

    __asm__ __volatile__(
            "movl %1,%0\n\t"
            "jmp 2f\n"
            "1:\tcmpb $0,(%0)\n\t"
            "je 3f\n\t"
            "incl %0\n"
            "2:\tdecl %2\n\t"
            "cmpl $-1,%2\n\t"
            "jne 1b\n"
            "3:\tsubl %1,%0"
            :"=a" (__res)
            :"c" (s),"d" (count)
        );

    return __res;
}

#define _HAVE_ARCH_MEMCPY
static inline void *memcpy(void *dest, void *src, size_t n)
{
    __asm__ volatile (
            "cld\n\t"
            "rep\n\t"
            "movsb"
            :"=&c" (n), "=&S" (src), "=&D" (dest)
            : "" (n), "1" (src), "2" (dest)
            : "memory"
        );

    return dest;
}

#define _HAVE_ARCH_MEMSET
static inline void *memset(void *dest, unsigned char c, size_t n)
{
    __asm__("cld\n\t"
            "rep stos"
            : "=&c" (n), "=&D" (dest)
            : "" (n), "1" (dest), "a" (c)
            : "memory", "ax"
           );
    return dest;
}

#endif /* _STRING_H */
