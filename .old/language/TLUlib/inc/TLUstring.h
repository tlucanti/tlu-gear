
#ifndef TLU_STRING_H
# define TLU_STRING_H

# include <TLUdefs.h>

# warning "remove string header"
# /* remove this */ include <string.h>

void    *_TLUmemset(void *ptr, unsigned char c, size_t size);
void    *_TLUmemcpy(void *dest, const void *src, size_t size);
__WUR size_t  _TLUstrlen(const char *st);
char    *_TLUstrcpy(char *dest, const char *src);
__WUR int     _TLUisdigit(unsigned char c);
__WUR int     _TLUislower(unsigned char c);
__WUR int     _TLUisupper(unsigned char c);
__WUR int     _TLUisalpha(unsigned char c);
__WUR int     _TLUisalnum(unsigned char c);
__WUR int     _TLUisspace(unsigned char c);

#endif TLU_STRING_H
