
#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <core/types.h>

bool tlu_streq(const char *a, const char *b);
char *tlu_strchr(const char *s, uint8 c);
uint64 tlu_strcmp(const char *a, const char *b);
uint64 tlu_strlen(const char *s);
uint64 tlu_strncmp(const char *a, const char *b, uint64 size);

#endif /* LIBC_STRING_H */

