
#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include <stddef.h>
#include <stdbool.h>

size_t tlu_strlen(const char *s);
int tlu_strcmp(const char *a, const char *b);
bool tlu_streq(const char *a, const char *b);
char *tlu_strchr(const char *str, char c);
char *tlu_strrchr(const char *str, char c);
bool tlu_sstartswith(const char *str, const char *pattern);

#endif /* _LIBC_STRING_H_ */

