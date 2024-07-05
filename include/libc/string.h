
#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <core/types.h>

bool tlu_streq(const char *a, const char *b);
uint64 tlu_strcmp(const char *a, const char *b);
uint64 tlu_strlen(const char *s);

#endif /* LIBC_STRING_H */

