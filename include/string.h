#ifndef _STRING_H
#define _STRING_H


static inline int strlen(const char *str)
{
    int i = 0;

    while(str[i] != '\0')
        i++;

    return i;
}

#endif /* _STRING_H */
