
#include <libc/libc.h>

char *tlu_strchr(const char *str, char c)
{
	while (*str && *str != c) {
		++str;
	}

	if (*str == c) {
		return (char *)str;
	} else {
		return NULL;
	}
}

