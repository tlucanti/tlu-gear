
#ifndef _LIBC_LEXICAL_H_
#define _LIBC_LEXICAL_H_

#include <stdint.h>

#define MAX_NUMBER_LEN sizeof(int64_t) * 8 + 1

unsigned int numtos(char *s, int64_t num);
unsigned int unumtos(char *s, uint64_t num);
unsigned int numtos_base(char *s, int64_t num, unsigned short base);
unsigned int unumtos_base(char *s, uint64_t num, unsigned short base);
unsigned int numtos_base_upper(char *s, int64_t num, unsigned short base);
unsigned int unumtos_base_upper(char *s, uint64_t num, unsigned short base);

#endif /* _LIBC_LEXICAL_H_ */

