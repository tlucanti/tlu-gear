
#include <libc/string.h>

const char *tlu_strstr(const char *s, const char *pattern)
{
	while (*s) {
		if (tlu_sstartswith(s, pattern)) {
			return s;
		}
		++s;
	}
	return NULL;
}

