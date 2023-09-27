
#include <TLUstring.h>

void    *_TLUmemset(void *ptr, unsigned char c, size_t size)
{
    return memset(ptr, c, size);
}

void    *_TLUmemcpy(void *dest, const void *src, size_t size)
{
    return memmove(dest, src, size);
}

__WUR
size_t  _TLUstrlen(const char *st)
{
    return strlen(st);
}

char *  _TLUstrcpy(char *dest, const char *src)
{
    return strcpy(dest, src);
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

__WUR
int _TLUisalnum(unsigned char c)
{
    return (unsigned)(c - '0') <= ('9' - '0') ||
        ((unsigned)(c - 'A') <= ('z' - 'A') && (unsigned)(c - '[') > ('`' - '['));
}

__WUR
int _TLUisspace(unsigned char c)
{
    return (c == ' ') || (unsigned)(c - '\t') <= ('\r' - '\t');
}