#include <string.h>

#ifndef _HAVE_ARCH_STRLEN

static inline int strlen(const char *str) 
{                                         
    int i = 0;

    while(str[i] != '\0')
        i++;

    return i;
}

#endif /* _HAVE_ARCH_STRLEN */

#ifndef _HAVE_ARCH_MEMCPY

void *memcpy(void *dest, const void *src, size_t len)
{
    void *ret = dest;

    while( len-- ){
        *(char *)dest = *(char *)src;
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }

    return(ret);
}

#endif /* _HAVE_ARCH_MEMCPY */

#ifndef _HAVE_ARCH_MEMSET

void *memset(void *dest, const char c, size_t len)
{
    void *ret = dest;

    while(len--){
        *(char *)dest = c;
        dest = (char *)dest + 1;
    }

    return(ret);
}

#endif /* _HAVE_ARCH_MEMSET */
