
#ifndef LIBC_CHAR_H
#define LIBC_CHAR_H

#include <core/types.h>

bool tlu_isalnum(uint8 c);
bool tlu_isalpha(uint8 c);
bool tlu_isdigit(uint8 c);
bool tlu_islower(uint8 c);
bool tlu_isprint(uint8 c);
bool tlu_ispunct(uint8 c);
bool tlu_isspace(uint8 c);
bool tlu_isupper(uint8 c);
bool tlu_ishex(uint8 c);

uint8 tlu_tolower(uint8 c);
uint8 tlu_toupper(uint8 c);

#endif /* LIBC_CHAR_H */

