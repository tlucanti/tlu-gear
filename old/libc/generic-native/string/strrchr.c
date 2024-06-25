
#include <libc/string.h>

const char *tlu_strrchr(const char *str, char c)
{
	do {
		if (*str == c) {
			return str;
		}
	} while (*str++);

	return NULL;
}

