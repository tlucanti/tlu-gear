
#include <libc/string.h>

const char *tlu_strstr(const char *s, const char *pattern)
{
	do {
		if (tlu_strstarts(s, pattern)) {
			return s;
		}
	} while (*s++);
	return NULL;
}

