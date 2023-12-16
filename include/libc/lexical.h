
#ifndef _LIBC_LEXICAL_H_
#define _LIBC_LEXICAL_H_

#include <stdint.h>

int numtos(char *s, intmax_t num);
int unumtos(char *s, uintmax_t num);
int numtos_base(char *s, intmax_t num, unsigned short base);
int unumtos_base(char *s, uintmax_t num, unsigned short base);
int numtos_base_upper(char *s, intmax_t num, unsigned short base);
int unumtos_base_upper(char *s, uintmax_t num, unsigned short base);

#endif /* _LIBC_LEXICAL_H_ */

