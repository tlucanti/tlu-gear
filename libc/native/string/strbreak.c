
#include <libc/string.h>

char *tlu_strbreak(const char *s, const char *breakset)
{
	while (*s) {
		if (tlu_strchr(breakset, *s) != NULL) {
			return (char *)s;
		}
		s++;
	}

	return NULL;
}

