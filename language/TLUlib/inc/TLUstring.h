
#ifndef TLU_STRING_H
# define TLU_STRING_H

/* remove this */ #include <string.h>

void    *_TLUmemset(void *ptr, unsigned char c, size_t size);
void    *_TLUmemcpy(void *dest, void *src, size_t size);
__WUR size_t  _TLUstrlen(const char *st);

#endif TLU_STRING_H
