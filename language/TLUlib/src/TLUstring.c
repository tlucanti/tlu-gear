
#include "../inc/TLUstring.h"

void    *_TLUmemset(void *ptr, unsigned char c, size_t size)
{
    return memset(ptr, c, size);
}

void    *_TLUmemcpy(void *dest, void *src, size_t size)
{
    return memmove(dest, src, size);
}

__WUR
size_t  _TLUstrlen(const char *st)
{
    return strlen(st);
}

__WUR
int     _TLUisdigit(unsigned char c)
{
    return (unsigned)(c - '0') <= ('9' - '0');
}

__WUR
int     _TLUislower(unsigned char c)
{
    return (unsigned)(c - 'a') <= ('z' - 'a');
}

__WUR
int     _TLUisupper(unsigned char c)
{
    return (unsigned)(c - 'A') <= ('Z' - 'A');
}

__WUR
int     _TLUisalpha(unsigned char c)
{
    return (unsigned)(c - 'A') <= ('z' - 'A') && (unsigned)(c - '[') > ('`' - '[');
}

__WUR   _TLUisalnum(unsigned char c)
{
    return (unsigned)(c - '0') <= ('9' - '0') ||
        ((unsigned)(c - 'A') <= ('z' - 'A') && (unsigned)(c - '[') > ('`' - '['));
}

