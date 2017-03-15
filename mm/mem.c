#include <types.h>
#include "mm.h"

void *memcpy(void *dest, const void *src, size_t len)
{
    void *ret = dest;

    while( len-- ){
        *(char *)dest = *(char *)src;
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }

    return ret;
}
