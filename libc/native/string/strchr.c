
#include <libc/string.h>

char *tlu_strchr(const char *s, uint8 c)
{
	while (*s) {
		if (*s == c)
			return (char *)s;
		s++;
	}

	if (c == '\0')
		return (char *)s;
	return NULL;
}

