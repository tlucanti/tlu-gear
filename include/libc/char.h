
#ifndef _LIBC_CHAR_H_
#define _LIBC_CHAR_H_

#include <stdbool.h>

bool tlu_isalnum(unsigned char c);
bool tlu_isalpha(unsigned char c);
bool tlu_isdigit(unsigned char c);
bool tlu_islower(unsigned char c);
bool tlu_isprint(unsigned char c);
bool tlu_ispunct(unsigned char c);
bool tlu_isspace(unsigned char c);
bool tlu_isupper(unsigned char c);
bool tlu_ishex(unsigned char c);

unsigned char tlu_tolower(unsigned char c);
unsigned char tlu_toupper(unsigned char c);

#endif /* _LIBC_CHAR_H_ */

