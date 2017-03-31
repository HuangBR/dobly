#include <stdarg.h>
#include <stddef.h>
#include <os/kernel.h>

extern int vsprintf(char *, const char *, va_list);
extern int print(char *);

static char buf[1024];

int printk(const char *fmt, ...)
{
    va_list args;
    int i;

    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    va_end(args);

    print(buf);

    return i;
}
