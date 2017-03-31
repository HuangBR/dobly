#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

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
