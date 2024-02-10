
#include <libc/string.h>

const char *tlu_strrstr(const char *s, const char *pattern)
{
	const char *ret = NULL;
	do {
		if (tlu_sstartswith(s, pattern)) {
			ret = s;
		}
	} while (*s++);
	return ret;
}

