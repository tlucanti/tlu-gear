
#ifndef _LIBC_LEXICAL_H_
#define _LIBC_LEXICAL_H_

#include <stdint.h>

#define MAX_NUMBER_LEN sizeof(int64_t) * 8 + 1

int numtos(char *s, int64_t num);
int unumtos(char *s, uint64_t num);
int numtos_base(char *s, int64_t num, unsigned short base);
int unumtos_base(char *s, uint64_t num, unsigned short base);
int numtos_base_upper(char *s, int64_t num, unsigned short base);
int unumtos_base_upper(char *s, uint64_t num, unsigned short base);

#endif /* _LIBC_LEXICAL_H_ */

